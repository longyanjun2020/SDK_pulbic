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
* @file    srv_resmgr_mmlutility_api.h
* @version
* @brief
*
*/

#ifndef __SRV_RESMGR_MMLUTILITY_API_H__
#define __SRV_RESMGR_MMLUTILITY_API_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

/*=============================================================*/
// Include files
/*=============================================================*/
#include "srv_resmgr_mml_forward.h"
#include "vm_types.ht"
#include "srv_resmgr_mmlcommon_types.h"
#include "srv_resmgr_mmlutility_types.h"

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
MmlUtilityResult_e MmlRingOpen
(
    MmlRingOpen_t     tOpen,
    u32               *pHandle
);

MmlUtilityResult_e MmlRingClose
(
    u32     nHandle
);

MmlUtilityResult_e MmlRingWriteSpaceSizeGet
(
    u32     nHandle,
    u32     *pWriteSpaceSize
);

MmlUtilityResult_e MmlRingReadDataSizeGet
(
    u32     nHandle,
    u32     *pReadDataSize
);

MmlUtilityResult_e MmlRingWriteInfoGet
(
    u32     nHandle,
    u32     *pWritePoint,
    u32     *pWriteSpaceAvailSize
);

MmlUtilityResult_e MmlRingReadInfoGet
(
    u32     nHandle,
    u32     *pReadPoint,
    u32     *pReadDataAvailSize
);

MmlUtilityResult_e MmlRingWriteAdvance
(
    u32     nHandle,
    u32     nWriteSize
);

MmlUtilityResult_e MmlRingReadAdvance
(
    u32     nHandle,
    u32     nReadSize
);

MmlUtilityResult_e MmlRingReset
(
    u32     nHandle
);

MmlUtilityResult_e MmlRingCallbackAttach
(
    u32                         nHandle,
    MmlRingOperatingMode_e      eOperatingMode,
    MmlRingCallback_t           tCallback
);

MmlUtilityResult_e MmlRingPrint
(
    u32     nHandle
);

MmlUtilityResult_e MmlRingWatermarkNotifyDisable
(
    u32                        nHandle,
    MmlRingOperatingMode_e     eOperatingMode
);

MmlUtilityResult_e MmlRingWatermarkNotifyEnable
(
    u32                        nHandle,
    MmlRingOperatingMode_e     eOperatingMode
);

MmlUtilityResult_e MmlRingMessageSend
(
    u32                 nContactIDSource,
    u32                 nContactIDDestination,
    MmlRingMessage_t    tMessage
);

MmlUtilityResult_e MmlRingDataEndFlagSet
(
    u32     nHandle,
    bool    bDataEnd
);

MmlUtilityResult_e MmlRingDataEndFlagGet
(
    u32     nHandle,
    bool    *pDataEnd
);

MmlUtilityResult_e MmlRingLock
(
    u32     nHandle
);

MmlUtilityResult_e MmlRingUnlock
(
    u32     nHandle
);

u16 MmlIsDowngraded8532B2(void);
u16 MmlIsDowngraded8556R2(void);
u16 MmlIsDowngraded8556M2(void);
#ifdef __cplusplus
}
#endif

#endif //__SRV_RESMGR_MMLUTILITY_API_H__
