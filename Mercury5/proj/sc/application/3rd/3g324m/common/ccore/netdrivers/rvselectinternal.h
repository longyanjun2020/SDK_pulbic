/***********************************************************************
Filename   : rvselectinternal.h
Description: internal address module definitions
             These definitions shouldn't be used outside of the
             address module directly
************************************************************************
        Copyright (c) 2001 RADVISION Inc. and RADVISION Ltd.
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

#ifndef _RV_SELECT_INTERNAL_H
#define _RV_SELECT_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif


/********************************************************************


            type definitions written in this file should not
            be accessed directly from outside the core. They
            may vary greatly between core versions!


 ********************************************************************/

#include "rvccore.h"
#include "rvtimer.h"
#include "rvthread.h"
#include "rvcondvar.h"

#if (RV_NET_TYPE != RV_NET_NONE)

#define RV_SELECT_PREEMPTION_NONE 0 /* No preemption mechanism at all */
#define RV_SELECT_PREEMPTION_PIPE 1 /* Use a pipe as a preemption mechanism */
#define RV_SELECT_PREEMPTION_SOCKET 2 /* Use a socket as a preemption mechanism */
#define RV_SELECT_PREEMPTION_SYMBIAN 3 /* Use a Symbian specific preemption mechanism */
#define RV_SELECT_PREEMPTION_MOPI 4     /* Use Mopi's process messaging mechanism */
#define RV_SELECT_PREEMPTION_SMQ  5


/* Remove annoying RV_SELECT_PREEPEMTION_TYPE typo */
#if defined(RV_SELECT_PREEPEMTION_TYPE)
#pragma message("ATTENTION: RV_SELECT_PREEPEMTION_TYPE macro was renamed to RV_SELECT_PREEMPTION_TYPE")

#ifndef RV_SELECT_PREEMPTION_TYPE
#define RV_SELECT_PREEMPTION_TYPE RV_SELECT_PREEPEMTION_TYPE
#endif

#endif /* RV_SELECT_PREEPEMTION_TYPE */


/* Check by interface which preemption we need to use to stop blocking */

/* If there is no user-defined preemption type - try
 *  to figure out correct preemption according to OS
 */
#ifndef RV_SELECT_PREEMPTION_TYPE

#if (RV_THREADNESS_TYPE == RV_THREADNESS_SINGLE) && (RV_SINGLE_THREADED_PREEMPTION == RV_NO)
/* No preemption when running single threaded */
#define RV_SELECT_PREEMPTION_TYPE RV_SELECT_PREEMPTION_NONE

#elif RV_OS_TYPE == RV_OS_TYPE_WIN32

/* No need for preemption in Win32 */

#if (RV_SELECT_TYPE == RV_SELECT_SELECT)
#define RV_SELECT_PREEMPTION_TYPE RV_SELECT_PREEMPTION_SOCKET
#else
#define RV_SELECT_PREEMPTION_TYPE RV_SELECT_PREEMPTION_NONE
#endif

#elif (RV_OS_TYPE == RV_OS_TYPE_WINCE)   || (RV_OS_TYPE == RV_OS_TYPE_NUCLEUS)|| \
      (RV_OS_TYPE == RV_OS_TYPE_PSOS)    || (RV_OS_TYPE == RV_OS_TYPE_OSE)    || \
      (RV_OS_TYPE == RV_OS_TYPE_INTEGRITY)
/* These operating systems don't support pipe() commands, so we have to use sockets instead */
#define RV_SELECT_PREEMPTION_TYPE RV_SELECT_PREEMPTION_SOCKET

#elif (RV_OS_TYPE == RV_OS_TYPE_SYMBIAN)

#define RV_SELECT_PREEMPTION_TYPE RV_SELECT_PREEMPTION_SMQ

#elif (RV_OS_TYPE == RV_OS_TYPE_MOPI)
#define RV_SELECT_PREEMPTION_TYPE RV_SELECT_PREEMPTION_MOPI

#else
/* We can use a pipe() command */
#define RV_SELECT_PREEMPTION_TYPE RV_SELECT_PREEMPTION_PIPE

#endif

#endif /* RV_SELECT_PREEMPTION_TYPE */




#if ((RV_SELECT_TYPE == RV_SELECT_WIN32_WSA) || (RV_SELECT_TYPE == RV_SELECT_WIN32_COMPLETION))

#include <winsock2.h>

/* We use Windows specific values so we don't have to convert them */
#define RV_SELECT_READ       FD_READ
#define RV_SELECT_WRITE      FD_WRITE
#define RV_SELECT_ACCEPT     FD_ACCEPT
#define RV_SELECT_CONNECT    FD_CONNECT
#define RV_SELECT_CLOSE      FD_CLOSE



#elif (	(RV_SELECT_TYPE == RV_SELECT_SELECT)  || (RV_SELECT_TYPE == RV_SELECT_POLL) || \
    	(RV_SELECT_TYPE == RV_SELECT_DEVPOLL) || (RV_SELECT_TYPE == RV_SELECT_SYMBIAN) || \
        (RV_SELECT_TYPE == RV_SELECT_KQUEUE)  || (RV_SELECT_TYPE == RV_SELECT_EPOLL))

#if (RV_OS_TYPE == RV_OS_TYPE_WINCE)
#include <winsock.h>

#elif (RV_OS_TYPE == RV_OS_TYPE_VXWORKS)
#include <time.h>
#include <types.h>
#include <selectLib.h>

#elif (RV_OS_TYPE == RV_OS_TYPE_PSOS)
#include <time.h>
#include <types.h>
#include <pna.h>

#elif (RV_OS_TYPE == RV_OS_TYPE_OSE)
#include <sys/time.h>
#include <sys/types.h>
#include <inet.h>

#elif (RV_OS_TYPE == RV_OS_TYPE_NUCLEUS)
#include <inc/nu_net.h>
/*#include <sys/select.h>*/

#elif (RV_OS_TYPE == RV_OS_TYPE_INTEGRITY)
#include <unistd.h>

#elif (RV_OS_TYPE == RV_OS_TYPE_SOLARIS) || \
      (RV_OS_TYPE == RV_OS_TYPE_LINUX) || \
      (RV_OS_TYPE == RV_OS_TYPE_TRU64) || \
      (RV_OS_TYPE == RV_OS_TYPE_UNIXWARE) || \
      (RV_OS_TYPE == RV_OS_TYPE_FREEBSD) || \
      (RV_OS_TYPE == RV_OS_TYPE_MAC) || \
      (RV_OS_TYPE == RV_OS_TYPE_NETBSD)
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>

#elif (RV_OS_TYPE == RV_OS_TYPE_HPUX)
#include <sys/time.h>
#endif

#if (RV_OS_TYPE == RV_OS_TYPE_NUCLEUS)
/* =========== NUCLEUS =========== */
#define RV_FD_ZERO  NU_FD_Init
#define RV_FD_SET   NU_FD_Set
#define RV_FD_ISSET NU_FD_Check
#define RV_FD_CLR   NU_FD_Reset
#define fd_set      FD_SET

#ifdef FD_SETSIZE
#undef FD_SETSIZE
#endif
#define FD_SETSIZE 2048

#elif (RV_OS_TYPE == RV_OS_TYPE_MOPI)
/* ============= MOPI ============ */

#define RV_FD_ZERO  Mmb_fdZero
#define RV_FD_SET   Mmb_FdSet
#define RV_FD_ISSET Mmb_fdIsSet
#define RV_FD_CLR   Mmb_FdClr

#else
/* ======== ALL OTHER OS's ======= */
#define RV_FD_ZERO FD_ZERO
#define RV_FD_SET FD_SET
#define RV_FD_ISSET FD_ISSET
#define RV_FD_CLR FD_CLR

#endif



#define RV_SELECT_READ       RvUint16Const(0x01)
#define RV_SELECT_WRITE      RvUint16Const(0x02)
#define RV_SELECT_ACCEPT     RvUint16Const(0x04)
#define RV_SELECT_CONNECT    RvUint16Const(0x08)
#define RV_SELECT_CLOSE      RvUint16Const(0x10)


#endif  /* RV_SELECT_TYPEs */


#if (RV_SELECT_TYPE == RV_SELECT_POLL)
#include <sys/poll.h>

#elif (RV_SELECT_TYPE == RV_SELECT_DEVPOLL)
#include <sys/ioctl.h>
#include <sys/poll.h>
#if (RV_OS_TYPE == RV_OS_TYPE_SOLARIS)
#include <sys/devpoll.h>
#else
#include <devpoll.h>
#endif

#elif (RV_SELECT_TYPE == RV_SELECT_EPOLL)
#include <sys/epoll.h>

#elif (RV_SELECT_TYPE == RV_SELECT_KQUEUE)
/* ===== only used in FreeBSD OS ====== */
#include <sys/event.h>

typedef enum {
    RV_SELECT_KQUEUE_GROUP_LOW,     /* Low priority group */
    RV_SELECT_KQUEUE_GROUP_HIGH,    /* High priority group */
    RV_SELECT_KQUEUE_GROUP_CNTL     /* The "Control" Kqueue used for handling events
                                     * from the low and high Kqueue as well as the
                                     * preemption mechanism */
} RvSelectKqueueGroupId;

#endif

#if RV_SELECT_PREEMPTION_TYPE == RV_SELECT_PREEMPTION_SMQ

#include "rvsmq.h"

#endif




struct RvSelectFdInternal
{
    RvSocket        fd;               /* File descriptor for this event */
    RvSelectCb      callback;         /* Callback function - should be type casted when used */
    RvSelectEvents  events;           /* Events we're waiting on - needed for translation */
    RvBool          closedByTcpPeer;  /* TRUE if TCP peer sent shutdown request */
    RvUint64        timestamp;        /* 'seli' timestamp at the moment of 'fd' addition to seli */

#if RV_SELECT_TYPE == RV_SELECT_WIN32_WSA
    /* When added to select engine under AsyncSelect model, there may be
     * socket events pertinent to previous incarnation of our socket. Those 'old' events shouldn't trigger
     * callbacks on our socket.
     *
     * So, we apply the following procedure on adding socket to select engine
     *  1. Newly added socket is marked as disabled.
     *     As long as a socket is disabled no events is triggered for it.
     *
     *  2. ENABLE event is posted for this socket to the queue. In order to distinguish
     *     new ENABLE event from the old one, that probably still stay in in the event queue
     *     we add running counter to the posted ENABLE event as LWPARAM as additional id.
     *
     *  3. When ENABLE event is read from the queue, the socket is enabled.
     */
    RvBool           bEnabled;
    LPARAM           fdId;
                                   
#endif

#if (RV_SELECT_TYPE == RV_SELECT_POLL)
    RvInt           fdArrayIndex; /* Index in fdArray of the select engine used by this fd */
#endif

#if (RV_SELECT_TYPE == RV_SELECT_DEVPOLL)
    short           devpollEvents; /* /dev/poll events we're using. Done here to reduce the
                                      number of writes to /dev/poll */
#endif

#if (RV_SELECT_TYPE == RV_SELECT_KQUEUE)
#if (RV_SELECT_KQUEUE_GROUPS == RV_YES)
    RvSelectKqueueGroupId   group; /* group to which this fd belongs (low / high) */
#endif
#endif
    RvLogMgr        *logMgr;       /* log manager instance. Important for case when two
                                   stacks running in the same process use same select engine
                                   but separate log managers */
    RvSelectFd      *nextInBucket; /* Next file descriptor in the same bucket */


    void            *userContext;  /* a user's arbitrary data */
};


/********************************************************************************************
 * RvSelectBucket
 * Will be used as the element in the hash.
 ********************************************************************************************/
typedef struct RvSelectBucketInternal RvSelectBucket;
struct RvSelectBucketInternal
{
    RvSelectFd          *selectFD;
    RvSelectBucket      *prevBucket;
    RvSelectBucket      *nextBucket;
};

#define RV_SELECT_INIT_BUCKET(_b,_selFD,_prev,_next) \
    (_b)->selectFD = _selFD;  \
    (_b)->prevBucket = _prev; \
    (_b)->nextBucket = _next;

/* By default, FD removal synchronization is applied for
 * RV_SELECT_SELECT and RV_SELECT_POLL multiplexer models
 * It can be disabled by setting RV_SELECT_SYNC_REMOVAL to 0 in
 * rvusrconfig.h, for example
 *
 * With each thread is associated single semaphore that synchronize
 * FD removal. This semaphore is kept in thread's TLS variable
 * When thread enters RvSelectRemove and recognizes the need in synchronization
 * (for example: seli running on another thread is inside 'select' system call) it inserts
 * this semaphore into linked lists of semaphores. When seli exits it's system call it signals
 * all those semaphores and resets the list
 *
 */

#ifndef RV_SELECT_SYNC_REMOVAL

#if (RV_SELECT_TYPE == RV_SELECT_SELECT) || (RV_SELECT_TYPE == RV_SELECT_POLL)
#define RV_SELECT_SYNC_REMOVAL 1
#else
#define RV_SELECT_SYNC_REMOVAL 0
#endif

#endif

#if RV_SELECT_SYNC_REMOVAL

/* Linked list of semaphores waiting for seli thread to exit 'select' system call
 * Each node of this list is allocated on the stack of the thread associated with
 * this semaphore
 */
typedef struct _RvSelectSyncNode {
    struct _RvSelectSyncNode *next;
    RvSemaphore *syncSemaphore;
} RvSelectSyncNode;

#endif

#define MAX_PREEMPTION_HANDLERS 256

typedef struct _RvSelectPreemptionHandler {
    RvSelectPreemptionCb cb;
    void *ctx;
} RvSelectPreemptionHandler;

typedef struct {
    RvSelectPreemptionHandler defaultHandler;
    RvSelectPreemptionHandler handlers[MAX_PREEMPTION_HANDLERS];
} RvSelectPreemptionHandlers;

/********************************************************************************************
 * RvSelectEngineInternal
 * Fd Events engine declaration. This struct's members should not be modified or accessed
 * directly by users of the core.
 ********************************************************************************************/
struct RvSelectEngineInternal
{
    RvUint64                timestamp;         /* It isn't timestamp per se, but rather,
                                                * the number of calls to WaitAndBlock
                                                * In each iteration of WaitAndBlock we're
                                                * considering only those fds that were added to
                                                * select engine BEFORE this call to WaitAndBlock
                                                * in order to avoid phantom events.
                                                */

#if (RV_SELECT_TYPE == RV_SELECT_WIN32_WSA)
    HWND                    hNetEventsWnd;      /* Network events window. All events are
                                                received by it
                                                Must not being changed after engine
                                                initialization. */
    RvBool                  exitMessageLoop;    /* RV_TRUE if we want to exit the current
                                                message loop */
    HANDLE                  threadHandle;       /* Thread handle of this fd engine.
                                                Must not being changed after engine
                                                initialization. */
    DWORD                   threadId;           /* Thread ID handling this events engine.
                                                Must not being changed after engine
                                                initialization. */
    LPARAM                  additionCounter;    /* Running counter that counts number of call to RvSelectAdd
                                                 * This counter is used as ID for newly added socket
                                                 * (see documentation for RvSelectFd)
                                                 */

    /* When user event handling callback is called for fd, this fd can be
       removed and it's memory can be freed. Both by the same thread that calls
       the callback and by other thread. In this case the fd should not
       be accessed anymore after return from the callback.
       In order to catch this situation the "removed fd" flag was added.
       It works in following way:
          1. "removed fd" flag is defined as a local variable in rvSelectWinFunc
          2. Before engine is unlocked before call to callback the fd's pointer
             to the flag is updated in order to point to this local variable.
             The local variable is initialized with RV_FALSE.
          3. Whenever RvSelectRemove is called for this fd, it turns on this
             flag, using the fd's pointer.
             Note if fd's pointer is NULL, that means that there is no event
             fro which the callback is being called.
          4. After return from the callback the flag value is checked.
             If it is RV_TRUE, the fd was removed when the select thread was
             in the callback. In this case no more processing of fd is done
             in the rvSelectWinFunc. */
    RvBool                  bFdRemovedFromUserCallback;

#elif (RV_SELECT_TYPE == RV_SELECT_WIN32_COMPLETION)
    HANDLE                  completionPort;     /* Handle of the completion port we use
                                                for this engine.
                                                Must not being changed after engine
                                                initialization. */
#elif (RV_SELECT_TYPE == RV_SELECT_SELECT)
    RvUint32                maxFd;              /* Maximum number of fd's supported.
                                                Must not being changed after engine
                                                initialization */
    RvUint32                maxFdInSelect;      /* Maximum fd set in the fdset's
                                                of the select() */
    fd_set                  rdSet;              /* Read fd's we're currently waiting for */
    fd_set                  wrSet;              /* Write fd's we're currently waiting for */
    RvBool                  waiting;            /* RV_TRUE if we're blocked in a select()
                                                call */
    RvUint64                nsecTimeout;        /* timeout required by rvtimer module */
    RvBool                  suspectTimeout;

    RvThread                *selectThread;      /* Thread where select was used last time */

#if (RV_OS_TYPE == RV_OS_TYPE_NUCLEUS)
    fd_set                  simulatedRdSet;     /* Read fd's that were simulated */
    fd_set                  simulatedWrSet;     /* Write fd's that were simulated */
    RvUint32                simulatedNumFd;     /* number of fd's that were simulated in simulated sets */
    RvUint32                simulatedMaxFd;     /* Maximum fd set in the simulated fdset's */
    RvLock                  simulatedSetLock;   /* just to make sure we wont clear any new events */
    RvBool                  needToPreempt;      /* used to signal a "must-send" preemption message, even
                                                if preemption is called from within the 'selecting'
                                                thread' - used to overcome write-event problem in nucleus */

#endif /* (RV_OS_TYPE == RV_OS_TYPE_NUCLEUS) */

#elif (RV_SELECT_TYPE == RV_SELECT_POLL)
    RvUint32                maxFd;              /* Maximum number of fd's supported.
                                                Must not being changed after engine
                                                initialization */
    RvUint32                maxFdInPoll;        /* Number of file descriptors being polled */

    RvSize_t                fdArraySize;
    struct pollfd*          fdArray;            /* File descriptors we're polling */
    struct pollfd*          tmpFdArray;         /* temporrary file descriptors array,
                                                used to call 'poll' without locking
                                                select engine */
    RvBool                  waiting;            /* RV_TRUE if we're blocked in a poll() call*/
    RvUint64                nsecTimeout;        /* timeout required by rvtimer module */
    RvBool                  suspectTimeout;

    RvThread                *selectThread;      /* Thread where select was used last time */

#elif (RV_SELECT_TYPE == RV_SELECT_DEVPOLL)
    RvUint32                maxFd;              /* Maximum number of fd's supported
                                                Must not being changed after engine
                                                initialization. */
    RvUint32                maxFdInPoll;     /* Number of FDs currently used. */
    int                     fdDevPoll;          /* /dev/poll's file descriptor */
#if 0
    struct pollfd*          fdArray;            /* File descriptors we're polling */
#endif
    RvSize_t                fdArraySize;
    struct pollfd*          tmpFdArray;         /* temporrary file descriptors array,
                                                used to call 'poll' without locking
                                                select engine */
    RvBool                  waiting;            /* RV_TRUE if we're blocked in a /dev/poll ioctl() call */
    RvUint64                nsecTimeout;        /* timeout required by rvtimer module */
    RvBool                  suspectTimeout;

    RvThread                *selectThread;      /* Thread where select was used last time */
    RvSemaphore             devPollWrite;       /* used as a mutex to synchronize
                                                manipulation of /dev/poll */

#elif (RV_SELECT_TYPE == RV_SELECT_EPOLL)
    RvUint32                maxFds;             /* Maximum number of fd's supported
                                                Must not be changed after engine
                                                initialization. */
    RvInt32                 epFd;               /* epoll file descriptor */
    struct epoll_event*     fdArray;            /* epoll events array - where all events are receieved*/
    RvBool                  waiting;            /* RV_TRUE if we're blocked in a epoll_wait() call */
    RvUint64                nsecTimeout;        /* timeout required by rvtimer module */
    RvThread                *selectThread;      /* Thread where select was used last time */

#elif (RV_SELECT_TYPE == RV_SELECT_KQUEUE)
    RvUint32                maxFd;              /* Maximum number of fd's supported
                                                Must not be changed after engine
                                                initialization. */
    RvInt32                 kqueueId;           /* kqueue file descriptor */
    struct kevent*          fdArray;            /* kevents array - where all event are receieved*/
    RvInt32                 nFdArray;           /* maximum elements in fdArray */
    RvBool                  waiting;            /* RV_TRUE if we're blocked in a kevent() call */
    RvUint64                nsecTimeout;        /* timeout required by rvtimer module */
    RvThread                *selectThread;      /* Thread where select was used last time */
#if (RV_SELECT_KQUEUE_GROUPS == RV_YES)
    RvInt32                 kqueueIdLow;        /* low priority kqueue file descriptor */
    RvInt32                 kqueueIdHigh;       /* high priority kqueue file descriptor */
    RvSelectFd              kqueueFdLow;        /* fd struct for low priority Kqueue file descriptor */
    RvSelectFd              kqueueFdHigh;       /* fd struct for high priority Kqueue file descriptor */
    struct kevent*          fdArrayLow;         /* kevents array - where low pri. events are receieved*/
    struct kevent*          fdArrayHigh;        /* kevents array - where high pri. events are receieved*/
    RvInt32                 ratioLow;           /* low priority ratio */
    RvInt32                 ratioHigh;          /* high priority ratio */
#endif
#elif (RV_SELECT_TYPE == RV_SELECT_SYMBIAN)
    void*                   symSelectStruct;
    RvBool                  waiting;            /* RV_TRUE if we're blocked in a select()
                                                call */
    RvUint64                nsecTimeout;        /* timeout required by rvtimer module */
    RvBool                  suspectTimeout;
    RvThread                *selectThread;      /* Thread where select was used last time */
#endif

    /* Bucket-hash parameters */
    RvUint32                maxHashSize;        /* Size of the bucket hash to use */
    RvSelectBucket*         hash;               /* Bucket hash to use for the file descriptors */
    RvSelectBucket*         firstBucket;        /* the first non-empty bucket in the hash */
    RvUint32                currentFDsCount;    /* count of FD's held in the hash */

    struct RvSelectFdInternal* fdInUserCallback;    /* marks the FD which is currently within 
                                                   the callback*/

    RvSelectPreemptionHandlers preemptionHandlers; /* Handlers for preemption messages */
    RvThread                *constructedThread; /* pointer to the thread constructed when select engine
                                                 was created */

#if (RV_SELECT_PREEMPTION_TYPE == RV_SELECT_PREEMPTION_SOCKET) || \
    (RV_SELECT_PREEMPTION_TYPE == RV_SELECT_PREEMPTION_PIPE)
    RvSelectFd              preemptionFd;       /* Information about the pipe's read file descriptor
                                                Must not being changed after engine
                                                initialization. */
#endif

#if (RV_SELECT_PREEMPTION_TYPE == RV_SELECT_PREEMPTION_SOCKET)
    RvSocket                preemptionSocket;   /* Socket used to preempt a select() call of the thread
                                                Must not being changed after engine
                                                initialization. */
    RvAddress               localAddress;       /* Address we're listening on for preemption.
                                                Must not being changed after engine
                                                initialization. */

#elif (RV_SELECT_PREEMPTION_TYPE == RV_SELECT_PREEMPTION_PIPE)
    int                     preemptionPipeFd[2]; /* Pipe used to preempt a select() call of the thread
                                                Must not being changed after engine
                                                initialization. */

#elif (RV_SELECT_PREEMPTION_TYPE == RV_SELECT_PREEMPTION_MOPI)
    RvUint32                mopiProcessId;      /* process ID to which preemption messages
                                                   will be sent */
#endif

#if RV_SELECT_PREEMPTION_TYPE == RV_SELECT_PREEMPTION_SMQ
    HRvSMQ                  smq;
    RvSelectFd              smqFd;
    RvAddress               smqAddr;
    RvSMQMsgTargetId        smqMsgTargetId;
    RvInt                   smqNotifications;   /* statistics counter for SMQ */
#endif

    RvInt32                 usageCnt;           /* select engine usage counter */
    RvTimerQueue            tqueue;             /* timer queue that asked for the last timeout */
    RvSize_t                maxTimers;          /* maximum required number of timers.
                                                tqueue size may be more than the maxTimers.*/
    RvTimerFunc             timeOutCb;          /* callback, applied when timeout event occures */
    void                    *timeOutCbContext;  /* callback user data */
    RvLogMgr*               logMgr;             /* log manager used to print log from the select module.
                                                Must not being changed after engine
                                                initialization. */
    RvLock                  lock;               /* Select engine instance protection lock.
                                                Must not being changed after engine
                                                initialization. */
    RvUint64                wakeupTime;         /* Absolute time when select should be waked up */

    RvCondvar               removeFdCondVar;    /* this condvar is used to synchronize between the
                                                   the thread performing the callback associated
                                                   with the 'RvSelectFd' object and the other thread 
                                                   trying to remove that fd object from the select
                                                   engine */

    RvThreadId              selectEngineThreadId;   /* the ID of the thread where WaitAndBlock is called */

#if RV_SELECT_SYNC_REMOVAL

/* Support for synchronous removal of FD
 * Removing FD from select engine and closing socket after that may cause
 * problems when, for example, RvSelectWaitAndBlock is still inside 'select'
 * system call
 */

    /* Semaphore to wait for notifications on for exit from OS multiplexer (select, poll, etc) */
    RvSelectSyncNode *removalSyncList;

    /* Lock guarding removal synchronization mechanism */
    RvLock                 removalLock;

#endif
};


#ifdef __cplusplus
}
#endif

#endif /* (RV_NET_TYPE != RV_NET_NONE) */

#endif  /* _RV_SELECT_INTERNAL_H */
