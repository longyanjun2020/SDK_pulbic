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
* @file    mmi_filemgrapp_fileinfo.h
* @version
* @brief
*
*/

#ifndef __MMI_FILEMGRAPP_FILEINFO_H__
#define __MMI_FILEMGRAPP_FILEINFO_H__
/*==============================================================================
INCLUDE FILES FOR MODULE
==============================================================================*/
#include "mmi_filemgrapp_priv.h"
#include "mmi_filemgrapp_util.h"

#define FILEINFO_DISP_STR_LEN       (2048)

typedef struct FileMgrFileInfoInitWndData_t_
{
    u32                     nDurationTime;
    FileMgrAppFileInfo_t    tSelectedFileInfo;

} FileMgrFileInfoInitWndData_t;

typedef struct _FileMgrFileInfoWndData
{
    u32                     nDurationTime;
    FileMgrAppFileInfo_t    tSelectedFileInfo;

}FileMgrFileInfoWndData_t;

/*==============================================================================
FUNCTION DECLARATIONS
==============================================================================*/
#define     MS_PER_SECOND    1000
/*-------------------------------------------------------------------------------------------------*/
MAE_Ret FileMgrAppFileInfoSetView(MmiFileMgrApp *pThis);
MAE_Ret FileMgrAppFileInfoShowUI(MmiFileMgrApp *pThis, FileMgrFileInfoWndData_t *pFileInfoWndData);

/*-------------------------------------------------------------------------------------------------*/
MAE_Ret FileMgrAppFileInfoCreateWindow(MmiFileMgrApp *pThis, u32 nDuration);

/*-------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------*/
/*==============================================================================*/

MAE_Ret FileMgrAppMemStatusSetView(MmiFileMgrApp* pThis, FileMgrAppMemStatusViewMode_e eViewLoad);

void FileMgrAppFileInfoAudCallback(void *pApplet, MediaSrvErrCode_e eErrorCode, u32 nCusData, AudioSrvFileInfo_t *pAudFileInfo);
void FileMgrAppFileInfoVodCallback(void *pApplet, MediaSrvErrCode_e eErrorCode, VideoPlayerSrvDataInfo_t *pVideoInfo);

#endif  /* __MMI_FILEMGRAPP_FILEINFO_H__ */
