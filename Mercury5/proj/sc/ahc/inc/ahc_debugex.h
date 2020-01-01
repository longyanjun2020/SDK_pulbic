//==============================================================================
//
//  File        : ahc_debugex.h
//  Description : AHC Debug header file
//  Author      : Caesar Chang
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_DEBUG_EX_H_
#define _AHC_DEBUG_EX_H_

#include "ahc_common.h"

#ifndef FUN
// FUNCTION INFORMATION
// print current functin name /line number /return address
#define FUN  {int __LR__; __asm { mov __LR__,r14; } 	printc( "%s():%d <- <0x%08X> \n",__func__,__LINE__, __LR__); }
#endif

#ifndef FUNCD 
// FUNCTION INFORMATION DETAIL
// print current functin name /line number /current address / return address
#define FUNCD {int __LR__,__PC__; __asm { mov __LR__,r14; mov __PC__,r15 } 	printc( "%s - %s():%d  <0x%08X><- <0x%08X>\n",__FILE__,__func__,__LINE__, __PC__, __LR__); }
#endif

void     AHC_PrintCurrentTask(void);
AHC_BOOL AHC_CheckAllTaskStack(void);
void     AHC_PrintCurrentTask(void);
void     AHC_PrintAllTask(void);
void     AHC_DebugPrintReadyTable(void);
void 	 AHC_MemoryMonitor( AHC_BOOL enable );
INT16U   AHC_DBG_GetCurPrioEx(void);
#endif
