		.text
/*
        AREA    subrout, CODE, READONLY

        CODE32
;****************************************************************************
;
;      File             : AACLib.s
;      Purpose          : Common routines for AAC-LC encoder
;
;****************************************************************************
        EXPORT  Window_Filter1
        EXPORT  Window_Filter2 
        EXPORT  Short_Window_Filter 
;        EXPORT  Calc_Sum32      
        EXPORT  Threshold_Calc

;==============================================================================
; void Window_Filter1(Word16 *ptr1, 
;                     Word16 *ptr2,
;                     Word32 *ptr3, 
;                     const Word32 *win_ptr,
;                     Word16 minSf,
;                     Word32 len)
;==============================================================================
minSf_idx         equ   7*4
len_idx           equ   8*4
*/
			.equ	minSf_idx,	(7*4)
			.equ	len_idx,	(8*4)
			.globl	Window_Filter1
Window_Filter1:
		stmfd	r13!, {r4-r10}

        ldr     r4,[r13,#minSf_idx]             // r4 = minSf_idx
        ldr     r5,[r13,#len_idx]               // r5 = loop coounter

Window_Filter1_loop:
        ldrsh   r7,[r0],#2                      // r7 = *ptr1
        ldrsh   r9,[r1],#-2                     // r9 = *ptr2
        ldr     r6,[r3],#4                      // r6 = LongWindowKBD[i]
        mov     r7,r7,lsl r4                    // r7 = timeSignalSample
        mov     r9,r9,lsl r4                    // r9 = a1
        smulbb  r8,r7,r6                        // r8 = ws1
        smulbt  r10,r9,r6                       // r10 = ws2
        ldrsh   r7,[r0],#2                      // r7 = *ptr1
        qsub    r8,r8,r10
        ldrsh   r9,[r1],#-2                     // r9 = *ptr2
        str     r8,[r2],#4

        ldr     r6,[r3],#4                      // r6 = LongWindowKBD[i]
        mov     r7,r7,lsl r4                    // r7 = timeSignalSample
        mov     r9,r9,lsl r4                    // r9 = a1
        smulbb  r8,r7,r6                        // r8 = ws1
        smulbt  r10,r9,r6                       // r10 = ws2
        qsub    r8,r8,r10
        subs    r5,r5,#2        
        str     r8,[r2],#4

        bgt     Window_Filter1_loop

		ldmfd	r13!, {r4-r10}
		bx		lr		

/*
;==============================================================================
; void Window_Filter2(Word16 *ptr1, 
;                     Word16 *ptr2,
;                     Word32 *ptr3, 
;                     const Word32 *win_ptr,
;                     Word16 minSf
;                     Word32 len)
;==============================================================================
*/
		.globl	Window_Filter2
Window_Filter2:
		stmfd	r13!, {r4-r10}

        ldr     r4,[r13,#minSf_idx]             // r4 = minSf_idx
        ldr     r5,[r13,#len_idx]               // r5 = loop coounter

Window_Filter2_loop:
        ldrsh   r7,[r0],#2                      // r7 = *ptr1
        ldrsh   r9,[r1],#-2                     // r9 = *ptr2
        ldr     r6,[r3],#4                      // r6 = LongWindowKBD[i]
        mov     r7,r7,lsl r4                    // r7 = timeSignalSample
        mov     r9,r9,lsl r4                    // r9 = a1
        smulbt  r8,r7,r6                        // r8 = ws1
        smulbb  r10,r9,r6                       // r10 = ws2
        ldrsh   r7,[r0],#2                      // r7 = *ptr1
        qadd    r8,r8,r10        
        ldrsh   r9,[r1],#-2                     // r9 = *ptr2
        rsb     r8,r8,#0
        str     r8,[r2],#-4       

        ldr     r6,[r3],#4                      // r6 = LongWindowKBD[i]
        mov     r7,r7,lsl r4                    // r7 = timeSignalSample
        mov     r9,r9,lsl r4                    // r9 = a1
        smulbt  r8,r7,r6                        // r8 = ws1
        smulbb  r10,r9,r6                       // r10 = ws2
        subs    r5,r5,#2                 
        qadd    r8,r8,r10        
        rsb     r8,r8,#0
        str     r8,[r2],#-4        
                   
        bgt     Window_Filter2_loop

		ldmfd	r13!, {r4-r10}
		bx		lr		

/*
;==============================================================================
; void Short_Window_Filter(Word16 *ptr1, 
;                          Word16 *ptr2,
;                          Word32 *ptr3, 
;                          const Word32 *win_ptr,
;                          Word16 minSf,
;                          Word32 len)
;==============================================================================
minSf1_idx         equ   9*4
len1_idx           equ   10*4
*/
		.equ	minSf1_idx, (9*4)
		.equ	len1_idx, (10*4)
		.globl	Short_Window_Filter
Short_Window_Filter:
		stmfd	r13!, {r4-r12}

        ldr     r4,[r13,#minSf1_idx]            // r4 = minSf_idx
        ldr     r5,[r13,#len1_idx]              // r5 = loop coounter
        sub     r11,r2,#4
        add     r12,r1,#128*2
Short_Window_Filter_loop:
        ldrsh   r7,[r0],#2                      // r7 = *ptr1
        ldrsh   r9,[r1],#-2                     // r9 = *ptr2
        ldr     r6,[r3],#4                      // r6 = ShortWindowSine[i]
        mov     r7,r7,lsl r4                    // r7 = timeSignalSample
        mov     r9,r9,lsl r4                    // r9 = a1
        smulbb  r8,r7,r6                        // r8 = ws1
        smulbt  r10,r9,r6                       // r10 = ws2
        ldrsh   r7,[r0,#127*2]                  // r7 = *ptr1
        qsub    r8,r8,r10
        ldrsh   r9,[r12],#-2                    // r9 = *ptr2
        str     r8,[r2],#4
                    
        mov     r7,r7,lsl r4                    // r7 = timeSignalSample
        mov     r9,r9,lsl r4                    // r9 = a1
        smulbt  r8,r7,r6                        // r8 = ws1
        smulbb  r10,r9,r6                       // r10 = ws2
        subs    r5,r5,#1        
        qadd    r8,r8,r10        
        rsb     r8,r8,#0
        str     r8,[r11],#-4               
        bgt     Short_Window_Filter_loop

		ldmfd	r13!, {r4-r12}
		bx		lr		

/*
;==============================================================================
; Word32 Calc_Sum32(Word32 *ptr32, 
;                   Word32 Len,
;                   Word32 Acc); 
;==============================================================================
;Calc_Sum32
;        stmfd	r13!, {r4-r7}
;
;        and     r3,r1,#0x03
;        mov     r1,r1,asr #2
;        
;Calc_Sum32_loop1
;        ldr     r4,[r0],#4
;        subs    r3,r3,#1
;        qadd    r2,r2,r4         
;        bgt     Calc_Sum32_loop1
;        
;        cmp     r1,#0
;        moveq   r0,r2
;		ldmeqfd	r13!, {r4-r10}
;		bxeq		lr		        
;        
;Calc_Sum32_loop2
;        ldr     r4,[r0],#4
;        ldr     r5,[r0],#4
;        qadd    r2,r2,r4
;        ldr     r6,[r0],#4
;        qadd    r2,r2,r5
;        ldr     r7,[r0],#4
;        qadd    r2,r2,r6
;        subs    r1,r1,#1
;        qadd    r2,r2,r7
;        bgt     Calc_Sum32_loop2                  
;
;        mov     r0,r2
;
;		ldmfd	r13!, {r4-r7}
;		bx		lr		
		

;==============================================================================
; Word32 Threshold_Calc(Word32 *ptrI,
;                       Word32 *ptrO, 
;                       Word16 ratio,
;                       Word32 clipEnergy,
;                       Word32 Len);
;==============================================================================		
Len_idx         equ   4*4
*/
		.equ	Len_idx, (4*4)
		.globl	Threshold_Calc
Threshold_Calc:
        stmfd	r13!, {r4-r7}

        ldr     r4,[r13,#Len_idx]               // r4 = Length

Threshold_Calc_loop:
        ldr     r5,[r0],#4
        ldr     r6,[r0],#4
        
        smulwb  r5,r5,r2
        smulwb  r6,r6,r2
        qadd    r5,r5,r5                        // r5 = fixmul_32x16b(psyData->sfbEnergy.sfbLong[i], hPsyConfLong->ratio);
        qadd    r6,r6,r6
        cmp     r5,r3
        movle   r7,r5                           // r7 = L_min(tmp32, clipEnergy)
        movgt   r7,r3     
        str     r7,[r1],#4

        cmp     r6,r3
        movle   r7,r6                           // r7 = L_min(tmp32, clipEnergy)
        movgt   r7,r3     
        
        subs    r4,r4,#2
        str     r7,[r1],#4        
                
        bgt     Threshold_Calc_loop

		ldmfd	r13!, {r4-r7}
		bx		lr		
		
        .end
