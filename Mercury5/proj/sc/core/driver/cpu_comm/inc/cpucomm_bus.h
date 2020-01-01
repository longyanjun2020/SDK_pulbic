#ifndef __CPU_COMM_BUS_H_
#define __CPU_COMM_BUS_H_

#include "cpucomm_core.h"

//------------------------------------------------------------------------------
//  Macro       : CPUCOMM_MODULE_INIT
//  Description : CPU_COMM_ENTRY are destributed over source files,
//                and init functions are gathered in section .CpuCommTable
//------------------------------------------------------------------------------
typedef CPU_COMM_ERR (*CPUCOMM_MODULE_FUN)(void);
#define __VAR_NAME(x,y) g_pfCpuCommModule##x##y
#define _VAR_NAME(x,y) __VAR_NAME(x,y)
#define CPUCOMM_MODULE_INIT( fInit ) \
                _Pragma("arm section rodata = \"CpuCommModuleInit\"") \
                const CPUCOMM_MODULE_FUN _VAR_NAME(fInit, __LINE__) = fInit; \
                _Pragma("arm section rodata")

#define CPUCOMM_MODULE_EXIT( fExit) \
                    _Pragma("arm section rodata = \"CpuCommModuleExit\"") \
                    const CPUCOMM_MODULE_FUN _VAR_NAME(fExit, __LINE__) = fExit; \
                    _Pragma("arm section rodata")


// Constructor & Destructor (for dual CPU)
CPU_COMM_ERR CpuComm_Init(void);
CPU_COMM_ERR CpuComm_Start(void);
void CpuComm_Destroy(void);

#endif
