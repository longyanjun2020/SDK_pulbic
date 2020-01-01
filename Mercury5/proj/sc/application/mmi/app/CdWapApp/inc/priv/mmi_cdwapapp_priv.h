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
* @file    mmi_cdwapapp_priv.h
* @version
* @brief   CDWAP applet private header file
*
*/

#ifndef __MMI_CDWAPAPP_PRIV_H__
#define __MMI_CDWAPAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_cdwapapp.h"

#include "mmi_cdwapapp_common.h"
#include "mmi_event.h"
#include "mmi_common_dialog.h"
#include "mmi_common_inttbl.h"
#include "mmi_common_util.h"
#include "mmi_if_cdwap.h"
#include "mmi_req_cdwap.h"
#include "mmi_req_vendor.h"
#include "mmi_venappid.h"
#include "wap_comm.hi"
#include "wap_porting.hi"//Could AP use other task define?
#include "ven_os.h"
#include "mmi_srv_header.h"

#include "mmi_wdg_headers.h"
#include "mmi_common_vtm.h"
#include "mmi_mae_text_util.h"
#include "mmi_mae_file_util.h"
#include "mmi_common_wdgvar.h"
#include "mmi_common_storage_mgr.h"
#include "mmi_common_window.h"

#include "mmi_cdwapapp_id.h"
#include "cdwapapp_resource.h"

#if defined(__JAVA_MMI__)
#include "mmi_javaamsapp.h"
#endif /* __JAVA_MMI__ */

#ifdef __WAP_MMI_CDWAP__

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/


#define CDW_EDITOR_MAX_CHARS  256
#define CDW_PASSWORD_MAX_COUNT  128

#define MMI_CDWAPAPP_TEXT_MASK_UNDERLINE    (1 << 2)
#define MMI_CDWAPAPP_TEXT_MASK_BOLD           1
#define MMI_CDWAPAPP_EXPLORER_VISIBLE_PAGE  12

//#define CDWAP_USING_RADIO_LIST
//#define __CDWAP_SUPPORT_MULTI_OPEN_FOLDER_HANDLE__
//#define __CDWAP_USE_ASYNC_DELETE_FOLDER__

#define CDWAPAPP_DELETE_FILES_DURATION  50

#define WAP_UNITE(x,y)    (((x) <<16)|((y) & 0x0FFFF))

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum
{
    CDWAPAPP_STORAGE_CARD,
    CDWAPAPP_STORAGE_PHONE,
    CDWAPAPP_STORAGE_CARD2
}CdWapStorage_e;

typedef enum
{
	CDW_MID_OPTION_MENU_L1 = 1,
	CDW_MID_OPTION_MENU_L2_HISTORY,
	CDW_MID_OPTION_MENU_L2_GUIDANCE,
	CDW_MID_OPTION_MENU_L2_BOOKMARK,
	CDW_MID_OPTION_MENU_L2_LOCAL,
	CDW_MID_OPTION_MENU_L2_FOLDER,
	CDW_MID_OPTION_MENU_L2_TOOLS,
	CDW_MID_EDIT_OPTMENU_L1,
	CDW_MID_OPTION_MENU_L1_MARK,
} CdWapMidOption_e;

typedef enum
{
    CDWAP_NODE_LABEL,
    CDWAP_NODE_HOTLINK,
    CDWAP_NODE_IMAGE,
    CDWAP_NODE_LINE,
    CDWAP_NODE_TABLE,
    CDWAP_NODE_TEXTBOX,
    CDWAP_NODE_EDITBOX,
    CDWAP_NODE_PASSWORD,
    CDWAP_NODE_CHECKBOX,
    CDWAP_NODE_RADIOBOX,
    CDWAP_NODE_BUTTON,
    CDWAP_NODE_SINGLELIST,
    CDWAP_NODE_MULTILIST,
}CdWapNodeType_e;

typedef struct CdWapExplorerStruct_Tag
{
    u32 nNodeIndex;
    u32 nNodeParam;
    IWidget *pNodeWidget;
    CdWapNodeType_e eNodeType;
    RECT rc;
    u8* pNodeGroup;
    MAE_WChar *pNodeEditContent; //Due to password mode, we need to store extra string instead of use textinfo
    struct CdWapExplorerStruct_Tag *pNextNodeStruct;
}CdWapExplorerStruct_t;

typedef enum
{
    CDWAP_SET_FOCUS_FIRST,
    CDWAP_SET_FOCUS_TOP,
    CDWAP_SET_FOCUS_BOTTOM,
    CDWAP_SET_FOCUS_TO_INDEX
}CdWapFocusType_e;

typedef struct
{
    u32 nVisibleFocuseIndex;
    CdWapFocusType_e eSetFocusType;
    boolean bVisibleSetFocuse;
}VisibleSetFocuse_t;

typedef struct
{
    IWidget *pMflCntr;
    IWidget *pTextInputNameWdg;
    IWidget *pTextInputURLWdg;
}CdWapWndEditBookMarkWdgList_t;

typedef struct
{
    CdWapWndEditBookMarkWdgList_t tWdgList;
} CdWapWndEditBookMarkWndData_t;

//*******************************************************************//

typedef struct
{
    IWidget *pMflCntr;
    IWidget *pDoubleTextWdg;
    IWidget *pDoubleFontSizeWdg;
    IWidget *pDoubleStorageTypeTextWdg;
} CdWapWndSettingsWdgList_t;

typedef struct
{
    CdWapWndSettingsWdgList_t tWdgList;
} CdWapWndSettingsWndData_t;

typedef struct
{
    IWidget *InputWidget;
    IWidget *MenuWidget;
    boolean bNoFilter;
} CdWapInputUrlWdgList_t;


typedef enum
{
    CDWAPAPP_ACTION_HOTLINK = 1,
    CDWAPAPP_ACTION_REFRESH,
    CDWAPAPP_ACTION_NEXT,
    CDWAPAPP_ACTION_BACK,
    CDWAPAPP_ACTION_HOMEPAGE,
    CDWAPAPP_ACTION_SAVE_IMAGE,
    CDWAPAPP_ACTION_BUTTON,
    CDWAPAPP_ACTION_RADIO,
}CdWapActionType_e;

typedef enum
{
    CDWAPAPP_STATUS_NORMAL = 0,
    CDWAPAPP_STATUS_SUSPENDING,
    CDWAPAPP_STATUS_SUSPENDED
}CdWapApp_Status_e;

typedef enum
{
    CDWAPAPP_ACC_NORMAL = 0,    // at least one T card inserted
    CDWAPAPP_ACC_TCARD_OUT,     // plug out T card
    CDWAPAPP_ACC_NORFLASH       // no T card inserted
}CdWapAppAcc_e;

#ifdef __FEATURE_VECTOR_FONT__
typedef enum
{
    ZOOM_IN_PIX_14 = 14,
    ZOOM_IN_PIX_16 = 16,
    ZOOM_IN_PIX_18 = 18,
    ZOOM_IN_PIX_20 = 20,
    ZOOM_IN_PIX_22 = 22,
    ZOOM_IN_PIX_24 = 24,
    ZOOM_IN_DEFAULT = ZOOM_IN_PIX_20,
}ZOOM_IN_e;
#endif //__FEATURE_VECTOR_FONT__

typedef enum
{
    CDWAPAPP_TABVIEW_BOOKMARK = 0,
    CDWAPAPP_TABVIEW_LOCALPAGE
} CdWapAppTabView_e;

typedef struct
{
    boolean             bViewTpress;
    boolean             bIgnoreViewTrelease;
    boolean             bScrollTpress;
    boolean             bIgnoreScrollTrelease;
    boolean             bKeyPress;
    boolean             bNoFocusChangKey;
    boolean             bIgnoreKeyrelease;
    u8                  nCountGetDataEvent;
    VisibleSetFocuse_t  tVisibleSetFocuse;
    IWidget             *pTopEmptyWidget;
    IWidget             *pBottomEmptyWidget;

    IWidget             *pTitleWdg;
    IContainer          *pViewerCntr;               // explorer VDF absContainer
    IWidget             *pExplorerScrollWdg;
}CdWapExplorerFlag_t;

typedef struct
{
    MenuWdgList_t       tWdgList;
    CdWapAppListInfo_t  tFileListInfo;

} CdWapFileManageWndData_t;

typedef struct
{
    APPLET_BASE_ELEMENTS;
    u8                  nFocusItemId;                // focus item in menu widget
    u32                 nMenuItemID;                // record the selected option menu item id
    u8                  nPlugInOut;                 // 0: noting; 1: SD plug out; 2: USB plug in
    CdWapAppViewType_e  eViewType;                  // to indicate which view is active
    MAE_WChar           *pContent;                  // used to save content input by user when ap is interrupted

    u32                 venHandle;
    u8                  nSuspend;                   // 0, unsuspend, 1; need to be suspend; 2, has suspended
    boolean             bSendEvent;                 // True, send event; False, don't send event
    WapEvent_t          *pWapEvent;                 // save the date come from wap when AP is suspend

    // -- resolve the blinking issue, we will not delete and redraw widget if we don't receive enough node
    WapEvent_t			*pWapEventForUpdate;
    u32                 nNodeCountForUpdate;

    boolean             bIsConvertSent;
    u32                 nConvertEventX;
    u32                 nConvertEventY;

    // init mode
    boolean             bResumeStop;                // deal with end key
    COMMON_SIM_CARD_STATUS_e eSimStatus;                 // check sim status

    boolean             bInit;                      // TRUE, the wap lib is inited success; FALSE, initial failed
    boolean             bIsSorting;
    u32                 nIndexShift;                // When bIsSorting==FALSE, we have to shift index

#ifdef __MMS_MMI_CDMMS__
    boolean             bMmsSuspend;                // TRUE, suspend mms service ; FALSE, not suspend
    boolean				bMmsSrvActivated;				// TRUE,the stop mms checking has passed;FALSE, has not passed.
#endif
    u32                 nLanchMode;                 // wap or wapQQ
    boolean             bStorageAssigned; // Download Launcher storage assignment check
#ifdef __BLUETOOTH_OBEX_MMI__
    boolean             bIsBTSrvRegister;           // TRUE, register bt service notice ; FALSE, not register
    boolean             bBtSrvActivated;			// TRUE:bluetooth service has been activated;False,not yet.
#endif

    boolean             bIsMain;
    boolean             bNeedRecreateMain;
    u32                 nFocusWgdId;

    // file manager mode
#ifdef __CDWAP_SUPPORT_MULTI_OPEN_FOLDER_HANDLE__
    CdWapAppListInfo_t  tBookmakrInfo;              // record bookmark file list info
    CdWapAppListInfo_t  tLocalPageInfo;             // record localpage file list info
#else
    CdWapAppListInfo_t  tMainPageFileListInfo;             // record localpage file list info
#endif

    CdWapAppListInfo_t  tFileListInfo;              // record file list info
    CdWapAppTabView_e eTabViewType;               // bookmark or local page

    MAE_WChar           *pwstrFilePath;
    CdWapHistoryRecd_t  tHistoryItem;               // record the history information
    CdWapFocusHistory_t *pFocusHistory;             // record the focus in different folder level

    // history(record) window, amount defined as DBA_RECORDSTACK_DEEPTH
    T_DB_ParseRCtxt     *pRStack;                    // store record stack

    // explorer
    CdWapExplorerStruct_t     *pNode;                     // explorer display noder
    CdWapExplorerStruct_t     *pFocusedNode;                     // explorer display noder
    IWidget             *pWaitingWdg;

    u32                 nCurrentNodeIndex;
    boolean             bFromExplor;
    boolean             bSetAsHomepage;
    MAE_WChar           *pCurrentEditText;
    boolean             bLockExplorer;
    u32                 nLockType;
    boolean             bEditPassword;
    u32                 nPrevFocusNodeIdx;
    boolean             bSetRepaintFocus;

    WidgetHandler_t     tExplorerHandle;
    WidgetHandler_t     tScrollHandle;
    u32                 nExplorerViewHeight;
    u32                 nScrollBarCurrentPos;

    boolean             bRepaint;

    // option menu
    IWidget             *pIOptMenuWdg;              // option menu widget
    u32                 nOptionType;

    // edit bookmark & launch AP
    IWidget             *pIInputNameWdg;            // input widget in edit bookmark for input name
    IWidget             *pIInputUrlWdg;             // input widget in edit bookmark for input url
    boolean             bEditOnFocused;

    // InputAddress
    CdWapAppUrlList_t    *ptUrlList;                 // the URL list, inputed before
    MAE_WChar           *pAddress;                  // pointer to the address
    WidgetHandler_t     tMenuWidgetHandler;
    WidgetHandler_t     tInputWidgetHandler;
    MAE_WChar           *pwInputAddress;            // save current input URL Str
    MAE_WChar			*pwLastInputAddress;		// for suspend/resume
#ifdef __STREAMING_MODULE__
    MAE_WChar			*pwStreamingAddress;		// for playing streaming media
    boolean             bIsLaunchVideoPlayer;         // TRUE: user select YES to launch video player
#endif
    boolean             bIsMtCallComing;                  // for MT call coming
    boolean				bNotRememberAddress;		// for HTTP streaming address, don't remember it.

    CdwapSettingInfo_t  *ptWapCfgInfo;              // to save wap setting info
    CdWapStorage_e       eStorageType;               // to save storage type setting info

    // edit folder
    boolean             bRename;                    // TRUE, rename a folder; FALSE, create a new folder
    boolean             bDelFile;

    // move file
    MAE_WChar           *pwDestPath;                // the destination path that file will be moved to
    MAE_WChar           *pwFileName;                // the file name that will be moved

    // ConfirmDlg
    MAE_WChar           *pwdownloadFileName;        // file name from download
    boolean             bDlgEntry;
    boolean             bWaitingDlgEntry;

    SoftkeyID_e         nRSK;
    IWidget             *pProgressWgt;

    // mark mode
    MenuWdgList_t       tMarkWdgList;
    ArrayClass_t		*pMarkedItems;
#ifdef __CDWAP_USE_ASYNC_DELETE_FOLDER__
    boolean             bDeleteFolder;              // Flag to check if we are deleting folder
    u32                 nDeleteFolderHandleId;      // HandleiD get from FileMgrAsyncRmDir(), and use for FileMgrBatchCommandAbort() to cancel.
    boolean             bDeleteFolderCancel;        // User cancel deleting
#endif

#ifdef __FEATURE_VECTOR_FONT__
    // zoom size
    u32                 nNowSize;
#endif
    boolean bIsLoadingPage;     // TRUE: loading explorer page, FALSE: have received REQ_WAP_DISPLAY_PAGEHEIGHT_PAGEEND event
    boolean bIsBookMark;    // TRUE: bookmark,  FALSE: save localpage
    boolean bAccessURLResume;   // TRUE: create datalink confirm in suspend,  need to keep pThis->pwInputAddress and free in resume
    boolean bNeedToRefresh;     // TRUE: we pause loading page when suspend, it need to refresh when resume
#ifndef __NAND_MMI__ // NOR
/* #ifdef __WAP_KERNEL_RELEASE_ON_SUSPEND__ // Stand alone WAP kernel suspend feature temparily not defined */
	boolean bNeedToReAccessURL;	// TRUE: need to re-access last URL from resume(release then initialize)
//#endif
#endif
    CmnAppLaunchRspCbInfo_t tRspInfo;

#ifdef JAVA_INSTALL_WITH_TWO_PATH
    MAE_WChar           *pJADFileName;        // JAD file name from download,
#endif

    // download file
    u32                 nExtensionLen;              // Extension length of download file, used to calculate rest of chars on renaming.
	boolean				bInformUser;		  // TRUE: Inform user download fail before exiting by end key confirm-dialog selecting 'NO', FALSE: exit directly.
	boolean				bDisableOptionButton; // TRUE: Disable option button(LSK) for download url mode, FALSE: Not disable option button.
    boolean             bIsOpenDownloadDir;   // TRUE: Open download dir to suspend WAP.

	u8 *pDialStr;  // for WTAI make call string
#ifdef __MMI_OMA_DRM_V1__
	boolean bOMADownload;	//TRUE: OMA download, FALSE: Normal download
#endif

	// drm
	boolean	bIsDrmProcessing;	// judge if drm agent is processing on WAP exit
	void *pFileMgrCbData;	// store processing drm file handle for later use
} CdWapAppData_t;

#ifdef __MMI_OMA_DRM_V1__
typedef struct
{
    IWidget *pNameTxtWdg;
    IWidget *pTypeTxtWdg;
    IWidget *pSizeTxtWdg;
    IWidget *pVendorTxtWdg;
    IWidget *pUriTxtWdg;
    IWidget *pDescriptionTxtWdg;
    IWidget *pPropContainer;
    IWidget *pViewPortWdg;
    IWidget *pScrollBarWdg;
}CdWapWndViewOMADDWdgList_t;
#endif

#endif

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret CdWapConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret CdWapDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CdWapStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CdWapResumeCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CdWapSuspendCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CdWapGetPropertyCb(IApplet *pApplet, u32 nEvt, u32 key, u32 outVal);
boolean CdWapKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CdWapProcessEventCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
#ifdef __MMS_MMI_CDMMS__
void CdWapMmsSuspendIndCb(void *pUserData);
#endif
#ifdef __BLUETOOTH_OBEX_MMI__
void CdWapBtTransInteractiveCb(void *pUserData);
void CdWapBtSendFileCb(void *pUserData, BTSRV_TRANS_RESULT_e eResult);
void CdWapBtRecvFileCb(void *pUserData, BTSRV_TRANS_RESULT_e eResult);
#endif

MAE_Ret CdWapWndMainPageEmptyHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndCreateMainPageEmpty(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndSetMainPageEmpty(void *pCusHandle, void *pWndData);
MAE_Ret CdWapWndDestroyMainPageEmpty(void *pCusHandle, void *pWndData);

MAE_Ret CdWapWndMainPageListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndCreateMainPageList(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndShowMainPageList(void *pCusHandle, void *pWndData);
MAE_Ret CdWapWndSetMainPageList(void *pCusHandle, void *pWndData);
MAE_Ret CdWapWndDestroyMainPageList(void *pCusHandle, void *pWndData);

MAE_Ret CdWapWndPopupMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndCreatePopupMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndSetPopupMenu(void *pCusHandle, void *pWndData);

MAE_Ret CdWapWndFileManageHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndCreateFileManage(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndShowFileManage(void *pCusHandle, void *pWndData);
MAE_Ret CdWapWndSetFileManage(void *pCusHandle, void *pWndData);
MAE_Ret CdWapWndDestroyFileManage(void *pCusHandle, void *pWndData);

MAE_Ret CdWapWndEditFolderHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndCreateEditFolder(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndSetEditFolder(void *pCusHandle, void *pWndData);

MAE_Ret CdWapWndDualSimHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndCreateDualSim(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndSetDualSim(void *pCusHandle, void *pWndData);

MAE_Ret CdWapWndOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndCreateOptionMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndSetOptionMenu(void *pCusHandle, void *pWndData);

MAE_Ret CdWapWndSettingsHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndCreateSettings(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndSetSettings(void *pCusHandle, void *pWndData);
MAE_Ret CdWapWndDestroySettings(void *pCusHandle, void *pWndData);
MAE_Ret CdWapWndShowSettings(void *pCusHandle, void *pWndData);

MAE_Ret CdWapWndCreateFontSizeSettingsHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndCreateFontSizeSettingsWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndSetFontSizeSettingsWnd(void *pCusHandle, void *pWndData);
MAE_Ret CdWapWndDestroyFontSizeSettingsWnd(void *pCusHandle, void *pWndData);

MAE_Ret CdWapWndLaunchAPHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndCreateLaunchAP(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndSetLaunchAP(void *pCusHandle, void *pWndData);
MAE_Ret CdWapWndDestroyLaunchAP(void *pCusHandle, void *pWndData);

MAE_Ret CdWapWndEditBookMarkHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndCreateEditBookMark(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndSetEditBookMark(void *pCusHandle, void *pWndData);
MAE_Ret CdWapWndDestroyEditBookMark(void *pCusHandle, void *pWndData);

MAE_Ret CdWapWndInputURLHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndCreateInputURL(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndSetInputURL(void *pCusHandle, void *pWndData);
MAE_Ret CdWapWndDestroyInputURL(void *pCusHandle, void *pWndData);

MAE_Ret CdWapWndInputURLOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndCreateInputURLOptionMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndSetInputURLOptionMenu(void *pCusHandle, void *pWndData);

MAE_Ret CdWapWndMarkModeHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndCreateMarkMode(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndSetMarkMode(void *pCusHandle, void *pWndData);

MAE_Ret CdWapWndMoveFilesHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndCreateMoveFiles(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndSetMoveFiles(void *pCusHandle, void *pWndData);
MAE_Ret CdWapWndDestroyMoveFiles(void *pCusHandle, void *pWndData);

MAE_Ret CdWapWndViewPageImageHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndCreateViewPageImage(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndSetViewPageImage(void *pCusHandle, void *pWndData);

MAE_Ret CdWapWndSaveBookmarkOrPageHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndCreateSaveBookmarkOrPage(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret CdWapWndSetSaveBookmarkOrPage(void *pCusHandle, void *pWndData);

void CdWapPlugStatusChangeCb(void *pUserData, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);
void CdWapBattLevelChangeCb(void *pUserData, MAEBatteryLevel_e eLevel, MAEBatteryID_e eBatID);
void CdWapUSBStatusIndCb(void* pUserData, MMI_USB_STATUS_E eUSBStatus);
void CdWapDualSimSoftkeyHandleCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void CdWapEditBookmarkAndLocalpageTextChangeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
void CdWapEditViewImageTextChangeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
void CdWapEditFolderTextChangeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
void CdWapTabChangeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, TabChangeData_t *pTabData, IWidget *pWidget);
void CdWapTabItemFree(WdgDynamicMenuItemPtr_t *pMenuItem, void *pOwner, WdgMenuItemType_e eItemType);
void CdWapTabItemGet(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
void CdWapFileManageItemGet(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
void CdWapTabOnFocusCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);
void CdWapTabSoftkeyActCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void CdWapFontSizeRadioMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void CdWapOptionMenuSoftkeyHandleCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void CdWapInputURLOptionMenuSoftkeyHandleCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void CdWapMarkOptionMenuSoftkeyHandleCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#ifdef __MMI_OMA_DRM_V1__
void CdWapDrmProcessCb(void *pUserData, MAE_WChar *pwDrmFilePath, MAE_Ret nRetDRM);
#endif
void CdWapEditOptionMenuSoftkeyHandleCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void CdWapEditOptionMenuL2SoftkeyHandleCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#ifdef __TOUCH_SCREEN_MMI__
void CdWapTouchNoItemCb (void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif

void CdWapSettingsFocusSelectCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, MFLFocusData_t *pMFLFocusData, IWidget *pWidget);
void CdWapEditBookMarkNameTextChangeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
void CdWapEditBookMarkURLTextChangeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
#ifdef __CDWAP_USE_ASYNC_DELETE_FOLDER__
void CdWapAppDeleteFolderCb(void *pApplet, void *pInfo);
void CdWapFinishDeleteFolderActionCb(void *pApplet, u32 nRetCode);
#endif
void CdWapFinishMoveFileActionCB(void *pApplet, u32 nRetCode);
void CdWapUrlListItemGet(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
void CdWapUrlListItemFree(WdgDynamicMenuItemPtr_t *pMenuItem, void *pOwner, WdgMenuItemType_e eItemType);
void CdWapInputUrlTextChangeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pIWidget);
void CdWapInputUrlTextOnFocusCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bFocus, IWidget *pWidget);
void CdWapInputUrlOnFocusCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);
void CdWapInputUrlMenuSelectCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void CdWapMarkModeOnFocusCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);
void CdWapMarkModeSoftkeyActCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
boolean CdWapMenuWidgetHandler(void* pUserData, MAE_EventId nEvt, u32 nParam1, u32 nParam2);
boolean CdWapInputWidgetHandler(void* pUserData, MAE_EventId nEvt, u32 nParam1, u32 nParam2);

MAE_Ret _CdWapSendReq(void *pApplet, u32 nType, u32 nParam1, u32 nParam2, u32 nDataLen, void* pData);
MAE_Ret _CdWapNoLockSendReq(void *pApplet, u32 nType, u32 nParam1, u32 nParam2, u32 nDataLen, void* pData);

#endif /* __MMI_CDWAPAPP_PRIV_H__ */
