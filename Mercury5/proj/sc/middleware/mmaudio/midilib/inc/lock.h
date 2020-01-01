#if ! defined( common_lock_h )
#define common_lock_h
/*****************************************************************************/
/* common_lock_h                                                             */
/* lock.h                                                                    */
/* 2007/08                                                                   */
/* Copyright 2007 FAITH,INC.                                                 */
/* H.M.                                                                      */
/*****************************************************************************/

#if 1

#define LOCKCREATE(XX)
#define LOCKDESTROY(XX)
#define LOCK(XX)
#define UNLOCK(XX)
#define CRITICALSECTION_CREATE()	0
#define CRITICALSECTION_DESTROY(XX)
#define CRITICALSECTION_IN(XX)
#define CRITICALSECTION_OUT(XX)

#else
extern
void
LOCKCREATE(
    void** pmutex
);

extern
void
LOCKDESTROY(
    void *mutex
);

extern
void
LOCK(
    void * mutex
);

extern
void
UNLOCK(
    void * mutex
);

/*****************************************************************************/

extern
void *
CRITICALSECTION_CREATE(
    void
);

extern
void
CRITICALSECTION_DESTROY(
    void *pcs
);

extern
void
CRITICALSECTION_IN(
    void *pcs
);

extern
void
CRITICALSECTION_OUT(
    void *pcs
);

#endif
/*****************************************************************************/
#endif  /* ! defined( common_lock_h ) */
