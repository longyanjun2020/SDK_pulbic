//==============================================================================
//
//  File        : os_wrap.h
//  Description : OS wrapper function for uC/OS-II
//  Author      : Jerry Tsao
//  Revision    : 1.0
//
//==============================================================================

#ifndef _OS_WRAP_H_
#define _OS_WRAP_H_

#include "mmpf_typedef.h"

#if defined(__RTK_OS__)
#include "sys_MsWrapper_cus_os_int_pub.h"
#include "sys_MsWrapper_cus_os_int_ctrl.h"
#include "sys_MsWrapper_cus_os_timer.h"
#include "sys_MsWrapper_cus_os_flag.h"
#include "sys_MsWrapper_cus_os_sem.h"
#include "sys_MsWrapper_cus_os_util.h"
#include "sys_MsWrapper_cus_os_msg.h"

typedef union{ //Necessary???
    u32 userdata;
} Body_os_wrap_t;

#define Body_t Body_os_wrap_t
#include "stdmsg.ht"
#endif

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

#define OS_LOWEST_PRIO              2 //63    /* Defines the lowest priority that can be assigned ...           */

#ifndef OS_TICKS_PER_SEC
#define OS_TICKS_PER_SEC            1000    /* Set the number of ticks in one second                          */
#endif

#if defined(__RTK_OS__) 
#define MMPF_OS_SEMID_MAX           250
#define MMPF_OS_FLAGID_MAX          64
#define MMPF_OS_MUTEXID_MAX         4
#define MMPF_OS_MQID_MAX            (4+12+4)
#define MMPF_OS_TMRID_MAX           (0xFFFFFFFF) //MsTimerId_e//(u32)
#else //ucOSII
#define MMPF_OS_SEMID_MAX           250
#define MMPF_OS_FLAGID_MAX          64
#define MMPF_OS_MUTEXID_MAX         4
#define MMPF_OS_MQID_MAX            (4+12+4)
#define MMPF_OS_TMRID_MAX           16
#endif

/* Error Code */
#define MMPF_OS_ERR_NONE                (0x00)

#define MMPF_OS_ERR_TASK_ID             (0xFF)
#define MMPF_OS_ERR_TASK_EXCEED_MAX     (0xFE)

#define MMPF_OS_ERR_CREATE_SEM_ERR      (0xFF)
#define MMPF_OS_ERR_SEM_ID_EXCEED_MAX   (0xFE)
#define MMPF_OS_ERR_SEM_NOT_INIT        (0xFD)
#define MMPF_OS_ERR_SEM_IN_INTERRUPT    (0xFC)
#define MMPF_OS_ERR_SEM_OPERATION       (0xFB)

#define MMPF_OS_CREATE_FLAG_INT_ERR     (0xFF)
#define MMPF_OS_ERR_FLAG_ID_EXCEED_MAX  (0xFE)

#define MMPF_OS_ERR_CREATE_MSG_Q        (0xFE)

#if defined(__RTK_OS__)
#define MMPF_OS_CREATE_TMR_INT_ERR      (0xFFFFFFFF)
#else
#define MMPF_OS_CREATE_TMR_INT_ERR      (0xFF)
#endif

#if defined(__RTK_OS__) //Copied from os_cpu.h (LibSourceInc\uCOS-II\Ports\ARM9\ARM926EJS)
#ifdef OS_CRITICAL_INIT
#undef OS_CRITICAL_INIT
#endif
#ifdef OS_ENTER_CRITICAL
#undef OS_ENTER_CRITICAL
#endif
#ifdef OS_EXIT_CRITICAL
#undef OS_EXIT_CRITICAL
#endif
#define OS_CRITICAL_INIT()    MsIntMask_e eIntMask;
#define OS_ENTER_CRITICAL()    {eIntMask = MsDisableInterrupt();}
#define OS_EXIT_CRITICAL()    {MsEnableInterrupt(eIntMask);}
#else //ucOSII
#define OS_CRITICAL_INIT()    {}
#define OS_ENTER_CRITICAL()   {}
#define OS_EXIT_CRITICAL()    {}
#endif

//==============================================================================
//
//                              ucOSII relatvie definition. Review them one by one later...
//
//==============================================================================

typedef unsigned char   BOOLEAN;
typedef unsigned char   INT8U;                    /* Unsigned  8 bit quantity                           */
typedef signed   char   INT8S;                    /* Signed    8 bit quantity                           */
typedef unsigned short  INT16U;                   /* Unsigned 16 bit quantity                           */
typedef signed   short  INT16S;                   /* Signed   16 bit quantity                           */
typedef unsigned int    INT32U;                   /* Unsigned 32 bit quantity                           */
typedef signed   int    INT32S;                   /* Signed   32 bit quantity                           */
typedef float           FP32;                     /* Single precision floating point                    */
typedef double          FP64;                     /* Double precision floating point                    */

typedef unsigned int    OS_STK;                   /* Each stack entry is 32-bit wide                    */
typedef unsigned int    OS_CPU_SR;                /* Define size of CPU status register (PSR = 32 bits) */

typedef void            OS_TMR;//TBD

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef MMP_UBYTE   MMPF_OS_TASKID;
typedef MMP_ULONG   MMPF_OS_SEMID;
typedef MMP_ULONG   MMPF_OS_FLAGID;
typedef MMP_ULONG   MMPF_OS_MUTEXID;
typedef MMP_ULONG   MMPF_OS_MQID;
typedef MMP_ULONG   MMPF_OS_TMRID;

#if defined(__RTK_OS__)
typedef int         MMPF_OS_FLAGS;
#else //ucOSII
typedef MMP_ULONG   MMPF_OS_FLAGS;
#endif

typedef MMP_USHORT  MMPF_OS_FLAG_WTYPE;
#if defined(__RTK_OS__)
    #define MMPF_OS_FLAG_WAIT_CLR_ALL       MS_FLAG_WAITMODE_AND
    #define MMPF_OS_FLAG_WAIT_CLR_ANY       MS_FLAG_WAITMODE_OR
    #define MMPF_OS_FLAG_WAIT_SET_ALL       MS_FLAG_WAITMODE_AND
    #define MMPF_OS_FLAG_WAIT_SET_ANY       MS_FLAG_WAITMODE_OR
    #define MMPF_OS_FLAG_CONSUME            MS_FLAG_WAITMODE_CLR_SET
typedef MMP_USHORT  MMPF_OS_FLAG_OPT;
    #define MMPF_OS_FLAG_CLR                0x00
    #define MMPF_OS_FLAG_SET                0x01
typedef MMP_UBYTE   MMPF_OS_TMR_OPT;
    #define MMPF_OS_TMR_OPT_ONE_SHOT        0x02
    #define MMPF_OS_TMR_OPT_PERIODIC        0x03
    #define MMPF_OS_TMR_OPT_NONE            0x01
    #define MMPF_OS_TMR_OPT_CALLBACK        0x04
#else //ucOSII
    #define MMPF_OS_FLAG_WAIT_CLR_ALL       0
    #define MMPF_OS_FLAG_WAIT_CLR_ANY       1
    #define MMPF_OS_FLAG_WAIT_SET_ALL       2
    #define MMPF_OS_FLAG_WAIT_SET_ANY       3
    #define MMPF_OS_FLAG_CONSUME            0x80
typedef MMP_USHORT  MMPF_OS_FLAG_OPT;
    #define MMPF_OS_FLAG_CLR                0
    #define MMPF_OS_FLAG_SET                1
typedef MMP_UBYTE   MMPF_OS_TMR_OPT;
    #define MMPF_OS_TMR_OPT_ONE_SHOT        2
    #define MMPF_OS_TMR_OPT_PERIODIC        3
    #define MMPF_OS_TMR_OPT_NONE            1
    #define MMPF_OS_TMR_OPT_CALLBACK        4
#endif    

#if defined(__RTK_OS__)
typedef void (*MMPF_OS_TMR_CALLBACK)(MsTimerId_e eTimerID, u32 UserData);
#else //ucOSII
typedef  void (*OS_TMR_CALLBACK_PROTOTYPE)(void *ptmr, void *parg);
typedef OS_TMR_CALLBACK_PROTOTYPE   MMPF_OS_TMR_CALLBACK;
#endif

typedef struct {
    MMP_ULONG   pbos;           // lower address
    MMP_ULONG   ptos;           // higer address
    MMP_UBYTE   ubPriority;
    void     (*TaskiInit) (void * );
} MMPF_TASK_CFG;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

void                MMPF_OS_Initialize(void);
void                MMPF_OS_StartTask(void);

// Task Related
MMPF_OS_TASKID      MMPF_OS_CreateTask(void (*taskproc)(void *param), MMPF_TASK_CFG *task_cfg, void *param);
MMP_UBYTE           MMPF_OS_SetTaskName(MMP_UBYTE ubPriority, MMP_UBYTE *pTaskName);
MMP_UBYTE           MMPF_OS_ChangeTaskPriority(MMP_UBYTE ubPriority, MMP_UBYTE ubNewPriority);
MMP_UBYTE           MMPF_OS_DeleteTask(MMP_UBYTE ubPriority);
MMP_UBYTE           MMPF_OS_SuspendTask(MMP_UBYTE ubPriority);
MMP_UBYTE           MMPF_OS_ResumeTask(MMP_UBYTE ubPriority);

MMP_UBYTE           MMPF_OS_LockSchedule(void);
MMP_UBYTE           MMPF_OS_UnlockSchedule(void);

// Semaphore Related
MMPF_OS_SEMID       MMPF_OS_CreateSem(MMP_UBYTE ubSemValue);
MMP_UBYTE           MMPF_OS_DeleteSem(MMPF_OS_SEMID ulSemId);
MMP_UBYTE           MMPF_OS_ReleaseSem(MMPF_OS_SEMID ulSemId);
MMP_UBYTE           MMPF_OS_AcquireSem(MMPF_OS_SEMID ulSemId, MMP_ULONG ulTimeout);
MMP_UBYTE           MMPF_OS_AcceptSem(MMPF_OS_SEMID ulSemId, MMP_USHORT *usCount);
MMP_UBYTE           MMPF_OS_QuerySem(MMPF_OS_SEMID ulSemId, MMP_USHORT *usCount);

// Task Related
MMPF_OS_FLAGID      MMPF_OS_CreateEventFlagGrp(MMP_ULONG ulFlagValues);
MMP_UBYTE           MMPF_OS_DeleteEventFlagGrp(MMPF_OS_FLAGID ulFlagId);
MMP_UBYTE           MMPF_OS_SetFlags(MMPF_OS_FLAGID ulFlagID, MMPF_OS_FLAGS flags, MMPF_OS_FLAG_OPT opt);
MMP_UBYTE           MMPF_OS_WaitFlags(MMPF_OS_FLAGID ulFlagID, MMPF_OS_FLAGS flags, MMPF_OS_FLAG_WTYPE waitType,
                                      MMP_ULONG ulTimeout, MMPF_OS_FLAGS *ret_flags);
MMP_UBYTE           MMPF_OS_QueryFlags(MMPF_OS_FLAGID ulFlagID, MMPF_OS_FLAGS *ret_flags);

// Mutex Related
MMPF_OS_MUTEXID     MMPF_OS_CreateMutex(MMP_UBYTE   ubPriority);
MMP_UBYTE           MMPF_OS_DeleteMutex(MMPF_OS_MUTEXID ulMutexId);
MMP_UBYTE           MMPF_OS_AcquireMutex(MMPF_OS_MUTEXID ulMutexId, MMP_ULONG ulTimeout);
MMP_UBYTE           MMPF_OS_ReleaseMutex(MMPF_OS_MUTEXID ulMutexId);

// Message Queue Related
MMPF_OS_MQID        MMPF_OS_CreateMQueue(void **msg, MMP_USHORT ubQueueSize);
MMP_UBYTE           MMPF_OS_DeleteMQueue(MMPF_OS_MQID ulMQId);
MMP_UBYTE           MMPF_OS_GetMessage(MMPF_OS_MQID ulMQId,void **msg, MMP_ULONG ulTimeout);
MMP_UBYTE           MMPF_OS_PutMessage(MMPF_OS_MQID ulMQId, void *msg);
MMP_UBYTE           MMPF_OS_FlushMQueue(MMPF_OS_MQID ulMQId);
MMP_UBYTE           MMPF_OS_QueryMQueue(MMPF_OS_MQID ulMQId, MMP_USHORT *usCount);

// Time Related
MMP_UBYTE           MMPF_OS_Sleep(MMP_USHORT usTickCount);
MMP_UBYTE           MMPF_OS_SleepMs(MMP_ULONG ulMiliSecond);
MMP_UBYTE           MMPF_OS_SetTime(MMP_ULONG ulTickCount);
MMP_UBYTE           MMPF_OS_GetTime(MMP_ULONG *ulTickCount);
MMP_UBYTE           MMPF_OS_GetTimeMs(MMP_ULONG *ulTickCount);

// Timer Related
MMPF_OS_TMRID       MMPF_OS_StartTimer(MMP_ULONG ulPeriod, MMPF_OS_TMR_OPT opt, MMPF_OS_TMR_CALLBACK callback,
                                        void *callback_arg);
MMP_UBYTE           MMPF_OS_StopTimer(MMPF_OS_TMRID ulTmrId, MMPF_OS_TMR_OPT opt);

// CPU State Releated
MMP_BOOL            MMPF_OS_InInterrupt(void);

#endif // _OS_WRAP_H_
