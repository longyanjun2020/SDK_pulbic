#ifndef __ON_APP_H__
#define __ON_APP_H__

#include "mmi_launcher_common.h"


/// 1. mmi_main.c, APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = OnAppStart_t, Mode = ON_LAUNCH_MODE_CHARGER
///                APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = OnAppStart_t, Mode = ON_LAUNCH_MODE_ALARM
///                APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = OnAppStart_t, Mode = ON_LAUNCH_MODE_RESET
///                APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = OnAppStart_t, Mode = ON_LAUNCH_MODE_TIME_EVT
///                APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = OnAppStart_t, Mode = ON_LAUNCH_MODE_POWER_CUT
///                APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = OnAppStart_t, Mode = ON_LAUNCH_MODE_SW_RESET
///                APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = OnAppStart_t, Mode = ON_LAUNCH_MODE_SIM_RESET
///                APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = OnAppStart_t, Mode = ON_LAUNCH_MODE_OTHER


typedef enum
{
	ON_LAUNCH_MODE_MIN = 0,
	ON_LAUNCH_MODE_UNKNOW = ON_LAUNCH_MODE_MIN,
	ON_LAUNCH_MODE_NORMAL,
	ON_LAUNCH_MODE_AUTO,
	ON_LAUNCH_MODE_ALARM,
	ON_LAUNCH_MODE_CHARGING,
	ON_LAUNCH_MODE_CHARGING_NOANIM,
	ON_LAUNCH_MODE_POWER_CUT,
	ON_LAUNCH_MODE_ATCOMMAND,
	ON_LAUNCH_MODE_STK_REFRESH,
	ON_LAUNCH_MODE_RESET,
	ON_LAUNCH_MODE_TIMEEVT,
	ON_LAUNCH_MODE_SW_RESET,
	ON_LAUNCH_MODE_NORMAL_KEY_RELEASE,
	ON_LAUNCH_MODE_OTHER,
	ON_LAUNCH_MODE_MAX = ON_LAUNCH_MODE_OTHER,
}OnLaunchMode_e;

typedef struct
{
    OnLaunchMode_e eLaunchMode;
	union
	{
		u32 uAlarmEvtCode; /// eLaunchMode == ON_LAUNCH_MODE_ALARM
	}LaunchData_t;
}OnLaunchData_t;

/// URL Format: "On://Launch?APM_Mode=%d&StartMode=%d&AlarmEvtCode=%d"
/// No data response callback
void LaunchOnApp
(
  AppLaunchMode_e eAppLaunchMode,
  OnLaunchData_t *psOnLaunchData, 
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#endif
