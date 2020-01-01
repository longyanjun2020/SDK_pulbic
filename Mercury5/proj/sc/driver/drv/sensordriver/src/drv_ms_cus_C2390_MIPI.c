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
#include "drv_pm_chip.h"

#if defined(__RTK_OS__)
#if defined(__GNUC__)
#include "vm_types.ht"
#endif
#include "libcamera.h"
#include "AIT_Init.h"
#include "Config_SDK.h" //By project.
#else //#if defined(__RTK_OS__)

#include "isp_config.h"
#if (SENSOR0 == C2390)
#define BIND_SENSOR_C2390 (1)
#endif
#endif //#if defined(__RTK_OS__)

#if defined(BIND_SENSOR_C2390) && (BIND_SENSOR_C2390 == 1)

#define SENSOR_PAD_GROUP_SET CUS_SENSOR_PAD_GROUP_A
#define SENSOR_CHANNEL_NUM (0)
#define SENSOR_CHANNEL_MODE CUS_SENSOR_CHANNEL_MODE_RAW_STORE_LI_HDR//CUS_SENSOR_CHANNEL_MODE_RAW_STORE_LI_HDR //CUS_SENSOR_CHANNEL_MODE_REALTIME_NORMAL
//DCG HDR 
#define SENSOR_CHANNEL_MODE_LEF CUS_SENSOR_CHANNEL_MODE_REALTIME_HDR
#define SENSOR_DCGHDR_MODE CUS_SENSOR_DCGHDR_NONE


//============================================
//MIPI config begin.
#define SENSOR_MIPI_LANE_NUM (2)
#define SENSOR_MIPI_HDR_MODE (0) //0: Linear mode. 1:HDR_16b_combined_DCG. 2:HDR_VS_2x12b_DCG_HCG
//MIPI config end.
//============================================

#define RES_IDX_1920x1080_30P       (0)     // mode 4,  1920*1080 30P       // Video (16:9)
#define RES_IDX_1280x720_60P        (1)     // mode 9,  1280*720  60P       // Video (16:9)

#define SENSOR_MODEL_ID     "C2390_MIPI"
#define SENSOR_ISP_TYPE     ISP_EXT                //ISP_EXT, ISP_SOC
#define SENSOR_IFBUS_TYPE   CUS_SENIF_BUS_MIPI     //CFG //CUS_SENIF_BUS_PARL, CUS_SENIF_BUS_MIPI
#define SENSOR_MIPI_HSYNC_MODE PACKET_FOOTER_EDGE
#define SENSOR_MIPI_DELAY   0x1212                 //CFG
#define SENSOR_DATAPREC     CUS_DATAPRECISION_10   //CFG //CUS_DATAPRECISION_8, CUS_DATAPRECISION_10
#define SENSOR_DATAMODE     CUS_SEN_10TO12_9000    //CFG
#define SENSOR_BAYERID      CUS_BAYER_BG           //CFG //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
#define SENSOR_ORIT         CUS_ORIT_M0F0          //CUS_ORIT_M0F0, CUS_ORIT_M1F0, CUS_ORIT_M0F1, CUS_ORIT_M1F1,
#define SENSOR_MAX_GAIN     65536
#define SENSOR_MIN_GAIN      2048
#define Preview_MCLK_SPEED  CUS_CMU_CLK_24MHZ //CUS_CMU_CLK_27MHZ        //CFG //CUS_CMU_CLK_12M, CUS_CMU_CLK_16M, CUS_CMU_CLK_24M, CUS_CMU_CLK_27M
#define Preview_line_period 29626                  ////HTS/PCLK=2420 pixels/80MHZ=30.250us
#define Prv_Max_line_number 1080                   //maximum exposure line munber of sensor when preview
#define vts_30fps  1125                            //Virt Total Size , 30.25us * 1111 =  33.6ms frame interval =30 fps
#define Preview_WIDTH       1920                   //resolution Width when preview
#define Preview_HEIGHT      1080                   //resolution Height when preview
#define Preview_MAX_FPS     30                     //fastest preview FPS
#define Preview_MIN_FPS     8                      //slowest preview FPS
#define Preview_CROP_START_X     0//1              //CROP_START_X
#define Preview_CROP_START_Y     0//1              //CROP_START_Y

#define Cap_Max_line_number 1080                   //maximum exposure line munber of sensor when capture

#define SENSOR_I2C_ADDR    0x6c                         //I2C slave address
#define SENSOR_I2C_SPEED    I2C_SLOWSPEED_MODE_200KHZ   //200KHz
#define SENSOR_I2C_CHANNEL  1                           //I2C Channel
#define SENSOR_I2C_PAD_MODE 2                           //Pad/Mode Number

#define SENSOR_I2C_LEGACY  I2C_NORMAL_MODE     //usally set CUS_I2C_NORMAL_MODE,  if use old OVT I2C protocol=> set CUS_I2C_LEGACY_MODE
#define SENSOR_I2C_FMT     I2C_FMT_A16D8        //CUS_I2C_FMT_A8D8, CUS_I2C_FMT_A8D16, CUS_I2C_FMT_A16D8, CUS_I2C_FMT_A16D16

//#if (SENSOR_PAD_GROUP_SET == 0)
#define SENSOR_PWDN_POL     CUS_CLK_POL_POS
//#else
//#define SENSOR_PWDN_POL     CUS_CLK_POL_NEG        // if PWDN pin High can makes sensor in power down, set CUS_CLK_POL_POS
//#endif

#define SENSOR_RST_POL      CUS_CLK_POL_NEG//CUS_CLK_POL_NEG        // if RESET pin High can makes sensor in reset state, set CUS_CLK_POL_NEG

// VSYNC/HSYNC POL can be found in data sheet timing diagram,
// Notice: the initial setting may contain VSYNC/HSYNC POL inverse settings so that condition is different.

#define SENSOR_VSYNC_POL    CUS_CLK_POL_NEG        // if VSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_HSYNC_POL    CUS_CLK_POL_POS        // if HSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_PCLK_POL     CUS_CLK_POL_POS        // depend on sensor setting, sometimes need to try CUS_CLK_POL_POS or CUS_CLK_POL_NEG

#define C2390_GET_MIN(a, b)                   ( ((a) < (b)) ? (a) : (b) )
#define C2390_GET_MAX(a, b)                   ( ((a) > (b)) ? (a) : (b) )

#if (SENSOR_MIPI_HDR_MODE == 2) //Merged from Mv2.
#define MAX_SENSOR_GAIN_HCG_LCG     (64*11)
#define MAX_SENSOR_GAIN_VS     (64)
#define ISP_DGAIN_BASE      (0x200)
#define SENSOR_GAIN_BASE      (0x100)

//static  u32 ae_gain_l    = 1024;
//static  u32 ae_shutter_l = 256;
//static  u32 ae_gain_s    = 1024;
//static  u32 ae_shutter_s = 256;

static u32 HCG_AGain = 0;
static u32 HCG_DGain = 0x100;
static u32 LCG_AGain = 0;
static u32 LCG_DGain = 0x100;
static u32 VS_AGain = 0;
static u32 VS_DGain = 0x100;

static u32 new_shutter_l = 0;
static u32 new_shutter_s = 0;

static u8 HCG_switch = 0x85;
#endif

#if (SENSOR_PAD_GROUP_SET == CUS_SENSOR_PAD_GROUP_A)
static u32 DataLaneSelArray[5] = {1, 2, 0, 3, 4};
static u32 HsTxPolarityArray[5] = {0, 0, 0, 0, 0};
#elif (SENSOR_PAD_GROUP_SET == CUS_SENSOR_PAD_GROUP_B)
static u32 DataLaneSelArray[5] = {1, 0, 2, 0, 0};
static u32 HsTxPolarityArray[5] = {0, 0, 0, 0, 0};
#endif
static u8 SensorChannelMode = SENSOR_CHANNEL_MODE;
int c2390_MIPI_cus_camsensor_release_handle( ms_cus_sensor *handle );

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
} c2390_params;

static I2C_ARRAY Sensor_id_table[] =
{};

static I2C_ARRAY Sensor_init_table_2lane_linear[] =
{
//V9.7 [MIPI_2_1080P_HDR_30fps_24Mhz_800Mbps]
{0x0103,0x01},
{0x0003,0x00},
{0x0003,0x00},
{0x0003,0x00},
{0x0003,0x00},
{0x0003,0x00},
{0x0003,0x00},
{0x0003,0x00},
{0x0003,0x00},
{0x0003,0x00},
{0x0003,0x00},
{0x0003,0x00},
{0x3000,0x80},
{0x3080,0x01},
{0x3081,0x14},
{0x3082,0x01},
{0x3083,0x4b},
{0x3087,0xd0},
{0x3089,0x10},
{0x3180,0x10},
{0x3182,0x30},
{0x3183,0x10},
{0x3184,0x20},
{0x3185,0xc0},
{0x3189,0x50},
{0x3c03,0x00},
{0x3f8c,0x00},
{0x320f,0x48},
{0x3023,0x00},
{0x3d00,0x33},
{0x3c9d,0x01},
{0x3f08,0x00},
{0x3b80,0x42},
{0x3b81,0x10},
{0x3b82,0x10},
{0x3b83,0x10},
{0x3b84,0x04},
{0x3b85,0x30},
{0x3b86,0x80},
{0x0309,0x2e},
{0x0303,0x01},
{0x0304,0x00},
{0x0307,0x64},
{0x3508,0x00},
{0x350a,0x33},
{0x3292,0x28},
{0x3209,0x05},
{0x0003,0x00},
{0x0003,0x00},
{0x0003,0x00},
{0x0003,0x00},
{0x3209,0x04},
{0x3108,0xcd},
{0x3109,0xbc},
{0x310a,0x84},
{0x310b,0x42},
{0x3112,0x43},
{0x3113,0x01},
{0x3114,0xc0},
{0x3115,0x10},
{0x3905,0x01},
{0x3980,0x01},
{0x3881,0x04},
{0x3882,0x15},
{0x328b,0x03},
{0x328c,0x00},
{0x3981,0x57},
{0x3180,0xd8},
{0x3213,0x8a},
{0x3205,0x40},
{0x3208,0x8d},
{0x3210,0x12},
{0x3211,0x55},
{0x3212,0x50},
{0x3215,0x50},
{0x3216,0x60},
{0x3217,0x10},
{0x3218,0x20},
{0x321a,0x80},
{0x321b,0x00},
{0x321c,0x1a},
{0x321e,0x00},
{0x3223,0x10},
{0x3224,0x80},
{0x3225,0x00},
{0x3226,0x08},
{0x3227,0x00},
{0x3228,0x00},
{0x3229,0x08},
{0x322a,0x10},
{0x322b,0x44},
{0x308a,0x00},
{0x308b,0x00},
{0x3280,0x06},
{0x3281,0x30},
{0x3282,0x1a},
{0x3283,0x51},
{0x3284,0x0d},
{0x3285,0x4B},
{0x3286,0x3b},
{0x3287,0x07},
{0x3288,0x0f},
{0x3289,0x00},
{0x328a,0x08},
{0x328d,0x06},
{0x328e,0x10},
{0x328f,0x0d},
{0x3290,0x10},
{0x3291,0x00},
{0x3292,0x28},
{0x3293,0x00},
{0x3216,0x70},
{0x3217,0x08},
{0x3205,0x40},
{0x3215,0xa0},
{0x3223,0x20},
{0x3280,0x07},
{0x308b,0x0f},
{0x3184,0x20},
{0x3185,0xcc},
{0x3189,0x50},
{0x3280,0x87},
{0x0003,0x00},
{0x3280,0x07},
{0x3d00,0x00},
{0x0383,0x01},
{0x0387,0x01},
{0x0340,0x04},
{0x0341,0x50},
{0x0342,0x09},
{0x0343,0x6c},
{0x034c,0x07},
{0x034d,0x80},
{0x034e,0x08},
{0x034f,0x70},
{0x3b86,0x80},
{0x3021,0x11},
{0x3022,0xa2},
{0x3209,0x00},
{0x3805,0x09},
{0x3806,0x06},
{0x3807,0x06},
{0x3808,0x1a},
{0x3809,0xa7},
{0x380a,0x8e},
{0x380b,0xec},
{0x3500,0x10},
{0x308c,0x20},
{0x308d,0x31},
{0x3403,0x00},
{0x3407,0x01},
{0x3410,0x04},
{0x3411,0x18},
{0x3414,0x01},
{0x3415,0x02},
{0xe000,0x32},
{0xe001,0x85},
{0xe002,0x4B},
{0xe030,0x32},
{0xe031,0x85},
{0xe032,0x4B},
{0xe120,0x35},
{0xe121,0x00},
{0xe122,0x02},
{0xe123,0x03},
{0xe124,0x09},
{0xe125,0x2e},
{0x3500,0x00},
{0x3a87,0x04},
{0x3a88,0x10},
{0x3a89,0x60},
{0x3a8a,0x03},
{0x3a8b,0x20},
{0x3a80,0x88},
{0x3a81,0x02},
{0x3009,0x08},
{0x300b,0x08},
{0x034b,0x47},
{0x0202,0x04},
{0x0203,0x50},

//
//{0x3c00,0x04},  //Color bar


{0x3500,0x00},  //[Stream on]
{0x0309,0x26},
{0x0100,0x01},
{0x0003,0x00},
{0x0003,0x00},
{0x0003,0x00},
};

#if 0
static I2C_ARRAY Sensor_init_table_2lane_linear[] =            // 1920*1080_30fps_27MCLK_756MMIPI_2840*1109*30
{};
#endif

static I2C_ARRAY PatternTbl[] =
{};

static I2C_ARRAY Current_Mirror_Flip_Tbl[] =
{};

static I2C_ARRAY mirr_flip_table[] =
{};

static I2C_ARRAY gain_reg[] =
{};

static CUS_GAIN_GAP_ARRAY gain_gap_compensate[16] =
{};
static I2C_ARRAY expo_reg[] =
{};

static I2C_ARRAY vts_reg[] =
{};

static int pCus_poweron( ms_cus_sensor *handle )
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    SENSOR_DMSG( "[%s] ", __FUNCTION__ );

#if (SENSOR_MIPI_LANE_NUM == 2)
    if(SENSOR_PAD_GROUP_SET == 0) {
        printc("Rogers: GroupA\r\n");
        sensor_if->SetIOPad(SENSOR_PAD_GROUP_SET, CUS_SENIF_BUS_MIPI, CUS_SR0_MIPI_MODE_2 );
    }
    else {
        printc("Rogers: GroupB\r\n");
        sensor_if->SetIOPad(SENSOR_PAD_GROUP_SET, CUS_SENIF_BUS_MIPI, CUS_SR1_MIPI_MODE_1 );
    }
#endif
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_216M, handle->PCLK_POLARITY);
#if (SENSOR_MIPI_LANE_NUM == 2)
    sensor_if->SetCSI_Lane(SENSOR_PAD_GROUP_SET, 2, 1);
#endif
    sensor_if->MCLK(SENSOR_PAD_GROUP_SET, 1, handle->mclk);
    //  sensor_if->SetCSI_LongPacketType(handle,0xff00000000);

    SENSOR_DMSG( "[%s] reset low\n", __FUNCTION__ );
    sensor_if->Reset(SENSOR_PAD_GROUP_SET, handle->reset_POLARITY );
    MsSleep(RTK_MS_TO_TICK(5));//usleep( 500 );
    SENSOR_DMSG( "[%s] power low\n", __FUNCTION__ );
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, handle->pwdn_POLARITY );
    MsSleep(RTK_MS_TO_TICK(5));//usleep( 500 );
    ///////////////////

    // power -> high, reset -> high
    SENSOR_DMSG( "[%s] power high\n", __FUNCTION__ );
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, !handle->pwdn_POLARITY );
    MsSleep(RTK_MS_TO_TICK(10));//usleep( 500 );
    SENSOR_DMSG( "[%s] reset high\n", __FUNCTION__ );
    sensor_if->Reset(SENSOR_PAD_GROUP_SET, !handle->reset_POLARITY );
    MsSleep(RTK_MS_TO_TICK(5));//usleep( 500 );

    // pure power on
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, !handle->pwdn_POLARITY );
	sensor_if->SWReset(handle->channel_num, FALSE);
    return SUCCESS;
}

static int pCus_poweroff( ms_cus_sensor *handle )
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    SENSOR_DMSG( "[%s] power low\n", __FUNCTION__ );
	sensor_if->SWReset(handle->channel_num, TRUE);
    sensor_if->PowerOff( 1, handle->pwdn_POLARITY );
    MsSleep(RTK_MS_TO_TICK(5));//usleep( 1000 );
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_DISABLE, handle->PCLK_POLARITY);
    sensor_if->MCLK(0, 0, handle->mclk );
#if (SENSOR_MIPI_LANE_NUM == 2)
    sensor_if->SetCSI_Lane(SENSOR_PAD_GROUP_SET, 2, 0);
#endif
    return SUCCESS;
}

static int pCus_GetSensorID( ms_cus_sensor *handle, u32 *id )
{
    int i, n;
    int table_length = ARRAY_SIZE( Sensor_id_table );
    I2C_ARRAY id_from_sensor[ARRAY_SIZE( Sensor_id_table )];

    for( n = 0; n < table_length; ++n )
    {
        id_from_sensor[n].reg = Sensor_id_table[n].reg;
        id_from_sensor[n].data = 0;
    }

    *id = 0;
    if( table_length > 8 )
        table_length = 8;

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
            MsSleep(RTK_MS_TO_TICK(1));//usleep( 1*1000 );
    }

    short sen_data1;
    SensorReg_Read( 0x7a02, &sen_data1 );
    SENSOR_IMSG( "sen_data1=0x%x\n", sen_data1 );
    if( sen_data1 != 0x18 )
        return FAIL;

    short OTP_7a0e, OTP_7a03, OTP_7a04, OTP_7a05, OTP_7a06, OTP_7a07, OTP_7a08;

    SensorReg_Read( 0x7a03, &OTP_7a03 );
    SENSOR_IMSG( "OTP_7a03=0x%x\n", OTP_7a03 );
    SensorReg_Read( 0x7a04, &OTP_7a04 );
    SENSOR_IMSG( "OTP_7a04=0x%x\n", OTP_7a04 );
    SensorReg_Read( 0x7a05, &OTP_7a05 );
    SENSOR_IMSG( "OTP_7a05=0x%x\n", OTP_7a05 );
    SensorReg_Read( 0x7a06, &OTP_7a06 );
    SENSOR_IMSG( "OTP_7a06=0x%x\n", OTP_7a06 );
    SensorReg_Read( 0x7a07, &OTP_7a07 );
    SENSOR_IMSG( "OTP_7a07=0x%x\n", OTP_7a07 );
    SensorReg_Read( 0x7a08, &OTP_7a08 );
    SENSOR_IMSG( "OTP_7a08=0x%x\n", OTP_7a08 );
    SensorReg_Read( 0x7a0e, &OTP_7a0e );
    SENSOR_IMSG( "OTP_7a0e=0x%x\n", OTP_7a0e );

    if( ( OTP_7a03 == 0x19 ) && ( OTP_7a04 == 0x06 ) && ( OTP_7a05 == 0x20 ) && ( OTP_7a06 == 0x06 ) && ( OTP_7a07 == 0x02 )
                    && ( OTP_7a08 == 0x01 ) )
    {
        SENSOR_IMSG( "[%s] This is C2390 R2A version\n", __FUNCTION__ );
        return FAIL;
    }

    SENSOR_IMSG("[%s] %s get sensor id:0x%x, SUCCESS!\n", __FUNCTION__, handle->model_id, ( int )*id);
    return SUCCESS;
}

static int c2390_SetPatternMode( ms_cus_sensor *handle, u32 mode )
{
    switch( mode )
    {
        case 1:
            PatternTbl[0].data |= 0x01;            //enable
            break;
        case 0:
            PatternTbl[0].data &= 0xfe;            //disable
            break;
        default:
            PatternTbl[0].data &= 0xfe;            //disable
            break;
    }
    int i;
    for( i = 0; i < ARRAY_SIZE( PatternTbl ); i++ )
    {
        if( SensorReg_Write(PatternTbl[i].reg,PatternTbl[i].data) != SUCCESS )
        {
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
    UartSendTrace("c2390_MIPI reg: 0x%x, data: 0x%x, read: 0x%x.\n", usreg, usval, sen_data);

    return SUCCESS;
}

static int pCus_I2CRead(ms_cus_sensor *handle, unsigned short usreg, unsigned short* pusval)
{
    unsigned short usread_data;

    SensorReg_Read(usreg, &usread_data);
    *pusval = usread_data;
    UartSendTrace("c2390_MIPI reg: 0x%x, data: 0x%x\n", usreg, usread_data);

    return SUCCESS;
}
#endif

static int pCus_init_2lane_linear( ms_cus_sensor *handle )
{
    int i;
    ISensorIfAPI *sensor_if = &( handle->sensor_if_api );
    short sen_data;
    sensor_if->PCLK( CUS_SNR_PCLK_MIPI_TOP );

    UartSendTrace("\n===== c2390 2lane init. =====\n");
    //printf("[%s] C2390 R1C version\n", __FUNCTION__);
    for( i = 0; i < ARRAY_SIZE( Sensor_init_table_2lane_linear ); i++ )
    {
        if( Sensor_init_table_2lane_linear[i].reg == 0xffff )
        {
            MsSleep(RTK_MS_TO_TICK(1));//usleep( 1000*Sensor_init_table_2lane_linear[i].data );
        }
        else
        {
            if( SensorReg_Write(Sensor_init_table_2lane_linear[i].reg,Sensor_init_table_2lane_linear[i].data) != SUCCESS )
            {
                return FAIL;
            }
            SensorReg_Read( Sensor_init_table_2lane_linear[i].reg, &sen_data );
            UartSendTrace("c2390 reg: 0x%x, data: 0x%x, read: 0x%x.\n",Sensor_init_table_2lane_linear[i].reg, Sensor_init_table_2lane_linear[i].data, sen_data);
        }
    }

    UartSendTrace("\nc2390 reg pattern\n");
    for( i = 0; i < ARRAY_SIZE( PatternTbl ); i++ )
    {
        if( SensorReg_Write(PatternTbl[i].reg,PatternTbl[i].data) != SUCCESS )
        {
            return FAIL;
        }
        SensorReg_Read( PatternTbl[i].reg, &sen_data );
        UartSendTrace("c23908 reg: 0x%x, data: 0x%x, read: 0x%x.\n",PatternTbl[i].reg, PatternTbl[i].data, sen_data);
    }

    UartSendTrace("\nc2390 reg Current_Mirror_Flip_Tbl\n");
    for( i = 0; i < ARRAY_SIZE( Current_Mirror_Flip_Tbl ); i++ )
    {
        if( SensorReg_Write(Current_Mirror_Flip_Tbl[i].reg,Current_Mirror_Flip_Tbl[i].data) != SUCCESS )
        {
            return FAIL;
        }
        SensorReg_Read( Current_Mirror_Flip_Tbl[i].reg, &sen_data );
        UartSendTrace("c2390 reg: 0x%x, data: 0x%x, read: 0x%x.\n",Current_Mirror_Flip_Tbl[i].reg, Current_Mirror_Flip_Tbl[i].data, sen_data);

    }

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
    switch(res){
        case SENSOR_DRIVER_MODE_FULL_HD_30P_RESOLUTION:
            handle->video_res_supported.ulcur_res = RES_IDX_1920x1080_30P;
#if (SENSOR_MIPI_LANE_NUM == 2) //TBD
#if (SENSOR_MIPI_HDR_MODE == 0)
            handle->pCus_sensor_init = pCus_init_2lane_linear;
#elif (SENSOR_MIPI_HDR_MODE == 1)
#elif (SENSOR_MIPI_HDR_MODE == 2)
#error "C2390 MIPI 2 lane does not support HDR 2x12b DCG"
#endif
#endif //#if (SENSOR_MIPI_LANE_NUM == 2)
            break;

        default:
            UartSendTrace("[%s] Line:%d fail.\n",__FUNCTION__, __LINE__);
            break;
    }

    //sensor_if->WaitVEnd( 50 );
    return SUCCESS;
}

static int pCus_GetOrien( ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT *orit )
{
    c2390_params *params = ( c2390_params * ) handle->private_data;
    return params->mirror_flip.cur;
}

static int pCus_SetOrien( ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT orit )
{
    c2390_params *params = ( c2390_params * ) handle->private_data;
    params->mirror_flip.new_setting = orit;
    //DoMirror( handle, params->mirror_flip.new_setting );
    return SUCCESS;
}

static int pCus_GetFPS( ms_cus_sensor *handle )
{
    c2390_params *params = ( c2390_params * ) handle->private_data;
    SENSOR_DMSG("[%s] FPS %d\n", __FUNCTION__, params->expo.fps);
    return params->expo.fps;
}

static int pCus_SetFPS( ms_cus_sensor *handle, u32 fps )
{
    c2390_params *params = ( c2390_params * ) handle->private_data;

    if( fps >= 10 && fps <= 30 )
    {
        params->expo.fps = fps;
        params->expo.vts = ( vts_30fps * 30 ) / fps;
        vts_reg[0].data = ( params->expo.vts >> 8 ) & 0x00ff;
        vts_reg[1].data = ( params->expo.vts >> 0 ) & 0x00ff;
        // params->reg_dirty = true;
        SENSOR_DMSG( "\n\n[%s], fps=%d, lines=%d\n", __FUNCTION__, fps, params->expo.vts );
        return SUCCESS;
    }
    else if( fps >= 10000 && fps <= 30000 )
    {
        params->expo.fps = fps;
        params->expo.vts = ( vts_30fps * 30000 ) / fps;
        vts_reg[0].data = ( params->expo.vts >> 8 ) & 0x00ff;
        vts_reg[1].data = ( params->expo.vts >> 0 ) & 0x00ff;
        // params->reg_dirty = true;
        SENSOR_DMSG( "\n\n[%s], fps=%d, lines=%d\n", __FUNCTION__, fps, params->expo.vts );
        return SUCCESS;
    }
    else
    {
        SENSOR_DMSG( "[%s] FPS %d out of range.\n", fps, __FUNCTION__ );
        return FAIL;
    }
}

static int pCus_GetSensorCap( ms_cus_sensor *handle, CUS_CAMSENSOR_CAP *cap )
{
    if( cap )
        memcpy( cap, &sensor_cap, sizeof(CUS_CAMSENSOR_CAP) );
    else
        return FAIL;
    return SUCCESS;
}

static int pCus_AEStatusNotify( ms_cus_sensor *handle, CUS_CAMSENSOR_AE_STATUS_NOTIFY status )
{
    //c2390_params *params = ( c2390_params * ) handle->private_data;
    // u16 i,sen_data;
    switch( status )
    {
        case CUS_FRAME_ACTIVE:
            /*        if(params->reg_dirty) {

             SensorReg_Write(0xfd,0x01);//page 1
             SensorReg_Write(0x01,0x00);//frame sync disable
             SensorRegArrayW((I2C_ARRAY*)expo_reg, sizeof(expo_reg)/sizeof(I2C_ARRAY));
             SensorRegArrayW((I2C_ARRAY*)gain_reg, sizeof(gain_reg)/sizeof(I2C_ARRAY));
             SensorRegArrayW((I2C_ARRAY*)vts_reg, sizeof(vts_reg)/sizeof(I2C_ARRAY));
             SensorRegArrayW((I2C_ARRAY*)mirror_reg, sizeof(mirror_reg)/sizeof(I2C_ARRAY));
             SensorReg_Write(0x01,0x01);//frame sync enable

             params->reg_dirty = false;

             }*/
            break;
        case CUS_FRAME_INACTIVE:
            default:
            break;
    }

    return SUCCESS;
}

static int pCus_GetAEUSecs( ms_cus_sensor *handle, u32 *us )
{
    int rc = 0;
    u32 lines = 0;

    lines = ( u32 ) ( expo_reg[3].data & 0xff );
    lines |= ( u32 ) ( expo_reg[2].data & 0xff ) << 8;

    *us = ( lines * Preview_line_period ) / 1000;

    // SENSOR_DMSG("[%s] sensor expo lines/us %d, %dus\n", __FUNCTION__, lines, *us);
    return rc;
}

static int pCus_SetAEUSecs( ms_cus_sensor *handle, u32 us )
{
    u32 lines = 0, vts = 0;
    c2390_params *params = ( c2390_params * ) handle->private_data;
    lines = ( u32 ) ( ( 1000 * us ) / Preview_line_period );

    if( lines > params->expo.vts - 2 )
        vts = lines + 2;
    else
        vts = params->expo.vts;

    SENSOR_DMSG( "[%s] us %ld, lines %ld, vts %ld\n", __FUNCTION__,
                    us,
                    lines,
                    params->expo.vts
                    );

    // lines <<= 4;
    expo_reg[2].data = ( u16 ) ( ( lines >> 8 ) & 0x00ff );
    expo_reg[3].data = ( u16 ) ( ( lines >> 0 ) & 0x00ff );

    vts_reg[0].data = ( vts >> 8 ) & 0x00ff;
    vts_reg[1].data = ( vts >> 0 ) & 0x00ff;
    SensorRegArrayW( ( I2C_ARRAY* )expo_reg, ARRAY_SIZE(expo_reg) );
    SensorRegArrayW( ( I2C_ARRAY* )gain_reg, ARRAY_SIZE(gain_reg) );
    SensorRegArrayW( ( I2C_ARRAY* )vts_reg, ARRAY_SIZE(vts_reg) );

    // params->reg_dirty = true;
    return SUCCESS;
}

// Gain: 1x = 1024
static int pCus_GetAEGain( ms_cus_sensor *handle, u32* gain )
{
    u32 again, dgain;

    dgain = ( gain_reg[1].data ) << (8 + gain_reg[2].data);//dgain = ( gain_reg[1].data ) << 8 + gain_reg[2].data;
    again = ( u32 ) ( 1 << ( gain_reg[0].data & 0x03 ) );
    *gain = again * ( dgain << 2 );

    SENSOR_DMSG( "[%s] again(base1)/dgain(base64)/gain(base1024) = 0x%x/0x%x/0x%x\n", __FUNCTION__, again, dgain, *gain );
    return SUCCESS;
}

static int pCus_SetAEGain_cal( ms_cus_sensor *handle, u32 gain )
{
    //c2390_params *params = ( c2390_params * ) handle->private_data;
    u32 s_gain, ulTempGain;
    u32 DGain = 0x100, HCG_AGain = 0, LCG_AGain = 0;

    if( gain < SENSOR_MIN_GAIN )
        gain = SENSOR_MIN_GAIN;
    else if( gain >= SENSOR_MAX_GAIN )
        gain = SENSOR_MAX_GAIN;

    s_gain = gain >> 2;
    s_gain = s_gain / 2;            //for HCG DG min=X2
    if( s_gain > 0x800 )            //X8
    {
        HCG_AGain = 3;
        DGain = s_gain >> HCG_AGain;
    }
    else if( s_gain > 0x400 )
    {
        HCG_AGain = 2;
        DGain = s_gain >> HCG_AGain;
    }
    else if( s_gain > 0x200 )
    {
        HCG_AGain = 1;
        DGain = s_gain >> HCG_AGain;
    }
    else if( s_gain > 0x100 )
    {
        HCG_AGain = 0;
        DGain = s_gain >> HCG_AGain;
    }
    else if( s_gain < 0x100 )
    {
        HCG_AGain = 0;
        DGain = 0x100;
    }
    DGain = ( DGain * 0x200 + 0x80 ) / 0x100;            // make minima DG to be 2x
    if( DGain < 512 )
        DGain = 512;            //min=2X

    gain_reg[1].data = ( u16 ) ( DGain >> 8 );            //high byte
    gain_reg[2].data = ( u16 ) ( DGain & 0xff );            //low byte

    ulTempGain = gain >> 2;

    if( ulTempGain > 0x800 )            //X8
    {
        LCG_AGain = 3;
        DGain = ulTempGain >> LCG_AGain;
    }
    else if( ulTempGain > 0x400 )
    {
        LCG_AGain = 2;
        DGain = ulTempGain >> LCG_AGain;
    }
    else if( ulTempGain > 0x200 )
    {
        LCG_AGain = 1;
        DGain = ulTempGain >> LCG_AGain;
    }
    else if( ulTempGain > 0x100 )
    {
        LCG_AGain = 0;
        DGain = ulTempGain >> LCG_AGain;
    }
    else if( ulTempGain < 0x100 )
    {
        LCG_AGain = 0;
        DGain = 0x100;
    }
    if( DGain < 256 )
        DGain = 256;            //min=1.09X
    if( LCG_AGain < 1 )
        LCG_AGain = 1;            //min=2.0X

    gain_reg[3].data = ( u16 ) ( DGain >> 8 );            //high byte
    gain_reg[4].data = ( u16 ) ( DGain & 0xff );            //low byte
    gain_reg[0].data = ( u16 ) ( ( ( LCG_AGain << 2 ) & 0x0C ) + ( HCG_AGain & 0x03 ) );

    SENSOR_DMSG( "[%s] set gain/AG/HCG_H/HCG_L/LCG_H/LCG_L=%d/0x%x/0x%x/0x%x/0x%x/0x%x\n",
                    __FUNCTION__,
                    gain,
                    gain_reg[0].data,
                    gain_reg[1].data,
                    gain_reg[2].data,
                    gain_reg[3].data,
                    gain_reg[4].data );
    // params->reg_dirty = true;
    return SUCCESS;
}
static int pCus_SetAEGain( ms_cus_sensor *handle, u32 gain )
{
    //c2390_params *params = ( c2390_params * ) handle->private_data;
    CUS_GAIN_GAP_ARRAY* Sensor_Gain_Linearity;
    u32 i, s_gain, ulTempGain;
    u32 DGain = 0x100, HCG_AGain = 0, LCG_AGain = 0;

    if( gain < SENSOR_MIN_GAIN )
        gain = SENSOR_MIN_GAIN;
    else if( gain >= SENSOR_MAX_GAIN )
        gain = SENSOR_MAX_GAIN;

    Sensor_Gain_Linearity = gain_gap_compensate;

    for( i = 0; i < sizeof( gain_gap_compensate ) / sizeof(CUS_GAIN_GAP_ARRAY); i++ )
    {
        if( Sensor_Gain_Linearity[i].gain == 0 )
            break;
        if( ( gain > Sensor_Gain_Linearity[i].gain ) && ( gain < ( Sensor_Gain_Linearity[i].gain + Sensor_Gain_Linearity[i].offset ) ) )
        {
            gain = Sensor_Gain_Linearity[i].gain;
            break;
        }
    }
    s_gain = gain >> 2;
    s_gain = s_gain / 2;            //for HCG DG min=X2
    if( s_gain > 0x800 )            //X8
    {
        HCG_AGain = 3;
        DGain = s_gain >> HCG_AGain;
    }
    else if( s_gain > 0x400 )
    {
        HCG_AGain = 2;
        DGain = s_gain >> HCG_AGain;
    }
    else if( s_gain > 0x200 )
    {
        HCG_AGain = 1;
        DGain = s_gain >> HCG_AGain;
    }
    else if( s_gain > 0x100 )
    {
        HCG_AGain = 0;
        DGain = s_gain >> HCG_AGain;
    }
    else if( s_gain < 0x100 )
    {
        HCG_AGain = 0;
        DGain = 0x100;
    }
    DGain = ( DGain * 0x200 + 0x80 ) / 0x100;            // make minima DG to be 2x
    if( DGain < 512 )
        DGain = 512;            //min=2X

    gain_reg[1].data = ( u16 ) ( DGain >> 8 );            //high byte
    gain_reg[2].data = ( u16 ) ( DGain & 0xff );            //low byte

    ulTempGain = gain >> 2;

    if( ulTempGain > 0x800 )            //X8
    {
        LCG_AGain = 3;
        DGain = ulTempGain >> LCG_AGain;
    }
    else if( ulTempGain > 0x400 )
    {
        LCG_AGain = 2;
        DGain = ulTempGain >> LCG_AGain;
    }
    else if( ulTempGain > 0x200 )
    {
        LCG_AGain = 1;
        DGain = ulTempGain >> LCG_AGain;
    }
    else if( ulTempGain > 0x100 )
    {
        LCG_AGain = 0;
        DGain = ulTempGain >> LCG_AGain;
    }
    else if( ulTempGain < 0x100 )
    {
        LCG_AGain = 0;
        DGain = 0x100;
    }
    if( DGain < 256 )
        DGain = 256;            //min=1.09X
    if( LCG_AGain < 1 )
        LCG_AGain = 1;            //min=2.0X

    gain_reg[3].data = ( u16 ) ( DGain >> 8 );            //high byte
    gain_reg[4].data = ( u16 ) ( DGain & 0xff );            //low byte
    gain_reg[0].data = ( u16 ) ( ( ( LCG_AGain << 2 ) & 0x0C ) + ( HCG_AGain & 0x03 ) );

    SENSOR_DMSG( "[%s] set gain/AG/HCG_H/HCG_L/LCG_H/LCG_L=%d/0x%x/0x%x/0x%x/0x%x/0x%x\n",
                    __FUNCTION__,
                    gain,
                    gain_reg[0].data,
                    gain_reg[1].data,
                    gain_reg[2].data,
                    gain_reg[3].data,
                    gain_reg[4].data );
    // params->reg_dirty = true;
    return SUCCESS;
}

static int pCus_AEStatusNotifyHDR_VS( ms_cus_sensor *handle, CUS_CAMSENSOR_AE_STATUS_NOTIFY status )
{
    switch( status )
    {
        case CUS_FRAME_ACTIVE:
            break;
        case CUS_FRAME_INACTIVE:
            default:
            break;
    }
    return SUCCESS;
}

static int pCus_SetAEUSecsHDR_VS( ms_cus_sensor *handle, u32 us )
{
    u32 new_vsync = vts_30fps;
	#if 0
    new_shutter_s = (1000 * us) / Preview_line_period;
    new_shutter_s = C2390_GET_MIN(C2390_GET_MAX(new_shutter_s, 2), new_vsync - 2);
	#endif
	return SUCCESS;
}

static int pCus_SetAEGainHDR_LCG_VS_Cal(u32 ae_gain, u32 *pagain,  u32 *pdgain)
{
    u32 s_gain;
	#if 0
    //VS for HDR
    s_gain = C2390_GET_MAX( ae_gain , 3 * SENSOR_GAIN_BASE );
    s_gain = s_gain * 32 / 35;

    if(s_gain > (8 * SENSOR_GAIN_BASE)){
        *pagain = 3;
        *pdgain = (s_gain >> *pagain)* 35 / 32;
    } else if(s_gain > (4 * SENSOR_GAIN_BASE)){
        *pagain = 2;
        *pdgain = (s_gain >> *pagain)* 35 / 32;
    } else if(s_gain > (2 * SENSOR_GAIN_BASE)){
        *pagain = 1;
        *pdgain = C2390_GET_MAX(SENSOR_GAIN_BASE* 3 / 2,(s_gain >> *pagain)* 35 / 32);
    }
	#endif
}

static int pCus_SetAEGainHDR_VS( ms_cus_sensor *handle, u32 gain )
{
	#if 0
    u32 ae_gain_s    = SENSOR_GAIN_BASE;
    u32 s_gain_VS;
    ae_gain_s = gain >> 2;

    //ae_gain_s = ae_gain_s * ISP_DGAIN_BASE / dgain;
    if (ae_gain_s >= (SENSOR_GAIN_BASE * MAX_SENSOR_GAIN_VS)) {
        //dgain_s     = ISP_DGAIN_BASE * ae_gain_s /SENSOR_GAIN_BASE / MAX_SENSOR_GAIN;
        ae_gain_s   = SENSOR_GAIN_BASE * MAX_SENSOR_GAIN_VS;
    }
    else {
        //dgain_s    = ISP_DGAIN_BASE;
    }

    pCus_SetAEGainHDR_LCG_VS_Cal(ae_gain_s, &VS_AGain, &VS_DGain);
	#endif
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
    SENSOR_DMSG( "[%s]%d, %d, %d, %d\n", __FUNCTION__, num, pArray[0].gain, pArray[1].gain, pArray[num-1].offset );
    return SUCCESS;
}

static int C2390_GetShutterInfo( struct __ms_cus_sensor* handle, CUS_SHUTTER_INFO *info )
{
    info->max = 1000000000 / 12;
    info->min = Preview_line_period;
    info->step = Preview_line_period;
    return SUCCESS;
}

static int pCus_GetCsiAnaDataLaneSel(u32 *DataLaneSel)
{
    if(DataLaneSel){
        UartSendTrace("pCus_GetCsiAnaDataLaneSel\n");
        memcpy( DataLaneSel, &DataLaneSelArray, sizeof(DataLaneSelArray) );
    }
    else{
        return FAIL;
    }
    return SUCCESS;
}
static int pCus_GetCsiAnaHsTxPolarity(u32 *HsTxPolarity)
{
    if(HsTxPolarity){
        UartSendTrace("pCus_GetCsiAnaHsTxPolarity\n");
        memcpy( HsTxPolarity, &HsTxPolarityArray, sizeof(HsTxPolarityArray));
    }
    else{
        return FAIL;
    }
    return SUCCESS;
}

int c2390_MIPI_cus_camsensor_init_handle( ms_cus_sensor* drv_handle )
{
    ms_cus_sensor *handle = drv_handle;
    if( !handle )
    {
        SENSOR_DMSG( "[%s] not enough memory!\n", __FUNCTION__ );
        return FAIL;
    }
    SENSOR_DMSG( "[%s]\n", __FUNCTION__ );

    handle->private_data = calloc( 1, sizeof(c2390_params) );
    c2390_params *params = ( c2390_params * ) handle->private_data;

    sprintf( handle->model_id, SENSOR_MODEL_ID );
    handle->isp_type = SENSOR_ISP_TYPE;
    handle->sif_bus = SENSOR_IFBUS_TYPE;
    handle->data_prec = SENSOR_DATAPREC;
    handle->data_mode = SENSOR_DATAMODE;
    handle->bayer_id = SENSOR_BAYERID;
    handle->orient = SENSOR_ORIT;
    handle->interface_attr.attr_mipi.mipi_lane_num = SENSOR_MIPI_LANE_NUM;
    handle->interface_attr.attr_mipi.mipi_data_format = CUS_SEN_INPUT_FORMAT_RGB; // RGB pattern.
    handle->interface_attr.attr_mipi.mipi_yuv_order = 0; //don't care in RGB pattern.
    handle->interface_attr.attr_mipi.mipi_hsync_mode = SENSOR_MIPI_HSYNC_MODE;
    handle->interface_attr.attr_mipi.mipi_sampling_delay = SENSOR_MIPI_DELAY;
#if (SENSOR_MIPI_HDR_MODE == 2)
    handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_DCG;
#else
    handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_NONE;
#endif
    handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 1; //Short frame

	handle->channel_mode = SENSOR_CHANNEL_MODE;
	handle->dcg_hdr_mode = SENSOR_DCGHDR_MODE;
	if((DrvPM_GetChipID() == CHIP_ID_M5) && (handle->channel_mode != CUS_SENSOR_CHANNEL_MODE_RAW_STORE_LI_HDR)){ //M5only support RAW_STORE
		SENSOR_DMSG( "[%s] M5 does not support %d mode!\n", __FUNCTION__, handle->channel_mode);
        return FAIL;
	}
	
    handle->video_res_supported.num_res = 1;
    handle->video_res_supported.ulcur_res = 0; //default resolution index is 0.
    handle->video_res_supported.res[0].width = Preview_WIDTH;
    handle->video_res_supported.res[0].height = Preview_HEIGHT;
    handle->video_res_supported.res[0].max_fps = Preview_MAX_FPS;
    handle->video_res_supported.res[0].min_fps = Preview_MIN_FPS;
    handle->video_res_supported.res[0].crop_start_x= Preview_CROP_START_X;
    handle->video_res_supported.res[0].crop_start_y= Preview_CROP_START_Y;
    handle->video_res_supported.res[0].nOutputWidth= 1920;//1928;//Preview_WIDTH;
    if(handle->channel_mode == CUS_SENSOR_CHANNEL_MODE_RAW_STORE_LI_HDR){
		handle->video_res_supported.res[0].nOutputHeight= 1080*2; //Preview_HEIGHT;
    }else{
    	handle->video_res_supported.res[0].nOutputHeight= 1080; //Preview_HEIGHT;
    }
    handle->i2c_cfg.mode                = I2C_NORMAL_MODE;
    handle->i2c_cfg.fmt                 = SENSOR_I2C_FMT;
    handle->i2c_cfg.address             = SENSOR_I2C_ADDR;
    handle->i2c_cfg.speed               = SENSOR_I2C_SPEED;     //200000;
    handle->i2c_cfg.nChannel            = SENSOR_I2C_CHANNEL;   //Channel 1
    handle->i2c_cfg.nPadNum             = SENSOR_I2C_PAD_MODE;  //pad mode 2

    handle->mclk = Preview_MCLK_SPEED;

    handle->pwdn_POLARITY = SENSOR_PWDN_POL;
    handle->reset_POLARITY = SENSOR_RST_POL;

    handle->ae_gain_delay = 2;            //0;//1;
    handle->ae_shutter_delay = 2;            //1;//2;

    handle->sat_mingain = 1024;
    handle->dgain_remainder = 0;
    handle->pCus_sensor_release = c2390_MIPI_cus_camsensor_release_handle;
#if (SENSOR_MIPI_LANE_NUM == 2) //TBD
#if (SENSOR_MIPI_HDR_MODE == 0)
    handle->pCus_sensor_init = pCus_init_2lane_linear;
#elif (SENSOR_MIPI_HDR_MODE == 1)
#elif (SENSOR_MIPI_HDR_MODE == 2)
#error "C2390 MIPI 2 lane does not support HDR 2x12b DCG"
#endif
#endif //#if (SENSOR_MIPI_LANE_NUM == 2)
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
    handle->pCus_sensor_SetPatternMode = c2390_SetPatternMode;

#if (SENSOR_MIPI_HDR_MODE == 0)
    handle->pCus_sensor_AEStatusNotify = pCus_AEStatusNotify;
    handle->pCus_sensor_GetAEUSecs = pCus_GetAEUSecs;
    handle->pCus_sensor_SetAEUSecs = pCus_SetAEUSecs;
    handle->pCus_sensor_GetAEGain = pCus_GetAEGain;
    handle->pCus_sensor_SetAEGain_cal = pCus_SetAEGain_cal;
    handle->pCus_sensor_SetAEGain = pCus_SetAEGain;
#endif
#if (SENSOR_MIPI_HDR_MODE == 2)
    handle->pCus_sensor_AEStatusNotify = pCus_AEStatusNotifyHDR_VS;
    handle->pCus_sensor_GetAEUSecs = pCus_GetAEUSecs;
    handle->pCus_sensor_SetAEUSecs = pCus_SetAEUSecsHDR_VS;
    handle->pCus_sensor_GetAEGain = pCus_GetAEGain;
    handle->pCus_sensor_SetAEGain_cal = pCus_SetAEGain_cal;
    handle->pCus_sensor_SetAEGain = pCus_SetAEGainHDR_VS;
#endif

    handle->pCus_sensor_GetAEMinMaxGain = pCus_GetAEMinMaxGain;
    handle->pCus_sensor_GetAEMinMaxUSecs = pCus_GetAEMinMaxUSecs;
    handle->pCus_sensor_GetDGainRemainder = pCus_GetDGainRemainder;
    handle->pCus_sensor_GetShutterInfo = C2390_GetShutterInfo;
    handle->pCus_sensor_setCaliData_gain_linearity = pCus_setCaliData_gain_linearity;
#if 1//defined(__MV5_FPGA__)
    handle->pCus_sensor_I2CWrite = pCus_I2CWrite; //Andy Liu
    handle->pCus_sensor_I2CRead = pCus_I2CRead; //Andy Liu
#endif
    params->expo.vts = vts_30fps;
    params->expo.fps = 30;
    params->reg_dirty = false;

    handle->snr_pad_group = SENSOR_PAD_GROUP_SET;

    handle->channel_num = SENSOR_CHANNEL_NUM;
    handle->pCus_sensor_GetCsiAnaDataLaneSel = pCus_GetCsiAnaDataLaneSel;
    handle->pCus_sensor_GetCsiAnaHsTxPolarity = pCus_GetCsiAnaHsTxPolarity;
    return SUCCESS;
}

int c2390_MIPI_cus_camsensor_release_handle( ms_cus_sensor *handle )
{
    if( handle && handle->private_data )
    {
        SENSOR_IMSG("[%s] release handle 0x%x, private data %x\n",__FUNCTION__,(int)handle,(int)handle->private_data);
        free( handle->private_data );
        handle->private_data = NULL;
    }
    return SUCCESS;
}

static int pCus_poweron_dummy( ms_cus_sensor *handle )
{
    return SUCCESS;
}

static int pCus_poweroff_dummy( ms_cus_sensor *handle )
{
    return SUCCESS;
}

static int pCus_GetSensorID_dummy( ms_cus_sensor *handle, u32 *id )
{
    *id = 0;
     return SUCCESS;
}

static int c2390_SetPatternMode_dummy( ms_cus_sensor *handle, u32 mode )
{
    return SUCCESS;
}

static int pCus_I2CWrite_dummy(ms_cus_sensor *handle, unsigned short usreg, unsigned short usval)
{
    return SUCCESS;
}

static int pCus_I2CRead_dummy(ms_cus_sensor *handle, unsigned short usreg)
{
    return SUCCESS;
}

static int pCus_init_dummy( ms_cus_sensor *handle )
{
    return SUCCESS;
}

static int pCus_GetVideoRes_dummy( ms_cus_sensor *handle, cus_camsensor_res **res )
{
    *res = &handle->video_res_supported.res[handle->video_res_supported.ulcur_res];
    return SUCCESS;
}

static int pCus_SetVideoRes_dummy( ms_cus_sensor *handle, u32 res )
{
    handle->video_res_supported.ulcur_res = 0; //TBD
    return SUCCESS;
}

static int pCus_GetOrien_dummy( ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT *orit )
{
    c2390_params *params = ( c2390_params * ) handle->private_data;
    return params->mirror_flip.cur;
}

static int pCus_SetOrien_dummy( ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT orit )
{
    return SUCCESS;
}

static int pCus_GetFPS_dummy( ms_cus_sensor *handle )
{
    return SUCCESS;
}

static int pCus_SetFPS_dummy( ms_cus_sensor *handle, u32 fps )
{
    return SUCCESS;
}

static int pCus_GetSensorCap_dummy( ms_cus_sensor *handle, CUS_CAMSENSOR_CAP *cap )
{
    if( cap )
        memcpy( cap, &sensor_cap, sizeof(CUS_CAMSENSOR_CAP) );
    else
        return FAIL;
    return SUCCESS;
}

static int pCus_AEStatusNotify_dummy( ms_cus_sensor *handle, CUS_CAMSENSOR_AE_STATUS_NOTIFY status )
{
    return SUCCESS;
}

static int pCus_GetAEUSecs_dummy( ms_cus_sensor *handle, u32 *us )
{
    *us = 0;
    return SUCCESS;
}

static int pCus_SetAEUSecs_dummy( ms_cus_sensor *handle, u32 us )
{
    return SUCCESS;
}

// Gain: 1x = 1024
static int pCus_GetAEGain_dummy( ms_cus_sensor *handle, u32* gain )
{
    *gain = 0;
    return SUCCESS;
}

static int pCus_SetAEGain_cal_dummy( ms_cus_sensor *handle, u32 gain )
{
    return SUCCESS;
}
static int pCus_SetAEGain_dummy( ms_cus_sensor *handle, u32 gain )
{
    return SUCCESS;
}

static int pCus_GetAEMinMaxUSecs_dummy( ms_cus_sensor *handle, u32 *min, u32 *max )
{
    *min = 1;
    *max = 1000000 / 30;

    return SUCCESS;
}

static int pCus_GetAEMinMaxGain_dummy( ms_cus_sensor *handle, u32 *min, u32 *max )
{
    *min = SENSOR_MIN_GAIN;            //1024*1.1*2
    *max = SENSOR_MAX_GAIN;

    return SUCCESS;
}

static int pCus_GetDGainRemainder_dummy(ms_cus_sensor *handle, u32 *dgain_remainder)
{
    *dgain_remainder = handle->dgain_remainder;

    return SUCCESS;
}

static int pCus_setCaliData_gain_linearity_dummy( ms_cus_sensor* handle, CUS_GAIN_GAP_ARRAY* pArray, u32 num )
{
    return SUCCESS;
}

static int C2390_GetShutterInfo_dummy( struct __ms_cus_sensor* handle, CUS_SHUTTER_INFO *info )
{
    info->max = 1000000000 / 12;
    info->min = Preview_line_period;
    info->step = Preview_line_period;
    return SUCCESS;
}

int c2390_MIPI_cus_camsensor_init_handle_lef( ms_cus_sensor* drv_handle )
{
    ms_cus_sensor *handle = drv_handle;
    if( !handle )
    {
        SENSOR_DMSG( "[%s] not enough memory!\n", __FUNCTION__ );
        return FAIL;
    }
    SENSOR_DMSG( "[%s]\n", __FUNCTION__ );

    handle->private_data = calloc( 1, sizeof(c2390_params) );
    c2390_params *params = ( c2390_params * ) handle->private_data;

    sprintf( handle->model_id, SENSOR_MODEL_ID );
    handle->isp_type = SENSOR_ISP_TYPE;
    handle->sif_bus = SENSOR_IFBUS_TYPE;
    handle->data_prec = SENSOR_DATAPREC;
    handle->data_mode = SENSOR_DATAMODE;
    handle->bayer_id = SENSOR_BAYERID;
    handle->orient = SENSOR_ORIT;
    handle->interface_attr.attr_mipi.mipi_lane_num = SENSOR_MIPI_LANE_NUM;
    handle->interface_attr.attr_mipi.mipi_data_format = CUS_SEN_INPUT_FORMAT_RGB; // RGB pattern.
    handle->interface_attr.attr_mipi.mipi_yuv_order = 0; //don't care in RGB pattern.
    handle->interface_attr.attr_mipi.mipi_hsync_mode = SENSOR_MIPI_HSYNC_MODE;
    handle->interface_attr.attr_mipi.mipi_sampling_delay = SENSOR_MIPI_DELAY;
    handle->interface_attr.attr_mipi.mipi_hdr_mode = CUS_HDR_MODE_NONE;
    handle->interface_attr.attr_mipi.mipi_hdr_virtual_channel_num = 0; //Long frame

    handle->video_res_supported.num_res = 1;
    handle->video_res_supported.ulcur_res = 0; //default resolution index is 0.
    handle->video_res_supported.res[0].width = Preview_WIDTH;
    handle->video_res_supported.res[0].height = Preview_HEIGHT;
    handle->video_res_supported.res[0].max_fps = Preview_MAX_FPS;
    handle->video_res_supported.res[0].min_fps = Preview_MIN_FPS;
    handle->video_res_supported.res[0].crop_start_x= Preview_CROP_START_X;
    handle->video_res_supported.res[0].crop_start_y= Preview_CROP_START_Y;
    handle->video_res_supported.res[0].nOutputWidth= 1920;//Preview_WIDTH;
    handle->video_res_supported.res[0].nOutputHeight= 1080;//Preview_HEIGHT;

    handle->i2c_cfg.mode                = I2C_NORMAL_MODE;
    handle->i2c_cfg.fmt                 = SENSOR_I2C_FMT;
    handle->i2c_cfg.address             = SENSOR_I2C_ADDR;
    handle->i2c_cfg.speed               = SENSOR_I2C_SPEED;     //200000;
    handle->i2c_cfg.nChannel            = SENSOR_I2C_CHANNEL;   //Channel 1
    handle->i2c_cfg.nPadNum             = SENSOR_I2C_PAD_MODE;  //pad mode 2
	handle->dgain_remainder = 0;
    handle->mclk = Preview_MCLK_SPEED;

    handle->pwdn_POLARITY = SENSOR_PWDN_POL;
    handle->reset_POLARITY = SENSOR_RST_POL;

    handle->ae_gain_delay = 2;            //0;//1;
    handle->ae_shutter_delay = 2;            //1;//2;

    handle->sat_mingain = 1024;
    handle->pCus_sensor_release = c2390_MIPI_cus_camsensor_release_handle;
    handle->pCus_sensor_init = pCus_init_dummy;
    handle->pCus_sensor_poweron = pCus_poweron_dummy;
    handle->pCus_sensor_poweroff = pCus_poweroff_dummy;

    handle->pCus_sensor_GetSensorID = pCus_GetSensorID_dummy;
    handle->pCus_sensor_GetVideoResNum = pCus_GetVideoResNum;
    handle->pCus_sensor_GetVideoRes = pCus_GetVideoRes_dummy;
    handle->pCus_sensor_SetVideoRes = pCus_SetVideoRes_dummy;
    handle->pCus_sensor_GetOrien = pCus_GetOrien_dummy;
    handle->pCus_sensor_SetOrien = pCus_SetOrien_dummy;
    handle->pCus_sensor_GetFPS = pCus_GetFPS_dummy;
    handle->pCus_sensor_SetFPS = pCus_SetFPS_dummy;
    handle->pCus_sensor_GetSensorCap = pCus_GetSensorCap_dummy;
    handle->pCus_sensor_SetPatternMode = c2390_SetPatternMode_dummy;

    handle->pCus_sensor_AEStatusNotify = pCus_AEStatusNotify;
    handle->pCus_sensor_GetAEUSecs = pCus_GetAEUSecs;
    handle->pCus_sensor_SetAEUSecs = pCus_SetAEUSecs;
    handle->pCus_sensor_GetAEGain = pCus_GetAEGain;
    handle->pCus_sensor_SetAEGain_cal = pCus_SetAEGain_cal;
    handle->pCus_sensor_SetAEGain = pCus_SetAEGain;

    handle->pCus_sensor_GetAEMinMaxGain = pCus_GetAEMinMaxGain_dummy;
    handle->pCus_sensor_GetAEMinMaxUSecs = pCus_GetAEMinMaxUSecs_dummy;
    handle->pCus_sensor_GetShutterInfo = C2390_GetShutterInfo_dummy;
    handle->pCus_sensor_setCaliData_gain_linearity = pCus_setCaliData_gain_linearity_dummy;
	handle->pCus_sensor_GetDGainRemainder = pCus_GetDGainRemainder_dummy;
#if 1//defined(__MV5_FPGA__)
    handle->pCus_sensor_I2CWrite = pCus_I2CWrite_dummy; //Andy Liu
    handle->pCus_sensor_I2CRead = pCus_I2CRead_dummy; //Andy Liu
#endif
    params->expo.vts = vts_30fps;
    params->expo.fps = 30;
    params->reg_dirty = false;

    handle->snr_pad_group = SENSOR_PAD_GROUP_SET;

    handle->channel_num = SENSOR_CHANNEL_NUM + 1;
	handle->channel_mode = SENSOR_CHANNEL_MODE_LEF;
	handle->dcg_hdr_mode = SENSOR_DCGHDR_MODE;
    return SUCCESS;
}

#if defined(__RTK_OS__)
struct SensorMapTable_t gsensor_map_c2390[] = {
    { //Channel 0
        SENSOR_CHANNEL_NUM,
        c2390_MIPI_cus_camsensor_init_handle,
        c2390_MIPI_cus_camsensor_release_handle
    },
    { //Channel 1
        SENSOR_CHANNEL_NUM + 1,
        c2390_MIPI_cus_camsensor_init_handle_lef,
        c2390_MIPI_cus_camsensor_release_handle
    },
};

int C2390_Module_Init(void)
{
    cameraSensorRegister(&gsensor_map_c2390[0]);
	//LI HDR do not register, SEP LI HDR need to register 
	if(SensorChannelMode != CUS_SENSOR_CHANNEL_MODE_RAW_STORE_LI_HDR){
		cameraSensorRegister(&gsensor_map_c2390[1]);
	}
    return 0;
}

void C2390_Module_Exit(void)
{
    cameraSensorUnRegister(&gsensor_map_c2390[0]);
	if(SensorChannelMode != CUS_SENSOR_CHANNEL_MODE_RAW_STORE_LI_HDR){
    	cameraSensorUnRegister(&gsensor_map_c2390[1]);
	}
}

#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(C2390_Module_Init);
//ait_module_exit(C2390_Module_Exit);
#endif //#if defined(__RTK_OS__)

#endif //#if defined(BIND_SENSOR_C2390) && (BIND_SENSOR_C2390 == 1)
