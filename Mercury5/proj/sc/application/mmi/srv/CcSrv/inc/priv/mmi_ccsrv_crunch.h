/**
 * @file    mmi_ccsrv_crunch.h
 * @brief   xxxx
 * @version $Id: mmi_ccsrv_crunch.h 40036 2009-09-11 12:34:27Z lih.wang $
 */
#ifndef __MMI_CCSRV_CRUNCH_H__
#define __MMI_CCSRV_CRUNCH_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_ccsrv_priv.h"
#include "mmi_vendorsrv.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Local function prototype declaration and definition
/*=============================================================*/

void CCSRV_CrunchForReleaseInd(MMI_CCSRV *pThis, void *pSM, u8 u8RelCallID);
boolean CCSRV_CrunchForRingInd(MMI_CCSRV *pThis, void *pSM);

void CCSRV_CrunchForCallRefIDInd(MMI_CCSRV *pThis, void *pSM);
void CCSRV_CrunchForAlertInd(MMI_CCSRV *pThis, void *pSM);
void CCSRV_CrunchForProgressInd(MMI_CCSRV *pThis, SM_t *pSM);
void CCSRV_CrunchForMakeCallCnf(MMI_CCSRV *pThis, void *pSM);
void CCSRV_CrunchForAcceptCallCnf(MMI_CCSRV *pThis, void *pSM, u32 Result, CCSRV_Mode_e CCSrvMode);
void CCSRV_CrunchForChldRejectWaitingCall(MMI_CCSRV *pThis, void *pSM);
void CCSRV_CrunchForChldRelActiveAnswerWaitingCall(MMI_CCSRV *pThis, void *pSM);

CCSRV_MO_ERROR_CODE CCSRV_CrunchForMakeCall(MMI_CCSRV *pThis, MmiMakeCallReq_t *pCCSRVMakeCallData);

boolean CCSRV_CrunchLaunchCCMTA(MMI_CCSRV *pThis, void *pSM, CCSRV_MT_TYPE_E type);

boolean CCSRV_CrunchCheckBlackList(MMI_CCSRV *pThis, void *pSM);
MAE_Ret CCSRV_CrunchExecuteNextCHLD(MMI_CCSRV *pThis, MMI_CCSRV_Status_e eFilterID, u8 u8ChldOperFlag);

#ifdef __MMI_CALL_FIREWALL__
boolean CCSRV_CrunchCheckFirewall(MMI_CCSRV *pThis, void *pSM);
boolean CCSRV_CrunchCheckContactList(MMI_CCSRV *pThis);
void CCSRV_CrunchSetFirewallCause(MMI_CCSRV *pThis, boolean bSet);
#endif /* __MMI_CALL_FIREWALL__ */

VenSrv_Cc_Filter_t CCSRV_CrunchVendorFilter(MMI_CCSRV *pThis, void *pSM);	

#endif /* __MMI_CCSRV_CRUNCH_H__ */
