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

//#define _DEBUG_
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
#if (SENSOR0 == AR0237)
#define BIND_SENSOR_AR0237 (1)
#endif
#endif //#if defined(__RTK_OS__)

#if defined(BIND_SENSOR_AR0237) && (BIND_SENSOR_AR0237 == 1)

#define SENSOR_PAD_GROUP_SET CUS_SENSOR_PAD_GROUP_A
#define SENSOR_CHANNEL_NUM (0)
#define SENSOR_CHANNEL_MODE CUS_SENSOR_CHANNEL_MODE_REALTIME_NORMAL

#define SENSOR_MODEL_ID     "AR0237"

#define SENSOR_ISP_TYPE     ISP_EXT
#define SENSOR_IFBUS_TYPE   CUS_SENIF_BUS_PARL      //CUS_SENIF_BUS_PARL, CUS_SENIF_BUS_MIPI
#define SENSOR_DATAPREC     CUS_DATAPRECISION_12    //CUS_DATAPRECISION_8, CUS_DATAPRECISION_10
#define SENSOR_DATAMODE     CUS_SEN_10TO12_9098
#define SENSOR_BAYERID      CUS_BAYER_RG            //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
//#define SENSOR_BAYERID      CUS_BAYER_GB            //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
//#define SENSOR_BAYERID      CUS_BAYER_BG            //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
//#define SENSOR_BAYERID      CUS_BAYER_RG           //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
#define SENSOR_ORIT         CUS_ORIT_M0F0           //CUS_ORIT_M0F0, CUS_ORIT_M1F0, CUS_ORIT_M0F1, CUS_ORIT_M1F1,
#define SENSOR_MAX_GAIN     ((16*2.7*16) * 1024)                  // max sensor again, a-gain * conversion-gain*d-gain
#define SENSOR_MIN_GAIN      (1.52 * 1024) //1557
#define SENSOR_GAIN_DELAY_FRAME_COUNT      (2)
#define SENSOR_SHUTTER_DELAY_FRAME_COUNT      (2)

#define Preview_MCLK_SPEED CUS_CMU_CLK_27MHZ   //MCLK from SCL

#define Preview_line_period 29630                      //33.333/1125
//#define vts_30fps           1125                    //74.25M = 2200*1125*30
#define vts_30fps           1134                    //74.25M < 2200*1134*30
#define Preview_WIDTH       1920                    //resolution Width when preview
#define Preview_HEIGHT      1080                    //resolution Height when preview
#define Preview_MAX_FPS     30                      //fastest preview FPS
#define Preview_MIN_FPS     4                       //slowest preview FPS
#define Preview_CROP_START_X     1                      //CROP_START_X
#define Preview_CROP_START_Y     1                      //CROP_START_Y

#define SENSOR_I2C_ADDR     0x20

#define SENSOR_I2C_SPEED    I2C_SLOWSPEED_MODE_200KHZ   //200KHz
#define SENSOR_I2C_CHANNEL  1                           //I2C Channel
#define SENSOR_I2C_PAD_MODE 2                           //Pad/Mode Number

#define SENSOR_I2C_FMT      I2C_FMT_A16D16
#define SENSOR_PWDN_POL     CUS_CLK_POL_NEG         // AR0237 no care, OE_BAR pull low always enable
#define SENSOR_RST_POL      CUS_CLK_POL_NEG         // AR0237 RESET active LOW

#define SENSOR_VSYNC_POL    CUS_CLK_POL_NEG ///CUS_CLK_POL_NEG//CUS_CLK_POL_POS         // if VSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_HSYNC_POL    CUS_CLK_POL_POS         // if HSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_PCLK_POL     CUS_CLK_POL_POS         // depend on sensor setting, sometimes need to try CUS_CLK_POL_POS or CUS_CLK_POL_NEG

int ar0237_PARL_cus_camsensor_release_handle(ms_cus_sensor *handle);
static CUS_CAMSENSOR_CAP sensor_cap = {
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

    int sen_init;
    int still_min_fps;
    int video_min_fps;
    bool reg_dirty;            //sensor setting need to update through I2C
    bool orient_dirty;
} ar0237_params;
typedef struct
{
    float total_gain;
    unsigned short analog_gain_reg;
    unsigned short HCG_gain_reg;

} Gain_ARRAY;

static I2C_ARRAY Sensor_id_table[] =
{
    {0x300E, 0x0256},    // ar0237
};

static I2C_ARRAY Sensor_init_table[] =            // PARA12_1928*1088_30fps_27MCLK_74.25PCLK
{
    {0x301A, 0x0001},    // RESET_REGISTER
    {0xffff, 0x000A},
    {0x301A, 0x10D8},    // RESET_REGISTER
    {0xffff, 0x000A},
    {0x3088, 0x8000},    // SEQ_CTRL_PORT
    {0x3086, 0x4558},
    {0x3086, 0x72A6},
    {0x3086, 0x4A31},
    {0x3086, 0x4342},
    {0x3086, 0x8E03},
    {0x3086, 0x2A14},
    {0x3086, 0x4578},
    {0x3086, 0x7B3D},
    {0x3086, 0xFF3D},
    {0x3086, 0xFF3D},
    {0x3086, 0xEA2A},
    {0x3086, 0x043D},
    {0x3086, 0x102A},
    {0x3086, 0x052A},
    {0x3086, 0x1535},
    {0x3086, 0x2A05},
    {0x3086, 0x3D10},
    {0x3086, 0x4558},
    {0x3086, 0x2A04},
    {0x3086, 0x2A14},
    {0x3086, 0x3DFF},
    {0x3086, 0x3DFF},
    {0x3086, 0x3DEA},
    {0x3086, 0x2A04},
    {0x3086, 0x622A},
    {0x3086, 0x288E},
    {0x3086, 0x0036},
    {0x3086, 0x2A08},
    {0x3086, 0x3D64},
    {0x3086, 0x7A3D},
    {0x3086, 0x0444},
    {0x3086, 0x2C4B},
    {0x3086, 0xA403},
    {0x3086, 0x430D},
    {0x3086, 0x2D46},
    {0x3086, 0x4316},
    {0x3086, 0x2A90},
    {0x3086, 0x3E06},
    {0x3086, 0x2A98},
    {0x3086, 0x5F16},
    {0x3086, 0x530D},
    {0x3086, 0x1660},
    {0x3086, 0x3E4C},
    {0x3086, 0x2904},
    {0x3086, 0x2984},
    {0x3086, 0x8E03},
    {0x3086, 0x2AFC},
    {0x3086, 0x5C1D},
    {0x3086, 0x5754},
    {0x3086, 0x495F},
    {0x3086, 0x5305},
    {0x3086, 0x5307},
    {0x3086, 0x4D2B},
    {0x3086, 0xF810},
    {0x3086, 0x164C},
    {0x3086, 0x0955},
    {0x3086, 0x562B},
    {0x3086, 0xB82B},
    {0x3086, 0x984E},
    {0x3086, 0x1129},
    {0x3086, 0x9460},
    {0x3086, 0x5C19},
    {0x3086, 0x5C1B},
    {0x3086, 0x4548},
    {0x3086, 0x4508},
    {0x3086, 0x4588},
    {0x3086, 0x29B6},
    {0x3086, 0x8E01},
    {0x3086, 0x2AF8},
    {0x3086, 0x3E02},
    {0x3086, 0x2AFA},
    {0x3086, 0x3F09},
    {0x3086, 0x5C1B},
    {0x3086, 0x29B2},
    {0x3086, 0x3F0C},
    {0x3086, 0x3E03},
    {0x3086, 0x3E15},
    {0x3086, 0x5C13},
    {0x3086, 0x3F11},
    {0x3086, 0x3E0F},
    {0x3086, 0x5F2B},
    {0x3086, 0x902B},
    {0x3086, 0x803E},
    {0x3086, 0x062A},
    {0x3086, 0xF23F},
    {0x3086, 0x103E},
    {0x3086, 0x0160},
    {0x3086, 0x29A2},
    {0x3086, 0x29A3},
    {0x3086, 0x5F4D},
    {0x3086, 0x1C2A},
    {0x3086, 0xFA29},
    {0x3086, 0x8345},
    {0x3086, 0xA83E},
    {0x3086, 0x072A},
    {0x3086, 0xFB3E},
    {0x3086, 0x6745},
    {0x3086, 0x8824},
    {0x3086, 0x3E08},
    {0x3086, 0x2AFA},
    {0x3086, 0x5D29},
    {0x3086, 0x9288},
    {0x3086, 0x102B},
    {0x3086, 0x048B},
    {0x3086, 0x1686},
    {0x3086, 0x8D48},
    {0x3086, 0x4D4E},
    {0x3086, 0x2B80},
    {0x3086, 0x4C0B},
    {0x3086, 0x3F36},
    {0x3086, 0x2AF2},
    {0x3086, 0x3F10},
    {0x3086, 0x3E01},
    {0x3086, 0x6029},
    {0x3086, 0x8229},
    {0x3086, 0x8329},
    {0x3086, 0x435C},
    {0x3086, 0x155F},
    {0x3086, 0x4D1C},
    {0x3086, 0x2AFA},
    {0x3086, 0x4558},
    {0x3086, 0x8E00},
    {0x3086, 0x2A98},
    {0x3086, 0x3F0A},
    {0x3086, 0x4A0A},
    {0x3086, 0x4316},
    {0x3086, 0x0B43},
    {0x3086, 0x168E},
    {0x3086, 0x032A},
    {0x3086, 0x9C45},
    {0x3086, 0x783F},
    {0x3086, 0x072A},
    {0x3086, 0x9D3E},
    {0x3086, 0x305D},
    {0x3086, 0x2944},
    {0x3086, 0x8810},
    {0x3086, 0x2B04},
    {0x3086, 0x530D},
    {0x3086, 0x4558},
    {0x3086, 0x3E08},
    {0x3086, 0x8E01},
    {0x3086, 0x2A98},
    {0x3086, 0x8E00},
    {0x3086, 0x76A7},
    {0x3086, 0x77A7},
    {0x3086, 0x4644},
    {0x3086, 0x1616},
    {0x3086, 0xA57A},
    {0x3086, 0x1244},
    {0x3086, 0x4B18},
    {0x3086, 0x4A04},
    {0x3086, 0x4316},
    {0x3086, 0x0643},
    {0x3086, 0x1605},
    {0x3086, 0x4316},
    {0x3086, 0x0743},
    {0x3086, 0x1658},
    {0x3086, 0x4316},
    {0x3086, 0x5A43},
    {0x3086, 0x1645},
    {0x3086, 0x588E},
    {0x3086, 0x032A},
    {0x3086, 0x9C45},
    {0x3086, 0x787B},
    {0x3086, 0x3F07},
    {0x3086, 0x2A9D},
    {0x3086, 0x530D},
    {0x3086, 0x8B16},
    {0x3086, 0x863E},
    {0x3086, 0x2345},
    {0x3086, 0x5825},
    {0x3086, 0x3E10},
    {0x3086, 0x8E01},
    {0x3086, 0x2A98},
    {0x3086, 0x8E00},
    {0x3086, 0x3E10},
    {0x3086, 0x8D60},
    {0x3086, 0x1244},
    {0x3086, 0x4BB9},
    {0x3086, 0x2C2C},
    {0x3086, 0x2C2C},    // SEQ_DATA_PORT
    {0x301A, 0x10D8},    // RESET_REGISTER
    {0x30B0, 0x1A38},    // DIGITAL_TEST
    {0x31AC, 0x0C0C},    // DATA_FORMAT_BITS
    {0x302A, 0x0008},    // VT_PIX_CLK_DIV
    {0x302C, 0x0001},    // VT_SYS_CLK_DIV
    {0x302E, 0x0002},    // PRE_PLL_CLK_DIV , 74M
    {0x3030, 0x002C},    // PLL_MULTIPLIER
    {0x3036, 0x000C},    // OP_PIX_CLK_DIV
    {0x3038, 0x0001},    // OP_SYS_CLK_DIV
    {0x3002, 0x0000},    // Y_ADDR_START
    {0x3004, 0x0000},    // X_ADDR_START
    {0x3006, 0x043F},    // Y_ADDR_END,         1088
    {0x3008, 0x0787},    // X_ADDR_END,         1928
    {0x300A, 0x0465},    // FRAME_LENGTH_LINES, VT,1125
    {0x300C, 0x044C},    // LINE_LENGTH_PCK,    HT,1100
    {0x3012, 0x0416},    // COARSE_INTEGRATION_TIME
    {0x30A2, 0x0001},    // X_ODD_INC,subsampling
    {0x30A6, 0x0001},    // Y_ODD_INC
    {0x30AE, 0x0001},    // X_ODD_INC_CB
    {0x30A8, 0x0001},    // Y_ODD_INC_CB
    {0x3040, 0x0000},    // READ_MODE
    {0x31AE, 0x0301},    // SERIAL_FORMAT
    {0x3082, 0x0009},    // OPERATION_MODE_CTRL,ERS linear
    {0x30BA, 0x760C},    // DIGITAL_CTRL
    {0x3100, 0x0000},    // AECTRLREG
    {0x3060, 0x000B},    // GAIN
    {0x31D0, 0x0000},    // COMPANDING
    {0x3064, 0x1802},    // SMIA_TEST
    {0x3EEE, 0xA0AA},    // DAC_LD_34_35
    {0x30BA, 0x762C},    // DIGITAL_CTRL
    {0x3F4A, 0x0F70},    // DELTA_DK_PIX_THRES
    {0x309E, 0x016C},    // HIDY_PROG_START_ADDR
    {0x3092, 0x006F},    // ROW_NOISE_CONTROL
    {0x3EE4, 0x9937},    // DAC_LD_24_25
    {0x3EE6, 0x3863},    // DAC_LD_26_27
    {0x3EEC, 0x3B0C},    // DAC_LD_32_33
    {0x30B0, 0x1A3A},    // DIGITAL_TEST
    {0x30B0, 0x1A3A},    // DIGITAL_TEST
    {0x30BA, 0x762C},    // DIGITAL_CTRL
    {0x30B0, 0x1A3A},    // DIGITAL_TEST
    {0x30B0, 0x0A3A},    // DIGITAL_TEST
    {0x3EEA, 0x2838},    // DAC_LD_30_31
    {0x3ECC, 0x4E2D},    // DAC_LD_0_1
    {0x3ED2, 0xFEA6},    // DAC_LD_6_7
    {0x3ED6, 0x2CB3},    // DAC_LD_10_11
    {0x3EEA, 0x2819},    // DAC_LD_30_31
    {0x30B0, 0x1A3A},    // DIGITAL_TEST
    //{0x306E, 0x2418},    // DATAPATH_SELECT
    //{0x306E, 0x2C18},    // DATAPATH_SELECT , 12:10 , PCLK slew rate
    //{0x306E, 0x9018},    // DATAPATH_SELECT , 12:10 , PCLK slew rate
    {0x306E, 0x4818},    // DATAPATH_SELECT , 12:10 , PCLK slew rate , from FAE for blue line noise
    {0x31E0, 0x0001},   //enable defect pixel correction
    {0x3096, 0x0080},   //Conversion gain
    {0x3098, 0x0080},   //Conversion gain
    {0x3200, 0x0001},   //BIT0:  AdaCD disable/enable , BIT1: 0=Standard AdaCD, 1=low light
    {0x301A, 0x10DC},    // RESET_REGISTER,para,stream on
    //{0x3070, 0x0002},    // TestPattern,

};

static I2C_ARRAY gain_reg[] = {            // again = power(2, coarse_gain)*(32/(32-fine_gain))*conversion gain
    {0x3060, 0x000B},    // again: coarse:[6:4],fine:[3:0]
    {0x305E, 0x0080},    // dgain: xxxx.yyyyyyy
    {0x3100, 0x0000},    // HCG: bit2 2.7x
    {0x3202, 0x0080},   //noise filter
    {0x3206, 0x0B08},   //noise filter
    {0x3208, 0x1E13},   //noise filter
};

static I2C_ARRAY expo_reg[] = {
    {0x3012, 0x0416},            // COARSE_INTEGRATION_TIME
};

static I2C_ARRAY vts_reg[] = {
   {0x300A, 0x0465},            // FRAME_LENGTH_LINES
};

static I2C_ARRAY mirror_reg[] = {
    // {0x301A, 0x10D8}/*{0x3022, 0x0001}*/, //0x3022 group hold can not use, using stop stream
    {0x3040, 0x0000},
    // {0x301A, 0x10DC}/*{0x3022, 0x0000}*/,
};

static int pCus_poweron(ms_cus_sensor *handle)
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    SENSOR_DMSG("[%s] ", __FUNCTION__);
    //Sensor power on sequence, MCLK, RSTn HLH
    sensor_if->SetIOPad(SENSOR_PAD_GROUP_SET, CUS_SENIF_BUS_PARL, CUS_SR0_PAR_MODE_1); // h0015, bit: 10~11 //FPGA
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, handle->pwdn_POLARITY);            // pwdn always low!
	sensor_if->SWReset(handle->channel_num, FALSE);
	sensor_if->Reset(SENSOR_PAD_GROUP_SET, !handle->reset_POLARITY);
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_DISABLE, handle->PCLK_POLARITY);
    sensor_if->MCLK(SENSOR_PAD_GROUP_SET, 1, handle->mclk);
    SENSOR_DMSG("[%s] reset low\n", __FUNCTION__);
    sensor_if->Reset(SENSOR_PAD_GROUP_SET, !handle->reset_POLARITY);
    MsSleep(RTK_MS_TO_TICK(2));//usleep(30000);
    sensor_if->Reset(SENSOR_PAD_GROUP_SET, handle->reset_POLARITY);
    MsSleep(RTK_MS_TO_TICK(2));//usleep(2000);                                           // t4 > 1ms
    sensor_if->Reset(SENSOR_PAD_GROUP_SET, !handle->reset_POLARITY);
    MsSleep(RTK_MS_TO_TICK(12));//usleep(5000);                                           // t5 150000clk/27M

    return SUCCESS;
}

static int pCus_poweroff(ms_cus_sensor *handle)
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
	
	sensor_if->SWReset(handle->channel_num, TRUE);
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_DISABLE, handle->PCLK_POLARITY);
    sensor_if->MCLK(0, 0, handle->mclk);
	
    return SUCCESS;
}

static int pCus_GetSensorID(ms_cus_sensor *handle, u32 *id)
{
    int i, n;
    int table_length = ARRAY_SIZE(Sensor_id_table);
    I2C_ARRAY id_from_sensor[ARRAY_SIZE(Sensor_id_table)];

    for(n = 0; n < table_length; ++n)
    {
        id_from_sensor[n].reg = Sensor_id_table[n].reg;
        id_from_sensor[n].data = 0;
    }

    *id = 0;
    for(n = 0; n < 4; ++n)            //retry , until I2C success
    {
        if(n > 2)
            return FAIL;

        if( SensorRegArrayR((I2C_ARRAY*)id_from_sensor,table_length) == SUCCESS)            //read sensor ID from I2C
        {
            //convert sensor id to u32 format
            for( i = 0; i < table_length; ++i )
            {
                *id = id_from_sensor[i].data;
                SENSOR_DMSG("[%s] %s read id[%d], get 0x%x\n", __FUNCTION__, handle->model_id, i, ( int )*id);

                if( id_from_sensor[i].data != Sensor_id_table[i].data )
                {
                    SENSOR_EMSG("[%s] %s,get 0x%x, error id!\n", __FUNCTION__, handle->model_id, id_from_sensor[i].data);
                    return FAIL;
                }
            }
            break;
        }
        else
            MsSleep(RTK_MS_TO_TICK(10));//usleep(1*1000);
    }

    //SENSOR_IMSG("[%s] %s get sensor id:0x%x, SUCCESS!\n", __FUNCTION__, handle->model_id, ( int )*id);
    return SUCCESS;

}

static int pCus_SetPatternMode(ms_cus_sensor *handle, u32 mode)
{
    SENSOR_DMSG("\n\n[%s], mode=%d \n", __FUNCTION__, mode);

    return SUCCESS;
}

#if 1//defined(__MV5_FPGA__)
static int pCus_I2CWrite(ms_cus_sensor *handle, unsigned short usreg, unsigned short usval)
{
    unsigned short sen_data;

    SensorReg_Write(usreg, usval);
    //SensorReg_Read(usreg, &sen_data);
    //UartSendTrace("ar0237 reg: 0x%x, data: 0x%x, read: 0x%x.\n", usreg, usval, sen_data);

    return SUCCESS;
}

static int pCus_I2CRead(ms_cus_sensor *handle, unsigned short usreg, unsigned short* pusval)
{
    unsigned short usread_data;

    SensorReg_Read(usreg, &usread_data);
    *pusval = usread_data;
    //UartSendTrace("ar0237 reg: 0x%x, data: 0x%x\n", usreg, usread_data);

    return SUCCESS;
}
#endif

static int pCus_init(ms_cus_sensor *handle)
{
    int i,cnt=0;
#if 1//defined(__MV5_FPGA__IMX323__)
    unsigned short sen_data;
#endif
    ISensorIfAPI *sensor_if = &(handle->sensor_if_api);

    UartSendTrace("\n===== AR0237 init. =====\n");
    
    sensor_if->PCLK( CUS_SNR_PCLK_SR_PAD);
    for(i = 0; i < ARRAY_SIZE(Sensor_init_table); i++)
    {
        if(Sensor_init_table[i].reg == 0xffff)
        {
            MsSleep(RTK_MS_TO_TICK(Sensor_init_table[i].data));//usleep(1000*Sensor_init_table[i].data);
        }
        else
        {
            cnt = 0;
            while(SensorReg_Write(Sensor_init_table[i].reg,Sensor_init_table[i].data) != SUCCESS)
            {
                cnt++;
                SENSOR_DMSG("[%s] set Sensor_init_table retry : %d...\n",__FUNCTION__,cnt);("[%s] set Sensor_init_table retry : %d...\n",__FUNCTION__,cnt);
                if(cnt>=10)
                {
                    SENSOR_EMSG("[%s:%d] retry FAIL!!\n", __FUNCTION__, __LINE__);
                    return FAIL;
                }
                MsSleep(RTK_MS_TO_TICK(1));//usleep(10*1000);
            }
#if 0//defined(__MV5_FPGA__IMX323__)
            SensorReg_Read(Sensor_init_table[i].reg, &sen_data);
            UartSendTrace("ar0237 reg: 0x%x, data: 0x%x, read: 0x%x.\n",Sensor_init_table[i].reg, Sensor_init_table[i].data, sen_data);
#endif
        }
    }
    return SUCCESS;
}

static int pCus_GetVideoResNum( ms_cus_sensor *handle, u32 *ulres_num)
{
    *ulres_num = handle->video_res_supported.num_res;
    return SUCCESS;
}

static int pCus_GetVideoRes(ms_cus_sensor *handle, cus_camsensor_res **res)
{
    *res = &handle->video_res_supported.res[handle->video_res_supported.ulcur_res];
    return SUCCESS;
}

static int pCus_SetVideoRes(ms_cus_sensor *handle, u32 res)
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    handle->video_res_supported.ulcur_res = 0; //TBD

    //sensor_if->WaitVEnd(50);
    return SUCCESS;
}

static int pCus_GetOrien(ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT *orit)
{
    short sen_data;

    sen_data = mirror_reg[0].data;
    SENSOR_DMSG("mirror:%x\r\n", sen_data);
    switch(sen_data & 0xc000)
    {
        case 0x0000:
            *orit = CUS_ORIT_M0F0;
            break;
        case 0x4000:
            *orit = CUS_ORIT_M1F0;
            break;
        case 0x8000:
            *orit = CUS_ORIT_M0F1;
            break;
        case 0xC000:
            *orit = CUS_ORIT_M1F1;
            break;
    }

    return SUCCESS;
}

static int pCus_SetOrien(ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT orit)
{
    short index = 0;
    ar0237_params *params = (ar0237_params *)handle->private_data;

    switch(orit)
    {
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
    if(index != mirror_reg[0].data)
    {
        mirror_reg[0].data = index;
        params->orient_dirty = true;
    }

    return SUCCESS;
}

static int pCus_GetFPS(ms_cus_sensor *handle)
{
    ar0237_params *params = (ar0237_params *)handle->private_data;

    return params->expo.fps;
}

static int pCus_SetFPS(ms_cus_sensor *handle, u32 fps)
{
    ar0237_params *params = (ar0237_params *)handle->private_data;
    SENSOR_DMSG("\n\n[%s], fps=%d\n", __FUNCTION__, fps);
    if(fps >= Preview_MIN_FPS && fps <= Preview_MAX_FPS)
    {            //1 based
        params->expo.fps = fps;
        params->expo.vts = (vts_30fps * 30) / fps;
        vts_reg[0].data = params->expo.vts;
        return SensorRegArrayW((I2C_ARRAY* )vts_reg, sizeof(vts_reg) / sizeof(I2C_ARRAY));
    }
    else if(fps >= Preview_MIN_FPS*1000 && fps <= Preview_MAX_FPS*1000)
    {            //1000 based
        params->expo.fps = fps;
        params->expo.vts = (vts_30fps * 30000) / fps;
        vts_reg[0].data = params->expo.vts;
        return SensorRegArrayW((I2C_ARRAY* )vts_reg, sizeof(vts_reg) / sizeof(I2C_ARRAY));
    }
    else
    {
        SENSOR_DMSG("[%s] FPS %d out of range.\n", fps, __FUNCTION__);
        return FAIL;
    }
}

static int pCus_GetSensorCap(ms_cus_sensor *handle, CUS_CAMSENSOR_CAP *cap)
{
    if(cap)
        memcpy(cap, &sensor_cap, sizeof(CUS_CAMSENSOR_CAP));
    else
        return FAIL;
    return SUCCESS;
}

static int pCus_AEStatusNotify(ms_cus_sensor *handle, CUS_CAMSENSOR_AE_STATUS_NOTIFY status)
{
    ar0237_params *params = (ar0237_params *)handle->private_data;

    switch(status)
    {
        case CUS_FRAME_INACTIVE:
            if(params->orient_dirty)
            {
                SensorRegArrayW((I2C_ARRAY* )mirror_reg, sizeof(mirror_reg) / sizeof(I2C_ARRAY));
                params->orient_dirty = false;
            }
            break;
        case CUS_FRAME_ACTIVE:
            if(params->reg_dirty)
            {
                SensorRegArrayW((I2C_ARRAY* )expo_reg, sizeof(expo_reg) / sizeof(I2C_ARRAY));
                SensorRegArrayW((I2C_ARRAY* )gain_reg, sizeof(gain_reg) / sizeof(I2C_ARRAY));
                SensorRegArrayW((I2C_ARRAY* )vts_reg, sizeof(vts_reg) / sizeof(I2C_ARRAY));
                params->reg_dirty = false;
            }
            break;
        default:
            break;
    }
    return SUCCESS;
}

static int pCus_GetAEUSecs(ms_cus_sensor *handle, u32 *us)
{
    int rc;
    u32 lines = 0;
    rc = SensorRegArrayR((I2C_ARRAY* )expo_reg, ARRAY_SIZE(expo_reg));
    if(SUCCESS == rc)
    {
        lines = expo_reg[0].data;
        *us = lines * Preview_line_period / 1000;
    }
    SENSOR_DMSG("[%s] sensor expo lines/us %d, %dus\n", __FUNCTION__, lines, *us);
    return rc;
}

static int pCus_SetAEUSecs(ms_cus_sensor *handle, u32 us)
{
    u32 lines = 0, vts = 0;
    ar0237_params *params = (ar0237_params *)handle->private_data;


    lines = (1000 * us) / Preview_line_period;
    if(lines < 1)
        lines = 1;
    if(lines > params->expo.vts - 1)
    {
        vts = lines + 1;
    }
    else
        vts = params->expo.vts;

    expo_reg[0].data = lines;
    vts_reg[0].data = vts;

    SENSOR_DMSG("[%s] us %ld, lines %ld, vts %ld\n", __FUNCTION__, us, lines, params->expo.vts);
    params->reg_dirty = true;            //reg need to update
    return SUCCESS;
}

// Gain: 1x = 1024
static int pCus_GetAEGain(ms_cus_sensor *handle, u32* gain)
{
    int rc = SUCCESS;
    int i, tmp, coarse_gain, dgain;
    float fine_gain, hcg;

//  rc = SensorRegArrayR((I2C_ARRAY*)gain_reg, ARRAY_SIZE(gain_reg));
    if(SUCCESS == rc)
    {
        tmp = (gain_reg[0].data & 0x70) >> 4;
        coarse_gain = 1;
        for(i = 0; i < tmp; i++)
            coarse_gain = 2 * coarse_gain;

        tmp = gain_reg[0].data & 0x0F;
        fine_gain = 32.0 / (32 - tmp);

        dgain = gain_reg[2].data & 0x3ff;
        if(gain_reg[2].data & 4)
        {
            hcg = 2.7;
        }
        else
        {
            hcg = 1;
        }
        *gain = (coarse_gain * fine_gain * dgain * hcg * 1024) / 128;            // 128 for dgain xxxx.yyyyyyy
    }

//  SENSOR_DMSG("[%s] gain/reg = 0x%x/0x%x\n", __FUNCTION__, *gain, temp_gain);
    return rc;
}
#if 1
// again = power(2, coarse_gain)*(32/(32-fine_gain))*conversion gain
// fine_gain = 32 - ( (power(2, coarse_gain)*conversion_gain*32) / again )
static int pCus_SetAEGain(ms_cus_sensor *handle, u32 gain)
{
#define MAX_A_GAIN (16*1024*2.7)
    int coarse_gain, fine_gain, conversion_gain;
    u8 coarse_reg = 0;
    ar0237_params *params = (ar0237_params *)handle->private_data;
    params->expo.final_gain = gain;
    u32 again = 0;
    u32 dgain = 0;
    u32 input_gain = 0;
    bool hcg = 0;
    
    input_gain = gain;


    if(gain < SENSOR_MIN_GAIN/*1024*1.52*/)
        gain = SENSOR_MIN_GAIN;/*1024*1.52*/
    else if(gain >= SENSOR_MAX_GAIN)
        gain = SENSOR_MAX_GAIN;

    if(gain > 2.7 * 1024)
    {            // 2.7x must use HCG!
        hcg = 1;
        gain_reg[2].data |= 4;
        gain = gain / 2.7;
        conversion_gain = 100 * 2.7;
        gain_reg[3].data = 0x00B0;            //0x3202 , noise filter
        gain_reg[4].data = 0x1C0E;            //0x3206, noise filter
        gain_reg[5].data = 0x4E39;            //0x3208, noise filter
    }
    else
    {
        hcg = 0;
        gain_reg[2].data &= 0xfffb;
        conversion_gain = 100;
        gain_reg[3].data = 0x0080;            //0x3202, noise filter
        gain_reg[4].data = 0x0B08;            //0x3206, noise filter
        gain_reg[5].data = 0x1E13;            //0x3208, noise filter
    }

    if(gain >= 16 * 1024)
    {
        coarse_gain = 16;
        coarse_reg = 0x4;
    }
    else if(gain >= 8 * 1024)
    {
        coarse_gain = 8;
        coarse_reg = 0x3;
    }
    else if(gain >= 4 * 1024)
    {
        coarse_gain = 4;
        coarse_reg = 0x2;
    }
    else if(gain >= 2 * 1024)
    {
        coarse_gain = 2;
        coarse_reg = 0x1;
    }
    else
    {
        coarse_gain = 1;
        coarse_reg = 0x0;
    }

    if(input_gain <= 44237)            //44237 = 2^4 * 2.7 * 1024 Adjust A-gain when < 43.2x
    {
        fine_gain = 32 - ((1024 * coarse_gain * 32 + 512) / (gain > MAX_A_GAIN ? MAX_A_GAIN:gain));

        if(hcg == 1 && (coarse_gain >= 1) && (fine_gain & 0x01 == 1))
        {            //fine gain one step become 2x when coarse_gain >=1 reference to excel gain table
            fine_gain &= 0xFFFFFFFE;
        }

        gain_reg[0].data = (coarse_reg << 4) | fine_gain;

        again = /*(float)*/(32 * coarse_gain * conversion_gain) / (32 - fine_gain) * 100;

        dgain = input_gain * 1000 / again * 128;            //use dgain compensate again linearity

        if(dgain < 13300)
            dgain = 13300;

        gain_reg[1].data = dgain / 100;

        //printf("~~~input_gain : %d again:%d again_next:%d dgain_c:%d\n",input_gain,again,again_next,dgain);
    }
    else if(input_gain > 44237)
    {            //Adjust D-gain when > 43.2x

        gain_reg[0].data = 0x40;
        dgain = /*(float)*/(input_gain * 100) / 44237;

        dgain *= 128;

        if(dgain < 13300)
            dgain = 13300;

        gain_reg[1].data = dgain / 100;
    }
    //printf("[%s] TotalGain=%d(%dX) ,A-gain reg=0x%x , D-gain reg=%d\n", __FUNCTION__,input_gain,input_gain/1024,gain_reg[0].data ,gain_reg[1].data);
    params->reg_dirty = true;            //reg need to update
    return SUCCESS;
}

#endif

static int pCus_GetAEMinMaxUSecs(ms_cus_sensor *handle, u32 *min, u32 *max)
{
    *min = 150;
    *max = 33332; // <- max shutter (30fps: 33332, 60fps:16666)
    return SUCCESS;
}

static int pCus_GetAEMinMaxGain(ms_cus_sensor *handle, u32 *min, u32 *max)
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

static int pCus_setCaliData_gain_linearity(ms_cus_sensor* handle, CUS_GAIN_GAP_ARRAY* pArray, u32 num)
{
    SENSOR_DMSG("[%s]%d, %d, %d, %d\n", __FUNCTION__, num, pArray[0].gain, pArray[1].gain, pArray[num-1].offset);

    return SUCCESS;
}

static int AR0237_GetShutterInfo(struct __ms_cus_sensor* handle, CUS_SHUTTER_INFO *info)
{
    info->max = 1000000000 / Preview_MIN_FPS;
    info->min = Preview_line_period * 5;
    info->step = Preview_line_period;
    return SUCCESS;
}

int ar0237_PARL_cus_camsensor_init_handle(ms_cus_sensor* drv_handle)
{
    ms_cus_sensor *handle = drv_handle;
#if defined(__RTK_OS__)
    CamOsRet_e                  eCamOsRet = CAM_OS_OK;
    void*                       pvBufVirt = NULL;
    u64                 u64BufPhy = 0;
    u64                 u64BufMiu = 0;
    u8                   str[20];
#endif
    if(!handle)
    {
        SENSOR_EMSG("[%s] not enough memory!\n", __FUNCTION__);
        return FAIL;
    }
    SENSOR_DMSG("[%s]", __FUNCTION__);
#if defined(__RTK_OS__)
    sprintf(str, "AR0237linear");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(ar0237_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (ar0237_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(ar0237_params));
#else
    handle->private_data = calloc(1, sizeof(ar0237_params));
#endif

    ar0237_params *params = (ar0237_params *)handle->private_data;

    sprintf(handle->model_id, SENSOR_MODEL_ID);
    handle->isp_type = SENSOR_ISP_TYPE;            //ISP_SOC;
    handle->sif_bus = SENSOR_IFBUS_TYPE;            //CUS_SENIF_BUS_PARL;
    handle->data_prec = SENSOR_DATAPREC;            //CUS_DATAPRECISION_8;
    handle->data_mode = SENSOR_DATAMODE;
    if(SENSOR_CHANNEL_MODE == CUS_SENSOR_CHANNEL_MODE_RAW_STORE_FETCH) {
        handle->bayer_id = CUS_BAYER_GB;
    }
    else {
        handle->bayer_id = SENSOR_BAYERID;            //CUS_BAYER_GB;
    }
    handle->orient = SENSOR_ORIT;            //CUS_ORIT_M1F1;

    handle->video_res_supported.num_res = 1;
    handle->video_res_supported.ulcur_res = 0; //default resolution index is 0.
    handle->video_res_supported.res[0].width = Preview_WIDTH;
    handle->video_res_supported.res[0].height = Preview_HEIGHT;
    handle->video_res_supported.res[0].max_fps = Preview_MAX_FPS;
    handle->video_res_supported.res[0].min_fps = Preview_MIN_FPS;
    handle->video_res_supported.res[0].crop_start_x= Preview_CROP_START_X;
    handle->video_res_supported.res[0].crop_start_y= Preview_CROP_START_Y;
    handle->video_res_supported.res[0].nOutputWidth= 1928;
    handle->video_res_supported.res[0].nOutputHeight= 1088;

    handle->i2c_cfg.mode                = I2C_NORMAL_MODE;            //old OVT I2C protocol=>I2C_LEGACY_MODE
    handle->i2c_cfg.fmt                 = SENSOR_I2C_FMT;
    handle->i2c_cfg.address             = SENSOR_I2C_ADDR;
    handle->i2c_cfg.speed               = SENSOR_I2C_SPEED;     //200000;
    handle->i2c_cfg.nChannel            = SENSOR_I2C_CHANNEL;   //Channel 1
    handle->i2c_cfg.nPadNum             = SENSOR_I2C_PAD_MODE;  //pad mode 2

    handle->mclk = Preview_MCLK_SPEED;

    handle->pwdn_POLARITY = SENSOR_PWDN_POL;
    handle->reset_POLARITY = SENSOR_RST_POL;
    handle->VSYNC_POLARITY = SENSOR_VSYNC_POL;
    handle->HSYNC_POLARITY = SENSOR_HSYNC_POL;
    handle->PCLK_POLARITY = SENSOR_PCLK_POL;

    handle->ae_gain_delay = SENSOR_GAIN_DELAY_FRAME_COUNT;
    handle->ae_shutter_delay = SENSOR_SHUTTER_DELAY_FRAME_COUNT;

    handle->sat_mingain = SENSOR_MIN_GAIN;
    handle->dgain_remainder = 0;
    handle->pCus_sensor_release = ar0237_PARL_cus_camsensor_release_handle;
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
    handle->pCus_sensor_SetPatternMode = pCus_SetPatternMode;

    handle->pCus_sensor_AEStatusNotify = pCus_AEStatusNotify;
    handle->pCus_sensor_GetAEUSecs = pCus_GetAEUSecs;
    handle->pCus_sensor_SetAEUSecs = pCus_SetAEUSecs;
    handle->pCus_sensor_GetAEGain = pCus_GetAEGain;
    handle->pCus_sensor_SetAEGain_cal = pCus_SetAEGain;            //pCus_SetAEGain_cal;
    handle->pCus_sensor_SetAEGain = pCus_SetAEGain;

    handle->pCus_sensor_GetAEMinMaxGain = pCus_GetAEMinMaxGain;
    handle->pCus_sensor_GetAEMinMaxUSecs = pCus_GetAEMinMaxUSecs;
    handle->pCus_sensor_GetDGainRemainder = pCus_GetDGainRemainder;

    handle->pCus_sensor_setCaliData_gain_linearity = pCus_setCaliData_gain_linearity;
    handle->pCus_sensor_GetShutterInfo = AR0237_GetShutterInfo;
#if 1//defined(__MV5_FPGA__)
    handle->pCus_sensor_I2CWrite = pCus_I2CWrite; //Andy Liu
    handle->pCus_sensor_I2CRead = pCus_I2CRead; //Andy Liu
#endif
    params->expo.vts = vts_30fps;
    params->expo.fps = 30;

    handle->snr_pad_group = SENSOR_PAD_GROUP_SET;

    handle->channel_num = SENSOR_CHANNEL_NUM;
    handle->channel_mode = SENSOR_CHANNEL_MODE;

    return SUCCESS;
}

int ar0237_PARL_cus_camsensor_release_handle(ms_cus_sensor *handle)
{
#if defined(__RTK_OS__)
    CamOsRet_e                  eCamOsRet = CAM_OS_OK;
#endif

    if (handle && handle->private_data)
    {
        //SENSOR_IMSG("[%s] release handle 0x%x, private data %x\n",__FUNCTION__,(int)handle,(int)handle->private_data);
#if defined(__RTK_OS__)
        eCamOsRet = CamOsDirectMemRelease((void*)handle->private_data, sizeof(ar0237_params));
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
struct SensorMapTable_t gsensor_map_ar0237 = {
    SENSOR_CHANNEL_NUM,
    ar0237_PARL_cus_camsensor_init_handle,
    ar0237_PARL_cus_camsensor_release_handle
};

int AR0237_Module_Init(void)
{
    cameraSensorRegister(&gsensor_map_ar0237);

    return 0;
}

void AR0237_Module_Exit(void)
{
    cameraSensorUnRegister(&gsensor_map_ar0237);
}

#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(AR0237_Module_Init);
//ait_module_exit(AR0237_Module_Exit);
#endif //#if defined(__RTK_OS__)

#endif //#if defined(BIND_SENSOR_AR0237) && (BIND_SENSOR_AR0237 == 1)
