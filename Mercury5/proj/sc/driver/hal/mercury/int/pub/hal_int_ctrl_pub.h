////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2010 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    Hal_int_ctrl_pub.h
* @version
* @brief   Hal header file for interrupts
*
*/

#ifndef __HAL_INT_CTRL_PUB_H__
#define __HAL_INT_CTRL_PUB_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "hal_ext_int_pub.h"
#include "hal_int_irq_pub.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define IRQCTRL_INT_ON_FIQ  0
#define IRQCTRL_INT_ON_IRQ  1

#define IRQCTRL_CLR_NUM_ALL 0xFFFFFFFF
#define IRQCTRL_CLEARALL    0x00000100
#define IRQCTRL_AUTOACK     0x00000001

#define MAX_ISR_AMOUNT      IT_MAX_NUMBER
#define STDA_TIMER_SCALE    1  //Big3 would be 1
#define MAX_NESTED_LEVEL    16 //NestedLevel

#define INT_GET_NUM(x)      (x) + GIC_SPI_MS_IRQ_START

#define    MS_INT_NUM_IRQ_NONPM_TO_MCU51    INT_NUM_IRQ_NONPM_TO_MCU51
#define    MS_INT_NUM_IRQ_FIQ_FROM_PM       INT_NUM_IRQ_FIQ_FROM_PM
#define    MS_INT_NUM_IRQ_PM_SLEEP          INT_NUM_IRQ_PM_SLEEP
#define    MS_INT_NUM_IRQ_DUMMY_03          INT_NUM_IRQ_DUMMY_03
#define    MS_INT_NUM_IRQ_DUMMY_04          INT_NUM_IRQ_DUMMY_04
#define    MS_INT_NUM_IRQ_FSP               INT_NUM_IRQ_FSP
#define    MS_INT_NUM_IRQ_FLAG_POC          INT_NUM_IRQ_FLAG_POC
#define    MS_INT_NUM_IRQ_POWER_0_NG        INT_NUM_IRQ_POWER_0_NG
#define    MS_INT_NUM_IRQ_POWER_1_NG        INT_NUM_IRQ_POWER_1_NG
#define    MS_INT_NUM_IRQ_DUMMY_09          INT_NUM_IRQ_DUMMY_09
#define    MS_INT_NUM_IRQ_DUMMY_10          INT_NUM_IRQ_DUMMY_10
#define    MS_INT_NUM_IRQ_DUMMY_11          INT_NUM_IRQ_DUMMY_11
#define    MS_INT_NUM_IRQ_PM_ERROR_RESP     INT_NUM_IRQ_PM_ERROR_RESP
#define    MS_INT_NUM_IRQ_USB_INT_P0        INT_NUM_IRQ_USB_INT_P0
#define    MS_INT_NUM_IRQ_UHC_INT_P0        INT_NUM_IRQ_UHC_INT_P0
#define    MS_INT_NUM_IRQ_OTG_INT_P0        INT_NUM_IRQ_OTG_INT_P0
#define    MS_INT_NUM_IRQ_IRQ_FROM_PM       INT_NUM_IRQ_IRQ_FROM_PM
#define    MS_INT_NUM_IRQ_CMDQ              INT_NUM_IRQ_CMDQ
#define    MS_INT_NUM_IRQ_FCIE              INT_NUM_IRQ_FCIE
#define    MS_INT_NUM_IRQ_SDIO              INT_NUM_IRQ_SDIO
#define    MS_INT_NUM_IRQ_SC_TOP            INT_NUM_IRQ_SC_TOP
#define    MS_INT_NUM_IRQ_DUMMY_21          INT_NUM_IRQ_DUMMY_21
#define    MS_INT_NUM_IRQ_PS                INT_NUM_IRQ_PS
#define    MS_INT_NUM_IRQ_WADR_ERROR        INT_NUM_IRQ_WADR_ERROR
#define    MS_INT_NUM_IRQ_PM                INT_NUM_IRQ_PM
#define    MS_INT_NUM_IRQ_ISP               INT_NUM_IRQ_ISP
#define    MS_INT_NUM_IRQ_DUMMY_26          INT_NUM_IRQ_DUMMY_26
#define    MS_INT_NUM_IRQ_HEMCU             INT_NUM_IRQ_HEMCU
#define    MS_INT_NUM_IRQ_MFE               INT_NUM_IRQ_MFE
#define    MS_INT_NUM_IRQ_JPE               INT_NUM_IRQ_JPE
#define    MS_INT_NUM_IRQ_DUMMY_30          INT_NUM_IRQ_USB
#define    MS_INT_NUM_IRQ_DUMMY_31          INT_NUM_IRQ_UHC
#define    MS_INT_NUM_IRQ_DUMMY_32          INT_NUM_IRQ_OTG
#define    MS_INT_NUM_IRQ_MIPI_CSI2         INT_NUM_IRQ_MIPI_CSI2  //MIPI RX 4 Lane
#define    MS_INT_NUM_IRQ_UART_0            INT_NUM_IRQ_UART_0
#define    MS_INT_NUM_IRQ_UART_1            INT_NUM_IRQ_UART_1
#define    MS_INT_NUM_IRQ_MIIC_0            INT_NUM_IRQ_MIIC_0
#define    MS_INT_NUM_IRQ_MIIC_1            INT_NUM_IRQ_MIIC_1
#define    MS_INT_NUM_IRQ_MSPI_0            INT_NUM_IRQ_MSPI_0
#define    MS_INT_NUM_IRQ_MSPI_1            INT_NUM_IRQ_MSPI_1
#define    MS_INT_NUM_IRQ_BDMA_0            INT_NUM_IRQ_BDMA_0
#define    MS_INT_NUM_IRQ_BDMA_1            INT_NUM_IRQ_BDMA_1
#define    MS_INT_NUM_IRQ_BACH              INT_NUM_IRQ_BACH
#define    MS_INT_NUM_IRQ_KEYPAD            INT_NUM_IRQ_KEYPAD
#define    MS_INT_NUM_IRQ_RTC               INT_NUM_IRQ_RTC
#define    MS_INT_NUM_IRQ_SAR               INT_NUM_IRQ_SAR
#define    MS_INT_NUM_IRQ_IMI               INT_NUM_IRQ_IMI
#define    MS_INT_NUM_IRQ_FUART             INT_NUM_IRQ_FUART
#define    MS_INT_NUM_IRQ_URDMA             INT_NUM_IRQ_URDMA
#define    MS_INT_NUM_IRQ_MIU               INT_NUM_IRQ_MIU
#define    MS_INT_NUM_IRQ_GOP               INT_NUM_IRQ_GOP
#define    MS_INT_NUM_IRQ_RIU_ERROR_RESP    INT_NUM_IRQ_RIU_ERROR_RESP
#if defined(__MV5_ON_I3__)
#define    MS_INT_NUM_IRQ_CMDQ1             INT_NUM_IRQ_DUMMY_52
#define    MS_INT_NUM_IRQ_CMDQ2             INT_NUM_IRQ_DUMMY_53
#define    MS_INT_NUM_IRQ_USB               INT_NUM_IRQ_DUMMY_54
#define    MS_INT_NUM_IRQ_UHC               INT_NUM_IRQ_DUMMY_55
#define    MS_INT_NUM_IRQ_DUMMY_56          INT_NUM_IRQ_DUMMY_56
#define    MS_INT_NUM_IRQ_LDC               INT_NUM_IRQ_DUMMY_57
#define    MS_INT_NUM_IRQ_SC1_TOP           INT_NUM_IRQ_DUMMY_58
#define    MS_INT_NUM_IRQ_SC2_TOP           INT_NUM_IRQ_DUMMY_59
#define    MS_INT_NUM_IRQ_SD                INT_NUM_IRQ_DUMMY_60
#define    MS_INT_NUM_IRQ_SD_OSP            INT_NUM_IRQ_DUMMY_61
#define    MS_INT_NUM_IRQ_DC                INT_NUM_IRQ_DUMMY_62	//MVOP interrupt
#define    MS_INT_NUM_IRQ_DMA2CPU           INT_NUM_IRQ_DUMMY_63
#define    MS_INT_NUM_IRQ_HVD               INT_NUM_IRQ_DUMMY_64
#define    MS_INT_NUM_IRQ_MSPI2             INT_NUM_IRQ_DUMMY_65
#define    MS_INT_NUM_IRQ_UART2             INT_NUM_IRQ_DUMMY_66
#define    MS_INT_NUM_IRQ_MIIC_2            INT_NUM_IRQ_DUMMY_67
#define    MS_INT_NUM_IRQ_MIIC_3            INT_NUM_IRQ_DUMMY_68
#define    MS_INT_NUM_IRQ_VIF               INT_NUM_IRQ_DUMMY_69
#define    MS_INT_NUM_IRQ_MIPI_TX_CSI       INT_NUM_IRQ_DUMMY_70
#define    MS_INT_NUM_IRQ_JDC0              INT_NUM_IRQ_DUMMY_71
#define    MS_INT_NUM_IRQ_JDC1              INT_NUM_IRQ_DUMMY_72
#define    MS_INT_NUM_IRQ_DEC_GOP           INT_NUM_IRQ_DUMMY_73
#define    MS_INT_NUM_IRQ_MIPI_CSI2_1       INT_NUM_IRQ_DUMMY_74    //MIPI RX 2 Lane
#define    MS_INT_NUM_IRQ_MIPI_TX_DSI       INT_NUM_IRQ_DUMMY_75
#define    MS_INT_NUM_IRQ_DIP               INT_NUM_IRQ_DUMMY_76
#define    MS_INT_NUM_IRQ_DIP_CMDQ          INT_NUM_IRQ_DUMMY_77
#define    MS_INT_NUM_IRQ_AE_UPD_OSDB3      INT_NUM_IRQ_DUMMY_78
#define    MS_INT_NUM_IRQ_AE_UPD_OSDB4      INT_NUM_IRQ_DUMMY_79
#define    MS_INT_NUM_IRQ_AE_UPD_OSDB5      INT_NUM_IRQ_DUMMY_80
#define    MS_INT_NUM_IRQ_VIP_HIST_DONE     INT_NUM_IRQ_DUMMY_81
#define    MS_INT_NUM_IRQ_LCD               INT_NUM_IRQ_DUMMY_82    //LCD panel interrupt
#define    MS_INT_NUM_IRQ_VD_HVD_R2         INT_NUM_IRQ_DUMMY_83
#else
#define    MS_INT_NUM_IRQ_CMDQ1             INT_NUM_IRQ_CMDQ1
#define    MS_INT_NUM_IRQ_CMDQ2             INT_NUM_IRQ_CMDQ2
#define    MS_INT_NUM_IRQ_USB               INT_NUM_IRQ_USB_INT_P1
#define    MS_INT_NUM_IRQ_UHC               INT_NUM_IRQ_UHC_INT_P1
#define    MS_INT_NUM_IRQ_DUMMY_56          INT_NUM_IRQ_DUMMY_56
#define    MS_INT_NUM_IRQ_LDC               INT_NUM_IRQ_LDC
#define    MS_INT_NUM_IRQ_SC1_TOP           INT_NUM_IRQ_SC1_TOP
#define    MS_INT_NUM_IRQ_SC2_TOP           INT_NUM_IRQ_SC2_TOP
#define    MS_INT_NUM_IRQ_SD                INT_NUM_IRQ_SD
#define    MS_INT_NUM_IRQ_SD_OSP            INT_NUM_IRQ_SD_OSP
#define    MS_INT_NUM_IRQ_DC                INT_NUM_IRQ_DC              //MVOP interrupt
#define    MS_INT_NUM_IRQ_DMA2CPU           INT_NUM_IRQ_DMA2CPU
#define    MS_INT_NUM_IRQ_HVD               INT_NUM_IRQ_HVD
#define    MS_INT_NUM_IRQ_MSPI2             INT_NUM_IRQ_MSPI2
#define    MS_INT_NUM_IRQ_UART_2            INT_NUM_IRQ_UART2
#define    MS_INT_NUM_IRQ_MIIC_2            INT_NUM_IRQ_MIIC2
#define    MS_INT_NUM_IRQ_MIIC_3            INT_NUM_IRQ_MIIC3
#define    MS_INT_NUM_IRQ_VIF               INT_NUM_IRQ_VIF
#define    MS_INT_NUM_IRQ_MIPI_TX_CSI       INT_NUM_IRQ_MIPI_TX_CSI
#define    MS_INT_NUM_IRQ_JDC0              INT_NUM_IRQ_JDC0
#define    MS_INT_NUM_IRQ_JDC1              INT_NUM_IRQ_JDC1
#define    MS_INT_NUM_IRQ_DEC_GOP           INT_NUM_IRQ_DEC_GOP
#define    MS_INT_NUM_IRQ_MIPI_CSI2_1       INT_NUM_IRQ_MIPI_CSI2_INT_1 //MIPI RX 2 Lane
#define    MS_INT_NUM_IRQ_MIPI_TX_DSI       INT_NUM_IRQ_MIPI_TX_DSI
#define    MS_INT_NUM_IRQ_DIP               INT_NUM_IRQ_DIP0
#define    MS_INT_NUM_IRQ_DIP_CMDQ          INT_NUM_IRQ_DIP_CMDQ
#define    MS_INT_NUM_IRQ_AE_UPD_OSDB3      INT_NUM_IRQ_AE_UPD_DONE_OSDB3
#define    MS_INT_NUM_IRQ_AE_UPD_OSDB4      INT_NUM_IRQ_AE_UPD_DONE_OSDB4
#define    MS_INT_NUM_IRQ_AE_UPD_OSDB5      INT_NUM_IRQ_AE_UPD_DONE_OSDB5
#define    MS_INT_NUM_IRQ_VIP_HIST_DONE     INT_NUM_IRQ_VIP_HIST_DONE
#define    MS_INT_NUM_IRQ_LCD               INT_NUM_IRQ_LCD             //LCD panel interrupt
#define    MS_INT_NUM_IRQ_VD_HVD_R2         INT_NUM_IRQ_VD_HVD_R2
#endif
#define    MS_INT_NUM_IRQ_DUMMY_84          INT_NUM_IRQ_DUMMY_84
#define    MS_INT_NUM_IRQ_DUMMY_85          INT_NUM_IRQ_DUMMY_85
#define    MS_INT_NUM_IRQ_DUMMY_86          INT_NUM_IRQ_DUMMY_86
#define    MS_INT_NUM_IRQ_DUMMY_87          INT_NUM_IRQ_DUMMY_87
#define    MS_INT_NUM_IRQ_SIGNAL            INT_NUM_IRQ_SIGNAL
#define    MS_INT_NUM_IRQ_DUMMY_89          INT_NUM_IRQ_DUMMY_89
#define    MS_INT_NUM_IRQ_DUMMY_90          INT_NUM_IRQ_DUMMY_90
#define    MS_INT_NUM_IRQ_REGISTER_TABLE_1  INT_NUM_IRQ_DUMMY_REGISTER_TABLE_1
#define    MS_INT_NUM_IRQ_REGISTER_TABLE_0  INT_NUM_IRQ_DUMMY_REGISTER_TABLE_0
#define    MS_INT_NUM_IRQ_DUMMY_93          INT_NUM_IRQ_DUMMY_93
#define    MS_INT_NUM_IRQ_DUMMY_94          INT_NUM_IRQ_DUMMY_94
#define    MS_INT_NUM_IRQ_DUMMY_95          INT_NUM_IRQ_DUMMY_95
#define    MS_INT_NUM_FIQ_TIMER_0           INT_NUM_FIQ_TIMER_0
#define    MS_INT_NUM_FIQ_TIMER_1           INT_NUM_FIQ_TIMER_1
#define    MS_INT_NUM_FIQ_WDT               INT_NUM_FIQ_WDT
#define    MS_INT_NUM_FIQ_IR                INT_NUM_FIQ_IR
#define    MS_INT_NUM_FIQ_IR_RC             INT_NUM_FIQ_IR_RC
#define    MS_INT_NUM_FIQ_POWER_0_NG        INT_NUM_FIQ_POWER_0_NG
#define    MS_INT_NUM_FIQ_POWER_1_NG        INT_NUM_FIQ_POWER_1_NG
#define    MS_INT_NUM_FIQ_POWER_2_NG        INT_NUM_FIQ_POWER_2_NG
#define    MS_INT_NUM_FIQ_PM_XIU_TIMEOUT    INT_NUM_FIQ_PM_XIU_TIMEOUT
#define    MS_INT_NUM_FIQ_DUMMY_09          INT_NUM_FIQ_DUMMY_09
#define    MS_INT_NUM_FIQ_DUMMY_10          INT_NUM_FIQ_DUMMY_10
#define    MS_INT_NUM_FIQ_DUMMY_11          INT_NUM_FIQ_DUMMY_11
#define    MS_INT_NUM_FIQ_TIMER_2           INT_NUM_FIQ_TIMER_2
#define    MS_INT_NUM_FIQ_DUMMY_13          INT_NUM_FIQ_DUMMY_13
#define    MS_INT_NUM_FIQ_DUMMY_14          INT_NUM_FIQ_DUMMY_14
#define    MS_INT_NUM_FIQ_DUMMY_15          INT_NUM_FIQ_DUMMY_15
#define    MS_INT_NUM_FIQ_FIQ_FROM_PM       INT_NUM_FIQ_FIQ_FROM_PM
#define    MS_INT_NUM_FIQ_MCU51_TO_ARM      INT_NUM_FIQ_MCU51_TO_ARM
#define    MS_INT_NUM_FIQ_ARM_TO_MCU51      INT_NUM_FIQ_ARM_TO_MCU51
#define    MS_INT_NUM_FIQ_DUMMY_19          INT_NUM_FIQ_DUMMY_19
#define    MS_INT_NUM_FIQ_DUMMY_20          INT_NUM_FIQ_DUMMY_20
#define    MS_INT_NUM_FIQ_LAN_ESD           INT_NUM_FIQ_LAN_ESD
#define    MS_INT_NUM_FIQ_XIU_TIMEOUT       INT_NUM_FIQ_XIU_TIMEOUT
#define    MS_INT_NUM_FIQ_SD_CDZ            INT_NUM_FIQ_SD_CDZ
#define    MS_INT_NUM_FIQ_SAR_GPIO_0        INT_NUM_FIQ_SAR_GPIO_0
#define    MS_INT_NUM_FIQ_SAR_GPIO_1        INT_NUM_FIQ_SAR_GPIO_1
#define    MS_INT_NUM_FIQ_SAR_GPIO_2        INT_NUM_FIQ_SAR_GPIO_2
#define    MS_INT_NUM_FIQ_SAR_GPIO_3        INT_NUM_FIQ_SAR_GPIO_3
#define    MS_INT_NUM_FIQ_FUART_GPIO_0      INT_NUM_FIQ_SPI0_GPIO_0
#define    MS_INT_NUM_FIQ_FUART_GPIO_2      INT_NUM_FIQ_FUART_GPIO_2
#define    MS_INT_NUM_FIQ_SPI0_GPIO_3       INT_NUM_FIQ_SPI0_GPIO_3
#define    MS_INT_NUM_FIQ_SPI0_GPIO_2       INT_NUM_FIQ_SPI0_GPIO_2
#define    MS_INT_NUM_FIQ_SPI0_GPIO_1       INT_NUM_FIQ_SPI0_GPIO_1
#define    MS_INT_NUM_FIQ_SPI0_GPIO_0       INT_NUM_FIQ_SPI0_GPIO_0
#define    MS_INT_NUM_FIQ_SPI0_GPIO_4       INT_NUM_FIQ_SPI0_GPIO_4
#define    MS_INT_NUM_FIQ_I2C0_GPIO_1       INT_NUM_FIQ_I2C0_GPIO_1
#define    MS_INT_NUM_FIQ_SR0D_GPIO_0       INT_NUM_FIQ_SR0D_GPIO_0
#define    MS_INT_NUM_FIQ_SR0D_GPIO_1       INT_NUM_FIQ_SR0D_GPIO_1
#define    MS_INT_NUM_FIQ_SR0_GPIO_5        INT_NUM_FIQ_SR0_GPIO_5
#define    MS_INT_NUM_FIQ_SR0_GPIO_6        INT_NUM_FIQ_SR0_GPIO_6
#define    MS_INT_NUM_FIQ_SR1_GPIO_3        INT_NUM_FIQ_SR1_GPIO_3
#define    MS_INT_NUM_FIQ_SR1_GPIO_4        INT_NUM_FIQ_SR1_GPIO_4
#define    MS_INT_NUM_FIQ_SR1D_GPIO_4       INT_NUM_FIQ_SR1D_GPIO_4
#define    MS_INT_NUM_FIQ_SR1D_GPIO_5       INT_NUM_FIQ_SR1D_GPIO_5
#define    MS_INT_NUM_FIQ_LCD_GPIO_24       INT_NUM_FIQ_LCD_GPIO_24
#define    MS_INT_NUM_FIQ_LCD_GPIO_25       INT_NUM_FIQ_LCD_GPIO_25
#define    MS_INT_NUM_FIQ_LCD_GPIO_2        INT_NUM_FIQ_LCD_GPIO_2
#define    MS_INT_NUM_FIQ_LCD_GPIO_12       INT_NUM_FIQ_LCD_GPIO_12
#define    MS_INT_NUM_FIQ_LCD_GPIO_13       INT_NUM_FIQ_LCD_GPIO_13
#define    MS_INT_NUM_FIQ_LCD_GPIO_15       INT_NUM_FIQ_LCD_GPIO_15
#define    MS_INT_NUM_FIQ_LCD_GPIO_18       INT_NUM_FIQ_LCD_GPIO_18
#define    MS_INT_NUM_FIQ_LCD_GPIO_19       INT_NUM_FIQ_LCD_GPIO_19
#define    MS_INT_NUM_FIQ_LCD_GPIO_20       INT_NUM_FIQ_LCD_GPIO_20
#define    MS_INT_NUM_FIQ_LCD_GPIO_21       INT_NUM_FIQ_LCD_GPIO_21
#define    MS_INT_NUM_FIQ_LCD_GPIO_31       INT_NUM_FIQ_LCD_GPIO_31
#define    MS_INT_NUM_FIQ_LCD_GPIO_32       INT_NUM_FIQ_LCD_GPIO_32
#define    MS_INT_NUM_FIQ_LCD_GPIO_33       INT_NUM_FIQ_LCD_GPIO_33
#define    MS_INT_NUM_FIQ_LCD_GPIO_34       INT_NUM_FIQ_LCD_GPIO_34
#define    MS_INT_NUM_UART0_GPIO_0          INT_NUM_UART0_GPIO_0
#define    MS_INT_NUM_UART0_GPIO_1          INT_NUM_UART0_GPIO_1
#define    MS_INT_NUM_FIQ_DUMMY_60          INT_NUM_FIQ_DUMMY_60
#define    MS_INT_NUM_FIQ_DUMMY_61          INT_NUM_FIQ_DUMMY_61
#define    MS_INT_NUM_FIQ_DUMMY_62          INT_NUM_FIQ_DUMMY_62
#define    MS_INT_NUM_FIQ_DUMMY_63          INT_NUM_FIQ_DUMMY_63

typedef enum
{
    INT_NUM_IRQ_NONPM_TO_MCU51 = 0,   //000h:0
    INT_NUM_IRQ_FIQ_FROM_PM,          //001h:1
    INT_NUM_IRQ_PM_SLEEP,             //002h:2
    INT_NUM_IRQ_DUMMY_03,             //003h:3
    INT_NUM_IRQ_DUMMY_04,             //004h:4
    INT_NUM_IRQ_FSP,                  //005h:5
    INT_NUM_IRQ_FLAG_POC,             //006h:6
    INT_NUM_IRQ_POWER_0_NG,           //007h:7
    INT_NUM_IRQ_POWER_1_NG,           //008h:8
    INT_NUM_IRQ_DUMMY_09,             //009h:9
    INT_NUM_IRQ_DUMMY_10,             //00Ah:10
    INT_NUM_IRQ_DUMMY_11,             //00Bh:11
    INT_NUM_IRQ_PM_ERROR_RESP,        //00Ch:12
    INT_NUM_IRQ_USB_INT_P0,           //00Dh:13
    INT_NUM_IRQ_UHC_INT_P0,           //00Eh:14
    INT_NUM_IRQ_OTG_INT_P0,           //00Fh:15
    INT_NUM_IRQ_IRQ_FROM_PM,          //010h:16
    INT_NUM_IRQ_CMDQ,                 //011h:17
    INT_NUM_IRQ_FCIE,                 //012h:18
    INT_NUM_IRQ_SDIO,                 //013h:19
    INT_NUM_IRQ_SC_TOP,               //014h:20
    INT_NUM_IRQ_DUMMY_21,             //015h:21
    INT_NUM_IRQ_PS,                   //016h:22
    INT_NUM_IRQ_WADR_ERROR,           //017h:23
    INT_NUM_IRQ_PM,                   //018h:24
    INT_NUM_IRQ_ISP,                  //019h:25
    INT_NUM_IRQ_DUMMY_26,             //01Ah:26
    INT_NUM_IRQ_HEMCU,                //01Bh:27
    INT_NUM_IRQ_MFE,                  //01Ch:28
    INT_NUM_IRQ_JPE,                  //01Dh:29
    INT_NUM_IRQ_DUMMY_30,             //01Eh:30
    INT_NUM_IRQ_DUMMY_31,             //01Fh:31
    INT_NUM_IRQ_DUMMY_32,             //020h:32
    INT_NUM_IRQ_MIPI_CSI2,            //021h:33
    INT_NUM_IRQ_UART_0,               //022h:34
    INT_NUM_IRQ_UART_1,               //023h:35
    INT_NUM_IRQ_MIIC_0,               //024h:36
    INT_NUM_IRQ_MIIC_1,               //025h:37
    INT_NUM_IRQ_MSPI_0,               //026h:38
    INT_NUM_IRQ_MSPI_1,               //027h:39
    INT_NUM_IRQ_BDMA_0,               //028h:40
    INT_NUM_IRQ_BDMA_1,               //029h:41
    INT_NUM_IRQ_BACH,                 //02Ah:42
    INT_NUM_IRQ_KEYPAD,               //02Bh:43
    INT_NUM_IRQ_RTC,                  //02Ch:44
    INT_NUM_IRQ_SAR,                  //02Dh:45
    INT_NUM_IRQ_IMI,                  //02Eh:46
    INT_NUM_IRQ_FUART,                //02Fh:47
    INT_NUM_IRQ_URDMA,                //030h:48
    INT_NUM_IRQ_MIU,                  //031h:49
    INT_NUM_IRQ_GOP,                  //032h:50
    INT_NUM_IRQ_RIU_ERROR_RESP,       //033h:51
    INT_NUM_IRQ_CMDQ1,                //034h:52
    INT_NUM_IRQ_CMDQ2,                //035h:53
    INT_NUM_IRQ_USB_INT_P1,           //036h:54
    INT_NUM_IRQ_UHC_INT_P1,           //037h:55
    INT_NUM_IRQ_DUMMY_56,             //038h:56
    INT_NUM_IRQ_LDC,                  //039h:57
    INT_NUM_IRQ_SC1_TOP,              //03Ah:58
    INT_NUM_IRQ_SC2_TOP,              //03Bh:59
    INT_NUM_IRQ_SD,                   //03Ch:60
    INT_NUM_IRQ_SD_OSP,               //03Dh:61
    INT_NUM_IRQ_DC,                   //03Eh:62
    INT_NUM_IRQ_DMA2CPU,              //03Fh:63
#if defined(__MV5_ON_I3__)
    INT_NUM_FIQ_TIMER_0,
    INT_NUM_FIQ_TIMER_1,
    INT_NUM_FIQ_WDT,
    INT_NUM_FIQ_IR,
    INT_NUM_FIQ_IR_RC,
    INT_NUM_FIQ_POWER_0_NG,
    INT_NUM_FIQ_POWER_1_NG,
    INT_NUM_FIQ_POWER_2_NG,
    INT_NUM_FIQ_PM_XIU_TIMEOUT,
    INT_NUM_FIQ_DUMMY_09,
    INT_NUM_FIQ_DUMMY_10,
    INT_NUM_FIQ_DUMMY_11,
    INT_NUM_FIQ_TIMER_2,
    INT_NUM_FIQ_DUMMY_13,
    INT_NUM_FIQ_DUMMY_14,
    INT_NUM_FIQ_DUMMY_15,
    INT_NUM_FIQ_FIQ_FROM_PM,
    INT_NUM_FIQ_MCU51_TO_ARM,
    INT_NUM_FIQ_ARM_TO_MCU51,
    INT_NUM_FIQ_DUMMY_19,
    INT_NUM_FIQ_DUMMY_20,
    INT_NUM_FIQ_LAN_ESN,
    INT_NUM_FIQ_XIU_TIMEOUT,
    INT_NUM_FIQ_SD_CDZ,
    INT_NUM_FIQ_SAR_GPIO_0,
    INT_NUM_FIQ_SAR_GPIO_1,
    INT_NUM_FIQ_SAR_GPIO_2,
    INT_NUM_FIQ_SAR_GPIO_3,
    INT_NUM_FIQ_SPI0_GPIO_0,
    INT_NUM_FIQ_SPI0_GPIO_1,
    INT_NUM_FIQ_SPI0_GPIO_2,
    INT_NUM_FIQ_SPI0_GPIO_3,
    INT_NUM_IRQ_DUMMY_64, //__MV5_FPGA__ begin.
    INT_NUM_IRQ_DUMMY_65,
    INT_NUM_IRQ_DUMMY_66,
    INT_NUM_IRQ_DUMMY_67,
    INT_NUM_IRQ_DUMMY_68,
    INT_NUM_IRQ_DUMMY_69,
    INT_NUM_IRQ_DUMMY_70,
    INT_NUM_IRQ_DUMMY_71,
    INT_NUM_IRQ_DUMMY_72,
    INT_NUM_IRQ_DUMMY_73,
    INT_NUM_IRQ_DUMMY_74,
    INT_NUM_IRQ_DUMMY_75,
    INT_NUM_IRQ_DUMMY_76,
    INT_NUM_IRQ_DUMMY_77,
    INT_NUM_IRQ_DUMMY_78,
    INT_NUM_IRQ_DUMMY_79,
    INT_NUM_IRQ_DUMMY_80,
    INT_NUM_IRQ_DUMMY_81,
    INT_NUM_IRQ_DUMMY_82,
    INT_NUM_IRQ_DUMMY_83,
    INT_NUM_IRQ_DUMMY_84,
    INT_NUM_IRQ_DUMMY_85,
    INT_NUM_IRQ_DUMMY_86,
    INT_NUM_IRQ_DUMMY_87,
    INT_NUM_IRQ_DUMMY_88,
    INT_NUM_IRQ_DUMMY_89,
    INT_NUM_IRQ_DUMMY_90,
    INT_NUM_IRQ_DUMMY_91,
    INT_NUM_IRQ_DUMMY_92,
    INT_NUM_IRQ_DUMMY_93,
    INT_NUM_IRQ_DUMMY_94,
    INT_NUM_IRQ_DUMMY_95, //__MV5_FPGA__ end.

#else
    INT_NUM_IRQ_HVD,                  //040h:64 //__MV5_FPGA__ begin.
    INT_NUM_IRQ_MSPI2,                //041h:65
    INT_NUM_IRQ_UART2,                //042h:66
    INT_NUM_IRQ_MIIC2,                //043h:67
    INT_NUM_IRQ_MIIC3,                //044h:68
    INT_NUM_IRQ_VIF,                  //045h:69
    INT_NUM_IRQ_MIPI_TX_CSI,          //046h:70
    INT_NUM_IRQ_JDC0,                 //047h:71
    INT_NUM_IRQ_JDC1,                 //048h:72
    INT_NUM_IRQ_DEC_GOP,              //049h:73
    INT_NUM_IRQ_MIPI_CSI2_INT_1,      //04Ah:74
    INT_NUM_IRQ_MIPI_TX_DSI,          //04Bh:75
    INT_NUM_IRQ_DIP0,                 //04Ch:76
    INT_NUM_IRQ_DIP_CMDQ,             //04Dh:77
    INT_NUM_IRQ_AE_UPD_DONE_OSDB3,    //04Eh:78
    INT_NUM_IRQ_AE_UPD_DONE_OSDB4,    //04Fh:79
    INT_NUM_IRQ_AE_UPD_DONE_OSDB5,    //050h:80
    INT_NUM_IRQ_VIP_HIST_DONE,        //051h:81
    INT_NUM_IRQ_LCD,                  //052h:82
    INT_NUM_IRQ_VD_HVD_R2,            //053h:83
    INT_NUM_IRQ_DUMMY_84,             //054h:84
    INT_NUM_IRQ_DUMMY_85,             //055h:85
    INT_NUM_IRQ_DUMMY_86,             //056h:86
    INT_NUM_IRQ_DUMMY_87,             //057h:87
    INT_NUM_IRQ_SIGNAL,               //058h:88
    INT_NUM_IRQ_DUMMY_89,             //059h:89
    INT_NUM_IRQ_DUMMY_90,             //05Ah:90
    INT_NUM_IRQ_DUMMY_REGISTER_TABLE_1, //05bh:91
    INT_NUM_IRQ_DUMMY_REGISTER_TABLE_0, //05Ch:92
    INT_NUM_IRQ_DUMMY_93,             //05Dh:93
    INT_NUM_IRQ_DUMMY_94,             //05Eh:94
    INT_NUM_IRQ_DUMMY_95,             //05Fh:95 //__MV5_FPGA__ end.

    INT_NUM_FIQ_TIMER_0,              //060h:96
    INT_NUM_FIQ_TIMER_1,              //061h:97
    INT_NUM_FIQ_WDT,                  //062h:98
    INT_NUM_FIQ_IR,                   //063h:99
    INT_NUM_FIQ_IR_RC,                //064h:100
    INT_NUM_FIQ_POWER_0_NG,           //065h:101
    INT_NUM_FIQ_POWER_1_NG,           //066h:102
    INT_NUM_FIQ_POWER_2_NG,           //067h:103
    INT_NUM_FIQ_PM_XIU_TIMEOUT,       //068h:104
    INT_NUM_FIQ_DUMMY_09,             //069h:105
    INT_NUM_FIQ_DUMMY_10,             //06Ah:106
    INT_NUM_FIQ_DUMMY_11,             //06Bh:107
    INT_NUM_FIQ_TIMER_2,              //06Ch:108
    INT_NUM_FIQ_DUMMY_13,             //06Dh:109
    INT_NUM_FIQ_DUMMY_14,             //06Eh:110
    INT_NUM_FIQ_DUMMY_15,             //06Fh:111
    INT_NUM_FIQ_FIQ_FROM_PM,          //070h:112
    INT_NUM_FIQ_MCU51_TO_ARM,         //071h:113
    INT_NUM_FIQ_ARM_TO_MCU51,         //072h:114
    INT_NUM_FIQ_DUMMY_19,             //073h:115
    INT_NUM_FIQ_DUMMY_20,             //074h:116
    INT_NUM_FIQ_LAN_ESD,              //075h:117
    INT_NUM_FIQ_XIU_TIMEOUT,          //076h:118
    INT_NUM_FIQ_SD_CDZ,               //077h:119
    INT_NUM_FIQ_SAR_GPIO_0,           //078h:120
    INT_NUM_FIQ_SAR_GPIO_1,           //079h:121
    INT_NUM_FIQ_SAR_GPIO_2,           //07Ah:122
    INT_NUM_FIQ_SAR_GPIO_3,           //07Bh:123
    INT_NUM_FIQ_FUART_GPIO_0,         //07Ch:124
    INT_NUM_FIQ_FUART_GPIO_2,         //07Dh:125
    INT_NUM_FIQ_SPI0_GPIO_3,          //07Eh:126
    INT_NUM_FIQ_SPI0_GPIO_2,          //07Fh:127
    INT_NUM_FIQ_SPI0_GPIO_1,          //080h:128
    INT_NUM_FIQ_SPI0_GPIO_0,          //081h:129
    INT_NUM_FIQ_SPI0_GPIO_4,          //082h:130
    INT_NUM_FIQ_I2C0_GPIO_1,          //083h:131
    INT_NUM_FIQ_SR0D_GPIO_0,          //084h:132
    INT_NUM_FIQ_SR0D_GPIO_1,          //085h:133
    INT_NUM_FIQ_SR0_GPIO_5,           //086h:134
    INT_NUM_FIQ_SR0_GPIO_6,           //087h:135
    INT_NUM_FIQ_SR1_GPIO_3,           //088h:136
    INT_NUM_FIQ_SR1_GPIO_4,           //089h:137
    INT_NUM_FIQ_SR1D_GPIO_4,          //08Ah:138
    INT_NUM_FIQ_SR1D_GPIO_5,          //08Bh:139
    INT_NUM_FIQ_LCD_GPIO_24,          //08Ch:140
    INT_NUM_FIQ_LCD_GPIO_25,          //08Dh:141
    INT_NUM_FIQ_LCD_GPIO_2,           //08eh:142
    INT_NUM_FIQ_LCD_GPIO_12,          //08Fh:143
    INT_NUM_FIQ_LCD_GPIO_13,          //090h:144
    INT_NUM_FIQ_LCD_GPIO_15,          //091h:145
    INT_NUM_FIQ_LCD_GPIO_18,          //092h:146
    INT_NUM_FIQ_LCD_GPIO_19,          //093h:147
    INT_NUM_FIQ_LCD_GPIO_20,          //094h:148
    INT_NUM_FIQ_LCD_GPIO_21,          //095h:149
    INT_NUM_FIQ_LCD_GPIO_31,          //096h:150
    INT_NUM_FIQ_LCD_GPIO_32,          //097h:151
    INT_NUM_FIQ_LCD_GPIO_33,          //098h:152
    INT_NUM_FIQ_LCD_GPIO_34,          //099h:153
    INT_NUM_UART0_GPIO_0,             //09Ah:154
    INT_NUM_UART0_GPIO_1,             //09Bh:155
    INT_NUM_FIQ_DUMMY_60,             //09Ch:156
    INT_NUM_FIQ_DUMMY_61,             //09Dh:157
    INT_NUM_FIQ_DUMMY_62,             //09Eh:158
    INT_NUM_FIQ_DUMMY_63,             //09Fh:159
#endif
    INT_NUM_MAX                       //0A0h:160
} IntNumber_e;

typedef union
{
    IntcParam_t   intc;
} IntInitParam_u;

/*=============================================================*/
// Global function definition
/*=============================================================*/

#ifdef __I_SW__
void __enable_irqfiq(void); //for i_sw
#endif

#endif // __HAL_INT_CTRL_PUB_H__

