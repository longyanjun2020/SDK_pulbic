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
* @file    hal_drv_util.h
* @version
* @brief   This module defines the driver utility hal layer
*
*/

#ifndef __HAL_DRV_UTIL_H__
#define __HAL_DRV_UTIL_H__

/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "stdcomp.h"
#include "sys_sys_chip.h"
#ifdef __I_SW__
#define HALUTIL_IS_BOOT_ROM2NOR() \
(((g_ptBbTop->reg_boot_status_raw & BOOT_CTRL_STRAP_MSK) == ROM_BOOT_SRC_SPI_EXTNOR_ADMUX_SPI) \
|| ((g_ptBbTop->reg_boot_status_raw & BOOT_CTRL_STRAP_MSK) == ROM_BOOT_SRC_ROM_EXTNOR_ADMUX_SPI) \
|| ((g_ptBbTop->reg_boot_status_raw & BOOT_CTRL_STRAP_MSK) == ROM_BOOT_SRC_ROM_EXTNOR_ADMUX_EMBED_SPI) \
|| ((g_ptBbTop->reg_boot_status_raw & BOOT_CTRL_STRAP_MSK) == ROM_BOOT_SRC_ROM_EXTNOR_SPANSION) \
|| ((g_ptBbTop->reg_boot_status_raw & BOOT_CTRL_STRAP_MSK) == ROM_BOOT_SRC_ROM_EXTNOR_NUMORYX) \
|| ((g_ptBbTop->reg_boot_status_raw & BOOT_CTRL_STRAP_MSK) == ROM_BOOT_SRC_ROM_EXTNOR_ADMUX) \
|| ((g_ptBbTop->reg_boot_status_raw & BOOT_CTRL_STRAP_MSK) == ROM_BOOT_SRC_EXTNOR_SPANSION))
#else
#define HALUTIL_IS_BOOT_ROM2NOR() \
    (((g_ptBbTop->reg_boot_status_raw & BOOT_CTRL_STRAP_MSK) == ROM_BOOT_EXTNOR_ADMUX) \
      || ((g_ptBbTop->reg_boot_status_raw & BOOT_CTRL_STRAP_MSK) == ROM_BOOT_EXTNOR_SWAP) \
      || ((g_ptBbTop->reg_boot_status_raw & BOOT_CTRL_STRAP_MSK) == ROM_BOOT_EXTNOR_NOSWAP))
#endif

typedef enum
{
    BOOTSRC_NONE = 0,
    BOOTSRC_ROM,
    BOOTSRC_NOR,
    BOOTSRC_SPI,
    BOOTSRC_EMBED_SPI
} BootSrc_e;

#define FUNC_ALLOC
/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DECLARATION                                            */
/*--------------------------------------------------------------------------*/
u32     HalUtilPHY2MIUAddr(u32 phyaddr);
u32     HalUtilMIU2PHYAddr(u32 miuaddr);
void    HalUtilSysVery1stInit(void);
bool    HalUtilSupportEDGE(void);
void    sysCheckDwlMode(void);
void    HalUtilIntDBB(void);
sys_ChipId_e    HalGetChipIDRev(void);
sys_ChipType_e  HalGetChipType(void);
u16 HalGetGFID(void);
u16 HalGetGFID2(void);
bool HalIsGFType(void);
BootSrc_e sys_get_bootSrc(void);
#ifndef __HAL_DRV_UTIL_C__
#include "sys_sys_premain.h"
extern const L1PTE_t _g_atPte[];
#endif
void HalPreFintISR(void);
void HalPostFintISR(void);
void HalSetSddlFlag(void);
#endif //__HAL_DRV_UTIL_H__
