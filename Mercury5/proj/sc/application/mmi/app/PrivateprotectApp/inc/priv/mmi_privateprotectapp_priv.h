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
* @file    mmi_privateprotectapp_priv.h
* @version
* @brief   Privateprotectapp applet private header file
*
*/
#ifndef __MMI_PRIVATEPROTECTAPP_PRIV_H__
#define __MMI_PRIVATEPROTECTAPP_PRIV_H__

#ifdef __APP_MMI_PRIVATEPROTECT__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_srv_clock.h"
#include "mmi_common_vtm.h"
#include "mmi_common_dialog.h"
#include "mmi_common_rai_id.h"

#include "mmi_privateprotectsrv.h"
#include "mmi_privateprotectapp.h"
#include "mmi_privateprotectapp_id.h"
#include "privateprotectapp_resource.h"


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
    u32				nFocusIndex;
	boolean			bPhonebookLocked;	
	boolean			bCallCenterLocked;	
	boolean			bMessageLocked;		
} PrivateprotectAppData_t;


typedef enum
{
  	MAIN_VIEW_BEGIN = APP_WDG_START,
	MAINVIEW_MFLCONTAINER,
	PHONEBOOK_PICKWIDGET,
	CALLCENTER_PICKWIDGET,
	MESSAGE_PICKWIDGET,
  	MAIN_VIEW_END
}PrivateprotectMainView_e;


typedef struct
{
	IWidget		    *pIMflContainer;
	IWidget         *pIPhonebookPickWdg;
  	IWidget         *pICallCenterPickWdg;
  	IWidget         *pIMessagePickWdg;
}MainWndData_t;


/*=============================================================*/
// Global function definition
/*=============================================================*/
/** PrivateprotectAppConstructor
* @brief        Applet start function(when receive MAE_EVT_CONSTRUCT)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE                Event is handled
* @retval       FALSE               Event needs to pass to other handle function
*
*/
boolean PrivateprotectAppConstructor
(
    IApplet *pApplet,
    u32     nEvt,
    u32     nParam1,
    u32     nParam2
);

MAE_Ret PrivateprotectAppDestructor
(
    IApplet *pApplet,
    u32     nEvt,
    u32     nParam1,
    u32     nParam2
);



/** PrivateprotectAppStartCB
* @brief        Applet start function(when receive MAE_EVT_APP_START)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE                Event is handled
* @retval       FALSE               Event needs to pass to other handle function
*
*/
boolean PrivateprotectAppStartCB
(
    IApplet *pApplet,
    u32     nEvt,
    u32     nParam1,
    u32     nParam2
);


/**PrivateprotectAppStopCB
* @brief        Applet stop function(when receive MAE_EVT_APP_STOP)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE                Event is handled
* @retval       FALSE               Event needs to pass to other handle function
*
*/
boolean PrivateprotectAppStopCB
(
    IApplet *pApplet,
    u32     nEvt,
    u32     nParam1,
    u32     nParam2
);


/** PrivateprotectAppPressCB
* @brief        Handle key press function(when receive MAE_EVT_KEY_PRESS)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE                Event is handled
* @retval       FALSE               Event needs to pass to other handle function
*
*/
boolean PrivateprotectAppKeyPressCB
(
    IApplet *pApplet,
    u32     nEvt,
    u32     nParam1,
    u32     nParam2
);



/** PrivateprotectAppMainWndHdl
* @brief        Main window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret PrivateprotectAppMainWndHdl
(
    void                *pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void                *pWndData,
    u32                 nWndInitParam
);

#endif//#ifdef __APP_MMI_PRIVATEPROTECT__

#endif /* __MMI_PRIVATEPROTECTAPP_PRIV_H__ */

