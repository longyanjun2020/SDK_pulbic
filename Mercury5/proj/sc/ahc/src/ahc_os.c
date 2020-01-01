/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_os.h"
#include "mmps_system.h"
//#include "ucos_ii.h"
#include "os_wrap.h"

/*===========================================================================
 * Main body
 *===========================================================================*/ 

//------------------------------------------------------------------------------
//  Function    : AHC_OS_CreateTask
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used to have OS manage the execution of a task.  Tasks can either
              be created prior to the start of multitasking or by a running task.  A task cannot be
              created by an ISR.

@param[in] taskproc : the task function entry pointer
@param[in] task_cfg : pointert to @ref AHC_TASK_CFG structure, that deal with stack top/bottom address and task priority.
@param[in] param : input paramter to the taskproc
@retval 0xFE for bad input priority
        0xFF for createtask internal error from OS
        others, return the priority of the task.
*/
AHC_OS_TASKID AHC_OS_CreateTask(void (*taskproc)(void *param), AHC_OS_TASK_CFG *task_cfg, void *param)
{
    return MMPF_OS_CreateTask(taskproc, (MMPF_TASK_CFG*)task_cfg, (void *)param);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_SetTaskName
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_OS_SetTaskName(UINT8 ubNewPriority, UINT8 *pTaskName)
{
    MMP_UBYTE ubRetVal = 0;
 
   ubRetVal = MMPF_OS_SetTaskName((MMP_UBYTE)ubNewPriority, (MMP_UBYTE *)pTaskName);

    if (ubRetVal != 0) {
        printc("%s,%d error!\r\n", __FUNCTION__, __LINE__);
        return AHC_FALSE;
    }
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_StartTask
//  Description :
//------------------------------------------------------------------------------
/** @brief To start the OS multi-task working.

@return None.
*/
void AHC_OS_StartTask(void)
{
    MMPF_OS_StartTask();
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_ChangeTaskPriority
//  Description :
//------------------------------------------------------------------------------
UINT8 AHC_OS_ChangeTaskPriority(UINT8 ubold_pri, UINT8 ubnew_pri)
{
    return MMPF_OS_ChangeTaskPriority((MMP_UBYTE) ubold_pri, (MMP_UBYTE) ubnew_pri);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_DeleteTask
//  Description :
//------------------------------------------------------------------------------
/** @brief This function allows you to delete a task.  The calling task can delete itself by its own priority number.  
           The deleted task is returned to the dormant state and can be re-activated by creating the deleted task again.

@param[in] taskid : is the task ID to delete.  Note that you can explicitely delete the current task without knowing its 
                    priority level by setting taskid to 0xFF.
@retval 0xFE for bad input task id,
        0xFF for deltask internal error from OS
        0, return delete success.
*/
UINT8 AHC_OS_DeleteTask(AHC_OS_TASKID taskid)
{
    return MMPF_OS_DeleteTask((MMP_UBYTE)taskid);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_CreateSem
//  Description :
//------------------------------------------------------------------------------
/** @brief This function creates a semaphore.

@param[in] ubSemValue : is the initial value for the semaphore.  If the value is 0, no resource is
                        available.  You initialize the semaphore to a non-zero value to specify how many resources are available.
@retval 0xFF for create semaphore internal error from OS
        0xFE the system maximum semaphore counts exceed.
        others, the ID to access the semaphore
*/
AHC_OS_SEMID AHC_OS_CreateSem(UINT8 ubSemValue)
{
    return MMPF_OS_CreateSem(ubSemValue);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_DeleteSem
//  Description :
//------------------------------------------------------------------------------
/** @brief This function deletes a semaphore and readies all tasks pending on the semaphore.

@param[in] ulSemId : The semaphore ID that return by @ref AHC_OS_CreateSem 
@retval 0xFF for delete semaphore internal error from OS
        0, return delete success.
*/

UINT8 AHC_OS_DeleteSem(AHC_OS_SEMID ulSemId)
{
    return MMPF_OS_DeleteSem(ulSemId);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_AcquireSem
//  Description :
//------------------------------------------------------------------------------
/** @brief This function waits for a semaphore.

@param[in] ulSemId : The semaphore ID that return by @ref AHC_OS_CreateSem 
@param[in] ulTimeout : is an optional timeout period (in clock ticks).  If non-zero, your task will
                            wait for the resource up to the amount of time specified by this argument.
                            If you specify 0, however, your task will wait forever at the specified
                            semaphore or, until the resource becomes available.
@retval 0xFE for bad input semaphore id,
        0xFF for acquire semaphore internal error from OS
        0 for getting the resource.
        1 for time out happens
*/

UINT8 AHC_OS_AcquireSem(AHC_OS_SEMID ulSemId, UINT32 ulTimeout)
{
    return MMPF_OS_AcquireSem(ulSemId, ulTimeout);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_ReleaseSem
//  Description :
//------------------------------------------------------------------------------
/** @brief This function signals a semaphore

@param[in] ulSemId : The semaphore ID that return by @ref AHC_OS_CreateSem 
@retval 0xFE for bad input semaphore id,
        0xFF for release semaphore internal error from OS
        0 for getting the resource.
        1 If the semaphore count exceeded its limit.
*/
UINT8 AHC_OS_ReleaseSem(AHC_OS_SEMID ulSemId)
{
    return MMPF_OS_ReleaseSem(ulSemId);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_QuerySem
//  Description :
//------------------------------------------------------------------------------
/** @brief This function obtains count about a semaphore

@param[in] ulSemId : The semaphore ID that return by @ref AHC_OS_CreateSem 
@param[out] usCount : The count of the ulSemId
@retval 0xFE for bad input semaphore id,
        0xFF for query semaphore internal error from OS
        0 for no error
*/
UINT8 AHC_OS_QuerySem(AHC_OS_SEMID ulSemId, UINT16 *usCount)
{
    return MMPF_OS_QuerySem(ulSemId, (MMP_USHORT*)usCount);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_CreateMutex
//  Description :
//------------------------------------------------------------------------------
/** @brief This function creates a mutual exclusion semaphore.

@param[in] ubPriority : is the priority to use when accessing the mutual exclusion semaphore.  In
                            other words, when the semaphore is acquired and a higher priority task
                            attempts to obtain the semaphore then the priority of the task owning the
                            semaphore is raised to this priority.  It is assumed that you will specify
                            a priority that is LOWER in value than ANY of the tasks competing for the
                            mutex.
@retval 0xFF for create semaphore internal error from OS
        0xFE the system maximum semaphore counts exceed.
        others, the ID to access the semaphore
*/
AHC_OS_MUTEXID AHC_OS_CreateMutex(UINT8 ubPriority)
{
    return MMPF_OS_CreateMutex(ubPriority);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_DeleteMutex
//  Description :
//------------------------------------------------------------------------------
/** @brief This function deletes a mutual exclusion semaphore and readies all tasks pending on the it.

@param[in] ulMutexId : The mutex ID that return by @ref AHC_OS_CreateMutex 
@retval 0xFF for delete mutex internal error from OS
        0, return delete success.
*/

UINT8 AHC_OS_DeleteMutex(AHC_OS_MUTEXID ulMutexId)
{
    return MMPF_OS_DeleteMutex(ulMutexId);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_AcquireMutex
//  Description :
//------------------------------------------------------------------------------
/** @brief This function waits for a mutual exclusion semaphore

@param[in] ulMutexId : The mutex ID that return by @ref AHC_OS_CreateMutex 
@param[in] ulTimeout : is an optional timeout period (in clock ticks).  If non-zero, your task will
                            wait for the resource up to the amount of time specified by this argument.
                            If you specify 0, however, your task will wait forever at the specified
                            semaphore or, until the resource becomes available.
@retval 0xFE for bad input mutex id,
        0xFF for acquire mutex internal error from OS
        0 for getting the resource.
        1 for time out happens
*/

UINT8 AHC_OS_AcquireMutex(AHC_OS_MUTEXID ulMutexId, UINT32 ulTimeout)
{
    return MMPF_OS_AcquireMutex(ulMutexId, ulTimeout);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_ReleaseMutex
//  Description :
//------------------------------------------------------------------------------
/** @brief This function signals a mutual exclusion semaphore

@param[in] ulMutexId : The mutex ID that return by @ref AHC_OS_CreateSem 
@retval 0xFE for bad input mutex id,
        0xFF for release mutex internal error from OS
        0 for getting the resource.
*/
UINT8 AHC_OS_ReleaseMutex(AHC_OS_MUTEXID ulMutexId)
{
    return MMPF_OS_ReleaseMutex(ulMutexId);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_CreateEventFlag
//  Description :
//------------------------------------------------------------------------------
UINT8 AHC_OS_CreateEventFlag(UINT32 ulFlagValues)
{
    return MMPF_OS_CreateEventFlagGrp(ulFlagValues);
}


void AHC_OS_Delay(UINT8 hours, UINT8 minutes, UINT8 seconds, UINT16 milli)
{
    //OSTimeDlyHMSM(hours,minutes,seconds,milli);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_WaitFlags
//  Description :
//------------------------------------------------------------------------------
/** @brief This function waits for a semaphore.

@param[in] ulFlagID : The Flag ID that return by @ref AHC_OS_CreateEventFlagGrp 
@param[in] flags : Is a bit pattern indicating which bit(s) (i.e. flags) you wish to wait for.
@param[in] waitType : specifies whether you want ALL bits to be set or ANY of the bits to be set.
                            You can specify the following argument:

                            AHC_OS_FLAG_WAIT_CLR_ALL   You will wait for ALL bits in 'mask' to be clear (0)
                            AHC_OS_FLAG_WAIT_SET_ALL   You will wait for ALL bits in 'mask' to be set   (1)
                            AHC_OS_FLAG_WAIT_CLR_ANY   You will wait for ANY bit  in 'mask' to be clear (0)
                            AHC_OS_FLAG_WAIT_SET_ANY   You will wait for ANY bit  in 'mask' to be set   (1)

                            NOTE: Add AHC_OS_FLAG_CONSUME if you want the event flag to be 'consumed' by
                                  the call.  Example, to wait for any flag in a group AND then clear
                                  the flags that are present, set 'wait_type' to:

                                  AHC_OS_FLAG_WAIT_SET_ANY + AHC_OS_FLAG_CONSUME
@param[in] ulTimeout : is an optional timeout (in clock ticks) that your task will wait for the
                            desired bit combination.  If you specify 0, however, your task will wait
                            forever at the specified event flag group or, until a message arrives.
@param[out] ret_flags : The flags in the event flag group that made the task ready or, 0 if a timeout or an error
        *              occurred.
@retval 0xFE for bad input flag id,
        0xFF for wait flag internal error from OS
        0 for getting the flag.
        1 for time out happens
*/
UINT8 AHC_OS_WaitFlags(AHC_OS_FLAGID ulFlagID, AHC_OS_FLAGS flags, AHC_OS_FLAG_WTYPE waitType, 
                           UINT32 ulTimeout, AHC_OS_FLAGS *ret_flags)
{
    return MMPF_OS_WaitFlags(ulFlagID, flags, waitType, ulTimeout, (MMPF_OS_FLAGS*)ret_flags);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_SetFlags
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is called to set or clear some bits in an event flag group.  The bits to
              set or clear are specified by a 'bit mask'.

@param[in] ulFlagID : The flag ID that return by @ref AHC_OS_CreateEventFlagGrp 
@param[in] flags : If 'opt' (see below) is AHC_OS_FLAG_SET, each bit that is set in 'flags' will
                   set the corresponding bit in the event flag group.
                   If 'opt' (see below) is AHC_OS_FLAG_CLR, each bit that is set in 'flags' will
                   CLEAR the corresponding bit in the event flag group.
@param[in] opt : AHC_OS_FLAG_CLR for flag clear
                 AHC_OS_FLAG_SET for flag set   
                 
@retval 0xFE for bad input semaphore id,
        0xFF for setflag internal error from OS
        0 for calling was successfull
*/

UINT8 AHC_OS_SetFlags(AHC_OS_FLAGID ulFlagID, AHC_OS_FLAGS flags, AHC_OS_FLAG_OPT opt)
{
    return MMPF_OS_SetFlags(ulFlagID, flags, opt);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_CreateMQueue
//  Description :
//------------------------------------------------------------------------------
/** @brief This function creates a message queue if free event control blocks are available.

@param[in] msg : is a pointer to the base address of the message queue storage area.  The
                            storage area MUST be declared as an array of pointers to 'void'.
@param[in] ubQueueSize : is the number of elements in the storage area
@retval 0xFF for create message queue internal error from OS
        0xFE the system maximum message queues counts exceed.
        others, the ID to access the message queue
*/

AHC_OS_MQID AHC_OS_CreateMQueue(void **msg, UINT8 ubQueueSize)
{
    return MMPF_OS_CreateMQueue(msg, ubQueueSize);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_DeleteMQueue
//  Description :
//------------------------------------------------------------------------------
/** @brief This function deletes a message queue and readies all tasks pending on the queue.

@param[in] ulMQId : The message queue ID that return by @ref MMPF_OS_CreateMQueue 
@retval 0xFF for delete message queue internal error from OS
        0, return delete success.
*/

UINT8 AHC_OS_DeleteMQueue(AHC_OS_MQID ulMQId)
{
    return MMPF_OS_DeleteMQueue(ulMQId);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_GetMessage
//  Description :
//------------------------------------------------------------------------------
/** @brief This function waits for a message to be sent to a queue

@param[in] ulMQId : The message queue ID that return by @ref AHC_OS_CreateMQueue 
@param[in] ulTimeout : is an optional timeout period (in clock ticks).  If non-zero, your task will
                            wait for a message to arrive at the queue up to the amount of time
                            specified by this argument.  If you specify 0, however, your task will wait
                            forever at the specified queue or, until a message arrives.
@retval 0xFE for bad message queue id,
        0xFF for acquire message queue internal error from OS
        0 for getting the message.
        1 for time out happens
*/

UINT8 AHC_OS_GetMessage(AHC_OS_MQID ulMQId, void **msg, UINT32 ulTimeout)
{
    return MMPF_OS_GetMessage(ulMQId, msg, ulTimeout);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_PutMessage
//  Description :
//------------------------------------------------------------------------------
/** @brief This function sends a message to a queue

@param[in] ulMQId : The message queue ID that return by @ref AHC_OS_CreateMQueue 
@param[in] msg : is a pointer to the message to send.
@retval 0xFE for bad message queue id,
        0xFF for put message queue internal error from OS
        0 for getting the message.
*/

UINT8 AHC_OS_PutMessage(AHC_OS_MQID ulMQId, void *msg)
{
    return MMPF_OS_PutMessage(ulMQId, msg);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_Sleep
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is called to delay execution of the currently running task until the
              specified number of system ticks expires.  This, of course, directly equates to delaying
              the current task for some time to expire.  No delay will result If the specified delay is
              0.  If the specified delay is greater than 0 then, a context switch will result.

@param[in] usTickCount : is the time delay that the task will be suspended in number of clock 'ticks'.
                        Note that by specifying 0, the task will not be delayed.
@retval 0 always return 0 for success
*/
UINT8 AHC_OS_Sleep(UINT16 usTickCount)
{
    return MMPF_OS_Sleep(usTickCount);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_SleepMs
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is called to delay execution of the currently running task until the
              specified number of system ticks expires.  This, of course, directly equates to delaying
              the current task for some time to expire.  No delay will result If the specified delay is
              0.  If the specified delay is greater than 0 then, a context switch will result.

@param[in] uiMiliSecond : is the time delay that the task will be suspended in mili-seconds.

@retval N/A
*/
void AHC_OS_SleepMs(UINT32 uiMiliSecond)
{
    UINT16 usDelay;

    while (uiMiliSecond > 0)
    {
        usDelay = (uiMiliSecond < 5000) ? uiMiliSecond : 5000;
        MMPF_OS_Sleep_MS(usDelay);
        uiMiliSecond -= usDelay;
    }
}

//------------------------------------------------------------------------------
//  Function    : MMPF_OS_SetTime
//  Description :
//------------------------------------------------------------------------------
/** @brief This function sets the 32-bit counter which keeps track of the number of clock ticks.

@param[in] ulTickCount : specifies the new value that OSTime needs to take.
@retval 0 always return 0 for success
*/
UINT8 AHC_OS_SetTime(UINT32 uiTickCount)
{
    return MMPF_OS_SetTime(uiTickCount);
}

//------------------------------------------------------------------------------
//  Function    : MMPF_OS_GetTime
//  Description :
//------------------------------------------------------------------------------
/** @brief This function sets the 32-bit counter which keeps track of the number of clock ticks.

@param[out] ulTickCount : specifies the new value that OSTime needs to take.
@retval 0 always return 0 for success
*/
UINT8 AHC_OS_GetTime(UINT32 *uiTickCount)
{
    MMPF_OS_GetTime(uiTickCount);
    return 0;   
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_StartTimer
//  Description :
//------------------------------------------------------------------------------
/** @brief This function creates a message queue if free event control blocks are available.

@param[in] ulPeriod : The time (in OS ticks) before the timer expires. If you specified 'AHC_OS_TMR_OPT_PERIODIC' as an option, when the timer expires, it will
                         automatically restart with the same period. 

@param[in] opt : Specifies either: 
                  AHC_OS_TMR_OPT_ONE_SHOT       The timer counts down only once and then is deleted
                  AHC_OS_TMR_OPT_PERIODIC       The timer counts down and then reloads itself
@param[in] callback : Is a pointer to a callback function that will be called when the timer expires.  The
                  callback function must be declared as follows:
                  void MyCallback (OS_TMR *ptmr, void *p_arg);
@param[in] callback_arg : Is an argument (a pointer) that is passed to the callback function when it is called.
@retval 0xFF for start timer internal error from OS
        0xFE the system maximum timer counts exceed.
        others, the ID to access the timer
*/

AHC_OS_TMRID AHC_OS_StartTimer(UINT32 ulPeriod, AHC_OS_TMR_OPT opt, AHC_OS_TMR_CALLBACK callback,
                                void *callback_arg)
{
    return MMPF_OS_StartTimer(ulPeriod, opt, callback, callback_arg);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_StopTimer
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is called by your application code to stop and delete a timer.

@param[in] ulTmrId : The timer ID that return by @ref AHC_OS_StartTimer 

@param[in] opt : Allows you to specify an option to this functions which can be:
                               OS_TMR_OPT_NONE          Do nothing special but stop the timer
                               OS_TMR_OPT_CALLBACK      Execute the callback function, pass it the callback argument
                                                        specified when the timer was created.
@retval 0xFF for start timer internal error from OS
        0, for stop timer sucessfully
*/

UINT8 AHC_OS_StopTimer(AHC_OS_TMRID ulTmrId, AHC_OS_TMR_OPT opt)
{
    return MMPF_OS_StopTimer(ulTmrId, opt);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_CreateMemPool
//  Description :
//------------------------------------------------------------------------------
/** @brief Create memory pool.
@param[in]  bPoolName Pool name.
@param[in]  ulSize Pool size.
@param[in]  ulAddr Pool Base address.
@param[out] pPoolHandler Pool handler.
@return It reports the status of the operation.
*/
AHC_BOOL AHC_OS_CreateMemPool(INT8 *bPoolName, UINT32 ulSize, UINT32 ulAddr, void *pHandler) 
{
    #if defined (ALL_FW)
    #if (MEMORY_POOL_CTL == 1)
    if ( MMP_ERR_NONE != MMPS_System_CreatePool(bPoolName, ulSize, ulAddr, pHandler) ) {
        return AHC_FALSE;
    }
    #endif
    #endif
    
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_Malloc
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used to allocate memory from the memory pool.

@param[in] size : required memory size

@retval memory pointer
*/
void* AHC_OS_Malloc(UINT32 size)
{
    #if (MEMORY_POOL_CTL == 0)
    return NULL;
    #endif
    
    #if defined (ALL_FW)
    #if (MEMORY_POOL_CTL == 1)
    
    MMP_ULONG   MemAddr;
    void*       mem_handle;
    UINT8       *ptr;
    
    MMPS_System_GetPoolHandler(&mem_handle);
    MMPS_System_AllocateMemory(mem_handle,&MemAddr,MMP_TRUE,size, MMPS_SYSTEM_MEM_TOP, MMP_TRUE, NULL, 0);
    
    ptr = (UINT8*)( MemAddr);
    return (void*)(ptr);

    #endif
    #endif
    
    return NULL;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OS_FreeMem
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used to release memory to the memory pool.

@param[in] ptr : memory pointer

*/
void AHC_OS_FreeMem(void* ptr)
{
    #if (MEMORY_POOL_CTL == 0)
    return;
    #endif
    
    #if defined (ALL_FW)
    #if (MEMORY_POOL_CTL == 1)
    
    void*       mem_handle;
    MMP_ULONG   MemAddr = (MMP_ULONG)ptr;
    
    if ( MemAddr != 0 ) {
        MMPS_System_AllocateMemory(mem_handle,&MemAddr,MMP_TRUE, 0 , MMPS_SYSTEM_MEM_TOP, MMP_FALSE, NULL, 0);
    }
    #endif
    
    #endif
}
