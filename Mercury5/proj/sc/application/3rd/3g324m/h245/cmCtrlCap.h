/***********************************************************************
        Copyright (c) 2005 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..

RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/

#ifndef _CMCTRLCAP_H_
#define _CMCTRLCAP_H_

#ifdef __cplusplus
extern "C" {
#endif



void capInit(H245Control* ctrl);

/************************************************************************
 * capEnd
 * purpose: Reset the capabilities timer and delete the capability nodes.
 * input  : ctrl    - Control object
 * output : none
 * return : none
 ************************************************************************/
void capEnd(IN H245Control* ctrl);

/************************************************************************
 * capEndProcess
 * purpose: Reset the capabilities timer.
 * input  : ctrl    - Control object
 * output : none
 * return : none
 ************************************************************************/
void capEndProcess(IN H245Control* ctrl);

/************************************************************************
 * capFree
 * purpose: Free the capabilities node ids
 * input  : ctrl    - Control object
 * output : none
 * return : none
 ************************************************************************/
void capFree(IN H245Control* ctrl);


/************************************************************************
 * outCapTransferRequest
 * purpose: Request to send out a TCS message
 *          This function also handled the timer to set and adds additional
 *          information to the outgoing TCS
 * input  : ctrl    - Control object
 *          message - TCS message node ID to send
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int outCapTransferRequest(IN H245Control* ctrl, IN int message);


/************************************************************************
 * terminalCapabilitySet
 * purpose: Handle an incoming TerminalCapabilitySet message
 * input  : ctrl    - Control object
 *          message - TCS.Request message node
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int terminalCapabilitySet(IN H245Control* ctrl, IN int message);

/************************************************************************
 * terminalCapabilitySetAck
 * purpose: Handle an incoming TerminalCapabilitySetAck message
 * input  : ctrl    - Control object
 *          message - TCS.Ack message node
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int terminalCapabilitySetAck(IN H245Control* ctrl, IN int message);

/************************************************************************
 * terminalCapabilitySetReject
 * purpose: Handle an incoming TerminalCapabilitySetReject message
 * input  : ctrl    - Control object
 *          message - TCS.Reject message node
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int terminalCapabilitySetReject(IN H245Control* ctrl, IN int message);

/************************************************************************
 * terminalCapabilitySetRelease
 * purpose: Handle an incoming TerminalCapabilitySetRelease message
 * input  : ctrl    - Control object
 *          message - TCS.Release message node
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int terminalCapabilitySetRelease(IN H245Control* ctrl, IN int message);

#if (RV_H245_SUPPORT_H225_PARAMS == RV_YES)
/************************************************************************
 * tcsGetMibParams
 * purpose: Get parameters related to the MIB for a TCS object in the
 *          control
 * input  : ctrl            - Control object
 *          inDirection     - RV_TRUE if incoming TCS should be checked. RV_FALSE for outgoing
 * output : state           - Status of TCS
 *          rejectCause     - Reject cause of TCS.Reject
 * return : Non-negative value on success
 *          Negative value on failure
 * Any of the output parameters can be passed as NULL if not relevant to caller
 ************************************************************************/
int tcsGetMibParams(
    IN  H245Control*    ctrl,
    IN  RvBool          inDirection,
    OUT CapStatus*      status,
    OUT int*            rejectCause);


/************************************************************************
 * tcsGetMibProtocolId
 * purpose: Get the protocol identifier of the capabilities.
 * input  : ctrl            - Control object
 *          inDirection     - RV_TRUE if incoming TCS should be checked. RV_FALSE for outgoing
 * output : valueSize       - Size in bytes of the protocol identifier
 *          value           - The protocol identifier
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int tcsGetMibProtocolId(
    IN  H245Control*    ctrl,
    IN  RvBool          inDirection,
    OUT int*            valueSize,
    OUT RvUint8*        value);
#endif /* (RV_H245_SUPPORT_H225_PARAMS == RV_YES) */

/************************************************************************
 * TerminalCapabilitiesSetTimerStop
 * purpose: stop the TCS timer
 * input  : app     - Application Control object
 *          ctrl    - Call Control object
 * output : none
 * return : None
 ************************************************************************/
void TerminalCapabilitiesSetTimerStop(IN H245Object * app, IN H245Control* ctrl);

/************************************************************************
 * TerminalCapabilitiesTimerRestart
 * purpose: set the TCS timer
 * input  : app     - Application Control object
 *          ctrl    - Call Control object
 * output : none
 * return : none
 ************************************************************************/
void TerminalCapabilitiesSetTimerRestart(IN H245Object * app, IN H245Control* ctrl);


#ifdef __cplusplus
}
#endif

#endif
