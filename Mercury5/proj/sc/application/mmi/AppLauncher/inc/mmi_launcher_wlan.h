#ifndef __MMI_LAUNCHER_WLAN_H__
#define __MMI_LAUNCHER_WLAN_H__

#include "mmi_launcher_common.h"

#ifdef __WLAN_MMI__
/// Plz fill the URL Format:
void LaunchWLANBySetting  (AppLaunchMode_e eAppLaunchMode,LaunchAppTransParam_t *psTransParam,CmnAppLaunchRspCbInfo_t *psRspCbInfo);
/// Plz fill the URL Format:
void LaunchWLANByLowSignal(AppLaunchMode_e eAppLaunchMode,LaunchAppTransParam_t *psTransParam,CmnAppLaunchRspCbInfo_t *psRspCbInfo);
#endif/* __WLAN_MMI__ */

#endif/* __MMI_LAUNCHER_WLAN_H__ */
