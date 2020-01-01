#ifndef __WAP_APP_H__
#define __WAP_APP_H__

#include "mmi_launcher_common.h"
#include "mmi_launcher_filemanager.h"

/// 1. Sva App,        APM_Mode = APM_LAUNCH_EMBEDDED,                               param = tWapStartParm,      Mode = CDWap_SAVE_BOOKMARK_MODE
///                    APM_Mode = APM_LAUNCH_INTERRUPTIVE|APML_ABORT_ON_INT_FAILED,  param = tWapStartParm,      Mode = CDWap_OPEN_URL_MODE
/// 2. Vendor App,     APM_Mode = APM_LAUNCH_INTERRUPTIVE|APML_ABORT_ON_INT_FAILED,  param = tWapStartParm,      Mode = CDWap_OPEN_URL_MODE
/// 3. Shortcut Srv,   APM_Mode = APM_LAUNCH_INTERRUPTIVE|APML_ABORT_ON_INT_FAILED,  param = NULL,               Mode = NULL
/// 4. Java Ams App,   APM_Mode =                                                 ,  param = tWapStartParm,      Mode = CDWap_DOWNLOAD_URL_MODE

/// 3.
/// URL Format: "Wap://Launch?APM_Mode=%d"
/// No Response DataCallback.
void LaunchCdWapApp
(
  AppLaunchMode_e eAppLaunchMode,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

/// 1. 2.
/// URL Format: "Wap://OpenUrl?APM_Mode=%d&simID=%d&url=%s"
/// No Response DataCallback.
void LaunchCdWapAppToOpenUrl
(
  AppLaunchMode_e eAppLaunchMode,
  SimID_e eSimId,
  MAE_WChar wStrUrl[FILEMGR_MAX_FILEPATH_SIZE],
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

/// 1.
/// URL Format: "Wap://SaveBookMark?APM_Mode=%d&simID=%d&url=%s"
/// No Response DataCallback.
void LaunchCdWapAppToSaveBookMark
(
  AppLaunchMode_e eAppLaunchMode,
  MAE_WChar wStrUrl[FILEMGR_MAX_FILEPATH_SIZE],
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

/// 4.
/// URL Format: "Wap://DownloadUrl?APM_Mode=%d&simID=%d&url=%s&StorageType=%d"
/// Use data response callback to retrieve data
/// nRspCode: MAE_RET_SUCCESS, MAE_RET_FAILED, MAE_RET_ABORT
void LaunchCdWapAppToDownloadUrlToStorage
(
  AppLaunchMode_e eAppLaunchMode,
  SimID_e eSimId,
  StorageType_e eStorageType,  
  MAE_WChar wStrUrl[FILEMGR_MAX_FILEPATH_SIZE],
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

/// 4.
/// URL Format: "Wap://DownloadUrl?APM_Mode=%d&simID=%d&url=%s"
/// Use data response callback to retrieve data
/// nRspCode: MAE_RET_SUCCESS, MAE_RET_FAILED, MAE_RET_ABORT
void LaunchCdWapAppToDownloadUrl
(
  AppLaunchMode_e eAppLaunchMode,
  SimID_e eSimId,
  MAE_WChar wStrUrl[FILEMGR_MAX_FILEPATH_SIZE],
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#endif
