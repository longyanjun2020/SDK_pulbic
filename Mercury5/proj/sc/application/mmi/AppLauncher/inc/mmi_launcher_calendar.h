#ifndef __CALENDAR_APP_H__
#define __CALENDAR_APP_H__

#include "mmi_launcher_common.h"

/// 1. EventCenter App,        APM_Mode = APM_LAUNCH_EMBEDDED,     param = CalEmbedModeInfo_t  ,Mode = CALENDAR_LAUNCH_MODE_VIEW_EVENT
/// 2. FileManager App,        APM_Mode = APM_LAUNCH_EMBEDDED,     param = CalEmbedModeInfo_t  ,Mode = CALENDAR_LAUNCH_MODE_IMPORT_EVENT
/// 3. Sea         App,        APM_Mode = APM_LAUNCH_EMBEDDED,     param = CalEmbedModeInfo_t  ,Mode = CALENDAR_LAUNCH_MODE_MONTHLY_VIEW
/// 4. Search App,             APM_Mode = APM_LAUNCH_EMBEDDED,     param = CalEmbedModeInfo_t  ,Mode = CALENDAR_LAUNCH_MODE_VIEW_EVENT
/// 5. Shortcut Srv,           APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = 0                   ,Mode = NULL

enum
{
    CALENDAR_EXPORT_AS_PLAIN_TEXT,
    CALENDAR_EXPORT_AS_FILE_URL
};
typedef u8 CalendarExportFormat_e;


typedef void (*CalendarAppExportEventRspDataFreeCb)(MAE_WChar *pRspData);
typedef void (*CalendarAppExportEventRspCb)(void *pUserData, MAE_Ret nRspCode, MAE_WChar *pRspData, CalendarAppExportEventRspDataFreeCb pfnRspDataFreeCb);

typedef struct
{
	void *pUserData;
    CmnLaunchAppRspCb pfnLaunchListenerCb;
	CalendarAppExportEventRspCb pfnDataRspCb;
}CalendarAppExportEventRspCbInfo_t;


/// Url Format: "Calendar://Launch?APM_Mode=%d"
/// No data response callback
void LaunchCalendarApp
(
  AppLaunchMode_e eAppLaunchMode, 
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

/// 2.
/// Url Format: "Calendar://ImportEvent?APM_Mode=%d&FileUrl=%s"
/// No data response callback
void LaunchCalendarAppToImportEvent
(
  AppLaunchMode_e eAppLaunchMode,
  MAE_WChar *pFileUrl, 
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

/// 1. 4.
/// Url Format: "Calendar://ViewEvent?APM_Mode=%d&EventId=%d"
/// No data response callback
void LaunchCalendarAppToViewEvent
(
  AppLaunchMode_e eAppLaunchMode,
  u32 nEventId, 
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

/// 3.
/// Url Format: "Calendar://ExportEvent?APM_Mode=%d&ExportFormat=%d"
/// 
/// If __CALENDAR_EXPORT_VCS_MMI__ is disablede, plain text is exported
void LaunchCalendarAppToExportEvent
(
  AppLaunchMode_e eAppLaunchMode, 
  CalendarExportFormat_e eExportFormat,
  LaunchAppTransParam_t *psTransParam,
  CalendarAppExportEventRspCbInfo_t *pRspCbInfo
);

/// Url Format: "Calendar://NewEvent?APM_Mode=%d"
/// No data response callback
void LaunchCalendarAppToNewEvent
(
  AppLaunchMode_e eAppLaunchMode,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

#endif
