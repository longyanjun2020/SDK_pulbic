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
* @file    mmi_angrybird_priv.h
* @version
* @brief   AngryBird applet private header file
*
*/

#ifndef __MMI_ANGRYBIRD_PRIV_H__
#define __MMI_ANGRYBIRD_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_angrybird.h"

//#include "melody_data.h"
#include "mmi_srv_audio.h"

#include "AngryBird_resource.h"

#include "mgl_Egl.h"
#include "mgl_Core_Types.h"

#include "AngryBird.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
enum 
{
	ANGRYBIRD_WND_DESKTOP = WND_ID_APP_BASE,
};

enum
{
	ANGRYBIRD_BG_IMAGEWIDGET = APP_WDG_START,
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

MAE_Ret AngryBirdConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret AngryBirdDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AngryBirdStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AngryBirdStopCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AngryBirdKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AngryBirdTSCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

boolean AngryBirdHookDraw(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AngryBirdGetInvalidateRect(IApplet *pApplet, u32 u32DisplayInfo, u32 param1, u32 param2);

MAE_Ret AngryBirdWndDesktopHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret AngryBirdWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);

#endif 
