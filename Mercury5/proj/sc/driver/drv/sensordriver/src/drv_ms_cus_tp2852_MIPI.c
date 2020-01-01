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

//TP2852 support HD, TP2854 support HD/FHD.

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
#if (SENSOR0 == TP2852)
#define BIND_SENSOR_TP2852_MIPI (1)
#endif
#endif //#if defined(__RTK_OS__)

#if (defined(BIND_SENSOR_TP2852_MIPI) && (BIND_SENSOR_TP2852_MIPI == 1))

#define SENSOR_PAD_GROUP_SET            CUS_SENSOR_PAD_GROUP_A
#define SENSOR_CHANNEL_NUM              (1)
#define SENSOR_CHANNEL_MODE_LINEAR      CUS_SENSOR_CHANNEL_MODE_RAW_STORE

#define SENSOR_MODE_HD_1CH              (1)
#define SENSOR_MODE_HD_2VC              (2)
#define SENSOR_MODE_FHD_1CH             (3)
#define SENSOR_MODE_FHD_2VC             (4)
#define SENSOR_MODE                     (SENSOR_MODE_HD_2VC)

#define SENSOR_30FPS                    (1)
#define SENSOR_25FPS                    (2)
#define SENSOR_FPS                      (SENSOR_25FPS)


//============================================
//MIPI config begin.
#if((SENSOR_MODE == SENSOR_MODE_HD_1CH) || (SENSOR_MODE == SENSOR_MODE_FHD_1CH))
#define SENSOR_MIPI_LANE_NUM            (2) //4 or 2
#else
#define SENSOR_MIPI_LANE_NUM            (4) //4
#endif

#define SENSOR_MIPI_HDR_MODE            (0) //0: Linear mode. 1:HDR_16b_combined_DCG. 2:HDR_VS_2x12b_DCG_HCG
//MIPI config end.
//============================================

//#define RES_IDX_1920x1080_30P       (0)     // mode 4,  1920*1080 30P       // Video (16:9)
//#define RES_IDX_1280x720_60P        (1)     // mode 9,  1280*720  60P       // Video (16:9)

#define SENSOR_MODEL_ID     "TP2852_MIPI"
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

#define Preview_MCLK_SPEED      CUS_CMU_CLK_24MHZ      //CFG //CUS_CMU_CLK_12M, CUS_CMU_CLK_16M, CUS_CMU_CLK_24M, CUS_CMU_CLK_27M
#define Preview_line_period     30250                  ////HTS/PCLK=2420 pixels/80MHZ=30.250us
#define Prv_Max_line_number     1080                    //maximum exposure line munber of sensor when preview
#define vts_30fps               1111                                 //Virt Total Size , 30.25us * 1111 =  33.6ms frame interval =30 fps

#if ((SENSOR_MODE == SENSOR_MODE_FHD_1CH) || (SENSOR_MODE == SENSOR_MODE_FHD_2VC))
#define Preview_WIDTH       1920                    //resolution Width when preview
#define Preview_HEIGHT      1080                    //resolution Height when preview
#else
#define Preview_WIDTH       1280                    //resolution Width when preview
#define Preview_HEIGHT      720                     //resolution Height when preview
#endif

#define Preview_MAX_FPS     30                     //fastest preview FPS
#define Preview_MIN_FPS     8                      //slowest preview FPS
#define Preview_CROP_START_X     1                      //CROP_START_X
#define Preview_CROP_START_Y     1                      //CROP_START_Y

#define Cap_Max_line_number 1080                   //maximum exposure line munber of sensor when capture

#define SENSOR_I2C_ADDR    (0x88) //(0x88 >> 1)         //I2C slave address
#define SENSOR_I2C_SPEED    I2C_SLOWSPEED_MODE_200KHZ   //200KHz
#define SENSOR_I2C_CHANNEL  1                           //I2C Channel
#define SENSOR_I2C_PAD_MODE 2                           //Pad/Mode Number

#define SENSOR_I2C_LEGACY  I2C_NORMAL_MODE     //usally set CUS_I2C_NORMAL_MODE,  if use old OVT I2C protocol=> set CUS_I2C_LEGACY_MODE
#define SENSOR_I2C_FMT     I2C_FMT_A8D8        //CUS_I2C_FMT_A8D8, CUS_I2C_FMT_A8D16, CUS_I2C_FMT_A16D8, CUS_I2C_FMT_A16D16

#define SENSOR_PWDN_POL     CUS_CLK_POL_POS        // if PWDN pin High can makes sensor in power down, set CUS_CLK_POL_POS
#define SENSOR_RST_POL      CUS_CLK_POL_NEG//CUS_CLK_POL_NEG        // if RESET pin High can makes sensor in reset state, set CUS_CLK_POL_NEG

// VSYNC/HSYNC POL can be found in data sheet timing diagram,
// Notice: the initial setting may contain VSYNC/HSYNC POL inverse settings so that condition is different.

#define SENSOR_VSYNC_POL    CUS_CLK_POL_POS// if VSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_HSYNC_POL    CUS_CLK_POL_POS// if HSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_PCLK_POL     CUS_CLK_POL_POS        // depend on sensor setting, sometimes need to try CUS_CLK_POL_POS or CUS_CLK_POL_NEG

int tp2852_MIPI_cus_camsensor_release_handle( ms_cus_sensor *handle );

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
} tp2852_params;

static I2C_ARRAY Sensor_id_table[] =
{

};

#if(SENSOR_MODE == SENSOR_MODE_HD_1CH)
static I2C_ARRAY Sensor_init_table_HD_60FPS_1CH[] =
{
    //video setting
    0x40, 0x00, //video page
    0x4e, 0x00,
    0xf5, 0xf0,

    0x02, 0xc2,
    0x07, 0xc0,
    0x0b, 0xc0,
    0x0c, 0x13,
    0x0d, 0x50,

    0x15, 0x13,
    0x16, 0x15,
    0x17, 0x00,
    0x18, 0x19,
    0x19, 0xd0,
    0x1a, 0x25,

#if(SENSOR_FPS == SENSOR_30FPS)
    0x1c, 0x06,  //1280*720, 30fps
    0x1d, 0x72,  //1280*720, 30fps
#else
    0x1c, 0x07,  //1280*720, 25fps
    0x1d, 0xbc,  //1280*720, 25fps
#endif

    0x20, 0x30,
    0x21, 0x84,
    0x22, 0x36,
    0x23, 0x3c,

    0x2b, 0x60,
    0x2c, 0x0a,
    0x2d, 0x30,
    0x2e, 0x70,

    0x30, 0x48,
    0x31, 0xbb,
    0x32, 0x2e,
    0x33, 0x90,

    0x35, 0x25,
    0x38, 0x00,
    0x39, 0x18,


    //mipi setting
    0x40, 0x08, //MIPI page
    0x01, 0xf8,
    0x02, 0x01,
    0x08, 0x0f,
    0x13, 0x04,

#if(SENSOR_MIPI_LANE_NUM == 4)
    0x14, 0x56,
    0x15, 0x0a,
    0x20, 0x14, //1CH, MIPI 4 Lane
#elif(SENSOR_MIPI_LANE_NUM == 2)
    0x14, 0x46,
    0x15, 0x08,
    0x20, 0x12,
#endif

    0x34, 0x1b,

    /* Disable MIPI CSI2 output */
    0x23, 0x02,

    /* Enable MIPI CSI2 output */
    0x23, 0x00,
};

static I2C_ARRAY Sensor_init_table_HD_1CH[] =
{
    //video setting
    0x40, 0x00, //video page
    0x4e, 0x00,
    0xf5, 0xf0,

    0x02, 0xc2,
    0x07, 0xc0,
    0x0b, 0xc0,
    0x0c, 0x13,
    0x0d, 0x50,

    0x15, 0x13,
    0x16, 0x15,
    0x17, 0x00,
    0x18, 0x19,
    0x19, 0xd0,
    0x1a, 0x25,

#if(SENSOR_FPS == SENSOR_30FPS)
    0x1c, 0x06,  //1280*720, 30fps
    0x1d, 0x72,  //1280*720, 30fps
#else
    0x1c, 0x07,  //1280*720, 25fps
    0x1d, 0xbc,  //1280*720, 25fps
#endif

    0x20, 0x30,
    0x21, 0x84,
    0x22, 0x36,
    0x23, 0x3c,

    0x2b, 0x60,
    0x2c, 0x0a,
    0x2d, 0x30,
    0x2e, 0x70,

    0x30, 0x48,
    0x31, 0xbb,
    0x32, 0x2e,
    0x33, 0x90,

    0x35, 0x25,
    0x38, 0x00,
    0x39, 0x18,


    //mipi setting
    0x40, 0x08, //MIPI page
    0x01, 0xf8,
    0x02, 0x01,
    0x08, 0x0f,
    0x13, 0x24, //0x04,

#if(SENSOR_MIPI_LANE_NUM == 4)
    0x14, 0x56,
    0x15, 0x0a,
    0x20, 0x14, //1CH, MIPI 4 Lane
#elif(SENSOR_MIPI_LANE_NUM == 2)
    0x14, 0x46,
    0x15, 0x08,
    0x20, 0x12,
#endif

    0x34, 0x1b,

    /* Disable MIPI CSI2 output */
    0x23, 0x02,

    /* Enable MIPI CSI2 output */
    0x23, 0x00,
};

#endif //(SENSOR_MODE == SENSOR_MODE_HD_1CH)

#if(SENSOR_MODE == SENSOR_MODE_HD_2VC)
static I2C_ARRAY Sensor_init_table_HD_60FPS_2VC[] =
{
    //video setting
    0x40, 0x04, //video page, write all
    0x4e, 0x00,
    0xf5, 0xf0,

    0x02, 0xc2,
    0x07, 0xc0,
    0x0b, 0xc0,
    0x0c, 0x13,
    0x0d, 0x50,

    0x15, 0x13,
    0x16, 0x15,
    0x17, 0x00,
    0x18, 0x19,
    0x19, 0xd0,
    0x1a, 0x25,

#if(SENSOR_FPS == SENSOR_30FPS)
    0x1c, 0x06,  //1280*720, 30fps
    0x1d, 0x72,  //1280*720, 30fps
#else
    0x1c, 0x07,  //1280*720, 25fps
    0x1d, 0xbc,  //1280*720, 25fps
#endif

    0x20, 0x30,
    0x21, 0x84,
    0x22, 0x36,
    0x23, 0x3c,

    0x2b, 0x60,
    0x2c, 0x0a,
    0x2d, 0x30,
    0x2e, 0x70,

    0x30, 0x48,
    0x31, 0xbb,
    //0x32, 0x3e,//
    0x32, 0x2e,//color carrier
    0x33, 0x90,

    0x35, 0x25,
    0x38, 0x00,
    0x39, 0x18,

    //mipi setting
    0x40, 0x08, //MIPI page
    0x01, 0xf8,
    0x02, 0x01,
    0x08, 0x0f,
    0x13, 0x04, //0x24,
    0x14, 0x45,
    0x15, 0x05,
    0x20, 0x24,
    0x34, 0x1b,

    /* Disable MIPI CSI2 output */
    0x23, 0x02,

    /* Enable MIPI CSI2 output */
    0x23, 0x00,
};

static I2C_ARRAY Sensor_init_table_HD_2VC[] =
{
    //video setting
    0x40, 0x04, //video page, write all
    0x4e, 0x00,
    0xf5, 0xf0,

    0x02, 0xc2,
    0x07, 0xc0,
    0x0b, 0xc0,
    0x0c, 0x13,
    0x0d, 0x50,

    0x15, 0x13,
    0x16, 0x15,
    0x17, 0x00,
    0x18, 0x19,
    0x19, 0xd0,
    0x1a, 0x25,
#if(SENSOR_FPS == SENSOR_30FPS)
    0x1c, 0x06,  //1280*720, 30fps
    0x1d, 0x72,  //1280*720, 30fps
#else
    0x1c, 0x07,  //1280*720, 25fps
    0x1d, 0xbc,  //1280*720, 25fps
#endif
    0x20, 0x30,
    0x21, 0x84,
    0x22, 0x36,
    0x23, 0x3c,

    0x2b, 0x60,
    0x2c, 0x0a,
    0x2d, 0x30,
    0x2e, 0x70,

    0x30, 0x48,
    0x31, 0xbb,
    0x32, 0x2e,
    //0x32, 0x3e,//0x32, 0x2e,//color carrier
    0x33, 0x90,

    0x35, 0x25,
    0x38, 0x00,
    0x39, 0x18,

    //mipi setting
    0x40, 0x08, //MIPI page
    0x01, 0xf8,
    0x02, 0x01,
    0x08, 0x0f,
    0x13, 0x24,
    0x14, 0x45,
    0x15, 0x05,
    0x20, 0x24,
    0x34, 0x1b,

    /* Disable MIPI CSI2 output */
    0x23, 0x02,

    /* Enable MIPI CSI2 output */
    0x23, 0x00,
};
#endif //(SENSOR_MODE == SENSOR_MODE_HD_2VC)

#if(SENSOR_MODE == SENSOR_MODE_FHD_1CH)
static I2C_ARRAY Sensor_init_table_FHD_1CH[] =
{
//video setting
    0x40, 0x04, //Old:0x00, //video page, write all
    0x4e, 0x00,
    0xf5, 0xf0,

    0x02, 0xc0,
    0x07, 0xc0,
    0x0b, 0xc0,
    0x0c, 0x03,
    0x0d, 0x50,

    0x15, 0x03,
    0x16, 0xd2,
    0x17, 0x80,
    0x18, 0x29,
    0x19, 0x38,
    0x1a, 0x47,

#if(SENSOR_FPS == SENSOR_30FPS)
    0x1c, 0x08,  //1920*1080, 30fps
    0x1d, 0x98,  //
#else
    0x1c, 0x0a,  //1920*1080, 25fps
    0x1d, 0x50,  //
#endif

    0x20, 0x30,
    0x21, 0x84,
    0x22, 0x36,
    0x23, 0x3c,

    0x2b, 0x60,
    0x2c, 0x0a,
    0x2d, 0x30,
    0x2e, 0x70,

    0x30, 0x48,
    0x31, 0xbb,
    0x32, 0x2e,
    0x33, 0x90,

    0x35, 0x05,
    0x38, 0x00,
    0x39, 0x1C,


    //mipi setting
    0x40, 0x08, //MIPI page
    0x01, 0xf8,
    0x02, 0x01,
    0x08, 0x0f,
    0x13, 0x04,

//0x25, 0x08,
//0x26, 0x01,
//0x27, 0x0e,

#if(SENSOR_MIPI_LANE_NUM == 4)
    0x14, 0x45,
    0x15, 0x05,
    0x20, 0x14, //1CH, MIPI 4 Lane
#elif(SENSOR_MIPI_LANE_NUM == 2)
	0x14, 0x46,
    0x15, 0x08,
    0x20, 0x12, //1CH, MIPI 2 Lane
#endif

	0x34, 0x1b,

    /* Disable MIPI CSI2 output */
    0x23, 0x02,

    /* Enable MIPI CSI2 output */
    0x23, 0x00,


};
#endif //(SENSOR_MODE == SENSOR_MODE_FHD_1CH)

#if(SENSOR_MODE == SENSOR_MODE_FHD_2VC)
static I2C_ARRAY Sensor_init_table_FHD_2VC[] =
{
    //video setting
    0x40, 0x04, //video page, write all
    0x4e, 0x00,
    0xf5, 0xf0,

    0x02, 0xc0,
    0x07, 0xc0,
    0x0b, 0xc0,
    0x0c, 0x03,
    0x0d, 0x50,

    0x15, 0x03,
    0x16, 0xd2,
    0x17, 0x80,
    0x18, 0x29,
    0x19, 0x38,
    0x1a, 0x47,

#if(SENSOR_FPS == SENSOR_30FPS)
    0x1c, 0x08,  //1920*1080, 30fps
    0x1d, 0x98,  //
#else
    0x1c, 0x0a,  //1920*1080, 25fps
    0x1d, 0x50,  //
#endif

    0x20, 0x30,
    0x21, 0x84,
    0x22, 0x36,
    0x23, 0x3c,

    0x2b, 0x60,
    0x2c, 0x0a,
    0x2d, 0x30,
    0x2e, 0x70,

    0x30, 0x48,
    0x31, 0xbb,
    0x32, 0x2e,
    0x33, 0x90,

    0x35, 0x05,
    0x38, 0x00,
    0x39, 0x1C,

    //mipi setting
    0x40, 0x08, //MIPI page
    0x01, 0xf8,
    0x02, 0x01,
    0x08, 0x0f,
    0x13, 0x04,
    0x14, 0x45,
    0x15, 0x05,
    0x20, 0x24,
    0x34, 0x1b,


    /* Disable MIPI CSI2 output */
    0x23, 0x02,

    /* Enable MIPI CSI2 output */
    0x23, 0x00,
};
#endif //(SENSOR_MODE == SENSOR_MODE_FHD_2VC)

static I2C_ARRAY PatternTbl[] =
{

};

static I2C_ARRAY Current_Mirror_Flip_Tbl[] =
{

};

/*
static I2C_ARRAY gain_reg[] =
{

};

static CUS_GAIN_GAP_ARRAY gain_gap_compensate[] =
{

};
static I2C_ARRAY expo_reg[] =
{

};

static I2C_ARRAY vts_reg[] =
{

};
*/

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

    sensor_if->SetCSI_Clk(handle->snr_pad_group, /*CUS_CSI_CLK_288M */CUS_CSI_CLK_216M, handle->PCLK_POLARITY);

    if(handle->interface_attr.attr_mipi.mipi_lane_num == 2){
        sensor_if->SetCSI_Lane(handle->snr_pad_group, 2, 1);
    }
    else if(handle->interface_attr.attr_mipi.mipi_lane_num == 4){
        sensor_if->SetCSI_Lane(handle->snr_pad_group, 4, 1);
    }

    sensor_if->MCLK(SENSOR_PAD_GROUP_SET, 1, handle->mclk);
    //  sensor_if->SetCSI_LongPacketType(handle,0xff00000000);

    SENSOR_DMSG( "[%s] reset low\n", __FUNCTION__ );
    sensor_if->Reset(handle->snr_pad_group, handle->reset_POLARITY );
    MsSleep(RTK_MS_TO_TICK(5));//usleep( 500 );
    SENSOR_DMSG( "[%s] power low\n", __FUNCTION__ );
    sensor_if->PowerOff(handle->snr_pad_group, handle->pwdn_POLARITY );
    MsSleep(RTK_MS_TO_TICK(5));//usleep( 500 );
    ///////////////////

    // power -> high, reset -> high
    SENSOR_DMSG( "[%s] power high\n", __FUNCTION__ );
    sensor_if->PowerOff(handle->snr_pad_group, !handle->pwdn_POLARITY );
    MsSleep(RTK_MS_TO_TICK(10));//usleep( 500 );
    sensor_if->PowerOff(handle->snr_pad_group, handle->pwdn_POLARITY );
    MsSleep(RTK_MS_TO_TICK(10));
    sensor_if->PowerOff(handle->snr_pad_group, !handle->pwdn_POLARITY );
    MsSleep(RTK_MS_TO_TICK(10));
    SENSOR_DMSG( "[%s] reset high\n", __FUNCTION__ );
    sensor_if->Reset(handle->snr_pad_group, !handle->reset_POLARITY );
    MsSleep(RTK_MS_TO_TICK(25));

    // pure power on
    sensor_if->PowerOff(handle->snr_pad_group, !handle->pwdn_POLARITY );

    sensor_if->SWReset(handle->channel_num, FALSE);
    return SUCCESS;
}

#if((SENSOR_MODE == SENSOR_MODE_HD_2VC) || (SENSOR_MODE == SENSOR_MODE_FHD_2VC))
static int pCus_poweron_Null( ms_cus_sensor *handle )
{
    return SUCCESS;
}
#endif

static int pCus_poweroff( ms_cus_sensor *handle )
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    SENSOR_DMSG( "[%s] power low\n", __FUNCTION__ );

    sensor_if->SWReset(handle->channel_num, TRUE);

    sensor_if->PowerOff(handle->snr_pad_group, handle->pwdn_POLARITY );
    MsSleep(RTK_MS_TO_TICK(5));//usleep( 1000 );
	sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_DISABLE, handle->PCLK_POLARITY );
    sensor_if->MCLK(handle->snr_pad_group, 0, handle->mclk );

    if(handle->interface_attr.attr_mipi.mipi_lane_num == 2){
        sensor_if->SetCSI_Lane(handle->snr_pad_group, 2, 0);
    }
    else if(handle->interface_attr.attr_mipi.mipi_lane_num == 4){
        sensor_if->SetCSI_Lane(handle->snr_pad_group, 4, 0);
    }
    return SUCCESS;
}

#if((SENSOR_MODE == SENSOR_MODE_HD_2VC) || (SENSOR_MODE == SENSOR_MODE_FHD_2VC))
static int pCus_poweroff_Null( ms_cus_sensor *handle )
{
    return SUCCESS;
}
#endif

static int pCus_GetSensorID( ms_cus_sensor *handle, u32 *id )
{
    *id =0;

    return SUCCESS;
}

static int tp2852_SetPatternMode( ms_cus_sensor *handle, u32 mode )
{

    return SUCCESS;
}

static int pCus_I2CWrite(ms_cus_sensor *handle, unsigned short usreg, unsigned short usval)
{
    unsigned short sen_data;

    SensorReg_Write(usreg, usval);
    SensorReg_Read(usreg, &sen_data);
    UartSendTrace("tp2852_MIPI reg: 0x%x, data: 0x%x, read: 0x%x.\n", usreg, usval, sen_data);

    return SUCCESS;
}

static int pCus_I2CRead(ms_cus_sensor *handle, unsigned short usreg, unsigned short* pusval)
{
    unsigned short usread_data;

    SensorReg_Read(usreg, &usread_data);
    *pusval = usread_data;
    UartSendTrace("tp2852_MIPI reg: 0x%x, data: 0x%x\n", usreg, usread_data);

    return SUCCESS;
}

#if(SENSOR_MODE == SENSOR_MODE_HD_1CH)
static int pCus_init_HD_1CH( ms_cus_sensor *handle )
{
    int i;
    ISensorIfAPI *sensor_if = &( handle->sensor_if_api );
    short sen_data;
    sensor_if->PCLK( CUS_SNR_PCLK_MIPI_TOP );

    UartSendTrace("\n===== tp2852 HD_1CH init. =====\n");

    for( i = 0; i < ARRAY_SIZE( Sensor_init_table_HD_1CH ); i++ )
    {
        if( Sensor_init_table_HD_1CH[i].reg == 0xffff )
        {
            MsSleep(RTK_MS_TO_TICK(1));
        }
        else
        {
            if( SensorReg_Write(Sensor_init_table_HD_1CH[i].reg,Sensor_init_table_HD_1CH[i].data) != SUCCESS )
            {
                return FAIL;
            }
            SensorReg_Read( Sensor_init_table_HD_1CH[i].reg, &sen_data );
            UartSendTrace("tp2852 reg: 0x%x, data: 0x%x, read: 0x%x.\n",Sensor_init_table_HD_1CH[i].reg, Sensor_init_table_HD_1CH[i].data, sen_data);
        }
    }

    return SUCCESS;
}
#endif

#if(SENSOR_MODE == SENSOR_MODE_HD_2VC)
static int pCus_init_HD_2VC( ms_cus_sensor *handle )
{
    int i;
    ISensorIfAPI *sensor_if = &( handle->sensor_if_api );
    short sen_data;
    sensor_if->PCLK( CUS_SNR_PCLK_MIPI_TOP );

    UartSendTrace("\n===== tp2852 HD_2VC init. =====\n");

    for( i = 0; i < ARRAY_SIZE( Sensor_init_table_HD_2VC ); i++ )
    {
        if( Sensor_init_table_HD_2VC[i].reg == 0xffff )
        {
            MsSleep(RTK_MS_TO_TICK(1));
        }
        else
        {
            if( SensorReg_Write(Sensor_init_table_HD_2VC[i].reg,Sensor_init_table_HD_2VC[i].data) != SUCCESS )
            {
                return FAIL;
            }
            SensorReg_Read( Sensor_init_table_HD_2VC[i].reg, &sen_data );
            //UartSendTrace("tp2852 reg: 0x%x, data: 0x%x, read: 0x%x.\n",Sensor_init_table_HD_2VC[i].reg, Sensor_init_table_HD_2VC[i].data, sen_data);
        }
    }

    return SUCCESS;
}
#endif

#if(SENSOR_MODE == SENSOR_MODE_FHD_1CH)
static int pCus_init_FHD_1CH( ms_cus_sensor *handle )
{
    int i;
    ISensorIfAPI *sensor_if = &( handle->sensor_if_api );
    short sen_data;
    sensor_if->PCLK( CUS_SNR_PCLK_MIPI_TOP );

    UartSendTrace("\n===== tp2852 FHD_1CH init. =====\n");

    for( i = 0; i < ARRAY_SIZE( Sensor_init_table_FHD_1CH ); i++ )
    {
        if( Sensor_init_table_FHD_1CH[i].reg == 0xffff )
        {
            MsSleep(RTK_MS_TO_TICK(1));
        }
        else
        {
            if( SensorReg_Write(Sensor_init_table_FHD_1CH[i].reg,Sensor_init_table_FHD_1CH[i].data) != SUCCESS )
            {
                return FAIL;
            }
            SensorReg_Read( Sensor_init_table_FHD_1CH[i].reg, &sen_data );
            UartSendTrace("tp2852 reg: 0x%x, data: 0x%x, read: 0x%x.\n",Sensor_init_table_FHD_1CH[i].reg, Sensor_init_table_FHD_1CH[i].data, sen_data);
        }
    }

    return SUCCESS;
}
#endif

#if(SENSOR_MODE == SENSOR_MODE_FHD_2VC)
static int pCus_init_FHD_2VC( ms_cus_sensor *handle )
{
    int i;
    ISensorIfAPI *sensor_if = &( handle->sensor_if_api );
    short sen_data;
    sensor_if->PCLK( CUS_SNR_PCLK_MIPI_TOP );

    UartSendTrace("\n===== tp2852 FHD_2VC init. =====\n");

    for( i = 0; i < ARRAY_SIZE( Sensor_init_table_FHD_2VC ); i++ )
    {
        if( Sensor_init_table_FHD_2VC[i].reg == 0xffff )
        {
            MsSleep(RTK_MS_TO_TICK(1));
        }
        else
        {
            if( SensorReg_Write(Sensor_init_table_FHD_2VC[i].reg,Sensor_init_table_FHD_2VC[i].data) != SUCCESS )
            {
                return FAIL;
            }
            SensorReg_Read( Sensor_init_table_FHD_2VC[i].reg, &sen_data );
            UartSendTrace("tp2852 reg: 0x%x, data: 0x%x, read: 0x%x.\n",Sensor_init_table_FHD_2VC[i].reg, Sensor_init_table_FHD_2VC[i].data, sen_data);
        }
    }

    return SUCCESS;
}
#endif

#if((SENSOR_MODE == SENSOR_MODE_HD_2VC) || (SENSOR_MODE == SENSOR_MODE_FHD_2VC))
static int pCus_init_Null( ms_cus_sensor *handle )
{
    return SUCCESS;
}
#endif

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
    #if 0
    //switch(res){
        //case SENSOR_DRIVER_MODE_FULL_HD_30P_RESOLUTION:
            handle->video_res_supported.ulcur_res = 0; //TBD
            handle->pCus_sensor_init = pCus_init_HD;
            //break;

        //default:
        //    UartSendTrace("[%s] Line:%d fail. res:%d\n",__FUNCTION__, __LINE__, res);
        //    break;
    //}

    //sensor_if->WaitVEnd( 50 );
    #endif

    handle->video_res_supported.ulcur_res = 0; //TBD
    #if(SENSOR_MODE == SENSOR_MODE_HD_1CH)
    handle->pCus_sensor_init = pCus_init_HD_1CH;
    #endif
    #if(SENSOR_MODE == SENSOR_MODE_HD_2VC)
    handle->pCus_sensor_init = pCus_init_HD_2VC;
    #endif
    #if(SENSOR_MODE == SENSOR_MODE_FHD_1CH)
    handle->pCus_sensor_init = pCus_init_FHD_1CH;
    #endif
    #if(SENSOR_MODE == SENSOR_MODE_FHD_2VC)
    handle->pCus_sensor_init = pCus_init_FHD_2VC;
    #endif

    return SUCCESS;
}

static int pCus_GetOrien( ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT *orit )
{
    tp2852_params *params = ( tp2852_params * ) handle->private_data;
    return params->mirror_flip.cur;
}

static int pCus_SetOrien( ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT orit )
{
    tp2852_params *params = ( tp2852_params * ) handle->private_data;
    params->mirror_flip.new_setting = orit;
    //DoMirror( handle, params->mirror_flip.new_setting );
    return SUCCESS;
}

static int pCus_GetFPS( ms_cus_sensor *handle )
{
    tp2852_params *params = ( tp2852_params * ) handle->private_data;
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

static int TP2852_GetShutterInfo( struct __ms_cus_sensor* handle, CUS_SHUTTER_INFO *info )
{
     return SUCCESS;
}

static int pCus_Sensor_GetSrcType(ms_cus_sensor *handle, CUS_SNR_ANADEC_SRC_TYPE *psrc_type)
{
	#define VIDEOINPUTREG 0x01
	#define DETECTREG    0x03
	#define PAGEREG      0x40
	#define PAGEVIN4     0x03
	#define PAGEVIN3     0x02
    #define PAGEMIPI     0x08
    #define PAGEVIDEO    0x04
	#define RES_HD60     0x00
	#define RES_HD50     0x01
	#define RES_FHD30    0x02
	#define RES_FHD25    0x03
	#define RES_HD30     0x04
	#define RES_HD25     0x05
	unsigned short usCnntStatus4, usCnntStatus3, usCurRes4, usCurRes3;
    unsigned short readdata_chnnl3[0x40],readdata_chnnl4[0x40] ,i;

	//for current application,this function only detect VIN4 and VIN3. TBD.
	*psrc_type = CUS_SNR_ANADEC_SRC_NO_READY;
	//switch VIN4
	if(SUCCESS != SensorReg_Write(PAGEREG, PAGEVIN4)){
		*psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
	}
	//Read VIN4 0x01.
    if (SUCCESS != SensorReg_Read(VIDEOINPUTREG, &usCnntStatus4)) {
        *psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
    }
	//Read VIN4 0x03.
	if (SUCCESS != SensorReg_Read(DETECTREG, &usCurRes4)) {
        *psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
    }
	//switch VIN3
	if(SUCCESS != SensorReg_Write(PAGEREG, PAGEVIN3)){
		*psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
	}
	//Read VIN3 0x01.
    if (SUCCESS != SensorReg_Read(VIDEOINPUTREG, &usCnntStatus3)) {
        *psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
    }
	//Read VIN3 0x03.
	if (SUCCESS != SensorReg_Read(DETECTREG, &usCurRes3)) {
        *psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
    }

    //debug mipi setting of tp2852
    #if 0
    UartSendTrace("PAGEMIPI:\n");
    if(SUCCESS != SensorReg_Write(PAGEREG, PAGEMIPI)){
		*psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
	}
    for(i=0;i<0x40;i++){
        if (/*(i==0x30||i==0x31||i==0x32||i==0x33||i==0x2d) && */
            SUCCESS != SensorReg_Read(i, &readdata_chnnl4[i])) {
            *psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
            return FAIL;
        }

        UartSendTrace("0x%02X ", readdata_chnnl4[i]);
        if(i%16 == 15)
            UartSendTrace("\n");
    }

    UartSendTrace("PAGEVIN3:\n");
    if(SUCCESS != SensorReg_Write(PAGEREG, PAGEVIN3)){
		*psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
	}
    for(i=0;i<0x40;i++){
        if (/*(i==0x30||i==0x31||i==0x32||i==0x33||i==0x2d) && */
            SUCCESS != SensorReg_Read(i, &readdata_chnnl3[i])) {
            *psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
            return FAIL;
        }

        UartSendTrace("0x%02X ", readdata_chnnl3[i]);
        if(i%16 == 15)
            UartSendTrace("\n");
    }
    UartSendTrace("PAGEVIN4:\n");
    if(SUCCESS != SensorReg_Write(PAGEREG, PAGEVIN4)){
		*psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
        return FAIL;
	}
    for(i=0;i<0x40;i++){
        if (/*(i==0x30||i==0x31||i==0x32||i==0x33||i==0x2d) && */
            SUCCESS != SensorReg_Read(i, &readdata_chnnl3[i])) {
            *psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
            return FAIL;
        }

        UartSendTrace("0x%02X ", readdata_chnnl3[i]);
        if(i%16 == 15)
            UartSendTrace("\n");
    }
    #endif

	#if 0
    UartSendTrace("usCnntStatus4=0x%X\n", usCnntStatus4);
    UartSendTrace("usCurRes4=0x%X\n", usCurRes4);
    UartSendTrace("usCnntStatus3=0x%X\n", usCnntStatus3);
    UartSendTrace("usCurRes3=0x%X\n", usCurRes3);
    #endif

    if(MMPF_GetANACamType() == ANA_CAM_2I1O){
        if(usCnntStatus4 == 0x7e && usCnntStatus3 == 0x7e)
    	{
    		if((usCurRes4&0x07) == RES_HD60 ||
    		   (usCurRes4&0x07) == RES_HD50 ||
    		   (usCurRes4&0x07) == RES_HD30 ||
    		   (usCurRes4&0x07) == RES_HD25){
    			*psrc_type = CUS_SNR_ANADEC_SRC_HD;
    		}
    		else if((usCurRes4&0x07) == RES_FHD30 ||
    		   		(usCurRes4&0x07) == RES_FHD25){
    			*psrc_type = CUS_SNR_ANADEC_SRC_FHD;
    		}
    	}
        else{
    		*psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
    	}
    }else{
    	//mapping , VIN4:Prm, VIN3:SCD
    	if(usCnntStatus4 == 0x7e /*&& usCnntStatus3 == 0x7e*/)//0x7e
    	{
    		if((usCurRes4&0x07) == RES_HD60 ||
    		   (usCurRes4&0x07) == RES_HD50 ||
    		   (usCurRes4&0x07) == RES_HD30 ||
    		   (usCurRes4&0x07) == RES_HD25){
    			*psrc_type = CUS_SNR_ANADEC_SRC_HD;
    		}
    		else if((usCurRes4&0x07) == RES_FHD30 ||
    		   		(usCurRes4&0x07) == RES_FHD25){
    			*psrc_type = CUS_SNR_ANADEC_SRC_FHD;
    		}
    	}
    	else if (usCnntStatus3 == 0x7e)
    	{
    		if((usCurRes3&0x07) == RES_HD60 ||
    		   (usCurRes3&0x07) == RES_HD50 ||
    		   (usCurRes3&0x07) == RES_HD30 ||
    		   (usCurRes3&0x07) == RES_HD25){
    			*psrc_type = CUS_SNR_ANADEC_SRC_HD;
    		}
    		else if((usCurRes3&0x07) == RES_FHD30 ||
    		   		(usCurRes3&0x07) == RES_FHD25){
    			*psrc_type = CUS_SNR_ANADEC_SRC_FHD;
    		}
    	}
    	else
    	{
    		*psrc_type = CUS_SNR_ANADEC_SRC_DISCNT;
    	}
    }
}

int tp2852_MIPI_cus_camsensor_init_handle( ms_cus_sensor* drv_handle )
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
    sprintf(str, "TP2852");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(tp2852_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (tp2852_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(tp2852_params));
#else
    handle->private_data = calloc( 1, sizeof(tp2852_params) );
#endif

    tp2852_params *params = ( tp2852_params * ) handle->private_data;

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

    #if((SENSOR_MODE == SENSOR_MODE_HD_1CH) || (SENSOR_MODE == SENSOR_MODE_FHD_1CH))
    handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_NONE;
    handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 0;
    #else
    handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_DCG; //???
    handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 0; //Short frame //???
    #endif
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
    handle->pCus_sensor_release = tp2852_MIPI_cus_camsensor_release_handle;

    #if(SENSOR_MODE == SENSOR_MODE_HD_1CH)
    handle->pCus_sensor_init = pCus_init_HD_1CH;
    #endif
    #if(SENSOR_MODE == SENSOR_MODE_HD_2VC)
    handle->pCus_sensor_init = pCus_init_HD_2VC;
    #endif
    #if(SENSOR_MODE == SENSOR_MODE_FHD_1CH)
    handle->pCus_sensor_init = pCus_init_FHD_1CH;
    #endif
    #if(SENSOR_MODE == SENSOR_MODE_FHD_2VC)
    handle->pCus_sensor_init = pCus_init_FHD_2VC;
    #endif

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
    handle->pCus_sensor_SetPatternMode = tp2852_SetPatternMode;

    handle->pCus_sensor_AEStatusNotify = pCus_AEStatusNotify;
    handle->pCus_sensor_GetAEUSecs = pCus_GetAEUSecs;
    handle->pCus_sensor_SetAEUSecs = pCus_SetAEUSecs;
    handle->pCus_sensor_GetAEGain = pCus_GetAEGain;
    handle->pCus_sensor_SetAEGain_cal = pCus_SetAEGain_cal;
    handle->pCus_sensor_SetAEGain = pCus_SetAEGain;

    handle->pCus_sensor_GetAEMinMaxGain = pCus_GetAEMinMaxGain;
    handle->pCus_sensor_GetAEMinMaxUSecs = pCus_GetAEMinMaxUSecs;
    handle->pCus_sensor_GetDGainRemainder = pCus_GetDGainRemainder;
    handle->pCus_sensor_GetShutterInfo = TP2852_GetShutterInfo;
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

#if((SENSOR_MODE == SENSOR_MODE_HD_2VC) || (SENSOR_MODE == SENSOR_MODE_FHD_2VC))
int tp2852_MIPI_cus_camsensor_init_handle_vc2( ms_cus_sensor* drv_handle )
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
    sprintf(str, "TP2852");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(tp2852_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (tp2852_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(tp2852_params));
#else
    handle->private_data = calloc( 1, sizeof(tp2852_params) );
#endif

    tp2852_params *params = ( tp2852_params * ) handle->private_data;

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

    //#if((SENSOR_MODE == SENSOR_MODE_HD_1CH) || (SENSOR_MODE == SENSOR_MODE_FHD_1CH))
    //handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_NONE; //???
    //handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 1; //Short frame //???
    //#else
    handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_DCG; //???
    handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 1; //Short frame //???
    //#endif

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
    handle->pCus_sensor_release = tp2852_MIPI_cus_camsensor_release_handle;

    handle->pCus_sensor_init = pCus_init_Null;

    handle->pCus_sensor_poweron = pCus_poweron_Null;
    handle->pCus_sensor_poweroff = pCus_poweroff_Null;

    handle->pCus_sensor_GetSensorID = pCus_GetSensorID;
    handle->pCus_sensor_GetVideoResNum = pCus_GetVideoResNum;
    handle->pCus_sensor_GetVideoRes = pCus_GetVideoRes;
    handle->pCus_sensor_SetVideoRes = pCus_SetVideoRes;
    handle->pCus_sensor_GetOrien = pCus_GetOrien;
    handle->pCus_sensor_SetOrien = pCus_SetOrien;
    handle->pCus_sensor_GetFPS = pCus_GetFPS;
    handle->pCus_sensor_SetFPS = pCus_SetFPS;
    handle->pCus_sensor_GetSensorCap = pCus_GetSensorCap;
    handle->pCus_sensor_SetPatternMode = tp2852_SetPatternMode;

    handle->pCus_sensor_AEStatusNotify = pCus_AEStatusNotify;
    handle->pCus_sensor_GetAEUSecs = pCus_GetAEUSecs;
    handle->pCus_sensor_SetAEUSecs = pCus_SetAEUSecs;
    handle->pCus_sensor_GetAEGain = pCus_GetAEGain;
    handle->pCus_sensor_SetAEGain_cal = pCus_SetAEGain_cal;
    handle->pCus_sensor_SetAEGain = pCus_SetAEGain;

    handle->pCus_sensor_GetAEMinMaxGain = pCus_GetAEMinMaxGain;
    handle->pCus_sensor_GetAEMinMaxUSecs = pCus_GetAEMinMaxUSecs;
    handle->pCus_sensor_GetDGainRemainder = pCus_GetDGainRemainder;
    handle->pCus_sensor_GetShutterInfo = TP2852_GetShutterInfo;
    handle->pCus_sensor_setCaliData_gain_linearity = pCus_setCaliData_gain_linearity;

    handle->pCus_sensor_I2CWrite = pCus_I2CWrite;
    handle->pCus_sensor_I2CRead = pCus_I2CRead;

    params->expo.vts = vts_30fps;
    params->expo.fps = 30;
    params->reg_dirty = false;
    params->reg_dirty_cnt = 0;

    handle->snr_pad_group = SENSOR_PAD_GROUP_SET;

    handle->channel_num = SENSOR_CHANNEL_NUM+1;
    handle->channel_mode = SENSOR_CHANNEL_MODE_LINEAR;

    return SUCCESS;
}
#endif //((SENSOR_MODE == SENSOR_MODE_HD_2VC) || (SENSOR_MODE == SENSOR_MODE_FHD_2VC))

int tp2852_MIPI_cus_camsensor_release_handle( ms_cus_sensor *handle )
{
#if defined(__RTK_OS__)
    CamOsRet_e                  eCamOsRet = CAM_OS_OK;
#endif

    if( handle && handle->private_data )
    {
        SENSOR_IMSG("[%s] release handle 0x%x, private data %x\n",__FUNCTION__,(int)handle,(int)handle->private_data);
#if defined(__RTK_OS__)
        eCamOsRet = CamOsDirectMemRelease((void*)handle->private_data, sizeof(tp2852_params));
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
struct SensorMapTable_t gsensor_map_tp2852[] = {
    { //Channel 0
        SENSOR_CHANNEL_NUM,
        tp2852_MIPI_cus_camsensor_init_handle,
        tp2852_MIPI_cus_camsensor_release_handle
    },
    #if((SENSOR_MODE == SENSOR_MODE_HD_2VC) || (SENSOR_MODE == SENSOR_MODE_FHD_2VC))
    { //Channel 1
        SENSOR_CHANNEL_NUM+1,
        tp2852_MIPI_cus_camsensor_init_handle_vc2,
        tp2852_MIPI_cus_camsensor_release_handle
    },
    #endif
};

int TP2852_Module_Init(void)
{
    cameraSensorRegister(&gsensor_map_tp2852[0]);
    #if((SENSOR_MODE == SENSOR_MODE_HD_2VC) || (SENSOR_MODE == SENSOR_MODE_FHD_2VC))
    cameraSensorRegister(&gsensor_map_tp2852[1]);
    MMPF_SetRawStoreNum(2);
    #endif

    #if(SENSOR_MODE == SENSOR_MODE_HD_2VC)
    MMPF_SetANACamType(ANA_CAM_2I1O);//debug TBD
    #endif
    #if (SENSOR_MODE == SENSOR_MODE_FHD_2VC)
    MMPF_SetANACamType(ANA_CAM_2I2O);
    #endif
    return 0;
}

void TP2852_Module_Exit(void)
{
    cameraSensorUnRegister(&gsensor_map_tp2852[0]);
    #if((SENSOR_MODE == SENSOR_MODE_HD_2VC) || (SENSOR_MODE == SENSOR_MODE_FHD_2VC))
    cameraSensorUnRegister(&gsensor_map_tp2852[1]);
    #endif
}

#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(TP2852_Module_Init);
//ait_module_exit(TP2852_Module_Exit);
#endif //#if defined(__RTK_OS__)

#endif //#if defined(BIND_SENSOR_TP2852_MIPI) && (BIND_SENSOR_TP2852_MIPI == 1)
