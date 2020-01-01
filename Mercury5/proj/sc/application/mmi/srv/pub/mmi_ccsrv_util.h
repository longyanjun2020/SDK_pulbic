/**
 * @file    mmi_ccsrv_util.h
 * @brief   xxxx
 * @version $Id: mmi_ccsrv_util.h 33496 2009-06-16 10:37:39Z collin.chiang $
 */
#ifndef __MMI_CCSRV_UTIL_H__
#define __MMI_CCSRV_UTIL_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_mae_common_def.h"
#include "mmi_mae_sm_defs.h"
#include "mmi_mae_datamodel.h"
#include "mmi_mae_notifier.h"
#include "mmi_ccsrv_def.h"
#include "mmi_calllogsrv_def.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Local function prototype declaration and definition
/*=============================================================*/

MAE_Ret CCSRV_UtilRetrieveUnMsgfromCurrentEvent(void *pSM, CCSRV_unMsg_t **ppData, IDataModel **ppDataModel, IBase *pIBase);
CallTable_t *CCSRV_UtilGetCallTableFromDataModel(IDataModel *pDataModel);
MAE_Ret CCSRV_UtilGetAcceptCnf(IBase *pThis, void *pSM, u32 *result, u32 *cause);
MAE_Ret CCSRV_UtilGetReleaseInd(IBase *pThis, void *pSM, u32 *callRef, u32 *cause);

boolean CCSRV_UtilGetCallIDbyStatus(CallTable_t *pCallTable, MMI_CCSRV_Status_e QueryStatus, u8 *pAryID, u8 *pNum);
u8 CCSRV_UtilGetFirstCallIDbyStatus(CallTable_t *pCallTable, MMI_CCSRV_Status_e status);
boolean CCSRV_UtilIsIncomingCallExisted(CallTable_t *pCallTable, u8 u8CallID);
boolean CCSRV_UtilIsMPTYCallExisted(CallTable_t *pCallTable);
boolean CCSRV_UtilIsMPTYCallActive(CallTable_t *pCallTable);
boolean CCSRV_UtilIsBelongToMPTY(CallTable_t *pCallTable, u8 u8CallID);

u8 CCSRV_UtilGetOutgoingCallIndex(CallTable_t *pCallTable);
boolean CCSRV_UtilPutActiveCallsOnHold(CallTable_t *pCallTable);
boolean CCSRV_UtilRetrieveHeldCalls(CallTable_t *pCallTable);
boolean CCSRV_UtilAnswerWaitingCall(IBase *pIBase);
boolean CCSRV_UtilDeleteWaitingCall(CallTable_t *pCallTable);
boolean CCSRV_UtilDeleteIncomingCall(CallTable_t* pCallTable);
boolean CCSRV_UtilDeleteOneCallbyID(CallTable_t *pCallTable, u8 u8CallID, MMI_CCSRV_Status_e CallType);
void CCSRV_UtilDeleteAllXstatusCall(IBase *pThis, MMI_CCSRV_Status_e CallType);
boolean CCSRV_UtilQueryCallStatusbyID(CallTable_t *pCallTable, u8 u8CallID, MMI_CCSRV_Status_e *pRet);
//boolean       CCSRV_UtilQueryCallStatusbyIndex(CallTable_t* pCallTable, u8 u8Index, MMI_CCSRV_Status_e* pRet);
boolean CCSRV_UtilIsJoinMPTYOperationAllow(CallTable_t *pCallTable);
boolean CCSRV_UtilIsSplitOperationAllow(CallTable_t *pCallTable, u8 u8CallID);
void CCSRV_UtilJoinMPTY(CallTable_t *pCallTable, boolean bMPTYValue);
void CCSRV_UtilSwapCallStatus(CallTable_t *pCallTable);
void CCSRV_UtilSplitCall(CallTable_t *pCallTable, u8 u8SplitCallID);
void CCSRV_UtilReturnFromBlackListMode(void *pSM, u8 RetFlag);

u32 CCSRV_UtilGetMTDualStatus(void *pSM);
void CCSRV_UtilSetDualModeStatus(IBase *pIBase, u8 u8DualMode);           

void CCSRV_UtilAddCallLog(IBase *pIBase, u8 DualType, MMI_CALLLOG_TYPE_E CalllogType, u8 *u8CallNumber);
void CCSRV_UtilAddCallDuration(IBase *pIBase, u8 DualType, u32 u32MODuration, u32 u32MTDuration, u32 u32LastDuration);
void CCSRV_UtilAddCallDurationHandler(IBase *pIBase, u8 DualType, u8 u8CallID, CallTable_t *pCallTable);
CCSRV_NUMBER_Type_e CCSRV_UtilGetNumberType(u8 *pNumber);
MAE_Ret CCSRV_UtilGetCallNumberByWaitingStatus(CallTable_t *pCallTable, u8 *pCallNumber, u8 *u8NumberType);
u32 CCSRV_UtilCountTimeDuration(u32 u32StartTime, u32 u32EndTime, u32 u32MinuteTick);
void CCSRV_UtilSyncCTbyCLCC(CallTable_t *pCallTable, CCSRV_ClccCnf_t *pClccCnf);
void CCSRV_UtilAddSingleCallLogTimeDuration(IBase *pIBase, CallEntry_t *pCallEntry, u32 u32EndTime);

#endif /* __MMI_CCSRV_UTIL_H__ */
