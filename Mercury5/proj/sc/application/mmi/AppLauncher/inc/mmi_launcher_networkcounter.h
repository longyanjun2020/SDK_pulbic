#ifndef __NETWORKCOUNTER_APP_H__
#define __NETWORKCOUNTER_APP_H__

#include "mmi_launcher_common.h"

typedef enum
{
    NETWORK_COUNTER_LAUNCH_MODE_MIN = 0,
    NETWORK_COUNTER_LAUNCH_MODE_GENERAL = NETWORK_COUNTER_LAUNCH_MODE_MIN,
    NETWORK_COUNTER_LAUNCH_MODE_GPRS,
    NETWORK_COUNTER_LAUNCH_MODE_WIFI,
    NETWORK_COUNTER_LAUNCH_MODE_MAX = NETWORK_COUNTER_LAUNCH_MODE_WIFI,
}NetworkCounterLaunchMode_e;

/// No data response callback
void LaunchNetworkCounterApp
(
  AppLaunchMode_e eAppLaunchMode,
  NetworkCounterLaunchMode_e eLaunchMode,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#endif
