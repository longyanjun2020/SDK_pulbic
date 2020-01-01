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
  psyntreeStackApi

  Internal Syntax-Tree functions used as API for other stack modules.

  */

#ifndef _PSYNTREE_STACKAPI_H
#define _PSYNTREE_STACKAPI_H

#include "psyntree.h"
#include "rvtypes.h"

#ifdef __cplusplus
extern "C" {
#endif



/************************************************************************
 *
 *                          Public structures
 *
 ************************************************************************/


typedef enum
{
    pstNotSpecial=0,        /* 000 */
    pstDepending=3,         /* 011 */
    pstDependent=5,         /* 101 */
    pstDependingDependent=7 /* 111 */
} pstFieldSpeciality;


typedef enum
{
    pstValueInteger = 0,
    pstValueString  = 1,
    pstValueSubTree = 2
} pstValueType;


/************************************************************************
 * pstChildExt
 * Extended information about a child node inside the syntax tree
 * index            - Index of the child, 1-based
 *                    Negative value if invalid
 * nodeId           - Child's node ID
 * fieldId          - Child's field ID
 * isOptional       - RV_TRUE if the child is an OPTIONAL field in a SEQUENCE
 * isDefault        - RV_TRUE if the child is a DEFAULT field in a SEQUENCE
 * isExtended       - RV_TRUE if the child is an extended field (after ...)
 * speciality       - Dependency between fields
 * enumerationValue - Value if it's an ENUMERATED value field type
 ************************************************************************/
typedef struct
{
    int                 index;
    RvPstNodeId         nodeId;
    RvInt32             fieldId;
    RvBool              isOptional;
    RvBool              isDefault;
    RvBool              isExtended;
#if (RV_ASN1_CODER_USE_H450 == RV_YES)
    pstFieldSpeciality  speciality;
#endif
    int                 enumerationValue;
} pstChildExt;


/* --- value tree root --- */
typedef struct
{
    int             typeReference;
    int             value;/* value of typeReference (integer or string). */
    pstValueType    isString; /* RV_TRUE if value is string */
} pstValueTreeStruct;


/* --- value node --- */
typedef struct
{
    int             fieldName;
    int             value; /* value of field (integer or string). */
    pstValueType    isString; /* RV_TRUE if value is string */
} pstValueNodeStruct;


typedef struct
{
    RvInt32 objectSetId;  /* object set nodeid  -  MUST be referenced */
    RvInt32 fieldInClassNumber; /* field in class number */
} pstTypeFromConstraint;


typedef struct
{
    RvInt32     parentDepth;
    RvPstNodeId fieldId;
    RvInt32     relativeIndex;
} pstConstrainingField;


typedef struct
{
    RvInt32     fieldInClassNumber;
    RvPstNodeId settingId;
} pstFieldOfObjectReference;




/************************************************************************
 *
 *                          Public functions
 *
 ************************************************************************/


/************************************************************************
 * pstGetChildExt
 * purpose: Return extended information about one of the child nodes of
 *          a parent node
 * input  : hSyn        - Syntax tree used
 *          nodeId      - Parent's node ID
 *          childIndex  - Index of the child (1-based)
 * output : child       - Extended child node information
 * return : Pointer to use with pstGetBrotherExt() on success,
 *          NULL on error
 ************************************************************************/
RvUint32* pstGetChildExt(
    IN  HPST            hSyn,
    IN  RvPstNodeId     nodeId,
    IN  int             childIndex,
    OUT pstChildExt*    child);


/************************************************************************
 * pstGetBrotherExt
 * purpose: Return extended information about the right brother of a
 *          node. responsibility not to call for a non-existant brother
 *          is on the caller (use num of children)
 * input  : hSyn        - Syntax tree used
 *          childIndex  - index of the child (not really needed)
 *          nodePtr     - Node pointer to which we want the brother
 * output : brother     - Extended child node information
 * return : Pointer to use (responsibly) in subsequent calls to
 *          stGetBrother()
 ************************************************************************/
RvUint32* pstGetBrotherExt(
    IN  HPST            hSyn,
    IN  int             childIndex,
    IN  RvUint32*       nodePtr,
    OUT pstChildExt*    brother);


int
pstGetField(
        IN  HPST        synH,
        IN  RvPstNodeId nodeId,      /* node id of parent */
        IN  int         fieldId,  /* index of child */
        OUT pstChild*   child);

int
pstGetFieldExt(
            IN  HPST            hSyn,
            IN  RvPstNodeId     nodeId,      /* node id of parent */
            IN  int             fieldId,  /* index of child */
            OUT pstChildExt*    child);

RVINTAPI int RVCALLCONV
pstChildIsExtended(
      IN  HPST        synH,
      IN  int         nodeId,      /* node id of parent */
      IN  int         childIndex    /* index of child */
      );

int
pstGetFirstExtendedChild(
         IN  HPST    synH,
         IN  int     nodeId);

int
pstGetNumberOfOptionalBeforeExtension(
         IN  HPST    synH,
         IN  int     nodeId);


/* null terminated field name */
RVINTAPI char * RVCALLCONV
pstGetFieldNamePtr(
        /* convert field internal id to field name */
        IN  HPST hSyn,
        IN  RvInt32 fieldId
        );


int /* type of node */
pstGetNodeRangeExt(
      IN  HPST    hSyn,
      IN  int     nodeId,
      OUT int *   from,
      OUT int *   to,
      OUT RvBool*   fromAbsent,
      OUT RvBool*   toAbsent);


int
pstChildIsSpecial(
  IN  HPST        synH,
  IN  RvPstNodeId nodeId,      /* node id of parent */
  IN  int         childIndex   /* index of child */
  );


int pstGetTypeFromConstraint(
            IN  HPST                    synH,
            IN  RvPstNodeId             specialTypeNodeId,
            OUT pstTypeFromConstraint*  specialType);

int pstGetConstrainingField(
            IN  HPST                    synH,
            IN  RvPstNodeId             specialTypeNodeId,
            OUT pstConstrainingField*   constrainingField);

int pstGetFieldOfObjectReference(
            IN  HPST                        synH,
            IN  int                         objectNodeId,
            IN  int                         index,
            OUT pstFieldOfObjectReference*  fieldOfObject);

int pstGetValueTreeStruct(
            IN  HPST                        synH,
            IN  int                         vtStructNodeId,
            OUT pstValueTreeStruct*         valueTreeStruct);

int pstGetValueNodeStruct(
            IN  HPST                synH,
            IN  int                 vtNodeNodeId,
            OUT pstValueNodeStruct* valueTreeNode);

/************************************************************************
 * pstCompareFunction
 * purpose: Comparison function used when searching for a specific object
 *          in an association table.
 * input  : hSyn        - Syntax tree used
 *          sNodeId     - Syntax value node to compare
 *          context     - Context to use for comparison
 * output : none
 * return : Negative if the key is lower than elem in dictionary comparison
 *          0 if the key and the element are equal
 *          Positive if the key is higher than elem in dictionary comparison
 ************************************************************************/
typedef int (*pstCompareFunction)(IN HPST hSyn, IN int sNodeId, IN void* context);

/************************************************************************
 * pstFindObjectInAT
 * purpose: Find the type of field from the association table that matches
 *          a given tree node. This is used when trying to encode/decode
 *          messages with object sets.
 * input  : hSyn        - Syntax tree used
 *          atNodeId    - Association table node ID in the syntax tree
 *          compareFunc - Comparison function to use for nodes
 *          context     - Context to use for comparison function
 * output : none
 * return : Node ID of the matching syntax value on success
 *          Negative value on failure
 ************************************************************************/
int pstFindObjectInAT(
    IN HPST                 hSyn,
    IN int                  atNodeId,
    IN pstCompareFunction   compareFunc,
    IN void*                context);

/* RV_TRUE if nodes have the same structure */
RVINTAPI RvBool RVCALLCONV
pstAreNodesCongruent(
            IN HPST         hSyn1,
            IN RvPstNodeId  synNodeId1,
            IN HPST         hSyn2,
            IN RvPstNodeId  synNodeId2);

char* /* actual length of the fromString or negative value on failure */
pstGetFROMStringPtr(
         /* Get the character constraints of the syntax node */
         IN  HPST hSyn,
         IN  RvPstNodeId nodeId,
         OUT int*actualLength);

/* Get root nodeId */

RVINTAPI RvPstNodeId RVCALLCONV
pstGetRoot(IN HPST hSyn);


/************************************************************************
 * pstPrintNode
 * purpose: Print the information of a syntax tree node to a buffer
 * input  : hSyn    - Syntax tree handle
 *          nodeId  - Node to print
 *          buf     - Result buffer to use
 *          len     - Length of buffer
 * output : none
 * return : Number of characters printed
 ************************************************************************/
int pstPrintNode(
    IN  HPST            hSyn,
    IN  RvPstNodeId     nodeId,
    IN  char*           buf,
    IN  int             len);




#ifdef __cplusplus
}
#endif

#endif  /* _PSYNTREE_STACKAPI_H */



