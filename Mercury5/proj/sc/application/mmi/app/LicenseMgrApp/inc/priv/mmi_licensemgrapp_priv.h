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
* @file    mmi_licensemgrapp_priv.h
* @version
* @brief   License Mgr applet private header file
*
*/
#ifndef __MMI_LICENSEMGRAPP_PRIV_H__
#define __MMI_LICENSEMGRAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_common_vtm.h"
#include "mmi_licensemgrapp_id.h"
#include "licensemgrapp_resource.h"
#include "mmi_base_util.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define RIGHT_DISPLAY_LEN_INCREMENT 512

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    MMI_LICENSEMGR_ACTION_NONE = 0,
    MMI_LICENSEMGR_ACTION_VIEW,
    MMI_LICENSEMGR_ACTION_DELETE, 
    MMI_LICENSEMGR_ACTION_DELETEALL, 
    MMI_LICENSEMGR_ACTION_SWEEP
} MMI_LICENSEMGR_ACTION_e;

typedef struct
{
    APPLET_BASE_ELEMENTS;
    ArrayClass_t *pRightsUIDList;
    u32 nFocusIndex;
    MMI_LICENSEMGR_ACTION_e eLastAction;
    u32 nTotalNum;
} LicenseMgrAppData_t;

typedef struct
{
    IWidget         *pITitleWdg;

}LicenseMgrWdgList_t;

typedef struct
{
    IWidget *pMenu;

}LicenseMgrMainWndData_t;

typedef struct
{
    IWidget *pMenu;

}LicenseMgrOptionWndData_t;

typedef struct
{
    IWidget *pTitleWdg;
    IWidget *pScrollWdg;    
    IWidget *pInputWdg;
}LicenseMgrDetailWndData_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret LicenseMgrMainWndHdl
(
    void                *pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void                *pWndData,
    u32                 nWndInitParam
);

MAE_Ret LicenseMgrOptionWndHdl
(
    void                *pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void                *pWndData,
    u32                 nWndInitParam
);

MAE_Ret LicenseMgrDetailWndHdl
(
 void                *pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void                *pWndData,
 u32                 nWndInitParam
 );

static void _LicenseMgrAppMainMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

#endif /* __MMI_LICENSEMGRAPP_PRIV_H__ */

