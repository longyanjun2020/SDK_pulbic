#ifndef __MTA_APP_H__
#define __MTA_APP_H__

#include "mmi_UrlSrvUtil.h"
#include "mmi_launcher_common.h"

typedef void (*MtaSelectLaunchAppRspCb)(void *pvUserData, MAE_Ret nRspCode, MAE_WChar *pvRspData, CmnRspDataFreeCb pfnRspFreeCb);

typedef struct
{
    void *pvUserData;
    CmnLaunchAppRspCb pfnLaunchListenerCb;
    MtaSelectLaunchAppRspCb pfnDataRspCb;
}MtaSelectLaunchRspCbInfo_t;

/// URL Format: "Mta://PickMode?APM_Mode=%d"
/// No response data callback
void LaunchMtaAppPickMode
(
  AppLaunchMode_e eAppLaunchMode, 
  LaunchAppTransParam_t *psTransParam,
  MtaSelectLaunchRspCbInfo_t *psRspCbInfo
);

#endif
