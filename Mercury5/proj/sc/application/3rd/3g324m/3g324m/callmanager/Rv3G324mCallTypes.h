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

#ifndef _RV_3G324M_CALL_TYPES_H_
#define _RV_3G324M_CALL_TYPES_H_


/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "cmH245GeneralDefs.h"


#ifdef __cplusplus
extern "C" {
#endif


/*-----------------------------------------------------------------------*/
/*                           TYPE DEFINITIONS                            */
/*-----------------------------------------------------------------------*/
/* Rv3G324mCallMonaMPCType
 * ----------------------------------------------------------------------------
 * Definitions of currently supported MPC channel types.
 */
typedef enum
{
    Rv3G324mCallMonaMPCTypeUnknown = 0,
    Rv3G324mCallMonaMPCTypeAmr,
    Rv3G324mCallMonaMPCTypeAmrWB,
    Rv3G324mCallMonaMPCTypeH264,
    Rv3G324mCallMonaMPCTypeMpeg4,
    Rv3G324mCallMonaMPCTypeH263,
    Rv3G324mCallMonaMPCTypeLast
} Rv3G324mCallMonaMPCType;

/* Rv3G324mCallMuxLevel
 * ----------------------------------------------------------------------------
 * Defines the multiplex level.
 */
typedef enum
{
    Rv3G324mCallMuxLevelUnknown = -1,
    Rv3G324mCallMuxLevel0,
    Rv3G324mCallMuxLevel1,
    Rv3G324mCallMuxLevel1WithDoubleFlag,
    Rv3G324mCallMuxLevel2,
    Rv3G324mCallMuxLevel2WithOptionalHeader,
    Rv3G324mCallMuxLevel3,
    Rv3G324mCallMuxLevel3WithOptionalHeader
} Rv3G324mCallMuxLevel;


/* Rv3G324mAudioType
 * ------------------------------------------------------------------------
 * Audio types supported by the 3G-324M Toolkit.
 * Needed for the generation of the multiplex entries table.
 */
typedef enum
{
    /* AMR codec types by their bitrate */
    Rv3G324mAudioAMR_4_75 = 0,
    Rv3G324mAudioAMR_5_15 = 1,
    Rv3G324mAudioAMR_5_90 = 2,
    Rv3G324mAudioAMR_6_70 = 3,
    Rv3G324mAudioAMR_7_40 = 4,
    Rv3G324mAudioAMR_7_95 = 5,
    Rv3G324mAudioAMR_10_2 = 6,
    Rv3G324mAudioAMR_12_2 = 7

} Rv3G324mAudioType;



/* Rv3G324mCallState
 * ------------------------------------------------------------------------
 * 3G-324M call states.
 * These states are reported by Rv3G324mCallStateChangedEv().
 */
typedef enum
{
    Rv3G324mCallStateInit = -1,			/* The Init state is the initial state 
										of the Call state machine. Upon call creation, 
										the call assumes the Init state. A call to 
										Rv3G324mCallOpen() and H.223 multiplex level 
										synchronization will move the call to the 
										Synchronized state. A call to Rv3G324mCallDrop(), 
										Rv3G324mCallDisconnected(), expiration of the 
										synchronization timer, or receiving an H.245 
										EndSessionCommand message will move the call 
										to the Disconnected state. */
    Rv3G324mCallStateSynchronized,		/* The call assumes the Synchronized state when 
										H.223 multiplex level synchronization is achieved. 
										After the H.245 TerminalCapabilitySet and 
										MasterSlaveDetermination procedures have been 
										completed, the call will assume the Connected state. 
										A call to Rv3G324mCallDrop(), Rv3G324mCallDisconnected(),
										or receiving an EndSessionCommand message will move 
										the call to the Disconnected state. 										
                                        The state mode indicated along with this state declares the multiplexing level with which the call was synchronized. */
    Rv3G324mCallStateConnected,			/* The call assumes the Connected state when the 
										H.245 TerminalCapabilitySet and MasterSlaveDetermination 
										procedures have been completed and the control 
										channel is established. An incoming 
										MultiplexEntrySendAck message will move the call 
										to the ConnectedChannels state. A call to 
										Rv3G324mCallDrop(), Rv3G324mCallDisconnected(), 
										or receiving an EndSessionCommand message will 
										move the call to the Disconnected state. */
    Rv3G324mCallStateConnectedChannels, /* The call assumes the ConnectedChannels after 
										receiving a MultiplexEntrySendAck message on the 
										control channel. In this state, the application 
										can start sending data on the logical channels. 
										A call to Rv3G324mCallDrop(), Rv3G324mCallDisconnected(),
										or receiving an EndSessionCommand message will move 
										the call to the Disconnected state. */
    Rv3G324mCallStateDisconnected,		/* The call assumes the Disconnected state after 
										calling Rv3G324mCallDrop(), Rv3G324mCallDisconnected(), 
										or receiving an EndSessionCommand message in all 
										states except for the Idle state. Expiration of the 
										synchronization timer in the Init state will also 
										move the call to the Disconnected state. The call 
										will then move automatically to the Idle state. 
										After reaching this state, the application should 
										stop calling Rv3G324mCallSend(), Rv3G324mCallReceive(), 
										and Rv3G324mCallReceiveMuxPdu(). */
    Rv3G324mCallStateIdle,				/* The Idle state is the terminal state of the Call 
										state machine. In this state the call no longer exists 
										and the function Rv3G324mCallDestruct() should be called. */
    Rv3G324mCallStateResetting,			/* The call assumes the Resetting state after calling 
										Rv3G324mCallReset() or receiving an H.245 
										EndSessionCommand with the gstnOptions field set to 
										v34H324. Resetting a call restarts the state machine 
										from the beginning, as if Rv3G324mCallOpen() had been 
										called when the call was in the Rv3G324mCallStateInit 
										state. The call will try to get synchronized on the 
										multiplexing level all over again. */
    Rv3G324mCallStateLostSynch			/* The call assumes the LostSynch state after it loses 
										synchronization of the H.223 multiplex level for too long. 
										Some network switches do not indicate call disconnection 
										properly when a congested call drop. As a result, the 
										call might stay open. This indication allows the 
										application to drop the call when this occurs, by 
										calling Rv3G324mCallDrop(). */
} Rv3G324mCallState;


/* Rv3G324mCallStateMode
 * ------------------------------------------------------------------------
 * 3G-324M Call state modes. Supplies additional information about the
 * reason of the given state. 
 * These state modes are reported by Rv3G324mCallStateChangedEv().
 */
typedef enum
{
    Rv3G324mCallStateModeNA = -1, /* State mode that is used when no additional information 
								  about the state itself can be supplied. */

	/* State modes for Rv3G324mCallStateDisconnected */
    Rv3G324mCallStateModeDisconnectedLocal, /* The local side has disconnected this call 
											using Rv3G324mCallDrop(). */
    Rv3G324mCallStateModeDisconnectedUnknown, /* The reason for disconnection is unknown. */
    Rv3G324mCallStateModeDisconnectedUnSynchronized, /* The local side has disconnected 
													 this call when the multiplex level
													 synchronization timer expires and
													 the call is still in the Init state. */

    /* State modes for Rv3G324mCallStateSynchronized */
    Rv3G324mCallStateModeSynchronizedMuxLevel0,	/* Indicated when the state indicated 
												is Rv3G324mCallStateSynchronized and 
												the multiplexing level used is 0. */
    Rv3G324mCallStateModeSynchronizedMuxLevel1,	/* Indicated when the state indicated 
												is Rv3G324mCallStateSynchronized and 
												the multiplexing level used is 1 (H.223 
												Annex A). */
    Rv3G324mCallStateModeSynchronizedMuxLevel2,	/* Indicated when the state indicated 
												is Rv3G324mCallStateSynchronized and 
												the multiplexing level used is 2 (H.223 
												Annex B). */
    Rv3G324mCallStateModeSynchronizedMuxLevel3,	/* Indicated when the state indicated 
												is Rv3G324mCallStateSynchronized and 
												the multiplexing level used is 3 (H.223 
												Annex C or D). */
    Rv3G324mCallStateModeSynchronizedMuxLevel2OptHeader, /* Indicated when the state indicated 
														 is Rv3G324mCallStateSynchronized and 
														 the multiplexing level used is 2 with 
														 optional header. */
    Rv3G324mCallStateModeSynchronizedMuxLevel3OptHeader /* Indicated when the state indicated 
														is Rv3G324mCallStateSynchronized and 
														the multiplexing level used is 3 
														(H.223 Annex C or D) with optional header. */
} Rv3G324mCallStateMode;


/* Rv3G324mCallParam
 * ------------------------------------------------------------------------
 * Defines the parameters of the call. 
 * This enumeration is used by Rv3G324mCallSetParam() and Rv3G324mCallGetParam().
 */
typedef enum
{
    Rv3G324mCallParamUnknown  = -1,

    Rv3G324mCallParamMultipleMessagesPerMuxPdu,	/* Defines whether to send more than one H.245 
												message in one MUX-PDU. Messages will be sent 
												in a single MUX-PDU only if they are sent from 
												within a callback. It is advisable to set this 
												parameter to RV_TRUE to reduce the call setup 
												time. Parameter type: RvBool. Default value: 
												RV_FALSE. */
    Rv3G324mCallParamMultiplexLevelSynchronizationTimeout,	/* Defines the timeout in milliseconds 
															of the multiplex level synchronization
															procedure. This time is calculated 
															from the moment Rv3G324mCallOpen() is
															called. Parameter type: RvInt32. 
															Default value: 5000 milliseconds. */
    Rv3G324mCallParamUseWnsrp,	/* Defines whether to use the WNSRP mode instead of NSRP/SRP 
								where possible. It is highly recommended to set this parameter 
								to RV_TRUE to reduce setup time. Parameter type: RvBool. 
								Default value: RV_FALSE.*/
    Rv3G324mCallParamHardwareStuffing, /* RvBool: Defines whether specific hardware should be 
									   used to do the stuffing. */
    Rv3G324mCallParamSaveIndication, /* Indicates if the call should be saved for high 
	                                 availability. Parameter type: RvBool. */
    Rv3G324mCallParamSavedCall, /* Indicates a stored call for high availability. 
							    Parameter type: RvBool. */
    Rv3G324mCallParamRetransmitOnIdle, /* Indicates if the call setup will be done in a 
									   retransmission on idle mode. When retransmission on 
									   idle is used (set to RV_TRUE), the Stack will send 
									   retransmissions of NSRP and WNSRP commands for H.245 
									   messages during the call setup stages only, allowing 
									   considerably faster call setup times on error-prone 
									   connections. It is highly recommended to set this 
									   parameter to RV_TRUE. Parameter type: RvBool. 
									   Default value: RV_FALSE. */
    Rv3G324mCallParamMaxCCSRLSegmentSize, /* Maximum size of a CCSRL segment to allow. 
										  Lowering this value is suggested when working on 
										  highly error-prone connections. The value of this 
										  parameter should not be lowered below 40. Parameter 
										  type: RvUint8. Default value: 255. */
	Rv3G324mCallParamUseMONA, /* RV_TRUE if the call can use MONA for quick setup. */
    Rv3G324mCallParamTxMPCTypes, /* Supported transmitting MPC types. */
    Rv3G324mCallParamRxMPCTypes, /* Supported receiving MPC types. */
    Rv3G324mCallParamUseACP, /* RV_TRUE if the call can use ACP for quick setup (with MONA 
						     or standalone). */
    Rv3G324mCallParamACPTxAudioChannel, /* The mux table entry number of the ACP audio channel. */ 
    Rv3G324mCallParamACPTxVideoChannel,  /* The mux table entry number of the ACP video channel. */ 
    Rv3G324mCallParamACPRxAudioChannel,  /* The demux table entry number of the ACP audio channel. */ 
    Rv3G324mCallParamACPRxVideoChannel,  /* The demux table entry number of the ACP video channel. */
    Rv3G324mCallParamLast /* Makes compilation a bit easier. Should be ignored by developers. */
} Rv3G324mCallParam;


/* Rv3G324mCallLegStatistics
 * ------------------------------------------------------------------------
 * Defines a structure that holds the call leg statistics information collected 
 * from the multiplexer or demultiplexer. 
 * This structure should not be used directly, 
 * but rather as part of the Rv3G324mCallStatistics structure.
 */
typedef struct 
{
    RvSize_t    entries[16]; /* Number of times each multiplexer entry was used. */
    RvSize_t    totalBytes; /* Number of bytes that were handled so far. */
    RvSize_t    stuffingBytes; /* Number of bytes that were recognized as stuffing. */
    RvSize_t    mediaBytes; /* Number of bytes that were dedicated to the actual media (without AL overhead). */
    RvSize_t    mediaPackets; /* Number of "packets" that were dedicated to the actual media. */
    RvSize_t    muxPduCount; /* Number of MUX-PDUs handled so far. */
    RvSize_t    muxPduSize; /* Number of bytes in MUX-PDUs handled so far. */
} Rv3G324mCallLegStatistics;


/* Rv3G324mCallStatistics
 * ------------------------------------------------------------------------
 * Defines a structure holding collected call statistics information. 
 * This structure can be used only if RV_H223_USE_STATISTICS is configured 
 * to RV_YES in rvusrconfig.h.
 */
typedef struct 
{
    Rv3G324mCallLegStatistics   outgoing; /* Outgoing call leg statistics (multiplexer). */
    Rv3G324mCallLegStatistics   incoming; /* Incoming call leg statistics (demultiplexer). */
    RvSize_t                    mediaCrcErrors; /* Number of media packets handled with CRC errors in them. */
} Rv3G324mCallStatistics;





/******************************************************************************
 * Rv3G324mCallStateChangedEv
 * ----------------------------------------------------------------------------
 * General: Indication of a change in the call state. This is the main event 
 * handler for call objects. For more information, see the call state machine 
 * in the RADVISION 3G-324M Protocol Toolkit Programmer Guide.
 *
 * Return Value: None
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mAppCall   - The application call handle of the call.
 *         h3G324mCall      - The newly created call handle.
 *         callState        - The new state of the call.
 *         callStateMode    - The state mode associated with the new state of the call.
 *****************************************************************************/
typedef void (RVCALLCONV * Rv3G324mCallStateChangedEv) (
    IN  HAPPCALL                h3G324mAppCall,
    IN  HCALL                   h3G324mCall,
    IN  Rv3G324mCallState       callState,
    IN  Rv3G324mCallStateMode   callStateMode);


/******************************************************************************
 * Rv3G324mCallSendMessageEv
 * ----------------------------------------------------------------------------
 * General: Callback function called prior to sending an H.245 message to the 
 * other side of the call. The application can modify the message or decide 
 * not to send it in this function. Callback function called prior to sending 
 * an H.245 message to the other side of the call. This callback allows the  
 * application to change the content of the message or to cause the Stack 
 * not to send this message at all (but act as if it did). After this callback,  
 * the node ID of the message should be considered as invalid, even if the  
 * application has asked not to send the message.
 *
 * Return Value: RV_TRUE if the application does not want the message to be sent, 
 * or RV_FALSE if the application wants the message to be sent.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mAppCall   - The application call handle of the call.
 *         h3G324mCall      - The newly created call handle.
 *         messageNodeId    - The node ID of the H.245 message that is about to be sent.
 *****************************************************************************/
typedef RvBool (RVCALLCONV * Rv3G324mCallSendMessageEv) (
    IN  HAPPCALL                h3G324mAppCall,
    IN  HCALL                   h3G324mCall,
    IN  RvPvtNodeId             messageNodeId);


/******************************************************************************
 * Rv3G324mCallReceiveMessageEv
 * ----------------------------------------------------------------------------
 * General: Callback function called prior to handling an incoming H.245 message
 *          on a call. This callback allows the application to change the content
 *          of the message before it is processed by the stack or to cause the
 *          stack not to handle this message at all.
 *          After this callback, the message's nodeId should be considered as
 *          invalid - even if the application asked not to receive the message.
 *
 * Return Value: RV_TRUE if the application does not want the Stack to handle the message, 
 * or RV_FALSE if the application wants the Stack to handle the message.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mAppCall   - The application call handle of the call.
 *         h3G324mCall      - The newly created call handle.
 *         messageNodeId    - The node ID of the received H.245 message.
 *****************************************************************************/
typedef RvBool (RVCALLCONV * Rv3G324mCallReceiveMessageEv) (
    IN  HAPPCALL                h3G324mAppCall,
    IN  HCALL                   h3G324mCall,
    IN  RvPvtNodeId             messageNodeId);


/******************************************************************************
 * Rv3G324mCallGetBufferEv
 * ----------------------------------------------------------------------------
 * General: Callback function called when there is a need for a buffer for 
 * processing incoming or outgoing media frames. This function allows the 
 * application to handle buffer allocation for media frames manually, 
 * reducing the memory constraints and CPU usage of the Stack.
 *
 * Application buffers are always logical channel buffers. 
 * If this callback is not implemented by the application or if pSize that is 
 * returned by this callback is 0, then the Stack will try to use a buffer 
 * from its internal memory pool. The application’s decision about the 
 * responsibility of buffer allocation is done per call/channel, which means 
 * that once the decision is made for a call/channel, it cannot be changed 
 * during the life of that call/channel. The application will be requested 
 * only for logical channel buffers and never for control channel buffers. 
 * This way, the application can focus on the media being sent. Inside this 
 * callback function, the application should be aware that internal Stack 
 * resources linked to the channel and call objects are locked. This means 
 * that the application should not lock its own call or channel objects if 
 * these are locked when it uses the API functions of the Stack. Otherwise, 
 * a deadlock might occur.
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mAppCall   - The application call handle of the call.
 *         h3G324mCall      - The call handle.
 *         h3G324mAppChan   - The application channel handle.
 *         h3G324mChan      - The channel handle. The channel handles can be 
							  used to decide on the allocation size to use 
							  for the request (audio channels usually require 
							  considerably smaller buffers than video channels).
 * Output: pBuffer          - The buffer to be supplied by the application.
 *         pSize            - The buffer size.
 *****************************************************************************/
typedef void (RVCALLCONV * Rv3G324mCallGetBufferEv) (
    IN  HAPPCALL                h3G324mAppCall,
    IN  HCALL                   h3G324mCall,
    IN  HAPPCHAN                h3G324mAppChan,
    IN  HCHAN                   h3G324mChan,
    OUT RvUint8                 **pBuffer,
    OUT RvUint32                *pSize);


/******************************************************************************
 * Rv3G324mCallReleaseBufferEv
 * ----------------------------------------------------------------------------
 * General: Called when the given buffer is no longer needed and can be released. 
 * This function is called only for buffers explicitly allocated by the 
 * application in Rv3G324mCallGetBufferEv().
 * Application buffers are always logical channel buffers. 
 * The application will be requested only for logical channel buffers and never 
 * for control channel buffers. This way, the application can focus on the media 
 * being sent. Inside this callback function, the application should be aware 
 * that internal Stack resources linked to the channel and the call objects are 
 * locked. This means that the application should not lock its own call or channel 
 * objects if these are locked when it uses the API functions of the Stack. 
 * Otherwise, a deadlock might occur.
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mAppCall   - The application’s call handle of the call.
 *         h3G324mCall      - The call handle.
 *         h3G324mAppChan   - The application’s channel handle.
 *         h3G324mChan      - The channel handle.
 *         pBuffer          - The buffer supplied by the application, which can be deallocated.
 * Output:
 *****************************************************************************/
typedef void (RVCALLCONV * Rv3G324mCallReleaseBufferEv) (
    IN  HAPPCALL                h3G324mAppCall,
    IN  HCALL                   h3G324mCall,
    IN  HAPPCHAN                h3G324mAppChan,
    IN  HCHAN                   h3G324mChan,
    IN  RvUint8                 *pBuffer);


/******************************************************************************
 * Rv3G324mCallLogicalChannelReceivedDataEv
 * ----------------------------------------------------------------------------
 * General: Callback function called to notify that data was received for the 
 * specified channel. The application should decode and play the received data.
 *
 * Return Value: None.
 * See Also: Rv3G324mCallLogicalChannelReceivedDataExtEv.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mAppCall   - The application call handle of the call.
 *         h3G324mCall      - The newly created call handle.
 *         h3G324mAppChan   - The application channel handle.
 *         h3G324mChan      - The channel handle.
 *         pBuffer          - The buffer that contains the received data.
 *         size             - The buffer size.
 * Output: None.
 *****************************************************************************/
typedef void (RVCALLCONV * Rv3G324mCallLogicalChannelReceivedDataEv) (
    IN  HAPPCALL                h3G324mAppCall,
    IN  HCALL                   h3G324mCall,
    IN  HAPPCHAN                h3G324mAppChan,
    IN  HCHAN                   h3G324mChan,
    IN  RvUint8                 *pBuffer,
    IN  RvUint32                size);

/******************************************************************************
 * Rv3G324mCallLogicalChannelReleaseSendBufferEv
 * ----------------------------------------------------------------------------
 * General: Called when the given buffer to Rv3G324mCallLogicalChannelSendData() 
 * function is no longer needed and can be released.
 *
 * Inside this callback function, the application should be aware that internal 
 * Stack resources linked to the channel and call objects are locked. This 
 * means that the application should not lock its own call or channel objects 
 * if these are locked when it uses the API functions of the Stack. Otherwise, 
 * a deadlock might occur. Rv3G324mCallLogicalChannelSendData() and 
 * Rv3G324mCallLogicalChannelSendDataExt() shall not be called from within this 
 * callback. The sending action should be done whenever the encoder has input 
 * for the Stack and not when the previous frame is released.
 * 
 * Note: Implementation of this callback is not mandatory. This callback can be 
 * implemented if the application needs to release the buffer immediately after 
 * the Stack has finished using it.
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mAppCall   - The application’s call handle of the call.
 *         h3G324mCall      - The newly created call handle.
 *         h3G324mAppChan   - The application’s channel handle.
 *         h3G324mChan      - The channel handle.
 *         pBuffer          - The buffer supplied by the application that can be released.
 *         size             - The buffer size as initially given by the application.
 * Output: None.
 *****************************************************************************/
typedef void (RVCALLCONV * Rv3G324mCallLogicalChannelReleaseSendBufferEv) (
    IN  HAPPCALL                h3G324mAppCall,
    IN  HCALL                   h3G324mCall,
    IN  HAPPCHAN                h3G324mAppChan,
    IN  HCHAN                   h3G324mChan,
    IN  RvUint8                 *pBuffer,
    IN  RvUint32                size);

/******************************************************************************
 * Rv3G324mCallMonaMPCChannelReleaseSendBufferEv
 * ----------------------------------------------------------------------------
 * General: Callback function that is called when the given buffer to the 
 * Rv3G324mCallMonaMPCChannelSendData() function is no longer needed and can be 
 * released.
 *
 * Note: Implementation of this callback is not mandatory. This callback can be 
 * implemented if the application needs to release the buffer immediately after 
 * the Stack has finished using it.
 *
 * Arguments:
 * Input:  h3G324mAppCall       - Application's call handle of the call.
 *         h3G324mCall          - The newly created call handle.
 *         mpcChannel           - The MPC channel.
 *         pBuffer              - Buffer to be released.
 *         size                 - The buffer size.
 *
 * Output: None.
 *
 * Return Value: None.
 *****************************************************************************/
typedef void (RVCALLCONV * Rv3G324mCallMonaMPCChannelReleaseSendBufferEv) (
    IN  HAPPCALL                h3G324mAppCall,
    IN  HCALL                   h3G324mCall,
    IN  Rv3G324mCallMonaMPCType mpcChannel,
    IN  RvUint8                 *pBuffer,
    IN  RvUint32                size);


/******************************************************************************
 * Rv3G324mCallLogicalChannelNotifyDrtxEv
 * ----------------------------------------------------------------------------
 * General: Callback function called when an I-PDU that was transmitted 
 * previously may have been discarded before the request for retransmission 
 * had been received and because of this a DRTX message is about to be sent.
 *
 * Inside this callback function, the application should be aware that 
 * internal Stack resources linked to the channel and call objects are locked. 
 * This means that the application should not lock its own call or channel 
 * objects if these are locked when it uses the API functions of the Stack. 
 * Otherwise, a deadlock might occur.
 *
 * Note: The DRTX message is used by an AL3 transmitter to decline the 
 * requested retransmission of an I-PDU, when that I-PDU is not available 
 * in the sent buffer at the time the SREJ PDU is received.
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mAppCall       - The application’s call handle of the call.
 *         h3G324mCall          - The call handle.
 *         h3G324mAppChan       - The application's channel handle.
 *         h3G324mChan          - The channel handle.
 *         muxSduSequenceNumber - The sequence number of the I-PDU that has been discarded.
 * Output: none.
 *****************************************************************************/
typedef void (RVCALLCONV * Rv3G324mCallLogicalChannelNotifyDrtxEv) (
    IN  HAPPCALL                h3G324mAppCall,
    IN  HCALL                   h3G324mCall,
    IN  HAPPCHAN                h3G324mAppChan,
    IN  HCHAN                   h3G324mChan,
    IN  RvUint16                muxSduSequenceNumber);


/******************************************************************************
 * Rv3G324mCallLogicalChannelRtxRequestEv
 * ----------------------------------------------------------------------------
 * General: Callback function, called when a bidirectional channel has found 
 * that media frames from the remote terminal may need to be retransmitted. 
 * This callback is invoked only for bidirectional channels that were opened 
 * using retransmissions that supported AL3, AL1M, or AL3M. In this callback, 
 * the application may decide to request retransmission of only some of the 
 * lost frames, or it may decide not to request retransmission at all.
 *
 * Remarks: Inside this callback function, the application should be aware 
 * that internal Stack resources linked to the channel and call objects are 
 * locked. This means that the application should not lock its own call or 
 * channel objects if these are locked when it uses the API functions of the 
 * Stack. Otherwise, a deadlock might occur.
 *
 * Return Value: The maximum number of frames for which retransmission may 
 * be asked. For example, if expectedSequenceNumber=10 while 
 * receivedSequenceNumber=15, then a return value of 2 indicates that the 
 * frames with the sequence numbers 13 and 14 should be retransmitted. 
 * If the retransmission request is for a CRC error, then a return value of 
 * 1 indicates that the application wants a retransmission due to the CRC 
 * error. A return value of 0 indicates that the application does not want 
 * any retransmission requests for the missing or bad frames.
 *
 * See Also: Rv3G324mCallLogicalChannelNotifyDrtxEv.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mAppCall           - Application's call handle of the call.
 *         h3G324mCall              - The newly created call handle.
 *         h3G324mAppChan           - Application's channel handle.
 *         h3G324mChan              - The channel handle.
 *         expectedSequenceNumber   - The sequence number that was expected 
 *                                    as the next incoming frame on this channel.
 *         receivedSequenceNumber   - The sequence number that was received. 
 *                                    If this sequence number is equal to the 
 *                                    one in expectedSequenceNumber, then it is 
 *                                    an indication that a CRC error occurred 
 *                                    on the frame and the application may 
 *                                    choose to ask for a retransmission for this frame.
 * Output: None.
 *****************************************************************************/
typedef RvInt32 (RVCALLCONV * Rv3G324mCallLogicalChannelRtxRequestEv) (
    IN  HAPPCALL                h3G324mAppCall,
    IN  HCALL                   h3G324mCall,
    IN  HAPPCHAN                h3G324mAppChan,
    IN  HCHAN                   h3G324mChan,
    IN  RvUint32                expectedSequenceNumber,
    IN  RvUint32                receivedSequenceNumber);


/******************************************************************************
 * Rv3G324mCallLogicalChannelReceivedDataExtEv
 * ----------------------------------------------------------------------------
 * General: Callback function, called to notify that data has been received for 
 * the specified channel. This callback can be used instead of 
 * Rv3G324mCallLogicalChannelReceivedDataEv() to indicate lost packets (using 
 * the sequence number when applicable) and to indicate that certain data had 
 * a CRC error. The application should decode and play the received data.
 *
 * Return Value: None.
 * See Also: Rv3G324mCallLogicalChannelReceivedDataEv.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mAppCall   - Application's call handle of the call.
 *         h3G324mCall      - The new created call handle.
 *         h3G324mAppChan   - Application's channel handle.
 *         h3G324mChan      - The channel handle.
 *         pBuffer          - The buffer that contains the received data.
 *         size             - The buffer size.
 *         bAnyError        - RV_TRUE if the buffer contains an error (CRC check 
 *                            failed for this buffer). If there is an error, 
 *                            the application may decide to discard the buffer 
 *                            or to try and use the buffer "as is", preferably if 
 *                            an error-resilient decoder is available.
 *         sequenceNumber   - Sequence number of the buffer received (0 if 
 *                            sequence numbering is not supported by this 
 *                            channel). The sequence number can be used to 
 *                            identify a state of lost packets, and for packet 
 *                            loss concealment techniques.
 * Output: None.
 *****************************************************************************/
typedef void (RVCALLCONV * Rv3G324mCallLogicalChannelReceivedDataExtEv) (
    IN  HAPPCALL                h3G324mAppCall,
    IN  HCALL                   h3G324mCall,
    IN  HAPPCHAN                h3G324mAppChan,
    IN  HCHAN                   h3G324mChan,
    IN  RvUint8                 *pBuffer,
    IN  RvUint32                size,
    IN  RvBool                  bAnyError,
    IN  RvUint16                sequenceNumber);


/******************************************************************************
 * Rv3G324mCallReceivedResetRequestEv
 * ----------------------------------------------------------------------------
 * General: Callback function, called when an H.245 EndSessionCommand message 
 * with the gstnOption.v34H324 choice was received. This message is a request 
 * to reset the call without disconnecting the physical connection. 
 * In this callback the application can return RV_TRUE to accept the Reset 
 * request. Otherwise, the call will be dropped as usual (including the 
 * physical connection).
 *
 * Return Value: RV_TRUE: The application accepts the Reset request.
 *               RV_FALSE: The application rejects the Reset request--
 *               the call will be dropped as usual.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mAppCall       - Application's call handle of the call.
 *         h3G324mCall          - The call handle.
 * Output: none.
 *****************************************************************************/
typedef RvBool (RVCALLCONV * Rv3G324mCallReceivedResetRequestEv) (
    IN  HAPPCALL                h3G324mAppCall,
    IN  HCALL                   h3G324mCall);


/******************************************************************************
 * Rv3G324mCallBitShiftIndicationEv
 * ----------------------------------------------------------------------------
 * General: Callback function, called before the Stack is synchronized on the 
 * incoming bit stream when the Stack detects that it has received the stream 
 * bit shifted. This situation may occur when working directly with a service 
 * provider, and usually happens when a high load of calls exists. 
 * The application is expected to handle the bit shifting and supply in future 
 * calls to Rv3G324mCallReceive() buffers with corrected bit shift.
 *
 * Bit shifting is indicated only if there is a bit shift. 
 * It is never indicated for mux-level 0.
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mAppCall       - Application's call handle of the call.
 *         h3G324mCall          - The call handle.
 *         bitShift             - Number of bits with which the stream is shifted.
 * Output: None.
 *****************************************************************************/
typedef void (RVCALLCONV * Rv3G324mCallBitShiftIndicationEv) (
    IN  HAPPCALL                h3G324mAppCall,
    IN  HCALL                   h3G324mCall,
    IN  RvUint8                 bitShift);


/******************************************************************************
 * Rv3G324mCallRandomNumberEv
 * ----------------------------------------------------------------------------
 * General: Callback function, called when a random number is required that 
 * the application can control. This callback is only needed to be implemented 
 * by applications using the High Availability feature.
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324m              - The Stack handle.
 *         h3G324mCall          - The call handle in the Stack.
 *         h3G324mAppCall       - The call handle in the application.
 * Output: value                - The random number determined by the application.
 *****************************************************************************/
typedef void (RVCALLCONV * Rv3G324mCallRandomNumberEv) (
    IN  HAPP                    h3G324m,
    IN  HCALL                   h3G324mCall,
    IN  HAPPCALL                h3G324mAppCall,
    OUT RvUint32                *value);

/******************************************************************************
 * Rv3G324mCallMessageSendingFailureEv
 * ----------------------------------------------------------------------------
 * General: A callback function that is called when an H.245 message failed 
 * to be sent. It is recommended to drop the call in this callback, but it is 
 * up to the application to decide whether it will do this.
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mAppCall       - The call handle in the application.
 *         h3G324mCall          - The call handle in the Stack.  
 * Output: None.
 *****************************************************************************/
typedef void (RVCALLCONV * Rv3G324mCallMessageSendingFailureEv) (
    IN  HAPPCALL                h3G324mAppCall,
    IN  HCALL                   h3G324mCall);

/******************************************************************************
 * Rv3G324mCallMonaMPCChannelReceivedDataEv
 * ----------------------------------------------------------------------------
 * General: Callback function called to notify that data has been received for 
 * the specified MPC phantom channel.
 *
 * Arguments:
 * Input:  h3G324mAppCall   - Application's call handle of the call.
 *         h3G324mCall      - The newly created call handle.
 *         mpcChannel       - The phantom channel index.  
 *         pBuffer          - The buffer that contains the received data.
 *         size             - The buffer size.
 *         bAnyError        - RV_TRUE if the buffer contains an error 
 *                            (CRC check failed for this buffer).
 *         sequenceNumber   - The sequence number of the buffer received (0 
 *                            if sequence numbering is not supported by this 
 *                            channel). The sequence number can be used to 
 *                            identify a lost packets situation.
 *
 * Output: None.
 *
 *Return Value: None.
 *****************************************************************************/
typedef void (RVCALLCONV * Rv3G324mCallMonaMPCChannelReceivedDataEv) (
    IN  HAPPCALL                h3G324mAppCall,
    IN  HCALL                   h3G324mCall,
    IN  Rv3G324mCallMonaMPCType mpcChannel,
    IN  RvUint8                 *pBuffer,
    IN  RvUint32                size,
    IN  RvBool                  bAnyError,
    IN  RvUint16                sequenceNumber);


/******************************************************************************
 * Rv3G324mMonaPreferenceReceivedEv
 * ----------------------------------------------------------------------------
 * General: Callback function called when the first MONA preference message 
 * is received.
 * 
 * Arguments:
 * Input:  h3G324mAppCall       - Application's call handle of the call.
 *         h3G324mCall          - The call handle.
 *         mpcRx                - The bitmask of matching MPC types for receiving media.
 *         mpcTx                - MPC types for transmitting media.
 *         pMsg                 - The MONA preference message.
 *         bufferSize           - The size of the preference message, in bytes.
 *         bAnyError            - RV_TRUE if the frame might contain errors (CRC check failed).
 *
 * Output: None.
 *
 * Return Value: RV_OK on success. Other values on failure.
 *****************************************************************************/
typedef void (RVCALLCONV * Rv3G324mMonaPreferenceReceivedEv) (
    IN  HAPPCALL                h3G324mAppCall,
    IN  HCALL                   h3G324mCall,
    IN  RvUint16                mpcRx,
    IN  RvUint16                mpcTx,
    IN  RvUint8                 *pMsg,
    IN  RvSize_t                msgSize,
    IN  RvBool                  bAnyError);

/******************************************************************************
 * Rv3G324mMonaPreferenceSendEv
 * ----------------------------------------------------------------------------
 * General: Callback function called in two events:
 * 1. After the required minimum number of MONA preference messages has been sent.
 * 2. After the last MONA preference message was sent.
 * Note that these events can occur simultaneously. 
 * In that case, the event will be raised to the application only once. 
 * This event should be used by the application to decide when to start 
 * sending media on MPC channels.
 *
 * Arguments:
 * Input:  h3G324mAppCall       - Application's call handle of the call.
 *         h3G324mCall          - The call handle.
 *         lastMessage          - RV_TRUE if no more preference messages 
 *                                are going to be sent.
 * Output: None.
 *
 * Return Value: RV_OK on success. Other values on failure.
 *****************************************************************************/
typedef void (RVCALLCONV * Rv3G324mMonaPreferenceSendEv) (
    IN  HAPPCALL                h3G324mAppCall,
    IN  HCALL                   h3G324mCall,
    IN  RvBool                  lastMessage);

/*@**************************************************************************
  * Rv3G324mMonaAckStatusChangedEv (Annex K)
  * ----------------------------------------------------------------------------
  * General: 
  *	Callback function called when the MONA ack status changes.
  *
  * Arguments:
  *
  * Input:  
  *		h3G324mAppCall       - Application's call handle of the call.
  *		h3G324mCall          - The call handle.
  *  	oldAckStatus	     - The current ack status.
  *		newAckStatus	     - The new ack status.
  *
  * Output: 			None.
  *
  * Return Value:	    None.
  ***************************************************************************@*/
typedef void (RVCALLCONV * Rv3G324mMonaAckStatusChangedEv) (
    IN  HAPPCALL                h3G324mAppCall,
    IN  HCALL                   h3G324mCall,
    IN  RvUint8					oldAckStatus,
	IN  RvUint8					newAckStatus);

/* Rv3G324mCallEvHandlers
 * ------------------------------------------------------------------------
 * Structure with function pointers to the callbacks of the call. 
 * This structure is used to set the application callbacks in 
 * the function Rv3G324mCallSetEvHandlers().
 */
typedef struct
{
    Rv3G324mCallStateChangedEv                    pfnStateChangedEv;
    Rv3G324mCallSendMessageEv                     pfnSendMessageEv;
    Rv3G324mCallReceiveMessageEv                  pfnReceiveMessageEv;
    Rv3G324mCallGetBufferEv                       pfnGetBufferEv;
    Rv3G324mCallReleaseBufferEv                   pfnReleaseBufferEv;
    Rv3G324mCallLogicalChannelReceivedDataEv      pfnLogicalChannelReceivedDataEv;
    Rv3G324mCallLogicalChannelReleaseSendBufferEv pfnLogicalChannelReleaseSendBufferEv;
    Rv3G324mCallLogicalChannelNotifyDrtxEv        pfnLogicalChannelNotifyDrtxEv;
    Rv3G324mCallLogicalChannelRtxRequestEv        pfnLogicalChannelRtxRequestEv;
    Rv3G324mCallReceivedResetRequestEv            pfnReceivedResetRequestEv;
    Rv3G324mCallLogicalChannelReceivedDataExtEv   pfnLogicalChannelReceivedDataExtEv;
    Rv3G324mCallBitShiftIndicationEv              pfnBitShiftIndicationEv;
    Rv3G324mCallRandomNumberEv                    pfnGetRandomNumberEv;
    Rv3G324mCallMessageSendingFailureEv           pfnMessageSendingFailureEv;
#if (RV_3G324M_USE_MONA == RV_YES)
    Rv3G324mCallMonaMPCChannelReceivedDataEv      pfnMonaMPCChannelReceivedDataEv;
    Rv3G324mCallMonaMPCChannelReleaseSendBufferEv pfnMonaMPCChannelReleaseSendBufferEv;
    Rv3G324mMonaPreferenceReceivedEv              pfnMonaPreferenceMsgRcvEv;
    Rv3G324mMonaPreferenceSendEv                  pfnMonaPreferenceMsgSendEv;
	Rv3G324mMonaAckStatusChangedEv				  pfnMonaAckStatusChangedEv;
#endif /* USE_MONA */
} Rv3G324mCallEvHandlers;




#ifdef __cplusplus
}
#endif

#endif /* _RV_3G324M_CALL_TYPES_H_ */
