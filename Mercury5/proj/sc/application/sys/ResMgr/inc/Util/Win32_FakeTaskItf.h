/**
* @file Win32_FakeTaskItf.h
*
* This header file defines the interfaces of fake task for win32
* simulations
*/

#ifndef __WIN32_FAKETASKITF_H__
#define __WIN32_FAKETASKITF_H__

#ifdef __SDK_SIMULATION__
/*=============================================================*/
// Include Files
/*=============================================================*/
#include <windows.h>
#include <process.h>
#include <stdio.h>
#include "DataStructItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
#define WIN32_MAX_TASK_NUM      10
#define WIN32_TRACE_BUFF_SIZE   255

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef void* Win32TaskHdl;

typedef void (*TaskEntry) (Win32TaskHdl pTaskHdl);

typedef struct Win32Task_t_
{
    TaskEntry EntryFunc;
    u32 uThreadID;
    void *pThreadHwnd;
    DataStruct_t *pQueue;
    //HANDLE pQueueSemaphore;
    CRITICAL_SECTION tCriticalSection;
    HANDLE pEvent;
} Win32Task_t;

typedef struct Win32Msg_t_
{
    u32 uMsgType;
    void *pMsgBody;
} Win32Msg_t;

typedef void (*TimerCallback) (void *pCusData);

typedef struct Win32Timer_t_
{
    u16 uDelay;
    TimerCallback TimeOut;
    void *pCusData;
    void *pThreadHwnd;
    u32 uThreadID;
    bool bStop;
} Win32Timer_t;

typedef struct Win32CriSec_t_
{
    CRITICAL_SECTION tCriticalSection;
} Win32CriSec_t;

typedef struct Win32Semaphore_t_
{
    HANDLE tSemaphore;
} Win32Semaphore_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void Win32_StartTask(Win32Task_t *pTask);
void Win32_StopTask(Win32Task_t *pTask);
Win32Msg_t* Win32_Receive(Win32Task_t *pTask);
void Win32_Send(Win32Task_t *pTask, Win32Msg_t *pMsg);
Win32Timer_t* Win32_StartTimer(u32 uDelay, TimerCallback TimeOut, void *pCusData);
void Win32_StopTimer(Win32Timer_t *pTimer);
Win32CriSec_t* Win32_CreateCriticalSection();
void Win32_EnterCriticalSection(Win32CriSec_t *pCriSec);
void Win32_LeaveCriticalSection(Win32CriSec_t *pCriSec);
void Win32_DestroyCriticalSection(Win32CriSec_t *pCriSec);

Win32Semaphore_t* Win32_CreateSemaphore(u16 nInitVal, u16 nMaxVal);
void Win32_ObtainSemaphore(Win32Semaphore_t *pWin32Semaphore);
void Win32_ProduceSemaphore(Win32Semaphore_t *pWin32Semaphore);
void Win32_DestroySemaphore(Win32Semaphore_t *pWin32Semaphore);

void Win32_Trace(u32 level, char *strFormat, ...);

#endif //__SDK_SIMULATION__

#endif //__WIN32_FAKETASKITF_H__
