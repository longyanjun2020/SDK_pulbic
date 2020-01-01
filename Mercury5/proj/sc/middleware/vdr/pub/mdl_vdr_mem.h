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
///@file       mdl_vdr_mem.h
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
signed long vdr_HeapInit(unsigned char* pstart_addr, int size);
void vdr_HeapRelease(void);
void *vdr_HeapAlloc(unsigned int size);
void vdr_HeapFree(void **p_ptr);
int vdr_HeapGetMaxSize(void);

void *vdr_DynamicAlloc(unsigned int size);
void *vdr_DynamicFree(void **p_ptr);
void *vdr_DynamicAllocIM(unsigned int size);
void vdr_DynamicFreeIM(void **p_ptr);

// non cached memory
void *vdr_DynamicAllocUncached(unsigned int size);
void vdr_DynamicFreeUncached(void **p_ptr);
void *vdr_MemUncachedVA2PA(void *ptr);
void *vdr_MemUncachedPA2VA(void *ptr);

// cached memory
void vdr_MemCleanFlush(unsigned int addr, int size);
void vdr_MemInvalidate(unsigned int addr, int size);
#endif	// __MDL_VDR_MEM_H__

