#ifndef _rv_ccoreglobals_h_
#define _rv_ccoreglobals_h_

#include "rvglobalindexes.h"
#include "rvglobals.h"


#include "rvlock.h"
#include "rvthread.h"
#include "rvmutex.h"
#include "rvmemory.h"
#include "rvalloc.h"
#include "rvaddress.h"


/********************************************************************************************
 * RvCCoreInitializeGlobals
 * 
 * Creates and initializes the global data structure of common core
 *
 * INPUT   :  
 *           indx - the index of the global data structure (always RV_CCORE_GLOBALS_INDEX)
 *           usrData - not used
 *           
 * OUTPUT  : None.
 * RETURN  : the data pointer of NULL if fails
 */
void* RvCCoreInitializeGlobals(int index, void* usrData);

/********************************************************************************************
 * RvCCoreDestroyGlobals
 * 
 * Destroys the global data structure of common core
 *
 * INPUT   :  
 *           indx - the index of the global data structure (always RV_CCORE_GLOBALS_INDEX)
 *           glDataPtr - pointer returned by RvCCoreInitializeGlobals
 *           
 * OUTPUT  : None.
 * RETURN  : the data pointer of NULL if fails
 */
void RvCCoreDestroyGlobals(int index, void* glDataPtr);

#define RV_USE_CCORE_GLOBALS  RvCCoreGlobals *__globals__ = (RvCCoreGlobals *)RvGetGlobalDataPtr(RV_CCORE_GLOBALS_INDEX)

#define RV_UNUSE_GLOBALS   RV_UNUSED_ARG(__globals__)

#define RvCCoreGlob(name) (__globals__->_##name)

#define RvCBaseInitCount                RvCCoreGlob(RvCBaseInitCount)
#define RvCCoreInitCount                RvCCoreGlob(RvCCoreInitCount)
#define RvCCoreNumModules               RvCCoreGlob(RvCCoreNumModules)

#if (RV_LOCK_TYPE != RV_LOCK_NONE)
#define RvDefaultLockAttr               RvCCoreGlob(RvDefaultLockAttr)
#endif

#if (RV_LOGMASK != RV_LOGLEVEL_NONE)
#define rvLogInsideTextAny              RvCCoreGlob(rvLogInsideTextAny)
#define rvLogCurId                      RvCCoreGlob(rvLogCurId)
#define rvLogTextStr                    RvCCoreGlob(rvLogTextStr)
#define logThreadNum                    RvCCoreGlob(logThreadNum)
#endif

#if (RV_MUTEX_TYPE != RV_MUTEX_NONE)
#define RvDefaultMutexAttr              RvCCoreGlob(RvDefaultMutexAttr)
#endif

#if (RV_SEMAPHORE_TYPE != RV_SEMAPHORE_NONE)
#define RvDefaultSemaphoreAttr          RvCCoreGlob(RvDefaultSemaphoreAttr)
#endif

#define RvDefaultThreadAttr             RvCCoreGlob(RvDefaultThreadAttr)

#if (RV_HOST_HAS_STATIC_ADDR == RV_YES)    
#define rvHostLocalIpList               RvCCoreGlob(rvHostLocalIpList)
#define rvHostLocalNumOfIps             RvCCoreGlob(rvHostLocalNumOfIps)
#define rvHostLocalListInitialized      RvCCoreGlob(rvHostLocalListInitialized)
#endif

#define rvSelectMaxDescriptors          RvCCoreGlob(rvSelectMaxDescriptors)
#define rvSelectTlsVarIndex             RvCCoreGlob(rvSelectTlsVarIndex)
#define tosSupported                    RvCCoreGlob(tosSupported)
#define rvLogLock                       RvCCoreGlob(rvLogLock)
#define RvDefaultRegion                 RvCCoreGlob(RvDefaultRegion)
#define RvUserDefaultCB                 RvCCoreGlob(RvUserDefaultCB)
#define RvRegionList                    RvCCoreGlob(RvRegionList)
#define RvUserDefaultLock               RvCCoreGlob(RvUserDefaultLock)
#define RvMemoryLock                    RvCCoreGlob(RvMemoryLock)
#define RvDriverStatus                  RvCCoreGlob(RvDriverStatus)
#define rvActualNumDrivers              RvCCoreGlob(rvActualNumDrivers)

#define RvThreadLock                    RvCCoreGlob(RvThreadLock)
#define RvThreadVars                    RvCCoreGlob(RvThreadVars)
#define RvCBaseNumModules               RvCCoreGlob(RvCBaseNumModules)
#define rvHostLocalName                 RvCCoreGlob(rvHostLocalName)
#define rvSelectMinTimeoutResolution    RvCCoreGlob(rvSelectMinTimeoutResolution)
#define rvDefaultAlloc                  RvCCoreGlob(rvDefaultAlloc)
#define gsSleepChannelTLSIndex          RvCCoreGlob(gsSleepChannelTLSIndex)
#define gsStatusTLS						RvCCoreGlob(gsStatusTLS)


typedef struct 
{
    RvInt _RvCCoreInitCount; /* Use to make sure we only run once */
    RvInt _RvCCoreNumModules;

#if (RV_LOCK_TYPE != RV_LOCK_NONE)
    /* define the default attributes since they may be a structure */
    RvLockAttr _RvDefaultLockAttr;
#endif    

#if (RV_LOGMASK != RV_LOGLEVEL_NONE)
    RvBool _rvLogInsideTextAny;
    RvThreadId _rvLogCurId;    
    RvChar _rvLogTextStr[RV_LOG_MESSAGE_SIZE + RV_LOG_RESERVED_BYTES];
#endif

    int _logThreadNum;

#if (RV_MUTEX_TYPE != RV_MUTEX_NONE)
    /* define the default attributes since they may be a structure */
    RvMutexAttr _RvDefaultMutexAttr;
#endif

#if (RV_SEMAPHORE_TYPE != RV_SEMAPHORE_NONE)
    /* define the default attributes since they may be a structure */
    RvSemaphoreAttr _RvDefaultSemaphoreAttr;
#endif

    RvThreadAttr _RvDefaultThreadAttr;

    RvInt _RvCBaseInitCount;
    
#if (RV_HOST_HAS_STATIC_ADDR == RV_YES)    
    /* List of host addresses - allocated statically */
    RvAddress _rvHostLocalIpList[RV_HOST_MAX_ADDRS];
    RvUint32  _rvHostLocalNumOfIps;
    RvBool    _rvHostLocalListInitialized;    
#endif    


#if ((RV_SELECT_TYPE == RV_SELECT_SELECT) || \
    (RV_SELECT_TYPE == RV_SELECT_POLL) || \
    (RV_SELECT_TYPE == RV_SELECT_DEVPOLL) || \
    (RV_SELECT_TYPE == RV_SELECT_EPOLL) || \
    (RV_SELECT_TYPE == RV_SELECT_KQUEUE)  || \
    (RV_SELECT_TYPE == RV_SELECT_SYMBIAN))
    /* Maximum number of file descriptors to allocate operating systems */
    RvUint32 _rvSelectMaxDescriptors;    
#endif

    RvUint32 _rvSelectTlsVarIndex;

    RvBool _tosSupported;

#if (RV_LOGMASK != RV_LOGLEVEL_NONE)
    /* Lock used for log buffer printing */
    RvLock _rvLogLock;
#endif

    RvMemory _RvDefaultRegion;     /* Default memory region: OsMem driver, also handle out-of-memory callback */
    RvMemoryFunc _RvUserDefaultCB; /* User changable out-of-memory callback for default region */
    RvObjList _RvRegionList;       /* List of currently constructed regions */
    RvLock _RvUserDefaultLock;     /* Use for locking RvUserDefaultCB */
    RvLock _RvMemoryLock;          /* Use for locking during construct/destruct */
    RvStatus _RvDriverStatus[RV_MEMORY_NUMDRIVERS]; /* Holds status of individual drivers */
    RvInt _rvActualNumDrivers;     /* Actual number of memory drivers */

    RvLock _RvThreadLock; /* RvThreadVars lock to prevent bizarre construct/destruct sequences */
    RvThreadVar _RvThreadVars[RV_THREAD_MAX_VARS]; /* Thread specific variable info */
    RvInt _RvCBaseNumModules;    /* Total number of initiated modules */

    RvChar _rvHostLocalName[RV_HOST_MAX_NAMESIZE]; 

/* Minimum timeout resolution that can be handled. This one on some of the embedded operating
   systems should be modified to make the system work correctly, without exiting the select()
   loop too many times for each timeout. The value is in nanoseconds, */
    RvUint64 _rvSelectMinTimeoutResolution;

    
    /* used in rvtimer.c */
    RvUint32 _gsSleepChannelTLSIndex;
	RvUint32 _gsStatusTLS;

    RvAlloc _rvDefaultAlloc;
    

    void*  osSpecificGlobals;
    
} RvCCoreGlobals;

#if (RV_OS_TYPE == RV_OS_TYPE_SYMBIAN)

#ifdef __cplusplus
extern "C" {
#endif

RvCCoreGlobals* RvSymbianAllocateGlobalData(RvCCoreGlobals *gl);
void RvSymbianDestroyGlobalData(void *p);

#ifdef __cplusplus
}
#endif 

#endif /* (RV_OS_TYPE = RV_OS_TYPE_SYMBIAN) */

#endif
