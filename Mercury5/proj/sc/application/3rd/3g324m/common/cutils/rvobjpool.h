/***********************************************************************
Filename   : objpool.h
Description: objpool header file
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

/***********************************************************************
This module provides functions for creating and manipulating
object pools. Memory for the pool will be allocated and freed
via callback functions.
To make a object (structure) usable in a pool, an element of type
RvObjPoolElement must be declared in that structure. You may also
need functions for constructing and destructing the object.
There are three types of pools:
    FIXED: This creates a fixed size pool. Items may only be
    added to the pool with the RvObjPoolAddItems and
    RvObjPoolAddPages functions. Items may only be removed
    with the RvObjPoolSalvage function (and only if the salvage
    option has been enabled). FIXED pools are subject to the
    maxitems and minitems settings but those settings will
    rarely be used with fixed pools.}
    EXPANDING: This creates a pool which expands (by adding
    pages) as needed. Items may also be added to the pool with
    the RvObjPoolAddItems and RvObjPoolAddPages functions. Items
    may only be removed with the RvObjPoolSalvage function (and
    only if the salvage option has been enabled). The maxitems
    and minitems settings may be used to put boundaries on the
    size of the pool.}
    DYNAMIC: This creates a pool which expands exactly like
    and EXPANDING pool but also has the ability to removed
    unused pages. The freelevel setting determines when a
    page should be released. Items may also be added to the
    pool with the RvObjPoolAddItems and RvObjPoolAddPages
    functions and may removed with the RvObjPoolSalvage
    function. The maxitems and minitems settings may be used
    to put boundaries on the size of the pool.}

This module does no locking at all. The locking of the
object pool is the responsibility of the user.}
***********************************************************************/

#ifndef RV_OBJPOOL_H
#define RV_OBJPOOL_H

#include "rvtypes.h"
#include "rvobjlist.h"


#ifndef RV_OBJPOOL_TEST
#define RV_OBJPOOL_TEST 0
#endif

/********************************************************************************************
 * RvObjPoolElement
 * An element of this data type must be declared in the
 * structure to be put into a pool.
 * The information stored in this element is only used while a
 * particular object is actually in the pool. The information
 * stored in that element does not need to be maintained when
 * the object is not in the pool.
 * An object type can be used to create multiple pools but
 * any individual object can only be in one pool, thus there
 * is never a need for more than one element in a structure.
 ********************************************************************************************/
typedef RvObjListElement RvObjPoolElement;


/********************************************************************************************
 * RvObjPoolFuncs
 * A structure containing callback information for an object pool. This structure
 * must be completely filled out before passing it to RvObjPoolConstruct.}
 * Normal operation of a pool will constist of creating and destroying pages. Each
 * page constains a given number of the objects in the pool. When a page is created,
 * the pagealloc callback with the number of bytes required for the page followed by
 * a call to objconstruct for each object in the new page. When destroying a page,
 * the objdestruct will be called on each object, then pagefree will be called for
 * the page.
 * The objconstruct and objdestruct calls are optional. Setting them to NULL
 * simply indicates that there is no constructor and/or destructor for the
 * object type being pooled.
 ********************************************************************************************/
typedef struct {
	void *(*objconstruct)(void *objptr, void *data); /* (optional) Construct object in pool. Return pointer to item, NULL = failed. */
	void  (*objdestruct)(void *objptr, void *data);  /* (optional) Destruct object in pool. */
	void *(*pagealloc)(RvSize_t size, void *data);   /* Allocate page of memory. Return pointer to page memory, NULL = failed. */
	void  (*pagefree)(void *ptr, void *data);        /* Free page of memory. */
	void *objconstructdata; /* User data parameter passed into objconstruct */
	void *objdestructdata;  /* User data parameter passed into objdestruct */
	void *pageallocdata;    /* User data parameter passed into pagealloc */
	void *pagefreedata;     /* User data parameter passed into pagefree */
} RvObjPoolFuncs;


/********************************************************************************************
 * RvObjPool
 * An object pool object.
 ********************************************************************************************/
typedef struct {
	RvObjList pagelist;       /* List of pages in pool */
	RvObjList freelist;       /* List of available items */
	RvObjPoolFuncs callbacks; /* User defined function callbacks */
	RvSize_t itemsize;        /* Size of each item */
	RvSize_t pageitems;       /* Number of items per page */
	RvSize_t pagesize;        /* Size (in bytes) of each page */
	RvSize_t blocksize;       /* size of memory block used for each item (calculated) */
	RvBool autoexpand;        /* RV_TRUE if pages automatically created as needed */
	RvBool autoreduct;        /* RV_TRUE if pages should be removed automatically */
	RvSize_t maxitems;        /* Number of items in pool will never exceed this value. */
	RvSize_t minitems;        /* Number of items in pool will never go below this value. */
	RvBool allowsalvage;      /* RV_TRUE if pages can be removed */
	RvSize_t reductlevel;     /* automatically removing a page will not leave less than */
	                          /*   reductlevel free items per 100 */
} RvObjPool;

/* Pool Types: options are passed in via the data parameter */
/*   FIXED: Pages only added by PageAdd commands */
/*   EXPANDING: Pages added as needed */
/*   DYNAMIC: Pages added as needed and removed automatically. */
#define RV_OBJPOOL_TYPE_FIXED RvIntConst(0)
#define RV_OBJPOOL_TYPE_EXPANDING RvIntConst(1)
#define RV_OBJPOOL_TYPE_DYNAMIC RvIntConst(2)

/* Options for salvage setting. */
#define RV_OBJPOOL_SALVAGE_ALLOWED RV_TRUE
#define RV_OBJPOOL_SALVAGE_NEVER RV_FALSE

#if defined(__cplusplus)
extern "C" {
#endif 

/* Prototypes: See documentation blocks below for details. */
    
/********************************************************************************************
 * RvObjPoolConstruct
 * Constructs an object pool.
 * INPUT   :    itemtemp - Pointer to an object of the type to be stored in the pool.
 *              elementptr - Pointer to the element within itemtemp to use for this pool.
 *              callbacks - Pointer to structure with callback information.
 *              itemsize - The size of the item to being stored in the pool.
 *              pageitems - Number of items per page (0 = calculate from pagesize).
 *              pagesize - Size of each page (0 = calculate from pageitems).
 *              pooltype - The type of block pool: RV_OBJPOOL_TYPE_FIXED, RV_OBJPOOL_TYPE_EXPANDING, or RV_OB
 *              salvage - Set to RV_OBJPOOL_SALVAGE_ALLOWED to allow page salvage, otherwise RV_OBJPOOL_SALVA  
 *           				Must be set to RV_OBJPOOL_SALVAGE_ALLOWED for DYNAMIC pools. Enabling this    
 *           				options incurs some additional memory overhead.
 *              maxitems - Number of items never to exceed this value (0 = no max).
 *              minitems - Number of items never to go below this value.
 *              freelevel - Minimum number of items free per 100 (0 to 100). Used for DYNAMIC pools only.
 * OUTPUT  :    objpool - Pointer to object pool object to construct.
 * RETURN  : A pointer to the object pool object or, if there is an error, NULL.
 * NOTE    :    The itemtemp and elementptr pointers are simply used to find the offset
 *              within the structure where the RvObjPoolElement element is located.
 *              Anything the itemtemp pointer may point is is never touched.
 *              The callbacks structure will be copied so there is no need to maintain this
 *              structure after construction.
 *              Disabling the salvage option reduces memory overhead. For DYNAMIC pools
 *              the salvage option must be enabled.
 */
RVCOREAPI 
RvObjPool * RVCALLCONV RvObjPoolConstruct( 
    IN void *itemtemp, 
    IN RvObjPoolElement *elementptr, 
    IN RvObjPoolFuncs *callbacks, 
    IN RvSize_t itemsize, 
    IN RvSize_t pageitems, 
    IN RvSize_t pagesize, 
    IN RvInt pooltype, 
    IN RvBool salvage, 
    IN RvSize_t maxitems, 
    IN RvSize_t minitems, 
    IN RvSize_t freelevel,
    OUT RvObjPool *objpool);

/********************************************************************************************
 * RvObjPoolDestruct
 * Destructs an object pool.
 * INPUT   :    objpool - Pointer to object pool object to be destructed.
 * OUTPUT  : None.
 * RETURN  : RV_TRUE if object pool has been destructed, RV_FALSE if not.
 * NOTE    : A pool can only be destructed if all items have been returned to
 *           the pool. Trying to destroy a pool with items missing will simply
 *           do nothing and return a value of RV_FALSE.
 */
RVCOREAPI 
RvBool RVCALLCONV RvObjPoolDestruct(
    IN RvObjPool *objpool);

/********************************************************************************************
 * RvObjPoolTotalItems
 * Gets the total number of items in an object pool.
 * INPUT   : objpool - Pointer to object pool to get information about.
 * OUTPUT  : None.
 * RETURN  : Total number of items in the object pool.
 */
RVCOREAPI 
RvSize_t RVCALLCONV RvObjPoolTotalItems(
    IN RvObjPool *objpool);

/********************************************************************************************
 * RvObjPoolFreeItems
 * Gets the number of items currently available in an object pool.
 * INPUT   : objpool - Pointer to object pool to get information about.
 * OUTPUT  : None.
 * RETURN  : Number of items currently available in the object pool.
 */
RVCOREAPI 
RvSize_t RVCALLCONV RvObjPoolFreeItems(
    IN RvObjPool *objpool);

/********************************************************************************************
 * RvObjPoolTotalPages
 * Gets the total number of pages in an object pool.
 * INPUT   : objpool - Pointer to object pool to get information about.
 * OUTPUT  : None.
 * RETURN  : Total number of pages in the object pool.
 */
RVCOREAPI 
RvSize_t RVCALLCONV RvObjPoolTotalPages(
    IN RvObjPool *objpool);

/********************************************************************************************
 * RvObjPoolItemsPerPage
 * Gets the number of items per page in an object pool.
 * INPUT   : objpool - Pointer to object pool to get information about.
 * OUTPUT  : None.
 * RETURN  : Number of items per page in the object pool.
 */
RVCOREAPI 
RvSize_t RVCALLCONV RvObjPoolItemsPerPage(
    IN RvObjPool *objpool);

/********************************************************************************************
 * RvObjPoolBlockSize
 * Gets the actual size of the memory block used by each item.
 * INPUT   : objpool - Pointer to object pool to get information about.
 * OUTPUT  : None.
 * RETURN  : Actual size of the memory block used by each item.
 */
RVCOREAPI 
RvSize_t RVCALLCONV RvObjPoolItemBlockSize(
    IN RvObjPool *objpool);

/********************************************************************************************
 * RvObjPoolPageSize
 * Gets the page size (in bytes) of an object pool.
 * INPUT   : objpool - Pointer to object pool to get information about.
 * OUTPUT  : None.
 * RETURN  : Page size, in bytes, of the object pool.
 */
RVCOREAPI 
RvSize_t RVCALLCONV RvObjPoolPageSize(
    IN RvObjPool *objpool);

/********************************************************************************************
 * RvObjPoolGetMaxitems
 * Gets the current maxitems setting. This is the maximum size that
 * the object pool may be.
 * INPUT   : objpool - Pointer to object pool to get information about.
 * OUTPUT  : None.
 * RETURN  : Maximum number of items allowed in the object pool.
 * NOTE    : The actual maximum number of items that may be in the pool may
 * 			 be less than this amount since items are allocated a page at a time.
 */
RVCOREAPI 
RvSize_t RVCALLCONV RvObjPoolGetMaxitems(
    IN RvObjPool *objpool);

/********************************************************************************************
 * RvObjPoolSetMaxitems
 * Sets the current maxitems setting. This is the maximum size that the object pool may be.
 * INPUT   : objpool - Pointer to object pool to set maxitems for.
 *           new - New value for maxitems (0 = no maximum).
 * OUTPUT  : None.
 * RETURN  : RV_TRUE if maxitems set successfully, otherwise RV_FALSE.
 * NOTE    : The actual maximum number of items that may be in the pool may
 *           be less than this amount since items are allocated a page at a time.
 *           Setting maxitems to be lower than minitems or to a value smaller
 *           than the current size ifs not allowed.
 *           This setting should not normally be used for FIXED pools.
 */
RVCOREAPI 
RvBool RVCALLCONV RvObjPoolSetMaxitems(
    IN RvObjPool *objpool, 
    IN RvSize_t newmax);

/********************************************************************************************
 * RvObjPoolGetMinitems
 * Gets the current minitems setting. This is the minimum size that the object pool may be.
 * INPUT   : objpool - Pointer to object pool to get information about.
 * OUTPUT  : None.
 * RETURN  : Minimum number of items allowed in the object pool.
 * NOTE    : The actual minimum number of items that may be in the pool may
 *   		 be larger than this amount since items are allocated a page at a time.
 */
RVCOREAPI 
RvSize_t RVCALLCONV RvObjPoolGetMinitems(
    IN RvObjPool *objpool);

/********************************************************************************************
 * RvObjPoolSetMinitems
 * Sets the current minitems setting. This is the minimum size that
 * the object pool may be.
 * INPUT   : objpool - Pointer to object pool to set minitems for.
 *           new - New value for minitems.
 * OUTPUT  : None.
 * RETURN  : RV_TRUE if minitems set successfully, otherwise RV_FALSE.
 * NOTE    : The actual minimum number of items that may be in the pool may
 *   		 be larger than this amount since items are allocated a page at a time.
 *           The actual minimum number of items that may be in the pool may
 *           be larger than this amount since items are allocated a page at a
 *           time.
 *           Setting minitems to be larger than maxitems is not allowed.
 *           This setting should not normally be used for FIXED pools.
 */
RVCOREAPI 
RvBool RVCALLCONV RvObjPoolSetMinitems(
    IN RvObjPool *objpool, 
    IN RvSize_t newmin);

/********************************************************************************************
 * RvObjPoolGetFreelevel
 * Gets the current freelevel setting. This is the minimum number of free items
 * per 100 that should be maintained.
 * INPUT   : objpool - Pointer to object pool to get information about.
 * OUTPUT  : None.
 * RETURN  : Minumum number of free items per 100 to be maintained (0 to 100).
 */
RVCOREAPI 
RvSize_t RVCALLCONV RvObjPoolGetFreelevel(
    IN RvObjPool *objpool);

/********************************************************************************************
 * RvObjPoolSetFreelevel
 * Sets the current freelevel setting. This is the minimum number of free items
 * per 100 that should be maintained.
 * INPUT   : objpool - Pointer to object pool to set freelevel for.
 *           newlevel - New value for freelevel.
 * OUTPUT  : None.
 * RETURN  : RV_TRUE if freelevel set successfully, otherwise RV_FALSE.
 * NOTE    : The freelevel setting is only used for DYNAMIC pools.
 *           Setting freelevel to 0 will cause a page to be released as soon
 *           as it has all items returned to it.
 *           Setting freelevel to 100 will never release pages and is the
 *           equivalent of using an EXPANDED pool.
 */
RVCOREAPI 
RvBool RVCALLCONV RvObjPoolSetFreelevel(
    IN RvObjPool *objpool, 
    IN RvSize_t newlevel);

/********************************************************************************************
 * RvObjPoolAddItems
 * Adds the requested number of items to a pool.
 * INPUT   : objpool - Pointer to object pool to add items to.
 *           numitems - Number of items to add (0 indicates to add a page of items).
 * OUTPUT  : None.
 * RETURN  : Actual number of items added.
 * NOTE    : The actual number of items added may be larger than that
 * 			 requested since items are added in multiples of the number
 * 			 of items in a page.
 *           If the actual number of items is less than that requested
 *           it means that those items could not be added because
 *           no more pages could be allocated, no more items could
 *           be constructed, or the maxitems limit was reached.
 */
RVCOREAPI 
RvSize_t RVCALLCONV RvObjPoolAddItems(
    IN RvObjPool *objpool, 
    IN RvSize_t numitems);

/********************************************************************************************
 * RvObjPoolAddPages
 * Adds the requested number of pages to a pool.
 * INPUT   : objpool - Pointer to object pool to add pages to.
 *           numpages - Number of pages to add.
 * OUTPUT  : None.
 * RETURN  : Actual number of pages added.
 * NOTE    : If the actual number of items is less than that requested
 *           it means that those items could not be added because
 *           no more pages could be allocated, no more items could
 *           be constructed, or the maxitems limit was reached.
 */
RVCOREAPI 
RvSize_t RVCALLCONV RvObjPoolAddPages(
    IN RvObjPool *objpool, 
    IN RvSize_t numpages);

/********************************************************************************************
 * RvObjPoolSalvage
 * Release any pages in an object pool which have no items allocated from them.
 * INPUT   : objpool - Pointer to object pool to salvage.
 * OUTPUT  : None.
 * RETURN  : Actual number of pages added.
 * NOTE    : Calling this function on an object pool which had the salvage option
 * 		     disabled will do nothing (and return a 0).
 *           The number of pages released is limited by the minitems setting.
 */
RVCOREAPI 
RvSize_t RVCALLCONV RvObjPoolSalvage(
    IN RvObjPool *objpool);

/********************************************************************************************
 * RvObjPoolGetItem
 * Get an item from a pool.
 * INPUT   : objpool - Pointer to object pool to get item from.
 * OUTPUT  : None.
 * RETURN  : Pointer to object allocated or NULL is none are available.
 * NOTE    : Items may only be returned to the pool they came from.
 */
RVCOREAPI 
void * RVCALLCONV RvObjPoolGetItem(
    IN RvObjPool *objpool);

/********************************************************************************************
 * RvObjPoolReleaseItem
 * Returns an item back to a pool.
 * INPUT   : objpool - Pointer to object pool to return item to.
 *           item - Pointer to item to be returned.
 * OUTPUT  : None.
 * RETURN  : RV_TRUE if successful otherwise RV_FALSE.
 */
RVCOREAPI 
RvBool RVCALLCONV RvObjPoolReleaseItem(
    IN RvObjPool *objpool, 
    IN void *item);



/********************************************************************************************
 * RvObjPoolReset
 *
 * Resets an object pool. 
 * INPUT   : objpool - Pointer to object pool to return item to.
 * OUTPUT  : None.
 * RETURN  : None
 */
RVCOREAPI
void RVCALLCONV RvObjPoolReset(IN RvObjPool *objpool);



#if RV_OBJPOOL_TEST

/* Debug functions */

typedef RvBool (*RvObjPoolEnumerator)(RvObjPool *objpool, void *enumCtx, void *item, RvBool isFreeItem);

RVCOREAPI
RvInt RvObjPoolEnumerate(RvObjPool *objpool, RvObjPoolEnumerator enumerator, void *enumCtx);

#endif

#if defined(__cplusplus)
}
#endif 

#endif /* RV_OBJPOOL_H */
