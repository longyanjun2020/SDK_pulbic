#ifndef __MMI_EVTCENTERSRV_LOGMSG_H__
#define __MMI_EVTCENTERSRV_LOGMSG_H__

#include "mmi_evtcentersrv_priv.h"

MAE_Ret _EVTCENTERSRV_LogMsgToDB(MMI_EVTCENTERSRV *pThis, u32 nLogTextID, MAE_WChar *pLogStr, EvtCenter_Log_Type_e eType); //13
MAE_Ret _EVTCENTERSRV_CreateLogItem(MMI_EVTCENTERSRV *pThis, u16 MsgId, MAE_WChar *pLogText, EvtCenter_Dialog_Type_e nType, u32 nDialogTimer, u32 param, u32 nLogTextID, LOGDATAFREE_FUNC_PTR pfnFuncFree);
void _EVTCENTERSRV_FreeLogItem(void *pData, IBase *pOwner);
u16 _EVTCENTERSRV_GetNextID(MMI_EVTCENTERSRV *pThis);
MAE_Ret _EVTCENTERSRV_FindLogItemFromQueue(MMI_EVTCENTERSRV *pThis, u16 MsgId, EVTCenter_Log_Item_t **ppLogItem, u32 *nIndexFound); //3
MAE_Ret _EVTCENTERSRV_IsDialogTypeLogItemInQueue(MMI_EVTCENTERSRV *pThis, EvtCenter_Dialog_Type_e eDialogType);

void _EVTCENTERSRV_HandleLogItem(MMI_EVTCENTERSRV *pThis, EVTCenter_Log_Item_t *pLogItem, u32 nEvtCode);
MAE_Ret _EvtCenterSrvPlayMelodyFromRaw(MMI_EVTCENTERSRV *pThis, u32 nRingerID, u32 nTimeOut,EvtCenter_Dialog_Type_e eDialogType);

#endif //__MMI_EVTCENTERSRV_LOGMSG_H__
