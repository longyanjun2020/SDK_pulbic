#ifndef __CONSETTING_APP_H__
#define __CONSETTING_APP_H__

#include "mmi_launcher_common.h"

/// 1. JavaHttp App,   APM_Mode = APM_LAUNCH_EMBEDDED, param = Mode,     Mode = CON_SETTING_LAUNCH_MODE_CONNECT_SETTING_MENU
/// 2. Setting App,    APM_Mode = APM_LAUNCH_NORMAL,   param = NULL,     Mode = NULL
///                    APM_Mode = APM_LAUNCH_NORMAL,   param = Mode,     Mode = CON_SETTING_LAUNCH_MODE_DATA_ACCOUNT
///                    APM_Mode = APM_LAUNCH_NORMAL,   param = Mode,     Mode = CON_SETTING_LAUNCH_MODE_WAP_PROFILE
///                    APM_Mode = APM_LAUNCH_NORMAL,   param = Mode,     Mode = CON_SETTING_LAUNCH_MODE_MMS_PROFILE
///                    APM_Mode = APM_LAUNCH_NORMAL,   param = Mode,     Mode = CON_SETTING_LAUNCH_MODE_JAVA_PROFILE
///                    APM_Mode = APM_LAUNCH_NORMAL,   param = Mode,     Mode = CON_SETTING_LAUNCH_MODE_OTHER_PROFILE
///                    APM_Mode = APM_LAUNCH_NORMAL,   param = Mode,     Mode = CON_SETTING_LAUNCH_MODE_IPTV_SETTING
///                    APM_Mode = APM_LAUNCH_NORMAL,   param = Mode,     Mode = CON_SETTING_LAUNCH_MODE_MMTV_SETTING
///                    APM_Mode = APM_LAUNCH_NORMAL,   param = Mode,     Mode = CON_SETTING_LAUNCH_MODE_LBS_SETTING

typedef enum
{
	CON_SETTING_LAUNCH_MODE_MIN = 0,
	CON_SETTING_LAUNCH_MODE_MAIN_MENU = CON_SETTING_LAUNCH_MODE_MIN,
	CON_SETTING_LAUNCH_MODE_DATA_ACCOUNT,
	CON_SETTING_LAUNCH_MODE_WAP_SETTING,
	CON_SETTING_LAUNCH_MODE_MMS_SETTING,
	CON_SETTING_LAUNCH_MODE_JAVA_SETTING,
	CON_SETTING_LAUNCH_MODE_OTHER_SETTING,
#ifdef __APP_MMI_NTP__
    CON_SETTING_LAUNCH_MODE_NTP_SETTING,
#endif
	CON_SETTING_LAUNCH_MODE_LBS_SETTING,
#ifdef __EMAIL_MMI__
	CON_SETTING_LAUNCH_MODE_EMAIL_SETTING,
#endif

#ifdef __NCCQQ_MMI__
    CON_SETTING_LAUNCH_MODE_QQ_SETTING,
#endif

#ifdef __STREAMING_MODULE__
    CON_SETTING_LAUNCH_MODE_STREAMING_SETTING,
    CON_SETTING_LAUNCH_MODE_MAX = CON_SETTING_LAUNCH_MODE_STREAMING_SETTING
#else
    #ifdef __NCCQQ_MMI__
        CON_SETTING_LAUNCH_MODE_MAX = CON_SETTING_LAUNCH_MODE_QQ_SETTING
    #else 
        #ifdef __EMAIL_MMI__
        	CON_SETTING_LAUNCH_MODE_MAX = CON_SETTING_LAUNCH_MODE_EMAIL_SETTING
        #else
            CON_SETTING_LAUNCH_MODE_MAX = CON_SETTING_LAUNCH_MODE_LBS_SETTING
        #endif
    #endif
#endif
}ConSettingLaunchMode_e;

/// 1. 2.
/// URL Format: "ConSetting://Launch?APM_Mode=%d&StartMode=%d"
/// No data response callback
void LaunchConSettingApp
(
  AppLaunchMode_e eAppLaunchMode,
  ConSettingLaunchMode_e eLaunchMode,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#endif
