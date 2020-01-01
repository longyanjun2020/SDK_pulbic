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
* @file    : arp_mgr_shell.h
* @version :
* @author  : CA.Wang
* @brief   : interface define
*/

#ifndef __ARP_MGR_SHELL_H__
#define __ARP_MGR_SHELL_H__

/*============================================================================*/
// Include Files
/*============================================================================*/
#include "vm_types.ht"

/*============================================================================*/
// Global function definition
/*============================================================================*/
#ifdef __cplusplus
extern "C"
{
#endif

s32 MDL_ARPCtrTask_SetVolumePower(u8 bBn);
s32 MDL_ARPCtrTask_SetVolumeGain(s32 s32VolumeIdx);
s32 MDL_ARPCtrTask_SetTableAddress(void *pMessage);
s32 MDL_ARPCtrTask_GetTableAddress(void *pMessage, u8** ppu8TableAddress, u32* pu32TableSize);
s32 MDL_APPProcTask_Loading(u32* u32ARPComputLoad);
s32 MDL_ARPCtrTask_SetTableConfigure(void *pMessage);
s32 MDL_ARPProcTask_Init(s32 s32ChannelNum, s32 s32SampleRate);
s32 MDL_ARPProcTask_Proc(s32 s32ChannelNum, s32* s32SamplePerCh, u8* pIOBuffer);
s32 MDL_ARPProcTask_Close(void);

#ifdef __cplusplus
}
#endif
#endif
