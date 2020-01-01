/* rvadmutex_macros.h - rvadmutex_macros header file */
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

#ifndef RV_AD_MACROS_H
#define RV_AD_MACROS_H

#ifdef RV_USE_MACROS

#include "rvadmutex.h"
#include "rvadlock_t.h"

struct RvLogMgrInternal;

RVINLINE RvStatus RvAdMutexLock(
                        IN  RvMutex*                  mu,
                        IN  struct RvLogMgrInternal*  logMgr)
{
    RV_UNUSED_ARG(logMgr);
    if(pthread_mutex_lock(&mu->mtx) != 0)
        return RV_ERROR_UNKNOWN;
    mu->count++;
    return RV_OK;
}

RVINLINE RvStatus RvAdMutexUnlock(
                        IN  RvMutex*   mu,
                        IN  struct RvLogMgrInternal*  logMgr)
{
    RV_UNUSED_ARG(logMgr);

    mu->count--;

    if(pthread_mutex_unlock(&mu->mtx) != 0)
        return RV_ERROR_UNKNOWN;

    return RV_OK;
}

RVINLINE RvStatus RvAdLockGet(
                        IN  RvLock*                   lock,
                        IN  struct RvLogMgrInternal*  logMgr)
{
    RV_UNUSED_ARG(logMgr);

    if(pthread_mutex_lock(lock) != 0)
        return RV_ERROR_UNKNOWN;

    return RV_OK;
}


RVINLINE RvStatus RvAdLockRelease(
                        IN  RvLock*                   lock,
                        IN  struct RvLogMgrInternal*  logMgr)
{
    RV_UNUSED_ARG(logMgr);

    if(pthread_mutex_unlock(lock) != 0)
        return RV_ERROR_UNKNOWN;

    return RV_OK;
}


#endif /* #ifdef RV_USE_MACROS */
#endif /* #ifndef RV_AD_MACROS_H */
