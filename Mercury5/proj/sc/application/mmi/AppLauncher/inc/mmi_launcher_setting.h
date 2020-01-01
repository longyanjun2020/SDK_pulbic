#ifndef __SETTING_APP_H__
#define __SETTING_APP_H__

#include "mmi_launcher_common.h"

/// 1. Shortcut Srv,   APM_Mode = APM_LAUNCH_INTERRUPTIVE, Mode = MSA_LAUNCH_MODE_SEND_OPTIONS
///                    APM_Mode = APM_LAUNCH_INTERRUPTIVE, Mode = SETTINGAPType_DateTime
///                    APM_Mode = APM_LAUNCH_INTERRUPTIVE, Mode = SETTINGAPType_Time
///                    APM_Mode = APM_LAUNCH_INTERRUPTIVE, Mode = SETTINGAPType_AutoOnOff
///                    APM_Mode = APM_LAUNCH_INTERRUPTIVE, Mode = SETTINGAPType_PhoneSettings
///                    APM_Mode = APM_LAUNCH_INTERRUPTIVE, Mode = SETTINGAPType_DisplaySettings
///                    APM_Mode = APM_LAUNCH_INTERRUPTIVE, Mode = SETTINGAPType_RingtoneSettings
///                    APM_Mode = APM_LAUNCH_INTERRUPTIVE, Mode = SETTINGAPType_CallSettings
///                    APM_Mode = APM_LAUNCH_INTERRUPTIVE, Mode = SETTINGAPType_ConnectSettings
///                    APM_Mode = APM_LAUNCH_INTERRUPTIVE, Mode = SETTINGAPType_NetworkSettings
///                    APM_Mode = APM_LAUNCH_INTERRUPTIVE, Mode = SETTINGAPType_Security

typedef enum
{
    SETTING_LAUNCH_MODE_MIN = 0,
    SETTING_LAUNCH_MODE_MAIN_MENU = SETTING_LAUNCH_MODE_MIN,
	SETTING_LAUNCH_MODE_DATE_TIME, /// SETTINGAPType_DateTime
	SETTING_LAUNCH_MODE_TIME,          /// SETTINGAPType_Time
	SETTING_LAUNCH_MODE_AUTO_ON_OFF,   /// SETTINGAPType_AutoOnOff
	SETTING_LAUNCH_MODE_PHONE,         /// SETTINGAPType_PhoneSettings
	SETTING_LAUNCH_MODE_DISPLAY,       /// SETTINGAPType_DisplaySettings
	SETTING_LAUNCH_MODE_RING_TONE,     /// SETTINGAPType_RingtoneSettings
	SETTING_LAUNCH_MODE_CALL,          /// SETTINGAPType_CallSettings
	SETTING_LAUNCH_MODE_CONNECT,       /// SETTINGAPType_ConnectSettings
	SETTING_LAUNCH_MODE_NETWORK,       /// SETTINGAPType_NetworkSettings
	SETTING_LAUNCH_MODE_SECURITY,      /// SETTINGAPType_Security	
#ifdef __DUAL_CAMERA_MMI__    
    SETTING_LAUNCH_MODE_CAMERATYPE,  ///SETTINGAPType_CameraType
#endif    	
    SETTING_LAUNCH_MODE_WALLPAPER_3D_EFFECT, /// SETTINGAPType_Wallpaper3DEffect
    SETTING_LAUNCH_MODE_IDLE_WALLPAPER_3D_EFFECT, /// SETTINGAPType_IdleWallpaper3DEffect
    SETTING_LAUNCH_MODE_MAX = SETTING_LAUNCH_MODE_IDLE_WALLPAPER_3D_EFFECT,    
}SettingLaunchMode_e;

/// URL Format: "Setting://Launch?APM_Mode=%d&StartMode=%d"
/// No data response callback
void LaunchSettingApp
(
  AppLaunchMode_e eAppLaunchMode,
  SettingLaunchMode_e eLaunchMode, 
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#endif
