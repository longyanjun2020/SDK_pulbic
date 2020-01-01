/*****************************************************************************************
* @settingapp_view.h
*
* Comment:
*
* @version:0.0.2  @ 2009.12.01
*****************************************************************************************/
#ifndef __settingapp_view__H
#define __settingapp_view__H

#include "mmi_settingapp_priv.h"
#include "mmi_common_cfg.h"
#include "mmi_coresrv.h"

typedef struct
{
    IWidget *pPMLIMenuWdg;
    IWidget *pIPhoneMenuWidget;
    IWidget *pIConnectMenuWidget;
    IWidget *pITabWidget;
    IWidget *pITitleWidget;
} SettingAppMainListViewWdgList_t;

MAE_Ret SettingAppCreateMainListView(HWIN hWin, SettingAppMainListViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppPersonalizationViewWdgList_t;

MAE_Ret SettingAppCreatePersonalizationView(HWIN hWin, SettingAppPersonalizationViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppDisplayViewWdgList_t;

MAE_Ret SettingAppCreateDisplayView(HWIN hWin, SettingAppDisplayViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppRingToneViewWdgList_t;

MAE_Ret SettingAppCreateRingToneView(HWIN hWin, SettingAppRingToneViewWdgList_t *pWdgList);
#ifdef __USER_DEFINE_POWERONOFF_MELODY__
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppPowerOnRingToneViewWdgList_t;

MAE_Ret SettingAppCreatePowerOnRingToneView(HWIN hWin, SettingAppPowerOnRingToneViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppPowerOffRingToneViewWdgList_t;

MAE_Ret SettingAppCreatePowerOffRingToneView(HWIN hWin, SettingAppPowerOffRingToneViewWdgList_t *pWdgList);
#endif
//*******************************************************************//
typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppVoiceCallViewWdgList_t;

MAE_Ret SettingAppCreateVoiceCallView(HWIN hWin, SettingAppVoiceCallViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppMessageViewWdgList_t;

MAE_Ret SettingAppCreateMessageView(HWIN hWin, SettingAppMessageViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppCalendarViewWdgList_t;

MAE_Ret SettingAppCreateCalendarView(HWIN hWin, SettingAppCalendarViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppAlarmViewWdgList_t;

MAE_Ret SettingAppCreateAlarmView(HWIN hWin, SettingAppAlarmViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppTransitionViewWdgList_t;

MAE_Ret SettingAppCreateTransitionView(HWIN hWin, SettingAppTransitionViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppThemeViewWdgList_t;

MAE_Ret SettingAppCreateThemeView(HWIN hWin, SettingAppThemeViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppBackLightViewWdgList_t;

MAE_Ret SettingAppCreateBackLightView(HWIN hWin, SettingAppBackLightViewWdgList_t *pWdgList);
//*******************************************************************//

#ifdef __APP_MMI_SCREENSAVER__
typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppScreensaverViewWdgList_t;

MAE_Ret SettingAppCreateScreensaverView(HWIN hWin, SettingAppScreensaverViewWdgList_t *pWdgList);
#endif
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppDateTimeViewWdgList_t;

MAE_Ret SettingAppCreateDateTimeView(HWIN hWin, SettingAppDateTimeViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppTimeZoneViewWdgList_t;

MAE_Ret SettingAppCreateTimeZoneView(HWIN hWin, SettingAppTimeZoneViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppSecondTimeViewWdgList_t;

MAE_Ret SettingAppCreateSecondTimeView(HWIN hWin, SettingAppSecondTimeViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppPowerOnOffViewWdgList_t;

MAE_Ret SettingAppCreatePowerOnOffView(HWIN hWin, SettingAppPowerOnOffViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppAutoOnOffViewWdgList_t;

MAE_Ret SettingAppCreateAutoOnOffView(HWIN hWin, SettingAppAutoOnOffViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppInformationViewWdgList_t;

MAE_Ret SettingAppCreateInformationView(HWIN hWin, SettingAppInformationViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppIdleScreenViewWdgList_t;

MAE_Ret SettingAppCreateIdleScreenView(HWIN hWin, SettingAppIdleScreenViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppLanguageViewWdgList_t;

MAE_Ret SettingAppCreateLanguageView(HWIN hWin, SettingAppLanguageViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pMainContainer;
    IWidget *pImgWidget;
    IWidget *pDecreaseButtonWidget;
    IWidget *pIncreaseButtonWidget;
#ifdef __SETTINGAPP_SMALLROM__
    IWidget *pMenuWidget;
    IWidget *pTextWidget;
#else
    IWidget *pTitle2Txt;
    BackLightLevelImage_t *pImage;
#endif
} SettingAppBackLightLevelViewWdgList_t;

MAE_Ret SettingAppCreateBackLightLevelView(HWIN hWin, SettingAppBackLightLevelViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
#if !defined(__SETTINGAPP_FIGURE_COMMAND_COMMAND_DATE_TIME__)
    IWidget *pMflContainer;
#endif
    IWidget *pTextDateWidget;
} SettingAppDateViewWdgList_t;

MAE_Ret SettingAppCreateDateView(HWIN hWin, SettingAppDateViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
#if !defined(__SETTINGAPP_FIGURE_COMMAND_COMMAND_DATE_TIME__)
    IWidget *pMflContainer;
#endif
    IWidget *pTextTimeWidget;
} SettingAppTimeViewWdgList_t;

MAE_Ret SettingAppCreateTimeView(HWIN hWin, SettingAppTimeViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
#ifdef __SETTINGAPP_SMALLROM__
    IWidget *pVolumeBGImageWdg;
#endif
    IWidget *pIVolumeWdg;
} SettingAppVolumeViewWdgList_t;

MAE_Ret SettingAppCreateVolumeView(HWIN hWin, SettingAppVolumeViewWdgList_t *pWdgList);
//*******************************************************************//

#ifdef __FEATURE_FONT_STYLE__
typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppFontStyleViewWdgList_t;

MAE_Ret SettingAppCreateFontStyleView(HWIN hWin, SettingAppFontStyleViewWdgList_t *pWdgList);
#endif
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppDisplayLangViewWdgList_t;

MAE_Ret SettingAppCreateDisplayLangView(HWIN hWin, SettingAppDisplayLangViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppVibrateTypeViewWdgList_t;

MAE_Ret SettingAppCreateVibrateTypeView(HWIN hWin, SettingAppVibrateTypeViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppVoiceCallsRingingTypeViewWdgList_t;

MAE_Ret SettingAppCreateVoiceCallsRingingTypeView(HWIN hWin, SettingAppVoiceCallsRingingTypeViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppMessageToneViewWdgList_t;

MAE_Ret SettingAppCreateMessageToneView(HWIN hWin, SettingAppMessageToneViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppCalendarToneViewWdgList_t;

MAE_Ret SettingAppCreateCalendarToneView(HWIN hWin, SettingAppCalendarToneViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppAlarmToneViewWdgList_t;

MAE_Ret SettingAppCreateAlarmToneView(HWIN hWin, SettingAppAlarmToneViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppBackLightDurationViewWdgList_t;

MAE_Ret SettingAppCreateBackLightDurationView(HWIN hWin, SettingAppBackLightDurationViewWdgList_t *pWdgList);
//*******************************************************************//

#ifdef __APP_MMI_SCREENSAVER__
typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppScreensaverDurationViewWdgList_t;

MAE_Ret SettingAppCreateScreensaverDurationView(HWIN hWin, SettingAppScreensaverDurationViewWdgList_t *pWdgList);
#endif
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppAutomaticUpdateViewWdgList_t;

MAE_Ret SettingAppCreateAutomaticUpdateView(HWIN hWin, SettingAppAutomaticUpdateViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppDefaultSimViewWdgList_t;

MAE_Ret SettingAppCreateDefaultSimView(HWIN hWin, SettingAppDefaultSimViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppDateFormatViewWdgList_t;

MAE_Ret SettingAppCreateDateFormatView(HWIN hWin, SettingAppDateFormatViewWdgList_t *pWdgList);
//*******************************************************************//
#ifdef __DUAL_CAMERA_MMI__
typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppCameraSelectionWdgList_t;

MAE_Ret SettingAppCreateCameraSelectionView(HWIN hWin, SettingAppCameraSelectionWdgList_t *pWdgList);
//*******************************************************************//
#endif

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppMenuAnimatedStyleViewWdgList_t;

MAE_Ret SettingAppCreateMenuAnimatedStyleView(HWIN hWin, SettingAppMenuAnimatedStyleViewWdgList_t *pWdgList);
//*******************************************************************//
#ifdef __MULTI_THEMES_ENABLED__
typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppMenuChangeThemeViewWdgList_t;

MAE_Ret SettingAppCreateMenuChangeThemeView(HWIN hWin, SettingAppMenuChangeThemeViewWdgList_t *pWdgList);
#endif
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppLayoutViewWdgList_t;

MAE_Ret SettingAppCreateLayoutView(HWIN hWin, SettingAppLayoutViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppWriteLangViewWdgList_t;

MAE_Ret SettingAppCreateWriteLangView(HWIN hWin, SettingAppWriteLangViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppDefaultInputMethodViewWdgList_t;

MAE_Ret SettingAppCreateDefaultInputMethodView(HWIN hWin, SettingAppDefaultInputMethodViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppEncodingViewWdgList_t;

MAE_Ret SettingAppCreateEncodingView(HWIN hWin, SettingAppEncodingViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppFileMgrImageViewWdgList_t;

MAE_Ret SettingAppCreateFileMgrImageView(HWIN hWin, SettingAppFileMgrImageViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppFileMgrMelodyViewWdgList_t;

MAE_Ret SettingAppCreateFileMgrMelodyView(HWIN hWin, SettingAppFileMgrMelodyViewWdgList_t *pWdgList);
//*******************************************************************//
#if defined (__USER_DEFINE_MAINMENU_VIDEO__) || (!defined (__USER_DEFINE_POWERONOFF_ANIM__) && defined(__USER_DEFINE_POWERONOFF_VIDEO__))
MAE_Ret SettingAppCreateFileMgrVideoView(HWIN hWin, SettingAppFileMgrImageViewWdgList_t *pWdgList);
#endif
//*******************************************************************//
#ifdef __SETTING_DUAL_BATTERY__
typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppPowerSwitchViewWdgList_t;

MAE_Ret SettingAppCreatePowerSwitchView(HWIN hWin, SettingAppPowerSwitchViewWdgList_t *pWdgList);
#endif
//*******************************************************************//
#ifdef __G_SENSOR_MMI__
typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppGSensorViewWdgList_t;

MAE_Ret SettingAppCreateGSensorView(HWIN hWin, SettingAppGSensorViewWdgList_t *pWdgList);
#endif
//*******************************************************************//
#ifdef __LIVE_WALLPAPER__
typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppEffectSelectViewWdgList_t;

MAE_Ret SettingAppCreateEffectSelectView(HWIN hWin, SettingAppEffectSelectViewWdgList_t *pWdgList);
//*******************************************************************//
typedef struct
{
    IWidget *pWallpaperEffectWdg;
    u32 nMenuItemSelected;
} SettingAppLiveWallpaperPreview_t;
MAE_Ret SettingAppCreateLiveWallpaperPreviewView(HWIN hWin, SettingAppLiveWallpaperPreview_t *pWdgList);
//*******************************************************************//
typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppLiveWallpaperOption_t;
MAE_Ret SettingAppCreateLiveWallpaperOptionView(HWIN hWin, SettingAppLiveWallpaperOption_t *pWdgList);
//*******************************************************************//
typedef struct
{
    IWidget *pImgWidget;
} SettingAppImgWallpaperPreview_t;
MAE_Ret SettingAppCreateImgWallpaperPreviewView(HWIN hWin, SettingAppImgWallpaperPreview_t *pWdgList);
#endif
//*******************************************************************//

#ifdef __SCREEN_EFFECTS_SUPPORT__
typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppScreenEffectViewWdgList_t;
MAE_Ret SettingAppCreateScreenEffectView(HWIN hWin, SettingAppScreenEffectViewWdgList_t *pWdgList);
typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppScreenEffectTypeViewWdgList_t;

MAE_Ret SettingAppCreateScreenEffectTypeView(HWIN hWin, SettingAppScreenEffectTypeViewWdgList_t *pWdgList,u32 nISPopUpStyle);
#ifdef __SCREEN_EFFECT_SNOW_SUPPORT__
typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pITitleWidget;
} SettingAppScreenEffectSnowViewWdgList_t;

MAE_Ret SettingAppCreateScreenEffectSnowView(HWIN hWin, SettingAppScreenEffectSnowViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppScreenEffectSnowSpeedViewWdgList_t;

MAE_Ret SettingAppCreateScreenEffectSnowSpeedView(HWIN hWin, SettingAppScreenEffectSnowSpeedViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppScreenEffectSnowNumViewWdgList_t;

MAE_Ret SettingAppCreateScreenEffectSnowNumView(HWIN hWin, SettingAppScreenEffectSnowNumViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppScreenEffectSnowBigNumViewWdgList_t;

MAE_Ret SettingAppCreateScreenEffectSnowBigNumView(HWIN hWin, SettingAppScreenEffectSnowBigNumViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppScreenEffectSnowBlowDirViewWdgList_t;

MAE_Ret SettingAppCreateScreenEffectSnowBlowDirView(HWIN hWin, SettingAppScreenEffectSnowBlowDirViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppScreenEffectSnowBlowTimeViewWdgList_t;

MAE_Ret SettingAppCreateScreenEffectSnowBlowTimeView(HWIN hWin, SettingAppScreenEffectSnowBlowTimeViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppScreenEffectSnowPileSpeedViewWdgList_t;

MAE_Ret SettingAppCreateScreenEffectSnowPileSpeedView(HWIN hWin, SettingAppScreenEffectSnowPileSpeedViewWdgList_t *pWdgList);
//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
} SettingAppScreenEffectSnowColorViewWdgList_t;

MAE_Ret SettingAppCreateScreenEffectSnowColorView(HWIN hWin, SettingAppScreenEffectSnowColorViewWdgList_t *pWdgList);
#endif // __SCREEN_EFFECT_SNOW_SUPPORT__
#endif // __SCREEN_EFFECTS_SUPPORT__
//*******************************************************************//

void _SettingAppDeleteMenuItem(IWidget *pMenuWdg, u32 u32MenuId);
void _SettingAppGetMenuModelData(SettingAppData_t* pThis, u32 u32ItemID, u32 *pU32MenuSize, WdgMenuItemText_t **ppMenuTitle, WdgDynamicMenuItemInf_t **ppMenuItem);
void _SettingAppDisableDownWidgetBG(HWIN hWin, IWidget *pMenuWdg);

//*******************************************************************//
#endif //__settingapp_view__H
