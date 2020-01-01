//==============================================================================
//
//  File        : mmpf_uart.h
//  Description : INCLUDE File for the Firmware Timer Control Driver
//  Author      : Jerry Lai
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_TIMER_H_
#define _MMPF_TIMER_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMPF_TIMER_ID
{
    /* MMPF_TIMER_0 = 0, Timer 0 is reserved for OS */
    MMPF_TIMER_1 = 1,
    MMPF_TIMER_2,
    MMPF_TIMER_3,
    MMPF_TIMER_4,
    MMPF_TIMER_5,
    MMPF_TIMER_MAX,
    #if defined( __RTK_OS__ )
    MMPF_TIMER_VID = 1811,
    #endif
} MMPF_TIMER_ID;

typedef enum _MMPF_TIMER_PRECISION
{
    MMPF_TIMER_SEC = 0,
    MMPF_TIMER_MILLI_SEC = 1,
    MMPF_TIMER_MICRO_SEC = 2
} MMPF_TIMER_PRECISION;

typedef enum _MMPF_TIMER_INT_MODE
{
    MMPF_TIMER_ONE_SHOT = 0,
    MMPF_TIMER_PERIODIC = 1
} MMPF_TIMER_INT_MODE;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef void TimerCallBackFunc(void);

typedef struct _MMPF_TIMER_ATTR {
    MMPF_TIMER_PRECISION TimePrecision;
    MMP_ULONG            ulTimeUnits;
    TimerCallBackFunc    *Func;
    MMPF_TIMER_INT_MODE  bIntMode;
} MMPF_TIMER_ATTR;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

__inline void *GetpTC(MMPF_TIMER_ID id);

MMP_ERR MMPF_Timer_Start(MMPF_TIMER_ID id, MMPF_TIMER_ATTR *TimerAttribute);
MMP_ERR MMPF_Timer_Stop(MMPF_TIMER_ID id);
MMP_ULONG MMPF_Timer_GetTimeDetail(MMPF_TIMER_ID id, MMP_ULONG precision);

#if defined(ALL_FW)

typedef void (*MMPF_STOPWATCH_REPORT) (MMP_ULONG ms, MMP_ULONG detail);

typedef struct _MMPF_STOPWATCH {
    MMPF_TIMER_ID 	id;
    MMP_ULONG 		precision;
    MMP_ULONG 		ms;
    MMP_ULONG 		detail;
    MMP_ULONG 		sumMs;
    MMP_ULONG 		sumDetail;
    MMP_ULONG 		count;
    MMP_ULONG 		trigger;
    char 			name[12];
    MMPF_STOPWATCH_REPORT reportFunc;
} MMPF_STOPWATCH, *MMPF_STOPWATCH_HANDLE;

// These functions are used for performance measurement only.
// It depends on 1ms HW timer
MMP_ERR MMPF_Stopwatch_Open(MMPF_STOPWATCH_HANDLE* h);
// Register unnamed handler. It is used for customer handler
MMP_ERR MMPF_Stopwatch_RegisterHandler(MMPF_STOPWATCH_HANDLE h, MMP_ULONG triggerCount, MMPF_STOPWATCH_REPORT reportFunc);
// Register handler with name.
MMP_ERR MMPF_Stopwatch_Register(MMPF_STOPWATCH_HANDLE h, MMP_ULONG triggerCount, MMPF_STOPWATCH_REPORT reportFunc, char *szName);
MMP_ERR MMPF_Stopwatch_Start(MMPF_STOPWATCH_HANDLE h);
MMP_ERR MMPF_Stopwatch_Stop(MMPF_STOPWATCH_HANDLE h);
MMP_ERR MMPF_Stopwatch_Reset(MMPF_STOPWATCH_HANDLE h);

/*
 * For streaming timestamp
 * It takes time more than 1 ms in JPEG ISR, cause timer0 (OS timer) lost few interrupts.
 * and the timestamp sent to client will accumulate error between stream time and player time.
 * Open TIMER_3 and give 4/1000 second to count to solve this issue.
 */
void MMPF_Streaming_TimerOpen(void);
void MMPF_Streaming_TimerClose(void);
unsigned int MMPF_Get_Streaming_Time(void);
#endif

#endif // _MMPF_TIMER_H_
