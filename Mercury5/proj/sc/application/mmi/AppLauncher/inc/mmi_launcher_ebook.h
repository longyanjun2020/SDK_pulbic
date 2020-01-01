#ifndef __EBOOK_LAUNCHER_H__
#define __EBOOK_LAUNCHER_H__

#include "mmi_launcher_common.h"
#include "mmi_launcher_filemanager.h"

/// URL Format: EBook://Browse?APM_Mode=%d&FilePath=%s&bIsNeedDeleteFile=%d
/// No data response callback
void LaunchEbookAppToBrowseFile
(
  AppLaunchMode_e eAppLaunchMode,
  MAE_WChar wStrUrl[FILEMGR_MAX_FILEPATH_SIZE],
  boolean bIsNeedDeleteFile,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

void LaunchEbookAppToBrowseFileEx(
  AppLaunchMode_e eAppLaunchMode,
  MAE_WChar strBrowserUrl[FILEMGR_MAX_FILEPATH_SIZE],
  boolean bIsNeedDeleteFile,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchFileOpRspCbInfo_t *pFileOpRspCbInfo
);
#endif /* __EBOOK_LAUNCHER_H__*/
