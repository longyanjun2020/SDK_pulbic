#ifndef __MMI_EVTCENTERSRV_ALARM_H__
#define __MMI_EVTCENTERSRV_ALARM_H__

#include "mmi_evtcentersrv_priv.h"

MAE_Ret _EVTCENTERSRV_GetCalendarEventAlertData(u32 nEventUID, AlertDisplayType_e eDisplayType, MAE_WChar **ppAlertStr, u32 *pSnoozeCount, IBase *pOwner);
void _EVTCENTERSRV_AlarmModelListener(void *pUserData, ModelEvent_t *pMdlEvent);
void _EVTCENTERSRV_ProcessAlarmModelListener(MMI_EVTCENTERSRV *pThis, ModelEvent_t *pMdlEvent);

#endif //__MMI_EVTCENTERSRV_ALARM_H__
