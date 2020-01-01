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
 * @file    mmi_settingapp_util_priv.h
 *
 * @version $Id: mmi_settingapp_util_priv.h 39456 2009-09-04 10:51:16Z lena.lin $
 */

#ifndef __MMI_SETTINGAPP_UTIL_PRIV_H__
#define __MMI_SETTINGAPP_UTIL_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_settingapp.h"
#include "mmi_settingapp_priv.h"
#include "mmi_cfgsrv.h"
#include "mmi_previewline2srv.h"


#include "mmi_srv_header.h"
#include "mmi_wdg_headers.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define AUTO_POWER_ON_OFF_MIN_DIFFER_MINUTES 5
#define AUTO_POWER_ON_OFF_MIN_ROUND_DIFFER_MINUTES ((24 * 60) - 5)

#define LAST_HOUR_PER_DAY 23
#define MINUTES_PER_HOUR 60
#define START_PLAY_POSITION 0

#define SETTINGAPP_VOLUME_RETRY_TIMER (200)
#define SETTINGAPP_VOLUME_RETRY_COUNT (10)

#define SETTINGAPP_VOLUME_DELAY_STOP_AUDIO_TIME  1500

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef struct
{
    MenuItemId_e    eMenuItemID;
    u16             u16ViewID;
} GRBLViewInfo_t;

typedef enum
{
    eCurrentValue,
    eNextValue
} UpdateLine2Value_e;

#ifdef __MULTI_THEMES_ENABLED__
typedef struct
{
	u32 eThemeId;
	u16 *pThemeName;
} MAE_ThemeData_t;
#endif

/*=============================================================*/
// Local function definition
/*=============================================================*/

void _SettingAppCheckMenuItemType(SettingAppData_t* pThis);
void _SettingAppLaunchWallpaperFileManager(SettingAppData_t* pThis, MenuItemId_e eMenuItemID, CFGItemID_e eCFGItemID, u32 nSelectedID);

void _SettingAppLaunchFileManager(SettingAppData_t* pThis, MenuItemId_e eMenuItemID, CFGItemID_e eCFGItemID, u32 nSelectedID);

/***************************************************************************************************************
* Common Utility
****************************************************************************************************************/
MAE_Ret _SettingAppMasterRestoreInfoDialogTimeout_CB(void *pData, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
boolean SettingAppShowDialogIfNotAllowed(SettingAppData_t *pThis, MenuItemId_e eSettingMenuID);
#ifdef __AUTO_ROTATE_DISPLAY__
void _SettingAppAutoRotateCheck(void);
#endif
/***************************************************************************************************************
* Preview Menu List Related Function
****************************************************************************************************************/
void _SettingAppSdStatusChangeOperation(SettingAppData_t *pThis);
//due to DB can't ready immediately when SD inserted,
//so the following function can't update the data correctly when SD inserted
void _SettingAppResetFileMgrRelatedItemInfo(SettingAppData_t *pThis);
void _SettingAppPmlUpdateModelItemLine2Text(SettingAppData_t *pThis, u32 u32FocusIndex, UpdateLine2Value_e eValueIndex);
void _SettingAppAccessorySetPlugStatusChangeCb(void *pUserData, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);
#ifdef __USB_MMI_NON_BLOCKING_USAGE__
void _SettingAppUsbStatusChangedCb(void *pApplet, MMI_USB_STATUS_E eUsbStatus);
#endif
#if defined(__APP_MMI_CHECKDISK__)
void _SettingAppCheckDiskStatusListener(char *pSbjName, SubjectStatus_e nSbjStatus, void *pUser);
#endif
void _SettingAppCfgItemUpdateIndCb(void *pApplet, SrvCfgItemStatusChangeType_e IndType, SrvCfgItemUpdateResult_t tresult);
void _SettingAppFreePMLModelItemLine2(SettingAppData_t *pThis);
void _SettingAppPmlVectorItemFree(void *pItemData, void *pUseData);
MAE_Ret _SettingAppPmlPushMenuHistory(SettingAppData_t *pThis, SettingAppPMLHistoryData_t *pstMMIPMLHistoryData);
MAE_Ret _SettingAppPmlPopMenuHistory(SettingAppData_t *pThis, SettingAppPMLHistoryData_t **ppstMMIPMLHistoryData);
boolean _SettingAppPmlHaveMenuHistory(SettingAppData_t *pThis);
void _SettingAppPreviewMenuListViewModelListener(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

/***************************************************************************************************************
* Generic Radio Button List Related Function
****************************************************************************************************************/
void _SettingAppGenericRadioButtonListViewModelListener(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

#ifdef __LIVE_WALLPAPER__
/***************************************************************************************************************
* Effect select Radio Button List  Function
****************************************************************************************************************/
void _SettingAppEffectSelectRadioListListener(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _SettingAppWallpaperOptionMenuSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _SettingAppEffectLoopNext(SettingAppData_t *pThis, boolean bForward);
void SettingAppLiveWallpaperPreviewSave(SettingAppData_t *pThis);
MAE_Ret SettingAppLiveWallpaperPreviewExitWithoutSaveDialogCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
MAE_Ret SettingAppLiveWallpaperPreviewExitWithoutSaveEndKeyDialogCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
void SettingAppLiveWallpaperContentChanged(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bChanged, void *pReserve);
#endif

/***************************************************************************************************************
* Theme style select Radio Button List  Function
****************************************************************************************************************/
#ifdef __MULTI_THEMES_ENABLED__
void _SettingAppChangeThemeFocusChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pReserve);
MAE_Ret _SettingAppLoadChangeThemeMenuItem(SettingAppData_t *pThis, IWidget *pIMenuWdg);
void _SettingAppChangeThemeSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _SettingAppFreeThemeItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
MAE_Ret _SettingAppUseThemeWallpaperDialogCB(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret _SettingAppChangingThemeDialogCB(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret _SettingAppThemeChangedDialogCB(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret _SettingAppExitTheme(void *pApplet);
MAE_Ret _SettingAppShowChangeThemeErrorDialog(void *pApplet);
MAE_Ret _SettingAppUseThemeWallpaper(void);
MAE_Ret _SettingAppChangeToDefaultTheme(void *pApplet);
#endif
/***************************************************************************************************************
* Volume Utility
****************************************************************************************************************/
void _SettingAppStartPlayVolMelody(void *pData);
void _SettingAppStopPlayVolMelody(SettingAppData_t *pThis,  SettingAppVolume_t *pData);
void _SettingAppRestoreVolume(SettingAppData_t *pThis);
void _SettingAppSetVolume(SettingAppData_t *pThis, u32 u32VolumeLevel);
MAE_Ret _SettingAppSaveVolume(SettingAppData_t *pThis);
void _SettingAppVolumeViewModelListener(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nCurrentLevel,IWidget *pWidget);
void _SettingAppVolumeViewInterruptCb(void *pUserData, u32 nCusData, MediaSrvInterruptStatus_e eStatus);
void _SettingAppPlayVolMelodyCb(void *pApplet, MediaSrvErrCode_e eErrorCode);
void _SettingAppStopPlayVolMelodyCb(void *pApplet, MediaSrvErrCode_e eErrorCode);
void _SettingAppVolMelodyPlayStatusCb(void *pApplet, u32 nCusData, AudioSrvPlayStatusEvent_e eEventId, u32 nInfoData);
/***************************************************************************************************************
* Back light Utility
****************************************************************************************************************/
MAE_Ret _SettingAppSetBkLLevel(SettingAppData_t *pThis, s16 s8BKLLevelIndex);
MAE_Ret _SettingAppSaveBkLLevel(SettingAppData_t *pThis);
void _SettingAppBacklightIncButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void _SettingAppBacklightDecButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);

/***************************************************************************************************************
* Font Style Utility
****************************************************************************************************************/
#ifdef __FEATURE_FONT_STYLE__
MAE_Ret _SettingAppLoadFontStyleMenuItem(SettingAppData_t *pThis, IWidget *pIMenuWdg);
void _SettingAppFontStyleSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif

/***************************************************************************************************************
* Display Language Utility
****************************************************************************************************************/
MAE_Ret _SettingAppLoadDisplayLangMenuItem(SettingAppData_t *pThis, IWidget *pIMenuWdg);
void _SettingAppDisplayLanguageSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

/***************************************************************************************************************
* Writing Language Utility
****************************************************************************************************************/
MAE_Ret _SettingAppLoadWritingLangMenuItem(SettingAppData_t *pThis, IWidget *pIMenuWdg);
void _SettingAppWritingLanguageSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

/***************************************************************************************************************
* Default Input Method Utility
****************************************************************************************************************/
MAE_Ret _SettingAppLoadDefaultInputMethodMenuItem(SettingAppData_t *pThis, IWidget *pIMenuWdg);
void _SettingAppDefaultInputMethodSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

/***************************************************************************************************************
* Encoding Method Utility
****************************************************************************************************************/
MAE_Ret _SettingAppLoadEncodingMenuItem(SettingAppData_t *pThis, IWidget *pIMenuWdg);
void _SettingAppEncodingSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

/***************************************************************************************************************
* Layout Utility
****************************************************************************************************************/
#ifndef __APP_MMI_SMALLROM__
MAE_Ret _SettingAppLoadLayoutMenuItem(SettingAppData_t *pThis, MenuItemId_e eMenuId, IWidget *pIMenuWdg);
void _SettingAppLayoutSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif
/***************************************************************************************************************
* Date Time Utility
****************************************************************************************************************/
void _SettingAppResetAutoOnOffAlarm(SettingAppData_t *pThis);
void _SettingAppTimeMflFocusSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, MFLFocusData_t *pMFLFocusData, IWidget *pWidget);
void _SettingAppDateMflFocusSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, MFLFocusData_t *pMFLFocusData, IWidget *pWidget);

#ifdef __LIVE_WALLPAPER__
MAE_Ret _SettingAppSaveEffect(SettingAppData_t *pThis);
#endif

MAE_Ret _SettingAppSaveDate(SettingAppData_t *pThis);
MAE_Ret _SettingAppSaveTime(SettingAppData_t *pThis);
boolean _SettingAppIsAutoUpdateSystemTimeAvailable(void);

// auto on/off timer status
boolean _SettingAppIsAutoOnOffTimeVaild(SettingAppData_t *pThis, MenuItemId_e eMenuId);

/***************************************************************************************************************
* Auto On/Off Time Utility
****************************************************************************************************************/
MAE_Ret _SettingAppSaveAutoOnOffTime(SettingAppData_t *pThis, MAE_DateTime_t *pstPowerOnDataTime, MAE_DateTime_t *pstPowerOffDataTime);
MAE_Ret _SettingAppSetAutoPowerOnOffTime(SetOnOff_e ePowerOnStatus, MAE_DateTime_t *pstPowerOnTime, SetOnOff_e ePowerOffStatus, MAE_DateTime_t *pstPowerOffTime);

/***************************************************************************************************************
* File Manager (Content Item) Utility
****************************************************************************************************************/
void _SettingAppWallPaperSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _SettingAppWallPaperCheckHighlightItem(SettingAppData_t *pThis);

/***************************************************************************************************************
* Input Method Utility
****************************************************************************************************************/
MAE_WChar * _SettingAppGetChineseInputString(SettingAppData_t *pThis, u32 nIndex);

/***************************************************************************************************************
* Master Reset
****************************************************************************************************************/
void _SettingAppMasterRestoreWaitingCB(void *data);
void _SettingAppRemoveMasterRestoreWatingDialog(SettingAppData_t *pThis);
void _SettingAppMasterRestoreInfoSafetyCB(void *pData);
void _SettingAppMasterRestoreResetInfo(SettingAppData_t *pThis);


/***************************************************************************************************************
* Theme Adapt get
****************************************************************************************************************/
void _SettingAppThemeGetItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);
void _SettingAppThemeFreeItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, void *pOwner, WdgMenuItemType_e eItemType);
void _SettingAppThemeOptSoftkeyActCB(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

/***************************************************************************************************************
* Power Switch
****************************************************************************************************************/
#ifdef __SETTING_DUAL_BATTERY__
void _SettingAppPlugStatusChangeCb(void *pApplet, MAEBatteryID_e eBatID, boolean ePlugBattStatus);
void _SettingAppCurrBattChangeCb(void *pApplet, MAEBatteryID_e eBatID);
void _SettingAppPowerSwitchSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif

MAE_Ret _PowerOnOffTooCloseWarningDlgCB(void * pData, u32 nEvt, u32 param1, u32 param2);

#endif //__MMI_SETTINGAPP_UTIL_PRIV_H__
