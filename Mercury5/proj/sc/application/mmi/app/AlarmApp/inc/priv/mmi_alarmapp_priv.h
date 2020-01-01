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
* @file    mmi_alarmapp_priv.h
* @version
* @brief   Alarm applet private header file
*
*/

#ifndef __MMI_ALARMAPP_PRIV_H__
#define __MMI_ALARMAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_alarmapp.h"
#include "mmi_alarmapp_util.h"

#include "mmi_common_dialog.h"
#include "mmi_srv_header.h"

#include "mmi_common_vtm.h"
#include "mmi_alarmapp_id.h"
#include "alarmapp_resource.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define ALARMAPP_EMPTY_TITLE_STRING L""
#define FREQUENCY_STATUS_NUM 9

/*=============================================================*/
// Data type definition
/*=============================================================*/

/* The field ids of an alarm record. */
typedef enum
{
    ALARM_FIELD_TITLE,
    ALARM_FIELD_STATUS,
    ALARM_FIELD_TIME,
    ALARM_FIELD_FREQUENCY,
    ALARM_FIELD_RINGTONE
} AlarmField_e;

/* The type of message to be displayed on dialog. */
typedef enum
{
    ALARM_MSG_SAVEALARMSUCCESS,
    ALARM_MSG_SAVEALARMFAIL,
    ALARM_MSG_TITLEISEMPTY
} AlarmMsg_e;

/* This data structure is used to pass the values of field name or alarm uid together. */
typedef struct
{
    u32             nOtherInfo; /* May be alarm uid. */
    AlarmField_e    eFieldName;
} AlarmFieldData_t;

/* This data structure is used to keep the temporary field values of the set alarm view. */
typedef struct
{
    MAE_WChar           *pTitle;
    MAE_DateTime_t      *pTime;
    MAE_WChar* pRingToneURL;
    ALARM_STATUS_e      eStatus;
    ALARM_FREQUENCY_e   eFrequency;
} AlarmSetAlarmTmpInfo_t;

/* The data structure is used for storing the variables of the alarm list view. */
typedef struct
{
    IMenuModel  *pIMenuModel; // will be removed
} AlarmListView_t;

/* The data structure is used for storing the variables of the set alarm view. */
typedef struct
{
    IWidget                 *pITitleWidget;
    IWidget                 *pITimeWidget;
    IWidget                 *pIStatusWidget;
    IWidget                 *pIFrequencyWidget;
    IWidget                 *pIRingtoneWidget;
    IWidget                 *pIMflContainerWidget;
    IWidget                 *pIScrollBarWidget;
    u32                     nAlarmUID;
    MAE_WChar               *pRingToneURL;
    SetPhoneTimeFormat_e    eTimeFormat;
    ALARM_FREQUENCY_e       eFrequency;
    ScrollData_t            tScrollData;
} AlarmSetAlarmView_t;

/* The data structure is used for storing the variables of the set title view. */
typedef struct
{
    IWidget         *pIInputWidget;
} AlarmSetTitleView_t;

typedef struct
{
    IWidget     *pIOptionMenuWidget;
} AlarmSetTitleLoadOptionMenuView_t;

/* The data structure is used for storing the variables of the set frequency view. */
typedef struct
{
    IWidget         *pIMenuWidget;
} AlarmSetFrequencyView_t;

/* The data structure is used for storing the variables of the set ringtone view. */
typedef struct
{
    IWidget         *pIMenuWdg;
} AlarmSetRingtoneView_t;

typedef struct
{
    IWidget                 *pIInputWidget;
    MAE_WChar               *pRingToneURL;
    u32                     nAlarmUID;
} AlarmViewAlarmView_t;

/**
 * Application structure
 */
typedef struct
{
    APPLET_BASE_ELEMENTS;
    ALARM_RECORD_t          _alarmList[ALARM_RECORDS_MAX_NUM];
    AlarmSetAlarmTmpInfo_t  *pSetAlarmTmpInfo;
    u32                     nAlarmIndex;
    u32                     nFocusIndex;
    AlarmMsg_e              eMsgID;
    boolean                 bLaunchAp;
} AlarmAppData_t;

/*=============================================================*/
// Local function definition
/*=============================================================*/
void AlarmWndMenuSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
MAE_Ret _AlarmListWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);

MAE_Ret _AlarmSetAlarmWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _AlarmSetAlarmWndDestroy(void *pCusHandle, void *pWndData);
MAE_Ret _AlarmSetAlarmWndConvert(void *pCusHandle, void *pWndData);

MAE_Ret _AlarmSetTitleWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);

MAE_Ret _AlarmSetTitleLoadOptionMenuWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _AlarmSetTitleLoadOptionMenuWndDestroy(void *pCusHandle, void *pWndData);

MAE_Ret _AlarmSetFrequencyWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);

MAE_Ret _AlarmViewAlarmWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);

MAE_Ret _AlarmFileMgrWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _AlarmFileMgrWndDestroy(void *pCusHandle, void *pWndData);

/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret AlarmDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AlarmStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AlarmKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AlarmResumeCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AlarmPreHookCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
void AlarmAccessoryPlugStatusCB(void *pUserData, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);
void AlarmExpiredAlarmCloseCB(void *pUserData, u32 nExpiredAlarmUserCode, u32 nAlarmAlertReply);

//Window manager related function

MAE_Ret AlarmListWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret AlarmSetAlarmWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret AlarmSetTitleWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret AlarmSetTitleLoadOptionMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret AlarmSetFrequencyWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret AlarmViewAlarmWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret AlarmFileMgrWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

#ifdef __USB_MMI_NON_BLOCKING_USAGE__
static void _AlarmAppUsbStatusChangedCb(void *pApplet, MMI_USB_STATUS_E eUsbStatus);
#endif
#if defined(__APP_MMI_CHECKDISK__)
static void _AlarmAppCheckDiskListener(char *pSbjName, SubjectStatus_e nSbjStatus, void *pUser);
#endif
void _AlarmSwitchWindow(AlarmAppData_t *pThis, MAE_WndId nWndId, u32 nWndParam);
void _AlarmAppViewAlarmStatusChange(AlarmAppData_t *pThis);
void _AlarmAppSetAlarmStatusChange(AlarmAppData_t* pThis);
static MAE_Ret _AlarmAppGetRingerFileNameByURL(AlarmAppData_t* pThis, MAE_WChar* pURL, MAE_WChar** ppRingerName);
void _AlarmAppMflContainerMFLFocusSelect(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, MFLFocusData_t *pMFLFocusData, IWidget *pWidget);
void _AlarmAppMflContainerMFLFocusChange(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, MFLFocusData_t *pMFLFocusData, IWidget *pWidget);
static MAE_Ret _AlarmAppSetTimeWidgetFormat(IWidget* pIWidget, SetPhoneTimeFormat_e eTimeFormat);
static MAE_Ret _AlarmAppSwitchTimeWidgetAmPm(IWidget* pITimeWidget);
static MAE_Ret _AlarmAppSetAlarmViewSetValuesToWidgets(AlarmAppData_t* pThis, u32 nAlarmUID);
static void _AlarmAppTimeAmPmChange(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TimePeriod_e eTimePeriod, IWidget *pWidget);
static MAE_Ret _AlarmAppSetAlarmViewSetValuesToTmpInfo(AlarmAppData_t* pThis);
static MAE_Ret _AlarmAppSwitchSoftKeyAMPM(AlarmAppData_t* pThis, IWidget* pITimeWidget);
static MAE_Ret _AlarmAppSetSoftKey(AlarmAppData_t* pThis, SoftkeyID eSoftkeyID);
static void _AlarmAppSetAlarmTmpInfoFree(AlarmAppData_t* pThis);
static MAE_Ret _AlarmAppSetAlarmViewGetFrequencyString(AlarmAppData_t* pThis, ALARM_FREQUENCY_e eFrequency, MAE_WChar** ppFrequencyStr);
static void _AlarmAppSetTitleViewOptionMenuViewModelListener(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _AlarmAppSetTitleViewOptionMenuViewModelLayer2Listener(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void _AlarmAppTextInputOptionMenuViewModelListener(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static MAE_Ret _AlarmAppSetAlarmViewGetValuesFromWidgets(AlarmAppData_t* pThis, u32 nAlarmUID);
static void _AlarmAppResetScrollData(ScrollData_t* pScrollData);
static MAE_Ret _AlarmAppSetTitleViewGetInputText(AlarmAppData_t* pThis);
static void _AlarmAppDialogTimeOut(void* pUserData);
void AlarmAppEditAlarmSetFrequencyOk(AlarmAppData_t* pThis);
void  AlarmAppEditAlarmSetFrequencySelect(AlarmAppData_t* pThis, u32 nParam);
static MAE_Ret _AlarmAppViewAlarmViewSetValuesToWidgets(AlarmAppData_t* pThis, u32 nAlarmUID);
static MAE_Ret _AlarmAppOpenDialog(AlarmAppData_t* pThis, AlarmMsg_e eMsg);
void  AlarmAppEditAlarmSaveAlarm(AlarmAppData_t* pThis);
void  AlarmAppEditAlarmSetAlarm(AlarmAppData_t* pThis);

void _AlarmLaunchFileManager(AlarmAppData_t* pThis, MenuItemId_e eMenuItemID, u32 nSelectedID);
void _AlarmFileMgrViewMdlListener(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

#endif /* __MMI_ALARMAPP_PRIV_H__ */
