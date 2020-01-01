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
* @file mmi_callerlocationapp_priv.h
*
* Class Id: CLSID_CALLERLOCATIONAPP
*
* @version $Id$
*/
#ifndef __MMI_CALLERLOCATIONAPP_PRIV_H__
#define __MMI_CALLERLOCATIONAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_callerlocationapp.h"
#include "mmi_baseapplet.h"

#include "mmi_common_dialog.h"
#include "mmi_common_vtm.h"
#include "mmi_mae_file_util.h"
#include "mmi_callerlocationapp_id.h"
#include "callerlocationapp_resource.h"

/*=============================================================*/
// Data type definition
/*=============================================================*/
#define CALLERLOCATIONAPP_MAINMENUSIZE 4
#define CALLERLOCATIONAPP_TEMP_FILENAME (L"cldb.tmp")

typedef struct{
    IWidget         *pInputLableWdg;
    IWidget         *pInputWdg;
    IWidget         *pResultLableWdg;
    IWidget         *pResultWdg;
} CallerLocationQueryWdgList_t;

typedef struct
{
    APPLET_BASE_ELEMENTS;

    MAE_WChar        *pwDownloadedCldbURL;        // Local URL of Cldb file for update
    boolean          bIsNeedMoveFile;  // TRUE if download db file by wap is successed

} CallerLocationAppData_t;


/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret CallerLocationAppConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret CallerLocationAppDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CallerLocationAppStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CallerLocationAppResumeCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CallerLocationAppKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

/*=============================================================*/
// Local function definition
/*=============================================================*/
/* MainMenu */
MAE_Ret _CallerLocationAppWndMainHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallerLocationAppWndCreateMain(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallerLocationAppWndDestroyMain(void *pCusHandle, void *pWndData);
MAE_Ret _CallerLocationAppWndShowMain(void *pCusHandle, void *pWndData);
void _CallerLocationAppMainSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

/* Query */
MAE_Ret _CallerLocationAppWndQueryHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallerLocationAppWndCreateQuery(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallerLocationAppSetQueryWnd(void  *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallerLocationAppWndDestroyQuery(void *pCusHandle, void *pWndData);
boolean _CallerLocationAppQueryKeyPressCb(CallerLocationAppData_t* pThis, u32 nEvt, u32 nParam1, u32 nParam2);
void _CallerLocationAppInputTextChangeCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);

/* Update */
void _CallerLocationAppLaunchWapRspCb(void *pvUserData, MAE_Ret nRspCode, void *pvRspData, CmnRspDataFreeCb pfnRspFreeCb);
void _CallerLocationAppLaunchWap(CallerLocationAppData_t* pThis);
void _CallerLocationAppMoveCldbFileCb(void *pUser, void *pInfo);
MAE_Ret _CallerLocationAppGetStorage(MAE_WChar *pStorage);
MAE_Ret _CallerLocationAppErrorDialogTimeOutCB(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);

/* Help */
MAE_Ret _CallerLocationAppWndHelpHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallerLocationAppWndCreateHelp(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CallerLocationAppSetHelpWnd(void  *pCusHandle, void *pWndData, u32 nWndInitParam);

#endif /* __MMI_CALLERLOCATION_PRIV_H__ */
