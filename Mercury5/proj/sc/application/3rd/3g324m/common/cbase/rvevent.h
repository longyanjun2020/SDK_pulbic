/* rvevent.h - rvevent header file */
/************************************************************************
      Copyright (c) 2001-2006 RADVISION Inc. and RADVISION Ltd.
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
 *		This module provides routines for manipulating events objects
 *
 ***********************************************************************/
#ifndef _rvevent_h_
#define _rvevent_h_
#include "rvsemaphore.h"
    
typedef struct RvEventSleepingChannel_s {
    RvSemaphore iSleepingChSema;
    struct RvEventSleepingChannel_s *iSleepingChNext;
} RvEventSleepingChannel;


typedef struct {
#ifdef RV_DEBUG_EVENT
    RvUint iChCounter;
#endif        
    RvEventSleepingChannel *iSleepingChannel;
} RvEvent;

/********************************************************************************************
 * RvEventConstruct - Constructs the event object
 *
 * INOUT   : event	- Pointer to event object to be constructed.
 *                    The event object does not need to be destructed.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI RvStatus RvEventConstruct(INOUT RvEvent* event);

/********************************************************************************************
 * RvEventPulse - Pulses the event object causing all threads waiting on this event object to 
 *                continue. The access to event object has to be protected b 'lock'. If the 'lock'
 *                argument points to valid lock object this lock will be used to protect the access
 *                to event. If 'lock' is NULL it is responsibility of the caller to protect the event
 *                object.
 *
 * IN   : event	- Pointer to event object to be constructed.
 *        lock - Points to valid lock object or NULL.
 *        logMgr - the log manager
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI RvStatus RvEventPulse(IN RvEvent* event, IN RvLock* lock, IN RvLogMgr *logMgr);

/********************************************************************************************
 * RvEventWait - Blocks the calling thread until the event is pulsed by some other thread.
 *               It is supposed that RvEventWait is called when the 'lock' was locked. 
 *               The function will set up waiting thread and then unlock the 'lock' for 
 *               actual waiting. When the function returns it is gurantedd that the 'lock' is locked
 *               again.
 *
 * IN   : event	- Pointer to event object to be constructed.
 *        lock - Points to valid lock object.
 *        logMgr - the log manager
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI RvStatus RvEventWait(IN RvEvent* event, IN RvLock* lock, IN RvLogMgr *logMgr);

#define RvEventNoWaiters(_event) (((_event)->iSleepingChannel==NULL)?RV_TRUE:RV_FALSE)

#endif
