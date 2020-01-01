/******************************************************************************/
/* File    : hal.h                                                            */
/*----------------------------------------------------------------------------*/
/* Scope   : HAL APIs and Macros                                              */
/*                                                                            */
/******************************************************************************/
#ifndef __HAL_H__
#define __HAL_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "plfcfg.h"
#include "stdcomp.h"


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#define HAL_READ_UINT16( _register_, _value_ ) \
    ((_value_) = *((volatile u16 *)(_register_)))

#define HAL_WRITE_UINT16( _register_, _value_ ) \
    (*((volatile u16 *)(_register_)) = (_value_))

#define HAL_READ_UINT32( _register_, _value_ )  \
    ((_value_) = *((volatile u32 *)(_register_)))

#define HAL_WRITE_UINT32( _register_, _value_ ) \
    (*((volatile u32 *)(_register_)) = (_value_))

#define HAL_DCACHE_START_ADDRESS(_addr_) \
    (((u32)(_addr_)) & ~(SYSHAL_DCACHE_LINE_SIZE-1))

#define HAL_DCACHE_END_ADDRESS(_addr_, _asize_) \
    (((u32)((_addr_) + (_asize_) + (SYSHAL_DCACHE_LINE_SIZE-1) )) & \
     ~(SYSHAL_DCACHE_LINE_SIZE-1))

/* Interrupt vector number */
#define HAL_IRQNUM_PM2BB        0x00
#define HAL_IRQNUM_EXT1         0x01
#define HAL_IRQNUM_EXT2         0x02
#define HAL_IRQNUM_EXT3         0x03
#define HAL_IRQNUM_I2C_STAT     0x04
#define HAL_IRQNUM_SPI1         0x05
#define HAL_IRQNUM_NOBAT        0x06
#define HAL_IRQNUM_BT_TIMER0    0x07
#define HAL_IRQNUM_BT_TIMER1    0x08
#define HAL_IRQNUM_I2C_TFR      0x09
#define HAL_IRQNUM_UART1        0x0A
#define HAL_IRQNUM_UART2        0x0B
#define HAL_IRQNUM_KEY          0x0C
#define HAL_IRQNUM_TIMSOFT      0x0D
#define HAL_IRQNUM_OSTICK       0x0E
#define HAL_IRQNUM_TIMEOUT      0x0F
#define HAL_IRQNUM_OSTICK2      0x10
#define HAL_IRQNUM_TBU_SINT0    0x11
#define HAL_IRQNUM_TBU_SINT1    0x12
#define HAL_IRQNUM_TBU_SINT2    0x13
#define HAL_IRQNUM_TBU_SINT3    0x14
#define HAL_IRQNUM_TBU_FINT     0x15
#define HAL_IRQNUM_TBU_SINTA    0x16
#define HAL_IRQNUM_RFDL_COLLISION   0x17
#define HAL_IRQNUM_AUD          0x18
#define HAL_IRQNUM_C0_DSMA      0x19
#define HAL_IRQNUM_C0_SHIFACE   0x1A
#define HAL_IRQNUM_LDOERR       0x1B
#define HAL_IRQNUM_CARD         0x1C
#define HAL_IRQNUM_ADCDONE      0x1D
#define HAL_IRQNUM_DMAC         0x1E
#define HAL_IRQNUM_PENDET       0x1F
#define HAL_IRQNUM_SIM1         0x20
#define HAL_IRQNUM_SIM2         0x21
#define HAL_IRQNUM_TBU_WAKEUP   0x22
#define HAL_IRQNUM_WDOG         0x23
#define HAL_IRQNUM_EMI_IMI      0x24
#define HAL_IRQNUM_MMP_TIMER    0x25
#define HAL_IRQNUM_DBB10        0x26
#define HAL_IRQNUM_AUD_ATOP     0x27
#define HAL_IRQNUM_AU_SYSTEM    0x28
#define HAL_IRQNUM_AU_INTA      0x29
#define HAL_IRQNUM_AU_INTB      0x2A
#define HAL_IRQNUM_JPDE         0x2B
#define HAL_IRQNUM_SENSOR_IF    0x2C
#define HAL_IRQNUM_ICP          0x2D
#define HAL_IRQNUM_SCLDMA       0x2E
#define HAL_IRQNUM_FCIE         0x2F
#define HAL_IRQNUM_SDIO         0x30
#define HAL_IRQNUM_OTG          0x31
#define HAL_IRQNUM_USB          0x32
#define HAL_IRQNUM_DISP         0x33
#define HAL_IRQNUM_FM_DSP       0x34
#define HAL_IRQNUM_BT_TAB       0x35
#define HAL_IRQNUM_BT_DMA       0x36
#define HAL_IRQNUM_DMA2D        0x37
#define HAL_IRQNUM_MPIF         0x38
#define HAL_IRQNUM_DS           0x39
#define HAL_IRQNUM_ADC_DMA      0x3A
#define HAL_IRQNUM_EXT4         0x3B
#define HAL_IRQNUM_EXT5         0x3C
#define HAL_IRQNUM_EXT6         0x3D
#define HAL_IRQNUM_EXT7         0x3E
#define HAL_IRQNUM_EXT8         0x3F

/* TCM Region */
#define ARM_ITCM_SIZE           0x4000      /* Actual 0x3000 KB only in BIG3 */


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------
typedef void (*isr_entry)(int vector, u32 data);

typedef enum
{
    INT_POLARITY_LOW = 0,
    INT_POLARITY_HIGH
} INT_POLARITY_e;

typedef enum
{
    INT_SENSITIVITY_EDGE = 0,
    INT_SENSITIVITY_LEVEL
} INT_SENSITIVITY_e;


//------------------------------------------------------------------------------
// Global Variable Declarations
//------------------------------------------------------------------------------
#ifndef __APCS_RWPI
extern u32  hal_isr_handlers[SYSNUM_HAL_ISR_COUNT];
extern u32  hal_isr_data[SYSNUM_HAL_ISR_COUNT];
#define PTR2ISRHAND     hal_isr_handlers
#define PTR2ISRDATA     hal_isr_data
#else
extern u32  (*ptr_hal_isr_handlers)[SYSNUM_HAL_ISR_COUNT];
extern u32  (*ptr_hal_isr_data)[SYSNUM_HAL_ISR_COUNT];
#define PTR2ISRHAND     (*ptr_hal_isr_handlers)
#define PTR2ISRDATA     (*ptr_hal_isr_data)
#endif

extern u8   gu8ucVendBuf[SYSNUM_USBVEND_BUFFER_SIZE];
extern u8   gu8ucDataBuf[SYSNUM_USBDATA_BUFFER_SIZE];
extern u8   gu8tmpBuf[SYSNUM_TEMP_BUFFER_SIZE];


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------
/* Platform Initialization */
void    plf_hardware_init(void);
void    init_arm_reset(void);
/* System Interrupt Control */
void    hal_interrupt_attach(int vector, void *isr, u32 data);
void    hal_interrupt_detach(int vector, void *isr);
void    hal_interrupt_create(int vector, u32 priority, isr_entry isr, u32 data);
void    hal_interrupt_mask(int vector);
void    hal_interrupt_unmask(int vector);
void    hal_interrupt_acknowledge(int vector);
void    hal_interrupt_configure(int vector, INT_SENSITIVITY_e esense,
                                INT_POLARITY_e epol);
void    hal_interrupt_ack(int vector);
void    hal_interrupt_clear(int vector);

/* CPU Interrupt Control */
u32     hal_disable_interrupts(void);
u32     hal_is_irq_disabled(void);
void    hal_enable_interrupts(void);
void    hal_restore_interrupts(u32 oldval);
/* CPU Cache Control */
void    hal_icache_enable(void);
void    hal_icache_disable(void);
void    hal_icache_invalidate(void);
void    hal_dcache_enable(void);
void    hal_dcache_disable(void);
void    hal_dcache_flush(void *base , u32 asize);
void    hal_dcache_invalidate(void *base , u32 asize);
void    hal_dcache_flush_all(void);
/* CPU TCM Region control */
bool    hal_itcm_enable(void *ptrbase);
void    hal_itcm_disable(void);
/* MMU Control */
void    hal_ttb_config(void *ttb);
void    hal_domainaccess_config(unsigned int value, unsigned int mask);
#if defined(__MSW8522__) || defined(__MSW8556__)
void	hal_mmu_disable(void);
#endif
/* System Delay */
void    hal_delay_us(u32 usecs);

#endif /* __HAL_H__ */
