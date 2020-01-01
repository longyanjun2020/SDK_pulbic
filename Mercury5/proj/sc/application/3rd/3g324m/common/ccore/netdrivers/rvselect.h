/***********************************************************************
Filename   : rvselect.h
Description: select interface (select, poll, /dev/poll, etc.)
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

#ifndef _RV_FD_SELECT_H
#define _RV_FD_SELECT_H

#include "rvccore.h"
#include "rvlock.h"
#include "rvsocket.h"


/* Error checks to make sure configuration has been done properly */
#if !defined(RV_SELECT_TYPE) || ((RV_SELECT_TYPE != RV_SELECT_SELECT) && \
    (RV_SELECT_TYPE != RV_SELECT_POLL) && (RV_SELECT_TYPE != RV_SELECT_DEVPOLL) && \
    (RV_SELECT_TYPE != RV_SELECT_WIN32_WSA) && (RV_SELECT_TYPE != RV_SELECT_WIN32_COMPLETION) && \
    (RV_SELECT_TYPE != RV_SELECT_SYMBIAN) && (RV_SELECT_TYPE != RV_SELECT_KQUEUE) && \
    (RV_SELECT_TYPE != RV_SELECT_EPOLL))
    
#error RV_SELECT_TYPE not set properly
#endif
#if (RV_SELECT_TYPE == RV_SELECT_WIN32_COMPLETION)
#error RV_SELECT_WIN32_COMPLETION is not supported in this version
#endif
/* End of configuration error checks */


/* Module specific error codes (-512..-1023). See rverror.h dor more details */
#define RV_SELECT_ERROR_GETRLIMIT -512 /* Can't get the resource limit from the operating system */
#define RV_SELECT_ERROR_PIPE -513 /* Can't create a pipe for preemption */

/* Define # of timers per page in the select engine timer queue */
#define RV_SELECT_TIMERS_PER_PAGE 120


#if defined(__cplusplus)
extern "C" {
#endif


typedef struct RvSelectEngineInternal RvSelectEngine;


/* File descriptor type */
typedef struct RvSelectFdInternal RvSelectFd;

/* Type declaration of events we can wait for on file descriptors */
typedef RvUint16 RvSelectEvents;


/* Utility function to set/get user data per fd structure */
#define RvFdGetUserContext(thisPtr) (((struct RvSelectFdInternal *)(thisPtr))->userContext)
#define RvFdSetUserContext(thisPtr,v) (((struct RvSelectFdInternal *)(thisPtr))->userContext = (v))


/********************************************************************************************
 * RvSelectCb
 *
 * purpose : Callback that is executed when an event occurs on a file descriptor
 * input   : selectEngine   - Events engine of this fd
 *           fd             - File descriptor that this event occured on
 *           selectEvent    - Event that happened
 *           error          - RV_TRUE if an error occured
 * output  : None
 * return  : None
 * remarks :
 * - RvSelectRead is received whenever there are messages waiting on the given connection.
 *   Applications must be prepared to get WOULDBLOCK events when actually trying to read
 *   from the connection.
 *   Multiple recv() calls are possible. The event will only be activated again once this
 *   callback returns.
 * - RvSelectWrite is received when the application can send messages on the connection
 *   without being blocked (again, they must be prepared to get WOULDBLOCK).
 *   After this event is received, applications are encouraged to remove this event once they
 *   get it and enable it again when you get blocked trying to send messages - this works
 *   both on Unix and Windows systems.
 ********************************************************************************************/
typedef void
    (* RvSelectCb)(
        IN RvSelectEngine*  selectEngine,
        IN RvSelectFd*      fd,
        IN RvSelectEvents   selectEvent,
        IN RvBool           error);


/********************************************************************************************
 * RvSelectPreemptionCb
 *
 * purpose : Callback that is executed when an select was preempted by reason,
 * other that RvSelectEmptyPreemptMsg
 * input   : selectEngine    - Events engine
 *           preemptionEvent - Preemption Event
 *           context         - predefined user context
 * output  : None
 * return  : None
 * remarks : None
 *			
 ********************************************************************************************/
typedef void 
	(* RvSelectPreemptionCb)(
		IN RvSelectEngine	*selectEngine,
		IN RvUint8			preemptEv,
		IN void				*context);

#include "rvselectinternal.h"



/********************************************************************************************
 * Possible fd events
 * Not all operating systems support all of these events. In these cases, it's up to the
 * user of this module to resolve the actual event from the events he got.
 * The events that are supported by all are read and write events.
 * Note the fact that CLOSE events might not be returned by some OS's (mostly Unix). In such
 * cases, receiving a READ event, and actually trying to read will cause an error, which can
 * be interpreted as close event.
 ********************************************************************************************/
#define RvSelectRead        RV_SELECT_READ
#define RvSelectWrite       RV_SELECT_WRITE
#define RvSelectAccept      RV_SELECT_ACCEPT
#define RvSelectConnect     RV_SELECT_CONNECT
#define RvSelectClose       RV_SELECT_CLOSE


/********************************************************************************************
 * Define empty preemption message. Stack may define other types of preemption messages.
 * When RvSelect module preemption callback reads that value, no stack callbacks will be 
 * applied. It leaves 2^7 (128) optional values for the stack.
 ********************************************************************************************/
#define RvSelectEmptyPreemptMsg ((RvUint8)0)

/* Prototypes and macros */

/********************************************************************************************
 * RvSelectInit - Initiates select module.
 * This function must be applied only once when initiating process that uses the common core.
 * Even in case there are multiple stacks that uses common core, this function must be applied
 * only once. The function is registered in the rvccore.c file in RvCCoreModules structure and
 * is applied automatically by function RvCCoreInit.
 * Not thread-safe functions.
 * INPUT   : none
 * OUTPUT  : none
 * RETURN  : RV_OK on success, other on failure
 */
RvStatus RvSelectInit(void);

/********************************************************************************************
 * RvSelectEnd - Shutdown select module.
 * This function must be applied only once during shutdown of process that uses the common core.
 * Even in case there are multiple stacks that uses common core, this function must be applied
 * only once. The function is registered in the rvccore.c file in RvCCoreModules structure and
 * is applied automatically by function RvCCoreEnd.
 * Not thread-safe functions.
 * INPUT   : none
 * OUTPUT  : none
 * RETURN  : RV_OK on success, other on failure
 */
RvStatus RvSelectEnd(void);

/********************************************************************************************
 * RvSelectSourceConstruct - initiates log source, used for select module logging.
 * This function must be applied once per instance of log manager. This function
 * is registered in list of RvLogModules and automatically applied by function 
 * RvLogConstruct. It's assumed that this function is applied in main thread 
 * and only once for specific select engine. Note that log source destruct applied
 * automatically when stack applied log manager destruct function.
 * Not thread-safe functions.
 * INPUT   : logMgr		- log manager instance
 * OUTPUT  : none
 * RETURN  : RV_OK on success, other on failure
 */

RvStatus RvSelectSourceConstruct(
	IN RvLogMgr* logMgr);


#if (RV_NET_TYPE != RV_NET_NONE)

/********************************************************************************************
 * RvSelectSetMaxFileDescriptors
 *
 * Set the amount of file descriptors that the Select module can handle in a single
 * select engine. This is also the value of the highest file descriptor possible.
 * Check if your stack and application uses this function before porting it.
 * This function should be called before calling RvSelectConstruct() and after RvSelectInit().
 * Not thread-safe
 * INPUT   : maxFileDescriptors - Maximum value of file descriptor possible
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI 
RvStatus RVCALLCONV RvSelectSetMaxFileDescriptors(
	IN RvUint32 maxFileDescriptors);


/********************************************************************************************
 * RvSelectGetMaxFileDescriptors
 *
 * Get the current value used as the maximum value for a file descriptor by the select engine.
 * Thread-safe functions, under assumptions specified in the header of the file.
 *
 * input   : None
 * output  : None
 * return  : Maximum value for a file descriptor select engines are going to support.
 */
RVCOREAPI 
RvUint32 RVCALLCONV RvSelectGetMaxFileDescriptors(void);


/********************************************************************************************
* RvSelectSetPreemptionCbEx
* Sets stack preemption callback that later used to notify stack about
* non-empty preemption messages.
*
* INPUT   : selectEngine     - Events engine to construct
*         : preemptionCb     - preemption callback to be called 
*         : preemptionCtx    - user supplied context
* INOUT   : *pmsg
*            if pmsg == 0    - default preemption callback will be installed
*            if *pmsg == 0   - In this case pmsg serves as output parameter:
*                                fresh message will be allocated if possible and returned in *pmsg
*                                If messages namespace is exhausted, RV_ERROR_OUTOFRESOURCES will be returned
*            if *pmsg != 0   - New callback will be set for specified message
*                              
* OUTPUT  : None
* RETURN  : RV_OK on success, other on failure
*/
RVCOREAPI
RvStatus RVCALLCONV RvSelectSetPreemptionCbEx(
    IN  RvSelectEngine          *selectEngine,
    IN  RvSelectPreemptionCb    preemptionCb,
    IN  void                    *preemptionCtx,
    INOUT RvUint8               *pmsg);

#define RvSelectSetPreemptionCb(seli, cb, ctx) RvSelectSetPreemptionCbEx(seli, cb, ctx, 0)

/********************************************************************************************
 * RvSelectSetTimeoutInfo
 * Sets stack timeout processing callback. Usefull when stack wish to process timeouts
 * differently than simply applying timer service routine.
 * Thread-safe functions, under assumptions specified in the header of the file.
 * INPUT   : selectEngine     - select engine object
 *           timeOutCb        - timeout callback
 *           cbContext        - callback user data
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSelectSetTimeoutInfo(
    IN  RvSelectEngine          *selectEngine,
    IN  RvTimerFunc             timeOutCb,
    IN  void                    *cbContext);


/********************************************************************************************
 * RvSelectGetTimeoutInfo
 * Retrieves stack timeout processing information, including callback and timeout events queue
 * Thread-safe functions, under assumptions specified in the header of the file.
 * INPUT   : selectEngine     - select engine object
 * OUTPUT  : timeOutCb        - timeout callback
 *           tqueue           - timeout events queue
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSelectGetTimeoutInfo(
    IN  RvSelectEngine          *selectEngine,
    OUT RvTimerFunc             *timeOutCb,
    OUT RvTimerQueue            **tqueue);


/********************************************************************************************
 * RvSelectConstruct
 *
 * Allocates and initiates a new select engine.
 * In case select engine was already constructed for the current thread,
 * pointer to the existing agent will be returned.
 *
 *
 * INPUT   : maxHashSize    - Hash size used by the engine
 *           maxTimers      - maximum initial value for number of timers in the
 *                            timer queue, associated with the select engine
 *           logMgr         - log manager
 * OUTPUT  : engine         - Events engine to construct.
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSelectConstruct(
    IN    RvUint32         maxHashSize,
	IN    RvUint32         maxTimers,
    IN    RvLogMgr         *logMgr,
    OUT   RvSelectEngine   **engine);


/********************************************************************************************
 * RvSelectDestruct
 *
 * Destruct a select engine
 * Not thread-safe function.
 *
 * INPUT   : selectEngine - Events engine to destruct
 *           maxTimers    - number of timers, added to the 
 *                          select engine's tqueue for this
 *                          select engine instance
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSelectDestruct(
    IN RvSelectEngine   *selectEngine,
	IN RvUint32         maxTimers);

/********************************************************************************************
 * RvSelectGetThreadEngine
 *
 * Destruct a select engine
 * Not thread-safe function.
 *
 * INPUT   : logMgr       - log manager instance
 * OUTPUT  : selectEngine - Select engine associated with the current thread
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSelectGetThreadEngine(
	IN  RvLogMgr         *logMgr,
    IN  RvSelectEngine   **selectEngine);

/********************************************************************************************
 * RvFdConstruct
 *
 * Construct a file descriptor for a given socket.
 * This function must not be applied on fd structure after 
 * it was added to RvSelect waiting loop (or before it was removed
 * from there)
 * Not thread-safe function
 * INPUT   : fd     - File descriptor to construct
 *           s      - Socket to use for this file descriptor
 *           logMgr - log manager instance
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvFdConstruct(
    IN RvSelectFd   *fd,
    IN RvSocket     *s,
	IN RvLogMgr     *logMgr);


/********************************************************************************************
 * RvFdDestruct
 *
 * Destruct a file descriptor of a given socket.
 * It is assumed that this function will not be called if the given socket is still
 * waiting for events in the select engine. This means that RvSelectRemove() has
 * been called before calling this function.
 * Not thread-safe function
 * INPUT   : fd - File descriptor to destruct
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvFdDestruct(
    IN RvSelectFd*        fd);


/********************************************************************************************
 * RvFdGetSocket
 *
 * Get the socket associated with the file descriptor struct.
 * Not thread-safe
 * INPUT   : fd - File descriptor
 * RETURN  : Socket associated with the file descriptor on success
 *           NULL on failure
 */
RVCOREAPI
RvSocket* RVCALLCONV RvFdGetSocket(
	IN RvSelectFd* fd);

/********************************************************************************************
 * RvFdClosedByPeer
 *
 * Not thread-safe
 * INPUT   : fd - File descriptor
 * RETURN  : RV_TRUE if 'fd' is associated with TCP socket closed
 *           by it's peer, otherwise - return RV_FALSE.
 */
#define RvFdIsClosedByPeer(fd) ((fd) ? (fd)->closedByTcpPeer : 0)


/********************************************************************************************
 * RvSelectGetEvents
 *
 * Return the list of events we're waiting on for a given file descriptor
 * Not thread-safe
 * INPUT   : fd - File descriptor
 * OUTPUT  : None
 * RETURN  : Events we're waiting on
 */
RVCOREAPI
RvSelectEvents RVCALLCONV RvSelectGetEvents(
	IN RvSelectFd* fd);


/********************************************************************************************
 * RvSelectFindFd - Find the RvSelectFd object by the socket/file descriptor it's connected to.
 *
 * This function is used by the H.323 Stack to allow calls to seliCallOn() from the
 * stack's API. You don't need to port it if you are using other Stacks or if you
 * are not using the seliCallOn() function from your H.323 application.
 * Thread-safe functions, under assumptions specified in the header of the file.
 * Note that it still may be problem if you relay on output of the function since
 * after it called, list of file descriptor structure may be changed by other thread.
 *
 * INPUT   : selectEngine   - Events engine to look in
 *           s              - Socket/file descriptor object to find
 * OUTPUT  : None
 * RETURN  : RvSelectFd object if one exists, NULL otherwise.
 */
RVCOREAPI
RvSelectFd* RVCALLCONV RvSelectFindFd(
    IN RvSelectEngine*  selectEngine,
    IN RvSocket*        s);


/********************************************************************************************
 * RvSelectAdd - Add a new file descriptor to those being checked
 *
 * A file descriptor cannot be added twice. Once added, only RvSelectUpdate() can be
 * used to update the events we're waiting for, or RvSelectRemove() can be called
 * to remove this file descriptor from being handled by this select engine.
 * Thread-safe functions, under assumptions specified in the header of the file.
 *
 * INPUT   : selectEngine   - Events engine of this fd
 *           fd             - File descriptor to check
 *           selectEvents   - Events to check
 *           eventsCb       - Callback to use when these events occur
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSelectAdd(
    IN RvSelectEngine*      selectEngine,
    IN RvSelectFd*          fd,
    IN RvSelectEvents       selectEvents,
    IN RvSelectCb           eventsCb);


/********************************************************************************************
 * RvSelectRemove - Remove a file descriptor that is being checked by this engine
 *
 * Should only be called for file descriptors that RvSelectAdd() was called for them.
 * Thread-safe functions, under assumptions specified in the header of the file.
 *
 * INPUT   : selectEngine   - Events engine of this fd
 *           fd             - File descriptor to remove
 *           bWaitForCallbackCompletion - if set to RV_TRUE the function will wait
 *                            till the completion of the 'fd->callback' if it was active
 *                            when the fucntion was called.
 * OUTPUT  : 
 *           pbWasInCallback - if not NULL will be set to RV_TRUE if the 'fd->callback' was
 *                             active when the RvSelectRemoveEx was called.
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSelectRemoveEx(
    IN RvSelectEngine*      selectEngine,
    IN RvSelectFd*          fd,
    IN RvBool               bWaitForCallbackCompletion,
    OUT RvBool              *pbWasInCallback);

/********************************************************************************************
 * RvSelectRemove - Remove a file descriptor that is being checked by this engine
 *
 * Should only be called for file descriptors that RvSelectAdd() was called for them.
 * Thread-safe functions, under assumptions specified in the header of the file.
 * 
 * INPUT   : selectEngine   - Events engine of this fd
 *           fd             - File descriptor to remove
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
#define RvSelectRemove(_s,_fd) RvSelectRemoveEx((_s),(_fd),RV_FALSE,NULL)




/********************************************************************************************
 * RvSelectUpdate - Update the events of callback used for a given file descriptor
 * Should only be called for file descriptors that RvSelectAdd() was called for them.
 * Thread-safe functions, under assumptions specified in the header of the file.
 * INPUT   : selectEngine   - Events engine of this fd
 *           fd             - File descriptor to update
 *           selectEvents   - Events to check
 *           eventsCb       - Callback to use when these events occur
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSelectUpdate(
    IN RvSelectEngine*      selectEngine,
    IN RvSelectFd*          fd,
    IN RvSelectEvents       selectEvents,
    IN RvSelectCb           eventsCb);


/********************************************************************************************
 * RvSelectWaitAndBlock
 *
 * Wait for events to occur on this engine and block the current running thread
 * for a given amount of time, or until events occur.
 * This function must be called from the thread that called RvSelectConstruct().
 * The timeout in this function is used by some of the stacks to implement their
 * timers mechanism. 
 * Thread-safe functions, under assumptions specified in the header of the file.
 * 
 * INPUT   : selectEngine   - Events engine to wait for
 *           nsecTimeout    - Timeout to wait in nanoseconds
 *                            A 0-value will not block - just check for events
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSelectWaitAndBlock(
    IN RvSelectEngine*      selectEngine,
    IN RvUint64             nsecTimeout);


/********************************************************************************************
 * RvSelectStopWaiting
 *
 * Stop waiting for events on the given events engine. This function is called
 * from threads other than the one that called RvSelectWaitAndBlock() in order
 * to preempt it.This function doesn't wait for the other thread to stop executing, it just
 * makes sure the other thread returns from the call to RvSelectWaitAndBlock().
 * This function doesn't need to be ported for applications that are single-threaded
 * on top of stacks that are single threaded.
 * Thread-safe functions, under assumptions specified in the header of the file.
 *
 * INPUT   : selectEngine	- Events engine to stop from blocking
 *			 message		- message to be send. Can be used by the receiver
 *							  for stack specific messages
 *           logMgr         - log manager instance
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSelectStopWaiting(
    IN RvSelectEngine       *selectEngine,
	IN RvUint8				message,
	IN RvLogMgr             *logMgr);


/********************************************************************************************
 * RvSelectSetTimeOut
 *
 * Sets timeout for the select. This function used by the rvtimer module to set timeout
 * according to shortest user specified timeout.
 *
 * INPUT   : selectEngine   - Events engine to set timer on it
 *           nsecTimeout    - Timeout to wait in nanoseconds
 *                            A 0-value will not block - just check for events
 *           currentTime    - current time in nanoseconds
 *			 logMgr			- log manager instance
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RvStatus RVCALLCONV RvSelectSetTimeOut(
    IN RvSelectEngine       *selectEngine,
	IN RvUint64             currentTime,
	IN RvUint64				nsecTimeout,
	IN RvLogMgr             *logMgr);


/********************************************************************************************
 * RvSelectRemoveLogMgr
 *
 * Resets the pointer to the log manager if it owned by the caller.
 *
 * INPUT   : selectEngine   - Select engine
 *           logMgr         - log manager instance
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSelectRemoveLogMgr(
    IN RvSelectEngine       *selectEngine,
    IN RvLogMgr             *logMgr);


/* The following is used as an internal API for H.323's SELI interface when applicable */
#if (RV_SELECT_TYPE == RV_SELECT_SELECT)
RVCOREAPI 
RvStatus RVCALLCONV RvSelectGetSelectFds(
    IN  RvSelectEngine* selectEngine,
    OUT int*            numFds,
    OUT fd_set*         rdSet,
    OUT fd_set*         wrSet);

RVCOREAPI
RvStatus RVCALLCONV RvSelectHandleSelectFds(
    IN RvSelectEngine*  selectEngine,
    IN fd_set*          rdSet,
    IN fd_set*          wrSet,
    IN int              numFds,
    IN int              numEvents);
#endif /* (RV_SELECT_TYPE == RV_SELECT_SELECT) */
#if ((RV_SELECT_TYPE == RV_SELECT_POLL) || (RV_SELECT_TYPE == RV_SELECT_DEVPOLL))
RVCOREAPI
RvStatus RVCALLCONV RvSelectGetPollFds(
    IN    RvSelectEngine*   selectEngine,
    INOUT RvUint32*         maxFds,
    OUT   struct pollfd*    pollFdSet);

RVCOREAPI
RvStatus RVCALLCONV RvSelectHandlePollFds(
    IN RvSelectEngine*  selectEngine,
    IN struct pollfd*   pollFdSet,
    IN int              numFds,
    IN int              numEvents);
#endif /* ((RV_SELECT_TYPE == RV_SELECT_POLL) || (RV_SELECT_TYPE == RV_SELECT_DEVPOLL)) */

#if (RV_SELECT_TYPE == RV_SELECT_EPOLL)
RVCOREAPI
RvStatus RVCALLCONV RvSelectHandleEpollFds(
    IN RvSelectEngine*  	selectEngine,
    IN struct epoll_event*  epFdSet,
    IN int              	numFds,
    IN int                  numEvents);
#endif /* (RV_SELECT_TYPE == RV_SELECT_EPOLL) */

#if (RV_SELECT_TYPE == RV_SELECT_KQUEUE)

/********************************************************************************************
 * RvSelectKqueueSetRatio
 *
 * Set the proportion of events handling between low and high priority fd's.
 * Events that are detected by the WaitAndBlock loop are handled according
 * to a simple priority policy, i.e. for each 'ratioLow' events from the
 * low priority queue a 'ratioHigh' events from the high priority queue are handled.
 *
 *
 * INPUT   : selectEngine - Events engine constructed previously.
 *           ratioLow     - Ratio for low priority events
 *           ratioHigh    - Ratio for high priority events
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvSelectKqueueSetRatio(
    IN RvSelectEngine*      selectEngine,
    IN RvUint32             ratioLow,
    IN RvUint32             ratioHigh);

/********************************************************************************************
 * RvFdSetGroup
 *
 * Set a group id to a socket (fd struct).
 *
 *
 * INPUT   : fd     - The fd struct constructed by RvFdConstruct.
 *           group  - The group id to assign
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RVCOREAPI
RvStatus RVCALLCONV RvFdSetGroup(
    IN RvSelectFd*              fd,
    IN RvSelectKqueueGroupId    group);

#endif /* RV_SELECT_TYPE == RV_SELECT_KQUEUE */


#if (RV_OS_TYPE == RV_OS_TYPE_NUCLEUS)
void RvSelectSimulateEvent(
	IN RvSelectEngine*      selectEngine,
	IN RvSelectFd*          fd,
	IN RvSelectEvents       selectEvents);

#endif

#if (RV_OS_TYPE == RV_OS_TYPE_MOPI)

RvStatus RvSelectMmbHandleSelectFds(void *selectEngine);
RvStatus rvFdPreempt(
    IN RvSelectEngine   *selectEngine,
    IN RvUint8                message);

#endif


#if defined(__cplusplus)
}
#endif

#endif /* _RV_FD_SELECT_H */

#endif /* (RV_NET_TYPE != RV_NET_NONE) */
