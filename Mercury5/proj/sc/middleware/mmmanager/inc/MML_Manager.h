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
* @file    MML_Manager.h
* @version
* @brief
*
*/

#ifndef __MML_MANAGER_H__
#define __MML_MANAGER_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

/** @defgroup MMLayer Multimedia Management
    Multimedia Manager
    @{
*/
    /** @defgroup MMLayerManager Manager
        Multimedia Manager
        @{
    */
    /** @} */

    /** @defgroup MMLayerAudio Audio
        Audio Playback and Recording
        @{
    */
    /** @} */

    /** @defgroup MMLayerVideo Video
        Video Playback and Recording
        @{
    */
    /** @} */

    /** @defgroup MMLayerImage Image
        Image Decoding and Encoding (Capture)
        @{
    */
    /** @} */

    /** @defgroup MMLayerDisplay Display
        Image Rendering
        @{
    */
    /** @} */

    /** @defgroup MMLayerGame Game
        NES Game
        @{
    */
    /** @} */

    /** @defgroup MMLayerUsb USB
        Mass Storage, Virtual COM, Modem, PC-Cam, Picture Bridge
        @{
    */
    /** @} */

    /** @defgroup MMLayerTv TV
        Analog TV, Digital TV
        @{
    */
    /** @} */

    /** @defgroup MMLayerCamera Camera
        Preview On/Off, 3A, Digital Zoom, Image Effects, Scene Mode
        @{
    */
    /** @} */

    /** @defgroup MMLayerRadio Radio
        FM radio
        @{
    */
    /** @} */

/** @} */

/*=============================================================*/
// Include files
/*=============================================================*/
#include "sys_rtk_vmrtkho.h"
#include "sys_vm_dbg.ho"
#include "vm_stdio.ho"
#include "cus_os.hc"
#include "sys_MsWrapper_cus_os_msg.h"
#include "sys_MsWrapper_cus_os_sem.h"
#include "sys_MsWrapper_cus_os_util.h"
#include "sys_MsWrapper_cus_os_timer.h"
#include "cus_msg.hc"
#if defined(__SDK_SIMULATION__)
#include "assert.h"
#endif

#include "srv_resmgr_mml_forward.h"
#include "srv_ResMgr_MmlManager.h"
#include "MML_Common.h"
#include "MML_Audio.h"
#include "MML_Camera.h"
#include "MML_Display.h"
#include "MML_Game.h"
#include "MML_Gps.h"
#include "MML_Image.h"
#include "MML_Tv.h"
#include "MML_Radio.h"
#include "MML_Usb.h"
#include "MML_Video.h"
#include "MML_Wlan.h"
#include "MML_Utility.h"
#include "MML_Concurrent.h"
#include "MML_VideoSdk.h"
#include "MML_Rfid.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/
#define ATOMICITY_PROTECTION_BY_MESSAGE
#define FREE_USECASE_PARAMETER_AFTER_RESPONSE
#define WORKAROUND_ABORT_IMAGE_DECODING

#if defined(__SDK_SIMULATION__)
// Note: Audio player will still simulate middleware even enable this define
#define NO_MIDDLEWARE_SIMULATOR
#endif

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define MmlMsg_t                                vm_msg_t
#define MML_TRC_NORM                            (_CUS2 | LEVEL_30)
#define MML_TRC_IMAGE                           (_CUS2 | LEVEL_29)

//#define MML_DEBUG_SEND_TRACE
#ifdef MML_DEBUG_SEND_TRACE
//#define MML_DEBUG_SEND_TRACE_WITH_IMAGE
#ifndef MML_DEBUG_SEND_TRACE_WITH_IMAGE
#define MML_TRACE(lvl, fmt, ...) \
{ \
    if ((lvl != MML_TRC_IMAGE) && (lvl != (_SYS | LEVEL_29))) \
        sys_UartPrintf(fmt, ##__VA_ARGS__); \
}
#else
#define MML_TRACE(lvl, fmt, ...)                sys_UartPrintf(fmt, ##__VA_ARGS__)
#endif
#else
#define MML_TRACE                               vm_dbgTrace
#endif

#define MML_MALLOC(Type_t, nSize)               ((Type_t *)MsAllocateMem(nSize))
#define MML_MFREE(pMem)                         MsReleaseMemory(pMem)
#define MML_FLUSH(pMem, nSize)
#define MML_INVALIDATE(pMem, nSize)
#define MML_MEMSET(pMem, nVal, nSize)           memset(pMem, nVal, nSize)
#define MML_MEMCPY(pDst, pSrc, nSize)           memcpy(pDst, pSrc, nSize)
#define MML_MEMMOVE(pDst, pSrc, nSize)          memmove(pDst, pSrc, nSize)
#define MML_MEMCMP(pMem1, pMem2, nSize)         memcmp(pMem1, pMem2, nSize)

#define MML_SLEEP(nTick)                        MsSleep(nTick)
#define MML_DELAY(nMicroSec)
#define MML_GET_TICK                            MsGetOsTick

#define MML_SENDMSG(eMailbox, pMsg)             MsSend(eMailbox, pMsg)
#define MML_SEM_INIT                            MsInitSem(MML_MANAGER_SEM, 1)
#define MML_SEM_LOCK                            MsConsumeSem(MML_MANAGER_SEM)
#define MML_SEM_UNLOCK                          MsProduceSem(MML_MANAGER_SEM)
#define MML_SEM_CONSUME(nSemaphore)		        MsConsumeSem(nSemaphore)
#define MML_SEM_PRODUCE(nSemaphore)		        MsProduceSem(nSemaphore)

#if !defined(__SDK_SIMULATION__)
#define MML_ASSERT                              CUS_ASSERT
#else
#define MML_ASSERT                              assert
#endif

#define MML_GET_FIRST(pList)                   (((pList)->pNext != (pList)) ? (pList)->pNext : NULL)
#define MML_GET_NEXT(pList, pCur)              (((pCur == NULL) || (pCur->pNext == (pList))) ? NULL : pCur->pNext)
#define MML_SET_LIST(pListHead)                (pListHead)->pPrev = (pListHead); (pListHead)->pNext = (pListHead)

#define MML_BACKTRACE_HISTORY_SIZE             (16)    /* must be a power of 2 */
#define MML_BACKTRACE_HISTORY_INDEX(nIndex)    ((nIndex) & (MML_BACKTRACE_HISTORY_SIZE-1))
//#define MML_GETCHIPTYPE_SUCCESS                (0xFFFFFFFF) /* the value written to _g_nChipTypeErrorCode if get chip type success */
/*=============================================================*/
// Data type definition
/*=============================================================*/
/** @ingroup    MMLayerManager
    @brief      Timer IDs
*/
typedef enum
{
    MML_TIMER_ID_POWERMANAGEMENT = MML_TIMER_ID_BASE,
    MML_TIMER_ID_INVAILD = 0xFFFF,
} MmlTimerId_e;

/** @ingroup    MMLayerManager
    @brief      Use case internal handler prototype
    @param      pUseCaseParam         Pointer to the use case parameter structure
    @param      nUseCaseParamSize     Size in bytes of the use case parameter structure
    @param      nUserData             Interface self-reference
*/
struct MmlMultimediaGroup_t_;
typedef void (*PfnMmlUseCaseHandler)(void *pUseCaseParam, u32 nUseCaseParamSize, struct MmlMultimediaGroup_t_ *pGroup);

/** @ingroup    MMLayerManager
    @brief      Use case registration structure
*/
struct MmlUseCaseCallback_t_;
typedef struct MmlUseCaseCallback_t_
{
    struct MmlUseCaseCallback_t_    *pPrev;         ///< Link field
    struct MmlUseCaseCallback_t_    *pNext;         ///< Link field
    u32                             nUseCaseID;     ///< Use case ID to specify which use case you want to handle
    PfnMmlUseCaseCallback           pfnUCCallback;  ///< Use case callback function's address
    u32                             nUserData;      ///< Interface self-reference
} MmlUseCaseCallback_t;

/** @cond       MML_INTERNAL_DOC
    @ingroup    MMLayerManager
    @brief      Response payload
    @endcond
*/
typedef union
{
    MmlAudioResponse_t     tAudioResponse;     ///< Audio response payload
    MmlVideoResponse_t     tVideoResponse;     ///< Video response payload
    MmlImageResponse_t     tImageResponse;     ///< Image response payload
    MmlGameResponse_t      tGameResponse;      ///< Game response payload
    MmlUsbResponse_t       tUsbResponse;       ///< Usb response payload
    MmlTvResponse_t        tTvResponse;        ///< Tv response payload
    MmlCameraResponse_t    tCameraResponse;    ///< Camera response payload
    MmlRadioResponse_t     tRadioResponse;     ///< Radio response payload
    MmlGpsResponse_t       tGpsResponse;       ///< Gps response payload
    MmlWlanResponse_t      tWlanResponse;      ///< Wlan response payload
    MmlVideoSdkResponse_t     tVideoSdkResponse;     ///< Video SDK response payload
    MmlRfidResponse_t      tRfidResponse;      ///< Rfid response payload
} MmlManagerResponse_t;

/** @cond       MML_INTERNAL_DOC
    @ingroup    MMLayerManager
    @brief      Response callback registration structure
    @endcond
*/
typedef struct
{
    u16     nSenderID;              ///< Sender's mailbox ID
    u32     nUserValue;             ///< Interface self-reference
    void    *pfnResponseCallback;   ///< Callback function your want to register
} MmlManagerResponseCallback_t;

/** @cond       MML_INTERNAL_DOC
    @ingroup    MMLayerManager
    @brief      Data sturcture used to implement the async to sync conversion
    @endcond
*/
typedef struct
{
    u16     bAsyncToSync;           ///< Enable the async to sync conversion
    u16     bReadyToGo;             ///< Being waiting for a specific event (response received already)
    u32     nErrCode;               ///< Returned result (error code)
    void    *pResponse;             ///< Pointer to the returned response payload
    u32     nEvent;                 ///< Specify which event to wait for
    u16     bDropEvent;             ///< Set to TRUE to drop this event after conversion
} MmlManagerAsyncToSync_t;

/** @cond       MML_INTERNAL_DOC
    @ingroup    MMLayerManager
    @brief      Response registration structure
    @endcond
*/
struct MmlResponseCallback_t_;
typedef struct MmlResponseCallback_t_
{
    struct MmlResponseCallback_t_    *pPrev;               ///< Link field
    struct MmlResponseCallback_t_    *pNext;               ///< Link field
    u32                              nUseCaseID;           ///< Use case ID to specify which use case you want to handle
    void                             *pUseCaseParam;       ///< Pointer to the use case parameter sturcture
    MmlManagerResponseCallback_t     tResponseCallback;    ///< Registration data specifying the callback function' address
    MmlManagerAsyncToSync_t          tAsyncToSync;         ///< Data sturcture used to implement the async to sync conversion
} MmlResponseCallback_t;

/** @cond       MML_INTERNAL_DOC
    @ingroup    MMLayerManager
    @brief      Response internal handler prototype
    @param      pRCallback        Pointer to the response registration structure
    @param      nErrCode          Returned result (error code)
    @param      pResponse         Pointer to the returned response payload
    @endcond
*/
typedef void (*PfnMmlResponseHandler)(MmlResponseCallback_t *pRCallback, u32 nErrCode, void *pResponse);

/** @cond       MML_INTERNAL_DOC
    @ingroup    MMLayerManager
    @endcond
*/
typedef bool (*PfnMmlCallbackVoid)();


/** @cond       MML_INTERNAL_DOC
    @ingroup    MMLayerManager
    @brief      Notification payload
    @endcond
*/
typedef union
{
    MmlAudioNotify_t     tAudioNotify;     ///< Audio notification payload
    MmlVideoNotify_t     tVideoNotify;     ///< Video notification payload
    MmlImageNotify_t     tImageNotify;     ///< Image notification payload
    MmlGameNotify_t      tGameNotify;      ///< Game notification payload
    MmlUsbNotify_t       tUsbNotify;       ///< Usb notification payload
    MmlTvNotify_t        tTvNotify;        ///< Tv notification payload
    MmlCameraNotify_t    tCameraNotify;    ///< Camera notification payload
    MmlRadioNotify_t     tRadioNotify;     ///< Radio notification payload
    MmlGpsNotify_t       tGpsNotify;       ///< Gps notification payload
    MmlWlanNotify_t      tWlanNotify;      ///< Wlan notification payload
    MmlVideoSdkNotify_t     tVideoSdkNotify;     ///< Video SDK notification payload
    MmlRfidNotify_t      tRfidNotify;      ///< Rfid notification payload
} MmlManagerNotify_t;

/** @cond       MML_INTERNAL_DOC
    @ingroup    MMLayerManager
    @brief      Notification callback registration structure
    @endcond
*/
typedef struct
{
    u16      nSenderID;             ///< Sender's mailbox ID
    u32      nUserValue;            ///< Interface self-reference
    void     *pfnNotifyCallback;    ///< Callback function your want to register
} MmlManagerNotifyCallback_t;

/** @cond       MML_INTERNAL_DOC
    @ingroup    MMLayerManager
    @brief      Notification registration structure
    @endcond
*/
struct MmlNotifyCallback_t_;
struct MmlNotifyCallback_t_
{
    struct MmlNotifyCallback_t_    *pPrev;             ///< Link field
    struct MmlNotifyCallback_t_    *pNext;             ///< Link field
    u32                            nEvent;             ///< Specify which event you want to handle
    MmlManagerNotifyCallback_t     tNotifyCallback;    ///< Registration data specifying the callback function' address
};

/** @cond       MML_INTERNAL_DOC
    @ingroup    MMLayerManager
    @brief      Notification internal handler prototype
    @param      nEvent            Incoming event ID
    @param      pNotify           Pointer to the returned notification payload
    @endcond
*/
typedef MmlErrCode_e (*PfnMmlNotifyHandler)(u32 nEvent, void *pNotify);

/** @cond       MML_INTERNAL_DOC
    @ingroup    MMLayerManager
    @brief      Async to sync conversion handler prototype
    @param      nEvent            Incoming event ID
    @param      pNotify           Pointer to the returned notification payload
    @param      pRCallback        Pointer to the response registration structure
    @endcond
*/
typedef MmlErrCode_e (*PfnMmlAsyncToSyncHandler)
(
    u32                      nEvent,
    void                     *pNotify,
    MmlResponseCallback_t    *pRCallback
);

/** @cond       MML_INTERNAL_DOC
    @ingroup    MMLayerManager
    @brief      Message body used to add/remove/invoke the use case callbacks
    @endcond
*/
typedef struct
{
    u32                     nUseCaseID;             ///< Use case ID
    PfnMmlUseCaseCallback   pfnUCCallback;          ///< Address of the use case callback
    u32                     nUserData;              ///< Interface self-reference
    void                    *pUseCaseParam;         ///< Pointer to the use case parameter sturcture
    u32                     nUseCaseParamSize;      ///< The size in bytes of the use case parameter structure
} MmlUseCaseDescriptor_t;

/** @cond       MML_INTERNAL_DOC
    @ingroup    MMLayerManager
    @brief      Message body used to invoke the sender's response callback
    @endcond
*/
typedef struct
{
	u32     nUseCaseID;           ///< Use case ID
    u32     nErrCode;             ///< Returned result (error code)
    void    *pResponsePayload;    ///< Pointer to the response payload
} MmlResponseDescriptor_t;

/** @cond       MML_INTERNAL_DOC
    @ingroup    MMLayerManager
    @brief      Message body used to add/remove/invoke the notification callbacks
    @endcond
*/
typedef struct
{
    u32     nEvent;               ///< Event ID
    u16     nSenderID;            ///< Sender's mailbox ID
    u32     nUserValue;           ///< Interface self-reference
    void    *pfnNotifyCallback;   ///< Address of the notification callback
    void    *pNotifyPayload;      ///< Pointer to the noitfication payload
} MmlNotifyDescriptor_t;

/** @cond       MML_INTERNAL_DOC
    @ingroup    MMLayerManager
    @brief      Use case parameters
    @endcond
*/
typedef struct
{
	u32     nUseCaseID;             ///< Use case ID
	void    *pResponseCallback;     ///< Pointer to the response callback registration data
	void    *pResponse;             ///< Pointer to the response payload
} MmlManagerUCParam_t;

/** @ingroup    MMLayerManager
    @brief      Application data structure
*/
typedef struct
{
    MmlCameraStartPreview_t         tStartPreview;              ///< Used with 'MML_UCPARAM_CAMERA_START_PREVIEW'
    MmlCameraSensorInfo_t           tSensorInfo;                ///< Used with 'MML_RESPONSE_CAMERA_DETECT_SENSOR'
    MmlRadioSetRadioConfiguration_t tSetRadioConfig;            ///< Used with 'MML_UCPARAM_RADIO_SET_RADIO_CONFIGURATION'
	MmlCameraSetDigitalZoom_t       tSetDigitalZoom;            ///< Used with 'MML_UCID_CAMERA_SET_DIGITAL_ZOOM'
    MmlCameraSetExposure_t          tSetExposure;               ///< Used with 'MML_UCID_CAMERA_SET_EXPOSURE'
    MmlCameraSetWhiteBalance_t      tSetWhiteBalance;           ///< Used with 'MML_UCID_CAMERA_SET_WHITE_BALANCE'
    MmlCameraSetFocus_t             tSetFocus;                  ///< Used with 'MML_UCID_CAMERA_SET_FOCUS'
    MmlCameraSetEV_t                tSetEV;                     ///< Used with 'MML_UCID_CAMERA_SET_EV'
    MmlCameraSetAntiFlicker_t       tSetAntiFlicker;            ///< Used with 'MML_UCID_CAMERA_SET_ANTI_FLICKER'
    MmlCameraSetImageEffect_t       tSetImageEffect;            ///< Used with 'MML_UCID_CAMERA_SET_IMAGE_EFFECT'
    MmlCameraSetSceneMode_t         tSetSceneMode;              ///< Used with 'MML_UCID_CAMERA_SET_SCENE_MODE'
    MmlImageEncodeImage_t           tImageEncodingToPath;       ///< Used with 'MML_UCID_IMAGE_ENCODE_IMAGE' to presave the path given by application
    MmlImageEncodeImage_t           tImageEncodingToBuffer;     ///< Used with 'MML_UCID_IMAGE_ENCODE_IMAGE' to presave the output buffer address and length
    MmlVideoStartRecording_t        tVideoEncodingToPath;       ///< Used with 'MML_UCID_VIDEO_START_RECORDING' to presave the path given by application
    MmlImageOutputType_e            eImageEncodeOutputType;     ///< Used with 'MML_UCID_IMAGE_ENCODE_IMAGE' to save the encoding output type
    MmlMultimediaCapability_t       tMultimediaCapability;
    MmlMultimediaResource_t         tMultimediaResource;
} MmlApplicationData_t;

/** @ingroup    MMLayerManager
    @brief      Multimedia group structure
*/
struct MmlMultimediaGroup_t_
{
    MmlUseCaseGroupId_e           eGroupID;                   ///< Use case group ID
    MmlUseCaseCallback_t          tUCCallbackList;            ///< Head of the use case callback list
    PfnMmlUseCaseHandler          pfnUseCasePreHandler;       ///< Internal use case pre-handler
    PfnMmlUseCaseHandler          pfnUseCasePostHandler;      ///< Internal use case post-handler
    MmlResponseCallback_t         tRCallbackList;             ///< Head of the response callback list
    PfnMmlResponseHandler         pfnResponsePreHandler;      ///< Internal response pre-handler
    PfnMmlResponseHandler         pfnResponsePostHandler;     ///< Internal response post-handler
    MmlNotifyCallback_t           tNCallbackList;             ///< Head of the notification callback list
    PfnMmlNotifyHandler           pfnNotifyPreHandler;        ///< Internal notification pre-handler
    PfnMmlNotifyHandler           pfnNotifyPostHandler;       ///< Internal notification post-handler
    PfnMmlAsyncToSyncHandler      pfnAsyncToSyncHandler;      ///< Async to sync conversion handler
    s32                           nResponseReadyToGoCount;    ///< Count how many responses are ready-to-go, waiting for the events
    u32                           nLastErrCode;               ///< The last error code returned from RUNTIME_ERROR event
};

/** @ingroup    MMLayerManager
    @brief      Backtrace record types
*/
typedef enum
{
    MML_BACKTRACE_RECORDTYPE_UNUSED = 0x0,
    MML_BACKTRACE_RECORDTYPE_COMMAND,
    MML_BACKTRACE_RECORDTYPE_RESPONSE,
    MML_BACKTRACE_RECORDTYPE_NOTIFY,
    MML_BACKTRACE_RECORDTYPE_NUM
} MmlBacktraceRecordType_e;

/** @ingroup    MMLayerManager
    @brief      Backtrace record used to log the command that is sent from\n
                resource manager to middleware
*/
typedef struct
{
    u32         nUseCaseID;             ///< Use case ID
    void        *pfnCommandCallback;    ///< Address of the command callback
    u32         nParameter;             ///< Used to log any parameter you think important to this command
} MmlBacktraceRecordCommand_t;

/** @ingroup    MMLayerManager
    @brief      Backtrace record used to log the command response that is sent from\n
                middleware to resource manager
*/
typedef struct
{
    u32         nUseCaseID;             ///< Use case ID
    void        *pfnResponseCallback;   ///< Address of the response callback
    u32         nErrCode;               ///< Returned result (error code)
    u32         nPayload;               ///< Used to log any payload you think important to this response
} MmlBacktraceRecordResponse_t;

/** @ingroup    MMLayerManager
    @brief      Backtrace record used to log the command response that is sent from\n
                middleware to resource manager
*/
typedef struct
{
    u32         nEvent;                 ///< Event ID
    void        *pfnNotifyCallback;     ///< Address of the notification callback
                                        ///< Set NULL when notify being dropped due to mailbox over threshold
    u32         nPayload;               ///< Used to log any payload you think important to this response
} MmlBacktraceRecordNotify_t;

/** @ingroup    MMLayerManager
    @brief      Backtrace record used to keep track of the activities between\n
                resource manager and middlewares
*/
typedef struct MmlBacktraceRecord_t_
{
    MmlBacktraceRecordType_e            eRecordType;    ///< Specify which type of this record
    u32                                 nTick;          ///< Timestamp

    /// union of MmlBacktraceRecord_t parameters
    union
    {
        MmlBacktraceRecordCommand_t     tRecordCommand;
        MmlBacktraceRecordResponse_t    tRecordResponse;
        MmlBacktraceRecordNotify_t      tRecordNotify;
    } uParam;
} MmlBacktraceRecord_t;

/** @ingroup    MMLayerManager
    @brief      Backtrace history
*/
typedef struct MmlBacktraceHistory_t_
{
    u32                     bSysPowerDown;
    u32                     nIndexAudio;
    u32                     nIndexVideo;
    u32                     nIndexImage;
    u32                     nIndexGame;
    u32                     nIndexUsb;
    u32                     nIndexTv;
    u32                     nIndexCamera;
    u32                     nIndexRadio;
    u32                     nIndexWlan;
    u32                     nIndexGps;
    u32                     nIndexVideoSdk;
    u32                     nIndexRfid;
    u32                     nPowerManagementTimerInterval;
    MmlBacktraceRecord_t    tRecordAudio[MML_BACKTRACE_HISTORY_SIZE];
    MmlBacktraceRecord_t    tRecordVideo[MML_BACKTRACE_HISTORY_SIZE];
    MmlBacktraceRecord_t    tRecordImage[MML_BACKTRACE_HISTORY_SIZE];
    MmlBacktraceRecord_t    tRecordGame[MML_BACKTRACE_HISTORY_SIZE];
    MmlBacktraceRecord_t    tRecordUsb[MML_BACKTRACE_HISTORY_SIZE];
    MmlBacktraceRecord_t    tRecordTv[MML_BACKTRACE_HISTORY_SIZE];
    MmlBacktraceRecord_t    tRecordCamera[MML_BACKTRACE_HISTORY_SIZE];
    MmlBacktraceRecord_t    tRecordRadio[MML_BACKTRACE_HISTORY_SIZE];
    MmlBacktraceRecord_t    tRecordGps[MML_BACKTRACE_HISTORY_SIZE];
    MmlBacktraceRecord_t    tRecordWlan[MML_BACKTRACE_HISTORY_SIZE];
    MmlBacktraceRecord_t    tRecordVideoSdk[MML_BACKTRACE_HISTORY_SIZE];
    MmlBacktraceRecord_t    tRecordRfid[MML_BACKTRACE_HISTORY_SIZE];
} MmlBacktraceHistory_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/
extern MmlBacktraceHistory_t      _g_tBacktraceHistory;
extern u16                        _g_nMemoryConfig;

/*=============================================================*/
// Global function definition
/*=============================================================*/
#ifdef MML_DEBUG_SEND_TRACE
void mml_send_msg(char *msg);
s8 mml_send_trace(u32 Level, const char *strFormat, ...);
#endif

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Initialize the multimedia manager kernel table
*
*   @retval       MML_ERROR_SUCCESS    Succeed
*   @endcond
*/
MmlErrCode_e MmlKernelTableInit(void);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Reset the multimedia manager kernel table
*
*   @retval       MML_ERROR_SUCCESS    Succeed
*   @endcond
*/
MmlErrCode_e MmlKernelTableDelete(void);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Find a multimedia group entry from the kernel table
*
*   @param[out]   ppGroup     Pointer to the pointer to the returned group entry
*   @param[in]    eGroupID    Use case group ID
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @endcond
*/
MmlErrCode_e MmlKernelTableLookUp
(
    MmlMultimediaGroup_t     **ppGroup,
    MmlUseCaseGroupId_e      eGroupID
);


MmlErrCode_e MmlCallbackRegister
(
    MmlCallbackId_e  eCallbackID,
    void            *pfnCallback
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Add the specified callback to use case callback list
*
*   @param[in]    nUseCaseID     Use case ID
*   @param[in]    pfnUCCallback  Address of the use case callback
*   @param[in]    nUserData      Interface self-reference
*   @param[out]   ppUCCallback   Pointer to the pointer to the returned use case registration structure
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_PARAMETER_INVALID         Failed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @retval       MML_ERROR_PRECONDITIONS_VIOLATED    Failed
*   @retval       MML_ERROR_MEMORY_FAILURE            Failed
*   @endcond
*/
MmlErrCode_e MmlUseCaseCallbackAttach
(
    u32                     nUseCaseID,
    PfnMmlUseCaseCallback   pfnUCCallback,
    u32                     nUserData,
    MmlUseCaseCallback_t    **ppUCCallback
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Remove the specified callback from use case callback list
*
*   @param[in]    nUseCaseID       Use case ID
*   @param[in]    pfnUCCallback    Address of the use case callback
*   @param[in]    nUserData        Interface self-reference
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_PARAMETER_INVALID         Failed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @retval       MML_ERROR_PRECONDITIONS_VIOLATED    Failed
*   @endcond
*/
MmlErrCode_e MmlUseCaseCallbackDetach
(
    u32                     nUseCaseID,
    PfnMmlUseCaseCallback   pfnUCCallback,
    u32                     nUserData
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Dispatch the registered use case callbacks
*
*   @param[in]    nUseCaseID            Use case ID
*   @param[in]    pUseCaseParam         Pointer to the use case parameter sturcture
*   @param[in]    nUseCaseParamSize     The size in bytes of the use case parameter structure
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @retval       MML_ERROR_PRECONDITIONS_VIOLATED    Failed
*   @endcond
*/
MmlErrCode_e MmlUseCaseCallbackDispatch
(
    u32     nUseCaseID,
    void    *pUseCaseParam,
    u32     nUseCaseParamSize
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Send message to manager task to add a use case callback to list
*
*   @param[in]    pDescriptor    Message body used to add the use case callback
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_PARAMETER_INVALID         Failed
*   @retval       MML_ERROR_MEMORY_FAILURE            Failed
*   @endcond
*/
MmlErrCode_e MmlUseCaseCallbackMessageAttach
(
    MmlUseCaseDescriptor_t   *pDescriptor
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Send message to manager task to remove a use case callback from list
*
*   @param[in]    pDescriptor    Message body used to remove the use case callback
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_PARAMETER_INVALID         Failed
*   @retval       MML_ERROR_MEMORY_FAILURE            Failed
*   @endcond
*/
MmlErrCode_e MmlUseCaseCallbackMessageDetach
(
    MmlUseCaseDescriptor_t   *pDescriptor
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Send message to manager task to invoke the registered use case callbacks
*
*   @param[in]    pDescriptor    Message body used to invoke the use case callbacks
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_PARAMETER_INVALID         Failed
*   @retval       MML_ERROR_MEMORY_FAILURE            Failed
*   @endcond
*/
MmlErrCode_e MmlUseCaseCallbackMessageDispatch
(
    MmlUseCaseDescriptor_t   *pDescriptor
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Traverse list to invoke all of the associated use case callbacks
*
*   @param[in]    nUseCaseID            Use case ID
*   @param[in]    pUseCaseParam         Pointer to the use case parameter sturcture
*   @param[in]    nUseCaseParamSize     The size in bytes of the use case parameter structure
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @retval       MML_ERROR_PRECONDITIONS_VIOLATED    Failed
*   @endcond
*/
MmlErrCode_e MmlUseCaseCallbackInvoke
(
    u32     nUseCaseID,
    void    *pUseCaseParam,
    u32     nUseCaseParamSize
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Add the specified callback to response callback list
*
*   @param[in]    nUseCaseID             Use case ID
*   @param[in]    nSenderID              Sender's mailbox ID
*   @param[in]    nUserValue             Interface self-reference
*   @param[in]    pUseCaseParam          Pointer to the use case parameter sturcture
*   @param[in]    pfnResponseCallback    Address of the response callback
*   @param[out]   ppNCallback            Pointer to the pointer to the returned response registration structure
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_PARAMETER_INVALID         Failed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @retval       MML_ERROR_PRECONDITIONS_VIOLATED    Failed
*   @retval       MML_ERROR_MEMORY_FAILURE            Failed
*   @endcond
*/
MmlErrCode_e MmlResponseCallbackAttach
(
    u32                       nUseCaseID,
    u16                       nSenderID,
    u32                       nUserValue,
    void                      *pUseCaseParam,
    void                      *pfnResponseCallback,
    MmlResponseCallback_t     **ppRCallback
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Remove the specified callback from response callback list
*
*   @param[in]    nUseCaseID              Use case ID
*   @param[in]    nSenderID               Sender's mailbox ID
*   @param[in]    nUserValue              Interface self-reference
*   @param[in]    pfnResponseCallback     Address of the response callback
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_PARAMETER_INVALID         Failed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @retval       MML_ERROR_PRECONDITIONS_VIOLATED    Failed
*   @endcond
*/
MmlErrCode_e MmlResponseCallbackDetach
(
    u32     nUseCaseID,
    u16     nSenderID,
    u32     nUserValue,
    void    *pfnResponseCallback
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Dispatch the registered response callback
*
*   @param[in]    nUseCaseID          Use case ID
*   @param[in]    nErrCode            Returned result (error code)
*   @param[in]    pResponsePayload    Pointer to the response payload
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @retval       MML_ERROR_PRECONDITIONS_VIOLATED    Failed
*   @endcond
*/
MmlErrCode_e MmlResponseCallbackDispatch
(
 	u32     nUseCaseID,
    u32     nErrCode,
    void    *pResponsePayload
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Send message to manager task to invoke the sender's response callback
*
*   @param[in]    pDescriptor    Message body used to invoke the sender's response callbacks
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_PARAMETER_INVALID         Failed
*   @retval       MML_ERROR_MEMORY_FAILURE            Failed
*   @endcond
*/
MmlErrCode_e MmlResponseCallbackMessageDispatch
(
    MmlResponseDescriptor_t   *pDescriptor
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Add the specified callback to notification callback list
*
*   @param[in]    nEvent               Event ID
*   @param[in]    nSenderID            Sender's mailbox ID
*   @param[in]    nUserValue           Interface self-reference
*   @param[in]    pfnNotifyCallback    Address of the notification callback
*   @param[out]   ppNCallback          Pointer to the pointer to the returned notification registration structure
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_PARAMETER_INVALID         Failed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @retval       MML_ERROR_PRECONDITIONS_VIOLATED    Failed
*   @retval       MML_ERROR_MEMORY_FAILURE            Failed
*   @endcond
*/
MmlErrCode_e MmlNotifyCallbackAttach
(
    u32                       nEvent,
    u16                       nSenderID,
    u32                       nUserValue,
    void                      *pfnNotifyCallback,
    MmlNotifyCallback_t       **ppNCallback
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Remove the specified callback from notification callback list
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
*   @endcond
*/
MmlErrCode_e MmlNotifyCallbackDetach
(
    u32     nEvent,
    u16     nSenderID,
    u32     nUserValue,
    void    *pfnNotifyCallback
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Dispatch the registered notification callbacks
*
*   @param[in]    nEvent               Event ID
*   @param[in]    pNotifyPayload       Pointer to the noitfication payload
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @retval       MML_ERROR_PRECONDITIONS_VIOLATED    Failed
*   @endcond
*/
MmlErrCode_e MmlNotifyCallbackDispatch
(
    u32     nEvent,
    void    *pNotifyPayload
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Send message to manager task to add a notification callback to list
*
*   @param[in]    pDescriptor    Message body used to add the notification callback
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_PARAMETER_INVALID         Failed
*   @retval       MML_ERROR_MEMORY_FAILURE            Failed
*   @endcond
*/
MmlErrCode_e MmlNotifyCallbackMessageAttach
(
    MmlNotifyDescriptor_t   *pDescriptor
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Send message to manager task to remove a notification callback from list
*
*   @param[in]    pDescriptor    Message body used to remove the notification callback
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_PARAMETER_INVALID         Failed
*   @retval       MML_ERROR_MEMORY_FAILURE            Failed
*   @endcond
*/
MmlErrCode_e MmlNotifyCallbackMessageDetach
(
    MmlNotifyDescriptor_t   *pDescriptor
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Send message to manager task to invoke the registered notification callbacks
*
*   @param[in]    pDescriptor    Message body used to invoke the notification callbacks
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_PARAMETER_INVALID         Failed
*   @retval       MML_ERROR_MEMORY_FAILURE            Failed
*   @endcond
*/
MmlErrCode_e MmlNotifyCallbackMessageDispatch
(
    MmlNotifyDescriptor_t   *pDescriptor
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Print the specified use case callback list
*
*   @param[in]    eGroupID    Use case group ID
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @endcond
*/
MmlErrCode_e MmlUseCaseCallbackPrint
(
    MmlUseCaseGroupId_e     eGroupID
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Print the specified notification callback list
*
*   @param[in]    eGroupID    Use case group ID
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @endcond
*/
MmlErrCode_e MmlNotifyCallbackPrint
(
    MmlUseCaseGroupId_e     eGroupID
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Handler to process the resource manager's messages
*
*   @param[in]    nMessageType    Message ID
*   @param[in]    pMessage        Pointer to the message payload
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @endcond
*/
MmlErrCode_e MmlResMgrMessageHandler
(
    u16      nMessageType,
    void     *pMessage
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Get the last code, returned from RUMTIME_ERROR event
*
*   @param[in]    eGroupID    Use case group ID
*   @param[in]    pErrCode    Pointer to the variable to store the last error code
*
*   @retval       MML_ERROR_SUCCESS                   Succeed
*   @retval       MML_ERROR_INTERNAL_ERROR            Failed
*   @endcond
*/
MmlErrCode_e MmlLastErrorCodeGet
(
    MmlUseCaseGroupId_e     eGroupID,
    u32                     *pErrCode
);

/** @cond         MML_INTERNAL_DOC
*   @ingroup      MMLayerManager
*   @brief        Get the dynamic adjust interval time in millionseconds
*
*   @param[in]    nInterval    Interval to be adjusted
*   @param[in]    nDelta       Step to increase
*   @param[in]    nMaximum     Upper bound
*
*   @retval       The dynamic adjust interval time in millionseconds
*   @endcond
*/
u32 MmlAdaptiveTimerIntervalGet
(
    u32     nInterval,
    u32     nDelta,
    u32     nMaximum
);

#ifdef __cplusplus
}
#endif

#endif //__MML_MANAGER_H__

