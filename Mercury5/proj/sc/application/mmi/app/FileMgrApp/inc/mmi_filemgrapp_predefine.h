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
* @file    mmi_filemgrapp_predefine.h
* @version
* @brief
*
*/

#ifndef __MMI_FILEMGRAPP_PREDEFINE_H__
#define __MMI_FILEMGRAPP_PREDEFINE_H__
#include "mmi_filemgrapp_priv.h"
#include "mmi_filemgrapp_util.h"

typedef struct PredefinedDataListWndData_t_
{
    IWidget			*pIMenuWdg;
} PredefinedDataListWndData_t;

MAE_Ret FileMgrListerPredefinedDataListSetView(MmiFileMgrApp* pThis, PredefinedDataListWndData_t *pWndData);
MAE_Ret FileMgrListerPredefinedDataListPopView(MmiFileMgrApp* pThis, PredefinedDataListWndData_t *pWndData);
void FileMgrAppPredefinedDataLisMenuActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void FileMgrAppPredefinedDataLisMenuOnFocusCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);
void FileMgrListerPredefinedDataListCntDetailListAdaptGet(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
void FileMgrListerPredefinedDataListCntDetailListFreeItem(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType);


#endif //__MMI_FILEMGRAPP_PREDEFINE_H__

