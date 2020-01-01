#ifndef _INCLUDE_MMPF_CPU_H_
#define _INCLUDE_MMPF_CPU_H_

#include "config_fw.h"

#if (1)

// ITCM Address
#define CPUA_ITCM_ADDR          0x00800000
#define CPUB_ITCM_ADDR          0x00900000
#define CPUB_ITCM_SIZE          0x00001000      // 4K

// SRAM Address
#define CPUB_SRAM_ADDR          MMU_TRANSLATION_TABLE_ADDR
#define CPUB_SRAM_SIZE          0x00004000      // 16K

// DRAM Address for uC/OS2
#define CPUB_DRAM_ADDR_UCOS2    0x04E00000
#define CPUB_DRAM_SIZE_UCOS2    0x00020000      // 128K

// DRAM Address for Linux
#define CPUB_DRAM_ADDR_LINUX    0x03000000      // DRAM strart address for Linux
#define CPUB_DRAM_SIZE_LINUX    0x02000000      // DRAM size for Linux
#define CPUB_ZIMG_ADDR_LINUX    0x04000000      // zImage entry address
#define CPUB_RDSK_ADDR_LINUX    0x04800000      // initrd start address
#define CPUB_RDSK_SIZE_LINUX    0x00800000      // initrd size


#define CPUB_ITCM_FILE_UCOS2    "SD:\\ITCM_EXE_UCOS2"
#define CPUB_DRAM_FILE_UCOS2    "SD:\\ALL_DRAM_UCOS2"

#define CPUB_ITCM_FILE_LINUX    "SD:\\ITCM_EXE_LINUX"
#define CPUB_DRAM_FILE_LINUX    "SD:\\zImage"
#define CPUB_RDSK_FILE_LINUX    "SD:\\rdisk.gz"

// This definition indicats the rootfs type in Linux
// Defined, root fs is initrd
// Undefined, root fs is initramfs
// #define _USE_INITRD_

#if (CPU_ID == CPU_A)
MMP_ERR MMPF_SYS_StartCpuB_Ucos2(void);
MMP_ERR MMPF_SYS_StartCpuB_Linux(void);
MMP_ERR MMPF_SYS_StopCpuB(void);
#endif


#endif
#endif
