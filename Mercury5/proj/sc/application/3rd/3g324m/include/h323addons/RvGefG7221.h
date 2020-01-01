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

#ifndef _RV_GEF_G7221_H_
#define _RV_GEF_G7221_H_


/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "RvGefGeneral.h"

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                           TYPE DEFINITIONS                            */
/*-----------------------------------------------------------------------*/

/* G.722.1 definitions according to G.722.1 / Annex A */

#define RV_GEF_G7221_MAX_BIT_RATE_32 32000
#define RV_GEF_G7221_MAX_BIT_RATE_24 24000

#define RV_GEF_G7221_CAPABILITY_IDENTIFIER "itu-t(0) recommendation(0) g(7) 7221 generic-capabilities(1) 0"

#define RV_GEF_G7221_PARAMETER_IDENTIFIER_MAX_FRAMES_PER_PACKET 1

/*-----------------------------------------------------------------------*/
/*                           FUNCTIONS HEADERS                           */
/*-----------------------------------------------------------------------*/


/******************************************************************************
 * RvGefG7221Build
 * ----------------------------------------------------------------------------
 * General: Builds the GenericCapability ASN.1 node ID for G.722.1 codec. 
 *          If this node ID is built, it is the responsibility of the 
 *          application to delete it. Note that the Capability Identifier 
 *          has already been set to this node ID.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt             - PVT handle for building ASN.1 node IDs.
 * Output: g7221NodeId      - The new GenericCapability node ID for G.722.1 codec.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7221Build(
    IN  HPVT                    hPvt,
    OUT RvPvtNodeId             *g7221NodeId);



/******************************************************************************
 * RvGefG7221SetMaxBitRate
 * ----------------------------------------------------------------------------
 * General: Sets the maxBitRate parameter to the GenericCapability ASN.1 node ID  
 *          for the G.722.1 codec. Currently, this parameter can only be set to:
 *          RV_GEF_G7221_MAX_BIT_RATE_32 or RV_GEF_G7221_MAX_BIT_RATE_24.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g7221NodeId          - The GenericCapability node ID for the G.722.1 codec.
 *         maxBitRate           - The maxBitRate parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7221SetMaxBitRate(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g7221NodeId,
    IN  RvUint32                            maxBitRate);


/******************************************************************************
 * RvGefG7221GetMaxBitRate
 * ----------------------------------------------------------------------------
 * General: Gets the maxBitRate parameter from the GenericCapability ASN.1 node ID 
 *          of the G.722.1 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g7221NodeId          - The GenericCapability node ID for the G.722.1 codec.
 * Output: pMaxBitRate          - The maxBitRate parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7221GetMaxBitRate(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g7221NodeId,
    OUT RvUint32                            *pMaxBitRate);


/******************************************************************************
 * RvGefG7221AddMaxFramesPerPacket
 * ----------------------------------------------------------------------------
 * General: Adds the maxFramesPerPacket parameter to the GenericCapability 
 *          ASN.1 node ID for the G.722.1 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g7221NodeId          - The GenericCapability node ID for the G.722.1 codec.
 *         maxFramesPerPacket   - The maxFramesPerPacket parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7221AddMaxFramesPerPacket(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g7221NodeId,
    IN  RvUint16                            maxFramesPerPacket);


/******************************************************************************
 * RvGefG7221GetMaxFramesPerPacket
 * ----------------------------------------------------------------------------
 * General: Gets the maxFramesPerPacket parameter from the GenericCapability 
 *          ASN.1 node ID of the G.722.1 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g7221NodeId          - The GenericCapability node ID for the G.722.1 codec.
 * Output: pMaxFramesPerPacket  - The maxFramesPerPacket parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7221GetMaxFramesPerPacket(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g7221NodeId,
    OUT RvUint16                            *pMaxFramesPerPacket);






#ifdef __cplusplus
}
#endif

#endif /* _RV_GEF_G7221_H_ */
