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
* @file    srv_resmgr_mml_api.h
* @version
* @brief
*
*/

#ifndef __SRV_RESMGR_MML_API_H__
#define __SRV_RESMGR_MML_API_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

#include "vm_types.ht"
#include "srv_resmgr_mml_forward.h"

/*
 Interface header don't need to know
 1. Definition of SrvResMgrMmlModule_h, which is defined in srv_ResMgr_MmlDependency.c
    to separate the implementation from interface so that clients won't be affected by
    any change in implementation.
 2. Definitions of data types used here, which are defined in srv_resmgr_mml_types.h
    to minimize the dependency introduced due to #include "srv_resmgr_mml_api.h".

 Files that include this header to use these interfaces also need to include the
 srv_resmgr_mml_types.h, if necessary.
 */

/* Definitions */

typedef MmlErrCode_e (*PfnSrvResMgrMmlCallbackRegister)
(
    SrvResMgrMmlModule_h            hModule,
    MmlCallbackId_e                 eCallbackID,
    void                            *pfnCallback
);

typedef MmlErrCode_e (*PfnSrvResMgrMmlFunctionNoInputParameter)
(
    SrvResMgrMmlModule_h            hModule
);

typedef MmlErrCode_e (*PfnSrvResMgrMmlCommandCallbackRegister)
(
    SrvResMgrMmlModule_h            hModule,
    u32                             nCommandId,
    void                            *pfnCommandCallback,
    u32                             nUserData
);

typedef MmlErrCode_e (*PfnSrvResMgrMmlCommandCallbackUnregister)
(
    SrvResMgrMmlModule_h            hModule,
    u32                             nCommandId,
    void                            *pfnCommandCallback,
    u32                             nUserData
);

typedef MmlErrCode_e (*PfnSrvResMgrMmlCommandResponseSend)
(
    SrvResMgrMmlModule_h            hModule,
	u32                             nCommandId,
    u32                             nErrCode,
    void                            *pResponsePayload
);

typedef MmlErrCode_e (*PfnSrvResMgrMmlNotifyCallbackRegister)
(
    SrvResMgrMmlModule_h            hModule,
    u32                             nEvent,
    u16                             nSenderID,
    u32                             nUserValue,
    void                            *pfnNotifyCallback
);

typedef MmlErrCode_e (*PfnSrvResMgrMmlApplicationData)
(
    SrvResMgrMmlModule_h      hModule,
    MmlApplicationDataId_e    eDataID,
    void                      *pData
);

typedef MmlErrCode_e (*PfnSrvResMgrMmlUseCaseCallbackInvoke)
(
    SrvResMgrMmlModule_h    hModule,
    u32                     nUseCaseID,
    void                    *pUseCaseParam,
    u32                     nUseCaseParamSize
);

typedef MmlErrCode_e (*PfnSrvResMgrMmlNotifyCallbackAttach)
(
    SrvResMgrMmlModule_h      hModule,
    u32                       nEvent,
    u16                       nSenderID,
    u32                       nUserValue,
    void                      *pfnNotifyCallback,
    MmlNotifyCallback_t       **ppNCallback
);

typedef MmlErrCode_e (*PfnSrvResMgrMmlNotifyCallbackDetach)
(
    SrvResMgrMmlModule_h      hModule,
    u32                       nEvent,
    u16                       nSenderID,
    u32                       nUserValue,
    void                      *pfnNotifyCallback
);

typedef u32 (*PfnSrvResMgrMmlAdaptiveTimerIntervalGet)
(
    SrvResMgrMmlModule_h    hModule,
    u32     nInterval,
    u32     nDelta,
    u32     nMaximum
);

typedef MmlErrCode_e (*PfnSrvResMgrMmlLastErrorCodeGet)
(
    SrvResMgrMmlModule_h    hModule,
    MmlUseCaseGroupId_e     eGroupID,
    u32                     *pErrCode
);

typedef MmlErrCode_e (*PfnSrvResMgrMmlUseCaseCallbackUnregister)
(
    SrvResMgrMmlModule_h    hModule,
    u32                     nUseCaseID,
    void                    *pfnUseCaseCallback,
    u32                     nUserData
);

typedef MmlErrCode_e (*PfnSrvResMgrMmlNotifyCallbackUnregister)
(
    SrvResMgrMmlModule_h            hModule,
    u32                             nEvent,
    u16                             nSenderID,
    u32                             nUserValue,
    void                            *pfnNotifyCallback
);

typedef MmlErrCode_e (*PfnSrvResMgrMmlNotifyEventSend)
(
    SrvResMgrMmlModule_h            hModule,
    u32                             nEvent,
    void                            *pNotifyPayload
);

typedef MmlErrCode_e (*PfnSrvResMgrMmlPlatformCapabilityGet)
(
    SrvResMgrMmlModule_h            hModule,
    MmlPlatformCapability_t         *pPlatformCapability
);

typedef MmlUtilityResult_e (*PfnSrvResMgrMmlFileFilenameGet)
(
    SrvResMgrMmlModule_h            hModule,
    MmlFileGetFileNameType_e        eGetFileType,
    MmlFileNameInfo_t               *pFileNameType,
    MmlFilenameFormat_e             eFilenameFormat,
    u16                             *dest,
    u32                             nBytes
);

typedef MmlErrCode_e (*PfnSrvResMgrMmlMultimediaCapabilityGet)
(
    SrvResMgrMmlModule_h            hModule,
    MmlMultimediaCapability_t       *pCapability
);

opaque_enum(SrvResMgrMmlDependency_e_)
{
    SRV_RESMGR_MML_DEPENDENCY_DEFAULT = 0,
    SRV_RESMGR_MML_DEPENDENCY_NUM,
};


/* Create/Destroy module instance */
MmlErrCode_e SrvResMgrMmlModuleCreate
(
    SrvResMgrMmlModule_h            *pModule,
    SrvResMgrMmlDependency_e        eDependency
);

MmlErrCode_e SrvResMgrMmlModuleDestroy
(
    SrvResMgrMmlModule_h            hModule
);

/* Interfaces */
MmlErrCode_e SrvResMgrMmlCommandCallbackRegister
(
    SrvResMgrMmlModule_h            hModule,
    u32                             nCommandId,
    void                            *pfnCommandCallback,
    u32                             nUserData
);

MmlErrCode_e SrvResMgrMmlCommandCallbackRegisterEx
(
    u32                             nCommandId,
    void                            *pfnCommandCallback,
    u32                             nUserData
);

MmlErrCode_e SrvResMgrMmlCommandCallbackUnregister
(
    SrvResMgrMmlModule_h            hModule,
    u32                             nCommandId,
    void                            *pfnCommandCallback,
    u32                             nUserData
);

MmlErrCode_e SrvResMgrMmlUseCaseCallbackUnregisterEx
(
    u32                     nUseCaseID,
    void                    *pfnUseCaseCallback,
    u32                     nUserData
);

MmlErrCode_e SrvResMgrMmlUseCaseCallbackUnregister
(
    SrvResMgrMmlModule_h    hModule,
    u32                     nUseCaseID,
    void                    *pfnUseCaseCallback,
    u32                     nUserData
);

MmlErrCode_e SrvResMgrMmlCommandResponseSend
(
    SrvResMgrMmlModule_h            hModule,
	u32                             nCommandId,
    u32                             nErrCode,
    void                            *pResponsePayload
);

MmlErrCode_e SrvResMgrMmlCommandResponseSendEx
(
	u32                             nCommandId,
    u32                             nErrCode,
    void                            *pResponsePayload
);

MmlErrCode_e SrvResMgrMmlNotifyCallbackRegister
(
    SrvResMgrMmlModule_h            hModule,
    u32                             nEvent,
    u16                             nSenderID,
    u32                             nUserValue,
    void                            *pfnNotifyCallback
);

MmlErrCode_e SrvResMgrMmlNotifyCallbackRegisterEx
(
    u32                             nEvent,
    u16                             nSenderID,
    u32                             nUserValue,
    void                            *pfnNotifyCallback
);

MmlErrCode_e SrvResMgrMmlNotifyCallbackUnregister
(
    SrvResMgrMmlModule_h            hModule,
    u32                             nEvent,
    u16                             nSenderID,
    u32                             nUserValue,
    void                            *pfnNotifyCallback
);

MmlErrCode_e SrvResMgrMmlNotifyCallbackUnregisterEx
(
    u32                             nEvent,
    u16                             nSenderID,
    u32                             nUserValue,
    void                            *pfnNotifyCallback
);

MmlErrCode_e SrvResMgrMmlNotifyEventSend
(
    SrvResMgrMmlModule_h            hModule,
    u32                             nEvent,
    void                            *pNotifyPayload
);

MmlErrCode_e SrvResMgrMmlNotifyEventSendEx
(
    u32                             nEvent,
    void                            *pNotifyPayload
);

MmlErrCode_e SrvResMgrMmlPlatformCapabilityGet
(
    SrvResMgrMmlModule_h            hModule,
    MmlPlatformCapability_t         *pPlatformCapability
);

MmlErrCode_e SrvResMgrMmlPlatformCapabilityGetEx
(
    MmlPlatformCapability_t         *pPlatformCapability
);

MmlUtilityResult_e SrvResMgrMmlFileFilenameGet
(
    SrvResMgrMmlModule_h            hModule,
    MmlFileGetFileNameType_e        eGetFileType,
    MmlFileNameInfo_t               *pFileNameType,
    MmlFilenameFormat_e             eFilenameFormat,
    u16                             *dest,
    u32                             nBytes
);

MmlUtilityResult_e SrvResMgrMmlFileFilenameGetEx
(
    MmlFileGetFileNameType_e        eGetFileType,
    MmlFileNameInfo_t               *pFileNameType,
    MmlFilenameFormat_e             eFilenameFormat,
    u16                             *dest,
    u32                             nBytes
);

MmlErrCode_e SrvResMgrMmlBacktraceDump
(
    SrvResMgrMmlModule_h            hModule
);

MmlErrCode_e SrvResMgrMmlBacktraceDumpEx(void);

MmlErrCode_e SrvResMgrMmlApplicationDataSet
(
    SrvResMgrMmlModule_h      hModule,
    MmlApplicationDataId_e    eDataID,
    void                      *pData
);


MmlErrCode_e SrvResMgrMmlApplicationDataSetEx
(
    MmlApplicationDataId_e    eDataID,
    void                      *pData
);

MmlErrCode_e SrvResMgrMmlApplicationDataGet
(
    SrvResMgrMmlModule_h      hModule,
    MmlApplicationDataId_e    eDataID,
    void                      *pData
);


MmlErrCode_e SrvResMgrMmlApplicationDataGetEx
(
    MmlApplicationDataId_e    eDataID,
    void                      *pData
);

MmlErrCode_e SrvResMgrMmlNotifyCallbackAttach
(
    SrvResMgrMmlModule_h      hModule,
    u32                       nEvent,
    u16                       nSenderID,
    u32                       nUserValue,
    void                      *pfnNotifyCallback,
    MmlNotifyCallback_t       **ppNCallback
);

MmlErrCode_e SrvResMgrMmlNotifyCallbackAttachEx
(
    u32                       nEvent,
    u16                       nSenderID,
    u32                       nUserValue,
    void                      *pfnNotifyCallback,
    MmlNotifyCallback_t       **ppNCallback
);

MmlErrCode_e SrvResMgrMmlNotifyCallbackDetach
(
    SrvResMgrMmlModule_h    hModule,
    u32                     nEvent,
    u16                     nSenderID,
    u32                     nUserValue,
    void                    *pfnNotifyCallback
);

MmlErrCode_e SrvResMgrMmlNotifyCallbackDetachEx
(
    u32                      nEvent,
    u16                      nSenderID,
    u32                      nUserValue,
    void                     *pfnNotifyCallback
);

u32 SrvResMgrMmlAdaptiveTimerIntervalGetEX
(
    u32     nInterval,
    u32     nDelta,
    u32     nMaximum
);

u32 SrvResMgrMmlAdaptiveTimerIntervalGet
(
    SrvResMgrMmlModule_h    hModule,
    u32     nInterval,
    u32     nDelta,
    u32     nMaximum
);

MmlErrCode_e SrvResMgrMmlLastErrorCodeGetEx
(
    MmlUseCaseGroupId_e     eGroupID,
    u32                     *pErrCode
);

MmlErrCode_e SrvResMgrMmlLastErrorCodeGet
(
    SrvResMgrMmlModule_h    hModule,
    MmlUseCaseGroupId_e     eGroupID,
    u32                     *pErrCode
);

MmlErrCode_e SrvResMgrMmlMultimediaCapabilityGet
(
    SrvResMgrMmlModule_h            hModule,
    MmlMultimediaCapability_t       *pCapability
);

MmlErrCode_e SrvResMgrMmlMultimediaCapabilityGetEx
(
    MmlMultimediaCapability_t       *pCapability
);

MmlErrCode_e SrvResMgrMmlPlatfromCapabilitySet
(
    SrvResMgrMmlModule_h       hModule
);

MmlErrCode_e SrvResMgrMmlPlatformCapabilitySetEx(void);

MmlErrCode_e SrvResMgrMmlUseCaseCallbackInvoke
(
    SrvResMgrMmlModule_h      hModule,
    u32     nUseCaseID,
    void    *pUseCaseParam,
    u32     nUseCaseParamSize
);

MmlErrCode_e SrvResMgrMmlUseCaseCallbackInvokeEx
(
    u32     nUseCaseID,
    void    *pUseCaseParam,
    u32     nUseCaseParamSize
);

MmlErrCode_e SrvResMgrMmlCallbackRegisterEx
(
    MmlCallbackId_e         eCallbackID,
    void                    *pfnCallback
);

MmlErrCode_e SrvResMgrMmlCallbackRegister
(
    SrvResMgrMmlModule_h    hModule,
    MmlCallbackId_e         eCallbackID,
    void                    *pfnCallback
);


#ifdef __cplusplus
}
#endif

#endif //__SRV_RESMGR_MML_API_H__

