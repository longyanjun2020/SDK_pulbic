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
* @file    mmi_searchapp_priv.h
* @version
* @brief   searchapp applet private header file
*
*/

#ifndef __MMI_SEARCHAPP_PRIV_H__
#define __MMI_SEARCHAPP_PRIV_H__

#if defined(__MMI_SEARCH_APP__)
/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_base_util.h"
#include "mmi_layout.h"
#include "mmi_searchapp.h"
#include "mmi_searchapp_id.h"
#include "mmi_searchapp_rs.h"
#include "mmi_log.h"
#include "SearchApp_resource.h"
#include "mmi_launcher_common.h"

//service
#include "mmi_srv_client_commondefine.h"
#include "mmi_phbsrv_utility.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/ 
#define SEARCH_CHAR_NAME_LEN 40
#define SEARCH_PARSER_CONTENT_PERIOD 1
/*=============================================================*/
// Data type definition
/*=============================================================*/


/**
 * Application structure
 */
enum
{
	SEARCHAPP_STORAGE_PHONE = 0,
	SEARCHAPP_STORAGE_CARD,
	SEARCHAPP_STORAGE_CARD2,
	SEARCHAPP_STORAGE_NUMBER,
};
typedef u8 MMI_SearchApp_Storage_e;

typedef struct SearchResultData_t_
{
	u16 uContact;
	u16 uImage;
	u16 uMusic;
	u16 uVideo;
	u16 uEbook;
	u16 uEvent;
	u16 uCataNum;
} SearchResultData_t;


typedef struct
{
    u32			nSrvFileMgrSearchListHandle[SEARCHAPP_STORAGE_NUMBER];
    u32			nSearchedFileNumber[SEARCHAPP_STORAGE_NUMBER];
	MMI_SearchApp_Storage_e eCurSearchFolderStorage;
    boolean     bFinishSearch;
} SearchFileInfo_t;

typedef struct
{
	APPLET_BASE_ELEMENTS;
	MenuItemStatus_e eMenuStatus;
	MenuItemStatus_e eMenuCusStatus;
	SearchResultData_t tMenuResult;
	WidgetHandler_t         tMenuWidgetHandler;
	WidgetHandler_t         tContentMenuWidgetHandler;
	WidgetHandler_t         tInputWidgetHandler;

	MAE_WChar               au16SearchText[SEARCH_CHAR_NAME_LEN+1];    /*The input text before text changed*/
	MAE_WChar               wCurrentFolder[FILEMGR_MAX_FILEPATH_SIZE];
	//phb search para.s
	MmiPhbSearchResult_t    *patSearchResult;   /*The all serching result contact's informations*/
	u8 	uCurUpdateIndex;

	//event search para.s
	ArrayClass_t *pEventArray;

	//Search File Info structure.
	SearchFileInfo_t tSearchContactFileInfo;
	SearchFileInfo_t tSearchImageFileInfo;
	SearchFileInfo_t tSearchVideoFileInfo;
	SearchFileInfo_t tSearchMusicFileInfo;
	SearchFileInfo_t tSearchEbookFileInfo;
#ifdef __SEARCHAPP_SEARCH_CALENDAR_MMI__
	SearchFileInfo_t tSearchEventFileInfo;
#endif // End of __SEARCHAPP_SEARCH_CALENDAR_MMI__
	boolean bDeviceExtCardStatus;
	boolean bDeviceExtCardStatus2;
	boolean bDoReParserSearch;
	boolean bMusicPlaying;
	boolean bUsePhbSortingTable;
	TextInfo tLastInputTexInfo;
	u32		u32HistoryFocusIndex;

	u16 MainMenuItemList[SEARCH_MENUITEM_MAX];

#ifdef __MMI_OMA_DRM_V1__
	MAE_WChar *strDrmFileURL;
#endif 
} SearchAppData_t;


typedef struct
{
    IWidget *pPropContainer;
    IWidget *pMainMenuWidget;
    IWidget *pItemMenuWidget;
    IWidget *pSearchAbsContainer;
    IWidget *pSearchBGImageWidget;
    IWidget *pSearchIconImageWidget;
	IWidget *pSearchLoadingImageWidget;
    IWidget *pSearchInputWidget; 
} SearchAppWdgList_t;

typedef struct
{
    SearchAppWdgList_t tWdgList;
} SearchAppWndData_t;


/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret SearchConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret SearchDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean SearchStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean SearchKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean SearchTSEventCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);

boolean SearchResumeCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean SearchSuspendCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);

MAE_Ret SearchAppWndHdlMain(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SearchAppWndHdlMainCreate(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret _SearchAppWndHdlMainDestroy(void* pCusHandle,void* pWndData, u32 nWndInitParam);

#ifdef __MMI_OMA_DRM_V1__
static MAE_Ret SearchAppDrmConfirmDialogCb(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
static void SearchAppLaunchCdWapDownloadDrmRightsFileCb(void *pvUserData, MAE_Ret nRspCode, void *pvRspData, CmnRspDataFreeCb pfnRspFreeCb);
#endif //__MMI_OMA_DRM_V1__

#endif //__MMI_SEARCH_APP__
#endif /* __MMI_MGLDEMOAPP_PRIV_H__ */
