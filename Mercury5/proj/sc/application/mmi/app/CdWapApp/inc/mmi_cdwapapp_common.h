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
* @file    mmi_cdwapapp_common.h
* @version
* @brief   CDWAP common file
*
*/

#ifdef __WAP_MMI_CDWAP__

#ifndef __MMI_CDWAPAPP_COMMON_H__
#define __MMI_CDWAPAPP_COMMON_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_mae_common_def.h"
#include "mmi_cdwapapp_cfg.h"
#include "mmi_common_content.h"
#include "mmi_filemgrapp.h"
#include "mmi_common_storage_mgr.h"
//#include "mmi_cdwapapp_priv.h"
/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define     CDW_SPEC_FULLPATH_LEN   262

#define     CDW_MAX_NAME_LEN        64  // the maxmum for the name of bookmark or local page
#define     CDW_MAX_URL_LEN         URL_MAX_LENGTH  // max byte len for input url
#define     CDW_SPEC_FULLNAME_LEN   FILEMGR_MAX_FILEPATH_SIZE// VFS FAT max file name length, specially used in create/rename window.
#define     CDW_MAX_URL_NUM         10  // the maxmum for the record of input history
#define     CDW_TITEL_SMSTXT_LEN    5
#define     CDW_LEAST_MEMORY        10      // check limit when WAP is opened.

#define     CDW_MAX_BOOKMARK        100
#define     CDW_MAX_PAGE            50
#ifdef __MOVE_DEF_FOLDER_TO_FLASH__
#define     CDW_SYSTEM_PATH             PHONE_DIR_CDWAP_ROOT //L"fs:/PHON/.system/"
#define     CDW_ROOT_FULL_PATH          PHONE_DIR_CDWAP_EXPLORERE
#define     CDW_BM_FULL_PATH            PHONE_DIR_CDWAP_BM
#define     CDW_LP_FULL_PATH            PHONE_DIR_CDWAP_LP //L"fs:/PHON/.system/WapExplorer/History/"
#define     CDW_INPUT_FULL_PATH_NAME    PHONE_DIR_CDWAP_INPUT //L"fs:/PHON/.system/WapExplorer/Input.cdw"
#else
#define     CDW_SYSTEM_PATH             CARD_DIR_CDWAP_ROOT //L"fs:/CARD/.system/"
#define     CDW_ROOT_FULL_PATH          CARD_DIR_CDWAP_EXPLORERE//L"fs:/CARD/.system/WapExplorer/"
#define     CDW_BM_FULL_PATH            CARD_DIR_CDWAP_BM//L"fs:/CARD/.system/WapExplorer/Bookmark/"
#define     CDW_LP_FULL_PATH            CARD_DIR_CDWAP_LP//L"fs:/CARD/.system/WapExplorer/History/"
#define     CDW_INPUT_FULL_PATH_NAME    CARD_DIR_CDWAP_INPUT//L"fs:/CARD/.system/WapExplorer/Input.cdw"
#endif// __MOVE_DEF_FOLDER_TO_FLASH__

#define     CDW_LEAST_MEMORY        10      // check limit when WAP is opened.
#define     CDW_DOWNLOAD_FOLDER     CARD_DIR_CDWAP_DOWNLOAD
#define     CDW_DOWNLOAD_FOLDER2    CARD2_DIR_CDWAP_DOWNLOAD
#define     CDW_INIT_URL                L"http://"
#define     CDW_DEF_HOMEPAGE            L"http://wap.google.com/"
#ifdef __MOVE_DEF_FOLDER_TO_FLASH__
#ifdef __NAND_MMI__
#define     CDW_LOCALPAGE_URL_PREFIX    L"/NAND"
#else
#define     CDW_LOCALPAGE_URL_PREFIX    L"/NOR0"
#endif  //__NAND_MMI__
#else
#define     CDW_LOCALPAGE_URL_PREFIX    L"/CARD"
#endif

#ifdef __NAND_MMI__
#define     CDW_MUST_MEMORY         100      // necessory flash free memory used by WAP kernel
#else
#define     CDW_MUST_MEMORY         30      // necessory flash free memory used by WAP kernel
#endif  //__NAND_MMI__

#define     CDW_MARK_ALL_LIMIT_COUNT    300
/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef struct
{
    boolean bIsDir;                 // TRUE, the item is dir; FALSE, the item is file
    MAE_WChar *pItemName;               // pointer to the name of item
}CdWapFileItem_t;

typedef struct
{
    boolean bIsDir;                         // focused item whether is dir
    FocusInfo_t tFocusInfo;                     // focused item's focus info
    MAE_WChar wszItemName[CDW_SPEC_FULLPATH_LEN + 1];   // focused item's name
}CdWapHistoryRecd_t;

typedef struct                  // usd to record the focus hisoty
{
    FocusInfo_t tFocusInfo;
    void *pNext;
}CdWapFocusHistory_t;

typedef struct
{
    u16 nListNum;                       // total rul history number
    MAE_WChar *pwcUrlList[CDW_MAX_URL_NUM]; // pointer to url address
}CdWapAppUrlList_t;

typedef struct
{
    u32 nHandle;        // start list handle
    u32 nNumber;            // total file number in folder
}CdWapAppListInfo_t;

typedef enum
{
    CDWAP_DLG_NORMAL = 0,               // normal style
    CDWAP_DLG_NO_EXT_MEM,               // external memory card isn't exist
    CDWAP_DLG_BEYOND_MAX_PATH_LEN,      // the length is beyond the maxmum
    CDWAP_DLG_WRONG_OPERAION,           // wrong operation
    CDWAP_DLG_NULL_CONTENT,             // input content is null
    CDWAP_DLG_NULL_HOMEPAGE,            // homepage is null
    CDWAP_DLG_DEL_FOLDER,               // delete a folder
    CDWAP_DLG_DEL_FILE,                 // delete a file
    CDWAP_DLG_DEL_MARK_ITEM,            // delete marked item
    CDWAP_DLG_FS_FULL,                  // delete marked item
    CDWAP_DLG_FILE_EXIST,               // delete marked item
    CDWAP_DLG_CLEAR_INPUT_URL,          // delete selected input url
    CDWAP_DLG_CLEAR_ALL_INPUT_URL,      // delete all input url
    CDWAP_DLG_CLEAN_CACHE,              // clean cache
    CDWAP_DLG_CLEAN_SUCCESS,            // the result of clean
    CDWAP_DLG_CLEAN_FAIL,               // the result of clean
    CDWAP_DLG_COVER_HOMEPAGE,           // cover the origin homepage in configration
    CDWAP_DLG_SAVE_SUCCESS,             // success save bookmark
    CDWAP_DLG_SIM_INACTIVE,             // SIM is inactive
    CDWAP_DLG_DOWNLOADING,              // Saving file
    CDWAP_DLG_HAVE_DOWNLOAD,            // File has been saved
    CDWAP_DLG_SAVE_UNSUCCESS,           // Can not save
    CDWAP_DLG_EXIT_APP,                 // exit cdwap app
    CDWAP_DLG_INIT,                     // init cdwap app
    CDWAP_DLG_NO_SIM,                   // sim not insert
    CDWAP_DLG_SIM_UNKNOW,               // Not receive SIM indication yet
    CDWAP_DLG_CDWAP_LIB_ERROR,          // error notic from cdwap
    CDWAP_DLG_INIT_ERROR,               // init fail
    CDWAP_DLG_STOP_MMS,                 // stop mms yes/no
    CDWAP_DLG_NETWORK_ERROR,            // didn't stop mms transition, wap connect error
    CDWAP_DLG_FILETOOLARGE,             // file too large,can not download
    CDWAP_DLG_AIRPLANEMODE,             // not allowe use network
    CDWAP_DLG_DNLD_FAIL,                // file download fail
    CDWAP_DLG_SYS_NOT_READY,            // system isn't ready
    CDWAP_DLG_MOVE_SUCCESS,             // move file success
    CDWAP_DLG_MOVE_FAIL,                // move file failed
    CDWAP_DLG_CANNOT_MOVE,              // source path and destination path is the same
    CDWAP_DLG_FS_ERROR, // no used          // file system error
    CDWAP_DLG_STOP_BT,                  // mms service is stopping
    CDWAP_DLG_TCARD_FULL,               // space not enough,can not download
    CDWAP_DLG_FILE_UNSUPPORTED,         // file unsupported
    CDWAP_DLG_ILLEGAL_CHAR,             // input file name include some illegal char
    CDWAP_DLG_INVALID_CHAR,             // input file name include some invalid char
    CDWAP_DLG_DB_NOT_READY, // no used      // file db isn't ready
    CDWAP_DLG_MEMORY_INSUFFICIENT,      // memory is insufficient
    CDWAP_DLG_NO_MEMORY,                   // can't save bookmark or local page when FS is full
    CDWAP_DLG_BOOK_LIMIT,                     // beyond the max number of bookmark
    CDWAP_DLG_LOCAL_LIMIT,                    // beyond the max number of localpage
    CDWAP_DLG_BRPWSER_MEM_ERROR,        // browser memeory error
    CDWAP_DLG_USB_MSC,
    CDWAP_DLG_USB_VDC,
    CDWAP_DLG_USB_CDC_MODEM,
    CDWAP_DLG_JAVA_RUNNING,
    CDWAP_DLG_DELETE_SUCCESS,
    CDWAP_DLG_DELETE_FAIL,
    CDWAP_DLG_LAUNCH_JAVA,              // Quit WAP and launch Java to install jar
#ifdef __STREAMING_MODULE__
	CDWAP_DLG_LAUNCH_VIDEO_PLAYER_RTSP,	// Suspend WAP and launch Video player for RTSP streaming video
	CDWAP_DLG_LAUNCH_VIDEO_PLAYER_HTTP, // Suspend WAP and launch Video player for HTTP streaming video
#else
    CDWAP_DLG_NOT_SUPPORT_STREAMING,    // Not support streaming
#endif
    CDWAP_DLG_LINK_INVALID,			// Link content is empty or invalid
    CDWAP_DLG_REFRESH_ERROR,			// Refresh Error
	CDWAP_DLG_MARK_TOO_MANY_FILES,		// Mark over number of files error.
	CDWAP_DLG_BAD_PARAM,
	CDWAP_DLG_FAILED,
	CDWAP_DLG_OUT_OF_MEMORY,
#ifdef __MMI_OMA_DRM_V1__
	// DRM related part
	CDWAP_DLG_DRM_AGENT_PROCESSING,		// DRM agent is processing
	CDWAP_DLG_DRM_RIGHTS_INSTALL_SUCCESS,
	CDWAP_DLG_DRM_FILE_ERROR,
	CDWAP_DLG_DRM_RIGHTS_INSTALL_ERROR,
	CDWAP_DLG_DRM_RIGHTS_FULL,
	CDWAP_DLG_DRM_VIDEO_HAVE_DOWNLOAD,
	CDWAP_DLG_DRM_MUSIC_HAVE_DOWNLOAD,
	CDWAP_DLG_DRM_PICTURE_HAVE_DOWNLOAD,
	// DD related part
    CDWAP_DLG_OMA_INSUFFICIENT_MEMORY,
    CDWAP_DLG_OMA_LOSS_OF_SERVICE,
    CDWAP_DLG_OMA_ATRR_MISMATCH,
    CDWAP_DLG_OMA_INVALID_DD,
    CDWAP_DLG_OMA_INVALID_DD_VERSION,
    CDWAP_DLG_OMA_NON_ACCEPTABLE_CONTENT,
    CDWAP_DLG_OMA_LOADER_ERROR,
#endif
	CDWAP_DLG_OP_NOT_SUPPORTED,
	CDWAP_DLG_GET_RECORD,				// Now it's getting recent page records
	CDWAP_DLG_REOPEN_LAST_PAGE,				// ask user if re-open last page when back from WAP suspend.
#ifdef __BLUETOOTH_OBEX_MMI__	
    CDWAP_DLG_STOP_BY_BTOPP,            // WAP exit because of BT OPP is transferring
#endif    
}CdWapAppDlgType_e;

typedef enum
{
    // prevent to cover MAE return code
    CDWAP_RET_NO_MEMORY = 0x1000,         // can't save bookmark or local page when FS is full
    CDWAP_RET_BOOK_LIMIT,                     // beyond the max number of bookmark
    CDWAP_RET_LOCAL_LIMIT,                    // beyond the max number of localpage
    CDWAP_RET_ILLEGAL_CHAR,
    CDWAP_RET_INVALID_CHAR,
    CDWAP_RET_NO_EXT_MEM,
    CDWAP_RET_FILE_UNSUPPORTED,
    CDWAP_RET_NULL_CONTENT,
    CDWAP_RET_MAX_PATH_LEN

} CdWapMaeRetCode_e;

typedef enum
{
    CDWAP_OPT_NORMAL = 0,               // normal style
    CDWAP_OPT_BOOKMARK,                 // option menu for bookmark menu
    CDWAP_OPT_LOCALPAGE,                // option menu for local page menu
    CDWAP_OPT_BOOKMARK_L2,              // option menu for bookmark menu level2
    CDWAP_OPT_LOCALPAGE_L2,             // option menu for local page menu level2
    CDWAP_OPT_BOOKMARK_L2_NULL,         // option menu for bookmark menu level2 when item is null
    CDWAP_OPT_LOCALPAGE_L2_NULL,        // option menu for local page menu level2 when item is null
    CDWAP_OPT_EXPLORER,                 // option menu for explorer when focusing on an image
    CDWAP_OPT_EXPLORER_NO_IMAGE,        // option menu for explorer when not focusing on an image
    CDWAP_OPT_EXPLORER_L2,              // option menu for explorer level2
    CDWAP_OPT_EDIT,                     // option menu for editor
    CDWAP_OPT_MARK,                     // Option menu for mark
}CdWapAppOptionType_e;

typedef enum
{
    CDWAP_VT_INITIAL = 0,
    CDWAP_VT_TAB_VIEW,
    CDWAP_VT_FILE_LIST,
    CDWAP_VT_GET_PATH,      // CDWAP_WND_MOVE_FILES
    CDWAP_VT_MOVE_FILE,     // CDWAP_WND_MOVE_FILES
    CDWAP_VT_BOOKMARK,      // CDWAP_WND_MOVE_FILES
    CDWAP_VT_RECORD,
    CDWAP_VT_SETTING,
    CDWAP_VT_EXPLOR_PAGE,
    CDWAP_VT_WAIT_DATALINK,
    CDWAP_VT_DATALINKED,
    CDWAP_VT_UNINIT,
    CDWAP_VT_BT_MMS,
    CDWAP_VT_VIEW_OMA_DD,
    CDWAP_VT_VIEW_NONE
}CdWapAppViewType_e;

typedef enum
{
    CDWAP_ID_NONE = 0,
    CDWAP_ID_APP_EXIT,
    CDWAP_ID_HAVE_DOWNLOAD,
    CDWAP_ID_DELETE_FOLDER,
    CDWAP_ID_DELETE_BOOKMARK,
    CDWAP_ID_MARK_DELETE,
    CDWAP_ID_MARK_ALL,
    CDWAP_ID_SET_HOMEPAGE,
    CDWAP_ID_LAUNCH_JAVA,
#ifdef __STREAMING_MODULE__
	CDWAP_ID_LAUNCH_VIDEO_PLAYER_RTSP,
	CDWAP_ID_LAUNCH_VIDEO_PLAYER_HTTP,
#endif
    CDWAP_ID_CLEAN,
    CDWAP_ID_STOP_MMS,
    CDWAP_ID_STOP_BT,
    CDWAP_ID_DOWNLOADING,
	CDWAP_ID_DRM_PROCESSING,
	CDWAP_ID_REOPEN_LAST_PAGE,
#ifdef __BLUETOOTH_OBEX_MMI__	
    CDWAP_ID_STOP_BY_BTOPP,
#endif
} CdWapMenuItemID_e;

/*=============================================================*/
// Variable definition & declaration
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

/*
**  malloc memory and copy content
*/
void CdWapCommonMemCopy(MAE_WChar **ppwPath,const MAE_WChar *pwSource);
/*
**  check the defautl folder whether exist, if not, create it
*/
MAE_Ret CdWapCommonCheckDir(void *pData);
/**
*   start list file
*/
MAE_Ret CdWapCommonStartFileList(void *pData, CdWapAppListInfo_t *pList,const MAE_WChar *pPath);
/**
*   end list file
*/
MAE_Ret CdWapCommonEndFileList(void *pData, CdWapAppListInfo_t *pList);
/*
*   get the number of files (including folders) in a folder
*   store into the FileList (CdWapAppListInfo_t.nNumber)
*/
MAE_Ret CdWapCommonGetFileNum(void *pData, CdWapAppListInfo_t *pList,const MAE_WChar *pPath);
/**
*   get fileinfo by index
*/
void CdWapCommonGetFileInfoById(void *pData, u32 nHandle, u32 FileId, VFS_PartialListFileInfo_t *pInfo);
/**
*   change directoyr by selecled folder
*/
MAE_Ret CdWapCommonUpdatePath(void *pData, MAE_WChar *pName, MAE_WChar **ppPath, boolean bEnter);
/**
*   add focusinfo item to list
*   used to record the focus info in each folder level that have entered
*/
void CdWapCommonAddHistoryLevel(CdWapFocusHistory_t **ppHistory, FocusInfo_t *pFocusInfo);
/**
*   delete focusinfo item from list
*   RetLvl : return level
*/
void CdWapCommonDelHistoryLevel(CdWapFocusHistory_t **ppHistory, FocusInfo_t *pFocusInfo, u32 RetLvl);

/*
**  get input history from default file
*/
MAE_Ret CdWapCommonSaveInputHistory(void *pData);

/*
**  get input history from default file
*/
MAE_Ret CdWapCommonGetInputHistory(void *pData);

/*
**  write URL to input history file
*/
MAE_Ret CdWapCommonAddUrlToHistory(void *pData, MAE_WChar *pwstrUrl);
/*
**  edit folder name
*   bRename : TRUE, rename a folder; FALSE, create a new folder
*/
MAE_Ret CdWapCommonEditFolderName(void *pData, boolean bRename);
/*
**  delete a file or folder
*   pName : the item's name that will be deleted
*   pPath : the item's path
*   bIsDir : TRUE, the item is a file; FALSE the item is a folder
*/
MAE_Ret CdWapCommonDelItem(void *pData, boolean bIsDir, MAE_WChar *pPath, MAE_WChar *pName);
/*
**  save loacal page
*/
MAE_Ret CdWapCommonSaveLocalpage(void *pData, u8 **ppPath, size_t* pByteLen);
/*
**  edit bookmark
*   pwName : the name of bookmark
*   pwUrl : the url of the bookmark
*/
MAE_Ret CdWapCommonSaveBookmark(void *pData, MAE_WChar *pwName,const MAE_WChar *pwPath, MAE_WChar *pwUrl, boolean bEdit);
/*
**  get url from selected bookmark
*   pwName : the name of bookmark
*   pwUrl : the url of the bookmark
*/
MAE_Ret CdWapCommonGetUrlFromBookmark(void *pData, MAE_WChar *pwPath, MAE_WChar *pwName, MAE_WChar **ppwUrl);
/*
**  get homepage from configuration
*/
MAE_Ret CdWapCommonGetHomepage(void *pData, MAE_WChar *pwHomepage);
/*
**  get homepage from configuration
*/
MAE_Ret CdWapCommonSetHomepage(void *pData, MAE_WChar *pwHomepage);
/*
**  move file
*   pwSource : the source path
*   pwDest : the destination path
*/
MAE_Ret CdWapCommonMoveFile(void *pData, MAE_WChar *pwDest, MAE_WChar *pwSource);

/*
**  convert return code to dialog type
*/
u32 CdWapCommonConvertErrorDlgType(MAE_Ret nRetVal);

/*
**  display a error notice dialog by error code
*/
boolean CdWapCommonErrorNotice(IApplet *pApplet, u32 ErrorID);

/**
Free Data for call file Mgr
*/
void CdWapCommonFreeFileMgrStartData(IBase *pOwner, u32 FileMgrReqData);

/**
add file_id to Content DB
*/
MAE_Ret CdWapCommonDelData(void *pThisData, MAE_WChar *pfilename);

/**
Launch FileManger App
*/
MAE_Ret CdWapCommonLaunchFileMangerApp(void *pData, FileMgrApp_FilterType_e nFilterType);

/**
is Picture in localpage
*/
boolean CdWapCommonCheckURLFormat( const MAE_WChar*pUrlstr,void *pData);

/**
check input file name
*/
MAE_Ret CdWapCommonCheckInputFileName(MAE_WChar **ppwName, boolean bHaveExtName);

MAE_Ret CdWapCommonRenameFile(void *pData, MAE_WChar *pwFullName, MAE_WChar *pwCurName, MAE_WChar *pwExt);

MAE_WChar* CdWapCommonGetDownloadFolder(void *pData);

void CdWapCommonSaveDefaultStorageType(void);

void CdWapCommonRestoreDefaultStorageType(void);

/**
*  mae_wstrtrim: remove space in head and tail of src string, remove dot in tail of src string.
*/
MAE_WChar *CdWapCommonTrimFileName(MAE_WChar *pDest, MAE_WChar *pSrc);

/**
Support WTAI URL functions
*/
void CdWapCommonWtaiUrl(void *pData, u32 nEvtType, u32 pEvtBody);

/**
Launch CC App to make call
*/
void CdWapCommonLaunchCC(void *pData, u8 * pDialStr);

/**
Launch Phonebook App to add entry
*/
void CdWapCommonLaunchPhb(void *pData, u8 * pNumStr, u8 * pNameStr);



#endif // #define __MMI_CDWAPAPP_COMMON_H__
#endif // __WAP_MMI_CDWAP__
