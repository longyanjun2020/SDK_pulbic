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

#ifndef _RV_GEF_MONA_H_
#define _RV_GEF_MONA_H_


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


#define RV_GEF_MONA_PARAMETER_IDENTIFIER_MEDIA_BUFFERING 3
#define RV_GEF_MONA_PARAMETER_IDENTIFIER_AUDIO_ENTRY 4
#define RV_GEF_MONA_PARAMETER_IDENTIFIER_VIDEO_ENTRY 5

/*-----------------------------------------------------------------------*/
/*                           FUNCTIONS HEADERS                           */
/*-----------------------------------------------------------------------*/

/******************************************************************************
 * RvGefMONABuild
 * ----------------------------------------------------------------------------
 * General: Builds the genericInformation ASN.1 MONA genericCapability node. 
 *          After this node is built, it is the responsibility of the application 
 *          to delete it. Note that the Message Identifier has already been set 
 *          to this node.
 *
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *
 * Output: genericInformationNodeId  - The new genericInformation node ID 
 *                                     for the MONA generic capability.
 *
 * Return Value: RV_OK if successful. Other on failure.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefMONABuild(
    IN  HPVT                    hPvt,
    OUT RvPvtNodeId             *genericInformationNodeId);

/******************************************************************************
 * RvGefMONASetMediaBuffering
 * ----------------------------------------------------------------------------
 * General: Sets the mediaBuffering parameter in the messageContent subfield 
 *          of the genericInformation node for the MONA Generic Capability. 
 *
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID of the 
 *                                     MONA genericCapability.
 *         mediaBuffering            - The mediaBuffering value.
 *
 * Output: None.
 *
 * Return Value: RV_OK if successful. Other on failure.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefMONASetMediaBuffering(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    IN  RvUint32                mediaBuffering);

/******************************************************************************
 * RvGefMONAGetMediaBuffering
 * ----------------------------------------------------------------------------
 * General: Gets the MediaBuffering from the MONA generic capability.
 *
 * Arguments:
 * Input:  hPvt                         - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId     - The GenericMessage node id for MONA capability.
 *
 * Output: mbParam         - RV_TRUE if masterBidirectionalVideo is present.
 *
 * Return Value: RV_OK if successful. Other on failure.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefMONAGetMediaBuffering(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    OUT RvUint16                *mbParam);

/******************************************************************************
 * RvGefMONASetAudioEntry
 * ----------------------------------------------------------------------------
 * General: Sets the audioEntry parameter in the messageContent subfield of the 
 *          genericInformation node for the MONA Generic Capability.  
 *
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID 
 *                                     of the MONA generic capability.
 *         audioEntry                - The audioEntry value.
 *
 * Output: None.
 *
 * Return Value: RV_OK if successful. Other on failure.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefMONASetAudioEntry(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    IN  RvUint32                audioEntry);

/******************************************************************************
 * RvGefMONAGetAudioEntry
 * ----------------------------------------------------------------------------
 * General: Gets the audioEntry parameter from the messageContent subfield of 
 *          the genericInformation node of the MONA generic capability.  
 *
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID 
 *                                     of the MONA generic capability.
 *
 * Output: audioEntry                - The audioEntry value.
 *
 * Return Value: RV_OK if successful. Other on failure.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefMONAGetAudioEntry(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    OUT RvUint32                *audioEntry);

/******************************************************************************
 * RvGefMONASetVideoEntry
 * ----------------------------------------------------------------------------
 * General: Sets the videEntry parameter in the messageContent subfield of the 
 *          genericInformation node for the MONA Generic Capability.  
 *
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID 
 *                                     of the MONA generic capability.
 *         videoEntry				 - The videoEntry value.
 *
 * Output: None.
 *
 * Return Value: RV_OK if successful. Other on failure.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefMONASetVideoEntry(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    IN  RvUint32                videoEntry);

/******************************************************************************
 * RvGefMONAGetVideoEntry
 * ----------------------------------------------------------------------------
 * General: Gets the videoEntry parameter from the messageContent subfield of 
 *          the genericInformation node of the MONA Generic Capability. 
 *
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID 
 *                                     of the MONA generic capability.
 *
 * Output: videoEntry                - The videoEntry value. 
 *
 * Return Value: RV_OK if successful. Other on failure.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefMONAGetVideoEntry(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    OUT RvUint32                *videoEntry);

#ifdef __cplusplus
}
#endif

#endif /* _RV_GEF_MONA_H_ */

