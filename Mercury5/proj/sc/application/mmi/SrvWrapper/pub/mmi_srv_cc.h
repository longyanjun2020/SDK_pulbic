/**
* @file    mmi_srv_cc.h
* @brief   Call control service(CC service) wrapper header file
*          CC Service plays the role of:
*          (1)	Provide the service to CC APP. Sometimes and notify others the status of call.
*          (2)	Communicate to Call Control protocol.
*          (3)	Provide the call information.
*
*/

#ifndef __MMI_SRV_CC_H__
#define __MMI_SRV_CC_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_srv_client_commondefine.h"
#include "mmi_ccsrv.h"

/*=============================================================*/
// Type definition of callBack function
/*=============================================================*/

/** SrvCcMakeCallCB
@brief  The callback function to confirm the make MO call request. (triggered by CC_MASK_OUTGOINGCALL / CCSRV_EVT_MakeCallCnf)

@param[out]     pThis           The pointer of Applet.
@param[out]     bResult         The result is TRUE/FALSE.
@param[out]     nCause          The error cause number.
*/
typedef void (*SrvCcMakeCallCB)(void *pThis, boolean bResult, u32 nCause);
/** SrvCcAcceptCallCB
@brief  The callback function to confirm the accept MT call request. (triggered by CC_MASK_INCOMINGCALL / CCSRV_EVT_AcceptCallCnf)

@param[out]     pThis           The pointer of Applet.
@param[out]     bResult         The result is TRUE/FALSE.
@param[out]     nCause          The error cause number.
*/
typedef void (*SrvCcAcceptCallCB)(void *pThis, boolean bResult, u32 nCause);
/** SrvCcHangUpCallCB
@brief  The callback function to confirm the hang up call request. (triggered by CC_MASK_HANGUPCALL / CCSRV_EVT_HangUpCallCnf)

@param[out]     pThis           The pointer of Applet.
@param[out]     bResult         The result is TRUE/FALSE.
@param[out]     nCause          The error cause number.
*/
typedef void (*SrvCcHangUpCallCB)(void *pThis, boolean bResult, u32 nCause);
/** SrvCcHangUpOutgoingCallCB
@brief  The callback function to confirm the hang up out going call request. (triggered by CC_MASK_HANGUPCALL / CCSRV_EVT_HangUpOutgoingCallCnf)

@param[out]     pThis           The pointer of Applet.
@param[out]     bResult         The result is TRUE/FALSE.
@param[out]     nCause          The error cause number.
*/
typedef void (*SrvCcHangUpOutgoingCallCB)(void *pThis, boolean bResult, u32 nCause);
/** SrvCcReleaseHoldCallCB
@brief  The callback function to confirm the release hold call request. (triggered by CC_MASK_HANGUPCALL / CCSRV_EVT_ReleaseHoldCallCnf)

@param[out]     pThis           The pointer of Applet.
@param[out]     bResult         The result is TRUE/FALSE.
@param[out]     nCause          The error cause number.
*/
typedef void (*SrvCcReleaseHoldCallCB)(void *pThis, boolean bResult, u32 nCause);
/** SrvCcReleaseSpecificCallCB
@brief  The callback function to confirm the release specific call request. (triggered by CC_MASK_CHLD_OPER / CCSRV_EVT_ReleaseSpecificCallCnf)

@param[out]     pThis           The pointer of Applet.
@param[out]     bResult         The result is TRUE/FALSE.
@param[out]     nCause          The error cause number.
*/
typedef void (*SrvCcReleaseSpecificCallCB)(void *pThis, boolean bResult, u32 nCause);
/** SrvCcRejectWaitingCallCB
@brief  The callback function to confirm the reject waiting call request. (triggered by CC_MASK_INCOMINGCALL / CCSRV_EVT_RejectWaitingCallCnf)

@param[out]     pThis           The pointer of Applet.
@param[out]     bResult         The result is TRUE/FALSE.
@param[out]     nCause          The error cause number.
*/
typedef void (*SrvCcRejectWaitingCallCB)(void *pThis, boolean bResult, u32 nCause);
/** SrvCcReplaceActiveCallCB
@brief  The callback function to confirm the retrive hold call to replace active call request. (triggered by CC_MASK_INCOMINGCALL / CCSRV_EVT_ReplaceActiveCallCnf)

@param[out]     pThis           The pointer of Applet.
@param[out]     bResult         The result is TRUE/FALSE.
@param[out]     nCause          The error cause number.
*/
typedef void (*SrvCcReplaceActiveCallCB)(void *pThis, boolean bResult, u32 nCause);
/** SrvCcReplaceActiveInWaitingCB
@brief  The callback function to confirm the make call log request. (triggered by CC_MASK_INCOMINGCALL / CCSRV_EVT_ReplaceActiveInWaitingCnf)

@param[out]     pThis           The pointer of Applet.
@param[out]     bResult         The result is TRUE/FALSE.
@param[out]     nCause          The error cause number.
*/
typedef void (*SrvCcReplaceActiveInWaitingCB)(void *pThis, boolean bResult, u32 nCause);
/** SrvCcReplaceHoldInWaitingCB
@brief  The callback function to confirm the release active call and accept the waiting call request. (triggered by CC_MASK_INCOMINGCALL / CCSRV_EVT_ReplaceHoldInWaitingCnf)

@param[out]     pThis           The pointer of Applet.
@param[out]     bResult         The result is TRUE/FALSE.
@param[out]     nCause          The error cause number.
*/
typedef void (*SrvCcReplaceHoldInWaitingCB)(void *pThis, boolean bResult, u32 nCause);
/** SrvCcHoldCallCB
@brief  The callback function to confirm the hold call request. (triggered by CC_MASK_CHLD_OPER / CCSRV_EVT_HoldCallCnf)

@param[out]     pThis           The pointer of Applet.
@param[out]     bResult         The result is TRUE/FALSE.
@param[out]     nCause          The error cause number.
*/
typedef void (*SrvCcHoldCallCB)(void *pThis, boolean bResult, u32 nCause);
/** SrvCcRetrieveCallCB
@brief  The callback function to confirm the retrieve call request. (triggered by CC_MASK_CHLD_OPER / CCSRV_EVT_RetrieveCallCnf)

@param[out]     pThis           The pointer of Applet.
@param[out]     bResult         The result is TRUE/FALSE.
@param[out]     nCause          The error cause number.
*/
typedef void (*SrvCcRetrieveCallCB)(void *pThis, boolean bResult, u32 nCause);
/** SrvCcJoinMPTYCallCB
@brief  The callback function to confirm the join multiparty call request. (triggered by CC_MASK_CHLD_OPER / CCSRV_EVT_JoinMPTYCallCnf)

@param[out]     pThis           The pointer of Applet.
@param[out]     bResult         The result is TRUE/FALSE.
@param[out]     nCause          The error cause number.
*/
typedef void (*SrvCcJoinMPTYCallCB)(void *pThis, boolean bResult, u32 nCause);
/** SrvCcSplitCallCB
@brief  The callback function to confirm the split call request. (triggered by CC_MASK_CHLD_OPER / CCSRV_EVT_JoinMPTYCallCnf)
@param[out]     pThis           The pointer of Applet.
@param[out]     bResult         The result is TRUE/FALSE.
@param[out]     nCause          The error cause number.
*/
typedef void (*SrvCcSplitCallCB)(void *pThis, boolean bResult, u32 nCause);
/** SrvCcSwapCallCB
@brief  The callback function to confirm the swap call request. (triggered by CC_MASK_CHLD_OPER / CCSRV_EVT_SplitCallCnf)

@param[out]     pThis           The pointer of Applet.
@param[out]     bResult         The result is TRUE/FALSE.
@param[out]     nCause          The error cause number.
*/
typedef void (*SrvCcSwapCallCB)(void *pThis, boolean bResult, u32 nCause);
/** SrvCcTransferCallCB
@brief  The callback function to confirm the transfer call request. (triggered by CC_MASK_CHLD_OPER / CCSRV_EVT_TransferCallCnf)

@param[out]     pThis           The pointer of Applet.
@param[out]     bResult         The result is TRUE/FALSE.
@param[out]     nCause          The error cause number.
*/
typedef void (*SrvCcTransferCallCB)(void *pThis, boolean bResult, u32 nCause);
/** SrvCcDTMFCB
@brief  The callback function to confirm the send DTMF request. (triggered by CC_MASK_INCALL / CCSRV_EVT_DTMFCnf)

@param[out]     pThis           The pointer of Applet.
@param[out]     bResult         The result is TRUE/FALSE.
*/
typedef void (*SrvCcDTMFCB)(void *pThis, boolean bResult);
/** SrvCcReleaseActiveCallCB
@brief  The callback function to confirm the release active call request. (triggered by CC_MASK_RELEASECALL / CCSRV_EVT_ReleaseActiveCallCnf)

@param[out]     pThis           The pointer of Applet.
@param[out]     bResult         The result is TRUE/FALSE.
@param[out]     nCause          The error cause number.
*/
typedef void (*SrvCcReleaseActiveCallCB)(void *pThis, boolean bResult, u32 nCause);
/** SrvCcAbortDTMFCB
@brief  The callback function to confirm the abort DTMF request. (triggered by CC_MASK_INCALL / CCSRV_EVT_AbortDTMFCnf)

@param[out]     pThis           The pointer of Applet.
@param[out]     bResult         The result is TRUE/FALSE.
*/
typedef void (*SrvCcAbortDTMFCB)(void *pThis, u32 nResult);

/** SrvCcRingCB
@brief  The callback function to listen the MT call ring indication. (triggered by CC_MASK_INCOMINGCALL / CCSRV_EVT_RingInd)

@param[out]     pThis           The pointer of Applet.
@param[out]     nDualID         DUAL_MASTER/DUAL_SLAVE.
*/
typedef void (*SrvCcRingCB)(void *pThis, u32 nDualID);
/** SrvCcAlertCB
@brief  The callback function to listen the MO call alert indication. (triggered by CC_MASK_OUTGOINGCALL / CCSRV_EVT_AlertInd)

@param[out]     pThis           The pointer of Applet.
@param[out]     nProgID         The progress indication ID.
*/
typedef void (*SrvCcAlertCB)(void *pThis, u32 nProgID);
/** SrvCcReleaseCB
@brief  The callback function to listen release call indication. (triggered by CC_MASK_RELEASECALL / CCSRV_EVT_ReleaseInd)

@param[out]     pThis           The pointer of Applet.
@param[out]     nCause          The error cause number.
*/
typedef void (*SrvCcReleaseCB)(void *pThis, u32 nCause);
/** SrvCcReleaseIncomingCallCB
@brief  The callback function to listen release incoming call indication. (triggered by CC_MASK_RELEASECALL / CCSRV_EVT_ReleaseIncomingCallInd)

@param[out]     pThis           The pointer of Applet.
@param[out]     nCause          The error cause number.
*/
typedef void (*SrvCcReleaseIncomingCallCB)(void *pThis, u32 nCause);
/** SrvCcReleaseOutgoingCallCB
@brief  The callback function to listen release outgoing call indication. (triggered by CC_MASK_RELEASECALL / CCSRV_EVT_ReleaseOutgoingCallInd)

@param[out]     pThis           The pointer of Applet.
@param[out]     nCause          The error cause number.
*/
typedef void (*SrvCcReleaseOutgoingCallCB)(void *pThis, u32 nCause);
/** SrvCcActiveCallReleasedCB
@brief  The callback function to listen active call released indication while waiting exists. (triggered by CC_MASK_RELEASECALL / CCSRV_EVT_ReleaseActiveCallInd)

@param[out]     pThis           The pointer of Applet.
*/
typedef void (*SrvCcActiveCallReleasedCB)(void *pThis);
/** SrvCcHoldCallReleasedCB
@brief  The callback function to listen hold call released indication while waiting exists. (triggered by CC_MASK_RELEASECALL / CCSRV_EVT_ReleaseHoldCallInd)

@param[out]     pThis           The pointer of Applet.
*/
typedef void (*SrvCcHoldCallReleasedCB)(void *pThis);
/** SrvCcReleaseWaitingCallCB
@brief  The callback function to listen waiting call released indication. (triggered by CC_MASK_INCOMINGCALL / CCSRV_EVT_ReleaseWaitingCallInd)

@param[out]     pThis           The pointer of Applet.
@param[out]     nCause          The error cause number.
*/
typedef void (*SrvCcReleaseWaitingCallCB)(void *pThis, u32 nCause);
/** SrvCcNoCallExistedCB
@brief  The callback function to to listen no call existed indication. (triggered by CC_MASK_OTHER / CCSRV_EVT_NoCallExistedInd)

@param[out]     pThis           The pointer of Applet.
@param[out]     nDualID         DUAL_MASTER/DUAL_SLAVE.
*/
typedef void (*SrvCcNoCallExistedCB)(void *pThis, u32 nDualID);
/** SrvCcCallSetupNotifyCB
@brief  The callback function to listen call setup indication with CSSI information. (triggered by CC_MASK_NOTIFY / CCSRV_EVT_CallSetupNotifyInd)

@param[out]     pThis           The pointer of Applet.
@param[out]     nServiceCode    The CSSI code.
@param[out]     nIndex          CUG call index.
*/
typedef void (*SrvCcCallSetupNotifyCB)(void *pThis, u32 nServiceCode, u32 nIndex);
/** SrvCcInCallNotifyCB
@brief  The callback function to listen in call indication with CSSD information. (triggered by CC_MASK_NOTIFY / CCSRV_EVT_InCallNotifyInd)

@param[out]     pThis           The pointer of Applet.
@param[out]     ServiceCode     The CSSU code.
@param[out]     index           CUG call index.
@param[out]     nTonNpi         The address format.
@param[out]     CalledNb        The call number.
*/
typedef void (*SrvCcInCallNotifyCB)(void *pThis, u32 ServiceCode, u32 index, u32 nTonNpi, u8 *CalledNb);
/** SrvCcAudioChannelCB
@brief  The callback function to listen audio channel indication with TCH information. (triggered by CC_MASK_AUDIO / CCSRV_EVT_AudioChannelInd)

@param[out]     pThis           The pointer of Applet.
*/
typedef void (*SrvCcAudioChannelCB)(void *pThis);
/** SrvCcInCallSessionTimerCB
@brief  The callback function to listen in call timer indication. (triggered by CC_MASK_INCALL / CCSRV_EVT_InCallSessionTimer)

@param[out]     pThis           The pointer of Applet.
*/
typedef void (*SrvCcInCallSessionTimerCB)(void *pThis);
/** SrvCcAllCallReleasedCB
@brief  The callback function to listen all call released indication. (triggered by CC_MASK_RELEASECALL / CCSRV_EVT_AllCallReleasedInd)

@param[out]     pThis           The pointer of Applet.
*/
typedef void (*SrvCcAllCallReleasedCB)(void *pThis);
/** SrvCcWaitingToIncomingCall
@brief  The callback function to listen waiting to incoming call indication. (triggered by CC_MASK_INCOMINGCALL / CCSRV_EVT_WaitingToIncomingCallInd)

@param[out]     pThis           The pointer of Applet.
*/
typedef void (*SrvCcWaitingToIncomingCall)(void *pThis);
/** SrvCcProgressCB
@brief  The callback function to confirm the make call log request. (triggered by CC_MASK_OUTGOINGCALL / CCSRV_EVT_ProgressInd)

@param[out]     pThis           The pointer of Applet.
@param[out]     nProgID         The progress indication ID.
*/
typedef void (*SrvCcProgressCB)(void *pThis, u32 nProgID);
/** SrvCcCBSSettingChangeNotifyCB
@brief  The callback function to notify the change of call background sound setting. (triggered by CC_MASK_OTHER / CCSRV_EVT_ChangeCBSSettingInd)

@param[out]     pThis           The pointer of Applet.
@param[out]     eCFGItemID    	The config item id.
@param[out]     u8Data          The data of the specfic config item.
*/
typedef void (*SrvCcCBSSettingChangeNotifyCB)(void *pThis, u32 eCFGItemID, u8 u8Data);
/** SrvCcCallRefIDCB
@brief  The callback function to listen call ID update. (triggered by CC_MASK_OUTGOINGCALL / CCSRV_EVT_CallRefIDInd)

@param[out]     pThis           The pointer of Applet.
@param[out]     nCallRefID      The Call ID.
*/
typedef void (*SrvCcCallRefIDCB)(void *pThis, u32 nCallRefID);

/*=============================================================*/
// Global function definition
/*=============================================================*/

/** SrvCcSetMakeCallCB
@brief  Register/deregister a callback function to listen make MO call confirm.
        (triggered by CC_MASK_OUTGOINGCALL / CCSRV_EVT_MakeCallCnf)

@param[in]      pfnCallBack     SrvCcMakeCallCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetMakeCallCB(SrvCcMakeCallCB pfnCallBack);

/** SrvCcSetAcceptCallCB
@brief  Register/deregister a callback function to listen accept MT call confirm. 
        (triggered by CC_MASK_INCOMINGCALL / CCSRV_EVT_AcceptCallCnf)

@param[in]      pfnCallBack     SrvCcAcceptCallCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetAcceptCallCB(SrvCcAcceptCallCB pfnCallBack);

/** SrvCcSetHangUpCallCB
@brief  Register/deregister a callback function to listen hang up call confirm.
        (triggered by CC_MASK_HANGUPCALL / CCSRV_EVT_HangUpCallCnf)
        
@param[in]      pfnCallBack     SrvCcHangUpCallCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetHangUpCallCB(SrvCcHangUpCallCB pfnCallBack);

/** SrvCcSetHangUpOutgoingCallCB
@brief  Register/deregister a callback function to listen hang up out going call confirm.
        (triggered by CC_MASK_HANGUPCALL / CCSRV_EVT_HangUpOutgoingCallCnf)

@param[in]      pfnCallBack     SrvCcHangUpOutgoingCallCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetHangUpOutgoingCallCB(SrvCcHangUpOutgoingCallCB pfnCallBack);

/** SrvCcSetReleaseHoldCallCB
@brief  Register/deregister a callback function to listen release hold call confirm.
        (triggered by CC_MASK_HANGUPCALL / CCSRV_EVT_ReleaseHoldCallCnf)

@param[in]      pfnCallBack     SrvCcReleaseHoldCallCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetReleaseHoldCallCB(SrvCcReleaseHoldCallCB    pfnCallBack);

/** SrvCcSetReleaseSpecificCallCB
@brief  Register/deregister a callback function to listen release specific call confirm.
        (triggered by CC_MASK_CHLD_OPER / CCSRV_EVT_ReleaseSpecificCallCnf)

@param[in]      pfnCallBack     SrvCcReleaseSpecificCallCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetReleaseSpecificCallCB(SrvCcReleaseSpecificCallCB pfnCallBack);

/** SrvCcSetRejectWaitingCallCB
@brief  Register/deregister a callback function to listen reject waiting call confirm.
        (triggered by CC_MASK_INCOMINGCALL / CCSRV_EVT_RejectWaitingCallCnf)

@param[in]      pfnCallBack     SrvCcRejectWaitingCallCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetRejectWaitingCallCB(SrvCcRejectWaitingCallCB pfnCallBack);

/** SrvCcSetReplaceActiveCallCB
@brief  Register/deregister a callback function to listen retrive hold call to replace active call(if exists) confirm.
        (triggered by CC_MASK_INCOMINGCALL / CCSRV_EVT_ReplaceActiveCallCnf)

@param[in]      pfnCallBack     SrvCcReplaceActiveCallCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetReplaceActiveCallCB(SrvCcReplaceActiveCallCB pfnCallBack);

/** SrvCcSetReplaceActiveInWaitingCB
@brief  Register/deregister a callback function to listen release active call and accept the waiting call confirm.
        (triggered by CC_MASK_INCOMINGCALL / CCSRV_EVT_ReplaceActiveInWaitingCnf)

@param[in]      pfnCallBack     SrvCcReplaceActiveInWaitingCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetReplaceActiveInWaitingCB(SrvCcReplaceActiveInWaitingCB pfnCallBack);

/** SrvCcSetReplaceHoldInWaitingCB
@brief  Register/deregister a callback function to listen replace hold call by waiting call confirm.
        (triggered by CC_MASK_INCOMINGCALL / CCSRV_EVT_ReplaceHoldInWaitingCnf)

@param[in]      pfnCallBack     SrvCcReplaceHoldInWaitingCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetReplaceHoldInWaitingCB(SrvCcReplaceHoldInWaitingCB pfnCallBack);

/** SrvCcSetHoldCallCB
@brief  Register/deregister a callback function to listen hold call confirm.
        (triggered by CC_MASK_CHLD_OPER / CCSRV_EVT_HoldCallCnf)

@param[in]      pfnCallBack     SrvCcHoldCallCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetHoldCallCB(SrvCcHoldCallCB pfnCallBack);

/** SrvCcSetRetrieveCallCB
@brief  Register/deregister a callback function to listen retrieve call confirm.
        (triggered by CC_MASK_CHLD_OPER / CCSRV_EVT_RetrieveCallCnf)

@param[in]      pfnCallBack     SrvCcRetrieveCallCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetRetrieveCallCB(SrvCcRetrieveCallCB pfnCallBack);

/** SrvCcSetJoinMPTYCallCB
@brief  Register/deregister a callback function to listen join multiparty call confirm.
        (triggered by CC_MASK_CHLD_OPER / CCSRV_EVT_JoinMPTYCallCnf)

@param[in]      pfnCallBack     SrvCcJoinMPTYCallCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetJoinMPTYCallCB(SrvCcJoinMPTYCallCB pfnCallBack);

/** SrvCcSetSplitCallCB
@brief  Register/deregister a callback function to listen split call confirm.
        (triggered by CC_MASK_CHLD_OPER / CCSRV_EVT_SplitCallCnf)

@param[in]      pfnCallBack     SrvCcSplitCallCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetSplitCallCB(SrvCcSplitCallCB    pfnCallBack);

/** SrvCcSetSwapCallCB
@brief  Register/deregister a callback function to listen swap call confirm.
        (triggered by CC_MASK_CHLD_OPER / CCSRV_EVT_SwapCallCnf)

@param[in]      pfnCallBack     SrvCcSwapCallCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetSwapCallCB(SrvCcSwapCallCB pfnCallBack);

/** SrvCcSetTransferCallCB
@brief  Register/deregister a callback function to listen transfer call confirm.
        (triggered by CC_MASK_CHLD_OPER / CCSRV_EVT_TransferCallCnf)

@param[in]      pfnCallBack     SrvCcTransferCallCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetTransferCallCB(SrvCcTransferCallCB pfnCallBack);

/** SrvCcSetDTMFCB
@brief  Register/deregister a callback function to listen send DTMF confirm.
        (triggered by CC_MASK_INCALL / CCSRV_EVT_DTMFCnf)

@param[in]      pfnCallBack     SrvCcDTMFCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetDTMFCB(SrvCcDTMFCB pfnCallBack);

/** SrvCcSetReleaseActiveCallCB
@brief  Register/deregister a callback function to listen release active call confirm.
        (triggered by CC_MASK_RELEASECALL / CCSRV_EVT_ReleaseActiveCallCnf)

@param[in]      pfnCallBack     SrvCcReleaseActiveCallCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetReleaseActiveCallCB(SrvCcReleaseActiveCallCB pfnCallBack);

/** SrvCcSetAbortDTMFCB
@brief  Register/deregister a callback function to listen abort DTMF confirm.
        (triggered by CC_MASK_INCALL / CCSRV_EVT_AbortDTMFCnf)

@param[in]      pfnCallBack     SrvCcAbortDTMFCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetAbortDTMFCB(SrvCcAbortDTMFCB pfnCallBack);

/** SrvCcSetRingCB
@brief  Register/deregister a callback function to listen MT call ring indication.
        (triggered by CC_MASK_INCOMINGCALL / CCSRV_EVT_RingInd)

@param[in]      pfnCallBack     SrvCcRingCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetRingCB(SrvCcRingCB  pfnCallBack);

/** SrvCcSetAlertCB
@brief  Register/deregister a callback function to listen MO call alert indication.
        (triggered by CC_MASK_OUTGOINGCALL / CCSRV_EVT_AlertInd)

@param[in]      pfnCallBack     SrvCcAlertCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetAlertCB(SrvCcAlertCB  pfnCallBack);

/** SrvCcSetReleaseCB
@brief  Register/deregister a callback function to listen release call indication.
        (triggered by CC_MASK_RELEASECALL / CCSRV_EVT_ReleaseInd)

@param[in]      pfnCallBack     SrvCcReleaseCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetReleaseCB(SrvCcReleaseCB  pfnCallBack);

/** SrvCcSetReleaseIncomingCallCB
@brief  Register/deregister a callback function to listen release incoming call indication.
        (triggered by CC_MASK_RELEASECALL / CCSRV_EVT_ReleaseIncomingCallInd)

@param[in]      pfnCallBack     SrvCcReleaseIncomingCallCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetReleaseIncomingCallCB(SrvCcReleaseIncomingCallCB  pfnCallBack);

/** SrvCcSetReleaseOutgoingCallCB
@brief  Register/deregister a callback function to listen release outgoing call indication.
        (triggered by CC_MASK_RELEASECALL / CCSRV_EVT_ReleaseOutgoingCallInd)

@param[in]      pfnCallBack     SrvCcReleaseOutgoingCallCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetReleaseOutgoingCallCB(SrvCcReleaseOutgoingCallCB  pfnCallBack);

/** SrvCcSetActiveCallReleasedCB
@brief  Register/deregister a callback function to listen active call released indication while waiting exists.
        (triggered by CC_MASK_RELEASECALL / CCSRV_EVT_ReleaseActiveCallInd)

@param[in]      pfnCallBack     SrvCcActiveCallReleasedCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetActiveCallReleasedCB(SrvCcActiveCallReleasedCB  pfnCallBack);

/** SrvCcSetHoldCallReleasedCB
@brief  Register/deregister a callback function to listen hold call released indication while waiting exists.
        (triggered by CC_MASK_RELEASECALL / CCSRV_EVT_ReleaseHoldCallInd)

@param[in]      pfnCallBack     SrvCcHoldCallReleasedCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetHoldCallReleasedCB(SrvCcHoldCallReleasedCB  pfnCallBack);

/** SrvCcSetReleaseWaitingCallCB
@brief  Register/deregister a callback function to listen waiting call released indication.
        (triggered by CC_MASK_INCOMINGCALL / CCSRV_EVT_ReleaseWaitingCallInd)

@param[in]      pfnCallBack     SrvCcReleaseWaitingCallCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetReleaseWaitingCallCB(SrvCcReleaseWaitingCallCB  pfnCallBack);

/** SrvCcSetNoCallExistedCB
@brief  Register/deregister a callback function to listen no call existed indication.
        (triggered by CC_MASK_OTHER / CCSRV_EVT_NoCallExistedInd)

@param[in]      pfnCallBack     SrvCcNoCallExistedCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetNoCallExistedCB(SrvCcNoCallExistedCB  pfnCallBack);

/** SrvCcSetCallSetupNotifyCB
@brief  Register/deregister a callback function to listen call setup indication with CSSI information.
        (triggered by CC_MASK_NOTIFY / CCSRV_EVT_CallSetupNotifyInd)

@param[in]      pfnCallBack     SrvCcCallSetupNotifyCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetCallSetupNotifyCB(SrvCcCallSetupNotifyCB  pfnCallBack);

/** SrvCcSetInCallNotifyCB
@brief  Register/deregister a callback function to listen in call indication with CSSD information.
        (triggered by CC_MASK_NOTIFY / CCSRV_EVT_InCallNotifyInd)

@param[in]      pfnCallBack     SrvCcInCallNotifyCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetInCallNotifyCB(SrvCcInCallNotifyCB  pfnCallBack);

/** SrvCcSetAudioChannelCB
@brief  Register/deregister a callback function to listen audio channel indication with TCH information.
        (triggered by CC_MASK_AUDIO / CCSRV_EVT_AudioChannelInd)

@param[in]      pfnCallBack     SrvCcAudioChannelCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetAudioChannelCB(SrvCcAudioChannelCB  pfnCallBack);

/** SrvCcSetInCallSessionTimerCB
@brief  Register/deregister a callback function to listen in call timer indication.
        (triggered by CC_MASK_INCALL / CCSRV_EVT_InCallSessionTimer)

@param[in]      pfnCallBack     SrvCcInCallSessionTimerCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetInCallSessionTimerCB(SrvCcInCallSessionTimerCB  pfnCallBack);

/** SrvCcSetAllCallReleasedCB
@brief  Register/deregister a callback function to listen all call released indication.
        (triggered by CC_MASK_RELEASECALL / CCSRV_EVT_AllCallReleasedInd)

@param[in]      pfnCallBack     SrvCcAllCallReleasedCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetAllCallReleasedCB(SrvCcAllCallReleasedCB  pfnCallBack);

/** SrvCcSetWaitingToIncomingCallCB
@brief  Register/deregister a callback function to listen waiting to incoming call indication.
        (triggered by CC_MASK_INCOMINGCALL / CCSRV_EVT_WaitingToIncomingCallInd)

@param[in]      pfnCallBack     SrvCcWaitingToIncomingCall, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetWaitingToIncomingCallCB(SrvCcWaitingToIncomingCall  pfnCallBack);

/** SrvCcSetProgressCB
@brief  Register/deregister a callback function to listen progress indication.
        (triggered by CC_MASK_OUTGOINGCALL / CCSRV_EVT_ProgressInd)

@param[in]      pfnCallBack     SrvCcProgressCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetProgressCB(SrvCcProgressCB  pfnCallBack);

/** SrvCcSetCBSSettingChangeCB
@brief  Register/deregister a callback function to listen the change of call background sound setting. 
		(triggered by CC_MASK_OTHER / CCSRV_EVT_ChangeCBSSettingInd)

@param[in]      pfnCallBack     SrvCcCBSSettingChangeNotifyCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetCBSSettingChangeCB(SrvCcCBSSettingChangeNotifyCB pfnCallBack);

/** SrvCcSetCallRefIDCB
@brief  Register/deregister a callback function to listen call ref id indication.
        (triggered by CC_MASK_OUTGOINGCALL / CCSRV_EVT_CallRefIDInd)

@param[in]      pfnCallBack     SrvCcCallRefIDCB, callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  CCSRV_MO_FAILED        If an error occurs.
*/
MAE_Ret SrvCcSetCallRefIDCB(SrvCcCallRefIDCB  pfnCallBack);

/** SrvCcMakeCallReq
@brief  The interface is is provided to make MO call.
        (1) Accept this request at IDLE, Active and Hold modes only.
        (2) Send VM_MRL_CC_DIALING_REQ to RIL task.

@param[in]    pMakeCallData     MO call data(The phone number is necessary).
@param[in]    eDualMode         MO call by master or slave SIM card(DUAL_MASTER / DUAL_SLAVE).
@param[in]    pfnCallBack       Make call cnf callback function pointer.

@retval  CCSRV_MO_NO_ERROR               If successful.
@retval  CCSRV_MO_FAILED                 If an error occurs.
@retval  CCSRV_MO_CALL_NO_SIM_CARD       No SIM card is inserted.
*/
CCSRV_MO_ERROR_CODE SrvCcMakeCallReq(MmiMakeCallReq_t *pMakeCallData,
                                     MAE_DualMode_t eDualMode,
                                     SrvCcMakeCallCB pfnCallBack);

/** SrvCcMake2ndCallReq
@brief  The interface is used to make 2nd MO call.

@param[in]      pMakeCallData   MO call data(The phone number is necessary).
@param[in]      pfnCallBack     Make2ndCall cnf callback function pointer.

@retval  CCSRV_MO_NO_ERROR               If successful.
@retval  CCSRV_MO_FAILED                 If an error occurs.
@retval  CCSRV_MO_CALL_NO_SIM_CARD       No SIM card is inserted.
@retval  MAE_RET_NOT_READY               CCSrv is already terminated.
@retval  MAE_RET_BAD_PARAM               If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY           Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY                    The service is busy for doing other requests and waiting confirms.
*/
MAE_Ret SrvCcMake2ndCallReq(MmiMakeCallReq_t *pMakeCallData, SrvCcMakeCallCB pfnCallBack);

/** SrvCcHangUpCallReq
@brief  The interface is used to release active, hold or waiting call.
        (1) Only accept this request at IncomingCall and all Waiting call modes.
		(2) Send VM_MRL_CC_ACCEPT_REQ to RIL task.

@param[in]      pfnCallBack     HangUpCall cnf callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvCcHangUpCallReq(SrvCcHangUpCallCB  pfnCallBack);

/** SrvCcHangUpOutgoingCallReq
@brief  The interface is used to release outgoing call. It's very useful to release outgoing call without affecting the active or hold call.
        (1) Accept this request at OutgoingCall, IncomingCall, Active, Hold and ActiveHold modes only.
        (2) Send VM_MRL_CC_HANG_UP_REQ to RIL task.

@param[in]      pfnCallBack     HangUp outgoing call cnf callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
*/
MAE_Ret SrvCcHangUpOutgoingCallReq(SrvCcHangUpCallCB  pfnCallBack);

/** SrvCcAcceptCallReq
@brief  The interface is used to accept incoming call or accept waiting call. The active call will be hold automatically if accept a waiting call.
        (1) Accept this request at Make2ndCall only.
        (2) Send VM_MRL_CC_HANG_UP_REQ to RIL task (Parameter should be different with MAE_CCSRV_HangUpCallReq. This command should request ATH1 to AT Command)

@param[in]      pfnCallBack     Accept call cnf callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
*/
MAE_Ret SrvCcAcceptCallReq(SrvCcAcceptCallCB pfnCallBack);

/** SrvCcReleaseHoldCallReq
@brief  The interface is used to release hold call.
        (1) Accept this request at ActiveHold call only.
        (2) This function is a CHLD operation. CHLD flag is CCSRV_REL_HELD_CALLS_ONLY.
        (3) Send VM_MRL_CC_CHLD_REQ to RIL with MRL_CHLD_REL_HELD_OR_UDUB.

@param[in]      pfnCallBack     Release hold call cnf callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvCcReleaseHoldCallReq(SrvCcReleaseHoldCallCB     pfnCallBack);

/** SrvCcReleaseActiveCallReq
@brief  The interface is provided to release active calls.

@param[in]      pfnCallBack     Release active call cnf callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvCcReleaseActiveCallReq(SrvCcReleaseActiveCallCB  pfnCallBack);

/** SrvCcReleaseSpecificCallReq
@brief  The interface is provided to release any specific call. Caller has to provide the call ID.
        (1) Accept this request at all the child mode for Active, except CheckBlacklist.
        (2) This function is a CHLD operation. CHLD flag is CCSRV_REL_SPECIFIC_CALLS.
        (3) Send VM_MRL_CC_CHLD_REQ to RIL task with MRL_CHLD_REL_ONE_CALL and CallID.

@param[in]      nCallID         Call ID.
@param[in]      pfnCallBack     Release specific call cnf callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
*/
MAE_Ret SrvCcReleaseSpecificCallReq(u8 nCallID, SrvCcReleaseSpecificCallCB  pfnCallBack);

/** SrvCcRejectWaitingCallReq
@brief  The interface is provided to reject a waiting call.
        (1) Accept this request at all the WaitingCall modes only.
        (2) This function is a CHLD operation. CHLD flag is CCSRV_REJECT_WAITING_CALL.
        (3) Send VM_MRL_CC_CHLD_REQ to RIL with MRL_CHLD_REL_HELD_OR_UDUB.

@param[in]      pfnCallBack     Reject waiting call cnf callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
*/
MAE_Ret SrvCcRejectWaitingCallReq(SrvCcRejectWaitingCallCB  pfnCallBack);

/** SrvCcReplaceActiveCallReq
@brief  The interface is to release active call and retrieve hold call. However, it can't be used while the waiting call existed.
        (1) Accept this request at ActiveHold mode only.
        (2) This function is a CHLD operation. CHLD flag is CCSRV_REL_ACT_CALLS_RETRIEVE_CALLS.
        (3) Send VM_MRL_CC_CHLD_REQ to RIL with MRL_CHLD_REL_ACT_AND_ACCEPT.

@param[in]      pfnCallBack     Replace active call cnf callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
*/
MAE_Ret SrvCcReplaceActiveCallReq(SrvCcReplaceActiveCallCB  pfnCallBack);

/** SrvCcReplaceActiveInWaitingReq
@brief  The interface is used to replace active call by waiting call. All the active calls will be released first.
        (1) Accept this request at Active and ActiveHold modes only.
        (2) This function is a CHLD operation. CHLD flag is CCSRV_REL_ACT_CALLS_ANSWER_CALL.
        (3) Send VM_MRL_CC_CHLD_REQ to RIL with MRL_CHLD_REL_ACT_AND_ACCEPT.

@param[in]      pfnCallBack     Replace active in waiting cnf callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
*/
MAE_Ret SrvCcReplaceActiveInWaitingReq(SrvCcReplaceActiveInWaitingCB  pfnCallBack);

/** SrvCcReplaceHoldInWaitingReq
@brief  The interface is used to replace hold call by waiting call. All the hold calls will be released first.
        (1) Accept this request at ActiveHold mode only.
        (2) This function is a composed CHLD operations. CHLD flag is CC_SRV_REPLCAE_HELD_CALL.
		(3) Service will release all the held calls first by VM_MRL_CC_CHLD_REQ with MRL_CHLD_REL_ONE_CALL and CallID.
        (4) Accept the waiting call by VM_MRL_CC_ACCEPT_REQ when all held calls are released.

@param[in]      pfnCallBack     Replace hold in waiting cnf callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
*/
MAE_Ret SrvCcReplaceHoldInWaitingReq(SrvCcReplaceHoldInWaitingCB   pfnCallBack);

/** SrvCcHoldCallReq
@brief  The interface is provided to hold an active call.
        (1) Accept this request at Active mode only.
        (2) This function is a CHLD operation. CHLD flag is CCSRV_HOLD_CALLS.
        (3) Send VM_MRL_CC_CHLD_REQ to RIL with MRL_CHLD_HOLD_ACT_AND_ACCEPT.

@param[in]      pfnCallBack     Hold call cnf callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
*/
MAE_Ret SrvCcHoldCallReq(SrvCcHoldCallCB  pfnCallBack);

/** SrvCcRetrieveCallReq
@brief  The interface is provided to retrieve a hold call.
        (1) Accept this request at Hold mode only.
        (2) This function is a CHLD operation. CHLD flag is CCSRV_RETRIEVE_CALLS.
        (3) Send VM_MRL_CC_CHLD_REQ to RIL with MRL_CHLD_HOLD_ACT_AND_ACCEPT.
        
@param[in]      pfnCallBack     Retrieve call cnf callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
*/
MAE_Ret SrvCcRetrieveCallReq(SrvCcRetrieveCallCB  pfnCallBack);

/** SrvCcJoinMPTYCallReq
@brief  The interface is provided to host a conference call.
        (1) Accept this request at ActiveHold mode with remote party members less than 5.
        (2) This function is a CHLD operation. CHLD flag is CCSRV_JOIN_MPTY_CALL.
        (3) Send VM_MRL_CC_CHLD_REQ to RIL task with MRL_CHLD_MPTY.

@param[in]      pfnCallBack     Join MPTY call cnf callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
*/
MAE_Ret SrvCcJoinMPTYCalllReq(SrvCcJoinMPTYCallCB  pfnCallBack);

/** SrvCcSplitCallReq
@brief  The interface is provided to split a member from the conference call.
        (1) Accept this request at ActiveHold mode only.
        (2) This function is a CHLD operation. CHLD flag is CCSRV_SPLIT_CALL.
        (3) Send VM_MRL_CC_CHLD_REQ to RIL task with MRL_CHLD_SPLIT and CallID. The CallID is the call user wants to split.

@param[in]      nCallID         Split call ID.
@param[in]      pfnCallBack     Split call cnf callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
*/
MAE_Ret SrvCcSplitCalllReq(u8 nCallID, SrvCcSplitCallCB     pfnCallBack);

/** SrvCcSwapCallReq
@brief  The interface is provided to change the status between active and hold call.
        (1) Accept this request at ActiveHold mode only.
        (2) This function is a CHLD operation. CHLD flag is CCSRV_SWAP_CALLS.
        (3) Send VM_MRL_CC_CHLD_REQ to RIL task with MRL_CHLD_HOLD_ACT_AND_ACCEPT.

@param[in]      pfnCallBack     Swap call cnf callback function pointer

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
*/
MAE_Ret SrvCcSwapCalllReq(SrvCcSwapCallCB pfnCallBack);

/** SrvCcTransferCallReq
@brief  The interface is used to transfer the calls and leave the in-call session.
        (1) Accept this request at ActiveHold (waiting or make2ndcall?) mode only.
        (2) This function is a CHLD operation. CHLD flag is CCSRV_TRANSFER_CALLS.
        (3) Send VM_MRL_CC_CHLD_REQ to RIL task with MRL_CHLD_ECT.

@param[in]      pfnCallBack     Transfer call cnf callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
*/
MAE_Ret SrvCcTransferCalllReq(SrvCcTransferCallCB pfnCallBack);

/** SrvCcSendDTMFReq
@brief  The interface is used to send DTMF to protocol stack.
        (1) Accept this request at OneActiveCall or OneActiveOneHoldCall only.
        (2) Send VM_MRL_CC_DTMF_REQ to RIL task.

@param[in]  nKeyCode            The key user pressed.
@param[in]  eDTMFOper           Start to send or Stop to send the DTMF.
@param[in]  nDuration           1~254*100ms if DTMFOper is Start
                                255 is infinite DTMF playing
                                Don't care if DTMFOper is Stop
@param[in]  pfnCallBack         Send DTMF cnf callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
*/
MAE_Ret SrvCcSendDTMFReq(u8 nKeyCode, MMI_CCSRV_DTMF_OP_e eDTMFOper, u8 nDuration, SrvCcDTMFCB pfnCallBack);

/** SrvCcGetActiveMode
@brief  The interface is provided to APP to query the mode status of CC Service.

@retval  pMode                  Mode status of CC Service.
                                CCSRV_IDLE          No call
                                CCSRV_1A            Active call(s)
                                CCSRV_1H            Hold call(s)
                                CCSRV_1A1H          Active call + Hold call(s) or Active call(s) + Hold call
                                CCSRV_1AW           Active call(s) with 1 Waiting call
                                CCSRV_1HW           Hold call(s) with 1 Waiting call
                                CCSRV_1AHW          Active call + Hold call(s)+ Waiting call or Active call(s) + Hold call + Waiting call
                                CCSRV_MAKE2NDCALL   Hold call(s) + 1 Outgoing call
                                CCSRV_OUTGOING      1 Outgoing call
                                CCSRV_INCOMING      1 Incoming call
                                CCSRV_Unknown       Unknow
*/
CCSRV_Mode_e SrvCcGetActiveMode(void);

/** SrvCcGetCallTableData
@brief  The interface provided APPs to get the call table data.

@retval  CallTable_t            If successful.
@retval  NULL                   If an error occurs.
*/
CallTable_t* SrvCcGetCallTableData(void);

/** SrvCcIsEmgegencyCall
@brief  The interface is used to check if the phone number is an emergency number.

@param[in]    pNumber           The phone number to be checked.

@retval  TRUE                   The phone number is belong to emergency call.
@retval  FALSE                  The phone number is no emergency call.       
*/
boolean SrvCcIsEmergencyCall(u8 *pNumber);

/** SrvCcGetDuoCallStatus
@brief  The interface is used to get the status of current call session.

@retval  CCSRV_MASTER_CALL_EXISTED  Current call session belongs to Master mode
@retval  CCSRV_SLAVE_CALL_EXISTED   Current call session belongs to Slave mode
@retval  CCSRV_NO_CALL              No call existed
*/
CCSRV_DUO_STATUS_e SrvCcGetDuoCallStatus(void);

/** SrvCcIsMissCallExisted
@brief  The interface is used to check if the miss call exists when CCSRV is active.

@retval  TRUE                   The miss call exists.
@retval  FALSE                  No miss call exists.
*/
boolean SrvCcIsMissCallExisted(void);

/** SrvCcResetMissCallStatus
@brief  The interface is used to reset miss call flag for CCSRV.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcResetMissCallStatus(void);

/** SrvCcGetInCallDuration
@brief  The interface is used to reset Miss Call flag for CCSRV.

@param[in]    eDurationType     Call duration type CCSRV_DURATION_CURRENT/CCSRV_DURATION_FINAL

@retval  x seconds
*/
u32 SrvCcGetInCallDuration(CCSRV_DURATION_Type_e eDurationType);

/** SrvCcAbortDTMFReq
@brief  The interface is used to force abort DTMF during in-call session.

@param[in]      pfnCallBack     Abort DTMF cnf callback function pointer.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CCSrv is already terminated.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcAbortDTMFReq(SrvCcAbortDTMFCB  pfnCallBack);

/** SrvCcSetAutoRedialStatus
@brief  The interface is used to set auto redial status.

@param[in]    bStatus           Set the status to TRUE or FALSE.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetAutoRedialStatus(boolean bStatus);

/** SrvCcIsAtoRedialActive
@brief  The interface is used to check auto redial status.

@retval TRUE                    Audo redial status is active. 
@retval FALSE                   Audo redial status is inactive or memory is not enough.    
*/
boolean SrvCcIsAtoRedialActive(void);

/** SrvCcSetPreMOCallStatus
@brief  The interface is used to set previous MO call status. (Dual-sim or IP call)

@param[in]    bStatus           Set the status to TRUE or FALSE.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetPreMOCallStatus(boolean bStatus);

/** SrvCcIsPreMOCallActive
@brief  The interface is used to check previous MO call status. (Dual-sim or IP call)

@retval TRUE                    Previous MO call status is active for dual-sim or IP call. 
@retval FALSE                   Previous MO call status is inactive or memory is not enough.
*/
boolean SrvCcIsPreMOCallActive(void);

/** SrvCcIsTryToReleaseAllCall
@brief  The interface is used to check release all call status.
        (Corresponding feedback confirm is CCSRV_EVT_MakeCallCnf)

@retval TRUE                    CcSrv is in release all call status.
@retval FALSE                   CcSrv is not in release all call status or memory is not enough.
*/
boolean SrvCcIsTryToReleaseAllCall(void);

/** SrvCcNotifyAnsweringMachineFailed
@brief  The interface is used to notify that launching answering machine failed with cause.

@param[in]    eAnsweringMachineFailedType   ANSWERING_MACHINE_INSUFFICIENT_STORAGE or ANSWERING_MACHINE_MASS_STORAGE

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcNotifyAnsweringMachineFailed(ANSWERING_MACHINE_FAILED_TYPE_e eAnsweringMachineFailedType);

/** SrvCcSetAnsweringMachineInProgress
@brief  The interface is used to set if answering machine is in progress.

@param[in]    bInProgress   TRUE or FALSE

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetAnsweringMachineInProgress(boolean bInProgress);

/** SrvCcIsAnsweringMachineInProgress
@brief  The interface is used to check if answering machine is in progress.

@retval TRUE                    Answering machine is in progress.
@retval FALSE                   Answering machine is not in progress.
*/
boolean SrvCcIsAnsweringMachineInProgress(void);

/** SrvCcSetAutoRejectMTCall
@brief  The interface is used to enable/disable auto reject MT call for testing.

@param[in]    bRejectMTCall     TRUE(Enable) or FALSE(Disable).

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CcSrv is already terminated. 
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_NOT_SUPPORTED  The operation is not supported.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCcSetAutoRejectMTCall(boolean bRejectMTCall);

/** SrvCcSetDistortedVoiceSettings
@brief  The interface is use to set disotrted voice settings

@param[in]    bStatus   Enable/disable distorted voice
@param[in]    eEffect   The effect of distorted voice

@retval MAE_RET_SUCCESS         If successful.
*/
MAE_Ret SrvCcSetDistortedVoiceSettings(boolean bStatus, MMI_CALLSETTING_DISTORTED_EFFECT_e eEffect);

/** SrvCcGetDistortedVoiceSettings
@brief  The interface is use to get disotrted voice settings

@param[out]    bStatus   Get current distortued voice status
@param[out]    eEffect   Get current distorted voice effect

@retval MAE_RET_SUCCESS         If successful.
*/
MAE_Ret SrvCcGetDistortedVoiceSettings(boolean * bStatus, MMI_CALLSETTING_DISTORTED_EFFECT_e * eEffect);

/** SrvCcSetCallBackgroundSoundSettings
@brief  The interface is use to set call background sound settings

@param[in]    eCFGItemID   The config item id
@param[in]    u8Data   The value of the config item

@retval MAE_RET_SUCCESS         If successful.
*/
MAE_Ret SrvCcSetCallBackgroundSoundSettings(u32 eCFGItemID, const u8 u8Data);

/** SrvCcGetCallBackgroundSoundSettings
@brief  The interface is use to get call background sound settings

@param[out]    eCFGItemID   The config item id
@param[out]    pData   The pointer of the value of the config item

@retval MAE_RET_SUCCESS         If successful.
*/
MAE_Ret SrvCcGetCallBackgroundSoundSettings(u32 eCFGItemID, u8 *pData);

/*-----------------------------------------------------*/
#endif //__MMI_SRV_CC_H__

