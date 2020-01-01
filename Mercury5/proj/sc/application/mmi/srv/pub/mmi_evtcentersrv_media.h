#ifndef __MMI_EVTCENTERSRV_MEDIA_H__
#define __MMI_EVTCENTERSRV_MEDIA_H__

#include "mmi_evtcentersrv_priv.h"

static void _EvtCenterSrvPlayMelodyCb(void *pIEVTCENTERSRV, MediaSrvErrCode_e eErrorCode);
static void _EvtCenterSrvStopMelodyCb(void *pThis, MediaSrvErrCode_e eErrorCode);
void _EvtCenterSrvInterruptNotifyCb(void *pUserData, u32 nCusData, MediaSrvInterruptStatus_e eStatus);
void _EvtCenterSrvPlayStatusChangeCb(void *pUserData, u32 nCusData, AudioSrvPlayStatusEvent_e eEventId, u32 nInfoData);
/** _EvtCenterSrvPlayRinger
@brief  The interface is use to play ringtone for a notification dialog.

@param[in]      eDialogType             Eventcenter dialog type reference of EvtCenter_Dialog_Type_e.
@param[in]      DialogStatus            Eventcenter dialog Start type reference of Dialog_Start_e.
@param[in]      nMsgId            		Eventcenter dialog logitem id.Created by _EVTCENTERSRV_GetNextID(). 0 means alivewidget play ringer
@param[in]      nRingerID            	Eventcenter dialog ringer id.
@param[in]      eAlertFor            	Eventcenter dialog alert mode reference of EVTCenter_Alert_For_e.

@retval void
*/
MAE_Ret _EvtCenterSrvPlayRinger(MMI_EVTCENTERSRV *pThis, EvtCenter_Dialog_Type_e eDialogType, Dialog_Start_e DialogStatus, u32 nMsgId, u32 nRingerID, EVTCenter_Alert_For_e eAlertFor);
MAE_Ret _EvtCenterSrvPlayMelodyFromURL(MMI_EVTCENTERSRV *pThis, MAE_WChar *pRingerURL, EvtCenter_Dialog_Type_e eDialogType);
void _EvtCenterSrvPeriodicRingerCB(void *data);
void _EvtCenterSrvRingTimeout(void *data);
boolean _EvtCenterSrvHandleBTAudioLink(MMI_EVTCENTERSRV *pThis, BTSRV_AudioLink_e connect, u16 *Name);
void _EvtCenterSrvSetVibration(MMI_EVTCENTERSRV *pThis, ACCVibrateAction_e eVibrateAction, u32 nVibMsec);
void _EvtCenterSrvStopMelody(MMI_EVTCENTERSRV *pThis);
void _EvtCenterSrvStopAlarmMelody(MMI_EVTCENTERSRV *pThis);
void _EvtCenterSrvVibrateCB(void *data);
void _EvtCenterSrvStartFmrRec(MMI_EVTCENTERSRV *pThis, u32 nUId, boolean bPowerOff);
void _EvtCenterSrvStartFmrPlay(MMI_EVTCENTERSRV *pThis, u32 nUId, boolean bPowerOff);

#endif //__MMI_EVTCENTERSRV_MEDIA_H__
