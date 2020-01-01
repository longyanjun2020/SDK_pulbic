////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    mmi_videoplayerapp.h
* @version
* @brief   Video player applet header file
*
*/

#ifndef __MMI_VIDEOPLAYERAPP_H__
#define __MMI_VIDEOPLAYERAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_filemgrapp.h"
#include "mmi_mediasrv_common.h"
#include "mmi_videoplayersrv.h"

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    VIDEOPLAYER_MODE_PREVIEW_PORTRAIT,
    VIDEOPLAYER_MODE_PREVIEW_LANDSCAPE,
    VIDEOPLAYER_MODE_PICK_PORTRAIT,
    VIDEOPLAYER_MODE_PICK_LANDSCAPE,
    VIDEOPLAYER_MODE_CAMCORDER_PORTRAIT,
    VIDEOPLAYER_MODE_CAMCORDER_LANDSCAPE,
    VIDEOPLAYER_MODE_SIMPLE_PORTRAIT,
    VIDEOPLAYER_MODE_SIMPLE_LANDSCAPE,
    VIDEOPLAYER_MODE_SIMPLE_BUFFER_PORTRAIT,
    VIDEOPLAYER_MODE_SIMPLE_BUFFER_LANDSCAPE,
    VIDEOPLAYER_MODE_SIMPLE_STREAMING_PORTRAIT,
    VIDEOPLAYER_MODE_SIMPLE_STREAMING_LANDSCAPE
}MMI_VIDEOPLAYERAPP_MODE_e;

typedef struct
{
    MMI_VIDEOPLAYERAPP_MODE_e eMode;	// Indicate how video player is activated
    IVectorModel *pIVectorModel;	// It stores the UID (video id) to be played in video player
    u32 nFocusIndex;	// It stores the index in the vector model to be played in the videoplayerapp
    IDataModel *pFocusDataModel; // It is used to inform the caller ap which UID is focused.
    IDataModel *pIDataModel;	// It is used to inform the caller ap which UID is selected (It is used in the mode VIDEOPLAYER_MODE_PICK), or it can be null.
    //New
    MAE_WChar wDirUrl[FILEMGR_MAX_FILEPATH_SIZE];
    MAE_WChar *pFileUrl;
    //void *pCBData;
    VFS_FileID_t    *pFileId;
    u32 nClient;
    //PlayBuffer
    u8 *pBuf;
    u32 nBufLen;
    MediaSrvMimeType_e eMimeType;
    CmnLaunchAppFileOpRspCb pfnRspCb;
    CmnLaunchAppDataRspCb pfnResumePosRspCb;
    u32 nResumePos;
    VideoPlayerSrvStreamingMode_e eStreamingMode;
    void *pfnDownloadItf;
}MMI_VIDEOPLAYERAPP_PARAMS;

/*=============================================================*/
// Global function prototype declaration
/*=============================================================*/
MAE_Ret VideoPlayerNew(MAE_ClsId nClsId, void **ppObj);
void VideoPlayerPreNew(void);

#endif /* __MMI_VIDEOPLAYERAPP_H__ */
