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


#ifndef __DRV_BACKLIGHT_FORWARD_H__
#define __DRV_BACKLIGHT_FORWARD_H__

/**
* @file    drv_backlight_forward.h
* @version
* @brief   Driver backlight header file
*
*/


/** \addtogroup Backlight
 *  @{
 * \file
 */


/**
 * @brief The enumeration defines error codes of backlight drivers .
 */
typedef enum
{
    DRV_BACKLIGHT_FAIL,                ///< Function common fail
    DRV_BACKLIGHT_OK                   ///< Function complete successfully
}DrvBacklightErrCode_e;

/** @}*/
#endif // __DRV_BACKLIGHT_FORWARD_H__

