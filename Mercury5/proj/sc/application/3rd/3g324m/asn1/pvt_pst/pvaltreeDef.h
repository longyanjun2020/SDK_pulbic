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

#ifndef _PVALTREE_DEF_H
#define _PVALTREE_DEF_H

#include "rtree.h"
#include "rpool.h"
#include "rvmutex.h"
#include "psyntreeDb.h"
#include "psyntreeStackApi.h"
#include "pvaltree.h"

#ifdef __cplusplus
extern "C" {
#endif




/************************************************************************
 * pvtPrintDegree enum
 * Used to define what will be printed for each node of a tree
 ************************************************************************/
typedef enum
{
  pvtPrintDegreeSyntax      = 0x1, /* Display syntax information */
  pvtPrintDegreeNodeId      = 0x2, /* Display node ID for each node */
  pvtPrintDegreeValue       = 0x4, /* Always print the node's value */
  pvtPrintDegreeSyntaxId    = 0x8, /* Display syntax node ID for each node */

  pvtPrintDegreeNone        = 0x0, /* Print nothing */
  pvtPrintDegreeAll         = 0xffff /* Print everything */
} pvtPrintDegree;


/************************************************************************
 * vtStruct
 * PVT handle contents
 ************************************************************************/
typedef struct
{
    HRTREE          vTree; /* Value tree handle to use.
                              Should be first field for performance reasons */
    HRPOOL          sPool; /* Strings pool. Holds all the strings for the nodes.
                              It actually points to the same place as vTree. */
    RvLogMgr*       logMgr; /* Log manager that constructed this PV handle */
    RvLogSource     log; /* Log handle to use for PVT related messages */
    RvLogSource     unregLog; /* Log handle used for PVT messages by user on no-log handle */
    RvLock          lock; /* Mutex to use for locking */

    /* Printing related variables */
    pvtPrintFuncP   pFunc; /* Print function to use for each node printed */
    void *          pFuncParam; /* The context to pass to the print function on each printed line */
    RvBool          printOnlyRoots; /* Indicates if debug printing of all nodes will
                                       print only the roots or the whole trees */
    pvtPrintDegree  degree; /* Details degree of the printing */
} vtStruct;


/************************************************************************
 * vtNode
 * PVT node contents
 ************************************************************************/
typedef struct
{
    HPST        hSyn; /* Syntax tree of the node.
                         Make sure it's first (optimized pointer access) */
    RvUint32    synFieldAndNode; /* Field and node in syntax tree */
    HRPOOLELEM  string; /* String stored inside node, NULL if it doesn't exist */
    RvInt32     value; /* Value of node for non-string values.
                          Length of string for string values */
#ifdef RV_DEBUG
    RvBool      shieldedNode; /* (debug only) RV_TRUE if this node was created by 
                                 the stack and is important to it. */
#endif
} vtNode;





/************************************************************************
 *
 *                          Private macros
 *
 ************************************************************************/



#define VTN_SYN_FIELD(_vtnode) ((RvUint16)((_vtnode)->synFieldAndNode & 0xFFFF))
#define VTN_SYN_NODE(_vtnode)  ((RvPstNodeId)((RvUint16)((_vtnode)->synFieldAndNode >> 16)))


#define VTN_SET_SYN_INFO(vtnode, node, field) \
    ((vtnode)->synFieldAndNode = ((RvUint)node << 16) + (RvUint16)field)
#define VTN_SET_SYN_FIELD(vtnode, field) \
    ((vtnode)->synFieldAndNode = ((vtnode)->synFieldAndNode & 0xFFFF0000) + (RvUint)field);
#define VTN_SET_SYN_NODE(vtnode, node) \
    ((vtnode)->synFieldAndNode = ((vtnode)->synFieldAndNode & 0xFFFF) + ((RvUint)node << 16))


#define GET_NODE(_vt, _nodeId) \
    ((vtNode *)rtGetByPath(((vtStruct *)(_vt))->vTree, (int)(_nodeId)))



/* Definitions of errors in the pvt */
#define RV_PVT_ERROR_UNKNOWN (RvPvtNodeId)RV_ERROR_UNKNOWN
#define RV_PVT_ERROR_OUTOFRESOURCES (RvPvtNodeId)RV_ERROR_OUTOFRESOURCES



#ifdef __cplusplus
}
#endif


#endif  /* _PVALTREE_DEF_H */

