#ifndef __SYS_SYS_CORE_H__
#define __SYS_SYS_CORE_H__

#include "vm_types.ht"
#include "sys_MsWrapper_cus_os_int_pub.h"

#define _SYS_DPM	(_SYS | LEVEL_19)
#define _SYS_SLDLM	(_SYS | LEVEL_20)

#define _SLDLM_TRACE(fmt, ...)       _TRACE((_SYS_SLDLM, fmt, ##__VA_ARGS__))

#if 0
#define _DPM_TRACE(fmt, ...)
#elif 0
extern void sys_UartPrintf(const char *fmt, ...);
#define _DPM_TRACE(fmt, ...)        sys_UartPrintf(fmt, ##__VA_ARGS__)
#elif 1
#define _DPM_TRACE(fmt, ...)        _TRACE((_SYS_DPM, fmt, ##__VA_ARGS__))
#endif

void sys_Activate_ITCM(void);
void sys_Activate_DTCM(void);
void sys_Deactivate_ITCM(void);
void sys_Deactivate_DTCM(void);
void sys_Enable_cache(void);
void sys_Disable_cache(void);
void sys_Clean_and_flush_data_cache_entry(u32 addr);
void sys_Clean_and_flush_data_cache_buffer(u32 addr, s32 size);
void sys_Invalidate_data_cache_buffer(u32 addr, s32 size);
void sys_Invalidate_data_cache(void);
void sys_test_clean_dcache_drain_wbuffer(void);
void sys_Invalidate_inst_cache(void);
void sys_Drain_write_buffer(void);
void sys_flush_data_cache_buffer(u32 addr, s32 size);
void sys_Enable_icache(void);
void sys_Disable_icache(void);

u32 sys_Set_Pagetable(u32 vAddr, u32 pAddr, u32 size, u32 *pageTableAddr, u32 pageSize);


MsIntMask_e sys_Set_Pagetable_Start(void);
void sys_Set_Pagetable_End(MsIntMask_e context);
u32 sys_Set_Pagetable_Entry(u32 vAddr, u32 pAddr, u32 *pageTableAddr, u32 pageSize, u32 mmuAccessProtection, u32 mmuCachedBuffered);
u32 sys_Set_Pagetable_Addr(u32 vAddr, u32 *pageTableAddr, u32 pageSize);
u32 sys_Init_PagetableEx(u32 vStart, u32 size, u32 *pageTableAddr, u32 pageSize, u32 attr);
u32 sys_Set_PagetableEx(u32 vStart, u32 offset, u32 pAddr, u32 size, u32 *pageTableAddr, u32 pageSize, bool bLast, u32 attr);
u32 sys_Clear_Pagetable(u32 vAddr);


#endif  // __SYS_ARM_CORE_H__

