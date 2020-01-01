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
//#include "MsTypes.h"
//#include "drv_ms_cus_motor.h"
#include "drv_SensorIF_pub.h"
#include "drv_ms_cus_sensor.h"
#include "drv_i2c_common.h"
#include <sensor_log.h>
//#include "dbg_info.h"
//#include "drv_ms_rwcfg.h"
//#include "hal_ms_isp_i2c.h"
//#include <version.h>
//#include "logcat.h"
//#include <utils/Log.h>
#ifdef __cplusplus
}
#endif

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
#if (SENSOR0 == BG0806)
#define BIND_SENSOR_BG0806 (1)
#endif
#endif //#if defined(__RTK_OS__)

#if defined(BIND_SENSOR_BG0806) && (BIND_SENSOR_BG0806 == 1)

#define __SENSOR_W (1)

#define SENSOR_PAD_GROUP_SET CUS_SENSOR_PAD_GROUP_A
#define SENSOR_CHANNEL_NUM (0)
#define SENSOR_CHANNEL_MODE CUS_SENSOR_CHANNEL_MODE_REALTIME_NORMAL
//#define SENSOR_CHANNEL_MODE_SONY_DOL CUS_SENSOR_CHANNEL_MODE_RAW_STORE_HDR

#define SENSOR_CHANNEL_BG0806_ISP_CALIBRATION_ENABLE  (0)//(1) // 2018-4-26 large lcd set 0

//============================================
//MIPI config begin.
#define SENSOR_MIPI_LANE_NUM (1)
//#define SENSOR_MIPI_HDR_MODE (0) //0: Non-HDR mode. 1:Sony DOL mode
//MIPI config end.
//============================================

#define LOGD //(...)

//c11 extern int usleep(u32 usec);
//int usleep(u32 usec);

#define R_GAIN_REG 1
#define G_GAIN_REG 2
#define B_GAIN_REG 3

#define BG0806A     0x01
#define BG0806C1    0x07
#define BG0806C2    0x0b
#define BG0806B1    0x03
#define BG0806B2    0x0f

#undef SENSOR_DBG
#define SENSOR_DBG 1

#define SENSOR_ISP_TYPE     ISP_EXT                   //ISP_EXT, ISP_SOC
#define F_number  22                                  // CFG, demo module
//#define SENSOR_DATAFMT      CUS_DATAFMT_BAYER        //CUS_DATAFMT_YUV, CUS_DATAFMT_BAYER
#define SENSOR_IFBUS_TYPE   CUS_SENIF_BUS_MIPI      //CFG //CUS_SENIF_BUS_PARL, CUS_SENIF_BUS_MIPI
#define SENSOR_MIPI_HSYNC_MODE PACKET_HEADER_EDGE1
#define SENSOR_MIPI_DELAY   0x1212                  //CFG
#define SENSOR_DATAPREC     CUS_DATAPRECISION_10 //12    //CFG //CUS_DATAPRECISION_8, CUS_DATAPRECISION_10
#define SENSOR_DATAMODE     CUS_SEN_10TO12_9098     //CFG
#define SENSOR_BAYERID      CUS_BAYER_GR//CUS_BAYER_RG            //CFG //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
#ifndef SENSOR_ORIT
#define SENSOR_ORIT         CUS_ORIT_M1F1           //CUS_ORIT_M0F0, CUS_ORIT_M1F0, CUS_ORIT_M0F1, CUS_ORIT_M1F1,
#endif
//#define SENSOR_YCORDER      CUS_SEN_YCODR_YC       //CUS_SEN_YCODR_YC, CUS_SEN_YCODR_CY
//#define lane_number 2
//#define vc0_hs_mode 3   //0: packet header edge  1: line end edge 2: line start edge 3: packet footer edge
//#define long_packet_type_enable 0x00 //UD1~UD8 (user define)
#define SENSOR_MAX_GAIN      (60* 1024)//(8 * 1024)                  // max sensor again, a-gain * conversion-gain*d-gain
#define SENSOR_MIN_GAIN      (1 * 1024)
#define SENSOR_GAIN_DELAY_FRAME_COUNT      (2)
#define SENSOR_SHUTTER_DELAY_FRAME_COUNT      (2)

#define Preview_MCLK_SPEED  CUS_CMU_CLK_24MHZ //CUS_CMU_CLK_36MHZ//CUS_CMU_SCL_CLK_37P125M        //CFG //CUS_CMU_CLK_12M, CUS_CMU_CLK_16M, CUS_CMU_CLK_24M, CUS_CMU_CLK_27M
//#define Preview_line_period 30000                  ////HTS/PCLK=4455 pixels/148.5MHZ=30usec @MCLK=36MHz
//#define vts_30fps 1125//1346,1616                 //for 29.1fps @ MCLK=36MHz
#define Preview_line_period 35556//29630//30556//30580                  //(36M/37.125M)*30fps=29.091fps(34.375msec), hts=34.375/1125=30556,
//#define Line_per_second     32727
#define vts_30fps  1125//1090 8+VSIZE+VBLANK                             //for 25fps =1125*30/25=1350
#define Prv_Max_line_number 1080                    //maximum exposure line munber of sensor when preview
#define Preview_WIDTH       1920                    //resolution Width when preview
#define Preview_HEIGHT      1080                    //resolution Height when preview
#define Preview_MAX_FPS     25//30                     //fastest preview FPS
#define Preview_MIN_FPS     3                      //slowest preview FPS
#define Preview_CROP_START_X     1                      //CROP_START_X
#define Preview_CROP_START_Y     1                      //CROP_START_Y

#define SENSOR_I2C_ADDR    0x64                   //I2C slave address
#define SENSOR_I2C_SPEED   I2C_SLOWSPEED_MODE_200KHZ//200000 //300000// 240000                  //I2C speed, 60000~320000
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
//static int  drv_Fnumber = 22;

#if SENSOR_DBG == 1
//#define SENSOR_DMSG(args...) LOGD(args)
//#define SENSOR_DMSG(args...) LOGE(args)
//#define SENSOR_DMSG(args...) printf(args)
#elif SENSOR_DBG == 0
//#define SENSOR_DMSG(args...)
#endif
#undef SENSOR_NAME
#define SENSOR_NAME BG0806

//#define SensorReg_Read(_reg,_data)     (handle->i2c_bus->i2c_rx(handle->i2c_bus,handle->i2c_cfg,_reg,_data))
//#define SensorReg_Write(_reg,_data)    (handle->i2c_bus->i2c_tx(handle->i2c_bus,handle->i2c_cfg,_reg,_data))
//#define SensorRegArrayW(_reg,_len)  (handle->i2c_bus->i2c_array_tx(handle->i2c_bus, handle->i2c_cfg,(_reg),(_len)))
//#define SensorRegArrayR(_reg,_len)  (handle->i2c_bus->i2c_array_rx(handle->i2c_bus, handle->i2c_cfg,(_reg),(_len)))

int cus_camsensor_release_handle(ms_cus_sensor *handle);
static int pCus_SetAEGain(ms_cus_sensor *handle, u32 gain);
static int pCus_SetAEUSecs(ms_cus_sensor *handle, u32 us);
static int pCus_SetFPS(ms_cus_sensor *handle, u32 fps);
static int pCus_SetOrien(ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT orit);
u32 blank = 0;

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
    bool reg_dirty;
    bool change;
} bg0806_params;
// set sensor ID address and data,

I2C_ARRAY Sensor_id_table[] =
{
//{0x3004, 0x10},      // {address of ID, ID },
//{0x3009, 0x01},      // {address of ID, ID },
};

#if 0
//FHD@25FPS
I2C_ARRAY Sensor_init_table_1lane[] =
{
    {0x0200,0x0001},
    //{0x0003,0x0027},

    {0x0002,0x00}, //1920
    {0x0003,0x28},
    {0x0004,0x00}, //1080
    {0x0005,0x00},

    {0x0006,0x07}, //1928
    {0x0007,0x88},//0x88  //1928
    {0x0008,0x04}, //1088
    {0x0009,0x40},//0x40 //1088


    {0x000e, 0x0008},
    {0x000f, 0x00ae},
    {0x0013, 0x0001},
    {0x0021, 0x0000},//0
    {0x0022, 0x00fe},//25 30fps  // fe 25fps
    {0x0028, 0x0000},
    {0x0029, 0x0030},
    {0x002a, 0x0000},
    {0x002b, 0x0050},
    {0x0030, 0x0000},
    {0x0031, 0x00c0},
    {0x0034, 0x0000},
    {0x0035, 0x00c0},
    {0x003c, 0x0001},
    {0x003d, 0x0084},
    {0x003e, 0x0005},
    {0x0042, 0x0001},
    {0x005c, 0x0000},
    {0x0061, 0x0004},
    {0x0062, 0x005c},
    {0x0064, 0x0000},
    {0x0065, 0x0080},
    {0x0067, 0x0001},
    {0x0068, 0x0090},
    {0x006c, 0x0003},
    {0x007f, 0x0000},
    {0x0080, 0x0001},
    {0x0081, 0x0000},
    {0x0082, 0x000b},
    {0x0084, 0x0008},
    {0x0088, 0x0005},
    {0x008e, 0x0000},
    {0x008f, 0x0000},

    {0x0090, 0x0001},//170411 3.3V

    {0x0094, 0x0001},
    {0x0095, 0x0001},
    {0x009e, 0x0003},
    {0x009f, 0x0020},
    {0x00b1, 0x007f},
    {0x00b2, 0x0002},
    {0x00bc, 0x0002},
    {0x00bd, 0x0000},
    {0x0120, 0x0001},
    {0x0139, 0x0007},
    {0x0139, 0x00ff},
    {0x013b, 0x0008},
    {0x01a5, 0x0007},
    {0x0160, 0x0000},
    {0x0161, 0x0030},
    {0x0162, 0x0000},
    {0x0163, 0x0030},
    {0x0164, 0x0000},
    {0x0165, 0x0030},
    {0x0166, 0x0000},
    {0x0167, 0x0030},
    {0x0053, 0x0000},
    {0x0054, 0x0028},
    {0x0055, 0x0000},

    {0x00f3, 0x0000},
    {0x00f4, 0x007b},
    {0x00f5, 0x0006},

    {0x006d, 0x0003},
    {0x006c, 0x0000},
    {0x008d, 0x003f},
    {0x008e, 0x000c},
    {0x008f, 0x0003},
    {0x00fa, 0x00cf},
    {0x0391, 0x0000},
    {0x0392, 0x0000},
    {0x0393, 0x0001},
    {0x0398, 0x000a},
    {0x0390, 0x0006},

    ///{0x0132, 0x00,
    //{0x0133, 0xff},
    //{0x0206, 0x00}, //0x03
    //{0x0207, 0x01},
    {0x006e, 0x00},

    {0x0131, 0x74},

    //{0x0151, 0x02},//R
    //{0x0153, 0x06},//G
    //{0x0155, 0x06},//G
    //{0x0157, 0x02},//B


    {0x001d, 0x0001},
};
#endif

//FHD@30FPS
I2C_ARRAY Sensor_init_table_1lane[] =
{
    {0x0200,0x0001},
    //{0x0003,0x0027},

    {0x0002,0x00}, //1920
    {0x0003,0x28},
    {0x0004,0x00}, //1080
    {0x0005,0x00},

    {0x0006,0x07}, //1928
    {0x0007,0x88}, //0x88  //1928
    {0x0008,0x04}, //1088
    {0x0009,0x40}, //0x40 //1088


    {0x000e, 0x0008},
    {0x000f, 0x00ae},
    {0x0013, 0x0001},
    {0x0021, 0x0000},//0
    {0x0022, 0x0025},//25 30fps  // fe 25fps // 2018-4-14
    {0x0028, 0x0000},
    {0x0029, 0x0030},
    {0x002a, 0x0000},
    {0x002b, 0x0050},
    {0x0030, 0x0000},
    {0x0031, 0x00c0},
    {0x0034, 0x0000},
    {0x0035, 0x00c0},
    {0x003c, 0x0001},
    {0x003d, 0x0084},
    {0x003e, 0x0005},
    {0x0042, 0x0001},
    {0x005c, 0x0000},
    {0x0061, 0x0004},
    {0x0062, 0x005c},
    {0x0064, 0x0000},
    {0x0065, 0x0080},
    {0x0067, 0x0001},
    {0x0068, 0x0090},
    {0x006c, 0x0003},
    {0x007f, 0x0000},
    {0x0080, 0x0001},
    {0x0081, 0x0000},
    {0x0082, 0x000b},
    {0x0084, 0x0008},
    {0x0088, 0x0005},
    {0x008e, 0x0000},
    {0x008f, 0x0000},

    {0x0090, 0x0001},//170411 3.3V

    {0x0094, 0x0001},
    {0x0095, 0x0001},
    {0x009e, 0x0003},
    {0x009f, 0x0020},
    {0x00b1, 0x007f},
    {0x00b2, 0x0002},
    {0x00bc, 0x0002},
    {0x00bd, 0x0000},
    {0x0120, 0x0001},
    {0x0139, 0x0007},
    {0x0139, 0x00ff},
    {0x013b, 0x0008},
    {0x01a5, 0x0007},
    {0x0160, 0x0000},
    {0x0161, 0x0030},
    {0x0162, 0x0000},
    {0x0163, 0x0030},
    {0x0164, 0x0000},
    {0x0165, 0x0030},
    {0x0166, 0x0000},
    {0x0167, 0x0030},
    {0x0053, 0x0000},
    {0x0054, 0x0028},
    {0x0055, 0x0000},

    {0x00f3, 0x0000},
    {0x00f4, 0x007b},
    {0x00f5, 0x0006},

    {0x006d, 0x0003},
    {0x006c, 0x0000},
    {0x008d, 0x003f},
    {0x008e, 0x000c},
    {0x008f, 0x0003},
    {0x00fa, 0x00cf},
    {0x0391, 0x0000},
    {0x0392, 0x0000},
    {0x0393, 0x0001},
    {0x0398, 0x000a},
    {0x0390, 0x0006},

    //{0x0132, 0x00},
    //{0x0133, 0xff},
    //{0x0206, 0x00}, //0x03
    //{0x0207, 0x01},
    {0x006e, 0x00},
 #if 1  // 2018-4-17 15:12
    {0x0131, 0x38},//0x18 // 2018-4-19 19:50
    {0x0153, 0x06},//G  // 2018-4-21 15:28
    {0x0155, 0x06},//G // 2018-4-21 15:28
 #else
    {0x0131, 0x74},

    //{0x0151, 0x02}, //R
    {0x0153, 0x06},//G
    {0x0155, 0x06},//G
    //{0x0157, 0x02},//B
#endif

//5fps
#if 0
    {0x00f1, 0x00},
    {0x00f4, 0x04},
    {0x00f5, 0x00},
    {0x00fb, 0x01},
#endif
//25fps
#if 1
        {0x00f1, 0x08},
        {0x00f4, 0x18},
        {0x00f5, 0x00},
        {0x00fb, 0x02},
#endif


    {0x001d, 0x0001},
};

#define DSC_ADDR_BASE 0x0400
 U8 Tab_sensor_dsc[768] = {
        //20170206 update dsc   external ldo
        0x0a, 0x5c, 0x09, 0x4a, 0x08, 0x07, 0x06, 0xee, 0x06, 0x23, 0x05, 0x7e, 0x05, 0x21, 0x05, 0x01, 0x05, 0xcc, 0x06, 0xf5,
        0x08, 0x0b, 0x09, 0x0e, 0x0a, 0x0e, 0x0b, 0x34, 0x0c, 0x42, 0x0e, 0x9b, 0x09, 0xe0, 0x08, 0x71, 0x06, 0xce, 0x05, 0xd7,
        0x05, 0x19, 0x04, 0x9c, 0x04, 0x54, 0x04, 0x4d, 0x04, 0xd2, 0x05, 0xf8, 0x07, 0x04, 0x07, 0xe3, 0x08, 0xe2, 0x09, 0xfe,
        0x0b, 0x69, 0x0d, 0xfa, 0x09, 0x62, 0x07, 0x83, 0x05, 0xd8, 0x04, 0xe6, 0x04, 0x44, 0x03, 0xe5, 0x03, 0x82, 0x03, 0x88,
        0x04, 0x07, 0x05, 0x09, 0x05, 0xfe, 0x06, 0xc5, 0x07, 0xbf, 0x08, 0xe2, 0x0a, 0x68, 0x0d, 0x59, 0x08, 0xf7, 0x06, 0xea,
        0x05, 0x43, 0x04, 0x55, 0x03, 0xbf, 0x03, 0x43, 0x03, 0x09, 0x02, 0xf7, 0x03, 0x83, 0x04, 0x75, 0x05, 0x5c, 0x06, 0x09,
        0x06, 0xf5, 0x08, 0x1c, 0x09, 0xa6, 0x0c, 0xc6, 0x08, 0x6a, 0x06, 0x5e, 0x04, 0xa9, 0x03, 0xc7, 0x03, 0x36, 0x02, 0xd1,
        0x02, 0x99, 0x02, 0x91, 0x02, 0xea, 0x03, 0xdb, 0x04, 0xad, 0x05, 0x4f, 0x06, 0x48, 0x07, 0x62, 0x08, 0xf4, 0x0b, 0x71,
        0x07, 0xbd, 0x05, 0xd0, 0x04, 0x2a, 0x03, 0x43, 0x02, 0xa1, 0x02, 0x4d, 0x02, 0x08, 0x01, 0xf8, 0x02, 0x58, 0x03, 0x3f,
        0x03, 0xec, 0x04, 0xa1, 0x05, 0x87, 0x06, 0xa5, 0x08, 0x31, 0x0a, 0xc0, 0x07, 0x5a, 0x05, 0x54, 0x03, 0xa0, 0x02, 0xca,
        0x02, 0x4a, 0x01, 0xd9, 0x01, 0x9c, 0x01, 0x98, 0x01, 0xf0, 0x02, 0xba, 0x03, 0x70, 0x04, 0x02, 0x04, 0xe5, 0x06, 0x0b,
        0x07, 0x84, 0x0a, 0x2f, 0x06, 0xdf, 0x04, 0xe4, 0x03, 0x3f, 0x02, 0x6d, 0x01, 0xe9, 0x01, 0x84, 0x01, 0x47, 0x01, 0x3f,
        0x01, 0x8e, 0x02, 0x31, 0x02, 0xea, 0x03, 0x78, 0x04, 0x5e, 0x05, 0x68, 0x06, 0xea, 0x09, 0x27, 0x06, 0x82, 0x04, 0x81,
        0x02, 0xe8, 0x02, 0x20, 0x01, 0x9c, 0x01, 0x2c, 0x00, 0xfa, 0x00, 0xea, 0x01, 0x37, 0x01, 0xdc, 0x02, 0x76, 0x02, 0xf6,
        0x03, 0xd5, 0x04, 0xd7, 0x06, 0x49, 0x08, 0xb0, 0x06, 0x4b, 0x04, 0x42, 0x02, 0xaf, 0x01, 0xde, 0x01, 0x4f, 0x00, 0xe7,
        0x00, 0xa2, 0x00, 0x92, 0x00, 0xb6, 0x01, 0x5a, 0x01, 0xe4, 0x02, 0x7e, 0x03, 0x3b, 0x04, 0x31, 0x05, 0x88, 0x07, 0xb8,
        0x06, 0x25, 0x04, 0x0d, 0x02, 0x7a, 0x01, 0xa1, 0x01, 0x1b, 0x00, 0xab, 0x00, 0x5e, 0x00, 0x4e, 0x00, 0x68, 0x00, 0xf2,
        0x01, 0x62, 0x01, 0xec, 0x02, 0x9e, 0x03, 0x8f, 0x04, 0xe3, 0x07, 0x01, 0x06, 0x0e, 0x04, 0x0d, 0x02, 0x66, 0x01, 0x94,
        0x01, 0x10, 0x00, 0x99, 0x00, 0x44, 0x00, 0x21, 0x00, 0x34, 0x00, 0x97, 0x01, 0x13, 0x01, 0x94, 0x02, 0x49, 0x03, 0x40,
        0x04, 0x75, 0x06, 0x92, 0x06, 0x54, 0x04, 0x31, 0x02, 0x96, 0x01, 0xc5, 0x01, 0x18, 0x00, 0x99, 0x00, 0x39, 0x00, 0x21,
        0x00, 0x21, 0x00, 0x65, 0x00, 0xd6, 0x01, 0x5f, 0x02, 0x0c, 0x02, 0xfa, 0x04, 0x31, 0x06, 0x5b, 0x06, 0x5c, 0x04, 0x41,
        0x02, 0x9e, 0x01, 0xc5, 0x01, 0x18, 0x00, 0x99, 0x00, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x59, 0x00, 0xc6, 0x01, 0x4b,
        0x01, 0xf9, 0x02, 0xf3, 0x04, 0x1d, 0x06, 0x37, 0x06, 0x0e, 0x04, 0x1a, 0x02, 0x92, 0x01, 0xbd, 0x01, 0x18, 0x00, 0xa1,
        0x00, 0x4a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x59, 0x00, 0xce, 0x01, 0x4b, 0x02, 0x14, 0x02, 0xfa, 0x04, 0x25, 0x06, 0x3f,
        0x05, 0x82, 0x03, 0xf2, 0x02, 0x87, 0x01, 0xa0, 0x01, 0x28, 0x00, 0xaa, 0x00, 0x62, 0x00, 0x31, 0x00, 0x3c, 0x00, 0x89,
        0x00, 0xfe, 0x01, 0x7b, 0x02, 0x3a, 0x03, 0x26, 0x04, 0x69, 0x06, 0x82, 0x05, 0xb3, 0x04, 0x02, 0x02, 0x97, 0x01, 0xd2,
        0x01, 0x43, 0x00, 0xdb, 0x00, 0x99, 0x00, 0x5d, 0x00, 0x75, 0x00, 0xd6, 0x01, 0x4b, 0x01, 0xc7, 0x02, 0x71, 0x03, 0x73,
        0x04, 0xc7, 0x06, 0xe2, 0x05, 0xcf, 0x04, 0x3c, 0x02, 0xe4, 0x02, 0x1f, 0x01, 0x90, 0x01, 0x30, 0x00, 0xe6, 0x00, 0xcb,
        0x00, 0xd6, 0x01, 0x2b, 0x01, 0xb5, 0x02, 0x25, 0x02, 0xf3, 0x03, 0xe4, 0x05, 0x42, 0x07, 0xb2, 0x05, 0xe0, 0x04, 0x83,
        0x03, 0x22, 0x02, 0x67, 0x01, 0xed, 0x01, 0x7d, 0x01, 0x3f, 0x01, 0x14, 0x01, 0x27, 0x01, 0x93, 0x02, 0x10, 0x02, 0x8d,
        0x03, 0x4c, 0x04, 0x3f, 0x05, 0x9c, 0x07, 0xc1, 0x06, 0x1d, 0x04, 0xce, 0x03, 0x7d, 0x02, 0xb5, 0x02, 0x42, 0x01, 0xd1,
        0x01, 0x85, 0x01, 0x74, 0x01, 0x88, 0x01, 0xe8, 0x02, 0x71, 0x02, 0xe1, 0x03, 0xc0, 0x04, 0xb6, 0x06, 0x04, 0x08, 0x7f,
        0x06, 0x40, 0x05, 0x10, 0x03, 0xe0, 0x03, 0x1b, 0x02, 0xab, 0x02, 0x3a, 0x01, 0xe4, 0x01, 0xd4, 0x01, 0xdc, 0x02, 0x50,
        0x02, 0xce, 0x03, 0x60, 0x04, 0x29, 0x05, 0x32, 0x06, 0x88, 0x09, 0x16, 0x06, 0x63, 0x05, 0x8c, 0x04, 0x66, 0x03, 0xbc,
        0x03, 0x1b, 0x02, 0xc2, 0x02, 0x79, 0x02, 0x41, 0x02, 0x69, 0x02, 0xde, 0x03, 0x52, 0x03, 0xdf, 0x04, 0xc9, 0x05, 0xc8,
        0x06, 0xfd, 0x09, 0x46, 0x06, 0x88, 0x05, 0xf8, 0x05, 0x2a, 0x04, 0x42, 0x03, 0xb0, 0x03, 0x4b, 0x02, 0xf3, 0x02, 0xcf,
        0x02, 0xc5, 0x03, 0x46, 0x03, 0xdf, 0x04, 0x6d, 0x05, 0x46, 0x06, 0x54, 0x07, 0x69, 0x09, 0xe9, 0x06, 0x9d, 0x05, 0xe7,
        0x06, 0x75, 0x04, 0x68, 0x04, 0x10, 0x03, 0x5c, 0x03, 0x0f, 0x02, 0xeb, 0x02, 0xf6, 0x03, 0x7d, 0x04, 0x0e, 0x04, 0xa7,
        0x05, 0xc7, 0x06, 0x72, 0x07, 0x84, 0x0a, 0x0d

};

I2C_ARRAY TriggerStartTbl[] = {
//{0x3002,0x00},//Master mode start
};

I2C_ARRAY PatternTbl[] = {
//{0x308c,0x20}, //colorbar pattern , bit 0 to enable
};

I2C_ARRAY Current_Mirror_Flip_Tbl[] = {
//{0x3007, 0x00},//M0F0

};

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


I2C_ARRAY mirr_flip_table[] =
{
};

typedef struct {
    short reg;
    char startbit;
    char stopbit;
} COLLECT_REG_SET;



static I2C_ARRAY gain_reg[] = {
    {0x00B1, 0x7F},      // AG = 128 / (0x00B1 + 1) = 0x0C~0x7F
    {0x00BC, 0x02},
    {0x00BD, 0x00},      // DG = (0xBC * 256+0xBD) / 512
};

static I2C_ARRAY frame_drop_reg[] = {
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
    {0x000C, 0x01},
    {0x000D, 0x10},
};

I2C_ARRAY vts_reg[] = {
    {0x0008, 0x04},
    {0x0009, 0x40},               //1088
};

I2C_ARRAY dummy_line[] = {
    {0x0021, 0x00},
    {0x0022, 0x25},               //1088
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

/////////// function definition ///////////////////


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
    sensor_if->MCLK(SENSOR_PAD_GROUP_SET, 1, handle->mclk);//sensor_if->MCLK(handle,1, handle->mclk);

    if(SENSOR_PAD_GROUP_SET == CUS_SENSOR_PAD_GROUP_A) {
        sensor_if->SetIOPad(SENSOR_PAD_GROUP_SET, CUS_SENIF_BUS_MIPI, CUS_SR0_MIPI_MODE_2 );
    }
    else {
        sensor_if->SetIOPad(SENSOR_PAD_GROUP_SET, CUS_SENIF_BUS_MIPI, CUS_SR1_MIPI_MODE_1); //CUS_SR1_MIPI_MODE_1:for 1Lane, CUS_SR1_MIPI_MODE_2:for 2Lane
    }

    //Set_csi_if(1, 0);
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_216M, handle->PCLK_POLARITY);//sensor_if->SetCSI_Clk(handle,CUS_CSI_CLK_144M);
#if (SENSOR_MIPI_LANE_NUM == 1)
    sensor_if->SetCSI_Lane(SENSOR_PAD_GROUP_SET, 1, 1);
#endif
    //Set_csi_lane(lane_number,vc0_hs_mode,long_packet_type_enable); //for 1 or 2 lane
    //sensor_if->SetCSI_Lane(handle,2);
    //sensor_if->SetCSI_VC0HSmode(handle,PACKET_FOOTER_EDGE);
    //sensor_if->SetCSI_LongPacketType(handle,CSI_LONG_PACKET_TYPE_RAW12|CSI_LONG_PACKET_TYPE_RAW10);
    ISP_config_io(handle);
    SENSOR_DMSG("[%s] reset low\n", __FUNCTION__);
    sensor_if->Reset(SENSOR_PAD_GROUP_SET, handle->reset_POLARITY );//sensor_if->Reset(handle, 1,handle->reset_POLARITY);
    MsSleep(RTK_MS_TO_TICK(10));//usleep(500);
    SENSOR_DMSG("[%s] power low\n", __FUNCTION__);
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, handle->pwdn_POLARITY );//sensor_if->PowerOff(handle, 1, handle->pwdn_POLARITY);
    MsSleep(RTK_MS_TO_TICK(10));//usleep(500);

    // power -> high, reset -> high
    SENSOR_DMSG("[%s] power high\n", __FUNCTION__);
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, !handle->pwdn_POLARITY );//sensor_if->PowerOff(handle, 1, !handle->pwdn_POLARITY);
    MsSleep(RTK_MS_TO_TICK(10));//usleep(500);
    SENSOR_DMSG("[%s] reset high\n", __FUNCTION__);
    sensor_if->Reset(SENSOR_PAD_GROUP_SET, !handle->reset_POLARITY );//sensor_if->Reset(handle, 1, !handle->reset_POLARITY);
    MsSleep(RTK_MS_TO_TICK(10));//usleep(500);

    //sensor_if->Set3ATaskOrder(handle, def_order);
    // pure power on
    //ISP_config_io(handle);
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, !handle->pwdn_POLARITY );//sensor_if->PowerOff(handle, 1, !handle->pwdn_POLARITY);
	sensor_if->SWReset(handle->channel_num, FALSE);
	MsSleep(RTK_MS_TO_TICK(10));//usleep(5000);
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
	sensor_if->PowerOff( 1, handle->pwdn_POLARITY );//sensor_if->PowerOff(handle, 1, handle->pwdn_POLARITY);
    //handle->i2c_bus->i2c_close(handle->i2c_bus);
    MsSleep(RTK_MS_TO_TICK(50));//usleep(1000);
    //Set_csi_if(0, 0);
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_DISABLE, handle->PCLK_POLARITY);
    sensor_if->MCLK(0, 0, handle->mclk );
#if (SENSOR_MIPI_LANE_NUM == 1)
    sensor_if->SetCSI_Lane(SENSOR_PAD_GROUP_SET, 1, 0);
#endif

    return SUCCESS;
}

/////////////////// image function /////////////////////////
//Get and check sensor ID
//if i2c error or sensor id does not match then return FAIL
static int pCus_GetSensorID(ms_cus_sensor *handle, u32 *id)
{
    int i,n;
    int table_length= ARRAY_SIZE(Sensor_id_table);
    unsigned short pid,pid_6bit,T,Y,U,I;
    I2C_ARRAY id_from_sensor[ARRAY_SIZE(Sensor_id_table)];

    for(n=0;n<table_length;++n)
    {
      id_from_sensor[n].reg = Sensor_id_table[n].reg;
      id_from_sensor[n].data = 0;
    }

    *id =0;
    if(table_length>8) table_length=8;

    SENSOR_DMSG("\n\n[%s]", __FUNCTION__);

    for(n=0;n<4;++n) //retry , until I2C success
    {
      if(n>2) return FAIL;

      if( SensorRegArrayR((I2C_ARRAY*)id_from_sensor,table_length) == SUCCESS) //read sensor ID from I2C
          break;
      else
          usleep(1*1000);
    }

    //convert sensor id to u32 format
    for(i=0;i<table_length;++i)
    {
      if( id_from_sensor[i].data != Sensor_id_table[i].data )
        return FAIL;
      *id = id_from_sensor[i].data;
    }


    SensorReg_Read(0x0045, &pid);
    //printc("pid===0x%02x\r\n",pid);

    pid_6bit = pid & 0x3f;
    if (pid == 0x4b || pid_6bit == BG0806B1 || pid_6bit == BG0806B2) {
        SensorReg_Write(0x0390,0x00);
        return FAIL;
    }

    switch(pid_6bit){
        case BG0806A:
            SensorReg_Write(0x0206,0x02);
            SensorReg_Write(0x0207,0xc8);
            SensorReg_Write(0x0132,0x01);
            SensorReg_Write(0x0133,0x38);
            break;
        case BG0806C1:
        case BG0806C2:
            SensorReg_Write(0x0206,0x02);
            SensorReg_Write(0x0207,0xaa);
            SensorReg_Write(0x0132,0x01);
            SensorReg_Write(0x0133,0x56) ;
            break;
        case BG0806B1:
        case BG0806B2:
        default:
            SensorReg_Write(0x0206,0x02);
            SensorReg_Write(0x0207,0xde);
            SensorReg_Write(0x0132,0x01);
            SensorReg_Write(0x0133,0x22);
            break;
      }

        SensorReg_Write(0x001d,0x02);
    // ONLY READ
    //SensorReg_Read(0x0206,&T);
    //SensorReg_Read(0x0207,&Y);
    //SensorReg_Read(0x0132,&U);
    //SensorReg_Read(0x0133,&I);
    //printc("0x0206===0x%02x\r\n",T);
    //printc("0x0207===0x%02x\r\n",Y);
    //printc("0x0132===0x%02x\r\n",U);
    //printc("0x0133===0x%02x\r\n",I);


    SENSOR_DMSG("[%s]BG0806 sensor ,Read sensor id, get 0x%x Success\n", __FUNCTION__, (int)*id);

    return SUCCESS;
}

static int bg0806_SetPatternMode(ms_cus_sensor *handle,u32 mode)
{
#if (__SENSOR_W)

    int i;
  switch(mode)
  {
  case 1:
    PatternTbl[0].data = 0x21; //enable
  break;
  case 0:
    PatternTbl[0].data &= 0xFE; //disable
  break;
  default:
    PatternTbl[0].data &= 0xFE; //disable
  break;
  }

  for(i=0;i< ARRAY_SIZE(PatternTbl);i++)
  {
    if(SensorReg_Write(PatternTbl[i].reg,PatternTbl[i].data) != SUCCESS)
    {
      //MSG("[%s:%d]Sensor init fail!!\n", __FUNCTION__, __LINE__);
      return FAIL;
    }
  }
#endif

  return SUCCESS;
}

#if 1//defined(__MV5_FPGA__)
static int pCus_I2CWrite(ms_cus_sensor *handle, unsigned short usreg, unsigned short usval)
{
    //unsigned short sen_data;

    SensorReg_Write(usreg, usval);
    //SensorReg_Read(usreg, &sen_data);
    //UartSendTrace("bg0806_MIPI reg: 0x%x, data: 0x%x, read: 0x%x.\n", usreg, usval, sen_data);

    return SUCCESS;
}

static int pCus_I2CRead(ms_cus_sensor *handle, unsigned short usreg, unsigned short* pusval)
{
    unsigned short usread_data;

    SensorReg_Read(usreg, &usread_data);
    *pusval = usread_data;
    UartSendTrace("bg0806_MIPI reg: 0x%x, data: 0x%x\n", usreg, usread_data);

    return SUCCESS;
}
#endif

static int pCus_init_mipi1lane_linear(ms_cus_sensor *handle)
{
    SENSOR_DMSG("\n\n[%s]", __FUNCTION__);
    int i,n,cnt=0;
    ISensorIfAPI *sensor_if = &(handle->sensor_if_api);
    short sen_data;
    sensor_if->PCLK( CUS_SNR_PCLK_MIPI_TOP );//sensor_if->PCLK(NULL,CUS_PCLK_MIPI_TOP);

    UartSendTrace("BG0806 Sensor_init_table_1lane\n");
    for(i=0;i< ARRAY_SIZE(Sensor_init_table_1lane);i++)
    {
        if(Sensor_init_table_1lane[i].reg==0xffff)
        {
            MsSleep(RTK_MS_TO_TICK(1));//usleep(1000*Sensor_init_table_1lane[i].data);
        }
        else
        {
            cnt = 0;
            while(SensorReg_Write(Sensor_init_table_1lane[i].reg,Sensor_init_table_1lane[i].data) != SUCCESS)
            {
                cnt++;
                //printf("Sensor_init_table_1lane -> Retry %d...\n",cnt);
                if(cnt>=10)
                {
                    //printf("[%s:%d]Sensor init fail!!\n", __FUNCTION__, __LINE__);
                    return FAIL;
                }
                //usleep(10*1000);
            }
//            SensorReg_Read( Sensor_init_table_1lane[i].reg, &sen_data );
//            UartSendTrace("BG0806 reg: 0x%x, data: 0x%x, read: 0x%x.\n",Sensor_init_table_1lane[i].reg, Sensor_init_table_1lane[i].data, sen_data);
        }
    }

    for(n=0;n<768;++n)
    {
        SensorReg_Write(DSC_ADDR_BASE+n, Tab_sensor_dsc[n]);
    }

    SensorReg_Write(0x001d, 0x02);

#if 0
//debug hxb20180418
    for(i=0;i< ARRAY_SIZE(Sensor_init_table_1lane);i++)
    {
        SensorReg_Read( Sensor_init_table_1lane[i].reg, &sen_data );
        if (sen_data != Sensor_init_table_1lane[i].data) {
            UartSendTrace("BG0806 reg write error: 0x%x, data: 0x%x, read: 0x%x.\n",Sensor_init_table_1lane[i].reg, Sensor_init_table_1lane[i].data, sen_data);
        }
    }
    for(i=0;i<768;++i)
    {
        SensorReg_Read(DSC_ADDR_BASE+i,  &sen_data);
        if (sen_data != Tab_sensor_dsc[i]) {
            UartSendTrace("BG0806 reg write error: 0x%x, data: 0x%x, read: 0x%x.\n",DSC_ADDR_BASE+i, Tab_sensor_dsc[i], sen_data);
        }
    }

    short pid_6bit;
    unsigned char value_206,value_207,value_132,value_133;
    SensorReg_Read(0x0045, &pid_6bit);
    pid_6bit = pid_6bit & 0x3f;

    switch(pid_6bit){
        case BG0806A:
            value_206 = 0x02;
            value_207 = 0xc8;
            value_132 = 0x01;
            value_133 = 0x38;
            break;
        case BG0806C1:
        case BG0806C2:
            value_206 = 0x02;
            value_207 = 0xaa;
            value_132 = 0x01;
            value_133 = 0x56;
            break;
        case BG0806B1:
        case BG0806B2:
        default:
            value_206 = 0x02;
            value_207 = 0xde;
            value_132 = 0x01;
            value_133 = 0x22;
            break;
      }

    SensorReg_Read(0x206,  &sen_data);
    if (sen_data != value_206) {
        UartSendTrace("BG0806 reg write error: 0x%x, data: 0x%x, read: 0x%x.\n",0x206, value_206, sen_data);
    }
    SensorReg_Read(0x207,  &sen_data);
    if (sen_data != value_207) {
        UartSendTrace("BG0806 reg write error: 0x%x, data: 0x%x, read: 0x%x.\n",0x207, value_207, sen_data);
    }
    SensorReg_Read(0x132,  &sen_data);
    if (sen_data != value_132) {
        UartSendTrace("BG0806 reg write error: 0x%x, data: 0x%x, read: 0x%x.\n",0x132, value_132, sen_data);
    }
    SensorReg_Read(0x133,  &sen_data);
    if (sen_data != value_133) {
        UartSendTrace("BG0806 reg write error: 0x%x, data: 0x%x, read: 0x%x.\n",0x133, value_133, sen_data);
    }
#endif
    pCus_SetOrien(handle,handle->orient);
    return SUCCESS;
}

/*
int pCus_release(ms_cus_sensor *handle)
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    sensor_if->PCLK(NULL,CUS_PCLK_OFF);
    return SUCCESS;
}
*/

static int pCus_GetVideoResNum( ms_cus_sensor *handle, u32 *ulres_num)
{
    *ulres_num = handle->video_res_supported.num_res;
    return SUCCESS;
}

static int pCus_GetVideoRes(ms_cus_sensor *handle, cus_camsensor_res **res)
{
    //return current resolution
    *res = &handle->video_res_supported.res[handle->video_res_supported.ulcur_res];
    return SUCCESS;
}

static int pCus_SetVideoRes(ms_cus_sensor *handle, u32 res)
{
    handle->video_res_supported.ulcur_res = 0; //TBD

    return SUCCESS;
}

static int pCus_GetOrien(ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT *orit)
{
#if (__SENSOR_W)
    short sen_data;

    SensorReg_Read(0x3007, &sen_data);//always success now

    LOGD("mirror:%x\r\n", sen_data & 0x03);
    switch(sen_data & 0x03)
    {
        case 0x00:
            *orit = CUS_ORIT_M0F0;
        break;
        case 0x02:
            *orit = CUS_ORIT_M1F0;
        break;
        case 0x01:
            *orit = CUS_ORIT_M0F1;
        break;
        case 0x03:
            *orit = CUS_ORIT_M1F1;
        break;
    }
#endif

    return SUCCESS;
}

static int pCus_SetOrien(ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT orit) {
#if (__SENSOR_W)
    int table_length = ARRAY_SIZE(mirr_flip_table);
    int seg_length=table_length/4;
    int i,j;

    SENSOR_DMSG("\n\n[%s]", __FUNCTION__);

    switch(orit)
    {
        case CUS_ORIT_M0F0:
            for(i=0,j=0;i<seg_length;i++,j++){
                SensorReg_Write(mirr_flip_table[i].reg,mirr_flip_table[i].data);
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }
           //  handle->bayer_id=    CUS_BAYER_BG;
            break;

        case CUS_ORIT_M1F0:
            for(i=seg_length,j=0;i<seg_length*2;i++,j++){
                SensorReg_Write(mirr_flip_table[i].reg,mirr_flip_table[i].data);
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }
        //  handle->bayer_id=   CUS_BAYER_BG;
            break;

        case CUS_ORIT_M0F1:
            for(i=seg_length*2,j=0;i<seg_length*3;i++,j++){
                SensorReg_Write(mirr_flip_table[i].reg,mirr_flip_table[i].data);
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }
         // handle->bayer_id=   CUS_BAYER_GR;
            break;

        case CUS_ORIT_M1F1:
            for(i=seg_length*3,j=0;i<seg_length*4;i++,j++){
                SensorReg_Write(mirr_flip_table[i].reg,mirr_flip_table[i].data);
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }
         // handle->bayer_id=   CUS_BAYER_GR;
            break;

        default :
            for(i=0,j=0;i<seg_length;i++,j++){
                SensorReg_Write(mirr_flip_table[i].reg,mirr_flip_table[i].data);
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }
        //  handle->bayer_id=   CUS_BAYER_BG;
            break;
    }
#endif

    return SUCCESS;
}

static int pCus_GetFPS(ms_cus_sensor *handle)
{
    bg0806_params *params = (bg0806_params *)handle->private_data;
    //SENSOR_DMSG("[%s]", __FUNCTION__);

    return  params->expo.fps;
}
static int pCus_SetFPS(ms_cus_sensor *handle, u32 fps)
{
    bg0806_params *params = (bg0806_params *)handle->private_data;
    SENSOR_DMSG("\n\n[%s]", __FUNCTION__);
    printc(FG_YELLOW("\r\n0806_fps=%d\r\n"),fps);
    /*if(fps>=3 && fps <= 30){
      fps = fps>29?29:fps;//limit fps at 29 fps due to MCLK=36MHz
      params->expo.fps = fps;
      params->expo.vts=  (vts_30fps*29)/fps;
      vts_reg[0].data = (params->expo.vts>> 16) & 0x0003;
      vts_reg[1].data = (params->expo.vts >> 8) & 0x00ff;
      vts_reg[2].data = (params->expo.vts >> 0) & 0x00ff;
      params->reg_dirty = true;
      return SUCCESS;
    }else if(fps>=3000 && fps <= 30000){
        fps = fps>29091?29091:fps;//limit fps at 29.091 fps due to MCLK=36MHz
        params->expo.fps = fps;
        params->expo.vts=  (vts_30fps*29091)/fps;
        vts_reg[0].data = (params->expo.vts>> 16) & 0x0003;
        vts_reg[1].data = (params->expo.vts >> 8) & 0x00ff;
        vts_reg[2].data = (params->expo.vts >> 0) & 0x00ff;
        params->reg_dirty = true;
        return SUCCESS;
    }else{
      //params->expo.vts=vts_30fps;
      //params->expo.fps=30;
      SENSOR_DMSG("[%s] FPS %d out of range.\n",__FUNCTION__,fps);
      return FAIL;
    }*/
}
static int pCus_GetSensorCap(ms_cus_sensor *handle, CUS_CAMSENSOR_CAP *cap)
{
    if (cap)
        memcpy(cap, &sensor_cap, sizeof(CUS_CAMSENSOR_CAP));
    else     return FAIL;
    return SUCCESS;
}


///////////////////////////////////////////////////////////////////////
// auto exposure
///////////////////////////////////////////////////////////////////////
// unit: micro seconds
//AE status notification
static int pCus_AEStatusNotify(ms_cus_sensor *handle, CUS_CAMSENSOR_AE_STATUS_NOTIFY status)
{
    bg0806_params *params = (bg0806_params *)handle->private_data;
    //ISensorIfAPI2 *sensor_if1 = handle->sensor_if_api2;
    switch(status)
    {
        case CUS_FRAME_INACTIVE:
             //SensorReg_Write(0x3001,0);
             break;
        case CUS_FRAME_ACTIVE:
            if(params->reg_dirty)
            {
/*
                if(params->change){

                    // sensor_if1->SetSkipFrame(handle,3);
                     params->change = false;

                    }
*/
                //SensorReg_Write(0x3001,1);
            SensorRegArrayW((I2C_ARRAY*)expo_reg, ARRAY_SIZE(expo_reg));
            SensorRegArrayW((I2C_ARRAY*)dummy_line, ARRAY_SIZE(dummy_line));
            SensorRegArrayW((I2C_ARRAY*)gain_reg, ARRAY_SIZE(gain_reg));
             //   SensorRegArrayW((I2C_ARRAY*)vts_reg, ARRAY_SIZE(vts_reg));
                SensorReg_Write(0x001d,2);  //
               // printf("0x3009=0x%x,0x3014=0x%x,0x3016=0x%x,0x3020=0x%x,0x3021=0x%x\n", gain_reg[1].data,gain_reg[0].data,gain_reg[2].data,expo_reg[2].data,expo_reg[1].data);
                params->reg_dirty = false;

            //printc( "[%s] Peter SensorRegArrayW\n", __FUNCTION__);
            }
            break;
        default :
             break;
    }
    return SUCCESS;
}

static int pCus_GetAEUSecs(ms_cus_sensor *handle, u32 *us)
{
    //int rc;
    u32 lines = 0;
    //int rc = SensorRegArrayR((I2C_ARRAY*)expo_reg, ARRAY_SIZE(expo_reg));


    lines |= (u32)(expo_reg[0].data&0xff)<<8;
    lines |= (u32)(expo_reg[1].data&0xff)<<0;
   // lines >>= 4;
   // *us = (lines+dummy) * params->expo.us_per_line;
    //*us = lines;//(lines*Preview_line_period);
    *us = (lines*Preview_line_period)/1000;
    SENSOR_DMSG("[%s] sensor expo lines/us %ld,%ld us\n", __FUNCTION__, __LINE__, *us);
    //printc("[%s] Peter sensor expo lines/us %ld,%ld us\n", __FUNCTION__, lines, *us);
    //return rc;

    return SUCCESS;
}

static int pCus_SetAEUSecs(ms_cus_sensor *handle, u32 us)
{
#if (__SENSOR_W)
    u32 lines = 0, vts = 0;
    //u32 blank = 0;
    bg0806_params *params = (bg0806_params *)handle->private_data;

    //return SUCCESS; //TBD

    // us = 1000000/30;
    //lines = us/Preview_line_period;
    lines = (1000*us)/Preview_line_period;
    vts=params->expo.vts;

    if(lines < 1 ) lines = 1;
    if(lines > vts - 1){
        vts   = lines;
        lines = vts - 1;
    }


    blank = vts - 1088 - 8;  //blank = vts - vsize - 8

   // lines=us/Preview_line_period;
    SENSOR_DMSG("[%s] us %ld, lines %ld, vts %ld\n", __FUNCTION__,
                us,
                lines,
                blank
                );



    expo_reg[0].data = (lines>>8) & 0x00ff;
    expo_reg[1].data = (lines>>0) & 0x00ff;


    dummy_line[0].data = (blank >> 8) & 0x00ff;
    dummy_line[1].data = (blank >> 0) & 0x00ff;

    //SensorRegArrayW((I2C_ARRAY*)expo_reg, ARRAY_SIZE(expo_reg));
    //SensorRegArrayW((I2C_ARRAY*)vts_reg, ARRAY_SIZE(dummy_line));
    params->reg_dirty = true;
#endif
    //printc( "[%s] Peter expo_reg_H/expo_reg_L/dummy_line_H/dummy_line_L = 0x%x/0x%x/0x%x/0x%x\n", __FUNCTION__, expo_reg[0].data, expo_reg[1].data, dummy_line[0].data, dummy_line[1].data );

    return SUCCESS;
}

// Gain: 1x = 1024
static int pCus_GetAEGain(ms_cus_sensor *handle, u32* gain)
{
    u32 again, dgain;

    dgain = ( gain_reg[1].data * 256 +  gain_reg[2].data);
    again = ( u32 ) ( 128 * 1024  / (gain_reg[0].data + 1) );
    *gain = again * dgain / 512;

    SENSOR_DMSG( "[%s] again(base1024)/dgain(base512)/gain(base1024) = 0x%x/0x%x/0x%x\n", __FUNCTION__, again, dgain, *gain );
    //printc( "[%s] Peter again(base1024)/dgain(base512)/gain(base1024) = 0x%x/0x%x/0x%x\n", __FUNCTION__, again, dgain, *gain );
    return SUCCESS;
}

#define AE_GAINBASE 1024

static int pCus_SetAEGain_cal(ms_cus_sensor *handle, u32 gain)
{
    return SUCCESS;
}

static int pCus_SetAEGain(ms_cus_sensor *handle, u32 gain)
{
#if (__SENSOR_W)
    //extern DBG_ITEM Dbg_Items[DBG_TAG_MAX];
    bg0806_params *params = (bg0806_params *)handle->private_data;

    u32 vref1 = 0x7f;
    u32 dig_gain = 512;
    u32 sensor_again = AE_GAINBASE;

    if(gain<SENSOR_MIN_GAIN)
       gain=SENSOR_MIN_GAIN;
    else if(gain>=SENSOR_MAX_GAIN)
        gain=SENSOR_MAX_GAIN;
    //else if(gain>=78*1024)
    //   gain=78*1024;

    //if(gain > 8192) gain=8192;

    vref1 = (128 * AE_GAINBASE + gain - 1) / gain - 1;

    //if(vref1 < 0x0C) vref1 = 0x0C; //9,8x
    if(vref1 < 0x0F) vref1 = 0x0F;   //8x
    if(vref1 > 0x7F) vref1 = 0x7F;

    //vref1 = 0x7F;


    sensor_again = 128 * AE_GAINBASE / (vref1 +1);
    dig_gain = gain * 512 / sensor_again;  //replace by ISP Dgain

//  *ISPDgain = gain * (*ISPDgain) / sensor_again;

    gain_reg[0].data = ( u16 ) ( vref1 );                     //A gain
    gain_reg[1].data = ( u16 ) ( dig_gain >> 8 );             //DG high byte
    gain_reg[2].data = ( u16 ) ( dig_gain & 0xff );           //DG low byte

    SENSOR_DMSG("[%s] set gain/vref1/digH/digL = %ld/0x%x/0x%x/0x%x\n", __FUNCTION__, gain,gain_reg[0].data,gain_reg[1].data,gain_reg[2].data);
    //printc("[%s] Peter set gain/vref1/digH/digL = %ld/0x%x/0x%x/0x%x\n", __FUNCTION__, gain,gain_reg[0].data,gain_reg[1].data,gain_reg[2].data);

    //UartSendTrace("@@@@[%s] Peter set gain = %ld, 0x%x / 0x%x\n", __FUNCTION__,gain, sensor_again, *ISPDgain);

    params->reg_dirty = true;
#endif
    SensorReg_Write(0x001D, 0x02);

    if(vref1 == 0x0F){
        SensorReg_Write(0x0030, 0x01);
        SensorReg_Write(0x0031, 0xb0);
        SensorReg_Write(0x0034, 0x01);
        SensorReg_Write(0x0035, 0xb0);
        SensorReg_Write(0x004d, 0x03);
        SensorReg_Write(0x004f, 0x0c);
        SensorReg_Write(0x0061, 0x02);
        SensorReg_Write(0x0067, 0x00);
        SensorReg_Write(0x0068, 0x80);
    }else{
        SensorReg_Write(0x0030, 0x00);
        SensorReg_Write(0x0031, 0xc0);
        SensorReg_Write(0x0034, 0x00);
        SensorReg_Write(0x0035, 0xc0);
        SensorReg_Write(0x004d, 0x00);
        SensorReg_Write(0x004f, 0x09);
        SensorReg_Write(0x0061, 0x04);
        SensorReg_Write(0x0067, 0x01);
        SensorReg_Write(0x0068, 0x90);
    }

    if(vref1 == 0x0F) {
        if (blank > 0x106) {
            SensorReg_Write(0x0082, 0x04);
            SensorReg_Write(0x007f, 0x01);
            SensorReg_Write(0x0052, 0x07);
            SensorReg_Write(0x00f2, 0x07);
            SensorReg_Write(0x00fb, 0x02);
        } else {
            SensorReg_Write(0x0082, 0x08);
            SensorReg_Write(0x007f, 0x01);
            SensorReg_Write(0x0052, 0x06);
            SensorReg_Write(0x00f2, 0x06);
            SensorReg_Write(0x00fb, 0x01);
        }
    }else{
        SensorReg_Write(0x0082, 0x0b);
        SensorReg_Write(0x007f, 0x01);
        SensorReg_Write(0x0052, 0x06);
        SensorReg_Write(0x00f2, 0x06);
        SensorReg_Write(0x00fb, 0x01);
    }

    return SUCCESS;
    //return CusHW_i2c_array_tx(handle, handle->i2c_cfg, gain_reg, sizeof(gain_reg)/sizeof(CUS_I2C_ARRAY));
   // return SensorRegArrayW((I2C_ARRAY*)gain_reg, sizeof(gain_reg)/sizeof(I2C_ARRAY));
}

static int pCus_GetAEMinMaxUSecs(ms_cus_sensor *handle, u32 *min, u32 *max)
{
    *min = 150;
    *max = 33332; // <- max shutter (30fps: 33332, 60fps:16666)
    return SUCCESS;
}

static int pCus_GetAEMinMaxGain(ms_cus_sensor *handle, u32 *min, u32 *max)
{
    *min = SENSOR_MIN_GAIN;
    *max = SENSOR_MAX_GAIN;//3980*1024;
    return SUCCESS;
}

static int pCus_GetDGainRemainder(ms_cus_sensor *handle, u32 *dgain_remainder)
{
    *dgain_remainder = handle->dgain_remainder;

    return SUCCESS;
}

static int BG0806_GetShutterInfo(struct __ms_cus_sensor* handle,CUS_SHUTTER_INFO *info)
{
    info->max = 1000000000/Preview_MIN_FPS;
    info->min = (Preview_line_period * 1);
    info->step = Preview_line_period;
    return SUCCESS;
}

static int pCus_setCaliData_gain_linearity(ms_cus_sensor* handle, CUS_GAIN_GAP_ARRAY* pArray, u32 num) {
    u32 i, j;

    for(i=0,j=0;i< num ;i++,j+=2){
        gain_gap_compensate[i].gain=pArray[i].gain;
        gain_gap_compensate[i].offset=pArray[i].offset;
    }

    LOGD("[%s]%d, %d, %d, %d\n", __FUNCTION__, num, pArray[0].gain, pArray[1].gain, pArray[num-1].offset);

    return SUCCESS;
}

int cus_camsensor_init_handle(ms_cus_sensor* drv_handle)
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
    //private data allocation & init
#if defined(__RTK_OS__)
    sprintf(str, "BG0806linear");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(bg0806_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (bg0806_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(bg0806_params));
#else
    handle->private_data = calloc(1, sizeof(bg0806_params));
#endif

    bg0806_params *params = (bg0806_params *)handle->private_data;

    ////////////////////////////////////
    //    sensor model ID                           //
    ////////////////////////////////////
    sprintf(handle->model_id,"BG0806_MIPI");

    ////////////////////////////////////
    //    sensor interface info       //
    ////////////////////////////////////
    //SENSOR_DMSG("[%s] entering function with id %d\n", __FUNCTION__, id);
    handle->isp_type    = SENSOR_ISP_TYPE;  //ISP_SOC;
    //handle->data_fmt    = SENSOR_DATAFMT;   //CUS_DATAFMT_YUV;
    handle->sif_bus     = SENSOR_IFBUS_TYPE;//CUS_SENIF_BUS_PARL;
    handle->data_prec   = SENSOR_DATAPREC;  //CUS_DATAPRECISION_8;
    handle->data_mode   = SENSOR_DATAMODE;
    handle->bayer_id    = SENSOR_BAYERID;   //CUS_BAYER_GB;
    handle->orient      = SENSOR_ORIT;      //CUS_ORIT_M1F1;
    //handle->YC_ODER     = SENSOR_YCORDER;   //CUS_SEN_YCODR_CY;
    handle->interface_attr.attr_mipi.mipi_lane_num = SENSOR_MIPI_LANE_NUM;
    handle->interface_attr.attr_mipi.mipi_data_format = CUS_SEN_INPUT_FORMAT_RGB; // RGB pattern.
    handle->interface_attr.attr_mipi.mipi_yuv_order = 0; //don't care in RGB pattern.
    handle->interface_attr.attr_mipi.mipi_hsync_mode = SENSOR_MIPI_HSYNC_MODE;
    handle->interface_attr.attr_mipi.mipi_sampling_delay = SENSOR_MIPI_DELAY;
    handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_NONE;
    handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 1; //Short frame

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
    handle->video_res_supported.res[0].nOutputWidth = 1928;//Preview_WIDTH;
    handle->video_res_supported.res[0].nOutputHeight = 1088;//DOL HDR //Preview_HEIGHT;

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
    //handle->VSYNC_POLARITY              = SENSOR_VSYNC_POL; //CUS_CLK_POL_POS;
    //handle->HSYNC_POLARITY              = SENSOR_HSYNC_POL; //CUS_CLK_POL_POS;
    handle->PCLK_POLARITY               = SENSOR_PCLK_POL;  //CUS_CLK_POL_POS);    // use '!' to clear board latch error
    /////////////////////////////////////////////////////



    ////////////////////////////////////////////////////
    // AE parameters
    ////////////////////////////////////////////////////
    handle->ae_gain_delay       = SENSOR_GAIN_DELAY_FRAME_COUNT;//0;//1;
    handle->ae_shutter_delay    = SENSOR_SHUTTER_DELAY_FRAME_COUNT;//1;//2;

    ///calibration
    handle->sat_mingain = SENSOR_MIN_GAIN;//g_sensor_ae_min_gain;
    handle->dgain_remainder = 0;

    //LOGD("[%s:%d]\n", __FUNCTION__, __LINE__);
    handle->pCus_sensor_release     = cus_camsensor_release_handle;
#if (SENSOR_MIPI_LANE_NUM == 1)
    handle->pCus_sensor_init        = pCus_init_mipi1lane_linear    ;
#endif
    //Set_csi_if(true, SENSOR_MIPI_DELAY);//?????
    //handle->pCus_sensor_powerupseq  = pCus_powerupseq   ;
    handle->pCus_sensor_poweron     = pCus_poweron ;
    handle->pCus_sensor_poweroff    = pCus_poweroff;

    // Normal
    handle->pCus_sensor_GetSensorID       = pCus_GetSensorID   ;
    //handle->pCus_sensor_GetStillResCap    = pCus_GetStillResCap;
    //handle->pCus_sensor_GetStillRes       = pCus_GetStillRes   ;
    //handle->pCus_sensor_SetStillRes       = pCus_SetStillRes   ;
    //handle->pCus_sensor_GetVideoResCap    = pCus_GetVideoResCap;
    handle->pCus_sensor_GetVideoResNum = pCus_GetVideoResNum;
    handle->pCus_sensor_GetVideoRes       = pCus_GetVideoRes   ;
    handle->pCus_sensor_SetVideoRes       = pCus_SetVideoRes   ;
    handle->pCus_sensor_GetOrien          = pCus_GetOrien      ;
    handle->pCus_sensor_SetOrien          = pCus_SetOrien      ;
    handle->pCus_sensor_GetFPS          = pCus_GetFPS      ;
    handle->pCus_sensor_SetFPS          = pCus_SetFPS      ;
    handle->pCus_sensor_GetSensorCap    = pCus_GetSensorCap;
    handle->pCus_sensor_SetPatternMode = bg0806_SetPatternMode;
    ///////////////////////////////////////////////////////
    // AE
    ///////////////////////////////////////////////////////
    // unit: micro seconds
    //handle->pCus_sensor_GetAETrigger_mode      = pCus_GetAETrigger_mode;
    //handle->pCus_sensor_SetAETrigger_mode      = pCus_SetAETrigger_mode;
    handle->pCus_sensor_AEStatusNotify = pCus_AEStatusNotify;
    handle->pCus_sensor_GetAEUSecs      = pCus_GetAEUSecs;
    handle->pCus_sensor_SetAEUSecs      = pCus_SetAEUSecs;
    handle->pCus_sensor_GetAEGain       = pCus_GetAEGain;
    //handle->pCus_sensor_SetAEGain       = pCus_SetAEGain;
    handle->pCus_sensor_SetAEGain       = pCus_SetAEGain;

    handle->pCus_sensor_GetAEMinMaxGain = pCus_GetAEMinMaxGain;
    handle->pCus_sensor_GetAEMinMaxUSecs= pCus_GetAEMinMaxUSecs;
    handle->pCus_sensor_GetDGainRemainder = pCus_GetDGainRemainder;

     //sensor calibration
    handle->pCus_sensor_SetAEGain_cal   = pCus_SetAEGain_cal;
    handle->pCus_sensor_setCaliData_gain_linearity=pCus_setCaliData_gain_linearity;
    handle->pCus_sensor_GetShutterInfo = BG0806_GetShutterInfo;
#if 1//defined(__MV5_FPGA__)
    handle->pCus_sensor_I2CWrite = pCus_I2CWrite; //Andy Liu
    handle->pCus_sensor_I2CRead = pCus_I2CRead; //Andy Liu
#endif
    params->expo.vts=vts_30fps;
    params->expo.fps = 25;
    params->reg_dirty = false;

    handle->snr_pad_group = SENSOR_PAD_GROUP_SET;

    handle->channel_num = SENSOR_CHANNEL_NUM;
    handle->channel_mode = SENSOR_CHANNEL_MODE;

    return SUCCESS;
}

static int pCus_init_mipi1lane_linear_isp_calibration( ms_cus_sensor *handle )
{
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

static int bg0806_SetPatternMode_isp_calibration( ms_cus_sensor *handle, u32 mode )
{
    return SUCCESS;
}

static int pCus_I2CWrite_isp_calibration(ms_cus_sensor *handle, unsigned short usreg, unsigned short usval)
{
    return SUCCESS;
}

static int pCus_I2CRead_isp_calibration(ms_cus_sensor *handle, unsigned short usreg)
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
    bg0806_params *params = ( bg0806_params * ) handle->private_data;
    //return params->mirror_flip.cur;
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
    *min = 1024;            //1024*1.1*2
    *max = 1024*8;

    return SUCCESS;
}

static int pCus_setCaliData_gain_linearity_isp_calibration( ms_cus_sensor* handle, CUS_GAIN_GAP_ARRAY* pArray, u32 num )
{
    return SUCCESS;
}

static int BG0806_GetShutterInfo_isp_calibration( struct __ms_cus_sensor* handle, CUS_SHUTTER_INFO *info )
{
    info->max = 1000000000 / 12;
    info->min = Preview_line_period;
    info->step = Preview_line_period;
    return SUCCESS;
}

int cus_camsensor_init_handle_linear_isp_calibration(ms_cus_sensor* drv_handle)
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
    //private data allocation & init
#if defined(__RTK_OS__)
    sprintf(str, "BG0806cali");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(bg0806_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (bg0806_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(bg0806_params));
#else
    handle->private_data = calloc(1, sizeof(bg0806_params));
#endif

    bg0806_params *params = (bg0806_params *)handle->private_data;

    ////////////////////////////////////
    //    sensor model ID                           //
    ////////////////////////////////////
    sprintf(handle->model_id,"BG0806_MIPI");

    ////////////////////////////////////
    //    sensor interface info       //
    ////////////////////////////////////
    //SENSOR_DMSG("[%s] entering function with id %d\n", __FUNCTION__, id);
    handle->isp_type    = SENSOR_ISP_TYPE;  //ISP_SOC;
    //handle->data_fmt    = SENSOR_DATAFMT;   //CUS_DATAFMT_YUV;
    handle->sif_bus     = SENSOR_IFBUS_TYPE;//CUS_SENIF_BUS_PARL;
    handle->data_prec   = SENSOR_DATAPREC;  //CUS_DATAPRECISION_8;
    handle->data_mode   = SENSOR_DATAMODE;
    handle->bayer_id    = SENSOR_BAYERID;   //CUS_BAYER_GB;
    handle->orient      = SENSOR_ORIT;      //CUS_ORIT_M1F1;
    //handle->YC_ODER     = SENSOR_YCORDER;   //CUS_SEN_YCODR_CY;
    handle->interface_attr.attr_mipi.mipi_lane_num = SENSOR_MIPI_LANE_NUM;
    handle->interface_attr.attr_mipi.mipi_data_format = CUS_SEN_INPUT_FORMAT_RGB; // RGB pattern.
    handle->interface_attr.attr_mipi.mipi_yuv_order = 0; //don't care in RGB pattern.
    handle->interface_attr.attr_mipi.mipi_hsync_mode = SENSOR_MIPI_HSYNC_MODE;
    handle->interface_attr.attr_mipi.mipi_sampling_delay = SENSOR_MIPI_DELAY;
    handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_NONE;
    handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 1; //Short frame

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
    handle->video_res_supported.res[0].nOutputWidth = 1928;//Preview_WIDTH;
    handle->video_res_supported.res[0].nOutputHeight = 1088;//DOL HDR //Preview_HEIGHT;

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
    //handle->VSYNC_POLARITY              = SENSOR_VSYNC_POL; //CUS_CLK_POL_POS;
    //handle->HSYNC_POLARITY              = SENSOR_HSYNC_POL; //CUS_CLK_POL_POS;
    handle->PCLK_POLARITY               = SENSOR_PCLK_POL;  //CUS_CLK_POL_POS);    // use '!' to clear board latch error
    /////////////////////////////////////////////////////



    ////////////////////////////////////////////////////
    // AE parameters
    ////////////////////////////////////////////////////
    handle->ae_gain_delay       = 1;//0;//1;
    handle->ae_shutter_delay    = 2;//1;//2;
    ///calibration
    handle->sat_mingain=g_sensor_ae_min_gain;

    //LOGD("[%s:%d]\n", __FUNCTION__, __LINE__);
    handle->pCus_sensor_release     = cus_camsensor_release_handle;
#if (SENSOR_MIPI_LANE_NUM == 1)
    handle->pCus_sensor_init        = pCus_init_mipi1lane_linear_isp_calibration    ;
#endif
    //Set_csi_if(true, SENSOR_MIPI_DELAY);//?????
    //handle->pCus_sensor_powerupseq  = pCus_powerupseq   ;
    handle->pCus_sensor_poweron     = pCus_poweron_isp_calibration ;
    handle->pCus_sensor_poweroff    = pCus_poweroff_isp_calibration;

    // Normal
    handle->pCus_sensor_GetSensorID       = pCus_GetSensorID_isp_calibration   ;
    //handle->pCus_sensor_GetStillResCap    = pCus_GetStillResCap;
    //handle->pCus_sensor_GetStillRes       = pCus_GetStillRes   ;
    //handle->pCus_sensor_SetStillRes       = pCus_SetStillRes   ;
    //handle->pCus_sensor_GetVideoResCap    = pCus_GetVideoResCap;
    handle->pCus_sensor_GetVideoResNum = pCus_GetVideoResNum;
    handle->pCus_sensor_GetVideoRes       = pCus_GetVideoRes_isp_calibration   ;
    handle->pCus_sensor_SetVideoRes       = pCus_SetVideoRes_isp_calibration   ;
    handle->pCus_sensor_GetOrien          = pCus_GetOrien_isp_calibration      ;
    handle->pCus_sensor_SetOrien          = pCus_SetOrien_isp_calibration      ;
    handle->pCus_sensor_GetFPS          = pCus_GetFPS_isp_calibration      ;
    handle->pCus_sensor_SetFPS          = pCus_SetFPS_isp_calibration      ;
    handle->pCus_sensor_GetSensorCap    = pCus_GetSensorCap_isp_calibration;
    handle->pCus_sensor_SetPatternMode = bg0806_SetPatternMode_isp_calibration;
    ///////////////////////////////////////////////////////
    // AE
    ///////////////////////////////////////////////////////
    // unit: micro seconds
    //handle->pCus_sensor_GetAETrigger_mode      = pCus_GetAETrigger_mode;
    //handle->pCus_sensor_SetAETrigger_mode      = pCus_SetAETrigger_mode;
    handle->pCus_sensor_AEStatusNotify = pCus_AEStatusNotify_isp_calibration;
    handle->pCus_sensor_GetAEUSecs      = pCus_GetAEUSecs_isp_calibration;
    handle->pCus_sensor_SetAEUSecs      = pCus_SetAEUSecs_isp_calibration;
    handle->pCus_sensor_GetAEGain       = pCus_GetAEGain_isp_calibration;
    //handle->pCus_sensor_SetAEGain       = pCus_SetAEGain;
    handle->pCus_sensor_SetAEGain       = pCus_SetAEGain_isp_calibration;

    handle->pCus_sensor_GetAEMinMaxGain = pCus_GetAEMinMaxGain_isp_calibration;
    handle->pCus_sensor_GetAEMinMaxUSecs= pCus_GetAEMinMaxUSecs_isp_calibration;

     //sensor calibration
    handle->pCus_sensor_SetAEGain_cal   = pCus_SetAEGain_cal_isp_calibration;
    handle->pCus_sensor_setCaliData_gain_linearity=pCus_setCaliData_gain_linearity_isp_calibration;
    handle->pCus_sensor_GetShutterInfo = BG0806_GetShutterInfo_isp_calibration;
#if 1//defined(__MV5_FPGA__)
    handle->pCus_sensor_I2CWrite = pCus_I2CWrite_isp_calibration; //Andy Liu
    handle->pCus_sensor_I2CRead = pCus_I2CRead_isp_calibration; //Andy Liu
#endif
    params->expo.vts=vts_30fps;
    params->expo.fps = 25;
    params->reg_dirty = false;

    handle->snr_pad_group = SENSOR_PAD_GROUP_SET;

    handle->channel_num = SENSOR_CHANNEL_NUM + 1;
    handle->channel_mode = CUS_SENSOR_CHANNEL_MODE_RAW_STORE_ISP_CALIBRATION;

    return SUCCESS;
}

int cus_camsensor_release_handle(ms_cus_sensor *handle)
{
#if defined(__RTK_OS__)
    CamOsRet_e                  eCamOsRet = CAM_OS_OK;
#endif

    //ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    //sensor_if->PCLK(NULL,CUS_PCLK_OFF);
    //sensor_if->SetCSI_Clk(handle,CUS_CSI_CLK_DISABLE);
    if (handle && handle->private_data) {
        LOGD("[%s] release handle, handle %x, private data %x",
                __FUNCTION__,
                (int)handle,
                (int)handle->private_data);
#if defined(__RTK_OS__)
        eCamOsRet = CamOsDirectMemRelease((void*)handle->private_data, sizeof(bg0806_params));
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
struct SensorMapTable_t gsensor_map_bg0806[] = {
    { //Channel 0
        SENSOR_CHANNEL_NUM,
        cus_camsensor_init_handle,
        cus_camsensor_release_handle
    },

#if (SENSOR_CHANNEL_BG0806_ISP_CALIBRATION_ENABLE == 1)
    { //Channel 1. ISP calibration.
        SENSOR_CHANNEL_NUM + 1,
        cus_camsensor_init_handle_linear_isp_calibration,
        cus_camsensor_release_handle
    },
#endif
};

int BG0806_Module_Init(void)
{
    cameraSensorRegister(&gsensor_map_bg0806[0]);

#if (SENSOR_CHANNEL_BG0806_ISP_CALIBRATION_ENABLE == 1)
    cameraSensorRegister(&gsensor_map_bg0806[1]);
#endif
    return 0;
}

void BG0806_Module_Exit(void)
{
    cameraSensorUnRegister(&gsensor_map_bg0806[0]);

#if (SENSOR_CHANNEL_BG0806_ISP_CALIBRATION_ENABLE == 1)
    cameraSensorUnRegister(&gsensor_map_bg0806[1]);
#endif
}

#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(BG0806_Module_Init);
//ait_module_exit(BG0806_Module_Exit);
#endif //#if defined(__RTK_OS__)

#endif //#if defined(BIND_SENSOR_BG0806) && (BIND_SENSOR_BG0806 == 1)
