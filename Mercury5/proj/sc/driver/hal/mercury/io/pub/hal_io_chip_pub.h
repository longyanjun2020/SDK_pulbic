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
#define IO_PAD_DBB_PAD_NUM      (106)
#define IO_PAD_MMP_PAD_NUM      (0)

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

/* Macros to handle type IoChipPadNum_e */
#define PAD_NUM_SET_NUM(x)  (((x) << 16) & 0x00FF0000)
#define PAD_NUM_GET_NUM(x)  (((x) & 0x00FF0000) >> 16)

#define PAD_NUM_SET_SRC(x)  (((x) << 14) & 0x0000C000)
#define PAD_NUM_GET_SRC(x)  (((x) & 0x0000C000) >> 14)
#define PAD_NUM_SRC_DBB     0x00UL
#define PAD_NUM_SRC_MMP     0x01UL
#define PAD_NUM_SRC_PMU     0x02UL

#define PAD_NUM_SET_FUN(x)  (((x) << 9) & 0x00003E00)
#define PAD_NUM_GET_FUN(x)  (((x) & 0x00003E00) >> 9)

#define PAD_NUM_SET_PE(x)   (((x) << 8) & 0x00000100)
#define PAD_NUM_GET_PE(x)   (((x) & 0x00000100) >> 8)

#define PAD_NUM_SET_PS(x)   (((x) << 7) & 0x00000080)
#define PAD_NUM_GET_PS(x)   (((x) & 0x00000080) >> 7)

#define PAD_NUM_SET_DRV(x)  (((x) << 6) & 0x00000040)
#define PAD_NUM_GET_DRV(x)  (((x) & 0x00000040) >> 6)

#define PAD_NUM_SET_DRV0(x) (((x) << 5) & 0x00000020)
#define PAD_NUM_GET_DRV0(x) (((x) & 0x00000020) >> 5)

#define PAD_NUM_SET_DRV1(x) (((x) << 4) & 0x00000010)
#define PAD_NUM_GET_DRV1(x) (((x) & 0x00000010) >> 4)

#define PAD_NUM_SET_RSEL(x) (((x) << 3) & 0x00000008)
#define PAD_NUM_GET_RSEL(x) (((x) & 0x00000008) >> 3)

#define PAD_NUM_SET_RPU(x)  (((x) << 2) & 0x00000004)
#define PAD_NUM_GET_RPU(x)  (((x) & 0x00000004) >> 2)

#define PAD_NUM_SET_GPIO(x) (((x) << 1) & 0x00000002)
#define PAD_NUM_GET_GPIO(x) (((x) & 0x00000002) >> 1)
#define PAD_NUM_GPIO_NO     0x00UL
#define PAD_NUM_GPIO_YES    0x01UL

#define PAD_NUM_SET_DIR(x)  (((x) << 0) & 0x00000001)
#define PAD_NUM_GET_DIR(x)  (((x) & 0x00000001) >> 0)
#define PAD_NUM_DIR_IN      0x00UL
#define PAD_NUM_DIR_OUT     0x01UL

#define PAD_NUM_CONFIG(num, src, fun, pe, ps, drv, drv0, drv1, rsel, rpu, gpio, dir) (PAD_NUM_SET_NUM(num) | PAD_NUM_SET_SRC(src) | PAD_NUM_SET_FUN(fun) | PAD_NUM_SET_PE(pe) | PAD_NUM_SET_PS(ps) | PAD_NUM_SET_DRV(drv) | PAD_NUM_SET_DRV0(drv0) | PAD_NUM_SET_DRV1(drv1) | PAD_NUM_SET_RSEL(rsel) | PAD_NUM_SET_RPU(rpu) | PAD_NUM_SET_GPIO(gpio) | PAD_NUM_SET_DIR(dir))

#define PAD_NUM_GPIO_IN(num, src, fun, pe, ps, drv, drv0, drv1, rsel, rpu)           PAD_NUM_CONFIG(num, src, fun, pe, ps, drv, drv0, drv1, rsel, rpu, PAD_NUM_GPIO_YES, PAD_NUM_DIR_IN)
#define PAD_NUM_GPIO_OUT(num, src, fun, pe, ps, drv, drv0, drv1, rsel, rpu)          PAD_NUM_CONFIG(num, src, fun, pe, ps, drv, drv0, drv1, rsel, rpu, PAD_NUM_GPIO_YES, PAD_NUM_DIR_OUT)
#define PAD_NUM_GPIO_FUN(num, src, fun, pe, ps, drv, drv0, drv1, rsel, rpu)          PAD_NUM_CONFIG(num, src, fun, pe, ps, drv, drv0, drv1, rsel, rpu, PAD_NUM_GPIO_NO, PAD_NUM_DIR_IN)

#define PAD_NUM_BGPIO_IN(num, fun, pe, ps, drv, drv0, drv1, rsel, rpu)               PAD_NUM_GPIO_IN(num, PAD_NUM_SRC_DBB, fun, pe, ps, drv, drv0, drv1, rsel, rpu)
//#define PAD_NUM_MGPIO_IN(num, fun, pe, ps, drv, drv0, drv1, rsel, rpu)               PAD_NUM_GPIO_IN(num, PAD_NUM_SRC_MMP, fun, pe, ps, drv, drv0, drv1, rsel, rpu)
//#define PAD_NUM_PGPIO_IN(num, fun, pe, ps, drv, drv0, drv1, rsel, rpu)               PAD_NUM_GPIO_IN((num + IO_PAD_DBB_PAD_NUM), PAD_NUM_SRC_PMU, fun, pe, ps, drv, drv0, drv1, rsel, rpu)

#define PAD_NUM_BGPIO_OUT(num, fun, pe, ps, drv, drv0, drv1, rsel, rpu)              PAD_NUM_GPIO_OUT(num, PAD_NUM_SRC_DBB, fun, pe, ps, drv, drv0, drv1, rsel, rpu)
//#define PAD_NUM_MGPIO_OUT(num, fun, pe, ps, drv, drv0, drv1, rsel, rpu)              PAD_NUM_GPIO_OUT(num, PAD_NUM_SRC_MMP, fun, pe, ps, drv, drv0, drv1, rsel, rpu)
#define PAD_NUM_PGPIO_OUT(num, fun, pe, ps, drv, drv0, drv1, rsel, rpu)              PAD_NUM_GPIO_OUT((num + IO_PAD_DBB_PAD_NUM), PAD_NUM_SRC_PMU, fun, pe, ps, drv, drv0, drv1, rsel, rpu)

#define PAD_NUM_BGPIO_FUN(num, fun, pe, ps, drv, drv0, drv1, rsel, rpu)              PAD_NUM_GPIO_FUN(num, PAD_NUM_SRC_DBB, fun, pe, ps, drv, drv0, drv1, rsel, rpu)
//#define PAD_NUM_MGPIO_FUN(num, fun, pe, ps, drv, drv0, drv1, rsel, rpu)              PAD_NUM_GPIO_FUN(num, PAD_NUM_SRC_MMP, fun, pe, ps, drv, drv0, drv1, rsel, rpu)
#define PAD_NUM_PGPIO_FUN(num, fun, pe, ps, drv, drv0, drv1, rsel, rpu)              PAD_NUM_GPIO_FUN((num + IO_PAD_DBB_PAD_NUM), PAD_NUM_SRC_PMU, fun, pe, ps, drv, drv0, drv1, rsel, rpu)

#define PAD_NUM_MAX_NUM     0xFFUL

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{ 
    PAD_NUM_WL_STATE_GPIO_0_IN           = PAD_NUM_BGPIO_IN (  0,  0, 1, 0, 0, 0, 0, 0, 0), // BTIF_GPIO_2
    PAD_NUM_WL_STATE_GPIO_0_OUT          = PAD_NUM_BGPIO_OUT(  0,  0, 1, 0, 0, 0, 0, 0, 0), // BTIF_GPIO_2
    PAD_NUM_WL_STATE_F2_ECO4_DUMMY_3     = PAD_NUM_BGPIO_FUN(  0,  1, 0, 0, 0, 0, 0, 0, 0),
    PAD_NUM_WL_STATE_F3_WL_REQUEST       = PAD_NUM_BGPIO_FUN(  0,  2, 0, 0, 0, 0, 0, 0, 0),
    PAD_NUM_WL_STATE_F4_BT_DATA_1        = PAD_NUM_BGPIO_FUN(  0,  3, 0, 0, 0, 0, 0, 0, 0),

    PAD_NUM_WL_PRIOR_GPIO_1_IN           = PAD_NUM_BGPIO_IN (  1,  0, 1, 0, 0, 0, 0, 0, 0), // BTIF_GPIO_3
    PAD_NUM_WL_PRIOR_GPIO_1_OUT          = PAD_NUM_BGPIO_OUT(  1,  0, 1, 0, 0, 0, 0, 0, 0), // BTIF_GPIO_3
    PAD_NUM_WL_PRIOR_F2_ECO4_DUMMY_4     = PAD_NUM_BGPIO_FUN(  1,  1, 0, 0, 0, 0, 0, 0, 0),
    PAD_NUM_WL_PRIOR_F3_WL_PRIORITY      = PAD_NUM_BGPIO_FUN(  1,  2, 0, 0, 0, 0, 0, 0, 0),
    PAD_NUM_WL_PRIOR_F4_BT_SPI_SDATA     = PAD_NUM_BGPIO_FUN(  1,  3, 0, 0, 0, 0, 0, 0, 0),

    PAD_NUM_WL_FREQ_GPIO_2_IN            = PAD_NUM_BGPIO_IN (  2,  0, 1, 0, 0, 0, 0, 0, 0), // BTIF_GPIO_4
    PAD_NUM_WL_FREQ_GPIO_2_OUT           = PAD_NUM_BGPIO_OUT(  2,  0, 1, 0, 0, 0, 0, 0, 0), // BTIF_GPIO_4
    PAD_NUM_WL_FREQ_F2_ECO4_DUMMY_5      = PAD_NUM_BGPIO_FUN(  2,  1, 0, 0, 0, 0, 0, 0, 0),
    PAD_NUM_WL_FREQ_F3_WL_FREQUENCY      = PAD_NUM_BGPIO_FUN(  2,  2, 0, 0, 0, 0, 0, 0, 0),
    PAD_NUM_WL_FREQ_F4_BT_SPI_SCLK       = PAD_NUM_BGPIO_FUN(  2,  3, 0, 0, 0, 0, 0, 0, 0),

    PAD_NUM_WL_ACT_GPIO_3_IN             = PAD_NUM_BGPIO_IN (  3,  0, 1, 0, 0, 0, 0, 0, 0), // BTIF_GPIO_5
    PAD_NUM_WL_ACT_GPIO_3_OUT            = PAD_NUM_BGPIO_OUT(  3,  0, 1, 0, 0, 0, 0, 0, 0), // BTIF_GPIO_5
    PAD_NUM_WL_ACT_F2_ECO4_DUMMY_6       = PAD_NUM_BGPIO_FUN(  3,  1, 0, 0, 0, 0, 0, 0, 0),
    PAD_NUM_WL_ACT_F3_WL_ACK             = PAD_NUM_BGPIO_FUN(  3,  2, 0, 0, 0, 0, 0, 0, 0),
    PAD_NUM_WL_ACT_F4_BT_DATA_0          = PAD_NUM_BGPIO_FUN(  3,  3, 0, 0, 0, 0, 0, 0, 0),

    PAD_NUM_MPIF_D2_GPIO_4_IN            = PAD_NUM_BGPIO_IN (  4,  0, 1, 0, 0, 0, 1, 0, 0), // MPIF_GPIO_7
    PAD_NUM_MPIF_D2_GPIO_4_OUT           = PAD_NUM_BGPIO_OUT(  4,  0, 1, 0, 0, 0, 1, 0, 0), // MPIF_GPIO_7
    PAD_NUM_MPIF_D2_F8_ECO0_DUMMY_6      = PAD_NUM_BGPIO_FUN(  4,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_D2_F9_MPIF_D_2          = PAD_NUM_BGPIO_FUN(  4,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_D2_F10_SD_D_2           = PAD_NUM_BGPIO_FUN(  4,  3, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_D2_F11_DBG_UART_RTS     = PAD_NUM_BGPIO_FUN(  4,  4, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_D2_F12_FUART_RX         = PAD_NUM_BGPIO_FUN(  4,  5, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_MPIF_D1_GPIO_5_IN            = PAD_NUM_BGPIO_IN (  5,  0, 1, 0, 0, 0, 1, 0, 0), // MPIF_GPIO_6
    PAD_NUM_MPIF_D1_GPIO_5_OUT           = PAD_NUM_BGPIO_OUT(  5,  0, 1, 0, 0, 0, 1, 0, 0), // MPIF_GPIO_6
    PAD_NUM_MPIF_D1_F8_ECO0_DUMMY_12     = PAD_NUM_BGPIO_FUN(  5,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_D1_F9_MPIF_D_1          = PAD_NUM_BGPIO_FUN(  5,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_D1_F10_SD_D_1           = PAD_NUM_BGPIO_FUN(  5,  3, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_D1_F11_DBG_UART_RTS     = PAD_NUM_BGPIO_FUN(  5,  4, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_D1_F12_FUART_TX         = PAD_NUM_BGPIO_FUN(  5,  5, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_MPIF_D3_GPIO_6_IN            = PAD_NUM_BGPIO_IN (  6,  0, 1, 0, 0, 0, 1, 0, 0), // MPIF_GPIO_8
    PAD_NUM_MPIF_D3_GPIO_6_OUT           = PAD_NUM_BGPIO_OUT(  6,  0, 1, 0, 0, 0, 1, 0, 0), // MPIF_GPIO_8
    PAD_NUM_MPIF_D3_F7_ECO0_DUMMY_8      = PAD_NUM_BGPIO_FUN(  6,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_D3_F8_MPIF_D_3          = PAD_NUM_BGPIO_FUN(  6,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_D3_F9_SD_D_3            = PAD_NUM_BGPIO_FUN(  6,  3, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_D3_F10_DBG_UART_CTS     = PAD_NUM_BGPIO_FUN(  6,  4, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_D3_F11_FUART_CTS        = PAD_NUM_BGPIO_FUN(  6,  5, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_MPIF_BUSY_GPIO_7_IN          = PAD_NUM_BGPIO_IN (  7,  0, 1, 0, 0, 0, 1, 0, 0), // MPIF_GPIO_4
    PAD_NUM_MPIF_BUSY_GPIO_7_OUT         = PAD_NUM_BGPIO_OUT(  7,  0, 1, 0, 0, 0, 1, 0, 0), // MPIF_GPIO_4
    PAD_NUM_MPIF_BUSY_F8_ECO0_DUMMY_7    = PAD_NUM_BGPIO_FUN(  7,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_BUSY_F9_MPIF_BUSY       = PAD_NUM_BGPIO_FUN(  7,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_BUSY_F10_SD_CMD         = PAD_NUM_BGPIO_FUN(  7,  3, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_MPIF_D0_GPIO_8_IN            = PAD_NUM_BGPIO_IN (  8,  0, 1, 0, 0, 0, 1, 0, 0), // MPIF_GPIO_5
    PAD_NUM_MPIF_D0_GPIO_8_OUT           = PAD_NUM_BGPIO_OUT(  8,  0, 1, 0, 0, 0, 1, 0, 0), // MPIF_GPIO_5
    PAD_NUM_MPIF_D0_F8_ECO0_DUMMY_10     = PAD_NUM_BGPIO_FUN(  8,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_D0_F9_MPIF_D_0          = PAD_NUM_BGPIO_FUN(  8,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_D0_F10_SD_D_0           = PAD_NUM_BGPIO_FUN(  8,  3, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_D0_F11_DBG_UART_CTS     = PAD_NUM_BGPIO_FUN(  8,  4, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_MPIF_CLK_GPIO_9_IN           = PAD_NUM_BGPIO_IN (  9,  0, 1, 0, 0, 0, 1, 0, 0), // MPIF_GPIO_3
    PAD_NUM_MPIF_CLK_GPIO_9_OUT          = PAD_NUM_BGPIO_OUT(  9,  0, 1, 0, 0, 0, 1, 0, 0), // MPIF_GPIO_3
    PAD_NUM_MPIF_CLK_F5_ECO0_DUMMY_14    = PAD_NUM_BGPIO_FUN(  9,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_CLK_F6_MPIF_CLK         = PAD_NUM_BGPIO_FUN(  9,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_CLK_F7_SD_CLK           = PAD_NUM_BGPIO_FUN(  9,  3, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_MPIF_GPIO2_GPIO_10_IN        = PAD_NUM_BGPIO_IN ( 10,  0, 1, 0, 0, 0, 1, 0, 0), // MPIF_GPIO_1
    PAD_NUM_MPIF_GPIO2_GPIO_10_OUT       = PAD_NUM_BGPIO_OUT( 10,  0, 1, 0, 0, 0, 1, 0, 0), // MPIF_GPIO_1
    PAD_NUM_MPIF_GPIO2_F7_ECO0_DUMMY_13  = PAD_NUM_BGPIO_FUN( 10,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_GPIO2_F8_PWM1           = PAD_NUM_BGPIO_FUN( 10,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_GPIO2_F9_DBG_UART_TX    = PAD_NUM_BGPIO_FUN( 10,  3, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_GPIO2_F10_26MHZ_OUT     = PAD_NUM_BGPIO_FUN( 10,  4, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_GPIO2_F11_SPI_CS1_N     = PAD_NUM_BGPIO_FUN( 10,  5, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_GPIO2_F12_DBB_SPI_CS1_N = PAD_NUM_BGPIO_FUN( 10,  6, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_MPIF_GPIO1_GPIO_11_IN        = PAD_NUM_BGPIO_IN ( 11,  0, 1, 0, 0, 0, 1, 0, 0), // MPIF_GPIO_0
    PAD_NUM_MPIF_GPIO1_GPIO_11_OUT       = PAD_NUM_BGPIO_OUT( 11,  0, 1, 0, 0, 0, 1, 0, 0), // MPIF_GPIO_0
    PAD_NUM_MPIF_GPIO1_F8_ECO0_DUMMY_11  = PAD_NUM_BGPIO_FUN( 11,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_GPIO1_F9_PWM0           = PAD_NUM_BGPIO_FUN( 11,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_GPIO1_F10_GPS_CLK_OUT   = PAD_NUM_BGPIO_FUN( 11,  3, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_GPIO1_F11_GPS_CLK_OUT2  = PAD_NUM_BGPIO_FUN( 11,  4, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_GPIO1_F12_DBG_UART_RX   = PAD_NUM_BGPIO_FUN( 11,  5, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_GPIO1_F13_FUART_RTS     = PAD_NUM_BGPIO_FUN( 11,  6, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_GPIO1_F14_26MHZ_OUT     = PAD_NUM_BGPIO_FUN( 11,  7, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_MPIF_CS0N_GPIO_12_IN         = PAD_NUM_BGPIO_IN ( 12,  0, 1, 1, 0, 0, 1, 0, 0), // MPIF_GPIO_2
    PAD_NUM_MPIF_CS0N_GPIO_12_OUT        = PAD_NUM_BGPIO_OUT( 12,  0, 1, 1, 0, 0, 1, 0, 0), // MPIF_GPIO_2
    PAD_NUM_MPIF_CS0N_F8_ECO0_DUMMY_9    = PAD_NUM_BGPIO_FUN( 12,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_CS0N_F9_MPIF_CS0N       = PAD_NUM_BGPIO_FUN( 12,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_CS0N_F10_SD_CDZ         = PAD_NUM_BGPIO_FUN( 12,  3, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_MPIF_CS0N_F11_SD1_CDZ        = PAD_NUM_BGPIO_FUN( 12,  4, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_BTIF_GPIO1_GPIO_13_IN        = PAD_NUM_BGPIO_IN ( 13,  0, 1, 0, 0, 0, 1, 0, 0), // BTIF_GPIO_0
    PAD_NUM_BTIF_GPIO1_GPIO_13_OUT       = PAD_NUM_BGPIO_OUT( 13,  0, 1, 0, 0, 0, 1, 0, 0), // BTIF_GPIO_0
    PAD_NUM_BTIF_GPIO1_F6_ECO4_DUMMY_1   = PAD_NUM_BGPIO_FUN( 13,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_BTIF_GPIO1_F7_BT_RX_TX       = PAD_NUM_BGPIO_FUN( 13,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_BTIF_GPIO1_F8_BT_RX_TX       = PAD_NUM_BGPIO_FUN( 13,  3, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_BTIF_GPIO1_F9_SD1_CDZ        = PAD_NUM_BGPIO_FUN( 13,  4, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_BTIF_GPIO1_F10_PWM0          = PAD_NUM_BGPIO_FUN( 13,  5, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_BTIF_GPIO1_F11_FMARK         = PAD_NUM_BGPIO_FUN( 13,  6, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_BTIF_GPIO1_F12_LCD_CS1_N     = PAD_NUM_BGPIO_FUN( 13,  7, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_BTIF_GPIO1_F13_LCD_CS0_N     = PAD_NUM_BGPIO_FUN( 13,  8, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_BTIF_GPIO1_F14_LCD_SCL       = PAD_NUM_BGPIO_FUN( 13,  9, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_BTIF_GPIO1_F15_LCD_SCL       = PAD_NUM_BGPIO_FUN( 13, 10, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_BTIF_GPIO1_F16_SPI_CLK       = PAD_NUM_BGPIO_FUN( 13, 11, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_BTIF_GPIO1_F17_DBB_SPI_CLK   = PAD_NUM_BGPIO_FUN( 13, 12, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_BTIF_GPIO2_GPIO_14_IN        = PAD_NUM_BGPIO_IN ( 14,  0, 1, 0, 0, 0, 1, 0, 0), // BTIF_GPIO_1
    PAD_NUM_BTIF_GPIO2_GPIO_14_OUT       = PAD_NUM_BGPIO_OUT( 14,  0, 1, 0, 0, 0, 1, 0, 0), // BTIF_GPIO_1
    PAD_NUM_BTIF_GPIO2_F6_ECO4_DUMMY_2   = PAD_NUM_BGPIO_FUN( 14,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_BTIF_GPIO2_F7_PWM_IN         = PAD_NUM_BGPIO_FUN( 14,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_BTIF_GPIO2_F8_BT_CLK_24M     = PAD_NUM_BGPIO_FUN( 14,  3, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_BTIF_GPIO2_F9_BT_CLK_24M     = PAD_NUM_BGPIO_FUN( 14,  4, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_BTIF_GPIO2_F10_LCD_DCX       = PAD_NUM_BGPIO_FUN( 14,  5, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_BTIF_GPIO2_F11_LCD_SDO       = PAD_NUM_BGPIO_FUN( 14,  6, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_BTIF_GPIO2_F12_SPI_DO        = PAD_NUM_BGPIO_FUN( 14,  7, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_BTIF_GPIO2_F13_DBB_SPI_DO    = PAD_NUM_BGPIO_FUN( 14,  8, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_SR_D_0_GPIO_15_IN            = PAD_NUM_BGPIO_IN ( 15,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_1
    PAD_NUM_SR_D_0_GPIO_15_OUT           = PAD_NUM_BGPIO_OUT( 15,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_1
    PAD_NUM_SR_D_0_F7_ECO3_DUMMY_5       = PAD_NUM_BGPIO_FUN( 15,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_SR_D_0_F8_SR_D_0             = PAD_NUM_BGPIO_FUN( 15,  2, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_SR_D_1_GPIO_16_IN            = PAD_NUM_BGPIO_IN ( 16,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_2
    PAD_NUM_SR_D_1_GPIO_16_OUT           = PAD_NUM_BGPIO_OUT( 16,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_2
    PAD_NUM_SR_D_1_F7_ECO3_DUMMY_6       = PAD_NUM_BGPIO_FUN( 16,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_SR_D_1_F8_SR_D_1             = PAD_NUM_BGPIO_FUN( 16,  2, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_SR_D_2_GPIO_17_IN            = PAD_NUM_BGPIO_IN ( 17,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_3
    PAD_NUM_SR_D_2_GPIO_17_OUT           = PAD_NUM_BGPIO_OUT( 17,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_3
    PAD_NUM_SR_D_2_F7_ECO3_DUMMY_7       = PAD_NUM_BGPIO_FUN( 17,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_SR_D_2_F8_EFUSE_GADDR_1      = PAD_NUM_BGPIO_FUN( 17,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_SR_D_2_F9_SR_D_2             = PAD_NUM_BGPIO_FUN( 17,  3, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_SR_D_3_GPIO_18_IN            = PAD_NUM_BGPIO_IN ( 18,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_4
    PAD_NUM_SR_D_3_GPIO_18_OUT           = PAD_NUM_BGPIO_OUT( 18,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_4
    PAD_NUM_SR_D_3_F7_ECO3_DUMMY_8       = PAD_NUM_BGPIO_FUN( 18,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_SR_D_3_F8_EFUSE_GADDR_0      = PAD_NUM_BGPIO_FUN( 18,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_SR_D_3_F9_SR_D_3             = PAD_NUM_BGPIO_FUN( 18,  3, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_SR_D_4_GPIO_19_IN            = PAD_NUM_BGPIO_IN ( 19,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_5
    PAD_NUM_SR_D_4_GPIO_19_OUT           = PAD_NUM_BGPIO_OUT( 19,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_5
    PAD_NUM_SR_D_4_F7_ECO3_DUMMY_4       = PAD_NUM_BGPIO_FUN( 19,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_SR_D_4_F8_SR_D_4             = PAD_NUM_BGPIO_FUN( 19,  2, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_SR_D_5_GPIO_20_IN            = PAD_NUM_BGPIO_IN ( 20,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_6
    PAD_NUM_SR_D_5_GPIO_20_OUT           = PAD_NUM_BGPIO_OUT( 20,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_6
    PAD_NUM_SR_D_5_F7_ECO3_DUMMY_9       = PAD_NUM_BGPIO_FUN( 20,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_SR_D_5_F8_SPI_SEN_RDY        = PAD_NUM_BGPIO_FUN( 20,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_SR_D_5_F9_SR_D_5             = PAD_NUM_BGPIO_FUN( 20,  3, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_SR_D_6_GPIO_21_IN            = PAD_NUM_BGPIO_IN ( 21,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_7
    PAD_NUM_SR_D_6_GPIO_21_OUT           = PAD_NUM_BGPIO_OUT( 21,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_7
    PAD_NUM_SR_D_6_F7_ECO3_DUMMY_3       = PAD_NUM_BGPIO_FUN( 21,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_SR_D_6_F8_SPI_SEN_OVF        = PAD_NUM_BGPIO_FUN( 21,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_SR_D_6_F9_SR_D_6             = PAD_NUM_BGPIO_FUN( 21,  3, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_SR_D_7_GPIO_22_IN            = PAD_NUM_BGPIO_IN ( 22,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_8
    PAD_NUM_SR_D_7_GPIO_22_OUT           = PAD_NUM_BGPIO_OUT( 22,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_8
    PAD_NUM_SR_D_7_F7_ECO3_DUMMY_1       = PAD_NUM_BGPIO_FUN( 22,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_SR_D_7_F8_SPI_SEN_SSN        = PAD_NUM_BGPIO_FUN( 22,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_SR_D_7_F9_SR_D_7             = PAD_NUM_BGPIO_FUN( 22,  3, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_SR_MCLK_GPIO_23_IN           = PAD_NUM_BGPIO_IN ( 23,  0, 1, 0, 1, 0, 0, 0, 0), // SR_GPIO_10
    PAD_NUM_SR_MCLK_GPIO_23_OUT          = PAD_NUM_BGPIO_OUT( 23,  0, 1, 0, 1, 0, 0, 0, 0), // SR_GPIO_10
    PAD_NUM_SR_MCLK_F7_ECO3_DUMMY_2      = PAD_NUM_BGPIO_FUN( 23,  1, 0, 0, 1, 0, 0, 0, 0),
    PAD_NUM_SR_MCLK_F8_SR_MCLK           = PAD_NUM_BGPIO_FUN( 23,  2, 0, 0, 1, 0, 0, 0, 0),

    PAD_NUM_SR_GPIO_GPIO_24_IN           = PAD_NUM_BGPIO_IN ( 24,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_0
    PAD_NUM_SR_GPIO_GPIO_24_OUT          = PAD_NUM_BGPIO_OUT( 24,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_0
    PAD_NUM_SR_GPIO_F4_ECO3_DUMMY_14     = PAD_NUM_BGPIO_FUN( 24,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_SR_GPIO_F5_GPS_CLK_OUT       = PAD_NUM_BGPIO_FUN( 24,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_SR_GPIO_F6_GPS_CLK_OUT2      = PAD_NUM_BGPIO_FUN( 24,  3, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_SR_GPIO_F7_26MHZ_OUT         = PAD_NUM_BGPIO_FUN( 24,  4, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_SR_PCLK_GPIO_25_IN           = PAD_NUM_BGPIO_IN ( 25,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_14
    PAD_NUM_SR_PCLK_GPIO_25_OUT          = PAD_NUM_BGPIO_OUT( 25,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_14
    PAD_NUM_SR_PCLK_F7_ECO3_DUMMY_0      = PAD_NUM_BGPIO_FUN( 25,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_SR_PCLK_F8_SR_PCLK           = PAD_NUM_BGPIO_FUN( 25,  2, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_SR_HSYNC_GPIO_26_IN          = PAD_NUM_BGPIO_IN ( 26,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_9
    PAD_NUM_SR_HSYNC_GPIO_26_OUT         = PAD_NUM_BGPIO_OUT( 26,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_9
    PAD_NUM_SR_HSYNC_F4_ECO3_DUMMY_13    = PAD_NUM_BGPIO_FUN( 26,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_SR_HSYNC_F5_SR_HSYNC         = PAD_NUM_BGPIO_FUN( 26,  2, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_SR_VSYNC_GPIO_27_IN          = PAD_NUM_BGPIO_IN ( 27,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_11
    PAD_NUM_SR_VSYNC_GPIO_27_OUT         = PAD_NUM_BGPIO_OUT( 27,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_11
    PAD_NUM_SR_VSYNC_F7_ECO3_DUMMY_10    = PAD_NUM_BGPIO_FUN( 27,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_SR_VSYNC_F8_SR_VSYNC         = PAD_NUM_BGPIO_FUN( 27,  2, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_SR_RST_GPIO_28_IN            = PAD_NUM_BGPIO_IN ( 28,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_12
    PAD_NUM_SR_RST_GPIO_28_OUT           = PAD_NUM_BGPIO_OUT( 28,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_12
    PAD_NUM_SR_RST_F5_ECO3_DUMMY_12      = PAD_NUM_BGPIO_FUN( 28,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_SR_RST_F6_SR_RST             = PAD_NUM_BGPIO_FUN( 28,  2, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_SR_PWRDN_GPIO_29_IN          = PAD_NUM_BGPIO_IN ( 29,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_13
    PAD_NUM_SR_PWRDN_GPIO_29_OUT         = PAD_NUM_BGPIO_OUT( 29,  0, 1, 0, 0, 1, 0, 0, 0), // SR_GPIO_13
    PAD_NUM_SR_PWRDN_F5_ECO3_DUMMY_11    = PAD_NUM_BGPIO_FUN( 29,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_SR_PWRDN_F6_SR_PWRDN         = PAD_NUM_BGPIO_FUN( 29,  2, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_BLEDOD_F0_PMU_PWM4           = PAD_NUM_BGPIO_FUN( 30,  0, 0, 0, 0, 0, 0, 0, 0),

    PAD_NUM_GLEDOD_F0_PMU_PWM3           = PAD_NUM_BGPIO_FUN( 31,  0, 0, 0, 0, 0, 0, 0, 0),

    PAD_NUM_RLEDOD_F0_PMU_PWM2           = PAD_NUM_BGPIO_FUN( 32,  0, 0, 0, 0, 0, 0, 0, 0),

    PAD_NUM_VIB_F0_PMU_PWM1              = PAD_NUM_BGPIO_FUN( 33,  0, 0, 0, 0, 0, 0, 0, 0),

    PAD_NUM_KEYLED_F0_PMU_PWM0           = PAD_NUM_BGPIO_FUN( 34,  0, 0, 0, 0, 0, 0, 0, 0),

    PAD_NUM_INT1_GPIO_87_IN              = PAD_NUM_BGPIO_IN ( 35,  0, 1, 0, 0, 0, 1, 0, 0), // INT_GPIO1
    PAD_NUM_INT1_GPIO_87_OUT             = PAD_NUM_BGPIO_OUT( 35,  0, 1, 0, 0, 0, 1, 0, 0), // INT_GPIO1
    PAD_NUM_INT1_F7_ECO0_DUMMY_15        = PAD_NUM_BGPIO_FUN( 35,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_INT1_F8_WIFI_CLK_EN          = PAD_NUM_BGPIO_FUN( 35,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_INT1_F9_PWM_IN               = PAD_NUM_BGPIO_FUN( 35,  3, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_INT1_F10_MPIF_CS1N           = PAD_NUM_BGPIO_FUN( 35,  4, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_INT1_F11_26MHZ_OUT           = PAD_NUM_BGPIO_FUN( 35,  5, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_INT1_F12_LCD_SDI             = PAD_NUM_BGPIO_FUN( 35,  6, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_INT1_F13_LCD_SDA             = PAD_NUM_BGPIO_FUN( 35,  7, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_INT1_F14_SPI_DI              = PAD_NUM_BGPIO_FUN( 35,  8, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_INT1_F15_DBB_SPI_DI          = PAD_NUM_BGPIO_FUN( 35,  9, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_U0RXD_GPIO_88_IN             = PAD_NUM_BGPIO_IN ( 36,  0, 0, 0, 0, 0, 1, 0, 0), // UART_GPIO_1
    PAD_NUM_U0RXD_GPIO_88_OUT            = PAD_NUM_BGPIO_OUT( 36,  0, 0, 0, 0, 0, 1, 0, 0), // UART_GPIO_1

    PAD_NUM_U0TXD_GPIO_89_IN             = PAD_NUM_BGPIO_IN ( 37,  0, 0, 0, 0, 0, 1, 0, 0), // UART_GPIO_0
    PAD_NUM_U0TXD_GPIO_89_OUT            = PAD_NUM_BGPIO_OUT( 37,  0, 0, 0, 0, 0, 1, 0, 0), // UART_GPIO_0

    PAD_NUM_I2CCLK_GPIO_90_IN            = PAD_NUM_BGPIO_IN ( 38,  0, 0, 0, 0, 0, 1, 0, 0), // I2C_GPIO_0
    PAD_NUM_I2CCLK_GPIO_90_OUT           = PAD_NUM_BGPIO_OUT( 38,  0, 0, 0, 0, 0, 1, 0, 0), // I2C_GPIO_0
    PAD_NUM_I2CCLK_F1_EFUSE_GSIGDEV_P    = PAD_NUM_BGPIO_FUN( 38,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2CCLK_F2_I2CCLK             = PAD_NUM_BGPIO_FUN( 38,  2, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_I2CDATA_GPIO_91_IN           = PAD_NUM_BGPIO_IN ( 39,  0, 0, 0, 0, 0, 1, 0, 0), // I2C_GPIO_1
    PAD_NUM_I2CDATA_GPIO_91_OUT          = PAD_NUM_BGPIO_OUT( 39,  0, 0, 0, 0, 0, 1, 0, 0), // I2C_GPIO_1
    PAD_NUM_I2CDATA_F1_EFUSE_GPROG       = PAD_NUM_BGPIO_FUN( 39,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2CDATA_F2_I2CDATA           = PAD_NUM_BGPIO_FUN( 39,  2, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_CMMB_GPIO1_GPIO_92_IN        = PAD_NUM_BGPIO_IN ( 40,  0, 1, 0, 0, 0, 1, 0, 0), // CMMB_GPIO_0
    PAD_NUM_CMMB_GPIO1_GPIO_92_OUT       = PAD_NUM_BGPIO_OUT( 40,  0, 1, 0, 0, 0, 1, 0, 0), // CMMB_GPIO_0
    PAD_NUM_CMMB_GPIO1_F12_ECO0_DUMMY_3  = PAD_NUM_BGPIO_FUN( 40,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO1_F13_WL_FREQUENCY  = PAD_NUM_BGPIO_FUN( 40,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO1_F14_BT_SPI_SCLK   = PAD_NUM_BGPIO_FUN( 40,  3, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO1_F15_ROW_7         = PAD_NUM_BGPIO_FUN( 40,  4, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO1_F16_SD_D_3        = PAD_NUM_BGPIO_FUN( 40,  5, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO1_F17_PWM1          = PAD_NUM_BGPIO_FUN( 40,  6, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO1_F18_GPS_CLK_OUT   = PAD_NUM_BGPIO_FUN( 40,  7, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO1_F19_GPS_CLK_OUT2  = PAD_NUM_BGPIO_FUN( 40,  8, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO1_F20_DBG_UART_TX   = PAD_NUM_BGPIO_FUN( 40,  9, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO1_F21_FUART_RX      = PAD_NUM_BGPIO_FUN( 40, 10, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO1_F22_FUART_TX      = PAD_NUM_BGPIO_FUN( 40, 11, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO1_F23_26MHZ_OUT     = PAD_NUM_BGPIO_FUN( 40, 12, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO1_F24_LCD_SCS       = PAD_NUM_BGPIO_FUN( 40, 13, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO1_F25_LCD_SCS       = PAD_NUM_BGPIO_FUN( 40, 14, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO1_F26_SPI_CS0_N     = PAD_NUM_BGPIO_FUN( 40, 15, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO1_F27_DBB_SPI_CS0_N = PAD_NUM_BGPIO_FUN( 40, 16, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_CMMB_GPIO2_GPIO_93_IN        = PAD_NUM_BGPIO_IN ( 41,  0, 1, 0, 0, 0, 1, 0, 0), // CMMB_GPIO_1
    PAD_NUM_CMMB_GPIO2_GPIO_93_OUT       = PAD_NUM_BGPIO_OUT( 41,  0, 1, 0, 0, 0, 1, 0, 0), // CMMB_GPIO_1
    PAD_NUM_CMMB_GPIO2_F12_ECO0_DUMMY_4  = PAD_NUM_BGPIO_FUN( 41,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO2_F13_PWM_IN        = PAD_NUM_BGPIO_FUN( 41,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO2_F14_WL_PRIORITY   = PAD_NUM_BGPIO_FUN( 41,  3, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO2_F15_BT_DATA_0     = PAD_NUM_BGPIO_FUN( 41,  4, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO2_F16_ROW_6         = PAD_NUM_BGPIO_FUN( 41,  5, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO2_F17_SD_CMD        = PAD_NUM_BGPIO_FUN( 41,  6, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO2_F18_BT_PCM_SDI    = PAD_NUM_BGPIO_FUN( 41,  7, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO2_F19_DBG_UART_RX   = PAD_NUM_BGPIO_FUN( 41,  8, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO2_F20_FUART_CTS     = PAD_NUM_BGPIO_FUN( 41,  9, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO2_F21_FUART_RX      = PAD_NUM_BGPIO_FUN( 41, 10, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO2_F22_26MHZ_OUT     = PAD_NUM_BGPIO_FUN( 41, 11, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO2_F23_LCD_SDI       = PAD_NUM_BGPIO_FUN( 41, 12, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO2_F24_LCD_SDA       = PAD_NUM_BGPIO_FUN( 41, 13, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO2_F25_SPI_DI        = PAD_NUM_BGPIO_FUN( 41, 14, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO2_F26_DBB_SPI_DI    = PAD_NUM_BGPIO_FUN( 41, 15, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_CMMB_GPIO3_GPIO_94_IN        = PAD_NUM_BGPIO_IN ( 42,  0, 1, 0, 0, 0, 1, 0, 0), // CMMB_GPIO_2
    PAD_NUM_CMMB_GPIO3_GPIO_94_OUT       = PAD_NUM_BGPIO_OUT( 42,  0, 1, 0, 0, 0, 1, 0, 0), // CMMB_GPIO_2
    PAD_NUM_CMMB_GPIO3_F10_ECO0_DUMMY_5  = PAD_NUM_BGPIO_FUN( 42,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO3_F11_WL_REQUEST    = PAD_NUM_BGPIO_FUN( 42,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO3_F12_BT_SPI_SDATA  = PAD_NUM_BGPIO_FUN( 42,  3, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO3_F13_COL_7         = PAD_NUM_BGPIO_FUN( 42,  4, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO3_F14_SD_D_2        = PAD_NUM_BGPIO_FUN( 42,  5, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO3_F15_PWM0          = PAD_NUM_BGPIO_FUN( 42,  6, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO3_F16_FUART_RTS     = PAD_NUM_BGPIO_FUN( 42,  7, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO3_F17_26MHZ_OUT     = PAD_NUM_BGPIO_FUN( 42,  8, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO3_F18_SPI_CS1_N     = PAD_NUM_BGPIO_FUN( 42,  9, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_CMMB_GPIO3_F19_DBB_SPI_CS1_N = PAD_NUM_BGPIO_FUN( 42, 10, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_INT0_GPIO_95_IN              = PAD_NUM_BGPIO_IN ( 43,  0, 1, 0, 0, 0, 1, 0, 0), // INT_GPIO0
    PAD_NUM_INT0_GPIO_95_OUT             = PAD_NUM_BGPIO_OUT( 43,  0, 1, 0, 0, 0, 1, 0, 0), // INT_GPIO0
    PAD_NUM_INT0_F6_ECO4_DUMMY_0         = PAD_NUM_BGPIO_FUN( 43,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_INT0_F7_BT_SPI_SENB          = PAD_NUM_BGPIO_FUN( 43,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_INT0_F8_BT_SPI_SENB          = PAD_NUM_BGPIO_FUN( 43,  3, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_INT0_F9_PWM1                 = PAD_NUM_BGPIO_FUN( 43,  4, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_INT0_F10_GPS_CLK_OUT         = PAD_NUM_BGPIO_FUN( 43,  5, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_INT0_F11_GPS_CLK_OUT2        = PAD_NUM_BGPIO_FUN( 43,  6, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_INT0_F12_FMARK               = PAD_NUM_BGPIO_FUN( 43,  7, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_INT0_F13_LCD_CS1_N           = PAD_NUM_BGPIO_FUN( 43,  8, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_INT0_F14_LCD_CS0_N           = PAD_NUM_BGPIO_FUN( 43,  9, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_INT0_F15_LCD_SCS             = PAD_NUM_BGPIO_FUN( 43, 10, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_INT0_F16_LCD_SCS             = PAD_NUM_BGPIO_FUN( 43, 11, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_INT0_F17_SPI_CS0_N           = PAD_NUM_BGPIO_FUN( 43, 12, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_INT0_F18_DBB_SPI_CS0_N       = PAD_NUM_BGPIO_FUN( 43, 13, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_SD_D_1_GPIO_96_IN            = PAD_NUM_BGPIO_IN ( 44,  0, 1, 0, 0, 0, 1, 0, 0), // SD_GPIO_1
    PAD_NUM_SD_D_1_GPIO_96_OUT           = PAD_NUM_BGPIO_OUT( 44,  0, 1, 0, 0, 0, 1, 0, 0), // SD_GPIO_1
    PAD_NUM_SD_D_1_F4_ECO2_DUMMY_3       = PAD_NUM_BGPIO_FUN( 44,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_SD_D_1_F5_SD_D_1             = PAD_NUM_BGPIO_FUN( 44,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_SD_D_1_F6_SD_CMD             = PAD_NUM_BGPIO_FUN( 44,  3, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_SD_D_1_F7_SPI_CS1_N          = PAD_NUM_BGPIO_FUN( 44,  4, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_SD_CLK_GPIO_97_IN            = PAD_NUM_BGPIO_IN ( 45,  0, 1, 0, 0, 0, 1, 0, 0), // SD_GPIO_5
    PAD_NUM_SD_CLK_GPIO_97_OUT           = PAD_NUM_BGPIO_OUT( 45,  0, 1, 0, 0, 0, 1, 0, 0), // SD_GPIO_5
    PAD_NUM_SD_CLK_F4_ECO2_DUMMY_0       = PAD_NUM_BGPIO_FUN( 45,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_SD_CLK_F5_SD_CLK             = PAD_NUM_BGPIO_FUN( 45,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_SD_CLK_F6_SD_CLK             = PAD_NUM_BGPIO_FUN( 45,  3, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_SD_CLK_F7_SPI_CLK            = PAD_NUM_BGPIO_FUN( 45,  4, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_SD_CDZ_GPIO_98_IN            = PAD_NUM_BGPIO_IN ( 46,  0, 1, 1, 0, 0, 1, 0, 0), // SD_GPIO_4
    PAD_NUM_SD_CDZ_GPIO_98_OUT           = PAD_NUM_BGPIO_OUT( 46,  0, 1, 1, 0, 0, 1, 0, 0), // SD_GPIO_4
    PAD_NUM_SD_CDZ_F4_ECO2_DUMMY_4       = PAD_NUM_BGPIO_FUN( 46,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_SD_CDZ_F5_SD_CDZ             = PAD_NUM_BGPIO_FUN( 46,  2, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_SD_D_0_GPIO_99_IN            = PAD_NUM_BGPIO_IN ( 47,  0, 1, 0, 0, 0, 1, 0, 0), // SD_GPIO_0
    PAD_NUM_SD_D_0_GPIO_99_OUT           = PAD_NUM_BGPIO_OUT( 47,  0, 1, 0, 0, 0, 1, 0, 0), // SD_GPIO_0
    PAD_NUM_SD_D_0_F4_ECO2_DUMMY_5       = PAD_NUM_BGPIO_FUN( 47,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_SD_D_0_F5_SD_D_0             = PAD_NUM_BGPIO_FUN( 47,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_SD_D_0_F6_SD_D_0             = PAD_NUM_BGPIO_FUN( 47,  3, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_SD_D_0_F7_SPI_DO             = PAD_NUM_BGPIO_FUN( 47,  4, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_SD_CMD_GPIO_100_IN           = PAD_NUM_BGPIO_IN ( 48,  0, 1, 0, 0, 0, 1, 0, 0), // SD_GPIO_6
    PAD_NUM_SD_CMD_GPIO_100_OUT          = PAD_NUM_BGPIO_OUT( 48,  0, 1, 0, 0, 0, 1, 0, 0), // SD_GPIO_6
    PAD_NUM_SD_CMD_F4_ECO2_DUMMY_2       = PAD_NUM_BGPIO_FUN( 48,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_SD_CMD_F5_SD_CMD             = PAD_NUM_BGPIO_FUN( 48,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_SD_CMD_F6_SD_CMD             = PAD_NUM_BGPIO_FUN( 48,  3, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_SD_CMD_F7_SPI_DI             = PAD_NUM_BGPIO_FUN( 48,  4, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_SD_D_2_GPIO_101_IN           = PAD_NUM_BGPIO_IN ( 49,  0, 1, 0, 0, 0, 1, 0, 0), // SD_GPIO_2
    PAD_NUM_SD_D_2_GPIO_101_OUT          = PAD_NUM_BGPIO_OUT( 49,  0, 1, 0, 0, 0, 1, 0, 0), // SD_GPIO_2
    PAD_NUM_SD_D_2_F4_ECO2_DUMMY_6       = PAD_NUM_BGPIO_FUN( 49,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_SD_D_2_F5_SD_D_2             = PAD_NUM_BGPIO_FUN( 49,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_SD_D_2_F6_SD_CLK             = PAD_NUM_BGPIO_FUN( 49,  3, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_SD_D_3_GPIO_102_IN           = PAD_NUM_BGPIO_IN ( 50,  0, 1, 0, 0, 0, 1, 0, 0), // SD_GPIO_3
    PAD_NUM_SD_D_3_GPIO_102_OUT          = PAD_NUM_BGPIO_OUT( 50,  0, 1, 0, 0, 0, 1, 0, 0), // SD_GPIO_3
    PAD_NUM_SD_D_3_F4_ECO2_DUMMY_1       = PAD_NUM_BGPIO_FUN( 50,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_SD_D_3_F5_SD_D_3             = PAD_NUM_BGPIO_FUN( 50,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_SD_D_3_F6_SD_D_0             = PAD_NUM_BGPIO_FUN( 50,  3, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_SD_D_3_F7_SPI_CS0_N          = PAD_NUM_BGPIO_FUN( 50,  4, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_LCD_D_7_GPIO_103_IN          = PAD_NUM_BGPIO_IN ( 51,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_7
    PAD_NUM_LCD_D_7_GPIO_103_OUT         = PAD_NUM_BGPIO_OUT( 51,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_7
    PAD_NUM_LCD_D_7_F5_ECO1_DUMMY_9      = PAD_NUM_BGPIO_FUN( 51,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_7_F6_LCD_D_7           = PAD_NUM_BGPIO_FUN( 51,  2, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_LCD_D_12_GPIO_104_IN         = PAD_NUM_BGPIO_IN ( 52,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_12
    PAD_NUM_LCD_D_12_GPIO_104_OUT        = PAD_NUM_BGPIO_OUT( 52,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_12
    PAD_NUM_LCD_D_12_F5_ECO1_DUMMY_1     = PAD_NUM_BGPIO_FUN( 52,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_12_F6_SD_D_3           = PAD_NUM_BGPIO_FUN( 52,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_12_F7_SD1_CDZ          = PAD_NUM_BGPIO_FUN( 52,  3, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_12_F8_LCD_D_12         = PAD_NUM_BGPIO_FUN( 52,  4, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_12_F9_LCD_SCS          = PAD_NUM_BGPIO_FUN( 52,  5, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_12_F10_LCD_SCS         = PAD_NUM_BGPIO_FUN( 52,  6, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_12_F11_SPI_CS0_N       = PAD_NUM_BGPIO_FUN( 52,  7, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_12_F12_DBB_SPI_CS0_N   = PAD_NUM_BGPIO_FUN( 52,  8, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_LCD_D_15_GPIO_105_IN         = PAD_NUM_BGPIO_IN ( 53,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_15
    PAD_NUM_LCD_D_15_GPIO_105_OUT        = PAD_NUM_BGPIO_OUT( 53,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_15
    PAD_NUM_LCD_D_15_F7_ECO1_DUMMY_2     = PAD_NUM_BGPIO_FUN( 53,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_15_F8_SD_CLK           = PAD_NUM_BGPIO_FUN( 53,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_15_F9_SD_CLK           = PAD_NUM_BGPIO_FUN( 53,  3, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_15_F10_SD_CLK          = PAD_NUM_BGPIO_FUN( 53,  4, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_15_F11_LCD_D_15        = PAD_NUM_BGPIO_FUN( 53,  5, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_15_F12_LCD_SCL         = PAD_NUM_BGPIO_FUN( 53,  6, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_15_F13_LCD_SCL         = PAD_NUM_BGPIO_FUN( 53,  7, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_15_F14_SPI_CLK         = PAD_NUM_BGPIO_FUN( 53,  8, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_15_F15_DBB_SPI_CLK     = PAD_NUM_BGPIO_FUN( 53,  9, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_LCD_D_14_GPIO_106_IN         = PAD_NUM_BGPIO_IN ( 54,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_14
    PAD_NUM_LCD_D_14_GPIO_106_OUT        = PAD_NUM_BGPIO_OUT( 54,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_14
    PAD_NUM_LCD_D_14_F5_ECO1_DUMMY_3     = PAD_NUM_BGPIO_FUN( 54,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_14_F6_SD_CMD           = PAD_NUM_BGPIO_FUN( 54,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_14_F7_SD_CMD           = PAD_NUM_BGPIO_FUN( 54,  3, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_14_F8_LCD_D_14         = PAD_NUM_BGPIO_FUN( 54,  4, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_14_F9_LCD_SDI          = PAD_NUM_BGPIO_FUN( 54,  5, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_14_F10_LCD_SDA         = PAD_NUM_BGPIO_FUN( 54,  6, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_14_F11_SPI_DI          = PAD_NUM_BGPIO_FUN( 54,  7, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_14_F12_DBB_SPI_DI      = PAD_NUM_BGPIO_FUN( 54,  8, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_LCD_D_6_GPIO_107_IN          = PAD_NUM_BGPIO_IN ( 55,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_6
    PAD_NUM_LCD_D_6_GPIO_107_OUT         = PAD_NUM_BGPIO_OUT( 55,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_6
    PAD_NUM_LCD_D_6_F5_ECO1_DUMMY_21     = PAD_NUM_BGPIO_FUN( 55,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_6_F6_LCD_D_6           = PAD_NUM_BGPIO_FUN( 55,  2, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_LCD_RD_GPIO_108_IN           = PAD_NUM_BGPIO_IN ( 56,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_20
    PAD_NUM_LCD_RD_GPIO_108_OUT          = PAD_NUM_BGPIO_OUT( 56,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_20
    PAD_NUM_LCD_RD_F4_ECO1_DUMMY_7       = PAD_NUM_BGPIO_FUN( 56,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_RD_F5_EFUSE_GFSET_P      = PAD_NUM_BGPIO_FUN( 56,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_RD_F6_LCD_RD             = PAD_NUM_BGPIO_FUN( 56,  3, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_RD_F7_LCD_SDI            = PAD_NUM_BGPIO_FUN( 56,  4, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_RD_F8_LCD_SDA            = PAD_NUM_BGPIO_FUN( 56,  5, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_LCD_D_9_GPIO_109_IN          = PAD_NUM_BGPIO_IN ( 57,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_9
    PAD_NUM_LCD_D_9_GPIO_109_OUT         = PAD_NUM_BGPIO_OUT( 57,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_9
    PAD_NUM_LCD_D_9_F7_ECO1_DUMMY_6      = PAD_NUM_BGPIO_FUN( 57,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_9_F8_PWM_IN            = PAD_NUM_BGPIO_FUN( 57,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_9_F9_LCD_D_9           = PAD_NUM_BGPIO_FUN( 57,  3, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_9_F10_LCD_SCS          = PAD_NUM_BGPIO_FUN( 57,  4, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_9_F11_LCD_SCS          = PAD_NUM_BGPIO_FUN( 57,  5, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_LCD_RSTZ_GPIO_110_IN         = PAD_NUM_BGPIO_IN ( 58,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_19
    PAD_NUM_LCD_RSTZ_GPIO_110_OUT        = PAD_NUM_BGPIO_OUT( 58,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_19
    PAD_NUM_LCD_RSTZ_F2_ECO1_DUMMY_13    = PAD_NUM_BGPIO_FUN( 58,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_RSTZ_F3_EFUSE_GPRCHG2_N  = PAD_NUM_BGPIO_FUN( 58,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_RSTZ_F4_LCD_RSTZ         = PAD_NUM_BGPIO_FUN( 58,  3, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_RSTZ_F5_LCD_RSTZ         = PAD_NUM_BGPIO_FUN( 58,  4, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_RSTZ_F6_LCD_RSTZ         = PAD_NUM_BGPIO_FUN( 58,  5, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_RSTZ_F7_LCD_RSTZ         = PAD_NUM_BGPIO_FUN( 58,  6, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_RSTZ_F8_LCD_RSTZ         = PAD_NUM_BGPIO_FUN( 58,  7, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_RSTZ_F9_LCD_RSTZ         = PAD_NUM_BGPIO_FUN( 58,  8, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_RSTZ_F10_LCD_RSTZ        = PAD_NUM_BGPIO_FUN( 58,  9, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_RSTZ_F11_LCD_RSTZ        = PAD_NUM_BGPIO_FUN( 58, 10, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_RSTZ_F12_LCD_RSTZ        = PAD_NUM_BGPIO_FUN( 58, 11, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_RSTZ_F13_LCD_RSTZ        = PAD_NUM_BGPIO_FUN( 58, 12, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_RSTZ_F14_LCD_RSTZ        = PAD_NUM_BGPIO_FUN( 58, 13, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_RSTZ_F15_LCD_RSTZ        = PAD_NUM_BGPIO_FUN( 58, 14, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_RSTZ_F16_LCD_RSTZ        = PAD_NUM_BGPIO_FUN( 58, 15, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_LCD_D_13_GPIO_111_IN         = PAD_NUM_BGPIO_IN ( 59,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_13
    PAD_NUM_LCD_D_13_GPIO_111_OUT        = PAD_NUM_BGPIO_OUT( 59,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_13
    PAD_NUM_LCD_D_13_F7_ECO1_DUMMY_8     = PAD_NUM_BGPIO_FUN( 59,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_13_F8_SD_D_0           = PAD_NUM_BGPIO_FUN( 59,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_13_F9_SD_D_0           = PAD_NUM_BGPIO_FUN( 59,  3, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_13_F10_SD_D_0          = PAD_NUM_BGPIO_FUN( 59,  4, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_13_F11_LCD_D_13        = PAD_NUM_BGPIO_FUN( 59,  5, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_13_F12_LCD_DCX         = PAD_NUM_BGPIO_FUN( 59,  6, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_13_F13_LCD_SDO         = PAD_NUM_BGPIO_FUN( 59,  7, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_13_F14_SPI_DO          = PAD_NUM_BGPIO_FUN( 59,  8, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_13_F15_DBB_SPI_DO      = PAD_NUM_BGPIO_FUN( 59,  9, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_LCD_CMD_GPIO_112_IN          = PAD_NUM_BGPIO_IN ( 60,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_21
    PAD_NUM_LCD_CMD_GPIO_112_OUT         = PAD_NUM_BGPIO_OUT( 60,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_21
    PAD_NUM_LCD_CMD_F5_ECO1_DUMMY_4      = PAD_NUM_BGPIO_FUN( 60,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_CMD_F6_EFUSE_GMONGATE    = PAD_NUM_BGPIO_FUN( 60,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_CMD_F7_LCD_CMD           = PAD_NUM_BGPIO_FUN( 60,  3, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_CMD_F8_LCD_SCL           = PAD_NUM_BGPIO_FUN( 60,  4, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_CMD_F9_LCD_SCL           = PAD_NUM_BGPIO_FUN( 60,  5, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_LCD_D_10_GPIO_113_IN         = PAD_NUM_BGPIO_IN ( 61,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_10
    PAD_NUM_LCD_D_10_GPIO_113_OUT        = PAD_NUM_BGPIO_OUT( 61,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_10
    PAD_NUM_LCD_D_10_F5_ECO1_DUMMY_10    = PAD_NUM_BGPIO_FUN( 61,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_10_F6_WIFI_CLK_EN      = PAD_NUM_BGPIO_FUN( 61,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_10_F7_SD_D_2           = PAD_NUM_BGPIO_FUN( 61,  3, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_10_F8_SD_CMD           = PAD_NUM_BGPIO_FUN( 61,  4, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_10_F9_FMARK            = PAD_NUM_BGPIO_FUN( 61,  5, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_10_F10_LCD_CS1_N       = PAD_NUM_BGPIO_FUN( 61,  6, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_10_F11_LCD_CS0_N       = PAD_NUM_BGPIO_FUN( 61,  7, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_10_F12_LCD_D_10        = PAD_NUM_BGPIO_FUN( 61,  8, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_10_F13_LCD_DCX         = PAD_NUM_BGPIO_FUN( 61,  9, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_10_F14_LCD_SDO         = PAD_NUM_BGPIO_FUN( 61, 10, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_LCD_D_16_GPIO_114_IN         = PAD_NUM_BGPIO_IN ( 62,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_16
    PAD_NUM_LCD_D_16_GPIO_114_OUT        = PAD_NUM_BGPIO_OUT( 62,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_16
    PAD_NUM_LCD_D_16_F8_ECO1_DUMMY_11    = PAD_NUM_BGPIO_FUN( 62,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_16_F9_PWM0             = PAD_NUM_BGPIO_FUN( 62,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_16_F10_DBG_UART_RTS    = PAD_NUM_BGPIO_FUN( 62,  3, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_16_F11_FMARK           = PAD_NUM_BGPIO_FUN( 62,  4, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_16_F12_26MHZ_OUT       = PAD_NUM_BGPIO_FUN( 62,  5, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_16_F13_LCD_CS1_N       = PAD_NUM_BGPIO_FUN( 62,  6, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_16_F14_LCD_D_16        = PAD_NUM_BGPIO_FUN( 62,  7, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_16_F15_LCD_SCS1        = PAD_NUM_BGPIO_FUN( 62,  8, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_16_F16_LCD_SDI         = PAD_NUM_BGPIO_FUN( 62,  9, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_16_F17_LCD_SDA         = PAD_NUM_BGPIO_FUN( 62, 10, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_LCD_D_17_GPIO_115_IN         = PAD_NUM_BGPIO_IN ( 63,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_17
    PAD_NUM_LCD_D_17_GPIO_115_OUT        = PAD_NUM_BGPIO_OUT( 63,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_17
    PAD_NUM_LCD_D_17_F8_ECO1_DUMMY_12    = PAD_NUM_BGPIO_FUN( 63,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_17_F9_WIFI_CLK_EN      = PAD_NUM_BGPIO_FUN( 63,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_17_F10_PWM1            = PAD_NUM_BGPIO_FUN( 63,  3, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_17_F11_DBG_UART_CTS    = PAD_NUM_BGPIO_FUN( 63,  4, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_17_F12_FMARK           = PAD_NUM_BGPIO_FUN( 63,  5, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_17_F13_26MHZ_OUT       = PAD_NUM_BGPIO_FUN( 63,  6, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_17_F14_LCD_CS1_N       = PAD_NUM_BGPIO_FUN( 63,  7, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_17_F15_LCD_CS0_N       = PAD_NUM_BGPIO_FUN( 63,  8, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_17_F16_LCD_D_17        = PAD_NUM_BGPIO_FUN( 63,  9, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_17_F17_LCD_SCS1        = PAD_NUM_BGPIO_FUN( 63, 10, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_17_F18_LCD_SCL         = PAD_NUM_BGPIO_FUN( 63, 11, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_17_F19_LCD_SCL         = PAD_NUM_BGPIO_FUN( 63, 12, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_LCD_CS0_N_GPIO_116_IN        = PAD_NUM_BGPIO_IN ( 64,  0, 1, 1, 0, 1, 0, 0, 0), // LCD_GPIO_18
    PAD_NUM_LCD_CS0_N_GPIO_116_OUT       = PAD_NUM_BGPIO_OUT( 64,  0, 1, 1, 0, 1, 0, 0, 0), // LCD_GPIO_18
    PAD_NUM_LCD_CS0_N_F4_ECO1_DUMMY_0    = PAD_NUM_BGPIO_FUN( 64,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_CS0_N_F5_EFUSE_GPRCHG_N  = PAD_NUM_BGPIO_FUN( 64,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_CS0_N_F6_LCD_CS1_N       = PAD_NUM_BGPIO_FUN( 64,  3, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_CS0_N_F7_LCD_CS0_N       = PAD_NUM_BGPIO_FUN( 64,  4, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_CS0_N_F8_LCD_SCS         = PAD_NUM_BGPIO_FUN( 64,  5, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_CS0_N_F9_LCD_SCS         = PAD_NUM_BGPIO_FUN( 64,  6, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_LCD_D_8_GPIO_117_IN          = PAD_NUM_BGPIO_IN ( 65,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_8
    PAD_NUM_LCD_D_8_GPIO_117_OUT         = PAD_NUM_BGPIO_OUT( 65,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_8
    PAD_NUM_LCD_D_8_F6_ECO1_DUMMY_19     = PAD_NUM_BGPIO_FUN( 65,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_8_F7_FMARK             = PAD_NUM_BGPIO_FUN( 65,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_8_F8_LCD_CS1_N         = PAD_NUM_BGPIO_FUN( 65,  3, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_8_F9_LCD_CS0_N         = PAD_NUM_BGPIO_FUN( 65,  4, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_8_F10_LCD_D_8          = PAD_NUM_BGPIO_FUN( 65,  5, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_LCD_D_3_GPIO_118_IN          = PAD_NUM_BGPIO_IN ( 66,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_3
    PAD_NUM_LCD_D_3_GPIO_118_OUT         = PAD_NUM_BGPIO_OUT( 66,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_3
    PAD_NUM_LCD_D_3_F6_ECO1_DUMMY_14     = PAD_NUM_BGPIO_FUN( 66,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_3_F7_LCD_D_3           = PAD_NUM_BGPIO_FUN( 66,  2, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_LCD_D_4_GPIO_119_IN          = PAD_NUM_BGPIO_IN ( 67,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_4
    PAD_NUM_LCD_D_4_GPIO_119_OUT         = PAD_NUM_BGPIO_OUT( 67,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_4
    PAD_NUM_LCD_D_4_F5_ECO1_DUMMY_15     = PAD_NUM_BGPIO_FUN( 67,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_4_F6_LCD_D_4           = PAD_NUM_BGPIO_FUN( 67,  2, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_LCD_D_2_GPIO_120_IN          = PAD_NUM_BGPIO_IN ( 68,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_2
    PAD_NUM_LCD_D_2_GPIO_120_OUT         = PAD_NUM_BGPIO_OUT( 68,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_2
    PAD_NUM_LCD_D_2_F6_ECO1_DUMMY_17     = PAD_NUM_BGPIO_FUN( 68,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_2_F7_LCD_D_2           = PAD_NUM_BGPIO_FUN( 68,  2, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_LCD_D_11_GPIO_121_IN         = PAD_NUM_BGPIO_IN ( 69,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_11
    PAD_NUM_LCD_D_11_GPIO_121_OUT        = PAD_NUM_BGPIO_OUT( 69,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_11
    PAD_NUM_LCD_D_11_F8_ECO1_DUMMY_18    = PAD_NUM_BGPIO_FUN( 69,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_11_F9_SD_D_1           = PAD_NUM_BGPIO_FUN( 69,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_11_F10_LCD_D_11        = PAD_NUM_BGPIO_FUN( 69,  3, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_11_F11_SPI_CS0_N       = PAD_NUM_BGPIO_FUN( 69,  4, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_11_F12_SPI_CS1_N       = PAD_NUM_BGPIO_FUN( 69,  5, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_11_F13_DBB_SPI_CS1_N   = PAD_NUM_BGPIO_FUN( 69,  6, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_LCD_D_1_GPIO_122_IN          = PAD_NUM_BGPIO_IN ( 70,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_1
    PAD_NUM_LCD_D_1_GPIO_122_OUT         = PAD_NUM_BGPIO_OUT( 70,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_1
    PAD_NUM_LCD_D_1_F5_ECO1_DUMMY_22     = PAD_NUM_BGPIO_FUN( 70,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_1_F6_LCD_D_1           = PAD_NUM_BGPIO_FUN( 70,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_1_F7_LCD_DCX           = PAD_NUM_BGPIO_FUN( 70,  3, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_LCD_D_5_GPIO_123_IN          = PAD_NUM_BGPIO_IN ( 71,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_5
    PAD_NUM_LCD_D_5_GPIO_123_OUT         = PAD_NUM_BGPIO_OUT( 71,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_5
    PAD_NUM_LCD_D_5_F6_ECO1_DUMMY_20     = PAD_NUM_BGPIO_FUN( 71,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_5_F7_LCD_D_5           = PAD_NUM_BGPIO_FUN( 71,  2, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_LCD_D_0_GPIO_124_IN          = PAD_NUM_BGPIO_IN ( 72,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_0
    PAD_NUM_LCD_D_0_GPIO_124_OUT         = PAD_NUM_BGPIO_OUT( 72,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_0
    PAD_NUM_LCD_D_0_F7_ECO1_DUMMY_16     = PAD_NUM_BGPIO_FUN( 72,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_0_F8_LCD_D_0           = PAD_NUM_BGPIO_FUN( 72,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_D_0_F9_LCD_SCS1          = PAD_NUM_BGPIO_FUN( 72,  3, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_LCD_WR_GPIO_125_IN           = PAD_NUM_BGPIO_IN ( 73,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_22
    PAD_NUM_LCD_WR_GPIO_125_OUT          = PAD_NUM_BGPIO_OUT( 73,  0, 1, 0, 0, 1, 0, 0, 0), // LCD_GPIO_22
    PAD_NUM_LCD_WR_F5_ECO1_DUMMY_5       = PAD_NUM_BGPIO_FUN( 73,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_WR_F6_EFUSE_GMONSEL      = PAD_NUM_BGPIO_FUN( 73,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_WR_F7_LCD_WR             = PAD_NUM_BGPIO_FUN( 73,  3, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_WR_F8_LCD_DCX            = PAD_NUM_BGPIO_FUN( 73,  4, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_LCD_WR_F9_LCD_SDO            = PAD_NUM_BGPIO_FUN( 73,  5, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_AUXADC0_F0_GPIO_IN           = PAD_NUM_BGPIO_IN(74,  0, 1, 0, 0, 0, 0, 0, 0), //0
    PAD_NUM_AUXADC0_F0_GPIO_OUT          = PAD_NUM_BGPIO_OUT(74,  0, 1, 0, 0, 0, 0, 0, 0), //0
    PAD_NUM_AUXADC0_F1                   = PAD_NUM_BGPIO_FUN(74,  1, 1, 0, 0, 0, 0, 0, 0), //0

    PAD_NUM_AUXADC1_F0_GPIO_IN           = PAD_NUM_BGPIO_IN(75,  0, 1, 0, 0, 0, 0, 0, 0), //0
    PAD_NUM_AUXADC1_F0_GPIO_OUT          = PAD_NUM_BGPIO_OUT(75,  0, 1, 0, 0, 0, 0, 0, 0), //0
    PAD_NUM_AUXADC1_F1                   = PAD_NUM_BGPIO_FUN(75,  1, 1, 0, 0, 0, 0, 0, 0), //0

    PAD_NUM_AUXADC2_F0_GPIO_IN           = PAD_NUM_BGPIO_IN(76,  0, 1, 0, 0, 0, 0, 0, 0), //0
    PAD_NUM_AUXADC2_F0_GPIO_OUT          = PAD_NUM_BGPIO_OUT(76,  0, 1, 0, 0, 0, 0, 0, 0), //0
    PAD_NUM_AUXADC2_F1                   = PAD_NUM_BGPIO_FUN(76,  1, 1, 0, 0, 0, 0, 0, 0), //0

    PAD_NUM_AUXADC3_F0_GPIO_IN           = PAD_NUM_BGPIO_IN(77,  0, 1, 0, 0, 0, 0, 0, 0), //0
    PAD_NUM_AUXADC3_F0_GPIO_OUT          = PAD_NUM_BGPIO_OUT(77,  0, 1, 0, 0, 0, 0, 0, 0), //0
    PAD_NUM_AUXADC3_F1                   = PAD_NUM_BGPIO_FUN(77,  1, 1, 0, 0, 0, 0, 0, 0), //0

    PAD_NUM_I2SDIO_GPIO_130_IN           = PAD_NUM_BGPIO_IN ( 78,  0, 1, 0, 0, 0, 1, 0, 0), // I2S_GPIO_1
    PAD_NUM_I2SDIO_GPIO_130_OUT          = PAD_NUM_BGPIO_OUT( 78,  0, 1, 0, 0, 0, 1, 0, 0), // I2S_GPIO_1
    PAD_NUM_I2SDIO_F4_ECO0_DUMMY_1       = PAD_NUM_BGPIO_FUN( 78,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SDIO_F5_EFUSE_GBANK_P_0    = PAD_NUM_BGPIO_FUN( 78,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SDIO_F6_BTRF_CHIP_EN       = PAD_NUM_BGPIO_FUN( 78,  3, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SDIO_F7_BTRF_CHIP_EN       = PAD_NUM_BGPIO_FUN( 78,  4, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SDIO_F8_ROW_6              = PAD_NUM_BGPIO_FUN( 78,  5, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SDIO_F9_SD_CLK             = PAD_NUM_BGPIO_FUN( 78,  6, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SDIO_F10_SD_D_1            = PAD_NUM_BGPIO_FUN( 78,  7, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SDIO_F11_SD_CLK            = PAD_NUM_BGPIO_FUN( 78,  8, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SDIO_F12_PWM0              = PAD_NUM_BGPIO_FUN( 78,  9, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SDIO_F13_BT_PCM_SDI        = PAD_NUM_BGPIO_FUN( 78, 10, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SDIO_F14_BT_PCM_SDO        = PAD_NUM_BGPIO_FUN( 78, 11, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SDIO_F15_BT_PCM_SDO        = PAD_NUM_BGPIO_FUN( 78, 12, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SDIO_F16_DBG_UART_RX       = PAD_NUM_BGPIO_FUN( 78, 13, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SDIO_F17_SPI_CS1_N         = PAD_NUM_BGPIO_FUN( 78, 14, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SDIO_F18_DBB_SPI_CS1_N     = PAD_NUM_BGPIO_FUN( 78, 15, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_I2SBCLK_GPIO_131_IN          = PAD_NUM_BGPIO_IN ( 79,  0, 1, 0, 0, 0, 1, 0, 0), // I2S_GPIO_0
    PAD_NUM_I2SBCLK_GPIO_131_OUT         = PAD_NUM_BGPIO_OUT( 79,  0, 1, 0, 0, 0, 1, 0, 0), // I2S_GPIO_0
    PAD_NUM_I2SBCLK_F4_ECO0_DUMMY_2      = PAD_NUM_BGPIO_FUN( 79,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SBCLK_F5_EFUSE_GADDR_2     = PAD_NUM_BGPIO_FUN( 79,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SBCLK_F6_PWM_IN            = PAD_NUM_BGPIO_FUN( 79,  3, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SBCLK_F7_WL_ACK            = PAD_NUM_BGPIO_FUN( 79,  4, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SBCLK_F8_BT_DATA_1         = PAD_NUM_BGPIO_FUN( 79,  5, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SBCLK_F9_COL_7             = PAD_NUM_BGPIO_FUN( 79,  6, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SBCLK_F10_SD_CMD           = PAD_NUM_BGPIO_FUN( 79,  7, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SBCLK_F11_SD_D_0           = PAD_NUM_BGPIO_FUN( 79,  8, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SBCLK_F12_SD_CMD           = PAD_NUM_BGPIO_FUN( 79,  9, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SBCLK_F13_BT_PCM_BCK       = PAD_NUM_BGPIO_FUN( 79, 10, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SBCLK_F14_BT_PCM_BCK       = PAD_NUM_BGPIO_FUN( 79, 11, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SBCLK_F15_BT_PCM_BCK       = PAD_NUM_BGPIO_FUN( 79, 12, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SBCLK_F16_FUART_TX         = PAD_NUM_BGPIO_FUN( 79, 13, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SBCLK_F17_26MHZ_OUT        = PAD_NUM_BGPIO_FUN( 79, 14, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SBCLK_F18_LCD_DCX          = PAD_NUM_BGPIO_FUN( 79, 15, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SBCLK_F19_LCD_SDO          = PAD_NUM_BGPIO_FUN( 79, 16, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SBCLK_F20_SPI_DO           = PAD_NUM_BGPIO_FUN( 79, 17, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SBCLK_F21_DBB_SPI_DO       = PAD_NUM_BGPIO_FUN( 79, 18, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_I2SWS_GPIO_132_IN            = PAD_NUM_BGPIO_IN ( 80,  0, 1, 0, 0, 0, 1, 0, 0), // I2S_GPIO_2
    PAD_NUM_I2SWS_GPIO_132_OUT           = PAD_NUM_BGPIO_OUT( 80,  0, 1, 0, 0, 0, 1, 0, 0), // I2S_GPIO_2
    PAD_NUM_I2SWS_F4_ECO0_DUMMY_0        = PAD_NUM_BGPIO_FUN( 80,  1, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SWS_F5_EFUSE_GBANK_P_1     = PAD_NUM_BGPIO_FUN( 80,  2, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SWS_F6_ROW_7               = PAD_NUM_BGPIO_FUN( 80,  3, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SWS_F7_SD_D_0              = PAD_NUM_BGPIO_FUN( 80,  4, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SWS_F8_SD_CLK              = PAD_NUM_BGPIO_FUN( 80,  5, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SWS_F9_SD_D_0              = PAD_NUM_BGPIO_FUN( 80,  6, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SWS_F10_PWM1               = PAD_NUM_BGPIO_FUN( 80,  7, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SWS_F11_BT_PCM_WCK         = PAD_NUM_BGPIO_FUN( 80,  8, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SWS_F12_BT_PCM_WCK         = PAD_NUM_BGPIO_FUN( 80,  9, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SWS_F13_BT_PCM_WCK         = PAD_NUM_BGPIO_FUN( 80, 10, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SWS_F14_DBG_UART_TX        = PAD_NUM_BGPIO_FUN( 80, 11, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SWS_F15_FMARK              = PAD_NUM_BGPIO_FUN( 80, 12, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SWS_F16_LCD_CS1_N          = PAD_NUM_BGPIO_FUN( 80, 13, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SWS_F17_LCD_CS0_N          = PAD_NUM_BGPIO_FUN( 80, 14, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SWS_F18_LCD_SCL            = PAD_NUM_BGPIO_FUN( 80, 15, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SWS_F19_LCD_SCL            = PAD_NUM_BGPIO_FUN( 80, 16, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SWS_F20_SPI_CLK            = PAD_NUM_BGPIO_FUN( 80, 17, 0, 0, 0, 0, 1, 0, 0),
    PAD_NUM_I2SWS_F21_DBB_SPI_CLK        = PAD_NUM_BGPIO_FUN( 80, 18, 0, 0, 0, 0, 1, 0, 0),

    PAD_NUM_ROW_0_GPIO_133_IN            = PAD_NUM_BGPIO_IN ( 81,  0, 1, 0, 0, 1, 0, 0, 0), // ROW_GPIO_0
    PAD_NUM_ROW_0_GPIO_133_OUT           = PAD_NUM_BGPIO_OUT( 81,  0, 1, 0, 0, 1, 0, 0, 0), // ROW_GPIO_0
    PAD_NUM_ROW_0_F6_ROW_0               = PAD_NUM_BGPIO_FUN( 81,  1, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_ROW_1_GPIO_134_IN            = PAD_NUM_BGPIO_IN ( 82,  0, 1, 0, 0, 1, 0, 0, 0), // ROW_GPIO_1
    PAD_NUM_ROW_1_GPIO_134_OUT           = PAD_NUM_BGPIO_OUT( 82,  0, 1, 0, 0, 1, 0, 0, 0), // ROW_GPIO_1
    PAD_NUM_ROW_1_F7_ROW_1               = PAD_NUM_BGPIO_FUN( 82,  1, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_ROW_2_GPIO_135_IN            = PAD_NUM_BGPIO_IN ( 83,  0, 1, 0, 0, 1, 0, 0, 0), // ROW_GPIO_2
    PAD_NUM_ROW_2_GPIO_135_OUT           = PAD_NUM_BGPIO_OUT( 83,  0, 1, 0, 0, 1, 0, 0, 0), // ROW_GPIO_2
    PAD_NUM_ROW_2_F7_ECO2_DUMMY_7        = PAD_NUM_BGPIO_FUN( 83,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_ROW_2_F8_EFUSE_GADDR_3       = PAD_NUM_BGPIO_FUN( 83,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_ROW_2_F9_ROW_2               = PAD_NUM_BGPIO_FUN( 83,  3, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_ROW_3_GPIO_136_IN            = PAD_NUM_BGPIO_IN ( 84,  0, 1, 0, 0, 1, 0, 0, 0), // ROW_GPIO_3
    PAD_NUM_ROW_3_GPIO_136_OUT           = PAD_NUM_BGPIO_OUT( 84,  0, 1, 0, 0, 1, 0, 0, 0), // ROW_GPIO_3
    PAD_NUM_ROW_3_F9_ECO2_DUMMY_8        = PAD_NUM_BGPIO_FUN( 84,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_ROW_3_F10_ROW_3              = PAD_NUM_BGPIO_FUN( 84,  2, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_ROW_4_GPIO_137_IN            = PAD_NUM_BGPIO_IN ( 85,  0, 1, 0, 0, 1, 0, 0, 0), // ROW_GPIO_4
    PAD_NUM_ROW_4_GPIO_137_OUT           = PAD_NUM_BGPIO_OUT( 85,  0, 1, 0, 0, 1, 0, 0, 0), // ROW_GPIO_4
    PAD_NUM_ROW_4_F9_ECO2_DUMMY_13       = PAD_NUM_BGPIO_FUN( 85,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_ROW_4_F10_EFUSE_GADDR_5      = PAD_NUM_BGPIO_FUN( 85,  2, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_ROW_4_F11_ROW_4              = PAD_NUM_BGPIO_FUN( 85,  3, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_ROW_5_GPIO_138_IN            = PAD_NUM_BGPIO_IN ( 86,  0, 1, 0, 0, 1, 0, 0, 0), // ROW_GPIO_5
    PAD_NUM_ROW_5_GPIO_138_OUT           = PAD_NUM_BGPIO_OUT( 86,  0, 1, 0, 0, 1, 0, 0, 0), // ROW_GPIO_5
    PAD_NUM_ROW_5_F8_ECO2_DUMMY_14       = PAD_NUM_BGPIO_FUN( 86,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_ROW_5_F9_ROW_5               = PAD_NUM_BGPIO_FUN( 86,  2, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_COL_0_GPIO_139_IN            = PAD_NUM_BGPIO_IN ( 87,  0, 1, 1, 0, 1, 0, 0, 0), // COL_GPIO_0
    PAD_NUM_COL_0_GPIO_139_OUT           = PAD_NUM_BGPIO_OUT( 87,  0, 1, 1, 0, 1, 0, 0, 0), // COL_GPIO_0
    PAD_NUM_COL_0_F8_COL_0               = PAD_NUM_BGPIO_FUN( 87,  1, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_COL_1_GPIO_140_IN            = PAD_NUM_BGPIO_IN ( 88,  0, 1, 1, 0, 1, 0, 0, 0), // COL_GPIO_1
    PAD_NUM_COL_1_GPIO_140_OUT           = PAD_NUM_BGPIO_OUT( 88,  0, 1, 1, 0, 1, 0, 0, 0), // COL_GPIO_1
    PAD_NUM_COL_1_F8_COL_1               = PAD_NUM_BGPIO_FUN( 88,  1, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_COL_2_GPIO_141_IN            = PAD_NUM_BGPIO_IN ( 89,  0, 1, 1, 0, 1, 0, 0, 0), // COL_GPIO_2
    PAD_NUM_COL_2_GPIO_141_OUT           = PAD_NUM_BGPIO_OUT( 89,  0, 1, 1, 0, 1, 0, 0, 0), // COL_GPIO_2
    PAD_NUM_COL_2_F8_EFUSE_GADDR_4       = PAD_NUM_BGPIO_FUN( 89,  1, 0, 0, 0, 1, 0, 0, 0),
    PAD_NUM_COL_2_F9_COL_2               = PAD_NUM_BGPIO_FUN( 89,  2, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_COL_3_GPIO_142_IN            = PAD_NUM_BGPIO_IN ( 90,  0, 1, 1, 0, 1, 0, 0, 0), // COL_GPIO_3
    PAD_NUM_COL_3_GPIO_142_OUT           = PAD_NUM_BGPIO_OUT( 90,  0, 1, 1, 0, 1, 0, 0, 0), // COL_GPIO_3
    PAD_NUM_COL_3_F8_COL_3               = PAD_NUM_BGPIO_FUN( 90,  1, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_COL_4_GPIO_143_IN            = PAD_NUM_BGPIO_IN ( 91,  0, 1, 1, 0, 1, 0, 0, 0), // COL_GPIO_4
    PAD_NUM_COL_4_GPIO_143_OUT           = PAD_NUM_BGPIO_OUT( 91,  0, 1, 1, 0, 1, 0, 0, 0), // COL_GPIO_4
    PAD_NUM_COL_4_F8_COL_4               = PAD_NUM_BGPIO_FUN( 91,  1, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_COL_5_GPIO_144_IN            = PAD_NUM_BGPIO_IN ( 92,  0, 1, 1, 0, 1, 0, 0, 0), // COL_GPIO_5
    PAD_NUM_COL_5_GPIO_144_OUT           = PAD_NUM_BGPIO_OUT( 92,  0, 1, 1, 0, 1, 0, 0, 0), // COL_GPIO_5
    PAD_NUM_COL_5_F7_COL_5               = PAD_NUM_BGPIO_FUN( 92,  1, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_COL_6_GPIO_145_IN            = PAD_NUM_BGPIO_IN ( 93,  0, 1, 1, 0, 1, 0, 0, 0), // COL_GPIO_6
    PAD_NUM_COL_6_GPIO_145_OUT           = PAD_NUM_BGPIO_OUT( 93,  0, 1, 1, 0, 1, 0, 0, 0), // COL_GPIO_6
    PAD_NUM_COL_6_F7_COL_6               = PAD_NUM_BGPIO_FUN( 93,  1, 0, 0, 0, 1, 0, 0, 0),

    PAD_NUM_USIM1DATA_GPIO_146_IN        = PAD_NUM_BGPIO_IN ( 94,  0, 0, 0, 1, 0, 0, 0, 0), // SIM1_GPIO_0
    PAD_NUM_USIM1DATA_GPIO_146_OUT       = PAD_NUM_BGPIO_OUT( 94,  0, 0, 0, 1, 0, 0, 0, 0), // SIM1_GPIO_0
    PAD_NUM_USIM1DATA_F2_USIM1DATA       = PAD_NUM_BGPIO_FUN( 94,  1, 0, 0, 1, 0, 0, 0, 0),

    PAD_NUM_USIM1RST_GPIO_147_IN         = PAD_NUM_BGPIO_IN ( 95,  0, 0, 0, 1, 0, 0, 0, 0), // SIM1_GPIO_1
    PAD_NUM_USIM1RST_GPIO_147_OUT        = PAD_NUM_BGPIO_OUT( 95,  0, 0, 0, 1, 0, 0, 0, 0), // SIM1_GPIO_1
    PAD_NUM_USIM1RST_F2_USIM1RST         = PAD_NUM_BGPIO_FUN( 95,  1, 0, 0, 1, 0, 0, 0, 0),

    PAD_NUM_USIM1CLK_GPIO_148_IN         = PAD_NUM_BGPIO_IN ( 96,  0, 0, 0, 1, 0, 0, 0, 0), // SIM1_GPIO_2
    PAD_NUM_USIM1CLK_GPIO_148_OUT        = PAD_NUM_BGPIO_OUT( 96,  0, 0, 0, 1, 0, 0, 0, 0), // SIM1_GPIO_2
    PAD_NUM_USIM1CLK_F2_USIM1CLK         = PAD_NUM_BGPIO_FUN( 96,  1, 0, 0, 1, 0, 0, 0, 0),

    PAD_NUM_USIM2RST_GPIO_149_IN         = PAD_NUM_BGPIO_IN ( 97,  0, 0, 0, 1, 0, 0, 0, 0), // SIM2_GPIO_1
    PAD_NUM_USIM2RST_GPIO_149_OUT        = PAD_NUM_BGPIO_OUT( 97,  0, 0, 0, 1, 0, 0, 0, 0), // SIM2_GPIO_1
    PAD_NUM_USIM2RST_F2_USIM2RST         = PAD_NUM_BGPIO_FUN( 97,  1, 0, 0, 1, 0, 0, 0, 0),

    PAD_NUM_USIM2CLK_GPIO_150_IN         = PAD_NUM_BGPIO_IN ( 98,  0, 0, 0, 1, 0, 0, 0, 0), // SIM2_GPIO_2
    PAD_NUM_USIM2CLK_GPIO_150_OUT        = PAD_NUM_BGPIO_OUT( 98,  0, 0, 0, 1, 0, 0, 0, 0), // SIM2_GPIO_2
    PAD_NUM_USIM2CLK_F2_USIM2CLK         = PAD_NUM_BGPIO_FUN( 98,  1, 0, 0, 1, 0, 0, 0, 0),

    PAD_NUM_USIM2DATA_GPIO_151_IN        = PAD_NUM_BGPIO_IN ( 99,  0, 0, 0, 1, 0, 0, 0, 0), // SIM2_GPIO_0
    PAD_NUM_USIM2DATA_GPIO_151_OUT       = PAD_NUM_BGPIO_OUT( 99,  0, 0, 0, 1, 0, 0, 0, 0), // SIM2_GPIO_0
    PAD_NUM_USIM2DATA_F2_USIM2DATA       = PAD_NUM_BGPIO_FUN( 99,  1, 0, 0, 1, 0, 0, 0, 0),

    PAD_NUM_TBUO0_GPIO_152_IN            = PAD_NUM_BGPIO_IN (100,  0, 1, 0, 1, 0, 0, 0, 0), // RF_GPIO_0
    PAD_NUM_TBUO0_GPIO_152_OUT           = PAD_NUM_BGPIO_OUT(100,  0, 1, 0, 1, 0, 0, 0, 0), // RF_GPIO_0
    PAD_NUM_TBUO0_F11_ECO2_DUMMY_9       = PAD_NUM_BGPIO_FUN(100,  1, 0, 0, 1, 0, 0, 0, 0),
    PAD_NUM_TBUO0_F12_WIFI_CLK_EN        = PAD_NUM_BGPIO_FUN(100,  2, 0, 0, 1, 0, 0, 0, 0),
    PAD_NUM_TBUO0_F13_QB_SAVE            = PAD_NUM_BGPIO_FUN(100,  3, 0, 0, 1, 0, 0, 0, 0),
    PAD_NUM_TBUO0_F14_TBUO_0             = PAD_NUM_BGPIO_FUN(100,  4, 0, 0, 1, 0, 0, 0, 0),

    PAD_NUM_TBUO3_GPIO_153_IN            = PAD_NUM_BGPIO_IN (101,  0, 1, 0, 1, 0, 0, 0, 0), // RF_GPIO_3
    PAD_NUM_TBUO3_GPIO_153_OUT           = PAD_NUM_BGPIO_OUT(101,  0, 1, 0, 1, 0, 0, 0, 0), // RF_GPIO_3
    PAD_NUM_TBUO3_F10_ECO2_DUMMY_10      = PAD_NUM_BGPIO_FUN(101,  1, 0, 0, 1, 0, 0, 0, 0),
    PAD_NUM_TBUO3_F11_QB_SAVE            = PAD_NUM_BGPIO_FUN(101,  2, 0, 0, 1, 0, 0, 0, 0),
    PAD_NUM_TBUO3_F12_TBUO_3             = PAD_NUM_BGPIO_FUN(101,  3, 0, 0, 1, 0, 0, 0, 0),

    PAD_NUM_TBUO6_GPIO_154_IN            = PAD_NUM_BGPIO_IN (102,  0, 1, 0, 1, 0, 0, 0, 0), // RF_GPIO_6
    PAD_NUM_TBUO6_GPIO_154_OUT           = PAD_NUM_BGPIO_OUT(102,  0, 1, 0, 1, 0, 0, 0, 0), // RF_GPIO_6
    PAD_NUM_TBUO6_F10_ECO2_DUMMY_12      = PAD_NUM_BGPIO_FUN(102,  1, 0, 0, 1, 0, 0, 0, 0),
    PAD_NUM_TBUO6_F11_SD1_CDZ            = PAD_NUM_BGPIO_FUN(102,  2, 0, 0, 1, 0, 0, 0, 0),
    PAD_NUM_TBUO6_F12_BT_PCM_SDI         = PAD_NUM_BGPIO_FUN(102,  3, 0, 0, 1, 0, 0, 0, 0),
    PAD_NUM_TBUO6_F13_FUART_RX           = PAD_NUM_BGPIO_FUN(102,  4, 0, 0, 1, 0, 0, 0, 0),
    PAD_NUM_TBUO6_F14_QB_SAVE            = PAD_NUM_BGPIO_FUN(102,  5, 0, 0, 1, 0, 0, 0, 0),
    PAD_NUM_TBUO6_F15_TBUO_6             = PAD_NUM_BGPIO_FUN(102,  6, 0, 0, 1, 0, 0, 0, 0),

    PAD_NUM_TBUO2_GPIO_155_IN            = PAD_NUM_BGPIO_IN (103,  0, 1, 0, 1, 0, 0, 0, 0), // RF_GPIO_2
    PAD_NUM_TBUO2_GPIO_155_OUT           = PAD_NUM_BGPIO_OUT(103,  0, 1, 0, 1, 0, 0, 0, 0), // RF_GPIO_2
    PAD_NUM_TBUO2_F9_ECO2_DUMMY_11       = PAD_NUM_BGPIO_FUN(103,  1, 0, 0, 1, 0, 0, 0, 0),
    PAD_NUM_TBUO2_F10_QB_SAVE            = PAD_NUM_BGPIO_FUN(103,  2, 0, 0, 1, 0, 0, 0, 0),
    PAD_NUM_TBUO2_F11_TBUO_2             = PAD_NUM_BGPIO_FUN(103,  3, 0, 0, 1, 0, 0, 0, 0),

    PAD_NUM_TBUO5_GPIO_156_IN            = PAD_NUM_BGPIO_IN (104,  0, 1, 0, 1, 0, 0, 0, 0), // RF_GPIO_5
    PAD_NUM_TBUO5_GPIO_156_OUT           = PAD_NUM_BGPIO_OUT(104,  0, 1, 0, 1, 0, 0, 0, 0), // RF_GPIO_5
    PAD_NUM_TBUO5_F9_ECO2_DUMMY_15       = PAD_NUM_BGPIO_FUN(104,  1, 0, 0, 1, 0, 0, 0, 0),
    PAD_NUM_TBUO5_F10_FUART_TX           = PAD_NUM_BGPIO_FUN(104,  2, 0, 0, 1, 0, 0, 0, 0),
    PAD_NUM_TBUO5_F11_QB_SAVE            = PAD_NUM_BGPIO_FUN(104,  3, 0, 0, 1, 0, 0, 0, 0),
    PAD_NUM_TBUO5_F12_TBUO_5             = PAD_NUM_BGPIO_FUN(104,  4, 0, 0, 1, 0, 0, 0, 0),

    PAD_NUM_TBUO4_GPIO_157_IN            = PAD_NUM_BGPIO_IN (105,  0, 1, 0, 1, 0, 0, 0, 0), // RF_GPIO_4
    PAD_NUM_TBUO4_GPIO_157_OUT           = PAD_NUM_BGPIO_OUT(105,  0, 1, 0, 1, 0, 0, 0, 0), // RF_GPIO_4
    PAD_NUM_TBUO4_F8_ECO2_DUMMY_16       = PAD_NUM_BGPIO_FUN(105,  1, 0, 0, 1, 0, 0, 0, 0),
    PAD_NUM_TBUO4_F9_QB_SAVE             = PAD_NUM_BGPIO_FUN(105,  2, 0, 0, 1, 0, 0, 0, 0),
    PAD_NUM_TBUO4_F10_TBUO_4             = PAD_NUM_BGPIO_FUN(105,  3, 0, 0, 1, 0, 0, 0, 0),

    PAD_NUM_INVALID                   = PAD_NUM_BGPIO_IN(PAD_NUM_MAX_NUM, 0, 0, 0, 0, 0, 0, 0, 0),
}IoChipPadNum_e;

#endif //__HAL_IO_CHIP_PUB_H__

