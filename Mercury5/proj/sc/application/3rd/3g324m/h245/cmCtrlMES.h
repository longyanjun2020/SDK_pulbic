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
#ifndef _CM_CTRL_MES_H_
#define _CM_CTRL_MES_H_


#ifdef __cplusplus
extern "C" {
#endif

#if (RV_H245_SUPPORT_H223_PARAMS == 1)    
    
/******************************************************************************
 * mesInit
 * ----------------------------------------------------------------------------
 * General: Initialize a multiplexEntrySend object of the control.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  ctrl - Control object
 *****************************************************************************/
RvStatus mesInit(IN H245Control* ctrl);

/******************************************************************************
 * mesEnd
 * ----------------------------------------------------------------------------
 * General: Destruct a multiplexEntrySend object of the control.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  ctrl - Control object
 *****************************************************************************/
RvStatus mesEnd(IN H245Control* ctrl);

/************************************************************************
 * multiplexEntrySend
 * purpose: Handle an incoming multiplexEntrySend message
 * input  : ctrl    - Control object
 *          message - MES message node
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int multiplexEntrySend(IN H245Control* ctrl, IN int message);

/************************************************************************
 * multiplexEntrySendAck
 * purpose: Handle an incoming multiplexEntrySendAck message
 * input  : ctrl    - Control object
 *          message - MES.Ack message node
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int multiplexEntrySendAck(IN H245Control* ctrl, IN int message);

/************************************************************************
 * multiplexEntrySendReject
 * purpose: Handle an incoming multiplexEntrySendReject message
 * input  : ctrl    - Control object
 *          message - MES.Reject message node
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int multiplexEntrySendReject(IN H245Control* ctrl, IN int message);

/************************************************************************
 * multiplexEntrySendRelese
 * purpose: Handle an incoming multiplexEntrySendRelese message
 * input  : ctrl    - Control object
 *          message - MES message node
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int multiplexEntrySendRelese(IN H245Control* ctrl, IN int message);	

#else /*RV_H245_SUPPORT_H223_PARAMS == 1*/

#define multiplexEntrySend(ctrl, message)
#define multiplexEntrySendAck(ctrl, message)
#define multiplexEntrySendReject(ctrl, message)
#define multiplexEntrySendRelese(ctrl, message)	

#endif /*RV_H245_SUPPORT_H223_PARAMS == 1*/

#ifdef __cplusplus
}
#endif

#endif /* _CM_CTRL_MES_H_ */
