/******************************************************************/
/*  File    : rtkdata.hv                                          */
/*-------------------------------------------------------------   */
/*  Scope   :   Declaration/definition of internal RTK global     */
/*              variables.                                        */
/*                                                                */
/*                                                                */
/******************************************************************/

#ifndef __SYS_RTK_HV_H__
#define __SYS_RTK_HV_H__

#include "sys_rtk_config.h"
#include "comdefs.hc"   /* Common define flags */


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

/******* Monitor Heap Memory ************/

#ifdef __RTK_HEAP_DIAGNOSE__
#ifdef __RTK_DATA__
 u16 MonitorHeapMemory[25][3] = 0;
#else
 RtkDefExtern u16 MonitorHeapMemory[25][3]; 	/* 25 taches maxi! */
#endif
#endif


RtkDefExtern    rtk_MaskImage_t  Rtk_MaskInt;
RtkDefExtern    bool		 Rtk_TaskMarkerOwner;
RtkDefExtern    u8		*Rtk_PtrMarkerStack;

//RtkDefExtern    u8               Rtk_NbOfTask;
RtkDefExtern    u8               Rtk_NbOfMBox;
RtkDefExtern    u16               Rtk_NbOfSem;
RtkDefExtern    u16              Rtk_RegionCount;

#ifdef __RTK_DIAGNOSE_ENHANCE__
RtkDefExtern    u32              Rtk_IsIrqFiqMode;
#endif

RtkDefExtern    rtk_Timer_t     *Rtk_PtrFirstFreeTimer;
RtkDefExtern    rtk_Timer_t     *Rtk_PtrFirstUsedTimer;
RtkDefExtern    rtk_Timer_t     *Rtk_PtrLastUsedTimer;
RtkDefExtern    rtk_Timer_t     *Rtk_PtrFirstExpiredTimer;
RtkDefExtern    rtk_Timer_t     *Rtk_PtrFirstTimer;
RtkDefExtern    u32              Rtk_TailTimerCount;

RtkDefExtern    u16              Rtk_KernelVersion;
#if defined(__MSTAR_DUAL_SIM__) && defined(__MSTAR_DUAL_SIM_REDUCE_CODE__) && defined(__MSTAR_DUAL_SIM_DUP_GLOB__) && !defined(__SDK_SIMULATION__)
extern          u8               Rtk_CurrentTask;
#else
RtkDefExtern    volatile u8      Rtk_CurrentTask;
#endif

#if defined(__TIME_SLICE_SCHEDULE__)
RtkDefExtern    u8               Rtk_LastTask;
//RtkDefExtern    u8               Rtk_HacTaskId;
#endif

RtkDefExtern    u32	             RtkRegisters[4];														// R13, R14, PC
RtkDefExtern    u32	             RtkExceptionSP;

RtkDefExtern    rtk_Task_t      *Rtk_PtrCurrentTask;
RtkDefExtern    rtk_Task_t      *rtk_TaskPrioList;

RtkDefExtern    rtk_Task_t       *rtk_Tasks[RTK_MAX_TASKS];
RtkDefExtern    u32              rtk_SystemTasksCount;
RtkDefExtern    u32              rtk_CustomerTasksCount;

RtkDefExtern    u32              RtkDynamicCustomerTasksCount;
RtkDefExtern    u32              RtkMaxDynamicCustomerTasksCount;
RtkDefExtern    u32              RtkDynamicCustomerTasksReleaseCount;
RtkDefExtern    u8               RtkReleasedDynTaskID[RTK_MAX_CUSTOMER_TASKS];

RtkDefExtern    rtk_Mailbox_t   rtk_Mailboxes[RTK_MAX_MAILBOXES];

// to help improve the scheduling times
RtkDefExtern    u8              rtk_stateBitmap[RTK_TASKS_BITMAP_LENGTH];
RtkDefExtern    rtk_Task_t      * rtk_BitmapIdx2task[RTK_MAX_TASKS];
RtkDefExtern    u32              rtk_TaskTimeoutCount[RTK_MAX_TASKS]; //Task monitor
RtkDefExtern    u32              rtk_TaskTimeoutMaxCount[RTK_MAX_TASKS];

RtkDefExtern    rtk_Mailbox_t   *Rtk_Ptr1stMBox;
RtkDefExtern    rtk_Semaphor_t  *Rtk_Ptr1stSem;
RtkDefExtern    rtk_Envelop_t   *Rtk_PtrFreeEnv;
RtkDefExtern    rtk_Envelop_t   *Rtk_PtrFirstEnv;
RtkDefExtern    rtk_Envelop_t   *Rtk_PtrLastEnv;
RtkDefExtern    u16             Rtk_NbOfFreeEnv;
RtkDefExtern    bool            Rtk_WorthItSched;

#define         rtk_WorthItSched Rtk_WorthItSched
RtkDefExtern  volatile  bool             rtk_bool_DiferredSched;

/*
** RDO: the sizing of 'rtk_HeapWalkStack' defines the maximum number of
** re-entrancy levels in _GetHeapMemory().
** For the time being, 16 is deemed as a sensible maximum.
** Note that the highest level of reentrancy equals to the amount of RTK
** tasks plus the maximum number of nested interrupts. Needless to say that
** this highest level is very unlikely to be reached.
** CEVEAT: no check is performed to prevent this re-entrancy stack from
** overflowing so it must be carefully sized!!!
*/



RtkDefExtern    void (*ExcptHandler) _PROTO((u8 Status, u32 Param));

#ifdef __SDK_SIMULATION__
RtkDefExtern void* TraceHwnd;
RtkDefExtern    u8 InterruptOn;
RtkDefExtern u8 ChargeTable[100];
RtkDefExtern u8 ChargeTableIndex;
#endif //__SDK_SIMULATION__


#undef RtkDefExtern


#endif   /* __SYS_RTK_HV_H__ */

