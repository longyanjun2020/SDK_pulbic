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
* @file    mmi_filemgrapp_medialist.h
* @version
* @brief
*
*/

#ifndef __MMI_FILEMGRAPP_MEDIALIST_H__
#define __MMI_FILEMGRAPP_MEDIALIST_H__
/*==============================================================================
                       INCLUDE FILES FOR MODULE
==============================================================================*/
#include "mmi_filemgrapp_priv.h"

#include "mmi_filemgrapp_util.h"
#include "mmi_filemgrapp_view.h"

/*==============================================================================
                       STRUCTURE DECLARATIONS
==============================================================================*/
typedef struct MediaListMultipleSelectionWndData_t_
{
    u32                             nTitleTextId;
    MAE_WChar                       wszFolder[FILEMGR_MAX_FILEPATH_SIZE];

    IWidget                         *pIMenuWdg;

    VFS_FileID_t                    nFileId; // for single mark only

    FileMgrAppWndId_e               eWndId;
    FileMgrAppMarkTypeFromOpt_e     eMarkTypeFromOpt;

    ArrayClass_t                    *pThumbnailQueue; // in MMI_FileMgrapp_ThumbListInfo_t

#ifdef __FILEMGRAPP_ID3V2_IMG__
    boolean                         bPauseID3Img;
    ArrayClass_t                    *pID3ImgQueue;
#endif
} MediaListMultipleSelectionWndData_t;


/*==============================================================================
                       FUNCTION DECLARATIONS
==============================================================================*/
/*-------------------------------------------------------------------------*/
void FileMgrMediaListReleaseViewData(FileMgrAppMediaLstData_t *pMediaLstViewData, IBase* pOwner);
/*-------------------------------------------------------------------------*/
MAE_Ret FileMgrMediaListInitWnd(MmiFileMgrApp* pThis);

MAE_Ret FileMgrMediaListChangeDataAdapter(MmiFileMgrApp *pThis);



static boolean _FileMgrMediaListChkSeriousCMD(FileMgrAppAct_e nCmd);
void FileMgrMediaListMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void FileMgrMediaListMenuBackCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void FileMgrMediaListMenuOnFocusCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);
void FileMgrMediaListMenuSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _FileMgrMediaListDeregisterMenuCB(void *pApplet);
static MAE_Ret _FileMgrMediaListVolDlgCB (void *pApplet, MAEEvent_t nEvent, u32 param1, u32 param2);

void FileMgrAppMultiSelectionListUpdate(MmiFileMgrApp *pThis, MAE_Ret nFsRetCode);
void FileMgrMediaListFolderMultiSelectionMonitorURLCb(void *pUserData, void *pInfo);
void FileMgrMediaListFolderMultiSelectionListUpdateCb(void *pUser, void *pInfo);

MAE_Ret FileMgrAppMultipleSelectionMarkAllCB(void *pData, MAEEvent_t nEvtId, u32 param1, u32 param2);

/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
void FileMgrMediaListStorageViewAdaptGet(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
/*-------------------------------------------------------------------------*/
void FileMgrMediaListCntDetailListAdaptGet (WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
/*-------------------------------------------------------------------------*/
void FileMgrMediaListStorageViewFreeItem(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType);
/*-------------------------------------------------------------------------*/
void FileMgrMediaListCntDetailListFreeItem(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType);
/*-------------------------------------------------------------------------*/
void FileMgrMediaListReleaseTabWdgMdlItem(void *pData, IBase *pOwner);
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
MAE_Ret FileMgrMediaListSetStorageTo(MmiFileMgrApp* pThis, FileMgrAppStorageType_e nStorageId);
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
static MAE_Ret FileMgrMediaListGetItemRLSK(void                            *pUsrData,
                                                    SoftkeyID_e                     *pnRetLSKVal,
                                                    SoftkeyID_e                     *pnRetRSKVal,
                                                    MMI_Common_FMList_ItemType_e    nItemType);
/*-------------------------------------------------------------------------*/
MAE_Ret FileMgrMediaListGetItemSK(void                             *pUsrData,
                                           SoftkeyID_e                      *pnRetLSKVal,
                                           SoftkeyID_e                      *pnRetCSKVal,
                                           SoftkeyID_e                      *pnRetRSKVal,
                                           /*MMI_Common_FMList_ItemElement_t  *pItem,*/
										   MMI_Common_FMList_ItemType_e     eItemType,
                                           MMI_Common_SupportedMediaType_e  nMediaType);
/*-------------------------------------------------------------------------*/
MAE_Ret FileMgrMediaListReleaseMenuMdlData(MmiFileMgrApp  *pThis);
/*-------------------------------------------------------------------------*/
__SLDPM_FREE__ MAE_Ret FileMgrMediaListChangeTabIcon(
									  IWidget								*pTabWdg,
									  boolean								bIsExtMemPresented,
#if defined(__DUAL_CARD__)
									  boolean								bIsExtMem2Presented,
#endif
									  FileMgrAppStorageType_e   nCurFocusStorage);

MAE_Ret FileMgrMediaListChangeAbsentTabIcon(
                                        IWidget *pTabWdg,
                                        boolean bIsExtMemPresented,
#if defined(__DUAL_CARD__)
                                        boolean bIsExtMem2Presented,
#endif
                                        FileMgrAppStorageType_e nFocusAbsentStorage);

/*-------------------------------------------------------------------------*/

//4 Newly added for window archi. [begin]
static void _FileMgrMediaListMenuBackHdl(MmiFileMgrApp *pThis);
static void _FileMgrMediaListMenuOptionHdl(MmiFileMgrApp *pThis);
void FileMgrMediaListMenuSelectHdl(MmiFileMgrApp *pThis,
																	MAE_WndId nWndId,
													//#if defined(USING_NEW_SRVFILEMGR)
																	const VFS_PartialListFileInfo_t *pEfsFileInfo
													//#else
													//	   MAEFileInfo_t *pFileInfo
													//#endif
																);
void FileMgrMediaListMenuSelectFileHdl(MmiFileMgrApp *pThis,
																		MMI_Common_SupportedMediaType_e eSupportedMediaType,
															//#if defined(USING_NEW_SRVFILEMGR)
																		const VFS_PartialListFileInfo_t *pEfsFileInfo
															//#else
															//	const MAEFileInfo_t *pFileInfo
															//#endif
																		);

//#if defined(USING_NEW_SRVFILEMGR)
void FileMgrMediaListMultipleSelectionSelectHdl(void 					  *pApplet,
																		 u32 					  nMarkListHandleID,
																		 WdgDynamicMenuItemPtr_t  *pMenuItemData,
																		 HistoryInfo_t 		  	  *pHistoryInfo,
																		 IWidget 				  *pWidget,
																		 VFS_PartialListFileInfo_t 	      **ppEfsFileInfo,
																		 MAE_WChar 				  *pwszSourceURL);
//#endif
void FileMgrMediaListMenuSelectFileLaunchableHdl(MmiFileMgrApp *pThis,
																			 MMI_Common_SupportedMediaType_e eSupportedMediaType,
																		//#if defined(USING_NEW_SRVFILEMGR)
																			 const VFS_PartialListFileInfo_t *pEfsFileInfo
																		//#else
																		//	 const MAEFileInfo_t *pFileInfo
																		//#endif
																			 );
static MAE_Ret _FileMgrMediaListMenuSelectFileAudioHdl(MmiFileMgrApp *pThis,
																			//#if defined(USING_NEW_SRVFILEMGR)
																			   const VFS_PartialListFileInfo_t *pEfsFileInfo
																			//#else
																			//   const MAEFileInfo_t *pFileInfo
																			//#endif
																			   );
void FileMgrMediaListMultipleSelectionMenuOnFocusCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);

static void _FileMgrMediaListSrvAudioPlayCB(void *pApplet, MediaSrvErrCode_e eErrorCode);
static void _FileMgrMediaListSrvAudioPlayStatusNotifyCB(void *pApplet, u32 nCusData, AudioSrvPlayStatusEvent_e eEventId, u32 nInfoData);
static void _FileMgrMediaListSrvAudioPlayStopFailDlg(void *pApplet);

void FileMgrMediaListSrvAudioPlayStatusNotifyCB(void * pApplet, u32 nCusData, AudioSrvPlayStatusEvent_e eEventId, u32 nInfoData);
void FileMgrMediaListSrvAudioInterruptNotifyCB(void *pApplet, u32 nCusData, MediaSrvInterruptStatus_e nStatus);

#ifdef __FILEMGRAPP_ID3V2_IMG__
void FileMgrMediaListGetNextID3v2ImageTimer(void *pData, void *pUserData);
void FileMgrMediaListDecodeID3ImageNotifyCb(IImage* pImage, IBase* pOwner, ImgStatus_t tStatus);
#endif

//4 Newly added for window archi. [end]


// MultipleSelection - begin
/*-------------------------------------------------------------------------*/
MAE_Ret FileMgrMediaListMultipleSelection_SetView(MmiFileMgrApp * pThis, MediaListMultipleSelectionWndData_t *pMultiSelWndData);
MAE_Ret FileMgrMediaListMultipleSelection_PopView(MmiFileMgrApp * pThis, MediaListMultipleSelectionWndData_t *pMultiSelWndData);
#ifdef __FILEMGRAPP_ID3V2_IMG__
void FileMgrMultipleSelectionGetNextID3v2ImageTimer(void *pData, void *pUserData);
void FileMgrMultipleSelectionDecodeID3ImageNotifyCb(IImage* pImage, IBase* pOwner, ImgStatus_t tStatus);
#endif
// MultipleSelection - end


#endif  /* __MMI_FILEMGRAPP_MEDIALIST_H__ */
