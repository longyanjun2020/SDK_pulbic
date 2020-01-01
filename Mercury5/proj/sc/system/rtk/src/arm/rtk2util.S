#include <r2_spr_defs.h>
#include <r2_gpr_defs.h>
#include <r2_asm_defs.h>

#define TASK_CONTEXT_SIZE               CONTEXT_FRAME_SIZE

.extern BacktraceStackStart
.extern pLastRegisters
.extern HalStdaTimerGetTick
.extern checkDiTickCount

#if defined (__RTK_DIAGNOSE_ENHANCE__)

.global RTK_GET_REGISTERS

RTK_GET_REGISTERS:

	l.j	.
	l.jr	r9
#endif


.global RTK2_ENABLE
RTK2_ENABLE:
	l.mfspr r4, r0, SPR_SR

	l.andi  r3, r3, (SPR_SR_TEE|SPR_SR_IEE)  // make sure input arg only impact IEE/TEE
	l.or	r3, r4, r3

#ifdef __RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__
	l.andi  r4, r3, (SPR_SR_TEE|SPR_SR_IEE)  // check if it is really enabled
	l.bnei  r4, (SPR_SR_TEE|SPR_SR_IEE), __NoEnableIntFlag

__EnableIntFlag:
	LOAD_SYMBOL_2_GPR(r4, RtkRegisters)
	l.sw 0(r4), r0
	l.sw 4(r4), r0
	l.sw 8(r4), r0
	l.sw 12(r4), r0                          // all clear
	LOAD_SYMBOL_2_GPR(r4, pLastRegisters)
	l.lwz r4, 0(r4)
	l.sw 0(r4), r0
	l.sw 4(r4), r0
	l.sw 8(r4), r0
	l.sw 12(r4), r0                          // all clear
	LOAD_SYMBOL_2_GPR(r4, Rtk_RegionCount)   // Rtk_RegionCount--
	l.lwz r5, 0(r4)
	l.addi r5, r5, -1
	l.sw 0(r4), r5

#ifdef __INTERRUPT_INTEGRITY_PROTECT__
#else
        LOAD_SYMBOL_2_GPR(r4, sys_diProfile)
	l.lbz   r5, 0(r4)
	l.bnei  r5, 1, __without_profile_INT_2
#endif
        
	LOAD_SYMBOL_2_GPR(r5, sys_diLr)
	l.sw 0(r5), r9                        //;save caller in sys_diLr
	
	l.addi r1,r1,-8
	l.sw 0(r1), r9	                      //;save return address of RTK2_DISABLE_xx
	l.sw 4(r1), r3                        //;save return value of RTK2_DISABLE_xx
	
	LOAD_SYMBOL_2_GPR(r5, HalStdaTimerGetTick)            
	l.jalr r5
	LOAD_SYMBOL_2_GPR(r5, sys_diQbCount4)
	l.sw 0(r5), r3                        //; Store QB count 4 as 
	
	LOAD_SYMBOL_2_GPR(r5, checkDiTickCount)
	l.jalr r5

	l.lwz r9, 0(r1)                       //;restore return address of RTK2_DISABLE_xx from stack 
	l.lwz r3, 4(r1)                       //;restore return value of RTK2_DISABLE_xx from stack 
	l.addi r1,r1,8
	
__without_profile_INT_2:
	l.j RTK2_ENABLE_END

__NoEnableIntFlag:
	LOAD_SYMBOL_2_GPR(r4, pLastRegisters)
	l.lwz r4, 0(r4)
	l.sw 0(r4), r1
	l.sw 4(r4), r9
	l.sw 8(r4), r9
	l.mfspr r5, r0, SPR_SR
	l.sw 12(r4), r5                          // update latest
#endif

RTK2_ENABLE_END:
	l.mtspr	r0, r3, SPR_SR
	l.jr	r9

.global RTK2_ENABLE_K
RTK2_ENABLE_K:
	l.mfspr r4, r0, SPR_SR

	l.andi  r3, r3, (SPR_SR_TEE|SPR_SR_IEE)  // make sure input arg only impact IEE/TEE
	l.or	r3, r4, r3

#ifdef __RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__
	l.andi  r4, r3, (SPR_SR_TEE|SPR_SR_IEE)  // check if it is really enabled
	l.bnei  r4, (SPR_SR_TEE|SPR_SR_IEE), __NoDisableIntFlag_k

__DisableIntFlag_k:
	LOAD_SYMBOL_2_GPR(r4, RtkRegisters)
	l.sw 0(r4), r0
	l.sw 4(r4), r0
	l.sw 8(r4), r0
	l.sw 12(r4), r0                          // all clear
	LOAD_SYMBOL_2_GPR(r4, pLastRegisters)
	l.lwz r4, 0(r4)
	l.sw 0(r4), r0
	l.sw 4(r4), r0
	l.sw 8(r4), r0
	l.sw 12(r4), r0                          // all clear

#ifdef __INTERRUPT_INTEGRITY_PROTECT__
#else
        LOAD_SYMBOL_2_GPR(r4, sys_diProfile_K)
	l.lbz   r5, 0(r4)
	l.bnei  r5, 1, __without_profile_INT_K_2
#endif
        
	LOAD_SYMBOL_2_GPR(r5, sys_diLr_K)
	l.sw 0(r5), r9                        //;save caller in sys_diLr_K
	
	l.addi r1,r1,-8
	l.sw 0(r1), r9	                      //;save return address of RTK2_DISABLE_xx
	l.sw 4(r1), r3                        //;save return value of RTK2_DISABLE_xx
	
	LOAD_SYMBOL_2_GPR(r5, HalStdaTimerGetTick)            
	l.jalr r5
	LOAD_SYMBOL_2_GPR(r5, sys_diQbCount2)
	l.sw 0(r5), r3                        //; Store QB count 2 as 

	LOAD_SYMBOL_2_GPR(r5, checkDiQbCount)
	l.jalr r5
	
	l.lwz r9, 0(r1)                       //;restore return address of RTK2_DISABLE_xx from stack 
	l.lwz r3, 4(r1)                       //;restore return value of RTK2_DISABLE_xx from stack 
	l.addi r1,r1,8
	
__without_profile_INT_K_2:
	l.j RTK2_ENABLE_K_END

__NoDisableIntFlag_k:
	LOAD_SYMBOL_2_GPR(r4, pLastRegisters)
	l.lwz r4, 0(r4)
	l.sw 0(r4), r1
	l.sw 4(r4), r9
	l.sw 8(r4), r9
	l.mfspr r5, r0, SPR_SR
	l.sw 12(r4), r5                          // update latest
#endif

RTK2_ENABLE_K_END:
	l.mtspr	r0, r3, SPR_SR
	l.jr	r9

.global RTK2_DISABLE
RTK2_DISABLE:
	l.mfspr r4, r0, SPR_SR
	l.add   r5, r4, r0

	l.andi 	r3, r4, (SPR_SR_TEE|SPR_SR_IEE)  // make sure only output IEE/TEE

	l.movhi	r6, hi(~(SPR_SR_TEE|SPR_SR_IEE))
	l.ori	r6, r6, lo(~(SPR_SR_TEE|SPR_SR_IEE))

	l.and	r4, r4, r6                       // clear IEE and TEE.
	l.mtspr	r0, r4, SPR_SR

#ifdef __RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__
	LOAD_SYMBOL_2_GPR(r6, pLastRegisters)
	l.lwz r6, 0(r6)
	l.sw 0(r6), r1
	l.sw 4(r6), r9
	l.sw 8(r6), r9
	l.sw 12(r6), r5                          // update latest

	l.bnei  r3, (SPR_SR_TEE|SPR_SR_IEE), RTK2_DISABLE_END

	LOAD_SYMBOL_2_GPR(r6, RtkRegisters)
	l.sw 0(r6), r1
	l.sw 4(r6), r9
	l.sw 8(r6), r9
	l.sw 12(r6), r5                          // update latest

	LOAD_SYMBOL_2_GPR(r6, Rtk_RegionCount)   // Rtk_RegionCount++
	l.lwz r5, 0(r6)
	l.addi r5, r5, 1
	l.sw 0(r6), r5
#endif

#ifdef __INTERRUPT_INTEGRITY_PROTECT__
#else
        LOAD_SYMBOL_2_GPR(r4, sys_diProfile)
	l.lbz   r5, 0(r4)
	l.bnei  r5, 1, __without_profile_INT_1
#endif
        
	l.addi r1,r1,-8
	l.sw 0(r1), r9	                      //;save return address of RTK2_DISABLE_xx
	l.sw 4(r1), r3                        //;save return value of RTK2_DISABLE_xx
	
	LOAD_SYMBOL_2_GPR(r5, HalStdaTimerGetTick)            
	l.jalr r5
	LOAD_SYMBOL_2_GPR(r5, sys_diQbCount3)
	l.sw 0(r5), r3                        //; Store QB count 1 as 

	l.lwz r9, 0(r1)                       //;restore return address of RTK2_DISABLE_xx from stack 
	l.lwz r3, 4(r1)                       //;restore return value of RTK2_DISABLE_xx from stack 
	l.addi r1,r1,8
        
__without_profile_INT_1:

RTK2_DISABLE_END:
	l.jr	r9

.global RTK2_DISABLE_K
RTK2_DISABLE_K:
	l.mfspr r4, r0, SPR_SR
	l.add   r5, r4, r0

	l.andi 	r3, r4, (SPR_SR_TEE|SPR_SR_IEE)  // make sure only output IEE/TEE

	l.movhi	r6, hi(~(SPR_SR_TEE|SPR_SR_IEE))
	l.ori	r6, r6, lo(~(SPR_SR_TEE|SPR_SR_IEE))

	l.and	r4, r4, r6 // clear IEE and TEE.
	l.mtspr	r0, r4, SPR_SR

#ifdef __RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__
	LOAD_SYMBOL_2_GPR(r6, pLastRegisters)
	l.lwz r6, 0(r6)
	l.sw 0(r6), r1
	l.sw 4(r6), r9
	l.sw 8(r6), r9
	l.sw 12(r6), r5                          // update latest

	l.bnei  r3, (SPR_SR_TEE|SPR_SR_IEE), RTK2_DISABLE_K_END

	LOAD_SYMBOL_2_GPR(r6, RtkRegisters)
	l.sw 0(r6), r1
	l.sw 4(r6), r9
	l.sw 8(r6), r9
	l.sw 12(r6), r5
#endif

#ifdef __INTERRUPT_INTEGRITY_PROTECT__
#else
        LOAD_SYMBOL_2_GPR(r6, sys_diProfile_K)
	l.lbz   r5, 0(r6)
	l.bnei  r5, 1, __without_profile_INT_K_1
#endif
      
	l.addi r1,r1,-8
	l.sw 0(r1), r9	                      //;save return address of RTK2_DISABLE_xx
	l.sw 4(r1), r3                        //;save return value of RTK2_DISABLE_xx
	
	LOAD_SYMBOL_2_GPR(r5, HalStdaTimerGetTick)            
	l.jalr r5
	LOAD_SYMBOL_2_GPR(r5, sys_diQbCount1)
	l.sw 0(r5), r3                        //; Store QB count 1 as 

	l.lwz r9, 0(r1)                       //;restore return address of RTK2_DISABLE_xx from stack 
	l.lwz r3, 4(r1)                       //;restore return value of RTK2_DISABLE_xx from stack 
	l.addi r1,r1,8
	
__without_profile_INT_K_1:

RTK2_DISABLE_K_END:
	l.jr	r9

.global __current_sp

__current_sp:
	l.add 	r3, 	r0, 	r1
	l.jr 	r9


.global RTK1_ACTIVATE_TASK


RTK1_ACTIVATE_TASK:

#if defined(__MMU_STACK_PROTECTION__)

	//
	// if MMU_STACK_PROTECTIN is enabled...
	//


	l.j	.
#else

	l.addi 	r1, r1, -TASK_CONTEXT_SIZE
	l.sw	GPR2(r1), r2
	l.sw	GPR3(r1), r3
	l.sw	GPR4(r1), r4
	l.sw	GPR5(r1), r5
	l.sw	GPR6(r1), r6
	l.sw	GPR7(r1), r7
	l.sw	GPR8(r1), r8
	l.sw	GPR9(r1), r9
	l.sw	GPR10(r1), r10
	l.sw	GPR11(r1), r11
	l.sw	GPR12(r1), r12
	l.sw	GPR13(r1), r13
	l.sw	GPR14(r1), r14
	l.sw	GPR15(r1), r15
	l.sw	GPR16(r1), r16
	l.sw	GPR17(r1), r17
	l.sw	GPR18(r1), r18
	l.sw	GPR19(r1), r19
	l.sw	GPR20(r1), r20
	l.sw	GPR21(r1), r21
	l.sw	GPR22(r1), r22
	l.sw	GPR23(r1), r23
	l.sw	GPR24(r1), r24
	l.sw	GPR25(r1), r25
	l.sw	GPR26(r1), r26
	l.sw	GPR27(r1), r27
	l.sw	GPR28(r1), r28
	l.sw	GPR29(r1), r29
	l.sw	GPR30(r1), r30
	l.sw	GPR31(r1), r31

        // save MAC registers
        l.ori   r8, r0, SPR_MACLO
        l.mfspr r8, r8, 0
        l.sw    SPR_MACLO_SAV(r1), r8
        l.ori   r8, r0, SPR_MACHI
        l.mfspr r8, r8, 0
        l.sw    SPR_MACHI_SAV(r1), r8

	l.sw 	0(r3),	r1 // save r1 into SP

	l.mfspr	r8, r0, SPR_SR
	l.sw R2_SR(r1), r8

	l.sw R2_PC(r1), r9


	l.lwz	r1, 0(r4)
        b.mtspr r0, r1, SPR_CONTEXT_SAVE1

	l.lwz 	r5, 4(r4)

	l.sfeq 	r5, r0
	l.bf 1f

	l.mfspr r7, r0, SPR_SR
	l.ori	r7, r7, (SPR_SR_IEE|SPR_SR_TEE)
//	l.mtspr	r0, r7, SPR_ESR_BASE
	l.mtspr	r0, r7, SPR_CONTEXT_SAVE3

	l.lwz	r5, 4(r4)
//	l.mtspr	r0, r5, SPR_EPCR_BASE
	l.mtspr	r0, r5, SPR_CONTEXT_SAVE2

	l.sw	4(r4), r0


        b.mfspr r1, r0, SPR_CONTEXT_SAVE2
        b.mtspr r0, r1, SPR_EPCR_BASE
        b.mfspr r1, r0, SPR_CONTEXT_SAVE3
        b.mtspr r0, r1, SPR_ESR_BASE

        b.mfspr r1, r0, SPR_CONTEXT_SAVE1


	l.rfe

1:


	l.lwz	r1, 	0(r4)
        b.mtspr r0, r1, SPR_CONTEXT_SAVE1

        // restore MAC registers
        l.lwz   r8, SPR_MACHI_SAV(r1)
        l.ori   r7, r0, SPR_MACHI
        l.mtspr r7, r8, 0
        l.lwz   r8, SPR_MACLO_SAV(r1)
        l.ori   r7, r0, SPR_MACLO
        l.mtspr r7, r8, 0

	l.lwz	r31, GPR31(r1)
	l.lwz	r30, GPR30(r1)
	l.lwz	r29, GPR29(r1)
	l.lwz	r28, GPR28(r1)
	l.lwz	r27, GPR27(r1)
	l.lwz	r26, GPR26(r1)
	l.lwz	r25, GPR25(r1)
	l.lwz	r24, GPR24(r1)
	l.lwz	r23, GPR23(r1)
	l.lwz	r22, GPR22(r1)
	l.lwz	r21, GPR21(r1)
	l.lwz	r20, GPR20(r1)
	l.lwz	r19, GPR19(r1)
	l.lwz	r18, GPR18(r1)
	l.lwz	r17, GPR17(r1)
	l.lwz	r16, GPR16(r1)
	l.lwz	r15, GPR15(r1)
	l.lwz	r14, GPR14(r1)
	l.lwz	r13, GPR13(r1)
	l.lwz	r12, GPR12(r1)
	l.lwz	r11, GPR11(r1)
	l.lwz	r10, GPR10(r1)
	l.lwz	r9, GPR9(r1)
	l.lwz	r8, GPR8(r1)
	l.lwz	r7, GPR7(r1)
	l.lwz	r6, GPR6(r1)
	l.lwz	r5, GPR5(r1)

	l.lwz	r2, GPR2(r1)
	l.lwz	r3, R2_SR(r1)
//	l.mtspr	r0, r3, SPR_ESR_BASE
	l.mtspr	r0, r3, SPR_CONTEXT_SAVE3

	l.lwz	r3, R2_PC(r1)
//	l.mtspr	r0, r3, SPR_EPCR_BASE
	l.mtspr	r0, r3, SPR_CONTEXT_SAVE2


        b.mfspr r1, r0, SPR_CONTEXT_SAVE2
        b.mtspr r0, r1, SPR_EPCR_BASE
        b.mfspr r1, r0, SPR_CONTEXT_SAVE3
        b.mtspr r0, r1, SPR_ESR_BASE

        b.mfspr r1, r0, SPR_CONTEXT_SAVE1

	l.addi	r1, r1, TASK_CONTEXT_SIZE

	l.rfe

	// how about EAR?

	// we should never reach here. put assert here.
	l.j	.
#endif


.global RTK1_ACTIVATE_MARKED_TASK

RTK1_ACTIVATE_MARKED_TASK:

	// needed for G1 ??
	l.j	.
	l.jr	r9



.global RTK1_ACTIVATE_FIRST_TASK

	//
	// activate the first task in the system
	// r3: the address containing task stack and function entry
	//
	//
RTK1_ACTIVATE_FIRST_TASK:

	l.lwz 	r1,	0(r3)
        b.mtspr r0, r1, SPR_CONTEXT_SAVE1

	// inherit the SR -> ESR
	l.mfspr r4,	r0,	SPR_SR
	l.mtspr	r0,	r4,	SPR_ESR_BASE

	l.lwz	r4, 	4(r3)
        b.mtspr r0, r4, SPR_CONTEXT_SAVE2
	l.sw	4(r3),  r0

	l.mfspr	r4,	r0, 	SPR_CONTEXT_SAVE2
	l.mtspr	r0,	r4, 	SPR_EPCR_BASE

	l.rfe

	// we should never reach here. put assert here.
	l.j	.



.global RtkTaskMarkerCall

RtkTaskMarkerCall:

    // TODO: FIXME
    l.rfe

.global RtkGetSpAndPc

RtkGetSpAndPc:
// G1 backtrace
    LOAD_SYMBOL_2_GPR(r3,RtkRegisters)
    l.sw 0(r3), r1   // r13
    l.sw 4(r3), r9   // r14
    l.sw 8(r3), r9   // pc
    l.sw 12(r3), r9  // cpsr
    l.jr r9

    // TODO: FIXME
    l.rfe

.global RetrieveRegisters

#define ESR   (R2_SR+4)
#define EPCR  (ESR+4)
#define EEAR  (ESR+8)
#define EPOS  (ESR+12)
#define EACC  (ESR+16)
#define ETYPE (ESR+20)

RetrieveRegisters:

	// Store r4
	b.addi r1, r1, -4
	b.sw 0(r1), r4

	b.sw GPR2(r3), r2
	b.sw GPR3(r3), r3
	b.sw GPR4(r3), r4
	b.sw GPR5(r3), r5
	b.sw GPR6(r3), r6
	b.sw GPR7(r3), r7
	b.sw GPR8(r3), r8
	b.sw GPR9(r3), r9
	b.sw GPR10(r3), r10
	b.sw GPR11(r3), r11
	b.sw GPR12(r3), r12
	b.sw GPR13(r3), r13
	b.sw GPR14(r3), r14
	b.sw GPR15(r3), r15
	b.sw GPR16(r3), r16
	b.sw GPR17(r3), r17
	b.sw GPR18(r3), r18
	b.sw GPR19(r3), r19
	b.sw GPR20(r3), r20
	b.sw GPR21(r3), r21
	b.sw GPR22(r3), r22
	b.sw GPR23(r3), r23
	b.sw GPR24(r3), r24
	b.sw GPR25(r3), r25
	b.sw GPR26(r3), r26
	b.sw GPR27(r3), r27
	b.sw GPR28(r3), r28
	b.sw GPR29(r3), r29
	b.sw GPR30(r3), r30
	b.sw GPR31(r3), r31
	b.mfspr1 r4, SPR_SR
	b.sw R2_SR(r3), r4
	b.mfspr1 r4, SPR_ESR_BASE
	b.sw ESR(r3), r4
	b.mfspr1 r4, SPR_EPCR_BASE
	b.sw EPCR(r3), r4
	b.mfspr1 r4, SPR_EEAR_BASE
	b.sw EEAR(r3), r4
	b.mfspr1 r4, SPR_EPOS
	b.sw EPOS(r3), r4
	b.mfspr1 r4, SPR_EACC
	b.sw EACC(r3), r4
	b.mfspr1 r4, SPR_ETYPE
	b.sw ETYPE(r3), r4
	b.mfspr1 r4, SPR_NPC
	b.sw R2_PC(r3), r4
	b.lwz r4, GPR4(r3)
	b.sw R2_SP(r3), r1

	// Restore r4
	b.lwz r4, 0(r1)
	b.addi r1, r1, 4
	b.jr r9

.global _RtkAssertRoutine

#define memcpy_size_excepiton   (44*4)
#define BACKTRACE_STACK_SIZE 2048

_RtkAssertRoutine:

	// Store r5
	b.addi r1, r1, -4
	b.sw 0(r1), r5
	LOAD_SYMBOL_2_GPR(r5, sys_exceptionKeep)
	b.sw GPR2(r5), r2
	b.sw GPR3(r5), r3
	b.sw GPR4(r5), r4
	b.sw GPR5(r5), r5
	b.sw GPR6(r5), r6
	b.sw GPR7(r5), r7
	b.sw GPR8(r5), r8
	b.sw GPR9(r5), r9
	b.sw GPR10(r5), r10
	b.sw GPR11(r5), r11
	b.sw GPR12(r5), r12
	b.sw GPR13(r5), r13
	b.sw GPR14(r5), r14
	b.sw GPR15(r5), r15
	b.sw GPR16(r5), r16
	b.sw GPR17(r5), r17
	b.sw GPR18(r5), r18
	b.sw GPR19(r5), r19
	b.sw GPR20(r5), r20
	b.sw GPR21(r5), r21
	b.sw GPR22(r5), r22
	b.sw GPR23(r5), r23
	b.sw GPR24(r5), r24
	b.sw GPR25(r5), r25
	b.sw GPR26(r5), r26
	b.sw GPR27(r5), r27
	b.sw GPR28(r5), r28
	b.sw GPR29(r5), r29
	b.sw GPR30(r5), r30
	b.sw GPR31(r5), r31
	b.mfspr1 r4, SPR_SR
	b.sw R2_SR(r5), r4
	b.mfspr1 r4, SPR_ESR_BASE
	b.sw ESR(r5), r4
	b.mfspr1 r4, SPR_EPCR_BASE
	b.sw EPCR(r5), r4
	b.mfspr1 r4, SPR_EEAR_BASE
	b.sw EEAR(r5), r4
	b.mfspr1 r4, SPR_EPOS
	b.sw EPOS(r5), r4
	b.mfspr1 r4, SPR_EACC
	b.sw EACC(r5), r4
	b.mfspr1 r4, SPR_ETYPE
	b.sw ETYPE(r5), r4
	b.sw R2_PC(r5), r9
	b.addi r1, r1, 4
	b.sw R2_SP(r5), r1
	b.addi r1, r1, -4
	b.lwz r4, 0(r1)
	b.sw GPR5(r5), r4
	b.lwz r4, GPR4(r5)

	// Restore r5
	b.lwz r5, 0(r1)
	b.addi r1, r1, 4

	b.jal RTK2_DISABLE_K
	LOAD_SYMBOL_2_GPR(r9, sys_exceptionKeep)
	b.lwz r9, GPR9(r9)
	LOAD_SYMBOL_2_GPR(r3, RtkRegisters)
	b.sw 0(r3), r1
	b.sw 4(r3), r9
	b.sw 8(r3), r9
	b.sw 12(r3), r9

	b.addi r3, r0, 240
	b.jal backtrace_preprocess
	b.sfeqi  r3, 0
        b.bnf    nocpy_a
        LOAD_SYMBOL_2_GPR(r1, BacktraceStack)
        b.addi r1, r1, (BACKTRACE_STACK_SIZE-3)*4
        LOAD_SYMBOL_2_GPR(r3, sys_exceptionKeep_backup)
	LOAD_SYMBOL_2_GPR(r4, sys_exceptionKeep)
	b.addi r5, r0, memcpy_size_excepiton
	b.jal memcpy

nocpy_a:
	LOAD_SYMBOL_2_GPR(r3, sys_exceptionKeep)
	b.lwz	r31, GPR31(r3)
	b.lwz	r30, GPR30(r3)
	b.lwz	r29, GPR29(r3)
	b.lwz	r28, GPR28(r3)
	b.lwz	r27, GPR27(r3)
	b.lwz	r26, GPR26(r3)
	b.lwz	r25, GPR25(r3)
	b.lwz	r24, GPR24(r3)
	b.lwz	r23, GPR23(r3)
	b.lwz	r22, GPR22(r3)
	b.lwz	r21, GPR21(r3)
	b.lwz	r20, GPR20(r3)
	b.lwz	r19, GPR19(r3)
	b.lwz	r18, GPR18(r3)
	b.lwz	r17, GPR17(r3)
	b.lwz	r16, GPR16(r3)
	b.lwz	r15, GPR15(r3)
	b.lwz	r14, GPR14(r3)
	b.lwz	r13, GPR13(r3)
	b.lwz	r12, GPR12(r3)
	b.lwz	r11, GPR11(r3)
	b.lwz	r10, GPR10(r3)
	b.lwz	r9, GPR9(r3)
	b.lwz	r8, GPR8(r3)
	b.lwz	r7, GPR7(r3)
	b.lwz	r6, GPR6(r3)
	b.lwz	r5, GPR5(r3)
	b.lwz	r4, GPR4(r3)
	b.lwz	r2, GPR2(r3)
	b.lwz	r3, GPR3(r3)
	b.j _RtkAssertRoutine_C

.global RtkExceptionRoutine

RtkExceptionRoutine:

	// Store r5
	b.addi r1, r1, -4
	b.sw 0(r1), r5
	LOAD_SYMBOL_2_GPR(r5, sys_exceptionKeep)
	b.sw GPR2(r5), r2
	b.sw GPR3(r5), r3
	b.sw GPR4(r5), r4
	b.sw GPR5(r5), r5
	b.sw GPR6(r5), r6
	b.sw GPR7(r5), r7
	b.sw GPR8(r5), r8
	b.sw GPR9(r5), r9
	b.sw GPR10(r5), r10
	b.sw GPR11(r5), r11
	b.sw GPR12(r5), r12
	b.sw GPR13(r5), r13
	b.sw GPR14(r5), r14
	b.sw GPR15(r5), r15
	b.sw GPR16(r5), r16
	b.sw GPR17(r5), r17
	b.sw GPR18(r5), r18
	b.sw GPR19(r5), r19
	b.sw GPR20(r5), r20
	b.sw GPR21(r5), r21
	b.sw GPR22(r5), r22
	b.sw GPR23(r5), r23
	b.sw GPR24(r5), r24
	b.sw GPR25(r5), r25
	b.sw GPR26(r5), r26
	b.sw GPR27(r5), r27
	b.sw GPR28(r5), r28
	b.sw GPR29(r5), r29
	b.sw GPR30(r5), r30
	b.sw GPR31(r5), r31
	b.mfspr1 r4, SPR_SR
	b.sw R2_SR(r5), r4
	b.mfspr1 r4, SPR_ESR_BASE
	b.sw ESR(r5), r4
	b.mfspr1 r4, SPR_EPCR_BASE
	b.sw EPCR(r5), r4
	b.mfspr1 r4, SPR_EEAR_BASE
	b.sw EEAR(r5), r4
	b.mfspr1 r4, SPR_EPOS
	b.sw EPOS(r5), r4
	b.mfspr1 r4, SPR_EACC
	b.sw EACC(r5), r4
	b.mfspr1 r4, SPR_ETYPE
	b.sw ETYPE(r5), r4
	b.sw R2_PC(r5), r9
	b.addi r1, r1, 4
	b.sw R2_SP(r5), r1
	b.addi r1, r1, -4
	b.lwz r4, 0(r1)
	b.sw GPR5(r5), r4
	b.lwz r4, GPR4(r5)

	// Restore r5
	b.lwz r5, 0(r1)
	b.addi r1, r1, 4

	b.jal RTK2_DISABLE_K
	LOAD_SYMBOL_2_GPR(r9, sys_exceptionKeep)
	b.lwz r9, GPR9(r9)
	LOAD_SYMBOL_2_GPR(r3, RtkRegisters)
	b.sw 0(r3), r1
	b.sw 4(r3), r9
	b.sw 8(r3), r9
	b.sw 12(r3), r9

	LOAD_SYMBOL_2_GPR(r9, sys_exceptionKeep)
	b.lwz r3, GPR3(r9)
	b.jal backtrace_preprocess
	b.sfeqi  r3, 0
        b.bnf    nocpy_e
        LOAD_SYMBOL_2_GPR(r1, BacktraceStack)
        b.addi r1, r1, (BACKTRACE_STACK_SIZE-3)*4
        LOAD_SYMBOL_2_GPR(r3, sys_exceptionKeep_backup)
	LOAD_SYMBOL_2_GPR(r4, sys_exceptionKeep)
	b.addi r5, r0, memcpy_size_excepiton
	b.jal memcpy

nocpy_e:
	LOAD_SYMBOL_2_GPR(r3, sys_exceptionKeep)
	b.lwz	r31, GPR31(r3)
	b.lwz	r30, GPR30(r3)
	b.lwz	r29, GPR29(r3)
	b.lwz	r28, GPR28(r3)
	b.lwz	r27, GPR27(r3)
	b.lwz	r26, GPR26(r3)
	b.lwz	r25, GPR25(r3)
	b.lwz	r24, GPR24(r3)
	b.lwz	r23, GPR23(r3)
	b.lwz	r22, GPR22(r3)
	b.lwz	r21, GPR21(r3)
	b.lwz	r20, GPR20(r3)
	b.lwz	r19, GPR19(r3)
	b.lwz	r18, GPR18(r3)
	b.lwz	r17, GPR17(r3)
	b.lwz	r16, GPR16(r3)
	b.lwz	r15, GPR15(r3)
	b.lwz	r14, GPR14(r3)
	b.lwz	r13, GPR13(r3)
	b.lwz	r12, GPR12(r3)
	b.lwz	r11, GPR11(r3)
	b.lwz	r10, GPR10(r3)
	b.lwz	r9, GPR9(r3)
	b.lwz	r8, GPR8(r3)
	b.lwz	r7, GPR7(r3)
	b.lwz	r6, GPR6(r3)
	b.lwz	r5, GPR5(r3)
	b.lwz	r4, GPR4(r3)
	b.lwz	r2, GPR2(r3)
	b.lwz	r3, GPR3(r3)
	b.j RtkExceptionRoutine_C
