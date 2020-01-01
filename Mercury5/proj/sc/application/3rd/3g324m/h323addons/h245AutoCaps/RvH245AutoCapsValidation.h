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

#ifndef _RV_H245_AUTO_CAPS_VALIDATION_H_
#define _RV_H245_AUTO_CAPS_VALIDATION_H_


/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/

#include "RvH245AutoCapsTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*/
/*                           TYPE DEFINITIONS                            */
/*-----------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/*                           FUNCTION HEADERS                           */
/*-----------------------------------------------------------------------*/

/******************************************************************************
 * RvH245AutoCapsInit
 * ----------------------------------------------------------------------------
 * General: Initializes the H.245 AutoCaps module. This function should be called
 *          only once.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  maxNumberOfValidationFunctions - Maximum total number of validation 
 *                                          functions to be used for all 
 *                                          H.245 AutoCaps instances.
 * Output: hH245AutoCaps				  - The H.245 AutoCaps handle.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsInit(
    IN  RvUint32       maxNumberOfValidationFunctions,
    OUT HH245AUTOCAPS  *hH245AutoCaps);

/******************************************************************************
 * RvH245AutoCapsEnd
 * ----------------------------------------------------------------------------
 * General: Ends the H.245 AutoCaps module.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hH245AutoCaps - The H.245 AutoCaps handle.
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsEnd(
    IN HH245AUTOCAPS hH245AutoCaps);


/******************************************************************************
 * RvH245AutoCapsGetSize
 * ----------------------------------------------------------------------------
 * General: Gets the size of the information object of this module. This function
 *          should be called before RvH245AutoCapsConstruct().
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  None.
 * Output: objectSize             - The size of the information object that
 *                                  the application will allocate.
 *                                  This object should be passed to each API
 *                                  function in this module after being cast
 *                                  to the HH245AUTOCAPS handle.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsGetSize(
    OUT RvUint32 *objectSize);

/******************************************************************************
 * RvH245AutoCapsConstruct
 * ----------------------------------------------------------------------------
 * General: Constructs the H.245 AutoCaps call object. This function should be 
 *          called for each 3G-324M call.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hH245AutoCaps - Handle to the H.245 AutoCaps module.
 *         hAutoCapsCall - Handle to the H.245 AutoCaps call object allocated
 *                         by the user.
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsConstruct(
    IN HH245AUTOCAPS hH245AutoCaps,
    IN HAUTOCAPSCALL hAutoCapsCall);


/******************************************************************************
 * RvH245AutoCapsEncodeToBuffer
 * ----------------------------------------------------------------------------
 * General: Encodes the AutoCaps call object into a buffer.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hAutoCapsCall - Handle to the H.245 AutoCaps call object to be encoded.
 *         size          - Size of the given buffer.
 * Output: buffer        - The buffer containing the encoded AutoCaps.
 *         size          - Size of the buffer used.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsEncodeToBuffer(
    IN    HAUTOCAPSCALL hAutoCapsCall,
    INOUT RvSize_t      *size,
    OUT   RvUint8       *buffer);


/******************************************************************************
 * RvH245AutoCapsConstructFromBuffer
 * ----------------------------------------------------------------------------
 * General: Constructs and decodes the AutoCaps call object from a buffer.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hH245AutoCaps - Handle to the H.245 AutoCaps module.
 *         hAutoCapsCall - Handle to the new H.245 AutoCaps call object
 *                         allocated by the user, to be decoded to.
 *         size          - Size of the given buffer.
 *         buffer        - The buffer containing the encoded AutoCaps.
 *         hPvt          - The PVT handle.
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsConstructFromBuffer(
    IN HH245AUTOCAPS    hH245AutoCaps,
    IN HAUTOCAPSCALL    hAutoCapsCall,
    IN RvSize_t         size,
    IN RvUint8          *buffer,
    IN HPVT             hPvt);


/******************************************************************************
 * RvH245AutoCapsDestruct
 * ----------------------------------------------------------------------------
 * General: Destructs the H.245 Auto caps module.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hAutoCapsCall - Handle to the H.245 AutoCaps call object.
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsDestruct(
    IN HAUTOCAPSCALL hAutoCapsCall);

/******************************************************************************
 * RvH245AutoCapsReset
 * ----------------------------------------------------------------------------
 * General: Resets the H.245 Auto caps module when the call is being reset.
 *          This function should be called in the Resetting state of the call.
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hAutoCapsCall - Handle to the H.245 AutoCaps call object.
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsReset(
    IN HAUTOCAPSCALL hAutoCapsCall);

/******************************************************************************
 * RvH245AutoCapsSetCallHandle
 * ----------------------------------------------------------------------------
 * General: Sets the call handle to the H.245 Auto caps module.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hAutoCapsCall - Handle to the H.245 AutoCaps call object.
 *         hCall         - Handle to the call.
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsSetCallHandle(
    IN HAUTOCAPSCALL hAutoCapsCall,
    IN HCALL         hCall);

/******************************************************************************
 * RvH245AutoCapsSetChannelHandle
 * ----------------------------------------------------------------------------
 * General: Sets the channel handle to the H.245 AutoCaps call object.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hAutoCapsCall - Handle to the H.245 AutoCaps call object.
 *         hChan         - Handle to the channel.
 *         eChannelType  - The type of the channel to set.
 *                         RvH245AutoCapsChannelTypeAll type will be ignored.
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsSetChannelHandle(
    IN HAUTOCAPSCALL             hAutoCapsCall,
    IN HCHAN                     hChan,
    IN cmChannelDataType         eChannelType);

/******************************************************************************
 * RvH245AutoCapsSetPVTHandle
 * ----------------------------------------------------------------------------
 * General: Sets the PVT handle to the H.245 Auto caps module.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hAutoCapsCall - Handle to the H.245 AutoCaps call object.
 *         hPvt          - The PVT handle.
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsSetPVTHandle(
    IN HAUTOCAPSCALL hAutoCapsCall,
    IN HPVT          hPvt);

/******************************************************************************
 * RvH245AutoCapsSetValidateFunctions
 * ----------------------------------------------------------------------------
 * General: Sets the validate functions object to the H.245 Auto caps.
 *          Note that this function sets validation functions that will be
 *          used by all H.245 Auto Caps instances. Therefore it should be called
 *          once and not for each instance separately.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hH245AutoCaps         - Handle to the H.245 AutoCaps module.
 *		   validateFunctions     - The validate functions array.
 *         validateFunctionsSize - Number of elements in validateFunctions array. 
 *                                 This value cannot exceed the initial value that 
 *                                 was passed to RvH245AutoCapsInit().
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsSetValidateFunctions(
    IN HH245AUTOCAPS                    hH245AutoCaps,
    IN RvH245AutoCapsValidateFunctions  *validateFunctions,
    IN RvUint32                         validateFunctionsSize);

/******************************************************************************
 * RvH245AutoCapsSetContext
 * ----------------------------------------------------------------------------
 * General: Sets the context to the H.245 AutoCaps module. This parameter will
 *          be used in the validate functions.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hAutoCapsCall - Handle to the H.245 AutoCaps call object.
 *         context       - The context to be set.
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsSetContext(
    IN HAUTOCAPSCALL hAutoCapsCall,
    IN void          *context);

/******************************************************************************
 * RvH245AutoCapsSetEvHandlers
 * ----------------------------------------------------------------------------
 * General: Sets the event handlers needed for this module.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hAutoCapsCall       - Handle to the H.245 AutoCaps call object.
 *         eventHandlers       - The event handlers of this module. Should
 *                               be set just after initialization of the module.
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsSetEvHandlers(
    IN HAUTOCAPSCALL                   hAutoCapsCall,
    IN RvH245AutoCapsEvHandlers        *eventHandlers);


/******************************************************************************
 * RvH245AutoCapsGetSessionResetSupport
 * ----------------------------------------------------------------------------
 * General: Gets the indication from the H.245 Auto caps module on whether 
 *          both sides support SessionResetCapability,
 *          Note that the indication may be changed after each incoming TCS message.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hAutoCapsCall - Handle to the H.245 AutoCaps call object.
 * Output: bSessionReset - Defines whether SessionResetCapability is supported
 *                         by both sides.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsGetSessionResetSupport(
    IN  HAUTOCAPSCALL hAutoCapsCall,
    OUT RvBool        *bSessionReset);


/******************************************************************************
 * RvH245AutoCapsGetMaximumAl2SDUSize
 * ----------------------------------------------------------------------------
 * General: Gets the indication on the maximum AL2 SDU size of the remote side.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hAutoCapsCall  - Handle to the H.245 AutoCaps call object.
 * Output: maxAl2SUDSize  - The maximum AL2 SDU size.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsGetMaximumAl2SDUSize(
    IN  HAUTOCAPSCALL   hAutoCapsCall,
    OUT RvUint16        *maxAl2SUDSize);

/******************************************************************************
 * RvH245AutoCapsGetMaximumAl3SDUSize
 * ----------------------------------------------------------------------------
 * General: Gets the indication on the maximum AL3 SDU size of the remote side.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hAutoCapsCall  - Handle to the H.245 AutoCaps call object.
 * Output: maxAl3SUDSize  - The maximum AL3 SDU size.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsGetMaximumAl3SDUSize(
    IN  HAUTOCAPSCALL   hAutoCapsCall,
    OUT RvUint16        *maxAl3SUDSize);

/******************************************************************************
 * RvH245AutoCapsGetMaximumDelayJitter
 * ----------------------------------------------------------------------------
 * General: Gets the indication on the maximum delay jitter of the remote side.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hAutoCapsCall  - Handle to the H.245 AutoCaps call object.
 * Output: maxDelayJitter - The maximum delay jitter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsGetMaximumDelayJitter(
    IN  HAUTOCAPSCALL   hAutoCapsCall,
    OUT RvUint16        *maxDelayJitter);

/******************************************************************************
 * RvH245AutoCapsGetChannelHandle
 * ----------------------------------------------------------------------------
 * General: Gets the channel handle from the H.245 Auto caps module.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hAutoCapsCall - Handle to the H.245 AutoCaps call object.
 *         eChannelType  - The type of the channel to set. The type
 *                         RvH245AutoCapsChannelTypeAll will be ignored.
 * Output: hChan         - Handle to the channel.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsGetChannelHandle(
    IN  HAUTOCAPSCALL             hAutoCapsCall,
    IN  cmChannelDataType         eChannelType,
    OUT HCHAN                     *hChan);

/******************************************************************************
 * RvH245AutoCapsOpenChannels
 * ----------------------------------------------------------------------------
 * General: Validates the capabilities before opening logical channels.
 *          This function should be called only after the HCHAN objects have been
 *          constructed, by calling cmChannelNew(). The function validates
 *          the capabilities and then opens the channels, by calling
 *          cmChannelOpenDynamic().
 *          If the application wants the function to consider its own adaptation 
 *          layer preferences, it should set these preferences to the HCHAN objects
 *          before calling the function (e.g., parameters such as 
 *          cmChannelParamH223AlLevel, cmChannelParamH223Al1Framed,
 *          cmChannelParamH223Al2SequenceNumber,
 *          cmChannelParamH223Al3ControlFieldSize and
 *          cmChannelParamH223Al3SendBufferSizeForRetransmissions).
 *          Note that this function does not yet support cases in which 
 *          eChannelType is cmChannelDataTypeVideo2 or cmChannelDataTypeData.
 *
 * Return Value: RV_OK if successful. Other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hAutoCapsCall            - The handle to the H.245 AutoCaps call object.
 *                                    The application must set all the information
 *                                    needed for the validation to this handle.
 *         eChannelType             - Channel type to validate.
 * Output: eErrorReason             - Defines the error reason description if
 *                                    this function fails and returns a
 *                                    negative status value.
 *                                    If the function succeeds, there is no
 *                                    reason to check this parameter.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV RvH245AutoCapsOpenChannels(
    IN     HAUTOCAPSCALL              hAutoCapsCall,
    IN     cmChannelDataType          eChannelType,
    OUT    RvH245AutoCapsErrorReason  *eErrorReason);


#ifdef __cplusplus
}
#endif

#endif /* _RV_H245_AUTO_CAPS_VALIDATION_H_ */
