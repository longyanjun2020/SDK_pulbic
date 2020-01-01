#ifndef __JAVAAMSAPP_H__
#define __JAVAAMSAPP_H__

#include "mmi_launcher_common.h"
#include "mmi_mae_filemgr.h"


/************************************************************* 
    this funciton used to Launch JAVA with Jad & jar path..
    
    note: this finction may only used by WAP

    PRlist::
        PR 0145991,[South Africa] Install JAVA midlet by jad. Use WAP download again if the jad download new jad file (install from WAP browser)
**************************************************************/
#define JAVA_INSTALL_WITH_TWO_PATH

#define JAD_INFO_STRING L"JAD_INFO"



typedef enum
{
	JAVA_LAUNCH_PREINSTALL_0 = 0,
	JAVA_LAUNCH_PREINSTALL_1,
	JAVA_LAUNCH_PREINSTALL_2,
	JAVA_LAUNCH_PREINSTALL_3,
	JAVA_LAUNCH_PREINSTALL_4,
	JAVA_LAUNCH_PREINSTALL_5,
	JAVA_LAUNCH_PREINSTALL_6,
	JAVA_LAUNCH_PREINSTALL_7,
	JAVA_LAUNCH_PREINSTALL_8,
	JAVA_LAUNCH_PREINSTALL_9,
	JAVA_LAUNCH_PREINSTALL_10,
	JAVA_LAUNCH_PREINSTALL_11,
	JAVA_LAUNCH_PREINSTALL_12,
	JAVA_LAUNCH_PREINSTALL_13,
	JAVA_LAUNCH_PREINSTALL_14,
	JAVA_LAUNCH_PREINSTALL_15,
	JAVA_LAUNCH_PREINSTALL_16,
	JAVA_LAUNCH_PREINSTALL_17,
	JAVA_LAUNCH_PREINSTALL_18,
	JAVA_LAUNCH_PREINSTALL_19,
	JAVA_LAUNCH_PREINSTALL_20,
	JAVA_LAUNCH_PREINSTALL_21,
	JAVA_LAUNCH_PREINSTALL_22,
	JAVA_LAUNCH_PREINSTALL_23,
	JAVA_LAUNCH_PREINSTALL_24,
	JAVA_LAUNCH_PREINSTALL_MAX,
}JavaLaunchPreinstallIndex_e;

/// URL Format: "JavaAsm://Install?APM_Mode=%d&FilePath=%s"
/// No data response callback
void LaunchJavaAmsToInstallJava
(
    AppLaunchMode_e eAppLaunchMode,
    MAE_WChar *pszFile,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

void  LaunchJavaAmsToLaunchJava
(
	AppLaunchMode_e eAppLaunchMode,
	JavaLaunchPreinstallIndex_e nMidletIndex,
	LaunchAppTransParam_t *psTransParam,
	CmnAppLaunchRspCbInfo_t *psRspCbInfo
);


#ifdef JAVA_INSTALL_WITH_TWO_PATH
void  LaunchJavaAmsToInstallJavaEx
(	
    AppLaunchMode_e eAppLaunchMode,
    MAE_WChar *JarPath,/*jar path*/
    MAE_WChar *JadPath,/*jad path if hava*/
    LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchRspCbInfo_t *psRspCbInfo
);
#endif

#endif/* __JAVAAMSAPP_H__ */
