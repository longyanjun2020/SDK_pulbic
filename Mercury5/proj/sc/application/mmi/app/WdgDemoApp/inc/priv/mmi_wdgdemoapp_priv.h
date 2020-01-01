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
* @file    mmi_wdgdemoapp_priv.h
* @version
* @brief   WdgDemoApp applet private header file
*
*/

#ifndef __MMI_WDGDEMOAPP_PRIV_H__
#define __MMI_WDGDEMOAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_base_util.h"
#include "mmi_layout.h"
#include "mmi_wdgdemoapp.h"
#include "mmi_log.h"
#include "mae_wallpaperwidget.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/**
 * Application structure
 */
typedef struct
{
    APPLET_BASE_ELEMENTS;    
} WdgDemoAppData_t;

typedef enum
{
    WDGDEMOAPP_WND_MAIN = WND_ID_APP_BASE,
} WdgDemoAppWndId_e;

typedef enum
{
    WDGDEMOAPP_FLASHLIGHT = 0,
    WDGDEMOAPP_FIRE,
    WDGDEMOAPP_LEAF,
    WDGDEMOAPP_SPHEREMENU,
    WDGDEMOAPP_EARTHROT,
    WDGDEMOAPP_FLAME,
    WDGDEMOAPP_COMET,
    WDGDEMOAPP_FIREWORK,
    WDGDEMOAPP_SNAKELINE,
    WDGDEMOAPP_PLBALL,
    WDGDEMOAPP_TUNELTEXTURE,
} WdgDemoAppId_e ;

typedef struct
{
    IWidget *pGlWidget;
} WdgDemoAppWdgList_t;

typedef struct
{
    WdgDemoAppId_e eAppId ;
    WdgDemoAppWdgList_t tWdgList;
} WdgDemoAppWndData_t;


/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret WdgDemoConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret WdgDemoDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean WdgDemoStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean WdgDemoKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

MAE_Ret WdgDemoAppWndHdlMain(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret _WdgDemoAppWndHdlMainCreate(void);
static MAE_Ret _WdgDemoAppWndHdlMainDestroy(void);
static MAE_Ret _WdgDemoAppFlashLight(void);
static MAE_Ret _WdgDemoAppFire(void);
static MAE_Ret _WdgDemoAppLeaf(void);
static MAE_Ret _WdgDemoAppSphereMenu(void);
static MAE_Ret _WdgDemoAppEarthRot(void) ;
static MAE_Ret _WdgDemoAppFlame(void) ;
static MAE_Ret _WdgDemoAppComet(void);
static MAE_Ret _WdgDemoAppFirework(void);
static MAE_Ret _WdgDemoAppSnakeline(void);
static MAE_Ret _WdgDemoAppPlball(void);
static MAE_Ret _WdgDemoAppTuneltextture(void) ;
static MAE_Ret _WdgDemoAppCreateWallPaper(SetWallpaper_3DEffect_e stytle) ;



#endif /* __MMI_MGLDEMOAPP_PRIV_H__ */
