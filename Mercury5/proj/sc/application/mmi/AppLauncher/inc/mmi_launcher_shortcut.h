#ifndef __SHORTCUT_APP_H__
#define __SHORTCUT_APP_H__

#ifdef __APP_MMI_SHORTCUT__

#include "mmi_launcher_common.h"

/// 1. Call setting App,        APM_Mode = APM_LAUNCH_NORMAL,        param = ShortcutsEntryParamInfo_t, Mode = SHORTCUTS_LAUNCH_MODE_SPEED_DIAL,       eDynaLinkType = NULL, pParamData = NULL
/// 2. Dialer App,              APM_Mode = APM_LAUNCH_NORMAL,        param = ShortcutsEntryParamInfo_t, Mode = SHORTCUTS_LAUNCH_MODE_NUM_KEY,          eDynaLinkType = NULL, pParamData = pnKeyCode
/// 3. Idle App,                APM_Mode = APM_LAUNCH_NORMAL,        param = ShortcutsEntryParamInfo_t, Mode = SHORTCUTS_LAUNCH_MODE_NUM_KEY,          eDynaLinkType = NULL, pParamData = pnKeyCode
/// 4. Setting App,             APM_Mode = APM_LAUNCH_NORMAL,        param = ShortcutsEntryParamInfo_t, Mode = SHORTCUTS_LAUNCH_MODE_SPEED_DIAL,       eDynaLinkType = NULL, pParamData = NULL
///                             APM_Mode = APM_LAUNCH_NORMAL,        param = ShortcutsEntryParamInfo_t, Mode = SHORTCUTS_LAUNCH_MODE_NAVI_KEY,         eDynaLinkType = NULL, pParamData = NULL
/// 5. Shortcuts Srv,           APM_Mode = APM_LAUNCH_INTERRUPTIVE,  param = ShortcutsEntryParamInfo_t, Mode = SHORTCUTS_LAUNCH_MODE_SHORTCUTS,        eDynaLinkType = NULL, pParamData = NULL
///                             APM_Mode = APM_LAUNCH_INTERRUPTIVE,  param = ShortcutsEntryParamInfo_t, Mode = SHORTCUTS_LAUNCH_MODE_MAIN_MENU_SETTING,eDynaLinkType = NULL, pParamData = NULL

typedef enum
{
    SHORTCUTS_LAUNCH_MODE_MIN = 0,
    SHORTCUTS_LAUNCH_MODE_SHORTCUTS = SHORTCUTS_LAUNCH_MODE_MIN,
    SHORTCUTS_LAUNCH_MODE_KEY_ASSIGN,
    SHORTCUTS_LAUNCH_MODE_NUM_KEY,
    SHORTCUTS_LAUNCH_MODE_DYNA_LINK,
    SHORTCUTS_LAUNCH_MODE_MAIN_MENU_SETTING,
    SHORTCUTS_LAUNCH_MODE_NAVI_KEY,
    SHORTCUTS_LAUNCH_MODE_SPEED_DIAL,
    SHORTCUTS_LAUNCH_MODE_ICON_LIST,
    SHORTCUTS_LAUNCH_MODE_MAX = SHORTCUTS_LAUNCH_MODE_ICON_LIST,
}ShortcutsLaunchMode_e;

/// URL Format: "ShortCut://WithoutNumKey?APM_Mode=%d&StartMode=%d"
/// No data response callback
void LaunchShortcutsAppToEnterNonNumberKey
(
  AppLaunchMode_e eAppLaunchMode,
  ShortcutsLaunchMode_e eStartMode,  
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

/// URL Format: "ShortCut://WithNumKey?APM_Mode=%d&KeyCode=%d"
/// No data response callback
void LaunchShortcutsAppToEnterNumberKey
(
  AppLaunchMode_e eAppLaunchMode,
  u32 uKeyCode,  
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#endif
#endif
