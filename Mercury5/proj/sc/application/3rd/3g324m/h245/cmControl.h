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

#ifndef _CMCOTROL_
#define _CMCOTROL_

#include "rvlog.h"
#include "cmH245GeneralDefs.h"
#include "cmctrl.h"
#include "rvtimer.h"
#include "pvaltree.h"

#ifdef __cplusplus
extern "C" {
#endif


RV_DECLARE_HANDLE(HCONTROL); /* H.245 Control handle */

/* Maximum number of states in the channel's state queue.
 * We do our best not to have a state-change of a channel from within another state-change
 * callback to give the best backward-compatibility we can and to reduce call-stack nesting
 */
#define RV_3G324M_CHANNEL_STATE_MAX (4)


/* States of the control object we're dealing with */
typedef enum
{
    ctrlNotInitialized,
    ctrlInitialized,
    ctrlConnected,
    ctrlConference,
    ctrlEndSession,
    ctrlTransmittedSidePaused, /* TCS0 was received. Waiting to get out of this state */
    ctrlMesFinished
} H245ControlState;

H245ControlState controlGetState(HCONTROL ctrl);

typedef enum
{
    CapStatusReleased,
    CapStatusSent,
    CapStatusAcknowledged,
    CapStatusRejected
} CapStatus;

typedef enum
{
    MesStatusReleased,
    MesStatusSent,
    MesStatusAcknowledged,
    MesStatusRejected
} MesStatus;

/************************************************************************
 * outgoingCapInfo struct
 * Outgoing capabilities negotiated for the call
 ************************************************************************/
typedef struct
{
    RvBool      waiting;        /* RV_TRUE if we're waiting for an Ack */
    RvTimer*    timer;          /* Timer used for negotiations of capabilities */
    RvUint8     seqNum;         /* Sequence number of the current TCS exchange between the endpoints */
    RvPvtNodeId termNodeId;     /* Current outgoing capabilities of this terminal */
    int         rejectCause;    /* Reject cause if rejected */
} OutgoingCapInfo;



/************************************************************************
 * incomingCapInfo struct
 * Incoming capabilities negotiated for the call
 ************************************************************************/
typedef struct
{
    char        pID[12];        /* Protocol Identifier of incoming capability. */
    int         pIDLen;
    RvUint8     seqNum;
    RvPvtNodeId termNodeId;
    RvBool      manualResponse;
} IncomingCapInfo;





/* Request Mode Information */
typedef struct
{
    RvUint8  seqNum;
    RvTimer* timer;
} OutRequestModeInfo;

typedef struct
{
    RvUint8 seqNum;
} InRequestModeInfo;




/* Master - Slave Information */
typedef enum
{
    MsdStateIdle,
    MsdStateIncomingAwaitingManualAcknoledge,
    MsdStateIncomingAwaitingResponse,
    MsdStateOutgoingAwaitingResponse
} MsdState;

typedef enum
{
    MsdStatusIndeterminate,
    MsdStatusMaster,
    MsdStatusSlave
} MsdStatus;


typedef struct
{
    MsdState   state;
    RvTimer*   timer;
    MsdStatus  status;
    RvUint8    myTerminalType;
    RvUint8    remoteTerminalType;
    int        myStatusDeterminationNumber;
    int        statusDeterminationNumber;
    int        count;
    RvBool     manualResponse;
} MasterSlaveInfo;





/* Round Trip Information */

typedef struct
{
    RvTimer*    timer;
    RvInt32     timeStart;
    RvUint8     seqNum;
    RvBool      waiting;
} RoundTripInfo;

/* The channel state enumeration */
typedef enum
{
    ChannelStateReleased = -1,
    ChannelStateIdle,
    ChannelStateAwaitingEstablishment,
    ChannelStateFaststart,
    ChannelStateFsAwaitingEstablish,
    ChannelStateEstablished,
    ChannelStateAwaitingRelease,
    ChannelStateAwaitingConfirmation
} ChannelState;


#if (RV_H245_SUPPORT_H223_PARAMS == 1)
/* ======= H.223 related parameters ======= */


/* parameters of Adaptation Layer AL1 */
typedef struct
{
    RvInt32 maxSduSize;                 /* {0..65535}, max size (in bytes) of transferred AL-SDU */
    RvBool  bIsFramed;                  /* Defines whether the bit stream is framed or unframed */
} H223AdaptationLayer1Parameters;

/* parameters of Adaptation Layer AL2 */
typedef struct
{
    RvBool  sequenceNumbering;          /* Indicates using optional Sequence Numbering */
    RvInt32 maxSduSize;                 /* {0..65535}, max size (in bytes) of transferred AL-SDU */

} H223AdaptationLayer2Parameters;

/* parameters of Adaptation Layer AL3 */
typedef struct
{
    cmH223ControlFieldSize  controlFieldSize;  /* {0..2} using sequence numbering and retransmission == (m_nControlFieldSize != 0) */
    RvInt32                 maxSduSize;        /* {0..65535}, max size (in bytes) of transferred AL-SDU */
    RvUint32                sendBufferSize;    /* for AL-PDU buffering. Should be 1024 bytes at the least */
    RvInt32                 localTimerTimeout; /* Local Timer value, used for retransmission */
    /* reverse oarameters */
    cmH223ControlFieldSize  reverseControlFieldSize;    /* controlFieldSize in reverse parameters */
    RvUint32                reverseSendBufferSize;      /* sendBufferSize in reverse parameters */
} H223AdaptationLayer3Parameters;


typedef union
{
    H223AdaptationLayer1Parameters  adaptationLayer1Params;
    H223AdaptationLayer2Parameters  adaptationLayer2Params;
    H223AdaptationLayer3Parameters  adaptationLayer3Params;
#if (RV_H223_USE_MUX_LEVEL_3 == RV_YES)
    cmH223ALxMConfig                adaptationLayerxMParams;
#endif
} AdaptationLayerUnion;

typedef enum
{
	channelInternalStateNULL = 0,
	channelInternalStateOLCSent ,
	channelInternalStateOLCReceived = channelInternalStateOLCSent,
	channelInternalStateAcked,
    channelInternalStateRejectedNoReason,
	channelInternalStaterejectPending,
	channelInternalStaterejectedReOpenRequired,
    channelInternalStaterejectedReOpenExpected =   channelInternalStaterejectedReOpenRequired
}channelInternalState;


typedef struct
{
    cmH223ALLevel               adaptationLayerType;           /* type of Adaptation Layer */
    AdaptationLayerUnion        adaptationLayerData;
    void                        *alTxContext;             /* AL transmitting context for the user */
    void                        *alRxContext;             /* AL receiving context for the user */
    RvBool                      bRecvLCBufferBelongsToApplication; /* defines whether the receive buffer of the logical channel is in the responsibility of the application */
    RvBool                      isSegmentable;                 /* indicates if AL-SDU could be segmented during transferring by Muxer */
    RvUint32                    bitRate;  /* The bit rate of the media in units of 100 bits/s. */
    cmChannelAudioType          eAudioType; /* Audio type of an audio channel */
    cmChannelDataType           eDataType; /* The data type of the channel */
    RvBool                      bIgnoreCorruptedAlSdu; /* Defines whether to pass the user corrupted Al-SDU or ignore it */

    /* per call... */
    RvUint                      bMaxMuxPduSize;
    RvBool                      bSkewIndication;
    RvBool                      bIsDuplexReverseNullData;  /*if true - the reverse parameters 
                                                            has nullData in its data type*/
#if (RV_3G324M_USE_MONA == RV_YES)
    /*MONA MPC*/
    RvBool                      bIsMPCChannel;               /*RV_TRUE if this is a h245 channel object
                                                            of a MPC channel*/
#endif /* USE_MONA */
    cmH245ChannelConflictType   conflictType; /*The type of conflict caused by the conflicting channel*/
    channelInternalState        internalState; /*the internal state of the channel, used for the channel's state machine for conflicts*/
}ChannelH223Params;

typedef struct
{
    RvTimer*   timer;
    RvBool     waiting;    /* a boolean flag , indication the state of the process*/
    RvUint8    seqNum;     /* a number for the enumeration of the 
                              multiplexEntrySend messages*/
    RvUint16   tableInd;   /* table indexes that were set in the last
                              multiplexEntrysend message*/
    
} OutgoingMESInfo;

typedef struct
{
    RvUint8     seqNum;     /* a number for the enumeration of the 
                               multiplexEntrySend messages*/
    RvBool      manualResponse; /* RV_TRUE if the MES message should be Acked or Rejected
                                   manually by the application */
} IncomingMESInfo;

#endif /* #if (RV_H245_SUPPORT_H223_PARAMS == 1) */


typedef struct ChannelElem H245Channel;

#if (RV_H245_SUPPORT_H225_PARAMS == 1)
/* ======= H.225 related parameters ======= */

typedef struct
{
    RvUint8                 sessionId; /* H.225 Session ID of this channel */
    RvUint8                 dynamicPayloadNumber; /* 0 is invalid. Values are 96-127 */

    RvInt32                 fastStartChannelIndex; /* -1 for normal channels. For faststart channels,
                                                      this is the index of the approval in callElem. */
    RvInt32                 portNumber; /* portNumber field set by the local side for this channel.
                                           This is an optional field used for ATM. */
    RvBool                  bFlowControlToZero;
    RvBool                  bForceSecondary; /* RV_TRUE if we want to force this channel to be a secondary
                                                channel (i.e - not have a session ID value of 1,2 or 3) */

    /* Channel associations */
    H245Channel*            pPartner;  /* Opposite channel with the same session ID */
    H245Channel*            pAssociated;   /* Pointer to the associated channel */

    /* RTP and RTCP addresses for the channel. Stored as node id's */
    RvPvtNodeId             recvRtpAddressID; /* Local RTP address for this channel. -1 if NA */
    RvPvtNodeId             recvRtcpAddressID; /* Local RTCP address for this channel. -1 if NA */
    RvPvtNodeId             sendRtpAddressID; /* Remote RTP address for this channel. -1 if NA */
    RvPvtNodeId             sendRtcpAddressID; /* Remote RTCP address for this channel. -1 if NA */

    RvPvtNodeId             redEncID; /* Redundancy encoding of the channel (redundancyEncoding field in h2250LogicalChannelParameters) */
    RvPvtNodeId             transCapID; /* Transport capabilities of the channel (transportCapability field in h2250LogicalChannelParameters) */

    /* Separate Stack related information */
    RvPvtNodeId             separateStackID; /* Separate Stack of the channel (separateStack.networkAddress.localAreaAddress) */
    RvInt32                 externalReferenceLength; /* Separate Stack's external reference length */
    RvChar                  externalReference[256]; /* Separate Stack's external reference */
    RvBool                  isAssociated; /* RV_TRUE if the channel is associated - used for separateStack information */
    cmT120SetupProcedure    t120SetupProcedure;
    cmTerminalLabel         source; /* Type of terminal on source side of this channel */
    cmTerminalLabel         destination; /* Type of terminal on destination side of this channel */
}ChannelH225Params;

typedef enum
{
    fssNo,
    fssPrplSend,
    fssPrplRcvd,
    fssAcptSend,
    fssAcptRcvd,
    fssIdle,
    fssRej
} fssFlags;

#endif /* #if (RV_H245_SUPPORT_H225_PARAMS == 1) */



/* The channelParams union to decide between H.225 parameters and H.223 parameters */
typedef union
{
#if (RV_H245_SUPPORT_H225_PARAMS == 1)
    ChannelH225Params   h225Params;
#endif /* #if (RV_H245_SUPPORT_H225_PARAMS == 1) */

#if (RV_H245_SUPPORT_H223_PARAMS == 1)
    ChannelH223Params   h223Params;
#endif /* #if (RV_H245_SUPPORT_H223_PARAMS == 1) */

}ChannelParamsUnion;


/* RvH245ChannelParamsType - Defines whether the parameters are H.225 or H.223 */
typedef enum
{
    RvH245ChannelParamsUndefined = -1,
    RvH245ChannelParamsH225,
    RvH245ChannelParamsH223
} RvH245ChannelParamsType;



/************************************************************************
 * Control struct
 * This structure holds the H.245 control information necessary for
 * connecting a regular call with H245 channel.
 ************************************************************************/
typedef struct
{
     /* The control state */
    H245ControlState        eState;          /* Control channel's state */
    H245ControlState        eLastState;      /* last state before receiving TCS0 */
    RvBool                  bIsConference;   /* RV_TRUE if we receive a conference indication */

    /* The capabilities information */
    OutgoingCapInfo         outCap;          /* Outgoing capabilities */
    IncomingCapInfo         inCap;           /* Incoming capabilities */
    CapStatus               eInCapStatus;    /* Incoming capabilities status */
    CapStatus               eOutCapStatus;   /* Outgoing capabilities status */

    /* Master - Slave information */
    MasterSlaveInfo         msd;             /* MasterSlaveDetermination process structure */
    RvBool                  bIsMasterSlave;  /* RV_TRUE if at least 1 MSD procedure was finished */
    RvBool                  bIsMaster;       /* RV_TRUE if local endpoint is master in this call */

    /* Request Mode */
    OutRequestModeInfo      outRequestMode;
    InRequestModeInfo       inRequestMode;

   /* Channel Information */
    RvH245ChannelParamsType eParamsType;
    RvUint16                logicalChannelOut;
    RvBool                  bIsDerived;
    int                     conflictChannels;   /* Used to prevent sid conflicts. Causes the stack to reject incoming
                                              simplex channels with sid=0 until all offered channels are ACKed,
                                              timed out, rejected or dropped. */

    /* General H245 Information */
    RoundTripInfo           roundTrip;
    RvBool                  multiPointMode;

    /* Link to the first channel in the channel list */
    HCHAN                   hFirstChannel;

#if (RV_H245_SUPPORT_H223_PARAMS == 1)
    /* multiplex entry send information */
    OutgoingMESInfo         outMES;             /* multiplex entry send process structure */
    IncomingMESInfo         inMES;              /* multiplex entry send process structure */
    MesStatus               eInMesStatus;       /* Incoming multiplex entry send status */
    MesStatus               eOutMesStatus;      /* Outgoing multiplex entry send status */
    RvUint8                 eInMesStatusCount;  /* Counter of number of incoming MES that are not answered yet */
    /* reset information */
    RvBool                  bResetInitiator; /* RV_TRUE if the local side initiated the reset procedure */
    RvBool                  bReset; /* Defines whether the call is being reset */
    /* ACP */
    RvBool                  bACPinUse;   /*Defines if the call uses ACP for fast connection*/
    /*MPC*/
    RvBool                  bMPCinUse;    /*Defines if the call uses MPC for fast connection*/
#endif /* #if (RV_H245_SUPPORT_H223_PARAMS == 1) */

#if (RV_H245_SUPPORT_H225_PARAMS == 1)
    /* H.323 information */
    cmTerminalLabel         myTerminalLabel;
    cmTransportAddress      mcLocationTA;

    /* Session ID related information */
    RvBool                  bFirstAudioIn;   /* RV_TRUE if no incoming Audio channel with SessionId=1 is established */
    RvBool                  bFirstVideoIn;   /* RV_TRUE if no incoming Video channel with SessionId=2 is established */
    RvBool                  bFirstDataIn;    /* RV_TRUE if no incoming Data channel with SessionId=3 is established */
    RvBool                  bFirstAudioOut;  /* RV_TRUE if no outgoing Audio channel with SessionId=1 is established */
    RvBool                  bFirstVideoOut;  /* RV_TRUE if no outgoing Video channel with SessionId=2 is established */
    RvBool                  bFirstDataOut;   /* RV_TRUE if no outgoing Data channel with SessionId=3 is established */
    RvUint8                 nextFreeSID;     /* Next sessionId that is not used. Must be of type RvUint8! */

    /* fast start */
    fssFlags                fastStartState;  /* State of fastStart procedure of this call (fssNo, fssRequest, fssAck) */
    RvPvtNodeId*            fastStartNodesPrplSend;
    RvUint8                 fastStartNodesPrplSendCount;
    RvPvtNodeId*            fastStartNodesAcptSend;
    RvUint8                 fastStartNodesAcptSendCount;
    RvPvtNodeId*            fastStartNodesPrplRcvd;
    RvUint8                 fastStartNodesPrplRcvdCount;
    RvPvtNodeId*            fastStartNodesAcptRcvd;
    RvUint8                 fastStartNodesAcptRcvdCount;
    RvUint8*                fastStartIndexes;

    /* misc */
    RvBool                  callInitiator;
    RvBool                  bIsFastStartFinished;  /* Indication whether the fast start process was finished */
    cmExtendedFastConnectState_e eExtendedFastConnectState;
#endif  /* (RV_H245_SUPPORT_H225_PARAMS == 1) */

    RvBool                  bIsControl;      /* Indication for H.245 connection */
    RvBool                  bEndSessionSent; /* Indication for H.245 termination */
    RvBool                  bSaveCallIndication; /* Indication for H.245 termination */

    /* Control Offset */
    int                     controlOffset;

    /* stored incoming OLCs before control got connected */
    RvPvtNodeId             incomingOLCs[2];
} H245Control;





/************************************************************************
 * Channel struct
 * This structure holds the channel information stored in the stack
 ************************************************************************/
struct ChannelElem
{
    /* Reference to the H245 control */
    HCONTROL            hCtrl;     /* Control object holding this channel. */

    /* Specific channel parameters */
    RvH245ChannelParamsType     eType; /* Type of channel - H.223 or H.225 */
    ChannelParamsUnion          data; /* Content of specific channel parameters */

    /* General H.245 channel information */
    RvBool              bIsDuplex;     /* Is the channel unidirectional or bidirectional? */
    RvUint16            myLogicalChannelNum;   /* Logical Channel Number of this channel */
    RvUint16            reverseLogicalChannelNum;
    RvBool              bOrigin;   /* RV_TRUE if we're the origin of this channel, RV_FALSE otherwise */
    RvInt32             remotePortNumber;   /* portNumber field set by the remote side for this channel */
    ChannelState        eState;          /* The state of the channel */
    RvPvtNodeId         dataTypeID;     /* The data type node id of this channel */
    RvPvtNodeId         reverseDataTypeID;     /* The data type node id of the reverse parameters in bi - directional channel */
    RvPvtNodeId         requestCloseParamID;
    cmRejectLcnReason   eRejectReason; /* The reject reason received on an outgoing channel. */
    RvUint16            capTableEntryNum; /* Capability table entry number used to open this channel with H.245 AutoCaps */

    /* Timers */
    RvTimer*            pTimer;
    RvTimer*            pRequestCloseTimer;
    RvTimer*            pMediaLoopTimer;

    /* Associated channels */
    H245Channel*        pReplacementCh; /* Channel we're replacing with this one */
    H245Channel*        pBase; /* The channel that this channel is dependent on (through forwardLogicalChannelDepedency) */

    /* Links to other channels on the same call */
    H245Channel*        pPrev;     /* Previous channel that belongs to the same call */
    H245Channel*        pNext;     /* Next channel that belongs to the same call */

    /* state queue - this is a cyclic queue */
    RvUint8                     q_nextState; /* Index of the next state we should handle */
    RvUint8                     q_numStates; /* Number of state currently in the queue */
    RvUint8                     q_states[RV_3G324M_CHANNEL_STATE_MAX];
    RvUint8                     q_stateModes[RV_3G324M_CHANNEL_STATE_MAX];
};


#if (RV_LOGMASK & (RV_LOGLEVEL_ENTER | RV_LOGLEVEL_LEAVE))
#define H245APIEnter(_args) if (app->evHandlers.pfnAPIEnterEv != NULL) app->evHandlers.pfnAPIEnterEv _args
#define H245APIExit(_args) if (app->evHandlers.pfnAPIExitEv != NULL) app->evHandlers.pfnAPIExitEv _args
#define H245CBEnter(_args) if (app->evHandlers.pfnCBEnterEv != NULL) app->evHandlers.pfnCBEnterEv _args
#define H245CBExit(_args) if (app->evHandlers.pfnCBExitEv != NULL) app->evHandlers.pfnCBExitEv _args

#else
/* No logs at all */
#define H245APIEnter(_args)
#define H245APIExit(_args)
#define H245CBEnter(_args)
#define H245CBExit(_args)

#endif

#ifdef __cplusplus
}
#endif


#endif  /* _CMCOTROL_ */

