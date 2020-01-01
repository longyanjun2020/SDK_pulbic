/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
*******************************************************************************/
/*******************************************************************************
* Copyright (C) 2013 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/******************************************************************************
* File Name     : reset_handler.S
* Device(s)     : RZ/A1H RSK2+RZA1H
* Tool-Chain    : GNUARM-RZv13.01-EABI
* H/W Platform  : RSK2+RZA1H CPU Board
* Description   : Called by reset vector (start.S/mirrorstart.S)
*               : As such its the startpoint for this software
******************************************************************************/
/******************************************************************************
* History       : DD.MM.YYYY Version Description
*               : 18.06.2013 1.00
******************************************************************************/

    .global reset_handler
    .global undefined_handler
    .global svc_handler
    .global prefetch_handler
    .global abort_handler
    .global reserved_handler

    .text
    .eabi_attribute Tag_ABI_align8_preserved,1

/* Standard definitions of mode bits and interrupt flags in PSRs */
    .equ    USR_MODE , 0x10
    .equ    FIQ_MODE , 0x11
    .equ    IRQ_MODE , 0x12
    .equ    SVC_MODE , 0x13
    .equ    ABT_MODE , 0x17
    .equ    UND_MODE , 0x1b
    .equ    SYS_MODE , 0x1f
    .equ    Thum_bit , 0x20                           /* CPSR/SPSR Thumb bit */


/* data segment, wait to modify
// To accelerate FINT execution by avoiding accessing memory via EMI
        AREA |SUP_Stacks|, DATA, NOINIT
        */

    .equ    IRQ_DISABLE ,  0x80
    .equ    FIQ_DISABLE ,  0x40

#ifdef __HW_WATCHDOG_FIQ__
    .equ    INT_DISABLE ,       IRQ_DISABLE
#else
    .equ    INT_DISABLE ,       FIQ_DISABLE | IRQ_DISABLE
#endif

__BootEntry:
       .global __BootEntry
reset_handler:
/* ========================================================================= */
/* Multi-core startup (future proofing boot code)                            */
/* Check core, if not core 0  put to sleep.                                  */
/* ========================================================================= */
        MRC     p15, 0, r0, c0, c0, 5                          /* Read MPIDR */
        ANDS    r0, r0, #3
goToSleep:
        WFINE
        BNE     goToSleep

/* ========================================================================= */
/* Disable cache and MMU in case it was left enabled from an earlier         */
/* This does not need to be done from a cold reset                           */
/*****************************************************************************/
    MRC  p15, 0, r0, c1, c0, 0 /* Read CP15 SCTLR                            */
    //BIC  r0, r0, #(0x1 << 12)  /* Clear I bit 12 to disable I Cache          */
    ORR  r0, r0, #(0x1 << 12)  /* Set I bit 12 to enable I Cache          */
    BIC  r0, r0, #(0x1 <<  2)  /* Clear C bit  2 to disable D Cache          */
    BIC  r0, r0, #0x1           /* Clear M bit  0 to disable MMU             */
    MCR  p15, 0, r0, c1, c0, 0 /* Write value back to CP15 SCR               */

/* ========================================================================= */
/*    Reset Vbar to this programs vectors                                    */
/* ========================================================================= */
    BL   VbarInit

/* Write to ACTLR before caches and MMU are enabled*/
    MRC	p15, 0, r0, c1, c0, 1		/* Read ACTLR*/
    ORR	r0, r0, #(0x01 << 6)		/* set SMP bit */
    MCR	p15, 0, r0, c1, c0, 1		/* Write ACTLR*/

/* ========================================================================= */
/* To boot using the on-chip program allowing user code to run from attached */
/* SPI/eSD, or eMMC devices, the RZA1 uses the Hivecs base vector            */
/* address (0xFFFF0000).                                                     */
/* Call SetLowVectors to clear the Hivecs bit in the System Control Register */
/* to allow the processor to use the relocated vector table specified in     */
/* this program.                                                             */
/* See the Hardware Manual Boot Mode section for detailed description of the */
/* startup process when using the on-chip ROM boot program.                  */
/* The relocated vector table MUST be aligned on 32-byte boundary.           */
/* Please refer for more details to section                                  */
/* B4.1.156 VBAR, Vector Base Address Register, Security Extensions,         */
/* ARM Architecture Reference Manual ARMv7-A and ARMv7-R edition             */
/* ========================================================================= */
    BL  SetLowVectors

/*sys_CleanBoot:
#ifdef __NOR_BOOT__
    //in case of HW WDT, need to reset MCP BCR in very begining
    LDR     r0, =IRAM_STACK
    SUB     r0, r0, #8
    STR     sp, [r0]// store current SP
    STR     lr, [r0, #4]// store current LR
    BL      Boot_Entry_EMI // init MCP BCR

    LDR     r0, =IRAM_STACK
    SUB     r0, r0, #8
    LDR     sp, [r0]             //restore SP
    LDR     lr, [r0, #4]         //restore LR
#endif
#ifdef __BRANCH_To_ZERO__
    LDR r0, =bzBacktrace
    STMIA   r0!, {r1-r12, sp, lr}
    MRS r1, cpsr
    MRS r2, spsr
    STMIA   r0!, {r1, r2}
    LDR     r1, =Rtk_CurrentTask
    LDRB    r1, [r1]
    STMIA   r0!, {r1}

    // check if SP is larger than 0x10400000 (DRAM upper boundary)
#ifdef __I_SW__
    LDR     r1, =Image$$XRAM$$Base
    LDR r2, =limitRAMsSize
    LDR r2, [r2]
    ADD     r2, r2, r1
#else
    LDR r2, =sys_PhyRAMSize
    LDR r2, [r2]
#ifdef __NOR_BOOT__
    LDR r1, =Image$$XRAM$$Base
    LDR r1, [r1]
    ADD     r2, r2, r1                    //usable ram base + usable ram size
#endif
    LDR     r1, =Image$$XRAM$$Base
#endif
    SUB     r2, r2, #200
    SUB     r2, r2, #200
    SUB     r2, r2, #200
    CMP     sp, r2
    BLE     __BootEntry_check_if_need_to_reset_SP_1
    // set SP as 0x10000000 as default value
    MOV     sp, r1
    B       __BootEntry_check_if_need_to_reset_SP_2

__BootEntry_check_if_need_to_reset_SP_1:
    // check if SP is smaller than 0x10000000 (DRAM lower boundary)
    CMP     sp, r1
    BGE     __BootEntry_check_if_need_to_reset_SP_2
    // set SP as 0x10000000 as default value
    MOV     sp, r1

__BootEntry_check_if_need_to_reset_SP_2:
    MOV     r1, #1
    LSL     r1, r1, #7

__BootEntry_backup_stack:
    LDR     r2, [sp], #4
    STR     r2, [r0], #4
    SUB     r1, r1, #1
    CMP     r1, #0
    BNE     __BootEntry_backup_stack


    // unlock internal RAM for initial setting
__BootEntry_after_store_debug_info:
    IMPORT  g_ptW5SysReg
    LDR r0, =g_ptW5SysReg
    LDR r0, [r0]
    LDR r1, [r0, #12]
    ORR r1, #0x300000
    STR r1, [r0, #12]

    B   __BootEntry_normal

#else
   // store the current Task status in IRAM_STACK
    LDR     r0, =IRAM_STACK   // save sp in Rtk_CurrentTaskStackDump.sp
    SUB     r0, r0, #564
    LDR     r1, =Rtk_CurrentTask   // save sp in Rtk_CurrentTaskStackDump.sp
    LDRB    r1, [r1]
    STR     r1, [r0], #4
    STR     sp, [r0], #4

    MRS     r1, cpsr                        // store user mode cpsr in r2
    STMIA   r0!, {r1, r4-r12, lr}           // save registers in Rtk_CurrentTaskStackDump.reg

    // check if SP is larger than 0x10400000 (DRAM upper boundary)
#ifdef __I_SW__
    LDR r1, =Image$$XRAM$$Base
    LDR r2, =limitRAMsSize
    LDR r2, [r2]
    ADD     r2, r2, r1
#else
    LDR r2, =sys_PhyRAMSize
    LDR r2, [r2]
#ifdef __NOR_BOOT__
    LDR r1, =Image$$XRAM$$Base
    LDR r1, [r1]
    ADD     r2, r2, r1                    //usable ram base + usable ram size
#endif
    LDR     r1, =Image$$XRAM$$Base
#endif

    SUB     r2, r2, #200
    SUB     r2, r2, #200
    SUB     r2, r2, #200
    CMP     sp, r2
    BLE     __BootEntry_noreset_sp_1
    // set SP as 0x10000000 as default value
    MOV     sp, r1
    B       __BootEntry_noreset_sp_2

__BootEntry_noreset_sp_1:
    // check if SP is smaller than 0x10000000 (DRAM lower boundary)
    CMP     sp, r1
    BGE     __BootEntry_noreset_sp_2
    // set SP as 0x10000000 as default value
    MOV     sp, r1

__BootEntry_noreset_sp_2:
    MOV     r1, #1
    LSL     r1, r1, #7

__BootEntry_loop_store:
    LDR     r2, [sp], #4
    STR     r2, [r0], #4
    SUB     r1, r1, #1
    CMP     r1, #0
    BNE     __BootEntry_loop_store
#endif
*/
__BootEntry_normal:
#ifdef __RTK_DIAGNOSE_ENHANCE__
    LDR     r0, =Rtk_IsIrqFiqMode
    MOV r1, #0
    STR r1, [r0]
#endif

_Keep_SYS_LR_SP:
	  LDR	R0, =Rtk_RegionCount
	  LDRH	R0, [R0]
	  LDR	R1, =SysWdtModeInfo
	  STR	R0, [R1]
    // Set mode Sys32
	  MOV     r0, #INT_DISABLE | SYS_MODE
	  MSR     cpsr_cxsf, r0
	  STR	SP, [R1, #4]
	  STR	LR, [R1, #8]
    // Set mode Irq32
	  MOV     r0, #INT_DISABLE | IRQ_MODE
	  MSR     cpsr_cxsf, r0
	  STR	SP, [R1, #12]
	  STR	LR, [R1, #16]

    // disable irq and fiq
    MOV   r0, #INT_DISABLE | SVC_MODE
    MSR   cpsr_cxsf, r0
    // Disable MMU
    //MRC     p15, 0, r0, c1, c0, 0       // read CP15 register 1 into r0
    //BIC     r0, r0, #0x1                // clear bit 0
   // MCR     p15, 0, r0, c1, c0, 0       // write value back
    // Drain the write buffer
    MOV     r0, #0x0
    MCR     p15, 0, r0, c7, c10, 4
    // Invalidate I and D Cache
    MOV     r0, #0x0
    MCR     p15, 0, r0, c7, c5, 0
    BL      __invalidate_l1
    // Invalidate unified TLB
    MOV     r0, #0x0
    MCR     p15, 0, r0, c8, c7, 0

// -----------------------------------------------------------------------------
// Branch to main
// -----------------------------------------------------------------------------
    // Initialisations are done
    // in C language routines
    //LDR sp, =IRAM_STACK
    //SUB sp, sp, #564

    // change boot stack from IRAM_STACK to imi2 heap end sine IRAM_STACK will cause
    // the contents of execution region IRAM_SECTION_ZI to be corrupted at run-time.
   // BL sys_get_imi2_end_address//
   // BIC r0, r0, #0x3
   // SUB r0, r0, #0x400
   // MOV sp, r0


    BL  sys_premain_first // init pll and emi

    // ;resrve for measuring  time
    //            ;IMPORT time_measure
    //            ;pop {r0}
    //            ;MOV r1, #1
    //            ;BL time_measure
    //            ;push {r0}  ; push result 1 to stack
#ifdef __ISW_NORBOOT__ /*__ISW_NORBOOT__*/
    /* set mmu 1st table */
    BL mmu_translation_table_reset_for_decompression
    /* enable mmu */
    MOV r0, #0
    BL __enable_mmu_wrapper


               // resrve for measuring  time
                //BL DrvTimerStdaTimerGetTick
                //push {r0}

    /* do decompress */
    BL	_do_decompress

   // LDR  r12,=initsct                 /* Use register for possible long jump */
   // BLX  r12                                             /* Stack Initialize */



                // resrve for measuring  time
                //pop {r0, r2}  ; pop result 1 from stack, and set to real result 1
                //MOV r1, #2
                //BL time_measure


    /*disable mmu and then enable ICache*/
    BL __disable_mmu_wrapper

    MRC  p15, 0, r0, c1, c0, 0 /* Read CP15 SCTLR                            */
    ORR  r0, r0, #(0x1 << 12)  /* Set I bit 12 to enable I Cache          */
    MCR  p15, 0, r0, c1, c0, 0 /* Write value back to CP15 SCR               */
#endif /*__ISW_NORBOOT__*/

/* ========================================================================= */
/*  Setting up Stack Area hadled by .ld file                                 */
/* ========================================================================= */

#ifdef __RTK_STACK_DIAGNOSE__
    // Stack initialization with a pattern
    LDR     r0, =fiq_stack_start
    LDR     r1, =boot_stack_end
    LDR     r2,=0x55555555
    CMP     r0, r1
    BEQ     StackInitEnd_STACK_DIAGNOSE
StackInitLoop_STACK_DIAGNOSE:
    STR     r2, [r0], #4
    CMP     r0, r1
    BCC     StackInitLoop_STACK_DIAGNOSE
StackInitEnd_STACK_DIAGNOSE:
//    For sup stack change position
    LDR     r0, =svc_stack_start
    LDR     r1, =svc_stack_end
    LDR     r2, =0x55555555
    CMP     r0, r1
    BEQ     StackInitEnd_STACK_DIAGNOSE2
StackInitLoop_STACK_DIAGNOSE2:
    STR     r2, [r0], #4
    CMP     r0, r1
    BCC     StackInitLoop_STACK_DIAGNOSE2
StackInitEnd_STACK_DIAGNOSE2:
    //guard pattern
    LDR     r2,=0xbeefdead

    // Set stack for SVC
    LDR     r0, =svc_stack_end
    SUB     r0, r0, #0x8
    MOV     sp, r0
    STR     r2, [r0]
    STR     r2, [r0, #0x4]
    //LDR     sp, =svc_stack_end

    // Set mode Fiq32 and set stack
    MOV     r0, #INT_DISABLE | FIQ_MODE
    MSR     cpsr_cxsf, r0
    LDR     r0, =fiq_stack_end
    SUB     r0, r0, #0x8
    MOV     sp, r0
    STR     r2, [r0]
    STR     r2, [r0, #0x4]
    //LDR     sp, =fiq_stack_end

    // Set mode Irq32 and set stack
    MOV     r0, #INT_DISABLE | IRQ_MODE
    MSR     cpsr_cxsf, r0
    LDR     r0, =irq_stack_end
    SUB     r0, r0, #0x8
    MOV     sp, r0
    STR     r2, [r0]
    STR     r2, [r0, #0x4]
    //LDR     sp, =irq_stack_end

    // Set mode abort32 and set stack
    MOV     r0, #INT_DISABLE | ABT_MODE
    MSR     cpsr_cxsf, r0
    LDR     r0, =abt_stack_end
    SUB     r0, r0, #0x8
    MOV     sp, r0
    STR     r2, [r0]
    STR     r2, [r0, #0x4]
    //LDR     sp, =abt_stack_end

    // Set mode undef32 and set stack
    MOV     r0, #INT_DISABLE | UND_MODE
    MSR     cpsr_cxsf, r0
    LDR     r0, =und_stack_end
    SUB     r0, r0, #0x8
    MOV     sp, r0
    STR     r2, [r0]
    STR     r2, [r0, #0x4]
    //LDR     sp, =und_stack_end

    // Set mode Sys32 and set stack (it also sets user stack)
    MOV     r0, #INT_DISABLE | SYS_MODE
    MSR     cpsr_cxsf, r0
    LDR     r0, =boot_stack_end
    SUB     r0, r0, #0x8
    MOV     sp, r0
    STR     r2, [r0]
    STR     r2, [r0, #0x4]
    //LDR     sp, =boot_stack_end
#else
    // Set stack for SVC
    LDR     sp, =svc_stack_end

    // Set mode Fiq32 and set stack
    MOV     r0, #INT_DISABLE | FIQ_MODE
    MSR     cpsr_cxsf, r0
    LDR     sp, =fiq_stack_end

    // Set mode Irq32 and set stack
    MOV     r0, #INT_DISABLE | IRQ_MODE
    MSR     cpsr_cxsf, r0
    LDR     sp, =irq_stack_end

    // Set mode abort32 and set stack
    MOV     r0, #INT_DISABLE | ABT_MODE
    MSR     cpsr_cxsf, r0
    LDR     sp, =abt_stack_end

    // Set mode undef32 and set stack
    MOV     r0, #INT_DISABLE | UND_MODE
    MSR     cpsr_cxsf, r0
    LDR     sp, =und_stack_end

    // Set mode Sys32 and set stack (it also sets user stack)
    MOV     r0, #INT_DISABLE | SYS_MODE
    MSR     cpsr_cxsf, r0
    LDR     sp, =boot_stack_end

    // Stack initialization with a pattern
    LDR     r0, =fiq_stack_start
    LDR     r1, =boot_stack_end
    LDR     r2,=0x55555555
    CMP     r0, r1
    BEQ     StackInitEnd
StackInitLoop:
    STR     r2, [r0], #4
    CMP     r0, r1
    BCC     StackInitLoop
StackInitEnd:
#endif



Finished:

/* ========================================================================= */
/* Enable access to NEON/VFP by enabling access to Coprocessors 10 and 11.   */
/* Enables Full Access i.e. in both privileged and non privileged modes      */
/* ========================================================================= */
    MRC  p15, 0, r0, c1, c0, 2   /* Read Coprocessor Access Control Register */
    ORR  r0, r0, #(0xF << 20)                 /* Enable access to CP 10 & 11 */
    MCR  p15, 0, r0, c1, c0, 2  /* Write Coprocessor Access Control Register */
    ISB

/* ========================================================================= */
/* Switch on the VFP and NEON hardware                                       */
/* ========================================================================= */
    MOV  r0, #0x40000000
    VMSR FPEXC, r0                       /* Write FPEXC register, EN bit set */

/* ========================================================================= */
/* initsct                                                                   */
/* Initialize ZI in Stack Area                                               */
/* ========================================================================= */
#ifndef __ISW_NORBOOT__/*__ISW_NORBOOT__*/
    LDR  r12,=initsct                 /* Use register for possible long jump */
    BLX  r12                                             /* Stack Initialize */
#endif
/* ========================================================================= */
/* Branch to C library entry point                                           */
/* ========================================================================= */
B   sys_premain_second // sys_premain calls main

/* ========================================================================= */
/* Other Handler                                                             */
/* ========================================================================= */
undefined_handler:
    B    undefined_handler

svc_handler:
    B    svc_handler

prefetch_handler:
    B    prefetch_handler

abort_handler:
    B    abort_handler

reserved_handler:
    B    reserved_handler


//; -----------------------------------------------------------------------------
//; Store ARM Registers
//; This functions store in adress pointed by r0 the content of R3->r14 + CPSR
//; for debug purpose, in case of unexpected watchdog reset
//; -----------------------------------------------------------------------------
    .global StoreARMRegisters
StoreARMRegisters:
    STR   r1, [sp, #-4]!     //; save registers mofified
                             //; Store registers.
    STMIA   r0!, {r3-r14}    //; copy R3 to R14 at the address specified by r0, and increment R0
    MRS     r1, cpsr
    STR     r1, [r0]         //; save CPSR after R14
    LDR   r1, [sp], #4       //; restore registers saved
    BX    lr

/****************************************************************************/
/* GLOBAL VARIABLES                                                         */
/****************************************************************************/
.section STATICBOOT
    .global sys_ResetPattern
    .global sys_RAMSize
sys_ResetPattern: .word  0
sys_RAMSize:      .word  0
#ifdef __I_SW__
#else
    .global limitRAMsSize
limitRAMsSize:    .word 0
#endif

.end
