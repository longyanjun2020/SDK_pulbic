#ifndef __EM_APP_H__
#define __EM_APP_H__

#include "mmi_launcher_common.h"

/// 1. Cc App,        APM_Mode = APM_LAUNCH_NORMAL,       param = Mode,  Mode = EMAPType_IMEI
///                   APM_Mode = APM_LAUNCH_NORMAL,       param = Mode,  Mode = EMAPType_FACTORY_INFO
///                   APM_Mode = APM_LAUNCH_NORMAL,       param = NULL,  Mode = NULL                  (NULL is equal to EMAPType_NORMAL)
/// 2. Dailer App,    APM_Mode = APM_LAUNCH_NORMAL,       param = Mode,  Mode = EMAPType_IMEI
///                   APM_Mode = APM_LAUNCH_NORMAL,       param = Mode,  Mode = EMAPType_FACTORY_INFO
///                   APM_Mode = APM_LAUNCH_NORMAL,       param = NULL,  Mode = NULL                  (NULL is equal to EMAPType_NORMAL)
/// 3. Setting App,   APM_Mode = APM_LAUNCH_EMBEDDED,     param = Mode,  Mode = EMAPType_SOFTWARE_VER
///                   APM_Mode = APM_LAUNCH_EMBEDDED,     param = Mode,  Mode = EMAPType_IMEI
/// 4. Shortcut Srv,  APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = Mode,  Mode = EMAPType_NORMAL
///                   APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = Mode,  Mode = EMAPType_FACTORY_INFO


typedef enum
{
	EM_LAUNCH_MODE_MIN = 0,
	EM_LAUNCH_MODE_NORMAL = EM_LAUNCH_MODE_MIN,
	EM_LAUNCH_MODE_IMEI,
	EM_LAUNCH_MODE_FACTORY_INFO,
	EM_LAUNCH_MODE_SOFTWARE_VERSION,
	EM_LAUNCH_MODE_WIFI_PRODUCTION,
	EM_LAUNCH_MODE_RESET_FACTORY,
	EM_LAUNCH_MODE_RESET_FACTORY_FOR_TOOL,
    EM_LAUNCH_MODE_TOUCH_SCREEN_FWUPDATE,
    EM_LAUNCH_MODE_WIFI_ALL_TEST,
    EM_LAUNCH_MODE_BT_ALL_TEST,
    EM_LAUNCH_MODE_WIFI_PRODUCTION_TX,
	EM_LAUNCH_MODE_MAX = EM_LAUNCH_MODE_WIFI_PRODUCTION_TX,
}EmLaunchMode_e;

/// 1. 2. 3. 4.
/// URL Format: Em://Launch?APM_Mode=%d&Launch_Mode=%d
/// No data response callback
void LaunchEmApp
(
  AppLaunchMode_e eAppLaunchMode,
  EmLaunchMode_e eLaunchMode, 
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#endif
