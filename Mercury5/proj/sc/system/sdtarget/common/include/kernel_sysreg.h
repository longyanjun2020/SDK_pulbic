/******************************************************************************/
/*  File    :   kernel_sysreg.h                                               */
/*----------------------------------------------------------------------------*/
/*  Scope   :   Sys_reg related definitions                                   */
/*                                                                            */
/******************************************************************************/

#ifndef __KERNEL_SYSREG_H__
#define __KERNEL_SYSREG_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "stdcomp.h"
#include "cpu_mem_map.h"


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
// SYSREG_APBCFG
#define APB0_RD_LATCH       (0x0001 << 0)  // when 1, the read pipe on the AHB2APB0 bridge is active and ine extra wait state is inserted for each read access
#define APB0_WR_BUFF        (0x0001 << 1)  // when 1, the write buffer on the AHB2APB0 is active and non-consecutive write accesses to this bridge are done without locking the CPU
#define APB1_RD_LATCH       (0x0001 << 2)  // when 1, the read pipe on the AHB2APB1 bridge is active and ine extra wait state is inserted for each read access
#define APB1_WR_BUFF        (0x0001 << 3)  // when 1, the write buffer on the AHB2APB1 is active and non-consecutive write accesses to this bridge are done without locking the CPU
#define APB2_RD_LATCH       (0x0001 << 4)  // when 1, the read pipe on the AHB2APB2 bridge is active and ine extra wait state is inserted for each read access
#define APB2_WR_BUFF        (0x0001 << 5)  // when 1, the write buffer on the AHB2APB2 is active and non-consecutive write accesses to this bridge are done without locking the CPU
#define APB3_RD_LATCH       (0x0001 << 6)  // when 1, the read pipe on the AHB2APB3 bridge is active and ine extra wait state is inserted for each read access
#define APB3_WR_BUFF        (0x0001 << 7)  // when 1, the write buffer on the AHB2APB3 is active and non-consecutive write accesses to this bridge are done without locking the CPU

// SYSREG_AHBPRIO
#define AHBPRIO_MASTER0     (0x0001 << 0)  // set the priority on the AHB multi-layer matrix for the master 0. the lowest value indicates the highest priority. only 2 different priority levels exist for all masters
#define AHBPRIO_MASTER1     (0x0001 << 1)  // set the priority on the AHB multi-layer matrix for the master 1. the lowest value indicates the highest priority. only 2 different priority levels exist for all masters
#define AHBPRIO_MASTER2     (0x0001 << 2)  // set the priority on the AHB multi-layer matrix for the master 2. the lowest value indicates the highest priority. only 2 different priority levels exist for all masters
#define AHBPRIO_MASTER3     (0x0001 << 3)  // set the priority on the AHB multi-layer matrix for the master 3. the lowest value indicates the highest priority. only 2 different priority levels exist for all masters
#define AHBPRIO_MASTER4     (0x0001 << 4)  // set the priority on the AHB multi-layer matrix for the master 4. the lowest value indicates the highest priority. only 2 different priority levels exist for all masters
#define AHBPRIO_MASTER5     (0x0001 << 5)  // set the priority on the AHB multi-layer matrix for the master 5. the lowest value indicates the highest priority. only 2 different priority levels exist for all masters

// SYSREG_AHBCFG
#define SLAVE0_RROBIN       (0x0001 << 0) // when 1 the round robin priority algorithm is active on the S0 slave port of the AHB multi-layer matrix
#define SLAVE1_RROBIN       (0x0001 << 1) // when 1 the round robin priority algorithm is active on the S1 slave port of the AHB multi-layer matrix
#define SLAVE2_RROBIN       (0x0001 << 2) // when 1 the round robin priority algorithm is active on the S2 slave port of the AHB multi-layer matrix
#define SLAVE3_RROBIN       (0x0001 << 3) // when 1 the round robin priority algorithm is active on the S3 slave port of the AHB multi-layer matrix
#define SLAVE4_RROBIN       (0x0001 << 4) // when 1 the round robin priority algorithm is active on the S4 slave port of the AHB multi-layer matrix
#define SLAVE5_RROBIN       (0x0001 << 5) // when 1 the round robin priority algorithm is active on the S5 slave port of the AHB multi-layer matrix
#define DEF_SLAVE_ERR       (0x0001 << 6) // 0: default slave never produces an eror response, 1: default slave indicates en erroneous request
#define IMI_HF              (0x0001 << 7) // when 1, the IMI is set in its high frequency mode and a wait state is inserted for each non sequenctial read access. No wia tstate is inserted for read sequential accesses

// SYSREG_MEMCFG
#define SYSREG_MEMCFG_BANK1_OFF	16
#define SYSREG_MEMCFG_BANK1_MSK	(1<<SYSREG_MEMCFG_BANK1_OFF)
#define SYSREG_MEMCFG_BANK1_TO_CPU	1
#define SYSREG_MEMCFG_BANK1_TO_GSS	0

#define SYSREG_MEMCFG_BANK2_OFF	17
#define SYSREG_MEMCFG_BANK2_MSK	(1<<SYSREG_MEMCFG_BANK2_OFF)
#define SYSREG_MEMCFG_BANK2_TO_CPU	1
#define SYSREG_MEMCFG_BANK2_TO_GSS	0

#define SYSREG_MEMCFG_BANK3_OFF	18
#define SYSREG_MEMCFG_BANK3_MSK	(1<<SYSREG_MEMCFG_BANK3_OFF)
#define SYSREG_MEMCFG_BANK3_TO_CPU	1
#define SYSREG_MEMCFG_BANK3_TO_GSS	0

#define SYSREG_MEMCFG_BANK4_OFF	19
#define SYSREG_MEMCFG_BANK4_MSK	(1<<SYSREG_MEMCFG_BANK4_OFF)
#define SYSREG_MEMCFG_BANK4_TO_CPU	1
#define SYSREG_MEMCFG_BANK4_TO_GSS	0

#define SYSREG_MEMCFG_BANK5_OFF	20
#define SYSREG_MEMCFG_BANK5_MSK	(1<<SYSREG_MEMCFG_BANK5_OFF)
#define SYSREG_MEMCFG_BANK5_TO_CPU	1
#define SYSREG_MEMCFG_BANK5_TO_DSP	0

#define SYSREG_MEMCFG_BANK6_OFF	21
#define SYSREG_MEMCFG_BANK6_MSK	(1<<SYSREG_MEMCFG_BANK6_OFF)
#define SYSREG_MEMCFG_BANK6_TO_CPU	1
#define SYSREG_MEMCFG_BANK6_TO_DSP	0

#define SYSREG_MEMCFG_BANK7_OFF	22
#define SYSREG_MEMCFG_BANK7_MSK	(1<<SYSREG_MEMCFG_BANK7_OFF)
#define SYSREG_MEMCFG_BANK7_TO_GSS	1
#define SYSREG_MEMCFG_BANK7_TO_DSP	0
#define DSP_MEMMAP          (0x0001 << 0) // when 0 program ROM mapped @0000, when 1 program RAM mapped @0000
#define CPU_MEMMAP_POS      4
#define CPU_MEMMAP_MASK     (0x0007 << CPU_MEMMAP_POS)  // allows the remapping of one of the memory spaces to the common space, i.e. at the CPU @0000_0000
                                                        // when 000: none of the memory space is remapped to the common space
                                                        // when 001: internal RAM memory space is remapped to the common space
                                                        // when 010: external MEM1 memory space is remapped to the common space
                                                        // when 011: external MEM2 memory space is remapped to the common space
                                                        // when 100: external MEM3 memory space is remapped to the common space
                                                        // when 101: external SDRAM0 memory space is remapped to the common space
                                                        // when 110: internal ROM memory space is remapped to the common space
                                                        // when 111: external MEM0 memory space is remapped to the common space
#define BOOT_CTRL_POS       8
#define BOOT_CTRL_MASK      (0x00FF << BOOT_CTRL_POS)       // represents the calues latched on the boot_ctrl# pins during the rising edge of the hardware reset


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------
/************************************************/
/* SYSREG registers definition                  */
/************************************************/
typedef struct W5SysReg_s
{
    u32 u32_apbcfg;     // 0x00
    u32 u32_ahbprio;    // 0x04
    u32 u32_ahbcfg;     // 0x08
    u32 u32_memcfg;     // 0x0C
    u32 u32_lock_key;   // 0x10
    u32 u32_design_version; // 0x14
    u32 u32_product_id;     // 0x18
    u32 u32_chip_id0;       // 0x1C
    u32 u32_chip_id1;       // 0x20
    u32 u32_chip_id2;       // 0x24
} W5SysReg_t;

#endif // __KERNEL_SYSREG_H__
