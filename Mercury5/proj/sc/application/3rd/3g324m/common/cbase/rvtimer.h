/* rvtimer.h - rvtimer header file */
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
/* This module provides functions for creating timer events and timer
queues for those events.*/

#ifndef RV_TIMER_H
#define RV_TIMER_H
#include "rvcbase.h"
#include "rvlock.h"
#include "rvsemaphore.h"
#include "rvobjpool.h"
#include "rvpqueue.h"
#include "rvmemory.h"

#ifndef RV_TIMER_TEST_TIMERS
#define RV_TIMER_TEST_TIMERS 0
#endif


/* Error checks to make sure configuration has been done properly */
#if !defined(RV_TIMER_TYPE) || ((RV_TIMER_TYPE != RV_TIMER_STANDARD))
#error RV_TIMER_TYPE not set properly
#endif
/* End of configuration error checks */

/* Module specific error codes (-512..-1023). See rverror.h for more details */
#define RV_TIMER_ERROR_POOL -512         /* Timer event pool error */
#define RV_TIMER_ERROR_PQUEUE -513       /* Timer Priority Queue error */
#define RV_TIMER_ERROR_QUEUEFULL -514    /* Timer queue is full. */
#define RV_TIMER_ERROR_QUEUESTOPPED -515 /* Timer queue has been stopped. */

/* Module specific Warning codes (512..1023). See rverror.h for more details */
#define RV_TIMER_WARNING_BUSY 512       /* Timer callback in progress. */
#define RV_TIMER_WARNING_QUEUEEMPTY 513 /* Timer queue is empty. */


/* Forward declaration for internal structure. */
typedef struct RvTimerEvent_s RvTimerEvent;



/* Used for control the queue processing state */
typedef enum {
	RV_TIMERQUEUE_ENABLED = 0,
	RV_TIMERQUEUE_DISABLED,
    RV_TIMERQUEUE_DELETED
} RvTimerQueueState;


/********************************************************************************************
 * RvTimerQueue
 * A timer queue object.
 ********************************************************************************************/
typedef struct {
	RvPQueue pqueue;		    /* Priority queue for timer events */
	RvObjPool pool;			    /* Pool of free timer events. */
	RvLock lock;			    /* lock for access to timer queue */
	RvSize_t callcount;		    /* Number of callbacks currently in progress. */
	RvSemaphore wait;		    /* Used to block task waiting for all callbacks to complete (QueueStop). */
	RvTimerQueueState qState;	/* queue processing control. */
	void	*selEng;	        /* Select engine */
	RvLogMgr* logMgr;           /* timer queue log manager */
	RvLogSource* timerSource;   /* log source, to be used for the queue module instance */
#if RV_TIMER_TEST_TIMERS
    /* Debugging support fields */
    RvInt lastServiceTime;      /* time of the RvTimerQueueService             */
    RvInt lastDisabled;         /* last time this queue was disabled           */ 
    RvInt lastEnabled;          /* last time this queue was enabled            */  
    void  *lastSId;             /* thread that called last RvTimerQueueService */ 
    void  *lastDId;             /* thread that called last 'disable' on queue  */
    void  *lastEId;             /* thread that called last 'enable' on queue   */
#endif
} RvTimerQueue;



/********************************************************************************************
 * RvTimer
 * A timer identifier. This object is returned when a timer is started
 * and is used only to cancel that timer. It's existance is not requred
 * in order for the timer to trigger. Thus deleting this object has no
 * effect on the timer other then the fact that the timer can no longer
 * be canceled.
 ********************************************************************************************/
typedef struct {
	RvTimerEvent *event;  /* Points to internal timer event. */
	RvUint id;            /* id number of event, used for sanity check. */
} RvTimer;

#define RvTimerIsEqual(t1, t2) ((t1)->event == (t2)->event) && ((t1)->id == (t2)->id)

/* Timer event types. */
/* ONESHOT: standard timer which will go off in the time specificed. */
/* PERIODIC: timer will go off periodically with the time specified being the interval. */
#define RV_TIMER_TYPE_ONESHOT RvIntConst(0)
#define RV_TIMER_TYPE_PERIODIC RvIntConst(1)

/* Timer Event Queue types*/
/*   FIXED: pool and priority queue is fixed size and preallocated. */
/*   EXPANDING: pool increased as needed and heap size is increased by */
/*              a factor of 2 and reallocated when heap is full. */
/*   DYNAMIC: EXPANDING plus pool reduced as needed and heap size is reduced */
/*            by a factor of 2 (min of startsize) when heap only 25% full. */
/*            The freelevel parameter should be set to items free per 100 */
/*            which should be maintained (frelevel = 0 indicates to always */
/*            remove free pages). */
#define RV_TIMER_QTYPE_FIXED RvIntConst(0)
#define RV_TIMER_QTYPE_EXPANDING RvIntConst(1)
#define RV_TIMER_QTYPE_DYNAMIC RvIntConst(2)

/* Flags to indicate direction of value deltas for */
/* RvTimerQueueChangeMaxtimers and RvTimerQueueChangeMintimers */
/* functions. */
#define RV_TIMER_VALUE_INCREASE RV_TRUE
#define RV_TIMER_VALUE_DECREASE RV_FALSE

#if defined(__cplusplus)
extern "C" {
#endif 

/********************************************************************************************
 * RvTimerFunc
 *	
 * purpose: This is the function that should be called when a timer is triggered.
 * INPUT  : data - User parameter that was passed to RvTimerStart.
 * OUTPUT : none
 * RETURN : Return value only affects PERIODIC timers. A return value of RV_TRUE
 *			indicates that the timer should be rescheduled. A value of RV_FALSE
 *			indicates that the timer should not be rescheduled (and is, in effect,
 *			canceled).
 ********************************************************************************************/

typedef RvBool (*RvTimerFunc)(void *);


/********************************************************************************************
 * RvTimerFuncEx
 *	
 * purpose: This is the function that should be called when a timer is triggered.
 * INPUT  : ctx - User parameter that was passed to RvTimerStart.
 *        : timerInfo - information about this timer. Points to the transient (on-stack)
 *          area, so it's accessible only during the call to this function
 *          
 * OUTPUT : none
 * RETURN : Return value only affects PERIODIC timers. A return value of RV_TRUE
 *			indicates that the timer should be rescheduled. A value of RV_FALSE
 *			indicates that the timer should not be rescheduled (and is, in effect,
 *			canceled).
 ********************************************************************************************/

typedef RvBool (*RvTimerFuncEx)(void *ctx, RvTimer *timerInfo);

/********************************************************************************************
									TYPES DEFINITIONS
 ********************************************************************************************/

/* enum types that indicate if RvTimerCancel should wait for the timer's callBack
   to end or not (blocking or non-blocking). */
typedef enum {
	RV_TIMER_CANCEL_WAIT_FOR_CB = 1,
	RV_TIMER_CANCEL_DONT_WAIT_FOR_CB
} RvTimerCancelBehavior;

/********************************************************************************************
									PROTOTYPES
 ********************************************************************************************/

/********************************************************************************************
 * RvTimerInit - Initializes the Timer module.
 *
 * Must be called once (and only once) before any other functions in the module are called.
 *
 * INPUT   : none
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvTimerInit(void);

/********************************************************************************************
 * RvTimerEnd - Shuts down the Timer module.
 *
 * Must be called once (and only once) when no further calls to this module will be made.
 *
 * INPUT   : none
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvTimerEnd(void);

/********************************************************************************************
 * RvTimerSourceConstruct - Constructs timer module log source.
 *
 * Constructs log source to be used by common core when printing log from the 
 * timer module. This function is applied per instance of log manager.
 * 
 * INPUT   : logMgr - log manager instance
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code. 
 */
RvStatus RvTimerSourceConstruct(
	IN RvLogMgr	*logMgr);


/********************************************************************************************
 * RvTimerQueueConstruct - Constructs a timer queue object based on the parameters passed in.
 *
 * There are two parts to each timer queue, the timer pool and the priority queue, both
 * of which require memory. There are three types of pools:
 *			FIXED:  This creates a fixed size timer queue (which contains
 *					a fixed size timer pool and a fixed size priority queue) with
 *					all memory pre-allocated based on the number of starttimers
 *					requested. The number of blocks can be increased with the
 *					RvTimerQueueSetSize and RvTimerQueueAddSize calls.}
 *			EXPANDING: This creates a timer queue pool which expands (by adding
 *					pages and doubling the priority queue size) as needed. The additional
 *					memory is not released until the timer queue is destructed.}
 *			DYNAMIC: This creates a timer queue which expands exactly like
 *					and EXPANDING timer queue but also has the ability to remove
 *					unused pages and reduce the size of the priority queue.
 *					The freelevel value determines when a page should be released.
 *					The priority queue is reduced by 50% when 25% or less of it is
 *					in use.}
 *
 *
 * INPUT   : tqtype		 - Type of timer queue: RV_TIMER_QTYPE_FIXED, 
 *					RV_TIMER_QTYPE_EXPANDING, or RV_TIMER_QTYPE_DYNAMIC.
 *			 starttimers - Number of timers to start with.
 *			 maxtimers   - Never exceed this number of timers.
 *			 mintimers   - Never go below this number of timers.
 *			 freelevel   - The minimum number of free timers per 100 to maintain
 *					in the pool when shrinking a DYNAMIC timer pool (0 to 100).
 *					A value of 0 always releases empty pages and a value of 100
 *					never releases empty pages (which is the same as an EXPANDING
 *					pool).
 *			 pagetimers - Number of timers per memory allocation page in th pool.
 *			 memregion  - Memory region to allocate memory from (NULL = default region).
 *			 selEng		- select engine (RvSelectEngine), used to set/cancel timer
 *			 logMgr		- log manager
 * OUTPUT  : tqueue - Pointer to timer queue object to be constructed.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI 
RvStatus RVCALLCONV RvTimerQueueConstruct( 
	IN  RvInt			tqtype, 
	IN  RvSize_t		starttimers, 
	IN  RvSize_t		maxtimers, 
	IN  RvSize_t		mintimers, 
	IN  RvSize_t		freelevel, 
	IN  RvSize_t		pagetimers, 
	IN  RvMemory		*memregion,
	IN  void			*selEng,
	IN  RvLogMgr		*logMgr,
	OUT RvTimerQueue	*tqueue);


/********************************************************************************************
 * RvTimerQueueControl - Stops/Resumes a timer queue.
 *
 * Stops or resumes processing of the timer queue.
 *
 * INPUT   : tqueue - Pointer to timer queue object to be stopped.
 *           qState - Indicates whether this is a permanent or temporary stop.
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI
RvStatus RVCALLCONV RvTimerQueueControl(
    IN RvTimerQueue         *tqueue,
    IN RvTimerQueueState    qState);


/********************************************************************************************
 * RvTimerQueueSetLogMgr - Update the log manager of a timer queue.
 *
 * INPUT   : tqueue - Pointer to the timer queue object.
 *           logMgr - log manager
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI
RvStatus RVCALLCONV RvTimerQueueSetLogMgr(
    IN RvTimerQueue     *tqueue,
    IN  RvLogMgr        *logMgr);


/********************************************************************************************
 * RvTimerQueueNumEvents - Find out how many events are in the timer queue.
 *
 *
 * INPUT   : tqueue - Pointer to timer queue object to be checked.
 * OUTPUT  : none
 * RETURN  : Number of events currently in the timer queue.
 */
RVCOREAPI
RvSize_t RVCALLCONV RvTimerQueueNumEvents(
	IN RvTimerQueue *tqueue);


/********************************************************************************************
 * RvTimerQueueNumEvents - Find out the maximum concurrent timers in the timer queue.
 *
 *
 * INPUT   : tqueue - Pointer to timer queue object to be checked.
 * OUTPUT  : none
 * RETURN  : Number of maximum concurrent events in the timer queue.
 */
RVCOREAPI
RvSize_t RVCALLCONV RvTimerQueueMaxConcurrentEvents(
    IN RvTimerQueue *tqueue);


/********************************************************************************************
 * RvTimerQueueTimersCreated - Find out how many timers were 
 *                             created in the timer queue.
 *
 * INPUT   : tqueue - Pointer to timer queue object to be checked.
 * OUTPUT  : none
 * RETURN  : Number of timer created in the timer queue.
 */
RVCOREAPI
RvSize_t RVCALLCONV RvTimerQueueTimersCreated(
    IN RvTimerQueue *tqueue);


/********************************************************************************************
 * RvTimerQueueGetSize - Find the current total size of the timer queue.
 *
 *
 * INPUT   : tqueue - Pointer to timer queue object to be checked.
 * OUTPUT  : none
 * RETURN  : Number of timers in the timer queue pool.
 */
RVCOREAPI 
RvSize_t RVCALLCONV RvTimerQueueGetSize(
	IN RvTimerQueue *tqueue);


/********************************************************************************************
 * RvTimerQueueSetSize - Set the total size of the timer queue.
 *
 * The size may only be increased over its current value.
 * The actual number of timers may be larger than that requested since
 * the amount added will be a multiple of the number of timers per
 * page that was set when the timer queue was constructed. The value
 * returned will be the actual new number of timers available.
 * Changes are subject to the limits of the maxtimers and mintimers settings.
 *
 * INPUT   : tqueue  - Pointer to timer queue object to be set.
 *			 newsize - New size that the timer queue should be set to.
 * OUTPUT  : none
 * RETURN  : Number of timers in the timer queue pool.
 */
RVCOREAPI
RvSize_t RVCALLCONV RvTimerQueueSetSize(
	IN RvTimerQueue *tqueue, 
	IN RvSize_t		newsize);


/********************************************************************************************
 * RvTimerQueueAddSize - Adds to the total size of the timer queue.
 *
 * The actual number of timers may be larger than that requested since
 * the amount added will be a multiple of the number of timers per
 * page that was set when the timer queue was constructed. The value
 * returned will be the actual new number of timers that was added.
 * Changes are subject to the limits of the maxtimers setting.
 *
 * INPUT   : tqueue  - Pointer to timer queue object to be set.
 *			 newsize - New size that the timer queue should be set to.
 * OUTPUT  : none
 * RETURN  : Actual number of timers added to the timer queue pool.
 */
RVCOREAPI 
RvSize_t RVCALLCONV RvTimerQueueAddSize(
	IN RvTimerQueue *tqueue, 
	IN RvSize_t		addsize);


/********************************************************************************************
 * RvTimerQueueGetMaxtimers - Returns current value for maxtimers (not used by FIXED queues)
 *
 * INPUT   : tqueue  - Pointer to timer queue object.
 * OUTPUT  : none
 * RETURN  : current value for maxtimers.
 */
RVCOREAPI
RvSize_t RVCALLCONV RvTimerQueueGetMaxtimers(
	IN RvTimerQueue *tqueue);


/********************************************************************************************
 * RvTimerQueueSetMaxtimers - Sets the value for maxtimers (not used by FIXED queues).
 *
 * INPUT   : tqueue    - Pointer to timer queue object.
 *			 maxtimers - new value for maxtimers
 * OUTPUT  : none
 * RETURN  : Returns RV_TRUE upon success (otherwise RV_FALSE).
 */
RVCOREAPI
RvBool RVCALLCONV RvTimerQueueSetMaxtimers(
	IN RvTimerQueue *tqueue, 
	IN RvSize_t		maxtimers);

/********************************************************************************************
 * RvTimerQueueChangeMaxtimers - Changes the value for maxtimers (not used by FIXED queues)
 *
 * INPUT   : tqueue    - Pointer to timer queue object.
 *			 delta	   - change value
 *			 direction - RV_TIMER_VALUE_DECREASE or RV_TIMER_VALUE_INCREASE
 * OUTPUT  : none
 * RETURN  : Returns RV_TRUE upon success (otherwise RV_FALSE).
 */
RVCOREAPI
RvBool RVCALLCONV RvTimerQueueChangeMaxtimers(
	IN RvTimerQueue *tqueue, 
	IN RvSize_t		delta, 
	IN RvBool		direction);


/********************************************************************************************
 * RvTimerQueueGetMintimers - Returns current value for mintimers (not used by FIXED).
 *
 * INPUT   : tqueue    - Pointer to timer queue object.
 * OUTPUT  : none
 * RETURN  : current value for mintimers 
 */
RVCOREAPI
RvSize_t RVCALLCONV RvTimerQueueGetMintimers(
	IN RvTimerQueue *tqueue);


/********************************************************************************************
 * RvTimerQueueSetMinTimers - Sets the minimum size of the timer queue.
 *
 * This setting is not ususally used by FIXED pools since they are limited
 * by their actual size. Increasing a fixed pool minimum beyond its current
 * size will use more memory but not add any timers.
 * 
 * INPUT   : tqueue    - Pointer to timer queue object to be set.
 *			 mintimers - New setting for minimum number of timers.
 * OUTPUT  : none
 * RETURN  : Returns RV_TRUE upon success (otherwise RV_FALSE).
 */
RVCOREAPI
RvBool RVCALLCONV RvTimerQueueSetMintimers(
	IN RvTimerQueue *tqueue, 
	IN RvSize_t		mintimers);


/********************************************************************************************
 * RvTimerQueueChangeMinTimers - Changes the minimum size of the timer queue.
 *
 * This setting is not ususally used by FIXED pools since they are limited
 * by their actual size. Increasing a fixed pool minimum beyond its current
 * size will use more memory but not add any timers.
 * 
 * INPUT   : tqueue    - Pointer to timer queue object to be changed.
 *			 delta     - The amount to change the mintimer value by.
 *			 direction - irection to change value, either RV_TIMER_VALUE_INCREASE or
 *					RV_TIMER_VALUE_DECREASE
 * OUTPUT  : none
 * RETURN  : Returns RV_TRUE upon success (otherwise RV_FALSE).
 */
RVCOREAPI
RvBool RVCALLCONV RvTimerQueueChangeMintimers(
	IN RvTimerQueue *tqueue, 
	IN RvSize_t		delta, 
	IN RvBool		direction);


/********************************************************************************************
 * RvTimerQueueGetFreelevel - Find the current freelevel of the timer queue.
 *
 * This setting is only used by DYNAMIC timer queues.
 * 
 * INPUT   : tqueue    - Pointer to timer queue object to be checked.
 * OUTPUT  : none
 * RETURN  : Value of the freevalue setting for timer queue pool.
 */
RVCOREAPI
RvSize_t RVCALLCONV RvTimerQueueGetFreelevel(
	IN RvTimerQueue *tqueue);


/********************************************************************************************
 * RvTimerQueueSetFreelevel - Sets the current freelevel of the timer queue.
 *
 * This is the minimum number
 * of free timers per 100 to maintain in the pool when shrinking a DYNAMIC
 * timer pool (0 to 100). A value of 0 always releases empty pages and a
 * value of 100 never releases empty pages (which is the same as an EXPANDING
 * pool).
 * This setting is only used by DYNAMIC timer queues.
 * 
 * INPUT   : tqueue    - Pointer to timer queue object to be set.
 *			 freelevel - New freelevel value to set (0 to 100).
 * OUTPUT  : none
 * RETURN  : Returns RV_TRUE if successful, otherwise RV_FALSE.
 */
RVCOREAPI
RvBool RVCALLCONV RvTimerQueueSetFreelevel(
	IN RvTimerQueue *tqueue, 
	IN RvSize_t		freelevel);


/********************************************************************************************
 * RvTimerQueueNextEvent - Returns the number of nanoseconds until the next timer is supposed
 * to be triggered.
 *
 * This is the minimum number
 * of free timers per 100 to maintain in the pool when shrinking a DYNAMIC
 * timer pool (0 to 100). A value of 0 always releases empty pages and a
 * value of 100 never releases empty pages (which is the same as an EXPANDING
 * pool).
 * This setting is only used by DYNAMIC timer queues.
 * The value of nextevent may be negative if the next event is overdue.
 * 
 * INPUT   : tqueue    - Pointer to timer queue object to be checked.
 * OUTPUT  : nextevent - Pointer to location to store the nanoseconds until the next event.
 * RETURN  : RV_OK if successful otherwise an error code. A warning of RV_TIMER_WARNING_QUEUEEMPTY
 *			will be returned if there are no events in the timer queue.
 */
RVCOREAPI 
RvStatus RVCALLCONV RvTimerQueueNextEvent(
	IN  RvTimerQueue	*tqueue, 
	OUT RvInt64			*nextevent);


/********************************************************************************************
 * RvTimerQueueDestruct - Destructs a timer queue.
 *
 * All timers in the queue are lost when the timer queue is destructed.
 * Insure that no threads are adding timers or servicing timers on the
 * timer queue when it is destructing since not all operating systems
 * handle the situation gracefully.
 * This function may only be called once on each timer queue. Thus
 * it may not be called simultaneously from multiple threads (with the
 * same timer queue to destruct).
 * 
 * INPUT   : tqueue    - Pointer to timer queue object to be Destructed.
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI 
RvStatus RVCALLCONV RvTimerQueueDestruct(
	IN RvTimerQueue *tqueue);


/********************************************************************************************
 * RvTimerStart - Creates and schedules a timer event.
 *
 * There are two type of timers, ONESHOT and PERIDOC.
 * A ONESHOT timer will trigger only once, at the requested time. A PERIODIC timer will
 * triggered repeatedly until it is canceled with a call to RvTimerCancel or by the
 * callback returning a value of RV_FALSE.
 * note:  There is no construct or destruct calls for the RvTimer type. It is simply used as
 *		an identifier for the timer event so that it may be canceled. The RvTimer structure
 *		is not required in order for the timer event to trigger and not keeping that
 *		structure around in no way effects the operation of the timer other then leaving
 *		no way to cancel the timer event. Also, the timer parameter may be NULL, which
 *		simply starts a timer without returning the information needed to cancel it.
 * note:  The actual accuracy of the timer is dependent upon a number of things including
 *		the resolution of the timestamp clock, the rate and priority of the thread
 * 		servicing the timer queue, and the cpu load of the system.
 *
 * INPUT  : timer		- Pointer to timer object which will be filled in with information
 *						needed to indentify the event.
 *			tqueue		- Pointer to timer queue object where timer should be scheduled.
 *			timertype	- Type of timer: RV_TIMER_TYPE_ONESHOT or RV_TIMER_TYPE_PERIODIC.
 *			delay		- Time until timer should be triggered, in nanoseconds.
 *			callback	- Function to be called when the timer is triggered.
 *			userdata	- Pointer that will be passed to the callback function when triggered.
 * OUTPUT  : none
 * RETURN  : returns: RV_OK if successful otherwise an error code.
 */
RVCOREAPI 
RvStatus RVCALLCONV RvTimerStartEx(
	IN RvTimer		*timer, 
	IN RvTimerQueue	*tqueue, 
	IN RvInt		timertype, 
	IN RvInt64		delay, 
	IN RvTimerFuncEx	callback,
	IN void			*userdata);

#define RvTimerStart(timer, queue, timertype, delay, cb, ctx) \
  RvTimerStartEx(timer, queue, timertype, delay, (RvTimerFuncEx)(cb), ctx)

#define RvTimerConstruct(timer) ((timer)->event = 0)
#define RvTimerDestruct(timer) ((timer)->event = 0) 

#define RV_TIMER_CLEAR(timer) ((timer)->event = 0)


/********************************************************************************************
 * RvTimerCancel - Cancels a timer event.
 * 
 * This function has two slightly different behaviours
 * depending on how the blocking parameter is set:
 *			RV_TIMER_CANCEL_WAIT_FOR_CB: The timer event is guaranteed to be canceled
 * 					when the function returns. If the timer event was is the middle of
 *					being triggered, this function will suspend the calling thread until
 *					the callback is completed.
 *			RV_TIMER_CANCEL_DONT_WAIT_FOR_CB: The timer event is canceled if it is
 *					not currently in the middle of being triggered. If the timer event
 *					was is the middle of being triggered a return warning value of
 *					RV_TIMER_WARNING_BUSY is returned. PERIODIC timers will have future
 *					triggers canceled so that the trigger currently in progress will be
 *					the last one.
 *	note:	Do not cancel a timer that was scheduled on a timer queue that has been destructed.
 *			Destructing the timer queue automatically cancels and destroys all timers.
 *	note:	Never call RvTimerCancel with behaviour set to RV_TIMER_CANCEL_WAIT_FOR_CB from
 *			inside of that timers callback. It really should not be necessary to call it
 *			at all from within its callback.
 *
 * INPUT   : timer		- Pointer to timer object which identifies the event to cancel.
 *			 behaviour	- Behaviour of cancel: RV_TIMER_CANCEL_WAIT_FOR_CB, RV_TIMER_CANCEL_DONT_WAIT_FOR_CB.
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code. May also return RV_TIMER_WARNING_BUSY
 *			if blocking is set to RV_TIMER_CANCEL_DONT_WAIT_FOR_CB.
 */
RVCOREAPI 
RvStatus RVCALLCONV RvTimerCancel(
	IN RvTimer					*timer,
	IN RvTimerCancelBehavior	behaviour);


/********************************************************************************************
 * RvTimerGetRemainingTime - Returns the time left until the timer is expired.
 *
 * INPUT   : timer      - Pointer to timer object.
 * OUTPUT  : delay      - Pointer to a 64-bit variable where the remaining time value will
 *                        be stored.
 * RETURN  : returns: RV_OK if successful otherwise an error code.
 */
RVCOREAPI
RvStatus RVCALLCONV RvTimerGetRemainingTime(
    IN  RvTimer     *timer,
    OUT RvInt64     *delay);


/********************************************************************************************
 * RvTimerResolution - Gets the resolution of the clock used by timers, in nanoseconds.
 * 
 * INPUT   : none
 * OUTPUT  : logMgr - log manager instance
 * RETURN  : Resolution of the timer clock, in nanoseconds.
 */
RVCOREAPI
RvInt64 RVCALLCONV RvTimerResolution(
	RvLogMgr *logMgr);

/********************************************************************************************
 * RvTimerQueueService - Checks a timer queue and executes events that should be triggered.
 * 
 * INPUT   : tqueue		- Pointer to timer queue object to be serviced.
 * 			 maxevents	- Maximum number of events that should be executed.
 *			 numevents	- Pointer to variable where the number of events 
 *					actually executed will be stored.
 *			 alternativeCb - used in stacks where some actions should be applied
 *					before executing defined for the time-out callbacks. Specifically
 *					if stack wishes to notify other thread about time-out event instead 
 *					of processing time-out events by the current thread.
 *			 alternativeCbContext - alternative callback user data
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code. An error of RV_TIMER_ERROR_QUEUESTOPPED
 *			will be returned if the queue hass been stopped (with the RvTimerQueueStop function).
 */
RVCOREAPI RvStatus RVCALLCONV RvTimerQueueService(
	IN RvTimerQueue *tqueue, 
	IN RvSize_t		maxevents, 
	IN RvSize_t		*numevents,
	IN RvTimerFunc	alternativeCb,
	IN void			*alternativeCbContext);



#if RV_TIMER_TEST_TIMERS

/* Debugging routine */

typedef void (*RvFprint)(void *ctx, RvChar *format,...);

RVCOREAPI 
void RvTimerTestTimers(RvTimerQueue *tq, RvFprint pf, void *pfCtx);

#endif
    

#if defined(__cplusplus)
}
#endif 

#endif
