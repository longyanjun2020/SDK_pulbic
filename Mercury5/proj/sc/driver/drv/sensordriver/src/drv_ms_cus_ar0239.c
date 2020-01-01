////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (??????MStar Confidential Information??????) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "drv_SensorIF_pub.h"
#include "drv_ms_cus_sensor.h"
#include "drv_i2c_common.h"

//#define _DEBUG_
#include <sensor_log.h>

#if defined(__RTK_OS__)
#include "cam_os_wrapper.h"
#if defined(__GNUC__)
#include "vm_types.ht"
#endif
#include "libcamera.h"
#include "AIT_Init.h"
#include "Config_SDK.h" //By project.
#else //#if defined(__RTK_OS__)

#include "isp_config.h"
#if (SENSOR0 == AR0239)
#define BIND_SENSOR_AR0239 (1)
#endif
#endif //#if defined(__RTK_OS__)

#if defined(BIND_SENSOR_AR0239) && (BIND_SENSOR_AR0239 == 1)

#define SENSOR_PAD_GROUP_SET CUS_SENSOR_PAD_GROUP_A
#define SENSOR_CHANNEL_NUM (0)
#define SENSOR_CHANNEL_MODE CUS_SENSOR_CHANNEL_MODE_REALTIME_NORMAL

//============================================
//MIPI config begin.
#define SENSOR_MIPI_LANE_NUM (4)
#define SENSOR_MIPI_HDR_MODE (0)
//MIPI config end.
//============================================

#define SENSOR_MODEL_ID     "AR0239"

#define SENSOR_ISP_TYPE     ISP_EXT
#define SENSOR_IFBUS_TYPE   CUS_SENIF_BUS_MIPI      //CFG //CUS_SENIF_BUS_PARL, CUS_SENIF_BUS_MIPI
#define SENSOR_MIPI_DELAY   0x1212                  //CFG
#define SENSOR_DATAPREC     CUS_DATAPRECISION_12    //CUS_DATAPRECISION_8, CUS_DATAPRECISION_10
#define SENSOR_DATAMODE     CUS_SEN_10TO12_9000     //CFG

#define SENSOR_BAYERID      CUS_BAYER_RG          //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
//#define SENSOR_BAYERID      CUS_BAYER_GB          //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
//#define SENSOR_BAYERID      CUS_BAYER_BG            //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
//#define SENSOR_BAYERID      CUS_BAYER_GR          //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
#define SENSOR_ORIT         CUS_ORIT_M0F0           //CUS_ORIT_M0F0, CUS_ORIT_M1F0, CUS_ORIT_M0F1, CUS_ORIT_M1F1,
#define SENSOR_MAX_GAIN     (64 * 1024)//65536
#define SENSOR_MIN_GAIN      (2 * 1024)//2048
#define SENSOR_GAIN_DELAY_FRAME_COUNT      (2)
#define SENSOR_SHUTTER_DELAY_FRAME_COUNT      (2)

#define Preview_MCLK_SPEED  CUS_CMU_CLK_27MHZ       //MCLK from SCL

#define Preview_line_period 29630                   //33.333/1125
#define Prv_Max_line_number 1080                    //maximum exposure line munber of sensor when preview
//#define vts_30fps           1125                  //74.25M = 2200*1125*30
#define vts_30fps           1134                    //74.25M < 2200*1134*30
#define Preview_WIDTH       1920                    //resolution Width when preview
#define Preview_HEIGHT      1080                    //resolution Height when preview
#define Preview_MAX_FPS     30                      //fastest preview FPS
#define Preview_MIN_FPS     8                       //slowest preview FPS
#define Preview_CROP_START_X     1                  //CROP_START_X
#define Preview_CROP_START_Y     1                  //CROP_START_Y

#define Cap_Max_line_number 1080                    //maximum exposure line munber of sensor when capture

#define SENSOR_I2C_ADDR     0x20
#define SENSOR_I2C_SPEED    I2C_SLOWSPEED_MODE_200KHZ   //200KHz
#define SENSOR_I2C_CHANNEL  1                       //I2C Channel
#define SENSOR_I2C_PAD_MODE 2                       //Pad/Mode Number
#define SENSOR_I2C_LEGACY   I2C_NORMAL_MODE            //usally set CUS_I2C_NORMAL_MODE,  if use old OVT I2C protocol=> set CUS_I2C_LEGACY_MODE
#define SENSOR_I2C_FMT      I2C_FMT_A16D16

#define SENSOR_PWDN_POL     CUS_CLK_POL_POS         // AR0239 no care, OE_BAR pull low always enable
#define SENSOR_RST_POL      CUS_CLK_POL_NEG         // AR0239 RESET active LOW

#define SENSOR_VSYNC_POL    CUS_CLK_POL_NEG//CUS_CLK_POL_POS         // if VSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_HSYNC_POL    CUS_CLK_POL_POS         // if HSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_PCLK_POL     CUS_CLK_POL_POS         // depend on sensor setting, sometimes need to try CUS_CLK_POL_POS or CUS_CLK_POL_NEG

int ar0239_MIPI_cus_camsensor_release_handle(ms_cus_sensor *handle);

static CUS_CAMSENSOR_CAP sensor_cap =
{
    .length = sizeof(CUS_CAMSENSOR_CAP),
    .version = 0x0001,
};

typedef struct
{
    struct
    {
        float sclk;
        u32 hts;
        u32 vts;
        u32 ho;
        u32 xinc;
        u32 line_freq;
        u32 us_per_line;
        u32 final_us;
        u32 final_gain;
        u32 back_pv_us;
        u32 fps;
    } expo;
    struct
    {
        CUS_CAMSENSOR_ORIT new_setting;            //the mirror/flip status set from user
        CUS_CAMSENSOR_ORIT cur;            //current sensor setting
    } mirror_flip;

    int sen_init;
    int still_min_fps;
    int video_min_fps;
    bool reg_dirty;            //sensor setting need to update through I2C
} ar0239_params;

typedef struct
{
    float total_gain;
    unsigned short analog_gain_reg;
    unsigned short HCG_gain_reg;

} Gain_ARRAY;

static I2C_ARRAY Sensor_id_table[] =
{
{0x3000, 0x1256},            // ar0239
//{0x300E, 0x0256},    // ar0239
};

#if 0 //UnSupport LI-HDR
static I2C_ARRAY Sensor_init_table[] =
{
//MIPI 4-lane LI-HDR mode 1080p@30fps
{0x301A,    0x1}, //reset

//DELAY = 100
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},

//Line_Interleaved_sequencer_2017-07-18
{0x3088,    0x8130},
{0x3086,    0x4558},
{0x3086,    0x729B},
{0x3086,    0x4A31},
{0x3086,    0x43C5},
{0x3086,    0x2A08},
{0x3086,    0x42CE},
{0x3086,    0xCB8E},
{0x3086,    0x345 },
{0x3086,    0x782A},
{0x3086,    0x1C7B},
{0x3086,    0xCA3D},
{0x3086,    0xFF3D},
{0x3086,    0xFF3D},
{0x3086,    0xEA2A},
{0x3086,    0xC3D },
{0x3086,    0x102A},
{0x3086,    0xD2A },
{0x3086,    0x1D35},
{0x3086,    0x2A0D},
{0x3086,    0x3D10},
{0x3086,    0x4558},
{0x3086,    0x2A0C},
{0x3086,    0x8E03},
{0x3086,    0x2A1C},
{0x3086,    0x3DFF},
{0x3086,    0x3DFF},
{0x3086,    0x3DEA},
{0x3086,    0x2A0C},
{0x3086,    0x62CC},
{0x3086,    0xCF2A},
{0x3086,    0x288E},
{0x3086,    0x36  },
{0x3086,    0x2A08},
{0x3086,    0x3D64},
{0x3086,    0x7ACD},
{0x3086,    0x3D04},
{0x3086,    0x442A},
{0x3086,    0x982C},
{0x3086,    0x4B8F},
{0x3086,    0xC257},
{0x3086,    0x43  },
{0x3086,    0xC2D },
{0x3086,    0x6343},
{0x3086,    0x5FC4},
{0x3086,    0xC52A},
{0x3086,    0xFCC8},
{0x3086,    0xC553},
{0x3086,    0x553 },
{0x3086,    0x78E },
{0x3086,    0x34D },
{0x3086,    0x2BF8},
{0x3086,    0x2924},
{0x3086,    0x29AE},
{0x3086,    0x45DC},
{0x3086,    0x3F04},
{0x3086,    0x5C19},
{0x3086,    0x495C},
{0x3086,    0x1B2A},
{0x3086,    0xFE8E},
{0x3086,    0xF3F },
{0x3086,    0x32B },
{0x3086,    0xB82B},
{0x3086,    0x984E},
{0x3086,    0x29BA},
{0x3086,    0x5397},
{0x3086,    0x604C},
{0x3086,    0x945 },
{0x3086,    0xCC45},
{0x3086,    0x8C5C},
{0x3086,    0xB3F },
{0x3086,    0x88E },
{0x3086,    0xD2A },
{0x3086,    0xFA3F},
{0x3086,    0x105C},
{0x3086,    0x33F },
{0x3086,    0x23E },
{0x3086,    0x10C3},
{0x3086,    0x5F2A},
{0x3086,    0xF2C7},
{0x3086,    0x2B90},
{0x3086,    0x2B80},
{0x3086,    0x5307},
{0x3086,    0x603F},
{0x3086,    0x629 },
{0x3086,    0xAAD0},
{0x3086,    0x2983},
{0x3086,    0x5F4D},
{0x3086,    0x1945},
{0x3086,    0xAC2A},
{0x3086,    0xFAC6},
{0x3086,    0x3E05},
{0x3086,    0x2AFB},
{0x3086,    0x5D16},
{0x3086,    0x8811},
{0x3086,    0x3E87},
{0x3086,    0x2992},
{0x3086,    0x2145},
{0x3086,    0x882B},
{0x3086,    0x485 },
{0x3086,    0x3F04},
{0x3086,    0x2AFA},
{0x3086,    0x8E09},
{0x3086,    0x3F04},
{0x3086,    0x4D4E},
{0x3086,    0x1648},
{0x3086,    0x2B80},
{0x3086,    0x4C0C},
{0x3086,    0x603F},
{0x3086,    0x7C3 },
{0x3086,    0x3F1A},
{0x3086,    0x2AF2},
{0x3086,    0xC73F},
{0x3086,    0xD29 },
{0x3086,    0x82D0},
{0x3086,    0x4558},
{0x3086,    0x5F4D},
{0x3086,    0x19C6},
{0x3086,    0xD32A},
{0x3086,    0xFAD2},
{0x3086,    0xC92A},
{0x3086,    0x988E},
{0x3086,    0x12  },
{0x3086,    0x4404},
{0x3086,    0x434A},
{0x3086,    0x543 },
{0x3086,    0x1658},
{0x3086,    0x4316},
{0x3086,    0x5A43},
{0x3086,    0x1606},
{0x3086,    0x4316},
{0x3086,    0x743 },
{0x3086,    0x1645},
{0x3086,    0x783F},
{0x3086,    0x48E },
{0x3086,    0x32A },
{0x3086,    0x9D5D},
{0x3086,    0x1688},
{0x3086,    0x112B},
{0x3086,    0x453 },
{0x3086,    0xD86 },
{0x3086,    0x2944},
{0x3086,    0x3F05},
{0x3086,    0x2545},
{0x3086,    0x584D},
{0x3086,    0x2B64},
{0x3086,    0x2A98},
{0x3086,    0x8E00},
{0x3086,    0x1244},
{0x3086,    0x4BC1},
{0x3086,    0x9BB9},
{0x3086,    0x2C2C},
{0x3086,    0x2C2C},

//PCLK_44MHz_528Mbps/lane
{0x302A,  6     },
{0x302C,  1     },
{0x302E,  9     },
{0x3030,  176   },
{0x3036,  12    },
{0x3038,  1     },
{0x301A,  0x2058},
{0x30B0,  0x023A},
{0x31B0,  0x0090},
{0x31B2,  0x0065},
{0x31B4,  0x2765},
{0x31B6,  0x1151},
{0x31B8,  0x5047},
{0x31BA,  0x0186},
{0x31BC,  0x8007},
{0x3354,  0x002C},

{0x3100,    0x0000},    // AECTRLREG
{0x3786,    0x6204},    // DIGITAL_CTRL_1

//working mode
{0x3082,  0x4028},
{0x318E,  0x9000},
{0x31D0,  0x0000},
{0x31AE,  0x0204},
{0x3004,  12    },
{0x3008,  1931  },
{0x3002,  54    },
{0x3006,  1133  },
{0x300C,  1254  },
{0x300A,  1100  },
{0x3012,  1098  },
{0x31AC,  0x0C0C},
{0x306E,  0x9010},
{0x30A2,  0x0001},
{0x30A6,  0x0001},

//Recommended Settings ES
{0x3EFC,    0xE0FF},
{0x30AE,    0x0003},
{0x3092,    0x086F},
{0x30BA,    0x762C},
{0x317E,    0x8F70},
{0x3180,    0x8040},
{0x3ED2,    0x0099},
{0x3ED6,    0x14A1},
{0x3ED8,    0xF9EE},
{0x3EDA,    0x6E40},
{0x3EDC,    0x08C5},
{0x3EDE,    0x11A1},
{0x3EE0,    0x118A},
{0x3EE2,    0x31C6},
{0x3EE4,    0x0D77},
{0x3EFE,    0x96F2},
{0x3F04,    0x0C18},
{0x3ED0,    0xC400},
{0x3ED4,    0x03CF},
{0x3ECE,    0x40F3},
{0x3F02,    0x2E1C},
{0x3EF4,    0x5805},
{0x3EF2,    0x9464},
{0x3EF2,    0x9464},
{0x3EF2,    0x9464},
{0x3EF4,    0x5805},
{0x3EF4,    0x5805},
{0x3EF4,    0x5805},
{0x3EF6,    0x5253},
{0x3EF6,    0x5253},
{0x3EF6,    0x5253},
{0x3EF8,    0x54F4},
{0x3EF8,    0x54F4},
{0x3EF8,    0x54F4},
{0x3F4C,    0x52BC},
{0x3F4C,    0x52BC},
{0x3F4E,    0x3E3C},
{0x3F4E,    0x3E3C},
{0x3F50,    0x380B},
{0x3F50,    0x380B},
{0x31E0,    0x000F},
{0x3324,    0x001C},

//CFPN Improvement settings for HDR Mode 2017-1-31
{0x3EFE,    0x96F2},
{0x3F04,    0x0F18},
{0x3F02,    0x2F1C},
{0x3ED0,    0xC400},
{0x3ED4,    0x03CF},
{0x3EF4,    0x1425},
{0x3ECE,    0x40F3},
{0x3EE6,    0xF723},
{0x3EF0,    0x1828},
{0x3EE8,    0xE4FF},
{0x3EFA,    0x638A},
{0x3EF2,    0x9464},
{0x3EF2,    0x9464},
{0x3EF2,    0x9464},
{0x3EF4,    0x1825},
{0x3EF4,    0x5825},
{0x3EF4,    0x5825},
{0x3EF6,    0x5253},
{0x3EF6,    0x5253},
{0x3EF6,    0x5253},
{0x3EF8,    0x54F4},
{0x3EF8,    0x54F4},
{0x3EF8,    0x54F4},

{0x3064,    0x1802},    //SMIA_TEST
{0x301A,    0x205C},    //streaming on
};
#endif

#if (SENSOR_MIPI_LANE_NUM == 2)
static I2C_ARRAY SensorInitTable_Mipi2Lane12Bit_FHD30Fps[] =
{
//MIPI 2-lane 12 bit Linear mode Init, FHD@30fps
{0x301A,    0x1}, //reset

//DELAY = 100
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},

//Linear_mode_sequencer_2017-01-17
{0x3088,    0x8000},
{0x3086,    0x4558},
{0x3086,    0x72A6},
{0x3086,    0x4A31},
{0x3086,    0x43C5},
{0x3086,    0x2A08},
{0x3086,    0x42CE},
{0x3086,    0xCB8E},
{0x3086,    0x0345},
{0x3086,    0x782A},
{0x3086,    0x1C7B},
{0x3086,    0xCA3D},
{0x3086,    0xFF3D},
{0x3086,    0xFF3D},
{0x3086,    0xEA2A},
{0x3086,    0x0C3D},
{0x3086,    0x102A},
{0x3086,    0x0D2A},
{0x3086,    0x1D35},
{0x3086,    0x2A0D},
{0x3086,    0x3D10},
{0x3086,    0x4558},
{0x3086,    0x2A0C},
{0x3086,    0x8E03},
{0x3086,    0x2A1C},
{0x3086,    0x3DFF},
{0x3086,    0x3DFF},
{0x3086,    0x3DEA},
{0x3086,    0x2A0C},
{0x3086,    0x62CC},
{0x3086,    0xCF2A},
{0x3086,    0x288E},
{0x3086,    0x0036},
{0x3086,    0x2A08},
{0x3086,    0x3D64},
{0x3086,    0x7ACD},
{0x3086,    0x3D04},
{0x3086,    0x442A},
{0x3086,    0x982C},
{0x3086,    0x4BA4},
{0x3086,    0xC257},
{0x3086,    0x0043},
{0x3086,    0x0C2D},
{0x3086,    0x6343},
{0x3086,    0x5FC4},
{0x3086,    0xC52A},
{0x3086,    0xFCC8},
{0x3086,    0xC553},
{0x3086,    0x0553},
{0x3086,    0x078E},
{0x3086,    0x034D},
{0x3086,    0x2BF8},
{0x3086,    0x2924},
{0x3086,    0x29AE},
{0x3086,    0x3F07},
{0x3086,    0x45DC},
{0x3086,    0x5C19},
{0x3086,    0x494C},
{0x3086,    0x095C},
{0x3086,    0x1B2A},
{0x3086,    0xFE8E},
{0x3086,    0x0F3F},
{0x3086,    0x032B},
{0x3086,    0xB82B},
{0x3086,    0x984E},
{0x3086,    0x29BA},
{0x3086,    0x6016},
{0x3086,    0x45CC},
{0x3086,    0x1645},
{0x3086,    0x8C3F},
{0x3086,    0x088E},
{0x3086,    0x0D5C},
{0x3086,    0x0B2A},
{0x3086,    0xFA3F},
{0x3086,    0x325C},
{0x3086,    0x033F},
{0x3086,    0x233E},
{0x3086,    0x105F},
{0x3086,    0x2AF2},
{0x3086,    0x2B90},
{0x3086,    0x2B80},
{0x3086,    0xC73F},
{0x3086,    0x0860},
{0x3086,    0x29AA},
{0x3086,    0xD029},
{0x3086,    0x835F},
{0x3086,    0x4D19},
{0x3086,    0x45AC},
{0x3086,    0x2AFA},
{0x3086,    0xC63E},
{0x3086,    0x052A},
{0x3086,    0xFB2A},
{0x3086,    0xFB5D},
{0x3086,    0x8810},
{0x3086,    0x3F06},
{0x3086,    0x4588},
{0x3086,    0x2992},
{0x3086,    0x212B},
{0x3086,    0x0485},
{0x3086,    0x3F04},
{0x3086,    0x2AFA},
{0x3086,    0x8E09},
{0x3086,    0x8D4D},
{0x3086,    0x4E48},
{0x3086,    0x2B80},
{0x3086,    0x4C0C},
{0x3086,    0x603F},
{0x3086,    0x30C7},
{0x3086,    0xC33F},
{0x3086,    0x052A},
{0x3086,    0xF23F},
{0x3086,    0x083F},
{0x3086,    0x0829},
{0x3086,    0x82C6},
{0x3086,    0xD0D2},
{0x3086,    0x4558},
{0x3086,    0xD35F},
{0x3086,    0x4D19},
{0x3086,    0x2AFA},
{0x3086,    0xC92A},
{0x3086,    0x988E},
{0x3086,    0x0012},
{0x3086,    0x444A},
{0x3086,    0x0443},
{0x3086,    0x1605},
{0x3086,    0x4316},
{0x3086,    0x5843},
{0x3086,    0x165A},
{0x3086,    0x4316},
{0x3086,    0x0643},
{0x3086,    0x1607},
{0x3086,    0x4316},
{0x3086,    0x8E03},
{0x3086,    0x4578},
{0x3086,    0x3F05},
{0x3086,    0x2A9D},
{0x3086,    0x5D88},
{0x3086,    0x112B},
{0x3086,    0x0453},
{0x3086,    0x0D86},
{0x3086,    0x2944},
{0x3086,    0x8D4D},
{0x3086,    0x2B64},
{0x3086,    0x3F20},
{0x3086,    0x4558},
{0x3086,    0x253F},
{0x3086,    0x058E},
{0x3086,    0x002A},
{0x3086,    0x9812},
{0x3086,    0x444B},
{0x3086,    0xC1A6},
{0x3086,    0xB92C},
{0x3086,    0x2C2C},
{0x3086,    0x2C2C},

//PLL_32MHZ_setup
{0x302A,    12    },
{0x302C,    1     },
{0x302E,    9     },
{0x3030,    128   },
{0x3036,    12    },
{0x3038,    1     },

{0x30B0,    0x023A},
{0x31B0,    0x0090},
{0x31B2,    0x0065},
{0x31B4,    0x2FA9},
{0x31B6,    0x42E0},
{0x31B8,    0xA04B},
{0x31BA,    0x030D},
{0x31BC,    0x800B},
{0x3354,    0x002C},

//Recommended Settings 2017-1-25
{0x3EFC,    0xE0FF},
{0x30AE,    0x0003},
{0x3092,    0x086F},
{0x30BA,    0x762C},
{0x317E,    0x8F70},
{0x3180,    0x8040},
{0x3ED2,    0x0099},
{0x3ED6,    0x14A0},
{0x3ED8,    0xFAEE},
{0x3EDA,    0x6E40},
{0x3EDC,    0x08C5},
{0x3EDE,    0x11A1},
{0x3EE0,    0x118A},
{0x3EE2,    0x31C6},
{0x3EE4,    0x0D77},
{0x3EFE,    0x96F2},
{0x3F04,    0x0C18},
{0x3ED0,    0xC400},
{0x3ED4,    0x03CF},
{0x3ECE,    0x40F3},
{0x3F02,    0x2E1C},
{0x3EF4,    0x1425},
{0x3EF2,    0x1465},
{0x3EF2,    0x9465},
{0x3EF2,    0x9464},
{0x3EF4,    0x1825},
{0x3EF4,    0x5825},
{0x3EF4,    0x5825},
{0x3EF6,    0x1252},
{0x3EF6,    0x5252},
{0x3EF6,    0x5253},
{0x3EF8,    0x14F2},
{0x3EF8,    0x54F2},
{0x3EF8,    0x54F4},

//working mode
{0x3082,    0x0001},
{0x318E,    0x0000},
{0x31D0,    0x0000},
{0x31AE,    0x0202},
{0x3004,    12    },
{0x3008,    1931  },
{0x3002,    4     },
{0x3006,    1083  },
{0x300C,    969   },
{0x300A,    1100  },
{0x3012,    1099  },
{0x31AC,    0x0C0C},
{0x306E,    0x9010},
{0x30A2,    0x0001},
{0x30A6,    0x0001},
{0x301A,    0x205C},

{0x3064,    0x1802},    //SMIA_TEST
{0x301A,    0x205C},    //streaming on
};
#endif

#if (SENSOR_MIPI_LANE_NUM == 4)
static I2C_ARRAY SensorInitTable_Mipi4Lane12Bit_FHD30Fps[] =
{
//MIPI 4-lane 12 bit Linear mode Init, FHD@30fps
{0x301A,    0x01},  //streaming off

//DELAY = 100
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},

//Linear_mode_sequencer_Serial
{0x3088,    0x8000},
{0x3086,    0x4558},
{0x3086,    0x72A6},
{0x3086,    0x4A31},
{0x3086,    0x43C5},
{0x3086,    0x2A08},
{0x3086,    0x42CE},
{0x3086,    0xCB8E},
{0x3086,    0x345 },
{0x3086,    0x782A},
{0x3086,    0x1C7B},
{0x3086,    0xCA3D},
{0x3086,    0xFF3D},
{0x3086,    0xFF3D},
{0x3086,    0xEA2A},
{0x3086,    0xC3D },
{0x3086,    0x102A},
{0x3086,    0xD2A },
{0x3086,    0x1D35},
{0x3086,    0x2A0D},
{0x3086,    0x3D10},
{0x3086,    0x4558},
{0x3086,    0x2A0C},
{0x3086,    0x8E03},
{0x3086,    0x2A1C},
{0x3086,    0x3DFF},
{0x3086,    0x3DFF},
{0x3086,    0x3DEA},
{0x3086,    0x2A0C},
{0x3086,    0x62CC},
{0x3086,    0xCF2A},
{0x3086,    0x288E},
{0x3086,    0x36  },
{0x3086,    0x2A08},
{0x3086,    0x3D64},
{0x3086,    0x7ACD},
{0x3086,    0x3D04},
{0x3086,    0x442A},
{0x3086,    0x982C},
{0x3086,    0x4BA4},
{0x3086,    0xC257},
{0x3086,    0x43  },
{0x3086,    0xC2D },
{0x3086,    0x6343},
{0x3086,    0x5FC4},
{0x3086,    0xC52A},
{0x3086,    0xFCC8},
{0x3086,    0xC553},
{0x3086,    0x553 },
{0x3086,    0x78E },
{0x3086,    0x34D },
{0x3086,    0x2BF8},
{0x3086,    0x2924},
{0x3086,    0x29AE},
{0x3086,    0x3F07},
{0x3086,    0x45DC},
{0x3086,    0x5C19},
{0x3086,    0x494C},
{0x3086,    0x95C },
{0x3086,    0x1B2A},
{0x3086,    0xFE8E},
{0x3086,    0xF3F },
{0x3086,    0x92B },
{0x3086,    0xB82B},
{0x3086,    0x984E},
{0x3086,    0x45CC},
{0x3086,    0x1645},
{0x3086,    0x8C3F},
{0x3086,    0x8E  },
{0x3086,    0xD29 },
{0x3086,    0xBA60},
{0x3086,    0x3F00},
{0x3086,    0x5C0B},
{0x3086,    0x2AFA},
{0x3086,    0x3F32},
{0x3086,    0x5C03},
{0x3086,    0x3F23},
{0x3086,    0x3E10},
{0x3086,    0x5F2A},
{0x3086,    0xF22B},
{0x3086,    0x902B},
{0x3086,    0x80C7},
{0x3086,    0x3F08},
{0x3086,    0x6029},
{0x3086,    0xAAD0},
{0x3086,    0x2983},
{0x3086,    0x5F4D},
{0x3086,    0x1945},
{0x3086,    0xAC2A},
{0x3086,    0xFAC6},
{0x3086,    0x3E05},
{0x3086,    0x2AFB},
{0x3086,    0x5D88},
{0x3086,    0x103F},
{0x3086,    0x2F45},
{0x3086,    0x8829},
{0x3086,    0x9221},
{0x3086,    0x2B04},
{0x3086,    0x853F},
{0x3086,    0x42A },
{0x3086,    0xFA8E},
{0x3086,    0x98D },
{0x3086,    0x4D4E},
{0x3086,    0x482B},
{0x3086,    0x804C},
{0x3086,    0xC60 },
{0x3086,    0x3F30},
{0x3086,    0xC7C3},
{0x3086,    0x3F0B},
{0x3086,    0x2AF2},
{0x3086,    0x3F08},
{0x3086,    0x3F08},
{0x3086,    0x2982},
{0x3086,    0xC6D0},
{0x3086,    0xD245},
{0x3086,    0x58D3},
{0x3086,    0x5F4D},
{0x3086,    0x192A},
{0x3086,    0xFAC9},
{0x3086,    0x2A98},
{0x3086,    0x8E00},
{0x3086,    0x1244},
{0x3086,    0x4A04},
{0x3086,    0x4316},
{0x3086,    0x543 },
{0x3086,    0x1658},
{0x3086,    0x4316},
{0x3086,    0x5A43},
{0x3086,    0x1606},
{0x3086,    0x4316},
{0x3086,    0x743 },
{0x3086,    0x168E},
{0x3086,    0x345 },
{0x3086,    0x783F},
{0x3086,    0x52A },
{0x3086,    0x9D5D},
{0x3086,    0x8811},
{0x3086,    0x2B04},
{0x3086,    0x530D},
{0x3086,    0x8629},
{0x3086,    0x448D},
{0x3086,    0x4D2B},
{0x3086,    0x643F},
{0x3086,    0x2045},
{0x3086,    0x5825},
{0x3086,    0x3F05},
{0x3086,    0x8E00},
{0x3086,    0x2A98},
{0x3086,    0x1244},
{0x3086,    0x4BC1},
{0x3086,    0xA6B9},
{0x3086,    0x2C2C},
{0x3086,    0x2C2C},

//PLL_64MHz_768Mbps/lane
{0x302A,  6     },
{0x302C,  1     },
{0x302E,  9     },
{0x3030,  128   },
{0x3036,  12    },
{0x3038,  1     },
{0x301A,  0x2058},
{0x30B0,  0x023A},
{0x31B0,  0x0090},
{0x31B2,  0x0065},
{0x31B4,  0x2A86},
{0x31B6,  0x21D6},
{0x31B8,  0x6049},
{0x31BA,  0x0208},
{0x31BC,  0x8007},
{0x3354,  0x002C},

#if 1
//working mode, MIPI 4 Lane FHD@30FPS
{0x3082,  0x0001},
{0x318E,  0x0000},
{0x31D0,  0x0000},
{0x31AE,  0x0204},
{0x3004,  12    },
{0x3008,  1931  },
{0x3002,  54    },
{0x3006,  1133  },
{0x300C,  1939  },
{0x300A,  1100  },
{0x3012,  1099  },
{0x31AC,  0x0C0C},
{0x306E,  0x9010},
{0x30A2,  0x0001},
{0x30A6,  0x0001},
#else
//working mode, MIPI 4 Lane FHD@60FPS
{0x3082,  0x0001},
{0x318E,  0x0000},
{0x31D0,  0x0000},
{0x31AE,  0x0204},
{0x3004,  12    },
{0x3008,  1931  },
{0x3002,  54    },
{0x3006,  1133  },
{0x300C,  968   },
{0x300A,  1100  },
{0x3012,  1099  },
{0x31AC,  0x0C0C},
{0x306E,  0x9010},
{0x30A2,  0x0001},
{0x30A6,  0x0001},
#endif

//Recommended Settings ES
{0x3EFC,    0xE0FF},
{0x30AE,    0x0003},
{0x3092,    0x086F},
{0x30BA,    0x762C},
{0x317E,    0x8F70},
{0x3180,    0x8040},
{0x3ED2,    0x0099},
{0x3ED6,    0x14A1},
{0x3ED8,    0xF9EE},
{0x3EDA,    0x6E40},
{0x3EDC,    0x08C5},
{0x3EDE,    0x11A1},
{0x3EE0,    0x118A},
{0x3EE2,    0x31C6},
{0x3EE4,    0x0D77},
{0x3EFE,    0x96F2},
{0x3F04,    0x0C18},
{0x3ED0,    0xC400},
{0x3ED4,    0x03CF},
{0x3ECE,    0x40F3},
{0x3F02,    0x2E1C},
{0x3EF4,    0x5805},
{0x3EF2,    0x9464},
{0x3EF2,    0x9464},
{0x3EF2,    0x9464},
{0x3EF4,    0x5805},
{0x3EF4,    0x5805},
{0x3EF4,    0x5805},
{0x3EF6,    0x5253},
{0x3EF6,    0x5253},
{0x3EF6,    0x5253},
{0x3EF8,    0x54F4},
{0x3EF8,    0x54F4},
{0x3EF8,    0x54F4},
{0x3F4C,    0x52BC},
{0x3F4C,    0x52BC},
{0x3F4E,    0x3E3C},
{0x3F4E,    0x3E3C},
{0x3F50,    0x380B},
{0x3F50,    0x380B},
{0x31E0,    0x000F},
{0x3324,    0x001C},

{0x3064,    0x1802},    //SMIA_TEST
{0x301A,    0x205C},    //streaming on
};

static I2C_ARRAY SensorInitTable_Mipi4Lane12Bit_FHD60Fps[] =
{
//MIPI 4-lane 12 bit Linear mode Init, FHD@60fps
{0x301A,    0x01},  //streaming off

//DELAY = 100
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},
{0xffff,  0x0},

//Linear_mode_sequencer_Serial
{0x3088,    0x8000},
{0x3086,    0x4558},
{0x3086,    0x72A6},
{0x3086,    0x4A31},
{0x3086,    0x43C5},
{0x3086,    0x2A08},
{0x3086,    0x42CE},
{0x3086,    0xCB8E},
{0x3086,    0x345 },
{0x3086,    0x782A},
{0x3086,    0x1C7B},
{0x3086,    0xCA3D},
{0x3086,    0xFF3D},
{0x3086,    0xFF3D},
{0x3086,    0xEA2A},
{0x3086,    0xC3D },
{0x3086,    0x102A},
{0x3086,    0xD2A },
{0x3086,    0x1D35},
{0x3086,    0x2A0D},
{0x3086,    0x3D10},
{0x3086,    0x4558},
{0x3086,    0x2A0C},
{0x3086,    0x8E03},
{0x3086,    0x2A1C},
{0x3086,    0x3DFF},
{0x3086,    0x3DFF},
{0x3086,    0x3DEA},
{0x3086,    0x2A0C},
{0x3086,    0x62CC},
{0x3086,    0xCF2A},
{0x3086,    0x288E},
{0x3086,    0x36  },
{0x3086,    0x2A08},
{0x3086,    0x3D64},
{0x3086,    0x7ACD},
{0x3086,    0x3D04},
{0x3086,    0x442A},
{0x3086,    0x982C},
{0x3086,    0x4BA4},
{0x3086,    0xC257},
{0x3086,    0x43  },
{0x3086,    0xC2D },
{0x3086,    0x6343},
{0x3086,    0x5FC4},
{0x3086,    0xC52A},
{0x3086,    0xFCC8},
{0x3086,    0xC553},
{0x3086,    0x553 },
{0x3086,    0x78E },
{0x3086,    0x34D },
{0x3086,    0x2BF8},
{0x3086,    0x2924},
{0x3086,    0x29AE},
{0x3086,    0x3F07},
{0x3086,    0x45DC},
{0x3086,    0x5C19},
{0x3086,    0x494C},
{0x3086,    0x95C },
{0x3086,    0x1B2A},
{0x3086,    0xFE8E},
{0x3086,    0xF3F },
{0x3086,    0x92B },
{0x3086,    0xB82B},
{0x3086,    0x984E},
{0x3086,    0x45CC},
{0x3086,    0x1645},
{0x3086,    0x8C3F},
{0x3086,    0x8E  },
{0x3086,    0xD29 },
{0x3086,    0xBA60},
{0x3086,    0x3F00},
{0x3086,    0x5C0B},
{0x3086,    0x2AFA},
{0x3086,    0x3F32},
{0x3086,    0x5C03},
{0x3086,    0x3F23},
{0x3086,    0x3E10},
{0x3086,    0x5F2A},
{0x3086,    0xF22B},
{0x3086,    0x902B},
{0x3086,    0x80C7},
{0x3086,    0x3F08},
{0x3086,    0x6029},
{0x3086,    0xAAD0},
{0x3086,    0x2983},
{0x3086,    0x5F4D},
{0x3086,    0x1945},
{0x3086,    0xAC2A},
{0x3086,    0xFAC6},
{0x3086,    0x3E05},
{0x3086,    0x2AFB},
{0x3086,    0x5D88},
{0x3086,    0x103F},
{0x3086,    0x2F45},
{0x3086,    0x8829},
{0x3086,    0x9221},
{0x3086,    0x2B04},
{0x3086,    0x853F},
{0x3086,    0x42A },
{0x3086,    0xFA8E},
{0x3086,    0x98D },
{0x3086,    0x4D4E},
{0x3086,    0x482B},
{0x3086,    0x804C},
{0x3086,    0xC60 },
{0x3086,    0x3F30},
{0x3086,    0xC7C3},
{0x3086,    0x3F0B},
{0x3086,    0x2AF2},
{0x3086,    0x3F08},
{0x3086,    0x3F08},
{0x3086,    0x2982},
{0x3086,    0xC6D0},
{0x3086,    0xD245},
{0x3086,    0x58D3},
{0x3086,    0x5F4D},
{0x3086,    0x192A},
{0x3086,    0xFAC9},
{0x3086,    0x2A98},
{0x3086,    0x8E00},
{0x3086,    0x1244},
{0x3086,    0x4A04},
{0x3086,    0x4316},
{0x3086,    0x543 },
{0x3086,    0x1658},
{0x3086,    0x4316},
{0x3086,    0x5A43},
{0x3086,    0x1606},
{0x3086,    0x4316},
{0x3086,    0x743 },
{0x3086,    0x168E},
{0x3086,    0x345 },
{0x3086,    0x783F},
{0x3086,    0x52A },
{0x3086,    0x9D5D},
{0x3086,    0x8811},
{0x3086,    0x2B04},
{0x3086,    0x530D},
{0x3086,    0x8629},
{0x3086,    0x448D},
{0x3086,    0x4D2B},
{0x3086,    0x643F},
{0x3086,    0x2045},
{0x3086,    0x5825},
{0x3086,    0x3F05},
{0x3086,    0x8E00},
{0x3086,    0x2A98},
{0x3086,    0x1244},
{0x3086,    0x4BC1},
{0x3086,    0xA6B9},
{0x3086,    0x2C2C},
{0x3086,    0x2C2C},

//PLL_64MHz_768Mbps/lane
{0x302A,  6     },
{0x302C,  1     },
{0x302E,  9     },
{0x3030,  128   },
{0x3036,  12    },
{0x3038,  1     },
{0x301A,  0x2058},
{0x30B0,  0x023A},
{0x31B0,  0x0090},
{0x31B2,  0x0065},
{0x31B4,  0x2A86},
{0x31B6,  0x21D6},
{0x31B8,  0x6049},
{0x31BA,  0x0208},
{0x31BC,  0x8007},
{0x3354,  0x002C},

#if 0
//working mode, MIPI 4 Lane FHD@30FPS
{0x3082,  0x0001},
{0x318E,  0x0000},
{0x31D0,  0x0000},
{0x31AE,  0x0204},
{0x3004,  12    },
{0x3008,  1931  },
{0x3002,  54    },
{0x3006,  1133  },
{0x300C,  1939  },
{0x300A,  1100  },
{0x3012,  1099  },
{0x31AC,  0x0C0C},
{0x306E,  0x9010},
{0x30A2,  0x0001},
{0x30A6,  0x0001},
#else
//working mode, MIPI 4 Lane FHD@60FPS
{0x3082,  0x0001},
{0x318E,  0x0000},
{0x31D0,  0x0000},
{0x31AE,  0x0204},
{0x3004,  12    },
{0x3008,  1931  },
{0x3002,  54    },
{0x3006,  1133  },
{0x300C,  968   },
{0x300A,  1100  },
{0x3012,  1099  },
{0x31AC,  0x0C0C},
{0x306E,  0x9010},
{0x30A2,  0x0001},
{0x30A6,  0x0001},
#endif

//Recommended Settings ES
{0x3EFC,    0xE0FF},
{0x30AE,    0x0003},
{0x3092,    0x086F},
{0x30BA,    0x762C},
{0x317E,    0x8F70},
{0x3180,    0x8040},
{0x3ED2,    0x0099},
{0x3ED6,    0x14A1},
{0x3ED8,    0xF9EE},
{0x3EDA,    0x6E40},
{0x3EDC,    0x08C5},
{0x3EDE,    0x11A1},
{0x3EE0,    0x118A},
{0x3EE2,    0x31C6},
{0x3EE4,    0x0D77},
{0x3EFE,    0x96F2},
{0x3F04,    0x0C18},
{0x3ED0,    0xC400},
{0x3ED4,    0x03CF},
{0x3ECE,    0x40F3},
{0x3F02,    0x2E1C},
{0x3EF4,    0x5805},
{0x3EF2,    0x9464},
{0x3EF2,    0x9464},
{0x3EF2,    0x9464},
{0x3EF4,    0x5805},
{0x3EF4,    0x5805},
{0x3EF4,    0x5805},
{0x3EF6,    0x5253},
{0x3EF6,    0x5253},
{0x3EF6,    0x5253},
{0x3EF8,    0x54F4},
{0x3EF8,    0x54F4},
{0x3EF8,    0x54F4},
{0x3F4C,    0x52BC},
{0x3F4C,    0x52BC},
{0x3F4E,    0x3E3C},
{0x3F4E,    0x3E3C},
{0x3F50,    0x380B},
{0x3F50,    0x380B},
{0x31E0,    0x000F},
{0x3324,    0x001C},

{0x3064,    0x1802},    //SMIA_TEST
{0x301A,    0x205C},    //streaming on
};
#endif


static I2C_ARRAY gain_reg[] = {            // again = power(2, coarse_gain)*(32/(32-fine_gain))*conversion gain
                {0x3060, 0x000B},            // again: coarse:[6:4],fine:[3:0]
                {0x305E, 0x0080},            // dgain: xxxx.yyyyyyy
                {0x3100, 0x0000},            // HCG: bit2 2.7x
                {0x3202, 0x0080},            //noise filter
                {0x3206, 0x0B08},            //noise filter
                {0x3208, 0x1E13},            //noise filter
                };

static I2C_ARRAY expo_reg[] = {
                        {0x3012, 0x0416},            // COARSE_INTEGRATION_TIME
                };

static I2C_ARRAY vts_reg[] = {
                       {0x300A, 0x0465},            // FRAME_LENGTH_LINES
                };

static I2C_ARRAY mirror_reg[] = {
                          // {0x301A, 0x10D8}/*{0x3022, 0x0001}*/, //0x3022 group hold can not use, using stop stream
                          {0x3040, 0x0000},
// {0x301A, 0x10DC}/*{0x3022, 0x0000}*/,

                };

static int pCus_poweron(ms_cus_sensor *handle)
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    SENSOR_DMSG( "[%s] ", __FUNCTION__ );


#if (SENSOR_MIPI_LANE_NUM == 2)
    sensor_if->SetIOPad(SENSOR_PAD_GROUP_SET, CUS_SENIF_BUS_MIPI, CUS_SR0_MIPI_MODE_1 );
#endif
#if (SENSOR_MIPI_LANE_NUM == 4)
    sensor_if->SetIOPad(SENSOR_PAD_GROUP_SET, CUS_SENIF_BUS_MIPI, CUS_SR0_MIPI_MODE_2);
#endif
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_216M, handle->PCLK_POLARITY);
#if (SENSOR_MIPI_LANE_NUM == 2)
    sensor_if->SetCSI_Lane(SENSOR_PAD_GROUP_SET, 2, 1);
#endif
#if (SENSOR_MIPI_LANE_NUM == 4)
    sensor_if->SetCSI_Lane(SENSOR_PAD_GROUP_SET, 4, 1);
#endif
    sensor_if->MCLK(SENSOR_PAD_GROUP_SET, 1, handle->mclk);
    //  sensor_if->SetCSI_LongPacketType(handle,0xff00000000);

    SENSOR_DMSG( "[%s] reset low\n", __FUNCTION__ );
    sensor_if->Reset(SENSOR_PAD_GROUP_SET, handle->reset_POLARITY );
    MsSleep(RTK_MS_TO_TICK(500));//usleep( 500 );
    SENSOR_DMSG( "[%s] power low\n", __FUNCTION__ );
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, handle->pwdn_POLARITY );
    MsSleep(RTK_MS_TO_TICK(500));//usleep( 500 );
    ///////////////////

    // power -> high, reset -> high
    SENSOR_DMSG( "[%s] power high\n", __FUNCTION__ );
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, !handle->pwdn_POLARITY );
    MsSleep(RTK_MS_TO_TICK(500));//usleep( 500 );
    SENSOR_DMSG( "[%s] reset high\n", __FUNCTION__ );
    sensor_if->Reset(SENSOR_PAD_GROUP_SET, !handle->reset_POLARITY );
    MsSleep(RTK_MS_TO_TICK(500));//usleep( 500 );

    // pure power on
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, !handle->pwdn_POLARITY );
	sensor_if->SWReset(handle->channel_num, FALSE);
    return SUCCESS;
}

static int pCus_poweroff(ms_cus_sensor *handle)
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    SENSOR_DMSG( "[%s] power low\n", __FUNCTION__ );
	sensor_if->SWReset(handle->channel_num, TRUE);
    sensor_if->PowerOff( SENSOR_PAD_GROUP_SET, handle->pwdn_POLARITY );
    MsSleep(RTK_MS_TO_TICK(500));//usleep( 1000 );
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_DISABLE, handle->PCLK_POLARITY);
    sensor_if->MCLK(0, 0, handle->mclk );
#if (SENSOR_MIPI_LANE_NUM == 2)
    sensor_if->SetCSI_Lane(SENSOR_PAD_GROUP_SET, 2, 0);
#endif
#if (SENSOR_MIPI_LANE_NUM == 4)
    sensor_if->SetCSI_Lane(SENSOR_PAD_GROUP_SET, 4, 0);
#endif
    return SUCCESS;
}

static int pCus_GetSensorID(ms_cus_sensor *handle, u32 *id)
{
    int i, n;
    int table_length = ARRAY_SIZE(Sensor_id_table);
    I2C_ARRAY id_from_sensor[ARRAY_SIZE(Sensor_id_table)];

    for(n = 0; n < table_length; ++n)
    {
        id_from_sensor[n].reg = Sensor_id_table[n].reg;
        id_from_sensor[n].data = 0;
    }

    *id = 0;
    for(n = 0; n < 4; ++n)            //retry , until I2C success
    {
        if(n > 2)
            return FAIL;

        if( SensorRegArrayR((I2C_ARRAY*)id_from_sensor,table_length) == SUCCESS)            //read sensor ID from I2C
        {
            //convert sensor id to u32 format
            for( i = 0; i < table_length; ++i )
            {
                *id = id_from_sensor[i].data;
                SENSOR_DMSG("[%s] %s read id[%d], get 0x%x\n", __FUNCTION__, handle->model_id, i, ( int )*id);

                if( id_from_sensor[i].data != Sensor_id_table[i].data )
                {
                    SENSOR_EMSG("[%s] %s,get 0x%x, error id!\n", __FUNCTION__, handle->model_id, id_from_sensor[i].data);
                    return FAIL;
                }
            }
            break;
        }
        else
            MsSleep(RTK_MS_TO_TICK(10));//usleep(1*1000);
    }

    SENSOR_IMSG("[%s] %s get sensor id:0x%x, SUCCESS!\n", __FUNCTION__, handle->model_id, ( int )*id);
    return SUCCESS;

}

static int pCus_SetPatternMode(ms_cus_sensor *handle, u32 mode)
{
    SENSOR_DMSG("\n\n[%s], mode=%d \n", __FUNCTION__, mode);

    return SUCCESS;
}

#if 1//defined(__MV5_FPGA__)
static int pCus_I2CWrite(ms_cus_sensor *handle, unsigned short usreg, unsigned short usval)
{
    unsigned short sen_data;

    SensorReg_Write(usreg, usval);
    SensorReg_Read(usreg, &sen_data);
    UartSendTrace("ar0239 reg: 0x%x, data: 0x%x, read: 0x%x.\n", usreg, usval, sen_data);

    return SUCCESS;
}

static int pCus_I2CRead(ms_cus_sensor *handle, unsigned short usreg, unsigned short* pusval)
{
    unsigned short usread_data;

    SensorReg_Read(usreg, &usread_data);
    *pusval = usread_data;
    UartSendTrace("ar0239 reg: 0x%x, data: 0x%x\n", usreg, usread_data);

    return SUCCESS;
}
#endif

static int pCus_init(ms_cus_sensor *handle)
{
    int i,cnt=0;
#if 1//defined(__MV5_FPGA__IMX323__)
    unsigned short sen_data;
#endif
    ISensorIfAPI *sensor_if = &(handle->sensor_if_api);

    sensor_if->PCLK( CUS_SNR_PCLK_SR_PAD);

#if (SENSOR_MIPI_LANE_NUM == 2)
    UartSendTrace("\n===== ar0239 Mipi2Lane12Bit_FHD30Fps init. =====\n");
    for(i = 0; i < ARRAY_SIZE(SensorInitTable_Mipi2Lane12Bit_FHD30Fps); i++)
    {
        if(SensorInitTable_Mipi2Lane12Bit_FHD30Fps[i].reg == 0xffff)
        {
            MsSleep(RTK_MS_TO_TICK(10));//usleep(1000*Sensor_init_table[i].data);
        }
        else
        {
            cnt = 0;
            while(SensorReg_Write(SensorInitTable_Mipi2Lane12Bit_FHD30Fps[i].reg,SensorInitTable_Mipi2Lane12Bit_FHD30Fps[i].data) != SUCCESS)
            {
                cnt++;
                SENSOR_DMSG("[%s] set Sensor_init_table retry : %d...\n",__FUNCTION__,cnt);
                if(cnt>=10)
                {
                    SENSOR_EMSG("[%s:%d] retry FAIL!!\n", __FUNCTION__, __LINE__);
                    return FAIL;
                }
                MsSleep(RTK_MS_TO_TICK(1));//usleep(10*1000);
            }
#if 1
            SensorReg_Read(SensorInitTable_Mipi2Lane12Bit_FHD30Fps[i].reg, &sen_data);
            UartSendTrace("ar0239 reg: 0x%x, data: 0x%x, read: 0x%x.\n",SensorInitTable_Mipi2Lane12Bit_FHD30Fps[i].reg, SensorInitTable_Mipi2Lane12Bit_FHD30Fps[i].data, sen_data);
#endif
        }
    }
#endif //SENSOR_MIPI_LANE_NUM == 2

#if (SENSOR_MIPI_LANE_NUM == 4)
#if (Preview_MAX_FPS == 30)
    UartSendTrace("\n===== ar0239 Mipi4Lane12Bit_FHD30Fps init. =====\n");
    for(i = 0; i < ARRAY_SIZE(SensorInitTable_Mipi4Lane12Bit_FHD30Fps); i++)
    {
        if(SensorInitTable_Mipi4Lane12Bit_FHD30Fps[i].reg == 0xffff)
        {
            MsSleep(RTK_MS_TO_TICK(10));//usleep(1000*Sensor_init_table[i].data);
        }
        else
        {
            cnt = 0;
            while(SensorReg_Write(SensorInitTable_Mipi4Lane12Bit_FHD30Fps[i].reg,SensorInitTable_Mipi4Lane12Bit_FHD30Fps[i].data) != SUCCESS)
            {
                cnt++;
                SENSOR_DMSG("[%s] set Sensor_init_table retry : %d...\n",__FUNCTION__,cnt);
                if(cnt>=10)
                {
                    SENSOR_EMSG("[%s:%d] retry FAIL!!\n", __FUNCTION__, __LINE__);
                    return FAIL;
                }
                MsSleep(RTK_MS_TO_TICK(1));//usleep(10*1000);
            }
#if 1
            SensorReg_Read(SensorInitTable_Mipi4Lane12Bit_FHD30Fps[i].reg, &sen_data);
            UartSendTrace("ar0239 reg: 0x%x, data: 0x%x, read: 0x%x.\n",SensorInitTable_Mipi4Lane12Bit_FHD30Fps[i].reg, SensorInitTable_Mipi4Lane12Bit_FHD30Fps[i].data, sen_data);
#endif
        }
    }
#endif   //Preview_MAX_FPS == 30

#if (Preview_MAX_FPS == 60)
    UartSendTrace("\n===== ar0239 Mipi4Lane12Bit_FHD60Fps init. =====\n");
    for(i = 0; i < ARRAY_SIZE(SensorInitTable_Mipi4Lane12Bit_FHD60Fps); i++)
    {
        if(SensorInitTable_Mipi4Lane12Bit_FHD60Fps[i].reg == 0xffff)
        {
            MsSleep(RTK_MS_TO_TICK(10));//usleep(1000*Sensor_init_table[i].data);
        }
        else
        {
            cnt = 0;
            while(SensorReg_Write(SensorInitTable_Mipi4Lane12Bit_FHD60Fps[i].reg,SensorInitTable_Mipi4Lane12Bit_FHD60Fps[i].data) != SUCCESS)
            {
                cnt++;
                SENSOR_DMSG("[%s] set Sensor_init_table retry : %d...\n",__FUNCTION__,cnt);
                if(cnt>=10)
                {
                    SENSOR_EMSG("[%s:%d] retry FAIL!!\n", __FUNCTION__, __LINE__);
                    return FAIL;
                }
                MsSleep(RTK_MS_TO_TICK(1));//usleep(10*1000);
            }
#if 1
            SensorReg_Read(SensorInitTable_Mipi4Lane12Bit_FHD60Fps[i].reg, &sen_data);
            UartSendTrace("ar0239 reg: 0x%x, data: 0x%x, read: 0x%x.\n",SensorInitTable_Mipi4Lane12Bit_FHD60Fps[i].reg, SensorInitTable_Mipi4Lane12Bit_FHD60Fps[i].data, sen_data);
#endif
        }
    }
#endif   //Preview_MAX_FPS == 60
#endif   //SENSOR_MIPI_LANE_NUM == 4

    return SUCCESS;
}

static int pCus_GetVideoResNum( ms_cus_sensor *handle, u32 *ulres_num)
{
    *ulres_num = handle->video_res_supported.num_res;
    return SUCCESS;
}

static int pCus_GetVideoRes(ms_cus_sensor *handle, cus_camsensor_res **res)
{
    *res = &handle->video_res_supported.res[handle->video_res_supported.ulcur_res];
    return SUCCESS;
}

static int pCus_SetVideoRes(ms_cus_sensor *handle, u32 res)
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    handle->video_res_supported.ulcur_res = 0; //TBD

    //sensor_if->WaitVEnd(50);
    return SUCCESS;
}

static int pCus_GetOrien(ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT *orit)
{
    short sen_data;

    sen_data = mirror_reg[0].data;
    SENSOR_DMSG("mirror:%x\r\n", sen_data);
    switch(sen_data & 0xc000)
    {
        case 0x0000:
            *orit = CUS_ORIT_M0F0;
            break;
        case 0x4000:
            *orit = CUS_ORIT_M1F0;
            break;
        case 0x8000:
            *orit = CUS_ORIT_M0F1;
            break;
        case 0xC000:
            *orit = CUS_ORIT_M1F1;
            break;
    }

    return SUCCESS;
}

static int pCus_SetOrien(ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT orit)
{
#if 0 //TODO
    short index = 0;
    ar0239_params *params = (ar0239_params *)handle->private_data;

    switch(orit)
    {
        case CUS_ORIT_M0F0:
            index = 0;
            break;
        case CUS_ORIT_M1F0:
            index = 0x4000;
            break;
        case CUS_ORIT_M0F1:
            index = 0x8000;
            break;
        case CUS_ORIT_M1F1:
            index = 0xC000;
            break;
    }
    SENSOR_DMSG("pCus_SetOrien:%x\r\n", index);
    if(index != mirror_reg[0].data)
    {
        mirror_reg[0].data = index;
        params->orient_dirty = true;
    }

#endif
    return SUCCESS;
}

static int pCus_GetFPS(ms_cus_sensor *handle)
{
    ar0239_params *params = (ar0239_params *)handle->private_data;

    return params->expo.fps;
}

static int pCus_SetFPS(ms_cus_sensor *handle, u32 fps)
{
    ar0239_params *params = (ar0239_params *)handle->private_data;
    SENSOR_DMSG("\n\n[%s], fps=%d\n", __FUNCTION__, fps);
    if(fps >= 5 && fps <= 30)
    {            //1 based
        params->expo.fps = fps;
        params->expo.vts = (vts_30fps * 30) / fps;
        vts_reg[0].data = params->expo.vts;
        return SensorRegArrayW((I2C_ARRAY* )vts_reg, sizeof(vts_reg) / sizeof(I2C_ARRAY));
    }
    else if(fps >= 5000 && fps <= 30000)
    {            //1000 based
        params->expo.fps = fps;
        params->expo.vts = (vts_30fps * 30000) / fps;
        vts_reg[0].data = params->expo.vts;
        return SensorRegArrayW((I2C_ARRAY* )vts_reg, sizeof(vts_reg) / sizeof(I2C_ARRAY));
    }
    else
    {
        SENSOR_DMSG("[%s] FPS %d out of range.\n", fps, __FUNCTION__);
        return FAIL;
    }
}

static int pCus_GetSensorCap(ms_cus_sensor *handle, CUS_CAMSENSOR_CAP *cap)
{
    if(cap)
        memcpy(cap, &sensor_cap, sizeof(CUS_CAMSENSOR_CAP));
    else
        return FAIL;
    return SUCCESS;
}

static int pCus_AEStatusNotify(ms_cus_sensor *handle, CUS_CAMSENSOR_AE_STATUS_NOTIFY status)
{
    ar0239_params *params = (ar0239_params *)handle->private_data;

    switch(status)
    {
        case CUS_FRAME_INACTIVE:
#if 0 //TODO
            if(params->orient_dirty)
            {
                SensorRegArrayW((I2C_ARRAY* )mirror_reg, sizeof(mirror_reg) / sizeof(I2C_ARRAY));
                params->orient_dirty = false;
            }
#endif
            break;
        case CUS_FRAME_ACTIVE:
#if 0
            if(params->reg_dirty)
            {
                SensorRegArrayW((I2C_ARRAY* )expo_reg, sizeof(expo_reg) / sizeof(I2C_ARRAY));
                SensorRegArrayW((I2C_ARRAY* )gain_reg, sizeof(gain_reg) / sizeof(I2C_ARRAY));
                SensorRegArrayW((I2C_ARRAY* )vts_reg, sizeof(vts_reg) / sizeof(I2C_ARRAY));
                params->reg_dirty = false;
            }
#endif
            break;
        default:
            break;
    }
    return SUCCESS;
}

static int pCus_GetAEUSecs(ms_cus_sensor *handle, u32 *us)
{
    int rc = 0;
    u32 lines = 0;
    rc = SensorRegArrayR((I2C_ARRAY* )expo_reg, ARRAY_SIZE(expo_reg));
    if(SUCCESS == rc)
    {
        lines = expo_reg[0].data;
        *us = lines * Preview_line_period / 1000;
    }
    SENSOR_DMSG("[%s] sensor expo lines/us %d, %dus\n", __FUNCTION__, lines, *us);
    return rc;
}

static int pCus_SetAEUSecs(ms_cus_sensor *handle, u32 us)
{
    u32 lines = 0, vts = 0;
    ar0239_params *params = (ar0239_params *)handle->private_data;


    lines = (1000 * us) / Preview_line_period;
    if(lines < 1)
        lines = 1;
    if(lines > params->expo.vts - 1)
    {
        vts = lines + 1;
    }
    else
        vts = params->expo.vts;

    expo_reg[0].data = lines;
    vts_reg[0].data = vts;

    SENSOR_DMSG("[%s] us %ld, lines %ld, vts %ld\n", __FUNCTION__, us, lines, params->expo.vts);
    params->reg_dirty = true;            //reg need to update
    return SUCCESS;
}

// Gain: 1x = 1024
static int pCus_GetAEGain(ms_cus_sensor *handle, u32* gain)
{
    int rc = SUCCESS;
    int i, tmp, coarse_gain, dgain;
    float fine_gain, hcg;

//  rc = SensorRegArrayR((I2C_ARRAY*)gain_reg, ARRAY_SIZE(gain_reg));
    if(SUCCESS == rc)
    {
        tmp = (gain_reg[0].data & 0x70) >> 4;
        coarse_gain = 1;
        for(i = 0; i < tmp; i++)
            coarse_gain = 2 * coarse_gain;

        tmp = gain_reg[0].data & 0x0F;
        fine_gain = 32.0 / (32 - tmp);

        dgain = gain_reg[2].data & 0x3ff;
        if(gain_reg[2].data & 4)
        {
            hcg = 2.7;
        }
        else
        {
            hcg = 1;
        }
        *gain = (coarse_gain * fine_gain * dgain * hcg * 1024) / 128;            // 128 for dgain xxxx.yyyyyyy
    }

//  SENSOR_DMSG("[%s] gain/reg = 0x%x/0x%x\n", __FUNCTION__, *gain, temp_gain);
    return rc;
}
#if 1
// again = power(2, coarse_gain)*(32/(32-fine_gain))*conversion gain
// fine_gain = 32 - ( (power(2, coarse_gain)*conversion_gain*32) / again )
static int pCus_SetAEGain(ms_cus_sensor *handle, u32 gain)
{
#define MAX_A_GAIN (16*1024*2.7)
    int coarse_gain, fine_gain, conversion_gain;
    u8 coarse_reg = 0;
    ar0239_params *params = (ar0239_params *)handle->private_data;
    params->expo.final_gain = gain;
    u32 again = 0;
    u32 dgain = 0;
    u32 input_gain = 0;
    bool hcg = 0;

    input_gain = gain;


    if(gain < SENSOR_MIN_GAIN/*1024*1.52*/)
        gain = SENSOR_MIN_GAIN;/*1024*1.52*/
    else if(gain >= SENSOR_MAX_GAIN)
        gain = SENSOR_MAX_GAIN;

    if(gain > 2.7 * 1024)
    {            // 2.7x must use HCG!
        hcg = 1;
        gain_reg[2].data |= 4;
        gain = gain / 2.7;
        conversion_gain = 100 * 2.7;
        gain_reg[3].data = 0x00B0;            //0x3202 , noise filter
        gain_reg[4].data = 0x1C0E;            //0x3206, noise filter
        gain_reg[5].data = 0x4E39;            //0x3208, noise filter
    }
    else
    {
        hcg = 0;
        gain_reg[2].data &= 0xfffb;
        conversion_gain = 100;
        gain_reg[3].data = 0x0080;            //0x3202, noise filter
        gain_reg[4].data = 0x0B08;            //0x3206, noise filter
        gain_reg[5].data = 0x1E13;            //0x3208, noise filter
    }

    if(gain >= 16 * 1024)
    {
        coarse_gain = 16;
        coarse_reg = 0x4;
    }
    else if(gain >= 8 * 1024)
    {
        coarse_gain = 8;
        coarse_reg = 0x3;
    }
    else if(gain >= 4 * 1024)
    {
        coarse_gain = 4;
        coarse_reg = 0x2;
    }
    else if(gain >= 2 * 1024)
    {
        coarse_gain = 2;
        coarse_reg = 0x1;
    }
    else
    {
        coarse_gain = 1;
        coarse_reg = 0x0;
    }

    if(input_gain <= 44237)            //44237 = 2^4 * 2.7 * 1024 Adjust A-gain when < 43.2x
    {
        fine_gain = 32 - ((1024 * coarse_gain * 32 + 512) / (gain > MAX_A_GAIN ? MAX_A_GAIN:gain));

        if(hcg == 1 && (coarse_gain >= 1) && (fine_gain & 0x01 == 1))
        {            //fine gain one step become 2x when coarse_gain >=1 reference to excel gain table
            fine_gain &= 0xFFFFFFFE;
        }

        gain_reg[0].data = (coarse_reg << 4) | fine_gain;

        again = /*(float)*/(32 * coarse_gain * conversion_gain) / (32 - fine_gain) * 100;

        dgain = input_gain * 1000 / again * 128;            //use dgain compensate again linearity

        if(dgain < 13300)
            dgain = 13300;

        gain_reg[1].data = dgain / 100;

        //printf("~~~input_gain : %d again:%d again_next:%d dgain_c:%d\n",input_gain,again,again_next,dgain);
    }
    else if(input_gain > 44237)
    {            //Adjust D-gain when > 43.2x

        gain_reg[0].data = 0x40;
        dgain = /*(float)*/(input_gain * 100) / 44237;

        dgain *= 128;

        if(dgain < 13300)
            dgain = 13300;

        gain_reg[1].data = dgain / 100;
    }
    //printf("[%s] TotalGain=%d(%dX) ,A-gain reg=0x%x , D-gain reg=%d\n", __FUNCTION__,input_gain,input_gain/1024,gain_reg[0].data ,gain_reg[1].data);
    params->reg_dirty = true;            //reg need to update
    return SUCCESS;
}

#endif

static int pCus_GetAEMinMaxUSecs(ms_cus_sensor *handle, u32 *min, u32 *max)
{
    *min = 150;
    *max = 33332; // <- max shutter (30fps: 33332, 60fps:16666)
    return SUCCESS;
}

static int pCus_GetAEMinMaxGain(ms_cus_sensor *handle, u32 *min, u32 *max)
{
    *min = SENSOR_MIN_GAIN;            //1024*1.52;
    *max = SENSOR_MAX_GAIN;

    return SUCCESS;
}

static int pCus_GetDGainRemainder(ms_cus_sensor *handle, u32 *dgain_remainder)
{
    *dgain_remainder = handle->dgain_remainder;

    return SUCCESS;
}

static int pCus_setCaliData_gain_linearity(ms_cus_sensor* handle, CUS_GAIN_GAP_ARRAY* pArray, u32 num)
{
    SENSOR_DMSG("[%s]%d, %d, %d, %d\n", __FUNCTION__, num, pArray[0].gain, pArray[1].gain, pArray[num-1].offset);

    return SUCCESS;
}

static int AR0239_GetShutterInfo(struct __ms_cus_sensor* handle, CUS_SHUTTER_INFO *info)
{
    info->max = 1000000000 / 12;
    info->min = Preview_line_period * 5;
    info->step = Preview_line_period;
    return SUCCESS;
}

int ar0239_MIPI_cus_camsensor_init_handle(ms_cus_sensor* drv_handle)
{
    ms_cus_sensor *handle = drv_handle;
#if defined(__RTK_OS__)
    CamOsRet_e                  eCamOsRet = CAM_OS_OK;
    void*                       pvBufVirt = NULL;
    u64                 u64BufPhy = 0;
    u64                 u64BufMiu = 0;
    u8                   str[20];
#endif
    if(!handle)
    {
        SENSOR_DMSG("[%s] not enough memory!\n", __FUNCTION__);
        return FAIL;
    }
    SENSOR_DMSG("[%s]"\n, __FUNCTION__);
#if defined(__RTK_OS__)
    sprintf(str, "AR0239linear");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(ar0239_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (ar0239_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(ar0239_params));
#else
    handle->private_data = calloc(1, sizeof(ar0239_params));
#endif
    ar0239_params *params = (ar0239_params *)handle->private_data;

    sprintf(handle->model_id, SENSOR_MODEL_ID);
    handle->isp_type = SENSOR_ISP_TYPE;            //ISP_SOC;
    handle->sif_bus = SENSOR_IFBUS_TYPE;            //CUS_SENIF_BUS_MIPI;
    handle->data_prec = SENSOR_DATAPREC;            //CUS_DATAPRECISION_8;
    handle->data_mode = SENSOR_DATAMODE;
    handle->bayer_id = SENSOR_BAYERID;            //CUS_BAYER_GB;
    handle->orient = SENSOR_ORIT;            //CUS_ORIT_M1F1;
    handle->interface_attr.attr_mipi.mipi_lane_num = SENSOR_MIPI_LANE_NUM;
    handle->interface_attr.attr_mipi.mipi_data_format = CUS_SEN_INPUT_FORMAT_RGB; // RGB pattern.
    handle->interface_attr.attr_mipi.mipi_yuv_order = 0; //don't care in RGB pattern.
    handle->interface_attr.attr_mipi.mipi_sampling_delay = SENSOR_MIPI_DELAY;
    handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_NONE;
    handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 0;

    handle->video_res_supported.num_res = 1;
    handle->video_res_supported.ulcur_res = 0; //default resolution index is 0.
    handle->video_res_supported.res[0].width = Preview_WIDTH;
    handle->video_res_supported.res[0].height = Preview_HEIGHT;
    handle->video_res_supported.res[0].max_fps = Preview_MAX_FPS;
    handle->video_res_supported.res[0].min_fps = Preview_MIN_FPS;
    handle->video_res_supported.res[0].crop_start_x= Preview_CROP_START_X;
    handle->video_res_supported.res[0].crop_start_y= Preview_CROP_START_Y;
    handle->video_res_supported.res[0].nOutputWidth= 1928;
    handle->video_res_supported.res[0].nOutputHeight= 1088;

    handle->i2c_cfg.mode                = I2C_NORMAL_MODE;            //old OVT I2C protocol=>I2C_LEGACY_MODE
    handle->i2c_cfg.fmt                 = SENSOR_I2C_FMT;
    handle->i2c_cfg.address             = SENSOR_I2C_ADDR;
    handle->i2c_cfg.speed               = SENSOR_I2C_SPEED;     //200000;
    handle->i2c_cfg.nChannel            = SENSOR_I2C_CHANNEL;   //Channel 1
    handle->i2c_cfg.nPadNum             = SENSOR_I2C_PAD_MODE;  //pad mode 2

    handle->mclk = Preview_MCLK_SPEED;

    handle->pwdn_POLARITY = SENSOR_PWDN_POL;
    handle->reset_POLARITY = SENSOR_RST_POL;
    //handle->VSYNC_POLARITY = SENSOR_VSYNC_POL;
    //handle->HSYNC_POLARITY = SENSOR_HSYNC_POL;
    //handle->PCLK_POLARITY = SENSOR_PCLK_POL;

    handle->ae_gain_delay = SENSOR_GAIN_DELAY_FRAME_COUNT;
    handle->ae_shutter_delay = SENSOR_SHUTTER_DELAY_FRAME_COUNT;

    handle->sat_mingain = SENSOR_MIN_GAIN;
    handle->dgain_remainder = 0;
    handle->pCus_sensor_release = ar0239_MIPI_cus_camsensor_release_handle;
    handle->pCus_sensor_init = pCus_init;
    handle->pCus_sensor_poweron = pCus_poweron;
    handle->pCus_sensor_poweroff = pCus_poweroff;

    handle->pCus_sensor_GetSensorID = pCus_GetSensorID;
    handle->pCus_sensor_GetVideoResNum = pCus_GetVideoResNum;
    handle->pCus_sensor_GetVideoRes = pCus_GetVideoRes;
    handle->pCus_sensor_SetVideoRes = pCus_SetVideoRes;
    handle->pCus_sensor_GetOrien = pCus_GetOrien;
    handle->pCus_sensor_SetOrien = pCus_SetOrien;
    handle->pCus_sensor_GetFPS = pCus_GetFPS;
    handle->pCus_sensor_SetFPS = pCus_SetFPS;
    handle->pCus_sensor_GetSensorCap = pCus_GetSensorCap;
    handle->pCus_sensor_SetPatternMode = pCus_SetPatternMode;

    handle->pCus_sensor_AEStatusNotify = pCus_AEStatusNotify;
    handle->pCus_sensor_GetAEUSecs = pCus_GetAEUSecs;
    handle->pCus_sensor_SetAEUSecs = pCus_SetAEUSecs;
    handle->pCus_sensor_GetAEGain = pCus_GetAEGain;
    handle->pCus_sensor_SetAEGain_cal = pCus_SetAEGain;            //pCus_SetAEGain_cal;
    handle->pCus_sensor_SetAEGain = pCus_SetAEGain;

    handle->pCus_sensor_GetAEMinMaxGain = pCus_GetAEMinMaxGain;
    handle->pCus_sensor_GetAEMinMaxUSecs = pCus_GetAEMinMaxUSecs;
    handle->pCus_sensor_GetDGainRemainder = pCus_GetDGainRemainder;
    handle->pCus_sensor_GetShutterInfo = AR0239_GetShutterInfo;
    handle->pCus_sensor_setCaliData_gain_linearity = pCus_setCaliData_gain_linearity;
#if 1//defined(__MV5_FPGA__)
    handle->pCus_sensor_I2CWrite = pCus_I2CWrite; //Andy Liu
    handle->pCus_sensor_I2CRead = pCus_I2CRead; //Andy Liu
#endif
    params->expo.vts = vts_30fps;
    params->expo.fps = 30;
    params->reg_dirty = false;

    handle->snr_pad_group = SENSOR_PAD_GROUP_SET;

    handle->channel_num = SENSOR_CHANNEL_NUM;
    handle->channel_mode = SENSOR_CHANNEL_MODE;


    return SUCCESS;
}

int ar0239_MIPI_cus_camsensor_release_handle(ms_cus_sensor *handle)
{
#if defined(__RTK_OS__)
    CamOsRet_e                  eCamOsRet = CAM_OS_OK;
#endif

    if (handle && handle->private_data)
    {
        SENSOR_IMSG("[%s] release handle 0x%x, private data %x\n",__FUNCTION__,(int)handle,(int)handle->private_data);
#if defined(__RTK_OS__)
        eCamOsRet = CamOsDirectMemRelease((void*)handle->private_data, sizeof(ar0239_params));
        if (eCamOsRet != CAM_OS_OK) {
            handle->private_data = NULL;
            UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
            return FAIL;
        }

#else
        free( handle->private_data );
#endif

        handle->private_data = NULL;
    }
    return SUCCESS;
}

#if defined(__RTK_OS__)
struct SensorMapTable_t gsensor_map_ar0239 = {
    SENSOR_CHANNEL_NUM,
    ar0239_MIPI_cus_camsensor_init_handle,
    ar0239_MIPI_cus_camsensor_release_handle
};

int AR0239_Module_Init(void)
{
    cameraSensorRegister(&gsensor_map_ar0239);

    return 0;
}

void AR0239_Module_Exit(void)
{
    cameraSensorUnRegister(&gsensor_map_ar0239);
}

#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(AR0239_Module_Init);
//ait_module_exit(AR0239_Module_Exit);
#endif //#if defined(__RTK_OS__)

#endif //#if defined(BIND_SENSOR_AR0239) && (BIND_SENSOR_AR0239 == 1)
