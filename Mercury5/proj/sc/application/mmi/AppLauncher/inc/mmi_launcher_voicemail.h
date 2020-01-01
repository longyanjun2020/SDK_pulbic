#ifndef __VOICEMAIL_APP_H__
#define __VOICEMAIL_APP_H__

#include "mmi_launcher_common.h"


/// 1. Call Setting App,   APM_Mode = APM_LAUNCH_EMBEDDED, StartType = VMA_E_START_SET_NUMBER_WITH_SELECT_SIM, SelectSim = SIM1 or SIM2
/// 2. Message Center App, APM_Mode = APM_LAUNCH_EMBEDDED, StartType = VMA_E_START_SETTING,                    SelectSim = SIM1 or SIM2
///                        APM_Mode = APM_LAUNCH_EMBEDDED, StartType = VMA_E_START_DIAL_NUMBER,                SelectSim = SIM1 or SIM2
///                        APM_Mode = APM_LAUNCH_EMBEDDED, StartType = VMA_E_START_DIAL_NUMBER_WITH_SELECT_SIM,SelectSim = SIM1 or SIM2


typedef enum
{
    VOICE_MAIL_LAUNCH_MODE_MIN = 0,
	VOICE_MAIL_LAUNCH_MODE_SETTING = VOICE_MAIL_LAUNCH_MODE_MIN,
    VOICE_MAIL_LAUNCH_MODE_DIAL_NUMBER,
  	VOICE_MAIL_LAUNCH_MODE_MAX = VOICE_MAIL_LAUNCH_MODE_DIAL_NUMBER,
	VOICE_MAIL_LAUNCH_MODE_NUM,
	VOICE_MAIL_LAUNCH_MODE_INVALID,
}VoiceMailLaunchModeWithNoSim_e;

typedef enum
{
    VOICE_MAIL_LAUNCH_MODE_MIN_WITH_SIM = 0,
	VOICE_MAIL_LAUNCH_MODE_SET_NUMBER_WITH_SIM = VOICE_MAIL_LAUNCH_MODE_MIN,
    VOICE_MAIL_LAUNCH_MODE_DIAL_NUMBER_WITH_SIM,
	VOICE_MAIL_LAUNCH_MODE_MAX_WITH_SIM = VOICE_MAIL_LAUNCH_MODE_DIAL_NUMBER_WITH_SIM,
	VOICE_MAIL_LAUNCH_MODE_NUM_WITH_SIM,
	VOICE_MAIL_LAUNCH_MODE_INVALID_WITH_SIM,
}VoiceMailLaunchModeWithSim_e;

typedef struct
{
    VoiceMailLaunchModeWithSim_e eLaunchModeWithSim;
	SimID_e eSim;  /// For VOICE_MAIL_LAUNCH_MODE_SET_NUMBER_WITH_SIM, VOICE_MAIL_LAUNCH_MODE_DIAL_NUMBER_WITH_SIM
}VoiceMailLaunchDataWithSim_t;

/// VoiceMail://Launch?APM_Mode=%d&LaunchMode=Setting
/// VoiceMail://Launch?APM_Mode=%d&LaunchMode=SelectSimAndDial
/// VoiceMail://Launch?APM_Mode=%d&LaunchMode=DialWithSim&Sim=Sim1
/// VoiceMail://Launch?APM_Mode=%d&LaunchMode=DialWithSim&Sim=Sim2
/// VoiceMail must notify Mca when exit
/// URL Format: "VoiceMail://LaunchWithSim?APM_Mode=%d&LaunchMode=%d&SimMod=%d"
/// No Response Data Callback
void LaunchVoiceMailAppToSelectSim
(
  AppLaunchMode_e eAppLaunchMode,
  VoiceMailLaunchDataWithSim_t *psLaunchDataWithSim,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

/// URL Format: "VoiceMail://LaunchWithoutSim?APM_Mode=%d&LaunchMode=%d"
/// No Response Data Callback
void LaunchVoiceMailAppToUnselectSim
(
  AppLaunchMode_e eAppLaunchMode,
  VoiceMailLaunchModeWithNoSim_e eLaunchModeWithNoSim,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#endif
