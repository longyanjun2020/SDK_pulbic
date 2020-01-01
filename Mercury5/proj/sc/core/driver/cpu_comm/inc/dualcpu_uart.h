#ifndef _INCLUDE_DUAL_CPU_UART_H_
#define _INCLUDE_DUAL_CPU_UART_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if (1)

#if (CPU_ID == CPU_B )
MMP_BOOL CpuB_Printf( const char* pszFormat, ... );
#else
#include "ahc_utility.h"
#define CpuB_Printf printc
#endif

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
