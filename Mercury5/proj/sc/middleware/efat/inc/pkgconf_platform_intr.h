#ifndef ONCE_HAL_MSTAR_PLATFORM_MONTAGE_INTR_H
#define ONCE_HAL_MSTAR_PLATFORM_MONTAGE_INTR_H

///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file   pkgconf_platform_intr.h
/// @author MStar Semiconductor Inc.
/// @brief  video application header file
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_system.h>

// First an assembly safe part

//--------------------------------------------------------------------------
// Interrupt vectors.

#ifndef HWR_HAL_INTERRUPT_VECTORS_DEFINED

// These are decoded via the IP bits of the cause
// register when an external interrupt is delivered.

#define NUM_HAL_INTERRUPT_SW0             0
#define NUM_HAL_INTERRUPT_SW1             1
#define NUM_HAL_INTERRUPT_HARDWARE_BASE   2
#define NUM_HAL_INTERRUPT_INTC_IRQ        2    // HW0
#define NUM_HAL_INTERRUPT_INTC_FIQ        3    // HW1
#define NUM_HAL_INTERRUPT_4               4    // HW2
#define NUM_HAL_INTERRUPT_5               5    // HW3
#define NUM_HAL_INTERRUPT_6               6    // HW4
#define NUM_HAL_INTERNAL_RTC_IRQ          7    // HW5

// Vector 8
// These bits are decoded by INTC FIQ control registers
#define NUM_HAL_INTERRUPT_FIQ_BASE        8

#define NUM_HAL_INTERRUPT_HIF             (NUM_HAL_INTERRUPT_FIQ_BASE+ 0)
#define NUM_HAL_INTERRUPT_09              (NUM_HAL_INTERRUPT_FIQ_BASE+ 1)
#define NUM_HAL_INTERRUPT_10              (NUM_HAL_INTERRUPT_FIQ_BASE+ 2)
#define NUM_HAL_INTERRUPT_11              (NUM_HAL_INTERRUPT_FIQ_BASE+ 3)
#define NUM_HAL_INTERRUPT_12              (NUM_HAL_INTERRUPT_FIQ_BASE+ 4)
#define NUM_HAL_INTERRUPT_13              (NUM_HAL_INTERRUPT_FIQ_BASE+ 5)
#define NUM_HAL_INTERRUPT_14              (NUM_HAL_INTERRUPT_FIQ_BASE+ 6)
#define NUM_HAL_INTERRUPT_15              (NUM_HAL_INTERRUPT_FIQ_BASE+ 7)
#define NUM_HAL_INTERRUPT_16              (NUM_HAL_INTERRUPT_FIQ_BASE+ 8)
#define NUM_HAL_INTERRUPT_17              (NUM_HAL_INTERRUPT_FIQ_BASE+ 9)
#define NUM_HAL_INTERRUPT_18              (NUM_HAL_INTERRUPT_FIQ_BASE+10)
#define NUM_HAL_INTERRUPT_19              (NUM_HAL_INTERRUPT_FIQ_BASE+11)
#define NUM_HAL_INTERRUPT_20              (NUM_HAL_INTERRUPT_FIQ_BASE+12)
#define NUM_HAL_INTERRUPT_21              (NUM_HAL_INTERRUPT_FIQ_BASE+13)
#define NUM_HAL_INTERRUPT_22              (NUM_HAL_INTERRUPT_FIQ_BASE+14)
#define NUM_HAL_INTERRUPT_23              (NUM_HAL_INTERRUPT_FIQ_BASE+15)

// Vector 24
// These bits are decoded via the INTC registers
#define NUM_HAL_INTERRUPT_EXTERNAL_BASE   (NUM_HAL_INTERRUPT_FIQ_BASE+16)

// Interrupt numbers, named after HW document
#define NUM_HAL_INTERRUPT_ICP             (NUM_HAL_INTERRUPT_EXTERNAL_BASE+ 0)
#define NUM_HAL_INTERRUPT_JPG2MCU         (NUM_HAL_INTERRUPT_EXTERNAL_BASE+ 1)
#define NUM_HAL_INTERRUPT_USB11           (NUM_HAL_INTERRUPT_EXTERNAL_BASE+ 2)
#define NUM_HAL_INTERRUPT_FCIE            (NUM_HAL_INTERRUPT_EXTERNAL_BASE+ 3)
#define NUM_HAL_INTERRUPT_DMA             (NUM_HAL_INTERRUPT_EXTERNAL_BASE+ 4)
#define NUM_HAL_INTERRUPT_JPD             (NUM_HAL_INTERRUPT_EXTERNAL_BASE+ 5)
#define NUM_HAL_INTERRUPT_TIMER           (NUM_HAL_INTERRUPT_EXTERNAL_BASE+ 6)
#define NUM_HAL_INTERRUPT_DISP            (NUM_HAL_INTERRUPT_EXTERNAL_BASE+ 7)
#define NUM_HAL_INTERRUPT_SPIDMA          (NUM_HAL_INTERRUPT_EXTERNAL_BASE+ 8)
#define NUM_HAL_INTERRUPT_MIIC            (NUM_HAL_INTERRUPT_EXTERNAL_BASE+ 9)
#define NUM_HAL_INTERRUPT_UART1           (NUM_HAL_INTERRUPT_EXTERNAL_BASE+10)
#define NUM_HAL_INTERRUPT_IIS_TX          (NUM_HAL_INTERRUPT_EXTERNAL_BASE+11)
#define NUM_HAL_INTERRUPT_IIS_RX          (NUM_HAL_INTERRUPT_EXTERNAL_BASE+12)
#define NUM_HAL_INTERRUPT_GPIO3           (NUM_HAL_INTERRUPT_EXTERNAL_BASE+13)
#define NUM_HAL_INTERRUPT_GPIO2           (NUM_HAL_INTERRUPT_EXTERNAL_BASE+14)
#define NUM_HAL_INTERRUPT_GPIO1           (NUM_HAL_INTERRUPT_EXTERNAL_BASE+15)
#define NUM_HAL_INTERRUPT_GPIO0           (NUM_HAL_INTERRUPT_EXTERNAL_BASE+16)
#define NUM_HAL_INTERRUPT_ISP             (NUM_HAL_INTERRUPT_EXTERNAL_BASE+17)
#define NUM_HAL_INTERRUPT_SCL             (NUM_HAL_INTERRUPT_EXTERNAL_BASE+18)
#define NUM_HAL_INTERRUPT_SSP             (NUM_HAL_INTERRUPT_EXTERNAL_BASE+19)
#define NUM_HAL_INTERRUPT_NFIE            (NUM_HAL_INTERRUPT_EXTERNAL_BASE+20)
#define NUM_HAL_INTERRUPT_COMP            (NUM_HAL_INTERRUPT_EXTERNAL_BASE+21)
//for Montage2
#define NUM_HAL_INTERRUPT_WD              (NUM_HAL_INTERRUPT_EXTERNAL_BASE+22)
#define NUM_HAL_INTERRUPT_UART2           (NUM_HAL_INTERRUPT_EXTERNAL_BASE+26)




#define NUM_HAL_INTERRUPT_ECBRIDGE        (NUM_HAL_INTERRUPT_EXTERNAL_BASE+27)

#define NUM_HAL_INTERRUPT_OTGAVALID       (NUM_HAL_INTERRUPT_EXTERNAL_BASE+29)
#define NUM_HAL_INTERRUPT_OTGAVBUS        (NUM_HAL_INTERRUPT_EXTERNAL_BASE+30)

#ifdef HWR_M3_BIG2
#define NUM_HAL_INTERRUPT_SPIF            (NUM_HAL_INTERRUPT_EXTERNAL_BASE+32)
#define NUM_HAL_INTERRUPT_UTMI0           (NUM_HAL_INTERRUPT_EXTERNAL_BASE+33)
#define NUM_HAL_INTERRUPT_UTMI1           (NUM_HAL_INTERRUPT_EXTERNAL_BASE+34)
#define NUM_HAL_INTERRUPT_UHC             (NUM_HAL_INTERRUPT_EXTERNAL_BASE+35)
#define NUM_HAL_INTERRUPT_M4VE            (NUM_HAL_INTERRUPT_EXTERNAL_BASE+36)
#define NUM_HAL_INTERRUPT_M4VD            (NUM_HAL_INTERRUPT_EXTERNAL_BASE+37)
#define NUM_HAL_INTERRUPT_FUART           (NUM_HAL_INTERRUPT_EXTERNAL_BASE+38)
#define NUM_HAL_INTERRUPT_FUART_DMA       (NUM_HAL_INTERRUPT_EXTERNAL_BASE+39)
#define NUM_HAL_INTERRUPT_G3D             (NUM_HAL_INTERRUPT_EXTERNAL_BASE+40)
// ...
#define NUM_HAL_INTERRUPT_LAST            (NUM_HAL_INTERRUPT_EXTERNAL_BASE+47)
#endif

// Alias names for driver writers
#define NUM_HAL_INTERRUPT_JPEG_ENC        NUM_HAL_INTERRUPT_JPG2MCU
#define NUM_HAL_INTERRUPT_JPG_ENC         NUM_HAL_INTERRUPT_JPG2MCU
#define NUM_HAL_INTERRUPT_CARD_READER     NUM_HAL_INTERRUPT_FCIE
#define NUM_HAL_INTERRUPT_JPEG_DEC        NUM_HAL_INTERRUPT_JPD
#define NUM_HAL_INTERRUPT_JPG_DEC         NUM_HAL_INTERRUPT_JPD
#define NUM_HAL_INTERRUPT_CAM             NUM_HAL_INTERRUPT_SCL
#define NUM_HAL_INTERRUPT_SPI             NUM_HAL_INTERRUPT_SPI
#define NUM_HAL_INTERRUPT_NAND_CTRL       NUM_HAL_INTERRUPT_NFIE
#define NUM_HAL_INTERRUPT_LBC             NUM_HAL_INTERRUPT_COMP


// Vector 56
#ifdef HWR_M3_BIG2
#define NUM_HAL_INTERRUPT_USER_BASE       (NUM_HAL_INTERRUPT_EXTERNAL_BASE+48)
#else
#define NUM_HAL_INTERRUPT_USER_BASE       (NUM_HAL_INTERRUPT_EXTERNAL_BASE+32)
#endif
#define NUM_HAL_INTERRUPT_TIMER0          (NUM_HAL_INTERRUPT_USER_BASE+ 0)
#define NUM_HAL_INTERRUPT_TIMER1          (NUM_HAL_INTERRUPT_USER_BASE+ 1)
#define NUM_HAL_INTERRUPT_58              (NUM_HAL_INTERRUPT_USER_BASE+ 2)
#define NUM_HAL_INTERRUPT_59              (NUM_HAL_INTERRUPT_USER_BASE+ 3)
#define NUM_HAL_INTERRUPT_60              (NUM_HAL_INTERRUPT_USER_BASE+ 4)
#define NUM_HAL_INTERRUPT_61              (NUM_HAL_INTERRUPT_USER_BASE+ 5)
#define NUM_HAL_INTERRUPT_62              (NUM_HAL_INTERRUPT_USER_BASE+ 6)
#define NUM_HAL_INTERRUPT_63              (NUM_HAL_INTERRUPT_USER_BASE+ 7)
// Total 64 vectors

#if defined(IMP_HAL_COMMON_INTERRUPTS_CHAIN)

// This overlaps with NUM_HAL_INTERRUPT_EXTERNAL_BASE above but it
// doesn't matter. It's only used by the HAL to access the special
// chaining entry in the ISR tables.  All other attempted access to
// the ISR table will be redirected to this entry (courtesy of
// HAL_TRANSLATE_VECTOR). The other vector definitions are still
// valid, but only for enable/disable/config etc. (i.e., in chaining
// mode they have associated entries in the ISR tables).
#define NUM_HAL_INTERRUPT_CHAINING        NUM_HAL_INTERRUPT_EXTERNAL_BASE

#define HAL_TRANSLATE_VECTOR(_vector_,_index_) \
    (_index_) = NUM_HAL_INTERRUPT_CHAINING

// Min/Max ISR numbers
#define NUM_HAL_ISR_MIN                 0
#define NUM_HAL_ISR_MAX                 NUM_HAL_INTERRUPT_CHAINING

#else

// Min/Max ISR numbers
#define NUM_HAL_ISR_MIN                 0
#define NUM_HAL_ISR_MAX                 NUM_HAL_INTERRUPT_63
#endif // IMP_HAL_COMMON_INTERRUPTS_CHAIN

#define NUM_HAL_ISR_COUNT               (NUM_HAL_ISR_MAX - NUM_HAL_ISR_MIN + 1)

#define HWR_HAL_INTERRUPT_VECTORS_DEFINED

#endif


//--------------------------------------------------------------------------
#ifndef __ASSEMBLER__

#include <infra_type.h>
#include <hal_plf_io.h>

//--------------------------------------------------------------------------
// Interrupt controller access, MSTAR standard INTC, montage variant

//externC void intc_ack_delay( void );

#ifndef HAL_INTERRUPT_ACKNOWLEDGE
#define HAL_INTERRUPT_ACKNOWLEDGE( _vector_ )                   \
    EFAT_MACRO_START                                                         \
    if ( ( (_vector_) >= NUM_HAL_INTERRUPT_FIQ_BASE ) &&                 \
         ( (_vector_) < NUM_HAL_INTERRUPT_EXTERNAL_BASE ) )              \
    {                                                                       \
        efat_uint32 _shift_ = (_vector_)-NUM_HAL_INTERRUPT_FIQ_BASE;      \
        efat_uint32 _oldinten_;                                              \
        HAL_DISABLE_INTERRUPTS( _oldinten_ );                               \
        /* write one clear */                                               \
        *HAL_REG16(ARC_UNCACHED_ADDRESS(HAL_MSTAR_INTC_FIQ_CLEAR))       \
            |= (1<<_shift_);                                                \
        /* write zero clear */                                              \
        *HAL_REG16(ARC_UNCACHED_ADDRESS(HAL_MSTAR_INTC_FIQ_CLEAR))       \
            &= ~(1<<_shift_);                                               \
        HAL_RESTORE_INTERRUPTS( _oldinten_ );                               \
    }                                                                       \
    /* All other IP must clear the interrupt by it's own ISR */             \
    EFAT_MACRO_END
#endif

//--------------------------------------------------------------------------
// Clock control.

#ifndef NUM_HAL_RTC_INTERNAL_TIMER

externC EFAT_WORD32 efat_hal_clock_period;
#define HWR_HAL_CLOCK_PERIOD_DEFINED

#define HAL_CLOCK_INITIALIZE( _period_ )                                                       \
    EFAT_MACRO_START                                                                            \
    HAL_WRITE_UINT16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_TIMER0_PRECISION), (_period_) >> 16 ); \
    HAL_WRITE_UINT16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_TIMER0_STARTCNT), (_period_) & 0xffff );  \
    efat_hal_clock_period = _period_;                                                           \
    EFAT_MACRO_END

// Clear timer 0 interrupt and reset counter
#define HAL_CLOCK_RESET( _vector_, _period_ )                                                  \
    EFAT_MACRO_START                                                                            \
    register unsigned short origval;                                                           \
    register unsigned short isr_raw_status;                                                    \
    unsigned orig_inten;                                                                       \
    HAL_CLOCK_INITIALIZE( _period_ );                                                          \
    HAL_READ_UINT16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_TIMER_INT_CLEAR), origval );            \
    /* clear timer interrupt */                                                                \
    HAL_DISABLE_INTERRUPTS( orig_inten );                                                      \
    HAL_WRITE_UINT16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_TIMER_INT_CLEAR), origval | 0x01 );    \
    do {                                                                                       \
    HAL_READ_UINT16(ARC_UNCACHED_ADDRESS(HAL_MSTAR_TIMER_INT_FINAL), isr_raw_status);         \
        }while((isr_raw_status & (0x01)) == 0x01);                                             \
    HAL_WRITE_UINT16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_TIMER_INT_CLEAR), origval & (~0x01) ); \
    HAL_RESTORE_INTERRUPTS( orig_inten );                                                      \
    EFAT_MACRO_END

// Read the up-counter
#define HAL_CLOCK_READ( _pvalue_ )                                                      \
    EFAT_MACRO_START                                                                     \
    register unsigned short precision, count;                                           \
    HAL_READ_UINT16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_TIMER0_PREC_VAL), precision );   \
    HAL_READ_UINT16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_TIMER0_COUNT_VAL), count );      \
    *(_pvalue_) = ((unsigned long)precision * (efat_hal_clock_period >> 16)) + count;    \
    EFAT_MACRO_END

// Read the up-counter
// compact with non-OS mode, no use global variable
#define HAL_CLOCK_READ_NG( _pvalue_ )                                                      \
    EFAT_MACRO_START                                                                     \
    register unsigned short precision, count;                                           \
    HAL_READ_UINT16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_TIMER0_PREC_VAL), precision );   \
    HAL_READ_UINT16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_TIMER0_COUNT_VAL), count );      \
    *(_pvalue_) = ((unsigned long)precision * (NUM_HAL_RTC_PERIOD >> 16)) + count;    \
    EFAT_MACRO_END

#define HWR_HAL_CLOCK_CONTROL_DEFINED

#endif // NUM_HAL_RTC_INTERNAL_TIMER



//--------------------------------------------------------------------------
// WatchDog control.

#if defined(HWR_HAL_MIPS_MSTAR_CPU_WATCHDOG)

externC EFAT_WORD32 efat_hal_watchdog_period;
#define HWR_HAL_WATCHDOG_PERIOD_DEFINED

#if defined(HWR_HAL_WATCHDOG_RESET)
#define WATCHDOG_WD_CONTROL 0x1
#else
#define WATCHDOG_WD_CONTROL 0x2
#endif


#define HAL_WATCHDOG_SATRT()                                                                           \
    EFAT_MACRO_START                                                                                    \
    HAL_WRITE_UINT16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_WATCHDOG_WD_CODE), 0x04b2 );                   \
    HAL_WRITE_UINT16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_WATCHDOG_WD_CONTROL), WATCHDOG_WD_CONTROL);    \
    HAL_WRITE_UINT16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_WD_INT_MASK), 0x2 );                        \
    HAL_WRITE_UINT16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_WD_ENABLE), 0x1 );                        \
    EFAT_MACRO_END


#define HAL_WATCHDOG_INITIALIZE( _period_ )                                                       \
    EFAT_MACRO_START                                                                               \
    HAL_WRITE_UINT16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_WD_TIMER0_PRECISION), (_period_) >> 16 );  \
    HAL_WRITE_UINT16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_WD_TIMER0_STARTCNT), (_period_) & 0xffff );\
    efat_hal_watchdog_period = _period_;                                                           \
    EFAT_MACRO_END

// reset WatchDog
#define HAL_WATCHDOG_RESET()                                                                      \
    EFAT_MACRO_START                                                                               \
    register unsigned short origval;                                                              \
    register unsigned short status;                                                               \
    HAL_WRITE_UINT16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_WD_ENABLE), origval & (~0x01) );         \
    do {                                                                                          \
    HAL_READ_UINT16(ARC_UNCACHED_ADDRESS(HAL_MSTAR_WD_TIMER0_PREC_VAL), status);               \
        }while(status != 0x0);                                                                  \
    HAL_WRITE_UINT16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_WD_ENABLE), origval | 0x01 );            \
    EFAT_MACRO_END

// restart WatchDog
#define HAL_CLOCK_RESTART( _period_ )                                                          \
    EFAT_MACRO_START                                                                            \
    register unsigned short origval;                                                           \
    register unsigned short isr_raw_status;                                                    \
    HAL_WATCHDOG_INITIALIZE( _period_ );                                                          \
    HAL_READ_UINT16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_WD_INT_CLEAR), origval );               \
    /* clear timer interrupt */                                                                \
    HAL_WRITE_UINT16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_WD_INT_CLEAR), origval | 0x01 );       \
    do {                                                                                       \
    HAL_READ_UINT16(ARC_UNCACHED_ADDRESS(HAL_MSTAR_WD_INT_RAW), isr_raw_status);            \
        }while((isr_raw_status & (0x01)) == 0x01);                                             \
    HAL_WRITE_UINT16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_WD_INT_CLEAR), origval & (~0x01) );    \
    EFAT_MACRO_END

// Read the up-counter
#define HAL_WATCHDOG_READ( _pvalue_ )                                                             \
    EFAT_MACRO_START                                                                               \
    register unsigned short precision, count;                                                     \
    HAL_READ_UINT16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_WD_TIMER0_PREC_VAL), precision );           \
    HAL_READ_UINT16( ARC_UNCACHED_ADDRESS(HAL_MSTAR_WD_TIMER0_COUNT_VAL), count );              \
    *(_pvalue_) = ((unsigned long)precision * (efat_hal_watchdog_period >> 16)) + count;           \
    EFAT_MACRO_END

#define HWR_HAL_WATCHDOG_CONTROL_DEFINED
#endif

#endif // __ASSEMBLER__

//--------------------------------------------------------------------------
#endif // ifndef ONCE_HAL_MSTAR_PLATFORM_MONTAGE_INTR_H
// End of platform_intr.h

