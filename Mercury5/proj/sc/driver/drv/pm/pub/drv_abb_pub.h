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
* @file    drv_abb.h
* @version
* @brief   DRV header file of ABB task
*
*/
#ifndef __DRV_ABB_H__
#define __DRV_ABB_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "msgofs.hc"
#include "vm_types.ht"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/**
 *  @brief The structure defines touch panel coordination.
 */


typedef enum
{
    DRV_ABB_SERVICE_HEADSET = 0,
    DRV_ABB_SERVICE_HOOKKEY,
    DRV_ABB_SERVICE_BATT_CHG,
    DRV_ABB_SERVICE_MAX
}DrvServiceType_e;

typedef enum
{
    DRV_ABB_OK = 0,
    DRV_ABB_FAIL,
    DRV_ABB_INVALID_PARAM
}DrvAbbRetCode_e;

typedef enum {
    DRV_ABB_HEADSET_PLUGGED = 0,       ///< Sent when the headset is plugged
    DRV_ABB_HEADSET_UNPLUGGED,         ///< Sent when the headset is unplugged
    DRV_ABB_HOOKKEY_PRESSED,           ///< Sent when the headset button is pressed
    DRV_ABB_HOOKKEY_RELEASED,          ///< Sent when the headset button is released
    DRV_ABB_BAT_CHARG_EVENT,           ///< Sent when the charger event (plug or unplug) is detected
    DRV_ABB_BAT_LOW,                   ///< Sent when the battery low event is detected
    DRV_ABB_CHARG_OVER_VOLTAGE,        ///< Sent when the charger over voltage event is detected
    DRV_ABB_MSG_LAST = DRV_ABB_CHARG_OVER_VOLTAGE
} DrvAbbMsgCode_e;

typedef enum
{
    DRV_ABB_SERVICE_NOTIFY_MAIL_BOX= 0,
    DRV_ABB_SERVICE_NOTIFY_CALL_BACK,
    DRV_ABB_SERVICE_NOTIFY_NONE
}DrvServiceNotify_e;

typedef void (*PfnDrvAbbServiceCBFunc)(DrvAbbMsgCode_e);

typedef union
{
    u32 nMailBox;
    PfnDrvAbbServiceCBFunc pfnDrvAbbServiceCB;
}DrvServiceNotifyParam_u;

typedef struct
{
    DrvServiceNotify_e      eServiceNotify;
    DrvServiceNotifyParam_u uServiceNotifyParam;
}DrvAbbServiceParam_t;

/**
 * @brief ABB Management Message Types
 *
 */
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
typedef enum
{
#include "drv_abb_message_define__.hi"
} AbbMsgTypes_t;


/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

/** DrvAbbServiceSubscribe
* @brief        API for MDL to subscribe one ABB service
*
* @param[in]    DrvAbbServiceParam_t: structure of ABB service parameters
* @retval       DrvAbbRetCode_e
*
*/
DrvAbbRetCode_e DrvAbbServiceSubscribe(DrvServiceType_e eServiceType, DrvAbbServiceParam_t *ptAbbServiceParam);


/** DrvAbbServiceCallBack
* @brief        CB function invoked in ABB DSR
*
* @param[in]    DrvAbbMsgCode_e: enum of ABB event type
* @retval       None
*
*/
void DrvAbbServiceCallBack(DrvAbbMsgCode_e tEvent);

#endif //__DRV_ABB_H__

