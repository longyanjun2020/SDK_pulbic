    INCLUDE kernel_b2.i

    IMPORT  Rtk_RegionCount
    IMPORT  Rtk_WorthItSched
    IMPORT  Rtk11Schedule
    IMPORT  IntcIrqHandler
    IMPORT  IntcFiqHandler

    IF :DEF:__REAL_TIME_PROBLEM_DIAGNOSE__
    IMPORT  g_apSysLastPcBeforeItPreemption
    IMPORT  g_nSysLastPcBeforeItPreemptionIndex
    IMPORT  g_pSysActiveIsr
    IMPORT  g_anSysHacPreemtedByItHistogram
    IMPORT  hac2_RealTimeCheck
    ENDIF

    ; export for the boot loader
    EXPORT __SoftInt
    EXPORT __IrqISR
    EXPORT __FiqISR

    IF :DEF:__INTERRUPT_INTEGRITY_PROTECT__
    IMPORT  g_ptW5IrqControl
    IMPORT  g_ptW5TbuC
    IMPORT  RtkExceptionRoutine
    IMPORT  sys_bFintCheckReady
    IMPORT  sys_IsrCheckAbIsr
    IMPORT  sys_IsrCheckAbIsrNumber
    IMPORT  sys_IsrCheckAbLr
    IMPORT  sys_IsrCheckAbSp
    ENDIF

    IF :DEF:__SEPARATE_INTERRUPT_API__
    IMPORT  g_nSysDisableInterrupt_k
    ENDIF

    IF :DEF:__SEPARATE_INTERRUPT_API_PROFILE__
    IMPORT profileIsrQbCount
    ENDIF

    IF :DEF: __I_SW__
    ELSE
    IF :DEF:__SOFTWARE_WATCHDOG_PROFILE__
    IMPORT sys_SwdProfile
    ELSE
    IMPORT sys_profiling_irq_strart_time
    ENDIF
    IMPORT g_ptW5SysTimer
    IMPORT sys_SwdCountProfileSum
    IMPORT sys_bPreemptedSched
    IMPORT sys_bSwdProfileOn
    IMPORT sys_queryProfileState
    ENDIF
    IF :DEF:__RTK_DIAGNOSE_ENHANCE__
    IMPORT isrStartTime
    ENDIF
    IMPORT backtrace_ToolUpdateTaskMgr
    IMPORT MsSysAutoCpuUpdate
    IMPORT MsSysAutoCpuIsrStartTime

    IF :DEF:__INTERRUPT_INTEGRITY_PROTECT__
TBU_FINT_IT_MSK           EQU       0x0001<<21
TBU_FINT_ENA              EQU       0x0001<<0
CPU_WAKE_UP_INT_ENA       EQU       0x0001<<2

ISR_INTERRUPT_CORRUPT     EQU       202
    ENDIF

ABORT_DATA      EQU       1
ABORT_PREFETCH  EQU       2
UNDEF           EQU       3
RTK_SUSPENDED   EQU       7
INT_GPIO_NUMBER EQU       15

    IF :DEF:__RTK_STACK_DIAGNOSE__

CURRENT_STACK_TOP_OFF    EQU 16
CURRENT_STACK_SIZE_OFF   EQU 20
CURRENT_STACK_SP_OFF     EQU 8
CURRENT_MARKED_OFFSET    EQU 36
PATTERN_CHECK_OFFSEET    EQU 28

;map to sys_rtk_ho.h/cus_backtrace_filter.h
SYS_STACK_CORRUPT   EQU 191
ISR_STACK_CORRUPT   EQU 192
SUV_STACK_CORRUPT   EQU 193
TASK_STACK_CORRUPT  EQU 194
FIQ_STACK_CORRUPT   EQU 195

;map to rtktool.c
SP_OVERRUN    EQU 0
TOP_BROKEN    EQU 1
BOTTOM_BROKEN EQU 2

;map to tasks.c
SUV_STACK  EQU 1
ISR_STACK  EQU 2
TASK_STACK EQU 3
FIQ_STACK  EQU 4

    IMPORT g_ptW5TbuC
    IMPORT RtkStartCalQb
    IMPORT RtkStopCalQb

    ENDIF

    IF :DEF: __I_SW__
    ELSE
;map to sys_rtk_config.h
RTK_MAX_TASKS EQU 200
    ENDIF

BA_SYSREG   EQU  0x34000400
IMI1_ADDR   EQU  0X08000000
MEM0_ADDR   EQU  0X0C000000

    PRESERVE8

;===============================================================================
;                               SWI handler
;===============================================================================
     AREA |isr|, CODE, READONLY

     CODE32
     ALIGN

__SoftInt	FUNCTION

    IMPORT SWI_Handler
    B       SWI_Handler

    ENDFUNC

;===============================================================================
;                               IRQ service
;===============================================================================

    IF :DEF:__INTERRUPT_INTEGRITY_PROTECT__
__IrqISR_Abnormal
    MRS     r1, cpsr                ; Mask interrupt first
    ORR     r1, r1, #IRQ_DISABLE
    MSR     CPSR_cxsf, r1

    MOV     r3, r0
    CMP     r3, #0                  ; 0 for entry, 1 for exit
    BEQ     __IrqISR_Abnormal_Get_Info

    MOV     r1, #Sup32Mode          ; If exit, use sup32 mode sp
    B       __IrqISR_Abnormal_End

    ; If entry, get information and previous mode sp
__IrqISR_Abnormal_Get_Info
    ; In entry, scanning pending IRQ ID sometimes lead to IRQ 0
    ; So postpone to exception routine to dump g_ptW5IrqControl information

    ;LDR     r0, =ITCTRL_Pending_1   ; get interrupt number
    ;LDRH    r2, [r0]                ; IT with equal/lower priority are masked
    ;AND     r2, r2, #0x00FC
    ;LDR     r0, =IrqHandlerTbl
    ;LDR     r1, [r0, r2]            ; use table to get handler address

    ;LDR     r0, =sys_IsrCheckAbIsr  ; Record abnormal isr routine information
    ;STR     r1, [r0]
    ;LDR     r0, =sys_IsrCheckAbIsrNumber
    ;LSR     r2, r2, #2
    ;STR     r2, [r0]

    MRS     r0, spsr
    AND     r0, r0, #0x1F           ; Use M0~M4 only
    MOV     r1, #2_10001            ; FIQ mode
    CMP     r0, r1
    BEQ     __IrqISR_Abnormal_End
    MOV     r1, #Sup32Mode
    CMP     r0, r1
    BEQ     __IrqISR_Abnormal_End
    MOV     r1, #Sys32Mode
    CMP     r0, r1
    BEQ     __IrqISR_Abnormal_End
    MOV     r1, #2_10010            ; IRQ mode (default)

__IrqISR_Abnormal_End
    MRS     r0, cpsr
    ORR     r1, #INT_DISABLE        ; Disable interrupt to prevent ISR
    MSR     cpsr_cxsf, r1
    LDR     r1, =sys_IsrCheckAbSp
    STR     sp, [r1]
    MSR     cpsr_cxsf, r0           ; Restore cpsr

    MOV     r0, #ISR_INTERRUPT_CORRUPT
    MOV     r1, #0                  ; 0 for entry fail, 1 for exit fail
    CMP     r3, #0
    BEQ     __IrqISR_CheckFail_End
    MOV     r1, #1

__IrqISR_CheckFail_End
    BLX     RtkExceptionRoutine     ; Branch to exception routine
    ENDIF


;-------------------------------------------------------------------------------
; IRQ prologue
;-------------------------------------------------------------------------------
__IrqISR
    ; When an IRQ is detected the arm processor does the following actions:
    ; - lr_irq = pc + 4 (return address + 4)
    ; - spsr_irq = cpsr
    ; - cpsr[4:0] = 0b10010 (enter IRQ mode)
    ; - cpsr[5] = 0 (execute in ARM state)
    ; - cpsr[6] unchanged
    ; - cpsr[7] = 1 (disable normal interrupts)
    ; - pc = 0x00000018 (here : __IrqISR placed by scatter file)

    ; save registers into IRQ stack
    SUB     lr, lr, #4              ; to return by LDMIA instruction
    STMDB   sp!, {r0-r3, ip, lr}    ; save work registers and lr_irq
                                    ; scratched by call to handler
    MRS     r0, spsr                ; we are going to change mode
    STR     r0, [sp, #-4]!          ; save spsr_irq in the IRQ stack

    IF :DEF: __RTK_PROFILE_ENHANCE__
    IMPORT sampling_LR
    LDR	    r2, =sampling_LR
    STR     lr, [r2]
    ENDIF

    IF :DEF: __I_SW__
    ELSE

    AND     r2, r0, #MODE_MASK              ; If the spsr is in task mode, record the start time
    CMP     r2, #Sys32Mode
    BNE     __IrqISR_Entry_No_Save_SwdProfile

    ; take  g_ptW5SysTimer->u32_StdaCounter
    LDR     r2, =g_ptW5SysTimer
    LDR     r2, [r2]
    LDR     r2, [r2, #0x44]
    
    IF :DEF:__SOFTWARE_WATCHDOG_PROFILE__
    ; sys_SwdProfile[RTK_MAX_TASKS].u32_StartStdaCount = g_ptW5SysTimer->u32_StdaCounter;
    LDR     r3, =sys_SwdProfile
    STR     r2, [r3, #RTK_MAX_TASKS*16]
    ELSE
    ; sys_profiling_irq_strart_time  = g_ptW5SysTimer->u32_StdaCounter;
    LDR     r3, =sys_profiling_irq_strart_time
    STR     r2, [r3]
    ENDIF
    
    IF :DEF:__RTK_DIAGNOSE_ENHANCE__
    ; Store ISR start time,  isrStartTime = g_ptW5SysTimer->u32_StdaCounter;
    LDR     r3, =isrStartTime
    STR     r2, [r3]
    ENDIF
    
    PUSH    {lr}                    ; save irq_lr in the IRQ stack
    BLX     MsSysAutoCpuIsrStartTime
    POP     {lr}                    ; restore irq_lr

__IrqISR_Entry_No_Save_SwdProfile
    ENDIF

    IF :DEF:__INTERRUPT_INTEGRITY_PROTECT__
    LDR     r1, =sys_IsrCheckAbLr           ; Store ISR lr
    STR     lr, [r1]
    ENDIF

    IF :DEF:__RTK_STACK_DIAGNOSE__
    ;AND     r0, r0, #0xF
    ;CMP     r0, #0xF                        ; if r2 is 0xf, it means spsr is usr/system mode
    ;BNE     IRQ_SYS_NO_CHECK
    ;BL      __SYS_STACK_CHECK
;IRQ_SYS_NO_CHECK
    ENDIF

    IF :DEF:__SEPARATE_INTERRUPT_API_PROFILE__
    ; TODO: Mask IRQ and FIQ to profile
    MRS     r0, cpsr
    ORR     r1, r0, #INT_DISABLE
    PUSH    {r0}
    MSR     cpsr_c, r1                      ; Switching back

    LDR     r1, =g_ptW5TbuC                     ; Get start QB count
    LDR     r1, [r1]
    LDR     r3, [r1, #8]
    ENDIF

    IF :DEF:__INTERRUPT_INTEGRITY_PROTECT__
    LDR     r0, =g_ptW5TbuC
    LDR     r0, [r0]
    LDR     r0, [r0, #48]
    MOV     r1, #CPU_WAKE_UP_INT_ENA
    AND     r0, r0, r1
    CMP     r0, #0
    BNE     __IrqISR_IntCheckEnd_Entry   ; If enabled (in TbuWakeupISR context), skip check

    LDR     r0, =sys_bFintCheckReady
    LDRB    r0, [r0]
    CMP     r0, #1
    BNE     __IrqISR_IntCheckEnd_Entry   ; If fint not initialized, skip check

    MOV     r0, #0                  ; Reserve r0 for entry fail
    LDR     r1, =g_ptW5IrqControl       ; Check FINT mask
    LDR     r1, [r1]
    LDR     r1, [r1, #28]           ; Get u32_Mask0
    MOV     r2, #TBU_FINT_IT_MSK
    AND     r1, r1, r2
    CMP     r1, #0
    BEQ     __IrqISR_Abnormal

    LDR     r1, =g_ptW5TbuC             ; Continue to check TBU register
    LDR     r1, [r1]
    LDR     r1, [r1, #48]           ; Get u32_IntCtrl
    MOV     r2, #TBU_FINT_ENA
    AND     r1, r1, r2
    CMP     r1, #0
    BEQ     __IrqISR_Abnormal

__IrqISR_IntCheckEnd_Entry
    ENDIF

    IF :DEF:__SEPARATE_INTERRUPT_API_PROFILE__
    LDR     r1, =g_ptW5TbuC
    LDR     r1, [r1]
    LDR     r1, [r1, #8]
    MOV     r0, r3
    BLX     profileIsrQbCount       ; Profile QB count

    ; TODO: Restore FIQ to profile
    POP     {r0}
    MSR     CPSR_cxsf, r0
    ENDIF

    IF :DEF:__RTK_DIAGNOSE_ENHANCE__
    IMPORT  Rtk_IsIrqFiqMode
    LDR     r0, =Rtk_IsIrqFiqMode
    MOV     r1, #0x12
    STR     r1, [r0]
    ENDIF

    IF :DEF:__REAL_TIME_PROBLEM_DIAGNOSE__
    LDR     r0, =g_apSysLastPcBeforeItPreemption
    LDR     r1, =g_nSysLastPcBeforeItPreemptionIndex
    LDR     r2, [r1]
    STR     lr, [r0, r2, LSL #2]    ; Save the last PC (which is LR in IRQ mode) being preempted by IRQ.
                                    ; Luckily, LR offset 4 in IRQ mode was already
                                    ; corrected while saving registers into IRQ stack.
                                    ; TODO: Nested IRQ is not handled here. Only the last PC is recored.
    ADD     r2, r2, #1              ; Increment the index
    AND     r2, r2, #0x3            ; Index modulo by 4 (0~3)
    STR     r2, [r1]
    ENDIF

    IF :DEF:__SOFTWARE_WATCHDOG__
    ; start of software watchdog Task register handling [__SOFTWARE_WATCHDOG__]
    MRS     r0, cpsr                        ; Put actual ARM mode status in r5
    MRS     r1, spsr                        ; Put ARM mode status when DataAbort occured in r6
                                                ;
    ORR     r1, r1, #INT_DISABLE            ; If an IT occurs before we disable them. result will
                                                ; unpredictable if IT handler do not preserve context
    MOV     r2, r1                          ; Save ARM mode status when DataAbort occured in r2
    AND     r2, r2, #0xF
    CMP     r2, #0xF                        ; if r2 is 0xf, it means spsr is usr/system mode
    BNE     __IrqISR_NoSave

__IrqISR_SaveUsrReg

    IMPORT  Rtk_CurrentTask
    IF :DEF:__RTK_DIAGNOSE_ENHANCE__
    IMPORT  Rtk_IsrRegisterSet
    ELSE
    IMPORT  Rtk_CurrentTaskStackDump
    ENDIF

    ORR     r1, r1, #0xF                    ; If EQ switch usr->sys mode else nothing to do

    BIC     r2, r1, #0x20 ; (1<<5)          ; Go to forced ARM state using r7
    MOV     r3, lr                          ; save PC to r3
    MSR     cpsr_c, r2                      ; Switching mode
                                            ; The trick for the state switching is to use
                                            ; "forced" ARM state. This step is necessary
                                            ; because the Thumb state doesn't support access
                                            ; to control bits of cpsr.
                                            ; If the exception was generated in Thumb state
                                            ; of some mode, we clear the mode's Thumb bit
                                            ; and enter that mode in ARM state.
                                            ; Then we can get the desired sp and lr values.

    IF :DEF:__RTK_DIAGNOSE_ENHANCE__
    LDR     r1, =Rtk_IsrRegisterSet         ; save sp in Rtk_Rtk_IsrRegisterSet
    ELSE
    LDR     r1, =Rtk_CurrentTaskStackDump   ; save sp in Rtk_CurrentTaskStackDump.sp
    ENDIF
    STR     sp, [r1], #4

    MRS     r2, cpsr                        ; store user mode cpsr in r2
    STMIA   r1!, {r2, r4-r12}               ; save registers in Rtk_CurrentTaskStackDump.reg
    STR     r3, [r1]

__IrqISR_NoSave

    MSR     cpsr_c, r0                      ; Switching back
    ; end of software watchdog Task register handling [__SOFTWARE_WATCHDOG__]
    ENDIF

    IF __LOGIC_ANALYSER__ = {TRUE}
    ;Up  Gpio when IT starting
    MOVS    r0, #INT_GPIO_NUMBER    ;Dedicated GPIO to IT
    MOVS    r2, #1
    LSLS    r2,r2,r0                ;put GPIO mask into r2
    LDR     r1,=0x34001000              ;not fine. if GPIO > 31, does not work
    LDR     r1,[r1, #0x3c]          ;offset of dataout 0
    MOVS    r0,r1
    LDR     r1,=0x34001000
    ORRS    r0,r0,r2
    STR     r0,[r1, #0x3c]
    ENDIF

    MOV     r0, #INT_DISABLE | Sup32Mode    ; IT will be enabled in handler later
    MSR     cpsr_c, r0                      ; switch to SVC mode to keep lr_irq
                                            ; in case of nested interrupts
    STR     lr, [sp, #-4]!                  ; save lr_svc for reeentrance

;-------------------------------------------------------------------------------
; IRQ User Interrupt Service Routine (User ISR)
;-------------------------------------------------------------------------------

; with arch 5TE
    BLX     IntcIrqHandler  ; call handler

;-------------------------------------------------------------------------------
; IRQ epilogue
;-------------------------------------------------------------------------------

    LDR     lr,[sp],#4              ; restore lr_svc

    IF :DEF:__RTK_STACK_DIAGNOSE__
    MOV     r1, sp                  ;store sp point (SUV mode) for later use
    LDR     r2, =0xFFFFFFFF         ; r2 = call handler
    ENDIF

    MOV     r0, #IRQ_DISABLE | Irq32Mode ; disable irq to prevent nested IT
    MSR     cpsr_cxsf, r0           ; switch back to IRQ mode

    IF :DEF:__RTK_DIAGNOSE_ENHANCE__
    IMPORT  Rtk_IsIrqFiqMode

    ;MRS     r0, spsr
    LDR     r0, [sp, #4]
    AND     r0, r0, #0x1F
    ;CMP     r0, #0x1F
    ;BNE     __IrqISR_CheckIsrModeExit
    CMP     r0, #0x13
    BEQ     __IrqISR_CheckIsrModeExit
    LDR     r0, =Rtk_IsIrqFiqMode
    MOV     r3, #0
    STR     r3, [r0]
__IrqISR_CheckIsrModeExit
    ENDIF

    IF :DEF:__RTK_STACK_DIAGNOSE__
    BL __SUV_STACK_CHECK
    ENDIF

    IF :DEF:__INTERRUPT_INTEGRITY_PROTECT__
    LDR     r0, =g_ptW5TbuC
    LDR     r0, [r0]
    LDR     r0, [r0, #48]
    MOV     r1, #CPU_WAKE_UP_INT_ENA
    AND     r0, r0, r1
    CMP     r0, #0
    BNE     __IrqISR_IntCheckEnd_Exit    ; If enabled (in TbuWakeupISR context), skip check

    LDR     r0, =sys_bFintCheckReady
    LDRB    r0, [r0]
    CMP     r0, #1
    BNE     __IrqISR_IntCheckEnd_Exit    ; If fint not initialized, skip check

    MOV     r0, #1                  ; Reserve r0 for exit fail
    LDR     r1, =g_ptW5IrqControl       ; Check FINT mask
    LDR     r1, [r1]
    LDR     r1, [r1, #28]           ; Get u32_Mask0
    MOV     r2, #TBU_FINT_IT_MSK
    AND     r1, r1, r2
    CMP     r1, #0
    BEQ     __IrqISR_Abnormal

    LDR     r1, =g_ptW5TbuC             ; Continue to check TBU register
    LDR     r1, [r1]
    LDR     r1, [r1, #48]           ; Get u32_IntCtrl
    MOV     r2, #TBU_FINT_ENA
    AND     r1, r1, r2
    CMP     r1, #0
    BEQ     __IrqISR_Abnormal

__IrqISR_IntCheckEnd_Exit
    ENDIF

    IF :DEF:__REAL_TIME_PROBLEM_DIAGNOSE__
    LDR     r0, =g_pSysActiveIsr      ; Save the ISR to branch later
    MOV     r1, #0xffffffff
    STR     r1, [r0]
    ENDIF

    LDR     r0, =Rtk_RegionCount
    LDRH    r1, [r0]
    CMP     r1, #0
    BNE     __IrqNoSchedule

    IF __LOGIC_ANALYSER__ = {TRUE}
    ;Down  Gpio when IT finished
    MOVS    r0, #INT_GPIO_NUMBER    ;Dedicated GPIO to IT
    MOVS    r2, #1
    LSLS    r2,r2,r0                ;put GPIO mask into r2
    LDR     r1,=0x34001000          ;not fine. if GPIO > 31, does not work
    LDR     r1,[r1, #0x3c]          ;offset of dataout 0.
    MOVS    r0,r1
    LDR     r1,=0x34001000
    BICS    r0,r0,r2
    STR     r0,[r1, #0x3c]
    ENDIF

    LDR     r0, =Rtk_WorthItSched
    LDRB    r2, [r0]
    CMP     r2, #0
    BNE     __IrqSchedule           ; check if worth scheduling

__IrqNoSchedule
    LDR     r0, [sp], #4
    MSR     spsr_cxsf, r0           ; restore spsr_irq

    IF :DEF: __I_SW__
    ELSE
    AND     r0, r0, #MODE_MASK              ; If the spsr is in task mode, counting spent time
    CMP     r0, #Sys32Mode
    BNE       __IrqISR_Exit1_No_Save_SwdProfile

__IrqISR_Exit1_Save_IrqTime
    MOV     r0, #RTK_MAX_TASKS
    BLX     backtrace_ToolUpdateTaskMgr
    MOV     r0, #RTK_MAX_TASKS
    BLX     MsSysAutoCpuUpdate
    
    IF :DEF:__SOFTWARE_WATCHDOG_PROFILE__
    ELSE
    BLX     sys_queryProfileState         ; check light weight or general cpu profiling is ON or OFF
    CMP     r0, #1
    BNE     __IrqISR_Exit1_No_Save_SwdProfile
    ENDIF

__IrqISR_Exit1_Save_SwdProfile
    MOV     r0, #RTK_MAX_TASKS
    BLX     sys_SwdCountProfileSum

__IrqISR_Exit1_No_Save_SwdProfile
    ENDIF

    LDMIA   sp!, {r0-r3, ip, pc}^   ; restore work registers and return
                                    ; cpsr = spsr_irq
                                    ; pc = lr_irq
__IrqSchedule
    MOV     r0, sp                  ; store sp_irq stack at spsr_irq position
    ADD     sp, sp, #7*4            ; and update it before leaving
    ; 7 is the number of registers saved when enter IRQ

    MOV     r1, #IRQ_DISABLE |  Sys32Mode ; here IRQ are already disabled
                                          ; just change mode to SYS
    MSR     cpsr_cxsf, r1           ; switch to SYS mode

    STR     lr, [sp, #-4]!          ; save lr_sys

    ; transfer from IRQ stack to SYS stack
    LDR     r1, [r0], #4            ; get spsr from IRQ stack
    STR     r1, [sp, #-7*4]         ; spsr at the top of the SYS stack,
    LDMIA   r0, {r0-r3, ip, lr}     ; after all updates restore all registers
    STMDB   sp!, {r0-r3, ip, lr}    ; and save them in SYS stack
    SUB     sp, sp, #0x04           ; for spsr position

    IF :DEF:__SEPARATE_INTERRUPT_API__
    LDR     r0, =g_nSysDisableInterrupt_k        ; Change flag to resolve false alarm
    MOV     r1, #1
    STR     r1, [r0]
    ENDIF

    IF :DEF: __I_SW__
    ELSE
    IF :DEF:__SOFTWARE_WATCHDOG_PROFILE__
    ELSE
    BLX     sys_queryProfileState         ; check light weight or general cpu profiling is ON or OFF
    CMP     r0, #1
    BNE     __IrqISR_Exit1_No_Save_SwdProfile2
    ENDIF
    ; In IRQ schedule case no need to consider spsr
    ; There is no case that a preempt IRQ could call schedule
    ; Only (Rtk_RegionCount == 0) will call schedule
    MOV     r0, #RTK_MAX_TASKS
    BLX     sys_SwdCountProfileSum

    ; To separate active/positive schedule
    LDR     r0, =sys_bPreemptedSched
    MOV     r1, #1
    STRB    r1, [r0]

__IrqISR_Exit1_No_Save_SwdProfile2

    MOV     r0, #RTK_MAX_TASKS
    BLX     backtrace_ToolUpdateTaskMgr
    MOV     r0, #RTK_MAX_TASKS
    BLX     MsSysAutoCpuUpdate
    ENDIF

    MOV     r0, #RTK_SUSPENDED
    BL      Rtk11Schedule          ; call scheduler

    ; we are going back to IRQ mode to allow interrupt return
    ; so transfer back registers to IRQ stack (interrupt is safe)
    MOV     r0, sp                  ; store the SYS stack at spsr position
    ADD     sp, sp, #7*4            ; and update it before leaving
    LDR     lr, [sp], #4            ; restore lr_sys

    MOV     r1, #IRQ_DISABLE | Irq32Mode
    MSR     cpsr_cxsf, r1           ; come back to IRQ mode

    LDR     r1, [r0], #4
    MSR     spsr_cxsf, r1           ; restore spsr_irq from SYS stack

    IF :DEF:__SEPARATE_INTERRUPT_API__
    LDR     r1, =g_nSysDisableInterrupt_k        ; Change flag to resolve false alarm
    MOV     r2, #0
    STR     r2, [r1]
    ENDIF

    LDMIA   r0, {r0-r3, ip, pc}^    ; restore work registers and return
                                    ; cpsr = spsr_irq
                                    ; pc = lr_irq

;===============================================================================
;
;       FIQ assembly routine
;
;===============================================================================

__FiqISR
;-------------------------------------------------------------------------------
; FIQ prologue
;-------------------------------------------------------------------------------
    ; When a FIQ is detected the arm processor does the following actions:
    ; - lr_fiq = pc + 4 (return address + 4)
    ; - spsr_fiq = cpsr
    ; - cpsr[4:0] = 0b10001 (enter FIQ mode)
    ; - cpsr[5] = 0 (execute in ARM state)
    ; - cpsr[6] = 1 (Disable fast interrupt)
    ; - cpsr[7] = 1 (disable normal interrupts)
    ; - pc = 0x00000018 (here : __IrqISR placed by scatter file)

    ; When enter FIQ mode, spsr_fiq = cpsr and lr_fiq = pc (return address)
    SUB     lr, lr, #4              ; to return by LDMIA instruction
    STMDB   sp!, {r0-r3, ip, lr}    ; save work registers and lr_fiq
                                    ; scratched by call to handler

    IF :DEF:__RTK_DIAGNOSE_ENHANCE__
    IMPORT  Rtk_IsIrqFiqMode
    LDR     r0, =Rtk_IsIrqFiqMode
    MOV     r1, #0x11
    STR     r1, [r0]
    ENDIF

    IF :DEF:__RTK_STACK_DIAGNOSE__
    ;BL RtkStartCalQb
    ;MRS     r0, spsr
    ;AND     r0, r0, #0xF
    ;CMP     r0, #0xF                        ; if r2 is 0xf, it means spsr is usr/system mode
    ;BNE     FIQ_SYS_NO_CHECK
    ;BL __SYS_STACK_CHECK
;FIQ_SYS_NO_CHECK
    ;BL RtkStopCalQb
    ENDIF

    ; call handler and don't allow nested interrupts

;-------------------------------------------------------------------------------
; FIQ User Interrupt Service Routine (User ISR)
;-------------------------------------------------------------------------------

    IF :DEF:__RTK_STACK_DIAGNOSE__
    ;IMPORT  Corrupt_stack

    ;save info to the Corrupt_stack
    ;LDR     r3, =Corrupt_stack
    ;STR     r1, [r3, #12]           ;Store user isr address in Corrupt_stack.info
    ENDIF

; with arch 5TE
    BLX     IntcFiqHandler   ; call handler

    IF :DEF:__RTK_DIAGNOSE_ENHANCE__
    IMPORT  Rtk_IsIrqFiqMode
    LDR     r0, =Rtk_IsIrqFiqMode
    MOV     r1, #0
    STR     r1, [r0]
    ENDIF

    IF :DEF:__RTK_STACK_DIAGNOSE__
    ;BL RtkStartCalQb
    ;BL __FIQ_STACK_CHECK
    ;BL RtkStopCalQb
    ENDIF

;-------------------------------------------------------------------------------
; FIQ epilogue
;-------------------------------------------------------------------------------
    LDMIA   sp!, {r0-r3, ip, pc}^   ; restore work registers and return
                                    ; cpsr = spsr_fiq
                                    ; pc = lr_fiq


    IF :DEF:__RTK_STACK_DIAGNOSE__

    ;------------------------------------------------------------------------------
    ;Supervisor stack check
    ;Check point 1: check if SP is over top stack
    ;Check point 2: check task stack usage
    ;check point 3: check guarding pattern of top stack (0x55555555)
    ;check point 4: check guarding pattern of bottom stack (0xbeefdead)
    ;-------------------------------------------------------------------------------

__SUV_STACK_CHECK  PROC
    ;-------------------------------------------------------------------------------
    ; SUV stack check
    ;-------------------------------------------------------------------------------


    IMPORT  SupStack
    IMPORT  SupStackStart
    IMPORT  Corrupt_stack

    ;-------------------------------------------------------------------------------
    ; Step 1
    ; Check SP position
    ;-------------------------------------------------------------------------------

    ;save user isr handle to the Corrupt_stack fist (we will use it while exception occurs)
    LDR     r3, =Corrupt_stack
    STR     r2, [r3, #12]           ;Store user isr address in Corrupt_stack.info

    LDR     r0, =SupStack                       ;r0 = top of IRQ stack
    CMP     r0, r1                              ;compare with current sp

    BLT     SUV_STEP_2                          ;sp shoudl be greater than top stack

    ;exception occure
    SUB     r2, r0, r1                          ;r2 = the size we are about to print (top stack - sp)
    MOV     r0, #SP_OVERRUN                     ;r0 = exception type
    MOV     r1, sp                              ;r1 = sp
    BL       __Exception_SUV_STACK_Corrupt

SUV_STEP_2
    ;-------------------------------------------------------------------------------
    ; Step 2
    ; Check gaurding pattern of top stack
    ;-------------------------------------------------------------------------------

    LDR     r1, =0x55555555

    LDR     r2, [r0]                            ;r0 = top of IRQ stack, r2 = content of stack
    CMP     r1, r2                              ;Compare with guarding pattern (0x55555555)
    BNE     SUV_EXCEPTION

    LDR     r2, [r0, #PATTERN_CHECK_OFFSEET]!   ;check next 32bytes guarding pattern
    CMP     r1, r2
    BEQ     SUV_STEP_3

SUV_EXCEPTION
    ;exception occurs
    SUB     r1, r0, #0x4                        ;r1 = the sp point to the corrupted address                              ;r1 = the sp point to the corrupted address
    MOV     r0, #TOP_BROKEN                     ;r0 = exception type
    MOV     r2, #256                            ;r2 = dump size
    BL       __Exception_SUV_STACK_Corrupt

SUV_STEP_3

    ;-------------------------------------------------------------------------------
    ; Step 3
    ; Check gaurding pattern of bottom stack
    ;-------------------------------------------------------------------------------

    LDR     r0, =SupStackStart                 ;r0 = bottom of stack
    LDR     r1, =0xbeefdead

    SUB     r0, r0, #0x8                       ;shif to the address of guard pattern

    LDR     r2, [r0], #0x4                     ;r2 = content of stack
    CMP     r2, r1                             ;Check the content if it's 0xbeefdead
    BNE     SUV_EXCEPTION_1                    ;if not, we go to RtkExceptionRoutine

    LDR     r2, [r0]                           ;Get the content of this address
    CMP     r2, r1                             ;Check the content if it's 0xbeefdead
    BEQ     SUV_END

    ;exception occurs
SUV_EXCEPTION_1

    MOV     r1, r0                              ;r1 = the sp point to the corrupted address
    MOV     r0, #BOTTOM_BROKEN                  ;r0 = exception type
    MOV     r2, #256                            ;r2 = dump size
    BL       __Exception_SUV_STACK_Corrupt

SUV_END

    BX lr
    ENDP

    ;------------------------------------------------------------------------------
    ;FIQ stack check
    ;Check point 1: check if SP is over top stack
    ;Check point 2: check task stack usage
    ;check point 3: check guarding pattern of top stack (0x55555555)
    ;check point 4: check guarding pattern of bottom stack (0xbeefdead)
    ;-------------------------------------------------------------------------------

__FIQ_STACK_CHECK  PROC
    ;-------------------------------------------------------------------------------
    ; FIQ stack check
    ;-------------------------------------------------------------------------------


    IMPORT  FiqStack
    IMPORT  FiqStackStart

    ;-------------------------------------------------------------------------------
    ; Step 1
    ; Check SP position
    ;-------------------------------------------------------------------------------
    LDR     r0, =FiqStack                       ;r0 = top of IRQ stack
    CMP     r0, sp                              ;compare with current sp

    BLT     FIQ_STEP_2                          ;sp shoudl be greater than top stack

    ;exception occure
    ;because the FIQ stack will be re-used after going to RtkExceptionRoutine
    ;we havbe to copy the stack content to another place before branching

    LDR     r2, =IrqStackStart                  ;r2 = IRQ stack used to store FIQ stack content
    SUB     r3, r0, sp                          ;r3 = total byte to copy (top stack - sp)
    STMFD   sp!, {r3}                           ;store the dump size for later use
    MOV     r0, sp

loop_1
    LDR     r1, [r0], #0x4                      ;copy content from FIQ stack
    STR     r1, [r2], #0x4                      ;store the content

    SUBS    r3, r3, #0x4
    BGE     loop_1

    LDMFD   sp!, {r2}                           ;r2 = the size we are about to print (top stack - sp)
    MOV     r0, #SP_OVERRUN                     ;r0 = exception type
    MOV     r1, sp                              ;r1 = sp
    BL       __Exception_FIQ_STACK_Corrupt

FIQ_STEP_2
    ;-------------------------------------------------------------------------------
    ; Step 2
    ; Check gaurding pattern of top stack
    ;-------------------------------------------------------------------------------

    LDR     r1, =0x55555555

    LDR     r2, [r0]                            ;r0 = top of IRQ stack, r2 = content of stack
    CMP     r1, r2                              ;Compare with guarding pattern (0x55555555)
    BNE     FIQ_EXCEPTION

    LDR     r2, [r0, #PATTERN_CHECK_OFFSEET]!   ;check next 32bytes guarding pattern
    CMP     r1, r2
    BEQ     FIQ_STEP_3

FIQ_EXCEPTION
    ;because the FIQ stack will be re-used after going to RtkExceptionRoutine
    ;we havbe to copy the stack content to another place before branching

    LDR     r2, =IrqStackStart                  ;r2 = IRQ stack used to store FIQ stack content
    LDR     r3, =0x100                          ;r3 = total byte to copy (256bytes)
    SUB     r0, r0, #0x4
    STMFD sp!, {r0}                             ;store the corrupted address for later use

loop
    LDR     r1, [r0], #0x4                      ;copy content from FIQ stack
    STR     r1, [r2], #0x4                      ;store the content

    SUBS    r3, r3, #0x4
    BGE     loop

    LDMFD   sp!, {r1}                           ;r1 = point to the corrupted address
    MOV     r0, #TOP_BROKEN                     ;r0 = exception type
    MOV     r2, #256                            ;r2 = dump size
    BL       __Exception_FIQ_STACK_Corrupt

FIQ_STEP_3

    ;-------------------------------------------------------------------------------
    ; Step 3
    ; Check gaurding pattern of bottom stack
    ;-------------------------------------------------------------------------------

    LDR     r0, =FiqStackStart                 ;r0 = bottom of stack
    LDR     r1, =0xbeefdead

    SUB     r0, r0, #0x8                       ;shif to the address of guard pattern

    LDR     r2, [r0], #0x4                     ;r2 = content of stack
    CMP     r2, r1                             ;Check the content if it's 0xbeefdead
    BNE     FIQ_EXCEPTION_1                    ;if not, we go to RtkExceptionRoutine

    LDR     r2, [r0]                           ;Get the content of this address
    CMP     r2, r1                             ;Check the content if it's 0xbeefdead
    BEQ     FIQ_END

    ;exception occurs
FIQ_EXCEPTION_1

    MOV     r1, r0                              ;r1 = the sp point to the corrupted address
    MOV     r0, #BOTTOM_BROKEN                  ;r0 = exception type
    MOV     r2, #256                            ;r2 = dump size

    BL       __Exception_FIQ_STACK_Corrupt

FIQ_END

    BX lr
    ENDP

   ;------------------------------------------------------------------------------
    ;IRQ stack check
    ;Check point 1: check if SP is over top stack
    ;Check point 2: check task stack usage
    ;check point 3: check guarding pattern of top stack (0x55555555)
    ;check point 4: check guarding pattern of bottom stack (0xbeefdead)
    ;-------------------------------------------------------------------------------

__IRQ_STACK_CHECK  PROC
    ;-------------------------------------------------------------------------------
    ; IRQ stack check
    ;-------------------------------------------------------------------------------

    IMPORT  IrqStack
    IMPORT  IrqStackStart

    ;-------------------------------------------------------------------------------
    ; Step 1
    ; Check SP position
    ;-------------------------------------------------------------------------------
    LDR     r0, =IrqStack                       ;r0 = top of IRQ stack
    CMP     r0, sp                              ;compare with current sp

    BLT     IRQ_STEP_2                          ;sp shoudl be greater than top stack

    ;exception occure
    SUB     r2, r0, sp                          ;r2 = the size we are about to print (top stack - sp)
    MOV     r0, #SP_OVERRUN                     ;r0 = exception type
    MOV     r1, sp                              ;r1 = sp
    BL       __Exception_IRQ_STACK_Corrupt

IRQ_STEP_2
    ;-------------------------------------------------------------------------------
    ; Step 2
    ; Check gaurding pattern of top stack
    ;-------------------------------------------------------------------------------

    LDR     r1, =0x55555555

    LDR     r2, [r0]                            ;r0 = top of IRQ stack, r2 = content of stack
    CMP     r1, r2                              ;Compare with guarding pattern (0x55555555)
    BNE     IRQ_EXCEPTION

    LDR     r2, [r0, #PATTERN_CHECK_OFFSEET]!   ;check next 32bytes guarding pattern
    CMP     r1, r2
    BEQ     IRQ_STEP_3

IRQ_EXCEPTION
    ;exception occurs
    SUB     r1, r0, #0x4                        ;r1 = the sp point to the corrupted address                              ;r1 = the sp point to the corrupted address
    MOV     r0, #TOP_BROKEN                     ;r0 = exception type
    MOV     r2, #256                            ;r2 = dump size
    BL       __Exception_IRQ_STACK_Corrupt

IRQ_STEP_3

    ;-------------------------------------------------------------------------------
    ; Step 3
    ; Check gaurding pattern of bottom stack
    ;-------------------------------------------------------------------------------

    LDR     r0, =IrqStackStart                 ;r0 = bottom of stack
    LDR     r1, =0xbeefdead

    SUB     r0, r0, #0x8                       ;shif to the address of guard pattern

    LDR     r2, [r0], #0x4                     ;r2 = content of stack
    CMP     r2, r1                             ;Check the content if it's 0xbeefdead
    BNE     IRQ_EXCEPTION_2                    ;if not, we go to __Exception_IRQ_STACK_Corrupt

    LDR     r2, [r0]                           ;Get the content of this address
    CMP     r2, r1                             ;Check the content if it's 0xbeefdead
    BEQ     IQR_END

    ;exception occurs
IRQ_EXCEPTION_2
    MOV     r1, r0                              ;r1 = the sp point to the corrupted address
    MOV     r0, #BOTTOM_BROKEN                  ;r0 = exception type
    MOV     r2, #256                            ;r2 = dump size
    BL      __Exception_IRQ_STACK_Corrupt

IQR_END

    BX lr                                       ;go back to ISR

    ENDP

    ;------------------------------------------------------------------------------
    ;SYS stack check
    ;Check point 1: check guarding pattern of top stack (0x55555555)
    ;Check point 2: check if SP is over top stack
    ;check point 3: check task stack usage
    ;check point 4: check guarding pattern of bottom stack (0xbeefdead)
    ;-------------------------------------------------------------------------------

__SYS_STACK_CHECK  PROC

    IMPORT Rtk_PtrCurrentTask
    IMPORT Rtk_CurrentTask

    ;-------------------------------------------------------------------------------
    ; check guard pattern at top of stack
    ;-------------------------------------------------------------------------------

    LDR     r0, =Rtk_PtrCurrentTask		;@Rtk_PtrCurrentTask
    LDR     r3, [r0]                            ;r3 = Rtk_PtrCurrentTask
    ADD     r0,  r3, #CURRENT_STACK_TOP_OFF     ;offset to TopOfStack
    LDR     r0, [r0]			        ;r0 = address of Top stack

    LDR     r2, =0x55555555                     ;pattern value

    LDR     r1, [r0]                            ;r1 = the content of stack
    CMP     r1, r2                              ;Compare with 0x55555555

    BNE     task_sp_check

    LDR     r1, [r0, #PATTERN_CHECK_OFFSEET]!
    CMP     r1, r2

    BEQ     task_continue

task_sp_check

    SUB     r0, r0, #0x4
    STMFD   sp!, {r0}                             ;save the broken position

    ;-------------------------------------------------------------------------------
    ; If guard pattern is broken, check if sp is over the top
    ;-------------------------------------------------------------------------------
    ;ADD     r0,  r3, #CURRENT_STACK_TOP_OFF     ;offset to TopOfStack
    ;LDR     r0, [r0]			        ;r0 = address of Top stack

    ;check if it's marker call, if yes, ignore the sp check
    ADD     r1, r3, #CURRENT_MARKED_OFFSET
    LDR     r1, [r1]                            ;r1 = value of Marked
    AND     r1, r1, #0x000000FF                 ;we only take lease significant byte
    CMP     r1, #1
    BEQ     task_exception

    ;STMFD sp!, {r13}^
    ;LDMFD sp!, {r1}                              ;r1 = sp of sys/user mode
    SUB     ip, sp, #4
    STMIA   ip, {sp}^
    ADD     r0,  r3, #CURRENT_STACK_TOP_OFF     ;offset to TopOfStack
    LDR     r0, [r0]			                ;r0 = address of Top stack
    LDMIA   ip, {r1}                              ;r1 = sp of sys/user mode

    CMP     r0, r1                               ;r0 = address of top stack
    BLT     task_exception                       ;SP is not over top

    LDMFD sp!, {r2}                              ;just pop the broken positino we store, the value is useless
    SUB     r2, r0, r1                           ;r2 = the size we are about o print (top stack - sp)
    MOV     r0, #SP_OVERRUN                      ;r0 = exception type
                                                 ;r1 = sp (already save in r1)
    BL       __Exception_SYS_STACK_Corrupt       ;branch to __Exception_SYS_STACK_Corrupt

task_exception
    ;exception occurs
    ;prepare information for backtrace
    LDMFD   sp!, {r1}                           ;r1 = the point to the corrupted address
    MOV     r2, #256                            ;r2 = the size we are about to print
    MOV     r0, #TOP_BROKEN                     ;r0 = exception type
    BL       __Exception_SYS_STACK_Corrupt      ;branch to __Exception_SYS_STACK_Corrupt

task_continue

    BX lr                                       ;jump back to ISR

    ENDP

  IMPORT Corrupt_stack
  IMPORT Rtk_IrqFiqException
  IMPORT RtkExceptionRoutine

__Exception_IRQ_STACK_Corrupt

    ;save info to the global var Corrupt_stack
    LDR     r3, =Corrupt_stack
    STR     r0, [r3], #4         ;r0 = exception type
    STR     r1, [r3], #4         ;r1 = the sp point to the corrupted address
    STR     r2, [r3]             ;r2 = the size we are about to print

    ;save Rtk_IrqFiqException as IRQ interrupt type
    LDR     r0, =Rtk_IrqFiqException
    MOV     r1, #0xFD
    STR     r1, [r0]

    ;r0 = the exception type, as 1st parameter
    MOV     r0, #ISR_STACK_CORRUPT

    ;r1 = current task id, as 2nd parameter
    LDR     r1, =Rtk_CurrentTask                ;second parameter: current task id
    LDR     r1, [r1]
    AND     r1, r1, #0x000000FF                 ;we only take lease significant byte

    BLX       RtkExceptionRoutine

__Exception_SUV_STACK_Corrupt

    ;save info to the global var Corrupt_stack
    LDR     r3, =Corrupt_stack
    STR     r0, [r3], #4
    STR     r1, [r3], #4
    STR     r2, [r3]

    ;save Rtk_IrqFiqException as IRQ interrupt type
    LDR     r0, =Rtk_IrqFiqException
    MOV     r1, #0xFD
    STR     r1, [r0]

    ;r0 = the exception type, as 1st parameter
    MOV     r0, #SUV_STACK_CORRUPT

    ;r1 = current task id, as 2nd parameter
    LDR     r1, =Rtk_CurrentTask                ;second parameter: current task id
    LDR     r1, [r1]
    AND     r1, r1, #0x000000FF                 ;we only take lease significant byte

    BLX       RtkExceptionRoutine

__Exception_FIQ_STACK_Corrupt

    ;save info to the global var Corrupt_stack
    LDR     r3, =Corrupt_stack
    STR     r0, [r3], #4
    STR     r1, [r3], #4
    STR     r2, [r3]

    ;save Rtk_IrqFiqException as FIQ interrupt type
    LDR     r0, =Rtk_IrqFiqException
    MOV     r1, #0xFC
    STR     r1, [r0]

    ;r0 = the exception type, as 1st parameter
    MOV     r0, #FIQ_STACK_CORRUPT

    ;r1 = current task id, as 2nd parameter
    LDR     r1, =Rtk_CurrentTask                ;second parameter: current task id
    LDR     r1, [r1]
    AND     r1, r1, #0x000000FF                 ;we only take lease significant byte

    BLX       RtkExceptionRoutine


__Exception_SYS_STACK_Corrupt

    ;save info to the global var Corrupt_stack
    LDR     r3, =Corrupt_stack
    STR     r0, [r3], #4
    STR     r1, [r3], #4
    STR     r2, [r3], #4
    ;check if we in FIQ or IRQ mode
    MRS     r1, cpsr
    AND     r1, r1, #0xF
    CMP     r1, #0x2
    BEQ     _IRQ_MODE

    LDR     r2, [sp, #20]      ;FIQ mode, r2 = lr
    MOV     r1, #0xFC          ;Rtk_IrqFiqException = 0xFD
    B       _FINAL

_IRQ_MODE
    LDR     r2, [sp, #24]      ;IRQ mode, r2 = lr
    MOV     r1, #0xFD          ;Rtk_IrqFiqException = 0xFD

_FINAL
    STR     r2, [r3]

    ;save Rtk_IsIrqFiqMode as IRQ interrupt type
    LDR     r0, =Rtk_IrqFiqException
    STR     r1, [r0]

    ;r0 = the exception type, as 1st parameter
    MOV     r0, #TASK_STACK_CORRUPT

    ;r1 = current task id, as 2nd parameter
    LDR     r1, =Rtk_CurrentTask                ;second parameter: current task id
    LDR     r1, [r1]
    AND     r1, r1, #0x000000FF                 ;we only take lease significant byte

    BLX       RtkExceptionRoutine

    ENDIF

     END