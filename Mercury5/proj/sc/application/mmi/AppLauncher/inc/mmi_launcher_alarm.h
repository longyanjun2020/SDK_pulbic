#ifndef __ALARM_APP_H__
#define __ALARM_APP_H__

#include "mmi_launcher_common.h"

/// 1. EventCenter App,        APM_Mode = APM_LAUNCH_EMBEDDED,     param = ALARMAPP_EMBEDMODEINFO_t,  Mode = ALARM_EMBEDDEDMODE_VIEWALARM
/// 2. Shortcut Srv,           APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = 0,                         Mode = NULL

typedef enum
{
	ALARM_ID_MIN = 0,
    ALARM_ID_1 = ALARM_ID_MIN,
	ALARM_ID_2,
	ALARM_ID_3,
	ALARM_ID_4,
	ALARM_ID_5,
	ALARM_ID_6,
	ALARM_ID_MAX = ALARM_ID_6,
}AlarmId_e;

/// 1.
/// Launch Alarm App, then list all its alarm.
/// 
/// URL Format: "Alarm://ListAllAlarm?APM_Mode=%d"
/// No data response callback
void LaunchAppToListAllAlarm
(
  AppLaunchMode_e eAppLaunchMode, 
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

/// 2.
/// Launch Alarm App, the view a indicated alarm
/// 
/// URL Format: "Alarm://ViewAlarm?APM_Mode=%d&AlarmId=%d"
/// No data response callback
void LaunchAppToViewAlarm
(
  AppLaunchMode_e eAppLaunchMode, 
  AlarmId_e eAlarmId, 
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

#endif/* __ALARM_APP_H__ */
