/****************************************************************************/
/*  File    : rtk.ho                                                        */
/*--------------------------------------------------------------------------*/
/*  Scope   : RTK exports                                                   */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*                                                                          */
/*  Historical :                                                            */
/****************************************************************************/

/*!
 *   \file sys_rtk_ho.h
 *
 *   \brief public rtk include file
 *
 *   this file defines the public interface of RTK
 *
 */

#ifndef __SYS_RTK_HO_H__
#define __SYS_RTK_HO_H__


#include "comdefs.hc"   /* Common define flags */
#include "stdcomp.h"
#include <stdarg.h>
#include "sys_rtk_vmrtkho.h"
#include "sys_rtk_config.h"

#ifdef __SDK_SIMULATION__

#ifdef __RTK_DATA__
#define RtkDefExtern
#else //__RTK_DATA__

#ifdef _MKSYS
#define RtkDefExtern    extern
#else //_MKSYS
#define RtkDefExtern    __declspec(dllimport)
#endif //#ifdef _MKSYS

#endif // __RTK_DATA__

#else // __SDK_SIMULATION__

#ifdef __RTK_DATA__
#define RtkDefExtern
#else
#define RtkDefExtern    extern
#endif

#endif // __SDK_SIMULATION__

/******* Return status parameters *******/

/*!
 *      \brief Rtk error codes. These values are returned by most of the RTK functions
 */
typedef enum {
    RTK_OK                    = 10,   ///< No error - the function call was successfull
    RTK_NOT_RELEASED          = 11,   ///< The bloc was not released
    RTK_UNIT_NOAVAIL          = 21,   ///< Not available
    RTK_NO_MESSAGE            = 33,   ///< No message found
    RTK_NON_SATISFACTORY_POOL = 40,   ///< No memory pool found (-deprecated-)
    RTK_NO_MEMORY_AVAIL       = 41,   ///< Not enough memory
    RTK_CLUSTER_OUT_OF_RANGE  = 42,   ///<
    RTK_TIMER_NOT_FOUND       = 43,   ///< Invalid timer id
    RTK_MEM_OVERFLOW          = 44,   ///<
    RTK_NULL_RELEASE          = 45,   ///< Try to release a NULL pointer
    RTK_NOT_HEAP_RELEASE      = 46,   ///< Memory zone is not in heap
    RTK_NOT_MEMORY_RELEASE    = 47,   ///< Memory zone is not in pool memory (-deprecated-)
    RTK_MAILBOX_FULL          = 48,   ///< Mailbox is full (-deprecated-)
    RTK_TIMER_EXHAUSTED       = 49,   ///< Timer is unavailable (-deprecated-)
    RTK_MAILBOX_NOT_EXIST     = 50,   ///< Mailbox is in initial state since dynamic task is deleted
    RTK_IN_INTERRUPT          = 51,
    RTK_STACK_ADDRESS_ERROR   = (-1),
    RTK_ENTRY_POINTER_ERROR   = (-2),
    RTK_PRIORITY_ERROR        = (-3),
    RTK_TASK_EXHAUSTED        = (-4),
    RTK_TASK_ID_ERROR         = (-5),
    RTK_TASK_NOT_EXISTED      = (-6),
    RTK_TASK_ALREADY_CREATED  = (-7),
} _rtk_ErrCode_e;

typedef u8 rtk_ErrCode_e;
/*!
 *    \brief memory area type
 */
typedef enum {
  RTK_GEN_NOT_DYNAMIC_MEMORY,    ///< Not a dynamic memory area
  RTK_GEN_HEAP_STACK,            ///< Stack's Heap zone
  RTK_GEN_POOL_STACK,            ///< Stack'sPool memory area (-deprecated-)
  RTK_GEN_HEAP_CUS,              ///< Customer's heap zone
  RTK_GEN_POOL_CUS,              ///< Customer's pool area (-deprecated-)
  RTK_GEN_HEAP_OPEN_AT           ///< Open AT heap zone
}rtk_MemoryAreaType_e;


/*!
 *   \brief exceptions
 */
typedef enum {
  R2_BUS_ERROR =                        12,
  R2_DATA_PAGE_FAULT =                  13,
  R2_INSTRUCTION_PAGE_FAULT =           14,
  R2_ALIGNMENT_FAULT =                  16,
  R2_ILLEGAL_INSTRUCTION =              17,
  R2_DTLB_MISS =                        19,
  R2_ITLB_MISS =                        20,
  R2_UNKNOWN_VECTOR =                   29,
  //woody test for dbb exception temp solution
  R2_DBB_ASSERT =					30, ///<

  RTK_NO_TIMER_AVAIL =                  90, ///<   No more timers available
  RTK_CLEAR_TIMER =                     94, ///<

  RTK_BAD_TASK_STATE =                  110, ///< Invalid task state
  RTK_BAD_TASK_NUMBER =                 111, ///< Invalid task number
  RTK_BAD_PRIORITY =                    112, ///< Invalid task priority
  RTK_TASK_NOT_INITIALIZED =            113, ///<
  RTK_TASK_ALREADY_STARTED =            114, ///< Task already started
  RTK_TASK_IN_NON_OPSTATE =             115, ///<
  RTK_MBX_NON_ALLOWED_OPBGT =           116, ///< invalid task (idle-task)
  RTK_SEM_NON_ALLOWED_OPBGT =           117, ///< invalid task (idle-task)

  RTK_COUNTER_OVERFLOW =                120, ///< Region Counter overflowed
  RTK_COUNTER_UNDERFLOW =               121, ///< Region Counter underflowed

  RTK_BAD_SEM_NUMBER =                  130, ///< Invalid semaphore identifier
  RTK_SEM_INIT_ERROR =                  131,
  RTK_SEM_OVERFLOW =                    133, ///< Semaphore counter overflowed
  RTK_SEM_UNDERFLOW =                   134, ///< Semaphore counter undeflowed
  RTK_SEM_TIMEOUT =                     136, ///< Semaphore consume timed out
  RTK_SEM_TIMER_ERROR =                 137, ///< Error on a semaphore's timer
  RTK_SEM_TIMER_USED_ERROR =            138, ///<
  RTK_SEM_STOP_TIMER_ERROR =            139, ///<

  RTK_BAD_MAILBOX_NUMBER =              140, ///< Invalid mailbox identifier
  RTK_OBJECT_OVERFLOW =                 144, ///<

  RTK_POOL_ID_ERROR =                   149, ///< Invalid pool identifier (-deprecated-)
  RTK_OUT_OF_MEMORY_WITH_SIZE =         150, ///< No more memory
  RTK_OUT_OF_MEMORY_WITH_POOL_ID =      151, ///< No more memory
  RTK_DESTROYED_MEMORY =                152, ///<
  RTK_NO_MEMORY_AVAILLABLE =            153, ///<
  RTK_NULL_PTR_RELEASE =                154, ///< Tried to release a null address
  RTK_DESTROYED_POOL =                  155,

  RTK_MEMORY_SIZE_ERROR_WITH_SIZE =     156, ///< Invalid memory size
  RTK_MEMORY_SIZE_ERROR_WITH_POOL_ID =  157, ///< Invalid memory size
  RTK_DESTROYED_CLUSTER =               158, ///<
  RTK_DESTROYED_HEAP =                  159, ///<
  RTK_BAD_HEAP_RELEASE =                161, ///<
  RTK_REL_MEMGLB_FAIL =                 163, ///<
  RTK_REL_MEMORY_FAIL =                 164, ///<
  RTK_UNKNOWN_REGION  =                 165, ///< pointer not in stack pool nore in custo pool

  RTK_BAD_TIMER_PERIOD =                171, ///<
  RTK_BAD_EXTRACTION_TIMER =            173, ///<

  RTK_MEMORY_HANDLE_FATAL =          174,
  RTK_MEMORY_HANDLE_INVALID =          175,

  RTK_EMI_PROTECT_POOL_DESTROYED =   176, ///<emi controller detect a destroyed pool cluster

  RTK_NULL_PTR_SEND =                   180, ///<
  RTK_STACK_OVERFLOW =                  190, ///<
  SYS_STACK_CORRUPT =                   191, ///<
  ISR_STACK_CORRUPT =                   192, ///<
  SUV_STACK_CORRUPT =                   193, ///<
  TASK_STACK_CORRUPT =                  194, ///<
  FIQ_STACK_CORRUPT =                   195, ///<
  RTK_NO_STARTABLE_TASK =               200, ///<

  //for __INTERRUPT_INTEGRITY_PROTECT__
  IDLE_SCHEDULE_INTERRUPT_CORRUPT =     201,
  ISR_INTERRUPT_CORRUPT =               202,
  SYSCALL_INTERRUPT_CORRUPT =           203,
  DISABLE_INTERRUPT_TIME_OUT =          204,
  SW_WATCHDOG_TIMEOUT =                 205,

	RTK_MAILBOX_OVERFLOW =								210, ///<
	MMP_COMMAND_TIMEOUT =									220, ///<
	MMI_KERNEL_FATAL_ERROR =							230, ///<
	SYSTEM_ASSERT =												240, ///<
	HW_WATCHDOG_TIMEOUT=                  244,
	RTK_BRANCH_ZERO = 										245, ///<
	RTK_DATA_ABORT =											246, ///<
	RTK_PREFETCH_ABORT = 									247, ///<
	RTK_UNDEFINED_INSTRUCTION = 					248, ///<
	RTK_BAD_MUTEX_EXCEPTION =           249,
	RTK_SLDLM_DATA_ABORT =           250,
	RTK_SLDLM_PREFETCH_ABORT =           251,
	RTK_UNDEFINED_EXCEPTION
} rtk_Exception_e;



// TODO: Move to appropriate place
#if defined(__INTERRUPT_INTEGRITY_PROTECT__)
// Types for IDLE_SCHEDULE_INTERRUPT_CORRUPT
#define CPSR_IBIT_ERR_MASK              (1<<0)
#define IRQC_FINT_ERR_MASK              (1<<1)
#define TBUC_FINT_ERR_MASK              (1<<2)
#define API_PAIR_USR_ERR_MASK           (1<<3)
#define API_PAIR_KER_ERR_MASK           (1<<4)
#define QB_COUNT_EXCEED_ERR_MASK        (1<<5)
#define TICK_COUNT_EXCEED_ERR_MASK      (1<<6)

#define SCHEDULE_CHECK_ERR_MASK         (1<<31) // 0 from idle check, 1 from schedule check
#define TICK_COUNT_CHECK_ERR_MASK       (1<<31) // 0 from QB check, 1 from tick check
#endif // __INTERRUPT_INTEGRITY_PROTECT__

typedef enum {
  RTK_PTR_STACK = 1,                  /// Pointer on a stack Pool
  RTK_PTR_CUSTO = 2,                  /// Pointer on a custo Pool
  RTK_PTR_AUX   = 3                  /// Pointer on a custo Pool
} rtk_PtrRegion_e;
/****** Received messages *********************/

/* Even though this value is mostly used in rtk_Task_t.TypeOfObj
   there are parts of the cause where it must be a one-bit boolean
   (see TypeOfEnv in Rtk10TimerExtract() for instance).
   So we use RTK_OBJ_MESSAGE for both mail-boxes and semaphores
   since a task cannot be waiting on both at the same time
   but both may be interrupted by the expiration of a timer.
*/

/*!
 *  \brief type of an object
 */
typedef enum {
  RTK_OBJ_MESSAGE =                      0,  ///< Object is a message
  RTK_OBJ_TIMER =                        1,   ///< Object is a timer
  RTK_OBJ_EVENT=                        2 ///< Object is an event
} rtk_ObjectType_e;

#define	RTK_FORCE_SUSPEND				(0xFFFFFFFF)
#define	RTK_FORCE_ASSERT				(0xFFFFFFFE)

#if defined(__TIME_SLICE_SCHEDULE__)
#define RTK_SCHEDULE_TIMER_ID           (0xFFFFFFFE)
#endif

#ifdef __REMOTE_RTK__

/****** Type of remote mailboxes *************/

#define RTK_REMOTE_MBX                         0x01
#define RTK_LOCAL_MBX                          0x02
#endif

/*********************** some timer values ***************************/
/*!
 *   \brief Rtk tick time (integer approximation)
 */
#define RTK_TICK_TIME         VM_RTK_TICK_TIME
/*!
 *   \brief Rtk tick time (float value)
 */
#define RTK_TICK_TIME_REAL    VM_RTK_TICK_TIME_REAL
/*!
 *   \brief TDMA frame delay
 */
#define RTK_TDMA_FRAME_DELAY  4.615
/*!
 *   \brief macro to convert milli seconds to ticks
 */
#define RTK_MS_TO_TICK(MsT)   VM_RTK_MS_TO_TICK(MsT)
#define RTK_MS_TO_TICK_64(MsT)   VM_RTK_MS_TO_TICK_64(MsT)
/*!
 *   \brief macro to convert seconds to ticks
 */
#define RTK_S_TO_TICK(SecT)   VM_RTK_S_TO_TICK(SecT)
/*!
 *   \brief macro to convert minuts to ticks
 */
#define RTK_MN_TO_TICK(MnT)   VM_RTK_MN_TO_TICK(MnT)
/*!
 *   \brief macro to convert Ticks to s
 */
#define RTK_TICK_TO_S(_tick_)   VM_RTK_TICK_TO_S(_tick_)
/*!
 *   \brief macro to convert Ticks to ms
 */
#define RTK_TICK_TO_MS(_tick_)   VM_RTK_TICK_TO_MS(_tick_)
/*!
 *   \brief Rtk tick time (float value)
 */
#define RTK_TICK_TIME_REAL    VM_RTK_TICK_TIME_REAL
/*!
 *   \brief macro to convert TDMA frame to ticks
 */
#define RTK_FRAME_TO_TICK(F)  VM_RTK_FRAME_TO_TICK(F)
/*!
 *   \brief macro to convert ticks to TDMA frame
 */
#define RTK_TICK_TO_FRAME(T)  VM_RTK_TICK_TO_FRAME(T)
/*!
 *   \brief maximum value for an RTK timer
 */
#define RTK_MAXTIMER_VALUE      VM_RTK_MAXTIMER_VALUE

/******* Structure returned by Receive and TestReceive *******/

/*!
 *  \brief object structure ( as returned by \ref RtkReceive functions )
 */
typedef struct ObjDescriptorStructure {
  u8 TypeOfObj;      ///< type of object (\ref rtk_ObjectType_e)
  u8 Bid;            ///< Bid
  union  {
    u32   TimerID;   ///< Identifier of a timer object
    void  *Message;  ///< Message content of a message object
  }ReceivedObj;      ///< Received object content
} rtk_ObjDesc_t;


struct rtk_KernelInit;
struct rtk_TaskInit;
struct TaskStructure;

/******* Envelop Structure *******/

/*!
 *  \brief enveloppe structure
 */
typedef struct EnvStructure {
	struct EnvStructure *PtrNextEnv;               ///< Pointer to next enveloppe of an  envelopped linked array
	union  {
		u32      TimerID;                                 ///< Timer identifier
		u8       *PtrMessageObj;                    ///< Pointer to a message
		struct   TaskStructure  *PtrTaskObj;  ///< Pointer to a Task structure
		void     *PtrQueueObj;                       ///< Pointer to a queue
		struct   FlagStructure   *PtrFlagObj;   ///< Pointer to a flag structure
		struct   MutexStructure   *PtrMutexObj; ///< Pointer to a mutex structure
	}PtrObject;                                                ///< object's content
	u32 lr;                                                         /// caller function
	u32 flag;                                                     /// additional debug info
}rtk_Envelop_t;

#define LEN_rtk_Envelop_t sizeof (rtk_Envelop_t )

/******* Structure for Queue management ***********/

/*!
 *   \brief queue structure
 */
typedef struct {
  rtk_Envelop_t  *First; ///< First element of the queue
  rtk_Envelop_t *Last;   ///< Last element of the queue
  u32 count;
} rtk_Queue_t;

/*!
 *   \brief used with \ref RTK2_DISABLE to store the it mask
 */
#if defined(__SEPARATE_INTERRUPT_API__)
typedef u64 rtk_MaskImage_t;
#else
typedef  u32  rtk_MaskImage_t;
#endif
/*!
 *   \brief used with \ref RTK2_DISABLE to store the it mask
 */
typedef  rtk_MaskImage_t rtk_ItMask_t;

/*!
 *   \brief timer identifier type
 */
typedef u32 rtk_TimerId_t;
/*!
 *   \brief task identifier type
 */
typedef u8 rtk_TaskId_t;

/*!
 *  \brief mailbox identifier type
 */
typedef u8 rtk_MailboxId_t;

/*!
 *  \brief semaphore identifier type
 */
typedef u16 rtk_SemId_t;


/*!
 *   \brief heap status structure
 */
typedef struct
{
    u32 freeBlockcount;
    u32 usedBlockCount;
    u32 freeSize;
    u32 usedSize;
    u32 maxUsedSize;
    u32 totalSize;
    u32 maxFreeBlock;
} rtk_Heap_Status_t;

/*!
 *   \brief virtual memory block structure
 */
typedef struct vmb_struct
{
    u32 size;
    void *next;
} vmb_struct_t;

#ifdef __SDK_SIMULATION__
#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus
#endif   // __SDK_SIMULATION__

/* ------------------------------------------------------------------------*/
/*              C RTK prototype interface functions                        */
/* ------------------------------------------------------------------------*/

  /*!
   *   \fn bool RtkMailboxStatus (rtk_MailboxId_t MboxNo, u32 *limit, u32 * max, u32 * current)
   *
   *   \get rtk mailbox status information
   *
   *   \param MboxNo the mailbox identifier
   *   \param limit  the limitation number of this mailbox
   *   \param max    the max unprocessed number of this mailbox
   *   \param current the current messge number of this mailbox
   *
   *   \return TRUE if MboxNo is correct
   *   \return FALSE if MboxNo is invalid or error occurs
   *
   */
  extern bool RtkMailboxStatus (rtk_MailboxId_t MboxNo, u32 *limit, u32 * max, u32 * current);

  /*!
   *    \fn void RTK2_ENABLE(rtk_ItMask_t itmask)
   *
   *    \brief enable back interruptions using the specified mask (\ref RTK2_DISABLE )
   *
   *    \param itmask the interruptions mask to restore
   *
   *    \return void
   */
  void           RTK2_ENABLE(rtk_ItMask_t itmask);
#if defined(__SEPARATE_INTERRUPT_API__)
  void           RTK2_ENABLE_K(rtk_ItMask_t itmask);
#else
#define RTK2_ENABLE_K(itmask) RTK2_ENABLE(itmask)
#endif

  /*!
   *    \fn rtk_ItMask_t   RTK2_DISABLE()
   *
   *    \brief disable interruptions and return previous interruptions mask
   *
   *    \return the interruptions mask to use with \ref RTK2_ENABLE to restore interruptions
   */
  rtk_ItMask_t   RTK2_DISABLE(void);
#if defined(__SEPARATE_INTERRUPT_API__)
  rtk_ItMask_t   RTK2_DISABLE_K(void);
#else
#define RTK2_DISABLE_K RTK2_DISABLE
#endif

#if !defined(__SDK_SIMULATION__)
#ifdef __FIXME__
void RTK2_ENABLE_K_R(rtk_ItMask_t itmask);
rtk_ItMask_t RTK2_DISABLE_K_R(void);
#endif
#endif

  /*!
   *    \fn rtk_ItMask_t   RTK2_DISABLE_IRQ()
   *
   *    \brief disable interruptions (only IRQ, not FIQ) and return previous interruptions mask
   *
   *    \return the interruptions mask to use with \ref RTK2_ENABLE to restore interruptions
   */
  rtk_ItMask_t   RTK2_DISABLE_IRQ(void);
void RTK2_ENABLE_IRQ(rtk_ItMask_t itmask);
  //////////////////////////////////////////////////////////////////////////
  //  QUEUE FUNCTIONS
  //////////////////////////////////////////////////////////////////////////

  /*!
   *    \fn rtk_ErrCode_e RtkQueue(rtk_Queue_t *Q, void *E);
   *
   *    \brief Enqueue an item at the end of the specified queue
   *    \param Q a \ref rtk_Queue_t pointer defining the queue
   *    \param E the element to enqueue
   *    \return RTKOK
   *
   */
  rtk_ErrCode_e  RtkQueue( rtk_Queue_t *, void * );

  /*!
   *   \fn rtk_ErrCode_e RtkQueueFirst(rtk_Queue_t *Q, void *E);
   *
   *   \brief Enqueue an item at the beginning of the queue
   *   \param Q a \ref  rtk_Queue_t pointer that specifies the queue
   *   \param E a pointer to the element to insert.
   *
   *   \return RTK_OK
   */
  rtk_ErrCode_e RtkQueueFirst(rtk_Queue_t *Q, void *E);

  /*!
   *    \fn void * RtkDeQueue(rtk_Queue_t *Q);
   *    \brief Remove the first element of a queue
   *
   *    \param Q a \ref rtk_Queue_t pointer that specifies the queue
   *    \return  a pointer to the element that was removed from the queue
   */
  void      *RtkDeQueue( rtk_Queue_t * );

#if 0
  // not implemented in rtk9que.c
  u8        RtkInsertQueue( rtk_Queue_t *, void *, void * );
#endif

  /*!
   *   \fn rtk_ErrCode_e  RtkDeleteQueue(rtk_Queue_t *Q,void *E_REF);
   *
   *   \brief remove the specified element from a queue
   *
   *   \param Q a \ref rtk_Queue_t pointer that defines the queue
   *   \param E_REF a pointer to the item to be removed
   *   \return \li RTK_OK if the element was succesfully removed
   *           \li FALSE  if the element does not belong to the queue
   */
  rtk_ErrCode_e        RtkDeleteQueue ( rtk_Queue_t *, void * );

  /*!
   *    \fn void RtkInitQueue(rtk_Queue_t* Q);
   *
   *    \brief Init the given queue, if not NULL
   *    \param Q a \ref rtk_Queue_t pointer defining the queue
   *    \return none
   *
   */
#ifndef NULL
#define NULL 0
#endif
__inline static void RtkInitQueue(rtk_Queue_t* Q)
{
    if ( Q != NULL )
    {
        Q->First=Q->Last = (rtk_Envelop_t*)NULL;
	 Q->count = 0;
    }
}

  void      RtkConnectTimerInterrupt _PROTO(( void ** ));
  void      RtkDisconnectTimerInterrupt _PROTO(( void ** ));

  u32	  RtkTaskMarkerCall _PROTO((void *Fct, u8 NbPar, ...));
  void      RtkDefaultHook _PROTO((u8 Mbox, void *Msg, bool IsLocal));

  void      RtkExceptionRoutine _PROTO(( u8, u32, char *, char *, int ));
  void      RtkExceptionRoutine_C _PROTO(( u8, u32 ));


  //////////////////////////////////////////////////////////////////////////
  //  MISC FUNCTIONS
  //////////////////////////////////////////////////////////////////////////

  u16       RtkGetVersion _PROTO((void));
  u8        RtkInitTask _PROTO((struct rtk_TaskInit *PtrTaskInfo));

#ifdef __REMOTE_RTK__
  void      RtkRestartTasks _PROTO((void));
#endif
  u8        RtkChangeTaskPriority _PROTO((u8 rtkTaskNumber,u8 rtkNewPriority));
  void      RtkSuspendTaskTreat(u32 i_u32_NbTask, va_list i_s_args );
  void      RtkResumeTaskTreat(u32 i_u32_NbTask, va_list i_s_args );
  u8        RtkInitMailBox _PROTO((u8 MboxNo));
  void      RtkSuspendTask _PROTO((u32 NbTask, ...));
  void      RtkResumeTask _PROTO((u32 NbTask, ...));
#ifndef __SDK_SIMULATION__

#ifdef __RTK_PROFILE_ENHANCE__
  void      RtkConnectTimeSoftInterrupt _PROTO((void));
#endif

#if defined (__RTK_OSTICK_ENHANCE__)
  void RtkConnectGlobalTimerInterrupt _PROTO((void **));
  void RtkDisconnectGlobalTimerInterrupt _PROTO((void **)) ;
#endif

#if defined(__TIME_SLICE_SCHEDULE__)
  u8 RtkChangeTaskTimeSlice(u8 uTaskId, u32 uTimeSlice);
  u8 RtkSelfYield(void);
#endif

#endif // ! __SDK_SIMULATION__
#ifdef __RTK_DIAGNOSE__
  void      RtkSetOwner _PROTO(( u8 , void * ));
#else
#define   RtkSetOwner(x, y)
#endif

#ifndef __SDK_SIMULATION__
  u8 RtkGetTaskStack( u8 rtkTaskNumber, void **PtrStackBase, u32 *StackSize );
  u8 RtkGetTaskState( u8 rtkTaskNumber, u32 *pPC, u32 *pState);
  u8 RtkSetTaskState( u8 rtkTaskNumber, u32 PC, u32 state);
  u8 RtkRegisterUserOwnCallStack(bool val);
#endif //__SDK_SIMULATION__
  /* ------------------- to be provided par user ----------------------------- */

#ifdef __SDK_SIMULATION__
#ifdef __cplusplus
}
#endif //__cplusplus
#endif // __SDK_SIMULATION__

typedef enum
{
	RTK_NON_TASK_STACK_TYPE_MARKER,
#ifndef __RTK_OVER_R2__
	RTK_NON_TASK_STACK_TYPE_FIQ,
	RTK_NON_TASK_STACK_TYPE_IRQ,
	RTK_NON_TASK_STACK_TYPE_SUP,
#endif
	RTK_NON_TASK_STACK_TYPE_MAX
} rtk_non_task_stack_type_e;

u32 RtkScanTaskStackDepth(u8 taskId, void* pStkInfo);
u32 RtkScanNonTaskStackDepth(rtk_non_task_stack_type_e type, void* pStkInfo);
u32 RtkGetStackProfileData(void);
/* ------------------------------------------------------------------------*/
/*              EXPORTERTED variables                                      */
/* ------------------------------------------------------------------------*/

#define RTK_ALL_TASK_LOCAL 0xffffffff
#define RTK_ALL_MBX_LOCAL  0xaaaaaaaa

#define RTK_ALL_STACK_TASK 0xe03fffff  /* customer tasks are excluded id[22-28] */

#define MBX_STATE_NUM (RTK_MAX_TASKS/16+(RTK_MAX_TASKS%16?1:0))

/* implementation/declaration of some data */
#ifdef __RTK_DATA__
#ifdef __SDK_SIMULATION__
u32 rtk_TaskState   = RTK_ALL_TASK_LOCAL;
#endif // __SDK_SIMULATION__

u32 rtk_MbxState[MBX_STATE_NUM] = {
#if (MBX_STATE_NUM==(5))
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL,	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL
#elif(MBX_STATE_NUM==(6))
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL,
	RTK_ALL_MBX_LOCAL
#elif(MBX_STATE_NUM==(7))
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL,
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL
#elif(MBX_STATE_NUM==(8))
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL,
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL
#elif(MBX_STATE_NUM==(9))
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL,
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL
#elif(MBX_STATE_NUM==(10))
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL,
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL
#elif(MBX_STATE_NUM==(11))
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL,
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL,
	RTK_ALL_MBX_LOCAL
#elif(MBX_STATE_NUM==(12))
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL,
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL,
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL
#elif(MBX_STATE_NUM==(13))
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL,
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL,
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL
#elif(MBX_STATE_NUM==(14))
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL,
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL,
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL
#elif(MBX_STATE_NUM==(15))
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL,
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL,
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL
#elif(MBX_STATE_NUM==(16))
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL,
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL,
	RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL, RTK_ALL_MBX_LOCAL,
	RTK_ALL_MBX_LOCAL
#else
#error "pls add new array!!"
#endif
	};

void (*rtk_MbxHook)( u8 Mbx, void *Msg, bool IsLocal ) = RtkDefaultHook;

#else
#ifdef __SDK_SIMULATION__
extern  u32 rtk_TaskState;
#endif // __SDK_SIMULATION__

extern  u32 rtk_MbxState[MBX_STATE_NUM];

extern  void (*rtk_MbxHook)( u8 Mbx, void *Msg, bool IsLocal );
//extern void *rtk_OverwriteArea;
#endif


#define EXCPTHANDLER(X, Y) { RtkExceptionRoutine(X, Y, __FILE__, __FUNCTION__, __LINE__);}


/******** QUEUE MANAGEMENT **********/

#define RtkLastQueue(Q,E)          (*E = Q->Last, Q->Last->PtrObject.PtrQueueObj)
#define RtkReplaceObjectQueue(E,P) ((rtk_Envelop_t *) (*E))->PtrObject.PtrQueueObj = (void*) P

#define RtkTopQueue(Q,E)						\
  (									\
   ((rtk_Queue_t*)Q) ? (						\
			(*E = (void*)((rtk_Queue_t*)Q)->First),		\
			(((rtk_Queue_t*)Q)->First) ? ((void *)(((rtk_Envelop_t*)(*E))->PtrObject.PtrQueueObj)): NULL \
			):NULL						\
   )

// How to use this macro can be found in A7.18 of "The C Program Language, 2nd Edition".
// The expression after "," means the return value of this macro.
#define RtkNextQueue(E)							\
  ((*E) ?								\
   ((((rtk_Envelop_t*) (*E))->PtrNextEnv ) ?				\
    (*E = (void*) ((rtk_Envelop_t*) (*E))->PtrNextEnv, (void *) (((rtk_Envelop_t*) (*E))->PtrObject.PtrQueueObj )) \
    : (*E = (void*) NULL, (void*) NULL))				\
   : (void*) NULL)

// Correct LINT Error 522, this macro is defined.
// RtkNextQueue_No_Return() does not have return value (used by hac1tim.c in L1c).
#define RtkNextQueue_No_Return(E)							\
  ((*E) ?								\
   ((((rtk_Envelop_t*) (*E))->PtrNextEnv ) ?				\
    (*E = (void*) ((rtk_Envelop_t*) (*E))->PtrNextEnv) \
    : (*E = (void*) NULL))				\
   : (void*) NULL)



#define RtkObjectQueue(E) ((*E) ? (((rtk_Envelop_t*) (*E))->PtrObject.PtrQueueObj) : ((void *) NULL ))


/************* MACRO INTERRUPT *******************/

#define RTK_RESTORE_INT(X)     MsEnableInterruptUser(X)
#define RTK_SAVE_DISABLE_INT() MsDisableInterruptUser()

#ifndef __SDK_SIMULATION__
#define RTK2_TILT_INTERRUPT(itmask)                RTK2_TILT_INT()
#define RTK_SAVE_DISABLE_INT_BEFORE_SLEEP_MODE()   MsDisableInterruptUser()
#define RtkTraceCriticalSessionTiming()
#define RtkStartQbTiming(x)
#define RtkUpdateFrameLength(x)
#else // __SDK_SIMULATION__

// See RTE Kernel, rte_rtk11utl.cpp
extern void RtkEnable(u8 mask);
extern void Remote_Idle_Task(void);
extern rtk_MaskImage_t RtkDisable(void);

// See RTE Kernel, rte_rtktools.cpp
extern void RtkVFatalError(char * buf);
extern void RtkVError(char * buf);

#define RTK2_ENABLE(X)  RtkEnable(X)
#define RTK2_DISABLE()  RtkDisable()

// For separate kernel/user API
#if defined(__SEPARATE_INTERRUPT_API__)
#define RTK2_ENABLE_K(X)  RtkEnable(X)
#define RTK2_DISABLE_K()  RtkDisable()
#endif

#define RTK2_TILT_INTERRUPT(itmask)

//void VisualTrace(char*);
//int main(void);
//void ExitRtk(void);
#endif // __SDK_SIMULATION__


/************* REMOTE MANAGEMENT MACRO *******************/
//#define RTK_GET_TSK_STATE(t)    ((rtk_TaskState>>t)&1)
#define RTK_GET_MBX_STATE(m)    ((rtk_MbxState[m >> 4] >> ((m & 15) << 1)) & 3)
#define RTK_SET_MBX_STATE(m, s) rtk_MbxState[m >> 4] =	\
    (rtk_MbxState[m >> 4] & ~(3 << ((m & 15) << 1))) |	\
    (s << ((m & 15) << 1))
//#define RTK_TASK_REMOTE(t)      (rtk_TaskState = ((1<<t)^(-1)) & rtk_TaskState)
RtkDefExtern    u16 huge        *rtk_CustHeapStart;
RtkDefExtern    u16 huge        *rtk_CustHeapEnd;

extern const char stringStack [];


#include "sys_rtk_ht.h"

#define CONVERT_U8_U32 0xFF

#if defined(__SDK_SIMULATION__) || !defined(__GMM__)
RtkDefExtern rtk_memoryContext_t rtk_memoryStk;
#endif

#if defined(__arm) && !defined(__GNUC__)
#pragma arm section rwdata = "SysNonZI"
#endif

__section__(SysNonZI) RtkDefExtern u32 ms_memoryhandle;

#if defined(__arm) && !defined(__GNUC__)
#pragma arm section rwdata
#endif

#if defined(__IRAM_ALLOC__) && defined(__GMM__)
RtkDefExtern u32 ms_iramhandle;
#endif

#ifdef __GMM__

#include "sys_rtk_mshmem.h"
#define rtk_memoryStk ((pMemHandle_t)ms_memoryhandle)->rtkCtxt
#endif

void RtkDumpMemoryStatus(void);
void      RtkStatusMemory(const char *stringMemCtx, rtk_memoryContext_t *p_ctx);

u32 RtkGetAvailableHeapSize(void);
u32 RtkGetAllocatedHeapSize(void);
u32 RtkGetHeapPeakSize(void);
void RtkSetHeapPeakSize(u32 uSize);
u32 RtkResetHeapPeakSize(void);

typedef enum
{
  RTK_CALL_STACK_FIQ,
  RTK_CALL_STACK_IRQ,
  RTK_CALL_STACK_SUP,
  RTK_CALL_STACK_BOOT,
  RTK_CALL_STACK_ABT,
  RTK_CALL_STACK_UND,
  RTK_CALL_STACK_CURRENT_STACK,
  RTK_CALL_STACK_NONE
}rtk_CallStackType_e;
rtk_CallStackType_e RtkSP2CallStackId( u32 l_u32_SP, u32* o_pu32_StackTop, u32* o_pu32_StackStart );

bool      _RtkHeapWalkExGeneric(bool Start, rtk_HeapInfo_t *Info, rtk_memoryContext_t *rtk_memoryContext);
#define   RtkHeapWalkEx(X, Y)           _RtkHeapWalkExGeneric(X, Y, &rtk_memoryStk)

#define   RtkHeapWalkEx_aux(X, Y)            _RtkHeapWalkExGeneric(X, Y, &rtk_memoryStk)

bool _RtkHeapStatusGeneric(rtk_Heap_Status_t * heapStatus, rtk_memoryContext_t *p_ctx);
#define   RtkQueryHeapStatus(H)		_RtkHeapStatusGeneric(H, &rtk_memoryStk)

#if defined(__SDK_SIMULATION__)
#define RtkRunInIsrContext() (1 == 0)
#else
#ifndef __RTK_OVER_R2__
extern u32 GetStatus(void);
#define RtkRunInIsrContext() ((GetStatus() & 0x1f) != 0x1f) // Not running in ARM system mode
#else
extern s32 NestedLevel;
#define RtkRunInIsrContext() (NestedLevel > 0) // Running in ISR
#endif
#endif

/* ------------------- to be provided par user ----------------------------- */
#undef RtkDefExtern

#endif  /* __SYS_RTK_HO_H__ */

