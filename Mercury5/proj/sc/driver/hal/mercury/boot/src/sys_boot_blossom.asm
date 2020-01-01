        INCLUDE kernel_b3.i
        INCLUDE sys_scf.i

        PRESERVE8

        AREA |BootPatch|, READONLY
        EXPORT PatchArry
PatchArry   & 0x34000400, 0x34000400, 0x34000400, 0x34000400

; -----------------------------------------------------------------------------
;                               Stacks
; -----------------------------------------------------------------------------

IRQ_STACK_SIZE  EQU       1024
FIQ_STACK_SIZE  EQU       512 ;with dedi exc stack, no need to enlarge
;SUP_STACK_SIZE  EQU       1024 ;Enlarge SUP_STACK_SIZE because of moving HAC back to ISR
SUP_STACK_SIZE  EQU       3000
ABT_STACK_SIZE  EQU       512
BOOT_STACK_SIZE    EQU     700
UNDEF_STACK_SIZE   EQU     256
BACKTRACE_STACK_SIZE   EQU     2048

        AREA |AAA_Stacks|, DATA, NOINIT

        EXPORT FiqStack
        EXPORT FiqStackStart
        EXPORT IrqStack
        EXPORT IrqStackStart
        EXPORT SupStack
        EXPORT SupStackStart
        EXPORT AbtStack
        EXPORT AbtStackStart
        EXPORT UndefStack
        EXPORT UndefStackStart
        EXPORT BacktraceStack
        EXPORT BacktraceStackStart
        EXPORT BootStack
        EXPORT BootStackStart
        EXPORT EndOfITStacks
        ;EXPORT IRAM_STACK


FiqStack        %       FIQ_STACK_SIZE
FiqStackStart   %       0
IrqStack        %       IRQ_STACK_SIZE
IrqStackStart   %       0
AbtStack        %       ABT_STACK_SIZE
AbtStackStart   %       0
UndefStack      %       UNDEF_STACK_SIZE
UndefStackStart %       0
BacktraceStack     %    BACKTRACE_STACK_SIZE
BacktraceStackStart %   0
BootStack       %       BOOT_STACK_SIZE
BootStackStart  %       0
EndOfITStacks   %       0

; To accelerate FINT execution by avoiding accessing memory via EMI
        AREA |SUP_Stacks|, DATA, NOINIT
SupStack        %       SUP_STACK_SIZE
SupStackStart   %       0


; -----------------------------------------------------------------------------
;                       TTB
; -----------------------------------------------------------------------------
; reserve 4096 words for level 1 translation table (16 KB)
; aligned on 16 KB boundary

        AREA |TTB|, DATA, NOINIT

;ttb_level1      %       0x4000

; -----------------------------------------------------------------------------
;                       Arm Vectors
; -----------------------------------------------------------------------------
        AREA |AAA_vectors|, CODE, READONLY

        CODE32
        ALIGN

        IMPORT __Undef
        IMPORT __SoftInt
        IMPORT __AbortPrefetch
        IMPORT __AbortData
        IMPORT __IrqISR
        IMPORT __FiqISR

AAA_Begin
        B       __ResetVector
        LDR       pc,=__Undef
        LDR       pc,=__SoftInt
        LDR       pc,=__AbortPrefetch
        LDR       pc,=__AbortData
        DCD     0
        LDR       pc,=__IrqISR
        LDR       pc,=__FiqISR
        EXPORT SPI_RST_CMD
SPI_RST_CMD   & 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
__ResetVector
        B       __BootEntry

   ALIGN

; -----------------------------------------------------------------------------
;                       Startup code
; -----------------------------------------------------------------------------
   AREA |init|, CODE, READONLY

   EXPORT   __BootEntry

   ENTRY

__BootEntry                      ; Main Entry Point

        ; Enable ICache
        MRC p15, 0, r0, c1, c0, 0 ;r0 = current status
        MOV r1, #1
        LSL r1, r1, #12
        ORR r0, r0, r1
        MCR p15, 0, r0, c1, c0, 0

    IMPORT  Rtk_CurrentTask
        IF :DEF:__I_SW__
    IMPORT  limitRAMsSize
        ELSE
    IMPORT  sys_PhyRAMSize
    IMPORT  ||Image$$XRAM$$Base||
        ENDIF

; -----------------------------------------------------------------------------
; Force core into known state
; -----------------------------------------------------------------------------

sys_CleanBoot

        ; Turn on Alignment Fault (Because B3 ROM code turn on)
        MRC p15, 0, r0, c1, c0, 0
        ;ORR r0, r0, #0x02
        ; Turn off
        AND r0, r0, #0xFFFFFFFD
        MCR p15, 0, r0, c1, c0, 0

        IF :DEF:__NOR_BOOT__
        ; Reset bigblue:
        ; reg_bbtop_rst0_ow = 0
        ; reg_bbtop_rst1_ow = 1
        ; reg_bbtop_rst2_ow = 1
        LDR     r0,=0x740064C0
        LDR     r1,=0x6
        STR     r1, [r0]

        ; Reset padmux and gpio control:
        ; reg_pad_rst0_ow = 0 (padmux, no reset)
        ; reg_pad_rst1_ow = 1 (gpio, reset)
        LDR     r0,=0x740064C4
        LDR     r1,=0x2
        STR     r1, [r0]

        ;in case of HW WDT, need to reset MCP BCR in very begining
        LDR     r0, =IRAM_STACK
        STR     sp, [r0]; store current SP
        STR     lr, [r0, #4]; store current LR
        BL      Boot_Entry_EMI ; init MCP BCR

        LDR     r0, =IRAM_STACK
        LDR     sp, [r0]             ;restore SP
        LDR     lr, [r0, #4]         ;restore LR
        ELSE
        ; Reset padmux
        ; reg_pad_rst0_ow = 0 (padmux, no reset)
        LDR     r0,=0x740064C4
        LDR	r1, [r0,#0]
        BIC     r1, r1, #0x1; clear bit 0
        STR     r1, [r0]
        ENDIF
    IF :DEF:__BRANCH_To_ZERO__
    ; backup ARM register for checking
    IMPORT  bzBacktrace
;   CMP sp, #0x08000000
;   BLE __BootEntry_after_store_debug_info
;   STMDB   sp!, {r0}
    LDR r0, =bzBacktrace
    STMIA   r0!, {r1-r12, sp, lr}
    MRS r1, cpsr
    MRS r2, spsr
    STMIA   r0!, {r1, r2}
    LDR     r1, =Rtk_CurrentTask
    LDRB    r1, [r1]
    STMIA   r0!, {r1}
;   LDMIA   sp!, {r0}
;   STMIA   r0!, {r1}

    ; check if SP is larger than 0x10400000 (DRAM upper boundary)
        IF :DEF:__I_SW__
    LDR     r1, =||Image$$XRAM$$Base||
    LDR r2, =limitRAMsSize
    LDR r2, [r2]
    ADD     r2, r2, r1
        ELSE
    LDR r2, =sys_PhyRAMSize
    LDR r2, [r2]
    IF :DEF:__NOR_BOOT__
    LDR r1, =||Image$$XRAM$$Base||
    LDR r1, [r1]
    ADD     r2, r2, r1                    ;usable ram base + usable ram size
    ENDIF
    LDR     r1, =||Image$$XRAM$$Base||
        ENDIF ;__I_SW__

    SUB     r2, r2, #200
    SUB     r2, r2, #200
    SUB     r2, r2, #200
    CMP     sp, r2
    BLE     __BootEntry_check_if_need_to_reset_SP_1
    ; set SP as 0x10000000 as default value
    MOV     sp, r1
    B       __BootEntry_check_if_need_to_reset_SP_2

__BootEntry_check_if_need_to_reset_SP_1
    ; check if SP is smaller than 0x10000000 (DRAM lower boundary)
    CMP     sp, r1
    BGE     __BootEntry_check_if_need_to_reset_SP_2
    ; set SP as 0x10000000 as default value
    MOV     sp, r1

__BootEntry_check_if_need_to_reset_SP_2
    MOV     r1, #1
    LSL     r1, r1, #7

__BootEntry_backup_stack
        LDR     r2, [sp], #4
    STR     r2, [r0], #4
    SUB     r1, r1, #1
    CMP     r1, #0
    BNE     __BootEntry_backup_stack


    ; unlock internal RAM for initial setting
__BootEntry_after_store_debug_info
    IMPORT  g_ptW5SysReg
    LDR r0, =g_ptW5SysReg
    LDR r0, [r0]
    LDR r1, [r0, #12]
    ORR r1, #0x300000
    STR r1, [r0, #12]

    B   __BootEntry_normal

    ELSE ; !__BRANCH_To_ZERO__
    ; store the current Task status in IRAM_STACK
    LDR     r0, =IRAM_STACK   ; save sp in Rtk_CurrentTaskStackDump.sp
    SUB     r0, r0, #564
    LDR     r1, =Rtk_CurrentTask   ; save sp in Rtk_CurrentTaskStackDump.sp
    LDRB    r1, [r1]
    STR     r1, [r0], #4
    STR     sp, [r0], #4

    MRS     r1, cpsr                        ; store user mode cpsr in r2
    STMIA   r0!, {r1, r4-r12, lr}           ; save registers in Rtk_CurrentTaskStackDump.reg

    ; check if SP is larger than 0x10400000 (DRAM upper boundary)
        IF :DEF:__I_SW__
    LDR     r1, =||Image$$XRAM$$Base||
    LDR r2, =limitRAMsSize
    LDR r2, [r2]
    ADD     r2, r2, r1
        ELSE
    LDR r2, =sys_PhyRAMSize
    LDR r2, [r2]
    IF :DEF:__NOR_BOOT__
    LDR r1, =||Image$$XRAM$$Base||
    LDR r1, [r1]
    ADD     r2, r2, r1                    ;usable ram base + usable ram size
    ENDIF
    LDR     r1, =||Image$$XRAM$$Base||
        ENDIF

    SUB     r2, r2, #200
    SUB     r2, r2, #200
    SUB     r2, r2, #200
    CMP     sp, r2
    BLE     __BootEntry_noreset_sp_1
    ; set SP as 0x10000000 as default value
    MOV     sp, r1
    B       __BootEntry_noreset_sp_2

__BootEntry_noreset_sp_1
    ; check if SP is smaller than 0x10000000 (DRAM lower boundary)
    CMP     sp, r1
    BGE     __BootEntry_noreset_sp_2
    ; set SP as 0x10000000 as default value
    MOV     sp, r1

__BootEntry_noreset_sp_2
    MOV     r1, #1
    LSL     r1, r1, #7

__BootEntry_loop_store
        LDR     r2, [sp], #4
    STR     r2, [r0], #4
    SUB     r1, r1, #1
    CMP     r1, #0
    BNE     __BootEntry_loop_store
    ENDIF

__BootEntry_normal
    IF :DEF:__RTK_DIAGNOSE_ENHANCE__
    IMPORT  Rtk_IsIrqFiqMode
    LDR     r0, =Rtk_IsIrqFiqMode
    MOV r1, #0
    STR r1, [r0]
    ENDIF

_Keep_SYS_LR_SP
	IMPORT SysWdtModeInfo;
	IMPORT Rtk_RegionCount;
	LDR	R0, =Rtk_RegionCount
	LDRH	R0, [R0]
	LDR	R1, =SysWdtModeInfo
	STR	R0, [R1]
        ; Set mode Sys32
	MOV     r0, #INT_DISABLE | Sys32Mode
	MSR     cpsr_cxsf, r0
	STR	SP, [R1, #4]
	STR	LR, [R1, #8]
        ; Set mode Irq32
	MOV     r0, #INT_DISABLE | Irq32Mode
	MSR     cpsr_cxsf, r0
	STR	SP, [R1, #12]
	STR	LR, [R1, #16]

        ; disable irq and fiq
        MOV   r0, #INT_DISABLE | Sup32Mode
        MSR   cpsr_cxsf, r0
        ; Disable MPU
        MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
        BIC     r0, r0, #0x1                ; clear bit 0
        MCR     p15, 0, r0, c1, c0, 0       ; write value back
        ; Drain the write buffer
        MOV     r0, #0x0
        MCR     p15, 0, r0, c7, c10, 4
        ; Flush I and D Cache
        MOV     r0, #0x0
        MCR     p15, 0, r0, c7, c7, 0
        ; Flush the TLB
        MOV     r0, #0x0
        MCR     p15, 0, r0, c8, c7, 0

; -----------------------------------------------------------------------------
; Branch to main
; -----------------------------------------------------------------------------
        ; Initialisations are done
        ; in C language routines
        ;LDR sp, =IRAM_STACK
        ;SUB sp, sp, #564

        ; change boot stack from IRAM_STACK to imi2 heap end sine IRAM_STACK will cause
        ; the contents of execution region IRAM_SECTION_ZI to be corrupted at run-time.
;;IF :DEF:__FIXME__
        ;IMPORT  sys_get_imi2_end_address
        ;BL sys_get_imi2_end_address;
        ;BIC r0, r0, #0x3
        ;SUB r0, r0, #0x400
        ;MOV sp, r0
;;ENDIF
        IMPORT  sys_premain_first
        BL  sys_premain_first ; init pll and emi



_MainEntry
        IMPORT __main

                ; resrve for measuring  time
                ;IMPORT DrvTimerStdaTimerGetTick
                ;BL DrvTimerStdaTimerGetTick
                ;push {r0}

        B      __main

; -----------------------------------------------------------------------------
; __rt_entry : Stacks initialisation. Called by __main
; -----------------------------------------------------------------------------
          EXPORT __rt_entry
__rt_entry


                ;BL __rt_entry

        ;IF :DEF:__BOOT_UNCOMPRESS__

        IMPORT _do_decompress
        IMPORT mmu_translation_table_reset_for_decompression
        IMPORT __enable_mmu_wrapper
        IMPORT __disable_mmu_wrapper


        ; we set emi clock to 156MHZ to speedup memory access
        IF :DEF:__FIXME__
        IMPORT HalEmiSetSmcClockInBootup
        BL HalEmiSetSmcClockInBootup
        ENDIF


                ; resrve for measuring  time
                ;IMPORT time_measure
                ;pop {r0}
                ;MOV r1, #1
                ;BL time_measure
                ;push {r0}  ; push result 1 to stack

        ; set mmu 1st table
        BL mmu_translation_table_reset_for_decompression
        ; enable mmu
        MOV r0, #0
        BL __enable_mmu_wrapper


                ; resrve for measuring  time
                ;BL DrvTimerStdaTimerGetTick
                ;push {r0}

        ; do decompress
        BL	_do_decompress


                ; resrve for measuring  time
                ;pop {r0, r2}  ; pop result 1 from stack, and set to real result 1
                ;MOV r1, #2
                ;BL time_measure


        ; disable mmu then enable ICache
        BL __disable_mmu_wrapper
        MRC p15, 0, r0, c1, c0, 0 ;r0 = current status
        MOV r1, #1
        LSL r1, r1, #12
        ORR r0, r0, r1
        MCR p15, 0, r0, c1, c0, 0

        ;ENDIF


        IF :DEF:__RTK_STACK_DIAGNOSE__

        ; Stack initialization with a pattern
        LDR     r0, =FiqStack
        LDR     r1, =BootStackStart
        LDR     r2,=0x55555555
        CMP     r0, r1
        BEQ     StackInitEnd_STACK_DIAGNOSE
StackInitLoop_STACK_DIAGNOSE
        STR     r2, [r0], #4
        CMP     r0, r1
        BCC     StackInitLoop_STACK_DIAGNOSE
StackInitEnd_STACK_DIAGNOSE

        ; For sup stack change position
        LDR     r0, =SupStack
        LDR     r1, =SupStackStart
        LDR     r2, =0x55555555
        CMP     r0, r1
        BEQ     StackInitEnd_STACK_DIAGNOSE2
StackInitLoop_STACK_DIAGNOSE2
        STR     r2, [r0], #4
        CMP     r0, r1
        BCC     StackInitLoop_STACK_DIAGNOSE2
StackInitEnd_STACK_DIAGNOSE2

        ;guard pattern
        LDR     r2,=0xbeefdead

        ; Set stack for SVC
        LDR     r0, =SupStackStart
        SUB     r0, r0, #0x8
        MOV     sp, r0
        STR     r2, [r0]
        STR     r2, [r0, #0x4]
        ;LDR     sp, =SupStackStart

        ; Set mode Fiq32 and set stack
        MOV     r0, #INT_DISABLE | Fiq32Mode
        MSR     cpsr_cxsf, r0
        LDR     r0, =FiqStackStart
        SUB     r0, r0, #0x8
        MOV     sp, r0
        STR     r2, [r0]
        STR     r2, [r0, #0x4]
        ;LDR     sp, =FiqStackStart

        ; Set mode Irq32 and set stack
        MOV     r0, #INT_DISABLE | Irq32Mode
        MSR     cpsr_cxsf, r0
        LDR     r0, =IrqStackStart
        SUB     r0, r0, #0x8
        MOV     sp, r0
        STR     r2, [r0]
        STR     r2, [r0, #0x4]
        ;LDR     sp, =IrqStackStart

        ; Set mode abort32 and set stack
        MOV     r0, #INT_DISABLE | Abt32Mode
        MSR     cpsr_cxsf, r0
        LDR     r0, =AbtStackStart
        SUB     r0, r0, #0x8
        MOV     sp, r0
        STR     r2, [r0]
        STR     r2, [r0, #0x4]
        ;LDR     sp, =AbtStackStart

        ; Set mode undef32 and set stack
        MOV     r0, #INT_DISABLE | Und32Mode
        MSR     cpsr_cxsf, r0
        LDR     r0, =UndefStackStart
        SUB     r0, r0, #0x8
        MOV     sp, r0
        STR     r2, [r0]
        STR     r2, [r0, #0x4]
        ;LDR     sp, =UndefStackStart

        ; Set mode Sys32 and set stack (it also sets user stack)
        MOV     r0, #INT_DISABLE | Sys32Mode
        MSR     cpsr_cxsf, r0
        LDR     r0, =BootStackStart
        SUB     r0, r0, #0x8
        MOV     sp, r0
        STR     r2, [r0]
        STR     r2, [r0, #0x4]
        ;LDR     sp, =BootStackStart
        ELSE
        ; Set stack for SVC
        LDR     sp, =SupStackStart

        ; Set mode Fiq32 and set stack
        MOV     r0, #INT_DISABLE | Fiq32Mode
        MSR     cpsr_cxsf, r0
        LDR     sp, =FiqStackStart

        ; Set mode Irq32 and set stack
        MOV     r0, #INT_DISABLE | Irq32Mode
        MSR     cpsr_cxsf, r0
        LDR     sp, =IrqStackStart

        ; Set mode abort32 and set stack
        MOV     r0, #INT_DISABLE | Abt32Mode
        MSR     cpsr_cxsf, r0
        LDR     sp, =AbtStackStart

        ; Set mode undef32 and set stack
        MOV     r0, #INT_DISABLE | Und32Mode
        MSR     cpsr_cxsf, r0
        LDR     sp, =UndefStackStart

        ; Set mode Sys32 and set stack (it also sets user stack)
        MOV     r0, #INT_DISABLE | Sys32Mode
        MSR     cpsr_cxsf, r0
        LDR     sp, =BootStackStart

        ; Stack initialization with a pattern
        LDR     r0, =FiqStack
        LDR     r1, =BootStackStart
        LDR     r2,=0x55555555
        CMP     r0, r1
        BEQ     StackInitEnd
StackInitLoop
        STR     r2, [r0], #4
        CMP     r0, r1
        BCC     StackInitLoop
StackInitEnd
        ENDIF


        IMPORT  sys_premain_second
        B   sys_premain_second ; sys_premain calls main

	IF :DEF:__NOR_BOOT__
SYS_TIMER_REG EQU  0x34002c00
SYS_TIMER_WATCHDOG_0_OFF EQU 0x0c
SYS_TIMER_WATCHDOG_1_OFF EQU 0x10
SYS_TIMER_WATCHDOG_TIMEOUT_FLAG_OFF EQU 20

  EXPORT Boot_Entry_EMI
Boot_Entry_EMI
        LDR     r0,=SYS_TIMER_REG
        LDR     r0, [r0, #SYS_TIMER_WATCHDOG_0_OFF]
        TST     r0, #1:SHL:SYS_TIMER_WATCHDOG_TIMEOUT_FLAG_OFF ;(g_ptW5SysTimer->u32_WatchDog0Control & SYSTIMER_WDOG_TIMEOUT) !=0
        ;if bit[20]=1 ==> alu_out =1 ==> z=0
        BNE     Boot_Entry_EMI_reset ;
        ;if bit[20]=0 ==> alu_out =0 ==> z=1
        LDR     r0,=SYS_TIMER_REG
        LDR     r0, [r0, #SYS_TIMER_WATCHDOG_1_OFF]
        TST     r0, #1:SHL:SYS_TIMER_WATCHDOG_TIMEOUT_FLAG_OFF ;(g_ptW5SysTimer->u32_WatchDog1Control & SYSTIMER_WDOG_TIMEOUT) !=0
        ;if bit[20]=1 ==> alu_out =1 ==> z=0
        BNE     Boot_Entry_EMI_reset ;
        BX      lr
Boot_Entry_EMI_reset
        LDR     r0,=0x74002458
        LDR     r1,=0x0100
        STR     r1, [r0]         ; Use Fix DMC Clk
        ;Added to turn off RAM BURST/PAGE mode
        LDR     r0,=0x74002808
        LDR     r1,=0xE51F
        STR     r1, [r0]
        LDR     r0,=0x7400280C
        LDR     r1,=0x1008
        STR     r1, [r0]
        LDR     r0,=0x7400281C
        LDR     r1,=0x3
        STR     r1, [r0]
        LDR     r0,=0x74002818
        LDR     r1,=0x1
        STR     r1, [r0]
        BX      lr
	ENDIF

; -----------------------------------------------------------------------------
; Store ARM Registers
; This functions store in adress pointed by r0 the content of R3->r14 + CPSR
; for debug purpose, in case of unexpected watchdog reset
; -----------------------------------------------------------------------------
  EXPORT StoreARMRegisters
StoreARMRegisters
        STR   r1, [sp, #-4]!                  ; save registers mofified
    ; Store registers.
    STMIA   r0!, {r3-r14} ; copy R3 to R14 at the address specified by r0, and increment R0
    MRS     r1, cpsr
    STR     r1, [r0] ; save CPSR after R14
        LDR   r1, [sp], #4                    ; restore registers saved
        BX    lr
IF :DEF:__I_SW__
 EXPORT SpiTest
SpiTest
     LDR   r0, =0x14000014
     LDMIA r0!, {r1-r8}
ENDIF
; -----------------------------------------------------------------------------
; Get register for back stack analysis.
; -----------------------------------------------------------------------------
        EXPORT KeGetRegister
        IMPORT RtkRegisters
KeGetRegister
        LDR     r0, =RtkRegisters
        STMIA   r0, {r11-r14}
        BX      lr
   CODE32
   ALIGN

; Useful variable
    IMPORT ||Image$$XRAM$$Base||

    export __XRAM_Base
__XRAM_Base
    DCD ||Image$$XRAM$$Base||

;/****************************************************************************/
;/* GLOBAL VARIABLES                                                         */
;/****************************************************************************/
        AREA |STATICBOOT|, DATA, NOINIT

        ; Size of the available RAM
        EXPORT sys_ResetPattern
        EXPORT sys_RAMSize
        IF :DEF:__I_SW__
        ELSE
        EXPORT limitRAMsSize
        ENDIF
sys_ResetPattern     DCD 0
sys_RAMSize          DCD 0
        IF :DEF:__I_SW__
        ELSE
limitRAMsSize        DCD 0
        ENDIF
        END
