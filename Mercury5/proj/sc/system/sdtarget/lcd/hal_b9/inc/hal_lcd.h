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
* @file    hal_lcd.h
* @version
* @brief   This module defines the Display driver hal layer
*
*/

#ifndef __HAL_LCD_H__
#define __HAL_LCD_H__

/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "vm_types.ht"

/**
 *  @brief The structure defines the device information
 */
typedef enum {
    LCD_PANEL_TYPE_0 = 0,
    LCD_PANEL_TYPE_1,
    LCD_PANEL_TYPE_2,
    LCD_PANEL_TYPE_3,
    LCD_PANEL_TYPE_4,
    LCD_PANEL_TYPE_5,
    LCD_PANEL_TYPE_6,
}dev_LcdPanelType_e;

#ifdef __LCD_PANEL_DETECT_BY_ADC_DRV__
void HalLcdConfigLCDPanelType(void);
u16 HalLcdGetLcdPanelADC(void);
dev_LcdPanelType_e HalLcdGetLCDPanelType(void);
#endif

#ifdef __DUAL_LCD__
void HalLcdSetCS1Config(void);
#endif

void HalLcdEnableGpioRstzOutputLow(void);
void HalLcdDisableGpioRstz(void);


#endif //__HAL_LCD_H__

