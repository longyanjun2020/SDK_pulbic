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

#ifndef _RV_GEF_H249_H_
#define _RV_GEF_H249_H_


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

/* H249 Annex A (Navigation Keys) definitions  */
#define RV_GEF_H249_NAVIGATION_KEY_PARAMETER_IDENTIFIER_KEY_ID                      1

/* H249 Annex B (Soft Keys) definitions  */
#define RV_GEF_H249_SOFT_KEYS_PARAMETER_IDENTIFIER_NUMBER_OF_SOFT_KEYS              1
#define RV_GEF_H249_SOFT_KEYS_PARAMETER_IDENTIFIER_KEY_ID                           2
#define RV_GEF_H249_SOFT_KEYS_PARAMETER_IDENTIFIER_KEY_NAME                         3

/* H249 Annex C (Pointing Device) definitions  */
#define RV_GEF_H249_POINTING_DEVICE_PARAMETER_IDENTIFIER_X                          1
#define RV_GEF_H249_POINTING_DEVICE_PARAMETER_IDENTIFIER_Y                          2
#define RV_GEF_H249_POINTING_DEVICE_PARAMETER_IDENTIFIER_ACTION                     3
#define RV_GEF_H249_POINTING_DEVICE_PARAMETER_IDENTIFIER_BUTTON_ID                  4
#define RV_GEF_H249_POINTING_DEVICE_PARAMETER_IDENTIFIER_NUMBER_OF_CLICKS           5

/* H249 Annex D (Modal Interface) definitions  */
#define RV_GEF_H249_MODAL_INTERFACE_PARAMETER_IDENTIFIER_USER_INPUT_ELEMENT_ID      1
#define RV_GEF_H249_MODAL_INTERFACE_PARAMETER_IDENTIFIER_SET_REMOTE_CONTROL_MODE    2

#define MAX_KEY_H249_NAME_SIZE (128)

/*-----------------------------------------------------------------------*/
/*                           FUNCTIONS HEADERS                           */
/*-----------------------------------------------------------------------*/

/******************************************************************************
 * RvGefH249NavigationKeyCapabilityBuild
 * ----------------------------------------------------------------------------
 * General: Builds the GenericCapability ASN.1 node for the Navigation Key capability. 
 *          After this node ID is built, it is the responsibility of the application 
 *          to delete it. Note that the Capability Identifier has already been set 
 *          to this node.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 * Output: navigationKeyNodeId       - The new GenericCapability node ID for the 
 *                                     Navigation Key capability.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249NavigationKeyCapabilityBuild(
    IN  HPVT                    hPvt,
    OUT RvPvtNodeId             *navigationKeyNodeId);

/******************************************************************************
 * RvGefH249SoftKeysCapabilityBuild
 * ----------------------------------------------------------------------------
 * General: Builds the GenericCapability ASN.1 node for the Soft Keys capability. 
 *          After this node ID is built, it is the responsibility of the application 
 *          to delete it. Note that the Capability Identifier has already been set 
 *          to this node.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 * Output: softKeysNodeId            - The new GenericCapability node ID for the 
 *                                     Soft Keys capability.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249SoftKeysCapabilityBuild(
    IN  HPVT                    hPvt,
    OUT RvPvtNodeId             *softKeysNodeId);

/******************************************************************************
 * RvGefH249SoftKeysSetNumberOfSoftKeys
 * ----------------------------------------------------------------------------
 * General: Sets the Number of Soft Keys parameter in the Soft Key capability node.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         softKeysNodeId            - The GenericCapability node ID for the 
 *                                     Soft Keys capability.
 *         numberOfSoftKeys          - The number of supported soft keys.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249SoftKeysSetNumberOfSoftKeys(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             softKeysNodeId,
    IN  RvUint32                numberOfSoftKeys);

/******************************************************************************
 * RvGefH249SoftKeysGetNumberOfSoftKeys
 * ----------------------------------------------------------------------------
 * General: Gets the value of the Number of Soft Keys parameter from the 
 *          Soft Keys capability node.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         softKeysNodeId            - The GenericCapability node ID for the 
 *                                     Soft Key capability.
 * Output: numberOfSoftKeys          - The number of supported soft keys.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249SoftKeysGetNumberOfSoftKeys(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             softKeysNodeId,
    OUT RvUint32                *numberOfSoftKeys);

/******************************************************************************
 * RvGefH249PointingDeviceCapabilityBuild
 * ----------------------------------------------------------------------------
 * General: Builds the GenericCapability ASN.1 node for the Pointing Device 
 *          capability. After this node ID is built, it is the responsibility 
 *          of the application to delete it. Note that the Capability Identifier 
 *          has already been set to this node.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 * Output: pointingDeviceNodeId      - The new GenericCapability node ID for the 
 *                                     Pointing Device capability.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249PointingDeviceCapabilityBuild(
    IN  HPVT                    hPvt,
    OUT RvPvtNodeId             *pointingDeviceNodeId);

/******************************************************************************
 * RvGefH249ModalinterfaceCapabilityBuild
 * ----------------------------------------------------------------------------
 * General: Builds the GenericCapability ASN.1 node for the Modal Interface 
 *          capability. After this node ID is built, it is the responsibility 
 *          of the application to delete it. Note that the Capability Identifier 
 *          has already been set to this node.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 * Output: modalInterfaceNodeId      - The new GenericCapability node ID for 
 *                                     the Modal Interface capability.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249ModalinterfaceCapabilityBuild(
    IN  HPVT                    hPvt,
    OUT RvPvtNodeId             *modalInterfaceNodeId);

/******************************************************************************
 * RvGefH249ModalInterfaceCapAddUserInputElementId
 * ----------------------------------------------------------------------------
 * General: Adds a User Input Element ID parameter to the Modal Interface 
 *          capability node.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         modalInterfaceNodeId      - The GenericCapability node ID for the 
 *                                     Modal Interface capability.
 *         userElementId             - The user input element ID, one of the 
 *                                     H.249 elements capability:
 *                                     RvGefMessageTypeH249NavigationKey or
 *                                     RvGefMessageTypeH249SoftKeys or
 *                                     RvGefMessageTypeH249PointingDevice
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249ModalInterfaceCapAddUserInputElementId(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             modalInterfaceNodeId,
    IN  RvGefMessageType        userElementId);

/******************************************************************************
 * RvGefH249ModalInterfaceCapGetUserInputElementId
 * ----------------------------------------------------------------------------
 * General: Gets the User Input Element ID parameter from the Modal Interface 
 *          capability node.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                         - PVT handle for building ASN.1 node IDs.
 *         modalInterfaceNodeId         - The GenericCapability node ID for 
 *                                        the Modal Interface capability.
 *         userElementIdArray           - An array allocated by the application 
 *                                        for all userInputElemenIds.
 *         userElementIdArraySize       - The size of the array allocated by the 
 *                                        application.
 * Output: userElementIdArray           - The userInputElemenIds found in the
 *                                  .     capability message.
 *         userElementIdArray           - The number of userInputElemenIds 
 *                                  .     found in the capability message.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249ModalInterfaceCapGetUserInputElementId(
    IN    HPVT                  hPvt,
    IN    RvPvtNodeId           modalInterfaceNodeId,
    INOUT RvGefMessageType      *userElementIdArray,
    INOUT RvUint32              *userElementIdArraySize);

/******************************************************************************
 * RvGefH249NavigationKeyIndicationBuild
 * ----------------------------------------------------------------------------
 * General: Builds the genericInformation ASN.1 Navigation Key indication node. 
 *          After this node ID is built, it is the responsibility of the 
 *          application to delete it. Note that the Capability Identifier has 
 *          already been set to this node.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 * Output: genericInformationNodeId  - The new genericInformation node ID for 
 *                                     the Navigation Key indication.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249NavigationKeyIndicationBuild(
    IN  HPVT                    hPvt,
    OUT RvPvtNodeId             *genericInformationNodeId);

/******************************************************************************
 * RvGefH249NavigationKeySetKeyId
 * ----------------------------------------------------------------------------
 * General: Sets the Key ID parameter in the messageContent subfield of the 
 *          genericInformation node for the Navigation Key indication.  
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID 
 *                                     of the Navigation Key indication.
 *         keyIdValue                - Key ID value.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249NavigationKeySetKeyId(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    IN  RvUint32                keyIdValue);

/******************************************************************************
 * RvGefH249NavigationKeyGetKeyId
 * ----------------------------------------------------------------------------
 * General: Gets the Key ID parameter from the messageContent subfield of the 
 *          genericInformation node of the Navigation Key indication. 
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID
 *                                     of the Navigation Key indication.
 * Output: keyIdValue                - Key ID value. 
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249NavigationKeyGetKeyId(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    OUT RvUint32                *keyIdValue);

/******************************************************************************
 * RvGefH249SoftKeysIndicationBuild
 * ----------------------------------------------------------------------------
 * General: Builds the genericInformation ASN.1 Soft Keys indication node. 
 *          After this node ID was built, it is the responsibility of the 
 *          application to delete it. Note that the Capability Identifier has 
 *          already been set to this node.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 * Output: genericInformationNodeId  - The new genericInformation node ID 
 *                                     for the Soft Keys indication.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249SoftKeysIndicationBuild(
    IN  HPVT                    hPvt,
    OUT RvPvtNodeId             *genericInformationNodeId);

/******************************************************************************
 * RvGefH249SoftKeysSetKeyId
 * ----------------------------------------------------------------------------
 * General: Sets the Key ID parameter in the messageContent subfield of the 
 *          genericInformation node for the Soft Keys indications. 
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID
 *                                     of the Soft Keys indication.
 *         keyIdValue                - Key ID value.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249SoftKeysSetKeyId(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    IN  RvUint32                keyIdValue);

/******************************************************************************
 * RvGefH249SoftKeysGetKeyId
 * ----------------------------------------------------------------------------
 * General: Gets the Key ID parameter genericInformation node of the Soft Keys 
 *          indications. 
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID 
 *                                     of the Soft Keys indication.
 * Output: keyIdValue                - Key ID value. 
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249SoftKeysGetKeyId(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    OUT RvUint32                *keyIdValue);

/******************************************************************************
 * RvGefH249SoftKeysSetKeyId
 * ----------------------------------------------------------------------------
 * General: Sets the Key ID parameter in the messageContent subfield of the 
 *          genericInformation node for the Soft Keys indications.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID
 *                                     of the Soft Keys indication.
 *         encodedKeyName            - The key name, encoded according to H.249.
 *         encodedKeyNameSize        - The encoded key name size.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249SoftKeysSetKeyName(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    IN  const RvUint8           *encodedKeyName,
    IN  RvUint32                encodedKeyNameSize);

/******************************************************************************
 * RvGefH249SoftKeysGetKeyName
 * ----------------------------------------------------------------------------
 * General: Gets the Key Name parameter genericInformation node of the 
 *          Soft Keys indications.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID 
 *                                     of the Soft Keys indication.
 * Output: encodedKeyName            - Key name value, encoded according to H.249.
 *         encodedKeyNameSize        - The size of the encoded name. 
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249SoftKeysGetKeyName(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    OUT RvUint8                 *encodedKeyName,
    OUT RvUint32                *encodedKeyNameSize);

/******************************************************************************
 * RvGefH249PointingDeviceIndicationBuild
 * ----------------------------------------------------------------------------
 * General: Builds the genericInformation ASN.1 Pointing Device indication node. 
 *          After this node ID is built, it is the responsibility of the application 
 *          to delete it. Note that the Capability Identifier has already been 
 *          set to this node.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 * Output: genericInformationNodeId  - The new genericInformation node ID 
 *                                     for the Pointing Device indication.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249PointingDeviceIndicationBuild(
    IN  HPVT                    hPvt,
    OUT RvPvtNodeId             *genericInformationNodeId);

/******************************************************************************
 * RvGefH249PointingDeviceSetXPosition
 * ----------------------------------------------------------------------------
 * General: Sets the X parameter in the messageContent subfield of the 
 *          genericInformation node for the Pointing Device indications. 
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID 
 *                                     of the Pointing Device indication.
 *         Xposition                 - X parameter value.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249PointingDeviceSetXPosition(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    IN  RvUint32                Xposition);

/******************************************************************************
 * RvGefH249PointingDeviceGetXPosition
 * ----------------------------------------------------------------------------
 * General: Gets the X parameter from the messageContent subfield of the 
 *          genericInformation node for the Pointing Device indications. 
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID 
 *                                     of the Pointing Device indication.
 * Output: Xposition                 - X parameter value.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249PointingDeviceGetXPosition(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    OUT RvUint32                *Xposition);

/******************************************************************************
 * RvGefH249PointingDeviceSetYPosition
 * ----------------------------------------------------------------------------
 * General: Sets the Y parameter in the messageContent subfield of the 
 *          genericInformation node for the Pointing Device indications.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID 
 *                                     of the Pointing Device indication.
 *         Yposition                 - Y parameter value.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249PointingDeviceSetYPosition(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    IN  RvUint32                Yposition);

/******************************************************************************
 * RvGefH249PointingDeviceGetYPosition
 * ----------------------------------------------------------------------------
 * General: Gets the Y parameter from the messageContent subfield of the 
 *          genericInformation node for the Pointing Device indications.  
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID 
 *                                     of the Pointing Device indication.
 * Output: Yposition                 - Y parameter value.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249PointingDeviceGetYPosition(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    OUT RvUint32                *Yposition);

/******************************************************************************
 * RvGefH249PointingDeviceSetAction
 * ----------------------------------------------------------------------------
 * General: Sets the Action parameter in the messageContent subfield of the 
 *          genericInformation node for the Pointing Device indications. 
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID 
 *                                     of the Pointing Device indication.
 *         action                    - Action parameter value.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249PointingDeviceSetAction(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    IN  RvUint32                action);

/******************************************************************************
 * RvGefH249PointingDeviceGetAction
 * ----------------------------------------------------------------------------
 * General: Gets the Action parameter from the messageContent subfield of the 
 *          genericInformation node for the Pointing Device indications. 
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID
 *                                     of the Pointing Device indication.
 * Output: action                    - Action parameter value.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249PointingDeviceGetAction(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    OUT RvUint32                 *action);

/******************************************************************************
 * RvGefH249PointingDeviceSetButtonId
 * ----------------------------------------------------------------------------
 * General: Sets the Button ID parameter in the messageContent subfield of the 
 *          genericInformation node for the Pointing Device indications.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID 
 *                                     of the Pointing Device indication.
 *         buttonId                  - Button ID parameter value.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249PointingDeviceSetButtonId(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    IN  RvUint32                buttonId);

/******************************************************************************
 * RvGefH249PointingDeviceGetButtonId
 * ----------------------------------------------------------------------------
 * General: Gets the Button ID parameter from the messageContent subfield of 
 *          the genericInformation node for the Pointing Device indications.  
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID 
 *                                     of the Pointing Device indication.
 * Output: buttonId                  - Button ID parameter value.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249PointingDeviceGetButtonId(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    OUT RvUint32                *buttonId);

/******************************************************************************
 * RvGefH249PointingDeviceSetNumberOfClicks
 * ----------------------------------------------------------------------------
 * General: Sets the Number of Clicks parameter in the messageContent subfield 
 *          of the genericInformation node for the Pointing Device indications. 
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID 
 *                                     of the Pointing Device indication.
 *         numberOfClicks            - Number of Clicks parameter value.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249PointingDeviceSetNumberOfClicks(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    IN  RvUint32                numberOfClicks);

/******************************************************************************
 * RvGefH249PointingDeviceGetNumberOfClicks
 * ----------------------------------------------------------------------------
 * General: Gets the Number of Clicks parameter from the messageContent subfield 
 *          of the genericInformation node for the Pointing Device indications.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID
 *                                     of the Pointing Device indication.
 * Output: numerOfClicks             - Number of Clicks parameter value.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249PointingDeviceGetNumberOfClicks(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    OUT RvUint32                 *numerOfClicks);

/******************************************************************************
 * RvGefH249ModalInterfaceIndicationBuild
 * ----------------------------------------------------------------------------
 * General: Builds the genericInformation ASN.1 Modal Interface indication node. 
 *          After this node ID is built, it is the responsibility of the application 
 *          to delete it. Note that the Capability Identifier has already been set 
 *          to this node.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 * Output: genericInformationNodeId  - The new genericInformation node ID 
 *                                     for the Modal Interface indication.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249ModalInterfaceIndicationBuild(
    IN  HPVT                    hPvt,
    OUT RvPvtNodeId             *genericInformationNodeId);

/******************************************************************************
 * RvGefH249ModalInterfaceIndAddUserInputElementId
 * ----------------------------------------------------------------------------
 * General: Adds a User Input Element Id parameter in the messageContent subfield 
 *          of the genericInformation node for the Modal Interface indications.  
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID
 *                                     for the Modal Interface indication.
 *         userElementId             - The user input element ID, one of the 
 *                                     H.249 elements capability:
 *                                     RvGefMessageTypeH249NavigationKey or
 *                                     RvGefMessageTypeH249SoftKeys or
 *                                     RvGefMessageTypeH249PointingDevice
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249ModalInterfaceIndAddUserInputElementId(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    IN  RvGefMessageType        userElementId);

/******************************************************************************
 * RvGefH249ModalInterfaceIndGetUserInputElementId
 * ----------------------------------------------------------------------------
 * General: Gets the User Input Element ID parameter from the genericIndication 
 *          node of the Modal Interface indication.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                         - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId     - The genericInformation node ID 
 *                                        for the Modal Interface indication.
 *         userElementIdArray           - An array allocated by the application 
 *                                        for all userInputElemenIds.
 *         userElementIdArraySize       - The size of the array allocated by the 
 *                                        application.
 * Output: userElementIdArray           - The capability type found in the
 *                                  .     genericInformation message.
 *         userElementIdArraySize       - The number of userInputElemenIds 
 *                                  .     found in the genericInformation message.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249ModalInterfaceIndGetUserInputElementId(
    IN    HPVT                  hPvt,
    IN    RvPvtNodeId           genericInformationNodeId,
    INOUT RvGefMessageType      *userElementIdArray,
    INOUT RvUint32              *userElementIdArraySize );

/******************************************************************************
 * RvGefH249ModalInterfaceSetRemoteControlMode
 * ----------------------------------------------------------------------------
 * General: Sets the Remote Control Mode parameter in the messageContent subfield 
 *          of the genericInformation node for the Modal Interface indications. 
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID 
 *                                     of the Modal Interface indication.
 *         setRemoteControlMode      - Remote Control Mode parameter value.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249ModalInterfaceSetRemoteControlMode(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    IN  RvBool                  setRemoteControlMode);

/******************************************************************************
 * RvGefH249ModalInterfaceGetRemoteControlMode
 * ----------------------------------------------------------------------------
 * General: Gets the Remote Control Mode parameter from the messageContent 
 *          subfield of the genericInformation node for the Modal Interface indication.  
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                      - PVT handle for building ASN.1 node IDs.
 *         genericInformationNodeId  - The genericInformation node ID 
 *                                     of the Modal Interface indication.
 * Output: setRemoteControlMode      - Remote Control Mode parameter value.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefH249ModalInterfaceGetRemoteControlMode(
    IN  HPVT                    hPvt,
    IN  RvPvtNodeId             genericInformationNodeId,
    OUT RvBool                  *setRemoteControlMode);


#ifdef __cplusplus
}
#endif

#endif /* _RV_GEF_H249_H_ */

