/***********************************************************************
        Copyright (c) 2005 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..

RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/

#ifndef _USER_INPUT_H
#define _USER_INPUT_H

#include "rverror.h"

#ifdef __cplusplus
extern "C" {
#endif



typedef enum
{
    cmUserInputNonStandard = 0,
    cmUserInputAlphanumeric,
    cmUserInputSupport,
    cmUserInputSignal,
    cmUserInputSignalUpdate,
    cmUserInputExtendedAlphanumeric,
    cmUserInputEncryptedAlphanumeric,
    cmUserInputGenericInformation
} cmUserInputIndication;


typedef enum
{
    cmSupportNonStandard = 0,
    cmSupportBasicString, /* alphanumeric */
    cmSupportIA5String, /* alphanumeric */
    cmSupportGeneralString, /* alphanumeric */
    cmSupportDtmf, /* supports dtmf using signal and signalUpdate */
    cmSupportHookflash, /* supports hookflash using signal */
    cmSupportExtendedAlphanumeric,
    cmSupportEncryptedBasicString, /* encrypted Basic string in encryptedAlphanumeric */
    cmSupportEncryptedIA5String, /* encrypted IA5 string in encryptedSignalType */
    cmSupportEncryptedGeneralString, /* encrypted general string in extendedAlphanumeric.encryptedalphanumeric */
    cmSupportSecureDTMF /* secure DTMF using encryptedSignalType */
} cmUserInputSupportIndication;


typedef struct
{
    int timestamp;      /* -1 if optional; */
    int expirationTime; /* -1 if optional;*/
    int logicalChannelNumber;
} cmUserInputSignalRtpStruct;


typedef struct
{
    char                        signalType;
    int                         duration;
    cmUserInputSignalRtpStruct  cmUserInputSignalRtp;/* if logical channel == 0 -optional*/
} cmUserInputSignalStruct;


RVAPI int RVCALLCONV  /* userInput message node ID or negative value on failure */
cmUserInputSupportIndicationBuild(
    /* Build userUser message with alphanumeric data */
    IN  HAPP                            hApp,
    IN  cmUserInputSupportIndication    userInputSupport,
    OUT int*                            nodeId);  /* nodeId of nonstandard UserInputSupportIndication */


RVAPI int RVCALLCONV  /* userInput message node ID or negative value on failure */
cmUserInputSignalBuild(
    /* Builds userUser message with alphanumeric data */
    IN  HAPP                        hApp,
    IN  cmUserInputSignalStruct*    userInputSignalStruct);


RVAPI int RVCALLCONV  /* userInput message node ID or negative value on failure */
cmUserInputSignalUpdateBuild(
    /* Builds userUser message with alphanumeric data */
    IN  HAPP                        hApp,
    IN  cmUserInputSignalStruct*    userInputSignalStruct);


RVAPI int RVCALLCONV  /* RV_TRUE or negative value on failure */
cmUserInputGetDetail(
    IN  HAPP                    hApp,
    IN  RvInt32                 userInputId,
    OUT cmUserInputIndication*  userInputIndication);

RVAPI int RVCALLCONV
cmUserInputGetSignal(
    IN  HAPP                        hApp,
    IN  RvInt32                     signalUserInputId,
    OUT cmUserInputSignalStruct*    userInputSignalStruct);

RVAPI int RVCALLCONV
cmUserInputGetSignalUpdate(
    IN  HAPP                        hApp,
    IN  RvInt32                     signalUserInputId,
    OUT cmUserInputSignalStruct*    userInputSignalStruct);

RVAPI int RVCALLCONV
cmUserInputSupportGet(
    IN  HAPP                            hApp,
    IN  RvInt32                         supportUserInputId,
    OUT cmUserInputSupportIndication*   userInputSupportIndication);

/******************************************************************************
 * cmUserInputBuildWithGenericInformation
 * ----------------------------------------------------------------------------
 * General: Creates a userInputIndication message tree and adds the 
 *          genericInformation node supplied by the user.
 *
 * Return Value: userInputIndication message PVT node ID on success.
 *               RV_PVT_INVALID_NODE_ID on failure. 
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hApp                 - The Stack handle for the application.
 *         genericInformation   - The PVT node ID of the genericInformation sub-tree
 *                                to be added to the message.
 * Output: None.
 *****************************************************************************/ 
RVAPI RvPvtNodeId RVCALLCONV cmUserInputBuildWithGenericInformation(
    IN  HAPP            hApp,
    IN  RvPvtNodeId     genericInformation);

/******************************************************************************
 * cmUserInputGetGenericInformation
 * ----------------------------------------------------------------------------
 * General: Gets the genericInformation node of the userInputIndication message.
 *
 * Return Value: RV_OK on success.
 *				 Negative value on error.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hApp                 - The Stack handle for the application. 
 *		   userInputId			- The userInput message PVT node.
 * Output: genericInformation   - The PVT node ID of the genericInformation sub-tree
 *                                to be added to the message.
 *****************************************************************************/ 
RVAPI RvStatus RVCALLCONV cmUserInputGetGenericInformation(
	   IN  HAPP            hApp,
       IN  RvPvtNodeId     userInputId,
	   OUT RvPvtNodeId	   *genericInformationNodeId);





#ifdef __cplusplus
}
#endif

#endif
