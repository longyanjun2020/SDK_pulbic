/**
* @file    mmi_srv_evtcenter.h
* @brief
*
*/

#ifndef __MMI_SRV_EVTCENTER_H__
#define __MMI_SRV_EVTCENTER_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_evtcentersrv.h"


//#define EVTCENTERSRV_EVT_NewMessageNum                (CLSID_EVTCENTERSRV << 16 | 1)
typedef void (* SrvEvtCenterNewMessageNumCB)(void *pThis, u16 nNewMsgNum);
//#define EVTCENTERSRV_EVT_MissedCallNum                (CLSID_EVTCENTERSRV << 16 | 2)
typedef void (* SrvEvtCenterMissedCallNumCB)(void *pThis, u16 nMissedCallNum);
//#define EVTCENTERSRV_EVT_NewAlarmId               (CLSID_EVTCENTERSRV << 16 | 3)
typedef void (* SrvEvtCenterNewAlarmIdCB)(void *pThis, u32 nAlarmUserCode1, u32 nAlarmUserCode2);
//#define EVTCENTERSRV_EVT_StartDialogNotify                (CLSID_EVTCENTERSRV << 16 | 5)
typedef void (* SrvEvtCenterStartDialogNotifyCB)(void *pThis, EvtCenter_Dialog_Type_e eDialogType, u32 nMsgId);
//#define EVTCENTERSRV_EVT_EventHandleTypeNotify                (CLSID_EVTCENTERSRV << 16 | 11)
typedef void (* SrvEvtCenterEventHandleTypeNotifyCB)(void *pThis, EvtCenter_Event_Handle_Type_e eEventHandleType);

typedef void (* SrvEvtCenterMissCallLogChangeCB)(void *pThis, u16 nMissCallLogNum);
typedef void (* SrvEvtCenterSMSLogChangeCB)(void *pThis, u16 nSMSLogNum);
typedef void (* SrvEvtCenterCellBroadcastLogChangeCB)(void *pThis, u16 nCellBroadcastLogNum);
typedef void (* SrvEvtCenterMMSLogChangeCB)(void *pThis, u16 nMMSLogNum);
typedef void (* SrvEvtCenterVoiceMailLogChangeCB)(void *pThis, u16 nVoiceMailLogNum);
typedef void (* SrvEvtCenterAlarmLogChangeCB)(void *pThis, u16 nAlarmLogNum);
typedef void (* SrvEvtCenterBatteryLogChangeCB)(void *pThis, u16 nBatteryLogNum);
typedef void (* SrvEvtCenterOtherLogChangeCB)(void *pThis, u16 nOtherLogNum);
typedef void (* SrvEvtCenterShowDialogCB)(void *pThis, u32 nParam);
typedef void (* SrvEvtCenterDialogKeyPressCB)(void *pThis, u32 nMsgId);

/** SrvEventCenterSetxxxCB
@brief  Add a CB to EvtCenter obex.

@param[in]      pfnCallBack             the function which will be called to notify the detection of specific value change.
*/
void SrvEvtCenterSetNewMessageNumCB(SrvEvtCenterNewMessageNumCB pfnCallBack);

void SrvEvtCenterSetMissedCallNumCB(SrvEvtCenterMissedCallNumCB pfnCallBack);

void SrvEvtCenterSetNewAlarmIdCB(SrvEvtCenterNewAlarmIdCB pfnCallBack);

void SrvEvtCenterSetStartDialogNotifyCB(SrvEvtCenterStartDialogNotifyCB pfnCallBack);

void SrvEvtCenterSetEventHandleTypeNotifyCB(SrvEvtCenterEventHandleTypeNotifyCB pfnCallBack);


/** SrvEvtCenterSetxxxLogChangeCB
@brief  Add a CB to EvtCenter to ind the log data change.

@param[in]      pfnCallBack         the function which will be called to notify the detection of specific event.
*/
void SrvEvtCenterSetMissCallLogChangeCB(SrvEvtCenterMissCallLogChangeCB pfnCallBack);

void SrvEvtCenterSetSMSLogChangeCB(SrvEvtCenterSMSLogChangeCB pfnCallBack);

void SrvEvtCenterSetCellBroadcastLogChangeCB(SrvEvtCenterCellBroadcastLogChangeCB pfnCallBack);

void SrvEvtCenterSetMMSLogChangeCB(SrvEvtCenterMMSLogChangeCB pfnCallBack);

void SrvEvtCenterSetVoiceMailLogChangeCB(SrvEvtCenterVoiceMailLogChangeCB pfnCallBack);

void SrvEvtCenterSetAlarmLogChangeCB(SrvEvtCenterAlarmLogChangeCB pfnCallBack);

void SrvEvtCenterSetBatteryLogChangeCB(SrvEvtCenterBatteryLogChangeCB pfnCallBack);

void SrvEvtCenterSetOtherLogChangeCB(SrvEvtCenterOtherLogChangeCB pfnCallBack);
void SrvEvtCenterSetDialogKeyPressCB( SrvEvtCenterDialogKeyPressCB pfnCallBack );

/** SrvEvtCenterGetLastMessageID
@brief  The interface is use to get last Message ID by

@param[in]      eMsgType            Event model type reference of EvtCenter_Model_Index_e.

@retval Get message ID
*/
u32 SrvEvtCenterGetLastMessageID(EvtCenter_Model_Index_e eMsgType);

/** SrvEvtCenterGetLogRecordCountbyType
@brief  The interface is use to get count amount of log.

@param[in]      eLogType            Message log type

@retval Count amount info data
*/
u32 SrvEvtCenterGetLogRecordCountbyType(EvtCenter_Log_Type_e eLogType);

/** SrvEvtCenterGetAllLogRecordsbyType
@brief  The interface is use to get a type log point

@param[in]      eLogType            Message log type
@param[in]      pLogArray           ArrayClass_t pointer to insert data

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_READY           If EvtCenter Srv is already terminated.
@retval MAE_RET_FAILED              If GetLogdb fail.
*/
MAE_Ret SrvEvtCenterGetAllLogRecordsbyType(EvtCenter_Log_Type_e eLogType, ArrayClass_t *pLogArray);

/** SrvEvtCenterRemoveAllLogRecordsbyType
@brief  The interface is use to remove a type all log.

@param[in]      eLogType            Message log type

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_READY           If EvtCenter Srv is already terminated.
*/
MAE_Ret SrvEvtCenterRemoveAllLogRecordsbyType(EvtCenter_Log_Type_e pLogType);

/** SrvEvtCenterRemoveLogRecordbyID
@brief  The interface is use to remove one of register of a type log.

@param[in]      nLogID              One register of message log type
@param[in]      eLogType            Message log type

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_READY           If EvtCenter Srv is already terminated.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvEvtCenterRemoveLogRecordbyID(u32 nLogID, EvtCenter_Log_Type_e eLogType);

/** SrvEvtCenterGetEvtCenterLogStatus
@brief  The interface is use to get event center status

@param[out]   pEvtCenterStatus      Event center Log status data pointer to return

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_READY           If an error happen.
*/
MAE_Ret SrvEvtCenterGetEvtCenterLogStatus(EVTCenterStatus_t *pEvtCenterLogStatus);

/** SrvEvtCenterResetLogStatus
@brief  The interface is use to reset event.

@param[in]      eModelType          Event type
*/
void SrvEvtCenterResetLogStatus(EvtCenter_Model_Index_e eModelType);

/** SrvEvtCenterIgnoreBatteryEvent
@brief  The interface is use to set if the battery event need to check or Ignore

@param[in]      bCheck              TRUE/FALSE
*/
void SrvEvtCenterSetBatteryEventCheckOrNot(boolean bCheck);

/** SrvEvtCenterGetMissedEventCount
@brief  The interface is use to get amount of missed event count

@retval   Missed event count amount
*/
u32 SrvEvtCenterGetMissedEventCount(void);

/** SrvEvtCenterStopMelody
@brief   Stop current playing melody

@param[in]      eStopMelodyFor      Stop target normal or alivewidget
*/
void SrvEvtCenterStopMelody(EVTCenter_Alert_For_e eStopMelodyFor);

/** SrvEvtCenterGetNewMessageNum
@brief   Get new Message number

@param[in]  eMsgType                Message type which you want to get

@retval     New message count
*/
u32 SrvEvtCenterGetNewMessageNum(EvtCenter_Message_Type_e eMsgType);

/** SrvEvtCenterGetMissedCallNum
@brief  Get missed call number

@retval    Miss call status data pointer to return
*/
u32 SrvEvtCenterGetMissedCallNum(void);

/** SrvEvtCenterCleanMessageLog
@brief  The interface is use clean message log

@param[in]      eMsgType            Message log type
*/
void SrvEvtCenterCleanMessageLog(EvtCenter_Message_Type_e eMsgType);

/** SrvEvtCenterGetAlarmUserCode
@brief  The interface is use to get alarm user data

@retval    User set alarm data.
*/
u32 SrvEvtCenterGetAlarmUserCode(void);

/** SrvEventCenterIsLastMMSComplete
@brief   Check if the last MMS complete or not

@retval	TRUE		MMS is complete.
@retval FALSE		MMS is not complete
*/
boolean SrvEvtCenterIsLastMMSComplete(void);

/** SrvEvtCenterSetEventHandleType
@brief   Set event handle type and send notify too.

@param[in]      pType               Event handle type
*/
void SrvEvtCenterSetEventHandleType(EvtCenter_Event_Handle_Type_e pType);

/** SrvEvtCenterGetEventHandleType
@brief   Get event handle type

@retval  Event handle type
*/
EvtCenter_Event_Handle_Type_e SrvEvtCenterGetEventHandleType(void);

/** SrvEvtCenterCloseAlarmDialog
@brief  This function is to close dialog that match the nAlarmuserCode.

@param[in]      eLnAlarmUserCodeogType  Close alarm type
*/
void SrvEvtCenterCloseAlarmDialog(u32 nAlarmUserCode);

/** SrvEvtCenterProcessKeyguardNotice
@brief   Process keyguard app notice event

@param[in]      nMsgId                  Message ID
@param[in]      eDialogEvt              Dialog type status
*/
void SrvEvtCenterProcessKeyguardNotice(u32 nMsgId, EvtCenter_Keyguard_Evt_e eDialogEvt);

/** SrvEvtCenterHomeAPReadyForEventReminder
@brief   HomeAPReady: Home AP is ready. The event reminder could start if home AP and other service are ready.
*/
void SrvEvtCenterHomeAPReadyForEventReminder(void);

/** SrvEvtCenterGetCurrentDialogInfo
@brief   Get Current Dialog information. If no dialog, return MAE_RET_NOT_FOUND.
		 [Note]The Dialog String will alloc and copy to  ppDialogString ;Remember to Free ppDialogString by AP Self

@param[in]      pnID                    The MsgId which Msg is being answered
@param[in]      pDialogType             Dialog type of EventCenter
@param[in]      ppDialogStringpLogType  Dialog show string
@param[out]      pDialogTimer           Dialog timer

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_ILLEGAL_OPERATION       If EvtCenter Srv is already terminated.
@retval MAE_RET_NOT_FOUND               If not found in array model.
*/
MAE_Ret SrvEvtCenterGetCurrentDialogInfo(u32 *pnID,
                                         EvtCenter_Dialog_Type_e *pDialogType,
                                         MAE_WChar **ppDialogString,
                                         u32 *pDialogTimer);

/** SrvEvtCenterGetDialogInfoByID
@brief   Get Dialog info by Dialog ID
		 [Note]The Dialog String will alloc and copy to  ppDialogString ;Remember to Free ppDialogString by AP Self

@param[in]      nId                         The MsgId which Msg is being answered
@param[in]      pDialogType                 Dialog type of EventCenter
@param[in]      ppDialogStringpLogType      Dialog show string
@param[out]     pDialogTimer                Dialog timer

@retval MAE_RET_SUCCESS                     If successful.
@retval MAE_RET_NOT_FOUND                   If not found in array model.
*/
MAE_Ret SrvEvtCenterGetDialogInfoByID(u32 nId,
									  EvtCenter_Dialog_Type_e *pDialogType,
									  MAE_WChar **ppDialogString,
									  u32 *pDialogTimer);

/** SrvEvtCenterToShowDialog
@brief   Show dialog
		 [Note] Show dialog and register one callback to get the response about dialog

@param[in]      pfnCallBack                 receive the operation about dialog

@retval MAE_RET_SUCCESS                     If successful.
*/

MAE_Ret SrvEvtCenterToShowDialog( SrvEvtCenterShowDialogCB pfnCallBack );

#endif //__MMI_SRV_EVTCENTER_H__
/*-----------------------------------------------------*/
