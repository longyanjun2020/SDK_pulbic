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
* @file    mmi_notepadapp_priv.h
* @version
* @brief   Notepad applet private header file
*
*/

#ifndef __MMI_NOTEPADAPP_PRIV_H__
#define __MMI_NOTEPADAPP_PRIV_H__
#define __NOTEPADAPP_RAI__

#include "mmi_baseapplet.h"
#include "mmi_notepadapp.h"
#include "mmi_common_dialog_id.h"
#include "mmi_common_rai_id.h"
#include "mmi_util_rtc.h"
#include "mmi_util_fs.h"
#include "mmi_common_vtm.h"
#include "mmi_notepadapp_id.h"
#include "notepadapp_resource.h"


/* The data structure is used for storing the variables of the note list view. */
typedef struct
{
    IWidget     *pIMenuWdg;
} NotepadNoteListView_t;

typedef struct
{
    IWidget     *pIOptionMenuWidget;
} NotepadLoadOptionMenuView_t;


/* The data structure is used for storing the variables of the edit note view. */
typedef struct
{
    IWidget         *pIInputWidget;
    bool            bIsSaving;
    boolean			bIsResumeStopping;
	boolean			bIsNeedStopInteractive;
} NotepadEditNoteView_t;

typedef struct
{
    IWidget     *pIOptionMenuWidget;
} NotepadEditNoteLoadOptionMenuView_t;

/* The data structure is used for storing the variables of the view note view. */
typedef struct
{
    IWidget         *pIInputWidget;
} NotepadViewNoteView_t;

// NotepadApp \ This variable defines the maximum number of characters for each note record.
#define MMI_NOTEPAD_MAX_NOTE_LEN 250

// NotepadApp \ This variable defines the maximum number of characters for each title length in list view.
#define MMI_NOTEPAD_MAX_TITLE_LEN 20

#define MMI_NOTEPAD_MAX_EMPTY_STR       10
#define MMI_NOTEPAD_MAX_FILE_NAME_LEN   40

#define MMI_NOTEPAD_IDX_NO_DATA         255
#ifndef __NOTEPADAPP_RAI__
#define MMI_NOTEPAD_LEAST_MEMORY        6
#define MMI_NOTEPAD_NOTEFILE_MEMORY     1
#else
#define MMI_NOTEPAD_LEAST_MEMORY        6*1024
#define MMI_NOTEPAD_NOTEFILE_MEMORY     1024
#endif

#define MMI_NOTEPAD_SECONDS_PER_DAY     (24*60*60)
#define MMI_NOTEPAD_DELETEALL_TIMER     2

#define PHONE_FULLPATH  L"fs:/PHON/"
#define SD_FULLPATH     L"fs:/CARD/"

#ifndef __NOTEPADAPP_RAI__
#define MMI_NOTEPAD_FILE_PATH               L"fs:/PHON/NOTEPAD/"
#define MMI_NOTEPAD_IDXTBL_FILE_NAME        L"NotepadTable.dat"
#define MMI_NOTEPAD_IDXTBL_FILEPATH_NAME    MMI_NOTEPAD_FILE_PATH MMI_NOTEPAD_IDXTBL_FILE_NAME
#define MMI_NOTEPAD_PHYSICAL_FILE_NAME      L"Note0"
#define MMI_NOTEPAD_PHYSICAL_FILEPATH_NAME  MMI_NOTEPAD_FILE_PATH MMI_NOTEPAD_PHYSICAL_FILE_NAME
#endif

typedef struct
{
	u32				u32EditTime;
	u16				u16NoteSize;
	u16				u16Align;
	MAE_WChar		au16Title[MMI_NOTEPAD_MAX_TITLE_LEN];
} Mmi_NotepadNotePartial_t;

typedef struct
{
	u8                          au8SortTbl[MMI_NOTEPAD_MAX_NOTE];
	u16							u16NoteNumber;
	u16							u16Align;
	Mmi_NotepadNotePartial_t    atNotePartial[MMI_NOTEPAD_MAX_NOTE];
} Mmi_NotepadIdxTblBuf_t;

typedef struct Mmi_Notepad_ListItemData_TAG
{
	MAE_WChar         *u16Text1;
	MAE_WChar         *u16Text2;

} Mmi_Notepad_ListItemData_t;

#define MMI_NOTEPAD_IDXTBL_FILE_SIZE sizeof(Mmi_NotepadIdxTblBuf_t)

typedef struct
{
    APPLET_BASE_ELEMENTS;
	Mmi_NotepadIdxTblBuf_t				*pIdxTblBuf;
	boolean								bIsEditNote;
    boolean								bIsExit;
	boolean								bIsDeleteALL;
	boolean								bNeedConfig;
	u8									u8SelectedNoteIdx;
} NotepadAppData_t;


/*=============================================================*/
// Local function definition
/*=============================================================*/
void NotepadWndMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void NotepadWndMenuOnFocusCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pReserve);

MAE_Ret _NotepadNoteListWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _NotepadNoteListWndConvert(void *pCusHandle, void *pWndData);

MAE_Ret _NotepadEditNoteWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _NotepadEditNoteWndDestroy(void *pCusHandle, void *pWndData);

MAE_Ret _NotepadViewNoteWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);

MAE_Ret _NotepadLoadOptionMenuWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _NotepadLoadOptionMenuWndConvert(void *pCusHandle, void *pWndData);
MAE_Ret _NotepadLoadOptionMenuWndDestroy(void *pCusHandle, void *pWndData);

MAE_Ret _NotepadEditNoteLoadOptionMenuWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _NotepadEditNoteLoadOptionMenuWndConvert(void *pCusHandle, void *pWndData);
MAE_Ret _NotepadEditNoteLoadOptionMenuWndDestroy(void *pCusHandle, void *pWndData);

/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret NotepadConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret NotepadDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean NotepadStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean NotepadKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean NotepadSuspendCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean NotepadResumeCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean NotepadTsClickCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

//void NotepadAccessoryPlugStatusCB(void *pUserData, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);

MAE_Ret NotepadNoteListWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret NotepadEditNoteWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret NotepadViewNoteWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret NotepadLoadOptionMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret NotepadEditNoteLoadOptionMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static void _NotepadOptionMenuSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _NotepadOptionMenuLayer2SelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _NotepadTextInputOptionMenuSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _NotepadCheckIfSave(NotepadAppData_t *pThis);

static MAE_Ret _NotepadCheckFileDir(NotepadAppData_t *pThis);
static MAE_Ret _NotepadInitFile(NotepadAppData_t *pThis);
static MAE_Ret _NotepadReadIdxTblFile(NotepadAppData_t *pThis, Mmi_NotepadIdxTblBuf_t *ptFileBuf);
static MAE_Ret _NotepadWriteIdxTblFile(NotepadAppData_t *pThis, const Mmi_NotepadIdxTblBuf_t *ptFileBuf);
static MAE_Ret _NotepadReadNoteFile(NotepadAppData_t *pThis, MAE_WChar *pu16NoteBuf, u8 u8Idx, u16 u16Size);
static MAE_Ret _NotepadWriteNoteFile(NotepadAppData_t *pThis, MAE_WChar *pu16NoteBuf, u8 u8Idx, u16 u16Size);
static MAE_Ret _NotepadDeleteNoteFile(NotepadAppData_t *pThis, u8 u8Idx);

#ifndef __NOTEPADAPP_RAI__
static MAE_Ret _NotepadIdxToFilePathName(MAE_WChar *pFilePathName, u8 u8Idx);
#endif

static MAE_Ret _NotepadReadNoteBySelectedId(NotepadAppData_t *pThis, MAE_WChar **ppu16NoteBuf);
static MAE_Ret _NotepadSetTitleSMSStr(NotepadAppData_t *pThis, u16 u16Count);
void NotepadInputTextChangeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
void NotepadAddNote(void *pApplet);
void NotepadSaveNote(void *pApplet);
static void _NotepadDeleteAllStart(void *pThis);
MAE_Ret NotepadDialogTimeOutCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
MAE_Ret NotepadCheckIfSaveConfirmDialogCb(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret NotepadDeleteConfirmDialogCb(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
static MAE_Ret _NotepadDeleteNote(NotepadAppData_t *pThis);
static MAE_Ret _NotepadDeleteAllNote(NotepadAppData_t *pThis);

#endif /* __MMI_NOTEPADAPP_PRIV_H__ */
