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
* @file    mmi_mgldemoapp_priv.h
* @version
* @brief   MglDemoApp applet private header file
*
*/

#ifndef __MMI_MGLDEMOAPP_PRIV_H__
#define __MMI_MGLDEMOAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_mgldemoapp.h"
#include "mgl_Egl.h"
#include "mgl_Core_Types.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef MAE_Ret (*pfnDemoStart)(IApplet *pApplet);
typedef MAE_Ret (*pfnDemoEnd)(IApplet *pApplet);
typedef MAE_Ret (*pfnTimerTimeout)(IApplet *pApplet);
typedef MAE_Ret (*pfnDemoTouch)(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2, bool *pbNeedUpdateScreen);

typedef struct
{
    pfnDemoStart pfnStart; // start demo case
    pfnDemoEnd   pfnEnd;  // end demo case
    pfnTimerTimeout pfnTimeout; // need timer for animation
    u32 nTimer; // in ms
    pfnDemoTouch pfnTouchEvent;
}MglDemoAppDemoCases_t;

/**
 * Application structure
 */
typedef struct
{
    APPLET_BASE_ELEMENTS;
    mgl_u16 u16SceneHandleId;
    bool bIsDemoRunning;
	const MglDemoAppDemoCases_t *ptDemoCase;
} MglDemoAppData_t;


/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret MglDemoConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret MglDemoDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean MglDemoStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean MglDemoStopCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean MglDemoIsFOCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean MglDemoKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean MglDemoTSCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
void MglDemoCaseTimeoutCb(void* pUserData);

#endif /* __MMI_MGLDEMOAPP_PRIV_H__ */
