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
* @file    mmi_networkcounterapp_priv.h
* @version
* @brief   NetworkCounter applet private header file
*
*/

#ifndef __MMI_NETWORKCOUNTERAPP_PRIV_H__
#define __MMI_NETWORKCOUNTERAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_networkcounterapp.h"
#include "mmi_networkcounterapp_id.h"

#include "mmi_common_vtm.h"
#include "mmi_common_dialog.h"
#include "mmi_srv_header.h"

#include "networkcounterapp_resource.h"


/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef u32 MenuItemID_e;

typedef struct
{
    IWidget         *pIMenuWdg;
} NetworkCounterAppMenuList_t;

typedef struct
{
    APPLET_BASE_ELEMENTS;
    u32 nCounterListMenuId;
    u32 nCountItemMenuId;    
    u8 nCurrDualId;
} NetworkCounterAppData_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/
void NetworkCounterShowCountConfirmDialog(NetworkCounterAppData_t *pThis, u32 nCountVale);
void NetworkCounterShowDialog(NetworkCounterAppData_t *pThis, u32 nTextId);

MAE_Ret NetworkCounterAppConstructorCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret NetworkCounterAppDestructorCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean NetworkCounterAppStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

MAE_Ret NetworkCounterWndCounterListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret NetworkCounterWndCreateCounterList(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret NetworkCounterWndDestroyCounterList(void *pCusHandle, void *pWndData);

MAE_Ret NetworkCounterWndDualSimHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret NetworkCounterWndCreateDualSim(void *pCusHandle, void *pWndData, u32 nWndInitParam);

MAE_Ret NetworkCounterWndCounterHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret NetworkCounterWndCreateCounter(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret NetworkCounterWndDestroyCounter(void *pCusHandle, void *pWndData);


#endif /* __MMI_NETWORKCOUNTERAPP_PRIV_H__ */
