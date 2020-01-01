/** @file sys_sys_queue.h
 * @author Piazza.Lo
 * @date 04/07/2010
 *
 * General queue utility interface
 */
 
#ifndef __SYS_SYS_QUEUE_H__
#define __SYS_SYS_QUEUE_H__

#include "vm_types.ht"

/************************************************************************/
/*                                                   Macros                                                              */
/************************************************************************/

/************************************************************************/
/*                                                   Types                                                               */
/************************************************************************/
typedef enum QueueErr_e_
{
	QUEUE_OK = 0,
	QUEUE_INVALID_PARAM,
	QUEUE_NON_INITIALIZE,
	QUEUE_OVERFLOW,
	QUEUE_UNDERFLOW,
	
	QUEUE_ERR_LAST = 255
} QueueErr_e;

typedef struct Node_t_
{
	struct Node_t_ *Next;  // Next node
	void *Element;   // Pointed object
} Node_t, *pNode_t;

typedef struct MsQueue_t_
{
	Node_t *First;  // First node of the queue
	Node_t *Last;   // Last node of the queue
	s32 count;  // Number of nodes
} MsQueue_t, *pMsQueue_t;

/************************************************************************/
/*                                                  Functions                                                           */
/************************************************************************/

/** @defgroup Queue management
 * @{
 */

/**
 * @brief Runtime library init.
 * @return void
 */
void SysQueueRtInit(void);


/**
 * @brief Enqueue an element at the end of the specified queue.
 * @param[in] Q the specified queue.
 * @param[in] E the enqueued element.
 * @return QueueErr_e error code.
 */
QueueErr_e SysEnQueue(pMsQueue_t Q, void *E);


/**
 * @brief Enqueue an element by sorting according E.
 * @param[in] Q the specified queue.
 * @param[in] E the enqueued element.
 * @return QueueErr_e error code.
 */
QueueErr_e SysEnQueueBySort(pMsQueue_t Q, void *E);


/**
 * @brief Dequeue the first element of the specified queue.
 * @param[in] Q the specified queue.
 * @return void* the first element.
 */
void *SysDeQueue(pMsQueue_t Q);


/**
 * @brief Dequeue the element with a specified node of the specified queue.
 * @param[in] Q the specified queue.
 * @param[in] E the specified node.
 * @return void* the element.
 */
void *SysDeleteQueue(pMsQueue_t Q, void *E);

/* @} */

#endif // __SYS_SYS_QUEUE_H__

