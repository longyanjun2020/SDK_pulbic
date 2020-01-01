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
* @file    drv_disp.h
* @version
* @brief   This module defines the public interface for Display driver
*
*/

#ifndef __DRV_DISP_H__
#define __DRV_DISP_H__

#include "vm_types.ht"
#include "drv_disp_types.h"


typedef enum
{
    DISP_RELEASE_BUS = 0,
    DISP_OWN_BUS,
} DISP_BUS_PHASE;

/************************************************/
void DrvDispSetPanelType(DispPanelType_e PanelType, u32 PanelParameters);


void DrvDispSetBusFmt(DispChipSel_e PANEL_SEL, DISPINIT_PARAS *pInitp);
void DrvDispInit(DispChipSel_e PANEL_SEL,DISPINIT_PARAS *pInitp);

bool DrvDispUpdatePolling(void);
void DrvDispReadLCMRegArray(u32 Reg, u8 times, u32 *pData);
u32  DrvDispReadLCMReg(u32 Reg, u8 times);
//void DrvDispEnBGClr(u8 *Enables);
void DrvDispDeGammaSet(u8 nCtrl, u16 *pDeGammaTable);
void DrvDispGammaEnable(u8 nCtrl, u8 *pu8Adr);
void DrvDispCSCSet(u16 *pCSCTable);

void DrvDispWriteLcmData(u32 u32Data);
void DrvDispWriteLcmCmd(u32 u32Data);
void DrvDispWriteLcmSet(u32 u32Reg,u32 u32Dat);

void DrvDispInitial(void);
void DrvDispRestart(void);
void DrvDispSWInit(void);


void DrvDispPowerOn(void);
void DrvDispPowerOff(void);

void DrvDispUDelay(u32 DelayUS);
void DrvDispMDelay(u32 DelayMs);

void DrvDispLcokBus(void);
void DrvDispReleaseBus(void);


void DrvDispSetLCMBusInt(DispCmdDataType_e Flag);

u32 DrvDispSetCLK(DISP_CLOCK_SEL clkSel);

void DrvDispUpdate(LayerFormat *pLayerFormat, DISP_UPDATE_TYPE type);

DISPFUN_ERRCODE DrvDispStartWriteLCD(void);
DISPFUN_ERRCODE DrvDispEndWriteLCD(void);
void DrvDispSetDispTable(void);
void DrvDispReset(void);
void DrvDispChangeCmdPhase(DISP_BUS_PHASE BusCtrl);

void DrvDispChangePanelCtrl(DispChipSel_e PANEL_SEL);
bool DrvDispNeed8MBoundaryPatch(void);
void DrvDispClkSet(u32 ClkSpeed);

void DrvDispSpiPanel_ReadIdWithStartByte(u16 id_addr);
void DrvDispSpiPanel_SetStartByte(u16 val);

void DrvDispTimingAdjust(DispAdjustPinSel_e AdjustPin,DispTimingDelay_e Level);

DISPSCL_MODE_e DrvDispSCLMode(void);

#endif //__DRV_DISP_H__
