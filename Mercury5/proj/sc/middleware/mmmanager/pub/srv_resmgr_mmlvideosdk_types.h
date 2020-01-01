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
* @file    srv_resmgr_mmlvideosdk_types.h
* @version
* @brief
*
*/

#ifndef __SRV_RESMGR_MMLVIDEOSDK_TYPES_H__
#define __SRV_RESMGR_MMLVIDEOSDK_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup MMLayerVideoSdk Video SDK
    Video Playback SDK for 3rd party
    @{
*/
    /** @defgroup MMLayerVideoSdkColorConvert Color convert
        Color Convert
        @{
    */
    /** @} */

/** @} */

/*=============================================================*/
// Include files
/*=============================================================*/
#include "srv_resmgr_mml_forward.h"
#include "vm_types.ht"
#include "srv_resmgr_mmlcommon_types.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/** @ingroup    MMLayerVideoSdk
    @brief      Use case IDs
*/
opaque_enum(MmlUseCaseVideoSdkId_e_)
{
    /* Video SDK Init */
    MML_UCID_VIDEOSDK_INIT_BASE = MML_GET_UCID_INIT_BASE(MML_UCGID_VIDEOSDK),
    MML_UCID_VIDEOSDK_REG_NOTIFY_CALLBACK = MML_UCID_VIDEOSDK_INIT_BASE,           ///< 000D0000 = Reg notify callback
    MML_UCID_VIDEOSDK_UNREG_NOTIFY_CALLBACK,                                       ///< 000D0001 = Unreg notify callback
    MML_UCID_VIDEOSDK_INIT_CATEGORY,

    /* Video SDK Get */
    MML_UCID_VIDEOSDK_GET_BASE = MML_GET_UCID_GET_BASE(MML_UCGID_VIDEOSDK),
    MML_UCID_VIDEOSDK_GET_CATEGORY = MML_UCID_VIDEOSDK_GET_BASE,

    /* Video SDK Set */
    MML_UCID_VIDEOSDK_SET_BASE = MML_GET_UCID_SET_BASE(MML_UCGID_VIDEOSDK),
    MML_UCID_VIDEOSDK_SET_CATEGORY = MML_UCID_VIDEOSDK_SET_BASE,

    /* Video SDK Execute */
    MML_UCID_VIDEOSDK_EXECUTE_BASE = MML_GET_UCID_EXE_BASE(MML_UCGID_VIDEOSDK),
    MML_UCID_VIDEOSDK_OPEN_PLAYER = MML_UCID_VIDEOSDK_EXECUTE_BASE,                ///< 000D0300 = Open player
    MML_UCID_VIDEOSDK_CLOSE_PLAYER,                                                ///< 000D0301 = Close player
    MML_UCID_VIDEOSDK_OPEN_COLOR_CONVERTER,                                        ///< 000D0302 = Open color converter
    MML_UCID_VIDEOSDK_CLOSE_COLOR_CONVERTER,                                       ///< 000D0303 = Close color converter
    MML_UCID_VIDEOSDK_CONVERT_COLOR,                                               ///< 000D0304 = Convert color
    MML_UCID_VIDEOSDK_EXECUTE_CATEGORY,

    /* Force ID to be at least 32-bits */
    MML_UCID_VIDEOSDK_FORCE_U32 = 0x7FFFFFFF
};

/** @ingroup    MMLayerVideoSdk
    @brief      Response results
*/
typedef enum
{
    /* Common */
    VIDEOSDK_ERROR_SUCCESS = 0,
    VIDEOSDK_ERROR_FAIL,
    VIDEOSDK_ERROR_PARAMETER_INVALID,
    VIDEOSDK_ERROR_STATE_CHANGE,
    VIDEOSDK_ERROR_ACCEPT,
    VIDEOSDK_ERROR_IGNORE,
    VIDEOSDK_ERROR_REJECT,
    VIDEOSDK_ERROR_MEMORY_FAILURE,
    VIDEOSDK_ERROR_NUM
} MmlVideoSdkResult_e;

/** @ingroup    MMLayerVideoSdk
    @brief      States
*/
typedef enum
{
    /* Video Playback */
    VIDEOSDK_STATE_PLAYBACK_STOPPED = 0,
    VIDEOSDK_STATE_PLAYBACK_PLAYING,
    VIDEOSDK_STATE_DONTCARE,
    VIDEOSDK_STATE_NUM
} MmlVideoSdkState_e;

/** @ingroup    MMLayerVideoSdk
    @brief      Events
*/
typedef enum
{
    /* Common */
    VIDEOSDK_EVENT_STATE_CHANGE = MML_GET_UCGEVENT_BASE(MML_UCGID_VIDEOSDK),
    VIDEOSDK_EVENT_RUNTIME_ERROR,
    /* */
    VIDEOSDK_EVENT_DONTCARE,
    VIDEOSDK_EVENT_ALL,
    VIDEOSDK_EVENT_NUM
} MmlVideoSdkEvent_e;

/** @ingroup    MMLayerVideoSdk
    @brief      State change info
*/
typedef	struct
{
    MmlVideoSdkState_e             eState;                                          ///< The new state after the transition
    MmlVideoSdkEvent_e	           eCause;                                          ///< The cause of state change, if any

    /// union of MmlVideoSdkStateChange_t parameters
    /*
    union
    {
    } uParam;
    */
} MmlVideoSdkStateChange_t;

/** @ingroup    MMLayerVideoSdk
    @brief      Notification payload
*/
typedef struct
{
    MmlVideoSdkEvent_e	           eEvent;             ///< Specify the event you want to notify
    //u32                            nHandle;            ///< 32-bit playback handle

    /// union of MmlVideoSdkNotify_t parameters
    union
    {
        MmlVideoSdkStateChange_t   tStateChange;       ///< Used with VIDEOSDK_EVENT_STATE_CHANGE event
        MmlVideoSdkResult_e        eErrCode;           ///< Used with VIDEOSDK_EVENT_RUNTIME_ERROR event
	} uParam;
} MmlVideoSdkNotify_t;

/** @ingroup    MMLayerVideoSdk
    @brief      Notification callback prototype
    @param      nSenderID         Sender's mailbox ID
    @param      nUserValue        Interface self-reference
    @param      pVideoNotify      Pointer to the accompanying notification payload
*/
typedef void (*PfnMmlVideoSdkNotifyCallback)(u16 nSenderID, u32 nUserValue, MmlVideoSdkNotify_t *pVideoSdkNotify);

/** @ingroup    MMLayerVideoSdk
    @brief      Notification callback registration structure
*/
typedef struct
{
    u16                                nSenderID;           ///< Sender's mailbox ID
    u32                                nUserValue;          ///< Interface self-reference
    PfnMmlVideoSdkNotifyCallback       pfnNotifyCallback;   ///< Callback function your want to register
} MmlVideoSdkNotifyCallback_t;

/** @ingroup    MMLayerVideoSdk
    @brief      Response callback       prototype
    @param      nSenderID               Sender's mailbox ID
    @param      nUserValue              Interface self-reference
    @param      eErrCode                Returned result (error code)
    @param      pVideoSdkResponse       Pointer to the returned response payload
*/
struct MmlVideoSdkResponse_t_;
typedef void (*PfnMmlVideoSdkResponseCallback)(u16 nSenderID, u32 nUserValue, MmlVideoSdkResult_e eErrCode, struct MmlVideoSdkResponse_t_ *pVideoSdkResponse);

/** @ingroup    MMLayerVideoSdk
    @brief      Response callback registration structure
*/
typedef struct
{
    u16                             nSenderID;              ///< Sender's mailbox ID
    u32                             nUserValue;             ///< Interface self-reference
    PfnMmlVideoSdkResponseCallback  pfnResponseCallback;    ///< Callback function your want to register
} MmlVideoSdkResponseCallback_t;

/** @ingroup    MMLayerVideoSdk
    @brief      Register notification callback
*/
typedef struct
{
    MmlVideoSdkEvent_e              eEvent;             ///< Specify which event you want to handle
    MmlVideoSdkNotifyCallback_t     tNotifyCallback;    ///< Registration data specifying the callback function' address
} MmlVideoSdkRegNotifyCallback_t;

/** @ingroup    MMLayerVideoSdk
    @brief      Video config data
*/
struct MDLAvpVideoConfig_s;                                             /* Forward declaration */
typedef struct MDLAvpVideoConfig_s       MmlVideoSdkVideoConfig_t;      ///< Cast void pointer to MDLAvpVideoConfig_st

/** @ingroup    MMLayerVideoSdkColorConvert
    @brief      Open color converter
*/
typedef struct
{
    u32                               nHandle;                          ///< 32-bit player handle
    MmlVideoSdkVideoConfig_t          *pVideoConfigInput;               ///< pointer to video input config data block
    MmlVideoSdkVideoConfig_t          *pVideoConfigOutput;              ///< pointer to video output config data block
} MmlVideoSdkOpenColorConverter_t;

/** @ingroup    MMLayerVideoSdk
    @brief      Video frame config data
*/
struct MDLVideoFrame_s;                                                 /* Forward declaration */
typedef struct MDLVideoFrame_s        MmlVideoSdkVideoFrameConfig_t;    ///< Cast void pointer to MDLVideoFrame_st

/** @ingroup    MMLayerVideoSdk
    @brief      Convert color
*/
typedef struct
{
    u32                               nHandle;                          ///< 32-bit player handle
    MmlVideoSdkVideoFrameConfig_t     *pVideoFrameConfigInput;          ///< pointer to video input frame config data block
    MmlVideoSdkVideoFrameConfig_t     *pVideoFrameConfigOutput;         ///< pointer to video output frame config data block
} MmlVideoSdkConvertColor_t;

/** @ingroup    MMLayerVideoSdk
    @brief      Response payload
*/
typedef struct MmlVideoSdkResponse_t_
{
    MmlVideoSdkState_e          eState;                                 ///< Current state
    u32                         nHandle;                                ///< 32-bit playback handle
    /// union of MmlVideoResponse_t parameters
	union
	{
        MmlVideoSdkStateChange_t      tStateChange;                     ///< Used with 'VIDEOSDK_ERROR_STATE_CHANGE' result
    } uParam;
} MmlVideoSdkResponse_t;

/** @ingroup    MMLayerVideoSdk
    @brief      Video SDK use case parameters
*/
typedef struct
{
	u32                                    nUseCaseID;                   ///< Use case ID
	MmlVideoSdkResponseCallback_t          *pResponseCallback;           ///< Pointer to the response callback registration data
	MmlVideoSdkResponse_t                  *pResponse;                   ///< Pointer to the response payload

    /// union of MmlVideoSdkUCParam_t parameters
	union
	{
        u32                                 nHandle;                     ///< Used with 'Close color converter,Close player'
        MmlVideoSdkOpenColorConverter_t     tOpenColorConverter;         ///< Used with 'Open color converter'
        MmlVideoSdkConvertColor_t           tConvertColor;               ///< Used with 'Convert color'
	} uParam;

} MmlVideoSdkUCParam_t;
/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#ifdef __cplusplus
}
#endif

#endif //__SRV_RESMGR_MMLVIDEOSDK_TYPES_H__
