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
/*******************************************************************************
* File Name     : access.S
* Device(s)     : RZ/A1H RSK2+RZA1H
* Tool-Chain    : GNUARM-RZv13.01-EABI
* H/W Platform  : RSK2+RZA1H CPU Board
* Description   : This is the code provides access to the co-processors
*******************************************************************************/
/*******************************************************************************
* History       : DD.MM.YYYY Version Description
*               : 18.06.2013 1.00
*******************************************************************************/

    .text
    .code 32

        .global enable_neon_vfp_access_priv
        .global enable_neon_vfp_access_full
        .global disable_neon_vfp_access
        .global neon_vfp_on
        .global neon_vfp_off
        .global enable_mmu
        .global disable_mmu
        .global VbarInit
        .global SetLowVectors
        .global SetHighVectors
        .global getAPSR
        .global setFPSCR
        .global L1CacheInit
        .global initsct
        .global __clean_dcache_all
        .global __flush_dcache_all
        .global __invalidate_l1


/* ========================================================================== */
/* Enable access to NEON/VFP by enabling access to Coprocessors 10 and 11.    */
/* Enables Privileged Access i.e. in both privileged and non privileged modes */
/* ========================================================================== */
    .func   enable_neon_vfp_access_priv
enable_neon_vfp_access_priv:
    MRC  p15, 0, r0, c1, c0, 2 /* Read Coprocessor Access Register (CPACR)    */
    ORR  r0, r0, #(0x5 << 20)  /* Enable access to CP 10 & 11                 */
    BIC  r0, r0, #(3 << 30)    /* Clear ASEDIS/D32DIS if set                  */
    MCR  p15, 0, r0, c1, c0, 2 /* Write Coprocessor Access Register (CPACR)   */
    ISB
    BX        lr
    .endfunc
    .align 4

/* ========================================================================== */
/* Enable access to NEON/VFP by enabling access to Coprocessors 10 and 11.    */
/* Enables Full Access i.e. in both privileged and non privileged modes       */
/* ========================================================================== */
    .func   enable_neon_vfp_access_full
enable_neon_vfp_access_full:
    MRC  p15, 0, r0, c1, c0, 2 /* Read Coprocessor Access Register (CPACR)    */
    ORR  r0, r0, #(0xF << 22)  /* Enable access to CP 10 & 11                 */
    BIC  r0, r0, #(3 << 30)    /* Clear ASEDIS/D32DIS if set                  */
    MCR  p15, 0, r0, c1, c0, 2 /* Write Coprocessor Access Register (CPACR)   */
    ISB
    BX        lr
    .endfunc
    .align 4


/* ========================================================================== */
/* Disable access to NEON/VFP by enabling access to Coprocessors 10 and 11.   */
/* ========================================================================== */
    .func   disable_neon_vfp_access
disable_neon_vfp_access:
    MRC  p15, 0, r0, c1, c0, 2 /* Read Coprocessor Access Register (CPACR)    */
    BIC  r0, r0, #(0xF << 20)  /* Disable access to CP 10 & 11                */
    MCR  p15, 0, r0, c1, c0, 2 /* Write Coprocessor Access Register (CPACR)   */
    ISB
    BX        lr
    .align 4
    .endfunc

/* ========================================================================== */
/*  Switch on the VFP and NEON hardware                                       */
/* ========================================================================== */
    .func neon_vfp_on
neon_vfp_on:
    MOV  r0, #0x40000000
    VMSR FPEXC, r0                        /* Write FPEXC register, EN bit set */
    ISB
    BX        lr
    .endfunc
    .align 4

/* ========================================================================== */
/*  Switch off the VFP and NEON hardware                                      */
/* ========================================================================== */
    .func neon_vfp_off
neon_vfp_off:
    MOV  r0, #0x00000000
    VMSR FPEXC, r0                      /* Write FPEXC register, EN bit clear */
    ISB
    BX        lr
    .endfunc
    .align 4

/* ========================================================================== */
/* Enable MMU                                                                 */
/* Leaving the caches disabled.                                               */
/* ========================================================================== */
    .func enable_mmu
enable_mmu:
    MRC  p15, 0, r0, c1, c0, 0     /* Read CP15 System Control register (SCTLR) */
    BIC  r0, r0, #(0x1 << 12)             /* Clear I bit 12 to disable I Cache */
    BIC  r0, r0, #(0x1 <<  2)             /* Clear C bit  2 to disable D Cache */
    BIC  r0, r0, #0x2       /* Clear A bit 1 to disable alignment fault check */
    ORR  r0, r0, #0x1      /* Set M bit 1 to enable MMU before scatter loading */
    MCR  p15, 0, r0, c1, c0, 0            /* Write CP15 System Control register */
    ISB
    BX        lr
    .endfunc
    .align 4

/* ========================================================================== */
/* Disable MMU                                                                */
/* Leaving the caches disabled.                                               */
/* ========================================================================== */
        .func disable_mmu
disable_mmu:
        MRC  p15, 0, r0, c1, c0, 0       /* Read CP15 System Control register */
        BIC  r0, r0, #(0x1 << 12)        /* Clear I bit 12 to disable I Cache */
        BIC  r0, r0, #(0x1 <<  2)        /* Clear C bit  2 to disable D Cache */
        BIC  r0, r0, #0x2   /* Clear A bit 1 to disable alignment fault check */
        BIC  r0, r0, #0x1 /* Set M bit 0 to enable MMU before scatter loading */
        MCR  p15, 0, r0, c1, c0, 0      /* Write CP15 System Control register */
        BX   lr
        .endfunc
        .align 4

/* ========================================================================== */
/* VbarInit                                                                   */
/* ========================================================================== */
    .func VbarInit
VbarInit:
/* ========================================================================== */
/* Set Vector Base Address Register to point to application's vector table    */
/* ========================================================================== */
    LDR r0, = start
    MCR p15, 0, r0, c12, c0, 0

    BX		lr
    .endfunc

/* ========================================================================== */
/* Set SCTLR Low Vectors                                                      */
/*      0 = Normal (Low address) Vectors                                      */
/*      1 = High (High address) Vectors                                       */
/* ========================================================================== */
    .func SetLowVectors
SetLowVectors:
    MRC  p15, 0, r0, c1, c0, 0   /* Read CP15 System Control register (SCTLR) */
    BIC  r0, r0, #(0x1 << 13)           /* Clear V bit 13 to set Low Vectors  */
    MCR  p15, 0, r0, c1, c0, 0          /* Write CP15 System Control register */
    ISB
    BX        lr
    .endfunc
    .align 4

/* ========================================================================== */
/* Set SCTLR High Vectors                                                     */
/*      0 = Normal (Low address) Vectors                                      */
/*      1 = High (High address) Vectors                                       */
/* ========================================================================== */
    .func SetHighVectors
SetHighVectors:
    MRC  p15, 0, r0, c1, c0, 0   /* Read CP15 System Control register (SCTLR) */
    ORR  r0, r0, #(0x1 << 13)           /* Set V bit 13 to set High Vectors   */
    MCR  p15, 0, r0, c1, c0, 0          /* Write CP15 System Control register */
    ISB
    BX        lr
    .endfunc
    .align 4

/* ========================================================================== */
/* getAPSR                                                                   */
/* ========================================================================== */
    .func getAPSR
getAPSR:
/* ========================================================================== */
/* Get Application Program Status Register contents                           */
/* ========================================================================== */
    MRS  r0, APSR
    ISB
    BX		lr
    .endfunc
    .align 4

/* ========================================================================== */
/* setFPSCR                                                                   */
/* ========================================================================== */
    .func setFPSCR
setFPSCR:
/* ========================================================================== */
/* Set Floating Point Status and Control Register contents                    */
/* ========================================================================== */
    FMXR 	FPSCR, r0
    ISB
    BX		lr
    .endfunc
    .align 4



    .func __invalidate_l1
__invalidate_l1:
    MOV     r0, #0
    MCR     p15, 2, r0, c0, c0, 0
    MRC     p15, 1, r0, c0, c0, 0

    LDR     r1, =0x7fff
    AND     r2, r1, r0, lsr #13

    LDR     r1, =0x3ff

    AND     r3, r1, r0, lsr #3      // NumWays - 1
    ADD     r2, r2, #1              // NumSets

    AND     r0, r0, #0x7
    ADD     r0, r0, #4      // SetShift

    CLZ     r1, r3          // WayShift
    ADD     r4, r3, #1      // NumWays
1:  SUB     r2, r2, #1      // NumSets--
    MOV     r3, r4          // Temp = NumWays
2:  SUBS    r3, r3, #1      // Temp--
    MOV     r5, r3, lsl r1
    MOV     r6, r2, lsl r0
    ORR     r5, r5, r6      // Reg = (Temp<<WayShift)|(NumSets<<SetShift)
    MCR     p15, 0, r5, c7, c6, 2
    BGT     2b
    CMP     r2, #0
    BGT     1b
    DSB     st
    ISB
    BX	    lr
    .endfunc

    .func __clean_dcache_all
__clean_dcache_all:
 /* Clean Data/Unified Caches */
    PUSH  {r4-r5,r7,r9-r11}
    MRC  p15, 1, r0, c0, c0, 1                                 /* Read CLIDR */
    ANDS r3, r0, #0x07000000                      /* Extract coherency level */
    MOV  r3, r3, LSR #23                          /* Total cache levels << 1 */
    BEQ  CFinished                                  /* If 0, no need to clean */

    MOV  r10, #0                       /* R10 holds current cache level << 1 */
CLoop1:
    ADD  r2, r10, r10, LSR #1               /* R2 holds cache "Set" position */
    MOV  r1, r0, LSR r2   /* Bottom 3 bits are the Cache-type for this level */
    AND  r1, r1, #7                            /* Isolate those lower 3 bits */
    CMP  r1, #2
    BLT  CSkip            /* No cache or only instruction cache at this level */

    MCR  p15, 2, r10, c0, c0, 0  /* Write the Cache Size selection  (CSSELR) */
    ISB                     /* ISB to sync the change to the CacheSizeID reg */
    MRC  p15, 1, r1, c0, c0, 0       /* Reads current Cache Size ID (CCSIDR) */
    AND  r2, r1, #7                         /* Extract the line length field */
    ADD  r2, r2, #4      /* Add 4 for the line length offset (log2 16 bytes) */
    LDR  r4, =0x3FF
    ANDS r4, r4, r1, LSR #3          /* R4 is the max number on the way size */
    CLZ  r5, r4          /* R5 is the bit position of the way size increment */
    LDR  r7, =0x7FFF
    ANDS r7, r7, r1, LSR #13       /* R7 is the max number of the index size */
CLoop2:
    MOV  r9, r4                      /* R9 working copy of the max way size  */

CLoop3:
    ORR  r11, r10, r9, LSL r5 /* Factor in the Way and cache number into R11 */
    ORR  r11, r11, r7, LSL r2                    /* Factor in the Set number */
    MCR  p15, 0, r11, c7, c10, 2             /* Clean by Set/Way (DCISW) */
    SUBS r9, r9, #1                              /* Decrement the Way number */
    BGE  CLoop3
    SUBS r7, r7, #1                              /* Decrement the Set number */
    BGE  CLoop2
CSkip:
    ADD  r10, r10, #2                          /* increment the cache number */
    CMP  r3, r10
    BGT  CLoop1
CFinished:
    MOV  r10, #0			/* swith back to cache level 0 */
    MCR  p15, 2, r10, c0, c0, 0		/* select current cache level in CSSELR*/
    POP  {r4-r5,r7,r9-r11}
    BX	 lr
    .endfunc

    .func __flush_dcache_all
__flush_dcache_all:
 /* Flush Data/Unified Caches */
    PUSH  {r4-r5,r7,r9-r11}
    MRC  p15, 1, r0, c0, c0, 1                                 /* Read CLIDR */
    ANDS r3, r0, #0x07000000                      /* Extract coherency level */
    MOV  r3, r3, LSR #23                          /* Total cache levels << 1 */
    BEQ  Finished                                  /* If 0, no need to clean */

    MOV  r10, #0                       /* R10 holds current cache level << 1 */
Loop1:
    ADD  r2, r10, r10, LSR #1               /* R2 holds cache "Set" position */
    MOV  r1, r0, LSR r2   /* Bottom 3 bits are the Cache-type for this level */
    AND  r1, r1, #7                            /* Isolate those lower 3 bits */
    CMP  r1, #2
    BLT  Skip            /* No cache or only instruction cache at this level */

    MCR  p15, 2, r10, c0, c0, 0  /* Write the Cache Size selection  (CSSELR) */
    ISB                     /* ISB to sync the change to the CacheSizeID reg */
    MRC  p15, 1, r1, c0, c0, 0       /* Reads current Cache Size ID (CCSIDR) */
    AND  r2, r1, #7                         /* Extract the line length field */
    ADD  r2, r2, #4      /* Add 4 for the line length offset (log2 16 bytes) */
    LDR  r4, =0x3FF
    ANDS r4, r4, r1, LSR #3          /* R4 is the max number on the way size */
    CLZ  r5, r4          /* R5 is the bit position of the way size increment */
    LDR  r7, =0x7FFF
    ANDS r7, r7, r1, LSR #13       /* R7 is the max number of the index size */
Loop2:
   MOV  r9, r4                      /* R9 working copy of the max way size  */

Loop3:
    ORR  r11, r10, r9, LSL r5 /* Factor in the Way and cache number into R11 */
    ORR  r11, r11, r7, LSL r2                    /* Factor in the Set number */
    MCR  p15, 0, r11, c7, c14, 2             /* Clean & Invalidate by Set/Way (DCISW) */
    SUBS r9, r9, #1                              /* Decrement the Way number */
    BGE  Loop3
    SUBS r7, r7, #1                              /* Decrement the Set number */
    BGE  Loop2
Skip:
    ADD  r10, r10, #2                          /* increment the cache number */
    CMP  r3, r10
    BGT  Loop1
Finished:
    MOV  r10, #0			/* swith back to cache level 0 */
    MCR  p15, 2, r10, c0, c0, 0		/* select current cache level in CSSELR*/
    POP  {r4-r5,r7,r9-r11}
    BX	 lr
    .endfunc
//
//
//    .func __invalidate_l1
//__invalidate_l1:
//    PUSH {r4-r5,r7,r9-r11}
//    MOV  r10, #0                       /* R10 holds current cache level << 1 */
//    MCR  p15, 2, r10, c0, c0, 0  /* Write the Cache Size selection  (CSSELR) */
//    ISB                     /* ISB to sync the change to the CacheSizeID reg */
//    MRC  p15, 1, r1, c0, c0, 0       /* Reads current Cache Size ID (CCSIDR) */
//    AND  r2, r1, #7                         /* Extract the line length field */
//    ADD  r2, r2, #4      /* Add 4 for the line length offset (log2 16 bytes) */
//    LDR  r4, =0x3FF
//    ANDS r4, r4, r1, LSR #3          /* R4 is the max number on the way size */
//    CLZ  r5, r4          /* R5 is the bit position of the way size increment */
//    LDR  r7, =0x7FFF
//    ANDS r7, r7, r1, LSR #13       /* R7 is the max number of the index size */
//ILoop1:
//    MOV  r9, r4                      /* R9 working copy of the max way size  */

//ILoop2:
//    ORR  r11, r10, r9, LSL r5 /* Factor in the Way and cache number into R11 */
//    ORR  r11, r11, r7, LSL r2                    /* Factor in the Set number */
//    MCR  p15, 0, r11, c7, c6, 2             /* Invalidate by Set/Way (DCISW) */
//    SUBS r9, r9, #1                              /* Decrement the Way number */
//    BGE  ILoop2
//    SUBS r7, r7, #1                              /* Decrement the Set number */
//    BGE  ILoop1
//    POP  {r4-r5,r7,r9-r11}
//    BX	 lr
//    .endfunc




/******************************************************************************/
/* This code provides basic global enable for Cortex-A7 cache.                */
/* It also enables branch prediction                                          */
/* This code must be run from a privileged mode                               */
/******************************************************************************/
.func L1CacheInit
L1CacheInit:

/******************************************************************************/
/* Enable caches                                                              */
/* Caches are controlled by the System Control Register:                      */
/******************************************************************************/
    MRC  p15, 0, r0, c1, c0, 0			              /* Read CP15 register 1 */
    ORR  r0, r0, #(0x1 << 12)			                    /* Enable I Cache */
    ORR  r0, r0, #(0x1 << 2)			                    /* Enable D Cache */
    MCR  p15, 0, r0, c1, c0, 0			             /* Write CP15 register 1 */

/******************************************************************************/
/* Enable Program Flow Prediction                                             */
/*                                                                            */
/* Branch prediction is controlled by the System Control Register:            */
/* Set Bit 11 to enable branch prediction and return                          */
/******************************************************************************/
    MRC  p15, 0, r0, c1, c0, 0		  	      /* Read System Control Register */
    ORR  r0, r0, #(0x1 << 11)
    MCR  p15, 0, r0, c1, c0, 0			     /* Write System Control Register */
    BX   lr

    .endfunc
    .align 4


/* ========================================================================== */
/* initsct                                                               */
/* ========================================================================== */
     .func   initsct
initsct:
init_bss:
    LDR  r0, = __start_BSS_RESET
    LDR  r1, = __stop_BSS_RESET
clear_memory:
    TEQ   r0,r1
    BEQ  finished
    MOVS r3,#0
    STM  r0!,{r3}
    B    clear_memory
finished:
    LDR  r0, = __bss_start__
    LDR  r1, = __bss_end__
bss_clear_memory:
    TEQ   r0,r1
    BEQ  bss_finished
    MOVS r3,#0
    STM  r0!,{r3}
    B    bss_clear_memory
bss_finished:

#ifdef __ISW_NORBOOT__
init_rw:
    PUSH {r4-r10}
    LDR  r1, = __load_start_copy
    LDR  r0, = Image$$XRAM0$$Base
    LDR  r2, = __load_size_copy
copy_memory:
    LDMIA r1!, {r3 - r10}
    STMIA r0!, {r3 - r10}
    SUBS r2, r2, #32
    BGE copy_memory
    POP {r4-r10}
rw_finished:
#endif
    ISB
    BX     lr
    .endfunc
    .end

