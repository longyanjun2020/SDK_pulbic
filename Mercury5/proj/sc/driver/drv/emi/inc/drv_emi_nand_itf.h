////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
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
 * @file drv_emi_nand_itf.h
 * @brief NAND interface for G1
 */

#ifndef __EMI_NAND_ITF_H__
#define __EMI_NAND_ITF_H__

#if 0 // TODO: not used <-@@@

#include "vm_types.ht"
#include "drv_emi_nand.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define NAND_ECC_SIZE       10
#define NAND_SPARE_SIZE     6       /* spare_size  value: spare_size in bytes*/
#define NAND_DATA_SIZE      512   /* data_size   value: data_size in bytes */

#define NAND_OK                  1
#define NAND_BAD_PARAM          -1
#define NAND_TIMEOUT_ERROR      -2
#define NAND_NOT_OPEN_SESSION   -3

/*=============================================================*/
// Type definition
/*=============================================================*/

typedef struct emi_NandInit_s
{
    emi_NandTiming_t tTiming;
    emi_NandDivClk_e tDivClk;
    emi_NandCE_e tCE;
    emi_NandCpuCfg_e tCpuCfg;
} emi_NandInit_t;

typedef struct emi_NandOpen_s
{
    u8 nAddrCycles;
    u8 nSectPerPage;
    u8 nSectToPageShift;
    u8 nBlockToPageShift;
} emi_NandOpen_t;

/*=============================================================*/
// External function prototype
/*=============================================================*/

s32 DrvEmiNandInit(emi_NandInit_t *param);
s32 DrvEmiNandOpen(emi_NandOpen_t *param);
s32 DrvEmiNandGetStatus(void);
s32 DrvEmiNandReadId(u8 *vendor_id, u8 *product_id);
s32 DrvEmiNandReadSector(s32 session, u32 physical_sector, u8 *buffer, u16 nb_words);
s32 DrvEmiNandReadSpare(s32 session, u32 physical_sector, u8 *buffer);
s32 DrvEmiNandWriteSector(s32 session, u32 physical_sector, u8 *buffer, u16 nb_words);
s32 DrvEmiNandWriteSpare(s32 session, u32 physical_sector, u8 *buffer);
s32 DrvEmiNandEraseBlock(s32 session, u32 block_number);

#endif // TODO: not used <-@@@

#endif // __EMI_NAND_ITF_H__
