#ifndef __MSA_APP_H__
#define __MSA_APP_H__

#include "mmi_launcher_common.h"

/// 1. Sea App,      APM_Mode = APM_LAUNCH_EMBEDDED, Mode = MSA_LAUNCH_MODE_SEND_OPTIONS

/// URL Format: "Msa://ListCertainSim?APM_Mode=%d&SimId=%d"
/// No data response callback
void LaunchMsaAppToListCertainSIM
(
  AppLaunchMode_e eAppLaunchMode, 
  SimID_e eSimId, 
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#endif
