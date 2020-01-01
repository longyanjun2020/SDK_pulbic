/**
* @file mmi_android_idleapp_priv.h
*
* Class Id: CLSID_ANDROID_IDLEAPP
*
* @version $Id: mmi_android_idleapp_priv.h $
*/
#ifndef __MMI_ANDROID_IDLEAPP_PRIV_H__
#define __MMI_ANDROID_IDLEAPP_PRIV_H__
#ifdef __UI_STYLE_MMI_ANDROID_IDLE__
/*-------------------------------------------------------------------------*/

#include "mmi_mae_common_def.h"
#include "mmi_android_idleapp.h"

/*-------------------------------------------------------------------------*/
#include "mmi_baseapplet.h"
#include "mmi_common_cfg.h"
#include "mmi_launcher_off.h"
#include "mmi_launcher_dialer.h"
#include "mmi_launcher_calllog.h"
#include "mmi_launcher_keyguard.h"
#include "mmi_launcher_shortcut.h"
#include "mmi_srv_header.h"
#include "mmi_common_wdgvar.h"
#include "mmi_wdg_desktop.h"
#include "mmi_wdg_calendardesktop.h"
#include "mmi_wdg_dclockdesktop.h"
#include "mmi_wdg_fmdesktop.h"
#include "mmi_wdg_mpdesktop.h"
#include "mmi_wdg_notedesktop.h"
#include "mmi_wdg_opdesktop.h"
#include "mmi_wdg_searchdesktop.h"
#include "mmi_wdg_profile.h"
#include "mmi_android_idleapp_id.h"
#include "mae_animation.h"
#include "mmi_common_menu.h"
#include "mmi_common_util.h"
#include "Mmi_simsrv_def.h"

#ifdef __UI_STYLE_FLIPDCLOCK__
#include "mmi_wdg_flipdclock.h"
#endif

#define UNUSED_PARAM(x)     do{x=x;}while(0)

#define ANDROID_PAGE_NUM				5
#define	ANDROID_GRID_MAX_NUM (ANDROID_GRID_HOMEPAGE_MAX_NUM + ANDROID_GRID_SUBPAGE_MAX_NUM * (ANDROID_PAGE_NUM - 1))

#define ANDROID_TS_MOVE_CRITERIA    10
// For memory usage, widgets on desktop are released when Idle is suspend
// However, if this macro isn't defined, widgets will be released only when Idle is invisible
// #define __ANDROID_IDLE_RELEASE_ALL_WDG_ON_SUSPEND__

typedef struct
{
    u8  u8PosIndex;
    u8  u8MenuID;
    IWidget *	pWdg;
    MainMenuStartType_e eStartType;
    u32 nStartID;
    u32 nParamID;
    WidgetSize_t tSize;
#ifndef __UI_STYLE_MMI_ANDROID_IDLE_MUTEX__
    s32 Pos_x;
    s32 Pos_y;
    WidgetHandler_t DeskTopWdgHandle;
#endif
} AndroidItemInfo_t;


typedef enum
{
    ANDROID_IDLE_WALLPAPER_ENTRY,
    ANDROID_IDLE_WALLPAPER_USE_CACHE,
    ANDROID_IDLE_WALLPAPER_CHANGE,
} AndroidANDROID_IDLE_WALLPAPER_Update_e;

typedef enum
{
	ANDROID_IDLE_WALLPAPER_TYPE_PREDIFINED,
	ANDROID_IDLE_WALLPAPER_TYPE_PHONE, // Wallpaper which is stored at fs:/PHONE/Pictures
	ANDROID_IDLE_WALLPAPER_TYPE_CARD, // Wallpaper which is stored at fs:/CARD/Pictures
	ANDROID_IDLE_WALLPAPER_TYPE_NON_DEFAULT // Wallpaper which is not stored at fs:/PHONE/Pictures and fs:/CARD/Pictures

} AndroidIdleWallpaperType_e;

typedef struct
{
	VFS_FileID_t nFileId;
	AndroidIdleWallpaperType_e eWallpaperType;

} AndroidIdleWallpaperListItemInfo_t;

typedef struct
{
    IWidget *pFullScreenAbsContainer;
    IWidget *pBgImgWdg;
    IWidget *pMainAbsContainer;
    IWidget *pSoftkeyWdg;
    IWidget *pFadeoutWdg;
    IWidget *pMediaNameTxtWdg;
    IWidget *pNetworkTxtWdg;
    IWidget *pNetworkSlaveTxtWdg;
#ifdef __UI_STYLE_MMI_ANDROID_4_0__
    IWidget *pStkContainer;
#endif
    IWidget *pStkTxtWdg;
    IWidget *pStkSlaveTxtWdg;
    IWidget *pImeAssistWdg;
    IWidget *pShortcutBarShortcutWdg;
    IWidget *pShortcutBarOffButtonWdg;
    IWidget *pShortcutBarOnButtonWdg;
#ifdef __UI_STYLE_FLIPDCLOCK__
    IWidget *pFlipClockWdg;
    IWidget *pFlipClockBGWdg;
#endif
#ifdef __APP_MMI_COUNTDOWN_TIMER__
    IWidget *pCountDownAliveWdg;
#endif
#ifndef __UI_STYLE_MMI_ANDROID_4_0__    //  CB will not appeared in Android 4.0
    IWidget *pCbBgImgWdg;
#endif
    IWidget *pEventTxtWdg;
#ifndef __UI_STYLE_FLIPDCLOCK__
    IWidget *pLocalTimeTxtWdg;
    IWidget *pLocal12HTxtWdg;
    IWidget *pSeperatorTxtWdg;
    IWidget *pRemoteTimeTxtWdg;
    IWidget *pRemote12HTxtWdg;
#endif
    IWidget *pWstDateTxtWdg;
    IWidget *pChnDateTxtWdg;
    IWidget *pImgItemWdg[ANDROID_PAGE_NUM];
    IWidget *pAndroidSoftkeyContainer;
#ifdef __UI_STYLE_MMI_ANDROID_4_0__
    IWidget *pAndroidSepLine;
    IWidget *pAndroidLeft2key;
    IWidget *pAndroidLeft1key;
    IWidget *pAndroidMiddlekey;
    IWidget *pAndroidRight1key;
    IWidget *pAndroidRight2key;
#else
    IWidget *pAndroidLeftkey;
    IWidget *pAndroidMiddlekey;
    IWidget *pAndroidRightkey;
#endif // __UI_STYLE_MMI_ANDROID_4_0__

#ifdef __UI_STYLE_MMI_ANDROID_IDLE_ENABLE_PREVIEW__
    IWidget *pPagePreviewCnt;
#endif
#ifdef __CHECK_CPU_STATUS_BEFORE_SLEEP__
    IWidget *pWarningImgWdg;
#endif
    WidgetHandler_t tPagePreviewHandler;
    IWidget *AndroidIdlePageWdg[ANDROID_PAGE_NUM];
} AndroidIdleDesktopWndWdgList_t;

typedef struct
{
	AndroidIdleDesktopWndWdgList_t tWdgList;
} AndroidIdleDesktopWndData_t;

typedef struct
{
	IWidget *pMenuWdg;
} AndroidIdleWdgWndData_t;
/*-------------------------------------------------------------------------*/

/**
 * Application structure
 */
typedef struct MMI_ANDROID_IDLEAPP_TAG {

    APPLET_BASE_ELEMENTS;
    /* Add custom fields below */
    char           *pSPNName;
    MMSRV_NetworkRegInfo_t *pINetworkRegInfo;

#ifdef __DUAL_SIM_MMI__
    MMSRV_NetworkRegInfo_t *pINetworkRegInfo_Slave;
#endif /* __DUAL_SIM_MMI__ */

    //Disable code for softkey handling of CB
    //boolean         bSetCBSoftkey;
    boolean         bCBSliding;
    u8              nCurrentCBMsgId;
    Msg_CB_Setting_e eCBMsgSetting;

#ifdef __MMI_COMMON_SHOW_MEDIA_NAME__
    MAE_WChar      *pMediaName;
#endif /*  __MMI_COMMON_SHOW_MEDIA_NAME__ */


    IImage         *pIWallpaperImage;
    boolean        bDialWithFirstKey;

#ifdef __NATIVE_GAME_MMI_PEDOMETER__
    IWidget       *pPedometerButtonWdg;
    IDataModel	  *pButtonDataMdl;
    boolean         bPedometerDialogEnabled;
#endif /*  __NATIVE_GAME_MMI_PEDOMETER__ */

    SetRingToneVolume_e eVolumeLevel;
    AudioEnvSrvVolLevel_e eMediaVolumeLevel;
    CFGItemID_e eVolumeId;//record volume dialog is created by which ap
    boolean        bVolumeDialogEnabled;

#ifdef __APP_MMI_FM_RADIO__
    u32             nFMRadioBGPlay;
#endif /* __APP_MMI_FM_RADIO__ */

    MAE_WChar      wszCurrentWallpaperURL[FILEMGR_MAX_FILEPATH_SIZE];
    MAE_WChar      wszPreviousWallpaperURL[FILEMGR_MAX_FILEPATH_SIZE];
    boolean         bMPlayerBGPlay;
    boolean         bIsWallpaperReleasedByLowMem; // Wallpaper is released when idleapp is invisible & memroy low
    boolean			bIsCropWallpaper;
    boolean         bAdjustingBGPlayVol; // Request to adjust MPlayer volume.

#ifdef __IDLEAPP_WALLPAPER_MMC_CACHE__
    MAE_WChar       wszCachedWallpaperURL[FILEMGR_MAX_FILEPATH_SIZE];
    boolean         bCachingToCard;
#endif /* __IDLEAPP_WALLPAPER_MMC_CACHE__ */

    FileMgrHandleID_t	nMonitorHandle;

    MAE_WChar      *pNonDefaultWallpaperURL;

#ifdef __IP_CALL_MMI__
    boolean bShortPress;    // handle short press "send key"
#endif /* __IP_CALL_MMI__ */

    IAnimation *pAnimation;


    boolean		bIsSelectMSCorVDC;

    s32 sWallPaperMoveStartPos;
    s32 sWallPaperMoveEndPos;
    s32 sWallPaperReleasePos;//Record the release position in container of Wallpaper when moving end

    ArrayClass_t 	*ppIArray[ANDROID_PAGE_NUM];
#ifndef __UI_STYLE_MMI_ANDROID_IDLE_MUTEX__
    ArrayClass_t 	*ppIDskTopWdgArray[ANDROID_PAGE_NUM];
    boolean         bIsDskWdgFocus;
#endif
    IWidget         *pIParentAbsCntr;

    s8				nHotItemIdx;
    s8				nHotVecIdx;
    WPos_t 			stTmp;

    boolean			bIsLaunchAP;

    boolean	        bSwitch	:1; //Check if the pages are switched or not
    boolean         bDragMove:1;//Check if the icon is drager and moved by finger or not
    boolean	        bTSPRESS:1;//Check if the touch press has done or not
    boolean	        bPageMove:1;//Check if the page is moved by finger is now doing or not
    boolean	        bTranslation:1; //Check if the transition among pages is now doing or not
    boolean         bIsAddNewDragWdg:1;//Check if want add new item from mainmenu
    boolean         bIsDelActive:1;//check if want to delete the icon
    boolean         bIsCheckDisk;
    boolean         bIsBTAccessFiles;

    IWidget         *pIAbs;
    IWidget         *pBGImgWdg;
    IWidget		    *pITransWdg;

    IWidget         *pITransAbs;
    IWidget         *pITransLeftContainer;
    IWidget         *pITransRightContainer;

    IWidget         *pIFocusWidget;
    IWidget         *pFlipDClock;

    s8				sCurPageIdx;
    s32				s32TSPRESSPos_X;
    s32				s32TSPRESSPos_Y;

    ModelListener_t TransitionMdlListener;

    s32	nFocusIndex;
    s32	nTouchPos_X;
    s32	nTouchPos_Y;
    s32 nDragShift_X;
    s32 nDragShift_Y;
    s32 sPageMoveMaxLengh;
    s32 sWallPaperSpeed;
    s32 sWallpaperLeftPosThreshold;

    u16 nDskDragStartPosX;
    u16 nDskDragStartPosY;

    AndroidItemInfo_t *pNewItemDataFromMenu;
    AndroidItemInfo_t *pFocusItemInfo;
    u32 nPreDelImageID;
    u32 nDeskWdgSelID;

    //  AP status
    boolean bIsApSuspend;
    boolean bIsDisableReleaseOnce;
    boolean bIsTsPressed;

} MMI_ANDROID_IDLEAPP;

/*-------------------------------------------------------------------------*/
MAE_Ret AndroidIdleConstructor(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
MAE_Ret AndroidIdleDestructor(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean AndroidIdleStartCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean AndroidIdleStopCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean AndroidIdleSuspendCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean AndroidIdleResumeCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean AndroidIdleKeyPressCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean AndroidIdleTouchPressCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean AndroidIdleKeyLongPressCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean AndroidIdleKeyReleaseCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
static MAE_Ret _AndroidIdleDesktopKeyPress(MMI_ANDROID_IDLEAPP *pThis, u32 nKeyCode);
static void _AndroidIdleDesktopNumericKeyPress(MMI_ANDROID_IDLEAPP *pThis, u32 nKeyCode);
boolean AndroidIdleAppInVisibleCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);

MAE_Ret AndroidIdleWndDesktopHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _AndroidIdleWndCreateDesktop(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _AndroidIdleWndShowDesktop(void *pCusHandle, void *pWndData);
MAE_Ret _AndroidIdleWndHideDesktop(void *pCusHandle, void *pWndData);
MAE_Ret _AndroidIdleWndSetDesktop(void *pCusHandle, void *pWndData);
MAE_Ret _AndroidIdleWndDestroyDesktop(void *pCusHandle, void *pWndData);

void AndroidIdleVolumeDialogListener(void *pUserData, ModelEvent_t *pModelEvent);
void AndroidIdleVolumeDialogTimerCB(void *pUserData);
MAE_Ret AndroidIdleCreateNormalDialog(MMI_ANDROID_IDLEAPP* pThis, u32 uTextId, u32 nTimerTick);
MAE_Ret AndroidIdleNormalDialogTimerCB(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);

static MAE_Ret _AndroidIdleInit(MMI_ANDROID_IDLEAPP *pThis);

void AndroidIdleDateTickCB(void *pUserData);
#ifndef __UI_STYLE_FLIPDCLOCK__
void AndroidIdleMinuteTickCB(void *pUserData);
#endif
void AndroidIdleSysTimeChangeCB(void *pUserData, MAE_DateTime_t *pLocalTime);
void AndroidIdleSysTimeZoneChangeCB(void *pUserData, MAE_TimeZone_e ePrimaryTimeZone);

static MAE_Ret _AndroidIdleSetSPNName(MMI_ANDROID_IDLEAPP *pThis, COMMON_SPN_Type_e eSPNType, u8 nDualMode);
static MAE_Ret _AndroidIdleDetermineSPNwithPriority(MMI_ANDROID_IDLEAPP *pThis, COMMON_SPN_Type_e eCurrentType, boolean bRoaming, u8 nDualMode);
static MAE_Ret _AndroidIdleUpdateSPN(MMI_ANDROID_IDLEAPP *pThis, u8 nDualMode);
static MAE_Ret _AndroidIdleHandleVolumeKey(MMI_ANDROID_IDLEAPP *pThis, u32 nKeyCode);
static void _AndroidIdleLaunchCallLogApp(MMI_ANDROID_IDLEAPP *pThis);

#ifndef __UI_STYLE_FLIPDCLOCK__
static MAE_Ret _AndroidIdleDoTimeWidgetLayout(MMI_ANDROID_IDLEAPP *pThis);
#endif
#ifdef __APP_MMI_SHORTCUT__
static MAE_Ret _AndroidIdleLaunchShortcutByKeyCode(MMI_ANDROID_IDLEAPP *pThis, u32 nKeyCode, u32 nLaunchByKeyCode, MAE_EventId nEventId);
static void _AndroidIdleChangeShortcut(MMI_ANDROID_IDLEAPP *pThis, u32 nKeyCode);
#endif
void AndroidIdleThemeChangeCB(void *pUserData);
void AndroidIdleUSBStatusIndCB(void *pUserData, MMI_USB_STATUS_E eUSBStatus);
static MAE_Ret _AndroidIdleApplyThemeLayout(MMI_ANDROID_IDLEAPP *pThis, AndroidANDROID_IDLE_WALLPAPER_Update_e eUpdateCond);
static boolean _AndroidIdleIsDefaultImageURL(MAE_WChar *pURL);
static boolean _AndroidIdleIsValidImageURL(MAE_WChar *pURL);
static MAE_Ret _AndroidIdleLoadWallpaperByURL(MMI_ANDROID_IDLEAPP *pThis, IWidget *pIDestWdg, MAE_WChar *pURL, AndroidANDROID_IDLE_WALLPAPER_Update_e eUpdateCond);
static MAE_Ret _AndroidIdleUpdateWallpaper(MMI_ANDROID_IDLEAPP *pThis, IWidget *pIDestWdg, AndroidANDROID_IDLE_WALLPAPER_Update_e eUpdateCond);
static void _AndroidIdleRegWallpaperDecodeNotify(MMI_ANDROID_IDLEAPP *pThis);
static void _AndroidIdleDeregWallpaperDecodeNotify(MMI_ANDROID_IDLEAPP *pThis, boolean bForceUpdate);
void _AndroidIdleWallpaperDecodeNotify(IImage *pImage, IBase *pData, ImgStatus_t nStatus);

static void _AndroidIdleLaunchMainMenuApp(MMI_ANDROID_IDLEAPP *pThis);
static MAE_Ret _AndroidIdlePlayCBMsg(MMI_ANDROID_IDLEAPP *pThis, u32 nMsgID);

#ifdef __IDLEAPP_WALLPAPER_MMC_CACHE__
void AndroidIdleImageMakerCB(void *pUserData, ImageMakerCBData_t *pCBData);
static MAE_Ret _AndroidIdleGetHashFileName(MAE_WChar *pFileURL, MAE_WChar **ppFileName);
static MAE_Ret _AndroidIdleGetCacheURL(MAE_WChar* pFileURL, MAE_WChar** ppCacheFileURL);
static MAE_Ret _AndroidIdleCacheWallpaperToCard(MMI_ANDROID_IDLEAPP *pThis, MAE_WChar *pFileURL);
static MAE_Ret _AndroidIdleReadWallpaperCacheFromCard(MMI_ANDROID_IDLEAPP *pThis, MAE_WChar *pFileURL);
#endif


#ifdef __USB_MMI_NON_BLOCKING_USAGE__
static boolean _AndroidIdleIsBlockingByUSB(MMI_ANDROID_IDLEAPP *pThis);
#endif
static boolean _AndroidIdleIsMMCCardExisted(MMI_ANDROID_IDLEAPP *pThis, ACCDeviceType_e eDeviceType);
static MAE_Ret _AndroidIdleGetDefaultImageID(u32 *pImgId);
MAE_Ret _AndroidIdleSetMonitorURL(MMI_ANDROID_IDLEAPP *pThis, MAE_WChar *pURL);
void AndroidIdleMonitorURLCb(void *pUserData, void *pInfo);

#if defined(__HALL_SWITCH_MMI__)
void AndroidIdleAccessoryPlugStatusCB(void *pUserData, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);
#endif

#ifdef __G_SENSOR_MMI__
void AndroidIdleSimpleActionCB(void *pUserData, SIMPLE_ACTINO_e eAction);
#endif

void AndroidIdleCleanFuncForShortcutApp(IBase *pIssuer, u32 param);

// default event handler
boolean AndroidIdleDefaultHandler(MAEEvent_t evt, u32 lParam, u32 dParam);

static void AndroidIdleCloseAppletCB(IBase *pUser, u32 param);
static void _AndroidIdleSIMStatusChangeCB(void *pThis, COMMON_SIM_CARD_STATUS_e eStatus);
#ifdef __MMI_COMMON_SHOW_MEDIA_NAME__
static MAE_Ret _AndroidIdleGetMediaName(MMI_ANDROID_IDLEAPP *pThis, MAE_WChar *pMediaURL);
static void _AndroidIdleShowMediaName(MMI_ANDROID_IDLEAPP *pThis);
void AndroidIdlePlayingMediaNameCB(void *pUserData, MAE_WChar *pMediaName);
#endif

#if defined(__APP_MMI_CHECKDISK__)
void AndroidIdleCheckDiskStatusListener(char *pSbjName, SubjectStatus_e nSbjStatus, void *pUser);
#endif

void AndroidIdlePlayMediaStatusCB(void *pUserData, SrvAudioPlayerPlayStatus_e ePlayStatus);

#ifdef __APP_MMI_FM_RADIO__
void AndroidIdleFMStatusChangeCB(void *pThis, u32 nCusData, FmradioSrvPlayInfo_t *pPlayInfo);
void AndroidIdleFMInterruptNotifyCB(u32 nCusData, u32 nEvt);
#endif

void AndroidIdleBacklightOnOffCB(void *pUserData, boolean bBackLightOn);
#ifdef __CHECK_CPU_STATUS_BEFORE_SLEEP__
void AndroidIdleFindHighSpeedTaskCB(void *pUserData, HighSpeedTaskStatus_e eStatus);
#endif
void AndroidIdleNewCbMsgCB(void *pUserData, SMI_MsgID_t nMsgID);
void AndroidIdleProfileChangeCB(void *pUserData, ProfileID_e eProfileID);
void AndroidIdleSetupAndroidIdleTextCB(void *pUserData, MAE_WChar *pText, u32 nDual);
void AndroidIdleConfigItemUpdateCB(void *pUserData, SrvCfgItemStatusChangeType_e eChangeType, SrvCfgItemUpdateResult_t uResult);
void AndroidIdleTextSlideChangeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nSlideStatus, IWidget *pWidget);
void AndroidIdleNetworkRegIndCB(void *pUserData, MMI_MMSRV_RegStat_e eState, MAE_DualMode_t eDualMode);
void AndroidIdleGPRSRegStatusIndCB(void *pUserData, MMSRV_GPRSRegInd_t *pData, MAE_DualMode_t eDualMode);

#ifdef __NATIVE_GAME_MMI_PEDOMETER__
void AndroidIdleGoalReachCB(void *pUserData);
void AndroidIdleSensorStatusChangeCB(void *pUserData);
#endif

void AndroidIdleEvtCenterLogChangeCB(void *pUserData, u16 nLogNum);
static void _AndroidIdleLaunchDialerApp(MMI_ANDROID_IDLEAPP *pThis, u32 nKeyCode);
static MAE_Ret _AndroidIdleUpdateSIMAndSPN(MMI_ANDROID_IDLEAPP *pThis, u8 nDualID, u8 eSIMStatus);
static MAE_Ret _AndroidIdleUseDefaultWallpaper(MMI_ANDROID_IDLEAPP *pThis);
void AndroidIdleLaunchAppRspCb(void *pUserData, MAE_Ret nRspCode);
void AndroidIdleLaunchOffAppRspCb(void *pUserData, MAE_Ret nRspCode);
void AndroidIdleMemSubjectSubscribeCb(char *pSubjectName, SubjectStatus_e eSubjectStatus, void *pUser);
boolean AndroidIdleReleaseDesktopWidgetCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
void AndroidIdleCountDownTimerStateChangeCB(void *pThis, CountDownTimerSrv_State_e eState);

void AndroidIdleSoftButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
MAE_Ret AndroidIdleWndWdgHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _AndroidIdleWndCreateWdg(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _AndroidIdleWndDestroyWdg(void *pCusHandle, void *pWndData);
void _AndoroidIdleDeskWdgSelCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _AndoroidIdleWdgMenuBackCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);

MAE_Ret AndroidIdleInfoDialogCB(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
void AndroidIdleInfoDialogTimerCB(void *pUserData);

/*-------------------------------------------------------------------------*/
#endif /*__UI_STYLE_MMI_ANDROID_IDLE__*/
#endif /* __MMI_ANDROID_IDLEAPP_PRIV_H__ */
