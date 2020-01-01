//==============================================================================
//
//  File        : AHC_DebugEx.c
//  Description : AHC Debug function
//  Author      : Caesar Chang
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ait_utility.h"
#include "mmps_system.h"
#include "mmpf_system.h"
#include "os_wrap.h"
#include "ahc_debugex.h"
#include "ahc_uf.h"
#include "pmuctrl.h"
#include "mmps_dma.h"
#include "mmu.h"

#define printc UartSendTrace

/*******************************************************************************
 *
 *   STRUCTURE
 *
*******************************************************************************/

/*===========================================================================
 * Extern function
 *===========================================================================*/ 


/*===========================================================================
 * Main body
 *===========================================================================*/

void AHC_MemoryMonitor( AHC_BOOL enable )
{
}

void AIHC_DBG_PrintHorizontalLine(void)
{
    printc( "\r\n\r\n===================================\n");
}

void AIHC_DBG_PrintTaskTable( INT8U* pTaskTable )
{
	printc( "\n" );
}

//void AIHC_DBG_PrintTCB(OS_TCB* pTCB)
void AIHC_DBG_PrintTCB(void)
{

    AIHC_DBG_PrintHorizontalLine();
}

/*
    Check if a stack is overflowed.
*/
//AHC_BOOL AIHC_DBG_CheckStack(OS_TCB* pTCB)
AHC_BOOL AIHC_DBG_CheckStack(void)
{
	return AHC_TRUE;
}

INT16U AHC_DBG_GetCurPrioEx(void)
{
	return 0;
}

AHC_BOOL AHC_CheckAllTaskStack(void)
{
	
    return AHC_TRUE;
}

void AHC_DebugPrintReadyTable(void)
{
	printc( " ===== READY TABLE =====\n" );
	
	//AIHC_DBG_PrintTaskTable( OSRdyTbl );
	
	printc( " ===== READY TABLE END =====\n" );
}

void AHC_PrintUITask(void)
{
}

void AHC_PrintAllTask(void)
{
}

void AHC_PrintCurrentTask(void)
{
}

void ARM_ExceptionHandlerCB(void)
{
}

int ARM_ExceptionHandler_Module_Init(void)
{
    printc("[ARM_ExceptionHandler_Module_Init]\r\n");
    MMPF_Register_ARM_ExceptionHandlerCB(ARM_ExceptionHandlerCB);
    return 0;    
}

#pragma arm section code = "initcall1", rodata = "initcall1", rwdata = "initcall1",  zidata = "initcall1" 
#pragma O0
ait_core_init(ARM_ExceptionHandler_Module_Init);
#pragma
#pragma arm section rodata, rwdata ,  zidata 
