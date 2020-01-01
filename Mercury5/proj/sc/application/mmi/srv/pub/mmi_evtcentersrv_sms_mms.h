#ifndef __MMI_EVTCENTERSRV_SMS_MMS_H__
#define __MMI_EVTCENTERSRV_SMS_MMS_H__

#include "mmi_evtcentersrv_priv.h"

#define SMS_IS_UNABLE_TO_RECEIVE    0xFFFF

void _EVTCENTERSRV_FlushAPStackCB_SMS(IBase *pObj, u32 bCompleted);
void _EVTCENTERSRV_FlushAPStackCB_MMS(IBase *pObj, u32 bCompleted);
boolean _EVTCENTERSRV_HandleSMSBGSending(MMI_EVTCENTERSRV *pThis, u32 nSuccess, u32 nFail);
boolean _EVTCENTERSRV_HandleSMSUnableToReceiveInd(MMI_EVTCENTERSRV *pThis, u32 param1, u32 param2);
#ifdef __MMS_MMI_CDMMS__
//boolean _EVTCENTERSRV_HandleMMSCancelFail(MMI_EVTCENTERSRV* pThis, u32 nSuccess, u32 nFail);
//boolean _EVTCENTERSRV_HandleMMSCancelSuccess(MMI_EVTCENTERSRV* pThis, u32 nSuccess, u32 nFail);
//boolean _EVTCENTERSRV_HandleMMSSendSuccess(MMI_EVTCENTERSRV* pThis, u32 nSuccess, u32 nFail);
__SLDPM_FREE__ boolean _EVTCENTERSRV_HandleMMSNewInd(MMI_EVTCENTERSRV *pThis, u32 nMsgID, EVTMMS_NewIndication_e type);
boolean _EVTCENTERSRV_HandleMMSRetrieveFail(MMI_EVTCENTERSRV *pThis, u32 nMsgID, u32 ret);
boolean _EVTCENTERSRV_HandleMMSRetrieveFailNoStorage(MMI_EVTCENTERSRV *pThis, u32 nMsgID);
boolean _EVTCENTERSRV_HandleMMSRetrieveFailOverSize(MMI_EVTCENTERSRV *pThis, u32 pMsgID);
boolean _EVTCENTERSRV_HandleMMSSendFail(MMI_EVTCENTERSRV *pThis, u32 nCount);
__SLDPM_FREE__ boolean _EVTCENTERSRV_HandleMMSDeliveryReportInd(MMI_EVTCENTERSRV *pThis, u32 param1, u32 param2);
#ifdef __MMS_READ_REPORT__
boolean _EVTCENTERSRV_HandleMMSReadReportInd(MMI_EVTCENTERSRV *pThis, u32 param1, u32 param2);
#endif
MAE_Ret _EVTCENTERSRV_StartMMSMCA(MMI_EVTCENTERSRV *pThis, u32 nMsgID, u32 nNewMsg, MsgType_e nViewerType, boolean completeFlag);
#endif //__MMS_MMI_CDMMS__


#endif //__MMI_EVTCENTERSRV_SMS_MMS_H__
