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

#ifndef _CMCTRL_MMODE_H_
#define _CMCTRL_MMODE_H_

#ifdef __cplusplus
extern "C" {
#endif

#if (RV_H245_LEAN_H223 == RV_NO)


/* multipoint mode command on/off____________________________________________________________ */
int conferenceIndication(H245Control* ctrl, int message);
int conferenceCommand(H245Control* ctrl, int message);
int miscellaneousIndication(H245Control* ctrl, int lcn, int message);
int multipointModeCommand(H245Control* ctrl,int lcn);
int cancelMultipointModeCommand(H245Control* ctrl,int lcn);


#endif


#ifdef __cplusplus
}
#endif

#endif
