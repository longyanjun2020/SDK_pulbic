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
* @file    : arp_datatype.h
* @version :
* @author  : CA.Wang
* @brief   : data type define
*/

#ifndef __ARP_DATATYPE_H__
#define __ARP_DATATYPE_H__

/*============================================================================*/
// Include Files
/*============================================================================*/
#include "arp_confg.h"

/*============================================================================*/
// Data Type Define by DSP
/*============================================================================*/
#if defined(ARP_ON_B2M3_MIPS_SYSTEM)

#include "shellcfg.h"

#elif defined(ARP_ON_B2M3_MIPS_SIMULATOR)

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define _CUSARP 0

typedef unsigned char      tU8;
typedef signed char        tS8;
typedef unsigned short     tU16;
typedef short              tS16;
typedef unsigned int       tU32;
typedef int                tS32;
typedef unsigned long long tU64;
typedef long long          tS64;
typedef int                tBOOL;
#define TRUE  1
#define FALSE 0

#elif defined(ARP_ON_B3_ARM9_SYSTEM)

#include "vm_types.ht"
#include "sys_vm_dbg.ho"

#define _CUSARP _CUS2 | LEVEL_7

typedef u8   tU8;
typedef s8   tS8;
typedef u16  tU16;
typedef s16  tS16;
typedef u32  tU32;
typedef s32  tS32;
typedef u64  tU64;
typedef s64  tS64;
typedef s32 tBOOL;

#elif defined(ARP_ON_B3_ARM9_SIMULATOR)

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define _CUSARP 0

typedef unsigned char      tU8;
typedef signed char        tS8;
typedef unsigned short     tU16;
typedef short              tS16;
typedef unsigned int       tU32;
typedef int                tS32;
typedef unsigned long long tU64;
typedef long long          tS64;
typedef int                tBOOL;
#define TRUE  1
#define FALSE 0

#elif defined(ARP_ON_G1_AEON_SYSTEM)

#include "vm_types.ht"
#include "sys_vm_dbg.ho"

#define _CUSARP _CUS2 | LEVEL_7

typedef u8   tU8;
typedef s8   tS8;
typedef u16  tU16;
typedef s16  tS16;
typedef u32  tU32;
typedef s32  tS32;
typedef u64  tU64;
typedef s64  tS64;
typedef s32  tBOOL;

#elif defined(ARP_ON_G1_AEON_SIMULATOR)

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define _CUSARP 0

typedef unsigned char      tU8;
typedef signed char        tS8;
typedef unsigned short     tU16;
typedef short              tS16;
typedef unsigned int       tU32;
typedef int                tS32;
typedef unsigned long long tU64;
typedef long long          tS64;
typedef int                tBOOL;
#define TRUE  1
#define FALSE 0

#elif defined(ARP_ON_MSC)

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define _CUSARP 0

typedef unsigned char     tU8;
typedef signed char       tS8;
typedef unsigned short    tU16;
typedef short             tS16;
typedef unsigned int      tU32;
typedef int               tS32;
typedef __int64           tS64;
typedef unsigned __int64  tU64;
typedef int               tBOOL;
#define TRUE  1
#define FALSE 0

#else

#error Invalid Audio Post-Processer(ARP) Data Type Option!!!

#endif

/*============================================================================*/
// 16/32 Bits Instrunction by DSP
/*============================================================================*/

#if defined(ARP_ON_B2M3_MIPS_SYSTEM)

#define ARP_ATTR_16BITS    __attribute__((mips16))
#define ARP_ATTR_32BITS    __attribute__((nomips16))

#elif defined (ARP_ON_B2M3_MIPS_SIMULATOR)

#define ARP_ATTR_16BITS    __attribute__((mips16))
#define ARP_ATTR_32BITS    __attribute__((nomips16))

#elif defined(ARP_ON_B3_ARM9_SYSTEM)

#define ARP_ATTR_16BITS
#define ARP_ATTR_32BITS

#elif defined(ARP_ON_B3_ARM9_SIMULATOR)

#define ARP_ATTR_16BITS
#define ARP_ATTR_32BITS

#elif defined(ARP_ON_G1_AEON_SYSTEM)

#define ARP_ATTR_16BITS
#define ARP_ATTR_32BITS

#elif defined(ARP_ON_G1_AEON_SIMULATOR)

#define ARP_ATTR_16BITS
#define ARP_ATTR_32BITS

#elif defined(ARP_ON_MSC)

#define ARP_ATTR_16BITS
#define ARP_ATTR_32BITS

#else

#error Invalid Audio Pre-Processer(ARP) Function Attribute!!!

#endif

/*============================================================================*/
// Printf Define
/*============================================================================*/
#if !defined(ARP_ON_B3_ARM9_SYSTEM) && !defined(ARP_ON_G1_AEON_SYSTEM) && !defined(LOG_INFO)
#define LOG_INFO

//#define ARP_ENABLE_VM_DBGTRACE
//#define ARP_ENABLE_VM_DBGERROR

#if defined(ARP_ON_MSC)
#pragma warning(disable:4996)  
#endif

static __inline void vm_dbgTrace(int level, const char *format, ...)
{
#ifdef ARP_ENABLE_VM_DBGTRACE

#if 0
    va_list args;
    int     len;
    char    *buffer;

    // retrieve the variable arguments
    va_start( args, format );

    len = _vscprintf( format, args ) // _vscprintf doesn't count
                                + 1; // terminating '\0'

    buffer = (char*)malloc( len * sizeof(char) );

    vsprintf_s( buffer, len, format, args ); // C4996
    // Note: vsprintf is deprecated; consider using vsprintf_s instead
    puts( buffer );

    free( buffer );
#else
    va_list args;     
    char buffer[1000];

    va_start(args, format);    
    vsnprintf(buffer, sizeof(buffer)-1, format, args);  // C4996
    va_end(args);

    printf("%s\n", buffer);
#endif

#endif
}

static __inline void vm_dbgError(int level, const char *format, ...)
{
#ifdef ARP_ENABLE_VM_DBGERROR

#if 0
    va_list args;
    int     len;
    char    *buffer;

    // retrieve the variable arguments
    va_start( args, format );

    len = _vscprintf( format, args ) // _vscprintf doesn't count
                                + 1; // terminating '\0'

    buffer = (char*)malloc( len * sizeof(char) );

    vsprintf_s( buffer, len, format, args ); // C4996
    // Note: vsprintf is deprecated; consider using vsprintf_s instead
    puts( buffer );

    free( buffer );
#else
    va_list args;    
    char buffer[1000];

    va_start(args, format);    
    vsnprintf(buffer, sizeof(buffer)-1, format, args);  // C4996
    va_end(args);

    printf("%s\n", buffer);
#endif

#endif
}
#endif


/*============================================================================*/
//                             Data MIN/MAX
/*============================================================================*/
#define ARP_MAX_S16 ((tS16)32767)
#define ARP_MIN_S16 ((tS16)-32768)

#define ARP_MAX_U16 ((tU16)65535)
#define ARP_MIN_U16 ((tU16)0)

#define ARP_MAX_S32 ((tS32)2147483647)
#define ARP_MIN_S32 ((tS32)-2147483648)

#define ARP_MAX_U32 ((tS32)4294967296)
#define ARP_MIN_U32 ((tS32)0)

/*============================================================================*/
//                              Supported Fs
/*============================================================================*/
#define ARP_FS_48K 48000 // Hz
#define ARP_FS_44K 44100 // Hz
#define ARP_FS_32K 32000 // Hz
#define ARP_FS_24K 24000 // Hz
#define ARP_FS_22K 22050 // Hz
#define ARP_FS_16K 16000 // Hz
#define ARP_FS_12K 12000 // Hz
#define ARP_FS_11K 11025 // Hz
#define ARP_FS_8K  8000  // Hz
#define ARP_FS_NUM 9

/*============================================================================*/
//                              Frame Size
/*============================================================================*/
#define ARP_SUBFRAME_SIZE (256)
#define ARP_SUBFRAME_EXT_SIZE  (ARP_SUBFRAME_NORM_SIZE >> 1)
#define ARP_SUBFRAME_MAX_SIZE  (ARP_SUBFRAME_NORM_SIZE + ARP_SUBFRAME_EXT_SIZE)

/*============================================================================*/
//                       Calibration Table Format
/*============================================================================*/
typedef enum {
    ARP_TABLE_FORMAT_VERSION_V000 = 0,
    ARP_TABLE_FORMAT_VERSION_V001 = 1,
    ARP_TABLE_FORMAT_VERSION_NUM  = 2,
}ARP_TABLE_FORMAT_VERSION_e;

#define ARP_TABLE_FORMAT_CURRENT_VERSION ARP_TABLE_FORMAT_VERSION_V001
#define ARP_TABLE_SIZE_UPPER_BOUND (1024)

#define ARP_MAX_ENGINE_SIZE      (20) // Engine Count
#define ARP_MAX_IP_SIZE          (20) // IP Count
#define ARP_MAX_MODE_SIZE        (10) // Mode Count

#define ARP_SIZEOF_OPTION        (sizeof(tS8)*50) // IP Option Size
#define ARP_SIZEOF_COMMENT       (sizeof(tS8)*20) // IP Comment size
#define ARP_SIZEOF_ID            (sizeof(tS16))   // IP ID Size
#define ARP_SIZEOF_SIZE          (sizeof(tS32))   // IP Size
#define ARP_SIZEOF_NUM           (sizeof(tS16))   // IP Number Size


#endif //__POSTPROC_MGR_DATATYPE_H__

