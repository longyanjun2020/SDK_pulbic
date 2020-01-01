/**
* @file mmi_snoteapp_priv.h

*
*
* @version $Id$
*/

/*-------------------------------------------------------------------------*/
#ifndef __MMI_SNOTEAPP_PRIV_H__
#define __MMI_SNOTEAPP_PRIV_H__

#include "mmi_baseapplet.h"
#include "mmi_mae_file_util.h"
#include "mmi_common_dialog.h"
#include "mmi_mae_md5.h"
#include "mmi_common_vtm.h"
#include "mmi_common_inttbl.h"
#include "mmi_srv_header.h"
#include "mmi_snoteapp_id.h"
#include "snoteapp_resource.h"
#include "mmi_common_storage_mgr.h"
#include "mmi_common_window.h"

#include "mmi_launcher_filemanager.h"
/**************************************************
 ** Define Index File Version (u16): FORMAT: (y)YMM,
 ** Update version number only when format changed.
 **************************************************/

#define MMI_SNOTEAPP_IDX_FILE_VERSION	903
#define MMI_SNOTEAPP_IDX_EMPTY		255
#define MMI_SNOTEAPP_MAX_NOTES		20
#define MMI_SNOTEAPP_MAX_NOTE_BYTE_LEN	176 // 88 char

#define MMI_SNOTEAPP_MD5HASH_SIZE	16 // MD5 hash length 16 Byte

#define MMI_SNOTEAPP_LISTTHUMB_MENUMODEL_DIFF 2
#define MMI_SNOTEAPP_LISTTHUMB_MENUMODEL_MAX 6
#define MMI_SNOTEAPP_LISTTHUMB_MAX_QUEUE_SIZE 20

#define MMI_SNOTEAPP_PEN_OFFSET_Y	(RS_SNOTEAPP_EDITNOTE_SKETCHCANVAS_POS_Y+RS_MAIN_TITLE_HEIGHT)
#define MMI_SNOTEAPP_INPUTWIDGET_LINE_GAP 0

#define MMI_SNOTEAPP_PICKCOLOR_BGCOLOR_1 COLOR_ORANGE_4
#define MMI_SNOTEAPP_PICKCOLOR_BGCOLOR_2 COLOR_GREEN_7
#define MMI_SNOTEAPP_PICKCOLOR_BGCOLOR_3 COLOR_BLUE_6
#define MMI_SNOTEAPP_PICKCOLOR_BGCOLOR_4 COLOR_ORANGE_6
#define MMI_SNOTEAPP_PICKCOLOR_BGCOLOR_5 COLOR_RED_7
#define MMI_SNOTEAPP_PICKCOLOR_BGCOLOR_6 COLOR_BROWN_6

#define MMI_SNOTEAPP_PEN_COLOR0	COLOR_GREY_4
#define MMI_SNOTEAPP_PEN_COLOR1	COLOR_ORANGE_3
#define MMI_SNOTEAPP_PEN_COLOR2 COLOR_BROWN_2
#define MMI_SNOTEAPP_PEN_COLOR3 COLOR_GREEN_1
#define MMI_SNOTEAPP_PEN_COLOR4 COLOR_BLUE_1
#define MMI_SNOTEAPP_PEN_COLOR5 COLOR_GREY_1
#define MMI_SNOTEAPP_PEN_COLOR6 COLOR_RED_5
#define MMI_SNOTEAPP_PEN_COLOR7 COLOR_PURPLE_3
#define MMI_SNOTEAPP_PEN_COLOR8 COLOR_GREEN_2
#define MMI_SNOTEAPP_PEN_COLOR9 COLOR_BLUE_3

#if defined(__SPACE_FULL_STORAGE_SELECTION_MMI__) 
#define M_nSize_MenuItem(x) (sizeof(x)/sizeof(x[0]))
#endif

static RGBColor_t _gUsedColor[16] =
{
	MMI_SNOTEAPP_PICKCOLOR_BGCOLOR_1,
	MMI_SNOTEAPP_PICKCOLOR_BGCOLOR_2,
	MMI_SNOTEAPP_PICKCOLOR_BGCOLOR_3,
	MMI_SNOTEAPP_PICKCOLOR_BGCOLOR_4,
	MMI_SNOTEAPP_PICKCOLOR_BGCOLOR_5,
	MMI_SNOTEAPP_PICKCOLOR_BGCOLOR_6,

	MMI_SNOTEAPP_PEN_COLOR0,
	MMI_SNOTEAPP_PEN_COLOR1,
	MMI_SNOTEAPP_PEN_COLOR2,
	MMI_SNOTEAPP_PEN_COLOR3,
	MMI_SNOTEAPP_PEN_COLOR4,
	MMI_SNOTEAPP_PEN_COLOR5,
	MMI_SNOTEAPP_PEN_COLOR6,
	MMI_SNOTEAPP_PEN_COLOR7,
	MMI_SNOTEAPP_PEN_COLOR8,
	MMI_SNOTEAPP_PEN_COLOR9,
};

const VFS_PartialListFilter_t _gtFileListFilter
= {
    //FileManagerExtFilter_t
    {4 /* number of extension */, L"BMP|SKT|THU|dat" /* file extensitons */}
    // FileManagerSizeFilter_t
    ,{0, 0xFFFFFFFF}
    // FileManagerAttrFilter_t
    ,{VFS_ATTR_FILTER_IGNORE, VFS_ATTR_FILTER_IGNORE, VFS_ATTR_FILTER_OUT, VFS_ATTR_FILTER_IGNORE, VFS_ATTR_FILTER_IGNORE}
};

#define	MMI_SNOTEAPP_NAME_PREFIX			L"SNOTE"
#define	MMI_SNOTEAPP_NAME_PREFIX0 			L"SNOTE0"
#define	MMI_SNOTEAPP_NAME_POSTFIX_SKETCH 	L".BMP"
#define	MMI_SNOTEAPP_NAME_POSTFIX_TXTDAT 	L".SKT"
#define	MMI_SNOTEAPP_NAME_POSTFIX_THUMB 	L".THU"
#define	MMI_SNOTEAPP_IDXTABLE_FILENAME		L"SNoteTable.dat"
#define MMI_SNOTEAPP_DIR					L"SNOTE/"

#define MMI_SNOTEAPP_DIR_PHONE				DIR_PHONE
#define MMI_SNOTEAPP_DIR_CARD				DIR_CARD
#define MMI_SNOTEAPP_DIR_CARD2				DIR_CARD2

// Storage path, do not modify it here. Please check mmi_common_storage_mgr.h
#define MMI_SNOTEAPP_PHONEPATH 				(MMI_SNOTEAPP_DIR_PHONE MMI_SNOTEAPP_DIR)	//L"fs:/PHON/SNOTE/"
#define MMI_SNOTEAPP_CARD_PATH 				(MMI_SNOTEAPP_DIR_CARD MMI_SNOTEAPP_DIR)		//L"fs:/CARD/SNOTE/"
#define MMI_SNOTEAPP_CARD2_PATH 			(MMI_SNOTEAPP_DIR_CARD2 MMI_SNOTEAPP_DIR)	//L"fs:/SD_2/SNOTE/"

// IDX FILE URL (Path + MMI_SNOTEAPP_IDXTABLE_FILENAME)
#define MMI_SNOTEAPP_IDXTABLE_PHONEURL 		(MMI_SNOTEAPP_DIR_PHONE MMI_SNOTEAPP_DIR MMI_SNOTEAPP_IDXTABLE_FILENAME)  //L"fs:/PHON/SNOTE/SNoteTable.dat"
#define MMI_SNOTEAPP_IDXTABLE_CARDURL 		(MMI_SNOTEAPP_DIR_CARD MMI_SNOTEAPP_DIR MMI_SNOTEAPP_IDXTABLE_FILENAME)  //L"fs:/CARD/SNOTE/SNoteTable.dat"
#define MMI_SNOTEAPP_IDXTABLE_CARD2URL		(MMI_SNOTEAPP_DIR_CARD2 MMI_SNOTEAPP_DIR MMI_SNOTEAPP_IDXTABLE_FILENAME) //L"fs:/SD_2/SNOTE/SNoteTable.dat"

#define MMI_SNOTEAPP_NOTESIZE 70
#define MMI_SNOTEAPP_DIALOG_TIME 500
#define	MMI_SNOTEAPP_TRANSITION_DURATION 250

#define MMI_SNOTEAPP_PEN_SIZE_SMALL 0
#define MMI_SNOTEAPP_PEN_SIZE_MEDIUM 1
#define MMI_SNOTEAPP_PEN_SIZE_LARGE 2

#define MMI_SNOTEAPP_FLAG_TO_ADD 0
#define MMI_SNOTEAPP_FLAG_TO_EDIT 1

#define MMI_SNOTEAPP_THUNBNAIL_PER_SCREEN 4

typedef enum
{
	URL_TypeBMP = 0,
	URL_TypeSKT,
	URL_TypeTHU,
} Mmi_URL_type_e;

typedef enum
{
	ImgSaveState_Init = 0,
	ImgSaveState_First_Done,
	ImgSaveState_Both_Done,
} Mmi_SNote_ImgSaveState_e;


typedef enum
{
	MMI_SNOTE_NONE= 0,
	MMI_SNOTE_CARD_INSUFFICIENT,
	MMI_SNOTE_PHONE_INSUFFICIENT,
	MMI_SNOTE_FOLDER_NOT_EXISTED,
	MMI_SNOTE_FAIL,
} SNote_ErrorType_e;

#if defined(__SPACE_FULL_STORAGE_SELECTION_MMI__) 
typedef enum
{
    SNOTE_STORAGE_PHONE = 0,
    SNOTE_STORAGE_SD,
    SNOTE_STORAGE_SD2
} SNote_Storage_e;
#endif

/*********************************
*	Mmi_SNoteItem_t
*	0~99 to means exist files
*	255 to means empty slot.
**********************************/
typedef struct
{
	u8 u8FileIndex;
	u32	u32SaveTime;
	u32 u32BGColor; // note's Background color
	u16	u16NoteSize; // String length of TXT part
	u8 u8Align; // alignment
} Mmi_SNoteItem_t;
/*******************************************
*	Mmi_SNoteAppIdxTabBuf_t
*	u16IdxFileVer: Index File Version
*	u8AvailableNote: to stored exist notes
*	au8SortIdx: a sorted index from
*	From Latest to Oldest notes (0~u8AvailableNote)
*	255 to means non index;
********************************************/
typedef struct
{
	u16 u16IdxFileVer;
	u8 u8AvailableNote;
	u8 au8SortIdx[MMI_SNOTEAPP_MAX_NOTES];
	Mmi_SNoteItem_t asNoteItem[MMI_SNOTEAPP_MAX_NOTES];
	u8 u8Align;
} SNoteAppIdxTabBuf_t;
#define MMI_SNOTEAPP_IDXTBL_FILE_SIZE sizeof(SNoteAppIdxTabBuf_t)

typedef struct
{
	SNoteAppIdxTabBuf_t stSNoteAppIdxTab;
	// MD5Hash for IdxTabBuf, 16 bytes
	u8 pDigest[MMI_SNOTEAPP_MD5HASH_SIZE];
} SNoteAppIdxFileWithMd5Hash_t;
#define MMI_SNOTEAPP_IDXFILE_WITH_MD5HASH_SIZE sizeof(SNoteAppIdxFileWithMd5Hash_t)

typedef struct SNOTEAPP_PenProperty_TAG
{
	s32			s32origin_x;
	s32			s32origin_y;
	u32			u32penSize;
	RGBColor_t	tPenColor;
	RGBColor_t	tEraserColor;
	boolean		bIsStarDot;
} SNOTEAPP_PenProperty_t;

typedef struct SNOTEAPP_OPTION_MENU_TAG
{
	ModelListener_t stOptionMenuVMListener;
	ModelListener_t stOptionMenuL2VMListener; //View Model Listener
	IWidget	    *pIOptMenuWdg;
	IMenuModel	*pIOptMenuModel;
} SNOTEAPP_OPTIONMENU_t;

typedef struct SNOTEAPP_IMG_DECODE_ITEM_TAG
{
	IImage	*pImage;
	u32		u32Idx;
}SNOTEAPP_IMG_DECODE_ITEM;

/* id for pickup color menu item*/


/*-------------------------------------------------------------------------*/

/**
 * Application structure
 */


typedef struct
{
    APPLET_BASE_ELEMENTS;
	// NoteIdxTable Buffer
	SNoteAppIdxTabBuf_t		*pIdxTabBuf;
	SNOTEAPP_PenProperty_t	*pPenProperty;

	// for list thumbnail image cache
	SNOTEAPP_IMG_DECODE_ITEM	atPlistDecodeTbl[MMI_SNOTEAPP_LISTTHUMB_MAX_QUEUE_SIZE];
	u8					u8DecodeTblNum;


	u8					u8ToEditIdx;
	u8					u8tmpPenSize;
	u16					u16NoteSize;
	u8					u8EmptySlot;
	u8                  u8TargetIdx;
	MAE_WChar			*pThumbFileURL;

	// flag to use
	boolean				bIsSDInserted;
#ifdef __DUAL_CARD__
	boolean 			bIsSD2Inserted;
#endif
	boolean				bIsSaveCheck;
	boolean				bIsStrokeListActive;
	boolean				bIsColorListActive;
	boolean				bIsPenActive;
	boolean				bIsAddNewNote;
	boolean				bIsSaving;
	boolean				bIsSaved;
	boolean				bIsResumeStopping;
	boolean				bIsSDneedRecheck;
	boolean				bIsDecoding;
	boolean				bIsMassStorage;
#if defined(__APP_MMI_CHECKDISK__)
	boolean				bIsCheckDisk;
#endif
    boolean             bIsExtMemCardError;
	boolean				bIsTextLineOverflow;
	boolean				bIsNeedUpdateThumbList;
	boolean             bIsinsufficient;
	boolean             bIsBmpFormatError;
	boolean             bIsBmpLoadError;
	s8                  gNum;

	VFS_VOL_TYPE        eStorageType;
	SNote_ErrorType_e   eDlgError;
} SNoteAppData_t;

typedef struct
{
    IWidget *pMenuWdg;
}SNoteListWndData_t;

typedef struct
{
    IWidget *pPickColorMenuWdg;
}SNotePickColorWndData_t;

typedef struct
{
    IWidget *pBmpWdg;
    IWidget *pTextWdg;
    IWidget *pPenSwitchIconWdg;
    IWidget *pStrokeSwitchIconWdg;
    IWidget *pColorSwitchIconWdg;
    IWidget *pTxtBtnWdg;
    IWidget *pEraserSwitchIconWdg;
    IWidget *pStrokeGridWdg;
    IWidget *pColorGridWdg;

	IDisplay			          *pDisp;
	IBitmap	                      *pBitmap;
}EditWndData_t;

typedef struct
{
#ifndef __WIDGET_DISABLE_TRANSITION__
    IWidget *pITransitionWdg;
#endif
    IWidget *pBitmapWdg;
    IWidget *pITimestampTextWdg;
    IWidget *pPreBtnWdg;
    IWidget *pNextBtnWdg;
}SNoteViewerWndData_t;

typedef struct
{
	IWidget *pTitleWdg;
	IWidget *pScrollWdg;
	IWidget *pInputWdg;
}SNoteInputWndData_t;

typedef struct
{
    IWidget *pImgWidget;
    IWidget *pMenuWidget;
}SNoteSelectWndData_t;

#if defined(__SPACE_FULL_STORAGE_SELECTION_MMI__) 
typedef struct
{
    IWidget *pMenuWidget;
}SNotePopupSelectWndData_t;
#endif
MAE_Ret _WndPickColorHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _WndThumbnailListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _WndOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _WndViewerHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _WndEditNoteHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _WndInputTextHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

MAE_Ret _WndSelectHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#if defined(__SPACE_FULL_STORAGE_SELECTION_MMI__) 
MAE_Ret _WndPopupSelectHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif


static void _SNoteAppInit(SNoteAppData_t* pThis, u32 nEvt, u32 nParam1, u32 nParam2);
static void _GetPalette(RGBColor_t **pColorPallet, u16 *nCount);
static void _ThumbImgDecodeNotify(IImage *pImage, IBase *pData, ImgStatus_t nStatus);
static void _ThumbGridViewAdaptGet (WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
static void _RefreshThumbnailList(SNoteAppData_t *pThis);
static MAE_Ret _ShowStokeColorGridwdg(SNoteAppData_t* pThis);
static MAE_Ret _SDCardReCheckProcess(SNoteAppData_t *pThis);
static MAE_Ret _LoadThumbnailImg(SNoteAppData_t* pThis, u8 u8FileIndex, IImage** ppImg);
static MAE_Ret _LoadBitmap(SNoteAppData_t* pThis, u8 u8FileIndex, IBitmap** ppBmp);
static MAE_Ret _BmpWdgSetData(SNoteAppData_t* pThis, IWidget *pBmpWdg, u8 u8SortedIndex);
static MAE_Ret _SaveFiles(SNoteAppData_t*pThis, IBitmap *pBitmap);
static MAE_Ret _SaveSNote(SNoteAppData_t* pThis,IBitmap *pBitmap);
static MAE_Ret _SaveThumbImg(SNoteAppData_t* pThis, MAE_WChar *pThumbImgURL ,IBitmap *pBitmap);
static MAE_Ret _LoadSwitchIcon(void *pData , IWidget*pIWidget, u32 nWdgId,u32 nActiveImgId, u32 nInactiveImgId);


MAE_Ret _SNoteAppWndCreateListView(void *pCusHandle, SNoteListWndData_t *pWdgList);
MAE_Ret _SNoteAppWndCreatePickColorView(void *pCusHandle, SNotePickColorWndData_t *pWdgList);
MAE_Ret _SNoteAppWndCreateEditNoteView(void *pCusHandle, EditWndData_t *pWdgList);
MAE_Ret _SNoteAppWndCreateNoteViewerView(void *pCusHandle, SNoteViewerWndData_t *pWdgList);
MAE_Ret _SNoteAppWndCreateInputTextView(void *pCusHandle, SNoteInputWndData_t *pWdgList);
MAE_Ret _SNoteAppWndCreateOptionMenuView(void *pCusHandle, OptionMenuWdgList_t *pWdgList, u32 nWndInitParam);





#endif //__MMI _SNOTEAPP_PRIV_H__
