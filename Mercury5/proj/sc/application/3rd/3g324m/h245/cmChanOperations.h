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

#ifndef _CMCHANOPERATIONS_
#define _CMCHANOPERATIONS_


#ifdef __cplusplus
extern "C" {
#endif

int flowControlCommand(H245Control*ctrl, int base, int message);
int maintenanceLoopRequest(H245Control*ctrl, int base, int message);
int maintenanceLoopAck(H245Control*ctrl, int base, int message);
int maintenanceLoopReject(H245Control*ctrl, int base, int message);
int maintenanceLoopOffCommand(H245Control*ctrl, int message);
int videoFreezePicture(H245Control* ctrl, int base, int lcn);
int videoSendSyncEveryGOB(H245Control* ctrl, int base, int lcn);
int videoSendSyncEveryGOBCancel(H245Control* ctrl, int base, int lcn);
int switchReceiveMediaOff(H245Control* ctrl, int base, int lcn);
int switchReceiveMediaOn(H245Control* ctrl, int base, int lcn);
int videoTemporalSpatialTradeOff(H245Control* ctrl, int base, int message, int lcn, RvInt8 isCommand);
int videoFastUpdatePicture(H245Control* ctrl, int base, int lcn);
int videoFastUpdateGOB(H245Control* ctrl, int base, int message, int lcn);
int videoFastUpdateMB(H245Control* ctrl, int base, int message, int lcn);
int logicalChannelActive(H245Control* ctrl, int base, int lcn);
int logicalChannelInactive(H245Control* ctrl, int base, int lcn);
#if (RV_H245_LEAN_H223 == RV_NO)
int transportCapability(H245Control* ctrl, int base, int message, int lcn);
#endif

#ifdef __cplusplus
}
#endif

#endif
