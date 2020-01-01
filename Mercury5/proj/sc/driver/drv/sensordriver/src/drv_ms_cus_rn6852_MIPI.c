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

//RN2852 support HD/FHD 1/2 CH.

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
#if (SENSOR0 == RN6852)
#define BIND_SENSOR_RN6852_MIPI (1)
#endif
#endif //#if defined(__RTK_OS__)

#if (defined(BIND_SENSOR_RN6852_MIPI) && (BIND_SENSOR_RN6852_MIPI == 1))

#define SENSOR_PAD_GROUP_SET CUS_SENSOR_PAD_GROUP_A
#define SENSOR_CHANNEL_NUM (1)
#define SENSOR_CHANNEL_MODE_LINEAR CUS_SENSOR_CHANNEL_MODE_RAW_STORE

#define SENSOR_MODE_HD_2VC  (1)
#define SENSOR_MODE_FHD_2VC (2)
#define SENSOR_MODE         (SENSOR_MODE_HD_2VC)

#define SENSOR_30FPS  (1)
//#define SENSOR_25FPS  (2) //TODO
#define SENSOR_FPS         (SENSOR_30FPS)

#define RX_TEST_PATTERN (0)

#define NEW_PIN_DEFINE (1)

//============================================
//MIPI config begin.
#if(SENSOR_MODE == SENSOR_MODE_HD_2VC)
#define SENSOR_MIPI_LANE_NUM (4) //4 or 2
#elif (SENSOR_MODE == SENSOR_MODE_FHD_2VC)
#define SENSOR_MIPI_LANE_NUM (4) 
#endif

#define SENSOR_MIPI_HDR_MODE (0) //0: Linear mode. 1:HDR_16b_combined_DCG. 2:HDR_VS_2x12b_DCG_HCG
//MIPI config end.
//============================================

//#define RES_IDX_1920x1080_30P       (0)     // mode 4,  1920*1080 30P       // Video (16:9)
//#define RES_IDX_1280x720_60P        (1)     // mode 9,  1280*720  60P       // Video (16:9)

#define SENSOR_MODEL_ID     "RN6852_MIPI"
#define SENSOR_ISP_TYPE     ISP_EXT                   //ISP_EXT, ISP_SOC
#define SENSOR_IFBUS_TYPE   CUS_SENIF_BUS_MIPI      //CFG //CUS_SENIF_BUS_PARL, CUS_SENIF_BUS_MIPI
#define SENSOR_MIPI_HSYNC_MODE PACKET_HEADER_EDGE1
#define SENSOR_MIPI_DELAY   0x1212                  //CFG

#define SENSOR_DATAPREC     CUS_DATAPRECISION_16
#define SENSOR_DATAMODE     CUS_SEN_10TO12_9000 //CUS_SEN_10TO12_9098     //CFG
#define SENSOR_BAYERID      CUS_BAYER_GB            //CFG //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
#define SENSOR_ORIT         CUS_ORIT_M0F0           //CUS_ORIT_M0F0, CUS_ORIT_M1F0, CUS_ORIT_M0F1, CUS_ORIT_M1F1,
#define SENSOR_MAX_GAIN     (64*1024)//65536
#define SENSOR_MIN_GAIN      (3*1024)//3072
#define SENSOR_GAIN_DELAY_FRAME_COUNT      (2)
#define SENSOR_SHUTTER_DELAY_FRAME_COUNT      (2)

#define Preview_MCLK_SPEED  CUS_CMU_CLK_27MHZ      //CFG //CUS_CMU_CLK_12M, CUS_CMU_CLK_16M, CUS_CMU_CLK_24M, CUS_CMU_CLK_27M
#define Preview_line_period 30250                  ////HTS/PCLK=2420 pixels/80MHZ=30.250us
#define Prv_Max_line_number 1080                    //maximum exposure line munber of sensor when preview
#define vts_30fps  1111                                 //Virt Total Size , 30.25us * 1111 =  33.6ms frame interval =30 fps

#if ((SENSOR_MODE == SENSOR_MODE_FHD_1CH) || (SENSOR_MODE == SENSOR_MODE_FHD_2VC))
#define Preview_WIDTH       1920                    //resolution Width when preview
#define Preview_HEIGHT      1080                    //resolution Height when preview
#else
#define Preview_WIDTH       1280                    //resolution Width when preview
#define Preview_HEIGHT      720                     //resolution Height when preview
#endif

#define Preview_MAX_FPS     30                     //fastest preview FPS
#define Preview_MIN_FPS     8                      //slowest preview FPS
#define Preview_CROP_START_X     1                      //CROP_START_X
#define Preview_CROP_START_Y     1                      //CROP_START_Y

#define Cap_Max_line_number 1080                   //maximum exposure line munber of sensor when capture

#define SENSOR_I2C_ADDR     0x5a//0x2d         //I2C slave address
//#define SENSOR_I2C_ADDR     0x58//0x2c         //I2C slave address
#define SENSOR_I2C_SPEED    I2C_SLOWSPEED_MODE_200KHZ   //200KHz
#define SENSOR_I2C_CHANNEL  1                           //I2C Channel
#define SENSOR_I2C_PAD_MODE 2                           //Pad/Mode Number

#define SENSOR_I2C_LEGACY  I2C_NORMAL_MODE     //usally set CUS_I2C_NORMAL_MODE,  if use old OVT I2C protocol=> set CUS_I2C_LEGACY_MODE
#define SENSOR_I2C_FMT     I2C_FMT_A8D8        //CUS_I2C_FMT_A8D8, CUS_I2C_FMT_A8D16, CUS_I2C_FMT_A16D8, CUS_I2C_FMT_A16D16

#define SENSOR_PWDN_POL     CUS_CLK_POL_NEG        // if PWDN pin High can makes sensor in power down, set CUS_CLK_POL_POS
#define SENSOR_RST_POL      CUS_CLK_POL_NEG//CUS_CLK_POL_NEG        // if RESET pin High can makes sensor in reset state, set CUS_CLK_POL_NEG

// VSYNC/HSYNC POL can be found in data sheet timing diagram,
// Notice: the initial setting may contain VSYNC/HSYNC POL inverse settings so that condition is different.

#define SENSOR_VSYNC_POL    CUS_CLK_POL_POS// if VSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_HSYNC_POL    CUS_CLK_POL_POS// if HSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_PCLK_POL     CUS_CLK_POL_POS        // depend on sensor setting, sometimes need to try CUS_CLK_POL_POS or CUS_CLK_POL_NEG

/*
#define MAX_SENSOR_GAIN_HCG_LCG     (64*11)
#define MAX_SENSOR_GAIN_VS     (64)
#define ISP_DGAIN_BASE      (0x200)
#define SENSOR_GAIN_BASE      (0x100)

#define OV2718_GET_MIN(a, b)                   ( ((a) < (b)) ? (a) : (b) )
#define OV2718_GET_MAX(a, b)                   ( ((a) > (b)) ? (a) : (b) )
*/
/*
static u32 HCG_AGain = 0;
static u32 HCG_DGain = 0x100;
static u32 LCG_AGain = 0;
static u32 LCG_DGain = 0x100;
static u32 VS_AGain = 0;
static u32 VS_DGain = 0x100;

static u32 new_shutter_l = 0;
static u32 new_shutter_s = 0;

static u8 HCG_switch = 0x85;
*/

int rn6852_MIPI_cus_camsensor_release_handle( ms_cus_sensor *handle );

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
} rn6852_params;

static I2C_ARRAY Sensor_id_table[] =
{

};

#if(SENSOR_MODE == SENSOR_MODE_HD_1CH)
static I2C_ARRAY Sensor_init_table_HD_1CH[] =
{
    
};
#endif //(SENSOR_MODE == SENSOR_MODE_HD_1CH)

#if(SENSOR_MODE == SENSOR_MODE_HD_2VC)
#if (SENSOR_MIPI_LANE_NUM == 4)
static I2C_ARRAY Sensor_init_table_HD_2VC[] =
{
    // if clock source(Xin) of RN6752 is 26MHz, please add these procedures marked first
    //0xD2, 0x85, // disable auto clock detect
    //0xD6, 0x37, // 27MHz default
    //0xD8, 0x18, // switch to 26MHz clock
    //delay(100), // delay 100ms
    
    0x81, 0x03, // turn on video decoder
    0xDF, 0xFC, // enable HD format
    
    0x88, 0x00,
    0xF6, 0x00,
    
    // ch0
    0xFF, 0x00, // switch to ch0 (default; optional)
#if (RX_TEST_PATTERN)
    0x00, 0xA0, //0x20, // internal use*
#else
    0x00, 0x20, // internal use*
#endif
    0x06, 0x08, // internal use*
    0x07, 0x63, // HD format
    0x2A, 0x01, // filter control
    0x3A, 0x20, // Insert Channel ID in SAV/EAV code
    0x3F, 0x10, // channel ID
    0x4C, 0x37, // equalizer
    0x4F, 0x03, // sync control
    0x50, 0x02, // 720p resolution
    0x56, 0x01, // 72M mode
    0x5F, 0x40, // blank level
    0x63, 0xF5, // filter control
    0x59, 0x00, // extended register access
    0x5A, 0x44, // data for extended register
    0x58, 0x01, // enable extended register write
    0x59, 0x33, // extended register access
    0x5A, 0x23, // data for extended register
    0x58, 0x01, // enable extended register write
    0x51, 0x4E, // scale factor1
    0x52, 0x87, // scale factor2
    0x53, 0x12, // scale factor3
    0x5B, 0x07, // H-scaling control
#if (NEW_PIN_DEFINE)
    0x5E, 0x08, // enable H-scaling control
#else
    0x5E, 0x0B, // enable H-scaling control
#endif
    0x6A, 0x82, // H-scaling control
    0x28, 0x92, // cropping
    0x03, 0x80, // saturation
    0x04, 0x80, // hue
    0x05, 0x00, // sharpness
    0x57, 0x23, // black/white stretch
    0x68, 0x32, // coring
#if (NEW_PIN_DEFINE)
    0x37, 0x33,
    0x61, 0x6C,
#endif

    // ch1
    0xFF, 0x01, // switch to ch0 (default; optional)
#if (RX_TEST_PATTERN)
    0x00, 0xA0, //0x20, // internal use*
#else
    0x00, 0x20, // internal use*
#endif
    0x06, 0x08, // internal use*
    0x07, 0x63, // HD format
    0x2A, 0x01, // filter control
    0x3A, 0x20, // Insert Channel ID in SAV/EAV code
    0x3F, 0x11, // channel ID
    0x4C, 0x37, // equalizer
    0x4F, 0x03, // sync control
    0x50, 0x02, // 720p resolution
    0x56, 0x01, // 72M mode
    0x5F, 0x40, // blank level
    0x63, 0xF5, // filter control
    0x59, 0x00, // extended register access
    0x5A, 0x44, // data for extended register
    0x58, 0x01, // enable extended register write
    0x59, 0x33, // extended register access
    0x5A, 0x23, // data for extended register
    0x58, 0x01, // enable extended register write
    0x51, 0x4E, // scale factor1
    0x52, 0x87, // scale factor2
    0x53, 0x12, // scale factor3
    0x5B, 0x07, // H-scaling control
#if (NEW_PIN_DEFINE)
    0x5E, 0x08, // enable H-scaling control
#else
    0x5E, 0x0B, // enable H-scaling control
#endif
    0x6A, 0x82, // H-scaling control
    0x28, 0x92, // cropping
    0x03, 0x80, // saturation
    0x04, 0x80, // hue
    0x05, 0x00, // sharpness
    0x57, 0x23, // black/white stretch
    0x68, 0x32, // coring
#if (NEW_PIN_DEFINE)
    0x37, 0x33,
    0x61, 0x6C,
#endif

    0x81, 0x03, // turn on video decoder
    
    // mipi link1
    0xFF, 0x09, // switch to mipi tx1
    0x00, 0x03, // enable bias
#if (NEW_PIN_DEFINE)
    0x04, 0x32, 
    0x05, 0x10,
#else
    0x02, 0x04,
    0x04, 0x10, 
    0x05, 0x34,
    0x06, 0x02,
#endif
    0xFF, 0x08, // switch to mipi csi1
    0x04, 0x03, // csi1 and tx1 reset
    0x6C, 0x13, // disable ch output; turn on ch0/ch1
    0x06, 0x7C, // 4 lanes
    0x21, 0x01, // enable hs clock
    0x78, 0x80, // Y/C counts for ch0
    0x79, 0x02, // Y/C counts for ch0
    0x7A, 0x80, // Y/C counts for ch1
    0x7B, 0x02, // Y/C counts for ch1
    0x6C, 0x03, // enable ch0/ch1 output
    0x04, 0x00, // csi1 and tx1 reset finish
#if (NEW_PIN_DEFINE)
    0x20, 0xAA,
#endif

    // mipi link3
    0xFF, 0x0A, // switch to mipi csi3
    0x6C, 0x10, // disable ch output; turn off ch0~3
};
#endif

#if (SENSOR_MIPI_LANE_NUM == 2)
static I2C_ARRAY Sensor_init_table_HD_2VC[] =
{
    // 720P@30 2ch with mipi 2 data lanes + 1 clock lane out
    // pin24/23 data lane0, pin18/17 data lane1
    // pin16/15 clock lane
    // pin14/13 floating, pin12/11 floating
    // Slave address is 0x58
    // Register, data

    // if clock source(Xin) of RN6752 is 26MHz, please add these procedures marked first
    //0xD2, 0x85, // disable auto clock detect
    //0xD6, 0x37, // 27MHz default
    //0xD8, 0x18, // switch to 26MHz clock
    //delay(100), // delay 100ms

    0x81, 0x03, // turn on video decoder
    0xDF, 0xFC, // enable HD format

#if (NEW_PIN_DEFINE)
    0x88, 0x00,
    0xF6, 0x00,
#endif

    // ch0
    0xFF, 0x00, // switch to ch0 (default; optional)
#if (RX_TEST_PATTERN)
    0x00, 0xA0, //0x20, // internal use*
#else
    0x00, 0x20, // internal use*
#endif
    0x06, 0x08, // internal use*
    0x07, 0x63, // HD format
    0x2A, 0x01, // filter control
    0x3A, 0x20, // Insert Channel ID in SAV/EAV code
    0x3F, 0x10, // channel ID
    0x4C, 0x37, // equalizer
    0x4F, 0x03, // sync control
    0x50, 0x02, // 720p resolution
    0x56, 0x01, // 72M mode
    0x5F, 0x40, // blank level
    0x63, 0xF5, // filter control
    0x59, 0x00, // extended register access
    0x5A, 0x44, // data for extended register
    0x58, 0x01, // enable extended register write
    0x59, 0x33, // extended register access
    0x5A, 0x23, // data for extended register
    0x58, 0x01, // enable extended register write
    0x51, 0x4E, // scale factor1
    0x52, 0x87, // scale factor2
    0x53, 0x12, // scale factor3
    0x5B, 0x07, // H-scaling control
#if (NEW_PIN_DEFINE)
    0x5E, 0x08, // enable H-scaling control
#else
    0x5E, 0x0B, // enable H-scaling control
#endif
    0x6A, 0x82, // H-scaling control
    0x28, 0x92, // cropping
    0x03, 0x80, // saturation
    0x04, 0x80, // hue
    0x05, 0x00, // sharpness
    0x57, 0x23, // black/white stretch
    0x68, 0x32, // coring
#if (NEW_PIN_DEFINE)
    0x37, 0x33,
    0x61, 0x6C,
#endif

    // ch1
    0xFF, 0x01, // switch to ch0 (default; optional)
#if (RX_TEST_PATTERN)
    0x00, 0xA0, //0x20, // internal use*
#else
    0x00, 0x20, // internal use*
#endif
    0x06, 0x08, // internal use*
    0x07, 0x63, // HD format
    0x2A, 0x01, // filter control
    0x3A, 0x20, // Insert Channel ID in SAV/EAV code
    0x3F, 0x11, // channel ID
    0x4C, 0x37, // equalizer
    0x4F, 0x03, // sync control
    0x50, 0x02, // 720p resolution
    0x56, 0x01, // 72M mode
    0x5F, 0x40, // blank level
    0x63, 0xF5, // filter control
    0x59, 0x00, // extended register access
    0x5A, 0x44, // data for extended register
    0x58, 0x01, // enable extended register write
    0x59, 0x33, // extended register access
    0x5A, 0x23, // data for extended register
    0x58, 0x01, // enable extended register write
    0x51, 0x4E, // scale factor1
    0x52, 0x87, // scale factor2
    0x53, 0x12, // scale factor3
    0x5B, 0x07, // H-scaling control
#if (NEW_PIN_DEFINE)
    0x5E, 0x08, // enable H-scaling control
#else
    0x5E, 0x0B, // enable H-scaling control
#endif
    0x6A, 0x82, // H-scaling control
    0x28, 0x92, // cropping
    0x03, 0x80, // saturation
    0x04, 0x80, // hue
    0x05, 0x00, // sharpness
    0x57, 0x23, // black/white stretch
    0x68, 0x32, // coring
#if (NEW_PIN_DEFINE)
    0x37, 0x33,
    0x61, 0x6C,
#endif

    0x81, 0x03, // turn on video decoder

    // mipi link1
    0xFF, 0x09, // switch to mipi tx1
    0x00, 0x03, // enable bias
#if (NEW_PIN_DEFINE)
    0x04, 0x32, 
    0x05, 0x10, 
#else
    0x02, 0x04,
    0x04, 0x10, 
    0x05, 0x34,
    0x06, 0x02, 
#endif
    0xFF, 0x08, // switch to mipi csi1
    0x04, 0x03, // csi1 and tx1 reset
    0x6C, 0x13, // disable ch output; turn on ch0/ch1
    0x06, 0x4C, // 2 lanes
    0x21, 0x01, // enable hs clock
    0x78, 0x80, // Y/C counts for ch0
    0x79, 0x02, // Y/C counts for ch0
    0x7A, 0x80, // Y/C counts for ch1
    0x7B, 0x02, // Y/C counts for ch1
    0x6C, 0x03, // enable ch0/ch1 output
    0x04, 0x00, // csi1 and tx1 reset finish
#if (NEW_PIN_DEFINE)
    0x20, 0xAA,
#endif

    // mipi link3
    0xFF, 0x0A, // switch to mipi csi3
    0x6C, 0x10, // disable ch output; turn off ch0~3
};
#endif
#endif //(SENSOR_MODE == SENSOR_MODE_HD_2VC)


#if(SENSOR_MODE == SENSOR_MODE_FHD_1CH)
static I2C_ARRAY Sensor_init_table_FHD_1CH[] =
{

};
#endif //(SENSOR_MODE == SENSOR_MODE_FHD_1CH)

#if(SENSOR_MODE == SENSOR_MODE_FHD_2VC)
static I2C_ARRAY Sensor_init_table_FHD_2VC[] =
{
    // 1080P@30 2ch with mipi 4 data lanes + 1 clock lane out
    // pin24/23 data lane0, pin18/17 data lane1
    // pin16/15 clock lane
    // pin14/13 data lane2, pin12/11 data lane3
    // Slave address is 0x58
    // Register, data
    
    // if clock source(Xin) of RN6752 is 26MHz, please add these procedures marked first
    //0xD2, 0x85, // disable auto clock detect
    //0xD6, 0x37, // 27MHz default
    //0xD8, 0x18, // switch to 26MHz clock
    //delay(100), // delay 100ms
    
    0x81, 0x03, // turn on video decoder
    0xDF, 0xFC, // enable HD format
    0xF0, 0xC0, //
#if (NEW_PIN_DEFINE)
    0x88, 0x00,
    0xF6, 0x00,
#endif

    // ch0
    0xFF, 0x00, // switch to ch0 (default; optional)
#if (RX_TEST_PATTERN)
    0x00, 0xA0, //0x20, // internal use*
#else
    0x00, 0x20, // internal use*
#endif
    0x06, 0x08, // internal use*
    0x07, 0x63, // HD format
    0x2A, 0x01, // filter control
    0x3A, 0x20, // Insert Channel ID in SAV/EAV code
    0x3F, 0x10, // channel ID
    0x4C, 0x37, // equalizer
    0x4F, 0x03, // sync control
    0x50, 0x03, // 1080p resolution
    0x56, 0x02, // 144M mode
    0x5F, 0x44, // blank level
    0x63, 0xF8, // filter control
    0x59, 0x00, // extended register access
    0x5A, 0x49, // data for extended register
    0x58, 0x01, // enable extended register write
    0x59, 0x33, // extended register access
    0x5A, 0x23, // data for extended register
    0x58, 0x01, // enable extended register write
    0x51, 0xF4, // scale factor1
    0x52, 0x29, // scale factor2
    0x53, 0x15, // scale factor3
    0x5B, 0x01, // H-scaling control
#if (NEW_PIN_DEFINE)
    0x5E, 0x08, // enable H-scaling control
#else
    0x5E, 0x0F, // enable H-scaling control
#endif
    0x6A, 0x87, // H-scaling control
    0x28, 0x92, // cropping
    0x03, 0x80, // saturation
    0x04, 0x80, // hue
    0x05, 0x04, // sharpness
    0x57, 0x23, // black/white stretch
    0x68, 0x00, // coring
#if (NEW_PIN_DEFINE)
    0x37, 0x33,
    0x61, 0x6C,
#endif

    // ch1
    0xFF, 0x01, // switch to ch0 (default; optional)
#if (RX_TEST_PATTERN)
    0x00, 0xA0, //0x20, // internal use*
#else
    0x00, 0x20, // internal use*
#endif
    0x06, 0x08, // internal use*
    0x07, 0x63, // HD format
    0x2A, 0x01, // filter control
    0x3A, 0x20, // Insert Channel ID in SAV/EAV code
    0x3F, 0x11, // channel ID
    0x4C, 0x37, // equalizer
    0x4F, 0x03, // sync control
    0x50, 0x03, // 1080p resolution
    0x56, 0x02, // 144M mode
    0x5F, 0x44, // blank level
    0x63, 0xF8, // filter control
    0x59, 0x00, // extended register access
    0x5A, 0x49, // data for extended register
    0x58, 0x01, // enable extended register write
    0x59, 0x33, // extended register access
    0x5A, 0x23, // data for extended register
    0x58, 0x01, // enable extended register write
    0x51, 0xF4, // scale factor1
    0x52, 0x29, // scale factor2
    0x53, 0x15, // scale factor3
    0x5B, 0x01, // H-scaling control
#if (NEW_PIN_DEFINE)
    0x5E, 0x08, // enable H-scaling control
#else
    0x5E, 0x0F, // enable H-scaling control
#endif
    0x6A, 0x87, // H-scaling control
    0x28, 0x92, // cropping
    0x03, 0x80, // saturation
    0x04, 0x80, // hue
    0x05, 0x04, // sharpness
    0x57, 0x23, // black/white stretch
    0x68, 0x00, // coring
#if (NEW_PIN_DEFINE)
    0x37, 0x33,
    0x61, 0x6C,
#endif
    
    0x81, 0x03,
    
    // mipi link1
    0xFF, 0x09, // switch to mipi tx1
    0x00, 0x03, // enable bias
#if (NEW_PIN_DEFINE)
    0x04, 0x32, 
    0x05, 0x10,
#else
    0x02, 0x04,
    0x04, 0x10, 
    0x05, 0x34,
    0x06, 0x02, 
#endif
    0xFF, 0x08, // switch to mipi csi1
    0x04, 0x03, // csi1 and tx1 reset
    0x6C, 0x13, // disable ch output; turn on ch0/ch1
    0x06, 0x7C, // 4 lanes
    0x21, 0x01, // enable hs clock
    0x78, 0xC0, // Y/C counts for ch0
    0x79, 0x03, // Y/C counts for ch0
    0x7A, 0xC0, // Y/C counts for ch1
    0x7B, 0x03, // Y/C counts for ch1
    0x6C, 0x03, // enable ch output
    0x04, 0x00, // csi1 and tx1 reset finish
#if (NEW_PIN_DEFINE)
    0x20, 0xAA,
#endif

    // mipi link3
    0xFF, 0x0A, // switch to mipi csi3
    0x6C, 0x10, // disable ch output; turn off ch0~3
};
#endif //(SENSOR_MODE == SENSOR_MODE_FHD_2VC)

static I2C_ARRAY PatternTbl[] =
{

};

static I2C_ARRAY Current_Mirror_Flip_Tbl[] =
{

};

/*
static I2C_ARRAY gain_reg[] =
{

};

static CUS_GAIN_GAP_ARRAY gain_gap_compensate[] =
{

};
static I2C_ARRAY expo_reg[] =
{

};

static I2C_ARRAY vts_reg[] =
{

};
*/

static int pCus_poweron( ms_cus_sensor *handle )
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    SENSOR_DMSG( "[%s] ", __FUNCTION__ );

    //sensor_if->SetIOPad(SENSOR_PAD_GROUP_SET, CUS_SENIF_BUS_MIPI, CUS_SR0_MIPI_MODE_2 );//GroupB: Work //Old
    //sensor_if->SetIOPad(SENSOR_PAD_GROUP_SET, CUS_SENIF_BUS_MIPI, CUS_SR1_MIPI_MODE_2 );//GroupB:Work
    //sensor_if->SetIOPad(SENSOR_PAD_GROUP_SET, CUS_SENIF_BUS_MIPI, CUS_SR1_MIPI_MODE_1 );//GroupB:XX
    //sensor_if->SetIOPad(SENSOR_PAD_GROUP_SET, CUS_SENIF_BUS_MIPI, CUS_SR1_MIPI_MODE_3 );//GroupB:XX -> No RST pin Work
    //sensor_if->SetIOPad(SENSOR_PAD_GROUP_SET, CUS_SENIF_BUS_MIPI, CUS_SR1_MIPI_MODE_4 );//GroupB:Work
    
    //sensor_if->SetIOPad(SENSOR_PAD_GROUP_SET, CUS_SENIF_BUS_MIPI, CUS_SR0_MIPI_MODE_1 ); //GroupA: Set Bank1312
    #if 0
    if(handle->interface_attr.attr_mipi.mipi_lane_num == 2){
        sensor_if->SetIOPad(handle->snr_pad_group, CUS_SENIF_BUS_MIPI, CUS_SR1_MIPI_MODE_1 );
    }
    else if(handle->interface_attr.attr_mipi.mipi_lane_num == 4){
        sensor_if->SetIOPad(handle->snr_pad_group, CUS_SENIF_BUS_MIPI, CUS_SR0_MIPI_MODE_2);
    }
    else{
        SENSOR_DMSG( "[%s] mipi_lane_num err %d\n", __FUNCTION__, handle->interface_attr.attr_mipi.mipi_lane_num );
    }
    #endif

    if(handle->snr_pad_group == CUS_SENSOR_PAD_GROUP_A) {
        if(handle->interface_attr.attr_mipi.mipi_lane_num == 4){
            sensor_if->SetIOPad(handle->snr_pad_group, CUS_SENIF_BUS_MIPI, CUS_SR0_MIPI_MODE_2 );
        }
        else if((handle->interface_attr.attr_mipi.mipi_lane_num == 2) || (handle->interface_attr.attr_mipi.mipi_lane_num == 1)){ 
            sensor_if->SetIOPad(handle->snr_pad_group, CUS_SENIF_BUS_MIPI, CUS_SR0_MIPI_MODE_1);
        }
        else {
            SENSOR_DMSG( "[%s] mipi_lane_num err %d\n", __FUNCTION__, handle->interface_attr.attr_mipi.mipi_lane_num );
        }
    }
    else {//CUS_SENSOR_PAD_GROUP_B
        if(handle->interface_attr.attr_mipi.mipi_lane_num == 2){
            sensor_if->SetIOPad(handle->snr_pad_group, CUS_SENIF_BUS_MIPI, CUS_SR1_MIPI_MODE_3 );
        }
        else if(handle->interface_attr.attr_mipi.mipi_lane_num == 1){
            sensor_if->SetIOPad(handle->snr_pad_group, CUS_SENIF_BUS_MIPI, CUS_SR1_MIPI_MODE_1);
        }
        else {
            SENSOR_DMSG( "[%s] mipi_lane_num err2 %d\n", __FUNCTION__, handle->interface_attr.attr_mipi.mipi_lane_num );
        }
    }
    
    sensor_if->SetCSI_Clk(handle->snr_pad_group, /*CUS_CSI_CLK_288M */CUS_CSI_CLK_216M, handle->PCLK_POLARITY);

    //sensor_if->SetCSI_Lane(SENSOR_PAD_GROUP_SET, SENSOR_MIPI_LANE_NUM, 1);
    if(handle->interface_attr.attr_mipi.mipi_lane_num == 2){
        sensor_if->SetCSI_Lane(handle->snr_pad_group, 2, 1);
    }
    else if(handle->interface_attr.attr_mipi.mipi_lane_num == 4){
        sensor_if->SetCSI_Lane(handle->snr_pad_group, 4, 1);
    }

#if 0 //------------------------------------------------------------
    sensor_if->MCLK(SENSOR_PAD_GROUP_SET, 1, handle->mclk);
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
    MsSleep(RTK_MS_TO_TICK(10));
    SENSOR_DMSG( "[%s] reset high\n", __FUNCTION__ );
    sensor_if->Reset(handle->snr_pad_group, !handle->reset_POLARITY );
    MsSleep(RTK_MS_TO_TICK(5));//usleep( 500 );

    // pure power on
    sensor_if->PowerOff(handle->snr_pad_group, !handle->pwdn_POLARITY );

    sensor_if->SWReset(handle->channel_num, FALSE);

#else //------------------------------------------------------------
    sensor_if->MCLK(SENSOR_PAD_GROUP_SET, 1, handle->mclk);
    MsSleep(RTK_MS_TO_TICK(5));

    SENSOR_DMSG("[%s] reset low\n", __FUNCTION__);
    sensor_if->Reset(SENSOR_PAD_GROUP_SET, handle->reset_POLARITY);
    MsSleep(RTK_MS_TO_TICK(5));
#if 0
    SENSOR_DMSG("[%s] power low\n", __FUNCTION__);
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, handle->pwdn_POLARITY);
    MsSleep(RTK_MS_TO_TICK(5));//usleep(500);

    // power -> high, reset -> high
    SENSOR_DMSG("[%s] power high\n", __FUNCTION__);
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, !handle->pwdn_POLARITY);
    MsSleep(RTK_MS_TO_TICK(5));//usleep(500);
    SENSOR_DMSG("[%s] reset high\n", __FUNCTION__);
#endif
    sensor_if->Reset(SENSOR_PAD_GROUP_SET, !handle->reset_POLARITY);
    MsSleep(RTK_MS_TO_TICK(5));

    //sensor_if->Set3ATaskOrder( def_order);
    // pure power on
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, !handle->pwdn_POLARITY);
	sensor_if->SWReset(handle->channel_num, FALSE);
	MsSleep(RTK_MS_TO_TICK(50));

    #if defined(SENSOR_PWR_CTRL_GPIO)
    MMPF_PIO_Enable(SENSOR_PWR_CTRL_GPIO, MMP_TRUE);
    MMPF_PIO_EnableOutputMode(SENSOR_PWR_CTRL_GPIO, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData(SENSOR_PWR_CTRL_GPIO, MMP_TRUE, MMP_TRUE);
    #endif
    
#endif //------------------------------------------------------------
    return SUCCESS;
}

#if((SENSOR_MODE == SENSOR_MODE_HD_2VC) || (SENSOR_MODE == SENSOR_MODE_FHD_2VC))
static int pCus_poweron_Null( ms_cus_sensor *handle )
{
    return SUCCESS;
}
#endif

static int pCus_poweroff( ms_cus_sensor *handle )
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    SENSOR_DMSG( "[%s] power low\n", __FUNCTION__ );

    sensor_if->SWReset(handle->channel_num, TRUE);
    
    sensor_if->PowerOff(handle->snr_pad_group, handle->pwdn_POLARITY );
    MsSleep(RTK_MS_TO_TICK(5));//usleep( 1000 );
	sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_DISABLE, handle->PCLK_POLARITY );
    sensor_if->MCLK(handle->snr_pad_group, 0, handle->mclk );
    //sensor_if->SetCSI_Lane(handle->snr_pad_group, SENSOR_MIPI_LANE_NUM, 0);
    if(handle->interface_attr.attr_mipi.mipi_lane_num == 2){
        sensor_if->SetCSI_Lane(handle->snr_pad_group, 2, 0);
    }
    else if(handle->interface_attr.attr_mipi.mipi_lane_num == 4){
        sensor_if->SetCSI_Lane(handle->snr_pad_group, 4, 0);
    }
    return SUCCESS;
}

#if((SENSOR_MODE == SENSOR_MODE_HD_2VC) || (SENSOR_MODE == SENSOR_MODE_FHD_2VC))
static int pCus_poweroff_Null( ms_cus_sensor *handle )
{
    return SUCCESS;
}
#endif

static int pCus_GetSensorID( ms_cus_sensor *handle, u32 *id )
{
    *id =0;
    
    return SUCCESS;
}

static int rn6852_SetPatternMode( ms_cus_sensor *handle, u32 mode )
{
    
    return SUCCESS;
}

static int pCus_I2CWrite(ms_cus_sensor *handle, unsigned short usreg, unsigned short usval)
{
    unsigned short sen_data;

    SensorReg_Write(usreg, usval);

    #if 1
    SensorReg_Read(usreg, &sen_data);
    UartSendTrace("rn6852_MIPI reg: 0x%x, data: 0x%x, read: 0x%x.\n", usreg, usval, sen_data);
    #endif
    
    return SUCCESS;
}

static int pCus_I2CRead(ms_cus_sensor *handle, unsigned short usreg, unsigned short* pusval)
{
    unsigned short usread_data;

    SensorReg_Read(usreg, &usread_data);
    *pusval = usread_data;
    UartSendTrace("rn6852_MIPI reg: 0x%x, data: 0x%x\n", usreg, usread_data);

    return SUCCESS;
}

void pre_init(ms_cus_sensor *handle)
{
    short rom_byte1, rom_byte2, rom_byte3, rom_byte4, rom_byte5, rom_byte6;
    
    SensorReg_Write(0xE1, 0x80);
    SensorReg_Write(0xFA, 0x81);
    SensorReg_Read(0xFB, &rom_byte1);
    SensorReg_Read(0xFB, &rom_byte2);
    SensorReg_Read(0xFB, &rom_byte3);
    SensorReg_Read(0xFB, &rom_byte4);
    SensorReg_Read(0xFB, &rom_byte5);
    SensorReg_Read(0xFB, &rom_byte6);

    // config. decoder accroding to rom_byte5 and rom_byte6
	if ((rom_byte6 == 0x00) && (rom_byte5 == 0x00)) {
		SensorReg_Write(0xEF, 0xAA);  
		SensorReg_Write(0xE7, 0xFF);
		SensorReg_Write(0xFF, 0x09);
		SensorReg_Write(0x03, 0x0C);
		SensorReg_Write(0xFF, 0x0B);
		SensorReg_Write(0x03, 0x0C);
	}
	else if (((rom_byte6 == 0x34) && (rom_byte5 == 0xA9)) ||
         ((rom_byte6 == 0x2C) && (rom_byte5 == 0xA8))) {
		SensorReg_Write(0xEF, 0xAA);
		SensorReg_Write(0xE7, 0xFF);
		SensorReg_Write(0xFC, 0x60);
		SensorReg_Write(0xFF, 0x09);
		SensorReg_Write(0x03, 0x18);
		SensorReg_Write(0xFF, 0x0B);
		SensorReg_Write(0x03, 0x18);
	}
	else {
		SensorReg_Write(0xEF, 0xAA);
		SensorReg_Write(0xFC, 0x60);
		SensorReg_Write(0xFF, 0x09);
		SensorReg_Write(0x03, 0x18);
		SensorReg_Write(0xFF, 0x0B);
		SensorReg_Write(0x03, 0x18);
	}
}


#if(SENSOR_MODE == SENSOR_MODE_HD_1CH)
static int pCus_init_HD_1CH( ms_cus_sensor *handle )
{
    int i;
    ISensorIfAPI *sensor_if = &( handle->sensor_if_api );
    short sen_data;
    sensor_if->PCLK( CUS_SNR_PCLK_MIPI_TOP );

    UartSendTrace("\n===== rn6852 HD_1CH init. =====\n");

    pre_init(handle);

    for( i = 0; i < ARRAY_SIZE( Sensor_init_table_HD_1CH ); i++ )
    {
        if( Sensor_init_table_HD_1CH[i].reg == 0xffff )
        {
            MsSleep(RTK_MS_TO_TICK(1));
        }
        else
        {
            if( SensorReg_Write(Sensor_init_table_HD_1CH[i].reg,Sensor_init_table_HD_1CH[i].data) != SUCCESS )
            {
                return FAIL;
            }
            SensorReg_Read( Sensor_init_table_HD_1CH[i].reg, &sen_data );
            UartSendTrace("rn6852 reg: 0x%x, data: 0x%x, read: 0x%x.\n",Sensor_init_table_HD_1CH[i].reg, Sensor_init_table_HD_1CH[i].data, sen_data);
        }
    }

    return SUCCESS;
}
#endif

#if(SENSOR_MODE == SENSOR_MODE_HD_2VC)
static int pCus_init_HD_2VC( ms_cus_sensor *handle )
{
    int i;
    ISensorIfAPI *sensor_if = &( handle->sensor_if_api );
    short sen_data;
    sensor_if->PCLK( CUS_SNR_PCLK_MIPI_TOP );

    UartSendTrace("\n===== rn6852 HD_2VC init. =====\n");

    pre_init(handle);
    
    for( i = 0; i < ARRAY_SIZE( Sensor_init_table_HD_2VC ); i++ )
    {
        if( Sensor_init_table_HD_2VC[i].reg == 0xffff )
        {
            MsSleep(RTK_MS_TO_TICK(1));
        }
        else
        {
            if( SensorReg_Write(Sensor_init_table_HD_2VC[i].reg,Sensor_init_table_HD_2VC[i].data) != SUCCESS )
            {
                return FAIL;
            }
            SensorReg_Read( Sensor_init_table_HD_2VC[i].reg, &sen_data );
            UartSendTrace("rn6852 reg: 0x%x, data: 0x%x, read: 0x%x.\n",Sensor_init_table_HD_2VC[i].reg, Sensor_init_table_HD_2VC[i].data, sen_data);
        }
    }

    return SUCCESS;
}
#endif

#if(SENSOR_MODE == SENSOR_MODE_FHD_1CH)
static int pCus_init_FHD_1CH( ms_cus_sensor *handle )
{
    int i;
    ISensorIfAPI *sensor_if = &( handle->sensor_if_api );
    short sen_data;
    sensor_if->PCLK( CUS_SNR_PCLK_MIPI_TOP );

    UartSendTrace("\n===== rn6852 FHD_1CH init. =====\n");

    pre_init(handle);
    
    for( i = 0; i < ARRAY_SIZE( Sensor_init_table_FHD_1CH ); i++ )
    {
        if( Sensor_init_table_FHD_1CH[i].reg == 0xffff )
        {
            MsSleep(RTK_MS_TO_TICK(1));
        }
        else
        {
            if( SensorReg_Write(Sensor_init_table_FHD_1CH[i].reg,Sensor_init_table_FHD_1CH[i].data) != SUCCESS )
            {
                return FAIL;
            }
            SensorReg_Read( Sensor_init_table_FHD_1CH[i].reg, &sen_data );
            UartSendTrace("rn6852 reg: 0x%x, data: 0x%x, read: 0x%x.\n",Sensor_init_table_FHD_1CH[i].reg, Sensor_init_table_FHD_1CH[i].data, sen_data);
        }
    }

    return SUCCESS;
}
#endif

#if(SENSOR_MODE == SENSOR_MODE_FHD_2VC)
static int pCus_init_FHD_2VC( ms_cus_sensor *handle )
{
    int i;
    ISensorIfAPI *sensor_if = &( handle->sensor_if_api );
    short sen_data;
    sensor_if->PCLK( CUS_SNR_PCLK_MIPI_TOP );

    UartSendTrace("\n===== rn6852 FHD_2VC init. =====\n");

    pre_init(handle);
    
    for( i = 0; i < ARRAY_SIZE( Sensor_init_table_FHD_2VC ); i++ )
    {
        if( Sensor_init_table_FHD_2VC[i].reg == 0xffff )
        {
            MsSleep(RTK_MS_TO_TICK(1));
        }
        else
        {
            if( SensorReg_Write(Sensor_init_table_FHD_2VC[i].reg,Sensor_init_table_FHD_2VC[i].data) != SUCCESS )
            {
                return FAIL;
            }
            SensorReg_Read( Sensor_init_table_FHD_2VC[i].reg, &sen_data );
            UartSendTrace("rn6852 reg: 0x%x, data: 0x%x, read: 0x%x.\n",Sensor_init_table_FHD_2VC[i].reg, Sensor_init_table_FHD_2VC[i].data, sen_data);
        }
    }

    return SUCCESS;
}
#endif

#if((SENSOR_MODE == SENSOR_MODE_HD_2VC) || (SENSOR_MODE == SENSOR_MODE_FHD_2VC))
static int pCus_init_Null( ms_cus_sensor *handle )
{
    return SUCCESS;
}
#endif

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

static int pCus_SetVideoRes( ms_cus_sensor *handle, u32 res )
{
    #if 0
    //switch(res){
        //case SENSOR_DRIVER_MODE_FULL_HD_30P_RESOLUTION:
            handle->video_res_supported.ulcur_res = 0; //TBD
            handle->pCus_sensor_init = pCus_init_HD;
            //break;

        //default:
        //    UartSendTrace("[%s] Line:%d fail. res:%d\n",__FUNCTION__, __LINE__, res);
        //    break;
    //}

    //sensor_if->WaitVEnd( 50 );
    #endif
    
    handle->video_res_supported.ulcur_res = 0; //TBD
    #if(SENSOR_MODE == SENSOR_MODE_HD_1CH)
    handle->pCus_sensor_init = pCus_init_HD_1CH;
    #endif
    #if(SENSOR_MODE == SENSOR_MODE_HD_2VC)
    handle->pCus_sensor_init = pCus_init_HD_2VC;
    #endif
    #if(SENSOR_MODE == SENSOR_MODE_FHD_1CH)
    handle->pCus_sensor_init = pCus_init_FHD_1CH;
    #endif
    #if(SENSOR_MODE == SENSOR_MODE_FHD_2VC)
    handle->pCus_sensor_init = pCus_init_FHD_2VC;
    #endif
    
    return SUCCESS;
}

static int pCus_GetOrien( ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT *orit )
{
    rn6852_params *params = ( rn6852_params * ) handle->private_data;
    return params->mirror_flip.cur;
}

static int pCus_SetOrien( ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT orit )
{
    rn6852_params *params = ( rn6852_params * ) handle->private_data;
    params->mirror_flip.new_setting = orit;
    //DoMirror( handle, params->mirror_flip.new_setting );
    return SUCCESS;
}

static int pCus_GetFPS( ms_cus_sensor *handle )
{
    rn6852_params *params = ( rn6852_params * ) handle->private_data;
    SENSOR_DMSG("[%s] FPS %d\n", __FUNCTION__, params->expo.fps);
    return params->expo.fps;
}

static int pCus_SetFPS( ms_cus_sensor *handle, u32 fps )
{
    return SUCCESS;
}

static int pCus_GetSensorCap( ms_cus_sensor *handle, CUS_CAMSENSOR_CAP *cap )
{
    return SUCCESS;
}

static int pCus_AEStatusNotify( ms_cus_sensor *handle, CUS_CAMSENSOR_AE_STATUS_NOTIFY status )
{
    return SUCCESS;
}

static int pCus_GetAEUSecs( ms_cus_sensor *handle, u32 *us )
{
    return SUCCESS;

}

static int pCus_SetAEUSecs( ms_cus_sensor *handle, u32 us )
{
    return SUCCESS;
}

// Gain: 1x = 1024
static int pCus_GetAEGain( ms_cus_sensor *handle, u32* gain )
{
    return SUCCESS;
}

static int pCus_SetAEGain_cal( ms_cus_sensor *handle, u32 gain )
{
    return SUCCESS;
}

static int pCus_SetAEGain( ms_cus_sensor *handle, u32 gain )
{
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
    return SUCCESS;
}

static int RN6852_GetShutterInfo( struct __ms_cus_sensor* handle, CUS_SHUTTER_INFO *info )
{
     return SUCCESS;
}

static int pCus_Sensor_GetSrcType(ms_cus_sensor *handle, CUS_SNR_ANADEC_SRC_TYPE *psrc_type)
{
	#define VIDEOINPUTREG 0x01
	#define DETECTREG     0x03
	#define PAGEREG       0x40
	#define PAGEVIN4      0x03
	#define PAGEVIN3      0x02
	//#define PAGEVIN2      0x01
	//#define PAGEVIN1      0x00
	#define RES_HD60     0x00
	#define RES_HD50     0x01
	#define RES_FHD30    0x02
	#define RES_FHD25    0x03
	#define RES_HD30     0x04
	#define RES_HD25     0x05
	unsigned short usCnntStatus4, usCnntStatus3, usCurRes4, usCurRes3;
	//for current application,this function only detect VIN4 and VIN3. TBD.
	*psrc_type = CUS_SNR_ANADEC_SRC_NO_READY;

#if 0
	//switch VIN4
	if(SUCCESS != SensorReg_Write(PAGEREG, PAGEVIN4)){
		*psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
	}
	//Read Page 0x01.
    if (SUCCESS != SensorReg_Read(VIDEOINPUTREG, &usCnntStatus4)) {
        *psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
    }
	//Read Page 0x03.
	if (SUCCESS != SensorReg_Read(DETECTREG, &usCurRes4)) {
        *psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
    }
	//switch VIN3
	if(SUCCESS != SensorReg_Write(PAGEREG, PAGEVIN3)){
		*psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
	}
	//Read Page 0x01.
    if (SUCCESS != SensorReg_Read(VIDEOINPUTREG, &usCnntStatus3)) {
        *psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
    }
	//Read Page 0x03.
	if (SUCCESS != SensorReg_Read(DETECTREG, &usCurRes3)) {
        *psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
    }
	//mapping , VIN4:Prm, VIN3:SCD
	if(usCnntStatus4 == 0x7e)
	{
		if((usCurRes4&0x07) == RES_HD60 ||
		   (usCurRes4&0x07) == RES_HD50 ||
		   (usCurRes4&0x07) == RES_HD30 ||
		   (usCurRes4&0x07) == RES_HD25){
			*psrc_type = CUS_SNR_ANADEC_SRC_HD;
		}
		else if((usCurRes4&0x07) == RES_FHD30 ||
		   		(usCurRes4&0x07) == RES_FHD25){
			*psrc_type = CUS_SNR_ANADEC_SRC_FHD;
		}
	}
	else if (usCnntStatus3 == 0x7e)
	{
		if((usCurRes3&0x07) == RES_HD60 ||
		   (usCurRes3&0x07) == RES_HD50 ||
		   (usCurRes3&0x07) == RES_HD30 ||
		   (usCurRes3&0x07) == RES_HD25){
			*psrc_type = CUS_SNR_ANADEC_SRC_HD;
		}
		else if((usCurRes3&0x07) == RES_FHD30 ||
		   		(usCurRes3&0x07) == RES_FHD25){
			*psrc_type = CUS_SNR_ANADEC_SRC_FHD;
		}
	}
	else
	{
		*psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
	}
#else
    unsigned short usCnntStatus;
    unsigned short usRegVal;
    unsigned short usCnntStatus1;
    unsigned short usRegVal1;

    //switch Page ch0
    if(SUCCESS != SensorReg_Write(0xFF, 0x00)){
		*psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
	}
    //Read reg 0x00.
    if (SUCCESS != SensorReg_Read(0x00, &usCnntStatus)) {
        *psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
    }

    //Read reg 0x4B.
    if (SUCCESS != SensorReg_Read(0x4B, &usRegVal)) {
        *psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
    }
    
    //UartSendTrace("usCnntStatus ch0 =0x%X\n", usCnntStatus);
    //UartSendTrace("Reg0x4B ch0 =0x%X\n", usRegVal);

    if(SUCCESS != SensorReg_Write(0xFF, 0x01)){
		*psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
	}
    //Read reg 0x00.
    if (SUCCESS != SensorReg_Read(0x00, &usCnntStatus1)) {
        *psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
    }

    //Read reg 0x4B.
    if (SUCCESS != SensorReg_Read(0x4B, &usRegVal1)) {
        *psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
    }
    
    //UartSendTrace("usCnntStatus1 ch1 =0x%X\n", usCnntStatus1);
    //UartSendTrace("Reg0x4B ch1 =0x%X\n", usRegVal1);

    #if 0 //Dump
    {
        unsigned short usPage, usRegVal, i, j;
        static unsigned short Test = 0;

        Test++;
        
        if(Test%0xFF == 32) {
            usPage = 0;
            SensorReg_Write(0xFF, usPage);
            UartSendTrace("Page %d\n", usPage);
        
            for(i=0; i<=0xF; i++) {
                UartSendTrace("0x%2X: ", i*16);
                for(j=0;j<=0xF;j++) {
                    SensorReg_Read(i*16+j, &usRegVal);
                    UartSendTrace("0x%2X ", usRegVal);
                }
                UartSendTrace("\n");
            }

            usPage = 1;
            SensorReg_Write(0xFF, usPage);
            UartSendTrace("Page %d\n", usPage);
        
            for(i=0; i<=0xF; i++) {
                UartSendTrace("0x%2X: ", i*16);
                for(j=0;j<=0xF;j++) {
                    SensorReg_Read(i*16+j, &usRegVal);
                    UartSendTrace("0x%2X ", usRegVal);
                }
                UartSendTrace("\n");
            }

            usPage = 8;
            SensorReg_Write(0xFF, usPage);
            UartSendTrace("Page %d\n", usPage);
        
            for(i=0; i<=0xF; i++) {
                UartSendTrace("0x%2X: ", i*16);
                for(j=0;j<=0xF;j++) {
                    SensorReg_Read(i*16+j, &usRegVal);
                    UartSendTrace("0x%2X ", usRegVal);
                }
                UartSendTrace("\n");
            }

            usPage = 9;
            SensorReg_Write(0xFF, usPage);
            UartSendTrace("Page %d\n", usPage);
        
            for(i=0; i<=0xF; i++) {
                UartSendTrace("0x%2X: ", i*16);
                for(j=0;j<=0xF;j++) {
                    SensorReg_Read(i*16+j, &usRegVal);
                    UartSendTrace("0x%2X ", usRegVal);
                }
                UartSendTrace("\n");
            }
        }
    }
    #endif
    
    #if(SENSOR_MODE == SENSOR_MODE_HD_2VC)
    if(usCnntStatus == 0x25 || usCnntStatus1 == 0x25){
    	*psrc_type = CUS_SNR_ANADEC_SRC_HD;
    }
    #elif (SENSOR_MODE == SENSOR_MODE_FHD_2VC)
    *psrc_type = CUS_SNR_ANADEC_SRC_FHD;
    #endif
#endif
}

int rn6852_MIPI_cus_camsensor_init_handle( ms_cus_sensor* drv_handle )
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
    sprintf(str, "RN6852");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(rn6852_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (rn6852_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(rn6852_params));
#else
    handle->private_data = calloc( 1, sizeof(rn6852_params) );
#endif

    rn6852_params *params = ( rn6852_params * ) handle->private_data;

    sprintf( handle->model_id, SENSOR_MODEL_ID );
    handle->isp_type = SENSOR_ISP_TYPE;
    handle->sif_bus = SENSOR_IFBUS_TYPE;
    handle->data_prec = SENSOR_DATAPREC;
    handle->data_mode = SENSOR_DATAMODE;
    handle->bayer_id = SENSOR_BAYERID;
    handle->orient = SENSOR_ORIT;
    
    handle->interface_attr.attr_mipi.mipi_lane_num = SENSOR_MIPI_LANE_NUM;
    handle->interface_attr.attr_mipi.mipi_data_format = CUS_SEN_INPUT_FORMAT_YUV422; //CUS_SEN_INPUT_FORMAT_RGB; // RGB pattern.
    handle->interface_attr.attr_mipi.mipi_yuv_order = CUS_SENSOR_YUV_ORDER_YC;//0; //don't care in RGB pattern. //???
    handle->interface_attr.attr_mipi.mipi_hsync_mode = SENSOR_MIPI_HSYNC_MODE;
    handle->interface_attr.attr_mipi.mipi_sampling_delay = SENSOR_MIPI_DELAY;

    #if((SENSOR_MODE == SENSOR_MODE_HD_1CH) || (SENSOR_MODE == SENSOR_MODE_FHD_1CH))
    handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_NONE;
    handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 0;
    #else
    handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_DCG; //???
    handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 0; //Short frame //???
    #endif
    handle->interface_attr.attr_mipi.pCus_sensor_mipi_get_src_type = pCus_Sensor_GetSrcType;
	
    handle->video_res_supported.num_res = 1;
    handle->video_res_supported.ulcur_res = 0; //default resolution index is 0.
    handle->video_res_supported.res[0].width = Preview_WIDTH;
    handle->video_res_supported.res[0].height = Preview_HEIGHT;
    handle->video_res_supported.res[0].max_fps = Preview_MAX_FPS;
    handle->video_res_supported.res[0].min_fps = Preview_MIN_FPS;
    handle->video_res_supported.res[0].crop_start_x= Preview_CROP_START_X;
    handle->video_res_supported.res[0].crop_start_y= Preview_CROP_START_Y;
    handle->video_res_supported.res[0].nOutputWidth= Preview_WIDTH;
    handle->video_res_supported.res[0].nOutputHeight= Preview_HEIGHT;

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
    handle->pCus_sensor_release = rn6852_MIPI_cus_camsensor_release_handle;

    #if(SENSOR_MODE == SENSOR_MODE_HD_1CH)
    handle->pCus_sensor_init = pCus_init_HD_1CH;
    #endif
    #if(SENSOR_MODE == SENSOR_MODE_HD_2VC)
    handle->pCus_sensor_init = pCus_init_HD_2VC;
    #endif
    #if(SENSOR_MODE == SENSOR_MODE_FHD_1CH)
    handle->pCus_sensor_init = pCus_init_FHD_1CH;
    #endif
    #if(SENSOR_MODE == SENSOR_MODE_FHD_2VC)
    handle->pCus_sensor_init = pCus_init_FHD_2VC;
    #endif

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
    handle->pCus_sensor_SetPatternMode = rn6852_SetPatternMode;

    handle->pCus_sensor_AEStatusNotify = pCus_AEStatusNotify;
    handle->pCus_sensor_GetAEUSecs = pCus_GetAEUSecs;
    handle->pCus_sensor_SetAEUSecs = pCus_SetAEUSecs;
    handle->pCus_sensor_GetAEGain = pCus_GetAEGain;
    handle->pCus_sensor_SetAEGain_cal = pCus_SetAEGain_cal;
    handle->pCus_sensor_SetAEGain = pCus_SetAEGain;

    handle->pCus_sensor_GetAEMinMaxGain = pCus_GetAEMinMaxGain;
    handle->pCus_sensor_GetAEMinMaxUSecs = pCus_GetAEMinMaxUSecs;
    handle->pCus_sensor_GetDGainRemainder = pCus_GetDGainRemainder;
    handle->pCus_sensor_GetShutterInfo = RN6852_GetShutterInfo;
    handle->pCus_sensor_setCaliData_gain_linearity = pCus_setCaliData_gain_linearity;

    handle->pCus_sensor_I2CWrite = pCus_I2CWrite; 
    handle->pCus_sensor_I2CRead = pCus_I2CRead; 

    params->expo.vts = vts_30fps;
    params->expo.fps = 30;
    params->reg_dirty = false;
    params->reg_dirty_cnt = 0;

    handle->snr_pad_group = SENSOR_PAD_GROUP_SET;

    handle->channel_num = SENSOR_CHANNEL_NUM;
    handle->channel_mode = SENSOR_CHANNEL_MODE_LINEAR;

    return SUCCESS;
}

#if((SENSOR_MODE == SENSOR_MODE_HD_2VC) || (SENSOR_MODE == SENSOR_MODE_FHD_2VC))
int rn6852_MIPI_cus_camsensor_init_handle_vc2( ms_cus_sensor* drv_handle )
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
    sprintf(str, "RN6852");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(rn6852_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (rn6852_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(rn6852_params));
#else
    handle->private_data = calloc( 1, sizeof(rn6852_params) );
#endif

    rn6852_params *params = ( rn6852_params * ) handle->private_data;

    sprintf( handle->model_id, SENSOR_MODEL_ID );
    handle->isp_type = SENSOR_ISP_TYPE;
    handle->sif_bus = SENSOR_IFBUS_TYPE;
    handle->data_prec = SENSOR_DATAPREC;
    handle->data_mode = SENSOR_DATAMODE;
    handle->bayer_id = SENSOR_BAYERID;
    handle->orient = SENSOR_ORIT;
    
    handle->interface_attr.attr_mipi.mipi_lane_num = SENSOR_MIPI_LANE_NUM;
    handle->interface_attr.attr_mipi.mipi_data_format = CUS_SEN_INPUT_FORMAT_YUV422; //CUS_SEN_INPUT_FORMAT_RGB; // RGB pattern.
    handle->interface_attr.attr_mipi.mipi_yuv_order = CUS_SENSOR_YUV_ORDER_YC;//0; //don't care in RGB pattern. //???
    handle->interface_attr.attr_mipi.mipi_hsync_mode = SENSOR_MIPI_HSYNC_MODE;
    handle->interface_attr.attr_mipi.mipi_sampling_delay = SENSOR_MIPI_DELAY;

    //#if((SENSOR_MODE == SENSOR_MODE_HD_1CH) || (SENSOR_MODE == SENSOR_MODE_FHD_1CH))
    //handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_NONE; //???
    //handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 1; //Short frame //???
    //#else
    handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_DCG; //???
    handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 1; //Short frame //???
    //#endif
    
    handle->video_res_supported.num_res = 1;
    handle->video_res_supported.ulcur_res = 0; //default resolution index is 0.
    handle->video_res_supported.res[0].width = Preview_WIDTH;
    handle->video_res_supported.res[0].height = Preview_HEIGHT;
    handle->video_res_supported.res[0].max_fps = Preview_MAX_FPS;
    handle->video_res_supported.res[0].min_fps = Preview_MIN_FPS;
    handle->video_res_supported.res[0].crop_start_x= Preview_CROP_START_X;
    handle->video_res_supported.res[0].crop_start_y= Preview_CROP_START_Y;
    handle->video_res_supported.res[0].nOutputWidth= Preview_WIDTH;
    handle->video_res_supported.res[0].nOutputHeight= Preview_HEIGHT;

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
    handle->pCus_sensor_release = rn6852_MIPI_cus_camsensor_release_handle;

    handle->pCus_sensor_init = pCus_init_Null;

    handle->pCus_sensor_poweron = pCus_poweron_Null;
    handle->pCus_sensor_poweroff = pCus_poweroff_Null;

    handle->pCus_sensor_GetSensorID = pCus_GetSensorID;
    handle->pCus_sensor_GetVideoResNum = pCus_GetVideoResNum;
    handle->pCus_sensor_GetVideoRes = pCus_GetVideoRes;
    handle->pCus_sensor_SetVideoRes = pCus_SetVideoRes;
    handle->pCus_sensor_GetOrien = pCus_GetOrien;
    handle->pCus_sensor_SetOrien = pCus_SetOrien;
    handle->pCus_sensor_GetFPS = pCus_GetFPS;
    handle->pCus_sensor_SetFPS = pCus_SetFPS;
    handle->pCus_sensor_GetSensorCap = pCus_GetSensorCap;
    handle->pCus_sensor_SetPatternMode = rn6852_SetPatternMode;

    handle->pCus_sensor_AEStatusNotify = pCus_AEStatusNotify;
    handle->pCus_sensor_GetAEUSecs = pCus_GetAEUSecs;
    handle->pCus_sensor_SetAEUSecs = pCus_SetAEUSecs;
    handle->pCus_sensor_GetAEGain = pCus_GetAEGain;
    handle->pCus_sensor_SetAEGain_cal = pCus_SetAEGain_cal;
    handle->pCus_sensor_SetAEGain = pCus_SetAEGain;

    handle->pCus_sensor_GetAEMinMaxGain = pCus_GetAEMinMaxGain;
    handle->pCus_sensor_GetAEMinMaxUSecs = pCus_GetAEMinMaxUSecs;
    handle->pCus_sensor_GetDGainRemainder = pCus_GetDGainRemainder;
    handle->pCus_sensor_GetShutterInfo = RN6852_GetShutterInfo;
    handle->pCus_sensor_setCaliData_gain_linearity = pCus_setCaliData_gain_linearity;

    handle->pCus_sensor_I2CWrite = pCus_I2CWrite; 
    handle->pCus_sensor_I2CRead = pCus_I2CRead; 

    params->expo.vts = vts_30fps;
    params->expo.fps = 30;
    params->reg_dirty = false;
    params->reg_dirty_cnt = 0;

    handle->snr_pad_group = SENSOR_PAD_GROUP_SET;

    handle->channel_num = SENSOR_CHANNEL_NUM+1;
    handle->channel_mode = SENSOR_CHANNEL_MODE_LINEAR;

    return SUCCESS;
}
#endif //((SENSOR_MODE == SENSOR_MODE_HD_2VC) || (SENSOR_MODE == SENSOR_MODE_FHD_2VC))

int rn6852_MIPI_cus_camsensor_release_handle( ms_cus_sensor *handle )
{
#if defined(__RTK_OS__)
    CamOsRet_e                  eCamOsRet = CAM_OS_OK;
#endif

    if( handle && handle->private_data )
    {
        SENSOR_IMSG("[%s] release handle 0x%x, private data %x\n",__FUNCTION__,(int)handle,(int)handle->private_data);
#if defined(__RTK_OS__)
        eCamOsRet = CamOsDirectMemRelease((void*)handle->private_data, sizeof(rn6852_params));
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
struct SensorMapTable_t gsensor_map_rn6852[] = {
    { //Channel 0
        SENSOR_CHANNEL_NUM,
        rn6852_MIPI_cus_camsensor_init_handle,
        rn6852_MIPI_cus_camsensor_release_handle
    },
    #if((SENSOR_MODE == SENSOR_MODE_HD_2VC) || (SENSOR_MODE == SENSOR_MODE_FHD_2VC))
    { //Channel 1
        SENSOR_CHANNEL_NUM+1,
        rn6852_MIPI_cus_camsensor_init_handle_vc2,
        rn6852_MIPI_cus_camsensor_release_handle
    },
    #endif
};

int RN6852_Module_Init(void)
{
    cameraSensorRegister(&gsensor_map_rn6852[0]);
    #if((SENSOR_MODE == SENSOR_MODE_HD_2VC) || (SENSOR_MODE == SENSOR_MODE_FHD_2VC))
    cameraSensorRegister(&gsensor_map_rn6852[1]);
    #endif
    MMPF_SetRawStoreNum(2);
    MMPF_SetANACamType(ANA_CAM_2I1O);
    return 0;
}

void RN6852_Module_Exit(void)
{
    cameraSensorUnRegister(&gsensor_map_rn6852[0]);
    #if((SENSOR_MODE == SENSOR_MODE_HD_2VC) || (SENSOR_MODE == SENSOR_MODE_FHD_2VC))
    cameraSensorUnRegister(&gsensor_map_rn6852[1]);
    #endif
}

#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(RN6852_Module_Init);
//ait_module_exit(RN6852_Module_Exit);
#endif //#if defined(__RTK_OS__)

#endif //#if defined(BIND_SENSOR_RN6852_MIPI) && (BIND_SENSOR_RN6852_MIPI == 1)
