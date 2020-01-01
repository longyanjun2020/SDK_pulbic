#ifndef __CALLLOG_APP_H__
#define __CALLLOG_APP_H__

#include "mmi_launcher_common.h"
#include "mmi_common_calllog_type.h"

/// 1. Call Setting App,        APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiCallLogAPFidData_t   ,Mode = SRV_AP_FID_COST_SETTING,
/// 2. Dialer App,              APM_Mode = APM_LAUNCH_NORMAL,       param = SRV_AP_Show_List_Type_e ,Mode = CALLLOG_LAUNCH_MODE_SHOW_CALL_LOG_LIST, SRV_AP_Show_List_Type_e = CALLLOG_LIST_TYPE_DAILED
/// 3. Idle App,                APM_Mode = APM_LAUNCH_NORMAL,       param = SRV_AP_Show_List_Type_e ,Mode = CALLLOG_LAUNCH_MODE_SHOW_CALL_LOG_LIST, SRV_AP_Show_List_Type_e = CALLLOG_LIST_TYPE_DAILED
///                             APM_Mode = APM_LAUNCH_NORMAL,       param = SRV_AP_Show_List_Type_e ,Mode = CALLLOG_LAUNCH_MODE_SHOW_CALL_LOG_LIST, SRV_AP_Show_List_Type_e = CALLLOG_LIST_TYPE_MISSED
/// 4. Event Center Srv,        APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = SRV_AP_Show_List_Type_e ,Mode = NULL                                  , SRV_AP_Show_List_Type_e = CALLLOG_LIST_TYPE_MISSED
/// 5. Shortcut Srv,            APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = 0,                       Mode = NULL

/// 1.
/// URL Format: "CallLog://ShowCostSetting?APM_Mode=%d&simID=%d"
/// No data response callback
void LaunchAppToShowCostSetting
(
  AppLaunchMode_e eAppLaunchMode, 
  SimID_e eSimId, 
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

/// 2. 3. 4. 5.
/// URL Format: "CallLog://ShowCallLogList?APM_Mode=%d&listType=%d"
/// No data response callback
void LaunchAppToShowCallLogList
(
  AppLaunchMode_e eAppLaunchMode, 
  CallLogListType_e eListType, 
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

#endif
