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

#ifndef _RV_GEF_G7222_H_
#define _RV_GEF_G7222_H_


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

/* G.722.2 definitions according to G.722.2/Annex F (also known as AMR-WB). */

#define RV_GEF_G7222_CAPABILITY_IDENTIFIER "itu-t (0) recommendation (0) g (7) 7222 generic-capabilities (1) 0"

#define RV_GEF_G7222_MAX_BIT_RATE 239

#define RV_GEF_G7222_PARAMETER_IDENTIFIER_MAX_AL_SDU_FRAMES 0
#define RV_GEF_G7222_PARAMETER_IDENTIFIER_BIT_RATE 1 
#define RV_GEF_G7222_PARAMETER_IDENTIFIER_OCTET_ALIGN 2
#define RV_GEF_G7222_PARAMETER_IDENTIFIER_MODE_SET 3
#define RV_GEF_G7222_PARAMETER_IDENTIFIER_MODE_CHANGE_PERIOD 4
#define RV_GEF_G7222_PARAMETER_IDENTIFIER_MODE_CHANGE_NEIGHBOUR 5
#define RV_GEF_G7222_PARAMETER_IDENTIFIER_CRC 6
#define RV_GEF_G7222_PARAMETER_IDENTIFIER_ROBUST_SORTING 7
#define RV_GEF_G7222_PARAMETER_IDENTIFIER_INTERLEAVING 8


/*-----------------------------------------------------------------------*/
/*                           FUNCTIONS HEADERS                           */
/*-----------------------------------------------------------------------*/


/******************************************************************************
 * RvGefG7222Build
 * ----------------------------------------------------------------------------
 * General: Builds the GenericCapability ASN.1 node ID for the G.722.2 codec. 
 *          After this node ID is built, it is the responsibility of the 
 *          application to delete it. Note that the Capability Identifier 
 *          and maxBitRate have already been set to this node ID.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt             - PVT handle for building ASN.1 node IDs.
 * Output: g7222NodeId      - The new GenericCapability node ID for the G.722.2 codec.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7222Build(
    IN  HPVT                    hPvt,
    OUT RvPvtNodeId             *g7222NodeId);



/******************************************************************************
 * RvGefG7222AddMaxAlSduFrames
 * ----------------------------------------------------------------------------
 * General: Adds the maxAlSduFrames parameter to the GenericCapability 
 *          ASN.1 node ID for the G.722.2 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g7222NodeId          - The GenericCapability node ID for the G.722.2 codec.
 *         maxAlSduFrames       - The maxAlSduFrames parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7222AddMaxAlSduFrames(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g7222NodeId,
    IN  RvUint16                            maxAlSduFrames);


/******************************************************************************
 * RvGefG7222GetMaxAlSduFrames
 * ----------------------------------------------------------------------------
 * General: Gets the maxAlSduFrames parameter from the GenericCapability 
 *          ASN.1 node ID of the G.722.2 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g7222NodeId          - The GenericCapability node ID for the G.722.2 codec.
 * Output: pMaxAlSduFrames      - The maxAlSduFrames parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7222GetMaxAlSduFrames(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g7222NodeId,
    OUT RvUint16                            *pMaxAlSduFrames);


/******************************************************************************
 * RvGefG7222AddBitRate
 * ----------------------------------------------------------------------------
 * General: Adds the bitRate parameter to the GenericCapability ASN.1 node ID 
 *          for the G.722.2 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g7222NodeId          - The GenericCapability node ID for the G.722.2 codec.
 *         bitRate              - The bitRate parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7222AddBitRate(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g7222NodeId,
    IN  RvUint16                            bitRate);


/******************************************************************************
 * RvGefG7222GetBitRate
 * ----------------------------------------------------------------------------
 * General: Gets the bitRate parameter from the GenericCapability 
 *          ASN.1 node ID of the G.722.2 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g7222NodeId          - The GenericCapability node ID for the G.722.2 codec.
 * Output: pBitRate             - The bitRate parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7222GetBitRate(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g7222NodeId,
    OUT RvUint16                            *pBitRate);


/******************************************************************************
 * RvGefG7222AddOctetAlign
 * ----------------------------------------------------------------------------
 * General: Adds the OctetAlign parameter to the GenericCapability 
 *          ASN.1 node ID for the G.722.2 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g7222NodeId          - The GenericCapability node ID for the G.722.2 codec.
 *         bParameterExists     - Determines whether the OctetAlign parameter is used.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7222AddOctetAlign(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g7222NodeId,
    IN  RvBool                              bParameterExists);


/******************************************************************************
 * RvGefG7222GetOctetAlign
 * ----------------------------------------------------------------------------
 * General: Gets the OctetAlign parameter from the GenericCapability 
 *          ASN.1 node ID of the G.722.2 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g7222NodeId          - The GenericCapability node ID for the G.722.2 codec.
 * Output: pParameterExists     - The current support of OctetAlign.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7222GetOctetAlign(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g7222NodeId,
    OUT RvBool                              *pParameterExists);


/******************************************************************************
 * RvGefG7222AddModeSet
 * ----------------------------------------------------------------------------
 * General: Adds the modeSet parameter to the GenericCapability ASN.1 node ID 
 *          for the G.722.2 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g7222NodeId          - The GenericCapability node ID for the G.722.2 codec.
 *         modeSet              - The modeSet parameter defined as an array of 
 *                                RvUint16. The size is provided in the modeSetSize 
 *                                parameter.
 *         modeSetSize          - Number of modes inside the modeSetParameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7222AddModeSet(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g7222NodeId,
    IN  RvUint16                            *pModeSet,
    IN  RvUint32                            modeSetSize);


/******************************************************************************
 * RvGefG7222GetModeSet
 * ----------------------------------------------------------------------------
 * General: Gets the modeSet parameter from the GenericCapability 
 *          ASN.1 node ID of the G.722.2 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g7222NodeId          - The GenericCapability node ID for the G.722.2 codec.
 *         pModeSetSize         - The number of elements allocated for the 
 *                                pModeSet parameter. If this number is not high 
 *                                enough the function will fail and the real size 
 *                                will be provided to the application in this 
 *                                parameter. The application should call the function 
 *                                again with the appropriate allocated array.
 * Output: pModeSet             - The modeSet parameter. The array should be 
 *                                allocated by the application.
 *         pModeSetSize         - Number of elements inside pModeSet.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7222GetModeSet(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g7222NodeId,
    OUT RvUint16                            *pModeSet,
    OUT RvUint32                            *pModeSetSize);

/******************************************************************************
 * RvGefG7222AddModeChangePeriod
 * ----------------------------------------------------------------------------
 * General: Adds the ModeChangePeriod parameter to the GenericCapability 
 *          ASN.1 node ID for the G.722.2 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g7222NodeId          - The GenericCapability node ID for the G.722.2 codec.
 *         modeChangePeriod     - The modeChangePeriod parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7222AddModeChangePeriod(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g7222NodeId,
    IN  RvUint16                            modeChangePeriod);


/******************************************************************************
 * RvGefG7222GetModeChangePeriod
 * ----------------------------------------------------------------------------
 * General: Gets the ModeChangePeriod parameter from the GenericCapability 
 *          ASN.1 node ID of the G.722.2 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g7222NodeId          - The GenericCapability node ID for the G.722.2 codec.
 * Output: pModeChangePeriod    - The ModeChangePeriod parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7222GetModeChangePeriod(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g7222NodeId,
    OUT RvUint16                            *pModeChangePeriod);

/******************************************************************************
 * RvGefG7222AddModeChangeNeighbor
 * ----------------------------------------------------------------------------
 * General: Adds the ModeChangeNeighbor parameter to the GenericCapability 
 *          ASN.1 node ID for the G.722.2 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g7222NodeId          - The GenericCapability node ID for the G.722.2 codec.
 *         bParameterExists     - Determines whether the ModeChangeNeighbor parameter 
 *                                is used.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7222AddModeChangeNeighbor(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g7222NodeId,
    IN  RvBool                              bParameterExists);


/******************************************************************************
 * RvGefG7222GetModeChangeNeighbor
 * ----------------------------------------------------------------------------
 * General: Gets the ModeChangeNeighbor parameter from the 
 *          GenericCapability ASN.1 node ID of the G.722.2 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g7222NodeId          - The GenericCapability node ID for the G.722.2 codec.
 * Output: pParameterExists     - The current support of ModeChangeNeighbor.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7222GetModeChangeNeighbor(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g7222NodeId,
    OUT RvBool                              *pParameterExists);


/******************************************************************************
 * RvGefG7222AddCrc
 * ----------------------------------------------------------------------------
 * General: Adds the Crc parameter to the GenericCapability ASN.1 node ID 
 *          for the G.722.2 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g7222NodeId          - The GenericCapability node ID for the G.722.2 codec.
 *         bParameterExists     - Determines whether the Crc parameter is used.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7222AddCrc(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g7222NodeId,
    IN  RvBool                              bParameterExists);


/******************************************************************************
 * RvGefG7222GetCrc
 * ----------------------------------------------------------------------------
 * General: Gets the Crc parameter from the GenericCapability ASN.1 node ID 
 *          of the G.722.2 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g7222NodeId          - The GenericCapability node ID for the G.722.2 codec.
 * Output: pParameterExists     - The current support of Crc.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7222GetCrc(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g7222NodeId,
    OUT RvBool                              *pParameterExists);

/******************************************************************************
 * RvGefG7222AddRobustSorting
 * ----------------------------------------------------------------------------
 * General: Adds the robustSorting parameter to the GenericCapability 
 *          ASN.1 node ID for the G.722.2 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g7222NodeId          - The GenericCapability node ID for the G.722.2 codec.
 *         bParameterExists     - Determines whether the robustSorting parameter is used.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7222AddRobustSorting(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g7222NodeId,
    IN  RvBool                              bParameterExists);


/******************************************************************************
 * RvGefG7222GetRobustSorting
 * ----------------------------------------------------------------------------
 * General: Gets the robustSorting parameter from the GenericCapability 
 *          ASN.1 node ID of the G.722.2 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g7222NodeId          - The GenericCapability node ID for the G.722.2 codec.
 * Output: pParameterExists     - The current support of robustSorting.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7222GetRobustSorting(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g7222NodeId,
    OUT RvBool                              *pParameterExists);

/******************************************************************************
 * RvGefG7222AddInterleaving
 * ----------------------------------------------------------------------------
 * General: Adds the Interleaving parameter to the GenericCapability 
 *          ASN.1 node ID for the G.722.2 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g7222NodeId          - The GenericCapability node ID for the G.722.2 codec.
 *         interleaving         - The Interleaving parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7222AddInterleaving(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g7222NodeId,
    IN  RvUint16                            interleaving);


/******************************************************************************
 * RvGefG7222GetInterleaving
 * ----------------------------------------------------------------------------
 * General: Gets the Interleaving parameter from the GenericCapability 
 *          ASN.1 node ID of the G.722.2 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         g7222NodeId          - The GenericCapability node ID for the G.722.2 codec.
 * Output: pInterleaving        - The Interleaving parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefG7222GetInterleaving(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         g7222NodeId,
    OUT RvUint16                            *pInterleaving);

#ifdef __cplusplus
}
#endif

#endif /* _RV_GEF_G7222_H_ */
