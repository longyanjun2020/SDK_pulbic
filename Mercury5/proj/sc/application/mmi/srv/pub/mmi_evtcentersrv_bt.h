/*************************************************************
 *
 * Copyright (c) 2006-2011 MStar Semiconductor, Inc.
 * All rights reserved.
 *
 * Unless otherwise stipulated in writing, any and all information contained
 * herein regardless in any format shall remain the sole proprietary of
 * MStar Semiconductor Inc. and be kept in strict confidence
 * (¡§MStar Confidential Information¡¨) by the recipient.
 * Any unauthorized act including without limitation unauthorized disclosure,
 * copying, use, reproduction, sale, distribution, modification, disassembling,
 * reverse engineering and compiling of the contents of MStar Confidential
 * Information is unlawful and strictly prohibited. MStar hereby reserves the
 * rights to any and all damages, losses, costs and expenses resulting therefrom.
 *
 *************************************************************/
/**
* @file mmi_evtcentersrv_bt.h
* @author Michael Liao
* @history 7/13/2011 added for New Feature #437
*
*/
#ifndef __MMI_EVTCENTERSRV_BT_H__
#define __MMI_EVTCENTERSRV_BT_H__
#include "mmi_evtcentersrv_priv.h"
#include "mmi_wdg_itf_staticmenu.h" //for definition of WdgStaticMenuItem_t
#include "mmi_launcher_filemanager.h" //for LaunchAppToListDir()


#ifdef __BLUETOOTH_OBEX_MMI__


/* */
typedef struct
{
    const WdgStaticMenuItem_t           *sMenuItemList;
    const u32                           nMenuItemListSize;
    MMI_Common_SupportedMediaType_e     eMediaType;
} BtMediaTypeOptMenuMapping_t;


/* */
#ifdef __BLUETOOTH_MMI__
MAE_Ret     _EVTCENTERSRV_HandleBTStatusDialogEvent(MMI_EVTCENTERSRV *pThis, EVTCenter_Log_Item_t *pLogItem, u32 nEvtCode);
#endif


/* */
#ifdef __BLUETOOTH_MMI__
void        _EVTCENTERSRV_ListBTRecvFiles(MMI_EVTCENTERSRV *pThis);
#endif


/*  */
#ifdef __BLUETOOTH_MMI__
void        _EVTCENTERSRV_SetBTCurrentRecvFolder(MMI_EVTCENTERSRV *pThis);
#endif


/* */
void        _EVTCENTERSRV_ShowBTStatusDialog(MMI_EVTCENTERSRV *pThis);


/* */
void        _EVTCENTERSRV_SortCB(void *pUserData, PfnFileMgrSortCompareCb *pfnConpareFunction);
void        _EVTCENTERSRV_LaunchFileMgrGetOptionMenuCb(void *pUserData, u32 nFolderLevel, void *pFileInfo, u32 *pOptonMeneuItemNum, const WdgStaticMenuItem_t **pOptionMeneuItemList, PfnFileMgrOptMenuSelectCb *pfnSelectCb);
s32         _EVTCENTERSRV_FileListSortingComparatorByDate(void *pBase, void* pRef);


/* */
u16         _EVTCENTERSRV_GetBTRecvNum(MMI_EVTCENTERSRV *pThis);
void        _EVTCENTERSRV_ResetBTRecvNum(MMI_EVTCENTERSRV *pThis);
void        _EVTCENTERSRV_IncrementBTRecvNum(MMI_EVTCENTERSRV *pThis);


/* */
void        _EVTCENTERSRV_SetBTRecvDirStatus(MMI_EVTCENTERSRV *pThis, boolean bIsChanged);
void        _EVTCENTERSRV_ResetBTRecvDirStatus(MMI_EVTCENTERSRV *pThis);
boolean     _EVTCENTERSRV_IsBTRecvDirChanged(MMI_EVTCENTERSRV *pThis);


/* */
MAE_WChar*  _EVTCENTERSRV_GetBTCurrentRecvFolder(MMI_EVTCENTERSRV *pThis);
void        _EVTCENTERSRV_ResetBTCurrentRecvFolder(MMI_EVTCENTERSRV *pThis);


/* */
u16         _EVTCENTERSRV_GetBTRecvNumInLatestDir(MMI_EVTCENTERSRV *pThis);
void        _EVTCENTERSRV_ResetBTRecvNumInLatestDir(MMI_EVTCENTERSRV *pThis);
void        _EVTCENTERSRV_IncrementBTRecvNumInLatestDir(MMI_EVTCENTERSRV *pThis);


/* */
#if 0
void        _EVTCENTERSRV_LaunchBtStatusDialog(IBase* pUser, u32 Param);
#endif


#endif //#ifdef __BLUETOOTH_OBEX_MMI__
#endif /* __MMI_EVTCENTERSRV_BT_H__ */

