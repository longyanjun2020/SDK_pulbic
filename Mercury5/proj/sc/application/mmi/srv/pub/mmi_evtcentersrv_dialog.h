#ifndef __MMI_EVTCENTERSRV_DIALOG_H__
#define __MMI_EVTCENTERSRV_DIALOG_H__

#include "mmi_evtcentersrv_priv.h"

void _EVTCENTERSRV_DialogModelListener(void *pUsrData, ModelEvent_t *pMdlEvent);
void _EVTCENTERSRV_DialogActionModelNotify(MMI_EVTCENTERSRV *pThis, u32 nEvtCode, u32 evtParam);
void _EVTCENTERSRV_StartDialogAPCB(void *StartCallBackData, Dialog_Start_e StartStatus);
MAE_Ret _EVTCENTERSRV_StartDialogAP(MMI_EVTCENTERSRV *pThis, MAE_WChar *pDialogMsg, EvtCenter_Dialog_Type_e eDialogType, u16 nDialogViewID, SoftkeyID_e nLSK, SoftkeyID_e nCSK, SoftkeyID_e nRSK, u32 nAutoCloseTimer, u32 MsgId, IModel *pIModel, boolean bPlayMelody, u32 nMelodyID);

#ifdef __SXMENGINE__
MAE_Ret _EVTCENTERSRV_SendVideoChatReq(MMI_EVTCENTERSRV* pThis);
MAE_Ret _EVTCENTERSRV_StartVideoChatDlg(MMI_EVTCENTERSRV* pThis);       // add for videochat
MAE_Ret _EVTCENTERSRV_HandleVideoChatEvent(MMI_EVTCENTERSRV* pThis, EVTCenter_Log_Item_t* pLogItem, u32 nEvtCode);
#endif

void _EVTCENTERSRV_CleanFuncDialogAP(IBase *pIssuer, u32 Param);
void _EVTCENTERSRV_CheckDialogQueue(IBase *pUser, u32 Param);
void _EVTCENTERSRV_ProcessDialog(MMI_EVTCENTERSRV *pThis, u32 nMsgId, u32 nEvtCode);
//void _EVTCENTERSRV_ProcessDialogModelListener(MMI_EVTCENTERSRV *pThis, ModelEvent_t *pMdlEvent);
void _EVTCENTERSRV_FreeDialogItem(void *pData, IBase *pOwner);
void _EVTCENTERSRV_DeleteLogByDialogType(MMI_EVTCENTERSRV *pThis, EvtCenter_Dialog_Type_e DialogType); //6
MAE_Ret _EVTCENTERSRV_HandleMessageDialogEvent(MMI_EVTCENTERSRV *pThis, EVTCenter_Log_Item_t *pLogItem, u32 nEvtCode);
MAE_Ret _EVTCENTERSRV_HandleMissedCallDialogEvent(MMI_EVTCENTERSRV *pThis, EVTCenter_Log_Item_t *pLogItem, u32 nEvtCode);
MAE_Ret _EVTCENTERSRV_HandleAlarmDialogEvent(MMI_EVTCENTERSRV *pThis, EVTCenter_Log_Item_t *pLogItem, u32 nEvtCode);
MAE_Ret _EVTCENTERSRV_HandleTaskDialogEvent(MMI_EVTCENTERSRV *pThis, EVTCenter_Log_Item_t *pLogItem, u32 nEvtCode);
MAE_Ret _EVTCENTERSRV_CloseAlarmDialog(MMI_EVTCENTERSRV *pThis, ALARMSRV_ALARMALERTDATA_t *pAlarmAlertData, ALARMSRV_ALARMALERTREPLY_e eAlarmAlertReply, boolean bIsSnoozed);
MAE_Ret _EVTCENTERSRV_HandleMMDialogEvent(MMI_EVTCENTERSRV *pThis, EVTCenter_Log_Item_t *pLogItem, u32 nEvtCode);
MAE_Ret _EVTCENTERSRV_HandleMMSyncTimezoneDialogEvent(MMI_EVTCENTERSRV *pThis, EVTCenter_Log_Item_t *pLogItem, u32 nEvtCode);
#ifdef __MMI_SWITCH_MODE_WHEN_NO_NETWORK__
MAE_Ret _EVTCENTERSRV_HandleMMSwitchSimDialogEvent(MMI_EVTCENTERSRV *pThis, EVTCenter_Log_Item_t *pLogItem, u32 nEvtCode);
#endif // __MMI_SWITCH_MODE_WHEN_NO_NETWORK__
MAE_Ret _EVTCENTERSRV_HandlePhonebookDialogEvent(MMI_EVTCENTERSRV *pThis, EVTCenter_Log_Item_t *pLogItem, u32 nEvtCode);
MAE_Ret _EVTCENTERSRV_HandleBTDialogEvent(MMI_EVTCENTERSRV *pThis, EVTCenter_Log_Item_t *pLogItem, u32 nEvtCode);
MAE_Ret _EVTCENTERSRV_HandleDialogEvent(MMI_EVTCENTERSRV *pThis, EVTCenter_Log_Item_t *pLogItem, u32 nEvtCode);
void _EVTCENTERSRV_ShowSyncSIMPhonebookDialog(MMI_EVTCENTERSRV *pThis, u8 nSIMModule);
void _EVTCENTERSRV_ShowPhoneFullDialog(MMI_EVTCENTERSRV *pThis);
#ifdef __BLUETOOTH_OBEX_MMI__
void _EVTCENTERSRV_ShowBTDialog(MMI_EVTCENTERSRV *pThis, MAE_EventId eventID, BTSRV_TRANS_RESULT_e eTransResult, BTSRV_RecvInfoForDialog_t *pInfoForDialog);
#endif
boolean _EVTCENTERSRV_HandleShowDialog(MMI_EVTCENTERSRV *pThis, MAE_EventId nEventID, u32 param1, u32 param2);
boolean _EVTCENTERSRV_ShowDialog(MMI_EVTCENTERSRV *pThis, EVTCENTERSRV_DialogParamData_t *pDialogParam);

void _EVTCENTERSRV_ProcessDialogQueue(MMI_EVTCENTERSRV *pThis);
void _EVTCENTERSRV_Timer_CallBack_MissCallDialog(void *pHandler);
void _EVTCENTERSRV_UpdateDialogNewMsgNumber(MMI_EVTCENTERSRV *pThis);

#ifdef __APP_MMI_ANSWERING_MACHINE__
void _EVTCENTERSRV_Timer_CallBack_NewVoiceBoxDialog(void *pHandler);
void _EVTCENTERSRV_Timer_CallBack_AnsweringMachineFailedDialog(void *pHandler);
MAE_Ret _EVTCENTERSRV_HandleVoiceBoxDialogEvent(MMI_EVTCENTERSRV* pThis, EVTCenter_Log_Item_t* pLogItem, u32 nEvtCode);
#endif
/**
* This function shows countdown timer time dialog according to given text label.
*/
void _EVTCENTERSRV_ShowCountdownTimerDialogById(MMI_EVTCENTERSRV *pThis, u32 nTxtId);
#endif //__MMI_EVTCENTERSRV_DIALOG_H__
