#ifndef __JAVAFACTORYAPP_H__
#define __JAVAFACTORYAPP_H__

#include "mmi_launcher_common.h"


/// URL Format: "JavaFactory://Launch?APM_Mode=%d"
/// No data response callback
void LaunchJavaFactoryToInstallJava
(
    AppLaunchMode_e eAppLaunchMode,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#endif/* __JAVAFACTORYAPP_H__ */
