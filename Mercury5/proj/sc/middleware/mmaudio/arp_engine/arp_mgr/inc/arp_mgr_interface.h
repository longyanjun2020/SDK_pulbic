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
* @file    : arp_mgr_interface.h
* @version :
* @author  : CA.Wang
* @brief   : dinterface define
*/

#ifndef __ARP_MGR_INTERFACE_H__
#define __ARP_MGR_INTERFACE_H__

/*============================================================================*/
// Include Files
/*============================================================================*/
#include "arp_confg.h"

#if !defined(_MSC_VER)
#include <stdint.h>
#endif

/*============================================================================*/
// Global function definition
/*============================================================================*/
#ifdef __cplusplus
extern "C"
{
#endif
typedef void *(* tPARPMem_alloc)(unsigned int size);
typedef void (* tPARPMem_free)(void *p);

// Parser
int ARP_MGRParser_IniIntParTab(unsigned char* u8Addr, unsigned int u32BufSz);
int ARP_MGRParser_PshClbEngID2IntParTab(unsigned char * ps8CalibTab);
int ARP_MGRParser_PshClbPar2IntParTab(unsigned short u16TargetIPID, unsigned int u32TargetModeIdx, const unsigned char * ps8CalibTab);
int ARP_MGRParser_PshExtParTab2IntParTab(unsigned char* u8Buffer, unsigned int u32SubLen, unsigned int u32InTotalDatalen);
int ARP_MGRParser_CvtIntParTable2IntParStrc(void);
int ARP_MGRParser_CloseIntParTab(void);
int _ARP_MGRMem_FreeParserBuf(void);

// Paramater
int ARP_MGRPar_Volume_SetPow(unsigned char bEn);
int ARP_MGRPar_Volume_GetPow(unsigned char * pbEn);
int ARP_MGRPar_Volume_ChangeVolume(int s32Vol);
int ARP_MGRPar_SWAGC_GetPow(unsigned char * pbEn);
int ARP_MGRPar_Main_SetPow(unsigned char bEn);
int ARP_MGRPar_Main_GetPow(unsigned char* pbEn);
int AUDPreProcMemFunc_init(tPARPMem_alloc alloc_func, tPARPMem_free freefunc );


// Main IP
int ARP_MGRMain_Init(int s32ChannelNum, int s32SampleRate);
int ARP_MGRMain_Proc(int s32ChannelNum, int* s32SamplePerCh, unsigned char* pIOBuffer);
int ARP_MGRMain_Close(void);
#ifdef __cplusplus
}
#endif

#endif // __ARP_MGR_INTERFACE_H__

