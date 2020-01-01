/**
* @file    mmi_srv_vtcc.h
* @brief
*
*/

#ifndef __MMI_SRV_VTCC_H__
#define __MMI_SRV_VTCC_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_vtccsrv.h"

#ifdef __VT_3G324M__

typedef void (*SrvVtCcMakeCallCB)(void *pThis, boolean bResult, u32 nCause);
typedef void (*SrvVtCcAcceptCallCB)(void *pThis, boolean bResult, u32 nCause);
typedef void (*SrvVtCcHangUpCallCB)(void *pThis, boolean bResult, u32 nCause);
typedef void (*SrvVtCcHangUpOutgoingCallCB)(void *pThis, boolean bResult, u32 nCause);
typedef void (*SrvVtCcReleaseHoldCallCB)(void *pThis, boolean bResult, u32 nCause);
typedef void (*SrvVtCcReleaseSpecificCallCB)(void *pThis, boolean bResult, u32 nCause);
typedef void (*SrvVtCcRejectWaitingCallCB)(void *pThis, boolean bResult, u32 nCause);
typedef void (*SrvVtCcReplaceActiveCallCB)(void *pThis, boolean bResult, u32 nCause);
typedef void (*SrvVtCcReplaceActiveInWaitingCB)(void *pThis, boolean bResult, u32 nCause);
typedef void (*SrvVtCcReplaceHoldInWaitingCB)(void *pThis, boolean bResult, u32 nCause);
typedef void (*SrvVtCcHoldCallCB)(void *pThis, boolean bResult, u32 nCause);
typedef void (*SrvVtCcRetrieveCallCB)(void *pThis, boolean bResult, u32 nCause);
typedef void (*SrvVtCcJoinMPTYCallCB)(void *pThis, boolean bResult, u32 nCause);
typedef void (*SrvVtCcSplitCallCB)(void *pThis, boolean bResult, u32 nCause);
typedef void (*SrvVtCcSwapCallCB)(void *pThis, boolean bResult, u32 nCause);
typedef void (*SrvVtCcTransferCallCB)(void *pThis, boolean bResult, u32 nCause);
typedef void (*SrvVtCcDTMFCB)(void *pThis, boolean bResult);
typedef void (*SrvVtCcReleaseActiveCallCB)(void *pThis, boolean bResult, u32 nCause);
typedef void (*SrvVtCcAbortDTMFCB)(void *pThis, u32 nResult);


typedef void (*SrvVtCcRingCB)(void *pThis, u32 nDualID);
typedef void (*SrvVtCcAlertCB)(void *pThis, u32 nProgID);
typedef void (*SrvVtCcReleaseCB)(void *pThis, u32 nCause);
typedef void (*SrvVtCcReleaseIncomingCallCB)(void *pThis, u32 nCause);
typedef void (*SrvVtCcReleaseOutgoingCallCB)(void *pThis, u32 nCause);
typedef void (*SrvVtCcActiveCallReleasedCB)(void *pThis);
typedef void (*SrvVtCcHoldCallReleasedCB)(void *pThis);
typedef void (*SrvVtCcReleaseWaitingCallCB)(void *pThis, u32 nCause);
typedef void (*SrvVtCcNoCallExistedCB)(void *pThis, u32 nDualID);
typedef void (*SrvVtCcCallSetupNotifyCB)(void *pThis, u32 nServiceCode, u32 nIndex);
typedef void (*SrvVtCcInCallNotifyCB)(void *pThis, u32 ServiceCode, u32 index, u32 nTonNpi, u8 *CalledNb);
typedef void (*SrvVtCcAudioChannelCB)(void *pThis);
typedef void (*SrvVtCcInCallSessionTimerCB)(void *pThis);
typedef void (*SrvVtCcAllCallReleasedCB)(void *pThis);
typedef void (*SrvVtCcWaitingToIncomingCall)(void *pThis);
typedef void (*SrvVtCcProgressCB)(void *pThis, u32 nProgID);
typedef void (*SrvVtCc3G324MCallStateNotifyCB)(void *pThis, VtCc3G324MCallState_e eState);
typedef void (*SrvVtCc3G324MUserInputRequestCB)(void *pThis, boolean bResult);
typedef void (*SrvVtCc3G324MUserInputNotifyCB)(void *pThis, u8* pData, u32 nLength);
typedef void (*SrvVtCcCmDisconnectNotifyCB)(void *pThis, boolean bResult);
typedef void (*SrvVtCcFallbackNotifyCB)(void *pThis, boolean bResult);
typedef void (*SrvVtCc3G324ChannelOnOffNotifyCB)(void *pThis, VtCc3G324MOnOffState_e eState, VtCc3G324MChannelType_e eType);
    
/** SrvVtCcSetMakeCallCB
@brief  The interface of Service Client is use to set CB to listen make call confirm

@param[in]      pfnCallBack     SrvVtCcMakeCallCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetMakeCallCB(SrvVtCcMakeCallCB pfnCallBack);

/** SrvVtCcSetAcceptCallCB
@brief  The interface of Service Client is use to set CB to listen accept call confirm

@param[in]      pfnCallBack     SrvVtCcAcceptCallCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetAcceptCallCB(SrvVtCcAcceptCallCB pfnCallBack);

/** SrvVtCcSetHangUpCallCB
@brief  The interface of Service Client is use to set CB to listen hang up call confirm

@param[in]      pfnCallBack     SrvVtCcHangUpCallCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetHangUpCallCB(SrvVtCcHangUpCallCB pfnCallBack);

/** SrvVtCcSetHangUpOutgoingCallCB
@brief  The interface of Service Client is use to set CB to listen hang up out going call confirm

@param[in]      pfnCallBack     SrvVtCcHangUpOutgoingCallCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetHangUpOutgoingCallCB(SrvVtCcHangUpOutgoingCallCB pfnCallBack);

/** SrvVtCcSetReleaseHoldCallCB
@brief  The interface of Service Client is use to set CB to listen release hold call confirm

@param[in]      pfnCallBack     SrvVtCcReleaseHoldCallCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetReleaseHoldCallCB(SrvVtCcReleaseHoldCallCB    pfnCallBack);

/** SrvVtCcSetReleaseSpecificCallCB
@brief  The interface of Service Client is use to set CB to listen release specific call confirm

@param[in]      pfnCallBack     SrvVtCcReleaseSpecificCallCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetReleaseSpecificCallCB(SrvVtCcReleaseSpecificCallCB pfnCallBack);

/** SrvVtCcSetRejectWaitingCallCB
@brief  The interface of Service Client is use to set CB to listen reject waiting call confirm

@param[in]      pfnCallBack     SrvVtCcRejectWaitingCallCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetRejectWaitingCallCB(SrvVtCcRejectWaitingCallCB pfnCallBack);

/** SrvVtCcSetReplaceActiveCallCB
@brief  The interface of Service Client is use to set CB to listen replace active call confirm

@param[in]      pfnCallBack     SrvVtCcReplaceActiveCallCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetReplaceActiveCallCB(SrvVtCcReplaceActiveCallCB pfnCallBack);

/** SrvVtCcSetReplaceActiveInWaitingCB
@brief  The interface of Service Client is use to set CB to listen replace active inwaiting call confirm

@param[in]      pfnCallBack     SrvVtCcReplaceActiveInWaitingCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetReplaceActiveInWaitingCB(SrvVtCcReplaceActiveInWaitingCB pfnCallBack);

/** SrvVtCcSetReplaceHoldInWaitingCB
@brief  The interface of Service Client is use to set CB to listen replace hold inwaiting call confirm

@param[in]      pfnCallBack     SrvVtCcReplaceHoldInWaitingCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetReplaceHoldInWaitingCB(SrvVtCcReplaceHoldInWaitingCB pfnCallBack);

/** SrvVtCcSetHoldCallCB
@brief  The interface of Service Client is use to set CB to listen hold call confirm

@param[in]      pfnCallBack     SrvVtCcHoldCallCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetHoldCallCB(SrvVtCcHoldCallCB pfnCallBack);

/** SrvVtCcSetRetrieveCallCB
@brief  The interface of Service Client is use to set CB to listen retrieve call confirm

@param[in]      pfnCallBack     SrvVtCcRetrieveCallCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetRetrieveCallCB(SrvVtCcRetrieveCallCB pfnCallBack);

/** SrvVtCcSetJoinMPTYCallCB
@brief  The interface of Service Client is use to set CB to listen join multiparty call confirm

@param[in]      pfnCallBack     SrvVtCcJoinMPTYCallCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetJoinMPTYCallCB(SrvVtCcJoinMPTYCallCB pfnCallBack);

/** SrvVtCcSetSplitCallCB
@brief  The interface of Service Client is use to set CB to listen split call confirm

@param[in]      pfnCallBack     SrvVtCcSplitCallCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetSplitCallCB(SrvVtCcSplitCallCB    pfnCallBack);

/** SrvVtCcSetSwapCallCB
@brief  The interface of Service Client is use to set CB to listen swap call confirm

@param[in]      pfnCallBack     SrvVtCcSwapCallCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetSwapCallCB(SrvVtCcSwapCallCB pfnCallBack);

/** SrvVtCcSetTransferCallCB
@brief  The interface of Service Client is use to set CB to listen transfer call confirm

@param[in]      pfnCallBack     SrvVtCcTransferCallCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetTransferCallCB(SrvVtCcTransferCallCB pfnCallBack);

/** SrvVtCcSetDTMFCB
@brief  The interface of Service Client is use to set CB to listen DTMF confirm

@param[in]      pfnCallBack     SrvVtCcDTMFCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetDTMFCB(SrvVtCcDTMFCB pfnCallBack);

/** SrvVtCcSetReleaseActiveCallCB
@brief  The interface of Service Client is use to set CB to listen release active call confirm

@param[in]      pfnCallBack     SrvVtCcReleaseActiveCallCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetReleaseActiveCallCB(SrvVtCcReleaseActiveCallCB pfnCallBack);

/** SrvVtCcSetAbortDTMFCB
@brief  The interface of Service Client is use to set CB to listen abort DTMF confirm

@param[in]      pfnCallBack     SrvVtCcAbortDTMFCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetAbortDTMFCB(SrvVtCcAbortDTMFCB pfnCallBack);

/** SrvVtCcSetRingCB
@brief  The interface of Service Client is use to set CB to listen RING indication

@param[in]      pfnCallBack     SrvVtCcRingCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetRingCB(SrvVtCcRingCB  pfnCallBack);

/** SrvVtCcSetAlertCB
@brief  The interface of Service Client is use to set CB to listen Alert indication

@param[in]      pfnCallBack     SrvVtCcAlertCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetAlertCB(SrvVtCcAlertCB  pfnCallBack);

/** SrvVtCcSetReleaseCB
@brief  The interface of Service Client is use to set CB to listen release call indication

@param[in]      pfnCallBack     SrvVtCcReleaseCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetReleaseCB(SrvVtCcReleaseCB  pfnCallBack);

/** SrvVtCcSetReleaseIncomingCallCB
@brief  The interface of Service Client is use to set CB to listen release incomming call indication

@param[in]      pfnCallBack     SrvVtCcReleaseIncomingCallCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetReleaseIncomingCallCB(SrvVtCcReleaseIncomingCallCB  pfnCallBack);

/** SrvVtCcSetReleaseOutgoingCallCB
@brief  The interface of Service Client is use to set CB to listen release outcomming call indication

@param[in]      pfnCallBack     SrvVtCcReleaseOutgoingCallCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetReleaseOutgoingCallCB(SrvVtCcReleaseOutgoingCallCB  pfnCallBack);

/** SrvVtCcSetActiveCallReleasedCB
@brief  The interface of Service Client is use to set CB to listen release active call indication

@param[in]      pfnCallBack     SrvVtCcActiveCallReleasedCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetActiveCallReleasedCB(SrvVtCcActiveCallReleasedCB  pfnCallBack);

/** SrvVtCcSetHoldCallReleasedCB
@brief  The interface of Service Client is use to set CB to listen release hold call indication

@param[in]      pfnCallBack     SrvVtCcHoldCallReleasedCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetHoldCallReleasedCB(SrvVtCcHoldCallReleasedCB  pfnCallBack);

/** SrvVtCcSetReleaseWaitingCallCB
@brief  The interface of Service Client is use to set CB to listen release waiting call indication

@param[in]      pfnCallBack     SrvVtCcReleaseWaitingCallCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetReleaseWaitingCallCB(SrvVtCcReleaseWaitingCallCB  pfnCallBack);

/** SrvVtCcSetNoCallExistedCB
@brief  The interface of Service Client is use to set CB to listen no call existed indication

@param[in]      pfnCallBack     SrvVtCcNoCallExistedCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetNoCallExistedCB(SrvVtCcNoCallExistedCB  pfnCallBack);

/** SrvVtCcSetCallSetupNotifyCB
@brief  The interface of Service Client is use to set CB to listen call setup indication

@param[in]      pfnCallBack     SrvVtCcCallSetupNotifyCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetCallSetupNotifyCB(SrvVtCcCallSetupNotifyCB  pfnCallBack);

/** SrvVtCcSetInCallNotifyCB
@brief  The interface of Service Client is use to set CB to listen in call indication

@param[in]      pfnCallBack     SrvVtCcInCallNotifyCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetInCallNotifyCB(SrvVtCcInCallNotifyCB  pfnCallBack);

/** SrvVtCcSetAudioChannelCB
@brief  The interface of Service Client is use to set CB to listen audio channel indication

@param[in]      pfnCallBack     SrvVtCcAudioChannelCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetAudioChannelCB(SrvVtCcAudioChannelCB  pfnCallBack);

/** SrvVtCcSetInCallSessionTimerCB
@brief  The interface of Service Client is use to set CB to listen in call timer indication

@param[in]      pfnCallBack     SrvVtCcInCallSessionTimerCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetInCallSessionTimerCB(SrvVtCcInCallSessionTimerCB  pfnCallBack);

/** SrvVtCcSetAllCallReleasedCB
@brief  The interface of Service Client is use to set CB to listen all call released indication

@param[in]      pfnCallBack     SrvVtCcAllCallReleasedCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetAllCallReleasedCB(SrvVtCcAllCallReleasedCB  pfnCallBack);

/** SrvVtCcSetWaitingToIncomingCallCB
@brief  The interface of Service Client is use to set CB to listen waiting to incoming call indication

@param[in]      pfnCallBack     SrvVtCcWaitingToIncomingCall Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetWaitingToIncomingCallCB(SrvVtCcWaitingToIncomingCall  pfnCallBack);

/** SrvVtCcSetProgressCB
@brief  The interface of Service Client is use to set CB to listen progress indication

@param[in]      pfnCallBack     SrvVtCcProgressCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSetProgressCB(SrvVtCcProgressCB  pfnCallBack);

/** SrvVtCcMakeCallReq
@brief  The interface is use to MO call

@param[in]    pMakeCallData     MO call data (Number is necessary)
@param[in]    eDualMode         MO call by Master or Slave SIM card
@param[in]    pfnCallBack       Make call cnf callback function pointer

@retval VTCCSRV_MO_NO_ERROR       If successful.
@retval VTCCSRV_MO_FAILED         request ignored when shell wants to terminate service.
*/
VTCCSRV_MO_ERROR_CODE SrvVtCcMakeCallReq(MmiMakeCallReq_t *pMakeCallData,
                                     MAE_DualMode_t eDualMode,
                                     SrvVtCcMakeCallCB pfnCallBack);

/** SrvVtCcMake2ndCallReq
@brief  The interface is use to  MO call

@param[in]      pMakeCallData   MO call data (Number is necessary)
@param[in]      pfnCallBack     Make2ndCall cnfCall back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BUSY            Can't handle this request. 
*/
MAE_Ret SrvVtCcMake2ndCallReq(MmiMakeCallReq_t *pMakeCallData, SrvVtCcMakeCallCB pfnCallBack);

/** SrvVtCcHangUpCallReq
@brief  The interface is use to release call,  include active, held or waiting call

@param[in]      pfnCallBack     HangUpCall cnf callback function pointer

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BUSY            Can't handle this request. 
*/
MAE_Ret SrvVtCcHangUpCallReq(SrvVtCcHangUpCallCB  pfnCallBack);

/** SrvVtCcHangUpOutgoingCallReq
@brief  The interface is use to release outgoing call. It's very useful to release outgoing call without affecting the active or held call

@param[in]      pfnCallBack     HangUp outgoing call cnf callback function pointer

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BUSY            Can't handle this request. 
*/
MAE_Ret SrvVtCcHangUpOutgoingCallReq(SrvVtCcHangUpCallCB  pfnCallBack);

/** SrvVtCcAcceptCallReq
@brief  The interface is use to accept incoming call or accept waiting call. The active call will be held automatically if accept a waiting call.

@param[in]      pfnCallBack     Accept call cnf callback function pointer

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BUSY            VTCCSRV can't accept call right now. 
*/
MAE_Ret SrvVtCcAcceptCallReq(SrvVtCcAcceptCallCB pfnCallBack);

/** SrvVtCcReleaseHoldCallReq
@brief  The interface is use to accept incoming call or accept waiting call. The active call will be held automatically if accept a waiting call.

@param[in]      pfnCallBack     Release hold call cnf callback function pointer

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BUSY            VTCCSRV can't release call right now. 
*/
MAE_Ret SrvVtCcReleaseHoldCallReq(SrvVtCcReleaseHoldCallCB     pfnCallBack);

/** SrvVtCcReleaseActiveCallReq
@brief  The interface is provided to release active calls

@param[in]      pfnCallBack     Release active call cnf callback function pointer

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BUSY            VTCCSRV can't release call right now. 
*/
MAE_Ret SrvVtCcReleaseActiveCallReq(SrvVtCcReleaseActiveCallCB  pfnCallBack);

/** SrvVtCcReleaseSpecificCallReq
@brief  The interface is provided to release any specific call. Caller have to provide the Call ID he want to release.

@param[in]      nCallID         Call ID
@param[in]      pfnCallBack     Release specific call cnf callback function pointer

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BAD_PARAM       nCallID is not valid. 
*/
MAE_Ret SrvVtCcReleaseSpecificCallReq(u8 nCallID, SrvVtCcReleaseSpecificCallCB  pfnCallBack);

/** SrvVtCcRejectWaitingCallReq
@brief  The interface is provided to reject a waiting call.

@param[in]      pfnCallBack     Reject waiting call cnf callback function pointer

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BUSY            VTCCSRV can't release call right now. 
*/
MAE_Ret SrvVtCcRejectWaitingCallReq(SrvVtCcRejectWaitingCallCB  pfnCallBack);

/** SrvVtCcReplaceActiveCallReq
@brief  The interface is to release active call and retrieve held call. However, it can't be used with waiting call existed.

@param[in]      pfnCallBack     Replace active call cnf callback function pointer

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BUSY            VTCCSRV can't release call right now. 
*/
MAE_Ret SrvVtCcReplaceActiveCallReq(SrvVtCcReplaceActiveCallCB  pfnCallBack);

/** SrvVtCcReplaceActiveInWaitingReq
@brief  The interface is use to replace active call by waiting call. All the active calls will be released first.

@param[in]      pfnCallBack     Replace active in waiting cnf callback function pointer

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BUSY            VTCCSRV can't release call right now. 
*/
MAE_Ret SrvVtCcReplaceActiveInWaitingReq(SrvVtCcReplaceActiveInWaitingCB  pfnCallBack);

/** SrvVtCcReplaceHoldInWaitingReq
@brief  The interface is to replace held call by waiting call. All the held calls will be released first.

@param[in]      pfnCallBack     Replace hold in waiting cnf callback function pointer

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BUSY            VTCCSRV can't release call right now. 
*/
MAE_Ret SrvVtCcReplaceHoldInWaitingReq(SrvVtCcReplaceHoldInWaitingCB   pfnCallBack);

/** SrvVtCcHoldCallReq
@brief  The interface is provided to hold an active call.

@param[in]      pfnCallBack     Hold call cnf callback function pointer

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BUSY            VTCCSRV can't release call right now. 
*/
MAE_Ret SrvVtCcHoldCallReq(SrvVtCcHoldCallCB  pfnCallBack);

/** SrvVtCcRetrieveCallReq
@brief  The interface is provided to retrieve a held call .

@param[in]      pfnCallBack     Retrieve call cnf callback function pointer

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BUSY            VTCCSRV can't release call right now. 
*/
MAE_Ret SrvVtCcRetrieveCallReq(SrvVtCcRetrieveCallCB  pfnCallBack);

/** SrvVtCcJoinMPTYCallReq
@brief  The interface is provided to host a conference call.

@param[in]      pfnCallBack     Join MPTY call cnf callback function pointer

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BUSY            VTCCSRV can't release call right now. 
*/
MAE_Ret SrvVtCcJoinMPTYCalllReq(SrvVtCcJoinMPTYCallCB  pfnCallBack);

/** SrvVtCcSplitCallReq
@brief  The interface is provided to split a member from the conference call.

@param[in]      nCallID         Split Call ID
@param[in]      pfnCallBack     Split call cnf callback function pointer

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BUSY            VTCCSRV can't release call right now. 
*/
MAE_Ret SrvVtCcSplitCalllReq(u8 nCallID, SrvVtCcSplitCallCB     pfnCallBack);

/** SrvVtCcSwapCallReq
@brief  The interface is provided to change the status between active and held call.

@param[in]      pfnCallBack     Swap call cnf callback function pointer

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BUSY            VTCCSRV can't release call right now. 
*/
MAE_Ret SrvVtCcSwapCalllReq(SrvVtCcSwapCallCB pfnCallBack);

/** SrvVtCcTransferCallReq
@brief  The interface is used to transfer the calls and leave the in-call session.

@param[in]      pfnCallBack     Transfer call cnf callback function pointer

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BUSY            VTCCSRV can't release call right now. 
*/
MAE_Ret SrvVtCcTransferCalllReq(SrvVtCcTransferCallCB pfnCallBack);

/** SrvVtCcSendDTMFReq
@brief  The interface is used to send DTMF to protocol stack.

@param[in]  nKeyCode            The key user pressd
@param[in]  eDTMFOper           Start to send or Stop to send the DTMF
@param[in]  nduration           1~254*100ms if DTMFOper is Start
                                255 is infinite DTMF playing
                                Don't care if DTMFOper is Stop
@param[in]  pfnCallBack         Send DTMF cnf callback function pointer

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BUSY            VTCCSRV can't release call right now. 
*/
MAE_Ret SrvVtCcSendDTMFReq(u8 nKeyCode, MMI_VTCCSRV_DTMF_OP_e eDTMFOper, u8 nDuration, SrvVtCcDTMFCB pfnCallBack);

/** SrvVtCcGetActiveMode
@brief  The interface is provided to APP to query the mode status of VTCC Service.

@retval     pMode             Mode status of VTCC Service.
                              VTCCSRV_IDLE          No call
                              VTCCSRV_1A            Active call(s)
                              VTCCSRV_1H            Held call(s)
                              VTCCSRV_1A1H          Active call + Held call(s) or Active call(s) + Held call
                              VTCCSRV_1AW           Active call(s) with 1 Waiting call
                              VTCCSRV_1HW           Held call(s) with 1 Waiting call
                              VTCCSRV_1AHW          Active call + Held call(s)+ Waiting call or Active call(s) + Held call + Waiting call
                              VTCCSRV_MAKE2NDCALL   Held call(s) + 1 Outgoing call
                              VTCCSRV_OUTGOING      1 Outgoing call
                              VTCCSRV_INCOMING      1 Incoming call
                              VTCCSRV_Unknown       Unknow
*/
VTCCSRV_Mode_e SrvVtCcGetActiveMode(void);

/** SrvVtCcGetCallTableData
@brief  The interface provided APPs to get the Call table data model.

@retval CallTable_t         If successful.
@retval NULL                If an error happen.
*/
CallTable_t* SrvVtCcGetCallTableData(void);

/** SrvVtCcIsEmgegencyCall
@brief  The interface is use to check Emergency number

@param[in]    pNumber       Phone number to be checked

@retval TRUE                Emergency call.
@retval FALSE               Not a Emergency call.       
*/
boolean SrvVtCcIsEmergencyCall(u8 *pNumber);

/** SrvVtCcGetDuoCallStatus
@brief  The interface is use to get the duo status of current call

@retval     VTCCSRV_MASTER_CALL_EXISTED  Current call session belong to Master mode
@retval     VTCCSRV_SLAVE_CALL_EXISTED   Current call session belong to Slave mode
@retval     VTCCSRV_NO_CALL              No call existed
*/
VTCCSRV_DUO_STATUS_e SrvVtCcGetDuoCallStatus(void);

/** SrvVtCcIsMissCallExisted
@brief  The interface is use to check Miss Call existed when VTCCSRV is active

@retval TRUE            Miss call existed
@retval FALSE           No miss call         
*/
boolean SrvVtCcIsMissCallExisted(void);

/** SrvVtCcResetMissCallStatus
@brief  The interface is use to reset Miss Call flag for VTCCSRV

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcResetMissCallStatus(void);

/** SrvVtCcGetInCallDuration
@brief  The interface is use to reset Miss Call flag for VTCCSRV

@param[in]    eDurationType    Duration type

@retval x seconds
*/
u32 SrvVtCcGetInCallDuration(VTCCSRV_DURATION_Type_e eDurationType);

/** SrvVtCcAbortDTMFReq
@brief  The interface is used to force abort DTMF during in-call session.

@param[in]      pfnCallBack     Abort DTMF cnf callback function pointer

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcAbortDTMFReq(SrvVtCcAbortDTMFCB  pfnCallBack);

/** SrvVtCcSetAutoRedialStatus
@brief  The interface is use to set Auto Redial status

@param[in]    bStatus         TRUE or FALSE
*/
void SrvVtCcSetAutoRedialStatus(boolean bStatus);

/** SrvVtCcIsAtoRedialActive
@brief  The interface is use to check Auto Redial status

@retval TRUE            
@retval FALSE           
*/
boolean SrvVtCcIsAtoRedialActive(void);

/** SrvVtCcSetPreMOCallStatus
@brief  The interface is use to set Pre-MO call status(For Check dual or IP call)

@param[in]    bStatus         TRUE if set
*/
void SrvVtCcSetPreMOCallStatus(boolean bStatus);

/** SrvVtCcIsPreMOCallActive
@brief  The interface is use to check Pre MO call status

@retval TRUE            
@retval FALSE  
*/
boolean SrvVtCcIsPreMOCallActive(void);

/** SrvVtCcIsTryToReleaseAllCall
@brief  The interface is use to check release all call status

@retval TRUE            
@retval FALSE  
*/
boolean SrvVtCcIsTryToReleaseAllCall(void);

/** SrvVtCcNotifyAnsweringMachineFailed
@brief  The interface is use to notify that launching Answering Machine failed with cause.

@param[in]    eAnsweringMachineFailedType   ANSWERING_MACHINE_INSUFFICIENT_STORAGE or ANSWERING_MACHINE_MASS_STORAGE

@retval MAE_RET_SUCCESS         If successful.
*/
MAE_Ret SrvVtCcNotifyAnsweringMachineFailed(ANSWERING_MACHINE_FAILED_TYPE_e eAnsweringMachineFailedType);

/** SrvVtCcSet3G324MCallStateNotifyCB
@brief  The interface of Service Client is use to set CB to listen in call state indication

@param[in]      pfnCallBack     SrvVtCc3G324MCallStateNotifyCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
*/
MAE_Ret SrvVtCcSet3G324MCallStateNotifyCB(SrvVtCc3G324MCallStateNotifyCB pfnCallBack);

/** SrvVtCc3G324MSendUserInputReq
@brief  send user input
@param[in]  pData               Input buffer
@param[in]  nLen                Buffer length
@param[in]  pfnCallBack         Send user input request callback function pointer

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BUSY            Can't handle this request.
*/
MAE_Ret SrvVtCc3G324MSendUserInputReq(u8 *pData, u32 nLength, SrvVtCc3G324MUserInputRequestCB pfnCallBack);

/** SrvVtCcSet3G324MUserInputNotifyCB
@brief  The interface is used to do the user input notification.
@param[in]  pfnCallBack         User input notify callback function pointer

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BUSY            Can't handle this request.
*/
MAE_Ret SrvVtCcSet3G324MUserInputNotifyCB(SrvVtCc3G324MUserInputNotifyCB pfnCallBack);

/** SrvVtCcFallbackReq
@brief  The interface is used to make the fallback request

@param[in]      pfnCallBack     Fallback cnf callback function pointer

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BUSY            VTCCSRV can't release call right now. 
*/
MAE_Ret SrvVtCcFallbackReq(SrvVtCcFallbackNotifyCB pfnCallBack);

/** SrvVtCc3G324ChannelOnOffReq
@brief  The interface is used to make the channel on/off request

@param[in]      VtCc3G324MOnOffState_e     On/Off
@param[in]      VtCc3G324MChannelType_e    Audio/Video/Data
@param[in]      VtCc3G324MChannelNotify_e  On/Off

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BUSY            VTCCSRV can't release call right now. 
*/
MAE_Ret SrvVtCc3G324ChannelOnOffReq(VtCc3G324MOnOffState_e eState, VtCc3G324MChannelType_e eType, VtCc3G324MChannelNotify_e eNotify);

/** SrvVtCcSet3G324ChannelOnOffNotifyCB
@brief  The interface is used to make the channel on/off notification
@param[in]  pfnCallBack         Audio/Video/Data Channel on/off notify callback function pointer

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_SUPPORTED   request ignored when shell wants to terminate service.
@retval MAE_RET_BUSY            Can't handle this request.
*/
MAE_Ret SrvVtCcSet3G324ChannelOnOffNotifyCB(SrvVtCc3G324ChannelOnOffNotifyCB pfnCallBack);

MAE_Ret SrvVtCcCMDisconnectReq(SrvVtCcHangUpCallCB pfnCallBack);

/*-----------------------------------------------------*/
#endif //__VT_3G324M__
#endif //__MMI_SRV_VTCC_H__

