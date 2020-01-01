#ifndef __CALLSETTING_APP_H__
#define __CALLSETTING_APP_H__

#include "mmi_launcher_common.h"

/// 1. Setting App,     APM_Mode = APM_LAUNCH_NORMAL,   param = NULL,     Mode = NULL
///                             APM_Mode = APM_LAUNCH_NORMAL,   param = Mode,     Mode = CALL_SETTING_LAUNCH_MODE_CALL_SETTING
///                             APM_Mode = APM_LAUNCH_NORMAL,   param = Mode,     Mode = CALL_SETTING_LAUNCH_MODE_CALL_DIVERT
///                             APM_Mode = APM_LAUNCH_NORMAL,   param = Mode,     Mode = CALL_SETTING_LAUNCH_MODE_CALL_BARRING
///                             APM_Mode = APM_LAUNCH_NORMAL,   param = Mode,     Mode = CALL_SETTING_LAUNCH_MODE_DISTORTED_VOICE

typedef enum
{
	CALL_SETTING_LAUNCH_MODE_MIN = 0,
	CALL_SETTING_LAUNCH_MODE_NORMAL = CALL_SETTING_LAUNCH_MODE_MIN,
	CALL_SETTING_LAUNCH_MODE_VOICEBOX,
	CALL_SETTING_LAUNCH_MODE_CALL_SETTING,
	CALL_SETTING_LAUNCH_MODE_CALL_DIVERT,
	CALL_SETTING_LAUNCH_MODE_CALL_BARRING,
	CALL_SETTING_LAUNCH_MODE_DISTORTED_VOICE,
	CALL_SETTING_LAUNCH_MODE_CALL_BACKGROUND_SOUND,
	CALL_SETTING_LAUNCH_MODE_MAX=CALL_SETTING_LAUNCH_MODE_DISTORTED_VOICE,
}CallSettingLaunchMode_e;

typedef struct
{
    boolean bDistortedVoice;
    u8      nDistortedEffect;
} DistortedVoiceInfo_t;

/// 1.
/// URL Format: "CallSetting://Launch?APM_Mode=%d&StartMode=%d"
/// No data response callback
void LaunchCallSettingApp
(
  AppLaunchMode_e eAppLaunchMode,
  CallSettingLaunchMode_e eLaunchMode,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

/// URL Format: "CallSetting://Launch?APM_Mode=%d&startMode=%d&IsDistortedEnable=%d&DistortedEffect=%d"
void LaunchCallSettingAppToGetDistortedInfo
(
 AppLaunchMode_e eAppLaunchMode,
 boolean bDistortedVoice,
 u8 nDistortedEffect,
 LaunchAppTransParam_t *psTransParam,
 CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#endif
