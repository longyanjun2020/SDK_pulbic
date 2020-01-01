/***********************************************************************
Filename   : objlist.h
Description: objlist header file
             This module provides functions for creating and manipulating
			 structure lists.
		     To make a structure usable in a list, an element of type
			 RvObjListElement must be declared in that structure.
************************************************************************
      Copyright (c) 2001,2002 RADVISION Inc. and RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Inc. and RADVISION Ltd.. No part of this document may be
reproduced in any form whatsoever without written prior approval by
RADVISION Inc. or RADVISION Ltd..

RADVISION Inc. and RADVISION Ltd. reserve the right to revise this
publication and make changes without obligation to notify any person of
such revisions or changes.
***********************************************************************/
#ifndef RV_OBJLIST_H
#define RV_OBJLIST_H

#include "rvtypes.h"


/********************************************************************************************
 * RvObjListElement
 * An element of this data type must be declared in the
 * structure to be put into a list.
 * The information stored in this element is only used while a
 * particular object is actually in the list. The information
 * stored in that element does not need to be maintained when
 * the object is not in the list, even if it is to be returned
 * to a list..
 * A structure can be put into multiple lists by simply declaring
 * multiple elements of this type in thrie structure.
 * This module does no locking at all. The locking of the object list is the
 * responsibility of the user.
 ********************************************************************************************/
typedef struct RvObjListElement_s RvObjListElement;
struct RvObjListElement_s {
	RvObjListElement *prev, *next;
	void *obj;
};


/********************************************************************************************
 * RvObjList
 * An object list object.
 ********************************************************************************************/
typedef struct {
	RvObjListElement anchor;
	RvSize_t count;
	RvPtrdiff_t offset;
} RvObjList;

/* Constants for indicating if items should be removed from the list. */
#define RV_OBJLIST_REMOVE RV_TRUE
#define RV_OBJLIST_LEAVE RV_FALSE

#if defined(__cplusplus)
extern "C" {
#endif

/* Prototypes and macros: See documentation blocks below for details. */

/********************************************************************************************
 * RvObjListConstruct
 * Constructs an object list.
 * INPUT   : itemtmp - Pointer to an object of the type to be stored in the list.
 *           elementptr - Pointer to the element within itemtmp to use for this list.
 * OUTPUT  : objlist - Pointer to object list object to construct.
 * RETURN  : A pointer to the object list object or, if there is an error, NULL.
 * NOTE    : The itemtmp and elementptr pointers are simply used to find the offset
 *           within the structure where the RvObjListElement element is located.
 *           Anything the itemtmp pointer may point is is never touched.}
 *           For a more complicated structure, the RvObjListElement element can
 *           be placed outside the actual structure that will be in the list.
 *           It can even be before the structure itself, resulting in a negative
 *           offset. As long as the offset between the pointer passed in for an
 *           item and the location of the RvObjListElement data is constant, it
 *           will work.
 *           The template object is never touched and is simply used to find the
 *           location of the RvObjListElement structure (elementptr) within it.
 *           It is possible to put the Element structure outside of the the object
 *           and have a negative offset between the two.
 */
RVCOREAPI
RvObjList * RVCALLCONV RvObjListConstruct(
    IN void *itemtemp,
    IN RvObjListElement *elementptr,
    OUT RvObjList *objlist);

/********************************************************************************************
 * RvObjListSize
 * Get the current size of an object list.
 * INPUT   : objlist - Pointer to object list to get size of.
 * OUTPUT  : None
 * RETURN  : The size of the object list.
 */
RVCOREAPI
RvSize_t RVCALLCONV RvObjListSize(
    IN RvObjList *objlist);

/********************************************************************************************
 * RvObjListInsertAfter
 * Inserts a new object into the list after a specified item.
 * INPUT   : objlist - Pointer to object list to insert new item into.
 *           curitem - Pointer to item to insert new item after (NULL puts new item at beginning of list.
 * OUTPUT  : newitem - Pointer to new item to be inserted into the list.
 * RETURN  : A pointer to newitem or NULL if the item could not be inserted.
 * NOTE    : The curitem item must be in the list because that condition will not
 *           be detected and will cause major problems.
 *           If curitem is NULL than item is put at start of list.
 */
RVCOREAPI
void * RVCALLCONV RvObjListInsertAfter(
    IN RvObjList *objlist,
    IN void *curitem,
    OUT void *newitem);

/********************************************************************************************
 * RvObjListInsertBefore
 * Inserts a new object into the list before a specified item.
 * INPUT   : objlist - Pointer to object list to insert new item into.
 *           curitem - Pointer to item to insert new item after (NULL puts new item at the end of list.
 * OUTPUT  : newitem - Pointer to new item to be inserted into the list.
 * RETURN  : A pointer to newitem or NULL if the item could not be inserted.
 * NOTE    : The curitem item must be in the list because that condition will not
 *           be detected and will cause major problems.
 *           If curitem is NULL than item is put at end of list.
 */
RVCOREAPI
void * RVCALLCONV RvObjListInsertBefore(
    IN RvObjList *objlist,
    IN void *curitem,
    OUT void *newitem);

/********************************************************************************************
 * RvObjListGetNext
 * Gets the next item after a particular item in a list.
 * INPUT   : objlist - Pointer to object list to insert new item into.
 *           curitem - Pointer to item to insert new item after (NULL puts new item at beginning of list.
 *           removeitem - Set to RV_OBJLIST_REMOVE to remove the item from the list or set it
 *									to RV_OBJLIST_LEAVE to leave the item in the list.
 * OUTPUT  : None.
 * RETURN  : A pointer to the next item or NULL if curitem was the last item in the list.
 * NOTE    : The curitem item must be in the list because that
 *           condition will not be detected and will cause major problems.
 */
RVCOREAPI
void * RVCALLCONV RvObjListGetNext(
    IN RvObjList *objlist,
    IN void *curitem,
    IN RvBool removeitem);

/********************************************************************************************
 * RvObjListGetPrevious
 * Gets the previous item before a particular item in a list.
 * INPUT   : objlist - Pointer to object list to insert new item into.
 *           curitem - Pointer to item to insert new item after (NULL puts new item at beginning of list.
 *           removeitem - Set to RV_OBJLIST_REMOVE to remove the item from the list or set it
 *									to RV_OBJLIST_LEAVE to leave the item in the list.
 * OUTPUT  : None.
 * RETURN  : A pointer to the previous item or NULL if curitem was the first item in the list.
 * NOTE    : The curitem item must be in the list because that
 *           condition will not be detected and will cause major problems.
 */
RVCOREAPI
void * RVCALLCONV RvObjListGetPrevious(
    IN RvObjList *objlist,
    IN void *curitem,
    IN RvBool removeitem);

/********************************************************************************************
 * RvObjListRemoveItem
 * Removes an items from a list.
 * INPUT   : objlist - Pointer to object list to remove item from.
 *           item - Pointer to item to remove from the list.
 * OUTPUT  : None.
 * RETURN  : A pointer to the previous item that was removed or NULL if it could not be removed.
 * NOTE    : Do not remove an item from a list that it is not in because that
 * 			 condition will not be detected and will cause major problems.
 */
RVCOREAPI
void * RVCALLCONV RvObjListRemoveItem(
    IN RvObjList *objlist,
    IN void *item);

/********************************************************************************************
 * RvObjListDestruct
 * Destructs an object list.
 * PARAMS   : _objlist - Pointer to object list object to be destructed.
 * NOTE    : Any items still in the list are left untouched.
 ********************************************************************************************/
#define RvObjListDestruct(_objlist) /* Doesn't need to do anything. */


 /********************************************************************************************
 * RvObjListReset
 *
 * Resets (clears) the objlist. After resetting state of the objlist is identical to the
 *  state just after construction.
 *
 * INPUT   : objlist - Pointer to object list to remove item from.
 * OUTPUT  : None.
 * RETURN  : A pointer to the objlist itself
 */
RVCOREAPI
RvObjList* RVCALLCONV RvObjListReset(RvObjList *objlist);


#if defined(__cplusplus)
}
#endif

#endif /* RV_OBJLIST_H */
