    INCLUDE kernel_b2.i

    IF :DEF:__ARM_POWER_OFF__
    ; peterwei test for ARM9 power down
    EXPORT sys_Arm9PowerDown
    EXPORT sys_Arm9WakeUp
    EXPORT SYS_ARM9IMIBOOT

    IMPORT g_ptW5SysTimer
    IMPORT g_ptW5TbuC
    IMPORT arm_sleep_data
    IMPORT Arm9AfterPowerDownQbCnt
    IMPORT armSleepDataChkSum
    IMPORT sys_inSleepMode
    IMPORT sys_wakeUpFromReset
    IMPORT sys_CleanBoot
    IMPORT sys_EnterSleepValue
    IMPORT sys_LeaveSleepCount  
    IMPORT sys_LeaveSleepStep

    ENDIF
    IMPORT g_ptW5IrqControl

    IF :DEF:__I_SW__
    IMPORT hwll1_ReduceLastFrame
    IMPORT hwll1_SleepLastCheck
    IMPORT sys_EnterARMRestore
    IMPORT sys_LeaveARMRestore
    IMPORT sys_EnterArm9Wakeup
    IMPORT sys_LeaveWakeupImme
    IMPORT sys_EnterSleepCount
    ENDIF

    IF :DEF:__NAND__
    IF :DEF:__I_SW__
    IMPORT _gPadConfigTbl
    ENDIF
    ELSE
    ;IF :DEF:__EMI_PAD_PWD__
    IMPORT _gPadConfigTbl
    ;ENDIF
    ENDIF

DMC_REG     EQU  0x74002400
BA_SYSREG   EQU  0x34000400
IMI1_ADDR   EQU  0X08000000
MEM0_ADDR   EQU  0X0C000000
MEM0_DATA   EQU  0XEA000006
COMMON_ADDR EQU  0X00000000

    IF :DEF:__ARM_POWER_OFF__
; peterwei test for ARM9 power down
WORD_SIZE                       EQU     (4)

; MMU constants
MMU_CTL_MASK                    EQU     (0x3FFF0000)
MMU_TTB_MASK                    EQU     (0x00003FFF)
MMU_ID_MASK                     EQU     (0xFFFFFFF0)

; General CPU constants
;Mode_FIQ                        EQU      (0x11)
;Mode_IRQ                        EQU      (0x12)
;Mode_SVC                        EQU      (0x13)
Mode_ABT                        EQU      (0x17)
Mode_UND                        EQU      (0x1B)
Mode_SYS                        EQU      (0x1F)
;I_Bit                           EQU      (0x80)
;F_Bit                           EQU      (0x40)

SleepState_Data_Start		    EQU     (0)

SleepState_WakeAddr    		    EQU     (SleepState_Data_Start		    )
SleepState_MMUCTL               EQU     (SleepState_WakeAddr    + WORD_SIZE )
SleepState_MMUTTB       	    EQU     (SleepState_MMUCTL  	+ WORD_SIZE )
SleepState_MMUDOMAIN    	    EQU     (SleepState_MMUTTB  	+ WORD_SIZE )
SleepState_SVC_SP       	    EQU     (SleepState_MMUDOMAIN   + WORD_SIZE )
SleepState_SVC_SPSR     	    EQU     (SleepState_SVC_SP  	+ WORD_SIZE )
SleepState_FIQ_SPSR     	    EQU     (SleepState_SVC_SPSR    + WORD_SIZE )
SleepState_FIQ_R8       	    EQU     (SleepState_FIQ_SPSR    + WORD_SIZE )
SleepState_FIQ_R9       	    EQU     (SleepState_FIQ_R8  	+ WORD_SIZE )
SleepState_FIQ_R10      	    EQU     (SleepState_FIQ_R9  	+ WORD_SIZE )
SleepState_FIQ_R11      	    EQU     (SleepState_FIQ_R10 	+ WORD_SIZE )
SleepState_FIQ_R12      	    EQU     (SleepState_FIQ_R11 	+ WORD_SIZE )
SleepState_FIQ_SP       	    EQU     (SleepState_FIQ_R12 	+ WORD_SIZE )
SleepState_FIQ_LR       	    EQU     (SleepState_FIQ_SP  	+ WORD_SIZE )
SleepState_ABT_SPSR     	    EQU     (SleepState_FIQ_LR  	+ WORD_SIZE )
SleepState_ABT_SP       	    EQU     (SleepState_ABT_SPSR    + WORD_SIZE )
SleepState_ABT_LR       	    EQU     (SleepState_ABT_SP  	+ WORD_SIZE )
SleepState_IRQ_SPSR     	    EQU     (SleepState_ABT_LR  	+ WORD_SIZE )
SleepState_IRQ_SP       	    EQU     (SleepState_IRQ_SPSR    + WORD_SIZE )
SleepState_IRQ_LR       	    EQU     (SleepState_IRQ_SP  	+ WORD_SIZE )
SleepState_UND_SPSR     	    EQU     (SleepState_IRQ_LR  	+ WORD_SIZE )
SleepState_UND_SP       	    EQU     (SleepState_UND_SPSR    + WORD_SIZE )
SleepState_UND_LR       	    EQU     (SleepState_UND_SP  	+ WORD_SIZE )
SleepState_SYS_SP       	    EQU     (SleepState_UND_LR  	+ WORD_SIZE )
SleepState_SYS_LR       	    EQU     (SleepState_SYS_SP  	+ WORD_SIZE )

SleepState_Data_End     	    EQU     (SleepState_SYS_LR	+ WORD_SIZE )

SLEEPDATA_SIZE		    	    EQU     ((SleepState_Data_End - SleepState_Data_Start) / 4)

     AREA |sleep|, CODE, READONLY

     CODE32
     ALIGN
     PRESERVE8


sys_Arm9PowerDown

    stmdb   sp!, {r0-r12}                       ; store register value (except SP, LR) in SYS mode

    ;enter SVC mode
    mov     r1, #Mode_SVC:OR:I_Bit:OR:F_Bit
    msr     cpsr_c, r1

    ;1. Push SVC state onto our stack
    stmdb   sp!, {r4-r12}
    stmdb   sp!, {lr}
    ;stmdb   sp!, {r0}

    ;2. store return address (Awake_address) to RAM
    ldr     r3, =arm_sleep_data         ; base of Sleep mode storage

    ldr     r2, =Awake_address                  ; store Virtual return address
    str     r2, [r3], #4

    ;3. Save MMU Control register (C1) to RAM
    mrc     p15, 0, r2, c1, c0, 0               ; load r2 with MMU Control
    ldr     r0, =MMU_CTL_MASK                   ; mask off the undefined bits
    bic     r2, r2, r0
    str     r2, [r3], #4                        ; store MMU Control data

    ;4. Save TTB address (C2) to RAM
    mrc     p15, 0, r2, c2, c0, 0               ; load r2 with TTB address.
    ldr     r0, =MMU_TTB_MASK                   ; mask off the undefined bits
    bic     r2, r2, r0
    str     r2, [r3], #4                        ; store TTB address

    ;5. Save domain access control  (C3) to RAM
    mrc     p15, 0, r2, c3, c0, 0               ; load r2 with domain access control.
    str     r2, [r3], #4                        ; store domain access control

    ;6. Save SP value to RAM
    str     sp, [r3], #4                        ; store SVC stack pointer

    ;7. Save spsr_svc to RAM
    mrs     r2, spsr
    str     r2, [r3], #4                        ; store SVC status register

    ;8. switch to FIQ mode
    ;8. Save (spsr_fiq, r8~r12, sp, lr)  to RAM
    mov     r1, #Mode_FIQ:OR:I_Bit:OR:F_Bit     ; Enter FIQ mode, no interrupts
    msr     cpsr_c, r1
    mrs     r2, spsr
    stmia   r3!, {r2, r8-r12, sp, lr}           ; store the FIQ mode registers

    ;9. switch to ABT mode
    ;9. Save (spsr_abt, sp, lr)  to RAM
    mov     r1, #Mode_ABT:OR:I_Bit:OR:F_Bit     ; Enter ABT mode, no interrupts
    msr     cpsr_c, r1
    mrs     r0, spsr
    stmia   r3!, {r0, sp, lr}                   ; store the ABT mode Registers
    ;10. switch to IRQ mode
    ;10. Save (spsr_irq, sp, lr)  to RAM
    mov     r1, #Mode_IRQ:OR:I_Bit:OR:F_Bit     ; Enter IRQ mode, no interrupts
    msr     cpsr_c, r1
    mrs     r0, spsr
    stmia   r3!, {r0, sp, lr}                   ; store the IRQ Mode Registers

    ;11. switch to UND mode
    ;11. Save (spsr_und, sp, lr)  to RAM
    mov     r1, #Mode_UND:OR:I_Bit:OR:F_Bit     ; Enter UND mode, no interrupts
    msr     cpsr_c, r1
    mrs     r0, spsr
    stmia   r3!, {r0, sp, lr}                   ; store the UND mode Registers

    ;12. switch to SYS mode
    ;12. save (sp, lr)  to RAM
    mov     r1, #Mode_SYS:OR:I_Bit:OR:F_Bit     ; Enter SYS mode, no interrupts
    msr     cpsr_c, r1
    stmia   r3!, {sp, lr}                       ; store the SYS mode Registers

    ; back to SVC mode
    mov     r1, #Mode_SVC:OR:I_Bit:OR:F_Bit     ; Back to SVC mode, no interrupts
    msr     cpsr_c, r1

    ; Calculate checksum of RAM data
    ldr     r3, =arm_sleep_data         ; get pointer to SLEEPDATA
    mov     r2, #0
    ldr     r0, =SLEEPDATA_SIZE                     ; get size of data structure (in words)
30
    ldr     r1, [r3], #4
    and     r1, r1, #0x1
    mov     r1, r1, LSL #31
    orr     r1, r1, r1, LSR #1
    add     r2, r2, r1
    subs    r0, r0, #1
    bne     %b30

    LDR     r0, =sys_LeaveSleepStep
    MOV     r1, #0
    STR     r1, [r0]

    LDR     r0, =armSleepDataChkSum     ; store checksum
    STR     r2, [r0]             ;

    ;13. Flush and invalidate TLB
    mov     r0, #0
    mcr     p15, 0, r0, c8, c7, 0   ; flush unified TLB

    ;14. Flush I-cache
    mov     r0, #0
    mcr     p15, 0, r0, c7, c5, 0

    ;15. Flush D-cache
10  mrc     p15, 0, r15, c7, c14, 3
    bne     %b10

    ;16. Drain write buffer
    mov     r0, #0
    mcr     p15, 0, r0, c7, c10, 4

    ;16.1 disable MMU
    mov     r0, #0
    mcr     p15, 0, r0, c1, c0, 0

    LDR     r2, =g_ptW5SysTimer
    LDR     r2, [r2]
    LDR     r2, [r2, #0x44]                ; u32_StdaCounter
    LDR     r0, =Arm9AfterPowerDownQbCnt     ;KeGpio
    STR     r2, [r0]             ;


;    MOV     r2, #0
;    MOV     r3, #0

;    LDR     r1, =g_ptW5IrqControl   
;    LDR     r1, [r1]
;    LDR     r0, [r1, #68]           ; Get u32_RawStatus0
;    TST     r0, #1:SHL:7
;    BNE     sys_whileOne
    
;   MOV     r2, r0

;    CMP     r0, #0
;    BNE     sys_Arm9PowerDown_return
;    BNE     sys_whileOne

;    LDR     r0, [r1, #72]           ; Get u32_RawStatus1
;    CMP     r0, #0
;    BNE     sys_Arm9PowerDown_return
;    MOV     r3, r0
;    BNE     sys_whileOne

;    B       sys_Arm9PowerDown_Sleep

;sys_Arm9PowerDown_return
;    mov     r1, #Mode_SYS:OR:I_Bit:OR:F_Bit     ; Enter SYS mode, no interrupts
;    msr     cpsr_c, r1
    
;    LDR     r0, =sys_EnterSleepValue
;    MOV     r1, #0x2
;    STR     r1, [r0]

;    BX      lr

;sys_whileOne
;    B       sys_whileOne


    LDR     r4, =g_ptW5TbuC                ; use r4 to store g_ptW5TbuC
    LDR     r4, [r4]   
    LDR     r6, =hwll1_ReduceLastFrame       ; load reference label address
    LDR     r5, =BA_SYSREG

    IF :DEF:__NOR_BOOT__
    ELSE
    IF 0   ; temporary disable SDR self refresh
    ; SDR enter self-refresh mode

    LDR     r0, =DMC_REG
    ; reg_init_miu (turn off auto refresh)
    MOV     r1, #0x002F
    STRH    r1, [r0, #0x00]
    
    ; reg_init_miu (setting and issue precharge all command, single step)
    MOV     r1, #0x042F
    STRH    r1, [r0, #0x00]
            
    ; reg_mrx (addr[10]=1)
    MOV     r1, #0x0500
    STRH    r1, [r0, #0x30]             
    
    ; reg_init_miu (issue precharge all command out)
    MOV     r1, #0x052F
    STRH    r1, [r0, #0x00]             
    
    ; reg_init_miu (Setting and issue auto refresh command (single step turn on))
    MOV     r1, #0x022F
    STRH    r1, [r0, #0x00]             
    
    ; reg_init_miu (issue auto refresh command)
    MOV     r1, #0x032F
    STRH    r1, [r0, #0x00]             
    
    ; reg_init_miu ([8]=>sigle_step_en)
    MOV     r1, #0x002F
    STRH    r1, [r0, #0x00]             
    
    ; reg_pst_rq_mask (Turn off cmd0 client request)
    MOV     r1, #0xFFFF
    STRH    r1, [r0, #0x10C]             
    
    ; reg_init_miu (enter self refresh start)
    MOV     r1, #0x200F
    STRH    r1, [r0, #0x00]             
    ENDIF
    ENDIF	; __NOR_BOOT__

    ;IF :DEF:__EMI_PAD_PWD__
    ;19. EMI pad settting -- start
    LDR     r2, =_gPadConfigTbl            ; r0 = &_gPadConfigTbl[0]
    ;ENDIF ;:DEF:__EMI_PAD_PWD__

    ;IF :DEF:__EMI_PAD_PWD__
    ;19. EMI pad settting -- start
    ;LDR     r0, =_gPadConfigTbl            ; r0 = &_gPadConfigTbl[0]
    MOV     r0, r2
    MOV     r2, #27

50
    LDR     r3, [r0, #0x00]                ; r3 = _gPadConfigTbl[i].addr
    LDRH    r1, [r3]                       ; r1 = *(volatile u16 *)(_gPadConfigTbl[i].addr)
    STRH    r1, [r0, #0x06]                ; _gPadConfigTbl[i].shadow = r1

    LDRH    r1, [r0, #0x04]                ; r1 = _gPadConfigTbl[i].value;
    STRH    r1, [r3]                       ; _gPadConfigTbl[i].addr = r1

    ADD     r0, r0, #8                     ;move to next element of _gPadConfigTbl[0]
    SUB     r2, r2, #1
    CMP     r2, #0
    bne     %b50
    ; EMI pad settting -- end
    ;ENDIF; :DEF:__EMI_PAD_PWD__
    
    ;NOTE: from this point, all memory access shall be confined to IMI1, because EMI pad has been disabled

sys_Arm9PowerDown_Sleep
    ;LDR     r0, =hwll1_SleepLastCheck   ; load reference label address
    ;BLX     r0
   
     ;17. issue TBU sleep command
    ;g_ptW5TbuC->u32_Control |= TBU_SM32K_REQ;   // Go to sleep mode
    ;LDR     r2, =g_ptW5TbuC
    MOV     r2, r4
    LDR     r0, [r2, #0x0]              ; u32_Control
    orr     r0, r0, #0x0800             ; SM32_REQ
    STR     r0, [r2, #0x0]              ;

    ;LDR     r0, =hwll1_ReduceLastFrame       ; load reference label address
    BLX     r6                                ;hwll1_ReduceLastFrame() is tailored such that all access is within IMI1

    LDR     r0, =sys_Arm9PowerDown_1       ; load reference label address
    LDR     r1, =IMI1_ADDR                 ; add IMI base
    ORR     r1, r0
    BX      r1

sys_Arm9PowerDown_1

    ;IF :DEF:__SLEEP_MAP_IMI1__
    ;18. Change memory mapping
    ;LDR     r0, =BA_SYSREG
    MOV     r0, r5
    LDR     r1, [r0, #0x0c]                ; To map IRAM at 0x0
                                           ; CPU_MEMAP must be set to 1
    BIC     r1, r1, #7:SHL:4               ; Clear CPU_MEMAP field
    ORR     r1, r1, #1:SHL:4               ; Set to 1 (IMI1)
    STR     r1, [r0, #0x0c]                ; Write back
    ; Now the memory mapping has changed...
    nop
    nop
    ;ENDIF ;:DEF:__SLEEP_MAP_IMI1__


    LDR     r1, =sys_Arm9ImmePowerDown       ; load reference label address
    ;20. Issue WFI command
    mov     r0, #0
    mcr     p15, 0, r0, c7, c0, 4

    MOV     r2, r4
70
;    LDRH    r0, [r2, #0x1c]              ; u16_SleepTimeCounterVWIO
    
    LDR     r4, [r2, #0x34]              ; u32_IntStatus
    TST     r4, #1:SHL:2                 ; test u32_IntStatus[2]  
    BXNE	r1                           ; if (u32_IntStatus[2] == 1), go to wake up routine
 
;    CMP     r0, #0                       
;    BEQ     %b70                         ; wait until u16_SleepTimeCounterVWIO != 0
;    CMP     r0, #3
;    BXLT    r1
    B       %b70                         ; wait until wake-up interrupt bit = 1

sys_Arm9ImmePowerDown
    LDR     r0, =sys_LeaveWakeupImme
    LDR     r1, [r0]
    ADD     r1, r1, #1
    STR     r1, [r0]
;    B       sys_Arm9ImmePowerDown

;    B       SYS_ARM9IMIBOOT
    MOV     r0, #0
    BX      r0

    ;bx      lr

    ;nop
    ;nop
    ;nop


sys_Arm9WakeUp

    ;sys_inSleepMode = 0
    LDR     r0, =sys_inSleepMode
    MOV     r1, #0
    STR     r1, [r0]

    LDR     r0, =sys_EnterArm9Wakeup
    LDR     r1, [r0]
    ADD     r1, r1, #1
    STR     r1, [r0]


    ;Get Sleep Data size
    ldr     r0, =SLEEPDATA_SIZE                 ; r3 = 0x00000019
    mov         r2, #0                              ; Init r2
    ldr     r3, =arm_sleep_data         ; base of Sleep mode storage

40
    ldr         r1, [r3], #4                                ; Calculate checksum
    and         r1, r1, #0x1
    mov         r1, r1, LSL #31
    orr         r1, r1, r1, LSR #1
    add         r2, r2, r1
    subs        r0, r0, #1                                          ; dec the count
    bne         %b40                                        ; loop till done

    LDR     r0, =armSleepDataChkSum     ; get checksum
    LDR     r4, [r0]             ;
    teq     r2, r4                                      ; Get cehcksum compared
    bne     sys_CleanBoot                                ; Do a cold boot if checksum error

    ldr     r3, =arm_sleep_data         ; base of Sleep mode storage
    ldr     r10, [r3, #SleepState_MMUDOMAIN]        ; load the MMU domain access info
    ldr     r9,  [r3, #SleepState_MMUTTB]               ; load the MMU TTB info
    ldr     r8,  [r3, #SleepState_MMUCTL]               ; load the MMU control info
    ldr     r7,  [r3, #SleepState_WakeAddr]             ; load the LR address

    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop


    ;Restore MMU domain access control register (C3)
    mcr         p15, 0, r10, c3, c0, 0                  ; setup access to domain 0
    ;Restore MMU TTB address (C2)
    mcr         p15, 0, r9,  c2, c0, 0                  ; PT address
    ;Flush TLB
    mcr         p15, 0, r0,  c8, c7, 0                  ; flush I+D TLBs
    ;Restore MMU Control register (C1)
    mcr         p15, 0, r8,  c1, c0, 0                  ; restore MMU control

    BX          r7
    nop

Awake_address
    ;Restore CPU status
    LDR     r0, =sys_wakeUpFromReset
    MOV     r1, #0x1
    STR     r1, [r0]

    LDR     r0, =sys_EnterARMRestore
    LDR     r1, [r0]
    ADD     r1, r1, #1
    STR     r1, [r0]

    LDR     R3, =arm_sleep_data         ; 0xA00FE00
    add     r2, r3, #SleepState_FIQ_SPSR
    mov     r1, #Mode_FIQ:OR:I_Bit:OR:F_Bit             ; Enter FIQ mode, no interrupts - also FIQ
    msr     cpsr_c, r1
    ldr     r0,  [r2], #4
    msr     spsr_cxsf, r0
    ldr     r8,  [r2], #4
    ldr     r9,  [r2], #4
    ldr     r10, [r2], #4
    ldr     r11, [r2], #4
    ldr     r12, [r2], #4
    ldr     sp,  [r2], #4
    ldr     lr,  [r2], #4

    mov     r1, #Mode_ABT:OR:I_Bit                          ; Enter ABT mode, no interrupts
    msr     cpsr_c, r1
    ldr     r0, [r2], #4
    msr     spsr_cxsf, r0
    ldr     sp, [r2], #4
    ldr     lr, [r2], #4

    mov     r1, #Mode_IRQ:OR:I_Bit                          ; Enter IRQ mode, no interrupts
    msr     cpsr_c, r1
    ldr     r0, [r2], #4
    msr     spsr_cxsf, r0
    ldr     sp, [r2], #4
    ldr     lr, [r2], #4

    mov     r1, #Mode_UND:OR:I_Bit                          ; Enter UND mode, no interrupts
    msr     cpsr_c, r1
    ldr     r0, [r2], #4
    msr     spsr_cxsf, r0
    ldr     sp, [r2], #4
    ldr     lr, [r2], #4

    mov     r1, #Mode_SYS:OR:I_Bit                          ; Enter SYS mode, no interrupts
    msr     cpsr_c, r1
    ldr     sp, [r2], #4
    ldr     lr, [r2]

    mov     r1, #Mode_SVC:OR:I_Bit                              ; Enter SVC mode, no interrupts - FIQ is available
    msr     cpsr_c, r1
    ldr     r0, [r3, #SleepState_SVC_SPSR]
    msr     spsr_cxsf, r0

    ldr     r3, =arm_sleep_data                 ; Sleep mode information data structure
    ldr     sp, [r3, #SleepState_SVC_SP]
    ldr     lr, [sp], #4
    ;mov     r0, lr
    ldmia   sp!, {r4-r12}

    LDR     r0, =sys_LeaveARMRestore
    LDR     r1, [r0]
    ADD     r1, r1, #1
    STR     r1, [r0]

    ;12.go back to caller of OALCPUPowerOff()
    mov     r1, #Mode_SYS:OR:I_Bit:OR:F_Bit     ; Enter SYS mode, no interrupts
    msr     cpsr_c, r1
    ;mov     pc, lr                              ; and now back to our sponsors
    ;stmdb   sp!, {r0-r12}                       ; store register value (except SP, LR) in SYS mode
    ldmia   sp!, {r0-r12}                        ; restore register data of SYS mode

    bx      lr

     AREA |IMI_VECTORS|, CODE, READONLY
SYS_ARM9IMIBOOT
    ;IF :DEF:__EMI_PAD_PWD__
    ; EMI pad settting -- start
    LDR     r0, =_gPadConfigTbl            ; r0 = &_gPadConfigTbl[26]
    ADD     r0, r0, #(8*26)
    MOV     r2, #27

60
    LDR     r3, [r0, #0x00]                ; r3 = _gPadConfigTbl[i].addr
    LDRH    r1, [r0, #0x06]                ; r1 = _gPadConfigTbl[i].shadow
    STRH    r1, [r3]                       ; *(volatile u16 *)(_gPadConfigTbl[i].addr) = _gPadConfigTbl[i].shadow;

    SUB     r0, r0, #8                     ; move to previous element of _gPadConfigTbl[i]
    SUB     r2, r2, #1
    CMP     r2, #0
    bne     %b60
    ; EMI pad settting -- end
    ;ENDIF; :DEF:__EMI_PAD_PWD__

    IF :DEF:__NOR_BOOT__
    ELSE
    IF 0  ; temporary disable SDR self refresh    
    ; SDR leave self refresh
    
    LDR     r0, =DMC_REG
    ; reg_init_miu (Exit self refresh and enable auto refresh function)
    MOV     r1, #0x000F
    STRH    r1, [r0, #0x00]

    ; wait 0.5us(tXSR)
    MOV     r0, 26
1:  SUB     r0, r0, #1
    BNE     1b

    ; reg_pst_rq_mask (unmask cmd0 request)
    MOV     r1, #0xFFFE
    STRH    r1, [r0, #0x10C]

    ; reg_dynamic_cke (turn on dynamic cke/cs (disable dynamic cke in bring up))
    MOV     r1, #0x0000
    STRH    r1, [r0, #0x0C]

    ; reg_pst_rq_mask (turn on all client request)
    MOV     r1, #0x0000
    STRH    r1, [r0, #0x10C]
    ENDIF   ; 0
    ENDIF

    ;LDR     r0, =sys_LeaveSleepStep
    ;LDR     r1, [r0]
    ;ADD     r1, r1, #1
    ;STR     r1, [r0]

    LDR     r0, =sys_LeaveSleepCount
    LDR     r1, [r0]
    ADD     r1, r1, #1
    STR     r1, [r0]

;    LDR     r0, =sys_EnterSleepCount
;    LDR     r2, [r0]

;    CMP     r1, r2
;    BLGT    sys_whileOne
    
    ;LDR     r0, =sys_LeaveSleepStep
    ;LDR     r1, [r0]
    ;ADD     r1, r1, #1
    ;STR     r1, [r0]

    LDR     r2, =BA_SYSREG

    ; Change memory mapping
    LDR     r0, =SYS_ARM9IMIBOOT_1         ; load reference label address
    LDR     r1, =IMI1_ADDR                 ; add IMI base
    ORR     r1, r0                         ; r1= SYS_ARM9IMIBOOT_1 absolute address
    BX      r1

SYS_ARM9IMIBOOT_1
    ;LDR     r0, =sys_LeaveSleepStep
    ;LDR     r1, [r0]
    ;ADD     r1, r1, #1
    ;STR     r1, [r0]

    ;IF :DEF:__SLEEP_MAP_IMI1__
    MOV     r0, r2
    LDR     r1, [r0, #0x0c]                ; To map IRAM at 0x0
                                           ; CPU_MEMAP must be set to 1
    BIC     r1, r1, #7:SHL:4               ; Clear CPU_MEMAP field
    ORR     r1, r1, #7:SHL:4               ; Set to 7 (MEM0); for SDRAM 
    STR     r1, [r0, #0x0c]                ; Write back
    ; Now the memory mapping has changed...

    ;LDR     r1, [r0, #0x0c]                
    ;AND     r1, r1, #7:SHL:4               ; Set to 7 (MEM0); for SDRAM 
    ;TST     r1, #7:SHL:4                   ; branch to  SYS_ARM9IMIBOOT_1 absolute address
    ;BLXEQ   r2

    ;LDR     r0, =sys_LeaveSleepStep
    ;LDR     r1, [r0]
    ;ADD     r1, r1, #1
    ;STR     r1, [r0]


    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop

    ;LDR     r0, =SYS_ARM9IMIBOOT_2         ; load reference label address
    ;LDR     r2, =IMI1_ADDR                 ; add IMI base
    ;ORR     r2, r2, r0                         ; r1= SYS_ARM9IMIBOOT_1 absolute address

    ;LDR     r0, =sys_LeaveSleepStep
    ;LDR     r1, [r0]
    ;ADD     r1, r1, #1
    ;STR     r1, [r0]

;80
    ;LDR     r0, =MEM0_ADDR
    ;LDR     r2, [r0]                ; To map IRAM at 0x0

    ;MOV     r0, #0
    ;LDR     r1, [r0]                ; To map IRAM at 0x0

    ;CMP     r1, r2
    ;BXNE    r2 

    ;LDR     r0, =sys_LeaveSleepStep
    ;LDR     r1, [r0]
    ;ADD     r1, r1, #1
    ;STR     r1, [r0]

    ;LDR     r0, =COMMON_ADDR
    ;LDR     r1, [r0]

    ;LDR     r0, =MEM0_ADDR
    ;LDR     r2, [r0]
                                           
    ;CMP     r1, r2
    ;BNE     %b80
                                           ; CPU_MEMAP must be set to 1
    MOV     r0, #0
    BX      r0
    ;ENDIF ;:DEF:__SLEEP_MAP_IMI1__

    ENDIF

     END
