/* rvadmutex.h - rvadmutex header file */
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

#ifndef RV_ADMUTEX_H
#define RV_ADMUTEX_H


#include "rvccore.h"


#if (RV_MUTEX_TYPE != RV_MUTEX_NONE)

#include "rvadmutex_t.h"


typedef struct {
	RvAdMutex   mtx;
	RvInt32    count;
#if defined(RV_MUTEX_DEBUG)
    const RvChar    *filename;
    RvInt           lineno;
#endif
} RvMutex;


#ifdef RV_USE_MACROS
#include "rvad_macros.h"
#endif

struct RvLogMgrInternal;

/********************************************************************************************
 * RvAdMutexConstruct
 *
 * Called by RvMutexConstruct.
 * Create and initialize a mutex.
 *
 * INPUT   : None.
 * OUTPUT  : mu - address of the mutex object to be constructed
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvAdMutexConstruct(
    OUT RvMutex*                  mu,
    IN  struct RvLogMgrInternal*  logMgr);


/********************************************************************************************
 * RvAdMutexDestruct
 *
 * Called by RvMutexDestruct.
 * Destruct a mutex.
 *
 * INPUT   : mu - address of the mutex object to be destructed
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvAdMutexDestruct(
    IN  RvMutex*                  mu,
    IN  struct RvLogMgrInternal*  logMgr);


#ifndef RV_USE_MACROS
/********************************************************************************************
 * RvAdMutexLock
 *
 * Called by RvMutexLock.
 * Lock a mutex.
 *
 * INPUT   : mu - address of the mutex object to be locked
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvAdMutexLock(
    IN  RvMutex*                  mu,
    IN  struct RvLogMgrInternal*  logMgr);
#endif /*#ifndef RV_USE_MACROS*/

#ifndef RV_USE_MACROS
/********************************************************************************************
 * RvAdMutexUnlock
 *
 * Called by RvMutexUnlock.
 * Release a mutex.
 *
 * INPUT   : mu - address of the mutex object to be released
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvAdMutexUnlock(
    IN  RvMutex*                  mu,
    IN  struct RvLogMgrInternal*  logMgr);
#endif /*#ifndef RV_USE_MACROS*/


/********************************************************************************************
 * RvAdMutexSetAttr
 *
 * Called by RvMutexSetAttr.
 * Set default options to be used from now on by RvAdMutexConstruct.
 *
 * INPUT   : attr - set of options to be saved for future mutexes construction
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvAdMutexSetAttr(
    IN  RvMutexAttr*              attr,
    IN  struct RvLogMgrInternal*  logMgr);


#else

typedef RvInt RvMutex;     /* Dummy types, used to prevent warnings. */
typedef RvInt RvMutexAttr; /* not used */

#endif


#endif
