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
#if (SENSOR0 == IMX323)
#define BIND_SENSOR_IMX323 (1)
#endif
#endif //#if defined(__RTK_OS__)

#if defined(BIND_SENSOR_IMX323) && (BIND_SENSOR_IMX323 == 1)

#define SENSOR_PAD_GROUP_SET CUS_SENSOR_PAD_GROUP_A
#define SENSOR_CHANNEL_NUM (0)
#define SENSOR_CHANNEL_MODE CUS_SENSOR_CHANNEL_MODE_REALTIME_NORMAL //CUS_SENSOR_CHANNEL_MODE_RAW_STORE_FETCH //CUS_SENSOR_CHANNEL_MODE_REALTIME_NORMAL

//int usleep(u32 usec);

//#define __MV5_FPGA__IMX323__ (0)

#define SENSOR_ISP_TYPE     ISP_EXT                   //ISP_EXT, ISP_SOC
#define F_number  22                                  // CFG, demo module
//#define SENSOR_DATAFMT      CUS_DATAFMT_BAYER        //CUS_DATAFMT_YUV, CUS_DATAFMT_BAYER
#define SENSOR_IFBUS_TYPE   CUS_SENIF_BUS_PARL      //CFG //CUS_SENIF_BUS_PARL, CUS_SENIF_BUS_MIPI
//#define SENSOR_MIPI_DELAY   0x1212                  //CFG
#define SENSOR_DATAPREC     CUS_DATAPRECISION_12    //CUS_DATAPRECISION_8, CUS_DATAPRECISION_10
#define SENSOR_DATAMODE     CUS_SEN_10TO12_9000     //CFG
#if defined(__MV5_FPGA__IMX323__) //15 FPS.
#define SENSOR_BAYERID      CUS_BAYER_RG
#else
#define SENSOR_BAYERID      CUS_BAYER_GR            //CFG //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
#endif
#define SENSOR_ORIT         CUS_ORIT_M0F0           //CUS_ORIT_M0F0, CUS_ORIT_M1F0, CUS_ORIT_M0F1, CUS_ORIT_M1F1,
//#define SENSOR_YCORDER      CUS_SEN_YCODR_YC       //CUS_SEN_YCODR_YC, CUS_SEN_YCODR_CY
#define lane_number 2
#define vc0_hs_mode 3   //0: packet header edge  1: line end edge 2: line start edge 3: packet footer edge
#define long_packet_type_enable 0x00 //UD1~UD8 (user define)
#define SENSOR_MAX_GAIN     (177 * 1024)                  // max sensor again, a-gain * conversion-gain*d-gain
#define SENSOR_MIN_GAIN      (1 * 1024)
#define SENSOR_GAIN_DELAY_FRAME_COUNT      (2)
#define SENSOR_SHUTTER_DELAY_FRAME_COUNT      (2)

#define Preview_MCLK_SPEED  CUS_CMU_CLK_36MHZ       //CFG //CUS_CMU_CLK_12M, CUS_CMU_CLK_16M, CUS_CMU_CLK_24M, CUS_CMU_CLK_27M
#define Preview_line_period 30000                  ////HTS/PCLK=4455 pixels/148.5MHZ=30usec
#define Prv_Max_line_number 1080                    //maximum exposure line munber of sensor when preview
#define vts_30fps 1141//1125//1346,1616                      //for 29.1fps
#define Preview_WIDTH       1920                    //resolution Width when preview
#define Preview_HEIGHT      1080                    //resolution Height when preview
#define Preview_MAX_FPS     30                     //fastest preview FPS
#define Preview_MIN_FPS     8                      //slowest preview FPS
#define Preview_CROP_START_X     0x81                      //CROP_START_X
#define Preview_CROP_START_Y     0x21                      //CROP_START_Y

//#define Capture_MCLK_SPEED  CUS_CMU_CLK_16M     //CUS_CMU_CLK_12M, CUS_CMU_CLK_16M, CUS_CMU_CLK_24M, CUS_CMU_CLK_27M
#define Cap_Max_line_number 1080                   //maximum exposure line munber of sensor when capture

//#define SENSOR_I2C_LEGACY  CUS_I2C_NORMAL_MODE     //usally set CUS_I2C_NORMAL_MODE,  if use old OVT I2C protocol=> set CUS_I2C_LEGACY_MODE
//#define SENSOR_I2C_FMT     CUS_I2C_FMT_A16D8        //CUS_I2C_FMT_A8D8, CUS_I2C_FMT_A8D16, CUS_I2C_FMT_A16D8, CUS_I2C_FMT_A16D16
#define SENSOR_I2C_ADDR    0x34                   //I2C slave address
#define SENSOR_I2C_SPEED    I2C_SLOWSPEED_MODE_200KHZ   //200KHz
#define SENSOR_I2C_CHANNEL  1                           //I2C Channel
#define SENSOR_I2C_PAD_MODE 2                           //Pad/Mode Number

#define SENSOR_I2C_LEGACY  I2C_NORMAL_MODE     //usally set CUS_I2C_NORMAL_MODE,  if use old OVT I2C protocol=> set CUS_I2C_LEGACY_MODE
#define SENSOR_I2C_FMT     I2C_FMT_A16D8        //CUS_I2C_FMT_A8D8, CUS_I2C_FMT_A8D16, CUS_I2C_FMT_A16D8, CUS_I2C_FMT_A16D16

#define SENSOR_PWDN_POL     CUS_CLK_POL_POS//CUS_CLK_POL_NEG        // if PWDN pin High can makes sensor in power down, set CUS_CLK_POL_POS
#define SENSOR_RST_POL      CUS_CLK_POL_NEG        // if RESET pin High can makes sensor in reset state, set CUS_CLK_POL_NEG

// VSYNC/HSYNC POL can be found in data sheet timing diagram,
// Notice: the initial setting may contain VSYNC/HSYNC POL inverse settings so that condition is different.

#define SENSOR_VSYNC_POL    CUS_CLK_POL_NEG//CUS_CLK_POL_NEG //CUS_CLK_POL_POS        // if VSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_HSYNC_POL    CUS_CLK_POL_POS //CUS_CLK_POL_NEG        // if HSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_PCLK_POL     CUS_CLK_POL_POS        // depend on sensor setting, sometimes need to try CUS_CLK_POL_POS or CUS_CLK_POL_NEG
//static int  drv_Fnumber = 22;

static int pCus_SetAEGain(ms_cus_sensor *handle, u32 gain);
static int pCus_SetAEUSecs(ms_cus_sensor *handle, u32 us);
int imx323_cus_camsensor_release_handle(ms_cus_sensor *handle);

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
    u32 shutter_us;
    bool reg_dirty; //sensor setting need to update through I2C
} imx323_params;
// set sensor ID address and data,

static I2C_ARRAY Sensor_id_table[] =
{
    {0x301C, 0x50},      // {address of ID, ID },
    //{0x300b, 0x10},      // {address of ID, ID },
};
#define USE_10_BIT (0)
static I2C_ARRAY Sensor_init_table[] =
{
#if defined(__MV5_FPGA__IMX323__) //15 FPS.

    0x0100, 0x00,   //standby control 0:standby 1: normal
    0x0008, 0x00,   //black level offset [8]
    0x0009, 0xF0,   //black level offset [7:0]

    0x0101, 0x00,

    0x0104, 0x00,

    0x0112, 0x0C,
    0x0113, 0x0C,

    0x0202, 0x00,
    0x0203, 0x00,

    //0x0340,   0x04,
    //0x0341,   0x71,//0x65, // FRM_LENGTH
    0x0340, 0x04,//FPGA
    0x0341, 0x65,//0x65, // FRM_LENGTH

    //0x0342,   0x04,
    //0x0343,   0x4C, // 1100 // LINE_LENGTH
    0x0342, 0x08, //FPGA
    0x0343, 0x98, // 1100 // LINE_LENGTH

    0x0003, 0x08, //FPGA
    //0x0004,   0x98, // HMAX
    0x0004, 0xC8, // HMAX

    0x0005, 0x04, //FPGA
    0x0006, 0x65, // VMAX
    0x0011, 0x01, //FPGA
    0x009A, 0x44, //FPGA
    0x009B, 0x0C, //FPGA

    0x0344, 0x00,
    0x0345, 0x00,
    0x0346, 0x00,
    0x0347, 0x00,

    0x034C, 0x07,
    0x034D, 0xC0, // 1984
    0x034E, 0x04,
    0x034F, 0xC9, // 1225
    0x3000, 0x31,
    0x3001, 0x00,
    0x3002, 0x0F,
    0x300D, 0x00,
    0x300E, 0x00,
    0x300F, 0x00,
    0x3010, 0x00,
    //0x3011,   0x00,
    0x3011, 0x01, //FPGA, FRSEL

    0x3012, 0x82,

    0x3016, 0x3C,
    0x3017, 0x00,
    0x301E, 0x00,
    0x301F, 0x73,
    0x3020, 0x3C,

    0x3021, 0x20, // 22clk //0x00, // XHSLNG
    0x3022, 0x00,

    0x3027, 0x20,
    0x302C, 0x01,
    0x303B, 0xE1,

    0x307A, 0x00,
    0x307B, 0x00,

    0x3098, 0x26,
    0x3099, 0x02,

    0x309A, 0x26,
    0x309B, 0x02,

    0x30CE, 0x16,
    0x30CF, 0x82,
    0x30D0, 0x00,
    0x3117, 0x0D,

    0x302C, 0x00,
    0x0100, 0x01    //standby control 0:standby 1: normal

#else //#if defined(__MV5_FPGA__IMX323__)  //15 FPS.

    0x0100, 0x00,
    0x0008, 0x00,
    0x0009, 0xF0,
#if (SENSOR_ROTATE_180)
    0x0101, 0x03,   // (IMG_ORIENTATION, address 0101h[1]), Vertical (V) scanning direction control (I2C)
                    // 0: Normal, 1: Inverted
                    // (IMG_ORIENTATION, address 0101h[2]), Horizontal (H) scanning direction control (I2C)
                    // 0: Normal, 1: Inverted
#else
    0x0101, 0x00,
#endif
    0x0104, 0x00,

#if (USE_10_BIT)
    0x0112, 0x0A,
    0x0113, 0x0A,
#else
    0x0112, 0x0C,
    0x0113, 0x0C,
#endif

    0x0202, 0x00,
    0x0203, 0x00,

#if (USE_10_BIT)
    0x0340, 0x04,
    0x0341, 0x65,
#else
    0x0340, 0x04,
    //0x0341, 0x71,//0x65, // FRM_LENGTH
    0x0341, 0x8C,// FRM_LENGTH
#endif

    0x0342, 0x04,
    0x0343, 0x28, // LINE_LENGTH

    0x0344, 0x00,
    0x0345, 0x00,
    0x0346, 0x00,
    0x0347, 0x00,

    0x034C, 0x07,
    0x034D, 0xC0, // 1984
    0x034E, 0x04,
    0x034F, 0xC9, // 1225
    0x3000, 0x31,
    0x3001, 0x00,
    0x3002, 0x0F,
    0x300D, 0x00,
    0x300E, 0x00,
    0x300F, 0x00,
    0x3010, 0x00,
    0x3011, 0x00,

#if (USE_10_BIT)
    0x3012, 0x80,
#else
    0x3012, 0x82,
#endif

    0x3016, 0x3C,
    0x3017, 0x00,
    0x301E, 0x00,
    0x301F, 0x73,
    0x3020, 0x3C,

#if (USE_10_BIT)
    0x3021, 0xA0, // 22clk //0x00, // XHSLNG
    0x3022, 0x00,
#else
    0x3021, 0x20, // 22clk //0x00, // XHSLNG
    0x3022, 0x00,
#endif

    0x3027, 0x20,
    0x302C, 0x01,
    0x303B, 0xE1,

#if (USE_10_BIT)
    0x307A, 0x40, // Rogers: 10bit //0x00,
    0x307B, 0x02, // Rogers: 10bit //0x00,
#else
    0x307A, 0x00,
    0x307B, 0x00,
#endif

    0x3098, 0x26,
    0x3099, 0x02,

#if (USE_10_BIT)
    0x309A, 0x4C, // Rogers: 10bit //0x26,
    0x309B, 0x04, // Rogers: 10bit //0x02,
#else
    0x309A, 0x26,
    0x309B, 0x02,
#endif

    0x30CE, 0x16,
    0x30CF, 0x82,
    0x30D0, 0x00,
    0x3117, 0x0D,

    0x302C, 0x00,
    0x0100, 0x01

#endif //#if defined(__MV5_FPGA__IMX323__) //15 FPS.
};

static I2C_ARRAY TriggerStartTbl[] =
{
    {0x302c,0x00},//Master mode start
};

static I2C_ARRAY PatternTbl[] =
{
    //pattern mode
    {0x3020,0x00},
    {0x3021,0x00},
    {0x3023,0x09},
    {0x3028,0x30},
    {0x3042,0x00},
    {0x3066,0x02}, //[0:1]:pattern select bit 1~2
    //{0x3065,0x81}, //[1]:pattern gen enable , [7]:pattern select bit 0
    {0x3065,0x81}, //[1]:pattern gen enable , [7]:pattern select bit 0
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



typedef struct
{
    short reg;
    char startbit;
    char stopbit;
} COLLECT_REG_SET;


static I2C_ARRAY mirror_reg[] =
{
    {0x0101, 0x00},//M0F0
};

static I2C_ARRAY gain_reg[] =
{
    //{0x350A, 0x00},//bit0, high bit
    {0x301E, 0x00},//low bit
};

//static int g_sensor_ae_min_gain = 1024;
static CUS_GAIN_GAP_ARRAY gain_gap_compensate[16] =
{  //compensate  gain gap
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
    {0x0202, 0x00},
    {0x0203, 0x00},
};

static I2C_ARRAY vts_reg[] =
{
    {0x0340, 0x03},
    {0x0341, 0x18},
};
/*
static CUS_INT_TASK_ORDER def_order =
{
    .RunLength = 9,
    .Orders =
    {
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
};*/

/////////// function definition ///////////////////

/////////////////// sensor hardware dependent //////////////
static int pCus_poweron(ms_cus_sensor *handle)
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;

    //Sensor power on sequence
    //DrvSensorIFHWSetIOPad(0/*TBD*/, CUS_SENIF_BUS_PARL, CUS_SR_PAD_CFG_6);//call sensor if
    sensor_if->SetIOPad(SENSOR_PAD_GROUP_SET, CUS_SENIF_BUS_PARL, CUS_SR0_PAR_MODE_1); // h0015, bit: 10~11 //FPGA
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_DISABLE, handle->PCLK_POLARITY);     //Set_csi_if(0, 0); //disable MIPI
    sensor_if->MCLK(SENSOR_PAD_GROUP_SET, 1, handle->mclk);

    SENSOR_DMSG("[%s] reset low\n", __FUNCTION__);
    sensor_if->Reset(SENSOR_PAD_GROUP_SET, handle->reset_POLARITY);
    usleep(500);
    SENSOR_DMSG("[%s] power low\n", __FUNCTION__);
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, handle->pwdn_POLARITY);
    usleep(500);

    // power -> high, reset -> high
    SENSOR_DMSG("[%s] power high\n", __FUNCTION__);
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, !handle->pwdn_POLARITY);
    usleep(500);
    SENSOR_DMSG("[%s] reset high\n", __FUNCTION__);
    sensor_if->Reset(SENSOR_PAD_GROUP_SET, !handle->reset_POLARITY);
    usleep(500);

    //sensor_if->Set3ATaskOrder( def_order);
    // pure power on
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, !handle->pwdn_POLARITY);
	sensor_if->SWReset(handle->channel_num, FALSE);
	return SUCCESS;
}

static int pCus_poweroff(ms_cus_sensor *handle)
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    //sensor_if->MIPISamplingDelay(handle, false, handle->mipi_sampling_delay);
    SENSOR_DMSG("[%s] power low\n", __FUNCTION__);
	sensor_if->SWReset(handle->channel_num, TRUE);
    sensor_if->PowerOff( 1, handle->pwdn_POLARITY);

    usleep(1000);
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_DISABLE, handle->PCLK_POLARITY);     //Set_csi_if(0, 0);
    sensor_if->MCLK(0, 0, handle->mclk);

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

    for(n=0;n<table_length;++n)
    {
        id_from_sensor[n].reg = Sensor_id_table[n].reg;
        id_from_sensor[n].data = 0;
    }

    *id =0;
    if(table_length>8) table_length=8;

    for(n=0;n<4;++n)        //retry , until I2C success
    {
        if(n>2) return FAIL;

        if( SensorRegArrayR((I2C_ARRAY*)id_from_sensor,table_length) == SUCCESS)        //read sensor ID from I2C
        {
            //convert sensor id to u32 format
            for(i=0;i<table_length;++i)
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
            usleep(1*1000);
    }
    SENSOR_IMSG("[%s] %s get sensor id:0x%x, SUCCESS!\n", __FUNCTION__, handle->model_id, ( int )*id);
    return SUCCESS;
}

static int imx323_SetPatternMode(ms_cus_sensor *handle,u32 mode)
{
    SENSOR_DMSG("[%s]\n", __FUNCTION__);
    int i;
    switch(mode)
    {
        case 1:
            PatternTbl[2].data = 0x08;
            PatternTbl[3].data = 0x30;
            PatternTbl[4].data = 0x00;
            PatternTbl[6].data |= 0x01; //enable
            break;
        case 0:
        default:
            PatternTbl[2].data = 0x08;
            PatternTbl[3].data = 0x34;
            PatternTbl[4].data = 0x3C;
            PatternTbl[6].data &= ~0x01; //disable
            break;
    }

    for(i=0;i< ARRAY_SIZE(PatternTbl);i++)
    {
        if(SensorReg_Write(PatternTbl[i].reg,PatternTbl[i].data) != SUCCESS)
        {
            SENSOR_EMSG("[%s:%d]SensorReg_Write fail!!\n", __FUNCTION__, __LINE__);
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
    UartSendTrace("imx323 reg: 0x%x, data: 0x%x, read: 0x%x.\n", usreg, usval, sen_data);

    return SUCCESS;
}

static int pCus_I2CRead(ms_cus_sensor *handle, unsigned short usreg, unsigned short* pusval)
{
    unsigned short usread_data;

    SensorReg_Read(usreg, &usread_data);
    *pusval = usread_data;
    UartSendTrace("imx323 reg: 0x%x, data: 0x%x\n", usreg, usread_data);

    return SUCCESS;
}
#endif

static int pCus_init(ms_cus_sensor *handle)
{
    int i,cnt=0;
#if defined(__MV5_FPGA__IMX323__)
    unsigned short sen_data;
#endif
    ISensorIfAPI *sensor_if = &(handle->sensor_if_api);
    sensor_if->PCLK(CUS_SNR_PCLK_SR_PAD);

    for(i=0;i< ARRAY_SIZE(Sensor_init_table);i++)
    {
        if(Sensor_init_table[i].reg==0xffff)
        {
            usleep(1000*Sensor_init_table[i].data);
        }
        else
        {
            cnt = 0;
            while(SensorReg_Write(Sensor_init_table[i].reg,Sensor_init_table[i].data) != SUCCESS)
            {
                cnt++;
                SENSOR_DMSG("[%s] set Sensor_init_table retry : %d...\n",__FUNCTION__,cnt);
                if(cnt>=10)
                {
                    SENSOR_EMSG("[%s:%d] retry FAIL!!\n", __FUNCTION__, __LINE__);
                    return FAIL;
                }
                usleep(10*1000);
            }
#if defined(__MV5_FPGA__IMX323__)
            SensorReg_Read(Sensor_init_table[i].reg, &sen_data);
            UartSendTrace("imx323 reg: 0x%x, data: 0x%x, read: 0x%x.\n",Sensor_init_table[i].reg, Sensor_init_table[i].data, sen_data);
#endif
        }
    }

    for(i=0;i< ARRAY_SIZE(mirror_reg); i++)
    {
        if(SensorReg_Write(mirror_reg[i].reg,mirror_reg[i].data) != SUCCESS)
        {
          SENSOR_EMSG("[%s:%d] set mirror_reg fail!!\n", __FUNCTION__, __LINE__);
          return FAIL;
        }
    }

    for(i=0;i< ARRAY_SIZE(TriggerStartTbl);i++)
    {
        if(SensorReg_Write(TriggerStartTbl[i].reg,TriggerStartTbl[i].data) != SUCCESS)
        {
            SENSOR_EMSG("[%s:%d] set TriggerStartTbl fail!!\n", __FUNCTION__, __LINE__);
            return FAIL;
        }
    }
    usleep(50*1000);
    pCus_SetAEGain(handle,2048);
    pCus_SetAEUSecs(handle, 25000);

    return SUCCESS;
}

static int pCus_GetVideoResNum( ms_cus_sensor *handle, u32 *ulres_num)
{
    *ulres_num = handle->video_res_supported.num_res;
    return SUCCESS;
}

static int pCus_GetVideoRes(ms_cus_sensor *handle, cus_camsensor_res **res)
{
    SENSOR_DMSG("[%s]\n", __FUNCTION__);
    //return current resolution
    *res = &handle->video_res_supported.res[handle->video_res_supported.ulcur_res];
    return SUCCESS;
}

static int pCus_SetVideoRes(ms_cus_sensor *handle, u32 res)
{
    SENSOR_DMSG("[%s]\n", __FUNCTION__);
    handle->video_res_supported.ulcur_res = 0; //TBD
    //TODO: Set sensor output resolution
    return SUCCESS;
}

static int pCus_GetOrien(ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT *orit)
{
    char sen_data;

    sen_data = mirror_reg[0].data;
    SENSOR_DMSG("[%s] mirror:%x\r\n", __FUNCTION__, sen_data & 0x03);
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
    return SUCCESS;
}

static int pCus_SetOrien(ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT orit)
{
    char index=0;
    imx323_params *params = (imx323_params *)handle->private_data;

    switch(orit)
    {
        case CUS_ORIT_M0F0:
            index = 0;
            break;
        case CUS_ORIT_M1F0:
            index = 1;
            break;
        case CUS_ORIT_M0F1:
            index = 2;
            break;
        case CUS_ORIT_M1F1:
            index = 3;
            break;
    }
    SENSOR_DMSG("[%d] CUS_CAMSENSOR_ORIT orit : %x\r\n",__FUNCTION__, orit);
    if (index != mirror_reg[0].data)
    {
        mirror_reg[0].data = index;
        SensorRegArrayW((I2C_ARRAY*)mirror_reg, sizeof(mirror_reg)/sizeof(I2C_ARRAY));
        params->reg_dirty = true;
    }
    return SUCCESS;
}

static int pCus_GetFPS(ms_cus_sensor *handle)
{
    imx323_params *params = (imx323_params *)handle->private_data;
    //SENSOR_IMSG("[%s] FPS %d\n", __FUNCTION__, params->expo.fps);

    return params->expo.fps;
}

static int pCus_SetFPS(ms_cus_sensor *handle, u32 fps)
{
    //SENSOR_DMSG("[%s]\n", __FUNCTION__);
    imx323_params *params = (imx323_params *)handle->private_data;
    if(fps>=3 && fps <= 30){
        params->expo.fps = fps;
        params->expo.vts=  (vts_30fps*30)/fps;
        //vts_reg[0].data = (params->expo.vts>> 16) & 0x0003;
        vts_reg[0].data = (params->expo.vts >> 8) & 0x00ff;
        vts_reg[1].data = (params->expo.vts >> 0) & 0x00ff;
        params->reg_dirty = true; //reg need to update = true;
        //printf("Set FPS =%d\n",fps);
        return SUCCESS;
    }else if(fps>=3000 && fps <= 30000){
        params->expo.fps = fps;
        params->expo.vts=  (vts_30fps*30000)/fps;
        vts_reg[0].data = (params->expo.vts >> 8) & 0x00ff;
        vts_reg[1].data = (params->expo.vts >> 0) & 0x00ff;
        params->reg_dirty = true;
        //printf("Set FPS =%d\n",fps);
        return SUCCESS;
    }else{
        //SENSOR_DMSG("[%s] FPS %d out of range.\n",__FUNCTION__,fps);
        return FAIL;
    }
}
static int pCus_GetSensorCap(ms_cus_sensor *handle, CUS_CAMSENSOR_CAP *cap)
{
    SENSOR_DMSG("[%s]\n", __FUNCTION__);
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
    SENSOR_DMSG("[%s]\n", __FUNCTION__);
  imx323_params *params = (imx323_params *)handle->private_data;
  switch(status)
  {
    case CUS_FRAME_INACTIVE:
      //SensorReg_Write(0x3001,0);
      break;
    case CUS_FRAME_ACTIVE:
      if(params->reg_dirty)
      {
        SensorRegArrayW((I2C_ARRAY*)expo_reg, sizeof(expo_reg)/sizeof(I2C_ARRAY));
        SensorRegArrayW((I2C_ARRAY*)gain_reg, sizeof(gain_reg)/sizeof(I2C_ARRAY));
        SensorRegArrayW((I2C_ARRAY*)vts_reg, sizeof(vts_reg)/sizeof(I2C_ARRAY));
        params->reg_dirty = false;
      }
      break;
    default :
      break;
  }
  return SUCCESS;
}

static int pCus_GetAEUSecs(ms_cus_sensor *handle, u32 *us)
{
#if 0
  int rc;
  u32 lines = 0;
  rc = SensorRegArrayR((I2C_ARRAY*)expo_reg, ARRAY_SIZE(expo_reg));
  lines |= (u32)(expo_reg[0].data&0xff)<<8;
  lines |= (u32)(expo_reg[1].data&0xff)<<0;
  *us = lines;//(lines*Preview_line_period);
  return rc;
#else
  imx323_params *params = (imx323_params *)handle->private_data;
  *us = params->shutter_us;
  return 0;
#endif
}

static int pCus_SetAEUSecs(ms_cus_sensor *handle, u32 us)
{
  u32 lines = 0, vts = 0;
  imx323_params *params = (imx323_params *)handle->private_data;
  params->shutter_us = us;
  lines=(1000*us)/Preview_line_period;
  if(lines<1)
    lines=1;

  if (lines >params->expo.vts-1)
  {
    vts = lines +1;
  }
  else
  {
    vts=params->expo.vts;
  }

  // lines=us/Preview_line_period;
  SENSOR_DMSG("[%s] us %ld, lines %ld, vts %ld\n", __FUNCTION__,
      us,
      lines,
      params->expo.vts
  );
  lines=vts-lines-1;

  expo_reg[0].data = (lines>>8) & 0x00ff;
  expo_reg[1].data = (lines>>0) & 0x00ff;

  vts_reg[0].data = (vts >> 8) & 0x00ff;
  vts_reg[1].data = (vts >> 0) & 0x00ff;

  params->reg_dirty = true; //reg need to update
  return SUCCESS;
}

// Gain: 1x = 1024
static int pCus_GetAEGain(ms_cus_sensor *handle, u32* gain)
{
  int rc = SensorRegArrayR((I2C_ARRAY*)gain_reg, ARRAY_SIZE(gain_reg));
  u16 temp_gain;
  double temp_gain_double;
  temp_gain=gain_reg[0].data;
  temp_gain_double=((double)(temp_gain*3)/200.0f);
  *gain=(u32)(pow(10,temp_gain_double)*1024);

  SENSOR_DMSG("[%s] get gain/reg (1024=1X)= 0x%x/0x%x\n", __FUNCTION__, *gain,gain_reg[0].data);
  return rc;
}

static int pCus_SetAEGain_cal(ms_cus_sensor *handle, u32 gain)
{
    imx323_params *params = (imx323_params *)handle->private_data;
    double gain_double;
    params->expo.final_gain = gain;

    if(gain < SENSOR_MIN_GAIN)
        gain = SENSOR_MIN_GAIN;
    else if(gain >= SENSOR_MAX_GAIN)
        gain = SENSOR_MAX_GAIN;

    gain_double = 20*log10((double)gain/1024);
    gain_reg[0].data=(u16)((gain_double*10)/3);
    params->reg_dirty = true;    //reg need to update

    SENSOR_DMSG("[%s] set gain/reg=0x%x/0x%x\n", __FUNCTION__, gain,gain_reg[0].data);
    return SUCCESS;
}

static int pCus_SetAEGain(ms_cus_sensor *handle, u32 gain)
{
  imx323_params *params = (imx323_params *)handle->private_data;
  u32 gain2_4,gain4_8,gain8_16,gain16_32,i, sensor_DataH, sensor_DataL;
  CUS_GAIN_GAP_ARRAY* Sensor_Gain_Linearity;
  double gain_double;

  if(gain<1024)
    gain=1024;
  else if(gain>=177*1024)
    gain=177*1024;

  Sensor_Gain_Linearity = gain_gap_compensate;

  for(i = 0; i < sizeof(gain_gap_compensate)/sizeof(CUS_GAIN_GAP_ARRAY); i++){
    if (Sensor_Gain_Linearity[i].gain == 0)
      break;
    if((gain>Sensor_Gain_Linearity[i].gain) && (gain < (Sensor_Gain_Linearity[i].gain + Sensor_Gain_Linearity[i].offset))){
      gain=Sensor_Gain_Linearity[i].gain;
      break;
    }
  }

  gain = (gain * handle->sat_mingain+512)>>10;
  params->expo.final_gain = gain;
  gain_double = 20*log10((double)gain/1024);
  gain_reg[0].data=(u16)((gain_double*10)/3);
  params->reg_dirty = true;    //reg need to update
  SENSOR_DMSG("[%s] set gain/reg=0x%x/0x%x\n", __FUNCTION__, gain,gain_reg[0].data);
  return SUCCESS;
}

static int pCus_GetAEMinMaxUSecs(ms_cus_sensor *handle, u32 *min, u32 *max)
{
  *min = 150;
  *max = 33332; // <- max shutter (30fps: 33332, 60fps:16666)
  return SUCCESS;
}

static int pCus_GetAEMinMaxGain(ms_cus_sensor *handle, u32 *min, u32 *max)
{
    SENSOR_DMSG("[%s]\n", __FUNCTION__);
    *min = SENSOR_MIN_GAIN;//1024;
    *max = SENSOR_MAX_GAIN;//177*1024;
    return SUCCESS;
}

static int pCus_GetDGainRemainder(ms_cus_sensor *handle, u32 *dgain_remainder)
{
    *dgain_remainder = handle->dgain_remainder;

    return SUCCESS;
}

static int pCus_setCaliData_gain_linearity(ms_cus_sensor* handle, CUS_GAIN_GAP_ARRAY* pArray, u32 num)
{
    u32 i, j;

    for(i=0,j=0;i< num ;i++,j+=2)
    {
        gain_gap_compensate[i].gain=pArray[i].gain;
        gain_gap_compensate[i].offset=pArray[i].offset;
    }
    SENSOR_DMSG("[%s]%d, %d, %d, %d\n", __FUNCTION__, num, pArray[0].gain, pArray[1].gain, pArray[num-1].offset);
    return SUCCESS;
}

static int IMX323_GetShutterInfo(struct __ms_cus_sensor* handle,CUS_SHUTTER_INFO *info)
{
    info->max = 1000000000/Preview_MIN_FPS;
    info->min = Preview_line_period * 5;
    info->step = Preview_line_period;
    return SUCCESS;
}

int imx323_cus_camsensor_init_handle(ms_cus_sensor* handle)
{
#if defined(__RTK_OS__)
    CamOsRet_e                  eCamOsRet = CAM_OS_OK;
    void*                       pvBufVirt = NULL;
    u64                 u64BufPhy = 0;
    u64                 u64BufMiu = 0;
    u8                   str[20];
#endif

    if (!handle)
    {
        SENSOR_EMSG("[%s] not enough memory!\n", __FUNCTION__);
        return FAIL;
    }
    SENSOR_DMSG("[%s]\n", __FUNCTION__);
    //private data allocation & init
#if defined(__RTK_OS__)
    sprintf(str, "IMX323linear");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(imx323_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (imx323_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(imx323_params));
#else
    handle->private_data = calloc( 1, sizeof(imx323_params) );
#endif
    imx323_params *params = (imx323_params *)handle->private_data;

    ////////////////////////////////////
    //    sensor model ID                           //
    ////////////////////////////////////
    sprintf(handle->model_id,"IMX323_PARL");

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
    #if defined(__MV5_FPGA__IMX323__) //15 FPS.
    handle->video_res_supported.res[0].nOutputWidth= 2178;
    handle->video_res_supported.res[0].nOutputHeight= 1100;
    #else //30 FPS
    handle->video_res_supported.res[0].nOutputWidth= 2084;
    handle->video_res_supported.res[0].nOutputHeight= 1163;
    #endif

    // i2c
    handle->i2c_cfg.mode                = SENSOR_I2C_LEGACY;    //(CUS_ISP_I2C_MODE) FALSE;
    handle->i2c_cfg.fmt                 = SENSOR_I2C_FMT;       //CUS_I2C_FMT_A16D16;
    handle->i2c_cfg.address             = SENSOR_I2C_ADDR;      //0x5a;
    handle->i2c_cfg.speed               = SENSOR_I2C_SPEED;     //200000;
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
    /////////////////////////////////////////////////////



    ////////////////////////////////////////////////////
    // AE parameters
    ////////////////////////////////////////////////////
    handle->ae_gain_delay       = SENSOR_GAIN_DELAY_FRAME_COUNT;//0;//1;
    handle->ae_shutter_delay    = SENSOR_SHUTTER_DELAY_FRAME_COUNT;//1;//2;

    ///calibration
    handle->sat_mingain = SENSOR_MIN_GAIN;//g_sensor_ae_min_gain;
    handle->dgain_remainder = 0;
    handle->pCus_sensor_release     = imx323_cus_camsensor_release_handle;
    handle->pCus_sensor_init        = pCus_init    ;
    handle->pCus_sensor_poweron     = pCus_poweron ;
    handle->pCus_sensor_poweroff    = pCus_poweroff;

    // Normal
    handle->pCus_sensor_GetSensorID       = pCus_GetSensorID   ;
    handle->pCus_sensor_GetVideoResNum = pCus_GetVideoResNum;
    handle->pCus_sensor_GetVideoRes       = pCus_GetVideoRes   ;
    handle->pCus_sensor_SetVideoRes       = pCus_SetVideoRes   ;
    handle->pCus_sensor_GetOrien          = pCus_GetOrien      ;
    handle->pCus_sensor_SetOrien          = pCus_SetOrien      ;
    handle->pCus_sensor_GetFPS          = pCus_GetFPS      ;
    handle->pCus_sensor_SetFPS          = pCus_SetFPS      ;
    handle->pCus_sensor_GetSensorCap    = pCus_GetSensorCap;
    handle->pCus_sensor_SetPatternMode = imx323_SetPatternMode;
    ///////////////////////////////////////////////////////
    // AE
    ///////////////////////////////////////////////////////
    // unit: micro seconds
    handle->pCus_sensor_AEStatusNotify = pCus_AEStatusNotify;
    handle->pCus_sensor_GetAEUSecs      = pCus_GetAEUSecs;
    handle->pCus_sensor_SetAEUSecs      = pCus_SetAEUSecs;
    handle->pCus_sensor_GetAEGain       = pCus_GetAEGain;
    handle->pCus_sensor_SetAEGain_cal   = pCus_SetAEGain_cal;
    handle->pCus_sensor_SetAEGain       = pCus_SetAEGain;
    handle->pCus_sensor_GetShutterInfo = IMX323_GetShutterInfo;

    handle->pCus_sensor_GetAEMinMaxGain = pCus_GetAEMinMaxGain;
    handle->pCus_sensor_GetAEMinMaxUSecs= pCus_GetAEMinMaxUSecs;
    handle->pCus_sensor_GetDGainRemainder = pCus_GetDGainRemainder;

    //sensor calibration
    handle->pCus_sensor_setCaliData_gain_linearity=pCus_setCaliData_gain_linearity;
#if 1//defined(__MV5_FPGA__)
    handle->pCus_sensor_I2CWrite = pCus_I2CWrite; //Andy Liu
    handle->pCus_sensor_I2CRead = pCus_I2CRead; //Andy Liu
#endif
    params->expo.vts=vts_30fps;
    params->expo.fps = 30;
    params->reg_dirty = false;
    params->shutter_us = 0;

    handle->snr_pad_group = SENSOR_PAD_GROUP_SET;

    handle->channel_num = SENSOR_CHANNEL_NUM;
    handle->channel_mode = SENSOR_CHANNEL_MODE;



    return SUCCESS;
}

int imx323_cus_camsensor_release_handle(ms_cus_sensor *handle)
{
#if defined(__RTK_OS__)
    CamOsRet_e                  eCamOsRet = CAM_OS_OK;
#endif

    SENSOR_DMSG("[%s]\n", __FUNCTION__);
    if (handle && handle->private_data)
    {
        SENSOR_IMSG("[%s] release handle 0x%x, private data %x\n",__FUNCTION__,(int)handle,(int)handle->private_data);
#if defined(__RTK_OS__)
        eCamOsRet = CamOsDirectMemRelease((void*)handle->private_data, sizeof(imx323_params));
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
struct SensorMapTable_t gsensor_map_imx323 = {
    SENSOR_CHANNEL_NUM,
    imx323_cus_camsensor_init_handle,
    imx323_cus_camsensor_release_handle
};

int IMX323_Module_Init(void)
{
    cameraSensorRegister(&gsensor_map_imx323);

    return 0;
}

void IMX323_Module_Exit(void)
{
    cameraSensorUnRegister(&gsensor_map_imx323);
}

#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(IMX323_Module_Init);
//ait_module_exit(IMX323_Module_Exit);
#endif //#if defined(__RTK_OS__)

#endif //#if defined(BIND_SENSOR_IMX323) && (BIND_SENSOR_IMX323 == 1)
