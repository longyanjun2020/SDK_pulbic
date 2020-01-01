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

#ifndef _RV_GEF_GENERAL_H_
#define _RV_GEF_GENERAL_H_


/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/

#include "cmH245GeneralDefs.h"
#include "cmctrl.h"
#include "h245.h"

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                           TYPE DEFINITIONS                            */
/*-----------------------------------------------------------------------*/


/* RvGefGenericParameterIdentifierType
 * ------------------------------------------------------------------------
 * This enumeration describes the Generic Parameter Identifier types 
 * already defined in the GenericParameterIdentifier ASN.1 choice.
 */
typedef enum
{
    RvGefGenericParameterIdentifierTypeUnknown = -1,
    RvGefGenericParameterIdentifierTypeStandard,
    RvGefGenericParameterIdentifierTypeH221NonStandard,
    RvGefGenericParameterIdentifierTypeUuid,
    RvGefGenericParameterIdentifierTypeDomainBased

} RvGefGenericParameterIdentifierType;


/* RvGefGenericParameterValueType
 * ------------------------------------------------------------------------
 * This enumeration describes the Generic Parameter Value types already
 * defined in the GenericParameterValue ASN.1 choice.
 */
typedef enum
{
    RvGefGenericParameterValueTypeUnknown = -1,
    RvGefGenericParameterValueTypeLogical,
    RvGefGenericParameterValueTypeBooleanArray,
    RvGefGenericParameterValueTypeUnsignedMin,
    RvGefGenericParameterValueTypeUnsignedMax,
    RvGefGenericParameterValueTypeUnsigned32Min,
    RvGefGenericParameterValueTypeUnsigned32Max,
    RvGefGenericParameterValueTypeOctetString,
    RvGefGenericParameterValueTypeGenericParameter

} RvGefGenericParameterValueType;


/* RvGefCapabilityIdentifierType
 * ------------------------------------------------------------------------
 * This enumeration describes the Capability Identifier types already
 * defined in the CapabilityIdentifier ASN.1 choice.
 */
typedef enum
{
    RvGefCapabilityIdentifierTypeUnknown = -1,
    RvGefCapabilityIdentifierTypeStandard,
    RvGefCapabilityIdentifierTypeH221NonStandard,
    RvGefCapabilityIdentifierTypeUuid,
    RvGefCapabilityIdentifierTypeDomainBased

} RvGefCapabilityIdentifierType;


/* RvGefCodecType
 * ------------------------------------------------------------------------
 * This enumeration describes the codecs supported by the GEF package.
 */
typedef enum
{
    RvGefCodecTypeUnknown = -1,
    RvGefCodecTypeAmr,
    RvGefCodecTypeMpeg4,
    RvGefCodecTypeH264,
    RvGefCodecTypeH239Control,
    RvGefCodecTypeH239ExtendedVideo,
    RvGefCodecTypeG7221,
    RvGefCodecTypeG726,
    RvGefCodecTypeH324AnnexI,
    RvGefCodecTypeSessionReset,
    RvGefCodecTypeG7222,
    RvGefCodecTypeG7231,
    RvGefCodecTypeH263,
    RvGefCodecTypeG711,
    RvGefCodecTypeG722,
    RvGefCodecTypeG729,
    RvGefCodecTypeH249NavigationKey,
    RvGefCodecTypeH249SoftKeys,
    RvGefCodecTypeH249PointingDevice,
    RvGefCodecTypeH249ModalInterface,
    RvGefCodecTypeLast
} RvGefCodecType;

/* RvGefMessageType
 * ------------------------------------------------------------------------
 * This enumeration describes the GenericMessage types supported by the GEF package.
 */
typedef enum
{
    RvGefMessageTypeUnknown = -1,
    RvGefMessageTypeH239,
    RvGefMessageTypeH249NavigationKey,
    RvGefMessageTypeH249SoftKeys,
    RvGefMessageTypeH249PointingDevice,
    RvGefMessageTypeH249ModalInterface,
	RvGefMessageTypeMONA,
    RvGefMessageTypeLast

} RvGefMessageType;

/*-----------------------------------------------------------------------*/
/*                           FUNCTIONS HEADERS                           */
/*-----------------------------------------------------------------------*/


/******************************************************************************
 * RvGefInit
 * ----------------------------------------------------------------------------
 * General: Creates an instance of the GEF object.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Output: pH245Syntax - The H.245 syntax returned by cmEmGetH245Syntax().
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefInit(RvUint8 *pH245Syntax);


/******************************************************************************
 * RvGefEnd
 * ----------------------------------------------------------------------------
 * General: Destructs a GEF object.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefEnd(void);

/********************************************************************************
 *
 * Generic Capability
 *
 ********************************************************************************/

/******************************************************************************
 * RvGefGenericCapabilityBuild
 * ----------------------------------------------------------------------------
 * General: Builds a node ID of type GenericCapability. If this node ID is 
 *          built, it is the responsibility of the application to delete it.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt             - PVT handle for building ASN.1 node IDs.
 * Output: genericCapNodeId - The new GenericCapability node ID.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericCapabilityBuild(
    IN  HPVT                    hPvt,
    OUT RvPvtNodeId             *genericCapNodeId);



/******************************************************************************
 * RvGefGenericCapabilitySetIdentifier
 * ----------------------------------------------------------------------------
 * General: Sets the CapabilityIdentifier to the GenericCapability ASN.1 node ID.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         genericCapNodeId     - The GenericCapability node ID.
 *         eCapIdType           - The CapabilityIdentifier type.
 *         capabilityId         - The parameter of the integer type like
								  RvGefCapabilityIdentifierTypeH221NonStandard. In this
 *                                case, the non-standard node ID is no longer valid after 
 *                                being set and should not be deleted by the application.
 *                                If the parameter identifier is of the string type, 
 *                                use this argument to pass the size of the string 
 *                                (pStrCapabilityId argument).
 *         pStrCapabilityId     - The parameter identifier of the string types
 *                                RvGefCapabilityIdentifierTypeStandard,
 *                                RvGefCapabilityIdentifierTypeUuid or
 *                                RvGefCapabilityIdentifierTypeDomainBased.
 *                                If this argument is used, the application must provide 
 *                                the string length in the capabilityId argument.
 *                                If the argument is of the integer type, set this 
 *                                argument to NULL.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericCapabilitySetIdentifier(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericCapNodeId,
    IN  RvGefCapabilityIdentifierType       eCapIdType,
    IN  RvInt32                             capabilityId,
    IN  const RvUint8                       *pStrCapabilityId);


/******************************************************************************
 * RvGefGenericCapabilityGetIdentifier
 * ----------------------------------------------------------------------------
 * General: Gets the CapabilityIdentifier parameter from the 
 *          GenericCapability ASN.1 node ID.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         genericCapNodeId     - The GenericCapability node ID.
 *         pCapabilityId        - The parameter of the integer type like
 *                                RvGefCapabilityIdentifierTypeH221NonStandard.
 *                                If the parameter is of the string type, use this argument
 *                                to pass the size of pStrCapabilityId that was allocated.
 * Output: peCapIdType          - The CapabilityIdentifier type.
 *         pCapabilityId        - If the parameter is of the string type, this argument
 *                                will be filled with the actual size of the string.
 *         pStrCapabilityId     - The parameters of string types like
 *                                RvGefCapabilityIdentifierTypeStandard,
 *                                RvGefCapabilityIdentifierTypeUuid or
 *                                RvGefCapabilityIdentifierTypeDomainBased.
 *                                If this argument is used, the actual length of the string
 *                                will be provided in the pCapabilityId argument.
 *                                The allocation of this parameter is the responsibility
 *                                of the application.
 *                                If this argument is set to NULL and the parameter is of the 
 *                                string type, the application can use the size returned
 *                                in pCapabilityId and call this function again with a buffer
 *                                allocated in the appropriate size.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericCapabilityGetIdentifier(
    IN    HPVT                                hPvt,
    IN    RvPvtNodeId                         genericCapNodeId,
    OUT   RvGefCapabilityIdentifierType       *peCapIdType,
    INOUT RvInt32                             *pCapabilityId,
    OUT   RvUint8                             *pStrCapabilityId);


/******************************************************************************
 * RvGefGenericCapabilitySetMaxBitRate
 * ----------------------------------------------------------------------------
 * General: Sets the maxBitRate parameter to the GenericCapability ASN.1 node ID.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         genericCapNodeId     - The GenericCapability node ID.
 *         maxBitRate           - The maxBitRate parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericCapabilitySetMaxBitRate(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericCapNodeId,
    IN  RvUint32                            maxBitRate);


/******************************************************************************
 * RvGefGenericCapabilityGetMaxBitRate
 * ----------------------------------------------------------------------------
 * General: Gets the maxBitRate parameter from the GenericCapability ASN.1 node ID.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         genericCapNodeId     - The GenericCapability node ID.
 * Output: pMaxBitRate          - The maxBitRate parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericCapabilityGetMaxBitRate(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericCapNodeId,
    OUT RvUint32                            *pMaxBitRate);


/******************************************************************************
 * RvGefGenericCapabilitySetCollapsing
 * ----------------------------------------------------------------------------
 * General: Sets the collapsing parameter to the GenericCapability ASN.1 node ID. 
 *          Note that the collapsing parameter is a sequence of GenericParameter. 
 *          Therefore, you must set each part of the sequence separately using 
 *          the collapsingIndex parameter.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         genericCapNodeId     - The GenericCapability node ID.
 *         collapsingIndex      - The index of the collapsing parameter inside the
 *                                GenericParameter sequence. The index of the first
 *                                object of the sequence is 1. To set the object 
 *                                at the end of the sequence, use 0 as index. 
 *                                If an object already exists in the selected index, 
 *                                the new object will override the old object.
 *         collapsingNodeId     - The collapsing node ID built by the GenericParameter 
 *                                set of functions. The collapsing node ID is no 
 *                                longer valid after being set and should not be 
 *                                deleted by the application.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericCapabilitySetCollapsing(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericCapNodeId,
    IN  RvUint32                            collapsingIndex,
    IN  RvPvtNodeId                         collapsingNodeId);

/******************************************************************************
 * RvGefGenericCapabilityGetCollapsingByIndex
 * ----------------------------------------------------------------------------
 * General: Gets the collapsing parameter from the GenericCapability ASN.1 
 *          node ID. Note that the collapsing parameter is a sequence of 
 *          GenericParameter. Therefore, you must get each part of the sequence 
 *          separately using the collapsingIndex parameter.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         genericCapNodeId     - The GenericCapability node ID.
 *         collapsingIndex      - The index of the collapsing parameter inside 
 *                                the GenericParameter sequence. The index of 
 *                                the first object of the sequence is 1.
 * Output: collapsingNodeId     - The collapsing node ID. This node ID is a 
 *                                specific GenericParameter taken from the 
 *                                GenericParameter sequence, according to the 
 *                                given index.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericCapabilityGetCollapsingByIndex(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericCapNodeId,
    IN  RvUint32                            collapsingIndex,
    OUT RvPvtNodeId                         *collapsingNodeId);

/******************************************************************************
 * RvGefGenericCapabilityGetCollapsingByIdentifier
 * ----------------------------------------------------------------------------
 * General: Gets the collapsing parameter from the GenericCapability ASN.1 node 
 *          ID according to the parameter identifier. Note that parameterIdentifier 
 *          is a choice. Therefore, you must provide the identifier type.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         genericCapNodeId     - The GenericCapability node ID.
 *         eParamIdentifier     - The parameter identifier type of the collapsing parameter.
 *         paramId              - The parameter integer value. Used for integer types like
 *                                RvGefGenericParameterIdentifierTypeStandard and
 *                                RvGefGenericParameterIdentifierTypeH221NonStandard.
 *         pStrParamId          - The parameter string value. Used for string types like
 *                                RvGefGenericParameterIdentifierTypeUuid and
 *                                RvGefGenericParameterIdentifierTypeDomainBased.
 *                                If not used, set this argument to NULL.
 *                                Use the paramId argument to pass the size of the string.
 * Output: collapsingNodeId     - The collapsing node ID. This node ID is a specific 
 *                                GenericParameter taken from the GenericParameter sequence.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericCapabilityGetCollapsingByIdentifier(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericCapNodeId,
    IN  RvGefGenericParameterIdentifierType eParamIdentifier,
    IN  RvInt32                             paramId,
    IN  const RvUint8                       *pStrParamId,
    OUT RvPvtNodeId                         *collapsingNodeId);


/******************************************************************************
 * RvGefGenericCapabilitySetNonCollapsing
 * ----------------------------------------------------------------------------
 * General: Sets the nonCollapsing parameter to the GenericCapability ASN.1 node ID. 
 *          Note that the nonCollapsing parameter is a sequence of GenericParameter. 
 *          Therefore, you must set each part of the sequence separately using the 
 *          nonCollapsingIndex parameter.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         genericCapNodeId     - The GenericCapability node ID.
 *         nonCollapsingIndex   - The index of the nonCollapsing parameter inside the
 *                                GenericParameter sequence. The index of the first
 *                                object of the sequence is 1. To set the object
 *                                at the end of the sequence, use 0 as index.
 *                                If an object already exists in the selected index,
 *                                the new object will override the old object.
 *         nonCollapsingNodeId  - The nonCollapsing node ID built by the GenericParameter 
 *                                set of functions. The nonCollapsing node ID is no longer 
 *                                valid after being set and should not be deleted by the 
 *                                application.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericCapabilitySetNonCollapsing(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericCapNodeId,
    IN  RvUint32                            nonCollapsingIndex,
    IN  RvPvtNodeId                         nonCollapsingNodeId);

/******************************************************************************
 * RvGefGenericCapabilityGetNonCollapsingByIndex
 * ----------------------------------------------------------------------------
 * General: Gets the nonCollapsing parameter from the GenericCapability ASN.1 
 *          node ID. Note that the nonCollapsing parameter is a sequence of 
 *          GenericParameter. Therefore, you must get each part of the sequence 
 *          separately using the nonCollapsingIndex parameter.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         genericCapNodeId     - The GenericCapability node ID.
 *         nonCollapsingIndex   - The index of the nonCollapsing parameter inside 
 *                                the GenericParameter sequence. The index of the 
 *                                first object of the sequence is 1.
 * Output: nonCollapsingNodeId  - The nonCollapsing node ID. This node ID is a 
 *                                specific GenericParameter taken from the 
 *                                GenericParameter sequence according to the given 
 *                                index.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericCapabilityGetNonCollapsingByIndex(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericCapNodeId,
    IN  RvUint32                            nonCollapsingIndex,
    OUT RvPvtNodeId                         *nonCollapsingNodeId);

/******************************************************************************
 * RvGefGenericCapabilityGetNonCollapsingByIdentifier
 * ----------------------------------------------------------------------------
 * General: Gets the nonCollapsing parameter from the GenericCapability ASN.1 
 *          node ID according to the parameter identifier. Note that the 
 *          parameterIdentifier is a choice. Therefore, you must provide the 
 *          identifier type.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         genericCapNodeId     - The GenericCapability node ID.
 *         eParamIdentifier     - The parameter identifier type of the nonCollapsing parameter.
 *         paramId              - The parameter integer value. Used for integer types like
 *                                RvGefGenericParameterIdentifierTypeStandard and
 *                                RvGefGenericParameterIdentifierTypeH221NonStandard.
 *         pStrParamId          - The parameter string value. Used for string types like
 *                                RvGefGenericParameterIdentifierTypeUuid and
 *                                RvGefGenericParameterIdentifierTypeDomainBased.
 *                                If not used, set this argument to NULL.
 *                                Use the paramId argument to pass the size of the string.
 * Output: nonCollapsingNodeId  - The nonCollapsing node ID. This node ID is a specific
 *                                GenericParameter taken from the GenericParameter sequence.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericCapabilityGetNonCollapsingByIdentifier(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericCapNodeId,
    IN  RvGefGenericParameterIdentifierType eParamIdentifier,
    IN  RvInt32                             paramId,
    IN  const RvUint8                       *pStrParamId,
    OUT RvPvtNodeId                         *nonCollapsingNodeId);


/******************************************************************************
 * RvGefGenericCapabilitySetNonCollapsingRaw
 * ----------------------------------------------------------------------------
 * General: Sets the nonCollapsingRaw parameter to the GenericCapability ASN.1 node ID.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         genericCapNodeId     - The GenericCapability node ID.
 *         pNonCollapsingRaw    - The nonCollapsingRaw parameter.
 *         nonCollapsingRawSize - The size of the nonCollapsingRaw string.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericCapabilitySetNonCollapsingRaw(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericCapNodeId,
    IN  const RvUint8                       *pNonCollapsingRaw,
    IN  RvUint32                            nonCollapsingRawSize);


/******************************************************************************
 * RvGefGenericCapabilityGetNonCollapsingRaw
 * ----------------------------------------------------------------------------
 * General: Gets the nonCollapsingRaw parameter to the GenericCapability ASN.1 node ID.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                  - PVT handle for handling ASN.1 node IDs.
 *         genericCapNodeId      - The GenericCapability node ID.
 *         pNonCollapsingRawSize - The size of the nonCollapsingRaw string.
 *                                 This parameter will be filled with the actual size
 *                                 of the pNonCollapsingRaw string.
 * Output: pNonCollapsingRaw     - The nonCollapsingRaw parameter. This string must be
 *                                 allocated by the application. The size of the allocated
 *                                 string must be passed by the nonCollapsingRawSize parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericCapabilityGetNonCollapsingRaw(
    IN    HPVT                                hPvt,
    IN    RvPvtNodeId                         genericCapNodeId,
    INOUT RvUint32                            *pNonCollapsingRawSize,
    OUT   RvUint8                             *pNonCollapsingRaw);


/******************************************************************************
 * RvGefGenericCapabilityGetCodecType
 * ----------------------------------------------------------------------------
 * General: Gets the coded type of the given GenericCapability according 
 *          to the CapabilityIdentifier.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         genericCapNodeId     - The GenericCapability or CapabilityIdentifier node ID.
 * Output: pGefCodecType        - The codec type of the genericCapNodeId.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericCapabilityGetCodecType(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericCapNodeId,
    OUT RvGefCodecType                      *pGefCodecType);

/********************************************************************************
 *
 * Generic Parameter
 *
 ********************************************************************************/


/******************************************************************************
 * RvGefGenericParameterBuild
 * ----------------------------------------------------------------------------
 * General: Builds a node ID of type GenericParameter. When this node ID is built, 
 *          it is the responsibility of the application to delete it.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt               - PVT handle for building ASN.1 node IDs.
 * Output: genericParamNodeId - The new GenericParameter node ID.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericParameterBuild(
    IN  HPVT                    hPvt,
    OUT RvPvtNodeId             *genericParamNodeId);


/******************************************************************************
 * RvGefGenericParameterSetIdentifier
 * ----------------------------------------------------------------------------
 * General: Sets the Identifier parameter to the GenericParameter ASN.1 node ID.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node IDs.
 *         genericParamNodeId   - The GenericParameter node ID.
 *         eGenericParamIdType  - The GenericParameterIdentifier type.
 *         genericParamId       - The parameter of integer types like
 *                                RvGefGenericParameterIdentifierTypeStandard and
 *                                RvGefGenericParameterIdentifierTypeH221NonStandard. In the
 *                                RvGefGenericParameterIdentifierTypeH221NonStandard case,
 *                                the non standard node id is not valid anymore after the setting
 *                                and should not be deleted by the application.
 *                                If the parameter is from string type, use this
 *                                argument to pass the size of the string (pStrGenericParamId
 *                                argument).
 *         pStrGenericParamId   - The parameters from String type like
 *                                RvGefGenericParameterIdentifierTypeUuid and
 *                                RvGefGenericParameterIdentifierTypeDomainBased.
 *                                If this argument is used, then the application must
 *                                provide the string length in the genericParamId argument.
 *                                If this parameter is from integer type, set this argument
 *                                to NULL.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericParameterSetIdentifier(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericParamNodeId,
    IN  RvGefGenericParameterIdentifierType eGenericParamIdType,
    IN  RvInt32                             genericParamId,
    IN  const RvUint8                       *pStrGenericParamId);


/******************************************************************************
 * RvGefGenericParameterGetIdentifier
 * ----------------------------------------------------------------------------
 * General: Get the Identifier parameter from the GenericParameter ASN.1 node id.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node ids.
 *         genericParamNodeId   - The GenericParameter node id.
 *         pGenericParamId      - The parameters from integer type like
 *                                RvGefGenericParameterIdentifierTypeStandard and
 *                                RvGefGenericParameterIdentifierTypeH221NonStandard.
 *                                If the parameter is from string type, use this argument
 *                                to pass the size of pStrGenericParamId that was allocated.
 * Output: peGenericParamIdType - The GenericParameterIdentifier type.
 *         pGenericParamId      - If the parameter is from string type, then this argument
 *                                will be filled with the actual size of the string.
 *         pStrGenericParamId   - The parameters from String type like
 *                                RvGefGenericParameterIdentifierTypeUuid and
 *                                RvGefGenericParameterIdentifierTypeDomainBased.
 *                                If this argument is used, then the length of the string
 *                                will be provided in the pGenericParamId argument.
 *                                The allocation of this parameter is the responsibility
 *                                of the application.
 *                                If this argument is set to NULL and the parameter is from
 *                                string type then the application can use the size returned
 *                                in pGenericParamId and call this function again with buffer
 *                                allocated in the right size.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericParameterGetIdentifier(
    IN    HPVT                                hPvt,
    IN    RvPvtNodeId                         genericParamNodeId,
    OUT   RvGefGenericParameterIdentifierType *peGenericParamIdType,
    INOUT RvInt32                             *pGenericParamId,
    OUT   RvUint8                             *pStrGenericParamId);


/******************************************************************************
 * RvGefGenericParameterSetValue
 * ----------------------------------------------------------------------------
 * General: Set the Value parameter to the GenericParameter ASN.1 node id.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node ids.
 *         genericParamNodeId   - The GenericParameter node id.
 *         eGenericParamValType - The GenericParameterValue type.
 *         genericParamVal      - The parameters from integer type like
 *                                RvGefGenericParameterValueTypeLogical,
 *                                RvGefGenericParameterValueTypeBooleanArray,
 *                                RvGefGenericParameterValueTypeUnsignedMin,
 *                                RvGefGenericParameterValueTypeUnsignedMax,
 *                                RvGefGenericParameterValueTypeUnsigned32Min and
 *                                RvGefGenericParameterValueTypeUnsigned32Max.
 *         strGenericParamVal   - The parameters from String type like
 *                                RvGefGenericParameterValueTypeOctetString.
 *                                If this argument is used, then the application must
 *                                provide the string length in the genericParamVal argument.
 *                                If this argument is not used, set it to NULL.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericParameterSetValue(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericParamNodeId,
    IN  RvGefGenericParameterValueType      eGenericParamValType,
    IN  RvUint32                            genericParamVal,
    IN  const RvUint8                       *pStrGenericParamVal);


/******************************************************************************
 * RvGefGenericParameterGetValue
 * ----------------------------------------------------------------------------
 * General: Get the Value parameter to the GenericParameter ASN.1 node id.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                  - PVT handle for handling ASN.1 node ids.
 *         genericParamNodeId    - The GenericParameter node id.
 *         pGenericParamVal      - The parameters from integer type like
 *                                 RvGefGenericParameterValueTypeLogical,
 *                                 RvGefGenericParameterValueTypeBooleanArray,
 *                                 RvGefGenericParameterValueTypeUnsignedMin,
 *                                 RvGefGenericParameterValueTypeUnsignedMax,
 *                                 RvGefGenericParameterValueTypeUnsigned32Min and
 *                                 RvGefGenericParameterValueTypeUnsigned32Max.
 *                                 If the parameter is from string type, use this argument
 *                                 to pass the size of pStrGenericParamVal that was allocated.
 * Output: peGenericParamValType - The GenericParameterValue type.
 *         pGenericParamVal      - If the parameter is from string type, then this argument
 *                                 will be filled with the actual size of the string.
 *         pStrGenericParamVal   - The parameters from String type like
 *                                 RvGefGenericParameterValueTypeOctetString.
 *                                 If this argument is used, then the length of the string
 *                                 will be provided in the pGenericParamVal argument.
 *                                 The allocation of this parameter is the responsibility
 *                                 of the application.
 *                                 If this argument is set to NULL and the parameter is from
 *                                 string type then the application can use the size returned
 *                                 in pGenericParamVal and call this function again with buffer
 *                                 allocated in the right size.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericParameterGetValue(
    IN     HPVT                                hPvt,
    IN     RvPvtNodeId                         genericParamNodeId,
    OUT    RvGefGenericParameterValueType      *peGenericParamValType,
    INOUT  RvUint32                            *pGenericParamVal,
    OUT    RvUint8                             *pStrGenericParamVal);


/******************************************************************************
 * RvGefGenericParameterSetSupersedes
 * ----------------------------------------------------------------------------
 * General: Set the supersedes parameter to the GenericParameter ASN.1 node id.
 *          Note that the supersedes parameter is a sequence of ParameterIdentifier.
 *          Therefore, you must set each part of the sequence separately using the
 *          supersedesIndex parameter.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node ids.
 *         genericParamNodeId   - The GenericParameter node id.
 *         supersedesIndex      - The index of the supersedes parameter inside the
 *                                ParameterIdentifier sequence. The index of the first
 *                                object of the sequence is 1. In order to set the object
 *                                in the end of the sequence, use 0 as index.
 *                                If an object already exists in the index that you picked,
 *                                the new object will override the old object.
 *         eParamIdType         - The ParameterIdentifier type.
 *         paramId              - The parameters from integer type like
 *                                RvGefGenericParameterIdentifierTypeStandard and
 *                                RvGefGenericParameterIdentifierTypeH221NonStandard. In the
 *                                RvGefGenericParameterIdentifierTypeH221NonStandard case,
 *                                the non standard node id is not valid anymore after the setting
 *                                and should not be deleted by the application.
 *                                If the parameter is from string type, use this
 *                                argument to pass the size of the string (pStrParamId
 *                                argument).
 *         pStrParamId          - The parameters from String type like
 *                                RvGefGenericParameterIdentifierTypeUuid and
 *                                RvGefGenericParameterIdentifierTypeDomainBased.
 *                                If this argument is used, then the application must
 *                                provide the string length in the paramId argument.
 *                                If this parameter is from integer type, set this argument
 *                                to NULL.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericParameterSetSupersedes(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericParamNodeId,
    IN  RvUint32                            supersedesIndex,
    IN  RvGefGenericParameterIdentifierType eParamIdType,
    IN  RvInt32                             paramId,
    IN  const RvUint8                       *pStrParamId);

/******************************************************************************
 * RvGefGenericParameterGetSupersedes
 * ----------------------------------------------------------------------------
 * General: Get the supersedes parameter from the GenericParameter ASN.1 node id.
 *          Note that the supersedes parameter is a sequence of ParameterIdentifier.
 *          Therefore, you must get each part of the sequence separately using the
 *          supersedesIndex parameter.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node ids.
 *         genericParamNodeId   - The GenericParameter node id.
 *         supersedesIndex      - The index of the supersedes parameter inside the
 *         pParamId             - The parameters from integer type like
 *                                RvGefGenericParameterIdentifierTypeStandard and
 *                                RvGefGenericParameterIdentifierTypeH221NonStandard.
 *                                If the parameter is from string type, use this argument
 *                                to pass the size of pStrParamId that was allocated.
 * Output: peParamIdType        - The ParameterIdentifier type.
 *         pParamId             - If the parameter is from string type, then this argument
 *                                will be filled with the actual size of the string.
 *         pStrParamId          - The parameters from String type like
 *                                RvGefGenericParameterIdentifierTypeUuid and
 *                                RvGefGenericParameterIdentifierTypeDomainBased.
 *                                If this argument is used, then the length of the string
 *                                will be provided in the pParamId argument.
 *                                The allocation of this parameter is the responsibility
 *                                of the application.
 *                                If this argument is set to NULL and the parameter is from
 *                                string type then the application can use the size returned
 *                                in pParamId and call this function again with buffer
 *                                allocated in the right size.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericParameterGetSupersedes(
    IN    HPVT                                hPvt,
    IN    RvPvtNodeId                         genericParamNodeId,
    IN    RvUint32                            supersedesIndex,
    OUT   RvGefGenericParameterIdentifierType *peParamIdType,
    INOUT RvInt32                             *pParamId,
    OUT   RvUint8                             *pStrParamId);




/********************************************************************************
 *
 * Extended Video Capability
 *
 ********************************************************************************/


/******************************************************************************
 * RvGefGenericExtendedVideoCapabilityBuild
 * ----------------------------------------------------------------------------
 * General: Creates & builds an ExtendedVideoCapability node.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                           - PVT handle for handling ASN.1 node ids.
 *
 * Output: extendedVideoCapNode           - The new extendedVideoCapability node id.
 *****************************************************************************/
RVAPI RvStatus RvGefGenericExtendedVideoCapabilityBuild(
    IN  HPVT                                hPvt,
    OUT RvPvtNodeId                         *extendedVideoCapNode);

/******************************************************************************
 * RvGefGenericExtendedVideoAddCap
 * ----------------------------------------------------------------------------
 * General: add a videoCapability to the sequence of videoCapability in the
 *          extendedVideoCapability node.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                           - PVT handle for handling ASN.1 node ids.
 *         extendedVideoCapNode           - The extendedVideoCapability node id.
 *         capsNodeId                     - The videoCapability node (a sequence of
 *                                          VideoCapabilities) to be added under the
                                            given extendedVideoCapability node.
 *                                          This node id will not be valid when
 *                                          this function returns
 *
 * Output: none
 *****************************************************************************/
RVAPI RvStatus RvGefGenericExtendedVideoAddCap(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         extendedVideoCapNode,
    IN  RvPvtNodeId                         capsNodeId);

/******************************************************************************
 * RvGefGenericExtendedVideoCapabilityAddExtension
 * ----------------------------------------------------------------------------
 * General: Adds a videoCapabilityExtension to the sequence of videoCapabilityExtension
 *          in the extendedVideoCapability node.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                           - PVT handle for handling ASN.1 node ids.
 *         extendedVideoCapNode           - The extendedVideoCapability
 *                                          node in the videoData node under the
 *                                          dataType node of a logical channel..
 *         extensionNodeId                - The videoCapabilityExtension node id
 *                                          to be added under the extendedVideoCapability
 *                                          node.
 *                                          This node id will not be valid when
 *                                          this function returns
 * Output: none
 *****************************************************************************/
RVAPI RvStatus RvGefGenericExtendedVideoCapabilityAddExtension(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         extendedVideoCapNode,
    IN  RvPvtNodeId                         extensionNodeId);




/********************************************************************************
 *
 * Reset capability - Generic Control Capability
 *
 ********************************************************************************/


/******************************************************************************
 * RvGefGenericCapabilitySessionResetBuild
 * ----------------------------------------------------------------------------
 * General: Build the GenericCapability ASN.1 node id for Session Reset capability.
 *          After this node id was built, it is the responsibility of the application
 *          to delete it.
 *          Note that the Capability Identifier has already been set to this node id.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt               - PVT handle for building ASN.1 node ids.
 * Output: sessionResetNodeId - The new GenericCapability node id for Session Reset capability.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericCapabilitySessionResetBuild(
    IN  HPVT                    hPvt,
    OUT RvPvtNodeId             *sessionResetNodeId);




/********************************************************************************
 *
 * Generic Message
 *
 ********************************************************************************/

/******************************************************************************
 * RvGefGenericMessageBuild
 * ----------------------------------------------------------------------------
 * General: Build the GenericMessage ASN.1 node id.
 *          After this node id was built, it is the responsibility of the application
 *          to delete it.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for building ASN.1 node ids.
 * Output: genericMessageNodeId - The new GenericMessage node id.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericMessageBuild(
    IN  HPVT                    hPvt,
    OUT RvPvtNodeId             *genericMessageNodeId);

/******************************************************************************
 * RvGefGenericMessageGetMessageType
 * ----------------------------------------------------------------------------
 * General: Get the GenericMessage type of the given GenericMessage node according
 *          to the MessageIdentifier.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node ids.
 *         genericMessageNodeId - The GenericMessage node id.
 * Output: pGefMessageType        - The message type of the genericMessageNodeId.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericMessageGetMessageType(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericMessageNodeId,
    OUT RvGefMessageType                    *pGefMessageType);

/******************************************************************************
 * RvGefGenericMessageSetIdentifier
 * ----------------------------------------------------------------------------
 * General: Set the MessageIdentifier to the GenericMessage ASN.1 node id.
 *          Note that the GenericMessage node id should be built previously by the
 *          application using the function cmBuildMultimediaSystemControlMessage().
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node ids.
 *         genericMessageNodeId - The GenericMessage node id.
 *         eCapIdType           - The CapabilityIdentifier type.
 *         messageId            - The parameters from integer type
 *                                like RvGefCapabilityIdentifierTypeH221NonStandard. In this
 *                                case, the non standard node id is not valid anymore after
 *                                the setting and should not be deleted by the application.
 *                                If the parameter is from string type, use this
 *                                argument to pass the size of the string (pStrGenericMessageId
 *                                argument).
 * Output: pStrGenericMessageId - The parameters from String type like
 *                                RvGefCapabilityIdentifierTypeStandard,
 *                                RvGefCapabilityIdentifierTypeUuid or
 *                                RvGefCapabilityIdentifierTypeDomainBased.
 *                                If this argument is used, then the application must
 *                                provide the string length in the messageId argument.
 *                                If this parameter is from integer type, set this argument
 *                                to NULL.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericMessageSetIdentifier(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericMessageNodeId,
    IN  RvGefCapabilityIdentifierType       eCapIdType,
    IN  RvInt32                             messageId,
    IN  const RvUint8                       *pStrGenericMessageId);


/******************************************************************************
 * RvGefGenericMessageGetIdentifier
 * ----------------------------------------------------------------------------
 * General: Get the MessageIdentifier parameter from the GenericMessage
 *          ASN.1 node id.
 *          Note that the GenericMessage node id should be built previously by the
 *          application using the function cmBuildMultimediaSystemControlMessage().
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node ids.
 *         genericMessageNodeId - The GenericMessage node id.
 *         pMessageId           - The parameters from integer type like
 *                                RvGefCapabilityIdentifierTypeH221NonStandard.
 *                                If the parameter is from string type, use this argument
 *                                to pass the size of pStrMessageId that was allocated.
 * Output: peCapIdType          - The CapabilityIdentifier type.
 *         pMessageId           - If the parameter is from string type, then this argument
 *                                will be filled with the actual size of the string.
 *         pStrMessageId        - The parameters from String type like
 *                                RvGefCapabilityIdentifierTypeStandard,
 *                                RvGefCapabilityIdentifierTypeUuid or
 *                                RvGefCapabilityIdentifierTypeDomainBased.
 *                                If this argument is used, then the actual length of the string
 *                                will be provided in the pMessageId argument.
 *                                The allocation of this parameter is the responsibility
 *                                of the application.
 *                                If this argument is set to NULL and the parameter is from
 *                                string type then the application can use the size returned
 *                                in pMessageId and call this function again with buffer
 *                                allocated in the right size.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericMessageGetIdentifier(
    IN    HPVT                               hPvt,
    IN    RvPvtNodeId                        genericMessageNodeId,
    OUT   RvGefCapabilityIdentifierType      *peCapIdType,
    INOUT RvInt32                            *pMessageId,
    OUT   RvUint8                            *pStrMessageId);


/******************************************************************************
 * RvGefGenericMessageSetSubMessageIdentifier
 * ----------------------------------------------------------------------------
 * General: Set the subMessageIdentifier parameter to the GenericMessage ASN.1
 *          node id.
 *          Note that the GenericMessage node id should be built previously by the
 *          application using the function cmBuildMultimediaSystemControlMessage().
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node ids.
 *         genericMessageNodeId - The GenericMessage node id.
 *         subMessageIdentifier - The subMessageIdentifier parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericMessageSetSubMessageIdentifier(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericMessageNodeId,
    IN  RvUint8                             subMessageIdentifier);


/******************************************************************************
 * RvGefGenericMessageGetSubMessageIdentifier
 * ----------------------------------------------------------------------------
 * General: Get the subMessageIdentifier parameter from the GenericMessage ASN.1
 *          node id.
 *          Note that the GenericMessage node id should be built previously by the
 *          application using the function cmBuildMultimediaSystemControlMessage().
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                  - PVT handle for handling ASN.1 node ids.
 *         genericMessageNodeId  - The GenericMessage node id.
 * Output: pSubMessageIdentifier - The subMessageIdentifier parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericMessageGetSubMessageIdentifier(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericMessageNodeId,
    OUT RvUint8                             *pSubMessageIdentifier);


/******************************************************************************
 * RvGefGenericMessageSetMessageContent
 * ----------------------------------------------------------------------------
 * General: Set the messageContent parameter to the GenericMessage ASN.1 node id.
 *          Note that the messageContent parameter is a sequence of GenericParameter.
 *          Therefore, you must set each part of the sequence separately using the
 *          messageContentIndex parameter.
 *
 *          Note that the GenericMessage node id should be built previously by the
 *          application using the function cmBuildMultimediaSystemControlMessage().
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node ids.
 *         genericMessageNodeId - The GenericMessage node id.
 *         messageContentIndex  - The index of the messageContent parameter inside the
 *                                GenericParameter sequence. The index of the first
 *                                object of the sequence is 1. In order to set the object
 *                                in the end of the sequence, use 0 as index.
 *                                If an object already exists in the index that you picked,
 *                                the new object will override the old object.
 *         messageContentNodeId - The messageContent node id built by the GenericParameter
 *                                set of functions. The messageContentNodeId node id is not valid anymore after
 *                                the setting and should not be deleted by the application.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericMessageSetMessageContent(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericMessageNodeId,
    IN  RvUint32                            messageContentIndex,
    IN  RvPvtNodeId                         messageContentNodeId);

/******************************************************************************
 * RvGefGenericMessageGetMessageContent
 * ----------------------------------------------------------------------------
 * General: Get the messageContent parameter from the GenericMessage ASN.1 node id.
 *          Note that the messageContent parameter is a sequence of GenericParameter.
 *          Therefore, you must get each part of the sequence separately using the
 *          messageContentIndex parameter.
 *
 *          Note that the GenericMessage node id should be built previously by the
 *          application using the function cmBuildMultimediaSystemControlMessage().
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node ids.
 *         genericMessageNodeId - The GenericMessage node id.
 *         messageContentIndex  - The index of the messageContent parameter inside the
 *                                GenericParameter sequence. The index of the first
 *                                object of the sequence is 1.
 * Output: messageContentNodeId - The messageContent node id. This node id is a specific
 *                                GenericParameter taken from the GenericParameter sequence
 *                                according to the given index.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericMessageGetMessageContent(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericMessageNodeId,
    IN  RvUint32                            messageContentIndex,
    OUT RvPvtNodeId                         *messageContentNodeId);

/******************************************************************************
 * RvGefGenericCapabilityGetCollapsingByIdentifier
 * ----------------------------------------------------------------------------
 * General: Get the generic parameter from the GenericMessage ASN.1 node id
 *          according to the parameter identifier.
 *          Note that the parameterIdentifier is a choice and therefore, you must
 *          provide the type of the identifier.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node ids.
 *         genericMessageNodeId - The GenericMessage node id.
 *         eParamIdentifier     - The parameter identifier type . 
 *         paramId              - The parameter identifier value. Used for the integer types like 
 *                                RvGefGenericParameterIdentifierTypeStandard and
 *                                RvGefGenericParameterIdentifierTypeH221NonStandard.
 *         pStrParamId          - The parameter string value. Used for the string types like 
 *                                RvGefGenericParameterIdentifierTypeUuid and
 *                                RvGefGenericParameterIdentifierTypeDomainBased.
 *                                If not used, set this argument to NULL.
 *                                Use the paramId argument to pass the size of the string.
 * Output: genericParamNodeId   - The requested parameter node id. This node id is a specific
 *                                GenericParameter taken from the GenericParameter sequence.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericMessageGetMessageContentByIdentifier(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericMessageNodeId,
    IN  RvGefGenericParameterIdentifierType eParamIdentifier,
    IN  RvInt32                             paramId,
    IN  const RvUint8                       *pStrParamId,
    OUT RvPvtNodeId                         *genericParamNodeId);



/******************************************************************************
 * RvGefGenericMessageGetMessageType
 * ----------------------------------------------------------------------------
 * General: Get the GenericMessage type of the given GenericMessage node according
 *          to the MessageIdentifier.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hPvt                 - PVT handle for handling ASN.1 node ids.
 *         genericMessageNodeId - The GenericMessage node id.
 * Output: pGefMessageType      - The message type of the genericMessageNodeId.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvGefGenericMessageGetMessageType(
    IN  HPVT                                hPvt,
    IN  RvPvtNodeId                         genericMessageNodeId,
    OUT RvGefMessageType                    *pGefMessageType);


#ifdef __cplusplus
}
#endif

#endif /* _RV_GEF_GENERAL_H_ */
