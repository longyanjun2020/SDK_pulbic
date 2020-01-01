	.text
	
	.globl	PolyphaseStereo
	.globl	PolyphaseMono

	.equ RNDVAL,		(1 << ((32 - 12) + (6 - 1)))

	
	.macro	C64TOS	xl, xh, sign, maxPos

	mov		\xl, \xl, lsr #(20+6)
	orr		\xl, \xl, \xh, lsl #(12-6)
	mov		\sign, \xl, ASR #31
	cmp		\sign, \xl, ASR #15
	eorne	\xl, \sign, \maxPos
	
	.endm	

	
	.macro	MC0S	x  

	ldr		r12, [r2], #4
	ldr		r14, [r2], #4
	ldr		r0, [r1, #(4*(\x))]
	ldr		r3, [r1, #(4*(23 - \x))]

	smlal	r4, r5, r0, r12
	ldr		r0, [r1, #(4*(32 + \x))]
	rsb		r14, r14, #0
	smlal	r4, r5, r3, r14
	ldr		r3, [r1, #(4*(32 + 23 - \x))]
	
	smlal	r8, r9, r0, r12
	smlal	r8, r9, r3, r14

	.endm	

	
	.macro	MC1S	x 

	ldr		r12, [r2], #4
	ldr		r0, [r1, #(4*(\x))]
	ldr		r3, [r1, #(4*(32 + \x))]
	smlal	r4, r5, r0, r12
	smlal	r8, r9, r3, r12
	
	.endm	


	.macro	MC2S	x

	// load data as far as possible in advance of using it
	ldr		r12, [r2], #4
	ldr		r14, [r2], #4
	ldr		r0, [r1, #(4*(\x))]
	ldr		r3, [r1, #(4*(23 - \x))]

	smlal	r4, r5, r0, r12
	smlal	r6, r7, r0, r14
	rsb		r14, r14, #0
	smlal	r6, r7, r3, r12
	smlal	r4, r5, r3, r14

	ldr		r3, [r1, #(4*(32 + 23 - \x))]
	ldr		r0, [r1, #(4*(32 + \x))]

	smlal	r8, r9, r3, r14
	smlal	r10, r11, r3, r12
	rsb		r14, r14, #0
	smlal	r8, r9, r0, r12
	smlal	r10, r11, r0, r14

	.endm	


// void PolyphaseStereo(short *pcm, int *vbuf, const int *coefBase)


PolyphaseStereo:
	
	stmfd	sp!, {r4-r11, r14}
	
	/// clear out stack space for 2 local variables (4 bytes each)
	sub		sp, sp, #8
	str		r0, [sp, #4]			/// sp[1] = pcm pointer

	/// special case, output sample 0
	mov		r4, #RNDVAL				/// load rndVal (low 32)
	mov		r8, #RNDVAL				/// load rndVal (low 32)
	mov		r5, #0
	mov		r9, #0

	MC0S	0
	MC0S	1
	MC0S	2
	MC0S	3
	MC0S	4
	MC0S	5
	MC0S	6
	MC0S	7

	ldr		r0, [sp, #4]			// load pcm pointer
	mov		r14, #0x7f00
	orr		r14, r14, #0xff
	
	C64TOS	r4, r5, r12, r14
	C64TOS	r8, r9, r12, r14

	strh	r4, [r0, #(2*0)]
	strh	r8, [r0, #(2*1)]

	/// special case, output sample 16
	add		r2, r2, #(4*(256-16))	/// coef = coefBase + 256 (was coefBase + 16 after MC0S block)
	add		r1, r1, #(4*1024)		/// vb1 = vbuf + 64*16
	
	mov		r4, #RNDVAL				/// load rndVal (low 32)
	mov		r8, #RNDVAL				/// load rndVal (low 32)
	mov		r5, #0
	mov		r9, #0

	MC1S	0
	MC1S	1
	MC1S	2
	MC1S	3
	MC1S	4
	MC1S	5
	MC1S	6
	MC1S	7

	ldr		r0, [sp, #4]			/// load pcm pointer
	mov		r14, #0x7f00
	orr		r14, r14, #0xff
	
	C64TOS	r4, r5, r12, r14
	C64TOS	r8, r9, r12, r14

	strh	r4, [r0, #(2*(2*16+0))]
	strh	r8, [r0, #(2*(2*16+1))]

	// main convolution loop: sum1L = samples 1, 2, 3, ... 15   sum2L = samples 31, 30, ... 17
	sub		r2, r2, #(4*(264-16))	// coef = coefBase + 16 (was coefBase + 264 after MC1S block)
	sub		r1, r1, #(4*(1024-64))	// vb1 = vbuf + 64 (was vbuf + 64*16 after MC1S block)
	mov		r12, #15				// loop counter, count down
	add		r0, r0, #(2*2)			// pcm+=2
	
LoopPS:
	str		r12, [sp, #0]			// sp[0] = i (loop counter)
	str		r0, [sp, #4]			// sp[1] = pcm (pointer to pcm buffer)
	
	mov		r4, #RNDVAL				// load rndVal (low 32)
	mov		r8, #RNDVAL				// load rndVal (low 32)
	mov		r6, #RNDVAL				// load rndVal (low 32)
	mov		r10, #RNDVAL			// load rndVal (low 32)
	
	mov		r5, #0
	mov		r9, #0
	mov		r7, #0
	mov		r11, #0

	MC2S	0
	MC2S	1
	MC2S	2
	MC2S	3
	MC2S	4
	MC2S	5
	MC2S	6
	MC2S	7
	
	add		r1, r1, #(4*64)			// vb1 += 64
	
	ldr		r0, [sp, #4]			// load pcm pointer
	mov		r14, #0x7f00
	orr		r14, r14, #0xff
	
	C64TOS	r4, r5, r12, r14
	C64TOS	r8, r9, r12, r14
	C64TOS	r6, r7, r12, r14
	C64TOS	r10, r11, r12, r14
	
	ldr		r12, [sp, #0]			// load loop counter
	add		r14, r0, r12, lsl #3	// CF2 = PCM + 4*i (short offset)
	strh	r6, [r14], #2			// *(pcm + 2*2*i + 0)
	strh	r10, [r14], #2			// *(pcm + 2*2*i + 1)

	strh	r4, [r0], #2			// *(pcm + 0)
	strh	r8, [r0], #2			// *(pcm + 1)
	
	subs	r12, r12, #1
	bne		LoopPS

	// restore stack pointer
	add		sp, sp, #8

	ldmfd	sp!, {r4-r11, pc}
	

	.macro 	MC0M	x

	ldr		r12, [r2], #4
	ldr		r14, [r2], #4
	ldr		r0, [r1, #(4*(\x))]
	ldr		r3, [r1, #(4*(23 - \x))]

	rsb		r14, r14, #0
	smlal	r4, r5, r0, r12
	smlal	r4, r5, r3, r14

	.endm

	
	.macro 	MC1M	x

	ldr		r12, [r2], #4
	ldr		r0, [r1, #(4*(\x))]
	smlal	r4, r5, r0, r12
	
	.endm

	
	.macro 	MC2M	x

	// load data as far as possible in advance of using it
	ldr		r12, [r2], #4
	ldr		r14, [r2], #4
	ldr		r0, [r1, #(4*(\x))]
	ldr		r3, [r1, #(4*(23 - \x))]

	smlal	r4, r5, r0, r12
	smlal	r6, r7, r0, r14
	rsb		r14, r14, #0
	smlal	r4, r5, r3, r14
	smlal	r6, r7, r3, r12

	.endm


// void PolyphaseMono(short *pcm, int *vbuf, const int *coefBase)


PolyphaseMono:
	stmfd	sp!, {r4-r11, r14}
	
	// clear out stack space for 4 local variables (4 bytes each)
	sub		sp, sp, #8
	str		r0, [sp, #4]			// sp[1] = pcm pointer

	// special case, output sample 0
	mov		r4, #RNDVAL				// load rndVal (low 32)
	mov		r5, #0

	MC0M	0
	MC0M	1
	MC0M	2
	MC0M	3
	MC0M	4
	MC0M	5
	MC0M	6
	MC0M	7

	ldr		r0, [sp, #4]			// load pcm pointer
	mov		r14, #0x7f00
	orr		r14, r14, #0xff
	
	C64TOS	r4, r5, r12, r14
	strh	r4, [r0, #(2*0)]

	// special case, output sample 16
	add		r2, r2, #(4*(256-16))	// coef = coefBase + 256 (was coefBase + 16 after MC0M block)
	add		r1, r1, #(4*1024)		// vb1 = vbuf + 64*16
	
	mov		r4, #RNDVAL				// load rndVal (low 32)
	mov		r5, #0

	MC1M	0
	MC1M	1
	MC1M	2
	MC1M	3
	MC1M	4
	MC1M	5
	MC1M	6
	MC1M	7

	ldr		r0, [sp, #4]			// load pcm pointer
	mov		r14, #0x7f00
	orr		r14, r14, #0xff
	
	C64TOS	r4, r5, r12, r14

	strh	r4, [r0, #(2*16)]

	// main convolution loop: sum1L = samples 1, 2, 3, ... 15   sum2L = samples 31, 30, ... 17
	sub		r2, r2, #(4*(264-16))	// coef = coefBase + 16 (was coefBase + 264 after MC1M block)
	sub		r1, r1, #(4*(1024-64))	// vb1 = vbuf + 64 (was vbuf + 64*16 after MC1M block)
	mov		r12, #15				// loop counter, count down
	add		r0, r0, #(2)			// pcm++
	
LoopPM:
	str		r12, [sp, #0]			// sp[0] = i (loop counter)
	str		r0, [sp, #4]			// sp[1] = pcm (pointer to pcm buffer)
	
	mov		r4, #RNDVAL				// load rndVal (low 32)
	mov		r6, #RNDVAL				// load rndVal (low 32)
	mov		r5, #0
	mov		r7, #0

	MC2M	0
	MC2M	1
	MC2M	2
	MC2M	3
	MC2M	4
	MC2M	5
	MC2M	6
	MC2M	7
	
	add		r1, r1, #(4*64)	// vb1 += 64
	
	ldr		r0, [sp, #4]			// load pcm pointer
	mov		r14, #0x7f00
	orr		r14, r14, #0xff
	
	C64TOS	r4, r5, r12, r14
	C64TOS	r6, r7, r12, r14
	
	ldr		r12, [sp, #0]			// load loop counter
	add		r14, r0, r12, lsl #2	// r14 = PCM + 2*i (short offset)
	strh	r6, [r14], #2	// *(pcm + 2*i + 0)
	strh	r4, [r0], #2	// *(pcm + 0) ; pcm++
	
	subs	r12, r12, #1
	bne		LoopPM

	// restore stack pointer
	add		sp, sp, #8

	ldmfd	sp!, {r4-r11, pc}
	

	.end