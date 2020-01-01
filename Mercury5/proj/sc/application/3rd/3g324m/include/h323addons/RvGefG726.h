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

#ifndef _RV_GEF_G726_H_
#define _RV_GEF_G726_H_


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

/* AMR definitions according to H.245/Annex I */

#define RV_GEF_G726_CAPABILITY_IDENTIFIER "itu-t(0) recommendation(0) g(7) 726 generic-capabilities(1) version2003(0)"

#define RV_GEF_G726_MAX_BIT_RATE_40 400
#define RV_GEF_G726_MAX_BIT_RATE_32 320
#define RV_GEF_G726_MAX_BIT_RATE_24 240
#define RV_GEF_G726_MAX_BIT_RATE_16 160

#define RV_GEF_G726_PARAMETER_IDENTIFIER_MAX_SAMPLES_PER_PACKET 1
#define RV_GEF_G726_PARAMETER_IDENTIFIER_BIT_ORDER 2 


/*-----------------------------------------------------------------------*/
/*                           FUNCTIONS HEADERS                           */
/*-----------------------------------------------------------------------*/


/******************************************************************************
 * RvGefG726Build
 * ----------------------------------------------------------------------------
 * General: Builds the GenericCapability ASN.1 node ID for the G.726 codec. 
 *          When this node ID is built, it is the responsibility of the 
 *          application to delete it. Note that the Capability Identifier has 
 *          already been set to this node ID.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt             - PVT handle for building ASN.1 node IDs.
 * Output: g726NodeId       - The new GenericCapability node ID for the 
 *                            G.726 codec.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG726Build(
    IN  HPVT                    hPvt,
    OUT RvPvtNodeId             *g726NodeId);


/******************************************************************************
 * RvGefG726SetMaxBitRate
 * ----------------------------------------------------------------------------
 * General: Sets the maxBitRate parameter to the GenericCapability ASN.1 node ID
 *          for the G.726 codec. Currently, this parameter can only be set to:
 *          RV_GEF_G726_MAX_BIT_RATE_40, RV_GEF_G726_MAX_BIT_RATE_32, 
 *          RV_GEF_G726_MAX_BIT_RATE_24 or RV_GEF_G726_MAX_BIT_RATE_16.
 *
 *          This parameter should only be used in OpenLogicalChannel and 
 *          not in Capabilities.
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node ids.
 *         g726NodeId           - The GenericCapability node id for the G.726 codec.
 *         maxBitRate           - The maxBitRate parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG726SetMaxBitRate(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g726NodeId,
    IN  RvUint32                            maxBitRate);


/******************************************************************************
 * RvGefG726GetMaxBitRate
 * ----------------------------------------------------------------------------
 * General: Gets the maxBitRate parameter from the GenericCapability 
 *          ASN.1 node ID of the G.726 codec.
 *
 *          This parameter should be used only in OpenLogicalChannel and 
 *          not in Capabilities.
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g726NodeId           - The GenericCapability node ID for the G.726 codec.
 * Output: pMaxBitRate          - The maxBitRate parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG726GetMaxBitRate(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g726NodeId,
    OUT RvUint32                            *pMaxBitRate);

/******************************************************************************
 * RvGefG726AddMaxSamplesPerPacket 
 * ----------------------------------------------------------------------------
 * General: Adds the maxSamplesPerPacket parameter to the GenericCapability 
 *          ASN.1 node ID for the G.726 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g726NodeId           - The GenericCapability node ID for the G.726 codec.
 *         maxAlSduFrames       - The maxSamplesPerPacket parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG726AddMaxSamplesPerPacket(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g726NodeId,
    IN  RvUint16                            maxSamplesPerPacket);


/******************************************************************************
 * RvGefG726GetMaxSamplesPerPacket
 * ----------------------------------------------------------------------------
 * General: Gets the maxAlSduFrames parameter from the GenericCapability 
 *          ASN.1 node ID of the G.726 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g726NodeId           - The GenericCapability node ID for the G.726 codec.
 * Output: pMaxSamplesPerPacket - The maxSamplesPerPacket parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG726GetMaxSamplesPerPacket(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g726NodeId,
    OUT RvUint16                            *pMaxSamplesPerPacket);


/******************************************************************************
 * RvGefG726AddBitOrder
 * ----------------------------------------------------------------------------
 * General: Adds the bitOrder parameter to the GenericCapability 
 *          ASN.1 node ID for the G.726 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g726NodeId           - The GenericCapability node ID for the G.726 codec.
 *         bitOrder             - The bitOrder parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG726AddBitOrder(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g726NodeId,
    IN  RvUint8                             bitOrder);


/******************************************************************************
 * RvGefG726GetBitOrder
 * ----------------------------------------------------------------------------
 * General: Gets the bitOrder parameter from the GenericCapability 
 *          ASN.1 node ID of the G.726 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g726NodeId           - The GenericCapability node ID for the G.726 codec.
 * Output: pBitOrder            - The bitOrder parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG726GetBitOrder(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g726NodeId,
    OUT RvUint8                             *pBitOrder);


#ifdef __cplusplus
}
#endif

#endif /* _RV_GEF_G726_H_ */
