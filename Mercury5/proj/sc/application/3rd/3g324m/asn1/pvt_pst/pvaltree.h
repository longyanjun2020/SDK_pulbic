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
  pvaltree.h

  Tree manipulation.
  Holds message values according to syntax structure.
  Support multiple messages (trees) within a single instance.

  Global behavior:
  All functions return negative values upon illegal parameters or any other error situation.
  Some functions return RV_TRUE on normal conditions.
  OUT pointer parameters may be NULL if there is no need for them.

  Handlers:
   - HPVT: Value tree instance handler.
   - nodeId: Single message (tree) identifier.

  Function parameters:
   - parentId: ID of parent node. Unique node identifier.
   - fieldId: Enumeration of field as in the message.
   - value: Integer value of node.
   - index: Child under parent. >=1
   - path: String description by dotted notation of node location in tree.
           E.g.: root.colors.white
  */

#ifndef _PVALTREE_H
#define _PVALTREE_H

#include "rvtypes.h"
#include "rverror.h"
#include "psyntree.h"
    
#ifdef __cplusplus
extern "C" {
#endif


/* Handler */
RV_DECLARE_HANDLE(HPVT);

/* Print function prototype */
typedef void (*pvtPrintFuncP)(IN void* type, IN const char* line, ...);


/* Node ID definition */
typedef RvInt RvPvtNodeId;


/* Indication of invalid node ID */
#define RV_PVT_INVALID_NODEID (RvPvtNodeId)-1

/* Macro definition indicating whether a node ID is valid or not */
#define RV_PVT_NODEID_IS_VALID(_nodeId) ((RvInt)(_nodeId) >= 0)



/* Defined here to remove dependency of this API header on rvlog.h */
#define RV_PVT_LOGDEBUG 0x10



/************************************************************************
 *
 *                      Field ID Macros
 *
 ************************************************************************/

/* Macros for convenient access to paths by field IDs */
#ifndef LAST_TOKEN
#define LAST_TOKEN (-5) /* Last token in fieldPath parameters */
#endif

#ifndef MAX_TOKEN
#define MAX_TOKEN  100 /* Maximal elements in a path */
#endif

/* Macros used to specify any value of the given choice. They are the equivalent of '*' in
   their string functions */
#define _anyField RvInt16Const(-1),
#define __anyField RvInt16Const(-1)

/* Used to specify the index of the value inside a SEQUENCE OF */
#define _nul(_a) (RvInt16)(-((RvInt16)_a)-100),
#define __nul(_a) (RvInt16)(-((RvInt16)_a)-100)


/* Macros that allow easier access to the fields through the pvtXXXByFieldIds */
#define __pvtGetByFieldIds(_res, _valH, _nodeId, _path, _fieldId, _value, _isString) \
    { static RvInt16 fieldPath[] = _path; \
      _res = pvtGetByFieldIds(_valH, _nodeId, fieldPath, _fieldId, _value, _isString); \
    }
#define __pvtGetNodeIdByFieldIds(_res, _valH, _nodeId, _path) \
    { static RvInt16 fieldPath[] = _path; \
      _res = pvtGetNodeIdByFieldIds(_valH, _nodeId, fieldPath); \
    }
#define __pvtBuildByFieldIds(_res, _valH, _rootNodeId, _path, _value, _strValue) \
    { static RvInt16 fieldPath[] = _path; \
      _res = pvtBuildByFieldIds(_valH, _rootNodeId, fieldPath, _value, _strValue); \
    }


/************************************************************************
 * pvtConstruct
 * purpose: Constructs a pool of PVT nodes.
 * input  : stringBufferSize    - Not used.
 *          numOfNodes          - The maximum number of nodes allowed
 *                                in the tree.
 * output : None.
 * return : Handle to PVT constructed on success. NULL on failure.
 ************************************************************************/
RVAPI HPVT RVCALLCONV pvtConstruct(
    IN  int stringBufferSize,
    IN  int numOfNodes);

/************************************************************************
 * pvtDestruct
 * purpose: Destructs a pool of PVT nodes.
 * input  : hVal    - The PVT handle.
 * output : None.
 * return : Non-negative value on success. Negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV pvtDestruct(
    IN  HPVT hVal);

/************************************************************************
 * pvtGetRoot
 * purpose: Returns the node ID of the root of a Value Tree to which a
 *          specified node belongs.
 * input  : hVal    - The PVT handle.
 *          nodeId  - The ID of the node inside a tree.
 * output : None.
 * return : Root node ID of the given node ID on success. Negative value on failure.
 ************************************************************************/
RVAPI RvPvtNodeId RVCALLCONV pvtGetRoot(
    IN  HPVT         hVal,
    IN  RvPvtNodeId  nodeId);

/************************************************************************
 * pvtGetSynTree
 * purpose: Returns a handle to the structure (Syntax Tree) definition of
 *          a specified node.
 * input  : hVal    - The PVT handle.
 *          nodeId  - The ID of the node the syntax of which is returned.
 * output : None.
 * return : A handle to the structure (Syntax Tree) definition on success.
 *          NULL on failure.
 ************************************************************************/
RVAPI HPST RVCALLCONV pvtGetSynTree(
    IN  HPVT          hVal,
    IN  RvPvtNodeId   nodeId);


/*** Statistics ***/

/************************************************************************
 * pvtCurSize
 * purpose: Gets the number of nodes currently used in the Value Tree forest.
 * input  : hVal    - The PVT handle.
 * output : None.
 * return : The number of nodes in the Value Tree forest on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV pvtCurSize(
    IN HPVT hVal);

/************************************************************************
 * pvtMaxUsage
 * purpose: Gets the highest number of nodes used in the Value Tree forest
 *          since the cmInitialize() function was called.
 * input  : hVal    - The PVT handle.
 * output : None.
 * return : The maximum number of nodes used in the Value Tree forest on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV pvtMaxUsage(
    IN HPVT hVal);

/************************************************************************
 * pvtMaxSize
 * purpose: Gets the highest number of nodes that can be used in the Value Tree forest.
 * input  : hVal    - The PVT handle.
 * output : None.
 * return : The maximum number of nodes in the Value Tree forest on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV pvtMaxSize(
    IN HPVT hVal);

/************************************************************************
 * pvtPoolStatistics
 * purpose: Gets pool statistics (space is in bytes).
 * input  : hVal            - The PVT handle.
 * output : poolSize        - Maximum size of pool.
 *          availableSpace  - Current available space.
 *          maxFreeChunk    - Always returned as 0.
 *          numOfChunks     - Always returned as 0.
 *          If any output parameter is set to NULL, it will be discarded.
 * return : Non-negative value on success. Negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV pvtPoolStatistics(
    IN  HPVT     hVal,
    OUT RvInt32* poolSize,
    OUT RvInt32* availableSpace,
    OUT RvInt32* maxFreeChunk,
    OUT RvInt32* numOfChunks);

/************************************************************************
 * pvtTreeSize
 * purpose: Returns the number of nodes included in a Value Tree root.
 * input  : hVal        - The PVT handle.
 *          parentId    - The ID of any node. The function returns the
 *                        number of nodes located under the specified parent.
 * output : None.
 * return : The number of nodes included in a Value Tree on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV pvtTreeSize(
    IN  HPVT        hVal,
    IN  RvPvtNodeId parentId);

/************************************************************************
 * pvtNumChilds
 * purpose: Returns the number of dependents (children) of a parent tree.
 * input  : hVal        - The PVT handle.
 *          parentId    - The ID of any node.
 * output : None.
 * return : The number of immediate nodes under the given node on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV pvtNumChilds(
    IN  HPVT        hVal,
    IN  RvPvtNodeId parentId);

/************************************************************************
 * pvtParent
 * purpose: Returns the ID of the parent node of a specified node.
 * input  : hVal        - The PVT handle.
 *          nodeId      - The ID of any node.
 * output : None.
 * return : The parent ID of the given node on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI RvPvtNodeId RVCALLCONV pvtParent(
      IN  HPVT          hVal,
      IN  RvPvtNodeId   nodeId);

/************************************************************************
 * pvtBrother
 * purpose: Returns the node ID of the brother (i.e., to the right) of a specified node.
 * input  : hVal        - The PVT handle.
 *          nodeId      - The ID of any node.
 * output : None.
 * return : The node ID of the given node's brother on success.
 *          Negative value on failure.
 *          The function returns the next child (rightward). Use pvtChild() 
 *          to get the first dependent, and then use pvtBrother() to get to 
 *          the next brother.
 ************************************************************************/
RVAPI RvPvtNodeId RVCALLCONV pvtBrother(
       IN  HPVT         hVal,
       IN  RvPvtNodeId  nodeId);

/************************************************************************
 * pvtLBrother
 * purpose: Gets the ID of the node before (i.e., to the left of) a particular node.
 * input  : hVal        - The PVT handle.
 *          nodeId      - The ID of any node.
 * output : None.
 * return : The node ID of the previous node on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI RvPvtNodeId RVCALLCONV pvtLBrother(
    IN  HPVT         hVal,
    IN  RvPvtNodeId  nodeId);

/************************************************************************
 * pvtChild
 * purpose: Returns the node ID of the first (leftmost) child of a parent.
 * input  : hVal        - The PVT handle.
 *          parentId    - The ID of any node.
 * output : None.
 * return : The node ID of the first (leftmost) child of a parent on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI RvPvtNodeId RVCALLCONV pvtChild(
    IN  HPVT         hVal,
    IN  RvPvtNodeId  parentId);

/************************************************************************
 * pvtNext
 * purpose: Returns the ID of a node located after a specified node.
 * input  : hVal    - The PVT handle.
 *          rootId  - The ID of the root node of the current Value Tree.
 *          location- A Node ID inside the given root.
 * output : None.
 * return : The node ID of the next node in the tree on success; this
 *          value should be given as the location on the next call.
 *          Negative value on failure.
 ************************************************************************/
RVAPI RvPvtNodeId RVCALLCONV pvtNext(
    IN  HPVT            hVal,
    IN  RvPvtNodeId     rootId,
    IN  RvPvtNodeId     location);

/************************************************************************
 * pvtAddRootFromInt
 * purpose: Adds a new root to PVT. This function should not be used
 *          directly by user applications. It is called internally through
 *          macros or other Stack functions.
 * input  : hVal    - PVT handle to use.
 *          hSyn    - Syntax tree to use.
 *                    May be set to -1 if it is supplied later (by pvtSetTree).
 *          nodePath- Syntax node ID to use for the root.
 *                    May be set to -1 if it is supplied later or if
 *                    it will be the root of the created syntax tree.
 *          value   - Value of the root node, or length of the value if the
 *                    value is a string.
 *          string  - String value of the node, or NULL if it is not a string.
 *          fileName- Filename that called this function.
 *                    NULL if unknown.
 *          lineno  - Line number in the filename that called this function.
 *                    0 if unknown.
 * output : None.
 * return : Node ID of the added root on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI RvPvtNodeId RVCALLCONV pvtAddRootFromInt(
    IN  HPVT            hVal,
    IN  HPST            hSyn,
    IN  RvPstNodeId     nodePath,
    IN  RvInt32         value,
    IN  const RvChar*   string,
    IN  const RvChar*   fileName,
    IN  int             lineno);

/* Remove macro definitions for these functions. The definitions are there to allow
   information about these functions to be printed. */
#if defined(pvtAddRoot) || defined(pvtAddRootByPath)
#undef pvtAddRoot
#undef pvtAddRootByPath
#endif


/************************************************************************
 * pvtAddRoot
 * purpose: Adds a new node that constitutes the root of a new tree.
 * input  : hVal    - PVT handle to use.
 *          synH    - Syntax tree to use.
 *                    May be set to -1 if it is supplied later (by pvtSetTree).
 *          value   - Value of the root node, or length of the value if the
 *                    value is a string.
 *          string  - String value of the node, or NULL if it is not a string.
 * output : None.
 * return : Node ID of the added root on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI RvPvtNodeId RVCALLCONV pvtAddRoot(
    IN  HPVT            hVal,
    IN  HPST            synH,
    IN  RvInt32         value,
    IN  const RvChar*   string);

/************************************************************************
 * pvtAddRootByPath
 * purpose: Adds a new node that constitutes the root of a new tree.
 * input  : hVal        - PVT handle to use.
 *          synH        - Syntax tree to use.
 *                        May be set to -1 if it is supplied later (by pvtSetTree).
 *          syntaxPath  - A path separated by periods (for example, "a.b.c") that
 *                        identifies the node of the Value Tree's syntax node.
 *                        The path starts from the syntax handle root node.
 *          value       - Value of the root node, or length of the value if the
 *                        value is a string.
 *          string      - String value of the node, or NULL if it is not a string.
 * output : None.
 * return : Node ID of the added root on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI RvPvtNodeId RVCALLCONV pvtAddRootByPath(
    IN  HPVT            hVal,
    IN  HPST            synH,
    IN  const RvChar*   syntaxPath,
    IN  RvInt32         value,
    IN  const RvChar*   string);

/************************************************************************
 * pvtAdd
 * purpose: Adds child node under parentId.
 *          The new node is placed in its relative position according to the syntax tree
 *          indexing of SEQUENCE fields of structure.
 * input  : hVal        - PVT handle to use.
 *          parentId    - The node ID of the immediate parent of the new node.
 *          fieldId     - The field ID returned by pstGetFieldId().
 *                        If set to -1, it will be copied from the parent node.
 *          value       - Value of the root node, or length of the value if
 *                        the value is a string.
 *          string      - String value of the node, or NULL if it is not a string.
 * output : index       - The index of the added child (1-based).
 * return : Node ID of the added node on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI RvPvtNodeId RVCALLCONV pvtAdd(
    IN  HPVT            hVal,
    IN  RvPvtNodeId     parentId,
    IN  RvPstFieldId    fieldId,
    IN  RvInt32         value,
    IN  const RvChar*   string,
    OUT int*            index);

/************************************************************************
 * pvtAddTree
 * purpose: Copies a sub-tree and places it under a specified parent in
 *          another sub-tree.
 * input  : destH       - The handle returned by cmGetValTree() for the
 *                        parent (destination).
 *          destNodeId  - The node ID of the parent (destination).
 *                        The new sub-tree is placed under this node.
 *          srcH        - The handle returned by cmGetValTree() for the
 *                        source (copied sub-tree).
 *          srcNodeId   - The ID of the root node of the source sub-tree.
 * output : None.
 * return : Node ID of the added node on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI RvPvtNodeId RVCALLCONV pvtAddTree(
    IN  HPVT        destH,
    IN  RvPvtNodeId destNodeId,
    IN  HPVT        srcH,
    IN  RvPvtNodeId srcNodeId);

/************************************************************************
 * pvtAddChilds
 * purpose: Copies a sub-tree excluding its root node, and places it under
 *          a specified parent.
 * input  : destH       - The handle returned by cmGetValTree() for the
 *                        parent (destination).
 *          destNodeId  - The node ID of the parent (destination).
 *                        The new sub-tree is placed under this node.
 *          srcH        - The handle returned by cmGetValTree() for the
 *                        source (copied sub-tree).
 *          srcNodeId   - The ID of the root node of the source sub-tree.
 * output : None.
 * return : Non-negative value on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV pvtAddChilds(
    IN  HPVT        destH,
    IN  RvPvtNodeId destNodeId,
    IN  HPVT        srcH,
    IN  RvPvtNodeId srcNodeId);

/************************************************************************
 * pvtDeleteDbg
 * purpose: Deletes a sub-tree, with debug information.
 * input  : hVal            - PVT handle to use.
 *          subTreeRootId   - The ID of the root node to delete.
 *          fileName        - File from which pvtDelete was called.
 *          lineno          - Line number in the file.
 * output : None.
 * return : Non-negative value on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV pvtDeleteDbg(
    IN  HPVT          hVal,
    IN  RvPvtNodeId   subTreeRootId,
    IN  const char*   fileName,
    IN  int           lineno);

/* Remove macro definitions for these functions. The definitions are there to allow
   information about these functions to be printed. */
#if defined(pvtDelete)
#undef pvtDelete
#endif

/************************************************************************
 * pvtDelete
 * purpose: Deletes a sub-tree.
 * input  : hVal            - PVT handle to use.
 *          subTreeRootId   - The ID of the root node to delete.
 * output : None.
 * return : Non-negative value on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV pvtDelete(
    IN  HPVT          hVal,
    IN  RvPvtNodeId   subTreeRootId);

/************************************************************************
 * pvtDeleteChilds
 * purpose: Deletes the children of root node.
 * input  : hVal            - PVT handle to use.
 *          subTreeRootId   - The ID of the root node to delete.
 * output : None.
 * return : Non-negative value on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV pvtDeleteChilds(
    IN  HPVT        hVal,
    IN  RvPvtNodeId subTreeRootId);

/************************************************************************
 * pvtDeleteAll
 * purpose: Deletes all nodes in a Value Tree.
 * input  : hVal            - PVT handle to use.
 * output : None.
 * return : Non-negative value on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV pvtDeleteAll(
    IN HPVT hVal);

/************************************************************************
 * pvtSetTree
 * purpose: Copies a sub-tree from one Value Tree to another,
 *          overwriting the destination's tree.
 * input  : destH       - The handle returned by cmGetValTree() for the
 *                        parent (destination).
 *          destNodeId  - The node ID of the destination sub-tree.
 *                        The copied sub-tree overwrites this one.
 *          srcH        - The handle returned by cmGetValTree() for the
 *                        source (copied sub-tree).
 *          srcNodeId   - The ID of the root node of the source sub-tree.
 * output : None.
 * return : Non-negative value on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV pvtSetTree(
    IN  HPVT        destH,
    IN  RvPvtNodeId destNodeId,
    IN  HPVT        srcH,
    IN  RvPvtNodeId srcNodeId);

/************************************************************************
 * pvtMoveTree
 * purpose: Moves a sub-tree to another location within the same Value Tree.
 * input  : destH       - The handle returned by cmGetValTree() for the
 *                        parent (destination).
 *          destRootId  - The ID of the root node to which the sub-tree is
 *                        moved (destination root). This node is overwritten.
 *          srcRootId   - The ID of the root node to which the sub-tree
 *                        belongs (source node).
 * output : None.
 * return : Non-negative value on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV pvtMoveTree(
    IN  HPVT        destH,
    IN  RvPvtNodeId destRootId,
    IN  RvPvtNodeId srcRootId);

/************************************************************************
 * pvtShiftTree
 * purpose: Moves a sub-tree to another location within the same Value Tree,
 *          without changing the value of the source handle.
 * input  : destH       - The handle returned by cmGetValTree() for the
 *                        parent (destination).
 *          destRootId  - The ID of the root node to which the sub-tree
 *                        is moved (destination root).
 *          srcRootId   - The ID of the root node to which the sub-tree
 *                        belongs (source node).
 * output : None.
 * return : Non-negative value on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV pvtShiftTree(
    IN  HPVT        destH,
    IN  RvPvtNodeId destRootId,
    IN  RvPvtNodeId srcRootId);

/************************************************************************
 * pvtAdoptChild
 * purpose: Moves the child of a specific tree to below a specific node in
 *          a different tree. This process is referred to as adopting a child.
 * input  : hVal            - PVT handle to use.
 *          adoptedChildId  - The child you want to move.
 *          newParentId     - The node under which you want to move the child.
 *                            This node becomes the root. If this is set to -1,
 *                            then the node becomes a root.
 *          newBrotherId    - The node below the new root that you want the new
 *                            child to follow. If -1, then the node is the firstborn.
 * output : None.
 * return : Non-negative value on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV pvtAdoptChild(
    IN  HPVT        hVal,
    IN  RvPvtNodeId adoptedChildId,
    IN  RvPvtNodeId newParentId,
    IN  RvPvtNodeId newBrotherId);

/************************************************************************
 * pvtGet
 * purpose: Returns the value stored in a node (integer or a string) or an
 *          indication as to the type of the value.
 * input  : hVal        - PVT handle to use.
 *          nodeId      - The ID of the node to check.
 * output : fieldId     - The returned field ID of the node. You can then
 *                        use the pstGetFieldName() function to obtain the field name.
 *          synNodeId   - The ID of the node in the Syntax Tree.
 *          value       - Value of the root node, or length of the value if the
 *                        value is a string.
 *          isString    - RV_TRUE if the node contains a string. See pvtGetString().
 * return : The node ID value on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI RvPvtNodeId RVCALLCONV pvtGet(
    IN  HPVT            hVal,
    IN  RvPvtNodeId     nodeId,
    OUT RvPstFieldId*   fieldId,
    OUT RvPstNodeId*    synNodeId,
    OUT RvInt32*        value,
    OUT RvBool*         isString);

/************************************************************************
 * pvtGetString
 * purpose: Returns the value stored in the node, if the value is of the string type.
 * input  : hVal            - PVT handle to use.
 *          nodeId          - The ID of the node to check.
 *          stringLength    - The size of the buffer that will hold the returned value.
 * output : string          - The returned string value. This is a buffer allocated
 *                            by the user to hold the string.
 * return : Actual string's length on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI RvInt32 RVCALLCONV pvtGetString(
    IN  HPVT        hVal,
    IN  RvPvtNodeId nodeId,
    IN  RvInt32     stringLength,
    OUT char*       string);

/************************************************************************
 * pvtGetBitString
 * purpose: Returns the value stored in the node, if the value is of a bit string type.
 * input  : hVal            - PVT handle to use.
 *          nodeId          - The ID of the node to check.
 *          stringLength    - The size of the buffer that will hold the returned value.
 *                            The length is given in bytes.
 * output : string          - The returned string value. This is a buffer allocated
 *                            by the user to hold the string.
 * return : Actual string's length in bits on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI RvInt32 RVCALLCONV pvtGetBitString(
    IN  HPVT        hVal,
    IN  RvPvtNodeId nodeId,
    IN  RvInt32     stringLength,
    OUT char*       string);

/************************************************************************
 * pvtSet
 * purpose: Modifies values in a node.
 * input  : hVal    - PVT handle to use.
 *          nodeId  - The ID of the node to be modified.
 *          fieldId - The new field ID of the node.
 *                    A negative value means no change in fieldId.
 *          value   - Value of the root node, or length of the value if the
 *                    value is a string.
 *          string  - String value of the node, or NULL if no string.
 *                    The string is allocated and stored in the PVT.
 * output : None.
 * return : Non-negative value on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI RvInt32 RVCALLCONV pvtSet(
    IN  HPVT            hVal,
    IN  RvPvtNodeId     nodeId,
    IN  RvPstFieldId    fieldId,
    IN  RvInt32         value,
    IN  const char*     string);

/************************************************************************
 * pvtGetChild
 * purpose: Returns the ID of a child node based on its field ID.
 * input  : hVal        - PVT handle to use.
 *          parentId    - The node ID of the immediate parent.
 *          fieldId     - The field ID of the node that the function is
 *                        expected to locate.
 * output : childNodeId - The ID of the node that is found, or a negative value on failure.
 *                        If set to NULL, it will be discarded.
 * return : The node ID of the child on success, or a negative value on failure.
 ************************************************************************/
RVAPI RvPvtNodeId RVCALLCONV pvtGetChild(
    IN  HPVT            hVal,
    IN  RvPvtNodeId     parentId,
    IN  RvPstFieldId    fieldId,
    OUT RvPvtNodeId*    childNodeId);

/************************************************************************
 * pvtGetChildByFieldId
 * purpose: Returns the value of the child based on the field ID of the child.
 * input  : hVal        - PVT handle to use.
 *          parentId    - The node ID of the immediate parent.
 *          fieldId     - The field ID of the node that the function is
 *                        expected to locate.
 * output : value       - Value of the root node, or the length of the value if
 *                        the value is a string.
 *          isString    - RV_TRUE if the node contains a string. See pvtGetString().
 * return : The node ID of the child on success or a negative value on failure.
 ************************************************************************/
RVAPI RvPvtNodeId RVCALLCONV pvtGetChildByFieldId(
    IN  HPVT            hVal,
    IN  RvPvtNodeId     nodeId,
    IN  RvPstFieldId    fieldId,
    OUT RvInt32*        value,
    OUT RvBool*         isString);

/************************************************************************
 * pvtGetByIndex
 * purpose: Returns the ID of a child node based on the index of the child.
 * input  : hVal        - PVT handle to use.
 *          parentId    - The node ID of the immediate parent.
 *          index       - The index of the child, as determined by pvtAdd().
 *                        This index is 1-based.
 * output : childNodeId - The ID of the node that is found, or a negative value on failure.
 *                        If set to NULL, it will be discarded.
 * return : The child's node ID on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI RvPvtNodeId RVCALLCONV pvtGetByIndex(
    IN  HPVT            hVal,
    IN  RvPvtNodeId     parentId,
    IN  RvInt32         index,
    OUT RvPvtNodeId*    childNodeId);

/************************************************************************
 * pvtGetSyntaxIndex
 * purpose: Gets the index of the node in the parent syntax structure.
 * input  : hVal    - PVT handle to use.
 *          nodeId  - The PVT node ID.
 * output : None.
 * return : The index of the specified node in the parent syntax
 *          structure on success (this is 1-based).
 *          Negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV pvtGetSyntaxIndex(
    IN  HPVT        hVal,
    IN  RvPvtNodeId nodeId);

/************************************************************************
 * pvtSearchPath
 * purpose: Searches for a specified path, value or both in a specified tree.
 * input  : destH       - PVT handle of the search tree.
 *          rootNodeId  - Root ID of the search tree.
 *          srcH        - PVT handle of the path in which to search. 
 *          srcNodeId   - Node ID of the beginning of the path in which to search.
 *          checkLeaves - If RV_TRUE, compare the values in the lowest level nodes (leaves).
 *                        Use RV_FALSE if the tree syntax contains choices.
 * output : None.
 * return : RV_TRUE if found, RV_FALSE if not.
 *          Negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV pvtSearchPath(
    IN  HPVT        destH,
    IN  RvPvtNodeId rootNodeId,
    IN  HPVT        srcH,
    IN  RvPvtNodeId srcNodeId,
    IN  RvBool      checkLeaves);


/*---------------------- by path operations ------------------------ */

/************************************************************************
 * pvtGetNodeIdByPath
 * purpose: Returns the ID of a node based on a path that starts from a 
 *          specified root.
 * input  : hVal                - Value Tree handle.
 *          nodeId              - The ID of the node from which the search starts (root).
 *          path                - The path to the searched node. The format is: “a.b.c”
 * output : None.
 * return : Node ID that has been reached on success, or a negative value on failure.
 ************************************************************************/
RVAPI RvPvtNodeId RVCALLCONV pvtGetNodeIdByPath(
    IN  HPVT        hVal,
    IN  RvPvtNodeId nodeId,
    IN  const char* path);

/************************************************************************
 * pvtSetByPath
 * purpose: Modifies the value stored in a node. The function first locates
 *          the node based on a path. The function fails if  "path" does not exist.
 * input  : hVal    - Value Tree handle.
 *          nodeId  - The ID of the node from which the search starts.
 *          path    - The path to the searched node. The format is: “a.b.c”
 *          value   - Value of the root node, or length of the value if the
 *                    value is a string.
 *          string  - String value of the node, or NULL if it is not a string.
 *                    The string is allocated and stored in the PVT.
 * output : None.
 * return : Non-negative value on success.
 *          Negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV pvtSetByPath(
    IN  HPVT        hVal,
    IN  RvPvtNodeId nodeId,
    IN  const char  *path,
    IN  RvInt32     value,
    IN  const char* string);

/************************************************************************
 * pvtBuildByPath
 * purpose: Modifies the value stored in a node. If the path to the node 
 *          does not exist, the function first builds the path.
 * input  : hVal    - Value Tree handle.
 *          rootId  - The ID of the node from which the search starts.
 *          path    - The path to the searched node. The format is: “a.b.c”
 *          value   - The value of the root node, or length of the value if 
 *                    the value is a string.
 *          data    - The string value of the node, or NULL if it is not a string. 
 *                    The string is allocated and stored in the PVT.
 * output : None.
 * return : The last-built node ID on success, or a negative value on failure.
 ************************************************************************/
RVAPI RvPvtNodeId RVCALLCONV pvtBuildByPath(
    IN  HPVT        hVal,
    IN  RvPvtNodeId rootNodeId,
    IN  const char  *path,
    IN  RvInt32     value,
    IN  const char  *data);

#if (RV_ASN1_CODER_USE_Q931 == RV_YES)
/************************************************************************
 * pvtGetChildTagByPath
 * purpose: Gets the tag value of the node specified in the path format.
 * input  : hVal    - Value Tree handle.
 *          nodeId  - The ID of the node.
 *          path    - The path of the child node from the node specified 
 *                    in the node ID parameter.
 *          relation- The number of levels down the tree from the node 
 *                    specified in the node ID parameter
 * output : None.
 * return : The tag value of the specified node on success, or a 
 *          negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV pvtGetChildTagByPath(
    IN  HPVT        hVal,
    IN  RvPvtNodeId nodeId,
    IN  const char  *path,
    IN  int         relation);
#endif /* (RV_ASN1_CODER_USE_Q931 == RV_YES) */

/************************************************************************
 * pvtGetByPath
 * purpose: Returns the value in a node of the Value Tree.
 *          As input to the function, you need to provide the starting point
 *          node ID and the path to the node.
 * input  : hVal    - Value Tree handle.
 *          nodeId  - The ID of the node.
 *          path    - The path of the child node of the node specified in
 *                    the nodeId parameter.
 * output : fieldId     - The returned field ID of the node. You can then
 *                        use the pstGetFieldName() function to obtain the field name.
 *          value       - Value of the root node, or length of the value if the
 *                        value is a string.
 *          isString    - RV_TRUE if the node contains a string. See pvtGetString().
 * return : The ID of the node referred to by the path on success, or a 
 *          negative value on failure.
 ************************************************************************/
RVAPI RvPvtNodeId RVCALLCONV pvtGetByPath(
    IN  HPVT            hVal,
    IN  RvPvtNodeId     nodeId,
    IN  const char      *path,
    OUT RvPstFieldId    *fieldId,
    OUT RvInt32         *value,
    OUT RvBool          *isString);

/**************************************************************************************
 * pvtGetNodeIdByFieldIds
 *
 * Purpose: Finds the node ID by traversing both the Value Tree and the Syntax Tree 
 *          according to a path of field IDs.
 *              - Field IDs in the path should be existing field IDs.
 *              - Child indexes should be negative values starting from -101.
 *              - For '*' -1 is used.
 *              - To add an element to SEQUENCE OF, -100 may be used or 
 *                the last element index + 1.
 *              - The list should end with the LAST_TOKEN value.
 *
 * Input:   hVal       - vtStruct of the Value Tree.
 *          nodeId     - The beginning of the Value Sub-tree.
 *          path       - An array of fieldIds, ending with LAST_TOKEN.
 *
 *
 * Return value: The found node ID, or a negative value on failure.
 **************************************************************************************/
RVAPI RvPvtNodeId RVCALLCONV pvtGetNodeIdByFieldIds(
    IN  HPVT            hVal,
    IN  RvPvtNodeId     nodeId,
    IN  const RvInt16   *path);

/**************************************************************************************
 * pvtGetByFieldIds
 *
 * Purpose: Gets the data of a node pointed to by a given path of field IDs.
 *
 * Input:   hVal        - vtStruct of the Value Tree.
 *          nodeId      - The root of the Value Sub-tree.
 *          path        - An array of fieldIds, ending with LAST_TOKEN.
 *
 * Output:  fieldId     - The field ID of the element.
 *          value       - The value of the element, or string length if any exists.
 *          isSstring   - Specifies whether the value is a string.
 *
 * Return value: The node ID on success, or a negative value on failure.
 **************************************************************************************/
RVAPI RvPvtNodeId RVCALLCONV pvtGetByFieldIds(
    IN  HPVT            hVal,
    IN  RvPvtNodeId     nodeId,
    IN  RvInt16         *path,
    OUT RvPstFieldId    *fieldId,
    OUT RvInt32         *value,
    OUT RvBool          *isString);

/************************************************************************
 * pvtBuildByFieldIds
 * purpose: Modifies the value stored in a node.If the path to the node 
 *          does not exist, this function first builds the path.
 *          This function works faster than pvtBuildByPath.
 * input  : hVal        - Value Tree handle.
 *          rootNodeId  - The ID of the node from which the search starts.
 *          path        - The path to the searched node. Format: {a,b,c,LAST_TOKEN}.
 *          value       - Value of the root node, or length of the value if
 *                        the value is a string.
 *          string      - String value of the node, or NULL if it is not a string.
 *                        The string is allocated and stored in the PVT.
 * output : None.
 * return : The last-built node ID on success, or a negative value on failure.
 ************************************************************************/
RVAPI RvPvtNodeId RVCALLCONV pvtBuildByFieldIds(
    IN  HPVT            hVal,
    IN  RvPvtNodeId     rootNodeId,
    IN  RvInt16         *path,
    IN  RvInt32         value,
    IN  const RvChar    *data);

/************************************************************************
 * pvtPrint
 * purpose: Prints the tree from a given node, using a specified printing function.
 * input  : hVal        - Value Tree handle.
 *          parentId    - The node ID from which to start printing.
 *          pFunc       - The function that is called for the actual printing.
 *          pFuncParam  - The context to pass to the print function on each printed line.
 * output : None.
 * return : A non-negative value on success, or a negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV pvtPrint(
    IN  HPVT            hVal,
    IN  RvPvtNodeId     parentId,
    IN  pvtPrintFuncP   pFunc,
    IN  void            *pFuncParam);


/************************************************************************
 * pvtPrintStd
 * purpose: Print a tree from a given node
 *
 * Note   : This function calls a different API function: pvtPrintInternal().
 *
 * input  : hVal        - Value Tree handle.
 *          parentId    - Node ID from which to start printing. 
 *          logHandle   - Log source to which to print. 
 * output : None.
 * return : A non-negative value on success, or a negative value on failure.
 ************************************************************************/
RVAPI int RVCALLCONV pvtPrintStd(
    IN  HPVT        hVal,
    IN  RvPvtNodeId parentId,
    IN  int         logHandle);



/* The macros below could help make our lives simpler... */
#define pvtGetChild2(hVal,nodeId,fieldId1,fieldId2) \
    pvtGetChild((hVal),(pvtGetChild((hVal),(nodeId),(fieldId1),NULL)),(fieldId2),NULL)

#define pvtGetChildValue2(hVal,nodeId,fieldId1,fieldId2,value,svalue) \
    pvtGet((hVal),pvtGetChild2((hVal),(nodeId),(fieldId1),(fieldId2)),NULL,NULL,(value),(svalue))

#define pvtAddBranch(hVal,nodeId,fieldId) \
    pvtAdd((hVal),(nodeId),(fieldId),0,NULL,NULL)
#define pvtAddBranch2(hVal,nodeId,fieldId1,fieldId2) \
    pvtAddBranch((hVal),(pvtAddBranch((hVal),(nodeId),(fieldId1))),(fieldId2))


/************************************************************************
 * This section exists for debugging purposes only.
 * The function declarations below are not part of the API and might not
 * be supported in future versions.
 * These functions should not be called directly.
 ************************************************************************/
#if (RV_LOGMASK & RV_PVT_LOGDEBUG)
#define pvtAddRoot(hVal,hSyn,value,string)                  pvtAddRootFromInt(hVal,hSyn,RV_PST_INVALID_NODEID,value,(char *)string,__FILE__,__LINE__)
#define pvtAddRootByPath(hVal,hSyn,syntaxPath,value,string) pvtAddRootFromInt(hVal,hSyn,pstGetNodeIdByPath(hSyn,(const char*)syntaxPath),value,string,__FILE__,__LINE__)
#define pvtDelete(hVal,subTreeRootId)                       pvtDeleteDbg(hVal,subTreeRootId,__FILE__,__LINE__)
RVAPI int RVCALLCONV pvtDeleteDbg(IN HPVT hVal, IN RvPstNodeId subTreeRootId, IN const char* fileName, IN int lineno);
RVAPI void RVCALLCONV pvtPrintRootNodes(IN HPVT hVal, IN RvBool printOnlyRoot, IN void * msa);
#endif
RVAPI RvPvtNodeId RVCALLCONV pvtAddRootFromInt(IN HPVT hVal, IN HPST hSyn, IN RvPstNodeId nodePath, IN RvInt32 value, IN const char* string, IN const char* fileName, IN int lineno);


#ifdef __cplusplus
}
#endif

#endif  /* _PVALTREE_H */


