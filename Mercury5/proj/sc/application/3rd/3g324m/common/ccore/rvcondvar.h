#ifndef _RvCondvar_h
#define _RvCondvar_h

#include "rvsemaphore.h"
#include "rvlock.h"
#include "rvmutex.h"
#include "rvlog.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef struct _RvCondvar {
        RvLock lock;
    RvSemaphore sema;
    RvInt callCount;
} RvCondvar;
    
RVCOREAPI RvStatus RVCALLCONV RvCondvarConstruct(RvCondvar *self, RvLogMgr *log);

RVCOREAPI RvStatus RVCALLCONV RvCondvarDestruct(RvCondvar *self, RvLogMgr *logMgr);

RVCOREAPI RvStatus RVCALLCONV RvCondvarWaitL(RvCondvar *self, RvLock *lock, RvLogMgr *log);

RVCOREAPI RvStatus RVCALLCONV RvCondvarWaitM(RvCondvar *self, RvMutex *mutex, RvLogMgr *log);

RVCOREAPI RvStatus RVCALLCONV RvCondvarBroadcast(RvCondvar *self, RvLogMgr *log);

#if (RV_LOCK_TYPE != RV_LOCK_NONE)
#define RV_CONDVAR_WAITL(cond, condvar, lock, logMgr) \
        while(!(cond)) { \
        RvCondvarWaitL(condvar, lock, logMgr); \
        }; 
#else
#define RV_CONDVAR_WAITL(cond, condvar, lock, logMgr) \
        (void)((void)condvar,(void)lock,(void)logMgr)
#endif  /*#if (RV_LOCK_TYPE != RV_LOCK_NONE)*/
    
#if (RV_MUTEX_TYPE != RV_MUTEX_NONE)   
#define RV_CONDVAR_WAITM(cond, condvar, lock, logMgr) \
    while(!(cond)) { \
    RvCondvarWaitM(condvar, lock, logMgr); \
    }; 
#else    
#define RV_CONDVAR_WAITM(cond, condvar, lock, logMgr) \
    (void)((void)condvar,(void)lock,(void)logMgr)
#endif /*#if (RV_MUTEX_TYPE != RV_MUTEX_NONE)*/
    
    
    
#ifdef __cplusplus
}
#endif
#endif
