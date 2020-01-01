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

#ifndef _RV_CM_H223_PARAMS_H
#define _RV_CM_H223_PARAMS_H

#include "cmControl.h"
#include "h245.h"
#include "cmH245Object.h"
#include "cmChanGet.h"
#include "cmchan.h"
#include "pvaltreeStackApi.h"
#include "cmH245GeneralDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

#if (RV_H245_SUPPORT_H223_PARAMS == 1)

#if (RV_3G324M_USE_MONA == RV_YES)
/*Fast Media (MPC) media defintions*/
#define RV_H245_MPC_AMR_SUPPORTED        0x0002
#define RV_H245_MPC_AMR_WB_SUPPORTED     0x0004
#define RV_H245_MPC_H264_SUPPORTED       0x0008
#define RV_H245_MPC_MPEG4_SUPPORTED      0x0010
#define RV_H245_MPC_H263_SUPPORTED       0x0020
/*MPC media types*/
typedef enum
{
    RvH245MonaMPCChannelTypeUNKNOWN = 0,
    RvH245MonaMPCChannelTypeAMR,
    RvH245MonaMPCChannelTypeAMR_WB,
    RvH245MonaMPCChannelTypeH264,
    RvH245MonaMPCChannelTypeMPEG4,
    RvH245MonaMPCChannelTypeH263,
    RvH245MonaMPCChannelTypeLAST
} RvH245MonaMPCChannelType;
#endif /* USE_MONA */
/******************************************************************************
 * H223getVideoChannelRole
 * ----------------------------------------------------------------------------
 * General: calls the cmEvChannelSetRole event.
 *
 * Return Value: 0 for the primary video channel, 1 for the secondary video channel,
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  pChannel      - The channel object.
 *         app      -      The H245 object.
 * Output: none.
 *****************************************************************************/
RvUint16 H223getVideoChannelRole(IN H245Channel   *pChannel,
                                 IN RvPvtNodeId   dataTypeNode,
                                 IN H245Object    *app);

/************************************************************************
 * h223cmcCallAddressCallbacks
 * purpose: Call the callbacks of the h223 parameters.
 * input  : pApp            - application handle for the cm.
 *          pChannel        - Channel element to set h225 parameters for.
 *          h223ParamNodeId - node id for the h225 parameters.
 * output : none
 * return : none
 * NOTE: origin should be the origin of the MESSAGE - as the recerive and transmit address assosiation is
 * determined by the EP to send the message.
 ************************************************************************/
int h223cmcCallAddressCallbacks(
    IN H245Object*  pApp,
    IN H245Channel* pChannel,
    IN RvPvtNodeId  h223ParamNodeId);

/************************************************************************
 * h223ParamsOpenLogicalChannelEvent
 * purpose: Open logical channel event.
 * input  : app            - application handle for the cm.
 *          hVal            - handle for the PVT.
 *          forwardLCP_ID   - node id for the forward open logical channel parameters.
 *          reverseLCDataType_ID    - node id for the reverse data type.
 *          message         - node id for the message.
 *          pChannel        - Channel element to set h223 parameters for.
 * output : h223ID          - the node id of the h223 parameters.
 *          bIsReturn       - if true then there was a return value, otherwise there wasn't.
 * return : int
 ************************************************************************/
int h223ParamsOpenLogicalChannelEvent(
    IN H245Object    *app,
    IN HPVT          hVal,
    IN RvPvtNodeId   forwardLCP_ID,
    IN RvPvtNodeId   reverseLCDataType_ID,
    IN RvPvtNodeId   message,
    IN H245Channel   *pChannel,
    OUT RvPvtNodeId  *h223ID,
    OUT RvBool       *bIsReturn);

/************************************************************************
 * h223ParamsStartEstablishment
 * purpose: Start establishing a channel. This function adds h255 parameters into
 *          an OLC message from the channel element.
 * input  : hVal          - handle to the PVT.
 *          olcID         - node id for the open logical channel.
 *          forwardLCP_ID - node id for the forward logical channel parameters.
 *          reverseLCP_ID - node id for the reverse logical channel parameters.
 *          dataType      - node id for the data type.
 *          pChannel      - Channel element to add h225 parameters OLC for.
 * output : none
 * return : none
 ************************************************************************/
void h223ParamsStartEstablishment(IN HPVT        hVal,
                                  IN RvPvtNodeId olcID,
                                  IN RvPvtNodeId forwardLCP_ID,
                                  IN RvPvtNodeId reverseLCP_ID,
                                  IN RvPvtNodeId dataType,
                                  IN H245Channel *pChannel);

/************************************************************************
 * h223AllocateChannel
 * purpose: initiating h223 parameters while allocating the channel.
 * input  : pChannel - the channel object.
 * output : none
 * return : none
 ************************************************************************/
void h223AllocateChannel(H245Channel* pChannel);

/************************************************************************
 * h223ChannelFreeMemory
 * purpose: freeing h223 parameters while freeing the channel.
 * input  : pChannel - the channel object.
 *          hVal     - handle to the PVT.
 * output : none
 * return : none
 ************************************************************************/
void h223ChannelFreeMemory(H245Channel* pChannel, HPVT hVal);

/************************************************************************
 * h223ParamsOpenLogicalChannelAck
 * purpose: handle received OpenLogicalChannelAck message.
 * input  : pApp          - application handle for the cm element.
 *          hVal          - handle to the PVT.
 *          pChannel      - Channel element.
 *          pCtrl         - Control element.
 *          message       - node id for the OpenLogicalChannelAck message.
 * output : none
 * return : none
 ************************************************************************/
void h223ParamsOpenLogicalChannelAck(IN H245Object  *pApp,
                                     IN HPVT        hVal,
                                     IN H245Channel *pChannel,
                                     IN H245Control *pCtrl,
                                     IN RvPvtNodeId message);

/************************************************************************
 * h223ParamsOpenLogicalChannelreject
 * purpose: handle received OpenLogicalChannelreject message.
 * input  : pApp          - application handle for the cm element.
 *          pChannel      - Channel element.
 *          pCtrl         - Control element.
 *          message       - node id for the OpenLogicalChannelAck message.
 *          rejectReason  - Reject reason received on an outgoing channel.
 * output : none
 * return : none
 ************************************************************************/
void h223ParamsOpenLogicalChannelReject(
    IN  H245Object              *pApp,
    IN  H245Channel             *pChannel,
    IN  H245Control             *pCtrl,
    IN  RvPvtNodeId             message,
    IN  cmRejectLcnReason       rejectReason,
    OUT cmChannelStateMode_e    *stateMode);

/************************************************************************
 * h223ParamsChannelAnswer
 * purpose: Build OpenLogicalChannelAck message.
 * input  : hVal          - handle to the PVT.
 *          pChannel      - Channel element to add h225 parameters OLC for.
 *          pCtrl         - Control element.
 *          olcID         - node id for the open logical channel.
 * output : none
 * return : RV_OK on success, other on failure
 ************************************************************************/
RvStatus h223ParamsChannelAnswer(
    IN HPVT        hVal,
    IN H245Channel *pChannel,
    IN H245Control *pCtrl,
    IN RvPvtNodeId olcaID);

/************************************************************************
 * h223ParamsOpenLogicalChannelConfirm
 * purpose: handling OpenLogicalChannelConfirm message.
 * input  : hVal          - handle to the PVT.
 *          pChannel      - Channel element.
 *          message       - node id for the OpenLogicalChannelAck message.
 * output : none
 * return : none
 ************************************************************************/
void h223ParamsOpenLogicalChannelConfirm(IN HPVT        hVal,
                                         IN H245Channel *pChannel,
                                         IN RvPvtNodeId message);

/************************************************************************
 * h223MaximumSkewIndication
 * purpose: notifing the application on the maximumSkew for a channel.
 * input  : ctrl    - the h245 control object of the call.
 *          message - incoming h2250MaximumSkewIndication message.
 * output : none
 * return : int - negative number will be error.
 *                positive number will be success.
 ************************************************************************/
int h223MaximumSkewIndication(H245Control* ctrl,RvPvtNodeId message);

/************************************************************************
 * h223communicationModeCommand
 * purpose: getting h223 parameters from communicationModeCommand message.
 * input  : pCtrl    - the H245 control object.
 *          message  - the communicationModeCommand message node id.
 * output : none
 * return : int - negative number will be error.
 *                positive number will be success.
 ************************************************************************/
int h223communicationModeCommand(H245Control* pCtrl, RvPvtNodeId message);

/************************************************************************
 * h223ParamsDynamicRTPPayloadType
 * purpose: Dynamic RTP payload type event.
 * input  : pApp            - application handle for the cm.
 *          hVal            - handle for the PVT.
 *          h225ID          - node id for the h225 parameters.
 *          pChannel        - Channel element to set h225 parameters for.
 * output : none
 * return : none
 ************************************************************************/
void h223ParamsDynamicRTPPayloadType(
    IN H245Object*  pApp,
    IN HPVT         hVal,
    IN RvPvtNodeId  h225ID,
    IN H245Channel* pChannel);

/************************************************************************
 * h223ParamsChannelOpenDynamic
 * purpose: Sets the data type.
 * input  : pChannel    - Channel element to set h223 parameters for.
 *          hVal        - PVT handle.
 *          dataTypeId  - Data type node id.
 * output : none
 * return : none
 ************************************************************************/
void h223ParamsChannelOpenDynamic(H245Channel *pChannel, HPVT hVal, RvPvtNodeId dataTypeId);

/************************************************************************
 * h223ParamsCallChannelParametersCallback
 * purpose: Gets same session and associated channel handles.
 * input  : hsChan        - The channel handle.
 * output : hsAssociatedH - The associated channel handle.
 *          haAssociatedH - The associated application channel handle.
 *          hsAssociatedH - The same channel handle.
 *          hsAssociatedH - The same application channel handle.
 * return : none
 ************************************************************************/
void h223ParamsCallChannelParametersCallback(HCHAN    hsChan, 
                                             HCHAN    *hsAssociatedH,
                                             HAPPCHAN *haAssociatedH,
                                             HCHAN    *hsSameSessionH,
                                             HAPPCHAN *haSameSessionH);

/************************************************************************
 * h223ParamsChannelClose
 * purpose: Make sure the default used session Id's are updated if we close them.
 * input  : ctrl        - The control object.
 *          channel     - The channel object.
 * output : none.
 * return : none
 ************************************************************************/
void h223ParamsChannelClose(H245Control *ctrl, H245Channel *channel);

/******************************************************************************
 * h223ParamsChannelReject
 * ----------------------------------------------------------------------------
 * General: Handles outgoing openLogicalChannelReject - Release the videoBuffers
 *          in the demux and set the timer of buffering media - in ACP setup calls.   
 * Return Value: None.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  ctrl                 - H245Control object of the call.
 *         channel              - rejected Channel.
 * Output: None.
 *****************************************************************************/
void h223ParamsChannelReject(H245Control *ctrl, H245Channel *channel);

/****************************************************************************************************************/
/* This function shall be called before the first channel is opened using the H.245 procedures.                 */
/* It is protected from the second call so it may be called each time the new channel is about to be established*/
/* The main purpose of the function is to mark well-known session IDs used by the fast start and                */
/* prevent in this way usage of them in H.245                                                                   */
/****************************************************************************************************************/
void h223ParamsDeriveChannels(HCONTROL ctrl);

/************************************************************************
 * h223ParamsSessionOpenDynamic
 * purpose: Handle the same session and associated channels.
 * input  : channel             - The channel object.
 *          ctrlE               - The control object.
 *          hsChanSameSession   - The same session channel handle.
 *          hsChanAssociated    - The associated channel handle.
 * output : none.
 * return : none
 ************************************************************************/
void h223ParamsSessionOpenDynamic(H245Channel *channel,
                                  H245Control *ctrlE,
                                  HCHAN       hsChanSameSession,
                                  HCHAN       hsChanAssociated,
                                  RvBool      isDynamicPayloadType);

/************************************************************************
 * h223MultiplexReconfiguration
 * purpose: Handle an incoming h223MultiplexReconfiguration message.
 * input  : ctrl    - Control object
 *          message - h223MultiplexReconfiguration message node
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int h223MultiplexReconfiguration(IN H245Control* ctrl, IN int message);

/************************************************************************
 * maxH223MUXPDUsize
 * purpose: Handle an incoming maxH223MUXPDUsize message.
 * input  : ctrl    - Control object
 *          message - maxH223MUXPDUsize message node
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int maxH223MUXPDUsize(IN H245Control* ctrl, IN int message);

/************************************************************************
 * h223EndSessionCommand
 * purpose: Handle an incoming endSessionCommand message.
 *          This should stop the control of the call.
 * input  : ctrl    - Control object
 *          message - endSessionCommand message received
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int h223EndSessionCommand(IN H245Control* ctrl, IN int message);


#else

#define     h223ParamsStartEstablishment                     NULL
#define     h223cmcCallAddressCallbacks                      NULL
#define     h223ParamsOpenLogicalChannelEvent                NULL
#define     h223MaximumSkewIndication                        NULL
#define     h223AllocateChannel                              NULL
#define     h223ChannelFreeMemory                            NULL
#define     h223ParamsChannelAnswer                          NULL
#define     h223ParamsOpenLogicalChannelAck                  NULL
#define     h223ParamsOpenLogicalChannelReject               NULL
#define     h223ParamsOpenLogicalChannelConfirm              NULL
#define     h223communicationModeCommand                     NULL
#define     h223ParamsDynamicRTPPayloadType                  NULL
#define     h223ParamsChannelOpenDynamic                     NULL
#define     h223ParamsCallChannelParametersCallback          NULL
#define     h223ParamsChannelClose                           NULL
#define     h223ParamsChannelReject                          NULL
#define     h223ParamsDeriveChannels                         NULL
#define     h223ParamsSessionOpenDynamic                     NULL
#define     h223MultiplexReconfiguration                     NULL
#define     h223EndSessionCommand                            NULL

#endif /* RV_H245_SUPPORT_H223_PARAMS */

#ifdef __cplusplus
}
#endif

#endif  /* _RV_CM_H223_PARAMS_H */

