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
* @file    hal_disp.h
* @version
* @brief   This module defines the Display driver hal layer
*
*/

#ifndef __HAL_DISP_H__
#define __HAL_DISP_H__

/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/

#include "stdcomp.h"
#include "drv_disp.h"

/*--------------------------------------------------------------------------*/
/* CONSTANT DEFINITION                                                      */
/*--------------------------------------------------------------------------*/

#define BIT(_bit_)          (1 << (_bit_))
#define BITS(_bits_, _val_) ((BIT(((1)?_bits_)+1)-BIT(((0)?_bits_))) & (_val_<<((0)?_bits_)))
#define BITMASK(_bits_)     (BIT(((1)?_bits_)+1)-BIT(((0)?_bits_)))

#define WRITE_DISP_REG(addr, type, data)  ((*(volatile type *)(addr)) = (data))
#define READ_DISP_REG(addr, type, data)   ((data) = (*(volatile type *)(addr)))



/*--------------------------------------------------------------------------*/
/* VARIABLE DEFINITION                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* LOCAL FUNCTION PROTOTYPE DECLARATION AND DEFINITION                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/

void HalDispUDelay(u32 uDelay);

void HalDispSetCLKAndPowerOn(void);
void HalDispInit(DispChipSel_e PANEL_SEL, DISPINIT_PARAS *pInitp);
void HalDispSetLCMBus(DispCmdDataType_e Flag);

void HalDispStartWriteLCD(void);
void HalDispEndWriteLCD(void);

void HalDispWriteLCMBus(DispChipSel_e ePanelSel,DispLcmMode_e eLcmMode, DispLcmBusWidth_e eLcmBusWidth, DispLcmBusFmt_e eLcmBusFmt);

u32 HalDispReadLcmReg(u8 num);
void HalDispReadLcmRegArray(u8 num, u32 *pData);

u32 HalDispWriteLcm(u32 u32Reg, u32 u32Dat);
void HalDispWriteLcmSingle(DispLCDWrite_e WriteType,u32 u32Data);

void HalDispUpdate(LayerFormat *pLayerFormat, DISP_UPDATE_TYPE type);
void HalDispReset(void);
void HalDispSetPanelType(DispPanelType_e PanelType, u32 PanelParameter);
void HalDispSpiPanel_ReadIdWithStartByte(u16 id_addr);


#endif //__HAL_DISP_H__

