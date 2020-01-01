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
* @file    drv_power_api.h
* @version
* @brief   This module defines the power supply control driver
*
*/

#ifndef __DRV_POWER_API_H__
#define __DRV_POWER_API_H__

/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "vm_types.ht"
#include "drv_power_forward.h"

/*--------------------------------------------------------------------------*/
/* EXTERN DEFINITION                                                        */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* MACRO DEFINITION                                                         */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* DATA TYPE DEFINITION                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* VARIABLE DEFINITION                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/
s32 DrvPowerG3d(PowerState_e eActState, u32 pedding1, PowerState_e eStdbyState, u32 pedding2);
s32 DrvPowerDisp(PowerState_e eActState, u32 pedding1, PowerState_e eStdbyState, u32 pedding2);
s32 DrvPowerAudioDigital(PowerState_e eActState, u32 pedding1, PowerState_e eStdbyState, u32 pedding2);
s32 DrvPowerRfDigital(PowerState_e eActState, u32 pedding1, PowerState_e eStdbyState, u32 pedding2);
s32 DrvPowerEmi(PowerState_e eActState, u32 pedding1, PowerState_e eStdbyState, u32 pedding2);
s32 DrvPowerMmp(PowerState_e eActState, u32 pedding1, PowerState_e eStdbyState, u32 pedding2);
s32 DrvPowerMmpIo(PowerState_e eActState, VioVolt_e eActVolt, PowerState_e eStdbyState, VioVolt_e eStdbyVolt);
s32 DrvPowerDbbIo(PowerState_e eActState, VioVolt_e eActVolt, PowerState_e eStdbyState, VioVolt_e eStdbyVolt);
s32 DrvPowerDigrf(PowerState_e eActState, VdigrfVolt_e eActVolt, PowerState_e eStdbyState, VdigrfVolt_e eStdbyVolt);
s32 DrvPowerSim(PowerState_e eActState, VsimVolt_e eActVolt, PowerState_e eStdbyState, VsimVolt_e eStdbyVolt);
s32 DrvPowerSimTwo(PowerState_e eActState, VsimVolt_e eActVolt, PowerState_e eStdbyState, VsimVolt_e eStdbyVolt);
s32 DrvPowerDig(PowerState_e eActState, VdigVolt_e eActVolt, PowerState_e eStdbyState, VdigVolt_e eStdbyVolt);
s32 DrvPowerPeripheralFour(PowerState_e eActState, VperVolt_e eActVolt, PowerState_e eStdbyState, VperVolt_e eStdbyVolt);
s32 DrvPowerPeripheralThree(PowerState_e eActState, Vper3Volt_e eActVolt, PowerState_e eStdbyState, Vper3Volt_e eStdbyVolt);
s32 DrvPowerPeripheralTwo(PowerState_e eActState, VperVolt_e eActVolt, PowerState_e eStdbyState, VperVolt_e eStdbyVolt);
s32 DrvPowerPeripheralOne(PowerState_e eActState, VperVolt_e eActVolt, PowerState_e eStdbyState, VperVolt_e eStdbyVolt);
s32 DrvPowerTcxo(PowerState_e eActState, VaVolt_e eActVolt, PowerState_e eStdbyState, VaVolt_e eStdbyVolt);
s32 DrvPowerAbbAud(PowerState_e eActState, VabbaudVolt_e eActVolt, PowerState_e eStdbyState, VabbaudVolt_e eStdbyVolt);
s32 DrvPowerAux(PowerState_e eActState, VauxVolt_e eActVolt, PowerState_e eStdbyState, VauxVolt_e eStdbyVolt);
s32 DrvPowerGetEfuseValue(u8 *efuse);
s32 DrvPowerSetEfuseValue(u8 efuse);

void DrvPowerSysInit(void);
void DrvPowerOff(void);
void DrvPowerOnIrqOpen(void);
void DrvPowerDownTemp(void);

/* MST change -- begin */
void DrvPowerCheckPowerOnCause(void);
PowerOnCause_e DrvPowerReadPowerOnCause(void);
/* MST change -- end */

// Register Access Function
void DrvPmuCLKCtrl1(bool bFromBBMclk);
void DrvPmuLowVBATTurnOff(bool Flag);
void DrvPmCpuRomPD(void);


#endif //__DRV_POWER_API_H__

