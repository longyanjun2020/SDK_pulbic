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

/*
 **  Important : This software is protected by Copyright and the information
 **              contained herein is confidential. Distribution, reproduction
 **              as well as exploitation and transmission of its contents is
 **              not allowed except if expressly permitted. Infringments
 **              result in damage claims.
 **              Copyright VMTS S.A. (c) 2001
 */
/****************************************************************************/
/*  File    : emi_nand_drv.h                                                */
/*--------------------------------------------------------------------------*/
/*  Scope   : NAND driver for V2751                                         */
/*                                                                          */
/*  Historical :                                                            */
/*--------------------------------------------------------------------------*/
/*   Date   | Author | Err  |  Modification                                 */
/*----------+--------+------+-----------------------------------------------*/
/* 06.06.05 |   NRO  |      |  Creation                                     */
/*----------+--------+------+-----------------------------------------------*/
/****************************************************************************/

#ifndef __EMI_NAND_DRV_H__
#define __EMI_NAND_DRV_H__

#if 0 // TODO: not used <-@@@

#include "vm_types.ht"

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define EMI_NAND_CMD1_EN    0x1
#define EMI_NAND_CMD2_EN    0x2
#define EMI_NAND_CMD3_EN    0x4

#define NAND_PAGE_SIZE 528
#define NAND_ECC_SIZE 10

/*=============================================================*/
// Type definition
/*=============================================================*/

typedef struct emi_NandTiming_s
{
    u32 TWP :4; // TWP : Min time for write = 0. From 1 to 16 HCLK cycles
    u32 TWH :3; // TWH: Min time for write = 1. From 1 to 8 HCLK cycles
    u32 TRP :4; // TRP: Min time for read = 0. From 1 to 16 HCLK cycles
    u32 TREH :3; // TREH: Min time for read = 1. From 1 to 8 HCLK cycles
    u32 BTA :3; // BTA: Bus Turnaround. Min time from   a read access to  a write access. From 1 to 8 HCLK cycles
    u32 TWSETUP :1; // TWSETUP: Min time  between CLE, ALE,  /CE change to /WE negative edge. From 1 to 2 HCLK cycles
    u32 TRSETUP :2; // TRSETUP: Min time between /CE negative edge and /RE negative edge. From 1 to 4 HCLK cycles
    u32 TBUSY :5; // TBUSY:  Max time between /WE rising  edge and busy falling edge or Min time between busy rising edge and /RE falling edge. From 1 to 32 HCLK cycles
    u32 TWRH :4; // TWHR: Min time between /WE rising edge and /RE falling edge. From 1 to 16 HCLK cycles
    u32 TCEH :3; // TCEH: Min time for /CE = 1. From 1 to 8 HCLK cycles
} emi_NandTiming_t;

typedef enum
{
    NAND_READ,
    NAND_WRITE
} emi_NandRW_e;

typedef enum
{
    NAND_16BITS,
    NAND_8BITS
} emi_NandItfWidth_e;

typedef enum
{
    NAND_HCLK_NO_DIV = 0,
    NAND_HCLK_DIV_2 = 1,
    NAND_HCLK_DIV_4 = 2
} emi_NandDivClk_e;

typedef enum
{
    NAND_CE0 = 0,
    NAND_CE1 = 1,
} emi_NandCE_e;

typedef enum
{
    NAND_CPU = 0,
    NAND_BOOT = 1,
} emi_NandCpuCfg_e;

/*=============================================================*/
// External function prototype
/*=============================================================*/

void DrvEmiNandConfigureTiming(emi_NandTiming_t *timing);
void DrvEmiNandSetCommands(const u8 *cmd, u8 mask);
void DrvEmiNandSetAddress(const u8 *addr, u8 nb_addr);
void DrvEmiNandSetNbData(u16 nb_data);
void DrvEmiNandCtrlECC(bool enable);
void DrvEmiNandWaitBusy(bool enable);
void DrvEmiNandDataOperation(bool enable);
void DrvEmiNandRWOperation(emi_NandRW_e rw);
bool DrvEmiNandIsBusy(void);
bool DrvEmiNandIsOpComplete(void);
bool DrvEmiNandDecodeError(void);
u8 DrvEmiNandGetNbDecErrors(void);
bool DrvEmiNandDecodeFail(void);
bool DrvEmiNandWriteFault(void);
void DrvEmiNandStartPulse(bool enable);
void DrvEmiNandResetPulse(bool enable);
void DrvEmiNandControlItf(emi_NandItfWidth_e width);
void DrvEmiNandSetNbColAddr(u8 nbCol);
void DrvEmiNandWriteProtect(bool enable);
void DrvEmiNandSetHighestProtectedRow(u32 row);
void DrvEmiNandSetDecClkDivider(emi_NandDivClk_e divider);
void DrvEmiNandSelectCE(emi_NandCE_e ce_type);
void DrvEmiNandSetCpuConfig(emi_NandCpuCfg_e cfg);
void DrvEmiNandSetCEIntercept(bool enable);
u32 DrvEmiNandReadData(u8 *buffer, u16 offset, u16 size);
u32 DrvEmiNandWriteData(u8 *buffer, u16 offset, u16 size);

#endif // TODO: not used <-@@@

#endif //__EMI_NAND_DRV_H__
