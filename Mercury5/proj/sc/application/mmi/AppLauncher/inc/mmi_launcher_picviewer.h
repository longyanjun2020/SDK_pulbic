#ifndef __MMI_LAUNCHER_PICVIEWER_H__
#define __MMI_LAUNCHER_PICVIEWER_H__

#include "mmi_launcher_common.h"
#include "mmi_srv_filemgr.h"
#include "mmi_launcher_filemanager.h"

/// 1. Cam App,          APM_Mode = APM_LAUNCH_NORMAL,   Mode = PICVIEWER_MODE_LANDSCAPE,        bCardIsInsert = TRUE,  pIVectorModel = one item, nFocusIndex = 0, pFocusDataModel = NULL, pSelectDataModel = NULL, eVectorItemType = PICVIEWER_ITEM_CONTENT, /// store in phone
///                      APM_Mode = APM_LAUNCH_NORMAL,   Mode = PICVIEWER_MODE_PORTRAIT,         bCardIsInsert = TRUE,  pIVectorModel = one item, nFocusIndex = 0, pFocusDataModel = NULL, pSelectDataModel = NULL, eVectorItemType = PICVIEWER_ITEM_CONTENT, /// store in phone
///                      APM_Mode = APM_LAUNCH_NORMAL,   Mode = PICVIEWER_MODE_LANDSCAPE,        bCardIsInsert = FALSE, pIVectorModel = one item, nFocusIndex = 0, pFocusDataModel = NULL, pSelectDataModel = NULL, eVectorItemType = PICVIEWER_ITEM_CONTENT, /// store in phone
///                      APM_Mode = APM_LAUNCH_NORMAL,   Mode = PICVIEWER_MODE_PORTRAIT,         bCardIsInsert = FALSE, pIVectorModel = one item, nFocusIndex = 0, pFocusDataModel = NULL, pSelectDataModel = NULL, eVectorItemType = PICVIEWER_ITEM_CONTENT, /// store in phone
///                      APM_Mode = APM_LAUNCH_EMBEDDED, Mode = PICVIEWER_MODE_SIMPLE_LANDSCAPE, bCardIsInsert = FALSE, pIVectorModel = one item, nFocusIndex = 0, pFocusDataModel = NULL, pSelectDataModel = NULL, eVectorItemType = PICVIEWER_ITEM_IBITMAP, /// store in card
///                      APM_Mode = APM_LAUNCH_EMBEDDED, Mode = PICVIEWER_MODE_SIMPLE_PORTRAIT,  bCardIsInsert = FALSE, pIVectorModel = one item, nFocusIndex = 0, pFocusDataModel = NULL, pSelectDataModel = NULL, eVectorItemType = PICVIEWER_ITEM_IBITMAP, /// store in card
/// 2. File Manager App, APM_Mode = APM_LAUNCH_EMBEDDED, Mode = PICVIEWER_MODE_CROP_WALLPAPER,   pSelectDataModel = pPickerCnt, pIVectorModel = PlayList, pFocusDataModel = Final Focus Idx, nFocusIndex = Cur Focus Idx, eVectorItemType = PICVIEWER_ITEM_CONTENT
///                      APM_Mode = APM_LAUNCH_EMBEDDED, Mode = PICVIEWER_MODE_VIEW_WALLPAPER,   pSelectDataModel = pPickerCnt, pIVectorModel = PlayList, pFocusDataModel = Final Focus Idx, nFocusIndex = Cur Focus Idx, eVectorItemType = PICVIEWER_ITEM_CONTENT
///                      APM_Mode = APM_LAUNCH_EMBEDDED, Mode = PICVIEWER_MODE_SELECT,           pSelectDataModel = pPickerCnt, pIVectorModel = PlayList, pFocusDataModel = Final Focus Idx, nFocusIndex = Cur Focus Idx, eVectorItemType = PICVIEWER_ITEM_CONTENT
///                      APM_Mode = APM_LAUNCH_EMBEDDED, Mode = PICVIEWER_MODE_VIEW_SIMPLE,      pSelectDataModel = NULL,       pIVectorModel = PlayList, pFocusDataModel = Final Focus Idx, nFocusIndex = Cur Focus Idx, eVectorItemType = PICVIEWER_ITEM_CONTENT
///                      APM_Mode = APM_LAUNCH_EMBEDDED, Mode = PICVIEWER_MODE_SLIDESHOW,        pSelectDataModel = NULL,       pIVectorModel = PlayList, pFocusDataModel = Final Focus Idx, nFocusIndex = Cur Focus Idx, eVectorItemType = PICVIEWER_ITEM_CONTENT
///                      APM_Mode = APM_LAUNCH_EMBEDDED, Mode = PICVIEWER_MODE_CROP_WALLPAPER,   pSelectDataModel = NULL,       pIVectorModel = PlayList, pFocusDataModel = Final Focus Idx, nFocusIndex = Cur Focus Idx, eVectorItemType = PICVIEWER_ITEM_CONTENT
///                      APM_Mode = APM_LAUNCH_EMBEDDED, Mode = PICVIEWER_MODE_VIEW,             pSelectDataModel = NULL,       pIVectorModel = PlayList, pFocusDataModel = Final Focus Idx, nFocusIndex = Cur Focus Idx, eVectorItemType = PICVIEWER_ITEM_CONTENT
/// 3. Sea App,          APM_Mode = APM_LAUNCH_EMBEDDED, Mode = PICVIEWER_MODE_VIEW_SIMPLE,      pSelectDataModel = NULL,       pIVectorModel = PlayList, pFocusDataModel = NULL,            nFocusIndex = 0,             eVectorItemType = PICVIEWER_ITEM_URL
/// 4. Search App,       APM_Mode = APM_LAUNCH_EMBEDDED, Mode = PICVIEWER_MODE_VIEW,             pSelectDataModel = NULL,       pIVectorModel = PlayList, pFocusDataModel = NULL,            nFocusIndex = 0,             eVectorItemType = PICVIEWER_ITEM_CONTENT
/// 5. Sva App,          APM_Mode = APM_LAUNCH_EMBEDDED, Mode = PICVIEWER_MODE_VIEW_SIMPLE,      pSelectDataModel = NULL,       pIVectorModel = PlayList, pFocusDataModel = NULL,            nFocusIndex = 0,             eVectorItemType = PICVIEWER_ITEM_URL

typedef enum
{
    PICVIEWER_LAUNCH_MODE_VIEW,
    PICVIEWER_LAUNCH_MODE_SELECT,
#ifdef __MMI_PICVIEWER_SLIDESHOW_ENABLE__
    PICVIEWER_LAUNCH_MODE_SLIDESHOW,
#endif
    PICVIEWER_LAUNCH_MODE_LANDSCAPE,
    PICVIEWER_LAUNCH_MODE_PORTRAIT,
    PICVIEWER_LAUNCH_MODE_CROP_WALLPAPER,
    PICVIEWER_LAUNCH_MODE_VIEW_WALLPAPER,
    PICVIEWER_LAUNCH_MODE_VIEW_SIMPLE,
    PICVIEWER_LAUNCH_MODE_VIEW_ALL,
    PICVIEWER_LAUNCH_MODE_SIMPLE_PORTRAIT,
    PICVIEWER_LAUNCH_MODE_SIMPLE_LANDSCAPE,
    PICVIEWER_LAUNCH_MODE_NUM,
    PICVIEWER_LAUNCH_MODE_INVALID
} PicViewerLaunchMode_e;

typedef enum
{
    PICVIEWER_LAUNCH_ITEM_URL,
    PICVIEWER_LAUNCH_ITEM_IBITMAP,
    PICVIEWER_LAUNCH_ITEM_FILELIST,
    PICVIEWER_LAUNCH_ITEM_BUFFER
} PicViewerLaunchItemType_e;

typedef struct
{
    PicViewerLaunchMode_e       eLaunchMode;
    PicViewerLaunchItemType_e   eItemType;
    MAE_WChar                   *pPathUrl;
    VFS_FileID_t                *pFileId;
} PicFileListInfo_t;

typedef struct
{
    PicViewerLaunchMode_e       eLaunchMode;
    PicViewerLaunchItemType_e   eItemType;
    MAE_WChar                   *pFileUrl;  //full path
} PicUrlInfo_t;

#define CAM_PIC_LIST_MAX_SIZE    9

typedef struct
{
    PicViewerLaunchMode_e       eLaunchMode;
    PicViewerLaunchItemType_e   eItemType;
    u16                         nListSize;
    MAE_WChar                   *pFileUrl[CAM_PIC_LIST_MAX_SIZE];  //full path
    boolean                     bEnableBlogLink;
} PicUrlListInfo_t;

typedef struct
{
    PicViewerLaunchMode_e       eLaunchMode;
    PicViewerLaunchItemType_e   eItemType;
    u8                          *pBuffer;
    u32                         nBufLen;
} PicBufferInfo_t;

typedef enum
{
    PICVIEWER_RSP_EVT_FOCUS_ON_FOLDERLIST_FILE,
    PICVIEWER_RSP_EVT_SELECT_ON_FOLDERLIST_FILE,
    PICVIEWER_RSP_EVT_DELETE_ON_FOLDERLIST_FILE,
    PICVIEWER_RSP_EVT_FOCUS_ON_URL_FILE,
    PICVIEWER_RSP_EVT_SELECT_ON_URL_FILE,
    PICVIEWER_RSP_EVT_DELETE_ON_URL_FILE,
    PICVIEWER_RSP_EVT_NULL
} PicViewerRspEvent_e;

/// "PicViewer://Play?APM_Mode=%d&ViewMode=Portrait&DirUrl=%s&FileUrl=%s"
/// "PicViewer://Play?APM_Mode=%d&ViewMode=Landscape&DirUrl=%s&FileUrl=%s"
/// Plz fill your URL Format
void LaunchPicViewerAppToPlay
(
    AppLaunchMode_e eAppLaunchMode,
    PicFileListInfo_t *pPicFileList,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchFileOpRspCbInfo_t *pRspCbInfo
);

/// "PicViewer://SimplePlay?APM_Mode=%d&ViewMode=Portrait&DirUrl=%s&FileUrl=%s"
/// "PicViewer://SimplePlay?APM_Mode=%d&ViewMode=Landscape&DirUrl=%s&FileUrl=%s"
/// Plz fill your URL Format
void LaunchPicViewerAppToSimplePlay
(
    AppLaunchMode_e eAppLaunchMode,
    PicUrlInfo_t *pPicUrl,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchFileOpRspCbInfo_t *pRspCbInfo
);

/// "PicViewer://SimplePlayAll?APM_Mode=%d&ViewMode=Portrait&DirUrl=%s&FileUrl=%s"
/// "PicViewer://SimplePlayAll?APM_Mode=%d&ViewMode=Landscape&DirUrl=%s&FileUrl=%s"
/// Plz fill your URL Format
void LaunchPicViewerAppToSimplePlayAll
(
    AppLaunchMode_e eAppLaunchMode,
    PicFileListInfo_t *pPicFileList,
    LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchFileOpRspCbInfo_t *pRspCbInfo
);

void LaunchPicViewerAppToSimplePlayBuffer
(
    AppLaunchMode_e eAppLaunchMode,
    PicBufferInfo_t *pPicBuf,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchFileOpRspCbInfo_t *pRspCbInfo
);

#ifdef __MMI_PICVIEWER_SLIDESHOW_ENABLE__
/// "PicViewer://SlideShow?APM_Mode=%d&ViewMode=Portrait&DirUrl=%s&FileUrl=%s"
/// "PicViewer://SlideShow?APM_Mode=%d&ViewMode=Landscape&DirUrl=%s&FileUrl=%s"
/// Plz fill your URL Format
void LaunchPicViewerAppToPlaySlideShow
(
    AppLaunchMode_e eAppLaunchMode,
    PicFileListInfo_t *pPicFileList,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchFileOpRspCbInfo_t *pRspCbInfo
);
#endif

/// "PicViewer://PlayAndSelect?APM_Mode=%d&ViewMode=Portrait&DirUrl=%s&FileUrl=%s"
/// "PicViewer://PlayAndSelect?APM_Mode=%d&ViewMode=Landscape&DirUrl=%s&FileUrl=%s"
/// Plz fill your URL Format
void LaunchPicViewerAppToPlayAndSelect
(
    AppLaunchMode_e eAppLaunchMode,
    PicFileListInfo_t *pPicFileList,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchFileOpRspCbInfo_t *pRspCbInfo
);

///  "PicViewer://PlayAfterSaving?APM_Mode=%d&ViewMode=Portrait&FileUrl=%s"
///  "PicViewer://PlayAfterSaving?APM_Mode=%d&ViewMode=Landscape&FileUrl=%s"
///  Plz fill your URL Format
void LaunchPicViewerAppToPlayAfterSaving
(
    AppLaunchMode_e eAppLaunchMode,
    PicUrlListInfo_t *pPicUrlList,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchFileOpRspCbInfo_t *pRspCbInfo
);

/// "PicViewer://CropPic?APM_Mode=%d&ViewMode=Portrait&FileUrl=%s"
/// "PicViewer://CropPic?APM_Mode=%d&ViewMode=Landscape&FileUrl=%s"
/// Plz fill your URL Format
void LaunchPicViewerAppToCropPic
(
    AppLaunchMode_e eAppLaunchMode,
    PicUrlInfo_t *pPicUrl,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchFileOpRspCbInfo_t *pRspCbInfo
);

// Utility for launching File Manager App to do file listing
void PictureViewerListFiles(void);

// Utility for launching File Manager App to do file listing
// APM_LAUNCH_EMBEDDED mode is used for Applet and APM_LAUNCH_INTERRUPTIVE mode is used for hot key
void PictureViewerListFilesEx(u32 nLaunchMode);

#if defined(__ATV_MMI__)
// Utility for launching File Manager App to do file listing
void PictureViewerListFiles4ATV(void);
#endif


#endif /* __MMI_LAUNCHER_PICVIEWER_H__ */
