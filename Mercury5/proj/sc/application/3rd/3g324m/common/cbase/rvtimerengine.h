/***********************************************************************
Filename   : rvtimerengine.h
Description: rvtimerengine header file
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
This module provides functions for creating "engines" to service
timer queues. Each "engine" consists is a threads which	will
periodically service a given timer queue.
More that one timer engine may service the same timer queue.
***********************************************************************/
  
#ifndef RV_TIMERENGINE_H
#define RV_TIMERENGINE_H

#include "rvcbase.h"
#include "rvtimer.h"
#include "rvthread.h"

/* Error checks to make sure configuration has been done properly */
#if !defined(RV_TIMERENGINE_TYPE) || ((RV_TIMERENGINE_TYPE != RV_TIMERENGINE_STANDARD))
#error RV_TIMERENGINE_TYPE not set properly
#endif
/* End of configuration error checks */

/* Module specific error codes (-512..-1023). See rverror.h for more details */

/* Module specific Warning codes (512..1023). See rverror.h for more details */

/*******************************************************************************************
 * RvTimerEngine -  A timerengine object.
 * There is no locking. The stopped and paused variables are the only info
 * modified between tasks so they must be monotonic.
 *******************************************************************************************/
typedef struct {
	RvInt64 period;       /* Interval at which queue should be serviced. */
	RvBool stopped;       /* Set to RV_TRUE to stop Engine (RV_FALSE while running). */
	RvBool paused;        /* Set to RV_TRUE to pause Engine (RV_FALSE while running). */
	RvTimerQueue *tqueue; /* Timer queue to service. */
	RvThread thread;      /* Thread engine is running in. */
} RvTimerEngine;

#if defined(__cplusplus)
extern "C" {
#endif 

/* Prototypes: See documentation blocks below for details. */

/********************************************************************************************
 * RvTimerEngineInit
 *
 * Initializes the TimerEngine module. Must be called once (and
 * only once) before any other functions in the module are called.
 * INPUT   : none
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvTimerEngineInit(void);

/********************************************************************************************
 * RvTimerEngineEnd
 *
 * Shuts down the TimerEngine module. Must be called once (and
 * only once) when no further calls to this module will be made.
 * INPUT   : none
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvTimerEngineEnd(void);

/********************************************************************************************
 * RvTimerEngineConstruct
 *
 * Constructs a timer engine based on the parameters passed in.
 * INPUT   : tengine - Pointer to timer engine object to be constructed.
 *           tqueue - Pointer to timer queue object that needs to be serviced.
 *           period - Rate (in nanoseconds) at which timer should be serviced.
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 * NOTE    : The configuration of the timer engine thread will use the RvThread default
 *			 settings. To change the thread configuration, use the RvTimerEngineSetOptions
 *			 function before starting the engine.
 *		     The actual period at which the timer queue is serviced may not be precisely
 *			 the period requested. The acutal period will depend on the resolution and
 *			 acuracy of the operatings systems schedular.
 */
RVCOREAPI RvStatus RVCALLCONV RvTimerEngineConstruct(
    IN RvTimerEngine *tengine, 
    IN RvTimerQueue *tqueue, 
    IN RvInt64 period);

/********************************************************************************************
 * RvTimerEngineDestruct
 *
 * Destructs a timer engine.
 * INPUT   : tengine - Pointer to timer engine object to be Destructed.
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 * NOTE    : RvTimerEngineDestruct may only be called once on each timer engine.
 *			 Thus it may not be called simultaneously from multiple threads (with
 *			 the same timer engine to destruct).}
 *		     This function will suspend the calling thread until the timer engine
 *			 completes any callbacks that are in progess and until the timer engine
 *			 (and associated thread) is completely shut down.
 */
RVCOREAPI RvStatus RVCALLCONV RvTimerEngineDestruct(
    IN RvTimerEngine *tengine);

/********************************************************************************************
 * RvTimerEngineSetOptions
 *
 * Sets the thread configuration for the thread of a timer engine. For more information
 * about these options, refer to the documentation for the Thread module.
 * INPUT   : tengine - Pointer to timer engine object to set thread configuration for.
 *           name - Pointer to string which constains the thread name.
 *           stackaddr - Address of memory to use for stack (NULL means to allocate it).
 *           stacksize - Size of the stack.
 *           priority - Priority to set thread to.
 *           attr - Pointer to OS speicific thread attributes to use (NULL = use defaults).
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 * NOTE    : A copy of the name string passed in is made. The maximum size of the
 *           the string is RV_THREAD_MAX_NAMESIZE and names that are too long
 *           will be truncated.
 *           If stackaddr is set to NULL, the amount of stack space used for internal overhead
 *           will be allocated in addition to the requested stack size.
 *           If stackaddr is set to NULL and the stacksize is set to 0, the default
 *           stack settings will be used (see rvccoreconfig.h).
 *           The default values for the thread attributes are set in rvccoreconfig.h.
 *           Further information about these attributes can be found in that file and
 *           the rvthread.h file.
 *           Once the timer engine is started, these options can not be changed.
 */
RVCOREAPI RvStatus RVCALLCONV RvTimerEngineSetOptions(
    IN RvTimerEngine *tengine, 
    IN RvChar *name, 
    IN void *stackaddr, 
    IN RvInt32 stacksize, 
    IN RvInt32 priority, 
    IN RvThreadAttr *attr);

/********************************************************************************************
 * RvTimerEngineStart
 *
 * Starts a timer engine.
 * INPUT   : tengine - Pointer to timer engine object to be started.
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 * NOTE    : This function can only be called once for each timer engine.
 */
RVCOREAPI RvStatus RVCALLCONV RvTimerEngineStart(
    IN RvTimerEngine *tengine);

/********************************************************************************************
 * RvTimerEngineStop
 *
 * Stops a timer engine.
 * INPUT   : tengine - Pointer to timer engine object to be stopped.
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 * NOTE    : This function can only be called once for each timer engine.
 *           Callbacks currently in progress will be completed and the timer
 *           engine thread will exit, however, the RvTimerEngineStop call
 *           will not wait for this to happen.
 */
RVCOREAPI RvStatus RVCALLCONV RvTimerEngineStop(
    IN RvTimerEngine *tengine);

/********************************************************************************************
 * RvTimerEnginePause
 *
 * Pauses a timer engine.
 * INPUT   : tengine - Pointer to timer engine object to be paused.
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 * NOTE    : Callbacks currently in progress will be completed 
 */
RvStatus RvTimerEnginePause(
    IN RvTimerEngine *tengine);

/********************************************************************************************
 * RvTimerEngineResume
 *
 * Resumes a paused timer engine.
 * INPUT   : tengine - Pointer to timer engine object to be resumed.
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 * NOTE    : When a timer engine resumes, timer events that were supposed to
 *			 happen while the timer engine was paused will not be lost. They
 *			 will be triggered and soon as the timer engine resumes.
 */
RvStatus RvTimerEngineResume(
    IN RvTimerEngine *tengine);


#if defined(__cplusplus)
}
#endif 

#endif
