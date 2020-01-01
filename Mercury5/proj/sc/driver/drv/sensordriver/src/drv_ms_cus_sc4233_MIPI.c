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
#if (SENSOR0 == SC4233)
#define BIND_SENSOR_SC4233_MIPI (1)
#endif
#endif //#if defined(__RTK_OS__)

#if defined(BIND_SENSOR_SC4233_MIPI) && (BIND_SENSOR_SC4233_MIPI == 1)

#define SENSOR_PAD_GROUP_SET CUS_SENSOR_PAD_GROUP_A
#define SENSOR_CHANNEL_NUM (0)
#define SENSOR_CHANNEL_MODE_LINEAR CUS_SENSOR_CHANNEL_MODE_REALTIME_NORMAL
//#define SENSOR_CHANNEL_MODE_2x12B_HDR_DCG CUS_SENSOR_CHANNEL_MODE_RAW_STORE_HDR

#define SENSOR_CHANNEL_SC4233_ISP_CALIBRATION_ENABLE (0)
//============================================
//MIPI config begin.
#define SENSOR_MIPI_LANE_NUM (2)
//#define SENSOR_MIPI_HDR_MODE (0) //0: Linear mode. 1:HDR_16b_combined_DCG. 2:HDR_VS_2x12b_DCG_HCG
//MIPI config end.
//============================================

//int usleep(u32 usec); //TBD

///////////////////////////////////////////////////////////////
//          @@@                                                                                       //
//       @   @@      ==  S t a r t * H e r e ==                                            //
//            @@      ==  S t a r t * H e r e  ==                                            //
//            @@      ==  S t a r t * H e r e  ==                                           //
//         @@@@                                                                                  //
//                                                                                                     //
//      Start Step 1 --  show preview on LCM                                         //
//                                                                                                    ï¿½@//
//  Fill these #define value and table with correct settings                        //
//      camera can work and show preview on LCM                                 //
//                                                                                                       //
///////////////////////////////////////////////////////////////
#define RES_IDX_2304x1296_30P       (0)     // mode 4,  1920*1080 30P       // Video (16:9)
//#define RES_IDX_1280x720_60P        (1)     // mode 9,  1280*720  60P       // Video (16:9)

#define SENSOR_MODEL_ID     "SC4233_MIPI"
#define SENSOR_ISP_TYPE     ISP_EXT                   //ISP_EXT, ISP_SOC
#define SENSOR_IFBUS_TYPE   CUS_SENIF_BUS_MIPI      //CFG //CUS_SENIF_BUS_PARL, CUS_SENIF_BUS_MIPI
#define SENSOR_MIPI_HSYNC_MODE PACKET_HEADER_EDGE1
#define SENSOR_MIPI_HSYNC_MODE_HDR PACKET_FOOTER_EDGE
#define SENSOR_MIPI_DELAY   0x1313                  //CFG
#define SENSOR_DATAPREC     CUS_DATAPRECISION_10    //CFG //CUS_DATAPRECISION_8, CUS_DATAPRECISION_10
#define SENSOR_DATAMODE     CUS_SEN_10TO12_9000     //CFG
#define SENSOR_BAYERID      CUS_BAYER_BG            //CFG //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
#define SENSOR_ORIT         CUS_ORIT_M0F0           //CUS_ORIT_M0F0, CUS_ORIT_M1F0, CUS_ORIT_M0F1, CUS_ORIT_M1F1,
#define SENSOR_MAX_GAIN     (64*1024)
#define SENSOR_MIN_GAIN      (1*1024)
#define SENSOR_GAIN_DELAY_FRAME_COUNT      (2)
#define SENSOR_SHUTTER_DELAY_FRAME_COUNT      (2)

#define Preview_MCLK_SPEED      CUS_CMU_CLK_24MHZ        //CFG //CUS_CMU_CLK_12M, CUS_CMU_CLK_16M, CUS_CMU_CLK_24M, CUS_CMU_CLK_27M
#define Preview_line_period     20812//29630                  //
#define Prv_Max_line_number     1296//1536                  //maximum exposure line munber of sensor when preview
#define vts_30fps               1600//1536//1600//1465                   //for 30fps

#define Preview_WIDTH       (2304)                  //resolution Width when preview
#define Preview_HEIGHT      (1296)                   //resolution Height when preview

#define Preview_MAX_FPS     30                     //fastest preview FPS
#define Preview_MIN_FPS     5                      //slowest preview FPS
#define Preview_CROP_START_X    0                 //CROP_START_X
#define Preview_CROP_START_Y    0                  //CROP_START_Y

#define SENSOR_I2C_ADDR         0x60                    //I2C slave address
#define SENSOR_I2C_SPEED        I2C_SLOWSPEED_MODE_200KHZ   //200KHz
#define SENSOR_I2C_CHANNEL      1                           //I2C Channel
#define SENSOR_I2C_PAD_MODE     2                           //Pad/Mode Number
#define SENSOR_I2C_LEGACY       I2C_NORMAL_MODE     //usally set CUS_I2C_NORMAL_MODE,  if use old OVT I2C protocol=> set CUS_I2C_LEGACY_MODE
#define SENSOR_I2C_FMT          I2C_FMT_A16D8        //CUS_I2C_FMT_A8D8, CUS_I2C_FMT_A8D16, CUS_I2C_FMT_A16D8, CUS_I2C_FMT_A16D16

#define SENSOR_PWDN_POL     CUS_CLK_POL_POS        // if PWDN pin High can makes sensor in power down, set CUS_CLK_POL_POS
#define SENSOR_RST_POL      CUS_CLK_POL_NEG        // if RESET pin High can makes sensor in reset state, set CUS_CLK_POL_NEG
#define SENSOR_VSYNC_POL    CUS_CLK_POL_POS         // if VSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_HSYNC_POL    CUS_CLK_POL_POS         // if HSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_PCLK_POL     CUS_CLK_POL_POS         // depend on sensor setting, sometimes need to try CUS_CLK_POL_POS or CUS_CLK_POL_NEG

static int pCus_SetAEGain(ms_cus_sensor *handle, u32 gain);
static int pCus_SetAEUSecs(ms_cus_sensor *handle, u32 us);
static int SC4233_MIPI_cus_camsensor_release_handle(ms_cus_sensor *handle);

CUS_CAMSENSOR_CAP sensor_cap = {
    .length = sizeof(CUS_CAMSENSOR_CAP),
    .version = 0x0001,
};

typedef struct {
    struct {
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
    struct {
        bool bVideoMode;
        u16 res_idx;
        //        bool binning;
        //        bool scaling;
        CUS_CAMSENSOR_ORIT  orit;
    } res;
    struct {
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

    int sen_init;
    int still_min_fps;
    int video_min_fps;
    bool dirty;
    bool orient_dirty;
} SC4233_params;
// set sensor ID address and data

typedef struct {
    float total_gain;
    unsigned short fine_val;
    unsigned short coarse_val;
    float d_gain;
} Gain_ARRAY;


I2C_ARRAY Sensor_id_table[] =
{
    {0x3107, 0x32},    // SC4233
    {0x3108, 0x35},    // SC4233
};

I2C_ARRAY Sensor_init_table[] =
{
    {0x0103,0x01},
    {0x0100,0x00},

    {0x36e9,0xc4},

    //close mipi
    //{0x3018,0x1f},
    //{0x3019,0xff},
    //{0x301c,0xb4},

    //close DVP
    {0x301c,0x78}, // [7]:0  [3]:1 to

    {0x3333,0x00},

    {0x3e01,0xc7},
    {0x3e02,0xe0},
    {0x3640,0x02},
    {0x3641,0x02},

    {0x3908,0x11},

    //row noise
    {0x3e06,0x03},
    {0x3e08,0x1f},
    {0x3e09,0x1f},

    //9.29  mipi
    //mipi
    {0x3018,0x33},//[7:5] lane_num-1
    {0x3031,0x0a},//[3:0] bitmode
    {0x3037,0x20},//[6:5] bitsel
    {0x3001,0xFE},//[0] c_y

    {0x4603,0x00},//[0] data_fifo mipi mode
    {0x4837,0x35},//[7:0] pclk period * 2
    //{0x4827,0x88},//[7:0] hs_prepare_time[7:0]   20180108

    {0x303f,0x01}, //[7] 1: pll_sclk  0: pll_pclk

    {0x5784,0x10}, //1114 0x04
    {0x5788,0x10}, //1114 0x04


    {0x337f,0x03}, //new auto precharge  330e in 3372   [7:6] 11: close div_rst 00:open div_rst
    {0x3368,0x04},
    {0x3369,0x00},
    {0x336a,0x00},
    {0x336b,0x00},
    {0x3367,0x08},
    {0x330e,0x30},

    {0x3320,0x06}, // New ramp offset timing
    //0x3321,0x06,
    {0x3326,0x00},
    {0x331e,0x2f},
    {0x331f,0x2f},
    {0x3308,0x18},
    {0x3303,0x40},
    {0x3309,0x40},

    {0x3306,0x40},

    {0x3301,0x50},
    {0x3638,0x88},

    {0x3307,0x18}, //[3:0]nedd >=7

    {0x3366,0x7c}, // div_rst gap

    //read noise
    {0x3622,0x22},
    {0x3633,0x88},
    {0x3635,0xc2},

    //fwc&Noise FWC4K
    {0x3632,0x18},
    {0x3038,0xcc},
    {0x363c,0x05},
    {0x363d,0x05},
    {0x3637,0x62},
    {0x3638,0x8c},
    {0x330b,0xc8},

    //10.16
    {0x3639,0x09},
    {0x363a,0x1f},

    {0x3638,0x98},
    {0x3306,0x60},

    {0x363b,0x0c},
    //0x3e03,0x03,

    {0x3908,0x15},

    //low power
    {0x3620,0x28},

    //PLL
    {0x36e9,0x24},

    //25fps
    {0x320d,0x8c},

    {0x330b,0xd8},

    //blksun
    {0x3622,0x26},
    {0x3630,0xb8},
    {0x3631,0x88}, //margin 6 levels

    //2304x1440 30fps  585Mbps x 2  dataspeed 117Mpix/s  351M cnt  sys 117M

    {0x36e9,0x46},
    {0x36ea,0x33},
    {0x36f9,0x06},
    {0x36fa,0xca},

    {0x320c,0x0a}, //2600x1500
    {0x320d,0x28},
    {0x320e,0x05},
    {0x320f,0xdc},

    {0x320a,0x05}, //1440
    {0x320b,0xa0},

    {0x3202,0x00},
    {0x3203,0x30},
    {0x3206,0x05}, //1448 rows seleted
    {0x3207,0xd7},

    {0x3e01,0xbb},
    {0x3e02,0x60},
    {0x330b,0xec},


    {0x3636,0x24},
    {0x3637,0x64},
    {0x3638,0x18},
    {0x3625,0x03},

    //1019
    {0x4837,0x20}, //mipi prepare floor(2 x Tmipi_pclk or bitres x 2000/ mipi lane speed bps )

    {0x3333,0x20}, //pix_samp all high
    //{0x331b,0x83}, //snow nosie cancel

    {0x3e06,0x00},
    {0x3e08,0x03},
    {0x3e09,0x10},

    {0x3622,0x06},

    {0x3306,0x50},
    {0x330a,0x01},
    {0x330b,0x10},

    {0x366e,0x08},  // ofs auto en [3]
    {0x366f,0x2f},  // ofs+finegain  real ofs in 0x3687[4:0]



    {0x3235,0x0b}, //group hold position 1115C
    {0x3236,0xb0},

    //for 3.7k
    {0x3637,0x61},
    {0x3306,0x60},
    {0x330b,0x10},


    {0x3633,0x83},
    {0x3301,0x50},

    {0x3630,0xc8},

    {0x330e,0x80}, //for nir


    //pll test
    {0x36e9,0x44},
    {0x36eb,0x0e},
    {0x36ec,0x1e},
    {0x36ed,0x23},

    //sram write
    {0x3f00,0x0f}, //[2]
    {0x3f04,0x05},
    {0x3f05,0x00},

    {0x3962,0x04}, //[0] 1  high temp cal_en

    //1114
    {0x3622,0x16},


    {0x3320,0x06}, // New ramp offset timing
    //0x3321,0x06,
    {0x3326,0x00},
    {0x331e,0x21},
    {0x331f,0x71},
    {0x3308,0x18},
    {0x3303,0x30},
    {0x3309,0x80},


    /////////////////////////////////////high temp/////////////////////////////////////
    //blc max
    {0x3933,0x0a},
    {0x3934,0x08},
    {0x3942,0x02},
    {0x3943,0x0d},
    {0x3940,0x19},
    {0x3941,0x14},
    //blc temp
    {0x3946,0x20}, //kh0
    {0x3947,0x18},//kh1
    {0x3948,0x06}, //kh2
    {0x3949,0x06}, //kh3
    {0x394a,0x18}, //kh4
    {0x394b,0x2c}, //kh5
    {0x394c,0x08},
    {0x394d,0x14},
    {0x394e,0x24},
    {0x394f,0x34},
    {0x3950,0x14},
    {0x3951,0x08},

    {0x3952,0x78}, //kv0 20171211
    {0x3953,0x48}, //kv1
    {0x3954,0x18}, //kv2
    {0x3955,0x18}, //kv3
    {0x3956,0x48}, //kv4
    {0x3957,0x80}, //kv5
    {0x3958,0x10}, //posv0
    {0x3959,0x20}, //posv1
    {0x395a,0x38}, //posv2
    {0x395b,0x38}, //posv3
    {0x395c,0x20}, //posv4
    {0x395d,0x10}, //posv5

    {0x395e,0x24}, // alpha threshold 1115B
    {0x395f,0x00},
    {0x3960,0xc4},
    {0x3961,0xb1},
    {0x3962,0x0d},
    {0x3963,0x44}, //0x80

    //////////////////////////////////////////////////////////////////////////////////////////

    //1115
    {0x3637,0x63}, //add fullwell
    {0x3802,0x01},

    //1123
    {0x3366,0x78}, //row noise optimize

    //1211
    {0x33aa,0x00},//save power

    //20171213
    {0x3208,0x09},//2304
    {0x3209,0x00},
    {0x320a,0x05},//1296
    {0x320b,0x10},

    {0x3200,0x00},//xstar 4
    {0x3201,0x04},
    {0x3202,0x00},//ystar 124
    {0x3203,0x7c},

    //{0x3210,0x00}, // x shift 4
    {0x3211,0x04}, // x shift 4
    //{0x3212,0x00}, // y shift 4
    {0x3213,0x04}, // y shift 4

    {0x3204,0x09},//xend 4+8+2304-1=2315
    {0x3205,0x0b},
    {0x3206,0x05},//yend 124+8+1296-1=1427
    {0x3207,0x93},

    //20171214
    {0x320c,0x09},//hts=2500
    {0x320d,0xc4},
    {0x3f04,0x04},
    {0x3f05,0xbe},  // hts / 2 - 0x24
    {0x320e,0x06}, //vts=1600
    {0x320f,0x40},

    {0x3802,0x01},
    {0x3235,0x0c},
    {0x3236,0x7e}, // vts x 2 - 2
    {0x3e01,0xc7},
    {0x3e01,0x70},

    {0x36e9,0x02}, //24Mimput->120Pclk; x2.5
    {0x36ea,0x36}, // x10
    {0x36eb,0x06}, // /5
    {0x36ec,0x0e}, // /5
    {0x36ed,0x03},

    {0x36f9,0x01}, // CountCLK=3xPclk=360M
    {0x36fa,0x8a}, // x15
    {0x36fb,0x00},

    //20171225
    {0x3222,0x29},
    {0x3901,0x02},

    //20171226  bypass txvdd
    {0x3635,0xe2},
    //20171226B
    {0x3963,0x80},//edges brighting when high temp
    {0x3e1e,0x34},// digital finegain enable


    ////////////20180201  preprecharge
    // prchg max time =(0x3307[7:4]+0x3307[3:0]+0x330e+0x330f+0x3310[7:0])X3 when short exposure
    {0x330f,0x04},
    {0x3310,0x20},//0201B
    {0x3314,0x04},
    {0x330e,0x50},//0201B
    ///////////////////////////

    //20180208
    {0x4827,0x46},// [40ns+4/600M,85ns]
    {0x3650,0x42},


    //20180508
    {0x5000,0x06},	//dpc enable
    {0x5780,0x7f},	//auto dpc
    {0x5781,0x04},	//white	1x
    {0x5782,0x03},	//		4x
    {0x5783,0x02},	//		8x
    {0x5784,0x01},	//		128x
    {0x5785,0x18},	//black	1x
    {0x5786,0x10},	//		4x
    {0x5787,0x08},	//		8x
    {0x5788,0x02},	//		128x
    {0x5789,0x20},	//Gain_thre1=4x
    {0x578a,0x30},	//Gain_thre2=8x

    //20180517	high temperature logic
    {0x3962,0x09},
    {0x3940,0x17},
    {0x3946,0x48},
    {0x3947,0x20},
    {0x3948,0x0A},
    {0x3949,0x10},
    {0x394A,0x28},
    {0x394B,0x48},
    {0x394E,0x28},
    {0x394F,0x50},
    {0x3950,0x20},
    {0x3951,0x10},
    {0x3952,0x70},
    {0x3953,0x40},
    {0x3956,0x40},

    //20180529 20180530
    {0x3940,0x15},
    {0x3934,0x16},
    {0x3943,0x20},
    {0x3952,0x68},
    {0x3953,0x38},
    {0x3956,0x38},
    {0x3957,0x78},
    {0x394F,0x40},

    {0x3301,0x1e},  //[a,21]
    {0x3633,0x23},
    {0x3630,0x80},
    {0x3622,0xf6},

    {0x3802,0x00},//for special area

    {0x0100,0x01},

    //[gain<2]
    {0x3301,0x1e},  //[a,21]
    {0x3633,0x23},
    {0x3630,0x80},
    {0x3622,0xf6},

    //[4>gain>=2]
    {0x3301,0x50},   //20171214[11,66]
    {0x3633,0x23},
    {0x3630,0x80},
    {0x3622,0xf6},

    //[8>gain>=4]
    {0x3301,0x50},  //20171214[18,66]
    {0x3633,0x23},
    {0x3630,0x80},
    {0x3622,0xf6},

    //[15.5>=gain>=8]
    {0x3301,0x50}, //20171214[1e,66]
    {0x3633,0x23},
    {0x3630,0x80},
    {0x3622,0xf6},

    //[gain>15.5]
    {0x3301,0x50}, //20171214[20,66]
    {0x3633,0x44}, //20180418
    {0x3630,0x82},
    {0x3622,0x16},

    //{0x3221,0x66},//mirror&flip
};

I2C_ARRAY mirror_reg[] = {
    {0x3221, 0x00}, // 6 is mirror
};

I2C_ARRAY gain_reg[] = { // 0x3e03=3, gain=(3e08<<8+3e09)/16
    {0x3e06, 0x00},     //[3:0] d-gain
    {0x3e07, 0x10},     //[7:0] finegain 0x80 ~0x8f
    {0x3e08, 0x00 | 0x03},     //[4:2] again_reg
    {0x3e09, 0x10},     //[7:0] finegain 0x10 ~0x1f
};

I2C_ARRAY expo_reg[] = {  // max expo line vts-4!
    {0x3e00, 0x00},//expo [20:17]
    {0x3e01, 0x30}, // expo[15:8]
    {0x3e02, 0x00}, // expo[7:0], [3:0] fraction of line
};

I2C_ARRAY vts_reg[] = {
    {0x320e, 0x06},
    {0x320f, 0xcc},
};

I2C_ARRAY nr2_reg[] = {
{0x3314,0x04},
{0x330e,0x50},
};
static int g_sensor_ae_min_gain = 1024;
static CUS_GAIN_GAP_ARRAY gain_gap_compensate[16] = {  //compensate  gain gap
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

#if ENABLE_NR
I2C_ARRAY nr_reg[] = {
{0x3301,0x1e},  //[a,21]
{0x3633,0x23},
{0x3630,0x80},
{0x3622,0xf6},

};
#endif

#if ENABLE_DPC
I2C_ARRAY DPC_reg[] = {
    {0x5781,0x04},
    {0x5785,0x18},
};
#endif

I2C_ARRAY PatternTbl[] = {
    {0x5040,0x00}, //colorbar pattern , bit 7 to enable
};

CUS_INT_TASK_ORDER def_order = {
        .RunLength = 9,
        .Orders = {
                CUS_INT_TASK_AE|CUS_INT_TASK_VDOS|CUS_INT_TASK_AF,
                CUS_INT_TASK_AWB|CUS_INT_TASK_VDOS|CUS_INT_TASK_AF,
                CUS_INT_TASK_VDOS|CUS_INT_TASK_AF,
                CUS_INT_TASK_AE|CUS_INT_TASK_VDOS|CUS_INT_TASK_AF,
                CUS_INT_TASK_AWB|CUS_INT_TASK_VDOS|CUS_INT_TASK_AF,
                CUS_INT_TASK_VDOS|CUS_INT_TASK_AF,
                CUS_INT_TASK_AE|CUS_INT_TASK_VDOS|CUS_INT_TASK_AF,
                CUS_INT_TASK_AWB|CUS_INT_TASK_VDOS|CUS_INT_TASK_AF,
                CUS_INT_TASK_VDOS|CUS_INT_TASK_AF,
        },
};

static int pCus_poweron(ms_cus_sensor *handle)
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    SENSOR_DMSG("[%s] ", __FUNCTION__);

    //Sensor power on sequence
    sensor_if->MCLK(SENSOR_PAD_GROUP_SET, 1, handle->mclk);
    sensor_if->SetIOPad(SENSOR_PAD_GROUP_SET, CUS_SENIF_BUS_MIPI, CUS_SR1_MIPI_MODE_1 );
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_216M, handle->PCLK_POLARITY);
    sensor_if->SetCSI_Lane(SENSOR_PAD_GROUP_SET, 2, 1);

    SENSOR_DMSG("[%s] reset low\n", __FUNCTION__);
    sensor_if->Reset(SENSOR_PAD_GROUP_SET, handle->reset_POLARITY);
    MsSleep(RTK_MS_TO_TICK(50));
    SENSOR_DMSG("[%s] power low\n", __FUNCTION__);
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, handle->pwdn_POLARITY);
    MsSleep(RTK_MS_TO_TICK(50));

    // power -> high, reset -> high
    SENSOR_DMSG("[%s] power high\n", __FUNCTION__);
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET,!handle->pwdn_POLARITY);
    MsSleep(RTK_MS_TO_TICK(50));
    SENSOR_DMSG("[%s] reset high\n", __FUNCTION__);
    sensor_if->Reset(SENSOR_PAD_GROUP_SET, !handle->reset_POLARITY);
    MsSleep(RTK_MS_TO_TICK(50));

    //sensor_if->Set3ATaskOrder(handle, def_order);
    // pure power on
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET,!handle->pwdn_POLARITY);
    sensor_if->SWReset(handle->channel_num, FALSE);

    MsSleep(RTK_MS_TO_TICK(50));
    //handle->i2c_bus->i2c_open(handle->i2c_bus,&handle->i2c_cfg);
    return SUCCESS;

}

static int pCus_poweroff(ms_cus_sensor *handle)
{
    // power/reset low
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    //sensor_if->MIPISamplingDelay(handle, false, handle->mipi_sampling_delay);
    SENSOR_DMSG("[%s] power low\n", __FUNCTION__);
    sensor_if->SWReset(handle->channel_num, TRUE);
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, handle->pwdn_POLARITY);
    //handle->i2c_bus->i2c_close(handle->i2c_bus);
    MsSleep(RTK_MS_TO_TICK(10));
    //Set_csi_if(0, 0);
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_DISABLE, handle->PCLK_POLARITY);
    sensor_if->MCLK(SENSOR_PAD_GROUP_SET , 0, handle->mclk);
    return SUCCESS;
}

/////////////////// image function /////////////////////////
//Get and check sensor ID
//if i2c error or sensor id does not match then return FAIL
static int pCus_GetSensorID(ms_cus_sensor *handle, u32 *id)
{
    int i,n;
    u16 sen_data1;
    int table_length= ARRAY_SIZE(Sensor_id_table);
    I2C_ARRAY id_from_sensor[ARRAY_SIZE(Sensor_id_table)];

    //SENSOR_DMSG("\n\n[%s]", __FUNCTION__);
    for(n=0;n<table_length;++n) {
      id_from_sensor[n].reg = Sensor_id_table[n].reg;
      id_from_sensor[n].data = 0;
    }
    *id =0;

    for(n=0;n<4;++n) //retry , until I2C success
    {
      if(n>2) return FAIL;

      if( SensorRegArrayR((I2C_ARRAY*)id_from_sensor,table_length) == SUCCESS) //read sensor ID from I2C
      {
        break;
      }
      else
        continue;
    }

    if( id_from_sensor[0].data != Sensor_id_table[0].data ) {
        SENSOR_DMSG("[%s]Read sensor id: 0x%x fail.\n", __FUNCTION__, id_from_sensor[0].data);
        return FAIL;
    }
    *id = id_from_sensor[i].data;

    return SUCCESS;
}

static int SC4233_SetPatternMode(ms_cus_sensor *handle,u32 mode)
{
    return SUCCESS;
}

static int pCus_SetFPS(ms_cus_sensor *handle, u32 fps);
static int pCus_SetAEGain_cal(ms_cus_sensor *handle, u32 gain);
static int pCus_AEStatusNotify(ms_cus_sensor *handle, CUS_CAMSENSOR_AE_STATUS_NOTIFY status);

static int pCus_init(ms_cus_sensor *handle)
{
    int i,cnt=0;
    short ReadData;
    ISensorIfAPI *sensor_if = &(handle->sensor_if_api);
    sensor_if->PCLK( CUS_SNR_PCLK_MIPI_TOP );

    for(i=0;i< ARRAY_SIZE(Sensor_init_table);i++)
    {
        if(Sensor_init_table[i].reg == SENSOR_DELAY_REG)
        {
            MsSleep(RTK_MS_TO_TICK(Sensor_init_table[i].data)); //(1000*Sensor_init_table[i].data);
            SENSOR_DMSG("[%s]*Delay %d[ms]\n",__FUNCTION__ ,Sensor_init_table[i].data );
        }
        else
        {
            cnt = 0;
            while(SensorReg_Write(Sensor_init_table[i].reg,Sensor_init_table[i].data) != SUCCESS)
            {
                cnt++;
                SENSOR_EMSG("Sensor_init_table -> Retry %d...\n",cnt);
                if(cnt>=10)
                {
                    SENSOR_EMSG("[%s:%d]Sensor init fail!!\n", __FUNCTION__, __LINE__);
                    return FAIL;
                }
                MsSleep(RTK_MS_TO_TICK(100));//(10*1000);
            }
        }
        #if 0 //Read reg for check
        //SensorReg_Read(,Sensor_init_table[i].data)
        SensorReg_Read(Sensor_init_table[i].reg, &ReadData);
        UartSendTrace("[%s] SC4233SensorReg: %d 0x%x, 0x%x, \n", __FUNCTION__, i, Sensor_init_table[i].reg, ReadData);
        #endif
    }

    for(i=0;i< ARRAY_SIZE(PatternTbl);i++)
    {
        if(SensorReg_Write(PatternTbl[i].reg,PatternTbl[i].data) != SUCCESS)
        {
            //MSG("[%s:%d]Sensor init fail!!\n", __FUNCTION__, __LINE__);
            return FAIL;
        }
    }

    pCus_SetAEGain(handle,1024); //Set sensor gain = 1x
    pCus_SetAEUSecs(handle, 30000);
    pCus_AEStatusNotify(handle,CUS_FRAME_ACTIVE);
    return SUCCESS;
}

static int pCus_GetVideoRes(ms_cus_sensor *handle, cus_camsensor_res **res)
{
    //return current resolution
    *res = &handle->video_res_supported.res[0];
    return SUCCESS;
}

static int pCus_SetVideoRes(ms_cus_sensor *handle, u32 res)
{
    switch(res)
    {
        case SENSOR_DRIVER_MODE_SUPER_HD_30P_RESOLUTION:
        case SENSOR_DRIVER_MODE_FULL_HD_30P_RESOLUTION:
            handle->video_res_supported.ulcur_res = RES_IDX_2304x1296_30P;
            handle->pCus_sensor_init = pCus_init;
            break;

        default:
            UartSendTrace("[%s] Line:%d fail. res:%d\n",__FUNCTION__, __LINE__, res);
            break;
    }

    return SUCCESS;
}

static int pCus_GetOrien(ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT *orit)
{
    *orit = (CUS_CAMSENSOR_ORIT)mirror_reg[0].data;
    return SUCCESS;
}

static int pCus_SetOrien(ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT orit)
{
  short index=0,readdata=0;
  SC4233_params *params = (SC4233_params *)handle->private_data;

  switch(orit) {
        case CUS_ORIT_M0F0:
      index = 0;
            break;
        case CUS_ORIT_M1F0:
      index = 0x06;
            break;
        case CUS_ORIT_M0F1:
      index = 0x60;
            break;
        case CUS_ORIT_M1F1:
      index = 0x66;
            break;
            }
  SENSOR_DMSG("pCus_SetOrien:%x\r\n", index);
  if (index != mirror_reg[0].data) {
    mirror_reg[0].data = index;
    params->orient_dirty = true;
  }

    //SensorReg_Write( mirror_reg[0].reg, mirror_reg[0].data );
    //SensorReg_Read( mirror_reg[0].reg, &readdata );
    //printc("pCus_SetOrien, read out%x\r\n");
    return SUCCESS;
}

static int pCus_GetFPS(ms_cus_sensor *handle)
{
    SC4233_params *params = (SC4233_params *)handle->private_data;
    SENSOR_DMSG("[%s]", __FUNCTION__);

    return  params->expo.fps;
}
static int pCus_SetFPS(ms_cus_sensor *handle, u32 fps)
{
    SC4233_params *params = (SC4233_params *)handle->private_data;

  SENSOR_DMSG("\n\n[%s], fps=%d\n", __FUNCTION__, fps);
    if(fps>=5 && fps <= 30){
        params->expo.fps = fps;
    params->expo.vts=  (vts_30fps*30)/fps;
        vts_reg[0].data = (params->expo.vts >> 8) & 0x00ff;
        vts_reg[1].data = (params->expo.vts >> 0) & 0x00ff;
        params->dirty = true;
        return SUCCESS;
    }else if(fps>=5000 && fps <= 30000){
        params->expo.fps = fps;
    params->expo.vts=  (vts_30fps*30000)/fps;
        vts_reg[0].data = (params->expo.vts >> 8) & 0x00ff;
        vts_reg[1].data = (params->expo.vts >> 0) & 0x00ff;
        params->dirty = true;
        return SUCCESS;
    }else{
    SENSOR_DMSG("[%s] FPS %d out of range.\n",__FUNCTION__,fps);
      return FAIL;
    }
    return SUCCESS;
}

static int pCus_GetSensorCap(ms_cus_sensor *handle, CUS_CAMSENSOR_CAP *cap)
{
  if (cap)
    memcpy(cap, &sensor_cap, sizeof(CUS_CAMSENSOR_CAP));
  else
    return FAIL;
  return SUCCESS;
}

///////////////////////////////////////////////////////////////////////
// auto exposure
///////////////////////////////////////////////////////////////////////
// unit: micro seconds
//AE status notification
static int pCus_AEStatusNotify(ms_cus_sensor *handle, CUS_CAMSENSOR_AE_STATUS_NOTIFY status)
{
    SC4233_params *params = (SC4233_params *)handle->private_data;
    switch(status)
    {
        case CUS_FRAME_INACTIVE:

        break;
        case CUS_FRAME_ACTIVE:
            if(params->dirty)
            {
                SensorRegArrayW((I2C_ARRAY*)expo_reg, ARRAY_SIZE(expo_reg));
                SensorRegArrayW((I2C_ARRAY*)gain_reg, ARRAY_SIZE(gain_reg));
                SensorRegArrayW((I2C_ARRAY*)vts_reg, ARRAY_SIZE(vts_reg));
                params->dirty = false;
            }

            break;
            default :
            break;
    }
    return SUCCESS;
}

static int pCus_GetAEUSecs(ms_cus_sensor *handle, u32 *us) {
  int rc=0;
  u32 lines = 0;
  lines |= (u32)(expo_reg[0].data&0x0f)<<16;
  lines |= (u32)(expo_reg[1].data&0xff)<<8;
  lines |= (u32)(expo_reg[2].data&0xf0)<<0;
  lines >>= 4;
  *us = (lines*Preview_line_period)/1000/2; //return us

  SENSOR_DMSG("[%s] sensor expo lines/us %d, %dus\n", __FUNCTION__, lines, *us);
  return rc;
}

static int pCus_SetAEUSecs(ms_cus_sensor *handle, u32 us) {
    int i;
    u32 half_lines = 0,vts = 0;
    SC4233_params *params = (SC4233_params *)handle->private_data;
    I2C_ARRAY expo_reg_temp[] = {  // max expo line vts-4!
    {0x3e00, 0x00},//expo [20:17]
    {0x3e01, 0x00}, // expo[16:8]
    {0x3e02, 0x00}, // expo[7:0], [3:0] fraction of line
    };
    memcpy(expo_reg_temp, expo_reg, sizeof(expo_reg));

    half_lines = (1000*us*2)/Preview_line_period; // Preview_line_period in ns
    if(half_lines<3) half_lines=3;
    if (half_lines >  2 * (params->expo.vts)-4) {
        half_lines = 2 * (params->expo.vts)-4;
    }
    else
        vts=params->expo.vts;

    half_lines = half_lines<<4;

    SENSOR_DMSG("[%s] us %ld, lines %ld, vts %ld\n", __FUNCTION__, us, lines, params->expo.vts);
    //printf("us %ld, lines %ld, vts %ld\n", us, lines, params->expo.vts);
    expo_reg[0].data = (half_lines>>16) & 0x0f;
    expo_reg[1].data =  (half_lines>>8) & 0xff;
    expo_reg[2].data = (half_lines>>0) & 0xf0;

    if (((half_lines >>8) & 0x0fff) < 5)
    {
        nr2_reg[0].data = 0x14;
		nr2_reg[1].data = 0x40;
    }else if (((half_lines >>8) & 0x0fff) > 0xa)
    {
        nr2_reg[0].data = 0x04;
		nr2_reg[1].data = 0x50;
    }
    params->dirty = true;    //reg need to update
    return SUCCESS;
}

// Gain: 1x = 1024
static int pCus_GetAEGain(ms_cus_sensor *handle, u32* gain) {
    int rc = 0;
    float temp_gain;
    u8 i=0 ,Dgain = 1,  Coarse_gain = 1; float Fine_again = 1.0f,Fine_dgain = 1.0f;
    SC4233_params *params = (SC4233_params *)handle->private_data;
    Fine_again = (float) gain_reg[3].data/16;
    Fine_dgain = (float) gain_reg[1].data/128;
    Coarse_gain = ((gain_reg[2].data&0x1C)>>2) +1;
    Dgain = ((gain_reg[0].data&0x0f) + 1);

    temp_gain = Fine_again * 1024;
    *gain = (temp_gain * Coarse_gain * Dgain * Fine_dgain);

    SENSOR_DMSG("[%s] gain/reg = %d, 0x%x,  0x%x  0x%x\n", __FUNCTION__, *gain,gain_reg[0].data,gain_reg[1].data,gain_reg[2].data);
    SENSOR_DMSG("[%s] gain/reg = %d, %f ,%d, %d %f %f\n", __FUNCTION__, *gain,temp_gain,Coarse_gain,Dgain,Fine_again,Fine_dgain);
  return rc;
}

static int pCus_SetAEGain(ms_cus_sensor *handle, u32 gain) {
    SC4233_params *params = (SC4233_params *)handle->private_data;
    u8 i=0 ,Dgain = 1,  Coarse_gain = 1; float Fine_again = 1.0f,Fine_dgain = 1.0f;
    u8 Dgain_reg = 0, Coarse_gain_reg = 0, Fine_again_reg= 0x10,Fine_dgain_reg= 0x80;

    I2C_ARRAY gain_reg_temp[] = {
        {0x3e06, 0x00},
        {0x3e07, 0x00},
        {0x3e08, (0x00|0x03)},
        {0x3e09, 0x10},
    };
    memcpy(gain_reg_temp, gain_reg, sizeof(gain_reg));

    if (gain < 1024) {
        gain = 1024;
    } else if (gain > SENSOR_MAX_GAIN*1024) {
        gain = SENSOR_MAX_GAIN*1024;
    }

#if ENABLE_NR
    if (gain < 2*1024) {
        nr_reg[0].data = 0x1e;
        nr_reg[1].data = 0x23;
        nr_reg[2].data = 0x80;
        nr_reg[3].data = 0xf6;
    } else if (gain < 4*1024) {
        nr_reg[0].data = 0x50;
        nr_reg[1].data = 0x23;
        nr_reg[2].data = 0x80;
        nr_reg[3].data = 0xf6;
    } else if (gain <= 15.5*1024) {
        nr_reg[0].data = 0x50;
        nr_reg[1].data = 0x23;
        nr_reg[2].data = 0x80;
        nr_reg[3].data = 0xf6;
    } else {
        nr_reg[0].data = 0x80;
        nr_reg[1].data = 0x53;
        nr_reg[2].data = 0x82;
        nr_reg[3].data = 0x16;
    }
#endif

#if ENABLE_DPC
    if (gain < 10*1024) {
        DPC_reg[0].data = 0x04;
        DPC_reg[1].data = 0x18;
    } else {
        DPC_reg[0].data = 0x02;
        DPC_reg[1].data = 0x08;
    }
#endif

    if (gain < 2 * 1024)
    {
        Dgain = 1;      Fine_dgain = 1;         Coarse_gain = 1;
        Dgain_reg = 0;  Fine_dgain_reg = 0x80;  Coarse_gain_reg = 0;
    }
    else if (gain <  4 * 1024)
    {
        Dgain = 1;      Fine_dgain = 1;         Coarse_gain = 2;
        Dgain_reg = 0;  Fine_dgain_reg = 0x80;  Coarse_gain_reg = 1;
    }
    else if (gain <  8 * 1024)
    {
        Dgain = 1;      Fine_dgain = 1;         Coarse_gain = 4;
        Dgain_reg = 0;  Fine_dgain_reg = 0x80;  Coarse_gain_reg = 3;
    }
    else if (gain <=  15.5 * 1024)
    {
        Dgain = 1;      Fine_dgain = 1;         Coarse_gain = 8;
        Dgain_reg = 0;  Fine_dgain_reg = 0x80;  Coarse_gain_reg = 7;
    }
    else if (gain <  31 * 1024)
    {
        Dgain = 1;      Fine_again = 1.9375;    Coarse_gain = 8;
        Dgain_reg = 0;  Fine_again_reg = 0x1f;  Coarse_gain_reg = 7;
    }
    else if (gain <  62 * 1024)
    {
        Dgain = 2;      Fine_again = 1.9375;    Coarse_gain = 8;
        Dgain_reg = 1;  Fine_again_reg = 0x1f;  Coarse_gain_reg = 7;
    }
     else if (gain < 128 * 1024)
    {
        Dgain = 4;      Fine_again = 1.9375;    Coarse_gain = 8;
        Dgain_reg = 3;  Fine_again_reg = 0x1f;  Coarse_gain_reg = 7;
    }
        else if (gain < SENSOR_MAX_GAIN * 1024)
    {
        Dgain = 8;      Fine_again = 1.9375;    Coarse_gain = 8;
        Dgain_reg = 7;  Fine_again_reg = 0x1f;  Coarse_gain_reg = 7;
    }

    if (gain <= 15.5 * 1024)
    {
        Fine_again =(float)gain / (Dgain * Coarse_gain * Fine_dgain)/ 1024;
        Fine_again_reg = abs((Fine_again - 1) * 16) + 16;
    }
    else
    {
        Fine_dgain =(float)gain / (Dgain * Coarse_gain * Fine_again)/ 1024;
        Fine_dgain_reg = abs((Fine_dgain - 1) * 128) + 128;
    }

    //SENSOR_DMSG("[%s]  gain : %f ,%f ,%d , %d\n\n", __FUNCTION__,Fine_again,Fine_dgain,Dgain,Coarse_gain);

    gain_reg[3].data = Fine_again_reg;
    gain_reg[2].data = (Coarse_gain_reg<<2)&0x1C | 0x03;
    gain_reg[1].data = Fine_dgain_reg;
    gain_reg[0].data = Dgain_reg & 0xF;

    for (i = 0; i < sizeof(gain_reg)/sizeof(I2C_ARRAY); i++)
    {
      if (gain_reg[i].data != gain_reg_temp[i].data)
      {
        params->dirty = true;
        break;
      }
    }

    return SUCCESS;
}

static int pCus_SetAEGain_cal(ms_cus_sensor *handle, u32 gain)
{
    u8 i=0 ,Dgain = 1,  Coarse_gain = 1; float Fine_again = 1.0f,Fine_dgain = 1.0f;
    u8 Dgain_reg = 0, Coarse_gain_reg = 0, Fine_again_reg= 0x10,Fine_dgain_reg= 0x80;
  SC4233_params *params = (SC4233_params *)handle->private_data;

    I2C_ARRAY gain_reg_temp[] = {
        {0x3e06, 0x00},
        {0x3e07, 0x00},
        {0x3e08, (0x00|0x03)},
        {0x3e09, 0x10},
    };
    memcpy(gain_reg_temp, gain_reg, sizeof(gain_reg));

    if (gain < 1024) {
        gain = 1024;
    } else if (gain > SENSOR_MAX_GAIN*1024) {
        gain = SENSOR_MAX_GAIN*1024;
    }

#if ENABLE_NR
    if (gain < 2*1024) {
        nr_reg[0].data = 0x1e;
        nr_reg[1].data = 0x23;
        nr_reg[2].data = 0x80;
        nr_reg[3].data = 0xf6;
    } else if (gain < 4*1024) {
        nr_reg[0].data = 0x50;
        nr_reg[1].data = 0x23;
        nr_reg[2].data = 0x80;
        nr_reg[3].data = 0xf6;
    } else if (gain <= 15.5*1024) {
        nr_reg[0].data = 0x50;
        nr_reg[1].data = 0x23;
        nr_reg[2].data = 0x80;
        nr_reg[3].data = 0xf6;
    } else {
        nr_reg[0].data = 0x80;
        nr_reg[1].data = 0x53;
        nr_reg[2].data = 0x82;
        nr_reg[3].data = 0x16;
    }
#endif

#if ENABLE_DPC
    if (gain < 10*1024) {
        DPC_reg[0].data = 0x04;
        DPC_reg[1].data = 0x18;
    } else {
        DPC_reg[0].data = 0x02;
        DPC_reg[1].data = 0x08;
    }
#endif

    if (gain < 2 * 1024)
    {
        Dgain = 1;      Fine_dgain = 1;         Coarse_gain = 1;
        Dgain_reg = 0;  Fine_dgain_reg = 0x80;  Coarse_gain_reg = 0;
    }
    else if (gain <  4 * 1024)
    {
        Dgain = 1;      Fine_dgain = 1;         Coarse_gain = 2;
        Dgain_reg = 0;  Fine_dgain_reg = 0x80;  Coarse_gain_reg = 1;
    }
    else if (gain <  8 * 1024)
    {
        Dgain = 1;      Fine_dgain = 1;         Coarse_gain = 4;
        Dgain_reg = 0;  Fine_dgain_reg = 0x80;  Coarse_gain_reg = 3;
    }
    else if (gain <=  15.5 * 1024)
    {
        Dgain = 1;      Fine_dgain = 1;         Coarse_gain = 8;
        Dgain_reg = 0;  Fine_dgain_reg = 0x80;  Coarse_gain_reg = 7;
    }
    else if (gain <  31 * 1024)
    {
        Dgain = 1;      Fine_again = 1.9375;    Coarse_gain = 8;
        Dgain_reg = 0;  Fine_again_reg = 0x1f;  Coarse_gain_reg = 7;
    }
    else if (gain <  62 * 1024)
    {
        Dgain = 2;      Fine_again = 1.9375;    Coarse_gain = 8;
        Dgain_reg = 1;  Fine_again_reg = 0x1f;  Coarse_gain_reg = 7;
    }
     else if (gain < 128 * 1024)
    {
        Dgain = 4;      Fine_again = 1.9375;    Coarse_gain = 8;
        Dgain_reg = 3;  Fine_again_reg = 0x1f;  Coarse_gain_reg = 7;
    }
        else if (gain < SENSOR_MAX_GAIN * 1024)
    {
        Dgain = 8;      Fine_again = 1.9375;    Coarse_gain = 8;
        Dgain_reg = 7;  Fine_again_reg = 0x1f;  Coarse_gain_reg = 7;
    }

    if (gain <= 15.5 * 1024)
    {
        Fine_again =(float)gain / (Dgain * Coarse_gain * Fine_dgain)/ 1024;
        Fine_again_reg = abs((Fine_again - 1) * 16) + 16;
    }
    else
    {
        Fine_dgain =(float)gain / (Dgain * Coarse_gain * Fine_again)/ 1024;
        Fine_dgain_reg = abs((Fine_dgain - 1) * 128) + 128;
    }

    //SENSOR_DMSG("[%s]  gain : %f ,%f ,%d , %d\n\n", __FUNCTION__,Fine_again,Fine_dgain,Dgain,Coarse_gain);

    gain_reg[3].data = Fine_again_reg;
    gain_reg[2].data = (Coarse_gain_reg<<2)&0x1C | 0x03;
    gain_reg[1].data = Fine_dgain_reg;
    gain_reg[0].data = Dgain_reg & 0xF;

    for (i = 0; i < sizeof(gain_reg)/sizeof(I2C_ARRAY); i++)
    {
      if (gain_reg[i].data != gain_reg_temp[i].data)
      {
        params->dirty = true;
        break;
      }
    }

    return SUCCESS;
}

static int pCus_GetAEMinMaxUSecs(ms_cus_sensor *handle, u32 *min, u32 *max) {
  *min = 30;
  *max = 1000000/Preview_MIN_FPS;

    return SUCCESS;
}

static int pCus_GetAEMinMaxGain(ms_cus_sensor *handle, u32 *min, u32 *max) {
    *min =handle->sat_mingain;
    *max = SENSOR_MAX_GAIN*1024;
    return SUCCESS;
}

static int SC4233_GetShutterInfo(struct __ms_cus_sensor* handle,CUS_SHUTTER_INFO *info)
{
    info->max = 1000000000/Preview_MIN_FPS;
    info->min = Preview_line_period * 3;
    info->step = Preview_line_period;
    return SUCCESS;
}

static int pCus_setCaliData_gain_linearity(ms_cus_sensor* handle, CUS_GAIN_GAP_ARRAY* pArray, u32 num) {
    u32 i, j;

    for(i=0,j=0;i< num ;i++,j+=2){
        gain_gap_compensate[i].gain=pArray[i].gain;
        gain_gap_compensate[i].offset=pArray[i].offset;
    }

    SENSOR_IMSG("[%s]%d, %d, %d, %d\n", __FUNCTION__, num, pArray[0].gain, pArray[1].gain, pArray[num-1].offset);
    return SUCCESS;
}

static int pCus_GetVideoResNum( ms_cus_sensor *handle, u32 *ulres_num)
{
    *ulres_num = handle->video_res_supported.num_res;
    return SUCCESS;
}

static int pCus_GetDGainRemainder(ms_cus_sensor *handle, u32 *dgain_remainder)
{
    *dgain_remainder = handle->dgain_remainder;

    return SUCCESS;
}

int SC4233_MIPI_cus_camsensor_init_handle(ms_cus_sensor* drv_handle)
{
    ms_cus_sensor *handle = drv_handle;
    #if defined(__RTK_OS__)
    CamOsRet_e                  eCamOsRet = CAM_OS_OK;
    void*                       pvBufVirt = NULL;
    u64                 u64BufPhy = 0;
    u64                 u64BufMiu = 0;
    u8                   str[20];
    #endif
    if (!handle) {
        SENSOR_DMSG("[%s] not enough memory!\n", __FUNCTION__);
        return FAIL;
    }
    SENSOR_DMSG("[%s]", __FUNCTION__);
    UartSendTrace("\n===== SC4233 init. =====\n");
    #if defined(__RTK_OS__)
    sprintf(str, "SC4233cali");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(SC4233_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (SC4233_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(SC4233_params));
    #else
    handle->private_data = calloc( 1, sizeof(SC4233_params) );
    #endif

    SC4233_params *params = (SC4233_params *)handle->private_data;

    ////////////////////////////////////
    //    sensor model ID                           //
    ////////////////////////////////////
    sprintf(handle->model_id,SENSOR_MODEL_ID);

    ////////////////////////////////////
    //    sensor interface info       //
    ////////////////////////////////////
    //SENSOR_DMSG("[%s] entering function with id %d\n", __FUNCTION__, id);
    handle->isp_type    = SENSOR_ISP_TYPE;  //ISP_SOC;
    handle->sif_bus     = SENSOR_IFBUS_TYPE;//CUS_SENIF_BUS_PARL;
    handle->data_prec   = SENSOR_DATAPREC;  //CUS_DATAPRECISION_8;
    handle->data_mode   = SENSOR_DATAMODE;
    handle->bayer_id    = SENSOR_BAYERID;   //CUS_BAYER_GB;
    handle->orient      = SENSOR_ORIT;      //CUS_ORIT_M1F1;
    handle->interface_attr.attr_mipi.mipi_lane_num = SENSOR_MIPI_LANE_NUM;
    handle->interface_attr.attr_mipi.mipi_data_format = CUS_SEN_INPUT_FORMAT_RGB; // RGB pattern.
    handle->interface_attr.attr_mipi.mipi_yuv_order = 0; //don't care in RGB pattern.
    handle->interface_attr.attr_mipi.mipi_hsync_mode = SENSOR_MIPI_HSYNC_MODE;
    handle->interface_attr.attr_mipi.mipi_sampling_delay = SENSOR_MIPI_DELAY;
    handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_NONE;
    handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 1; //Long frame
        //handle->mipi_sampling_delay = SENSOR_MIPI_DELAY;

    ////////////////////////////////////
    //    resolution capability       //
    ////////////////////////////////////

    handle->video_res_supported.num_res = 1;
    handle->video_res_supported.ulcur_res = 0; //default resolution index is 0.
    handle->video_res_supported.res[0].width = Preview_WIDTH;
    handle->video_res_supported.res[0].height = Preview_HEIGHT;
    handle->video_res_supported.res[0].max_fps= Preview_MAX_FPS;
    handle->video_res_supported.res[0].min_fps= Preview_MIN_FPS;
    handle->video_res_supported.res[0].crop_start_x= Preview_CROP_START_X;
    handle->video_res_supported.res[0].crop_start_y= Preview_CROP_START_Y;
    handle->video_res_supported.res[0].nOutputWidth= Preview_WIDTH;
    handle->video_res_supported.res[0].nOutputHeight= Preview_HEIGHT;
    // i2c
    handle->i2c_cfg.mode                = SENSOR_I2C_LEGACY;    //(CUS_ISP_I2C_MODE) FALSE;
    handle->i2c_cfg.fmt                 = SENSOR_I2C_FMT;       //CUS_I2C_FMT_A16D16;
    handle->i2c_cfg.address             = SENSOR_I2C_ADDR;      //0x5a;
    handle->i2c_cfg.speed               = SENSOR_I2C_SPEED;     //320000;
    handle->i2c_cfg.nChannel            = SENSOR_I2C_CHANNEL;   //Channel 1
    handle->i2c_cfg.nPadNum             = SENSOR_I2C_PAD_MODE;  //pad mode 2

    // mclk
    handle->mclk                        = Preview_MCLK_SPEED;

    //polarity
    /////////////////////////////////////////////////////
    handle->pwdn_POLARITY               = SENSOR_PWDN_POL;  //CUS_CLK_POL_NEG;
    handle->reset_POLARITY              = SENSOR_RST_POL;   //CUS_CLK_POL_NEG;
    handle->VSYNC_POLARITY              = SENSOR_VSYNC_POL; //CUS_CLK_POL_POS;
    handle->HSYNC_POLARITY              = SENSOR_HSYNC_POL; //CUS_CLK_POL_POS;
    handle->PCLK_POLARITY               = SENSOR_PCLK_POL;  //CUS_CLK_POL_POS);    // use '!' to clear board latch error
    //
    handle->ae_gain_delay = SENSOR_GAIN_DELAY_FRAME_COUNT;            //0;//1;
    handle->ae_shutter_delay = SENSOR_SHUTTER_DELAY_FRAME_COUNT;            //1;//2;

    handle->sat_mingain = SENSOR_MIN_GAIN;
    handle->dgain_remainder = 0;

    handle->pCus_sensor_release     = SC4233_MIPI_cus_camsensor_release_handle;
    handle->pCus_sensor_init        = pCus_init;
    handle->pCus_sensor_poweron     = pCus_poweron;
    handle->pCus_sensor_poweroff    = pCus_poweroff;

    handle->pCus_sensor_GetSensorID       = pCus_GetSensorID;
    handle->pCus_sensor_GetVideoResNum    = pCus_GetVideoResNum;
    handle->pCus_sensor_GetVideoRes       = pCus_GetVideoRes;
    handle->pCus_sensor_SetVideoRes       = pCus_SetVideoRes;
    handle->pCus_sensor_GetOrien          = pCus_GetOrien;
    handle->pCus_sensor_SetOrien          = pCus_SetOrien;
    handle->pCus_sensor_GetFPS            = pCus_GetFPS;
    handle->pCus_sensor_SetFPS            = pCus_SetFPS;
    handle->pCus_sensor_GetSensorCap      = pCus_GetSensorCap;
    handle->pCus_sensor_SetPatternMode    = SC4233_SetPatternMode;

    handle->pCus_sensor_AEStatusNotify = pCus_AEStatusNotify;
    handle->pCus_sensor_GetAEUSecs      = pCus_GetAEUSecs;
    handle->pCus_sensor_SetAEUSecs      = pCus_SetAEUSecs;
    handle->pCus_sensor_GetAEGain       = pCus_GetAEGain;
    handle->pCus_sensor_SetAEGain       = pCus_SetAEGain;
    handle->pCus_sensor_SetAEGain_cal       = pCus_SetAEGain_cal;

    handle->pCus_sensor_GetAEMinMaxGain = pCus_GetAEMinMaxGain;
    handle->pCus_sensor_GetAEMinMaxUSecs= pCus_GetAEMinMaxUSecs;
    handle->pCus_sensor_GetDGainRemainder = pCus_GetDGainRemainder;

    handle->pCus_sensor_setCaliData_gain_linearity=pCus_setCaliData_gain_linearity;
    handle->pCus_sensor_GetShutterInfo = SC4233_GetShutterInfo;

    params->expo.vts=vts_30fps;
    params->expo.fps = 30;

    handle->snr_pad_group = SENSOR_PAD_GROUP_SET;

    //params->orient_dirty = false;
    params->dirty = false;
    //params->reg_dirty_cnt = 0;
    handle->channel_num = SENSOR_CHANNEL_NUM;
    handle->channel_mode = SENSOR_CHANNEL_MODE_LINEAR;

    //pCus_SetOrien(handle,handle->orient);
    return SUCCESS;
}

static int pCus_poweron_isp_calibration( ms_cus_sensor *handle )
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    SENSOR_DMSG( "[%s] ", __FUNCTION__ );

    return SUCCESS;
}

static int pCus_poweroff_isp_calibration( ms_cus_sensor *handle )
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    SENSOR_DMSG( "[%s] power low\n", __FUNCTION__ );

    return SUCCESS;
}

static int pCus_GetSensorID_isp_calibration( ms_cus_sensor *handle, u32 *id )
{
    *id = 0;
     return SUCCESS;
}

static int SC4233_SetPatternMode_isp_calibration( ms_cus_sensor *handle, u32 mode )
{
    return SUCCESS;
}

static int pCus_init_isp_calibration( ms_cus_sensor *handle )
{
    return SUCCESS;
}

static int pCus_GetVideoRes_isp_calibration( ms_cus_sensor *handle, cus_camsensor_res **res )
{
    *res = &handle->video_res_supported.res[handle->video_res_supported.ulcur_res];
    return SUCCESS;
}

static int pCus_SetVideoRes_isp_calibration( ms_cus_sensor *handle, u32 res )
{
    handle->video_res_supported.ulcur_res = 0; //TBD
    return SUCCESS;
}

static int pCus_GetOrien_isp_calibration( ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT *orit )
{
    SC4233_params *params = ( SC4233_params * ) handle->private_data;
    return SUCCESS;
}

static int pCus_SetOrien_isp_calibration( ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT orit )
{
    return SUCCESS;
}

static int pCus_GetFPS_isp_calibration( ms_cus_sensor *handle )
{
    return SUCCESS;
}

static int pCus_SetFPS_isp_calibration( ms_cus_sensor *handle, u32 fps )
{
    return SUCCESS;
}

static int pCus_GetSensorCap_isp_calibration( ms_cus_sensor *handle, CUS_CAMSENSOR_CAP *cap )
{
    if( cap )
        memcpy( cap, &sensor_cap, sizeof(CUS_CAMSENSOR_CAP) );
    else
        return FAIL;
    return SUCCESS;
}

static int pCus_AEStatusNotify_isp_calibration( ms_cus_sensor *handle, CUS_CAMSENSOR_AE_STATUS_NOTIFY status )
{
    return SUCCESS;
}

static int pCus_GetAEUSecs_isp_calibration( ms_cus_sensor *handle, u32 *us )
{
    *us = 0;
    return SUCCESS;
}

static int pCus_SetAEUSecs_isp_calibration( ms_cus_sensor *handle, u32 us )
{
    return SUCCESS;
}

// Gain: 1x = 1024
static int pCus_GetAEGain_isp_calibration( ms_cus_sensor *handle, u32* gain )
{
    *gain = 0;
    return SUCCESS;
}

static int pCus_SetAEGain_cal_isp_calibration( ms_cus_sensor *handle, u32 gain )
{
    return SUCCESS;
}
static int pCus_SetAEGain_isp_calibration( ms_cus_sensor *handle, u32 gain )
{
    return SUCCESS;
}

static int pCus_GetAEMinMaxUSecs_isp_calibration( ms_cus_sensor *handle, u32 *min, u32 *max )
{
    *min = 1;
    *max = 1000000 / 30;

    return SUCCESS;
}

static int pCus_GetAEMinMaxGain_isp_calibration( ms_cus_sensor *handle, u32 *min, u32 *max )
{
    *min = SENSOR_MIN_GAIN;            //1024*1.1*2
    *max = SENSOR_MAX_GAIN;

    return SUCCESS;
}

static int pCus_setCaliData_gain_linearity_isp_calibration( ms_cus_sensor* handle, CUS_GAIN_GAP_ARRAY* pArray, u32 num )
{
    return SUCCESS;
}

static int SC4233_GetShutterInfo_isp_calibration( struct __ms_cus_sensor* handle, CUS_SHUTTER_INFO *info )
{
    info->max = 1000000000 / 12;
    info->min = Preview_line_period;
    info->step = Preview_line_period;
    return SUCCESS;
}

static int pCus_GetDGainRemainder_isp_calibration(ms_cus_sensor *handle, u32 *dgain_remainder)
{
    *dgain_remainder = 0;

    return SUCCESS;
}


int SC4233_MIPI_cus_camsensor_init_handle_isp_calibration(ms_cus_sensor* drv_handle)
{
    ms_cus_sensor *handle = drv_handle;
    #if defined(__RTK_OS__)
    CamOsRet_e                  eCamOsRet = CAM_OS_OK;
    void*                       pvBufVirt = NULL;
    u64                 u64BufPhy = 0;
    u64                 u64BufMiu = 0;
    u8                   str[20];
    #endif
    if (!handle) {
        SENSOR_DMSG("[%s] not enough memory!\n", __FUNCTION__);
        return FAIL;
    }
    SENSOR_DMSG("[%s]", __FUNCTION__);
    UartSendTrace("\n===== SC4233 init. =====\n");
    #if defined(__RTK_OS__)
    sprintf(str, "SC4233cali");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(SC4233_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (SC4233_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(SC4233_params));
    #else
    handle->private_data = calloc( 1, sizeof(SC4233_params) );
    #endif

    SC4233_params *params = (SC4233_params *)handle->private_data;

    ////////////////////////////////////
    //    sensor model ID                           //
    ////////////////////////////////////
    sprintf(handle->model_id,SENSOR_MODEL_ID);

    ////////////////////////////////////
    //    sensor interface info       //
    ////////////////////////////////////
    //SENSOR_DMSG("[%s] entering function with id %d\n", __FUNCTION__, id);
    handle->isp_type    = SENSOR_ISP_TYPE;  //ISP_SOC;
    handle->sif_bus     = SENSOR_IFBUS_TYPE;//CUS_SENIF_BUS_PARL;
    handle->data_prec   = SENSOR_DATAPREC;  //CUS_DATAPRECISION_8;
    handle->data_mode   = SENSOR_DATAMODE;
    handle->bayer_id    = SENSOR_BAYERID;   //CUS_BAYER_GB;
    handle->orient      = SENSOR_ORIT;      //CUS_ORIT_M1F1;
    handle->interface_attr.attr_mipi.mipi_lane_num = SENSOR_MIPI_LANE_NUM;
    handle->interface_attr.attr_mipi.mipi_data_format = CUS_SEN_INPUT_FORMAT_RGB; // RGB pattern.
    handle->interface_attr.attr_mipi.mipi_yuv_order = 0; //don't care in RGB pattern.
    handle->interface_attr.attr_mipi.mipi_hsync_mode = SENSOR_MIPI_HSYNC_MODE;
    handle->interface_attr.attr_mipi.mipi_sampling_delay = SENSOR_MIPI_DELAY;
    handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_NONE;
    handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 1; //Long frame
        //handle->mipi_sampling_delay = SENSOR_MIPI_DELAY;

    ////////////////////////////////////
    //    resolution capability       //
    ////////////////////////////////////

    handle->video_res_supported.num_res = 1;
    handle->video_res_supported.ulcur_res = 0; //default resolution index is 0.
    handle->video_res_supported.res[0].width = Preview_WIDTH;
    handle->video_res_supported.res[0].height = Preview_HEIGHT;
    handle->video_res_supported.res[0].max_fps= Preview_MAX_FPS;
    handle->video_res_supported.res[0].min_fps= Preview_MIN_FPS;
    handle->video_res_supported.res[0].crop_start_x= Preview_CROP_START_X;
    handle->video_res_supported.res[0].crop_start_y= Preview_CROP_START_Y;
    handle->video_res_supported.res[0].nOutputWidth= Preview_WIDTH;
    handle->video_res_supported.res[0].nOutputHeight= Preview_HEIGHT;
    // i2c
    handle->i2c_cfg.mode                = SENSOR_I2C_LEGACY;    //(CUS_ISP_I2C_MODE) FALSE;
    handle->i2c_cfg.fmt                 = SENSOR_I2C_FMT;       //CUS_I2C_FMT_A16D16;
    handle->i2c_cfg.address             = SENSOR_I2C_ADDR;      //0x5a;
    handle->i2c_cfg.speed               = SENSOR_I2C_SPEED;     //320000;
    handle->i2c_cfg.nChannel            = SENSOR_I2C_CHANNEL;   //Channel 1
    handle->i2c_cfg.nPadNum             = SENSOR_I2C_PAD_MODE;  //pad mode 2

    // mclk
    handle->mclk                        = Preview_MCLK_SPEED;

    //polarity
    /////////////////////////////////////////////////////
    handle->pwdn_POLARITY               = SENSOR_PWDN_POL;  //CUS_CLK_POL_NEG;
    handle->reset_POLARITY              = SENSOR_RST_POL;   //CUS_CLK_POL_NEG;
    handle->VSYNC_POLARITY              = SENSOR_VSYNC_POL; //CUS_CLK_POL_POS;
    handle->HSYNC_POLARITY              = SENSOR_HSYNC_POL; //CUS_CLK_POL_POS;
    handle->PCLK_POLARITY               = SENSOR_PCLK_POL;  //CUS_CLK_POL_POS);    // use '!' to clear board latch error
    //
    handle->ae_gain_delay = SENSOR_GAIN_DELAY_FRAME_COUNT;            //0;//1;
    handle->ae_shutter_delay = SENSOR_SHUTTER_DELAY_FRAME_COUNT;            //1;//2;

    handle->sat_mingain = SENSOR_MIN_GAIN;
    handle->dgain_remainder = 0;

    handle->pCus_sensor_release     = SC4233_MIPI_cus_camsensor_release_handle;
    handle->pCus_sensor_init        = pCus_init_isp_calibration;
    handle->pCus_sensor_poweron     = pCus_poweron_isp_calibration;
    handle->pCus_sensor_poweroff    = pCus_poweroff_isp_calibration;

    handle->pCus_sensor_GetSensorID       = pCus_GetSensorID_isp_calibration;
    handle->pCus_sensor_GetVideoResNum    = pCus_GetVideoResNum;
    handle->pCus_sensor_GetVideoRes       = pCus_GetVideoRes_isp_calibration;
    handle->pCus_sensor_SetVideoRes       = pCus_SetVideoRes_isp_calibration;
    handle->pCus_sensor_GetOrien          = pCus_GetOrien_isp_calibration;
    handle->pCus_sensor_SetOrien          = pCus_SetOrien_isp_calibration;
    handle->pCus_sensor_GetFPS            = pCus_GetFPS_isp_calibration;
    handle->pCus_sensor_SetFPS            = pCus_SetFPS_isp_calibration;
    handle->pCus_sensor_GetSensorCap      = pCus_GetSensorCap_isp_calibration;
    handle->pCus_sensor_SetPatternMode    = SC4233_SetPatternMode_isp_calibration;

    handle->pCus_sensor_AEStatusNotify = pCus_AEStatusNotify_isp_calibration;
    handle->pCus_sensor_GetAEUSecs      = pCus_GetAEUSecs_isp_calibration;
    handle->pCus_sensor_SetAEUSecs      = pCus_SetAEUSecs_isp_calibration;
    handle->pCus_sensor_GetAEGain       = pCus_GetAEGain_isp_calibration;
    handle->pCus_sensor_SetAEGain       = pCus_SetAEGain_isp_calibration;
    handle->pCus_sensor_SetAEGain_cal       = pCus_SetAEGain_cal_isp_calibration;

    handle->pCus_sensor_GetAEMinMaxGain = pCus_GetAEMinMaxGain_isp_calibration;
    handle->pCus_sensor_GetAEMinMaxUSecs= pCus_GetAEMinMaxUSecs_isp_calibration;
    handle->pCus_sensor_GetDGainRemainder = pCus_GetDGainRemainder_isp_calibration;

    handle->pCus_sensor_setCaliData_gain_linearity=pCus_setCaliData_gain_linearity_isp_calibration;
    handle->pCus_sensor_GetShutterInfo = SC4233_GetShutterInfo_isp_calibration;

    params->expo.vts=vts_30fps;
    params->expo.fps = 30;
    handle->snr_pad_group = SENSOR_PAD_GROUP_SET;

    params->dirty = false;
    handle->channel_num = SENSOR_CHANNEL_NUM + 1;
    handle->channel_mode = CUS_SENSOR_CHANNEL_MODE_RAW_STORE_ISP_CALIBRATION;
    return SUCCESS;
}

int SC4233_MIPI_cus_camsensor_release_handle(ms_cus_sensor *handle)
{
    #if defined(__RTK_OS__)
    CamOsRet_e                  eCamOsRet = CAM_OS_OK;
    #endif
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;

    //sensor_if->PCLK(CUS_PCLK_OFF);
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_DISABLE, handle->PCLK_POLARITY);
    if (handle && handle->private_data)
    {
        SENSOR_IMSG("[%s] release handle, handle %x, private data %x",
            __FUNCTION__,
            (int)handle,
            (int)handle->private_data);
        #if defined(__RTK_OS__)
        eCamOsRet = CamOsDirectMemRelease((void*)handle->private_data, sizeof(SC4233_params));
        if (eCamOsRet != CAM_OS_OK)
        {
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
struct SensorMapTable_t gsensor_map_SC4233[] = {
    { //Channel 0
        SENSOR_CHANNEL_NUM,
        SC4233_MIPI_cus_camsensor_init_handle,
        SC4233_MIPI_cus_camsensor_release_handle
    },
#if (SENSOR_CHANNEL_SC4233_ISP_CALIBRATION_ENABLE == 1)
    { //Channel 1. ISP calibration.
        SENSOR_CHANNEL_NUM + 1,
        SC4233_MIPI_cus_camsensor_init_handle_isp_calibration,
        SC4233_MIPI_cus_camsensor_release_handle
    },
#endif
};

int SC4233_Module_Init(void)
{
    cameraSensorRegister(&gsensor_map_SC4233[0]);
#if (SENSOR_CHANNEL_SC4233_ISP_CALIBRATION_ENABLE == 1)
    cameraSensorRegister(&gsensor_map_SC4233[1]);
#endif
    return 0;
}

void SC4233_Module_Exit(void)
{
    cameraSensorUnRegister(&gsensor_map_SC4233[0]);
#if (SENSOR_CHANNEL_SC4233_ISP_CALIBRATION_ENABLE == 1)
    cameraSensorRegister(&gsensor_map_SC4233[1]);
#endif
}

#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(SC4233_Module_Init);
#endif //#if defined(__RTK_OS__)

#endif
