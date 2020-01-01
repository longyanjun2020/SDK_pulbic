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

#ifndef CMCTRL_H
#define CMCTRL_H


#include "transpcap.h"
#include "redencod.h"
#include "userinput.h"


#ifdef __cplusplus
extern "C" {
#endif


RV_DECLARE_HANDLE(HAPPCHAN);
RV_DECLARE_HANDLE(HCHAN);




/* This type exists for backward compatibility only. */
typedef
int (*cmNewProtocolEH)(void);



typedef enum
{
    cmChannelStateDialtone,
    cmChannelStateRingBack,
    cmChannelStateConnected,
    cmChannelStateDisconnected,
    cmChannelStateIdle,
    cmChannelStateOffering
} cmChannelState_e;

typedef enum
{
    cmChannelStateModeOn,
    cmChannelStateModeOff,

    cmChannelStateModeDisconnectedLocal,
    cmChannelStateModeDisconnectedRemote,
    cmChannelStateModeDisconnectedMasterSlaveConflict,
    cmChannelStateModeDuplex,

    cmChannelStateModeDisconnectedReasonUnknown,
    cmChannelStateModeDisconnectedReasonReopen,
    cmChannelStateModeDisconnectedReasonReservationFailure,

    cmChannelStateModeReconfigured

} cmChannelStateMode_e;



/* cmChannelDataType
 * ----------------------------------------------------------------------------
 * Channel data type enumeration.
 * This enumeration is used by 3G-324M and H.245 AutoCaps add-on APIs to
 * distinguish between different channels, as they require different handling.
 */
typedef enum
{
    cmChannelDataTypeUnknown = -1,
    cmChannelDataTypeAudio,
    cmChannelDataTypeVideo,
    cmChannelDataTypeVideo2,
    cmChannelDataTypeData,
    cmChannelDataTypeAll
} cmChannelDataType;

typedef enum
{
  cmCapReceive=1,
  cmCapTransmit=2,
  cmCapReceiveAndTransmit=3
} cmCapDirection;



/* cmCapRejectCause
 * ----------------------------------------------------------------------------
 * TerminalCapabilitySetReject message cause types.
 * This enumeration should be used with cmCallCapabilitiesReject().
 */
typedef enum
{
    cmCapRejectCauseUnspecified = 1,
    cmCapRejectCauseUndefinedTableEntry = 2,
    cmCapRejectCauseDescriptorExceeded = 3,
    cmCapRejectCauseTableEntryExceeded = 4
} cmCapRejectCause;


typedef enum
{
  cmCapEmpty=0, /* in case of an empty capability set */
  cmCapAudio=1, /* in case of receiveAudioCapability,
                             transmitAudioCapability or
                             receiveAndTransmitAudioCapability */
  cmCapVideo=2, /* in case of receiveVideoCapability,
                             transmitVideoCapability or
                             receiveAndTransmitVideoCapability */
  cmCapData=3, /* in case of receiveDataApplicationCapability,
                            transmitDataApplicationCapability or
                            receiveAndTransmitDataApplicationCapability */
  cmCapNonStandard=4, /* in case of nonstandard capability */
  cmCapUserInput=5, /* in case of receiveUserInputCapability ,
                                 transmitUserInputCapability or
                                 receiveAndTransmitUserInputCapability */
  cmCapConference=6, /* in case of conferenceCapability */
  cmCapH235=7, /* in case of h235SecurityCapability */
  cmCapMaxPendingReplacementFor=8, /* in case of maxPendingReplacementFor capability */
  cmCapGeneric=9, /* in case of genericControlCapability capability */
  cmCapMultiplexedStream=10, /* in case of receiveMultiplexedStreamCapability,
                                          transmitMultiplexedStreamCapability or
                                          receiveAndTransmitMultiplexedStreamCapability */
  cmCapAudioTelephonyEvent=11, /* in case of receiveRTPAudioTelephonyEventCapability */
  cmCapAudioTone=12, /* in case of receiveRTPAudioToneCapability */
  cmCapFEC=13, /* Forward Error Correction */
  cmCapMultiplePayloadStream=14 /* in case of multiplePayloadStreamCapability */
} cmCapDataType;

#if (RV_H245_SUPPORT_H225_PARAMS == 1)
#include "faststart.h"
#endif


typedef struct
{
  char*             name;
  RvInt32           capabilityId; /* capabilityTableEntryNumber */
  int               capabilityHandle; /* capability item message tree (video/audio/data/nonStandard) */
  cmCapDirection    direction;
  cmCapDataType     type;
} cmCapStruct;


typedef enum
{
  cmCapAccept=1,
  cmCapReject
} cmCapStatus;


typedef enum
{
  cmMSSlave=1,
  cmMSMaster,
  cmMSError
} cmMSStatus;



typedef enum
{
  cmRequestCloseRequest, /* Received request to close channel */
  cmRequestCloseConfirm, /* Request to close this channel is confirmed */
  cmRequestCloseReject   /* Request to close this channel is rejected */
} cmRequestCloseStatus;


typedef enum
{
  cmMediaLoopRequest,    /* Received request for a media loop on a channel */
  cmMediaLoopConfirm,    /* Media loop confirmed */
  cmMediaLoopOff         /* Media loop on channel is canceled */
} cmMediaLoopStatus;



typedef struct
{
  char* data; /* GeneralString formatted data */
  int   length; /* in bytes */
} cmUserInputData;


typedef enum
{
  /* The path in parenthesis indicates the nodeId syntax */
  cmReqModeRequest,    /* Request mode (requestMode.requestedModes) */
  cmReqModeAccept,     /* Request acknowledged (requestModeAck.response) */
  cmReqModeReject,     /* Request rejected (requestModeReject.cause) */
  cmReqModeReleaseOut, /* Outgoing request released due to timeout (N/A) */
  cmReqModeReleaseIn   /* Incoming request released due to timeout (N/A) */
} cmReqModeStatus;


typedef enum
{
  cmMiscMpOn,  /* Multipoint mode command is on (set) */
  cmMiscMpOff  /* Multipoint mode command is off (cancel) */
} cmMiscStatus;


typedef struct
{
  char  name[32];
  RvInt32 entryId; /* ModeElement node ID */
} cmReqModeEntry;



typedef enum
{
  cmControlStateConnected,
  cmControlStateConference,
  cmControlStateTransportConnected,
  cmControlStateTransportDisconnected,
  cmControlStateFastStart,
  cmControlStateFastStartComplete
} cmControlState;


typedef enum
{
  cmControlStateModeNull,
  cmControlStateModeFastStartNoMoreChannels,
  cmControlStateModeFastStartRejected
} cmControlStateMode;


typedef enum
{
  cmCloseReasonUnknown=0,
  cmCloseReasonReopen   ,
  cmCloseReasonReservationFailure,
  cmCloseReasonNormal /* for request close only */
} cmCloseLcnReason;


typedef enum
{
  cmRejectReasonUnspecified=0,
  cmRejectReasonUnsuitableReverseParameters,
  cmRejectReasonDataTypeNotSupported,
  cmRejectReasonDataTypeNotAvailable,
  cmRejectReasonUnknownDataType,
  cmRejectReasonDataTypeALCombinationNotSupported,
  cmRejectReasonMulticastChannelNotAllowed,
  cmRejectReasonInsufficientBandwidth,
  cmRejectReasonSeparateStackEstablishmentFailed,
  cmRejectReasonInvalidSessionID,
  cmRejectReasonMasterSlaveConflict,
  cmRejectReasonWaitForCommunicationMode,
  cmRejectReasonInvalidDependentChannel,
  cmRejectReasonReplacementForRejected,
  cmRejectReasonSecurityDenied,
  cmRejectReasonLast
} cmRejectLcnReason;



typedef enum
{
    cmVideoFreezePicture=0,
    cmVideoSendSyncEveryGOB,
    cmVideoSendSyncEveryGOBCancel,
    cmSwitchReceiveMediaOff,
    cmSwitchReceiveMediaOn,
    cmVideoFastUpdatePicture
} cmMiscellaneousCommand;


/* Enumeration of messages supported by the cmEvCallControlMessage callback function */
typedef enum
{
    /* Conference Request */
    h245crqTerminalListRequest,
    h245crqMakeMeChair,
    h245crqCancelMakeMeChair,
    h245crqDropTerminal,
    h245crqRequestTerminalID,
    h245crqEnterH243Password,
    h245crqEnterH243TerminalID,
    h245crqEnterH243ConferenceID,
    h245crqRequestChairTokenOwner,
    h245crqRequestTerminalCertificate,
    h245crqBroadcastMyLogicalChannel,
    h245crqMakeTerminalBroadcaster,
    h245crqSendThisSource,
    h245crqRequestAllTerminalIDs,
    h245crqRemoteMCRequest,

    /* Conference Response*/
    h245crsMCTerminalIDResponse,
    h245crsTerminalIDResponse,
    h245crsConferenceIDResponse,
    h245crsPasswordResponse,
    h245crsTerminalListResponse,
    h245crsVideoCommandReject,
    h245crsTerminalDropReject,
    h245crsMakeMeChairResponse,
    h245crsChairTokenOwnerResponse,
    h245crsTerminalCertificateResponse,
    h245crsBroadcastMyLogicalChannelResponse,
    h245crsMakeTerminalBroadcasterResponse,
    h245crsSendThisSourceResponse,
    h245crsRequestAllTerminalIDsResponse,
    h245crsRemoteMCResponse,

    /* Conference Indications */
    h245ciSbeNumber,
    h245ciTerminalJoinedConference,
    h245ciTerminalLeftConference,
    h245ciSeenByAtLeastOneOther,
    h245ciCancelSeenByAtLeastOneOther,
    h245ciSeenByAll,
    h245ciCancelSeenByAll,
    h245ciTerminalYouAreSeeing,
    h245ciRequestForFloor,
    h245ciWithdrawChairToken,
    h245ciFloorRequested,
    h245ciTerminalYouAreSeeingInSubPictureNumber,
    h245ciVideoIndicateCompose,

    /* Conference Commands */
    h245ccBroadcastMyLogicalChannel,
    h245ccCancelBroadcastMyLogicalChannel,
    h245ccMakeTerminalBroadcaster,
    h245ccCancelMakeTerminalBroadcaster,
    h245ccSendThisSource,
    h245ccCancelSendThisSource,
    h245ccDropConference,
    h245ccSubstituteConferenceIDCommand,

    /* Miscellaneous Command */
    h245mcEqualiseDelay,
    h245mcZeroDelay,
    h245mcMaxH223MUXPDUsize,
    h245mcEncryptionUpdate,
    h245mcEncryptionUpdateRequest,
    h245mcProgressiveRefinementStart,
    h245mcProgressiveRefinementAbortOne,
    h245mcProgressiveRefinementAbortContinuous,
    h245mcVideoBadMBs,
    h245mcLostPicture,
    h245mcLostPartialPicture,
    h245mcRecoveryReferencePicture,

    /* Indication */
    h245iJitterIndication,
    h245iH223SkewIndication,
    h245iFunctionNotSupported,
    h245iFlowControlIndication,
    h245iVendorIdentification,

    /* Miscellaneous Indication */
    h245miMultipointZeroComm,
    h245miCancelMultipointZeroComm,
    h245miMultipointSecondaryStatus,
    h245miCancelMultipointSecondaryStatus,
    h245miVideoIndicateReadyToActivate,
    h245miVideoNotDecodedMBs,

    /* Generic Messages */
    h245grqGenericRequest,
    h245grsGenericResponse,
    h245gcGenericCommand,
    h245giGenericIndication
} cmH245MessageType;


typedef enum
{
    cmH245ConflictNoConflict = -1,
    cmH245ConflictUnansweredProposals,
    cmH245ConflictMasterSlaveBiDirectProposal,
    cmH245ConflictMasterBiDirectProposal,
    cmH245ConflictSlaveBiDirectProposal,
    cmH245ConflictSlaveBiDirectProposalRejected,
    cmH245ConflictMasterNotRejected
} cmH245ChannelConflictType;




#if (RV_H245_SUPPORT_H225_PARAMS == 1)
/* ------------------------- H.225 structures -------------------------- */

typedef struct
{
  RvUint8 mcuNumber; /* Constraint: 0..192 */
  RvUint8 terminalNumber; /* Constraint: 0..192 */
} cmTerminalLabel;




typedef struct
{
  HCHAN hsChan; /* Outgoing: New reverse channel. Incoming: Keep the existing channel
           Null: New unassociated reverse channel. */

  /* ! Set the following fields only for new outgoing channels. */

  HCHAN hsChanAssociate; /* Associate channel. FFS */

  char *channelName; /* Channel name from the configuration, or NULL for handle setting. */
  RvInt32 channelDataTypeHandle; /* Data type (HPVT) tree handle. channelName should be NULL. */

  cmTerminalLabel terminalLabel; /* Use 0xffff if the label is unavailable. */

  char *sessionDescription;
  int sessionDescriptionLength; /* Number of bytes in sessionDescription. */

  cmTransportAddress rtpAddress;
  cmTransportAddress rtcpAddress;

    /* Used only in the cmCallSetChannelsExt function. */
  int uid; /* Unique ID may be index in array.*/
  int dependency; /* Unique ID of the element that describes the channel on which 
                     this channel is dependent. */
  /* If its value is equal -1, the parameter is not used. */
  int redEncodingId; /* Node ID of redundancyEncoding PVT built by the user. */

} cmChannelStruct;

typedef struct
{
  int redundancyEncodingMethodId;
  int secondaryEncodingId;
} cmRedundancyEncoding;



typedef enum
{
  cmIssueJoin   =0,
  cmIssueQueryAndJoin,
  cmIssueCreate ,
  cmIssueInvite ,
  cmWaitForInvite,
  cmOriginateCall,
  cmWaitForCall,
  cmIssueQuery
} cmT120SetupProcedure;

/* -------------------------H.225 functions ---------------------------*/

RVAPI
int RVCALLCONV cmChannelSameSession(
             /* Gets the same session opposite channel of hsChan. */
             IN     HCHAN           hsChan,
             OUT    HAPPCHAN*       haSameSession,
             OUT    HCHAN*          hsSameSession
             );

RVAPI int RVCALLCONV /* Returns the session ID for this channel. */
cmChannelSessionId(
           /* Gets the session ID of the channel. */
           IN   HCHAN           hsChan
           );



RVAPI int RVCALLCONV
cmChannelSetT120Setup(
             IN      HCHAN               hsChan,
             IN      cmT120SetupProcedure t120SetupProc);

RVAPI int RVCALLCONV
cmChannelGetT120Setup(
             IN      HCHAN               hsChan,
             OUT      cmT120SetupProcedure *t120SetupProc);


/* Sets FlowControlToZero on the incoming channel during the establishing process,
   used before answering. */

RVAPI int RVCALLCONV
cmChannelSetFlowControlToZero(
             IN      HCHAN               hsChan,
             IN      RvBool              flowControl);



RVAPI
int RVCALLCONV cmChannelSetNSAPAddress(
        IN      HCHAN               hsChan,
        IN      const RvChar*       address,
        IN      int                 length,
        IN      RvBool              multicast);



RVAPI
int RVCALLCONV cmChannelSetATMVC(
        IN      HCHAN               hsChan,
        IN      int                 portNumber);


RVAPI
int RVCALLCONV cmChannelSetAddress(
        IN      HCHAN               hsChan,
        IN      RvUint32            ip,
        IN      RvUint16            port);

RVAPI
int RVCALLCONV cmChannelSetRTCPAddress(
        IN      HCHAN               hsChan,
        IN      RvUint32            ip,
        IN      RvUint16            port);

RVAPI
int RVCALLCONV cmChannelSetDynamicRTPPayloadType(
        IN      HCHAN           hsChan,
        IN      RvInt8          dynamicPayloadType);


RVAPI int RVCALLCONV
cmCallSetTerminalLabel(
               /* Sets the remote endpoint terminal label. */
               IN      HCALL               hsCall,
               IN      cmTerminalLabel*    terminalLabel
               );

RVAPI int RVCALLCONV /* Negative value on failure if the terminal label is not 
                        defined for this terminal. */
cmCallGetTerminalLabel(
               /* Gets the local endpoint terminal label. */
               IN      HCALL               hsCall,
               OUT     cmTerminalLabel*    terminalLabel /* User allocated. */
               );


/* When the conference becomes active, the master (MC) terminal shall call cmCallDeclareMC() to
   indicate the new conference status. */
RVAPI
int RVCALLCONV cmCallDeclareMC(
                 /* Declare this terminal to be the MC of the call. */
        IN      HCALL               hsCall
        );




/* When the conference becomes active, these functions provide the address of the Active MC. */
RVAPI
int RVCALLCONV cmCallGetMcTransportAddress(
                IN      HCALL               hsCall,
                OUT     cmTransportAddress* ta);


#if (RV_H323_TRANSPORT_ADDRESS != RV_H323_TRANSPORT_ADDRESS_ANY) || defined RV_H323_COMPILE_WITH_DEAD_FUNCTIONS
RVAPI
int RVCALLCONV cmCallGetMCAddress(
                /* Not supported when working with IPv6. */
        IN      HCALL               hsCall,
        OUT     RvUint32*           ip,
        OUT     RvUint16*           port);
#endif /* (RV_H323_TRANSPORT_ADDRESS != RV_H323_TRANSPORT_ADDRESS_ANY) || (RV_H323_COMPILE_WITH_DEAD_FUNCTIONS) */


/* The master (MC) terminal shall use cmCallSetChannels() to force the remote terminal to open
   the indicated channels for transmit. */
RVAPI
int RVCALLCONV cmCallSetChannels(
                 /* As Active MC, sets transfer channels for the remote terminal. */
        IN      HCALL               hsCall,
        IN      int                 channelSetSize, /* The number of elements in channelSet. */
        IN      cmChannelStruct     channelSet[]
        );

/* The master (MC) terminal shall use cmCallSetChannels() to force the remote terminal to open
   the indicated channels for transmit. Adds parameters specified in version 3,such as 
   redEncoding and sessionDependancy. */
RVAPI
int RVCALLCONV cmCallSetChannelsExt(
                 /* As Active MC, sets transfer channels for the remote terminal. */
        IN      HCALL               hsCall,
        IN      int                 channelSetSize, /* The number of elements in channelSet. */
        IN      cmChannelStruct     channelSet[]
        );

RVAPI
int RVCALLCONV cmChannelSetDuplexAddress(
                       /* Sets the address of the duplex connection. */
         IN     HCHAN               hsChan,
         IN     cmTransportAddress  address,
         IN     int                 externalReferenceLength,
         IN     const RvChar*       externalReference, /* NULL if it does not exist. */
         IN     RvBool              isAssociated /* RV_TRUE if associated. */
         );

RVAPI
int RVCALLCONV /* Actual size of external reference, or negative value on failure. */
cmChannelGetDuplexAddress(
              /* Gets address of duplex connection. */
         IN     HCHAN               hsChan,
         OUT    cmTransportAddress* address, /* User-allocated structure. */
         IN     int                 externalReferenceLength, /* Size of the extRef buffer. */
         OUT    char*               externalReference, /* User-allocated buffer. */
         OUT    RvBool*               isAssociated /* RV_TRUE if associated. */
         );

RVAPI int RVCALLCONV
cmChannelSetTransportCapability(
             IN      HCHAN               hsChan,
             IN      int                 transportCapId);

RVAPI int RVCALLCONV
cmChannelGetTransportCapabilityId(
             IN      HCHAN               hsChan);

RVAPI int RVCALLCONV
cmChannelSetRedundancyEncoding(
             IN      HCHAN               hsChan,
         IN     cmRedundancyEncoding * redundancyEncoding);

RVAPI int RVCALLCONV
cmChannelGetRedundancyEncoding(
             IN      HCHAN               hsChan,
         OUT     cmRedundancyEncoding * redundancyEncoding);


RVAPI int RVCALLCONV
cmChannelSetSource(
             IN      HCHAN               hsChan,
         IN     cmTerminalLabel *terminalLabel);

RVAPI int RVCALLCONV
cmChannelGetSource(
             IN      HCHAN               hsChan,
         OUT     cmTerminalLabel *terminalLabel);


RVAPI int RVCALLCONV
cmChannelSetDestination(
         IN      HCHAN               hsChan,
         IN     cmTerminalLabel *terminalLabel);

RVAPI int RVCALLCONV
cmChannelGetDestination(
         IN      HCHAN               hsChan,
         OUT     cmTerminalLabel     *terminalLabel);


RVAPI
int RVCALLCONV cmChannelMaxSkew(
        IN      HCHAN               hsChan1,
        IN      HCHAN               hsChan2,
        IN      RvUint32            skew);


/******************************************************************************
 * cmCallGetChannelBySessionId
 * ----------------------------------------------------------------------------
 * General: Finds a channel of a call from its sessionId and direction.
 *
 * Return Value: RV_OK if successful.
 *               Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hsCall       - The call handle.
 *         sessionId    - Session ID to look for.
 *         origin       - RV_TRUE if we are the origin of the searched channel.
 *                        RV_FALSE if we are not the origin of the searched
 *                        channel.
 * Output: hsChan       - Channel that was found.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV
cmCallGetChannelBySessionId(
       IN   HCALL       hsCall,
       IN   int         sessionId,
       IN   RvBool      origin,
       OUT  HCHAN       *hsChan);



/* ----------------------- H.225 Callbacks ---------------------------- */

typedef int
    (RVCALLCONV *cmEvChannelSetAddressT)(
        IN      HAPPCHAN            haChan,
        IN      HCHAN               hsChan,
        IN      RvUint32            ip,
        IN      RvUint16            port);

typedef int
    (RVCALLCONV *cmEvChannelSetRTCPAddressT)(
        IN      HAPPCHAN            haChan,
        IN      HCHAN               hsChan,
        IN      RvUint32            ip,
        IN      RvUint16            port);

typedef int
    (RVCALLCONV *cmEvChannelRTPDynamicPayloadTypeT)(
        IN      HAPPCHAN            haChan,
        IN      HCHAN               hsChan,
        IN      RvInt8              dynamicPayloadType);

typedef int
    (RVCALLCONV *cmEvChannelGetRTCPAddressT)(
        IN      HAPPCHAN            haChan,
        IN      HCHAN               hsChan,
        IN      RvUint32*           ip,
        IN      RvUint16*           port);

typedef int
    (RVCALLCONV * cmEvChannelFlowControlToZeroT)(
         IN      HAPPCHAN             haChan,
         IN      HCHAN                hsChan);

typedef int
    (RVCALLCONV *cmEvChannelSetNSAPAddressT)(
        IN      HAPPCHAN              haChan,
        IN      HCHAN                 hsChan,
        IN      char*                 address,
        IN      int                   length,
        IN      RvBool                multicast);


typedef int
    (RVCALLCONV *cmEvChannelSetATMVCT)(
        IN      HAPPCHAN              haChan,
        IN      HCHAN                 hsChan,
        IN      int                   portNumber);






#endif /* #if (RV_H245_SUPPORT_H225_PARAMS == 1) */


/* -------------------------H.223 functions ---------------------------*/
#if (RV_H245_SUPPORT_H223_PARAMS == 1)

/******************************************************************************
 * cmH223ALLevel
 * ----------------------------------------------------------------------------
 * Definitions of the Adaptation Layer level.
 *****************************************************************************/
typedef enum
{
    cmH223ALLevelUnknown,
    cmH223ALLevel1,
    cmH223ALLevel2,
    cmH223ALLevel3,
    cmH223ALLevel1M,
    cmH223ALLevel2M,
    cmH223ALLevel3M
} cmH223ALLevel;

/******************************************************************************
 * cmH223ControlFieldSize
 * ----------------------------------------------------------------------------
 * Control field sizes that are used for retransmission in AL3.
 *****************************************************************************/
typedef enum
{
    cmH223ControlFieldSizeNone = 0,
    cmH223ControlFieldSize1Byte,
    cmH223ControlFieldSize2Bytes
}cmH223ControlFieldSize;

/* cmChannelAudioType
 * ------------------------------------------------------------------------
 * Audio types supported by the 3G-324M Toolkit.
 * Needed for generation of the multiplex entries table.
 */
typedef enum
{
    cmChannelAudioUnknown  = -1,

    /* Audio codec types by their bitrate */
    cmChannelAudioAMR_4_75    = 0,
    cmChannelAudioAMR_5_15    = 1,
    cmChannelAudioAMR_5_90    = 2,
    cmChannelAudioAMR_6_70    = 3,
    cmChannelAudioAMR_7_40    = 4,
    cmChannelAudioAMR_7_95    = 5,
    cmChannelAudioAMR_10_2    = 6,
    cmChannelAudioAMR_12_2    = 7,
    cmChannelAudioG723_53     = 8,
    cmChannelAudioG723_63     = 9,
    cmChannelAudioG7222_6_60  = 10,
    cmChannelAudioG7222_8_85  = 11,
    cmChannelAudioG7222_12_65 = 12,
    cmChannelAudioG7222_14_25 = 13,
    cmChannelAudioG7222_15_85 = 14,
    cmChannelAudioG7222_18_25 = 15,
    cmChannelAudioG7222_19_85 = 16,
    cmChannelAudioG7222_23_05 = 17,
    cmChannelAudioG7222_23_85 = 18

} cmChannelAudioType;


/* cmH223ALxMConfig
 * ------------------------------------------------------------------------
 * H.223 Annex C or Annex D related configuration parameters.
 * Some of these parameters relate only to specific adaptation layers and
 * not to all adaptation layers.
 * On each of the fields of this structure, there is an indication of the
 * adaptation layer that supports it.
 * Note that when using H.223 Annex D (i.e., codeRate field value is 128-255),
 * splitting cannot be used, crcLength can be 8,16 or 32 and arqType cannot
 * be 2.
 */
typedef struct
{
    RvBool              bIsFramed; /* AL1M. Framed or unframed mode */
    RvBool              bUseGolay; /* AL1M,AL2M,AL3M. RV_TRUE to use Golay, RV_FALSE to use SEBCH */
    RvBool              bUseInterleaving; /* AL1M,AL2M,AL3M. RV_TRUE to do interleaving */
    RvBool              bUseSplitting; /* AL1M. RV_TRUE to do splitting. Not supported by H.223 Annex D */
    RvUint8             crcLength; /* AL1M,AL3M. 0, 4, 8, 12, 16, 20, 28, 32. CRC check for frame data.
                                      CRC lengths of 4, 12, 20 and 28 fits RCPC.
                                      CRC lengths of 0, 8, 16 and 32 fits SRS. */
    RvUint8             codeRate; /* AL1M,AL3M. Code correction rate to use.
                                     8-32 for RCPC code rate (H.223 Annex C).
                                     128-255 for SRS code correction (H.223 Annex D).
                                     For SRS, 128 will be subtracted from the actual correction.
                                     For example: A value of 200 indicates 72 (200-128). */
    RvUint8             arqType; /* AL1M,AL3M. ARQ type to use.
                                    0 - FEC only.
                                    1 - ARQ type I.
                                    2 - ARQ type II. Not supported by H.223 Annex D */
    RvUint8             retransmissions; /* AL1M,AL3M. 0-16,255. Number of retransmissions.
                                            255 indicates infinite retransmissions.
                                            This field is only relevant when the arqType field is 1 or 2. */
    RvUint32            sendBufferSize; /* AL1M,AL3M. 0-16777215. Sends buffer size for retransmissions.
                                           This field is relevant only when the arqType field is 1 or 2. */
} cmH223ALxMConfig;



/******************************************************************************
 * cmChannelH223MaxSkew
 * ----------------------------------------------------------------------------
 * General: Builds and sends an h223SkewIndication message.
 *          Note that the cmEvChannelMaxSkew callback is used to notify the
 *          application that an h223SkewIndication message was received.
 *
 * Return Value: RV_OK if successful.
 *               Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hsChan1      - The first channel for which the skew is indicated.
 *         hsChan2      - The second channel for which the skew is indicated.
 *         skew         - The skew number, in milliseconds.
 * Output: none.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV
cmChannelH223MaxSkew(
         IN     HCHAN           hsChan1,
         IN     HCHAN           hsChan2,
         IN     RvUint32        skew);


/******************************************************************************
 * cmCallMultiplexEntrySend
 * ----------------------------------------------------------------------------
 * General: Sends a MultiplexEntrySend request.
 *          The message NodeId is not deleted and not modified by this function.
 *
 * Return Value: RV_OK if successful.
 *               Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hsCall  - The call handle.
 *         message - The root nodeId of the PVT tree to send.
 *                   Of the type MultiplexEntrySend.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV
cmCallMultiplexEntrySend(
               IN   HCALL       hsCall,
               IN   RvPvtNodeId message);


/******************************************************************************
 * cmCallMultiplexEntrySendResponse
 * ----------------------------------------------------------------------------
 * General: Sends multiplexEntrySend response (Ack or Reject).
 *          The message NodeId is not deleted and not modified by this function.
 *          This function can only be called if the H245 configuration
 *          states the use of a manual response for the multiplex entry table
 *          (i.e: h245.multiplexEntryTable.manualResponse is set).
 *
 * Return Value: RV_OK if successful.
 *               Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hsCall  - The call handle.
 *         isOk    - RV_TRUE if multiplexEntrySendAck is to be sent.
 *                   RV_FALSE if multiplexEntrySendReject is to be sent.
 *         message - The root nodeId of the PVT tree to send.
 *                   Should hold the MultiplexEntrySendAck.multiplexTableEntryNumber
 *                   if isOk==RV_TRUE,
 *                   or MultiplexEntrySendReject.rejectionDescriptions
 *                   if isOk==RV_FALSE.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV
cmCallMultiplexEntrySendResponse(
               IN   HCALL       hsCall,
               IN   RvBool      isOk,
               IN   RvPvtNodeId message);


#endif /* RV_H245_SUPPORT_H223_PARAMS */






/* cmChannelParam
 * ------------------------------------------------------------------------
 * Defines the parameters of the channel.
 */
typedef enum
{
    cmChannelParamUnknown  = -1,

    cmChannelParamDataTypeNodeId,            /* RvPvtNodeId: PVT Node Id of the dataType of this channel.
                                                This parameter could be set only before opening the channel. The channel
                                                opening in this case, can be done only with cmChannelOpenDynamic().*/
    cmChannelParamReverseDataTypeNodeId,     /* RvPvtNodeId: PVT Node Id of the reverse dataType of this bi - directional channel.
                                                This parameter could be set only before opening the channel. The channel
                                                opening in this case, can be done only with cmChannelOpenDynamic(). */
    cmChannelParamCapDataType,               /* cmCapDataType: The capability data type of the channel */
    cmChannelParamRejectReason,              /* cmRejectLcnReason: The reject reason of an outgoing channel. This parameter
                                                shall not be set. */
	cmChannelParamCapabilityTableEntryNumber,/* RvUint16: The capability table entry number of the capability that this channel uses. */

    /*-- H.223 related parameters - Used by 3G-324M --*/
#if (RV_H245_SUPPORT_H223_PARAMS == 1)
    cmChannelParamH223AlLevel = 1000,       /* cmH223ALLevel: Adaptation Layer */
    cmChannelParamH223Segmentable,          /* RvBool: Defines whether the logical channel is segmentable or non-segmentable.
                                               Should be set to RV_TRUE for video channels and RV_FALSE for audio channels. */
    /* AL1 parameters only */
    cmChannelParamH223Al1Framed,            /* RvBool: Defines whether the bit stream is framed or unframed. In use by AL1 channels. */
    /* AL2 parameters only */
    cmChannelParamH223Al2SequenceNumber,    /* RvBool: Defines whether to use sequence numbering. In use by AL2 channels.*/
    /* AL3 parameters only */
    cmChannelParamH223Al3ControlFieldSize,  /* cmH223ControlFieldSize: The size of MUX-SDU header. In use by AL3 channels.
                                               This value is stored in h223LogicalChannelParameters.adaptationLayerType.al3.controlFieldOctets.
                                               To be able to use AL3 with retransmissions, this parameter must be set to cmH223ControlFieldSize1Byte or cmH223ControlFieldSize2Bytes. */
    cmChannelParamH223Al3SendBufferSizeForRetransmissions,  /* RvUint32: The size of all MUX-SDU saved concurrently when using AL3 retransmissions.
                                                               This value is stored in h223LogicalChannelParameters.adaptationLayerType.al3.sendBufferSize.
                                                               To be able to use AL3 with retransmissions, this parameter must be set to a number greater than zero.*/
    /* For Audio channels only */
    cmChannelParamH223AudioType,            /* cmChannelAudioType: The audio type of the channel. This parameter should not be used
                                                                    on the receiving side of the channel. */
    /* For Video and Data channels only */
    cmChannelParamH223BitRate,              /* RvUint32: The bit rate of the channel in units of 100 bits/s. Used only for video and data channels. */
    /* For ALl Audio and Video Channels */
    cmChannelParamH223IgnoreCorruptedAlSdu, /* RvBool: Defines whether corrupted AL-SDU should be passed to the user or ignored.
                                                       Used especially for CRC errors. */
    cmChannelParamH223ReverseNullDataType,  /* RvBool: Defines if the reverse parameters data type is null. */

    cmChannelParamH223AlxMParameters,       /* cmH223ALxMConfig: AL1M/AL2M/AL3M related configuration parameters. */
    cmChannelParamH223IsMPC,                 /*RvBool: Defines if an H245Channel object is an MPC channel or not. */
#endif

#if (RV_H245_SUPPORT_H225_PARAMS == 1)
    cmChannelParamH225LocalRtpAddress = 2000,   /* cmTransportAddress: Local RTP address for the incoming channel. */
    cmChannelParamH225LocalRtcpAddress,         /* cmTransportAddress: Local RTCP address for the channel. */
    cmChannelParamH225RemoteRtpAddress,         /* cmTransportAddress: Remote RTP address for the outgoing channel. */
    cmChannelParamH225RemoteRtcpAddress,        /* cmTransportAddress: Remote RTCP address for the channel. */
    cmChannelParamH225DynamicRTPPayloadType,    /* RvUint32: The dynamic RTP payload type used for this channel, or 0 if none exists. */
    cmChannelParamH225ForceSecondary,           /* RvBool: RV_TRUE to force the Stack not to give session ID 1-3 to this channel. */
#endif

    cmChannelParamLast /* Intended to simplify compilation */
} cmChannelParam;


/******************************************************************************
 * cmChannelSetParam
 * ----------------------------------------------------------------------------
 * General: Obtains a specific channel parameter from the application.
 *          This function should be called after the call to cmChannelNew() 
 *          and before the call to cmChannelOpen().
 *          See also cmChannelParam, cmChannelGetParam.
 *
 * Return Value: RV_OK if successful.
 *               Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hsChan      - The channel handle with the parameter that will be changed.
 *         eParam      - The parameter to be changed. The parameters are defined
 *                       in the cmChannelParam enumeration.
 *         value       - If the parameter value is a simple integer value, this 
 *                       is the value itself.
 *         strValue    - If the parameter value is a string, strValue
 *                       represents the parameter value.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV
cmChannelSetParam(
         IN      HCHAN               hsChan,
         IN      cmChannelParam      eParam,
         IN      RvInt32             value,
         IN      const RvUint8       *strValue);

/******************************************************************************
 * cmChannelGetParam
 * ----------------------------------------------------------------------------
 * General: Gets a specific channel parameter for the application. 
 *          See also cmChannelParam, cmChannelSetParam.
 *
 * Return Value: RV_OK if successful.
 *               Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hsChan      - The channel handle with the parameter that has been requested.
 * Output: eParam      - The parameter requested. The list of parameters is
 *                       defined in the cmCallParam enumeration.
 *         value       - If the parameter value is a simple integer,
 *                       this is the pointer to the parameter value.
 *         strValue    - If the parameter value is a string, strValue
 *                       represents the parameter itself.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV
cmChannelGetParam(
         IN      HCHAN               hsChan,
         IN      cmChannelParam      eParam,
         OUT     RvInt32             *value,
         OUT     RvUint8             *strValue);

/******************************************************************************
 * cmChannelGetHandle
 * ----------------------------------------------------------------------------
 * General: Returns the application handle for a channel from the channel handle.
 *
 * Return Value: RV_OK if successful.
 *               Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hsChan      - The Stack handle for the channel.
 * Output: haChan      - The returned application handle of the channel.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV
cmChannelGetHandle(
                IN  HCHAN hsChan,
                OUT HAPPCHAN* haChan);


/* Callback function prototypes____________________________________________________________________________*/






/* --- Control session callback functions --- */

typedef int
    (RVCALLCONV *cmEvCallCapabilitiesT)(
        IN      HAPPCALL            haCall,
        IN      HCALL               hsCall,
        IN      cmCapStruct*        capabilities[]);

typedef int
    (RVCALLCONV *cmEvCallCapabilitiesExtT)(
        IN      HAPPCALL            haCall,
        IN      HCALL               hsCall,
        IN      cmCapStruct***      capabilities[]);

typedef int
    (RVCALLCONV *cmEvCallNewChannelT)(
        IN      HAPPCALL            haCall,
        IN      HCALL               hsCall,
        IN      HCHAN               hsChan,
        OUT     LPHAPPCHAN          lphaChan);

typedef int
    (RVCALLCONV *cmEvCallCapabilitiesResponseT)(
        IN      HAPPCALL            haCall,
        IN      HCALL               hsCall,
        IN      RvUint32            status);


/******************************************************************************
 * cmEvCallMasterSlaveExpectedStatusT
 * ----------------------------------------------------------------------------
 * General: Control event, raised when MSDDeterminationAck is sent.
 *
 * Return Value: None
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  haCall        - The call handle in the application.
 *         hsCall        - The call handle in the Stack.
 *         status        - The expected status.
 * Output: None.
 *****************************************************************************/
typedef RvStatus
    (RVCALLCONV *cmEvCallMasterSlaveExpectedStatusT)(
        IN      HAPPCALL            haCall,
        IN      HCALL               hsCall,
        IN      RvUint32            status);

typedef int
    (RVCALLCONV *cmEvCallMasterSlaveStatusT)(
        IN      HAPPCALL            haCall,
        IN      HCALL               hsCall,
        IN      RvUint32            status);

typedef int
    (RVCALLCONV *cmEvCallMultiplexEntryT)(
        IN      HAPPCALL            haCall,
        IN      HCALL               hsCall,
        IN      RvPvtNodeId         descriptors);

typedef int
    (RVCALLCONV *cmEvCallMultiplexEntryResponseT)(
        IN      HAPPCALL            haCall,
        IN      HCALL               hsCall,
        IN      RvBool              isACK,  /* If RV_TRUE = MESACK , RV_FALSE = MESReject */
        IN      RvUint16            includedEntries,
        IN      RvPvtNodeId         descriptions);



typedef int
    (RVCALLCONV *cmEvCallRoundTripDelayT)(
        IN      HAPPCALL            haCall,
        IN      HCALL               hsCall,
        IN      RvInt32             delay); /* Positive: msec delay. Negative: expiration. */

typedef int
    (RVCALLCONV *cmEvCallUserInputT)(
        IN      HAPPCALL            haCall,
        IN      HCALL               hsCall,
        IN      RvInt32             userInputId /* User input node ID. */
        );

typedef int
    (RVCALLCONV *cmEvCallRequestModeT)(
         /* Request to transmit the following mode preferences: */
        IN      HAPPCALL            haCall,
        IN      HCALL               hsCall,
        IN      cmReqModeStatus     status,
        IN      RvInt32             nodeId /* PVT nodeId handle, according to status. */
        );


typedef int
    (RVCALLCONV *cmEvCallMiscStatusT)(
        IN      HAPPCALL            haCall,
        IN      HCALL               hsCall,
        IN      cmMiscStatus        status);


typedef int
    (RVCALLCONV *cmEvCallControlStateChangedT)(
        IN      HAPPCALL            haCall,
        IN      HCALL               hsCall,
        IN      cmControlState      state,
        IN      cmControlStateMode  stateMode);


typedef int
    (RVCALLCONV *cmEvCallMasterSlaveT)(
        IN      HAPPCALL            haCall,
        IN      HCALL               hsCall,
        IN      RvUint32            terminalType,
        IN      RvUint32            statusDeterminationNumber);


/********************************************************************************************
 * cmEvCallControlMessageT
 * purpose : Notifies the application that an incoming H.245 message has been received.
 *           The messages reported by this callback are not handled by
 *           internal state machines in the Stack.
 * input   : haCall         - Application's handle for the call.
 *           hsCall         - Stack's handle for the call.
 *           message        - Node ID of the received message.
 *           messageType    - Type of message received.
 * output  : None.
 ********************************************************************************************/
typedef int
    (RVCALLCONV *cmEvCallControlMessageT)(
        IN  HAPPCALL            haCall,
        IN  HCALL               hsCall,
        IN  HAPPCHAN            haChan,
        IN  HCHAN               hsChan,
        IN  RvPvtNodeId         message,
        IN  cmH245MessageType   messageType);


/********************************************************************************************
 * cmEvCallTerminalNumberAssignT
 * purpose : Notifies the application the application that an incoming TerminalNumberAssign
 *           message has been received.
 * input   : haCall         - Application's handle for the call.
 *           hsCall         - Stack's handle for the call.
 *           mcuNumber      - New MCU number.
 *           terminalNumber - New terminal number.
 * output  : None.
 ********************************************************************************************/
typedef int
    (RVCALLCONV *cmEvCallTerminalNumberAssignT)(
        IN      HAPPCALL            haCall,
        IN      HCALL               hsCall,
        IN      RvUint8             mcuNumber,
        IN      RvUint8             terminalNumber);


/******************************************************************************
 * cmEvCallVendorIdentificationT
 * ----------------------------------------------------------------------------
 * General: 
 *         Indication to the application on an incoming VendorIdentification
 *         message.
 * 
 * Input:  haChan            - Application's handle for the call.
 *         hsChan            - Stack's handle for the call.
 *         nonStandardId     - Non-standard identifier taken from the message.
 *         productNumber     - Product number parameter taken from the message.
 *         productNumberSize - The size of the productNumber argument. If the size 
 *                             is 0, the productNumber does not exist.
 *         versionNumber     - Version number parameter taken from the message.
 *         versionNumberSize - The size of the versionNumber argument. If the size 
 *                             is 0, the versionNumber does not exist.
 * Output: None.
 *
 * Return Value: None.
 *****************************************************************************/
typedef int
    (RVCALLCONV *cmEvCallVendorIdentificationT)(
        IN      HAPPCALL                 haCall,
        IN      HCALL                    hsCall,
        IN      cmNonStandardIdentifier  *nonStandardId,
        IN      RvUint8                  *productNumber,
        IN      RvUint16                 productNumberSize,
        IN      RvUint8                  *versionNumber,
        IN      RvUint16                 versionNumberSize);


typedef  struct
{
    cmEvCallCapabilitiesT               cmEvCallCapabilities;
    cmEvCallCapabilitiesExtT            cmEvCallCapabilitiesExt;
    cmEvCallNewChannelT                 cmEvCallNewChannel;
    cmEvCallCapabilitiesResponseT       cmEvCallCapabilitiesResponse;
    cmEvCallMasterSlaveStatusT          cmEvCallMasterSlaveStatus;
    cmEvCallMasterSlaveExpectedStatusT  cmEvCallMasterSlaveExpectedStatus;
    cmEvCallRoundTripDelayT             cmEvCallRoundTripDelay;
    cmEvCallUserInputT                  cmEvCallUserInput;
    cmEvCallRequestModeT                cmEvCallRequestMode;
    cmEvCallMiscStatusT                 cmEvCallMiscStatus;
    cmEvCallControlStateChangedT        cmEvCallControlStateChanged;
    cmEvCallMasterSlaveT                cmEvCallMasterSlave;
    cmEvCallControlMessageT             cmEvCallControlMessage;
    cmEvCallMultiplexEntryResponseT     cmEvCallMultiplexEntryResponse;
    cmEvCallMultiplexEntryT             cmEvCallMultiplexEntry;
    cmEvCallTerminalNumberAssignT       cmEvCallTerminalNumberAssign;
    cmEvCallVendorIdentificationT       cmEvCallVendorIdentification;
} SCMCONTROLEVENT,*CMCONTROLEVENT;

typedef SCMCONTROLEVENT SCMSESSIONEVENT; /* for backward compatibility */
typedef CMCONTROLEVENT CMSESSIONEVENT;




/* --- Control channels callback functions --- */


typedef int
    (RVCALLCONV *cmEvChannelStateChangedT)(
        IN      HAPPCHAN                haChan,
        IN      HCHAN                   hsChan,
        IN      cmChannelState_e        state,
        IN      cmChannelStateMode_e    stateMode);

typedef int
    (RVCALLCONV *cmEvChannelNewRateT)(
        IN      HAPPCHAN            haChan,
        IN      HCHAN               hsChan,
        IN      RvUint32            rate);

typedef int
    (RVCALLCONV *cmEvChannelMaxSkewT)(
        IN      HAPPCHAN            haChan1,
        IN      HCHAN               hsChan1,
        IN      HAPPCHAN            haChan2,
        IN      HCHAN               hsChan2,
        IN      RvUint32            skew);

typedef int
    (RVCALLCONV *cmEvChannelParametersT)(
        IN      HAPPCHAN            haChan,
        IN      HCHAN               hsChan,
        IN      char*               channelName,
        IN      HAPPCHAN            haChanSameSession,
        IN      HCHAN               hsChanSameSession,
        IN      HAPPCHAN            haChanAssociated,
        IN      HCHAN               hsChanAssociated,
        IN      RvUint32            rate);


typedef int
    (RVCALLCONV *cmEvChannelVideoFastUpdatePictureT)(
        IN      HAPPCHAN            haChan,
        IN      HCHAN               hsChan);

typedef int
    (RVCALLCONV *cmEvChannelVideoFastUpdateGOBT)(
        IN      HAPPCHAN            haChan,
        IN      HCHAN               hsChan,
        IN      int                 firstGOB,
        IN      int                 numberOfGOBs);

typedef int
    (RVCALLCONV *cmEvChannelVideoFastUpdateMBT)(
        IN      HAPPCHAN            haChan,
        IN      HCHAN               hsChan,
        IN      int                 firstGOB,
        IN      int                 firstMB,
        IN      int                 numberOfMBs);

typedef int
    (RVCALLCONV *cmEvChannelHandleT)(
          /* Provides data type tree handle for this channel */
        IN      HAPPCHAN            haChan,
        IN      HCHAN               hsChan,
        IN      int                 dataTypeHandle,
        IN      cmCapDataType       dataType);


typedef int
    (RVCALLCONV *cmEvChannelRequestCloseStatusT)(
        IN      HAPPCHAN              haChan,
        IN      HCHAN                 hsChan,
        IN      cmRequestCloseStatus  status);

typedef int
    (RVCALLCONV *cmEvChannelTSTOT)(
        IN      HAPPCHAN              haChan,
        IN      HCHAN                 hsChan,
        IN      RvInt8                isCommand, /* 0: Indication. 1: Command */
        IN      RvInt8                tradeoffValue); /* 0-31 tradeoff value */

typedef int
    (RVCALLCONV *cmEvChannelMediaLoopStatusT)(
        IN      HAPPCHAN              haChan,
        IN      HCHAN                 hsChan,
        IN      cmMediaLoopStatus     status);



typedef int
    (RVCALLCONV * cmEvChannelReplaceT)(
         IN     HAPPCHAN              haChan,
         IN     HCHAN                 hsChan,
         IN     HAPPCHAN              haReplacedChannel,
         IN     HCHAN                 hsReplacedChannel);



typedef int
    (RVCALLCONV * cmEvChannelMiscCommandT)(
         IN      HAPPCHAN             haChan,
         IN      HCHAN                hsChan,
         IN      cmMiscellaneousCommand miscCommand);

typedef int
    (RVCALLCONV * cmEvChannelTransportCapIndT)(
         IN      HAPPCHAN             haChan,
         IN      HCHAN                hsChan,
         IN      int                  nodeId);


/******************************************************************************
 * cmEvChannelRecvMessageT
 * ----------------------------------------------------------------------------
 * General: Notification function for the application that an incoming H.245
 *          message related to a specific channel was received by the Stack and
 *          is about to be processed.
 * Remarks: This callback will be invoked after the callback indicating a new
 *          message for a call is invoked (cmEvCallRecvMessage in H.323 or
 *          Rv3G324mCallReceiveMessageEv in 3G-324M).
 *          This callback will not be invoked for Fast start messages in H.323.
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  haChan   - Application's handle for the channel.
 *         hsChan   - Stack's handle for the channel.
 *         message  - PVT node ID of the message that was received.
 * Output: None.
 *****************************************************************************/
typedef int
    (RVCALLCONV*cmEvChannelRecvMessageT)(
        IN      HAPPCHAN            haChan,
        IN      HCHAN               hsChan,
        IN      RvPvtNodeId         message);


/******************************************************************************
 * cmEvChannelSendMessageT
 * ----------------------------------------------------------------------------
 * General: Notification function for the application that an outgoing H.245
 *          message related to a specific channel is about to be sent by the
 *          Stack.
 * Remarks: This callback will be invoked before the callback indicating the
 *          sending of a message for a call is invoked (cmEvCallSendMessage in
 *          H.323, or Rv3G324mCallSendMessageEv in 3G-324M).
 *          This callback will not be invoked for Fast Start messages in H.323.
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  haChan   - Application's handle for the channel.
 *         hsChan   - Stack's handle for the channel.
 *         message  - PVT node ID of the message that is about to be sent.
 * Output: None.
 *****************************************************************************/
typedef int
    (RVCALLCONV*cmEvChannelSendMessageT)(
        IN      HAPPCHAN            haChan,
        IN      HCHAN               hsChan,
        IN      RvPvtNodeId         message);


/******************************************************************************
 * cmEvChannelMasterSlaveConflictT
 * ----------------------------------------------------------------------------
 * General: Notification function for the application that an incoming OLC
 *          conflicts with an offered OLC. The application should decide
 *          what to do with it.
 *
 * Return Value: For H.323:
 *               positive - The SID to use.
 *               zero - Use any SID.
 *               negative - Reject with reason masterSlaveConflict.
 *
 *               For 3G-324M:
 *               positive or zero - Continue as though there were no conflict.
 *               negative - Act according to the conflict type.
 * ----------------------------------------------------------------------------
 * Input:  haChan       - Application's handle for the channel.
 *         hsChan       - Stack's handle for the channel.
 *         conflictType - Type of conflict.
 *         confChans    - Array of handles of conflicting channels.
 *         numConfChans - Number of channels in the array.
 *         message      - PVT node ID of the incoming OLC.
 * Output: None.
 *****************************************************************************/
typedef int
    (RVCALLCONV *cmEvChannelMasterSlaveConflictT)(
        IN      HAPPCHAN                    haChan,
        IN      HCHAN                       hsChan,
        IN      cmH245ChannelConflictType   conflictType,
        IN      HCHAN                      *confChans,
        IN      int                         numConfChans,
        IN      RvPvtNodeId                 message);


/******************************************************************************
 * cmEvChannelSetRoleT
 * ----------------------------------------------------------------------------
 * General: A request from the application to set the role of a video channel
 *          (video or video2).
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Input:  haChan       - Application's handle for the channel.
 *         hsChan       - Stack's handle for the channel.
 *         dataType     - PVT node ID of the dataType field in the OLC.
 * Output: channelRole  - Role of the channel (0 for video and 1 for video2).
 *****************************************************************************/
typedef void
    (RVCALLCONV *cmEvChannelSetRoleT)(
        IN      HAPPCHAN                    haChan,
        IN      HCHAN                       hsChan,
        IN      RvPvtNodeId                 dataType,
        OUT     RvUint16*                   channelRole);


typedef struct
{
    cmEvChannelStateChangedT            cmEvChannelStateChanged;
    cmEvChannelNewRateT                 cmEvChannelNewRate;
    cmEvChannelMaxSkewT                 cmEvChannelMaxSkew;

#if (RV_H245_SUPPORT_H225_PARAMS == 1)
    cmEvChannelSetAddressT              cmEvChannelSetAddress;
    cmEvChannelSetRTCPAddressT          cmEvChannelSetRTCPAddress;
#endif /* #if (RV_H245_SUPPORT_H225_PARAMS == 1) */

    cmEvChannelParametersT              cmEvChannelParameters;

#if (RV_H245_SUPPORT_H225_PARAMS == 1)
    cmEvChannelRTPDynamicPayloadTypeT   cmEvChannelRTPDynamicPayloadType;
#endif /* #if (RV_H245_SUPPORT_H225_PARAMS == 1) */

    cmEvChannelVideoFastUpdatePictureT  cmEvChannelVideoFastUpdatePicture;
    cmEvChannelVideoFastUpdateGOBT      cmEvChannelVideoFastUpdateGOB;
    cmEvChannelVideoFastUpdateMBT       cmEvChannelVideoFastUpdateMB;
    cmEvChannelHandleT                  cmEvChannelHandle;

#if (RV_H245_SUPPORT_H225_PARAMS == 1)
    cmEvChannelGetRTCPAddressT          cmEvChannelGetRTCPAddress;
#endif /* #if (RV_H245_SUPPORT_H225_PARAMS == 1) */

    cmEvChannelRequestCloseStatusT      cmEvChannelRequestCloseStatus;
    cmEvChannelTSTOT                    cmEvChannelTSTO;
    cmEvChannelMediaLoopStatusT         cmEvChannelMediaLoopStatus;
    cmEvChannelReplaceT                 cmEvChannelReplace;

#if (RV_H245_SUPPORT_H225_PARAMS == 1)
    cmEvChannelFlowControlToZeroT       cmEvChannelFlowControlToZero;
#endif /* #if (RV_H245_SUPPORT_H225_PARAMS == 1) */

    cmEvChannelTransportCapIndT         cmEvChannelTransportCapInd;
    cmEvChannelMiscCommandT             cmEvChannelMiscCommand;

#if (RV_H245_SUPPORT_H225_PARAMS == 1)
    cmEvChannelSetNSAPAddressT          cmEvChannelSetNSAPAddress;
    cmEvChannelSetATMVCT                cmEvChannelSetATMVC;
#endif /* #if (RV_H245_SUPPORT_H225_PARAMS == 1) */

    cmEvChannelRecvMessageT             cmEvChannelRecvMessage;
    cmEvChannelSendMessageT             cmEvChannelSendMessage;
    cmEvChannelMasterSlaveConflictT     cmEvChannelMasterSlaveConflict;
#if (RV_H245_SUPPORT_H223_PARAMS == 1)
    cmEvChannelSetRoleT                 cmEvChannelSetRole;
#endif

} SCMCHANEVENT,*CMCHANEVENT;







/* General_______________________________________________________________________________________________*/






RVAPI int RVCALLCONV /* The real number of channels in the configuration, or a negative value on failure. */
cmGetConfigChannels(
            /* Builds array containing the channel names as they appear in
               the configuration. The strings are copied into array elements. */
            IN  HAPP        hApp,
            IN  int         arraySize,
            IN  int         elementLength, /* sizeof each string in the array */
            OUT char*       array[] /* allocated with elements */
            );


/******************************************************************************
 * cmGetConfigChannelDataType
 * ----------------------------------------------------------------------------
 * General: Gets the DataType PVT sub-tree of a specified channel that is
 *          defined in the configuration.
 *
 * Return Value: Non-negative if successful.
 *               Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hApp             - The handle to the Stack.
 *         channelName      - The channel name from configuration.
 * Output: dataTypeNodeId   - The DataType node ID of the channel.
 *****************************************************************************/
RVAPI int RVCALLCONV
cmGetConfigChannelDataType(
             IN    HAPP            hApp,
             IN    const RvChar    *channelName,
             OUT   RvPvtNodeId     *dataTypeNodeId);


/************************************************************************
 * cmBuildH245DataTypeNode
 * purpose: Builds an H.245 dataType node according to the given data type name.
 * input  : hApp            - Stack handle for the application.
 *          dataType        - Channel type name.
 *          nonH235         - If True, remove h235Media.mediaType level.
 * output : dataTypeNode    - The dataType node supplied to the application.
 *                            The application is responsible for deleting this
 *                            node.
 * return : RV_OK on success, other on failure.
 ************************************************************************/
RVAPI RvStatus RVCALLCONV cmBuildH245DataTypeNode(
    IN  HAPP            hApp,
    IN  const RvChar    *dataType,
    IN  RvBool          nonH235,
    OUT RvPvtNodeId     *dataTypeNode);


/************************************************************************
 * cmSetControlEventHandler
 * purpose: Used only for backward compatibility. Also known as cmSetSessionEventHandler.
 *          Installs the control event handler.
 * input  : hApp            - Stack handle for the application.
 *          cmControlEvent  - Pointer to the array of pointers to the general event callback functions.
 *          size            - Size of *cmControlEvent in bytes.
 * output : None.
 * return : Non-negative value on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI
int RVCALLCONV cmSetControlEventHandler(
        IN      HAPP                hApp,
        IN      CMCONTROLEVENT      cmControlEvent,
        IN      int                 size);

RVAPI
int RVCALLCONV cmGetControlEventHandler(
        IN      HAPP                hApp,
        OUT     CMCONTROLEVENT      cmControlEvent,
        IN      int                 size);

#define cmSetSessionEventHandler cmSetControlEventHandler /* for backward compatability */


/************************************************************************
 * cmSetChannelEventHandler
 * purpose: Installs the channel event handler.
 * input  : hApp            - Stack handle for the application.
 *          cmChannelEvent  - Pointer to the array of pointers to the general event callback functions.
 *          size            - Size of *cmChannelEvent, in bytes.
 * output : None.
 * return : Non-negative value on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI
int RVCALLCONV cmSetChannelEventHandler(
        IN      HAPP                hApp,
        IN      CMCHANEVENT         cmChannelEvent,
        IN      int                 size);


RVAPI
int RVCALLCONV cmGetChannelEventHandler(
        IN      HAPP                hApp,
        OUT      CMCHANEVENT         cmChannelEvent,
        IN      int                 size);



/* Returns the value tree node ID of the H.245 configuration root node. */
RVAPI
RvInt32 RVCALLCONV cmGetH245ConfigurationHandle(
                IN  HAPP             hApp);


/* Control Session API_______________________________________________________________________________*/



#if (RV_H245_SUPPORT_H225_PARAMS == 1)

RVAPI
int RVCALLCONV cmCallCreateControlSession(
        IN   HCALL           hsCall,
        IN OUT   cmTransportAddress* addr);



RVAPI int RVCALLCONV
cmCallCloseControlSession(
              /* Close the H.245 PDL protocol tree */
              IN     HCALL               hsCall);


RVAPI int RVCALLCONV
cmCallHasControlSession(
              /* Checks if Transport has connected a control session for the call.
                 The control session may be tunneled. */
              IN     HCALL               hsCall);

#endif /* #if (RV_H245_SUPPORT_H225_PARAMS == 1) */

/* --- Master/Slave --- */


RVAPI
int RVCALLCONV cmCallMasterSlaveDetermine(
                    /* Starts the Master/Slave determination request. */
                    IN  HCALL       hsCall,
                    IN  int         terminalType
                    );
#define cmMasterSlaveDetermine cmCallMasterSlaveDetermine


RVAPI int RVCALLCONV /* Master/Slave status of this call. */
cmCallMasterSlaveStatus(
            IN  HCALL       hsCall
            );

/******************************************************************************
 * cmCallMasterSlaveExpectedStatus
 * ----------------------------------------------------------------------------
 * General: Returns the MSD status as it is known to the Stack, even before the MSD 
 *          process has been completed.
 *
 * Return Value: RV_OK on success. Negative value on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hsCall            - Call handle in the Stack.
 * Output: None.
 ******************************************************************************/
RVAPI int RVCALLCONV
cmCallMasterSlaveExpectedStatus(
            IN  HCALL       hsCall
            );


RVAPI int RVCALLCONV
cmCallMasterSlaveDetermineExt(
               /*  Starts Master/Slave determination request.
          Acknowledges Master/Slave determination request.
          Sets terminalType and determinationNumber.
          */
               IN   HCALL       hsCall,
               IN   int         terminalType,
               IN   int         determinationNumber);






/* --- Capabilities --- */

RVAPI int RVCALLCONV /* Remote terminal capability sets node ID, or negative value on failure. */
cmCallGetRemoteCapabilities(
                /* Gets the latest remote terminal capability message. */
                IN  HCALL       hsCall
                );


RVAPI int RVCALLCONV /* RV_TRUE, or a negative value on failure. */
cmCallSendCapability(
             /* Sends the terminal capability set tree to the remote terminal. */
             /* Note: Capability tree is not deleted! */
             IN  HCALL hsCall,
             IN  int termCapSet  /* Local terminal capabiliy set ID */
             );


RVAPI int RVCALLCONV /* New terminalCapabilitySet node ID. */
cmCallCapabilitiesBuild(
            /* Builds the terminalCapabilitySet value tree, including the capability set
               and capability descriptors. */
            IN  HCALL           hsCall,
            IN      cmCapStruct*        capSet[],
            IN      cmCapStruct***      capDesc[]
            );

RVAPI int RVCALLCONV
cmCallCapabilitiesSend(
               IN      HCALL               hsCall,
               IN      cmCapStruct*        capSet[],
               IN      cmCapStruct***      capDesc[]
               );

/******************************************************************************
 * cmCallGetLocalCapabilities
 * ----------------------------------------------------------------------------
 * General: Gets the local capabilities that are part of the outgoing
 *          TerminalCapabilitySet message.
 *          Note that if the TCS message has already been sent, the
 *          capabilities of the message will be processed. Otherwise the
 *          capabilities set in the configuration will be processed.
 *          An example of usage:
 *
 *          cmCapStruct     capA[capSetASize];
 *          cmCapStruct     *capSetA[capSetASize];
 *          void            *capDescA[capDescASize];
 *          cmCapStruct     **capSet;
 *          cmCapStruct     ****capDesc;
 *          int             i;
 *
 *          for (i=0; i<capSetASize; i++) capSetA[i] = capA+i;
 *          cmCallGetLocalCapabilities(hsCall,
 *          capSetA, capSetASize,
 *          capDescA, capDescASize,
 *          &capSet, &capDesc);
 *
 * Return Value: If successful, the node ID of the outgoing
 *               TCS message/capabilities set in the configuration.
 *               Negative number on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hsCall       - The handle of the call.
 *         capSetA      - An array that is used to build the capability set
 *                        taken from the capabilityTable field in TCS message.
 *                        This array is allocated by the user.
 *         capSetASize  - Number of elements allocated in capSetA array.
 *         capDescA     - An array that will be used to build the capability
 *                        descriptors taken from the capabilityDescriptors field
 *                        in the TCS message.
 *                        This array is allocated by the user.
 *         capDescASize - Number of elements allocated in capDescA array.
 * Output: capSet       - A pointer to the capability set array that was given
 *                        as capSetA parameter.
 *         capDesc      - Pointer to the capability descriptors array that
 *                        was given as capDescA parameter. The array is sorted
 *                        in ascending order according to
 *                        capabilityDescriptorNumbers.
 *                        This array is a four-dimensional array that organizes
 *                        the capability descriptors in four hierarchical levels:
 *                        CapabilityDescriptor -> simultaneousCapabilities ->
 *                        AlternativeCapabilitySet -> CapabilityTableEntry.
 *****************************************************************************/
RVAPI int RVCALLCONV
cmCallGetLocalCapabilities(
               IN      HCALL                hsCall,
               IN      cmCapStruct*         capSetA[],
               IN      int                  capSetASize,
               IN      void*                capDescA[],
               IN      int                  capDescASize,
               OUT     cmCapStruct**        capSet[],
               OUT     cmCapStruct****      capDesc[]);


/******************************************************************************
 * cmCallGetRemoteCapabilitiesEx
 * ----------------------------------------------------------------------------
 * General: Gets the remote capabilities that are part of the incoming
 *          TerminalCapabilitySet message.
 *          Note that this function should be called after at least one TCS
 *          message has been received. Otherwise, it fails.
 *          For example:
 *
 *          cmCapStruct     capA[capSetASize];
 *          cmCapStruct     *capSetA[capSetASize];
 *          void            * capDescA[capDescASize];
 *          cmCapStruct     **capSet;
 *          cmCapStruct     ****capDesc;
 *          int             i;
 *
 *          for (i=0; i<capSetASize; i++) capSetA[i] = capA+i;
 *          cmCallGetRemoteCapabilitiesEx(hsCall,
 *          capSetA, capSetASize,
 *          capDescA, capDescASize,
 *          &capSet, &capDesc);
 *
 * Return Value: If successful, the node ID of the incoming TCS.
 *               Negative number on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hsCall       - The handle of the call.
 *         capSetA      - An array that will be used to build the capability set
 *                        taken from the capabilityTable field in the TCS message.
 *                        This array is allocated by the user.
 *         capSetASize  - Number of elements allocated in capSetA array.
 *         capDescA     - An array that will be used to build the capability
 *                        descriptors taken from the capabilityDescriptors field
 *                        in the TCS message.
 *                        This array is allocated by the user.
 *         capDescASize - Number of elements allocated in the capDescA array.
 * Output: capSet       - A pointer to the capability set array that was given
 *                        as capSetA parameter. If an empty TCS message has arrived
 *                        just before calling this function, the first element
 *                        of this array will be set to NULL.
 *         capDesc      - A pointer to the capability descriptors array which
 *                        was given as capDescA parameter. The array is sorted
 *                        in ascending order according to
 *                        capabilityDescriptorNumbers.
 *                        This array is a four-dimensional array that organizes
 *                        the capability descriptors in four hierarchial levels:
 *                        CapabilityDescriptor -> simultaneousCapabilities ->
 *                        AlternativeCapabilitySet -> CapabilityTableEntry.
 *                        If an empty TCS message has arrived just before calling
 *                        this function, the first element of this array will be
 *                        set to NULL.
 *****************************************************************************/
RVAPI int RVCALLCONV
cmCallGetRemoteCapabilitiesEx(
               IN      HCALL                hsCall,
               IN      cmCapStruct*         capSetA[],
               IN      int                  capSetASize,
               IN      void*                capDescA[],
               IN      int                  capDescASize,
               OUT     cmCapStruct**        capSet[],
               OUT     cmCapStruct****      capDesc[]);


/******************************************************************************
 * cmCallCapabilitiesAck
 * ----------------------------------------------------------------------------
 * General: Replies manually with an acknowledgement to a
 *          terminalCapabilitySet request.
 *
 * Return Value: Non-negative value on success, negative value on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hsCall           - The Stack handle for the call.
 *****************************************************************************/
RVAPI int RVCALLCONV
cmCallCapabilitiesAck(
               IN HCALL             hsCall);


/******************************************************************************
 * cmCallCapabilitiesReject
 * ----------------------------------------------------------------------------
 * General: Replies manually with a rejection to a
 *          terminalCapabilitySet request.
 *
 * Return Value: RV_OK on success, negative value on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hsCall           - The Stack handle for the call.
 *         cause            - Rejection cause for this message.
 *         highestEntry     - The highest number entry that was processed from
 *                            the incoming terminalCapabilitySet message.
 *                            This parameter is only valid if cause is set to
 *                            cmCapRejectCauseTableEntryExceeded.
 *                            A value of 0 indicates that none of the entries
 *                            were processed.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV
cmCallCapabilitiesReject(
               IN HCALL             hsCall,
               IN cmCapRejectCause  cause,
               IN RvInt             highestEntry);



/* --- alive --- */

RVAPI
int RVCALLCONV cmCallRoundTripDelay(
                  /* Measures the round trip delay to the remote terminal */
                  /* Note: maxDelay=0 --> Delay taken from configuration */
                  IN    HCALL       hsCall,
                  IN    RvInt32         maxDelay /* Maximum waiting delay, in seconds */
                  );



/* --- User input --- */


RVAPI int RVCALLCONV
cmCallSendUserInput(
            /* Sends user input mmessage: userInputId tree is deleted */
            /* Note: Select one of the nonStandard or userData options */
            IN  HCALL hsCall,
            IN  RvInt32 userInputId /* indication.userInput tree node ID */
            );

RVAPI int RVCALLCONV  /* userInput message node ID or negative value on failure */
cmUserInputBuildNonStandard(
                /* Builds userUser message with non-standard data */
                IN  HAPP hApp,
                IN  cmNonStandardIdentifier *identifier,
                IN  const RvChar *data,
                IN  int dataLength /* in bytes */
                );

RVAPI int RVCALLCONV  /* userInput message node ID or negative value on failure */
cmUserInputBuildAlphanumeric(
                 /* Builds userUser message with alphanumeric data */
                 IN  HAPP hApp,
                 IN  cmUserInputData *userData
                 );


/******************************************************************************
 * cmUserInputGet
 * ----------------------------------------------------------------------------
 * General: Creates a string of user data from data stored in a sub-tree.
 *          The data can be standard or non-standard.
 *
 * Return Value: If an error occurs, the function returns a negative value.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hApp         - The Stack handle for the application.
 *         userInputId  - The PVT node ID of the userInputIndicator sub-tree
 *                        that contains the user data.
 *         identifier   - The vendor and type of the non-standard information.
 *         dataLength   - The length of the data buffer, in bytes.
 * Output: data         - Pointer to the data buffer for non-standard data.
 *         dataLength   - 0 for standard data, or the length of buffer for
 *                        non-standard data.
 *         userData     - Pointer to cmUserInputData.
 *****************************************************************************/
RVAPI int RVCALLCONV
cmUserInputGet(
    IN    HAPP                      hApp,
    IN    RvPvtNodeId               userInputId,
    IN    cmNonStandardIdentifier   *identifier,
    OUT   RvChar                    *data,
    INOUT RvInt32                   *dataLength,
    OUT   cmUserInputData           *userData);


/* --- Request mode --- */

RVAPI int RVCALLCONV
cmCallRequestMode(
          /* Sends a request mode message */
          /* Note: The ID is deleted when the function returns */
          IN  HCALL hsCall,
          IN  RvInt32 modeDescriptorsId /* (requestMode.requestedModes) */
          );

RVAPI int RVCALLCONV
cmCallRequestModeAck(
             /* Acknowledges the request */
             IN  HCALL hsCall,
             IN  const RvChar* responseName /* (requestModeAck.response) */
             );

RVAPI int RVCALLCONV
cmCallRequestModeReject(
            /* Rejects the request */
            IN  HCALL hsCall,
            IN  const RvChar* causeName /* requestModeReject.cause */
            );



RVAPI int RVCALLCONV/* Request mode node ID, or negative value on failure */
cmRequestModeBuild(
           /* Builds request mode message */
           /* Note: entryId overrides name */
           IN  HAPP hApp,
           IN  cmReqModeEntry **modes[] /* Modes matrix in preference order. NULL-terminated arrays */
           );

RVAPI int RVCALLCONV/* RV_TRUE, or negative value on failure */
cmRequestModeStructBuild(
             /* Builds request mode matrix structure from message */
             /* Note: Entry name, as in H.245 standard */
             IN  HAPP hApp,
             IN  RvInt32 descId, /* requestMode.requestedModes node ID */
             IN  cmReqModeEntry **entries, /* User-allocated entries */
             IN  int entriesSize, /* Number of entries */
             IN  void **ptrs, /* Pool of pointers to construct modes */
             IN  int ptrsSize, /* Number of pointers */

             /* Modes matrix in preference order. NULL terminated arrays */
             OUT cmReqModeEntry ***modes[]
             );




/* Channels____________________________________________________________________________________*/





RVAPI int RVCALLCONV
cmChannelGetCallHandles(
            /* Gets the Stack and application call handles by the channel handle */
            IN  HCHAN hsChan,
            OUT HCALL *hsCall,
            OUT HAPPCALL *haCall
            );




RVAPI int RVCALLCONV
cmChannelNew(
         IN      HCALL               hsCall,
         IN      HAPPCHAN            haChan,
         OUT     LPHCHAN             lphsChan);

RVAPI int RVCALLCONV
cmChannelSetHandle(
           /* Makes haChan the new application handle of this channel */
           IN HCHAN                    hsChan,
           IN HAPPCHAN                 haChan);



/************************************************************************
 * cmChannelOpen
 * purpose: Opens a new logical channel using the definitions in the
 *          Stack configuration.
 * input  : hsChan              - Channel to open.
 *          channelName         - Name of the Stack configuration settings
 *                                entry for the channel to be opened.
 *          hsChanSameSession   - Stack handle for the channel that belongs to
 *                                the same session (may be NULL).
 *          hsChanAssociated    - Stack handle of outgoing channel that is
 *                                to be associated with the newly created one
 *                                (may be NULL).
 *                              - Unused. Reserved for backward compatability rate.
 * output : None.
 * return : Non-negative value on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI
int RVCALLCONV cmChannelOpen(
        IN      HCHAN               hsChan,
        IN      const RvChar*       channelName,
        IN      HCHAN               hsChanSameSession,
        IN      HCHAN               hsChanAssociated,
        IN      RvUint32            rate);

RVAPI
int RVCALLCONV cmChannelOpenDynamic(
        IN      HCHAN               hsChan,
        IN      int                 dataTypeHandle, /* Data type (HPVT) tree handle */
        IN      HCHAN               hsChanSameSession,
        IN      HCHAN               hsChanAssociated,
        IN      RvBool              isDynamicPaloadType);


RVAPI
int RVCALLCONV cmChannelOn(
        IN      HCHAN               hsChan);

RVAPI
int RVCALLCONV cmChannelOff(
        IN      HCHAN               hsChan);

RVAPI
int RVCALLCONV cmChannelAnswer(
        IN      HCHAN               hsChan);

RVAPI
int RVCALLCONV cmChannelDrop(
        IN      HCHAN               hsChan);

RVAPI
int RVCALLCONV cmChannelClose(
         IN     HCHAN               hsChan);


RVAPI int RVCALLCONV
cmChannelRequestCloseReject(
                /* Rejects the request for closing the outgoing channel. */
                IN  HCHAN       hsChan
                );


/* --- Duplex channels --- */
RVAPI
int RVCALLCONV cmChannelDuplex(
                 /* Declares the channel (full) duplex. Composed of
                two uni-directional channels in opposite directions. */
        IN      HCHAN               hsChan);

RVAPI
int RVCALLCONV cmChannelIsDuplex(
                   /* Returns RV_TRUE if the channel is duplex. RV_FALSE if the channel is not duplex. 
                  A negative value on error. */
         IN     HCHAN               hsChan);







/* Channel commands_____________________________________________________________________________________*/





RVAPI
int RVCALLCONV cmChannelFlowControl(
        IN      HCHAN               hsChan,
        IN      RvUint32            rate);


RVAPI
int RVCALLCONV cmChannelGetOrigin(
        IN      HCHAN               hsChan,
        OUT     RvBool*             origin);


RVAPI
int RVCALLCONV cmChannelVideoFastUpdatePicture(
        IN      HCHAN               hsChan);

RVAPI
int RVCALLCONV cmChannelVideoFastUpdateGOB(
        IN      HCHAN               hsChan,
        IN      int                 firstGOB,
        IN      int                 numberOfGOBs);

RVAPI
int RVCALLCONV cmChannelVideoFastUpdateMB(
        IN      HCHAN               hsChan,
        IN      int                 firstGOB,
        IN      int                 firstMB,
        IN      int                 numberOfMBs);



RVAPI int RVCALLCONV
cmChannelTSTOCommand(
             /* Sends temporal spatial tradeoff command. Requests the remote terminal to change
              the tradeoff. */
             IN HCHAN hsChan, /* Incoming channel */
             IN int tradeoffValue /* 0-31 */
             );

RVAPI int RVCALLCONV
cmChannelTSTOIndication(
             /* Sends temporal spatial tradeoff indication. Indicates the current tradeoff value
              of the local terminal. */
             IN HCHAN hsChan, /* Outgoing channel */
             IN int tradeoffValue /* 0-31 */
             );



/* Media loop____________________________________________________________________________*/

RVAPI int RVCALLCONV
cmChannelMediaLoopRequest(
              /* Requests media loop on this channel */
              IN HCHAN hsChan /* outgoing channel */
              );

RVAPI int RVCALLCONV
cmChannelMediaLoopConfirm(
              /* Confirms media loop request on this channel */
              IN HCHAN hsChan /* Incoming channel */
              );

RVAPI int RVCALLCONV
cmChannelMediaLoopReject(
             /* Rejects media loop request on this channel */
             IN HCHAN hsChan /* Incoming channel */
             );

RVAPI int RVCALLCONV
cmCallMediaLoopOff(
           /* Releases all media loops in this call */
           IN HCALL hsCall
           );




/* Replaces an existing channel with a new one. */
RVAPI int RVCALLCONV
cmChannelReplace(
                     IN      HCHAN          hsChan, /* Opens outgoing channel that is supposed to replace the existing channel */
                     IN      HCHAN          hsChanReplace);/* The existing outgoing channel to be replaced */



/******************************************************************************
 * cmIsChannelReplace
 * ----------------------------------------------------------------------------
 * General: Checks if the given channel (hsChan) replaces an existing channel
 *          and, if so, looks for that channel.
 *
 * Return Value: If an error occurs, the function returns a negative value.
 *               1 - Channel replaces an existing channel.
 *               0 - Channel does not replace an existing channel.
 * See Also:
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hsChan           - The Stack handle for the channel.
 *         haReplaceChannel - The application handle for the replaced channel.
 *         hsReplaceChannel - The Stack handle for the replaced channel.
 *****************************************************************************/
RVAPI int RVCALLCONV
cmIsChannelReplace(
             IN     HCHAN           hsChan,
             OUT    HAPPCHAN*       haReplaceChannel,
             OUT    HCHAN*          hsReplaceChannel
             );


/* Sets outgoing channel hsChan to be dependent on base channel with handle hsChanBase */
RVAPI int RVCALLCONV
cmChannelSetDependency(
             IN      HCHAN               hsChan,
             IN      HCHAN               hsChanBase);


/* Checks if the channel is dependent on another channel.
Returns RV_TRUE if it is, and returns handles of base channel
in haBaseChannel and hsBaseChannel.
*/
RVAPI int RVCALLCONV
cmChannelGetDependency(
                     IN     HCHAN           hsChan,
                     OUT    HAPPCHAN*       haBaseChannel,
                     OUT    HCHAN*          hsBaseChannel);






/* -------------------- Close logical channels ----------------- */

RVAPI int RVCALLCONV
cmChannelDropReason(
          /*
        - Closes outgoing channel.
        - Rejects incoming channel open request.
        - New: Requests to close incoming channel.
        - On the other side, the close lcn reason is passed via rejectStateMode to the
          cmEvChannelStateChanged callback function.
          */
            IN  HCHAN       hsChan,
            IN  cmCloseLcnReason reason
          );

/************************************************************************
 * cmChannelRejectReason
 * purpose: Rejects incoming OpenLogicaChannel request.
 * input  : hsChan      - Channel to check.
 *          reason      - Channel reject reason.
 * return : Non-negative value on success.
 *          Negative value on failure.
 * remar  : Created to allow all reasons for OLC rejection.
 *          cmChannelDropReason will still work, using the reason 'unspecified'.
 ************************************************************************/
RVAPI int RVCALLCONV cmChannelRejectReason(
    IN  HCHAN            hsChan,
    IN  cmRejectLcnReason reason);


RVAPI int RVCALLCONV
cmChannelRequestClose(
          /*
        - New: Request to close incoming channel.
          */
          IN    HCHAN       hsChan,
        IN  cmCloseLcnReason reason,
        cmQosCapability * cmQOSCapability
          );

/* Gets on the outgoing side request to close channel, reason and Qos capability of remote endpoint */
RVAPI int RVCALLCONV
cmChannelGetRequestCloseParam(  IN  HCHAN       hsChan,
                                OUT  cmCloseLcnReason *reason,
                                OUT cmQosCapability * cmQOSCapability
                               );

/* Multipoint operations_______________________________________________________________________________*/




RVAPI int RVCALLCONV
cmCallStartConference(
              /* Enter call conference mode */
              IN      HCALL               hsCall
              );

RVAPI int RVCALLCONV
cmCallCancelConference(
               /* Cancel the call conference mode */
               IN      HCALL               hsCall
               );



/*   Multipoint mode set/cancel operations */

RVAPI int RVCALLCONV
cmCallMultipointCommand(
          /* Sends multipoint command (On or Off) message */
          IN  HCALL hsCall,
          IN  RvBool isModeOn /* RV_TRUE: mp mode (On). RV_FALSE: cancel mp mode (Off) */
          );


RVAPI int RVCALLCONV
cmCallMultipointStatus(
          /* Gets the multipoint mode status (on or off) */
          IN  HCALL hsCall,
          OUT RvBool *isModeOn /* RV_TRUE: mp mode (On). RV_FALSE: cancel mp mode (Off) */
          );


#if (RV_H245_LEAN_H223 == RV_NO)
RVAPI int RVCALLCONV
cmChannelSendTransportCapInd(
         IN     HCHAN       hsChan,
         IN     int         nodeId);  /* Node ID of type TransportCapability */
#endif

RVAPI int RVCALLCONV
cmChannelSendMiscCommand(
         IN     HCHAN                  hsChan,
         IN     cmMiscellaneousCommand miscCommand);


/* Delete pvt of remote capability to reduce memory */
RVAPI
int RVCALLCONV cmFreeCapability(  IN HCALL hsCall);




RVAPI
RvInt32 RVCALLCONV cmChannelGetNumber(IN HCHAN hsChan);


/* This function will build a Multimedia System Control Message and will return the node ID of the message, and
   the node ID to which the message itself (according to the messageType enumerations) should be inserted (if at
   all). The function will return 0 on success and -1 on failure. */
RVAPI int RVCALLCONV
cmBuildMultimediaSystemControlMessage(IN  HAPP              hApp,
                                      IN  cmH245MessageType messageType,
                                      IN  int               lcn,
                                      OUT RvPvtNodeId *     messageNode,
                                      OUT RvPvtNodeId *     insertionNode);






#ifdef __cplusplus
}
#endif


#endif  /* CMCTRL_H */


