/******************************************************************************/
/* File    : arm_mmu.h                                                        */
/*----------------------------------------------------------------------------*/
/* Scope   : ARM MMU related definitions                                      */
/*                                                                            */
/******************************************************************************/
#ifndef __ARM_MMU_H__
#define __ARM_MMU_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "plfcfg.h"
#include "cpu_mem_map.h"
#include "riubridge.h"


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
/* L1 page table entry ID */
#define PTE_FAULT_ID                    0x0
#define LVL1_COARSE_ID                  0x1
#define LVL1_SECT_ID                    0x2
#define LVL1_FINE_ID                    0x3
#define LVL2_LARGE_ID                   0x1
#define LVL2_SMALL_ID                   0x2
#define LVL2_TINY_ID                    0x3
#define COARSE_PTE_COUNT                256
#define SECT_PTE_COUNT                  4096
#define FINE_PTE_COUNT                  1024

/* Write buffer and cache configurations */
#define ARM_UNCACHEABLE                 0
#define ARM_CACHEABLE                   1
#define ARM_UNBUFFERABLE                0
#define ARM_BUFFERABLE                  1

/* Access right configurations */
#define ARM_ACCESS_PERM_NONE_NONE       0
#define ARM_ACCESS_PERM_RO_NONE         0
#define ARM_ACCESS_PERM_RO_RO           0
#define ARM_ACCESS_PERM_RW_NONE         1
#define ARM_ACCESS_PERM_RW_RO           2
#define ARM_ACCESS_PERM_RW_RW           3

/* ARM Domain Access Control Bit Masks */
#define ARM_ACCESS_TYPE_NO_ACCESS(domain_num)   (0x0 << (domain_num)*2)
#define ARM_ACCESS_TYPE_CLIENT(domain_num)      (0x1 << (domain_num)*2)
#define ARM_ACCESS_TYPE_MANAGER(domain_num)     (0x3 << (domain_num)*2)

/* Page size definitions */
#define SECT_PAGE_SIZE          1024
#define LARGE_PAGE_SIZE         64
#define SMALL_PAGE_SIZE         4
#define TINY_PAGE_SIZE          1

/* Page Table Control Block Address Definitions */
#if defined(__MSW8522__) || defined(__MSW8556__)
#define MASTER_PT_ADDR          (SYSNUM_MMU_PAGETBL_ADDR + 0x0000)
#define MASTER_PT_VA            COMMON_START_ADDRESS
#define IMI1_PT_ADDR            (SYSNUM_MMU_PAGETBLLV2_ADDR + 0x0000)
#define IMI1_PT_VA              IRAM_START_ADDRESS
#define IMI2_PT_ADDR            (SYSNUM_MMU_PAGETBLLV2_ADDR + 0x0400)
#define IMI2_PT_VA              USR0_START_ADDRESS
#else
#define MASTER_PT_ADDR          (SYSNUM_MMU_PAGETBL_ADDR + 0x1000)
#define MASTER_PT_VA            COMMON_START_ADDRESS
#define IMI1_PT_ADDR            (SYSNUM_MMU_PAGETBL_ADDR + 0x0000)
#define IMI1_PT_VA              IRAM_START_ADDRESS
#define IMI2_PT_ADDR            (SYSNUM_MMU_PAGETBL_ADDR + 0x0400)
#define IMI2_PT_VA              USR0_START_ADDRESS
#endif

/* Region Control Block Address Definitions */
#define ROM_CODE_START_COMM_ADDR    COMMON_START_ADDRESS
#define ROM_CODE_START_PHY_ADDR     IROM_START_ADDRESS
#define ROM_CODE_PAGE_SIZE          SECT_PAGE_SIZE
#define ROM_CODE_NUM_PAGES          1
#define MEM0_RO_START_ADDR          MEM0_START_ADDRESS
#define MEM0_RO_PAGE_SIZE           SECT_PAGE_SIZE
#define MEM0_RO_NUM_PAGES           1
#define MEM3_RO_START_ADDR          MEM3_START_ADDRESS
#define MEM3_RO_PAGE_SIZE           SECT_PAGE_SIZE
#define MEM3_RO_NUM_PAGES           1
#if defined(__MSW8522__) || defined(__MSW8556__)
#define IMI1_DATA_START_ADDR        (IRAM_START_ADDRESS + 0x4000)
#define IMI1_DATA_PAGE_SIZE         SMALL_PAGE_SIZE
#define IMI1_DATA_NUM_PAGES         2
#define IMI1_PAGETBL_START_ADDR     SYSNUM_MMU_PAGETBL_ADDR
#define IMI1_PAGETBL_PAGE_SIZE      SMALL_PAGE_SIZE
#define IMI1_PAGETBL_NUM_PAGES      4
#define IMI2_UNCACHED_START_ADDR    USR0_START_ADDRESS
#define IMI2_UNCACHED_PAGE_SIZE     SMALL_PAGE_SIZE
#define IMI2_UNCACHED_NUM_PAGES     6
#define IMI2_CACHED_UNBUF_START_ADDR    (USR0_START_ADDRESS + 0x6000)
#define IMI2_CACHED_UNBUF_PAGE_SIZE     SMALL_PAGE_SIZE
#define IMI2_CACHED_UNBUF_NUM_PAGES     1
#define IMI2_CACHED_START_ADDR      (USR0_START_ADDRESS + 0x7000)
#define IMI2_CACHED_PAGE_SIZE       SMALL_PAGE_SIZE
#define IMI2_CACHED_NUM_PAGES       13
#define IMI2_CACHED_TEST_IE_START_ADDR      USR0_START_ADDRESS
#define IMI2_CACHED_TEST_IE_PAGE_SIZE       SMALL_PAGE_SIZE
#define IMI2_CACHED_TEST_IE_NUM_PAGES       24
#else
#define IMI1_DATA_START_ADDR        IRAM_START_ADDRESS
#define IMI1_DATA_PAGE_SIZE         SMALL_PAGE_SIZE
#define IMI1_DATA_NUM_PAGES         3
#define IMI1_PAGETBL_START_ADDR     SYSNUM_MMU_PAGETBL_ADDR
#define IMI1_PAGETBL_PAGE_SIZE      SMALL_PAGE_SIZE
#define IMI1_PAGETBL_NUM_PAGES      5
#define IMI2_UNCACHED_START_ADDR    USR0_START_ADDRESS
#define IMI2_UNCACHED_PAGE_SIZE     SMALL_PAGE_SIZE
#define IMI2_UNCACHED_NUM_PAGES     18
#define IMI2_CACHED_START_ADDR      (USR0_START_ADDRESS + 0x12000)
#define IMI2_CACHED_PAGE_SIZE       SMALL_PAGE_SIZE
#define IMI2_CACHED_NUM_PAGES       46
#endif
#define APB_REG_START_ADDR          PERIPH_START_ADDRESS
#define APB_REG_PAGE_SIZE           SECT_PAGE_SIZE
#define APB_REG_NUM_PAGES           64
#define RIU_REG_START_ADDR          HAL_RIU_BRIDGE_BASE
#define RIU_REG_PAGE_SIZE           SECT_PAGE_SIZE
#define RIU_REG_NUM_PAGES           64
#define DMC_TGT_START_ADDR          MEM0_START_ADDRESS
#define DMC_TGT_PAGE_SIZE           SECT_PAGE_SIZE
#if defined(__MSW8522__) || defined(__MSW8556__)
#define DMC_TGT_UNCACHE_START_ADDR  (MEM0_START_ADDRESS + 0x800000)
#define DMC_TGT_UNCACHE_PAGE_SIZE   SECT_PAGE_SIZE
#define DMC_TGT_UNCACHE_NUM_PAGES   2
#endif
#define DMC_TGT_NUM_PAGES           64
#define NOR_TGT_START_ADDR          MEM0_START_ADDRESS
#define NOR_TGT_PAGE_SIZE           SECT_PAGE_SIZE
#define NOR_TGT_NUM_PAGES           64
#define SPI_TGT_START_ADDR          MEM3_START_ADDRESS
#define SPI_TGT_PAGE_SIZE           SECT_PAGE_SIZE
#define SPI_TGT_NUM_PAGES           64
#define PSRAM_TGT_START_ADDR        MEM1_START_ADDRESS
#define PSRAM_TGT_PAGE_SIZE         SECT_PAGE_SIZE
#if defined(__MSW8522__) || defined(__MSW8556__)
#define PSRAM_TGT_UNCACHE_START_ADDR    (MEM1_START_ADDRESS + 0x3E0000)
#define PSRAM_TGT_UNCACHE_PAGE_SIZE     SECT_PAGE_SIZE
#define PSRAM_TGT_UNCACHE_NUM_PAGES     2
#endif
#define PSRAM_TGT_NUM_PAGES         64
#define DPRAM_TGT_START_ADDR        SHIFACE_DPRAM_START_ADDRESS
#define DPRAM_TGT_PAGE_SIZE         SECT_PAGE_SIZE
#define DPRAM_TGT_NUM_PAGES         1

/* Definitions for various page table field insertions */
#define VA_TO_SECT_PAGE_IDX_OFF     20
#define VA_TO_COARSE_PAGE_IDX_OFF   12
#define VA_TO_COARSE_PAGE_IDX_MSK   0x000FF000
#define VA_TO_FINE_PAGE_IDX_OFF     10
#define VA_TO_FINE_PAGE_IDX_MSK     0x000FFC00
#define VA_TO_LARGE_BASE_OFF        16
#define VA_TO_SMALL_BASE_OFF        12
#define VA_TO_TINY_BASE_OFF         10
#define COARSE_LARGE_PAGE_MULT      (LARGE_PAGE_SIZE / SMALL_PAGE_SIZE)
#define FINE_LARGE_PAGE_MULT        (LARGE_PAGE_SIZE / TINY_PAGE_SIZE)
#define FINE_SMALL_PAGE_MULT        (SMALL_PAGE_SIZE / TINY_PAGE_SIZE)
#define COARSE_PAGETBL_BASE_OFF     10
#define FINE_PAGETBL_BASE_OFF       12


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------
/* PTCB, page table control block structure */
typedef struct Pagetable_s
{
    unsigned int    vAddr;
    unsigned int    ptAddr;
    unsigned int    masterPtAddr;
    unsigned int    type;
    unsigned int    dom;
} Pagetable_t;

/* RCB, region control block structure */
typedef struct Region_s
{
    unsigned int    vAddr;
    unsigned int    pAddr;
    unsigned short  pageSize;
    unsigned short  numPages;
    unsigned char   AP;
    unsigned char   buffer;
    unsigned char   cached;
    Pagetable_t const   *ptrPT;
} Region_t;


//------------------------------------------------------------------------------
// Global Variable Declarations
//------------------------------------------------------------------------------
/* Page Table Control Block configured in ROM */
extern Pagetable_t const    masterPT;
extern Pagetable_t const    imi1PT;
extern Pagetable_t const    imi2PT;

#ifndef __APCS_ROPI
/* Region Control Block Declarations */
extern Region_t const       romCommRegion;
extern Region_t const       romPhyRegion;
extern Region_t const       mem0Region;
#if defined(__MSW8522__) || defined(__MSW8556__)
extern Region_t const       mem3Region;
#endif
extern Region_t const       imi1DataRegion;
extern Region_t const       imi1PageTblRegion;
#if defined(__MSW8522__) || defined(__MSW8556__)
extern Region_t const       imi2LV2PageTblRegion;
#endif
extern Region_t const       imi2UncachedRegion;
extern Region_t const       imi2CachedRegion;
extern Region_t const       apbRegion;
extern Region_t const       riuRegion;
extern Region_t const       dmcTgtRegion;
#if defined(__MSW8522__) || defined(__MSW8556__)
extern Region_t const       dmcTgtUncacheRegion;
#endif
extern Region_t const       norTgtRegion;
extern Region_t const       spiTgtRegion;
extern Region_t const       psramTgtRegion;
#if defined(__MSW8522__) || defined(__MSW8556__)
extern Region_t const       psramTgtUncacheRegion;
#endif
extern Region_t const       dpramTgtRegion;
#else // __APCS_ROPI
#ifdef __SDAPPRAM_PI__
extern Region_t             dmcTgtRegion;
#if defined(__MSW8522__) || defined(__MSW8556__)
extern Region_t             dmcTgtUncacheRegion;
#endif
extern Region_t             norTgtRegion;
extern Region_t             spiTgtRegion;
extern Region_t             psramTgtRegion;
#endif // __SDAPPRAM_PI__
extern Region_t             dpramTgtRegion;
#endif // __APCS_ROPI

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------
void    hal_mmu_pageTbl_init(Pagetable_t const *pt);
int     hal_mmu_region_map(Region_t const *region);
int     hal_mmu_pageTbl_attach(Pagetable_t const *pt);
void    hal_mmu_init(void);

#endif /* __ARM_MMU_H__ */
