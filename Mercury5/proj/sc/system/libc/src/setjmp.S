/* Simple setjmp/longjmp for the Beyond Architecture (AEON ISA).
   Damjan Lampret, OpenCores.org, Aug 15 2000.  */

/* Until AEON Arch is fixed, we just save entire register file.
   Should be fixed eventually. */

	.align	4
	.proc	setjmp
	.global	setjmp
	.extern	setjmp
setjmp:
	b.sw	0(r3),r1
	b.sw	4(r3),r2
	b.sw	8(r3),r3
	b.sw	12(r3),r4
	b.sw	16(r3),r5
	b.sw	20(r3),r6
	b.sw	24(r3),r7
	b.sw	28(r3),r8
	b.sw	32(r3),r9
	b.sw	36(r3),r10
	b.sw	40(r3),r11
	b.sw	44(r3),r12
	b.sw	48(r3),r13
	b.sw	52(r3),r14
	b.sw	56(r3),r15
#ifndef __AEON_SIXTEEN_REGS__
	b.sw	60(r3),r16
	b.sw	64(r3),r17
	b.sw	68(r3),r18
	b.sw	72(r3),r19
	b.sw	76(r3),r20
	b.sw	80(r3),r21
	b.sw	84(r3),r22
	b.sw	88(r3),r23
	b.sw	92(r3),r24
	b.sw	96(r3),r25
	b.sw	100(r3),r26
	b.sw	104(r3),r27
	b.sw	108(r3),r28
	b.sw	112(r3),r29
	b.sw	116(r3),r30
	b.sw	120(r3),r31
#endif

#if defined(__AEON2__) || defined(__AEONR2__)
	b.addi	r3,r0,0
	b.jr	r9
#else
	b.jr	r9
	b.addi	r3,r0,0
#endif /* __AEON2__ || __AEONR2__ */
.endproc setjmp

	.align	4
	.proc	longjmp
	.global	longjmp
longjmp:
	b.lwz	r1,0(r3)
	b.lwz	r2,4(r3)
	b.lwz	r5,16(r3)
	b.lwz	r6,20(r3)
	b.lwz	r7,24(r3)
	b.lwz	r8,28(r3)
	b.lwz	r9,32(r3)
	b.lwz	r10,36(r3)
	b.lwz	r11,40(r3)
	b.lwz	r12,44(r3)
	b.lwz	r13,48(r3)
	b.lwz	r14,52(r3)
	b.lwz	r15,56(r3)
#ifndef __AEON_SIXTEEN_REGS__
	b.lwz	r16,60(r3)
	b.lwz	r17,64(r3)
	b.lwz	r18,68(r3)
	b.lwz	r19,72(r3)
	b.lwz	r20,76(r3)
	b.lwz	r21,80(r3)
	b.lwz	r22,84(r3)
	b.lwz	r23,88(r3)
	b.lwz	r24,92(r3)
	b.lwz	r25,96(r3)
	b.lwz	r26,100(r3)
	b.lwz	r27,104(r3)
	b.lwz	r28,108(r3)
	b.lwz	r29,112(r3)
	b.lwz	r30,116(r3)
	b.lwz	r31,120(r3)
#endif
#if defined(__AEON2__) || defined(__AEONR2__)
    /* longjmp return the 2nd input argument: val */
        b.bne   r4, r0, 1f
        b.ori   r3, r0, 1
        b.jr    r9
1:
        b.addi  r1, r1, -4
        b.sw    0(r1), r4
        b.lwz   r4,12(r3)
        b.lwz   r3, 0(r1)
        b.addi  r1, r1, 4
	
	b.jr	r9
#else
	b.jr	r9
	b.addi	r3,r4,0
#endif /* __AEON2__ || __AEONR2__ */

.endproc longjmp
