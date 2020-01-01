#ifndef __SOHUUPDATER_APP_H__
#define __SOHUUPDATER_APP_H__

#include "mmi_launcher_common.h"

// 1. from Setting App,    APM_Mode = APM_LAUNCH_NORMAL,   param = tSohuStartParm,  Mode = SOHU_UPDATER_NORMAL_MODE
// 2. from Alarm Srv,    APM_Mode = APM_LAUNCH_NORMAL,   param = tSohuStartParm, Mode = SOHU_UPDATER_AUTO_MODE

typedef enum
{
    SOHU_UPDATER_NORMAL_MODE = 0,
    SOHU_UPDATER_AUTO_MODE
} SoHu_Updater_Field_e;

// 1. URL Format: "SohuUpdater://FromSetting?APM_Mode=%d&ModeID=%d"
// No Response DataCallback.
void LaunchSoHuUpdaterAppFromSetting
(
    AppLaunchMode_e eAppLaunchMode,
    SoHu_Updater_Field_e eField,
    LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

// 2. URL Format: "SohuUpdater://FromSetting?APM_Mode=%d&ModeID=%d"
// No Response DataCallback.
void LaunchSoHuUpdaterAppFromAlarm
(
    AppLaunchMode_e eAppLaunchMode,
    SoHu_Updater_Field_e eField,
    LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#endif
