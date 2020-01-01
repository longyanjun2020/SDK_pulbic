/* rvadlock.h - rvadlock header file */
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

#ifndef RV_ADLOCK_H
#define RV_ADLOCK_H


#include "rvccore.h"


#if (RV_LOCK_TYPE != RV_LOCK_NONE)

#include "rvadlock_t.h"

#ifdef RV_USE_MACROS
#include "rvad_macros.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct RvLogMgrInternal;

/********************************************************************************************
 * RvAdLockConstruct
 *
 * Called by RvLockConstruct.
 * Create and initialize a non-recursive mutex (lock).
 *
 * INPUT   : None.
 * OUTPUT  : lock - address of the lock object to be constructed
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvAdLockConstruct(
    OUT RvLock*         lock,
    IN  struct RvLogMgrInternal*       logMgr);


/********************************************************************************************
 * RvAdLockDestruct
 *
 * Called by RvLockDestruct.
 * Destruct a lock.
 *
 * INPUT   : lock - address of the lock object to be destructed
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvAdLockDestruct(
    IN  RvLock*         lock,
    IN  struct RvLogMgrInternal*       logMgr);


#ifndef RV_USE_MACROS
/********************************************************************************************
 * RvAdLockGet
 *
 * Called by RvLockGet.
 * Lock a lock.
 *
 * INPUT   : lock - address of the lock object to be locked
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvAdLockGet(
    IN  RvLock*         lock,
    IN  struct RvLogMgrInternal*       logMgr);
#endif /*#ifndef RV_USE_MACROS*/


#ifndef RV_USE_MACROS
/********************************************************************************************
 * RvAdLockRelease
 *
 * Called by RvLockRelease.
 * Release a lock.
 *
 * INPUT   : lock - address of the lock object to be released
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvAdLockRelease(
    IN  RvLock*         lock,
    IN  struct RvLogMgrInternal*       logMgr);
#endif /*#ifndef RV_USE_MACROS*/


/********************************************************************************************
 * RvAdLockSetAttr
 *
 * Called by RvLockSetAttr.
 * Set default options to be used from now on by RvAdLockConstruct.
 *
 * INPUT   : attr - set of options to be saved for future locks construction
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvAdLockSetAttr(
    IN  RvLockAttr*     attr,
    IN  struct RvLogMgrInternal*       logMgr);

#ifdef __cplusplus
}
#endif

#else

typedef RvInt RvLock;     /* Dummy types, used to prevent warnings. */
typedef RvInt RvLockAttr; /* not used */

#endif


#endif
