#ifndef ONCE_HAL_MIPS_REGS_H
#define ONCE_HAL_MIPS_REGS_H
////////////////////////////////////////////////////////////////////////////////
///@file hal_mips-regs.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_hal.h>

#ifdef ARC_HAL_COMMON_EXPORT_CPU_MACROS

/* This value must agree with NUMREGS in mips-stub.h. */

#if defined(PKG_HAL_MIPS_GDB_REPORT_CP0)
#define NUM_REGS   107
#else
#define NUM_REGS    90
#endif

#ifdef __mips64
  #define REG_SIZE 8
#else
  #define REG_SIZE 4
#endif

/* General register names for assembly code. */
#endif // ifdef ARC_HAL_COMMON_EXPORT_CPU_MACROS

#endif // ifndef ONCE_HAL_MIPS_REGS_H
