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

#ifndef _CMCTRL_RMODE_H_
#define _CMCTRL_RMODE_H_

#ifdef __cplusplus
extern "C" {
#endif




int requestMode(H245Control* ctrl, int message);
int requestModeAck(H245Control* ctrl, int message);
int requestModeReject(H245Control* ctrl, int message);
int requestModeRelease(H245Control* ctrl, int message);

/************************************************************************
 * rmInit
 * purpose: Initialize the request mode process on a control channel
 * input  : ctrl    - Control object
 * output : none
 * return : none
 ************************************************************************/
int rmInit(H245Control* ctrl);

/************************************************************************
 * rmEnd
 * purpose: Stop the request mode process on a control channel
 * input  : ctrl    - Control object
 * output : none
 * return : none
 ************************************************************************/
void rmEnd(IN H245Control* ctrl);


#ifdef __cplusplus
}
#endif

#endif
