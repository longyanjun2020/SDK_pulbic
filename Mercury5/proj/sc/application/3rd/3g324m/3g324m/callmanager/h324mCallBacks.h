/***********************************************************************
        Copyright (c) 2002 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION RADVISION Ltd.. No part of this document may be reproduced
in any form whatsoever without written prior approval by RADVISION Ltd..

RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/

#ifndef _H324M_CALLBACKS_H_
#define _H324M_CALLBACKS_H_


/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "Rv3G324mCallTypes.h"
#include "h324mStackObject.h"
#include "h324mCallObject.h"
#include "rvh223defs.h"


#ifdef __cplusplus
extern "C" {
#endif


/*-----------------------------------------------------------------------*/
/*                           FUNCTIONS HEADERS                           */
/*-----------------------------------------------------------------------*/


/******************************************************************************
 * H324mSendMessage
 * ----------------------------------------------------------------------------
 * General: Notifies the application for message to send. This function does
 *          not delete nodeId when it's done.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle.
 *         nodeId           - The node id that holds the message to be sent.
 * Output: sentOnDummy      - Ignored.
 *****************************************************************************/
RvStatus H324mSendMessage(
    IN  HCALL        h3G324mCall,
    IN  RvPvtNodeId  nodeId,
    OUT RvBool      *sentOnDummy);


/******************************************************************************
 * H324mSendChanMessage
 * ----------------------------------------------------------------------------
 * General: Notifies the application for message on a channel to send. This
 *          function does not delete nodeId when it's done.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle.
 *         h3g324mChannel   - The channel handle.
 *         nodeId           - The node id that holds the message to be sent.
 * Output: sentOnDummy      - Ignored.
 *****************************************************************************/
RvStatus H324mSendChanMessage(
    IN  HCALL        h3G324mCall,
    IN  HCHAN        h3G324mChannel,
    IN  RvPvtNodeId  nodeId,
    OUT RvBool      *sentOnDummy);


/******************************************************************************
 * HandleH245MsgReceived
 * ----------------------------------------------------------------------------
 * General: Decodes the received message and notifies the application for
 *          message received.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  context        - The call handle.
 *         pBuf           - The buffer that contains the message.
 *         bufSize        - The buffer size.
 *         eControlResult - Control result of receiving the message.
 * Output: none.
 *****************************************************************************/
void HandleH245MsgReceived(
    IN void            *context,
	IN RvUint8         *pBuf,
	IN RvUint32        bufSize,
	IN EControlResult  eControlResult);

/******************************************************************************
 * HandleChannelDataReceived
 * ----------------------------------------------------------------------------
 * General: extract the AL-PDU and notify the application for the received data.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  context           - The channel handle.
 *         subContext        - Not used.
 *         pAlSdu            - The Al-SDU that contains the data.
 *         bufSize           - The buffer size.
 *         eExtractionResult - The result of extraction action on the received buffer.
 * Output: none.
 *****************************************************************************/
void HandleChannelDataReceived(
                           IN void              *context,
                           IN RvInt32          subContext,
						   IN TRvAlSdu          *pAlSdu,
						   IN RvUint32          bufSize,
						   IN EExtractionResult eExtractionResult);
#if (RV_3G324M_USE_MONA == RV_YES)
/******************************************************************************
 * HandleMonaMPCDataReceived
 * ----------------------------------------------------------------------------
 * General: extract the AL-PDU and notify the application for the received data
 *          on MPC phantom channels.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  context           - The channel handle.
 *         subContext        - Not used.
 *         pAlSdu            - The Al-SDU that contains the data.
 *         bufSize           - The buffer size.
 *         eExtractionResult - The result of extraction action on the received buffer.
 * Output: none.
 *****************************************************************************/
void HandleMonaMPCDataReceived(
                       IN void              *context,
                       IN RvInt32           subContext,
					   IN TRvAlSdu          *pAlSdu,
					   IN RvUint32          bufSize,
					   IN EExtractionResult eExtractionResult);
#endif /* USE_MONA */

/******************************************************************************
 * HandleRtxRequest
 * ----------------------------------------------------------------------------
 * General: Handle a request for retransmission that the H.223 RxAl would like
 *          to make.
 *
 * Return Value: Number of retransmissions to actually ask for.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  context           - The channel handle.
 *         expectedSeqNum    - The expected sequence number we wanted.
 *         curSeqNum         - The sequence number we got.
 * Output: None.
 *****************************************************************************/
RvInt32 HandleRtxRequest(
    IN  void      *context,
    IN  RvUint16  expectedSeqNum,
    IN  RvUint16  curSeqNum);


/******************************************************************************
 * H324mTimerStartEv
 * ----------------------------------------------------------------------------
 * General: Start a timer for the use of H.245.
 *
 * Return Value: Timer started on success
 *               NULL on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hCtrl        - Control object to start a timer for.
 *         eventHandler - Callback function on timeout.
 *         context      - Context for the callback function.
 *         millisec     - Length of the timer in milliseconds.
 * Output: none.
 *****************************************************************************/
RvTimer* H324mTimerStartEv(
    IN HCONTROL     hCtrl,
    IN RvTimerFunc  eventHandler,
    IN void*        context,
    IN RvInt32      millisec);

/******************************************************************************
 * H324mTimerCancelEv
 * ----------------------------------------------------------------------------
 * General: Cancel a timer that wasn't timed-out yet.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hCtrl        - Control object that is associated with the timer.
 *         timer        - Pointer to the timer to cancel.
 * Output: timer        - NULL timer pointer for easy handling.
 *****************************************************************************/
RvStatus H324mTimerCancelEv(
    IN    HCONTROL  hCtrl,
    INOUT RvTimer   **timer);

/******************************************************************************
 * H324mTimerClearEv
 * ----------------------------------------------------------------------------
 * General: Clear a timer that has timed-out.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hCtrl        - Control object that is associated with the timer.
 *         timer        - Pointer to the timer to clear.
 * Output: timer        - NULL timer pointer for easy handling.
 *****************************************************************************/
RvStatus H324mTimerClearEv(
    IN    HCONTROL  hCtrl,
    INOUT RvTimer   **timer);

/******************************************************************************
 * H324mGetRandomNumberEv
 * ----------------------------------------------------------------------------
 * General: A request of random number from the application.
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324m          - The stack handle.
 *         h3G324mCall      - The call handle in the stack.
 *         seed             - The randomGenerator to use.
 * Output: value            - The random number determined by the application.
 *****************************************************************************/
void H324mGetRandomNumberEv(
    IN HAPP                 h3G324m,
    IN HCALL                h3G324mCall,
    IN RvRandomGenerator    *seed,
    OUT RvRandom*           value);

/******************************************************************************
 * H324mCallUpdateOutgoingChannelsInfo
 * ----------------------------------------------------------------------------
 * General: Make sure we allocate H.223 transmit channel objects for all
 *          of the outgoing channels.
 *          H.223 channel objects are usually created upon an incoming or
 *          outgoing OLC Ack. When the application wants to send an MES message
 *          prior to the OLC Ack, this is done by updating the H.223 channel
 *          objects using this function.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  pCall - The call object.
 * Output: none.
 *****************************************************************************/
RvStatus H324mCallUpdateOutgoingChannelsInfo(
    IN H324mCall    *pCall);

/******************************************************************************
 * H324mH223LogicalChannelEv
 * ----------------------------------------------------------------------------
 * General: Open logical channel in the H.223 module. For Muxer channel
 *          will be opened for outgoing channel and Demux channel will be opened
 *          for incoming channel.
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle.
 *         h3G324mChannel   - The channel handle.
 *         isChannelOpen    - defines whether the channel is being opened or closed.
 * Output: none.
 *****************************************************************************/
RvStatus H324mH223LogicalChannelEv(
    IN HCALL  h3G324mCall,
    IN HCHAN  h3G324mChannel,
    IN RvBool isChannelOpen);

/******************************************************************************
 * Rv3G324mCallBuildDEMUXfromMES
 * ----------------------------------------------------------------------------
 * General: Get a descriptors pvt tree of all entries of the demux table,
 *          translate the pvt into a struct and set the entries in the demux
 *          table.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure - in which case, the procedure should be
 *               rejected.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle
 *         h3G324m          - the application handle
 *         descriptors      - the pvt nodeid that holds the MES descriptors
 * Output: entries          - bit set of the entries that were read successfully
 *         tooComplex       - In case we return a failure (!RV_OK), this boolean
 *                            indicates if the reason for failure was complexity
 *                            of the entries or other problems.
 *****************************************************************************/
RvStatus Rv3G324mCallBuildDEMUXfromMES(
    IN  HCALL           h3G324mCall,
    IN  HAPP            h3G324m,
    IN  RvPvtNodeId     descriptors,
    OUT RvUint16        *entries,
    OUT RvBool          *tooComplex);

/******************************************************************************
 * H324mCallMultiplexReconfiguration
 * ----------------------------------------------------------------------------
 * General: Gets the value of the choice inside the h223MultiplexReconfiguration
 *          message and Sets it to the Demux module.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall       - The call handle.
 *         fieldId           - The field id of the choice inside the message.
 *         bIsH223ModeChange - Defines whether the choice field id is h223ModeChange
 *                             or h223AnnexADoubleFlag.
 * Output: none
 *****************************************************************************/
RvStatus H324mCallMultiplexReconfiguration(
    IN  HCALL           h3G324mCall,
    IN  RvPstFieldId    fieldId,
    IN  RvBool          bIsH223ModeChange);

/******************************************************************************
 * H324mCallMaxH223MUXPDUsize
 * ----------------------------------------------------------------------------
 * General: Gets the value of the maxMuxPduSize from inside the 
 *          maxH223MUXPDUsize message Sets it to the Muxer module.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall       - The call handle.
 *         maxMuxPduSize     - The max MUX - PDU size.
 * Output: none
 *****************************************************************************/
RvStatus H324mCallMaxH223MUXPDUsize(
    IN  HCALL           h3G324mCall,
    IN  RvUint16        value);

/******************************************************************************
 * H324mNotifyStateEv
 * ----------------------------------------------------------------------------
 * General: Notify changes in the state of a control object of a call. This is called
 *          for connected states only (Connected/Conference).
 * Return Value: none.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle.
 *         eState           - The control state.
 * Output: none.
 *****************************************************************************/
void H324mNotifyStateEv(
     IN HCALL               h3G324mCall,
     IN H245ControlState    eState);


/******************************************************************************
 * H324mIsClearEv
 * ----------------------------------------------------------------------------
 * General: Informs the user that the module is empty and ready for termination.
 *          The H.223 module is actualy destructed in this function.
 * Return Value: none.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  context      - The context of the call.
 * Output: none.
 *****************************************************************************/
void H324mIsClearEv(IN void  *context);


/******************************************************************************
 * H324mMuxLevelIndicationEv
 * ----------------------------------------------------------------------------
 * General: Informs the user which mux level the demux has detected.
 * Return Value: none.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  context      - The context of the call.
 *         bitShift     - Bit shift notification regarding the synchronization
 *                        that has occurred.
 *         muxLevel     - Mux level information.
 * Output: none.
 *****************************************************************************/
void H324mMuxLevelIndicationEv(
    IN void             *context,
    IN RvUint8          bitShift,
    IN TMuxLevelCfg     *muxLevel);


/******************************************************************************
 * DemuxEventAdd
 * ----------------------------------------------------------------------------
 * General: Add an H.223 demux event to the queue of pending events.
 *          We use this mechanism to avoid deadlocks when we need to access the
 *          MUX object from the DEMUX.
 * Return Value: RV_OK on success, other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  app          - Stack instance.
 *         h3G324mCall  - Call this event belongs to.
 * Output: event        - Pointer to a free demux event, if the function was
 *                        successful. The caller sof this function should then fill
 *                        in the given struct.
 *****************************************************************************/
RvStatus DemuxEventAdd(
    IN H324mStack       *app,
    IN  HCALL           h3G324mCall,
    OUT H223DemuxEvent  **event);


/******************************************************************************
 * DemuxEventsHandle
 * ----------------------------------------------------------------------------
 * General: Handle any pending demux events for the given call. This function
 *          should be called whenever we finish handling the incoming data
 *          on a call, to avoid deadlocks.
 * Return Value: RV_OK on success, other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  app          - Stack application handle. Passed for optimization.
 *         h3G324mCall  - Call to handle.
 *****************************************************************************/
RvStatus DemuxEventsHandle(
    IN H324mStack   *app,
    IN HCALL        h3G324mCall);

/******************************************************************************
 * H324mMuxReconfigurationTimer
 * ----------------------------------------------------------------------------
 * General: Informs the user that the multiplex reconfiguration has finished and
 *          the new mux level can be set.
 * Return Value: RvBool
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  context      - The context of the call.
 * Output: none.
 *****************************************************************************/
RvBool H324mMuxReconfigurationTimer(IN void  *context);

/******************************************************************************
 * H324mIsMuxLevelEqual
 * ----------------------------------------------------------------------------
 * General: Compares mux level between 2 structs.
 * Return Value: RvBool
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  pMuxLevel1      - The first mux level struct.
 *         pMuxLevel2      - The second mux level struct.
 * Output: none.
 *****************************************************************************/
RvBool H324mIsMuxLevelEqual(IN TMuxLevelCfg *pMuxLevel1,
                            IN TMuxLevelCfg *pMuxLevel2);

/******************************************************************************
 * NotifyState
 * ----------------------------------------------------------------------------
 * General: Notify the application about the state of the call.
 * Return Value: none.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hsCall      - The stack call handle.
 *         state       - The state of the call.
 *         stateMode   - The mode of the state.
 * Output: none.
 *****************************************************************************/
void NotifyState(
                 IN HCALL hsCall,
                 IN Rv3G324mCallState state,
                 IN Rv3G324mCallStateMode stateMode);

/******************************************************************************
 * H324mLockMessageSending
 * ----------------------------------------------------------------------------
 * General: Locks the H.245 message sending and accumulates the messages until
 *          unlocking it.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle.
 * Output: none.
 *****************************************************************************/
RvStatus H324mLockMessageSending(IN  HCALL        h3G324mCall);

/******************************************************************************
 * H324mUnlockMessageSending
 * ----------------------------------------------------------------------------
 * General: Unlocks the H.245 message accumulation and allows to send it.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  app              - Stack instance.
 *         h3G324mCall      - The call handle.
 * Output: none.
 *****************************************************************************/
RvStatus H324mUnlockMessageSending(
    IN  H324mStack  *app,
    IN  HCALL       h3G324mCall);

/******************************************************************************
 * H324mMuxLevelSynchronizationTimer
 * ----------------------------------------------------------------------------
 * General: Disconnects the call if the call hasn't reached the Synchronize state
 *          yet.
 * Return Value: RvBool
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  context      - The context of the call.
 * Output: none.
 *****************************************************************************/
RvBool H324mMuxLevelSynchronizationTimer(IN void  *context);

/******************************************************************************
 * H324mReceivedResetRequestEv
 * ----------------------------------------------------------------------------
 * General: This callback gives the application the possibility whether to drop
 *          or reset a call when EndSessionCommand message was received with
 *          communication mode options.
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle.
 * Output: none.
 *****************************************************************************/
RvStatus H324mReceivedResetRequestEv(IN HCALL  h3G324mCall);

/******************************************************************************
 * H324mResetH223ACPIgnoreDataEv
 * ----------------------------------------------------------------------------
 * General: Calls the RvH223DemuxResetIgnoreData to avoid the check if to ignore
 *          received data on an ACP channel, or not (for ACP channels).
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hChan      - The channel handle.
 * Output: none.
 *****************************************************************************/
RvStatus H324mResetH223ACPIgnoreDataEv(IN HCHAN    hChan);

/******************************************************************************
 * H324mClearACPChannelEv
 * ----------------------------------------------------------------------------
 * General: Calls the RvH223DemuxACPClearAudioLC or RvH223DemuxACPClearVideoLC. 
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hChan      - The channel handle.
 *         isVideo    - RV_TRUE if the channel is a video channel, RV_FALSE
 *                      if the channel is an audio channel.
 * Output: none.
 *****************************************************************************/
RvStatus H324mClearACPChannelEv(IN HCHAN    hChan, 
                                   IN RvBool   isVideo);

/******************************************************************************
 * H324mSetACPDefaultMuxTblEv
 * ----------------------------------------------------------------------------
 * General: Calls the RvH223MuxerACPSetDefaultMuxTbl. 
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hCall      - The call handle.
 * Output: none.
 *****************************************************************************/
RvStatus H324mSetACPDefaultMuxTblEv(IN HCALL hCall);

#ifdef __cplusplus
}
#endif

#endif /* _H324M_CALLBACKS_H_ */
