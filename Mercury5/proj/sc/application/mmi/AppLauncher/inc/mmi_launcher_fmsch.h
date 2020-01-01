#ifndef __FMSCH_APP_H__
#define __FMSCH_APP_H__

#include "mmi_launcher_common.h"

/// 1. Fm Schedule App,         APM_Mode = APM_LAUNCH_INTERRUPTIVE,  param = FMSCHAPP_START_TYPE_FM_SCHEDULE,           Mode = NULL
/// 2. Fm Schedule Record App,  APM_Mode = APM_LAUNCH_INTERRUPTIVE,  param = FMSCHAPP_START_TYPE_FM_SCHEDULE_RECORD,    Mode = NULL

/// 1.
/// Launch Fm Schedule App
/// 
/// URL Format: "FmSch://LaunchFmSch?APM_Mode=%d&Type=%d"
/// No data response callback
void LaunchFmSchApp
(
  AppLaunchMode_e eAppLaunchMode, 
  CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

/// 2.
/// Launch Fm Schedule Record App
/// 
/// URL Format: "FmSch://LaunchFmSchRec?APM_Mode=%d&Type=%d"
/// No data response callback
void LaunchFmSchRecApp
(
  AppLaunchMode_e eAppLaunchMode, 
  CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

#endif/* __FMSCH_APP_H__ */
