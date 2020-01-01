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
#if (SENSOR0 == OV2710)
#define BIND_SENSOR_OV2710 (1)
#endif
#endif //#if defined(__RTK_OS__)

#if (defined(BIND_SENSOR_OV2710) && (BIND_SENSOR_OV2710 == 1) || defined(BIND_SENSOR_OV2710_2ND) && (BIND_SENSOR_OV2710_2ND == 1))

#define SENSOR_PAD_GROUP_SET CUS_SENSOR_PAD_GROUP_A
#define SENSOR_CHANNEL_NUM (0)
#define SENSOR_CHANNEL_MODE_LINEAR CUS_SENSOR_CHANNEL_MODE_REALTIME_NORMAL

//============================================
//MIPI config begin.
#define SENSOR_MIPI_LANE_NUM (1)
#define SENSOR_MIPI_HDR_MODE (0) //0: Linear mode. 1:HDR_16b_combined_DCG. 2:HDR_VS_2x12b_DCG_HCG
//MIPI config end.
//============================================

#define RES_IDX_1920x1080_30P       (0)     // mode 4,  1920*1080 30P       // Video (16:9)
#define RES_IDX_1280x720_60P        (1)     // mode 9,  1280*720  60P       // Video (16:9)

#define SENSOR_MODEL_ID     "OV2710_MIPI"
#define SENSOR_ISP_TYPE     ISP_EXT                   //ISP_EXT, ISP_SOC
#define SENSOR_IFBUS_TYPE   CUS_SENIF_BUS_MIPI      //CFG //CUS_SENIF_BUS_PARL, CUS_SENIF_BUS_MIPI
#define SENSOR_MIPI_HSYNC_MODE PACKET_HEADER_EDGE1
#define SENSOR_MIPI_DELAY   0x1212                  //CFG

#define SENSOR_DATAPREC     CUS_DATAPRECISION_10
#define SENSOR_DATAMODE     CUS_SEN_10TO12_9098     //CFG
#define SENSOR_BAYERID      CUS_BAYER_GB            //CFG //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
#define SENSOR_ORIT         CUS_ORIT_M0F0           //CUS_ORIT_M0F0, CUS_ORIT_M1F0, CUS_ORIT_M0F1, CUS_ORIT_M1F1,
#define SENSOR_MAX_GAIN     (64*1024)//65536
#define SENSOR_MIN_GAIN      (3*1024)//3072
#define SENSOR_GAIN_DELAY_FRAME_COUNT      (2)
#define SENSOR_SHUTTER_DELAY_FRAME_COUNT      (2)

#define Preview_MCLK_SPEED  CUS_CMU_CLK_12MHZ //CUS_CMU_CLK_27MHZ        //CFG //CUS_CMU_CLK_12M, CUS_CMU_CLK_16M, CUS_CMU_CLK_24M, CUS_CMU_CLK_27M
#define Preview_line_period 30250                  ////HTS/PCLK=2420 pixels/80MHZ=30.250us
#define Prv_Max_line_number 1080                    //maximum exposure line munber of sensor when preview
#define vts_30fps  1111                                 //Virt Total Size , 30.25us * 1111 =  33.6ms frame interval =30 fps
#define Preview_WIDTH       1920                    //resolution Width when preview
#define Preview_HEIGHT      1080                    //resolution Height when preview
#define Preview_MAX_FPS     30                     //fastest preview FPS
#define Preview_MIN_FPS     8                      //slowest preview FPS
#define Preview_CROP_START_X     1                      //CROP_START_X
#define Preview_CROP_START_Y     1                      //CROP_START_Y

#define Cap_Max_line_number 1080                   //maximum exposure line munber of sensor when capture

#define SENSOR_I2C_ADDR    0x6c                         //I2C slave address
#define SENSOR_I2C_SPEED    I2C_SLOWSPEED_MODE_200KHZ   //200KHz
#define SENSOR_I2C_CHANNEL  1                           //I2C Channel
#define SENSOR_I2C_PAD_MODE 2                           //Pad/Mode Number

#define SENSOR_I2C_LEGACY  I2C_NORMAL_MODE     //usally set CUS_I2C_NORMAL_MODE,  if use old OVT I2C protocol=> set CUS_I2C_LEGACY_MODE
#define SENSOR_I2C_FMT     I2C_FMT_A16D8        //CUS_I2C_FMT_A8D8, CUS_I2C_FMT_A8D16, CUS_I2C_FMT_A16D8, CUS_I2C_FMT_A16D16

#define SENSOR_PWDN_POL     CUS_CLK_POL_POS        // if PWDN pin High can makes sensor in power down, set CUS_CLK_POL_POS
#define SENSOR_RST_POL      CUS_CLK_POL_NEG//CUS_CLK_POL_NEG        // if RESET pin High can makes sensor in reset state, set CUS_CLK_POL_NEG

// VSYNC/HSYNC POL can be found in data sheet timing diagram,
// Notice: the initial setting may contain VSYNC/HSYNC POL inverse settings so that condition is different.

#define SENSOR_VSYNC_POL    CUS_CLK_POL_NEG// if VSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_HSYNC_POL    CUS_CLK_POL_POS// if HSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_PCLK_POL     CUS_CLK_POL_POS        // depend on sensor setting, sometimes need to try CUS_CLK_POL_POS or CUS_CLK_POL_NEG

#define MAX_SENSOR_GAIN_HCG_LCG     (64*11)
#define MAX_SENSOR_GAIN_VS     (64)
#define ISP_DGAIN_BASE      (0x200)
#define SENSOR_GAIN_BASE      (0x100)
//define 2nd para
#define SCD_SENSOR_MIPI_LANE_NUM (1)
#define SCD_SENSOR_PAD_GROUP_SET CUS_SENSOR_PAD_GROUP_B
#define SCD_SENSOR_PWDN_POL      CUS_CLK_POL_POS
#define SCD_SENSOR_CHANNEL_NUM   (1)
#define SCD_SENSOR_CHANNEL_MODE_LINEAR CUS_SENSOR_CHANNEL_MODE_RAW_STORE_FETCH
#define SCD_SENSOR_BAYERID      CUS_BAYER_RG
#define SCD_SENSOR_I2C_ADDR     0x6c 

#define OV2718_GET_MIN(a, b)                   ( ((a) < (b)) ? (a) : (b) )
#define OV2718_GET_MAX(a, b)                   ( ((a) > (b)) ? (a) : (b) )

//
//static  u32 ae_gain_l    = 1024;
//static  u32 ae_shutter_l = 256;
//static  u32 ae_gain_s    = 1024;
//static  u32 ae_shutter_s = 256;

static u32 HCG_AGain = 0;
static u32 HCG_DGain = 0x100;
static u32 LCG_AGain = 0;
static u32 LCG_DGain = 0x100;
static u32 VS_AGain = 0;
static u32 VS_DGain = 0x100;

static u32 new_shutter_l = 0;
static u32 new_shutter_s = 0;

static u8 HCG_switch = 0x85;

int ov2710_MIPI_cus_camsensor_release_handle( ms_cus_sensor *handle );

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
    bool reg_dirty;
    int reg_dirty_cnt;
} ov2710_params;

static I2C_ARRAY Sensor_id_table[] =
{
{0x300a, 0x27},            // {address of ID, ID },
{0x300b, 0x10},            // {address of ID, ID },
};
static I2C_ARRAY Sensor_init_table_R1C[] =            // 1920*1080_30fps_27MCLK_756MMIPI_2840*1109*30
    {
        {0x3103,0x93},
        {0x3008,0x42},
        {0xffff,0x20},

            //{0x3008,0x82},
            {0x3008,0x42},//sleep mode
            {0x3017,0x7f},    //parallel pad input
            {0x3018,0xfc},     // parallel pad input
            {0x3706,0x61},
            {0x3712,0x0c},
            {0x3630,0x6d},
            {0x3801,0xb4},
            {0x3621,0x04},
            {0x3604,0x60},
            {0x3603,0xa7},
            {0x3631,0x26},
            {0x3600,0x04},
            {0x3620,0x37},
            {0x3623,0x00},
            {0x3702,0x9e},
            {0x3703,0x5c},
            {0x3704,0x40},
            {0x370d,0x0f},
            {0x3713,0x9f},
            {0x3714,0x4c},
            {0x3710,0x9e},
            {0x3801,0xc4},
            {0x3605,0x05},
            {0x3606,0x3f},
            {0x302d,0x90},
            {0x370b,0x40},
            {0x3716,0x31},
            {0x3707,0x52},
            //HTS:Total Horz Size ,
            //{0x380c,0x09},  //HTS High byte , Skip this setting because of default value is ths same. (default=0x09)
            {0x380d,0x74},  //HTS Low byte
            {0x5181,0x20},
            {0x518f,0x00},
            {0x4301,0xff},
            {0x4303,0x00},
            {0x3a00,0x78},
            {0x300f,0x88},
            {0x3011,0x28},
            {0x3a1a,0x06},
            {0x3a18,0x00},
            {0x3a19,0x7a},
            {0x3a13,0x54},
#if 1
        //Rogers
        0x3800, 0x01,
        0x3801, 0xC4,
        0x3804, 0x07,
        0x3805, 0x88,
        0x3802, 0x00,
        0x3803, 0x0A,
        0x3806, 0x04,
        0x3807, 0x40,
        0x3808, 0x07,
        0x3809, 0x88,
        0x380a, 0x04,
        0x380b, 0x40,
        0x380c, 0x09,
        0x380d, 0x74, // 0xA4
        0x380e, 0x04,
        0x380f, 0x50,
        0x3810, 0x08,
        0x3811, 0x02,
#endif
            {0x382e,0x0f},
            {0x381a,0x1a},
            {0x401d,0x02},
            {0x5688,0x03},
            {0x5684,0x07},
            {0x5685,0xa0},
            {0x5686,0x04},
            {0x5687,0x43},
            {0x3011,0x14},//;for MCLK=12MHz, default 24MHz is 0a
            {0x300f,0x8a},
            {0x3017,0x00},
            {0x3018,0x00},
            {0x300e,0x04},
            {0x4801,0x0f},
            {0x300f,0xc3},
            {0x3a0f,0x40},
            {0x3a10,0x38},
            {0x3a1b,0x48},
            {0x3a1e,0x30},
            {0x3a11,0x90},
            {0x3a1f,0x10},
            //-----------------------------
            {0x3011 ,0x15}, //;eliminate v-line
            {0x380d ,0xec},
            {0x3703 ,0x61},
            {0x3704 ,0x44},
            {0x3800 ,0x01},
            {0x3801 ,0xd2},
            //------------------------------
            //{0x3030,0x2B}, //use external 1.5V
            {0x3503,0x37},//;off aec/agc
            {0x350b,0x00},
            {0x3500,0x00},
            {0x3501,0x10},
            {0x3502,0xA0},
            {0x5001,0x4e},//;off awb
            {0x5000,0x5F&(~0x04)&(~0x0a)},//;off lenc // off defect bit[1-3]:0
            //{0x5000,0x51},//;off lenc // off defect bit[1-3]:0
            //{0x503d,0x20}, //colorbar pattern , bit 7 to enable
            //{0x3008,0x02},//normal mode
            {0x3200,0x00}, //group 0 start address
            {0x3201,0x40}, //group 1 start address
            {0x3202,0x7F}, //group 2 start address
            {0x3203,0x7F}, //group 0 start address

            {0xffff,0x20},
            {0x3008,0x02},//normal mode

    };

/*
{
#if 1
    0x3103, 0x93, // SCCB_PWUP_DIS

    0x3008, 0x82,

    0x3017, 0x7f, // PAD_OUTPUT ENABLE 1
    0x3018, 0xfc, // PAD_OUTPUT ENABLE 2
    0x3706, 0x61, // ANALOG CONTROL
    0x3712, 0x0c, // ANALOG CONTROL
    0x3630, 0x6d, //
    #if SENSOR_ROTATE_180
    0x3621, 0x14, // [7]: 1: H-sub, [4]: 0: if 0x3818[6]=1, 1: if 0x3818[6]=0
    #else
    0x3621, 0x04, // [7]: 1: H-sub, [4]: 0: if 0x3818[6]=1, 1: if 0x3818[6]=0
    #endif
    0x3604, 0x60, //
    0x3603, 0xa7, //
    0x3631, 0x26, //
    0x3600, 0x04, //
    0x3620, 0x37, //
    0x3623, 0x00,
    0x3702, 0x9e, // ANALOG CONTROL
    0x3703, 0x74, // // HREF offset
    0x3704, 0x10, // ANALOG CONTROL
    0x370d, 0x0f,
    0x3713, 0x8b, // ANALOG CONTROL
    0x3714, 0x74,
    0x3710, 0x9e, // ANALOG CONTROL
#if 0
    //0x3800, 0x01, // HREF Horizontal Start Point High Byte [3:0]
    0x3801, 0xc4,//0x7c, // HREF Horizontal Start Point Low Byte
    //0x3802, 0x00, // HREF Vertical Start Point Low Byte
    //0x3803, 0x0a, // HREF Vertical Start Point Low Byte       ==> 0x10
#else
    0x3800, 0x01,
    0x3801, 0xC4,
    0x3804, 0x07,
    0x3805, 0x88,
    0x3802, 0x00,
    0x3803, 0x0A,
    0x3806, 0x04,
    0x3807, 0x40,
    0x3808, 0x07,
    0x3809, 0x88,
    0x380a, 0x04,
    0x380b, 0x40,
    0x380c, 0x09,
    0x380d, 0x74, // 0xA4
    0x380e, 0x04,
    0x380f, 0x50,
    0x3810, 0x08,
#endif
    0x3811, 0x02,

#if (SENSOR_ROTATE_180)
    0x3621, 0x14, // [7]: 1: H-sub, [4]: 0: if 0x3818[6]=1, 1: if 0x3818[6]=0
#else
    0x3621, 0x04, // [7]: 1: H-sub, [4]: 0: if 0x3818[6]=1, 1: if 0x3818[6]=0
#endif
    0x3622, 0x08,
#if (SENSOR_ROTATE_180)
    0x3818, 0xE0, // TIMING CONTROL 18, [6]: mirror, [5]: vertical flip, [0]: vsub2, [1]: vsub4
#else
    0x3818, 0x80,
#endif

    0x3010, 0x20, // 0x20 //LeiQin
    0x302c, 0xC0,       // driving 4x //LeiQin

    0x3605, 0x05, //
    0x3606, 0x12, //
    0x302d, 0x90,
    0x370b, 0x40, // ANALOG CONTROL
    0x3716, 0x31,


    0x5181, 0x20,
    0x518f, 0x00,
    0x4301, 0xff,
    0x4303, 0x00,
    0x3a00, 0x00, //0x38, // AEC CONTROL

    0x3a1a, 0x06, // DIFF_MAX
    0x3a18, 0x00,
    0x3a19, 0x7a,
    0x3a13, 0x54,
    0x382e, 0x0f,
    0x381a, 0x1a,//0x00,//0x3c, // TIMING TC HS MIRR ADJ        ==> 0x3c
    0x5688, 0x03,
    0x5684, 0x07,
    0x5685, 0xa0,
    0x5686, 0x04,
    0x5687, 0x43,

    //#if 0//SENSOR_IF_USING_MIPI
    // for MIPI interface
    0x3017, 0x00,
    0x3018, 0x00,
    0x300e, 0x04, // SC_MIPI_SC_CTRL 0
    0x4801, 0x0f, // MIPI CONTROL 01

    0x3a0f, 0x40,
    0x3a10, 0x38,
    0x3a1b, 0x48,
    0x3a1e, 0x30,
    0x3a11, 0x90,
    0x3a1f, 0x10,


    0x3500, 0x00, // long_exposure[19:16]
    0x3501, 0x10, // long_exposure[15:8]
    0x3502, 0x00, // long_exposure[7:0]

    0x3503, 0x07, // MANUAL CONTROL, [0]:AEC manual, 0: Auto, 1: manual
    //                 [1]:AGC manual, 0: Auto, 1: manual
    //                 [2]:VTS manual, 0: Auto, 1: manual

    0x3406, 0x01,  // manual AWB

    0x350c, 0x00, // VTS_DIFF[15:8], set to zero in manual mode
    0x350d, 0x00, // VTS_DIFF[7:0], set to zero in manual mode
    0x3c01, 0x80, // 5060HZ CONTROL 01

    0x4006, 0x00, // BLC target[9:8]
    0x4007, 0x00, // BLC target[7:0]
    0x4000, 0x01,//0x01, // BLC CONTROL 00, [0]: BLC enable
    0x401d, 0x22,//0x28, // BLC CONTROL 1D


    0x5000, 0x06,//0x02, // ISP CONTROL 00, [1]: wc_en, [2]: bc_en, [7]: lenc_en
    0x5001, 0x00, // ISP CONTROL 01 (AWB), [0]: awb_en
    //        0x5002, 0x00, // ISP CONTROL 02, [1]: vap_en
    //        0x503d, 0x00, // ISP CONTROL 3D,
    //        0x5900, 0x01, // VAP CONTROL 00, [0]: avg_en
    //        0x5901, 0x00, // VAP CONTROL 01, [3:2]: hsub_coef, [1:0]: vsub_coef

    //        0x5180, 0x00, // AWB CONTROL, [7]: debug mode, [6]: fast_awb
    #if SENSOR_ROTATE_180
    0x3818, 0xE0,
    #else
    0x3818, 0x80, // TIMING CONTROL 18, [6]: mirror, [5]: vertical flip, [0]: vsub2, [1]: vsub4
    #endif
    //#if 0//SENSOR_IF_USING_MIPI
    0x3008, 0x04, // Start streaming, [1]:
    0x300e, 0x04, // Start streaming, [1]:

    0x300f, 0x8a, // PLL CONTROL, [2]: R_DIVL 0: one lane, 1: two lanes
    //0x3011, 0x0e,//0x0c, // 14*12*4/8 => PCLK = 672/8 = 84MHz
    0x3011, 0x14,//0x0c, // 14*12*4/8 => PCLK = 672/8 = 84MHz
    //        0x3011, 0x0f, // 11*15*4 = 660MHz => PCLK = 660/10 = 66MHz
    #if 0
    0x3012, 0x02, // [2:0]: R_PREDIV, 010: divide by 2
    #else
    0x3012, 0x00, // [2:0]: R_PREDIV, 000: divide by 1
    #endif

#endif
#if 0
        0x3103, 0x03, // SCCB_PWUP_DIS

        0x3008, 0x82,

        0x3017, 0x7f, // PAD_OUTPUT ENABLE 1
        0x3018, 0xfc, // PAD_OUTPUT ENABLE 2
        0x3706, 0x61, // ANALOG CONTROL
        0x3712, 0x0c, // ANALOG CONTROL
        0x3630, 0x6d, //
        0x3621, 0x04, // [7]: 1: H-sub, [4]: 0: if 0x3818[6]=1, 1: if 0x3818[6]=0
        0x3604, 0x60, //
        0x3603, 0xa7, //
        0x3631, 0x26, //
        0x3600, 0x04, //
        0x3620, 0x37, //
        0x3623, 0x00,
        0x3702, 0x9e, // ANALOG CONTROL
        0x3703, 0x74, // // HREF offset
        0x3704, 0x10, // ANALOG CONTROL
        0x370d, 0x0f,
        0x3713, 0x8b, // ANALOG CONTROL
        0x3714, 0x74,
        0x3710, 0x9e, // ANALOG CONTROL
        0x3800, 0x01,
        0x3801, 0xC4,
        0x3804, 0x07,
        0x3805, 0x88,
        0x3802, 0x00,
        0x3803, 0x0A,
        0x3806, 0x04,
        0x3807, 0x40,
        0x3808, 0x07,
        0x3809, 0x88,
        0x380a, 0x04,
        0x380b, 0x40,
        0x380c, 0x09,
        0x380d, 0x74, // 0xA4
        0x380e, 0x04,
        0x380f, 0x50,
        0x3810, 0x08,
        0x3010, 0x20, // 0x20 //LeiQin
        0x302c, 0xC0,       // driving 4x //LeiQin

        0x3605, 0x05, //
        0x3606, 0x12, //
        0x302d, 0x90,
        0x370b, 0x40, // ANALOG CONTROL
        0x3716, 0x31,


        0x5181, 0x20,
        0x518f, 0x00,
        0x4301, 0xff,
        0x4303, 0x00,
        0x3a00, 0x00, //0x38, // AEC CONTROL

        0x3a1a, 0x06, // DIFF_MAX
        0x3a18, 0x00,
        0x3a19, 0x7a,
        0x3a13, 0x54,
        0x382e, 0x0f,
        0x381a, 0x1a,//0x00,//0x3c, // TIMING TC HS MIRR ADJ        ==> 0x3c
        0x5688, 0x03,
        0x5684, 0x07,
        0x5685, 0xa0,
        0x5686, 0x04,
        0x5687, 0x43,

        //#if 0//SENSOR_IF_USING_MIPI
        0x3017, 0x00,
        0x3018, 0x00,
        0x300e, 0x04, // SC_MIPI_SC_CTRL 0
        0x4801, 0x0f, // MIPI CONTROL 01

        0x3a0f, 0x40,
        0x3a10, 0x38,
        0x3a1b, 0x48,
        0x3a1e, 0x30,
        0x3a11, 0x90,
        0x3a1f, 0x10,


        0x3500, 0x00, // long_exposure[19:16]
        0x3501, 0x10, // long_exposure[15:8]
        0x3502, 0x00, // long_exposure[7:0]

        0x3503, 0x07, // MANUAL CONTROL, [0]:AEC manual, 0: Auto, 1: manual
        //                 [1]:AGC manual, 0: Auto, 1: manual
        //                 [2]:VTS manual, 0: Auto, 1: manual

        0x3406, 0x01,  // manual AWB

        0x350c, 0x00, // VTS_DIFF[15:8], set to zero in manual mode
        0x350d, 0x00, // VTS_DIFF[7:0], set to zero in manual mode
        0x3c01, 0x80, // 5060HZ CONTROL 01

        0x4006, 0x00, // BLC target[9:8]
        0x4007, 0x00, // BLC target[7:0]
        0x4000, 0x01,//0x01, // BLC CONTROL 00, [0]: BLC enable
        0x401d, 0x22,//0x28, // BLC CONTROL 1D


        0x5000, 0x06,//0x02, // ISP CONTROL 00, [1]: wc_en, [2]: bc_en, [7]: lenc_en
        0x5001, 0x00, // ISP CONTROL 01 (AWB), [0]: awb_en
        //        0x5002, 0x00, // ISP CONTROL 02, [1]: vap_en
        //        0x503d, 0x00, // ISP CONTROL 3D,
        //        0x5900, 0x01, // VAP CONTROL 00, [0]: avg_en
        //        0x5901, 0x00, // VAP CONTROL 01, [3:2]: hsub_coef, [1:0]: vsub_coef

        //        0x5180, 0x00, // AWB CONTROL, [7]: debug mode, [6]: fast_awb

        0x3818, 0x80, // TIMING CONTROL 18, [6]: mirror, [5]: vertical flip, [0]: vsub2, [1]: vsub4
        //#if 0//SENSOR_IF_USING_MIPI
        0x3008, 0x04, // Start streaming, [1]:
        0x300e, 0x04, // Start streaming, [1]:


        0x300f, 0x8a, // PLL CONTROL, [2]: R_DIVL 0: one lane, 1: two lanes
        //0x3011, 0x0e,//0x0c, // 14*12*4/8 => PCLK = 672/8 = 84MHz
        0x3011, 0x0e,//0x0c, // 14*12*4/8 => PCLK = 672/8 = 84MHz
        //        0x3011, 0x0f, // 11*15*4 = 660MHz => PCLK = 660/10 = 66MHz
        0x3012, 0x00, // [2:0]: R_PREDIV, 000: divide by 1
#endif

};
*/
static I2C_ARRAY PatternTbl[] =
{
{0x503d, 0x00},            //colorbar pattern , bit 0 to enable
};

static I2C_ARRAY Current_Mirror_Flip_Tbl[] =
{
{0x3818, 0x20},
};

static I2C_ARRAY gain_reg[] =
{

};

static CUS_GAIN_GAP_ARRAY gain_gap_compensate[] =
{

};
static I2C_ARRAY expo_reg[] =
{
    {0x3500, 0x00},
    {0x3501, 0x00},
    {0x3502, 0x00},
};

static I2C_ARRAY vts_reg[] =
{
    {0x380e, 0x06},    // total vertical size[11:8]
    {0x380f, 0x18},    // total vertical size[7:0]
};

static int pCus_poweron( ms_cus_sensor *handle )
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    SENSOR_DMSG( "[%s] ", __FUNCTION__ );
	if(handle->snr_pad_group == CUS_SENSOR_PAD_GROUP_A){
    	sensor_if->SetIOPad(handle->snr_pad_group, CUS_SENIF_BUS_MIPI, CUS_SR0_MIPI_MODE_2 );
	}
	if(handle->snr_pad_group == CUS_SENSOR_PAD_GROUP_B){
		sensor_if->SetIOPad(handle->snr_pad_group, CUS_SENIF_BUS_MIPI, CUS_SR1_MIPI_MODE_1 );
	}
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_216M, handle->PCLK_POLARITY);
    sensor_if->SetCSI_Lane(handle->snr_pad_group, SENSOR_MIPI_LANE_NUM, 1);
    sensor_if->MCLK(handle->snr_pad_group, 1, handle->mclk);
    //  sensor_if->SetCSI_LongPacketType(handle,0xff00000000);

    SENSOR_DMSG( "[%s] reset low\n", __FUNCTION__ );
    sensor_if->Reset(handle->snr_pad_group, handle->reset_POLARITY );
    MsSleep(RTK_MS_TO_TICK(5));//usleep( 500 );
    SENSOR_DMSG( "[%s] power low\n", __FUNCTION__ );
    sensor_if->PowerOff(handle->snr_pad_group, handle->pwdn_POLARITY );
    MsSleep(RTK_MS_TO_TICK(5));//usleep( 500 );
    ///////////////////

    // power -> high, reset -> high
    SENSOR_DMSG( "[%s] power high\n", __FUNCTION__ );
    sensor_if->PowerOff(handle->snr_pad_group, !handle->pwdn_POLARITY );
    MsSleep(RTK_MS_TO_TICK(10));//usleep( 500 );
    sensor_if->PowerOff(handle->snr_pad_group, handle->pwdn_POLARITY );
    MsSleep(RTK_MS_TO_TICK(10));
    sensor_if->PowerOff(handle->snr_pad_group, !handle->pwdn_POLARITY );
	sensor_if->SWReset(handle->channel_num, FALSE);
	MsSleep(RTK_MS_TO_TICK(10));
    SENSOR_DMSG( "[%s] reset high\n", __FUNCTION__ );
    sensor_if->Reset(handle->snr_pad_group, !handle->reset_POLARITY );
    MsSleep(RTK_MS_TO_TICK(5));//usleep( 500 );


    // pure power on
    //sensor_if->PowerOff(handle->snr_pad_group, !handle->pwdn_POLARITY );

    return SUCCESS;
}

static int pCus_poweroff( ms_cus_sensor *handle )
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    SENSOR_DMSG( "[%s] power low\n", __FUNCTION__ );
	sensor_if->SWReset(handle->channel_num, TRUE);
    sensor_if->PowerOff(handle->snr_pad_group, handle->pwdn_POLARITY );
    MsSleep(RTK_MS_TO_TICK(5));//usleep( 1000 );
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_DISABLE, handle->PCLK_POLARITY);
    sensor_if->MCLK(handle->snr_pad_group, 0, handle->mclk );
    sensor_if->SetCSI_Lane(handle->snr_pad_group, SENSOR_MIPI_LANE_NUM, 0);
    return SUCCESS;
}

static int pCus_GetSensorID( ms_cus_sensor *handle, u32 *id )
{
    int i, n;
    int table_length = ARRAY_SIZE( Sensor_id_table );
    I2C_ARRAY id_from_sensor[ARRAY_SIZE( Sensor_id_table )];

    for( n = 0; n < table_length; ++n )
    {
        id_from_sensor[n].reg = Sensor_id_table[n].reg;
        id_from_sensor[n].data = 0;
    }

    *id = 0;
    if( table_length > 8 )
        table_length = 8;

    for( n = 0; n < 4; ++n )            //retry , until I2C success
    {
        if( n > 2 )
            return FAIL;

        if( SensorRegArrayR((I2C_ARRAY*)id_from_sensor,table_length) == SUCCESS )            //read sensor ID from I2C
        {
            //convert sensor id to u32 format
            for( i = 0; i < table_length; ++i )
            {
                *id = id_from_sensor[i].data;
                SENSOR_DMSG("[%s] %s read id[%d], get 0x%x\n", __FUNCTION__, handle->model_id, i, ( int )*id);

                if( id_from_sensor[i].data != Sensor_id_table[i].data )
                {
                    SENSOR_EMSG("[%s] %s,get 0x%x, error id!\n", __FUNCTION__, handle->model_id, Sensor_id_table[i].data);
                    return FAIL;
                }
            }
            break;
        }
        else
            MsSleep(RTK_MS_TO_TICK(1));//usleep( 1*1000 );
    }

    SENSOR_IMSG("[%s] %s get sensor id:0x%x, SUCCESS!\n", __FUNCTION__, handle->model_id, ( int )*id);
    return SUCCESS;
}

static int ov2710_SetPatternMode( ms_cus_sensor *handle, u32 mode )
{
    switch( mode )
    {
        case 1:
            PatternTbl[0].data |= 0x01;            //enable
            break;
        case 0:
            PatternTbl[0].data &= 0xfe;            //disable
            break;
        default:
            PatternTbl[0].data &= 0xfe;            //disable
            break;
    }
    int i;
    for( i = 0; i < ARRAY_SIZE( PatternTbl ); i++ )
    {
        if( SensorReg_Write(PatternTbl[i].reg,PatternTbl[i].data) != SUCCESS )
        {
            return FAIL;
        }
    }
    return SUCCESS;
}

#if 1//defined(__MV5_FPGA__)
static int pCus_I2CWrite(ms_cus_sensor *handle, unsigned short usreg, unsigned short usval)
{
    unsigned short sen_data;

    SensorReg_Write(usreg, usval);
    SensorReg_Read(usreg, &sen_data);
    UartSendTrace("ov2710_MIPI reg: 0x%x, data: 0x%x, read: 0x%x.\n", usreg, usval, sen_data);

    return SUCCESS;
}

static int pCus_I2CRead(ms_cus_sensor *handle, unsigned short usreg, unsigned short* pusval)
{
    unsigned short usread_data;

    SensorReg_Read(usreg, &usread_data);
    *pusval = usread_data;
    UartSendTrace("ov2710_MIPI reg: 0x%x, data: 0x%x\n", usreg, usread_data);

    return SUCCESS;
}
#endif

static int pCus_init_1lane_linear( ms_cus_sensor *handle )
{
    int i;
    ISensorIfAPI *sensor_if = &( handle->sensor_if_api );
    short sen_data;
    sensor_if->PCLK( CUS_SNR_PCLK_MIPI_TOP );

    UartSendTrace("\n===== ov2710 1lane init. =====\n");
    //printf("[%s] OV2718 R1C version\n", __FUNCTION__);
    for( i = 0; i < ARRAY_SIZE( Sensor_init_table_R1C ); i++ )
    {
        if( Sensor_init_table_R1C[i].reg == 0xffff )
        {
            MsSleep(RTK_MS_TO_TICK(1));//usleep( 1000*Sensor_init_table_R1C[i].data );
        }
        else
        {
            if( SensorReg_Write(Sensor_init_table_R1C[i].reg,Sensor_init_table_R1C[i].data) != SUCCESS )
            {
                return FAIL;
            }
            SensorReg_Read( Sensor_init_table_R1C[i].reg, &sen_data );
            UartSendTrace("ov2710 reg: 0x%x, data: 0x%x, read: 0x%x.\n",Sensor_init_table_R1C[i].reg, Sensor_init_table_R1C[i].data, sen_data);
        }
    }

/*    UartSendTrace("\nov2710 reg pattern\n");
    for( i = 0; i < ARRAY_SIZE( PatternTbl ); i++ )
    {
        if( SensorReg_Write(PatternTbl[i].reg,PatternTbl[i].data) != SUCCESS )
        {
            return FAIL;
        }
        SensorReg_Read( PatternTbl[i].reg, &sen_data );
        UartSendTrace("ov2710 reg: 0x%x, data: 0x%x, read: 0x%x.\n",PatternTbl[i].reg, PatternTbl[i].data, sen_data);
    }

    UartSendTrace("\nov2710 reg Current_Mirror_Flip_Tbl\n");
    for( i = 0; i < ARRAY_SIZE( Current_Mirror_Flip_Tbl ); i++ )
    {
        if( SensorReg_Write(Current_Mirror_Flip_Tbl[i].reg,Current_Mirror_Flip_Tbl[i].data) != SUCCESS )
        {
            return FAIL;
        }
        SensorReg_Read( Current_Mirror_Flip_Tbl[i].reg, &sen_data );
        UartSendTrace("ov2710 reg: 0x%x, data: 0x%x, read: 0x%x.\n",Current_Mirror_Flip_Tbl[i].reg, Current_Mirror_Flip_Tbl[i].data, sen_data);

    }
*/
    return SUCCESS;
}

static int pCus_init_linear_isp_calibration( ms_cus_sensor *handle )
{
    return SUCCESS;
}

static int pCus_GetVideoResNum( ms_cus_sensor *handle, u32 *ulres_num)
{
    *ulres_num = handle->video_res_supported.num_res;
    return SUCCESS;
}

static int pCus_GetVideoRes( ms_cus_sensor *handle, cus_camsensor_res **res )
{
    *res = &handle->video_res_supported.res[handle->video_res_supported.ulcur_res];
    return SUCCESS;
}

static int pCus_SetVideoRes_linear( ms_cus_sensor *handle, u32 res )
{
    //switch(res){
        //case SENSOR_DRIVER_MODE_FULL_HD_30P_RESOLUTION:
            handle->video_res_supported.ulcur_res = RES_IDX_1920x1080_30P;
            handle->pCus_sensor_init = pCus_init_1lane_linear;
            //break;

        //default:
        //    UartSendTrace("[%s] Line:%d fail. res:%d\n",__FUNCTION__, __LINE__, res);
        //    break;
    //}

    //sensor_if->WaitVEnd( 50 );
    return SUCCESS;
}

static int pCus_GetOrien( ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT *orit )
{
    ov2710_params *params = ( ov2710_params * ) handle->private_data;
    return params->mirror_flip.cur;
}

static int pCus_SetOrien( ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT orit )
{
    ov2710_params *params = ( ov2710_params * ) handle->private_data;
    params->mirror_flip.new_setting = orit;
    //DoMirror( handle, params->mirror_flip.new_setting );
    return SUCCESS;
}

static int pCus_GetFPS( ms_cus_sensor *handle )
{
    ov2710_params *params = ( ov2710_params * ) handle->private_data;
    SENSOR_DMSG("[%s] FPS %d\n", __FUNCTION__, params->expo.fps);
    return params->expo.fps;
}

static int pCus_SetFPS( ms_cus_sensor *handle, u32 fps )
{
    ov2710_params *params = ( ov2710_params * ) handle->private_data;

    if( fps >= 10 && fps <= 30 )
    {
        params->expo.fps = fps;
        params->expo.vts = ( vts_30fps * 30 ) / fps;
        vts_reg[0].data = ( params->expo.vts >> 8 ) & 0x00ff;
        vts_reg[1].data = ( params->expo.vts >> 0 ) & 0x00ff;
        // params->reg_dirty = true;
        SENSOR_DMSG( "\n\n[%s], fps=%d, lines=%d\n", __FUNCTION__, fps, params->expo.vts );
        return SUCCESS;
    }
    else if( fps >= 10000 && fps <= 30000 )
    {
        params->expo.fps = fps;
        params->expo.vts = ( vts_30fps * 30000 ) / fps;
        vts_reg[0].data = ( params->expo.vts >> 8 ) & 0x00ff;
        vts_reg[1].data = ( params->expo.vts >> 0 ) & 0x00ff;
        // params->reg_dirty = true;
        SENSOR_DMSG( "\n\n[%s], fps=%d, lines=%d\n", __FUNCTION__, fps, params->expo.vts );
        return SUCCESS;
    }
    else
    {
        SENSOR_DMSG( "[%s] FPS %d out of range.\n", fps, __FUNCTION__ );
        return FAIL;
    }
}

static int pCus_GetSensorCap( ms_cus_sensor *handle, CUS_CAMSENSOR_CAP *cap )
{
    if( cap )
        memcpy( cap, &sensor_cap, sizeof(CUS_CAMSENSOR_CAP) );
    else
        return FAIL;
    return SUCCESS;
}

static int pCus_AEStatusNotify( ms_cus_sensor *handle, CUS_CAMSENSOR_AE_STATUS_NOTIFY status )
{
/*
    ov2710_params *params = ( ov2710_params * ) handle->private_data;
    switch(status)
    {
        case CUS_FRAME_INACTIVE:
             break;
        case CUS_FRAME_ACTIVE:
            if(params->reg_dirty)
            {
                SensorRegArrayW( ( I2C_ARRAY* )expo_reg, ARRAY_SIZE(expo_reg) );
                SensorRegArrayW( ( I2C_ARRAY* )gain_reg, ARRAY_SIZE(gain_reg) );
                SensorRegArrayW( ( I2C_ARRAY* )vts_reg, ARRAY_SIZE(vts_reg) );
                params->reg_dirty = false;
            }
            break;
        default :
             break;
    }
        */
    return SUCCESS;
}

static int pCus_GetAEUSecs( ms_cus_sensor *handle, u32 *us )
{
    int rc = 0;
    u32 lines = 0;

    lines = ( u32 ) ( expo_reg[3].data & 0xff );
    lines |= ( u32 ) ( expo_reg[2].data & 0xff ) << 8;

    *us = ( lines * Preview_line_period ) / 1000;

    // SENSOR_DMSG("[%s] sensor expo lines/us %d, %dus\n", __FUNCTION__, lines, *us);
    return rc;
}

static int pCus_SetAEUSecs( ms_cus_sensor *handle, u32 us )
{
/*
    u32 lines = 0, vts = 0;
    ov2710_params *params = ( ov2710_params * ) handle->private_data;
    lines = ( u32 ) ( ( 1000 * us ) / Preview_line_period );

    if( lines > params->expo.vts - 2 )
        vts = lines + 2;
    else
        vts = params->expo.vts;

    SENSOR_DMSG( "[%s] us %ld, lines %ld, vts %ld\n", __FUNCTION__,
                    us,
                    lines,
                    params->expo.vts
                    );

    // lines <<= 4;
    expo_reg[2].data = ( u16 ) ( ( lines >> 8 ) & 0x00ff );
    expo_reg[3].data = ( u16 ) ( ( lines >> 0 ) & 0x00ff );

    vts_reg[0].data = ( vts >> 8 ) & 0x00ff;
    vts_reg[1].data = ( vts >> 0 ) & 0x00ff;
//  SensorRegArrayW( ( I2C_ARRAY* )expo_reg, ARRAY_SIZE(expo_reg) );
//  SensorRegArrayW( ( I2C_ARRAY* )gain_reg, ARRAY_SIZE(gain_reg) );
//  SensorRegArrayW( ( I2C_ARRAY* )vts_reg, ARRAY_SIZE(vts_reg) );

    params->reg_dirty = true;
    */
    return SUCCESS;
}

// Gain: 1x = 1024
static int pCus_GetAEGain( ms_cus_sensor *handle, u32* gain )
{
    u32 again, dgain;
    u32 HCG_en;
    HCG_en = ( gain_reg[0].data & 0x40 ) ? 1 : 0;

    dgain = ( gain_reg[1].data ) << (8 + gain_reg[2].data);//dgain = ( gain_reg[1].data ) << 8 + gain_reg[2].data;
    again = ( u32 ) ( 1 << ( gain_reg[0].data & 0x03 ) );
    *gain = again * ( dgain << 2 ) * (HCG_en*19 + 2) / 2;

    SENSOR_DMSG( "[%s] again(base1)/dgain(base64)/gain(base1024) = 0x%x/0x%x/0x%x\n", __FUNCTION__, again, dgain, *gain );
    return SUCCESS;
}

static int pCus_SetAEGain_cal( ms_cus_sensor *handle, u32 gain )
{

}

static int pCus_SetAEGain( ms_cus_sensor *handle, u32 gain )
{
/*
    ov2710_params *params = ( ov2710_params * ) handle->private_data;
     u32 ae_gain_l    = SENSOR_GAIN_BASE;
     u32  ae_gain_l_tmp = SENSOR_GAIN_BASE;
     u32 s_gain_HCG;
     u32 sensor_AG = 0, sensor_DG = 0;
     u32 sensor_HCG_EN = 0;

     ae_gain_l = gain >> 2;

     //Calculate gain.
     if (ae_gain_l >= SENSOR_GAIN_BASE * MAX_SENSOR_GAIN_HCG_LCG) {
         //dgain      = ISP_DGAIN_BASE * ae_gain_l / SENSOR_GAIN_BASE / MAX_SENSOR_GAIN ;
         ae_gain_l  = SENSOR_GAIN_BASE * MAX_SENSOR_GAIN_HCG_LCG;
     }
     else {
         //dgain = ISP_DGAIN_BASE;
     }

     if(ae_gain_l > 21 * SENSOR_GAIN_BASE) {
         sensor_HCG_EN = 1;
         ae_gain_l_tmp = ae_gain_l;

         ae_gain_l_tmp =  ae_gain_l_tmp*2/21;

         s_gain_HCG = OV2718_GET_MAX( ae_gain_l_tmp , 2 * SENSOR_GAIN_BASE );
         s_gain_HCG = s_gain_HCG * 1 /2;

         // HG for HDR
         if(s_gain_HCG > (8 * SENSOR_GAIN_BASE))
         {
             sensor_AG = 3;
             sensor_DG = (s_gain_HCG >> sensor_AG)*2;
         } else if(s_gain_HCG > (4 * SENSOR_GAIN_BASE)){
             sensor_AG = 2;
             sensor_DG = (s_gain_HCG >> sensor_AG)*2;
         } else if(s_gain_HCG > (2 * SENSOR_GAIN_BASE)){
             sensor_AG = 1;
             sensor_DG = (s_gain_HCG >> sensor_AG)*2;
         }  else{
             sensor_AG = 0; //HCG mode Min AG =1x
             sensor_DG = (0x100)*2;//HCG mode Min DG =2x
         }

     }else {
         sensor_HCG_EN = 0;
         ae_gain_l_tmp = ae_gain_l;

         s_gain_HCG = OV2718_GET_MAX( ae_gain_l_tmp , 3 * SENSOR_GAIN_BASE );
         s_gain_HCG = s_gain_HCG * 2/3;

         // HG for HDR
         if(s_gain_HCG > (8 * SENSOR_GAIN_BASE))
         {
             sensor_AG = 3;
             sensor_DG = (s_gain_HCG >> sensor_AG)*3/2;
         } else if(s_gain_HCG > (4 * SENSOR_GAIN_BASE)){
             sensor_AG = 2;
             sensor_DG = (s_gain_HCG >> sensor_AG)*3/2;
         } else if(s_gain_HCG > (2 * SENSOR_GAIN_BASE)){
             sensor_AG = 1;
             sensor_DG = (s_gain_HCG >> sensor_AG)*3/2;
         }  else {
             sensor_AG = 1;  //LCG mode Min AG =2x
             sensor_DG = (0x100)*3/2; //LCG mode Min DG =1.5x
         }
     }

    gain_reg[0].data = ( u16 ) ( 0x40 * sensor_HCG_EN + (sensor_AG & 0x03) );          //high byte

    gain_reg[1].data = ( u16 ) ( sensor_DG >> 8 );            //high byte
    gain_reg[2].data = ( u16 ) ( sensor_DG & 0xff );            //low byte

    SENSOR_DMSG( "[%s] set gain/AG/HCG_H/HCG_L/LCG_H/LCG_L=%d/0x%x/0x%x/0x%x/0x%x/0x%x\n",
                    __FUNCTION__,
                    gain,
                    gain_reg[0].data,
                    gain_reg[1].data,
                    gain_reg[2].data,
                    gain_reg[3].data,
                    gain_reg[4].data );
    params->reg_dirty = true;
    */
    return SUCCESS;

}

static int pCus_GetAEMinMaxUSecs( ms_cus_sensor *handle, u32 *min, u32 *max )
{
    *min = 150;
    *max = 33332; // <- max shutter (30fps: 33332, 60fps:16666)

    return SUCCESS;
}

static int pCus_GetAEMinMaxGain( ms_cus_sensor *handle, u32 *min, u32 *max )
{
    *min = SENSOR_MIN_GAIN;            //1024*1.1*2
    *max = SENSOR_MAX_GAIN;

    return SUCCESS;
}

static int pCus_GetDGainRemainder(ms_cus_sensor *handle, u32 *dgain_remainder)
{
    *dgain_remainder = handle->dgain_remainder;

    return SUCCESS;
}

static int pCus_setCaliData_gain_linearity( ms_cus_sensor* handle, CUS_GAIN_GAP_ARRAY* pArray, u32 num )
{
    SENSOR_DMSG( "[%s]%d, %d, %d, %d\n", __FUNCTION__, num, pArray[0].gain, pArray[1].gain, pArray[num-1].offset );
    return SUCCESS;
}

static int OV2710_GetShutterInfo( struct __ms_cus_sensor* handle, CUS_SHUTTER_INFO *info )
{
    info->max = 1000000000 / 12;
    info->min = Preview_line_period;
    info->step = Preview_line_period;
    return SUCCESS;
}

int ov2710_MIPI_cus_camsensor_init_handle_linear( ms_cus_sensor* drv_handle )
{
    ms_cus_sensor *handle = drv_handle;
#if defined(__RTK_OS__)
    CamOsRet_e                  eCamOsRet = CAM_OS_OK;
    void*                       pvBufVirt = NULL;
    u64                 u64BufPhy = 0;
    u64                 u64BufMiu = 0;
    u8                   str[20];
#endif

    if( !handle )
    {
        SENSOR_DMSG( "[%s] not enough memory!\n", __FUNCTION__ );
        return FAIL;
    }
    SENSOR_DMSG( "[%s]\n", __FUNCTION__ );
#if defined(__RTK_OS__)
    sprintf(str, "OV2710linear");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(ov2710_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (ov2710_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(ov2710_params));
#else
    handle->private_data = calloc( 1, sizeof(ov2710_params) );
#endif

    ov2710_params *params = ( ov2710_params * ) handle->private_data;

    sprintf( handle->model_id, SENSOR_MODEL_ID );
    handle->isp_type = SENSOR_ISP_TYPE;
    handle->sif_bus = SENSOR_IFBUS_TYPE;
    handle->data_prec = SENSOR_DATAPREC;
    handle->data_mode = SENSOR_DATAMODE;
    handle->bayer_id = SENSOR_BAYERID;
    handle->orient = SENSOR_ORIT;
    handle->interface_attr.attr_mipi.mipi_lane_num = SENSOR_MIPI_LANE_NUM;
    handle->interface_attr.attr_mipi.mipi_data_format = CUS_SEN_INPUT_FORMAT_RGB; // RGB pattern.
    handle->interface_attr.attr_mipi.mipi_yuv_order = 0; //don't care in RGB pattern.
    handle->interface_attr.attr_mipi.mipi_hsync_mode = SENSOR_MIPI_HSYNC_MODE;
    handle->interface_attr.attr_mipi.mipi_sampling_delay = SENSOR_MIPI_DELAY;

    handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_NONE;
    handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 1; //Short frame

    handle->video_res_supported.num_res = 1;
    handle->video_res_supported.ulcur_res = 0; //default resolution index is 0.
    handle->video_res_supported.res[0].width = Preview_WIDTH;
    handle->video_res_supported.res[0].height = Preview_HEIGHT;
    handle->video_res_supported.res[0].max_fps = Preview_MAX_FPS;
    handle->video_res_supported.res[0].min_fps = Preview_MIN_FPS;
    handle->video_res_supported.res[0].crop_start_x= Preview_CROP_START_X;
    handle->video_res_supported.res[0].crop_start_y= Preview_CROP_START_Y;
    handle->video_res_supported.res[0].nOutputWidth= 1920;//Preview_WIDTH;
    handle->video_res_supported.res[0].nOutputHeight= 1080;//Preview_HEIGHT;

    handle->i2c_cfg.mode                = I2C_NORMAL_MODE;
    handle->i2c_cfg.fmt                 = SENSOR_I2C_FMT;
    handle->i2c_cfg.address             = SENSOR_I2C_ADDR;
    handle->i2c_cfg.speed               = SENSOR_I2C_SPEED;     //200000;
    handle->i2c_cfg.nChannel            = SENSOR_I2C_CHANNEL;   //Channel 1
    handle->i2c_cfg.nPadNum             = SENSOR_I2C_PAD_MODE;  //pad mode 2

    handle->mclk = Preview_MCLK_SPEED;

    handle->pwdn_POLARITY = SENSOR_PWDN_POL;
    handle->reset_POLARITY = SENSOR_RST_POL;
    handle->VSYNC_POLARITY              = SENSOR_VSYNC_POL; //CUS_CLK_POL_POS;
    handle->HSYNC_POLARITY              = SENSOR_HSYNC_POL; //CUS_CLK_POL_POS;
    handle->PCLK_POLARITY               = SENSOR_PCLK_POL;  //CUS_CLK_POL_POS);    // use '!' to clear board latch error

    handle->ae_gain_delay = SENSOR_GAIN_DELAY_FRAME_COUNT;            //0;//1;
    handle->ae_shutter_delay = SENSOR_SHUTTER_DELAY_FRAME_COUNT;            //1;//2;

    handle->sat_mingain = SENSOR_MIN_GAIN;
    handle->dgain_remainder = 0;
    handle->pCus_sensor_release = ov2710_MIPI_cus_camsensor_release_handle;

    handle->pCus_sensor_init = pCus_init_1lane_linear;

    handle->pCus_sensor_poweron = pCus_poweron;
    handle->pCus_sensor_poweroff = pCus_poweroff;

    handle->pCus_sensor_GetSensorID = pCus_GetSensorID;
    handle->pCus_sensor_GetVideoResNum = pCus_GetVideoResNum;
    handle->pCus_sensor_GetVideoRes = pCus_GetVideoRes;
    handle->pCus_sensor_SetVideoRes = pCus_SetVideoRes_linear;
    handle->pCus_sensor_GetOrien = pCus_GetOrien;
    handle->pCus_sensor_SetOrien = pCus_SetOrien;
    handle->pCus_sensor_GetFPS = pCus_GetFPS;
    handle->pCus_sensor_SetFPS = pCus_SetFPS;
    handle->pCus_sensor_GetSensorCap = pCus_GetSensorCap;
    handle->pCus_sensor_SetPatternMode = ov2710_SetPatternMode;

    handle->pCus_sensor_AEStatusNotify = pCus_AEStatusNotify;
    handle->pCus_sensor_GetAEUSecs = pCus_GetAEUSecs;
    handle->pCus_sensor_SetAEUSecs = pCus_SetAEUSecs;
    handle->pCus_sensor_GetAEGain = pCus_GetAEGain;
    handle->pCus_sensor_SetAEGain_cal = pCus_SetAEGain_cal;
    handle->pCus_sensor_SetAEGain = pCus_SetAEGain;

    handle->pCus_sensor_GetAEMinMaxGain = pCus_GetAEMinMaxGain;
    handle->pCus_sensor_GetAEMinMaxUSecs = pCus_GetAEMinMaxUSecs;
    handle->pCus_sensor_GetDGainRemainder = pCus_GetDGainRemainder;
    handle->pCus_sensor_GetShutterInfo = OV2710_GetShutterInfo;
    handle->pCus_sensor_setCaliData_gain_linearity = pCus_setCaliData_gain_linearity;
#if 1//defined(__MV5_FPGA__)
    handle->pCus_sensor_I2CWrite = pCus_I2CWrite; //Andy Liu
    handle->pCus_sensor_I2CRead = pCus_I2CRead; //Andy Liu
#endif
    params->expo.vts = vts_30fps;
    params->expo.fps = 30;
    params->reg_dirty = false;
    params->reg_dirty_cnt = 0;

    handle->snr_pad_group = SENSOR_PAD_GROUP_SET;

    handle->channel_num = SENSOR_CHANNEL_NUM;
    handle->channel_mode = SENSOR_CHANNEL_MODE_LINEAR;

    return SUCCESS;
}
int ov2710_MIPI_cus_camsensor_init_handle_linear_2ND( ms_cus_sensor* drv_handle )
{
    ms_cus_sensor *handle = drv_handle;
#if defined(__RTK_OS__)
    CamOsRet_e                  eCamOsRet = CAM_OS_OK;
    void*                       pvBufVirt = NULL;
    u64                 u64BufPhy = 0;
    u64                 u64BufMiu = 0;
    u8                   str[20];
#endif

    if( !handle )
    {
        SENSOR_DMSG( "[%s] not enough memory!\n", __FUNCTION__ );
        return FAIL;
    }
    SENSOR_DMSG( "[%s]\n", __FUNCTION__ );
#if defined(__RTK_OS__)
    sprintf(str, "OV2710linear");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(ov2710_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (ov2710_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(ov2710_params));
#else
    handle->private_data = calloc( 1, sizeof(ov2710_params) );
#endif
	UartSendTrace("[%s:%d] ov2710_MIPI_cus_camsensor_init_handle_linear_2ND\n", __FUNCTION__, __LINE__);
    ov2710_params *params = ( ov2710_params * ) handle->private_data;

    sprintf( handle->model_id, SENSOR_MODEL_ID );
    handle->isp_type = SENSOR_ISP_TYPE;
    handle->sif_bus = SENSOR_IFBUS_TYPE;
    handle->data_prec = SENSOR_DATAPREC;
    handle->data_mode = SENSOR_DATAMODE;
    handle->bayer_id = SCD_SENSOR_BAYERID;
    handle->orient = SENSOR_ORIT;
    handle->interface_attr.attr_mipi.mipi_lane_num = SENSOR_MIPI_LANE_NUM;
    handle->interface_attr.attr_mipi.mipi_data_format = CUS_SEN_INPUT_FORMAT_RGB; // RGB pattern.
    handle->interface_attr.attr_mipi.mipi_yuv_order = 0; //don't care in RGB pattern.
    handle->interface_attr.attr_mipi.mipi_hsync_mode = SENSOR_MIPI_HSYNC_MODE;
    handle->interface_attr.attr_mipi.mipi_sampling_delay = SENSOR_MIPI_DELAY;

    handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_NONE;
    handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 1; //Short frame

    handle->video_res_supported.num_res = 1;
    handle->video_res_supported.ulcur_res = 0; //default resolution index is 0.
    handle->video_res_supported.res[0].width = Preview_WIDTH;
    handle->video_res_supported.res[0].height = Preview_HEIGHT;
    handle->video_res_supported.res[0].max_fps = Preview_MAX_FPS;
    handle->video_res_supported.res[0].min_fps = Preview_MIN_FPS;
    handle->video_res_supported.res[0].crop_start_x= Preview_CROP_START_X;
    handle->video_res_supported.res[0].crop_start_y= Preview_CROP_START_Y;
    handle->video_res_supported.res[0].nOutputWidth= 1928;//Preview_WIDTH;
    handle->video_res_supported.res[0].nOutputHeight= 1088;//Preview_HEIGHT;

    handle->i2c_cfg.mode                = I2C_NORMAL_MODE;
    handle->i2c_cfg.fmt                 = SENSOR_I2C_FMT;
    handle->i2c_cfg.address             = SCD_SENSOR_I2C_ADDR;
    handle->i2c_cfg.speed               = SENSOR_I2C_SPEED;     //200000;
    handle->i2c_cfg.nChannel            = SENSOR_I2C_CHANNEL;   //Channel 1
    handle->i2c_cfg.nPadNum             = SENSOR_I2C_PAD_MODE;  //pad mode 2

    handle->mclk = Preview_MCLK_SPEED;

    handle->pwdn_POLARITY = SCD_SENSOR_PWDN_POL;
    handle->reset_POLARITY = SENSOR_RST_POL;
    handle->VSYNC_POLARITY              = SENSOR_VSYNC_POL; //CUS_CLK_POL_POS;
    handle->HSYNC_POLARITY              = SENSOR_HSYNC_POL; //CUS_CLK_POL_POS;
    handle->PCLK_POLARITY               = SENSOR_PCLK_POL;  //CUS_CLK_POL_POS);    // use '!' to clear board latch error

    handle->ae_gain_delay = SENSOR_GAIN_DELAY_FRAME_COUNT;            //0;//1;
    handle->ae_shutter_delay = SENSOR_SHUTTER_DELAY_FRAME_COUNT;            //1;//2;

    handle->sat_mingain = SENSOR_MIN_GAIN;
    handle->dgain_remainder = 0;
    handle->pCus_sensor_release = ov2710_MIPI_cus_camsensor_release_handle;

    handle->pCus_sensor_init = pCus_init_1lane_linear;

    handle->pCus_sensor_poweron = pCus_poweron;
    handle->pCus_sensor_poweroff = pCus_poweroff;

    handle->pCus_sensor_GetSensorID = pCus_GetSensorID;
    handle->pCus_sensor_GetVideoResNum = pCus_GetVideoResNum;
    handle->pCus_sensor_GetVideoRes = pCus_GetVideoRes;
    handle->pCus_sensor_SetVideoRes = pCus_SetVideoRes_linear;
    handle->pCus_sensor_GetOrien = pCus_GetOrien;
    handle->pCus_sensor_SetOrien = pCus_SetOrien;
    handle->pCus_sensor_GetFPS = pCus_GetFPS;
    handle->pCus_sensor_SetFPS = pCus_SetFPS;
    handle->pCus_sensor_GetSensorCap = pCus_GetSensorCap;
    handle->pCus_sensor_SetPatternMode = ov2710_SetPatternMode;

    handle->pCus_sensor_AEStatusNotify = pCus_AEStatusNotify;
    handle->pCus_sensor_GetAEUSecs = pCus_GetAEUSecs;
    handle->pCus_sensor_SetAEUSecs = pCus_SetAEUSecs;
    handle->pCus_sensor_GetAEGain = pCus_GetAEGain;
    handle->pCus_sensor_SetAEGain_cal = pCus_SetAEGain_cal;
    handle->pCus_sensor_SetAEGain = pCus_SetAEGain;

    handle->pCus_sensor_GetAEMinMaxGain = pCus_GetAEMinMaxGain;
    handle->pCus_sensor_GetAEMinMaxUSecs = pCus_GetAEMinMaxUSecs;
    handle->pCus_sensor_GetDGainRemainder = pCus_GetDGainRemainder;
    handle->pCus_sensor_GetShutterInfo = OV2710_GetShutterInfo;
    handle->pCus_sensor_setCaliData_gain_linearity = pCus_setCaliData_gain_linearity;
#if 1//defined(__MV5_FPGA__)
    handle->pCus_sensor_I2CWrite = pCus_I2CWrite; //Andy Liu
    handle->pCus_sensor_I2CRead = pCus_I2CRead; //Andy Liu
#endif
    params->expo.vts = vts_30fps;
    params->expo.fps = 30;
    params->reg_dirty = false;
    params->reg_dirty_cnt = 0;

    handle->snr_pad_group = SCD_SENSOR_PAD_GROUP_SET;

    handle->channel_num = SCD_SENSOR_CHANNEL_NUM;
    handle->channel_mode = SCD_SENSOR_CHANNEL_MODE_LINEAR;

    return SUCCESS;
}

int ov2710_MIPI_cus_camsensor_release_handle( ms_cus_sensor *handle )
{
#if defined(__RTK_OS__)
    CamOsRet_e                  eCamOsRet = CAM_OS_OK;
#endif

    if( handle && handle->private_data )
    {
        SENSOR_IMSG("[%s] release handle 0x%x, private data %x\n",__FUNCTION__,(int)handle,(int)handle->private_data);
#if defined(__RTK_OS__)
        eCamOsRet = CamOsDirectMemRelease((void*)handle->private_data, sizeof(ov2710_params));
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
struct SensorMapTable_t gsensor_map_ov2710_linear[] = {
    { //Channel 0
        SENSOR_CHANNEL_NUM,
        ov2710_MIPI_cus_camsensor_init_handle_linear,
        ov2710_MIPI_cus_camsensor_release_handle
    },

};

struct SensorMapTable_t gsensor_map_ov2710_linear_2ND[] = {
    { //Channel 1
        SCD_SENSOR_CHANNEL_NUM,
        ov2710_MIPI_cus_camsensor_init_handle_linear_2ND,
        ov2710_MIPI_cus_camsensor_release_handle
    },

};

int OV2710_Module_Init(void)
{
	#if defined(BIND_SENSOR_OV2710) && (BIND_SENSOR_OV2710 == 1)
    cameraSensorRegister(&gsensor_map_ov2710_linear[0]);
	#endif //#if defined(BIND_SENSOR_OV2710) && (BIND_SENSOR_OV2710 == 1)
	#if defined(BIND_SENSOR_OV2710_2ND) && (BIND_SENSOR_OV2710_2ND == 1)
	cameraSensorRegister(&gsensor_map_ov2710_linear_2ND[0]);
	#endif//#if defined(BIND_SENSOR_OV2710_2ND) && (BIND_SENSOR_MIPI_2ND == 1)
    return 0;
}

void OV2710_Module_Exit(void)
{
	#if defined(BIND_SENSOR_OV2710) && (BIND_SENSOR_OV2710 == 1)
    cameraSensorUnRegister(&gsensor_map_ov2710_linear[0]);
	#endif//#if defined(BIND_SENSOR_OV2710) && (BIND_SENSOR_OV2710 == 1)
	#if defined(BIND_SENSOR_OV2710_2ND) && (BIND_SENSOR_OV2710_2ND == 1)
	cameraSensorUnRegister(&gsensor_map_ov2710_linear_2ND[0]);
	#endif //#if defined(BIND_SENSOR_OV2710_2ND) && (BIND_SENSOR_OV2710_2ND == 1)
}

#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(OV2710_Module_Init);
//ait_module_exit(OV2710_Module_Exit);
#endif //#if defined(__RTK_OS__)

#endif //#if (defined(BIND_SENSOR_OV2710) && (BIND_SENSOR_OV2710 == 1) || defined(BIND_SENSOR_OV2710_2ND) && (BIND_SENSOR_OV2710_2ND == 1))
