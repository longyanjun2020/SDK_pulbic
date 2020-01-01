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
* @file    mmi_evtcenterapp_priv.h
* @version
* @brief   EventCenter applet private header file
*
*/

#ifndef __MMI_EVTCENTERAPP_PRIV_H__
#define __MMI_EVTCENTERAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_evtcenterapp.h"
#include "mmi_evtcenterapp_custom.h"
#include "mmi_common_dialog_id.h"
#include "mmi_wdg_headers.h"
#include "mmi_common_vtm.h"
#include "mmi_launcher_alarm.h"
#include "mmi_launcher_calendar.h"
#include "mmi_launcher_mca.h"
#include "mmi_evtcenterapp_id.h"
#include "evtcenterapp_resource.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

#define MAX_MISSED_NUM_DIGITS	2
#define EVTCENTERAPP_ARRAYMODEL_SIZE_INIT 120
#define EVTCENTERAPP_ARRAYMODEL_SIZE_GROW 120

#define EVTCENTERAPP_SYSVIEWTAB_MASK_NONE       0
#define EVTCENTERAPP_SYSVIEWTAB_MASK_ALARM      (1 << 0)
#define EVTCENTERAPP_SYSVIEWTAB_MASK_BATT       (1 << 1)
#define EVTCENTERAPP_SYSVIEWTAB_MASK_OTHER      (1 << 2)
#define EVTCENTERAPP_SYSVIEWTAB_MASK_ALL        (EVTCENTERAPP_SYSVIEWTAB_MASK_ALARM|EVTCENTERAPP_SYSVIEWTAB_MASK_BATT|EVTCENTERAPP_SYSVIEWTAB_MASK_OTHER)

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum
{
	EVTCENTER_APP_EVENT_ALL_EVENT = 0,
	EVTCENTER_APP_EVENT_MISSED_CALL, //skip missed call
	EVTCENTER_APP_EVENT_SMS,
	EVTCENTER_APP_EVENT_CB,
	EVTCENTER_APP_EVENT_MMS,
	EVTCENTER_APP_EVENT_WAP,
	EVTCENTER_APP_EVENT_EMAIL,
	EVTCENTER_APP_EVENT_VOICEMAIL,
	EVTCENTER_APP_EVENT_ALARM_CALENDAR,
	EVTCENTER_APP_EVENT_BATTERY,
	EVTCENTER_APP_EVENT_SIM,
	EVTCENTER_APP_EVENT_OTHER
}EvtCenterAppEventType_e;

typedef enum
{
	EVTCENTER_APP_SUMMARY_MENU_MISSED_CALL = 0,
	EVTCENTER_APP_SUMMARY_MENU_SMS,
	EVTCENTER_APP_SUMMARY_MENU_CB,
	EVTCENTER_APP_SUMMARY_MENU_VOICEMAIL,
	EVTCENTER_APP_SUMMARY_MENU_ALARM,
	EVTCENTER_APP_SUMMARY_MENU_BATTERY,
	EVTCENTER_APP_SUMMARY_MENU_OTHER
}EvtCenterAppSummaryMenu_e;


typedef struct
{
    APPLET_BASE_ELEMENTS;

	ArrayClass_t *pSystemAlarmArrayClass;	//keep alarm events of system view;
	ArrayClass_t *pSystemBattArrayClass;	//keep battery events of system view;
	ArrayClass_t *pSystemOtherArrayClass;	//keep other events of system view;

	EVTCenterStatus_t tEvtCenterStatus;	//store event status;
	HistoryInfo_t MenuHistory_All;		//keep menu history of all summary list;
	HistoryInfo_t MenuHistory_Sys;	//keep menu history of system event view;

    u32 nAlarmEvt;
    u32 nBattEvt;
    u32 nOtherEvt;
	EvtCenterApp_Start_Type_e eStartType;	//store start type;
	boolean	bCloseSelf;	                    //Is need to close self app;
	u32	nDialog;	                        //store dialog textlabel;

    EvtCenterApp_SysMenuType_e eSysViewMenuIndex;	//keep System view menu index;
	boolean bIsSuspend;
	boolean bNeedToResetSMS;
	boolean bNeedToResetCB;
	u32	nResetSysEvtType;

} EvtCenterApp_t;

typedef struct
{
	IWidget *pMenuWdg;
	IWidget *pImageWdg01;
	IWidget *pImageWdg02;
	IWidget *pImageWdg03;
	IWidget *pImageWdg04;
	IWidget *pImageWdg05;
	IWidget *pImageWdg06;
	IWidget *pTextWdg01;
	IWidget *pTextWdg02;
	IWidget *pTextWdg03;
	IWidget *pTextWdg04;
	IWidget *pTextWdg05;
	IWidget *pTextWdg06;
} AllEvtSummaryWndWdgList_t;

typedef struct
{
    AllEvtSummaryWndWdgList_t tWdgList;
} AllEvtSummaryWndData_t;

typedef struct
{
    IWidget             *pMenuWdg;
    boolean             bNoResetLog;
    boolean             bDestroying;
} SysEvtSummaryWndData_t;

typedef struct
{
    OptionMenuWdgList_t tOptionMenuWdgList;
} SysOptionMenuWndData_t;

typedef struct
{
    IWidget *pTitleWdg;
    IWidget *pPropContainer;
    IWidget *pDateTimeTextWdg;
    IWidget *pInfoTextWdg;
}DetailWndWdgList_t;

typedef struct
{
    DetailWndWdgList_t tWdgList;
} DetailWndData_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret EvtCenterAppConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret EvtCenterAppDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean EvtCenterAppStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean EvtCenterAppStopCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean EvtCenterAppSuspendCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean EvtCenterAppResumeCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean EvtCenterAppKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

MAE_Ret EvtCenterAppInfoDialogTimerCb(void *pData, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
void EvtCenterAppSMSLogChangeCb(void *pUserData, u16 nSMSLogNum);
void EvtCenterAppMMSLogChangeCb(void *pUserData, u16 nSMSLogNum);
void EvtCenterAppCellBroadcastLogChangeCb(void *pUserData, u16 nSMSLogNum);
void EvtCenterAppVoiceMailLogChangeCb(void *pUserData, u16 nSMSLogNum);
void EvtCenterAppAlarmLogChangeCb(void *pUserData, u16 nSMSLogNum);
void EvtCenterAppBatteryLogChangeCb(void *pUserData, u16 nSMSLogNum);
void EvtCenterAppOtherLogChangeCb(void *pUserData, u16 nSMSLogNum);

static void _EvtCenterAppViewAdaptGet(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);
static void _EvtCenterAppViewItemDataFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);

void EvtCenterAppMenuSoftkeyCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void EvtCenterAppMenuOnFocusCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);
void EvtCenterAppMenuTitleChangeCb (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TitleDataChangeData_t *pTitleDataChangeData, IWidget *pWidget);
void EvtCenterAppOptionMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

//Window manager related function
MAE_Ret EvtCenterAppWndAllSummaryHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret EvtCenterAppWndSysSummaryHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret EvtCenterAppWndSysOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret EvtCenterAppWndDetailHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

#endif /* __MMI_EVTCENTERAPP_PRIV_H__ */
