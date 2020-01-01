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
* @file    mmi_screensaverapp_priv.h
* @version
* @brief   Screensaver applet private header file
*
*/

#ifndef __MMI_SCREENSAVERAPP_PRIV_H__
#define __MMI_SCREENSAVERAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_screensaverapp.h"
#include "mmi_common_inttbl.h"

#include "mmi_srv_header.h"
#include "mmi_screensaverapp_id.h"
//#include "screensaverapp_resource.h"


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
	APPLET_BASE_ELEMENTS;

	IWidget *pAnimWdg;
	IImage *pISCImage;//screen saver image.
} ScreensaverAppData_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/

boolean ScreensaverStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ScreensaverForceStopCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ScreensaverGetProperty(IApplet *pApplet, u32 nEvt, u32 key, u32 outVal);
boolean ScreensaverDisableFingerCmdOnceCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret ScreensaverWndMainHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret ScreensaverWndCreateMain(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret ScreensaverWndDestroyMain(void *pCusHandle, void *pWndData);


#endif /* __MMI_SCREENSAVERAPP_PRIV_H__ */
