    INCLUDE kernel_b3.i

        IMPORT  sys_AbortData
        IMPORT  sys_AbortPrefetch
        IMPORT  sys_UndefError
        IMPORT  BacktraceStack
        IMPORT  BacktraceStackStart

        PRESERVE8

        AREA    abort_handlers, CODE

;****************************************************************************
;* Function: __AbortData
;****************************************************************************
;* This function should not be called directly
;*
;* This is the Abort Data exception handler
;****************************************************************************
__AbortData     FUNCTION
        EXPORT  __AbortData
        IMPORT  sys_exceptionDump
        IMPORT  AbtStackStart
        IMPORT	sys_data_abort_criteria
        IMPORT	sys_data_abort_handler

	SUB	lr, lr, #8
	STMFD	sp!, {r0-r12, lr}		; save r0-r12, lr_abt

	BL	sys_data_abort_criteria		; check demand paging criteria first

	CMP	r0, #0				; check return value of sys_data_abort_criteria
	BEQ	restore_normal_data_abort	;

	MRS     r1, spsr                	; we are going to change mode
	STR     r1, [sp, #-4]!          	; save spsr_abt in the ABORT stack

	MOV	r0, sp				; store sp_abt to r0
						; 15 is the number of registers saved when enter ABORT mode {spsr_abt, r0-r12, lr_abt}
	ADD	sp, sp, #15*4			; restore sp_abt to original position

	MOV	r1, #IRQ_DISABLE | Sys32Mode	; switch to SYSTEM mode
	MSR	cpsr_c, r1			;

	STR	lr, [sp, #-4]!			; save lr_sys

	LDR	r1, [r0], #4			; get spsr_abt from ABORT stack
	STR	r1, [sp, #-15*4]		; spsr_abt at the top of the SYSTEM stack
	LDMIA	r0, {r0-r12, lr}		; restore register from ABORT stack
	STMDB	sp!, {r0-r12, lr}		; save them in SYSTEM stack
	SUB	sp, sp, #4			; for spsr_abt position
						; current SYSTEM stack = {spsr_abt, r0-r12, lr_abt, lr_sys}

	BL	sys_data_abort_handler

	CMP	r0, #0				; check return value of sys_data_abort_handler
	BEQ	return_to_normal_data_abort	;

	LDR	r1, [sp], #4			; load spsr_abt to r1 from SYS stack
	MOV	r2, sp				; save sys_sp position to r2

	ADD	sp, sp, #14*4			; restore SYSTEM stack position
	LDR	lr, [sp], #4			; restore lr_sys

	MOV	r3, #IRQ_DISABLE | Abt32Mode	; switch to ABORT mode
	MSR	cpsr_c, r3			;

	MSR	spsr_fxsc, r1			; restore spsr_abt from r1

	LDMIA	r2, {r0-r12, lr}		; restore register from SYS stack
	STMDB	sp!, {r0-r12, lr}		; save them in ABORT stack

	LDMFD	sp!, {r0-r12, pc}^		; restore registers and resume execution

return_to_normal_data_abort
	LDR	r1, [sp], #4			; load spsr_abt to r1 from SYS stack

	MOV	r2, sp				; save sys_sp position to r2

	ADD	sp, sp, #14*4			; restore SYSTEM stack position
	LDR	lr, [sp], #4			; restore lr_sys

	MOV	r3, #IRQ_DISABLE | Abt32Mode	; switch to ABORT mode
	MSR	cpsr_c, r3			;

	MSR	spsr_fxsc, r1			; restore spsr_abt from r1

	LDMIA	r2, {r0-r12, lr}		; restore register from SYS stack
	STMDB	sp!, {r0-r12, lr}		; save them in ABORT stack

restore_normal_data_abort
	LDMFD	sp!, {r0-r12, lr}		; restore registers and enter normal data abort
	ADD	lr, lr,	#8			;

        STR     R8, [SP, #-4]                   ;;save R8
        LDR     R8, =(sys_exceptionDump+5*4)    ; Use R8 as &sys_exceptionKeep.r0
        STR     R0, [R8]                        ;;save R0 to &sys_exceptionKeep.r0
        LDR     R8, =(sys_exceptionDump+18*4)   ; Use R8 as &sys_exceptionKeep.dfsr
        MRC     p15, 0, R0, c5, c0, 0           ; get DFSR
        STR     R0, [R8]                        ; save R0 to &sys_exceptionKeep.dfsr
        LDR     R8, =(sys_exceptionDump+19*4)   ; Use R8 as &sys_exceptionKeep.ifsr
        MRC     p15, 0, R0, c5, c0, 1           ; get IFSR
        STR     R0, [R8]                        ; save R0 to &sys_exceptionKeep.ifsr
        LDR     R8, =(sys_exceptionDump+20*4)   ; Use R8 as &sys_exceptionKeep.fault_ar
        MRC     p15, 0, R0, c6, c0, 0           ; get FAR
        STR     R0, [R8]                        ; save R0 to &sys_exceptionKeep.fault_ar
        LDR     R8, [SP, #-4]                   ;;restore R8
                                                ;
        LDR     R0, =(sys_exceptionDump+6*4)    ; Use R0 as a pointer on sys_abortDataDump structure
        STMIA   R0, {r1-r12}                    ; Save all register from r1 to r12 in our structure
                                                ;
        SUB     r0, lr, #8                      ; Get the adress of code which caused the DataAbort
                                                ; What we need in this data-abort exception
                                                ; handler is the address of the instruction that
                                                ; raised the exception; this address is
                                                ; pc = lr - 8
        MRS     r5, cpsr                        ; Put actual ARM mode status in r5
        MRS     r6, spsr                        ; Put ARM mode status when DataAbort occured in r6
                                                ;
        MOV     r2, r6                          ; Save ARM mode status when DataAbort occured in r2
        ORR     r5, r5, #INT_DISABLE            ; Disable IT in all mode we going to use
        ORR     r6, r6, #INT_DISABLE            ; If an IT occurs before we disable them. result will
                                                ; unpredictable if IT handler do not preserve context
        TST     r6, #0xF                        ; Test for the mode which raised the DataAbort
                                                ; All ARM privileged modes can modify the control
                                                ; bits of cpsr. If the data-abort exception was
                                                ; raised in the nonprivileged mode (usr) we
                                                ; could not return to the data-abort exception
                                                ; handler mode. Therefore, we test for the usr
                                                ; mode. If we detect it, we switch the processor
                                                ; to sys mode, since the link register and stack
                                                ; pointer for usr and sys modes are shared
        ORREQ   r6, r6, #0xF                    ; If EQ switch usr->sys mode else nothing to do
        BIC     r7, r6, #0x20 ; (1<<5)          ; Go to forced ARM state using r7
        MSR     cpsr_c, r7                      ; Switching mode
                                                ; The trick for the state switching is to use
                                                ; "forced" ARM state. This step is necessary
                                                ; because the Thumb state doesn't support access
                                                ; to control bits of cpsr.
                                                ; If the exception was generated in Thumb state
                                                ; of some mode, we clear the mode's Thumb bit
                                                ; and enter that mode in ARM state.
                                                ; Then we can get the desired sp and lr values.
                                                ;
        MOV     r3, lr                          ; Save lr in r3
        MOV     r4, sp                          ; Save sp in r4
                                                ;
        MSR     cpsr_c, r5                      ; Switch back to Exception mode
                                                ;
        TST     r6, #0x20                       ; ARM was in thumb mode when DataAbort occured ?
        LDRNEH  r1, [r0]                        ; If not store the 32bits intruction in r1
        LDREQ   r1, [r0]                        ; If yes store the 16bits instruction in r1
        LDR     R8, =sys_exceptionDump          ; Use R8 as a pointer on our structure

        STMIA   R8, {r0-r4}                     ; Save r0 to r4 in our structure

        LDR     R9, =BacktraceStack             ;
        CMP     R4, R9                          ;
        BLS     no_switch_da                     ;
        LDR     R9, =BacktraceStackStart        ;
        CMP     R4, R9                          ;
        BHI     no_switch_da                     ;
        MOV     SP, R4                          ;

no_switch_da     ;; no need to switch SP if SPSR_SP is not inside BacktraceStack
        LDR     R0, =(sys_exceptionDump+6*4)    ; Use R0 as &sys_exceptionDump.r1
        LDMIA   R0, {r1-r12}                    ; Restore r1~r12 context
        LDR     R0, =(sys_exceptionDump+5*4)    ; Use R0 as &sys_exceptionDump.r0
        LDR     R0, [R0]                        ;;Restore R0

        B       sys_AbortData                   ; Branch on C function to send traces and reset

        ENDFUNC

;****************************************************************************
;* Function: __AbortPrefetch
;****************************************************************************
;* This function should not be called directly
;*
;* This is the Abort Prefetch exception handler
;****************************************************************************
__AbortPrefetch FUNCTION
        EXPORT  __AbortPrefetch
        IMPORT  sys_exceptionDump
        IMPORT  AbtStackStart
        IMPORT	sys_prefetch_abort_criteria
        IMPORT	sys_prefetch_abort_handler

	SUB	lr, lr, #4
	STMFD	sp!, {r0-r12, lr}

	MOV	r0, lr				; lr_abt as 1st argument
	BL	sys_prefetch_abort_criteria	; check demand paging criteria first

	CMP	r0, #0				; check return value of sys_prefetch_abort_criteria
	BEQ	restore_normal_prefetch_abort	;

	MRS     r1, spsr                	; we are going to change mode
	STR     r1, [sp, #-4]!          	; save spsr_abt in the ABORT stack

	MOV	r0, sp				; store sp_abt to r0
						; 15 is the number of registers saved when enter ABORT mode {spsr_abt, r0-r12, lr_abt}
	ADD	sp, sp, #15*4			; restore sp_abt to original position

	MOV	r1, #IRQ_DISABLE | Sys32Mode	; switch to SYSTEM mode
	MSR	cpsr_c, r1			;

	STR	lr, [sp, #-4]!			; save lr_sys

	LDR	r1, [r0], #4			; get spsr_abt from ABORT stack
	STR	r1, [sp, #-15*4]		; spsr_abt at the top of the SYSTEM stack
	LDMIA	r0, {r0-r12, lr}		; restore register from ABORT stack
	STMDB	sp!, {r0-r12, lr}		; save them in SYSTEM stack
	SUB	sp, sp, #4			; for spsr_abt position
						; current SYSTEM stack = {spsr_abt, r0-r12, lr_abt, lr_sys}

	MOV	r0, lr				; lr_abt as 1st argument
	BL	sys_prefetch_abort_handler

	CMP	r0, #0				; check return value of sys_prefetch_abort_handler
	BEQ	return_to_normal_prefetch_abort	;

	LDR	r1, [sp], #4			; load spsr_abt to r1 from SYS stack
	MOV	r2, sp				; save sys_sp position to r2

	ADD	sp, sp, #14*4			; restore SYSTEM stack position
	LDR	lr, [sp], #4			; restore lr_sys

	MOV	r3, #IRQ_DISABLE | Abt32Mode	; switch to ABORT mode
	MSR	cpsr_c, r3			;

	MSR	spsr_fxsc, r1			; restore spsr_abt from r1

	LDMIA	r2, {r0-r12, lr}		; restore register from SYS stack
	STMDB	sp!, {r0-r12, lr}		; save them in ABORT stack

	LDMFD	sp!, {r0-r12, pc}^		; restore registers and resume execution

return_to_normal_prefetch_abort
	LDR	r1, [sp], #4			; load spsr_abt to r1 from SYS stack

	MOV	r2, sp				; save sys_sp position to r2

	ADD	sp, sp, #14*4			; restore SYSTEM stack position
	LDR	lr, [sp], #4			; restore lr_sys

	MOV	r3, #IRQ_DISABLE | Abt32Mode	; switch to ABORT mode
	MSR	cpsr_c, r3			;

	MSR	spsr_fxsc, r1			; restore spsr_abt from r1

	LDMIA	r2, {r0-r12, lr}		; restore register from SYS stack
	STMDB	sp!, {r0-r12, lr}		; save them in ABORT stack

restore_normal_prefetch_abort
	LDMFD	sp!, {r0-r12, lr}		; restore registers and enter normal prefetch abort
	ADD	lr, lr,	#4			;

        STR     R8, [SP, #-4]                   ;;save R8
        LDR     R8, =(sys_exceptionDump+5*4)    ; Use R8 as &sys_exceptionKeep.r0
        STR     R0, [R8]                        ;;save R0 to &sys_exceptionKeep.r0
        LDR     R8, =(sys_exceptionDump+18*4)   ; Use R8 as &sys_exceptionKeep.dfsr
        MRC     p15, 0, R0, c5, c0, 0           ; get DFSR
        STR     R0, [R8]                        ; save R0 to &sys_exceptionKeep.dfsr
        LDR     R8, =(sys_exceptionDump+19*4)   ; Use R8 as &sys_exceptionKeep.ifsr
        MRC     p15, 0, R0, c5, c0, 1           ; get IFSR
        STR     R0, [R8]                        ; save R0 to &sys_exceptionKeep.ifsr
        LDR     R8, =(sys_exceptionDump+20*4)   ; Use R8 as &sys_exceptionKeep.fault_ar
        MRC     p15, 0, R0, c6, c0, 0           ; get FAR
        STR     R0, [R8]                        ; save R0 to &sys_exceptionKeep.fault_ar
        LDR     R8, [SP, #-4]                   ;;restore R8
                                                ;
        LDR     R0, =(sys_exceptionDump+6*4)    ; Use R0 as a pointer on sys_abortDataDump structure
        STMIA   R0, {r1-r12}                    ; Save all register from r1 to r12 in our structure
                                                ;
        SUB     r0, lr, #4                      ; Get the adress of code which caused the PrefetchAbort
                                                ; What we need in this prefetch-abort exception
                                                ; handler is the address of the instruction that
                                                ; raised the exception; this address is
                                                ; pc = lr - 4
        MRS     r5, cpsr                        ; Put actual ARM mode status in r5
        MRS     r6, spsr                        ; Put ARM mode status when DataAbort occured in r6
                                                ;
        MOV     r2, r6                          ; Save ARM mode status when PrefetchAbort occured in r2
        ORR     r5, r5, #INT_DISABLE            ; Disable IT in all mode we going to use
        ORR     r6, r6, #INT_DISABLE            ; If an IT occurs before we disable them. result will
                                                ; unpredictable if IT handler do not preserve context
        TST     r6, #0xF                        ; Test for the mode which raised the DataAbort
                                                ; All ARM privileged modes can modify the control
                                                ; bits of cpsr. If the prefetch-abort exception was
                                                ; raised in the nonprivileged mode (usr) we
                                                ; could not return to the prefetch-abort exception
                                                ; handler mode. Therefore, we test for the usr
                                                ; mode. If we detect it, we switch the processor
                                                ; to sys mode, since the link register and stack
                                                ; pointer for usr and sys modes are shared
        ORREQ   r6, r6, #0xF                    ; If EQ switch usr->sys mode else nothing to do
        BIC     r7, r6, #0x20 ; (1<<5)          ; Go to forced ARM state using r7
        MSR     cpsr_c, r7                      ; Switching mode
                                                ; The trick for the state switching is to use
                                                ; "forced" ARM state. This step is necessary
                                                ; because the Thumb state doesn't support access
                                                ; to control bits of cpsr.
                                                ; If the exception was generated in Thumb state
                                                ; of some mode, we clear the mode's Thumb bit
                                                ; and enter that mode in ARM state.
                                                ; Then we can get the desired sp and lr values.
                                                ;
        MOV     r3, lr                          ; Save lr in r3
        MOV     r4, sp                          ; Save sp in r4
                                                ;
        MSR     cpsr_c, r5                      ; Switch back to Exception mode
                                                ;
        MOV     r1, #0                          ; * Prefetch Abort is no need to read the insturction *
        LDR     R8, =sys_exceptionDump          ; Use R8 as a pointer on our structure

        STMIA   R8, {r0-r4}                     ; Save r0 to r4 in our structure

        LDR     R9, =BacktraceStack             ;
        CMP     R4, R9                          ;
        BLS     no_switch_pa                     ;
        LDR     R9, =BacktraceStackStart        ;
        CMP     R4, R9                          ;
        BHI     no_switch_pa                     ;
        MOV     SP, R4                          ;

no_switch_pa     ;; no need to switch SP if SPSR_SP is not inside BacktraceStack
        LDR     R0, =(sys_exceptionDump+6*4)    ; Use R0 as &sys_exceptionDump.r1
        LDMIA   R0, {r1-r12}                    ; Restore r1~r12 context
        LDR     R0, =(sys_exceptionDump+5*4)    ; Use R0 as &sys_exceptionDump.r0
        LDR     R0, [R0]                        ;;Restore R0

        B       sys_AbortPrefetch               ; Branch on C function to send traces and reset

        ENDFUNC

;****************************************************************************
;* Function: __Undef
;****************************************************************************
;* This function should not be called directly
;*
;* This is the Undefined Instruction exception handler
;****************************************************************************
__Undef         FUNCTION
        EXPORT  __Undef
        IMPORT  sys_exceptionDump
        IMPORT  UndefStackStart

        STR     R8, [SP, #-4]                   ;;save R8
        LDR     R8, =(sys_exceptionDump+5*4)    ; Use R8 as &sys_exceptionKeep.r0
        STR     R0, [R8]                        ;;save R0 to &sys_exceptionKeep.r0
        LDR     R8, =(sys_exceptionDump+18*4)   ; Use R8 as &sys_exceptionKeep.dfsr
        MRC     p15, 0, R0, c5, c0, 0           ; get DFSR
        STR     R0, [R8]                        ; save R0 to &sys_exceptionKeep.dfsr
        LDR     R8, =(sys_exceptionDump+19*4)   ; Use R8 as &sys_exceptionKeep.ifsr
        MRC     p15, 0, R0, c5, c0, 1           ; get IFSR
        STR     R0, [R8]                        ; save R0 to &sys_exceptionKeep.ifsr
        LDR     R8, =(sys_exceptionDump+20*4)   ; Use R8 as &sys_exceptionKeep.fault_ar
        MRC     p15, 0, R0, c6, c0, 0           ; get FAR
        STR     R0, [R8]                        ; save R0 to &sys_exceptionKeep.fault_ar
        LDR     R8, [SP, #-4]                   ;;restore R8
                                                ;
        LDR     R0, =(sys_exceptionDump+6*4)    ; Use R0 as a pointer on sys_abortDataDump structure
        STMIA   R0, {r1-r12}                    ; Save all register from r1 to r12 in our structure
                                                ;
        SUB     r0, lr, #4                      ; Get the adress of code which caused the Undefined-Instruction
                                                ; What we need in this undefined-instruction exception
                                                ; handler is the address of the instruction that
                                                ; raised the exception; this address is
                                                ; pc = lr - 4
        MRS     r5, cpsr                        ; Put actual ARM mode status in r5
        MRS     r6, spsr                        ; Put ARM mode status when Undefined-Instruction occured in r6
                                                ;
        MOV     r2, r6                          ; Save ARM mode status when DataAbort occured in r2
        ORR     r5, r5, #INT_DISABLE            ; Disable IT in all mode we going to use
        ORR     r6, r6, #INT_DISABLE            ; If an IT occurs before we disable them. result will
                                                ; unpredictable if IT handler do not preserve context
        TST     r6, #0xF                        ; Test for the mode which raised the DataAbort
                                                ; All ARM privileged modes can modify the control
                                                ; bits of cpsr. If the undefined-instruction exception was
                                                ; raised in the nonprivileged mode (usr) we
                                                ; could not return to the undefined-instruction exception
                                                ; handler mode. Therefore, we test for the usr
                                                ; mode. If we detect it, we switch the processor
                                                ; to sys mode, since the link register and stack
                                                ; pointer for usr and sys modes are shared
        ORREQ   r6, r6, #0xF                    ; If EQ switch usr->sys mode else nothing to do
        BIC     r7, r6, #0x20 ; (1<<5)          ; Go to forced ARM state using r7
        MSR     cpsr_c, r7                      ; Switching mode
                                                ; The trick for the state switching is to use
                                                ; "forced" ARM state. This step is necessary
                                                ; because the Thumb state doesn't support access
                                                ; to control bits of cpsr.
                                                ; If the exception was generated in Thumb state
                                                ; of some mode, we clear the mode's Thumb bit
                                                ; and enter that mode in ARM state.
                                                ; Then we can get the desired sp and lr values.
                                                ;
        MOV     r3, lr                          ; Save lr in r3
        MOV     r4, sp                          ; Save sp in r4
                                                ;
        MSR     cpsr_c, r5                      ; Switch back to Exception mode
                                                ;
        TST     r6, #0x20                       ; ARM was in thumb mode when Undefined-Instruction occured ?
        LDRNEH  r1, [r0]                        ; If not store the 32bits intruction in r1
        LDREQ   r1, [r0]                        ; If yes store the 16bits instruction in r1
        LDR     R8, =sys_exceptionDump          ; Use R8 as a pointer on our structure

        STMIA   R8, {r0-r4}                     ; Save r0 to r4 in our structure

        LDR     R9, =BacktraceStack             ;
        CMP     R4, R9                          ;
        BLS     no_switch_ud                    ;
        LDR     R9, =BacktraceStackStart        ;
        CMP     R4, R9                          ;
        BHI     no_switch_ud                    ;
        MOV     SP, R4                          ;

no_switch_ud     ;; no need to switch SP if SPSR_SP is not inside BacktraceStack
        LDR     R0, =(sys_exceptionDump+6*4)    ; Use R0 as &sys_exceptionDump.r1
        LDMIA   R0, {r1-r12}                    ; Restore r1~r12 context
        LDR     R0, =(sys_exceptionDump+5*4)    ; Use R0 as &sys_exceptionDump.r0
        LDR     R0, [R0]                        ;;Restore R0

        B       sys_UndefError                  ; Branch on C function to send traces and reset

        ENDFUNC

	IF :DEF:__I_SW__
	ELSE

    IF :DEF:__RTK_DIAGNOSE_ENHANCE__
        IMPORT   RTK2_DISABLE_K
        IMPORT   RtkGetSpAndPc
        IMPORT   backtrace_preprocess
        IMPORT   sys_exceptionKeep
        IMPORT   RtkRegisters
        IMPORT   sys_exceptionKeep_backup
        IMPORT   memcpy

_RtkAssertRoutine         FUNCTION
        EXPORT   _RtkAssertRoutine
        IMPORT   _RtkAssertRoutine_C
        STR     R6, [SP, #-4]                   ;;save r6
        LDR     R6, =(sys_exceptionKeep+5*4)    ; Use R6 as &sys_exceptionKeep.r0
        STR     R0, [R6], #-4                   ;;save R0 and point to &sys_exceptionKeep.SP
        STR     SP, [R6], #-4                   ;;save SP and point to &sys_exceptionKeep.SP
        STR     LR, [R6], #-4                   ;;save LR and point to &sys_exceptionKeep.CPSR
        MRS     R0, cpsr                        ;  Put actual ARM mode status in R0
        STR     R0, [R6], #-4                   ;;save CPSR and point to &sys_exceptionKeep.PC
        MRS     R0, spsr                        ;  save SPSR in R0
        STR     R0, [R6]                        ;;save SPSR in &sys_exceptionKeep.PC
        LDR     R6, [SP, #-4]                   ;;restore r6
        LDR     R0, =(sys_exceptionKeep+6*4)    ; Use R0 as &sys_exceptionKeep.r1
        STMIA   R0, {r1-r12}                    ; Save all register from r1 to r12 in our structure

        BLX     RTK2_DISABLE_K                  ;; fetch RTK2_DISABLE_K before next instruction
        LDR     LR, =(sys_exceptionKeep+3*4)    ; &sys_exceptionKeep.lr
        LDR     LR, [LR]                        ;;restore LR
        ;;;BLX RtkGetSpAndPc
        LDR	    R0, =RtkRegisters
        STR	    SP, [R0], #4
        STR	    LR, [R0], #4
        STR	    LR, [R0], #4

        MOV     R0, #240                        ; SYSTEM_ASSERT
        BLX     backtrace_preprocess
        CMP     R0, #0
        LDREQ   SP, =(BacktraceStackStart)      ;;Switch_backtrace_SP
        SUBEQ   SP, SP, #0xC                    ;;sub guard pattern
        BNE     nocpy_a
        LDR     R0, =(sys_exceptionKeep_backup) ; Use R0 as &sys_exceptionKeep_backup
        LDR     R1, =(sys_exceptionKeep)        ; Use R1 as &sys_exceptionKeep
        MOV     R2, #18*4                       ; sizeof(sys_exceptionDump_t)
        LDR     R3, =memcpy
        BLX     R3                              ; backup sys_exceptionKeep

        ;;context restore
nocpy_a LDR     R0, =(sys_exceptionKeep+6*4)    ; Use R0 as &sys_exceptionKeep.r1
        LDMIA   R0, {r1-r12}                    ; Restore r1~r12 context
        LDR     R0, =(sys_exceptionKeep+5*4)    ; Use R0 as &sys_exceptionKeep.r0
        LDR     R0, [R0]                        ;;Restore R0
        LDR     LR, =_RtkAssertRoutine_C
        BX      LR
        ENDFUNC

RtkExceptionRoutine         FUNCTION
        EXPORT   RtkExceptionRoutine
        IMPORT   RtkExceptionRoutine_C
        STR     R6, [SP, #-4]                   ;;save r6
        LDR     R6, =(sys_exceptionKeep+5*4)    ; Use R6 as &sys_exceptionKeep.r0
        STR     R0, [R6], #-4                   ;;save R0 and point to &sys_exceptionKeep.SP
        STR     SP, [R6], #-4                   ;;save SP and point to &sys_exceptionKeep.SP
        STR     LR, [R6], #-4                   ;;save LR and point to &sys_exceptionKeep.CPSR
        MRS     R0, cpsr                        ;  Put actual ARM mode status in R0
        STR     R0, [R6], #-4                   ;;save CPSR and point to &sys_exceptionKeep.PC
        MRS     R0, spsr                        ;  save SPSR in R0
        STR     R0, [R6]                        ;;save SPSR in &sys_exceptionKeep.PC
        LDR     R6, [SP, #-4]                   ;;restore r6
        LDR     R0, =(sys_exceptionKeep+6*4)    ; Use R0 as &sys_exceptionKeep.r1
        STMIA   R0, {r1-r12}                    ; Save all register from r1 to r12 in our structure

        BLX     RTK2_DISABLE_K                  ;; fetch RTK2_DISABLE_K before next instruction
        LDR     LR, =(sys_exceptionKeep+3*4)    ; &sys_exceptionKeep.lr
        LDR     LR, [LR]                        ;;restore LR
        ;;;BLX RtkGetSpAndPc
        LDR	    R0, =RtkRegisters
        STR	    SP, [R0], #4
        STR	    LR, [R0], #4
        STR	    LR, [R0], #4

        LDR     R0, =(sys_exceptionKeep+5*4)    ; Use R0 as &sys_exceptionKeep.r0
        LDR     R0, [R0]                        ;;exceptionType
        BLX     backtrace_preprocess
        CMP     R0, #0
        LDREQ   SP, =(BacktraceStackStart)      ;;Switch_backtrace_SP
        SUBEQ   SP, SP, #0xC                    ;;sub guard pattern
        BNE     nocpy_e
        LDR     R0, =(sys_exceptionKeep_backup) ; Use R0 as &sys_exceptionKeep_backup
        LDR     R1, =(sys_exceptionKeep)        ; Use R1 as &sys_exceptionKeep
        MOV     R2, #18*4                       ; sizeof(sys_exceptionDump_t)
        LDR     R3, =memcpy
        BLX     R3                              ; backup sys_exceptionKeep

        ;;context restore
nocpy_e LDR     R0, =(sys_exceptionKeep+6*4)    ; Use R0 as &sys_exceptionKeep.r1
        LDMIA   R0, {r1-r12}                    ; Restore r1~r12 context
        LDR     R0, =(sys_exceptionKeep+5*4)    ; Use R0 as &sys_exceptionKeep.r0
        LDR     R0, [R0]                        ;;Restore R0
        LDR     LR, =RtkExceptionRoutine_C
        BX      LR
        ENDFUNC
    ENDIF ;__RTK_DIAGNOSE_ENHANCE__

	ENDIF ;__I_SW__

        END



     END
