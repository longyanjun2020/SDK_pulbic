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

#ifndef _RV_GEF_H239_H_
#define _RV_GEF_H239_H_


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

/* H.239 definitions according to the H.239 draft. */

#define RV_GEF_H239_CONTROL_CAPABILITY_IDENTIFIER "itu-t(0) recommendation(0) h(8) 239 generic-capabilities(1) h239ControlCapability(1)"
#define RV_GEF_H239_EXTENDED_VIDEO_CAPABILITY_IDENTIFIER "itu-t(0) recommendation(0) h(8) 239 generic-capabilities(1) h239ExtendedVideoCapability(2)"
#define RV_GEF_H239_MESSAGE_IDENTIFIER "itu-t(0) recommendation(0) h(8) 239 generic-message(2)" 

#define RV_GEF_H239_PARAMETER_IDENTIFIER_ROLE_LABEL 1

    
#define RV_GEF_H239_SUB_MESSAGE_IDENTIFIER_FLOW_CONTROL_RELEASE_REQUEST 1
#define RV_GEF_H239_SUB_MESSAGE_IDENTIFIER_FLOW_CONTROL_RELEASE_RESPONSE 2
#define RV_GEF_H239_SUB_MESSAGE_IDENTIFIER_PRESENTATION_TOKEN_REQUEST 3
#define RV_GEF_H239_SUB_MESSAGE_IDENTIFIER_PRESENTATION_TOKEN_RESPONSE 4
#define RV_GEF_H239_SUB_MESSAGE_IDENTIFIER_PRESENTATION_TOKEN_RELEASE 5
#define RV_GEF_H239_SUB_MESSAGE_IDENTIFIER_PRESENTATION_TOKEN_INDICATE_OWNER 6

#define RV_GEF_H239_MESSAGE_CONTENT_PARAMETER_IDENTIFIER_RESERVED 0
#define RV_GEF_H239_MESSAGE_CONTENT_PARAMETER_IDENTIFIER_BIT_RATE 41
#define RV_GEF_H239_MESSAGE_CONTENT_PARAMETER_IDENTIFIER_CHANNEL_ID 42
#define RV_GEF_H239_MESSAGE_CONTENT_PARAMETER_IDENTIFIER_SYMMETRY_BREAKING 43
#define RV_GEF_H239_MESSAGE_CONTENT_PARAMETER_IDENTIFIER_TERMINAL_LABEL 44
#define RV_GEF_H239_MESSAGE_CONTENT_PARAMETER_IDENTIFIER_ACKNOWLEDGE 126
#define RV_GEF_H239_MESSAGE_CONTENT_PARAMETER_IDENTIFIER_REJECT 127

/* RvGefH239GenericMessageType
 * ------------------------------------------------------------------------
 * This enumeration describes the GenericMessage types for the H.239 
 * codec supported by the GEF package.
 */
typedef enum
{
    RvGefH239GenericMessageTypeUnknown = -1,
    RvGefH239GenericMessageTypeFlowControlReleaseRequest = 1,
    RvGefH239GenericMessageTypeFlowControlReleaseResponse,
    RvGefH239GenericMessageTypePresentationTokenRequest,
    RvGefH239GenericMessageTypePresentationTokenResponse,
    RvGefH239GenericMessageTypePresentationTokenRelease,
    RvGefH239GenericMessageTypePresentationTokenIndicateOwner
    
} RvGefH239GenericMessageType;

/*-----------------------------------------------------------------------*/
/*                           FUNCTIONS HEADERS                           */
/*-----------------------------------------------------------------------*/


/******************************************************************************
 * RvGefH239ControlCapabilityBuild
 * ----------------------------------------------------------------------------
 * General: Builds the GenericCapability ASN.1 node ID for H.239 Control 
 *          Capability. If this node ID is built, it is the responsibility 
 *          of the application to delete it. Note that the Capability Identifier 
 *          has already been set to this node ID.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt              - PVT handle for building ASN.1 node IDs.
 * Output: h239ControlNodeId - The new GenericCapability node ID for H.239 
 *                             Control capability.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH239ControlCapabilityBuild(
    IN  HPVT                    hPvt,
    OUT RvPvtNodeId             *h239ControlNodeId);



/******************************************************************************
 * RvGefH239ExtendedVideoCapabilityBuild
 * ----------------------------------------------------------------------------
 * General: Builds the GenericCapability ASN.1 node ID for H.239 extended 
 *          video capability. This capability is included in the 
 *          videoCapabilityExtension, which is part of the ExtendedVideoCapability 
 *          node ID. If this node ID is built, it is the responsibility of 
 *          the application to delete it.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                    - PVT handle for building ASN.1 node IDs.
 * Output: h239ExtendedVideoNodeId - The new GenericCapability node ID for H.239 
 *                                   Control capability.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH239ExtendedVideoCapabilityBuild(
    IN  HPVT                    hPvt,
    OUT RvPvtNodeId             *h239ExtendedVideoNodeId);



/******************************************************************************
 * RvGefH239AddRoleLabel
 * ----------------------------------------------------------------------------
 * General: Adds the roleLabel parameter to the GenericCapability ASN.1 node ID 
 *          for the H.239 capability. Note that this capability is the 
 *          H.239ExtendedVideoCapability and not the h239ControlCapability.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h239NodeId           - The GenericCapability node ID for H.239.
 *         roleLabel            - The roleLabel parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH239AddRoleLabel(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h239NodeId,
    IN  RvUint8                             roleLabel);


/******************************************************************************
 * RvGefH239GetRoleLabel
 * ----------------------------------------------------------------------------
 * General: Gets the roleLabel parameter from the GenericCapability 
 *          ASN.1 node ID of the H.239 capability. Note that this capability 
 *          is the H.239ExtendedVideoCapability and not the h239ControlCapability.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         h239NodeId           - The GenericCapability node ID for H.239.
 * Output: pRoleLabel           - The profile parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH239GetRoleLabel(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         h239NodeId,
    OUT RvUint8                             *pRoleLabel);


/********************************************************************************
 *
 * Generic Messages
 * 
 ********************************************************************************/

/******************************************************************************
 * RvGefH239GetMessageType
 * ----------------------------------------------------------------------------
 * General: Gets the GenericMessage type of the given H.239 GenericMessage node.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         genericMessageNodeId - The GenericMessage node ID.
 * Output: pH239MessageType     - The H.239 GenericMessage type of the genericMessageNodeId.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH239GetMessageType(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericMessageNodeId,
    OUT RvGefH239GenericMessageType         *pH239MessageType);



/******************************************************************************
 * RvGefH239BuildFlowControlReleaseRequest
 * ----------------------------------------------------------------------------
 * General: Builds the flowControlReleaseRequest generic message node ID. 
 *          Note that the application should first build the GenericMessage 
 *          node ID, using the function cmBuildMultimediaSystemControlMessage().
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                  - PVT handle for handling ASN.1 node IDs.
 *         genericMessageNodeId  - The GenericMessage node ID.  
 *                                 This node ID should be built previously  
 *                                 by the application using the function 
 *                                 cmBuildMultimediaSystemControlMessage().
 *         channelId             - The channelId parameter of the message.
 *         bitRate               - The bitRate parameter of the message.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH239BuildFlowControlReleaseRequest(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericMessageNodeId,
    IN  RvUint16                            channelId,
    IN  RvUint16                            bitRate);

/******************************************************************************
 * RvGefH239GetFlowControlReleaseRequestParams
 * ----------------------------------------------------------------------------
 * General: Gets the parameters from the flowControlReleaseRequest generic 
 *          message node ID. Note that this function must be called after 
 *          verifying that the message is in fact flowControlReleaseRequest. 
 *          This may be done by calling to the RvGefH239GetMessageType() function.
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                  - PVT handle for handling ASN.1 node IDs.
 *         genericMessageNodeId  - The GenericMessage node ID.
 * Output: pChannelId            - The channelId parameter of the message.
 *         pBitRate              - The bitRate parameter of the message.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH239GetFlowControlReleaseRequestParams(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericMessageNodeId,
    OUT RvUint16                            *pChannelId,
    OUT RvUint16                            *pBitRate);

/******************************************************************************
 * RvGefH239BuildFlowControlReleaseResponse
 * ----------------------------------------------------------------------------
 * General: Builds the flowControlReleaseResponse generic message node ID. 
 *          Note that the application should first build the GenericMessage 
 *          node ID, using the function cmBuildMultimediaSystemControlMessage().
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                  - PVT handle for handling ASN.1 node IDs.
 *         genericMessageNodeId  - The GenericMessage node ID. This node ID should 
 *                                 be built previously by the application using the 
 *                                 function cmBuildMultimediaSystemControlMessage().
 *         bAcknowledge          - If this parameter is RV_TRUE, the acknowledge 
 *                                 parameter is set to the message. Otherwise, 
 *                                 the reject parameter is set.
 *         channelId             - The channelId parameter of the message.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH239BuildFlowControlReleaseResponse(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericMessageNodeId,
    IN  RvBool                              bAcknowledge,
    IN  RvUint16                            channelId);

/******************************************************************************
 * RvGefH239GetFlowControlReleaseResponseParams
 * ----------------------------------------------------------------------------
 * General: Gets the parameters from the flowControlReleaseResponse generic 
 *          message node ID. Note that this function must be called after 
 *          verifying that the message is in fact flowControlReleaseResponse. 
 *          This may be done by calling to the RvGefH239GetMessageType() function.
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                  - PVT handle for handling ASN.1 node IDs.
 *         genericMessageNodeId  - The GenericMessage node ID.
 * Output: pAcknowledge          - The acknowledge parameter of the message.
 *         pChannelId            - The channelId parameter of the message.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH239GetFlowControlReleaseResponseParams(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericMessageNodeId,
    OUT RvBool                              *pAcknowledge,
    OUT RvUint16                            *pChannelId);


/******************************************************************************
 * RvGefH239BuildPresentationTokenRequest
 * ----------------------------------------------------------------------------
 * General: Builds the presentationTokenRequest generic message node ID. 
 *          Note that the application should first build the GenericMessage 
 *          node ID, using the function cmBuildMultimediaSystemControlMessage().
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                  - PVT handle for handling ASN.1 node IDs.
 *         genericMessageNodeId  - The GenericMessage node ID. This node ID should
 *                                 be built previously by the application using the 
 *                                 function cmBuildMultimediaSystemControlMessage().
 *         terminalLabel         - The terminalLabel parameter of the message.
 *         channelId             - The channelId parameter of the message.
 *         symmetryBreaking      - The symmetryBreaking parameter of the message.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH239BuildPresentationTokenRequest(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericMessageNodeId,
    IN  RvUint16                            terminalLabel,
    IN  RvUint16                            channelId,
    IN  RvUint8                             symmetryBreaking);

/******************************************************************************
 * RvGefH239GetPresentationTokenRequestParams
 * ----------------------------------------------------------------------------
 * General: Gets the parameters from the presentationTokenRequest generic message 
 *          node ID. Note that this function must be called after verifying that 
 *          the message is in fact presentationTokenRequest. This may be done by 
 *          calling to the RvGefH239GetMessageType() function.
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                  - PVT handle for handling ASN.1 node ids.
 *         genericMessageNodeId  - The GenericMessage node id.
 * Output: pTerminalLabel        - The terminalLabel parameter of the message.
 *         pChannelId            - The pChannelId parameter of the message.
 *         pSymmetryBreaking     - The pSymmetryBreaking parameter of the message.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH239GetPresentationTokenRequestParams(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericMessageNodeId,
    OUT RvUint16                            *pTerminalLabel,
    OUT RvUint16                            *pChannelId,
    OUT RvUint8                             *pSymmetryBreaking);

/******************************************************************************
 * RvGefH239BuildPresentationTokenResponse
 * ----------------------------------------------------------------------------
 * General: Builds the presentationTokenResponse generic message node ID. Note 
 *          that the application should first build the GenericMessage node ID, 
 *          using the function cmBuildMultimediaSystemControlMessage().
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                  - PVT handle for handling ASN.1 node IDs.
 *         genericMessageNodeId  - The GenericMessage node ID. This node ID should 
 *                                 be built previously by the application using the 
 *                                 function cmBuildMultimediaSystemControlMessage().
 *         bAcknowledge          - If this parameter is RV_TRUE, the acknowledge 
 *                                 parameter is set to the message. Otherwise, the 
 *                                 reject parameter is set.
 *         terminalLabel         - The terminalLabel parameter of the message.
 *         channelId             - The channelId parameter of the message.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH239BuildPresentationTokenResponse(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericMessageNodeId,
    IN  RvBool                              bAcknowledge,
    IN  RvUint16                            terminalLabel,
    IN  RvUint16                            channelId);

/******************************************************************************
 * RvGefH239GetPresentationTokenResponseParams
 * ----------------------------------------------------------------------------
 * General: Gets the parameters from the presentationTokenResponse generic message 
 *          node ID. Note that this function must be called after verifying that 
 *          the message is in fact presentationTokenResponse. This may be done by 
 *          calling to the RvGefH239GetMessageType() function.
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                  - PVT handle for handling ASN.1 node IDs.
 *         genericMessageNodeId  - The GenericMessage node ID.
 * Output: pAcknowledge          - The acknowledge parameter of the message.
 *         pTerminalLabel        - The terminalLabel parameter of the message.
 *         pChannelId            - The channelId parameter of the message.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH239GetPresentationTokenResponseParams(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericMessageNodeId,
    OUT RvBool                              *pAcknowledge,
    OUT RvUint16                            *pTerminalLabel,
    OUT RvUint16                            *pChannelId);


/******************************************************************************
 * RvGefH239BuildPresentationTokenRelease
 * ----------------------------------------------------------------------------
 * General: Builds the presentationTokenRelease generic message node ID. Note that 
 *          the application should first build the GenericMessage node ID, using 
 *          the function cmBuildMultimediaSystemControlMessage().
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                  - PVT handle for handling ASN.1 node IDs.
 *         genericMessageNodeId  - The GenericMessage node ID. This node ID should 
 *                                 be built previously by the application using the 
 *                                 function cmBuildMultimediaSystemControlMessage().
 *         terminalLabel         - The terminalLabel parameter of the message.
 *         channelId             - The channelId parameter of the message.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH239BuildPresentationTokenRelease(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericMessageNodeId,
    IN  RvUint16                            terminalLabel,
    IN  RvUint16                            channelId);

/******************************************************************************
 * RvGefH239GetPresentationTokenReleaseParams
 * ----------------------------------------------------------------------------
 * General: Gets the parameters from the presentationTokenRelease generic message 
 *          node ID. Note that this function must be called after verifying that 
 *          the message is in fact presentationTokenRelease. This may be done by 
 *          calling to the RvGefH239GetMessageType() function.
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                  - PVT handle for handling ASN.1 node IDs.
 *         genericMessageNodeId  - The GenericMessage node ID.
 * Output: pTerminalLabel        - The terminalLabel parameter of the message.
 *         pChannelId            - The channelId parameter of the message.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH239GetPresentationTokenReleaseParams(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericMessageNodeId,
    OUT RvUint16                            *pTerminalLabel,
    OUT RvUint16                            *pChannelId);


/******************************************************************************
 * RvGefH239BuildPresentationTokenIndicateOwner
 * ----------------------------------------------------------------------------
 * General: Builds the presentationTokenIndicateOwner generic message node ID.  
 *          Note that the application should first build the GenericMessage node ID, 
 *          using the function cmBuildMultimediaSystemControlMessage().
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                  - PVT handle for handling ASN.1 node IDs.
 *         genericMessageNodeId  - The GenericMessage node ID. This node ID should 
 *                                 be built previously by the application using the 
 *                                 function cmBuildMultimediaSystemControlMessage().
 *         terminalLabel         - The terminalLabel parameter of the message.
 *         channelId             - The channelId parameter of the message.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH239BuildPresentationTokenIndicateOwner(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericMessageNodeId,
    IN  RvUint16                            terminalLabel,
    IN  RvUint16                            channelId);

/******************************************************************************
 * RvGefH239GetPresentationTokenIndicateOwnerParams
 * ----------------------------------------------------------------------------
 * General: Gets the parameters from the presentationTokenIndicateOwner generic 
 *          message node ID. Note that this function must be called after verifying 
 *          that the message is in fact presentationTokenIndicateOwner. This may be 
 *          done by calling to the RvGefH239GetMessageType() function.
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                  - PVT handle for handling ASN.1 node IDs.
 *         genericMessageNodeId  - The GenericMessage node ID.
 * Output: pTerminalLabel        - The terminalLabel parameter of the message.
 *         pChannelId            - The channelId parameter of the message.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH239GetPresentationTokenIndicateOwnerParams(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericMessageNodeId,
    OUT RvUint16                            *pTerminalLabel,
    OUT RvUint16                            *pChannelId);



#ifdef __cplusplus
}
#endif

#endif /* _RV_GEF_H239_H_ */
