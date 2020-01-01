#ifndef __MMI_EVTCENTERSRV_MODEL_H__
#define __MMI_EVTCENTERSRV_MODEL_H__

#include "mmi_evtcentersrv_priv.h"

void _EVTCENTERSRV_FreeModelItem(void *pData, IBase *pOwner);
void _EVTCENTERSRV_StatusModelNotify(MMI_EVTCENTERSRV *pThis, u32 nEvtCode, u32 evtParam);

#endif //__MMI_EVTCENTERSRV_MODEL_H__
