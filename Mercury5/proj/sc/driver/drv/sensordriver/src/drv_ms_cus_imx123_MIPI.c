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
#if (SENSOR0 == IMX123_MIPI)
#define BIND_SENSOR_IMX123_MIPI (1)
#endif
#endif //#if defined(__RTK_OS__)

#if defined(BIND_SENSOR_IMX123_MIPI) && (BIND_SENSOR_IMX123_MIPI == 1)

#define SENSOR_PAD_GROUP_SET CUS_SENSOR_PAD_GROUP_A
#define SENSOR_CHANNEL_NUM (0)
#define SENSOR_CHANNEL_MODE CUS_SENSOR_CHANNEL_MODE_REALTIME_NORMAL

//============================================
//MIPI config begin.
#define SENSOR_MIPI_LANE_NUM (2)
//MIPI config end.
//============================================

//c11 extern int usleep(u32 usec);

#define R_GAIN_REG 1
#define G_GAIN_REG 2
#define B_GAIN_REG 3

#define SENSOR_ISP_TYPE     ISP_EXT                   //ISP_EXT, ISP_SOC
#define F_number  22                                  // CFG, demo module
//#define SENSOR_DATAFMT      CUS_DATAFMT_BAYER        //CUS_DATAFMT_YUV, CUS_DATAFMT_BAYER
#define SENSOR_IFBUS_TYPE   CUS_SENIF_BUS_MIPI      //CFG //CUS_SENIF_BUS_PARL, CUS_SENIF_BUS_MIPI
#define SENSOR_MIPI_HSYNC_MODE PACKET_HEADER_EDGE1
#define SENSOR_MIPI_DELAY   0x1212                  //CFG
#define SENSOR_DATAPREC     CUS_DATAPRECISION_12    //CFG //CUS_DATAPRECISION_8, CUS_DATAPRECISION_10
#define SENSOR_DATAMODE     CUS_SEN_10TO12_9098     //CFG
#define SENSOR_BAYERID      CUS_BAYER_RG            //CFG //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
#define SENSOR_ORIT         CUS_ORIT_M0F0           //CUS_ORIT_M0F0, CUS_ORIT_M1F0, CUS_ORIT_M0F1, CUS_ORIT_M1F1,
//#define SENSOR_YCORDER      CUS_SEN_YCODR_YC       //CUS_SEN_YCODR_YC, CUS_SEN_YCODR_CY
//#define SENSOR_MAX_GAIN     350                  // max sensor again, a-gain * conversion-gain*d-gain//51db
//#define SENSOR_MAX_GAIN     1412                  // max sensor again, a-gain * conversion-gain*d-gain*expand gain//63db
#define lane_number 2
#define vc0_hs_mode 3   //0: packet header edge  1: line end edge 2: line start edge 3: packet footer edge
#define long_packet_type_enable 0x00 //UD1~UD8 (user define)
#define SENSOR_MAX_GAIN     (1.37 * 1024) //1412                 // max sensor again, a-gain * conversion-gain*d-gain
#define SENSOR_MIN_GAIN      (1 * 1024)
#define SENSOR_GAIN_DELAY_FRAME_COUNT      (2)
#define SENSOR_SHUTTER_DELAY_FRAME_COUNT      (2)

#define Preview_MCLK_SPEED  CUS_CMU_CLK_27MHZ        //CFG //CUS_CMU_CLK_12M, CUS_CMU_CLK_16M, CUS_CMU_CLK_24M, CUS_CMU_CLK_27M
#define Preview_line_period  20513                  ////HTS/PCLK=1600 pixels/78MHZ=20.513usec
#define Prv_Max_line_number 1536                    //maximum exposure line munber of sensor when preview
#define vts_30fps 1625//                      //for 29.1fps
#define Preview_WIDTH       2048                    //resolution Width when preview
#define Preview_HEIGHT      1536                    //resolution Height when preview
#define Preview_MAX_FPS     30                     //fastest preview FPS
#define Preview_MIN_FPS     8                      //slowest preview FPS
#define Preview_CROP_START_X     0                      //CROP_START_X
#define Preview_CROP_START_Y     1                      //CROP_START_Y
#define Sensor_MAX_WIDTH   2048                    //sensor max resolution Width
#define Sensor_MAX_HEIGHT  1552                    //sensor max resolution Height

#define SENSOR_I2C_ADDR     0x34                        //I2C slave address
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
//static int  drv_Fnumber = 22;

static int pCus_SetAEGain(ms_cus_sensor *handle, u32 gain);
static int pCus_SetAEUSecs(ms_cus_sensor *handle, u32 us);
int imx123_MIPI_cus_camsensor_release_handle(ms_cus_sensor *handle);

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
} imx123_params;
// set sensor ID address and data,

static I2C_ARRAY Sensor_id_table[] =
{
    {0x3004, 0x10},      // {address of ID, ID },
    {0x3005, 0x02},
};

static I2C_ARRAY Sensor_init_table[] =
{
    {0x3002, 0x01},   //Master mode stop
    //{0xffff, 0x14},//delay
    {0x3000, 0x01},   // standby
    //{0xffff, 0x14},//delay
    {0x3009, 0x02},//FRSEL
    {0x3012, 0x0E},
    {0x3013, 0x01},
    {0x3018, 0x59},//1625,VMAX
    {0x3019, 0x06},
    {0x301B, 0x40},//1600  HMAX
    {0x301C, 0x06},
    {0x3044, 0x22},
    {0x3049, 0x0A},
    {0x3061, 0x31},
    {0x3062, 0x00},
    {0x309D, 0x82},
    {0x309F, 0x01},
    {0x30B3, 0x91},

    {0x3103, 0x58},//0x58:from NICK, 0x3F from EXCEL
    {0x3104, 0x06},//
    {0x3106, 0x07},
    {0x3107, 0x00},
    {0x3108, 0x00},
    {0x3109, 0x00},
    {0x310A, 0x00},
    {0x310B, 0x00},
    {0x3110, 0xF2},
    {0x3111, 0x03},
    {0x3112, 0xEB},
    {0x3113, 0x07},
    {0x3114, 0xED},
    {0x3115, 0x07},
    {0x3126, 0x91},
    {0x3130, 0x4D},
    {0x3133, 0x12},
    {0x3134, 0x10},
    {0x3135, 0x12},
    {0x3136, 0x10},
    {0x313A, 0x0C},
    {0x313B, 0x0C},
    {0x313C, 0x0C},
    {0x313D, 0x0C},
    {0x3140, 0x00},
    {0x3141, 0x00},
    {0x3144, 0x1E},
    {0x3149, 0x55},
    {0x314B, 0x99},
    {0x314C, 0x99},
    {0x3154, 0xE7},
    {0x315A, 0x04},
    {0x316D, 0x09},
    {0x3170, 0x60},
    {0x3171, 0x1A},
    {0x3179, 0x94},
    {0x317A, 0x06},
    {0x31EB, 0x44},

    {0x3201, 0x3C},
    {0x3202, 0x01},
    {0x3203, 0x0E},
    {0x3213, 0x05},
    {0x321F, 0x05},
    {0x325F, 0x03},
    {0x3269, 0x03},
    {0x32B6, 0x03},
    {0x32BA, 0x01},
    {0x32C4, 0x01},
    {0x32CB, 0x01},
    {0x32D9, 0x80},
    {0x32DC, 0xB0},
    {0x32DD, 0x13},

    {0x332A, 0xFF},
    {0x332B, 0xFF},
    {0x332C, 0xFF},
    {0x332D, 0xFF},
    {0x332E, 0xFF},
    {0x332F, 0xFF},
    {0x3335, 0x50},
    {0x3336, 0x80},
    {0x3337, 0x1B},
    {0x333C, 0x01},
    {0x333D, 0x03},

    {0x3504, 0x0C},
    {0x3505, 0x0C},
    {0x350B, 0x01},
    {0x3517, 0x1B},
    {0x3016, 0x89},//normal mode:0x09, expand mode:0x89
    {0x3012, 0x86},//normal mode:0x0E, expand mode:0x86

    {0x3000, 0x00},   // operating
    {0xffff, 0x14},

};

static I2C_ARRAY TriggerStartTbl[] =
{
    {0x3002,0x00},//Master mode start
};

static I2C_ARRAY Current_Mirror_Flip_Tbl[] =
{
    {0x3007, 0x00},//M0F0
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


static I2C_ARRAY mirr_flip_table[] =
{
    {0x3007, 0x00},//M0F0
    {0x3007, 0x02},//M1F0
    {0x3007, 0x01},//M0F1
    {0x3007, 0x03},//M1F1

};

typedef struct {
    short reg;
    char startbit;
    char stopbit;
} COLLECT_REG_SET;



static I2C_ARRAY gain_reg[] =
{
    {0x3014, 0x00},//low byte
    {0x3015, 0x00},//high bit 0,1
    // {0x3016, 0x09},//normal mode:0x09, expand mode:0x89
    // {0x3012, 0x0E},//normal mode:0x0E, expand mode:0x86
    //{0x3016, 0x01},//normal mode:0x01, expand mode:0x01
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
    {0x3020, 0x00},//bit0->MSB
    {0x301F, 0x00},
    {0x301E, 0x00},
};

static I2C_ARRAY vts_reg[] =
{
    {0x301a, 0x00},//bit0-->MSB
    {0x3019, 0x18},
    {0x3018, 0x10},
};

static I2C_ARRAY PatternTbl[] =
{
    //pattern mode
    {0x3096,0xFF},  //PGDATA1 [7:0]
    {0x3097,0x0F},  //PGDATA1 [14:8]
    {0x3098,0x00},  //PGDATA2 [7:0]
    {0x3099,0x00},  //PGDATA2 [14:8]
    {0x309A,0x00},  //colorbar width
    {0x308C,0x20} //[1]:pattern gen enable , [4:7]:pattern select
};
/*
static CUS_INT_TASK_ORDER def_order =
{
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
};*/

/////////////////// sensor hardware dependent //////////////
static int pCus_poweron(ms_cus_sensor *handle)
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;

    //Sensor power on sequence
    sensor_if->SetIOPad(SENSOR_PAD_GROUP_SET, CUS_SENIF_BUS_MIPI, CUS_SR0_MIPI_MODE_1);
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_216M, handle->PCLK_POLARITY);
    sensor_if->SetCSI_Lane(SENSOR_PAD_GROUP_SET, 2, 1);
    sensor_if->SetCSI_VC0HSmode(PACKET_FOOTER_EDGE);
    sensor_if->SetCSI_LongPacketType(CSI_LONG_PACKET_TYPE_RAW12|CSI_LONG_PACKET_TYPE_RAW10);
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

    // pure power on
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, !handle->pwdn_POLARITY);
	sensor_if->SWReset(handle->channel_num, FALSE);
    return SUCCESS;
}

static int pCus_poweroff(ms_cus_sensor *handle)
{
    // power/reset low
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    SENSOR_DMSG("[%s] power low\n", __FUNCTION__);
	sensor_if->SWReset(handle->channel_num, TRUE);
    sensor_if->PowerOff(1, handle->pwdn_POLARITY);

    usleep(1000);
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_DISABLE, handle->PCLK_POLARITY);//Set_csi_if(0, 0);
    sensor_if->MCLK(0, 0, handle->mclk);
    sensor_if->SetCSI_Lane(SENSOR_PAD_GROUP_SET, 2, 0);
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
            usleep(1*1000);
    }
    SENSOR_IMSG("[%s] %s get sensor id:0x%x, SUCCESS!\n", __FUNCTION__, handle->model_id, ( int )*id);
    return SUCCESS;
}

static int imx123_SetPatternMode(ms_cus_sensor *handle,u32 mode)
{
    SENSOR_DMSG("[%s]\n", __FUNCTION__);
    int i;
    switch(mode)
    {
        case 1:
            PatternTbl[5].data |= 0x01; //enable
            break;
        case 0:
            PatternTbl[5].data &= 0xFE; //disable
            break;
        default:
            PatternTbl[5].data &= 0xFE; //disable
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

static int pCus_SetFPS(ms_cus_sensor *handle, u32 fps);
static int pCus_SetAEGain_cal(ms_cus_sensor *handle, u32 gain);
static int pCus_AEStatusNotify(ms_cus_sensor *handle, CUS_CAMSENSOR_AE_STATUS_NOTIFY status);

#if 1//defined(__MV5_FPGA__)
static int pCus_I2CWrite(ms_cus_sensor *handle, unsigned short usreg, unsigned short usval)
{
    unsigned short sen_data;

    SensorReg_Write(usreg, usval);
    SensorReg_Read(usreg, &sen_data);
    UartSendTrace("imx123_MIPI reg: 0x%x, data: 0x%x, read: 0x%x.\n", usreg, usval, sen_data);

    return SUCCESS;
}

static int pCus_I2CRead(ms_cus_sensor *handle, unsigned short usreg, unsigned short* pusval)
{
    unsigned short usread_data;

    SensorReg_Read(usreg, &usread_data);
    *pusval = usread_data;
    UartSendTrace("imx123_MIPI reg: 0x%x, data: 0x%x\n", usreg, usread_data);

    return SUCCESS;
}
#endif

static int pCus_init(ms_cus_sensor *handle)
{
    int i,cnt=0;
    ISensorIfAPI *sensor_if = &(handle->sensor_if_api);
    sensor_if->PCLK(CUS_SNR_PCLK_MIPI_TOP);

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
        }
    }

    /*
    for(i=0;i< ARRAY_SIZE(PatternTbl);i++)
    {
        if(SensorReg_Write(PatternTbl[i].reg,PatternTbl[i].data) != SUCCESS)
        {
            //MSG("[%s:%d]Sensor init fail!!\n", __FUNCTION__, __LINE__);
            return FAIL;
        }
    }
    */
    SensorRegArrayW(vts_reg,ARRAY_SIZE(vts_reg)); //set vts

    for(i=0;i< ARRAY_SIZE(TriggerStartTbl);i++)
    {
        if(SensorReg_Write(TriggerStartTbl[i].reg,TriggerStartTbl[i].data) != SUCCESS)
        {
            SENSOR_EMSG("[%s:%d] set TriggerStartTbl fail!!\n", __FUNCTION__, __LINE__);
            return FAIL;
        }
    }

    for(i=0;i< ARRAY_SIZE(Current_Mirror_Flip_Tbl); i++)
    {
        if(SensorReg_Write(Current_Mirror_Flip_Tbl[i].reg,Current_Mirror_Flip_Tbl[i].data) != SUCCESS)
        {
            SENSOR_EMSG("[%s:%d] set Current_Mirror_Flip_Tbl fail!!\n", __FUNCTION__, __LINE__);
            return FAIL;
        }

    }

    usleep(50*1000);
    //pCus_SetFPS(handle,20);
    pCus_SetAEGain(handle,1024);
    pCus_SetAEUSecs(handle, 7000);
    pCus_AEStatusNotify(handle,CUS_FRAME_ACTIVE);
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
    return SUCCESS;
}

static int pCus_GetOrien(ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT *orit)
{
    short sen_data;

    SensorReg_Read(0x3007, &sen_data);//always success now

    SENSOR_DMSG("[%s] mirror:%x\r\n",__FUNCTION__, sen_data & 0x03);
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
    int table_length = ARRAY_SIZE(mirr_flip_table);
    int seg_length=table_length/4;
    int i,j;

    switch(orit)
    {
        case CUS_ORIT_M0F0:
            for(i=0,j=0;i<seg_length;i++,j++)
            {
                SensorReg_Write(mirr_flip_table[i].reg,mirr_flip_table[i].data);
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }
           //  handle->bayer_id=    CUS_BAYER_BG;
            break;

        case CUS_ORIT_M1F0:
            for(i=seg_length,j=0;i<seg_length*2;i++,j++)
            {
                SensorReg_Write(mirr_flip_table[i].reg,mirr_flip_table[i].data);
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }
        //  handle->bayer_id=   CUS_BAYER_BG;
            break;

        case CUS_ORIT_M0F1:
            for(i=seg_length*2,j=0;i<seg_length*3;i++,j++)
            {
                SensorReg_Write(mirr_flip_table[i].reg,mirr_flip_table[i].data);
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }
         // handle->bayer_id=   CUS_BAYER_GR;
            break;

        case CUS_ORIT_M1F1:
            for(i=seg_length*3,j=0;i<seg_length*4;i++,j++)
            {
                SensorReg_Write(mirr_flip_table[i].reg,mirr_flip_table[i].data);
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }
         // handle->bayer_id=   CUS_BAYER_GR;
            break;

        default :
            for(i=0,j=0;i<seg_length;i++,j++)
            {
                SensorReg_Write(mirr_flip_table[i].reg,mirr_flip_table[i].data);
                Current_Mirror_Flip_Tbl[j].reg = mirr_flip_table[i].reg;
                Current_Mirror_Flip_Tbl[j].data = mirr_flip_table[i].data;
            }
        //  handle->bayer_id=   CUS_BAYER_BG;
            break;
    }
    SENSOR_DMSG("[%s] CUS_CAMSENSOR_ORIT orit : %x\r\n",__FUNCTION__, orit);
    return SUCCESS;
}

static int pCus_GetFPS(ms_cus_sensor *handle)
{
    imx123_params *params = (imx123_params *)handle->private_data;
    SENSOR_IMSG("[%s] FPS %d\n", __FUNCTION__, params->expo.fps);

    return params->expo.fps;
}

static int pCus_SetFPS(ms_cus_sensor *handle, u32 fps)
{
    imx123_params *params = (imx123_params *)handle->private_data;
    SENSOR_DMSG("\n\n[%s]", __FUNCTION__);
    if(fps>=2 && fps <= 30)
    {
      params->expo.fps = fps;
      params->expo.vts=  (vts_30fps*30)/fps;
      vts_reg[0].data = (params->expo.vts>> 16) & 0x0001;
      vts_reg[1].data = (params->expo.vts >> 8) & 0x00ff;
      vts_reg[2].data = (params->expo.vts >> 0) & 0x00ff;
      return SUCCESS;
    }
    else if(fps>=2000 && fps <= 30000)
    {
        params->expo.fps = fps;
        params->expo.vts=  (vts_30fps*30000)/fps;
        vts_reg[0].data = (params->expo.vts>> 16) & 0x0001;
        vts_reg[1].data = (params->expo.vts >> 8) & 0x00ff;
        vts_reg[2].data = (params->expo.vts >> 0) & 0x00ff;
        return SUCCESS;
    }
    else
    {
      //params->expo.vts=vts_30fps;
      //params->expo.fps=30;
      SENSOR_DMSG("[%s] FPS %d out of range.\n",fps,__FUNCTION__);
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
    imx123_params *params = (imx123_params *)handle->private_data;
    switch(status)
    {
        case CUS_FRAME_INACTIVE:
            //SensorReg_Write(0x3001,0);
            break;
        case CUS_FRAME_ACTIVE:
            if(params->dirty)
            {
              //  SensorReg_Write(0x3001,1);
              //  SensorRegArrayW((I2C_ARRAY*)expo_reg, ARRAY_SIZE(expo_reg));
               // SensorRegArrayW((I2C_ARRAY*)gain_reg, ARRAY_SIZE(gain_reg));
                //SensorRegArrayW((I2C_ARRAY*)vts_reg, ARRAY_SIZE(vts_reg));
                SensorReg_Write(0x3001,0);
                params->dirty = false;
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

    lines |= (u32)(expo_reg[0].data&0xff)<<16;
    lines |= (u32)(expo_reg[1].data&0xff)<<8;
    lines |= (u32)(expo_reg[2].data&0xff)<<0;
    // lines >>= 4;
    // *us = (lines+dummy) * params->expo.us_per_line;
    //*us = lines;//(lines*Preview_line_period);
    *us = lines*Preview_line_period/1000;
    SENSOR_DMSG("[%s] sensor expo lines/us 0x%x,0x%x us\n", __FUNCTION__, lines, *us);
    return SUCCESS;
}

static int pCus_SetAEUSecs(ms_cus_sensor *handle, u32 us)
{
    u32 lines = 0, vts = 0;
    imx123_params *params = (imx123_params *)handle->private_data;
    // us = 1000000/30;

    // if( params->dirty_fps == true)
    // return SUCCESS;

    lines=(1000*us)/Preview_line_period;
    if (lines >params->expo.vts-4)
    {
        vts = lines +4;
    }
    else
        vts=params->expo.vts;

    // lines=us/Preview_line_period;
    SENSOR_DMSG("[%s] us %ld, lines %ld, vts %ld\n", __FUNCTION__,us,lines,params->expo.vts);
    lines=vts-lines;
    expo_reg[0].data = (lines>>16) & 0x0001;
    expo_reg[1].data = (lines>>8) & 0x00ff;
    expo_reg[2].data = (lines>>0) & 0x00ff;

    vts_reg[0].data = (vts >> 16) & 0x0001;
    vts_reg[1].data = (vts >> 8) & 0x00ff;
    vts_reg[2].data = (vts >> 0) & 0x00ff;
    SensorReg_Write(0x3001,1);
    SensorRegArrayW((I2C_ARRAY*)expo_reg, ARRAY_SIZE(expo_reg));
    SensorRegArrayW((I2C_ARRAY*)gain_reg, ARRAY_SIZE(gain_reg));
    SensorRegArrayW((I2C_ARRAY*)vts_reg, ARRAY_SIZE(vts_reg));
    params->dirty = true;
    return SUCCESS;
}

// Gain: 1x = 1024
static int pCus_GetAEGain(ms_cus_sensor *handle, u32* gain)
{
    //int rc = SensorRegArrayR((I2C_ARRAY*)gain_reg, ARRAY_SIZE(gain_reg));
    u16  temp_gain;
    double  temp_gain_double;

    temp_gain=(gain_reg[0].data)|((gain_reg[1].data)<<8);
    temp_gain_double=((double)temp_gain/200.0f);
    *gain=(u32)(pow(10,temp_gain_double)*1024);

    SENSOR_DMSG("[%s] get gain/regL/regH (1024=1X)= %d/0x%x/0x%x\n", __FUNCTION__, *gain,gain_reg[0].data,gain_reg[1].data);
    return SUCCESS;
}

static int pCus_SetAEGain_cal(ms_cus_sensor *handle, u32 gain)
{
    imx123_params *params = (imx123_params *)handle->private_data;
    u16 gain16;
    double gain_double;
    params->expo.final_gain = gain;

    if(gain < SENSOR_MIN_GAIN)
        gain = SENSOR_MIN_GAIN;
    else if(gain >= SENSOR_MAX_GAIN)
        gain = SENSOR_MAX_GAIN;
    /*
    if(gain>=2048)//if gain exceed 2x , enable high conversion gain
    {
        gain_reg[1].data |= 0x10;
        gain /= 2;
    }
    else
        gain_reg[1].data &= ~0x10;
    */
    gain_double = 20*log10((double)gain/1024);
    gain16=(u16)(gain_double*10);
    /*    if(gain16>512)//enable gain expand mode
    {
        gain_reg[2].data=0x89;
        gain_reg[3].data=0x86;
    }
    else
    {
        gain_reg[2].data=0x09;
        gain_reg[3].data=0x0E;
    }*/
    gain_reg[1].data=(gain16>>8)&0x03;//bit 0-->MSB
    gain_reg[0].data=gain16&0xff;//low byte,LSB

    SENSOR_DMSG("[%s] set gain/reg0/reg1=%ld/0x%x/0x%x\n", __FUNCTION__, gain,gain_reg[0].data,gain_reg[1].data);
    params->dirty = true;
    return SUCCESS;
}

static int pCus_SetAEGain(ms_cus_sensor *handle, u32 gain)
{
    //extern DBG_ITEM Dbg_Items[DBG_TAG_MAX];
    imx123_params *params = (imx123_params *)handle->private_data;
    u32 i;
    double gain_double;
    CUS_GAIN_GAP_ARRAY* Sensor_Gain_Linearity;
    // double gain_double;
    u16 gain16;
    // if( params->dirty_fps == true)
    // return SUCCESS;
    // u32 times = log2((double)gain/1024.0f)/log(2);
    params->expo.final_gain = gain;
    if(gain<1024)
        gain=1024;
    else if(gain>=SENSOR_MAX_GAIN*1024)
        gain=SENSOR_MAX_GAIN*1024;

    Sensor_Gain_Linearity = gain_gap_compensate;

    for(i = 0; i < sizeof(gain_gap_compensate)/sizeof(CUS_GAIN_GAP_ARRAY); i++)
    {
        //SENSOR_DMSG("GAP:%x %x\r\n",Sensor_Gain_Linearity[i].gain, Sensor_Gain_Linearity[i].offset);
        if (Sensor_Gain_Linearity[i].gain == 0)
            break;
        if((gain>Sensor_Gain_Linearity[i].gain) && (gain < (Sensor_Gain_Linearity[i].gain + Sensor_Gain_Linearity[i].offset)))
        {
            gain=Sensor_Gain_Linearity[i].gain;
            break;
        }
    }

    gain_double = 20*log10((double)gain/1024);
    gain16=(u16)(gain_double*10);
    /*    if(gain16>512)//enable gain expand mode
    {
        gain_reg[2].data=0x89;
        gain_reg[3].data=0x86;
    }
    else
    {
        gain_reg[2].data=0x09;
        gain_reg[3].data=0x0E;
    }*/
    gain_reg[1].data=(gain16>>8)&0x03;//bit 0-->MSB
    gain_reg[0].data=gain16&0xff;//low byte,LSB

    SENSOR_DMSG("[%s] set gain/reg0/reg1=%d/0x%x/0x%x\n", __FUNCTION__, gain,gain_reg[0].data,gain_reg[1].data);
    return SUCCESS;
}

static int pCus_GetAEMinMaxUSecs(ms_cus_sensor *handle, u32 *min, u32 *max)
{
    SENSOR_DMSG("[%s]\n", __FUNCTION__);
    *min = 150;
    *max = 33332; // <- max shutter (30fps: 33332, 60fps:16666)
    return SUCCESS;
}

static int pCus_GetAEMinMaxGain(ms_cus_sensor *handle, u32 *min, u32 *max)
{
    SENSOR_DMSG("[%s]\n", __FUNCTION__);
    *min = SENSOR_MIN_GAIN;//handle->sat_mingain;
    *max = SENSOR_MAX_GAIN;//*1024;
    return SUCCESS;
}

static int pCus_GetDGainRemainder(ms_cus_sensor *handle, u32 *dgain_remainder)
{
    *dgain_remainder = handle->dgain_remainder;

    return SUCCESS;
}

static int imx123_GetShutterInfo(struct __ms_cus_sensor* handle,CUS_SHUTTER_INFO *info)
{
    SENSOR_DMSG("[%s]\n", __FUNCTION__);
    info->max = 1000000000/12;
    info->min =  Preview_line_period*3;
    info->step = Preview_line_period;
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


int imx123_MIPI_cus_camsensor_init_handle(ms_cus_sensor* handle)
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
    sprintf(str, "IMX123linear");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(imx123_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (imx123_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(imx123_params));
#else
    handle->private_data = calloc(1, sizeof(imx123_params));
#endif
    imx123_params *params = (imx123_params *)handle->private_data;

    ////////////////////////////////////
    //    sensor model ID                           //
    ////////////////////////////////////
    sprintf(handle->model_id,"imx123_MIPI");

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
    handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 0;

    ////////////////////////////////////
    //    resolution capability       //
    ////////////////////////////////////

    handle->video_res_supported.num_res = 2;
    handle->video_res_supported.ulcur_res = 0; //default resolution index is 0.
    handle->video_res_supported.res[0].width = Preview_WIDTH;
    handle->video_res_supported.res[0].height = Preview_HEIGHT;
    handle->video_res_supported.res[0].max_fps= Preview_MAX_FPS;
    handle->video_res_supported.res[0].min_fps= Preview_MIN_FPS;
    handle->video_res_supported.res[0].crop_start_x= Preview_CROP_START_X;
    handle->video_res_supported.res[0].crop_start_y= Preview_CROP_START_Y;

    handle->video_res_supported.res[1].width = Sensor_MAX_WIDTH;
    handle->video_res_supported.res[1].height = Sensor_MAX_HEIGHT;
    handle->video_res_supported.res[1].max_fps= Preview_MAX_FPS;
    handle->video_res_supported.res[1].min_fps= Preview_MIN_FPS;
    handle->video_res_supported.res[1].crop_start_x= Preview_CROP_START_X;
    handle->video_res_supported.res[1].crop_start_y= Preview_CROP_START_Y;

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

    //SENSOR_DMSG("[%s:%d]\n", __FUNCTION__, __LINE__);
    handle->pCus_sensor_release     = imx123_MIPI_cus_camsensor_release_handle;
    handle->pCus_sensor_init        = pCus_init    ;
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
    handle->pCus_sensor_SetPatternMode = imx123_SetPatternMode;
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
    handle->pCus_sensor_SetAEGain_cal       = pCus_SetAEGain_cal;
    handle->pCus_sensor_SetAEGain       = pCus_SetAEGain;
    handle->pCus_sensor_GetShutterInfo = imx123_GetShutterInfo;

    handle->pCus_sensor_GetAEMinMaxGain = pCus_GetAEMinMaxGain;
    handle->pCus_sensor_GetAEMinMaxUSecs= pCus_GetAEMinMaxUSecs;
    handle->pCus_sensor_GetDGainRemainder = pCus_GetDGainRemainder;

     //sensor calibration
    // handle->pCus_sensor_SetAEGain_cal   = pCus_SetAEGain_cal;
    handle->pCus_sensor_setCaliData_gain_linearity=pCus_setCaliData_gain_linearity;
#if 1//defined(__MV5_FPGA__)
    handle->pCus_sensor_I2CWrite = pCus_I2CWrite; //Andy Liu
    handle->pCus_sensor_I2CRead = pCus_I2CRead; //Andy Liu
#endif
    params->expo.vts=vts_30fps;
    params->expo.fps = 30;
    params->dirty = false;

    handle->snr_pad_group = SENSOR_PAD_GROUP_SET;

    handle->channel_num = SENSOR_CHANNEL_NUM;
    handle->channel_mode = SENSOR_CHANNEL_MODE;



    return SUCCESS;
}

int imx123_MIPI_cus_camsensor_release_handle(ms_cus_sensor *handle)
{
#if defined(__RTK_OS__)
    CamOsRet_e                  eCamOsRet = CAM_OS_OK;
#endif

    SENSOR_DMSG("[%s]\n", __FUNCTION__);
    if (handle && handle->private_data)
    {
        SENSOR_IMSG("[%s] release handle 0x%x, private data %x\n",__FUNCTION__,(int)handle,(int)handle->private_data);
#if defined(__RTK_OS__)
        eCamOsRet = CamOsDirectMemRelease((void*)handle->private_data, sizeof(imx123_params));
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
struct SensorMapTable_t gsensor_map_imx123 = {
    SENSOR_CHANNEL_NUM,
    imx123_MIPI_cus_camsensor_init_handle,
    imx123_MIPI_cus_camsensor_release_handle
};

int IMX123_Module_Init(void)
{
    cameraSensorRegister(&gsensor_map_imx123);

    return 0;
}

void IMX123_Module_Exit(void)
{
    cameraSensorUnRegister(&gsensor_map_imx123);
}

#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(IMX123_Module_Init);
//ait_module_exit(IMX123_Module_Exit);
#endif //#if defined(__RTK_OS__)

#endif //#if defined(BIND_SENSOR_IMX123_MIPI) && (BIND_SENSOR_IMX123_MIPI == 1)
