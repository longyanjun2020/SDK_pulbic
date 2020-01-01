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
* @file    srv_hopper_task.h
* @version
* @brief
*
*/

#ifndef __SRV_HOPPER_TASK_H__
#define __SRV_HOPPER_TASK_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "vm_types.ht"
#include "mmi_filemgr.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void HopperParser(void *pReceivedMsg);
void HopperSendKeyMsg(u8 nTargetKey, u8 bIsPress);
void HopperSendPressKeyMsg(u8 nTargetKey, u32 nMs);
void HopperSendTouchMsg(u32 nPosX, u32 nPosY, u8 bIsPress);
void HopperSendPressTouchMsg(u32 nPosX, u32 nPosY, u32 nMs);
void HopperInit(void);
u8 HopperGetKey(void);
void HopperSetHopperLockAP(u8 bLockAP);
void HopperSetHopperLockAPRun(void);
void HopperSetHopperRun(u8 bSetRun);
void HopperReplay(const FileMgr_WChar *pStrURL, void *pIShell);
void HopperInternalReplay(void);
void HopperReadLogData(void);
void HopperReadLogFile(const FileMgr_WChar *pStrURL, void *pIShell);
void HopperReplayEvt(u32 nEvent, u8 nIsEnd);

/*=============================================================*/
// Variable Declarations
/*=============================================================*/

#endif //__SRV_HOPPER_TASK_H__
