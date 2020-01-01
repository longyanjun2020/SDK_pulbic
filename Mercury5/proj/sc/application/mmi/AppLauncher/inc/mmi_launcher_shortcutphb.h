#ifndef __SHORTCUTPHB_APP_H__
#define __SHORTCUTPHB_APP_H__

#include "mmi_launcher_common.h"

/// 1. EventCenter App,        APM_Mode = APM_LAUNCH_EMBEDDED,     param = CalEmbedModeInfo_t  ,Mode = CALENDAR_LAUNCH_MODE_VIEW_EVENT
/// 2. FileManager App,        APM_Mode = APM_LAUNCH_EMBEDDED,     param = CalEmbedModeInfo_t  ,Mode = CALENDAR_LAUNCH_MODE_IMPORT_EVENT
/// 3. Sea         App,        APM_Mode = APM_LAUNCH_EMBEDDED,     param = CalEmbedModeInfo_t  ,Mode = CALENDAR_LAUNCH_MODE_MONTHLY_VIEW
/// 4. Search App,             APM_Mode = APM_LAUNCH_EMBEDDED,     param = CalEmbedModeInfo_t  ,Mode = CALENDAR_LAUNCH_MODE_VIEW_EVENT
/// 5. Shortcut Srv,           APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = 0                   ,Mode = NULL


void LaunchShortcutPhbApp
(
  AppLaunchMode_e eAppLaunchMode,
  u32 nSelectedIdx,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

#endif
