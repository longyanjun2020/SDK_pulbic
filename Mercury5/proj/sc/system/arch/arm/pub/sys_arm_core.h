#ifndef __SYS_ARM_CORE_H__
#define __SYS_ARM_CORE_H__

#include "vm_types.ht"

#include "sys_MsWrapper_cus_os_int_pub.h"

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
MsIntMask_e __start_set_page_table(void);
void __end_set_page_table(MsIntMask_e context);
u32 __set_page_table_entry(u32 vAddr, u32 pAddr, u32 *pageTableAddr, u32 pageSize, u32 mmuAccessProtection, u32 mmuCachedBuffered);
u32 __set_page_table_Addr(u32 vAddr, u32 *pageTableAddr, u32 pageSize);
u32 __clear_page_table(u32 vAddr);
u32 __init_page_table_ex(u32 vStart, u32 size, u32 *pageTableAddr, u32 pageSize, u32 attr);
u32 __set_page_table_ex(u32 vStart, u32 offset, u32 pAddr, u32 size, u32 *pageTableAddr, u32 pageSize, bool bLast, u32 attr);

#ifdef __PSRAM_PERF_TEST__
void nor_psram_cache_en(void);
#endif
void sys_config_null_attribute(void);
void sys_config_null_attribute_ex(u8 op);

enum
{
  SYS_ABORT_NORMAL = 0,
  SYS_ABORT_DPM
};

/* for mmu setting */
#define PTE_OP_CACHED			(0x01<<3)
#define PTE_OP_BUFFERED			(0x01<<2)
#define PTE_OP_RO           (0x01<<10)
#define PTE_OP_RW           (0x03<<10)
#define PTE_OP_RW_FIELD     (0x03<<10)
#define PTE_OP_NO_ACCESS    (0xF<<5)
#define PTE_OP_CLIENT_MODE  (0x1<<5)


/* for mmu setting */
#if defined(__CORTEX_A7__)
enum
{
	FAULT_PAGE_TABLE = 0x00,		// 00000, indicates this is a fault		page table entry
	COARSE_PAGE_TABLE =0x01,	// 00001, indicates this is a coarse	page table entry, reserved for compiling successfully
	SECTION_1M_ENTRY = 0x02,	// 00010, indicates this is a section	page table entry
	FINE_PAGE_TABLE = 0x03,		// 00011, indicates this is a fine		page table entry, reserved for compiling successfully
};

#define DATA_CACHE_ENTRY_SIZE 64 // 64 bytes per data cache entry
#define DATA_CACHE_ENTRY_SHIFT 6 // 64 bytes per data cache entry

#else
enum
{
	FAULT_PAGE = 0,			//indicates this is a fault	page
	LARGE_64KB_PAGE = 1,	//indicates this is a 64KB	page
	SMALL_4KB_PAGE = 2,		//indicates this is a 4KB	page
	TINY_1KB_PAGE = 3		//indicates this is a 1KB	page
};

enum
{
	FAULT_PAGE_TABLE = 0x00,	// 00000, indicates this is a fault   page table entry
	COARSE_PAGE_TABLE =0x11,	// 10001, indicates this is a coarse  page table entry
	SECTION_1M_ENTRY = 0x12,	// 10010, indicates this is a section page table entry
	FINE_PAGE_TABLE = 0x13,		// 10011, indicates this is a fine    page table entry
};

#define DATA_CACHE_ENTRY_SIZE 32 // 32 bytes per data cache entry
#define DATA_CACHE_ENTRY_SHIFT 5 // 32 bytes per data cache entry

#endif
#endif  // __SYS_ARM_CORE_H__

