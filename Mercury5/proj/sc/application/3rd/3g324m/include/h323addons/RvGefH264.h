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

#ifndef _RV_GEF_H264_H_
#define _RV_GEF_H264_H_


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

/* H.264 definitions according to the H.241 Draft. */

#define RV_GEF_H264_CAPABILITY_IDENTIFIER "itu-t(0) recommendation(0) h(8) 241(241) specificVideoCodecCapabilities(0) h264(0) generic-capabilities(1)"

#define RV_GEF_H264_PARAMETER_IDENTIFIER_PROFILE 41
#define RV_GEF_H264_PARAMETER_IDENTIFIER_LEVEL 42
#define RV_GEF_H264_PARAMETER_IDENTIFIER_DECODER_CONFIGURATION_INFORMATION 43
#define RV_GEF_H264_PARAMETER_IDENTIFIER_ACCEPT_REDUNDANT_SLICES 44
#define RV_GEF_H264_PARAMETER_IDENTIFIER_NAL_ALIGNED_MODE 45
#define RV_GEF_H264_PARAMETER_IDENTIFIER_PROFILE_IOP 46
#define RV_GEF_H264_PARAMETER_IDENTIFIER_CUSTOM_MAX_MBPS 3
#define RV_GEF_H264_PARAMETER_IDENTIFIER_CUSTOM_MAX_FS 4
#define RV_GEF_H264_PARAMETER_IDENTIFIER_CUSTOM_MAX_DPB 5
#define RV_GEF_H264_PARAMETER_IDENTIFIER_CUSTOM_MAX_BR_AND_CPB 6
#define RV_GEF_H264_PARAMETER_IDENTIFIER_MAX_STATIC_MBPS 7
#define RV_GEF_H264_PARAMETER_IDENTIFIER_MAX_RCMD_NAL_UNIT_SIZE 8
#define RV_GEF_H264_PARAMETER_IDENTIFIER_MAX_NAL_UNIT_SIZE 9

/*-----------------------------------------------------------------------*/
/*                           FUNCTIONS HEADERS                           */
/*-----------------------------------------------------------------------*/


/******************************************************************************
 * RvGefH264Build
 * ----------------------------------------------------------------------------
 * General: Builds the GenericCapability ASN.1 node ID for H.264 codec. After 
 *          this node ID is built, it is the responsibility of the application 
 *          to delete it. Note that the Capability Identifier has already been 
 *          set to this node ID.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt             - PVT handle for building ASN.1 node IDs.
 * Output: h264NodeId       - The new GenericCapability node ID for the H.264 codec.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264Build(
    IN  HPVT                    hPvt,
    OUT RvPvtNodeId             *h264NodeId);



/******************************************************************************
 * RvGefH264SetMaxBitRate
 * ----------------------------------------------------------------------------
 * General: Sets the maxBitRate parameter to the GenericCapability ASN.1 node ID 
 *          for the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 *         maxBitRate           - The maxBitRate parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264SetMaxBitRate(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         mpegNodeId,
    IN  RvUint32                            maxBitRate);


/******************************************************************************
 * RvGefH264GetMaxBitRate
 * ----------------------------------------------------------------------------
 * General: Gets the maxBitRate parameter from the GenericCapability ASN.1 
 *          node ID of the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 * Output: pMaxBitRate          - The maxBitRate parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264GetMaxBitRate(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    OUT RvUint32                            *pMaxBitRate);


/******************************************************************************
 * RvGefH264AddProfile
 * ----------------------------------------------------------------------------
 * General: Adds the profile parameter to the GenericCapability ASN.1 node ID 
 *          for the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 *         profileAndLevel      - The profile parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264AddProfile(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    IN  RvUint8                             profile);


/******************************************************************************
 * RvGefH264GetProfile
 * ----------------------------------------------------------------------------
 * General: Gets the profile parameter from the GenericCapability ASN.1 node ID 
 *          of the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 * Output: pProfile             - The profile parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264GetProfile(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    OUT RvUint8                             *pProfile);


/******************************************************************************
 * RvGefH264AddLevel
 * ----------------------------------------------------------------------------
 * General: Adds the level parameter to the GenericCapability ASN.1 node ID 
 *          for the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 *         level                - The level parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264AddLevel(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    IN  RvUint16                            level);


/******************************************************************************
 * RvGefH264GetLevel
 * ----------------------------------------------------------------------------
 * General: Gets the level parameter from the GenericCapability ASN.1 node ID 
 *          of the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 * Output: pLevel               - The level parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264GetLevel(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    OUT RvUint16                            *pLevel);


/******************************************************************************
 * RvGefH264AddCustomMaxMBPS
 * ----------------------------------------------------------------------------
 * General: Adds the customMaxMBPS parameter to the GenericCapability ASN.1 
 *          node ID for the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 *         customMaxMBPS        - The customMaxMBPS parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264AddCustomMaxMBPS(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    IN  RvUint16                            customMaxMBPS);


/******************************************************************************
 * RvGefH264GetCustomMaxMBPS
 * ----------------------------------------------------------------------------
 * General: Gets the customMaxMBPS parameter from the GenericCapability 
 *          ASN.1 node ID of the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 * Output: pCustomMaxMBPS       - The customMaxMBPS parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264GetCustomMaxMBPS(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    OUT RvUint16                            *pCustomMaxMBPS);


/******************************************************************************
 * RvGefH264AddCustomMaxFS
 * ----------------------------------------------------------------------------
 * General: Adds the customMaxFS parameter to the GenericCapability ASN.1 node ID 
 *          for the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 *         customMaxFS          - The customMaxFS parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264AddCustomMaxFS(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    IN  RvUint16                            customMaxFS);


/******************************************************************************
 * RvGefH264GetCustomMaxFS
 * ----------------------------------------------------------------------------
 * General: Gets the customMaxFS parameter from the GenericCapability 
 *          ASN.1 node ID of the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 * Output: pCustomMaxFS         - The customMaxFS parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264GetCustomMaxFS(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    OUT RvUint16                            *pCustomMaxFS);


/******************************************************************************
 * RvGefH264AddCustomMaxDPB
 * ----------------------------------------------------------------------------
 * General: Adds the customMaxDPB parameter to the GenericCapability 
 *          ASN.1 node ID for the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 *         customMaxDPB         - The customMaxDPB parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264AddCustomMaxDPB(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    IN  RvUint16                            customMaxDPB);


/******************************************************************************
 * RvGefH264GetCustomMaxDPB
 * ----------------------------------------------------------------------------
 * General: Gets the customMaxDPB parameter from the GenericCapability 
 *          ASN.1 node ID of the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 * Output: pCustomMaxDPB        - The customMaxDPB parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264GetCustomMaxDPB(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    OUT RvUint16                            *pCustomMaxDPB);


/******************************************************************************
 * RvGefH264AddCustomMaxBRAndCPB
 * ----------------------------------------------------------------------------
 * General: Adds the customMaxBRAndCPB parameter to the GenericCapability 
 *          ASN.1 node ID for the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 *         customMaxBRAndCPB    - The customMaxBRAndCPB parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264AddCustomMaxBRAndCPB(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    IN  RvUint16                            customMaxBRAndCPB);


/******************************************************************************
 * RvGefH264GetCustomMaxBRAndCPB
 * ----------------------------------------------------------------------------
 * General: Gets the customMaxBRAndCPB parameter from the GenericCapability 
 *          ASN.1 node ID of the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 * Output: pCustomMaxBRAndCPB   - The customMaxBRAndCPB parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264GetCustomMaxBRAndCPB(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    OUT RvUint16                            *pCustomMaxBRAndCPB);

/******************************************************************************
 * RvGefH264AddMaxStaticMBPS
 * ----------------------------------------------------------------------------
 * General: Adds the maxStaticMBPS parameter to the GenericCapability 
 *          ASN.1 node ID for the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 *         maxStaticMBPS        - The maxStaticMBPS parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264AddMaxStaticMBPS(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    IN  RvUint16                            maxStaticMBPS);

/******************************************************************************
 * RvGefH264GetMaxStaticMBPS
 * ----------------------------------------------------------------------------
 * General: Gets the maxStaticMBPS parameter from the GenericCapability 
 *          ASN.1 node ID of the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 * Output: pMaxStaticMBPS       - The maxStaticMBPS parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264GetMaxStaticMBPS(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    OUT RvUint16                            *pMaxStaticMBPS);

/******************************************************************************
 * RvGefH264AddMaxRcmdNalUnitSize
 * ----------------------------------------------------------------------------
 * General: Adds the maxRcmdNalUnitSize parameter to the GenericCapability 
 *          ASN.1 node ID for the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 *         maxRcmdNalUnitSize   - The maxRcmdNalUnitSize parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264AddMaxRcmdNalUnitSize(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    IN  RvUint16                            maxRcmdNalUnitSize);

/******************************************************************************
 * RvGefH264GetMaxRcmdNalUnitSize
 * ----------------------------------------------------------------------------
 * General: Gets the maxRcmdNalUnitSize parameter from the GenericCapability 
 *          ASN.1 node ID of the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 * Output: pMaxRcmdNalUnitSize  - The maxRcmdNalUnitSize parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264GetMaxRcmdNalUnitSize(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    OUT RvUint16                            *pMaxRcmdNalUnitSize);

/******************************************************************************
 * RvGefH264AddMaxNalUnitSize
 * ----------------------------------------------------------------------------
 * General: Adds the maxNalUnitSize parameter to the GenericCapability 
 *          ASN.1 node ID for the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 *         maxNalUnitSize       - The maxNalUnitSize parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264AddMaxNalUnitSize(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    IN  RvUint16                            maxNalUnitSize);

/******************************************************************************
 * RvGefH264GetMaxNalUnitSize
 * ----------------------------------------------------------------------------
 * General: Gets the maxNalUnitSize parameter from the GenericCapability 
 *          ASN.1 node ID of the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 * Output: pMaxNalUnitSize      - The maxNalUnitSize parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264GetMaxNalUnitSize(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    OUT RvUint16                            *pMaxNalUnitSize);

/******************************************************************************
 * RvGefH264AddDecoderConfigurationInformation
 * ----------------------------------------------------------------------------
 * General: Adds the decoderConfigurationInformation parameter to the 
 *          GenericCapability ASN.1 node ID for the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 *         pDecoderConfInfo     - The decoderConfigurationInformation parameter.
 *         decoderConfInfoSize  - The size of the pDecoderConfInfo string, in bytes.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264AddDecoderConfigurationInformation(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    IN  const RvUint8                       *pDecoderConfInfo,
    IN  RvUint32                            decoderConfInfoSize);

/******************************************************************************
 * RvGefH264GetDecoderConfigurationInformation
 * ----------------------------------------------------------------------------
 * General: Sets the decoderConfigurationInformation parameter to the GenericCapability
 *          ASN.1 node ID for the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 * Output: pDecoderConfInfo     - The decoderConfigurationInformation parameter.
 *                                The string should be allocated by the application.
 *                                The pDecoderConfInfoSize argument will be filled with
 *                                the actual size of the string. If this argument is set 
 *                                to NULL, the application can use the size returned in 
 *                                pDecoderConfInfoSize and call this function again with  
 *                                the buffer allocated in the correct size.
 *         pDecoderConfInfoSize - The size of the pDecoderConfInfo string, in bytes.
 *                                Use this argument to pass the size of pDecoderConfInfo
 *                                that was allocated.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264GetDecoderConfigurationInformation(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    OUT RvUint8                             *pDecoderConfInfo,
    INOUT RvUint32                          *pDecoderConfInfoSize);

/******************************************************************************
 * RvGefH264AddAcceptRedundantSlices
 * ----------------------------------------------------------------------------
 * General: Adds the acceptRedundantSlices parameter to the GenericCapability 
 *          ASN.1 node ID for the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId                - The GenericCapability node ID for the H.264 codec.
 *         bAcceptRedundantSlices    - The acceptRedundantSlices parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264AddAcceptRedundantSlices(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    IN  RvBool                              bAcceptRedundantSlices);

/******************************************************************************
 * RvGefH264GetAcceptRedundantSlices
 * ----------------------------------------------------------------------------
 * General: Gets the acceptRedundantSlices parameter from the GenericCapability 
 *          ASN.1 node ID of the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId                - The GenericCapability node ID for the H.264 codec.
 * Output: pbAcceptRedundantSlices   - The acceptRedundantSlices parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264GetAcceptRedundantSlices(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    OUT RvBool                              *pbAcceptRedundantSlices);

/******************************************************************************
 * RvGefH264AddNalAlignedMode
 * ----------------------------------------------------------------------------
 * General: Adds the nalAlignedMode parameter to the GenericCapability 
 *          ASN.1 node ID for the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId                - The GenericCapability node ID for the H.264 codec.
 *         bNalAlignedMode           - The nalAlignedMode parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264AddNalAlignedMode(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    IN  RvBool                              bNalAlignedMode);


/******************************************************************************
 * RvGefH264GetNalAlignedMode
 * ----------------------------------------------------------------------------
 * General: Gets the nalAlignedMode parameter from the GenericCapability 
 *          ASN.1 node ID of the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId                - The GenericCapability node ID for the H.264 codec.
 * Output: pbNalAlignedMode          - The nalAlignedMode parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264GetNalAlignedMode(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    OUT RvBool                              *pbNalAlignedMode);

/******************************************************************************
 * RvGefH264AddProfileIOP
 * ----------------------------------------------------------------------------
 * General: Adds the profileIOP parameter to the GenericCapability 
 *          ASN.1 node ID for the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 *         profileIOP		    - The profileIOP parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264AddProfileIOP(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    IN  RvUint8                             profileIOP);

/******************************************************************************
 * RvGefH264GetProfileIOP
 * ----------------------------------------------------------------------------
 * General: Gets the profileIOP parameter from the GenericCapability 
 *          ASN.1 node ID of the H.264 codec.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h264NodeId           - The GenericCapability node ID for the H.264 codec.
 * Output: pProfileIOP          - The profileIOP parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH264GetProfileIOP(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h264NodeId,
    OUT RvUint8                             *pProfileIOP);



#ifdef __cplusplus
}
#endif

#endif /* _RV_GEF_H264_H_ */
