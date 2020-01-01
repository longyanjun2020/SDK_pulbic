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

#ifndef __HAL_IO_CHIP_H__
#define __HAL_IO_CHIP_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mdl_pm.h"

#include "hal_io_chip_pub.h"
#include "drv_io_chip_pub_types.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define IO_PAD_DBB_PAD_NUM      (106)
#define IO_PAD_MMP_PAD_NUM      (0)

/* Macros to handle type IoChipReg_e */
#define PAD_SET_REG(base, offset)  (((base) << 9) | offset)
#define PAD_GET_REG_BASE(x)        (((x) & 0x00001E00) >> 9)
#define PAD_GET_REG_OFFSET(x)      (((x) & 0x000001FF) >> 0)
#define BASE_PAD_CTRL   0x00
#define BASE_GPIO_CTRL0 0x01
#define BASE_GPIO_CTRL1 0x02
#define BASE_GPIO_CTRL2 0x03
#define BASE_PSEUDO     0x04
#define BASE_INVALID    0x0F

/* Macros to handle type IoChipPadInfo_e */
#define PAD_INFO_SET_REG(x)  (((x) << 7) & 0x000FFF80)
#define PAD_INFO_GET_REG(x)  ((IoChipReg_e)(((x) & 0x000FFF80) >> 7))

#define PAD_INFO_SET_PE(x)   (((x) << 6) & 0x00000040)
#define PAD_INFO_GET_PE(x)   (((x) & 0x00000040) >> 6)
#define PE_YES 0x01
#define PE_NO  0x00

#define PAD_INFO_SET_PS(x)   (((x) << 5) & 0x00000020)
#define PAD_INFO_GET_PS(x)   (((x) & 0x00000020) >> 5)
#define PS_YES 0x01
#define PS_NO  0x00

#define PAD_INFO_SET_DRV(x)  (((x) << 4) & 0x00000010)
#define PAD_INFO_GET_DRV(x)  (((x) & 0x00000010) >> 4)
#define DRV_YES 0x01
#define DRV_NO  0x00

#define PAD_INFO_SET_DRV0(x) (((x) << 3) & 0x00000008)
#define PAD_INFO_GET_DRV0(x) (((x) & 0x00000008) >> 3)
#define DRV0_YES 0x01
#define DRV0_NO  0x00

#define PAD_INFO_SET_DRV1(x) (((x) << 2) & 0x00000004)
#define PAD_INFO_GET_DRV1(x) (((x) & 0x00000004) >> 2)
#define DRV1_YES 0x01
#define DRV1_NO  0x00

#define PAD_INFO_SET_RSEL(x) (((x) << 1) & 0x00000002)
#define PAD_INFO_GET_RSEL(x) (((x) & 0x00000002) >> 1)
#define RSEL_YES 0x01
#define RSEL_NO  0x00

#define PAD_INFO_SET_RPU(x)  (((x) << 0) & 0x00000001)
#define PAD_INFO_GET_RPU(x)  (((x) & 0x00000001) >> 0)
#define RPU_YES 0x01
#define RPU_NO  0x00

#define PAD_INFO_SET_ALL(reg, pe, ps, drv, drv0, drv1, rsel, rpu) (PAD_INFO_SET_REG(reg) | PAD_INFO_SET_PE(pe) | PAD_INFO_SET_PS(ps) | PAD_INFO_SET_DRV(drv) | PAD_INFO_SET_DRV0(drv0) | PAD_INFO_SET_DRV1(drv1) | PAD_INFO_SET_RSEL(rsel) | PAD_INFO_SET_RPU(rpu))

/* register definition */
#define GPIO_CTRL_IN   0x01
#define GPIO_CTRL_OUT  0x02
#define GPIO_CTRL_OEN  0x04
#define GPIO_CTRL_DRV1 0x08
#define GPIO_CTRL_PE   0x10
#define GPIO_CTRL_PS   0x20
#define GPIO_CTRL_DRV  0x40
#define GPIO_CTRL_MODE 0x80

/* invalid address for addreIoChipOnOffSetting_t*/
#define ADDRESS_INVALID 0x00000000
typedef enum
{
    IO_CHIP_OFF = 0,
    IO_CHIP_ON
}IoChipOnOff_e;

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{ 
    REG_26MHZ_OUT_MODE       = PAD_SET_REG(BASE_PAD_CTRL, 0x2C),
    REG_BT_PCM_MODE          = PAD_SET_REG(BASE_PAD_CTRL, 0x19),
    REG_BTIF_GPIO0_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x00),
    REG_BTIF_GPIO1_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x01),
    REG_BTIF_GPIO2_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x04),
    REG_BTIF_GPIO3_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x05),
    REG_BTIF_GPIO4_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x08),
    REG_BTIF_GPIO5_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x09),
    REG_BTIF_MODE            = PAD_SET_REG(BASE_PAD_CTRL, 0x04),
    REG_CMMB_GPIO0_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x18),
    REG_CMMB_GPIO1_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x19),
    REG_CMMB_GPIO2_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x1C),
    REG_COL7_MODE            = PAD_SET_REG(BASE_PAD_CTRL, 0x08),
    REG_COL_GPIO0_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0x44),
    REG_COL_GPIO1_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0x45),
    REG_COL_GPIO2_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0x48),
    REG_COL_GPIO3_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0x49),
    REG_COL_GPIO4_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0x4C),
    REG_COL_GPIO5_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0x4D),
    REG_COL_GPIO6_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0x50),
    REG_DBB_SPI_CS0_MODE     = PAD_SET_REG(BASE_PAD_CTRL, 0x54),
    REG_DBB_SPI_CS1_MODE     = PAD_SET_REG(BASE_PAD_CTRL, 0x55),
    REG_DBB_SPI_MODE         = PAD_SET_REG(BASE_PAD_CTRL, 0x54),
    REG_DBG_UART_MODE        = PAD_SET_REG(BASE_PAD_CTRL, 0x18),
    REG_DBG_UART_RTS_MODE    = PAD_SET_REG(BASE_PAD_CTRL, 0x18),
    REG_EFUSE_IN_EN          = PAD_SET_REG(BASE_PAD_CTRL, 0x05),
    REG_FUART_MODE           = PAD_SET_REG(BASE_PAD_CTRL, 0x19),
    REG_GPS_CLK_OUT2_MODE    = PAD_SET_REG(BASE_PAD_CTRL, 0x15),
    REG_GPS_CLK_OUT_MODE     = PAD_SET_REG(BASE_PAD_CTRL, 0x15),
    REG_I2C_EN               = PAD_SET_REG(BASE_PAD_CTRL, 0x1C),
    REG_I2C_GPIO0_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0xC8),
    REG_I2C_GPIO1_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0xC9),
    REG_I2S_GPIO0_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0x70),
    REG_I2S_GPIO1_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0x71),
    REG_I2S_GPIO2_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0x74),
    REG_KEY7X6_EN            = PAD_SET_REG(BASE_PAD_CTRL, 0x08),
    REG_LCD_CS0_MODE         = PAD_SET_REG(BASE_PAD_CTRL, 0x21),
    REG_LCD_CS1_MODE         = PAD_SET_REG(BASE_PAD_CTRL, 0x20),
    REG_LCD_FMARK_MODE       = PAD_SET_REG(BASE_PAD_CTRL, 0x21),
    REG_LCD_GPIO0_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0xCC),
    REG_LCD_GPIO10_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0xE0),
    REG_LCD_GPIO11_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0xE1),
    REG_LCD_GPIO12_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0xE4),
    REG_LCD_GPIO13_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0xE5),
    REG_LCD_GPIO14_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0xE8),
    REG_LCD_GPIO15_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0xE9),
    REG_LCD_GPIO16_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0xEC),
    REG_LCD_GPIO17_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0xED),
    REG_LCD_GPIO18_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0xF0),
    REG_LCD_GPIO19_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0xF1),
    REG_LCD_GPIO1_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0xCD),
    REG_LCD_GPIO20_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0xF4),
    REG_LCD_GPIO21_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0xF5),
    REG_LCD_GPIO22_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0xF8),
    REG_LCD_GPIO2_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0xD0),
    REG_LCD_GPIO3_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0xD1),
    REG_LCD_GPIO4_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0xD4),
    REG_LCD_GPIO5_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0xD5),
    REG_LCD_GPIO6_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0xD8),
    REG_LCD_GPIO7_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0xD9),
    REG_LCD_GPIO8_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0xDC),
    REG_LCD_GPIO9_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0xDD),
    REG_LCD_MODE             = PAD_SET_REG(BASE_PAD_CTRL, 0x20),
    REG_LCD_RS_MODE          = PAD_SET_REG(BASE_PAD_CTRL, 0x25),
    REG_MPIF_GPIO0_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x20),
    REG_MPIF_GPIO1_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x21),
    REG_MPIF_GPIO2_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x24),
    REG_MPIF_GPIO3_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x25),
    REG_MPIF_GPIO4_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x28),
    REG_MPIF_GPIO5_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x29),
    REG_MPIF_GPIO6_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x2C),
    REG_MPIF_GPIO7_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x2D),
    REG_MPIF_GPIO8_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x30),
    REG_MPIF_MODE            = PAD_SET_REG(BASE_PAD_CTRL, 0x04),
    REG_MSPI_CS0_MODE        = PAD_SET_REG(BASE_PAD_CTRL, 0x28),
    REG_MSPI_CS1_MODE        = PAD_SET_REG(BASE_PAD_CTRL, 0x28),
    REG_MSPI_MODE            = PAD_SET_REG(BASE_PAD_CTRL, 0x28),
    REG_PMUPWM_EN            = PAD_SET_REG(BASE_PAD_CTRL, 0x11),
    REG_PWM0_MODE            = PAD_SET_REG(BASE_PAD_CTRL, 0x10),
    REG_PWM1_MODE            = PAD_SET_REG(BASE_PAD_CTRL, 0x10),
    REG_PWM_IN_MODE          = PAD_SET_REG(BASE_PAD_CTRL, 0x05),
    REG_QBSAVE_MODE          = PAD_SET_REG(BASE_PAD_CTRL, 0x1C),
    REG_RF_GPIO0_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0x90),
    REG_RF_GPIO1_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0x91),
    REG_RF_GPIO2_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0x94),
    REG_RF_GPIO3_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0x95),
    REG_RF_GPIO4_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0x98),
    REG_RF_GPIO5_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0x99),
    REG_RF_GPIO6_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0x9C),
    REG_RF_GPIO7_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0x9D),
    REG_ROW6_MODE            = PAD_SET_REG(BASE_PAD_CTRL, 0x09),
    REG_ROW7_MODE            = PAD_SET_REG(BASE_PAD_CTRL, 0x09),
    REG_ROW_GPIO0_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0x54),
    REG_ROW_GPIO1_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0x55),
    REG_ROW_GPIO2_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0x58),
    REG_ROW_GPIO3_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0x59),
    REG_ROW_GPIO4_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0x5C),
    REG_ROW_GPIO5_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0x5D),
    REG_SD1_CDZ_EN           = PAD_SET_REG(BASE_PAD_CTRL, 0x0D),
    REG_SD1_MODE             = PAD_SET_REG(BASE_PAD_CTRL, 0x0D),
    REG_SD_CDZ_EN            = PAD_SET_REG(BASE_PAD_CTRL, 0x0C),
    REG_SD_GPIO0_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0x60),
    REG_SD_GPIO1_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0x61),
    REG_SD_GPIO2_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0x64),
    REG_SD_GPIO3_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0x65),
    REG_SD_GPIO4_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0x68),
    REG_SD_GPIO5_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0x69),
    REG_SD_GPIO6_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0x6C),
    REG_SD_MODE              = PAD_SET_REG(BASE_PAD_CTRL, 0x0C),
    REG_SERIAL_LCD_CS1_MODE  = PAD_SET_REG(BASE_PAD_CTRL, 0x25),
    REG_SERIAL_LCD_MODE      = PAD_SET_REG(BASE_PAD_CTRL, 0x24),
    REG_SIM1_EN              = PAD_SET_REG(BASE_PAD_CTRL, 0x04),
    REG_SIM1_GPIO0_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x34),
    REG_SIM1_GPIO1_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x35),
    REG_SIM1_GPIO2_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x38),
    REG_SIM2_EN              = PAD_SET_REG(BASE_PAD_CTRL, 0x04),
    REG_SIM2_GPIO0_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x3C),
    REG_SIM2_GPIO1_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x3D),
    REG_SIM2_GPIO2_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x40),
    REG_SPI_SR_EN            = PAD_SET_REG(BASE_PAD_CTRL, 0x1C),
    REG_SR_EN                = PAD_SET_REG(BASE_PAD_CTRL, 0x1C),
    REG_SR_GPIO0_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0xA8),
    REG_SR_GPIO10_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0xBC),
    REG_SR_GPIO11_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0xBD),
    REG_SR_GPIO12_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0xC0),
    REG_SR_GPIO13_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0xC1),
    REG_SR_GPIO14_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0xC4),
    REG_SR_GPIO1_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0xA9),
    REG_SR_GPIO2_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0xAC),
    REG_SR_GPIO3_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0xAD),
    REG_SR_GPIO4_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0xB0),
    REG_SR_GPIO5_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0xB1),
    REG_SR_GPIO6_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0xB4),
    REG_SR_GPIO7_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0xB5),
    REG_SR_GPIO8_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0xB8),
    REG_SR_GPIO9_MODE        = PAD_SET_REG(BASE_GPIO_CTRL0, 0xB9),
    REG_TBUO_EN              = PAD_SET_REG(BASE_PAD_CTRL, 0x2C),
    REG_UART_GPIO0_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x7C),
    REG_UART_GPIO1_MODE      = PAD_SET_REG(BASE_GPIO_CTRL0, 0x7D),
    REG_WIFI_ANTENNA_MODE    = PAD_SET_REG(BASE_PAD_CTRL, 0x05),
    REG_WIFI_CLK_EN_MODE     = PAD_SET_REG(BASE_PAD_CTRL, 0xA0),
    REG_INT_GPIO0_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0x14),
    REG_INT_GPIO1_MODE       = PAD_SET_REG(BASE_GPIO_CTRL0, 0x15),
    REG_INVALID              = PAD_SET_REG(BASE_INVALID, 0xFF),
} IoChipReg_e;

typedef enum
{ 
    PAD_INFO_WL_STATE       = PAD_INFO_SET_ALL(      REG_BTIF_GPIO2_MODE, PE_YES, PS_YES, DRV_YES,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 0
    PAD_INFO_WL_PRIOR       = PAD_INFO_SET_ALL(      REG_BTIF_GPIO3_MODE, PE_YES, PS_YES, DRV_YES,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 1
    PAD_INFO_WL_FREQ        = PAD_INFO_SET_ALL(      REG_BTIF_GPIO4_MODE, PE_YES, PS_YES, DRV_YES,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 2
    PAD_INFO_WL_ACT         = PAD_INFO_SET_ALL(      REG_BTIF_GPIO5_MODE, PE_YES, PS_YES, DRV_YES,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 3
    PAD_INFO_MPIF_D2        = PAD_INFO_SET_ALL(      REG_MPIF_GPIO7_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 4
    PAD_INFO_MPIF_D1        = PAD_INFO_SET_ALL(      REG_MPIF_GPIO6_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 5
    PAD_INFO_MPIF_D3        = PAD_INFO_SET_ALL(      REG_MPIF_GPIO8_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 6
    PAD_INFO_MPIF_BUSY      = PAD_INFO_SET_ALL(      REG_MPIF_GPIO4_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 7
    PAD_INFO_MPIF_D0        = PAD_INFO_SET_ALL(      REG_MPIF_GPIO5_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 8
    PAD_INFO_MPIF_CLK       = PAD_INFO_SET_ALL(      REG_MPIF_GPIO3_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 9
    PAD_INFO_MPIF_GPIO2     = PAD_INFO_SET_ALL(      REG_MPIF_GPIO1_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 10
    PAD_INFO_MPIF_GPIO1     = PAD_INFO_SET_ALL(      REG_MPIF_GPIO0_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 11
    PAD_INFO_MPIF_CS0N      = PAD_INFO_SET_ALL(      REG_MPIF_GPIO2_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 12
    PAD_INFO_BTIF_GPIO1     = PAD_INFO_SET_ALL(      REG_BTIF_GPIO0_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 13
    PAD_INFO_BTIF_GPIO2     = PAD_INFO_SET_ALL(      REG_BTIF_GPIO1_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 14
    PAD_INFO_SR_D_0         = PAD_INFO_SET_ALL(        REG_SR_GPIO1_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 15
    PAD_INFO_SR_D_1         = PAD_INFO_SET_ALL(        REG_SR_GPIO2_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 16
    PAD_INFO_SR_D_2         = PAD_INFO_SET_ALL(        REG_SR_GPIO3_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 17
    PAD_INFO_SR_D_3         = PAD_INFO_SET_ALL(        REG_SR_GPIO4_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 18
    PAD_INFO_SR_D_4         = PAD_INFO_SET_ALL(        REG_SR_GPIO5_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 19
    PAD_INFO_SR_D_5         = PAD_INFO_SET_ALL(        REG_SR_GPIO6_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 20
    PAD_INFO_SR_D_6         = PAD_INFO_SET_ALL(        REG_SR_GPIO7_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 21
    PAD_INFO_SR_D_7         = PAD_INFO_SET_ALL(        REG_SR_GPIO8_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 22
    PAD_INFO_SR_MCLK        = PAD_INFO_SET_ALL(       REG_SR_GPIO10_MODE, PE_YES,  PS_NO, DRV_YES,  DRV0_NO,  DRV1_NO, RSEL_YES, RPU_NO ), // 23
    PAD_INFO_SR_GPIO        = PAD_INFO_SET_ALL(        REG_SR_GPIO0_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 24
    PAD_INFO_SR_PCLK        = PAD_INFO_SET_ALL(       REG_SR_GPIO14_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 25
    PAD_INFO_SR_HSYNC       = PAD_INFO_SET_ALL(        REG_SR_GPIO9_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 26
    PAD_INFO_SR_VSYNC       = PAD_INFO_SET_ALL(       REG_SR_GPIO11_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 27
    PAD_INFO_SR_RST         = PAD_INFO_SET_ALL(       REG_SR_GPIO12_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 28
    PAD_INFO_SR_PWRDN       = PAD_INFO_SET_ALL(       REG_SR_GPIO13_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 29
    PAD_INFO_BLEDOD         = PAD_INFO_SET_ALL(              REG_INVALID,  PE_NO,  PS_NO,  DRV_NO,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 82
    PAD_INFO_GLEDOD         = PAD_INFO_SET_ALL(              REG_INVALID,  PE_NO,  PS_NO,  DRV_NO,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 83
    PAD_INFO_RLEDOD         = PAD_INFO_SET_ALL(              REG_INVALID,  PE_NO,  PS_NO,  DRV_NO,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 84
    PAD_INFO_VIB            = PAD_INFO_SET_ALL(              REG_INVALID,  PE_NO,  PS_NO,  DRV_NO,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 85
    PAD_INFO_KEYLED         = PAD_INFO_SET_ALL(              REG_INVALID,  PE_NO,  PS_NO,  DRV_NO,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 86
    PAD_INFO_INT1           = PAD_INFO_SET_ALL(       REG_INT_GPIO1_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 87
    PAD_INFO_U0RXD          = PAD_INFO_SET_ALL(      REG_UART_GPIO1_MODE,  PE_NO,  PS_NO, DRV_YES,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 88
    PAD_INFO_U0TXD          = PAD_INFO_SET_ALL(      REG_UART_GPIO0_MODE,  PE_NO,  PS_NO, DRV_YES,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 89
    PAD_INFO_I2CCLK         = PAD_INFO_SET_ALL(       REG_I2C_GPIO0_MODE,  PE_NO,  PS_NO,  DRV_NO,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 90
    PAD_INFO_I2CDATA        = PAD_INFO_SET_ALL(       REG_I2C_GPIO1_MODE,  PE_NO,  PS_NO,  DRV_NO,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 91
    PAD_INFO_CMMB_GPIO1     = PAD_INFO_SET_ALL(      REG_CMMB_GPIO0_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 92
    PAD_INFO_CMMB_GPIO2     = PAD_INFO_SET_ALL(      REG_CMMB_GPIO1_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 93
    PAD_INFO_CMMB_GPIO3     = PAD_INFO_SET_ALL(      REG_CMMB_GPIO2_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 94
    PAD_INFO_INT0           = PAD_INFO_SET_ALL(       REG_INT_GPIO0_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 95
    PAD_INFO_SD_D_1         = PAD_INFO_SET_ALL(        REG_SD_GPIO1_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 96
    PAD_INFO_SD_CLK         = PAD_INFO_SET_ALL(        REG_SD_GPIO5_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 97
    PAD_INFO_SD_CDZ         = PAD_INFO_SET_ALL(        REG_SD_GPIO4_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 98
    PAD_INFO_SD_D_0         = PAD_INFO_SET_ALL(        REG_SD_GPIO0_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 99
    PAD_INFO_SD_CMD         = PAD_INFO_SET_ALL(        REG_SD_GPIO6_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 100
    PAD_INFO_SD_D_2         = PAD_INFO_SET_ALL(        REG_SD_GPIO2_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 101
    PAD_INFO_SD_D_3         = PAD_INFO_SET_ALL(        REG_SD_GPIO3_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 102
    PAD_INFO_LCD_D_7        = PAD_INFO_SET_ALL(       REG_LCD_GPIO7_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 103
    PAD_INFO_LCD_D_12       = PAD_INFO_SET_ALL(      REG_LCD_GPIO12_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 104
    PAD_INFO_LCD_D_15       = PAD_INFO_SET_ALL(      REG_LCD_GPIO15_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 105
    PAD_INFO_LCD_D_14       = PAD_INFO_SET_ALL(      REG_LCD_GPIO14_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 106
    PAD_INFO_LCD_D_6        = PAD_INFO_SET_ALL(       REG_LCD_GPIO6_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 107
    PAD_INFO_LCD_RD         = PAD_INFO_SET_ALL(      REG_LCD_GPIO20_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 108
    PAD_INFO_LCD_D_9        = PAD_INFO_SET_ALL(       REG_LCD_GPIO9_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 109
    PAD_INFO_LCD_RSTZ       = PAD_INFO_SET_ALL(      REG_LCD_GPIO19_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 110
    PAD_INFO_LCD_D_13       = PAD_INFO_SET_ALL(      REG_LCD_GPIO13_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 111
    PAD_INFO_LCD_CMD        = PAD_INFO_SET_ALL(      REG_LCD_GPIO21_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 112
    PAD_INFO_LCD_D_10       = PAD_INFO_SET_ALL(      REG_LCD_GPIO10_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 113
    PAD_INFO_LCD_D_16       = PAD_INFO_SET_ALL(      REG_LCD_GPIO16_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 114
    PAD_INFO_LCD_D_17       = PAD_INFO_SET_ALL(      REG_LCD_GPIO17_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 115
    PAD_INFO_LCD_CS0_N      = PAD_INFO_SET_ALL(      REG_LCD_GPIO18_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 116
    PAD_INFO_LCD_D_8        = PAD_INFO_SET_ALL(       REG_LCD_GPIO8_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 117
    PAD_INFO_LCD_D_3        = PAD_INFO_SET_ALL(       REG_LCD_GPIO3_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 118
    PAD_INFO_LCD_D_4        = PAD_INFO_SET_ALL(       REG_LCD_GPIO4_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 119
    PAD_INFO_LCD_D_2        = PAD_INFO_SET_ALL(       REG_LCD_GPIO2_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 120
    PAD_INFO_LCD_D_11       = PAD_INFO_SET_ALL(      REG_LCD_GPIO11_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 121
    PAD_INFO_LCD_D_1        = PAD_INFO_SET_ALL(       REG_LCD_GPIO1_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 122
    PAD_INFO_LCD_D_5        = PAD_INFO_SET_ALL(       REG_LCD_GPIO5_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 123
    PAD_INFO_LCD_D_0        = PAD_INFO_SET_ALL(       REG_LCD_GPIO0_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 124
    PAD_INFO_LCD_WR         = PAD_INFO_SET_ALL(      REG_LCD_GPIO22_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 125
    PAD_INFO_AUXADC0        = PAD_INFO_SET_ALL(              REG_INVALID,  PE_NO,  PS_NO,  DRV_NO,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 126
    PAD_INFO_AUXADC1        = PAD_INFO_SET_ALL(              REG_INVALID,  PE_NO,  PS_NO,  DRV_NO,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 127
    PAD_INFO_AUXADC2        = PAD_INFO_SET_ALL(              REG_INVALID,  PE_NO,  PS_NO,  DRV_NO,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 128
    PAD_INFO_AUXADC3        = PAD_INFO_SET_ALL(              REG_INVALID,  PE_NO,  PS_NO,  DRV_NO,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 129
    PAD_INFO_I2SDIO         = PAD_INFO_SET_ALL(       REG_I2S_GPIO1_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 130
    PAD_INFO_I2SBCLK        = PAD_INFO_SET_ALL(       REG_I2S_GPIO0_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 131
    PAD_INFO_I2SWS          = PAD_INFO_SET_ALL(       REG_I2S_GPIO2_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 132
    PAD_INFO_ROW_0          = PAD_INFO_SET_ALL(       REG_ROW_GPIO0_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 133
    PAD_INFO_ROW_1          = PAD_INFO_SET_ALL(       REG_ROW_GPIO1_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 134
    PAD_INFO_ROW_2          = PAD_INFO_SET_ALL(       REG_ROW_GPIO2_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 135
    PAD_INFO_ROW_3          = PAD_INFO_SET_ALL(       REG_ROW_GPIO3_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 136
    PAD_INFO_ROW_4          = PAD_INFO_SET_ALL(       REG_ROW_GPIO4_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 137
    PAD_INFO_ROW_5          = PAD_INFO_SET_ALL(       REG_ROW_GPIO5_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 138
    PAD_INFO_COL_0          = PAD_INFO_SET_ALL(       REG_COL_GPIO0_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 139
    PAD_INFO_COL_1          = PAD_INFO_SET_ALL(       REG_COL_GPIO1_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 140
    PAD_INFO_COL_2          = PAD_INFO_SET_ALL(       REG_COL_GPIO2_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 141
    PAD_INFO_COL_3          = PAD_INFO_SET_ALL(       REG_COL_GPIO3_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 142
    PAD_INFO_COL_4          = PAD_INFO_SET_ALL(       REG_COL_GPIO4_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 143
    PAD_INFO_COL_5          = PAD_INFO_SET_ALL(       REG_COL_GPIO5_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 144
    PAD_INFO_COL_6          = PAD_INFO_SET_ALL(       REG_COL_GPIO6_MODE, PE_YES, PS_YES,  DRV_NO, DRV0_YES, DRV1_YES,  RSEL_NO, RPU_NO ), // 145
    PAD_INFO_USIM1DATA      = PAD_INFO_SET_ALL(      REG_SIM1_GPIO0_MODE, PE_YES, PS_YES, DRV_YES,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 146
    PAD_INFO_USIM1RST       = PAD_INFO_SET_ALL(      REG_SIM1_GPIO1_MODE, PE_YES, PS_YES, DRV_YES,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 147
    PAD_INFO_USIM1CLK       = PAD_INFO_SET_ALL(      REG_SIM1_GPIO2_MODE, PE_YES, PS_YES, DRV_YES,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 148
    PAD_INFO_USIM2RST       = PAD_INFO_SET_ALL(      REG_SIM2_GPIO1_MODE, PE_YES, PS_YES, DRV_YES,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 149
    PAD_INFO_USIM2CLK       = PAD_INFO_SET_ALL(      REG_SIM2_GPIO2_MODE, PE_YES, PS_YES, DRV_YES,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 150
    PAD_INFO_USIM2DATA      = PAD_INFO_SET_ALL(      REG_SIM2_GPIO0_MODE, PE_YES, PS_YES, DRV_YES,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 151
    PAD_INFO_TBUO0          = PAD_INFO_SET_ALL(        REG_RF_GPIO0_MODE, PE_YES, PS_YES, DRV_YES,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 152
    PAD_INFO_TBUO3          = PAD_INFO_SET_ALL(        REG_RF_GPIO3_MODE, PE_YES, PS_YES, DRV_YES,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 153
    PAD_INFO_TBUO6          = PAD_INFO_SET_ALL(        REG_RF_GPIO6_MODE, PE_YES, PS_YES, DRV_YES,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 154
    PAD_INFO_TBUO2          = PAD_INFO_SET_ALL(        REG_RF_GPIO2_MODE, PE_YES, PS_YES, DRV_YES,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 155
    PAD_INFO_TBUO5          = PAD_INFO_SET_ALL(        REG_RF_GPIO5_MODE, PE_YES, PS_YES, DRV_YES,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 156
    PAD_INFO_TBUO4          = PAD_INFO_SET_ALL(        REG_RF_GPIO4_MODE, PE_YES, PS_YES, DRV_YES,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 157
    PAD_INFO_VMSEL          = PAD_INFO_SET_ALL(              REG_INVALID,  PE_NO,  PS_NO,  DRV_NO,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 158
    PAD_INFO_BOOTCTL0       = PAD_INFO_SET_ALL(              REG_INVALID,  PE_NO,  PS_NO,  DRV_NO,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 159
    PAD_INFO_BOOTCTL1       = PAD_INFO_SET_ALL(              REG_INVALID,  PE_NO,  PS_NO,  DRV_NO,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 160
    PAD_INFO_BOOTCTL2       = PAD_INFO_SET_ALL(              REG_INVALID,  PE_NO,  PS_NO,  DRV_NO,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 161
    PAD_INFO_BOOTCTL3       = PAD_INFO_SET_ALL(              REG_INVALID,  PE_NO,  PS_NO,  DRV_NO,  DRV0_NO,  DRV1_NO,  RSEL_NO, RPU_NO ), // 162
    PAD_INFO_INVALID        = 0x7fffffff,  
} IoChipPadInfo_e;

typedef enum
{
    PAD_DOMAIN_VDDIO_L1,
    PAD_DOMAIN_VDDIO_B1,
    PAD_DOMAIN_VDDIOLCD,
    PAD_DOMAIN_VDDIO_R1,
    PAD_DOMAIN_AVDDVSIM1,
    PAD_DOMAIN_AVDDVSIM2,
    
    PAD_DOMAIN_INVALID,        // 12
} IoChipPowerDomain_e;

typedef enum
{
    ePWM_0 = 0,
    ePWM_1,
    eMAX_PWM,
} PWM_NUM_e; 

typedef struct
{
    u16 *pnAddr;
    u16  nMask;
    u16  nValue;
} IoChipPadInitReg_t;

typedef struct
{
  IoChipReg_e eReg;
  u8          nValue;
  u8          nShadow;
} IoChipSleepSetting_t;

typedef struct
{
  IoChipSignalIndex_e ePadNum;
  IoChipReg_e eReg;
  u8          nValue;
  u8          nShadow;
} IoChipSleepSetting_e;

typedef enum
{
    eIoPullDefault = 0,
    eIoPullPass,
}IoChipPullSetting_e;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
extern void Hal_IoChipInit(void);
extern void Hal_IoChipSetGpioDirReg(IoChipPadNum_e ePadNum);
extern VmIoState_e Hal_IoChipGetGpioInReg(IoChipPadNum_e ePadNum);
extern void Hal_IoChipSetGpioOutReg(IoChipPadNum_e ePadNum, bool bSetHigh);
extern void Hal_IoChipSetMuxReg(IoChipPadNum_e ePadNum);
extern void Hal_IoChipSetMuxRegInput(IoChipPadNum_e ePadNum);
extern bool Hal_IoChipSetPullReg(IoChipPadNum_e ePadNum, IoChipPull_e ePull);
extern bool Hal_IoChipSetSlewRateReg(IoChipPadNum_e ePadNum, IoChipDrive_e eDrive);
extern void Hal_IoChipEnterSleepMode(void);
extern void Hal_IoChipLeaveSleepMode(void);
extern void Hal_IoChipLcdOnOff(IoChipOnOff_e eOn);
extern MdlPmPowerDomain_e Hal_IoChipGetPmPadDomain(IoChipPowerDomain_e eDomain);
extern IoChipPowerDomain_e Hal_IoChipPadPowerEnable(IoChipPadNum_e ePadNum);
extern IoChipPowerDomain_e Hal_IoChipPadPowerDisable(IoChipPadNum_e ePadNum);
extern bool Hal_IoChipValidatePadNum(IoChipPadNum_e ePadNum);
extern IoChipPadNum_e Hal_IoChipFindDefaultIn(IoChipPadNum_e ePadNum);
extern IoChipPadNum_e Hal_IoChipFindDefaultOut(IoChipPadNum_e ePadNum);
extern PWM_NUM_e Hal_IoChipGetPwmNumber(IoChipPadNum_e ePadNum);
extern VmIoErrorCode_e HalIoChipPWMSetting(u8 pwm_no, bool en, vm_IoPwmParam_t *ptIoPwmParam);
extern bool Hal_IoChipTestOut24Bit(u32 nTestBus24bSel, u32 nTestOutMode);
extern bool Hal_IoChipTestOutSingleClock(u32 nOutBit, u32 nDivider);
extern u8 *Hal_IoChipGetGpioCtrlReg(u32 nPadNum);
void Hal_IoChipLockSlewRate(IoChipPadNum_e ePadNum);

#ifdef __FAST_GPIO_ACCESS__
VmIoErrorCode_e HalIoChipGetGPIORegAddr(IoChipPadNum_e ePadNum,u32 *addr);

#define HalIoChipFastDwnGpio(x) \
do { \
    if((x & 0x3400C100) != 0x3400C100){\
	(*(volatile u8 *)x) &= ~GPIO_CTRL_OUT; \
    }else{\
        (*(volatile u32 *)0x3400C1D4) &= ~(0x10<<(x&3));\
    }\
}while(0)

#define HalIoChipFastUpGpio(x) \
do { \
    if((x & 0x3400C100) != 0x3400C100){\
	    (*(volatile u8 *)x) |= GPIO_CTRL_OUT; \
    }else{\
        (*(volatile u32 *)0x3400C1D4) |= (0x10<<(x&3));\
    }\
}while(0)

#define HalIoChipFastSetDirInputGpio(x) \
do { \
    if((x & 0x3400C100) != 0x3400C100){\
        (*(volatile u8 *)x) |= (GPIO_CTRL_OEN); \
        (*(volatile u8 *)x) |= GPIO_CTRL_MODE; \
    }else{\
            (*(volatile u32 *)0x3400C184) |= 0x4000;\
        (*(volatile u32 *)0x3400C1E8) |= (1<<4);\
        (*(volatile u32 *)0x3400C1E4) |= (1<<4);\
        (*(volatile u32 *)0x3400C184) |= 1;\
        *(volatile u32*) 0x3400C1B4 = 0x79;\
        if(x&3 == 0)\
            (*(volatile u32 *)0x3400C1D4)  |= (1<<0);\
        else\
            (*(volatile u32 *)0x3400C1E8) &= ~((1<<11)<<(x&3));\
    }\
}while(0)

#define HalIoChipFastAcqGpio(x)  ((x & 0x3400C100) == 0x3400C100)?((*(volatile u32 *)0x3400C1D4) & (0x100 << (x&3))) >> (8 + (x&3)):(*(volatile u8 *)x) & GPIO_CTRL_IN

#define HalIoChipFastSetDirOutputGpio(x, y) \
do { \
    if((x & 0x3400C100) == 0x3400C100){\
        (*(volatile u32 *)0x3400C184) |= 0x4000;\
        (*(volatile u32 *)0x3400C1E8) |= (1<<4);\
        (*(volatile u32 *)0x3400C1E4) |= (1<<4);\
        (*(volatile u32 *)0x3400C184) |= 1;\
        *(volatile u32*) 0x3400C1B4 = 0x79;\
         (*(volatile u32 *)0x3400C1D4) &= ~(0x10<<(x&3));\
         (*(volatile u32 *)0x3400C1D4) |= ((y<<4)<<(x&3));\
        if(x&3 == 0)\
            (*(volatile u32 *)0x3400C1D4)  &= ~(1<<0);\
        else\
            (*(volatile u32 *)0x3400C1E8) |= ((1<<11)<<(x&3));\
    }else{\
        if(y != VM_IO_SKIP){ \
            (*(volatile u8 *)x) &= ~GPIO_CTRL_OUT; \
            (*(volatile u8 *)x) |= y << 1; \
        } \
        (*(volatile u8 *)x) &= ~GPIO_CTRL_OEN; \
        (*(volatile u8 *)x) |= GPIO_CTRL_MODE; \
    }\
}while(0)
#endif

#endif //__HAL_IO_CHIP_H__

