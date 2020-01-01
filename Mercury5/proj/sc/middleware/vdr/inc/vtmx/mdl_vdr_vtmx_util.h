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
///@file       mdl_vdr_mx_mov.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#ifndef __MDL_VDR_MX_UTIL_H__
#define __MDL_VDR_MX_UTIL_H__

//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------
#include <string.h>
#include <ctype.h>
#include "mdl_vdr_mx_def.h"

typedef enum VtMxMP4MemStyle
{
    MX_MP4_MEM_STYLE_REC,
    MX_MP4_MEM_STYLE_FILE,
    MX_MP4_MEM_STYLE_VT,
    MX_MP4_MEM_STYLE_VT_REC    
}VTMXMP4MEMSTYLE_e;

typedef enum VtMxMP4MemType
{
#if 1 //VT still use old sequence
	MX_MP4_MEM_POOL_V,
	MX_MP4_MEM_CACHE_DATA,
	MX_MP4_MEM_CACHE_ATOM,
	MX_MP4_MEM_POOL_A,

	MX_MP4_MEM_NUM,
#else
	MX_MP4_MEM_POOL_V,
	MX_MP4_MEM_CACHE_DATA,
	MX_MP4_MEM_CACHE_ATOM,
	MX_MP4_MEM_POOL_A,

	MX_MP4_MEM_FILE_DATA,

	MX_MP4_MEM_NUM,
#endif
} VTMXMP4MEMTYPE_e;

S32 mx_VTBlockInit(VTMXMP4MEMSTYLE_e style);
void *mx_VTBlockAlloc(VTMXMP4MEMTYPE_e type, unsigned int *size);
unsigned int mx_VTBlockSize(VTMXMP4MEMTYPE_e type);
void mx_VTBlockRelease(VTMXMP4MEMSTYLE_e style);

#endif	// __MDL_VDR_MX_UTIL_H__

