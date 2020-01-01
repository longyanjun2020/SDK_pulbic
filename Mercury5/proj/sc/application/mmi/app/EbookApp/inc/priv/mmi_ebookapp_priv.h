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
* @file    mmi_ebookapp_priv.h
* @version
* @brief   Ebook applet private header file
*
*/
#ifndef __MMI_EBOOKAPP_PRIV_H__
#define __MMI_EBOOKAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_ebookapp.h"

#include "app_utility.h"
#include "mmi_mae_text_util.h"

#include "mmi_ebookapp_cfg.h"
#include "mmi_common_encoding.h"
#include "mmi_common_dialog_id.h"

#include "mmi_srv_header.h"
#include "mmi_common_vtm.h"

#include "mmi_launcher_filemanager.h"
#include "mmi_ebookapp_id.h"
#include "ebookapp_resource.h"

#include "mmi_common_storage_mgr.h"

#include "sys_sys_wmh_sys.h"	/* For vm_sysDelayWatchDogReset(). */
#if defined(__3D_UI_EBOOK__)
#include "mae_glflipeffectwidget.h"
#endif

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define E_BOOK_MAX_FILESIZE 	(10*1024*1024)
#define E_BOOK_MAX_FREESPACE 	((E_BOOK_MAX_FILESIZE * 18) /(1024*1024))
#define E_BOOK_MIN_FREESPACE 	((E_BOOK_MAX_FILESIZE * 2) /(1024*1024))
#ifndef __MMI_SCRIPT_EASY__
#define E_BOOK_MAX_BUFSIZE 		(1024*2)             //(1024*16)
#define E_BOOK_MAX_BUFSIZE_VECTORFONT 		(1024*2)             //(1024*16)
#else
#define E_BOOK_MAX_BUFSIZE 		(1024)
#define E_BOOK_MAX_BUFSIZE_VECTORFONT 		(1024)
#endif
#define E_BOOK_CHECK_EXP    4
#define E_BOOK_CHECK_LINE   (1<<E_BOOK_CHECK_EXP)
#define E_BOOK_MAX_LOAD_LINES 	(6*E_BOOK_CHECK_LINE)
#define E_BOOK_MAX_LINES_TO_CHECK   64              //2000
#define E_BOOK_LINES_TO_RESET_WATCHDOG	32
#define E_BOOK_ERROR_LINE 	0xFFFFFFFF
#define E_BOOK_INVALID_INDEX    0xFFFF

#define E_BOOK_MIN_FILE_NAME_LEN    13
#define E_BOOK_MAX_ONCE_CHECK_FILES 20
#define E_BOOK_CHECK_FILES_DURATION  2
#define E_BOOK_MAX_FILES    3000
#define E_BOOK_EXTERN_NAME_LEN  4
#define E_BOOK_FILE_HEAD_MAX_LEN    5

#define E_BOOK_CREATE_BMK_DURATION  200             // 2
#define E_BOOK_CREATE_BMK_DURATION_IN_ACTIVE  222   //70

#define E_BOOK_FILE_100M    (1024*1024*100)
#define E_BOOK_FILE_1M      (1024*1024)
#define E_BOOK_FILE_1K      (1024)

#define E_BOOK_RECREATE_BMK 0
#define E_BOOK_GO_ON_CREATE_BMK 1
#define E_BOOK_CREATE_BMK_ACTIVE    3
#define E_BOOK_SAVE_BMK_INFO    0xffff

#define WCHAR_SPACE     0x0020
#define WCHAR_RETURN    0x000A
#define WCHAR_ISIN(wch, cBtm, cTop)	((MAE_WChar) ((wch) - (cBtm)) <= ((MAE_WChar) (cTop) - (cBtm)))
#define W_IS_WHITESPACE(wch)   		((wch) == WCHAR_SPACE)
/* ouyang's code start  */

#define BOOKMARK_NULL_SLOT		(0xffff)
#define BOOKMARK_MAX_SLOT			(8)

#define BOOKMARK_HEAD_VALID		(0x5a5a)
#define BOOKMARK_HEAD_EMPTY		(0xa5a5)

#define E_BOOK_MAX_FILE_LENGTH      280
#define E_BOOK_MAX_FILE_NAME_LEN (E_BOOK_MAX_FILE_LENGTH-mae_wstrlen(CARD_DIR_EBOOK))
#define E_BOOK_BMK_VALID    0x12345678

#define E_BOOK_STRING_LESS_SIZE (RS_MAIN_LCD_HEIGHT / E_BOOK_TEXTBROWSE_LINE_HEIGHT * 3)

#define E_BOOK_POSITION_INFOSTART   	(sizeof(BookMark_t)*BOOKMARK_MAX_SLOT)
#define E_BOOK_POSITION_FILESTART 		(E_BOOK_POSITION_INFOSTART+sizeof(BookMarkInfo_t))

#define BOOKMARK_TITEL_SMSTXT_LEN   10

#define INDICATOR_PAGE_TXT_LEN   30

#define TEXTBROWSER_RANGE   7
#define TEXTFULLBROWSER_RANGE   10

#define MAX_TEXT_LINE   20

//image boarder
#define E_BOOK_TEXT_BROWSER_BOARD_X RS_MAIN_LCD_WIDTH-E_BOOK_TEXT_BROWSER_BOARD_W
#define E_BOOK_TEXT_BROWSER_BOARD_Y RS_MAIN_TITLE_HEIGHT
#define E_BOOK_TEXT_BROWSER_BOARD_H RS_MAIN_DEFVIEW_HEIGHT - RS_MAIN_TITLE_HEIGHT
#define E_BOOK_TEXT_BROWSER_BOARD_W 14
#define E_BOOK_TEXT_BROWSER_BOARD_TOP_H 10
#define E_BOOK_TEXT_BROWSER_BOARD_BUTTON_H 6
#define E_BOOK_TEXT_FULLBROWSER_BOARD_Y 0
#define E_BOOK_TEXT_FULLBROWSER_BOARD_H RS_MAIN_LCD_HEIGHT


//indicator
#define E_BOOK_TEXTBROWSER_INDICATOR_X 0
#define E_BOOK_TEXTBROWSER_INDICATOR_Y RS_MAIN_DEFVIEW_HEIGHT - E_BOOK_TEXTBROWSER_INDICATOR_H -E_BOOK_TEXTBROWSER_PAGEIDX_TEXT_H
#define E_BOOK_TEXTBROWSER_INDICATOR_W RS_MAIN_LCD_WIDTH - E_BOOK_TEXT_BROWSER_BOARD_W*2
#define E_BOOK_TEXTBROWSER_INDICATOR_H 26
#define E_BOOK_TEXTBROWSERFULL_INDICATOR_Y RS_MAIN_LCD_HEIGHT - E_BOOK_TEXTBROWSER_INDICATOR_H -E_BOOK_TEXTBROWSER_PAGEIDX_TEXT_H

//text wdg
#define E_BOOK_TEXTBROWSER_TEXT_X 0
#define E_BOOK_TEXTBROWSER_TEXT_Y RS_MAIN_TITLE_HEIGHT+E_BOOK_TEXT_BROWSER_BOARD_TOP_H
#define E_BOOK_TEXTBROWSER_TEXT_W RS_MAIN_LCD_WIDTH - E_BOOK_TEXT_BROWSER_BOARD_W
#define E_BOOK_TEXTBROWSER_TEXT_H RS_MAIN_DEFVIEW_HEIGHT - RS_MAIN_TITLE_HEIGHT -E_BOOK_TEXTBROWSER_INDICATOR_H-E_BOOK_TEXTBROWSER_PAGEIDX_TEXT_H - E_BOOK_TEXT_BROWSER_BOARD_BUTTON_H - E_BOOK_TEXT_BROWSER_BOARD_TOP_H +5

#define E_BOOK_TEXTFULLBROWSER_TEXT_X 0
#define E_BOOK_TEXTFULLBROWSER_TEXT_Y E_BOOK_TEXT_BROWSER_BOARD_TOP_H
#define E_BOOK_TEXTFULLBROWSER_TEXT_W RS_MAIN_LCD_WIDTH-E_BOOK_TEXT_BROWSER_BOARD_W
#define E_BOOK_TEXTFULLBROWSER_TEXT_H RS_MAIN_LCD_HEIGHT -E_BOOK_TEXTBROWSER_INDICATOR_H -E_BOOK_TEXTBROWSER_PAGEIDX_TEXT_H - E_BOOK_TEXT_BROWSER_BOARD_BUTTON_H - E_BOOK_TEXT_BROWSER_BOARD_TOP_H+5

//flip wdg
#define E_BOOK_TEXTBROWSER_FLIP_X E_BOOK_TEXTBROWSER_TEXT_X
#define E_BOOK_TEXTBROWSER_FLIP_Y E_BOOK_TEXTBROWSER_TEXT_Y
#define E_BOOK_TEXTBROWSER_FLIP_W E_BOOK_TEXTBROWSER_TEXT_W
#define E_BOOK_TEXTBROWSER_FLIP_H E_BOOK_TEXTBROWSER_TEXT_H  + E_BOOK_TEXTBROWSER_INDICATOR_H  +E_BOOK_TEXTBROWSER_PAGEIDX_TEXT_H

#define E_BOOK_TEXTFULLBROWSER_FLIP_X E_BOOK_TEXTFULLBROWSER_TEXT_X
#define E_BOOK_TEXTFULLBROWSER_FLIP_Y E_BOOK_TEXTFULLBROWSER_TEXT_Y
#define E_BOOK_TEXTFULLBROWSER_FLIP_W E_BOOK_TEXTFULLBROWSER_TEXT_W
#define E_BOOK_TEXTFULLBROWSER_FLIP_H E_BOOK_TEXTFULLBROWSER_TEXT_H  + E_BOOK_TEXTBROWSER_INDICATOR_H  +E_BOOK_TEXTBROWSER_PAGEIDX_TEXT_H

#define ABS(a) ((a)<0?-(a):(a))
#define E_BOOK_FLIPEFFECT_IGNORE_THRESHOLD 10

#ifdef __FEATURE_VECTOR_FONT__
#define E_BOOK_FONT_SIZE_UB 24
#define E_BOOK_FONT_SIZE_LB 14
#endif


#define MMI_MD5HASH_SIZE (16) //// MD5 hash length 16 Byte



/*=============================================================*/
// Data type definition
/*=============================================================*/
#if defined(__3D_UI_EBOOK__)
enum
{
    EBOOK_SETFLIP_STATUS_CLOSE,
    EBOOK_SETFLIP_STATUS_OPEN,
};
typedef u16 EBook_SetFlip_Status_e;

enum
{
	EBOOK_FLIP_TYPE_PRE_PAGE,
	EBOOK_FLIP_TYPE_NEXT_PAGE,
	EBOOK_FLIP_TYPE_IND_PAGE,
	EBOOK_FLIP_TYPE_NONE,
};
typedef u16 EBook_Flip_TYPE_e;
#endif

enum
{
	/* Model ID start */
	/* ouyang's code start */
	MID_E_BOOK_FILELIST_OPT_MENUMDL,
	MID_E_BOOK_FILELIST_OPT_0_MENUMDL,
	MID_E_BOOK_TEXTBROWSE_OPT_MENUMDL,
	MID_E_BOOK_BOOKMARK_OPT_MENUMDL,
	MID_E_BOOK_FILE_INFO_TEXTMDL,
	MID_E_BOOK_BOOKMARK_LIST_MENUMDL,
	MID_E_BOOK_BOOKMARKEDIT_OPT_MENUMDL,
	/* ouyang's code end */
	/* Model ID end */
};

typedef s32 MMI_E_BOOK_AP_MID_E;

typedef enum
{
    E_BOOK_STARTTYPE_BYUSER,
    E_BOOK_STARTTYPE_BYFILEMGR,
    E_BOOK_STARTTYPE_END,
} EbookStartType_e;

typedef enum
{
    EDIT_SAVE,
    EDIT_RENAME,
} EbookEdit_e;

typedef enum
{
    SETTING_SCROLLSTYLE,
    SETTING_LANGUAGECODE,
    SETTING_END
} EbookTextBrowseSet_e;

typedef enum
{
    DIALOGUE_NULL,
    DIALOGUE_DELETEFILE,
    DIALOGUE_DELETEALLFILE,
    DIALOGUE_DELETEBOOKMARK,
    DIALOGUE_DELETEALLBOOKMARK,
    DIALOGUE_SCROLLSTYLE,
    DIALOGUE_LANGUAGECODE,
    DIALOGUE_FILETOOLARGE,
    DIALOGUE_FILEZEROSIZE,
    DIALOGUE_NOCARD,
    DIALOGUE_NOSPACE,
#ifdef __BLUETOOTH_MMI__
#ifdef __BLUETOOTH_OBEX_MMI__
    DIALOGUE_BTISSENDING,
#endif
#endif
    DIALOGUE_READ_ERROR,
    DIALOGUE_ERROR,
    DIALOGUE_CARD_ERROR
} EbookDialogue_e;

typedef enum
{
    DELETE_STEP_NULL = 0,
    DELETE_STEP_CONFIRM,
    DELETE_STEP_DELETING
} EbookDeleteStep_e;

typedef struct EbookFileList_t_
{
    struct EbookFileList_t_ *pPrev;
    struct EbookFileList_t_ *pNext;
    u16 nValidItems;
    u16 nIndexArray[E_BOOK_MAX_ONCE_CHECK_FILES];
} EbookFileList_t;


typedef struct
{
    u16 nHead;
    u16 nSlot;
    u32 nPostion;
    MAE_WChar wcName[BOOKMARK_MAX_NAME_CHARACTER + 4 - (BOOKMARK_MAX_NAME_CHARACTER % 4)];    //keep align 4 bytes
    u32 nCheckSum;
} BookMark_t;

typedef struct
{
	u8  Md5Version[MMI_MD5HASH_SIZE];	// MD5 hash value (128bit)
    u32 nTxtFileSize;
    u32 nBmkFileSize;
    u32 nTotalLine;
    EBOOK_DECODE_TYPE_e eLanguageCode;
    u32 nLastLine;
    u32 nValid;
    u32 nLastPos;
    u32 nFinish;
    u32 nCheckSumForLineInfo;
    u32 nCheckSum;
    u32 nReserve1;
    u32 nReserve2;
} BookMarkInfo_t;

typedef struct
{
	APPLET_BASE_ELEMENTS;

	u8  Md5Version[MMI_MD5HASH_SIZE];	// MD5 hash value (128bit)

    u32 nNumberOfFiles;
    u16 nMenuItemFirst;
    u16 nMenuItemSelected;
    MAE_WChar WstrFileName[E_BOOK_MAX_FILE_LENGTH];
    MAE_WChar WstrFileNameWithsuffix[E_BOOK_MAX_FILE_LENGTH];
    MAE_WChar WstrBmkFileNameWithsuffix[E_BOOK_MAX_FILE_LENGTH];
    u32 nTxtFileSize;
    EbookTextBrowseSet_e eTextBrowseSettingType;
    EBOOK_SCROLL_TYPE_e eScrollType;
    EBOOK_SCROLL_TYPE_e eScrollTypeHighLight;
    EBOOK_DECODE_TYPE_e eDecodeType;
    EBOOK_DECODE_TYPE_e eDecodeTypeHighLight;
    EBOOK_DECODE_TYPE_e eLanguageCode;
    EbookDialogue_e eDialogueItem;
    IWidget *pITextWidget;
	IWidget *pIIndicator;
	IWidget *pPageIndex;
    u32 nFileTotalLines;
    u32 nFileTotalPages;
    u32 nFileCurLines;
    u32 nFileOldLines;
	u32 nFileGotoLineMax;
    u32 nTxtStringOffset;
    u32 nCurBufStartLine;
    u32 nCurBufEndLine;
    u32 nCurBufStartPos;
    u32 nCurBufEndPos;
    u32 nLastLine;
    u8 *pSrcBuf;
    MAE_WChar *pwDstBuf;
    MAE_WChar *pwDisplayBuf;
    MAE_WChar *pwDispTextDataBuf;
    u8 *pSrcReadBuf;
    MAE_WChar *pwDstReadBuf;
    u32 *pTmpBuf;
    u32 nSrcBufSize;
    u32 nDstBufSize;
    u32 nSrcReadBufSize;
    u32 nDstReadBufSize;
    u32 nLinePosCheckSum;
	u32 nVisualRange;
    WidgetHandler_t ScrollbarHdlData;
    boolean bIsFullTextBrowse;
    MAE_WChar *pszFileInfoText;
    boolean bCreateBmkInActive;
    boolean bIsBmkOpen;
    boolean bIsTextOpen;
    u32 nLastCreateBmkFilePos;
    u32 nFinish;
    IWidget *pIOptMenuWdg;
    MMI_E_BOOK_AP_MID_E eOptMenuModelId;
    u32 nSelectedID;
    EbookEdit_e eEditType;
    MAE_WChar *pwText; //text in model
    IWidget *pITitleWidget;
    IWidget *pIInputWidget;
    VFS_PartialListFileInfo_t *pstFileInfo;
    u32 nHandle;
    u32 nCheckFileListStep;
    u32 nTotalFileListStep;
    EbookFileList_t *pFileListHead;
    EbookFileList_t *pFileListTail;
    FileMgr_Stream_t *pIFStreamBmk;
    FileMgr_Stream_t *pIFStreamTxt;
    u32 nCreateBmkStep;
    EbookStartType_e eStartType;
    MAE_WndId nWndId;
    EbookDeleteStep_e eDeleteStep;
    boolean bAtCheckBmk;
    boolean bAtSuspend;
#ifdef __FEATURE_VECTOR_FONT__
    u32 nLineHeight;
#endif

    VFS_VOL_TYPE eStorageType;
    boolean bInBmkWnd;
	boolean bInBrowseWnd;
#if defined(__ONBOARD_USER_STORAGE_MMI__) || defined(__DUAL_CARD__)
    u16 nPhoneItemSelected;
    u16 nCardItemSelected;
    u16 nPhoneItemFirst;
    u16 nCardItemFirst;
#endif
	boolean bIsNeedDeleteFile;
	u32 pvUserData;
	CmnLaunchAppFileOpRspCb pfnFileOpRspCb;

#if defined(__3D_UI_EBOOK__)
    Pos_t tPressedPos;
    IWidget *pSetFlipWdg;
	IWidget *pBgBitmapWdg;
	EBook_SetFlip_Status_e eFlipStatus;
	EBook_Flip_TYPE_e eFlipType;
	boolean bIsPressed;
	boolean bEnableDrag;
	IWidget *pMagnifyWdg;
    boolean bIndexBust;
    u32 nBustTxtOffset;
#endif

} EbookAppData_t;

typedef struct
{
    IWidget *pIScrollbarWdg;
    IWidget *pTextWdg;
#if defined(__3D_UI_EBOOK__)
	IWidget *pWdgIndicator;
	IWidget *pDecoratebookImageWdg;
	IWidget *pBookShadeTopImageWdg;
	IWidget *pBookShadeButtonImageWdg;
	IWidget *pPageIndexWdg;
#else
	IWidget *pPageIndexWdg;
#endif
}EbookTextBrowseWdgList_t;

typedef struct
{
    IWidget *pIScrollbarWdg;
    IWidget *pTextWdg;
#if defined(__3D_UI_EBOOK__)
	IWidget *pWdgIndicator;
	IWidget *pDecoratebookImageWdg;
	IWidget *pBookShadeTopImageWdg;
	IWidget *pBookShadeButtonImageWdg;
	IWidget *pPageIndexWdg;
#else
	IWidget *pPageIndexWdg;
#endif
}EbookTextBrowseFullWdgList_t;

typedef struct
{
    IWidget *pIMenuWdg;
    IWidget *pIThmTextWdg;
}EbookFileListWdgList_t;

typedef struct FileListWndData_t_
{
    IWidget *pIMenuWdg;
    IWidget *pIThmTextWdg;
}FileListWndData_t;

typedef struct TextBrowseWndData_t_
{
    IWidget *pIScrollbarWdg;
}TextBrowseWndData_t;

typedef struct TextBrowseSettingWndData_t_
{
    IWidget *pIMenuWdg;
}TextBrowseSettingWndData_t;

typedef struct BookMarkListWndData_t_
{
    IWidget *pIMenuWdg;
}BookMarkListWndData_t;

typedef struct GotoLineWndData_t_
{
	PopUpPromptWdgList_t    tWdgList;
}GotoLineWndData_t;
typedef struct
{
	MAE_WChar wszFileName[FILEMGR_MAX_FILEPATH_SIZE];
	boolean   bIsNeedDeleteFile;
	u32 pvUserData;
	CmnLaunchAppFileOpRspCb pfnFileOpRspCb;
} MmiEbookappRequest_t;
/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret EbookConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret EbookDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean EbookStartCB(IApplet* pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean EbookStopCB(IApplet* pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean EbookResumeCB(IApplet* pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
static boolean EbookSuspendCB(IApplet* pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean EbookKeyPressCB(IApplet* pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean EbookTSClickCB(IApplet* pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean EbookTSPressCB(IApplet* pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
#if !defined(__3D_UI_EBOOK__)
boolean EbookTSLeftCB(IApplet* pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean EbookTSRightCB(IApplet* pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
#endif

//void EbookUSBStatusIndCB(void *pUserData, MMI_USB_STATUS_E eUSBStatus);
void EbookUSBStatusIndCB(char *pSbjName, SubjectStatus_e nSbjStatus, void *pUserData);
#if defined(__APP_MMI_CHECKDISK__)
void EbookCheckDiskStatusIndCB(char *pSbjName, SubjectStatus_e nSbjStatus, void *pUserData);
#endif
void EbookAccessoryPlugStatusCB(void *pUserData, ACCDeviceType_e eDevice, boolean bPlug,ExtCardAccInfo_e eCardinfo);
void EbookCoreBackLightOnOffCB(void *pUserData, boolean bBackLightOn);

void EbookFileListAdaptGet(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);
void EbookFileListMenuItemFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
void EbookFileListMenuSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void EbookFileListMenuBackCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void EbookFileListMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void EbookFileListMenuOnFocusCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);


void EbookBookMarkListFreeMenu(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
void EbookBookMarkListMenuBackCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void EbookBookMarkListMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void EbookBookMarkListMenuSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void EbookBookMarkListMenuOnFocusCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);

void EbookInputWidgetTextChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);

void EbookOptionMenuLayer1SoftkeyCancelCB (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void EbookOptionMenuReqOption2CB (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void EbookOptionMenuLayer1SoftkeySelectCB (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void EbookOptionMenuLayer2SoftkeySelectCB (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void EbookSettingMenuOnFocusCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);
void EbookSettingMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void EbookSettingMenuSoftkeyCancelCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

MAE_Ret EbookDialogueInformationCB(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret EbookDialogueConfirmCB(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
void EbookDelFileTimerCB(void *pData);

void EbookCalcTotalFileTimerCB(void *pData);
void EbookCreateBmkTimerCB(void *pData);

void EbookBrowseFileFree(IBase *pUser, u32 nParam);
MAE_Ret _EbookWndConvertFileList(void* pCusHandle,void* pWndData);
MAE_Ret _EbookWndConvertBookMarkList(void* pCusHandle,void* pWndData);
MAE_Ret _EbookWndConvertBookMarkEdit(void* pCusHandle,void* pWndData);
MAE_Ret _EbookWndConvertOption(void* pCusHandle,void* pWndData);
MAE_Ret _EbookWndConvertFileInfo(void* pCusHandle,void* pWndData);
MAE_Ret _EbookWndConvertTextBrowseSetting(void* pCusHandle,void* pWndData);
MAE_Ret _EbookWndConvertGotoLine(void* pCusHandle,void* pWndData);

MAE_Ret _EbookConvertTextBrowseView(void* pCusHandle,void* pWndData);
MAE_Ret _EbookConvertTextBrowseFullView(void* pCusHandle,void* pWndData);
MAE_Ret _EbookWndConvertTextBrowse(void* pCusHandle,void* pWndData);

#endif /* __MMI_EBOOKAPP_PRIV_H__ */
