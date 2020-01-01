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
* @file mmi_settingapp_priv.h
*
* Class Id: CLSID_SETTINGAPP
*
* @version $Id: mmi_settingapp_priv.h 39672 2009-09-08 11:18:35Z jorena.ku $
*/
#ifndef __MMI_SETTINGAPP_PRIV_H__
#define __MMI_SETTINGAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/


#include "mmi_settingapp.h"
#include "mmi_baseapplet.h"

//MAE
//Service
#include "mmi_common_cfg.h"
#include "mmi_previewline2srv.h"
//VIEW
#include "mmi_settingapp_view_id.h"
//Widget
//Model
#include "mmi_base_util.h"


#include "mmi_common_vtm.h"
#include "mmi_settingapp_id.h"
#include "mmi_settingapp_rs.h"
#include "mmi_common_setting_type.h"
//#include "settingapp_resource.h"

#if !defined(__SDK_SIMULATION__)
#include "mdl_gpd_pub.h"
#endif

#include "mmi_launcher_security.h"
#include "mmi_usbsrv.h"

#if defined(__LIVE_WALLPAPER__)
#include "mmi_wdg_wallpaper.h"
#endif

#include "mmi_common_encoding.h"
/*=============================================================*/
// Macro definition
/*=============================================================*/

#ifndef ARR_SIZE
#define ARR_SIZE(a)  (sizeof((a))/sizeof((a[0])))
#endif

//Preview Menu List Data

#define SETTINGAPP_DIALOG_TIMER           1000

#if defined(__TOUCH_SCREEN_MMI__) && !defined(__WIDGET_DISABLE_FINGERCOMMAND__)
#define __SETTINGAPP_FIGURE_COMMAND_COMMAND_DATE_TIME__
#endif

#define SET_WRITE_DEFAULT_LANG_TO_SIM (FALSE)

/*=============================================================*/
// Data type definition
/*=============================================================*/

#define BACKLIGHTLEVELSIZE 7

typedef struct
{
    u32 aImage[BACKLIGHTLEVELSIZE];
}BackLightLevelImage_t;

typedef struct
{
    u16 u16ItemID;
    u32 u32LogFirstItemIndex;
    u32 u32LogHighlightIndex;

} SettingAppPMLHistoryData_t;

typedef enum
{
    SET_POWER_ON_TIME_WDG,
    SET_POWER_OFF_TIME_WDG
} SettingAppPowerOnOffTime_e;

typedef struct
{
#ifdef __SETTINGAPP_SMALLROM__
    IWidget                 *pBKLTextWdg;
#endif
    IWidget                 *pBKLLevelImageWdg;
    IVectorModel            *pBKLIVectorModel;
    LCDSrv_BacklightLevel_e eDisplayBKLLevel;
    IWidget                 *pIIncButtonWidget;
    IWidget                 *pIDecButtonWidget;
    BackLightLevelImage_t   *pImage;
} SettingAppBKLLevel_t;

#ifdef __FEATURE_FONT_STYLE__
typedef struct
{
    IWidget         *pFontStyleIMenuWdg;
    boolean         bChangeFontIng;
	s32             nPreHlightIndex;
} SettingAppFontStyle_t;
#endif

typedef struct
{
    IWidget         *pLANGIMenuWdg;
    MAE_LANG_CODE_e eCurLangCode;
} SettingAppDisplayLang_t;

#ifdef __MULTI_THEMES_ENABLED__
typedef struct
{
	IWidget         *pThemeMenuWdg;
	u32				eCurThemeId;
	u32				eOriginalThemeId;
	u32             *aSettingValue;
} SettingAppChangeTheme_t;
#endif

typedef struct
{
    IWidget         *pLANGIMenuWdg;
    MAE_LANG_CODE_e eCurLangCode;
} SettingAppWritingLang_t;

typedef struct
{
    IWidget         *pDIMIMenuWdg;
} SettingAppDefaultInputMethod_t;

typedef struct
{
	IWidget *pEncodingIMenuWdg;
	Common_Encoding_StringType_e eCurEncoding;
} SettingAppEncodingMethod_t;

#ifndef __APP_MMI_SMALLROM__
typedef struct
{
    IWidget         *pLayoutIMenuWdg;
    u8              u8CurrentLayoutSetting;
} SettingAppLayout_t;
#endif

typedef struct
{
	IWidget         *pTextWdg;
} SettingAppInfoIMEI_t;

typedef struct
{
	IWidget         *pTextWdg;
} SettingAppInfoSWVersion_t;

typedef struct
{
    u32             nThemeNameID;
} SettingAppTheme_t;

#ifdef __SETTINGAPP_FIGURE_COMMAND_COMMAND_DATE_TIME__          //Figure Command __TOUCH_SCREEN_MMI__
typedef struct
{
    IWidget     *pIDateWdg;
    DateInputWdgList_t tInputWdg;
} SettingAppDate_t;
#else                                                           //__SETTINGAPP_FIGURE_COMMAND_COMMAND_DATE_TIME__
typedef struct
{
    IWidget         *pIDateWdg;
    IWidget         *pIMflContainerWidget;

} SettingAppDate_t;
#endif                                                          //Figure Command __SETTINGAPP_FIGURE_COMMAND_COMMAND_DATE_TIME__

#ifdef __SETTINGAPP_FIGURE_COMMAND_COMMAND_DATE_TIME__          //Figure Command __TOUCH_SCREEN_MMI__
//Figure Command
typedef struct
{
    IWidget     *pIFCTimeWdg;
    MenuItemId_e eMenuItemID;
    TimeInputWdgList_t tInputWdg;
} SettingAppTime_t;
#else//__SETTINGAPP_FIGURE_COMMAND_COMMAND_DATE_TIME__
typedef struct
{
    IWidget         *pITime1Wdg;
    MenuItemId_e    eMenuItemID;
} SettingAppTime_t;
#endif //__SETTINGAPP_FIGURE_COMMAND_COMMAND_DATE_TIME__

typedef struct
{
    IWidget             *pIMenuWdg;
    MenuItemId_e        eMenuItemID;
    const ContentInfo_t *pstContentInfo;
    MAE_WChar           *pURL;
} SettingAppLaunchFileMgr_t;

typedef struct
{
    MAE_WChar           *pMelodyURL; //MAE_WChar using for play ringer URL
    IWidget             *pVolWdg;
#ifdef __SETTINGAPP_SMALLROM__
	IWidget             *pVolumeTopImageWdg;
#endif
    MenuItemId_e        eMenuItemID;
    CFGItemID_e         eCFGItemID;
    u32                 nVolRetryCount;
    SetRingToneVolume_e eOrigVolLevel;
    SetRingToneVolume_e eVolLevel;
    ProfileID_e         eOrigProfileId;
    boolean             bSuspendWndClose;   //T: wnd closed by suspend, F: wnd closed normally
    boolean             bRestoreVolume;     // TRUE if we need to restore volume when closing volume window
} SettingAppVolume_t;

typedef struct
{
    IWidget         *pGRBLIMenuWdg;
    CFGInfo_t       *pGRBLstCFGInfo;
    u32             u32CFGItemValue;
} SettingAppGenericRadioButtonList_t;

typedef enum
{
    MMI_SETTINGAPP_INPUT_METHOD_NO_CHINESE_LANG_CODE = 0,
    MMI_SETTINGAPP_INPUT_METHOD_NO_CHINESE_SMART_INPUT,
    MMI_SETTINGAPP_INPUT_METHOD_NO_CHINESE_SOFT_KEYBOARD
} SettingAppInputMethodNoChinese_e;

typedef enum
{
    MMI_SETTINGAPP_INPUT_METHOD_LANG_CODE = 0,
    MMI_SETTINGAPP_INPUT_METHOD_CHINESE_INPUT,
//  MMI_SETTINGAPP_INPUT_METHOD_DEFAULT_INPUT,
    MMI_SETTINGAPP_INPUT_METHOD_SMART_INPUT,
    MMI_SETTINGAPP_INPUT_METHOD_SOFT_KEYBOARD
} SettingAppInputMethodItem_e;

#ifdef __MMI_CONNECT_SETTING__
#define SETTINGAPPTABSIZE 3
#else
#define SETTINGAPPTABSIZE 2
#endif

static u32 nImageFocusId[] =
{
    SETTINGS_IMG_TAB_GENERAL,
    SETTINGS_IMG_TAB_PHONE
#ifdef __MMI_CONNECT_SETTING__
    , SETTINGS_IMG_TAB_CONNECTION
#endif
};

typedef enum
{
    MMI_SETTINGAPP_TABVIEW_GENERAL = 0,
    MMI_SETTINGAPP_TABVIEW_PHONE,
    MMI_SETTINGAPP_TABVIEW_CONNECTION,
} SettingAppTabViewItem_e;

typedef struct
{
    APPLET_BASE_ELEMENTS;
    u16                 u16InterruptLevel;
    boolean             bEnterOtherAP;
    // Related to TabView
    VectorClass_t       *pIPMLHistoryVector;      //Preview Menu List History Vector
    IWidget             *pPMLIMenuWdg;
    IWidget             *pITabWidget;
    IWidget             *pITitleWidget;
    IWidget             *pIPhoneMenuWidget;
    IWidget             *pIConnectMenuWidget;
    u32                 u32TabFocusIdx;
    u32                 u32PhoneMenuHighlightIdx;
    u32                 u32ConnectMenuHighlightIdx;
    boolean             bLaunchHistoryMenu;
    u32                 u32FirstItemIndex;
    u32                 u32HighlightIndex;
    MAE_WChar           *pPMLPreviewLine2Buf;
    u16                 u16PMLItemID;
    WdgMenuItemType_e   PMLItemWidgetClsId;
    //Related object for Check Item Type
    MenuItemId_e        eCITMenuItemID;
    SET_NEXT_FORM_TYPE_e eCITNextFormType;
    boolean             bMasterRestoreDone;
    boolean             bMasterRestoreWaitingDone;
    u8                  nMaterRestoreResult;
    //pointer to mode structure
    CFGItemID_e 		eCFGItemID;
	//Theme List selected ID
	u16					nThemeListSelectedID;
#ifdef __LIVE_WALLPAPER__
    boolean             bChangedWallpaper;
#if defined(__3D_UI_IDLE_MULTIPAGE__)
    boolean             bIdleStyle;
#endif
#endif
#ifdef __USER_DEFINE_POWERONOFF_VIDEO__
    MAE_WChar           *pOnOffVideoUrl;
#endif
#if defined (__USER_DEFINE_MAINMENU_VIDEO__) && defined(__UI_STYLE_MMI_MAIN_MENU_ANIMATION__)
    MAE_WChar           *pMainmenuVideoUrl;
    SetDisplayMenuAnimationStyle_e eAnimStyle;
#endif
#if defined (__VIDEO_WALLPAPER__) && defined(__SCREEN_EFFECTS_SUPPORT__)
    MAE_WChar           *pIdleVideoUrl;
    SetDisplayMenuAnimationStyle_e eScreenEffect;
#endif
    boolean             bDoViewRotation;
    CmnAppLaunchRspCbInfo_t tRspCbInfo;
#ifdef __FEATURE_FONT_STYLE__
	VectorFontStyle_t   *pFontStyleInfo;     //for change ttf font from card use
	boolean             bRestoreDefaultFont; //for change ttf font from card use
#endif
} SettingAppData_t;

void _SettingAppFreeFileMgrStartData(IBase* pOwner, u32 FileMgrReqData);

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret SettingAppConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret SettingAppDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean SettingAppStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean SettingAppKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean SettingAppResumeCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean SettingAppSuspendCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
#if !defined(__SETTINGAPP_FIGURE_COMMAND_COMMAND_DATE_TIME__)
boolean SettingAppPreHookCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
#endif
boolean SettingAppPhoneLockSuccess(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean SettingAppPhoneLockCancel(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

/*=============================================================*/
// Local function definition
/*=============================================================*/

void _SettingAppJumpToPml(SettingAppData_t* pThis);


MAE_Ret _SettingAppWndCreatePreviewMenuList(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndSetPreviewMenuList(void *pCusHandle, void *pWndData);
MAE_Ret _SettingAppWndDestroyPreviewMenuList(void *pCusHandle, void *pWndData);
MAE_Ret _SettingAppWndShowPreviewMenuList(void *pCusHandle, void *pWndData);

MAE_Ret _SettingAppWndCreateVibrateType(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyVibrateType(void *pCusHandle, void *pWndData);

MAE_Ret _SettingAppWndCreateVoiceCallsRingingType(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyVoiceCallsRingingType(void *pCusHandle, void *pWndData);

MAE_Ret _SettingAppWndCreateMessageTone(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyMessageTone(void *pCusHandle, void *pWndData);

MAE_Ret _SettingAppWndCreateCalendarTone(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyCalendarTone(void *pCusHandle, void *pWndData);

MAE_Ret _SettingAppWndCreateAlarmTone(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyAlarmTone(void *pCusHandle, void *pWndData);

MAE_Ret _SettingAppWndCreateBackLightDuration(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyBackLightDuration(void *pCusHandle, void *pWndData);

#ifdef __APP_MMI_SCREENSAVER__
MAE_Ret _SettingAppWndCreateScreensaverDuration(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyScreensaverDuration(void *pCusHandle, void *pWndData);
#endif

MAE_Ret _SettingAppWndCreateAutomaticUpdate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyAutomaticUpdate(void *pCusHandle, void *pWndData);

MAE_Ret _SettingAppWndCreateDateFormat(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyDateFormat(void *pCusHandle, void *pWndData);

MAE_Ret _SettingAppWndCreateDefaultSim(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyDefaultSim(void *pCusHandle, void *pWndData);

MAE_Ret _SettingAppWndCreateMenuAnimatedStyle(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyMenuAnimatedStyle(void *pCusHandle, void *pWndData);

#ifdef __MULTI_THEMES_ENABLED__
MAE_Ret _SettingAppWndCreateMenuChangeTheme(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyMenuChangeTheme(void *pCusHandle, void *pWndData);
#endif

#ifdef __DUAL_CAMERA_MMI__
MAE_Ret _SettingAppWndCreateCameraSelection(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyCameraSelection(void *pCusHandle, void *pWndData);
#endif

#ifdef __LIVE_WALLPAPER__
MAE_Ret _SettingAppWndCreateEffectSelect(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyEffectSelect(void *pCusHandle, void *pWndData);

MAE_Ret _SettingAppWndCreateLiveWallpaperPreview(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyLiveWallpaperPreview(void *pCusHandle, void *pWndData);

MAE_Ret _SettingAppWndCreateLiveWallpaperOption(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyLiveWallpaperOption(void *pCusHandle, void *pWndData);

MAE_Ret _SettingAppWndCreateImgWallpaperPreview(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndShowImgWallpaperPreview(void *pCusHandle, void *pWndData);
MAE_Ret _SettingAppWndDestroyImgWallpaperPreview(void *pCusHandle, void *pWndData);
static void _SettingAppLiveWallPaperPlayAudio(void *pUsrData1, void *pUsrData2, WidgetEvtCode_t nEvtCode, u32 dwParam, IWIDGET *pWdg) ;
#endif

MAE_Ret _SettingAppWndCreateFileMgrImage(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyFileMgrImage(void *pCusHandle, void *pWndData);

MAE_Ret _SettingAppWndCreateVolume(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndSetVolume(void *pCusHandle, void *pWndData);
MAE_Ret _SettingAppWndDestroyVolume(void *pCusHandle, void *pWndData);

MAE_Ret _SettingAppWndCreateBKLLevel(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndSetBKLLevel(void *pCusHandle, void *pWndData);
MAE_Ret _SettingAppWndDestroyBKLLevel(void *pCusHandle, void *pWndData);

#ifdef __FEATURE_FONT_STYLE__
MAE_Ret _SettingAppWndCreateFontStyle(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyFontStyle(void *pCusHandle, void *pWndData);
#endif

MAE_Ret _SettingAppWndCreateDisplayLang(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyDisplayLang(void *pCusHandle, void *pWndData);

MAE_Ret _SettingAppWndCreateWritingLang(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyWritingLang(void *pCusHandle, void *pWndData);

MAE_Ret _SettingAppWndCreateDefaultInputMethod(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyDefaultInputMethod(void *pCusHandle, void *pWndData);

MAE_Ret _SettingAppWndCreateEncoding(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyEncoding(void *pCusHandle, void *pWndData);

MAE_Ret _SettingAppWndCreateDate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyDate(void *pCusHandle, void *pWndData);

MAE_Ret _SettingAppWndCreateTime(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyTime(void *pCusHandle, void *pWndData);
#ifndef __APP_MMI_SMALLROM__
MAE_Ret _SettingAppWndCreateLayout(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyLayout(void *pCusHandle, void *pWndData);
#endif
MAE_Ret _SettingAppWndCreateFileMgrMelody(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyFileMgrMelody(void *pCusHandle, void *pWndData);

MAE_Ret _SettingAppWndCreateThemeOpt(void *pCusHandle, void *pWndData, u32 nWndInitParam);
//MAE_Ret _SettingAppWndDestroyThemeOpt(void *pCusHandle, void *pWndData);


MAE_Ret _SettingAppWndPreviewMenuListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndVibrateTypeHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndVoiceCallsRingingTypeHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndMessageToneHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndCalendarToneHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndAlarmToneHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndBackLightDurationHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifdef __APP_MMI_SCREENSAVER__
MAE_Ret _SettingAppWndScreensaverDurationHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif
MAE_Ret _SettingAppWndAutomaticUpdateHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDateFormatHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDefaultSimHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifdef __DUAL_CAMERA_MMI__
MAE_Ret _SettingAppWndCameraSelectionHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif

#ifdef __LIVE_WALLPAPER__
MAE_Ret _SettingAppWndEffectSelectHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndLiveWallpaperPreviewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndLiveWallpaperOptionHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndImgWallpaperPreviewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif

MAE_Ret _SettingAppWndMenuAnimatedStyleHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifdef __MULTI_THEMES_ENABLED__
MAE_Ret _SettingAppWndMenuChangeThemeHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif
MAE_Ret _SettingAppWndVolumeHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndBKLLevelHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifdef __FEATURE_FONT_STYLE__
MAE_Ret _SettingAppWndFontStyleHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif
MAE_Ret _SettingAppWndDisplayLangHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndWritingLangHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDefaultInputMethodHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndEncodingHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDateHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndTimeHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifndef __APP_MMI_SMALLROM__
MAE_Ret _SettingAppWndLayoutHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif
MAE_Ret _SettingAppWndInfoIMEIHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndCreateInfoIMEI(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndConvertInfoIMEI(void *pCusHandle, void *pWndData);
MAE_Ret _SettingAppWndDestroyInfoIMEI(void *pCusHandle, void *pWndData);
MAE_Ret _SettingAppWndInfoSWVersionHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndCreateInfoSWVersion(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndConvertInfoSWVersion(void *pCusHandle, void *pWndData);
MAE_Ret _SettingAppWndDestroyInfoSWVersion(void *pCusHandle, void *pWndData);

MAE_Ret _SettingAppWndFileMgrImageHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndFileMgrMelodyHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

void _SettingAppFileMgrImageSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _SettingAppFileMgrMelodySoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void _SettingAppLaunchSecInfoCB(void *pvUserData, MAE_Ret nRspCode, SecurityLaunchRspData_t *psRspData, SecurityLaunchRspDataFreeCb pfnRspDataFreeCb);
void _SettingAppSetPopupSelLayout(HWIN hWin, IWidget *pMenuWdg);
void _SettingAppProfileChangeCB(void *pApplet, ProfileID_e eProfileID);

boolean _SettingAppIsAnySimActive(void);
boolean _SettingAppIsAllowUserSetDateTime(SettingAppData_t *pThis);

#ifdef __SCREEN_EFFECTS_SUPPORT__
MAE_Ret _SettingAppWndScreenEffectTypeHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndCreateScreenEffectType(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyScreenEffectType(void *pCusHandle, void *pWndData);
#ifdef __SCREEN_EFFECT_SNOW_SUPPORT__
MAE_Ret _SettingAppWndScreenEffectSnowSpeedHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndCreateScreenEffectSnowSpeed(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyScreenEffectSnowSpeed(void *pCusHandle, void *pWndData);
MAE_Ret _SettingAppWndScreenEffectSnowNumHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndCreateScreenEffectSnowNum(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyScreenEffectSnowNum(void *pCusHandle, void *pWndData);
MAE_Ret _SettingAppWndScreenEffectSnowBigNumHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndCreateScreenEffectSnowBigNum(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyScreenEffectSnowBigNum(void *pCusHandle, void *pWndData);
MAE_Ret _SettingAppWndScreenEffectSnowBlowDirHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndCreateScreenEffectSnowBlowDir(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyScreenEffectSnowBlowDir(void *pCusHandle, void *pWndData);
MAE_Ret _SettingAppWndScreenEffectSnowBlowTimeHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndCreateScreenEffectSnowBlowTime(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyScreenEffectSnowBlowTime(void *pCusHandle, void *pWndData);
MAE_Ret _SettingAppWndScreenEffectSnowPileSpeedHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndCreateScreenEffectSnowPileSpeed(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyScreenEffectSnowPileSpeed(void *pCusHandle, void *pWndData);
MAE_Ret _SettingAppWndScreenEffectSnowColorHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndCreateScreenEffectSnowColor(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _SettingAppWndDestroyScreenEffectSnowColor(void *pCusHandle, void *pWndData);
#endif // __SCREEN_EFFECT_SNOW_SUPPORT__
#endif // __SCREEN_EFFECTS_SUPPORT__
#if defined (__USER_DEFINE_MAINMENU_VIDEO__) && defined(__UI_STYLE_MMI_MAIN_MENU_ANIMATION__)
MAE_Ret _SettingAppMainmenuDlgHdl(void *pIApplet, MAEEvent_t evtId, u32 param1, u32 param2);
MAE_Ret _SettingAppMainmenuAnimDlgHdl(void *pIApplet, MAEEvent_t evtId, u32 param1, u32 param2);
#endif
#if defined (__VIDEO_WALLPAPER__) && defined(__SCREEN_EFFECTS_SUPPORT__)
MAE_Ret _SettingAppIdleDlgHdl(void *pIApplet, MAEEvent_t evtId, u32 param1, u32 param2);
MAE_Ret _SettingAppIdleEffectDlgHdl(void *pIApplet, MAEEvent_t evtId, u32 param1, u32 param2);
#endif


#endif /* __MMI_SETTINGAPP_PRIV_H__ */
