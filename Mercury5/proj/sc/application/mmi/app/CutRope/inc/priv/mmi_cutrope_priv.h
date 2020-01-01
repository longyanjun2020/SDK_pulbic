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
* @file    mmi_IplayCube_priv.h
* @version
* @brief   IplayCube Game applet private header file
*
*/

#ifndef __MMI_CUTROPE_PRIV_H__
#define __MMI_CUTROPE_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"

#include "melody_data.h"
#include "mmi_srv_audio.h"

#include "cutrope_resource.h"

#include "mgl_Egl.h"
#include "mgl_Core_Types.h"

#include "CutRope.h"
#include "CutRopeAPI.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
enum 
{
	CUTROPE_WND_DESKTOP = WND_ID_APP_BASE,
};

enum
{
	CUTROPE_BG_IMAGEWIDGET = APP_WDG_START,
};
/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret CutRopeConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret CutRopeDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CutRopeStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CutRopeStopCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CutRopeIsFOCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CutRopeKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CutRopeTSCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CutRopePreHookCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

boolean CutRopeHookDraw(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CutRopeIsFullOpaque(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CutRopeGetInvalidateRect(IApplet *pApplet, u32 u32DisplayInfo, u32 param1, u32 param2);

MAE_Ret CutRopeWndDesktopHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CutRopeWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);

#endif 
