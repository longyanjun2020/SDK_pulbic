/**
 * \file sys_sys_bootinit.h
 * \brief System boot init interface
*/
/****************************************************************************/

#ifndef __SYS_SYS_BOOTINIT_H__
#define __SYS_SYS_BOOTINIT_H__

#include "vm_types.ht"

/**
 * \brief macros
 */
#if defined(__TARGET__) && defined(__arm)
#define __ONCE_CALL_ON_BOOT__          __attribute__((section(".bootcalloncesection")))
#define __RO_CODE_ON_BOOT__            __attribute__((section(".RoCodeOnBoot")))
#define __RO_DATA_ON_BOOT__            __attribute__((section(".RoDataOnBoot")))
#define __RW_DATA_ON_BOOT__            __attribute__((section(".RwDataOnBoot")))
#define __RO_CODE_ON_BOOT_STAGE2__     __attribute__((section(".RoCodeOnBootStage2")))
#define __RO_DATA_ON_BOOT_STAGE2__     __attribute__((section(".RoDataOnBootStage2")))
#else
#define __ONCE_CALL_ON_BOOT__
#define __RO_CODE_ON_BOOT__
#define __RO_DATA_ON_BOOT__
#define __RW_DATA_ON_BOOT__
#define __RO_CODE_ON_BOOT_STAGE2__
#define __RO_DATA_ON_BOOT_STAGE2__
#endif



typedef enum {
	BIN_INFO_BASE     = 0,
	BIN_INFO_ADD_OF_SELECTED_BIN_HEADER = BIN_INFO_BASE+1,   //0xFFC
	BIN_INFO_SIZE_OF_SELECTED_BIN_POOL,                      //0cFF8
	BIN_INFO_SIZE_OF_SELECTED_BIN,                           //0xFF4
	BIN_INFO_ADD_OF_COMPRESSED_BIN_HEADER,                   //0xFF0
	BIN_INFO_ADD_OF_ZLIB_DICT,                               //0xFEC
	BIN_INFO_LAST
} _Bin_Info_Id_e;



typedef enum {
	BOOT_MEM_BASE     = 0,
	BOOT_MEM_HEAP_START_ADDR = BOOT_MEM_BASE,
	BOOT_MEM_SELECTED_BIN_POOL_START_ADDR,
	BOOT_MEM_PAGE_TABLE,
	BOOT_MEM_FREE_MEM = BOOT_MEM_HEAP_START_ADDR    /* take uninitial heap as free memory */
} _Boot_Mem_Map_Id_e;

u32 * _take_memory_from_uninitial_heap(u32);
u32 * sys_get_heap_start_address(void);
u32 sys_get_imi2_end_address(void);
u32 _take_bin_info(u32);

#endif  // __SYS_SYS_BOOTINIT_H__
