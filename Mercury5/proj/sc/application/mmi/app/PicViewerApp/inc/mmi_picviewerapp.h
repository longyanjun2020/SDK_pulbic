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
* @file    mmi_picviewerapp.h
* @version
* @brief   Picture viewer applet header file
*
*/

#ifndef __MMI_PICVIEWERAPP_H__
#define __MMI_PICVIEWERAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_common_wdgvar.h"
#include "mmi_launcher_picviewer.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define PV_FILE_URL_LIST_SIZE  9

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    PICVIEWER_MODE_VIEW,            // For file manager view
    PICVIEWER_MODE_SELECT,          // For file manager pick
#ifdef __MMI_PICVIEWER_SLIDESHOW_ENABLE__
    PICVIEWER_MODE_SLIDESHOW,       // For file manager slide show
#endif
    PICVIEWER_MODE_LANDSCAPE,       // For camera landscape mode
    PICVIEWER_MODE_PORTRAIT,        // For camera portrait mode
    PICVIEWER_MODE_CROP_WALLPAPER,  // For cropping wallpaper
    PICVIEWER_MODE_VIEW_WALLPAPER,  // For viewing wallpaper. In display settings, user presses action key to view a wallpaper.
    PICVIEWER_MODE_VIEW_SIMPLE,     // For viewing picture but CANNOT set as, delete, send, view info, ...,etc.
    PICVIEWER_MODE_VIEW_ALL,        // For Wap viewing picture(only back and view).
    PICVIEWER_MODE_SIMPLE_PORTRAIT, // For camera portrait mode without delete function(only back).
    PICVIEWER_MODE_SIMPLE_LANDSCAPE // For camera landscape mode without delete function(only back).
} PicViewerMode_e;

typedef enum
{
    PICVIEWER_ITEM_URL,
    PICVIEWER_ITEM_IBITMAP,
    PICVIEWER_ITEM_FILELIST,
    PICVIEWER_ITEM_BUFFER
} PicViewerItemType_e;

typedef struct
{
    PicViewerMode_e eMode;
    PicViewerItemType_e eItemType;
    MAE_WChar   *pPathUrl;
    VFS_FileID_t    *pFileId;
    u32         nFileUrlListSize;
    MAE_WChar   *pFileUrlList[PV_FILE_URL_LIST_SIZE];
    u8          *pBuffer;
    u32         nBufLen;
    u32 nClient;
    boolean bEnableBlogLink;
    CmnLaunchAppFileOpRspCb pfnRspCb;
} PicViewerAppParam_t;

/*=============================================================*/
// Global function prototype declaration
/*=============================================================*/
MAE_Ret PicViewerAppNew(MAE_ClsId nClsId, void **ppObj);
void PicViewerPreNew(void);

#endif /* __MMI_PICVIEWERAPP_H__ */
