#ifndef ONCE_HAL_VAR_INTR_H
#define ONCE_HAL_VAR_INTR_H
///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file   hal_var_intr.h
/// @author MStar Semiconductor Inc.
/// @brief  video application header file
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_hal.h>
#include <infra_type.h>
#include <hal_plf_intr.h>


// Interrupt control macros

#if (defined(HWR_HAL_MIPS_MIPS32_CORE_4KEc) || defined(HWR_HAL_MIPS_MIPS32_CORE_M4K)) && \
        !defined( HWR_HAL_INTERRUPT_ENABLE_DISABLE_RESTORE_DEFINED )


#define HAL_DISABLE_INTERRUPTS(_old_)           \
{                                               \
    asm volatile (                              \
        "mfc0   $8,$12;"                        \
        ASM_MFC0_DELAY                          \
        "di;"                                   \
        ASM_CLEAR_EHB                           \
        "and    %0,$8,0x1;"                     \
        : "=r"(_old_)                           \
        :                                       \
        : "$8"                                  \
        );                                      \
}

#define HAL_ENABLE_INTERRUPTS()                 \
{                                               \
    asm volatile (                              \
        "ei;"                                   \
        ASM_CLEAR_EHB                           \
        :                                       \
        :                                       \
        :                                       \
        );                                      \
}

#define HAL_RESTORE_INTERRUPTS(_old_)           \
{                                               \
    asm volatile (                              \
        "mfc0   $8,$12;"                        \
        ASM_MFC0_DELAY                          \
        "and    %0,%0,0x1;"                     \
        "or     $8,$8,%0;"                      \
        "mtc0   $8,$12;"                        \
        ASM_CLEAR_EHB                           \
        :                                       \
        : "r"(_old_)                            \
        : "$8"                                  \
        );                                      \
}

#define HAL_QUERY_INTERRUPTS( _state_ )         \
{                                               \
    asm volatile (                              \
        "mfc0   %0,$12;"                        \
        ASM_MFC0_DELAY                          \
        "and    %0,%0,0x1;"                     \
        : "=r"(_state_)                         \
        :                                       \
        :                                       \
        );                                      \
}

#define HWR_HAL_INTERRUPT_ENABLE_DISABLE_RESTORE_DEFINED

#endif // HWR_HAL_INTERRUPT_ENABLE_DISABLE_RESTORE_DEFINED

//--------------------------------------------------------------------------
#endif // ifndef ONCE_HAL_IMP_INTR_H
// End of imp_intr.h
