#ifndef HAL_CLKPAD_H
#define HAL_CLKPAD_H
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//


// Drv_ms_clkpad.h
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

#include "kernel_chiptop.h"
#include "drv_clkgen_cmu.h"
#include "drv_clkgen_cmu_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

////////////////////////////////////
//CHIP TOP AND CLKGEN register
////////////////////////////////////
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <hal_ms_isp.h>
#include "drv_ms_isp_general.h"
#include <platform_regs.h>
*/
#if 0
typedef struct
{
    u16 volatile *chiptop;
    u16 volatile *clkgen;
    u16 volatile *padtop;
    u16 volatile *csi_mac;
    u16 volatile *csi_ana;
    u16 volatile *csi_dig;
} hal_clkpad_handle;
#endif

//----------------- ISP CLOCK-------------
#define OFFSET_CLKGEN_TO_CLK_ISP     (0x61<<2)//(0x45<<2)
typedef struct
{
    u32  reg_ckg_aesdma : 5;
    u32                               : 3;
    u32 reg_ckg_icp_en        : 1;
    u32 reg_ckg_icp_invert    : 1;
    u32 reg_ckg_icp           : 3;
    u32                       : 3;
    u32                       : 16;
} clk_isp;

//----------------- ISP CLOCK-------------
#define OFFSET_CLKGEN_TO_CLK_MAC     (0x6B << 2)//(0x45<<2)
typedef struct
{
    u32 reg_ckg_ns        : 4;
    u32                   : 28;
    u32 reg_ckg_csi_mac           : 5;
    u32                       : 3;
    u32 reg_ckg_mac_lptx           : 5;
    u32                       : 19;
} clk_mac;

//---------------- SENSOR CLOCK ---------
/*
h0061	h0061	11	8	 reg_ckg_isp	3	0	4	h1	rw

clk_isp clock setting
[0]: disable clock
[1]: invert clock

[3:2]: Select clock source
00: 123.4 MHz
01: 86.4 MHz
10: 72 MHz
11: 54 MHz

h0062	h0062	12	8	 reg_ckg_sr_mclk	4	0	5	h1	rw

clk_sr_mclk clock setting (sensor main clock to ISP)
[0]: disable clock
[1]: invert clock

[4:2]: Select clock source
000: 27 MHz
001: 21.6 MHz
010: xtal (12) MHz
011: 5.4 MHz
100: 36 MHz
101: 54 MHz
110: 43.2 MHz
111: 61.7 MHz"


 */
#define OFFSET_CLKGEN_TO_CLK_SENSOR  (0x62<<2)
typedef enum  	//for reg_ckg_sr_mclk_select_clock_source
{
    SEN_MAIN_CLK_27M     = 0 ,
    SEN_MAIN_CLK_21P6M   = 1 ,
    SEN_MAIN_CLK_12M     = 2 ,
    SEN_MAIN_CLK_5P4M    = 3 ,
    SEN_MAIN_CLK_36M     = 4 ,
    SEN_MAIN_CLK_54M     = 5 ,
    SEN_MAIN_CLK_43P2M   = 6 ,
    SEN_MAIN_CLK_61P7M   = 7 ,
} SENSOR_MAIN_CLK;

typedef enum   //for reg_ckg_sr_select_clock_source
{
    clk_sr_from_sr_pad     = 0 ,
    clk_sr_from_mipi_atop   = 1 ,
    patgen_40MHz     = 2 ,
    patgen_86MHz    = 3 ,

} SENSOR_PCLK;

typedef struct
{
    u32 reg_ckg_sr_disable_clock     : 1;				//pixel clock
    u32 reg_ckg_sr_invert_clock    : 1;				//pixel clock
    u32 reg_ckg_sr_select_clock_source        : 2;		//enum SENSOR_PCLK
    u32                       : 4;
    u32 reg_ckg_sr_mclk_disable_clock     : 1;		//mclk
    u32 reg_ckg_sr_mclk_invert_clock : 1;			//mclk
    u32 reg_ckg_sr_mclk_select_clock_source        : 3; //enum SENSOR_MAIN_CLK
    u32                       : 19;
} clk_sensor;


//--------------- SENSOR MODE -------------

#define OFFSET_CHIPTOP_TO_SENSOR_MODE (0x06<<2)
#define OFFSET_CHIPTOP_TO_I2C0_MODE (0x09<<2)
typedef enum   //for reg_sr_mode
{
    SR_PAD_CFG_1 = 1,
    SR_PAD_CFG_2 = 2,
    SR_PAD_CFG_3 = 3,
    SR_PAD_CFG_10BITS = 4,
    SR_PAD_CFG_4 = 4,
    SR_PAD_CFG_12BITS = 5,
    SR_PAD_CFG_5 = 5,
    SR_PAD_CFG_6 = 6,
} SR_PAD_CFG;

typedef struct
{
    u32 reg_sr_mode           : 3;
    u32                       : 1;
    u32 reg_sr_i2c_mode       : 2;
    u32                       : 26;
} chiptop_sensor_mode;

#define OFFSET_CHIPTOP_TO_SENSOR_PAD (0x24<<2)
typedef struct
{
    u32 reg_sr_ie           : 6;
    u32                       : 26;
    u32 reg_sr_pe       : 6;
    u32                       : 26;
    u32 reg_sr_ps       : 6;
    u32                       : 26;
} chiptop_sensor_pad_control;

#define ISP_CMU_CLK_12M    CMU_TOP_CLK_12M
#define ISP_CMU_CLK_12P8M  CMU_TOP_CLK_12P8M
#define ISP_CMU_CLK_13P7M  CMU_TOP_CLK_13P7M
#define ISP_CMU_CLK_16M    CMU_TOP_CLK_16M
#define ISP_CMU_CLK_19P2M  CMU_TOP_CLK_19P2M
#define ISP_CMU_CLK_21P3M  CMU_TOP_CLK_21P3M
#define ISP_CMU_CLK_24M    CMU_TOP_CLK_24M
#define ISP_CMU_CLK_27P4M  CMU_TOP_CLK_27P4M
#define ISP_CMU_CLK_32M    CMU_TOP_CLK_32M
#define ISP_CMU_CLK_38P4M  CMU_TOP_CLK_38P4M
#define ISP_CMU_CLK_42P6M  CMU_TOP_CLK_42P6M
#define ISP_CMU_CLK_51P2M  CMU_TOP_CLK_51P2M
#define ISP_CMU_CLK_64M    CMU_TOP_CLK_64M
#define ISP_CMU_CLK_76P8M  CMU_TOP_CLK_76P8M
#define ISP_CMU_CLK_85P3M  CMU_TOP_CLK_85P3M
#define ISP_CMU_CLK_96M    CMU_TOP_CLK_96M
#define ISP_CMU_CLK_12M    CMU_TOP_CLK_12M
#define ISP_ASIC_CLK_128M  CMU_MMP_ASIC_CLK_128M

typedef enum
{
    ISP_SR_PWDN_0,
    ISP_SR_PWDN_1,
    ISP_SR_PWDN_2
} ISP_SR_PWDN;

typedef enum
{
    ISP_SR_RST_0,
    ISP_SR_RST_1,
    ISP_SR_RST_2
} ISP_SR_RST;

typedef enum
{
    ISP_SR_LEVEL_LOW     = 0,
    ISP_SR_LEVEL_HIGH    = 1,
} ISP_SR_LEVEL;

typedef enum
{
    BOARD_DATAPIN_0TO9 = 0, //
    BOARD_DATAPIN_2TO9 = 1,
    BOARD_DATAPIN_0TO7 = 2,
} BOARD_DATAPIN_CFG;


typedef enum
{
    CAM_STS_POWER_OFF = 0,
    CAM_STS_POWER_ON,
    CAM_STS_POWER_DOWN
} CAMSENSOR_STATE;

typedef enum
{
    TCAP_INIT_TO_FIRST_FRAME    = 0,
    TCAP_PREVIEW_TO_FIRST_FRAME,
    TCAP_CAPTURE_TO_FRIST_FRAME,
    TCAP_AE_SETTING,
    TCAP_AWB_SETTING,
    TCAP_AF_SETTING,
    TCAP_EFFECT_SETTING,
    TCAP_GENERAL,
    TCAP_END
} ISP_TCAP;

#if 0
typedef struct
{
    u32   reg_csimac_00      : 32;
    u32   reg_csimac_01      : 32;
    u32   reg_csimac_02      : 32;
    u32   reg_csimac_03      : 32;
    u32   reg_csimac_04      : 32;
    u32   reg_csimac_05      : 32;
    u32   reg_csimac_06      : 32;
    u32   reg_csimac_07      : 32;
    u32   reg_csimac_08      : 32;
    u32   reg_csimac_09      : 32;
    u32   reg_csimac_0A      : 32;
    u32   reg_csimac_0B      : 32;
    u32   reg_csimac_0C      : 32;
    u32   reg_csimac_0D      : 32;
    u32   reg_csimac_0E      : 32;
    u32   reg_csimac_0F      : 32;
    u32   reg_csimac_10      : 32;
    u32   reg_csimac_11      : 32;
    u32   reg_csimac_12      : 32;
    u32   reg_csimac_13      : 32;
    u32   reg_csimac_14      : 32;
    u32   reg_csimac_15      : 32;
    u32   reg_csimac_16      : 32;
    u32   reg_csimac_17      : 32;
    u32   reg_csimac_18      : 32;
    u32   reg_csimac_19      : 32;
    u32   reg_csimac_1A      : 32;
    u32   reg_csimac_1B      : 32;
    u32   reg_csimac_1C      : 32;
    u32   reg_csimac_1D      : 32;
    u32   reg_csimac_1E      : 32;
    u32   reg_csimac_1F      : 32;
    u32   reg_csimac_20      : 32;
    u32   reg_csimac_21      : 32;
    u32   reg_csimac_22      : 32;
    u32   reg_csimac_23      : 32;
    u32   reg_csimac_24      : 32;
    u32   reg_csimac_25      : 32;
    u32   reg_csimac_26      : 32;
    u32   reg_csimac_27      : 32;
    u32   reg_csimac_28      : 32;
    u32   reg_csimac_29      : 32;
    u32   reg_csimac_2A      : 32;
    u32   reg_csimac_2B      : 32;
    u32   reg_csimac_2C      : 32;
    u32   reg_csimac_2D      : 32;
    u32   reg_csimac_2E      : 32;
    u32   reg_csimac_2F      : 32;
    u32   reg_csimac_30      : 32;
    u32   reg_csimac_31      : 32;
    u32   reg_csimac_32      : 32;
    u32   reg_csimac_33      : 32;
    u32   reg_csimac_34      : 32;
    u32   reg_csimac_35      : 32;
    u32   reg_csimac_36      : 32;
    u32   reg_csimac_37      : 32;
    u32   reg_csimac_38      : 32;
    u32   reg_csimac_39      : 32;
    u32   reg_csimac_3A      : 32;
    u32   reg_csimac_3B      : 32;
    u32   reg_csimac_3C      : 32;
    u32   reg_csimac_3D      : 32;
    u32   reg_csimac_3E      : 32;
    u32   reg_csimac_3F      : 32;
    u32   reg_csimac_40      : 32;
    u32   reg_csimac_41      : 32;
    u32   reg_csimac_42      : 32;
    u32   reg_csimac_43      : 32;
    u32   reg_csimac_44      : 32;
    u32   reg_csimac_45      : 32;
    u32   reg_csimac_46      : 32;
    u32   reg_csimac_47      : 32;
    u32   reg_csimac_48      : 32;
    u32   reg_csimac_49      : 32;
    u32   reg_csimac_4A      : 32;
    u32   reg_csimac_4B      : 32;
    u32   reg_csimac_4C      : 32;
    u32   reg_csimac_4D      : 32;
    u32   reg_csimac_4E      : 32;
    u32   reg_csimac_4F      : 32;
    u32   reg_csimac_50      : 32;
    u32   reg_csimac_51      : 32;
    u32   reg_csimac_52      : 32;
    u32   reg_csimac_53      : 32;
    u32   reg_csimac_54      : 32;
    u32   reg_csimac_55      : 32;
    u32   reg_csimac_56      : 32;
    u32   reg_csimac_57      : 32;
    u32   reg_csimac_58      : 32;
    u32   reg_csimac_59      : 32;
    u32   reg_csimac_5A      : 32;
    u32   reg_csimac_5B      : 32;
    u32   reg_csimac_5C      : 32;
    u32   reg_csimac_5D      : 32;
    u32   reg_csimac_5E      : 32;
    u32   reg_csimac_5F      : 32;
} __attribute__((packed, aligned(4))) csimac_cfg_t;


typedef struct
{
    u32   reg_csidphy_00      : 32;
    u32   reg_csidphy_01      : 32;
    u32   reg_csidphy_02      : 32;
    u32   reg_csidphy_03      : 32;
    u32   reg_csidphy_04      : 32;
    u32   reg_csidphy_05      : 32;
    u32   reg_csidphy_06      : 32;
    u32   reg_csidphy_07      : 32;
    u32   reg_csidphy_08      : 32;
    u32   reg_csidphy_09      : 32;
    u32   reg_csidphy_0A      : 32;
    u32   reg_csidphy_0B      : 32;
    u32   reg_csidphy_0C      : 32;
    u32   reg_csidphy_0D      : 32;
    u32   reg_csidphy_0E      : 32;
    u32   reg_csidphy_0F      : 32;
    u32   reg_csidphy_10      : 32;
    u32   reg_csidphy_11      : 32;
    u32   reg_csidphy_12      : 32;
    u32   reg_csidphy_13      : 32;
    u32   reg_csidphy_14      : 32;
    u32   reg_csidphy_15      : 32;
    u32   reg_csidphy_16      : 32;
    u32   reg_csidphy_17      : 32;
    u32   reg_csidphy_18      : 32;
    u32   reg_csidphy_19      : 32;
    u32   reg_csidphy_1A      : 32;
    u32   reg_csidphy_1B      : 32;
    u32   reg_csidphy_1C      : 32;
    u32   reg_csidphy_1D      : 32;
    u32   reg_csidphy_1E      : 32;
    u32   reg_csidphy_1F      : 32;
    u32   reg_csidphy_20      : 32;
    u32   reg_csidphy_21      : 32;
    u32   reg_csidphy_22      : 32;
    u32   reg_csidphy_23      : 32;
    u32   reg_csidphy_24      : 32;
    u32   reg_csidphy_25      : 32;
    u32   reg_csidphy_26      : 32;
    u32   reg_csidphy_27      : 32;
    u32   reg_csidphy_28      : 32;
    u32   reg_csidphy_29      : 32;
    u32   reg_csidphy_2A      : 32;
    u32   reg_csidphy_2B      : 32;
    u32   reg_csidphy_2C      : 32;
    u32   reg_csidphy_2D      : 32;
    u32   reg_csidphy_2E      : 32;
    u32   reg_csidphy_2F      : 32;
    u32   reg_csidphy_30      : 32;
    u32   reg_csidphy_31      : 32;
    u32   reg_csidphy_32      : 32;
    u32   reg_csidphy_33      : 32;
    u32   reg_csidphy_34      : 32;
    u32   reg_csidphy_35      : 32;
    u32   reg_csidphy_36      : 32;
    u32   reg_csidphy_37      : 32;
    u32   reg_csidphy_38      : 32;
    u32   reg_csidphy_39      : 32;
    u32   reg_csidphy_3A      : 32;
    u32   reg_csidphy_3B      : 32;
    u32   reg_csidphy_3C      : 32;
    u32   reg_csidphy_3D      : 32;
    u32   reg_csidphy_3E      : 32;
    u32   reg_csidphy_3F      : 32;
    u32   reg_csidphy_40      : 32;
    u32   reg_csidphy_41      : 32;
    u32   reg_csidphy_42      : 32;
    u32   reg_csidphy_43      : 32;
    u32   reg_csidphy_44      : 32;
    u32   reg_csidphy_45      : 32;
    u32   reg_csidphy_46      : 32;
    u32   reg_csidphy_47      : 32;
    u32   reg_csidphy_48      : 32;
    u32   reg_csidphy_49      : 32;
    u32   reg_csidphy_4A      : 32;
    u32   reg_csidphy_4B      : 32;
    u32   reg_csidphy_4C      : 32;
    u32   reg_csidphy_4D      : 32;
    u32   reg_csidphy_4E      : 32;
    u32   reg_csidphy_4F      : 32;
    u32   reg_csidphy_50      : 32;
    u32   reg_csidphy_51      : 32;
    u32   reg_csidphy_52      : 32;
    u32   reg_csidphy_53      : 32;
    u32   reg_csidphy_54      : 32;
    u32   reg_csidphy_55      : 32;
    u32   reg_csidphy_56      : 32;
    u32   reg_csidphy_57      : 32;
    u32   reg_csidphy_58      : 32;
    u32   reg_csidphy_59      : 32;
    u32   reg_csidphy_5A      : 32;
    u32   reg_csidphy_5B      : 32;
    u32   reg_csidphy_5C      : 32;
    u32   reg_csidphy_5D      : 32;
    u32   reg_csidphy_5E      : 32;
    u32   reg_csidphy_5F      : 32;

} __attribute__((packed, aligned(4))) csidphy_cfg_t;
#endif

typedef enum
{
    SR_VOL_OFF,
    SR_VOL_1_8,
    SR_VOL_2_8
} SR_VOL;

typedef enum
{
    ISP_I2C_OFF = 0,
    ISP_I2C_0,
    ISP_I2C_1,
    ISP_I2C_EXTERNAL_0,
    ISP_I2C_EXTERNAL_1,
} ISP_I2C;

/*
  00: 123.4 MHz
  01: 86.4 MHz
  10: 72 MHz
  11: 54 MHz
*/
typedef enum
{
    ISP_CLK_123P4M = 0,
    ISP_CLK_86P4M = 1,
    ISP_CLK_72M = 2,
    ISP_CLK_54M = 3,
    ISP_CLK_144M = 4,
    ISP_CLK_192M = 5,
    ISP_CLK_216M = 6,
    ISP_CLK_240M = 7,
    ISP_CLK_OFF,
} ISP_CLK;

typedef enum
{
    CSI_CLK_108M = 0,
    CSI_CLK_86M = 1,
    CSI_CLK_144M = 2,
    CSI_CLK_172M = 3,
    CSI_CLK_216M = 4,
    CSI_CLK_288M = 5
} CSI_CLK;
/*
typedef enum { //for reg_sr_mode
    SR_PAD_CFG_1 = 1,
    SR_PAD_CFG_2 = 2,
    SR_PAD_CFG_3 = 3,
    SR_PAD_CFG_10BITS = 4,
    SR_PAD_CFG_4 = 4,
    SR_PAD_CFG_12BITS = 5,
    SR_PAD_CFG_5 = 5,
    SR_PAD_CFG_6 = 6,
}SR_PAD_CFG;
*/

/*! @brief Sensor master clock select */
typedef enum
{
    SR_ISP_MCLK_5P4M    = 0 ,    /**< Sensor MCLK 5.4MHz */
    SR_ISP_MCLK_12M     = 1 ,     /**< Sensor MCLK 12MHz */
    SR_ISP_MCLK_21P6M   = 2 ,   /**< Sensor MCLK 21.6MHz */
    SR_ISP_MCLK_27M     = 3 ,     /**< Sensor MCLK 27MHz */
    SR_ISP_MCLK_36M     = 4 ,     /**< Sensor MCLK 36MHz */
    SR_ISP_MCLK_43P2M   = 5 ,   /**< Sensor MCLK 43.2MHz */
    SR_ISP_MCLK_54M     = 6 ,     /**< Sensor MCLK 54MHz */
    SR_ISP_MCLK_61P7M   = 7 ,   /**< Sensor MCLK 61.7MHz */
    SR_ISP_MCLK_ISP_MAX = 128,  /**< Reserved , Do not use */
    SR_SCL_MCLK_36M = 129, /**< Sensor MCLK 36MHz from SCL */
    SR_SCL_MCLK_27M = 130, /**< Sensor MCLK 36MHz from SCL */
    SR_SCL_MCLK_37P125M = 131, /**< Sensor MCLK 36MHz from SCL */
    SR_SCL_MCLK_33M = 132, /**< Sensor MCLK 33MHz from SCL */
    SR_SCL_MCLK_34M = 133, /**< Sensor MCLK 34MHz from SCL */
    SR_SCL_MCLK_36P125M = 134, /**< Sensor MCLK 36.125MHz from SCL */
} SR_MCLK_FREQ;

#if 0
/*! @brief Select pixel clock source */
typedef enum
{
    ISP_PCLK_OFF = 0, /**< Disable pixel clock*/
    ISP_PCLK_SR_PAD,    /**< Pixel clock from parallel sensor intarface */
    ISP_PCLK_MIPI_TOP,  /**< Pixel clock from MIPI intarface */
    ISP_PCLK_40HZ,  /**< Reserved, Do not use*/
    ISP_PCLK_86HZ, /**< Reserved, Do not use*/
} ISP_PCLK_SOURCE;
#endif

typedef enum {
    CHIPTOP_SR0_PAR_DISABLE,
    CHIPTOP_SR0_PAR_MODE_1,
    CHIPTOP_SR0_PAR_MODE_2,
} CHIPTOP_SR0_PAR_MODE_e;

typedef enum {
    CHIPTOP_SR0_BT656_DISABLE,
    CHIPTOP_SR0_BT656_MODE_1,
    CHIPTOP_SR0_BT656_MODE_2,
    CHIPTOP_SR0_BT656_MODE_3,
    CHIPTOP_SR0_BT656_MODE_4,
} CHIPTOP_SR0_BT656_MODE_e;

typedef enum {
    CHIPTOP_SR1_BT656_DISABLE,
    CHIPTOP_SR1_BT656_MODE_1,
} CHIPTOP_SR1_BT656_MODE_e;

typedef enum {
    CHIPTOP_SR0_BT601_DISABLE,
    CHIPTOP_SR0_BT601_MODE_1,
    CHIPTOP_SR0_BT601_MODE_2,
    CHIPTOP_SR0_BT601_MODE_3,
    CHIPTOP_SR0_BT601_MODE_4,
} CHIPTOP_SR0_BT601_MODE_e;

typedef enum {
    CHIPTOP_SR0_MIPI_DISABLE,
    CHIPTOP_SR0_MIPI_MODE_1,
    CHIPTOP_SR0_MIPI_MODE_2,
} CHIPTOP_SR0_MIPI_MODE_e;

typedef enum {
    CHIPTOP_SR1_MIPI_DISABLE,
    CHIPTOP_SR1_MIPI_MODE_1,
    CHIPTOP_SR1_MIPI_MODE_2,
    CHIPTOP_SR1_MIPI_MODE_3,
    CHIPTOP_SR1_MIPI_MODE_4,
} CHIPTOP_SR1_MIPI_MODE_e;

typedef enum {
    CHIPTOP_I2C0,
    CHIPTOP_I2C1DUAL,
    CHIPTOP_I2C2,
    CHIPTOP_I2C3,
} CHIPTOP_I2C_SET_e;

typedef enum {
    CHIPTOP_I2C_DISABLE,
    CHIPTOP_I2C_MODE_1,
    CHIPTOP_I2C_MODE_2,
    CHIPTOP_I2C_MODE_3,
} CHIPTOP_I2C_MODE_e;

//void Select_SR_IOPad(u32 ulSnrPadNum, u32 ulSnrType, u32 ulSnrPadCfg);
void HalClkpad_Set_ISP_Clk(int ion, int iclkidx, int iratehz);
void HalClkpad_Set_SR_MCLK(int isensor_num, int ion, int iclkidx, int iratehz);
void HalClkpad_Set_SR_PCLK(int isensor_num, int ion, int iclkidx, int iratehz);
void HalClkpad_Set_CSI_MAC_CLK(int isensor_num, int ion, int iclkidx, int iratehz);
void HalClkpad_Set_CSI_NS_CLK(int isensor_num, int ion, int iclkidx, int iratehz);
void HalClkpad_Set_CSI_LPTX_CLK(int isensor_num, int ion, int iclkidx, int iratehz) ;
void Set_csi_if(bool, CSI_CLK);
//void Set_csi_clk_data_skip(u8 rx_clk_skip_ns, u8 rx_data_skip_ns);
//void Set_csi_lane(u16 lane);
//void Set_csi_vc0_hs_mode(u16 vc0_hs_mode);
//void Set_csi_long_packet(u64 enable);
void HalClkpad_Sensor0ParallelPad(CHIPTOP_SR0_PAR_MODE_e ssr0_par_mode);
void HalClkpad_Sensor0BT656Pad(CHIPTOP_SR0_BT656_MODE_e ssr0_bt656_mode);
void HalClkpad_Sensor1BT656Pad(CHIPTOP_SR1_BT656_MODE_e ssr1_bt656_mode);
void HalClkpad_Sensor0BT601Pad(CHIPTOP_SR0_BT601_MODE_e ssr0_bt601_mode);
void HalClkpad_Sensor0MIPIPad(CHIPTOP_SR0_MIPI_MODE_e ssr0_mipi_mode);
void HalClkpad_Sensor1MIPIPad(CHIPTOP_SR1_MIPI_MODE_e ssr1_mipi_mode);
void HalClkpad_I2CSetPad(CHIPTOP_I2C_SET_e si2c_set, CHIPTOP_I2C_MODE_e si2c_mode);

#ifdef __cplusplus
}
#endif

#endif //end of HAL_CLKPAD_H
