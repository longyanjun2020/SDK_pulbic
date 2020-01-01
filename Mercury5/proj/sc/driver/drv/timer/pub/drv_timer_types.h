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
* @file    drv_timer_types.h
* @version
* @brief   Timer/WDT driver header file.
*
*/

#ifndef __DRV_TIMER_TYPES_H__
#define __DRV_TIMER_TYPES_H__
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
opaque_enum(DrvTimerErrorCode_e_)
{
    DRV_TIMER_SUCCESS               = (s32)(0),  ///< Process is done, nothing wrong
    DRV_TIMER_WDT_OUT_OF_RANGE      = (s32)(-1), ///< Configure WD timer parameter out of range
};

#ifdef __CHIPDRV_MM_TIMER___
opaque_enum(DrvMMTimerId_e_)
{
    DRV_MM_TIMER0,
    DRV_MM_TIMER1
};
#endif //__CHIPDRV_MM_TIMER___
#include "drv_timer_forward.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

#endif /* __DRV_TIMER_TYPES_H__ */
