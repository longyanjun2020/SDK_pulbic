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
* @file    MML_Usb.h
* @version
* @brief
*
*/

#ifndef __MML_USB_H__
#define __MML_USB_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

/** @defgroup MMLayerUsb USB
    Mass Storage, Virtual COM, Modem, PC-Cam, Picture Bridge
    @{
*/
    /** @defgroup MMLayerUsbMassStorage Mass Storage
        Mass Storage
        @{
    */
    /** @} */

    /** @defgroup MMLayerUsbVirtualCom Virtual COM
        Virtual COM
        @{
    */
    /** @} */

    /** @defgroup MMLayerUsbModem Modem
        Modem
        @{
    */
    /** @} */

    /** @defgroup MMLayerUsbPCCam PC-Cam
        PC-Cam
        @{
    */
    /** @} */

    /** @defgroup MMLayerUsbPicBridge Picture Bridge
        Picture Bridge
        @{
    */
    /** @} */

/** @} */

/*=============================================================*/
// Include files
/*=============================================================*/
#include "srv_resmgr_mml_forward.h"
#include "vm_types.ht"
#include "srv_resmgr_mmlusb_types.h" // Lib release stage1's workaround

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
MmlErrCode_e MmlUsbNotifyCallbackDispatch
(
    MmlMultimediaGroup_t            *pGroup,
    u32                             nEvent,
    void                            *pNotifyPayload
);

#ifdef __cplusplus
}
#endif

#endif //__MML_USB_H__
