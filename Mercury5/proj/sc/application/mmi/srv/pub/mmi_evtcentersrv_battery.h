#ifndef __MMI_EVTCENTERSRV_BATTERY_H__
#define __MMI_EVTCENTERSRV_BATTERY_H__
//#include "mmi_mae_battery.h"
#include "mmi_evtcentersrv_priv.h"

__SLDPM_FREE__ void _EVTCENTERSRV_BattModelListener(void *pUsrData, ModelEvent_t *pMdlEvent);
__SLDPM_FREE__ void _EVTCENTERSRV_ProcessBattModelListener(MMI_EVTCENTERSRV *pThis, ModelEvent_t *pMdlEvent);

#endif //__MMI_EVTCENTERSRV_BATTERY_H__
