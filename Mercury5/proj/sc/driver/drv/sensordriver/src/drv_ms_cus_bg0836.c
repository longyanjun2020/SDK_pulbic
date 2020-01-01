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
#if (SENSOR0 == BG0836)
#define BIND_SENSOR_BG0836 (1)
#endif
#endif //#if defined(__RTK_OS__)

#if defined(BIND_SENSOR_BG0836) && (BIND_SENSOR_BG0836 == 1)

#define SENSOR_PAD_GROUP_SET CUS_SENSOR_PAD_GROUP_A
#define SENSOR_CHANNEL_NUM (0)
#define SENSOR_CHANNEL_MODE CUS_SENSOR_CHANNEL_MODE_REALTIME_NORMAL

#define SENSOR_MODEL_ID     "BG0836"

#define SENSOR_ISP_TYPE     ISP_EXT
#define SENSOR_IFBUS_TYPE   CUS_SENIF_BUS_PARL      //CUS_SENIF_BUS_PARL, CUS_SENIF_BUS_MIPI
#define SENSOR_DATAPREC     CUS_DATAPRECISION_12    //CUS_DATAPRECISION_8, CUS_DATAPRECISION_10
#define SENSOR_DATAMODE     CUS_SEN_10TO12_9098
//#define SENSOR_BAYERID      CUS_BAYER_RG            //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
//#define SENSOR_BAYERID      CUS_BAYER_GB            //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
//#define SENSOR_BAYERID      CUS_BAYER_BG            //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
#define SENSOR_BAYERID      CUS_BAYER_GR           //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
#define SENSOR_ORIT         CUS_ORIT_M0F0           //CUS_ORIT_M0F0, CUS_ORIT_M1F0, CUS_ORIT_M0F1, CUS_ORIT_M1F1,
#define SENSOR_MAX_GAIN     ((16*2.7*16) * 1024)                  // max sensor again, a-gain * conversion-gain*d-gain
#define SENSOR_MIN_GAIN      (1.52 * 1024) //1557
#define SENSOR_GAIN_DELAY_FRAME_COUNT      (2)
#define SENSOR_SHUTTER_DELAY_FRAME_COUNT      (2)

#define Preview_MCLK_SPEED CUS_CMU_CLK_24MHZ   //MCLK from SCL

#define Preview_line_period 29630                      //33.333/1125
//#define vts_30fps           1125                    //74.25M = 2200*1125*30
#define vts_30fps           1134                    //74.25M < 2200*1134*30
#define Preview_WIDTH       1920                    //resolution Width when preview
#define Preview_HEIGHT      1080                   //resolution Height when preview
#define Preview_MAX_FPS     25                      //fastest preview FPS
#define Preview_MIN_FPS     8                       //slowest preview FPS
#define Preview_CROP_START_X     1                      //CROP_START_X
#define Preview_CROP_START_Y     1                      //CROP_START_Y

#define SENSOR_I2C_ADDR     0x64

#define SENSOR_I2C_SPEED    I2C_SLOWSPEED_MODE_200KHZ   //200KHz
#define SENSOR_I2C_CHANNEL  1                           //I2C Channel
#define SENSOR_I2C_PAD_MODE 2                           //Pad/Mode Number

#define SENSOR_I2C_FMT      I2C_FMT_A16D8
#define SENSOR_PWDN_POL     CUS_CLK_POL_NEG
#define SENSOR_RST_POL      CUS_CLK_POL_NEG         // BG0836 RESET active LOW

#define SENSOR_VSYNC_POL    CUS_CLK_POL_NEG         // if VSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_HSYNC_POL    CUS_CLK_POL_POS         // if HSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_PCLK_POL     CUS_CLK_POL_POS         // depend on sensor setting, sometimes need to try CUS_CLK_POL_POS or CUS_CLK_POL_NEG

int bg0836_PARL_cus_camsensor_release_handle(ms_cus_sensor *handle);
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
} bg0836_params;
typedef struct
{
    float total_gain;
    unsigned short analog_gain_reg;
    unsigned short HCG_gain_reg;

} Gain_ARRAY;

static I2C_ARRAY Sensor_id_table[] =
{
    {0x0000, 0x08},    // bg0836
    {0x0001, 0x06},    // bg0836
};

static I2C_ARRAY Sensor_init_table[] =            // PARA12_1928*1088_30fps_27MCLK_74.25PCLK
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
    {0x008e, 0x0000},//0x000c},
    {0x008f, 0x0000},//0x0003},
    {0x00fa, 0x008f},//0x00cf},
    {0x0391, 0x0000},
    {0x0392, 0x0000},
    {0x0393, 0x0001},
    {0x0398, 0x000a},
    {0x0390, 0x0000},//0x0006},

    //{0x0132, 0x00},
    //{0x0133, 0xff},
    //{0x0206, 0x00}, //0x03
    //{0x0207, 0x01},
    {0x006e, 0x00},
 #if 1  // 2018-4-17 15:12
    {0x0131, 0x18},
 #else
    {0x0131, 0x74},

    //{0x0151, 0x02}, //R
    {0x0153, 0x06},//G
    {0x0155, 0x06},//G
    //{0x0157, 0x02},//B
#endif

    {0x001d, 0x0001},
};

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
            return SUCCESS;

        if( SensorRegArrayR((I2C_ARRAY*)id_from_sensor,table_length) == SUCCESS)            //read sensor ID from I2C
        {
            //convert sensor id to u32 format
            for( i = 0; i < table_length; ++i )
            {
                *id = id_from_sensor[i].data;
                SENSOR_IMSG("[%s] %s read id[%d], get 0x%x\n", __FUNCTION__, handle->model_id, i, ( int )*id);

                if( id_from_sensor[i].data != Sensor_id_table[i].data )
                {
                    SENSOR_EMSG("[%s] %s,get 0x%x, error id!\n", __FUNCTION__, handle->model_id, id_from_sensor[i].data);
                    return SUCCESS;
                }
            }
            break;
        }
        else
            MsSleep(RTK_MS_TO_TICK(10));//usleep(1*1000);
    }

    SENSOR_IMSG("[%s] %s get sensor id:0x%x, SUCCESS!\n", __FUNCTION__, handle->model_id, ( int )*id);
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
//     SensorReg_Read(usreg, &sen_data);
    //UartSendTrace("bg0836 reg: 0x%x, data: 0x%x, read: 0x%x.\n", usreg, usval, sen_data);

    return SUCCESS;
}

static int pCus_I2CRead(ms_cus_sensor *handle, unsigned short usreg, unsigned short* pusval)
{
    unsigned short usread_data;

    SensorReg_Read(usreg, &usread_data);
    *pusval = usread_data;
    //UartSendTrace("bg0836 reg: 0x%x, data: 0x%x\n", usreg, usread_data);

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
            UartSendTrace("bg0836 reg: 0x%x, data: 0x%x, read: 0x%x.\n",Sensor_init_table[i].reg, Sensor_init_table[i].data, sen_data);
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
#if 0
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
#endif
    return SUCCESS;
}

static int pCus_SetOrien(ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT orit)
{
#if 0
    short index = 0;
    bg0836_params *params = (bg0836_params *)handle->private_data;

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
#endif
    return SUCCESS;
}

static int pCus_GetFPS(ms_cus_sensor *handle)
{
    bg0836_params *params = (bg0836_params *)handle->private_data;

    return params->expo.fps;
}

static int pCus_SetFPS(ms_cus_sensor *handle, u32 fps)
{
    bg0836_params *params = (bg0836_params *)handle->private_data;
    SENSOR_DMSG("\n\n[%s]", __FUNCTION__);

    if(fps>=3 && fps <= 30){
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
    bg0836_params *params = (bg0836_params *)handle->private_data;
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
    SENSOR_DMSG("[%s] sensor expo lines/us %ld,%ld us\n", __FUNCTION__, lines, *us);
    //printc("[%s] Peter sensor expo lines/us %ld,%ld us\n", __FUNCTION__, lines, *us);
    //return rc;

    return SUCCESS;
}

static int pCus_SetAEUSecs(ms_cus_sensor *handle, u32 us)
{
#if (__SENSOR_W)
    u32 lines = 0, vts = 0;
    u32 blank = 0;
    bg0836_params *params = (bg0836_params *)handle->private_data;

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
    return SUCCESS;
}
#if 1
// again = power(2, coarse_gain)*(32/(32-fine_gain))*conversion gain
// fine_gain = 32 - ( (power(2, coarse_gain)*conversion_gain*32) / again )
static int pCus_SetAEGain(ms_cus_sensor *handle, u32 gain)
{
#if (__SENSOR_W)
    //extern DBG_ITEM Dbg_Items[DBG_TAG_MAX];
    bg0836_params *params = (bg0836_params *)handle->private_data;

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
//  dig_gain = gain * 512 / sensor_again;  //replace by ISP Dgain

//  *ISPDgain = gain * (*ISPDgain) / sensor_again;

    gain_reg[0].data = ( u16 ) ( vref1 );                     //A gain
    gain_reg[1].data = ( u16 ) ( dig_gain >> 8 );             //DG high byte
    gain_reg[2].data = ( u16 ) ( dig_gain & 0xff );           //DG low byte

    SENSOR_DMSG("[%s] set gain/vref1/digH/digL = %ld/0x%x/0x%x/0x%x\n", __FUNCTION__, gain,gain_reg[0].data,gain_reg[1].data,gain_reg[2].data);
    //printc("[%s] Peter set gain/vref1/digH/digL = %ld/0x%x/0x%x/0x%x\n", __FUNCTION__, gain,gain_reg[0].data,gain_reg[1].data,gain_reg[2].data);

    //UartSendTrace("@@@@[%s] Peter set gain = %ld, 0x%x / 0x%x\n", __FUNCTION__,gain, sensor_again, *ISPDgain);

    params->reg_dirty = true;
#endif

    return SUCCESS;
    //return CusHW_i2c_array_tx(handle, handle->i2c_cfg, gain_reg, sizeof(gain_reg)/sizeof(CUS_I2C_ARRAY));
   // return SensorRegArrayW((I2C_ARRAY*)gain_reg, sizeof(gain_reg)/sizeof(I2C_ARRAY));
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

static int BG0836_GetShutterInfo(struct __ms_cus_sensor* handle, CUS_SHUTTER_INFO *info)
{
    info->max = 1000000000 / 12;
    info->min = Preview_line_period * 5;
    info->step = Preview_line_period;
    return SUCCESS;
}

int bg0836_PARL_cus_camsensor_init_handle(ms_cus_sensor* drv_handle)
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
    sprintf(str, "BG0836linear");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(bg0836_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (bg0836_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(bg0836_params));
#else
    handle->private_data = calloc(1, sizeof(bg0836_params));
#endif

    bg0836_params *params = (bg0836_params *)handle->private_data;

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
    handle->pCus_sensor_release = bg0836_PARL_cus_camsensor_release_handle;
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
    handle->pCus_sensor_GetShutterInfo = BG0836_GetShutterInfo;
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

int bg0836_PARL_cus_camsensor_release_handle(ms_cus_sensor *handle)
{
#if defined(__RTK_OS__)
    CamOsRet_e                  eCamOsRet = CAM_OS_OK;
#endif

    if (handle && handle->private_data)
    {
        //SENSOR_IMSG("[%s] release handle 0x%x, private data %x\n",__FUNCTION__,(int)handle,(int)handle->private_data);
#if defined(__RTK_OS__)
        eCamOsRet = CamOsDirectMemRelease((void*)handle->private_data, sizeof(bg0836_params));
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
struct SensorMapTable_t gsensor_map_bg0836 = {
    SENSOR_CHANNEL_NUM,
    bg0836_PARL_cus_camsensor_init_handle,
    bg0836_PARL_cus_camsensor_release_handle
};

int BG0836_Module_Init(void)
{
    cameraSensorRegister(&gsensor_map_bg0836);

    return 0;
}

void BG0836_Module_Exit(void)
{
    cameraSensorUnRegister(&gsensor_map_bg0836);
}

#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(BG0836_Module_Init);
//ait_module_exit(BG0836_Module_Exit);
#endif //#if defined(__RTK_OS__)

#endif //#if defined(BIND_SENSOR_BG0836) && (BIND_SENSOR_BG0836 == 1)
