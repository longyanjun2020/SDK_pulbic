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
#if (SENSOR0 == AR0330)
#define BIND_SENSOR_AR0330_MIPI (1)
#endif
#endif //#if defined(__RTK_OS__)

#if defined(BIND_SENSOR_AR0330_MIPI) && (BIND_SENSOR_AR0330_MIPI == 1)

#define SENSOR_PAD_GROUP_SET CUS_SENSOR_PAD_GROUP_A
#define SENSOR_CHANNEL_NUM (0)
#define SENSOR_CHANNEL_MODE_LINEAR CUS_SENSOR_CHANNEL_MODE_REALTIME_NORMAL
//#define SENSOR_CHANNEL_MODE_2x12B_HDR_DCG CUS_SENSOR_CHANNEL_MODE_RAW_STORE_HDR

#define SENSOR_CHANNEL_AR0330_ISP_CALIBRATION_ENABLE (0)
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

#define SENSOR_MODEL_ID     "ar0330_MIPI"
#define SENSOR_ISP_TYPE     ISP_EXT                   //ISP_EXT, ISP_SOC
#define SENSOR_IFBUS_TYPE   CUS_SENIF_BUS_MIPI      //CFG //CUS_SENIF_BUS_PARL, CUS_SENIF_BUS_MIPI
#define SENSOR_MIPI_HSYNC_MODE PACKET_FOOTER_EDGE
#define SENSOR_MIPI_HSYNC_MODE_HDR PACKET_FOOTER_EDGE
#define SENSOR_MIPI_DELAY   0x1313                  //CFG
#define SENSOR_DATAPREC     CUS_DATAPRECISION_10    //CFG //CUS_DATAPRECISION_8, CUS_DATAPRECISION_10
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
#define vts_30fps           1465                   //for 30fps
#define Preview_WIDTH       2304                  //resolution Width when preview
#define Preview_HEIGHT      1296                   //resolution Height when preview
#define Preview_MAX_FPS     30                     //fastest preview FPS
#define Preview_MIN_FPS     5                      //slowest preview FPS
#define Preview_CROP_START_X     1                      //CROP_START_X
#define Preview_CROP_START_Y     1                      //CROP_START_Y

#define SENSOR_I2C_ADDR     0x20                    //I2C slave address
#define SENSOR_I2C_SPEED    I2C_SLOWSPEED_MODE_200KHZ   //200KHz
#define SENSOR_I2C_CHANNEL  1                           //I2C Channel
#define SENSOR_I2C_PAD_MODE 2                           //Pad/Mode Number
//#define SENSOR_I2C_SPEED    200000                  //I2C speed, 60000~320000

#define SENSOR_I2C_LEGACY  I2C_NORMAL_MODE     //usally set CUS_I2C_NORMAL_MODE,  if use old OVT I2C protocol=> set CUS_I2C_LEGACY_MODE
#define SENSOR_I2C_FMT     I2C_FMT_A16D16        //CUS_I2C_FMT_A8D8, CUS_I2C_FMT_A8D16, CUS_I2C_FMT_A16D8, CUS_I2C_FMT_A16D16

#define SENSOR_PWDN_POL     CUS_CLK_POL_POS        // if PWDN pin High can makes sensor in power down, set CUS_CLK_POL_POS
#define SENSOR_RST_POL      CUS_CLK_POL_NEG        // if RESET pin High can makes sensor in reset state, set CUS_CLK_POL_NEG

#define SENSOR_VSYNC_POL    CUS_CLK_POL_POS         // if VSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_HSYNC_POL    CUS_CLK_POL_POS         // if HSYNC pin High and data bus have data, set CUS_CLK_POL_POS
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
} ar0330_params;
// set sensor ID address and data

typedef struct {
    float total_gain;
    unsigned short fine_val;
    unsigned short coarse_val;
    float d_gain;
} Gain_ARRAY;


I2C_ARRAY Sensor_id_table[] =
{
    {0x3000, 0x2604},    // ar0330
};

I2C_ARRAY Sensor_init_table[] =
{
    {0x31AE, 0x0202},
    {0x301A, 0x0058},     // Disable streaming

    {SENSOR_DELAY_REG, 10},

    {0x31AE, 0x202},      // Output 2-lane MIPI

    //Configure for Serial Interface
    {0x301A, 0x0058},     // Drive Pins,Parallel Enable,SMIA Serializer Disable
    {0x3064, 0x1802},   // Disable Embedded Data

    //Optimized Gain Configuration
    {0x3EE0, 0x1500},   // DAC_LD_20_21
    {0x3EEA, 0x001D},
    {0x31E0, 0x0003},
    {0x3F06, 0x046A},
    {0x3ED2, 0x0186},
    {0x3ED4, 0x8F2C},
    {0x3ED6, 0x2244},
    {0x3ED8, 0x6442},
    {0x30BA, 0x002C},     // Dither enable
    {0x3046, 0x4038},       // Enable Flash Pin
    {0x3048, 0x8480},       // Flash Pulse Length
    {0x3ED0, 0x0016},   // DAC_LD_4_5
    {0x3ED0, 0x0036},   // DAC_LD_4_5
    {0x3ED0, 0x0076},   // DAC_LD_4_5
    {0x3ED0, 0x00F6},   // DAC_LD_4_5
    {0x3ECE, 0x1003},   // DAC_LD_2_3
    {0x3ECE, 0x100F},   // DAC_LD_2_3
    {0x3ECE, 0x103F},   // DAC_LD_2_3
    {0x3ECE, 0x10FF},   // DAC_LD_2_3
    {0x3ED0, 0x00F6},   // DAC_LD_4_5
    {0x3ED0, 0x04F6},   // DAC_LD_4_5
    {0x3ED0, 0x24F6},   // DAC_LD_4_5
    {0x3ED0, 0xE4F6},   // DAC_LD_4_5
    {0x3EE6, 0xA480},   // DAC_LD_26_27
    {0x3EE6, 0xA080},   // DAC_LD_26_27
    {0x3EE6, 0x8080},   // DAC_LD_26_27
    {0x3EE6, 0x0080},   // DAC_LD_26_27
    {0x3EE6, 0x0080},   // DAC_LD_26_27
    {0x3EE8, 0x2024},   // DAC_LD_28_29
    {0x30FE, 128},        // Noise Pedestal of 128

    //Assuming Input Clock of 24MHz.  Output Clock will be 70Mpixel/s
    {0x302A, 0x0005},   // VT_PIX_CLK_DIV
    {0x302C, 0x0002},   // VT_SYS_CLK_DIV
    {0x302E, 0x0004},   // PRE_PLL_CLK_DIV
    {0x3030, 82},       // PLL_MULTIPLIER
    {0x3036, 0x000A},   // OP_PIX_CLK_DIV
    {0x3038, 0x0001},   // OP_SYS_CLK_DIV
    {0x31AC, 0x0A0A},   // DATA_FORMAT_BITS

    //MIPI TIMING
    {0x31B0, 40},         // FRAME PREAMBLE
    {0x31B2, 14},         // LINE PREAMBLE
    {0x31B4, 0x2743},     // MIPI TIMING 0
    {0x31B6, 0x114E},     // MIPI TIMING 1
    {0x31B8, 0x2049},     // MIPI TIMING 2
    {0x31BA, 0x0186},     // MIPI TIMING 3
    {0x31BC, 0x8005},     // MIPI TIMING 4
    {0x31BE, 0x2003},     // MIPI CONFIG STATUS

    //Sequencer
    {0x3088, 0x8000},      // SEQ_CTRL_PORT - [0:00:29.002]
    {0x3086, 0x4A03},     // SEQ_DATA_PORT - [0:00:29.010]
    {0x3086, 0x4316},      // SEQ_DATA_PORT - [0:00:29.014]
    {0x3086, 0x0443},      // SEQ_DATA_PORT - [0:00:29.019]
    {0x3086, 0x1645},      // SEQ_DATA_PORT - [0:00:29.023]
    {0x3086, 0x4045},     // SEQ_DATA_PORT - [0:00:29.028]
    {0x3086, 0x6017},      // SEQ_DATA_PORT - [0:00:29.033]
    {0x3086, 0x2045},      // SEQ_DATA_PORT - [0:00:29.037]
    {0x3086, 0x404B},     // SEQ_DATA_PORT - [0:00:29.042]
    {0x3086, 0x1244},      // SEQ_DATA_PORT - [0:00:29.047]
    {0x3086, 0x6134},      // SEQ_DATA_PORT - [0:00:29.051]
    {0x3086, 0x4A31},     // SEQ_DATA_PORT - [0:00:29.055]
    {0x3086, 0x4342},      // SEQ_DATA_PORT - [0:00:29.058]
    {0x3086, 0x4560},      // SEQ_DATA_PORT - [0:00:29.061]
    {0x3086, 0x2714},      // SEQ_DATA_PORT - [0:00:29.064]
    {0x3086, 0x3DFF},     // SEQ_DATA_PORT - [0:00:29.067]
    {0x3086, 0x3DFF},     // SEQ_DATA_PORT - [0:00:29.070]
    {0x3086, 0x3DEA},    // SEQ_DATA_PORT - [0:00:29.073]
    {0x3086, 0x2704},      // SEQ_DATA_PORT - [0:00:29.076]
    {0x3086, 0x3D10},     // SEQ_DATA_PORT - [0:00:29.079]
    {0x3086, 0x2705},      // SEQ_DATA_PORT - [0:00:29.082]
    {0x3086, 0x3D10},     // SEQ_DATA_PORT - [0:00:29.085]
    {0x3086, 0x2715},      // SEQ_DATA_PORT - [0:00:29.088]
    {0x3086, 0x3527},      // SEQ_DATA_PORT - [0:00:29.091]
    {0x3086, 0x053D},     // SEQ_DATA_PORT - [0:00:29.094]
    {0x3086, 0x1045},      // SEQ_DATA_PORT - [0:00:29.097]
    {0x3086, 0x4027},      // SEQ_DATA_PORT - [0:00:29.100]
    {0x3086, 0x0427},      // SEQ_DATA_PORT - [0:00:29.103]
    {0x3086, 0x143D},     // SEQ_DATA_PORT - [0:00:29.106]
    {0x3086, 0xFF3D},     // SEQ_DATA_PORT - [0:00:29.109]
    {0x3086, 0xFF3D},     // SEQ_DATA_PORT - [0:00:29.114]
    {0x3086, 0xEA62},    // SEQ_DATA_PORT - [0:00:29.117]
    {0x3086, 0x2728},      // SEQ_DATA_PORT - [0:00:29.120]
    {0x3086, 0x3627},      // SEQ_DATA_PORT - [0:00:29.123]
    {0x3086, 0x083D},     // SEQ_DATA_PORT - [0:00:29.126]
    {0x3086, 0x6444},      // SEQ_DATA_PORT - [0:00:29.129]
    {0x3086, 0x2C2C},     // SEQ_DATA_PORT - [0:00:29.132]
    {0x3086, 0x2C2C},     // SEQ_DATA_PORT - [0:00:29.135]
    {0x3086, 0x4B01},     // SEQ_DATA_PORT - [0:00:29.138]
    {0x3086, 0x432D},    // SEQ_DATA_PORT - [0:00:29.141]
    {0x3086, 0x4643},      // SEQ_DATA_PORT - [0:00:29.145]
    {0x3086, 0x1647},      // SEQ_DATA_PORT - [0:00:29.148]
    {0x3086, 0x435F},      // SEQ_DATA_PORT - [0:00:29.150]
    {0x3086, 0x4F50},      // SEQ_DATA_PORT - [0:00:29.153]
    {0x3086, 0x2604},      // SEQ_DATA_PORT - [0:00:29.156]
    {0x3086, 0x2684},      // SEQ_DATA_PORT - [0:00:29.159]
    {0x3086, 0x2027},      // SEQ_DATA_PORT - [0:00:29.164]
    {0x3086, 0xFC53},     // SEQ_DATA_PORT - [0:00:29.167]
    {0x3086, 0x0D5C},     // SEQ_DATA_PORT - [0:00:29.170]
    {0x3086, 0x0D57},     // SEQ_DATA_PORT - [0:00:29.173]
    {0x3086, 0x5417},      // SEQ_DATA_PORT - [0:00:29.176]
    {0x3086, 0x0955},      // SEQ_DATA_PORT - [0:00:29.179]
    {0x3086, 0x5649},      // SEQ_DATA_PORT - [0:00:29.182]
    {0x3086, 0x5307},      // SEQ_DATA_PORT - [0:00:29.185]
    {0x3086, 0x5302},      // SEQ_DATA_PORT - [0:00:29.188]
    {0x3086, 0x4D28},     // SEQ_DATA_PORT - [0:00:29.191]
    {0x3086, 0x6C4C},     // SEQ_DATA_PORT - [0:00:29.195]
    {0x3086, 0x0928},      // SEQ_DATA_PORT - [0:00:29.197]
    {0x3086, 0x2C28},     // SEQ_DATA_PORT - [0:00:29.200]
    {0x3086, 0x294E},      // SEQ_DATA_PORT - [0:00:29.203]
    {0x3086, 0x5C09},     // SEQ_DATA_PORT - [0:00:29.206]
    {0x3086, 0x6045},      // SEQ_DATA_PORT - [0:00:29.209]
    {0x3086, 0x0045},      // SEQ_DATA_PORT - [0:00:29.211]
    {0x3086, 0x8026},      // SEQ_DATA_PORT - [0:00:29.215]
    {0x3086, 0xA627},     // SEQ_DATA_PORT - [0:00:29.218]
    {0x3086, 0xF817},      // SEQ_DATA_PORT - [0:00:29.220]
    {0x3086, 0x0227},      // SEQ_DATA_PORT - [0:00:29.223]
    {0x3086, 0xFA5C},     // SEQ_DATA_PORT - [0:00:29.225]
    {0x3086, 0x0B17},     // SEQ_DATA_PORT - [0:00:29.228]
    {0x3086, 0x1826},      // SEQ_DATA_PORT - [0:00:29.231]
    {0x3086, 0xA25C},     // SEQ_DATA_PORT - [0:00:29.233]
    {0x3086, 0x0317},      // SEQ_DATA_PORT - [0:00:29.236]
    {0x3086, 0x4427},      // SEQ_DATA_PORT - [0:00:29.239]
    {0x3086, 0xF25F},      // SEQ_DATA_PORT - [0:00:29.241]
    {0x3086, 0x2809},      // SEQ_DATA_PORT - [0:00:29.244]
    {0x3086, 0x1714},      // SEQ_DATA_PORT - [0:00:29.246]
    {0x3086, 0x2808},      // SEQ_DATA_PORT - [0:00:29.249]
    {0x3086, 0x1616},      // SEQ_DATA_PORT - [0:00:29.252]
    {0x3086, 0x4D1A},    // SEQ_DATA_PORT - [0:00:29.254]
    {0x3086, 0x2683},      // SEQ_DATA_PORT - [0:00:29.257]
    {0x3086, 0x1616},      // SEQ_DATA_PORT - [0:00:29.260]
    {0x3086, 0x27FA},     // SEQ_DATA_PORT - [0:00:29.262]
    {0x3086, 0x45A0},     // SEQ_DATA_PORT - [0:00:29.265]
    {0x3086, 0x1707},      // SEQ_DATA_PORT - [0:00:29.268]
    {0x3086, 0x27FB},     // SEQ_DATA_PORT - [0:00:29.270]
    {0x3086, 0x1729},      // SEQ_DATA_PORT - [0:00:29.273]
    {0x3086, 0x4580},      // SEQ_DATA_PORT - [0:00:29.275]
    {0x3086, 0x1708},      // SEQ_DATA_PORT - [0:00:29.278]
    {0x3086, 0x27FA},     // SEQ_DATA_PORT - [0:00:29.281]
    {0x3086, 0x1728},      // SEQ_DATA_PORT - [0:00:29.283]
    {0x3086, 0x5D17},     // SEQ_DATA_PORT - [0:00:29.286]
    {0x3086, 0x0E26},      // SEQ_DATA_PORT - [0:00:29.289]
    {0x3086, 0x8153},      // SEQ_DATA_PORT - [0:00:29.291]
    {0x3086, 0x0117},      // SEQ_DATA_PORT - [0:00:29.294]
    {0x3086, 0xE653},      // SEQ_DATA_PORT - [0:00:29.297]
    {0x3086, 0x0217},      // SEQ_DATA_PORT - [0:00:29.299]
    {0x3086, 0x1026},      // SEQ_DATA_PORT - [0:00:29.302]
    {0x3086, 0x8326},      // SEQ_DATA_PORT - [0:00:29.304]
    {0x3086, 0x8248},      // SEQ_DATA_PORT - [0:00:29.307]
    {0x3086, 0x4D4E},     // SEQ_DATA_PORT - [0:00:29.310]
    {0x3086, 0x2809},      // SEQ_DATA_PORT - [0:00:29.312]
    {0x3086, 0x4C0B},     // SEQ_DATA_PORT - [0:00:29.315]
    {0x3086, 0x6017},      // SEQ_DATA_PORT - [0:00:29.318]
    {0x3086, 0x2027},      // SEQ_DATA_PORT - [0:00:29.320]
    {0x3086, 0xF217},      // SEQ_DATA_PORT - [0:00:29.323]
    {0x3086, 0x535F},      // SEQ_DATA_PORT - [0:00:29.325]
    {0x3086, 0x2808},      // SEQ_DATA_PORT - [0:00:29.328]
    {0x3086, 0x164D},     // SEQ_DATA_PORT - [0:00:29.331]
    {0x3086, 0x1A16},     // SEQ_DATA_PORT - [0:00:29.334]
    {0x3086, 0x1627},      // SEQ_DATA_PORT - [0:00:29.336]
    {0x3086, 0xFA26},     // SEQ_DATA_PORT - [0:00:29.339]
    {0x3086, 0x035C},     // SEQ_DATA_PORT - [0:00:29.341]
    {0x3086, 0x0145},      // SEQ_DATA_PORT - [0:00:29.344]
    {0x3086, 0x4027},      // SEQ_DATA_PORT - [0:00:29.346]
    {0x3086, 0x9817},      // SEQ_DATA_PORT - [0:00:29.349]
    {0x3086, 0x2A4A},    // SEQ_DATA_PORT - [0:00:29.352]
    {0x3086, 0x0A43},     // SEQ_DATA_PORT - [0:00:29.354]
    {0x3086, 0x160B},     // SEQ_DATA_PORT - [0:00:29.357]
    {0x3086, 0x4327},      // SEQ_DATA_PORT - [0:00:29.359]
    {0x3086, 0x9C45},     // SEQ_DATA_PORT - [0:00:29.364]
    {0x3086, 0x6017},      // SEQ_DATA_PORT - [0:00:29.366]
    {0x3086, 0x0727},      // SEQ_DATA_PORT - [0:00:29.369]
    {0x3086, 0x9D17},     // SEQ_DATA_PORT - [0:00:29.371]
    {0x3086, 0x2545},      // SEQ_DATA_PORT - [0:00:29.374]
    {0x3086, 0x4017},     // SEQ_DATA_PORT - [0:00:29.376]
    {0x3086, 0x0827},      // SEQ_DATA_PORT - [0:00:29.379]
    {0x3086, 0x985D},     // SEQ_DATA_PORT - [0:00:29.381]
    {0x3086, 0x2645},      // SEQ_DATA_PORT - [0:00:29.384]
    {0x3086, 0x5C01},     // SEQ_DATA_PORT - [0:00:29.387]
    {0x3086, 0x4B17},     // SEQ_DATA_PORT - [0:00:29.389]
    {0x3086, 0x0A28},     // SEQ_DATA_PORT - [0:00:29.392]
    {0x3086, 0x0853},      // SEQ_DATA_PORT - [0:00:29.395]
    {0x3086, 0x0D52},     // SEQ_DATA_PORT - [0:00:29.397]
    {0x3086, 0x5112},      // SEQ_DATA_PORT - [0:00:29.400]
    {0x3086, 0x4460},      // SEQ_DATA_PORT - [0:00:29.402]
    {0x3086, 0x184A},     // SEQ_DATA_PORT - [0:00:29.405]
    {0x3086, 0x0343},      // SEQ_DATA_PORT - [0:00:29.407]
    {0x3086, 0x1604},      // SEQ_DATA_PORT - [0:00:29.410]
    {0x3086, 0x4316},      // SEQ_DATA_PORT - [0:00:29.412]
    {0x3086, 0x5843},      // SEQ_DATA_PORT - [0:00:29.415]
    {0x3086, 0x1659},      // SEQ_DATA_PORT - [0:00:29.418]
    {0x3086, 0x4316},      // SEQ_DATA_PORT - [0:00:29.420]
    {0x3086, 0x5A43},     // SEQ_DATA_PORT - [0:00:29.423]
    {0x3086, 0x165B},     // SEQ_DATA_PORT - [0:00:29.425]
    {0x3086, 0x4345},      // SEQ_DATA_PORT - [0:00:29.428]
    {0x3086, 0x4027},      // SEQ_DATA_PORT - [0:00:29.431]
    {0x3086, 0x9C45},     // SEQ_DATA_PORT - [0:00:29.433]
    {0x3086, 0x6017},      // SEQ_DATA_PORT - [0:00:29.436]
    {0x3086, 0x0727},      // SEQ_DATA_PORT - [0:00:29.438]
    {0x3086, 0x9D17},     // SEQ_DATA_PORT - [0:00:29.441]
    {0x3086, 0x2545},      // SEQ_DATA_PORT - [0:00:29.443]
    {0x3086, 0x4017},      // SEQ_DATA_PORT - [0:00:29.446]
    {0x3086, 0x1027},      // SEQ_DATA_PORT - [0:00:29.449]
    {0x3086, 0x9817},      // SEQ_DATA_PORT - [0:00:29.451]
    {0x3086, 0x2022},      // SEQ_DATA_PORT - [0:00:29.454]
    {0x3086, 0x4B12},     // SEQ_DATA_PORT - [0:00:29.456]
    {0x3086, 0x442C},     // SEQ_DATA_PORT - [0:00:29.459]
    {0x3086, 0x2C2C},     // SEQ_DATA_PORT - [0:00:29.461]
    {0x3086, 0x2C00},     // SEQ_DATA_PORT - [0:00:29.464]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.467]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.469]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.472]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.474]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.477]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.479]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.482]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.485]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.487]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.490]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.492]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.496]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.499]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.501]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.504]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.506]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.509]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.511]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.514]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.517]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.519]
    {0x3086, 0x0000},     // SEQ_DATA_PORT - [0:00:29.522]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.524]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.527]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.529]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.532]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.535]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.537]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.540]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.542]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.546]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.549]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.551]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.554]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.556]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.559]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.561]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.564]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.567]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.569]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.572]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.574]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.577]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.579]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.582]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.585]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.588]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.590]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.593]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.596]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.598]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.601]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.603]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.606]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.608]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.611]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.614]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.616]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.619]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.621]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.624]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.626]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.629]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.632]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.634]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.637]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.640]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.643]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.645]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.648]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.651]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.653]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.656]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.659]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.662]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.665]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.668]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.670]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.673]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.676]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.680]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.682]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.685]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.688]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.690]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.693]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.696]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.699]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.701]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.704]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.706]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.709]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.712]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.714]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.717]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.719]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.722]
    {0x3086, 0x0000},      // SEQ_DATA_PORT - [0:00:29.724]

    // SNR_AR0330_MIPI_2_LANE_Reg_2304x1296
    {0x3030, (82+1)},   // PLL_MULTIPLIER  @ 490Mbps/lane
    {SENSOR_DELAY_REG, 100},

    //ARRAY READOUT SETTINGS
    // +2 for X axis dead pixel.
    {0x3004, 0+2},      // X_ADDR_START
    {0x3008, 2311+2},       // X_ADDR_END
    {0x3002, 122},      // Y_ADDR_START
    {0x3006, 1421},     // Y_ADDR_END

    //Sub-sampling
    {0x30A2, 1},            // X_ODD_INCREMENT
    {0x30A6, 1},            // Y_ODD_INCREMENT
    #if SENSOR_ROTATE_180
    {0x3040, 0xC000},       // [15]: flip, [14]: mirror, [12]: Row binning, [13]: column binning
    #else
    {0x3040, 0x0000},       // [15]: flip, [14]: mirror, [12]: Row binning, [13]: column binning
    #endif

    //Frame-Timing
    {0x300C, 1280},       // LINE_LENGTH_PCK
    {0x300A, 1465},     // FRAME_LENGTH_LINES
    {0x3014, 0},            // FINE_INTEGRATION_TIME
    {0x3012, 152},      // Coarse_Integration_Time
    {0x3042, 0},            // EXTRA_DELAY
    {0x30BA, 0x2C},

    {0x301A, 0x000C},     // Grouped Parameter Hold = 0x0
};

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

static Gain_ARRAY gain_table[]={
{1.00, 0,0,1.04},
{1.03, 1,0,1.04},
{1.07, 2,0,1.04},
{1.10, 3,0,1.04},
{1.14, 4,0,1.04},
{1.19, 5,0,1.04},
{1.23, 6,0,1.04},
{1.28, 7,0,1.04},
{1.33, 8,0,1.04},
{1.39, 9,0,1.04},
{1.45, 10,0,1.04},
{1.52, 11,0,1.04},
{1.60, 12,0,1.04},
{1.68, 13,0,1.04},
{1.78, 14,0,1.04},
{1.88, 15,0,1.04},
{2.00, 0,1,1.06},
{2.13, 2,1,1.06},
{2.29, 4,1,1.06},
{2.46, 6,1,1.06},
{2.67, 8,1,1.06},
{2.91, 10,1,1.06},
{3.20, 12,1,1.06},
{3.56, 14,1,1.06},
{4.00, 0,2,1.14},
{4.57, 4,2,1.14},
{5.33, 8,2,1.14},
{6.40, 12,2,1.14},
{8.00, 0,3,1.25}

};

static I2C_ARRAY gain_reg[] = {    // again = power(2, coarse_gain)*(32/(32-fine_gain))*conversion gain
    {0x3060, 0x000B},    // again: coarse:[5:4],fine:[3:0]
    {0x305E, 0x0080},    // dgain: xxxx.yyyyyyy
    //{0x3100, 0x0000},    // HCG: bit2 2.7x
    //{0x3202, 0x0080},   //noise filter
    //{0x3206, 0x0B08},   //noise filter
    //{0x3208, 0x1E13},   //noise filter
};

I2C_ARRAY expo_reg[] = {
    {0x3012, 0x0416},    // COARSE_INTEGRATION_TIME
};

I2C_ARRAY vts_reg[] = {
    {0x300A, 0x0465},    // FRAME_LENGTH_LINES
};

I2C_ARRAY mirror_reg[] = {
  //  {0x301A,0x0258},
    {0x3040, 0x0000},
  //  {0x301A,0x025C},//stream on

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
#define SENSOR_NAME ar0330
*/
//#define SensorReg_Read(_reg,_data)     (handle->i2c_bus->i2c_rx(handle->i2c_bus,handle->i2c_cfg,_reg,_data))
//#define SensorReg_Write(_reg,_data)    (handle->i2c_bus->i2c_tx(handle->i2c_bus,handle->i2c_cfg,_reg,_data))
//#define SensorRegArrayW(_reg,_len)  (handle->i2c_bus->i2c_array_tx(handle->i2c_bus, handle->i2c_cfg,(_reg),(_len)))
//#define SensorRegArrayR(_reg,_len)  (handle->i2c_bus->i2c_array_rx(handle->i2c_bus, handle->i2c_cfg,(_reg),(_len)))

int ar0330_MIPI_cus_camsensor_release_handle(ms_cus_sensor *handle);

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
	sensor_if->SWReset(handle->channel_num, FALSE);
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
    SensorReg_Read(0x3072, &sen_data1);
    if(sen_data1!=0x08){   //rev2.1 (V5)
        SENSOR_DMSG("[%s] OTP read wrong version, 0x3072=0x%x\n", __FUNCTION__,sen_data1);
        return FAIL;
    }
     SENSOR_DMSG("[%s] 0x3072=0x%x\n", __FUNCTION__,sen_data1);



    return SUCCESS;
}

static int ar0330_SetPatternMode(ms_cus_sensor *handle,u32 mode)
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
        UartSendTrace("[%s] ar0330SensorReg: %d 0x%x, 0x%x, \n", __FUNCTION__, i, Sensor_init_table[i].reg, ReadData);
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
    *orit = CUS_ORIT_M0F0;
    return SUCCESS;
}

static int pCus_SetOrien(ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT orit)
{
  short index=0;
    ar0330_params *params = (ar0330_params *)handle->private_data;

  switch(orit) {
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
  if (index != mirror_reg[0].data) {
    mirror_reg[0].data = index;
    params->orient_dirty = true;
    }

    return SUCCESS;
}

static int pCus_GetFPS(ms_cus_sensor *handle)
{
    ar0330_params *params = (ar0330_params *)handle->private_data;
    SENSOR_DMSG("[%s]", __FUNCTION__);

    return  params->expo.fps;
}
static int pCus_SetFPS(ms_cus_sensor *handle, u32 fps)
{
    ar0330_params *params = (ar0330_params *)handle->private_data;

  SENSOR_DMSG("\n\n[%s], fps=%d\n", __FUNCTION__, fps);
    if(fps>=5 && fps <= 30){
        params->expo.fps = fps;
    params->expo.vts=  (vts_30fps*30)/fps;
    vts_reg[0].data = params->expo.vts;
    }else if(fps>=5000 && fps <= 30000){
        params->expo.fps = fps;
    params->expo.vts=  (vts_30fps*30000)/fps;
    vts_reg[0].data = params->expo.vts;
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
    ar0330_params *params = (ar0330_params *)handle->private_data;
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
  int rc;
    u32 lines = 0;
  rc = SensorRegArrayR((I2C_ARRAY*)expo_reg, ARRAY_SIZE(expo_reg));
  if (SUCCESS == rc) {
    lines = expo_reg[0].data;
    *us = lines*Preview_line_period/1000;
  }
  SENSOR_DMSG("[%s] sensor expo lines/us %d, %dus\n", __FUNCTION__, lines, *us);
  return rc;
}

static int pCus_SetAEUSecs(ms_cus_sensor *handle, u32 us) {
    u32 lines = 0, vts = 0;
    ar0330_params *params = (ar0330_params *)handle->private_data;

    lines=(1000*us)/Preview_line_period;
    if(lines<1) lines=1;
    if (lines >params->expo.vts-1)
    {
        vts = lines +1;
    }
    else
        vts=params->expo.vts;

    expo_reg[0].data = lines;
    vts_reg[0].data = vts;

    SENSOR_DMSG("[%s] us %ld, lines %ld, vts %ld\n", __FUNCTION__, us, lines, params->expo.vts);
    //printf("us %ld, lines %ld, vts %ld\n", us, lines, params->expo.vts);
    params->dirty = true;    //reg need to update
    return SUCCESS;
}

// Gain: 1x = 1024
static int pCus_GetAEGain(ms_cus_sensor *handle, u32* gain) {
  int rc = SUCCESS;
    ar0330_params *params = (ar0330_params *)handle->private_data;

    *gain=params->expo.final_gain;
   SENSOR_DMSG("[%s] gain = 0x%x\n", __FUNCTION__, *gain);
  return rc;
}

static int pCus_SetAEGain(ms_cus_sensor *handle, u32 gain) {

   // u16 coarse_gain, fine_gain,i;
    u16 coarse_reg=0,fine_reg,i;
    double DGain_double,gain_double,total_gain_double;
    ar0330_params *params = (ar0330_params *)handle->private_data;
    CUS_GAIN_GAP_ARRAY* Sensor_Gain_Linearity;


    if(gain<SENSOR_MIN_GAIN)
        gain=SENSOR_MIN_GAIN;
    else if(gain>=SENSOR_MAX_GAIN)
        gain=SENSOR_MAX_GAIN;
    params->expo.final_gain = gain;
    Sensor_Gain_Linearity = gain_gap_compensate;
/*
    for(i = 0; i < sizeof(gain_gap_compensate)/sizeof(CUS_GAIN_GAP_ARRAY); i++){
        //LOGD("GAP:%x %x\r\n",Sensor_Gain_Linearity[i].gain, Sensor_Gain_Linearity[i].offset);

        if (Sensor_Gain_Linearity[i].gain == 0)
            break;
        if((gain>Sensor_Gain_Linearity[i].gain) && (gain < (Sensor_Gain_Linearity[i].gain + Sensor_Gain_Linearity[i].offset))){
              gain=Sensor_Gain_Linearity[i].gain;
              break;
        }
    }
*/
    gain_double=(double)gain;
    if (gain >= 8*1024) {
       // coarse_gain = 8;
        coarse_reg = 0x3;
        fine_reg=0;
        DGain_double=(gain_double/8192);
        DGain_double=DGain_double*1.25;

    } else {
       // coarse_gain = 1;
      //  coarse_reg = 0x0;
        total_gain_double=(gain_double)/1024;
        for(i=1;i<29;i++){
           if(gain_table[i].total_gain>total_gain_double){
                fine_reg=gain_table[i-1].fine_val;
                coarse_reg=gain_table[i-1].coarse_val;
                DGain_double=(total_gain_double/gain_table[i-1].total_gain);
                DGain_double=DGain_double*gain_table[i-1].d_gain;
                break;
            }
            else if(i==29){
                fine_reg=gain_table[i].fine_val;
                DGain_double=(total_gain_double/gain_table[i].total_gain);
                DGain_double=DGain_double*gain_table[i].d_gain;
                break;
            }
        }
    }

      if(DGain_double<1.04)
         DGain_double=1.04;
      else if(DGain_double>15.9)
         DGain_double=15.9;
      gain_reg[0].data =(u16)( (coarse_reg<<4) | fine_reg);
      gain_reg[1].data = (u16)(DGain_double*128);
      SENSOR_DMSG("[%s]gain=%d,total_gain_double=%f, coarse_gain=%d , fine_gain=%d,DGain_double=%f\n",__FUNCTION__,gain,total_gain_double,coarse_gain,fine_gain ,DGain_double);
   //printf("gain=%d,total_gain_double=%f, coarse_gain=%d , fine_gain=%d,DGain_double=%f\n",gain,total_gain_double,coarse_gain,fine_gain ,DGain_double);
    params->dirty = true;    //reg need to update
    return SUCCESS;
    }
static int pCus_SetAEGain_cal(ms_cus_sensor *handle, u32 gain) {

    //u16 coarse_gain, fine_gain,i;
     u16 coarse_reg=0,fine_reg,i;
    double DGain_double,gain_double,total_gain_double;
    ar0330_params *params = (ar0330_params *)handle->private_data;
   // params->expo.final_gain = gain;


    if(gain<SENSOR_MIN_GAIN)
        gain=SENSOR_MIN_GAIN;
    else if(gain>=SENSOR_MAX_GAIN)
        gain=SENSOR_MAX_GAIN;

    gain_double=(double)gain;
    if (gain >= 8*1024) {
       // coarse_gain = 8;
        coarse_reg = 0x3;
        fine_reg=0;
        DGain_double=(gain_double/8192);
        DGain_double=DGain_double*1.25;

    } else {
       // coarse_gain = 1;
      //  coarse_reg = 0x0;
        total_gain_double=(gain_double)/1024;
             for(i=1;i<29;i++){
                   if(gain_table[i].total_gain>total_gain_double){
                      fine_reg=gain_table[i-1].fine_val;
                      coarse_reg=gain_table[i-1].coarse_val;
                      DGain_double=(total_gain_double/gain_table[i-1].total_gain);
                      DGain_double=DGain_double*gain_table[i-1].d_gain;
                      break;
                      }
                   else if(i==29){
                      fine_reg=gain_table[i].fine_val;
                      DGain_double=(total_gain_double/gain_table[i].total_gain);
                      DGain_double=DGain_double*gain_table[i].d_gain;
                      break;
                    }
                  }



    }

      if(DGain_double<1.04)
         DGain_double=1.04;
      else if(DGain_double>15.9)
         DGain_double=15.9;
      gain_reg[0].data =(u16)( (coarse_reg<<4) | fine_reg);
      gain_reg[1].data = (u16)(DGain_double*128);
      SENSOR_DMSG("[%s]gain=%d,total_gain_double=%f, coarse_gain=%d , fine_gain=%d,DGain_double=%f\n",__FUNCTION__,gain,total_gain_double,coarse_gain,fine_gain ,DGain_double);
   //printf("gain=%d,total_gain_double=%f, coarse_gain=%d , fine_gain=%d,DGain_double=%f\n",gain,total_gain_double,coarse_gain,fine_gain ,DGain_double);
    params->dirty = true;    //reg need to update
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

static int ar0330_GetShutterInfo(struct __ms_cus_sensor* handle,CUS_SHUTTER_INFO *info)
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

int ar0330_MIPI_cus_camsensor_init_handle(ms_cus_sensor* drv_handle)
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
    UartSendTrace("\n===== AR0330 init. =====\n");
    #if defined(__RTK_OS__)
    sprintf(str, "AR0330cali");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(ar0330_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (ar0330_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(ar0330_params));
    #else
    handle->private_data = calloc( 1, sizeof(ar0330_params) );
    #endif

    ar0330_params *params = (ar0330_params *)handle->private_data;

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

    handle->pCus_sensor_release     = ar0330_MIPI_cus_camsensor_release_handle;
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
    handle->pCus_sensor_SetPatternMode    = ar0330_SetPatternMode;

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
    handle->pCus_sensor_GetShutterInfo = ar0330_GetShutterInfo;

    params->expo.vts=vts_30fps;
    params->expo.fps = 30;

    handle->snr_pad_group = SENSOR_PAD_GROUP_SET;

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

static int ar0330_SetPatternMode_isp_calibration( ms_cus_sensor *handle, u32 mode )
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
    ar0330_params *params = ( ar0330_params * ) handle->private_data;
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

static int ar0330_GetShutterInfo_isp_calibration( struct __ms_cus_sensor* handle, CUS_SHUTTER_INFO *info )
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


int ar0330_MIPI_cus_camsensor_init_handle_isp_calibration(ms_cus_sensor* drv_handle)
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
    UartSendTrace("\n===== AR0330 init. =====\n");
    #if defined(__RTK_OS__)
    sprintf(str, "AR0330cali");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(ar0330_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (ar0330_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(ar0330_params));
    #else
    handle->private_data = calloc( 1, sizeof(ar0330_params) );
    #endif

    ar0330_params *params = (ar0330_params *)handle->private_data;

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

    handle->pCus_sensor_release     = ar0330_MIPI_cus_camsensor_release_handle;
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
    handle->pCus_sensor_SetPatternMode    = ar0330_SetPatternMode_isp_calibration;

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
    handle->pCus_sensor_GetShutterInfo = ar0330_GetShutterInfo_isp_calibration;

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

int ar0330_MIPI_cus_camsensor_release_handle(ms_cus_sensor *handle)
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
        eCamOsRet = CamOsDirectMemRelease((void*)handle->private_data, sizeof(ar0330_params));
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
struct SensorMapTable_t gsensor_map_ar0330[] = {
    { //Channel 0
        SENSOR_CHANNEL_NUM,
        ar0330_MIPI_cus_camsensor_init_handle,
        ar0330_MIPI_cus_camsensor_release_handle
    },
#if (SENSOR_CHANNEL_AR0330_ISP_CALIBRATION_ENABLE == 1)
    { //Channel 1. ISP calibration.
        SENSOR_CHANNEL_NUM + 1,
        ar0330_MIPI_cus_camsensor_init_handle_isp_calibration,
        ar0330_MIPI_cus_camsensor_release_handle
    },
#endif
};

int AR0330_Module_Init(void)
{
    cameraSensorRegister(&gsensor_map_ar0330[0]);
#if (SENSOR_CHANNEL_AR0330_ISP_CALIBRATION_ENABLE == 1)
    cameraSensorRegister(&gsensor_map_ar0330[1]);
#endif
    return 0;
}

void AR0330_Module_Exit(void)
{
    cameraSensorUnRegister(&gsensor_map_ar0330[0]);
#if (SENSOR_CHANNEL_AR0330_ISP_CALIBRATION_ENABLE == 1)
    cameraSensorRegister(&gsensor_map_ar0330[1]);
#endif
}

#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(AR0330_Module_Init);
#endif //#if defined(__RTK_OS__)

#endif
