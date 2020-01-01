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
* @file    mmi_videoplayerapp_priv.h
* @version
* @brief   Video player applet private header file
*
*
*/

#ifndef __MMI_VIDEOPLAYERAPP_PRIV_H__
#define __MMI_VIDEOPLAYERAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_videoplayerapp.h"
#include "mmi_common_dialog_id.h"
#include "mmi_common_cfg.h"
#include "mmi_common_vtm.h"
#include "mmi_videoplayerapp_id.h"
#include "videoplayerapp_resource.h"
#include "mmi_videoplayerapp_rs.h"

#ifdef __MMI_KING_MOVIE__
#include "mmi_mae_md5.h"
#endif

#include "mmi_srv_header.h"
#include "mmi_launcher_filemanager.h"
#include "mmi_event.h"


/*=============================================================*/
// Macro definition
/*=============================================================*/
#ifdef __OFN_DRV_GPIO_SIMU_I2C__
#define __VIDEOPLAYERAPP_OPTICAL_FINGER_NAVIGATION__
#endif

#define __VIDEOPLAYERAPP_AUTO_RESUME__

#ifdef BREAKIFWNDIDINVALID
#undef BREAKIFWNDIDINVALID
#endif
#define BREAKIFWNDIDINVALID(a, ret) { if(WND_ID_INVALID == a){\
                                ret = MAE_RET_FAILED; break; \
                            }}
#ifdef __MMI_KING_MOVIE__
#define VIDEOPLAYERAPP_DIALOG_TIMER (1000)
#endif

#define ABS(a) ((a)<0?-(a):(a))

#define START_PLAY_POSITION 0
#define MSEC_PER_SEC	1000
#define MSEC_PER_HALF_SEC	500

#define NORMAL_PANEL_DISPLAY_REGION_X       VIDEOPLAYERAPP_PANEL_VIDEO_OSDWIDGET_X_POSITION
#define NORMAL_PANEL_DISPLAY_REGION_Y       VIDEOPLAYERAPP_PANEL_VIDEO_OSDWIDGET_Y_POSITION
#define NORMAL_PANEL_DISPLAY_REGION_WIDTH   VIDEOPLAYERAPP_PANEL_VIDEO_OSDWIDGET_WIDTH
#define NORMAL_PANEL_DISPLAY_REGION_HEIGHT  VIDEOPLAYERAPP_PANEL_VIDEO_OSDWIDGET_HEIGHT
#define FULL_PANEL_DISPLAY_REGION_WIDTH     VIDEOPLAYERAPP_FULLSCREEN_VIDEO_OSDWIDGET_WIDTH
#define FULL_PANEL_DISPLAY_REGION_HEIGHT    VIDEOPLAYERAPP_FULLSCREEN_VIDEO_OSDWIDGET_HEIGHT
#define FULL_PANEL_DISPLAY_REGION_X         VIDEOPLAYERAPP_FULLSCREEN_VIDEO_OSDWIDGET_X_POSITION
#define FULL_PANEL_DISPLAY_REGION_Y         VIDEOPLAYERAPP_FULLSCREEN_VIDEO_OSDWIDGET_Y_POSITION

#ifdef __VIDEOPLAYERAPP_FFREWIND_SUPPORT__
#define FFREWIND_START_TIMER            100
#define FFREWIND_STOP_TIMER             5
#define FASTFORWARD_REWIND_TIME_UNIT    20
#endif

#define SEEK_DURATION                    400

#define DEFAULT_VIDEOPLAYER_VOLUME      4
#define FULLSCREEN_CLOSE_PANEL_TIMER    (5 * MSEC_PER_SEC) // 5 seconds

#define VIDEOPLAYER_BATCH_SEARCH_FILE_NUM     (100) // need to consider memory usage

// W > 352 && H > 288 --> HQ
#define VIDEOPLAYER_HQ_MIN_WIDTH 352
#define VIDEOPLAYER_HQ_MIN_HEIGHT 288

// W > 720 && H > 576 --> HD
#define VIDEOPLAYER_HD_MIN_WIDTH 720
#define VIDEOPLAYER_HD_MIN_HEIGHT 576

#ifdef __MMI_STEREO_VIDEO__
#define VIDEOPLAYER_DEPTH_MAX_LEVEL 8
#define VIDEOPLAYER_DEPTH_MIN_LEVEL 0
#endif
/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
	NORMAL_MODE,
	FULLSCREEN_MODE
} VideoPlayerDisplayMode_e;

typedef enum
{
    PLAY_NEXT,
    PLAY_PREVIOUS,
    PLAY_NULL = 0xFF,
} VideoPlayerPlayAction_e;

#ifdef __VIDEOPLAYERAPP_FFREWIND_SUPPORT__
typedef enum
{
    FFREWIND_NONE,
    FASTFORWARD_ACTION,
    REWIND_ACTION
} VideoPlayerFFRewindAction_e;
#endif

typedef enum
{
    APP_NOT_SUSPEND = 0, // Not receive APP_SUSPEND yet.
    APP_SUSPENDING, // Receive APP_SUSPEND, and video is pausing or waiting some media confirm.
    APP_SUSPENDED // Confirm APM_SUSPEND.
} VIDEOPLAYERAPP_APP_SUSPEND_STATE;

typedef enum
{
    MEDIA_NOT_SUSPEND = 0, // Not receive IMEDIA_IND_INTERRUPED yet.
    MEDIA_SUSPENDING, // Receive IMEDIA_IND_INTERRUPTED, and video is stopping and wait stop success.
    MEDIA_SUSPENDED // Receive stop success.
} VIDEOPLAYERAPP_MEDIA_SUSPEND_STATE;

typedef enum
{
    INFO_DIALOG_WARNING,
    INFO_DIALOG_DONE,
    INFO_DIALOG_UNKNOWN
} VIDEOPLAYERAPP_INFO_DIALOG_TYPE;

typedef enum
{
    STATUS_STOP,
    STATUS_PAUSE,
    STATUS_PLAY,
} VideoPlayerAppStatus_e;

typedef enum
{
    STOP_BY_USER,
    STOP_BY_PICK,
    STOP_BY_RSK,
    STOP_BY_APP_STOP,
    STOP_BY_MEDIA_SUSPEND,
    STOP_BY_SETPOS_FAILED,
    STOP_BY_OPTION,
    STOP_BY_APP_SUSPEND,
    STOP_BY_NONE
} VideoPlayerStopReason_e;

typedef enum
{
    VOL_IMG_DECREASE_DISABLE = 0,
    VOL_IMG_DECREASE_PRESSED,
    VOL_IMG_DECREASE_UNPRESSED,
    VOL_IMG_INCREASE_DISABLE,
    VOL_IMG_INCREASE_PRESSED,
    VOL_IMG_INCREASE_UNPRESSED,
    VOL_IMG_MAX
} VideoPlayerVolImgStatusId_e;

typedef enum
{
    PLAYBACK_IMG_PLAY_ENABLE = 0,
    PLAYBACK_IMG_PAUSE_ENABLE,
    PLAYBACK_IMG_PAUSE_DISABLE,
    PLAYBACK_IMG_MAX
} VideoPlayerPlaybackImgStatusId_e;

typedef enum
{
    FFREWIND_IMG_DISABLE = 0,
    FFREWIND_IMG_ENABLE,
    FFREWIND_IMG_PREV_NEXT_ENABLE,
    FFREWIND_IMG_MAX
} VideoPlayerFFRewindImgStatusId_e;

typedef enum
{
    VIDEO_SEEK_MODE__OFF, //Disable Seek
    VIDEO_SEEK_MODE__DOWNLOADED_ONLY, //Seek only alread downloaded data
    VIDEO_SEEK_MODE__ALL, //Seekable
} VideoPlayerSeekMode_e;

typedef enum
{
    VIDEOPLAYERAPP_CONNECTION_TYPE_WIFI,
    VIDEOPLAYERAPP_CONNECTION_TYPE_GPRS_SIM_MASTER,
    VIDEOPLAYERAPP_CONNECTION_TYPE_GPRS_SIM_SLAVE,
    VIDEOPLAYERAPP_CONNECTION_TYPE_GPRS_SIM_SELECTION,
    VIDEOPLAYERAPP_CONNECTION_TYPE_UNKNOWN,
    VIDEOPLAYERAPP_CONNECTION_TYPE_NUM = VIDEOPLAYERAPP_CONNECTION_TYPE_UNKNOWN
} VideoPlayerAppConnectionType_e;

typedef struct
{
    IWidget *pVideoOsdWdg;
    IWidget *pBgImageWdg;
    IWidget *pTitleBarImageWdg;
    IWidget *pVolumeBtnWdg;
    IWidget *pVolumeBgImageWdg;
    IWidget *pVolumeDecreaseWdg;
    IWidget *pVolumeIncreaseWdg;
    IWidget *pVolumeIndicatorWdg;
#if !defined(__G_SENSOR_MMI__) || defined(__LCM_LANDSCAPE__)
    IWidget *pNormalToFullscreenWdg;
#endif
    IWidget *pImageWdg;
#ifdef __VIDEOPLAYERAPP_SMALLROM__
    IWidget *pAudioOnlyTextWdg;
#endif
#if defined(__MMI_BATTERY_ICON_DISPLAY__)
    IWidget *pBatteryBgWdg;
    IWidget *pBatteryWdg;
#endif
#ifndef __SLIM_MMI__
    IWidget *pVideoQualityWdg;
#endif
    IWidget *pDurationTextWdg;
    IWidget *pSlashTextWdg;
    IWidget *pDurationTotalTextWdg;
    IWidget *pInfoTextWdg;
    IWidget *pIndicatorWdg;
    IWidget *pRewindWdg;
    IWidget *pPlaybackWdg;
    IWidget *pForwardWdg;
#ifdef __MMI_STEREO_VIDEO__
    IWidget *pDepthBtnWdg;
    IWidget *pDepthBgImageWdg;
    IWidget *pDepthDecreaseWdg;
    IWidget *pDepthIncreaseWdg;
    IWidget *pDepthIndicatorWdg;
    IWidget *p2DBtnWdg;
    IWidget *p3DBtnWdg;
#endif
} VideoPlayerNormalScreenWdgList;

typedef struct
{
    VideoPlayerNormalScreenWdgList   tWdgList;
    boolean bNeedToChangeWindowSize;
} VideoPlayerNormalScreenWndData_t;

typedef struct
{
    IWidget *pVideoOsdWdg;
    IWidget *pImageWdg;
#ifdef __VIDEOPLAYERAPP_SMALLROM__
    IWidget *pAudioOnlyTextWdg;
#endif
    IWidget *pBgImageWdg;
    IWidget *pTitleBarImageWdg;
#ifndef __SLIM_MMI__
    IWidget *pVideoQualityWdg;
#endif
#if defined(__MMI_BATTERY_ICON_DISPLAY__)
    IWidget *pBatteryBgWdg;
    IWidget *pBatteryWdg;
#endif
    IWidget *pDurationTextWdg;
    IWidget *pSlashTextWdg;
    IWidget *pDurationTotalTextWdg;
    IWidget *pInfoTextWdg;
    IWidget *pIndicatorBgWdg;
    IWidget *pIndicatorWdg;
#if !defined(__G_SENSOR_MMI__) || defined(__LCM_LANDSCAPE__)
    IWidget *pBackToPanelWdg;
#endif
    IWidget *pGotoFullscreenBtnWdg;
    IWidget *pGotoRatioBtnWdg;
    IWidget *pReturnWdg;
    IWidget *pRewindWdg;
    IWidget *pStopWdg;
    IWidget *pPlaybackWdg;
    IWidget *pForwardWdg;
    IWidget *pVolumeBgImageWdg;
    IWidget *pVolumeBtnWdg;
    IWidget *pVolumeDecreaseWdg;
    IWidget *pVolumeIncreaseWdg;
    IWidget *pVolumeIndicatorWdg;
#ifdef __MMI_STEREO_VIDEO__
#ifdef __TOUCH_SCREEN_MMI__
    IWidget *pDepthBtnWdg;
    IWidget *pDepthBgImageWdg;
    IWidget *pDepthDecreaseWdg;
    IWidget *pDepthIncreaseWdg;
    IWidget *pDepthIndicatorWdg;
#endif
    IWidget *p2DBtnWdg;
    IWidget *p3DBtnWdg;
#endif
} VideoPlayerFullScreenWdgList;

typedef struct
{
    VideoPlayerFullScreenWdgList   tWdgList;
    boolean bNeedToChangeWindowSize;
    boolean bIsPanelShown;
    boolean bFitScreenRatio;
} VideoPlayerFullScreenWndData_t;

typedef struct
{
    OptionMenuWdgList_t tOptionMenuWdgList;
    OptionMenuData_t    tOptionMenuData;
} VideoPlayerOptionMenuWndData_t;

typedef struct
{
    SimSelectionWdgList_t tSimSelectionWdgList;
} VideoPlayerSIMSelectionWndData_t;

#ifdef __MMI_KING_MOVIE__
typedef struct
{
    PopUpInputWdgList_t tPopUpInputWdgList;
}VideoPlayerPasswordInputWndWdgList_t;

typedef struct
{
    VideoPlayerPasswordInputWndWdgList_t tPasswordInputWndWdgList;
    char *pPassword;
} VideoPlayerPasswordInputWndData_t;
#endif

typedef struct
{
	MAE_WChar *pName;
	MAE_WChar *pType;
	u32 nSize;
	MAE_WChar *pDate;
	MMI_Common_Location_Type_e eLocationType;
}VIDEOPLAYERAPP_DETAILS_DBINFO;

typedef struct
{
	u32 nListFileHandle;
	u32 nListFileNumber;
}VIDEOPLAYERAPP_LISTFILEINFO;

typedef struct
{
    u8 *pBuf;
    u32 nBufLen;
} VideoPlayerBufferItem_t;

/**
 * Application structure
 */
typedef struct
{
    APPLET_BASE_ELEMENTS;
    MMI_VIDEOPLAYERAPP_MODE_e eActivatedMode;
    VideoPlayerSrvDataInfo_t   tMediaFileInfo;	// the file info of the media
    u32 *pPlaylist;	// It is a pointer (array) to keep the order of playing.
    u32 nNumOfVideos;
    u32 nPlayingIndex;
    u32 nFocusIndex;
    VideoPlayerStopReason_e eStopReason;
    u8 nVolume;
    u32 nTick;
    u32 nDownloadStartTick;
    u32 nDownloadEndTick;
    u32 nDuration;
    u32 nMediaSuspendPosition; // The stop position of preempt stop action.
    MAE_WChar *pFilePath;
    MediaSrvMimeType_e eMimeType;
    boolean bHasRecvFinished;
    boolean bIsKeyLocked;
    boolean bAlreadyActivated;
//  Verifying Parameter for resume
    boolean bCloseAfterResume;
    boolean bIsNeedGetFirstFrame;
#ifdef __VIDEOPLAYERAPP_FFREWIND_SUPPORT__
    boolean bIsFFRewindProcessing;
    boolean bIsFFRewindLocked;
    VideoPlayerFFRewindAction_e eFFRewindAction;
    boolean bOk2PlayNextFlag;
    boolean bOk2PlayPreviousFlag;
#endif
    VIDEOPLAYERAPP_APP_SUSPEND_STATE eAPPSuspendState;
    VIDEOPLAYERAPP_MEDIA_SUSPEND_STATE eMediaSuspendState; // Receive StopSuccess of preempt stop.
    VIDEOPLAYERAPP_DETAILS_DBINFO *pDetailsInfo;
    boolean bNeedToCheckOrientation;
    ORIENTATION_e eCurrentOrientation;
    ORIENTATION_e eNewOrientation;
    VideoPlayerDisplayMode_e eCurrentDisplayMode;

    /* Edward Added [begin] */
    u32 nCurrDialogStrId;
    VIDEOPLAYERAPP_INFO_DIALOG_TYPE eInfoDialogType;	//Newly added 20091117 for new dialog archi.
    /* Edward Added [End] */
    // Jonathan: For keep file list result.
    //TODO:
    VIDEOPLAYERAPP_LISTFILEINFO tListFileInfo;
    u32 nClient;
    CmnLaunchAppFileOpRspCb     pfnFileOpRspCb;
    MAE_WChar *pFileDirPath;
    VFS_FileID_t    tFileId;
    u8  nCount;
    u32 nOptype;
    boolean bNeedResumeToPlay;
    //Play buffer from MMS
    VideoPlayerBufferItem_t tBufItem;
    CmnLaunchAppDataRspCb pfnResumePosRspCb;
    u32 nStartPos;
#ifdef __MMI_OMA_DRM_V1__
    boolean bShowRightsInstallResult;
#endif

    //  New Parameter
    VideoPlayerSeekMode_e eSeekMode;
    boolean bListFile;
    boolean bGetFrameBusy;
    boolean bDeleting;
    boolean bSeeking;
    boolean bBufferring;
    u16 nBufferingProg;
    boolean bRecvFileInfo;
    u8 nStatusBeforeCreateMenu;
#ifdef __MMI_STEREO_VIDEO__
    VideoPlayerImageStereoType_e eVideoStereoType;
    u32 nDepth;
    boolean bStereoEffectSupport;
    boolean bIsOpening3D;
#ifndef __TOUCH_SCREEN_MMI__
    boolean bInAdjust3DDepthMode;
#endif // !__TOUCH_SCREEN_MMI__
#endif // __MMI_STEREO_VIDEO__
    VideoPlayerSrvConnectionType_e eConnectionType;
    VideoPlayerSrvStreamingMode_e eStreamingMode;
} VideoPlayerAppData_t;

/*=============================================================*/
// Global function prototype declaration
/*=============================================================*/
MAE_Ret VideoPlayerConstructor(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean VideoPlayerStartCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean VideoPlayerStopCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean VideoPlayerSuspendCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean VideoPlayerResumeCb(IApplet *pAppet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean VideoPlayerKeyPressCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
#ifdef __VIDEOPLAYERAPP_FFREWIND_SUPPORT__
boolean VideoPlayerKeyLongPressCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
#endif
boolean VideoPlayerKeyReleaseCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean VideoPlayerTSClickCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean VideoPlayerEmbeddedAppCloseCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean VideoPlayerEmbeddedAppEvtParserCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
#ifdef __MMI_STEREO_VIDEO__
boolean _HandleKeyStarPress(VideoPlayerAppData_t *pThis);
MAE_Ret VideoPlayerDecideStereoType(VideoPlayerAppData_t *pThis, VideoPlayerImageStereoType_e *pStereoType);
#endif

//Window manager related function
MAE_Ret VideoPlayerWndNormalScreenHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret VideoPlayerWndFullScreenHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret VideoPlayerWndOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret VideoPlayerWndDetailsHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifdef __STREAMING_MODULE__
MAE_Ret VideoPlayerWndSIMSelectionHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif
#ifdef __MMI_KING_MOVIE__
MAE_Ret VideoPlayerWndPasswordInputHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif
#ifdef __STREAMING_MODULE__
void VideoPlayerWndSIMSelectionSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);
#endif
#ifdef __MMI_KING_MOVIE__
//registered callback function
void VideoPlayerPasswordInputTextChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
#endif
//============= Utility functions [begin] ================
MAE_Ret HandleForwardRewindStopTimerAndRestPanelForFullScreen(s32 MSces, PfnTimerCallbackEx pfnCallback, VideoPlayerAppData_t *pThis, void *pUserData);
//============= Utility functions [end] ================

#endif /* __MMI_VIDEOPLAYERAPP_PRIV_H__ */
