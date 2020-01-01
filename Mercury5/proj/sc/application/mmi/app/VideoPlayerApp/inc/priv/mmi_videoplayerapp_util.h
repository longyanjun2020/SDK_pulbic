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
* @file    mmi_videoplayerapp_util.h
* @version
* @brief   Video player applet utility header file
*
*/

#ifndef __MMI_VIDEOPLAYERAPP_UTIL_H__
#define __MMI_VIDEOPLAYERAPP_UTIL_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_wdg_headers.h"
MAE_Ret VideoPlayerCfgSetItem(VideoPlayerAppData_t *pThis, CFGItemID_e eId, void *pItemBuffer, u32 nBufferSize);
MAE_Ret VideoPlayerCfgGetItem(VideoPlayerAppData_t *pThis, CFGItemID_e eId, void *pItemBuffer, u32 nBufferSize);
void VideoPlayerOptionMenuSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void VideoPlayerOptionMenuSoftKeyCancelCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#ifdef __TOUCH_SCREEN_MMI__
static void _VideoPlayerFullScreenBtnGotoFullscreenCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
static void _VideoPlayerFullScreenBtnGotoRatioCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
static void _VideoPlayerFullScreenBtnReturnCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
#if !defined(__G_SENSOR_MMI__) || defined(__LCM_LANDSCAPE__)
static void _VideoPlayerFullScreenBtnToNomalScreenCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
static void _VideoPlayerNormalScreenBtnToFullScreenCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
#endif
static void _VideoPlayerVolumeBtnCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode,u32 dwParam,IWidget * pWidget);
static void _VideoPlayerIncreaseVolumeBtnCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
static void _VideoPlayerDecreaseVolumeBtnCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
#ifdef __MMI_STEREO_VIDEO__
static void _VideoPlayer3DModeBtnCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode,u32 dwParam,IWidget * pWidget);
static void _VideoPlayer2DModeBtnCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode,u32 dwParam,IWidget * pWidget);
static void _VideoPlayerDepthBtnCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode,u32 dwParam,IWidget * pWidget);
static void _VideoPlayerIncreaseDepthBtnCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode,u32 dwParam,IWidget * pWidget);
static void _VideoPlayerDecreaseDepthBtnCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode,u32 dwParam,IWidget * pWidget);
void VideoPlayerDepthIndicatorTouchCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, s32 nNewPos, IWidget *pWidget);
#endif  //__MMI_STEREO_VIDEO__
static void _VideoPlayerPlaybackBtnCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
static void _VideoPlayerStopBtnCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
static void _VideoPlayerIndicatorPressOrMoveFunc(VideoPlayerAppData_t *pThis, s32 nNewPos);
static void _VideoPlayerIndicatorPressCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, s32 nNewPos, IWidget *pWidget);
static void _VideoPlayerIndicatorReleaseCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, s32 nNewPos, IWidget *pWidget);
static void _VideoPlayerIndicatorMoveCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, s32 nNewPos, IWidget *pWidget);
void VideoPlayerVolumeIndicatorTouchCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, s32 nNewPos, IWidget *pWidget);
static MAE_Ret _VideoPlayerRegisterIndicatorWdgCb(VideoPlayerAppData_t *pThis);
static MAE_Ret _VideoPlayerDeregisterIndicatorWdgCb(VideoPlayerAppData_t *pThis);
static MAE_Ret _VideoPlayerRegisterBtnCB4RewindOrFastForward(IWidget *pIWidget, boolean bFastForwardFlag);
static MAE_Ret _VideoPlayerDeregisterBtnCB4RewindOrFastForward(IWidget *pIWidget, boolean bFastForwardFlag);
static void _VideoPlayerRewindBtnClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
#ifdef __VIDEOPLAYERAPP_FFREWIND_SUPPORT__
static void _VideoPlayerRewindBtnValidCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bValid,IWidget *pWidget);
static void _VideoPlayerRewindBtnInvalidCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bValid,IWidget *pWidget);
#endif
static void _VideoPlayerRewindBtnClickOrInvalidFunc(VideoPlayerAppData_t *pThis, u32 nEvtCode);
static void _VideoPlayerFastForwardBtnClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
#ifdef __VIDEOPLAYERAPP_FFREWIND_SUPPORT__
static void _VideoPlayerFastForwardBtnValidCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bValid,IWidget *pWidget);
static void _VideoPlayerFastForwardBtnInvalidCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bValid,IWidget *pWidget);
#endif
static void _VideoPlayerFastForwardBtnClickOrInvalidFunc(VideoPlayerAppData_t *pThis, u32 nEvtCode);
#endif // __TOUCH_SCREEN_MMI__

#if defined(__MMI_STEREO_VIDEO__)
void VideoPlayerOptionMenuReqLayer2Cb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _VideoPlayerUpdateStereoEffectIcon(void *pApplet, MAE_WndId nId);
void _VideoPlayerUpdateStereoMode(void *pApplet, MediaSrvErrCode_e nErrorCode, void *pInfoData);
void _VideoPlayerSetStereoTypeCb(void *pThis, u32 nCusData, VideoPlayerSrvSetConfigInfo_t *pRspInfo);
void _VideoPlayerSetDepthCb(void *pThis, u32 nCusData, VideoPlayerSrvSetConfigInfo_t *pRspInfo);
VideoPlayerImageStereoType_e _VideoPlayerSwitch2D3DMode(VideoPlayerImageStereoType_e eCurrStero);
void _VideoPlayerDepthBarSetVisible(VideoPlayerAppData_t *pThis, boolean bVisible);
static void _VideoPlayerDepthBarSetInvisible(void * pUser);
MAE_Ret _VideoPlayerUpdateDepthIcon(VideoPlayerAppData_t *pThis);
MAE_Ret _VideoPlayerUpdateDepthIndicator(VideoPlayerAppData_t *pThis);
#ifndef __TOUCH_SCREEN_MMI__
boolean VideoPlayerDepthIncrease(VideoPlayerAppData_t *pThis);
boolean VideoPlayerDepthDecrease(VideoPlayerAppData_t *pThis);
MAE_Ret VideoPlayerCreateAdjustDepthScene(VideoPlayerAppData_t *pThis);
MAE_Ret VideoPlayerDestroyAdjustDepthScene(VideoPlayerAppData_t *pThis);
#endif  // !__TOUCH_SCREEN_MMI__
#endif  // __MMI_STEREO_VIDEO__

#if defined(__MMI_BATTERY_ICON_DISPLAY__)
void _VideoPlayerBattLevelChangeCb(void *pUserData, MAEBatteryLevel_e eLevel, MAEBatteryID_e eBatID);
void _VideoPlayerExtPwrChangeCb(void *pUserData, boolean bChargerPlugged);
#ifdef __DUAL_BATT_MMI__
void _VideoPlayerCurrBattChangeCb(void *pUserData, MAEBatteryID_e eBatID);
#endif
MAE_Ret _VideoPlayerUpdateBatteryIcon(VideoPlayerAppData_t *pThis);
#endif

MAE_Ret _VideoPlayerInit(VideoPlayerAppData_t *pThis);
void _VideoPlayerRelease(VideoPlayerAppData_t *pThis);
void _VideoPlayerShowNotice(VideoPlayerAppData_t *pThis, u32 nTextId, VideoPlayerDisplayMode_e eDisplayMode);

#ifdef __MMI_OMA_DRM_V1__
static void _VideoPlayerShowDrmConfirmDialog(VideoPlayerAppData_t *pThis, u32 nTextId);
static boolean _DrmRightsInvalidConfirmDialogCb(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
static void _LaunchCdWapDownloadDrmRightsFileCb(void *pvUserData, MAE_Ret nRspCode, void *pvRspData, CmnRspDataFreeCb pfnRspFreeCb);
#endif
static boolean _ShowNoticeInfoDialogCallback(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
static boolean _DeleteFileConfirmDialogCallback(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
static boolean _HandleKeyPressDeleteFileConfirmDialog(VideoPlayerAppData_t *pThis, u32 nParam);
static void _HandleSKRightPressDeleteFileConfirmDialog(VideoPlayerAppData_t *pThis);

void _VideoPlayerWarningTimeoutCb(void *pData);
void _VideoPlayerFreeDetailsInfo(VIDEOPLAYERAPP_DETAILS_DBINFO *pDetailsInfo);

MAE_Ret _VideoPlayerGetVideoFileInfo(VideoPlayerAppData_t *pThis, u32 nIndex);
void _VideoPlayerShowConfirmDialog(VideoPlayerAppData_t *pThis, u32 nTextId);
#ifdef __MMI_KING_MOVIE__
MAE_Ret VideoPlayerPasswordListFullDialogCallback(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret VideoPlayerSavePasswordDialogCallback(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
#endif
MAE_Ret _VideoPlayerDeleteTheVideo(VideoPlayerAppData_t *pThis, MAE_WChar *pFileUrl);
void _VideoPlayerDoneTimeoutCb(void *pData);
MAE_Ret VideoPlayerCreateNormalScreen(void *pCusHandle, void *pWndData, u32 nWndInitParam);
void _VideoPlayerReleaseNormalPanel(VideoPlayerAppData_t *pThis);

MAE_Ret _VideoPlayerUpdatePlaybackButton(VideoPlayerAppData_t *pThis);
MAE_Ret _VideoPlayerUpdateDurationText(VideoPlayerAppData_t *pThis);
MAE_Ret _VideoPlayerUpdateDurationTotalText(VideoPlayerAppData_t *pThis);
void _VideoPlayerVolumeBarSetVisible(VideoPlayerAppData_t *pThis, boolean bVisible);
void _VideoPlayerUpdateVolume(VideoPlayerAppData_t *pThis);
boolean VideoPlayerVolumeIncrease(VideoPlayerAppData_t *pThis);
boolean VideoPlayerVolumeDecrease(VideoPlayerAppData_t *pThis);
MAE_Ret _VideoPlayerHandleNormalPanelOptionMenuSelect(VideoPlayerAppData_t *pThis, u32 nSelectedID);
MAE_Ret _VideoPlayerDecideNormalModeVideoRegion(Rect_t *pRegion);
MAE_Ret _VideoPlayerDecideFullscreenModeVideoRegion(Rect_t *pRegion);
MAE_Ret _VideoPlayerGeneratePlayListOrder(VideoPlayerAppData_t *pThis);
void _VideoPlayerSetPlayNext(VideoPlayerAppData_t *pThis);
void _VideoPlayerSetPlayPrevious(VideoPlayerAppData_t *pThis);
MAE_Ret _VideoPlayerGetVideoInfo(VideoPlayerAppData_t *pThis, u32 nIndex);

void _VideoPlayerReleaseFullscreen(VideoPlayerAppData_t *pThis);
MAE_Ret VideoPlayerCreateFullScreen(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _VideoPlayerSetNormalWindowSize(VideoPlayerAppData_t *pThis);
MAE_Ret _VideoPlayerSetFullscreenWindowSize(VideoPlayerAppData_t *pThis, boolean bFitScreenRatio);
MAE_Ret _VideoPlayerHandleKeyAction(VideoPlayerAppData_t *pThis, VideoPlayerDisplayMode_e eDisplayMode);
MAE_Ret _VideoPlayerHandleKeyStop(VideoPlayerAppData_t *pThis);
MAE_Ret _VideoPlayerUpdateFirstFrame(VideoPlayerAppData_t *pThis, VideoPlayerDisplayMode_e eDisplayMode, IBitmap *pIBitmap);
MAE_Ret _VideoPlayerUpdateAudioOnlyGIF(VideoPlayerAppData_t *pThis, VideoPlayerDisplayMode_e eDisplayMode);
MAE_Ret _VideoPlayerGetVideoFirstFrame(VideoPlayerAppData_t *pThis, VideoPlayerDisplayMode_e eDisplayMode);

MAE_Ret _VideoPlayerPlayVideo(VideoPlayerAppData_t *pThis, u32 nPosition, VideoPlayerDisplayMode_e eMode);
MAE_Ret _VideoPlayerUpdateProgressBar(VideoPlayerAppData_t *pThis);
#ifdef __VIDEOPLAYERAPP_FFREWIND_SUPPORT__
MAE_Ret _VideoPlayerFFRewindStart(VideoPlayerAppData_t *pThis, VideoPlayerFFRewindAction_e eFFRewindAction);
MAE_Ret _VideoPlayerFFRewindStop(VideoPlayerAppData_t *pThis, VideoPlayerFFRewindAction_e eFFRewindAction);
#endif
MAE_Ret _VideoPlayerStopVideo(VideoPlayerAppData_t *pThis);
MAE_Ret _VideoPlayerGetFileInfo(VideoPlayerAppData_t *pThis);
MAE_Ret _VideoPlayerPauseVideo(VideoPlayerAppData_t *pThis);
MAE_Ret _VideoPlayerEvtAppSuspendVideo(VideoPlayerAppData_t *pThis);
MAE_Ret _VideoPlayerResumeVideo(VideoPlayerAppData_t *pThis, boolean bResume);
MAE_Ret _VideoPlayerResumeFromSuspend(VideoPlayerAppData_t *pThis);

MAE_Ret _VideoPlayerSeekVideo(VideoPlayerAppData_t *pThis, u32 nSetPosition);
void _VideoPlayerStartAudioTrackOnlyGIF(VideoPlayerAppData_t *pThis);
void _VideoPlayerStopAudioTrackOnlyGIF(VideoPlayerAppData_t *pThis);
MAE_Ret _VideoPlayerLaunchSendVia(VideoPlayerAppData_t *pThis);

#ifdef __VIDEOPLAYERAPP_FFREWIND_SUPPORT__
void _VideoPlayerTimeoutFFRewindStartCb(void *pUser, void *pUserData);
void _VideoPlayerTimeoutFFRewindStopCb(void *pUser, void *pUserData);
#endif
void _VideoPlayerHideFullScreenPanel(VideoPlayerAppData_t *pThis);
void _VideoPlayerShowFullScreenPanel(VideoPlayerAppData_t *pThis);
void _VideoPlayerFullScreenHidePanelTimeoutCb(void *data);
void _VideoPlayerResetPanelHideTimerIfinFullscreen(VideoPlayerAppData_t *pThis);

#ifndef __SLIM_MMI__
MAE_Ret _VideoPlayerUpdateQualityIcon(VideoPlayerAppData_t *pThis);
#endif

boolean _VideoPlayerIsCurrentVideoAudioTrackOnly(VideoPlayerAppData_t *pThis);

#ifdef __VIDEOPLAYERAPP_FFREWIND_SUPPORT__
#ifdef __TOUCH_SCREEN_MMI__
static void _VideoPlayerStartFastForward(VideoPlayerAppData_t *pThis, u32 nKeyCode);
static void _VideoPlayerStopFastForward(VideoPlayerAppData_t *pThis, u32 nKeyCode);
static void _VideoPlayerStopRewind(VideoPlayerAppData_t *pThis, u32 nKeuCode);
static void _VideoPlayerStartRewind(VideoPlayerAppData_t *pThis, u32 nKeyCode);
#endif // __TOUCH_SCREEN_MMI__
#endif //__VIDEOPLAYERAPP_FFREWIND_SUPPORT__
static MAE_Ret _VideoPlayerStopSuccessNormalScreenStopByPick(VideoPlayerAppData_t *pThis);

MAE_Ret VideoPlayerGoToPanelMode(VideoPlayerAppData_t *pThis);
MAE_Ret VideoPlayerGoToFullScreenMode(VideoPlayerAppData_t *pThis);

static MAE_Ret _VideoPlayerHandleNormalPanelOptionMenuSelectFuncGoToPanelMode(VideoPlayerAppData_t *pThis, u32 nSelectId);
#if !defined(__G_SENSOR_MMI__) || defined(__LCM_LANDSCAPE__)
static MAE_Ret _VideoPlayerHandleNormalPanelOptionMenuSelectFuncGoToFullscreenMode(VideoPlayerAppData_t *pThis, u32 nSelectId);
#endif
static MAE_Ret _VideoPlayerHandleNormalPanelOptionMenuSelectFuncGoToLaunchAP(VideoPlayerAppData_t *pThis, u32 nSelectId);
static MAE_Ret _VideoPlayerHandleNormalPanelOptionMenuSelectFuncGoToDeleteMode(VideoPlayerAppData_t *pThis, u32 nSelectId);
static MAE_Ret _VideoPlayerHandleNormalPanelOptionMenuSelectFuncGoToDetailsMode(VideoPlayerAppData_t *pThis, u32 nSelectId);
#ifdef __MMI_STEREO_VIDEO__
static MAE_Ret _VideoPlayerHandleNormalPanelOptionMenuSelectFuncSwitch2D3DEffectMode(VideoPlayerAppData_t *pThis, u32 nSelectId);
#ifndef __TOUCH_SCREEN_MMI__
static MAE_Ret _VideoPlayerHandleNormalPanelOptionMenuSelectFuncAdjustDepthMode(VideoPlayerAppData_t *pThis, u32 nSelectId);
#endif // !__TOUCH_SCREEN_MMI__
#endif // __MMI_STEREO_VIDEO__

static MAE_Ret _VideoPlayerResumeFromSuspendEvtHandleNormalScreen(VideoPlayerAppData_t *pThis, u32 nEventId);

static MAE_Ret _VideoPlayerNormalScreenPlayFinishedSimpleMode(VideoPlayerAppData_t *pThis);
static MAE_Ret _VideoPlayerNormalScreenPlayFinishedGeneralMode(VideoPlayerAppData_t *pThis);
static MAE_Ret _VideoPlayerNormalScreenPlayFinishedCamcorderMode(VideoPlayerAppData_t *pThis);

static MAE_Ret _VideoPlayerResumeFromSuspendEvtHandleFullScreen(VideoPlayerAppData_t *pThis, u32 nEventId);

static MAE_Ret _VideoPlayerResumeFromSuspendEvtHandleOptionMenu(VideoPlayerAppData_t *pThis, u32 nEventId);

static MAE_Ret _VideoPlayerResumeFromSuspendEvtHandleDetails(VideoPlayerAppData_t *pThis, u32 nEventId);

static boolean _VideoPlayerIsMediaSuspending(VideoPlayerAppData_t *pThis, MAE_WndId nWndId);
static boolean _VideoPlayerIsAppSuspending(VideoPlayerAppData_t *pThis, MAE_WndId nWndId);

MAE_Ret VideoPlayerPlayFinished(VideoPlayerAppData_t *pThis);

void _VideoPlayerDeleteOperation(VideoPlayerAppData_t *pThis);
void _VideoPlayerUpdateDurTextProgressBar(VideoPlayerAppData_t *pThis);
MAE_Ret _VideoPlayerUpdateDurTextProgressBarPlaybackButton(VideoPlayerAppData_t *pThis, boolean bNeedUpdateScreen);

static boolean _VideoPlayerPlayNextConditionCheck(VideoPlayerAppData_t *pThis, u32 nKeyCode, VideoPlayerPlayAction_e ePlayAct);
static void _VideoPlayerPlayNext(VideoPlayerAppData_t *pThis);
void VideoPlayerPlayNext(VideoPlayerAppData_t *pThis, u32 nKeyCode, VideoPlayerPlayAction_e ePlayAct);
boolean VideoPlayerStopApp(VideoPlayerAppData_t *pThis);

static boolean _VideoPlayerPlayPreviousConditionCheck(VideoPlayerAppData_t *pThis, u32 nKeyCode, VideoPlayerPlayAction_e ePlayAct);
static void _VideoPlayerPlayPrevious(VideoPlayerAppData_t *pThis);
void VideoPlayerPlayPrevious(VideoPlayerAppData_t *pThis, u32 nKeyCode, VideoPlayerPlayAction_e ePlayAct);

MAE_Ret VideoPlayerGetFileFramework(VideoPlayerAppData_t *pThis, u32 nFocusIndex);

static void  _HandleGetFirstFrameInfoFileFormatNotSupport(VideoPlayerAppData_t *pThis);
void HandlePlayPauseStopFailed(VideoPlayerAppData_t *pThis, MAE_Ret nErrCode);

static MAE_Ret _VideoPlayerStartDeleting(VideoPlayerAppData_t *pThis);
void _VideoPlayerShowWaitingDialog(VideoPlayerAppData_t *pThis, u32 nTextId, VideoPlayerDisplayMode_e eDisplayMode, SoftkeyID_e eLsk, SoftkeyID_e eCsk, SoftkeyID_e eRsk, PFN_DlgHandler pfnDialogHdlCB);

static void _VideoPlayerGetFirstFrameSuccess(VideoPlayerAppData_t *pThis, IBitmap *pIBitmap);

static void _VideoPlayerGetFileInfoCnf(VideoPlayerAppData_t *pThis);
static void _VideoPlayerGetFileInfoCnfForPlay(VideoPlayerAppData_t *pThis);
static void _VideoPlayerGetFileInfoCnfForGetFirstFrame(VideoPlayerAppData_t *pThis);

static void _VideoPlayerSetPlayingWindowSuccessFailed(VideoPlayerAppData_t *pThis);
#ifdef __MMI_KING_MOVIE__
static void _VideoPlayerHandlePasswordMismatch(VideoPlayerAppData_t *pThis);
#endif
static void _VideoPlayerSetPlayingSpeedSuccess(VideoPlayerAppData_t *pThis);

static void _VideoPlayerPlaySuccess(VideoPlayerAppData_t *pThis);
static void _VideoPlayerSuspendInd(VideoPlayerAppData_t *pThis);
static void _VideoPlayerResumeInd(VideoPlayerAppData_t *pThis);

MAE_Ret VideoPlayerPauseSuccess(VideoPlayerAppData_t *pThis);

static MAE_Ret _VideoPlayerStopSuccessStopByOption(VideoPlayerAppData_t *pThis);
static MAE_Ret _VideoPlayerStopSuccessStopByUser(VideoPlayerAppData_t *pThis);
static MAE_Ret _VideoPlayerStopSuccessStopByRSK(VideoPlayerAppData_t *pThis);

MAE_Ret _VideoPlayerStopSuccess(VideoPlayerAppData_t *pThis);

static MAE_Ret _VideoPlayerStopFailed(VideoPlayerAppData_t *pThis);
static MAE_Ret _VideoPlayerStopSuccessFailedStopByApp(VideoPlayerAppData_t *pThis);
static MAE_Ret _VideoPlayerStopSuccessFailedStopByMediaSuspend(VideoPlayerAppData_t *pThis);
static MAE_Ret _VideoPlayerStopSuccessFailedStopBySetPosFailed(VideoPlayerAppData_t *pThis);

static MAE_Ret _VideoPlayerSetPosSuccessFailed(VideoPlayerAppData_t *pThis, boolean bSuccess);

void HandleGsensorOrientationChange(VideoPlayerAppData_t *pThis);
static void _HandleGsensorOrintationChangeNormalScreen(VideoPlayerAppData_t *pThis);
static void _HandleGsensorOrintationChangeFullScreen(VideoPlayerAppData_t *pThis);
#if defined(__G_SENSOR_MMI__) && !defined(__LCM_LANDSCAPE__)
void _VideoPlayerMotionDetectorOrientationCb(void *pUserData, ORIENTATION_e eResult);
#endif
void VideoPlayerStartWnd(VideoPlayerAppData_t *pThis);
MAE_Ret VideoPlayerCreateFileList(VideoPlayerAppData_t *pThis, MAE_WChar *pDirPath);
void _VideoPlayerTurnOnBackLight(void *pApplet, boolean bAlwaysOn, boolean bIsDefaultLevel, boolean bIsKeypadLightAutoOff);
void _VideoPlayerTurnOffBackLight(void);

u8 VideoPlayerGetCurrStatus(VideoPlayerAppData_t *pThis);

#ifdef __TOUCH_SCREEN_MMI__
boolean _VideoPlayerIndicatorIsTouch(VideoPlayerAppData_t *pThis);
MAE_Ret VideoPlayerDisableSeekIndicatorTouchEvent(VideoPlayerAppData_t *pThis, boolean bDisable);
#endif

MAE_Ret _VideoPlayerUpdateSeekOnOff(VideoPlayerAppData_t *pThis);

void VideoPlayerCloseProcess(VideoPlayerAppData_t *pThis);

boolean VideoPlayerIsKeyLock(VideoPlayerAppData_t *pThis);
void _VideoPlayerUpdateInfoText(VideoPlayerAppData_t *pThis);
boolean VideoPlayerGetSeekable(VideoPlayerAppData_t *pThis);

boolean VideoPlayerIsLandscapeMode(VideoPlayerAppData_t *pThis);
boolean VideoPlayerIsPreviewMode(VideoPlayerAppData_t *pThis);
boolean VideoPlayerIsPickMode(VideoPlayerAppData_t *pThis);
boolean VideoPlayerIsCamcorderMode(VideoPlayerAppData_t *pThis);
boolean VideoPlayerIsSimpleMode(VideoPlayerAppData_t *pThis);
boolean VideoPlayerIsSimpleBufferMode(VideoPlayerAppData_t *pThis);
boolean VideoPlayerIsSimpleStreamingMode(VideoPlayerAppData_t *pThis);

MAE_Ret VideoPlayerIsSuspend(VideoPlayerAppData_t *pThis, boolean *pIsSuspend);
#ifdef __STREAMING_MODULE__
MAE_Ret VideoPlayerJudgeConnectionType(VideoPlayerAppConnectionType_e *pConnectionType);
#endif

#endif  //  __MMI_VIDEOPLAYERAPP_UTIL_H__
