/**
 * @file    mmi_vtccsrv_crunch.h
 * @brief   xxxx
 * @version $Id: mmi_vtccsrv_crunch.h $
 */
#ifndef __MMI_VTCCSRV_CRUNCH_H__
#define __MMI_VTCCSRV_CRUNCH_H__

#include "mmi_vtccsrv_priv.h"

#ifdef __VT_3G324M__

void VTCCSRV_CrunchForReleaseInd(MMI_VTCCSRV *pThis, void *pSM, u8 u8RelCallID);
boolean VTCCSRV_CrunchForRingInd(MMI_VTCCSRV *pThis, void *pSM);

void VTCCSRV_CrunchForCallRefIDInd(MMI_VTCCSRV *pThis, void *pSM);
void VTCCSRV_CrunchForAlertInd(MMI_VTCCSRV *pThis, void *pSM);
void VTCCSRV_CrunchForProgressInd(MMI_VTCCSRV *pThis, SM_t *pSM);
void VTCCSRV_CrunchForMakeCallCnf(MMI_VTCCSRV *pThis, void *pSM);
void VTCCSRV_CrunchForAcceptCallCnf(MMI_VTCCSRV *pThis, void *pSM, u32 Result, VTCCSRV_Mode_e VTCCSrvMode);
void VTCCSRV_CrunchForChldRejectWaitingCall(MMI_VTCCSRV *pThis, void *pSM);
void VTCCSRV_CrunchForChldRelActiveAnswerWaitingCall(MMI_VTCCSRV *pThis, void *pSM);

VTCCSRV_MO_ERROR_CODE VTCCSRV_CrunchForMakeCall(MMI_VTCCSRV *pThis, MmiMakeCallReq_t *pVTCCSRVMakeCallData);

boolean VTCCSRV_CrunchLaunchVTCCMTA(MMI_VTCCSRV *pThis, void *pSM, VTCCSRV_MT_TYPE_E type);

boolean VTCCSRV_CrunchCheckBlackList(MMI_VTCCSRV *pThis, void *pSM);
MAE_Ret VTCCSRV_CrunchExecuteNextCHLD(MMI_VTCCSRV *pThis, MMI_VTCCSRV_Status_e eFilterID, u8 u8ChldOperFlag);

///
void VTCCSRV_CrunchForCallDropRequest(MMI_VTCCSRV *pThis);

#endif //__VT_3G324M__
#endif /* __MMI_VTCCSRV_CRUNCH_H__ */

