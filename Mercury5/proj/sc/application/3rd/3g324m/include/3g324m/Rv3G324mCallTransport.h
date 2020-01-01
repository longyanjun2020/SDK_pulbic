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

#ifndef _RV_3G324M_CALL_TRANSPORT_H_
#define _RV_3G324M_CALL_TRANSPORT_H_


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
 * Rv3G324mCallSend
 * ----------------------------------------------------------------------------
  * General: Sends a message for this call object.
 *          The application should supply a buffer to be filled with the MUX-PDU
 *          data that is going to be sent.
 *
 *          Note that according to 3GPP documentation, the stream that is
 *          transmitted between 3G terminals is bit oriented and not byte
 *          oriented. The LSB is always transmitted first. This means that when
 *          a call is made between 3G terminal and ISDN terminal, it is the
 *          responsibility of the application of the ISDN terminal to make sure
 *          that the ISDN protocol stack converts the byte stream to a bit stream
 *          correctly.
 * 
 * Return Value: RV_OK if successful, or another value on failure.
 * See Also:Rv3G324mCallReceive, Rv3G324mProcessEvents
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle.
 *         pSize            - The buffer size that can be handled. 
 * Output: pBuffer          - The buffer to be filled with the MUX-PDU data. 
 *                            It is the responsibility of the user to allocate 
 *                            the buffer.
 *         pSize            - The function will update this parameter with the 
                              actual size filled.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallSend(
    IN    HCALL                 h3G324mCall,
    OUT   RvUint8               *pBuffer,
    INOUT RvUint32              *pSize);


/******************************************************************************
 * Rv3G324mCallReceive
 * ----------------------------------------------------------------------------
 * General: Receives data for this call object and passes it to the H.223 layer
 *          for demuxing the data.
 *
 *          Note that according to 3GPP documentation, the stream that is
 *          transmitted between 3G terminals is bit oriented and not byte
 *          oriented. The LSB is always transmitted first. This means that when
 *          making a call between 3G terminal and ISDN terminal, it is the
 *          responsibility of the application of the ISDN terminal to make sure
 *          that the ISDN protocol stack converts the bit stream to a byte stream
 *          correctly.
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * See Also:Rv3G324mCallSend, Rv3G324mProcessEvents, Rv3G324mCallReceiveMuxPdu
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle.
 *         pBuffer          - The buffer with the data that was received.
 *         size             - The size of the data that was received.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallReceive(
    IN  HCALL                   h3G324mCall,
    IN  RvUint8                 *pBuffer,
    IN  RvUint32                size);


/******************************************************************************
 * Rv3G324mCallReceiveMuxPdu
 * ----------------------------------------------------------------------------
 * General: Receives a single MUX-PDU for this call object and passes it to the
 *          H.223 layer for demuxing.
 *          This function should be used instead of Rv3G324mCallReceive() when
 *          the modem used is responsible for the framing and stuffing done in
 *          the call.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * See Also: Rv3G324mCallSend, Rv3G324mProcessEvents, Rv3G324mCallReceive
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall                  - The call handle.
 *         pBuffer                      - The buffer with the data that was 
 *                                        received. Should contain a full 
 *                                        MUX-PDU frame, including the header
 *                                        and without any synchronization flags.
 *         size                         - The size of the data that was received.
 *         bSegmentableChannelClosure   - RV_TRUE if the received MUX-PDU frame 
 *                                        closes a segmentable channel. This 
 *                                        parameter must be set to RV_FALSE for 
 *                                        mux-level 0 and mux-level 1 at all times 
 *                                        since this information resides within 
 *                                        the header of the MUX-PDU itself.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallReceiveMuxPdu(
    IN  HCALL                   h3G324mCall,
    IN  RvUint8                 *pBuffer,
    IN  RvUint32                size,
    IN  RvBool                  bSegmentableChannelClosure);


/******************************************************************************
 * Rv3G324mCallLogicalChannelSendData
 * ----------------------------------------------------------------------------
 * General: This function is used for setting the channel data to
 *          prepare MUX-PDUs for sending.
 *
 *          If pBuffer==NULL and size==0, this function will not send anything 
 *          but will check whether any retransmissions should be handled for 
 *          this channel. This function should be called in this way when a 
 *          bidirectional channel exists on which data is not always sent (e.g., 
 *          if data is only being received or if received data is being looped 
 *          back). 
 *
 * Return Value: RV_OK if successful, or another value on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle.
 *         h3G324mChannel   - The channel handle.
 *         pBuffer          - The data buffer that is about to be sent. 
 *                            The application should not deallocate or 
 *                            reuse this buffer until 
 *                            Rv3G324mCallLogicalChannelReleaseSendBufferEv() 
 *                            is received on it.
 *         size             - The size of the data buffer.
 * Output: none.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallLogicalChannelSendData(
    IN  HCALL                   h3G324mCall,
    IN  HCHAN                   h3G324mChannel,
    IN  RvUint8                 *pBuffer,
    IN  RvUint16                size);


/******************************************************************************
 * Rv3G324mCallLogicalChannelSendDataExt
 * ----------------------------------------------------------------------------
 * General: This function is used for setting the channel data to
 *          prepare MUX-PDUs for sending. This function acts the same way as
 *          Rv3G324mCallLogicalChannelSendData(), but returns an additional
 *          parameter that indicates how many data buffers are pending in the
 *          multiplexer send queue for the given logical channel. This
 *          allows the application to manage the flow control and transmission
 *          rate of the channel.
 *
 *          If pBuffer==NULL and size==0, then this function will not send
 *          anything, but will check if any retransmissions needs to be handled
 *          for this channel. The function should be called in this way
 *          in case of a bidirectional channel on which data is not always sent
 *          (e.g. if data is received only, or if received data is looped back).
 *
 * Return Value: RV_OK if successful, or another value on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle.
 *         h3G324mChannel   - The channel handle.
 *         pBuffer          - The data buffer that is about to be sent.
 *         size             - The size of the data buffer.
 * Output: pendingData      - The number of pending data buffers on the
 *                            logical channel (including this one) that are
 *                            waiting to be sent by the multiplexer.
 *                            This parameter cannot be set to NULL.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallLogicalChannelSendDataExt(
    IN  HCALL                   h3G324mCall,
    IN  HCHAN                   h3G324mChannel,
    IN  RvUint8                 *pBuffer,
    IN  RvUint16                size,
    OUT RvUint16                *pendingData);

/******************************************************************************
 * Rv3G324mCallLogicalChannelClear
 * ----------------------------------------------------------------------------
 * General: This function clears the internal channel queues from any pending 
 * data that was not yet multiplexed after calls to 
 * Rv3G324mCallLogicalChannelSendData() or Rv3G324mCallLogicalChannelSendDataExt(). 
 * It can be used to clear up any media being sent in order to start a new 
 * stream of data from a different given source when developing a media server.
 *
 * Return Value: RV_OK if successful, or another value on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle.
 *         h3G324mChannel   - The channel handle.
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallLogicalChannelClear(
    IN  HCALL                   h3G324mCall,
    IN  HCHAN                   h3G324mChannel);

#if (RV_3G324M_USE_MONA == RV_YES)
/******************************************************************************
 * Rv3G324mCallMonaMPCChannelSendData
 * ----------------------------------------------------------------------------
 * General: This function is used to set MPC channel data to prepare MUX-PDUs 
 * for sending. If pBuffer==NULL and size==0, this function will not send anything.
 *
 * Return Value: RV_OK if successful. Other values on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  h3G324mCall      - The call handle.
 *         mpcChannel       - The MPC channel.
 *         pBuffer          - The data buffer that is about to be sent.
 *         size             - The size of the data buffer.
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV Rv3G324mCallMonaMPCChannelSendData(
    IN  HCALL                       h3G324mCall,
    IN  Rv3G324mCallMonaMPCType     mpcChannel,
    IN  RvUint8                    *pBuffer,
    IN  RvUint16                    size);
#endif /* USE_MONA */
#ifdef __cplusplus
}
#endif

#endif /* _RV_3G324M_CALL_H_ */
