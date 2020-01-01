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
* @file    mmi_fmschapp_priv.h
* @version
* @brief   FM schedule applet private header file
*
*/

#ifndef __MMI_FMSCHAPP_PRIV_H__
#define __MMI_FMSCHAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_fmschapp.h"
#include "mmi_fmschapp_util.h"

#include "mmi_common_dialog.h"
#include "mmi_srv_header.h"
#include "mmi_common_vtm.h"

#include "mmi_rs_macro_struct.h"
#include "mmi_fmschapp_id.h"
#include "fmschapp_resource.h"

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
    ALARM_FIELD_CHANNEL_FREQUENCY,
    ALARM_FIELD_STATUS,
    ALARM_FIELD_TIME,
    ALARM_FIELD_FREQUENCY,
    ALARM_FIELD_RINGTONE
} AlarmField_e;

/* The type of message to be displayed on dialog. */
typedef enum
{
    FMSCHAPP_MSG_SAVEALARMSUCCESS,
    FMSCHAPP_MSG_SAVEALARMFAIL,
    FMSCHAPP_MSG_CHANNEL_OUT_OF_RANGE,
    FMSCHAPP_MSG_CHANNEL_INPUT_FAIL,
    FMSCHAPP_MSG_RECORD_TIME_OVERLAP, // Show "Record time overlap!"
    FMSCHAPP_MSG_PLAYING_TIME_OVERLAP, //Show "Play time overlap!"
    FMSCHAPP_MSG_CHANNEL_EMPTY, // Show "Frequency is empty!"
    FMSCHAPP_MSG_SAVESUCCESS_NOTIFY_HEADSET_PLUG,
    FMSCHAPP_MSG_STARTDATETIME_PAST, // Show "Start time must be greater than current time!"
    FMSCHAPP_MSG_ENDTIME_EARLIER, // Show "End time must be greater than start time!"
    FMSCHAPP_MSG_PLAYBACKTIME_CONFLICT, // Show "Time can't conflict with other FM schedule playback.
    FMSCHAPP_MSG_SAVESUCCESS_NOTIFY_HEADSET_PLUG_PLAY,//Show "Plug headset when playing!"
    FMSCHAPP_MSG_STORAGE_NOT_EXIST_SCH_RECORD_OFF, //Show "Storage not exist, schedule record is turned off."
    FMSCHAPP_MSG_STORAGE_UNSUPPORT_FORMAT_ON_NOR,
} FmSchAppMsg_e;

typedef enum
{
    FMSCHAPP_TYPE_PLAY,
    FMSCHAPP_TYPE_RECORD,
} FmSchAppType_e;

/* The data structure is used for storing the variables of the set alarm view. */
typedef struct
{
    IWidget                 *pIChannelFrequencyWidget;
    IWidget                 *pITimeWidget;
    IWidget                 *pIStatusWidget;
    IWidget                 *pIFrequencyWidget;
    IWidget                 *pIMflContainerWidget;
    IWidget                 *pIScrollBarWidget;

    u32                     nAlarmId;
    u32                     nChannelFreq;
    SetPhoneTimeFormat_e    eTimeFormat;
    ALARM_FREQUENCY_e       eFrequency;
    ScrollData_t            tScrollData;
} FmSchSetPlayScheduleView_t;

#ifdef __APP_MMI_FM_RADIO_REC__
/* The data structure is used for storing the variables of the set alarm view. */
typedef struct
{
    IWidget                 *pIChannelFrequencyWidget;
    IWidget                 *pIStatusWidget;
    IWidget                 *pIStartDateWidget;
    IWidget                 *pIStartTimeWidget;
    IWidget                 *pIEndTimeWidget;
    IWidget                 *pIFrequencyWidget;
    IWidget                 *pIRecFileWidget;
    IWidget                 *pIRecFileTypeWidget;
    IWidget                 *pIStorageTypeWidget;
    IWidget                 *pIMflContainerWidget;
    IWidget                 *pIScrollBarWidget;

    u16                     nAlarmId;
    u32                     nChannelFreq;
    SetPhoneTimeFormat_e    eTimeFormat;
    ALARM_FREQUENCY_e       eFrequency;
	boolean                 bAppendRecord;
	MAE_WChar                *pRecFileURL;
	VOICE_RECORD_Type_e      eRecordType;
	FM_Record_Storage_e      eStorage;

    ScrollData_t            tScrollData;
} FmSchSetRecScheduleView_t;
#endif

/* The data structure is used for storing the variables of the set alarm view. */
typedef struct
{
    IWidget *   pIFreqThmTextWdg;
    FMR_CHANNEL_RECORD_t MyChannelList[FMR_CHANNEL_NUM_MAX];
} FmSchSelectMyChannelView_t;

/* The data structure is used for storing the variables of the set alarm view. */
typedef struct
{
    boolean bSKShown;   //Check if softkey is shown.
} FmSchManualInputView_t;

/* The data structure is used for storing the variables of the set frequency view. */
typedef struct
{
    IWidget         *pIMenuWidget;
} FmSchSetFrequencyView_t;

/* The data sturcture is used for storing the variables of the set rec file view. */
typedef struct
{
  PopUpSelectWdgList_t   tWdgList;
} FmSchSetRecFileView_t;

typedef struct
{
	PopUpSelectWdgList_t tWdgList;
} FmSchSetRecFileTypeView_t;

typedef struct
{
    PopUpSelectWdgList_t tWdgList;
} FmSchSetStorageTypeView_t;

/**
 * Application structure
 */
typedef struct
{
    APPLET_BASE_ELEMENTS;
    FMSCH_ENTITY_t                  _playSchList[FMSCH_RECORDS_MAX_NUM];
#ifdef __APP_MMI_FM_RADIO_REC__
    FMRECSCH_ENTITY_t               _recSchList[FMRECSCH_RECORDS_MAX_NUM];
#endif
    FmSchAppMsg_e                   eMsgID;
    FmSchAppType_e                  eType;
    boolean                         bCardPlugHappen;

} FmSchAppData_t;

/*=============================================================*/
// Local function definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret FmSchDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FmSchStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FmSchKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FmSchResumeCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FmSchPreHookCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
void FmSchCfgItemUpdateIndCB(void *pThis, SrvCfgItemStatusChangeType_e IndType, SrvCfgItemUpdateResult_t tresult);
//Window manager related function
MAE_Ret FmSchPlayListWndHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FmSchSetPlayScheduleWndHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FmSchSelectMenuWndHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FmSchSelectMyChannelWndHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FmSchManualInputWndHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FmSchSetFrequencyWndHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FmSchSetRecFileWndHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FmSchSetRecFileTypeWndHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FmSchSetStorageTypeWndHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifdef __APP_MMI_FM_RADIO_REC__
MAE_Ret FmSchRecListWndHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FmSchSetRecScheduleWndHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif

void _FmSchSwitchWindow(FmSchAppData_t *pThis, MAE_WndId nWndId, u32 nWndParam);
static void _FmSchAppTimeAmPmChange(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TimePeriod_e eTimePeriod, IWidget *pWidget);
static MAE_Ret _FmSchAppSwitchTimeWidgetAmPm(IWidget* pITimeWidget);
static MAE_Ret _FmSchAppSetAlarmViewGetFrequencyString(FmSchAppData_t* pThis, ALARM_FREQUENCY_e eFrequency, MAE_WChar** ppFrequencyStr);
static MAE_Ret _FmSchAppSetScheduleViewGetValuesFromWidgets(FmSchAppData_t* pThis, u32 nAlarmUID);
static MAE_Ret _FmSchAppSetRecScheduleViewGetValuesFromWidgets(FmSchAppData_t* pThis, u32 nAlarmUID);
//static MAE_Ret _FmSchAppSetScheduleViewSetValuesToWidgets(FmSchAppData_t* pThis, u32 nAlarmId);
//static MAE_Ret _FmSchAppSetRecScheduleViewSetValuesToWidgets(FmSchAppData_t * pThis,u32 nAlarmId);
static void _FmSchAppResetScrollData(ScrollData_t* pScrollData);
static void _FmSchAppDialogTimeOut(void* pUserData);
void FmSchAppEditAlarmSetFrequencyOk(FmSchAppData_t* pThis);
void  FmSchAppEditAlarmSetFrequencySelect(FmSchAppData_t* pThis, u32 nParam);
static MAE_Ret _FmSchAppOpenDialog(FmSchAppData_t* pThis, FmSchAppMsg_e eMsg);
void FmSchAppEditAlarmSetAlarm(FmSchAppData_t* pThis);
void FmSchAppEditAlarmSaveAlarm(FmSchAppData_t* pThis);
void FmSchAppEditRecAlarmSetAlarm(FmSchAppData_t* pThis);
void FmSchAppEditRecAlarmSaveAlarm(FmSchAppData_t *pThis);

//record schedule checking
#ifdef __APP_MMI_FM_RADIO_REC__
static boolean FmSchAppCheckRecSchedule(FmSchAppData_t *pThis, u32 nAlarmId, FmSchAppMsg_e *pMsg);
static boolean _FmSchAppCheckRecordTimeOverlap(FmSchAppData_t *pThis, u32 nAlarmId);
static boolean _FmSchAppCheckPlaybackTimeOverlap(FmSchAppData_t *pThis, u32 nAlarmId);
static boolean _FmSchAppCheckRecordTimeOverlap2(FmSchAppData_t *pThis, u32 nAlarmId);
#endif

//play schedule checking
static boolean FmSchAppCheckPlaySchedule(FmSchAppData_t *pThis, u32 nAlarmId, FmSchAppMsg_e *pMsg);
static boolean _FmSchAppCheckSettingTimeOverlap(FmSchAppData_t *pThis, u32 nAlarmId);

//common checking functions
static boolean _FmSchAppCheckChannelEmpty(u32 channelFreq);
static boolean _FmSchAppCheckChannelOutOfRange(u32 channelFreq);
static boolean _FmSchAppCheckStartDateTimePast(u32 startDateTime);
static boolean _FmSchAppCheckEndTimeEarlierThanStartTime(u32 startDateTime, u32 endTime);

//checking util functions
static ALARM_FREQUENCY_e _FmSchApp_GetFrequencyByTimeSec(u32 nTimeSec);
static s8 _FmSchApp_CompareTimeWithoutDate(u32 nTime1, u32 nTime2);

#endif /* __MMI_ALARMAPP_PRIV_H__ */
