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
#if (SENSOR0 == SC2363)
#define BIND_SENSOR_SC2363 (1)
#endif
#endif //#if defined(__RTK_OS__)

#if (defined(BIND_SENSOR_SC2363) && (BIND_SENSOR_SC2363 == 1) || defined(BIND_SENSOR_SC2363_2ND) && (BIND_SENSOR_SC2363_2ND == 1))
#define SENSOR_PAD_GROUP_SET		CUS_SENSOR_PAD_GROUP_A
#define SCD_SENSOR_PAD_GROUP_SET	CUS_SENSOR_PAD_GROUP_B
#define SENSOR_CHANNEL_NUM		(0)
#define SCD_SENSOR_CHANNEL_NUM		(1)
#define SENSOR_CHANNEL_MODE_LINEAR	CUS_SENSOR_CHANNEL_MODE_REALTIME_NORMAL
#define SCD_SENSOR_CHANNEL_MODE		CUS_SENSOR_CHANNEL_MODE_RAW_STORE_FETCH

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
//                                                                                                    //
//  Fill these #define value and table with correct settings                        //
//      camera can work and show preview on LCM                                 //
//                                                                                                       //
///////////////////////////////////////////////////////////////
#define RES_IDX_1920x1080_30P       (0)     // mode 4,  1920*1080 30P       // Video (16:9)
#define RES_IDX_1280x720_60P        (1)     // mode 9,  1280*720  60P       // Video (16:9)

#define SENSOR_MODEL_ID     "sc2363_MIPI"
#define SENSOR_ISP_TYPE     ISP_EXT                   //ISP_EXT, ISP_SOC
#define SENSOR_IFBUS_TYPE   CUS_SENIF_BUS_MIPI      //CFG //CUS_SENIF_BUS_PARL, CUS_SENIF_BUS_MIPI
#define SENSOR_MIPI_HSYNC_MODE PACKET_HEADER_EDGE1
#define SENSOR_MIPI_HSYNC_MODE_HDR PACKET_FOOTER_EDGE
#define SENSOR_MIPI_DELAY   0x1313                  //CFG
#define SENSOR_DATAPREC     CUS_DATAPRECISION_10    //CFG //CUS_DATAPRECISION_8, CUS_DATAPRECISION_10
#define SENSOR_DATAMODE     CUS_SEN_10TO12_9000     //CFG
#define SENSOR_BAYERID      CUS_BAYER_GB            //CFG //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
#define SCD_SENSOR_BAYERID      CUS_BAYER_RG//CUS_BAYER_GB            //CFG //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
#define SENSOR_ORIT         CUS_ORIT_M0F0           //CUS_ORIT_M0F0, CUS_ORIT_M1F0, CUS_ORIT_M0F1, CUS_ORIT_M1F1,
#define SENSOR_MAX_GAIN     (15.5*31)
#define SENSOR_MIN_GAIN      1024
#define SENSOR_GAIN_DELAY_FRAME_COUNT      (2)
#define SENSOR_SHUTTER_DELAY_FRAME_COUNT      (2)

#define Preview_MCLK_SPEED  CUS_CMU_CLK_24MHZ        //CFG //CUS_CMU_CLK_12M, CUS_CMU_CLK_16M, CUS_CMU_CLK_24M, CUS_CMU_CLK_27M
#define Preview_line_period 26667                  //
//#define Preview_Pixel_clock 86
#define Prv_Max_line_number 1950                  //maximum exposure line munber of sensor when preview
#define vts_30fps           1250//1125                   //for 30fps
#define Preview_WIDTH       1920                   //resolution Width when preview
#define Preview_HEIGHT      1080                   //resolution Height when preview
#define Preview_MAX_FPS     30                     //fastest preview FPS
#define Preview_MIN_FPS     5                      //slowest preview FPS
#define Preview_CROP_START_X     1                      //CROP_START_X
#define Preview_CROP_START_Y     1                      //CROP_START_Y

#define SENSOR_I2C_ADDR     0x60                    //I2C slave address
#define SENSOR_I2C_SPEED    I2C_SLOWSPEED_MODE_200KHZ   //200KHz
#define SENSOR_I2C_CHANNEL  1                           //I2C Channel
#define SENSOR_I2C_PAD_MODE 2                           //Pad/Mode Number
//#define SENSOR_I2C_SPEED    200000                  //I2C speed, 60000~320000

#define SENSOR_I2C_LEGACY  I2C_NORMAL_MODE     //usally set CUS_I2C_NORMAL_MODE,  if use old OVT I2C protocol=> set CUS_I2C_LEGACY_MODE
#define SENSOR_I2C_FMT     I2C_FMT_A16D8        //CUS_I2C_FMT_A8D8, CUS_I2C_FMT_A8D16, CUS_I2C_FMT_A16D8, CUS_I2C_FMT_A16D16

#define SENSOR_PWDN_POL     CUS_CLK_POL_NEG        // if PWDN pin High can makes sensor in power down, set CUS_CLK_POL_POS
#define SENSOR_RST_POL      CUS_CLK_POL_NEG// if RESET pin High can makes sensor in reset state, set CUS_CLK_POL_NEG

#define SENSOR_VSYNC_POL    CUS_CLK_POL_POS         // if VSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_HSYNC_POL    CUS_CLK_POL_NEG         // if HSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_PCLK_POL     CUS_CLK_POL_POS         // depend on sensor setting, sometimes need to try CUS_CLK_POL_POS or CUS_CLK_POL_NEG
//static int  drv_Fnumber = 22;
//static volatile long long framecount=0;
static int pCus_SetAEGain(ms_cus_sensor *handle, u32 gain);
static int pCus_SetAEUSecs(ms_cus_sensor *handle, u32 us);
static CUS_CAMSENSOR_CAP sensor_cap = {
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
} sc2363_params;
// set sensor ID address and data

typedef struct {
    float total_gain;
    unsigned short reg_val;
} Gain_ARRAY;


static I2C_ARRAY Sensor_id_table[] =
{
{0x3107, 0x22},      // {address of ID, ID },
{0x3108, 0x32},
};

static I2C_ARRAY Sensor_init_table[] =
{
#if  1
    //[ParaList]
    0x0103,0x01,   //74.25 sysclk 297M cntclk
    0x0100,0x00,

    //close mipi
    //0x3018,0x1f,
    //0x3019,0xff,
    //0x301c,0xb4,

    0x320c,0x0a,
    0x320d,0x50,  //a80->a50

    0x3e01,0x23,

    0x363c,0x05,  //04
    0x3635,0xa8, //c0
    0x363b,0x0d, //0d

    0x3620,0x08,
    0x3622,0x02,
    0x3635,0xc0,//
    0x3908,0x10,

    0x3624,0x08, //count_clk inv  need debug  flash row in one channel

    0x5000,0x06,  //rts column test
    0x3e06,0x00,
    0x3e08,0x03,
    0x3e09,0x10,
    0x3333,0x10,
    0x3306,0x7e,

    //0x3e08,0x1f,
    //0x3e09,0x1f,
    //0x3e06,0x03,
    0x3902,0x05,
    //0x3909,0x01,  //auto blc
    //0x390a,0xf5,  //auto blc

    0x3213,0x08,

    0x337f,0x03, //new auto precharge  330e in 3372   [7:6] 11: close div_rst 00:open div_rst
    0x3368,0x04,
    0x3369,0x00,
    0x336a,0x00,
    0x336b,0x00,
    0x3367,0x08,
    0x330e,0x30,

    0x3366,0x7c, // div_rst gap


    0x3633,0x42,

    0x330b,0xe0,

    0x3637,0x57,

    0x3302,0x1f, // adjust the gap betwen first and second cunt_en pos edage to even times the clk
    0x3309,0xde, // adjust the gap betwen first and second cunt_en pos edage to even times the clk
    //0x303f,0x81, // pclk sel pll_sclk_dig_div  20171205



    //leage current

    0x3907,0x00,
    0x3908,0x61,
    0x3902,0x45,
    0x3905,0xb8,
    //0x3904,0x06, //10.18
    0x3e01,0x8c,
    0x3e02,0x10,
    0x3e06,0x00,

    0x3038,0x48,
    0x3637,0x5d,
    0x3e06,0x00,


    //0921
    0x3908,0x11,

    0x335e,0x01,  //ana dithering
    0x335f,0x03,
    0x337c,0x04,
    0x337d,0x06,
    0x33a0,0x05,
    0x3301,0x04,

    0x3633,0x4f,  //prnu

    0x3622,0x06,  //blksun
    0x3630,0x08,
    0x3631,0x84,
    0x3306,0x30,

    0x366e,0x08,  // ofs auto en [3]
    0x366f,0x22,  // ofs+finegain  real ofs in 0x3687[4:0]

    0x3637,0x59,  // FW to 4.6k //9.22

    0x3320,0x06, // New ramp offset timing
    //0x3321,0x06,
    0x3326,0x00,
    0x331e,0x11,
    0x331f,0xc1,
    0x3303,0x20,
    0x3309,0xd0,
    0x330b,0xbe,
    0x3306,0x36,

    0x3635,0xc2, //TxVDD,HVDD
    0x363b,0x0a,
    0x3038,0x88,

    //9.22
    0x3638,0x1f, //ramp_gen by sc  0x30
    0x3636,0x25, //
    0x3625,0x02,
    0x331b,0x83,
    0x3333,0x30,

    //10.18
    0x3635,0xa0,
    0x363b,0x0a,
    0x363c,0x05,

    0x3314,0x13,//preprecharge

    //20171101 reduce hvdd pump lighting
    0x3038,0xc8,// high pump clk,low lighting
    0x363b,0x0b,//high hvdd ,low lighting
    0x3632,0x18,//large current,low ligting  0x38 (option)

    //20171102 reduce hvdd pump lighting
    0x3038,0xff,// high pump clk,low lighting

    0x3639,0x09,
    0x3621,0x28,
    0x3211,0x0c,

    //20171106
    0x366f,0x26,

    //20171121
    0x366f,0x2f,
    0x3320,0x01,
    0x3306,0x48,
    0x331e,0x19,
    0x331f,0xc9,

    0x330b,0xd3,
    0x3620,0x28,

    //20171122
    0x3309,0x60,
    0x331f,0x59,
    0x3308,0x10,
    0x3630,0x0c,

    //digital ctrl
    0x3f00,0x07,  // bit[2] = 1
    0x3f04,0x05,
    0x3f05,0x04,  // hts / 2 - 0x24

    0x3802,0x01,
    0x3235,0x08,
    0x3236,0xc8, // vts x 2 - 2

    //20171127
    0x3630,0x1c,

    //20171129

    0x320c,0x08, //2080 hts
    0x320d,0x20,

    0x320e,0x04, //1250 vts
    0x320f,0xe2,

    //digital ctrl
    0x3f04,0x03,
    0x3f05,0xec,  // hts / 2 - 0x24

    0x3235,0x09,
    0x3236,0xc2, // vts x 2 - 2

    0x3e01,0x9c,
    0x3e02,0x00,

    0x3039,0x54, //vco 390M
    0x303a,0xb3, //sysclk  78M
    0x303b,0x06,
    0x303c,0x0e,
    0x3034,0x01,//cunt clk 312M
    0x3035,0x9b,

    //mipi
    0x3018,0x33,//[7:5] lane_num-1
    0x3031,0x0a,//[3:0] bitmode
    0x3037,0x20,//[6:5] bitsel
    0x3001,0xFE,//[0] c_y

    //lane_dis of lane3~8
    //0x3018,0x12,
    //0x3019,0xfc,

    0x4603,0x00,//[0] data_fifo mipi mode
    0x4837,0x19,//[7:0] pclk period * 2
    0x4827,0x48,//[7:0] hs_prepare_time[7:0]

    0x33aa,0x10,//save power

    //20171208  logical   inter
    0x3670,0x04, //0x3631 3670[2] enable  0x3631 in 0x3682
    0x3677,0x84,//gain<gain0
    0x3678,0x88,//gain0=<gain<gain1
    0x3679,0x88,//gain>=gain1
    0x367e,0x08,//gain0 {3e08[4:2],3e09[3:1]}
    0x367f,0x28,//gain1

    0x3670,0x0c, //0x3633 3670[3] enable  0x3633 in 0x3683     20171227
    0x3690,0x34,//gain<gain0
    0x3691,0x11,//gain0=<gain<gain1
    0x3692,0x42,//gain>=gain1
    0x369c,0x08,//gain0{3e08[4:2],3e09[3:1]}
    0x369d,0x28,//gain1

    0x360f,0x01, //0x3622 360f[0] enable  0x3622 in 0x3680
    0x3671,0xc6,//gain<gain0
    0x3672,0x06,//gain0=<gain<gain1
    0x3673,0x16,//gain>=gain1
    0x367a,0x28,//gain0{3e08[4:2],3e09[3:1]}
    0x367b,0x3f,//gain1

    //20171218
    0x3802,0x00,

    //20171225 BLC power save mode
    0x3222,0x29,
    0x3901,0x02,
    0x3905,0x98,

    //20171227
    0x3e1e,0x34, // digital finegain enable

    //20180113
    0x3314,0x08,

    //20180312
    0x3208,0x07,//1928
    0x3209,0x88,
    0x320a,0x04,//1088
    0x320b,0x40,

    0x3200,0x00,//xstar 0
    0x3201,0x00,
    0x3202,0x00,//ystar 0
    0x3203,0x00,

    0x3204,0x07,//xend 1935
    0x3205,0x8f,
    0x3206,0x04,//yend 4+8+1088-1=1095
    0x3207,0x47,

    0x3211,0x04, // x shift 4
    0x3213,0x04, // y shift 4

    //20180328 MIPI CK SOT ISSUE

    0x4800,0x64,
    0x5988,0x02,
    0x598e,0x07,
    0x598f,0xd5,

    0x4837,0x33,
    //************


    //init
    0x3301,0x06,
    0x3306,0x48,
    0x3632,0x08,
    0x3e00,0x00,
    0x3e01,0x4d,
    0x3e02,0xe0,
    0x3e03,0x0b,
    0x3e06,0x00,
    0x3e07,0x80,
    0x3e08,0x03,
    0x3e09,0x10,

    0x0100,0x01,

#endif
};

static I2C_ARRAY TriggerStartTbl[] = {
//{0x30f4,0x00},//Master mode start
};

static I2C_ARRAY mirr_flip_table[] =
{
    {0x3221, 0x00}, // mirror[2:1], flip[6:5]
    {0x3213, 0x04}, // crop for bayer
};

typedef struct {
    short reg;
    char startbit;
    char stopbit;
} COLLECT_REG_SET;

static I2C_ARRAY gain_reg[] = {
    {0x3e06, 0x00},//Dgain [3:0]
    {0x3e07, 0x80},//[7:0]
    {0x3e08, 0x00|0x03},//Agian [4:2]
    {0x3e09, 0x10}, //[7:0]
};

static I2C_ARRAY gain_logic_reg[] = {
    {0x3301, 0x00},
    {0x3306, 0x00},
    {0x3632, 0x00},
};

static I2C_ARRAY precharge_reg[] = {
    {0x3314, 0x00},
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
static I2C_ARRAY expo_reg[] = {  // max expo line vts-4!
    {0x3e00, 0x00},//expo [20:17]
    {0x3e01, 0x00}, // expo[16:8]
    {0x3e02, 0x00}, // expo[7:0], [3:0] fraction of line
};

static I2C_ARRAY vts_reg[] = {
    {0x320e, 0x04},
    {0x320f, 0x65},
};
static I2C_ARRAY PatternTbl[] = {
    //pattern mode
};

static CUS_INT_TASK_ORDER def_order = {
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

int sc2363_MIPI_cus_camsensor_release_handle(ms_cus_sensor *handle);

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

static int pCus_poweron_2nd(ms_cus_sensor *handle)
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    SENSOR_DMSG("[%s] ", __FUNCTION__);

    //Sensor power on sequence
    sensor_if->MCLK(SCD_SENSOR_PAD_GROUP_SET, 1, handle->mclk);
    sensor_if->SetIOPad(SCD_SENSOR_PAD_GROUP_SET, CUS_SENIF_BUS_MIPI, CUS_SR1_MIPI_MODE_1 );
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_216M, handle->PCLK_POLARITY);
    sensor_if->SetCSI_Lane(SCD_SENSOR_PAD_GROUP_SET, 2, 1);

    ISP_config_io(handle); //not support
    SENSOR_DMSG("[%s] reset low\n", __FUNCTION__);
    sensor_if->Reset(SCD_SENSOR_PAD_GROUP_SET, handle->reset_POLARITY);
    MsSleep(RTK_MS_TO_TICK(10));
    SENSOR_DMSG("[%s] power low\n", __FUNCTION__);

    // power -> high, reset -> high
    SENSOR_DMSG("[%s] power high\n", __FUNCTION__);
    sensor_if->SWReset(handle->channel_num, FALSE);
    SENSOR_DMSG("[%s] reset high\n", __FUNCTION__);
    sensor_if->Reset(SCD_SENSOR_PAD_GROUP_SET, !handle->reset_POLARITY);
    MsSleep(RTK_MS_TO_TICK(5));

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
    MsSleep(RTK_MS_TO_TICK(10));
    SENSOR_DMSG("[%s] power low\n", __FUNCTION__);
    //sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, handle->pwdn_POLARITY);
    //MsSleep(RTK_MS_TO_TICK(5));

    // power -> high, reset -> high
    SENSOR_DMSG("[%s] power high\n", __FUNCTION__);
    //sensor_if->PowerOff(SENSOR_PAD_GROUP_SET,!handle->pwdn_POLARITY);
    sensor_if->SWReset(handle->channel_num, FALSE);
    //MsSleep(RTK_MS_TO_TICK(5));
    SENSOR_DMSG("[%s] reset high\n", __FUNCTION__);
    sensor_if->Reset(SENSOR_PAD_GROUP_SET, !handle->reset_POLARITY);
    MsSleep(RTK_MS_TO_TICK(5));

    //sensor_if->Set3ATaskOrder(handle, def_order);
    // pure power on
    //ISP_config_io(handle);
    //sensor_if->PowerOff(SENSOR_PAD_GROUP_SET,!handle->pwdn_POLARITY);
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

static int pCus_poweroff_2nd(ms_cus_sensor *handle)
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;

    SENSOR_DMSG("[%s] power low\n", __FUNCTION__);

    sensor_if->SWReset(handle->channel_num, TRUE);
    sensor_if->PowerOff(SCD_SENSOR_PAD_GROUP_SET, handle->pwdn_POLARITY);
    MsSleep(RTK_MS_TO_TICK(10));
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_DISABLE, handle->PCLK_POLARITY);
    sensor_if->MCLK(SCD_SENSOR_PAD_GROUP_SET , 0, handle->mclk);

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
#if 0 // TBD
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
    SENSOR_DMSG("[%s]sc2363 Read sensor id, get 0x%x Success\n", __FUNCTION__, (int)*id);
    SENSOR_DMSG("[%s]Read sensor id, get 0x%x Success\n", __FUNCTION__, (int)*id);
#endif
    return SUCCESS;
}

static int sc2363_SetPatternMode(ms_cus_sensor *handle,u32 mode)
{
    SENSOR_DMSG("\n\n[%s], mode=%d \n", __FUNCTION__, mode);

  return SUCCESS;
}

static int pCus_SetFPS(ms_cus_sensor *handle, u32 fps);
static int pCus_AEStatusNotify(ms_cus_sensor *handle, CUS_CAMSENSOR_AE_STATUS_NOTIFY status);
static int pCus_init(ms_cus_sensor *handle)
{

  UartSendTrace("\n\n[%s]", __FUNCTION__);
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
        SENSOR_EMSG("Sensor_init_table -> Retry %d...\n",cnt);
        if(cnt>=10)
        {
          SENSOR_EMSG("[%s:%d]Sensor init fail!!\n", __FUNCTION__, __LINE__);
          return FAIL;
        }
        MsSleep(RTK_MS_TO_TICK(100));//(10*1000);
      }
       #if 0 //Read reg for check
      SensorReg_Read(Sensor_init_table[i].reg, &ReadData);
      SENSOR_DMSG("[%s] sc2363SensorReg: %d 0x%x, 0x%x, \n", __FUNCTION__, i, Sensor_init_table[i].reg, ReadData);
      #endif
    }
    #if 0 //Read reg for check
    //SensorReg_Read(,Sensor_init_table[i].data)
    SensorReg_Read(Sensor_init_table[i].reg, &ReadData);
    UartSendTrace("[%s] sc2363SensorReg: %d 0x%x, 0x%x, \n", __FUNCTION__, i, Sensor_init_table[i].reg, ReadData);
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
  char sen_data;

  sen_data = mirr_flip_table[0].data;
  SENSOR_DMSG("mirror:%x\r\n", sen_data);
  switch(sen_data) {
    case 0x00:
      *orit = CUS_ORIT_M0F0;
      break;
    case 0x06:
      *orit = CUS_ORIT_M1F0;
      break;
    case 0x60:
      *orit = CUS_ORIT_M0F1;
      break;
    case 0x66:
      *orit = CUS_ORIT_M1F1;
      break;
  }

    return SUCCESS;
}

static int pCus_SetOrien(ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT orit) {
  sc2363_params *params = (sc2363_params *)handle->private_data;

  switch(orit) {
    case CUS_ORIT_M0F0:
      if (mirr_flip_table[0].data) {
          mirr_flip_table[0].data = 0;
          params->dirty = true;
      }
      break;
    case CUS_ORIT_M1F0:
      if (mirr_flip_table[0].data!=6) {
          mirr_flip_table[0].data = 0x6;
          params->dirty = true;
      }
      break;
    case CUS_ORIT_M0F1:
      if (mirr_flip_table[0].data!= 0x60) {
          mirr_flip_table[0].data = 0x60;
          params->dirty = true;
      }
      break;
    case CUS_ORIT_M1F1:
      if (mirr_flip_table[0].data!=0x66) {
          mirr_flip_table[0].data = 0x66;
          params->dirty = true;
      }
      break;
  }
  SENSOR_DMSG("pCus_SetOrien:%x\r\n", orit);
    return SUCCESS;
}

static int pCus_GetFPS(ms_cus_sensor *handle)
{
    sc2363_params *params = (sc2363_params *)handle->private_data;
    SENSOR_DMSG("[%s]", __FUNCTION__);

    return  params->expo.fps;
}

static int pCus_SetFPS(ms_cus_sensor *handle, u32 fps)
{
    sc2363_params *params = (sc2363_params *)handle->private_data;
    SENSOR_DMSG("\n\n[%s]", __FUNCTION__);

    //return SUCCESS;

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
    sc2363_params *params = (sc2363_params *)handle->private_data;

    short sen_data1;

    switch(status)
    {
        case CUS_FRAME_INACTIVE:

        break;
        case CUS_FRAME_ACTIVE:
            //SENSOR_DMSG("[%s] frame %ld\n", __FUNCTION__,framecount);
            if(params->dirty)
            {
            SensorRegArrayW((I2C_ARRAY*)expo_reg, ARRAY_SIZE(expo_reg));
            //  SensorRegArrayW((I2C_ARRAY*)precharge_reg, ARRAY_SIZE(precharge_reg));
            SensorRegArrayW((I2C_ARRAY*)gain_reg, ARRAY_SIZE(gain_reg));

            SensorReg_Write(0x3812,0x00);

            SensorRegArrayW((I2C_ARRAY*)gain_logic_reg, ARRAY_SIZE(gain_logic_reg));

            SensorRegArrayW((I2C_ARRAY*)precharge_reg, ARRAY_SIZE(precharge_reg));

            SensorReg_Write(0x3812,0x30);

            SensorRegArrayW((I2C_ARRAY*)vts_reg, ARRAY_SIZE(vts_reg));



        /*  SensorReg_Read( 0x3e00, &sen_data1 );
            SENSOR_DMSG( "0x3101=0x%x,", sen_data1 );
            SensorReg_Read( 0x3e01, &sen_data1 );
            SENSOR_DMSG( "0x%x,", sen_data1 );
            SensorReg_Read( 0x3e02, &sen_data1 );
            SENSOR_DMSG( "0x%x \r\n", sen_data1 );

            SensorReg_Read( 0x3e06, &sen_data1 );
            SENSOR_DMSG( "0x3e06=0x%x,", sen_data1 );
            SensorReg_Read( 0x3e07, &sen_data1 );
            SENSOR_DMSG( "0x%x,", sen_data1 );
            SensorReg_Read( 0x3e08, &sen_data1 );
            SENSOR_DMSG( "0x%x,", sen_data1 );
            SensorReg_Read( 0x3e09, &sen_data1 );
            SENSOR_DMSG( "0x%x \r\n", sen_data1 );*/

            //SensorReg_Read( 0x3314, &sen_data1 );
            //SENSOR_DMSG( "0x3314=0x%x,", sen_data1 );




                params->dirty = false;
            }

            break;
            default :
            break;
    }
    return SUCCESS;
}

static int pCus_GetAEUSecs(ms_cus_sensor *handle, u32 *us) {
    sc2363_params *params = (sc2363_params *)handle->private_data;
    u32 lines = 0;
    lines |= (u32)(expo_reg[0].data&0x0f)<<16;
    lines |= (u32)(expo_reg[1].data&0xff)<<8;
    lines |= (u32)(expo_reg[2].data&0xf0)<<0;
    lines >>= 4;

    *us = lines*Preview_line_period/1000/2;
    //SENSOR_DMSG("====================================================\n");
    //SENSOR_DMSG("[%s] sensor expo lines/us %ld,%ld us\n", __FUNCTION__, lines, *us);
    //SENSOR_DMSG("====================================================\n");

    SENSOR_DMSG("[%s] sensor expo lines/us %ld,%ld us\n", __FUNCTION__, lines, *us);

    return SUCCESS;
}

static int pCus_SetAEUSecs(ms_cus_sensor *handle, u32 us) {
    int i;
    u32 half_lines = 0,vts = 0;
    sc2363_params *params = (sc2363_params *)handle->private_data;

        short sen_data1;

    I2C_ARRAY expo_reg_temp[] = {  // max expo line vts-4!
        {0x3e00, 0x00},//expo [20:17]
        {0x3e01, 0x00}, // expo[16:8]
        {0x3e02, 0x00}, // expo[7:0], [3:0] fraction of line
    };
    memcpy(expo_reg_temp, expo_reg, sizeof(expo_reg));

    half_lines = (1000*us*2)/Preview_line_period; // Preview_line_period in ns
    if(half_lines<1) half_lines=1;
    if (half_lines >  2 * (params->expo.vts)-4) {
        half_lines = 2 * (params->expo.vts)-4;
    }
    else
     vts=params->expo.vts;
    SENSOR_DMSG("[%s] us %ld, half_lines %ld, vts %ld\n", __FUNCTION__, us, half_lines, params->expo.vts);
    half_lines = half_lines<<4;
    expo_reg[0].data = (half_lines>>16) & 0x0f;
    expo_reg[1].data = (half_lines>>8) & 0xff;
    expo_reg[2].data = (half_lines>>0) & 0xf0;

/*    if (((half_lines >>8) & 0x0fff) < 5)
    {
        nr2_reg[0].data = 0x14;
    }else if (((half_lines >>8) & 0x0fff) > 0xa)
    {
        nr2_reg[0].data = 0x04;
    }
*/

    if(expo_reg[1].data<0x05)
    {
        precharge_reg[0].data=0x14;
        //params->dirty = true;
    }
    else if(expo_reg[1].data>0x0a)
    {
        precharge_reg[0].data=0x04;
        //params->dirty = true;
    }

    for (i = 0; i < sizeof(expo_reg)/sizeof(I2C_ARRAY); i++)
    {
      if (expo_reg[i].data != expo_reg_temp[i].data)
      {
        params->dirty = true;
        break;
      }
 //   SENSOR_DMSG("=========================================================\n");
    }

    //params->dirty = true;
    return SUCCESS;
}

// Gain: 1x = 1024
static int pCus_GetAEGain(ms_cus_sensor *handle, u32* gain) {
    int rc = 0;
    u8 i=0 ,Dgain = 1,  Coarse_gain = 1;

    Coarse_gain = ((gain_reg[2].data&0x1C)>>2) +1;
    Dgain = ((gain_reg[0].data&0x0f) + 1);

    *gain = (Coarse_gain*Dgain*(gain_reg[1].data)*(gain_reg[3].data))/2;


    SENSOR_DMSG("[%s] gain/reg = %d, 0x%x,  0x%x  0x%x\n", __FUNCTION__, *gain,gain_reg[0].data,gain_reg[1].data,gain_reg[2].data);
    SENSOR_DMSG("[%s] gain/reg = %d, %f ,%d, %d %f %f\n", __FUNCTION__, *gain,temp_gain,Coarse_gain,Dgain,Fine_again,Fine_dgain);
    return rc;
}

static int pCus_SetAEGain(ms_cus_sensor *handle, u32 gain) {
    sc2363_params *params = (sc2363_params *)handle->private_data;
    int i = 0;
    u8 Dgain_reg = 0, Cgain_reg = 0, Fine_again_reg= 0x10,Fine_dgain_reg= 0x80;
    u32 gainTemp;

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
/*
#if ENABLE_NR
    if (gain < 2*1024) {
        nr_reg[0].data = 0x06;
        nr_reg[1].data = 0x48;
        nr_reg[2].data = 0x08;
    } else if (gain < 4*1024) {
        nr_reg[0].data = 0x14;
        nr_reg[1].data = 0x48;
        nr_reg[2].data = 0x08;
    } else if (gain < 8*1024) {
        nr_reg[0].data = 0x18;
        nr_reg[1].data = 0x48;
        nr_reg[2].data = 0x08;
    } else if (gain < 15.5*1024) {
        nr_reg[0].data = 0x13;
        nr_reg[1].data = 0x48;
        nr_reg[2].data = 0x08;
    } else if (gain < 31*1024) {
        nr_reg[0].data = 0xf9;
        nr_reg[1].data = 0x78;
        nr_reg[2].data = 0x48;
    } else {
        nr_reg[0].data = 0xf9;
        nr_reg[1].data = 0x78;
        nr_reg[2].data = 0x78;
    }
#endif
    if (gain < 10*1024) {
        DPC_reg[0].data = 0x04;
        DPC_reg[1].data = 0x18;
    } else {
        DPC_reg[0].data = 0x02;
        DPC_reg[1].data = 0x08;
    }
*/
    if (gain < 2 * 1024)
    {
        Cgain_reg = 0;  Fine_again_reg = gain>>6;
        Dgain_reg = 0;  Fine_dgain_reg = (gain<<1)/Fine_again_reg;
    }
    else if (gain <  4 * 1024)
    {
        Cgain_reg = 1;  Fine_again_reg = gain>>7;
        Dgain_reg = 0;  Fine_dgain_reg = gain/Fine_again_reg;
    }
    else if (gain < 8 * 1024)
    {
        Cgain_reg = 3;  Fine_again_reg = gain>>8;
        Dgain_reg = 0;  Fine_dgain_reg = (gain>>1)/Fine_again_reg;
    }
    else if (gain <= 15.5 * 1024)
    {
        Cgain_reg = 7;  Fine_again_reg = gain>>9;
        Dgain_reg = 0;  Fine_dgain_reg = (gain>>2)/Fine_again_reg;
    }
    else if (gain < 31 * 1024)
    {
        Cgain_reg = 7;  Fine_again_reg = 0x1f;
        Dgain_reg = 0;  Fine_dgain_reg = gain/124;
    }
    else if (gain < 62 * 1024)
    {
        Cgain_reg = 7;  Fine_again_reg = 0x1f;
        Dgain_reg = 1;  Fine_dgain_reg = gain/248;
    }
    else if (gain < 124 * 1024)
    {
        Cgain_reg = 7;  Fine_again_reg = 0x1f;
        Dgain_reg = 3;  Fine_dgain_reg = gain/496;
    }
    else if (gain < 248 * 1024)
    {
        Cgain_reg = 7;  Fine_again_reg = 0x1f;
        Dgain_reg = 7;  Fine_dgain_reg = gain/992;
    }else if (gain <= SENSOR_MAX_GAIN * 1024)
    {
        Cgain_reg = 7;  Fine_again_reg = 0x1f;
        Dgain_reg = 0xF;  Fine_dgain_reg = gain/1984;
    }

    gain_reg[3].data = Fine_again_reg;
    gain_reg[2].data = (Cgain_reg<<2)&0x1C | 0x03;
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

    if(true == params->dirty )
    {
        ///gainTemp = gain/1024;
        {
            if(gain <2* 1024)
            //if (gainTemp <2)
            {
                //sc2363_sccb_write(0x3301, 0x06);
                //sc2363_sccb_write(0x3306, 0x48);
                //sc2363_sccb_write(0x3632, 0x08);
                gain_logic_reg[0].data=0x06;
                gain_logic_reg[1].data=0x48;
                gain_logic_reg[2].data=0x08;
            }
            else if(gain <4* 1024)
            //else if(gainTemp <4)
            {
                //sc2363_sccb_write(0x3301, 0x14);
                //sc2363_sccb_write(0x3306, 0x48);
                //sc2363_sccb_write(0x3632, 0x08);
                gain_logic_reg[0].data=0x14;
                gain_logic_reg[1].data=0x48;
                gain_logic_reg[2].data=0x08;
            }
            else if((gain >=4* 1024)&&(gain <8* 1024))
            // else if((gainTemp >=4)&&(gainTemp <8))
            {
                //sc2363_sccb_write(0x3301, 0x18);
                //sc2363_sccb_write(0x3306, 0x48);
                //sc2363_sccb_write(0x3632, 0x08);
                gain_logic_reg[0].data=0x18;
                gain_logic_reg[1].data=0x48;
                gain_logic_reg[2].data=0x08;
            }
            //else if(gain <15.5* 1024)512
            else if(gain <(15* 1024+512))
            //else if(gainTemp <16)
            {
                //sc2363_sccb_write(0x3301, 0x13);
                //sc2363_sccb_write(0x3306, 0x48);
                //sc2363_sccb_write(0x3632, 0x08);
                gain_logic_reg[0].data=0x13;
                gain_logic_reg[1].data=0x48;
                gain_logic_reg[2].data=0x08;
            }
            //  else if((gain >=15.5* 1024)&&(gain <31* 1024))
            else if((gain >=(15* 1024+512))&&(gain <31* 1024))
            //else if((gainTemp >=16)&&(gainTemp <31))
            {
                //sc2363_sccb_write(0x3301, 0xA1);
                //sc2363_sccb_write(0x3306, 0x78);
                //sc2363_sccb_write(0x3632, 0x48);
                gain_logic_reg[0].data=0xA1;
                gain_logic_reg[1].data=0x78;
                gain_logic_reg[2].data=0x48;
            }
            else
            {
                //sc2363_sccb_write(0x3301, 0xA1);
                //sc2363_sccb_write(0x3306, 0x78);
                //sc2363_sccb_write(0x3632, 0x48);
                gain_logic_reg[0].data=0xA1;
                gain_logic_reg[1].data=0x78;
                gain_logic_reg[2].data=0x48;
            }
        }
    }

        return SUCCESS;
}

static int pCus_GetAEMinMaxUSecs(ms_cus_sensor *handle, u32 *min, u32 *max) {
    *min = 150;
    *max = 33332; // <- max shutter (30fps: 33332, 60fps:16666)
    return SUCCESS;
}

static int pCus_GetAEMinMaxGain(ms_cus_sensor *handle, u32 *min, u32 *max) {
    *min = 1024;
    *max = SENSOR_MAX_GAIN*1024;
    return SUCCESS;
}

static int sc2363_GetShutterInfo(struct __ms_cus_sensor* handle,CUS_SHUTTER_INFO *info)
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

#if defined(BIND_SENSOR_SC2363_2ND) && (BIND_SENSOR_SC2363_2ND == 1)
int sc2363_MIPI_cus_camsensor_init_handle_2nd(ms_cus_sensor* drv_handle)
{
    ms_cus_sensor *handle = drv_handle;
    #if defined(__RTK_OS__)
    CamOsRet_e          eCamOsRet = CAM_OS_OK;
    void*               pvBufVirt = NULL;
    u64                 u64BufPhy = 0;
    u64                 u64BufMiu = 0;
    u8                  str[20];
    #endif

    if (!handle) {
        SENSOR_DMSG("[%s] not enough memory!\n", __FUNCTION__);
        return FAIL;
    }

    SENSOR_DMSG("[%s]", __FUNCTION__);

    #if defined(__RTK_OS__)
    sprintf(str, "SC2363cali");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(sc2363_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }

    handle->private_data = (sc2363_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(sc2363_params));
    #else
    handle->private_data = calloc( 1, sizeof(sc2363_params) );
    #endif

    sc2363_params *params = (sc2363_params *)handle->private_data;

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
    handle->bayer_id    = SCD_SENSOR_BAYERID;   //CUS_BAYER_GB;
    handle->orient      = SENSOR_ORIT;      //CUS_ORIT_M1F1;
    handle->interface_attr.attr_mipi.mipi_lane_num = SENSOR_MIPI_LANE_NUM;
    handle->interface_attr.attr_mipi.mipi_data_format = CUS_SEN_INPUT_FORMAT_RGB; // RGB pattern.
    handle->interface_attr.attr_mipi.mipi_yuv_order = 0; //don't care in RGB pattern.
    handle->interface_attr.attr_mipi.mipi_hsync_mode = SENSOR_MIPI_HSYNC_MODE;
    handle->interface_attr.attr_mipi.mipi_sampling_delay = SENSOR_MIPI_DELAY;
    handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_NONE;
    handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 1;
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
    handle->video_res_supported.res[0].nOutputWidth= 1928;//Preview_WIDTH;
    handle->video_res_supported.res[0].nOutputHeight= 1088;//Preview_HEIGHT;
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

    handle->pCus_sensor_release     = sc2363_MIPI_cus_camsensor_release_handle;
    handle->pCus_sensor_init        = pCus_init;
    handle->pCus_sensor_poweron     = pCus_poweron_2nd;
    handle->pCus_sensor_poweroff    = pCus_poweroff_2nd;

    handle->pCus_sensor_GetSensorID       = pCus_GetSensorID;
    handle->pCus_sensor_GetVideoResNum    = pCus_GetVideoResNum;
    handle->pCus_sensor_GetVideoRes       = pCus_GetVideoRes;
    handle->pCus_sensor_SetVideoRes       = pCus_SetVideoRes;
    handle->pCus_sensor_GetOrien          = pCus_GetOrien;
    handle->pCus_sensor_SetOrien          = pCus_SetOrien;
    handle->pCus_sensor_GetFPS            = pCus_GetFPS;
    handle->pCus_sensor_SetFPS            = pCus_SetFPS;
    handle->pCus_sensor_GetSensorCap      = pCus_GetSensorCap;
    handle->pCus_sensor_SetPatternMode    = sc2363_SetPatternMode;

    handle->pCus_sensor_AEStatusNotify  = pCus_AEStatusNotify;
    handle->pCus_sensor_GetAEUSecs      = pCus_GetAEUSecs;
    handle->pCus_sensor_SetAEUSecs      = pCus_SetAEUSecs;
    handle->pCus_sensor_GetAEGain       = pCus_GetAEGain;
    handle->pCus_sensor_SetAEGain       = pCus_SetAEGain;

    handle->pCus_sensor_GetAEMinMaxGain     = pCus_GetAEMinMaxGain;
    handle->pCus_sensor_GetAEMinMaxUSecs    = pCus_GetAEMinMaxUSecs;
    handle->pCus_sensor_GetDGainRemainder   = pCus_GetDGainRemainder;

    handle->pCus_sensor_setCaliData_gain_linearity=pCus_setCaliData_gain_linearity;
    handle->pCus_sensor_GetShutterInfo      = sc2363_GetShutterInfo;

    handle->snr_pad_group = SCD_SENSOR_PAD_GROUP_SET;

    params->expo.vts=vts_30fps;
    params->expo.fps = 30;
    //params->dirty = false;
    //params->orient_dirty = false;
    params->dirty = false;
    //params->reg_dirty_cnt = 0;
    handle->channel_num = SCD_SENSOR_CHANNEL_NUM;
    handle->channel_mode = SCD_SENSOR_CHANNEL_MODE;
    return SUCCESS;
}

#endif

#if defined(BIND_SENSOR_SC2363) && (BIND_SENSOR_SC2363 == 1)
int sc2363_MIPI_cus_camsensor_init_handle(ms_cus_sensor* drv_handle)
{
    ms_cus_sensor *handle = drv_handle;
    #if defined(__RTK_OS__)
    CamOsRet_e          eCamOsRet = CAM_OS_OK;
    void*               pvBufVirt = NULL;
    u64                 u64BufPhy = 0;
    u64                 u64BufMiu = 0;
    u8                  str[20];
    #endif

    if (!handle) {
        SENSOR_DMSG("[%s] not enough memory!\n", __FUNCTION__);
        return FAIL;
    }

    SENSOR_DMSG("[%s]", __FUNCTION__);

    #if defined(__RTK_OS__)
    sprintf(str, "SC2363cali");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(sc2363_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }

    handle->private_data = (sc2363_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(sc2363_params));
    #else
    handle->private_data = calloc( 1, sizeof(sc2363_params) );
    #endif

    sc2363_params *params = (sc2363_params *)handle->private_data;

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
    handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 1;
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
    handle->video_res_supported.res[0].nOutputWidth= 1928;//Preview_WIDTH;
    handle->video_res_supported.res[0].nOutputHeight= 1088;//Preview_HEIGHT;
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

    handle->pCus_sensor_release     = sc2363_MIPI_cus_camsensor_release_handle;
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
    handle->pCus_sensor_SetPatternMode    = sc2363_SetPatternMode;

    handle->pCus_sensor_AEStatusNotify = pCus_AEStatusNotify;
    handle->pCus_sensor_GetAEUSecs      = pCus_GetAEUSecs;
    handle->pCus_sensor_SetAEUSecs      = pCus_SetAEUSecs;
    handle->pCus_sensor_GetAEGain       = pCus_GetAEGain;
    handle->pCus_sensor_SetAEGain       = pCus_SetAEGain;

    handle->pCus_sensor_GetAEMinMaxGain = pCus_GetAEMinMaxGain;
    handle->pCus_sensor_GetAEMinMaxUSecs= pCus_GetAEMinMaxUSecs;
    handle->pCus_sensor_GetDGainRemainder = pCus_GetDGainRemainder;

    handle->pCus_sensor_setCaliData_gain_linearity=pCus_setCaliData_gain_linearity;
    handle->pCus_sensor_GetShutterInfo = sc2363_GetShutterInfo;

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
#endif

int sc2363_MIPI_cus_camsensor_release_handle(ms_cus_sensor *handle)
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
        eCamOsRet = CamOsDirectMemRelease((void*)handle->private_data, sizeof(sc2363_params));
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
#if defined(BIND_SENSOR_SC2363_2ND) && (BIND_SENSOR_SC2363_2ND == 1)
struct SensorMapTable_t gsensor_map_sc2363_2nd[] = {
    { //Channel 1
        SCD_SENSOR_CHANNEL_NUM,
        sc2363_MIPI_cus_camsensor_init_handle_2nd,
        sc2363_MIPI_cus_camsensor_release_handle
    }
};
#endif

#if defined(BIND_SENSOR_SC2363) && (BIND_SENSOR_SC2363 == 1)
struct SensorMapTable_t gsensor_map_sc2363[] = {
    { //Channel 0
        SENSOR_CHANNEL_NUM,
        sc2363_MIPI_cus_camsensor_init_handle,
        sc2363_MIPI_cus_camsensor_release_handle
    }
};
#endif

int SC2363_Module_Init(void)
{
    #if defined(BIND_SENSOR_SC2363) && (BIND_SENSOR_SC2363 == 1)
        cameraSensorRegister(&gsensor_map_sc2363[0]);
    #endif

    #if defined(BIND_SENSOR_SC2363_2ND) && (BIND_SENSOR_SC2363_2ND == 1)
        cameraSensorRegister(&gsensor_map_sc2363_2nd[0]);
    #endif

    return 0;
}

void SC2363_Module_Exit(void)
{
    #if defined(BIND_SENSOR_SC2363) && (BIND_SENSOR_SC2363 == 1)
        cameraSensorUnRegister(&gsensor_map_sc2363[0]);
    #endif

    #if defined(BIND_SENSOR_SC2363_2ND) && (BIND_SENSOR_SC2363_2ND == 1)
        cameraSensorUnRegister(&gsensor_map_sc2363_2nd[0]);
    #endif
}

#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(SC2363_Module_Init);
#endif //#if defined(__RTK_OS__)

#endif


