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
* @file    mmi_evtcenterapp.h
* @version
* @brief   EventCenter applet header file
*
*/

#ifndef __MMI_EVTCENTERAPP_H__
#define __MMI_EVTCENTERAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_launcher_eventcenter.h"
#include "mmi_srv_header.h"
#include "mmi_common_evtcenter_type.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum
{
	EvtCenterApp_SysMenuType_Alarm = 0,
	EvtCenterApp_SysMenuType_Batt,
	EvtCenterApp_SysMenuType_Other
}EvtCenterApp_SysMenuType_e;

typedef enum
{
	MenuStartType_Applet = 0,
	MenuStartType_Submenu
}EvtCenterApp_MenuStartType_e;

typedef struct
{
	EvtCenterApp_MenuStartType_e eStartType;
	u32 nViewID;
	u32 nMdlID;
	u32 nParam;
	u32 nMenuModelID;
} EvtCenterApp_MenuItemInfo_t;

typedef struct
{
	MenuModelData_t stMenuModelData;
	EvtCenterApp_MenuItemInfo_t stMenuItemData;
} EvtCenterApp_MenuItemStruct_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret EvtCenterAppNew(MAE_ClsId id, void **ppObj);
void EvtCenterAppPreNew(void);

#endif /* __MMI_EVTCENTERAPP_H__ */
