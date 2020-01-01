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


/*
  psyntree.h

  Syntax tree interface.
  Provides access to a single compilation unit of ASN modules.

  Parameters:
   - synH: Syntax tree handler.
   - nodeId: ID of node in the syntax tree. Unique identifier.
   - node: Node information unit. Allocated by the user.
   - child: Field under the node information unit. Allocated by the user.
   - index: >=1.

  Notes:
   - Field names are identical to names in asn text file. The names are NULL terminated.
   - Output pointer parameters may be null. This means that they are ignored.

  */

#ifndef _PSYNTREE_H
#define _PSYNTREE_H

#include "rvtypes.h"
#include "rverror.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Syntax field ID definition. */
/* A field ID is the identification value of a field inside a specific CHOICE or SEQUENCE. */
#if (defined(RV_H323_VERSION_DEFINITIONS) && (RV_H323_VERSION_DEFINITIONS <= 400))
/* Up to version 4 of the H.323 Stack, the fieldIds of these API functions were declared
   as INTPTR, and not RvPstFieldId. */
#define RvPstFieldId INTPTR

#else

typedef RvInt RvPstFieldId;
#endif


/* Syntax node ID definition. */
/* A node ID is the identification value of a type in an ASN.1 definition. */
typedef RvInt RvPstNodeId;


/* An indication of an invalid node ID. */
#define RV_PST_INVALID_NODEID (RvPstNodeId)-1

/* Macro definition indicating whether a node ID is valid or not. */
#define RV_PST_NODEID_IS_VALID(_nodeId) ((RvInt)(_nodeId) >= 0)


typedef enum
{
    /*** Simple types ***/
    pstInteger = 1,
    pstNull = 2,
    pstBoolean = 3,
    pstEnumeration = 4,
    pstObjectIdentifier = 5,
    pstOctetString = 6,

    /*** Strings ***/
    pstBitString = 7,
    pstGeneralString = 8,
    pstUniversalString = 9,
    pstBMPString = 10,
    pstIA5String = 11,
    pstVisibleString = 12,
    pstNumericString = 13,
    pstPrintableString = 14,

    /*** Complex types ***/
    pstChoice = 15,
    pstSequence = 16,
    pstSet = 17,
    pstOf = 18,
    pstSequenceOf = 19,
    pstSetOf = 20,

    /*** Proprietary types ***/
    pstNotSupported = 21

} pstNodeType;


typedef enum
{
    pstTagUniversal = 1,
    pstTagApplication = 2,
    pstTagPrivate = 3,
    pstTagEmpty = 4
} pstTagClass;

/* child record type */
typedef struct
{
    int         index;           /* Number of the child, starting at 1.
                                    Negative value on failure if invalid. */
    RvPstNodeId nodeId;          /* Child's node ID. */
    RvInt32     fieldId;         /* Child's field ID. */
    RvBool      isOptional;      /* RV_TRUE if the child is optional. */
} pstChild;



RV_DECLARE_HANDLE(HPST); /* Syntax tree handle */



/************************************************************************
 * pstConstruct
 * purpose: Creates a PST handle for a type in an ASN.1 definition.
 *          This function uses dynamic allocation when called.
 * input  : syntax      - The syntax buffer to use (the output of the ASN.1 compiler).
 *                        The buffer is the parameter returned by
 *                        cmEmGetCommonSyntax(), cmEmGetH245Syntax() and
 *                        cmEmGetQ931Syntax().
 *          rootName    - The root name of the type to create a PST handle.
 * output : None.
 * return : The PST handle on success, or NULL on failure.
 * examples:
 *      hPst = pstConstruct(cmEmGetQ931Syntax(), "AliasAddress");
 *      hPst = pstConstruct(cmEmGetH245Syntax(), "Setup-UUIE.fastStart");
 ************************************************************************/
RVAPI HPST RVCALLCONV
pstConstruct(
    IN  const RvUint8*      syntax,
    IN  const RvChar*       rootName);


/************************************************************************
 * pstDestruct
 * purpose: Destructs a PST handle created by pstConstruct().
 * input  : hSyn    - The PST handle to destruct.
 * output : None.
 * return : A non-negative value on success, or a negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV
pstDestruct(IN HPST hSyn);


RVAPI pstNodeType RVCALLCONV /* type of node */
pstGetNodeType(
           IN  HPST         hSyn,
           IN  RvPstNodeId  nodeId);

/* for Sequence Of XXX/Set Of XXX nodes - returns the ID of XXX */
RVAPI RvPstNodeId RVCALLCONV
pstGetNodeOfId(
     IN  HPST           synH,
     IN  RvPstNodeId    nodeId);

RVAPI int RVCALLCONV /* type of node */
pstGetNodeRange(
      IN  HPST          synH,
      IN  RvPstNodeId   nodeId,
      OUT int *         from,
      OUT int *         to);

#if (RV_ASN1_CODER_USE_Q931 == RV_YES)
RVAPI int RVCALLCONV /* the tag of the node or a negative value on failure */
pstGetTag(
     IN  HPST           synH,
     IN  RvPstNodeId    nodeId,
     OUT pstTagClass*   tagClass);
#endif

RVAPI int RVCALLCONV /* not extended, or a negative value on failure */
pstGetIsExtended(
     IN  HPST           synH,
     IN  RvPstNodeId    nodeId);

#ifdef RV_H323_COMPILE_WITH_DEAD_FUNCTIONS
RVAPI int RVCALLCONV /* not extended, or a negative value on failure */
pstGetIsOpenType(
     IN  HPST           synH,
     IN  RvPstNodeId    nodeId);
#endif

RVAPI RvPstFieldId RVCALLCONV /* field enumeration, or a negative value on failure */
pstGetFieldId(
        /* convert field name to internal ID */
        IN  HPST        synH,
        IN  const char *fieldName /* null-terminated string */
        );

RVAPI int RVCALLCONV /* real length of the field name, or a negative value on failure */
pstGetFieldName(
      /* convert field internal ID to field name */
      IN  HPST synH,
      IN  RvPstFieldId fieldId,
      IN  int fieldNameLength, /* number of bytes in the string allocation */
      OUT char* fieldName /* user allocated */
      );

RVAPI char* RVCALLCONV /* null-terminated token name */
pstGetTokenName(
      IN pstNodeType type);

/******************************************************************************
 * pstGetFROMString
 * ----------------------------------------------------------------------------
 * General: Gets the string that defines the alphabet of the given string ASN.1 type.
 *
 * Return Value: The actual length of the FROM constrain string if successful.
 *               Negative error value on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hSyn             - The PST handle.
 *         nodeId           - The PST node ID of the string ASN.1 type.
 *         fromStringLength - Length of the fromString parameter passed to this 
 *                            function, in bytes.
 * Output: fromString       - FROM constrain string. If given as NULL, this
 *                            parameter will be ignored.
 *****************************************************************************/
RVAPI  int RVCALLCONV
pstGetFROMString(
   IN  HPST         hSyn,
   IN  RvPstNodeId  nodeId,
   IN  int          fromStringLength,
   OUT char*        fromString);

RVAPI RvPstNodeId RVCALLCONV /* Internal node ID, or a negative value on failure */
pstGetNodeIdByPath(
         /* gets internal node ID from the specified node path.
        The path to the node should start at the root and correspond to the
        ASN module syntax structure */
         IN  HPST        synH,
         IN  const char *path  /* format: "a.b.c" */
         );


RVAPI int RVCALLCONV /* the length of the root name, or a negative value on failure */
pstGetRootName(
     /* Note: If bufferLength is smaller than the name length,
        the correct length is returned but the buffer will
        not be valid. */
     IN  HPST    synH,
     IN  int     bufferLength,   /* Target buffer length */
     OUT char *  buffer          /* Target buffer for root name */
     );

RVAPI int RVCALLCONV
pstGetNumberOfChildren(
         IN  HPST           synH,
         IN  RvPstNodeId    nodeId);


RVAPI RvPstNodeId RVCALLCONV
pstGetChild(
            IN  HPST        hSyn,
            IN  RvPstNodeId nodeId,      /* Node ID of the parent */
            IN  int         childIndex,  /* Index of the child */
            OUT pstChild*   child);


RVAPI RvBool RVCALLCONV /* True if the node is of one of the following string types: */
/*  pstObjectIdentifier, pstOctetString, pstBitString, pstGeneralString,
  pstUniversalString, pstBMPString, pstIA5String, pstVisibleString,
  pstNumericString, pstPrintableString
*/
pstIsStringNode(
       IN  HPST         hSyn,
       IN  RvPstNodeId  nodeId);


#ifdef __cplusplus
}
#endif

#endif  /* _PSYNTREE_H */


