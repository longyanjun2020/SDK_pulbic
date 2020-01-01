#ifndef __R2_ASM_DEFS_H__
#define __R2_ASM_DEFS_H__

#ifndef ENTRY
#define ENTRY(symbol)			\
	.global symbol			;\
	symbol:	
#endif

        
	
#define CLEAR_GPR(gpr)			\
	l.or	gpr,r0,r0

#define LOAD_SYMBOL_2_GPR(gpr,symbol)	\
	l.movhi	gpr,hi(symbol)		;\
	l.ori	gpr,gpr,lo(symbol)

#define LOAD_SYMBOL_2_GPR_(gpr,symbol)	\
	l.movhi	gpr,hi(_##symbol)		;\
	l.ori	gpr,gpr,lo(_##symbol)

/*
 * DSCR: lower bits of SPR_SR defined by mask will be set to 1
 *
 * PRMS: t1 is temporary (and destroyed)
 */
#define SR_ENABLE_LO_BITS(mask,t1)	\
	l.mfspr	t1,r0,SPR_SR		;\
	l.ori	t1,t1,lo(mask)		;\
	l.mtspr	r0,t1,SPR_SR

/*
 * DSCR: bits set in mask will be set to 1
 *
 * PRMS: t1 is temporary register
 *       t2 is temporary register
 */
#define SR_ENABLE_BITS(mask,t1,t2)	\
	l.mfspr	t2,r0,SPR_SR		;\
	LOAD_SYMBOL_2_GPR(t1,mask)	;\
	l.or	t2,t2,t1		;\
	l.mtspr	r0,t2,SPR_SR

/*
 * DSCR: bits set in mask will be set to 0
 *
 * PRMS: t1 is temporary register
 *       t2 is temporary register
 */ 
#define SR_DISABLE_BITS(mask,t1,t2)	\
	l.mfspr	t2,r0,SPR_SR		;\
	LOAD_SYMBOL_2_GPR(t1,(~mask))	;\
	l.and	t2,t2,t1		;\
	l.mtspr	r0,t2,SPR_SR

/*
 * DSCR: lower bits of SPR defined by mask will be set to 1
 *
 * PRMS: t1 is temporary (and destroyed)
 */
#define SPR_ENABLE_LO_BITS(SPR,mask,t1)	\
	l.mfspr t1,r0,SPR		;\
	l.ori  t1,t1,lo(mask)		;\
	l.mtspr r0,t1,SPR
	
/*
 * DSCR: lower bits of SPR defined by mask will be set to 0
 *
 * PRMS: t1 is temporary (and destroyed)
 */
#define SPR_DISABLE_LO_BITS(SPR,mask,t1)	\
	l.mfspr t1,r0,SPR			;\
	l.andi  t1,t1,lo(~mask)			;\
	l.mtspr r0,t1,SPR
	
#define DISABLE_INTERRUPTS(t1,t2)	\
	SR_DISABLE_BITS((SPR_SR_IEE|SPR_SR_TEE),t1,t2)

#define ENABLE_INTERRUPTS(t1)		\
	SR_ENABLE_LO_BITS((SPR_SR_IEE|SPR_SR_TEE),t1)

#define R2_GPRSIZE  4

#define R2_REGSIZE  4

#define SPIDX   1
#define LRIDX   9

#if (__GNUC__ >= 4 )
// GCC 4.x.x
#define FPIDX   10
#else
// GCC 3.x
#define FPIDX   2
#endif // (__GNUC__ >= 4 )

// Utility macro: Load a 32-bit constant into a register
    .macro  load32i reg const
        l.movhi \reg,hi(\const)
        l.ori   \reg,\reg,lo(\const)
    .endm

    .macro save_sp_reg basereg
        l.sw    SPIDX * R2_GPRSIZE(\basereg), r1	       // SP (v3/v4: r1)
    .endm

    .macro save_lr_reg basereg
        l.sw    LRIDX * R2_GPRSIZE(\basereg), r9        // LR (v3/v4: r9)
    .endm

    .macro save_fp_reg basereg
        l.sw    FPIDX * R2_GPRSIZE(\basereg), r10	       // FP (v3:r2 v4:r10)
    .endm

    .macro load_sp_reg basereg
        l.lwz   r1, SPIDX * R2_GPRSIZE(\basereg)
    .endm

    .macro load_lr_reg basereg
        l.lwz   r9, LRIDX * R2_GPRSIZE(\basereg)
    .endm

    .macro load_fp_reg basereg
        l.lwz   r10, FPIDX * R2_GPRSIZE(\basereg)
    .endm

#if (__GNUC__ >= 4 )
// GCC 4.x.x

    .macro save_argument_regs basereg
        l.sw     3 * R2_GPRSIZE(\basereg), r3
        l.sw     4 * R2_GPRSIZE(\basereg), r4
        l.sw     5 * R2_GPRSIZE(\basereg), r5
        l.sw     6 * R2_GPRSIZE(\basereg), r6
        l.sw     7 * R2_GPRSIZE(\basereg), r7
        l.sw     8 * R2_GPRSIZE(\basereg), r8
    .endm

    .macro load_argument_regs basereg
        l.lwz   r3,  3 * R2_GPRSIZE(\basereg)
        l.lwz   r4,  4 * R2_GPRSIZE(\basereg)
        l.lwz   r5,  5 * R2_GPRSIZE(\basereg)
        l.lwz   r6,  6 * R2_GPRSIZE(\basereg)
        l.lwz   r7,  7 * R2_GPRSIZE(\basereg)
        l.lwz   r8,  8 * R2_GPRSIZE(\basereg)
    .endm

    .macro save_callee_saved_regs basereg
	l.sw    11 * R2_GPRSIZE(\basereg), r11
	l.sw    12 * R2_GPRSIZE(\basereg), r12
	l.sw    13 * R2_GPRSIZE(\basereg), r13
	l.sw    14 * R2_GPRSIZE(\basereg), r14
	l.sw    15 * R2_GPRSIZE(\basereg), r15
	l.sw    16 * R2_GPRSIZE(\basereg), r16
	l.sw    17 * R2_GPRSIZE(\basereg), r17
	l.sw    18 * R2_GPRSIZE(\basereg), r18
	l.sw    19 * R2_GPRSIZE(\basereg), r19
	l.sw    20 * R2_GPRSIZE(\basereg), r20
	l.sw    21 * R2_GPRSIZE(\basereg), r21
	l.sw    22 * R2_GPRSIZE(\basereg), r22
    .endm

    .macro load_callee_saved_regs basereg
	l.lwz   r11, 11 * R2_GPRSIZE(\basereg)
	l.lwz   r12, 12 * R2_GPRSIZE(\basereg)
	l.lwz   r13, 13 * R2_GPRSIZE(\basereg)
	l.lwz   r14, 14 * R2_GPRSIZE(\basereg)
	l.lwz   r15, 15 * R2_GPRSIZE(\basereg)
	l.lwz   r16, 16 * R2_GPRSIZE(\basereg)
	l.lwz   r17, 17 * R2_GPRSIZE(\basereg)
	l.lwz   r18, 18 * R2_GPRSIZE(\basereg)
	l.lwz   r19, 19 * R2_GPRSIZE(\basereg)
	l.lwz   r20, 20 * R2_GPRSIZE(\basereg)
	l.lwz   r21, 21 * R2_GPRSIZE(\basereg)
	l.lwz   r22, 22 * R2_GPRSIZE(\basereg)
    .endm

    .macro save_temporary_regs basereg
	l.sw	 2 * R2_GPRSIZE(\basereg), r2	// actually, not temporary register, but GP
	l.sw	23 * R2_GPRSIZE(\basereg), r23
	l.sw	24 * R2_GPRSIZE(\basereg), r24
	l.sw	25 * R2_GPRSIZE(\basereg), r25
	l.sw	26 * R2_GPRSIZE(\basereg), r26
	l.sw	27 * R2_GPRSIZE(\basereg), r27
	l.sw	28 * R2_GPRSIZE(\basereg), r28
	l.sw	29 * R2_GPRSIZE(\basereg), r29
	l.sw	30 * R2_GPRSIZE(\basereg), r30
	l.sw	31 * R2_GPRSIZE(\basereg), r31
    .endm

    .macro load_temporary_regs basereg
	l.lwz	r2,   2 * R2_GPRSIZE(\basereg) // actually, not temporary register, but GP
	l.lwz	r23, 23 * R2_GPRSIZE(\basereg)
	l.lwz	r24, 24 * R2_GPRSIZE(\basereg)
	l.lwz	r25, 25 * R2_GPRSIZE(\basereg)
	l.lwz	r26, 26 * R2_GPRSIZE(\basereg)
	l.lwz	r27, 27 * R2_GPRSIZE(\basereg)
	l.lwz	r28, 28 * R2_GPRSIZE(\basereg)
	l.lwz	r29, 29 * R2_GPRSIZE(\basereg)
	l.lwz	r30, 30 * R2_GPRSIZE(\basereg)
	l.lwz	r31, 31 * R2_GPRSIZE(\basereg)
    .endm

#else
// GCC 3.x

    .macro save_argument_regs basereg
        l.sw     3 * R2_GPRSIZE(\basereg), r3
        l.sw     4 * R2_GPRSIZE(\basereg), r4
        l.sw     5 * R2_GPRSIZE(\basereg), r5
        l.sw     6 * R2_GPRSIZE(\basereg), r6
        l.sw     7 * R2_GPRSIZE(\basereg), r7
        l.sw     8 * R2_GPRSIZE(\basereg), r8
    .endm

    .macro load_argument_regs basereg
        l.lwz    r3,  3 * R2_GPRSIZE(\basereg)
        l.lwz    r4,  4 * R2_GPRSIZE(\basereg)
        l.lwz    r5,  5 * R2_GPRSIZE(\basereg)
        l.lwz    r6,  6 * R2_GPRSIZE(\basereg)
        l.lwz    r7,  7 * R2_GPRSIZE(\basereg)
        l.lwz    r8,  8 * R2_GPRSIZE(\basereg)
    .endm

    .macro save_callee_saved_regs basereg
	// even numberred registers exclude r12
        l.sw    10 * R2_GPRSIZE(\basereg), r10
        l.sw    14 * R2_GPRSIZE(\basereg), r14
        l.sw    16 * R2_GPRSIZE(\basereg), r16
        l.sw    18 * R2_GPRSIZE(\basereg), r18
        l.sw    20 * R2_GPRSIZE(\basereg), r20
        l.sw    22 * R2_GPRSIZE(\basereg), r22
        l.sw    24 * R2_GPRSIZE(\basereg), r24
        l.sw    26 * R2_GPRSIZE(\basereg), r26
        l.sw    28 * R2_GPRSIZE(\basereg), r28
        l.sw    30 * R2_GPRSIZE(\basereg), r30
    .endm

    .macro load_callee_saved_regs basereg
	// even numberred registers exclude r12
        l.lwz    r10, 10 * R2_GPRSIZE(\basereg)
        l.lwz    r14, 14 * R2_GPRSIZE(\basereg)
        l.lwz    r16, 16 * R2_GPRSIZE(\basereg)
        l.lwz    r18, 18 * R2_GPRSIZE(\basereg)
        l.lwz    r20, 20 * R2_GPRSIZE(\basereg)
        l.lwz    r22, 22 * R2_GPRSIZE(\basereg)
        l.lwz    r24, 24 * R2_GPRSIZE(\basereg)
        l.lwz    r26, 26 * R2_GPRSIZE(\basereg)
        l.lwz    r28, 28 * R2_GPRSIZE(\basereg)
        l.lwz    r30, 30 * R2_GPRSIZE(\basereg)
    .endm

    .macro save_temporary_regs basereg
        // odd-numberred registers including r12 (RVH)
        l.sw    11 * R2_GPRSIZE(\basereg), r11
        l.sw    12 * R2_GPRSIZE(\basereg), r12
        l.sw    13 * R2_GPRSIZE(\basereg), r13
        l.sw    15 * R2_GPRSIZE(\basereg), r15
        l.sw    17 * R2_GPRSIZE(\basereg), r17
        l.sw    19 * R2_GPRSIZE(\basereg), r19
        l.sw    21 * R2_GPRSIZE(\basereg), r21
        l.sw    23 * R2_GPRSIZE(\basereg), r23
        l.sw    25 * R2_GPRSIZE(\basereg), r25
        l.sw    27 * R2_GPRSIZE(\basereg), r27
        l.sw    29 * R2_GPRSIZE(\basereg), r29
        l.sw    31 * R2_GPRSIZE(\basereg), r31
    .endm

    .macro load_temporary_regs basereg
        // odd-numberred registers including r12 (RVH)
        l.lwz   r11, 11 * R2_GPRSIZE(\basereg)
        l.lwz   r12, 12 * R2_GPRSIZE(\basereg)
        l.lwz   r13, 13 * R2_GPRSIZE(\basereg)
        l.lwz   r15, 15 * R2_GPRSIZE(\basereg)
        l.lwz   r17, 17 * R2_GPRSIZE(\basereg)
        l.lwz   r19, 19 * R2_GPRSIZE(\basereg)
        l.lwz   r21, 21 * R2_GPRSIZE(\basereg)
        l.lwz   r23, 23 * R2_GPRSIZE(\basereg)
        l.lwz   r25, 25 * R2_GPRSIZE(\basereg)
        l.lwz   r27, 27 * R2_GPRSIZE(\basereg)
        l.lwz   r29, 29 * R2_GPRSIZE(\basereg)
        l.lwz   r31, 31 * R2_GPRSIZE(\basereg)
    .endm

#endif // (__GNUC__ >= 4 )

#endif // __R2_ASM_DEFS_H__


