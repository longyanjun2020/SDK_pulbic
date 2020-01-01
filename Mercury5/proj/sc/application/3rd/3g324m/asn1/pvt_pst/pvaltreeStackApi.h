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
  pvaltreeStackApi

  This file contains functions which are available for the use of the stack modules,
  but are not part of the API provided to the users

  */

#ifndef _PVALTREE_STACKAPI_H
#define _PVALTREE_STACKAPI_H

#include "pvaltree.h"
#include "pvaltreeDef.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 *                      Print functions
 ************************************************************************/

 /************************************************************************
 * vtPrintToLog
 * purpose: Callback function called when a node has been parsed into
 *          a string and should be sent to the log.
 * input  : type    - Type of log handle to use
 *          line    - Line information
 *                    The additional parameters are discarded
 * output : none
 * return : none
 ************************************************************************/
#if (RV_LOGMASK & RV_LOGLEVEL_DEBUG)
void vtPrintToLog(void * type, const char* line, ...);
#endif


/************************************************************************
 * vtPrintFunc
 * purpose: Print a tree from a given node.
 *          This function is the function used by all of the public
 *          print functions.
 * input  : hVal        - Value Tree handle
 *          parentId    - node ID to start printing from
 *          pFunc       - The function called for the printing itself
 *          pFuncParam  - The context to pass to the print function
 *                        on each printed line
 *          degree      - Detail degree to use when printing the message
 *                        tree
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int vtPrintFunc(
    IN  vtStruct        *vt,
    IN  RvPvtNodeId     parentId,
    IN  pvtPrintFuncP   pFunc,
    IN  void *          pFuncParam,
    IN  pvtPrintDegree  degree);

/************************************************************************
 * vtNodePrint
 * purpose: Callback function used to print a single node using vt's
 *          print parameters
 * input  : rtH     - RTree handle used
 *          nodeId  - Node to print
 *          layer   - Level of node in tree
 *          param   - vtStruct of the node
 * output : none
 * return : vtStruct of the node (i.e. - param)
 ************************************************************************/
void *vtNodePrint(
    HRTREE rtH, 
    int nodeId, 
    int layer, 
    void *param);

#if (RV_LOGMASK & RV_LOGLEVEL_DEBUG)
/************************************************************************
 * vtRootPrint
 * purpose: Callback function used to print a single root for debugging
 *          purposes only
 * input  : rtH     - RTree handle used
 *          element - Node to print
 *          param   - vtStruct of the node
 * output : none
 * return : vtStruct of the node (i.e. - param)
 ************************************************************************/
void* vtRootPrint(IN HRTREE rtH, IN RTElement element, IN void* param);
#endif


/************************************************************************
 * pvtPrintInternal
 *
 * ** declared here to remove dependency of pvaltree.h from rvlog.h **
 *
 * purpose: Print a tree from a given node.
 *          This function should be used internally instead of using
 *          pvtPrintStd().
 * input  : hVal        - Value Tree handle
 *          parentId    - node ID to start printing from
 *          logHandle   - Log source to print to
 *          level       - Debug level to use for printing
 *                        0,1 - None
 *                        2 - Print the tree
 *                        3 - Print all values in the tree (even the irrelevant onse)
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
RVAPI int RVCALLCONV pvtPrintInternal(
    IN  HPVT            hVal,
    IN  RvPvtNodeId     parentId,
    IN  RvLogSource     *logHandle,
    IN  int             level);


/************************************************************************
 * vtGetRoot
 * purpose: Returns the Node ID of the root of a Value Tree to which a
 *          specified node belongs
 * input  : vt      - Pointer to VT struct
 *          nodeId  - The ID of the node inside a tree
 * output : none
 * return : Root node ID of the given node ID on success
 *          Negative value on failure
 ************************************************************************/
RvPvtNodeId vtGetRoot(
    IN  vtStruct    *vt,
    IN  RvPvtNodeId  nodeId);

/************************************************************************
 * vtGetSynTree
 * purpose: Returns a handle to the structure (Syntax Tree) definition of
 *          a specified node
 * input  : vt      - Pointer to VT struct
 *          nodeId  - The ID of the node the syntax of which is returned
 * output : none
 * return : A handle to the structure (Syntax Tree) definition on success
 *          NULL on failure
 ************************************************************************/
HPST vtGetSynTree(
    IN  vtStruct    *vt,
    IN  RvPvtNodeId nodeId);

/************************************************************************
 * vtTreeSize
 * purpose: Returns the number of nodes included in a Value Tree root
 * input  : hVal        - Pointer to VT struct
 *          parentId    - The ID of any node. The function returns the
 *                        number of nodes located under the specified parent.
 * output : none
 * return : The number of nodes included in a Value Tree on success
 *          Negative value on failure
 ************************************************************************/
int vtTreeSize(
    IN  vtStruct    *vt,
    IN  RvPvtNodeId parentId);

/************************************************************************
 * vtNumChilds
 * purpose: Returns the number of the dependents (children) of a parent tree
 * input  : vt          - Pointer to VT struct
 *          parentId    - The ID of any node
 * output : none
 * return : The number of immediate nodes under the given node on success
 *          Negative value on failure
 ************************************************************************/
int vtNumChilds(
    IN  vtStruct    *vt,
    IN  RvPvtNodeId parentId);

/************************************************************************
 * vtParent
 * purpose: Returns the ID of the parent node of a specified node
 * input  : vt          - Pointer to VT struct
 *          nodeId      - The ID of any node
 * output : none
 * return : The parent ID of the given node on success
 *          Negative value on failure
 ************************************************************************/
RvPvtNodeId vtParent(
    IN  vtStruct    *vt,
    IN  RvPvtNodeId   nodeId);

/************************************************************************
 * vtBrother
 * purpose: Returns the Node ID of a specified node's brother (right).
 * input  : vt          - Pointer to VT struct
 *          nodeId      - The ID of any node
 * output : none
 * return : The node ID of the given node's brother on success
 *          Negative value on failure
 * The function returns the next child (rightward). Use pvtChild() to get
 * the first dependent, and then use pvtBrother() to get to the next brother.
 ************************************************************************/
RvPvtNodeId vtBrother(
    IN  vtStruct    *vt,
    IN  RvPvtNodeId  nodeId);

/************************************************************************
 * vtChild
 * purpose: Returns the Node ID of the first (leftmost) child of a parent.
 * input  : vt          - Pointer to VT struct
 *          parentId    - The ID of any node
 * output : none
 * return : The Node ID of the first (leftmost) child of a parent on success
 *          Negative value on failure
 ************************************************************************/
RvPvtNodeId vtChild(
    IN  vtStruct    *vt,
    IN  RvPvtNodeId  parentId);

/************************************************************************
 * vtNext
 * purpose: Returns the ID of a node located after a specified node.
 * input  : vt      - Pointer to VT struct
 *          rootId  - The ID of the root node of the current Value Tree
 *          location- A Node ID inside the given root
 * output : none
 * return : The Node ID of the next node in the tree on success - this
 *          value should be given as the location on the next call.
 *          Negative value on failure
 ************************************************************************/
RvPvtNodeId vtNext(
    IN  vtStruct    *vt,
    IN  RvPvtNodeId rootId,
    IN  RvPvtNodeId location);

/************************************************************************
 * vtDelete
 * purpose: Deletes a sub-tree
 * input  : vt              - Pointer to VT struct
 *          subTreeRootId   - The ID of the root node to delete
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int vtDelete(
    IN  vtStruct    *vt,
    IN  RvPvtNodeId subTreeRootId);

/************************************************************************
 * vtDeleteFunc
 * purpose: Used as callback delete function
 * input  : rtH             - Handle of rtree object that contains element
 *          element         - Pointer to node that contains rpool element
 *          ppvt            - Points to VT struct
 * output : none
 * return : ppvt on success
 *          NULL upon failure
 ************************************************************************/
void *vtDeleteFunc(HRTREE rtH, RTElement element, void *ppvt);

/************************************************************************
 * vtDeleteChilds
 * purpose: Deletes the children of root node.
 * input  : vt              - Pointer to VT struct
 *          subTreeRootId   - The ID of the root node to delete
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int vtDeleteChilds(
    IN  vtStruct    *vt,
    IN  RvPvtNodeId subTreeRootId);

/************************************************************************
 * vtGet
 * purpose: Returns the value stored in a node (integer or a string) or an
 *          indication as to the type of the value
 * input  : vt          - Pointer to VT struct
 *          nodeId      - The ID of the node to check
 * output : fieldId     - The returned field ID of the node. You can then
 *                        use the pstGetFieldName() function to obtain the field name
 *          synNodeId   - The ID of the node in the Syntax Tree
 *          value       - Value of the root node, or length of the value if
 *                        value is a string
 *          isString    - RV_TRUE if node contains a string - see pvtGetString()
 * return : The node Id value on success
 *          Negative value on failure
 ************************************************************************/
RvPvtNodeId vtGet(
    IN  vtStruct        *vt,
    IN  RvPvtNodeId     nodeId,
    OUT RvPstFieldId*   fieldId,
    OUT RvPstNodeId*    synNodeId,
    OUT RvInt32*        value,
    OUT RvBool*         isString);

/************************************************************************
 * vtGetString
 * purpose: Returns the value stored in the node, if the value is of string type.
 * input  : vt              - Pointer to VT struct
 *          nodeId          - The ID of the node to check
 *          stringLength    - The size of the buffer that will hold the returned value
 * output : string          - The return string value. This is a buffer allocated
 *                            by the user to hold the string
 * return : Actual string's length on success
 *          Negative value on failure
 ************************************************************************/
RvInt32 vtGetString(
    IN  vtStruct    *vt,
    IN  RvPvtNodeId nodeId,
    IN  RvInt32     stringLength,
    OUT char*       string);

/************************************************************************
 * vtSet
 * purpose: Modifies values in a node
 * input  : vt      - Pointer to VT struct
 *          nodeId  - The ID of the node to modify
 *          fieldId - The new field ID of the node.
 *                    A negative value means no change in fieldId.
 *          value   - Value of the root node, or length of the value if
 *                    value is a string
 *          string  - String value of the node, or NULL if not a string
 *                    The string is allocated and stored in the PVT.
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
RvInt32 vtSet(
    IN  vtStruct        *vt,
    IN  RvPvtNodeId     nodeId,
    IN  RvPstFieldId    fieldId,
    IN  RvInt32         value,
    IN  const char*     string);

/************************************************************************
 * vtGetChild
 * purpose: Returns the ID of a child node based on its field ID
 * input  : vt          - Pointer to VT struct
 *          parentId    - The Node ID of the immediate parent
 *          fieldId     - The field ID of the node that the function is
 *                        expected to locate
 * output : childNodeId - The ID of the node that is found, or negative value on failure
 *                        If set to NULL, it will be discarded
 * return : Child's node id on success
 *          Negative value on failure
 ************************************************************************/
RvPvtNodeId vtGetChild(
    IN  vtStruct        *vt,
    IN  RvPvtNodeId     parentId,
    IN  RvPstFieldId    fieldId,
    OUT RvPvtNodeId*    childNodeId);

/************************************************************************
 * vtGetChildByFieldId
 * purpose: Returns the child's value based on its field ID
 * input  : vt          - Pointer to VT struct
 *          parentId    - The Node ID of the immediate parent
 *          fieldId     - The field ID of the node that the function is
 *                        expected to locate
 * output : value       - Value of the root node, or length of the value if
 *                        value is a string
 *          isString    - RV_TRUE if node contains a string - see pvtGetString()
 * return : Child's node id on success
 *          Negative value on failure
 ************************************************************************/
RvPvtNodeId vtGetChildByFieldId(
    IN  vtStruct        *vt,
    IN  RvPvtNodeId     nodeId,
    IN  RvPstFieldId    fieldId,
    OUT RvInt32*        value,
    OUT RvBool*         isString);

/************************************************************************
 * vtGetByIndex
 * purpose: Returns the ID of a child node based on the child's index
 * input  : vt          - Pointer to VT struct
 *          parentId    - The Node ID of the immediate parent
 *          index       - The index of the child, as determined by pvtAdd().
 *                        This index is 1-based.
 * output : childNodeId - The ID of the node that is found, or negative value on failure
 *                        If set to NULL, it will be discarded
 * return : Child's node id on success
 *          Negative value on failure
 ************************************************************************/
RvPvtNodeId vtGetByIndex(
    IN  vtStruct        *vt,
    IN  RvPvtNodeId     parentId,
    IN  RvInt32         index,
    OUT RvPvtNodeId*    childNodeId);

/************************************************************************
 * vtGetNodeIdByPath
 * purpose: Returns the ID of a node based on a path that starts from a
 *          specified root
 * input  : vt                  - Pointer to VT struct
 *          searchRootNodeId    - The ID of the node from which the search starts from
 *          path                - The path to the searched node. format: "a.b.c"
 * output : none
 * return : Node ID we reached on success
 *          Negative value on failure
 ************************************************************************/
RvPvtNodeId vtGetNodeIdByPath(
    IN  vtStruct    *vt,
    IN  RvPvtNodeId nodeId,
    IN  const char* path);

/**************************************************************************************
 * vtGetNodeIdByFieldIds
 *
 * Purpose: find node id by traversing both value and syntax trees according to a path
 *          of filed Ids.
 *              - Field Ids in the path should be existing Field Ids.
 *              - Child indexes should be negative values starting from -101.
 *              - for '*' -1 is used
 *              - to add element to SEQUENCE OF -100 may be used or the last element index + 1
 *              - The list should end with LAST_TOKEN value
 *
 * Input:   vt          - Pointer to VT struct
 *          nodeId      - The start of the val sub tree.
 *          path        - An array of fieldIds, ending with LAST_TOKEN
 *
 *
 * Return value: The found node id or negative value on failure
 **************************************************************************************/
RvPvtNodeId vtGetNodeIdByFieldIds(
    IN  vtStruct        *vt,
    IN  RvPvtNodeId     nodeId,
    IN  const RvInt16   *path);

/************************************************************************
 * vtSearchPath
 * purpose: Searches for a specified path, value or both in a specified tree
 *          This function is called by pvtSearchPath. It does less sanity
 *          checks and has no locking mechanisms in it
 * input  : vtDest      - VT struct of the search tree
 *          rootNodeId  - Root ID of the search tree
 *          vtSrc       - VT struct of path to be searched in
 *          srcNodeId   - Node ID of the beginning of the path to be searched in
 *          checkLeaves - If RV_TRUE, Compare the values in the lowest level nodes (leaves)
 *                        Use RV_FALSE if the tree syntax contains choices.
 * output : none
 * return : RV_TRUE if found, RV_FALSE if not
 *          Negative value on failure
 ************************************************************************/
int vtSearchPath(
    IN  vtStruct*   vtDest,
    IN  RvPvtNodeId rootNodeId,
    IN  vtStruct*   vtSrc,
    IN  RvPvtNodeId srcNodeId,
    IN  RvBool      checkLeaves);


/************************************************************************
 * Setting and adding nodes
 ************************************************************************/

/* syntax node id or negative value on failure */
RvPstNodeId vtResolveSynNodeId(
    IN  vtStruct        *vt,
    IN  HPST            hSyn,
    IN  RvPvtNodeId     valParentId,
    IN  RvPstFieldId    fieldEnum,
    OUT int             *index /* of child in parent */
    );

/************************************************************************
 * vtSetNode
 * purpose: Set a node's value
 * input  : vt          - VT struct to use
 *          hSyn        - Syntax tree to use
 *                        Can be set to -1 if it will be supplied later (by vtSetTree)
 *          nodePath    - Node Id to set
 *          nodeSynId   - Syntax node Id of the node or negative value on failure if unknown
 *          parentId    - Parent's node Id or negative value on failure if a root node
 *          fieldEnum   - Syntax tree field inside a type, or negative value on failure if a root node
 *          value       - Value of the root node, or length of the value if
 *                        value is a string
 *          string      - String value of the node, or NULL if not a string
 * output : index       - Index of the new node (1-based)
 * return : Node id of the added root on success
 *          Negative value on failure
 ************************************************************************/
RvPvtNodeId vtSetNode(
    IN  vtStruct        *vt,
    IN  HPST            hSyn,
    IN  RvPvtNodeId     nodePath,
    IN  RvPstNodeId     nodeSynId,
    IN  RvPvtNodeId     parentId,
    IN  RvPstFieldId    fieldEnum,
    IN  RvInt32         value,
    IN  const char*     string,
    OUT int*            index);


/*  new node id or negative value on failure
    Add child node under parentId.
    The new node is placed in its relative position according to syntax tree
    indexing of SEQUENCE fields of structure. */
RvPvtNodeId vtAddSyn(
    IN  vtStruct        *vt,
    IN  HPST            hSyn,       /* -1 ==> copy from parent node */
    IN  RvPvtNodeId     parentId,
    IN  RvPstFieldId    fieldEnum,  /* field inside SEQUENCE or CHOICE, or -1 if not applicable */
    IN  RvInt32         value,      /* if string exists ==> size of string , if Bit String - length in bit*/
    IN  const char      *string,    /* NULL if no string */
    OUT RvPvtNodeId     *newNodeId, /* id for the new node */
    OUT int             *index      /* index of new node */
    ); 

/* Sets values for existing node */
int vtSetSyn(
    IN  vtStruct        *vt,
    IN  HPST            hSyn, /* -1 ==> don't change */
    IN  RvPvtNodeId     nodeId,
    IN  RvPstFieldId    fieldEnum, /* <0 not changing current value */
    IN  RvInt32         value,      /* if bit string - length in bits */
    IN  const char      *string);



/************************************************************************
 * vtCompare
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
int vtCompare(
    IN HPST hSyn, 
    IN int sNodeId, 
    IN void* context);



/************************************************************************
 *
 *                          RVAPI functions
 *
 ************************************************************************/


/************************************************************************
 * pvtCompareTree
 * purpose: Compare between two trees
 *          The trees must be structure identical, the compare function only
 *          checks that the values are identical.
 * input  : val1H       - PVT handle of the 1st tree
 *          val1RootId  - Root ID of the 1st tree
 *          val2H       - PVT handle of the 2nd tree
 *          val2RootId  - Root ID of the 2nd tree
 * output : none
 * return : Non-negative value if trees are identical
 *          Negative value on failure
 ************************************************************************/
RVAPI int RVCALLCONV pvtCompareTree(
    IN  HPVT        val1H,
    IN  RvPvtNodeId val1RootId,
    IN  HPVT        val2H,
    IN  RvPvtNodeId val2RootId);


RVAPI int RVCALLCONV pvtFindObject(
    IN  HPVT           hVal,
    IN  RvPvtNodeId    nodeId,
    IN  HPST           hSyn,
    IN  int            stNodeIdOfAT,
    OUT int*           objectId);



#if defined(RV_DEBUG)

/************************************************************************
 * pvtAddRootShielded
 * purpose: Adds a new shielded node that constitutes the root of a new tree.
 * input  : valH    - PVT handle to use
 *          synH    - Syntax tree to use
 *                    Can be set to -1 if it will be supplied later (by pvtSetTree)
 *          value   - Value of the root node, or length of the value if
 *                    value is a string
 *          string  - String value of the node, or NULL if not a string
 * output : none
 * return : Node id of the added root on success
 *          Negative value on failure
 ************************************************************************/
RVAPI RvPvtNodeId RVCALLCONV pvtAddRootShielded(
    IN  HPVT        valH,
    IN  HPST        synH,
    IN  RvInt32     value,
    IN  const char* string);
#else
#define pvtAddRootShielded(_valH, _synH, _value, _string) pvtAddRoot(_valH, _synH, _value, _string)
#endif


#if defined(RV_DEBUG)
/************************************************************************
 * pvtDeleteShielded
 * purpose: Deletes a shielded sub-tree
 * input  : valH            - PVT handle to use
 *          subTreeRootId   - The ID of the root node to delete
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
RVAPI int RVCALLCONV pvtDeleteShielded(
    IN  HPVT          hVal,
    IN  RvPvtNodeId   subTreeRootId);
#else
#define pvtDeleteShielded(_hVal, _subTreeRootId) pvtDelete(_hVal, _subTreeRootId)
#endif /* defined(RV_DEBUG) */



#ifdef __cplusplus
}
#endif

#endif  /* _PVALTREE_STACKAPI_H */


