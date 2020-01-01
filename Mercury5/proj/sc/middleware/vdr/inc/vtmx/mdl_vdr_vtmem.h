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

////////////////////////////////////////////////////////////////////////////////
///@file       mdl_vdr_vtmem.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#ifndef __MDL_VDR_MEM_H__
#define __MDL_VDR_MEM_H__

//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Macro Definition
//-----------------------------------------------------------------------------
//#define USE_MALLOC

//-----------------------------------------------------------------------------
// Extern Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Data Type Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Variable Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Global Function Definition
//-----------------------------------------------------------------------------
S32 vdr_VTHeapInit(unsigned char* pstart_addr, int size);
void vdr_VTHeapRelease(void);
void *vdr_VTHeapAlloc(unsigned int size);
void vdr_VTHeapFree(void* ptr);

void *vdr_VTDynamicAlloc(unsigned int size);
void *vdr_VTDynamicFree(void *ptr);

// non cached memory
void *vdr_VTDynamicAllocUncached(unsigned int size);
void vdr_VTDynamicFreeUncached(void *ptr);
void *vdr_VTMemUncachedVA2PA(void *ptr);
void *vdr_VTMemUncachedPA2VA(void *ptr);

// cached memory
void vdr_VTMemCleanFlush(unsigned int addr, int size);
void vdr_VTMemInvalidate(unsigned int addr, int size);
#endif	// __MDL_VDR_MEM_H__

