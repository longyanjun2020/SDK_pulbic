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
* @file    drv_backlight_wrapper.h
* @version
* @brief   Wrapper header file for customer backlight driver to call HAL layer
*
*/

#ifndef __DRV_BACKLIGHT_API_H__
#define __DRV_BACKLIGHT_API_H__

#include "vm_types.ht"
#include "drv_backlight_forward.h"

/** WrapperBacklightWLedToggle
* @brief        Wrapper for backlight to access wled hal toggle.
* @param[in]    nLevel: backlight level
* @retval       DrvBacklightErrCode_e error code
*
*/
DrvBacklightErrCode_e WrapperBacklightWLedToggle(u16 nLevel);

#ifdef __SUBBACKLIGHT_DRV__
/** WrapperSubBacklightToggle
* @brief        Wrapper for sub backlight to access hal toggle.
* @param[in]    nLevel: sub backlight level
* @retval       DrvBacklightErrCode_e error code
*
*/
DrvBacklightErrCode_e WrapperSubBacklightToggle(u16 nLevel);
#endif

#ifdef __WLED_SHUNT_SUPPORT__
/** WrapperBacklightWLedSetShunt
* @brief        Wrapper for backlight to set shunt wled hal.
* @param[in]    channel1: 1 enable, 0 disable
* @param[in]    channel2: 1 enable, 0 disable
* @param[in]    channel3: 1 enable, 0 disable
* @param[in]    channel4: 1 enable, 0 disable
* @retval       DrvBacklightErrCode_e error code
*
*/
DrvBacklightErrCode_e WrapperBacklightWLedSetShunt(u8 channel1, u8 channel2, u8 channel3, u8 channel4);
#endif

#ifdef __BREATHLIGHT_DRV__
/** WrapperBreathLightToggle
* @brief        Wrapper for breathlight to access hal toggle.
* @param[in]    nLevel: breathlight level
* @retval       DrvBacklightErrCode_e error code
*
*/
DrvBacklightErrCode_e WrapperBreathLightToggle(u16 nLevel);
#endif

#endif 
