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
* @file    srv_drv_ofn_types.h
* @version
* @brief   This module defines the Unified Driver Interface (UDI) of OFN
*
*/

#ifndef __SRV_DRV_OFN_TYPES_H__
#define __SRV_DRV_OFN_TYPES_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "osdefs.hc"
#include "srv_drv_ofn_forward.h"
#include "vm_msgof.hc"

// Enable OFN Finger Leave mechanism
//#define __DRV_OFN_FINGER_LEAVE__

/*=============================================================*/
// Extern definition
/*=============================================================*/
#define DEV_OFN_MBX VM_MBX_CUS1  /* DEV_TASK is CUS1 */


#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum{
#include "srv_drv_ofn_message_define__.hi"
};

#define OFN_POLLING_TIMER_INTERVAL  RTK_MS_TO_TICK(30) // 30ms

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define OFN_DEBUG_LEVEL    (_CUS10 | LEVEL_10)

/*=============================================================*/
// Data type definition
/*=============================================================*/

/**
 *  @brief The enumeration defines error codes of GPD drivers .
 */
opaque_enum(DrvOfnErrCode_e_)
{
    DRV_OFN_OK,                /**< Function complete successfully */
    DRV_OFN_FAIL              /**< Function common fail */
};

/**
 * @brief The structure defines the ccelerometer information of OFN.
 */
struct DrvOfnData_t_
{
    s8 nAxisX;                    /**< X-axis */
    s8 nAxisY;                    /**< Y-axis */
    #ifdef __DRV_OFN_FINGER_LEAVE__
    bool bIsFingerLeave;          /**< To check Finger is touched or left. */
    #endif
};

opaque_enum(MS_OFN_VKeyCode_)
{
    OFN_KEY_OFN_LEFT,
    OFN_KEY_OFN_RIGHT,
    OFN_KEY_OFN_UP,
    OFN_KEY_OFN_DOWN,
    OFN_KEY_DUMMY   = 0xFF
};

/*=============================================================*/
// Variable definition
/*=============================================================*/


#endif // __SRV_DRV_OFN_TYPES_H__
