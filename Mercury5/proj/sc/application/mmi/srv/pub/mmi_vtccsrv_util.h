/**
 * @file    mmi_vtccsrv_util.h
 * @brief   
 * @version $Id: mmi_vtccsrv_util.h $
 */
#ifndef __MMI_VTCCSRV_UTIL_H__
#define __MMI_VTCCSRV_UTIL_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_sm_defs.h"
#include "mmi_mae_datamodel.h"
#include "mmi_mae_notifier.h"
#include "mmi_vtccsrv_def.h"
#include "mmi_calllogsrv_def.h"

#ifdef __VT_3G324M__

MAE_Ret VTCCSRV_UtilRetrieveUnMsgfromCurrentEvent(void *pSM, VTCCSRV_unMsg_t **ppData, IDataModel **ppDataModel, IBase *pIBase);
CallTable_t *VTCCSRV_UtilGetCallTableFromDataModel(IDataModel *pDataModel);
MAE_Ret VTCCSRV_UtilGetAcceptCnf(IBase *pThis, void *pSM, u32 *result, u32 *cause);
MAE_Ret VTCCSRV_UtilGetReleaseInd(IBase *pThis, void *pSM, u32 *callRef, u32 *cause);

boolean VTCCSRV_UtilGetCallIDbyStatus(CallTable_t *pCallTable, MMI_VTCCSRV_Status_e QueryStatus, u8 *pAryID, u8 *pNum);
u8 VTCCSRV_UtilGetFirstCallIDbyStatus(CallTable_t *pCallTable, MMI_VTCCSRV_Status_e status);
boolean VTCCSRV_UtilIsIncomingCallExisted(CallTable_t *pCallTable, u8 u8CallID);
boolean VTCCSRV_UtilIsMPTYCallExisted(CallTable_t *pCallTable);
boolean VTCCSRV_UtilIsMPTYCallActive(CallTable_t *pCallTable);

u8 VTCCSRV_UtilGetOutgoingCallIndex(CallTable_t *pCallTable);
boolean VTCCSRV_UtilPutActiveCallsOnHold(CallTable_t *pCallTable);
boolean VTCCSRV_UtilRetrieveHeldCalls(CallTable_t *pCallTable);
boolean VTCCSRV_UtilAnswerWaitingCall(CallTable_t *pCallTable);
boolean VTCCSRV_UtilDeleteWaitingCall(CallTable_t *pCallTable);
boolean VTCCSRV_UtilDeleteIncomingCall(CallTable_t* pCallTable);
boolean VTCCSRV_UtilDeleteOneCallbyID(CallTable_t *pCallTable, u8 u8CallID, MMI_VTCCSRV_Status_e CallType);
void VTCCSRV_UtilDeleteAllXstatusCall(CallTable_t *pCallTable, MMI_VTCCSRV_Status_e CallType);
boolean VTCCSRV_UtilQueryCallStatusbyID(CallTable_t *pCallTable, u8 u8CallID, MMI_VTCCSRV_Status_e *pRet);
//boolean       VTCCSRV_UtilQueryCallStatusbyIndex(CallTable_t* pCallTable, u8 u8Index, MMI_VTCCSRV_Status_e* pRet);
boolean VTCCSRV_UtilIsJoinMPTYOperationAllow(CallTable_t *pCallTable);
boolean VTCCSRV_UtilIsSplitOperationAllow(CallTable_t *pCallTable, u8 u8CallID);
void VTCCSRV_UtilJoinMPTY(CallTable_t *pCallTable, boolean bMPTYValue);
void VTCCSRV_UtilSwapCallStatus(CallTable_t *pCallTable);
void VTCCSRV_UtilSplitCall(CallTable_t *pCallTable, u8 u8SplitCallID);
void VTCCSRV_UtilReturnFromBlackListMode(void *pSM, u8 RetFlag);

u32 VTCCSRV_UtilGetMTDualStatus(void *pSM);
void VTCCSRV_UtilSetDualModeStatus(IBase *pIBase, u8 u8DualMode);           

void VTCCSRV_UtilAddCallLog(IBase *pIBase, u8 DualType, MMI_CALLLOG_TYPE_E CalllogType, u8 *u8CallNumber);
void VTCCSRV_UtilAddCallDuration(IBase *pIBase, u8 DualType, u32 u32MODuration, u32 u32MTDuration, u32 u32LastDuration);
void VTCCSRV_UtilAddCallDurationHandler(IBase *pIBase, u8 DualType, u8 u8CallID, CallTable_t *pCallTable);
VTCCSRV_NUMBER_Type_e VTCCSRV_UtilGetNumberType(u8 *pNumber);
MAE_Ret VTCCSRV_UtilGetCallNumberByWaitingStatus(CallTable_t *pCallTable, u8 *pCallNumber, u8 *u8NumberType);
u32 VTCCSRV_UtilCountTimeDuration(u32 u32StartTime, u32 u32EndTime, u32 u32MinuteTick);
void VTCCSRV_UtilSyncCTbyCLCC(CallTable_t *pCallTable, VTCCSRV_ClccCnf_t *pClccCnf);

#endif //__VT_3G324M__
#endif /* __MMI_VTCCSRV_UTIL_H__ */

