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
* @file    drv_timer.h
* @version
* @brief   Timer/WDT driver header file.
*
*/

#ifndef __DRV_TIMER_FORWARD_H__
#define __DRV_TIMER_FORWARD_H__

#include "vm_types.ht"

/*=============================================================*/
// External definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/**
 * @brief   Error Code for timer procedures
 */
opaque_enum(DrvTimerErrorCode_e_);
typedef enum DrvTimerErrorCode_e_ DrvTimerErrorCode_e;

#ifdef __CHIPDRV_MM_TIMER___
opaque_enum(DrvMMTimerId_e_);
typedef enum DrvMMTimerId_e_ DrvMMTimerId_e;
#endif //__CHIPDRV_MM_TIMER___

#endif /* __DRV_TIMER_FORWARD_H__ */
