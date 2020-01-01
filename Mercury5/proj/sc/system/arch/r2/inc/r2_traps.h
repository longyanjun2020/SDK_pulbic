#include <r2_gpr_defs.h>

//-----------------------------------------------------------------------------

// OpenRISC thread and interrupt saved state structure. These offsets
// must match the layout of the HAL_SavedRegisters struct in
// hal_arch.h. Do not change this without changing the layout there,
// or viceversa.

// Notice that this file must be consistent with r2_gpr_defs.h

typedef struct __hal_save__
{
	unsigned long  pc;
	unsigned long  sp;
	unsigned long  gprs[30];
	unsigned long  orig_gpr3;  /* Used for restarting system calls */
	unsigned long  sr;
	unsigned long  machi;          // High and low words of
	unsigned long  maclo;          //   multiply/accumulate reg
	unsigned long  eacc;
	unsigned long  eear;
	unsigned long  epcr;
	unsigned long  esr;
	unsigned long  vector;

	// red zone
	//    char                    redzone[OR1K_REDZONE];
	char                    redzone[OR1K_REDZONE];
} HAL_SavedRegs,*pHAL_SavedRegs;

