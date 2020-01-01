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

#ifndef _CM_CTRL_RTD_H
#define _CM_CTRL_RTD_H


#include "cmControl.h"


#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 * rtdInit
 * purpose: Initialize the round trip delay process on a control channel
 * input  : ctrl    - Control object
 * output : none
 * return : none
 ************************************************************************/
int rtdInit(H245Control* ctrl);

/************************************************************************
 * rtdEnd
 * purpose: Stop the round trip delay process on a control channel
 * input  : ctrl    - Control object
 * output : none
 * return : none
 ************************************************************************/
void rtdEnd(IN H245Control* ctrl);

int roundTripDelayRequest(H245Control* ctrl, int message);
int roundTripDelayResponse(H245Control* ctrl, int message);

#ifdef __cplusplus
}
#endif

#endif /* _CM_CTRL_RTD_H */
