#ifndef __MPLAYER_APP_H__
#define __MPLAYER_APP_H__

#include "mmi_launcher_common.h"

/// 1. Idle App,      APM_Mode = APM_LAUNCH_NORMAL, param = Mode, Mode = MPLAYER_MODE_MUSIC
/// 2. Shortcut Srv,  APM_Mode = APM_LAUNCH_NORMAL, param = NULL, Mode = MPLAYER_MODE_MUSIC
/// 3, Desktop Widget,APM_Mode = , param = , Mode =

typedef enum
{
    MPLAYER_LAUNCH_MODE_MIN = 0,
    MPLAYER_LAUNCH_MODE_NORMAL = MPLAYER_LAUNCH_MODE_MIN,
	MPLAYER_LAUNCH_MODE_MAX = MPLAYER_LAUNCH_MODE_NORMAL,
	MPLAYER_LAUNCH_MODE_INVALID,
}MPlayerAppLauchMode_e;

/// URL Format: "MPlayer://Launch?APM_Mode=%d&LaunchMode=%d"
/// No data response callback
void LaunchMPlayerApp
(
  AppLaunchMode_e eAppLaunchMode,
  MPlayerAppLauchMode_e eMPlayerLauchMode, 
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#endif
