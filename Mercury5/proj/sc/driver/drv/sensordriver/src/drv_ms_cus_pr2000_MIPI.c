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
#if (SENSOR0 == PR2000)
#define BIND_SENSOR_PR2000 (1)
#endif
#endif //#if defined(__RTK_OS__)

#if defined(BIND_SENSOR_PR2000) && (BIND_SENSOR_PR2000 == 1)

#define SENSOR_PAD_GROUP_SET CUS_SENSOR_PAD_GROUP_A
#define SENSOR_CHANNEL_NUM (0)
#define SENSOR_CHANNEL_MODE CUS_SENSOR_CHANNEL_MODE_REALTIME_ISP_BYPASS

//============================================
//MIPI config begin.
#define SENSOR_MIPI_LANE_NUM (4)
#define PR2000_TEST_PATTERN            (0)
//MIPI config end.
//============================================

#define SENSOR_MODEL_ID     "PR2000_MIPI"
#define SENSOR_ISP_TYPE     ISP_EXT                   //ISP_EXT, ISP_SOC
#define SENSOR_IFBUS_TYPE   CUS_SENIF_BUS_MIPI      //CFG //CUS_SENIF_BUS_PARL, CUS_SENIF_BUS_MIPI
#define SENSOR_MIPI_HSYNC_MODE PACKET_HEADER_EDGE1
#define SENSOR_MIPI_DELAY   0x1212                  //CFG
#define SENSOR_DATAPREC     CUS_DATAPRECISION_16 //CUS_DATAPRECISION_12   //CFG //CUS_DATAPRECISION_8, CUS_DATAPRECISION_10
#define SENSOR_DATAMODE     CUS_SEN_10TO12_9000     //CFG
#define SENSOR_BAYERID      CUS_BAYER_RG            //CFG //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
#define SENSOR_ORIT         CUS_ORIT_M0F0           //CUS_ORIT_M0F0, CUS_ORIT_M1F0, CUS_ORIT_M0F1, CUS_ORIT_M1F1,
#define SENSOR_MAX_GAIN     (64 * 1024)//65536
#define SENSOR_MIN_GAIN      (2 * 1024)//2048
#define SENSOR_GAIN_DELAY_FRAME_COUNT      (2)
#define SENSOR_SHUTTER_DELAY_FRAME_COUNT      (2)

#define MOVIE_SIZE_1080P25    (0)
#define MOVIE_SIZE_720P30     (1)

#define SENSOR_OUTPUT_MOVIE_SIZE            (MOVIE_SIZE_720P30)

#define Preview_MCLK_SPEED  CUS_CMU_CLK_27MHZ        //CFG //CUS_CMU_CLK_12M, CUS_CMU_CLK_16M, CUS_CMU_CLK_24M, CUS_CMU_CLK_27M
#define Preview_line_period 29626                  ////HTS/PCLK=2420 pixels/80MHZ=30.250us
#define Prv_Max_line_number 1080                    //maximum exposure line munber of sensor when preview
#define vts_30fps  1125                                 //Virt Total Size , 30.25us * 1111 =  33.6ms frame interval =30 fps


#if (SENSOR_MIPI_LANE_NUM == 4)
#if (SENSOR_OUTPUT_MOVIE_SIZE == MOVIE_SIZE_1080P25)
#define Preview_WIDTH       1920                    //resolution Width when preview
#else
#define Preview_WIDTH       1280                    //resolution Width when preview
#endif
#endif
#if (SENSOR_MIPI_LANE_NUM == 2)
#define Preview_WIDTH       1280                    //resolution Width when preview
#endif

#if (SENSOR_OUTPUT_MOVIE_SIZE == MOVIE_SIZE_1080P25)
#define Preview_HEIGHT      1080                    //resolution Height when preview
#else
#define Preview_HEIGHT      720                    //resolution Height when preview
#endif

#define Preview_MAX_FPS     30                     //fastest preview FPS
#define Preview_MIN_FPS     8                      //slowest preview FPS
#define Preview_CROP_START_X     1                      //CROP_START_X
#define Preview_CROP_START_Y     1                      //CROP_START_Y

#define Cap_Max_line_number 1080                   //maximum exposure line munber of sensor when capture

#define SENSOR_I2C_ADDR    0xB8                         //I2C slave address
#define SENSOR_I2C_SPEED    I2C_SLOWSPEED_MODE_200KHZ   //200KHz
#define SENSOR_I2C_CHANNEL  1                           //I2C Channel
#define SENSOR_I2C_PAD_MODE 2                           //Pad/Mode Number

#define SENSOR_I2C_LEGACY  I2C_NORMAL_MODE     //usally set CUS_I2C_NORMAL_MODE,  if use old OVT I2C protocol=> set CUS_I2C_LEGACY_MODE
#define SENSOR_I2C_FMT     I2C_FMT_A8D8        //CUS_I2C_FMT_A8D8, CUS_I2C_FMT_A8D16, CUS_I2C_FMT_A16D8, CUS_I2C_FMT_A16D16

#define SENSOR_PWDN_POL     CUS_CLK_POL_POS        // if PWDN pin High can makes sensor in power down, set CUS_CLK_POL_POS
#define SENSOR_RST_POL      CUS_CLK_POL_NEG//CUS_CLK_POL_NEG        // if RESET pin High can makes sensor in reset state, set CUS_CLK_POL_NEG

// VSYNC/HSYNC POL can be found in data sheet timing diagram,
// Notice: the initial setting may contain VSYNC/HSYNC POL inverse settings so that condition is different.

#define SENSOR_VSYNC_POL    CUS_CLK_POL_NEG//CUS_CLK_POL_POS//CUS_CLK_POL_NEG        // if VSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_HSYNC_POL    CUS_CLK_POL_POS//CUS_CLK_POL_NEG//CUS_CLK_POL_POS        // if HSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_PCLK_POL     CUS_CLK_POL_POS        // depend on sensor setting, sometimes need to try CUS_CLK_POL_POS or CUS_CLK_POL_NEG

int pr2000_MIPI_cus_camsensor_release_handle( ms_cus_sensor *handle );

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
} pr2000_params;

static I2C_ARRAY Sensor_id_table[] =
{

};

#if (SENSOR_MIPI_LANE_NUM == 4)
static I2C_ARRAY Sensor_init_table_4lane_1280x720_30fps[] =
{
    //Camera:5(HDT_NEW), cameraResolution:4(camera_1280x720p30), videoResolution:6(video_1280x720p30), MIPI
    //   [CHIP1]:I2C SlvAddr(0x5d)
    //    vinMode(0:[Differential|VinPN], 1:VinP, 3:VinN): 1
    //    vidOutMode(0:pararllel, 2:mipi_2lane(~HD), 4:mipi_4lane(~FHD): 4
    //    cascade(0:no, 1:cascade): 0
    //    cascadeMux(If cascade, 0:single(slave), 1:mux(master)): 0
    //    chid_num(If cascade, 0:master, 1:slave): 0
    //    bt656(If parallel, 0:bt1120(8bit), 1:bt656(8bit)): 0
    //    datarate(If parallel, 0:148.5Mhz, 1:74.25Mhz, 2:36Mhz, 3:27Mhz): 0
    //    clkphase_Mux(If parallel & cascadeMux, clkphase:0~15): 0
    //    clkphase_148Mhz(If parallel & datarate=0, clkphase:0~15): 0
    //    clkphase_74Mhz(If parallel & datarate=1, clkphase:0~15): 0
    //    clkphase_36Mhz(If parallel & datarate=2, clkphase:0~3): 0
    //    clkphase_27Mhz(If parallel & datarate=3, clkphase:0~3): 0
    ///////////////////////////////////////////////
    /// slv, addr, data/////////////////////

    //                      If CHIP_ID(0x2000) is invalid, reload i2c slave address of all pr2000 chips like below.
    //> 0xb8, 0xff, 0x00]
    //> 0xb8, 0xa1, 0xff]
    //> 0xba, 0xff, 0x00]
    //> 0xba, 0xa1, 0xff]
    //> 0xbc, 0xff, 0x00]
    //> 0xbc, 0xa1, 0xff]
    //> 0xbe, 0xff, 0x00]
    //> 0xbe, 0xa1, 0xff]
    //> 0xb8, 0xff, 0x80]
    //> 0xba, 0xff, 0x80]
    //> 0xbc, 0xff, 0x80]
    //> 0xbe, 0xff, 0x80]

    //                      Page0 sys
    {0xff, 0x00},
    {0x10, 0xda},
    {0x11, 0x00},
    {0x12, 0x00},
    {0x13, 0x00},
    {0x14, 0x21},    //b[1:0] => Select Camera Input. VinP(1), VinN(3), Differ(0).
    {0x15, 0x44},
    {0x16, 0x0d},
    {0x40, 0x40},
    {0x41, 0x08},
    {0x42, 0x00},
    {0x43, 0x00},
    {0x47, 0xba},
    {0x48, 0x00},//{0x48, 0x10},
    {0x49, 0x0a},
    {0x4e, 0x40},
    {0x80, 0x56},
    {0x81, 0x0e},
    {0x82, 0x0d},
    {0x84, 0x30},
    {0x86, 0x30},
    {0x87, 0x00},
    {0x8a, 0x00},
    {0x90, 0x00},
    {0x91, 0x00},
    {0x92, 0x00},
    {0x94, 0x00},
    {0x95, 0x80},
    {0x96, 0x00},
    {0xa0, 0x01},
    {0xa1, 0xe3},
    {0xa4, 0x01},
    {0xa5, 0xe3},
    {0xa6, 0x00},
    {0xa7, 0x12},
    {0xa8, 0x00},
    {0xd0, 0x30},
    {0xd1, 0x08},
    {0xd2, 0x21},
    {0xd3, 0x00},
    {0xd8, 0x37},
    {0xd9, 0x08},
    {0xda, 0x21},
    {0xe0, 0x19},
    {0xe1, 0x40},
    {0xe2, 0x1C},//{0xe2, 0x18},
    {0xe3, 0x00},
    {0xe4, 0x00},
    {0xe5, 0x0c},
    {0xe6, 0x00},
    {0xea, 0x00},
    {0xeb, 0x00},
    {0xf1, 0x44},
    {0xf2, 0x01},

    //Page1 vdec
    {0xff, 0x01},
    {0x00, 0xe4},
    {0x01, 0x61},
    {0x02, 0x00},
    {0x03, 0x57},
    {0x04, 0x0c},
    {0x05, 0x88},
    {0x06, 0x04},
    {0x07, 0xb2},
    {0x08, 0x44},
    {0x09, 0x34},
    {0x0a, 0x02},
    {0x0b, 0x14},
    {0x0c, 0x04},
    {0x0d, 0x08},
    {0x0e, 0x5e},
    {0x0f, 0x5e},
    {0x10, 0x26},
    {0x11, 0x01},
    {0x12, 0x45},
    {0x13, 0x68},
    {0x14, 0x00},
    {0x15, 0x18},
    {0x16, 0xd0},
    {0x17, 0x00},
    {0x18, 0x41},
    {0x19, 0x46},
    {0x1a, 0x22},
    {0x1b, 0x07},
    {0x1c, 0xe9},
    {0x1d, 0x45},
    {0x1e, 0x40},
    {0x1f, 0x00},
    {0x20, 0x80},
    {0x21, 0x80},
    {0x22, 0x80},
    {0x23, 0x80},
    {0x24, 0xc0},
    {0x25, 0xc0},
    {0x26, 0x80},
    {0x27, 0x80},
    {0x28, 0x00},
    {0x29, 0x7f},
    {0x2a, 0xff},
    {0x2b, 0x00},
    {0x2c, 0x00},
    {0x2d, 0x00},
    {0x2e, 0x02},
    {0x2f, 0xc0},
    {0x30, 0x00},
    {0x31, 0x00},
    {0x32, 0xc0},
    {0x33, 0x14},
    {0x34, 0x14},
    {0x35, 0x80},
    {0x36, 0x80},
    {0x37, 0x00},
    {0x38, 0x40},
    {0x39, 0x04},
    {0x3a, 0x07},
    {0x3b, 0x02},
    {0x3c, 0x01},
    {0x3d, 0x22},
    {0x3e, 0x01},
    {0x3f, 0xc4},
    {0x40, 0x05},
    {0x41, 0x11},
    {0x42, 0x01},
    {0x43, 0x34},
    {0x44, 0x6a},
    {0x45, 0x00},
    {0x46, 0x12},
    {0x47, 0x2f},
    {0x48, 0x24},
    {0x49, 0x08},
    {0x4a, 0x6c},
    {0x4b, 0x60},
    {0x4c, 0x00},
    {0x4d, 0x22},
    {0x4e, 0x00},
#if (PR2000_TEST_PATTERN)
    {0x4f, 0x10},
#else
    {0x4f, 0x00},
#endif
    {0x50, 0xc6},
    {0x51, 0x28},
    {0x52, 0x40},
    {0x53, 0x0c},
    {0x54, 0x0f},
    {0x55, 0x8d},
    {0x70, 0x06},
    {0x71, 0x08},
    {0x72, 0x0a},
    {0x73, 0x0c},
    {0x74, 0x0e},
    {0x75, 0x10},
    {0x76, 0x12},
    {0x77, 0x14},
    {0x78, 0x06},
    {0x79, 0x08},
    {0x7a, 0x0a},
    {0x7b, 0x0c},
    {0x7c, 0x0e},
    {0x7d, 0x10},
    {0x7e, 0x12},
    {0x7f, 0x14},
    {0x80, 0x00},
    {0x81, 0x09},
    {0x82, 0x00},
    {0x83, 0x07},
    {0x84, 0x00},
    {0x85, 0x14},
    {0x86, 0x03},
    {0x87, 0x36},
    {0x88, 0x0a},
    {0x89, 0x62},
    {0x8a, 0x0a},
    {0x8b, 0x62},
    {0x8c, 0x0b},
    {0x8d, 0xe0},
    {0x8e, 0x06},
    {0x8f, 0x66},
    {0x90, 0x06},
    {0x91, 0xd1},
    {0x92, 0x73},
    {0x93, 0x39},
    {0x94, 0x0f},
    {0x95, 0x5e},
    {0x96, 0x09},
    {0x97, 0x26},
    {0x98, 0x1c},
    {0x99, 0x20},
    {0x9a, 0x17},
    {0x9b, 0x70},
    {0x9c, 0x0e},
    {0x9d, 0x10},
    {0x9e, 0x0b},
    {0x9f, 0xb8},
    {0xa0, 0x01},
    {0xa1, 0xc2},
    {0xa2, 0x01},
    {0xa3, 0xb8},
    {0xa4, 0x00},
    {0xa5, 0xe1},
    {0xa6, 0x00},
    {0xa7, 0xc6},
    {0xa8, 0x01},
    {0xa9, 0x7c},
    {0xaa, 0x01},
    {0xab, 0x7c},
    {0xac, 0x00},
    {0xad, 0xea},
    {0xae, 0x00},
    {0xaf, 0xea},
    {0xb0, 0x09},
    {0xb1, 0xaa},
    {0xb2, 0x0f},
    {0xb3, 0xae},
    {0xb4, 0x00},
    {0xb5, 0x17},
    {0xb6, 0x08},
    {0xb7, 0xe8},
    {0xb8, 0xb0},
    {0xb9, 0xce},
    {0xba, 0x90},
    {0xbb, 0x03},
    {0xbc, 0x00},
    {0xbd, 0x00},
    {0xbe, 0x05},
    {0xbf, 0x00},//{0xbf, 0x08},
    {0xc0, 0x00},
    {0xc1, 0x1B},//{0xc1, 0x00},//{0xc1, 0x19},
    {0xc2, 0x02},
    {0xc3, 0xd0},

    //{0xff, 0x01},
    {0x54, 0x0e},
    //{0xff, 0x01},
    {0x54, 0x0f},


#if (PR2000_TEST_PATTERN)
    //Page2 for Test Pattern
    {0xff, 0x02},

    {0x80, 0xB8},
#endif
    // Stop mipi 4lane
    //{0xff, 0x00},
    //{0x47, 0x3a},
    //{0xff, 0x00},
    //{0x40, 0x00},
    //{0xff, 0x00},
    //{0x4e, 0x7f},

    // Start mipi 4lane
    {0xff, 0x00},
    {0x40, 0x00},
    //{0xff, 0x00},
    {0x4e, 0x40},
    //{0xff, 0x00},
    {0x40, 0x40},
    //{0xff, 0x00},
    {0x4e, 0x60},
    //{0xff, 0x00},
    {0x4e, 0x40},
    //{0xff, 0x00},
    {0x47, 0xba},
    ///////////////////////////////////////////////
};

static I2C_ARRAY Sensor_init_table_4lane_1920x1080_25fps[] =
{
    //                      Page0 sys
    {0xff, 0x00},
    {0x10, 0x83},
    {0x11, 0x07},
    {0x12, 0x00},
    {0x13, 0x00},
    {0x14, 0x21},    //b[1:0}, => Select Camera Input. VinP(1), VinN(3), Differ(0).
    {0x15, 0x44},
    {0x16, 0x0d},
    {0x40, 0x40},  //00
    {0x41, 0x08},
    {0x42, 0x00},
    {0x43, 0x00},
    {0x47, 0xba},
    {0x48, 0x00},
    {0x49, 0x0f},
    {0x4e, 0x40},
    {0x80, 0x56},
    {0x81, 0x0e},
    {0x82, 0x0d},
    {0x84, 0x30},
    {0x86, 0x20},
    {0x87, 0x00},
    {0x8a, 0x00},
    {0x90, 0x00},
    {0x91, 0x00},
    {0x92, 0x00},
    {0x94, 0xff},
    {0x95, 0xff},
    {0x96, 0xff},
    {0xa0, 0x01},
    {0xa1, 0xe8},
    {0xa4, 0x00},
    {0xa5, 0x11},
    {0xa6, 0x00},
    {0xa7, 0x81},
    {0xa8, 0x00},
    {0xd0, 0x30},
    {0xd1, 0x08},
    {0xd2, 0x21},
    {0xd3, 0x00},
    {0xd8, 0x37},
    {0xd9, 0x08},
    {0xda, 0x21},
    {0xe0, 0x15},
    {0xe1, 0x40},
    {0xe2, 0x1C}, //18
    {0xe3, 0x00},
    {0xe4, 0x00},
    {0xe5, 0x0c},
    {0xe6, 0x00},
    {0xea, 0x00},
    {0xeb, 0x00},
    {0xf1, 0x44},
    {0xf2, 0x01},

    //                      Page1 vdec
    {0xff, 0x01},
    {0x00, 0xe4},
    {0x01, 0x61},
    {0x02, 0x00},
    {0x03, 0x57},
    {0x04, 0x0c},
    {0x05, 0x88},
    {0x06, 0x04},
    {0x07, 0xb2},
    {0x08, 0x44},
    {0x09, 0x34},
    {0x0a, 0x02},
    {0x0b, 0x14},
    {0x0c, 0x04},
    {0x0d, 0x08},
    {0x0e, 0x5e},
    {0x0f, 0x5e},
    {0x10, 0x26},
    {0x11, 0x00},
    {0x12, 0x87},
    {0x13, 0x24},
    {0x14, 0x80},
    {0x15, 0x2a},
    {0x16, 0x38},
    {0x17, 0x00},
    {0x18, 0x80},
    {0x19, 0x48},
    {0x1a, 0x6c},
    {0x1b, 0x05},
    {0x1c, 0x61},
    {0x1d, 0x07},
    {0x1e, 0x7e},
    {0x1f, 0x80},
    {0x20, 0x80},
    {0x21, 0x80},
    {0x22, 0x90},
    {0x23, 0x80},
    {0x24, 0x80},
    {0x25, 0x80},
    {0x26, 0x84},
    {0x27, 0x82},
    {0x28, 0x00},
    {0x29, 0xff},
    {0x2a, 0xff},
    {0x2b, 0x00},
    {0x2c, 0x00},
    {0x2d, 0x00},
    {0x2e, 0x00},
    {0x2f, 0x00},
    {0x30, 0x00},
    {0x31, 0x00},
    {0x32, 0xc0},
    {0x33, 0x14},
    {0x34, 0x14},
    {0x35, 0x80},
    {0x36, 0x80},
    {0x37, 0xad},
    {0x38, 0x4b},
    {0x39, 0x08},
    {0x3a, 0x21},
    {0x3b, 0x02},
    {0x3c, 0x01},
    {0x3d, 0x23},
    {0x3e, 0x05},
    {0x3f, 0xc8},
    {0x40, 0x05},
    {0x41, 0x55},
    {0x42, 0x01},
    {0x43, 0x38},
    {0x44, 0x6a},
    {0x45, 0x00},
    {0x46, 0x14},
    {0x47, 0xb0},
    {0x48, 0xdf},
    {0x49, 0x00},
    {0x4a, 0x7b},
    {0x4b, 0x60},
    {0x4c, 0x00},
    {0x4d, 0x26},
    {0x4e, 0x00},
    //{0x4f, 0x04},
#if (PR2000_TEST_PATTERN)
        {0x4f, 0x10},
#else
        {0x4f, 0x00},
#endif

    {0x50, 0x01},
    {0x51, 0x28},
    {0x52, 0x40},
    {0x53, 0x0c},
    {0x54, 0x0f},
    {0x55, 0x8d},
    {0x70, 0x06},
    {0x71, 0x08},
    {0x72, 0x0a},
    {0x73, 0x0c},
    {0x74, 0x0e},
    {0x75, 0x10},
    {0x76, 0x12},
    {0x77, 0x14},
    {0x78, 0x06},
    {0x79, 0x08},
    {0x7a, 0x0a},
    {0x7b, 0x0c},
    {0x7c, 0x0e},
    {0x7d, 0x10},
    {0x7e, 0x12},
    {0x7f, 0x14},
    {0x80, 0x00},
    {0x81, 0x09},
    {0x82, 0x00},
    {0x83, 0x07},
    {0x84, 0x00},
    {0x85, 0x17},
    {0x86, 0x03},
    {0x87, 0xe5},
    {0x88, 0x05},
    {0x89, 0x24},
    {0x8a, 0x05},
    {0x8b, 0x24},
    {0x8c, 0x08},
    {0x8d, 0xe8},
    {0x8e, 0x05},
    {0x8f, 0x47},
    {0x90, 0x02},
    {0x91, 0xb4},
    {0x92, 0x73},
    {0x93, 0xe8},
    {0x94, 0x0f},
    {0x95, 0x5e},
    {0x96, 0x03},
    {0x97, 0xd0},
    {0x98, 0x17},
    {0x99, 0x34},
    {0x9a, 0x13},
    {0x9b, 0x56},
    {0x9c, 0x0b},
    {0x9d, 0x9a},
    {0x9e, 0x09},
    {0x9f, 0xab},
    {0xa0, 0x01},
    {0xa1, 0x74},
    {0xa2, 0x01},
    {0xa3, 0x6b},
    {0xa4, 0x00},
    {0xa5, 0xba},
    {0xa6, 0x00},
    {0xa7, 0xa3},
    {0xa8, 0x01},
    {0xa9, 0x39},
    {0xaa, 0x01},
    {0xab, 0x39},
    {0xac, 0x00},
    {0xad, 0xc1},
    {0xae, 0x00},
    {0xaf, 0xc1},
    {0xb0, 0x05},
    {0xb1, 0xcc},
    {0xb2, 0x09},
    {0xb3, 0x6d},
    {0xb4, 0x00},
    {0xb5, 0x17},
    {0xb6, 0x08},
    {0xb7, 0xe8},
    {0xb8, 0xb0},
    {0xb9, 0xce},
    {0xba, 0x90},
    {0xbb, 0x03},
    {0xbc, 0x00},
    {0xbd, 0x04},
    {0xbe, 0x07},
    {0xbf, 0x80},
    {0xc0, 0x00},
    {0xc1, 0x30},
    {0xc2, 0x04},
    {0xc3, 0x38},

    //{0xff, 0x01},
    {0x54, 0x0e},
    //{0xff, 0x01},
    {0x54, 0x0f},

#if (PR2000_TEST_PATTERN)
        //Page2 for Test Pattern
        {0xff, 0x02},
        {0x80, 0xB8},
#endif

    //                      Stop mipi 4lane
    //{0xff, 0x00},
    //{0x47, 0x3a},
    //{0xff, 0x00},
    //{0x40, 0x00},
    //{0xff, 0x00},
    //{0x4e, 0x7f},

    //                      Start mipi 4lane
    {0xff, 0x00},
    {0x40, 0x00},
    {0xff, 0x00},
    {0x4e, 0x40},
    {0xff, 0x00},
    {0x40, 0x40},
    {0xff, 0x00},
    {0x4e, 0x60},
    {0xff, 0x00},
    {0x4e, 0x40},
    {0xff, 0x00},
    {0x47, 0xba},

};
#endif

#if (SENSOR_MIPI_LANE_NUM == 2)
static I2C_ARRAY Sensor_init_table_2lane_1280x720_30fps[] =
{
    //Camera:5(HDT_NEW), cameraResolution:4(camera_1280x720p30), videoResolution:6(video_1280x720p30), MIPI
    //   [CHIP1]:I2C SlvAddr(0x5d)
    //    vinMode(0:[Differential|VinPN], 1:VinP, 3:VinN): 1
    //    vidOutMode(0:pararllel, 2:mipi_2lane(~HD), 4:mipi_4lane(~FHD): 2
    //    cascade(0:no, 1:cascade): 0
    //    cascadeMux(If cascade, 0:single(slave), 1:mux(master)): 0
    //    chid_num(If cascade, 0:master, 1:slave): 0
    //    bt656(If parallel, 0:bt1120(8bit), 1:bt656(8bit)): 0
    //    datarate(If parallel, 0:148.5Mhz, 1:74.25Mhz, 2:36Mhz, 3:27Mhz): 0
    //    clkphase_Mux(If parallel & cascadeMux, clkphase:0~15): 0
    //    clkphase_148Mhz(If parallel & datarate=0, clkphase:0~15): 0
    //    clkphase_74Mhz(If parallel & datarate=1, clkphase:0~15): 0
    //    clkphase_36Mhz(If parallel & datarate=2, clkphase:0~3): 0
    //    clkphase_27Mhz(If parallel & datarate=3, clkphase:0~3): 0
    ///////////////////////////////////////////////
    /// slv, addr, data/////////////////////

    //                      If CHIP_ID(0x2000) is invalid, reload i2c slave address of all pr2000 chips like below.
    //> 0xb8, 0xff, 0x00]
    //> 0xb8, 0xa1, 0xff]
    //> 0xba, 0xff, 0x00]
    //> 0xba, 0xa1, 0xff]
    //> 0xbc, 0xff, 0x00]
    //> 0xbc, 0xa1, 0xff]
    //> 0xbe, 0xff, 0x00]
    //> 0xbe, 0xa1, 0xff]
    //> 0xb8, 0xff, 0x80]
    //> 0xba, 0xff, 0x80]
    //> 0xbc, 0xff, 0x80]
    //> 0xbe, 0xff, 0x80]

    //Page0 sys
    {0xff, 0x00},
    {0x10, 0xda},
    {0x11, 0x07},
    {0x12, 0x00},
    {0x13, 0x00},
    {0x14, 0x21},    //b[1:0] => Select Camera Input. VinP(1), VinN(3), Differ(0).
    {0x15, 0x44},
    {0x16, 0x0d},
    {0x40, 0x00},
    {0x41, 0x08},
    {0x42, 0x00},
    {0x43, 0x00},
    {0x47, 0x9a},
    {0x48, 0x00},
    {0x49, 0x0a},
    {0x4e, 0x4c},
    {0x80, 0x56},
    {0x81, 0x0e},
    {0x82, 0x0d},
    {0x84, 0x30},
    {0x86, 0x20},//0x30,
    {0x87, 0x00},
    {0x8a, 0x00},
    {0x90, 0x00},
    {0x91, 0x00},
    {0x92, 0x00},
    {0x94, 0xff},
    {0x95, 0xff},
    {0x96, 0xff},

    #if 0
    {0xa0, 0x01},
    {0xa1, 0xe8},
    {0xa4, 0x00},
    {0xa5, 0x11},
    {0xa6, 0x00},
    {0xa7, 0x81},
    {0xa8, 0x00},
    #else
    //18V
    {0xa0, 0x00},
    {0xa1, 0x20},
    {0xa4, 0x01},
    {0xa5, 0xE3},
    {0xa6, 0x00},
    {0xa7, 0x12},
    {0xa8, 0x00},
    #endif

    {0xd0, 0x30},
    {0xd1, 0x08},
    {0xd2, 0x21},
    {0xd3, 0x00},
    {0xd8, 0x37},
    {0xd9, 0x08},
    {0xda, 0x21},//0x18,//0x21,
    {0xe0, 0x19},
    {0xe1, 0x10},//0x10,//lucas
    {0xe2, 0x1C},
    {0xe3, 0x00},
    {0xe4, 0x00},
    {0xe5, 0x0c},
    {0xe6, 0x00},
    {0xea, 0x00},
    {0xeb, 0x00},
    {0xf1, 0x44},
    {0xf2, 0x01},

    //Page1 vdec
    {0xff, 0x01},
    {0x00, 0xe4},
    {0x01, 0x61},
    {0x02, 0x00},
    {0x03, 0x57},
    {0x04, 0x0c},
    {0x05, 0x88},
    {0x06, 0x04},
    {0x07, 0xb2},
    {0x08, 0x44},
    {0x09, 0x34},
    {0x0a, 0x02},
    {0x0b, 0x14},
    {0x0c, 0x04},
    {0x0d, 0x08},
    {0x0e, 0x5e},
    {0x0f, 0x5e},
    {0x10, 0x26},
    {0x11, 0x01},
    {0x12, 0x45},
    {0x13, 0x68},
    {0x14, 0x00},
    {0x15, 0x18},
    {0x16, 0xd0},
    {0x17, 0x00},
    {0x18, 0x41},
    {0x19, 0x46},
    {0x1a, 0x22},
    {0x1b, 0x07},
    {0x1c, 0xe9},
    {0x1d, 0x45},
    {0x1e, 0x40},
    {0x1f, 0x00},
    {0x20, 0x80},
    {0x21, 0x80},
    {0x22, 0x80},
    {0x23, 0x80},
    {0x24, 0xc0},
    {0x25, 0xc0},
    {0x26, 0x80},
    {0x27, 0x80},
    {0x28, 0x00},
    {0x29, 0x7f},
    {0x2a, 0xff},
    {0x2b, 0x00},
    {0x2c, 0x00},
    {0x2d, 0x00},
    {0x2e, 0x02},
    {0x2f, 0xc0},
    {0x30, 0x00},
    {0x31, 0x00},
    {0x32, 0xc0},
    {0x33, 0x14},
    {0x34, 0x14},
    {0x35, 0x80},
    {0x36, 0x80},
    {0x37, 0x00},
    {0x38, 0x40},
    {0x39, 0x04},
    {0x3a, 0x07},
    {0x3b, 0x02},
    {0x3c, 0x01},
    {0x3d, 0x22},
    {0x3e, 0x01},
    {0x3f, 0xc4},
    {0x40, 0x05},
    {0x41, 0x11},
    {0x42, 0x01},
    {0x43, 0x34},
    {0x44, 0x6a},
    {0x45, 0x00},
    {0x46, 0x12},
    {0x47, 0x2f},
    {0x48, 0x24},
    {0x49, 0x08},
    {0x4a, 0x6c},
    {0x4b, 0x60},
    {0x4c, 0x00},
    {0x4d, 0x22},
    {0x4e, 0x00},
    #if (PR2000_TEST_PATTERN)
    {0x4f, 0x10},
    #else
    {0x4f, 0x00},
    #endif
    {0x50, 0xc6},
    {0x51, 0x28},
    {0x52, 0x40},
    {0x53, 0x0c},
    {0x54, 0x0f},
    {0x55, 0x8d},
    {0x70, 0x06},
    {0x71, 0x08},
    {0x72, 0x0a},
    {0x73, 0x0c},
    {0x74, 0x0e},
    {0x75, 0x10},
    {0x76, 0x12},
    {0x77, 0x14},
    {0x78, 0x06},
    {0x79, 0x08},
    {0x7a, 0x0a},
    {0x7b, 0x0c},
    {0x7c, 0x0e},
    {0x7d, 0x10},
    {0x7e, 0x12},
    {0x7f, 0x14},
    {0x80, 0x00},
    {0x81, 0x09},
    {0x82, 0x00},
    {0x83, 0x07},
    {0x84, 0x00},
    {0x85, 0x14},
    {0x86, 0x03},
    {0x87, 0x36},
    {0x88, 0x0a},
    {0x89, 0x62},
    {0x8a, 0x0a},
    {0x8b, 0x62},
    {0x8c, 0x0b},
    {0x8d, 0xe0},
    {0x8e, 0x06},
    {0x8f, 0x66},
    {0x90, 0x06},
    {0x91, 0xd1},
    {0x92, 0x73},
    {0x93, 0x39},
    {0x94, 0x0f},
    {0x95, 0x5e},
    {0x96, 0x09},
    {0x97, 0x26},
    {0x98, 0x1c},
    {0x99, 0x20},
    {0x9a, 0x17},
    {0x9b, 0x70},
    {0x9c, 0x0e},
    {0x9d, 0x10},
    {0x9e, 0x0b},
    {0x9f, 0xb8},
    {0xa0, 0x01},
    {0xa1, 0xc2},
    {0xa2, 0x01},
    {0xa3, 0xb8},
    {0xa4, 0x00},
    {0xa5, 0xe1},
    {0xa6, 0x00},
    {0xa7, 0xc6},
    {0xa8, 0x01},
    {0xa9, 0x7c},
    {0xaa, 0x01},
    {0xab, 0x7c},
    {0xac, 0x00},
    {0xad, 0xea},
    {0xae, 0x00},
    {0xaf, 0xea},
    {0xb0, 0x09},
    {0xb1, 0xaa},
    {0xb2, 0x0f},
    {0xb3, 0xae},
    {0xb4, 0x00},
    {0xb5, 0x17},
    {0xb6, 0x08},
    {0xb7, 0xe8},
    {0xb8, 0xb0},
    {0xb9, 0xce},
    {0xba, 0x90},
    {0xbb, 0x03},
    {0xbc, 0x00},
    {0xbd, 0x00}, //{0xbd, 0x04},
    {0xbe, 0x05},
    {0xbf, 0x00},
    {0xc0, 0x00},
    {0xc1, 0x00},//{0xc1, 0x18},
    {0xc2, 0x02},
    {0xc3, 0xd0},

    {0xff, 0x01},
    {0x54, 0x0e},
    {0xff, 0x01},
    {0x54, 0x0f},


    #if (PR2000_TEST_PATTERN)
    //Page2 for Test Pattern
    {0xff, 0x02},

    {0x80, 0xB8},
    #endif

    //Stop mipi 2lane
    {0xff, 0x00},
    {0x47, 0x1a},
    {0xff, 0x00},
    {0x40, 0x00},
    {0xff, 0x00},
    {0x4e, 0x7f},

    //Start mipi 2lane
    {0xff, 0x00},
    {0x40, 0x00},
    {0xff, 0x00},
    {0x4e, 0x4c},
    {0xff, 0x00},
    {0x40, 0x40},
    {0xff, 0x00},
    {0x4e, 0x6c},
    {0xff, 0x00},
    {0x4e, 0x4c},
    {0xff, 0x00},
    {0x47, 0x9a},
};
#endif

static I2C_ARRAY PatternTbl[] =
{

};

static I2C_ARRAY Current_Mirror_Flip_Tbl[] =
{

};

static I2C_ARRAY mirr_flip_table[] =
{

};

static I2C_ARRAY gain_reg[] =
{

};



static CUS_GAIN_GAP_ARRAY gain_gap_compensate[16] =
{            //compensate  gain gap

};

static I2C_ARRAY expo_reg[] =
{

};

static I2C_ARRAY vts_reg[] =
{

};

/*
static CUS_INT_TASK_ORDER def_order =
{
    .RunLength = 9,
    .Orders =
    {
        CUS_INT_TASK_AE | CUS_INT_TASK_VDOS | CUS_INT_TASK_AF,
        CUS_INT_TASK_VDOS | CUS_INT_TASK_AF,
        CUS_INT_TASK_AWB | CUS_INT_TASK_VDOS | CUS_INT_TASK_AF,
        CUS_INT_TASK_AE | CUS_INT_TASK_VDOS | CUS_INT_TASK_AF,
        CUS_INT_TASK_VDOS | CUS_INT_TASK_AF,
        CUS_INT_TASK_VDOS | CUS_INT_TASK_AF,
        CUS_INT_TASK_AE | CUS_INT_TASK_VDOS | CUS_INT_TASK_AF,
        CUS_INT_TASK_VDOS | CUS_INT_TASK_AF,
        CUS_INT_TASK_VDOS | CUS_INT_TASK_AF,
    },
};*/

static int pCus_poweron( ms_cus_sensor *handle )
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

static int pCus_poweroff( ms_cus_sensor *handle )
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    SENSOR_DMSG( "[%s] power low\n", __FUNCTION__ );
	sensor_if->SWReset(handle->channel_num, TRUE);
    sensor_if->PowerOff( 1, handle->pwdn_POLARITY );
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

static int pCus_GetSensorID( ms_cus_sensor *handle, u32 *id )
{
    int i, n;
    int table_length = ARRAY_SIZE( Sensor_id_table );
    I2C_ARRAY id_from_sensor[ARRAY_SIZE( Sensor_id_table )];

    //return SUCCESS;

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

    short sen_data1;
    SensorReg_Read( 0x7a02, &sen_data1 );
    SENSOR_IMSG( "sen_data1=0x%x\n", sen_data1 );
    if( sen_data1 != 0x18 )
        return FAIL;

    short OTP_7a0e, OTP_7a03, OTP_7a04, OTP_7a05, OTP_7a06, OTP_7a07, OTP_7a08;

    SensorReg_Read( 0x7a03, &OTP_7a03 );
    SENSOR_IMSG( "OTP_7a03=0x%x\n", OTP_7a03 );
    SensorReg_Read( 0x7a04, &OTP_7a04 );
    SENSOR_IMSG( "OTP_7a04=0x%x\n", OTP_7a04 );
    SensorReg_Read( 0x7a05, &OTP_7a05 );
    SENSOR_IMSG( "OTP_7a05=0x%x\n", OTP_7a05 );
    SensorReg_Read( 0x7a06, &OTP_7a06 );
    SENSOR_IMSG( "OTP_7a06=0x%x\n", OTP_7a06 );
    SensorReg_Read( 0x7a07, &OTP_7a07 );
    SENSOR_IMSG( "OTP_7a07=0x%x\n", OTP_7a07 );
    SensorReg_Read( 0x7a08, &OTP_7a08 );
    SENSOR_IMSG( "OTP_7a08=0x%x\n", OTP_7a08 );
    SensorReg_Read( 0x7a0e, &OTP_7a0e );
    SENSOR_IMSG( "OTP_7a0e=0x%x\n", OTP_7a0e );

    if( ( OTP_7a03 == 0x19 ) && ( OTP_7a04 == 0x06 ) && ( OTP_7a05 == 0x20 ) && ( OTP_7a06 == 0x06 ) && ( OTP_7a07 == 0x02 )
                    && ( OTP_7a08 == 0x01 ) )
    {
        SENSOR_IMSG( "[%s] This is PR2000 R2A version\n", __FUNCTION__ );
        return FAIL;
    }

    SENSOR_IMSG("[%s] %s get sensor id:0x%x, SUCCESS!\n", __FUNCTION__, handle->model_id, ( int )*id);
    return SUCCESS;
}

static int pr2000_SetPatternMode( ms_cus_sensor *handle, u32 mode )
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
    UartSendTrace("pr2000_MIPI reg: 0x%x, data: 0x%x, read: 0x%x.\n", usreg, usval, sen_data);

    return SUCCESS;
}

static int pCus_I2CRead(ms_cus_sensor *handle, unsigned short usreg, unsigned short* pusval)
{
    unsigned short usread_data;

    SensorReg_Read(usreg, &usread_data);
    *pusval = usread_data;
    UartSendTrace("pr2000_MIPI reg: 0x%x, data: 0x%x\n", usreg, usread_data);

    return SUCCESS;
}
#endif

static int pCus_init( ms_cus_sensor *handle )
{
    int i;
    ISensorIfAPI *sensor_if = &( handle->sensor_if_api );
    short sen_data;
    sensor_if->PCLK( CUS_SNR_PCLK_MIPI_TOP );

#if (SENSOR_MIPI_LANE_NUM == 2)
    //printf("[%s] PR2000 R1C version\n", __FUNCTION__);
    UartSendTrace("\npr2000 2lane_1280x720_30fps init.\n");
    for( i = 0; i < ARRAY_SIZE( Sensor_init_table_2lane_1280x720_30fps ); i++ )
    {
        if( Sensor_init_table_2lane_1280x720_30fps[i].reg == 0xffff )
        {
            MsSleep(RTK_MS_TO_TICK(1));//usleep( 1000*Sensor_init_table_2lane_1280x720_30fps[i].data );
        }
        else
        {
            if( SensorReg_Write(Sensor_init_table_2lane_1280x720_30fps[i].reg,Sensor_init_table_2lane_1280x720_30fps[i].data) != SUCCESS )
            {
                return FAIL;
            }
            SensorReg_Read( Sensor_init_table_2lane_1280x720_30fps[i].reg, &sen_data );
            UartSendTrace("pr2000 reg: 0x%x, data: 0x%x, read: 0x%x.\n",Sensor_init_table_2lane_1280x720_30fps[i].reg, Sensor_init_table_2lane_1280x720_30fps[i].data, sen_data);
        }
    }

    UartSendTrace("\npr2000 reg pattern\n");
    for( i = 0; i < ARRAY_SIZE( PatternTbl ); i++ )
    {
        if( SensorReg_Write(PatternTbl[i].reg,PatternTbl[i].data) != SUCCESS )
        {
            return FAIL;
        }
        SensorReg_Read( PatternTbl[i].reg, &sen_data );
        UartSendTrace("pr2000 reg: 0x%x, data: 0x%x, read: 0x%x.\n",PatternTbl[i].reg, PatternTbl[i].data, sen_data);
    }

    UartSendTrace("\npr2000 reg Current_Mirror_Flip_Tbl\n");
    for( i = 0; i < ARRAY_SIZE( Current_Mirror_Flip_Tbl ); i++ )
    {
        if( SensorReg_Write(Current_Mirror_Flip_Tbl[i].reg,Current_Mirror_Flip_Tbl[i].data) != SUCCESS )
        {
            return FAIL;
        }
        SensorReg_Read( Current_Mirror_Flip_Tbl[i].reg, &sen_data );
        UartSendTrace("pr2000 reg: 0x%x, data: 0x%x, read: 0x%x.\n",Current_Mirror_Flip_Tbl[i].reg, Current_Mirror_Flip_Tbl[i].data, sen_data);

    }
#endif

#if (SENSOR_MIPI_LANE_NUM == 4)
#if (SENSOR_OUTPUT_MOVIE_SIZE == MOVIE_SIZE_1080P25)
    UartSendTrace("\npr2000 4lane_1920x1080_25fps init.\n");
    for( i = 0; i < ARRAY_SIZE( Sensor_init_table_4lane_1920x1080_25fps ); i++ )
    {
        if( Sensor_init_table_4lane_1920x1080_25fps[i].reg == 0xffff )
        {
            MsSleep(RTK_MS_TO_TICK(1));//usleep( 1000*Sensor_init_table_4lane_1920x1080_25fps[i].data );
        }
        else
        {
            if( SensorReg_Write(Sensor_init_table_4lane_1920x1080_25fps[i].reg,Sensor_init_table_4lane_1920x1080_25fps[i].data) != SUCCESS )
            {
                return FAIL;
            }
            SensorReg_Read( Sensor_init_table_4lane_1920x1080_25fps[i].reg, &sen_data );
            UartSendTrace("pr2000 reg: 0x%x, data: 0x%x, read: 0x%x.\n",Sensor_init_table_4lane_1920x1080_25fps[i].reg, Sensor_init_table_4lane_1920x1080_25fps[i].data, sen_data);
        }
    }
#else
    UartSendTrace("\npr2000 4lane_1280x720_30fps init.\n");
    for( i = 0; i < ARRAY_SIZE( Sensor_init_table_4lane_1280x720_30fps ); i++ )
    {
        if( Sensor_init_table_4lane_1280x720_30fps[i].reg == 0xffff )
        {
            MsSleep(RTK_MS_TO_TICK(1));//usleep( 1000*Sensor_init_table_2lane_1280x720_30fps[i].data );
        }
        else
        {
            if( SensorReg_Write(Sensor_init_table_4lane_1280x720_30fps[i].reg,Sensor_init_table_4lane_1280x720_30fps[i].data) != SUCCESS )
            {
                return FAIL;
            }
            SensorReg_Read( Sensor_init_table_4lane_1280x720_30fps[i].reg, &sen_data );
            UartSendTrace("pr2000 reg: 0x%x, data: 0x%x, read: 0x%x.\n",Sensor_init_table_4lane_1280x720_30fps[i].reg, Sensor_init_table_4lane_1280x720_30fps[i].data, sen_data);
        }
    }
#endif
#endif

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

static int pCus_SetVideoRes( ms_cus_sensor *handle, u32 res )
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    handle->video_res_supported.ulcur_res = 0; //TBD
    //sensor_if->WaitVEnd( 50 );
    return SUCCESS;
}

static int pCus_GetOrien( ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT *orit )
{
    pr2000_params *params = ( pr2000_params * ) handle->private_data;
    return params->mirror_flip.cur;
}

static int pCus_SetOrien( ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT orit )
{
    pr2000_params *params = ( pr2000_params * ) handle->private_data;
    params->mirror_flip.new_setting = orit;
    //DoMirror( handle, params->mirror_flip.new_setting );
    return SUCCESS;
}

#if 0 //TBD
static int DoMirror( ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT orit )
{
    int table_length = ARRAY_SIZE( mirr_flip_table );
    int seg_length = table_length / 4;
    int i, j;

    pr2000_params *params = ( pr2000_params * ) handle->private_data;

    SENSOR_DMSG( "\n\n[%s]", __FUNCTION__ );

    switch( orit )
    {
        case CUS_ORIT_M0F0:
            for( i = 0, j = 0; i < seg_length; i++, j++ )
            {
                SensorReg_Write( mirr_flip_table[i].reg, mirr_flip_table[i].data );
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }

            break;

        case CUS_ORIT_M1F0:
            for( i = seg_length, j = 0; i < seg_length * 2; i++, j++ )
            {
                SensorReg_Write( mirr_flip_table[i].reg, mirr_flip_table[i].data );
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }

            break;

        case CUS_ORIT_M0F1:
            for( i = seg_length * 2, j = 0; i < seg_length * 3; i++, j++ )
            {
                SensorReg_Write( mirr_flip_table[i].reg, mirr_flip_table[i].data );
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }

            break;

        case CUS_ORIT_M1F1:
            for( i = seg_length * 3, j = 0; i < seg_length * 4; i++, j++ )
            {
                SensorReg_Write( mirr_flip_table[i].reg, mirr_flip_table[i].data );
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }

            break;

        default:
            for( i = 0, j = 0; i < seg_length; i++, j++ )
            {
                SensorReg_Write( mirr_flip_table[i].reg, mirr_flip_table[i].data );
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }

            break;
    }

    params->mirror_flip.cur = orit;

    return SUCCESS;
}
#endif

static int pCus_GetFPS( ms_cus_sensor *handle )
{
    pr2000_params *params = ( pr2000_params * ) handle->private_data;
    SENSOR_IMSG("[%s] FPS %d\n", __FUNCTION__, params->expo.fps);
    return params->expo.fps;
}

static int pCus_SetFPS( ms_cus_sensor *handle, u32 fps )
{
    pr2000_params *params = ( pr2000_params * ) handle->private_data;

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
    //pr2000_params *params = ( pr2000_params * ) handle->private_data;
    // u16 i,sen_data;
    switch( status )
    {
        case CUS_FRAME_ACTIVE:
            /*        if(params->reg_dirty) {

             SensorReg_Write(0xfd,0x01);//page 1
             SensorReg_Write(0x01,0x00);//frame sync disable
             SensorRegArrayW((I2C_ARRAY*)expo_reg, sizeof(expo_reg)/sizeof(I2C_ARRAY));
             SensorRegArrayW((I2C_ARRAY*)gain_reg, sizeof(gain_reg)/sizeof(I2C_ARRAY));
             SensorRegArrayW((I2C_ARRAY*)vts_reg, sizeof(vts_reg)/sizeof(I2C_ARRAY));
             SensorRegArrayW((I2C_ARRAY*)mirror_reg, sizeof(mirror_reg)/sizeof(I2C_ARRAY));
             SensorReg_Write(0x01,0x01);//frame sync enable

             params->reg_dirty = false;

             }*/
            break;
        case CUS_FRAME_INACTIVE:
            default:
            break;
    }

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
    //extern int ov4689_run;

    u32 lines = 0, vts = 0;
    pr2000_params *params = ( pr2000_params * ) handle->private_data;
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

    //handle->i2c_cfg.address = 0x7C;
    //if(ov4689_run == 1){
    //    return SUCCESS;
    //}
    SensorRegArrayW( ( I2C_ARRAY* )expo_reg, ARRAY_SIZE(expo_reg) );
    SensorRegArrayW( ( I2C_ARRAY* )gain_reg, ARRAY_SIZE(gain_reg) );
    SensorRegArrayW( ( I2C_ARRAY* )vts_reg, ARRAY_SIZE(vts_reg) );
#if 0
    UartSendTrace("[r:0x%x, d:0x%x]\n", expo_reg[0].reg, expo_reg[0].data);
    UartSendTrace("[r:0x%x, d:0x%x]\n", expo_reg[1].reg, expo_reg[1].data);
    UartSendTrace("[r:0x%x, d:0x%x]\n", expo_reg[2].reg, expo_reg[2].data);
    UartSendTrace("[r:0x%x, d:0x%x]\n", expo_reg[3].reg, expo_reg[3].data);

    UartSendTrace("[r:0x%x, d:0x%x]\n", gain_reg[0].reg, gain_reg[0].data);
    UartSendTrace("[r:0x%x, d:0x%x]\n", gain_reg[1].reg, gain_reg[1].data);
    UartSendTrace("[r:0x%x, d:0x%x]\n", gain_reg[2].reg, gain_reg[2].data);
    UartSendTrace("[r:0x%x, d:0x%x]\n", gain_reg[3].reg, gain_reg[3].data);
    UartSendTrace("[r:0x%x, d:0x%x]\n", gain_reg[4].reg, gain_reg[4].data);

    UartSendTrace("[r:0x%x, d:0x%x]\n", vts_reg[0].reg, vts_reg[0].data);
    UartSendTrace("[r:0x%x, d:0x%x]\n", vts_reg[1].reg, vts_reg[1].data);
    UartSendTrace("[r:0x%x, d:0x%x]\n", vts_reg[2].reg, vts_reg[2].data);
    UartSendTrace("[r:0x%x, d:0x%x]\n", vts_reg[3].reg, vts_reg[3].data);
    UartSendTrace("\n");
#endif

    // params->reg_dirty = true;
    return SUCCESS;
}

// Gain: 1x = 1024
static int pCus_GetAEGain( ms_cus_sensor *handle, u32* gain )
{
    u32 again, dgain;

    dgain = ( gain_reg[1].data ) << (8 + gain_reg[2].data);//dgain = ( gain_reg[1].data ) << 8 + gain_reg[2].data;
    again = ( u32 ) ( 1 << ( gain_reg[0].data & 0x03 ) );
    *gain = again * ( dgain << 2 );

    SENSOR_DMSG( "[%s] again(base1)/dgain(base64)/gain(base1024) = 0x%x/0x%x/0x%x\n", __FUNCTION__, again, dgain, *gain );
    return SUCCESS;
}

static int pCus_SetAEGain_cal( ms_cus_sensor *handle, u32 gain )
{
    //pr2000_params *params = ( pr2000_params * ) handle->private_data;
    u32 s_gain, ulTempGain;
    u32 DGain = 0x100, HCG_AGain = 0, LCG_AGain = 0;

    if( gain < SENSOR_MIN_GAIN )
        gain = SENSOR_MIN_GAIN;
    else if( gain >= SENSOR_MAX_GAIN )
        gain = SENSOR_MAX_GAIN;

    s_gain = gain >> 2;
    s_gain = s_gain / 2;            //for HCG DG min=X2
    if( s_gain > 0x800 )            //X8
    {
        HCG_AGain = 3;
        DGain = s_gain >> HCG_AGain;
    }
    else if( s_gain > 0x400 )
    {
        HCG_AGain = 2;
        DGain = s_gain >> HCG_AGain;
    }
    else if( s_gain > 0x200 )
    {
        HCG_AGain = 1;
        DGain = s_gain >> HCG_AGain;
    }
    else if( s_gain > 0x100 )
    {
        HCG_AGain = 0;
        DGain = s_gain >> HCG_AGain;
    }
    else if( s_gain < 0x100 )
    {
        HCG_AGain = 0;
        DGain = 0x100;
    }
    DGain = ( DGain * 0x200 + 0x80 ) / 0x100;            // make minima DG to be 2x
    if( DGain < 512 )
        DGain = 512;            //min=2X

    gain_reg[1].data = ( u16 ) ( DGain >> 8 );            //high byte
    gain_reg[2].data = ( u16 ) ( DGain & 0xff );            //low byte

    ulTempGain = gain >> 2;

    if( ulTempGain > 0x800 )            //X8
    {
        LCG_AGain = 3;
        DGain = ulTempGain >> LCG_AGain;
    }
    else if( ulTempGain > 0x400 )
    {
        LCG_AGain = 2;
        DGain = ulTempGain >> LCG_AGain;
    }
    else if( ulTempGain > 0x200 )
    {
        LCG_AGain = 1;
        DGain = ulTempGain >> LCG_AGain;
    }
    else if( ulTempGain > 0x100 )
    {
        LCG_AGain = 0;
        DGain = ulTempGain >> LCG_AGain;
    }
    else if( ulTempGain < 0x100 )
    {
        LCG_AGain = 0;
        DGain = 0x100;
    }
    if( DGain < 256 )
        DGain = 256;            //min=1.09X
    if( LCG_AGain < 1 )
        LCG_AGain = 1;            //min=2.0X

    gain_reg[3].data = ( u16 ) ( DGain >> 8 );            //high byte
    gain_reg[4].data = ( u16 ) ( DGain & 0xff );            //low byte
    gain_reg[0].data = ( u16 ) ( ( ( LCG_AGain << 2 ) & 0x0C ) + ( HCG_AGain & 0x03 ) );

    SENSOR_DMSG( "[%s] set gain/AG/HCG_H/HCG_L/LCG_H/LCG_L=%d/0x%x/0x%x/0x%x/0x%x/0x%x\n",
                    __FUNCTION__,
                    gain,
                    gain_reg[0].data,
                    gain_reg[1].data,
                    gain_reg[2].data,
                    gain_reg[3].data,
                    gain_reg[4].data );
    // params->reg_dirty = true;
    return SUCCESS;
}
static int pCus_SetAEGain( ms_cus_sensor *handle, u32 gain )
{
    //pr2000_params *params = ( pr2000_params * ) handle->private_data;
    CUS_GAIN_GAP_ARRAY* Sensor_Gain_Linearity;
    u32 i, s_gain, ulTempGain;
    u32 DGain = 0x100, HCG_AGain = 0, LCG_AGain = 0;

    if( gain < SENSOR_MIN_GAIN )
        gain = SENSOR_MIN_GAIN;
    else if( gain >= SENSOR_MAX_GAIN )
        gain = SENSOR_MAX_GAIN;

    Sensor_Gain_Linearity = gain_gap_compensate;

    for( i = 0; i < sizeof( gain_gap_compensate ) / sizeof(CUS_GAIN_GAP_ARRAY); i++ )
    {
        if( Sensor_Gain_Linearity[i].gain == 0 )
            break;
        if( ( gain > Sensor_Gain_Linearity[i].gain ) && ( gain < ( Sensor_Gain_Linearity[i].gain + Sensor_Gain_Linearity[i].offset ) ) )
        {
            gain = Sensor_Gain_Linearity[i].gain;
            break;
        }
    }
    s_gain = gain >> 2;
    s_gain = s_gain / 2;            //for HCG DG min=X2
    if( s_gain > 0x800 )            //X8
    {
        HCG_AGain = 3;
        DGain = s_gain >> HCG_AGain;
    }
    else if( s_gain > 0x400 )
    {
        HCG_AGain = 2;
        DGain = s_gain >> HCG_AGain;
    }
    else if( s_gain > 0x200 )
    {
        HCG_AGain = 1;
        DGain = s_gain >> HCG_AGain;
    }
    else if( s_gain > 0x100 )
    {
        HCG_AGain = 0;
        DGain = s_gain >> HCG_AGain;
    }
    else if( s_gain < 0x100 )
    {
        HCG_AGain = 0;
        DGain = 0x100;
    }
    DGain = ( DGain * 0x200 + 0x80 ) / 0x100;            // make minima DG to be 2x
    if( DGain < 512 )
        DGain = 512;            //min=2X

    gain_reg[1].data = ( u16 ) ( DGain >> 8 );            //high byte
    gain_reg[2].data = ( u16 ) ( DGain & 0xff );            //low byte

    ulTempGain = gain >> 2;

    if( ulTempGain > 0x800 )            //X8
    {
        LCG_AGain = 3;
        DGain = ulTempGain >> LCG_AGain;
    }
    else if( ulTempGain > 0x400 )
    {
        LCG_AGain = 2;
        DGain = ulTempGain >> LCG_AGain;
    }
    else if( ulTempGain > 0x200 )
    {
        LCG_AGain = 1;
        DGain = ulTempGain >> LCG_AGain;
    }
    else if( ulTempGain > 0x100 )
    {
        LCG_AGain = 0;
        DGain = ulTempGain >> LCG_AGain;
    }
    else if( ulTempGain < 0x100 )
    {
        LCG_AGain = 0;
        DGain = 0x100;
    }
    if( DGain < 256 )
        DGain = 256;            //min=1.09X
    if( LCG_AGain < 1 )
        LCG_AGain = 1;            //min=2.0X

    gain_reg[3].data = ( u16 ) ( DGain >> 8 );            //high byte
    gain_reg[4].data = ( u16 ) ( DGain & 0xff );            //low byte
    gain_reg[0].data = ( u16 ) ( ( ( LCG_AGain << 2 ) & 0x0C ) + ( HCG_AGain & 0x03 ) );

    SENSOR_DMSG( "[%s] set gain/AG/HCG_H/HCG_L/LCG_H/LCG_L=%d/0x%x/0x%x/0x%x/0x%x/0x%x\n",
                    __FUNCTION__,
                    gain,
                    gain_reg[0].data,
                    gain_reg[1].data,
                    gain_reg[2].data,
                    gain_reg[3].data,
                    gain_reg[4].data );
    // params->reg_dirty = true;
    return SUCCESS;
}
static int pCus_GetAEMinMaxUSecs( ms_cus_sensor *handle, u32 *min, u32 *max )
{
    *min = 1;
    *max = 1000000 / 30;

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

static int PR2000_GetShutterInfo( struct __ms_cus_sensor* handle, CUS_SHUTTER_INFO *info )
{
    info->max = 1000000000 / 12;
    info->min = Preview_line_period;
    info->step = Preview_line_period;
    return SUCCESS;
}

static int pCus_Sensor_GetSrcType(ms_cus_sensor *handle, CUS_SNR_ANADEC_SRC_TYPE *psrc_type)
{
    unsigned short usreg, usPreVal, usCurVal,usCurVal1,usCurVal2;
    unsigned short usLockStatus;

    *psrc_type = CUS_SNR_ANADEC_SRC_NO_READY;

    if (pCus_I2CRead == NULL) {
        SENSOR_EMSG("[%s] I2C function is not ready!\n", __FUNCTION__);
        return FAIL;
    }

    usreg = 0x0;
    //Set 0 Page
     if (SUCCESS != pCus_I2CWrite(handle, 0xFF, 0x00)) {
        *psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
    }
    //Read 0Page 0x00.
    if (SUCCESS != pCus_I2CRead(handle, usreg, &usCurVal)) {
        *psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
    }
    #if 1
    if (SUCCESS != pCus_I2CRead(handle, 0x01, &usCurVal1)) {
        *psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
    }

    if (SUCCESS != pCus_I2CRead(handle, 0x10, &usCurVal2)) {
        *psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
    }
    #endif
    do {
        usPreVal = usCurVal;
        if (SUCCESS != pCus_I2CRead(handle, usreg, &usCurVal)) {
            *psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
            return FAIL;
        }
    } while (usCurVal != usPreVal);

    if ((usCurVal & 0x08) == 0) {
        *psrc_type = CUS_SNR_ANADEC_SRC_NO_READY;
    }
    else {
        switch(usCurVal & 0x30)
        {
            case 0x00://25Hz
                if((usCurVal & 0x03) == 0x00)
                {
                    *psrc_type = CUS_SNR_ANADEC_SRC_PAL;
                }
                else if((usCurVal & 0x03) == 0x01)
                {
                    *psrc_type = CUS_SNR_ANADEC_SRC_NTSC;
                }
                else if((usCurVal & 0x03) == 0x02)
                {
                    *psrc_type = CUS_SNR_ANADEC_SRC_HD;
                }
                else if((usCurVal & 0x03) == 0x03)
                {
                    UartSendTrace(FG_PURPLE("+++++++1080P 25Hz++++++++++\r\n"));
                    *psrc_type = CUS_SNR_ANADEC_SRC_FHD;
                }
                else
                {
                    *psrc_type = CUS_SNR_ANADEC_SRC_NO_READY;
                }
                break;
            case 0x10://30Hz
                if((usCurVal & 0x03) == 0x00)
                {
                    *psrc_type = CUS_SNR_ANADEC_SRC_PAL;
                }
                else if((usCurVal & 0x03) == 0x01)
                {
                    *psrc_type = CUS_SNR_ANADEC_SRC_NTSC;
                }
                else if((usCurVal & 0x03) == 0x02)
                {
                    *psrc_type = CUS_SNR_ANADEC_SRC_HD;
                }
                else if((usCurVal & 0x03) == 0x03)
                {
                    UartSendTrace(FG_PURPLE("+++++++1080P 30Hz++++++++++\r\n"));
                    *psrc_type = CUS_SNR_ANADEC_SRC_FHD;
                }
                else
                {
                    *psrc_type = CUS_SNR_ANADEC_SRC_NO_READY;
                }
                break;
            case 0x20://50Hz
                if((usCurVal & 0x03) == 0x00)
                {
                    *psrc_type = CUS_SNR_ANADEC_SRC_PAL;
                }
                else if((usCurVal & 0x03) == 0x01)
                {
                    *psrc_type = CUS_SNR_ANADEC_SRC_NTSC;
                }
                else if((usCurVal & 0x03) == 0x02)
                {
                    *psrc_type = CUS_SNR_ANADEC_SRC_HD;
                }
                else if((usCurVal & 0x03) == 0x03)
                {
                    UartSendTrace(FG_PURPLE("+++++++1080P 50Hz++++++++++\r\n"));
                    *psrc_type = CUS_SNR_ANADEC_SRC_FHD;
                }
                else
                {
                    *psrc_type = CUS_SNR_ANADEC_SRC_NO_READY;
                }

                break;
            case 0x30://60Hz
                if((usCurVal & 0x03) == 0x00)
                {
                    *psrc_type = CUS_SNR_ANADEC_SRC_PAL;
                }
                else if((usCurVal & 0x03) == 0x01)
                {
                    *psrc_type = CUS_SNR_ANADEC_SRC_NTSC;
                }
                else if((usCurVal & 0x03) == 0x02)
                {
                    *psrc_type = CUS_SNR_ANADEC_SRC_HD;
                }
                else if((usCurVal & 0x03) == 0x03)
                {
                    UartSendTrace(FG_PURPLE("+++++++1080P 60Hz++++++++++\r\n"));
                    *psrc_type = CUS_SNR_ANADEC_SRC_FHD;
                }
                else
                {
                    *psrc_type = CUS_SNR_ANADEC_SRC_NO_READY;
                }
                break;

            default:
                *psrc_type = CUS_SNR_ANADEC_SRC_NO_READY;
                break;
        }
    }
    UartSendTrace("[%s] VID_STATUS: 0x%02x,0x%02x,0x%02x %d\n", __FUNCTION__, usCurVal,usCurVal1,usCurVal2, *psrc_type);

    return SUCCESS;
}

int pr2000_MIPI_cus_camsensor_init_handle( ms_cus_sensor* drv_handle )
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
    sprintf(str, "pr2000");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(pr2000_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (pr2000_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(pr2000_params));
#else
    handle->private_data = calloc( 1, sizeof(pr2000_params) );
#endif
    pr2000_params *params = ( pr2000_params * ) handle->private_data;

    sprintf( handle->model_id, SENSOR_MODEL_ID );
    handle->isp_type = SENSOR_ISP_TYPE;
    handle->sif_bus = SENSOR_IFBUS_TYPE;
    handle->data_prec = SENSOR_DATAPREC;
    handle->data_mode = SENSOR_DATAMODE;
    handle->bayer_id = SENSOR_BAYERID;
    handle->orient = SENSOR_ORIT;
    handle->interface_attr.attr_mipi.mipi_lane_num = SENSOR_MIPI_LANE_NUM;
    handle->interface_attr.attr_mipi.mipi_data_format = CUS_SEN_INPUT_FORMAT_YUV422; // YUV 422 format.
    handle->interface_attr.attr_mipi.mipi_yuv_order = CUS_SENSOR_YUV_ORDER_YC; // YUYV
    handle->interface_attr.attr_mipi.mipi_hsync_mode = SENSOR_MIPI_HSYNC_MODE;
    handle->interface_attr.attr_mipi.mipi_sampling_delay = SENSOR_MIPI_DELAY;
    handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_NONE;
    handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 0;
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

    handle->ae_gain_delay = SENSOR_GAIN_DELAY_FRAME_COUNT;            //0;//1;
    handle->ae_shutter_delay = SENSOR_SHUTTER_DELAY_FRAME_COUNT;            //1;//2;

    handle->sat_mingain = SENSOR_MIN_GAIN;
    handle->dgain_remainder = 0;
    handle->pCus_sensor_release = pr2000_MIPI_cus_camsensor_release_handle;
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
    handle->pCus_sensor_SetPatternMode = pr2000_SetPatternMode;

    handle->pCus_sensor_AEStatusNotify = pCus_AEStatusNotify;
    handle->pCus_sensor_GetAEUSecs = pCus_GetAEUSecs;
    handle->pCus_sensor_SetAEUSecs = pCus_SetAEUSecs;
    handle->pCus_sensor_GetAEGain = pCus_GetAEGain;
    handle->pCus_sensor_SetAEGain_cal = pCus_SetAEGain_cal;
    handle->pCus_sensor_SetAEGain = pCus_SetAEGain;

    handle->pCus_sensor_GetAEMinMaxGain = pCus_GetAEMinMaxGain;
    handle->pCus_sensor_GetAEMinMaxUSecs = pCus_GetAEMinMaxUSecs;
    handle->pCus_sensor_GetDGainRemainder = pCus_GetDGainRemainder;
    handle->pCus_sensor_GetShutterInfo = PR2000_GetShutterInfo;
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

int pr2000_MIPI_cus_camsensor_release_handle( ms_cus_sensor *handle )
{
#if defined(__RTK_OS__)
    CamOsRet_e                  eCamOsRet = CAM_OS_OK;
#endif

    if( handle && handle->private_data )
    {
        SENSOR_IMSG("[%s] release handle 0x%x, private data %x\n",__FUNCTION__,(int)handle,(int)handle->private_data);
#if defined(__RTK_OS__)
        eCamOsRet = CamOsDirectMemRelease((void*)handle->private_data, sizeof(pr2000_params));
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
struct SensorMapTable_t gsensor_map_pr2000 = {
    SENSOR_CHANNEL_NUM,
    pr2000_MIPI_cus_camsensor_init_handle,
    pr2000_MIPI_cus_camsensor_release_handle
};

int PR2000_Module_Init(void)
{
    cameraSensorRegister(&gsensor_map_pr2000);

    return 0;
}

void PR2000_Module_Exit(void)
{
    cameraSensorUnRegister(&gsensor_map_pr2000);
}

#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(PR2000_Module_Init);
//ait_module_exit(PR2000_Module_Exit);
#endif //#if defined(__RTK_OS__)

#endif //#if defined(BIND_SENSOR_PR2000) && (BIND_SENSOR_PR2000 == 1)
