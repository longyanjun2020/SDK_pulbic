/* rvsemaphore.h - rvsemaphore header file */
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

/**********************************************************************
 *
 *	DESCRIPTION:	
 *		This module provides semaphore functions.
 *
 ***********************************************************************/

#ifndef RV_SEMAPHORE_H
#define RV_SEMAPHORE_H

#include "rvccore.h"
#include "rvadsema4.h"
#include "rvlog.h"

#if !defined(RV_SEMAPHORE_TYPE) || \
   ((RV_SEMAPHORE_TYPE != RV_SEMAPHORE_POSIX)   && (RV_SEMAPHORE_TYPE != RV_SEMAPHORE_VXWORKS) && \
    (RV_SEMAPHORE_TYPE != RV_SEMAPHORE_PSOS)    && (RV_SEMAPHORE_TYPE != RV_SEMAPHORE_OSE)     && \
    (RV_SEMAPHORE_TYPE != RV_SEMAPHORE_NUCLEUS) && (RV_SEMAPHORE_TYPE != RV_SEMAPHORE_WIN32)   && \
    (RV_SEMAPHORE_TYPE != RV_SEMAPHORE_SYMBIAN) && (RV_SEMAPHORE_TYPE != RV_SEMAPHORE_NONE)	   && \
	(RV_SEMAPHORE_TYPE != RV_SEMAPHORE_RTK) && (RV_SEMAPHORE_TYPE != RV_SEMAPHORE_CONDVAR) && (RV_SEMAPHORE_TYPE != RV_SEMAPHORE_OSA))
#error RV_SEMAPHORE_TYPE not set properly
#endif

#if !defined(RV_SEMAPHORE_ATTRIBUTE_DEFAULT)
#error RV_SEMAPHORE_ATTRIBUTE_DEFAULT not set properly
#endif


#if defined(__cplusplus)
extern "C" {
#endif

/* Prototypes and macros */

/********************************************************************************************
 * RvSemaphoreInit - Initializes the Semaphore module.
 *
 * Must be called once (and only once) before any other functions in the module are called.
 *
 * INPUT   : none
 * OUTPUT  : None
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvSemaphoreInit(void);

/********************************************************************************************
 * RvSemaphoreEnd - Shuts down the Semaphore module.
 *
 * Must be called once (and only once) when no further calls to this module will be made.
 *
 * INPUT   : none
 * OUTPUT  : None
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvSemaphoreEnd(void);

/********************************************************************************************
 * RvSemaphoreSourceConstruct - constructs semaphore module log source
 *
 * The semaphore module log source is constructed per log manager instance.
 *
 * INPUT   : logMgr  - log manager instances
 * OUTPUT  : None
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvSemaphoreSourceConstruct(
	IN RvLogMgr* logMgr);


#if (RV_SEMAPHORE_TYPE != RV_SEMAPHORE_NONE)

/********************************************************************************************
 * RvSemaphoreConstruct - Creates a counting semaphore object.
 *
 * note: The maximum value of a sempahore is OS and architecture dependent.
 *
 * INPUT   : statcount	- Initial value of the semaphore.
 *			 logMgr		- log manager instances
 * OUTPUT  : sema		- Pointer to lock object to be constructed.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI 
RvStatus RvSemaphoreConstruct(
	IN  RvUint32	startcount, 
	IN  RvLogMgr	*logMgr, 
	OUT RvSemaphore *sema);


/********************************************************************************************
 * RvSemaphoreDestruct - Destroys a counting semaphore object.
 *
 * note: Never destroy a semaphore object which has a thread suspended on it.
 *
 * INPUT   : sema		- Pointer to semaphore object to be destructed.
 *			 logMgr		- log manager instances
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI 
RvStatus RVCALLCONV RvSemaphoreDestruct(
	IN RvSemaphore	*sema,
	IN RvLogMgr		*logMgr);


/********************************************************************************************
 * RvSemaphorePost - Increments the semaphore.
 *
 * note: The maximum value of a sempahore is OS and architecture dependent.
 *
 * INPUT   : sema		- Pointer to semaphore object to be incremented.
 *			 logMgr		- log manager instances
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI 
RvStatus RvSemaphorePost(
	IN RvSemaphore	*sema,
	IN RvLogMgr		*logMgr);

/********************************************************************************************
 * RvSemaphoreWait - Decrements a semaphore.
 *
 * If the semaphore is 0, it will suspend the calling task until it can.
 *
 * INPUT   : sema		- Pointer to semaphore object to be decremented.
 *			 logMgr		- log manager instances
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI 
RvStatus RvSemaphoreWait(
	IN RvSemaphore	*sema,
	IN RvLogMgr		*logMgr);

/********************************************************************************************
 * RvSemaphoreTryWait - Try to decrement a semaphore.
 *
 * If the semaphore is 0, it will not suspend the calling task. Instead, this function
 * returns RV_ERROR_TRY_AGAIN error code.
 *
 * INPUT   : sema       - Pointer to semaphore object to be decremented.
 *           logMgr     - log manager instances
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI
RvStatus RvSemaphoreTryWait(
    IN RvSemaphore  *sema,
    IN RvLogMgr     *logMgr);


/********************************************************************************************
 * RvSemaphoreSetAttr
 *
 * Sets the options and attributes to be used when creating and using semaphore objects.
 * note: Non-reentrant function. Do not call when other threads may be calling rvsemaphore functions.
 * note: These attributes are global and will effect all semaphore functions called thereafter.
 * note: The default values for these attributes are set in rvccoreconfig.h.
 *
 * INPUT   : attr		- Pointer to OS specific semaphore attributes to begin using.
 *           logMgr		- log manager instances
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI
RvStatus RVCALLCONV RvSemaphoreSetAttr(
	IN RvSemaphoreAttr *attr,
	IN RvLogMgr		   *logMgr);

#else
/* If none is set then none of these functions do anything */
#define RvSemaphoreConstruct(_c,_lg,_s) ((void)(_lg), *(_s) = RV_OK)
#define RvSemaphoreDestruct(_s,_lg) ((void)(_lg), *(_s) = RV_OK)
#define RvSemaphorePost(_s,_lg) ((void)(_lg), *(_s) = RV_OK)
#define RvSemaphoreWait(_s,_lg) ((void)(_lg), *(_s) = RV_OK)
#define RvSemaphoreTryWait(_s,_lg) ((void)(_lg), *(_s) = RV_OK)
#define RvSemaphoreSetAttr(_s,_lg) ((void)(_lg), *(_s) = RV_OK)
#endif


#if defined(__cplusplus)
}
#endif

#endif
