#ifndef __SYS_ARM_H__
#define __SYS_ARM_H__

#include "vm_types.ht"

void sys_Delay( u32 i_u32_Delay );
void sys_Activate_ITCM(void);
void sys_Activate_DTCM(void);
void sys_Deactivate_ITCM(void);
void sys_Deactivate_DTCM(void);
#define sys_Enable_cache() 
#define sys_Disable_cache()
void sys_Clean_and_flush_data_cache_entry(u32 * addr);
void sys_Clean_and_flush_data_cache_buffer(u32 addr, s32 size);
void sys_Invalidate_data_cache_buffer(u32 addr, s32 size);
void sys_Invalidate_data_cache(void);
void sys_Drain_write_buffer(void);
#define sys_Enable_icache() 
#define sys_Disable_icache() 

#endif  // __SYS_ARM_H__
