/**
* @file    mmi_srv_alarm.h
* @brief
*
*/

#ifndef __MMI_SRV_ALARM_H__
#define __MMI_SRV_ALARM_H__


#include "mmi_srv_client_commondefine.h"
#include "mmi_alarmsrv.h"

typedef void (*SrvAlarmAlarmExpireCB)(void *pThis, ALARMSRV_ALARMALERTDATA_t *pAlarmAlertData);

/** SrvAlarmSetAlarmExpireCB
@brief  Set the callback function to execute when Alarm Expire happen

@param[in]      pfnCallBack         Call back function point, it will be trigger when the Alarm Expire happen

@retval  MAE_RET_SUCCESS            If successful.
@retval  MAE_RET_NOT_READY          If AlarmSrv is terminated.
*/
MAE_Ret SrvAlarmSetAlarmExpireCB(SrvAlarmAlarmExpireCB pfnCallBack);

typedef void (*SrvAlarmAutoPowerOnAlarmExpireCB)(void *pThis);

/** SrvAlarmSetAutoPowerOnAlarmExpireCB
@brief  Set the callback function to execute when AutoPowerOn Alarm Expire

@param[in]      pfnCallBack         Call back function point, it will be trigger when the AutoPowerOn Alarm Expire happen

@retval  MAE_RET_SUCCESS            If successful.
@retval  MAE_RET_NOT_READY          If AlarmSrv is terminated.
*/
MAE_Ret SrvAlarmSetAutoPowerOnAlarmExpireCB(SrvAlarmAutoPowerOnAlarmExpireCB pfnCallBack);

typedef void (*SrvAlarmExpiredAlarmCloseCB)(void *pThis, u32 nExpiredAlarmUserCode, u32 nAlarmAlertReply);

/** SrvAlarmSetExpiredAlarmCloseCB
@brief  Set the callback function to execute when expire alarm expire is close

@param[in]      pfnCallBack         Call back function point trigger when the expire alarm expire is close

@retval  MAE_RET_SUCCESS            If successful.
@retval  MAE_RET_NOT_READY          If AlarmSrv is terminated.
*/
MAE_Ret SrvAlarmSetExpiredAlarmCloseCB(SrvAlarmExpiredAlarmCloseCB pfnCallBack);


/** SrvAlarmOpenAlarmAlert
@brief only use in OnApp/AlarmApp to ask AlarmSrv to launch alarm alert dialog.

@param[in]      pAlarmExpiredData	AlarmExpireData to describe the alarm type

@retval  MAE_RET_SUCCESS            If successful.
@retval  MAE_RET_FAILED             If it is not power off alert.
*/
MAE_Ret SrvAlarmOpenAlarmAlert(ALARMSRV_ALARMEXPIREDDATA_t *pAlarmExpiredData);

/** SrvAlarmCloseAlarmAlert
@brief  AlarmSrv to notify OnApp or AlarmApp about what action happened on the alarm alert dialog.

@param[in]      nUserCode           User code.
@param[in]      eReplyValue         replay value. Please reference to ALARMSRV_ALARMALERTREPLY_e.

@retval  MAE_RET_SUCCESS            If successful.
@retval  MAE_RET_NOT_READY          If AlarmSrv is terminated.
*/
MAE_Ret SrvAlarmCloseAlarmAlert(u32 nUserCode, ALARMSRV_ALARMALERTREPLY_e eReplyValue);

/** SrvAlarmSetAlarm
@brief  Set alarm based on the class id and alarm cause.

@param[in]      nClsID              Class ID.
@param[in]      eAlarmCause         Alarm cause. Please reference to ALARMSRV_ALARMCAUSE_e.
@param[in]      pAlarmTime          Set alarm time.
@param[in]      nUserCode           User code.

@retval  MAE_RET_SUCCESS            If successful.
@retval  MAE_RET_BAD_PARAM          If input parameter error.
@retval  MAE_RET_NOT_READY          If AlarmSrv is terminated.
*/
MAE_Ret SrvAlarmSetAlarm(MAE_ClsId nClsID,
                         ALARMSRV_ALARMCAUSE_e eAlarmCause,
                         MAE_DateTime_t *pAlarmTime,
                         u32 nUserCode);

/** SrvAlarmCancelAlarm
@brief  This function is cancel the request of alarm which is set by IALARM_SetAlarm.
        Cancel alarm based on the class id and alarm cause.

@param[in]      nClsID              Class ID.
@param[in]      eAlarmCause         Alarm cause. Please reference to ALARMSRV_ALARMCAUSE_e.
@param[in]      nUserCode           User code.

@retval  MAE_RET_SUCCESS            If successful.
@retval  MAE_RET_NOT_FOUND          not found alarm with same Cls ID and userCode.
*/
MAE_Ret SrvAlarmCancelAlarm(MAE_ClsId nClsID, ALARMSRV_ALARMCAUSE_e eAlarmCause, u32 nUserCode);

/** SrvAlarmSuspendAlarm
@brief  This function is to turned off Alarm temporarily. All registrations are not cleared but suspend.
		Used in the scenario like airplane mode.

@retval  MAE_RET_SUCCESS            If successful.
@retval  MAE_RET_NOT_READY          If AlarmSrv is terminated.
*/
MAE_Ret SrvAlarmSuspendAlarm(void);

/** SrvAlarmResumeAlarm
@brief  This function is pair of suspend and used to turned on Alarm, and Alarm will Expire when the time is up.

@retval  MAE_RET_SUCCESS            If successful.
@retval  MAE_RET_NOT_READY          If AlarmSrv is terminated.
*/
MAE_Ret SrvAlarmResumeAlarm(void);

typedef void (*SrvAlarmCheckExistCnfCB)(void *pThis, boolean bExist);

/** SrvAlarmCheckAlarmExistReq
@brief  This function is used for checking if the specific type alarm exists.

@param[in]      eAlarmCause			specific type alarm, reference of ALARMSRV_ALARMCAUSE_e

@retval  MAE_RET_SUCCESS            If successful.
@retval  MAE_RET_NOT_READY          If AlarmSrv is terminated.
*/
MAE_Ret SrvAlarmCheckAlarmExistReq(ALARMSRV_ALARMCAUSE_e eAlarmCause, SrvAlarmCheckExistCnfCB pfnCallBack);

/** SrvAlarmSetAlarmClockAlarm
@brief  This function is setting alarm for an alarm record when it was created.

@param[in]      nAlarmUID           Alarm UID.
@param[in]      pAlarmRecord        Alarm record data structure. Please reference to ALARM_RECORD_t.

@retval  MAE_RET_SUCCESS            If successful.
@retval  MAE_RET_NOT_READY          If AlarmSrv is terminated.
*/
MAE_Ret SrvAlarmSetAlarmClockAlarm(u32 nAlarmUID, ALARM_RECORD_t *pAlarmRecord);

#ifdef __APP_MMI_FM_SCHEDULE__
/** SrvAlarmSetFmradioRecAlarm
@brief  This function is setting Fmradio record alarm for an alarm record when it was created.

@param[in]      nAlarmUID           Alarm UID.
@param[in]      pFmrRecord        Fmradio record data structure. Please reference to FMRECSCH_ENTITY_t.

@retval  MAE_RET_SUCCESS            If successful.
@retval  MAE_RET_NOT_READY          If AlarmSrv is terminated.
*/
MAE_Ret  SrvAlarmSetFmradioRecAlarm(u32 nAlarmUID, FMRECSCH_ENTITY_t *pFmrRecord);

/** SrvAlarmSetFmradioPlayAlarm
@brief  This function is setting Fmradio play alarm for an alarm record when it was created.

@param[in]      nAlarmUID           Alarm UID.
@param[in]      pFmrPlay        Fmradio play data structure. Please reference to FMSCH_ENTITY_t.

@retval  MAE_RET_SUCCESS            If successful.
@retval  MAE_RET_NOT_READY          If AlarmSrv is terminated.
*/
MAE_Ret  SrvAlarmSetFmradioPlayAlarm(u32 nAlarmUID, FMSCH_ENTITY_t *pFmrPlay);
#endif
#ifdef __APP_MMI_SOHU_UPDATER__
MAE_Ret  SrvAlarmSetSOHUUpdateAlarm(u32 nAlarmUID, SOHU_ENTITY_t *pFmrPlay);
#endif

/** SrvAlarmSetupAzanAlarm
@brief  This function is setting Fmradio play alarm for an alarm record when it was created.

@param[in]      nAlarmUID           Alarm UID.
@param[in]      pAzanRecord         data structure of Azan record. Please reference to Azan_Entry_t.

@retval  MAE_RET_SUCCESS            If successful.
@retval  MAE_RET_NOT_READY          If AlarmSrv is terminated.
*/
MAE_Ret SrvAlarmSetupAzanAlarm(void);

#endif /*__MMI_SRV_ALARM_H__*/
