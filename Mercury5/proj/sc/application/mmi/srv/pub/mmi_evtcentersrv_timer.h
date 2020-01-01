#ifndef __MMI_EVTCENTERSRV_TIMER_H__
#define __MMI_EVTCENTERSRV_TIMER_H__

#include "mmi_evtcentersrv_priv.h"

void _EVTCENTERSRV_Timer_CallBack(void *pHandler);
void _EVTCENTERSRV_CreateRingTimer(MMI_EVTCENTERSRV *pThis, u32 nTimer); //
void _EVTCENTERSRV_CancelRingTimer(MMI_EVTCENTERSRV *pThis);

#endif //__MMI_EVTCENTERSRV_TIMER_H__
