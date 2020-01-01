/**
* @file mmi_VideoStreaming.h
*
* This header file defines the data structure of video streaming.
*
*/

#ifndef __MMI_VIDEOSTREAMING_H__
#define __MMI_VIDEOSTREAMING_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "mmi_VideoPlayerSrv.h"
/*=============================================================*/
// Type Declarations
/*=============================================================*/
#define VDO_STM_TEMP_FILE_LIMIT 50

typedef struct VdoStmTmpFileInfo_t_
{
    MAE_WChar *pFilePath;
    u32 nTmpFileSize;
    u32 nFileSize;
    u16 nIndex;
} VdoStmTmpFileInfo_t;

/*=============================================================*/
// Function Declaration
/*=============================================================*/
MAE_Ret VideoStreamingGetTempFileInfo(VideoSrvHandle_t pVdoSrvHdl, MAE_WChar *pDownloadUrl, VdoStmTmpFileInfo_t *pTmpFileInfo);
MAE_WChar *VideoStreamingGenTempFilePath(VideoSrvHandle_t pVdoSrvHdl, MAE_WChar *pDownloadUrl, MediaSrvMimeType_e eMimeType);
VideoPlayerSrvDownloadModuleCb VideoStreamingGetDownloadItf(VideoSrvHandle_t pVdoSrvHdl, MAE_WChar *pDownloadUrl);
MAE_Ret VideoStreamingUpdateFileSize(VideoSrvHandle_t pVdoSrvHdl, MAE_WChar *pDownloadUrl, u32 nFileSize);
/*=============================================================*/
// UnitTest Function Declaration
/*=============================================================*/
void VideoStreamingSetMaxTempFileNum(u16 nTempFileNum);
MAE_WChar* VideoStreamingGetFileListPath(void);

#endif /* __MMI_VIDEOSTREAMING_H__ */
