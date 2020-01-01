#ifndef __VIDEOPLAYER_APP_H__
#define __VIDEOPLAYER_APP_H__

#include "mmi_launcher_common.h"
#include "mmi_launcher_filemanager.h"
#include "mmi_mediasrv_common.h"

/// 1. Cam App,          APM_Mode = APM_LAUNCH_NORMAL,        Mode = VIDEOPLAYER_MODE_CAMCORDER_LANDSCAPE, pIDataModel = NULL,       pIVectorModel = one item, pFocusDataModel = NULL,      nFocusIndex = 0
///                      APM_Mode = APM_LAUNCH_NORMAL,        Mode = VIDEOPLAYER_MODE_CAMCORDER_PORTRAIT,  pIDataModel = NULL,       pIVectorModel = one item, pFocusDataModel = NULL,      nFocusIndex = 0
/// 2. File Manager App, APM_Mode = APM_LAUNCH_EMBEDDED,      Mode = VIDEOPLAYER_MODE_SIMPLE,              pIDataModel = NULL,       pIVectorModel = one item, pFocusDataModel = NULL,      nFocusIndex = 0
///                      APM_Mode = APM_LAUNCH_EMBEDDED,      Mode = VIDEOPLAYER_MODE_PICK,                pIDataModel = pPickerCnt, pIVectorModel = one item, pFocusDataModel = pFocusCnt, nFocusIndex = nFocusCntAtIdx
///                      APM_Mode = APM_LAUNCH_EMBEDDED,      Mode = VIDEOPLAYER_MODE_SIMPLE,              pIDataModel = NULL,       pIVectorModel = one item, pFocusDataModel = pFocusCnt, nFocusIndex = nFocusCntAtIdx
///                      APM_Mode = APM_LAUNCH_EMBEDDED,      Mode = VIDEOPLAYER_MODE_PREVIEW,             pIDataModel = NULL,       pIVectorModel = one item, pFocusDataModel = pFocusCnt, nFocusIndex = nFocusCntAtIdx
/// 3. MPlayer App,      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
/// 4. Sea App,          APM_Mode = APM_LAUNCH_EMBEDDED,      Mode = VIDEOPLAYER_MODE_SIMPLE_URL,          pIDataModel = NULL,       pIVectorModel = one item, pFocusDataModel = NULL,      nFocusIndex = 0
/// 5. Search App,       APM_Mode = APM_LAUNCH_EMBEDDED,      Mode = VIDEOPLAYER_MODE_PREVIEW,             pIDataModel = NULL,       pIVectorModel = one item, pFocusDataModel = NULL,      nFocusIndex = 0
/// 6. Sva App,          APM_Mode = APM_LAUNCH_EMBEDDED,      Mode = VIDEOPLAYER_MODE_SIMPLE_URL,          pIDataModel = NULL,       pIVectorModel = one item, pFocusDataModel = NULL,      nFocusIndex = 0
/// 7. Vendor App,       APM_Mode = APM_LAUNCH_EMBEDDED,      Mode = VIDEOPLAYER_MODE_PREVIEW,             pIDataModel = NULL,       pIVectorModel = one item, pFocusDataModel = NULL,      nFocusIndex = 0

typedef enum
{
	VID_PLAYER_VIEW_MODE_PORTRAIT,
	VID_PLAYER_VIEW_MODE_LANDSCAPE,
	VID_PLAYER_VIEW_MODE_NUM,
	VID_PLAYER_VIEW_MODE_INVALID,
}VidPlayerViewMode_e;

typedef enum
{
    VIDEOPLAYERLAUNCHER_STREAMING_FILE_MODE,
    VIDEOPLAYERLAUNCHER_STREAMING_MEMORY_MODE
} VideoPlayerLauncherStreamingMode_e;

typedef struct
{
	VidPlayerViewMode_e eViewMode;
	MAE_WChar wStrDirUrl[FILEMGR_MAX_FILEPATH_SIZE];
    VFS_FileID_t    *pFileId;
}VidListInfo_t;

typedef struct
{
	VidPlayerViewMode_e eViewMode;
	MAE_WChar wStrFileUrl[FILEMGR_MAX_FILEPATH_SIZE];
    u32 nStartPosition;
}VidInfo_t;

typedef struct
{
    //void *pCBData;
    VidPlayerViewMode_e eViewMode;
    MAE_WChar *pFileUrl;
    u32 nStartPosition;
    VideoPlayerLauncherStreamingMode_e eStreamingMode;
    MediaSrvMimeType_e eMimeType;
    void *pfnDownloadItf;
}VidStreamInfo_t;

typedef struct
{
    VidPlayerViewMode_e eViewMode;
    u8 *pBuf;
    u32 nBufLen;
    MediaSrvMimeType_e eMimeType;
} VidBufInfo_t;

typedef struct
{
    MAE_WChar wStrLastFocusFileUrl[FILEMGR_MAX_FILEPATH_SIZE];
}VidPlayerAppPlayRspData_t;

typedef void (*VidPlayerAppPlayRspDataFreeCb)(VidPlayerAppPlayRspData_t *psRspDataFreeCb);
typedef void (*VidPlayerAppPlayRspCb)(void *pvUserData, MAE_Ret nRspCode, VidPlayerAppPlayRspData_t *psRspData, VidPlayerAppPlayRspDataFreeCb pfnRspDataFreeCb);

typedef struct
{
	void *pvUserData;
	VidPlayerAppPlayRspCb pfnRspCb;
}VidPlayerAppPlayRspCbInfo_t;

typedef struct
{
	MAE_WChar wStrLastFocusFileUrl[FILEMGR_MAX_FILEPATH_SIZE];
	MAE_WChar wStrSelectedFileUrl[FILEMGR_MAX_FILEPATH_SIZE];
}VidPlayerVidRspData_t;

typedef void (*VidPlayerAppSimplePlayAndSelectRspDataFreeCb)(VidPlayerVidRspData_t *psRspData);
typedef void (*VidPlayerAppSimplePlayAndSelectRspCb)(void *pvUserData, MAE_Ret nRspCode, VidPlayerVidRspData_t *psRspData, VidPlayerAppSimplePlayAndSelectRspDataFreeCb pfnRspDataFreeCb);

typedef struct
{
	void *pvUserData;
	VidPlayerAppSimplePlayAndSelectRspCb pfnRspCb;
}VidPlayerAppSimplePlayAndSelectRspCbInfo_t;

typedef enum
{
    VID_SEEK_MODE__OFF, //Disable Seek
    VID_SEEK_MODE__DOWNLOADED_ONLY, //Seek only already downloaded data
    VID_SEEK_MODE__ALL, //Seekable
} VidPlayerSeekMode_e;

typedef enum
{
    VID_EMBEDED_EVT_START = 0,
    VID_EMBEDED_EVT_SEEK_ENABLE = VID_EMBEDED_EVT_START,
    VID_EMBEDED_EVT_END,
}VidPlayerEmbededEvt_e;

/// "VidPlayer://Play?APM_Mode=%d&ViewMode=Portrait&DirUrl=%s&FileUrl=%s"
/// "VidPlayer://Play?APM_Mode=%d&ViewMode=Landscape&DirUrl=%s&FileUrl=%s"
/// Plz fill the URL Format:
void LaunchVideoPlayerAppToPlay
(
  AppLaunchMode_e eAppLaunchMode,
  VidListInfo_t *psVidList,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchFileOpRspCbInfo_t *psRspCbInfo
);

/// "VidPlayer://SimplePlayAndSelect?APM_Mode=%d&ViewMode=Portrait&DirUrl=%s&FileUrl=%s"
/// "VidPlayer://SimplePlayAndSelect?APM_Mode=%d&ViewMode=Landscape&DirUrl=%s&FileUrl=%s"
/// Plz fill the URL Format:
void LaunchVideoPlayerAppToSimplePlayAndSelect
(
  AppLaunchMode_e eAppLaunchMode,
  VidListInfo_t *psVidList,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchFileOpRspCbInfo_t *psRspCbInfo
);

/// "VidPlayer://SimplePlay?APM_Mode=%d&ViewMode=Portrait&DirUrl=%s&FileUrl=%s"
/// "VidPlayer://SimplePlay?APM_Mode=%d&ViewMode=Landscape&DirUrl=%s&FileUrl=%s"
void LaunchVideoPlayerAppToSimplePlay
(
 AppLaunchMode_e eAppLaunchMode,
 VidInfo_t *pVideoInfo,
 LaunchAppTransParam_t *psTransParam,
 CmnAppLaunchRspCbInfo_t *psRspCbInfo
 );

/// "VidPlayer://SimplePlay?APM_Mode=%d&ViewMode=Portrait&DirUrl=%s&FileUrl=%s"
/// "VidPlayer://SimplePlay?APM_Mode=%d&ViewMode=Landscape&DirUrl=%s&FileUrl=%s"
void LaunchVideoPlayerAppToPlayStream
(
 AppLaunchMode_e eAppLaunchMode,
 VidStreamInfo_t *pVideoInfo,
 LaunchAppTransParam_t *psTransParam,
 CmnAppLaunchRspCbInfo_t *psRspCbInfo
 );

/// "VidPlayer://PlayAfterSaving?APM_Mode=%d&ViewMode=Portrait&FileUrl=%s"
/// "VidPlayer://PlayAfterSaving?APM_Mode=%d&ViewMode=Landscape&FileUrl=%s"
/// Plz fill the URL Format:
void LaunchVideoPlayerAppToPlayAfterSaving
(
  AppLaunchMode_e eAppLaunchMode,
  VidInfo_t *psVid,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

void LaunchVideoPlayerAppToPlayBuffer
(
 AppLaunchMode_e eAppLaunchMode,
 VidBufInfo_t *pVideoBufInfo,
 LaunchAppTransParam_t *psTransParam,
 CmnAppLaunchRspCbInfo_t *psRspCbInfo
 );

void PostEmbededEvtToVideoPlayerApp
(
    VidPlayerEmbededEvt_e eEvtId,
    u32 nParam,
    CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

// Utility for launching File Manager App to do file listing
void VideoPlayerListFiles(boolean bSimple);

// Utility for launching File Manager App to do file listing
// APM_LAUNCH_EMBEDDED mode is used for Applet and APM_LAUNCH_INTERRUPTIVE mode is used for hot key
void VideoPlayerListFilesEx(boolean bSimple, u32 nLaunchMode);

#endif
