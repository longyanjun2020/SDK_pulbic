#ifndef __SYS_R2_CORE_H__
#define __SYS_R2_CORE_H__

#include "vm_types.ht"

#define ENABLE_IMMU 1
#define ENABLE_DMMU 1
#define FORCE_DRAM_NO_DTLBMISS   0
#define KEEP_MMU_STATUS_ON_EXCEPTION 0
#define TEXT_DEMAND_PAGING_GDB_SUPPORT 0

#define UTLB_DEBUG 0
#define TLB_PAGESIZE_8K 1
#define RANDOM_HASH 0
#define TLBMISS_STACK_SIZE 512

#define UTLB_PAGESIZE_8K      (0x00)
#define UTLB_PAGESIZE_1M      (0x01)
#define UTLB_PAGESIZE_4M      (0x02)
#define UTLB_PAGESIZE_8M      (0x03)
#define UTLB_PAGESIZE_256M    (0x03)

#define MMU_SIZE_8K           (0x2000)
#define MMU_SIZE_1M           (0x100000)
#define MMU_SIZE_4M           (0x400000)
#define MMU_SIZE_8M           (0x800000)

#define CONFIG_MMU_PAGESIZE   MMU_SIZE_8K

#define CONFIG_MMU_PAGEMASK   (CONFIG_MMU_PAGESIZE-1)
#if (CONFIG_MMU_PAGESIZE == MMU_SIZE_8K)
#define CONFIG_MMU_PAGE_SETTING   UTLB_PAGESIZE_8K
#elif (CONFIG_MMU_PAGESIZE == MMU_SIZE_1M)
#define CONFIG_MMU_PAGE_SETTING   UTLB_PAGESIZE_1M
#elif (CONFIG_MMU_PAGESIZE == MMU_SIZE_4M)
#define CONFIG_MMU_PAGE_SETTING   UTLB_PAGESIZE_4M
#elif (CONFIG_MMU_PAGESIZE == MMU_SIZE_8M)
#define CONFIG_MMU_PAGE_SETTING   UTLB_PAGESIZE_8M
#endif

#ifndef __ASSEMBLER__

//#include "vm_types.ht"
#ifndef __SDK_SIMULATION__
#define OS_RTK 1

#if !defined(OS_RTK)                    // <-@@@
#define PLATFORM_IO_IMPLEMENTATION
#endif                                  // <-@@@
// This flag will instruct <pkgconf/platform_io.h> to declare shadow registers

#if !defined(OS_RTK)                    // <-@@@ <cyg/hal/hal_if.h>
#include <cyg/hal/hal_if.h>
#else                                   // <-@@@ <cyg/hal/hal_if.h>

#define CYG_HAL_OPENRISC_REG unsigned int // CYG_WORD32 // <-@@@
#define CYG_MACRO_START do {                            // <-@@@
#define CYG_MACRO_END   } while (0)                     // <-@@@

#include "r2_system.h"

// #ifdef CYGHWR_HAL_OPENRISC_MSTAR_CPUTYPE_AEONR2
#define MFSPR(_spr_)                            \
    ({  CYG_HAL_OPENRISC_REG _result_;          \
        asm volatile ("l.mfspr %0, %1, 0;"      \
                      : "=r"(_result_)          \
                      : "r"(_spr_)              \
            );                                  \
        _result_;})

// Move data to architecture special registers (SPR)
#define MTSPR(_spr_, _val_)                     \
    CYG_MACRO_START                             \
    CYG_HAL_OPENRISC_REG val = _val_;           \
    asm volatile ("l.mtspr %0, %1, 0;"          \
                  :                             \
                  : "r"(_spr_), "r"(val)        \
        );                                      \
    CYG_MACRO_END
////    : "r"(val), "r"(_spr_) /*incorrect*/
// #else  // CYGHWR_HAL_OPENRISC_MSTAR_CPUTYPE_AEONR2
// #endif // CYGHWR_HAL_OPENRISC_MSTAR_CPUTYPE_AEONR2

#endif                                  // <-@@@ <cyg/hal/hal_if.h>
#if !defined(OS_RTK)                    // <-@@@ <cyg/hal/spr_defs.h>
#include <cyg/hal/spr_defs.h>
#endif                                  // <-@@@ <cyg/hal/hal_if.h>

#if !defined(OS_RTK)                    // <-@@@ <cyg/infra/diag.h>
#include <cyg/infra/diag.h>
#define UartSendTrace(x...)      diag_printf(x)
#else                                   // <-@@@ <cyg/infra/diag.h>
#if UTLB_DEBUG
#define diag_printf     UartSendTrace
#else
#define diag_printf(x...)
#endif
#endif                                  // <-@@@ <cyg/infra/diag.h>

/*
 * uTLB SPRs
 */

#define        UTLB_CFG               0
#define        UTLB_MASK              1
#define        UTLB_EIR               2
#define        UTLB_MR                4
#define        UTLB_TR                6
#define        UTLB_IQM_MR            20
#define        UTLB_IQM_TR            22
#define        UTLB_DQM_MR            24
#define        UTLB_DQM_TR            26
#define        UTLB_DSEG_MR           28
#define        UTLB_DSEG_MSK          29
#define        UTLB_DSEG_TR           30
#define        UTLB_ISEG_MR           32
#define        UTLB_ISEG_MSK          33
#define        UTLB_ISEG_TR           34

#define        UTLB_D_MR_0            48
#define        UTLB_D_MR_1            49
#define        UTLB_D_MR_2            50
#define        UTLB_D_MR_3            51
#define        UTLB_D_TR_0            52
#define        UTLB_D_TR_1            53
#define        UTLB_D_TR_2            54
#define        UTLB_D_TR_3            55

#define        UTLB_I_MR_0            56
#define        UTLB_I_MR_1            57
#define        UTLB_I_MR_2            58
#define        UTLB_I_MR_3            59
#define        UTLB_I_TR_0            60
#define        UTLB_I_TR_1            61
#define        UTLB_I_TR_2            62
#define        UTLB_I_TR_3            63


#define BIT0            0x00000001
#define BIT1            0x00000002
#define BIT2            0x00000004
#define BIT3            0x00000008
#define BIT4            0x00000010
#define BIT5            0x00000020
#define BIT6            0x00000040
#define BIT7            0x00000080
#define BIT8            0x00000100
#define BIT9            0x00000200
#define BIT10           0x00000400
#define BIT11           0x00000800
#define BIT12           0x00001000
#define BIT13           0x00002000
#define BIT14           0x00004000
#define BIT15           0x00008000
#define BIT16           0x00010000
#define BIT17           0x00020000
#define BIT18           0x00040000
#define BIT19           0x00080000
#define BIT20           0x00100000
#define BIT21           0x00200000
#define BIT22           0x00400000
#define BIT23           0x00800000
#define BIT24           0x01000000
#define BIT25           0x02000000
#define BIT26           0x04000000
#define BIT27           0x08000000
#define BIT28           0x10000000
#define BIT29           0x20000000
#define BIT30           0x40000000
#define BIT31           0x80000000

/* TR attribute bits */
#define UTLB_TR_CC            (BIT0)
#define UTLB_TR_CI            (BIT1)
#define UTLB_TR_IO            (BIT5)
#define UTLB_TR_SRE           (BIT6)
#define UTLB_TR_SWE           (BIT7)
#define UTLB_TR_URE           (BIT8)
#define UTLB_TR_UWE           (BIT9)
#define UTLB_TR_SXE           (BIT10)
#define UTLB_TR_UXE           (BIT11)
/* MR attribute bits */
#define UTLB_MR_VALID         (BIT0)

#define UTLB_TR_PPN_MASK      (0xffffe000)
#define UTLB_MR_VPN_MASK      (0xffffe000)

//#include <cyg/hal/hal_cache.h>
// Copy&paste from ecos kernel:
// TODO: get these value from a global system definition table
#define HAL_ICACHE_SIZE         32768
#define HAL_ICACHE_WAYS         4
#define HAL_ICACHE_LINE_SIZE    32
#define HAL_DCACHE_SIZE         16384
#define HAL_DCACHE_WAYS         4
#define HAL_DCACHE_LINE_SIZE    16

typedef unsigned long cyg_uint32;
#define CYG_ADDRESS cyg_uint32

#define HAL_DISABLE_INTERRUPTS( flag ) local_irq_save( flag )
#define HAL_RESTORE_INTERRUPTS( flag ) local_irq_restore( flag )

#include "sys_sys_chip.h"
static inline int HAL_DCACHE_U02_READY(void)
{
#define MMP_DCU_U02_ECO_ADDR	0x28000364
#define MMP_DCU_U02_ECO_BIT	8
    sys_ChipId_e revision_id;
    revision_id = sys_GetChipRevisionId();
    if(revision_id >= CHIP_ID(G1, U02)) {
        if (readl(MMP_DCU_U02_ECO_ADDR) & (0x1 << MMP_DCU_U02_ECO_BIT)) {
            return 1;
        }
    }
    return 0;
}

#define HAL_DRAIN_WRITE_BUFFER()                                \
    CYG_MACRO_START                                             \
    /* drain write buffer */                                    \
    /*__asm__ __volatile__( "l.lbs    r0, 0x0400(r0);" );*/     \
    __asm__ __volatile__( "l.syncwritebuffer;" );               \
    CYG_MACRO_END

void __activate_ITCM(void);
void __activate_DTCM(void);
void __deactivate_ITCM(void);
void __deactivate_DTCM(void);
void __enable_cache(void);
void __disable_cache(void);
void __clean_and_flush_data_cache_entry(u32 addr);
void __clean_and_flush_data_cache_buffer(u32 addr, s32 size);
void __invalidate_data_cache_buffer(u32 addr, s32 size);
void __invalidate_data_cache(void);
void __test_clean_dcache_drain_wbuffer(void);
void __invalidate_inst_cache(void);
void __drain_write_buffer(void);
void __flush_data_cache_buffer(u32 addr, s32 size);
void __enable_icache(void);
void __disable_icache(void);

u32 __set_page_table(u32 vAddr, u32 pAddr, u32 size, u32 *pageTableAddr, u32 pageSize);
u32 __clear_page_table(u32 vAddr);
u32 __init_page_table_ex(u32 vStart, u32 size, u32 *pageTableAddr, u32 pageSize, u32 attr);
u32 __set_page_table_ex(u32 vStart, u32 offset, u32 pAddr, u32 size, u32 *pageTableAddr, u32 pageSize, bool bLast, u32 attr);

static inline void HAL_DCACHE_FLUSH(unsigned int base, unsigned int size)
{
    unsigned int addr;
    unsigned int addr_end;
    unsigned int inten;
    unsigned int dummy;
    unsigned int dummy_addr;
    int mmp_dcu_u02_eco;

    HAL_DISABLE_INTERRUPTS(inten);
    mmp_dcu_u02_eco = HAL_DCACHE_U02_READY();
    addr = base & -(HAL_DCACHE_LINE_SIZE);
    addr_end = base + size + (HAL_DCACHE_LINE_SIZE - 1);
    addr_end &= -(HAL_DCACHE_LINE_SIZE);
    //HAL_DRAIN_WRITE_BUFFER();
    if (size < HAL_DCACHE_SIZE) {
        if (!mmp_dcu_u02_eco) {
            dummy_addr = addr & -(8192);
            __asm__ __volatile__ (
                "l.lbz %0,0(%1)\n" /* dummy read */
                : "=r"(dummy)
                : "r"(dummy_addr)
            );
            dummy_addr += 8192;
        }
        for (; addr < addr_end; addr += HAL_DCACHE_LINE_SIZE) {
            if (!mmp_dcu_u02_eco) {
                if (addr == dummy_addr) {
                    __asm__ __volatile__ (
                        "l.lbz %0,0(%1)\n" /* dummy read */
                        : "=r"(dummy)
                        : "r"(dummy_addr)
                    );
                    dummy_addr += 8192;
                }
            }
            __asm__ __volatile__ (
                "l.flush_invalidate 0(%0)\n"
                :
                : "r"(addr)
            );
        }
    } else {
        for (addr = 0; addr < HAL_DCACHE_SIZE/HAL_DCACHE_WAYS;
             addr += HAL_DCACHE_LINE_SIZE) {
            __asm__ __volatile__(
                "l.flush_line       0(%0), 0\n" /* way 0 */
                "l.flush_line       0(%0), 1\n" /* way 1 */
                "l.flush_line       0(%0), 2\n" /* way 2 */
                "l.flush_line       0(%0), 3\n" /* way 3 */
                "l.invalidate_line  0(%0), 0\n" /* way 0 */
                "l.invalidate_line  0(%0), 1\n" /* way 1 */
                "l.invalidate_line  0(%0), 2\n" /* way 2 */
                "l.invalidate_line  0(%0), 3\n" /* way 3 */
                :
                : "r"(addr)
            );
        }
    }
    HAL_DRAIN_WRITE_BUFFER();
    HAL_RESTORE_INTERRUPTS(inten);
}

static inline void HAL_DCACHE_INVALIDATE(unsigned int base, unsigned int size)
{
    unsigned int addr;
    unsigned int addr_end;
    unsigned int inten;
    unsigned int dummy;
    unsigned int dummy_addr;
    int mmp_dcu_u02_eco;

    HAL_DISABLE_INTERRUPTS(inten);
    mmp_dcu_u02_eco = HAL_DCACHE_U02_READY();
    addr = base;
    addr_end = base + size;
    //HAL_DRAIN_WRITE_BUFFER();
    if (size < HAL_DCACHE_SIZE) {
        if ((addr & (HAL_DCACHE_LINE_SIZE-1)) != 0) {
            addr &= -(HAL_DCACHE_LINE_SIZE);
            if (!mmp_dcu_u02_eco) {
                dummy_addr = addr & -(8192);
                __asm__ __volatile(
                    "l.lbz              %0,0(%1)\n" /* dummy read */
                    : "=r"(dummy)
                    : "r"(dummy_addr)
                );
            }
            __asm__ __volatile(
                "l.flush_invalidate 0(%0)\n"
                :
                : "r"(addr)
            );
            addr += HAL_DCACHE_LINE_SIZE;
            HAL_DRAIN_WRITE_BUFFER();
        }
        if ((addr_end & (HAL_DCACHE_LINE_SIZE-1)) != 0) {
            addr_end &= -(HAL_DCACHE_LINE_SIZE);
            if (!mmp_dcu_u02_eco) {
                dummy_addr = addr_end & -(8192);
                __asm__ __volatile(
                    "l.lbz              %0,0(%1)\n" /* dummy read */
                    : "=r"(dummy)
                    : "r"(dummy_addr)
                );
            }
            __asm__ __volatile(
                "l.flush_invalidate 0(%0)\n"
                :
                : "r"(addr_end)
            );
            HAL_DRAIN_WRITE_BUFFER();
        }
        if (!mmp_dcu_u02_eco) {
            dummy_addr = addr & -(8192);
            __asm__ __volatile(
                "l.lbz              %0,0(%1)\n" /* dummy read */
                : "=r"(dummy)
                : "r"(dummy_addr)
            );
            dummy_addr += 8192;
        }
        for (; addr < addr_end; addr += HAL_DCACHE_LINE_SIZE) {
            if (!mmp_dcu_u02_eco) {
                if (addr == dummy_addr) {
                    __asm__ __volatile__ (
                        "l.lbz %0,0(%1)\n" /* dummy read */
                        : "=r"(dummy)
                        : "r"(dummy_addr)
                    );
                    dummy_addr += 8192;
                }
            }
            __asm__ __volatile__(
                "l.invalidate 0(%0)\n"
                :
                : "r"(addr)
            );
        }
    } else {
        for (addr = 0; addr < HAL_DCACHE_SIZE/HAL_DCACHE_WAYS;
             addr += HAL_DCACHE_LINE_SIZE) {
            __asm__ __volatile__(
                "l.flush_line       0(%0), 0\n" /* way 0 */
                "l.flush_line       0(%0), 1\n" /* way 1 */
                "l.flush_line       0(%0), 2\n" /* way 2 */
                "l.flush_line       0(%0), 3\n" /* way 3 */
                "l.invalidate_line  0(%0), 0\n" /* way 0 */
                "l.invalidate_line  0(%0), 1\n" /* way 1 */
                "l.invalidate_line  0(%0), 2\n" /* way 2 */
                "l.invalidate_line  0(%0), 3\n" /* way 3 */
                : : "r"(addr)
            );
        }
        HAL_DRAIN_WRITE_BUFFER();
    }
    HAL_RESTORE_INTERRUPTS(inten);
}

static void inline HAL_DCACHE_INVALIDATE_LINE(unsigned int base, unsigned int size)
{
    unsigned int addr;
    unsigned int addr_end;
    unsigned int inten;
    HAL_DISABLE_INTERRUPTS(inten);
    if (size < (HAL_DCACHE_SIZE/HAL_DCACHE_WAYS)) {
        addr = base & -(HAL_DCACHE_LINE_SIZE);
        addr_end = base + size + (HAL_DCACHE_LINE_SIZE - 1);
        addr_end &= -(HAL_DCACHE_LINE_SIZE);
    } else {
        addr = 0;
        addr_end = HAL_DCACHE_SIZE/HAL_DCACHE_WAYS;
    }
    for (; addr < addr_end; addr += HAL_DCACHE_LINE_SIZE) {
        __asm__ __volatile__(
            "l.flush_line       0(%0), 0\n" /* way 0 */
            "l.flush_line       0(%0), 1\n" /* way 1 */
            "l.flush_line       0(%0), 2\n" /* way 2 */
            "l.flush_line       0(%0), 3\n" /* way 3 */
            "l.invalidate_line  0(%0), 0\n" /* way 0 */
            "l.invalidate_line  0(%0), 1\n" /* way 1 */
            "l.invalidate_line  0(%0), 2\n" /* way 2 */
            "l.invalidate_line  0(%0), 3\n" /* way 3 */
            :
            : "r"(addr)
        );
    }
    HAL_DRAIN_WRITE_BUFFER();
    HAL_RESTORE_INTERRUPTS(inten);
}

#define __HAL_DCACHE_INVALIDATE_ALL_WAYS(addr)      \
    CYG_MACRO_START                                 \
    __asm__ __volatile__ (                          \
        "b.invalidate_line  0(%0), 0\n" /* way 0 */ \
        "b.invalidate_line  0(%0), 1\n" /* way 1 */ \
        "b.invalidate_line  0(%0), 2\n" /* way 2 */ \
        "b.invalidate_line  0(%0), 3\n" /* way 3 */ \
        : : "r"(addr)                               \
        );                                          \
    CYG_MACRO_END

#define HAL_DCACHE_ENABLE()   MTSPR(SPR_SR, MFSPR(SPR_SR) | SPR_SR_DCE)
#define HAL_DCACHE_DISABLE()  MTSPR(SPR_SR, MFSPR(SPR_SR) & ~SPR_SR_DCE)

#define HAL_DCACHE_IS_ENABLED(_state_)                          \
    CYG_MACRO_START                                             \
    (_state_) = (1 - !(MFSPR(SPR_SR) & SPR_SR_DCE));            \
    CYG_MACRO_END

#define HAL_SET_DCACHE_ENABLED(enable)                          \
    MTSPR(SPR_SR, MFSPR(SPR_SR) | (SPR_SR_DCE & -(enable)))

// Invalidate the entire data cache
static inline void HAL_DCACHE_INVALIDATE_ALL(void)
{
    unsigned int addr;
    unsigned int inten;
    HAL_DISABLE_INTERRUPTS(inten);
    for (addr = 0; addr < HAL_DCACHE_SIZE/HAL_DCACHE_WAYS;
         addr += HAL_DCACHE_LINE_SIZE) {
        __asm__ __volatile__(
            "l.flush_line       0(%0), 0\n" /* way 0 */
            "l.flush_line       0(%0), 1\n" /* way 1 */
            "l.flush_line       0(%0), 2\n" /* way 2 */
            "l.flush_line       0(%0), 3\n" /* way 3 */
            "l.invalidate_line  0(%0), 0\n" /* way 0 */
            "l.invalidate_line  0(%0), 1\n" /* way 1 */
            "l.invalidate_line  0(%0), 2\n" /* way 2 */
            "l.invalidate_line  0(%0), 3\n" /* way 3 */
            :
            : "r"(addr)
        );
    }
    HAL_DRAIN_WRITE_BUFFER();
    HAL_RESTORE_INTERRUPTS(inten);
}

#define HAL_ICACHE_IS_ENABLED(_state_)                          \
    CYG_MACRO_START                                             \
    (_state_) = (1 - !(MFSPR(SPR_SR) & SPR_SR_ICE));            \
    CYG_MACRO_END

#define __HAL_ICACHE_SWITCH_WITH_RFE()          \
    CYG_MACRO_START                             \
    register cyg_uint32 epcr=0;                 \
    asm volatile (                              \
            "\tb.movhi   %0, hi(1999f)\n"       \
            "\tb.ori     %0, %0, lo(1999f)\n"   \
            "\tb.mtspr   r0, %0, %1\n"          \
            "\tb.rfe\n"                         \
        "1999:\n"                               \
            : "+r"(epcr) : "K"(SPR_EPCR_BASE)   \
        );                                      \
    CYG_MACRO_END


#define HAL_ICACHE_DISABLE()                            \
    CYG_MACRO_START                                     \
    register cyg_uint32 inten, esr0, epcr0;             \
    HAL_DISABLE_INTERRUPTS( inten );                    \
    esr0 = MFSPR(SPR_ESR_BASE);                         \
    epcr0 = MFSPR(SPR_EPCR_BASE);                       \
    MTSPR( SPR_ESR_BASE, MFSPR(SPR_SR) & ~SPR_SR_ICE ); \
    __HAL_ICACHE_SWITCH_WITH_RFE();                     \
    MTSPR( SPR_ESR_BASE, esr0 );                        \
    MTSPR( SPR_EPCR_BASE, epcr0 );                      \
    HAL_RESTORE_INTERRUPTS( inten & ~SPR_SR_ICE );      \
    CYG_MACRO_END


#define HAL_ICACHE_ENABLE()                                 \
    CYG_MACRO_START                                         \
    register cyg_uint32 inten, esr0, epcr0;                 \
    HAL_DISABLE_INTERRUPTS( inten );                        \
    esr0 = MFSPR(SPR_ESR_BASE);                             \
    epcr0 = MFSPR(SPR_EPCR_BASE);                           \
    MTSPR( SPR_ESR_BASE, (MFSPR(SPR_SR) | SPR_SR_ICE) );    \
    __HAL_ICACHE_SWITCH_WITH_RFE();                         \
    MTSPR( SPR_ESR_BASE, esr0 );                            \
    MTSPR( SPR_EPCR_BASE, epcr0 );                          \
    HAL_RESTORE_INTERRUPTS( inten | SPR_SR_ICE );                        \
    CYG_MACRO_END

#define HAL_SET_ICACHE_ENABLED(enable)                                  \
    CYG_MACRO_START                                                     \
    register cyg_uint32 inten, esr0, epcr0;                             \
    HAL_DISABLE_INTERRUPTS( inten );                                    \
    esr0 = MFSPR(SPR_ESR_BASE);                                         \
    epcr0 = MFSPR(SPR_EPCR_BASE);                                       \
    MTSPR( SPR_ESR_BASE, (MFSPR(SPR_SR) | (SPR_SR_ICE & -(enable))) );  \
    __HAL_ICACHE_SWITCH_WITH_RFE();                                     \
    MTSPR( SPR_ESR_BASE, esr0 );                                        \
    MTSPR( SPR_EPCR_BASE, epcr0 );                                      \
    HAL_RESTORE_INTERRUPTS( inten | (SPR_SR_ICE & -(enable)) );                       \
    CYG_MACRO_END

#define HAL_ICACHE_INVALIDATE_ALL()                             \
    CYG_MACRO_START                                             \
    int cache_enabled, addr;                                    \
                                                                \
    /* Save current cache mode (disabled/enabled) */            \
    HAL_ICACHE_IS_ENABLED(cache_enabled);                       \
                                                                \
    /* Disable cache, so that invalidation ignores cache tags */\
    HAL_ICACHE_DISABLE();                                       \
    addr = 0;                                     \
    do {                                                        \
        MTSPR(SPR_ICBIR, addr);                                 \
        addr += HAL_ICACHE_LINE_SIZE;                           \
    } while (addr < HAL_ICACHE_SIZE);                                         \
                                                                \
    /* Re-enable cache if it was enabled on entry */            \
    HAL_SET_ICACHE_ENABLED(cache_enabled);                      \
    CYG_MACRO_END

#define HAL_ICACHE_INVALIDATE( _base_ , _size_ )                             \
    CYG_MACRO_START                                                     \
    register cyg_uint32 size_once = _size_;                             \
    register CYG_ADDRESS base_once = _base_;                            \
    register CYG_ADDRESS addr, end;                                     \
    int cache_enabled;                                    \
                                                                                            \
    /* Save current cache mode (disabled/enabled) */            \
    HAL_ICACHE_IS_ENABLED(cache_enabled);                       \
                                                                \
    /* Disable cache, so that invalidation ignores cache tags */\
    HAL_ICACHE_DISABLE();                                       \
        \
    end = ((base_once + size_once + (HAL_ICACHE_LINE_SIZE-1)) &     \
           ~(HAL_ICACHE_LINE_SIZE-1));                              \
    for (addr = base_once & ~(HAL_ICACHE_LINE_SIZE-1);              \
         addr < end;                                                \
         addr += HAL_ICACHE_LINE_SIZE)                              \
    {                                                               \
        MTSPR(SPR_ICBIR, addr);                                 \
    }                                                               \
                                                            \
    /* Re-enable cache if it was enabled on entry */            \
    HAL_SET_ICACHE_ENABLED(cache_enabled);                      \
    CYG_MACRO_END

#endif //#ifndef __SDK_SIMULATION__

typedef enum IQMEM_Mux_tag
{
    IQMUX_CPU,
    IQMUX_CPUIO1,
    IQMUX_SLAVE,
    IQMUX_DMA
} iqmux_e;

void sys_Switch_IQMEM_Mux(iqmux_e mux);
void sys_hal_invoke_constructors(void);
void restore_dqmem(void);
void save_dqmem(void);

#endif //ndef __ASSEMBLER__

#endif  // __SYS_R2_CORE_H__

