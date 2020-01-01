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
* @file    srv_ResMgr_MmlManager.h
* @version
* @brief
*
*/

#ifndef __SRV_RESMGR_MMLMANAGER_H__
#define __SRV_RESMGR_MMLMANAGER_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

/*=============================================================*/
// Include files
/*=============================================================*/
#include "srv_resmgr_mml_types.h"
#include "vm_msgof.hc"
/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define MML_GET_AUDIO_UCID(pUseCaseParam)      ((MmlUseCaseAudioId_e)(*(u32*)(pUseCaseParam)))
#define MML_GET_VIDEO_UCID(pUseCaseParam)      ((MmlUseCaseVideoId_e)(*(u32*)(pUseCaseParam)))
#define MML_GET_IMAGE_UCID(pUseCaseParam)      ((MmlUseCaseImageId_e)(*(u32*)(pUseCaseParam)))
#define MML_GET_GAME_UCID(pUseCaseParam)       ((MmlUseCaseGameId_e)(*(u32*)(pUseCaseParam)))
#define MML_GET_USB_UCID(pUseCaseParam)        ((MmlUseCaseUsbId_e)(*(u32*)(pUseCaseParam)))
#define MML_GET_TV_UCID(pUseCaseParam)         ((MmlUseCaseTvId_e)(*(u32*)(pUseCaseParam)))
#define MML_GET_CAMERA_UCID(pUseCaseParam)     ((MmlUseCaseCameraId_e)(*(u32*)(pUseCaseParam)))
#define MML_GET_RADIO_UCID(pUseCaseParam)      ((MmlUseCaseRadioId_e)(*(u32*)(pUseCaseParam)))
#define MML_GET_GPS_UCID(pUseCaseParam)        ((MmlUseCaseGpsId_e)(*(u32*)(pUseCaseParam)))
#define MML_GET_WLAN_UCID(pUseCaseParam)       ((MmlUseCaseWlanId_e)(*(u32*)(pUseCaseParam)))
#define MML_GET_RFID_UCID(pUseCaseParam)       ((MmlUseCaseRfidId_e)(*(u32*)(pUseCaseParam)))

#define MML_POWERMANAGEMENT_TIMER_INTERVAL     (5000) /* in milliseconds */
#define MML_POWERMANAGEMENT_TIMER_DELTA        (1000) /* in milliseconds */
/** @ingroup    MMLayerManager
    @brief      Message ID bases
*/
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
typedef enum{
#include "srv_ResMgr_message_define__.hi"
}MmlMessageId_e;

/*=============================================================*/
// Data type definition
/*=============================================================*/
/** @ingroup    MMLayerManager
    @brief      Use case callback prototype
    @param      pUseCaseParam         Pointer to the use case parameter structure
    @param      nUseCaseParamSize     Size in bytes of the use case parameter structure
    @param      nUserData             Interface self-reference
*/
typedef void (*PfnMmlUseCaseCallback)(void *pUseCaseParam, u32 nUseCaseParamSize, u32 nUserData);

/** @ingroup    MMLayerManager
    @brief      Multimedia resource
*/
typedef struct
{
    /*
     Naming: <Category><ResourceName><Status>
     */
    u16      bHardwareScalarOccupied;
} MmlMultimediaResource_t;

/** @ingroup    MMLayerManager
    @brief      Application data IDs
*/

opaque_enum(MmlApplicationDataId_e_)
{
    MML_UCPARAM_CAMERA_START_PREVIEW = 0,
    MML_RESPONSE_CAMERA_DETECT_SENSOR,
    MML_UCPARAM_RADIO_SET_RADIO_CONFIGURATION,
    MML_UCPARAM_CAMERA_SET_DIGITAL_ZOOM,
    MML_UCPARAM_CAMERA_SET_EXPOSURE,
    MML_UCPARAM_CAMERA_SET_WHITE_BALANCE,
    MML_UCPARAM_CAMERA_SET_FOCUS,
    MML_UCPARAM_CAMERA_SET_EV,
    MML_UCPARAM_CAMERA_SET_ANTI_FLICKER,
    MML_UCPARAM_CAMERA_SET_IMAGE_EFFECT,
    MML_UCPARAM_CAMERA_SET_SCENE_MODE,
	MML_UCPARAM_IMAGE_ENCODE_IMAGE_PATH,
    MML_UCPARAM_IMAGE_ENCODE_IMAGE_BUFFER,
    MML_UCPARAM_IMAGE_ENCODE_IMAGE_OUTPUTTYPE,
    MML_UCPARAM_VIDEO_START_RECORDING_PATH,
    MML_APDATID_MULTIMEDIA_CAPABILITY,
    MML_APDATID_MULTIMEDIA_RESOURCE,
} ;


/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
/** @ingroup      MMLayerManager
*   @brief        Register a use case callback for the specified use case
*
*   @param[in]    nUseCaseID     Use case ID
*   @param[in]    pfnUCCallback  Address of the use case callback
*   @param[in]    nUserData      Interface self-reference
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_PARAMETER_INVALID         Failed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @retval       MML_ERROR_PRECONDITIONS_VIOLATED    Failed
*   @retval       MML_ERROR_MEMORY_FAILURE            Failed
*/
MmlErrCode_e MmlUseCaseCallbackRegister
(
    u32                     nUseCaseID,
    PfnMmlUseCaseCallback   pfnUCCallback,
    u32                     nUserData
);

/** @ingroup      MMLayerManager
*   @brief        Unregister the specified use case callback
*
*   @param[in]    nUseCaseID       Use case ID
*   @param[in]    pfnUCCallback    Address of the use case callback
*   @param[in]    nUserData        Interface self-reference
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_PARAMETER_INVALID         Failed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @retval       MML_ERROR_PRECONDITIONS_VIOLATED    Failed
*/
MmlErrCode_e MmlUseCaseCallbackUnregister
(
    u32                     nUseCaseID,
    PfnMmlUseCaseCallback   pfnUCCallback,
    u32                     nUserData
);

/** @ingroup      MMLayerManager
*   @brief        Send response to the sender's response callback
*
*   @param[in]    nUseCaseID          Use case ID
*   @param[in]    nErrCode            Returned result (error code)
*   @param[in]    pResponsePayload    Pointer to the response payload
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @retval       MML_ERROR_PRECONDITIONS_VIOLATED    Failed
*/
MmlErrCode_e MmlResponseCallbackInvoke
(
	u32     nUseCaseID,
    u32     nErrCode,
    void    *pResponsePayload
);

/** @ingroup      MMLayerManager
*   @brief        Register a notification callback for the specified event
*
*   @param[in]    nEvent               Event ID
*   @param[in]    nSenderID            Sender's mailbox ID
*   @param[in]    nUserValue           Interface self-reference
*   @param[in]    pfnNotifyCallback    Address of the notification callback
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_PARAMETER_INVALID         Failed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @retval       MML_ERROR_PRECONDITIONS_VIOLATED    Failed
*   @retval       MML_ERROR_MEMORY_FAILURE            Failed
*/
MmlErrCode_e MmlNotifyCallbackRegister
(
    u32      nEvent,
    u16      nSenderID,
    u32      nUserValue,
    void     *pfnNotifyCallback
);

/** @ingroup      MMLayerManager
*   @brief        Unregister the specified notification callback
*
*   @param[in]    nEvent               Event ID
*   @param[in]    nSenderID            Sender's mailbox ID
*   @param[in]    nUserValue           Interface self-reference
*   @param[in]    pfnNotifyCallback    Address of the notification callback
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_PARAMETER_INVALID         Failed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @retval       MML_ERROR_PRECONDITIONS_VIOLATED    Failed
*   @retval       MML_ERROR_MEMORY_FAILURE            Failed
*/
MmlErrCode_e MmlNotifyCallbackUnregister
(
    u32      nEvent,
    u16      nSenderID,
    u32      nUserValue,
    void     *pfnNotifyCallback
);

/** @ingroup      MMLayerManager
*   @brief        Send notification to all of the associated notification callbacks
*
*   @param[in]    nEvent               Event ID
*   @param[in]    pNotifyPayload       Pointer to the noitfication payload
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @retval       MML_ERROR_PRECONDITIONS_VIOLATED    Failed
*/
MmlErrCode_e MmlNotifyCallbackInvoke
(
    u32     nEvent,
    void    *pNotifyPayload
);

/** @ingroup      MMLayerManager
*   @brief        Get a copy of the application data from the multimedia manager
*
*   @param[in]    eDataID     Application data ID
*   @param[in]    pData       Pointer to the buffer to store the application data
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @retval       MML_ERROR_PRECONDITIONS_VIOLATED    Failed
*/
MmlErrCode_e MmlApplicationDataGet
(
    MmlApplicationDataId_e    eDataID,
    void                      *pData
);

/** @ingroup      MMLayerManager
*   @brief        Change the application data stored inside the multimedia manager
*
*   @param[in]    eDataID     Application data ID
*   @param[in]    pData       Pointer to the buffer specifying the application data
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @retval       MML_ERROR_PRECONDITIONS_VIOLATED    Failed
*/
MmlErrCode_e MmlApplicationDataSet
(
    MmlApplicationDataId_e    eDataID,
    void                      *pData
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Dump the multimedia manager backtrace
*
*   @retval       MML_ERROR_SUCCESS    Succeed
*   @endcond
*/
MmlErrCode_e MmlBacktraceDump(void);

#ifdef __cplusplus
}
#endif

#endif //__SRV_RESMGR_MMLMANAGER_H__

