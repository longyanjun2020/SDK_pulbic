#ifndef __USSD_APP_H__
#define __USSD_APP_H__

#include "mmi_launcher_common.h"
#include "mmi_srv_client_platformdefines.h"
#include "mmi_UrlSrvUtilUrl.h"
#include "mmi_UrlSrvUtil.h"
#include "mmi_UrlSrvClientHelper.h"
#include "mmi_sssrv_def.h"

/// APM_Mode = APM_LAUNCH_NORMAL,   param = SSSRV_CreateUSSDAppReq_t*,
/// Plz Fill your URL Format
void LaunchUssd(AppLaunchMode_e eAppLaunchMode, SSSRV_CreateUSSDAppReq_t *pReq, LaunchAppTransParam_t *psTransParam,CmnAppLaunchRspCbInfo_t *psRspCbInfo);

#endif
