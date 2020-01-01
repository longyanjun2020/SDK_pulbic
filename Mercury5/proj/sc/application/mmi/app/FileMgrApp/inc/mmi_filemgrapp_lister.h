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
* @file    mmi_filemgrapp_lister.h
* @version
* @brief
*
*/

#ifndef __MMI_FILEMGRAPP_LISTER_H__
#define __MMI_FILEMGRAPP_LISTER_H__
/*==============================================================================
                       INCLUDE FILES FOR MODULE
==============================================================================*/
#include "mmi_filemgrapp_priv.h"
#include "mmi_filemgrapp_util.h"

/*==============================================================================
                       STRUCTURE DECLARATIONS
==============================================================================*/
#define FILEMGRAPP_MARK_LIMIT_TITLESTR  L"%d/%d"

#define FILEMGRAPP_FOLDERQUEUE_SIZE_INIT    20
#define FILEMGRAPP_FOLDERQUEUE_SIZE_GROW    20

typedef struct ListerVirtualRootWndData_t_
{
    IWidget			*pIMenuWdg;
	u32				nPresentNum;
	u32				naPresentRefIdx[VFS_VOL_MAX];
} ListerVirtualRootWndData_t;

typedef struct ListerInitWndData_t_
{
    u32				nInitTitleId;
    boolean         bInitRecreateWindowForEmptyFolder;

} ListerInitWndData_t;

typedef struct ListerWndData_t_
{
    u32             nTitleId;
    u32             nUsedTitleId;
    IWidget         *pIMenuWdg;
    IWidget         *pTitleWdg;

    boolean         bListAnotherFolder; // File Manager Service is busy for listing another folder

    ArrayClass_t    *pThumbnailQueue;   // in MMI_Filemgrapp_ThumbListInfo_t

#ifdef __FILEMGRAPP_ID3V2_IMG__
    boolean         bPauseID3Img;
    ArrayClass_t    *pID3ImgQueue;
#endif
} ListerWndData_t;

/*==============================================================================
                       FUNCTION DECLARATIONS
==============================================================================*/

/*-------------------------------------------------------------------------*/
MAE_Ret FileMgrListerSetView(MmiFileMgrApp* pThis, ListerWndData_t *pWndData);
MAE_Ret FileMgrListerPopView(MmiFileMgrApp* pThis, ListerWndData_t *pWndData);

/*-------------------------------------------------------------------------*/
void FileMgrListerRootViewAdaptGet(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);

/*-------------------------------------------------------------------------*/
void FileMgrListerRootViewFreeItem(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType);
/*-------------------------------------------------------------------------*/
void FileMgrListerCntDetailListAdaptGet(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
/*-------------------------------------------------------------------------*/
void FileMgrListerCntDetailListFreeItem(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType);
/*-------------------------------------------------------------------------*/
void FileMgrListerThumbGridViewAdaptGet (WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
/*-------------------------------------------------------------------------*/
void FileMgrListerThumbGridViewFreeItem (WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType);
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
MAE_Ret FileMgrListerGetItemSK(void                            *pUsrData,
                                        SoftkeyID_e                     *pnRetLSKVal,
                                        SoftkeyID_e                     *pnRetCSKVal,
                                        SoftkeyID_e                     *pnRetRSKVal,
                                        MMI_Common_FMList_ItemType_e    eItemType,
                                        MMI_Common_SupportedMediaType_e nMediaType);
/*-------------------------------------------------------------------------*/
MAE_Ret FileMgrAppSinglePickGetItemSK(void *pUsrData,
                                                SoftkeyID_e *pnRetLSKVal,
                                                SoftkeyID_e *pnRetCSKVal,
                                                SoftkeyID_e *pnRetRSKVal,
                                                MMI_Common_FMList_ItemType_e eItemType,
                                                MMI_Common_SupportedMediaType_e nMediaType);
/*-------------------------------------------------------------------------*/
static MAE_Ret FileMgrListerGetItemRLSK(void                           *pUsrData,
                                                 SoftkeyID_e                    *pnRetLSKVal,
                                                 SoftkeyID_e                    *pnRetRSKVal,
                                                 MMI_Common_FMList_ItemType_e   nItemType);
/*--------------------------------------------------------------------------*/
MAE_WChar* FileMgrAppMultiPickGenSelectLimitStr(u16   nPickCount,
                                                      u16   nCountLimit);
/*-------------------------------------------------------------------------*/
MAE_Ret FileMgrAppMultiPickGetItemSK(void                             *pUsrData,
												const VFS_PartialListFileInfo_t			 *pEfsFileInfo,
				                                SoftkeyID_e                      *pnRetLSKVal,
												SoftkeyID_e                      *pnRetCSKVal,
												SoftkeyID_e                      *pnRetRSKVal,
												MMI_Common_FMList_ItemType_e    eItemType,
												boolean                          *pIsSelected);

/*-------------------------------------------------------------------------*/
MAE_Ret FileMgrListerVirtualRootSetView(MmiFileMgrApp* pThis, ListerVirtualRootWndData_t *pWndData);
MAE_Ret FileMgrListerVirtualRootPopView(MmiFileMgrApp* pThis, ListerVirtualRootWndData_t *pWndData);
void FileMgrListerVirtualRootThumbGridViewAdaptGet (WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
void FileMgrListerVirtualRootThumbGridViewFreeItem(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType);
void FileMgrListerVirtualRootViewAdaptGet(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
void FileMgrListerVirtualRootViewFreeItem(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType);
void FileMgrMediaListMultipleSelectionListAdaptGet(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
void FileMgrMediaListMultipleSelectionListFreeItem(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType);

void FileMgrListerSelectHdl(void 					  		*pApplet,
								  		  		 u32 					  		nMarkListHandleID,
								  		  		 const WdgDynamicMenuItemPtr_t  *pMenuItemData,
								  		  		 HistoryInfo_t 		  	  		*pHistoryInfo,
								  		  		 IWidget 						*pMenuWdg,
								  		  		 VFS_PartialListFileInfo_t 	  	  		**ppEfsFileInfo,
								  		  		 const u32						nLimitCnt,
								  		  		 IWidget 						*pTitleWdg);

void FileMgrListerSelectFileAudioHdl(MmiFileMgrApp   *pThis,
                                                 ListerWndData_t    *pWndData,
                                                 const VFS_PartialListFileInfo_t *pEfsFileInfo);

MAE_Ret FileMgrAppMultiPickLoadOptMenuMdl(MmiFileMgrApp* pThis, FileMgrOptMenuWndData_t *pOptWndData);

s32 FileMgrAppMultiPickMarkAllCompFunc(void *pBase, void *pInfo);

MAE_Ret FileMgrAppMultiPickRefreshMenu(
    FileMgrHandleID_t       nMarkedHandleID,
    u32                     nMarkedLimit,
    IWidget 				*pMenuWdg,
    IWidget                 *pTitleWdg,
    boolean                 bForMarkAllAct);

#ifdef __FILEMGRAPP_ID3V2_IMG__
void FileMgrListerGetNextID3v2ImageTimer(void *pData, void *pUserData);
void FileMgrListerDecodeID3ImageNotifyCb(IImage* pImage, IBase* pOwner, ImgStatus_t tStatus);
#endif

#endif /* __MMI_FILEMGRAPP_LISTER_H__ */
