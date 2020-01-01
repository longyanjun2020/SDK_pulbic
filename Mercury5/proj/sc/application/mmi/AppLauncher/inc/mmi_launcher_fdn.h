#ifndef __CCMTA_LAUNCHER_H__
#define __CCMTA_LAUNCHER_H__

#include "mmi_launcher_common.h"
#include "mmi_UrlSrvUtil.h"

/// URL Format: "Fdn://Launch?APM_Mode=%d&DualId=%d"
/// No data response callback
void LaunchFdnApp
( 
  AppLaunchMode_e eAppLaunchMode,
  u8 nDualID,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

#endif /* __CCMTA_LAUNCHER_H__*/
