#ifndef __VENDORAPP_H__
#define __VENDORAPP_H__

#include "mmi_launcher_common.h"
#include "mmi_common_vendor_type.h"

void LaunchVendorToLaunchJavaAP
(
    AppLaunchMode_e eAppLaunchMode,
    MAE_WChar *pszFile,
	u32 bNeedMemCard,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#endif/* __VENDORAPP_H__ */
