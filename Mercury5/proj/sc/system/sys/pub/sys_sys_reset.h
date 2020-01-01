/****************************************************************************/
/*  File    : sys_sys_reset.h                                                    */
/*--------------------------------------------------------------------------*/
/*  Scope   : Reset management                              */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/****************************************************************************/



#ifndef __SYS_SYS_RESET_H__
#define __SYS_SYS_RESET_H__

#include "vm_types.ht"

void ke_Reset(void);

/**
 * @brief Restarts the software by resetting the core.
 * @warning Does not signal itself through the Debug Data Area
 */
void ke_FullReset(void);

/**
 * @brief Special extended type of ke_FullReset.
 * @warning Does not signal itself through the Debug Data Area
 */
void ke_FullReset_Ext(void);

/* @brief SIM reset: special type of SW reset.
    Branch to 0 directly and
        1. Skip the LCD controller init in DrvPowerMmpIo
        2. Skip reset pin handling in LCD_Init_first() function
        3. Skip LCD init in LCD_Init_first() function
 */
void ke_SimReset(void);

/**
 * @brief Software reset: performs a warm start and reset the core
 */
void sys_PerformSoftReset(void);

/**
 * @brief Restarts the software after a fatal error.
 */
void sys_DieOnError(u32 i_u32_ErrorStatus);

/**
 * @brief Restarts the software after a double fault.
 */
void sys_DieOnDoubleFault(void);

#endif //__SYS_SYS_RESET_H__

