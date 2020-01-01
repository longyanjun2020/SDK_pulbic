/***********************************************************************
Filename   : rvpqueue.h
Description: rvpqueue header file
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
 binary heap priority queues. Memory for the pool will be allocated
 and freed via callback functions.
 There are three types of pools:
	1)      FIXED: This creates a fixed priority queue. The size
			may only be changed with the RvPQueueChangeSize function.
	2)      EXPANDING: This creates a priority queue which expands as
			needed. When the priority queue runs out of space is will
			allocate a new space double the old size and release the old
			sace. The size may also be changed with the RvPQueueChangeSize
			function.
	3)      DYNAMIC: This creates a priority queue which expands exactly
			like an EXPANDING priority queue but also has the ability to
			reduce its size. When only 25% of the priority queue is in
			use, a new space 50% the old size will be allocated and the
			old space will be released. The size may also be changed with
			the RvPQueueChangeSize function. The size will never be reduced
			below the starting size.

 This module does no locking at all. The locking of the
 priority queue is the responsibility of the user.
***********************************************************************/

#ifndef RV_PQUEUE_H
#define RV_PQUEUE_H

#include "rvtypes.h"


#ifndef RV_PQUEUE_TEST
#define RV_PQUEUE_TEST RV_TEST_ALL
#endif

/********************************************************************************************
 * RvPQueueFuncs
 * A structure containing callback information for a priority queue. This structure
 * must be completely filled out before passing it to RvPQueueConstruct.
 * The memalloc and memfree callbacks will be used to allocate and release
 * memory used for the priority queue.
 * The itemcmp callback is the user defined operation that determines how the
 * priority queue sorts the items in the queue.
 * The newindex callback is a call that is made whenever an item is moved in the
 * priority queue. This allows the item to save its current position in case
 * it needs to remove itself from the priority queue.
 ********************************************************************************************/
typedef struct {
	void  *(*memalloc)(RvSize_t size, void *data);  /* Allocate memory for heap. Return pointer to memory, NULL = failed. */
	void   (*memfree)(void *ptr, void *data);       /* Free memory allocated by memalloc. */
	RvBool (*itemcmp)(void *ptr1, void *ptr2);      /* Compare 2 items, return RV_TRUE if ptr1 higher priority, else RV_FALSE. */
	void   (*newindex)(void *item, RvSize_t index); /* Store new index for item, use this for removing items. */
	void *memallocdata;    /* User data parameter passed into memalloc */
	void *memfreedata;     /* User data parameter passed into memfree */
} RvPQueueFuncs;


/********************************************************************************************
 * RvPQueue
 *  An priority queue object.
 ********************************************************************************************/
typedef struct {
	RvSize_t startsize;      /* Starting size of queue (heap), also is minimum size */
	RvSize_t cursize;        /* Current size of queue (heap) */
	RvInt qtype;             /* type of queue: see RV_PQUEUE_TYPE_ */
	RvPQueueFuncs callbacks; /* User defined function callbacks */
	RvSize_t numitems;       /* Number or items currently in the heap */
	RvSize_t maxconcurrentitems; /* maximum number of concurrent timers used in this queue */
	RvSize_t allocitems;     /* Number of items ever allocated per this queue */
	void **heap;             /* Actual heap array (which will be allocated) */
} RvPQueue;


/* Priority Queue Types */
/*   FIXED: heap stays fixed at starting size */
/*   EXPANDING: heap size is increased by a factor of 2 and reallocated when heap is full */
/*   DYNAMIC: heap size is reduced by a factor of 2 (min of startsize) when heap only 25% full */
#define RV_PQUEUE_TYPE_FIXED RvIntConst(0)
#define RV_PQUEUE_TYPE_EXPANDING RvIntConst(1)
#define RV_PQUEUE_TYPE_DYNAMIC RvIntConst(2)

#if defined(__cplusplus)
extern "C" {
#endif 

/********************************************************************************************
 * RvPQueueConstruct
 * Constructs a priority queue.
 * INPUT   : qtype - The type of priority queue: RV_PQUEUE_TYPE_FIXED, RV_PQUEUE_TYPE_EXPANDING, or RV_PQUEUE_TYPE_DYNAMIC.
 *           startsize - Starting size of priority queue.
 *           callbacks - Pointer to structure with callback information.
 * OUTPUT  : pqueue - Pointer to priority queue object to construct.
 * RETURN  : A pointer to the priority queue object or, if there is an error, NULL.
 * NOTE    : The callbacks structure will be copied so there is no need to maintain this
 *  		 structure after construction.
 *           If startsize is less than 2 it will be set to 2, which is the minimum size.
 *           DYNAMIC priority queues will never shrink below startsize.
 *           The callbacks structure must be completely filled in. A duplicate 
 *           of the callbacks structure will be made so that the user doesn't have 
 *           to keep their own copy of that structure. Note that the memalloc callback 
 *           will be called to allocate the starting array. See header file for qtype 
 *           options.
 */
RVCOREAPI 
RvPQueue * RVCALLCONV RvPQueueConstruct(
    IN RvInt qtype, 
    IN RvSize_t startsize, 
    IN RvPQueueFuncs *callbacks, 
    IN RvPQueue *pqueue);

/********************************************************************************************
 * RvPQueueDestruct
 * Destructs a priority queue.
 * INPUT   : pqueue - Pointer to priority queue object to destruct.
 * OUTPUT  : None
 * RETURN  : None.
 * NOTE    : Any items in the priority queue when it is destructed are considered removed.
 */
RVCOREAPI 
void RVCALLCONV RvPQueueDestruct(
    IN RvPQueue *pqueue);

/********************************************************************************************
 * RvPQueuePut
 * Puts a new item into a priority queue.
 * INPUT   : pqueue - Pointer to priority queue to add newitem into.
 *           newitem - Pointer to the item to put into the queue.
 * OUTPUT  : None
 * RETURN  : A pointer to newitem or, if the item can not be added to the priority queue, NULL.
 */
RVCOREAPI 
void * RVCALLCONV RvPQueuePut(
    IN RvPQueue *pqueue, 
    IN void *newitem);

/********************************************************************************************
 * RvPQueueGet
 * Gets the highest priority item from a priority queue. The item is removed from the queue.
 * INPUT   : pqueue - Pointer to priority queue to get item from.
 * OUTPUT  : None
 * RETURN  : A pointer to the highest priority item or NULL if the priority queue is empty.
 */
RVCOREAPI 
void * RVCALLCONV RvPQueueGet(
    IN RvPQueue *pqueue);

/********************************************************************************************
 * RvPQueuePeek
 * Gets the highest priority item from a priority queue. Does not remove the item from the queue.
 * INPUT   : pqueue - Pointer to priority queue to get item from.
 * OUTPUT  : None
 * RETURN  : A pointer to the highest priority item or NULL if the priority queue is empty.
 */
RVCOREAPI 
void * RVCALLCONV RvPQueuePeek(
    IN RvPQueue *pqueue);

/********************************************************************************************
 * RvPQueueNumItems
 * Gets number of items currently in a priority queue.
 * INPUT   : pqueue - Pointer to priority queue to get number of items of.
 * OUTPUT  : None
 * RETURN  : The number of items in the priority queue.
 */
RVCOREAPI 
RvSize_t RVCALLCONV RvPQueueNumItems(
    IN RvPQueue *pqueue);

/********************************************************************************************
 * RvPQueueMaxConcurrentItems
 * Gets number of maximum concurrent items in a priority queue.
 * INPUT   : pqueue - Pointer to priority queue to get number of items of.
 * OUTPUT  : None
 * RETURN  : The number of maximum concurrent items in the priority queue.
 */
RVCOREAPI
RvSize_t RVCALLCONV RvPQueueMaxConcurrentItems(
    IN RvPQueue *pqueue);

/********************************************************************************************
 * RvPQueueAllocatedItems
 * Gets number of items ever allocated per queue.
 * INPUT   : pqueue - Pointer to priority queue to get number of items of.
 * OUTPUT  : None
 * RETURN  : The number of items allocated in the priority queue.
 */
RVCOREAPI
RvSize_t RVCALLCONV RvPQueueAllocatedItems(
    IN RvPQueue *pqueue);

/********************************************************************************************
 * RvPQueueSize
 * Gets the size of a priority queue.
 * INPUT   : pqueue - Pointer to priority queue to get size of.
 * OUTPUT  : None
 * RETURN  : The size of the priority queue.
 */
RVCOREAPI 
RvSize_t RVCALLCONV RvPQueueSize(
    IN RvPQueue *pqueue);

/********************************************************************************************
 * RvPQueueChangeSize
 * Changes the size of a priority queue.
 * INPUT   : pqueue - Pointer to priority queue to change the size of.
 *           newsize - New size of priority queue.
 * OUTPUT  : None
 * RETURN  : The size of the priority queue. If the size could not be changed than the
 *			 old size of the queue is returned.
 * NOTE    : The size can not be made smaller than the current number of items in the
 *			 priority queue.
 *           The size can not be set smaller than 2.}
 *           For DYNAMIC priority queues this value replaces the startsize as
 *			 the minimum size of the priority queue.
 *           Force a change of the priority queue size. Can not change 
 *           the size smaller than the number of items in it. DYNAMIC 
 *           queues will not reduce below this value (same as startsize) 
 *           Returns new size (or old size if it couldn't be changed. 
 */
RVCOREAPI 
RvSize_t RVCALLCONV RvPQueueChangeSize(
    IN RvPQueue *pqueue, 
    IN RvSize_t newsize);

/********************************************************************************************
 * RvPQueueClear
 * Clears all items from a priority queue.
 * INPUT   : pqueue - Pointer to priority queue to clear.
 * OUTPUT  : None
 * RETURN  : None
 * NOTE    : For DYNAMIC priority queues, their size will shrink back to
 * 	 		 their minimum size, which is their starting size unless it was
 *			 changed with a call to RvPQueueChangeSize.
 */
RVCOREAPI 
void RVCALLCONV RvPQueueClear(
    IN RvPQueue *pqueue);

/********************************************************************************************
 * RvPQueueRemove
 * Removes an item from a priority queue. The item is specified by its
 * index which it is given via the newindex callback.
 * INPUT   : pqueue - Pointer to priority queue to remove item from.
 *           itemindex - Index of the item to be removed.
 * OUTPUT  : None
 * RETURN  : A pointer to item that has been removed from the priority queue or NULL there is an error.
 */
RVCOREAPI 
void * RVCALLCONV RvPQueueRemove(
    IN RvPQueue *pqueue, 
    IN RvSize_t itemindex);

#if RV_PQUEUE_TEST

typedef enum {
    RV_PQUEUE_NODE,
    RV_PQUEUE_LEFT,
    RV_PQUEUE_RIGHT,
    RV_PQUEUE_UP
} RvPQueueEnumOp;

typedef RvInt (*RvPQueueEnumerator)(RvPQueue *pq, RvPQueueEnumOp op, void *parent, void *item, void *ctx);

RVCOREAPI
RvInt RvPQueueEnumerate(RvPQueue *pq, RvPQueueEnumerator enumerator, void *ctx);

#endif
    

#if defined(__cplusplus)
}
#endif

#endif /* RV_PQUEUE_H */
