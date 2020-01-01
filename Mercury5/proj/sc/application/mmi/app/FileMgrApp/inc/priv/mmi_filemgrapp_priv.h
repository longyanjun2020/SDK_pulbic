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
* @file    mmi_filemgrapp_priv.h
* @version
* @brief   Calibration applet header file
*
*/

#ifndef __MMI_FILEMGRAPP_PRIV_H__
#define __MMI_FILEMGRAPP_PRIV_H__

/*-------------------------------------------------------------------------*/
#include "mmi_filemgrapp.h"
#include "mmi_filemgrapp_util.h"
#include "mmi_filemgrapp_view.h"
#include "mmi_mae_file_util.h"
#include "mmi_common_util.h"
#include "mmi_common_vtm.h"

#include "mmi_baseapplet.h"
#include "mmi_common_cfg.h"
#include "mmi_srv_header.h"
#include "mmi_filemgrapp_id.h"
#include "filemgrapp_resource.h"
#ifdef __MMI_OMA_DRM_V1__
#include "mmi_srv_drmagent.h"
#endif

typedef enum FileMgrAppMarkTypeFromOpt_e_
{
    MARK_NONE_FROM_OPT,
    MARK_SINGLE_FROM_OPT,
    MARK_ALL_FROM_OPT,

    MARK_MAX,
}FileMgrAppMarkTypeFromOpt_e;

typedef enum FileMgrAppDeleteTypeFromOpt_e_
{
    DELETE_NONE_FROM_OPT,
    DELETE_SINGLE_FILE_FROM_OPT,
    DELETE_SINGLE_FOLDER_FROM_OPT,
    DELETE_MARK_FROM_OPT,
    DELETE_ALL_FROM_OPT,

    DELETE_MAX,
}FileMgrAppDeleteTypeFromOpt_e;

typedef enum FileMgrAppCpMvTypeFromOpt_e_
{
    CPMV_NONE_FROM_OPT,
    CPMV_SINGLE_CP_FROM_OPT,
    CPMV_SINGLE_MV_FROM_OPT,
    CPMV_MARK_FROM_OPT,

    CPMV_MAX,
}FileMgrAppCpMvTypeFromOpt_e;

#ifdef __MMI_OMA_DRM_V1__
typedef enum FileMgrAppMarklistProcType_e_
{
    MARKLIST_PROC_DRM_CHECK,
    MARKLIST_PROC_DRM_FILTER,
    MARKLIST_PROC_MAX,
} FileMgrAppMarklistProcType_e;

typedef struct FileMgrApp_MarklistProcData
{
    u32                             nCurrIdx;
    u32                             nFileCount;
    boolean                         bIsProcessing;
    FileMgrAppMarklistProcType_e    eProcType;
    DRM_UsageType_e                 eDrmUsageType;
} FileMgrApp_MarklistProcData_t;
#endif

typedef struct _FileMgrApp_MultiSelData
{
    MAE_WChar                       wszUsedFolder[FILEMGR_MAX_FILEPATH_SIZE];
    FileMgrApp_APMode_e             nBrowsingMode;      // denotes which display mode of the browsing data

    u32                             nFromWndId;
    IWidget                         *pIMenuWdg;
    IWidget                         *pITitleWdg;

    u32                             nNumOfFiles;
    FileMgrAppFLHandleID            tFLHandle;
    VFS_PartialListFilter_t         *pFilter;
    FileMgrAppFolderBrwsItem_t      tCurrentListInfo;

    FileMgrAppMarkTypeFromOpt_e     eMarkTypeFromOpt;
    boolean                         bShowWaitingDialog;
    boolean                         bIsSorting; // TRUE for waiting sorting complete
    boolean                         bNeedToSortData;
    VFS_FileID_t                    nFileId;
#ifdef __MMI_OMA_DRM_V1__
    FileMgrApp_MarklistProcData_t   tMarkProcData;
#endif
}FileMgrApp_MultiSelData_t;

typedef struct _FileMgrApp_NameObjData
{
    MAE_WChar                           *pNewName;
	MAE_WChar   					    *pExt;
    IWidget     					    *pInputWdg;
	ModelListener_t					    tInputMdlLstnr;
    boolean     					    bViewBeSet;
    FileMgrAppOPRslt_e 	        nOPRslt;
    u8          					    nNameFrom; // show the option menu from which mode...
}FileMgrApp_NameObjData_t;

typedef struct _FileMgrApp_DelObjData
{
    FileMgrAppOPRslt_e             nOPRslt;

    boolean                             bDlgPrompt;
    boolean                             bMultiObjDel;
    boolean                             bUserCancel;
	boolean			                    bStartDeleting;
    u32                                 nSelCount;
    u32                                 nDelCount;
    u32                                 nDelIdx;
    u8  			                    nDelFrom;
    u8  			                    nFromList;

	FileMgrHandleID_t                   nMarkedHandleID;
	FileMgrHandleID_t 			        nOpHandleID; // Batch copy/move command handle

	FileMgrAppDeleteTypeFromOpt_e       eDelType;

}FileMgrApp_DelObjData_t;

typedef struct _FileMgrApp_CpMvData
{
    FileMgrAppFolderBrwsItem_t  tCurrentListInfo;   // current focus item
    FileMgrAppMediaBrws_t       *pFolderBrwsData;

    FileMgrAppFileInfo_t        sSelectedFileInfo;

    boolean                     bProgressDlg;
    boolean                     bRsltDlg;
    boolean                     bUserCancel;
    boolean                     bIsWaitingFocus;    // TRUE for create waiting dialog
    boolean                     bIsSorting;         // TRUE for blocking Softkey, Select for menu while waiting sorting complete

    u32                         nSelCount;
    u32                         nOPCount;
    u32                         nOPIdx;
    u32                         nCurrentOPFileSize;

    FileMgrAppStorageType_e     nDestStorage;
    FileMgrAppStorageType_e     nFocusStorage;      // Keep the focused storage from folder back to storage window

    FileMgrAppOPRslt_e          nOPRslt;
    u8                          nCpMvFrom;

    boolean                     bNeedToSortData;
    IWidget                     *pMenuWdg;

    IWidget                     *pObjProcessWdg;    //handle Processing widget of processing dialog

    FileMgrHandleID_t           nMarkedHandleID;
    FileMgrHandleID_t           nOpHandleID;        // Batch copy/move command handle

    FileMgrAppCpMvTypeFromOpt_e eCpMvType;
}FileMgrApp_CpMvData_t;

typedef struct _FileMgrApp_SetAsData
{
    u32                     nSetAsMenuId;
    FileMgrAppFileInfo_t    tSelectedFileInfo;
} FileMgrApp_SetAsData_t;

typedef struct MediaListWndData_t_
{
    IWidget *pIMenuWdg;
    TabMenuWdgList_t TabMenuWdgList;
    FileMgrAppMedialstContentViewWdgList_t ContentWdgList;
    FileMgrAppSortbySelViewWdgList_t SortByWdgList;
    FileMgrAppCpmvDestSelViewWdgList_t CpmvWdgList;
    FileMgrAppCpmvStorageSelViewWdgList_t CpmvSWdgList;
    FileMgrAppListerContentViewWdgList_t ListerWidgetList;
    FileMgrAppListerRootViewWdgList_t RootViewWidgetList;
    FileMgrAppCntgridThumbViewWdgList_t ThumbViewWidgetList;
    PopUpInfoWdgList_t FileinfoWdgList;
#ifdef __FILEMGRAPP_ID3V2_IMG__
    boolean         bPauseID3Img;
    ArrayClass_t    *pID3ImgQueue;
#endif
} MediaListWndData_t;


typedef struct MMI_FILEMGR_TAG {
    APPLET_BASE_ELEMENTS;

    boolean bIsExtMemPresented;     // denotes the external card is inserted or not. it may be changed while the inserting/extracting occurs
#if defined(__DUAL_CARD__)
    boolean bIsExtMem2Presented;    // denotes the external card2 is inserted or not. it may be changed while the inserting/extracting occurs
#endif
    boolean bIsExtMemReadable;      // the external card is readable (all the supported content on external memory are installed into contentDB.)
    boolean bIsSorting;             // TRUE for blocking Softkey, Select for menu while waiting sorting complete
    boolean bIsWaitingFocus;        // True for create waiting dialog
    boolean bVolumeSetFlag;         // True for displaying volume dialog
    boolean bAppSuspend;
    boolean bIsMediaListAudioPlaying;
    boolean bIsWaitAudioCnf;
    boolean bSkipAudioCnf;
#if defined(__APP_MMI_CHECKDISK__)
    boolean bIsCheckDiskMode;
#endif

    FileMgrAppOpOP_e            nOPID;
    FileMgrAppDlgType_e         nCurrDlgType;

    FileMgrAppMediaBrws_t       *pMediaBrwsData;    // the data model for media browsing
    FileMgrAppMediaLstData_t    *pMediaLstData;     // view data.
    FileMgrApp_MultiSelData_t   *pMultiSelData;
    FileMgrApp_DelObjData_t     *pDelObjData;
    FileMgrApp_NameObjData_t    *pNameObjData;
    FileMgrApp_CpMvData_t       *pCpMvData;
    FileMgrApp_SetAsData_t      *pSetAsData;

    FileMgrApp_APMode_e         nAPLaunchFor;       // the applet is launched for what purpose

    MediaListWndData_t          MediaListWndData;

    void                        *pUserData;
    union
    {
        AppGetFileByBrowseCb            pfnGetFilesRspCb;
        AppGetDirByBrowseCb             pfnGetDirRspCb;
        AppGetPredefinedFileByBrowseCb  pfnGetPredefinedFilesRspCb;
    }uResultCb;
#ifdef __MMI_OMA_DRM_V1__
    MAE_WChar *pAudioFullPath;
#endif
} MmiFileMgrApp;

//4 ===================== Filemgrapp event callback related functions [begin] =====================
MAE_Ret FileMgrAppConstructor(IApplet *pApplet, u32 nEvt, u32 Param1, u32 Param2);
MAE_Ret FileMgrAppDestructor(IApplet *pApplet, u32 nEvt, u32 Param1, u32 Param2);
__SLDPM_FREE__ boolean FileMgrAppStartCB(IApplet* pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean FileMgrAppStopCB(IApplet *pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean FileMgrAppResumeCB(IApplet *pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean FileMgrAppSuspendCB(IApplet *pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean FileMgrAppEmbeddedCloseCB(IApplet * pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean FileMgrAppKeyPressCB(IApplet* pApplet,MAEEvent_t nEvt, u32 param1, u32 param2);
//4 ===================== Filemgrapp event callback related functions [end] =====================

//4 ===================== Filemgrapp related functions [begin] =====================
static MAE_Ret _FileMgrAppInit(MmiFileMgrApp *pThis, u32 lparam, u32 dparam);

static void _FileMgrAppMultiSelReleaseMultiSelData(FileMgrApp_MultiSelData_t **ppMultiSelData, IBase *pOwner);


//4 ===================== Filemgrapp related functions [end] =====================
//4 ===================== Filemgrapp window related functions [end] =====================
//4 --------------- PredefinedDataList  Window [begin] ---------------
MAE_Ret FileMgrAppWndPredefinedDataListHdl(void* pCusHandle, const WindowMsg_t *pWndMsg, void* pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndCreatePredefinedDataList(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndDestroyPredefinedDataList(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndShowPredefinedDataList(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndHidePredefinedDataList(void *pCusHandle, void *pWndData);
boolean _FileMgrAppPredefinedDataListSuspendHdl(IApplet * pApplet,MAEEvent_t nEvt,u32 lparam,u32 dparam);
//4 ------------ PredefinedDataList Window Utility [begin] ------------
static void _FileMgrAppPredefinedDataListInit(MmiFileMgrApp *pThis);
//4 --------- PredefinedDataList Window Utility [end] ---------
//4 --------------- ListerVirtualRoot  Window [begin] ---------------
MAE_Ret FileMgrAppWndListerVirtualRootHdl(void* pCusHandle, const WindowMsg_t *pWndMsg, void* pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndCreateListerVirtualRoot(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndDestroyListerVirtualRoot(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndShowListerVirtualRoot(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndHideListerVirtualRoot(void *pCusHandle, void *pWndData);
//4 ------------ ListerVirtualRoot Window Utility [begin] ------------
static void _FileMgrListerVirtualRootInit(MmiFileMgrApp * pThis);
static boolean _FileMgrListerVirtualRootKeyPressHdl(MmiFileMgrApp * pThis,u32 param1,u32 param2);
//4 --------- ListerVirtualRoot Window Utility [end] ---------
//4 --------------- ListerVirtualRoot  Window [end] ---------------
//4 --------------- Lister  Window [begin] ---------------
MAE_Ret FileMgrAppWndListerHdl(void* pCusHandle, const WindowMsg_t *pWndMsg, void* pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndCreateLister(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndShowLister(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndDestroyLister(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndShowLister(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndHideLister(void *pCusHandle, void *pWndData);
boolean _FileMgrListerSuspendHdl(IApplet * pApplet,MAEEvent_t nEvt,u32 lparam,u32 dparam);
boolean _FileMgrListerResumeHdl(IApplet * pApplet,MAEEvent_t nEvt,u32 lparam,u32 dparam);
//4 ------------ Lister Window Utility [begin] ------------
static void _FileMgrListerInit(MmiFileMgrApp *pThis, void *pWndData);
static boolean _FileMgrListerKeyPressHdl(MmiFileMgrApp * pThis,u32 param1,u32 param2);
//4 --------- Lister Window Utility [end] ---------
//4 --------------- MediaList  Window [begin] ---------------
static MAE_Ret _FileMgrAppCreateFullBrowsingWindow(MmiFileMgrApp *pThis);

//4 ------------ MediaList Window Utility [begin] ------------
__SLDPM_FREE__ static void _FileMgrMediaListObjListingInit(MmiFileMgrApp *pThis);
//4 --------- MediaList Window Utility [end] ---------
//4 --------------- MediaList MultipleSelection  Window [begin] ---------------
MAE_Ret FileMgrAppWndMediaListMultipleSelectionHdl(void* pCusHandle, const WindowMsg_t *pWndMsg, void* pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndCreateMediaListMultipleSelection(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndShowMediaListMultipleSelection(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndHideMediaListMultipleSelection(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndDestroyMediaListMultipleSelection(void *pCusHandle, void *pWndData);
boolean _FileMgrMediaListMultipleSelectionSuspendHdl(IApplet * pApplet,MAEEvent_t nEvt,u32 lparam,u32 dparam);
boolean _FileMgrMediaListMultipleSelectionResumeHdl(IApplet * pApplet,MAEEvent_t nEvt,u32 lparam,u32 dparam);
//4 ------------ MediaListMultipleSelection Window Utility [begin] ------------
MAE_Ret FileMgrAppMultipleSelectionLoadOptMenuMdl(MmiFileMgrApp* pThis, FileMgrOptMenuWndData_t *pOptWndData);

//4 --------- MediaList MultipleSelection Window Utility [end] ---------
//4 --------------- MediaList MultipleSelection  Window [end] ---------------
//4 --- MediaList Widget Wrapper callback related functions [begin] ---
__SLDPM_FREE__ void FileMgrMediaListTabChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TabChangeData_t *pTabData, IWidget *pWidget);
__SLDPM_FREE__ static void _FileMgrMediaListTabChangeHdl(MmiFileMgrApp *pThis, IWidget *pTabWdg, TabChangeData_t* pTabData);

__SLDPM_FREE__ static void _FileMgrMediaListStorageChanged(MmiFileMgrApp *pThis, u32 nFocusStorage);
static void _FileMgrMediaListExtCardAbsent(MmiFileMgrApp * pThis, IWidget *pTabWdg, FileMgrAppStorageType_e eAbsentStorage);


//4 --- MediaList Widget Wrapper callback related functions [end] ---
//4 --------------- MediaList  Window [end] ---------------

//4 --------------- MediaList_Empty_Folder  Window [begin] ---------------
MAE_Ret FileMgrAppWndMediaListEmptyFolderHdl(void* pCusHandle, const WindowMsg_t *pWndMsg, void* pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndCreateMediaListEmptyFolder(void * pCusHandle,void * pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndDestroyMediaListEmptyFolder(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndShowMediaListEmptyFolder(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndHideMediaListEmptyFolder(void *pCusHandle, void *pWndData);
//4  --------------- MediaList_Empty_Folder  Window [End] ---------------

//4 --------------- MediaList_Storage  Window [begin] ---------------
__SLDPM_FREE__ MAE_Ret FileMgrAppWndMediaListStorageAndContentHdl(void* pCusHandle, const WindowMsg_t *pWndMsg, void* pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndCreateMediaListStorageAndContent(void * pCusHandle,void * pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndDestroyMediaListStorageAndContent(void *pCusHandle, void *pWndData);
__SLDPM_FREE__ static MAE_Ret _FileMgrAppWndShowMediaListStorageAndContent(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndHideMediaListStorageAndContent(void *pCusHandle, void *pWndData);
boolean _FileMgrMediaListSuspendHdl(IApplet * pApplet,MAEEvent_t nEvt,u32 lparam,u32 dparam);
boolean _FileMgrMediaListResumeHdl(IApplet * pApplet,MAEEvent_t nEvt,u32 lparam,u32 dparam);
//4 ----- MediaList_Storage Utility [begin] -----

//4 ----- MediaList_Storage Utility [end] -----

//4  --------------- MediaList_Empty_Folder  Window [End] ---------------
//4 --------------- Option Menu  Window [begin] ---------------
MAE_Ret FileMgrAppWndOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndCreateOptionMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndDestroyOptionMenu(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndShowOptionMenu(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndHideOptionMenu(void *pCusHandle, void *pWndData);

//4 ------ Option Menu Utility [begin] ------
static MAE_Ret _FileMgrAppOptionMenuShowUI(MmiFileMgrApp *pThis, FileMgrOptMenuWndData_t *pOptWndData);

//4 Option Menu selected related handle function [begin] -----
void FileMgrAppOptionMenuSelectRenameCreateFolderHdl(MmiFileMgrApp *pThis, const FileMgrOptMenuWndData_t *pOptWndData, FileMgrAppOpOP_e eObjOP);
void FileMgrAppOptionMenuSelectFileInfoHdl(MmiFileMgrApp *pThis, const FileMgrOptMenuWndData_t *pOptWndData);
void FileMgrAppOptionMenuSelectMoveToHdl(MmiFileMgrApp *pThis, const FileMgrOptMenuWndData_t *pOptWndData);

static MAE_Ret _FileMgrAppOptionMenuCreateSelStorageWnd(
    MmiFileMgrApp                   *pThis,
    const FileMgrOptMenuWndData_t   *pOptWndData,
    FileMgrAppCpMvTypeFromOpt_e     eCpMvType,
    FileMgrAppOpOP_e                eObjOp);

//4 Option Menu selected related handle function [end] -----
//4 ------ Option Menu Utility [end] ------

//4 --------------- Virtual Root Option Menu  Window [begin] ---------------
MAE_Ret FileMgrAppWndVirtualRootOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndCreateVirtualRootOptionMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndDestroyVirtualRootOptionMenu(void *pCusHandle, void *pWndData);
MAE_Ret FileMgrAppWndShowVirtualRootOptionMenu(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndShowVirtualRootOptionMenu(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndHideVirtualRootOptionMenu(void *pCusHandle, void *pWndData);
//4 ------ Virtual Root Menu Utility [begin] ------
void _FileMgrAppVirtualRootOptionMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _FileMgrAppVirtualRootOptionMenuSoftkeyCancelCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

//4 --------------- Rename Window [begin] ---------------
MAE_Ret FileMgrAppWndRenameHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndCreateRename(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndDestroyRename(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndShowRename(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndHideRename(void *pCusHandle, void *pWndData);
//4 --------------- Rename Utility [begin] ---------------
static MAE_Ret _FileMgrAppRenameSetView(MmiFileMgrApp *pThis, MAE_WChar *pwszSourceURL, FileMgrOptMenuWndData_t *pOptWndData);
static void _FileMgrAppRenameLoadOptionMenu(MmiFileMgrApp *pThis);
MAE_Ret FileMgrAppRenameLoadOptMenuMdl(MmiFileMgrApp* pThis, FileMgrOptMenuWndData_t *pOptWndData);
static void _FileMgrAppRenameInputWidgetTextChangeCB(void * pApplet,void * pUsrData,WidgetEvtCode_t nEvtCode,TextInfo * pTextInfo,IWidget * pWidget);

static boolean _FileMgrAppRenameKeyPressHdl(MmiFileMgrApp *pThis, u32 param1, u32 param2);
static void _FileMgrAppRenameKeyPressHdlKeyAction(MmiFileMgrApp *pThis);
static void _FileMgrAppRenameKeyPressHdlSKLeft(MmiFileMgrApp *pThis);
static void _FileMgrAppRenameKeyPressHdlSKRight(MmiFileMgrApp *pThis);

static boolean _FileMgrAppRenameIsFileBackgroundPlaySong(MmiFileMgrApp *pThis, MAE_WChar *pwszSourceURL);



//4 --------------- Rename Utility [end] --------------

//4 --------------- Rename Window [end] ---------------

//4 --------------- Memory Status Window [begin] ---------------
MAE_Ret FileMgrAppWndMemoryStatusHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndCreateMemoryStatus(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndDestroyMemoryStatus(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndShowMemoryStatus(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndHideMemoryStatus(void *pCusHandle, void *pWndData);
//4 --------------- Memory Status Utility [begin] ---------------
static boolean _FileMgrAppMemStatusKeyPressHdl(MmiFileMgrApp *pThis, u32 param1, u32 param2);


//4 --------------- Memory Status Utility [end] --------------

//4 --------------- Memory Status Window [end] ---------------


//4 --------------- File Info Window [begin] ---------------
MAE_Ret FileMgrAppWndFileInfoHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndCreateFileInfo(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndDestroyFileInfo(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndShowFileInfo(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndHideFileInfo(void *pCusHandle, void *pWndData);
//4 --------------- File Info Utility [begin] ---------------
static boolean _FileMgrAppFileInfoKeyPressHdl(MmiFileMgrApp *pThis, u32 param1, u32 param2);


//4 --------------- File Info Utility [end] --------------
//4 --------------- File Info Window [end] ---------------

//4 --------------- Sort by Window [begin] ---------------
MAE_Ret FileMgrAppWndSortByHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndCreateSortBy(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndDestroySortBy(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndShowSortBy(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndHideSortBy(void *pCusHandle, void *pWndData);
//4 --------------- File Info Utility [begin] ---------------
static boolean _FileMgrAppSortByKeyPressHdl(MmiFileMgrApp *pThis, u32 param1, u32 param2);

//4 --------------- File Info Utility [end] --------------
//4 --------------- File Info Window [end] ---------------

//4 --------------- Select Storage Window [begin] ---------------
MAE_Ret FileMgrAppWndSelectStorageHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndCreateSelectStorage(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndDestroySelectStorage(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndShowSelectStorage(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndHideSelectStorage(void *pCusHandle, void *pWndData);
//4 --------------- Select Storage Utility [begin] ---------------
__SLDPM_FREE__ static MAE_Ret _FileMgrAppSelectStorageRefreshMenu(MmiFileMgrApp * pThis);
static MAE_Ret _FileMgrAppSelectStorageSetMenuFocus(MmiFileMgrApp *pThis);
static MAE_Ret _FileMgrAppSelectStorageShowUI(MmiFileMgrApp * pThis);
static void _FileMgrAppSelectStorageMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _FileMgrAppSelectStorageMenuSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void  _FileMgrAppSelectStorageMenuOnFocusCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);

//4 --------------- Select Storage Utility [end] --------------
//4 --------------- Select Storage Window [end] ---------------

//4 --------------- CP mv Select folder  Window [begin] ---------------
MAE_Ret FileMgrAppWndCPMVSelectFolderHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndCreateCPMVSelectFolder(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _FileMgrAppWndDestroyCPMVSelectFolder(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndShowCPMVSelectFolder(void *pCusHandle, void *pWndData);
static MAE_Ret _FileMgrAppWndHideCPMVSelectFolder(void *pCusHandle, void *pWndData);
//4 --------------- CP mv Select folder Utility [begin] ---------------

//4 --------------- CP mv Select folder Utility [end] --------------
//4 --------------- CP mv Select folder Window [end] ---------------


//4 ===================== Filemgrapp window related functions [end] =====================

//4 ===================== Newly added [Service wrapper function prototype] [begin] =====================
static void _FileMgrAppAccessoryPlugStatusCB(void *pThisData, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);
static void _FileMgrAppUSBStatusCB(void * pThisData,MMI_USB_STATUS_E eUSBStatus);
#if defined(__APP_MMI_CHECKDISK__)
static void _FileMgrAppCheckDiskStatusListener(char *pSbjName, SubjectStatus_e nSbjStatus, void *pUser);
#endif
//------------------------------------------------

//4 ===================== Newly added [Service wrapper function prototype] [end] =====================

static boolean _FileMgrAppVolumeKeyHdl(MmiFileMgrApp *pThis, u32 param1, u32 param2);

/*-------------------------------------------------------------------------*/
/* User Code End */
/*-------------------------------------------------------------------------*/
#endif /* __MMI_FILEMGRAPP_PRIV_H__ */
