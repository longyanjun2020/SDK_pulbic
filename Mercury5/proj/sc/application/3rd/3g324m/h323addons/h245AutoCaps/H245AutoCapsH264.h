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

#ifndef _H245_AUTO_CAPS_H264_H_
#define _H245_AUTO_CAPS_H264_H_


/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/

#include "H245AutoCapsInternal.h"

#ifdef __cplusplus
extern "C" {
#endif

#if (RV_H245_AUTO_CAPS_H264 == RV_YES)
/*-----------------------------------------------------------------------*/
/*                           TYPE DEFINITIONS                            */
/*-----------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/*                           FUNCTIONS HEADERS                           */
/*-----------------------------------------------------------------------*/

/******************************************************************************
 * H245AutoCapsMatchCapabilityH264
 * ----------------------------------------------------------------------------
 * General: Matching function for H.264 capability.
 *
 * Return Value: RV_OK  - if matching.
 *               Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  context              - The context of the application.
 *         hPvt                 - The PVT handle.
 *         localCapNodeId       - The local capability ASN.1 node id.
 *         remoteCapNodeId      - The remote capability ASN.1 node id.
 * Output: None.
 *****************************************************************************/
RvStatus RVCALLCONV H245AutoCapsMatchCapabilityH264 (
    IN  void			*context,
    IN  HPVT			hPvt,
    IN  RvPvtNodeId     localCapNodeId,
    IN  RvPvtNodeId     remoteCapNodeId);

/******************************************************************************
 * H245AutoCapsGetGCDCapabilityH264
 * ----------------------------------------------------------------------------
 * General: Function called when finding GCD between local and
 *          remote H.264 capabilities.
 *
 *          Note that the only parameters considered here are maxBitRate and
 *          level.
 * Return Value: RV_OK  - if successful.
 *               Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  context              - The context of the application.
 *         hPvt                 - The PVT handle.
 *         localCapNodeId       - The local capability ASN.1 node id.
 *         remoteCapNodeId      - The remote capability ASN.1 node id.
 * Output: bChanged             - Indication that one of the parameters was
 *                                changed during the GCD process.
 *****************************************************************************/
RvStatus RVCALLCONV H245AutoCapsGetGCDCapabilityH264 (
    IN  void			*context,
    IN  HPVT			hPvt,
    IN  RvPvtNodeId     localCapNodeId,
    IN  RvPvtNodeId     remoteCapNodeId,
    OUT RvBool          *bChanged);


#else 
/* RV_H245_AUTO_CAPS_H264 */
#define H245AutoCapsMatchCapabilityH264(_context, _hPvt, _localCapNodeId, _remoteCapNodeId) RV_OK
#define H245AutoCapsGetGCDCapabilityH264(_context, _hPvt, _localCapNodeId, _remoteCapNodeId, _bChanged) RV_OK
#endif  /* RV_H245_AUTO_CAPS_H264 */

#ifdef __cplusplus
}
#endif

#endif /* _H245_AUTO_CAPS_H264_H_ */
