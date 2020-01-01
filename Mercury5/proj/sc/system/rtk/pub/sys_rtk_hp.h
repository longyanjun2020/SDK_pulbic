/******************************************************************/
/*  File    : RTKPROTO.HP                                         */
/*-------------------------------------------------------------   */
/*  Scope   :  RTK Interface prototype definitions                */
/*                                                                */
/*  Contents:                                                     */
/*                                                                */
/******************************************************************/

#ifndef __SYS_RTK_HP_H__
#define __SYS_RTK_HP_H__


#include "sys_rtk_ht.h"

//===========================================================================
// INTERNAL INTERFACE

/********* ASM RTK prototype internal functions ************/
    void                RTK1_ACTIVATE_TASK _PROTO((rtk_Register_t *OldTask,rtk_Register_t *NewTask));	// JLO
    void                RTK1_ACTIVATE_FIRST_TASK _PROTO((rtk_Register_t *CsSuivant));
    void                RTK1_ACTIVATE_MARKED_TASK _PROTO((rtk_Register_t *OldTask, u32 SP));
    rtk_MaskImage_t     RTK2_DISABLE _PROTO((void));
    void                RTK2_ENABLE _PROTO((rtk_MaskImage_t mask));

    void                RTK2_TILT_INT _PROTO((void));
    u32                 GetSP _PROTO((void));

    /*    a rajouter pour nouvelle version
    void                RTK2_DISCONNECT_TIMER_INT _PROTO(( void ));
    void                RTK2_CONNECT_TIMER_INT _PROTO(( u8 seg, u8 ref ));
    void                RTK2_HANDLER_TIMER _PROTO(( void ));
    void                RTK2_OUTPORTB _PROTO(( u8 addr, u8 data ));
    */

    /*********** C RTK prototype internal functions **************/

    void                Rtk10TimerHandler _PROTO((void));

#if defined(__RTK_OSTICK_ENHANCE__)
    void                RtkGlobalTimerHandler _PROTO((void));
#endif

#ifdef __RTK_PROFILE_ENHANCE__
    void                Rtk10TimeSoftHandler _PROTO((void));
#endif

#ifdef __SDK_SIMULATION__
    void EXCEPTIONROUTINE _PROTO((u8 Status)); // Not usefull ??
    void Rtk10_TickHandler(void);
    /*interrupt*/
    void Rtk10TimerHandler _PROTO((void));
    void SetTimerThread(void); // WIN RTK -> rtk11tim.cpp
#endif //__SDK_SIMULATION__

    rtk_Envelop_t       *Rtk4GetEnv _PROTO((u32 lr));
    void                Rtk4FreeEnv _PROTO(( rtk_Envelop_t *UserEnvelop ));
    void                Rtk10ClearTimer _PROTO(( rtk_TimerId_t TimerID ));
    void                Rtk10TimerSend _PROTO((u8 DestMailBoxNumber, rtk_TimerId_t TimerID ));
    rtk_Timer_t         *Rtk10StartSemTimer _PROTO(( rtk_SemId_t semId, u32 Count ));
    void                Rtk11Schedule _PROTO((u8 NextState));
    void                Rtk11_ConnectTimerInterrupt _PROTO((void));
    void                Rtk11_DisconnectTimerInterrupt _PROTO((void));

    u32                 RtkGetCallerInStack (void);

    void                RtkHeapWalkEx _PROTO((bool Start, rtk_HeapInfo_t *Info));
	  bool                IsRtkReady (void);

#if defined(__TIME_SLICE_SCHEDULE__)
u8 RtkStartScheduleTimer(u32 TimerID, u32 Count);
u8 RtkStopScheduleTimer(u32 TimerID);
#endif

#ifdef __SDK_SIMULATION__
    void RtkScheduleThread (void); // WIN RTK -> rte_rtk5task.cpp
    void RtkResumeThread (rtk_Task_t *ptrCurrentTask); // WIN RTK -> rte_rtk2utils.cpp
#endif //__SDK_SIMULATION__

/***
 *    \fn s32 RtkCreateCustomTask(void (*entryPoint) _PROTO((void)), u32 prio,void *stackAddress,u32 stackSize, u32 userData)
 *
 *    \brief add a customer task
 *
 *    This function adds a system task. It is used at kernel initialisation
 *    and can not be used to create dynamically tasks as system tasks never die
 *
 *    \param entryPoint the task function
 *    \param prio       the task priority (must be lower or equal to \ref RTK_MAX_TASK_PRIORITY
 *    \param stackAddress top of the stack
 *    \param stackSize  the stack size
 *    \param userData  user owned data
 *
 *    \return the identifier of the task created or 0 if it failed.
 *
 *    \NOTE stackAddress is in memory order the beginning of the stack zone
 *    \NOTE there can only be \RTK_MAX_TASKS tasks
 *
 *****/
extern s32 RtkCreateCustomTask(char* pTaskName, void (*entryPoint) _PROTO((void)), u32 prio,void *stackAddress,u32 stackSize, u32 userData
#if defined(__TIME_SLICE_SCHEDULE__)
    , u32 TimeSliceLeft, u32 TimeSliceMax
#endif
);
/***
 *    \fn s32 RtkCreateSystemTask(void (*entryPoint) _PROTO((void)), u32 prio,void *stackAddress,u32 stackSize)
 *
 *    \brief add a system task
 *
 *    This function adds a system task. It is used at kernel initialisation
 *    and can not be used to create dynamically tasks as system tasks never die
 *
 *    \param entryPoint the task function
 *    \param prio       the task priority (must be lower or equal to \ref RTK_MAX_TASK_PRIORITY
 *    \param stackAddress top of the stack
 *    \param stackSize  the stack size
 *    \param TimeSliceLeft  the initial value of task time slice(should be less than or equal to TimeSliceMax)
 *    \param TimeSliceMax  the task time slice
 *
 *    \return a negative  value  if the task creation failed.
 *            the task identifier otherwise
 *
 *    \NOTE stackAddress is in memory order the beginning of the stack zone
 *    \NOTE there can only be \RTK_MAX_TASKS tasks
 *
 *****/
extern  s32 RtkCreateSystemTask(char* pTaskName, void (*entryPoint) _PROTO((void)), u32 prio,void *stackAddress,u32 stackSize
#if defined(__TIME_SLICE_SCHEDULE__)
    , u32 TimeSliceLeft, u32 TimeSliceMax
#endif
);


/***
 *    \fn s32 RtkCreateDynamicCustomTask(void *entryPoint, u32 prio,void *stackAddress,u32 stackSize, u32 userData)
 *
 *    \brief add a dynamic customer task
 *
 *    \param entryPoint the task function
 *    \param prio       the task priority (must be lower or equal to \ref RTK_MAX_TASK_PRIORITY
 *    \param stackAddress top of the stack
 *    \param stackSize  the stack size
 *    \param userData  user owned data
 *
 *    \return TRUE if the task creation succeeded.
 *
 *    \NOTE stackAddress is in memory order the beginning of the stack zone
 *    \NOTE there can only be \RTK_MAX_TASKS tasks
 *
 *****/
extern s32 RtkCreateDynamicCustomTask(char* pTaskName, void (*entryPoint) _PROTO((void)),
    u32 prio,void *stackAddress,u32 stackSize, u32 userData
#if defined(__TIME_SLICE_SCHEDULE__)
    , u32 TimeSliceLeft, u32 TimeSliceMax
#endif
);

/***
 *    \fn bool RtkDeleteDynamicCustomTask(u8 rtkTaskNumber)
 *
 *    \brief delete a dynamic customer task
 *
 *    \param rtkTaskNumber the task ID
 *
 *    \return RTK_OK if the task deletion succeeded.
 *
 *    \NOTE only dynamic custom task can be deleted; native task can NOT delete
 *
 *****/
extern s32 RtkDeleteDynamicCustomTask(u8 rtkTaskNumber);

/**!
 *    \fn rtk_Task_t*   RtkNextTaskToSchedule(rtk_Task_t* task,u32 state)
 *
 *    \brief this function returns the next task to activate
 *
 *    this function returns the next task to schedule depending
 *    on current configuration of all tasks ( priority / state )
 *
 *    \param task the task which state is to change
 *    \param state the new state of the task
 *
 *    \return a pointer to the task structure describing the most prioritary
 *            task that was found
 *
 *    \note : NULL can be a valid result, but should never be returned
 *            because of the way this function is used
 *            and asserting that the idle task can never be stopped
 *
 *
 ****/
extern rtk_Task_t*  RtkNextTaskToSchedule(void);

/**!
 *    \fn void RtkTaskSetState(rtk_Task_t* task,u32 state)
 *
 *    \brief this function changes the state of a task
 *           and help keep up to date any structure
 *           needed to schedule.
 *
 *    \param task the task which state is to change
 *    \param state the new state of the task
 *
 *    \return void
 *
 ****/
extern void RtkTaskSetState(rtk_Task_t* task,u32 state);



extern void RtkInsertTaskInPrioList  (rtk_Task_t* rtk_task);
extern void RtkRemoveTaskFromPrioList(rtk_Task_t* rtk_task);

/**!
 *    \fn void RtkStartFirstTask (void);
 *
 *    \brief this function starts the first task and the scheduling begins
 *
 *    \note this function never return
 *
 *    \return void
 *
 ****/
#ifdef __SDK_SIMULATION__
extern s32 RtkStartFirstTask (void);
#else //__SDK_SIMULATION__
extern void RtkStartFirstTask (void);
#endif //__SDK_SIMULATION__

#ifdef __SDK_SIMULATION__
#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus
#endif   // __SDK_SIMULATION__

  //////////////////////////////////////////////////////////////////////////
  //  TASKS INTERFACE
  //////////////////////////////////////////////////////////////////////////

  /*!
   *   \fn rtk_ErrCode_e        RtkStartTask (rtk_TaskId_t RtkTaskNumber)
   *
   *   \brief Start a task that have been created
   *
   *   \param RtkTaskNumber identifier of the task to start
   *
   *   \return RTK_OK
   *
   *   \note Raised exceptions :
   *           - RTK_TASK_NOT_INITIALIZED
   *           - RTK_BAD_TASK_NUMBER
   *           - RTK_TASK_ALREADY_STARTED
   */
  extern rtk_ErrCode_e  RtkStartTask(rtk_TaskId_t RtkTaskNumber);

  /*!
   *   \fn   rtk_TaskId_t RtkCurrentTask (void)
   *
   *   \brief Returns the current task identifier
   *
   *   \return The current task identifier
   *
   */
  extern rtk_TaskId_t        RtkCurrentTask(void);


  /*!
   *    \fn rtk_ErrCode_e RtkSleep( u32 Count )
   *
   *    \brief Suspend the calling task for the specified amount of time.
   *
   *    The calling task is suspended for the specified amount of time.
   *    After the call returns, Rtk_PtrCurrentTask->TypeOfObj is:
   *    - RTK_OBJ_TIMER if it slept for the specified amount of time,
   *    - RTK_OBJ_MESSAGE if the call was interrupted by a call to
   *      RtkWakeUpTask from another task.
   *
   *    \param Count the number of timer ticks to sleep for
   *
   *    \return - RTK_OK if the task has slept for the speficied amount of time
   *            - RTK_SEM_TIMEOUT if a call to RtkWakeUpTask interrupted the sleep
   */
  extern rtk_ErrCode_e    RtkSleep(u32 RtkSleepCount);

  /*!
   *   \fn rtk_ErrCode_e RtkWakeUpTask(rtk_TaskId_t TaskNumber )
   *
   *   \brief Wake up a task which is currently suspended on a RtkSleep call
   *
   *   If the specified task was suspended in a call to RtkSleep, this call
   *   is interrupted (made to return). The specified task's ->TypeOfObj is
   *   then RTK_OBJ_MESSAGE to indicate that the call to RtkSleep was
   *   interrupted before the specified amount of time has elapsed.
   *
   *   \param TaskNumber the task identifier
   *
   *   \return - RTK_OK if the task could be woken up
   *           - RTK_BAD_TASK_NUMBER if the task identifier is invalid
   *           - RTK_TASK_ALREADY_STARTED if the specified task was not asleep
   *           - RTK_BAD_TASK_STATE if the task is not found in the
   *             TASK_RTK_SLEEP_SEM semaphore queue (this is a bug)
   */
  extern rtk_ErrCode_e  RtkWakeUpTask(rtk_TaskId_t rtkTaskNumber);

  /*!
   *    \fn s32 RtkCreateSystemTask(void (*entryPoint)(void), u32 prio,void *stackAddress,u32 stackSize)
   *
   *    \brief add a system task
   *
   *    This function adds a system task. It is used at kernel initialisation
   *    and can not be used to create dynamically tasks as system tasks never die
   *
   *    \param entryPoint the task function
   *    \param prio       the task priority (must be lower or equal to \ref RTK_MAX_TASK_PRIORITY
   *    \param stackAddress top of the stack
   *    \param stackSize  the stack size
   *
   *    \return a negative  value  if the task creation failed.
   *            the task identifier otherwise (\ref rtk_TaskId_t)
   *
   *    \note stackAddress is in memory order the beginning of the stack zone
   *    \note there can only be \ref RTK_MAX_TASKS tasks
   *
   */
/*  extern s32 RtkCreateSystemTask(char* pTaskName, void (*entryPoint) (void), u32 prio,void *stackAddress,u32 stackSize
#if defined(__TIME_SLICE_SCHEDULE__)
    , u32 TimeSliceLeft, u32 TimeSliceMax
#endif
);*/

  //////////////////////////////////////////////////////////////////////////
  //  MESSAGES INTERFACE
  //////////////////////////////////////////////////////////////////////////

  /*!
   *   \fn rtk_ErrCode_e  RtkSend (rtk_MailboxId_t MboxNo, void *Msg, u32 nParam)
   *
   *   \brief sends a message to a mailbox
   *
   *   if the mailbox contains at least one pending task, the message is linked to the task and it becomes ready for preemption.
   *   if the task queue is empty, the message is inqueued to the mailbox, no preemption occurs.
   *
   *   \param MboxNo the mailbox identifier
   *   \param Msg    a pointer to the message to be sent
   *   \param nParam extra parameter for suspension
   *
   *   \return RTK_OK
   *
   */
  extern rtk_ErrCode_e  RtkSendCheckMP (rtk_MailboxId_t MboxNo, void *Msg);
  extern rtk_ErrCode_e  RtkSend   (rtk_MailboxId_t MboxNo, void *Msg, u32 nParam);

  /*!
   *   \fn rtk_ErrCode_e RtkSendWithPrio (rtk_MailboxId_t MboxNo, void *Msg, u32 nParam)
   *
   *   \brief sends a message to a mailbox
   *
   *   if the mailbox contains at least one pending task, the message is linked to the task and it becomes ready for preemption.
   *   if the task queue is empty, the message is inqueued to the mailbox, no preemption occurs.
   *
   *   \param MboxNo the mailbox identifier
   *   \param Msg    a pointer to the message to be sent
   *   \param nParam extra parameter for suspension
   *
   *   \return RTK_OK
   *
   */
  extern rtk_ErrCode_e RtkSendWithPrioCheckMP (rtk_MailboxId_t MboxNo, void *Msg);
  extern rtk_ErrCode_e RtkSendWithPrio(rtk_MailboxId_t MboxNo, void *Msg, u32 nParam);

  /*!
   *   \fn rtk_ErrCode_e  RtkReceive (rtk_MailboxId_t MboxNo,rtk_ObjDesc_t *Object)
   *
   *   \brief Reception of a messages
   *
   *   The task wants to receive a& message on a particular mailbox. It tests if any message is pending on the given mailbox.
   *   if there is a message, it is dequeued and RTK_OK is returned
   *   if there is no message, The task is queued to the mailbox, its state is updated to a Waiting State and the scheduler is activated
   *
   *   \param MboxNo the mailbox identifier
   *   \param Object  a \ref rtk_ObjDesc_t  pointer that contains either :
   *                    - A Timer Identifier
   *                    - A received message pointer
   *
   *   \return RTK_OK
   *
   */
  extern rtk_ErrCode_e RtkReceive(rtk_MailboxId_t MboxNo,rtk_ObjDesc_t *Object);

  /*!
   *   \fn rtk_ErrCode_e RtkTestReceive (rtk_MailboxId_t MboxNo,rtk_ObjDesc_t *Object)
   *
   *   \brief Reception of messages without waiting
   *
   *   \param MboxNo the mailbox identifier
   *   \param Object    a \ref rtk_ObjDesc_t  pointer that contains
   *                    \li the Timer Id
   *                    \li the received message pointer
   *
   *   \return RTK_OK if a message was received
   *   \return RTK_NO_MESSAGE if no message was available when the function  was called
   *
   */
  extern rtk_ErrCode_e RtkTestReceive (rtk_MailboxId_t MboxNo, rtk_ObjDesc_t *Object);

  //////////////////////////////////////////////////////////////////////////
  //  SEMAPHORES INTERFACE
  //////////////////////////////////////////////////////////////////////////

  /*!
   *   \fn rtk_ErrCode_e RtkSemProduce( rtk_SemId_t  rtkSemaphorNumber )
   *
   *   \brief Produce (Give back) a Semaphore
   *
   *   \param rtkSemaphorNumber the semaphore identifier
   *
   *   \return RTK_OK
   *
   *   \note  Raised Exceptions :
   *     - \ref RTK_BAD_SEM_NUMBER
   *     - \ref RTK_SEM_OVERFLOW
   */
  extern rtk_ErrCode_e   RtkSemProduce (rtk_SemId_t SemNo);

  /*!  \fn rtk_ErrCode_e RtkSemConsume(rtk_SemId_t  rtkSemaphorNumber)
   *
   *   \brief Consume (Take) a Semaphore
   *
   *   \param rtkSemaphorNumber the semaphore identifier
   *
   *   \return RTK_OK
   *
   *   \note Raised Exceptions :
   *     - \ref RTK_BAD_SEM_NUMBER
   *     - \ref RTK_NON_ALLOWED_OPBGT
   *     - \ref RTK_SEM_OVERFLOW
   *
   */
  extern rtk_ErrCode_e   RtkSemConsume (rtk_SemId_t SemNo);
  /*!
   *
   *  \fn rtk_ErrCode_e RtkSemConsumeDelay( rtk_SemId_t rtkSemaphorNumber, u32 SemTimeOut )
   *
   *  \brief Take the semaphore if available or wait for a bounded time.
   *
   *  If the semaphore is already available, take it and return immediately.
   *  Otherwise wait on it. If the caller was not woken up after a certain
   *  amount of time, make the call return. \ref RtkSemProduce needs not
   *  and should not be called even if the return value indicates that the
   *  semaphore could not be obtained before the timer expired.
   *
   *  \param rtkSemaphorNumber the semaphore handle
   *  \param SemTimeOut        max time to wait for the semaphore
   *
   *  \return - RTK_OK if the semaphore is obtained
   *          - RTK_NO_MESSAGE if the timer expired
   *
   *   \note Raised Exceptions :
   *     - \ref RTK_BAD_SEM_NUMBER
   *     - \ref RTK_NON_ALLOWED_OPBGT
   *     - \ref RTK_SEM_OVERFLOW
   */
  extern rtk_ErrCode_e   RtkSemConsumeDelay(rtk_SemId_t SemNo, u32 NbTicks);

  /*!
   *  \fn rtk_ErrCode_e RtkSemTestConsume( rtk_SemId_t rtkSemaphorNumber)
   *
   *  \brief Consume Semaphore (Take) if semaphore not free do not wait.
   *
   *  \param rtkSemaphorNumber the semaphore handle
   *  \return
   *         - RTKOK if the semaphore was consumed
   *         - RTK_UNIT_NOAVAIL if the semaphore was not free
   *
   *  \note Raised Exceptions :
   *     - \ref RTK_BAD_SEM_NUMBER
   *     - \ref RTK_SEM_UNDERFLOW
   *
   */
  extern rtk_ErrCode_e   RtkSemTestConsume(rtk_SemId_t SemNo);

  /*!
   * \fn rtk_ErrCode_e RtkSemRtkReadyProduce (rtk_SemId_t i_u8_SemNumber);
   *
   * \brief Release Semaphore (Produce), if rtk not ready ignore
   *
   * \param i_u8_SemNumber the semapÄ¥ore identifier
   * \return a rtk_ErrCode_e that is :
   *   - RTKOK if Rtk is not ready.
   *   - \ref RtkSemProduce result if Rtk is ready
   *
   * \note See \ref RtkSemProduce to get the list of raised exceptions
   *
   */
  extern rtk_ErrCode_e  RtkSemRtkReadyProduce (rtk_SemId_t i_u8_SemNumber);

  extern rtk_ErrCode_e  RtkSemRtkReadyConsume (rtk_SemId_t i_u8_SemNumber);

  extern rtk_ErrCode_e RtkSemGetCount(rtk_SemId_t rtkSemaphorNumber, s16* pSemCount);

  extern u8 RtkInitMutex (rtk_Mutex_t* mutex);
  rtk_ErrCode_e RtkMutexLock(rtk_Mutex_t* mutex);
  rtk_ErrCode_e RtkMutexUnlock(rtk_Mutex_t* mutex);
  rtk_ErrCode_e RtkMutexTryLock(rtk_Mutex_t* mutex);
  rtk_ErrCode_e RtkMutexSetProtocol(rtk_Mutex_t* mutex, rtk_Prio_Invr_e protocol);

  //////////////////////////////////////////////////////////////////////////
  //  TIMERS INTERFACE
  //////////////////////////////////////////////////////////////////////////

  /*!
   *    \fn rtk_ErrCode_e RtkStartTimer(rtk_TimerId_t timerID,rtk_MailboxId_t MBoxNo, u32 Count)
   *
   *    \brief Starts a new timer
   *
   *    \param timerID Identifier of the timer to start
   *    \param MBoxNo  The mailbox in which the timer expiration message will be sent
   *    \param Count   Number of timer ticks to wait for.
   *
   *    \return RTKOK
   *
   *    \note if the mailbox identifier is out of bounds, a RTK_BAD_MAILBOX_NUMBER exception will be raised.
   *          if the Count is out of bounds, a RTK_BAD_TIMER_PERIOD exception will be raised
   *          if there are no more timers available, a RTK_NO_TIMER_AVAIL exception will be raised
   *
   */
  #ifdef __RTK_TIMER_INFO__

  extern rtk_ErrCode_e  RtkStartTimer(rtk_TimerId_t TimerID, rtk_MailboxId_t MBoxNo, u32 Count, u32 Lr);

  #ifdef __RTK_TIMER_PERIODIC__
      extern rtk_ErrCode_e  RtkStartCyclicTimer( rtk_TimerId_t TimerID, bool bCyclic, rtk_MailboxId_t MBoxNo, u32 Count, u32 Lr );
  #endif

  #else //__RTK_TIMER_INFO__

  extern rtk_ErrCode_e  RtkStartTimer(rtk_TimerId_t TimerID, rtk_MailboxId_t MBoxNo, u32 Count);

  #ifdef __RTK_TIMER_PERIODIC__
      extern rtk_ErrCode_e  RtkStartCyclicTimer( rtk_TimerId_t TimerID, bool bCyclic, rtk_MailboxId_t MBoxNo, u32 Count );
  #endif

  #endif //__RTK_TIMER_INFO__

/*!
 *    \fn void RtkCleanTimerToMbox(rtk_MailboxId_t MboxNo);
 *
 *    \brief Stops any timer that was previously started to send mag to MboxNo
 *    and cleans any timer that was previously expired and sent mag to MboxNo
 *
 *    \param MboxNo Identifier of MboxNo which can receive msg sent from timer
 */
 void RtkCleanTimerToMbox(rtk_MailboxId_t MboxNo);

  /*!
   *    \fn rtk_ErrCode_e RtkStartStrictTimer(rtk_TimerId_t timerID,rtk_MailboxId_t MBoxNo, u32 Count)
   *
   *    \brief Starts a new timer
   *
   *    \param timerID Identifier of the timer to start
   *    \param MBoxNo  The mailbox in which the timer expiration message will be sent
   *    \param Count   Number of timer ticks to wait for.
   *
   *    \return RTKOK
   *
   *    \note if the mailbox identifier is out of bounds, a RTK_BAD_MAILBOX_NUMBER exception will be raised.
   *          if the Count is out of bounds, a RTK_BAD_TIMER_PERIOD exception will be raised
   *          if there are no more timers available, a RTK_NO_TIMER_AVAIL exception will be raised
   *
   */
  #ifdef __RTK_TIMER_INFO__
  extern rtk_ErrCode_e  RtkStartStrictTimer(rtk_TimerId_t TimerID, rtk_MailboxId_t MBoxNo, u32 Count, u32 Lr);
  #else
  extern rtk_ErrCode_e  RtkStartStrictTimer(rtk_TimerId_t TimerID, rtk_MailboxId_t MBoxNo, u32 Count);
  #endif
  /*!
   * \fn u32 RtkStopTimer(rtk_TimerId_t TimerID );
   *
   * \brief  Stops a timer that was previously started with \ref RtkStartTimer
   *
   * \param  TimerID Identifier of the timer to stop
   * \return The number of time ticks that were left when the timer was stopped
   */
  extern u32  RtkStopTimer(rtk_TimerId_t TimerID);

  /*!
   *    \fn bool RtkIsTimerActive(rtk_TimerId_t TimerId);
   *
   *    \brief tests a timer activity ( started / stopped )
   *
   *    \param TimerId the timer identifier
   *
   *    \return \li TRUE if the timer is active
   *            \li FALSE if the timer is stopped
   */
  extern bool RtkIsTimerActive (rtk_TimerId_t TimerId);

void Rtk10ClearTimerEx( rtk_TimerId_t TimerID, CallbackTimer_t *obj);

rtk_ErrCode_e RtkStartCallbackTimer(
	rtk_TimerId_t *TimerID,
	rtk_MailboxId_t MBoxNo,
	u32 trigger,
	u32 interval,
	CallbackTimer_t *cbtimer,
	u32 Lr
);

/**
 *   \fn u32 RtkTimeToExpireFirstTimer(void);
 *
 *   \brief remaining time to expire first timer
 *
 *   \param none
 *   \return: 0 if timer is already expired to be handled
 *             : 0xFFFFFFFF if no timer
 *             : otherwise return remaining time to expire first timer
 *
 */
u32 RtkTimeToExpireFirstTimer(void);

rtk_ErrCode_e RtkReceiveEx(rtk_MailboxId_t MboxNo, ObjDescEx_t *Object);

  //////////////////////////////////////////////////////////////////////////
  //  SCHEDULING CONTROL INTERFACE
  //////////////////////////////////////////////////////////////////////////

  /*!
   *   \fn rtk_ErrCode_e RtkEnterRegion( void )
   *
   *   \brief Increment the  regioncounter , the task can be interrupted but never preempted
   *
   *   \brief return RTK_OK
   *
   *   \note Raised exceptions :
   *     - \ref RTK_COUNTER_OVERFLOW
   *
   */
  rtk_ErrCode_e  RtkEnterRegion (void);
  /*!
   *   \fn rtk_ErrCode_e RtkLeaveRegion( void )
   *
   *   \brief  Decrement the regioncounter and go schedule
   *
   *   \return RTK_OK
   *
   *   \note Raised exceptions :
   *     - \ref RTK_COUNTER_UNDERFLOW
   *
   */
  rtk_ErrCode_e  RtkLeaveRegion(void);

  /*!
   *    \fn void RtkEnterRegionIT(void)
   *
   *    \brief Increment the  regioncounter , the task can be interrupted but never preempted
   *
   *    \return void
   */
  void           RtkEnterRegionIT(void);
  /*!
   *      \fn void RtkLeaveRegionIT(void)
   *
   *      \brief  Decrement the regioncounter and go schedule
   *
   *      \return void
   *
   */
  void           RtkLeaveRegionIT(void);

#ifdef __SDK_SIMULATION__
#ifdef __cplusplus
}
#endif //__cplusplus
#endif // __SDK_SIMULATION__

u32 RtkFlagTimeout(void *PtrFlag, rtk_TimerId_t TimerID);

/*
Parameters: PtrFlag¡Xpointer to flag object.
Description: Initializes a flag variable.
*/
void RtkFlagInit(rtk_Flag_t *PtrFlag);

/*
Parameters: PtrFlag¡Xpointer to flag object.
Description: Destroys the specified flag variable. Flag variables that are being waited on must not be destroyed.
*/
void RtkFlagDestroy(rtk_Flag_t *PtrFlag);

/*
Parameters: PtrFlag¡Xpointer to flag object.
		value¡Xthe bits that are set to one in this parameter are set along with the current bits set in the flag.
Description: Sets the bits in the flag value that are set to one in the value parameter. Any threads that
		are waiting on the flag and have their conditions met are woken up.
*/
void RtkFlagSetbits(rtk_Flag_t *PtrFlag, rtk_flag_value_t value);

/*
Parameters: PtrFlag¡Xpointer to flag object.
		value¡Xthe bits that are set to zero in this parameter are cleared in the flag.
Description: Clears the bits in the flag value that are set to zero in the value parameter. No threads
		are awakened by this call.
*/
void RtkFlagMaskbits(rtk_Flag_t *PtrFlag, rtk_flag_value_t value);

/*
Parameters: PtrFlag¡Xpointer to flag object.
		pattern¡Xbit setting that will cause the calling thread to be woken up.
		mode¡Xspecifies the conditions for wake up.
Description: If the mode parameter is set to AND, the function will wait for all bits in the pattern
		parameter to be set in the flag value. If the mode parameter is set to OR, the function will
		wait for any bits in the pattern parameter to be set in the flag value. When this function
		call returns, the condition is met and the flag value is returned.
		The mode parameter can have the following possible values:
		RTK_FLAG_WAITMODE_AND¡Xwake up if all bits specified in the mask are set in the flag.
		RTK_FLAG_WAITMODE_OR¡Xwake up if any bits specified in the mask are set in the flag.
		RTK_FLAG_WAITMODE_CLR¡Xclear all bits in the flag when the condition is met. Typically,
		only the bits that are set in the pattern parameter are cleared. This flag is bitwise
		combined with either the AND or OR wait mode flags.
*/
rtk_flag_value_t RtkFlagWait(rtk_Flag_t *PtrFlag, rtk_flag_value_t pattern, rtk_flag_mode_t mode);

/*
Parameters: PtrFlag¡Xpointer to flag object.
		pattern¡Xbit setting that will cause the calling thread to be woken up.
		mode¡Xmodifies the conditions for wake up.
		relativetime ¡X relative time to wait for flag conditions to be met.
Description: Waits for the conditions required by the pattern and mode parameters or the timeout
		specified by the abstime parameter. If the timeout occurs before the conditions are met,
		zero is returned; otherwise, the flag value is returned.
*/
rtk_flag_value_t RtkFlagTimedWait(rtk_Flag_t *PtrFlag, rtk_flag_value_t pattern, rtk_flag_mode_t mode, rtk_tick_count_t relative);

/*
Parameters: PtrFlag¡Xpointer to flag object.
		pattern¡Xbit setting that will cause the calling thread to be woken up.
		mode¡Xmodifies the conditions for returning the flag value.
Description: If the conditions required by the pattern and mode parameters are met, the flag value is
		returned; otherwise, zero is returned. Specifying RTK_FLAG_WAITMODE_CLR in the mode
		parameter will clear the flag value to zero.
*/
rtk_flag_value_t RtkFlagPoll(rtk_Flag_t *PtrFlag, rtk_flag_value_t pattern, rtk_flag_mode_t mode);

/*
Parameters: PtrFlag¡Xpointer to flag object.
Description: Returns the current value of the specified flag.
*/
rtk_flag_value_t RtkFlagPeek(rtk_Flag_t *PtrFlag);

/*
Parameters: PtrFlag¡Xpointer to flag object.
Description: Returns TRUE if there are any threads waiting on the specified flag.
*/
bool RtkFlagWaiting(rtk_Flag_t *PtrFlag);
//===========================================================================
// EXTERNAL INTERFACE

  //////////////////////////////////////////////////////////////////////////
  //  MISC FUNCTIONS
  //////////////////////////////////////////////////////////////////////////
  void RtkSemDisableService(bool bDisable);
  bool RtkSemQueryService(void);
  void RtkMutexDisableService(bool bDisable);
  bool RtkMutexQueryService(void);
  void RtkFlagDisableService(bool bDisable);
  bool RtkFlagQueryService(void);
  s32       RtkMemoryGenericLocation (void *rtkMemoryPtr);
  u8        RtkInitSem _PROTO((rtk_SemId_t SemNo, u16 InitialValue));
  u8        RtkInitSemExtend _PROTO((rtk_SemId_t rtkSemaphorNumber, s16 rtkCounterInitialValue, s16 rtkCurrentValue));
  u8        RtkSetSem _PROTO((rtk_SemId_t SemNo, u16 rtkCounterValue));
  u32       RtkGetOsTick _PROTO((void));
#if defined (__RTK_OSTICK_ENHANCE__)
  u64       RtkGetOsTickExt _PROTO((void));
#endif
  void      RtkUserInitProc _PROTO(( int agc, char **argv ));

  void      RtkInitDiagnoseGeneric (rtk_memoryContext_t *ptr_memoryContext);
  void      RtkInitPoolGeneric (rtk_PoolInit_t *PoolDescPtr, rtk_Pool_t **PoolStrucPtr,rtk_memoryContext_t *p, rtk_PtrRegion_e ptr_region);
  u8        RtkInitKernel (struct rtk_KernelInit *PtrInitTable, rtk_memoryContext_t *ptr_memoryContext);

#endif  /* __SYS_RTK_HP_H__ */

