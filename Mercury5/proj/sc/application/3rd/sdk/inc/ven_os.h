#ifndef __VEN_OS_H__
#define __VEN_OS_H__
/**
 *
 * @file    ven_os.h
 * @brief   This file defines the os interface definition.
 *
 * @author  Roger.lai
 * @version $Id: ven_os.h 47127 2009-12-10 14:30:38Z steve.lee $
 *
 */

#include "ven_sdk.h"
#include "ven_integration.h"

/*--------------------------------------------------------------------------*/
/* Type Definition                                                          */
/*--------------------------------------------------------------------------*/

enum {
  VEN_OS_OK= 10,                         ///< No error - the function call was successfull
  VEN_OS_NOT_RELEASED= 11,               ///< The bloc was not released
  VEN_OS_UNIT_NOAVAIL= 21,               ///< Not available
  VEN_OS_NO_MESSAGE  = 33,               ///< No message found
  VEN_OS_INVALID_MAILBOX_ID  = 34,               ///< invalid mailbox id
  VEN_OS_INVALID_MAILBOX_OWNER  = 35,               ///< mailbox is not owned by current task
  VEN_OS_INVALID_MAILBOX_THRESHOLD  = 36,               ///< invalid mailbox threshold
  VEN_OS_MAILBOX_OVER_THRESHOLD  = 37,               ///< mailbox reach threshold
  VEN_OS_NON_SATISFACTORY_POOL=   40,    ///< No memory pool found (-deprecated-)
  VEN_OS_NO_MEMORY_AVAIL      =   41,    ///< Not enough memory
  VEN_OS_CLUSTER_OUT_OF_RANGE =   42,    ///<
  VEN_OS_TIMER_NOT_FOUND      =   43,    ///< Invalid timer id
  VEN_OS_MEM_OVERFLOW         =   44,    ///<
  VEN_OS_NULL_RELEASE         =   45,    ///< Try to release a NULL pointer
  VEN_OS_NOT_HEAP_RELEASE     =   46,    ///< Memory zone is not in heap
  VEN_OS_NOT_MEMORY_RELEASE   =   47,     ///< Memory zone is not in pool memory (-deprecated-)
  VEN_OS_MAILBOX_FULL   =   48,     ///< Mailbox is full (-deprecated-)
  VEN_OS_TIMER_EXHAUSTED   =   49,     ///< Timer is unavailable (-deprecated-)
  VEN_OS_MAILBOX_NOT_EXIST = 50,     ///< Mailbox is in initial state since dynamic task is deleted 
  VEN_OS_STACK_ADDRESS_ERROR = (-1), //
  VEN_OS_ENTRY_POINTER_ERROR = (-2),
  VEN_OS_PRIORITY_ERROR = (-3),
  VEN_OS_TASK_EXHAUSTED = (-4),
  VEN_OS_TASK_IDRROR = (-5),
  VEN_OS_TASK_NOT_EXISTED = (-6),
  VEN_OS_TASK_TASK_ALREADY_CREATED = (-7),
  VEN_OS_TASK_PROFILING_NOT_START = (-8),
};
typedef s8 ven_os_ret;


enum 
{
    VEN_OS_THREAD_PRIO_VERY_HIGHT = VEN_TASK_PRIO_3,
    VEN_OS_THREAD_PRIO_HIGHT = VEN_TASK_PRIO_4,        //higher than mmi
    VEN_OS_THREAD_PRIO_MIDDLE = VEN_TASK_PRIO_6,       // lower than mmi
    VEN_OS_THREAD_PRIO_LOW = VEN_TASK_PRIO_9,
    VEN_OS_THREAD_PRIO_VERYLOW = VEN_TASK_PRIO_10,
};
typedef u32 ven_os_thread_priority_e;

typedef void (*ven_os_timeout_callback)(u16);
typedef void (*ven_os_msg_callback)(u32 , void *);

typedef struct
{
    u32 freeBlockcount; ///< Number of free block
    u32 usedBlockCount; ///< Number of used block
    u32 freeSize;       ///< Total free size
    u32 usedSize;       ///< Total used size
    u32 maxUsedSize;    ///< Max used size
    u32 totalSize;      ///< Total size
    u32 maxFreeBlock;   ///< The size of max free block
} ven_os_heap_status_t;

typedef struct
{
    u16 ClusterNum; //the number of clusters
    u16 ClusterSize;    //the cluster size
} venPDesc_t, *pvenPDesc_t;

typedef u8 ven_os_thread_id;
typedef void * ven_os_thread_handle;   

/*--------------------------------------------------------------------------*/
/* Public Function Definition                                               */
/*--------------------------------------------------------------------------*/

/**
 *  ven_os_msg_cb_register
 *
 *  @brief  Register to SDK for recieve message
 *
 *  @param  sdkHandle    [in] The handle of SDK get from ven_handle_open()
 *  @param  msgCb        [in] Pointer to the function to receive messge
 *
 *  @retval 1  if success
 *          -1 if failed
 *
 */
s32 ven_os_msgCbRegister(u32 sdkHandle, ven_os_msg_callback msgCb);


/**
 *  ven_os_msgCbUnRegister
 *
 *  @brief  UnRegister for recieve message
 *
 *  @param  sdkHandle    [in] The handle of SDK get from ven_handle_open()
 *
 *  @retval 1  if success
 *          -1 if failed
 *
 */
s32 ven_os_msgCbUnRegister(u32 sdkHandle);


/**
 *  ven_os_sendMessage
 *
 *  @brief  Send a message
 *
 *  @param  sourceHandle        [in] Handle used to send FROM Vendor SDK
 *  @param  destinationHandle   [in] Handle used to send TO Vendor SDK
 *  @param  pMsg                [in] message to sent
 *
 *  @retval  1    if success
 *           -1   if failed
 */
s32 ven_os_sendMessage(u32 sourceHandle, u32 destinationHandle, void *pMsg);


/**
 *  ven_os_getOSTick
 *
 *  @brief  get OS tick
 *
 *
 *  @retval current value of OS-tick
 */
u32 ven_os_getOSTick(void);


/**
 *  ven_os_getSemaphoreID
 *
 *  @brief  get semaphore id
 *
 *
 *  @retval semaphore id
 */
u32 ven_os_getSemaphoreID(void);


/**
 *  ven_os_freeSemaphoreID
 *
 *  @brief  free semaphore id
 *
 *  @param  semaphoreID [in] semaphore id
 *
 *  @retval  1  if success
 *          -1  if failed
 */
s32 ven_os_freeSemaphoreID(u32 semaphoreID);


/**
 *  ven_os_initialSemaphore
 *
 *  @brief  Semaphore initialisation
 *
 *  @param  semaphoreID      [in]semaphore id
 *  @param  initial_value    [in]semaphore value
 *
 *  @retval  1 if success
 *          -1 if failed
 */
s32 ven_os_initialSemaphore(u32 semaphoreID, u32 initial_value);


/**
 *  ven_os_semaphoreProduce
 *
 *  @brief  Take Semaphore
 *
 *  @param  semaphoreID      [in]semaphore id
 *
 *  @retval  1 if success
 *          -1 if failed
 */
s32 ven_os_semaphoreConsume(u32 semaphoreID);


/**
 *  ven_os_semaphoreProduce
 *
 *  @brief  Give back the Semaphore
 *
 *  @param  semaphoreID      [in]semaphore id
 *
 *  @retval  1 if success
 *          -1 if failed
 */
s32 ven_os_semaphoreProduce(u32 semaphoreID);


/**
 *  ven_os_semaphoreConsumeDelay
 *
 *  @brief  Take the semaphore if available or wait for a bounded time.
 *
 *  If the semaphore is already available, take it and return immediately.
 *  Otherwise wait on it. If the caller was not woken up after a certain
 *  amount of time, make the call return.
 *
 *  @param  semaphoreID      [in] semaphore id
 *  @param  timout_ms        [in] max time(milli-second) to wait for the semaphore
 *
 *  @retval 1 if the semaphore is obtained
 *          0 if the timer expired
 *          -1 if failed
 */
s32 ven_os_semaphoreConsumeDelay(u32 semaphoreID, u32 timout_ms);

/**
 *  ven_os_getSemaphoreCount
 *
 *  @brief  Get the number of semaphore counts.
 *
 *  @param  semaphoreID      [in] semaphore id
 *  @param  pSemCount        [out] the number of semaphore counts
 *
 *  @retval 1 if success
 *          -1 if failed
 */
s32 ven_os_getSemaphoreCount(u32 semaphoreID, s16 *pSemCount);

/**
 *  ven_os_createTimer
 *
 *  @brief  create a timer and register timeout callback
 *
 *  @retval  timer id if success
 *           0        if failed
 */
u16 ven_os_createTimer(ven_os_timeout_callback timeout);

/**
 *  ven_os_createTimer
 *
 *  @brief  release a timer and stop it
 *
 *  @param  TimerId      [in] Timer id
 *
 *  @retval  1 if success
 *          -1 if failed
 */
s32 ven_os_releaseTimer(u16 TimerId);


/**
 *  ven_os_startTimer
 *
 *  @brief  Start a timer
 *
 *  @param  TimerId      [in] Timer id
 *  @param  bCyclic      [in] Periodic timer enable or not
 *  @param  nHandle      [in] Application Handle Id
 *  @param  time_ms      [in] Timer value (milli-second)
 *
 *  @retval  1    if success
 *           -1   if failed
 */
s32 ven_os_startTimer(u16 TimerId, bool bCyclic, u32 nHandle, u32 time_ms);


/**
 *  ven_os_createTimer
 *
 *  @brief  Stop a timer
 *
 *  @param  TimerId      [in] Timer id
 *
 *  @retval  Upon service successful completion, the function
 *           shall return a null or a positive value, otherwise it shall
 *           return a negative error value.
 *
 */
u32 ven_os_stopTimer(u16 TimerId);


/**
 *  ven_os_IsTimerActive
 *
 *  @brief  check the timer active by TimerId
 *
 *  @param  TimerId      [in] Timer id
 *
 *  @retval  1 if time is active
 *           0 else
 *
 */
s32 ven_os_isTimerActive(u16 TimerId);

/**
 *  ven_os_mem_malloc
 *
 *  @brief  allocate memory space
 *
 *  @param  Size      [in] Memory size
 *
 *  @retval  memory address if success
 *           NULL else
 *
 */
void * ven_os_mem_malloc(s32 Size);

/**
 *  ven_os_mem_lr_malloc
 *  ONLY FOR MStar INTERNAL USE
 */
void * ven_os_mem_lr_malloc(s32 Size, s32 lr);

/**
 *  ven_os_mem_realloc
 *
 *  @brief  reallocate memory space
 *
 *  @param  pData    [in] Memory address
 *
 *  @param  Size     [in] Memory size
 *
 *  @retval  memory address if success
 *           NULL else
 *
 */

void * ven_os_mem_realloc(void* pData, s32 Size);

/**
 *  ven_os_mem_lr_realloc
 *  ONLY FOR MStar INTERNAL USE
 */
void * ven_os_mem_lr_realloc(void* pData, s32 Size, s32 lr);

/**
 *  ven_os_mem_free
 *
 *  @brief  free memory space, please set pData to NULL after calling this api.
 *
 *  @param  pData      [in] memory address to free
 *
 *  @retval  void
 *
 */
void ven_os_mem_free(void *pData);


/**
 *  ven_os_hmem_create
 *
 *  @brief  create a memory handle
 *
 *  @param  pBuf        [in] buffer address
 *  @param  nBufSize  [in] buffer size
 *
 *  @retval  handle (>0) if success, 0 else.
 *
 */
u32 ven_os_hmem_create(void* pBuf, u32 nBufSize);


/**
 *  ven_os_hmem_close
 *
 *  @brief  close a memory handle
 *
 *  @param  Handle     [in] memory handle
 *
 *  @retval  void
 *
 */
void ven_os_hmem_close(s32 Handle);


/**
 *  ven_os_hmem_poolinit
 *
 *  @brief  initialize a pool in the memory handle
 *
 *  @param  Handle       [in] memory handle
 *  @param  pDesc        [in] pool description table
 *  @param  nPoolNum  [in] pool description table size
 *
 *  @retval  1 if success, 0 else.
 *
 */
s32 ven_os_hmem_poolinit(s32 Handle, pvenPDesc_t pDesc, u32 nPoolNum);


/**
 *  ven_os_hmem_malloc
 *
 *  @brief  allocate a memory with given size in the memory handle
 *
 *  @param  Handle       [in] memory handle
 *  @param  nMemSize  [in] memory size
 *
 *  @retval  memory address if success, NULL else.
 *
 */
void* ven_os_hmem_malloc(s32 Handle, u32 nMemSize);


/**
 *  ven_os_hmem_realloc
 *
 *  @brief  reallocate a memory with given size in the memory handle
 *
 *  @param  Handle       [in] memory handle
 *  @param  pMem        [in] old memory address
 *  @param  nMemSize  [in] new memory size
 *
 *  @retval  memory address if success, NULL else.
 *
 */
void* ven_os_hmem_realloc(s32 Handle, void* pMem, u32 nMemSize);


/**
 *  ven_os_hmem_free
 *
 *  @brief  release the memory in the memory handle
 *
 *  @param  Handle       [in] memory handle
 *  @param  pMem        [in] memory address
 *
 *  @retval  void
 *
 */
void ven_os_hmem_free(s32 Handle, void *pMem);


/**
 *  ven_os_sleep
 *
 *  @brief  uspends calling task for duration ms
 *
 *  @param  duration      [in] sleep duration in ms
 *
 *  @retval  void
 *
 */
void ven_os_sleep(u32 duration);

/**
 *  ven_os_invalidate_data_cache
 *
 *  @brief  invalidate and flush system data cache
 *
 *  @param  void
 *
 *  @retval  void
 *
 */
void ven_os_invalidate_data_cache(void);

/**
 *  ven_os_invalidate_inst_cache
 *
 *  @brief  clear system instruction cache
 *
 *  @param  void
 *
 *  @retval  void
 *
 */
void ven_os_invalidate_inst_cache(void);

/**
 *  ven_os_queryHeapStatus
 *
 *  @brief  Query current heap status
 *
 *  @param  pHeapStatus      [out] Pointer to store the heap status
 *
 *  @retval  1    if success
 *           -1   if failed
 *
 */
s32 ven_os_queryHeapStatus(ven_os_heap_status_t *pHeapStatus);

/**
 *  ven_os_tick2ms
 *
 *  @brief  convert tick to time (milliseconds)
 *
 *  @param  tick      [in] the tick value to be converted to time
 *
 *  @retval the conversion result of input tick.
 *           
 *
 */
u32 ven_os_tick2ms(u32 tick);

/**
 *  ven_os_ms2tick
 *
 *  @brief  convert time (milliseconds) to tick.
 *
 *  @param  ms      [in] the time value to be converted to tick.
 *
 *  @retval the conversion result of input time.
 *  
 */
u32 ven_os_ms2tick(u32 ms);

/**
 *  ven_os_ThreadCreate
 *
 *  @brief  create a task
 *
 *  @param  pThreadName      [in] the given thread name.
 *  @param  AppliInit        [in] the entry function point.
 *  @param  Priority         [in] thread priority, please refer to ven_os_thread_priority_e
 *  @param  pStackTop        [in] base address of given thread stack, user provide.
 *  @param  StackSize        [in] byte size of given stack.
 *  @param  pInitData        [in] init data of entry function.
 *  @param  ThreadId         [out] the output thread id.
 *  @param  TimeSlice        [in]  not used now, just reserve.
 *
 *  @retval VEN_OS_TASK_NOT_EXISTED , if fail
 *          VEN_OS_OK               , if success
 *  
 */
ven_os_thread_handle  ven_os_ThreadCreate(char* pThreadName,
                void (*AppliInit) (void * ),
                ven_os_thread_priority_e  Priority,
                u32 *pStackTop,
                u32 StackSize,
                void *pInitData,
                ven_os_thread_id *ThreadId,
                u16 TimeSlice);

/**
 *  ven_os_ThreadStart
 *
 *  @brief  start task
 *
 *  @param  handle      [in] the handle of task.
 *
 *  @retval VEN_OS_TASK_NOT_EXISTED , if fail
 *          VEN_OS_OK               , if success
 *  
 */
ven_os_ret ven_os_ThreadStart(ven_os_thread_handle handle);

/**
 *  ven_os_ThreadDestroy
 *
 *  @brief  destroy task
 *
 *  @param  handle      in] the handle of task.
 *
 *  @retval VEN_OS_TASK_NOT_EXISTED , if fail
 *          VEN_OS_OK               , if success
 *  
 */
ven_os_ret ven_os_ThreadDestroy(ven_os_thread_handle handle);

/**
 *  ven_os_CurrThread
 *
 *  @brief  convert time (milliseconds) to tick.
 *
 *
 *  @retval the corresponding task id.
 *  
 */ven_os_thread_id ven_os_CurrThread(void);

#endif // __VEN_OS_H__

