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
#if (SENSOR0 == NONE_MIPI)
#define BIND_SENSOR_NONE_MIPI (1)
#endif
#endif //#if defined(__RTK_OS__)

#if (defined(BIND_SENSOR_NONE_MIPI) && (BIND_SENSOR_NONE_MIPI == 1))

#define SENSOR_PAD_GROUP_SET CUS_SENSOR_PAD_GROUP_A
#define SENSOR_CHANNEL_NUM (1)
#define SENSOR_CHANNEL_MODE_LINEAR CUS_SENSOR_CHANNEL_MODE_RAW_STORE

#define SENSOR_30FPS  (1)
//#define SENSOR_25FPS  (2) //TODO
#define SENSOR_FPS         (SENSOR_30FPS)

#define RX_TEST_PATTERN (0)

//============================================
//MIPI config begin.
#define SENSOR_MIPI_LANE_NUM (1) 
#define SENSOR_MIPI_HDR_MODE (0) //0: Linear mode. 1:HDR_16b_combined_DCG. 2:HDR_VS_2x12b_DCG_HCG
//MIPI config end.
//============================================

//#define RES_IDX_1920x1080_30P       (0)     // mode 4,  1920*1080 30P       // Video (16:9)
//#define RES_IDX_1280x720_60P        (1)     // mode 9,  1280*720  60P       // Video (16:9)

#define SENSOR_MODEL_ID     "NONE_MIPI"
#define SENSOR_ISP_TYPE     ISP_EXT                   //ISP_EXT, ISP_SOC
#define SENSOR_IFBUS_TYPE   CUS_SENIF_BUS_MIPI      //CFG //CUS_SENIF_BUS_PARL, CUS_SENIF_BUS_MIPI
#define SENSOR_MIPI_HSYNC_MODE PACKET_HEADER_EDGE1
#define SENSOR_MIPI_DELAY   0x1212                  //CFG

#define SENSOR_DATAPREC     CUS_DATAPRECISION_16
#define SENSOR_DATAMODE     CUS_SEN_10TO12_9000 //CUS_SEN_10TO12_9098     //CFG
#define SENSOR_BAYERID      CUS_BAYER_GB            //CFG //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
#define SENSOR_ORIT         CUS_ORIT_M0F0           //CUS_ORIT_M0F0, CUS_ORIT_M1F0, CUS_ORIT_M0F1, CUS_ORIT_M1F1,
#define SENSOR_MAX_GAIN     (64*1024)//65536
#define SENSOR_MIN_GAIN      (3*1024)//3072
#define SENSOR_GAIN_DELAY_FRAME_COUNT      (2)
#define SENSOR_SHUTTER_DELAY_FRAME_COUNT      (2)

#define Preview_MCLK_SPEED  CUS_CMU_CLK_27MHZ      //CFG //CUS_CMU_CLK_12M, CUS_CMU_CLK_16M, CUS_CMU_CLK_24M, CUS_CMU_CLK_27M
#define Preview_line_period 30250                  ////HTS/PCLK=2420 pixels/80MHZ=30.250us
#define Prv_Max_line_number 1080                    //maximum exposure line munber of sensor when preview
#define vts_30fps  1111                                 //Virt Total Size , 30.25us * 1111 =  33.6ms frame interval =30 fps

#define Preview_WIDTH       1920                    //resolution Width when preview
#define Preview_HEIGHT      1080                    //resolution Height when preview


#define Preview_MAX_FPS     30                     //fastest preview FPS
#define Preview_MIN_FPS     8                      //slowest preview FPS
#define Preview_CROP_START_X     1                      //CROP_START_X
#define Preview_CROP_START_Y     1                      //CROP_START_Y

#define Cap_Max_line_number 1080                   //maximum exposure line munber of sensor when capture

#define SENSOR_I2C_ADDR     0x5a//0x2d         //I2C slave address

#define SENSOR_I2C_SPEED    I2C_SLOWSPEED_MODE_200KHZ   //200KHz
#define SENSOR_I2C_CHANNEL  1                           //I2C Channel
#define SENSOR_I2C_PAD_MODE 2                           //Pad/Mode Number

#define SENSOR_I2C_LEGACY  I2C_NORMAL_MODE     //usally set CUS_I2C_NORMAL_MODE,  if use old OVT I2C protocol=> set CUS_I2C_LEGACY_MODE
#define SENSOR_I2C_FMT     I2C_FMT_A8D8        //CUS_I2C_FMT_A8D8, CUS_I2C_FMT_A8D16, CUS_I2C_FMT_A16D8, CUS_I2C_FMT_A16D16

#define SENSOR_PWDN_POL     CUS_CLK_POL_NEG //CUS_CLK_POL_POS        // if PWDN pin High can makes sensor in power down, set CUS_CLK_POL_POS
#define SENSOR_RST_POL      CUS_CLK_POL_NEG//CUS_CLK_POL_NEG        // if RESET pin High can makes sensor in reset state, set CUS_CLK_POL_NEG

// VSYNC/HSYNC POL can be found in data sheet timing diagram,
// Notice: the initial setting may contain VSYNC/HSYNC POL inverse settings so that condition is different.

#define SENSOR_VSYNC_POL    CUS_CLK_POL_POS// if VSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_HSYNC_POL    CUS_CLK_POL_POS// if HSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_PCLK_POL     CUS_CLK_POL_POS        // depend on sensor setting, sometimes need to try CUS_CLK_POL_POS or CUS_CLK_POL_NEG


int NONE_MIPI_cus_camsensor_release_handle( ms_cus_sensor *handle );

static CUS_CAMSENSOR_CAP sensor_cap =
{
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
    struct
    {
        CUS_CAMSENSOR_ORIT new_setting;            //the mirror/flip status set from user
        CUS_CAMSENSOR_ORIT cur;            //current sensor setting
    } mirror_flip;

    int sen_init;
    int still_min_fps;
    int video_min_fps;
    bool reg_dirty;
    int reg_dirty_cnt;
} none_mipi_params;

static I2C_ARRAY Sensor_id_table[] =
{

};

static I2C_ARRAY Sensor_init_table[] =
{
//NONE
};

static I2C_ARRAY PatternTbl[] =
{

};

static I2C_ARRAY Current_Mirror_Flip_Tbl[] =
{

};


static int pCus_poweron( ms_cus_sensor *handle )
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    SENSOR_DMSG( "[%s] ", __FUNCTION__ );

    if(handle->snr_pad_group == CUS_SENSOR_PAD_GROUP_A) {
        if(handle->interface_attr.attr_mipi.mipi_lane_num == 4){
            sensor_if->SetIOPad(handle->snr_pad_group, CUS_SENIF_BUS_MIPI, CUS_SR0_MIPI_MODE_2 );
        }
        else if((handle->interface_attr.attr_mipi.mipi_lane_num == 2) || (handle->interface_attr.attr_mipi.mipi_lane_num == 1)){ 
            sensor_if->SetIOPad(handle->snr_pad_group, CUS_SENIF_BUS_MIPI, CUS_SR0_MIPI_MODE_1);
        }
        else {
            SENSOR_DMSG( "[%s] mipi_lane_num err %d\n", __FUNCTION__, handle->interface_attr.attr_mipi.mipi_lane_num );
        }
    }
    else {//CUS_SENSOR_PAD_GROUP_B
        if(handle->interface_attr.attr_mipi.mipi_lane_num == 2){
            sensor_if->SetIOPad(handle->snr_pad_group, CUS_SENIF_BUS_MIPI, CUS_SR1_MIPI_MODE_3 );
        }
        else if(handle->interface_attr.attr_mipi.mipi_lane_num == 1){
            sensor_if->SetIOPad(handle->snr_pad_group, CUS_SENIF_BUS_MIPI, CUS_SR1_MIPI_MODE_1);
        }
        else {
            SENSOR_DMSG( "[%s] mipi_lane_num err2 %d\n", __FUNCTION__, handle->interface_attr.attr_mipi.mipi_lane_num );
        }
    }
    
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_216M, handle->PCLK_POLARITY);

    sensor_if->SetCSI_Lane(handle->snr_pad_group, handle->interface_attr.attr_mipi.mipi_lane_num, 1);
    

    sensor_if->MCLK(SENSOR_PAD_GROUP_SET, 1, handle->mclk);
    MsSleep(RTK_MS_TO_TICK(5));

    SENSOR_DMSG("[%s] reset low\n", __FUNCTION__);
    sensor_if->Reset(SENSOR_PAD_GROUP_SET, handle->reset_POLARITY);
    MsSleep(RTK_MS_TO_TICK(5));

    sensor_if->Reset(SENSOR_PAD_GROUP_SET, !handle->reset_POLARITY);
    MsSleep(RTK_MS_TO_TICK(5));

    //sensor_if->Set3ATaskOrder( def_order);
    // pure power on
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, !handle->pwdn_POLARITY);
	sensor_if->SWReset(handle->channel_num, FALSE);
	MsSleep(RTK_MS_TO_TICK(50));

    #if defined(SENSOR_PWR_CTRL_GPIO)
    MMPF_PIO_Enable(SENSOR_PWR_CTRL_GPIO, MMP_TRUE);
    MMPF_PIO_EnableOutputMode(SENSOR_PWR_CTRL_GPIO, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData(SENSOR_PWR_CTRL_GPIO, MMP_TRUE, MMP_TRUE);
    #endif

    return SUCCESS;
}

static int pCus_poweroff( ms_cus_sensor *handle )
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    SENSOR_DMSG( "[%s] power low\n", __FUNCTION__ );

    sensor_if->SWReset(handle->channel_num, TRUE);
    
    sensor_if->PowerOff(handle->snr_pad_group, handle->pwdn_POLARITY );
    MsSleep(RTK_MS_TO_TICK(5));//usleep( 1000 );
	sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_DISABLE, handle->PCLK_POLARITY );
    sensor_if->MCLK(handle->snr_pad_group, 0, handle->mclk );
    sensor_if->SetCSI_Lane(handle->snr_pad_group, handle->interface_attr.attr_mipi.mipi_lane_num, 0);
    
    return SUCCESS;
}

static int pCus_GetSensorID( ms_cus_sensor *handle, u32 *id )
{
    *id =0;
    
    return SUCCESS;
}

static int none_SetPatternMode( ms_cus_sensor *handle, u32 mode )
{
    
    return SUCCESS;
}

static int pCus_I2CWrite(ms_cus_sensor *handle, unsigned short usreg, unsigned short usval)
{
    //NONE
    return SUCCESS;
}

static int pCus_I2CRead(ms_cus_sensor *handle, unsigned short usreg, unsigned short* pusval)
{
    //NONE
    return SUCCESS;
}

static int pCus_init( ms_cus_sensor *handle )
{
    int i;
    ISensorIfAPI *sensor_if = &( handle->sensor_if_api );
    short sen_data;
    sensor_if->PCLK( CUS_SNR_PCLK_MIPI_TOP );

    UartSendTrace("\n===== Sensor none init. =====\n");

    //none

    return SUCCESS;
}

static int pCus_GetVideoResNum( ms_cus_sensor *handle, u32 *ulres_num)
{
    *ulres_num = handle->video_res_supported.num_res;
    return SUCCESS;
}

static int pCus_GetVideoRes( ms_cus_sensor *handle, cus_camsensor_res **res )
{
    *res = &handle->video_res_supported.res[handle->video_res_supported.ulcur_res];
    return SUCCESS;
}

static int pCus_SetVideoRes( ms_cus_sensor *handle, u32 res )
{
    handle->video_res_supported.ulcur_res = 0; //TBD
    handle->pCus_sensor_init = pCus_init;
    
    return SUCCESS;
}

static int pCus_GetOrien( ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT *orit )
{
    none_mipi_params *params = ( none_mipi_params * ) handle->private_data;
    return params->mirror_flip.cur;
}

static int pCus_SetOrien( ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT orit )
{
    none_mipi_params *params = ( none_mipi_params * ) handle->private_data;
    params->mirror_flip.new_setting = orit;
    //DoMirror( handle, params->mirror_flip.new_setting );
    return SUCCESS;
}

static int pCus_GetFPS( ms_cus_sensor *handle )
{
    none_mipi_params *params = ( none_mipi_params * ) handle->private_data;
    SENSOR_DMSG("[%s] FPS %d\n", __FUNCTION__, params->expo.fps);
    return params->expo.fps;
}

static int pCus_SetFPS( ms_cus_sensor *handle, u32 fps )
{
    return SUCCESS;
}

static int pCus_GetSensorCap( ms_cus_sensor *handle, CUS_CAMSENSOR_CAP *cap )
{
    return SUCCESS;
}

static int pCus_AEStatusNotify( ms_cus_sensor *handle, CUS_CAMSENSOR_AE_STATUS_NOTIFY status )
{
    return SUCCESS;
}

static int pCus_GetAEUSecs( ms_cus_sensor *handle, u32 *us )
{
    return SUCCESS;

}

static int pCus_SetAEUSecs( ms_cus_sensor *handle, u32 us )
{
    return SUCCESS;
}

// Gain: 1x = 1024
static int pCus_GetAEGain( ms_cus_sensor *handle, u32* gain )
{
    return SUCCESS;
}

static int pCus_SetAEGain_cal( ms_cus_sensor *handle, u32 gain )
{
    return SUCCESS;
}

static int pCus_SetAEGain( ms_cus_sensor *handle, u32 gain )
{
    return SUCCESS;

}

static int pCus_GetAEMinMaxUSecs( ms_cus_sensor *handle, u32 *min, u32 *max )
{
    *min = 150;
    *max = 33332; // <- max shutter (30fps: 33332, 60fps:16666)

    return SUCCESS;
}

static int pCus_GetAEMinMaxGain( ms_cus_sensor *handle, u32 *min, u32 *max )
{
    *min = SENSOR_MIN_GAIN;            //1024*1.1*2
    *max = SENSOR_MAX_GAIN;

    return SUCCESS;
}

static int pCus_GetDGainRemainder(ms_cus_sensor *handle, u32 *dgain_remainder)
{
    *dgain_remainder = handle->dgain_remainder;

    return SUCCESS;
}

static int pCus_setCaliData_gain_linearity( ms_cus_sensor* handle, CUS_GAIN_GAP_ARRAY* pArray, u32 num )
{
    return SUCCESS;
}

static int NONE_GetShutterInfo( struct __ms_cus_sensor* handle, CUS_SHUTTER_INFO *info )
{
     return SUCCESS;
}

static int pCus_Sensor_GetSrcType(ms_cus_sensor *handle, CUS_SNR_ANADEC_SRC_TYPE *psrc_type)
{
    //NONE
    *psrc_type = CUS_SNR_ANADEC_SRC_FHD;
}

int NONE_MIPI_cus_camsensor_init_handle( ms_cus_sensor* drv_handle )
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
#if defined(__RTK_OS__)
    sprintf(str, "NONE");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(none_mipi_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (none_mipi_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(none_mipi_params));
#else
    handle->private_data = calloc( 1, sizeof(none_mipi_params) );
#endif

    none_mipi_params *params = ( none_mipi_params * ) handle->private_data;

    sprintf( handle->model_id, SENSOR_MODEL_ID );
    handle->isp_type = SENSOR_ISP_TYPE;
    handle->sif_bus = SENSOR_IFBUS_TYPE;
    handle->data_prec = SENSOR_DATAPREC;
    handle->data_mode = SENSOR_DATAMODE;
    handle->bayer_id = SENSOR_BAYERID;
    handle->orient = SENSOR_ORIT;
    
    handle->interface_attr.attr_mipi.mipi_lane_num = SENSOR_MIPI_LANE_NUM;
    handle->interface_attr.attr_mipi.mipi_data_format = CUS_SEN_INPUT_FORMAT_YUV422; //CUS_SEN_INPUT_FORMAT_RGB; // RGB pattern.
    handle->interface_attr.attr_mipi.mipi_yuv_order = CUS_SENSOR_YUV_ORDER_YC;//0; //don't care in RGB pattern. //???
    handle->interface_attr.attr_mipi.mipi_hsync_mode = SENSOR_MIPI_HSYNC_MODE;
    handle->interface_attr.attr_mipi.mipi_sampling_delay = SENSOR_MIPI_DELAY;

    handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_NONE;
    handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 0;
    handle->interface_attr.attr_mipi.pCus_sensor_mipi_get_src_type = pCus_Sensor_GetSrcType;
	
    handle->video_res_supported.num_res = 1;
    handle->video_res_supported.ulcur_res = 0; //default resolution index is 0.
    handle->video_res_supported.res[0].width = Preview_WIDTH;
    handle->video_res_supported.res[0].height = Preview_HEIGHT;
    handle->video_res_supported.res[0].max_fps = Preview_MAX_FPS;
    handle->video_res_supported.res[0].min_fps = Preview_MIN_FPS;
    handle->video_res_supported.res[0].crop_start_x= Preview_CROP_START_X;
    handle->video_res_supported.res[0].crop_start_y= Preview_CROP_START_Y;
    handle->video_res_supported.res[0].nOutputWidth= Preview_WIDTH;
    handle->video_res_supported.res[0].nOutputHeight= Preview_HEIGHT;

    handle->i2c_cfg.mode                = I2C_NORMAL_MODE;
    handle->i2c_cfg.fmt                 = SENSOR_I2C_FMT;
    handle->i2c_cfg.address             = SENSOR_I2C_ADDR;
    handle->i2c_cfg.speed               = SENSOR_I2C_SPEED;     //200000;
    handle->i2c_cfg.nChannel            = SENSOR_I2C_CHANNEL;   //Channel 1
    handle->i2c_cfg.nPadNum             = SENSOR_I2C_PAD_MODE;  //pad mode 2

    handle->mclk = Preview_MCLK_SPEED;

    handle->pwdn_POLARITY = SENSOR_PWDN_POL;
    handle->reset_POLARITY = SENSOR_RST_POL;
    handle->VSYNC_POLARITY              = SENSOR_VSYNC_POL; //CUS_CLK_POL_POS;
    handle->HSYNC_POLARITY              = SENSOR_HSYNC_POL; //CUS_CLK_POL_POS;
    handle->PCLK_POLARITY               = SENSOR_PCLK_POL;  //CUS_CLK_POL_POS);    // use '!' to clear board latch error

    handle->ae_gain_delay = SENSOR_GAIN_DELAY_FRAME_COUNT;            //0;//1;
    handle->ae_shutter_delay = SENSOR_SHUTTER_DELAY_FRAME_COUNT;            //1;//2;

    handle->sat_mingain = SENSOR_MIN_GAIN;
    handle->dgain_remainder = 0;
    handle->pCus_sensor_release = NONE_MIPI_cus_camsensor_release_handle;
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
    handle->pCus_sensor_SetPatternMode = none_SetPatternMode;

    handle->pCus_sensor_AEStatusNotify = pCus_AEStatusNotify;
    handle->pCus_sensor_GetAEUSecs = pCus_GetAEUSecs;
    handle->pCus_sensor_SetAEUSecs = pCus_SetAEUSecs;
    handle->pCus_sensor_GetAEGain = pCus_GetAEGain;
    handle->pCus_sensor_SetAEGain_cal = pCus_SetAEGain_cal;
    handle->pCus_sensor_SetAEGain = pCus_SetAEGain;

    handle->pCus_sensor_GetAEMinMaxGain = pCus_GetAEMinMaxGain;
    handle->pCus_sensor_GetAEMinMaxUSecs = pCus_GetAEMinMaxUSecs;
    handle->pCus_sensor_GetDGainRemainder = pCus_GetDGainRemainder;
    handle->pCus_sensor_GetShutterInfo = NONE_GetShutterInfo;
    handle->pCus_sensor_setCaliData_gain_linearity = pCus_setCaliData_gain_linearity;

    handle->pCus_sensor_I2CWrite = pCus_I2CWrite; 
    handle->pCus_sensor_I2CRead = pCus_I2CRead; 

    params->expo.vts = vts_30fps;
    params->expo.fps = 30;
    params->reg_dirty = false;
    params->reg_dirty_cnt = 0;

    handle->snr_pad_group = SENSOR_PAD_GROUP_SET;

    handle->channel_num = SENSOR_CHANNEL_NUM;
    handle->channel_mode = SENSOR_CHANNEL_MODE_LINEAR;

    return SUCCESS;
}

int NONE_MIPI_cus_camsensor_release_handle( ms_cus_sensor *handle )
{
#if defined(__RTK_OS__)
    CamOsRet_e                  eCamOsRet = CAM_OS_OK;
#endif

    if( handle && handle->private_data )
    {
        SENSOR_IMSG("[%s] release handle 0x%x, private data %x\n",__FUNCTION__,(int)handle,(int)handle->private_data);
#if defined(__RTK_OS__)
        eCamOsRet = CamOsDirectMemRelease((void*)handle->private_data, sizeof(none_mipi_params));
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
struct SensorMapTable_t gsensor_map_none[] = {
    { //Channel 0
        SENSOR_CHANNEL_NUM,
        NONE_MIPI_cus_camsensor_init_handle,
        NONE_MIPI_cus_camsensor_release_handle
    }
};

int NONE_Module_Init(void)
{
    cameraSensorRegister(&gsensor_map_none[0]);
    
    return 0;
}

void NONE_Module_Exit(void)
{
    cameraSensorUnRegister(&gsensor_map_none[0]);
}

#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(NONE_Module_Init);
//ait_module_exit(NONE_Module_Exit);
#endif //#if defined(__RTK_OS__)

#endif //#if defined(BIND_SENSOR_NONE_MIPI) && (BIND_SENSOR_NONE_MIPI == 1)
