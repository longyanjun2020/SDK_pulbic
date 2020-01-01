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

#ifndef _CMI_FAST_START_H
#define _CMI_FAST_START_H

#include "cmCall.h"
#include "cmH245Object.h"

#ifdef __cplusplus
extern "C" {
#endif



/******************************************************************************************
 * analyzeFastStartMsg
 *
 * Purpose:  This function is called upon receipt of a setup message.
 *           The function checks for any fast-start channels in the message,
 *           decodes the data and builds it into a structure that is passed in a CallBack
 *           to the application, such that the application may ack some of them.
 *
 * Input:    hsCall     - call object instance
 *           message    - The node id to the setup message
 *
 * Returned Value: Non-negative value on success
 *                 Negative value on failure
 ****************************************************************************************/
int analyzeFastStartMsg(
                IN  HCALL       hsCall,
                IN  int         message
                );


/******************************************************************************************
 * cmFastStartReply
 *
 * Purpose:  This function is called from the CM whenever a response message after SETUP
 *           is received (CallProceeding, Alerting, Connect, Facility and Progress).
 *           It checks for FastStart response. If such exists, it processes it and opens
 *           the relevant channels.
 *
 * Input:    hsCall     - call object instance
 *           message    - node ID of the message
 *           isConnect  - True iff this is a connect message
 *
 * Returned Value: Non-negative value on success
 *                 Negative value on failure
 ****************************************************************************************/
int  cmFastStartReply(
    IN HCALL    hsCall,
    IN int      message,
    IN RvBool   isConnect);


/******************************************************************************************
 * addFastStart
 *
 * Purpose:  This function adds the fast start messages that are stored on the call
 *           to an outgoing message
 *
 * Input:    hsCall     - call object instance
 *           message    - message's root node ID to add fast start information to
 *
 * Returned Value: none
 ****************************************************************************************/
void addFastStart(
    IN HCALL    hsCall,
    IN int      message);


void deleteFastStart(HCALL hsCall);
void deleteOutgoingFastStartOffer(HCALL hsCall);
void deleteIncomingFastStartOffer(HCALL hsCall);
int  fastStartInit(IN HH245 hApp, IN int maxCalls, IN int proposed, IN int accepted);
void fastStartEnd(IN HH245 hApp);
void fastStartCallInit(HCALL hsCall);

#ifdef __cplusplus
}
#endif


#endif  /* _CMI_FAST_START_H */
