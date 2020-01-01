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

#define V_POOL_CHUNK_SIZE (4*1024)
#define A_POOL_CHUNK_SIZE 32
#define A_AMR_POOL_CHUNK_SIZE 32
#define A_MP3_POOL_CHUNK_SIZE 216
#define A_PCM_POOL_CHUNK_SIZE 512
// pool requirement
typedef enum
{
    POOL_MEMORYREQUIREMENT_HIGH  = 0,                      ///< memory requirement high
    POOL_MEMORYREQUIREMENT_MEDIUM,                         ///< memory requirement medium
    POOL_MEMORYREQUIREMENT_LOW,                            ///< memory requirement low
} MXMP4POOLMEMREQ_e;


#ifndef MIN
#define MIN(a,b) (a<b? a: b)
#endif

typedef enum MxMP4MemStyle
{
    MX_MP4_MEM_STYLE_REC,
    MX_MP4_MEM_STYLE_FILE,
    MX_MP4_MEM_STYLE_VT,
    MX_MP4_MEM_STYLE_VT_REC,
}MXMP4MEMSTYLE_e;

typedef enum MxMP4MemType
{
	MX_MP4_MEM_CACHE_DATA,
	MX_MP4_MEM_CACHE_ATOM,
	MX_MP4_MEM_POOL_A,
	MX_MP4_MEM_POOL_V,
	MX_MP4_MEM_POOL_V_0 = MX_MP4_MEM_POOL_V,
	MX_MP4_MEM_POOL_V_1,
	MX_MP4_MEM_POOL_V_2,
	MX_MP4_MEM_POOL_V_3,
	MX_MP4_MEM_POOL_V_4,
	MX_MP4_MEM_POOL_V_5,
	MX_MP4_MEM_POOL_V_6,
	MX_MP4_MEM_POOL_V_7,

	MX_MP4_MEM_FILE_DATA,

	MX_MP4_MEM_NUM,

    MX_MP4_MEM_REC_START = MX_MP4_MEM_CACHE_DATA,
    MX_MP4_MEM_REC_END = MX_MP4_MEM_POOL_A,
} MXMP4MEMTYPE_e;

S32 mx_BlockInit(MXMP4MEMSTYLE_e style, unsigned int v_bitrate, unsigned int a_bitrate);
void *mx_BlockAlloc(MXMP4MEMTYPE_e type, unsigned int *size);
unsigned int mx_BlockSize(MXMP4MEMTYPE_e type);
void mx_BlockRelease(MXMP4MEMSTYLE_e style);
void *mx_alloc(unsigned int size);
void mx_free(void **p_ptr);

void mx_PoolRequirementGet(u32 *pu32HighPool, u32 *pu32LowPool);
void mx_PoolRequirementSet(MXMP4POOLMEMREQ_e u32PoolReqMode);
void mx_VideoResCapabilityGet(u16 *pnMaxWidth, u16 *pnMaxHeight, u16 *pnMinWidth, u16 *pnMinHeight);
MP4Timestamp MP4MXGetAbsTimestamp(void);
const char* MP4MXNameAfterFirst(const char *s);
U8 MP4MXNameFirstMatches(const char* s1, const char* s2);
int mx_strcasecmp(const char *s1, const char *s2);
#endif	// __MDL_VDR_MX_UTIL_H__

