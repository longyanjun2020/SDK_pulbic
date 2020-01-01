;****************************************************************************
;*																			*
;*					RTK2UTIL.ASM for THUMB processor mode					*
;*					JLO, 27/04/2001											*
;*																			*
;****************************************************************************

MODE_MASK               *       2_11111
IRQ_DISABLE             *       2_10000000
FIQ_DISABLE             *       2_01000000
INT_DISABLE             *       FIQ_DISABLE | IRQ_DISABLE
Sup32Mode               *       2_10011
MARKER_SP_OFFSET        *       8*4
MARKED_OFFSET           *       9*4
TASKID_OFFSET           *       3
RTK_STACK_OVERFLOW      *       190


        AREA |RtkCode|, CODE, READONLY

;
; Task activation
;
		EXPORT RTK1_ACTIVATE_TASK
RTK1_ACTIVATE_TASK

        MRS     a3, cpsr                        ; save flags and state
        STMDB   sp!, {a3, r4-r12, lr}           ; save registers and flags
        STR     sp, [a1]                        ; save stack pointer

        LDR     sp, [a2]                        ; restore stack pointer
        LDR     a3, [a2, #4]                    ; point to PC
        CMP     a3, #0
        BEQ     __NotFirstStart                 ; first starting ?

        MOV     a3, #Sup32Mode                  ; start mode = it allowed, Sup32
        MSR     CPSR_cxsf, a3
        LDR     a3, [a2, #4]                    ; a3 = new pc
        MOV     a4, #0
        STR     a4, [a2, #4]                    ; set not first starting
	IF __THUMB__ = {TRUE}
; Thumb Mode
        ADR     a1,Rtk2ActivateThumb + 1
        BX      a1

        CODE16									; @@ THUMB16 MODE @@
Rtk2ActivateThumb
        MOV     pc, a3                          ; jump to routine
		CODE32									; @@ ARM32 MODE @@
		ALIGN
	ELSE
		MOV     pc, a3                          ; jump to routine
	ENDIF
__NotFirstStart                                 ; no
        LDMIA   sp!, {a3, r4-r12, lr}           ; restore registers
        MSR     CPSR_cxsf, a3                   ; restore flags
		BX      lr								; return
;
; Task activation w/ jump to marked task
;

		EXPORT RTK1_ACTIVATE_MARKED_TASK
RTK1_ACTIVATE_MARKED_TASK

        MRS     a3, cpsr                        ; save flags and state
        STMDB   sp!, {a3, r4-r12, lr}           ; save registers and flags
        STR     sp, [a1]                        ; save stack pointer

        MOV     sp, a2                          ; restore stack pointer
        MOV     a2, #1                          ; set jump flag

	IF __THUMB__ = {TRUE}
; Thumb Mode
        ADR     a3, Rtk2ActivateMarkedThumb + 1
        BX      a3 

        CODE16									; @@ THUMB16 MODE @@
Rtk2ActivateMarkedThumb
        LDR     r0, [sp]
        MOV     pc, r0							; do the jump to startup
		CODE32									; @@ ARM32 MODE @@
		ALIGN
	ELSE
		LDR     pc, [sp]                        ; do the jump to startup
	ENDIF
;
; First task activation
;

		EXPORT RTK1_ACTIVATE_FIRST_TASK
RTK1_ACTIVATE_FIRST_TASK

        MOV     a3, #Sup32Mode                  ; start mode = it allowed, Sup32
        MSR     CPSR_cxsf, a3

        LDR     sp, [a1]                        ; set stack pointer

        LDR     a3, [a1, #4]                    ; a3 = new pc
        MOV     a4, #0
        STR     a4, [a1, #4]                    ; set not first starting
	IF __THUMB__ = {TRUE}
        ADR     a2, Rtk2ActivateFirstThumb + 1
        BX      a2; 
        CODE16									; @@ THUMB16 MODE @@
Rtk2ActivateFirstThumb
	ENDIF
        MOV     pc, a3                          ; jump to routine
	  	CODE32									; @@ ARM32 MODE @@
		ALIGN

;
; Re-entrant calls with marker and single stack
;
;       RtkTaskMarkerCall(void *f, u8 n, ...)
;
;               where   f : function to be called
;                       n : number of parameters
;
        
		CODE32									; @@ ARM32 MODE @@
		ALIGN

		IMPORT Rtk_PtrMarkerStack
        IMPORT Rtk_PtrCurrentTask
        IMPORT Rtk_TaskMarkerOwner
        IMPORT cus_MarkerStackSize
        IMPORT RtkExceptionRoutine
        EXPORT RtkTaskMarkerCall

RtkTaskMarkerCall
        ; first set standard stack so that
        ;       fp      <== sp points there
        ;       ip      (contains sp on entry)
        ;       lr
        ;       pc      <== fp points there
        ;       p0      <== first parameter of called function
        ;       .
        ;       pn
        MOV     ip, sp
        STMDB   sp!, {a3, a4}
        STMDB   sp!, {fp, ip, lr, pc}
        SUB     fp, ip, #12

        ; set the task's context addressing in a1
        STR     a1, [sp, #-4]!					; save a1 before use (!)
        LDR     a1, =Rtk_PtrCurrentTask			; a1 = @Rtk_PtrCurrentTask
        LDR     a1, [a1]						; a1 = *Rtk_PtrCurrentTask
        ADD     a1, a1, #MARKER_SP_OFFSET

        ; the tricky part wich allows a kind of <setjmp/longjmp>
        ; be careful because the pc is +8 from the instruction using it.
        STMDB   sp!, {a1-a4, v1-v7, fp}			; save all registers because further
												; interruptions can be anywhere
        MRS     a2, cpsr						; get the flags
        STR     a2, [sp, #-4]!					; and store them (for interrupts)
        STR     pc, [sp, #-4]!					; the pc value is @__MarkerBack
        STR     sp, [a1]						; store the sp in task's context
        MOV     a2, #0							; with this, we know where we come from

__MarkerBack
        ; If a restart occurs, it will take place there and a1 == 1
        ; 0 otherwise. The stack looks like :
        ;       pc      <== sp points there
        ;       cpsr
        ;       a1
        ;       .
        ;       a4
        ;       v1
        ;       .
        ;       v7
        ;       fp
        ;       a1
        LDR     a1, [sp, #4]					; restore cpsr
        MSR     CPSR_cxsf, a1
        ADD     fp, sp, #8						; [fp] ==> a1 in stack
        LDMIA   fp, {a1-a4, v1-v7, fp}			; restore all regs

        ; now, this task has the right to own the marker
        ADD     a1, a1, #MARKED_OFFSET - MARKER_SP_OFFSET
        MOV     a4, #1
        STRB    a4, [a1]						; this task uses a marker

        ; and it can tells the world it owns it
        ; note that if this task is interrupted before the completion of
        ; this lines, it will restart from the jump point so no big deal ...
        ADD     a1, a1, #TASKID_OFFSET - MARKED_OFFSET
        LDRB    a4, [a1]						; get task ID
        LDR     a1, =Rtk_TaskMarkerOwner
        STRB    a4, [a1]

        ; now set the new stack
        ; don't care if we come directly or from a longjmp
        ;       a1 : function to call
        ;       a2 : number of parameters
        ;       a3 : free
        ;       a4 : free
        LDR     a1, [sp, #14*4]					; restore a1 on old stack
        LDR     a4, =Rtk_PtrMarkerStack			; a4 = @Rtk_PtrMarkerStack
        LDR     sp, [a4]						; sp = * Rtk_PtrMarkerStack
        ADD     a4, fp, a2, LSL #2				; a4 = fp + 4*n ==> last param to transfer (JLO)
        SUBS    a2, a2, #4
        BLE     __Marker4Param					; do we have more than 4 parameters ?
__MarkerStackLoop								; do the transfer
        LDR     a3, [a4], #-4	
        STR     a3, [sp, #-4]!
        SUBS    a2, a2, #1
        BNE     __MarkerStackLoop

        ; now transfer the register parameters
        ; it can be less than 4, but who cares ?
__Marker4Param
        STR     a1, [sp, #-4]!					; store function to be called address
        LDR     a1, [fp, #4]					; fp ==> 4 bytes over 1st param
        LDR     a2, [fp, #4*2]
        LDR     a3, [fp, #4*3]
        LDR     a4, [fp, #4*4]

	IF __THUMB__ = {TRUE}
        ; and then call the function
        ADR     a3, Rtk2TaskMarkerCallThumb + 1
        BX      a3 
		CODE16									; @@ THUMB16 MODE @@
Rtk2TaskMarkerCallThumb		
        LDR     r0, [sp]
        SUB     r0, #4
        MOV     lr, pc
        MOV     pc, r0							; do the jump to startup
		CODE32									; @@ ARM32 MODE @@
		ALIGN
	ELSE
		; And then call the function
        MOV     lr, pc
        LDR     pc, [sp], #4
	ENDIF        
		; at least we are back ...
        ; just have to un-mark the task
        LDR     a2, =Rtk_PtrCurrentTask         ; only a1 is usefull
        LDR     a2, [a2]                        ; a2 = *Rtk_PtrCurrentTask
        ADD     a2, a2, #MARKED_OFFSET
        MOV     a3, #0
        STRB    a3, [a2]                        ; ok, no more marked

        ; check stack overflow
        LDR     a2, =Rtk_PtrMarkerStack			; a2 = @Rtk_PtrMarkerStack
        LDR     a3, [a2]						; a3 = * Rtk_PtrMarkerStack
        LDR     a2, =cus_MarkerStackSize
        LDR     a2, [a2]
        BIC     a2, a2, #3						; align stack size on 32 bits
        SUB     a3, a3, a2						; a3 = @top of stack
        LDR     a3, [a3]						; a3 = last stack 32 bits word
        LDR     a2, [pc, #__MarkerStackValue-.-8]
        CMP     a3, a2							; and compare value
        BEQ     __MarkerEnd

        MOV     a1, #RTK_STACK_OVERFLOW
        MOV     a2, #-1
        B       RtkExceptionRoutine

        ; doing a normal return will restore everything as the fp as been
        ; preserved along all those stuff, so the caller's stack is still
        ; accessible
        ; also the sp value used for the call is now don't care, so no need
        ; to restore that stack and the return value is in a1 (if any)
__MarkerEnd
        LDMDB   fp, {fp, sp, pc}

__MarkerStackValue
        DCD     0x55555555


;============================================================================
;                       interrupt managment
;============================================================================
        EXPORT RTK2_ENABLE
        EXPORT RTK2_DISABLE

;
; Interrupt enable
;
RTK2_ENABLE
		MRS     a2, cpsr                        ; get cpsr
        ORR     a2, a2, #INT_DISABLE            ; disable interrupts
        MSR     CPSR_cxsf, a2
        ORR     a1, a1, #MODE_MASK              ; keep mode
        AND     a2, a2, a1                      ; restore flags
        MSR     CPSR_cxsf, a2                   ; set cpsr
		BX      lr

;
; Interrupt disable
;
RTK2_DISABLE
        MRS     a1, cpsr                        ; get cpsr
        MOV     a2, a1                          ; keep flags
        ORR     a2, a2, #INT_DISABLE            ; disable interrupts
        MSR     CPSR_cxsf, a2                   ; set cpsr
		BX      lr

;
; Get status flag
;

        EXPORT GetStatus
GetStatus
        MRS     r0, cpsr
        AND     r0, r0, #0xff
        BX      lr

;
; Get Stack Pointer
;
        EXPORT GetSP
GetSP
        MOV     r0, sp
        BX      lr

;
; Get register in stack.
;
        EXPORT RtkGetCallerInStack
RtkGetCallerInStack
        MOV     r0, fp
        SUB     r0, r0, #4
        LDR     r0, [r0]
        BX      lr

        END
