/***************************************************************************
*                                                                          *
*                    RTK2UTIL.ASM for THUMB processor mode                 *
*                    JLO, 27/04/2001                                       *
*                                                                          *
****************************************************************************/

    .equ  MODE_MASK               ,       0x1F
    .equ  IRQ_DISABLE             ,       0x80
    .equ  FIQ_DISABLE             ,       0x40
    .equ  Usr32Mode               ,       0x10
    .equ  Sup32Mode               ,       0x13
    .equ  Sys32Mode               ,       0x1F
    .equ  MARKER_SP_OFFSET        ,       8*4
    .equ  MARKED_OFFSET           ,       9*4
    .equ  TASKID_OFFSET           ,       3
    .equ  RTK_STACK_OVERFLOW      ,       190

#ifdef __HW_WATCHDOG_FIQ__
    .equ  INT_DISABLE         ,     IRQ_DISABLE
#else
    .equ  INT_DISABLE         ,     FIQ_DISABLE | IRQ_DISABLE
#endif

      /*********************************************************
      * !!!!8 bytes stack alignment maybe have some problems!!!!
      *  PRESERVE8
      * !!!! area not allocated now!!!!!
      *  AREA |RtkCode|, CODE, READONLY
      **********************************************************/
      .eabi_attribute Tag_ABI_align8_preserved,1

      .global RTK1_ACTIVATE_TASK
      .global RTK1_ACTIVATE_MARKED_TASK
      .global RTK1_ACTIVATE_FIRST_TASK
      .global RtkTaskMarkerCall

      .global __current_sp
      .func __current_sp
 __current_sp:
      MOV      r0, sp
      BX       lr
      .endfunc

#ifdef __RTK_DIAGNOSE_ENHANCE__
        .global RTK_GET_REGISTERS
        .func   RTK_GET_REGISTERS
RTK_GET_REGISTERS:
        IMPORT  Rtk_IsrRegisterSet
        STMDB   sp!, {r0, r1, r2, lr}
        MOV     r0, lr
        LDR     r1, =Rtk_IsrRegisterSet
        ADD     r2, sp, #0x10
        STR     r2, [r1], #4
        MRS     r2, cpsr
        STMIA   r1!, {r2, r4-r12}
        STR     r0, [r1]
        LDMIA   sp!, {r0, r1, r2, lr}
        BX      lr
        .endfunc
#endif

/**********************
   Task activation
***********************/
#ifdef __MMU_STACK_PROTECTION__
	.func RTK1_ACTIVATE_TASK
RTK1_ACTIVATE_TASK:

        MRS     a3, cpsr                        // save flags and state
        STMDB   sp!, {a3, r4-r12, lr}           // save registers and flags

        /* Context switch: RTK1_ACTIVATE_TASK(current, next)
         * 1. Enable next call stack AP to RW
         * 2. Context switch
         * 3. Disable current call stack AP
         */

        STR     sp, [a1, #8]                    // save stack pointer
        LDR     sp, [a2, #8]                    // restore stack pointer

        PUSH    {lr, a1-a4}
        //mmu_disableTaskStack(current->Id);
        LDRB    a1, [a1, #3]
        BL      mmu_disableTaskStack
        POP     {lr, a1-a4}

        LDR     a3, [a2, #12]                   // point to PC

        CMP     a3, #0
        BEQ     __NotFirstStart                 // first starting ?

        MOV     a3, #IRQ_DISABLE |  Sys32Mode   // start mode = it disabled, Sys32
        MSR     CPSR_cxsf, a3
        LDR     a3, [a2, #12]                   // a3 = new pc
        MOV     a4, #0
        STR     a4, [a2, #12]                   // set not first starting
        MOV     a4, #Sys32Mode                  // start mode = it allowed, Sys32
        MSR     CPSR_cxsf, a4
        BX      a3                              // jump to routine

__NotFirstStart:                                // no
        LDMIA   sp!, {a3, r4-r12, lr}           // restore registers
        MSR     CPSR_cxsf, a3                   // restore flags
        BX      lr				// return
        .endfunc

#else
	.func RTK1_ACTIVATE_TASK
RTK1_ACTIVATE_TASK:
        MRS     a3, cpsr                        // save flags and state
        STMDB   sp!, {a3, r4-r12, lr}           // save registers and flags
        STR     sp, [a1]                        // save stack pointer

        LDR     sp, [a2]                        // restore stack pointer
        LDR     a3, [a2, #4]                    // point to PC
        CMP     a3, #0
        BEQ     __NotFirstStart                 // first starting ?

        MOV     a3, #IRQ_DISABLE |  Sys32Mode     // start mode = it disabled, Sys32
        MSR     CPSR_cxsf, a3
        LDR     a3, [a2, #4]                    // a3 = new pc
        MOV     a4, #0
        STR     a4, [a2, #4]                    // set not first starting
        MOV     a4, #Sys32Mode                  // start mode = it allowed, Sys32
        MSR     CPSR_cxsf, a4
        BX      a3                              // jump to routine

__NotFirstStart:                                // no
        LDMIA   sp!, {a3, r4-r12, lr}           // restore registers
        MSR     CPSR_cxsf, a3                   // restore flags
        BX      lr                              // return
        .endfunc

#endif  // __MMU_STACK_PROTECTION__
/*****************************************
   Task activation w/ jump to marked task
*****************************************/
        .func RTK1_ACTIVATE_MARKED_TASK
RTK1_ACTIVATE_MARKED_TASK:
        MRS     a3, cpsr                        // save flags and state
        STMDB   sp!, {a3, r4-r12, lr}           // save registers and flags
        STR     sp, [a1]                        // save stack pointer

        MOV     sp, a2                          // restore stack pointer
        MOV     a2, #1                          // set jump flag

        #if __THUMB__
        LDR     r0, [sp]
        BX      r0
        #else
        LDR     pc, [sp]                        // do the jump to startup
        #endif
        .endfunc

/***************************
*  First task activation
****************************/
        .func RTK1_ACTIVATE_FIRST_TASK
RTK1_ACTIVATE_FIRST_TASK:
        #ifdef __RTK_STACK_DIAGNOSE__
        MOV     a3, #INT_DISABLE | Sys32Mode    // disable IRQ&FIQ interrupt
        #else
        MOV     a3, #Sys32Mode                  // start mode = it allowed, Sup32
        #endif
        MSR     CPSR_cxsf, a3

        LDR     sp, [a1]                        // set stack pointer

        #ifdef __RTK_STACK_DIAGNOSE__
        MOV     a3, #Sys32Mode                  // start mode = it allowed, Sup32
        MSR     CPSR_cxsf, a3
        #endif

        LDR     a3, [a1, #4]                    // a3 = new pc
        MOV     a4, #0
        STR     a4, [a1, #4]                    // set not first starting
        #if __THUMB__
        ADR     a2, Rtk2ActivateFirstThumb + 1
        BX      a2
        //CODE16                                  ; @@ THUMB16 MODE @@
        .code 16
Rtk2ActivateFirstThumb:
        #endif
        BX      a3                              // jump to routine
        .hword     0x0000                       // insert padding for compiler warning
        .endfunc

        //CODE32                                  ; @@ ARM32 MODE @@
        //ALIGN
        .code 32
        .align

/*****************************************************************
* Re-entrant calls with marker and single stack
*
*       RtkTaskMarkerCall(void *f, u8 n, ...)
*
*               where   f : function to be called
*                       n : number of parameters
******************************************************************/
        //CODE32                                  ; @@ ARM32 MODE @@
        //ALIGN
        .code 32
        .align


    .func RtkTaskMarkerCall
RtkTaskMarkerCall:
        /*********************************************************
         *       first set standard stack so that
         *       fp      <== sp points there
         *       ip      (contains sp on entry)
         *       lr
         *       pc      <== fp points there
         *       p0      <== first parameter of called function
         *       .
         *       pn
         *********************************************************/
        MOV     ip, sp
        STMDB   sp!, {r2, r3}
        STMDB   sp!, {fp, ip, lr, pc}
        SUB     fp, ip, #12

        // set the task's context addressing in r0
        STR     r0, [sp, #-4]!                  // save r0 before use (!)
        LDR     r0, =Rtk_PtrCurrentTask         // r0 = @rtk_ps_CurrentTask
        LDR     r0, [r0]                        // r0 = *Rtk_PtrCurrentTask
        ADD     r0, r0, #MARKER_SP_OFFSET

        // the tricky part wich allows a kind of <setjmp/longjmp>
        // be careful because the pc is +8 from the instruction using it.
        STMDB   sp!, {r0-r3, v1-v7, fp}         // save all registers because further
                                                // interruptions can be anywhere
        MRS     r1, cpsr                        // get the flags
        STR     r1, [sp, #-4]!                  // and store them (for interrupts)
        STR     pc, [sp, #-4]!                  // the pc value is @__MarkerBack
        STR     sp, [r0]                        // store the sp in task's context
        MOV     r1, #0                          // with this, we know where we come from

__MarkerBack :
        /*************************************************************
        *  If a restart occurs, it will take place there and r0 == 1
        *  0 otherwise. The stack looks like :
        *       pc      <== sp points there
        *       cpsr
        *       r0
        *       .
        *       r3
        *       v1
        *       .
        *       v7
        *       fp
        *       r0
        **************************************************************/
        LDR     r0, [sp, #4]                      // restore cpsr
        MSR     CPSR_cxsf, r0
        ADD     fp, sp, #8                        // [fp] ==> r0 in stack
        LDMIA   fp, {r0-r3, v1-v7, fp}            // restore all regs

        /* now, this task has the right to own the marker */
        ADD     r0, r0, #MARKED_OFFSET - MARKER_SP_OFFSET
        MOV     r3, #1
        STRB    r3, [r0]                        // this task uses a marker

        /********************************************************************
        * and it can tells the world it owns it
        * note that if this task is interrupted before the completion of
        * this lines, it will restart from the jump point so no big deal ...
        *********************************************************************/
        ADD     r0, r0, #TASKID_OFFSET - MARKED_OFFSET
        LDRB    r3, [r0]                        // get task ID
        LDR     r0, =Rtk_TaskMarkerOwner
        STRB    r3, [r0]

        /******************************************************
        * now set the new stack
        * don't care if we come directly or from a longjmp
        *       r0 : function to call
        *       r1 : number of parameters
        *       r2 : free
        *       r3 : free
        *******************************************************/
        LDR     r0, [sp, #14*4]                 // restore r0 on old stack
        LDR     r3, =Rtk_PtrMarkerStack         // r3 = @Rtk_PtrMarkerStack
        LDR     sp, [r3]                        // sp = * Rtk_PtrMarkerStack
        ADD     r3, fp, r1, LSL #2              // r3 = fp + 4*n ==> last param to transfer (JLO)
        SUBS    r1, r1, #4
        BLE     __Marker4Param                  // do we have more than 4 parameters ?
__MarkerStackLoop:                              // do the transfer
        LDR     r2, [r3], #-4
        STR     r2, [sp, #-4]!
        SUBS    r1, r1, #1
        BNE     __MarkerStackLoop

        /**********************************************
        * now transfer the register parameters
        * it can be less than 4, but who cares ?
        ************************************************/
__Marker4Param:
        STR     r0, [sp, #-4]!                  // store function to be called address
        LDR     r0, [fp, #4]                    // fp ==> 4 bytes over 1st param
        LDR     r1, [fp, #4*2]
        LDR     r2, [fp, #4*3]
        LDR     r3, [fp, #4*4]

        #if __THUMB__
        /* and then call the function */
        ADR     r2, Rtk2TaskMarkerCallThumb + 1
        BX      r2

        //CODE16                                  ; @@ THUMB16 MODE @@
        .code 16
Rtk2TaskMarkerCallThumb:
        //LDR     r0, [sp]
        //SUB     r0, #4
        //MOV     lr, pc
        //MOV     pc, r0                          ; do the jump to startup

        ADR     r2, Rtk2TaskMarkerEpilogue
        MOV     lr, r2
        POP     {pc}
        DCW     0x0000                          // insert padding for compiler warning

        //CODE32                                  ; @@ ARM32 MODE @@
        //ALIGN
        .code 32
        .align
        #else
        /* And then call the function */
        MOV     lr, pc
        LDR     pc, [sp], #4
        #endif

        /********************************************************************************
        * We must disable IT here because if an IT occurs after Marked
        * has been set to 0 the next scheduling will failed since Reg.SP
        * will be update with current SP which is the csn1 SP because
        * scheduling will call RTK1_ACTIVATE_TASK instead of RTK1_ACTIVATE_MARKED_TASK
        *********************************************************************************/
Rtk2TaskMarkerEpilogue:
        MRS     r3, cpsr                        // get cpsr
        MOV     r4, r3                          // keep flags
        ORR     r4, r4, #INT_DISABLE            // disable interrupts
        MSR     CPSR_cxsf, r4                   // set cpsr

        /**************************************
        * at least we are back ...
        * just have to un-mark the task
        **************************************/
        LDR     r1, =Rtk_PtrCurrentTask         // only r0 is usefull
        LDR     r1, [r1]                        // r1 = *rtk_ps_CurrentTask
        ADD     r1, r1, #MARKED_OFFSET
        MOV     r2, #0
        STRB    r2, [r1]                        // ok, no more marked

        /* check stack overflow */
        LDR     r1, =Rtk_PtrMarkerStack         // r1 = @Rtk_PtrMarkerStack
        LDR     r2, [r1]                        // r2 = * Rtk_PtrMarkerStack
        LDR     r1, =cus_MarkerStackSize
        LDRH    r1, [r1]
        BIC     r1, r1, #3                      // align stack size on 32 bits
        SUB     r2, r2, r1                      // r2 = @top of stack
        LDR     r2, [r2]                        // r2 = last stack 32 bits word
        LDR     r1, [pc, #__MarkerStackValue-.-8]
        CMP     r2, r1                          // and compare value
        BEQ     __MarkerEnd

        MOV     r0, #RTK_STACK_OVERFLOW
        MOV     r1, #-1
        B       RtkExceptionRoutine

        /************************************************************************
        * doing a normal return will restore everything as the fp as been
        * preserved along all those stuff, so the caller's stack is still
        * accessible
        * also the sp value used for the call is now don't care, so no need
        * to restore that stack and the return value is in r0 (if any)
        ************************************************************************/
__MarkerEnd:
        LDMDB   fp, {fp, sp, lr}

        /***************************************
        * Marked is 0 and SP has been restored.
        * We can safely allow IT now
        ****************************************/
        MRS     r4, cpsr                        // get cpsr
        ORR     r4, r4, #INT_DISABLE            // disable interrupts
        MSR     CPSR_cxsf, r4
        ORR     r3, r3, #MODE_MASK              // keep mode
        AND     r4, r4, r3                      // restore flags
        MSR     CPSR_cxsf, r4                   // set cpsr
        BX      lr

__MarkerStackValue:
        .word     0x55555555
        .endfunc

/*============================================================================*/
/*                       interrupt managment                                  */
/*============================================================================*/
        .global RTK2_ENABLE
        .global RTK2_DISABLE
        .global RTK2_DISABLE_IRQ
        .global RTK2_ENABLE_IRQ
        .global RTK2_TILT_INT

        #ifdef __SEPARATE_INTERRUPT_API__
        .global RTK2_ENABLE_K
        .global RTK2_DISABLE_K
        #endif

        .global RTK2_ENABLE_K_R
        .global RTK2_DISABLE_K_R

        #ifdef __SEPARATE_INTERRUPT_API__
 /* Make sure consistent with Kernel.h  */
.equ    TBU_FINT_IT_MSK ,      0x0001<<21
.eqe    TICK_COUNT_MASK ,      0x00FFFFFF
        #endif

/*******************
* Interrupt enable
********************/
        #ifdef __SEPARATE_INTERRUPT_API__
        .func RTK2_ENABLE
RTK2_ENABLE:
        /* if calling cpsr is not in task mode, just switch to kernel API */
        MRS     r2, cpsr
        AND     r2, r2, #Sys32Mode
        CMP     r2, #Sys32Mode
        BNE     RTK2_ENABLE_K

        #if defined(__INTERRUPT_INTEGRITY_PROTECT__) || defined(__SEPARATE_INTERRUPT_API_PROFILE__)
        PUSH    {lr}                            // Will change on calling C routine
        #endif

        MRS     a3, cpsr
        ORR     a4, a3, #INT_DISABLE
        MSR     CPSR_cxsf, a4                   // Disable interrupt first

        LDR     a4, =g_ptW5IrqControl
        LDR     a4, [a4]
        STR     a1, [a4, #28]
        STR     a2, [a4, #32]                   // Store u32_mask0 and u32_mask1

        #ifdef __SEPARATE_INTERRUPT_API_PROFILE__
        PUSH    {r4}
        LDR     a4, =sys_EiuQbCount1            // Profile information start
        LDR     r4, =g_ptW5TbuC
        LDR     r4, [r4]
        LDR     r4, [r4, #8]
        STR     r4, [a4]
        #endif

        ORR     a1, a1, #TBU_FINT_IT_MSK
        CMP     a1, #TBU_FINT_IT_MSK

        BNE     __DisableIntFlag
        CMP     a2, #0
        BNE     __DisableIntFlag
        B       __NoDisableIntFlag

__DisableIntFlag:
        LDR	a1, =g_nSysDisableInterrupt      // Save flag
        MOV	a2, #0
        STR	a2, [a1]

        LDR     a1, =Rtk_RegionCount            // Rtk_RegionCount--
        LDRH    a2, [a1]
        SUB     a2, a2, #1
        STRH    a2, [a1]

        #ifndef __INTERRUPT_INTEGRITY_PROTECT__
	LDR     a1, =sys_diProfile
	LDRB    a2, [a1]
	CMP     a2, #1
	BNE     __without_profile_INT_2
        #endif

        LDR     a1, =g_ptW5TbuC
        LDR     a1, [a1]
        LDRH    a1, [a1, #8]
        LDR     a2, =sys_diQbCount4
        STRH    a1, [a2]                        // Store QB count 4 as g_ptW5TbuC->u16_QbCnt

        LDR     a1, =sys_diLr
        STR     lr, [a1]                        // Store caller

        PUSH    {lr, a1-a4}
        BLX     checkDiTickCount                // Call check function
        POP     {lr, a1-a4}

__without_profile_INT_2:

__NoDisableIntFlag:
        #ifdef __SEPARATE_INTERRUPT_API_PROFILE__
        LDR     a1, =sys_EiuQbCount2            // Profile information end
        LDR     a2, =g_ptW5TbuC
        LDR     a2, [a2]
        LDR     a2, [a2, #8]
        STR     a2, [a1]

        PUSH    {a3}
        BLX     profileEiuQbCount
        POP     {a3}

        POP     {r4}
        #endif  // __SEPARATE_INTERRUPT_API_PROFILE__

        MSR     CPSR_cxsf, a3                   // Restore cpsr

        #if defined(__INTERRUPT_INTEGRITY_PROTECT__) || defined(__SEPARATE_INTERRUPT_API_PROFILE__)
        POP     {lr}
        #endif

        BX      lr
        .endfunc

       // !!! code section not specified now !!!!
       // AREA |.RoCodeOnBoot|, CODE, READONLY

    .func RTK2_ENABLE_K
RTK2_ENABLE_K:
        #if defined(__INTERRUPT_INTEGRITY_PROTECT__)|| defined(__SEPARATE_INTERRUPT_API_PROFILE__)
        PUSH    {lr}                            // Will change on calling C routine
        #endif

        MRS     a2, cpsr                        // get cpsr
        ORR     a2, a2, #INT_DISABLE            // disable interrupts
        MSR     CPSR_cxsf, a2
        ORR     a1, a1, #MODE_MASK              // keep mode
        AND     a2, a2, a1                      // restore flags

        #ifdef __SEPARATE_INTERRUPT_API_PROFILE__
        /* Profile information start section */
        //LDR     a3, =sys_EikQbCountTemp         ; Store temp QB count
        LDR     a3, =sys_EikQbCount1            ; Profile information start
        LDR     a4, =g_ptW5TbuC
        LDR     a4, [a4]
        LDR     a4, [a4, #8]
        STR     a4, [a3]
        #endif

        AND     a1, a1, #INT_DISABLE            // Test if IRQ and FIQ disabled in a1
        CMP     a1, #INT_DISABLE
        BEQ     __NoDisableIntFlag_k            // Already disabled before

__DisableIntFlag_k:

        /* Temp move here to catch disable interrupt lr */
        #ifdef __RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__
        LDR	a3, =RtkRegisters
        MOV     a4, #0
        STR	a4, [a3], #4
        STR	a4, [a3], #4
        STR	a4, [a3], #4
        STR     a4, [a3], #4                    // All clear
        #endif

        LDR	a1, =g_nSysDisableInterrupt_k    // Save flag
        MOV	a3, #0
        STR	a3, [a1]

        #ifndef __INTERRUPT_INTEGRITY_PROTECT__
        LDR     a1, =sys_diProfile_K
        LDRB    a3, [a1]
        CMP     a3, #1
	      BNE     __without_profile_INT_K_2
        #endif

        LDR     a1, =g_ptW5TbuC
        LDR     a1, [a1]
        LDRH    a1, [a1, #8]
        LDR     a3, =sys_diQbCount2
        STRH    a1, [a3]                        // Store QB count 2

        LDR     a3, =sys_diLr_K
        STR     lr, [a3]                        // Store caller

        PUSH    {lr, a1-a4}
        BLX     checkDiQbCount                  // Call check function
        POP     {lr, a1-a4}

__without_profile_INT_K_2:

__NoDisableIntFlag_k:
        #ifdef __SEPARATE_INTERRUPT_API_PROFILE__
        LDR     a1, =sys_EikQbCount2            // Profile information end
        LDR     a3, =g_ptW5TbuC
        LDR     a3, [a3]
        LDR     a3, [a3, #8]
        STR     a3, [a1]

        PUSH    {a2}
        BLX     profileEikQbCount
        POP     {a2}
        #endif // __SEPARATE_INTERRUPT_API_PROFILE__

        /**************************************************************************
        ; Legacy information
        ;IF :DEF:__REAL_TIME_PROBLEM_DIAGNOSE__
        ;MRS     a2, cpsr
        ;LDR     a1, =g_nSysCpsrSnapShot           ; Store CPSR such that later we can
        ;STR     a2, [a1]                        ; know if IRQ/FIQ is still disabled.
        ;ENDIF

        ;IF :DEF:__RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__
        ;STMDB	r13!, {r0-r12,lr}
        ;MRS	r0, cpsr
        ;STMDB	r13!, {r0}
        ;BL	saveEnableTime
        ;LDMIA   r13!, {r0}
        ;MSR	CPSR_cxsf, r0
        ;LDMIA	r13!, {r0-r12,lr}
        ;ENDIF
        ****************************************************************************/

        #ifdef __RTK_PROFILE_ENHANCE__
        LDR	a1, =sampling_LR1
        STR     lr, [a1]
        #endif

        MSR     CPSR_cxsf, a2                   // set cpsr

        #if defined(__INTERRUPT_INTEGRITY_PROTECT__)|| defined(__SEPARATE_INTERRUPT_API_PROFILE__)
        POP     {lr}
        #endif

        BX      lr
        .endfunc

        #ifdef __RTK_PROFILE_ENHANCE__
        .global RTK2_ENABLE_K_END
        .func RTK2_ENABLE_K_END
RTK2_ENABLE_K_END:

        .endfunc
        #endif

  // !!! code section not specified now !!!!
 //       AREA |tuil|, CODE, READONLY

        #else // __SEPARATE_INTERRUPT_API__

/* Original enable interrupt API */
    .func RTK2_ENABLE
RTK2_ENABLE:
        MRS     a2, cpsr                        // get cpsr
        ORR     a2, a2, #INT_DISABLE            // disable interrupts
        MSR     CPSR_cxsf, a2
        ORR     a1, a1, #MODE_MASK              // keep mode
        AND     a2, a2, a1                      // restore flags
        MSR     CPSR_cxsf, a2                   // set cpsr

        #ifdef __REAL_TIME_PROBLEM_DIAGNOSE__
        MRS     a2, cpsr
        LDR     a1, =g_nSysCpsrSnapShot           // Store CPSR such that later we can
        STR     a2, [a1]                        // know if IRQ/FIQ is still disabled.
        #endif

        #ifdef __RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__
        STMDB   r13!, {r0-r12,lr}
        MRS     r0, cpsr
        STMDB   r13!, {r0}
        BL      saveEnableTime
        LDMIA   r13!, {r0}
        MSR     CPSR_cxsf, r0
        LDMIA   r13!, {r0-r12,lr}
        #endif

        BX      lr
        .endfunc
        #endif // __SEPARATE_INTERRUPT_API__

/*******************
* Interrupt disable
********************/

        #ifdef __SEPARATE_INTERRUPT_API__
        .func RTK2_DISABLE
RTK2_DISABLE:
        /* if calling cpsr is not in task mode, just switch to kernel API */
        MRS     r2, cpsr
        AND     r2, r2, #Sys32Mode
        CMP     r2, #Sys32Mode
        BNE     RTK2_DISABLE_K

        #ifdef __SEPARATE_INTERRUPT_API_PROFILE__
        PUSH    {lr}
        #endif

        /* TODO: Temp modify for QB count profile*/
        //PUSH    {r4, r5}
        PUSH    {r4}                            // Store used registers

        /* Mask interrupt first */
        MRS     r4, cpsr
        ORR     a3, r4, #INT_DISABLE
        MSR     CPSR_cxsf, a3

        LDR     a3, =g_ptW5IrqControl
        LDR     a3, [a3]
        LDR     a1, [a3, #28]                   // Get u32_Mask0 and u32_Mask1
        LDR     a2, [a3, #32]

        AND     a4, a1, #TBU_FINT_IT_MSK
        STR     a4, [a3, #28]
        MOV     a4, #0
        STR     a4, [a3, #32]                   // Store u32_Mask0 and u32_Mask1

        #ifdef __SEPARATE_INTERRUPT_API_PROFILE__
        LDR     a3, =sys_DiuQbCount1            // Profile information start
        LDR     a4, =g_ptW5TbuC
        LDR     a4, [a4]
        LDR     a4, [a4, #8]
        STR     a4, [a3]
        #endif

        AND     a4, a1, #TBU_FINT_IT_MSK
        EOR     a4, a4, a1
        CMP     a4, #0

        BNE     __EnableIntFlag
        CMP     a2, #0
        BNE     __EnableIntFlag
        B       __NoEnableIntFlag

__EnableIntFlag:
        LDR	a4, =g_nSysDisableInterrupt      // Save flag
        MOV	a3, #1
        STR	a3, [a4]

        LDR     a4, =Rtk_RegionCount            // Rtk_RegionCount++
        LDRH    a3, [a4]
        ADD     a3, a3, #1
        STRH    a3, [a4]

        LDR     a3, =g_nSysDisableIntIndex
        LDR     a4, [a3]
        LDR     a3, =g_anSysDisableIntCpsr
        STR     r4, [a3, a4, LSL #2]            // Save cpsr
        LDR     a3, =g_apSysDisableIntLr
        STR     lr, [a3, a4, LSL #2]            // Save Lr

        ADD     a4, a4, #1
        AND     a4, a4, #0x3
        LDR     a3, =g_nSysDisableIntIndex
        STR	a4, [a3]

        #ifndef __INTERRUPT_INTEGRITY_PROTECT__
	LDR     a3, =sys_diProfile
	LDRB    a4, [a3]
	CMP     a4, #1
	BNE     __without_profile_INT_1
        #endif

        LDR     a3, =g_ptW5TbuC
        LDR     a3, [a3]
        LDRH    a3, [a3, #8]
        LDR     a4, =sys_diQbCount3
        STRH    a3, [a4]                        // Store QB count 1


__without_profile_INT_1:

__NoEnableIntFlag:
        #ifdef __SEPARATE_INTERRUPT_API_PROFILE__
        LDR     a3, =sys_DiuQbCount2            // Profile information end
        LDR     a4, =g_ptW5TbuC
        LDR     a4, [a4]
        LDR     a4, [a4, #8]
        STR     a4, [a3]

        PUSH    {a1, a2}
        BLX     profileDiuQbCount
        POP     {a1, a2}
        #endif

        MSR     CPSR_cxsf, r4                   // Restore cpsr
        /* TODO: Temp modify for QB count profile */
        //POP     {r4, r5}
        POP     {r4}                            // Restore used registers

        #ifdef __SEPARATE_INTERRUPT_API_PROFILE__
        POP    {lr}
        #endif
        BX      lr
        ENDP

         // !!! code section not specified now !!!!
        //AREA |.RoCodeOnBoot|, CODE, READONLY

        .func RTK2_DISABLE_K
RTK2_DISABLE_K:
        #ifdef __SEPARATE_INTERRUPT_API_PROFILE__
        PUSH    {lr}
        #endif

        MRS     a1, cpsr                        // get cpsr
        MOV     a2, a1                          // keep flags
        ORR     a2, a2, #INT_DISABLE            // disable interrupts
        MSR     CPSR_cxsf, a2                   // set cpsr

        #ifdef __SEPARATE_INTERRUPT_API_PROFILE__
        LDR     a3, =sys_DikQbCount1            // Profile information start
        LDR     a4, =g_ptW5TbuC
        LDR     a4, [a4]
        LDR     a4, [a4, #8]
        STR     a4, [a3]
        #endif

        CMP     a1, a2
        BEQ     __NoEnableIntFlag_k             // Already disabled before

__EnableIntFlag_k:
        /* Temp move here to catch disable interrupt lr */
        #ifdef __RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__
        LDR	a3, =RtkRegisters
        STR	sp, [a3], #4
        STR	lr, [a3], #4
        STR	lr, [a3], #4
        STR     a1, [a3], #4                    // a1 = cpsr
        #endif

        LDR	a2, =g_nSysDisableInterrupt_k
        MOV	a3, #1
        STR	a3, [a2]                        // Save flag

        LDR     a2, =g_nSysDisableIntIndex_k
        LDR     a3, [a2]
        LDR     a2, =g_anSysDisableIntCpsr_k
        STR     a1, [a2, a3, LSL #2]            // Save cpsr
        LDR     a2, =g_apSysDisableIntLr_k
        STR     lr, [a2, a3, LSL #2]            // Save Lr

        ADD     a3, a3, #1
        AND     a3, a3, #0x3
        LDR     a2, =g_nSysDisableIntIndex_k
        STR	a3, [a2]

        #ifndef __INTERRUPT_INTEGRITY_PROTECT__
        LDR     a2, =sys_diProfile_K
        LDRB    a3, [a2]
        CMP     a3, #1
	      BNE     __without_profile_INT_K_1
        #endif

        LDR     a2, =g_ptW5TbuC
        LDR     a2, [a2]
        LDRH    a2, [a2, #8]
        LDR     a3, =sys_diQbCount1
        STRH    a2, [a3]                        // Store QB count 1

__without_profile_INT_K_1:

__NoEnableIntFlag_k:
        #ifdef __SEPARATE_INTERRUPT_API_PROFILE__
        LDR     a3, =sys_DikQbCount2            // Profile information end
        LDR     a4, =g_ptW5TbuC
        LDR     a4, [a4]
        LDR     a4, [a4, #8]
        STR     a4, [a3]

        PUSH    {a1}
        BLX     profileDikQbCount
        POP     {a1}

        MOV     a2, #0                          // Restore
        #endif // __SEPARATE_INTERRUPT_API_PROFILE__

        /***********************************************************************************************
        ;Legacy information
        ;IF :DEF:__REAL_TIME_PROBLEM_DIAGNOSE__
        ;PUSH    {a3}                            ; Free up a3 first.
                                                ; a2 is clear for use (while a1 is not).
        ;LDR     a2, =g_nSysLastPcDisablingItIndex ; Load current index to a3
        ;LDR     a3, [a2]
        ;LDR     a2, =g_anSysLastPcDisablingItCpsr  ; Store CPSR such that later we can
        ;STR     a1, [a2, a3, LSL #2]            ; know if IRQ/FIQ is still disabled.
        ;LDR     a2, =g_apSysLastPcDisablingIt      ; Store LR, which record the PC before
        ;STR     lr, [a2, a3, LSL #2]            ; calling RTK2_DISABLE
        ;ADD     a3, a3, #1                      ; Increment the index
        ;AND     a3, a3, #0x3                    ; Index modulo by 4 (0~3)
        ;LDR     a2, =g_nSysLastPcDisablingItIndex ; Save index back to g_nSysLastPcDisablingItIndex
        ;STR     a3, [a2]

        ;LDR     a2, =g_nSysCpsrSnapShot
        ;STR     a1, [a2]

        ;POP     {a3}
        ;ENDIF

        ;IF :DEF:__RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__
        ;LDR	a2, =RtkRegisters
        ;STR	sp, [a2], #4
        ;STR	lr, [a2], #4
        ;STR	lr, [a2], #4
        ;STR     a1, [a2], #4
        ;STMDB	r13!, {r0-r12,lr}
        ;MRS	r0, cpsr
        ;STMDB	r13!, {r0}
        ;BL	saveDisableTime
        ;LDMIA   r13!, {r0}
        ;MSR	CPSR_cxsf, r0
        ;LDMIA	r13!, {r0-r12,lr}
        ;ENDIF
        *************************************************************************************************/

        #ifdef __SEPARATE_INTERRUPT_API_PROFILE__
        POP    {lr}
        #endif
        BX      lr
        .endfunc

        // !!! code section not specified now !!!!
        //AREA |util|, CODE, READONLY

        #else // __SEPARATE_INTERRUPT_API__

/* Original disable interrupt API*/
    .func RTK2_DISABLE
RTK2_DISABLE:
        MRS     a1, cpsr                        // get cpsr
        MOV     a2, a1                          // keep flags
        ORR     a2, a2, #INT_DISABLE            // disable interrupts
        MSR     CPSR_cxsf, a2                   // set cpsr

        #ifdef __REAL_TIME_PROBLEM_DIAGNOSE__
        PUSH    {a3}                            // Free up a3 first.
                                                // a2 is clear for use (while a1 is not).
        LDR     a2, =g_nSysLastPcDisablingItIndex // Load current index to a3
        LDR     a3, [a2]
        LDR     a2, =g_anSysLastPcDisablingItCpsr  // Store CPSR such that later we can
        STR     a1, [a2, a3, LSL #2]            // know if IRQ/FIQ is still disabled.
        LDR     a2, =g_apSysLastPcDisablingIt      // Store LR, which record the PC before
        STR     lr, [a2, a3, LSL #2]            // calling RTK2_DISABLE
        ADD     a3, a3, #1                      // Increment the index
        AND     a3, a3, #0x3                    // Index modulo by 4 (0~3)
        LDR     a2, =g_nSysLastPcDisablingItIndex // Save index back to g_nSysLastPcDisablingItIndex
        STR     a3, [a2]

        LDR     a2, =g_nSysCpsrSnapShot
        STR     a1, [a2]

        POP     {a3}
        #endif
        #ifdef __RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__
        LDR     a2, =RtkRegisters
        STR     sp, [a2], #4
        STR     lr, [a2], #4
        STR     lr, [a2], #4
        STR     a1, [a2], #4
        STMDB   r13!, {r0-r12,lr}
        MRS     r0, cpsr
        STMDB   r13!, {r0}
        BL      saveDisableTime
        LDMIA   r13!, {r0}
        MSR     CPSR_cxsf, r0
        LDMIA   r13!, {r0-r12,lr}
        #endif
        BX      lr
        .endfunc

        #endif // __SEPARATE_INTERRUPT_API__

#ifdef __FIXME__
/* Reduced version of kernel disable interrupt */
    .func RTK2_DISABLE_K_R
RTK2_DISABLE_K_R:

        MRS     a1, cpsr                        // get cpsr
        MOV     a2, a1                          // keep flags
        ORR     a2, a2, #INT_DISABLE            // disable interrupts
        MSR     CPSR_cxsf, a2                   // set cpsr

        CMP     a1, a2
        BEQ     __NoProfileDisableTime_d

__ProfileDisableTime_d:
        #ifndef __INTERRUPT_INTEGRITY_PROTECT__
        LDR     a2, =sys_diProfile_K
        LDRB    a3, [a2]
        CMP     a3, #1
        BNE     __NoProfileDisableTime_d
        #endif

        LDR     a2, =g_ptW5TbuC
        LDR     a2, [a2]
        LDRH    a2, [a2, #8]
        LDR     a3, =sys_diQbCount1
        STRH    a2, [a3]                        // Store QB count 1

__NoProfileDisableTime_d:
        BX      lr
        .endfunc

/* Reduced version of kernel enable interrupt */
    .func RTK2_ENABLE_K_R
RTK2_ENABLE_K_R:

        MRS     a2, cpsr                        // get cpsr
        ORR     a2, a2, #INT_DISABLE            // disable interrupts
        MSR     CPSR_cxsf, a2
        ORR     a1, a1, #MODE_MASK              // keep mode
        AND     a2, a2, a1                      // restore flags

        AND     a1, a1, #INT_DISABLE            // Test if IRQ and FIQ disabled in a1
        CMP     a1, #INT_DISABLE
        BEQ     __NoProfileDisableTime_e

__ProfileDisableTime_e:
        #ifndef __INTERRUPT_INTEGRITY_PROTECT__
        LDR     a1, =sys_diProfile_K
        LDRB    a3, [a1]
        CMP     a3, #1
        BNE     __NoProfileDisableTime_e
        #endif

        LDR     a1, =g_ptW5TbuC
        LDR     a1, [a1]
        LDRH    a1, [a1, #8]
        LDR     a3, =sys_diQbCount2
        STRH    a1, [a3]                        // Store QB count 2

        LDR     a3, =sys_diLr_K
        STR     lr, [a3]                        // Store caller

        PUSH    {lr, a1-a4}
        BLX     checkDiQbCount                  // Call check function
        POP     {lr, a1-a4}

__NoProfileDisableTime_e:
        MSR     CPSR_cxsf, a2                   // set cpsr
        BX      lr
        .endfunc
#endif

        .func RTK2_DISABLE_IRQ
RTK2_DISABLE_IRQ:
        MRS     a1, cpsr                        // get cpsr
        MOV     a3, a1                          // keep flags
        ORR     a3, a3, #IRQ_DISABLE            // disable interrupts
        MSR     CPSR_cxsf, a3                   // set cpsr
        MOV     a2, #0
        BX      lr
        .endfunc

        .func RTK2_ENABLE_IRQ
RTK2_ENABLE_IRQ:
        MRS     a2, cpsr                        // get cpsr
        ORR     a2, a2, #INT_DISABLE            // disable interrupts
        MSR     CPSR_cxsf, a2
        ORR     a1, a1, #MODE_MASK              // keep mode
        AND     a2, a2, a1                      // restore flags
        MSR     CPSR_cxsf, a2                   // set cpsr
        BX      lr
        .endfunc

/*******************************
* Original disable interrupt API
* we just disable IRQ, not FIQ
********************************/
/*
;RTK2_DISABLE_IRQ PROC
        ;MRS     a1, cpsr                        ; get cpsr
        ;MOV     a2, a1                          ; keep flags
        ;ORR     a2, a2, #IRQ_DISABLE            ; disable interrupts
        ;MSR     CPSR_cxsf, a2                   ; set cpsr

        ;IF :DEF:__REAL_TIME_PROBLEM_DIAGNOSE__
        ;PUSH    {a3}                            ; Free up a3 first.
                                                ; a2 is clear for use (while a1 is not).
        ;LDR     a2, =g_nSysLastPcDisablingItIndex ; Load current index to a3
        ;LDR     a3, [a2]
        ;LDR     a2, =g_anSysLastPcDisablingItCpsr  ; Store CPSR such that later we can
        ;STR     a1, [a2, a3, LSL #2]            ; know if IRQ/FIQ is still disabled.
        ;LDR     a2, =g_apSysLastPcDisablingIt      ; Store LR, which record the PC before
        ;STR     lr, [a2, a3, LSL #2]            ; calling RTK2_DISABLE
        ;ADD     a3, a3, #1                      ; Increment the index
        ;AND     a3, a3, #0x3                    ; Index modulo by 4 (0~3)
        ;LDR     a2, =g_nSysLastPcDisablingItIndex ; Save index back to g_nSysLastPcDisablingItIndex
        ;STR     a3, [a2]
        ;POP     {a3}
        ;ENDIF

        ;BX      lr
        ;ENDP
*/


/*********************
* Interrupt tilt
**********************/
    .func RTK2_TILT_INT
RTK2_TILT_INT:
        MRS     a1, cpsr                        // get cpsr
        BIC     a1, a1, #INT_DISABLE            // enable interrupts
        MSR     CPSR_cxsf, a1                   // set cpsr

        NOP                                     // wait once ...

        ORR     a1, a1, #INT_DISABLE            // disable interrupts
        MSR     CPSR_cxsf, a1                   // set cpsr
        BX      lr
        .endfunc

/*********************
* Get status flag
**********************/
        .global GetStatus
        .func GetStatus
GetStatus:
        MRS     r0, cpsr
        AND     r0, r0, #0xff
        BX      lr
        .endfunc

/*********************
* Get spsr
**********************/
        .global GetSpsr
        .func GetSpsr
GetSpsr:
        MRS     r0, spsr
        AND     r0, r0, #0xff
        BX      lr
        .endfunc

/*********************
* Get Stack Pointer
**********************/
        .global GetSP
        .func GetSP
GetSP:
        MOV     r0, sp
        BX      lr
        .endfunc

/*********************
* Get register in stack.
**********************/
        .global RtkGetCallerInStack
        .func RtkGetCallerInStack
RtkGetCallerInStack:
        MOV     r0, fp
        SUB     r0, r0, #4
        LDR     r0, [r0]
        BX      lr
        .endfunc

/********************************************
*  Get SP and a coherent PC according to SP
********************************************/
        #if 1 //__THUMB__ __FIXME__
        #ifdef __RTK_DIAGNOSE_ENHANCE__
        .global RtkGetARMRegisters               // the input parameter should be u32 array with 20 elements
        .func RtkGetARMRegisters
RtkGetARMRegisters:
        STMDB   sp!, {r0-r3}                    // keep the original register value

        MRS     r1, cpsr
        MOV     r2, r1
        STR     r1, [r0], #4                    // store current mode cpsr, sp, lr
        STR     sp, [r0], #4
        STR     lr, [r0], #4

        BIC     r1, r1, #0x1F                   // switch to FIQ mode
        ORR     r1, r1, #0x11
        MSR     cpsr_c, r1

        MRS     r3, spsr
        STR     r3, [r0], #4                    // store FIQ mode spsr, sp, lr
        STR     sp, [r0], #4
        STR     lr, [r0], #4

        BIC     r1, r1, #0x1F                   // switch to IRQ mode
        ORR     r1, r1, #0x12
        MSR     cpsr_c, r1

        MRS     r3, spsr
        STR     r3, [r0], #4                    // store IRQ mode spsr, sp, lr
        STR     sp, [r0], #4
        STR     lr, [r0], #4

        BIC     r1, r1, #0x1F                   // switch to SPV mode
        ORR     r1, r1, #0x13
        MSR     cpsr_c, r1

        MRS     r3, spsr
        STR     r3, [r0], #4                    // store SPV mode spsr, sp, lr
        STR     sp, [r0], #4
        STR     lr, [r0], #4

        BIC     r1, r1, #0x1F                   // switch to ABT mode
        ORR     r1, r1, #0x17
        MSR     cpsr_c, r1

        MRS     r3, spsr
        STR     r3, [r0], #4                    // store ABT mode spsr, sp, lr
        STR     sp, [r0], #4
        STR     lr, [r0], #4

        BIC     r1, r1, #0x1F                   // switch to UDF mode
        ORR     r1, r1, #0x1B
        MSR     cpsr_c, r1

        MRS     r3, spsr
        STR     r3, [r0], #4                    // store UDF mode spsr, sp, lr
        STR     sp, [r0], #4
        STR     lr, [r0], #4

        ORR     r1, r1, #0x1F                   // switch to SYS mode
        MSR     cpsr_c, r1

        STR     sp, [r0], #4                    // store SYS mode sp, lr
        STR     lr, [r0], #4

        MSR     cpsr_c, r2                      // restore the original mode and return
        LDMIA   sp!, {r0-r3}
        BX      lr
        .endfunc
        #endif


        .global RtkGetSpAndPc
       .func RtkGetSpAndPc
RtkGetSpAndPc:
        LDR     r0, =RtkRegisters
        STR     r13, [r0], #4
        STR     r14, [r0], #4
        STR     r14, [r0], #4
        BX      lr
        .endfunc

        .global RtkGetExceptionState
        .func RtkGetExceptionState
RtkGetExceptionState:
        LDR     r0, =RtkExceptionRegisters
        STR     r13, [r0], #4
        STR     r14, [r0], #4
        SUB     ip,   sp,  #4
        MRS     r2,   cpsr
        MRS     r3,   spsr
        AND     r3, r3, #0xDF                   //clear state bit
        MSR     cpsr_c, r3
        STR     r13,  [r0], #4
        STR     r14,  [r0], #4
        MSR     cpsr_cxsf, r2
        BX      lr
        .endfunc
        #endif

        .end