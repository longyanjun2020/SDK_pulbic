/**
 @file ahc_os.h
 @brief Header File for the AHC OS API.
 @author 
 @version 1.0
*/

#ifndef _AHC_OS_H_
#define _AHC_OS_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_common.h"
#include "os_wrap.h"

/*===========================================================================
 * Macro/Type define
 *===========================================================================*/ 

typedef void (*OS_TMR_CALLBACK)(void *ptmr, void *parg);

typedef UINT8   AHC_OS_TASKID;
typedef UINT32  AHC_OS_SEMID;
typedef UINT32  AHC_OS_FLAGID;
typedef UINT32  AHC_OS_MUTEXID;
typedef UINT32  AHC_OS_MQID;
typedef UINT32  AHC_OS_TMRID;

typedef UINT32  AHC_OS_FLAGS;

#define Sleep_MS(_ms)                       (OS_TICKS_PER_SEC * (UINT32)(_ms) / 1000L)
#define MS_TO_TICK(_ms)                     (OS_TICKS_PER_SEC * (UINT32)(_ms) / 1000L)
#define TICK_TO_MS(_tick)		            (((MMP_ULONG)(_tick)  * 1000L) / OS_TICKS_PER_SEC)

typedef UINT16  AHC_OS_FLAG_WTYPE;
    #define AHC_OS_FLAG_WAIT_CLR_ALL       	MMPF_OS_FLAG_WAIT_CLR_ALL
    #define AHC_OS_FLAG_WAIT_CLR_ANY       	MMPF_OS_FLAG_WAIT_CLR_ANY
    #define AHC_OS_FLAG_WAIT_SET_ALL       	MMPF_OS_FLAG_WAIT_SET_ALL
    #define AHC_OS_FLAG_WAIT_SET_ANY       	MMPF_OS_FLAG_WAIT_SET_ANY
    #define AHC_OS_FLAG_CONSUME            	MMPF_OS_FLAG_CONSUME
    
typedef UINT16  AHC_OS_FLAG_OPT;
    #define AHC_OS_FLAG_CLR                	MMPF_OS_FLAG_CLR
    #define AHC_OS_FLAG_SET                	MMPF_OS_FLAG_SET

typedef UINT8   AHC_OS_TMR_OPT;
    #define AHC_OS_TMR_OPT_ONE_SHOT        	2u
    #define AHC_OS_TMR_OPT_PERIODIC        	3u
    #define AHC_OS_TMR_OPT_NONE				1u
    #define AHC_OS_TMR_OPT_CALLBACK			4u

typedef OS_TMR_CALLBACK		AHC_OS_TMR_CALLBACK;

#define AHC_OS_CREATE_TMR_INT_ERR			MMPF_OS_CREATE_TMR_INT_ERR

/*===========================================================================
 * Structure define
 *===========================================================================*/ 
 
typedef struct {
    UINT32   pbos;           // lower address
    UINT32   ptos;           // higer address
	UINT8    ubPriority;
	void     (*TaskiInit) (void * );
} AHC_OS_TASK_CFG;

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 
 
AHC_OS_TASKID   AHC_OS_CreateTask(void (*taskproc)(void *param), AHC_OS_TASK_CFG *task_cfg, void *param);
AHC_BOOL        AHC_OS_SetTaskName(UINT8 ubNewPriority, UINT8 *pTaskName);
void            AHC_OS_StartTask(void);
UINT8           AHC_OS_ChangeTaskPriority(UINT8 ubold_pri, UINT8 ubnew_pri);
UINT8           AHC_OS_DeleteTask(AHC_OS_TASKID taskid);
UINT8           AHC_OS_SuspendTask(AHC_OS_TASKID taskid);
UINT8           AHC_OS_ResumeTask(AHC_OS_TASKID taskid);
AHC_OS_SEMID    AHC_OS_CreateSem(UINT8 ubSemValue);
UINT8           AHC_OS_DeleteSem(AHC_OS_SEMID ulSemId);
UINT8           AHC_OS_AcquireSem(AHC_OS_SEMID ulSemId, UINT32 ulTimeout);
UINT8           AHC_OS_ReleaseSem(AHC_OS_SEMID ulSemId);
UINT8           AHC_OS_QuerySem(AHC_OS_SEMID ulSemId, UINT16 *usCount);
AHC_OS_MUTEXID  AHC_OS_CreateMutex(UINT8	ubPriority);
UINT8           AHC_OS_DeleteMutex(AHC_OS_MUTEXID ulMutexId);
UINT8           AHC_OS_AcquireMutex(AHC_OS_MUTEXID ulMutexId, UINT32 ulTimeout);
UINT8           AHC_OS_ReleaseMutex(AHC_OS_MUTEXID ulMutexId);
UINT8           AHC_OS_CreateEventFlag(UINT32 ulFlagValues);
UINT8           AHC_OS_WaitFlags(AHC_OS_FLAGID ulFlagID, AHC_OS_FLAGS flags, AHC_OS_FLAG_WTYPE waitType, 
                                 UINT32 ulTimeout, AHC_OS_FLAGS *ret_flags);
UINT8           AHC_OS_SetFlags(AHC_OS_FLAGID ulFlagID, AHC_OS_FLAGS flags, AHC_OS_FLAG_OPT opt);
AHC_OS_MQID     AHC_OS_CreateMQueue(void **msg, UINT8 ubQueueSize);
UINT8           AHC_OS_DeleteMQueue(AHC_OS_MQID ulMQId);
UINT8           AHC_OS_GetMessage(AHC_OS_MQID ulMQId, void **msg, UINT32 ulTimeout);
UINT8           AHC_OS_PutMessage(AHC_OS_MQID ulMQId, void *msg);
UINT8           AHC_OS_Sleep(UINT16 usTickCount);
void            AHC_OS_SleepMs(UINT32 uiMiliSecond);
UINT8           AHC_OS_SetTime(UINT32 uiTickCount);
UINT8           AHC_OS_GetTime(UINT32 *uiTickCount);
AHC_OS_TMRID    AHC_OS_StartTimer(UINT32 ulPeriod, AHC_OS_TMR_OPT opt, AHC_OS_TMR_CALLBACK callback,void *callback_arg);
UINT8           AHC_OS_StopTimer(AHC_OS_TMRID ulTmrId, AHC_OS_TMR_OPT opt);
UINT8			AHC_OS_Sleep(UINT16 usTickCount);
void 			AHC_OS_Delay(UINT8 hours, UINT8 minutes, UINT8 seconds, UINT16 milli);


#endif // _AHC_OS_H_
