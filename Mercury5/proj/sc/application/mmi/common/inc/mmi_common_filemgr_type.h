#ifndef __MMI_COMMON_FILEMGR_TYPE_H__
#define __MMI_COMMON_FILEMGR_TYPE_H__

#include "mmi_mae_common_def.h"
#include "mmi_common_storage_mgr.h" //FileMgrVirtualVolumeItem_t etc.
#include "mmi_launcher_common.h" //for CmnLaunchAppRspCb etc.
#include "mdl_vfs_struct.h" //for VFS_FileID_t;
#include "srv_filemgr_data_types.h"
#include "mmi_wdg_itf_staticmenu.h" //for WdgStaticMenuItem_t
/*
 * FileMgrApp's data type/definition that other library, such as AppLauncher and srv
 * */

/// Common struct for other apps

typedef enum
{
    FILE_OP_REFRESH = 0X01,
    FILE_OP_ONFOCUS = 0x02,
    FILE_OP_SELECT = 0X04,
}File_Op_e;

typedef struct
{
    File_Op_e nOptype;
    VFS_FileID_t sFileId;
    MAE_WChar wszOnFocusFile[FILEMGR_MAX_FILEPATH_SIZE];
    boolean bIsDeleted;
}FileOpInfo_t;

typedef void (*CmnLaunchAppFileOpRspFreeCb)(FileOpInfo_t *psRspData);
typedef void (*CmnLaunchAppFileOpRspCb)(void *pvUserData, MAE_Ret nRspCode, FileOpInfo_t *psRspData, CmnLaunchAppFileOpRspFreeCb pfnRspFreeCb);

typedef struct
{
    void *pvUserData;
    CmnLaunchAppRspCb pfnLaunchListenerCb;
    CmnLaunchAppFileOpRspCb pfnDataRspCb;
}CmnAppLaunchFileOpRspCbInfo_t;

/// Interface to browsing files
typedef enum
{
	FILEMGR_LAUNCH_MODE_LIST_MIN = 0,
    FILEMGR_LAUNCH_MODE_FULL_BROWSING = FILEMGR_LAUNCH_MODE_LIST_MIN,
	FILEMGR_LAUNCH_MODE_LIST_DIR,
	FILEMGR_LAUNCH_MODE_MAX = FILEMGR_LAUNCH_MODE_LIST_DIR,
	FILEMGR_LAUNCH_MODE_INVALID,
}FileMgrLaunchMode_e;

typedef struct _FileMgrAppFileInfo
{
    MAE_WChar *pCurrentFolder;
	VFS_PartialListFileInfo_t *pEfsFileInfo;
}FileManagerFileInfo_t;

typedef enum
{
    ONSTATUSCHANGE_DELETE = 0,
    ONSTATUSCHANGE_RENAME,
    ONSTATUSCHANGE_FOCUSCHANED,
    ONSTATUSCHANGE_SELECTED,
    ONSTATUSCHANGE_NUM
}FileManagerOnStatus_e;

typedef s32 (*PfnFileMgrSortCompareCb)(void *data1, void *data2);
//typedef s32 (*PfnFileManagerMenuSelectRepb)(void *FileMgrUserData, boolean nClose, boolean bRefresh, void *pFocusFileInfo);
typedef void (*PfnFileMgrSelectCb)(FileManagerFileInfo_t *sFileInfo, CmnAppLaunchFileOpRspCbInfo_t *psRspCbInfo);

typedef void (*PfnFileMgrL1SoftKeySelectCb)(void *pUserData, u32 nEvtCode, boolean *pbCloseApp, boolean *pbHandled, CmnAppLaunchFileOpRspCbInfo_t *psRspCbInfo);
typedef void (*PfnFileMgrGetL1SoftKeyCb)(void *pUserData, u32 nFileNumber, u32 *pnLSKVal, u32 *pnCSKVal, u32 *pnRSKVal, PfnFileMgrL1SoftKeySelectCb *pfnLiselectCb);

typedef void (*PfnFileMgrGetSortCompareCb)(void *pUserData, PfnFileMgrSortCompareCb *pfnConpareFunction);
typedef void (*PfnFileMgrGetFilterCb)(void *pUserData, VFS_PartialListFilter_t **tFilter);
typedef void (*PfnFileMgrOptMenuSelectCb)(void *pUserData, u32 nMenuId, FileManagerFileInfo_t *sFileInfo, boolean *pbCloseApp, boolean *pbHandled, CmnAppLaunchFileOpRspCbInfo_t *psRspCbInfo);
typedef void (*PfnFileMgrGetOptMenuCb)(void *pUserData, u32 nFolderLevel, void *pFileInfo, u32 *pOptonMeneuItemNum, const WdgStaticMenuItem_t **pOptionMeneuItemList, PfnFileMgrOptMenuSelectCb *pfnSelectCb);
typedef void (*PfnFileMgrGetVirtualVolumeListCb)(void *pUserData, u32 *pNumber, const FileMgrVirtualVolumeItem_t **pVirtualVolumeList);

typedef void (*PfnFileMgrContentFilterCb)(FileManagerFileInfo_t *sFileInfo, boolean *pbReject, u32 *pnWarningMsgTextId);

typedef struct
{
    u32                                     nTitleTextId;               // title text
    MAE_WChar                               wStrDirPath[FILEMGR_MAX_FILEPATH_SIZE];   // beginning folder, ignore it if GetVirtualViolumeCb is set.
    void                                    *pUserData;
    boolean                                 bSimple;                    // Memory saving mode, some function are disabled.
    boolean                                 bThumbnailMode;             // Menu syle: Grid mode
    boolean                                 bThumbnailDecode;           // Decode image thumbnail when listing
    PfnFileMgrGetL1SoftKeyCb            pfnGetL1SoftkeyCb;

    PfnFileMgrGetSortCompareCb  pfnCompareCb;
    PfnFileMgrGetFilterCb               pfnGetFilterCb;
    PfnFileMgrGetOptMenuCb           pfnGetOptionMenuCb;
    PfnFileMgrGetVirtualVolumeListCb    pfnGetVirtualVolumeListCb;
}FileManagerListDir_t;

typedef struct
{
	union
	{
        FileManagerListDir_t sListDir;  /// FILE_MANAGER_LAUNCH_MODE_SIMPLE_LIST
	}LaunchData_t;
}FileManagerLaunchData_t;

/// data types to get predefined file
typedef enum
{
    GET_PREDEFINED_FILE_MODE_IMAGE = 0,
    GET_PREDEFINED_FILE_MODE_MELODY,
    GET_PREDEFINED_FILE_MODE_NUM,
    GET_PREDEFINED_FILE_MODE_INVALID,
}AppGetPredefinedFileMode_e;
typedef struct
{
    AppGetPredefinedFileMode_e      eMode;
	u32                                     nTitleTextId;               // title text
}AppGetPredefinedFileInputData_t;

typedef struct
{
    MAE_WChar                       *pwszUrl; // the data is read only
}AppGetPredefinedFileRspData_t;

typedef void (*AppGetPredefinedFileByBrowseRspDataFreeCb)(AppGetPredefinedFileRspData_t *psRspData);
typedef void (*AppGetPredefinedFileByBrowseCb)(void *pvUserData, MAE_Ret nRspCode, AppGetPredefinedFileRspData_t *psRspData);
typedef struct
{
    void *pvUserData;
    CmnLaunchAppRspCb pfnLaunchListenerCb;
    AppGetPredefinedFileByBrowseCb pfnRspCb;
}AppGetPredefinedFileRspCbInfo_t;

/// Data types to get files
typedef enum
{
    GET_FILE_MODE_SINGLE = 0,
    GET_FILE_MODE_MULTI,
	GET_FILE_MODE_NUM,
	GET_FILE_MODE_INVALID,
}AppGetFileMode_e;

typedef struct
{
    AppGetFileMode_e                        eMode;
    u32                                     nTitleTextId;               // title text
    MAE_WChar                               wStrDirPath[FILEMGR_MAX_FILEPATH_SIZE];   // beginning folder. If pfnGetVirtualVolumeListCb is set, this parameter will be ignored.

    u32                                     nCountLimit;                // for GET_FILE_MODE_MULTI only

    // callback to get compare callback for sorting. (Optional)
    PfnFileMgrGetSortCompareCb  pfnCompareCb;
    // callback to get filter.
    PfnFileMgrGetFilterCb               pfnGetFilterCb;
    // callback to get optionmenu item list, it should be static menu.
    PfnFileMgrGetOptMenuCb           pfnGetOptionMenuCb;
    // callback to get virtual volume list. (Optional)
    PfnFileMgrGetVirtualVolumeListCb    pfnGetVirtualVolumeListCb;

    PfnFileMgrContentFilterCb           pfnContentFilterCb; // for GET_FILE_MODE_SINGLE only

#if defined(__LIVE_WALLPAPER__)
    boolean                                 bGetWallpaper;
#endif
}AppGetFileInputData_t;

typedef struct
{
    u32                             nSrvFileMgrMarkListHandle; // Mark list, refer to mmi_srv_filemgr.h
    u32                             nSize;
}AppGetFileRspData_t;

typedef void (*AppGetFileByBrowseRspDataFreeCb)(AppGetFileRspData_t *psRspData);
typedef void (*AppGetFileByBrowseCb)(void *pvUserData, MAE_Ret nRspCode, AppGetFileRspData_t *psRspData, AppGetFileByBrowseRspDataFreeCb pfnRspDataFreeCb);
typedef struct
{
	void *pvUserData;
    CmnLaunchAppRspCb pfnLaunchListenerCb;
    AppGetFileByBrowseCb pfnRspCb;
}AppGetFileRspCbInfo_t;

// Data types to show storage information
typedef enum
{
    SHOW_MEM_MODE_PHONE = 0,
    SHOW_MEM_MODE_CARD,
    SHOW_MEM_MODE_CARD2,
    SHOW_MEM_MODE_ALL
}AppShowMemMode_e;

// Data types to get dir
typedef enum
{
    GET_DIR_MODE_SINGLE = 0,
}AppGetDirMode_e;

typedef struct
{
    AppGetDirMode_e                     eMode;
    u32                                 nTitleTextId; // title text

    PfnFileMgrContentFilterCb           pfnContentFilterCb;
}AppGetDirInputData_t;


typedef struct
{
    MAE_WChar           *pwszDir;
}AppGetDirRspData_t;

typedef void (*AppGetDirByBrowseRspDataFreeCb)(AppGetDirRspData_t *psRspData);
typedef void (*AppGetDirByBrowseCb)(void *pvUserData, MAE_Ret nRspCode, AppGetDirRspData_t *psRspData, AppGetDirByBrowseRspDataFreeCb pfnRspDataFreeCb);
typedef struct
{
	void *pvUserData;
    CmnLaunchAppRspCb pfnLaunchListenerCb;
    AppGetDirByBrowseCb pfnRspCb;
}AppGetDirRspCbInfo_t;

//Data types for FileMgrApp

enum _FileMgrApp_APMode{
	FILEMGRAPP_MODE_NONE,
	FILEMGRAPP_MODE_FULLBROWSING,
	FILEMGRAPP_MODE_MARK,
	FILEMGRAPP_MODE_CPMV,
	FILEMGRAPP_MODE_EMBEDDEDMEMINFO,
    FILEMGRAPP_MODE_SINGLEPICK,
    FILEMGRAPP_MODE_SINGLEPICK_DIR,
	FILEMGRAPP_MODE_MULTIPICK,
	FILEMGRAPP_MODE_LISTDIR,
	FILEMGRAPP_MODE_BROWSE_PREDEFINEDDATA,
	FILEMGRAPP_MODE_NUM
};
typedef u8 FileMgrApp_APMode_e;

	//file types, used in FileLister

enum _FileMgrApp_FilterType{
    FILEMGRAPP_NOTSPECIFIC,                // For All Files

    FILEMGRAPP_SOUND_FILE,                 // For Sound Files
	FILEMGRAPP_SOUND_FOR_M3U,				// For Music Player
    FILEMGRAPP_MMSSOUND_FILE,              // For MMS Sound Files

    FILEMGRAPP_PICTURE_FILE,               // For Picture Files
	FILEMGRAPP_MMSPICTURE_FILE,            // For MMS Picture Files

    FILEMGRAPP_VIDEO_FILE,                 // For Video Files
#ifdef __MMS_SUPPORT_PLAY_VIDEO__
    FILEMGRAPP_MMSVIDEO_FILE,              // For MMS Video Files
#endif
#if defined(__LIVE_WALLPAPER__)
    FILEMGRAPP_WALLPAPERS_FILE,            // For Wallpapers setting
#endif
	FILEMGRAPP_PREDEFINEDIMAGE_FILE,		// For picking the predefined image files
	FILEMGRAPP_PREDEFINEDRINGTONES_FILE,	// For picking the predefined ringtone files

#ifdef  __FEATURE_THEME_SUPPORTED__
    FILEMGRAPP_THEMES_FILE,                // For Settings App (Themes)
#endif  // FEATURE_THEME_SUPPORTED

	FILEMGRAPP_PHONEBOOK_FILE,				// For Phonebook supported files
	FILEMGRAPP_VOICEMEMO_FILE,
    FILEMGRAPP_MAX_TYPE = 0xFF
};
typedef u8 FileMgrApp_FilterType_e;

enum _FileMgrApp_OptionMenuItemType
{
    FILEMGR_ML_OPT_IMPORT,
    FILEMGR_ML_OPT_OPEN,
    FILEMGR_ML_OPT_INSTALL,
    FILEMGR_ML_OPT_PLAY,
    FILEMGR_ML_OPT_VIEW,
    FILEMGR_ML_OPT_SET_AS,
    FILEMGR_ML_OPT_SEND,
    FILEMGR_ML_OPT_RENAME,
    FILEMGR_ML_OPT_DELETE,
    FILEMGR_ML_OPT_COPY,
    FILEMGR_ML_OPT_MOVE,
    FILEMGR_ML_OPT_MARK,
    FILEMGR_ML_OPT_CREATE_FOLDER,
    FILEMGR_ML_OPT_SLIDESHOW,
    FILEMGR_ML_OPT_SEARCH,
    FILEMGR_ML_OPT_SETTINGS,
    FILEMGR_ML_OPT_MEM_DETAILS,
    FILEMGR_ML_OPT_VIEW_DETAILS,

    FILEMGR_SET_AS_OPT_WALLPAPER,
    FILEMGR_SET_AS_OPT_INCOMING_CALL,
    FILEMGR_SET_AS_OPT_CONTACT,
    FILEMGR_SET_AS_OPT_POWER_ON,
    FILEMGR_SET_AS_OPT_POWER_OFF,
    FILEMGR_SET_AS_OPT_ALARM,

    FILEMGR_SETTINGS_OPT_THUMBNAILS,
    FILEMGR_SETTINGS_OPT_LIST_MODE,
    FILEMGR_SETTINGS_OPT_SORT_BY,
    FILEMGR_SETTINGS_OPT_MEMORY_STATUS,

    FILEMGR_MARK_OPTION,
    FILEMGR_MARK_OPT_OPEN,
    FILEMGR_MARK_OPT_MARK,
    FILEMGR_MARK_OPT_UNMARK,
    FILEMGR_MARK_OPT_ADD,
    FILEMGR_MARK_OPT_IMPORT,
    FILEMGR_MARK_OPT_MARK_ALL,
    FILEMGR_MARK_OPT_UNMARK_ALL,
    FILEMGR_MARK_OPT_RENAME,
    FILEMGR_MARK_OPT_DELETE,
    FILEMGR_MARK_OPT_COPY,
    FILEMGR_MARK_OPT_MOVE,
    FILEMGR_MARK_OPT_SEND,

    FILEMGR_MARK_L2_OPTION,
    FILEMGR_MARK_L2_OPT_MARK,
    FILEMGR_MARK_L2_OPT_MARK_ALL,

    FILEMGR_OPT_ITME_NUM,

    FILEMGR_CUS_ITEM_LAUNCHTYPE   = FILEMGR_OPT_ITME_NUM + 1,
    FILEMGR_CUS_ITEM_EXECUTETYPE   = FILEMGR_OPT_ITME_NUM + 2,
};
typedef u8 FileMgrAppOptMenuItemType_e;

typedef enum
{
    FILEMGRAPP_MEMSTATUS_VIEW_PHONE,
    FILEMGRAPP_MEMSTATUS_VIEW_CARD,
    FILEMGRAPP_MEMSTATUS_VIEW_CARD2,
    FILEMGRAPP_MEMSTATUS_VIEW_ALL
} FileMgrAppMemStatusViewMode_e;

typedef struct _FileMgrAppFLHandleID
{
	FileMgrHandleID_t nCurrListFolderHandleID;
	FileMgrHandleID_t nCurrMarkedHandleID;
    FileMgrHandleID_t       nDetectFolderHandleID;
    FileMgrHandleID_t nMonitorHandle;
}FileMgrAppFLHandleID;

typedef struct FileMgrAppFileInfo_t_
{
    MAE_WChar                   *pCurrentFolder;
	VFS_PartialListFileInfo_t 	*pEfsFileInfo;
}FileMgrAppFileInfo_t;

typedef struct FileMgrExecuteApp_t_
{
    FileMgrAppFileInfo_t   *pExtcuteItemInf;
}FileMgrExecuteApp_t;

typedef void (*PfnFileDecodeThumbnailDoneCb)(void *pCusData, IImage *pThumbImg);

typedef void (*PfnFileMgrTitleUpdateCb)(void *pUserData, FileMgrAppFileInfo_t *pFocusItemInf, MAE_WChar **ppTitleText);
typedef void (*PfnFileMgrTitle2UpdateCb)(void *pUserData, FileMgrAppFileInfo_t *pFocusItemInf, MAE_WChar **ppTitle2Text);
typedef void (*PfnFileMgrItemUpdateCb)(void *pUserData, FileMgrAppFileInfo_t *pItemInf, MenuModelData_t **pMenuItem);
typedef void (*PfnFileMgrInfoBarUpdateCb)(void *pUserData, FileMgrAppFileInfo_t *pFocusItemInf, MAE_WChar **ppInfoBatText);
typedef void (*PfnFileMgrFocusChangeCb)(void *pUserData, FileMgrAppFileInfo_t *pItemInf);
typedef void (*PfnFileDecodeThumbnailCb)(void *pUserData, FileMgrAppFileInfo_t *pItemInf, void *pFileMgrUserData, PfnFileDecodeThumbnailDoneCb pfnRefshCb);
typedef void (*PfnFileMgrGetBgColorCb)(void *pUserData, FileMgrAppFileInfo_t *pFocusItemInf, u32 *pColor);
typedef void (*PfnFileMgrGetBgImgCb)(void *pUserData, FileMgrAppFileInfo_t *pFocusItemInf, u32 *nImgId);
typedef void (*PfnFileMgrOptMenuItemFilterCb)(void *pUserData, FileMgrAppFileInfo_t *pFocusItemInf, boolean *pShow);
typedef void (*PfnFileMgrPreloadItemUpdateCb)(void *pUserData, u32 nIndex, MenuModelData_t **pMenuItem);

typedef struct _FileMgrListerData
{
    //TODO: to be remove
    FileMgrApp_FilterType_e            nCntFilterType;
    u32                                     nTitleTextId;               // title text

    // beginning folder
    MAE_WChar						        wszInitFolder[FILEMGR_MAX_FILEPATH_SIZE];

    u32                                     nCountLimit;

    void                                    *pUserData;
    PfnFileMgrGetSortCompareCb  			pfnCompareCb;
    PfnFileMgrGetFilterCb               	pfnGetFilterCb;
    PfnFileMgrGetOptMenuCb           pfnGetOptionMenuCb;
    PfnFileMgrGetVirtualVolumeListCb    pfnGetVirtualVolumeListCb;

    PfnFileMgrContentFilterCb           pfnContentFilterCb;

	union
	{
		AppGetFileByBrowseCb				pfnGetFilesRspCb;
        AppGetDirByBrowseCb				    pfnGetDirRspCb;
		AppGetPredefinedFileByBrowseCb		pfnGetPredefinedFilesRspCb;
	}uResultCb;

}FileMgrPickerData_t;

typedef struct _FileMgrAppMultiPickerData
{
    u32                                     nTitleTextId;               // title text

    // begining folder
    MAE_WChar						        wszInitFolder[FILEMGR_MAX_FILEPATH_SIZE];

    u32                                     nCountLimit;

    void                                    *pUserData;
    PfnFileMgrGetSortCompareCb  			pfnCompareCb;
    PfnFileMgrGetFilterCb               	pfnGetFilterCb;
    PfnFileMgrGetOptMenuCb           pfnGetOptionMenuCb;
    PfnFileMgrGetVirtualVolumeListCb    pfnGetVirtualVolumeListCb;
    PfnFileMgrContentFilterCb           pfnContentFilterCb;

	AppGetFileByBrowseCb					pfnGetFilesRspCb;
}FileMgrAppMultiPickerData;

typedef struct _FileMgrAppListDirData
{
    //TODO: to be remove
    FileMgrApp_FilterType_e    nCntFilterType;
    u32                                     nTitleTextId;               // title text

    // begin folder
	MAE_WChar						wszInitFolder[FILEMGR_MAX_FILEPATH_SIZE];

    void                            *pUserData;

    boolean                                 bSimple;                    // Memory saving mode, some function are disabled.
    boolean                                 bThumbnailMode;             // Menu syle: Grid mode
    boolean                                 bThumbnailDecode;           // Decode image thumbnail when listing
    PfnFileMgrGetSortCompareCb  pfnCompareCb;
    PfnFileMgrGetFilterCb               pfnGetFilterCb;
    PfnFileMgrGetOptMenuCb           pfnGetOptionMenuCb;
    PfnFileMgrGetVirtualVolumeListCb    pfnGetVirtualVolumeListCb;

    // Display style
    ItemDisplayStyle_t              nMenuStyle;
    boolean                         bTwoLineTitle;
    boolean                         bInfoBar;
    u32                             nVirtualRootItemNum;
    FileMgrVirtualVolumeItem_t  *tVRoolList;

    PfnFileMgrGetL1SoftKeyCb    pfnGetL1SoftkeyCb;

    PfnFileMgrTitleUpdateCb   pfnTitleUpdateCb;
    PfnFileMgrTitle2UpdateCb  pfnTitle2UpdateCb;
    PfnFileMgrItemUpdateCb    pfnItemUpdateCb;
    PfnFileMgrInfoBarUpdateCb pfnInfoBarUpdateCb;
    PfnFileMgrFocusChangeCb   pfnFocusChangeCb;
    PfnFileDecodeThumbnailCb        pfnThumbnailDecodeCB;
    PfnFileMgrGetBgColorCb    pfnGetBackgroundColorCb;
    PfnFileMgrGetBgImgCb      pfnGetBackgroundImgIdCb;
}FileMgrAppListDirData_t;

typedef struct FileMgrAppShowMEmData
{
    FileMgrAppMemStatusViewMode_e       eViewMemStatusMode;
}FileMgrAppShowMemData_t;

typedef union _FileMgrAppUserData
{
    FileMgrAppMultiPickerData   tMultiPicker;
    FileMgrPickerData_t     	tPicker;
    FileMgrAppListDirData_t    	tListDir;
    FileMgrAppShowMemData_t    	tShowMem;
}FileMgrAppUserData_u;

typedef struct _FileMgrApp_EmbeddedData
{
    FileMgrAppUserData_u   *pUserData;
    FileMgrApp_APMode_e 	nLaunchType;
}FileMgrApp_EmbeddedData_t;



#endif // __MMI_COMMON_FILEMGR_TYPE_H__
