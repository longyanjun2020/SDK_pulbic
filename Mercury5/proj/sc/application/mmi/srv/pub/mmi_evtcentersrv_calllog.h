#ifndef __MMI_EVTCENTERSRV_CALLLOG_H__
#define __MMI_EVTCENTERSRV_CALLLOG_H__

#include "mmi_evtcentersrv_priv.h"

void _EVTCENTERSRV_CallLogModelListener(void *pUserData, ModelEvent_t *pMdlEvent);
void _EVTCENTERSRV_ProcessCallLogModelListener(MMI_EVTCENTERSRV *pThis, ModelEvent_t *pMdlEvent);
void _EVTCENTERSRV_FlushAPStackCB_CallLog(IBase *pObj, u32 bCompleted);
void _EVTCENTERSRV_MissCallResumeCallback(IBase *pUser, u32 Param);

#endif //__MMI_EVTCENTERSRV_CALLLOG_H__
