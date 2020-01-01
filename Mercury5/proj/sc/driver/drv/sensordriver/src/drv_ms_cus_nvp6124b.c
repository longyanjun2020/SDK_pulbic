////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (锟斤拷锟斤拷锟斤拷MStar Confidential Information锟斤拷锟斤拷锟斤拷) by the recipient.
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
#if (SENSOR0 == NVP6124B)
#define BIND_SENSOR_NVP6124B (1)
#endif
#endif //#if defined(__RTK_OS__)

#if defined(BIND_SENSOR_NVP6124B) && (BIND_SENSOR_NVP6124B == 1)

#define SENSOR_PAD_GROUP_SET CUS_SENSOR_PAD_GROUP_A
#define SENSOR_CHANNEL_NUM (0)
#define SENSOR_CHANNEL_MODE CUS_SENSOR_CHANNEL_MODE_REALTIME_ISP_BYPASS

//============================================
//BT656 config begin.
#define SENSOR_BT656_CH_TOTAL_NUM (2)
#define SENSOR_BT656_CH_DET_ENABLE CUS_SENSOR_FUNC_DISABLE
#define SENSOR_BT656_CH_DET_SEL CUS_VIF_BT656_EAV_DETECT
#define SENSOR_BT656_BIT_SWAP CUS_SENSOR_FUNC_DISABLE
#define SENSOR_BT656_8BIT_MODE CUS_SENSOR_FUNC_ENABLE
#define SENSOR_BT656_VSYNC_DELAY CUS_VIF_BT656_VSYNC_DELAY_AUTO
#define SENSOR_HSYCN_INVERT CUS_SENSOR_FUNC_DISABLE
#define SENSOR_VSYCN_INVERT CUS_SENSOR_FUNC_DISABLE
#define SENSOR_CLAMP_ENABLE CUS_SENSOR_FUNC_DISABLE
//BT656 config end.
//============================================

#define SENSOR_ISP_TYPE     ISP_EXT                   //ISP_EXT, ISP_SOC
#define F_number  22                                  // CFG, demo module
//#define SENSOR_DATAFMT      CUS_DATAFMT_BAYER        //CUS_DATAFMT_YUV, CUS_DATAFMT_BAYER
#define SENSOR_IFBUS_TYPE   CUS_SENIF_BUS_BT656      //CFG //CUS_SENIF_BUS_PARL, CUS_SENIF_BUS_MIPI
//#define SENSOR_MIPI_DELAY   0x1212                  //CFG
#define SENSOR_DATAPREC     CUS_DATAPRECISION_16    //CUS_DATAPRECISION_8, CUS_DATAPRECISION_10
#define SENSOR_DATAMODE     CUS_SEN_10TO12_9000     //CFG
#define SENSOR_BAYERID      CUS_BAYER_RG            //CFG //CUS_BAYER_GB, CUS_BAYER_GR, CUS_BAYER_BG, CUS_BAYER_RG
#define SENSOR_ORIT         CUS_ORIT_M0F0           //CUS_ORIT_M0F0, CUS_ORIT_M1F0, CUS_ORIT_M0F1, CUS_ORIT_M1F1,
//#define SENSOR_YCORDER      CUS_SEN_YCODR_YC       //CUS_SEN_YCODR_YC, CUS_SEN_YCODR_CY
#define lane_number 2
#define vc0_hs_mode 3   //0: packet header edge  1: line end edge 2: line start edge 3: packet footer edge
#define long_packet_type_enable 0x00 //UD1~UD8 (user define)
#define SENSOR_MAX_GAIN     ((16*2.7*16) * 1024)                  // max sensor again, a-gain * conversion-gain*d-gain
#define SENSOR_MIN_GAIN      (1.52 * 1024) //1557
#define SENSOR_GAIN_DELAY_FRAME_COUNT      (2)
#define SENSOR_SHUTTER_DELAY_FRAME_COUNT      (2)

#define Preview_MCLK_SPEED  CUS_CMU_CLK_27MHZ       //CFG //CUS_CMU_CLK_12M, CUS_CMU_CLK_16M, CUS_CMU_CLK_24M, CUS_CMU_CLK_27M
#define Preview_line_period 30000                  ////HTS/PCLK=4455 pixels/148.5MHZ=30usec
#define Prv_Max_line_number 1080                    //maximum exposure line munber of sensor when preview
#define vts_30fps 1125//1346,1616                      //for 29.1fps
#define Preview_WIDTH       1280 // 1920                   //resolution Width when preview
#define Preview_HEIGHT      720  // 1080                //resolution Height when preview
#define Preview_MAX_FPS     30                     //fastest preview FPS
#define Preview_MIN_FPS     8                      //slowest preview FPS
#define Preview_CROP_START_X     1                      //CROP_START_X
#define Preview_CROP_START_Y     1                      //CROP_START_Y

//#define Capture_MCLK_SPEED  CUS_CMU_CLK_16M     //CUS_CMU_CLK_12M, CUS_CMU_CLK_16M, CUS_CMU_CLK_24M, CUS_CMU_CLK_27M
#define Cap_Max_line_number 720                   //maximum exposure line munber of sensor when capture

//#define SENSOR_I2C_LEGACY  CUS_I2C_NORMAL_MODE     //usally set CUS_I2C_NORMAL_MODE,  if use old OVT I2C protocol=> set CUS_I2C_LEGACY_MODE
//#define SENSOR_I2C_FMT     CUS_I2C_FMT_A16D8        //CUS_I2C_FMT_A8D8, CUS_I2C_FMT_A8D16, CUS_I2C_FMT_A16D8, CUS_I2C_FMT_A16D16
#define SENSOR_I2C_ADDR    0x60                   //I2C slave address
#define SENSOR_I2C_SPEED    I2C_SLOWSPEED_MODE_200KHZ   //200KHz
#define SENSOR_I2C_CHANNEL  1                           //I2C Channel
#define SENSOR_I2C_PAD_MODE 2                           //Pad/Mode Number

#define SENSOR_I2C_LEGACY  I2C_NORMAL_MODE     //usally set CUS_I2C_NORMAL_MODE,  if use old OVT I2C protocol=> set CUS_I2C_LEGACY_MODE
#define SENSOR_I2C_FMT     I2C_FMT_A8D8        //CUS_I2C_FMT_A8D8, CUS_I2C_FMT_A8D16, CUS_I2C_FMT_A16D8, CUS_I2C_FMT_A16D16

#define SENSOR_PWDN_POL     CUS_CLK_POL_POS//CUS_CLK_POL_NEG        // if PWDN pin High can makes sensor in power down, set CUS_CLK_POL_POS
#define SENSOR_RST_POL      CUS_CLK_POL_NEG        // if RESET pin High can makes sensor in reset state, set CUS_CLK_POL_NEG

// VSYNC/HSYNC POL can be found in data sheet timing diagram,
// Notice: the initial setting may contain VSYNC/HSYNC POL inverse settings so that condition is different.

#define SENSOR_VSYNC_POL    CUS_CLK_POL_POS        // if VSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_HSYNC_POL    CUS_CLK_POL_NEG        // if HSYNC pin High and data bus have data, set CUS_CLK_POL_POS
#define SENSOR_PCLK_POL     CUS_CLK_POL_POS        // depend on sensor setting, sometimes need to try CUS_CLK_POL_POS or CUS_CLK_POL_NEG
//static int  drv_Fnumber = 22;

//#define Delay_ms(n)                             SYS_UDELAY(n*1000)
static int pCus_SetAEGain(ms_cus_sensor *handle, u32 gain);
static int pCus_SetAEUSecs(ms_cus_sensor *handle, u32 us);
int nvp6124b_cus_camsensor_release_handle(ms_cus_sensor *handle);

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
    bool reg_dirty; //sensor setting need to update through I2C
} nvp6124b_params;
// set sensor ID address and data,

static I2C_ARRAY Sensor_id_table[] =
{

};

/////////// structure definition ///////////////////
// device address define
#define NVP6124_R0_ID 	0x84
#define NVP6114A_R0_ID 	0x85
#define NVP6124B_R0_ID 	0x86
#define NTSC		0x00
#define PAL		0x01

unsigned short chip_id;
unsigned int nvp6124_cnt = 4; // 0 ~ 3 channel
unsigned int vloss;

/*nvp6124 1080P 色彩推荐配置*/
#define BRI_CENTER_VAL_NTSC 0xF4
#define BRI_CENTER_VAL_PAL  0xF4
#define CON_CENTER_VAL_NTSC 0x90
#define CON_CENTER_VAL_PAL  0x90
#define SAT_CENTER_VAL_NTSC 0x80
#define SAT_CENTER_VAL_PAL  0x80                       
#define HUE_CENTER_VAL_NTSC 0x00
#define HUE_CENTER_VAL_PAL  0x00


/*nvp6124 720P 色彩推荐配置*/
#define BRI_CENTER_VAL_NTSC_720P 0x08
#define BRI_CENTER_VAL_PAL_720P  0x08
#define CON_CENTER_VAL_NTSC_720P 0x88
#define CON_CENTER_VAL_PAL_720P  0x88
#define SAT_CENTER_VAL_NTSC_720P 0x90
#define SAT_CENTER_VAL_PAL_720P  0x90                       
#define HUE_CENTER_VAL_NTSC_720P 0xFD
#define HUE_CENTER_VAL_PAL_720P  0x00
                           
/*nvp6124 960H 色彩推荐配置*/
#define BRI_CENTER_VAL_NTSC_960H 0xFF
#define BRI_CENTER_VAL_PAL_960H  0x00
#define CON_CENTER_VAL_NTSC_960H 0x92
#define CON_CENTER_VAL_PAL_960H  0x90
#define SAT_CENTER_VAL_NTSC_960H 0x88
#define SAT_CENTER_VAL_PAL_960H  0x88                       
#define HUE_CENTER_VAL_NTSC_960H 0x01
#define HUE_CENTER_VAL_PAL_960H  0x00

unsigned int nvp6124_con_tbl[2]  = {CON_CENTER_VAL_NTSC, CON_CENTER_VAL_PAL};
unsigned int nvp6124_hue_tbl[2]  = {HUE_CENTER_VAL_NTSC, HUE_CENTER_VAL_PAL};
unsigned int nvp6124_sat_tbl[2]  = {SAT_CENTER_VAL_NTSC, SAT_CENTER_VAL_PAL};
unsigned int nvp6124_bri_tbl[2]  = {BRI_CENTER_VAL_NTSC, BRI_CENTER_VAL_PAL};

unsigned int nvp6124_con_tbl_720P[2]  = {CON_CENTER_VAL_NTSC_720P, CON_CENTER_VAL_PAL_720P};
unsigned int nvp6124_hue_tbl_720P[2]  = {HUE_CENTER_VAL_NTSC_720P, HUE_CENTER_VAL_PAL_720P};
unsigned int nvp6124_sat_tbl_720P[2]  = {SAT_CENTER_VAL_NTSC_720P, SAT_CENTER_VAL_PAL_720P};
unsigned int nvp6124_bri_tbl_720P[2]  = {BRI_CENTER_VAL_NTSC_720P, BRI_CENTER_VAL_PAL_720P};


unsigned int nvp6124_con_tbl_960H[2]  = {CON_CENTER_VAL_NTSC_960H, CON_CENTER_VAL_PAL_960H};
unsigned int nvp6124_hue_tbl_960H[2]  = {HUE_CENTER_VAL_NTSC_960H, HUE_CENTER_VAL_PAL_960H};
unsigned int nvp6124_sat_tbl_960H[2]  = {SAT_CENTER_VAL_NTSC_960H, SAT_CENTER_VAL_PAL_960H};
unsigned int nvp6124_bri_tbl_960H[2]  = {BRI_CENTER_VAL_NTSC_960H, BRI_CENTER_VAL_PAL_960H};

unsigned char nvp6124_motion_sens_tbl[8]= {0xe0,0xc8,0xa0,0x98,0x78,0x68,0x50,0x48};
unsigned char ch_mode_status[16]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
unsigned char ch_vfmt_status[16]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};


enum
{
	NVP6124_VI_SD = 0,       	//960x576i(480)
	NVP6124_VI_720P_2530,		//1280x720@25p(30)
	NVP6124_VI_720P_5060,		//1280x720@50p(60)
	NVP6124_VI_1080P_2530,		//1920x1080@25p(30)
	NVP6124_VI_1920H,			//1920x576i(480)
	NVP6124_VI_720H,			//720x576i(480)
	NVP6124_VI_1280H,			//1280x576i(480)
	NVP6124_VI_1440H,			//1440x576i(480)
	NVP6124_VI_960H2EX,   		//3840x576i(480)
	NVP6124_VI_HDEX,			//2560x720@25p(30)
	NVP6124_VI_BUTT
};

typedef enum _nvp6124_outmode_sel
{
	NVP6124_OUTMODE_1MUX_SD = 0,
	NVP6124_OUTMODE_1MUX_HD,
	NVP6124_OUTMODE_1MUX_HD5060,
	NVP6124_OUTMODE_1MUX_FHD,
	NVP6124_OUTMODE_2MUX_SD,
	NVP6124_OUTMODE_2MUX_HD_X,
	NVP6124_OUTMODE_2MUX_HD,
	NVP6124_OUTMODE_2MUX_FHD_X,
	NVP6124_OUTMODE_4MUX_SD,
	NVP6124_OUTMODE_4MUX_HD_X,
	NVP6124_OUTMODE_4MUX_HD,
	NVP6124_OUTMODE_2MUX_FHD,
	NVP6124_OUTMODE_1MUX_HD_X,   //nvp6124b
	NVP6124_OUTMODE_1MUX_FHD_X,
	NVP6124_OUTMODE_4MUX_FHD_X,
	NVP6124_OUTMODE_4MUX_MIX,
	NVP6124_OUTMODE_2MUX_MIX,
	NVP6124_OUTMODE_BUTT
}NVP6124_OUTMODE_SEL;

typedef struct _nvp6124_video_mode
{
    unsigned int chip;
    unsigned int mode;
	unsigned char vformat[16];
	unsigned char chmode[16];
}nvp6124_video_mode;

typedef struct _nvp6124_chn_mode
{
    unsigned char ch;
	unsigned char vformat;
	unsigned char chmode;
}nvp6124_chn_mode;

typedef struct _nvp6124_opt_mode
{
	unsigned char chipsel;
    unsigned char portsel;
	unsigned char portmode;
	unsigned char chid;
}nvp6124_opt_mode;

typedef struct _nvp6124_input_videofmt
{
    unsigned int inputvideofmt[16];
	unsigned int getvideofmt[16];
	unsigned int geteqstage[16];
	unsigned int getacpdata[16][8];
}nvp6124_input_videofmt;

typedef struct _nvp6124_video_adjust
{
    unsigned int ch;
	unsigned int value;
}nvp6124_video_adjust;

static unsigned char NVP6124_B0_Buf[] = {
      // 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F
/*0x00*/ 0x00,0x00,0x20,0x03,0x00,0x00,0x00,0x00,0x60,0x60,0x60,0x60,0x08,0x08,0x08,0x08,
/*0x10*/ 0x80,0x80,0x80,0x80,0x90,0x90,0x90,0x90,0x00,0x00,0x00,0x00,0xaf,0xaf,0xaf,0xaf,
/*0x20*/ 0x2f,0x92,0x0b,0x43,0x2f,0x92,0x0b,0x43,0x2f,0x92,0x0b,0x43,0x2f,0x92,0x0b,0x43,
/*0x30*/ 0x17,0x17,0x17,0x17,0x04,0x04,0x04,0x04,0x0a,0x0a,0x0a,0x0a,0x80,0x80,0x80,0x80,
/*0x40*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x50*/ 0x00,0x00,0x00,0x00,0xf0,0x10,0x10,0x00,0xa0,0xa0,0xa0,0xa0,0x9e,0x9e,0x9e,0x9e,
/*0x60*/ 0x00,0x00,0x00,0x00,0x8d,0x8d,0x8d,0x8d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x70*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x88,0x88,0x11,0x11,0x00,0x00,0x00,0x00,
/*0x80*/ 0x0F,0x66,0x66,0x33,0x33,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x11,0x77,0x77,0x00,
/*0x90*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x16,0x16,0x16,0x16,0x00,0x00,0x00,0x00,
/*0xa0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xb0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xc0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xd0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xe0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xf0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

static unsigned char NVP6124_B1_Buf[] = {
      // 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F
/*0x00*/ 0x02,0x0f,0x0f,0x0f,0x0f,0x0f,0x1b,0xc8,0x03,0x00,0x10,0x32,0x54,0x76,0x00,0x98,
/*0x10*/ 0xba,0xdc,0xfe,0x08,0x00,0x00,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,
/*0x20*/ 0x88,0x88,0x03,0x19,0x18,0x16,0x00,0x00,0x00,0x88,0xff,0x40,0xaa,0xaa,0xaa,0xaa,
/*0x30*/ 0xaa,0x82,0x00,0x00,0x00,0x8C,0xA0,0x00,0x18,0x01,0x80,0x30,0x00,0x00,0x80,0x00,
/*0x40*/ 0x0f,0x0f,0x0f,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x50*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x60*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x70*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x80*/ 0x60,0x00,0x14,0x2C,0x00,0x00,0x00,0x00,0x44,0x44,0xdd,0xdd,0x11,0x11,0x55,0x55,
/*0x90*/ 0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xa0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xb0*/ 0x00,0x00,0x00,0x00,0x40,0x30,0x40,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xc0*/ 0x22,0x22,0x33,0x33,0x00,0x00,0x11,0x11,0x00,0x00,0xff,0x00,0x30,0x30,0x30,0x30,
/*0xd0*/ 0x00,0x00,0x3C,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xe0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xf0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01
};


static unsigned char NVP6124_B2_Buf[] = {
      // 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F
/*0x00*/ 0x10,0x60,0x10,0x60,0x10,0x60,0x10,0x60,0x10,0x60,0x10,0x60,0x10,0x60,0x10,0x60,
/*0x10*/ 0x00,0x00,0x0F,0x00,0xc0,0x00,0x55,0x55,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,
/*0x20*/ 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
/*0x30*/ 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
/*0x40*/ 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
/*0x50*/ 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
/*0x60*/ 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
/*0x70*/ 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
/*0x80*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x90*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xa0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xb0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xc0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xd0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xe0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xf0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02
};   

static unsigned char NVP6124_B3_Buf[] = {
      // 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F
/*0x00*/ 0x37,0x37,0x1b,0x05,0x00,0x07,0x00,0x09,0x00,0x00,0x08,0x06,0x00,0x46,0x00,0x00,
/*0x10*/ 0xaa,0x1c,0x18,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x20*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x01,
/*0x30*/ 0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x32,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x40*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x50*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x60*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x70*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x80*/ 0x37,0x37,0x1b,0x05,0x00,0x07,0x00,0x09,0x00,0x00,0x08,0x06,0x00,0x46,0x00,0x00,
/*0x90*/ 0xaa,0x1c,0x18,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
/*0xa0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x01,
/*0xb0*/ 0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x32,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xc0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xd0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xe0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xf0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03
};

static unsigned char NVP6124_B4_Buf[] = {
      // 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F
/*0x00*/ 0x37,0x37,0x1b,0x05,0x00,0x07,0x00,0x09,0x00,0x00,0x08,0x06,0x00,0x46,0x00,0x00,
/*0x10*/ 0xaa,0x1c,0x18,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x20*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x01,
/*0x30*/ 0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x32,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x40*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x50*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x60*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x70*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x80*/ 0x37,0x37,0x1b,0x05,0x00,0x07,0x00,0x09,0x00,0x00,0x08,0x06,0x00,0x46,0x00,0x00,
/*0x90*/ 0xaa,0x1c,0x18,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xa0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x01,
/*0xb0*/ 0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x32,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xc0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xd0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xe0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xf0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04
};

static unsigned char NVP6124_B5678_Buf[] = {
      // 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F
/*0x00*/ 0xC0,0x0c,0x0c,0x1f,0x00,0x24,0x40,0x80,0x50,0x38,0x0f,0x00,0x04,0x30,0x30,0x00,
/*0x10*/ 0x06,0x06,0x00,0x80,0x37,0x80,0x49,0x37,0xef,0xdf,0xdf,0x08,0x50,0x0c,0x01,0x88,
/*0x20*/ 0x84,0x20,0x23,0x00,0x2a,0xdc,0xf0,0x57,0x90,0x70,0x52,0x78,0x08,0x68,0x00,0x07,
/*0x30*/ 0xe0,0x43,0xa2,0x00,0x00,0x15,0x25,0x00,0x00,0x02,0x02,0x00,0x00,0x00,0x00,0x00,
/*0x40*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x44,0xaa,0x00,0x00,0x00,0x00,0x00,
/*0x50*/ 0x84,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x30,
/*0x60*/ 0x53,0x53,0x20,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x70*/ 0xc0,0x01,0x06,0x06,0x11,0x00,0x01,0x81,0x01,0x01,0x01,0x81,0x01,0x01,0x00,0x00,
/*0x80*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x90*/ 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x48,0x84,0x00,0x80,0x00,0x00,0x00,0x00,
/*0xa0*/ 0x10,0x30,0x0c,0x50,0x10,0x34,0x70,0x5C,0x20,0x20,0x30,0x40,0x20,0x20,0x14,0xA0,
/*0xb0*/ 0x40,0x50,0x0e,0x00,0x00,0x80,0x00,0x00,0x38,0xb2,0x05,0x00,0xa0,0x00,0x00,0x00,
/*0xc0*/ 0x17,0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xd0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xe0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xf0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05
};

static unsigned char NVP6124_B9_Buf[] = {
       //0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F
/*0x00*/ 0x02,0x04,0x06,0x08,0x0c,0x10,0x14,0x18,0x1c,0x20,0x28,0x30,0x38,0x40,0x48,0x50,
/*0x10*/ 0x58,0x60,0x68,0x70,0x78,0x7f,0x87,0x8f,0x97,0x9f,0xaf,0xbf,0xcf,0xdf,0xef,0xff,
/*0x20*/ 0x01,0x03,0x05,0x07,0x0b,0x0f,0x13,0x17,0x1b,0x1f,0x27,0x2f,0x37,0x3f,0x47,0x4f,
/*0x30*/ 0x57,0x5f,0x67,0x6f,0x77,0x7f,0x87,0x8f,0x97,0x9f,0xaf,0xbf,0xcf,0xdf,0xef,0xff,
/*0x40*/ 0x00,0x00,0x00,0x00,0x0f,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x50*/ 0xee,0x00,0xe5,0x4e,0xee,0x00,0xe5,0x4e,0xee,0x00,0xe5,0x4e,0xee,0x00,0xe5,0x4e,
/*0x60*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x70*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x80*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x90*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xa0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xb0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xc0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xd0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xe0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xf0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09
};    

static unsigned char NVP6124_BA_Buf[] = {
      // 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F
/*0x00*/ 0x00,0x00,0x02,0x80,0x04,0x04,0x08,0x04,0x0C,0x00,0x08,0x0E,0x80,0x20,0x0A,0x08,
/*0x10*/ 0x30,0x42,0x80,0x0A,0x7A,0x88,0x6C,0x5E,0x18,0x1F,0x8E,0x94,0xC7,0xA3,0xA0,0x0A,
/*0x20*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x01,0x00,0x01,0x03,0xA0,0x04,0x03,
/*0x30*/ 0x03,0x0B,0x0A,0x11,0x0D,0x06,0x27,0x00,0x4E,0x6D,0x74,0x00,0x00,0x00,0x00,0x00,
/*0x40*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x50*/ 0x01,0x05,0x87,0x0B,0x01,0x05,0x87,0x0B,0x8E,0x11,0x64,0x00,0x00,0x00,0x00,0x00,
/*0x60*/ 0x02,0x01,0x00,0x01,0x03,0xA0,0x04,0x03,0x03,0x0B,0x0A,0x11,0x0D,0x06,0x27,0x00,
/*0x70*/ 0x4E,0x6D,0x74,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x80*/ 0x00,0x00,0x02,0x80,0x04,0x04,0x08,0x04,0x0C,0x00,0x08,0x0E,0x80,0x20,0x0A,0x08,
/*0x90*/ 0x30,0x42,0x80,0x0A,0x7A,0x88,0x6C,0x5E,0x18,0x1F,0x8E,0x94,0xC7,0xA3,0xA0,0x0A,
/*0xa0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x01,0x00,0x01,0x03,0xA0,0x04,0x03,
/*0xb0*/ 0x03,0x0B,0x0A,0x11,0x0D,0x06,0x27,0x00,0x4E,0x6D,0x74,0x00,0x00,0x00,0x00,0x00,
/*0xc0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xd0*/ 0x01,0x05,0x87,0x0B,0x01,0x05,0x87,0x0B,0x8E,0x11,0x64,0x00,0x00,0x00,0x00,0x00,
/*0xe0*/ 0x02,0x01,0x00,0x01,0x03,0xA0,0x04,0x03,0x03,0x0B,0x0A,0x11,0x0D,0x06,0x27,0x00,
/*0xf0*/ 0x4E,0x6D,0x74,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0A
};

static unsigned char NVP6124_BB_Buf[] = {
     // 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F
/*0x00*/ 0x00,0x00,0x02,0x80,0x04,0x04,0x08,0x04,0x0C,0x00,0x08,0x0E,0x80,0x20,0x0A,0x08,
/*0x10*/ 0x30,0x42,0x80,0x0A,0x7A,0x88,0x6C,0x5E,0x18,0x1F,0x8E,0x94,0xC7,0xA3,0xA0,0x0A,
/*0x20*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x01,0x00,0x01,0x03,0xA0,0x04,0x03,
/*0x30*/ 0x03,0x0B,0x0A,0x11,0x0D,0x06,0x27,0x00,0x4E,0x6D,0x74,0x00,0x00,0x00,0x00,0x00,
/*0x40*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x50*/ 0x01,0x05,0x87,0x0B,0x01,0x05,0x87,0x0B,0x8E,0x11,0x64,0x00,0x00,0x00,0x00,0x00,
/*0x60*/ 0x02,0x01,0x00,0x01,0x03,0xA0,0x04,0x03,0x03,0x0B,0x0A,0x11,0x0D,0x06,0x27,0x00,
/*0x70*/ 0x4E,0x6D,0x74,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x80*/ 0x00,0x00,0x02,0x80,0x04,0x04,0x08,0x04,0x0C,0x00,0x08,0x0E,0x80,0x20,0x0A,0x08,
/*0x90*/ 0x30,0x42,0x80,0x0A,0x7A,0x88,0x6C,0x5E,0x18,0x1F,0x8E,0x94,0xC7,0xA3,0xA0,0x0A,
/*0xa0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x01,0x00,0x01,0x03,0xA0,0x04,0x03,
/*0xb0*/ 0x03,0x0B,0x0A,0x11,0x0D,0x06,0x27,0x00,0x4E,0x6D,0x74,0x00,0x00,0x00,0x00,0x00,
/*0xc0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xd0*/ 0x01,0x05,0x87,0x0B,0x01,0x05,0x87,0x0B,0x8E,0x11,0x64,0x00,0x00,0x00,0x00,0x00,
/*0xe0*/ 0x02,0x01,0x00,0x01,0x03,0xA0,0x04,0x03,0x03,0x0B,0x0A,0x11,0x0D,0x06,0x27,0x00,
/*0xf0*/ 0x4E,0x6D,0x74,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0B
};

static unsigned char NVP6124_B5678_SD_Buf[] = {
      // 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F
/*0x00*/ 0xC0,0x0E,0x0C,0x1F,0x00,0x20,0x40,0x80,0x50,0x38,0x0F,0x00,0x04,0x30,0x30,0x00,
/*0x10*/ 0x06,0x04,0x00,0x80,0x37,0x80,0x49,0x37,0xEF,0xDF,0xDF,0x20,0x50,0x0C,0xFF,0x88,
/*0x20*/ 0x90,0x20,0x23,0x00,0x2A,0xDC,0xF0,0x57,0x90,0x1f,0x52,0x78,0x04,0x68,0x00,0x07,
/*0x30*/ 0xE0,0x43,0xA2,0x00,0x00,0x15,0x25,0x00,0x00,0x02,0x02,0x00,0x00,0x00,0x00,0x00,
/*0x40*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x44,0xAA,0x00,0x00,0x00,0x00,0x00,
/*0x50*/ 0x84,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x60*/ 0x53,0x53,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0x70*/ 0xC0,0x01,0x06,0x06,0x11,0x00,0x01,0x81,0x01,0x01,0x00,0x00,0x00,0x80,0x00,0x00,
/*0x80*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x3f,0xff,0xff,0xff,0x00,0x00,0x00,
/*0x90*/ 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x48,0x84,0x00,0x80,0x00,0x00,0x00,0x00,
/*0xa0*/ 0x10,0x30,0x0c,0x50,0x10,0x34,0x70,0x5c,0x20,0x20,0x30,0x40,0x20,0x20,0x14,0x20,
/*0xb0*/ 0x40,0x50,0x0e,0x00,0x00,0x80,0x00,0x00,0x39,0xb2,0x05,0x00,0xa0,0x00,0x00,0x00,
/*0xc0*/ 0x00,0x13,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xd0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xe0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*0xf0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05 
};

static I2C_ARRAY Sensor_init_System_table[] =
{
    0xFF, 0x01,			// Bank 1
    0x82, 0x12,			// -RESERVED- ?? Clk ??
    0x83, 0x2C,			// -RESERVED- ??
    0x3e, 0x10,			// -RESERVED- ??
    0x80, 0x60,			// -RESERVED- ??
    0x80, 0x61,			// -RESERVED- ??
    SENSOR_DELAY_REG, 100,
    0x80, 0x40,			// -RESERVED- ??
    0x81, 0x02,			// -RESERVED- ??
    0x97, 0x00,			// DEC_RST4  DEC_RST3  DEC_RST2  DEC_RST1
    SENSOR_DELAY_REG, 10,
    0x80, 0x60,
    0x81, 0x00,
    SENSOR_DELAY_REG, 10,
    0x97, 0x0F,
    0x38, 0x18,			// AUD_SW_RST
    0x38, 0x08,			// AUD_SW_RST
    SENSOR_DELAY_REG, 10,
    0xCA, 0xAE,//0xAE,			// VCLK_1_EN  VCLK_2_EN  VDO_1_EN (11 : ENABLE)  VDO_2_EN
};

static I2C_ARRAY TriggerStartTbl[] =
{

};

static I2C_ARRAY PatternTbl[] =
{

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

};

static I2C_ARRAY gain_reg[] =
{

};

//static int g_sensor_ae_min_gain = 1024;
static CUS_GAIN_GAP_ARRAY gain_gap_compensate[16] =
{

};

static I2C_ARRAY expo_reg[] =
{

};

static I2C_ARRAY vts_reg[] =
{

};

/////////// function definition ///////////////////

/////////////////// sensor hardware dependent //////////////
static int pCus_poweron(ms_cus_sensor *handle)
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;

    //Sensor power on sequence
    //DrvSensorIFHWSetIOPad(0/*TBD*/, CUS_SENIF_BUS_BT656, CUS_SR_PAD_CFG_6);//call sensor if
    sensor_if->SetIOPad(SENSOR_PAD_GROUP_SET/*TBD. Pad Num.*/, CUS_SENIF_BUS_BT656, CUS_SR1_BT656_MODE_1); //CHIPTOP_SR1_BT656_MODE_1);            //Parallel: reg_sr1_bt656_mode
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_DISABLE, handle->PCLK_POLARITY);     //Set_csi_if(0, 0); //disable MIPI
    sensor_if->MCLK(SENSOR_PAD_GROUP_SET, 1, handle->mclk);

    SENSOR_DMSG("[%s] reset low\n", __FUNCTION__);
    sensor_if->Reset(SENSOR_PAD_GROUP_SET, handle->reset_POLARITY);
    MsSleep(RTK_MS_TO_TICK(100));//usleep(500);
    SENSOR_DMSG("[%s] power low\n", __FUNCTION__);
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, handle->pwdn_POLARITY);
    MsSleep(RTK_MS_TO_TICK(100));//usleep(500);

    // power -> high, reset -> high
    SENSOR_DMSG("[%s] power high\n", __FUNCTION__);
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, !handle->pwdn_POLARITY);
    MsSleep(RTK_MS_TO_TICK(100));//usleep(500);
    SENSOR_DMSG("[%s] reset high\n", __FUNCTION__);
    sensor_if->Reset(SENSOR_PAD_GROUP_SET, !handle->reset_POLARITY);
    MsSleep(RTK_MS_TO_TICK(100));//usleep(500);

    //sensor_if->Set3ATaskOrder( def_order);
    // pure power on
    sensor_if->SWReset(handle->channel_num, FALSE);
    sensor_if->PowerOff(SENSOR_PAD_GROUP_SET, !handle->pwdn_POLARITY);
    return SUCCESS;
}

static int pCus_poweroff(ms_cus_sensor *handle)
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    //sensor_if->MIPISamplingDelay(handle, false, handle->mipi_sampling_delay);
    SENSOR_DMSG("[%s] power low\n", __FUNCTION__);
    sensor_if->SWReset(handle->channel_num, TRUE);
    sensor_if->PowerOff( 1, handle->pwdn_POLARITY);

    MsSleep(RTK_MS_TO_TICK(200));//usleep(1000);
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
            MsSleep(RTK_MS_TO_TICK(10));//usleep(1*1000);
    }
    SENSOR_IMSG("[%s] %s get sensor id:0x%x, SUCCESS!\n", __FUNCTION__, handle->model_id, ( int )*id);
    return SUCCESS;
}

static int nvp6124b_SetPatternMode(ms_cus_sensor *handle,u32 mode)
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
    //SensorReg_Read(usreg, &sen_data);
    //UartSendTrace("nvp6124b reg: 0x%x, data: 0x%x, read: 0x%x.\n", usreg, usval, sen_data);

    return SUCCESS;
}

static int pCus_I2CRead(ms_cus_sensor *handle, unsigned short usreg, unsigned short* pusval)
{
    unsigned short usread_data;

    SensorReg_Read(usreg, &usread_data);
    *pusval = usread_data;
    //UartSendTrace("nvp6124b reg: 0x%x, data: 0x%x\n", usreg, usread_data);

    return SUCCESS;
}
int nvp6124_write_table(ms_cus_sensor *handle, unsigned short addr, unsigned char *tbl_ptr, unsigned char tbl_cnt)
{
	unsigned char i = 0;
	unsigned short sen_data;
	
	for(i = 0; i < tbl_cnt; i ++)
	{
		SensorReg_Write((addr + i), *(tbl_ptr + i));
		//SensorReg_Read((addr + i), &sen_data);
		//UartSendTrace("nvp6124b reg: 0x%x, data: 0x%x, read: 0x%x.\n", (addr + i), *(tbl_ptr + i), sen_data);
	}
	return SUCCESS;
}
#endif

void software_reset(ms_cus_sensor *handle)
{
    SensorReg_Write( 0xFF, 0x01); 
    SensorReg_Write( 0x80, 0x40); 
    SensorReg_Write( 0x81, 0x02);
    SensorReg_Write( 0x80, 0x61);
    SensorReg_Write( 0x81, 0x00);
    MsSleep(RTK_MS_TO_TICK(100));
    SensorReg_Write( 0x80, 0x60); 
    SensorReg_Write( 0x81, 0x00);
    MsSleep(RTK_MS_TO_TICK(100));
}

/*nvp6124b视频模式值转换*/
static unsigned int nvp6124b_vdsts2_nvp6124(unsigned int vdsts)
{
	unsigned int ret;
	switch(vdsts)
	{
		case 0x00:			//nvp6124b NTSC SD状态值
			ret = 0x01;		//nvp6124  NTSC SD状态值
		break;
		case 0x10:          //nvp6124b PAL SD状态值
			ret = 0x02;
		break;
		case 0x20:			//nvp6124b NT 720P/30状态值
			ret = 0x04;
		break;
		case 0x21:                  //AHD 25P
			ret = 0x08;
		break;
		case 0x22:                  //AHD 60P
			ret = 0x10;
		break;
		case 0x23:                  //AHD 50P
			ret = 0x20;
		break;
		case 0x30:                  //AFHD  30P
			ret = 0x40;
		break;
		case 0x31:                  //AFHD  25P
			ret = 0x80;
		break;
		case 0xFF:
			ret = 0x00;
		break;
		default:
			ret = vdsts;
		break;
	}
	return ret;
}

#define CNT 5
unsigned int video_fmt_debounce(ms_cus_sensor *handle, unsigned char ch)
{
	unsigned int idx=CNT-1;
	unsigned int tmp, buf[CNT]={0,0,0,0,0};
	int i, j,cnt[CNT]={0,0,0,0,0};
		
	for(i=0; i<CNT; i++)
	{
		if(chip_id == NVP6124B_R0_ID)
		{
			SensorReg_Write( 0xFF, 0x05+ch%4);
			SensorReg_Read(0xF0, &tmp);
			buf[i] = nvp6124b_vdsts2_nvp6124(tmp);
			if(buf[i] == 0)
			{
				SensorReg_Write( 0xFF, 0x00);
				SensorReg_Read(0xD0+(ch%4), &buf[i]);
			}
		}
		else
		{
			SensorReg_Write( 0xFF, 0x00);
			SensorReg_Read(0xD0+(ch%4), &buf[i]);
		}
	}
	for(i=0; i<CNT; i++)
    {
        for(j=0; j<CNT; j++)
        {
            if(buf[i] == buf[j])
            {
            	cnt[i]++;
            }
        }
        if(i>0 && cnt[i-1]>=cnt[i])
	        idx = i-1;      
    }
	UartSendTrace("video_fmt_debounce ch[%d] buf[%d] = %x\n", ch, idx, buf[idx]);
	return buf[idx];
}

/*视频输入制式检测函数*/
void video_fmt_det(ms_cus_sensor *handle, nvp6124_input_videofmt *pvideofmt)
{
	int i;
	unsigned char tmp;
	static nvp6124_input_videofmt videofmt;

	for(i=0; i<nvp6124_cnt; i++)
	{
	    if(chip_id != NVP6124B_R0_ID)
		{
			SensorReg_Write( 0xFF, 0x00);
			SensorReg_Read(0xD0+i%4, &tmp);
			pvideofmt->getvideofmt[i] = tmp;
		}
		else
		{
			SensorReg_Write( 0xFF, 0x05 + i%4);
			SensorReg_Read(0xF0, &tmp);
			pvideofmt->getvideofmt[i] = nvp6124b_vdsts2_nvp6124(tmp);
			if(pvideofmt->getvideofmt[i] == 0x00)
			{
				SensorReg_Write( 0xFF, 0x00);
				SensorReg_Read(0xD0+i%4, &tmp);
				pvideofmt->getvideofmt[i] = tmp;
			}
		}

		if(videofmt.getvideofmt[i] != pvideofmt->getvideofmt[i])
		{
			pvideofmt->getvideofmt[i] = video_fmt_debounce(handle, i);
			videofmt.getvideofmt[i] = pvideofmt->getvideofmt[i];
		}
		
	    if(chip_id != NVP6124B_R0_ID)
		{
			if(    ((pvideofmt->getvideofmt[i] == 0x40)&&(((vloss>>i)&0x01) == 0x00)) 
				|| ((pvideofmt->getvideofmt[i] == 0x10)&&(((vloss>>i)&0x01) == 0x00)))
			{
				SensorReg_Write( 0xFF, 0x00);
				SensorReg_Write( 0x23+4*(i%4), 0x41);
				SensorReg_Write( 0xFF, 0x05+i%4);
				SensorReg_Write( 0x47, 0xee);
			}
			else
			{
				SensorReg_Write( 0xFF, 0x00);
				SensorReg_Write( 0x23+4*(i%4), 0x43);
				SensorReg_Write( 0xFF, 0x05+i%4);
				SensorReg_Write( 0x47, 0x04);
			}
		}		
		else
		{
			if(ch_mode_status[i] == NVP6124_VI_1080P_2530 && ch_vfmt_status[i] == NTSC)
			{
				if(((vloss>>i)&0x01) == 0x00)
				{
					SensorReg_Write( 0xFF, 0x05+i%4);
					SensorReg_Write( 0x47, 0xEE);
				}
				else
				{
					SensorReg_Write( 0xFF, 0x05+i%4);
					SensorReg_Write( 0x47, 0x04);
				}	
			}
		}		
	}
}

unsigned int nvp6124_getvideoloss(ms_cus_sensor *handle)
{
	unsigned int vloss=0, i;
	unsigned char tmp;
	//static unsigned int vlossbak=0xFFFF;
	SensorReg_Write( 0xFF, 0x00);
	SensorReg_Read(0xB8, &tmp);
	vloss|=(tmp&0x0F)<<(4*i);
	#if 0
	if(vlossbak != vloss)
	{
		for(ch=0;ch<nvp6124_cnt*4;ch++)
		{
			if(((vloss>>ch)&0x01)==0x00 && ((vlossbak>>ch)&0x01)==0x01)
				NVP6124_AfeReset(ch);
		}
		vlossbak = vloss;
	}
	#endif
	return vloss;
}

void NVP6124_AfeReset(ms_cus_sensor *handle, unsigned char ch)
{
	int i = 0;
	unsigned char tmp;
	if(ch == 0xFF)
	{
		SensorReg_Write(0xFF, 0x00);
		SensorReg_Read(0x02, &tmp);
		SensorReg_Write(0x02, tmp|0x0F);
		SensorReg_Write(0x02, tmp&0xF0);
		UartSendTrace("NVP6124_AfeReset ALL Channel done\n");
	}
	else
	{
		SensorReg_Write( 0xFF, 0x00);
		SensorReg_Read(0x02, &tmp);
		SensorReg_Write( 0x02, tmp|(0x01<<(ch%4)));
		SensorReg_Write( 0x02, tmp&0xF0);
		UartSendTrace("NVP6124_AfeReset ch[%d] done\n", ch);
	}	
	
}

void nvp6124_datareverse(ms_cus_sensor *handle)
{
/*
BANK1 0xD2[5:2],每个bit控制一个bt656的数据顺序，1为反序，0为正序。
*/
      SensorReg_Write(0xFF, 0x01);
	SensorReg_Write(0xD2, 0x3C); 
	UartSendTrace("nvp6124 data reversed\n");
}

void nvp6124_set_clockmode(ms_cus_sensor *handle, unsigned char chip, unsigned char is297MHz)
{
      unsigned char chipon297MHz=0;
	SensorReg_Write(0xFF, 0x01);
	SensorReg_Write(0x80, 0x40);
	if(is297MHz == 1)
	{
		SensorReg_Write(0x82, 0x12); 
		chipon297MHz = 1;
	}
	else
	{
		SensorReg_Write(0x82, 0x14); 
		chipon297MHz = 0;
	}
	SensorReg_Write(0x83, 0x2C); 
	SensorReg_Write(0x80, 0x61); 
	SensorReg_Write(0x80, 0x60); 
	 
	UartSendTrace("chip %d nvp6124_set_clockmode %d\n", chip, is297MHz);
}

void nvp6124_set_fpc(ms_cus_sensor *handle, unsigned char ch, unsigned char vformat)
{
	unsigned char tmp;
	SensorReg_Write(0xFF, 0x00);
	SensorReg_Read(0x54, &tmp);
	if(vformat==PAL)
		tmp &= ~(0x10<<(ch%4));
	else	
		tmp |= (0x10<<(ch%4));
	SensorReg_Write(0x54, tmp);
}

void nvp6124b_syncchange(ms_cus_sensor *handle, unsigned char ch, nvp6124_video_mode *pvmode)
{
	unsigned char vformat = pvmode->vformat[ch];

	if(vformat == NTSC)
	{
		if(pvmode->chmode[ch] == NVP6124_VI_1080P_2530)
		{
			SensorReg_Write( 0xff,0x00);
			SensorReg_Write( 0x23+(ch%4)*4,0x43);
			SensorReg_Write( 0x58+(ch%4),0x4E);
			SensorReg_Write( (ch%4)+0x8E,0x09);

			SensorReg_Write( 0xff,0x05+(ch%4));
			SensorReg_Write( 0x24,0x1A);
			SensorReg_Write( 0x47,0xEE);
			SensorReg_Write( 0x50,0xC6);
			SensorReg_Write( 0xBB,0x04);
		}
		else if(pvmode->chmode[ch]  == NVP6124_VI_720P_5060)
		{
			SensorReg_Write( 0xff,0x00);
			SensorReg_Write( 0x23+(ch%4)*4,0x43);
			SensorReg_Write( 0x58+(ch%4),0xa8);
			SensorReg_Write( (ch%4)+0x8E,0x09);

			SensorReg_Write( 0xff,0x05+(ch%4));
			SensorReg_Write( 0x24,0x2A); // 
			SensorReg_Write( 0x47,0xEE);
			SensorReg_Write( 0x50,0xC6);
			SensorReg_Write( 0xBB,0x04);
		}
		else
		{
			SensorReg_Write( 0xff,0x00);
			SensorReg_Write( 0x23+(ch%4)*4,0x43);
			SensorReg_Write( 0xff,0x05+(ch%4));
			SensorReg_Write( 0x47,0x04);
		}
	}
	else
	{
		SensorReg_Write( 0xff,0x00);
		SensorReg_Write( 0x23+(ch%4)*4,0x43);
		SensorReg_Write( 0xff,0x05+(ch%4));
		SensorReg_Write( 0x47,0x04);
	}
}

void init_acp(ms_cus_sensor *handle, unsigned char ch)
{
	SensorReg_Write( 0xFF, 0x01);
	//Decoder TX Setting
	{
		SensorReg_Write( 0xBC, 0xF7);
		SensorReg_Write( 0xBD, 0xF7);
		SensorReg_Write( 0xA8, 0xA5);
		//ACP_RX_D0 = 0x50;
	}

	SensorReg_Write( 0xFF, 0x03+((ch%4)/2));
	SensorReg_Write( 0x3A+((ch%2)*0x80), 0x01);
	MsSleep(RTK_MS_TO_TICK(10));
	SensorReg_Write( 0x3A+((ch%2)*0x80), 0x00);
	MsSleep(RTK_MS_TO_TICK(10));
}

void acp_each_setting(ms_cus_sensor *handle, unsigned char ch)
{
	init_acp(handle, ch);
	
	SensorReg_Write( 0xFF, 0x03+((ch%4)/2));
	if(ch_mode_status[ch] == NVP6124_VI_720P_2530)
	{
		SensorReg_Write( 0x00+((ch%2)*0x80), 0x0E);
		SensorReg_Write( 0x03+((ch%2)*0x80), 0x0D);//nvp6124_mode==PAL? 0x0D:0x0E);
	}
	else if(ch_mode_status[ch] == NVP6124_VI_1080P_2530)
	{
		SensorReg_Write( 0x00+((ch%2)*0x80), 0x0E);
		SensorReg_Write( 0x03+((ch%2)*0x80), 0x0E);
	}
	SensorReg_Write( 0x0D+((ch%2)*0x80), 0x14);
	SensorReg_Write( 0x0D+((ch%2)*0x80)+1, 0x00);  
	SensorReg_Write( 0x05+((ch%2)*0x80), 0x07);
	SensorReg_Write( 0x0A+((ch%2)*0x80), 0x03);
	SensorReg_Write( 0x0B+((ch%2)*0x80), 0x10);
	SensorReg_Write( 0x2F+((ch%2)*0x80), 0x00);

	//Decoder RX Setting
	SensorReg_Write( 0xFF, 0x05+(ch%4));
	SensorReg_Write( 0x30, 0x00);
	SensorReg_Write( 0x31, 0x01);
	SensorReg_Write( 0x32, 0x64);
	SensorReg_Write( 0x7C, 0x11);
	if(ch_mode_status[ch] == NVP6124_VI_720P_2530)
	{
		SensorReg_Write( 0x7D, 0x80);
	}
	else if(ch_mode_status[ch] == NVP6124_VI_1080P_2530)
	{
		SensorReg_Write( 0x7D, 0x80);
	}
	SensorReg_Write( 0xFF, 0x03+((ch%4)/2));

	if(ch_mode_status[ch] == NVP6124_VI_720P_2530)
	{
		SensorReg_Write( 0x62+((ch%2)*0x80), 0x05);//nvp6124_mode==PAL? 0x05:0x06);	// Camera TX DATA Check
		SensorReg_Write( 0x68+((ch%2)*0x80), 0x40);	// RX size
	}
	else if(ch_mode_status[ch] == NVP6124_VI_1080P_2530)
	{
		SensorReg_Write( 0x62+((ch%2)*0x80), 0x06);	// Camera TX DATA Check
		SensorReg_Write( 0x68+((ch%2)*0x80), 0x70);	// RX size
	}

	SensorReg_Write( 0x60+((ch%2)*0x80), 0x55);
	SensorReg_Write( 0x63+((ch%2)*0x80), 0x01);
	SensorReg_Write( 0x66+((ch%2)*0x80), 0x80);
	SensorReg_Write( 0x67+((ch%2)*0x80), 0x01);
	//printk("ACP DATA READ TEST!!!!CH%d  RESOL = %s\n\r",ch, ch_mode_status[ch]==NVP6124_VI_720P_2530?"720P":"1080P");
}

void nvp6124_each_mode_setting(ms_cus_sensor *handle, nvp6124_video_mode *pvmode)
{  
	unsigned char tmp;
	unsigned char ch, chmode[16];
	unsigned char pn_value_sd_nt_comet[4] = {0x4D,0x0E,0x88,0x6C};
	unsigned char pn_value_720p_30[4] = 	{0xEE,0x00,0xE5,0x4E};
	unsigned char pn_value_720p_60[4] = 	{0x2C,0xF9,0xC5,0x52};
	unsigned char pn_value_fhd_nt[4] = 		{0x2C,0xF0,0xCA,0x52};
	unsigned char pn_value_sd_pal_comet[4]= {0x75,0x35,0xB4,0x6C};
	unsigned char pn_value_720p_25[4] = 	{0x46,0x08,0x10,0x4F};
	unsigned char pn_value_720p_50[4] = 	{0x2C,0xE7,0xCF,0x52};
	unsigned char pn_value_fhd_pal[4] = 	{0xC8,0x7D,0xC3,0x52};
	unsigned char vformat[16];

	for(ch=0;ch<(nvp6124_cnt);ch++)
  	{
		chmode[ch] = pvmode->chmode[ch];
		vformat[ch] = pvmode->vformat[ch];
		if(chip_id != NVP6124B_R0_ID)
		{
			if(chmode[ch]>NVP6124_VI_1440H && chmode[ch]<NVP6124_VI_BUTT)
				UartSendTrace("!!!chmode[%d]=%d is out of range!!!\n", ch, chmode[ch]);
		}
  	}
	for(ch=0;ch<(nvp6124_cnt);ch++)
	{
        	if(chmode[ch] < NVP6124_VI_BUTT) 
        	{
        		switch(chmode[ch])
        		{
        			case NVP6124_VI_SD:
        			case NVP6124_VI_1920H:
        			case NVP6124_VI_720H:
        			case NVP6124_VI_1280H:
        			case NVP6124_VI_1440H:
        			case NVP6124_VI_960H2EX:	
        				SensorReg_Write( 0xFF, 0x00);
        				SensorReg_Write( 0x08+ch%4, vformat[ch]==PAL?0xDD:0xA0);
        				SensorReg_Write( 0x0c+ch%4, nvp6124_bri_tbl_960H[vformat[ch]%2]);
        				SensorReg_Write( 0x10+ch%4, nvp6124_con_tbl_960H[vformat[ch]%2]);
        				SensorReg_Write( 0x14+ch%4, vformat[ch]==PAL?0x80:0x80);
        				SensorReg_Write( 0x18+ch%4, vformat[ch]==PAL?0x18:0x18);
        				SensorReg_Write( 0x21+4*(ch%4), vformat[ch]==PAL?0x02:0x82);
        				SensorReg_Write( 0x22+4*(ch%4), 0x0B);
        				SensorReg_Write( 0x23+4*(ch%4), 0x43);
        				SensorReg_Write( 0x30+ch%4, vformat[ch]==PAL?0x12:0x11);
        				SensorReg_Write( 0x3c+ch%4, nvp6124_sat_tbl_960H[vformat[ch]%2]);
        				SensorReg_Write( 0x40+ch%4, nvp6124_hue_tbl_960H[vformat[ch]%2]);
        				SensorReg_Write( 0x44+ch%4, vformat[ch]==PAL?0x00:0x00);
        				SensorReg_Write( 0x48+ch%4, vformat[ch]==PAL?0x00:0x00);
        				SensorReg_Write( 0x4c+ch%4, vformat[ch]==PAL?0x04:0x00);
        				SensorReg_Write( 0x50+ch%4, vformat[ch]==PAL?0x04:0x00);
        				//nvp6124_set_fpc(handle, ch, vformat[ch]);
        				SensorReg_Read(0x54, &tmp);
                            	if(vformat[ch]==PAL)
                            		tmp &= ~(0x10<<(ch%4));
                            	else	
                            		tmp |= (0x10<<(ch%4));
                            	SensorReg_Write(0x54, tmp);
        				if(chmode[ch]==NVP6124_VI_SD)
        				{
        					if(chip_id == NVP6124B_R0_ID)
        						SensorReg_Write( 0x58+ch%4, vformat[ch]==PAL?0x60:0xC0);
        					else
        						SensorReg_Write( 0x58+ch%4, vformat[ch]==PAL?0x80:0x90);
        				}
        				else if(chmode[ch]==NVP6124_VI_960H2EX)
        					SensorReg_Write( 0x58+ch%4, vformat[ch]==PAL?0x80:0x90);
        				else if(chmode[ch]==NVP6124_VI_720H)
        				{
        					if(chip_id == NVP6124B_R0_ID)
        						SensorReg_Write( 0x58+ch%4, vformat[ch]==PAL?0x70:0x70);
        					else
        						SensorReg_Write( 0x58+ch%4, vformat[ch]==PAL?0xB0:0x40);
        				}
        				else if(chmode[ch]==NVP6124_VI_1280H)
        				{
        					if(chip_id == NVP6124B_R0_ID)
        						SensorReg_Write( 0x58+ch%4, vformat[ch]==PAL?0x50:0x50);
        					else
        						SensorReg_Write( 0x58+ch%4, vformat[ch]==PAL?0x80:0x90);
        				}	
        					
        				else if(chmode[ch]==NVP6124_VI_1440H)
        					SensorReg_Write( 0x58+ch%4, vformat[ch]==PAL?0x90:0xA0);
        				else	
        				{
        					if(chip_id == NVP6124B_R0_ID)
        						SensorReg_Write( 0x58+ch%4, vformat[ch]==PAL?0x88:0x98);
        					else	
        						SensorReg_Write( 0x58+ch%4, vformat[ch]==PAL?0x3B:0x4B);
        				}
        				SensorReg_Write( 0x5c+ch%4, vformat[ch]==PAL?0x1e:0x1e);
        				SensorReg_Write( 0x64+ch%4, vformat[ch]==PAL?0x0d:0x08);
        				if(chip_id == NVP6124B_R0_ID)
        				{
        					if(chmode[ch]==NVP6124_VI_SD || chmode[ch]==NVP6124_VI_720H)
        					{
        		 				SensorReg_Write( 0x81+ch%4, vformat[ch]==PAL?0x00:0x00);	
        		 				SensorReg_Write( 0x85+ch%4, vformat[ch]==PAL?0x11:0x11);
        						if(chmode[ch]==NVP6124_VI_720H)
        						{
        							UartSendTrace("ch %d setted to 720H %s\n", ch, vformat[ch]==PAL?"PAL":"NTSC");
        		 					SensorReg_Write( 0x89+ch%4, vformat[ch]==PAL?0x11:0x11);
        		 					SensorReg_Write( ch%4+0x8E, vformat[ch]==PAL?0x00:0x00);
        						}
        						else
        						{
        							UartSendTrace("ch %d setted to 960H %s\n", ch, vformat[ch]==PAL?"PAL":"NTSC");
        		 					SensorReg_Write( 0x89+ch%4, vformat[ch]==PAL?0x10:0x00);
        		 					SensorReg_Write( ch%4+0x8E, vformat[ch]==PAL?0x08:0x07);
        						}	
        					}
        					else if(chmode[ch]==NVP6124_VI_1280H)
        					{
        						UartSendTrace("ch %d setted to 1280H %s\n", ch, vformat[ch]==PAL?"PAL":"NTSC");
        		 				SensorReg_Write( 0x81+ch%4, vformat[ch]==PAL?0x20:0x20);	
        		 				SensorReg_Write( 0x85+ch%4, vformat[ch]==PAL?0x00:0x00);
        		 				SensorReg_Write( 0x89+ch%4, vformat[ch]==PAL?0x10:0x10);
        	 					SensorReg_Write( ch%4+0x8E, vformat[ch]==PAL?0x20:0x20);
        					}
        					else if(chmode[ch]==NVP6124_VI_1440H)
        					{
        						UartSendTrace("ch %d setted to 1440H %s\n", ch, vformat[ch]==PAL?"PAL":"NTSC");
        		 				SensorReg_Write( 0x81+ch%4, vformat[ch]==PAL?0x30:0x30);	
        		 				SensorReg_Write( 0x85+ch%4, vformat[ch]==PAL?0x00:0x00);
        		 				SensorReg_Write( 0x89+ch%4, vformat[ch]==PAL?0x10:0x10);
        		 				SensorReg_Write( ch%4+0x8E, vformat[ch]==PAL?0x10:0x10);
        					}
        					else if(chmode[ch]==NVP6124_VI_960H2EX)
        					{
        						UartSendTrace("ch %d setted to 3840H %s\n", ch, vformat[ch]==PAL?"PAL":"NTSC");
        		 				SensorReg_Write( 0x81+ch%4, vformat[ch]==PAL?0x00:0x00);	
        		 				SensorReg_Write( 0x85+ch%4, vformat[ch]==PAL?0x11:0x11);
        		 				SensorReg_Write( 0x89+ch%4, vformat[ch]==PAL?0x10:0x10);
        		 				SensorReg_Write( ch%4+0x8E, vformat[ch]==PAL?0x22:0x22);
        					}
        					else
        					{
        						UartSendTrace("ch %d setted to 1920H %s\n", ch, vformat[ch]==PAL?"PAL":"NTSC");
        		 				SensorReg_Write( 0x81+ch%4, vformat[ch]==PAL?0x40:0x40);	
        		 				SensorReg_Write( 0x85+ch%4, vformat[ch]==PAL?0x11:0x11);
        		 				SensorReg_Write( 0x89+ch%4, vformat[ch]==PAL?0x00:0x00);
        		 				SensorReg_Write( ch%4+0x8E, vformat[ch]==PAL?0x10:0x10);
        					}	
        				}
        				else
        				{
        					if(chmode[ch]==NVP6124_VI_SD || chmode[ch]==NVP6124_VI_720H)
        					{
        		 				SensorReg_Write( 0x81+ch%4, vformat[ch]==PAL?0x00:0x00);	
        		 				SensorReg_Write( 0x85+ch%4, vformat[ch]==PAL?0x11:0x11);
        						if(chmode[ch]==NVP6124_VI_720H)
        						{
        							UartSendTrace("ch %d setted to 720H %s\n", ch, vformat[ch]==PAL?"PAL":"NTSC");
        		 					SensorReg_Write( 0x89+ch%4, vformat[ch]==PAL?0x11:0x11);
        		 					SensorReg_Write( ch%4+0x8E, vformat[ch]==PAL?0x20:0x00);
        						}
        						else
        						{
        							UartSendTrace("ch %d setted to 960H %s\n", ch, vformat[ch]==PAL?"PAL":"NTSC");
        		 					SensorReg_Write( 0x89+ch%4, vformat[ch]==PAL?0x10:0x00);
        		 					SensorReg_Write( ch%4+0x8E, vformat[ch]==PAL?0x08:0x07);
        						}	
        					}
        					else if(chmode[ch]==NVP6124_VI_1280H)
        					{
        						UartSendTrace("ch %d setted to 1280H %s\n", ch, vformat[ch]==PAL?"PAL":"NTSC");
        		 				SensorReg_Write( 0x81+ch%4, vformat[ch]==PAL?0x20:0x20);	
        		 				SensorReg_Write( 0x85+ch%4, vformat[ch]==PAL?0x00:0x00);
        		 				SensorReg_Write( 0x89+ch%4, vformat[ch]==PAL?0x10:0x10);
        		 				SensorReg_Write( ch%4+0x8E, vformat[ch]==PAL?0x17:0x17);
        					}
        					else if(chmode[ch]==NVP6124_VI_1440H)
        					{
        						UartSendTrace("ch %d setted to 1440H %s\n", ch, vformat[ch]==PAL?"PAL":"NTSC");
        		 				SensorReg_Write( 0x81+ch%4, vformat[ch]==PAL?0x30:0x30);	
        		 				SensorReg_Write( 0x85+ch%4, vformat[ch]==PAL?0x00:0x00);
        		 				SensorReg_Write( 0x89+ch%4, vformat[ch]==PAL?0x10:0x10);
        		 				SensorReg_Write( ch%4+0x8E, vformat[ch]==PAL?0x0B:0x0B);
        					}
        					else
        					{
        						UartSendTrace("ch %d setted to 1920H %s\n", ch, vformat[ch]==PAL?"PAL":"NTSC");
        		 				SensorReg_Write( 0x81+ch%4, vformat[ch]==PAL?0x40:0x40);	
        		 				SensorReg_Write( 0x85+ch%4, vformat[ch]==PAL?0x00:0x00);
        		 				SensorReg_Write( 0x89+ch%4, vformat[ch]==PAL?0x00:0x00);
        		 				SensorReg_Write( ch%4+0x8E, vformat[ch]==PAL?0x10:0x10);
        					}	
        				}
        				SensorReg_Write( 0x93+ch%4, 0x00);
        				SensorReg_Write( 0x98+ch%4, vformat[ch]==PAL?0x07:0x04);
        				if(chip_id == NVP6124B_R0_ID)
        				{
        					if(chmode[ch]==NVP6124_VI_960H2EX)
        	 					SensorReg_Write( 0xa0+ch%4, vformat[ch]==PAL?0x16:0x15);
        					else
        						SensorReg_Write( 0xa0+ch%4, vformat[ch]==PAL?0x15:0x15);
        					SensorReg_Write( 0xa4+ch%4, vformat[ch]==PAL?0x05:0x07);
        				}
        				else
        				{
         					SensorReg_Write( 0xa0+ch%4, vformat[ch]==PAL?0x00:0x10);
        					SensorReg_Write( 0xa4+ch%4, vformat[ch]==PAL?0x00:0x01);
        				}
        				SensorReg_Write( 0xFF, 0x01);
        				if(chip_id == NVP6124B_R0_ID)
        				{
        					if(chmode[ch]==NVP6124_VI_SD || chmode[ch]==NVP6124_VI_720H)
        					{
        						SensorReg_Write( 0x88+ch%4, vformat[ch]==PAL?0x06:0x06);
        						SensorReg_Write( 0x8c+ch%4, vformat[ch]==PAL?0xa6:0xa6);
        						SensorReg_Read(0xd7, &tmp);
        						SensorReg_Write(0xd7, tmp&(~(1<<(ch%4))));					
        					}
        					else if(chmode[ch]==NVP6124_VI_1280H)
        					{
        						SensorReg_Write( 0x88+ch%4, vformat[ch]==PAL?0x06:0x06);
        						SensorReg_Write( 0x8c+ch%4, vformat[ch]==PAL?0x26:0x26);
        						SensorReg_Read(0xd7, &tmp);
        						SensorReg_Write( 0xd7,tmp|(1<<(ch%4)));
        					
        					}
        					else if(chmode[ch]==NVP6124_VI_1440H)
        					{
        						SensorReg_Write( 0x88+ch%4, vformat[ch]==PAL?0x06:0x06);
        						SensorReg_Write( 0x8c+ch%4, vformat[ch]==PAL?0x26:0x26);
        						SensorReg_Read(0xd7, &tmp);
        						SensorReg_Write( 0xd7,tmp|(1<<(ch%4)));
        					}
        					else if(chmode[ch]==NVP6124_VI_960H2EX)
        					{
        						SensorReg_Write( 0x88+ch%4, vformat[ch]==PAL?0x06:0x06);
        						SensorReg_Write( 0x8c+ch%4, vformat[ch]==PAL?0x46:0x46);
        						SensorReg_Read(0xd7, &tmp);
        						SensorReg_Write( 0xd7,tmp|(1<<(ch%4)));
        					}
        					else
        					{
        						SensorReg_Write( 0x88+ch%4, vformat[ch]==PAL?0x06:0x06);
        						SensorReg_Write( 0x8c+ch%4, vformat[ch]==PAL?0x06:0x06);
        						SensorReg_Read(0xd7, &tmp);
        						SensorReg_Write( 0xd7,tmp|(1<<(ch%4)));
        					}
        				}
        				else
        				{		
        					if(chmode[ch]==NVP6124_VI_SD || chmode[ch]==NVP6124_VI_720H)
        					{
        						SensorReg_Write( 0x88+ch%4, vformat[ch]==PAL?0x7e:0x7e);
        						SensorReg_Write( 0x8c+ch%4, vformat[ch]==PAL?0x26:0x26);
        						SensorReg_Read(0xd7, &tmp);
        						SensorReg_Write( 0xd7, tmp&(~(1<<(ch%4))));
        					}
        					else if(chmode[ch]==NVP6124_VI_1280H)
        					{
        						SensorReg_Write( 0x88+ch%4, vformat[ch]==PAL?0x7e:0x7e);
        						SensorReg_Write( 0x8c+ch%4, vformat[ch]==PAL?0x56:0x56);
        						SensorReg_Read(0xd7, &tmp);
        						SensorReg_Write( 0xd7,tmp|(1<<(ch%4)));
        					}
        					else if(chmode[ch]==NVP6124_VI_1440H)
        					{
        						SensorReg_Write( 0x88+ch%4, vformat[ch]==PAL?0x7e:0x7e);
        						SensorReg_Write( 0x8c+ch%4, vformat[ch]==PAL?0x56:0x56);
        						SensorReg_Read(0xd7, &tmp);
        						SensorReg_Write( 0xd7,tmp|(1<<(ch%4)));
        					}
        					else //if(chmode[ch]==NVP6124_VI_1920H)
        					{
        						SensorReg_Write( 0x88+ch%4, vformat[ch]==PAL?0x46:0x46);
        						SensorReg_Write( 0x8c+ch%4, vformat[ch]==PAL?0x47:0x47);
        						SensorReg_Read(0xd7, &tmp);
        						SensorReg_Write( 0xd7,tmp|(1<<(ch%4)));
        					}	
        				}
        				SensorReg_Write( 0xFF, 0x02);  
        				SensorReg_Read(0x16+(ch%4)/2, &tmp);
        				SensorReg_Write( 0x16+(ch%4)/2, (tmp&(ch%2==0?0xF0:0x0F))|(0x00<<((ch%2)*4)));
        				SensorReg_Write( 0xFF, 0x05+ch%4);
        				nvp6124_write_table(handle, 0x00, NVP6124_B5678_SD_Buf, 254 );
        				SensorReg_Write( 0x06,0x40);
        				SensorReg_Write( 0x0F,vformat[ch]==PAL?0x13:0x00);
        				SensorReg_Write( 0x1B,0x08);
        				SensorReg_Write( 0x20,0x88);
        				SensorReg_Write( 0x1E,vformat[ch]==PAL?0x00:0x01);
        				SensorReg_Write( 0x2C,vformat[ch]==PAL?0x08:0x0C);
        				SensorReg_Write( 0x35,vformat[ch]==PAL?0x17:0x15);
        				if(chip_id == NVP6124B_R0_ID)
        					SensorReg_Write( 0x62,0x00);
        				else
        					SensorReg_Write( 0x62,vformat[ch]==PAL?0x20:0x00);
        				SensorReg_Write( 0xA1,vformat[ch]==PAL?0x10:0x30);
        				SensorReg_Write( 0xA2,vformat[ch]==PAL?0x0E:0x0C);
        				SensorReg_Write( 0xA3,vformat[ch]==PAL?0x70:0x50);
        				SensorReg_Write( 0xA8,vformat[ch]==PAL?0x40:0x20);
        				SensorReg_Write( 0xAC,vformat[ch]==PAL?0x10:0x20);
        				SensorReg_Write( 0xAD,vformat[ch]==PAL?0x08:0x20);
        				SensorReg_Write( 0xAE,vformat[ch]==PAL?0x04:0x14);
        				SensorReg_Write( 0xC0,vformat[ch]==PAL?0x0D:0x00);
        				SensorReg_Write( 0x25,vformat[ch]==PAL?0xCA:0xDA);
        				if(chmode[ch]==NVP6124_VI_1280H || chmode[ch]==NVP6124_VI_1440H)
        				{
        					SensorReg_Write( 0x62, vformat[ch]==PAL?0x20:0x20);
        					SensorReg_Write( 0x64, vformat[ch]==PAL?0x0D:0x0D);
        				}
        				else if(chmode[ch]==NVP6124_VI_960H2EX)
        				{
        					SensorReg_Write( 0x6B, 0x10);
        				}
        				SensorReg_Write( 0xFF, 0x09);
        				SensorReg_Write( 0x40+(ch%4), 0x60);
        				SensorReg_Read(0x44, &tmp);
        				SensorReg_Write( 0x44, tmp&(~(1<<(ch%4))));
        				SensorReg_Write( 0x50+4*(ch%4),vformat[ch]==PAL?pn_value_sd_pal_comet[0]:pn_value_sd_nt_comet[0]);	//ch%41 960H	
        				SensorReg_Write( 0x51+4*(ch%4),vformat[ch]==PAL?pn_value_sd_pal_comet[1]:pn_value_sd_nt_comet[1]);		
        				SensorReg_Write( 0x52+4*(ch%4),vformat[ch]==PAL?pn_value_sd_pal_comet[2]:pn_value_sd_nt_comet[2]);		
        				SensorReg_Write( 0x53+4*(ch%4),vformat[ch]==PAL?pn_value_sd_pal_comet[3]:pn_value_sd_nt_comet[3]);
        			break;	
        			case NVP6124_VI_720P_2530:
        			case NVP6124_VI_HDEX:	
        				SensorReg_Write( 0xFF, 0x00);
        				SensorReg_Write( 0x08+ch%4,vformat[ch]==PAL?0x60:0x60);
        				SensorReg_Write( 0x0c+ch%4,nvp6124_bri_tbl_720P[vformat[ch]%2]);
        				SensorReg_Write( 0x10+ch%4,nvp6124_con_tbl_720P[vformat[ch]%2]);
        				SensorReg_Write( 0x14+ch%4,vformat[ch]==PAL?0x90:0x90);
        				SensorReg_Write( 0x18+ch%4,vformat[ch]==PAL?0x30:0x30);
        				SensorReg_Write( 0x21+4*(ch%4), 0x92);
        				SensorReg_Write( 0x22+4*(ch%4), 0x0A);
        				SensorReg_Write( 0x23+4*(ch%4), 0x43);
        				if(chip_id == NVP6124B_R0_ID)
        					SensorReg_Write( 0x30+ch%4,0x15);
        				else
        					SensorReg_Write( 0x30+ch%4,0x12);
        				SensorReg_Write( 0x3c+ch%4,nvp6124_sat_tbl_720P[vformat[ch]%2]);
        				SensorReg_Write( 0x40+ch%4,nvp6124_hue_tbl_720P[vformat[ch]%2]);
        				SensorReg_Write( 0x44+ch%4,vformat[ch]==PAL?0x30:0x30);
        				SensorReg_Write( 0x48+ch%4,vformat[ch]==PAL?0x30:0x30);
        				SensorReg_Write( 0x4c+ch%4,vformat[ch]==PAL?0x04:0x04);
        				SensorReg_Write( 0x50+ch%4,vformat[ch]==PAL?0x04:0x04);
        				//nvp6124_set_fpc(handle, ch, vformat[ch]);
        				SensorReg_Read(0x54, &tmp);
                            	if(vformat[ch]==PAL)
                            		tmp &= ~(0x10<<(ch%4));
                            	else	
                            		tmp |= (0x10<<(ch%4));
                            	SensorReg_Write(0x54, tmp);
        				SensorReg_Write( 0x58+ch%4,vformat[ch]==PAL?0x80:0x90);
        				SensorReg_Write( 0x5c+ch%4,vformat[ch]==PAL?0x9e:0x9e);
        				SensorReg_Write( 0x64+ch%4,vformat[ch]==PAL?0xb1:0xb2);
        				SensorReg_Write( 0x81+ch%4,vformat[ch]==PAL?0x07:0x06);	
        				SensorReg_Write( 0x85+ch%4,vformat[ch]==PAL?0x00:0x00);
        				SensorReg_Write( 0x89+ch%4,vformat[ch]==PAL?0x10:0x10);
        				if(chip_id == NVP6124B_R0_ID)
        				{	
        					if(chmode[ch] == NVP6124_VI_HDEX)
        						SensorReg_Write( ch%4+0x8E,0x07);
        					else
        						SensorReg_Write( ch%4+0x8E,0x0d);
        				}
        				else
        					SensorReg_Write( ch%4+0x8E,vformat[ch]==PAL?0x0d:0x0d);
        				SensorReg_Write( 0x93+ch%4,0x00);
        				SensorReg_Write( 0x98+ch%4,vformat[ch]==PAL?0x07:0x04);
        				if(chip_id == NVP6124B_R0_ID)
        					SensorReg_Write( 0xa0+ch%4,0x15);
        				else
        					SensorReg_Write( 0xa0+ch%4,0x00);
        				SensorReg_Write( 0xa4+ch%4,vformat[ch]==PAL?0x00:0x01);
        				SensorReg_Write( 0xFF,0x01);

        				if(chip_id == NVP6124B_R0_ID)
        				{
        					SensorReg_Write( 0x88+ch%4, vformat[ch]==PAL?0x0A:0x0A);

        					if(chmode[ch] == NVP6124_VI_HDEX)
        					{
        						UartSendTrace("ch %d setted to HDEX(2560x720) %s\n", ch, vformat[ch]==PAL?"PAL":"NTSC");
        						SensorReg_Write( 0x8c+ch%4, vformat[ch]==PAL?0x4A:0x5A);
        					}
        					else
        					{
        						UartSendTrace("ch %d setted to 720P %s\n", ch, vformat[ch]==PAL?"PAL":"NTSC");
        						SensorReg_Write( 0x8c+ch%4, vformat[ch]==PAL?0x0A:0x0A);
        					}
        										 		
        					SensorReg_Write( 0x9E, vformat[ch]==PAL?0x55:0x55);						 		
        				}
        				else
        				{
        					SensorReg_Write( 0x88+ch%4,vformat[ch]==PAL?0x5C:0x5C);	
        					SensorReg_Write( 0x8c+ch%4,vformat[ch]==PAL?0x40:0x40);					
        				}
        				SensorReg_Read(0xd7, &tmp);
        				SensorReg_Write( 0xd7,tmp|(1<<(ch%4)));
        				SensorReg_Write( 0xFF, 0x02);  
        				SensorReg_Read(0x16+(ch%4)/2, &tmp);
        				SensorReg_Write( 0x16+(ch%4)/2, (tmp&(ch%2==0?0xF0:0x0F))|(0x05<<((ch%2)*4)));
        				SensorReg_Write( 0xFF, 0x05+ch%4);
        				nvp6124_write_table(handle, 0x00, NVP6124_B5678_Buf,254 );
        				SensorReg_Write( 0x01,0x0D); 
        				SensorReg_Write( 0x06,0x40);
        				SensorReg_Write( 0x1E,vformat[ch]==PAL?0x00:0x01);
        				SensorReg_Write( 0x35,vformat[ch]==PAL?0x17:0x15);
        				SensorReg_Write( 0x7A,vformat[ch]==PAL?0x00:0x01);
        				SensorReg_Write( 0x7B,vformat[ch]==PAL?0x00:0x81);
        				SensorReg_Write( 0xA1,vformat[ch]==PAL?0x10:0x30);
        				SensorReg_Write( 0xA2,vformat[ch]==PAL?0x0E:0x0C);
        				SensorReg_Write( 0xA3,vformat[ch]==PAL?0x70:0x50);
        				SensorReg_Write( 0xA8,vformat[ch]==PAL?0x40:0x20);
        				SensorReg_Write( 0xAC,vformat[ch]==PAL?0x10:0x20);
        				SensorReg_Write( 0xAD,vformat[ch]==PAL?0x08:0x20);
        				SensorReg_Write( 0xAE,vformat[ch]==PAL?0x04:0x14);
        				SensorReg_Write( 0x25,0xDB);
        				SensorReg_Write( 0x2B,0x78); 
        				SensorReg_Write( 0x59,0x00);
        				SensorReg_Write( 0x58,0x13);
        				if(chmode[ch] == NVP6124_VI_HDEX)
        				{
        					SensorReg_Write( 0x54, 0x20);
        					SensorReg_Write( 0x55, 0x11);
        					SensorReg_Write( 0x6B, 0x01);
        				}
        				SensorReg_Write( 0xC0,0x16);
        				if(chip_id == NVP6124B_R0_ID)
        				{
        					SensorReg_Write( 0xC1, 0x13);
        					SensorReg_Write( 0xC8, 0x04);
        				}
        				else
        					SensorReg_Write( 0xC1,0x14);
        				SensorReg_Write( 0xD8,0x0C);    
        				SensorReg_Write( 0xD9,0x0E); 
        				SensorReg_Write( 0xDA,0x12);    
        				SensorReg_Write( 0xDB,0x14); 
        				SensorReg_Write( 0xDC,0x1C);    
        				SensorReg_Write( 0xDD,0x2C);
        				SensorReg_Write( 0xDE,0x34);
        				
        				SensorReg_Write( 0xFF, 0x09);
        				SensorReg_Write( 0x40+(ch%4),0x00);
        				if(chip_id == NVP6124B_R0_ID)
        					SensorReg_Write( 0x44, 0x00);
        				else{
        				      SensorReg_Read(0x44, &tmp);
        					SensorReg_Write( 0x44, tmp|(1<<(ch%4)));
        				}
        				SensorReg_Write( 0x50+4*(ch%4),vformat[ch]==PAL?pn_value_720p_25[0]:pn_value_720p_30[0]);	//ch%41 960H	
        				SensorReg_Write( 0x51+4*(ch%4),vformat[ch]==PAL?pn_value_720p_25[1]:pn_value_720p_30[1]);		
        				SensorReg_Write( 0x52+4*(ch%4),vformat[ch]==PAL?pn_value_720p_25[2]:pn_value_720p_30[2]);		
        				SensorReg_Write( 0x53+4*(ch%4),vformat[ch]==PAL?pn_value_720p_25[3]:pn_value_720p_30[3]);					
        			break;
        			case NVP6124_VI_720P_5060:
        				SensorReg_Write( 0xFF, 0x00);
        				SensorReg_Write( 0x08+ch%4,vformat[ch]==PAL?0x60:0x60);
        				SensorReg_Write( 0x0c+ch%4,nvp6124_bri_tbl_720P[vformat[ch]%2]);
        				SensorReg_Write( 0x10+ch%4,nvp6124_con_tbl_720P[vformat[ch]%2]);
        				SensorReg_Write( 0x14+ch%4,vformat[ch]==PAL?0x90:0x90);
        				SensorReg_Write( 0x18+ch%4,vformat[ch]==PAL?0x00:0x00);
        				SensorReg_Write( 0x21+4*(ch%4), 0x92);
        				SensorReg_Write( 0x22+4*(ch%4), 0x0A);
        				SensorReg_Write( 0x23+4*(ch%4), vformat[ch]==PAL?0x43:0x43);
        				SensorReg_Write( 0x30+ch%4,vformat[ch]==PAL?0x12:0x12);
        				SensorReg_Write( 0x3c+ch%4,nvp6124_sat_tbl_720P[vformat[ch]%2]);
        				SensorReg_Write( 0x40+ch%4,nvp6124_hue_tbl_720P[vformat[ch]%2]);
        				SensorReg_Write( 0x44+ch%4,vformat[ch]==PAL?0x30:0x30);
        				SensorReg_Write( 0x48+ch%4,vformat[ch]==PAL?0x30:0x30);
        				SensorReg_Write( 0x4c+ch%4,vformat[ch]==PAL?0x04:0x04);
        				SensorReg_Write( 0x50+ch%4,vformat[ch]==PAL?0x04:0x04);
        				//nvp6124_set_fpc(handle, ch, vformat[ch]);
        				SensorReg_Read(0x54, &tmp);
                            	if(vformat[ch]==PAL)
                            		tmp &= ~(0x10<<(ch%4));
                            	else	
                            		tmp |= (0x10<<(ch%4));
                            	SensorReg_Write(0x54, tmp);
        				SensorReg_Write( 0x58+ch%4,vformat[ch]==PAL?0xc0:0xb0);
        				SensorReg_Write( 0x5c+ch%4,vformat[ch]==PAL?0x9e:0x9e);
        				SensorReg_Write( 0x64+ch%4,vformat[ch]==PAL?0xb1:0xb2);
        				SensorReg_Write( 0x81+ch%4,vformat[ch]==PAL?0x05:0x04);
        				SensorReg_Write( 0x85+ch%4,vformat[ch]==PAL?0x00:0x00);
        				SensorReg_Write( 0x89+ch%4,vformat[ch]==PAL?0x10:0x10);
        				SensorReg_Write( ch%4+0x8E,vformat[ch]==PAL?0x0b:0x09);
        				SensorReg_Write( 0x93+ch%4,0x00);
        				SensorReg_Write( 0x98+ch%4,vformat[ch]==PAL?0x07:0x04);
        				SensorReg_Write( 0xa0+ch%4,vformat[ch]==PAL?0x00:0x00);
        				SensorReg_Write( 0xa4+ch%4,vformat[ch]==PAL?0x00:0x01);
        				SensorReg_Write( 0xFF, 0x01);
        				if(chip_id == NVP6124B_R0_ID)
        				{
        					SensorReg_Write( 0x88+ch%4,vformat[ch]==PAL?0x00:0x00);	
        					SensorReg_Write( 0x8c+ch%4,vformat[ch]==PAL?0x42:0x42);
        				}
        				else
        				{
        					SensorReg_Write( 0x88+ch%4,vformat[ch]==PAL?0x4d:0x4d);	
        					SensorReg_Write( 0x8c+ch%4,vformat[ch]==PAL?0x84:0x84);	
        				}
        				SensorReg_Read(0xd7, &tmp);
        				SensorReg_Write( 0xd7, tmp|(1<<(ch%4)));
        				SensorReg_Write( 0xFF, 0x02); 
        				SensorReg_Read(0x16+(ch%4)/2, &tmp);
        				SensorReg_Write( 0x16+(ch%4)/2, (tmp&(ch%2==0?0xF0:0x0F))|(0x05<<((ch%2)*4)));
        				SensorReg_Write( 0xFF, 0x05+ch%4);
        				nvp6124_write_table(handle, 0x00, NVP6124_B5678_Buf,254 );
        				SensorReg_Write( 0x01,0x0C);
        				SensorReg_Write( 0x06,0x40);
        				SensorReg_Write( 0x1E,vformat[ch]==PAL?0x00:0x01);
        				SensorReg_Write( 0x35,vformat[ch]==PAL?0x17:0x15);
        				SensorReg_Write( 0x7A,vformat[ch]==PAL?0x00:0x01);
        				SensorReg_Write( 0x7B,vformat[ch]==PAL?0x00:0x81);
        				SensorReg_Write( 0xA1,vformat[ch]==PAL?0x10:0x30);
        				SensorReg_Write( 0xA2,vformat[ch]==PAL?0x0E:0x0C);
        				SensorReg_Write( 0xA3,vformat[ch]==PAL?0x70:0x50);
        				SensorReg_Write( 0xA8,vformat[ch]==PAL?0x40:0x20);
        				SensorReg_Write( 0xAC,vformat[ch]==PAL?0x10:0x20);
        				SensorReg_Write( 0xAD,vformat[ch]==PAL?0x08:0x20);
        				SensorReg_Write( 0xAE,vformat[ch]==PAL?0x04:0x14);
        				SensorReg_Write( 0x2B,0x78); 
        				SensorReg_Write( 0x58,0x13);
        				SensorReg_Write( 0x59,0x01);  
        				SensorReg_Write( 0x24,vformat[ch]==PAL?0x2A:0x1A);  
        				SensorReg_Write( 0x50,vformat[ch]==PAL?0x84:0x86);
        				SensorReg_Write( 0xBB,vformat[ch]==PAL?0x00:0xE4);
        				SensorReg_Write( 0xD8,0x0C);    
        				SensorReg_Write( 0xD9,0x0E); 
        				SensorReg_Write( 0xDA,0x12);    
        				SensorReg_Write( 0xDB,0x14); 
        				SensorReg_Write( 0xDC,0x1C);    
        				SensorReg_Write( 0xDD,0x2C);
        				SensorReg_Write( 0xDE,0x34);
        				SensorReg_Write( 0xFF,0x09);
        				SensorReg_Write( 0x40+(ch%4), 0x00);
        				if(chip_id == NVP6124B_R0_ID)
        					SensorReg_Write( 0x44, 0x00);
        				else	{
        				      SensorReg_Read(0x44, &tmp);
        					SensorReg_Write( 0x44, tmp|(1<<(ch%4)));
        				}
        				SensorReg_Write( 0x50+4*(ch%4),vformat[ch]==PAL?pn_value_720p_50[0]:pn_value_720p_60[0]);	//ch%41 960H	
        				SensorReg_Write( 0x51+4*(ch%4),vformat[ch]==PAL?pn_value_720p_50[1]:pn_value_720p_60[1]);		
        				SensorReg_Write( 0x52+4*(ch%4),vformat[ch]==PAL?pn_value_720p_50[2]:pn_value_720p_60[2]);		
        				SensorReg_Write( 0x53+4*(ch%4),vformat[ch]==PAL?pn_value_720p_50[3]:pn_value_720p_60[3]);
        				UartSendTrace("ch %d setted to 720P@RT %s\n", ch, vformat[ch]==PAL?"PAL":"NTSC");
        			break;		
        			case NVP6124_VI_1080P_2530:
        				SensorReg_Write( 0xFF, 0x00);
        				SensorReg_Write( 0x08+ch%4,vformat[ch]==PAL?0x60:0x60);
        				SensorReg_Write( 0x0c+ch%4,nvp6124_bri_tbl[vformat[ch]%2]);
        				SensorReg_Write( 0x10+ch%4,nvp6124_con_tbl[vformat[ch]%2]);
        				SensorReg_Write( 0x14+ch%4,vformat[ch]==PAL?0x90:0x90);
        				SensorReg_Write( 0x18+ch%4,vformat[ch]==PAL?0x00:0x00);
        				SensorReg_Write( 0x21+4*(ch%4), 0x92);
        				if(chip_id == NVP6124B_R0_ID)
        					SensorReg_Write( 0x22+4*(ch%4), 0x0B);
        				else
        					SensorReg_Write( 0x22+4*(ch%4), 0x0A);
        				SensorReg_Write( 0x23+4*(ch%4), vformat[ch]==PAL?0x43:0x43);
        				if(chip_id == NVP6124B_R0_ID)
        					SensorReg_Write( 0x30+ch%4,0x15);
        				else
        					SensorReg_Write( 0x30+ch%4,0x12);
        				SensorReg_Write( 0x3c+ch%4,nvp6124_sat_tbl[vformat[ch]%2]);
        				SensorReg_Write( 0x40+ch%4,nvp6124_hue_tbl[vformat[ch]%2]);
        				SensorReg_Write( 0x44+ch%4,vformat[ch]==PAL?0x00:0x00);
        				SensorReg_Write( 0x48+ch%4,vformat[ch]==PAL?0x00:0x00);
        				SensorReg_Write( 0x4c+ch%4,vformat[ch]==PAL?0x00:0x00);
        				SensorReg_Write( 0x50+ch%4,vformat[ch]==PAL?0x00:0x00);
        				//nvp6124_set_fpc(handle, ch, vformat[ch]);
        				SensorReg_Read(0x54, &tmp);
                            	if(vformat[ch]==PAL)
                            		tmp &= ~(0x10<<(ch%4));
                            	else	
                            		tmp |= (0x10<<(ch%4));
                            	SensorReg_Write(0x54, tmp);
        				if(chip_id == NVP6124B_R0_ID)
        					SensorReg_Write( 0x58+ch%4,vformat[ch]==PAL?0x78:0x57);
        				else
        					SensorReg_Write( 0x58+ch%4,vformat[ch]==PAL?0x6a:0x49);
        				SensorReg_Write( 0x5c+ch%4,vformat[ch]==PAL?0x9e:0x9e);
        				SensorReg_Write( 0x64+ch%4,vformat[ch]==PAL?0xbf:0x8d);
        				SensorReg_Write( 0x81+ch%4,vformat[ch]==PAL?0x03:0x02);
        				SensorReg_Write( 0x85+ch%4,vformat[ch]==PAL?0x00:0x00);
        				SensorReg_Write( 0x89+ch%4,vformat[ch]==PAL?0x10:0x10);
        				SensorReg_Write( ch%4+0x8E,vformat[ch]==PAL?0x0a:0x09);
        				SensorReg_Write( 0x93+ch%4,0x00);
        				SensorReg_Write( 0x98+ch%4,vformat[ch]==PAL?0x07:0x04);
        				if(chip_id == NVP6124B_R0_ID)
        					SensorReg_Write( 0xa0+ch%4,0x15);	
        				else
        					SensorReg_Write( 0xa0+ch%4,0x00);	
        				SensorReg_Write( 0xa4+ch%4,vformat[ch]==PAL?0x00:0x01);
        				SensorReg_Write( 0xFF, 0x01);
        				
        				if(chip_id == NVP6124B_R0_ID)
        				{
        					SensorReg_Write( 0x88+ch%4, vformat[ch]==PAL?0x00:0x00);//NVP6124A NYH	
        					SensorReg_Write( 0x8c+ch%4, vformat[ch]==PAL?0x42:0x42);
        				}
        				else
        				{
        					SensorReg_Write( 0x88+ch%4,vformat[ch]==PAL?0x4c:0x4c);	
        					SensorReg_Write( 0x8c+ch%4,vformat[ch]==PAL?0x84:0x84);							 		
        				}
        				SensorReg_Read(0xd7, &tmp);
        				SensorReg_Write( 0xd7, tmp|(1<<(ch%4)));
        				SensorReg_Write( 0xFF, 0x02);  
        				SensorReg_Read(0x16+(ch%4)/2, &tmp);
        				SensorReg_Write( 0x16+(ch%4)/2, (tmp&(ch%2==0?0xF0:0x0F))|(0x05<<((ch%2)*4)));
        				SensorReg_Write( 0xFF, 0x05+ch%4);
        				nvp6124_write_table(handle, 0x00, NVP6124_B5678_Buf,254 );
        				SensorReg_Write( 0x01,0x0C);
        				SensorReg_Write( 0x06,0x40);
        				SensorReg_Write( 0x1E,vformat[ch]==PAL?0x00:0x01);
        				SensorReg_Write( 0x35,vformat[ch]==PAL?0x17:0x15);
        				SensorReg_Write( 0x7A,vformat[ch]==PAL?0x00:0x01);
        				SensorReg_Write( 0x7B,vformat[ch]==PAL?0x00:0x81);
        				SensorReg_Write( 0xA1,vformat[ch]==PAL?0x10:0x30);
        				SensorReg_Write( 0xA2,vformat[ch]==PAL?0x0E:0x0C);
        				SensorReg_Write( 0xA3,vformat[ch]==PAL?0x70:0x50);
        				SensorReg_Write( 0xA8,vformat[ch]==PAL?0x40:0x20);
        				SensorReg_Write( 0xAC,vformat[ch]==PAL?0x10:0x20);
        				SensorReg_Write( 0xAD,vformat[ch]==PAL?0x08:0x20);
        				SensorReg_Write( 0xAE,vformat[ch]==PAL?0x04:0x14);
        				SensorReg_Write( 0x2A,0x72);
        				SensorReg_Write( 0x2B,0xA8); 
        				SensorReg_Write( 0x58,0x13);
        				SensorReg_Write( 0x59,0x01);
        				if(chip_id == NVP6124B_R0_ID)
        				{
        					SensorReg_Write( 0xC0, 0x16); 
        					SensorReg_Write( 0xC1, 0x13);
        					SensorReg_Write( 0xC8, 0x04); 
        					SensorReg_Write( 0x47, 0xEE); 
        					SensorReg_Write( 0x50, 0xC4); 
        				}
        				else
        				{
        					SensorReg_Write( 0xC0,0x17);
        					SensorReg_Write( 0xC1,0x14);
        				}
        				SensorReg_Write( 0xD8,0x10);    
        				SensorReg_Write( 0xD9,0x1F); 
        				SensorReg_Write( 0xDA,0x2B);    
        				SensorReg_Write( 0xDB,0x7F); 
        				SensorReg_Write( 0xDC,0xFF);    
        				SensorReg_Write( 0xDD,0xFF);
        				SensorReg_Write( 0xDE,0xFF);
        				
        				SensorReg_Write( 0x24,vformat[ch]==PAL?0x2A:0x1A);  
        				SensorReg_Write( 0x50,vformat[ch]==PAL?0x84:0x86);
        				SensorReg_Write( 0xBB,vformat[ch]==PAL?0x00:0xE4);
        				SensorReg_Write( 0xFF, 0x09);
        				SensorReg_Write( 0x40+(ch%4), 0x00);
        				if(chip_id == NVP6124B_R0_ID)
        					SensorReg_Write( 0x44, 0x00);
        				else	{
        				      SensorReg_Read(0x44, &tmp);
        					SensorReg_Write( 0x44,tmp|(1<<(ch%4)));
        				}
        				SensorReg_Write( 0x50+4*(ch%4),vformat[ch]==PAL?pn_value_fhd_pal[0]:pn_value_fhd_nt[0]);		
        				SensorReg_Write( 0x51+4*(ch%4),vformat[ch]==PAL?pn_value_fhd_pal[1]:pn_value_fhd_nt[1]);		
        				SensorReg_Write( 0x52+4*(ch%4),vformat[ch]==PAL?pn_value_fhd_pal[2]:pn_value_fhd_nt[2]);		
        				SensorReg_Write( 0x53+4*(ch%4),vformat[ch]==PAL?pn_value_fhd_pal[3]:pn_value_fhd_nt[3]);					
        				UartSendTrace("ch %d setted to 1080P %s\n", ch, vformat[ch]==PAL?"PAL":"NTSC");
        			break;
        			default:
        				UartSendTrace("ch%d wrong mode detected!!!\n", ch);
        				break;
        		}						
        		ch_mode_status[ch] = chmode[ch];
        		ch_vfmt_status[ch] = vformat[ch];
        		if(chip_id == NVP6124B_R0_ID)
        		{
        			nvp6124b_syncchange(handle, ch, pvmode);
        			//TODO
        			SensorReg_Write( 0xFF, 0x09);
        			SensorReg_Write( 0x64, 0x18);
        			SensorReg_Write( 0x65, 0xC2);
        			SensorReg_Write( 0x66, 0x01);
        			SensorReg_Write( 0x67, 0x1E);
        			SensorReg_Write( 0x68, 0x02);
        			SensorReg_Write( 0x69, 0x64);
        			SensorReg_Write( 0x6A, 0x60);
        			SensorReg_Write( 0x6B, 0x3C);
        		}
        		//init_acp(ch);
        		acp_each_setting(handle, ch);
        	}	
        }
}

int nvp6124_set_chnmode(ms_cus_sensor *handle, unsigned char ch, unsigned char vfmt, unsigned char chnmode)
{
	nvp6124_video_mode vmode;
	int i;

	if((ch >= nvp6124_cnt) || chnmode >= NVP6124_VI_BUTT)
	{
		UartSendTrace("channel/mode is out of range\n");
		return FAIL;
	}

	for(i=0;i<nvp6124_cnt;i++)
	{
		if(ch == i)
		{
			vmode.vformat[i] = vfmt;
			vmode.chmode[i] = chnmode;
		}
		else
			vmode.chmode[i] = NVP6124_VI_BUTT;
	}
	nvp6124_each_mode_setting(handle, &vmode);
	return SUCCESS;
}

/*
chip:chip select[0,1,2,3];
portsel: port select[0,1];
portmode: port mode select[1mux,2mux,4mux]
chid:  channel id, 1mux[0,1,2,3], 2mux[0,1], 4mux[0]
NOTE: 
portsel == 0,对应芯片硬件VDO1,寄存器描述VPORT_2;
portsel == 1,对应芯片硬件VDO2,寄存器描述VPORT_1;
*/
int nvp6124b_set_portmode(ms_cus_sensor *handle, unsigned char portsel, unsigned char portmode, unsigned char chid)
{
	unsigned char tmp=0, reg1=0, reg2=0;
	
	if(portsel>1)
	{
		UartSendTrace("nvp6124b_set_portmode portsel[%d] error!!!\n", portsel);
		return -1;
	}

	//portsel = portsel^1;	//port switch
	
	switch(portmode)
	{
		case NVP6124_OUTMODE_1MUX_SD:
			/*输出720H或者960H单通道,数据37.125MHz,时钟37.125MHz,单沿采样.*/
			SensorReg_Write( 0xFF, 0x00);
			SensorReg_Write( 0x56, 0x10);
			SensorReg_Write( 0xFF, 0x01);
			SensorReg_Write( 0x90+portsel, 0x03);
			SensorReg_Write( 0x92+portsel, 0x03);
			SensorReg_Write( 0xA0+chid, 0x00);
			SensorReg_Write( 0xC0+portsel*2, (chid<<4)|chid); 
			SensorReg_Read(0xC8, &tmp);
			tmp = tmp & (portsel%2?0x0F:0xF0);
			SensorReg_Write( 0xC8, tmp);
			SensorReg_Write( 0xC8+portsel, 0x00);
			SensorReg_Write( 0xCF-(portsel<<1), 0x86);			
		break;
		case NVP6124_OUTMODE_1MUX_HD:
			/*输出720P或者1280H或者1440H单通道,数据74.25MHz,时钟74.25MHz,单沿采样.*/
			SensorReg_Write( 0xFF, 0x00);
			SensorReg_Write( 0x56, 0x10);
			SensorReg_Write( 0xFF, 0x01);
			SensorReg_Write( 0x90+portsel, 0x01);
			SensorReg_Write( 0x92+portsel, 0x01);
			SensorReg_Write( 0xA0+chid, 0x00);
			SensorReg_Write( 0xC0+portsel*2, (chid<<4)|chid);
			SensorReg_Read(0xC8, &tmp);
			tmp = tmp & (portsel%2?0x0F:0xF0);
			SensorReg_Write( 0xC8, tmp);
			SensorReg_Write( 0xCF-(portsel<<1), 0x16);   
		break;
		case NVP6124_OUTMODE_1MUX_HD5060:
		case NVP6124_OUTMODE_1MUX_FHD:	
			/*输出720P@5060或者1080P单通道,数据148.5MHz,时钟148.5MHz,单沿采样.*/
			SensorReg_Write( 0xFF, 0x00);
			SensorReg_Write( 0x56, 0x10);
			SensorReg_Write( 0xFF, 0x01);
			SensorReg_Write( 0x90+portsel, 0x01);
			SensorReg_Write( 0x92+portsel, 0x01);
			SensorReg_Write( 0xA0+chid, 0x01);
			SensorReg_Write( 0xC0+portsel*2, (chid<<4)|chid);    
			SensorReg_Read(0xC8, &tmp);
			tmp = tmp & (portsel%2?0x0F:0xF0);
			SensorReg_Write( 0xC8, tmp);
			SensorReg_Write( 0xCF-(portsel<<1), 0x47);//0x43);
			break;
		case NVP6124_OUTMODE_2MUX_SD:
			/*输出720H或者960H 2通道,数据74.25MHz,时钟74.25MHz,单沿采样.*/
			SensorReg_Write( 0xFF, 0x00);
			SensorReg_Write( 0x56, 0x10);
			SensorReg_Read(0xFD, &reg1);
			SensorReg_Read(0xFE, &reg2);
			SensorReg_Write( 0xFF, 0x01);
			SensorReg_Write( 0x90+portsel, 0x02);
			SensorReg_Write( 0x92+portsel, 0x02);
			SensorReg_Write( 0xA0+chid*2, 0x00);
			SensorReg_Write( 0xA1+chid*2, 0x00);
			SensorReg_Write( 0xC0+portsel*2, chid==0?0x10:0x32);   
			SensorReg_Read(0xC8, &tmp);
			tmp = tmp & (portsel%2?0x0F:0xF0);
			tmp |= (portsel%2?0x20:0x02);
			SensorReg_Write( 0xC8, tmp);
			//SensorReg_Write( 0xCF-(portsel<<1), 0x16);
			if(portsel==0)
				SensorReg_Write( 0xCF, 0x1A);
			else
				SensorReg_Write( 0xCD, 0x16);
			break;
		case NVP6124_OUTMODE_2MUX_HD_X:
			/*输出HD-X 2通道,数据74.25MHz,时钟74.25MHz,单沿采样.*/
			SensorReg_Write( 0xFF, 0x00);
			SensorReg_Write( 0x56, 0x10);
			SensorReg_Write( 0xFF, 0x01);
			SensorReg_Write( 0x90+portsel, 0x00);
			SensorReg_Write( 0x92+portsel, 0x00);
			SensorReg_Write( 0xA0+chid*2, 0x00);
			SensorReg_Write( 0xA1+chid*2, 0x00);
			SensorReg_Write( 0xC0+portsel*2, chid==0?0x98:0xBA);
			SensorReg_Read(0xC8, &tmp);
			tmp = tmp & (portsel%2?0x0F:0xF0);
			tmp |= (portsel%2?0x20:0x02);
			SensorReg_Write( 0xC8, tmp);
			SensorReg_Write( 0xCF-(portsel<<1), 0x16);
			break;
		case NVP6124_OUTMODE_2MUX_FHD_X:	
			/*输出FHD-X 2通道,数据148.5MHz,时钟148.5MHz,单沿采样.*/
			SensorReg_Write( 0xFF, 0x00);
			SensorReg_Write( 0x56, 0x10);
			SensorReg_Write( 0xFF, 0x01);
			SensorReg_Write( 0x90+portsel, 0x01);
			SensorReg_Write( 0x92+portsel, 0x01);
			SensorReg_Write( 0xA0+chid*2, 0x01);
			SensorReg_Write( 0xA1+chid*2, 0x01);
			SensorReg_Write( 0xC0+portsel*2, chid==0?0x10:0x32);    
			SensorReg_Read(0xC8, &tmp);
			tmp = tmp & (portsel%2?0x0F:0xF0);
			tmp |= (portsel%2?0x10:0x01);
			SensorReg_Write( 0xC8, tmp);
			SensorReg_Write( 0xCF-(portsel<<1), 0x43);
			break;
		case NVP6124_OUTMODE_2MUX_HD:
			/*输出HD 2通道,数据148.5MHz,时钟148.5MHz,单沿采样.*/
			SensorReg_Write( 0xFF, 0x00);
			SensorReg_Write( 0x56, 0x10);
			SensorReg_Write( 0xFF, 0x01);
			SensorReg_Write( 0x90+portsel, 0x03);
			SensorReg_Write( 0x92+portsel, 0x03);
			SensorReg_Write( 0xA0+chid*2, 0x03);
			SensorReg_Write( 0xA1+chid*2, 0x03);
			SensorReg_Write( 0xC0+portsel*2, chid==0?0x10:0x32);  
			SensorReg_Read(0xC8, &tmp);
			tmp = tmp & (portsel%2?0x0F:0xF0);
			tmp |= (portsel%2?0x20:0x02);
			SensorReg_Write( 0xC8, tmp);
			SensorReg_Write( 0xCF-(portsel<<1), 0x43);			
			break;
		case NVP6124_OUTMODE_4MUX_SD:
			/*输出720H或者960H 4通道,数据148.5MHz,时钟148.5MHz,单沿采样.*/
			SensorReg_Write( 0xFF, 0x00);
			SensorReg_Write( 0x56, 0x32);
			SensorReg_Write( 0xFF, 0x01);
			SensorReg_Write( 0x90+portsel, 0x03);
			SensorReg_Write( 0x92+portsel, 0x03);
			SensorReg_Write( 0xA0, 0x03);
			SensorReg_Write( 0xA1, 0x03);
			SensorReg_Write( 0xA2, 0x03);
			SensorReg_Write( 0xA3, 0x03);
			SensorReg_Write( 0xC0+portsel*2, 0x10);    
			SensorReg_Write( 0xC1+portsel*2, 0x32);
			SensorReg_Read(0xC8, &tmp);
			tmp = tmp & (portsel%2?0x0F:0xF0);
			tmp |= (portsel%2?0x80:0x08);
			SensorReg_Write( 0xC8, tmp);
			SensorReg_Write( 0xCF-(portsel<<1), 0x43);  
			break;
		case NVP6124_OUTMODE_4MUX_HD:	
			/*输出720P 4通道,数据297MHz,时钟148.5MHz,双沿采样.*/
			SensorReg_Write( 0xFF, 0x00);
			SensorReg_Write( 0x56, 0x32);
			SensorReg_Write( 0xFF, 0x01);
			SensorReg_Write( 0x90+portsel, 0x00);
			SensorReg_Write( 0x92+portsel, 0x00);
			SensorReg_Write( 0xA0, 0x00);
			SensorReg_Write( 0xA1, 0x00);
			SensorReg_Write( 0xA2, 0x00);
			SensorReg_Write( 0xA3, 0x00);
			SensorReg_Write( 0xC0+portsel*2, 0x10);    
			SensorReg_Write( 0xC1+portsel*2, 0x32);
			SensorReg_Read(0xC8, &tmp);
			tmp = tmp & (portsel%2?0x0F:0xF0);
			tmp |= (portsel%2?0x80:0x08);
			SensorReg_Write( 0xC8, tmp);
			SensorReg_Write( 0xCF-(portsel<<1), 0x43);  
			break;
		case NVP6124_OUTMODE_4MUX_HD_X:
			/*输出HD-X 4通道,数据148.5MHz,时钟148.5MHz,单沿采样.*/
			SensorReg_Write( 0xFF, 0x00);
			SensorReg_Write( 0x56, 0x32);
			SensorReg_Write( 0xFF, 0x01);
			SensorReg_Write( 0x90+portsel, 0x00);
			SensorReg_Write( 0x92+portsel, 0x00);
			SensorReg_Write( 0xA0, 0x00);
			SensorReg_Write( 0xA1, 0x00);
			SensorReg_Write( 0xA2, 0x00);
			SensorReg_Write( 0xA3, 0x00);
			SensorReg_Write( 0xC0+portsel*2, 0x98);    
			SensorReg_Write( 0xC1+portsel*2, 0xBA);
			SensorReg_Read(0xC8, &tmp);
			tmp = tmp & (portsel%2?0x0F:0xF0);
			tmp |= (portsel%2?0x80:0x08);
			SensorReg_Write( 0xC8, tmp);
			SensorReg_Write( 0xCF-(portsel<<1), 0x43);
			break;
		case NVP6124_OUTMODE_2MUX_FHD:	
			/*FHD,3840H,HDEX 2mux任意混合,数据297MHz,时钟148.5MHz,双沿采样.
			SOC VI端通过丢点，实现3840H->960H, HDEX->720P  */
			SensorReg_Write( 0xFF, 0x00);
			SensorReg_Write( 0x56, 0x10);
			SensorReg_Write( 0xFF, 0x01);
			SensorReg_Write( 0x90+portsel, 0x01);
			SensorReg_Write( 0x92+portsel, 0x01);
			SensorReg_Write( 0xA0+chid*2, 0x01);
			SensorReg_Write( 0xA1+chid*2, 0x01);
			SensorReg_Write( 0xC0+portsel*2, chid==0?0x10:0x32);    
			SensorReg_Read(0xC8, &tmp);
			tmp = tmp & (portsel%2?0x0F:0xF0);
			tmp |= (portsel%2?0x20:0x02);
			SensorReg_Write( 0xC8, tmp);
			SensorReg_Write( 0xCF-(portsel<<1), 0x43);
			//SensorReg_Write( 0xCD, 0x65);  //297MHz clock test
			//SensorReg_Write( 0xCF, 0x6A);
			break;	
		case NVP6124_OUTMODE_1MUX_HD_X:   //nvp6124b
		case NVP6124_OUTMODE_1MUX_FHD_X:
			break;
		case NVP6124_OUTMODE_4MUX_FHD_X:
			/*输出FHD-X 4通道,数据297MHz,时钟148.5MHz,单沿采样.*/
			SensorReg_Write( 0xFF, 0x00);
			SensorReg_Write( 0x56, 0x32);
			SensorReg_Write( 0xFF, 0x01);
			SensorReg_Write( 0x90+portsel, 0x01);
			SensorReg_Write( 0x92+portsel, 0x01);
			SensorReg_Write( 0xA0, 0x01);
			SensorReg_Write( 0xA1, 0x01);
			SensorReg_Write( 0xA2, 0x01);
			SensorReg_Write( 0xA3, 0x01);
			SensorReg_Write( 0xC0+portsel*2, 0x98);    
			SensorReg_Write( 0xC1+portsel*2, 0xBA);
			SensorReg_Read(0xC8, &tmp);
			tmp = tmp & (portsel%2?0x0F:0xF0);
			tmp |= (portsel%2?0x80:0x08);
			SensorReg_Write( 0xC8, tmp);
			SensorReg_Write( 0xCF-(portsel<<1), 0x43);  
			break;
		case NVP6124_OUTMODE_4MUX_MIX: 
			/*HD,1920H,FHD-X 4mux任意混合,数据297MHz,时钟148.5MHz,双沿采样
			SOC VI端通过丢点，实现1920H->960H  */
			SensorReg_Write( 0xFF, 0x00);
			SensorReg_Write( 0x56, 0x32);
			SensorReg_Read(0xFD, &tmp);
			if(((tmp&0x0F) == 0x02) || ((tmp&0x0F) == 0x03))
				reg1 |= 0x08;
			else
				reg1 &= 0xF0;
			if((((tmp>>4)&0x0F) == 0x02) || (((tmp>>4)&0x0F) == 0x03))
				reg1 |= 0x80;
			else
				reg1 &= 0x0F;
			SensorReg_Read(0xFE, &tmp);
			if(((tmp&0x0F) == 0x02) || ((tmp&0x0F) == 0x03))
				reg2 |= 0x08;
			else
				reg2 &= 0xF0;
			if((((tmp>>4)&0x0F) == 0x02) || (((tmp>>4)&0x0F) == 0x03))
				reg2 |= 0x80;
			else
				reg2 &= 0x0F;
			SensorReg_Write( 0xFF, 0x01);
			SensorReg_Write( 0x90+portsel, 0x01);
			SensorReg_Write( 0x92+portsel, 0x01);
			SensorReg_Write( 0xA0, 0x01);
			SensorReg_Write( 0xA1, 0x01);
			SensorReg_Write( 0xA2, 0x01);
			SensorReg_Write( 0xA3, 0x01);
			SensorReg_Write( 0xC0+portsel*2, 0x10|reg1);    
			SensorReg_Write( 0xC1+portsel*2, 0x32|reg2);
			SensorReg_Read(0xC8, &tmp);
			tmp = tmp & (portsel%2?0x0F:0xF0);
			tmp |= (portsel%2?0x80:0x08);
			SensorReg_Write( 0xC8, tmp);
			SensorReg_Write( 0xCF-(portsel<<1), 0x43);  
			break;	
		case NVP6124_OUTMODE_2MUX_MIX:  
			/*HD,1920H,FHD-X 2MUX任意混合,数据148.5MHz,时钟148.5MHz,单沿采样	
			SOC VI端通过丢点，实现1920H->960H  */
			SensorReg_Write( 0xFF, 0x00);
			SensorReg_Write( 0x56, 0x10);
			SensorReg_Read(0xFD, &tmp);
			if(((tmp&0x0F) == 0x02) || ((tmp&0x0F) == 0x03))
				reg1 |= 0x08;
			else
				reg1 &= 0xF0;
			if((((tmp>>4)&0x0F) == 0x02) || (((tmp>>4)&0x0F) == 0x03))
				reg1 |= 0x80;
			else
				reg1 &= 0x0F;
			SensorReg_Read(0xFE, &tmp);
			if(((tmp&0x0F) == 0x02) || ((tmp&0x0F) == 0x03))
				reg2 |= 0x08;
			else
				reg2 &= 0xF0;
			if((((tmp>>4)&0x0F) == 0x02) || (((tmp>>4)&0x0F) == 0x03))
				reg2 |= 0x80;
			else
				reg2 &= 0x0F;
			SensorReg_Write( 0xFF, 0x01);
			SensorReg_Write( 0x90+portsel, 0x03);
			SensorReg_Write( 0x92+portsel, 0x03);
			SensorReg_Write( 0xA0+chid*2, 0x03);
			SensorReg_Write( 0xA1+chid*2, 0x03);
			SensorReg_Write( 0xC0+portsel*2, chid==0?(0x10|reg1):(0x32|reg2));  
			SensorReg_Read(0xC8, &tmp);
			tmp = tmp & (portsel%2?0x0F:0xF0);
			tmp |= (portsel%2?0x20:0x02);
			SensorReg_Write( 0xC8, tmp);
			SensorReg_Write( 0xCF-(portsel<<1), 0x46);  
			break;	
		default:
			UartSendTrace("portmode %d not supported yet\n", portmode);
			break;		
  	}
	UartSendTrace("nvp6124b_set_portmode portsel %d portmode %d setting\n", portsel, portmode);
	return 0;
}

void nvp6124_video_set_contrast(ms_cus_sensor *handle, unsigned int ch, unsigned int value, unsigned int v_format)
{	
	SensorReg_Write( 0xFF, 0x00);
	if(value >= 100)
	{
		if(ch_mode_status[ch] == NVP6124_VI_1080P_2530)
			SensorReg_Write( (0x10+(ch%4)),(nvp6124_con_tbl[v_format]+value-100));
		else if(ch_mode_status[ch] == NVP6124_VI_720P_2530 || ch_mode_status[ch] == NVP6124_VI_720P_5060 || ch_mode_status[ch] == NVP6124_VI_HDEX)
			SensorReg_Write( (0x10+(ch%4)),(nvp6124_con_tbl_720P[v_format]+value-100));
		else //cvbs
			SensorReg_Write( (0x10+(ch%4)),(nvp6124_con_tbl_960H[v_format]+value-100));
	}
	else
	{
		if(ch_mode_status[ch] == NVP6124_VI_1080P_2530)
			SensorReg_Write( (0x10+(ch%4)),(nvp6124_con_tbl[v_format]+(0xff-(98-value))));
		else if(ch_mode_status[ch] == NVP6124_VI_720P_2530 || ch_mode_status[ch] == NVP6124_VI_720P_5060)
			SensorReg_Write( (0x10+(ch%4)),(nvp6124_con_tbl_720P[v_format]+(0xff-(98-value))));
		else
			SensorReg_Write( (0x10+(ch%4)),(nvp6124_con_tbl_960H[v_format]+(0xff-(98-value))));
	}
}

void nvp6124_video_set_brightness(ms_cus_sensor *handle, unsigned int ch, unsigned int value, unsigned int v_format)
{
	SensorReg_Write( 0xFF, 0x00);
	if(value >= 100)
	{
		if(ch_mode_status[ch] == NVP6124_VI_1080P_2530)
			SensorReg_Write( (0x0c+(ch%4)),(nvp6124_bri_tbl[v_format]+value-100));
		else if(ch_mode_status[ch] == NVP6124_VI_720P_2530 || ch_mode_status[ch] == NVP6124_VI_720P_5060 || ch_mode_status[ch] == NVP6124_VI_HDEX)
			SensorReg_Write( (0x0c+(ch%4)),(nvp6124_bri_tbl_720P[v_format]+value-100));
		else 
			SensorReg_Write( (0x0c+(ch%4)),(nvp6124_bri_tbl_960H[v_format]+value-100));
	}	
	else
	{
		if(ch_mode_status[ch] == NVP6124_VI_1080P_2530)
			SensorReg_Write( (0x0c+(ch%4)),(nvp6124_bri_tbl[v_format]+(0xff-(98-value))));
		else if(ch_mode_status[ch] == NVP6124_VI_720P_2530 || ch_mode_status[ch] == NVP6124_VI_720P_5060 || ch_mode_status[ch] == NVP6124_VI_HDEX)
			SensorReg_Write( (0x0c+(ch%4)),(nvp6124_bri_tbl_720P[v_format]+(0xff-(98-value))));
		else 
			SensorReg_Write( (0x0c+(ch%4)),(nvp6124_bri_tbl_960H[v_format]+(0xff-(98-value))));
	}	
}

void nvp6124_video_set_saturation(ms_cus_sensor *handle, unsigned int ch, unsigned int value, unsigned int v_format)
{
	SensorReg_Write( 0xFF, 0x00);
	if(ch_mode_status[ch] == NVP6124_VI_1080P_2530)
		SensorReg_Write( (0x3c+(ch%4)),(nvp6124_sat_tbl[v_format]+value-100));
	else if(ch_mode_status[ch] == NVP6124_VI_720P_2530 || ch_mode_status[ch] == NVP6124_VI_720P_5060 || ch_mode_status[ch] == NVP6124_VI_HDEX)
		SensorReg_Write( (0x3c+(ch%4)),(nvp6124_sat_tbl_720P[v_format]+value-100));
	else 
		SensorReg_Write( (0x3c+(ch%4)),(nvp6124_sat_tbl_960H[v_format]+value-100));
}

void nvp6124_video_set_hue(ms_cus_sensor *handle, unsigned int ch, unsigned int value, unsigned int v_format)
{
	SensorReg_Write( 0xFF, 0x00);
	if(ch_mode_status[ch] == NVP6124_VI_1080P_2530)
		SensorReg_Write( (0x40+(ch%4)), (nvp6124_hue_tbl[v_format]+value-100));
	else if(ch_mode_status[ch] == NVP6124_VI_720P_2530 || ch_mode_status[ch] == NVP6124_VI_720P_5060 || ch_mode_status[ch] == NVP6124_VI_HDEX)
		SensorReg_Write( (0x40+(ch%4)), (nvp6124_hue_tbl_720P[v_format]+value-100));
	else
		SensorReg_Write( (0x40+(ch%4)), (nvp6124_hue_tbl_960H[v_format]+value-100));
}

void nvp6124_video_set_sharpness(ms_cus_sensor *handle, unsigned int ch, unsigned int value)
{
	SensorReg_Write( 0xFF, 0x00);
	SensorReg_Write( (0x14+(ch%4)), (0x90+value-100));
}

static void nvp6124_common_init(ms_cus_sensor *handle)
{
    int i,cnt=0;
    unsigned short sen_data;

    SensorReg_Write(0xFF, 0x00);
    SensorReg_Read(0xF4, &chip_id);
    UartSendTrace("[%s]: CHIP_ID: 0x%x\n", __FUNCTION__, chip_id);

	SensorReg_Write(0xFF, 0x00);
    nvp6124_write_table(handle, 0x00,NVP6124_B0_Buf,254);
	SensorReg_Write(0xFF, 0x01);
    nvp6124_write_table(handle, 0x00,NVP6124_B1_Buf,254);
	SensorReg_Write(0xFF, 0x02);
    nvp6124_write_table(handle, 0x00,NVP6124_B2_Buf,254);
	SensorReg_Write(0xFF, 0x03);
    nvp6124_write_table(handle, 0x00,NVP6124_B3_Buf,254);
	SensorReg_Write(0xFF, 0x04);
    nvp6124_write_table(handle, 0x00,NVP6124_B4_Buf,254);
	SensorReg_Write(0xFF, 0x09);
    nvp6124_write_table(handle, 0x00,NVP6124_B9_Buf,254);
	SensorReg_Write(0xFF, 0x0A);
    nvp6124_write_table(handle, 0x00,NVP6124_BA_Buf,254);
	SensorReg_Write(0xFF, 0x0B);
    nvp6124_write_table(handle, 0x00,NVP6124_BB_Buf,254);
    
    //nvp6124 system init
    for(i=0;i< ARRAY_SIZE(Sensor_init_System_table);i++)
    {
        if(Sensor_init_System_table[i].reg==0xffff)
        {
            MsSleep((Sensor_init_System_table[i].data)*RTK_MS_TO_TICK(1));//usleep(1000*Sensor_init_table[i].data);
        }
        else
        {
            cnt = 0;
            while(SensorReg_Write(Sensor_init_System_table[i].reg,Sensor_init_System_table[i].data) != SUCCESS)
            {
                cnt++;
                SENSOR_DMSG("[%s] set Sensor_init_table retry : %d...\n",__FUNCTION__,cnt);
                if(cnt>=10)
                {
                    SENSOR_EMSG("[%s:%d] retry FAIL!!\n", __FUNCTION__, __LINE__);
                    return FAIL;
                }
                MsSleep(RTK_MS_TO_TICK(1));//usleep(10*1000);
            }
#if 0
            SensorReg_Read(Sensor_init_System_table[i].reg, &sen_data);
            UartSendTrace("nvp6124b reg: 0x%x, data: 0x%x, read: 0x%x.\n",Sensor_init_System_table[i].reg, Sensor_init_System_table[i].data, sen_data);
#endif
        }
    }
}

static int pCus_init(ms_cus_sensor *handle)
{
    int ch = 0;
    unsigned short sen_data;

    ISensorIfAPI *sensor_if = &(handle->sensor_if_api);
    sensor_if->PCLK(CUS_SNR_PCLK_SR_PAD);
 
    //software_reset(handle);
    nvp6124_common_init(handle);

    for(ch=0;ch<nvp6124_cnt;ch++)
    {
    	nvp6124_set_chnmode(handle, ch, PAL, NVP6124_VI_720P_2530);   //默认设置为1080P模式.
    }
    
    nvp6124b_set_portmode(handle, 0, NVP6124_OUTMODE_1MUX_HD, 1);  //设置nvp6124b 2个port的输出模式
    nvp6124b_set_portmode(handle, 1, NVP6124_OUTMODE_1MUX_HD, 0);
    nvp6124_datareverse(handle);

    MsSleep(RTK_MS_TO_TICK(10));
    pCus_SetAEGain(handle,2048);
    pCus_SetAEUSecs(handle, 25000);

    #if 0//for test video 
    SensorReg_Write(0xFF, 0x00);

    SensorReg_Write(0x08, 0x60);
    SensorReg_Write(0x09, 0x60);
    SensorReg_Write(0x0A, 0x60);
    SensorReg_Write(0x0B, 0x60);
    SensorReg_Write(0x81, 0x07);
    SensorReg_Write(0x82, 0x07);
    SensorReg_Write(0x83, 0x07);
    SensorReg_Write(0x84, 0x07);
    SensorReg_Write(0x85, 0x00);
    SensorReg_Write(0x86, 0x00);
    SensorReg_Write(0x87, 0x00);
    SensorReg_Write(0x88, 0x00);

    SensorReg_Write(0x78, 0xAA);//test pattern mdoe
    SensorReg_Write(0x79, 0xAA);//test pattern mode

     SensorReg_Write(0xFF, 0x01);
     SensorReg_Write(0x88, 0x0A);
     SensorReg_Write(0x89, 0x0A);
     SensorReg_Write(0x8A, 0x0A);
     SensorReg_Write(0x8B, 0x0A);
     SensorReg_Write(0x8C, 0x0A);
     SensorReg_Write(0x8D, 0x0A);
     SensorReg_Write(0x8E, 0x0A);
     SensorReg_Write(0x8F, 0x0A);

     SensorReg_Write(0xFF, 0x05);
     SensorReg_Write(0x2C, 0x08);
     #endif
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
    nvp6124b_params *params = (nvp6124b_params *)handle->private_data;

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
    nvp6124b_params *params = (nvp6124b_params *)handle->private_data;
    SENSOR_DMSG("[%s] FPS %d\n", __FUNCTION__, params->expo.fps);

    return params->expo.fps;
}
static int pCus_SetFPS(ms_cus_sensor *handle, u32 fps)
{
    SENSOR_DMSG("[%s]\n", __FUNCTION__);
    nvp6124b_params *params = (nvp6124b_params *)handle->private_data;


    return 0; //test only

    if(fps>=3 && fps <= 30)
    {
        params->expo.fps = fps;
        params->expo.vts=  (vts_30fps*30.1f)/fps;
        //vts_reg[0].data = (params->expo.vts>> 16) & 0x0003;
        vts_reg[0].data = (params->expo.vts >> 8) & 0x00ff;
        vts_reg[1].data = (params->expo.vts >> 0) & 0x00ff;
       // params->reg_dirty = true; //reg need to update = true;
       return SUCCESS;
    }
    else if(fps>=3000 && fps <= 30000)
    {
        params->expo.fps = fps;
        params->expo.vts=  (vts_30fps*30100.0f)/fps;
        vts_reg[0].data = (params->expo.vts >> 8) & 0x00ff;
        vts_reg[1].data = (params->expo.vts >> 0) & 0x00ff;
        return SUCCESS;
    }
    else
    {
        SENSOR_EMSG("[%s] FPS %d out of range.\n",fps,__FUNCTION__);
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
    nvp6124b_params *params = (nvp6124b_params *)handle->private_data;
    switch(status)
    {
        case CUS_FRAME_INACTIVE:
            //SensorReg_Write(0x3001,0);
            break;
        case CUS_FRAME_ACTIVE:
            if(params->reg_dirty)
            {
                //SensorReg_Write(0x3001,1);

                // SensorRegArrayW((I2C_ARRAY*)mirror_reg, sizeof(mirror_reg)/sizeof(I2C_ARRAY));
                // SensorRegArrayW((I2C_ARRAY*)expo_reg, sizeof(expo_reg)/sizeof(I2C_ARRAY));
                // SensorRegArrayW((I2C_ARRAY*)gain_reg, sizeof(gain_reg)/sizeof(I2C_ARRAY));
                //  SensorRegArrayW((I2C_ARRAY*)vts_reg, sizeof(vts_reg)/sizeof(I2C_ARRAY));

                SensorReg_Write(0x3001,0);
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
    //int rc;
    u32 lines = 0;
    //rc = SensorRegArrayR((I2C_ARRAY*)expo_reg, ARRAY_SIZE(expo_reg));

    //lines |= (u32)(expo_reg[0].data&0xff)<<16;
    lines |= (u32)(expo_reg[0].data&0xff)<<8;
    lines |= (u32)(expo_reg[1].data&0xff)<<0;
    // lines >>= 4;
    // *us = (lines+dummy) * params->expo.us_per_line;
    *us = lines;//(lines*Preview_line_period);
    SENSOR_DMSG("[%s] sensor expo lines/us 0x%x,0x%x us\n", __FUNCTION__, lines, *us);
    return SUCCESS;
}

static int pCus_SetAEUSecs(ms_cus_sensor *handle, u32 us)
{
    u32 lines = 0, vts = 0;
    nvp6124b_params *params = (nvp6124b_params *)handle->private_data;

    return 0; //test only

    lines=(1000*us)/Preview_line_period;
    if(lines<1) lines=1;
    if (lines >params->expo.vts-1)
    {
        vts = lines +1;
    }
    else
    vts=params->expo.vts;

    // lines=us/Preview_line_period;
    SENSOR_DMSG("[%s] us %ld, lines %ld, vts %ld\n", __FUNCTION__,us,lines,params->expo.vts);
    lines=vts-lines-1;
    //expo_reg[0].data = (lines>>16) & 0x0003;
    expo_reg[0].data = (lines>>8) & 0x00ff;
    expo_reg[1].data = (lines>>0) & 0x00ff;

    // vts_reg[0].data = (vts >> 16) & 0x0003;
    vts_reg[0].data = (vts >> 8) & 0x00ff;
    vts_reg[1].data = (vts >> 0) & 0x00ff;

    SensorReg_Write(0x3001,1);
    SensorRegArrayW((I2C_ARRAY*)expo_reg, sizeof(expo_reg)/sizeof(I2C_ARRAY));
    SensorRegArrayW((I2C_ARRAY*)gain_reg, sizeof(gain_reg)/sizeof(I2C_ARRAY));
    SensorRegArrayW((I2C_ARRAY*)vts_reg, sizeof(vts_reg)/sizeof(I2C_ARRAY));
    //SensorReg_Write(0x3001,0);
    params->reg_dirty = true; //reg need to update
    return SUCCESS;
}

// Gain: 1x = 1024
static int pCus_GetAEGain(ms_cus_sensor *handle, u32* gain)
{
    //int rc = SensorRegArrayR((I2C_ARRAY*)gain_reg, ARRAY_SIZE(gain_reg));
    u16 temp_gain;
    double temp_gain_double;

    temp_gain=gain_reg[0].data;
    temp_gain_double=((double)(temp_gain*3)/200.0f);
    *gain=(u32)(pow(10,temp_gain_double)*1024);

    SENSOR_DMSG("[%s] get gain/reg (1024=1X)= 0x%x/0x%x\n", __FUNCTION__, *gain,gain_reg[0].data);
    return SUCCESS;
}

static int pCus_SetAEGain_cal(ms_cus_sensor *handle, u32 gain)
{
    nvp6124b_params *params = (nvp6124b_params *)handle->private_data;
    double gain_double;
    params->expo.final_gain = gain;

    return 0; //test only

    if(gain<1024)
        gain=1024;
    else if(gain>=177*1024)
        gain=177*1024;

    gain_double = 20*log10((double)gain/1024);
    gain_reg[0].data=(u16)((gain_double*10)/3);
    params->reg_dirty = true;    //reg need to update

    SENSOR_DMSG("[%s] set gain/reg=0x%x/0x%x\n", __FUNCTION__, gain,gain_reg[0].data);
    return SUCCESS;
}

static int pCus_SetAEGain(ms_cus_sensor *handle, u32 gain)
{
    //extern DBG_ITEM Dbg_Items[DBG_TAG_MAX];
    nvp6124b_params *params = (nvp6124b_params *)handle->private_data;

    return SUCCESS;
}

static int pCus_GetAEMinMaxUSecs(ms_cus_sensor *handle, u32 *min, u32 *max)
{
    SENSOR_DMSG("[%s]\n", __FUNCTION__);
    *min = 1;
    *max = 1000000/4;
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

static int nvp6124b_GetShutterInfo(struct __ms_cus_sensor* handle,CUS_SHUTTER_INFO *info)
{
    SENSOR_DMSG("[%s]\n", __FUNCTION__);
    info->max = 1000000000/12;
    info->min = Preview_line_period * 5;
    info->step = Preview_line_period;
    return SUCCESS;
}

static int pCus_BT656_GetSrcType(ms_cus_sensor *handle, CUS_SNR_ANADEC_SRC_TYPE *psrc_type)
{
    unsigned short usval = 0;
    nvp6124_input_videofmt stVideofmt;
    int i;

    *psrc_type = CUS_SNR_ANADEC_SRC_NO_READY;

    if(pCus_I2CRead == NULL){
        SENSOR_EMSG("[%s] I2C function is not ready!\n", __FUNCTION__);
        return FAIL;
    }
    video_fmt_det(handle, &stVideofmt);
    #if 0// 4 channel detect 
    for(i=0; i<nvp6124_cnt; i++)
    {
        if(stVideofmt.getvideofmt[i] != 0 && i == 0)//detect channel 0 SIG
        {
            usval =  stVideofmt.getvideofmt[i];
            //UartSendTrace("[%s]: CHN: %d, SIG: 0x%x\n", __FUNCTION__, i, stVideofmt.getvideofmt[i]);
            break;
        }
    }
    #else
    usval =  stVideofmt.getvideofmt[0];
    #endif
    //switch case

    switch(usval)
    {
    	case 0x01:
    		*psrc_type = CUS_SNR_ANADEC_SRC_NTSC;
    	break;
    	case 0x02:
    		*psrc_type = CUS_SNR_ANADEC_SRC_PAL;
    	break;
    	case 0x04:
    		*psrc_type = CUS_SNR_ANADEC_SRC_HD; //30FPS
    	break;
    	case 0x08:
    		*psrc_type = CUS_SNR_ANADEC_SRC_HD; //25FPS
    	break;
    	case 0x40:
    	      *psrc_type = CUS_SNR_ANADEC_SRC_FHD; // 30FPS
    	break;
    	case 0x80:
    	      *psrc_type = CUS_SNR_ANADEC_SRC_FHD; // 25FPS
    	break;
    	default:
    	      *psrc_type = CUS_SNR_ANADEC_SRC_NO_READY;
    	break;
    }

    return SUCCESS;
}

int nvp6124b_cus_camsensor_init_handle_ch0(ms_cus_sensor* handle)
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
    sprintf(str, "nvp6124b");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(nvp6124b_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (nvp6124b_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(nvp6124b_params));
#else
    handle->private_data = calloc(1, sizeof(nvp6124b_params));
#endif
    nvp6124b_params *params = (nvp6124b_params *)handle->private_data;

    ////////////////////////////////////
    //    sensor model ID                           //
    ////////////////////////////////////
    sprintf(handle->model_id,"nvp6124b_PARL ch0");

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
    handle->video_res_supported.res[0].nOutputWidth= Preview_WIDTH;
    handle->video_res_supported.res[0].nOutputHeight= Preview_HEIGHT;

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
    handle->pCus_sensor_release     = nvp6124b_cus_camsensor_release_handle;
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
    handle->pCus_sensor_SetPatternMode = nvp6124b_SetPatternMode;
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
    handle->pCus_sensor_GetShutterInfo = nvp6124b_GetShutterInfo;

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

    handle->snr_pad_group = SENSOR_PAD_GROUP_SET;

    handle->channel_num = SENSOR_CHANNEL_NUM;
    handle->channel_mode = SENSOR_CHANNEL_MODE;

    //============================================
    //BT656 config begin.
    handle->interface_attr.attr_bt656.bt656_total_ch = 1;
    handle->interface_attr.attr_bt656.bt656_cur_ch = 0;
    handle->interface_attr.attr_bt656.bt656_ch_det_en = SENSOR_BT656_CH_DET_ENABLE;
    handle->interface_attr.attr_bt656.bt656_ch_det_sel = SENSOR_BT656_CH_DET_SEL;
    handle->interface_attr.attr_bt656.bt656_bit_swap = SENSOR_BT656_BIT_SWAP;
    handle->interface_attr.attr_bt656.bt656_8bit_mode = SENSOR_BT656_8BIT_MODE;
    handle->interface_attr.attr_bt656.bt656_vsync_delay = SENSOR_BT656_VSYNC_DELAY;
    handle->interface_attr.attr_bt656.bt656_hsync_inv = SENSOR_HSYCN_INVERT;
    handle->interface_attr.attr_bt656.bt656_vsync_inv = SENSOR_VSYCN_INVERT;
    handle->interface_attr.attr_bt656.bt656_clamp_en = SENSOR_CLAMP_ENABLE;
    handle->interface_attr.attr_bt656.bt656_yuv_order = CUS_SENSOR_YUV_ORDER_YC;
    handle->interface_attr.attr_bt656.pCus_sensor_bt656_get_src_type = pCus_BT656_GetSrcType;
    //BT656 config end.
    //============================================

    return SUCCESS;
}

int nvp6124b_cus_camsensor_release_handle(ms_cus_sensor *handle)
{
#if defined(__RTK_OS__)
    CamOsRet_e                  eCamOsRet = CAM_OS_OK;
#endif

    SENSOR_DMSG("[%s]\n", __FUNCTION__);
    if (handle && handle->private_data)
    {
        SENSOR_IMSG("[%s] release handle 0x%x, private data %x\n",__FUNCTION__,(int)handle,(int)handle->private_data);
#if defined(__RTK_OS__)
        eCamOsRet = CamOsDirectMemRelease((void*)handle->private_data, sizeof(nvp6124b_params));
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

static int pCus_poweron_dummy(ms_cus_sensor *handle)
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;

    //Sensor power on sequence
    //DrvSensorIFHWSetIOPad(0/*TBD*/, CUS_SENIF_BUS_BT656, CUS_SR_PAD_CFG_6);//call sensor if
    sensor_if->SetIOPad(CUS_SENSOR_PAD_GROUP_B/*TBD. Pad Num.*/, CUS_SENIF_BUS_BT656, CUS_SR1_BT656_MODE_1);//Parallel: reg_sr1_bt656_mode
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_DISABLE, handle->PCLK_POLARITY);     //Set_csi_if(0, 0); //disable MIPI
    sensor_if->MCLK(CUS_SENSOR_PAD_GROUP_B, 1, handle->mclk);

    SENSOR_DMSG("[%s] reset low\n", __FUNCTION__);
    sensor_if->Reset(CUS_SENSOR_PAD_GROUP_B, handle->reset_POLARITY);
    MsSleep(RTK_MS_TO_TICK(100));//usleep(500);
    SENSOR_DMSG("[%s] power low\n", __FUNCTION__);
    sensor_if->PowerOff(CUS_SENSOR_PAD_GROUP_B, handle->pwdn_POLARITY);
    MsSleep(RTK_MS_TO_TICK(100));//usleep(500);

    // power -> high, reset -> high
    SENSOR_DMSG("[%s] power high\n", __FUNCTION__);
    sensor_if->PowerOff(CUS_SENSOR_PAD_GROUP_B, !handle->pwdn_POLARITY);
    MsSleep(RTK_MS_TO_TICK(100));//usleep(500);
    SENSOR_DMSG("[%s] reset high\n", __FUNCTION__);
    sensor_if->Reset(CUS_SENSOR_PAD_GROUP_B, !handle->reset_POLARITY);
    MsSleep(RTK_MS_TO_TICK(100));//usleep(500);

    //sensor_if->Set3ATaskOrder( def_order);
    // pure power on
    sensor_if->PowerOff(CUS_SENSOR_PAD_GROUP_B, !handle->pwdn_POLARITY);
    return SUCCESS;
}

static int pCus_poweroff_dummy(ms_cus_sensor *handle)
{
    ISensorIfAPI *sensor_if = &handle->sensor_if_api;
    //sensor_if->MIPISamplingDelay(handle, false, handle->mipi_sampling_delay);
    SENSOR_DMSG("[%s] power low\n", __FUNCTION__);
    sensor_if->PowerOff( 1, handle->pwdn_POLARITY);

    MsSleep(RTK_MS_TO_TICK(200));//usleep(1000);
    sensor_if->SetCSI_Clk(handle->snr_pad_group, CUS_CSI_CLK_DISABLE, handle->PCLK_POLARITY);     //Set_csi_if(0, 0);
    sensor_if->MCLK(0, 0, handle->mclk);

    return SUCCESS;
}

/////////////////// image function /////////////////////////
//Get and check sensor ID
//if i2c error or sensor id does not match then return FAIL
static int pCus_GetSensorID_dummy(ms_cus_sensor *handle, u32 *id)
{
    *id = 0;
    return SUCCESS;
}

static int nvp6124b_SetPatternMode_dummy(ms_cus_sensor *handle,u32 mode)
{
    return SUCCESS;
}

#if 1//defined(__MV5_FPGA__)
static int pCus_I2CWrite_dummy(ms_cus_sensor *handle, unsigned short usreg, unsigned short usval)
{
    return SUCCESS;
}

static int pCus_I2CRead_dummy(ms_cus_sensor *handle, unsigned short usreg)
{
    return SUCCESS;
}
#endif

static int pCus_init_dummy(ms_cus_sensor *handle)
{
    int ch = 0;
    unsigned short sen_data;

    ISensorIfAPI *sensor_if = &(handle->sensor_if_api);
    sensor_if->PCLK(CUS_SNR_PCLK_SR_PAD);
    return SUCCESS;
}

static int pCus_GetVideoRes_dummy(ms_cus_sensor *handle, cus_camsensor_res **res)
{
    SENSOR_DMSG("[%s]\n", __FUNCTION__);
    //return current resolution
    *res = &handle->video_res_supported.res[handle->video_res_supported.ulcur_res];
    return SUCCESS;
}

static int pCus_SetVideoRes_dummy(ms_cus_sensor *handle, u32 res)
{
    SENSOR_DMSG("[%s]\n", __FUNCTION__);
    handle->video_res_supported.ulcur_res = 0; //TBD
    //TODO: Set sensor output resolution
    return SUCCESS;
}

static int pCus_GetOrien_dummy(ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT *orit)
{
    *orit = CUS_ORIT_M0F0;
    return SUCCESS;
}

static int pCus_SetOrien_dummy(ms_cus_sensor *handle, CUS_CAMSENSOR_ORIT orit)
{
    return SUCCESS;
}

static int pCus_GetFPS_dummy(ms_cus_sensor *handle)
{
    nvp6124b_params *params = (nvp6124b_params *)handle->private_data;
    SENSOR_DMSG("[%s] FPS %d\n", __FUNCTION__, params->expo.fps);

    return SUCCESS;
}

static int pCus_SetFPS_dummy(ms_cus_sensor *handle, u32 fps)
{
    return SUCCESS;
}

static int pCus_GetSensorCap_dummy(ms_cus_sensor *handle, CUS_CAMSENSOR_CAP *cap)
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
static int pCus_AEStatusNotify_dummy(ms_cus_sensor *handle, CUS_CAMSENSOR_AE_STATUS_NOTIFY status)
{
    return SUCCESS;
}

static int pCus_GetAEUSecs_dummy(ms_cus_sensor *handle, u32 *us)
{
    *us = 0;
    return SUCCESS;
}

static int pCus_SetAEUSecs_dummy(ms_cus_sensor *handle, u32 us)
{
    return SUCCESS;
}

// Gain: 1x = 1024
static int pCus_GetAEGain_dummy(ms_cus_sensor *handle, u32* gain)
{
    *gain = 0;
    return SUCCESS;
}

static int pCus_SetAEGain_cal_dummy(ms_cus_sensor *handle, u32 gain)
{
    return SUCCESS;
}

static int pCus_SetAEGain_dummy(ms_cus_sensor *handle, u32 gain)
{
    return SUCCESS;
}

static int pCus_GetAEMinMaxUSecs_dummy(ms_cus_sensor *handle, u32 *min, u32 *max)
{
    *min = 1;
    *max = 1000000/4;
    return SUCCESS;
}

static int pCus_GetAEMinMaxGain_dummy(ms_cus_sensor *handle, u32 *min, u32 *max)
{
    SENSOR_DMSG("[%s]\n", __FUNCTION__);
    *min = SENSOR_MIN_GAIN;
    *max = SENSOR_MAX_GAIN;

    return SUCCESS;
}

static int pCus_setCaliData_gain_linearity_dummy(ms_cus_sensor* handle, CUS_GAIN_GAP_ARRAY* pArray, u32 num)
{
    return SUCCESS;
}

static int nvp6124b_GetShutterInfo_dummy(struct __ms_cus_sensor* handle,CUS_SHUTTER_INFO *info)
{
    return SUCCESS;
}

static int pCus_BT656_GetSrcType_dummy(ms_cus_sensor *handle, CUS_SNR_ANADEC_SRC_TYPE *psrc_type)
{
    unsigned short usval = 0;
    nvp6124_input_videofmt stVideofmt;
    int i;

    *psrc_type = CUS_SNR_ANADEC_SRC_NO_READY;

    if(pCus_I2CRead == NULL){
        SENSOR_EMSG("[%s] I2C function is not ready!\n", __FUNCTION__);
        return FAIL;
    }
    video_fmt_det(handle, &stVideofmt);
    #if 0
    for(i=0; i<nvp6124_cnt; i++)
    {
        if(stVideofmt.getvideofmt[i] != 0 && i == 1)//detect channel 1 SIG
        {
            usval =  stVideofmt.getvideofmt[i];
            //UartSendTrace("[%s]: CHN: %d, SIG: 0x%x\n", __FUNCTION__, i, stVideofmt.getvideofmt[i]);
            break;
        }
    }
    #else
    usval =  stVideofmt.getvideofmt[1];
    #endif
    //switch case

    switch(usval)
    {
    	case 0x01:
    		*psrc_type = CUS_SNR_ANADEC_SRC_NTSC;
    	break;
    	case 0x02:
    		*psrc_type = CUS_SNR_ANADEC_SRC_PAL;
    	break;
    	case 0x04:
    		*psrc_type = CUS_SNR_ANADEC_SRC_HD; //30FPS
    	break;
    	case 0x08:
    		*psrc_type = CUS_SNR_ANADEC_SRC_HD; //25FPS
    	break;
    	case 0x40:
    	      *psrc_type = CUS_SNR_ANADEC_SRC_FHD; // 30FPS
    	break;
    	case 0x80:
    	      *psrc_type = CUS_SNR_ANADEC_SRC_FHD; // 25FPS
    	break;
    	default:
    	      *psrc_type = CUS_SNR_ANADEC_SRC_NO_READY;
    	break;
    }

    return SUCCESS;
}

int nvp6124b_cus_camsensor_init_handle_dummy(ms_cus_sensor* handle)
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
    UartSendTrace("[%s]\n", __FUNCTION__);
    //private data allocation & init
#if defined(__RTK_OS__)
    sprintf(str, "nvp6124b");
    eCamOsRet = CamOsDirectMemAlloc(str, sizeof(nvp6124b_params), &pvBufVirt, &u64BufMiu, &u64BufPhy);
    if (eCamOsRet != CAM_OS_OK) {
        UartSendTrace("[%s:%d] fail!\n", __FUNCTION__, __LINE__);
        return FAIL;
    }
    handle->private_data = (nvp6124b_params *)pvBufVirt;
    memset(handle->private_data, 0, sizeof(nvp6124b_params));
#else
    handle->private_data = calloc(1, sizeof(nvp6124b_params));
#endif
    nvp6124b_params *params = (nvp6124b_params *)handle->private_data;

    ////////////////////////////////////
    //    sensor model ID                           //
    ////////////////////////////////////
    //sprintf(handle->model_id,"nvp6124b_PARL");

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
    handle->video_res_supported.res[0].nOutputWidth= Preview_WIDTH;
    handle->video_res_supported.res[0].nOutputHeight= 800;

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
    handle->i2c_cfg.nPadNum             = SENSOR_I2C_PAD_MODE;  //pad mode 1

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
    handle->pCus_sensor_release     = nvp6124b_cus_camsensor_release_handle;
    handle->pCus_sensor_init        = pCus_init_dummy;
    handle->pCus_sensor_poweron     = pCus_poweron_dummy;
    handle->pCus_sensor_poweroff    = pCus_poweroff_dummy;

    // Normal
    handle->pCus_sensor_GetSensorID       = pCus_GetSensorID_dummy;
    handle->pCus_sensor_GetVideoResNum = pCus_GetVideoResNum;
    handle->pCus_sensor_GetVideoRes       = pCus_GetVideoRes_dummy;
    handle->pCus_sensor_SetVideoRes       = pCus_SetVideoRes_dummy;
    handle->pCus_sensor_GetOrien          = pCus_GetOrien_dummy;
    handle->pCus_sensor_SetOrien          = pCus_SetOrien_dummy;
    handle->pCus_sensor_GetFPS          = pCus_GetFPS_dummy;
    handle->pCus_sensor_SetFPS          = pCus_SetFPS_dummy;
    handle->pCus_sensor_GetSensorCap    = pCus_GetSensorCap_dummy;
    handle->pCus_sensor_SetPatternMode = nvp6124b_SetPatternMode_dummy;
    ///////////////////////////////////////////////////////
    // AE
    ///////////////////////////////////////////////////////
    // unit: micro seconds
    handle->pCus_sensor_AEStatusNotify = pCus_AEStatusNotify_dummy;
    handle->pCus_sensor_GetAEUSecs      = pCus_GetAEUSecs_dummy;
    handle->pCus_sensor_SetAEUSecs      = pCus_SetAEUSecs_dummy;
    handle->pCus_sensor_GetAEGain       = pCus_GetAEGain_dummy;
    handle->pCus_sensor_SetAEGain_cal   = pCus_SetAEGain_cal_dummy;
    handle->pCus_sensor_SetAEGain       = pCus_SetAEGain_dummy;
    handle->pCus_sensor_GetShutterInfo = nvp6124b_GetShutterInfo_dummy;

    handle->pCus_sensor_GetAEMinMaxGain = pCus_GetAEMinMaxGain_dummy;
    handle->pCus_sensor_GetAEMinMaxUSecs= pCus_GetAEMinMaxUSecs_dummy;
    handle->pCus_sensor_GetDGainRemainder = pCus_GetDGainRemainder;

    //sensor calibration
    handle->pCus_sensor_setCaliData_gain_linearity=pCus_setCaliData_gain_linearity_dummy;
#if 1//defined(__MV5_FPGA__)
    handle->pCus_sensor_I2CWrite = pCus_I2CWrite_dummy; //Andy Liu
    handle->pCus_sensor_I2CRead = pCus_I2CRead_dummy; //Andy Liu
#endif
    params->expo.vts=vts_30fps;
    params->expo.fps = 30;
    params->reg_dirty = false;

    handle->snr_pad_group = CUS_SENSOR_PAD_GROUP_B;

    //handle->channel_num = SENSOR_CHANNEL_NUM;
    handle->channel_mode = CUS_SENSOR_CHANNEL_MODE_RAW_STORE;

    //============================================
    //BT656 config begin.
    handle->interface_attr.attr_bt656.bt656_ch_det_en = SENSOR_BT656_CH_DET_ENABLE;
    handle->interface_attr.attr_bt656.bt656_ch_det_sel = SENSOR_BT656_CH_DET_SEL;
    handle->interface_attr.attr_bt656.bt656_bit_swap = SENSOR_BT656_BIT_SWAP;
    handle->interface_attr.attr_bt656.bt656_8bit_mode = SENSOR_BT656_8BIT_MODE;
    handle->interface_attr.attr_bt656.bt656_vsync_delay = SENSOR_BT656_VSYNC_DELAY;
    handle->interface_attr.attr_bt656.bt656_hsync_inv = SENSOR_HSYCN_INVERT;
    handle->interface_attr.attr_bt656.bt656_vsync_inv = SENSOR_VSYCN_INVERT;
    handle->interface_attr.attr_bt656.bt656_clamp_en = SENSOR_CLAMP_ENABLE;
    handle->interface_attr.attr_bt656.pCus_sensor_bt656_get_src_type = pCus_BT656_GetSrcType_dummy;
    //BT656 config end.
    //============================================
    return SUCCESS;
}

#if (SENSOR_BT656_CH_TOTAL_NUM == 2)
int nvp6124b_cus_camsensor_init_handle_ch1(ms_cus_sensor* handle)
{
    sprintf(handle->model_id,"nvp6124b_PARL ch1");
    handle->channel_num = SENSOR_CHANNEL_NUM + 1;
    handle->interface_attr.attr_bt656.bt656_total_ch = 1;
    handle->interface_attr.attr_bt656.bt656_cur_ch = 0;
    return nvp6124b_cus_camsensor_init_handle_dummy(handle);
}
#endif

#if (SENSOR_BT656_CH_TOTAL_NUM == 4)
int nvp6124b_cus_camsensor_init_handle_ch2(ms_cus_sensor* handle)
{
    sprintf(handle->model_id,"nvp6124b_PARL ch2");
    handle->channel_num = SENSOR_CHANNEL_NUM + 2;
    handle->interface_attr.attr_bt656.bt656_total_ch = SENSOR_BT656_CH_TOTAL_NUM;
    handle->interface_attr.attr_bt656.bt656_cur_ch = 2;
    return nvp6124b_cus_camsensor_init_handle_dummy(handle);
}

int nvp6124b_cus_camsensor_init_handle_ch3(ms_cus_sensor* handle)
{
    sprintf(handle->model_id,"nvp6124b_PARL ch3");
    handle->channel_num = SENSOR_CHANNEL_NUM + 3;
    handle->interface_attr.attr_bt656.bt656_total_ch = SENSOR_BT656_CH_TOTAL_NUM;
    handle->interface_attr.attr_bt656.bt656_cur_ch = 3;
    return nvp6124b_cus_camsensor_init_handle_dummy(handle);
}
#endif


#if defined(__RTK_OS__)
struct SensorMapTable_t gsensor_map_nvp6124b[] = {
    { //Channel 0
        SENSOR_CHANNEL_NUM,
        nvp6124b_cus_camsensor_init_handle_ch0,
        nvp6124b_cus_camsensor_release_handle
    },
#if (SENSOR_BT656_CH_TOTAL_NUM == 2)
    { //Channel 1
        SENSOR_CHANNEL_NUM + 1,
        nvp6124b_cus_camsensor_init_handle_ch1,
        nvp6124b_cus_camsensor_release_handle
    },
#endif
#if (SENSOR_BT656_CH_TOTAL_NUM == 4)
    { //Channel 2
        SENSOR_CHANNEL_NUM + 2,
        nvp6124b_cus_camsensor_init_handle_ch2,
        nvp6124b_cus_camsensor_release_handle
    },
    { //Channel 3
        SENSOR_CHANNEL_NUM + 3,
        nvp6124b_cus_camsensor_init_handle_ch3,
        nvp6124b_cus_camsensor_release_handle
    },
#endif
};

int NVP6124B_Module_Init(void)
{
    int iloop = 0;
    for(iloop = 0; iloop < SENSOR_BT656_CH_TOTAL_NUM; ++iloop){
        cameraSensorRegister(&gsensor_map_nvp6124b[iloop]);
    }
    return 0;
}

void NVP6124B_Module_Exit(void)
{
    int iloop = 0;
    for(iloop = SENSOR_BT656_CH_TOTAL_NUM; iloop >= 0; --iloop){
        cameraSensorUnRegister(&gsensor_map_nvp6124b[iloop]);
    }
}

#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(NVP6124B_Module_Init);
//ait_module_exit(NVP6124B_Module_Exit);
#endif //#if defined(__RTK_OS__)

#endif //#if defined(BIND_SENSOR_NVP6124B) && (BIND_SENSOR_NVP6124B == 1)
