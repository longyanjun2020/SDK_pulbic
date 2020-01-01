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
* @file    mmi_networkapp_util.h
* @version
* @brief   Network setting applet utility header file
*
*/

#ifndef __MMI_NETWORKAPP_UTIL_H__
#define __MMI_NETWORKAPP_UTIL_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_networkapp_priv.h"
/*=============================================================*/
// Extern definition
/*=============================================================*/
#define NETWORKAPP_DONE_TIMER   1000

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret _NetworkSetMenuItemLine2Data(IWidget *pMenuWidget, u32 u32MenuItemID, u32 u32TextID);
u32 _NetworkGetTextIdByMenuId(u32 u32MenuItemID);
MAE_Ret _NetworkDrawWaitingScreen(NetworkAppData_t* pThis, u32 ActionTextID, SoftkeyID_e rightSK, SoftkeyID_e leftSK, SoftkeyID_e middleSK);
MAE_Ret _NetworkDrawDoneScreen(NetworkAppData_t* pThis, u8 DialogViewID, MAE_WChar* pTitleStr);
MMI_MMSRV_Band_e _NetworkGetBandId(MenuItemID_e eMIID);
MMI_MMSRV_Line_Service_e _NetworkGetLineId(MenuItemID_e eMIID);
#ifdef __GPRS_MMI__
MMI_MMSRV_GPRS_Reg_e _NetworkGetGprsRegAction(MenuItemID_e eMIID);
MMI_MMSRV_NetAccess_Mode_e _NetworkGetAccessModeByMenuId(MenuItemID_e eMIID);
u32 _NetworkGetMenuIdByNetAccessEnum(MMI_MMSRV_NetAccess_Mode_e eNetAccess);
#endif //__GPRS_MMI__
u32 _NetworkGetMenuIDByNetSelectionEnum(MMI_MMSRV_RegMode_e eRegMode);
u32 _NetworkGetMenuIdByBandEnum(MMI_MMSRV_Band_e eBandID);
u32 _NetworkGetMenuIdByLineEnum(MMI_MMSRV_Line_Service_e eLineID);
void _NetworkPLMNListAdapterGetItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);
void _NetworkPreferPLMNListAdapterGetItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);
void _NetworkPLMNListItemFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
u32 _NetworkGetPreferPlmnMenuId(u8 index);
MAE_Ret NetworkWaitingDlgCb(void* data, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret NETWORKAPP_ShowInfoDlgCB(void* data, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_WChar* _NetworkGetErrorCause(u16 errorCode);
boolean _NetworkIsMNC3Digits( u16 nMCC, u16 nMNC );
#endif /* __MMI_NETWORKAPP_UTIL_H__ */
