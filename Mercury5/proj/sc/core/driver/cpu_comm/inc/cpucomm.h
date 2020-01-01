#ifndef _INCLUDE_CPU_COMM_COMMUNICATION_H_
#define _INCLUDE_CPU_COMM_COMMUNICATION_H_

#include "mmpf_typedef.h"
#include "os_wrap.h"
#include "cpucomm_if.h"
#include "mmp_lib.h"

//------------------------------------------------------------------------------
//  Macro       : CpuComm_CriticalSectionInit()
//  Description : Encapsulated for critical section
//------------------------------------------------------------------------------
#define CpuComm_CriticalSectionDeclare()
#define CpuComm_CriticalSectionInit()      OS_CRITICAL_INIT()
#define CpuComm_CriticalSectionEnter()     OS_ENTER_CRITICAL()
#define CpuComm_CriticalSectionLeave()     OS_EXIT_CRITICAL()

//------------------------------------------------------------------------------
//  Macro       : CpuComm_DbgMsg()
//  Description : Define the debug message output func
//------------------------------------------------------------------------------
#if 1 // Disable debug message
#define CpuComm_DbgMsg(...)
#else
#if (CPU_ID == CPU_A)
#define CpuComm_DbgMsg printc
#elif (CPU_ID == CPU_B)
#define CpuComm_DbgMsg printc
#endif
#endif

#endif // _INCLUDE_CPU_COMM_COMMUNICATION_H_
