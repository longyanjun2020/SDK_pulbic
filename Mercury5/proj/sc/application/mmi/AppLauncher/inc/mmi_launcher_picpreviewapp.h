#ifndef __PICPREVIEWAPP_H__
#define __PICPREVIEWAPP_H__

#include "mmi_launcher_common.h"

/// 1. EventCenter App,        APM_Mode = APM_LAUNCH_EMBEDDED,     param = CalEmbedModeInfo_t  ,Mode = CALENDAR_LAUNCH_MODE_VIEW_EVENT
/// 2. FileManager App,        APM_Mode = APM_LAUNCH_EMBEDDED,     param = CalEmbedModeInfo_t  ,Mode = CALENDAR_LAUNCH_MODE_IMPORT_EVENT
/// 3. Sea         App,        APM_Mode = APM_LAUNCH_EMBEDDED,     param = CalEmbedModeInfo_t  ,Mode = CALENDAR_LAUNCH_MODE_MONTHLY_VIEW
/// 4. Search App,             APM_Mode = APM_LAUNCH_EMBEDDED,     param = CalEmbedModeInfo_t  ,Mode = CALENDAR_LAUNCH_MODE_VIEW_EVENT
/// 5. Shortcut Srv,           APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = 0                   ,Mode = NULL

typedef enum
{
	PHOTOSLIDE_Portrait = 0,
	PHOTOSLIDE_Landscape,	
} PhotoSlideType_e;

typedef struct
{
	u32 nSelectedIdx;
	PhotoSlideType_e slideType;
} PicPreviewReqData_t;

void LaunchPicPreviewApp
(
  AppLaunchMode_e eAppLaunchMode,
 PicPreviewReqData_t *pPicPreviewReqData,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

#endif
