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

#ifndef _CMCHANGET_
#define _CMCHANGET_

#include "cmControl.h"
#include "cmctrl.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Return the channel by LCN. The reverse direction of the bidirectional channel is not considered separate channel */
H245Channel* getInChanByLCN(HCONTROL ctrl, int lcn);
H245Channel* getOutChanByLCN(HCONTROL ctrl, int lcn);

/* Return the channel by LCN. The reverse direction of the bidirectional channel is considered separate channel */
H245Channel* getInSubChanByLCN(HCONTROL ctrl, int lcn);
H245Channel* getOutSubChanByLCN(HCONTROL ctrl, int lcn);
H245Channel* getNextOutChanByBase(HCONTROL ctrl,H245Channel* channel, void** ptr);

H245Channel* getNextOutChan(HCONTROL ctrl, void** ptr);
H245Channel* getNextInChan(HCONTROL ctrl, void** ptr);

/************************************************************************
 * getNextChan
 * purpose: Get the next channel for a given control object.
 *          This function can be used to perform a single task on all
 *          the channels.
 * input  : ctrl            - Control object
 *          currentH245Channel  - Current channel we have.
 *                            If the contents of this pointer is NULL, then the
 *                            first channel will be returned
 * output : currentH245Channel  - Next channel in list
 * return : Next channel in list on success
 *          NULL when there are no more channels
 ************************************************************************/
H245Channel* getNextChan(IN HCONTROL ctrl, INOUT void** currentH245Channel);


#if (RV_H245_SUPPORT_H223_PARAMS == 1)

/************************************************************************
 * getInChanByDataType
 * purpose: Get incoming channel for a given DataType.
 *          
 * input  : ctrl            - Control object
 *          dataType  - DataType of channel
 * output : None
 * return : The required channel if exist
 *          NULL when there is no such channel
 ************************************************************************/
H245Channel* getInChanByDataType(IN HCONTROL ctrl, IN cmChannelDataType dataType);

/************************************************************************
 * getOutChanByDataType
 * purpose: Get outgoing channel for a given DataType.
 *          
 * input  : ctrl            - Control object
 *          dataType  - DataType of channel
 * output : None
 * return : The required channel if exist
 *          NULL when there is no such channel
 ************************************************************************/
H245Channel* getOutChanByDataType(IN HCONTROL ctrl, IN cmChannelDataType dataType);

#endif /* (RV_H245_SUPPORT_H223_PARAMS == 1) */


#if (RV_H245_SUPPORT_H225_PARAMS == 1)
/************************************************************************
 *
 *                Functions that deal with session IDs
 *
 ************************************************************************/

H245Channel* getOutChanBySID(HCONTROL ctrl, RvUint8 sid);
H245Channel* getInChanBySID(HCONTROL ctrl, RvUint8 sid);

RvBool checkChanSIDConsistency(
    IN HCONTROL         ctrl,
    IN H245Channel*     test_channel,
    IN RvUint8          sessionId,
    IN RvBool           isOrigin,
    IN RvBool           isDuplex);

RvUint8 getFreeSID(HCONTROL ctrl, RvBool isOrigin, RvBool isDuplex);

#endif /* (RV_H245_SUPPORT_H225_PARAMS == 1) */




#ifdef __cplusplus
}
#endif

#endif /* _CMCHANGET_ */
