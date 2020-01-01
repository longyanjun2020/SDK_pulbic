/****************************************************************************/
/*  $Workfile::   fms_lowl_bsp.h                                          $ */
/*--------------------------------------------------------------------------*/
/*  Scope   :  FMS low level functions: common definitions                  */
/*                                                                          */
/*  Contents:  Hardware related functions and constants                     */
/*                                                                          */
/****************************************************************************/



#ifndef _9f791d7296bc25b09d529eff015f3fe0_INCLUDED_FMS_LOWL_BSP_H
#define _9f791d7296bc25b09d529eff015f3fe0_INCLUDED_FMS_LOWL_BSP_H

#include "kernel.h"

extern u32 *QbCnt_Addr;

/****************************************************************************/
/*                                                                          */
/*   COMMON SYSTEM INLINE FUNCTIONS                                         */
/*                                                                          */
/****************************************************************************/
/* Read TBU_QBCNT_REG */
// Be careful, the address can change
#define fms_LowLevel_GetQbCnt() (*QbCnt_Addr)

/****************************************************************************/
/* ERASE PROCESS INTERRUPTIONS MONITORING UTILITIES                         */
/****************************************************************************/

/*
 * Usage:
 * FMS_ERASE_MONITOR_INIT at the beginning of the erase function
 * FMS_ERASE_MONITOR_LEAVENOW is true when a suspend operation is needed
 * FMS_ERASE_MONITOR_RELOAD to refresh some parameters (current time, etc...)
 */
#define FMS_ERASE_MONITOR_INIT(_VALUE_) u32 l__u32_QbCnt_BackupValue = fms_LowLevel_GetQbCnt(); \
                                          u32 l__u32_QbCnt_Value; \
                                          u32 l__u32_IterationCnt = _VALUE_

   /* a FINT is generated when QbCNT is reset */
   /* For WHAT2: If QBCNT has reached the reset value
    * (FRAME_CLK register) and has rolled over from 
    * 0x0000 or if the iteration count is elapsed */
                                          
#define FMS_ERASE_MONITOR_LEAVENOW   (( l__u32_QbCnt_BackupValue > ( l__u32_QbCnt_Value = fms_LowLevel_GetQbCnt() ) )\
                                       || ( (--l__u32_IterationCnt) == 0 ))

/* Save QBCNT value for the next check iteration */
#define FMS_ERASE_MONITOR_RELOAD        l__u32_QbCnt_BackupValue = l__u32_QbCnt_Value
   


#endif /* ! _9f791d7296bc25b09d529eff015f3fe0_INCLUDED_FMS_LOWL_BSP_H   */
