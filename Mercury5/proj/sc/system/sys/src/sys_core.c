/**************************************************************************/
/*  File    : sys_core.c                                                  */
/*-------------------------------------------------------------           */
/*  Scope   :    CPU core functions                                       */
/*                                                                        */
/*  Contents:                                                             */
/*           								  */
/*                                                                        */
/*  Changes    :                                                          */
/**************************************************************************/
#include "kernel.h"
#include "vm_types.ht"
#include "sys.ho"
#include "sys_rtk_ho.h"
#include "hal_drv_util.h"

#ifdef __RTK_OVER_R2
#include "sys_r2_core.h"
#else
#include "sys_arm_copro.h"
#include "sys_arm_core.h"
#endif

#include "sys_sys_dpm_mgr.h"

#define SIZE_1M (0x00100000)
#define REMAINDER_SIZE_1M (0x00100000-1)
#define ALIGN_SIZE_1M (~REMAINDER_SIZE_1M)

//#define __NONCACHED_BUFFER__

extern u32 limitRAMsSize;
#ifdef __NONCACHED_BUFFER__

#define NON_CACHE_VSTART_ADDRESS 0x90000000
#define NON_CACHE_PSTART_ADDRESS (((u32)&Image__RAM__Base)&~((1<<20)-1))
#define NON_CACHE_AREA_SIZE (limitRAMsSize&0xFFF00000)

extern u32 sys_GetModuleRAMsize(void);
#ifdef __PSRAM_PERF_TEST__
extern L1PTE_t psram_nor_Pte[4] ;
#endif


u32 sys_GetNonCacheOffsetAddress(void)
{
	return NON_CACHE_VSTART_ADDRESS-NON_CACHE_PSTART_ADDRESS;
}

bool sys_IsNonCacheAddress(u32 nVAddr)
{
	if (nVAddr >= NON_CACHE_VSTART_ADDRESS
		&& nVAddr <= (NON_CACHE_VSTART_ADDRESS+NON_CACHE_AREA_SIZE))
		return TRUE;

	return FALSE;
}

#endif

#ifdef __FIXME__
void sys_Activate_ITCM(void)
{
	__activate_ITCM();
}

void sys_Deactivate_ITCM(void)
{
	__deactivate_ITCM();
}

void sys_Activate_DTCM(void)
{
	__activate_DTCM();
}

void sys_Deactivate_DTCM(void)
{
	__deactivate_DTCM();
}
#endif


void sys_Enable_cache(void) {
#ifdef __RTK_OVER_R2__
    if (sys_init_mmu()==1) { // MMU already ON
        HAL_DCACHE_ENABLE();
    }
#else
	extern bool CusIsNandEnabled(void);
    extern void sys_mmu_wrapper_fine_page_table_set(u32 vAddr, u32 size);
    extern void sys_mmu_wrapper_small_page_table_set(void);

	MsIntMask_e context;
#ifdef __FIXME__
	u32 idx_common_start;
#endif
	u32 i , idx_xram=0xffffffff, size_xram=0;
	mmu_errorCode_e err = ERR_MMU_NO_ERROR;
	u32 no_access_start;
	u32 no_access_size;
	u32 mmu_size_1mb_align = 0;
	u32 mmu_start_1mb_align = 0;

	// clear interrupt, disable mmu
	context = mmu_begin_modify_translation_table();

	// retire all memory, NOT BUFFERED AND NOT CACHED
	if (err==ERR_MMU_NO_ERROR)
	{
		mmu_translation_table_reset(DOMAIN_15);
	}

#ifdef __NONCACHED_BUFFER__
	// remap
	mmu_translation_table_remap(NON_CACHE_VSTART_ADDRESS, NON_CACHE_PSTART_ADDRESS, NON_CACHE_AREA_SIZE);
#endif

	if((u32)&Image$$XRAM$$Base & (64*SIZE_1M-1))// It is NAND if &Image$$XRAM$$Base is not 64M alignment
	{
		i = 0;
		while(_g_atPte[i].nStartAddrV != END_OF_L1PTE)
		{
			if(_g_atPte[i].nStartAddrV == (u32)&Image$$XRAM$$Base)
			{
				if(_g_atPte[i].nSize == (64*SIZE_1M))
				{
					idx_xram = i;
					size_xram = ((64*SIZE_1M)-_g_atPte[i].nStartAddrV);
				}
				break;
			}
			i++;
		}
	}

	i = 0;
	while(_g_atPte[i].nStartAddrV != END_OF_L1PTE)
	{
		/* MMU : using 1M section page */
		mmu_start_1mb_align = _g_atPte[i].nStartAddrV & ALIGN_SIZE_1M ;
		//set CLIENT mode with larger size
		mmu_size_1mb_align = (((i == idx_xram) ? size_xram : _g_atPte[i].nSize) + REMAINDER_SIZE_1M) & ALIGN_SIZE_1M;
		mmu_set_attribution(mmu_start_1mb_align, mmu_size_1mb_align, PTE_OP_CLIENT_MODE); //setting domain from NO ACCESS to CLIENT

		//set attribution with (smaller) truncated size
		mmu_size_1mb_align = ((i == idx_xram) ? (size_xram + REMAINDER_SIZE_1M) : _g_atPte[i].nSize) & ALIGN_SIZE_1M;
		if (PTE_OP_RO == (_g_atPte[i].nPteOption & PTE_OP_RW_FIELD))
		{
			mmu_set_attribution(mmu_start_1mb_align, mmu_size_1mb_align, PTE_OP_RO);
		}
		if (_g_atPte[i].nPteOption & PTE_OP_CACHED)
		{
			mmu_set_attribution(mmu_start_1mb_align, mmu_size_1mb_align, PTE_OP_CACHED);
		}
		if (_g_atPte[i].nPteOption & PTE_OP_BUFFERED)
		{
			mmu_set_attribution(mmu_start_1mb_align, mmu_size_1mb_align, PTE_OP_BUFFERED);
		}

		i++;
	}

    /* The memory layout is following. Since the start address of _g_atPtep[X] is not aligned to 1M,
        we need to process the connection of "RO"(_g_atPtep[X]) and  "RW+ZI"(g_atPtep[X+1])

        | RO |          |  _g_atPtep[X]   |
        -----           -------------------
        | RW |   -->    |                 |
        -----           |  _g_atPtep[X+1] |
        | ZI |          |                 |

        the tail address does not aligned to 1M --> using 1k tiny page to do 1K MMU
    */
#ifdef __FIXME__
	if (CusIsNandEnabled() == TRUE)
    {
        i = idx_common_start = 0;
        while(_g_atPte[i].nStartAddrV != END_OF_L1PTE)
        {
            if(_g_atPte[i].nStartAddrV == COMMON_START_ADDRESS)
            {
                idx_common_start = i;
                break;
            }
            i++;
        }

        mmu_size_1mb_align = _g_atPte[idx_common_start].nSize & ALIGN_SIZE_1M ;
        if(mmu_size_1mb_align != _g_atPte[idx_common_start].nSize )
        {
            sys_mmu_wrapper_fine_page_table_set(mmu_size_1mb_align, _g_atPte[idx_common_start].nSize-mmu_size_1mb_align);
        }
    }
    else
    {
        // set mmu if __EXTRACT_BOOT_IMAGE__ is on, set mmu in XRAM region
        sys_mmu_wrapper_fine_page_table_set(0,0);
    }
    sys_mmu_wrapper_small_page_table_set();
#endif



	if (CusIsNandEnabled() == TRUE)
	{
		no_access_start = (COMMON_START_ADDRESS + limitRAMsSize);
		no_access_size = (COMMON_END_ADDRESS - no_access_start + 1);
	}
	else
	{
		no_access_start = (MEM1_START_ADDRESS + limitRAMsSize);
		no_access_size = (MEM1_END_ADDRESS - no_access_start + 1);
	}
	//setting no access according to MCP RAM size
	mmu_set_attribution(no_access_start, no_access_size, PTE_OP_NO_ACCESS);

#if defined(__NULL_READ_WRITE_EXEC_PROTECT__)
	if(err == ERR_MMU_NO_ERROR)
	{
		err = mmu_coarse_page_table_init_high();
	}
	if(err == ERR_MMU_NO_ERROR)
	{
		err = mmu_coarse_page_table_init_low(SysGetMPFlag());
	}
#endif

	// set 1st 4KB page as cached/non-buffered, and rest as cached/buffered
	imi0_coarse_page_table_init();

#ifdef __FIXME__
    if (TRUE == DpmIsRomRemapToEmmiSldpmNeighborhood())
    {
        // map rom remap section to the 1 or 2MB VA before EMMI SLDPM
        mmu_translation_table_remap_to_emmi_sldpm_neighborhood(DpmGetRomRemapStartAddr(), 0x0, DpmGetRomRemapAddrLen());
    }
#endif

	// end the modification process
	mmu_end_modify_translation_table(context);

	if (err==ERR_MMU_NO_ERROR)
	{
		u32 base_adress = mmu_get_translation_table();
		if (base_adress)
		{
			__enable_mmu((u32*)base_adress);
		}
		else
		{
			err=ERR_MMU_FAILED;
		}
	}
#endif
}

void sys_Disable_cache(void)
{
#ifdef __RTK_OVER_R2__
    HAL_DCACHE_INVALIDATE_ALL();
    // Disable the data cache
    HAL_DCACHE_DISABLE();
#else
	__disable_mmu();
#endif
}


void sys_Enable_icache(void)
{
	__enable_icache();
}

void sys_Disable_icache(void)
{
	__disable_icache();
}

void sys_Clean_and_flush_data_cache_entry(u32 addr)
{
    __clean_and_flush_data_cache_entry(addr);
}

void sys_Clean_and_flush_data_cache_buffer(u32 addr, s32 size)
{
    __clean_and_flush_data_cache_buffer(addr, size);
}

void sys_Invalidate_data_cache_buffer(u32 addr, s32 size)
{
    __invalidate_data_cache_buffer(addr, size);
}

void sys_Invalidate_data_cache(void)
{
    __invalidate_data_cache();
}

void sys_test_clean_dcache_drain_wbuffer(void)
{
    __test_clean_dcache_drain_wbuffer();
}

void sys_Invalidate_inst_cache(void)
{
    __invalidate_inst_cache();
}

void sys_Drain_write_buffer(void)
{
    __drain_write_buffer();
}

void sys_flush_data_cache_buffer(u32 addr, s32 size)
{
    __flush_data_cache_buffer(addr, size);
}

u32 sys_Set_Pagetable(u32 vAddr, u32 pAddr, u32 size, u32 *pageTableAddr, u32 pageSize)
{
    return __set_page_table(vAddr, pAddr, size, pageTableAddr, pageSize);
}

MsIntMask_e sys_Set_Pagetable_Start()
{
    return __start_set_page_table();
}

void sys_Set_Pagetable_End(MsIntMask_e context)
{
    __end_set_page_table(context);
}

u32 sys_Set_Pagetable_Entry(u32 vAddr, u32 pAddr, u32 *pageTableAddr, u32 pageSize, u32 mmuAccessProtection, u32 mmuCachedBuffered)
{
    return __set_page_table_entry(vAddr, pAddr, pageTableAddr, pageSize, mmuAccessProtection, mmuCachedBuffered);
}

u32 sys_Set_Pagetable_Addr(u32 vAddr, u32 *pageTableAddr, u32 pageSize)
{
    return __set_page_table_Addr(vAddr, pageTableAddr, pageSize);
}

u32 sys_Init_PagetableEx(u32 vStart, u32 size, u32 *pageTableAddr, u32 pageSize, u32 attr)
{
    return __init_page_table_ex(vStart, size, pageTableAddr, pageSize, attr);
}

u32 sys_Set_PagetableEx(u32 vStart, u32 offset, u32 pAddr, u32 size, u32 *pageTableAddr, u32 pageSize, bool bLast, u32 attr)
{
    return __set_page_table_ex(vStart, offset, pAddr, size, pageTableAddr, pageSize, bLast, attr);
}

u32 sys_Clear_Pagetable(u32 vAddr)
{
    return __clear_page_table(vAddr);
}

#ifdef __RTK_OVER_R2__
#endif

