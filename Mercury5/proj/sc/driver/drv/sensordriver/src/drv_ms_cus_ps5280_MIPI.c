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
#if (SENSOR0 == PS5280)
#define BIND_SENSOR_PS5280 (1)
#endif
#endif //#if defined(__RTK_OS__)

#if defined(BIND_SENSOR_PS5280) && (BIND_SENSOR_PS5280 == 1)

#define SENSOR_PAD_GROUP_SET CUS_SENSOR_PAD_GROUP_A
#define SENSOR_CHANNEL_NUM (0)
#define SENSOR_CHANNEL_MODE_LINEAR CUS_SENSOR_CHANNEL_MODE_REALTIME_NORMAL
//#define SENSOR_CHANNEL_MODE_2x12B_HDR_DCG CUS_SENSOR_CHANNEL_MODE_RAW_STORE_HDR

//#define SENSOR_CHANNEL_PS5280_ISP_CALIBRATION_ENABLE (0)
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
#define RES_IDX_1920x1080_30P       (0)     // mode 4,  1920*1080 30P       // Video (16:9)
#define RES_IDX_1280x720_60P        (1)     // mode 9,  1280*720  60P       // Video (16:9)

#define SENSOR_MODEL_ID     "ps5280_MIPI"
#define SENSOR_ISP_TYPE     ISP_EXT                   //ISP_EXT, ISP_SOC
#define SENSOR_IFBUS_TYPE   CUS_SENIF_BUS_MIPI      //CFG //CUS_SENIF_BUS_PARL, CUS_SENIF_BUS_MIPI
#define SENSOR_MIPI_HSYNC_MODE PACKET_HEADER_EDGE1
#define SENSOR_MIPI_HSYNC_MODE_HDR PACKET_FOOTER_EDGE
#define SENSOR_MIPI_DELAY   0x1313                  //CFG
#define SENSOR_DATAPREC     CUS_DATAPRECISION_12    //CFG //CUS_DATAPRECISION_8, CUS_DATAPRECISION_10
#define SENSOR_DATAMODE     CUS_SEN_10TO12_9000     //CFG
#define SENSOR_BAYERID      CUS_BAYER_GB            //CFG //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
#define SENSOR_ORIT         CUS_ORIT_M0F0           //CUS_ORIT_M0F0, CUS_ORIT_M1F0, CUS_ORIT_M0F1, CUS_ORIT_M1F1,
#define SENSOR_MAX_GAIN     (64*1024)//65536
#define SENSOR_MIN_GAIN      (1*1024)//1024
#define SENSOR_GAIN_DELAY_FRAME_COUNT      (2)
#define SENSOR_SHUTTER_DELAY_FRAME_COUNT      (2)

#define Preview_MCLK_SPEED  CUS_CMU_CLK_27MHZ        //CFG //CUS_CMU_CLK_12M, CUS_CMU_CLK_16M, CUS_CMU_CLK_24M, CUS_CMU_CLK_27M
#define Preview_line_period 29630                  //
//#define Preview_Pixel_clock 86
#define Prv_Max_line_number 1950                  //maximum exposure line munber of sensor when preview
#define vts_30fps           1125                   //for 30fps
#define Preview_WIDTH       1920                   //resolution Width when preview
#define Preview_HEIGHT      1080                   //resolution Height when preview
#define Preview_MAX_FPS     30                     //fastest preview FPS
#define Preview_MIN_FPS     5                      //slowest preview FPS
#define Preview_CROP_START_X     1                      //CROP_START_X
#define Preview_CROP_START_Y     1                      //CROP_START_Y

#define SENSOR_I2C_ADDR     0x90                    //I2C slave address
#define SENSOR_I2C_SPEED    I2C_SLOWSPEED_MODE_200KHZ   //200KHz
#define SENSOR_I2C_CHANNEL  1                           //I2C Channel
#define SENSOR_I2C_PAD_MODE 2                           //Pad/Mode Number
//#define SENSOR_I2C_SPEED    200000                  //I2C speed, 60000~320000

#define SENSOR_I2C_LEGACY  I2C_NORMAL_MODE     //usally set CUS_I2C_NORMAL_MODE,  if use old OVT I2C protocol=> set CUS_I2C_LEGACY_MODE
#define SENSOR_I2C_FMT     I2C_FMT_A8D8        //CUS_I2C_FMT_A8D8, CUS_I2C_FMT_A8D16, CUS_I2C_FMT_A16D8, CUS_I2C_FMT_A16D16

#define SENSOR_PWDN_POL     CUS_CLK_POL_POS        // if PWDN pin High can makes sensor in power down, set CUS_CLK_POL_POS
#define SENSOR_RST_POL      CUS_CLK_POL_NEG        // if RESET pin High can makes sensor in reset state, set CUS_CLK_POL_NEG

#define SENSOR_VSYNC_POL    CUS_CLK_POL_POS         // if VSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_HSYNC_POL    CUS_CLK_POL_NEG         // if HSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_PCLK_POL     CUS_CLK_POL_POS         // depend on sensor setting, sometimes need to try CUS_CLK_POL_POS or CUS_CLK_POL_NEG
//static int  drv_Fnumber = 22;
//static volatile long long framecount=0;
static int pCus_SetAEGain(ms_cus_sensor *handle, u32 gain);
static int pCus_SetAEUSecs(ms_cus_sensor *handle, u32 us);
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
} ps5280_params;
// set sensor ID address and data

typedef struct {
    float total_gain;
    unsigned short reg_val;
} Gain_ARRAY;


I2C_ARRAY Sensor_id_table[] =
{
{0x00, 0x52},      // {address of ID, ID },
{0x01, 0x80},
};

I2C_ARRAY Sensor_init_table[] =
{
    {0xEF, 0x05},
    {0x0F, 0x00},
    {0x42, 0x00},
    {0x43, 0x02},
    {0xED, 0x01},
    {0xEF, 0x01},
    {0xF5, 0x01},
    {0x09, 0x01},
    {0xEF, 0x00},
    {0x10, 0x80},//Cmd_BYTECLK_InvSel=0 for PS308
    {0x11, 0x80},//GatedAllClk enable
    {0x16, 0xBC},
    {0x36, 0x0E},//180308 7to E
    {0x37, 0x0E},//180308
    {0x38, 0x10},
    {0x63, 0x01},
    {0x64, 0x90},
    {0x67, 0x04},
    {0x68, 0xA0},
    {0x69, 0x10},
    {0x81, 0xC4},
    {0x9E, 0x40},
    {0xA3, 0x04},
    {0xA4, 0x7F},
    {0xBE, 0x05},
    {0xDE, 0x03},
    {0xDF, 0x34},
    {0xE0, 0x10},
    {0xE1, 0x0A},
    {0xE2, 0x09},
    {0xE3, 0x34},
    {0xE4, 0x10},
    {0xE5, 0x0A},
    {0xE6, 0x09},
    {0xED, 0x01},
    {0xEF, 0x01},
    {0x04, 0x10},
    {0x05, 0x0B},
    {0x0A, 0x04},
    {0x0B, 0x64},
    {0x0C, 0x00},
    {0x0D, 0x04},
    {0x0E, 0x0F},
    {0x0F, 0xA0},
    {0x10, 0xA0},
    {0x11, 0x5A}, //4A
    {0x19, 0x40},
    {0x2E, 0xB4},
    {0x32, 0x1E}, //28
    {0x33, 0x62}, //58
    {0x3A, 0x1E}, //28
    {0x3B, 0x6A}, //60
    {0x3E, 0x11},
    {0x3F, 0xC8},
    {0x40, 0x1E}, //28
    {0x42, 0xE8},
    {0x43, 0x62}, //58
    {0x5D, 0x08},
    {0x5E, 0x00},
    {0x5F, 0x32},
    {0x78, 0x40},//180308
    {0x8F, 0x05},
    {0x90, 0x00},
    {0x96, 0x80},
    {0xA4, 0x0A},
    {0xA5, 0x04},
    {0xA6, 0x48},
    {0xA8, 0x00},
    {0xA9, 0x07},
    {0xAA, 0x90},
    {0xAB, 0x01},
    {0xB6, 0x0F},
    {0xB7, 0xA0},
    {0xB8, 0x00},
    {0xB9, 0x01},
    {0xBD, 0x02},
    {0xC9, 0x5C},
    {0xCF, 0xFB},
    {0xD2, 0x22},//A04A: SMD setting from wenhan
    {0xD3, 0x3E},//A04A: SMD setting from wenhan
    {0xD4, 0xA4},
    {0xD6, 0x06},
    {0xD7, 0x0A},
    {0xD8, 0x03},//180308
    {0xDD, 0x32}, //52
    {0xE0, 0x43},
    {0xE2, 0x9A}, //0A
    {0xE4, 0x00},
    {0xF0, 0xFC}, //3C
    {0xF1, 0x16},
    {0xF2, 0x1F},
    {0xF3, 0x0F},
    {0xF5, 0x95},
    {0xF6, 0x05},
    {0xF7, 0x00},
    {0xF8, 0x48},
    {0xFA, 0xB5},
    {0x09, 0x01},
    {0xEF, 0x02},
    {0x33, 0x8A},
    {0x36, 0x00},//180308 BLC
    {0x4F, 0x0A},
    {0x54, 0x00},//180308
    {0xCB, 0x9B},
    {0xD4, 0x00},
    {0xED, 0x01},
    {0x47, 0x10}, // OBC by Peter
    {0x49, 0x10}, // OBC by Peter
    {0x4B, 0x10}, // OBC by Peter
    {0x4D, 0x10}, // OBC by Peter
    {0xEF, 0x05},
    {0x06, 0x05},//RAW12
    {0x09, 0x09},
    {0x0A, 0x05},
    {0x0F, 0x00},//MIPI CSI disable
    {0x10, 0x02},
    {0x11, 0x01},
    {0x15, 0x05},
    {0x17, 0x03},
    {0x18, 0x01},
    {0x3B, 0x01},//R_Cmd_Gated_MIPI_Clk=1
    {0x40, 0x19},
    {0x41, 0x15},
    {0x43, 0x02},//T_MIPI_sel[0], Bank5_67[1]=1
    {0x44, 0x01},//MIPI PLL enable
    {0x4A, 0x02},
    {0x4F, 0x01},
    {0x94, 0x04},
    {0x99, 0x01},
    {0x9A, 0x01},
    {0xB1, 0x00},
    {0xED, 0x01},
    {0xEF, 0x06},
    {0x00, 0x08},
    {0x02, 0x93},
    {0x08, 0x20},
    {0x09, 0xB0},
    {0x0A, 0x78},
    {0x0B, 0xD0},
    {0x0C, 0x60},
    {0x0D, 0x21},
    {0x0E, 0x30},
    {0x0F, 0x00}, //01
    {0x10, 0xFA}, //2C
    {0x11, 0x00}, //01
    {0x12, 0xFA}, //2C
    {0x17, 0x01},
    {0x18, 0x2C}, //90
    {0x19, 0x01},
    {0x1A, 0x2C}, //90
    {0x2B, 0x02},
    {0x2D, 0x04},
    {0x4A, 0x54},
    {0x4B, 0x97},
    {0x98, 0x40},
    {0x99, 0x06},
    {0x9A, 0x60},
    {0x9B, 0x09},
    {0x9C, 0xF0},
    {0x9D, 0x0A},
    {0x9F, 0x19},
    {0xA1, 0x02}, //comp mode turn on
    {0xD7, 0x32},
    {0xD8, 0x02},
    {0xDA, 0x02},
    {0xDC, 0x02},
    {0xDE, 0x02},
    {0xE4, 0x02},
    {0xE6, 0x06},
    {0xE9, 0x10},
    {0xEB, 0x04},
    {0xED, 0x01},
    {0xEF, 0x07},
    {0x01, 0x33},//A04A: SMD setting from wenhan
    {0x02, 0x33},//A04A: SMD setting from wenhan
    {0x03, 0x33},//A04A: SMD setting from wenhan
    {0x04, 0x44},//A04A: SMD setting from wenhan
    {0x05, 0x55},//A04A: SMD setting from wenhan
    {0x06, 0x05},//A04A: SMD setting from wenhan
    {0x10, 0xC9},//A04A: SMD setting from wenhan
    {0x12, 0x85},//A04A: SMD setting from wenhan
    {0x15, 0x10},//A04A: SMD setting from wenhan
    {0x65, 0x0C},//A04A: SMD setting from wenhan
    {0x67, 0x85},//A04A: SMD setting from wenhan
    {0x70, 0x12},//A04A: SMD setting from wenhan
    {0xED, 0x01},
    {0xEF, 0x00},
    {0x11, 0x00},//GatedAllClk disable
    {0xEF, 0x05},
    {0x3B, 0x00},//R_Cmd_Gated_MIPI_Clk=0
    {0xED, 0x01},
    {0xEF, 0x01},
    {0x02, 0xFB},//ResetTG
    {0x09, 0x01},
    {0xEF, 0x05},
    {0x0F, 0x01},//MIPI CSI enable
    {0xED, 0x01},
};

I2C_ARRAY TriggerStartTbl[] = {
//{0x30f4,0x00},//Master mode start
};

I2C_ARRAY Current_Mirror_Flip_Tbl[] = {
{0xEF, 0x01},//M0F0
{0x1b, 0x07},//bit7,Hflip
{0x90, 0x04},//bit[7:4] Cmd_ADC_Latency
{0x1d, 0x04},//bit7,Vflip
};

I2C_ARRAY mirr_flip_table[] =
{
    {0xEF, 0x01},//M0F0
    {0x1b, 0x07},//bit7,Hflip
    {0x90, 0x00},//bit2 Cmd_ADC_Latency
    {0x1d, 0x04},//bit7,Vflip

    {0xEF, 0x01},//M1F0
    {0x1b, 0x87},//bit7,Hflip
    {0x90, 0x04},//bit2 Cmd_ADC_Latency
    {0x1d, 0x04},//bit7,Vflip

    {0xEF, 0x01},//M0F1
    {0x1b, 0x07},//bit7,Hflip
    {0x90, 0x00},//bit2 Cmd_ADC_Latency
    {0x1d, 0x84},//bit7,Vflip

    {0xEF, 0x01},//M1F1
    {0x1b, 0x87},//bit7,Hflip
    {0x90, 0x04},//bit2 Cmd_ADC_Latency
    {0x1d, 0x84},//bit7,Vflip
};

typedef struct {
    short reg;
    char startbit;
    char stopbit;
} COLLECT_REG_SET;

static I2C_ARRAY gain_reg[] = {
    {0xEF, 0x01},
    {0x83, 0x04},//analog gain suggest from 1.25X to 32X
    {0x18, 0x00},
    {0x09, 0x01},
};

static Gain_ARRAY gain_table[]={
    {1024  ,0},
    {1088  ,1},
    {1152  ,2},
    {1216  ,3},
    {1280  ,4},
    {1344  ,5},
    {1408  ,6},
    {1472  ,7},
    {1536  ,8},
    {1600  ,9},
    {1664  ,10},
    {1728  ,11},
    {1792  ,12},
    {1856  ,13},
    {1920  ,14},
    {1982  ,15},
    {2048  ,16},
    {2176  ,17},
    {2304  ,18},
    {2432  ,19},
    {2560  ,20},
    {2688  ,21},
    {2816  ,22},
    {2944  ,23},
    {3072  ,24},
    {3200  ,25},
    {3328  ,26},
    {3456  ,27},
    {3584  ,28},
    {3712  ,29},
    {3840  ,30},
    {3968  ,31},
    {4096  ,32},
    {4352  ,33},
    {4608  ,34},
    {4864  ,35},
    {5120  ,36},
    {5376  ,37},
    {5623  ,38},
    {5888  ,39},
    {6144  ,40},
    {6400  ,41},
    {6656  ,42},
    {6912  ,43},
    {7168  ,44},
    {7424  ,45},
    {7680  ,46},
    {7936  ,47},
    {8192  ,48},
    {8704  ,49},
    {9216  ,50},
    {9728  ,51},
    {10240 ,52},
    {10752 ,53},
    {11264 ,54},
    {11776 ,55},
    {12288 ,56},
    {12800 ,57},
    {13312 ,58},
    {13824 ,59},
    {14336 ,60},
    {14848 ,61},
    {15360 ,62},
    {15872 ,63},
    {16384 ,64},
    {17408 ,65},
    {18432 ,66},
    {19456 ,67},
    {20480 ,68},
    {21504 ,69},
    {22528 ,70},
    {23552 ,71},
    {24576 ,72},
    {25600 ,73},
    {26624 ,74},
    {27648 ,75},
    {28672 ,76},
    {29696 ,77},
    {30720 ,78},
    {31744 ,79},
    {32768 ,80},
    {34816 ,81},
    {36864 ,82},
    {38912 ,83},
    {40960 ,84},
    {43008 ,85},
    {45056 ,86},
    {47104 ,87},
    {49152 ,88},
    {51200 ,89},
    {53248 ,90},
    {55286 ,91},
    {57344 ,92},
    {59392 ,93},
    {61440 ,94},
    {63488 ,95},
    {65536 ,96},
    {69632 ,97},
    {73728 ,98},
    {77824 ,99},
    {81920 ,100},
    {86016 ,101},
    {90112 ,102},
    {94208 ,103},
    {98304 ,104},
    {102400 ,105},
    {106496 ,106},
    {110592 ,107},
    {114688 ,108},
    {118784 ,109},
    {122880 ,110},
    {126976 ,111},
    {131072 ,112},
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

I2C_ARRAY expo_reg[] = {

    {0xEF, 0x01},
    {0x0C, 0x00},
    {0x0D, 0x02},
    {0x0E, 0x0e},
    {0x0F, 0xd8},
    {0x5e, 0x00},
    {0x5f, 0xfa},
    {0x09, 0x01},
};

I2C_ARRAY vts_reg[] = {
    {0xEF, 0x01},
    {0x0A, 0x04},
    {0x0B, 0x64},
    {0x09, 0x01},
};

I2C_ARRAY PatternTbl[] = {
    //pattern mode
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
/*
/////////// function definition ///////////////////
#if SENSOR_DBG == 1
//#define SENSOR_DMSG(args...) LOGD(args)
//#define SENSOR_DMSG(args...) LOGE(args)
#define SENSOR_DMSG(args...) printf(args)
#elif SENSOR_DBG == 0
#define SENSOR_DMSG(args...)
#endif
#undef SENSOR_NAME
#define SENSOR_NAME ps5280
*/
//#define SensorReg_Read(_reg,_data)     (handle->i2c_bus->i2c_rx(handle->i2c_bus,handle->i2c_cfg,_reg,_data))
//#define SensorReg_Write(_reg,_data)    (handle->i2c_bus->i2c_tx(handle->i2c_bus,handle->i2c_cfg,_reg,_data))
//#define SensorRegArrayW(_reg,_len)  (handle->i2c_bus->i2c_array_tx(handle->i2c_bus, handle->i2c_cfg,(_reg),(_len)))
//#define SensorRegArrayR(_reg,_len)  (handle->i2c_bus->i2c_array_rx(handle->i2c_bus, handle->i2c_cfg,(_reg),(_len)))

int ps5280_MIPI_cus_camsensor_release_handle(ms_cus_sensor *handle);

/////////////////// sensor hardware dependent //////////////
static int ISP_config_io(ms_cus_sensor *handle) {
#if 0
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;

    SENSOR_DMSG("[%s]", __FUNCTION__);

    sensor_if->HsyncPol(handle, handle->HSYNC_POLARITY);
    sensor_if->VsyncPol(handle, handle->VSYNC_POLARITY);
    sensor_if->ClkPol(handle, handle->PCLK_POLARITY);
    sensor_if->BayerFmt(handle, handle->bayer_id);
    sensor_if->DataBus(handle, handle->sif_bus);

    sensor_if->DataPrecision(handle, handle->data_prec);
    sensor_if->FmtConv(handle,  handle->data_mode);
#endif
    return SUCCESS;
}

static int pCus_poweron(ms_cus_sensor *handle)
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    SENSOR_DMSG("[%s] ", __FUNCTION__);

    //Sensor power on sequence

    sensor_if->MCLK(SENSOR_PAD_GROUP_SET, 1, handle->mclk);
    sensor_if->SetIOPad(SENSOR_PAD_GROUP_SET, CUS_SENIF_BUS_MIPI, CUS_SR1_MIPI_MODE_1 );
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_216M, handle->PCLK_POLARITY);
    sensor_if->SetCSI_Lane(SENSOR_PAD_GROUP_SET, 2, 1);

    ISP_config_io(handle); //not support
    SENSOR_DMSG("[%s] reset low\n", __FUNCTION__);
    sensor_if->Reset(SENSOR_PAD_GROUP_SET, handle->reset_POLARITY);
    MsSleep(RTK_MS_TO_TICK(5));
    SENSOR_DMSG("[%s] power low\n", __FUNCTION__);
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, handle->pwdn_POLARITY);
    MsSleep(RTK_MS_TO_TICK(5));

    // power -> high, reset -> high
    SENSOR_DMSG("[%s] power high\n", __FUNCTION__);
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET,!handle->pwdn_POLARITY);
    MsSleep(RTK_MS_TO_TICK(5));
    SENSOR_DMSG("[%s] reset high\n", __FUNCTION__);
    sensor_if->Reset(SENSOR_PAD_GROUP_SET, !handle->reset_POLARITY);
    MsSleep(RTK_MS_TO_TICK(5));

    //sensor_if->Set3ATaskOrder(handle, def_order);
    // pure power on
    ISP_config_io(handle);
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET,!handle->pwdn_POLARITY);
    sensor_if->SWReset(handle->channel_num, FALSE);
    //MsSleep(RTK_MS_TO_TICK(50));
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
    int table_length= ARRAY_SIZE(Sensor_id_table);
    I2C_ARRAY id_from_sensor[ARRAY_SIZE(Sensor_id_table)];

    SensorReg_Write(0xef,0x00); //??

    for(n=0;n<table_length;++n)
    {
      id_from_sensor[n].reg = Sensor_id_table[n].reg;
      id_from_sensor[n].data = 0;
    }
    *id =0;
    if(table_length>8) table_length=8; //??

    SENSOR_DMSG("\n\n[%s]", __FUNCTION__);

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

    //convert sensor id to u32 format
    for(i=0;i<table_length;++i)
    {
      if( id_from_sensor[i].data != Sensor_id_table[i].data )
        return FAIL;
      //*id = id_from_sensor[i].data;
      *id = ((*id)+ id_from_sensor[i].data)<<8;
    }

    *id >>= 8;
    SENSOR_DMSG("[%s]ps5280 Read sensor id, get 0x%x Success\n", __FUNCTION__, (int)*id);
    SENSOR_DMSG("[%s]Read sensor id, get 0x%x Success\n", __FUNCTION__, (int)*id);

    return SUCCESS;
}

static int ps5280_SetPatternMode(ms_cus_sensor *handle,u32 mode)
{
    SENSOR_DMSG("\n\n[%s], mode=%d \n", __FUNCTION__, mode);

  return SUCCESS;
}

static int pCus_SetFPS(ms_cus_sensor *handle, u32 fps);
static int pCus_SetAEGain_cal(ms_cus_sensor *handle, u32 gain);
static int pCus_AEStatusNotify(ms_cus_sensor *handle, CUS_CAMSENSOR_AE_STATUS_NOTIFY status);
static int pCus_init(ms_cus_sensor *handle)
{

  SENSOR_DMSG("\n\n[%s]", __FUNCTION__);
  int i,cnt=0;
       short ReadData;
  ISensorIfAPI *sensor_if = &(handle->sensor_if_api);
  sensor_if->PCLK( CUS_SNR_PCLK_MIPI_TOP );

  for(i=0;i< ARRAY_SIZE(Sensor_init_table);i++)
  {
    //UartSendTrace("Write: [%d] 0x%x, 0x%x, \n", i, Sensor_init_table[i].reg, Sensor_init_table[i].data);
    if(Sensor_init_table[i].reg==0xff)
    {
      MsSleep(RTK_MS_TO_TICK(10*Sensor_init_table[i].data)); //(1000*Sensor_init_table[i].data);
                    SENSOR_DMSG("[%s]*Delay %d[ms]\n",__FUNCTION__ ,Sensor_init_table[i].data );
    }
    else
    {
      cnt = 0;
      while(SensorReg_Write(Sensor_init_table[i].reg,Sensor_init_table[i].data) != SUCCESS)
      {
        cnt++;
        printf("Sensor_init_table -> Retry %d...\n",cnt);
        if(cnt>=10)
        {
          printf("[%s:%d]Sensor init fail!!\n", __FUNCTION__, __LINE__);
          return FAIL;
        }
        MsSleep(RTK_MS_TO_TICK(100));//(10*1000);
      }
    }
    #if 0 //Read reg for check
    //SensorReg_Read(,Sensor_init_table[i].data)
    SensorReg_Read(Sensor_init_table[i].reg, &ReadData);
    UartSendTrace("[%s] ps5280SensorReg: %d 0x%x, 0x%x, \n", __FUNCTION__, i, Sensor_init_table[i].reg, ReadData);
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
        case SENSOR_DRIVER_MODE_FULL_HD_30P_RESOLUTION:
            handle->video_res_supported.ulcur_res = RES_IDX_1920x1080_30P;
            handle->pCus_sensor_init = pCus_init;
            break;

        default:
            UartSendTrace("[%s] Line:%d fail. res:%d\n",__FUNCTION__, __LINE__, res);
            break;
    }
        //sensor_if->WaitVEnd( 50 );
        return SUCCESS;
}

static int pCus_GetOrien(ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT *orit) {
    short HFlip,VFlip;

    SensorReg_Write(0xef,0x01);//page 1
    SensorReg_Read(0x1b, &HFlip);
    SensorReg_Read(0x1d, &VFlip);

    if(((HFlip&0x80)==0) &&((VFlip&0x80)==0))
       *orit = CUS_ORIT_M0F0;
    else if(((HFlip&0x80)!=0) &&((VFlip&0x80)==0))
       *orit = CUS_ORIT_M1F0;
    else if(((HFlip&0x80)==0) &&((VFlip&0x80)!=0))
       *orit = CUS_ORIT_M0F1;
    else if(((HFlip&0x80)!=0) &&((VFlip&0x80)!=0))
       *orit = CUS_ORIT_M1F1;

    SENSOR_IMSG("mirror:%x\r\n", HFlip&0x80);
    SENSOR_IMSG("Flip:%x\r\n", VFlip&0x80);

    return SUCCESS;
}

static int pCus_SetOrien(ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT orit) {
    ps5280_params *params = (ps5280_params *)handle->private_data;
    int table_length = ARRAY_SIZE(mirr_flip_table);
    int seg_length=table_length/4;
    //ISensorIfAPI2 *sensor_if1 = handle->sensor_if_api2;
    int i,j;

    SENSOR_DMSG("\n\n[%s]", __FUNCTION__);
    //return SUCCESS;
    //sensor_if1->SetSkipFrame(handle,2); //skip 2 frame to avoid bad frame after mirror/flip

    switch(orit)
    {
        case CUS_ORIT_M0F0:
            for(i=0,j=0;i<seg_length;i++,j++){
                SensorReg_Write(mirr_flip_table[i].reg,mirr_flip_table[i].data);
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }
         //  handle->bayer_id=  CUS_BAYER_BG;
            break;

        case CUS_ORIT_M1F0:
            for(i=seg_length,j=0;i<seg_length*2;i++,j++){
                SensorReg_Write(mirr_flip_table[i].reg,mirr_flip_table[i].data);
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }
    //  handle->bayer_id= CUS_BAYER_BG;
            break;

        case CUS_ORIT_M0F1:
            for(i=seg_length*2,j=0;i<seg_length*3;i++,j++){
                SensorReg_Write(mirr_flip_table[i].reg,mirr_flip_table[i].data);
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }
     // handle->bayer_id= CUS_BAYER_GR;
            break;

        case CUS_ORIT_M1F1:
            for(i=seg_length*3,j=0;i<seg_length*4;i++,j++){
                SensorReg_Write(mirr_flip_table[i].reg,mirr_flip_table[i].data);
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }
     // handle->bayer_id= CUS_BAYER_GR;
            break;

        default :
            for(i=0,j=0;i<seg_length;i++,j++){
                SensorReg_Write(mirr_flip_table[i].reg,mirr_flip_table[i].data);
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }
    //  handle->bayer_id= CUS_BAYER_BG;
            break;
    }
    //SensorReg_Write(0xef,0x01);
    SensorReg_Write(0x09,1);

   // params->orient_dirty = true;
    return SUCCESS;
}

static int pCus_GetFPS(ms_cus_sensor *handle)
{
    ps5280_params *params = (ps5280_params *)handle->private_data;
    SENSOR_DMSG("[%s]", __FUNCTION__);

    return  params->expo.fps;
}
static int pCus_SetFPS(ms_cus_sensor *handle, u32 fps)
{
    ps5280_params *params = (ps5280_params *)handle->private_data;
    SENSOR_DMSG("\n\n[%s]", __FUNCTION__);

    //return SUCCESS;

    if(fps>=5 && fps <= 30){
        params->expo.fps = fps;
        params->expo.vts=  ((vts_30fps*30+(fps>>1))/fps)-1;
        vts_reg[1].data = (params->expo.vts >> 8) & 0x00ff;
        vts_reg[2].data = (params->expo.vts >> 0) & 0x00ff;
      //params->dirty = true;
        return SUCCESS;
    }else if(fps>=5000 && fps <= 30000){
        params->expo.fps = fps;
        params->expo.vts=  ((vts_30fps*30090+(fps>>1))/fps)-1;
        vts_reg[1].data = (params->expo.vts >> 8) & 0x00ff;
        vts_reg[2].data = (params->expo.vts >> 0) & 0x00ff;
        //params->dirty = true;
        return SUCCESS;
    }else{
      //params->expo.vts=vts_25fps;
      //params->expo.fps=25;
      //SENSOR_DMSG("[%s] FPS %d out of range.\n",__FUNCTION__,fps);
      return FAIL;
    }
}

static int pCus_GetSensorCap(ms_cus_sensor *handle, CUS_CAMSENSOR_CAP *cap)
{
  if (cap)
    memcpy(cap, &sensor_cap, sizeof(CUS_CAMSENSOR_CAP));
  else
    return FAIL;
}


///////////////////////////////////////////////////////////////////////
// auto exposure
///////////////////////////////////////////////////////////////////////
// unit: micro seconds
//AE status notification
static int pCus_AEStatusNotify(ms_cus_sensor *handle, CUS_CAMSENSOR_AE_STATUS_NOTIFY status){
    ps5280_params *params = (ps5280_params *)handle->private_data;
    switch(status)
    {
        case CUS_FRAME_INACTIVE:

        break;
        case CUS_FRAME_ACTIVE:
            //printf("[%s] frame %ld\n", __FUNCTION__,framecount);
            if(params->dirty)
            {
                SensorRegArrayW((I2C_ARRAY*)expo_reg, ARRAY_SIZE(expo_reg));
                SensorRegArrayW((I2C_ARRAY*)gain_reg, ARRAY_SIZE(gain_reg));
                SensorRegArrayW((I2C_ARRAY*)vts_reg, ARRAY_SIZE(vts_reg));
                SensorReg_Write(0xef,0x01);
                SensorReg_Write(0x09,1);
                params->dirty = false;
            }

            break;
            default :
            break;
    }
    return SUCCESS;
}

static int pCus_GetAEUSecs(ms_cus_sensor *handle, u32 *us) {
    ps5280_params *params = (ps5280_params *)handle->private_data;
    u32 lines = 0;

    lines |= (u32)(expo_reg[1].data&0xff)<<8;
    lines |= (u32)(expo_reg[2].data&0xff)<<0;

    lines=params->expo.vts-lines;

    *us = lines*Preview_line_period/1000;
    //printf("====================================================\n");
    //printf("[%s] sensor expo lines/us %ld,%ld us\n", __FUNCTION__, lines, *us);
    //printf("====================================================\n");

    SENSOR_DMSG("[%s] sensor expo lines/us %ld,%ld us\n", __FUNCTION__, lines, *us);

    return SUCCESS;
}

static int pCus_SetAEUSecs(ms_cus_sensor *handle, u32 us) {
    u32 sensor_lines = 0, expo_lines = 0, vts = 0, ne =0, ne_patch = 0, g_sns_const = 0;
    u16 const1, const2, const3, const4;
    ps5280_params *params = (ps5280_params *)handle->private_data;

    expo_lines=(1000*us)/Preview_line_period;

    if (expo_lines > params->expo.vts-4) {
        vts = expo_lines +4;
    }
    else
      vts=params->expo.vts;

    //printf("====================================================\n");
    //printf("[%s] us %ld, lines %ld, vts %ld\n", __FUNCTION__,us,lines, params->expo.vts);
    //printf("====================================================\n");
    SENSOR_DMSG("[%s] us %ld, lines %ld, vts %ld\n", __FUNCTION__,
                us,
                expo_lines,
                params->expo.vts
                );

    sensor_lines=vts+1-expo_lines;

    ne_patch=50+((38*sensor_lines)>>8);
    if (ne_patch > 250){
        ne_patch = 250;
    }

    g_sns_const=0xfd2;
    ne = g_sns_const - ne_patch;

    expo_reg[1].data =(u16)( (sensor_lines>>8) & 0x00ff);
    expo_reg[2].data =(u16)( (sensor_lines>>0) & 0x00ff);
    expo_reg[3].data = (u16)((ne >>8) & 0x00ff);
    expo_reg[4].data = (u16)((ne >>0) & 0x00ff);
    expo_reg[5].data = (u16)((ne_patch >>8) & 0x00ff);
    expo_reg[6].data = (u16)((ne_patch >>0) & 0x00ff);

    vts_reg[1].data = (u16)((vts >> 8) & 0x00ff);
    vts_reg[2].data = (u16)((vts >> 0) & 0x00ff);

    //SensorRegArrayW((I2C_ARRAY*)expo_reg, ARRAY_SIZE(expo_reg));
    //SensorRegArrayW((I2C_ARRAY*)gain_reg, ARRAY_SIZE(gain_reg));
    //SensorRegArrayW((I2C_ARRAY*)vts_reg, ARRAY_SIZE(vts_reg));
    params->dirty = true;
    return SUCCESS;
}

// Gain: 1x = 1024
static int pCus_GetAEGain(ms_cus_sensor *handle, u32* gain) {
  ps5280_params *params = (ps5280_params *)handle->private_data;
    u16  temp_gain;
    double  temp_gain_double;

    *gain=params->expo.final_gain;
    SENSOR_DMSG("[%s] set gain/reg=%d/0x%x\n", __FUNCTION__, gain,gain_reg[1].data);
   // printf("set gain/reg=%d/0x%x\n", gain,gain_reg[1].data);

    return SUCCESS;
}


static int pCus_SetAEGain_cal(ms_cus_sensor *handle, u32 gain) {
    ps5280_params *params = (ps5280_params *)handle->private_data;
    u32 i;
    CUS_GAIN_GAP_ARRAY* Sensor_Gain_Linearity;

    params->expo.final_gain = gain;
    if(gain<handle->sat_mingain)
        gain=handle->sat_mingain;
    else if(gain>=SENSOR_MAX_GAIN*1024)
        gain=SENSOR_MAX_GAIN*1024;

    for(i=0;i<112;i++)
    {
        if(gain < gain_table[i].total_gain)    break;
    }
    gain_reg[1].data = (gain_reg[2].data)?i:(i-32);
    SENSOR_DMSG("[%s] set gain/reg=%d/0x%x\n", __FUNCTION__, gain,gain_reg[1].data);
    return SUCCESS;
}

static int pCus_SetAEGain(ms_cus_sensor *handle, u32 gain) {
    ps5280_params *params = (ps5280_params *)handle->private_data;
    u32 i;
    u8 sens_ori,sens,j;
    CUS_GAIN_GAP_ARRAY* Sensor_Gain_Linearity;

    params->expo.final_gain = gain;
    if(gain<handle->sat_mingain)
        gain=handle->sat_mingain;
    else if(gain>=SENSOR_MAX_GAIN*1024)
        gain=SENSOR_MAX_GAIN*1024;

    Sensor_Gain_Linearity = gain_gap_compensate;

    for(i = 0; i < sizeof(gain_gap_compensate)/sizeof(CUS_GAIN_GAP_ARRAY); i++){
        //SENSOR_IMSG("GAP:%x %x\r\n",Sensor_Gain_Linearity[i].gain, Sensor_Gain_Linearity[i].offset);

        if (Sensor_Gain_Linearity[i].gain == 0)
            break;
        if((gain>Sensor_Gain_Linearity[i].gain) && (gain < (Sensor_Gain_Linearity[i].gain + Sensor_Gain_Linearity[i].offset))){
              gain=Sensor_Gain_Linearity[i].gain;
              break;
        }
    }

    SensorReg_Read(gain_reg[2].reg,&gain_reg[2].data);
    sens_ori = gain_reg[2].data;
    //printf("[%s] set total_gain=%d\n", __FUNCTION__,gain);
    //printf("[%s] set1 gain/regH/regL=%d/0x%x/0x%x sens %d frame %ld\n", __FUNCTION__,gain_reg[1].data,gain_reg[2].data,gain_reg[3].data,sens_ori,framecount);
    if(gain < 5*1024){
      sens = 1;     // LS
    }else if(gain > 6*1024){
      sens = 0;     // HS
    }

    for(i = 0;i < 112;i++)
    {
        if(gain < gain_table[i].total_gain)    break;
    }

    gain_reg[1].data = sens ?i:(i-32);
    gain_reg[2].data = sens;
    //SensorRegArrayW((I2C_ARRAY*)gain_reg, ARRAY_SIZE(gain_reg));
    SENSOR_DMSG("[%s] set gain/regH/regL=%d/0x%x/0x%x\n", __FUNCTION__, gain,gain_reg[0].data,gain_reg[1].data);

    params->dirty = true;
    return SUCCESS;
}

static int pCus_GetAEMinMaxUSecs(ms_cus_sensor *handle, u32 *min, u32 *max) {
    *min = 150;
    *max = 33332; // <- max shutter (30fps: 33332, 60fps:16666)
    return SUCCESS;
}

static int pCus_GetAEMinMaxGain(ms_cus_sensor *handle, u32 *min, u32 *max) {
    *min =handle->sat_mingain;
    *max = SENSOR_MAX_GAIN*1024;
    return SUCCESS;
}

static int ps5280_GetShutterInfo(struct __ms_cus_sensor* handle,CUS_SHUTTER_INFO *info)
{
    info->max = 1000000000/Preview_MIN_FPS;
    info->min = Preview_line_period * 1;
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

int ps5280_MIPI_cus_camsensor_init_handle(ms_cus_sensor* drv_handle)
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
    UartSendTrace("\n===== PS5280 init. =====\n");
    #if defined(__RTK_OS__)
    sprintf(str, "PS5280cali");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(ps5280_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (ps5280_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(ps5280_params));
    #else
    handle->private_data = calloc( 1, sizeof(ps5280_params) );
    #endif

    ps5280_params *params = (ps5280_params *)handle->private_data;

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
    handle->video_res_supported.res[0].nOutputWidth= 1936;//Preview_WIDTH;
    handle->video_res_supported.res[0].nOutputHeight= 1096;//Preview_HEIGHT;
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

    handle->pCus_sensor_release     = ps5280_MIPI_cus_camsensor_release_handle;
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
    handle->pCus_sensor_SetPatternMode    = ps5280_SetPatternMode;

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
    handle->pCus_sensor_GetShutterInfo = ps5280_GetShutterInfo;

    handle->snr_pad_group = SENSOR_PAD_GROUP_SET;

    params->expo.vts=vts_30fps;
    params->expo.fps = 30;
    //params->dirty = false;
    //params->orient_dirty = false;
    params->dirty = false;
    //params->reg_dirty_cnt = 0;
    handle->channel_num = SENSOR_CHANNEL_NUM;
    handle->channel_mode = SENSOR_CHANNEL_MODE_LINEAR;
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

static int ps5280_SetPatternMode_isp_calibration( ms_cus_sensor *handle, u32 mode )
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
    ps5280_params *params = ( ps5280_params * ) handle->private_data;
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

static int ps5280_GetShutterInfo_isp_calibration( struct __ms_cus_sensor* handle, CUS_SHUTTER_INFO *info )
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


int ps5280_MIPI_cus_camsensor_init_handle_isp_calibration(ms_cus_sensor* drv_handle)
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
    UartSendTrace("\n===== PS5280 init. =====\n");
    #if defined(__RTK_OS__)
    sprintf(str, "PS5280cali");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(ps5280_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (ps5280_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(ps5280_params));
    #else
    handle->private_data = calloc( 1, sizeof(ps5280_params) );
    #endif

    ps5280_params *params = (ps5280_params *)handle->private_data;

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
    handle->video_res_supported.res[0].nOutputWidth= 1936;//Preview_WIDTH;
    handle->video_res_supported.res[0].nOutputHeight= 1096;//Preview_HEIGHT;
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

    handle->pCus_sensor_release     = ps5280_MIPI_cus_camsensor_release_handle;
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
    handle->pCus_sensor_SetPatternMode    = ps5280_SetPatternMode_isp_calibration;

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
    handle->pCus_sensor_GetShutterInfo = ps5280_GetShutterInfo_isp_calibration;

    params->expo.vts=vts_30fps;
    params->expo.fps = 30;

    handle->snr_pad_group = SENSOR_PAD_GROUP_SET;

    //params->dirty = false;
    //params->orient_dirty = false;
    params->dirty = false;
    //params->reg_dirty_cnt = 0;
    handle->channel_num = SENSOR_CHANNEL_NUM + 1;
    handle->channel_mode = CUS_SENSOR_CHANNEL_MODE_RAW_STORE_ISP_CALIBRATION;
    return SUCCESS;
}

int ps5280_MIPI_cus_camsensor_release_handle(ms_cus_sensor *handle)
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
        eCamOsRet = CamOsDirectMemRelease((void*)handle->private_data, sizeof(ps5280_params));
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
struct SensorMapTable_t gsensor_map_ps5280[] = {
    { //Channel 0
        SENSOR_CHANNEL_NUM,
        ps5280_MIPI_cus_camsensor_init_handle,
        ps5280_MIPI_cus_camsensor_release_handle
    },
#if (SENSOR_CHANNEL_PS5280_ISP_CALIBRATION_ENABLE == 1)
    { //Channel 1. ISP calibration.
        SENSOR_CHANNEL_NUM + 1,
        ps5280_MIPI_cus_camsensor_init_handle_isp_calibration,
        ps5280_MIPI_cus_camsensor_release_handle
    },
#endif
};

int PS5280_Module_Init(void)
{
    cameraSensorRegister(&gsensor_map_ps5280[0]);
#if (SENSOR_CHANNEL_PS5280_ISP_CALIBRATION_ENABLE == 1)
    cameraSensorRegister(&gsensor_map_ps5280[1]);
#endif
    return 0;
}

void PS5280_Module_Exit(void)
{
    cameraSensorUnRegister(&gsensor_map_ps5280[0]);
#if (SENSOR_CHANNEL_PS5280_ISP_CALIBRATION_ENABLE == 1)
    cameraSensorRegister(&gsensor_map_ps5280[1]);
#endif
}

#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(PS5280_Module_Init);
#endif //#if defined(__RTK_OS__)

#endif
