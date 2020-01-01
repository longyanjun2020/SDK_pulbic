////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    hal_io_chip.h
* @version
* @brief   HAL header for GPIO of main chip
*
*/

#ifndef __HAL_IO_CHIP_PUB_H__
#define __HAL_IO_CHIP_PUB_H__

/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define HalIoChipFastSetFunction(x) \
do{ \
    *(volatile u16*)(0x74000000+ (x >> 16)) = *(volatile u16*)(0x74000000+ (x >> 16)) & ~((x >> 8) & 0xFF) | (x & 0xFF); \
}while(0)

#define IO_CHIP_BACKLIGHT_EN  IO_CHIP_SDDL_BACKLIGHT_EN
#define IO_CHIP_BACKLIGHT_PWM IO_CHIP_SDDL_BACKLIGHT_PWM

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{     
  PAD_NUM_WL_STATE_GPIO_0_IN = 0x74007404,
  PAD_NUM_WL_PRIOR_GPIO_1_IN = 0x74007405,
  PAD_NUM_WL_FREQ_GPIO_2_IN = 0x74007408,
  PAD_NUM_WL_ACT_GPIO_3_IN = 0x74007409,
  PAD_NUM_MPIF_D2_GPIO_4_IN = 0x7400742d,
  PAD_NUM_MPIF_D1_GPIO_5_IN = 0x7400742c,
  PAD_NUM_MPIF_D3_GPIO_6_IN = 0x74007430,
  PAD_NUM_MPIF_BUSY_GPIO_7_IN = 0x74007428,
  PAD_NUM_MPIF_D0_GPIO_8_IN = 0x74007429,
  PAD_NUM_MPIF_CLK_GPIO_9_IN = 0x74007425,
  PAD_NUM_MPIF_GPIO2_GPIO_10_IN = 0x74007421,
  PAD_NUM_MPIF_GPIO1_GPIO_11_IN = 0x74007420,
  PAD_NUM_MPIF_CS0N_GPIO_12_IN = 0x74007424,
  PAD_NUM_BTIF_GPIO1_GPIO_13_IN = 0x74007400,
  PAD_NUM_BTIF_GPIO2_GPIO_14_IN = 0x74007401,
  PAD_NUM_SR_D_0_GPIO_15_IN = 0x740074a9,
  PAD_NUM_SR_D_1_GPIO_16_IN = 0x740074ac,
  PAD_NUM_SR_D_2_GPIO_17_IN = 0x740074ad,
  PAD_NUM_SR_D_3_GPIO_18_IN = 0x740074b0,
  PAD_NUM_SR_D_4_GPIO_19_IN = 0x740074b1,
  PAD_NUM_SR_D_5_GPIO_20_IN = 0x740074b4,
  PAD_NUM_SR_D_6_GPIO_21_IN = 0x740074b5,
  PAD_NUM_SR_D_7_GPIO_22_IN = 0x740074b8,
  PAD_NUM_SR_MCLK_GPIO_23_IN = 0x740074bc,
  PAD_NUM_SR_GPIO_GPIO_24_IN = 0x740074a8,
  PAD_NUM_SR_PCLK_GPIO_25_IN = 0x740074c4,
  PAD_NUM_SR_HSYNC_GPIO_26_IN = 0x740074b9,
  PAD_NUM_SR_VSYNC_GPIO_27_IN = 0x740074bd,
  PAD_NUM_SR_RST_GPIO_28_IN = 0x740074c0,
  PAD_NUM_SR_PWRDN_GPIO_29_IN = 0x740074c1,
  PAD_NUM_INT1_GPIO_87_IN = 0x74007415,
  PAD_NUM_U0RXD_GPIO_88_IN = 0x7400747d,
  PAD_NUM_U0TXD_GPIO_89_IN = 0x7400747c,
  PAD_NUM_I2CCLK_GPIO_90_IN = 0x740074c8,
  PAD_NUM_I2CDATA_GPIO_91_IN = 0x740074c9,
  PAD_NUM_CMMB_GPIO1_GPIO_92_IN = 0x74007418,
  PAD_NUM_CMMB_GPIO2_GPIO_93_IN = 0x74007419,
  PAD_NUM_CMMB_GPIO3_GPIO_94_IN = 0x7400741c,
  PAD_NUM_INT0_GPIO_95_IN = 0x74007414,
  PAD_NUM_SD_D_1_GPIO_96_IN = 0x74007461,
  PAD_NUM_SD_CLK_GPIO_97_IN = 0x74007469,
  PAD_NUM_SD_CDZ_GPIO_98_IN = 0x74007468,
  PAD_NUM_SD_D_0_GPIO_99_IN = 0x74007460,
  PAD_NUM_SD_CMD_GPIO_100_IN = 0x7400746c,
  PAD_NUM_SD_D_2_GPIO_101_IN = 0x74007464,
  PAD_NUM_SD_D_3_GPIO_102_IN = 0x74007465,
  PAD_NUM_LCD_D_7_GPIO_103_IN = 0x740074d9,
  PAD_NUM_LCD_D_12_GPIO_104_IN = 0x740074e4,
  PAD_NUM_LCD_D_15_GPIO_105_IN = 0x740074e9,
  PAD_NUM_LCD_D_14_GPIO_106_IN = 0x740074e8,
  PAD_NUM_LCD_D_6_GPIO_107_IN = 0x740074d8,
  PAD_NUM_LCD_RD_GPIO_108_IN = 0x740074f4,
  PAD_NUM_LCD_D_9_GPIO_109_IN = 0x740074dd,
  PAD_NUM_LCD_RSTZ_GPIO_110_IN = 0x740074f1,
  PAD_NUM_LCD_D_13_GPIO_111_IN = 0x740074e5,
  PAD_NUM_LCD_CMD_GPIO_112_IN = 0x740074f5,
  PAD_NUM_LCD_D_10_GPIO_113_IN = 0x740074e0,
  PAD_NUM_LCD_D_16_GPIO_114_IN = 0x740074ec,
  PAD_NUM_LCD_D_17_GPIO_115_IN = 0x740074ed,
  PAD_NUM_LCD_CS0_N_GPIO_116_IN = 0x740074f0,
  PAD_NUM_LCD_D_8_GPIO_117_IN = 0x740074dc,
  PAD_NUM_LCD_D_3_GPIO_118_IN = 0x740074d1,
  PAD_NUM_LCD_D_4_GPIO_119_IN = 0x740074d4,
  PAD_NUM_LCD_D_2_GPIO_120_IN = 0x740074d0,
  PAD_NUM_LCD_D_11_GPIO_121_IN = 0x740074e1,
  PAD_NUM_LCD_D_1_GPIO_122_IN = 0x740074cd,
  PAD_NUM_LCD_D_5_GPIO_123_IN = 0x740074d5,
  PAD_NUM_LCD_D_0_GPIO_124_IN = 0x740074cc,
  PAD_NUM_LCD_WR_GPIO_125_IN = 0x740074f8,
  PAD_NUM_I2SDIO_GPIO_130_IN = 0x74007471,
  PAD_NUM_I2SBCLK_GPIO_131_IN = 0x74007470,
  PAD_NUM_I2SWS_GPIO_132_IN = 0x74007474,
  PAD_NUM_ROW_0_GPIO_133_IN = 0x74007454,
  PAD_NUM_ROW_1_GPIO_134_IN = 0x74007455,
  PAD_NUM_ROW_2_GPIO_135_IN = 0x74007458,
  PAD_NUM_ROW_3_GPIO_136_IN = 0x74007459,
  PAD_NUM_ROW_4_GPIO_137_IN = 0x7400745c,
  PAD_NUM_ROW_5_GPIO_138_IN = 0x7400745d,
  PAD_NUM_COL_0_GPIO_139_IN = 0x74007444,
  PAD_NUM_COL_1_GPIO_140_IN = 0x74007445,
  PAD_NUM_COL_2_GPIO_141_IN = 0x74007448,
  PAD_NUM_COL_3_GPIO_142_IN = 0x74007449,
  PAD_NUM_COL_4_GPIO_143_IN = 0x7400744c,
  PAD_NUM_COL_5_GPIO_144_IN = 0x7400744d,
  PAD_NUM_COL_6_GPIO_145_IN = 0x74007450,
  PAD_NUM_USIM1DATA_GPIO_146_IN = 0x74007434,
  PAD_NUM_USIM1RST_GPIO_147_IN = 0x74007435,
  PAD_NUM_USIM1CLK_GPIO_148_IN = 0x74007438,
  PAD_NUM_USIM2RST_GPIO_149_IN = 0x7400743d,
  PAD_NUM_USIM2CLK_GPIO_150_IN = 0x74007440,
  PAD_NUM_USIM2DATA_GPIO_151_IN = 0x7400743c,
  PAD_NUM_TBUO0_GPIO_152_IN = 0x74007490,
  PAD_NUM_TBUO3_GPIO_153_IN = 0x74007495,
  PAD_NUM_TBUO6_GPIO_154_IN = 0x7400749c,
  PAD_NUM_TBUO2_GPIO_155_IN = 0x74007494,
  PAD_NUM_TBUO5_GPIO_156_IN = 0x74007499,
  PAD_NUM_TBUO4_GPIO_157_IN = 0x74007498,


  PAD_NUM_MPIF_GPIO1_F9_PWM0 = 0x66100703,
  PAD_NUM_BTIF_GPIO1_F10_PWM0 = 0x66100704,
  PAD_NUM_CMMB_GPIO3_F15_PWM0 = 0x66100702,
  PAD_NUM_LCD_D_16_F9_PWM0 = 0x66100705,
  PAD_NUM_I2SDIO_F12_PWM0 = 0x66100701,

  PAD_NUM_MPIF_GPIO2_F8_PWM1 = 0x66107030,
  PAD_NUM_CMMB_GPIO1_F17_PWM1 = 0x66107020,
  PAD_NUM_INT0_F9_PWM1 = 0x66107040,
  PAD_NUM_LCD_D_17_F10_PWM1 = 0x66107050,
  PAD_NUM_I2SWS_F10_PWM1 = 0x66107010,
  PAD_NUM_INVALID
} IoChipPadNum_e;

#endif //__HAL_IO_CHIP_PUB_H__

