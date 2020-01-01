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
* @file    mmi_privateprotectpwapp_priv.h
* @version
* @brief   Privateprotectpwapp applet private header file
*
*/
#ifndef __MMI_PRIVATEPROTECTPWAPP_PRIV_H__
#define __MMI_PRIVATEPROTECTPWAPP_PRIV_H__

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
#include "mmi_privateprotectpwapp.h"
//#include "mmi_privateprotectapp_id.h"
#include "privateprotectapp_resource.h"


/*=============================================================*/
// Extern definition
/*=============================================================*/
#define PRIVATEPROTECT_PW_LEN 4

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef struct
{
    APPLET_BASE_ELEMENTS;
    u32				nPWInputLen;
	
	IPRIVATEPROTECTSRV *pIPrivateprotectSrv;
	IModel *pIPrivateprotectActionModel;
	ModelListener_t PrivateprotectActionMdlListener;

	PrivateprotectpwApp_Info_t *pInfo;
}PrivateprotectpwAppData_t;

/*
typedef enum
{
  	PW_VIEW_BEGIN = APP_WDG_START,
	PW_INPUTWIDGET,
  	PW_VIEW_END
}PrivateprotectPWView_e;
*/

typedef struct
{	
	PromptInputWdgList_t    tPromptInputWdgList;
}PWWndData_t;


typedef enum
{
	PRIVATEPROTECT_WND_PW = WND_ID_APP_BASE ,//+ 2,//only used in PrivateProtectAPPEnterPW 
}PrivateprotectPwAppWndId_e;


/*=============================================================*/
// Global function definition
/*=============================================================*/
/** PrivateprotectpwAppConstructor
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
MAE_Ret PrivateprotectpwAppConstructor
(
    IApplet *pApplet,
    u32     nEvt,
    u32     nParam1,
    u32     nParam2
);

MAE_Ret PrivateprotectpwAppDestructor
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
MAE_Ret PrivateprotectpwAppStartCB
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
MAE_Ret PrivateprotectpwAppStopCB
(
    IApplet *pApplet,
    u32     nEvt,
    u32     nParam1,
    u32     nParam2
);

MAE_Ret PrivateprotectpwAppResumeCB
(
    IApplet *pApplet, 
    u32 nEvt, 
    u32 nParam1, 
    u32 nParam2
);

MAE_Ret PrivateprotectpwAppSuspendCB
(
    IApplet *pApplet, 
    u32 nEvt, 
    u32 nParam1, 
    u32 nParam2
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

boolean PrivateprotectpwAppKeyPressCB
(
    IApplet *pApplet,
    u32     nEvt,
    u32     nParam1,
    u32     nParam2
);



#endif//#ifdef __APP_MMI_PRIVATEPROTECT__

#endif /* __MMI_PRIVATEPROTECTPWAPP_PRIV_H__ */

