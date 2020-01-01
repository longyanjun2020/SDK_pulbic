/*
*===============================================================================
*                                    USB-EH
*                          The USB Embedded Host Stack
*                               OS ABSTRACTION
*
*              Copyright (c) 2014, Alpha Imaging Technology Corp.
*                             All Rights Reserved
*
* File    : usbeh_os.h
* Author  : Alterman
* Version : v1.0
*===============================================================================
*/

#ifndef _USBEH_OS_H_
#define _USBEH_OS_H_

#include "usbeh_cfg.h"
//#include "os_cpu.h"
#include "os_wrap.h"

/*
*-------------------------------------------------------------------------------
*                                 OS Data Types
*-------------------------------------------------------------------------------
*/
typedef UINT    OS_SEM;
typedef UINT    OS_MSGQ;
typedef UINT    OS_STACK;
typedef void  (*OS_TASK)(void *param);

/*
*-------------------------------------------------------------------------------
*                               OS Sleep function
*-------------------------------------------------------------------------------
*/
#define USBEH_OS_SLEEP_MS(ms)       MMPF_OS_Sleep(ms)

/*
*-------------------------------------------------------------------------------
*                            OS CPU related functions
*-------------------------------------------------------------------------------
*/
#define USBEH_ENTER_CRITICAL(cpsr)  {/*cpsr = OS_CPU_SR_Save();*/}
#define USBEH_EXIT_CRITICAL(cpsr)   {/*OS_CPU_SR_Restore(cpsr);*/}

/*
*-------------------------------------------------------------------------------
*                            OS Layer Public functions
*-------------------------------------------------------------------------------
*/
extern INT  USBEH_OS_Init(void);
extern INT  USBEH_OS_CreateTask(UCHAR priority, OS_TASK handler, void *param,
                                UINT stack_bottom, UINT stack_top);
extern INT  USBEH_OS_CreateSem(OS_SEM *sem_id, UCHAR init_value);
extern INT  USBEH_OS_DestroySem(OS_SEM sem_id);
extern INT  USBEH_OS_AcquireSem(OS_SEM sem_id, UINT timeout);
extern INT  USBEH_OS_ReleaseSem(OS_SEM sem_id);
extern INT  USBEH_OS_AcceptSem(OS_SEM sem_id);
extern INT  USBEH_OS_CreateMsgQ(OS_MSGQ *msgq_id, void **msgq, UINT size);
extern INT  USBEH_OS_DestroyMsgQ(OS_MSGQ msgq_id);
extern INT  USBEH_OS_ReadMessage(OS_MSGQ msgq_id, void **msg, UINT timeout);
extern INT  USBEH_OS_SendMessage(OS_MSGQ msgq_id, void *msg);

#endif //_USBEH_OS_H_