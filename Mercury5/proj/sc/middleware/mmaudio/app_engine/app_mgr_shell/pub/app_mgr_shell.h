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
* @file    : app_mgr_shell.h
* @version :
* @author  : CA.Wang
* @brief   : dinterface define
*/

#ifndef __APP_MGR_SHELL_H__
#define __APP_MGR_SHELL_H__

/*============================================================================*/
// Include Files
/*============================================================================*/
#if defined(__RTK_OS__)
#include "vm_types.ht"
#else

#if !defined(_MSC_VER)
#include <stdint.h>
#endif

typedef int s32;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned int u32;

#endif



/*============================================================================*/
// Global function definition
/*============================================================================*/
#ifdef __cplusplus
extern "C"
{
#endif

int MDL_APPCtrTask_SetVolumePower(unsigned char bBn);
int MDL_APPCtrTask_SetVolumeGain(int s32VolumeIdx);

int MDL_APPCtrTask_SetTableAddress(void *pMessage);
int MDL_APPCtrTask_GetTableAddress(void *pMessage, unsigned char** ppu8TableAddress, unsigned int* pu32TableSize);
int MDL_APPCtrTask_SetTableConfigure(void *pMessage);
int MDL_APPCtrTask_SetTableDMARESET(void *pMessage , unsigned char* set);

int MDL_APPProcTask_Loading(unsigned int* u32APPComputLoad);
int MDL_APPProcTask_Init(int s32ChannelNum, int s32SampleRate);
int MDL_APPProcTask_Proc(int s32ChannelNum, int* s32SamplePerCh, unsigned char** pIOBuffer);
int MDL_APPProcTask_Close(void);

#ifdef __cplusplus
}
#endif

#endif // __APP_MGR_INTERFACE_H__

