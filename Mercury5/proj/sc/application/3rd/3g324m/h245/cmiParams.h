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

#ifndef _RV_CMI_PARAMS_H
#define _RV_CMI_PARAMS_H

#include "cmH245Object.h"
/*#include "cmCall.h"*/

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{

/************************************************************************
 * startEstablishment
 * purpose: Start establishing a channel. This function adds h25X parameters into
 *          an OLC message from the channel element.
 * input  : hVal          - handle to the PVT root.
 *          olcID         - node id for the open logical channel.
 *          forwardLCP_ID - node id for the forward logical channel parameters.
 *          reverseLCP_ID - node id for the reverse logical channel parameters.
 *          dataType      - node id for the data type.
 *          pChannel      - Channel element to add h22X parameters OLC for.
 * output : none
 * return : none
 ************************************************************************/
void (*startEstablishment)(
          IN HPVT        hVal,
          IN RvPvtNodeId olcID,
          IN RvPvtNodeId forwardLCP_ID,
          IN RvPvtNodeId reverseLCP_ID,
          IN RvPvtNodeId dataType,
          IN H245Channel *pChannel);


/************************************************************************
 * cmcCallAddressCallbacks
 * purpose: Call the callbacks of the h22X addresses.
 * input  : pApp            - application handle for the cm.
 *          pChannel        - Channel element to set h22X parameters for.
 *          h22XParamNodeId - node id for the h22X parameters.
 * output : none
 * return : none
 ************************************************************************/
int (*cmcCallAddressCallbacks)(
    IN H245Object*  pApp,
    IN H245Channel* pChannel,
    IN RvPvtNodeId  h22XParamNodeId);

 /************************************************************************
 * openLogicalChannelEvent
 * purpose: Open logical channel event.
 * input  : pApp            - application handle for the cm.
 *          hVal            - handle for the PVT.
 *          forwardLCP_ID   - node id for the forward open logical channel parameters.
 *          reverseLCP_ID   - node id for the reverse data type.
 *          message         - node id for the message.
 *          pChannel        - Channel element to set h22X parameters for.
 * output : h22XID          - the node id of the h22X parameters.
 *          bIsReturn       - if true then there was a return value, otherwise there wasn't.
 * return : int
 ************************************************************************/
int (*openLogicalChannelEvent)(
    IN H245Object    *pApp,
    IN HPVT          hVal,
    IN RvPvtNodeId   forwardLCP_ID,
    IN RvPvtNodeId   reverseLCP_ID,
    IN RvPvtNodeId   message,
    IN H245Channel   *pChannel,
    OUT RvPvtNodeId  *h22XID,
    OUT RvBool       *bIsReturn);

/************************************************************************
 * dynamicRTPPayloadType
 * purpose: Dynamic RTP payload type event.
 * input  : pApp            - application handle for the cm.
 *          hVal            - handle for the PVT root.
 *          h22XID          - node id for the h22X parameters.
 *          pChannel        - Channel element to set h22X parameters for.
 * output : none
 * return : none
 ************************************************************************/
void (*dynamicRTPPayloadType)(
    IN H245Object*  pApp,
    IN HPVT         hVal,
    IN RvPvtNodeId  h22XID,
    IN H245Channel* pChannel);


/************************************************************************
 * maximumSkewIndication
 * purpose: notifing the application on the maximumSkew for a channel.
 * input  : ctrl    - the h245 control object of the call.
 *          message - incoming h22X0MaximumSkewIndication message.
 * output : none
 * return : int - negative number will be error.
 *                positive number will be success.
 ************************************************************************/
int (*maximumSkewIndication)(H245Control* ctrl,RvPvtNodeId message);


/************************************************************************
 * communicationModeCommand
 * purpose: getting h22x parameters from communicationModeCommand message.
 * input  : pCtrl    - the H245 control object.
 *          message  - the communicationModeCommand message node id.
 * output : none
 * return : int - negative number will be error.
 *                positive number will be success.
 ************************************************************************/
int (*communicationModeCommand)(H245Control* pCtrl, RvPvtNodeId message);

/************************************************************************
 * allocateChannel
 * purpose: initiating h22x parameters while allocating the channel.
 * input  : pChannel - the channel object.
 * output : none
 * return : none
 ************************************************************************/
void (*allocateChannel)(H245Channel* pChannel);

/************************************************************************
 * channelFreeMemory
 * purpose: freeing h22x parameters while freeing the channel.
 * input  : pChannel - the channel object.
 *          hVal     - handle to the PVT.
 * output : none
 * return : none
 ************************************************************************/
void (*channelFreeMemory)(H245Channel* pChannel, HPVT hVal);


/************************************************************************
 * channelAnswer
 * purpose: Build OpenLogicalChannelAck message.
 * input  : hVal          - handle to the PVT.
 *          pChannel      - Channel element to add h225/h223 parameters OLC for.
 *          pCtrl         - Control element.
 *          olcID         - node id for the open logical channel.
 * output : none
 * return : RV_OK on success, other on failure
 ************************************************************************/
RvStatus (*channelAnswer)(
                 IN HPVT        hVal,
                 IN H245Channel *pChannel,
                 IN H245Control *pCtrl,
                 IN RvPvtNodeId olcaID);

/************************************************************************
 * openLogicalChannelAck
 * purpose: handle received OpenLogicalChannelAck message.
 * input  : pApp          - application handle for the cm element.
 *          hVal          - handle to the PVT.
 *          pChannel      - Channel element.
 *          pCtrl         - Control element.
 *          message       - node id for the OpenLogicalChannelAck message.
 * output : none
 * return : none
 ************************************************************************/
void (*openLogicalChannelAck)(
                 IN H245Object  *pApp,
                 IN HPVT        hVal,
                 IN H245Channel *pChannel,
                 IN H245Control *pCtrl,
                 IN RvPvtNodeId message);

/************************************************************************
 * openLogicalChannelReject
 * purpose: handle received OpenLogicalChannelReject message.
 * input  : pApp          - application handle for the cm element.
 *          pChannel      - Channel element.
 *          pCtrl         - Control element.
 *          message       - node id for the OpenLogicalChannelAck message.
 *          rejectReason  - Reject reason received on an outgoing channel.
 *          stateMode     - state of channel
 * output : none
 * return : none
 ************************************************************************/
void (*openLogicalChannelReject)(
                 IN H245Object              *pApp,
                 IN H245Channel             *pChannel,
                 IN H245Control             *pCtrl,
                 IN RvPvtNodeId             message,
                 IN cmRejectLcnReason       rejectReason,
                 OUT cmChannelStateMode_e   *stateMode);

/************************************************************************
 * openLogicalChannelConfirm
 * purpose: handling OpenLogicalChannelConfirm message.
 * input  : hVal          - handle to the PVT.
 *          pChannel      - Channel element.
 *          message       - node id for the OpenLogicalChannelAck message.
 * output : none
 * return : none
 ************************************************************************/
void (*openLogicalChannelConfirm)(
                 IN HPVT        hVal,
                 IN H245Channel *pChannel,
                 IN RvPvtNodeId message);

/************************************************************************
 * ChannelOpenDynamic
 * purpose: Sets the data type.
 * input  : pChannel    - Channel element to set h223 parameters for.
 *          hVal        - PVT handle.
 *          dataTypeId  - Data type node id.
 * output : none
 * return : none
 ************************************************************************/
void (*ChannelOpenDynamic)(H245Channel *pChannel, HPVT hVal, RvPvtNodeId dataTypeId);


/************************************************************************
 * CallChannelParametersCallback
 * purpose: Gets same session and associated channel handles.
 * input  : hsChan        - The channel handle.
 * output : hsAssociatedH - The associated channel handle.
 *          haAssociatedH - The associated application channel handle.
 *          hsAssociatedH - The same channel handle.
 *          hsAssociatedH - The same application channel handle.
 * return : none
 ************************************************************************/
void (*CallChannelParametersCallback)(HCHAN    hsChan,
                                      HCHAN    *hsAssociatedH,
                                      HAPPCHAN *haAssociatedH,
                                      HCHAN    *hsSameSessionH,
                                      HAPPCHAN *haSameSessionH);

/************************************************************************
 * ChannelClose
 * purpose: Make sure the default used session Id's are updated if we close them.
 * input  : ctrl        - The control object.
 *          channel     - The channel object.
 * output : none.
 * return : none
 ************************************************************************/
void (*ChannelClose)(H245Control *ctrl, H245Channel *channel);

/******************************************************************************
 * ChannelReject
 * ----------------------------------------------------------------------------
 * General: Handles outgoing openLogicalChannelReject..
 *
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  ctrl                 - H245Control object of the call.
 *         channel              - rejected Channel.
 *         dropReason           - Reason for channel dropping.
 * Output: None.
 *****************************************************************************/
void (*ChannelReject)(H245Control *ctrl, H245Channel *channel);

/****************************************************************************************************************/
/* This function shall be called before the first channel is opened using the H.245 procedures.                 */
/* It is protected from the second call so it may be called each time the new channel is about to be established*/
/* The main purpose of the function is to mark well-known session IDs used by the fast start and                */
/* prevent in this way usage of them in H.245                                                                   */
/****************************************************************************************************************/
void (*DeriveChannels)(HCONTROL ctrl);

/************************************************************************
 * SessionOpenDynamic
 * purpose: Handle the same session and associated channels.
 * input  : channel             - The channel object.
 *          ctrlE               - The control object.
 *          hsChanSameSession   - The same session channel handle.
 *          hsChanAssociated    - The associated channel handle.
 * output : none.
 * return : none
 ************************************************************************/
void (*SessionOpenDynamic)(H245Channel *channel,
                           H245Control *ctrlE,
                           HCHAN       hsChanSameSession,
                           HCHAN       hsChanAssociated,
                           RvBool      isDynamicPayloadType);

/************************************************************************
 * MultiplexReconfiguration
 * purpose: Handle an incoming h223MultiplexReconfiguration message.
 * input  : ctrl    - Control object
 *          message - h223MultiplexReconfiguration message node
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int (*MultiplexReconfiguration)(IN H245Control* ctrl, IN int message);

/************************************************************************
 * EndSessionCommand
 * purpose: Handle an incoming endSessionCommand message.
 *          This should stop the control of the call.
 * input  : ctrl    - Control object
 *          message - endSessionCommand message received
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int (*EndSessionCommand)(IN H245Control* ctrl, IN int message);

}H22XFunctions;


#ifdef __cplusplus
}
#endif

#endif  /* _RV_CMI_PARAMS_H */
