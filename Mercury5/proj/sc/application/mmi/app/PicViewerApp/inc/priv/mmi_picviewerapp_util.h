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
* @file    mmi_picviewerapp_util.h
* @version
* @brief   Picture viewer applet utility header file
*
*/

#ifndef __MMI_PICVIEWERAPP_UTIL_H__
#define __MMI_PICVIEWERAPP_UTIL_H__

/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof((a))/sizeof((a)[0]))
#endif
/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Global function prototype declaration
/*=============================================================*/
// Dialog utility
void PicViewerShowDialogById(PicViewerAppData_t *pThis, u32 nTextId);
void PicViewerShowDialogByStr(PicViewerAppData_t *pThis, MAE_WChar *pNoticeString, PFN_DlgHandler pfnTimeoutCb);
void PicViewerCloseDialog(PicViewerAppData_t *pThis);
void PicViewerShowConfirmDialog(PicViewerAppData_t *pThis, u32 nTextId);
void PicViewerShowDrmConfirmDialog(PicViewerAppData_t *pThis, u32 nTextId);

// View utility
MAE_Ret ViewWndDecode(PicViewerAppData_t *pThis);
MAE_Ret ViewWndShow(PicViewerAppData_t *pThis);
MAE_Ret ViewWndSuspend(PicViewerAppData_t *pThis);
#ifdef __MMI_STEREO_IMAGE__
void PicViewerViewWnd3DModeButtonWdgClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
#endif
#ifdef __TOUCH_SCREEN_MMI__
void PicViewerViewWndPreviousButtonWdgClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void PicViewerViewWndNextButtonWdgClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void PicViewerViewWndBackButtonWdgClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
#ifdef __MMI_PICVIEWER_SLIDESHOW_ENABLE__
void PicViewerViewWndSlideShowButtonWdgClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
#endif
void PicViewerViewWndOptionButtonWdgClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void PicViewerViewWndDeleteLSKButtonWdgClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void PicViewerViewWndBlogButtonWdgClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
#endif
void PicViewerInitDisplayQuickMenu(PicViewerAppData_t *pThis);
#ifndef __PICVIEWERAPP_SMALLROM__
void PicViewerUpdateQuickMenuItem(PicViewerAppData_t *pThis);
#endif
void PicViewerViewWndQuickMenuWdgSoftkeyCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#ifndef __PICVIEWERAPP_SMALLROM__
void PicViewerViewWndQuickMenuWdgOnFocusCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);
#endif
#if defined(__TOUCH_SCREEN_MMI__) && !defined(__PICVIEWERAPP_SMALLROM__)
void PicViewerViewWndSelectButtonWdgClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void PicViewerViewWndOkCSKButtonWdgClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
#endif
void _PicViewerSetAsWndSoftKeyActCB(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
MAE_Ret PicViewerSetAsWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#if defined(__MULTI_TOUCH__) || defined(__MULTI_TOUCH_SLIM__)
#ifdef __PICVIEWER_MULTI_FINGER__
boolean PicViewerHookDrawCb(IApplet *pApplet, u32 nDisplayId, u32 pRect, u32 bIsTopAp);
#endif
boolean PicViewerMultiViewWndImageWdgPreHookHdl(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean PicViewerMultiViewWndImageWdgHdl(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
#endif
boolean PicViewerViewWndImageWdgHdl(void *pUserData, MAE_EventId nEvt, u32 nParam1, u32 nParam2);
void PicViewerViewWndImageWdgHdlFree(void *pData);
MAE_Ret PicViewerSwitchOptionButton(PicViewerAppData_t *pThis);
void PicViewerFreeDetailsInfo(PicViewerAppData_t *pThis);
void PicViewerFreeModelData(void *pItemData, void *pUseData);
boolean PicViewerIsImageAbleToDelete(PicViewerAppData_t *pThis, u32 nUID);
MAE_Ret PicViewerDeleteImage(PicViewerAppData_t *pThis, u32 nCurrentIdx);

// Zoom utility
#ifdef __MMI_PICVIEWER_ZOOM_ENABLE__
MAE_Ret ZoomWndDecode(PicViewerAppData_t *pThis);
MAE_Ret ZoomWndShow(PicViewerAppData_t *pThis);
MAE_Ret ZoomWndSuspend(PicViewerAppData_t *pThis);
MAE_Ret ZoomWndZoomIn(PicViewerAppData_t *pThis);
MAE_Ret ZoomWndZoomOut(PicViewerAppData_t *pThis);
void PicViewerZoomWndZoomInButtonWdgClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void PicViewerZoomWndZoomOutButtonWdgClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void PicViewerZoomWndBackButtonWdgClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
boolean PicViewerZoomWndImageWdgHdl(void *pUserData, MAE_EventId nEvt, u32 nParam1, u32 nParam2);
void PicViewerZoomWndImageWdgHdlFree(void *pData);
void PicViewerZoomWndViewPortWdgScrollChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, ScrollData_t *pScrollData, IWidget *pIWidget);
void PicViewerZoomWndDecodeTimerCb(void *pData);

#ifdef __PICVIEWER_MULTI_FINGER__
void PicViewer_GetAnimateSize(WdgEasingType_t tEasingType, WidgetSize_t *pFromSize, WidgetSize_t *pEndSize, WidgetSize_t *pOutSize, u32 nCurrentFrame, u32 nTotalFrame);
void PicViewer_DumpBitmap(IBase *pThis, IBitmap *pBitmap);
void PicViewer_GetMaxScaleSize(u32 nWidth, u32 nHeight, u32 *pMaxWidth, u32 *pMaxHeight);
void PicViewer_InitZoomCenter(PicViewerAppData_t *pThis);
boolean PicViewer_IsTransit(PicViewerAppData_t *pThis, boolean bTransitLeft);
MAE_Ret PicViewer_DoScale(PicViewerAppData_t *pThis, boolean bScaleUp, float fRatio, s32 nClickCenterX, s32 nClickCenterY);
MAE_Ret PicViewer_FinishScale(PicViewerAppData_t *pThis);
boolean PicViewer_IsInsideViewport(PicViewerAppData_t *pThis, s32 x, s32 y);
MAE_Ret PicViewer_PrepareScaleBitmap(PicViewerAppData_t *pThis, PicViewerViewWndData_t *pWndData, u32 *pScaleWidth, u32 *pScaleHeight, IBitmap **ppScaleBitmap);
void PicViewer_ReleaseScaleBitmap(PicViewerAppData_t *pThis);
MAE_Ret ZoomWndScale(PicViewerAppData_t *pThis);
#endif
#endif

void PicViewerGenerateBaseRegion(PicViewerAppData_t *pThis, u32 nDisplayRegionWidth, u32 nDisplayRegionHeight, u32 *pBaseWidth, u32 *pBaseHeight);
void PicViewerGenerateBaseRegionEx(PicViewerAppData_t *pThis, u32 nDisplayRegionWidth, u32 nDisplayRegionHeight, u32 nOrigImageWidth, u32 nOrigImageHeight, u32 *pBaseWidth, u32 *pBaseHeight);
ImgDecAngle_t PicViewerGetDecodeAngle(PicViewerAppData_t *pThis);

// SlideShow utility
#ifdef __MMI_PICVIEWER_SLIDESHOW_ENABLE__
MAE_Ret SlideShowWndDecode(PicViewerAppData_t *pThis);
MAE_Ret SlideShowWndShow(PicViewerAppData_t *pThis);
MAE_Ret SlideShowWndSuspend(PicViewerAppData_t *pThis);
MAE_Ret SlideShowWndResume(PicViewerAppData_t *pThis);
#endif

// SetWallpaper utility
MAE_Ret SetWallpaperWndDecode(PicViewerAppData_t *pThis);
MAE_Ret SetWallpaperWndCropping(PicViewerAppData_t *pThis);
MAE_Ret SetWallpaperWndCroppingMove(PicViewerAppData_t *pThis);
MAE_Ret SetWallpaperWndCroppingZoom(PicViewerAppData_t *pThis);
MAE_Ret SetWallpaperWndCroppingSave(PicViewerAppData_t *pThis);
MAE_Ret SetWallpaperWndSuspend(PicViewerAppData_t *pThis);
MAE_Ret SetWallpaperWndResume(PicViewerAppData_t *pThis);
#if !defined(__NAND_MMI__) && defined(__ONBOARD_USER_STORAGE_MMI__)
MAE_Ret PicViewerChooseStorageLocationSave(PicViewerAppData_t *pThis);
#endif
void PicViewerSetWallpaperWndBackButtonWdgClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void PicViewerSetWallpaperWndSetButtonWdgClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void PicViewerSetWallpaperWndZoomSwitchButtonWdgClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void PicViewerSetWallpaperWndZoomButtonWdgClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
boolean PicViewerSetWallpaperWndContainerHdl(void *pUserData, MAE_EventId nEvt, u32 nParam1, u32 nParam2);
void PicViewerSetWallpaperWndContainerHdlFree(void *pData);
void PicViewerZoomInWallpaperCroppingZone(PicViewerAppData_t *pThis);
void PicViewerZoomOutWallpaperCroppingZone(PicViewerAppData_t *pThis);
boolean PicViewerImageCanBeCropped(PicViewerAppData_t *pThis);
boolean PicViewerCroppingZoneCanMove(PicViewerAppData_t *pThis);
boolean PicViewerCroppingZoneCanZoom(PicViewerAppData_t *pThis);
boolean PicViewerIsCroppingZoneBoundaryCorrect(PicViewerAppData_t *pThis);
boolean PicViewerIsCroppingWallpaperScreenInit(PicViewerAppData_t *pThis);
boolean PicViewerIsCroppingZoneMaxSize(PicViewerAppData_t *pThis);
MAE_Ret PicViewerSetButtonData
(
    PicViewerAppData_t *pThis,
    IWidget *pButtonWdg,
    u32 nPressedImgId,
    u32 nUnPressedImgId,
    boolean bIsDisabled
);

// OptionMenu utility
#ifdef __PICVIEWERAPP_SMALLROM__
MAE_Ret PicViewerCreateOptionWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
void PicViewerOptionWndSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif

// Common utility
void PicViewerAccessoryPlugStatusCb(void *pThis, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);
void PicViewerBacklightCb(void *pThis, boolean bBackLightOn);
void PicViewerUsbStatusCb(void *pThis, MMI_USB_STATUS_E eUsbStatus);
#if defined(__APP_MMI_CHECKDISK__)
void PicViewerCheckDiskStatusListener(char *pSbjName, SubjectStatus_e nSbjStatus, void *pUser);
#endif
#ifdef  __G_SENSOR_MMI__
void PicViewerMotionDetectorOrientationCb(void *pThis, ORIENTATION_e eResult);
void PicViewerMotionDetectorSimpleActionCb(void *pThis, SIMPLE_ACTINO_e eResult);
MAE_Ret PicViewerMotionDetectorAddCb(PicViewerAppData_t *pThis);
MAE_Ret PicViewerMotionDetectorRemoveCb(PicViewerAppData_t *pThis);
#endif  /* __G_SENSOR_MMI__ */
void PicViewerSetFocus(PicViewerAppData_t *pThis);
void PicViewerSetSelect(PicViewerAppData_t *pThis);
#ifndef __WIDGET_DISABLE_TRANSITION__
void PicViewerTransitionWdgDoneCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);
#endif
boolean PicViewerIsInSelectMode(PicViewerAppData_t *pThis);
boolean PicViewerIsInLandscapeMode(PicViewerAppData_t *pThis);
boolean PicViewerIsFromCameraMode(PicViewerAppData_t *pThis);

// Handler
MAE_Ret PicViewerDeletePictureHdl(PicViewerAppData_t *pThis);
#ifdef  __G_SENSOR_MMI__
MAE_Ret PicViewerGSensorRotateHdl(PicViewerAppData_t *pThis);
MAE_Ret PicViewerGSensorShakeHdl(PicViewerAppData_t *pThis);
#endif  /* __G_SENSOR_MMI__ */
MAE_Ret PicViewerGotoViewWndHdl(PicViewerAppData_t *pThis);
#ifdef __MMI_PICVIEWER_SLIDESHOW_ENABLE__
MAE_Ret PicViewerGotoSlideShowWndHdl(PicViewerAppData_t *pThis);
#endif
MAE_Ret PicViewerGotoSetWallpaperWndHdl(PicViewerAppData_t *pThis);

// File service utility
void PicViewerDeletedScanDoneCb(void *pUserData);
MAE_Ret PicViewerCreateFileList(PicViewerAppData_t *pThis);
MAE_Ret PicViewerCreateFileListBegin(PicViewerAppData_t *pThis, PfnMAE_Notify pfnCallback);

#ifdef __MMI_PICVIEWER_SLIDESHOW_ENABLE__
void PicViewerSlideShowImageNotify(IImage *pImage, IBase *pUser, ImgStatus_t eState);
void PicViewerSlideShow3DLoaderPrepare(PicViewerAppData_t  *pThis);
boolean PicViewerSlideShow3DLoaderMoveToCurrPage(PicViewerAppData_t  *pThis);
boolean PicViewerSlideShow3DLoaderStartAnim(PicViewerAppData_t  *pThis);
void PicViewerSlideShowExit(PicViewerAppData_t  *pThis);
#endif

#if defined(__MULTI_TOUCH__) || defined(__MULTI_TOUCH_SLIM__)
// Multi-touch utility
void PicViewerViewWndSwitchToMultiViewWnd(void *pUserData);
void PicViewerMultiViewWndSwitchToViewWnd(void *pUserData);
#endif

#ifdef __MMI_STEREO_IMAGE__
MAE_Ret PicViewerUpdateStereoMenuItem(PicViewerAppData_t *pThis);
#endif

#if !defined(__NAND_MMI__) && defined(__MMI_STEREO_IMAGE__)
MAE_Ret PicViewerMemorySubjectRequest(PicViewerAppData_t *pThis);
void PicViewerMemorySubjectRelease(PicViewerAppData_t *pThis);
#endif

#endif /* __MMI_PICVIEWERAPP_UTIL_H__ */
