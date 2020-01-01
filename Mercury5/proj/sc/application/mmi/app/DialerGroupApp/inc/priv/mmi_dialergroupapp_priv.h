////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file mmi_dialergroupapp_priv.h
* @version $Id: mmi_dialergroupapp_priv.h
*/

#ifndef __MMI_DIALERGROUPAPP_PRIV_H__
#define __MMI_DIALERGROUPAPP_PRIV_H__

/*-------------------------------------------------------------------------*/
#include "mmi_baseapplet.h"
#include "mmi_dialergroupapp.h"
/*-------------------------------------------------------------------------*/
#include "mmi_srv_header.h"
#include "mmi_launcher_common.h"
#include "mmi_launcher_calllog.h"
#include "mmi_calllogapp.h"
#include "mmi_launcher_phb.h"

typedef struct
{
    APPLET_BASE_ELEMENTS;
	
	u8 nCurrAPIdx;
} DialerGroupAppData_t;

typedef struct
{
    APPLET_BASE_ELEMENTS;

    u8          nCurrDualID;

} CallSettingAppData_t;

/*-------------------------------------------------------------------------*/
MAE_Ret DialerGroupAppConstructor(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
MAE_Ret DialerGroupAppDestructor(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean DialerGroupAppStartCB(IApplet* pApplet,MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean DialerGroupAppSuspendCB(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean DialerGroupAppResumeCB(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean DialerGroupAppKeyPressCB(IApplet* pApplet,MAEEvent_t nEvt, u32 lparam, u32 dparam);

MAE_Ret _DialerGroupAppLaunchAP(DialerGroupAppData_t *pThis, u8 nAPIndex);


/*-------------------------------------------------------------------------*/
#endif /* __MMI_DIALERGROUPAPP_PRIV_H__ */
