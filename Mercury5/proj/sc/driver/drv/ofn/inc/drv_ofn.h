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
* @file    drv_ofn.h
* @version
* @brief   This module defines the Unified Driver Interface (UDI) of OFN
*
*/

#ifndef ___PRIVATE_DRV_OFN_H__
#define ___PRIVATE_DRV_OFN_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "sys_rtk_ho.h"

#include "sys_rtk_vmoshi.h"
#include "vm_types.ht"
#include "vm_kbd.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef struct st_vkey_message_
{
    u8              keymode;
    u8              vkey;
} VKEYCODE, *PVKEYCODE;

typedef union{
    vm_osTimerMsgBody_t TimerMsgBody;
    VKEYCODE         vcode;
    //vm_kbdInd_t      scancode;
} Body_t;

/**
 * @brief The enumeration defines the operations of OFN.
 */
typedef enum
{
    DRV_OFN_OP_OFF = 0,        /**< Turn off OFN */
    DRV_OFN_OP_ON             /**< Turn on OFN */
} DrvOfnOp_e;

typedef struct
{
    u16 nAxisNum;         /**< Number of axis which OFN supported. */
    u16 nSensitiveLevel;  /**< OFN sensitive level. */
} DrvOfnCapability_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function declaration
/*=============================================================*/

/** DrvUnmaskOfnInterrupt
* @brief        Unmask OFN interrupt by keypad driver
*
* @retval       OFN_OK         Success.
* @retval       Other             Failed.
*
*/
DrvOfnErrCode_e DrvUnmaskOfnInterrupt(void);

/**
* @brief OFN initialization
*
* @param NONE
*
* @retval DRV_OFN_OK                   : Function request success
* @retval DRV_OFN_FAIL                 : Function request fail
*/
DrvOfnErrCode_e DrvOfnInit(void);

#if 0 /* not used */
/**
 * @brief OFN power on/off
 *
 * @param eOperation                        : [in] power on/off
 *
 * @retval DRV_OFN_OK                   : Function request success
 * @retval DRV_OFN_FAIL                 : Function request fail
 */
DrvOfnErrCode_e DrvOfnSwitch(DrvOfnOp_e eOperation);
#endif
DrvOfnErrCode_e DrvOfnGetCapability(DrvOfnCapability_t *ptCapability);

#endif

