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
///@file       mdl_vdr_mx_def.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#ifndef __MDL_VDR_MX_DEF_H__
#define __MDL_VDR_MX_DEF_H__

//#define DISABLE_FOPEN
#ifdef __RTK_OS__
//#define WIN32_FOPEN
#else
#define WIN32_FOPEN
#endif
#define VFS_FILE_EN

#include <stdlib.h>
#if defined(WIN32_FOPEN)
#include <stdio.h>
#else
#include "mdl_vfs_file.ho"
#endif
#include <string.h>
#include "mm_types.h"
//#include "msmError.h"

#ifdef __RTK_OS__
#include "mdl_vdr_system.h"
#endif


//-----------------------------------------------------------------------------
//Macros Defines
//-----------------------------------------------------------------------------

#define MP4_AUDIO_TRACK_TYPE	"soun"
#define MP4_AUDIO_SEM_ITEM_NUM  400
#define MP4_VT_AUDIO_SEM_ITEM_NUM  200 //4//4 sec*50=400

#define MP4_VIDEO_TRACK_TYPE	"vide"
#define MP4_VIDEO_SEM_ITEM_NUM  100
#define MP4_VT_VIDEO_SEM_ITEM_NUM  60

#define ATOM_PAGE_SIZE 512
#define MP4DEMUX_BUFMODE
#define MP4DEMUX_BUFTIME
#define ATOM_CLUSTER_MAX_NUM    6
#define ATOM_CLUSTER_PAGE_NUM  1
#define ATOM_CLUSTER_PAGE_SIZE   (4096)

#define MP4_INVALID_TRACK_ID	((MP4TrackId)0)

#define STRINGIFY(x)    #x

//-----------------------------------------------------------------------------
// Data Type Definition
//-----------------------------------------------------------------------------

// atom type
#if defined(__GNUC__)&&defined(__i686__)
#include <stdint.h>
#else //__GNUC__ && __i686__
typedef	s8						int8_t;
typedef	short int				int16_t;
typedef	int	       				int32_t;
typedef long int		       	int64_t;
typedef	u8						uint8_t;
typedef	u16						uint16_t;
typedef	u32	       				uint32_t;
typedef unsigned long int      	uint64_t;
#endif //__GNUC__ && __i686__

#if !defined(__byte_defined__)
#define __byte_defined__
typedef u8						byte;
#endif

typedef u32	MP4TrackId;
typedef uint64_t	MP4Timestamp;
typedef uint32_t	MP4Duration;

#ifdef DISABLE_FOPEN
	typedef long int	FILE_POS;
	typedef FILE*		FILE_HANDLE;
	#define mx_fopen(name, mode)
	#define mx_fclose(stream) )
	#define mx_fdelete(name)
	#define mx_fwrite(stream, pBytes, size, count)
	#define mx_fread(stream, pBytes, size, count)
	#define mx_fseek(stream, offset, origin)
	#define mx_ftell(stream)
	#define mx_fgetattr(name, attr)
	#define mx_fsetattr(name, attr)
	#define mx_mkdir(dirname)
       #define mx_fexists(name)
       #define mx_geterrno(x)                                               (x)
	#define NULL_FILE_HANDLE NULL
	#define F_SUCC     								(0)
	#define F_FAIL  								(-1)
#elif defined(WIN32_FOPEN)
	typedef long int	FILE_POS;
	typedef FILE*		FILE_HANDLE;
	#define mx_fopen(name, mode) 					fopen(name, mode)
	#define mx_fclose(stream) 						fclose(stream)
	#define mx_fdelete(name) 						remove(name)
	#define mx_fwrite(stream, pBytes, count, size) 	fwrite(pBytes, size, count, stream)
	#define mx_fread(stream, pBytes, count, size) 	fread(pBytes, size, count, stream)
	#define mx_fseek(stream, offset, origin)		fseek(stream, offset, origin)
	#define mx_ftell(stream) 						ftell(stream)
	#define mx_frename(old_name, new_name)			rename(old_name, new_name)
	#define mx_fgetattr(name, attr)
	#define mx_fsetattr(name, attr)
	#define mx_mkdir(dirname)
	#define mx_fexists(name)
       #define mx_geterrno(x)                                               (x)
	#define NULL_FILE_HANDLE NULL
	#define F_SUCC     								(0)
	#define F_FAIL  								(-1)
#elif defined(VFS_FILE_EN)
	typedef s32		FILE_POS;
	typedef VFS_FILE*		FILE_HANDLE;
	#define mx_fopen(name, mode) 					file_fopen(name, mode)
	#define mx_fclose(stream) 						file_fclose(stream)
	#define mx_fdelete(name) 						file_unlink(name)
	#define mx_fwrite(stream, pBytes, count, size) 	file_fwrite(stream, (u8 *)pBytes, count)
	#define mx_fread(stream, pBytes, count, size) 	file_fread(stream, pBytes, count)
	#define mx_fseek(stream, offset, origin)		file_fseek(stream, offset, origin)
	#define mx_ftell(stream) 						file_ftell(stream)
	#define mx_frename(old_name, new_name)			fat_N_rename(old_name, new_name)
	#define mx_fgetattr(name, attr)					fat_N_get_file_attr(name, attr)
	#define mx_fsetattr(name, attr)					fat_N_set_file_attr(name, attr)
	#define mx_mkdir(dirname)						fat_N_make_dir(dirname)
	#define mx_fexists(name)                                             fat_N_exists(name)
       #define mx_geterrno(x)                                               (x)
	#define NULL_FILE_HANDLE						NULL
	#define F_SUCC     								(FAT_NO_ERROR)
	#define F_FAIL  								(-1)
#endif

// debug operation
// link to mdl_vdr_system.h debug macro

#define ATOMID(a) (((uint32_t) ((uint8_t *) a)[3] << 24) \
					| ((uint32_t) ((uint8_t *) a)[2] << 16) \
					| ((uint32_t) ((uint8_t *) a)[1] <<  8) \
					| ((uint32_t) ((uint8_t *) a)[0]))
#define CODEC_TYPE_4CC(d,c,b,a)      (((a)<<24)|((b)<<16)|((c)<<8)|(d))

#define MP4REC_BYTE_SWAP(r,a) \
   ((r) = (((a) & 0xff) << 24)  | (((a) & 0xff00) << 8) | \
   (((a) >> 8) & 0xff00) | (((a) >> 24) & 0xff))
#endif // __MDL_VDR_MX_DEF_H__
