/***********************************************************************
        Copyright (c) 2002 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..

RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/

#ifndef _H324M_CALL_OBJECT_H_
#define _H324M_CALL_OBJECT_H_


#include "cmH245GeneralDefs.h"
#include "Rv3G324mCallTypes.h"
#include "rvh223defs.h"

/* Maximum number of states in the call's state queue.
 * We do our best not to have a state-change of a call from within another state-change
 * callback to give the best backward-compatibility we can and to reduce call-stack nesting
 */
#define RV_H324MCALL_STATE_MAX (5)

/* Dummy state definition, as held inside the queue */
#define RV_H324MCALL_STATE_DUMMY (0xff)

/* Size of the queue  for events received from the H.223 demux */
#define H223_EVENTS_QUEUE_SIZE (64)

#define CONTROL_OFFSET RvRoundToSize(sizeof(H324mCall), RV_ALIGN_SIZE)

/* Get the control object associated with a call. This object is placed right
   after the actual call struct. */
#define CALL_GET_CONTROL(_hCall) ( (HCONTROL)((RvUint8*)(_hCall) + CONTROL_OFFSET) )

/* Control buffer size */
#define CONTROL_BUFFER_SIZE 2050

/* Number of H.245 message to store before sending */
#define CONTROL_NUMBER_OF_MESSAGES 8


#ifdef __cplusplus
extern "C" {
#endif


/* Possible H.223 events we're storing in our queue */
typedef enum
{
    H223DemuxEventChannelDataReceived,
    H223DemuxEventControlMsgReceived,
    H223DemuxEventNotifyDrtx
} EH223DemuxEvent;


typedef struct
{
    EH223DemuxEvent event; /* Event we're storing */
    union
    {
        struct
        {
            HCHAN       chan; /* Channel who's retransmission request was discarded */
            RvUint16    sequenceNumber; /* Sequence number of discarded I-PDU */
        } drtx; /* NotifyDrtx parameters */

        struct
        {
            RvPvtNodeId     incomingMsg; /* Message that was received */
            EControlResult  eControlResult;
        } ctrl; /* ControlMsgReceived parameters */

        struct
        {
            HCHAN                           chan; /* Channel related to received data */
            Rv3G324mCallMonaMPCType         mpcChannel; /*MPC channel type*/
            RvUint8                        *bufferToRelease; /* Buffer we'll need to release */
            RvUint8                        *payload; /* Data to pass to application */
            RvUint32                        payloadSize; /* Size of data being passed to the application */
            EExtractionResult               eExtractionResult; /* Status of the received data */
        } chan; /* ChannelDataReceived parameters */
    } data;
} H223DemuxEvent;



typedef struct
{
    /* H.223 handles */
    HH223           hH223;        /* Handle to the H.223 instance */
    HMUXER          hMuxer;       /* Handle to the H.223 muxer instance */
    HDEMUX          hDemux;       /* Handle to the H.223 demux instance */
    HH223CONTROL    hH223Control; /* Handle to the H.223 control instance */

    /* H.223 streaming buffer */
    RvUint8              *h223StreaminBuffer; /* If != NULL, then we allocated this buffer on our own */
    RvSize_t             h223BufferSize; /* Size of streaming buffer (0 if streaming not supported */
    TMuxLevelCfg         muxLevel; /* The current mux-level of the call */

    /* H.223 multiplex reconfiguration */
    TMuxLevelCfg         dynamicMuxLevel; /* The mux-level to be changed dynamically by the multiplex reconfiguration procedure */
    RvUint32             channelsToBeCleared; /* Counter for the number of channels that has
                                                 to be cleared before changing mux level */
    RvBool               bUseInverseFlags; /* Defines whether the muxer sends inverse flags instead of ordinary flags */
    RvBool               bIsMuxReconfigurationOn; /* Defines whether we are in the middle of multiplex reconfiguration procedure */
    RvBool               bHMRInitiator;   /* Defines which side of the call initiated the HMR procedure */

    /* H.245 control */
    HCONTROL        hCtrl;    /* The H245 control handle */
    RvBool          bLockMsgSending; /* Defines whether to lock H.245 message sending in order to accumulate more than one message */
    RvBool          bLastTryToEncodeFailed; /* Did the last try to encode a message failed? */
    RvPvtNodeId     controlMultipleMessages[CONTROL_NUMBER_OF_MESSAGES]; /* Array of multiple H.245 messages to send */
    RvUint8         controlMultipleMessagesNumber; /* Defines the number of messages in the array */

    /* Call parameters */
    Rv3G324mCallState       state; /* Current state of the call */
    Rv3G324mCallStateMode   stateMode; /* Current state mode of the call */
    RvBool                  bIsFirstDropped; /* Defines whether this call is the first to drop the call and send EndSessionCommand message */
    RvBool                  bIsNetworkDisconnected; /* RV_TRUE if the network got this call disconnected */
    RvBool                  bIsCallOpened; /* RV_TRUE if the user called Rv3G324mCallOpen(), otherwise RV_FALSE */
    RvUint16                audioPayloadSize; /* The size of a payload of an audio channel. otherwise it is zero */
    RvBool                  bUseMultipleMessagesPerMuxPdu; /* RvBool: Defines whether to send more than one H.245 message in one MUX-PDU.*/
    RvInt32                 muxLevelSyncTimeout; /* Defines the timeout in milliseconds of the multiplex level synchronization */
    RvBool                  bIsStackDown; /* RV_TRUE if the user called Rv3G324mDestruct() without destructing the calls, otherwise RV_FALSE */
#if (RV_3G324M_USE_HIGH_AVAILABILITY == RV_YES)
    RvBool                  savedCall; /* RV_TRUE if call is a stored call for highavailability */
#endif
#if (RV_3G324M_USE_MONA == RV_YES)
    RvBool                  bUseMONA;
    RvBool                  bMPCBufferBelongs2App; /*If RV_TRUE, application releaseEv will be called*/ 
#endif /* USE_MONA */
    RvBool                  bUseACP;  /*RV_TRUE if ACP to be used in this call*/
    RvBool                  bACPBufferBelongs2App; /*buffers for incoming data processing*/
    RvBool                  bUseRetransmissionOnIdle; /*RV_TRUE if the call is currently in retransmissionOnIdle mode*/  
    RvBool                  bControlStartedBeforeSync; /* RV_TRUE if control was started before synchronization*/

    /* Timers */
    RvTimer                 *pIdleTimer; /* Zero timer that is used to notify the Idle state as soon as possible */
    RvTimer                 *pSyncTimer; /* Timer that is used to delay the notification of Synchronize state in order that flags will be sent for easy synchronization */
    RvTimer                 *pMuxReconfigurationTimer; /* Timer that is used to give enough time for the remote demux to synchronize on new mux level */
    RvTimer                 *pMuxLevelSyncTimer; /* Timer that is used to destruct calls that cannot synchronize H.223 multiplex level */
    RvTimer                 *pResetTimer; /* Timer that is used to send inverse flags before switching to state resetting */

#if (RV_H223_USE_STATISTICS == RV_YES)
    /* Statistics data */
    RvUint32                sentMediaBytes; /* Number of bytes sent on media channels */
    RvUint32                sentMediaPackets; /* Number of packets sent on media channels */
    RvUint32                receivedMediaBytes; /* Number of bytes received on media channels */
    RvUint32                receivedMediaPackets; /* Number of packets received on media channels */
    RvUint32                receivedMediaErrors; /* Number of packets with CRC errors in them that were received/ignored */
#endif

    /* H.223 Demux events queue - this is a cyclic queue */
    RvUint8                 qNextH223Event; /* Index of the next event we should handle */
    RvUint8                 qLastH223Event; /* Index of the last event we will handle */
    H223DemuxEvent          qH223Event[H223_EVENTS_QUEUE_SIZE]; /* The events queue itself */

    /* State queue - this is a cyclic queue */
    RvUint8                 queueNextState; /* Index of the next state we should handle */
    RvUint8                 queueNumStates; /* Number of state currently in the queue */
    RvUint8                 queueStates[RV_H324MCALL_STATE_MAX];
    RvUint8                 queueStateModes[RV_H324MCALL_STATE_MAX];

} H324mCall;



void* CloseCalls(IN EMAElement elem, IN void* param);

RvStatus H324mCallConstructAfterReset(H324mStack *app, H324mCall *call);

/******************************************************************************
 * H324mCallStop
 * ----------------------------------------------------------------------------
 * General: stop a call that is going to be saved for high availability.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 *          app                  - The stack instance
 * Input:   call                 - The call object.
 * Output:  none.
 *****************************************************************************/
RvStatus H324mCallStop(IN H324mStack *app,
                       IN H324mCall  *call);

#ifdef __cplusplus
}
#endif

#endif /* _H324M_CALL_OBJECT_H_ */

