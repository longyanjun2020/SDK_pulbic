#ifndef ONCE_HAL_PLF_INTR_H
#define ONCE_HAL_PLF_INTR_H
////////////////////////////////////////////////////////////////////////////////
///@file hal_plf_intr.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_hal.h>
#include <pkgconf_platform_intr.h>

//--------------------------------------------------------------------------
// Interrupt vectors.

// The vector used by the Real time clock
#ifdef NUM_HAL_RTC_INTERNAL_TIMER
#define NUM_HAL_INTERRUPT_RTC           NUM_HAL_INTERNAL_RTC_IRQ
#else
#define NUM_HAL_INTERRUPT_RTC           NUM_HAL_INTERRUPT_TIMER0
#endif

//--------------------------------------------------------------------------
#ifndef __ASSEMBLER__
#include <infra_type.h>
#include <hal_plf_io.h>

//--------------------------------------------------------------------------
// Interrupt controller access, MSTAR standard INTC

#ifndef HWR_HAL_INTERRUPT_CONTROLLER_ACCESS_DEFINED

#ifndef HAL_INTERRUPT_MASK
#ifdef  HWR_M3_BIG2
#define HAL_INTERRUPT_MASK( _vector_ )                       \
    EFAT_MACRO_START                                                         \
    if ( (_vector_) < NUM_HAL_INTERRUPT_FIQ_BASE ) {                     \
        asm volatile (                                                      \
            "mfc0   $3,$12\n"                                               \
            ASM_MFC0_DELAY                                                  \
            "la     $2,0x00000100\n"                                        \
            "sllv   $2,$2,%0\n"                                             \
            "nor    $2,$2,$0\n"                                             \
            "and    $3,$3,$2\n"                                             \
            "mtc0   $3,$12\n"                                               \
            ASM_CLEAR_EHB                                                   \
            :                                                               \
            : "r"(_vector_)                                                 \
            : "$2", "$3"                                                    \
            );                                                              \
    } /* FIQ 0-15 */                                                        \
    else if ((_vector_) < NUM_HAL_INTERRUPT_EXTERNAL_BASE ) {            \
        efat_uint32 _shift_ = (_vector_)-NUM_HAL_INTERRUPT_FIQ_BASE;      \
        *HAL_REG16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_INTC_FIQ_MASK) )      \
                |= (1<<_shift_);                                            \
    } /* IRQ 0-15 */                                                        \
    else if ((_vector_) < (NUM_HAL_INTERRUPT_EXTERNAL_BASE + 16) ) {     \
        efat_uint32 _shift_ = (_vector_)-NUM_HAL_INTERRUPT_EXTERNAL_BASE; \
        *HAL_REG16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_INTC_IRQ_MASK) )      \
                |= (1<<_shift_);                                            \
    } /* IRQ 16-31 */                                                     \
    else if ((_vector_) < NUM_HAL_INTERRUPT_EXTERNAL_BASE + 32) {                \
        efat_uint32 _shift_ = (_vector_)-(NUM_HAL_INTERRUPT_EXTERNAL_BASE+16); \
        *HAL_REG16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_INTC_IRQ_MASK_HI) )   \
                |= (1<<_shift_);                                            \
    }/* IRQ 32-47 */                                                       \
    else if ((_vector_) < NUM_HAL_INTERRUPT_USER_BASE ) {                \
        efat_uint32 _shift_ = (_vector_)-(NUM_HAL_INTERRUPT_EXTERNAL_BASE+32); \
        *HAL_REG16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_INTC_IRQ_MASK2) )   \
                |= (1<<_shift_);                                            \
    } /* USER 0-1 */                                                        \
    else if ((_vector_) <= (NUM_HAL_INTERRUPT_TIMER1) ) {                \
        efat_uint32 _shift_ = (_vector_)-(NUM_HAL_INTERRUPT_TIMER0);      \
        *HAL_REG16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_TIMER_INT_MASK) )     \
                |= (1<<_shift_);                                            \
    } /* USER 2-7 : user defined */                                         \
    EFAT_MACRO_END
#else   // !HWR_M3_BIG2
#define HAL_INTERRUPT_MASK( _vector_ )                       \
    EFAT_MACRO_START                                                         \
    if ( (_vector_) < NUM_HAL_INTERRUPT_FIQ_BASE ) {                     \
        asm volatile (                                                      \
            "mfc0   $3,$12\n"                                               \
            ASM_MFC0_DELAY                                                  \
            "la     $2,0x00000100\n"                                        \
            "sllv   $2,$2,%0\n"                                             \
            "nor    $2,$2,$0\n"                                             \
            "and    $3,$3,$2\n"                                             \
            "mtc0   $3,$12\n"                                               \
            ASM_CLEAR_EHB                                                   \
            :                                                               \
            : "r"(_vector_)                                                 \
            : "$2", "$3"                                                    \
            );                                                              \
    } /* FIQ 0-15 */                                                        \
    else if ((_vector_) < NUM_HAL_INTERRUPT_EXTERNAL_BASE ) {            \
        efat_uint32 _shift_ = (_vector_)-NUM_HAL_INTERRUPT_FIQ_BASE;      \
        *HAL_REG16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_INTC_FIQ_MASK) )      \
                |= (1<<_shift_);                                            \
    } /* IRQ 0-15 */                                                        \
    else if ((_vector_) < (NUM_HAL_INTERRUPT_EXTERNAL_BASE + 16) ) {     \
        efat_uint32 _shift_ = (_vector_)-NUM_HAL_INTERRUPT_EXTERNAL_BASE; \
        *HAL_REG16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_INTC_IRQ_MASK) )      \
                |= (1<<_shift_);                                            \
    } /* IRQ 16-31 */                                                       \
    else if ((_vector_) < NUM_HAL_INTERRUPT_USER_BASE ) {                \
        efat_uint32 _shift_ = (_vector_)-(NUM_HAL_INTERRUPT_EXTERNAL_BASE+16); \
        *HAL_REG16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_INTC_IRQ_MASK_HI) )   \
                |= (1<<_shift_);                                            \
    } /* USER 0-1 */                                                        \
    else if ((_vector_) <= (NUM_HAL_INTERRUPT_TIMER1) ) {                \
        efat_uint32 _shift_ = (_vector_)-(NUM_HAL_INTERRUPT_TIMER0);      \
        *HAL_REG16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_TIMER_INT_MASK) )     \
                |= (1<<_shift_);                                            \
    } /* USER 2-7 : user defined */                                         \
    EFAT_MACRO_END
#endif  // !HWR_M3_BIG2
#endif  // HAL_INTERRUPT_MASK

#ifndef HAL_INTERRUPT_UNMASK
#ifdef  HWR_M3_BIG2
#define HAL_INTERRUPT_UNMASK( _vector_ )                     \
    EFAT_MACRO_START                                                         \
    if ( (_vector_) < NUM_HAL_INTERRUPT_FIQ_BASE ) {                     \
        asm volatile (                                                      \
            "mfc0   $3,$12\n"                                               \
            ASM_MFC0_DELAY                                                  \
            "la     $2,0x00000100\n"                                        \
            "sllv   $2,$2,%0\n"                                             \
            "or     $3,$3,$2\n"                                             \
            "mtc0   $3,$12\n"                                               \
            ASM_CLEAR_EHB                                                   \
            :                                                               \
            : "r"(_vector_)                                                 \
            : "$2", "$3"                                                    \
            );                                                              \
    } /* FIQ 0-15 */                                                        \
    else if ((_vector_) < NUM_HAL_INTERRUPT_EXTERNAL_BASE ) {            \
        efat_uint32 _shift_ = (_vector_)-NUM_HAL_INTERRUPT_FIQ_BASE;      \
        *HAL_REG16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_INTC_FIQ_MASK) )      \
                &= ~(1<<_shift_);                                           \
    } /* IRQ 0-15 */                                                        \
    else if ((_vector_) < (NUM_HAL_INTERRUPT_EXTERNAL_BASE + 16) ) {     \
        efat_uint32 _shift_ = (_vector_)-NUM_HAL_INTERRUPT_EXTERNAL_BASE; \
        *HAL_REG16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_INTC_IRQ_MASK) )      \
                &= ~(1<<_shift_);                                           \
    } /* IRQ 16-31 */                                                       \
    else if ((_vector_) < (NUM_HAL_INTERRUPT_EXTERNAL_BASE + 32)) {                \
        efat_uint32 _shift_ = (_vector_)-(NUM_HAL_INTERRUPT_EXTERNAL_BASE+16); \
        *HAL_REG16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_INTC_IRQ_MASK_HI) )   \
                &= ~(1<<_shift_);                                           \
    } /* IRQ 32-47 */                                                       \
    else if ((_vector_) < NUM_HAL_INTERRUPT_USER_BASE ) {                \
        efat_uint32 _shift_ = (_vector_)-(NUM_HAL_INTERRUPT_EXTERNAL_BASE+32); \
        *HAL_REG16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_INTC_IRQ_MASK2) )   \
                &= ~(1<<_shift_);                                           \
    } /* USER 0-1 */                                                        \
    else if ((_vector_) <= (NUM_HAL_INTERRUPT_TIMER1) ) {                \
        efat_uint32 _shift_ = (_vector_)-(NUM_HAL_INTERRUPT_TIMER0);      \
        *HAL_REG16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_TIMER_INT_MASK) )     \
                &= ~(1<<_shift_);                                           \
        /* Unmask INTC NUM_HAL_INTERRUPT_MCU */                          \
        *HAL_REG16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_INTC_IRQ_MASK) )      \
                &= ~(1<<(NUM_HAL_INTERRUPT_TIMER-NUM_HAL_INTERRUPT_EXTERNAL_BASE)); \
    }                                                                       \
    EFAT_MACRO_END
#else   // !HWR_M3_BIG2
#define HAL_INTERRUPT_UNMASK( _vector_ )                     \
    EFAT_MACRO_START                                                         \
    if ( (_vector_) < NUM_HAL_INTERRUPT_FIQ_BASE ) {                     \
        asm volatile (                                                      \
            "mfc0   $3,$12\n"                                               \
            ASM_MFC0_DELAY                                                  \
            "la     $2,0x00000100\n"                                        \
            "sllv   $2,$2,%0\n"                                             \
            "or     $3,$3,$2\n"                                             \
            "mtc0   $3,$12\n"                                               \
            ASM_CLEAR_EHB                                                   \
            :                                                               \
            : "r"(_vector_)                                                 \
            : "$2", "$3"                                                    \
            );                                                              \
    } /* FIQ 0-15 */                                                        \
    else if ((_vector_) < NUM_HAL_INTERRUPT_EXTERNAL_BASE ) {            \
        efat_uint32 _shift_ = (_vector_)-NUM_HAL_INTERRUPT_FIQ_BASE;      \
        *HAL_REG16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_INTC_FIQ_MASK) )      \
                &= ~(1<<_shift_);                                           \
    } /* IRQ 0-15 */                                                        \
    else if ((_vector_) < (NUM_HAL_INTERRUPT_EXTERNAL_BASE + 16) ) {     \
        efat_uint32 _shift_ = (_vector_)-NUM_HAL_INTERRUPT_EXTERNAL_BASE; \
        *HAL_REG16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_INTC_IRQ_MASK) )      \
                &= ~(1<<_shift_);                                           \
    } /* IRQ 16-31 */                                                       \
    else if ((_vector_) < NUM_HAL_INTERRUPT_USER_BASE ) {                \
        efat_uint32 _shift_ = (_vector_)-(NUM_HAL_INTERRUPT_EXTERNAL_BASE+16); \
        *HAL_REG16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_INTC_IRQ_MASK_HI) )   \
                &= ~(1<<_shift_);                                           \
    } /* USER 0-1 */                                                        \
    else if ((_vector_) <= (NUM_HAL_INTERRUPT_TIMER1) ) {                \
        efat_uint32 _shift_ = (_vector_)-(NUM_HAL_INTERRUPT_TIMER0);      \
        *HAL_REG16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_TIMER_INT_MASK) )     \
                &= ~(1<<_shift_);                                           \
        /* Unmask INTC NUM_HAL_INTERRUPT_MCU */                          \
        *HAL_REG16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_INTC_IRQ_MASK) )      \
                &= ~(1<<(NUM_HAL_INTERRUPT_TIMER-NUM_HAL_INTERRUPT_EXTERNAL_BASE)); \
    }                                                                       \
    EFAT_MACRO_END
#endif  // !HWR_M3_BIG2
#endif  // HAL_INTERRUPT_UNMASK

#ifndef HAL_INTERRUPT_ACKNOWLEDGE
#define HAL_INTERRUPT_ACKNOWLEDGE( _vector_ )                   \
    EFAT_MACRO_START                                                         \
    if ( ( (_vector_) >= NUM_HAL_INTERRUPT_FIQ_BASE ) &&                 \
         ( (_vector_) < NUM_HAL_INTERRUPT_EXTERNAL_BASE ) )              \
    {                                                                       \
        efat_uint32 _shift_ = (_vector_)-NUM_HAL_INTERRUPT_FIQ_BASE;      \
        /* write one clear */                                               \
        *HAL_REG16(ARC_UNCACHED_ADDRESS(HAL_MSTAR_INTC_FIQ_CLEAR))       \
            |= (1<<_shift_);                                                \
        /* write zero clear */                                              \
        *HAL_REG16(ARC_UNCACHED_ADDRESS(HAL_MSTAR_INTC_FIQ_CLEAR))       \
            &= ~(1<<_shift_);                                               \
    }                                                                       \
    /* All other IP must clear the interrupt by it's own ISR */             \
    EFAT_MACRO_END
#endif //HAL_INTERRUPT_ACKNOWLEDGE

#ifndef HAL_INTERRUPT_CONFIGURE
#define HAL_INTERRUPT_CONFIGURE( _vector_, _level_, _up_ )                  \
    EFAT_EMPTY_STATEMENT
#endif //HAL_INTERRUPT_CONFIGURE

#ifndef HAL_INTERRUPT_SET_LEVEL
#define HAL_INTERRUPT_SET_LEVEL( _vector_, _level_ )                        \
    EFAT_EMPTY_STATEMENT
#endif //HAL_INTERRUPT_SET_LEVEL

#define HWR_HAL_INTERRUPT_CONTROLLER_ACCESS_DEFINED

#endif

//--------------------------------------------------------------------------
// Control-C support.

#if defined(DBG_HAL_MIPS_DEBUG_GDB_CTRLC_SUPPORT)

# define HWR_HAL_GDB_PORT_VECTOR NUM_HAL_INTERRUPT_SER

externC efat_uint32 hal_ctrlc_isr(EFAT_ADDRWORD vector, EFAT_ADDRWORD data);

# define HAL_CTRLC_ISR hal_ctrlc_isr

#endif


//----------------------------------------------------------------------------
// Reset.
#ifndef HWR_HAL_RESET_DEFINED
extern void hal_mstar_reset( void );
#define HWR_HAL_RESET_DEFINED
#define HAL_PLATFORM_RESET()             hal_mstar_reset()

#define HAL_PLATFORM_RESET_ENTRY 0xbfc00000

#endif // HWR_HAL_RESET_DEFINED

#endif // __ASSEMBLER__

//--------------------------------------------------------------------------
#endif // ifndef ONCE_HAL_PLF_INTR_H
// End of plf_intr.h
