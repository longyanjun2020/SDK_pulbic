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
* @file mmi_g3dmainmenuapp_priv.h
* @version
* @brief   G3D main menu applet private header file
*
*/

#ifndef __MMI_G3DMAINMENUAPP_PRIV_H__
#define __MMI_G3DMAINMENUAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_g3dmainmenuapp.h"
#include "mmi_log.h"
#include "mmi_common_util_menu.h"
#include "mmi_wdg_glmenuwidget.h"
#include "mmi_mae_arraymodel.h"
#include "mmi_g3dmainmenuapp_id.h"
#include "g3dmainmenuapp_resource.h"


/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef struct
{
    IWidget *pIMenuWdg;
} G3dMainMenuMainWndWdgList_t;

typedef struct
{
    G3dMainMenuMainWndWdgList_t tWdgList;
} G3dMainMenuMainWndData_t;

/**
 * Application structure
 */
typedef struct
{
    APPLET_BASE_ELEMENTS;

    IArrayModel     *pIAvailItem;
    boolean         bIsLaunchAP;
    u32             nPlayStartAnimation;
	u16				u16MissCall;
    ModelListener_t menuWdgMdlListener;
    IWidget *pPrevButtonWidget;
    IWidget *pHomeButtonWidget;
    IWidget *pTranButtonWidget;
    IWidget *pNextButtonWidget;    
    IWidget *pBGImgWdg;
    boolean bIsLangCfgUpdate;
	boolean bIsSuspendState;
	boolean bCpatureImgFreed;
	u32		u32CubeStartPage;

#if defined (__DROPDOWN_STATUSPAGE__)
    IWidget *pStatusPageWidget;
    boolean bToShowStatusPageAfterResume;
	boolean bShowAirplanceModeWaitingDlg;
#endif // __DROPDOWN_STATUSPAGE__
} G3dMainMenuAppData_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/

boolean G3dMainMenuConstructCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean G3dMainMenuDestructCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean G3dMainMenuStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean G3dMainMenuResumeCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean G3dMainMenuSuspendCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean G3dMainMenuKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean G3dMainMenuTouchEventCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
MAE_Ret G3dMainMenuWndListMainHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

#endif //__MMI_G3DMAINMENUAPP_PRIV_H__

