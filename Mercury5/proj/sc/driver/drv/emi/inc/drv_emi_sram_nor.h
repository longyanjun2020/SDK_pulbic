////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2010 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
 * @file drv_emi_sram_nor.h
 * @brief SRAM/NOR driver private interface
 */

#ifndef __DRV_EMI_SRAM_NOR_H__
#define __DRV_EMI_SRAM_NOR_H__

#include "vm_types.ht"
#include "drv_emi.h"
#include "fms_atcmd.h"
#include "drv_emi_sram_nor_pub.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define EMI_NOR_PORT    EMI_MEM0
#define EMI_SRAM_PORT   EMI_MEM1

// The following parameters are specific to the Intel Strataflash/PSRAM combo
// They should be moved in another file
#define SETUPRD_NOR_78MHz 1
#define WAITRD_NOR_78MHZ  7
#define HOLDRD_NOR_78MHZ  0
#define BPACCT_NOR_78MHZ  2 // BCLK = HCLK / 2
#define WAITACCT_NOR_78MHZ    1 // 2 wait
#define BHOLD_NOR_78MHZ       0 // no burst hold
#define WAITPOL_NOR_78MHZ     0
#define WAITSHIFT_NOR_78MHZ   1
#define BTA_NOR_78MHZ         2 //Bus Turn Around : number of hclk cycles between a read and write access on MEM0.
#define PAGESIZE_NOR_78MHZ    2 // continuous burst
#define WAITWR_NOR_78MHZ      7

#define SETUPRD_NOR_39MHz 2
#define WAITRD_NOR_39MHZ  4
#define HOLDRD_NOR_39MHZ  0
#define BPACCT_NOR_39MHZ  1 // BCLK = HCLK / 2
#define WAITACCT_NOR_39MHZ    2 // 2 wait
#define BHOLD_NOR_39MHZ       0 // no burst hold
#define WAITPOL_NOR_39MHZ     0
#define WAITSHIFT_NOR_39MHZ   1
#define BTA_NOR_39MHZ         2 //Bus Turn Around : number of hclk cycles between a read and write access on MEM0.
#define PAGESIZE_NOR_39MHZ    3 // continuous burst

#define SETUPRD_NOR_26MHz 2
#define WAITRD_NOR_26MHZ  3
#define HOLDRD_NOR_26MHZ  0
#define BPACCT_NOR_26MHZ  1 // BCLK = HCLK / 2
#define WAITACCT_NOR_26MHZ    2 // 2 wait
#define BHOLD_NOR_26MHZ       0 // no burst hold
#define WAITPOL_NOR_26MHZ     0
#define WAITSHIFT_NOR_26MHZ   1
#define BTA_NOR_26MHZ         2 //Bus Turn Around : number of hclk cycles between a read and write access on MEM0.
#define PAGESIZE_NOR_26MHZ    3 // continuous burst

#define SETUPRD_NOR_13MHz 2
#define WAITRD_NOR_13MHZ  2
#define HOLDRD_NOR_13MHZ  0
#define BPACCT_NOR_13MHZ  1 // BCLK = HCLK / 2
#define WAITACCT_NOR_13MHZ    2 // 2 wait
#define BHOLD_NOR_13MHZ       0 // no burst hold
#define WAITPOL_NOR_13MHZ     0
#define WAITSHIFT_NOR_13MHZ   1
#define BTA_NOR_13MHZ         2 //Bus Turn Around : number of hclk cycles between a read and write access on MEM0.
#define PAGESIZE_NOR_13MHZ    3 // continuous burst

#define SETUPRD_PSRAM_78MHZ 3
#define WAITRD_PSRAM_78MHZ  9
#define HOLDRD_PSRAM_78MHZ  1
//#define SETUPWR_PSRAM_78MHZ 3
#define SETUPWR_PSRAM_78MHZ 2
#define WAITWR_PSRAM_78MHZ  9
#define HOLDWR_PSRAM_78MHZ  1
//#define BPACCT_PSRAM_78MHZ  3
#define WAITACCT_PSRAM_78MHZ    2 // 2 wait
#define BHOLD_PSRAM_78MHZ       0 // no burst hold
#define WAITPOL_PSRAM_78MHZ     0
#define WAITSHIFT_PSRAM_78MHZ   1
#define BTA_PSRAM_78MHZ         2 //Bus Turn Around : number of hclk cycles between a read and write access on MEM0.
#define RTOR_PSRAM_78MHZ        2 //number of HCLK cycles between 2 consecutive read.
#define WTOW_PSRAM_78MHZ        0 //number of HCLK cycles between 2 consecutive write.
#define PAGESIZE_PSRAM_78MHZ    3 // continuous burst
#define BPACCT_PSRAM_78MHZ      5

#define SETUPRD_PSRAM_39MHZ 3
#define WAITRD_PSRAM_39MHZ  4
#define HOLDRD_PSRAM_39MHZ  1
//#define SETUPWR_PSRAM_39MHZ 3
#define SETUPWR_PSRAM_39MHZ 0
#define WAITWR_PSRAM_39MHZ  3
#define HOLDWR_PSRAM_39MHZ  1
//#define BPACCT_PSRAM_39MHZ  3
#define WAITACCT_PSRAM_39MHZ    2 // 2 wait
#define BHOLD_PSRAM_39MHZ       0 // no burst hold
#define WAITPOL_PSRAM_39MHZ     0
#define WAITSHIFT_PSRAM_39MHZ   1
#define BTA_PSRAM_39MHZ         2 //Bus Turn Around : number of hclk cycles between a read and write access on MEM0.
#define RTOR_PSRAM_39MHZ        2 //number of HCLK cycles between 2 consecutive read.
#define WTOW_PSRAM_39MHZ        0 //number of HCLK cycles between 2 consecutive write.
#define PAGESIZE_PSRAM_39MHZ    3 // continuous burst
#define BPACCT_PSRAM_39MHZ      1

#define SETUPRD_PSRAM_26MHZ 2
#define WAITRD_PSRAM_26MHZ  4
#define HOLDRD_PSRAM_26MHZ  0
//#define SETUPWR_PSRAM_26MHZ 2
#define SETUPWR_PSRAM_26MHZ 0
#define WAITWR_PSRAM_26MHZ  3
#define HOLDWR_PSRAM_26MHZ  0
//#define BPACCT_PSRAM_26MHZ  2
#define WAITACCT_PSRAM_26MHZ    2 // 2 wait
#define BHOLD_PSRAM_26MHZ       0 // no burst hold
#define WAITPOL_PSRAM_26MHZ     0
#define WAITSHIFT_PSRAM_26MHZ   1
#define BTA_PSRAM_26MHZ         2 //Bus Turn Around : number of hclk cycles between a read and write access on MEM0.
#define RTOR_PSRAM_26MHZ        2 //number of HCLK cycles between 2 consecutive read.
#define WTOW_PSRAM_26MHZ        0 //number of HCLK cycles between 2 consecutive write.
#define PAGESIZE_PSRAM_26MHZ    3 // continuous burst
#define BPACCT_PSRAM_26MHZ      1

#define SETUPRD_PSRAM_13MHZ 2
#define WAITRD_PSRAM_13MHZ  4
#define HOLDRD_PSRAM_13MHZ  0
//#define SETUPWR_PSRAM_13MHZ 2
#define SETUPWR_PSRAM_13MHZ 0
#define WAITWR_PSRAM_13MHZ  3
#define HOLDWR_PSRAM_13MHZ  0
//#define BPACCT_PSRAM_13MHZ  2
#define WAITACCT_PSRAM_13MHZ    2 // 2 wait
#define BHOLD_PSRAM_13MHZ       0 // no burst hold
#define WAITPOL_PSRAM_13MHZ     0
#define WAITSHIFT_PSRAM_13MHZ   1
#define BTA_PSRAM_13MHZ         2 //Bus Turn Around : number of hclk cycles between a read and write access on MEM0.
#define RTOR_PSRAM_13MHZ        2 //number of HCLK cycles between 2 consecutive read.
#define WTOW_PSRAM_13MHZ        0 //number of HCLK cycles between 2 consecutive write.
#define PAGESIZE_PSRAM_13MHZ    3 // continuous burst
#define BPACCT_PSRAM_13MHZ      1


#define WEN_CYCLE_104MHZ                13
#define CEN_WRITE_CYCLE_104MHZ          15
#define CEN_READ_CYCLE_104MHZ           15
#define PAGE_ADD_CYCLE_104MHZ           15
#define TURN_AROUND_CYCLE_104MHZ        15
#define OEN_AFTER_CEN_104MHZ            2

#define WEN_CYCLE_52MHZ                 6
#define CEN_WRITE_CYCLE_52MHZ           8
#define CEN_READ_CYCLE_52MHZ            8
#define PAGE_ADD_CYCLE_52MHZ            8
#define TURN_AROUND_CYCLE_52MHZ         8
#define OEN_AFTER_CEN_52MHZ             2

#define WEN_CYCLE_26MHZ                 3
#define CEN_WRITE_CYCLE_26MHZ           4
#define CEN_READ_CYCLE_26MHZ            4
#define PAGE_ADD_CYCLE_26MHZ            4
#define TURN_AROUND_CYCLE_26MHZ         4
#define OEN_AFTER_CEN_26MHZ             2

/*=============================================================*/
// Type definition
/*=============================================================*/

typedef enum
{
    EMI_CFG_AHB_78_MHZ = 0, ///< EMI config for AHB up to 78 MHz
    EMI_CFG_AHB_52_MHZ, ///< EMI config for AHB up to 52 MHz
    EMI_CFG_AHB_26_MHZ, ///< EMI config for AHB up to 26 MHz
    EMI_CFG_AHB_13_MHZ, ///< EMI config for AHB up to 13 MHz
    EMI_CFG_NB
///< number of configurations
} emi_CgfFreq_e;

#if 0 // TODO: not used <-@@@
typedef enum
{
    EMI_SMC_130_MHZ = 0,
    EMI_SMC_104_MHZ,
    EMI_SMC_78_MHZ,
    EMI_SMC_52_MHZ,
    EMI_SMC_26_MHZ,
    EMI_SMC_NB
} emi_SmcFreq_e;

typedef struct
{
    u32 nFineInBound; //0~7, unit: 0.4 ns
    u32 nFineOutBound; //0~7, unit: 0.4 ns
    u32 nSmcCLK; //0: 26M, 1:52M, 2:78M, 3:104M, 4:130M, 5:156M
    u32 nCoarseInBound; //0~3, unit: 3.2 ns
    u32 nCoarseOutBound; //0~3, unit: 3.2 ns
    u32 nDmcCLK; //0: 26M, 1:52M, 2:78M, 3:104M, 4:130M, 5:156M
} emi_Config_t;

typedef struct
{
    u32 nOM; //A15
    u32 nIL; //A14
    u32 nLC; //A13-A11
    u32 nWaitPol; //A10
    u32 nWaitConfig; //A8
    u32 nDrivStrength; //A5-A4
    u32 nBurstWrap; //A3
    u32 nBLength; //A2-A0
} sys_PsramCtrlReg_t;

typedef struct
{
    u32 B2WV;           //0
    u32 PreArbiterWV;   //8
    u32 M3WV;           //0
    u32 TestWV;         //8
    u32 ArbIgnore;      //0
    u32 ArbHold;        //4
} emi_ArbiterReg_t;

#define WEN_CYCLE_104MHZ				13
#define CEN_WRITE_CYCLE_104MHZ			15
#define CEN_READ_CYCLE_104MHZ			15
#define PAGE_ADD_CYCLE_104MHZ			15
#define TURN_AROUND_CYCLE_104MHZ		15
#define OEN_AFTER_CEN_104MHZ			2

#define WEN_CYCLE_52MHZ					6
#define CEN_WRITE_CYCLE_52MHZ			8
#define CEN_READ_CYCLE_52MHZ			8
#define PAGE_ADD_CYCLE_52MHZ			8
#define TURN_AROUND_CYCLE_52MHZ			8
#define OEN_AFTER_CEN_52MHZ				2

#define WEN_CYCLE_26MHZ					3
#define CEN_WRITE_CYCLE_26MHZ			4
#define CEN_READ_CYCLE_26MHZ			4
#define PAGE_ADD_CYCLE_26MHZ			4
#define TURN_AROUND_CYCLE_26MHZ			4
#define OEN_AFTER_CEN_26MHZ				2
#endif // TODO: not used <-@@@

/*=============================================================*/
// External function prototype
/*=============================================================*/

#endif //__DRV_EMI_SRAM_NOR_H__
