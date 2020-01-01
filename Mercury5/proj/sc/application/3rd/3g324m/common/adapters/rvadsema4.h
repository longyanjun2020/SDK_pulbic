/* rvadsema4.h - rvadsema4 header file */
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

#ifndef RV_ADSEMA4_H
#define RV_ADSEMA4_H


#include "rvccore.h"


#if (RV_SEMAPHORE_TYPE != RV_SEMAPHORE_NONE)

#include "rvadsema4_t.h"
#include "rvlog.h"


#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************
 * RvAdSema4Construct
 *
 * Called by RvSemaphoreConstruct.
 * Create and initialize a semaphore.
 *
 * INPUT   : None.
 * OUTPUT  : sema - address of the semaphore object to be constructed
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvAdSema4Construct(
    OUT RvSemaphore*    sema,
    IN  RvUint32        startcount,
    IN  RvLogMgr*       logMgr);


/********************************************************************************************
 * RvAdSema4Destruct
 *
 * Called by RvSemaphoreDestruct.
 * Destruct a semaphore.
 *
 * INPUT   : sema - address of the semaphore object to be destructed
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvAdSema4Destruct(
    IN  RvSemaphore*    sema,
    IN  RvLogMgr*       logMgr);


/********************************************************************************************
 * RvAdSema4Post
 *
 * Called by RvSemaphorePost.
 * Release a semaphore token.
 *
 * INPUT   : sema - address of the semaphore object to be released
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvAdSema4Post(
    IN  RvSemaphore*    sema,
    IN  RvLogMgr*       logMgr);


/********************************************************************************************
 * RvAdSema4Wait
 *
 * Called by RvSemaphoreWait.
 * Acquire a semaphore token.
 *
 * INPUT   : sema - address of the semaphore object to be acquired
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvAdSema4Wait(
    IN  RvSemaphore*    sema,
    IN  RvLogMgr*       logMgr);


/********************************************************************************************
 * RvAdSema4TryWait
 *
 * Called by RvSemaphoreTryWait.
 * Try to acquire a semaphore token.
 * If the semaphore is not available - returns immediately with RV_ERROR_TRY_AGAIN status.
 *
 * INPUT   : sema - address of the semaphore object to be acquired
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvAdSema4TryWait(
    IN  RvSemaphore*    sema,
    IN  RvLogMgr*       logMgr);


/********************************************************************************************
 * RvAdSema4SetAttr
 *
 * Called by RvSemaphoreSetAttr.
 * Set default options to be used from now on by RvAdSema4Construct.
 *
 * INPUT   : attr - set of options to be saved for future semaphores construction
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvAdSema4SetAttr(
    IN  RvSemaphoreAttr*attr,
    IN  RvLogMgr*       logMgr);

#ifdef __cplusplus
}
#endif


#else

typedef RvInt RvSemaphore;     /* Dummy types, used to prevent warnings. */
typedef RvInt RvSemaphoreAttr; /* not used */

#endif


#endif
