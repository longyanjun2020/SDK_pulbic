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
* @file    srv_mmi_hopper.h
* @version
* @brief
*
*/

#ifndef __SRV_MMI_HOPPER_H__
#define __SRV_MMI_HOPPER_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "vm_types.ht"
#include "mmi_mae_interface_def.h"
#include "srv_filemgr_fstream.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

#define INPUT_LOG_FILE_NAME	L"fs:/CARD/.system/log_input.txt"

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/

void HopperLockAPNotifyIf(IBase *pRecipient, struct vm_msg *pMessage);
void HopperLockAPNotifyNotify(u8 bSetLock);
void mmi_set_Record(u8 bSetRecord);
void mmi_save_TouchPressed(u32 nPosX, u32 nPosY, u8 bIsPressed, IBase *pIShell);
void mmi_save_KeyPressed(u8 nKey, u8 bIsPressed, IBase *pIShell);
void mmi_save_WriteFileCallback(void *pThis, FileMgrFileCallback_t *pInfo);
MAE_Ret mmi_query_HopperRunning(void);

#endif //__SRV_MMI_HOPPER_H__
