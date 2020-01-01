#ifndef __MMSA_APP_H__
#define __MMSA_APP_H__

#include "mmi_launcher_common.h"

/// 1. Sea App,       APM_Mode = APM_LAUNCH_NORMAL,        Mode = MMSA_E_START_PAGESETTING
typedef void (*MmsaGetDurationRspCb)(void *pvUserData, MAE_Ret nRspCode, u32 nDuration, CmnRspDataFreeCb pfnRspFreeCb);

typedef struct
{
	void *pvUserData;
    CmnLaunchAppDataRspCb pfnLaunchListenerCb;
	MmsaGetDurationRspCb  pfnDataRspCb;
}MmsaGetDurationRspCbInfo_t;


/// URL Format: "Mmsa://ListPageSetting?APM_Mode=%d&Duration=%d"
/// Use data response callback to retrieve data
void LaunchMmsaAppToListPageSetting
(
  AppLaunchMode_e eAppLaunchMode,
  u32 nDuration,   /// nDuration :  MIN_MMS_SLIDE_DURATION/1000 ~ MAX_MMS_SLIDE_DURATION/1000
  LaunchAppTransParam_t *psTransParam,
  MmsaGetDurationRspCbInfo_t *psRspCbInfo
);

/// URL Format: "Mmsa://ListSendOptions?APM_Mode=%d&SimId=%d"
/// No data response callback
void LaunchMmsaAppToListSendOptions
(
  AppLaunchMode_e eAppLaunchMode,
  SimID_e eSimId,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#endif
