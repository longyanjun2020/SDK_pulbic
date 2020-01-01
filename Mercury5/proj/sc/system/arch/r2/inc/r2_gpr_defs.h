#ifndef __R2_GPR_DEFS_H__
#define __R2_GPR_DEFS_H__

#define HZ 1


/**
 * This file will be included by assembly.
 * So use __ASSEMBLY__ to exclude the C
 * structure part.
 *
 */
#ifndef __ASSEMBLY__
struct regs {
	unsigned long  pc;
	unsigned long  sp;
	unsigned long  gprs[30];
	unsigned long  orig_gpr3;  /* Used for restarting system calls */
	unsigned long  sr;
	unsigned long  mac_hi;
	unsigned long  mac_lo;
};
#endif /* __ASSEMBLY__ */

// Size of all other registers
#define OR1K_REGSIZE    4

#if (__GNUC__ >= 4)
#define OR1K_REDZONE    32
#else
#define OR1K_REDZONE 0
#endif

// Notice that this file must be consistent with r2_traps.h and struct regs

#define R2_PC     0
#define R2_SP     4
#define GPR2      8
#define GPR3      12
#define GPR4      16
#define GPR5      20
#define GPR6      24
#define GPR7      28
#define GPR8      32
#define GPR9      36
#define GPR10     40
#define GPR11     44
#define GPR12     48
#define GPR13     52
#define GPR14     56
#define GPR15     60
#define GPR16     64
#define GPR17     68
#define GPR18     72
#define GPR19     76
#define GPR20     80
#define GPR21     84
#define GPR22     88
#define GPR23     92
#define GPR24     96
#define GPR25     100
#define GPR26     104
#define GPR27     108
#define GPR28     112
#define GPR29     116
#define GPR30     120
#define GPR31     124
#define ORIG_GPR3 128
#define R2_SR     132
#define SPR_MACHI_SAV 136
#define SPR_MACLO_SAV 140
#define SPR_EACC_SAV 144
#define SPR_EEAR_SAV 148
#define SPR_EPCR 152
#define SPR_ESR 156

#define REG_VECTOR (SPR_ESR + OR1K_REGSIZE)

// Red zone is the area below stack pointer which gcc can use in leaf
// functions. For this to work, we must make sure red zone is not
// overwritten at interrupts / exceptions.
#define REG_REDZONE  REG_VECTOR  + OR1K_REDZONE


//#define OR1K_GPRSIZE    4

// originally this was a hard coded literal "168"
#define CONTEXT_FRAME_SIZE    (REG_REDZONE)


#endif /* _R2_GPR_DEFS_H__ */
