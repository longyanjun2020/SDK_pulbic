/******************************************************************************/
/* File    : arm_arch.h                                                       */
/*----------------------------------------------------------------------------*/
/* Scope   : ARM architecture related definitions                             */
/*                                                                            */
/******************************************************************************/
#ifndef __ARM_ARCH_H__
#define __ARM_ARCH_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------

// Processor saved states:
// The layout of this structure is also defined in "arm.inc", for assembly
// code, which will be generated automatically if this file changes.
#define HAL_THREAD_CONTEXT_FIRST        0
#define HAL_THREAD_CONTEXT_R0           (0 - HAL_THREAD_CONTEXT_FIRST)
#define HAL_THREAD_CONTEXT_R4           (4 - HAL_THREAD_CONTEXT_FIRST)
#define HAL_THREAD_CONTEXT_R8           (8 - HAL_THREAD_CONTEXT_FIRST)
#define HAL_THREAD_CONTEXT_R9           (9 - HAL_THREAD_CONTEXT_FIRST)
#define HAL_THREAD_CONTEXT_R10          (10 - HAL_THREAD_CONTEXT_FIRST)
#define HAL_THREAD_CONTEXT_LAST         10
#define HAL_NUM_THREAD_CONTEXT_REGS     (HAL_THREAD_CONTEXT_LAST - \
                                         HAL_THREAD_CONTEXT_FIRST + 1)


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------

/* r0-r3,r12 are considered scratch by APCS */
typedef struct
{
    /* These are common to all saved states */
    unsigned long   d[HAL_NUM_THREAD_CONTEXT_REGS]; // Data regs (r0..r10)
    unsigned long   fp;                             // (r11) Frame pointer
    unsigned long   ip;                             // (r12)
    unsigned long   sp;                             // (r13) Stack pointer
    unsigned long   lr;                             // (r14) Link Reg
    unsigned long   pc;                             // (r15) PC place holder
    unsigned long   cpsr;                           // Condition Reg
    /* These are only saved for exceptions and interrupts */
    unsigned long   vector;                         // Vector number
    unsigned long   svc_lr;                         // saved svc mode lr
    unsigned long   svc_sp;                         // saved svc mode sp
} HAL_SavedRegisters;

#endif /* __ARM_ARCH_H__ */
