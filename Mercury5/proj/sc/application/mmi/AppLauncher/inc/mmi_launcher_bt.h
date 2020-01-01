#ifndef __BT_APP_H__
#define __BT_APP_H__

#include "mmi_launcher_common.h"
#include "mmi_launcher_filemanager.h"

#define MAX_FILE_NUM_SEND_BY_BT   (100)

/// 1. Phb App,      APM_Mode = APM_LAUNCH_NORMAL,      param = MmiBtappRequest_t, Type = BTAPP_SEND_FILE, eFileType = SENDVIA_FILETYPE_GENERAL,   pIDList = pIDListForMultiSendBT, pwURL = NULL, pURLList = NULL,     bIsNeedDeleteFile = TRUE
/// 2. SendVia App,  APM_Mode = APM_LAUNCH_NORMAL,      param = MmiBtappRequest_t, Type = BTAPP_SEND_FILE, eFileType = SENDVIA_FILETYPE_GENERAL,   pIDList = pIDList,               pwURL = NULL, pURLList = pURLList, bIsNeedDeleteFile = FALSE
///                  APM_Mode = APM_LAUNCH_NORMAL,      param = MmiBtappRequest_t, Type = BTAPP_SEND_FILE, eFileType = SENDVIA_FILETYPE_VCALENDAR, pIDList = NULL,                  pwURL = cb,   pURLList = NULL,     bIsNeedDeleteFile = FALSE
///                  APM_Mode = APM_LAUNCH_NORMAL,      param = MmiBtappRequest_t, Type = BTAPP_SEND_FILE, eFileType = *,                          pIDList = NULL,                  pwURL = URL,  pURLList = NULL,     bIsNeedDeleteFile = FALSE
/// 3. Shortcut Srv, APM_MOde = APM_LAUNCH_INTERRUPTIVE,param = NULL,

typedef struct
{
    MAE_WChar wStrUrl[FILEMGR_MAX_FILEPATH_SIZE]; // The file can be sent by BT.
	bool bIsNeedToDeleteFile; // Indicate whether or not need to delete the file after sent by BT.
}BtAppSendInputData_t;

typedef struct
{
    MAE_WChar pStrUrl[MAX_FILE_NUM_SEND_BY_BT][FILEMGR_MAX_FILEPATH_SIZE]; // The maximum number of files can be sent by BT is MAX_FILE_NUM_SEND_BY_BT.
    u32 nFileCount; // The number of files that try to send by BT.
    boolean bIsNeedToDeleteFile; // Indicate whether or not need to delete the file after sent by BT.
}BtAppSendMultipleInputData_t;

/// 1. 2. 3.
/// Url Format: Bt://SendFile?APM_Mode=%d&IsNeedToDeleteFile=%d&FileUrl=%s
/// No data response callback
void LaunchBtAppToSendFile
(
    AppLaunchMode_e eAppLaunchMode,
    BtAppSendInputData_t *pInputData,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

/// 1. 2. 3.
/// Url Format: Bt://SendMultiFile?APM_Mode=%d&IsNeedToDeleteFile=%d&FileCount=%d&FileUrl=%s....
void LaunchBtAppToSendMultipleFile
(
    AppLaunchMode_e eAppLaunchMode,
    BtAppSendMultipleInputData_t *pInputData,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

/// Url Format: Bt://SendByFileId?APM_Mode=%d&IsNeedToDeleteFile=%d&HandleId=%d
void LaunchBtAppToSendFileByHandleId
(
    AppLaunchMode_e eAppLaunchMode,
    u32 nHandleId,
    boolean bIsNeedToDeleteFile,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

#endif
