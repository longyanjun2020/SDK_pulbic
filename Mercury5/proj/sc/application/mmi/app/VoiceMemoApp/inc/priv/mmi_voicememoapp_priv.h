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
* @file    mmi_voicememoapp_priv.h
* @version
* @brief   voicememo applet private header file
*
*/

#ifndef __MMI_VOICEMEMOAPP_PRIV_H__
#define __MMI_VOICEMEMOAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_voicememoapp.h"
#include "mmi_common_util.h"
#include "mmi_common_dialog.h"
#include "mmi_common_custom.h"
#include "mmi_common_vtm.h"
#include "mmi_voicememoapp_id.h"
#include "voicememoapp_resource.h"
#include "mmi_srv_usb.h"
#include "mmi_srv_audio.h"
#include "mmi_srv_audiorecorder.h"
#include "mmi_UrlSrvClientHelper.h"
#include "mmi_common_window.h"
#include "mmi_common_storage_mgr.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
/* The minimum space for starting AMR recording. */
#define VOICEMEMOAPP_MINIMUM_RECORD_SPACE_LIMIT 10 // 10 KB

/* The maximum value for WdgProgressSetTotal(). */
#define VOICEMEMOAPP_MAXIMUM_PROGRESS_VALUE_LIMIT (0xFFFF)

#define VOICEMEMOAPP_ZERO_START_TIME L"00:00:00"

/* The type of message to be displayed on dialog. */
typedef enum
{
    VOICEMEMO_MSG_NONE = 0,
    VOICEMEMO_MSG_EXTCARDABSENT,
    VOICEMEMO_MSG_FILESTORED,
    VOICEMEMO_MSG_FILEBROKEN,
    VOICEMEMO_MSG_UNSUPPORTEDFORMAT,
    VOICEMEMO_MSG_STORAGEINSUFFICIENT,
    VOICEMEMO_MSG_DEFAULTFOLDERNOTEXISTED,
    VOICEMEMO_MSG_DELETESUCCESS,
    VOICEMEMO_MSG_DELETEFAIL,
    VOICEMEMO_MSG_RECORDFAIL,
    VOICEMEMO_MSG_PLAYFAIL,
    VOICEMEMO_MSG_SAVEFAIL,
    VOICEMEMO_MSG_DONE,
    VOICEMEMO_MSG_RECORDSUCCESS,
    VOICEMEMO_MSG_RECORDABORT,
} VoiceMemoAppMsg_e;


typedef struct
{
    IWidget *pVOICEMEMOAPP_RECORDER_STATUS_TEXTWIDGET;
    IWidget *pVOICEMEMOAPP_RECORDER_TIME_TEXTWIDGET;
    IWidget *pVOICEMEMOAPP_RECORDER_PROGRESS_PROGRESSWIDGET;
#ifdef __IFONE_STYLE_MMI_VOICEMEMO__
    IWidget *pVOICEMEMOAPP_RECORDER_STARTORPAUSE_WIDGET;
    IWidget *pVOICEMEMOAPP_RECORDER_STOPORSAVE_WIDGET;
    IWidget *pVOICEMEMOAPP_RECORDER_BUTTONG_CONTAINER_WIDGET;
    IWidget *pVOICEMEMOAPP_RECORDER_NEEDLE_CONTAINER_WIDGET;
    IWidget *pVOICEMEMOAPP_RECORDER_BG_WIDGET;
    IWidget *pVOICEMEMOAPP_RECORDER_SETTINGS_WIDGET;
#endif
} VoiceMemoAppRecorderViewWdgList_t;


typedef struct
{
    IWidget *pVOICEMEMOAPP_PLAYER_INFO_TEXTWIDGET;
    IWidget *pVOICEMEMOAPP_PLAYER_ELAPSEDTIME_TEXTWIDGET;
    IWidget *pVOICEMEMOAPP_PLAYER_TOTALTIME_TEXTWIDGET;
    IWidget *pVOICEMEMOAPP_PLAYER_PROGRESS_PROGRESSWIDGET;
} VoiceMemoAppPlayerViewWdgList_t;

/* The data structure is used for storing the variables of the player view. */
typedef struct
{
    MAE_WChar *pContentURL; // Full path of the recorded file
} VoiceMemoAppPlayerView_t;

typedef struct
{
    IWidget *pMenuWdg;
} VoiceMemoSetRecordTypeViewWdgList_t;

typedef struct
{
    VoiceMemoSetRecordTypeViewWdgList_t tWdgList;
} VoiceMemoSetRecordTypeViewWndData_t;

/**
 * Application structure
 */
typedef struct
{
    APPLET_BASE_ELEMENTS;

    VoiceMemoAppPlayerView_t *pPlayerView;  // Data of player view
    MAE_WChar *pTmpFilePath;                // Full path of the temporarily recorded file (including path and file name)
    MAE_WChar *pTmpFileName;                // Name of the temporarily recorded file
    u32 nProgressUnit;                      // Unit of the progress widget of elapsed time: number of seconds per tick
    u32 nTotalPlayTime;                     // Length of recorded time (unit: millisecond)
    boolean bIsRecording;                   // Flag of app is recordinging memo
    boolean bIsPausing;                     // Flag of app is pausing memo
    boolean bIsPlaying;                     // Flag of app is playing memo
    boolean bIsViewFiles;                   // Flag of app is viewing files
    boolean bIsMemCardEjected;              // TRUE: card plug out while receive SD card status ind., FALSE: card plug in
    boolean bIsSuspend;                     // Flag of app is suspend
    u32 nClient;                            // Client that lunch this app
    CmnLaunchAppFileOpRspCb pfnFileOpRspCb; // Response callback to client
#ifdef __IFONE_STYLE_MMI_VOICEMEMO__
    IDisplay *pDisplay;
    IBitmap *pBitmapImg;
    IWidget *pBmpWdg;
    u32 PointerInitAngle;
    u32 InitPointOnCircle_X,InitPointOnCircle_Y;
    boolean step_flag;
#endif
    u32 u32StartMode; 						// App start mode: APM_START_NORMAL or APM_START_EMBEDDED
    MediaSrvAudCodec_e eRecType;            // record setting type
    u8 uWaitCbCnt;                          // Flag of app waiting cb count, if not zero, don't accpt recording command
    StorageType_e eUsingStorage;            // current record/play stoarge
} VoiceMemoAppData_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function prototype declaration
/*=============================================================*/
MAE_Ret VoiceMemoConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret VoiceMemoDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean VoiceMemoAppStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean VoiceMemoAppStopCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean VoiceMemoAppSuspendCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean VoiceMemoAppResumeCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean VoiceMemoKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean VoiceMemoEmbededApCloseCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

MAE_Ret VoiceMemoWndRecorderInitViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret VoiceMemoWndRecorderPlayerViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret VoiceMemoWndRecorderPlayerOptionViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

void VoiceMemoOptionMenuKeyPressCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);
boolean VoiceMemoDeleteConfirmDialogKeyPressCb(void *pData, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
#ifndef __IFONE_STYLE_MMI_VOICEMEMO__
void VoiceMemoVolumeModelListener(void *pUserData, ModelEvent_t *pModelEvent);
#endif
void VoiceMemoAudioInterruptIndCb(void *pThis, u32 nCusData, MediaSrvInterruptStatus_e eStatus);
void VoiceMemoExtCardPluginHandleCb(void *pUserData, ACCDeviceType_e eDevice, boolean bPlug,ExtCardAccInfo_e eCardinfo);
void VoiceMemoUSBStatusChangeCb(void *pData, MMI_USB_STATUS_E eUsbStatus);
#if defined(__APP_MMI_CHECKDISK__)
void VoiceMemoCheckDiskStatusListener(char *pSbjName, SubjectStatus_e nSbjStatus, void *pUser);
#endif
void VoiceMemoRecorderStartRecordResultCb(void *pData, MediaSrvErrCode_e eErrorCode);
void VoiceMemoRecorderStopRecordResultCb(void *pData, MediaSrvErrCode_e eErrorCode, AudioRecSrvFileInfo_t *pFileInfo);
#ifndef __IFONE_STYLE_MMI_VOICEMEMO__
void VoiceMemoRecorderResumeRecordResultCb(void *pData, MediaSrvErrCode_e eErrorCode);
void VoiceMemoRecorderPauseRecordResultCb(void *pData, MediaSrvErrCode_e eErrorCode, AudioRecSrvFileInfo_t *pFileInfo);
#endif
void VoiceMemoRecorderRecordingStatusIndCb(void *pData, u32 nCusData, AudioRecSrvStatusInd_e eStatus, AudioRecSrvStatusNotifyInfo_t *pInfo);
void VoiceMemoRecorderGetFileInfoIndCb(void *pData, MediaSrvErrCode_e eErrorCode, u32 nCusData, AudioSrvFileInfo_t *pAudFileInfo);
#ifndef __IFONE_STYLE_MMI_VOICEMEMO__
void VoiceMemoPlayerStartResultCb(void *pData, MediaSrvErrCode_e eErrorCode);
void VoiceMemoPlayerStopResultCb(void *pData, MediaSrvErrCode_e eErrorCode);
void VoiceMemoPlayerPlayStatusIndCb(void *pThis, u32 nCusData, AudioSrvPlayStatusEvent_e eEventId, u32 nInfoData);
#endif
void VoiceMemoCleanup(IBase *pIssuer, u32 nParam);

#endif /* __MMI_VOICEMEMOAPP_PRIV_H__ */
