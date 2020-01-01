////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (������MStar Confidential Information������) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "drv_SensorIF_pub.h"
#include "drv_ms_cus_sensor.h"
#include "drv_i2c_common.h"

#ifdef __cplusplus
}
#endif

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
#if (SENSOR0 == OV4689_MIPI)
#define BIND_SENSOR_OV4689 (1)
#endif
#endif //#if defined(__RTK_OS__)

#if (defined(BIND_SENSOR_OV4689) && (BIND_SENSOR_OV4689 == 1) || defined(BIND_SENSOR_OV4689_2ND) && (BIND_SENSOR_OV4689_2ND == 1))

#define SENSOR_PAD_GROUP_SET CUS_SENSOR_PAD_GROUP_A
#define SENSOR_CHANNEL_NUM (0)
#define SENSOR_CHANNEL_MODE CUS_SENSOR_CHANNEL_MODE_REALTIME_NORMAL

//============================================
//MIPI config begin.
#define SENSOR_MIPI_LANE_NUM (4)
//MIPI config end.
//============================================

#if 1//defined(__MV5_FPGA__)
#define SLOW_CLK  (0) //Verify FPGA
#if (SENSOR_MIPI_LANE_NUM == 4)
#define OV4689_4LANE (1) //Verify FPGA
#elif (SENSOR_MIPI_LANE_NUM == 2)
#define OV4689_4LANE (0) //Verify FPGA
#endif
#define OV4689_2432x1368_60P_HDR (0) //Verify FPGA
#else //#if defined(__MV5_FPGA__)
#define SLOW_CLK  (0) //Verify FPGA
#define OV4689_4LANE (0) //Verify FPGA
#define OV4689_2432x1368_60P_HDR (0) //Verify FPGA
#endif //#if defined(__MV5_FPGA__)

#define RES_IDX_2304x1296_60P_HDR   (1)     // mode 0,  2304*1296 60P
#define RES_IDX_1920x1080_30P       (0)     // mode 4,  1920*1080 30P       // Video (16:9)
#define RES_IDX_1280x720_60P        (2)     // mode 9,  1280*720  60P       // Video (16:9)

#define SENSOR_ISP_TYPE     ISP_EXT                   //ISP_EXT, ISP_SOC
#define SENSOR_IFBUS_TYPE   CUS_SENIF_BUS_MIPI      //CFG //CUS_SENIF_BUS_PARL, CUS_SENIF_BUS_MIPI
#define SENSOR_MIPI_HSYNC_MODE PACKET_HEADER_EDGE1
#define SENSOR_MIPI_DELAY   0x0E06                  //CFG
#define SENSOR_DATAPREC     CUS_DATAPRECISION_10    //CFG //CUS_DATAPRECISION_8, CUS_DATAPRECISION_10
#define SENSOR_DATAMODE     CUS_SEN_10TO12_9000     //CFG
#if (OV4689_4LANE == 1)
#define SENSOR_BAYERID      CUS_BAYER_GB            //CFG //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
#else
#define SENSOR_BAYERID      CUS_BAYER_RG            //CFG //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
#endif
#define SENSOR_ORIT         CUS_ORIT_M0F0           //CUS_ORIT_M0F0, CUS_ORIT_M1F0, CUS_ORIT_M0F1, CUS_ORIT_M1F1,

#define SENSOR_MAX_GAIN     (15.5 * 1024)                // max sensor again, a-gain * conversion-gain*d-gain
#define SENSOR_MIN_GAIN      (1 * 1024)
#define SENSOR_GAIN_DELAY_FRAME_COUNT      (2)
#define SENSOR_SHUTTER_DELAY_FRAME_COUNT      (2)

#if (SLOW_CLK == 1)
#define Preview_MCLK_SPEED  CUS_CMU_CLK_27MHZ        //CFG //CUS_CMU_CLK_12M, CUS_CMU_CLK_16M, CUS_CMU_CLK_24M, CUS_CMU_CLK_27M
#else
#define Preview_MCLK_SPEED  CUS_CMU_CLK_24MHZ//CUS_CMU_CLK_27MHZ        //CFG //CUS_CMU_CLK_12M, CUS_CMU_CLK_16M, CUS_CMU_CLK_24M, CUS_CMU_CLK_27M
#endif
//#define Preview_line_period 32173                 // MCLK=27 HTS/PCLK=3909 pixels/121.5MHZ=32.17us
// MCLK=21.6 HTS/PCLK=3217 pixels/97.2MHZ=32.17us
//#define Preview_line_period 28806                 // MCLK=21.6 HTS/PCLK=2800 pixels/97.2MHZ=28.8us
//#define Preview_line_period 33333                 // MCLK=21.6 HTS/PCLK=2700 pixels/81MHZ=33.3333us

//#define hts_32p17us 3909                          // HTS for 32.17@MCLK 27
//#define hts_32p17us 3127                          // HTS for 32.17@MCLK 21.6

//#define hts_32p17us 2800                          // HTS for 28.806@MCLK 21.6
//#define hts_32p17us 2700                          // HTS for 28.806@MCLK 21.6

//#define Prv_Max_line_number 1520//1520                    //maximum exposure line munber of sensor when preview
//#define vts_25fps  1554   //20fps                         //Virt Total Size , 30.25us * 1111 =  33.6ms frame interval =30 fps

//#define vts_25fps  1736   //20fps                         //Virt Total Size , for Preview_line_period = 28.806us
//#define vts_25fps  1500   //20fps                         //Virt Total Size , for Preview_line_period = 28.806us

#if (SLOW_CLK == 1)
#define MIPI_CLK 33 //MCLK 783MHz
#else
#define MIPI_CLK 783 //MCLK 783MHz
#endif
//#define MCLK_CLK 626 //MCLK 626.4MHz
//#define MIPI_CLK 567 //MHz
//#define MIPI_CLK 486 //MHz
#if MIPI_CLK == 486 //need external MCLK 27MHz
#define Preview_line_period 32130                           // MCLK=21.6 HTS/PCLK=3080 pixels/97.2MHZ=31.687us
#define Hts 3904                                    // HTS for 31.687@MCLK 21.6
#define vts_25fps  1556                                     // VTS for 20fps
#endif

#if MIPI_CLK == 783 //need external MCLK 27MHz
#define Preview_line_period 24361                           // MCLK=21.6 HTS/PCLK=3080 pixels/97.2MHZ=31.687us
#define Hts 2960                                            // 3126 for 25fps
#define vts_25fps  1642                                     // VTS for 20fps
#endif

#if MIPI_CLK == 626 //need external MCLK 21.6MHz
#define Preview_line_period 31687                           // MCLK=21.6 HTS/PCLK=3080 pixels/97.2MHZ=31.687us
#define Hts 3080                                    // HTS for 31.687@MCLK 21.6
#define vts_25fps  1580                                     // VTS for 20fps
#endif

//V blanking min 2ms
#if MIPI_CLK == 567 ////need external MCLK 27MHz
#define Preview_line_period 31111                           // HTS/PCLK=2800 pixels/90MHZ=31.111us
#define Hts 2800                                    // HTS for 31.1111@MCLK 21.6
#define vts_25fps  1607                                     // VTS for 20fps
#endif

//V blanking min 2ms
#if MIPI_CLK == 540 ////need external MCLK 27MHz
#define Preview_line_period 31579                           // HTS/PCLK=2720 pixels/85.5MHZ=31.579us
#define Hts 2700                                    // HTS for 31.8136us@MCLK 27
#define vts_25fps  1583                                     // VTS for 20fps
#endif

#if MIPI_CLK == 33 ////need external MCLK 24MHz
//HSYNC=6.7KHz, VSYNC=3.75Hz, MIPI_CLK=33MHz, Grab 1928x1092
#define Preview_line_period 149253                           // HTS/PCLK=1920 pixels/85.5MHZ=31.579us ???
#define Hts 2700                                    // HTS for 31.8136us@MCLK 27 ???
#define vts_25fps  1583                                     // VTS for 20fps ???
#endif //#if MIPI_CLK == 33

#if (SLOW_CLK == 1)
#define Preview_WIDTH       1928//2688                    //resolution Width when preview
#define Preview_HEIGHT      1092//1520                    //resolution Height when preview

#define Preview_MAX_FPS     4                     //fastest preview FPS
#define Preview_MIN_FPS     3                      //slowest preview FPS
#else //#if (SLOW_CLK == 1)

#if OV4689_4LANE
#define Preview_WIDTH       2032//2688//2688                    //resolution Width when preview
#define Preview_HEIGHT      1524//1520//1520                    //resolution Height when preview
#else //2 lane
#define Preview_WIDTH       1928//2688//2688                    //resolution Width when preview
#define Preview_HEIGHT      1092//1520//1520                    //resolution Height when preview
#endif

#define Preview_MAX_FPS     30                     //fastest preview FPS
#define Preview_MIN_FPS     8                      //slowest preview FPS
#endif //#if (SLOW_CLK == 1)
#define Preview_CROP_START_X     1                      //CROP_START_X
#define Preview_CROP_START_Y     1                      //CROP_START_Y

#define Cap_Max_line_number 1520//1520                   //maximum exposure line munber of sensor when capture

#define SENSOR_I2C_ADDR     0x6c                   //I2C slave address
#define SENSOR_I2C_SPEED    I2C_SLOWSPEED_MODE_200KHZ   //200KHz
#define SENSOR_I2C_CHANNEL  1                           //I2C Channel
#define SENSOR_I2C_PAD_MODE 2                           //Pad/Mode Number

#define SENSOR_I2C_LEGACY  I2C_NORMAL_MODE     //usally set CUS_I2C_NORMAL_MODE,  if use old OVT I2C protocol=> set CUS_I2C_LEGACY_MODE
#define SENSOR_I2C_FMT     I2C_FMT_A16D8        //CUS_I2C_FMT_A8D8, CUS_I2C_FMT_A8D16, CUS_I2C_FMT_A16D8, CUS_I2C_FMT_A16D16

#define SENSOR_PWDN_POL     CUS_CLK_POL_POS        // if PWDN pin High can makes sensor in power down, set CUS_CLK_POL_POS
#define SENSOR_RST_POL      CUS_CLK_POL_NEG        // if RESET pin High can makes sensor in reset state, set CUS_CLK_POL_NEG

// VSYNC/HSYNC POL can be found in data sheet timing diagram,
// Notice: the initial setting may contain VSYNC/HSYNC POL inverse settings so that condition is different.

#define SENSOR_VSYNC_POL    CUS_CLK_POL_NEG        // if VSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_HSYNC_POL    CUS_CLK_POL_POS        // if HSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_PCLK_POL     CUS_CLK_POL_POS        // depend on sensor setting, sometimes need to try CUS_CLK_POL_POS or CUS_CLK_POL_NEG
//SCD define
#define SCD_SENSOR_MIPI_LANE_NUM (2)
#define SCD_SENSOR_PAD_GROUP_SET CUS_SENSOR_PAD_GROUP_B
#define SCD_SENSOR_PWDN_POL      CUS_CLK_POL_POS
#define SCD_SENSOR_CHANNEL_NUM   (1)
#define SCD_SENSOR_CHANNEL_MODE CUS_SENSOR_CHANNEL_MODE_RAW_STORE_FETCH
#define SCD_SENSOR_BAYERID      CUS_BAYER_RG
#define SCD_Preview_WIDTH       1928//2688//2688                    //resolution Width when preview
#define SCD_Preview_HEIGHT      1092//1520//1520
//

static int OV4689_SetAEGain( ms_cus_sensor *handle, u32 gain );
static int OV4689_SetAEUSecs( ms_cus_sensor *handle, u32 us );

int ov4689_MIPI_cus_camsensor_release_handle( ms_cus_sensor *handle );

static CUS_CAMSENSOR_CAP sensor_cap =
{
.length = sizeof(CUS_CAMSENSOR_CAP),
.version = 0x0001,
};

typedef struct
{
    struct
    {
        u16 pre_div0;
        u16 div124;
        u16 div_cnt7b;
        u16 sdiv0;
        u16 mipi_div0;
        u16 r_divp;
        u16 sdiv1;
        u16 r_seld5;
        u16 r_sclk_dac;
        u16 sys_sel;
        u16 pdac_sel;
        u16 adac_sel;
        u16 pre_div_sp;
        u16 r_div_sp;
        u16 div_cnt5b;
        u16 sdiv_sp;
        u16 div12_sp;
        u16 mipi_lane_sel;
        u16 div_dac;
    } clk_tree;
    struct
    {
        bool bVideoMode;
        u16 res_idx;
        //        bool binning;
        //        bool scaling;
        CUS_CAMSENSOR_ORIT orit;
    } res;
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
    u32 gain;
    bool reg_dirty;            //sensor setting need to update through I2C

} ov4689_params;

// set sensor ID address and data,
static I2C_ARRAY Sensor_id_table[] =
                {
                {0x300a, 0x46},            // {address of ID, ID },
                {0x300b, 0x88},            // {address of ID, ID },
//{0x7001, 0x46},      // {address of ID, ID },
//{0x7002, 0x89},      // {address of ID, ID },

// max 8 sets in this table
                };
/*
 ;----------------------------------------------
 ; MCLK: 27Mhz
 ; resolution: 2688x1520
 ; Mipi : 2 lane
 ; Mipi data rate: 486Mbps/Lane
 ; SystemCLK   : 121.5MHz
 ; FPS          : 20fps
 ; HTS      :3904 (R380c:R380d)
 ; VTS      :1556 (R380e:R380f)
 ; Tline    :32.13 us
 ;---------------------------------------------
 */
static I2C_ARRAY Sensor_init_table[] =
{
#if 1//(SLOW_CLK == 1)


#if (OV4689_4LANE == 1)

#if (OV4689_2432x1368_60P_HDR == 1)


        //----------------------------------------------
        // MCLK: 24Mhz
        // Mipi : 4 lane
        // Mipi data rate:480Mbps/Lane
        // Sensor Output:2436x1372 (8bit)
        // SystemCLK   :120MHz
        // #if (ADD_VTS)
        // FPS        :30.016 fps (long 30.016 fps, short 30.016 fps)
        // HTS        :1298 (R380c:R380d)
        // VTS        :1540 (R380e:R380f)
        // Tline     : 21.63
        //
        //
        // #else
        // FPS        :29.97fps (long 29.97fps, short 29.97fps)
        // HTS        :1422 (R380c:R380d)
        // VTS        :1408 (R380e:R380f)
        // Tline     : 23.7
        // (T0+T1) < VTS-4 ; T0 is for long exposure frame ; T1 is for middel exposure frame
        // T0 > T1
        // #endif
        //---------------------------------------------

        {0x0103, 0x01},
        //SENSOR_DELAY_REG, 100, // delay

        {0x3638, 0x00},
    #if SLOW_CLK
        #if 1 //Work, MIPI CLK rate = 60MHz
        {0x0300, 0x05},
        {0x030A, 0x00},
        {0x0302, 0x28},
        #endif
        #if 0 //Fail, MIPI CLK rate = 57MHz
        {0x0300, 0x05},
        {0x030A, 0x00},
        {0x0302, 0x26},
        #endif
        #if 0 //Fail, MIPI CLK rate = 58MHz
        {0x0300, 0x06},
        {0x030A, 0x00},
        {0x0302, 0x3A},
        #endif
    #else
        //Old: MIPI CLK rate = 340MHz
        {0x0300, 0x00},///0x03xx,///0x04x,///0x00,///0x03,///0x00},
        {0x030A, 0x00},
        {0x0302, 0x28},///0x21,///0x53xx,///0x64x,///0x21,///0x4E,///0x1f},
    #endif

        {0x0303, 0x01},
        {0x0304, 0x03},

    #if SLOW_CLK
        {0x030b, 0x05},
        {0x0311, 0x00},
    #else
        {0x030b, 0x00},
        {0x0311, 0x00},
    #endif

        {0x030d, 0x1e},
        {0x030e, 0x04},
        {0x030f, 0x01},
        {0x0312, 0x01},
        {0x031e, 0x00},
        {0x3000, 0x20},
        {0x3002, 0x00},
        {0x3018, 0x72},
        {0x3020, 0x93},
        {0x3021, 0x03},
        {0x3022, 0x01},
        {0x3031, 0x08},//0x0a: 10bit, 0x08: 8bit
        {0x303f, 0x0c},
        {0x3305, 0xf1},
        {0x3307, 0x04},
        {0x3309, 0x29},
        {0x3500, 0x00}, // long exp.
        {0x3501, 0x30}, // long exp.
        {0x3502, 0x00}, // long exp.
        {0x3503, 0x64},//0x04,
        {0x3504, 0x00},
        {0x3505, 0x00},
        {0x3506, 0x00},
        {0x3507, 0x00},
        {0x3508, 0x07},
        {0x3509, 0xf0}, // long: 15.5X
        {0x350a, 0x00}, // middle exp.
        {0x350b, 0x08}, // middle exp.
        {0x350c, 0x00}, // middle exp
        {0x350d, 0x00},
        {0x350e, 0x07},
        {0x350f, 0xf0}, // middle : 15.5X
        {0x3510, 0x00},
        {0x3511, 0x01}, // 00
        {0x3512, 0x00},
        {0x3513, 0x00},
        {0x3514, 0x00},
        {0x3515, 0x80},
        {0x3516, 0x00},
        {0x3517, 0x00},
        {0x3518, 0x00},
        {0x3519, 0x00},
        {0x351a, 0x00},
        {0x351b, 0x80},
        {0x351c, 0x00},
        {0x351d, 0x00},
        {0x351e, 0x00},
        {0x351f, 0x00},
        {0x3520, 0x00},
        {0x3521, 0x80},
        {0x3522, 0x08},
        {0x3524, 0x08},
        {0x3526, 0x08},
        {0x3528, 0x08},
        {0x352a, 0x08},
        {0x3602, 0x00},
        {0x3603, 0x40},
        {0x3604, 0x02},
        {0x3605, 0x00},
        {0x3606, 0x00},
        {0x3607, 0x00},
        {0x3609, 0x12},
        {0x360a, 0x40},
        {0x360c, 0x08},
        //{0x360f, 0xe5},
        {0x360f, 0xe0},
        {0x3608, 0x8f},
        {0x3611, 0x00},
        {0x3613, 0xf7},
        {0x3616, 0x58},
        {0x3619, 0x99},
        {0x361b, 0x60},
        {0x361c, 0x7a},
        {0x361e, 0x79},
        {0x361f, 0x02},
        {0x3632, 0x00},
        {0x3633, 0x10},
        {0x3634, 0x10},
        {0x3635, 0x10},
        //{0x3636, 0x15},
        {0x3636, 0x10},
        {0x3646, 0x86},
        {0x364a, 0x0b},
        {0x3700, 0x17},
        {0x3701, 0x22},
        {0x3703, 0x10},
        {0x370a, 0x37},
        {0x3705, 0x00},
        {0x3706, 0x63},
        {0x3709, 0x3c},
        {0x370b, 0x01},
        {0x370c, 0x30},
        {0x3710, 0x24},
        {0x3711, 0x0c},
        {0x3716, 0x00},
        {0x3720, 0x28},
        {0x3729, 0x7b},
        {0x372a, 0x84},
        {0x372b, 0xbd},
        {0x372c, 0xbc},
        {0x372e, 0x52},
        {0x373c, 0x0e},
        {0x373e, 0x33},
        {0x3743, 0x10},
        {0x3744, 0x88},
        {0x3745, 0xc0},
        {0x374a, 0x43},
        {0x374c, 0x00},
        {0x374e, 0x23},
        {0x3751, 0x7b},
        {0x3752, 0x84},
        {0x3753, 0xbd},
        {0x3754, 0xbc},
        {0x3756, 0x52},
        {0x375c, 0x00},
        {0x3760, 0x00},
        {0x3761, 0x00},
        {0x3762, 0x00},
        {0x3763, 0x00},
        {0x3764, 0x00},
        {0x3767, 0x04},
        {0x3768, 0x04},
        {0x3769, 0x08},
        {0x376a, 0x08},
        {0x376b, 0x20},
        {0x376c, 0x00},
        {0x376d, 0x00},
        {0x376e, 0x01}, // 00
        {0x3773, 0x00},
        {0x3774, 0x51},
        {0x3776, 0xbd},
        {0x3777, 0xbd},
        {0x3781, 0x18},
        {0x3783, 0x25},
        {0x3798, 0x1b},
        {0x3800, 0x00},
        {0x3801, 0x86},///0x88,///0x84, // 08
        {0x3802, 0x00},
        {0x3803, 0x4e},///0x4c, // 04
        {0x3804, 0x0a},
        {0x3805, 0x19},///0x1b, // 97
        {0x3806, 0x05},
        {0x3807, 0xB1},///0xb3, // fb
        {0x3808, 0x09},
        {0x3809, 0x84},///0x88, // 80
        {0x380a, 0x05},
        {0x380b, 0x5C},///0x60, // f0
    #if ADD_VTS
        {0x380c, 0x05}, //1298
        {0x380d, 0x12},
        {0x380e, 0x06}, //1540
        {0x380f, 0x04},
    #else
        {0x380c, 0x05}, //1422
        {0x380d, 0x8E},
        {0x380e, 0x05},
        {0x380f, 0x80}, //1408
    #endif

        {0x3810, 0x00},
        {0x3811, 0x08},///0x0A,///0x08},
        {0x3812, 0x00},
        {0x3813, 0x04},
        {0x3814, 0x01},
        {0x3815, 0x01},
        {0x3819, 0x01},
    #if SENSOR_ROTATE_180
        {0x3820, 0x06}, // Tom: 0x00: No Flip, 0x06: Row & Column Flip
        {0x3821, 0x00}, // Tom: 0x06: No Flip, 0x00: Row & Column Flip
    #else
        {0x3820, 0x00},
        {0x3821, 0x06},
    #endif
        {0x3829, 0x00},
        {0x382a, 0x01},
        {0x382b, 0x01},
        {0x382d, 0x7f},
        {0x3830, 0x04},
        {0x3836, 0x01},
        {0x3837, 0x00},
        {0x3841, 0x03}, // 02
        {0x3846, 0x08},
        {0x3847, 0x06}, // 07
        {0x3d85, 0x36},
        {0x3d8c, 0x71},
        {0x3d8d, 0xcb},
        {0x3f0a, 0x00},
        {0x4000, 0xF1},//0x71},
        {0x4001, 0x40},
        {0x4002, 0x04},
        {0x4003, 0x14},
        {0x400e, 0x00},
        {0x4011, 0x00},
        {0x401a, 0x00},
        {0x401b, 0x00},
        {0x401c, 0x00},
        {0x401d, 0x00},
        {0x401f, 0x00},
        {0x4020, 0x00},
        {0x4021, 0x10},
        {0x4022, 0x08}, // 07
        {0x4023, 0x17},///0x13,///0x1B, // cf
        {0x4024, 0x09},
        {0x4025, 0x44},///0x40,///0x48, // 60
        {0x4026, 0x09},
        {0x4027, 0x54},///0x50,///0x58, // 6f
        {0x4028, 0x00},
        {0x4029, 0x02},
        {0x402a, 0x06},
        {0x402b, 0x04},
        {0x402c, 0x02},
        {0x402d, 0x02},
        {0x402e, 0x0e},
        {0x402f, 0x04},
        {0x4302, 0xff},
        {0x4303, 0xff},
        {0x4304, 0x00},
        {0x4305, 0x00},
        {0x4306, 0x00},
        {0x4308, 0x02},
        {0x4500, 0x6c},
        {0x4501, 0xc4},
        {0x4502, 0x40},
        {0x4503, 0x01},
        {0x4601, 0x04}, //0x95, //Fix Issue: HDR mode right-up has noise line.
        {0x4800, 0x0c},
        {0x4813, 0x08},
        {0x481f, 0x40},
        {0x4829, 0x78},
        {0x4837, 0x21},
        {0x4b00, 0x2a},
        {0x4b0d, 0x00},
        {0x4d00, 0x04},
        {0x4d01, 0x42},
        {0x4d02, 0xd1},
        {0x4d03, 0x93},
        {0x4d04, 0xf5},
        {0x4d05, 0xc1},
        {0x5000, 0xf3},
        {0x5001, 0x11},
        {0x5004, 0x00},
        {0x500a, 0x00},
        {0x500b, 0x00},
        {0x5032, 0x00},
        {0x5040, 0x00},
        {0x5050, 0x0c},
        {0x5500, 0x00},
        {0x5501, 0x10},
        {0x5502, 0x01},
        {0x5503, 0x0f},
        {0x8000, 0x00},
        {0x8001, 0x00},
        {0x8002, 0x00},
        {0x8003, 0x00},
        {0x8004, 0x00},
        {0x8005, 0x00},
        {0x8006, 0x00},
        {0x8007, 0x00},
        {0x8008, 0x00},
        {0x3638, 0x00},
        {0x0100, 0x01},


#else //#if (OV4689_2432x1368_60P_HDR == 1)
        /*
        * @@ RES_2032x1524@30
        */

        /*
        * ---------------------------------------------
        *  MCLK: 24Mhz
        *  resolution: 2032x1524
        *  Mipi : 4 lane
        *  Mipi data rate: 360Mbps/Lane
        *  SystemCLK: 120Mhz
        *  FPS: 30
        *  HTS: 2560(R380c:R380d)
        *  VTS: 1562(R380e:R380f)
        *  Tline: 21.33us
        *  Max exp line: 1558 (VTS-4)
        * ---------------------------------------------
        */
        {0x0103, 0x001},
        {0x3638, 0x000},

        #if SLOW_CLK
        #if 0 //Work, MIPI CLK rate = 17.25MHz
        {0x0300, 0x005},
        {0x030a, 0x001},
        {0x0302, 0x017},
        #endif
        #if 0 //Work ?, MIPI CLK rate = 18.5MHz -> 36.5MHz
        {0x0300, 0x006},
        {0x030a, 0x001},
        {0x0302, 0x025},
        #endif

        #if 0 //Work 100%, MIPI CLK rate = 32MHz
        {0x0300, 0x004},
        {0x030a, 0x001},
        {0x0302, 0x020},
        #endif

        #if 1 //Work 100%, MIPI CLK rate = 26MHz
        {0x0300, 0x004},
        {0x030a, 0x000},//{0x030a, 0x001},
        {0x0302, 0x01A},
        #endif

        #if 0 //Work, MIPI CLK rate = 17MHz
        {0x0300, 0x006},
        {0x030a, 0x001},
        {0x0302, 0x022},
        #endif
        #if 0 //XX, MIPI CLK rate = 13.5MHz
        {0x0300, 0x006},
        {0x030a, 0x001},
        {0x0302, 0x01b},
        #endif
        #else

        {0x0300, 0x000},
        {0x030a, 0x000},
        {0x0302, 0x01e},
        #endif


        {0x0303, 0x001},
        {0x0304, 0x003},

        #if SLOW_CLK
        #if 1
        {0x030b, 0x005},
        {0x0311, 0x001},
        #endif
        #if 0
        {0x030b, 0x006},
        {0x0311, 0x001},
        #endif
        #else
        {0x030b, 0x000},
        //{0x0311, 0x001},//{0x0311, 0x000},
        #endif

        {0x030d, 0x01e},
        {0x030e, 0x004},
        {0x030f, 0x001},
        {0x0312, 0x001},
        {0x031e, 0x000},
        {0x3000, 0x020},
        {0x3002, 0x000},
        {0x3018, 0x072},
        {0x3020, 0x093},
        {0x3021, 0x003},
        {0x3022, 0x001},
        {0x3031, 0x00a},
        {0x303f, 0x00c},
        {0x3305, 0x0f1},
        {0x3307, 0x004},
        {0x3309, 0x029},
        {0x3500, 0x000},
        {0x3501, 0x061},
        {0x3502, 0x000},
        {0x3503, 0x004},
        {0x3504, 0x000},
        {0x3505, 0x000},
        {0x3506, 0x000},
        {0x3507, 0x000},
        {0x3508, 0x007},
        {0x3509, 0x078},
        {0x350a, 0x000},
        {0x350b, 0x000},
        {0x350c, 0x000},
        {0x350d, 0x000},
        {0x350e, 0x000},
        {0x350f, 0x080},
        {0x3510, 0x000},
        {0x3511, 0x000},
        {0x3512, 0x000},
        {0x3513, 0x000},
        {0x3514, 0x000},
        {0x3515, 0x080},
        {0x3516, 0x000},
        {0x3517, 0x000},
        {0x3518, 0x000},
        {0x3519, 0x000},
        {0x351a, 0x000},
        {0x351b, 0x080},
        {0x351c, 0x000},
        {0x351d, 0x000},
        {0x351e, 0x000},
        {0x351f, 0x000},
        {0x3520, 0x000},
        {0x3521, 0x080},
        {0x3522, 0x008},
        {0x3524, 0x008},
        {0x3526, 0x008},
        {0x3528, 0x008},
        {0x352a, 0x008},
        {0x3602, 0x000},
        {0x3603, 0x040},
        {0x3604, 0x002},
        {0x3605, 0x000},
        {0x3606, 0x000},
        {0x3607, 0x000},
        {0x3609, 0x012},
        {0x360a, 0x040},
        {0x360c, 0x008},
        //{0x360f, 0xe5},
        //{0x360f, 0xdb},
        {0x360f, 0xe0},
        {0x3608, 0x08f},
        {0x3611, 0x000},
        {0x3613, 0x0f7},
        {0x3616, 0x058},
        {0x3619, 0x099},
        {0x361b, 0x060},
        {0x361c, 0x07a},
        {0x361e, 0x079},
        {0x361f, 0x002},
        {0x3632, 0x000},
        {0x3633, 0x010},
        {0x3634, 0x010},
        {0x3635, 0x010},
        //{0x3636, 0x15},
        {0x3636, 0x10},
        {0x3646, 0x086},
        {0x364a, 0x00b},
        {0x3700, 0x017},
        {0x3701, 0x022},
        {0x3703, 0x010},
        {0x370a, 0x037},
        {0x3705, 0x000},
        {0x3706, 0x063},
        {0x3709, 0x03c},
        {0x370b, 0x001},
        {0x370c, 0x030},
        {0x3710, 0x024},
        {0x3711, 0x00c},
        {0x3716, 0x000},
        {0x3720, 0x028},
        {0x3729, 0x07b},
        {0x372a, 0x084},
        {0x372b, 0x0bd},
        {0x372c, 0x0bc},
        {0x372e, 0x052},
        {0x373c, 0x00e},
        {0x373e, 0x033},
        {0x3743, 0x010},
        {0x3744, 0x088},
        {0x3745, 0x0c0},
        {0x374a, 0x043},
        {0x374c, 0x000},
        {0x374e, 0x023},
        {0x3751, 0x07b},
        {0x3752, 0x084},
        {0x3753, 0x0bd},
        {0x3754, 0x0bc},
        {0x3756, 0x052},
        {0x375c, 0x000},
        {0x3760, 0x000},
        {0x3761, 0x000},
        {0x3762, 0x000},
        {0x3763, 0x000},
        {0x3764, 0x000},
        {0x3767, 0x004},
        {0x3768, 0x004},
        {0x3769, 0x008},
        {0x376a, 0x008},
        {0x376b, 0x020},
        {0x376c, 0x000},
        {0x376d, 0x000},
        {0x376e, 0x000},
        {0x3773, 0x000},
        {0x3774, 0x051},
        {0x3776, 0x0bd},
        {0x3777, 0x0bd},
        {0x3781, 0x018},
        {0x3783, 0x025},
        {0x3798, 0x01b},
        {0x3800, 0x001},   //Xstart
        {0x3801, 0x050},
        {0x3802, 0x000},   //Ystart
        {0x3803, 0x002},
        {0x3804, 0x009}, //XEnd
        {0x3805, 0x04f},
        {0x3806, 0x005}, //YEnd
        {0x3807, 0x0fd},
        {0x3808, 0x007},     //XSize
        {0x3809, 0x0f0},
        {0x380a, 0x005},     //YSize
        {0x380b, 0x0f4},
        {0x380c, 0x00a},
        {0x380d, 0x000},
        {0x380e, 0x006},
        {0x380f, 0x01a},
        {0x3810, 0x000},
        {0x3811, 0x008},
        {0x3812, 0x000},
        {0x3813, 0x004},
        {0x3814, 0x001},
        {0x3815, 0x001},
        {0x3819, 0x001},
        #if SENSOR_ROTATE_180
        {0x3820, 0x06}, // Tom: 0x00: No Flip, 0x06: Row & Column Flip
        {0x3821, 0x00}, // Tom: 0x06: No Flip, 0x00: Row & Column Flip
        #else
        {0x3820, 0x000},
        {0x3821, 0x006},
        #endif
        {0x3829, 0x000},
        {0x382a, 0x001},
        {0x382b, 0x001},
        {0x382d, 0x07f},
        {0x3830, 0x004},
        {0x3836, 0x001},
        {0x3837, 0x000},
        {0x3841, 0x002},
        {0x3846, 0x008},
        {0x3847, 0x007},
        {0x3d85, 0x036},
        {0x3d8c, 0x071},
        {0x3d8d, 0x0cb},
        {0x3f0a, 0x000},
        {0x4000, 0x071},
        {0x4001, 0x040},
        {0x4002, 0x004},
        {0x4003, 0x014},
        {0x400e, 0x000},
        {0x4011, 0x000},
        {0x401a, 0x000},
        {0x401b, 0x000},
        {0x401c, 0x000},
        {0x401d, 0x000},
        {0x401f, 0x000},
        {0x4020, 0x000},
        {0x4021, 0x010},
        {0x4022, 0x006},
        {0x4023, 0x083},
        {0x4024, 0x007},
        {0x4025, 0x0b0},
        {0x4026, 0x007},
        {0x4027, 0x0c0},
        {0x4028, 0x000},
        {0x4029, 0x002},
        {0x402a, 0x006},
        {0x402b, 0x004},
        {0x402c, 0x002},
        {0x402d, 0x002},
        {0x402e, 0x00e},
        {0x402f, 0x004},
        {0x4302, 0x0ff},
        {0x4303, 0x0ff},
        {0x4304, 0x000},
        {0x4305, 0x000},
        {0x4306, 0x000},
        {0x4308, 0x002},
        {0x4500, 0x06c},
        {0x4501, 0x0c4},
        {0x4502, 0x040},
        {0x4503, 0x001},
        {0x4601, 0x07e},
        {0x4800, 0x004},
        {0x4813, 0x008},
        {0x481f, 0x040},
        {0x4829, 0x078},
        {0x4837, 0x02c},
        {0x4b00, 0x02a},
        {0x4b0d, 0x000},
        {0x4d00, 0x004},
        {0x4d01, 0x042},
        {0x4d02, 0x0d1},
        {0x4d03, 0x093},
        {0x4d04, 0x0f5},
        {0x4d05, 0x0c1},
        {0x5000, 0x0f3},
        {0x5001, 0x011},
        {0x5004, 0x000},
        {0x500a, 0x000},
        {0x500b, 0x000},
        {0x5032, 0x000},

        #if 0//(TEST_PATTERN_EN)
        {0x5040, 0x80}, // PRE_CONTROL00, 0x00, RW
                  // Bit[7]:   Test pattern enable
                  //           0: disable
                  //           1: enable
                  // Bit[6]:   Rolling bar enable
                  //           0: disable
                  //           1: enable
                  // Bit[5]:   Tansparent enable
                  //           0: disable
                  //           1: enable
                  // Bit[4]:   Square enable
                  //           0: Color square
                  //           1: Black-white square
                  // Bit[3:2]: Color style
                  //           00: Standard color bar
                  //           01: Top-bottom darker color bar
                  //           10: Right-left darker color bar
                  //           11: Bottom-top darker color bar
                  // Bit[1:0]: Test pattern mode
                  //           00: Color bar
                  //           01: Random data
                  //           10: Square
                  //           01: Black image
        {0x5041, 0x00}, // PRE_CONTROL01, 0x41, RW
                  // Bit[6]:   Window cut enable
                  //           0: disable
                  //           1: enable
                  // Bit[4]:   Same seed enable
                  //           When set, the seed used to generate the
                  //           random data are same which is set in
                  //           seed register
                  // Bit[3:0]: Seed
                  //           Seed used in generating random data
        #else
        {0x5040, 0x000},
        #endif
        {0x5050, 0x00c},
        {0x5500, 0x000},
        {0x5501, 0x010},
        {0x5502, 0x001},
        {0x5503, 0x00f},
        {0x8000, 0x000},
        {0x8001, 0x000},
        {0x8002, 0x000},
        {0x8003, 0x000},
        {0x8004, 0x000},
        {0x8005, 0x000},
        {0x8006, 0x000},
        {0x8007, 0x000},
        {0x8008, 0x000},
        {0x3638, 0x000},
        {0x0100, 0x001},
        //SENSOR_DELAY_REG, 100, // delay

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

#if 1

        {0x3500,  0x0},
        {0x3501,  0x30},//{0x3501,  0x9},
        {0x3502,  0x0},
        {0x350A,  0x0},
        {0x350B,  0x0},
        {0x350C,  0x00},//{0x350C,  0xE0},
        {0x3508,  0x0},
        {0x3509,  0x88},
        {0x350E,  0x0},
        {0x350F,  0x8C},
#if 0
        //static I2C_ARRAY gain_reg[] =
        //{
        {0x3508, 0x00},            //long a-gain[15:8]
        {0x3509, 0x70},            //long a-gain[7:0]
        {0x352A, 0x00},            // d-gain[14:8]
        {0x352B, 0x00},            // d-gain[7:0]
        //};

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

        //static I2C_ARRAY expo_reg[] =
        //{
            {0x3208, 0x00},            //Group 0 hold start
            {0x3500, 0x00},            //long exp[19,16]
            {0x3501, 0x02},            //long exp[15,8]
            {0x3502, 0x00},            //long exp[7,0]
        //};

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

        //static I2C_ARRAY vts_reg[] =
        //{
        {0x380E, 0x7F & ( 1642 >> 8 )},
        {0x380F, 0xFF & ( 1642 )},
        {0x3208, 0x10},            //Group 0 hold end
        // {0x320B, 0x00},//manual launch
        {0x3208, 0xa0},            // Group delay launch
                        //   {0x3208, 0x00},//quick launch group 0
        //};
#endif
#endif
#endif


#else //#if (OV4689_4LANE == 1) //2LANE

    //SNR_OV4689_Reg_1920x1080_30P
    {0x0103, 0x01},
    {0x3638, 0x00},

#if (SLOW_CLK == 1)
#if 0 //No stable, MIPI CLK rate = 32MHz
    {0x0300, 0x04},
    {0x030a, 0x01},
    {0x0302, 0x20},
#endif
#if 0 //Work, MIPI CLK rate = ??MHz
    {0x0300, 0x04},
    {0x030a, 0x01},
    {0x0302, 0x28},
#endif
#if 0 //Work, MIPI CLK rate = ??MHz
    {0x0300, 0x04},
    {0x030a, 0x01},
    {0x0302, 0x24},
#endif
#if 0 //Work, MIPI CLK rate = ??MHz
    {0x0300, 0x04},
    {0x030a, 0x01},
    {0x0302, 0x22},
#endif
#if 1 //Work, MIPI CLK rate = ??MHz
    {0x0300, 0x04},
    {0x030a, 0x00},//{0x030a, 0x01},
    {0x0302, 0x21},
#endif
#else
    {0x0300, 0x00},
    {0x0302, 0x1e}, // 0x2a
#endif

    {0x0303, 0x01}, // 0x00
    {0x0304, 0x03},

#if (SLOW_CLK == 1)
    {0x030b, 0x05},
    {0x0311, 0x01},
#else
    {0x030b, 0x00},
    {0x0311, 0x00},
#endif

    {0x030d, 0x1e},
    {0x030e, 0x04},
    {0x030f, 0x01},
    {0x0312, 0x01},
    {0x031e, 0x00},
    {0x3000, 0x20},
    {0x3002, 0x00},

    {0x3018, 0x32},// 0x72, // 0x32/0x72 // 2lane/4lane
    {0x3019, 0x0c},//0x00, // 0x0c/0x00 // 2lane/4lane
    {0x3020, 0x93},
    {0x3021, 0x03},
    {0x3022, 0x01},
    {0x3031, 0x0a},
    {0x303f, 0x0c},
    {0x3305, 0xf1},
    {0x3307, 0x04},
    {0x3309, 0x29},
    {0x3500, 0x00},
    {0x3501, 0x46}, // 0x61
    {0x3502, 0x80}, // 0x00
    {0x3503, 0x04},
    {0x3504, 0x00},
    {0x3505, 0x00},
    {0x3506, 0x00},
    {0x3507, 0x00},
    {0x3508, 0x07}, // 0x8X
    {0x3509, 0x78}, // 0x80
    {0x350a, 0x00},
    {0x350b, 0x00},
    {0x350c, 0x00},
    {0x350d, 0x00},
    {0x350e, 0x00},
    {0x350f, 0x80},
    {0x3510, 0x00},
    {0x3511, 0x00},
    {0x3512, 0x00},
    {0x3513, 0x00},
    {0x3514, 0x00},
    {0x3515, 0x80},
    {0x3516, 0x00},
    {0x3517, 0x00},
    {0x3518, 0x00},
    {0x3519, 0x00},
    {0x351a, 0x00},
    {0x351b, 0x80},
    {0x351c, 0x00},
    {0x351d, 0x00},
    {0x351e, 0x00},
    {0x351f, 0x00},
    {0x3520, 0x00},
    {0x3521, 0x80},
    {0x3522, 0x08},
    {0x3524, 0x08},
    {0x3526, 0x08},
    {0x3528, 0x08},
    {0x352a, 0x08},
    {0x3602, 0x00},
    {0x3603, 0x40},
    {0x3604, 0x02},
    {0x3605, 0x00},
    {0x3606, 0x00},
    {0x3607, 0x00},
    {0x3609, 0x12},
    {0x360a, 0x40},
    {0x360c, 0x08},
    //{0x360f, 0xe5},
    {0x360f, 0xdb},
    {0x3608, 0x8f},
    {0x3611, 0x00},
    {0x3613, 0xf7},
    {0x3616, 0x58},
    {0x3619, 0x99},
    {0x361b, 0x60},
    {0x361c, 0x7a},
    {0x361e, 0x79},
    {0x361f, 0x02},
    {0x3632, 0x00},
    {0x3633, 0x10},
    {0x3634, 0x10},
    //{0x3636, 0x15},
    {0x3636, 0x10},
    {0x3635, 0x10},
    {0x3646, 0x86},
    {0x364a, 0x0b},
    {0x3700, 0x17},
    {0x3701, 0x22},
    {0x3703, 0x10},
    {0x370a, 0x37},
    {0x3705, 0x00},
    {0x3706, 0x63},
    {0x3709, 0x3c},
    {0x370b, 0x01},
    {0x370c, 0x30},
    {0x3710, 0x24},
    {0x3711, 0x0c},
    {0x3716, 0x00},
    {0x3720, 0x28},
    {0x3729, 0x7b},
    {0x372a, 0x84},
    {0x372b, 0xbd},
    {0x372c, 0xbc},
    {0x372e, 0x52},
    {0x373c, 0x0e},
    {0x373e, 0x33},
    {0x3743, 0x10},
    {0x3744, 0x88},
    {0x3745, 0xc0},
    {0x374a, 0x43},
    {0x374c, 0x00},
    {0x374e, 0x23},
    {0x3751, 0x7b},
    {0x3752, 0x84},
    {0x3753, 0xbd},
    {0x3754, 0xbc},
    {0x3756, 0x52},
    {0x375c, 0x00},
    {0x3760, 0x00},
    {0x3761, 0x00},
    {0x3762, 0x00},
    {0x3763, 0x00},
    {0x3764, 0x00},
    {0x3767, 0x04},
    {0x3768, 0x04},
    {0x3769, 0x08},
    {0x376a, 0x08},
    {0x376b, 0x20},
    {0x376c, 0x00},
    {0x376d, 0x00},
    {0x376e, 0x00},
    {0x3773, 0x00},
    {0x3774, 0x51},
    {0x3776, 0xbd},
    {0x3777, 0xbd},
    {0x3781, 0x18},
    {0x3783, 0x25},
    {0x3798, 0x1b},
    {0x3800, 0x01},
    {0x3801, 0x84}, // 0x24
    {0x3802, 0x00},
    {0x3803, 0xda}, // 0xa6
    {0x3804, 0x09},
    {0x3805, 0x1b}, // 0x7b
    {0x3806, 0x05},
    {0x3807, 0x25}, // 0x59
    {0x3808, 0x07}, // 0x08
    {0x3809, 0x88}, // 0x48
    {0x380a, 0x04},
    {0x380b, 0x44}, // 0xac
    {0x380c, 0x0d}, // 0x0a // 0x14 // 0x0a // 0x03
    {0x380d, 0xbc}, // 0x04 // 0xf6 // 0x30 // 0x18 // 0x5c
    {0x380e, 0x04}, // 0x06
    {0x380f, 0x70}, // 0x1c // 0x20 // 0x12
    {0x3810, 0x00},
    {0x3811, 0x08},
    {0x3812, 0x00},
    {0x3813, 0x04},
    {0x3814, 0x01},
    {0x3815, 0x01},
    {0x3819, 0x01},
#if SENSOR_ROTATE_180
    {0x3820, 0x06}, // Tom: 0x00: No Flip, 0x06: Row & Column Flip
    {0x3821, 0x00}, // Tom: 0x06: No Flip, 0x00: Row & Column Flip
#else
    {0x3820, 0x00},
    {0x3821, 0x06},
#endif
    {0x3829, 0x00},
    {0x382a, 0x01},
    {0x382b, 0x01},
    {0x382d, 0x7f},
    {0x3830, 0x04},
    {0x3836, 0x01},
    {0x3837, 0x00},
    {0x3841, 0x02},
    {0x3846, 0x08},
    {0x3847, 0x07},
    {0x3d85, 0x36},
    {0x3d8c, 0x71},
    {0x3d8d, 0xcb},
    {0x3f0a, 0x00},
    {0x4000, 0x71},
    {0x4001, 0x40},
    {0x4002, 0x04},
    {0x4003, 0x14},
    {0x400e, 0x00},
    {0x4011, 0x00},
    {0x401a, 0x00},
    {0x401b, 0x00},
    {0x401c, 0x00},
    {0x401d, 0x00},
    {0x401f, 0x00},
    {0x4020, 0x00},
    {0x4021, 0x10},
    {0x4022, 0x06},
    {0x4023, 0x1b}, // 0x3f
    {0x4024, 0x07},
    {0x4025, 0x48}, // 0x6c
    {0x4026, 0x07},
    {0x4027, 0x58}, // 0x7b
    {0x4028, 0x00},
    {0x4029, 0x02},
    {0x402a, 0x06},
    {0x402b, 0x04},
    {0x402c, 0x02},
    {0x402d, 0x02},
    {0x402e, 0x0e},
    {0x402f, 0x04},
    {0x4302, 0xff},
    {0x4303, 0xff},
    {0x4304, 0x00},
    {0x4305, 0x00},
    {0x4306, 0x00},
    {0x4308, 0x02},
    {0x4500, 0x6c},
    {0x4501, 0xc4},
    {0x4502, 0x40},
    {0x4503, 0x01},
    {0x4601, 0x77},
    {0x4800, 0x04},
    {0x4813, 0x08},
    {0x481f, 0x40},
    {0x4829, 0x78},
    {0x4837, 0x16},//0x2c, // 0x18
    {0x4b00, 0x2a},
    {0x4b0d, 0x00},
    {0x4d00, 0x04},
    {0x4d01, 0x42},
    {0x4d02, 0xd1},
    {0x4d03, 0x93},
    {0x4d04, 0xf5},
    {0x4d05, 0xc1},
    {0x5000, 0xf3},
    {0x5001, 0x11},
    {0x5004, 0x00},
    {0x500a, 0x00},
    {0x500b, 0x00},
    {0x5032, 0x00},

#if 0//(TEST_PATTERN_EN)
    {0x5040, 0x80}, // PRE_CONTROL00, 0x00, RW
          // Bit[7]:   Test pattern enable
          //           0: disable
          //           1: enable
          // Bit[6]:   Rolling bar enable
          //           0: disable
          //           1: enable
          // Bit[5]:   Tansparent enable
          //           0: disable
          //           1: enable
          // Bit[4]:   Square enable
          //           0: Color square
          //           1: Black-white square
          // Bit[3:2]: Color style
          //           00: Standard color bar
          //           01: Top-bottom darker color bar
          //           10: Right-left darker color bar
          //           11: Bottom-top darker color bar
          // Bit[1:0]: Test pattern mode
          //           00: Color bar
          //           01: Random data
          //           10: Square
          //           01: Black image
    {0x5041, 0x00}, // PRE_CONTROL01, 0x41, RW
          // Bit[6]:   Window cut enable
          //           0: disable
          //           1: enable
          // Bit[4]:   Same seed enable
          //           When set, the seed used to generate the
          //           random data are same which is set in
          //           seed register
          // Bit[3:0]: Seed
          //           Seed used in generating random data
#else
    {0x5040, 0x00},
#endif

    {0x5050, 0x0c},
    {0x5500, 0x00},
    {0x5501, 0x10},
    {0x5502, 0x01},
    {0x5503, 0x0f},
    {0x8000, 0x00},
    {0x8001, 0x00},
    {0x8002, 0x00},
    {0x8003, 0x00},
    {0x8004, 0x00},
    {0x8005, 0x00},
    {0x8006, 0x00},
    {0x8007, 0x00},
    {0x8008, 0x00},
    {0x3638, 0x00},
    {0x0100, 0x01},

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

#if 1

        {0x3500,  0x0},
        {0x3501,  0x30},//{0x3501,  0x9},
        {0x3502,  0x0},
        {0x350A,  0x0},
        {0x350B,  0x0},
        {0x350C,  0x00},//{0x350C,  0xE0},
        {0x3508,  0x0},
        {0x3509,  0x88},
        {0x350E,  0x0},
        {0x350F,  0x8C},
#endif

#endif //#if (OV4689_4LANE == 1)



#else //#if (SLOW_CLK == 1)


                #if 0 //for 486M
                {   0x0103,0x01},
                {   0x0100,0x00},
                {   0x3638,0x00},
                {   0x0300,0x00},
                {   0x0302,0x12},            //; for MIPI data rate=486Mbps
                {   0x0303,0x00},
                {   0x0304,0x03},
                {   0x030b,0x00},
                {   0x030d,0x1b},            //; SCLK= 121.5MHz
                {   0x030e,0x04},
                {   0x030f,0x01},
                {   0x0312,0x01},
                {   0x031e,0x00},
                {   0x3000,0x20},
                {   0x3002,0x00},
                {   0x3018,0x32},
                {   0x3020,0x93},
                {   0x3021,0x03},
                {   0x3022,0x01},
                {   0x3031,0x0a},
                {   0x303f,0x0c},
                {   0x3305,0xf1},
                {   0x3307,0x04},
                {   0x3309,0x29},
                {   0x3500,0x00},
                {   0x3501,0x60},
                {   0x3502,0x00},
                {   0x3503,0x04},
                {   0x3504,0x00},
                {   0x3505,0x00},
                {   0x3506,0x00},
                {   0x3507,0x00},
                {   0x3508,0x00},
                {   0x3509,0x80},
                {   0x350a,0x00},
                {   0x350b,0x00},
                {   0x350c,0x00},
                {   0x350d,0x00},
                {   0x350e,0x00},
                {   0x350f,0x80},
                {   0x3510,0x00},
                {   0x3511,0x00},
                {   0x3512,0x00},
                {   0x3513,0x00},
                {   0x3514,0x00},
                {   0x3515,0x80},
                {   0x3516,0x00},
                {   0x3517,0x00},
                {   0x3518,0x00},
                {   0x3519,0x00},
                {   0x351a,0x00},
                {   0x351b,0x80},
                {   0x351c,0x00},
                {   0x351d,0x00},
                {   0x351e,0x00},
                {   0x351f,0x00},
                {   0x3520,0x00},
                {   0x3521,0x80},
                {   0x3522,0x08},
                {   0x3524,0x08},
                {   0x3526,0x08},
                {   0x3528,0x08},
                {   0x352a,0x08},
                {   0x3602,0x00},
                {   0x3603,0x40},
                {   0x3604,0x02},
                {   0x3605,0x00},
                {   0x3606,0x00},
                {   0x3607,0x00},
                {   0x3609,0x12},
                {   0x360a,0x40},
                {   0x360c,0x08},
                {   0x360f,0xe5},            //; for 4689 e0 for4686
                {   0x3608,0x8f},
                {   0x3611,0x00},
                {   0x3613,0xf7},
                {   0x3616,0x58},
                {   0x3619,0x99},
                {   0x361b,0x60},
                {   0x361c,0x7a},
                {   0x361e,0x79},
                {   0x361f,0x02},
                {   0x3632,0x00},
                {   0x3633,0x10},
                {   0x3634,0x10},
                {   0x3635,0x10},
                {   0x3636,0x15},            //; for 4689 10 for4686
                {   0x3646,0x86},
                {   0x364a,0x0b},
                {   0x3700,0x17},
                {   0x3701,0x22},
                {   0x3703,0x10},
                {   0x370a,0x37},
                {   0x3705,0x00},
                {   0x3706,0x63},
                {   0x3709,0x3c},
                {   0x370b,0x01},
                {   0x370c,0x30},
                {   0x3710,0x24},
                {   0x3711,0x0c},
                {   0x3716,0x00},
                {   0x3720,0x28},
                {   0x3729,0x7b},
                {   0x372a,0x84},
                {   0x372b,0xbd},
                {   0x372c,0xbc},
                {   0x372e,0x52},
                {   0x373c,0x0e},
                {   0x373e,0x33},
                {   0x3743,0x10},
                {   0x3744,0x88},
                {   0x3745,0xc0},
                {   0x374a,0x43},
                {   0x374c,0x00},
                {   0x374e,0x23},
                {   0x3751,0x7b},
                {   0x3752,0x84},
                {   0x3753,0xbd},
                {   0x3754,0xbc},
                {   0x3756,0x52},
                {   0x375c,0x00},
                {   0x3760,0x00},
                {   0x3761,0x00},
                {   0x3762,0x00},
                {   0x3763,0x00},
                {   0x3764,0x00},
                {   0x3767,0x04},
                {   0x3768,0x04},
                {   0x3769,0x08},
                {   0x376a,0x08},
                {   0x376b,0x20},
                {   0x376c,0x00},
                {   0x376d,0x00},
                {   0x376e,0x00},
                {   0x3773,0x00},
                {   0x3774,0x51},
                {   0x3776,0xbd},
                {   0x3777,0xbd},
                {   0x3781,0x18},
                {   0x3783,0x25},
                {   0x3798,0x1b},
                {   0x3800,0x00},
                {   0x3801,0x08},
                {   0x3802,0x00},
                {   0x3803,0x04},
                {   0x3804,0x0a},
                {   0x3805,0x97},
                {   0x3806,0x05},
                {   0x3807,0xfb},
                {   0x3808,0x1a},
                {   0x3809,0x80},
                {   0x380a,0x05},
                {   0x380b,0xf0},
                {   0x380c,(Hts>>8)&0x7F},            //HTS
                {   0x380d,Hts&0xFF},
                {   0x380e,0x06},
                {   0x380f,0x14},
                {   0x3810,0x00},
                {   0x3811,0x08},
                {   0x3812,0x00},
                {   0x3813,0x04},
                {   0x3814,0x01},
                {   0x3815,0x01},
                {   0x3819,0x01},
                {   0x3820,0x00},
                {   0x3821,0x06},
                {   0x3829,0x00},
                {   0x382a,0x01},
                {   0x382b,0x01},
                {   0x382d,0x7f},
                {   0x3830,0x04},
                {   0x3836,0x01},
                {   0x3837,0x00},
                {   0x3841,0x02},
                {   0x3846,0x08},
                {   0x3847,0x07},
                {   0x3d85,0x36},
                {   0x3d8c,0x71},
                {   0x3d8d,0xcb},
                {   0x3f0a,0x00},
                {   0x4000,0xf1},
                {   0x4001,0x40},
                {   0x4002,0x04},
                {   0x4003,0x14},
                {   0x400e,0x00},
                {   0x4011,0x00},
                {   0x401a,0x00},
                {   0x401b,0x00},
                {   0x401c,0x00},
                {   0x401d,0x00},
                {   0x401f,0x00},
                {   0x4020,0x00},
                {   0x4021,0x10},
                {   0x4022,0x07},
                {   0x4023,0xcf},
                {   0x4024,0x09},
                {   0x4025,0x60},
                {   0x4026,0x09},
                {   0x4027,0x6f},
                {   0x4028,0x00},
                {   0x4029,0x02},
                {   0x402a,0x06},
                {   0x402b,0x04},
                {   0x402c,0x02},
                {   0x402d,0x02},
                {   0x402e,0x0e},
                {   0x402f,0x04},
                {   0x4302,0xff},
                {   0x4303,0xff},
                {   0x4304,0x00},
                {   0x4305,0x00},
                {   0x4306,0x00},
                {   0x4308,0x02},
                {   0x4500,0x6c},
                {   0x4501,0xc4},
                {   0x4502,0x40},
                {   0x4503,0x01},
                {   0x4601,0xA7},
                {   0x4800,0x04},
                {   0x4813,0x08},
                {   0x481f,0x40},
                {   0x4829,0x78},
                {   0x4837,0x20},
                {   0x4b00,0x2a},
                {   0x4b0d,0x00},
                {   0x4d00,0x04},
                {   0x4d01,0x42},
                {   0x4d02,0xd1},
                {   0x4d03,0x93},
                {   0x4d04,0xf5},
                {   0x4d05,0xc1},
                {   0x5000,0xf3},
                {   0x5001,0x11},
                {   0x5004,0x00},
                {   0x500a,0x00},
                {   0x500b,0x00},
                {   0x5032,0x00},
                {   0x5040,0x00},
                {   0x5050,0x0c},
                {   0x5500,0x00},
                {   0x5501,0x10},
                {   0x5502,0x01},
                {   0x5503,0x0f},
                {   0x8000,0x00},
                {   0x8001,0x00},
                {   0x8002,0x00},
                {   0x8003,0x00},
                {   0x8004,0x00},
                {   0x8005,0x00},
                {   0x8006,0x00},
                {   0x8007,0x00},
                {   0x8008,0x00},
                {   0x3638,0x00},
                {   0x0100,0x01},
#else //for 4M
                {0x0103, 0x01},
                {0x0100, 0x00},
                {0x3638, 0x00},
                #if MIPI_CLK==783
                {0x0300, 0x00},            //pre div = 1
                {0x0302, 0x1d},            //; for MIPI data rate=783Mbps
                {0x0303, 0x00},
                {0x0304, 0x03},
                {0x030b, 0x00},
                {0x030d, 0x1b},            //; SCLK= 121.5MHz
                {0x030e, 0x04},
                {0x030f, 0x01},
                #endif
#if MCLK_CLK==626 //Need FAE check
                {   0x0300,0x00},            //pre div = 1
                {   0x0302,0x1d},            //; for MIPI data rate=783Mbps
                {   0x0303,0x00},
                {   0x0304,0x03},
                {   0x030b,0x00},
                {   0x030d,0x1b},            //; SCLK= 121.5MHz
                {   0x030e,0x04},
                {   0x030f,0x01},
#endif

#if MIPI_CLK == 567 //Need FAE check
                {   0x0300,0x00},            //pre div = 1
                {   0x0302,0x15},            //x21 for MIPI data rate=576Mbps
                {   0x0303,0x00},
                {   0x0304,0x03},
                {   0x030b,0x00},            // FOR SCLK 90MHz
                {   0x030d,0x14},            // x20
                {   0x030e,0x04},            // /3
                {   0x030f,0x01},            // /2
#endif

#if MIPI_CLK == 540//Need FAE check
                {   0x0300,0x00},            //pre div = 1
                {   0x0302,0x14},            // x20 for MIPI data rate=540Mbps
                {   0x0303,0x00},            // x1
                {   0x0304,0x03},            //
                {   0x030b,0x00},            // FOR SCLK 85.5MHz
                {   0x030d,0x13},            // x19
                {   0x030e,0x04},            // /3
                {   0x030f,0x01},            // /2
#endif

                {0x0312, 0x01},
                {0x031e, 0x00},
                {0x3000, 0x20},
                {0x3002, 0x00},
                {0x3018, 0x32},
                {0x3020, 0x93},
                {0x3021, 0x03},
                {0x3022, 0x01},
                {0x3031, 0x0a},
                {0x303f, 0x0c},
                {0x3305, 0xf1},
                {0x3307, 0x04},
                {0x3309, 0x29},
                {0x3500, 0x00},
                {0x3501, 0x60},
                {0x3502, 0x00},
                {0x3503, 0x04},
                {0x3504, 0x00},
                {0x3505, 0x00},
                {0x3506, 0x00},
                {0x3507, 0x00},
                {0x3508, 0x00},
                {0x3509, 0x80},
                {0x350a, 0x00},
                {0x350b, 0x00},
                {0x350c, 0x00},
                {0x350d, 0x00},
                {0x350e, 0x00},
                {0x350f, 0x80},
                {0x3510, 0x00},
                {0x3511, 0x00},
                {0x3512, 0x00},
                {0x3513, 0x00},
                {0x3514, 0x00},
                {0x3515, 0x80},
                {0x3516, 0x00},
                {0x3517, 0x00},
                {0x3518, 0x00},
                {0x3519, 0x00},
                {0x351a, 0x00},
                {0x351b, 0x80},
                {0x351c, 0x00},
                {0x351d, 0x00},
                {0x351e, 0x00},
                {0x351f, 0x00},
                {0x3520, 0x00},
                {0x3521, 0x80},
                {0x3522, 0x08},
                {0x3524, 0x08},
                {0x3526, 0x08},
                {0x3528, 0x08},
                {0x352a, 0x08},
                {0x3602, 0x00},
                {0x3603, 0x40},
                {0x3604, 0x02},
                {0x3605, 0x00},
                {0x3606, 0x00},
                {0x3607, 0x00},
                {0x3609, 0x12},
                {0x360a, 0x40},
                {0x360c, 0x08},
                {0x360f, 0xe5},            //360f e0 ;for OV4686, 0xE5 for OV4689
                {0x3608, 0x8f},
                {0x3611, 0x00},
                {0x3613, 0xf7},
                {0x3616, 0x58},
                {0x3619, 0x99},
                {0x361b, 0x60},
                {0x361c, 0x7a},
                {0x361e, 0x79},
                {0x361f, 0x02},
                {0x3632, 0x00},
                {0x3633, 0x10},
                {0x3634, 0x10},
                {0x3635, 0x10},
                {0x3636, 0x15},            //3636 10 ;for OV4686, 0x15 for OV4689
                {0x3646, 0x86},
                {0x364a, 0x0b},
                {0x3700, 0x17},
                {0x3701, 0x22},
                {0x3703, 0x10},
                {0x370a, 0x37},
                {0x3705, 0x00},
                {0x3706, 0x63},
                {0x3709, 0x3c},
                {0x370b, 0x01},
                {0x370c, 0x30},
                {0x3710, 0x24},
                {0x3711, 0x0c},
                {0x3716, 0x00},
                {0x3720, 0x28},
                {0x3729, 0x7b},
                {0x372a, 0x84},
                {0x372b, 0xbd},
                {0x372c, 0xbc},
                {0x372e, 0x52},
                {0x373c, 0x0e},
                {0x373e, 0x33},
                {0x3743, 0x10},
                {0x3744, 0x88},
                {0x3745, 0xc0},
                {0x374a, 0x43},
                {0x374c, 0x00},
                {0x374e, 0x23},
                {0x3751, 0x7b},
                {0x3752, 0x84},
                {0x3753, 0xbd},
                {0x3754, 0xbc},
                {0x3756, 0x52},
                {0x375c, 0x00},
                {0x3760, 0x00},
                {0x3761, 0x00},
                {0x3762, 0x00},
                {0x3763, 0x00},
                {0x3764, 0x00},
                {0x3767, 0x04},
                {0x3768, 0x04},
                {0x3769, 0x08},
                {0x376a, 0x08},
                {0x376b, 0x20},
                {0x376c, 0x00},
                {0x376d, 0x00},
                {0x376e, 0x00},
                {0x3773, 0x00},
                {0x3774, 0x51},
                {0x3776, 0xbd},
                {0x3777, 0xbd},
                {0x3781, 0x18},
                {0x3783, 0x25},
                {0x3798, 0x1b},
                {0x3800, 0x00},
                {0x3801, 0x08},
                {0x3802, 0x00},
                {0x3803, 0x04},
                {0x3804, 0x0a},
                {0x3805, 0x97},
                {0x3806, 0x05},
                {0x3807, 0xfb},
                {0x3808, 0x1a},
                {0x3809, 0x80},
                {0x380a, 0x05},
                {0x380b, 0xf0},
                //{0x380c,0x0f},//HTS
//{0x380d,0x45},
                {0x380c, ( Hts >> 8 ) & 0x7F},            //HTS
                {0x380d, Hts & 0xFF},
                {0x380e, 0x06},            //VTS for 20fps
                {0x380f, 0x12},
                {0x3810, 0x00},
                {0x3811, 0x08},
                {0x3812, 0x00},
                {0x3813, 0x04},
                {0x3814, 0x01},
                {0x3815, 0x01},
                {0x3819, 0x01},
                {0x3820, 0x00},
                {0x3821, 0x06},
                {0x3829, 0x00},
                {0x382a, 0x01},
                {0x382b, 0x01},
                {0x382d, 0x7f},
                {0x3830, 0x04},
                {0x3836, 0x01},
                {0x3837, 0x00},
                {0x3841, 0x02},
                {0x3846, 0x08},
                {0x3847, 0x07},
                {0x3d85, 0x36},
                {0x3d8c, 0x71},
                {0x3d8d, 0xcb},
                {0x3f0a, 0x00},
                {0x4000, 0xf1},
                {0x4001, 0x40},
                {0x4002, 0x04},
                {0x4003, 0x14},
                {0x400e, 0x00},
                {0x4011, 0x00},
                {0x401a, 0x00},
                {0x401b, 0x00},
                {0x401c, 0x00},
                {0x401d, 0x00},
                {0x401f, 0x00},
                {0x4020, 0x00},
                {0x4021, 0x10},
                {0x4022, 0x07},
                {0x4023, 0xcf},
                {0x4024, 0x09},
                {0x4025, 0x60},
                {0x4026, 0x09},
                {0x4027, 0x6f},
                {0x4028, 0x00},
                {0x4029, 0x02},
                {0x402a, 0x06},
                {0x402b, 0x04},
                {0x402c, 0x02},
                {0x402d, 0x02},
                {0x402e, 0x0e},
                {0x402f, 0x04},
                {0x4302, 0xff},
                {0x4303, 0xff},
                {0x4304, 0x00},
                {0x4305, 0x00},
                {0x4306, 0x00},
                {0x4308, 0x02},
                {0x4500, 0x6c},
                {0x4501, 0xc4},
                {0x4502, 0x40},
                {0x4503, 0x01},
                {0x4601, 0xA7},
                {0x4800, 0x04},
                {0x4813, 0x08},
                {0x481f, 0x40},
                {0x4829, 0x78},
                {0x4837, 0x14},
                {0x4b00, 0x2a},
                {0x4b0d, 0x00},
                {0x4d00, 0x04},
                {0x4d01, 0x42},
                {0x4d02, 0xd1},
                {0x4d03, 0x93},
                {0x4d04, 0xf5},
                {0x4d05, 0xc1},
                {0x5000, 0xf3},
                {0x5001, 0x11},
                {0x5004, 0x00},
                {0x500a, 0x00},
                {0x500b, 0x00},
                {0x5032, 0x00},
                {0x5040, 0x00},
                {0x5050, 0x0c},
                {0x5500, 0x00},
                {0x5501, 0x10},
                {0x5502, 0x01},
                {0x5503, 0x0f},
                {0x8000, 0x00},
                {0x8001, 0x00},
                {0x8002, 0x00},
                {0x8003, 0x00},
                {0x8004, 0x00},
                {0x8005, 0x00},
                {0x8006, 0x00},
                {0x8007, 0x00},
                {0x8008, 0x00},
                {0x3638, 0x00},
                {0x0100, 0x01},

#endif

#endif //#if (SLOW_CLK == 1)
                };
static I2C_ARRAY Sensor_init_table_2lane[] =
{
    //SNR_OV4689_Reg_1920x1080_30P
    {0x0103, 0x01},
    {0x3638, 0x00},

#if (SLOW_CLK == 1)
#if 0 //No stable, MIPI CLK rate = 32MHz
    {0x0300, 0x04},
    {0x030a, 0x01},
    {0x0302, 0x20},
#endif
#if 0 //Work, MIPI CLK rate = ??MHz
    {0x0300, 0x04},
    {0x030a, 0x01},
    {0x0302, 0x28},
#endif
#if 0 //Work, MIPI CLK rate = ??MHz
    {0x0300, 0x04},
    {0x030a, 0x01},
    {0x0302, 0x24},
#endif
#if 0 //Work, MIPI CLK rate = ??MHz
    {0x0300, 0x04},
    {0x030a, 0x01},
    {0x0302, 0x22},
#endif
#if 1 //Work, MIPI CLK rate = ??MHz
    {0x0300, 0x04},
    {0x030a, 0x00},//{0x030a, 0x01},
    {0x0302, 0x21},
#endif
#else
    {0x0300, 0x00},
    {0x0302, 0x1e}, // 0x2a
#endif

    {0x0303, 0x01}, // 0x00
    {0x0304, 0x03},

#if (SLOW_CLK == 1)
    {0x030b, 0x05},
    {0x0311, 0x01},
#else
    {0x030b, 0x00},
    {0x0311, 0x00},
#endif

    {0x030d, 0x1e},
    {0x030e, 0x04},
    {0x030f, 0x01},
    {0x0312, 0x01},
    {0x031e, 0x00},
    {0x3000, 0x20},
    {0x3002, 0x00},

    {0x3018, 0x32},// 0x72, // 0x32/0x72 // 2lane/4lane
    {0x3019, 0x0c},//0x00, // 0x0c/0x00 // 2lane/4lane
    {0x3020, 0x93},
    {0x3021, 0x03},
    {0x3022, 0x01},
    {0x3031, 0x0a},
    {0x303f, 0x0c},
    {0x3305, 0xf1},
    {0x3307, 0x04},
    {0x3309, 0x29},
    {0x3500, 0x00},
    {0x3501, 0x46}, // 0x61
    {0x3502, 0x80}, // 0x00
    {0x3503, 0x04},
    {0x3504, 0x00},
    {0x3505, 0x00},
    {0x3506, 0x00},
    {0x3507, 0x00},
    {0x3508, 0x07}, // 0x8X
    {0x3509, 0x78}, // 0x80
    {0x350a, 0x00},
    {0x350b, 0x00},
    {0x350c, 0x00},
    {0x350d, 0x00},
    {0x350e, 0x00},
    {0x350f, 0x80},
    {0x3510, 0x00},
    {0x3511, 0x00},
    {0x3512, 0x00},
    {0x3513, 0x00},
    {0x3514, 0x00},
    {0x3515, 0x80},
    {0x3516, 0x00},
    {0x3517, 0x00},
    {0x3518, 0x00},
    {0x3519, 0x00},
    {0x351a, 0x00},
    {0x351b, 0x80},
    {0x351c, 0x00},
    {0x351d, 0x00},
    {0x351e, 0x00},
    {0x351f, 0x00},
    {0x3520, 0x00},
    {0x3521, 0x80},
    {0x3522, 0x08},
    {0x3524, 0x08},
    {0x3526, 0x08},
    {0x3528, 0x08},
    {0x352a, 0x08},
    {0x3602, 0x00},
    {0x3603, 0x40},
    {0x3604, 0x02},
    {0x3605, 0x00},
    {0x3606, 0x00},
    {0x3607, 0x00},
    {0x3609, 0x12},
    {0x360a, 0x40},
    {0x360c, 0x08},
    //{0x360f, 0xe5},
    {0x360f, 0xdb},
    {0x3608, 0x8f},
    {0x3611, 0x00},
    {0x3613, 0xf7},
    {0x3616, 0x58},
    {0x3619, 0x99},
    {0x361b, 0x60},
    {0x361c, 0x7a},
    {0x361e, 0x79},
    {0x361f, 0x02},
    {0x3632, 0x00},
    {0x3633, 0x10},
    {0x3634, 0x10},
    //{0x3636, 0x15},
    {0x3636, 0x10},
    {0x3635, 0x10},
    {0x3646, 0x86},
    {0x364a, 0x0b},
    {0x3700, 0x17},
    {0x3701, 0x22},
    {0x3703, 0x10},
    {0x370a, 0x37},
    {0x3705, 0x00},
    {0x3706, 0x63},
    {0x3709, 0x3c},
    {0x370b, 0x01},
    {0x370c, 0x30},
    {0x3710, 0x24},
    {0x3711, 0x0c},
    {0x3716, 0x00},
    {0x3720, 0x28},
    {0x3729, 0x7b},
    {0x372a, 0x84},
    {0x372b, 0xbd},
    {0x372c, 0xbc},
    {0x372e, 0x52},
    {0x373c, 0x0e},
    {0x373e, 0x33},
    {0x3743, 0x10},
    {0x3744, 0x88},
    {0x3745, 0xc0},
    {0x374a, 0x43},
    {0x374c, 0x00},
    {0x374e, 0x23},
    {0x3751, 0x7b},
    {0x3752, 0x84},
    {0x3753, 0xbd},
    {0x3754, 0xbc},
    {0x3756, 0x52},
    {0x375c, 0x00},
    {0x3760, 0x00},
    {0x3761, 0x00},
    {0x3762, 0x00},
    {0x3763, 0x00},
    {0x3764, 0x00},
    {0x3767, 0x04},
    {0x3768, 0x04},
    {0x3769, 0x08},
    {0x376a, 0x08},
    {0x376b, 0x20},
    {0x376c, 0x00},
    {0x376d, 0x00},
    {0x376e, 0x00},
    {0x3773, 0x00},
    {0x3774, 0x51},
    {0x3776, 0xbd},
    {0x3777, 0xbd},
    {0x3781, 0x18},
    {0x3783, 0x25},
    {0x3798, 0x1b},
    {0x3800, 0x01},
    {0x3801, 0x84}, // 0x24
    {0x3802, 0x00},
    {0x3803, 0xda}, // 0xa6
    {0x3804, 0x09},
    {0x3805, 0x1b}, // 0x7b
    {0x3806, 0x05},
    {0x3807, 0x25}, // 0x59
    {0x3808, 0x07}, // 0x08
    {0x3809, 0x88}, // 0x48
    {0x380a, 0x04},
    {0x380b, 0x44}, // 0xac
    {0x380c, 0x0d}, // 0x0a // 0x14 // 0x0a // 0x03
    {0x380d, 0xbc}, // 0x04 // 0xf6 // 0x30 // 0x18 // 0x5c
    {0x380e, 0x04}, // 0x06
    {0x380f, 0x70}, // 0x1c // 0x20 // 0x12
    {0x3810, 0x00},
    {0x3811, 0x08},
    {0x3812, 0x00},
    {0x3813, 0x04},
    {0x3814, 0x01},
    {0x3815, 0x01},
    {0x3819, 0x01},
#if SENSOR_ROTATE_180
    {0x3820, 0x06}, // Tom: 0x00: No Flip, 0x06: Row & Column Flip
    {0x3821, 0x00}, // Tom: 0x06: No Flip, 0x00: Row & Column Flip
#else
    {0x3820, 0x00},
    {0x3821, 0x06},
#endif
    {0x3829, 0x00},
    {0x382a, 0x01},
    {0x382b, 0x01},
    {0x382d, 0x7f},
    {0x3830, 0x04},
    {0x3836, 0x01},
    {0x3837, 0x00},
    {0x3841, 0x02},
    {0x3846, 0x08},
    {0x3847, 0x07},
    {0x3d85, 0x36},
    {0x3d8c, 0x71},
    {0x3d8d, 0xcb},
    {0x3f0a, 0x00},
    {0x4000, 0x71},
    {0x4001, 0x40},
    {0x4002, 0x04},
    {0x4003, 0x14},
    {0x400e, 0x00},
    {0x4011, 0x00},
    {0x401a, 0x00},
    {0x401b, 0x00},
    {0x401c, 0x00},
    {0x401d, 0x00},
    {0x401f, 0x00},
    {0x4020, 0x00},
    {0x4021, 0x10},
    {0x4022, 0x06},
    {0x4023, 0x1b}, // 0x3f
    {0x4024, 0x07},
    {0x4025, 0x48}, // 0x6c
    {0x4026, 0x07},
    {0x4027, 0x58}, // 0x7b
    {0x4028, 0x00},
    {0x4029, 0x02},
    {0x402a, 0x06},
    {0x402b, 0x04},
    {0x402c, 0x02},
    {0x402d, 0x02},
    {0x402e, 0x0e},
    {0x402f, 0x04},
    {0x4302, 0xff},
    {0x4303, 0xff},
    {0x4304, 0x00},
    {0x4305, 0x00},
    {0x4306, 0x00},
    {0x4308, 0x02},
    {0x4500, 0x6c},
    {0x4501, 0xc4},
    {0x4502, 0x40},
    {0x4503, 0x01},
    {0x4601, 0x77},
    {0x4800, 0x04},
    {0x4813, 0x08},
    {0x481f, 0x40},
    {0x4829, 0x78},
    {0x4837, 0x16},//0x2c, // 0x18
    {0x4b00, 0x2a},
    {0x4b0d, 0x00},
    {0x4d00, 0x04},
    {0x4d01, 0x42},
    {0x4d02, 0xd1},
    {0x4d03, 0x93},
    {0x4d04, 0xf5},
    {0x4d05, 0xc1},
    {0x5000, 0xf3},
    {0x5001, 0x11},
    {0x5004, 0x00},
    {0x500a, 0x00},
    {0x500b, 0x00},
    {0x5032, 0x00},

#if 0//(TEST_PATTERN_EN)
    {0x5040, 0x80}, // PRE_CONTROL00, 0x00, RW
          // Bit[7]:   Test pattern enable
          //           0: disable
          //           1: enable
          // Bit[6]:   Rolling bar enable
          //           0: disable
          //           1: enable
          // Bit[5]:   Tansparent enable
          //           0: disable
          //           1: enable
          // Bit[4]:   Square enable
          //           0: Color square
          //           1: Black-white square
          // Bit[3:2]: Color style
          //           00: Standard color bar
          //           01: Top-bottom darker color bar
          //           10: Right-left darker color bar
          //           11: Bottom-top darker color bar
          // Bit[1:0]: Test pattern mode
          //           00: Color bar
          //           01: Random data
          //           10: Square
          //           01: Black image
    {0x5041, 0x00}, // PRE_CONTROL01, 0x41, RW
          // Bit[6]:   Window cut enable
          //           0: disable
          //           1: enable
          // Bit[4]:   Same seed enable
          //           When set, the seed used to generate the
          //           random data are same which is set in
          //           seed register
          // Bit[3:0]: Seed
          //           Seed used in generating random data
#else
    {0x5040, 0x00},
#endif

    {0x5050, 0x0c},
    {0x5500, 0x00},
    {0x5501, 0x10},
    {0x5502, 0x01},
    {0x5503, 0x0f},
    {0x8000, 0x00},
    {0x8001, 0x00},
    {0x8002, 0x00},
    {0x8003, 0x00},
    {0x8004, 0x00},
    {0x8005, 0x00},
    {0x8006, 0x00},
    {0x8007, 0x00},
    {0x8008, 0x00},
    {0x3638, 0x00},
    {0x0100, 0x01},

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

#if 1

        {0x3500,  0x0},
        {0x3501,  0x30},//{0x3501,  0x9},
        {0x3502,  0x0},
        {0x350A,  0x0},
        {0x350B,  0x0},
        {0x350C,  0x00},//{0x350C,  0xE0},
        {0x3508,  0x0},
        {0x3509,  0x88},
        {0x350E,  0x0},
        {0x350F,  0x8C}
#endif
};

static I2C_ARRAY Sensor_init_table_4lane_1288x724_60fps[] =
{
    /*
     * @@ RES_1288x724_2x_Bin_60fps_360Mbps
     *
     * 100 99 1288 724
     * 102 3601 1770
     */

    /*
     * ----------------------------------------------
     *  MCLK: 24Mhz
     *  resolution: 1288x724
     *  Mipi: 4 lane
     *  Mipi data rate: 360Mbps/Lane
     *  SystemCLK: 120Mhz
     *  FPS: 60 (= SystemCLK / (HTS * VTS))
     *  HTS: 2508 (R380c:R380d)
     *  VTS: 797 (R380e:R380f)
     *  Tline: 20.9us
     *  Max exp line: 779 (VTS-8)
     * ---------------------------------------------
     */

    {0x0103, 0x01},
    {0x3638, 0x00},
    {0x0300, 0x00},
    {0x0302, 0x1e}, // 0x2a
    {0x0303, 0x01}, // 0x00
    {0x0304, 0x03},
    {0x030b, 0x00},
    {0x030d, 0x1e},
    {0x030e, 0x04},
    {0x030f, 0x01},
    {0x0312, 0x01},
    {0x031e, 0x00},
    {0x3000, 0x20},
    {0x3002, 0x00},
    {0x3018, 0x72}, // 0x32/0x72 // 2lane/4lane
    {0x3019, 0x00}, // 0x0c/0x00 // 2lane/4lane
    {0x3020, 0x93},
    {0x3021, 0x03},
    {0x3022, 0x01},
    {0x3031, 0x0a},
    {0x303f, 0x0c},
    {0x3305, 0xf1},
    {0x3307, 0x04},
    {0x3309, 0x29},
    {0x3500, 0x00},
    {0x3501, 0x31},
    {0x3502, 0x00},
    {0x3503, 0x04},
    {0x3504, 0x00},
    {0x3505, 0x00},
    {0x3506, 0x00},
    {0x3507, 0x00},
    {0x3508, 0x07}, // 0x8X
    {0x3509, 0x78},
    {0x350a, 0x00},
    {0x350b, 0x00},
    {0x350c, 0x00},
    {0x350d, 0x00},
    {0x350e, 0x00},
    {0x350f, 0x80},
    {0x3510, 0x00},
    {0x3511, 0x00},
    {0x3512, 0x00},
    {0x3513, 0x00},
    {0x3514, 0x00},
    {0x3515, 0x80},
    {0x3516, 0x00},
    {0x3517, 0x00},
    {0x3518, 0x00},
    {0x3519, 0x00},
    {0x351a, 0x00},
    {0x351b, 0x80},
    {0x351c, 0x00},
    {0x351d, 0x00},
    {0x351e, 0x00},
    {0x351f, 0x00},
    {0x3520, 0x00},
    {0x3521, 0x80},
    {0x3522, 0x08},
    {0x3524, 0x08},
    {0x3526, 0x08},
    {0x3528, 0x08},
    {0x352a, 0x08},
    {0x3602, 0x00},
    {0x3603, 0x40},
    {0x3604, 0x02},
    {0x3605, 0x00},
    {0x3606, 0x00},
    {0x3607, 0x00},
    {0x3609, 0x12},
    {0x360a, 0x40},
    {0x360c, 0x08},
      //{0x360f, 0xe5},
    //{0x360f, 0x}db,
    {0x360f, 0xe0},
    {0x3608, 0x8f},
    {0x3611, 0x00},
    {0x3613, 0xf7},
    {0x3616, 0x58},
    {0x3619, 0x99},
    {0x361b, 0x60},
    {0x361c, 0x7a},
    {0x361e, 0x79},
    {0x361f, 0x02},
    {0x3632, 0x05},
    {0x3633, 0x10},
    {0x3634, 0x10},
    {0x3635, 0x10},
      //{0x3636, 0x15},
    {0x3636, 0x10},
    {0x3646, 0x86},
    {0x364a, 0x0b},
    {0x3700, 0x17},
    {0x3701, 0x22},
    {0x3703, 0x10},
    {0x370a, 0x37},
    {0x3705, 0x00},
    {0x3706, 0x63},
    {0x3709, 0x3c},
    {0x370b, 0x01},
    {0x370c, 0x30},
    {0x3710, 0x24},
    {0x3711, 0x0c},
    {0x3716, 0x00},
    {0x3720, 0x28},
    {0x3729, 0x7b},
    {0x372a, 0x84},
    {0x372b, 0xbd},
    {0x372c, 0xbc},
    {0x372e, 0x52},
    {0x373c, 0x0e},
    {0x373e, 0x33},
    {0x3743, 0x10},
    {0x3744, 0x88},
    {0x3745, 0xc0},
    {0x374a, 0x43},
    {0x374c, 0x00},
    {0x374e, 0x23},
    {0x3751, 0x7b},
    {0x3752, 0x84},
    {0x3753, 0xbd},
    {0x3754, 0xbc},
    {0x3756, 0x52},
    {0x375c, 0x00},
    {0x3760, 0x00},
    {0x3761, 0x00},
    {0x3762, 0x00},
    {0x3763, 0x00},
    {0x3764, 0x00},
    {0x3767, 0x04},
    {0x3768, 0x04},
    {0x3769, 0x08},
    {0x376a, 0x08},
    {0x376b, 0x40},
    {0x376c, 0x00},
    {0x376d, 0x00},
    {0x376e, 0x00},
    {0x3773, 0x00},
    {0x3774, 0x51},
    {0x3776, 0xbd},
    {0x3777, 0xbd},
    {0x3781, 0x18},
    {0x3783, 0x25},
    {0x3798, 0x1b},
    {0x3800, 0x00},
    {0x3801, 0x40},
    {0x3802, 0x00},
    {0x3803, 0x28},
    {0x3804, 0x0a},
    {0x3805, 0x5f},
    {0x3806, 0x05},
    {0x3807, 0xD7},
    {0x3808, 0x05},
    {0x3809, 0x08},
    {0x380a, 0x02},
    {0x380b, 0xD4},
    {0x380c, 0x09}, // 0x03
    {0x380d, 0xcc}, // 0x5C
    {0x380e, 0x03},
    {0x380f, 0x1d},
    {0x3810, 0x00},
    {0x3811, 0x04},
    {0x3812, 0x00},
    {0x3813, 0x02},
    {0x3814, 0x03},
    {0x3815, 0x01},
    {0x3819, 0x01},
#if SENSOR_ROTATE_180
    {0x3820, 0x16}, // Tom: 0x00: No Flip, 0x06: Row & Column Flip
    {0x3821, 0x01}, // Tom: 0x06: No Flip, 0x00: Row & Column Flip
#else
    {0x3820, 0x10},
    {0x3821, 0x07},
#endif
    {0x3829, 0x00},
    {0x382a, 0x03},
    {0x382b, 0x01},
    {0x382d, 0x7f},
    {0x3830, 0x08},
    {0x3836, 0x02},
    {0x3837, 0x00},
    {0x3841, 0x02},
    {0x3846, 0x08},
    {0x3847, 0x07},
    {0x3d85, 0x36},
    {0x3d8c, 0x71},
    {0x3d8d, 0xcb},
    {0x3f0a, 0x00},
    {0x4000, 0x71},
    {0x4001, 0x50},
    {0x4002, 0x04},
    {0x4003, 0x14},
    {0x400e, 0x00},
    {0x4011, 0x00},
    {0x401a, 0x00},
    {0x401b, 0x00},
    {0x401c, 0x00},
    {0x401d, 0x00},
    {0x401f, 0x00},
    {0x4020, 0x00},
    {0x4021, 0x10},
    {0x4022, 0x03},
    {0x4023, 0x9b},
    {0x4024, 0x04},
    {0x4025, 0xc8},
    {0x4026, 0x04},
    {0x4027, 0xd8},
    {0x4028, 0x00},
    {0x4029, 0x02},
    {0x402a, 0x06},
    {0x402b, 0x04},
    {0x402c, 0x02},
    {0x402d, 0x02},
    {0x402e, 0x0e},
    {0x402f, 0x04},
    {0x4302, 0xff},
    {0x4303, 0xff},
    {0x4304, 0x00},
    {0x4305, 0x00},
    {0x4306, 0x00},
    {0x4308, 0x02},
    {0x4500, 0x6c},
    {0x4501, 0xc4},
    {0x4502, 0x44},
    {0x4503, 0x01},
    {0x4601, 0x4F},
    {0x4800, 0x04},
    {0x4813, 0x08},
    {0x481f, 0x40},
    {0x4829, 0x78},
    {0x4837, 0x2c}, // 0x20 // 0x10
    {0x4b00, 0x2a},
    {0x4b0d, 0x00},
    {0x4d00, 0x04},
    {0x4d01, 0x42},
    {0x4d02, 0xd1},
    {0x4d03, 0x93},
    {0x4d04, 0xf5},
    {0x4d05, 0xc1},
    {0x5000, 0xf3},
    {0x5001, 0x11},
    {0x5004, 0x00},
    {0x500a, 0x00},
    {0x500b, 0x00},
    {0x5032, 0x00},

#if (TEST_PATTERN_EN)
    {0x5040, 0x80}, // PRE_CONTROL00, 0x00, RW
                  // Bit[7]:   Test pattern enable
                  //           0: disable
                  //           1: enable
                  // Bit[6]:   Rolling bar enable
                  //           0: disable
                  //           1: enable
                  // Bit[5]:   Tansparent enable
                  //           0: disable
                  //           1: enable
                  // Bit[4]:   Square enable
                  //           0: Color square
                  //           1: Black-white square
                  // Bit[3:2]: Color style
                  //           00: Standard color bar
                  //           01: Top-bottom darker color bar
                  //           10: Right-left darker color bar
                  //           11: Bottom-top darker color bar
                  // Bit[1:0]: Test pattern mode
                  //           00: Color bar
                  //           01: Random data
                  //           10: Square
                  //           01: Black image
    {0x5041, 0x00}, // PRE_CONTROL01, 0x41, RW
                  // Bit[6]:   Window cut enable
                  //           0: disable
                  //           1: enable
                  // Bit[4]:   Same seed enable
                  //           When set, the seed used to generate the
                  //           random data are same which is set in
                  //           seed register
                  // Bit[3:0]: Seed
                  //           Seed used in generating random data
#else
    {0x5040, 0x00},
#endif
    {0x5050, 0x3c},
    {0x5500, 0x00},
    {0x5501, 0x10},
    {0x5502, 0x01},
    {0x5503, 0x0f},
    {0x8000, 0x00},
    {0x8001, 0x00},
    {0x8002, 0x00},
    {0x8003, 0x00},
    {0x8004, 0x00},
    {0x8005, 0x00},
    {0x8006, 0x00},
    {0x8007, 0x00},
    {0x8008, 0x00},
    {0x3638, 0x00},
    {0x0100, 0x01},
};

static I2C_ARRAY TriggerStartTbl[] =
{
{0x0100, 0x01},            //normal mode
                };

static I2C_ARRAY PatternTbl[] =
{
{0x5040, 0x00},            //colorbar pattern , bit 7 to enable
                };

static I2C_ARRAY Current_Mirror_Flip_Tbl[] =
{
{0x3820, 0x00},            //M0F0
{0x3821, 0x00},

};
/*
static I2C_ARRAY BadPixelTbl[] = {

// {0x5000,0x5F&(~0x04)},

                };*/

/////////////////////////////////////////////////////////////////
//       @@@@@@                                                                                    //
//                 @@                                                                                    //
//             @@@                                                                                      //
//       @       @@                                                                                    //
//         @@@@                                                                                        //
//                                                                                                          //
//      Step 3 --  complete camera features                                              //
//                                                                                                         //
//                                                                                                         //
//  camera set EV, MWB, orientation, contrast, sharpness                          //
//   , saturation, and Denoise can work correctly.                                     //
//                                                                                                          //
/////////////////////////////////////////////////////////////////

static I2C_ARRAY mirr_flip_table[] =
                {
                {0x3820, 0x00},            //M0F0
                {0x3821, 0x00},

                {0x3820, 0x00},            //M1F0
                {0x3821, 0x06},

                {0x3820, 0x06},            //M0F1
                {0x3821, 0x00},

                {0x3820, 0x06},            //M1F1
                {0x3821, 0x06},

                };

I2C_ARRAY AWB_GAIN_REG[] =
                {
                };

typedef struct
{
    short reg;
    char startbit;
    char stopbit;
} COLLECT_REG_SET;

static I2C_ARRAY gain_reg[] =
{
{0x3508, 0x00},            //long a-gain[15:8]
{0x3509, 0x70},            //long a-gain[7:0]
{0x352A, 0x00},            // d-gain[14:8]
{0x352B, 0x00},            // d-gain[7:0]

                };

//static int g_sensor_ae_min_gain = 1024;
static CUS_GAIN_GAP_ARRAY gain_gap_compensate[16] =
{            //compensate  gain gap
                {0, 0},
                {0, 0},
                {0, 0},
                {0, 0},
                {0, 0},
                {0, 0},
                {0, 0},
                {0, 0},
                {0, 0},
                {0, 0},
                {0, 0},
                {0, 0},
                {0, 0},
                {0, 0},
                {0, 0},
                {0, 0}
                };

static I2C_ARRAY expo_reg[] =
{
{0x3208, 0x00},            //Group 0 hold start
{0x3500, 0x00},            //long exp[19,16]
{0x3501, 0x02},            //long exp[15,8]
{0x3502, 0x00},            //long exp[7,0]
                };

static I2C_ARRAY vts_reg[] =
{
#if 0 //vts @20fps
{   0x380E, 0x7F&(vts_25fps>>8)},
{   0x380F, 0xFF&vts_25fps},
{   0x3208, 0x10},            //Group 0 hold end
// {0x320B, 0x00},//manual launch
{   0x3208, 0xa0},            // Group delay launch
//   {0x3208, 0x00},//quick launch group 0
#else
{0x380E, 0x7F & ( vts_25fps >> 8 )},
{0x380F, 0xFF & ( vts_25fps )},
{0x3208, 0x10},            //Group 0 hold end
// {0x320B, 0x00},//manual launch
{0x3208, 0xa0},            // Group delay launch
                //   {0x3208, 0x00},//quick launch group 0
#endif
                };
/*
static CUS_INT_TASK_ORDER def_order =
{
    .RunLength = 9,
    .Orders =
    {
        CUS_INT_TASK_AE | CUS_INT_TASK_VDOS | CUS_INT_TASK_AF,
        CUS_INT_TASK_AWB | CUS_INT_TASK_VDOS | CUS_INT_TASK_AF,
        CUS_INT_TASK_VDOS | CUS_INT_TASK_AF,
        CUS_INT_TASK_AE | CUS_INT_TASK_VDOS | CUS_INT_TASK_AF,
        CUS_INT_TASK_AWB | CUS_INT_TASK_VDOS | CUS_INT_TASK_AF,
        CUS_INT_TASK_VDOS | CUS_INT_TASK_AF,
        CUS_INT_TASK_AE | CUS_INT_TASK_VDOS | CUS_INT_TASK_AF,
        CUS_INT_TASK_AWB | CUS_INT_TASK_VDOS | CUS_INT_TASK_AF,
        CUS_INT_TASK_VDOS | CUS_INT_TASK_AF,
    },
};*/

/////////// function definition ///////////////////
#define SENSOR_NAME ov4689

static int OV4689_SetFPS( ms_cus_sensor *handle, u32 fps );

/////////////////// sensor hardware dependent //////////////
static int OV4689_poweron( ms_cus_sensor *handle )
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    SENSOR_DMSG( "[%s] ", __FUNCTION__ );

    //Sensor power on sequence
    //sensor_if->SetCSI_VC0HSmode(handle,PACKET_FOOTER_EDGE);
    // sensor_if->SetCSI_LongPacketType(handle,CSI_LONG_PACKET_TYPE_RAW12|CSI_LONG_PACKET_TYPE_RAW10);

    if(handle->interface_attr.attr_mipi.mipi_lane_num == 2){
        sensor_if->SetIOPad(handle->snr_pad_group, CUS_SENIF_BUS_MIPI, CUS_SR0_MIPI_MODE_1 );
    }

    if(handle->interface_attr.attr_mipi.mipi_lane_num == 4){
        sensor_if->SetIOPad(handle->snr_pad_group, CUS_SENIF_BUS_MIPI, CUS_SR0_MIPI_MODE_2);
    }

    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_216M, handle->PCLK_POLARITY);

    if(handle->interface_attr.attr_mipi.mipi_lane_num == 2){
        sensor_if->SetCSI_Lane(handle->snr_pad_group, 2, 1);
    }


    if(handle->interface_attr.attr_mipi.mipi_lane_num == 4){
        sensor_if->SetCSI_Lane(handle->snr_pad_group, 4, 1);
    }

    sensor_if->MCLK(handle->snr_pad_group, 1, handle->mclk );

    SENSOR_DMSG( "[%s] reset low\n", __FUNCTION__ );
    sensor_if->Reset(handle->snr_pad_group, handle->reset_POLARITY );
    MsSleep(RTK_MS_TO_TICK(100));//usleep( 500 );
    SENSOR_DMSG( "[%s] power low\n", __FUNCTION__ );
    sensor_if->PowerOff(handle->snr_pad_group, handle->pwdn_POLARITY );
    MsSleep(RTK_MS_TO_TICK(100));//usleep( 500 );
    ///////////////////

    // power -> high, reset -> high
    SENSOR_DMSG( "[%s] power high\n", __FUNCTION__ );
    sensor_if->PowerOff(handle->snr_pad_group, !handle->pwdn_POLARITY );
    MsSleep(RTK_MS_TO_TICK(100));//usleep( 500 );
    SENSOR_DMSG( "[%s] reset high\n", __FUNCTION__ );
    sensor_if->Reset(handle->snr_pad_group, !handle->reset_POLARITY );
    MsSleep(RTK_MS_TO_TICK(100));//usleep( 500 );

    // pure power on
    sensor_if->PowerOff(handle->snr_pad_group, !handle->pwdn_POLARITY );
	sensor_if->SWReset(handle->channel_num, FALSE);
    return SUCCESS;
}

static int OV4689_poweroff( ms_cus_sensor *handle )
{
    // power/reset low
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    SENSOR_DMSG( "[%s] power low\n", __FUNCTION__ );
	
	sensor_if->SWReset(handle->channel_num, TRUE);
    sensor_if->PowerOff( 1, handle->pwdn_POLARITY );
    MsSleep(RTK_MS_TO_TICK(100));//usleep( 1000 );
    //Set_csi_if(0, 0);
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_DISABLE, handle->PCLK_POLARITY);
    sensor_if->MCLK(0, 0, handle->mclk );

    if(handle->interface_attr.attr_mipi.mipi_lane_num == 2){
        sensor_if->SetCSI_Lane(handle->snr_pad_group, 2, 0);
    }


    if(handle->interface_attr.attr_mipi.mipi_lane_num == 4){
        sensor_if->SetCSI_Lane(handle->snr_pad_group, 4, 0);
    }

    return SUCCESS;
}

/////////////////// image function /////////////////////////
//Get and check sensor ID
//if i2c error or sensor id does not match then return FAIL
static int OV4689_GetSensorID( ms_cus_sensor *handle, u32 *id )
{
    int i, n;
    short sen_data1, sen_data2;
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

    //SENSOR_DMSG("\n\n[%s]", __FUNCTION__);

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
                    *id >>= 8;
                    SENSOR_EMSG( "[%s]OV4689 Read sensor id, get 0x%x Success\n", __FUNCTION__, ( int )*id );
                    return FAIL;
                }
            }
            break;
        }
        else
            MsSleep(RTK_MS_TO_TICK(1));//usleep( 1*1000 );
    }

#if 1//defined(__MV5_FPGA__) //For FPGA verification.
    *id >>= 8;
    SENSOR_DMSG( "[%s]OV4689 Read sensor id, get 0x%x Success\n", __FUNCTION__, (int)*id );
    UartSendTrace("[%s]OV4689 Read sensor id, get 0x%x Success\n",__FUNCTION__, (int)*id);
#else //#if defined(__MV5_FPGA__)
    for( i = 0; i < ARRAY_SIZE( Sensor_init_table ); i++ )
    {
        if( SensorReg_Write(Sensor_init_table[i].reg,Sensor_init_table[i].data) != SUCCESS )
        {
            SENSOR_DMSG( "[%s] I2C write fail\n", __FUNCTION__ );
            return FAIL;
        }
    }

    //  SensorReg_Write(0x0103,0x01);
    //  usleep(5000);
    SensorReg_Write( 0x0100, 0x01 );
    SensorReg_Write( 0x5000, 0xd3 );
    SensorReg_Write( 0x3d84, 0x00 );
    SensorReg_Write( 0x3d81, 0x01 );
    usleep( 5000 );
    SensorReg_Read( 0x7001, &sen_data1 );
    SensorReg_Read( 0x7002, &sen_data2 );
    SENSOR_DMSG( "[%s] sen_data1=0x%x,sen_data2=0x%x\n", __FUNCTION__, sen_data1, sen_data2 );
    if( sen_data2 != 0x89 )
        return FAIL;
#endif //#if defined(__MV5_FPGA__)

    return SUCCESS;
}

static int OV4689_SetPatternMode( ms_cus_sensor *handle, u32 mode )
{
    int i;
#if 1//defined(__MV5_FPGA__)
    return 0; //test only
#endif //#if defined(__MV5_FPGA__)

    switch( mode )
    {
        case 1:
            PatternTbl[0].data = 0x82;            //enable color square
            break;
        case 2:
            PatternTbl[0].data = 0x80;            //enable color bar
            break;
        case 0:
            PatternTbl[0].data &= 0x7F;            //disable
            break;
        default:
            PatternTbl[0].data &= 0x7F;            //disable
            break;
    }

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
    UartSendTrace("ov4689_MIPI reg: 0x%x, data: 0x%x, read: 0x%x.\n", usreg, usval, sen_data);

    return SUCCESS;
}

static int pCus_I2CRead(ms_cus_sensor *handle, unsigned short usreg, unsigned short* pusval)
{
    unsigned short usread_data;

    SensorReg_Read(usreg, &usread_data);
    *pusval = usread_data;
    UartSendTrace("ov4689_MIPI reg: 0x%x, data: 0x%x\n", usreg, usread_data);

    return SUCCESS;
}
#endif
static int OV4689_init( ms_cus_sensor *handle )
{
    SENSOR_DMSG( "\n\n[%s]", __FUNCTION__ );
    int i;
    I2C_ARRAY *pSensor_init_table = NULL;
    int ArraySize;
#if 1//defined(__MV5_FPGA__)
    unsigned short sen_data;
#endif //#if defined(__MV5_FPGA__)
    ISensorIfAPI *sensor_if = &( handle->sensor_if_api );
    sensor_if->PCLK( CUS_SNR_PCLK_MIPI_TOP );

    if(handle->interface_attr.attr_mipi.mipi_lane_num == 2)
    {
        pSensor_init_table = &Sensor_init_table_2lane;
        ArraySize = ARRAY_SIZE(Sensor_init_table_2lane);
    }
    else if(handle->interface_attr.attr_mipi.mipi_lane_num == 4)
    {
        pSensor_init_table = &Sensor_init_table;
        ArraySize = ARRAY_SIZE(Sensor_init_table);
    }
    //UartSendTrace("OV4689 ARRAY_SIZE( pSensor_init_table) %d\n",ARRAY_SIZE( &pSensor_init_table ));
    for( i = 0; i < ArraySize; i++ )
    {
        if( (pSensor_init_table+i)->reg == 0xffff ){
            MsSleep(RTK_MS_TO_TICK(1));//usleep( 1000*Sensor_init_table_R1C[i].data );
        }
        else{
            if( SensorReg_Write((pSensor_init_table+i)->reg,(pSensor_init_table+i)->data) != SUCCESS )
            {
                SENSOR_DMSG( "[%s] I2C write fail\n", __FUNCTION__ );
                return FAIL;
            }
#if 1//defined(__MV5_FPGA__)
            SensorReg_Read((pSensor_init_table+i)->reg, &sen_data);
            // printf("[%s] i=0x%x,sen_data=0x%x\n", __FUNCTION__,i,sen_data);
            UartSendTrace("OV4689 reg: 0x%x, data: 0x%x, read: 0x%x.\n",(pSensor_init_table+i)->reg, (pSensor_init_table+i)->data, sen_data);
            //MsSleep(20);
#endif //#if defined(__MV5_FPGA__)
        }
    }

#if 0
    UartSendTrace("\nOV4689 reg pattern\n");
    for( i = 0; i < ARRAY_SIZE( PatternTbl ); i++ )
    {
        if( SensorReg_Write(PatternTbl[i].reg,PatternTbl[i].data) != SUCCESS )
        {
            return FAIL;
        }
    }
#endif
    UartSendTrace("\nOV4689 reg Current_Mirror_Flip_Tbl\n");
    for( i = 0; i < ARRAY_SIZE( TriggerStartTbl ); i++ )
    {
        if( SensorReg_Write(TriggerStartTbl[i].reg,TriggerStartTbl[i].data) != SUCCESS )
        {
            return FAIL;
        }
    }
#if 0
    for( i = 0; i < ARRAY_SIZE( Current_Mirror_Flip_Tbl ); i++ )
    {
        if( SensorReg_Write(Current_Mirror_Flip_Tbl[i].reg,Current_Mirror_Flip_Tbl[i].data) != SUCCESS )
        {
            return FAIL;
        }

    }
#endif

    //OV4689_SetFPS(handle,19);//init fps
    OV4689_SetAEGain( handle, 2048 );
    OV4689_SetAEUSecs( handle, 25000 );
    return SUCCESS;
}

static int OV4689_init_4lane_1288x724_60fps( ms_cus_sensor *handle )
{
    SENSOR_DMSG( "\n\n[%s]", __FUNCTION__ );
    UartSendTrace( "\n$$$\n[%s]\n", __FUNCTION__ );

    int i;
#if 1//defined(__MV5_FPGA__)
    unsigned short sen_data;
#endif //#if defined(__MV5_FPGA__)
    ISensorIfAPI *sensor_if = &( handle->sensor_if_api );
    sensor_if->PCLK( CUS_SNR_PCLK_MIPI_TOP );

    for( i = 0; i < ARRAY_SIZE( Sensor_init_table_4lane_1288x724_60fps ); i++ )
    {
        if( Sensor_init_table_4lane_1288x724_60fps[i].reg == 0xffff ){
            MsSleep(RTK_MS_TO_TICK(1));//usleep( 1000*Sensor_init_table_R1C[i].data );
        }
        else{
            if( SensorReg_Write(Sensor_init_table_4lane_1288x724_60fps[i].reg,Sensor_init_table_4lane_1288x724_60fps[i].data) != SUCCESS )
            {
                SENSOR_DMSG( "[%s] I2C write fail\n", __FUNCTION__ );
                //ov4689_run = 0;
                return FAIL;
            }
#if 1//defined(__MV5_FPGA__)
            SensorReg_Read(Sensor_init_table_4lane_1288x724_60fps[i].reg, &sen_data);
            // printf("[%s] i=0x%x,sen_data=0x%x\n", __FUNCTION__,i,sen_data);
            UartSendTrace("OV4689 reg: 0x%x, data: 0x%x, read: 0x%x.\n",Sensor_init_table_4lane_1288x724_60fps[i].reg, Sensor_init_table_4lane_1288x724_60fps[i].data, sen_data);
            //MsSleep(20);
#endif //#if defined(__MV5_FPGA__)
        }
    }


#if 0
    UartSendTrace("\nOV4689 reg pattern\n");
    for( i = 0; i < ARRAY_SIZE( PatternTbl ); i++ )
    {
        if( SensorReg_Write(PatternTbl[i].reg,PatternTbl[i].data) != SUCCESS )
        {
            return FAIL;
        }
    }
#endif
    UartSendTrace("\nOV4689 reg Current_Mirror_Flip_Tbl\n");
    for( i = 0; i < ARRAY_SIZE( TriggerStartTbl ); i++ )
    {
        if( SensorReg_Write(TriggerStartTbl[i].reg,TriggerStartTbl[i].data) != SUCCESS )
        {
            return FAIL;
        }
    }
#if 0
    for( i = 0; i < ARRAY_SIZE( Current_Mirror_Flip_Tbl ); i++ )
    {
        if( SensorReg_Write(Current_Mirror_Flip_Tbl[i].reg,Current_Mirror_Flip_Tbl[i].data) != SUCCESS )
        {
            return FAIL;
        }

    }
#endif

    //OV4689_SetFPS(handle,19);//init fps
    OV4689_SetAEGain( handle, 2048 );
    OV4689_SetAEUSecs( handle, 25000 );

    //ov4689_run = 0;
    return SUCCESS;
}

static int OV4689_GetVideoResNum( ms_cus_sensor *handle, u32 *ulres_num)
{
    //return current resolution
    *ulres_num = handle->video_res_supported.num_res;
    return SUCCESS;
}

static int OV4689_GetVideoRes( ms_cus_sensor *handle, cus_camsensor_res **res )
{
    //return current resolution
    *res = &handle->video_res_supported.res[handle->video_res_supported.ulcur_res];
    return SUCCESS;
}

static int OV4689_SetVideoRes( ms_cus_sensor *handle, u32 res )
{
    //TODO: Set sensor output resolution
    //ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    switch(res){
        case SENSOR_DRIVER_MODE_SUPER_HD_30P_RESOLUTION:
            handle->video_res_supported.ulcur_res = RES_IDX_2304x1296_60P_HDR;
            //RES_IDX_2304x1296_60P_HDR //TBD
            break;

        case SENSOR_DRIVER_MODE_FULL_HD_30P_RESOLUTION:
            handle->video_res_supported.ulcur_res = RES_IDX_1920x1080_30P;
            handle->pCus_sensor_init = OV4689_init;
            break;

        case SENSOR_DRIVER_MODE_HD_60P_RESOLUTION:
            handle->video_res_supported.ulcur_res = RES_IDX_1280x720_60P;
            handle->pCus_sensor_init = OV4689_init_4lane_1288x724_60fps;
            break;

        default:
            break;
    }

    //sensor_if->WaitVEnd( 500 );
    return SUCCESS;
}

static int OV4689_GetOrien( ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT *orit )
{
    ov4689_params *params = ( ov4689_params * ) handle->private_data;
    return params->mirror_flip.cur;
#if 0
    short sen_data;
    SensorReg_Read(0x3818, &sen_data);            //always success now

    //LOGD("mirror:%x\r\n", sen_data & 0x60);
    switch(sen_data & 0x60)
    {
        case 0x00:
        *orit = CUS_ORIT_M0F0;
        break;
        case 0x40:
        *orit = CUS_ORIT_M1F0;
        break;
        case 0x20:
        *orit = CUS_ORIT_M0F1;
        break;
        case 0x60:
        *orit = CUS_ORIT_M1F1;
        break;
    }
    return SUCCESS;
#endif
}

static int DoMirror( ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT orit )
{
    int table_length = ARRAY_SIZE( mirr_flip_table );
    int seg_length = table_length / 4;
    int i, j;

    ov4689_params *params = ( ov4689_params * ) handle->private_data;

    SENSOR_DMSG( "\n\n[%s]", __FUNCTION__ );

    return SUCCESS;

    SensorReg_Write( 0x3208, 0x00 );

    switch( orit )
    {
        case CUS_ORIT_M0F0:
            for( i = 0, j = 0; i < seg_length; i++, j++ )
            {
                SensorReg_Write( mirr_flip_table[i].reg, mirr_flip_table[i].data );
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }
            //  handle->bayer_id=   CUS_BAYER_BG;
            break;

        case CUS_ORIT_M1F0:
            for( i = seg_length, j = 0; i < seg_length * 2; i++, j++ )
            {
                SensorReg_Write( mirr_flip_table[i].reg, mirr_flip_table[i].data );
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }
            //  handle->bayer_id=   CUS_BAYER_BG;
            break;

        case CUS_ORIT_M0F1:
            for( i = seg_length * 2, j = 0; i < seg_length * 3; i++, j++ )
            {
                SensorReg_Write( mirr_flip_table[i].reg, mirr_flip_table[i].data );
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }
            // handle->bayer_id=    CUS_BAYER_GR;
            break;

        case CUS_ORIT_M1F1:
            for( i = seg_length * 3, j = 0; i < seg_length * 4; i++, j++ )
            {
                SensorReg_Write( mirr_flip_table[i].reg, mirr_flip_table[i].data );
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }
            // handle->bayer_id=    CUS_BAYER_GR;
            break;

        default:
            for( i = 0, j = 0; i < seg_length; i++, j++ )
            {
                SensorReg_Write( mirr_flip_table[i].reg, mirr_flip_table[i].data );
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }
            //  handle->bayer_id=   CUS_BAYER_BG;
            break;
    }

    SensorReg_Write( 0x3208, 0x10 );
    SensorReg_Write( 0x3208, 0xa0 );

    params->mirror_flip.cur = orit;

    return SUCCESS;
}

static int OV4689_SetOrien( ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT orit )
{
    ov4689_params *params = ( ov4689_params * ) handle->private_data;
    params->mirror_flip.new_setting = orit;
    DoMirror( handle, params->mirror_flip.new_setting );
    return SUCCESS;
}

static int OV4689_GetFPS( ms_cus_sensor *handle )
{
    ov4689_params *params = ( ov4689_params * ) handle->private_data;

    SENSOR_DMSG( "[%s]", __FUNCTION__ );
    return params->expo.fps;
}

static int OV4689_SetFPS( ms_cus_sensor *handle, u32 fps )
{
    ov4689_params *params = ( ov4689_params * ) handle->private_data;
    SENSOR_DMSG( "\n\n[%s]", __FUNCTION__ );
#if defined(__MV5_FPGA__)
    return 0; //test only
#endif
    if( fps >= 2 && fps <= 60 )
    {

        params->expo.fps = fps;
        //params->expo.vts=  (vts_25fps*25)/fps;
        params->expo.vts = 1000000000 / ( Preview_line_period * fps );            //div64
        vts_reg[0].data = ( params->expo.vts >> 8 ) & 0x007f;
        vts_reg[1].data = ( params->expo.vts >> 0 ) & 0x00ff;
        return SensorRegArrayW( ( I2C_ARRAY* )vts_reg, ARRAY_SIZE(vts_reg) );
    }
    else if( fps >= 2000 && fps <= 60000 )
    {

        params->expo.fps = fps;
        //params->expo.vts=  (vts_25fps*25000)/fps;
        params->expo.vts = 1000000000000 / ( Preview_line_period * fps );            //div64
        vts_reg[0].data = ( params->expo.vts >> 8 ) & 0x007f;
        vts_reg[1].data = ( params->expo.vts >> 0 ) & 0x00ff;
        return SensorRegArrayW( ( I2C_ARRAY* )vts_reg, ARRAY_SIZE(vts_reg) );
    }
    else
    {
        SENSOR_EMSG( "[%s] FPS %d out of range.\n", __FUNCTION__, fps );
        return FAIL;
    }
}
static int OV4689_GetSensorCap( ms_cus_sensor *handle, CUS_CAMSENSOR_CAP *cap )
{
    if( cap )
        memcpy( cap, &sensor_cap, sizeof(CUS_CAMSENSOR_CAP) );
    else
        return FAIL;
    return SUCCESS;
}

///////////////////////////////////////////////////////////////////////
// auto exposure
///////////////////////////////////////////////////////////////////////
// unit: micro seconds
//AE status notification
static int OV4689_AEStatusNotify( ms_cus_sensor *handle, CUS_CAMSENSOR_AE_STATUS_NOTIFY status )
{
    ov4689_params *params = (ov4689_params *)handle->private_data;

    switch( status )
    {
        case CUS_FRAME_INACTIVE:
            break;
        case CUS_FRAME_ACTIVE:
            if (params->reg_dirty = true)
            {
                SensorRegArrayW( ( I2C_ARRAY* )expo_reg, ARRAY_SIZE(expo_reg) );
                SensorRegArrayW( ( I2C_ARRAY* )gain_reg, ARRAY_SIZE(gain_reg) );
                SensorRegArrayW( ( I2C_ARRAY* )vts_reg, ARRAY_SIZE(vts_reg) );
                params->reg_dirty = false;
            }
            break;
        default:
            break;
    }
    return SUCCESS;
}

static int OV4689_GetAEUSecs( ms_cus_sensor *handle, u32 *us )
{
    u32 lines = 0;
    //rc = SensorRegArrayR((I2C_ARRAY*)expo_reg, ARRAY_SIZE(expo_reg));

    lines |= ( u32 ) ( expo_reg[1].data & 0xff ) << 16;
    lines |= ( u32 ) ( expo_reg[2].data & 0xff ) << 8;
    lines |= ( u32 ) ( expo_reg[3].data & 0xff ) << 0;
    lines >>= 4;

    *us = ( lines * Preview_line_period );

    return SUCCESS;
}

static int OV4689_SetAEUSecs( ms_cus_sensor *handle, u32 us )
{
    u32 lines = 0, vts = 0;
    ov4689_params *params = ( ov4689_params * ) handle->private_data;
    // return SUCCESS;
#if defined(__MV5_FPGA__)
    return 0; //test only
#endif
    lines = ( 1000 * us ) / Preview_line_period;
    if( lines > params->expo.vts - 8 )
        vts = lines + 8;
    else
        vts = params->expo.vts;

    /*
     if(lines <= 16)
     {
     float ae_gain_compensate = ((1000.0f*us)/(lines*Preview_line_period));
     OV4689_SetAEGain(handle,params->gain* ae_gain_compensate);
     //printf("AE %d us,lines=%d,gain=%d, gain_comp=%.4f\n",us,lines,params->gain,ae_gain_compensate);
     }
     else*/
    OV4689_SetAEGain( handle, params->gain );

    SENSOR_DMSG( "[%s] us %ld, lines %ld, vts %ld\n", __FUNCTION__,
                    us,
                    lines,
                    params->expo.vts
                    );
    lines <<= 4;
    expo_reg[1].data = ( lines >> 16 ) & 0x000f;
    expo_reg[2].data = ( lines >> 8 ) & 0x00ff;
    expo_reg[3].data = ( lines >> 0 ) & 0x00ff;

    vts_reg[0].data = ( vts >> 8 ) & 0x007f;
    vts_reg[1].data = ( vts >> 0 ) & 0x00ff;

    params->reg_dirty = true;

    return 0;
}

//#define SENSOR_MAX_GAIN (15.5*1024)
// Gain: 1x = 1024
static int OV4689_GetAEGain( ms_cus_sensor *handle, u32* gain )
{
//=IF((B18=0),HEX2DEC(B19)/128,IF((B18=1),(HEX2DEC(B19)+8)/64,IF((B18=3),(HEX2DEC(B19)+12)/32,IF((B18=7),(HEX2DEC(B19)+8)/16,"Error"))))

    if( gain_reg[0].data == 0 )
        *gain = ( u32 ) ( ( gain_reg[1].data / 128 ) << 10 );
    else if( gain_reg[0].data == 1 )
        *gain = ( u32 ) ( ( ( gain_reg[1].data + 8 ) / 64 ) << 10 );
    else if( gain_reg[0].data == 3 )
        *gain = ( u32 ) ( ( ( gain_reg[1].data + 12 ) / 32 ) << 10 );
    else if( gain_reg[0].data == 7 )
        *gain = ( u32 ) ( ( ( gain_reg[1].data + 8 ) / 16 ) << 10 );

    SENSOR_DMSG( "[%s] get gain/reg0/reg1 (1024=1X)= %d/0x%x/0x%x\n", __FUNCTION__, *gain, gain_reg[0].data, gain_reg[1].data );
    return 0;
}

static int OV4689_SetAEGain_cal( ms_cus_sensor *handle, u32 gain )
{
    u32 input_gain = 0;
    // bool bEnableWhiteBadPixelComp = false, bEnableBlackBadPixelComp = false;

    // params->expo.final_gain = gain;
#if defined(__MV5_FPGA__)
    return 0; //test only
#endif
    if( gain < SENSOR_MIN_GAIN )
        gain = SENSOR_MIN_GAIN;
    else if( gain >= SENSOR_MAX_GAIN )
        gain = SENSOR_MAX_GAIN;

    input_gain = gain;

    if( ( gain >> 10 ) < 2 )
    {

        gain_reg[0].data = 0;
        gain_reg[1].data = ( gain * 128 ) >> 10;                 // 1X ~ 2X
    }
    else if( ( gain >> 10 ) < 4 )
    {

        gain_reg[0].data = 1;
        gain_reg[1].data = ( ( gain * 64 ) - ( 256 * 8 ) ) >> 10;            // 2X ~ 4X
    }
    else if( ( gain >> 10 ) < 8 )
    {

        gain_reg[0].data = 3;
        gain_reg[1].data = ( ( gain * 32 ) - ( 256 * 12 ) ) >> 10;            // 4X ~ 8X
    }
    else
    {

        gain_reg[0].data = 7;
        gain_reg[1].data = ( ( gain * 16 ) - ( 256 * 8 ) ) >> 10;            // 8X ~16X
    }

    if( input_gain > SENSOR_MAX_GAIN )
    {

        gain_reg[2].data = ( u16 ) ( ( input_gain / SENSOR_MAX_GAIN ) * 8 ) & 0x7F;
        gain_reg[3].data = ( u16 ) ( ( input_gain / SENSOR_MAX_GAIN ) * 2048 ) & 0xFF;
    }
    else
    {

        gain_reg[2].data = 0x04;
        gain_reg[3].data = 0;

    }
    SENSOR_DMSG( "[%s] set input gain/gain/regH/regL=%d/%d/0x%x/0x%x\n",
                    __FUNCTION__,
                    input_gain,
                    gain,
                    gain_reg[0].data,
                    gain_reg[1].data );
    return SensorRegArrayW( ( I2C_ARRAY* )gain_reg, sizeof( gain_reg ) / sizeof(I2C_ARRAY) );
}

static int OV4689_SetAEGain( ms_cus_sensor *handle, u32 gain )
{
    CUS_GAIN_GAP_ARRAY* Sensor_Gain_Linearity;
    ov4689_params *params = ( ov4689_params * ) handle->private_data;
    u32 i, input_gain = 0;
    // bool bEnableWhiteBadPixelComp = false, bEnableBlackBadPixelComp = false;
#if defined(__MV5_FPGA__)
    return 0; //test only
#endif

    gain = ( gain * handle->sat_mingain + 512 ) >> 10;            // need to add min sat gain
    //  params->expo.final_gain = gain;
    input_gain = gain;
    if( gain < SENSOR_MIN_GAIN )
        gain = SENSOR_MIN_GAIN;
    else if( gain >= SENSOR_MAX_GAIN )
        gain = SENSOR_MAX_GAIN;

    Sensor_Gain_Linearity = gain_gap_compensate;

    for( i = 0; i < sizeof( gain_gap_compensate ) / sizeof(CUS_GAIN_GAP_ARRAY); i++ )
    {
        //LOGD("GAP:%x %x\r\n",Sensor_Gain_Linearity[i].gain, Sensor_Gain_Linearity[i].offset);

        if( Sensor_Gain_Linearity[i].gain == 0 )
            break;
        if( ( gain > Sensor_Gain_Linearity[i].gain ) && ( gain < ( Sensor_Gain_Linearity[i].gain + Sensor_Gain_Linearity[i].offset ) ) )
        {
            gain = Sensor_Gain_Linearity[i].gain;
            break;
        }
    }

    if( ( gain >> 10 ) < 2 )
    {

        gain_reg[0].data = 0;
        gain_reg[1].data = ( gain * 128 ) >> 10;                 // 1X ~ 2X
    }
    else if( ( gain >> 10 ) < 4 )
    {

        gain_reg[0].data = 1;
        gain_reg[1].data = ( ( gain * 64 ) - ( 256 * 8 ) ) >> 10;            // 2X ~ 4X
    }
    else if( ( gain >> 10 ) < 8 )
    {

        gain_reg[0].data = 3;
        gain_reg[1].data = ( ( gain * 32 ) - ( 256 * 12 ) ) >> 10;            // 4X ~ 8X
    }
    else
    {

        gain_reg[0].data = 7;
        gain_reg[1].data = ( ( gain * 16 ) - ( 256 * 8 ) ) >> 10;            // 8X ~16X
    }

    if( input_gain > SENSOR_MAX_GAIN )
    {

        gain_reg[2].data = ( u16 ) ( ( input_gain / SENSOR_MAX_GAIN ) * 8 ) & 0x7F;
        gain_reg[3].data = ( u16 ) ( ( input_gain / SENSOR_MAX_GAIN ) * 2048 ) & 0xFF;
    }
    else
    {

        gain_reg[2].data = 0x08;
        gain_reg[3].data = 0;

    }

    SENSOR_DMSG( "[%s] set input gain/gain/regH/regL=%d/%d/0x%x/0x%x\n",
                    __FUNCTION__,
                    input_gain,
                    gain,
                    gain_reg[0].data,
                    gain_reg[1].data );
    params->reg_dirty = true;
    return SUCCESS;
}



static int DRIVER_SetAEGain( ms_cus_sensor *handle, u32 gain )
{
    ov4689_params *params = ( ov4689_params * ) handle->private_data;
#if defined(__MV5_FPGA__)
    return 0; //test only
#endif //#if defined(__MV5_FPGA__)

    if( gain < SENSOR_MIN_GAIN )
        gain = SENSOR_MIN_GAIN;
    else if( gain >= SENSOR_MAX_GAIN)
        gain = SENSOR_MAX_GAIN;

    params->gain = gain;
    //SENSOR_DMSG("OV4689 set gain = %d\n",gain);
#if 0
    u32 gain2_4,gain4_8,gain8_16,gain16_32,i, sensor_DataH, sensor_DataL;
    CUS_GAIN_GAP_ARRAY* Sensor_Gain_Linearity;
    bool bEnableWhiteBadPixelComp = false, bEnableBlackBadPixelComp = false;

    gain = (gain * handle->sat_mingain + 512)>>10;            // need to add min sat gain
    params->expo.final_gain = gain;

    if(gain<1024)
    gain=1024;
    else if(gain>=32767)
    gain=32767;

    Sensor_Gain_Linearity = gain_gap_compensate;

    for(i = 0; i < sizeof(gain_gap_compensate)/sizeof(CUS_GAIN_GAP_ARRAY); i++)
    {
        //LOGD("GAP:%x %x\r\n",Sensor_Gain_Linearity[i].gain, Sensor_Gain_Linearity[i].offset);

        if (Sensor_Gain_Linearity[i].gain == 0)
        break;
        if((gain>Sensor_Gain_Linearity[i].gain) && (gain < (Sensor_Gain_Linearity[i].gain + Sensor_Gain_Linearity[i].offset)))
        {
            gain=Sensor_Gain_Linearity[i].gain;
            break;
        }
    }

    if(gain<2048)
    {
        bEnableWhiteBadPixelComp = false;
        bEnableBlackBadPixelComp = false;
        gain_reg[0].data = (((gain-1024)>>6)) & 0x000f;            //<X2
    }
    else if((gain>=2048 )&&(gain<4096))            //X2~X4
    {
        bEnableWhiteBadPixelComp = true;
        bEnableBlackBadPixelComp = false;
        gain2_4=gain-2048;
        gain_reg[0].data = ((gain2_4>>7) & 0x000f)|0x10;
    }
    else if((gain>=4096 )&&(gain<8192))            //X4~X8
    {
        bEnableWhiteBadPixelComp = true;
        bEnableBlackBadPixelComp = false;
        gain4_8=gain-4096;
        gain_reg[0].data =( (gain4_8>>8) & 0x000f)|0x30;
    }
    else if((gain>=8192 )&&(gain<16384))            //X8~X16
    {
        bEnableWhiteBadPixelComp = true;
        bEnableBlackBadPixelComp = false;
        gain8_16=gain-8192;
        gain_reg[0].data =( (gain8_16>>9) & 0x000f)|0x70;
    }
    else if((gain>=16384 )&&(gain<32768))            //X16~X32
    {
        bEnableWhiteBadPixelComp = true;
        bEnableBlackBadPixelComp = false;
        gain16_32=gain-16384;
        gain_reg[0].data =( (gain16_32>>10) & 0x000f)|0xf0;
    }

    if (bEnableWhiteBadPixelComp)
    BadPixelTbl[0].data |= (0x0a);
    else
    BadPixelTbl[0].data &= ~(0x0a);

    if (bEnableBlackBadPixelComp)
    BadPixelTbl[0].data |= (0x04);
    else
    BadPixelTbl[0].data &= ~(0x04);

    SENSOR_DMSG("[%s] set gain/reg=0x%x/0x%x\n", __FUNCTION__, gain,gain_reg[0].data);
#endif

    return SUCCESS;
}

static int OV4689_GetAEMinMaxUSecs( ms_cus_sensor *handle, u32 *min, u32 *max )
{
    if (handle->video_res_supported.ulcur_res == RES_IDX_1920x1080_30P) {
        *min = 150;
        *max = 33332; // <- max shutter (30fps: 33332, 60fps:16666)
    }
    else if (handle->video_res_supported.ulcur_res == RES_IDX_1280x720_60P) {
        *min = 150;
        *max = 16666; // <- max shutter (30fps: 33332, 60fps:16666)
    }
    else {
        *min = 150;
        *max = 33332; // <- max shutter (30fps: 33332, 60fps:16666)
    }

    return SUCCESS;
}

static int OV4689_GetAEMinMaxGain( ms_cus_sensor *handle, u32 *min, u32 *max )
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

/*
static int OV4689_setCaliData_mingain( ms_cus_sensor* handle, u32 gain )
{
    handle->sat_mingain = gain;
    return SUCCESS;
}*/

static int OV4689_setCaliData_gain_linearity( ms_cus_sensor* handle, CUS_GAIN_GAP_ARRAY* pArray, u32 num )
{
    u32 i, j;

    for( i = 0, j = 0; i < num; i++, j += 2 )
    {
        gain_gap_compensate[i].gain = pArray[i].gain;
        gain_gap_compensate[i].offset = pArray[i].offset;
    }

    return SUCCESS;
}

static int OV4689_GetShutterInfo( struct __ms_cus_sensor* handle, CUS_SHUTTER_INFO *info )
{
    info->max = 1000000000 / 12;
    info->min = Preview_line_period * 4;
    info->step = Preview_line_period;
    return SUCCESS;
}

int ov4689_MIPI_cus_camsensor_init_handle( ms_cus_sensor* drv_handle )
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
    //private data allocation & init
#if defined(__RTK_OS__)
    sprintf(str, "OV4689linear");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(ov4689_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (ov4689_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(ov4689_params));
#else
    handle->private_data = calloc( 1, sizeof(ov4689_params) );
#endif
    ov4689_params *params = ( ov4689_params * ) handle->private_data;

    ////////////////////////////////////
    //    sensor model ID                           //
    ////////////////////////////////////
    sprintf( handle->model_id, "OV4689_MIPI" );

    ////////////////////////////////////
    //    sensor interface info       //
    ////////////////////////////////////
    //SENSOR_DMSG("[%s] entering function with id %d\n", __FUNCTION__, id);
    handle->isp_type = SENSOR_ISP_TYPE;            //ISP_SOC;
    //handle->data_fmt    = SENSOR_DATAFMT;   //CUS_DATAFMT_YUV;
    handle->sif_bus = SENSOR_IFBUS_TYPE;            //CUS_SENIF_BUS_PARL;
    handle->data_prec = SENSOR_DATAPREC;            //CUS_DATAPRECISION_8;
    handle->data_mode = SENSOR_DATAMODE;
    handle->bayer_id = SENSOR_BAYERID;            //CUS_BAYER_GB;
    handle->orient = SENSOR_ORIT;            //CUS_ORIT_M1F1;
    //handle->YC_ODER     = SENSOR_YCORDER;   //CUS_SEN_YCODR_CY;
    handle->interface_attr.attr_mipi.mipi_lane_num = SENSOR_MIPI_LANE_NUM;
    handle->interface_attr.attr_mipi.mipi_data_format = CUS_SEN_INPUT_FORMAT_RGB; // RGB pattern.
    handle->interface_attr.attr_mipi.mipi_yuv_order = 0; //don't care in RGB pattern.
    handle->interface_attr.attr_mipi.mipi_hsync_mode = SENSOR_MIPI_HSYNC_MODE;
    handle->interface_attr.attr_mipi.mipi_sampling_delay = SENSOR_MIPI_DELAY;
    handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_NONE;
    handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 0;

    ////////////////////////////////////
    //    resolution capability       //
    ////////////////////////////////////
    handle->video_res_supported.num_res = 3;
    handle->video_res_supported.ulcur_res = 0; //default resolution index is 0.
    handle->video_res_supported.res[RES_IDX_2304x1296_60P_HDR].width = 2304;
    handle->video_res_supported.res[RES_IDX_2304x1296_60P_HDR].height = 1296;
    handle->video_res_supported.res[RES_IDX_2304x1296_60P_HDR].max_fps = 30;
    handle->video_res_supported.res[RES_IDX_2304x1296_60P_HDR].min_fps = 30;
    handle->video_res_supported.res[RES_IDX_2304x1296_60P_HDR].crop_start_x = 1;
    handle->video_res_supported.res[RES_IDX_2304x1296_60P_HDR].crop_start_y = 1;
    handle->video_res_supported.res[RES_IDX_2304x1296_60P_HDR].nOutputWidth= 2304;
    handle->video_res_supported.res[RES_IDX_2304x1296_60P_HDR].nOutputHeight= 1296;

    handle->video_res_supported.res[RES_IDX_1920x1080_30P].width = 1920;
    handle->video_res_supported.res[RES_IDX_1920x1080_30P].height = 1080;
    handle->video_res_supported.res[RES_IDX_1920x1080_30P].max_fps = Preview_MAX_FPS;
    handle->video_res_supported.res[RES_IDX_1920x1080_30P].min_fps = Preview_MIN_FPS;
    handle->video_res_supported.res[RES_IDX_1920x1080_30P].crop_start_x = Preview_CROP_START_X;
    handle->video_res_supported.res[RES_IDX_1920x1080_30P].crop_start_y = Preview_CROP_START_Y;
    handle->video_res_supported.res[RES_IDX_1920x1080_30P].nOutputWidth= Preview_WIDTH;
    handle->video_res_supported.res[RES_IDX_1920x1080_30P].nOutputHeight= Preview_HEIGHT;

    handle->video_res_supported.res[RES_IDX_1280x720_60P].width = 1280;
    handle->video_res_supported.res[RES_IDX_1280x720_60P].height = 720;
    handle->video_res_supported.res[RES_IDX_1280x720_60P].max_fps = 60;
    handle->video_res_supported.res[RES_IDX_1280x720_60P].min_fps = 60;
    handle->video_res_supported.res[RES_IDX_1280x720_60P].crop_start_x = Preview_CROP_START_X;
    handle->video_res_supported.res[RES_IDX_1280x720_60P].crop_start_y = Preview_CROP_START_Y;
    handle->video_res_supported.res[RES_IDX_1280x720_60P].nOutputWidth= 1288;
    handle->video_res_supported.res[RES_IDX_1280x720_60P].nOutputHeight= 724;

    // i2c
    handle->i2c_cfg.mode                = SENSOR_I2C_LEGACY;            //(CUS_ISP_I2C_MODE) FALSE;
    handle->i2c_cfg.fmt                 = SENSOR_I2C_FMT;            //CUS_I2C_FMT_A16D16;
    handle->i2c_cfg.address             = SENSOR_I2C_ADDR;            //0x5a;
    handle->i2c_cfg.speed               = SENSOR_I2C_SPEED;     //200000;
    handle->i2c_cfg.nChannel            = SENSOR_I2C_CHANNEL;   //Channel 1
    handle->i2c_cfg.nPadNum             = SENSOR_I2C_PAD_MODE;  //pad mode 2

    // mclk
    handle->mclk = Preview_MCLK_SPEED;

    //polarity
    /////////////////////////////////////////////////////
    handle->pwdn_POLARITY = SENSOR_PWDN_POL;            //CUS_CLK_POL_NEG;
    handle->reset_POLARITY = SENSOR_RST_POL;            //CUS_CLK_POL_NEG;
    handle->VSYNC_POLARITY = SENSOR_VSYNC_POL;            //CUS_CLK_POL_POS;
    handle->HSYNC_POLARITY = SENSOR_HSYNC_POL;            //CUS_CLK_POL_POS;
    handle->PCLK_POLARITY = SENSOR_PCLK_POL;            //CUS_CLK_POL_POS);    // use '!' to clear board latch error
    /////////////////////////////////////////////////////

    //Mirror / Flip
    params->mirror_flip.new_setting = SENSOR_ORIT;
    params->mirror_flip.cur = SENSOR_ORIT;

    ////////////////////////////////////////////////////
    // AE parameters
    ////////////////////////////////////////////////////
    handle->ae_gain_delay = SENSOR_GAIN_DELAY_FRAME_COUNT;            //0;//1;
    handle->ae_shutter_delay = SENSOR_SHUTTER_DELAY_FRAME_COUNT;            //1;//2;

    ///calibration
    handle->sat_mingain = SENSOR_MIN_GAIN;//g_sensor_ae_min_gain;
    handle->dgain_remainder = 0;

    //LOGD("[%s:%d]\n", __FUNCTION__, __LINE__);
    handle->pCus_sensor_release = ov4689_MIPI_cus_camsensor_release_handle;
    handle->pCus_sensor_init = OV4689_init;
    handle->pCus_sensor_poweron = OV4689_poweron;
    handle->pCus_sensor_poweroff = OV4689_poweroff;

    // Normal
    handle->pCus_sensor_GetSensorID = OV4689_GetSensorID;
    handle->pCus_sensor_GetVideoResNum = OV4689_GetVideoResNum;
    handle->pCus_sensor_GetVideoRes = OV4689_GetVideoRes;
    handle->pCus_sensor_SetVideoRes = OV4689_SetVideoRes;
    handle->pCus_sensor_GetOrien = OV4689_GetOrien;
    handle->pCus_sensor_SetOrien = OV4689_SetOrien;
    handle->pCus_sensor_GetFPS = OV4689_GetFPS;
    handle->pCus_sensor_SetFPS = OV4689_SetFPS;
    handle->pCus_sensor_GetSensorCap = OV4689_GetSensorCap;
    handle->pCus_sensor_SetPatternMode = OV4689_SetPatternMode;
    ///////////////////////////////////////////////////////
    // AE
    ///////////////////////////////////////////////////////
    // unit: micro seconds
    handle->pCus_sensor_AEStatusNotify = OV4689_AEStatusNotify;
    handle->pCus_sensor_GetAEUSecs = OV4689_GetAEUSecs;
    handle->pCus_sensor_SetAEUSecs = OV4689_SetAEUSecs;
    handle->pCus_sensor_GetAEGain = OV4689_GetAEGain;
    handle->pCus_sensor_SetAEGain = DRIVER_SetAEGain;

    handle->pCus_sensor_GetAEMinMaxGain = OV4689_GetAEMinMaxGain;
    handle->pCus_sensor_GetAEMinMaxUSecs = OV4689_GetAEMinMaxUSecs;
    handle->pCus_sensor_GetDGainRemainder = pCus_GetDGainRemainder;
    handle->pCus_sensor_GetShutterInfo = OV4689_GetShutterInfo;

    //sensor calibration
    //handle->pCus_sensor_setCaliData_mingain=OV4689_setCaliData_mingain;
    handle->pCus_sensor_SetAEGain_cal = OV4689_SetAEGain_cal;
    handle->pCus_sensor_setCaliData_gain_linearity = OV4689_setCaliData_gain_linearity;
#if 1//defined(__MV5_FPGA__)
    handle->pCus_sensor_I2CWrite = pCus_I2CWrite; //Andy Liu
    handle->pCus_sensor_I2CRead = pCus_I2CRead; //Andy Liu
#endif
    params->expo.vts = vts_25fps;
    params->expo.fps = 25;
    params->gain = SENSOR_MIN_GAIN;

    handle->snr_pad_group = SENSOR_PAD_GROUP_SET;

    handle->channel_num = SENSOR_CHANNEL_NUM;
    handle->channel_mode = SENSOR_CHANNEL_MODE;


    return SUCCESS;
}
//2ND
int ov4689_MIPI_cus_camsensor_init_handle_2ND( ms_cus_sensor* drv_handle )
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
    //private data allocation & init
#if defined(__RTK_OS__)
    sprintf(str, "OV4689linear");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(ov4689_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (ov4689_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(ov4689_params));
#else
    handle->private_data = calloc( 1, sizeof(ov4689_params) );
#endif
    ov4689_params *params = ( ov4689_params * ) handle->private_data;

    ////////////////////////////////////
    //    sensor model ID                           //
    ////////////////////////////////////
    sprintf( handle->model_id, "OV4689_MIPI" );

    ////////////////////////////////////
    //    sensor interface info       //
    ////////////////////////////////////
    //SENSOR_DMSG("[%s] entering function with id %d\n", __FUNCTION__, id);
    handle->isp_type = SENSOR_ISP_TYPE;            //ISP_SOC;
    //handle->data_fmt    = SENSOR_DATAFMT;   //CUS_DATAFMT_YUV;
    handle->sif_bus = SENSOR_IFBUS_TYPE;            //CUS_SENIF_BUS_PARL;
    handle->data_prec = SENSOR_DATAPREC;            //CUS_DATAPRECISION_8;
    handle->data_mode = SENSOR_DATAMODE;
    handle->bayer_id = SCD_SENSOR_BAYERID;            //CUS_BAYER_GB;
    handle->orient = SENSOR_ORIT;            //CUS_ORIT_M1F1;
    //handle->YC_ODER     = SENSOR_YCORDER;   //CUS_SEN_YCODR_CY;
    handle->interface_attr.attr_mipi.mipi_lane_num = SCD_SENSOR_MIPI_LANE_NUM;
    handle->interface_attr.attr_mipi.mipi_data_format = CUS_SEN_INPUT_FORMAT_RGB; // RGB pattern.
    handle->interface_attr.attr_mipi.mipi_yuv_order = 0; //don't care in RGB pattern.
    handle->interface_attr.attr_mipi.mipi_hsync_mode = SENSOR_MIPI_HSYNC_MODE;
    handle->interface_attr.attr_mipi.mipi_sampling_delay = SENSOR_MIPI_DELAY;
    handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_NONE;
    handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 0;

    ////////////////////////////////////
    //    resolution capability       //
    ////////////////////////////////////
    handle->video_res_supported.num_res = 3;
    handle->video_res_supported.ulcur_res = 0; //default resolution index is 0.
    handle->video_res_supported.res[RES_IDX_2304x1296_60P_HDR].width = 2304;
    handle->video_res_supported.res[RES_IDX_2304x1296_60P_HDR].height = 1296;
    handle->video_res_supported.res[RES_IDX_2304x1296_60P_HDR].max_fps = 30;
    handle->video_res_supported.res[RES_IDX_2304x1296_60P_HDR].min_fps = 30;
    handle->video_res_supported.res[RES_IDX_2304x1296_60P_HDR].crop_start_x = 1;
    handle->video_res_supported.res[RES_IDX_2304x1296_60P_HDR].crop_start_y = 1;
    handle->video_res_supported.res[RES_IDX_2304x1296_60P_HDR].nOutputWidth= 2304;
    handle->video_res_supported.res[RES_IDX_2304x1296_60P_HDR].nOutputHeight= 1296;

    handle->video_res_supported.res[RES_IDX_1920x1080_30P].width = 1920;
    handle->video_res_supported.res[RES_IDX_1920x1080_30P].height = 1080;
    handle->video_res_supported.res[RES_IDX_1920x1080_30P].max_fps = Preview_MAX_FPS;
    handle->video_res_supported.res[RES_IDX_1920x1080_30P].min_fps = Preview_MIN_FPS;
    handle->video_res_supported.res[RES_IDX_1920x1080_30P].crop_start_x = Preview_CROP_START_X;
    handle->video_res_supported.res[RES_IDX_1920x1080_30P].crop_start_y = Preview_CROP_START_Y;
    handle->video_res_supported.res[RES_IDX_1920x1080_30P].nOutputWidth= SCD_Preview_WIDTH;
    handle->video_res_supported.res[RES_IDX_1920x1080_30P].nOutputHeight= SCD_Preview_HEIGHT;

    handle->video_res_supported.res[RES_IDX_1280x720_60P].width = 1280;
    handle->video_res_supported.res[RES_IDX_1280x720_60P].height = 720;
    handle->video_res_supported.res[RES_IDX_1280x720_60P].max_fps = 60;
    handle->video_res_supported.res[RES_IDX_1280x720_60P].min_fps = 60;
    handle->video_res_supported.res[RES_IDX_1280x720_60P].crop_start_x = Preview_CROP_START_X;
    handle->video_res_supported.res[RES_IDX_1280x720_60P].crop_start_y = Preview_CROP_START_Y;
    handle->video_res_supported.res[RES_IDX_1280x720_60P].nOutputWidth= 1288;
    handle->video_res_supported.res[RES_IDX_1280x720_60P].nOutputHeight= 724;

    // i2c
    handle->i2c_cfg.mode                = SENSOR_I2C_LEGACY;            //(CUS_ISP_I2C_MODE) FALSE;
    handle->i2c_cfg.fmt                 = SENSOR_I2C_FMT;            //CUS_I2C_FMT_A16D16;
    handle->i2c_cfg.address             = SENSOR_I2C_ADDR;            //0x5a;
    handle->i2c_cfg.speed               = SENSOR_I2C_SPEED;     //200000;
    handle->i2c_cfg.nChannel            = SENSOR_I2C_CHANNEL;   //Channel 1
    handle->i2c_cfg.nPadNum             = SENSOR_I2C_PAD_MODE;  //pad mode 2

    // mclk
    handle->mclk = Preview_MCLK_SPEED;

    //polarity
    /////////////////////////////////////////////////////
    handle->pwdn_POLARITY = SCD_SENSOR_PWDN_POL;            //CUS_CLK_POL_NEG;
    handle->reset_POLARITY = SENSOR_RST_POL;            //CUS_CLK_POL_NEG;
    handle->VSYNC_POLARITY = SENSOR_VSYNC_POL;            //CUS_CLK_POL_POS;
    handle->HSYNC_POLARITY = SENSOR_HSYNC_POL;            //CUS_CLK_POL_POS;
    handle->PCLK_POLARITY = SENSOR_PCLK_POL;            //CUS_CLK_POL_POS);    // use '!' to clear board latch error
    /////////////////////////////////////////////////////

    //Mirror / Flip
    params->mirror_flip.new_setting = SENSOR_ORIT;
    params->mirror_flip.cur = SENSOR_ORIT;

    ////////////////////////////////////////////////////
    // AE parameters
    ////////////////////////////////////////////////////
    handle->ae_gain_delay = SENSOR_GAIN_DELAY_FRAME_COUNT;            //0;//1;
    handle->ae_shutter_delay = SENSOR_SHUTTER_DELAY_FRAME_COUNT;            //1;//2;

    ///calibration
    handle->sat_mingain = SENSOR_MIN_GAIN;//g_sensor_ae_min_gain;
    handle->dgain_remainder = 0;

    //LOGD("[%s:%d]\n", __FUNCTION__, __LINE__);
    handle->pCus_sensor_release = ov4689_MIPI_cus_camsensor_release_handle;
    handle->pCus_sensor_init = OV4689_init;
    handle->pCus_sensor_poweron = OV4689_poweron;
    handle->pCus_sensor_poweroff = OV4689_poweroff;

    // Normal
    handle->pCus_sensor_GetSensorID = OV4689_GetSensorID;
    handle->pCus_sensor_GetVideoResNum = OV4689_GetVideoResNum;
    handle->pCus_sensor_GetVideoRes = OV4689_GetVideoRes;
    handle->pCus_sensor_SetVideoRes = OV4689_SetVideoRes;
    handle->pCus_sensor_GetOrien = OV4689_GetOrien;
    handle->pCus_sensor_SetOrien = OV4689_SetOrien;
    handle->pCus_sensor_GetFPS = OV4689_GetFPS;
    handle->pCus_sensor_SetFPS = OV4689_SetFPS;
    handle->pCus_sensor_GetSensorCap = OV4689_GetSensorCap;
    handle->pCus_sensor_SetPatternMode = OV4689_SetPatternMode;
    ///////////////////////////////////////////////////////
    // AE
    ///////////////////////////////////////////////////////
    // unit: micro seconds
    handle->pCus_sensor_AEStatusNotify = OV4689_AEStatusNotify;
    handle->pCus_sensor_GetAEUSecs = OV4689_GetAEUSecs;
    handle->pCus_sensor_SetAEUSecs = OV4689_SetAEUSecs;
    handle->pCus_sensor_GetAEGain = OV4689_GetAEGain;
    handle->pCus_sensor_SetAEGain = DRIVER_SetAEGain;

    handle->pCus_sensor_GetAEMinMaxGain = OV4689_GetAEMinMaxGain;
    handle->pCus_sensor_GetAEMinMaxUSecs = OV4689_GetAEMinMaxUSecs;
    handle->pCus_sensor_GetDGainRemainder = pCus_GetDGainRemainder;
    handle->pCus_sensor_GetShutterInfo = OV4689_GetShutterInfo;

    //sensor calibration
    //handle->pCus_sensor_setCaliData_mingain=OV4689_setCaliData_mingain;
    handle->pCus_sensor_SetAEGain_cal = OV4689_SetAEGain_cal;
    handle->pCus_sensor_setCaliData_gain_linearity = OV4689_setCaliData_gain_linearity;
#if 1//defined(__MV5_FPGA__)
    handle->pCus_sensor_I2CWrite = pCus_I2CWrite; //Andy Liu
    handle->pCus_sensor_I2CRead = pCus_I2CRead; //Andy Liu
#endif
    params->expo.vts = vts_25fps;
    params->expo.fps = 25;
    params->gain = SENSOR_MIN_GAIN;

    handle->snr_pad_group = SCD_SENSOR_PAD_GROUP_SET;

    handle->channel_num = SCD_SENSOR_CHANNEL_NUM;
    handle->channel_mode = SCD_SENSOR_CHANNEL_MODE;


    return SUCCESS;
}

int ov4689_MIPI_cus_camsensor_release_handle( ms_cus_sensor *handle )
{
#if defined(__RTK_OS__)
    CamOsRet_e                  eCamOsRet = CAM_OS_OK;
#endif

    SENSOR_DMSG( "[%s]\n", __FUNCTION__ );
    if( handle && handle->private_data )
    {
        SENSOR_IMSG( "[%s] release handle 0x%x, private data %x\n", __FUNCTION__, ( int )handle, ( int )handle->private_data );
#if defined(__RTK_OS__)
        eCamOsRet = CamOsDirectMemRelease((void*)handle->private_data, sizeof(ov4689_params));
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
struct SensorMapTable_t gsensor_map_ov4689 = {
    SENSOR_CHANNEL_NUM,
    ov4689_MIPI_cus_camsensor_init_handle,
    ov4689_MIPI_cus_camsensor_release_handle
};

struct SensorMapTable_t gsensor_map_ov4689_2ND = {
    SCD_SENSOR_CHANNEL_NUM,
    ov4689_MIPI_cus_camsensor_init_handle_2ND,
    ov4689_MIPI_cus_camsensor_release_handle
};

int OV4689_Module_Init(void)
{
#if defined(BIND_SENSOR_OV4689) && (BIND_SENSOR_OV4689 == 1)
    cameraSensorRegister(&gsensor_map_ov4689);
#endif //defined(BIND_SENSOR_OV4689) && (BIND_SENSOR_OV4689 == 1)
#if defined(BIND_SENSOR_OV4689_2ND) && (BIND_SENSOR_OV4689_2ND == 1)
    cameraSensorRegister(&gsensor_map_ov4689_2ND);
#endif //defined(BIND_SENSOR_OV4689_2ND) && (BIND_SENSOR_OV4689_2ND == 1)
    return 0;
}

void OV4689_Module_Exit(void)
{
#if defined(BIND_SENSOR_OV4689) && (BIND_SENSOR_OV4689 == 1)
    cameraSensorUnRegister(&gsensor_map_ov4689);
#endif //defined(BIND_SENSOR_OV4689) && (BIND_SENSOR_OV4689 == 1)
#if defined(BIND_SENSOR_OV4689_2ND) && (BIND_SENSOR_OV4689_2ND == 1)
    cameraSensorUnRegister(&gsensor_map_ov4689_2ND);
#endif //defined(BIND_SENSOR_OV4689_2ND) && (BIND_SENSOR_OV4689_2ND == 1)
}

#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(OV4689_Module_Init);
//ait_module_exit(OV4689_Module_Exit);
#endif //#if defined(__RTK_OS__)

#endif //#if defined(BIND_SENSOR_OV4689) && (BIND_SENSOR_OV4689 == 1)
