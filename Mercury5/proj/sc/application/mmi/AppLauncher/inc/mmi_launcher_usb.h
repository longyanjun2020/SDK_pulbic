#ifndef __USB_APP_H__
#define __USB_APP_H__

#include "mmi_launcher_common.h"

/// URL Format: "Usb://Launch?APM_Mode=%d"
/// No data response callback
void LaunchUsbApp
(
    AppLaunchMode_e eAppLaunchMode,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

/// URL Format: "Usb://Open?APM_Mode=%d"
/// Plz Fill your URL Format
void LaunchUsbAppOpenRequest
(
    AppLaunchMode_e eAppLaunchMode,
    u32 nUSBFuncID,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#endif
