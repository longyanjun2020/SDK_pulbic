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
* @file mmi_idleapp_priv.h
* @version
* @brief   Idle applet file
*
*/

#ifndef __MMI_IDLEAPP_PRIV_H__
#define __MMI_IDLEAPP_PRIV_H__

/*-------------------------------------------------------------------------*/

#include "mmi_mae_common_def.h"
#include "mmi_idleapp.h"

/*-------------------------------------------------------------------------*/
#include "mmi_idleapp_custom.h"
#include "mmi_baseapplet.h"
#include "mmi_common_cfg.h"
#include "mmi_launcher_off.h"
#include "mmi_launcher_dialer.h"
#include "mmi_launcher_phb.h"
#include "mmi_launcher_calllog.h"
#include "mmi_launcher_keyguard.h"
#include "mmi_launcher_shortcut.h"
#include "mmi_launcher_filemanager.h"
#include "mmi_launcher_mca.h"
#include "mmi_launcher_mplayer.h"
#include "mmi_launcher_setting.h"
#include "mmi_launcher_voicememo.h"
#if defined(__APP_MMI_CHECKDISK__)
#include "mmi_launcher_checkdisk.h"
#endif
#include "mmi_srv_header.h"
#include "mmi_common_wdgvar.h"
#include "mmi_wdg_calendardesktop.h"
#include "mmi_wdg_dclockdesktop.h"
#include "mmi_wdg_desktop.h"
#include "mmi_wdg_fmdesktop.h"
#include "mmi_wdg_mpdesktop.h"
#include "mmi_wdg_notedesktop.h"
#include "mmi_wdg_opdesktop.h"
#include "mmi_wdg_searchdesktop.h"
#include "mmi_wdg_shortcutdesktop.h"
#include "mmi_wdg_phonebookdesktop.h"
#include "mmi_wdg_profile.h"
#include "mmi_wdg_notepaddesktop.h"
#include "mmi_idleapp_id.h"
#include "mae_animation.h"
#include "mmi_mae_file_util.h"
#include "idleapp_resource.h"

#include "mmi_common_dialog_id.h"
#include "mmi_common_storage_mgr.h"
#include "mmi_common_cfg.h"
#include "mmi_common_util.h"
#include "mmi_common_mimetype.h"

#include "mae_widget_common.h"
#include "mmi_wdg_statuspage.h"

#if defined(__LIVE_WALLPAPER__)
#include "mmi_wdg_wallpaper.h"
#endif

#if defined(__3D_UI_IDLE_GADGETBAR__)
#include "mmi_wdg_animationcontainer.h"
#endif

#if defined(__3D_UI_IDLE_MULTIPAGE__)
#include "mmi_messagecenterapp.h"
#include "mmi_wdg_multipagecontainer.h"
#include "mmi_wdg_glAlbumSlidewidget.h"
#include "mgl_Core_Types.h"
#include "mmi_common_menu.h"
#include "mmi_mae_util_easing.h"
#endif

typedef enum
{
    IDLE_WALLPAPER_ENTRY,
    IDLE_WALLPAPER_USE_CACHE,
    IDLE_WALLPAPER_CHANGE,
    IDLE_WALLPAPER_NEXT,
    IDLE_WALLPAPER_PREV

} Idle_Wallpaper_Update_e;

typedef enum
{
    IDLE_CONFIRM_DIALOG_NONE = 0,
    IDLE_CONFIRM_DIALOG_CHECKDISK,
} Idle_Confirm_DialogID_e;

typedef enum
{
    IDLE_WALLPAPER_TYPE_PREDIFINED,
    IDLE_WALLPAPER_TYPE_PHONE, // Wallpaper which is stored at fs:/PHONE/Pictures
    IDLE_WALLPAPER_TYPE_CARD, // Wallpaper which is stored at fs:/CARD/Pictures
    IDLE_WALLPAPER_TYPE_CARD2, // Wallpaper which is stored at fs:/SD_2/Pictures
    IDLE_WALLPAPER_TYPE_NON_DEFAULT // Wallpaper which is not stored at fs:/PHONE/Pictures and fs:/CARD/Pictures

} IdleWallpaperType_e;

#ifdef __SCREEN_EFFECTS_SUPPORT__
typedef enum
{
	IDLEAPP_ACTIVE_IDLE_SCREENEFFECTWIDGET
} ScreenEffectID_e;
#endif //__SCREEN_EFFECTS_SUPPORT__
typedef struct
{
    VFS_FileID_t nFileId;
    IdleWallpaperType_e eWallpaperType;

} IdleWallpaperListItemInfo_t;

#if defined(__3D_UI_IDLE_SIMPLE__)
enum
{
    IDLEAPP_SIMPLESTYLE3D_BUTTON_MAINMENU,
    IDLEAPP_SIMPLESTYLE3D_BUTTON_SHORTCUT,        
    IDLEAPP_SIMPLESTYLE3D_BUTTON_PHONEBOOK,
    IDLEAPP_SIMPLESTYLE3D_BUTTON_TOTAL,
};
typedef u16 IdleApp_SimpleStyle3D_Button_e;
#endif //__3D_UI_IDLE_GADGETBAR__

#if defined(__3D_UI_IDLE_GADGETBAR__)
enum
{
    IDLEAPP_GADGETBAR_BUTTON_DIALER,
    IDLEAPP_GADGETBAR_BUTTON_MAINMENU,
    IDLEAPP_GADGETBAR_BUTTON_PHONEBOOK,
    IDLEAPP_GADGETBAR_BUTTON_TOTAL,
};
typedef u16 IdleApp_Gadgetbar_Button_e;
#endif //__3D_UI_IDLE_GADGETBAR__

#if defined(__3D_UI_IDLE_MULTIPAGE__)
enum
{
    IDLEAPP_MULTIPAGE_BUTTON_MAINMENU,
    IDLEAPP_MULTIPAGE_BUTTON_THUMBNAIL,
    IDLEAPP_MULTIPAGE_BUTTON_DIALER,
    IDLEAPP_MULTIPAGE_BUTTON_CONFIG,
    IDLEAPP_MULTIPAGE_BUTTON_TOTAL,
};
typedef u16 IdleApp_Multipage_Button_e;
#endif //__3D_UI_IDLE_MULTIPAGE__

typedef struct
{
    IWidget *pFullScreenAbsContainer;
    IWidget *pMainAbsContainer;
    IWidget *pSoftkeyWdg;
    IWidget *pFadeoutWdg;
    IWidget *pMediaNameTxtWdg;  // Show media name or FM radio channel info
    IWidget *pNetworkTxtWdg;
    IWidget *pNetworkSlaveTxtWdg;
    IWidget *pStkTxtWdg;
    IWidget *pStkSlaveTxtWdg;
    IWidget *pImeAssistWdg;
#ifdef __APP_MMI_COUNTDOWN_TIMER__
    IWidget *pCountDownWdg;
#endif
    IWidget *pCbBgImgWdg;
    IWidget *pEventTxtWdg;
    IWidget *pLocalTimeTxtWdg;
    IWidget *pLocal12HTxtWdg;
    IWidget *pSeperatorTxtWdg;
    IWidget *pRemoteTimeTxtWdg;
    IWidget *pRemote12HTxtWdg;
    IWidget *pWstDateTxtWdg;
    IWidget *pChnDateTxtWdg;
    IWidget *pUnspportImgTxtWdg; //show warning text for unsupport or damaged picture
    IWidget *pUnspportImgFadeoutWdg;//only hight light UnspportImgTxtWdg
#ifdef __CHECK_CPU_STATUS_BEFORE_SLEEP__
    IWidget *pWarningImgWdg;
#endif
} IdleDesktopWndWdgList_t;
typedef struct
{
    IdleDesktopWndWdgList_t tWdgList;
} IdleDesktopWndData_t;
typedef struct
{
    IWidget *pBgImgWdg;
    IWidget *pFadeoutWdg;
    IWidget *pEMNumWdg;
    IWidget *pInfoAbsContainer;
    IWidget *pLocalTimeImgGridMenuWdg;
    IWidget *pLocal12HTextWdg;
    IWidget *pDateTextWdg;
    IWidget *pMediaNameTextWdg;
    IWidget *pCountDownImgWdg;
    IWidget *pNetworkTextWdg;
#ifdef __DUAL_SIM_MMI__
    IWidget *pNetworkSlaveTextWdg;
#endif
    IWidget *pDialogInfoBgImgWdg;
    IWidget *pDialogInfoTextWdg;
    IWidget *pNewMsgImgWdg;
    IWidget *pNewMsgTextWdg;
    IWidget *pMissCallImgWdg;
    IWidget *pMissCallTextWdg;
#ifdef __DUAL_SIM_MMI__
    IWidget *pMissCallSlaveImgWdg;
    IWidget *pMissCallSlaveTextWdg;
#endif
}SubIdleDesktopWndWdgList_t;
typedef struct
{
    SubIdleDesktopWndWdgList_t tWdgList;
    u32 nNewMsgEvt;
    u32 nNewMsgSlaveEvt;
    u32 nMissedCallEvt;
    u32 nMissedCallSlaveEvt;
    u32	nAlarmUserCode;
    MAE_WChar *pMediaName;
    boolean bShowMediaName;
    boolean bMPlayerBGPlay;
#ifdef __APP_MMI_FM_RADIO__
    boolean bFMRadioBGPlay;
#endif
} SubIdleDesktopWndData_t;

/*-------------------------------------------------------------------------*/

/**
 * Application structure
 */
typedef struct MMI_IDLEAPP_TAG
{
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
    Msg_CB_Setting_e eMasterCBMsgSetting;
    Msg_CB_Setting_e eSlaveCBMsgSetting;

#ifdef __MMI_COMMON_SHOW_MEDIA_NAME__
    MAE_WChar       *pMediaName;
#endif

#if defined(__3D_UI_IDLE_MULTIPAGE__)
    IWidget         *pDesktopWdg[DESKTOP_WIDGET_NUM];
    IWidget         *pDesktopCut[DESKTOP_SHORTCUT_NUM];
#elif defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__)
    boolean         bIsDisplayShortcutBar;
    IWidget         *pDesktopWdg[SHORTCUTBAR_ITEMWDG_NUM];
#endif 

    IImage          *pIWallpaperImage;
    boolean         bIsWallpaperReleasedByLowMem; // Wallpaper is released when idleapp is invisible & memroy low
    boolean         bDialWithFirstKey;

#ifdef __NATIVE_GAME_MMI_PEDOMETER__
    IWidget         *pPedometerButtonWdg;
    IDataModel      *pButtonDataMdl;
    boolean         bPedometerDialogEnabled;
#endif /*  __NATIVE_GAME_MMI_PEDOMETER__ */

#ifdef __VIDEO_WALLPAPER__
    boolean bVideoWallpaper;
    boolean bOpenSession;
    boolean bEnableAlphaMask;
    IWidget *pBgOsdWdg;
#endif

    SetRingToneVolume_e eVolumeLevel;
    MPlayer_VolLevel_e  eMediaVolumeLevel;
    CFGItemID_e eVolumeId;//record volume dialog is created by which ap
    //boolean        bVolumeDialogEnabled;

#ifdef __APP_MMI_FM_RADIO__
    u32             nFMRadioBGPlay;
#endif /* __APP_MMI_FM_RADIO__ */
    MAE_WChar      wszCurrentWallpaperURL[FILEMGR_MAX_FILEPATH_SIZE];
    MAE_WChar      wszPreviousWallpaperURL[FILEMGR_MAX_FILEPATH_SIZE];
    boolean        bMPlayerBGPlay;
    boolean        bIsCropWallpaper;
    boolean        bAdjustingBGPlayVol; // Request to adjust MPlayer volume.

#ifdef __IDLEAPP_WALLPAPER_MMC_CACHE__
    MAE_WChar       wszCachedWallpaperURL[FILEMGR_MAX_FILEPATH_SIZE];
    boolean         bCachingToCard;
#endif /* __IDLEAPP_WALLPAPER_MMC_CACHE__ */

    FileMgrHandleID_t   nWallpaperFolderMonitorHandle;  // Handle to monitor wallpaper folder's URL
    FileMgrHandleID_t   nWallpaperFileMonitorHandle;    // Handle to monitor wallpaper file's URL

    //For Finger Command
    boolean     bChangeWallpaperByFingerCmd;
#ifndef __WIDGET_DISABLE_TRANSITION__
    boolean     bIsTransitionStart;
#endif

    ArrayClass_t        *pIWallpaperList;
    FileMgrHandleID_t   nCardHandle;
#ifdef __ONBOARD_USER_STORAGE_MMI__
    FileMgrHandleID_t   nPhoneHandle;
#endif
#ifdef __DUAL_CARD__
    FileMgrHandleID_t   nCard2Handle;
#endif
    MAE_WChar           *pNonDefaultWallpaperURL;

#ifdef __IP_CALL_MMI__
    boolean bShortPress;    // handle short press "send key"
#endif

    IAnimation *pAnimation;
#ifndef __WIDGET_DISABLE_TRANSITION__
    IWidget *pBgTransitionWdg;
#endif
    IWidget *pBgImgWdg;

#if defined(__LIVE_WALLPAPER__)
    IWidget            *pLiveWallpaperWidget;
    SetWallpaper_3DEffect_e nWallpaperType;
#endif

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__)
    IWidget *pShortcutBarShortcutWdg;
    IWidget *pShortcutBarOffButtonWdg;
    IWidget *pShortcutBarOnButtonWdg;
#endif

    boolean     bIsSelectMSCorVDC;
    boolean     bAppletActive;
#if defined(__APP_MMI_CHECKDISK__)
    boolean     bIsCheckDisk;
#endif

    boolean     bUseErrorHandleImg;

#if defined(__3D_UI_IDLE_SIMPLE__)
    IWidget         *pRotateWdg;
    IWidget         *pDesktopButWdg[IDLEAPP_SIMPLESTYLE3D_BUTTON_TOTAL];
    DesktopWdg_LaunchApp_Info_t tLaunchAppInfo;
#endif  //#if defined(__3D_UI_IDLE_SIMPLE__)

#if defined(__3D_UI_IDLE_GADGETBAR__)
    IWidget         *pDesktopDockBgWdg;
    IWidget         *pDesktopButWdg[IDLEAPP_GADGETBAR_BUTTON_TOTAL];
    DesktopWdg_LaunchApp_Info_t tLaunchAppInfo;
#endif

#if defined(__3D_UI_IDLE_MULTIPAGE__)
    boolean         bIsDesktopObjectCreating;

    IWidget         *pDesktopButWdg[IDLEAPP_MULTIPAGE_BUTTON_TOTAL];
    IWidget         *pHandoffContainer;
    IWidget         *pHandoffFocus;
    IWidget         *pHandoffNoticeLabel;
    IWidget         *pHandoffBlock[IDLEAPP_LAYOUT_MULTIPAGE_PAGE_ROW_COUNT][IDLEAPP_LAYOUT_MULTIPAGE_PAGE_COL_COUNT];
    IWidget         *pPageContainer;
    IWidget         *pButtonContainer;
    IWidget         *pButtonBgImage;
    IWidget         *pDeleteIndicatorImage;
    IWidget         *pPageIndicatorImage[IDLEAPP_LAYOUT_MULTIPAGE_PAGE_NUMBER];
    IWidget         *pPageFocusImage;
    boolean         bPageAnimating;
    u32             nPageAnimationCurrentFrame;

    IWidget         *pConfigContainer;
    IWidget         *pConfigFadeoutWdg;
    IWidget         *pConfigBackgroundWdg;
    IWidget         *pConfigTitleWdg;
    IWidget         *pConfigEntryWdg;
    IWidget         *pConfigCancelWdg;
    boolean         bShowConfigEntry;
    u32             nFocusConfigItemID;
    boolean         bIsWidgetOnHandoffOnly;
    boolean         bIsDeletingWidget;

    boolean         bTS_Press;
    s32             nTS_PressX;
    s32             nTS_PressY;

    boolean         bIsWaitingPageChange;
    s32             sPageChangePosX;
    s32             sPageChangePosY;

    // a copy pointer for IdleMultipageCalcFocusOnHandoffCB()
    IWidget         *pHandoffDesktopWidget;
    u8              nMoveDesktopWdgPage;
    boolean         bHaveHandoffFocus;

    boolean         bDragDesktopWdgVibrate;
#endif // __3D_UI_IDLE_MULTIPAGE__

#if defined (__DROPDOWN_STATUSPAGE__)
    IWidget *pStatusPageWidget;
    boolean bToShowStatusPageAfterResume;
    boolean bShowAirplanceModeWaitingDlg;
#endif

#if defined (__SCREEN_EFFECTS_SUPPORT__)
    IWidget *pScreenEffectWidget;
	WidgetHandler_t ptContainerHandle;
    SetDisplayScreenEffectType_e eScreenEffectType;
	IImage *pIScreenEffectBGImage;
#endif
	Idle_Confirm_DialogID_e eConfirmDialogID;
} MMI_IDLEAPP;

/*-------------------------------------------------------------------------*/
MAE_Ret IdleConstructor(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
MAE_Ret IdleDestructor(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean IdleStartCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean IdleStopCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean IdleSuspendCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean IdleResumeCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean IdleKeyPressCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean IdleKeyReleaseCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean IdleTouchEventCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean IdleKeyLongPressCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean IdleFingerCommandCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean IdleAppInVisibleCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);

MAE_Ret IdleWndDesktopHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _IdleWndCreateDesktop(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _IdleWndShowDesktop(void *pCusHandle, void *pWndData);
MAE_Ret _IdleWndHideDesktop(void *pCusHandle, void *pWndData);
MAE_Ret _IdleWndSetDesktop(void *pCusHandle, void *pWndData);
MAE_Ret _IdleWndDestroyDesktop(void *pCusHandle, void *pWndData);

#ifdef __DUAL_LCD__
MAE_Ret IdleSubWndDesktopHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif
MAE_Ret IdleCreateVolumeDialog(MMI_IDLEAPP *pThis, boolean bSilent, boolean bBGPlaying, CFGItemID_e eVolumeId);
MAE_Ret IdleVolumeDialogCB(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
void IdleVolumeDialogListener(void *pUserData, ModelEvent_t *pModelEvent);
void IdleVolumeDialogTimerCB(void *pUserData);
MAE_Ret IdleInfoDialogCB(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
void IdleInfoDialogTimerCB(void *pUserData);
MAE_Ret IdleCreateNormalDialog(MMI_IDLEAPP* pThis, u32 uTextId, u32 nTimerTick);
MAE_Ret IdleNormalDialogTimerCB(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);

void _IDLEAPP_DesktopButtonClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

#ifdef __2D_UI_IDLE_SIMPLE__
void IdleDateTickCB(void *pUserData);
__SLDPM_FREE__ void IdleMinuteTickCB(void *pUserData);
void IdleSysTimeChangeCB(void *pUserData, MAE_DateTime_t *pLocalTime);
void IdleSysTimeZoneChangeCB(void *pUserData, MAE_TimeZone_e ePrimaryTimeZone);
#endif

void IdleThemeChangeCB(void *pUserData);
void IdleUSBStatusIndCB(void *pUserData, MMI_USB_STATUS_E eUSBStatus);
#if defined(__APP_MMI_CHECKDISK__)
void IdleCheckDiskStatusListener(char *pSbjName, SubjectStatus_e nSbjStatus, void *pUser);
#endif

void _IdleWarningString_TimeoutCB(void *pUserData);
void _IdleWallpaperDecodeNotify(IImage *pImage, IBase *pData, ImgStatus_t nStatus);
void IdleMonitorURLCb(void *pUserData, void *pInfo);

void IdleCardWallpaperNumberUpdateCb(void *pUserData, void *pInfo);
#ifdef __ONBOARD_USER_STORAGE_MMI__
void IdlePhoneWallpaperNumberUpdateCb(void *pUserData, void *pInfo);
#endif /* __ONBOARD_USER_STORAGE_MMI__ */
#ifdef __DUAL_CARD__
void IdleCard2WallpaperNumberUpdateCb(void *pUserData, void *pInfo);
#endif /* __DUAL_CARD__ */
void IdleTransitDoneCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);
MAE_Ret IdleGetWallpaperCb(void *pUserData, u32 nIndex, MAE_WChar **pWallPaperUrl);

#if defined(__HALL_SWITCH_MMI__)
void IdleAccessoryPlugStatusCB(void *pUserData, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);
#endif

#ifdef __G_SENSOR_MMI__
void IdleSimpleActionCB(void *pUserData, SIMPLE_ACTINO_e eAction);
#endif

void IdleCleanFuncForShortcutApp(IBase *pIssuer, u32 param);

// default event handler
__SLDPM_FREE__ boolean IdleDefaultHandler(MAEEvent_t evt, u32 lParam, u32 dParam);

void IdleCloseAppletCB(IBase *pUser, u32 param);

#ifdef __MMI_COMMON_SHOW_MEDIA_NAME__
void IdlePlayingMediaNameCB(void *pUserData, MAE_WChar *pMediaName);
#endif
void IdlePlayMediaStatusCB(void *pUserData, SrvAudioPlayerPlayStatus_e ePlayStatus);

#ifdef __APP_MMI_FM_RADIO__
void IdleFMPlayStatusChangCB(void *pInstance, u32 nCusData, FmradioSrvPlayInfo_t *pPlayInfo);
void IdleFMStatusChangeCB(void *pUserData, FmradioSrvStatus_e ePlayStatus);
void IdleFMInterruptNotifyCB(u32 nCusData, u32 nEvt);
#endif

void IdleBacklightOnOffCB(void *pUserData, boolean bBackLightOn);
#ifdef __CHECK_CPU_STATUS_BEFORE_SLEEP__
void IdleFindHighSpeedTaskCB(void *pThis, HighSpeedTaskStatus_e eStatus);
#endif
void IdleNewCbMsgCB(void *pUserData, SMI_MsgID_t nMsgID);
void IdleProfileChangeCB(void *pUserData, ProfileID_e eProfileID);
void IdleSetupIdleTextCB(void *pUserData, MAE_WChar *pText, u32 nDual);
void IdleConfigItemUpdateCB(void *pUserData, SrvCfgItemStatusChangeType_e eChangeType, SrvCfgItemUpdateResult_t uResult);
void IdleTextSlideChangeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nSlideStatus, IWidget *pWidget);
void IdleNetworkRegIndCB(void *pUserData, MMI_MMSRV_RegStat_e eState, MAE_DualMode_t eDualMode);
#ifdef __GPRS_MMI__
void IdleGPRSRegStatusIndCB(void *pUserData, MMSRV_GPRSRegInd_t *pData, MAE_DualMode_t eDualMode);
#endif //__GPRS_MMI__
#if defined (__DROPDOWN_STATUSPAGE__)
void IdleCreateStatusPageWdg(void *pApplet, WidgetSize_t tStatusPageSize);
void IdleDelayDeleteStatusPageWdg(void *pApplet);
void IdleStatusPageWidgetLaunchAppCB (void *pApplet);
void IdleStatusPageWidgetCloseAnimDoneCB (void *pApplet);
#endif

#ifdef __NATIVE_GAME_MMI_PEDOMETER__
void IdleGoalReachCB(void *pUserData);
void IdleSensorStatusChangeCB(void *pUserData);
#endif

#ifdef __GADGETS_MMI__
void IdleSearchDesktopFocusChangeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, boolean bFocus, IWidget *pWidget);
void IdleIMEAssistLayoutChangeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nComponentMask, IWidget *pIWidget);
#endif

void IdleEvtCenterLogChangeCB(void *pUserData, u16 nLogNum);
void IdleLaunchAppRspCb(void *pUserData, MAE_Ret nRspCode);
void IdleLaunchOffAppRspCb(void *pUserData, MAE_Ret nRspCode);
void IdleMemSubjectSubscribeCb(char *pSubjectName, SubjectStatus_e eSubjectStatus, void *pUser);
boolean IdleReleaseDesktopWidgetCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
#if defined(__3D_MESSAGE_BOX__)
void _IDLEAPP_Launch3DMCA(MMI_IDLEAPP* pThis, e_MCA_MENU_BOX eEntryMenuBox);
#endif
#if defined(__LIVE_WALLPAPER__)
void _IDLEAPP_LiveWallPaper_PlayAudio(void *pUsrData1, void *pUsrData2, WidgetEvtCode_t nEvtCode, u32 dwParam, IWIDGET *pWdg);
#endif
void IdleCountDownTimerStateChangeCB(void *pThis, CountDownTimerSrv_State_e eState);

/*-------------------------------------------------------------------------*/
#endif /* __MMI_IDLEAPP_PRIV_H__ */
