/***********************************************************************
        Copyright (c) 2003 RADVISION Ltd.
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
   rtree.h

   RADVISION tree implementation.

   */

#ifndef _RTREE_
#define _RTREE_


#include "ra.h"



#ifdef __cplusplus
extern "C" {
#endif



/* array handler */
RV_DECLARE_HANDLE(HRTREE);


/*********** element prototypes ************/
typedef void *RTElement;
typedef RvBool (*RTECompare)(RTElement element1, void *param);
typedef RvBool (*RTECompareTwo)(RTElement element1, RTElement element2, void *param);
typedef void* (*RTEFunc)(HRTREE rtH, RTElement element, void *param);
typedef void* (*RTEPFunc)(HRTREE rtH, int nodeId, int layer, void *param);

/*********** array functions **************/

/************************************************************************
 * rtConstruct
 * purpose: Create an RTREE object.
 * input  : elemSize            - Size of elements in the RTREE in bytes.
 *          maxNumOfElements    - Number of elements in RTREE.
 *          logMgr              - Log manager to use.
 *          name                - Name of RTREE (used in log messages).
 *          logMgr              - Log manager to use.
 * output : none
 * return : Handle to RTREE constructed on success.
 *          NULL on failure.
 ************************************************************************/
HRTREE rtConstruct(
    IN int              elemSize,
    IN int              maxNumOfElements,
    IN const RvChar*    name,
    IN RvLogMgr*        logMgr);


/************************************************************************
 * rtDestruct
 * purpose: Deallocates an RTREE object
 * input  : rtH - RTREE handle
 * output : none
 * return : none
 ************************************************************************/
void rtDestruct(IN HRTREE rtH);


/************************************************************************
 * rtClear
 * purpose: Clear an RTREE object for any allocated nodes
 * input  : rtH - RTREE handle
 * output : none
 * return : none
 ************************************************************************/
void rtClear(IN HRTREE rtH);


/************************************************************************
 * rtSetCompareFunc
 * purpose: Set the compare function to use
 * input  : rtH     - Handle of the RTREE object
 *          func    - Compare function to use
 * output : none
 * return : none
 ************************************************************************/
void rtSetCompareFunc(IN HRTREE rtH, IN RTECompare func);


/************************************************************************
 * rtSetPrintFunc
 * purpose: Set the print function to use
 * input  : rtH     - Handle of the RTREE object
 *          func    - Print function to use
 * output : none
 * return : none
 ************************************************************************/
void rtSetPrintFunc(IN HRTREE rtH, IN RTEPFunc func);


/************************************************************************
 * rtGetByPath
 * purpose: Return the element stored in a node ID
 * input  : rtH     - Handle of the RTREE object
 *          path    - Node ID to get from
 * output : none
 * return : element on success
 *          NULL on failure
 ************************************************************************/
RTElement rtGetByPath(IN HRTREE rtH, IN int path);


/************************************************************************
 * rtGetNode
 * purpose: Return the node ID of an element.
 * input  : rtH     - Handle of the RTREE object.
 *          element - Node ID to get from.
 * output : none
 * return : element's node ID on success, negative value on failure.
 ************************************************************************/
int rtGetNode(IN HRTREE rtH, IN RTElement element);


/************************************************************************
 * rtGetRoot
 * purpose: Get the root node of the tree for the given node
 * input  : rtH     - Handle of the RTREE object
 *          nodeId  - Node ID whose root we're looking for
 * output : none
 * return : Root node ID on success
 *          Negative value on failure
 * This function returns a negative value if the given nodeId is the root
 * itself
 ************************************************************************/
int rtGetRoot(
    IN  HRTREE  rtH,
    IN  int     nodeId);


/************************************************************************
 * rtGetByIndex
 * purpose: Find one of the children of a parent node by its index
 * input  : rtH     - Handle of the RTREE object
 *          parent  - Parent's node ID
 *          index   - Index of searched child (1-based)
 * output : none
 * return : Child's Node id on success
 *          Negative value on failure
 ************************************************************************/
int rtGetByIndex(
    IN HRTREE   rtH,
    IN int      parent,
    IN int      index);


/************************************************************************
 * rtParent
 * purpose: Get the parent node of the given node
 * input  : rtH     - Handle of the RTREE object
 *          node    - Node ID whose parent we're looking for
 * output : none
 * return : Parent node ID on success
 *          Negative value on failure
 ************************************************************************/
int rtParent(IN HRTREE rtH, IN int node);


/************************************************************************
 * rtBrother
 * purpose: Get the next node in the same level of the current node.
 *          This is referred to as the brother of the current node.
 * input  : rtH     - Handle of the RTREE object
 *          node    - Node ID whose brother we're looking for
 * output : none
 * return : Brother's node ID on success
 *          Negative value on failure
 ************************************************************************/
int rtBrother(IN HRTREE rtH, IN int node);


/************************************************************************
 * rtHead
 * purpose: Get the first child node of the current parent node
 *          If we want to get all of the child nodes, we can call
 *          rtBrother() from hear on until we get an error
 * input  : rtH     - Handle of the RTREE object
 *          parent  - Node ID whose first child we're looking for
 * output : none
 * return : First child's node ID on success
 *          Negative value on failure
 ************************************************************************/
int rtHead(IN HRTREE rtH, IN int parent);


/************************************************************************
 * rtTail
 * purpose: Get the last child node of the current parent node
 * input  : rtH     - Handle of the RTREE object
 *          parent  - Node ID whose last child we're looking for
 * output : none
 * return : Last child's node ID on success
 *          Negative value on failure
 ************************************************************************/
int rtTail(IN HRTREE rtH, IN int parent);


/************************************************************************
 * rtIndex
 * purpose: Get the index of the given child under the parent node
 * input  : rtH     - Handle of the RTREE object
 *          parent  - Node ID of the parent
 *          child   - Child's node ID
 * output : none
 * return : Index of the child inside the parent (1-based)
 *          Negative value on failure
 ************************************************************************/
int rtIndex(IN HRTREE rtH, IN int parent, IN int child);


/************************************************************************
 * rtNumChilds
 * purpose: Get the number of child nodes under a given node
 * input  : rtH     - Handle of the RTREE object
 *          parent  - Node ID of the parent
 * output : none
 * return : Number of child nodes under the parent
 *          Negative value on failure
 ************************************************************************/
int rtNumChilds(IN HRTREE rtH, IN int parent);


/************************************************************************
 * rtNext
 * purpose: Get the next node for a given node ID
 *          This function can be used to traverse the tree, each time
 *          returning another node ID inside the tree.
 *          This function uses POST-ORDER traversal of the tree
 * input  : rtH         - Handle of the RTREE object
 *          root        - Root node ID of the sub-tree we're traversing
 *          location    - Current node ID
 * output : none
 * return : Next node ID in the tree on success
 *          Negative value when done or on failure
 ************************************************************************/
int rtNext(
    IN  HRTREE  rtH,
    IN  int     root,
    IN  int     location);


/************************************************************************
 * rtAddRoot
 * purpose: Add a new root node as a tree to RTREE
 * input  : rtH     - Handle of the RTREE object
 *          elem    - Element to add as root
 *                    If given as NULL, an empty element is added
 * output : none
 * return : Node ID of the new root on success
 *          Negative value on failure
 ************************************************************************/
int rtAddRoot(
    IN  HRTREE      rtH,
    IN  RTElement   elem);


/************************************************************************
 * rtAddHead
 * purpose: Add a new node as the first child, before any other of a given
 *          parent node
 * input  : rtH     - Handle of the RTREE object
 *          parent  - Parent's node ID
 *          elem    - Element to add
 *                    If given as NULL, an empty element is added
 * output : none
 * return : Node ID of the added node on success
 *          Negative value on failure
 ************************************************************************/
int rtAddHead(
    IN  HRTREE      rtH,
    IN  int         parent,
    IN  RTElement   elem);


/************************************************************************
 * rtAddTail
 * purpose: Add a new node as the last child of a parent
 * input  : rtH     - Handle of the RTREE object
 *          parent  - Parent's node ID
 *          elem    - Element to add
 *                    If given as NULL, an empty element is added
 * output : none
 * return : Node ID of the added node on success
 *          Negative value on failure
 ************************************************************************/
int rtAddTail(
    IN  HRTREE      rtH,
    IN  int         parent,
    IN  RTElement   elem);


/************************************************************************
 * rtAddBrother
 * purpose: Add a new node as the closest (right) brother of a given node
 * input  : rtH     - Handle of the RTREE object
 *          brother - Brother node we're joining to the right
 *          elem    - Element to add
 *                    If given as NULL, an empty element is added
 * output : none
 * return : Node ID of the added node on success
 *          Negative value on failure
 ************************************************************************/
int rtAddBrother(
    IN  HRTREE      rtH,
    IN  int         brother,
    IN  RTElement   elem);


/************************************************************************
 * rtAdd
 * purpose: Iterative copy of a source subtree under a destination parent
 *          node as its last child.
 *          - The source and destination RTREE elements must have the same size
 *          - There should be enough room in the destination for the source
 *            subtree
 * input  : destH           - Handle to destination RTREE
 *          destParentId    - Destination parent node. We're going to add
 *                            a new child to it (a last child)
 *          srcH            - Handle to source RTREE
 *          srcRootId       - The node ID of the source tree we're adding
 *                            under the destination parent node.
 *          fadd            - User's add function - called for every
 *                            added node in the tree.
 *                            If this function returns NULL, it is considered
 *                            an error in the execution of rtAdd.
 *                            can be set to NULL
 *          param           - Context parameter to use on calls to fadd
 * output : none
 * return : Node ID of the added node on success
 *          Negative value on failure
 ************************************************************************/
int rtAdd(
    IN  HRTREE  destH,
    IN  int     destParentId,
    IN  HRTREE  srcH,
    IN  int     srcRootId,
    IN  RTEFunc fadd,
    IN  void*   param);


/************************************************************************
 * rtAdd
 * purpose: Iterative copy of all the children of a source node under a
 *          destination parent node as its last children.
 *          - The source and destination RTREE elements must have the same size
 *          - There should be enough room in the destination for the source
 *            subtree
 * input  : destH           - Handle to destination RTREE
 *          destParentId    - Destination parent node. We're going to add
 *                            a new child to it (a last child)
 *          srcH            - Handle to source RTREE
 *          srcRootId       - The node ID of the source tree whose children
 *                            we're adding under the destination parent node.
 *          fadd            - User's add function - called for every
 *                            added node in the tree.
 *                            If this function returns NULL, it is considered
 *                            an error in the execution of rtAddChilds.
 *                            can be set to NULL
 *          param           - Context parameter to use on calls to fadd
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int rtAddChilds(
    IN  HRTREE  destH,
    IN  int     destParentId,
    IN  HRTREE  srcH,
    IN  int     srcRootId,
    IN  RTEFunc fadd,
    IN  void*   param);


/************************************************************************
 * rtSet
 * purpose: Copy a source sub-tree onto destParentId, deleting any previous
 *          content and nodes under destParentId
 *          - The source and destination RTREE elements must have the same size
 *          - There should be enough room in the destination for the source
 *            subtree
 * input  : destH           - Handle to destination RTREE
 *          destParentId    - Destination parent node. We're going to delete
 *                            it and copy srcRootId onto it
 *          srcH            - Handle to source RTREE
 *          srcRootId       - The node ID of the source tree we'll copy
 *          fadd            - User's add function - called for every
 *                            added node in the tree.
 *                            If this function returns NULL, it is considered
 *                            an error in the execution of rtAddChilds.
 *                            can be set to NULL
 *          fdelete         - User's delete function - caled for every
 *                            deleted node under destParentId, including destParentId
 *          param           - Context parameter to use on calls to fadd and fdelete
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
int rtSet(
    IN  HRTREE  destH,
    IN  int     destParentId,
    IN  HRTREE  srcH,
    IN  int     srcRootId,
    IN  RTEFunc fadd,
    IN  RTEFunc fdelete,
    IN  void*   param);


int /* RV_TRUE or negative value on failure */
rtMove(
       /* move sub-tree to another sub-tree, NO restriction */
       IN  HRTREE rtH,
       IN  int destNodeId,
       IN  int srcRootId,
       IN  RvBool keepSrcRoot, /* true==> srcRoot node not deleted */
       IN  RTEFunc fdelete,  /* user delete node function */
       IN  void *param       /* for add and delete user functions */
       );

int /* RV_TRUE or negative value on failure */
rtAdoptChild(
         /* Child is adopted by its new family. new brother is a child of new parent. */
         IN  HRTREE rtH,
         IN  int adoptedChildId, /* child to be adopted by the new family */
         IN  int newParentId, /* parent of adopted child. -1: become root */
         IN  int newBrotherId /* previously born child (left brother). -1: first born */
         );

int /* RV_TRUE or negative value on failure */
rtDelete(
     /* delete subtree from rootId. Iterative pre-order deleting */
     IN  HRTREE rtH,
     IN  int rootId, /* subtree root id */
     IN  RTEFunc fdelete, /* delete function */
     IN  void *param
     );

int /* RV_TRUE or negative value on failure */
rtDeleteChilds(
           /* delete all child-sub-trees of rootId. Iterative preorder deleting */
           IN  HRTREE rtH,
           IN  int rootId, /* subtree root id */
           IN  RTEFunc fdelete, /* delete function */
           IN  void *param
           );



int /* number of nodes in sub-tree */
rtTreeSize(
       /* calc. num of nodes in subtree */
       IN  HRTREE rtH,
       IN  int rootId
       );


int       rtGetChild  (HRTREE rtH, int parent, void *param, int index);

int       rtFind      (HRTREE rtH, int subTreeRoot, void *param, int index);
int       rtCompare   (HRTREE rtH, int subTreeRoot, void *param, int index, RTECompare compare);

int /* RV_TRUE or negative value on failure */
rtCompareTrees(
           /* Compare between two trees.
          The trees must be structure identical.
          The compare function check node content.
          */
           IN  HRTREE destH,
           IN  int destRootId,
           IN  HRTREE srcH,
           IN  int srcRootId,
           IN  RTECompareTwo fcompare, /* compare two nodes */
           IN  void *param /* for compare function */
           );

/* tree traveling */
int       rtFirst     (HRTREE rtH, int subTreeRoot);
int       rtCurrent   (HRTREE rtH);


/************************************************************************
 * rtDoAll
 * purpose: Execute a given function on all of the roots inside RTREE.
 *          Note that this function will only be called on the roots and
 *          not on all the allocated nodes.
 * input  : rtH         - Handle to RTREE
 *          operation   - Function to call on all roots
 *          param       - Context parameter to use on calls
 * output : none
 * return : none
 ************************************************************************/
void rtDoAll(
    IN HRTREE   rtH,
    IN RTEFunc  operation,
    IN void*    param);


int
rtPrint(
          /* Recursive print of tree. */
          IN  HRTREE rtH,
          IN  int parent,
          IN  unsigned int layer, /* start printing layer */
          IN  int maxLevel, /* -1=infinite, 0==>parent node */
          IN  void * param,
          IN  void * msa);


int       rtRoot      (HRTREE rtH); /* returns location of first root in forest */

int       rtCurSize   (HRTREE rtH); /* returns current number of elements */
int       rtMaxSize   (HRTREE rtH); /* returns maximum number of elements */

int /* tree max usage */
rtMaxUsage(HRTREE rtH);


#ifdef __cplusplus
}
#endif


#endif /* _RTREE_ */

