/****************************************************************************/
/*  $Workfile::   sys_sys_premain.h                                           $ */
/*--------------------------------------------------------------------------*/
/*  Scope   :                                                               */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*                                                                          */
/****************************************************************************/


#ifndef __SYS_SYS_PREMAIN_H__
#define __SYS_SYS_PREMAIN_H__

s32         sys_premain(void);
extern u32  sys_RAMSize;
extern u32  sys_ResetPattern;
u32         sys_GetRamSize(u32 i__u32_RamBase); 

/* The genuine main function */
s32         main(void);

#define SOFT_RESET_PATTERN 0xabcd

/* List of SIGNAL for __rt_signal */
#define SIGABRT       0x01 /* call from software to abort() or assert() */
#define SIGFPE        0x02 /* Arithmetic exception */
#define SIGILL        0x03 /* Illegal instruction */
#define SIGINT        0x04 /* Attention request from user */
#define SIGSEGV       0x05 /* Bas memory access */
#define SIGTERM       0x06 /* Termination request */
#define SIGSTAK       0x07 /* Stack overflow detected */
#define SIGRTRED      0x08 /* Redirection failed on a runtime library */
#define SIGRTMEM      0x09 /* Out of heap space after initialization or corruption */
#define SIGUSR1       0x0A /* USER signal 1 */
#define SIGUSR2       0x0B /* USER signal 2 */
#define SIGPVFN       0x0C /* Pure virtual function called from C++ */
#define SIGCPPL       0x0D /* Exception from C++ */
#define SIGOUTOFHEAP  0x0E /* Return from C++ operator new when out of heap */

/* Type for SIGFPE */
#define FE_EX_INEXACT   0x10
#define FE_EX_UNDERFLOW 0x08
#define FE_EX_OVERFLOW  0x04
#define FE_EX_DIVBYZERO 0x02
#define FE_EX_INVALID   0x01
#define DIVBYZERO       0x00

bool sys_download_cable_is_plugged(void);


#define END_OF_L1PTE     		0xffffffff

typedef struct L1PTE_s
{
    u32 nStartAddrV;
    u32 nStartAddrP;
    u32 nSize;
    u32 nPteOption;
} L1PTE_t;


#endif //__SYS_SYS_PREMAIN_H__

