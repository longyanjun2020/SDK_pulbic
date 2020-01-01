/*------------------------------------------------------------------------------
	Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
    PROJECT:
    DESCRIPTION:
          System service functions

    HISTORY:
         <Date>     <Author>    <Modification Description>
       2009/04/07   Ralf Chen   Initial revision

-------------------------------------------------------------------------------*/


#ifndef __SYS_MSWRAPPER_CUS_OS_UTIL_H__
#define __SYS_MSWRAPPER_CUS_OS_UTIL_H__


/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/

#include "sys_MsWrapper_cus_os_type.h"
#ifndef __SDK_SIMULATION__
#include "drv_timer_types.h"
#include "drv_timer_api.h"
#endif
#include "sys_rtk_ho.h"
/*------------------------------------------------------------------------------
    EXTERN definition
-------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
    Constant
-------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
/*!
 *      \brief MS error codes. These values are returned by most of the MS functions
 */
typedef enum {
    MS_OK                         = 10,   ///< No error - the function call was successfull
    MS_NOT_RELEASED               = 11,   ///< The bloc was not released
    MS_UNIT_NOAVAIL               = 21,   ///< Not available
    MS_NO_MESSAGE                 = 33,   ///< No message found
    MS_INVALID_MAILBOX_ID         = 34,   ///< invalid mailbox id
    MS_INVALID_MAILBOX_OWNER      = 35,   ///< mailbox is not owned by current task
    MS_INVALID_MAILBOX_THRESHOLD  = 36,   ///< invalid mailbox threshold
    MS_MAILBOX_OVER_THRESHOLD     = 37,   ///< mailbox reach threshold
    MS_NON_SATISFACTORY_POOL      = 40,   ///< No memory pool found (-deprecated-)
    MS_NO_MEMORY_AVAIL            = 41,   ///< Not enough memory
    MS_CLUSTER_OUT_OF_RANGE       = 42,   ///<
    MS_TIMER_NOT_FOUND            = 43,   ///< Invalid timer id
    MS_MEM_OVERFLOW               = 44,   ///<
    MS_NULL_RELEASE               = 45,   ///< Try to release a NULL pointer
    MS_NOT_HEAP_RELEASE           = 46,   ///< Memory zone is not in heap
    MS_NOT_MEMORY_RELEASE         = 47,   ///< Memory zone is not in pool memory (-deprecated-)
    MS_MAILBOX_FULL               = 48,   ///< Mailbox is full (-deprecated-)
    MS_TIMER_EXHAUSTED            = 49,   ///< Timer is unavailable (-deprecated-)
    MS_MAILBOX_NOT_EXIST          = 50,   ///< Mailbox is in initial state since dynamic task is deleted
    MS_IN_INTERRUPT               = 51,
    MS_STACK_ADDRESS_ERROR        = (-1),
    MS_ENTRY_POINTER_ERROR        = (-2),
    MS_PRIORITY_ERROR             = (-3),
    MS_TASK_EXHAUSTED             = (-4),
    MS_TASK_ID_ERROR              = (-5),
    MS_TASK_NOT_EXISTED           = (-6),
    MS_TASK_ALREADY_CREATED       = (-7),
    MS_COARSE_TIMER_ID_ERROR      = (-9),
    MS_COARSE_TIMER_START_FAILED  = (-10),
} Ms_ErrCode_e;

/******* Structure d'un flag *******/
typedef struct MsTaskCreateArgs
{
	u32         Priority;
	u32         StackSize;                     /* Stack Size              */
	u32         *pStackTop;                       /* Stack pointer           */
	void        (*AppliInit) (void * );    /* Initialisation function */
	void        (*AppliParser) (vm_msg_t * ); /* Parser function         */
	void        *pInitArgs;   // input argument for Initialisation function
	MsTaskId_e *TaskId;   //will be filled an ID if successfully created, otherwise *TaskId=NULL
	void        *Reserve; //reserve for future usage
	u8		ImmediatelyStart; //immediately start the task if TRUE, otherwise pendding until it's started
	char    TaskName[16];
#if defined(__TIME_SLICE_SCHEDULE__)
    u32 TimeSliceMax;
    u32 TimeSliceLeft;
#endif
}MsTaskCreateArgs_t;

typedef void (*pParsingFunc)(void *pData);

typedef struct
{
	u8 state;
	pParsingFunc pfunc;
	u32 records;
	u32 sizeofrecord;
	u32 index;
	u8 data[];
} MsLoggint_t;

typedef u8 (*pFunc_t)(void);
typedef u8 (*pFunc_tbl_init_t)(pFunc_t*);

typedef struct FreeEnvelope_t_
{
	struct FreeEnvelope_t_ *pNext;
	u32 guard;
} FreeEnvelope_t, *pFreeEnvelope_t;
/*------------------------------------------------------------------------------
    Variable
-------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/
#if !defined(__SDK_SIMULATION__)
//#define USER_TO_HW_TICK_GLOBAL(x) DrvTimerUserToHwTickGlobal(x)
#define HW_TO_USER_TICK_GLOBAL(x) DrvTimerHwToUserTickGlobal(x)
#define USER_TO_HW_TICK_OSTICK(x) DrvTimerUserToHwTickOstick(x)
#define HW_TO_USER_TICK_OSTICK(x) DrvTimerHwToUserTickOstick(x)

#define MS_TO_HW_TICK_OSTICK(x) DrvTimerMs2Ostick(x)
#define HW_TICK_TO_MS_OSTICK(x) DrvTimerOstick2Ms(x)
#else
#define USER_TO_HW_TICK(x) (x)
#define HW_TO_USER_TICK(x) (x)
#define USER_TO_HW_TICK_OSTICK(x) (x)
#define HW_TO_USER_TICK_OSTICK(x) (x)
#endif

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/

/** \addtogroup TaskMan1
 *  @{
 */

/**
 * \fn MsOsErr_e MsStartTask(MsTaskId_e eTaskId)
 * \brief The MsStartTask primitive starts a task. Note that the scheduler is not activated by the MsStartTask primitive.
 * \param[in] eTaskId The Task ID
 * \return Always RTK_OK
 */
MsOsErr_e MsStartTask(MsTaskId_e eTaskId);


/**
 * \fn MsTaskId_e MsCurrTask(void)
 * \brief The MsCurrTask primitive returns the task id of current task
 * \return The ID of current task
 */
MsTaskId_e MsCurrTask(void);


/**
 * \fn Ms_ErrCode_e MsChangeTaskPriority( u8 eTaskId, u8 eNewPriority )
 * \brief The MsChangeTaskPriority primitive is used to run-time change the priority of the given task.
 * When it is called, besides the priority of the desired task control block changes, the service will lock the system and rechain the priority waiting list for semaphore and flag. The priority change takes immediate effect upon API return.
 * The service will trigger rescheduling, only when the given new priority is higher than old one and the state of that task is RTK_READY or RTK_SUSPENDED
 * \param[in] eTaskId The Task ID
 * \param[in] eNewPriority The new task priority
 * \return MS_OK is returned if the action is done successfully; otherwise, kernel will assert
 */
Ms_ErrCode_e MsChangeTaskPriority( u8 eTaskId, u8 eNewPriority );


/**
 * \ingroup UTIL
 * \fn MsOsErr_e MsSleep(u32 u32Count)
 * \brief The MsSleep primitive suspends the calling task for specified time
 * \param[in] u32Count The sleep time is tick
 * \return Result of sleeping
 */
MsOsErr_e MsSleep(u32 u32Count);

/**
 * \ingroup UTIL
 * \fn MsOsErr_e MsSleepExt(u32 u32Count)
 * \brief -> Run-time: MsSleep -> exception: pure SYS_UDELAY
 * \param[in] u32Count The sleep time is tick
 * \return Result of sleeping
 */
MsOsErr_e MsSleepExt(u32 u32Count);

/**
 * \fn void MsResumeTask ( u32 Input, ... )
 * \brief The MsResumeTask primitive resumes a list of tasks
 * \param[in] Input The number of task to suspend
 */
void MsResumeTask ( u32 Input, ... );

/**
 * \fn void MsSuspendTask ( u32 Input, ... )
 * \brief The MsSuspendTask primitive suspends a list of tasks
 * \param[in] Input The number of task to suspend
 */
void MsSuspendTask ( u32 Input, ... );
//void MsSuspendTask(MsTaskId_e eTaskId);
//void MsResumeTask(MsTaskId_e eTaskId);

/**
 * \ingroup UTIL
 * \fn bool MsCheckOsReady (void)
 * \brief The MsCheckOsReady primitive would return the result of whether the scheduling is ready or not
 * \return Ture if the scheduling is ready, otherwise, return FALSE
 */
bool MsCheckOsReady (void);

/**
 * \fn Ms_ErrCode_e MsCreateTask(MsTaskCreateArgs_t *TaskArgs);
 * \brief The MsCreateTask primitive is used for creating a dynamic task. Our system use mailbox as default inter-process communication and the corresponding mailbox ID of the created task is the same as the task ID
 * \param[in] *TaskArgs Task parameters, the unit of time slice is RTK ticks( __TIME_SLICE_SCHEDULE__ )
 * \return MS_OK is returned if task is created successfully; otherwise, returns Ms_ErrCode_e
 */
Ms_ErrCode_e MsCreateTask(MsTaskCreateArgs_t *TaskArgs);

/**
 * \fn Ms_ErrCode_e MsDeleteTask(MsTaskId_e eTaskId)
 * \brief The MsDeleteTask primitive is used for deleting a dynamic task
 * \param[in] eTaskId The task ID
 * \return RTK_OK is returned if the dynamic task is deleted successfully; otherwise, returns error ID (Ms_ErrCode_e)
 */
Ms_ErrCode_e MsDeleteTask(MsTaskId_e eTaskId);

#if defined(__TIME_SLICE_SCHEDULE__)
/**
 * \fn Ms_ErrCode_e MsCreateTaskMs(MsTaskCreateArgs_t *TaskArgs);
 * \brief The MsCreateTask primitive is used for creating a dynamic task. Our system use mailbox as default inter-process communication and the corresponding mailbox ID of the created task is the same as the task ID
 * \param[in] *TaskArgs Task parameters, the unit of time slice is millisecond
 * \return MS_OK is returned if task is created successfully; otherwise, returns Ms_ErrCode_e
 */
Ms_ErrCode_e MsCreateTaskMs(MsTaskCreateArgs_t *TaskArgs);


/**
 * \fn Ms_ErrCode_e MsChangeTaskTimeSlice(MsTaskId_e eTaskId, u32 uTimeSlice)
 * \brief The MsChangeTaskTimeSlice primitive is used to run-time change the time slice of the given task. If the task does not participate in time slice scheduling when creating it, RTK_UNIT_NOAVAIL is returned. Otherwise the task time slice max and current values are set to uTimeSlice value.
 * \param[in] eTaskId The task ID
 * \param[in] uTimeSlice New time slice
 * \return MS_OK is returned if the action is done successfully; otherwise, returns error ID (Ms_ErrCode_e)
 */
Ms_ErrCode_e MsChangeTaskTimeSlice(MsTaskId_e eTaskId, u32 uTimeSlice);

/**
 * \fn Ms_ErrCode_e MsSelfYield(void)
 * \brief The MsSelfYield primitive is used to run-time self yield CPU time to other equal priority tasks if they participate in time slice scheduling. The task time slice current value is set to its time slice max value, and is chained to the tail of the running list. If the task does not participate time slice scheduling when creating it, RTK_UNIT_NOAVAIL is returned
 * \return MS_OK is returned if the action is done successfully; otherwise, returns error ID (Ms_ErrCode_e)
 */
Ms_ErrCode_e MsSelfYield(void);
#endif

/** @}*/


/** \addtogroup CRITAREA
 *  @{
 */

/**
 * \fn void MsEnterRegion(void)
 * \brief The MsEnterRegion primitive is used to define the entry point of a critical section: the scheduler is disabled for the duration of the critical section.
 * The level of scheduler locking (the number of successive critical section entries) is limited to 255.
 */
void MsEnterRegion(void);


/**
 * \fn void MsLeaveRegion(void)
 * \brief The MsLeaveRegion primitive is used to define the exit point of a critical section
 */
void MsLeaveRegion(void);


/**
 * \fn void MsEnterRegionInt(void)
 * \brief The MsEnterRegionInt primitive is used to define the entry point of a critical section in an interrupt routine. Only one level of critical sections is allowed in interrupt routines.
 * This primitive is a fast version of MsEnterRegion: the scheduler locking level is not tested and no exception can be generated
 */
void MsEnterRegionInt(void);


/**
 * \fn void MsLeaveRegionInt(void)
 * \brief The MsLeaveRegionInt primitive is used to define the exit point of a critical section in an interrupt routine.
 * This primitive is a fast version of MsEnterRegion: the scheduler locking level is not tested and no exception can be generated
 * The MsLeaveRegionInt primitive is used to define the exit point of a critical section in an interrupt routine.
 * This primitive is a fast version of MsEnterRegion: the scheduler locking level is not tested and no exception can be generated
 */
void MsLeaveRegionInt(void);

/** @}*/

/** \addtogroup UTIL
 *  @{
 */
/**
 * \fn u32 MsGetOsTick(void);
 * \brief The MsGetOsTick primitive returns the current count of tick
 * \return The current count of tick
 */
u32 MsGetOsTick(void);


#if defined (__RTK_OSTICK_ENHANCE__)
/** @}*/

/** \addtogroup UTIL
 *  @{
 */
/**
 * \fn u64 MsGetOsTick(void);
 * \brief The MsGetOsTickExt primitive returns the current count of tick
 * \return The current count of tick
 */
u64 MsGetOsTickExt(void);
#endif

/**
 * \fn void MsSrand(u32 seed)
 * @brief Set the random seed
 * @return void
 */
void MsSrand(u32 seed);


/**
 * \fn int MsRand(void)
 * @brief Return a random 32-bit value
 * @return int 32-bit value
 */
int MsRand(void);

/** @}*/

extern MsLoggint_t *MsLoggingConstructor(u32 nRecords, u32 nSizeOfRecord, pParsingFunc pfunc);
extern void MsLoggingDestructor(MsLoggint_t *pLogging);
extern void MsLoggingStart(MsLoggint_t *pLogging);
extern void MsLoggingStop(MsLoggint_t *pLogging);
extern void MsLoggingDo(MsLoggint_t *pLogging, void *pRecord);
extern void MsLoggingParsing(MsLoggint_t *pLogging);

extern u8 MsGetHighestSetBit(u32 nValue);
extern u8 MsGetLowestSetBit(u32 nValue);

typedef rtk_Queue_t ms_Queue_t;
extern void MsInitQueue(ms_Queue_t* Q);
extern Ms_ErrCode_e MsQueue(ms_Queue_t *Q, void *E);
extern void *MsDeQueue(ms_Queue_t *Q);
extern void MsBacktraceEntryCounterAdd(void);
extern u32 MsBacktraceEntryCounterCheck(void);
extern void MsModifyStateTaskToReady(u8 i_u8_MboxNo);
extern void MsDumpMemoryStatus(void);
#endif  /* __SYS_MSWRAPPER_CUS_OS_UTIL_H__ */


