/* rvqueue.h - rvqueue header file */
/************************************************************************
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

#ifndef RV_QUEUE_H
#define RV_QUEUE_H

#include "rvcbase.h"
#include "rvlock.h"
#include "rvsemaphore.h"
#include "rvmemory.h"

/* Error checks to make sure configuration has been done properly */
#if !defined(RV_QUEUE_TYPE) || \
    ((RV_QUEUE_TYPE != RV_QUEUE_STANDARD) && (RV_QUEUE_TYPE != RV_QUEUE_NONE))
#error RV_QUEUE_TYPE not set properly
#endif
/* End of configuration error checks */

/* Module specific error codes (-512..-1023). See rverror.h for more details */
#define RV_QUEUE_ERROR_EMPTY   -512 /* queue is empty */
#define RV_QUEUE_ERROR_FULL    -513 /* queue is full */
#define RV_QUEUE_ERROR_STOPPED -514 /* queue is stopped */

/* priority for RvQueueSend, URGENT puts item at front of queue */
#define RV_QUEUE_SEND_NORMAL RvIntConst(0)
#define RV_QUEUE_SEND_URGENT RvIntConst(1)

/* Constants for indicating if queue functions should block. */
#define RV_QUEUE_WAIT RV_TRUE
#define RV_QUEUE_NOWAIT RV_FALSE


/*******************************************************************************************
 * RvQueue -  A queue object.
 *******************************************************************************************/
typedef struct {
	RvSize_t size;        /* Maximum number of items in queue */
	RvSize_t curitems;    /* current number of items in queue */
	RvSize_t itemsize;    /* size of each item in queue */
	RvLock lock;          /* lock on queue data structure */
	RvSemaphore emptysem; /* semaphore to block tasks waiting due to empty queue */
	RvSemaphore fullsem;  /* semaphore to block tasks waiting due to full queue */
	RvSize_t waitempty;   /* number of tasks waiting on "emptysem" */
	RvSize_t waitfull;    /* number of tasks waiting on "fullsem" */
	RvSize_t notifyempty; /* Number of tasks waiting on "emptysem" told to continue */
	RvSize_t notifyfull;  /* Number of tasks waiting on "fullsem" told to continue */
	void *bufstart;       /* start of queue storage, first physical item */
	void *bufend;         /* end of queue storage, last physical item */
	void *firstitem;      /* current logical item at front of queue */
	void *lastitem;       /* current logical item at end of queue */
	RvBool stopped;       /* set to RV_TRUE when queue has been stopped */
	RvLogMgr* logMgr;           /* queue log manager */
	RvLogSource* queueSource;   /* log source, to be used for the queue module instance */
} RvQueue;

#if defined(__cplusplus)
extern "C" {
#endif 

/*******************************************************************************************
						 PROTOTYPES
 *******************************************************************************************/

/********************************************************************************************
 * RvQueueInit - Initializes the Queue module
 *
 * Must be called once (and only once) before any other functions in the module are called. 
 * Thread-safe function
 *
 * INPUT   : none
 * OUTPUT  : none
 * RETURN  : always RV_OK
 */
RvStatus RvQueueInit(void);

/********************************************************************************************
 * RvQueueEnd - Shuts down the Queue module.
 *
 * Must be called once (and only once) when no further calls to this module will be made.
 * Thread-safe function
 *
 * INPUT   : none
 * OUTPUT  : none
 * RETURN  : always RV_OK
 */
RvStatus RvQueueEnd(void);

/********************************************************************************************
 * RvQueueSourceConstruct - Constructs queue module log source.
 *
 * Constructs log source to be used by common core when printing log from the 
 * queue module. This function is applied per instance of log manager.
 * 
 * INPUT   : logMgr - log manager instance
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code. 
 */
RvStatus RvQueueSourceConstruct(IN RvLogMgr	*logMgr);


/********************************************************************************************
 * RvQueueConstruct - Constructs a queue object based on the parameters passed in.
 *
 * Must be called once (and only once) when no further calls to this module will be made.
 * Memory is allocated from region bufmem unless the OS allocates its own memory 
 * and doesn't provide any control over it. 
 *
 * INPUT   : numitems - number of items that the queue should be able to hold.
 *			 itemsize - Maximum size of each item that will put put into the queue.
 *			 bufmem   - Memory region to allocate queue memeory from (NULL = default region).
 *			 logMgr   - log manager
 * OUTPUT  : queue    - constructed queue
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI 
RvStatus RVCALLCONV RvQueueConstruct(
	IN	RvSize_t	numitems,
	IN	RvSize_t	itemsize, 
	IN	RvMemory	*bufmem,
	IN	RvLogMgr	*logMgr, 
	OUT	RvQueue		*queue);

/********************************************************************************************
 * RvQueueDestruct - Destructs a queue.
 *
 * All items in the queue are lost when the queue is destructed.
 * Insure that no threads are operating on the queue when it is
 * destructing since not all operating systems handle the situation
 * gracefully.
 *
 * INPUT   : queue    - Pointer to queue object to be Destructed.
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI 
RvStatus RVCALLCONV RvQueueDestruct(
	IN RvQueue *queue);


/********************************************************************************************
 * RvQueueReceive - Gets an item from the front of a queue.
 *
 * A thread waiting for data on a queue will be resumed and return
 * RV_QUEUE_ERROR_STOPPED if the queue is stopped.
 * If the buffer is smaller than the item in the queue, the data
 * copied into the buffer will be truncated.
 *
 * INPUT   : queue    - Pointer to queue object to get item from.
 *			 wait     - Set to RV_QUEUE_WAIT if thread should wait until item is available.
 *						If set to RV_QUEUE_NOWAIT, RV_QUEUE_ERROR_EMPTY will be returned if
 *						no item is available.
 * OUTPUT  : buf      - Pointer to buffer that item will be copied to.
 *           bufsize  - Size of the buffer that buf points to.
 * RETURN  : RV_OK if successful otherwise an error code. An error code of RV_QUEUE_ERROR_STOPPED
 *			indicates that the queue has been permanently stopped and there are no more items
 *			available in the queue.
 */
RVCOREAPI RvStatus RVCALLCONV RvQueueReceive(
	IN  RvQueue		*queue, 
	IN  RvBool		wait,
	OUT RvSize_t	bufsize, 
	OUT void		*buf);


/********************************************************************************************
 * RvQueueSend - Puts an item into a queue.
 *
 * A thread waiting to put data on a queue will be resumed and return
 * RV_QUEUE_ERROR_STOPPED if the queue is stopped.
 *
 * INPUT   : queue    - Pointer to queue object where item should be placed.
 *			 buf	  - Pointer to buffer that contains the item.
 *			 bufsize  - Size of the item that buf points to.
 *			 priority - Set to RV_QUEUE_SEND_NORMAL to put item at the end of the queue.
 *						Set to RV_QUEUE_SEND_URGENT to put the item at the front
 *						of the queue.
 *			 wait     - Set to RV_QUEUE_WAIT if thread should wait until space is available
 *						in the queue for the item. If set to RV_QUEUE_NOWAIT,
 *						RV_QUEUE_ERROR_FULL will be returned if there is no space in the queue.
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code. An error code of RV_QUEUE_ERROR_STOPPED
 *			indicates that the queue has been permanently stopped and no more items are allowed
 *			to be put in the queue.
 */
RVCOREAPI 
RvStatus RVCALLCONV RvQueueSend(
	IN  RvQueue		*queue, 
	IN  void		*buf, 
	IN  RvSize_t	bufsize,
	IN  RvInt		priority, 
	IN  RvBool		wait);


/********************************************************************************************
 * RvQueueStop - Permanently stops a queue.
 *
 * No more items will be allowed to be put on the queue.
 * Threads waiting to get items from the queue or waiting to put items onto the queue
 * will be resumed (and return with an error code indicating that the queue has been
 * stopped). Items already on the queue will still be available.
 * When a queue is stopped it is permanent, there is no way to undo it.
 * 
 * INPUT   : queue    - Pointer to queue object to be stopped.
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI
RvStatus RVCALLCONV RvQueueStop(
	IN RvQueue *queue);


/********************************************************************************************
 * RvQueueClear - Clears all items from a queue.
 *
 * note:  Stopped queues may be cleared.
 *
 * INPUT   : queue    - Pointer to queue object to be cleared.
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI RvStatus RVCALLCONV RvQueueClear(
	IN RvQueue *queue);


/********************************************************************************************
 * RvQueueIsStopped - Checks to see if a queue has been stopped.
 *
 * INPUT   : queue    - Pointer to queue object to check.
 * OUTPUT  : none
 * RETURN  : Returns RV_TRUE if the queue has been stopped, RV_FALSE otherwise.
 */
RVCOREAPI RvBool RVCALLCONV RvQueueIsStopped(
	IN RvQueue *queue);


/********************************************************************************************
 * RvQueueSize - Finds out the size of the queue.
 *
 * INPUT   : queue    - Pointer to queue object to check.
 * OUTPUT  : none
 * RETURN  : The maximum number of items that the queue can hold.
 */
RVCOREAPI RvSize_t RVCALLCONV RvQueueSize(
	IN RvQueue *queue);


/********************************************************************************************
 * RvQueueItems - Finds out the number of items currently on the queue.
 *
 * INPUT   : queue    - Pointer to queue object to check.
 * OUTPUT  : none
 * RETURN  : The current number of items on the queue.
 */
RVCOREAPI RvSize_t RVCALLCONV RvQueueItems(
	IN RvQueue *queue);


#if defined(__cplusplus)
}
#endif 


#endif
