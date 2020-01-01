//==============================================================================
//
//  File        : bsp.h
//  Description : Board support package source code
//  Author      : Jerry Tsao
//  Revision    : 1.0
//
//==============================================================================

#ifndef _BSP_H_
#define _BSP_H_

#include "mmp_err.h"
#include "mmpf_typedef.h"

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

/** @addtogroup BSP
@{
*/

typedef void (*ARM_EXCEPTION_HANDLERCB)(void);

MMP_ERR MMPF_BSP_Initialize(void);
MMP_ERR MMPF_BSP_InitializeInt(void);
MMP_ERR MMPF_BSP_InitializeTimer(void);
MMP_ERR MMPF_BSP_IntHandler(void);
void MMPF_MMU_Initialize(unsigned int *pTranslationTable,unsigned int *pCoarsePageTable);
void MMPF_MMU_Deinitialize(void);

MMP_ERR MMPF_Register_ARM_ExceptionHandlerCB(ARM_EXCEPTION_HANDLERCB pARMExceptionHandlerCB);
void ARM_ExceptionHandler(MMP_ULONG exceptID, MMP_ULONG lr);

/** @} */ // end of BSP

#endif //_BSP_H_

