////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2011 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MDL_CAMERA_IP_PUB_H_
#define	_MDL_CAMERA_IP_PUB_H_

/**
 *	@file
 *	@brief public video stabilizer interface
 */
#if _X86_
	#include <assert.h>
	#include <math.h>
	#include <stdint.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <sys/stat.h>
	#include <time.h>
	#include <unistd.h>
	typedef signed long		s32;
	typedef signed short	s16;
	typedef signed char		s8;
	typedef unsigned long	u32;
	typedef unsigned short	u16;
	typedef unsigned char   u8;

	#define	FILE_PREFIX		""

	#define	min(a,b)		((a)>(b) ? (b) : (a))
	#define	max(a,b)		((a)>(b) ? (a) : (b))
	#define	VS_ERROR		printf("IP ERROR -- %d: %s()\n", __LINE__, __FUNCTION__)
	#define	D				printf("IP DEBUG -- %d: %s()\n", __LINE__, __FUNCTION__)

#else
	#include <math.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "vm_types.ht"
	#include "sys_MsWrapper_cus_os_mem.h"
	#include "sys_vm_dbg.ho"
	#include "drv_timer_api.h"
	#include "mdl_vfs_file.ho"
	#include "mdl_vfs_fat.ho"
	#include "bsp.h"
	//#define	FILE_PREFIX		"/PHON/"
	#define	FILE_PREFIX		"/CARD/"
	//#define	FILE_PREFIX		"/SD_2/"
	#define	M_PI			3.14159265
	#define	CLOCKS_PER_SEC	1000
	#define	malloc			MsGetHeapMemory
	#define	free			MsReleaseHeapMemory
	#define abs(a)			((a) > 0 ? (a) : -(a))
	#define	min(a,b)		((a)>(b) ? (b) : (a))
	#define	max(a,b)		((a)>(b) ? (a) : (b))
	#define MDL_IP_TRC_NORM	0x1c18	//_CUS1 | LEVEL_28
	#define	printf(...)		vm_dbgTrace(MDL_IP_TRC_NORM, __VA_ARGS__)
	#define	VS_ERROR		vm_dbgTrace(MDL_IP_TRC_NORM, "IP ERROR -- %d: %s()\n", __LINE__, __FUNCTION__)
	#define	D				vm_dbgTrace(MDL_IP_TRC_NORM, "IP DEBUG -- %d: %s()\n", __LINE__, __FUNCTION__)
	#define	assert(a)		if(!(a)) VS_ERROR	//assert() will make compile error
	#define	clock(...)		DrvTimerStdaTimerGetTick()
	#define	FILE			VFS_FILE
	#define	fopen			file_fopen_ascii
	#define	fwrite(b,w,h,f)	file_fwrite((f),(u8*)(b),(w)*(h))		//s32 file_fwrite(VFS_FILE *fp, u8 *buffer, u32 nb_bytes)
	#define	fread(b,w,h,f)	file_fread((f),(u8*)(b),(w)*(h))			//s32 file_fread(VFS_FILE *fp, u8 *buffer, u32 nb_bytes)
	#define	fclose			file_fclose
	#define	ftell			file_ftell
	#define	fseek			file_fseek	//(VFS_FILE * const pFile, const s32 offset, const s32 position)
	#define	exit(...)		VS_ERROR
	#define	abort(...)		VS_ERROR
	VFS_FILE*file_fopen_ascii(char *name, char *mode);
#endif


typedef struct {
	s32 nX;
	s32 nY;
	s32 nW;
	s32 nH;
} Region_t;


typedef struct {
	u32		nMagic;			//!<nMagic number for chacking log file
	u32		nVersion;		//!<formation nVersion, current is 1

	//Y
	u32		nHeight;		//!<Number of pixels per Image_t line.
	u32		nWidth;			//!<Number of Image_t lines.
	u8*		pBuffer;		//!<Address of the raw data pBuffer.
	u32		nSize;			//!<nSize of pBuffer

	//YUV
	u32		bIsYUV;
	u8*		pUV;			//!<Address of the pUV pBuffer.

	s32		nExposure;		//!<nExposure with which frame was taken.
	s32		nIso;			//!<nIso with which frame was taken.
} Image_t;


#endif

Image_t*	Image_Alloc(s32 nWidth, s32 nHeight);
void		Image_Free(Image_t *pImage);
u32			Image_ExportAsPGM(Image_t *pImage, char *pOutfile);
Image_t*	Image_LoadPGM(Image_t* pImage, char* pPgmfile);

