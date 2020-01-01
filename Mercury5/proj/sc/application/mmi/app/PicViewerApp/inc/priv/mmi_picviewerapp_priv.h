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
* @file    mmi_picviewerapp_priv.h
* @version
* @brief   Picture viewer applet private header file
*
*/

#ifndef __MMI_PICVIEWERAPP_PRIV_H__
#define __MMI_PICVIEWERAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mae_glwidget_common.h"

#include "mmi_baseapplet.h"
#include "mmi_picviewerapp.h"
#include "mmi_picviewerapp_custom.h"
#include "mmi_picviewerview_id.h"

#include "mmi_common_dialog_id.h"
#if !defined(__NAND_MMI__) && defined(__ONBOARD_USER_STORAGE_MMI__)
#include "mmi_common_window.h"
#endif
#include "mmi_common_mimetype.h"
#include "mmi_common_vtm.h"
#include "mmi_picviewerapp_id.h"
#include "picviewerapp_resource.h"

// Launcher
#include "mmi_launcher_common.h"
#include "mmi_launcher_picviewer.h"
#include "mmi_launcher_sendvia.h"

#include "mmi_srv_header.h"
#include "mmi_phbapp.h"
#include "mmi_event.h"

#include "mmi_wdg_3dloader.h"
#include "mmi_mae_image.h"
#if defined(__3D_UI_PICVIWER_SLIDESHOW__)
#include "mgl_egl.h"
#include "mmi_common_display.h"
#endif
#if defined(__MULTI_TOUCH__) || defined(__MULTI_TOUCH_SLIM__)
#include "mmi_mae_porting.h"
#endif
/*=============================================================*/
// Macro definition
/*=============================================================*/
#define NORMAL_DISPLAY_WIDTH	MAIN_LCD_WIDTH
#define NORMAL_DISPLAY_HEIGHT	MAIN_LCD_HEIGHT

#define MAX_RESOLUTION_WIDTH	0xFFFFFFFF
#define MAX_RESOLUTION_HEIGHT	0xFFFFFFFF
#define MAX_RESOLUTION_LENGTH	23  // For example: 9999 x 9999
#define CROPPING_ZONE_ONE_MOVE_H_PIXELS  8  //(MAIN_DEFVIEW_WIDTH / 40)
#define CROPPING_ZONE_ONE_MOVE_V_PIXELS  8
#define ZOOM_MOVING_OFFSET_UNSET 0xFFFFFFFF

#define SLIDE_SHOW_3D_TOTAL_IMAGE 6
#define SLIDE_SHOW_SINGLE_KF_BG_WIDTH_HEIGHT 256
#if defined(__MULTI_TOUCH__) || defined(__MULTI_TOUCH_SLIM__)
#define FULL_DECODE_MEMORY_LIMIT	(1 * 1024 * 1024)	// 1MB
#define FULL_DECODE_MEMORY_USAGE(nWidth, nHeight)	(((nWidth*g_nMainLcdBPP+7)>>3)*nHeight)
#endif
#define PICVIEWER_APBGCOLOR RGBCOLOR_BLACK

#if defined(__MULTI_TOUCH__)
//#define __PICVIEWER_MULTI_FINGER__
#endif

#ifdef __PICVIEWER_MULTI_FINGER__
#include "mmi_mae_util_easing.h"

#define PICVIEWER_MULTI_FINGER_EASING       LINEAR_EASE_OUT
#define PICVIEWER_MULTI_FINGER_SCALE_STEP   8
#define FULL_DECODE_SCALE_MEMORY_LIMIT	(1 * 1024 * 1024)	// 2MB
#define FULL_DECODE_SCALE_MEMORY_USAGE(nWidth, nHeight)	(((nWidth*g_nMainLcdBPP+7)>>3)*nHeight)
#endif

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    PICVIEWER_TRANSITION_NONE,
    PICVIEWER_TRANSITION_LEFT,
    PICVIEWER_TRANSITION_RIGHT,
    PICVIEWER_TRANSITION_GROTATE,
    PICVIEWER_TRANSITION_ENTER_APP
} PicViewerTransitionType_e;

typedef enum
{
    PICVIEWER_LAUNCH_AP_PHONEBOOK,
    PICVIEWER_LAUNCH_AP_SENDVIA
} PicViewerLaunchAp_e;

#ifdef __MMI_PICVIEWER_ZOOM_ENABLE__
typedef enum
{
    PICVIEWER_ZOOM_1X = 0,
    PICVIEWER_ZOOM_1_25X,
    PICVIEWER_ZOOM_1_50X,
    PICVIEWER_ZOOM_2X,
    PICVIEWER_ZOOM_3X,
    PICVIEWER_ZOOM_4X,
    PICVIEWER_ZOOM_8X,
    PICVIEWER_ZOOM_16X,
    PICVIEWER_ZOOM_32X,
    NUM_OF_ZOOM_TYPE,
    PICVIEWER_ZOOM_MAX
} PicViewerZoomType_e;
#endif

typedef enum
{
    PICVIEWERAPP_RET_SUCCESS = (CLSID_PICVIEWERAPP << 16) | 0x70,
    PICVIEWERAPP_RET_NOMEM,
    PICVIEWERAPP_RET_PIC_TOO_LARGE,
    PICVIEWERAPP_RET_NOT_ENOUGH_SPACE,
    PICVIEWERAPP_RET_DEF_WPAPER_FOLDER_NOT_EXIST,
    PICVIEWERAPP_RET_FORMAT_NOT_SUPPORT,
    PICVIEWERAPP_RET_MAX
} PicViewerReturnCode_e;

typedef enum
{
    PICVIEWER_FILELIST_SORTING,
    PICVIEWER_FILELIST_SCANNING,
    PICVIEWER_FILELIST_DONE,
    PICVIEWER_FILELIST_FAILED
} PicViewerFileListState_e;

typedef enum
{
    PICVIEWER_SUBMODE_VIEW_DECODE,
    PICVIEWER_SUBMODE_VIEW_SHOW,
    PICVIEWER_SUBMODE_VIEW_SUSPEND,
    PICVIEWER_SUBMODE_VIEW_DELETE_CONFIRM,
    PICVIEWER_SUBMODE_VIEW_DELETE_DELETING,
    PICVIEWER_SUBMODE_VIEW_LAUNCHAP,
#ifdef __MMI_PICVIEWER_ZOOM_ENABLE__
    PICVIEWER_SUBMODE_ZOOM_DECODE,
    PICVIEWER_SUBMODE_ZOOM_SHOW,
    PICVIEWER_SUBMODE_ZOOM_SUSPEND,
#endif
#ifdef __MMI_PICVIEWER_SLIDESHOW_ENABLE__
    PICVIEWER_SUBMODE_SLIDESHOW_DECODE,
    PICVIEWER_SUBMODE_SLIDESHOW_SHOW,
    PICVIEWER_SUBMODE_SLIDESHOW_SUSPEND,
#endif
    PICVIEWER_SUBMODE_SETWALLPAPER_DECODE,
    PICVIEWER_SUBMODE_SETWALLPAPER_SAVE,
    PICVIEWER_SUBMODE_SETWALLPAPER_ZOOM,
    PICVIEWER_SUBMODE_SETWALLPAPER_MOVE,
    PICVIEWER_SUBMODE_SETWALLPAPER_SUSPEND,
#if !defined(__NAND_MMI__) && defined(__ONBOARD_USER_STORAGE_MMI__)
    PICVIEWER_SUBMODE_SETWALLPAPER_SAVING,
#endif
    PICVIEWER_SUBMODE_3DSLIDESHOW_SHOW
} PicViewerSubMode_e;

typedef enum
{
    PICVIEWER_ENTRYMODE_DECODE,
	PICVIEWER_ENTRYMODE_SHOW
} PicViewerEntryMode_e;

typedef struct
{
#ifndef __WIDGET_DISABLE_TRANSITION__
    IWidget *pDummyWdg;
    IWidget *pTransitionWdg;
#endif
    IWidget *pImageWdg;
#if defined(__MULTI_TOUCH__) || defined(__MULTI_TOUCH_SLIM__)
	IWidget *pImageAbsContainerWdg;
	IWidget *pViewportWdg;
#endif
#ifndef __PICVIEWERAPP_SMALLROM__
    IWidget *pActionBarBgImageWdg;
    IWidget *pPreviousButtonWdg;
    IWidget *pNextButtonWdg;
#ifdef __MMI_PICVIEWER_SLIDESHOW_ENABLE__
    IWidget *pSlideShowButtonWdg;
#endif
    IWidget *pBackButtonWdg;
    IWidget *pDeleteLSKButtonWdg;
    IWidget *pOptionButtonWdg;
    IWidget *pOkButtonWdg;
    IWidget *pBlogButtonWdg;
#endif
    IWidget *pPicIdxTextWdg;
#ifndef __PICVIEWERAPP_SMALLROM__
    IWidget *pMenuWdg;
    IWidget *pSelectButtonWdg;
#endif
#ifdef __MMI_STEREO_IMAGE__
    IWidget *p3DBtnWdg;
#endif
} PicViewerDisplayViewWdgList_t;

#ifdef __PICVIEWER_MULTI_FINGER__
typedef struct
{
    s32 PosX;
    s32 PosY;
    u8 nPointId;
    boolean bValid;
} PicViewerPoint_t;

typedef struct
{
    u8 nFinger;
    PicViewerPoint_t tPoint[MAE_TS_MAX_TOUCH];
} PicViewerFinger_t;
#endif

typedef struct
{
    u32                     nFocusIdx;
    boolean                 bIsFirstQuickMenuEntryFlag;
    WidgetHandler_t         tImageWdgHandler;
    PicViewerDisplayViewWdgList_t   tWdgList;
#if defined(__MULTI_TOUCH__) || defined(__MULTI_TOUCH_SLIM__)	// from PicViewerZoomWndData_t
	boolean bIsInterfaceModelSet;
    u32 nViewPortOffsetX;
    u32 nViewPortOffsetY;
    u32 nViewPortWidth;
    u32 nViewPortHeight;
    u32 nMovingOffsetX;
    u32 nMovingOffsetY;
    u32 nBaseWidth;
    u32 nBaseHeight;
    u32 nDisplayX;
    u32 nDisplayY;
    u32 nDisplayWidth;
    u32 nDisplayHeight;
    u32 nNewContainerWidth;
    u32 nNewContainerHeight;
    boolean bIgnoredViewPortChange;
    boolean bIsDecoding;
    boolean bIsMultiViewWnd;
#ifdef __PICVIEWER_MULTI_FINGER__
    u32 nClickCenterX;
    u32 nClickCenterY;
    u32 nPrevClickCenterX;
    u32 nPrevClickCenterY;
    float fKeepScaleRatio;
    boolean bScaling;
    boolean bNeedRestore;
    Rect_t tSrcRc;
    Rect_t tDstRc;
    IBitmap *pScaleBmp;
    float fScaleRatio;

    PicViewerFinger_t tFinger;
    boolean bFromMultiTouch;
#ifndef __WIDGET_DISABLE_TRANSITION__
    boolean bTransiting;
    boolean bSlip;
    boolean bSlipChange;
    s16 nOriPressX;
    s16 nOriPressY;
    s16 nPressX;
    s16 nPressY;
    s16 nMoveX;
    s16 nMoveY;
#endif
#endif
#endif // defined(__MULTI_TOUCH__) || defined(__MULTI_TOUCH_SLIM__)
#ifdef __PICVIEWERAPP_SMALLROM__
    boolean     bShowLSKOption;
    boolean     bShowLSKSelect;
    boolean     bShowLSKDelete;
#endif
} PicViewerViewWndData_t;

#ifdef __MMI_PICVIEWER_ZOOM_ENABLE__
typedef struct
{
    IWidget *pImageAbsContainerWdg;
    IWidget *pImageWdg;
    IWidget *pViewportWdg;
    IWidget *pScrollIndicatiorWdg;
#ifndef __PICVIEWERAPP_SMALLROM__
    IWidget *pActionBarBgImageWdg;
    IWidget *pZoomInButtonWdg;
    IWidget *pBackButtonWdg;
    IWidget *pZoomOutButtonWdg;
#endif
} PicViewerZoomWdgList_t;

typedef struct
{
    boolean bIsInterfaceModelSet;
    u32 nViewPortOffsetX;
    u32 nViewPortOffsetY;
    u32 nViewPortWidth;
    u32 nViewPortHeight;
    u32 nMovingOffsetX;
    u32 nMovingOffsetY;
    u32 nBaseWidth;
    u32 nBaseHeight;
    u32 nDisplayX;
    u32 nDisplayY;
    u32 nDisplayWidth;
    u32 nDisplayHeight;
    u32 nNewContainerWidth;
    u32 nNewContainerHeight;
    boolean bDecodeNewArea;
    boolean bIgnoredViewPortChange;
    boolean bIsDecoding;
#ifdef __PICVIEWER_ZOOM_MOVING_SEAMLESS__
	boolean bDrawCacheBG;
#endif
    WidgetHandler_t tZoomImageWidgetHdlData;
    PicViewerZoomWdgList_t tWdgList;
} PicViewerZoomWndData_t;
#endif //__MMI_PICVIEWER_ZOOM_ENABLE__

#ifdef __MMI_PICVIEWER_SLIDESHOW_ENABLE__
typedef struct
{
#ifndef __WIDGET_DISABLE_TRANSITION__
    IWidget *pDummyWdg;
    IWidget *pTransitionWdg;
#endif
    IWidget *pImageWdg;
} PicViewerSlideShowWdgList_t;

typedef struct
{
    PicViewerSlideShowWdgList_t tWdgList;
    boolean bPause;
    boolean bDecode;
} PicViewerSlideShowWndData_t;
#endif //__MMI_PICVIEWER_SLIDESHOW_ENABLE__

typedef struct
{
    IWidget *pAbsContainer;
    IWidget *pImageWdg;
    IWidget *pCroppingZoneBitmapWdg;
#ifndef __PICVIEWERAPP_SMALLROM__
    IWidget *pZoomInButtonWdg;
    IWidget *pZoomOutButtonWdg;
    IWidget *pActionBarBgImageWdg;
    IWidget *pBackButtonWdg;
    IWidget *pSetButtonWdg;
    IWidget *pZoomSwitchButtonWdg;
#endif
} PicViewerSetWallpaperWdgList_t;

typedef struct
{
	boolean bIsPressed;
	u16 nPressOn_X;
	u16 nPressOn_Y;
	u16 nZoomPressOn_X;
	u16 nZoomPressOn_Y;
	u16 nDragTo_X;
	u16 nDragTo_Y;
} CroppingZoneDragPos_t;

typedef enum
{
    PICVIEWER_SET_WALLPAPER_NONE,
    PICVIEWER_SET_WALLPAPER_MOVE,
    PICVIEWER_SET_WALLPAPER_ZOOM
} PicViewerSetWallpaperMode_e;

typedef struct
{
	CroppingZoneDragPos_t tDragCroppingZonePos;
	u8 nZoomIdx;                // Index of zoom resolution array(defined in mmi_picviewerapp_util.c).
	boolean bInMoveCropping;
	IImage *pIDecWallpaper;
    WidgetHandler_t tWallpaperContainerHdlData;
    PicViewerSetWallpaperMode_e eSetWallpaperMode;
    PicViewerSetWallpaperWdgList_t tWdgList;
} PicViewerSetWallpaperWndData_t;

typedef struct
{
	MAE_WChar *pName;
	MAE_WChar *pType;
	u32 nSize;
	MAE_WChar *pDate;
    MMI_Common_Location_Type_e  eLocationType;
	MMI_Common_SupportedFileType_e eFileType;
} PicViewerDetailInfo_t;

#ifdef __PICVIEWERAPP_SMALLROM__
typedef struct
{
    OptionMenuWdgList_t tOptionMenuWdgList;
    OptionMenuData_t    tOptionMenuData;
} PicViewerOptionWndData_t;
#endif

typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} PicViewerSetAsWndData_t;

/**
 * Application structure
 */

typedef struct
{
	APPLET_BASE_ELEMENTS;
    VectorClass_t   *pImageUrlList;
    PicViewerItemType_e eItemType;
#ifdef  __G_SENSOR_MMI__
	ORIENTATION_e  eCurrentOrientation;
	ORIENTATION_e  eDecodeOrientation;
#endif  /* __G_SENSOR_MMI__ */
	IImage *pIImage;
#ifdef __PICVIEWER_MULTI_FINGER__
    boolean bWaitScaleImageDbClick;
    boolean bWaitScaleImageMultiFinger;
    u32 nKeepScaleWidth;
    u32 nKeepScaleHeight;
    u32 nRunCounter;
#ifndef __WIDGET_DISABLE_TRANSITION__
    u8 nDecodeImageNum;
    IImage *pLeftIImage;
    IImage *pRightIImage;
    u32 nKeepIdx;
    boolean bTransitByFinger;
    boolean bDecodeFailed;
#endif
    boolean bReloadInfo;
    boolean bFromResume;
#endif
	IBitmap *pIBitmap;
#ifdef __PICVIEWER_ZOOM_MOVING_SEAMLESS__
	IBitmap *pCacheBmp;
#endif
	u32 nCurrentIdx;
	u32 nNumOfImages;
	u32 nImageWidth;
	u32 nImageHeight;
    ImgFormat_t nImageFormat;
	u32 nDisplayWidth;
	u32 nDisplayHeight;
	u8 eActivateMode;
#ifdef __MMI_PICVIEWER_ZOOM_ENABLE__
	PicViewerZoomType_e eZoom;
	PicViewerZoomType_e eMAXZoom;
#endif
	u32 nZoomCenterX;
	u32 nZoomCenterY;
#ifndef __WIDGET_DISABLE_TRANSITION__
	u8 eTransition;
#endif
    boolean bEmbeddedMode; // Indicate whether the PicViewer application is in embedded mode.
	boolean bNotZoomable;
	boolean bCloseAfterRemoveStorage;  // this flag would be turned on if the storage(SD1/SD2) of current image was removed
	boolean bDialogOn;
	boolean bActived;
	boolean bRedraw;
    boolean bShowTimeoutNotice;
    PicViewerDetailInfo_t   *pDetailsInfo;
	boolean bShowOptionButton;
#ifdef __MMI_PICVIEWER_SLIDESHOW_ENABLE__
	boolean bSlideShowFirstTime;
#endif
	boolean bIsKeyLocked;
	MAE_WChar *strImgURL;
#if defined(__MULTI_TOUCH__) || defined(__MULTI_TOUCH_SLIM__)
	ImgDecAngle_t eRotateAngle;
	boolean bIsMultiTouchLocked;
    IImage *pIImageTemp;
    s16 nZoomCount;
#endif
#if defined(__MULTI_TOUCH_SLIM__) && defined(__MMI_PICVIEWER_ZOOM_ENABLE__)
    boolean bUseZoomDecode;
#endif //defined(__MULTI_TOUCH_SLIM__) && defined(__MMI_PICVIEWER_ZOOM_ENABLE__)
	PicViewerEntryMode_e eEntryMode;
	PicViewerSubMode_e eWndSubMode;
	u32     nFileHandle;
    u32     nFileNum;
    FileMgr_ListData_t tFileListData;
    MAE_WChar *pCurrPath;
    VFS_FileID_t    tFileId;
    u8      *pBuffer;
    u32     nBufLen;
    u8  nCount;
    PfnMAE_Notify pfnFileListFinishCb;
    u32 nClient;
    CmnLaunchAppFileOpRspCb pfnFileOpRspCb;
    u32 nOptype;
#if !defined(__NAND_MMI__) && defined(__ONBOARD_USER_STORAGE_MMI__)
    VFS_VOL_TYPE eVFSType;
#endif
    boolean bPicIsDeleted;
    boolean bEnableBlogLink;
#if defined(__3D_UI_PICVIWER_SLIDESHOW__)
    IBitmap *pSlideShowBmp[SLIDE_SHOW_3D_TOTAL_IMAGE];
    IBitmap *pBGBmp;
    u16 nBmpOldX[SLIDE_SHOW_3D_TOTAL_IMAGE];
    u16 nBmpOldY[SLIDE_SHOW_3D_TOTAL_IMAGE];
    u32 nSlideShowIdx;
    u32 nSlideShowCount; //0 ~ SLIDE_SHOW_3D_TOTAL_IMAGE
    boolean bSlideShowInit;
    boolean bSingleKFMode;
    IImage *pCurrentImage;
    IWidget *p3DLoaderWdg;
#endif

#ifdef __MMI_OMA_DRM_V1__
    boolean bImgNeedConsumeRights;
    boolean bShowRightsInstallResult;
#endif
    ImageMakerCBData_t *pImageMakerCBData;
#ifdef __MMI_STEREO_IMAGE__
    ImgDecStereo_e eStereo;
    boolean bIs3DDecoding;
#endif
} PicViewerAppData_t;

#if defined(__3D_UI_PICVIWER_SLIDESHOW__)
static u32 PageFrameIdxArray[] =
{
    50/*Page1*/, 135/*Page2*/, 230/*Page3*/, 320/*Page4*/, 410/*Page5*/, 490/*Page6*/
};

static u32 PageFrameCheckIdxArray[] =
{
    50-3/*Page1*/, 135-3/*Page2*/, 230-3/*Page3*/, 320-3/*Page4*/, 410-3/*Page5*/, 490-3/*Page6*/
};
#endif

/*=============================================================*/
// Global function prototype declaration
/*=============================================================*/
MAE_Ret PicViewerConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret PicViewerDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean PicViewerStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean PicViewerSuspendCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean PicViewerResumeCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean PicViewerEmbeddedAppCloseCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean PicViewerKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean PicViewerDisplayPreviousCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
#ifndef __PICVIEWERAPP_SMALLROM__
boolean PicViewerKeyReleaseCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
#endif
boolean PicViewerDisplayNextCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean PicViewerTSClickCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

#if defined(__MMI_STEREO_IMAGE__)
boolean PicViewerViewWndStarKeyPressCb(PicViewerAppData_t *pThis);
#endif

// Window manager related function
MAE_Ret PicViewerViewWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifdef __MMI_PICVIEWER_ZOOM_ENABLE__
MAE_Ret PicViewerZoomWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif
#ifdef __MMI_PICVIEWER_SLIDESHOW_ENABLE__
MAE_Ret PicViewerSlideShowWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif
MAE_Ret PicViewerSetWallpaperWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret PicViewerDetailsWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

#ifdef __PICVIEWERAPP_SMALLROM__
MAE_Ret PicViewerOptionWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif

#if defined(__MULTI_TOUCH__) || defined(__MULTI_TOUCH_SLIM__)
// Get TS type for supportting MULTI_TOUCH evt or not
boolean PicViewerSupportMultiTouch(void);
#endif

#ifdef __MMI_STEREO_IMAGE__
ImgDecStereo_e _PicViewerSwitch2D3DMode(ImgDecStereo_e eStereo);
#endif

// Application Launcher related function
static boolean _PicViewerAppLaunch(UrlSrvUrlHdl_t pUrl, void *pUserData, void **ppvLaunchObj, CmnAppLaunchRspCbInfo_t *psRspCbInfo);
static boolean _PicViewerPlayEntryHandler(UrlSrvUrlHdl_t pUrl, void *pUserData, void **ppvLaunchObj, CmnAppLaunchFileOpRspCbInfo_t *pRspCbInfo);
static boolean _PicViewerSimplePlayEntryHandler(UrlSrvUrlHdl_t pUrl, void *pUserData, void **ppvLaunchObj, CmnAppLaunchFileOpRspCbInfo_t *pRspCbInfo);
static boolean _PicViewerSimplePlayAllEntryHandler(UrlSrvUrlHdl_t pUrl, void *pUserData, void **ppvLaunchObj, CmnAppLaunchFileOpRspCbInfo_t *pRspCbInfo);
static boolean _PicViewerSimplePlayBufferEntryHandler(UrlSrvUrlHdl_t pUrl, void *pUserData, void **ppvLaunchObj, CmnAppLaunchFileOpRspCbInfo_t *pRspCbInfo);
#ifdef __MMI_PICVIEWER_SLIDESHOW_ENABLE__
static boolean _PicViewerPlaySlideShowEntryHandler(UrlSrvUrlHdl_t pUrl, void *pUserData, void **ppvLaunchObj, CmnAppLaunchFileOpRspCbInfo_t *pRspCbInfo);
#endif
static boolean _PicViewerPlayAndSelectEntryHandler(UrlSrvUrlHdl_t pUrl, void *pUserData, void **ppvLaunchObj, CmnAppLaunchFileOpRspCbInfo_t *pRspCbInfo);
static boolean _PicViewerPlayAfterSavingEntryHandler(UrlSrvUrlHdl_t pUrl, void *pUserData, void **ppvLaunchObj, CmnAppLaunchFileOpRspCbInfo_t *pRspCbInfo);
static boolean _PicViewerCropPicEntryHandler(UrlSrvUrlHdl_t pUrl, void *pUserData, void **ppvLaunchObj, CmnAppLaunchFileOpRspCbInfo_t *pRspCbInfo);

#ifdef __PICVIEWER_MULTI_FINGER__
#ifndef __WIDGET_DISABLE_TRANSITION__
void _PicViewer_PrepareTransitionImage(PicViewerAppData_t  *pThis, boolean bLeft);
MAE_Ret _PicViewer_DecodeImage(PicViewerAppData_t *pThis);
#endif
#endif
MAE_Ret _PicViewerDecodeSuccessHdl(PicViewerAppData_t *pThis);
MAE_Ret _PicViewerViewWndDecodePrev(PicViewerAppData_t *pThis);
MAE_Ret _PicViewerViewWndDecodeNext(PicViewerAppData_t *pThis);
#endif /* __MMI_PICVIEWERAPP_PRIV_H__ */
