#ifndef __MMI_EVTCENTERSRV_ACCESSORY_H__
#define __MMI_EVTCENTERSRV_ACCESSORY_H__

#include "mmi_evtcentersrv_priv.h"

void _EVTCENTERSRV_AccessoryMdlListener(void *pData, ModelEvent_t *pMdlEvent);
void _EVTCENTERSRV_ProcessAccessoryMdlListener(MMI_EVTCENTERSRV *pThis, ModelEvent_t *pMdlEvent);
void _EVTCENTERSRV_HandleAccDeviceErrorEvt(MMI_EVTCENTERSRV *pThis, ACCModelMessage_t *pACCMdlMsg);
void _EVTCENTERSRV_HandleAccPlugEvt(MMI_EVTCENTERSRV *pThis, ACCModelMessage_t *pACCMdlMsg);

#endif //__MMI_EVTCENTERSRV_ACCESSORY_H__
