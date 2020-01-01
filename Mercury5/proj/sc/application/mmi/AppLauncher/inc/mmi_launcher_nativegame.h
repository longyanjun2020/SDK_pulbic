#ifndef __NGAME_APP_H__
#define __NGAME_APP_H__

#include "mmi_launcher_common.h"

/// 1. ShortCut Srv,  APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = Mode, Mode = Native_Game_PacMan
///                   APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = Mode, Mode = Native_Game_Big2
///                   APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = Mode, Mode = Native_Game_Settings

typedef enum
{
	NATIVE_GAME_LAUNCH_MODE_MIN = 0,
	NATIVE_GAME_LAUNCH_MODE_PAC_MAN = NATIVE_GAME_LAUNCH_MODE_MIN,
	NATIVE_GAME_LAUNCH_MODE_BIG_TWO,
	NATIVE_GAME_LAUNCH_MODE_SETTING,
	NATIVE_GAME_LAUNCH_MODE_MAX = NATIVE_GAME_LAUNCH_MODE_SETTING,
}NativeGameLaunchMode_e;

/// URL Format: "NativeGame://Launch?APM_Mode=%d&StartMode=%d"
/// No data response callback
void LaunchNativeGameApp
(
  AppLaunchMode_e eAppLaunchMode,
  NativeGameLaunchMode_e eLaunchMode,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#endif
