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
* @file    mmi_filemgrapp_common.h
* @version
* @brief
*
*/

#ifndef __MMI_FILEMGRAPP_UTIL_H__
#define __MMI_FILEMGRAPP_UTIL_H__
/*==============================================================================
                       INCLUDE FILES FOR MODULE
==============================================================================*/
#include "mmi_accessorysrv.h"
#include "mmi_common_mimetype.h"
#include "mmi_filemgrapp.h"
#include "mmi_filemgrapp_custom.h"
#include "mmi_filemgrapp_cmn.h"

#include "mmi_filemgrapp_cfg.h"
#include "mmi_objprocessingsrv.h"
#include "mmi_common_custom.h"
#include "mmi_common_dialog.h"
#include "mmi_base_util.h"
#include "mmi_srv_header.h"

/*===========================================================================
                       TYPE DECLARATIONS
============================================================================*/
#define __FILEMGRAPP_SELLIST_IN_ARRAY__

#define __FILEMGRAPP_RENAME_FOLDER__

#if !defined(__FILEMGRAPP_ITEMLIST_LIMIT__)
#define __FEATURE_UNSUPPORTED_FILE_CPMV__
#define __FILEMGRAPP_EMPTYFILE_CPMV__
#endif

#define __FILEMGRAPP_CRUNCHED__

#define __FILEMGRAPP_GRIDTHUMB_MARK_SUPPORT__

#define __FILEMGRAPP_COUNT_CAN_SEL_FILES__

#ifdef  BREAKIFLOGERR
#undef  BREAKIFLOGERR
#endif
#define BREAKIFLOGERR(str,ret)  {   if(MAE_RET_SUCCESS != ret){\
                                        LOG_ERROR(MMI_LEVEL_FILEMGR, str,ret);\
                                        break; \
                                }}

#ifdef  BREAKIFZERO
#undef  BREAKIFZERO
#endif
#define BREAKIFZERO(a, ret) { if(a == 0){\
                                ret = MAE_RET_FAILED; break; \
                            }}

#define FMAP_SETIF(p, v) {if(p){*p=v;}}

#ifndef MIN
#define MIN(a,b)    ((a) < (b) ? (a) : (b))
#endif

#define FILEMGRAPP_LEVEL_ROOT  0   // for folders at root level

#define BATCH_DEALING_CNT		(200)
#define FILE_NOT_FOUND			(0xFFFFFFFF)

#define FILEMGRAPP_ITEMCOUNT_ONEPIECE      (50)      // every time we hold in the vector model, REAL_LIST
#define FILEMGRAPP_ITEMCOUNT_GETHALFPIECE  (FILEMGRAPP_ITEMCOUNT_ONEPIECE/2)

#define FILEMGRAPP_CONTENTSORTATTR_COUNT   (4)   // sort content while listing by attributes, please refer to aCntAttrSort

#define FILEMGRAPP_ITEMIDX_NONE             0xffff  // atcurally, FILEMGRAPP_ITEMCOUNT_MAX is the maximal #

#define FILEMGRAPP_OPTMDL_SIZE_MAX          25

#define FILEMGRAPP_MARK_ALL_LIMIT_CNT      (300)

/* 2008-Jul-16, Elvis, #21673 {*/
#define FILEMGRAPP_THUMBGRID_MENU_CACHE     (RS_FILEMGRAPP_THUMBGRID_NUM_V*(RS_FILEMGRAPP_THUMBGRID_NUM_H+3))
#define FILEMGRAPP_THUMBGRID_MENU_DIFF      RS_FILEMGRAPP_THUMBGRID_NUM_V
#define FILEMGRAPP_DETAILITEM_MENU_CACHE    (FILEMGRAPP_DETAILITEM_MENU_DIFF*3)
#define FILEMGRAPP_DETAILITEM_MENU_DIFF     ((RS_MAIN_DEFVIEW_HEIGHT-RS_MAIN_TITLE_HEIGHT)/RS_MAIN_LCD_TWOLINE_HEIGHT)
#define FILEMGRAPP_BRIEFITEM_MENU_CACHE     (FILEMGRAPP_BRIEFITEM_MENU_DIFF*3)
#define FILEMGRAPP_BRIEFITEM_MENU_DIFF      ((RS_MAIN_DEFVIEW_HEIGHT-RS_MAIN_TITLE_HEIGHT)/RS_MAIN_LCD_ONELINE_HEIGHT)
/* 2008-Jul-16, Elvis, #21673 }*/

#define FILEMGRAPP_AUTO_CLOSE_DIALOG_TIMER  COMMON_DIALOG_AUTOCLOSE_TIME /* The auto close timer for the popup dialog is 2 seconds = 2000 miliseconds. */
#if defined(__PC_SIMULATOR__)
#define FILEMGRAPP_AUTO_CLOSE_DIALOG_TIMER2  (1000)
#else
#define FILEMGRAPP_AUTO_CLOSE_DIALOG_TIMER2  (100)
#endif

#define FILEMGRAPP_AUDIO_SKIPCMD_AGAIN_TIMER    300

#define FILEMGRAPP_OBJOP_SUCCESS_STR            L"%s %s"
#define FILEMGRAPP_OBJOP_SUCCESS_NO_SPACE_STR   L"%s%s"
#define FILEMGRAPP_DLG_CONCATENATE_STR          L"%s. %s"

#define FILEMGRAPP_MEMSTATUS_LOCATION_FORMAT_STR    L"<%s>"

#define FILEMGRAPP_THUMBLIST_SIZE_INIT		(12)
#define FILEMGRAPP_THUMBLIST_SIZE_GROW		(12)

#ifdef __FILEMGRAPP_ID3V2_IMG__
#define FILEMGRAPP_ID3V2_IMAGELIST_SIZE_INIT    (12)
#define FILEMGRAPP_ID3V2_IMAGELIST_SIZE_GROW    (12)
#endif

#ifdef  __FILEMGRAPP_SELLIST_IN_ARRAY__
    #define FILEMGRAPP_SELSEL_LIST_SIZE_INIT    10
    #define FILEMGRAPP_SELSEL_LIST_SIZE_GROW    10
#endif  /* __FILEMGRAPP_SELLIST_IN_ARRAY__ */

#define FILEMGRAPP_FOLDERHISTORY_LIST_SIZE_INIT 5
#define FILEMGRAPP_FOLDERHISTORY_LIST_SIZE_GROW 5

#if defined(__PC_SIMULATOR__)
#define FILEMGR_SEND_UT_FUNCTION_NAME(str) \
    { \
        LOG_TRACE(MMI_LEVEL_FILEMGR, "\n@@" str); \
        SEND_UT_FUNCTION_NAME(str); \
    }

#else
#define FILEMGR_SEND_UT_FUNCTION_NAME(str)
#endif

#define MMI_FILEMGRAPP_MONITOR_TYPE \
    (FILE_MGR_OPR__RENAME_BY_FOLDER|FILE_MGR_OPR__RMDIR_BY_FOLDER|FILE_MGR_OPR__DELETE_BY_FOLDER|FILE_MGR_OPR__COPY_BY_FOLDER|FILE_MGR_OPR__MOVE_BY_FOLDER|FILE_MGR_OPR__ADD_BY_FOLDER|FILE_MGR_OPR__MKDIR_BY_FOLDER|FILE_MGR_OPR__DELETE_ALL_BY_FOLDER)


typedef enum{
    // error
    // Reminder: if we add new return code here, we also need to check MMI_Filemgrapp_NameObj_CheckAnUpdate_SaveName NEWDIR error code
    MMI_FILEMGRAPP_RET_OUTOFBOUND = 0x0800,
    MMI_FILEMGRAPP_RET_INVALIDFN,
    MMI_FILEMGRAPP_RET_DUPLICATEFN,
    MMI_FILEMGRAPP_RET_QUERYNOMATCHED,
    MMI_FILEMGRAPP_FS_ERROR,
    MMI_FILEMGRAPP_DB_ERROR,
    MMI_FILEMGRAPP_DEL_DENIED_FOLDER,
    MMI_FILEMGRAPP_DEL_DENIED_FILE,
#ifdef  __FILEMGRAPP_COPYMOVE_FOLDER_ENABLE__
    MMI_FILEMGRAPP_CPMV_DENIED_FOLDER,
#endif  /* __FILEMGRAPP_COPYMOVE_FOLDER_ENABLE__ */
    MMI_FILEMGRAPP_CPMV_DENIED_FILE,
    MMI_FILEMGRAPP_RET_NOSPACEFORFOLDERNAME,
    MMI_FILEMGRAPP_RET_NO_ITEM,
    MMI_FILEMGRAPP_RET_MPLAYER_USED
}FileMgrAppRetCode_e;

typedef enum{
    MMI_FILEMGRAPP_DLG_NONE = 0x00,
    MMI_FILEMGRAPP_DLG_UNSUPPORT,   // unsupported media
    MMI_FILEMGRAPP_DLG_CANNTPLAYMEDIA,  // cannot play media
    MMI_FILEMGRAPP_DLG_MEDIAERROR, //corrupted data
    MMI_FILEMGRAPP_DLG_PLAYFAILED, // Failed to play a file
#ifdef __APP_MMI_CALL_BACKGROUND_SOUND__
    MMI_FILEMGRAPP_DLG_PLAYFAILED_CBS_PLAYING, // Failed to play a file due to playing call background sound
#endif
    MMI_FILEMGRAPP_DLG_PLAYFAILED_IN_CALL, // Failed to play a file due to in call
    MMI_FILEMGRAPP_DLG_INVALIDNAME,    // invalid name
    MMI_FILEMGRAPP_DLG_OPSUCCESS,   // %s %s (1.folder, file; 2. copied,moved,renamed,deleted)
    MMI_FILEMGRAPP_DLG_OPCANCELED,
    MMI_FILEMGRAPP_DLG_STORAGESEL,
    MMI_FILEMGRAPP_DLG_INSUFFICIENTSTORAGE,
    MMI_FILEMGRAPP_DLG_CPMVWAITING,
    MMI_FILEMGRAPP_DLG_PARTIALFAILED,
    MMI_FILEMGRAPP_DLG_SETASDONE,
    MMI_FILEMGRAPP_DLG_SETSORTFAILED,
    MMI_FILEMGRAPP_DLE_SETLISTFAILED,
    MMI_FILEMGRAPP_DLG_DESTAPFAILED,    // destination ap failed.
    MMI_FILEMGRAPP_DLG_EXTCARD_ABSENT,
    MMI_FILEMGRAPP_DLG_EXTCARD_NOTREADY,
    MMI_FILEMGRAPP_DLG_DEL_DENIED_FOLDER,
    MMI_FILEMGRAPP_DLG_DEL_DENIED_FILES,
    MMI_FILEMGRAPP_DLG_FILEPATH_TOO_LONG,
    MMI_FILEMGRAPP_DLG_INFO_UNAVAILABLE,
    MMI_FILEMGRAPP_DLG_NO_ITEM_SEL,
    MMI_FILEMGRAPP_DLG_OUT_OF_BOUND,
    MMI_FILEMGRAPP_DLG_CANNOT_LAUNCH_AP,
    MMI_FILEMGRAPP_DLG_IMG_TOO_LARGE,
    MMI_FILEMGRAPP_DLG_INVALID_IMG,
    MMI_FILEMGRAPP_DLG_CANNOT_CREATE_DEFAULT_DIR,
    MMI_FILEMGRAPP_DLG_LAUNCH_INIT_ERROR,
    MMI_FILEMGRAPP_DLG_PLZ_INSERT_EXTCARD,
    MMI_FILEMGRAPP_DLG_EXTCARD_UNAVAILABLE,
    MMI_FILEMGRAPP_DLG_FILENAME_TOOLONG,
    MMI_FILEMGRAPP_DLG_CPMV_COPY_DENIED,
    MMI_FILEMGRAPP_DLG_CPMV_MOVE_DENIED,
    MMI_FILEMGRAPP_DLG_IN_MPLAYER_USE,
    MMI_FILEMGRAPP_DLG_IMEDIA_DEVICE_UNSUPPORTED,
    MMI_FILEMGRAPP_DLG_PLZ_WAIT,
    MMI_FILEMGRAPP_DLG_PLZ_WAIT_CANCEL,
    MMI_FILEMGRAPP_DLG_FS_BUSY,
    MMI_FILEMGRAPP_DLG_USB_ACTIVATED,
    MMI_FILEMGRAPP_DLG_OUT_OF_SORT_FILE_NUM,
    MMI_FILEMGRAPP_DLG_RIGHTS_INVALID,
#ifdef __MMI_OMA_DRM_V1__
    MMI_FILEMGRAPP_DLG_RIGHTS_CONFIRM_DOWNLOAD,
    MMI_FILEMGRAPP_DLG_CONFIRM_UNMARK_DRM_FILES,
#endif
    MMI_FILEMGRAPP_DLG_UNSUPPORTED_RESOLUTION,
    MMI_FILEMGRAPP_DLG_UNSUPPORTED_FORMAT,
    MMI_FILEMGRAPP_DLG_PASSWORD_PROTECTED,
    MMI_FILEMGRAPP_DLG_FAIL,
    MMI_FILEMGRAPP_DLG_MAX
}FileMgrAppDlgType_e;

typedef enum{
    MMI_FILEMGRAPP_SETAS_NONE = 0x80,
    MMI_FILEMGRAPP_SETAS_WALLPAPER,
    MMI_FILEMGRAPP_SETAS_DEFAULTRINGER,
    MMI_FILEMGRAPP_SETAS_DEFAULTCALLERIMG,
    MMI_FILEMGRAPP_SETAS_RINGID,
    MMI_FILEMGRAPP_SETAS_IMAGEID,
    MMI_FILEMGRAPP_SETAS_PWRONRINGER,
    MMI_FILEMGRAPP_SETAS_PWROFFRINGER,
    MMI_FILEMGRAPP_SETAS_PWRONIMAGE,
    MMI_FILEMGRAPP_SETAS_PWROFFIMAGE,
	MMI_FILEMGRAPP_SETAS_ALARM,
#ifdef  FEATURE_VIDEORINGER_SUPPORTED
    MMI_FILEMGRAPP_SETAS_VIDRINGER,
    MMI_FILEMGRAPP_SETAS_PERSONALVIDRINGER,
#endif  // FEATURE_VIDEORINGER_SUPPORTED
    MMI_FILEMGRAPP_SETAS_MAX
}FileMgrAppSetAsFor_e;

typedef enum{
    MMI_FILEMGRAPP_OP_NONE,
    MMI_FILEMGRAPP_OP_NEWDIR,
    MMI_FILEMGRAPP_OP_RENAMEFILE,
    MMI_FILEMGRAPP_OP_RENAMEFOLDER,
    MMI_FILEMGRAPP_OP_DELETE,
    MMI_FILEMGRAPP_OP_DELETEFOLDER,
    MMI_FILEMGRAPP_OP_COPY,
    MMI_FILEMGRAPP_OP_MOVE,
    MMI_FILEMGRAPP_OP_PLAYAUD,
    MMI_FILEMGRAPP_OP_LAUNCHAP,
    MMI_FILEMGRAPP_OP_SLIDESHOW,
    MMI_FILEMGRAPP_OP_SETVALUE,
    MMI_FILEMGRAPP_OP_CROP_WALLPAPER, // Set As wallpaper or in display setting, user presses LSK key to crop a wallpaper..
    MMI_FILEMGRAPP_OP_VIEW_WALLPAPER, // In display setting, user presses action key to view a wallpaper.
    MMI_FILEMGRAPP_OP_MAX
}FileMgrAppOpOP_e;

typedef enum{
    MMI_FILEMGRAPP_ACT_NONE,
    MMI_FILEMGRAPP_ACT_APM_STOP,
    MMI_FILEMGRAPP_ACT_APM_SUSPEND,
    MMI_FILEMGRAPP_ACT_MENU_SELECT,
    MMI_FILEMGRAPP_ACT_MENU_OPT,
    MMI_FILEMGRAPP_ACT_MENU_BACK,
    MMI_FILEMGRAPP_ACT_MENU_EXIT,
    MMI_FILEMGRAPP_ACT_MENU_STOP,
    MMI_FILEMGRAPP_ACT_MENU_SET,
    MMI_FILEMGRAPP_ACT_MENU_STORAGECHANGE,
    MMI_FILEMGRAPP_ACT_MENU_FOCUSCHANGE,
    MMI_FILEMGRAPP_ACT_CARD_CHANGE, // eject, inserted, readable
    MMI_FILEMGRAPP_ACT_CANCEL_OP,
    MMI_FILEMGRAPP_ACT_MAX
}FileMgrAppAct_e;

typedef enum{
    MMI_FILEMGRAPP_CARDACT_NONE,
    MMI_FILEMGRAPP_CARDACT_EJECT,
    MMI_FILEMGRAPP_CARDACT_INSERTED,
    MMI_FILEMGRAPP_CARDACT_READABLE,
    MMI_FILEMGRAPP_CARDACT_MAX
}FileMgrAppExtCardAct_e;

typedef enum{
    MMI_FILEMGRAPP_OPRSLT_NONE,
    MMI_FILEMGRAPP_OPRSLT_SUCCESS,
    MMI_FILEMGRAPP_OPRSLT_FAILED,
    MMI_FILEMGRAPP_OPRSLT_PARTIALFAILED,
    MMI_FILEMGRAPP_OPRSLT_MPLAY_USED,
    MMI_FILEMGRAPP_OPRSLT_FSFULL,
	MMI_FILEMGRAPP_OPRSLT_FILENAME_TOOLONG,
    MMI_FILEMGRAPP_OPRSLT_MAX
}FileMgrAppOPRslt_e;

typedef enum
{
    MMI_FILEMGRAPP_TRV_NONE,
    MMI_FILEMGRAPP_TRV_DEEP,
    MMI_FILEMGRAPP_TRV_PLANE,
    MMI_FILEMGRAPP_TRV_UP,
    MMI_FILEMGRAPP_TRV_FORCE_PLANE, // eject card in Full Browsing
    MMI_FILEMGRAPP_TRV_FORCE_UP,    // eject card in Lister
    MMI_FILEMGRAPP_TRV_FORCE_REFRESH_EJECT, // eject card and refresh current folder in Lister
    MMI_FILEMGRAPP_TRV_FORCE_HOLD_EJECT,    // eject card and hold (do not refresh current folder) in Lister
    MMI_FILEMGRAPP_TRV_FORCE_REFRESH_INSERT,// card readable and refresh current folder in Lister
    MMI_FILEMGRAPP_TRV_FORCE_HOLD_INSERT,   // card readable and hold in Lister
#if defined(__ONBOARD_USER_STORAGE_MMI__) || defined(__CAMERA_MMI_USE_PHONE_STORAGE__)
    MMI_FILEMGRAPP_TRV_VOL_DISK_LIST,
#endif
    MMI_FILEMGRAPP_TRV_MAX
}FileMgrAppTraverseMode_e;

typedef enum
{
#ifdef __FILEMGRAPP_PHONESTORAGE__
    MMI_FILEMGRAPP_STORAGE_PHONE,
#endif
    MMI_FILEMGRAPP_STORAGE_CARD,
#if defined(__DUAL_CARD__)
	MMI_FILEMGRAPP_STORAGE_CARD2,
#endif
    MMI_FILEMGRAPP_STORAGE_MAX,

	MMI_FILEMGRAPP_STORAGE_NONE
}FileMgrAppStorageType_e;

typedef enum
{
    MMI_FILEMGRAPP_EMPTYFOLDER_NONE,
    MMI_FILEMGRAPP_EMPTYFOLDER_NORMAL,  // double title
    MMI_FILEMGRAPP_EMPTYFOLDER_ONETITLE,    // cpmv_browse
    MMI_FILEMGRAPP_EMPTYFOLDER_MARK,    // double title, in MultiPick
    MMI_FILEMGRAPP_EMPTYFOLDER_MAX
}FileMgrAppEmptyFolderType_e;

typedef enum
{
    MMI_FILEMGRAPP_SELTYPE_NONE,
    MMI_FILEMGRAPP_SELTYPE_AUDIO,
    MMI_FILEMGRAPP_SELTYPE_LAUNCHABLE,
    MMI_FILEMGRAPP_SELTYPE_FOLDER,
    MMI_FILEMGRAPP_SELTYPE_NONSUPPORTED
}FileMgrAppSelItemType_e;

typedef enum
{
    MMI_FILEMGRAPP_STATUS_UNMARK,
    MMI_FILEMGRAPP_STATUS_MARKED
}FileMgrAppMarkStaus_e;

typedef enum
{
	MMI_FILEMGRAPP_STORAGESEL_ITEM_PHONE	= 0x20,
	MMI_FILEMGRAPP_STORAGESEL_ITEM_CARD		= 0x40
#if defined(__DUAL_CARD__)
	,MMI_FILEMGRAPP_STORAGESEL_ITEM_CARD2	= 0x80
#endif
}FileMgrAppStorageSel_e;

typedef struct FileMgrVirtualRootOptMenuWndData_t_
{
    IWidget			                        *pIOptMenuWdg;

    u32                                     nHighlightedIndex;

    const WdgStaticMenuItem_t               *psOptMenuItemList;
    u32                                     nOptMenuItemListSize;
    PfnFileMgrOptMenuSelectCb         pfnSelectCb;
} FileMgrVirtualRootOptMenuWndData_t;

typedef struct FileMgrOptMenuWndData_t_
{
    FileMgrAppFileInfo_t                sSelectedFileInfo;
    MMI_Common_SupportedMediaType_e     nMediaType;

    IWidget                             *pIOptMenuWdg;
    boolean                             bMenuTypeStatic;

    union
    {
        const FileMgrAppOptMenuItem_t   *ptFileMgrAppOptMenuItemList;
        const WdgStaticMenuItem_t       *ptStaticOptMenuItemList;
    }uMnuItemList;
    u32                                 nOptMenuItemListSize;
    PfnFileMgrOptMenuSelectCb           pfnSelectCb;
    u32                                 nNameRemainLen;
} FileMgrOptMenuWndData_t;

typedef struct _FileMgrAppFieldSort{
    u32         *pFieldIDList;      // field id list.
    u32         nSortFiledCount;     // total sort count.
}FileMgrAppFieldSort_t;

typedef struct _FileMgrAppItemInListInfo{
    u32                             nIdx;   // the idx in array...
}FileMgrAppItemInListInfo_t;

typedef struct _FileMgrAppThumbListInfo{
    u32                             nIdx;   // the idx in array...
    VFS_PartialListFileInfo_t 	            sEfsFileInfo;
}FileMgrAppThumbListInfo_t;

#ifdef __FILEMGRAPP_ID3V2_IMG__
typedef struct _FileMgrAppID3v2ImgInfo{
    u32                         nIdx;
    MAE_WChar                   pFileURL[FILEMGR_MAX_FILEPATH_SIZE];
    IImage                      *pImgObj;
}FileMgrAppID3v2ImgInfo_t;

typedef struct _FileMgrAppID3v2ImgUserData{
    u32                         nIdx;
    MAE_WChar                   pFileURL[FILEMGR_MAX_FILEPATH_SIZE];
    MAE_WndId                   nCurWndId;
    ArrayClass_t                *pID3ImgQueue;
}FileMgrAppID3v2ImgUserData_t;
#endif

typedef struct _FileMgrAppItemInListerInfo{
    IVectorModel                    *pChildList;   // if tInfo.nType is folder, pChildList pointer to an vector, and all its element is file_id(u32)
    MMI_Common_FMList_ItemElement_t tInfo;
    u16                             nChildCount;
}FileMgrAppItemInListerInfo_t; // size 11

typedef struct _FileMgrAppFolderBrwsItem{
    FileMgrAppItemInListInfo_t    tFocusItem; // the focus item: id,type,idx (last time it left the folder)
    FileMgrAppItemInListInfo_t    tFirstItem; //the first item: id,type,idx (last time it left the folder)
}FileMgrAppFolderBrwsItem_t;

typedef struct _FileMgrAppSelListItem{
    FileMgrAppItemInListInfo_t tListInfo;
    MMI_Common_SupportedMediaType_e nContentMediaType;
}FileMgrAppSelListItem;

typedef struct _FileMgrAppMediaBrws{
    // current folder info
    MAE_WChar                       *pwszHighlightFileName;
    MMI_Common_FMList_ItemType_e    nCurrentFolderType;
    MAE_WChar                       wszCurrentFolder[FILEMGR_MAX_FILEPATH_SIZE];
    u32                             nNumOfFiles;
    FileMgrAppFLHandleID            tFLHandle;
    boolean                         bRefresh;       // to refresh menu
    boolean                         bDataSorted;    // indicate the listing data is sorted

    // history info
    boolean                         bHistoryExpired;
    ArrayClass_t                    *pFolderHistory;    // MMI_Filemgrapp_FolderBrwsItem_t

    VFS_PartialListFilter_t         *pFilter;
    u8                              tSort;
    u16                             nCountLimit;        // for multi-picker
#if defined(__FILEMGRAPP_COUNT_CAN_SEL_FILES__)
    u32                             nCanSelFiles;       // for multi-picker
    VFS_PartialListFilter_t         *pQueryFileFilter;
    FileMgrHandleID_t               nQueryFileHandleID;
#endif

    FileMgrApp_FilterType_e         nContentUsage;   // the browsing folder in one specific data type
    FileMgrApp_APMode_e             nBrowsingMode;   // denotes which display mode of the browsing data
    // next time traverse mode
    FileMgrAppTraverseMode_e        nTraverseMode;

    u8                              nFolderLevel;       // denotes for folder level
    u8                              nBaseFolderLevel;   // folder level base from. in normal case, it starts from FILEMGRAPP_LEVEL_ROOT

    u32                             nTitleLabelId;

    u32                             nOptonMeneuItemNum;
    WdgStaticMenuItem_t const       *pOptionMeneuItemList;

    FileMgrAppStorageType_e         nOnFocusStorage;
    boolean                         bNeedToRebuildModel;    // if needs to rebuild the item model or not

    MMI_Common_SupportedMediaType_e eMediaType;             //newly added

    boolean                         bSimple;                // Memory saving mode, some function are disabled.
    boolean                         bThumbnailDecode;       // Decode image thumbnail when listing

    PfnFileMgrGetL1SoftKeyCb        pfnGetL1SoftKeyCb;
    PfnFileMgrL1SoftKeySelectCb     pfnL1SoftKeySelectCb;
    PfnFileMgrSortCompareCb         pfnCompareCb;
    PfnFileMgrGetOptMenuCb          pfnGetOptionMenuCb;
    PfnFileMgrContentFilterCb       pfnContentFilterCb;

    u32                                 nVirtualVolumeListNumber;
    const FileMgrVirtualVolumeItem_t    *pVirtualVolumeList;

    u32                             nCurrHighLightCnt;
}FileMgrAppMediaBrws_t;

typedef struct _FileMgrAppMediaLstData
{
    // list (view) info
    ModelListener_t             tCntListViewMdlLstnr;
    ModelListener_t             tTabWdgMdlLstnr;

    GridItemNumInfo_t           tThumbGridItemNum;
    OPSrvRect_t                 tThumbIConRect;

    FileMgrAppFolderBrwsItem_t  tCurrentListInfo;   // current focus item (content or category)

    boolean                     bKeepCurrentFocus;

    FileMgrApp_ItemListType_e   nItemLstType;       // list in thumbnail or two-line list

    FileMgrAppStorageType_e     nOnFocusStorage;
    FileMgrAppStorageType_e     nAbsentFocusStorage;

    WidgetHandler_t             tTabWidgetHandler;

    IWidget                     *pCurrMenuWdg;		//4 newly added
    u32                         nTitleId;
}FileMgrAppMediaLstData_t;

typedef MAE_Ret(*PFN_GETITEMSK)(void                            *pUsrData,
                                SoftkeyID_e                     *pnRetLSKVal,
                                SoftkeyID_e                     *pnRetCSKVal,
                                SoftkeyID_e                     *pnRetRSKVal,
                                MMI_Common_FMList_ItemElement_t *pItemElmt,
                                MMI_Common_SupportedMediaType_e nMediaType);
typedef MAE_Ret(*PFN_PICKERGETITEMSK)(void                      *pUsrData,
                                SoftkeyID_e                     *pnRetLSKVal,
                                SoftkeyID_e                     *pnRetCSKVal,
                                SoftkeyID_e                     *pnRetRSKVal,
                                MMI_Common_FMList_ItemElement_t *pItemElmt,
                                boolean                          *pIsSelected
                                );

#if defined(__FILEMGRAPP_PERFORMANCE_PROFILING__)
extern u32 g_BatchCopyBegin;
extern u32 g_BatchCopyEnd;
extern u32 g_BatchMoveBegin;
extern u32 g_BatchMoveEnd;
extern u32 g_BatchDeleteBegin;
extern u32 g_BatchDeleteEnd;
extern u32 g_DeleteAllBegin;
extern u32 g_DeleteAllEnd;
#endif
/*==============================================================================
                       FUNCTION DECLARATIONS
==============================================================================*/

/*----------------------------------------------------------------------------
    release the memory of MediaBrws_t
----------------------------------------------------------------------------*/
void  FileMgrAppUtilReleaseMediaBrwsData(
    FileMgrAppMediaBrws_t *pMediaBrwsData,
    IBase *pOwner);

/*----------------------------------------------------------------------------
    query folder item from cagegoryDB and filter by filter_type
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------

----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------

----------------------------------------------------------------------------*/
MAE_Ret FileMgrAppUtilTraverseFolder(
    IBase                           *pOwner,
    FileMgrAppMediaBrws_t           *pBrwsData,
    FileMgrAppTraverseMode_e        nMoveTo,
    boolean                         bIsExtMemPresented,
    boolean                         bIsExtMemReadable,
    const VFS_PartialListFileInfo_t *pEfsFileInfo,
    FileMgrAppFolderBrwsItem_t      *pListInfo);

/*----------------------------------------------------------------------------

----------------------------------------------------------------------------*/
void FileMgrAppUtilReleaseMediaLstViewData(void *pData, IBase* pOwner);

/*----------------------------------------------------------------------------

----------------------------------------------------------------------------*/
MAE_Ret FileMgrAppUtilReplaceSKOfListItemAt(
    IMenuModel                          *pMenuMdl,
    u32                                 nIdx,
    SoftkeyID_e                         nLSKVal,
    SoftkeyID_e                         nCSKVal,
    SoftkeyID_e                         nRSKVal);

/*----------------------------------------------------------------------------

----------------------------------------------------------------------------*/

__SLDPM_FREE__ void FileMgrAppUtilHandleThumbnailDataDone(
    OPSrvRsltInfo_t             *pRsltInfo,
    IWidget                     *pMenu,
    ArrayClass_t                *pThumbnailQueue,
    IBase                       *pOwner);

__SLDPM_FREE__ void FileMgrAppUtilGetNextThumbnailTimer(void *pData);
__SLDPM_FREE__ MAE_Ret FileMgrAppUtilFreeThumbQueueItemByCnt(
	ArrayClass_t								*pList,
	u32											nIdx);
/*----------------------------------------------------------------------------

----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------

----------------------------------------------------------------------------*/
__SLDPM_FREE__ MAE_Ret FileMgrAppUtilGetCSKOfItem(
    SoftkeyID_e                         *pnCSKVal,
    MMI_Common_FMList_ItemType_e        nItemType,
    MMI_Common_SupportedMediaType_e     nMediaType);

/*----------------------------------------------------------------------------

----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------

----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------

----------------------------------------------------------------------------*/
MAE_Ret FileMgrAppUtilDrawIBmpFromIImg(IImage   *pImg,
                                               IBitmap  **ppBmp,
                                               IDisplay *pDsp,
                                               IBase    *pOwner);
/*----------------------------------------------------------------------------

----------------------------------------------------------------------------*/
__SLDPM_FREE__ MAE_Ret FileMgrAppUtilKeepNextThumbDecode(IBase    *pOwner, ArrayClass_t *pThumbnailQueue);

/*----------------------------------------------------------------------------

----------------------------------------------------------------------------*/
__SLDPM_FREE__ size_t FileMgrAppUtilInputGenLen(IBase *pOwner, IWidget *pInputWdg);




#if !defined(__ONBOARD_USER_STORAGE_MMI__) && defined(__CAMERA_MMI_USE_PHONE_STORAGE__)
/*----------------------------------------------------------------------------
Description Check files in the specified folder URL can be done by file system operation. (Copy/ Move/ Rename/ Delete/ Mark)
----------------------------------------------------------------------------*/
boolean FileMgrApp_Common_CheckPhoneURLAllowFSOp(const MAE_WChar *strFolderURL);
#endif

/*----------------------------------------------------------------------------

----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------

----------------------------------------------------------------------------*/


//4 -------------------- newly added for new Dialog archi. [begin] --------------------
MAE_Ret FileMgrAppUtilLoadDlg(
    FileMgrAppDlgType_e       nDlgId,
    FileMgrAppOPRslt_e        nRslt,
    FileMgrAppOpOP_e         nOPId,
    IBase                               *pOwner,
    PFN_DlgHandler	    pfnDialogHdl);


#ifdef __MMI_OMA_DRM_V1__
MAE_Ret FileMgrAppUtilLoadDrmDlg(void *pApplet, u32 nTextId);
MAE_Ret FileMgrAppUtilLoadDlgDrmConfirmDialogCb(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
void FileMgrAppLaunchCdWapDownloadDrmRightsFileCb(void *pvUserData, MAE_Ret nRspCode, void *pvRspData, CmnRspDataFreeCb pfnRspFreeCb);
MAE_Ret FileMgrAppDrmFilterRefreshMenu(
    FileMgrHandleID_t       nMarkedHandleID,
    IWidget 				*pMenuWdg,
    IWidget                 *pTitleWdg);
#endif
MAE_Ret FileMgrAppUtilLoadDlgWarningOverFileNumCB(void *pData, MAEEvent_t nEvtId, u32 param1, u32 param2);
MAE_Ret FileMgrAppUtilLoadDlgWarningOrInfoDlgCB(void *pData, MAEEvent_t nEvtId, u32 param1, u32 param2);
MAE_Ret FileMgrAppUtilLoadDlgToCloseWindowDlgCB(void *pData, MAEEvent_t nEvtId, u32 param1, u32 param2);

MAE_Ret FileMgrAppUtilLoadDlgWaitingDlgCB(void *pData, MAEEvent_t nEvtId, u32 param1, u32 param2);

MAE_Ret FileMgrAppUtilInitWndDataWithInputFileInfo(FileMgrAppFileInfo_t *pFileMgrFileInfo, FileMgrAppFileInfo_t *pInputFileInfo);

MAE_Ret FileMgrAppUtilDupMenuWndData(FileMgrOptMenuWndData_t *pDestOptMenuWndData, const FileMgrOptMenuWndData_t *pSrcOptMenuWndData);

__SLDPM_FREE__ MAE_Ret FileMgrAppUtilCloseFolderHandle(u32 *pnHandleID);
__SLDPM_FREE__ MAE_Ret FileMgrAppUtilDeMonitorHandle(u32 *pnHandleID);
MAE_Ret FileMgrAppUtilDestroyMarkHandle(u32 *pnHandleID);
MAE_Ret FileMgrAppUtilIsMarkedOfMarkList(u32 nMarkedHandleID, VFS_FileID_t nFileID);
MAE_Ret FileMgrAppUtilSingleUpdateMarkList(
    u32 					nMarkedHandleID,
    u32 					nFolderListHandleID,	//This handle should has filter only filter files
    u32 					nStartIdx,
    u32 					nMarkedCnt,
    VFS_FileID_t		nFindFileID,
    MAE_WChar 				*pwszSourceURL,
    FileMgr_MarkListType_e	eMarkType,
    IWidget 				*pMenuWdg,
    IWidget                 *pTitleWdg);
MAE_Ret FileMgrAppUtilBatchUpdateMarkList(
    u32 					nMarkedHandleID,
    u32 					nFolderListHandleID,	//This handle should has filter only filter files
    u32 					nStartIdx,
    u32 					nMarkedCnt,
    u32                     nMarkedLimit,
    MAE_WChar 				*pwszSourceURL,
    FileMgr_MarkListType_e  eMarkType,
    IWidget 				*pMenuWdg,
    u32						nHighlightIdx,
    IWidget                 *pTitleWdg,
    VFS_FileID_t            *ptFileID);

MAE_Ret FileMgrAppUtilUpdateTitleNum(
    u32 					nMarkedHandleID,
    IWidget                 *pTitleWdg);

//pnFoundIdx == -1 not found
MAE_Ret FileMgrAppUtilQueryIndexByName(
u32 nListFolderHandle,
u32 nStartIdx,
u32 nItemCnt,
u32 *pnFoundIdx,
const MAE_WChar *pwszFullFileName,
const MAE_WChar *pwszCurrentFolder
);

u32 FileMgrAppUtilCreateAndUpdateMarkList(
    MAE_WChar                           *pwszSourceURL,
    const VFS_PartialListFileInfo_t     *pFileInfo);

MAE_Ret FileMgrAppUtilUpdateMarkListAndUI(
    IWidget                             *pTitleWdg,
    IWidget                             *pMenuWdg,
    u32                                 nHighlightedIndex,
    u32                                 nMarkedHandleID,
    VFS_FileID_t                        nFileID,
    MAE_WChar                           *pwszSourceURL,
    FileMgr_MarkListType_e 	            eMarkListType);

__SLDPM_FREE__ void FileMgrAppUtilFolderMonitorURLCb(void *pUserData, void *pInfo);

__SLDPM_FREE__ void FileMgrAppUtilFolderListUpdateCb(void *pUser, void *pInfo);

__SLDPM_FREE__ void FileMgrAppUtilSortUpdateCB(void * pUser, void* pInfo);

__SLDPM_FREE__ MAE_Ret FileMgrAppUtilUpdateCpMvProgressUI(
    const u32           nErrCode,
    const u32           nProgressPos,
    const u32           nCurrFileIdx,
    u32                 *pnProcessFileNum,
    const u32           nTotalSelNum,
    IWidget             *pProgressWdg,
    FileMgrAppOpOP_e    eObjOp,
    u32                 *pnMarkedHandleID,
    FileMgrHandleID_t   *nOpHandleID,
    IBase               *pOwner);
MAE_Ret FileMgrAppUtilLoadCpMvDelFailedDlg(FileMgrAppOpOP_e eObjOp, MAE_Ret nFsErrCode, void * pApplet);
MAE_Ret FileMgrAppUtilLoadCpMvDelCancelDlg(FileMgrAppOpOP_e eObjOp, void *pApplet);
MAE_Ret FileMgrAppUtilLoadDlgCpMvDelFailedCancelDlgCB(void *pData, MAEEvent_t nEvtId, u32 param1, u32 param2);
//4 -------------------- newly added for new Dialog archi. [end] --------------------

MAE_Ret FileMgrAppUtilMenuSetHighlightedItem(
    IWidget                                 *pMenuWdg,
    FileMgrAppMediaBrws_t                   *pMediaBrwsData,
    FileMgrAppFolderBrwsItem_t   	        *pCurrentListInfo);

/*----------------------------------------------------------------------------

----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------

----------------------------------------------------------------------------*/
__SLDPM_FREE__ void FileMgrAppCommonFmtDispText(u32 nFmtTextID, u32 nTextId, MAE_WChar **ppDspTextBuf);

__SLDPM_FREE__ void FileMgrAppCommonAudioSrvStopCb(void *pApplet, MediaSrvErrCode_e eErrorCode);

//4 ======= Utilty newly added [begin] =======================
__SLDPM_FREE__ boolean FileMgrAppUtilIsFolder(u8 nAttr);
__SLDPM_FREE__ boolean FileMgrAppUtilIsDefaultFolder(MAE_WChar *pCurrentFolder, VFS_PartialListFileInfo_t *pEfsFileInfo);
#ifdef __MMI_OMA_DRM_V1__
boolean FileMgrAppFileCannotSetAs(MAE_WChar *pCurrentFolder, VFS_PartialListFileInfo_t *pEfsFileInfo);
boolean FileMgrAppFileCannotSend(MAE_WChar *pCurrentFolder, VFS_PartialListFileInfo_t *pEfsFileInfo);
MAE_Ret FileMgrAppUtilDrmFilterConfirmDialogCb(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
#endif
__SLDPM_FREE__ FileMgrAppSelItemType_e FileMgrAppUtilDetermineSelItemType(MMI_Common_SupportedMediaType_e eSupportedMediaType);
__SLDPM_FREE__ MAE_Ret FileMgrAppUtilSetMenuModelTotalSize(IWidget *pMenuWdg, u32 nTotalSize, IBase *pOwner);
//4 ======= Utilty newly added [end] =======================
__SLDPM_FREE__ void FileMgrAppCommonVolMdlListener(void * pUsrData,ModelEvent_t * pMdlEvent);

#if defined(__LIVE_WALLPAPER__)
void FileMgrAppCommonGetPredefinedFileOpRspCbData(IBase *pOwner, CmnAppLaunchFileOpRspCbInfo_t *pFileOpInfo);
void FileMgrAppCommonGetUserFileOpRspCbData(IBase *pOwner, CmnAppLaunchFileOpRspCbInfo_t *pFileOpInfo);
#endif
__SLDPM_FREE__ void FileMgrAppCommonGetFileOpRspCbData(IBase *pOwner, CmnAppLaunchFileOpRspCbInfo_t *pFileOpInfo);


/*----------------------------------------------------------------------------

----------------------------------------------------------------------------*/
static MAE_Ret FileMgrAppUtilBuildCustData(void);
/*----------------------------------------------------------------------------

----------------------------------------------------------------------------*/
static MAE_Ret FileMgrAppUtilBuildDefaultItem(void);
/*----------------------------------------------------------------------------

----------------------------------------------------------------------------*/
static MAE_Ret FileMgrAppCreateTabWdgMdl(IVectorModel* pTabWdgMdl);
/*----------------------------------------------------------------------------

----------------------------------------------------------------------------*/
static MAE_WChar* FileMgrAppUtilGenerateFolderChildCountStr(
    boolean                         bIsExtMemReadable,
    u32                             nCntSizeLimitaion,
    IBase                           *pOwner);


/*----------------------------------------------------------------------------

----------------------------------------------------------------------------*/
MAE_Ret FileMgrAppUtilLoadTypeIcon(
    MMI_Common_FMList_ItemType_e    tItemType,
    MAE_WChar                       *pFileURL,
    MAE_WChar                       *pFileExt,
    boolean                         bLargeOne,
    IImage                          **ppImg,
    IBase                           *pOwner);


/*----------------------------------------------------------------------------

----------------------------------------------------------------------------*/
MAE_Ret FileMgrAppUtilBuildListItem(
    const MAE_WChar                 *pCurrentFolder,
    const VFS_PartialListFileInfo_t *pEfsFileInfo,
    FileMgrApp_ItemListType_e       nListType,
    boolean                         bIsExtMemReadable,  // for detailed list
    u32                             nCntSizeLimitaion,  // for detailed list
    MAE_WChar                       **ppDetailedStr,    // for detailed list
    MAE_WChar                       **ppCntName,
    IImage                          **ppIconImg,
    u16                             nIndex,
    IBase                           *pOwner);

MAE_Ret FileMgrAppUtilBuildDemagedListItem(
    FileMgrApp_ItemListType_e   nListType,
    MAE_WChar                   **ppDetailedStr,    // for detailed list
    MAE_WChar                   **ppCntName,        // for name
    IImage                      **ppIconImg,        // for icon
    u16                         nIndex,
    IBase                       *pOwner);

__SLDPM_FREE__ MAE_Ret FileMgrAppUtilInitFolderHistory(FileMgrAppMediaBrws_t *pMediaBrwsData);

#ifdef __FILEMGRAPP_ID3V2_IMG__
__SLDPM_FREE__ void FileMgrAppUtilID3ArrayItemFreeFunc (void *pItemData, void *pUseData);
__SLDPM_FREE__ MAE_Ret FileMgrAppUtilCreateID3ImageQueue(IBase *pUser, ArrayClass_t **ppID3ImgQueue, u32 nItemSize, PfnArrayItemFree pfnArrayFreeFunc);
__SLDPM_FREE__ MAE_Ret FileMgrAppUtilAddID3ImageItem(IBase *pUser, ArrayClass_t *pID3ImgQueue, u32 nIndex, MAE_WChar *pCurrentFolder, MAE_WChar *pFilename);
__SLDPM_FREE__ MAE_Ret FileMgrAppUtilKeepDisplayNextID3Image(IBase *pOwner, MAE_WndId nWndId, ArrayClass_t *pID3ImgQueue);
__SLDPM_FREE__ void FileMgrAppUtilID3ImageSrcBufferFreeFunc(void *pData);
__SLDPM_FREE__ void FileMgrAppUtilGetID3InfoCb(void *pApplet, u32 nCusData, MediaSrvErrCode_e eErrorCode, AudioPlayerSrvID3InfoEx_t *pID3Info);
#endif

#endif  /* __MMI_FILEMGRAPP_UTIL_H__ */
