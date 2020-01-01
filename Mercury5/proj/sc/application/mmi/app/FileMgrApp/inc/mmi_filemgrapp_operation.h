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
* @file    mmi_filemgrapp_objop.h
* @version
* @brief
*
*/

#ifndef __MMI_FILEMGRAPP_OPERATION_H__
#define __MMI_FILEMGRAPP_OPERATION_H__
/*==============================================================================
INCLUDE FILES FOR MODULE
==============================================================================*/
#include "mmi_filemgrapp_util.h"
#include "mmi_filemgrapp_priv.h"

/*==============================================================================
STRUCTURE DECLARATIONS
==============================================================================*/
#ifdef __MMI_OMA_DRM_V1__
#define MMI_FILEMGRAPP_DRM_PROC_TIMER          (5)
#define MMI_FILEMGRAPP_DRM_PROC_BATCH_COUNT    (15)
#endif

typedef struct SortByWndData_t_
{
    IWidget			*pIMenuWdg;
} SortByWndData_t;

/*==============================================================================
FUNCTION DECLARATIONS
==============================================================================*/


/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
//3 Newly added [begin]----------------------
void FileMgrAppOpCpMvReleaseCpMvData(FileMgrApp_CpMvData_t **ppCpMvObjData, IBase *pOwner);
MAE_Ret FileMgrAppOpCpMvInitData(IBase *pOwner, const MAE_WChar *pwszDestFolderPath);
MAE_Ret MMI_FileMgrappObjCpMvShowUI(IBase *pOwner, const MAE_WChar *pwszDestFolderPath);

void FileMgrAppOpCpMvDestFolderViewAdaptGet(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
void FileMgrAppOpCpMvDestFolderViewFreeItem(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType);


void FileMgrAppOpCpMvMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void FileMgrAppOpCpMvMenuBackCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void FileMgrAppOpCpMvMenuOnFocusCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);
void FileMgrAppOpCpMvMenuSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);


void FileMgrAppSortByMenuActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

MAE_Ret FileMgrAppOpCpMvStartCpMv(void *pApplet, WidgetEvtCode_t nEvtCode, MAE_WChar *pwszDestFolder, IWidget *pWidget);
static MAE_Ret _FileMgrAppOpCpMvCreateProcessDialog(u32 nEvtCode, void *pApplet);

void FileMgrAppOpCpMvMarkedCpUpdateCb(void *pUser, void *pInfo);
void FileMgrAppOpCpMvMarkedMvUpdateCb(void *pUser, void *pInfo);
void FileMgrAppOpCpMvMarkedDeleteUpdateCb(void *pUser, void *pInfo);
void FileMgrAppOpCpMvDeleteAllUpdateCb(void *pUser, void *pInfo);
void FileMgrAppOpRmDirUpdateCb(void *pUser, void *pInfo);

MAE_Ret FileMgrAppCPMVOKLoadDlgCB(void *pData, MAEEvent_t nEvtId, u32 param1, u32 param2);
MAE_Ret FileMgrAppDelOKLoadDlgCB(void *pData, MAEEvent_t nEvtId, u32 param1, u32 param2);
MAE_Ret FileMgrAppDelAllOKLoadDlgCB(void *pData, MAEEvent_t nEvtId, u32 param1, u32 param2);

MAE_Ret FileMgrAppOpCpMvProcessDialogHdl(void *pUser, MAEEvent_t nEvtCode, u32 param1, u32 param2);
MAE_Ret FileMgrAppOpCpMvDelWaitingDialogHdl(void *pUser, MAEEvent_t nEvtCode, u32 param1, u32 param2);



MAE_Ret FileMgrAppDelObjLoadDelCfmDlg(IBase *pOwner, FileMgrAppDeleteTypeFromOpt_e  eDelType, FileMgrAppOpOP_e eObjOp);
static boolean _FileMgrAppDelObjConfirmDlgCB(void * pApplet,u32 nEvt,u32 nParam1,u32 nParam2);
static MAE_Ret _FileMgrAppDelObjStartDeleting(IApplet *pApplet);

void FileMgrAppOpCpMvFolderMonitorURLCb(void *pUserData, void *pInfo);
void FileMgrAppOpCpMvFolderListUpdateCb(void * pUser,void * pInfo);
void FileMgrAppReleaseDelObjData(IBase *pOwner);



//---------------------
void FileMgrAppSetAsReleaseSetAsData(FileMgrApp_SetAsData_t **ppSetAsData, IBase *pOwner);
MAE_Ret FileMgrAppSetAsUpdateSetting(IApplet *pApplet, u32 nMenuID, MAE_WChar const *pCurrentFolder, VFS_PartialListFileInfo_t *pEfsFileInfo);
#ifdef __USER_DEFINE_POWERONOFF_VIDEO__
MAE_Ret FileMgrCmnVideoSetAsPowerOnOffConfirmDlgCb(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
#endif
#if defined(__USER_DEFINE_MAINMENU_VIDEO__) && defined(__UI_STYLE_MMI_MAIN_MENU_ANIMATION__)
MAE_Ret FileMgrCmnVideoSetAsMainmenuDisplayConfirmDlgCb(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
#endif
#if defined(__VIDEO_WALLPAPER__) && defined(__SCREEN_EFFECTS_SUPPORT__)
MAE_Ret FileMgrCmnVideoSetAsWallpaperConfirmDlgCb(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
#endif
#if defined(__USER_DEFINE_POWERONOFF_VIDEO__) || defined(__USER_DEFINE_MAINMENU_VIDEO__) || defined(__VIDEO_WALLPAPER__)
MAE_Ret FileMgrAppSetAsCreateAndSaveSetAsData(FileMgrApp_SetAsData_t **ppSetAsData, u32 nSetMenuId, FileManagerFileInfo_t *pFileInfo);
#endif
// Sort by - begin
/*-------------------------------------------------------------------------*/
MAE_Ret FileMgrAppSortBySetView(MmiFileMgrApp * pThis, SortByWndData_t *pSortByWndData);
MAE_Ret FileMgrAppSortByPopView(MmiFileMgrApp * pThis, SortByWndData_t *pSortByWndData);
// Sort by - end

// Send - begin
/*-------------------------------------------------------------------------*/
#ifdef __MMI_OMA_DRM_V1__
void FileMgrAppOpDrmCheckMarklistTimerCb(void *pUser);
void FileMgrAppOpDrmFilterMarklistTimerCb(void *pUser);
MAE_Ret FileMgrAppOpDrmCheckMarklistUsageWaitingDlgCb(void *pData, MAEEvent_t nEvtId, u32 param1, u32 param2);
MAE_Ret FileMgrAppOpDrmFilterMarklistUsageWaitingDlgCb(void *pData, MAEEvent_t nEvtId, u32 param1, u32 param2);
MAE_Ret FileMgrAppOpDrmStartCheckMarkListCanBeUsed(MmiFileMgrApp *pThis, FileMgrApp_MultiSelData_t *pMultiSelData, DRM_UsageType_e eUsageType);
MAE_Ret FileMgrAppOpDrmStartFilterProtectedFilesInMarklist(MmiFileMgrApp *pThis, FileMgrApp_MultiSelData_t *pMultiSelData, DRM_UsageType_e eUsageType);
#endif
// Send - end

//3 Newly added [end] ---------------------
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
#endif /* __MMI_FILEMGRAPP_OPERATION_H__ */
