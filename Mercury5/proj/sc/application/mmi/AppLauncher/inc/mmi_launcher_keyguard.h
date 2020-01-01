#ifndef __KEYGUARD_APP_H__
#define __KEYGUARD_APP_H__

#include "mmi_launcher_common.h"

/// 1. Idle App,      APM_Mode = APM_LAUNCH_INTERRUPTIVE|APML_ABORT_ON_INT_FAILED, Mode = KEYGUARDAPP_START_TYPE_AUTOMATIC
/// 2. Main Menu App, APM_Mode = APM_LAUNCH_INTERRUPTIVE|APML_ABORT_ON_INT_FAILED, Mode = KEYGUARDAPP_START_TYPE_AUTOMATIC
/// 3. Core Srv,      APM_Mode = APM_LAUNCH_INTERRUPTIVE|APML_ABORT_ON_INT_FAILED, Mode = KEYGUARDAPP_START_TYPE_AUTOMATIC
/// 4. ShortCut Srv,  APM_Mode = APM_LAUNCH_INTERRUPTIVE                         , Mode = KEYGUARDAPP_START_TYPE_BY_HOTKEY
///                   APM_Mode = APM_LAUNCH_INTERRUPTIVE                         , Mode = KEYGUARDAPP_START_TYPE_AUTOMATIC

typedef enum
{
	KEY_GUARD_LAUNCH_MODE_MIN = 0,
    KEY_GUARD_LAUNCH_MODE_LOCK_BY_HOT_KEY = KEY_GUARD_LAUNCH_MODE_MIN,
#ifdef __HALL_SWITCH_MMI__
	KEY_GUARD_LAUNCH_MODE_LOCK_BY_HALL_SWITCH,
#endif
	KEY_GUARD_LAUNCH_MODE_LOCK_AUTOMATIC,
	KEY_GUARD_LAUNCH_MODE_MAX = KEY_GUARD_LAUNCH_MODE_LOCK_AUTOMATIC,
}KeyGuardLaunchMode_e;

/// URL Format: "KeyGuard://Launch?APM_Mode=%d&Mode=%d"
/// No data response callback
void LaunchKeyGuardApp
(
  AppLaunchMode_e eAppLaunchMode,
  KeyGuardLaunchMode_e eLaunchMode,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#endif
