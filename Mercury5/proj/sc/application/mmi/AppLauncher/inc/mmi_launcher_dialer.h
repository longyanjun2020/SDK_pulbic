#ifndef __DIALER_APP_H__
#define __DIALER_APP_H__

#include "mmi_launcher_common.h"
#include "mmi_ccsrv_def.h"

/// URL Format: "Dialer://Launch?APM_Mode=%d&startMode=%d"
/// No data response callback
void LaunchDialerApp
(
    AppLaunchMode_e eAppLaunchMode,
    u32 nKeyCode,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

void LaunchDialerAppWithNumber
(
    AppLaunchMode_e eAppLaunchMode, 
    u8 *pCallNum,
    LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchRspCbInfo_t *psRspCbInfo
);
#endif
