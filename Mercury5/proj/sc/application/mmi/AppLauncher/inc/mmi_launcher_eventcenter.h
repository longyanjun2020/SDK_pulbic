#ifndef __EVTCENTER_APP_H__
#define __EVTCENTER_APP_H__

#include "mmi_launcher_common.h"

/// 1. Idle App,          APM_Mode = APM_LAUNCH_NORMAL,       param = Mode, Mode = EVT_CENTER_LAUNCH_MODE_ALL_EVT_SUMMARY
/// 2. Shortcut Srv,      APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = Mode, Mode = EVT_CENTER_LAUNCH_MODE_ALL_EVT_SUMMARY
///                                                           param = Mode, Mode = EVT_CENTER_LAUNCH_MODE_IDLE_EVT_SUMMARY

typedef enum
{
	EVT_CENTER_LAUNCH_MODE_MIN = 0,
	EVT_CENTER_LAUNCH_MODE_ALL_EVT_SUMMARY = EVT_CENTER_LAUNCH_MODE_MIN, 
	EVT_CENTER_LAUNCH_MODE_IDLE_EVT_SUMMARY, 
	EVT_CENTER_LAUNCH_MODE_SYSTEM_EVT_VIEWER, 
	EVT_CENTER_LAUNCH_MODE_MAX = EVT_CENTER_LAUNCH_MODE_SYSTEM_EVT_VIEWER,
}EvtCenterLaunchMode_e;

/// 1. 2.
/// URL Format: "EvtCenter://Launch?APM_Mode=%d&StartMode=%d"
/// No data response callback
void LaunchEvtCenterApp
(
  AppLaunchMode_e eAppLaunchMode,
  EvtCenterLaunchMode_e eLaunchMode, 
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspInfo
);

#endif
