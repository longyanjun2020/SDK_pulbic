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

#ifndef _RV_CM_H255_PARAMS_H
#define _RV_CM_H255_PARAMS_H

#include "h245.h"
#include "cmChanGet.h"
#include "cmchan.h"
#include "pvaltreeStackApi.h"
#include "cmH245Object.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "cmH245GeneralDefs.h"
#if (RV_H245_SUPPORT_H225_PARAMS == 1)

/************************************************************************
 * h225ParamsStartEstablishment
 * purpose: Start establishing a channel. This function adds h255 parameters into
 *          an OLC message from the channel element.
 * input  : hVal          - handle to the PVT root.
 *          olcID         - node id for the open logical channel.
 *          forwardLCP_ID - node id for the forward logical channel parameters.
 *          reverseLCP_ID - node id for the reverse logical channel parameters.
 *          dataType      - node id for the data type.
 *          pChannel      - Channel element to add h225 parameters OLC for.
 * output : none
 * return : none
 ************************************************************************/
void h225ParamsStartEstablishment(IN HPVT        hVal,
                                  IN RvPvtNodeId olcID,
                                  IN RvPvtNodeId forwardLCP_ID,
                                  IN RvPvtNodeId reverseLCP_ID,
                                  IN RvPvtNodeId dataType,
                                  IN H245Channel *pChannel);


/************************************************************************
 * h225cmcCallAddressCallbacks
 * purpose: Call the callbacks of the h225 addresses.
 * input  : pApp            - application handle for the cm.
 *          pChannel        - Channel element to set h225 parameters for.
 *          h225ParamNodeId - node id for the h225 parameters.
 * output : none
 * return : none
 ************************************************************************/
int h225cmcCallAddressCallbacks(
    IN H245Object*  pApp,
    IN H245Channel* pChannel,
    IN RvPvtNodeId  h225ParamNodeId);

 /************************************************************************
 * h225ParamsOpenLogicalChannelEvent
 * purpose: Open logical channel event.
 * input  : pApp            - application handle for the cm.
 *          hVal            - handle for the PVT.
 *          forwardLCP_ID   - node id for the forward open logical channel parameters.
 *          reverseLCP_ID   - node id for the reverse data type.
 *          message         - node id for the message.
 *          pChannel        - Channel element to set h225 parameters for.
 * output : h225ID          - the node id of the h225 parameters.
 *          bIsReturn       - if true then there was a return value, otherwise there wasn't.
 * return : int
 ************************************************************************/
int h225ParamsOpenLogicalChannelEvent(
    IN H245Object    *pApp,
    IN HPVT          hVal,
    IN RvPvtNodeId   forwardLCP_ID,
    IN RvPvtNodeId   reverseLCP_ID,
    IN RvPvtNodeId   message,
    IN H245Channel   *pChannel,
    OUT RvPvtNodeId  *h225ID,
    OUT RvBool       *bIsReturn);

/************************************************************************
 * h225ParamsDynamicRTPPayloadType
 * purpose: Dynamic RTP payload type event.
 * input  : pApp            - application handle for the cm.
 *          hVal            - handle for the PVT root.
 *          h225ID          - node id for the h225 parameters.
 *          pChannel        - Channel element to set h225 parameters for.
 * output : none
 * return : none
 ************************************************************************/
void h225ParamsDynamicRTPPayloadType(
    IN H245Object*  pApp,
    IN HPVT         hVal,
    IN RvPvtNodeId  h225ID,
    IN H245Channel* pChannel);


/************************************************************************
 * h2250MaximumSkewIndication
 * purpose: notifing the application on the maximumSkew for a channel.
 * input  : ctrl    - the h245 control object of the call.
 *          message - incoming h2250MaximumSkewIndication message.
 * output : none
 * return : int - negative number will be error.
 *                positive number will be success.
 ************************************************************************/
int h225MaximumSkewIndication(H245Control* ctrl,RvPvtNodeId message);

/************************************************************************
 * h225communicationModeCommand
 * purpose: getting h225 parameters from communicationModeCommand message.
 * input  : pCtrl    - the H245 control object.
 *          message  - the communicationModeCommand message node id.
 * output : none
 * return : int - negative number will be error.
 *                positive number will be success.
 ************************************************************************/
int h225communicationModeCommand(H245Control* pCtrl, RvPvtNodeId message);


/************************************************************************
 * h225AllocateChannel
 * purpose: initiating h225 parameters while allocating the channel.
 * input  : pChannel - the channel object.
 * output : none
 * return : none
 ************************************************************************/
void h225AllocateChannel(H245Channel* pChannel);


/************************************************************************
 * h225ChannelFreeMemory
 * purpose: freeing h225 parameters while freeing the channel.
 * input  : pChannel - the channel object.
 *          hVal     - handle to the PVT.
 * output : none
 * return : none
 ************************************************************************/
void h225ChannelFreeMemory(H245Channel* pChannel, HPVT hVal);


/************************************************************************
 * h255ParamsChannelAnswer
 * purpose: Start establishing a channel. This function adds h255 parameters into
 *          an OLC message from the channel element.
 * input  : hVal          - handle to the PVT.
 *          pChannel      - Channel element to add h225 parameters OLC for.
 *          pCtrl         - Control element.
 *          olcID         - node id for the open logical channel.
 * output : none
 * return : RV_OK on success, other on failure
 ************************************************************************/
RvStatus h255ParamsChannelAnswer(
    IN HPVT        hVal,
    IN H245Channel *pChannel,
    IN H245Control *pCtrl,
    IN RvPvtNodeId olcaID);

/************************************************************************
 * h255ParamsOpenLogicalChannelAck
 * purpose: handle received OpenLogicalChannelAck message.
 * input  : pApp          - application handle for the cm element.
 *          hVal          - handle to the PVT.
 *          pChannel      - Channel element.
 *          pCtrl         - Control element.
 *          message       - node id for the OpenLogicalChannelAck message.
 * output : none
 * return : none
 ************************************************************************/
void h255ParamsOpenLogicalChannelAck(IN H245Object  *pApp,
                                     IN HPVT        hVal,
                                     IN H245Channel *pChannel,
                                     IN H245Control *pCtrl,
                                     IN RvPvtNodeId message);

/************************************************************************
 * h255ParamsOpenLogicalChannelReject
 * purpose: handle received OpenLogicalChannelreject message.
 * input  : pApp          - application handle for the cm element.
 *          pChannel      - Channel element.
 *          pCtrl         - Control element.
 *          message       - node id for the OpenLogicalChannelAck message.
 *          rejectReason  - Reject reason received on an outgoing channel.
 * output : none
 * return : none
 ************************************************************************/
void h255ParamsOpenLogicalChannelReject(
    IN  H245Object              *pApp,
    IN  H245Channel             *pChannel,
    IN  H245Control             *pCtrl,
    IN  RvPvtNodeId             message,
    IN  cmRejectLcnReason       rejectReason,
    OUT cmChannelStateMode_e    *stateMode);

/************************************************************************
 * h255ParamsOpenLogicalChannelConfirm
 * purpose: handling OpenLogicalChannelConfirm message.
 * input  : hVal          - handle to the PVT.
 *          pChannel      - Channel element.
 *          message       - node id for the OpenLogicalChannelAck message.
 * output : none
 * return : none
 ************************************************************************/
void h255ParamsOpenLogicalChannelConfirm(IN HPVT        hVal,
                                         IN H245Channel *pChannel,
                                         IN RvPvtNodeId message);

/************************************************************************
 * h225ParamsChannelOpenDynamic
 * purpose: Sets the data type.
 * input  : pChannel    - Channel element to set h223 parameters for.
 *          hVal        - PVT handle.
 *          dataTypeId  - Data type node id.
 * output : none
 * return : none
 ************************************************************************/
void h225ParamsChannelOpenDynamic(H245Channel *pChannel, HPVT hVal, RvPvtNodeId dataTypeId);

/************************************************************************
 * h225ParamsCallChannelParametersCallback
 * purpose: Gets same session and associated channel handles.
 * input  : hsChan        - The channel handle.
 * output : hsAssociatedH - The associated channel handle.
 *          haAssociatedH - The associated application channel handle.
 *          hsAssociatedH - The same channel handle.
 *          hsAssociatedH - The same application channel handle.
 * return : none
 ************************************************************************/
void h225ParamsCallChannelParametersCallback(HCHAN    hsChan, 
                                             HCHAN    *hsAssociatedH,
                                             HAPPCHAN *haAssociatedH,
                                             HCHAN    *hsSameSessionH,
                                             HAPPCHAN *haSameSessionH);

/************************************************************************
 * h225ParamsChannelClose
 * purpose: Make sure the default used session Id's are updated if we close them.
 * input  : ctrl        - The control object.
 *          channel     - The channel object.
 * output : none.
 * return : none
 ************************************************************************/
void h225ParamsChannelClose(H245Control *ctrl, H245Channel *channel);

/******************************************************************************
 * h223ParamsChannelReject
 * ----------------------------------------------------------------------------
 * General: Handles outgoing openLogicalChannelReject. 
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  ctrl                 - H245Control object of the call.
 *         channel              - rejected Channel.
 * Output: None.
 *****************************************************************************/
void h225ParamsChannelReject(H245Control *ctrl, H245Channel *channel);

/****************************************************************************************************************/
/* This function shall be called before the first channel is opened using the H.245 procedures.                 */
/* It is protected from the second call so it may be called each time the new channel is about to be established*/
/* The main purpose of the function is to mark well-known session IDs used by the fast start and                */
/* prevent in this way usage of them in H.245                                                                   */
/****************************************************************************************************************/
void h225ParamsDeriveChannels(HCONTROL ctrl);

/************************************************************************
 * h225ParamsSessionOpenDynamic
 * purpose: Handle the same session and associated channels.
 * input  : channel             - The channel object.
 *          ctrlE               - The control object.
 *          hsChanSameSession   - The same session channel handle.
 *          hsChanAssociated    - The associated channel handle.
 * output : none.
 * return : none
 ************************************************************************/
void h225ParamsSessionOpenDynamic(H245Channel *channel,
                                  H245Control *ctrlE,
                                  HCHAN       hsChanSameSession,
                                  HCHAN       hsChanAssociated,
                                  RvBool      isDynamicPayloadType);

/************************************************************************
 * h225MultiplexReconfiguration
 * purpose: Handle an incoming h223MultiplexReconfiguration message.
 * input  : ctrl    - Control object
 *          message - h223MultiplexReconfiguration message node
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int h225MultiplexReconfiguration(IN H245Control* ctrl, IN int message);

/************************************************************************
 * h225EndSessionCommand
 * purpose: Handle an incoming endSessionCommand message.
 *          This should stop the control of the call.
 * input  : ctrl    - Control object
 *          message - endSessionCommand message received
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int h225EndSessionCommand(IN H245Control* ctrl, IN int message);


int cmChannelSetRtpTransportAddress(
                                    IN  HCHAN               hsChan,
                                    IN  cmTransportAddress* ta);
                                    
int cmChannelSetRtcpTransportAddress(
                                     IN  HCHAN               hsChan,
                                     IN  cmTransportAddress* ta);
                                     
#else

#define     h225ParamsStartEstablishment                     NULL
#define     h225cmcCallAddressCallbacks                      NULL
#define     h225ParamsOpenLogicalChannelEvent                NULL
#define     h225ParamsDynamicRTPPayloadType                  NULL
#define     h225MaximumSkewIndication                        NULL
#define     h225communicationModeCommand                     NULL
#define     h225AllocateChannel                              NULL
#define     h225ChannelFreeMemory                            NULL
#define     h255ParamsChannelAnswer                          NULL
#define     h255ParamsOpenLogicalChannelAck                  NULL
#define     h255ParamsOpenLogicalChannelReject               NULL
#define     h255ParamsOpenLogicalChannelConfirm              NULL
#define     h225ParamsChannelOpenDynamic                     NULL
#define     h225ParamsCallChannelParametersCallback          NULL
#define     h225ParamsChannelClose                           NULL
#define     h225ParamsChannelReject                          NULL
#define     h225ParamsDeriveChannels                         NULL
#define     h225ParamsSessionOpenDynamic                     NULL
#define     h225MultiplexReconfiguration                     NULL
#define     h225EndSessionCommand                            NULL

#endif /* RV_H245_SUPPORT_H225_PARAMS */

#ifdef __cplusplus
}
#endif

#endif  /* _RV_CM_H255_PARAMS_H */

