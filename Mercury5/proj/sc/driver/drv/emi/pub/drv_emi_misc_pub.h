////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
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
 * @file drv_emi_misc_pub.h
 * @brief EMI SC engine driver public interface
 */

#ifndef __DRV_EMI_MISC_PUB_H__
#define __DRV_EMI_MISC_PUB_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "drv_emi_pub.h"


/*=============================================================*/
// Macro definition
/*=============================================================*/
#define PROTECT_SELECT_ID_TO_WR     0
#define PROTECT_SELECT_ID_NOT_WR    1
#define PROTECT_INSIDE_RANGE        0
#define PROTECT_OUTSIDE_RANGE       1
#define PROTECT_NULL_ENTRY          0xFFFFFFFF


/*=============================================================*/
// Type definition
/*=============================================================*/

typedef struct
{
    u32 nEn;
    u32 nBlockId;       // id = 0..7
    u32 nStartAddr;     // phsical address
    u32 nEndAddr;       // phsical address
    u32 nClusterSize;
    u32 nResideu;
    u32 nPattern;
} emi_protect_pat_t;

typedef enum
{
    SYS_RO_SEG = 0x00,
    SYS_DATA_SEG,
    SYS_INHIBIT_SEG,
    SYS_MODEM_SEG,
    NULL_SEG = 0xFF
} emi_protect_seg_e;

 
/*=============================================================*/
// External function prototype
/*=============================================================*/

EmiErrorCode_e DrvEmiSetMemProtectByPatternSnoop(emi_protect_pat_t *protect_region);
EmiErrorCode_e DrvEmiStopMemProtectByPatternSnoop(u32 u32pattern);
EmiErrorCode_e DrvEmiSetMemProtectByRegionSnoop(emi_protect_seg_e etype);
EmiErrorCode_e DrvEmiStopMemProtectByRegionSnoop(emi_protect_seg_e etype);
void DrvEmiInitMemProtect(void);
void DrvEmiMemProtect4Jtag(bool bset);
void DrvEmiMemProtect4ModemArea(bool bset);

#endif // __DRV_EMI_MISC_PUB_H__
