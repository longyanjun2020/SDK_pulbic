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

#ifndef _RV_3G324M_CALL_H_
#define _RV_3G324M_CALL_H_


/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "Rv3G324mCallTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


/*-----------------------------------------------------------------------*/
/*                           FUNCTIONS HEADERS                           */
/*-----------------------------------------------------------------------*/


/******************************************************************************
 * Rv3G324mCallConstruct
 * ----------------------------------------------------------------------------
 * General: Creates a new call object. 
 * This function must be called both for incoming and outgoing calls.
 *
 * Return Value: RV_OK if successful, or another value on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324m          - The Stack instance to use.
 *         h3G324mAppCall   - The application’s call handle for the new call. 
 *							  This handle will be indicated to the application 
 *                            in every event handler invoked on the new call.
 * Output: h3G324mCall      - The new created call handle.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallConstruct(
    IN  HAPP                    h3G324m,
    IN  HAPPCALL                h3G324mAppCall,
    OUT HCALL                  *h3G324mCall);


/******************************************************************************
 * Rv3G324mCallDestruct
 * ----------------------------------------------------------------------------
 * General: Destructs a call object.
 *          This function should be called only if the call has reached the 
 *          Rv3G324mCallStateIdle state or if Rv3G324mCallOpen() was not called 
 *          for this call. The application should call either Rv3G324mCallDrop() 
 *          or Rv3G324mCallDisconnected() to reach the idle state actively.
 *
 * Return Value: RV_OK if successful, or another value on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle to destruct.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallDestruct(
    IN  HCALL                   h3G324mCall);


/******************************************************************************
 * Rv3G324mCallSetStreamingBuffer
 * ----------------------------------------------------------------------------
 * General: Sets a streaming buffer to the multiplexer of the call.
 * If the application uses ISDN or any other networking modem/baseband that 
 * relies on the Stack to perform the stuffing mode that is required by H.223, 
 * it should set a streaming buffer for that purpose using this function. 
 * If the application uses hardware to make sure that the stuffing mode is used 
 * when no media is sent, this function should not be called.
 * This function should be called before calling Rv3G324mCallOpen(), but after 
 * Rv3G324mCallConstruct().
 *
 * Return Value: RV_OK if successful, or another value on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle to destruct.
 *         streamingBuffer  - The buffer to use. This buffer should be allocated 
 *                            by the application and remain for the full duration 
 *                            of the call. If this parameter is given as NULL, 
 *                            the Stack will allocate and deallocate the buffer 
 *                            internally and dynamically.
 *         bufferSize       - The size of the required buffer. 
 *                            The size of the buffer should be at least 512 bytes.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallSetStreamingBuffer(
    IN  HCALL                   h3G324mCall,
    IN  RvUint8                *streamingBuffer,
    IN  RvSize_t                bufferSize);


/******************************************************************************
 * Rv3G324mCallSendH223MultiplexReconfiguration
 * ----------------------------------------------------------------------------
 * General: Generates and sends an H.245 H223MultiplexReconfiguration message 
 * to the remote side of the call. This message is used to change the multiplex 
 * level between the two sides of the call. The function can only be called once 
 * the call has been synchronized. For multiplex level 2, the maxMuxPduPayloadSize 
 * must be no higher than 254. If it is higher, then the call will use 254. 
 * For other multiplex levels, this value is not restricted.
 *
 * Before calling this function, you must stop sending data on logical channels.
 * Most terminals today are not able to handle this procedure, so it is not 
 * recommended to use it. Currently, this function does not change the multiplex 
 * level to or from multiplex level 0.
 * 
 * Return Value: RV_OK if successful, or another value on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall          - The call handle.
 *         eMuxLevel            - The H.223 multiplex level to which to change.
 *         maxMuxPduPayloadSize - The maximum MUX-PDU payload size.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallSendH223MultiplexReconfiguration(
    IN   HCALL                h3G324mCall,
    IN   Rv3G324mCallMuxLevel eMuxLevel,
    IN   RvUint32             maxMuxPduPayloadSize);


/******************************************************************************
 * Rv3G324mCallSetMuxLevel
 * ----------------------------------------------------------------------------
 * General: Sets the Multiplex Level of the call. This function must be called 
 * after the call to Rv3G324mCallConstruct() and before the call to 
 * Rv3G324mCallOpen() or Rv3G324mCallSendH223MultiplexReconfiguration(). 
 * If this function is not used then the default multiplex 
 * level will be 2. For multiplex level 2, the maxMuxRduPayloadSize 
 * parameter must be no more than 254 bytes. If it is higher, then the call 
 * will use 254 bytes. For other multiplex levels, this value is not restricted.
 *
 * Return Value: RV_OK if successful, or another value on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall          - The call handle.
 *         eMuxLevel            - The multiplex level to set to the call.
 *         maxMuxPduPayloadSize - The maximum mux-PDU payload size.
 * Output: none
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallSetMuxLevel(
    IN  HCALL                    h3G324mCall,
    IN  Rv3G324mCallMuxLevel     eMuxLevel,
    IN  RvUint32                 maxMuxPduPayloadSize);


/******************************************************************************
 * Rv3G324mCallIndicateMuxLevel
 * ----------------------------------------------------------------------------
 * General: Sets the mux level used in the call as indicated by the hardware. 
 * This function should be used instead of the automatic synchronization 
 * mechanism which is built into Rv3G324mCallReceive() when the modem used is 
 * responsible for the framing and stuffing done in the call. 
 * This function should be called after calling Rv3G324mCallOpen().
 *
 * Return Value: RV_OK if successful, or another value on failure.
 * See Also: Rv3G324mCallReceiveMuxPdu
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle in the Stack.
 *         eMuxLevel        - The multiplex level the call was synchronized on.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallIndicateMuxLevel(
    IN  HCALL                   h3G324mCall,
    IN  Rv3G324mCallMuxLevel    eMuxLevel);


/******************************************************************************
 * Rv3G324mCallOpen
 * ----------------------------------------------------------------------------
 * General: Opens a call object.
 *          This function should be called prior to sending or receiving data 
 *          with this call object. In automatic operation modes of H.245 this 
 *          function call also starts the establishment of master-slave and 
 *          terminal capabilities negotiation. This function should be called 
 *          after the application has configured the call properly (setting 
 *          the multiplexing level, deciding on software or hardware stuffing, 
 *          etc.)
 * Return Value: RV_OK if successful, or another value on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle to open.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallOpen(
    IN  HCALL                   h3G324mCall);


/******************************************************************************
 * Rv3G324mCallDrop
 * ----------------------------------------------------------------------------
 * General: Drops a call object.
 *          This function should be called if Rv3G324mCallOpen() was called
 *          on the given call object, when the application wants to disconnect
 *          a call. Upon successful return from this function, the application is
 *          guaranteed to receive Rv3G324mCallStateIdle state for the call and
 *          it should destruct the call only after receiving that state.
 *
 * Return Value: RV_OK if successful, or another value on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle to drop.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallDrop(
    IN  HCALL                   h3G324mCall);


/******************************************************************************
 * Rv3G324mCallDisconnected
 * ----------------------------------------------------------------------------
 * General: Indicates that a call was disconnected in an ungraceful manner.
 * This function should be called when the network was disconnected without 
 * any explicit request to drop the call using the H.245 End Session Command.
 * Upon successful return from this function, the application will receive 
 * the Rv3G324mCallStateIdle state for the call, and the application should 
 * destruct the call only after receiving this state.
 *
 * Return Value: RV_OK if successful, or another value on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle that was disconnected.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallDisconnected(
    IN  HCALL                   h3G324mCall);


/******************************************************************************
 * Rv3G324mCallSendMultiplexEntryTable
 * ----------------------------------------------------------------------------
 * General: Generates and sends all the entries from the Multiplex Entry Table 
 * used by H.223 and sends an H.245 MultiplexEntrySend (MES) message to the 
 * remote side of the call. 
 * The application should call this function after all outgoing
 * channels have been opened and every time it wants to update the table
 * due to changes in its outgoing channels.
 *
 * Return Value: RV_OK if successful, or another value on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall  - The call handle.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallSendMultiplexEntryTable(
    IN  HCALL                   h3G324mCall);


/******************************************************************************
 * Rv3G324mCallClearMultiplexEntryTable
 * ----------------------------------------------------------------------------
 * General: Clears the current Multiplex Entry Table. Alternatively, this 
 * function can generate the default table again. After this function is called, 
 * the application is responsible for generating the table manually through 
 * calls to Rv3G324mCallAddMultiplexEntry().
 *
 * Return Value: RV_OK if successful, or another value on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle.
 *         bGenerateDefault - RV_TRUE to generate the default table after 
 *                            clearing it. RV_FALSE to leave the table cleared.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallClearMultiplexEntryTable(
    IN  HCALL                   h3G324mCall,
    IN  RvBool                  bGenerateDefault);


/******************************************************************************
 * Rv3G324mCallAddMultiplexEntry
 * ----------------------------------------------------------------------------
 * General: Manually adds a new multiplex entry to the Multiplex Entry Table. 
 * The size of video and data channels may be between 0-15. These values are 
 * taken as ratios of these channels. Only two of the audio and video channels 
 * may have a value other than 0.
 *
 * Return Value: RV_OK if successful, or another value on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall  - The call handle.
 *         audioSize    - Size of the audio frame in this entry (in bytes). 
 *                        This size should not include adaptation layer overhead 
 *                        (the overhead may include header and CRC information 
 *                        and is automatically added by the call to this function).
 *         video1Size   - Size of the primary video to multiplex in this entry, 
 *                        or 0 if none. For an entry with more than one 
 *                        segmentable entry this should be small enough to 
 *                        serve as ratio (0-15).
 *         video2Size   - Size of the secondary video to multiplex in this entry, 
 *                        or 0 if none. For an entry with more than one segmentable 
 *                        entry this should be small enough to serve as ratio (0-15).
 *         dataSize     - Size of data to multiplex in this entry, or 0 if none. 
 *                        For an entry with more than one segmentable entry this 
 *                        should be small enough to serve as ratio (0-15).
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallAddMultiplexEntry(
    IN  HCALL                   h3G324mCall,
    IN  RvUint32                audioSize,
    IN  RvUint32                video1Size,
    IN  RvUint32                video2Size,
    IN  RvUint32                dataSize);


/******************************************************************************
 * Rv3G324mCallGetState
 * ----------------------------------------------------------------------------
 * General: Returns the current state of the call.
 *
 * Return Value: RV_OK if successful, or another value on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle.
 * Output: callState        - The current state of the call.
 *         callStateMode    - The current state mode of the call.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallGetState(
    IN  HCALL                   h3G324mCall,
    OUT Rv3G324mCallState      *callState,
    OUT Rv3G324mCallStateMode  *callStateMode);


/******************************************************************************
 * Rv3G324mCallGetStatistics
 * ----------------------------------------------------------------------------
 * General: Gets statistical information for the call. This function can be 
 * used only if RV_H223_USE_STATISTICS is configured to RV_YES in rvusrconfig.h.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle to use.
 *         statsSize        - Size of the statistics structure passed.
 * Output: pStats           - Statistics structure to fill in.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallGetStatistics(
    IN  HCALL                   h3G324mCall,
    IN  RvSize_t                statsSize,
    OUT Rv3G324mCallStatistics  *pStats);


/******************************************************************************
 * Rv3G324mCallSetEvHandlers
 * ----------------------------------------------------------------------------
 * General: Sets the callbacks for the calls handled by this Stack instance.
 *
 * Return Value: RV_OK if successful, or another value on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324m          - The Stack instance to use.
 *         callEvent        - The callback functions to set.
 *         size             - Set this parameter to sizeof (Rv3G324mCallEvHandlers).
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallSetEvHandlers(
    IN  HAPP                    h3G324m,
    IN  Rv3G324mCallEvHandlers *callEvent,
    IN  RvSize_t                size);


/******************************************************************************
 * Rv3G324mCallSendMessage
 * ----------------------------------------------------------------------------
 * General: Sends an H.245 message. The application should build the message 
 * node ID with the PVT-PST API and delete it after the call to the function. 
 *
 * Return Value: RV_OK if successful, or other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle.
 *         nodeId           - The node ID that holds the message to be sent.
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus Rv3G324mCallSendMessage(
    IN  HCALL        h3G324mCall,
    IN  RvPvtNodeId  nodeId);


/******************************************************************************
 * Rv3G324mCallSetParam
 * ----------------------------------------------------------------------------
 * General: Obtains a specific call parameter from the application.
 *          This function should be called after the call to Rv3G324mCallConstruct() 
 *          and before the call to Rv3G324mCallOpen(). 
 *          See also Rv3G324mCallParam, Rv3G324mCallGetParam.
 *
 * Return Value: RV_OK if successful, or other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle to open.
 *         eParam           - The parameter to be changed. 
 *                            The parameters are defined in Rv3G324mCallParam 
 *                            enumeration.
 *         value            - If the parameter value is a simple integer value, 
 *                            this is the value itself.
 *         strValue         - If the parameter value is a string, strValue 
 *                            represents the parameter value.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallSetParam(
    IN  HCALL                   h3G324mCall,
    IN  Rv3G324mCallParam       eParam,
    IN  RvInt32                 value,
    IN  const RvUint8           *strValue);


/******************************************************************************
 * Rv3G324mCallGetParam
 * ----------------------------------------------------------------------------
 * General: Gets a specific call parameter for the application.
 * See also Rv3G324mCallParam, Rv3G324mCallSetParam.
 *
 * Return Value: RV_OK if successful, or other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall - The call handle to open.
 *         eParam      - The parameter requested. The list of parameters is 
 *                       defined in Rv3G324mCallParam enumeration.
 * Output: value       - If the parameter value is a simple integer, this is 
 *                       the pointer to the parameter value.
 *         strValue    - If the parameter value is a string, strValue 
 *                       represents the parameter itself.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallGetParam(
    IN  HCALL                   h3G324mCall,
    IN  Rv3G324mCallParam       eParam,
    OUT RvInt32                 *value,
    OUT RvUint8                 *strValue);


/******************************************************************************
 * Rv3G324mCallReset
 * ----------------------------------------------------------------------------
 * General: Resets a call object.
 * This function should be called when the application wants to disconnect the 
 * call and start it again but without disconnecting the physical connection. 
 * The function generates the H.245 EndSessionCommand message with the 
 * gstnOptions.v34H324 field. If the remote side chooses to do the same, the 
 * call will be reset and move back to phase D in the H.324 Recommendation.
 * If the application received H.245 EndSessionCommand message from the
 * remote side with the isdnOption called telephonyMode, the callback
 * Rv3G324mCallReceivedResetRequestEv will be invoked. In this callback
 * the application can call this function to send an H.245 EndSessionCommand 
 * message of its own.
 *
 * Return Value: RV_OK if successful, or another value on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle to drop.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallReset(
    IN  HCALL                   h3G324mCall);

/******************************************************************************
 * Rv3G324mCallSetMaxH223MuxPduSize
 * ----------------------------------------------------------------------------
 * General: Builds and sends the maxH223MUXPDUsize miscellaneous command message
 *          to force the remote side to restrict the MUX-PDU payload size.
 *          This function must be called after the call to Rv3G324mCallConstruct().
 *
 *          For multiplex level 2, the maxMuxPduPayloadSize must be no more than
 *          254. If it is higher, then the call will use 254. For other multiplex
 *          levels, this value should not exceed 65535.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall   - The call handle.
 *         maxMuxPduSize - The maximum MUX-PDU payload size.
 * Output: none
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallSendMaxH223MuxPduSize(
    IN  HCALL                    h3G324mCall,
    IN  RvUint16                 maxMuxPduSize);


/******************************************************************************
 * Rv3G324mCallSendVendorIdentification
 * ----------------------------------------------------------------------------
 * General: Builds and sends the vendorIdentification indication message to 
 * inform the remote side about the vendor identity of the terminal.
 * 
 * Arguments:
 * Input:  h3G324mCall         - The call handle.
 *         nonStandardId       - The non-standard identifier object.
 *         productNumber       - The product number value.
 *         productNumberSize   - The product number size.
 *         versionNumber       - The version number value.
 *         versionNumberSize   - The version number size.
 * Output: None.
 *
 * Return Value: RV_OK if successful. Other on failure.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallSendVendorIdentification(
    IN  HCALL                    h3G324mCall,
    IN  cmNonStandardIdentifier  *nonStandardId,
    IN  RvUint8                  *productNumber,
    IN  RvUint16                 productNumberSize,
    IN  RvUint8                  *versionNumber,
    IN  RvUint16                 versionNumberSize);

/******************************************************************************
 * Rv3G324mCallMONASetMPCChannels
 * ----------------------------------------------------------------------------
 * General: This API function is used to set the MPC receiving/transmitting 
 * channels. This function should be called for the receiving and transmitting 
 * MPC channels after the first preference message has been received along with 
 * a decision on which MPC channels have been established.
 *
 * Arguments:
 * Input:  h3G324mCall               - The call handle.
 *         supportedRxMPCChannels    - The bitMask supported receiving MPC channels.
 *         supportedTxMPCChannels    - The bitMask supported transmitting MPC channels.
 
 * Output: supporteRxMPCChannels     - The bitMask of actual receiving MPC channels.
 *         supporteTxMPCChannels     - The bitMask of actual transmitting MPC channels.
 *
 * Return Value: RV_OK if successful. Other values on failure.
 *****************************************************************************/
 RVAPI RvStatus RVCALLCONV Rv3G324mCallMONASetMPCChannels(
    IN      HCALL       h3G324mCall,
    INOUT  	RvUint16	*supportedRxMPCChannels,
    INOUT	RvUint16	*supportedTxMPCChannels);

/******************************************************************************
 * Rv3G324mCallMONARemoveMPCChannel
 * ----------------------------------------------------------------------------
 * General: This function is used to remove an MPC channel that was replaced 
 * by an H.245 logical channel. This function should be called with bIsoutgoing 
 * == RV_FALSE after receiving an OLC for an incoming channel or with bIsoutgoing 
 * == RV_TRUE after receiving an ack for an outgoing OLC. This function should 
 * be called when an incoming OLC replaces an existing MPC channel.
 *
 * Arguments:
 * Input:  h3G324mCall              - The call handle.
 *         mpcChannelType           - The MPC type (lcn) of the channel to be removed.
 *         bIsoutgoing              - RV_TRUE for removing the transmitting MPC channel.
 *
 * Output: None.
 *
 * Return Value: RV_OK if successful. Other values on failure.
 *****************************************************************************/
 RVAPI RvStatus RVCALLCONV Rv3G324mCallMONARemoveMPCChannel(
    IN  HCALL                   h3G324mCall,
    IN  Rv3G324mCallMonaMPCType mpcChannelType,
    IN  RvBool                  bIsoutgoing);

/*@**************************************************************************
 * Rv3G324mCallMONAStopSendPreferenceMsg (Annex K)
 * ----------------------------------------------------------------------------
 * General: 
 *	This API is used to manualy stop sending MONA preference messages before 
 *	MONA ack status is 2 (in which case the muxer stops sending PMs 
 *	automatically).
 *	This API should be called when the TCS is received and the MONA ack status
 *	is 1 or greater. This function will fail if it is called when less than the 
 *	minimal number of MONA preference messages were sent, in which case the application 
 *	should call it again after the minimal number of MONA preference messages were sent
 *	(in Rv3G324mMonaPreferenceSendEv with lastMessage = 0).
 *	
 * Arguments:
 *
 * Input:  
 *	h3G324mCall         - The call handle.
 *
 * Output: 		      None.
 *
 * Return Value: 
 *			      RV_OK if successful. 
 *			      Negative values on failure.
 ***************************************************************************@*/
 RVAPI	RvStatus RVCALLCONV Rv3G324mCallMONAStopSendPreferenceMsg(
    IN  HCALL                   h3G324mCall);


#ifdef __cplusplus
}
#endif

#endif /* _RV_3G324M_CALL_H_ */
