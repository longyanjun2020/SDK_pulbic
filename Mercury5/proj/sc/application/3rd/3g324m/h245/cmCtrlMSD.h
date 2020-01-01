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

#ifndef _CMCTRL_MSD_H_
#define _CMCTRL_MSD_H_

#ifdef __cplusplus
extern "C" {
#endif


/************************************************************************
 * msdInit
 * purpose: Initialize the master slave determination process on a control channel
 * input  : ctrl            - Control object
 *          terminalType    - Terminal type to use. -1 if we want to use configuration value.
 * output : none
 * return : none
 ************************************************************************/
void msdInit(
    IN H245Control* ctrl,
    IN RvInt32      terminalType);

/************************************************************************
 * msdEnd
 * purpose: Stop the master slave determination process on a control channel
 * input  : ctrl    - Control object
 * output : none
 * return : none
 ************************************************************************/
void msdEnd(IN H245Control* ctrl);

/*************************************************************************************
 * msdDetermineRequest
 *
 * Purpose: Main routine to initiate or respond to a MSD request.
 *
 * Input:	ctrl						- The ctrl element of the call
 *			terminalType				- The given terminal type of the call, may be -1.
 *			statusDeterminationNumber	- The determination numer, may be -1 and then needs to be
 *										  generated.
 * Output: None.
 *
 * return : Non-negative value on success
 *          Negative value on failure
 ******************************************************************************************/
int msdDetermineRequest(H245Control* ctrl, int terminalType, int statusDeterminationNumber);

/************************************************************************
 * masterSlaveDetermination
 * purpose: Handle an incoming MasterSlaveDetermination request,
 *          notifying the application or answering automatically.
 * input  : ctrl    - Control object
 *          message - MSD request message node
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int masterSlaveDetermination(IN H245Control* ctrl, IN int message);

/************************************************************************
 * masterSlaveDeterminationAck
 * purpose: Handle an incoming MasterSlaveDeterminationAck message
 * input  : ctrl    - Control object
 *          message - MSD.Ack message node
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int masterSlaveDeterminationAck(IN H245Control* ctrl, IN int message);

/************************************************************************
 * masterSlaveDeterminationReject
 * purpose: Handle an incoming MasterSlaveDeterminationReject message
 * input  : ctrl    - Control object
 *          message - MSD.Reject message node
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int masterSlaveDeterminationReject(IN H245Control* ctrl, IN int message);

/************************************************************************
 * masterSlaveDeterminationRelease
 * purpose: Handle an incoming MasterSlaveDeterminationRelease message
 * input  : ctrl    - Control object
 *          message - MSD.Release message node
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int masterSlaveDeterminationRelease(IN H245Control* ctrl, IN int message);

/************************************************************************
 * masterSlaveTimerStop
 * purpose: stop the MSD timer
 * input  : app     - Application Control object
 *          ctrl    - Call Control object
 * output : none
 * return : None
 ************************************************************************/
void masterSlaveTimerStop(IN H245Object * app, IN H245Control* ctrl);

/************************************************************************
 * masterSlaveTimerRestart
 * purpose: set the MSD timer
 * input  : app     - Application Control object
 *          ctrl    - Call Control object
 * output : none
 * return : None
 ************************************************************************/
void masterSlaveTimerRestart(IN H245Object * app, IN H245Control* ctrl);

/************************************************************************
 * msdGetMibParams
 * purpose: Get parameters related to the MIB for an MSD object in the
 *          control
 * input  : ctrl            - Control object
 * output : state           - State of MSD
 *          status          - Status of MSD
 *          retries         - Number of MSD retries
 *          terminalType    - Local terminal's type in MSD
 * return : Non-negative value on success
 *          Negative value on failure
 * Any of the output parameters can be passed as NULL if not relevant to caller
 ************************************************************************/
int msdGetMibParams(
    IN  H245Control*    ctrl,
    OUT MsdState*       state,
    OUT MsdStatus*      status,
    OUT int*            retries,
    OUT int*            terminalType);



#ifdef __cplusplus
}
#endif

#endif
