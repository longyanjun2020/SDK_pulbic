////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
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

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   MsTypes.h
/// @brief  MStar General Data Types
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __MS_TYPES_H__
#define __MS_TYPES_H__

#define UFO_PUBLIC_HEADER_300 // EROY TBD
#define VDEC3

#ifdef CONFIG_ENABLE_MENUCONFIG
    #include "autoconf.h"
#endif

#include <stddef.h>
//#include "UFO.h" // EROY
//-------------------------------------------------------------------------------------------------
//  System Data Type
//-------------------------------------------------------------------------------------------------
#define SUPPORT_ANDROID_L_PHYVIR_TYPE

/// data type unsigned char, data length 1 byte
typedef unsigned char               u8;                                 // 1 byte
/// data type unsigned short, data length 2 byte
typedef unsigned short              u16;                                // 2 bytes
/// data type unsigned int, data length 4 byte
#if INTPTR_MAX == INT32_MAX
typedef unsigned int                u32;
#else
typedef unsigned long               u32;                                // 4 bytes
#endif
/// data type unsigned int, data length 8 byte
typedef unsigned long long          u64;                                // 8 bytes
/// data type signed char, data length 1 byte
typedef signed char                 s8;                                 // 1 byte
/// data type signed short, data length 2 byte
typedef signed short                s16;                                // 2 bytes
/// data type signed int, data length 4 byte
//typedef signed long                 s32;                                // 4 bytes
/// data type signed long long, data length 8 byte
typedef signed long long            s64;                                // 8 bytes
/// data type float, data length 4 byte
typedef float                       FLOAT;                              // 4 bytes
/// data type unsigned char, data length 1 byte
typedef unsigned char               MS_U8;                              // 1 byte
/// data type unsigned short, data length 2 byte
typedef unsigned short              MS_U16;                             // 2 bytes
/// data type unsigned int, data length 4 byte
typedef unsigned int                MS_U32;                             // 4 bytes
/// data type unsigned long long, data length 8 byte
typedef unsigned long long          MS_U64;                             // 8 bytes
/// data type signed char, data length 1 byte
typedef signed char                 MS_S8;                              // 1 byte
/// data type signed short, data length 2 byte
typedef signed short                MS_S16;                             // 2 bytes
/// data type signed int, data length 4 byte
typedef signed int                  MS_S32;                             // 4 bytes
/// data type signed long long, data length 8 byte
typedef signed long long            MS_S64;                             // 8 bytes
/// data type float, data length 4 byte
typedef float                       MS_FLOAT;                           // 4 bytes
/// data type null pointer
typedef MS_U32                      MS_VIRT;                            // 8 bytes
/// data type hardware physical address
typedef MS_U32                      MS_PHYADDR;                         // 8 bytes
/// data type 64bit physical address
typedef MS_U32                      MS_PHY;                             // 8 bytes
/// data type size_t
typedef MS_U32                      MS_SIZE;                            // 8 bytes
/// definition for MS_BOOL
typedef unsigned char               MS_BOOL;                            // 1 byte
/// print type  MPRI_PHY
#define                             MPRI_PHY                            "%x"
/// print type  MPRI_PHY
#define                             MPRI_VIRT                           "%tx"
#ifdef NULL
#undef NULL
#endif
#define NULL                        0

/// data type hardware physical address
//typedef unsigned long               MS_PHYADDR;                         // 32bit physical address

//-------------------------------------------------------------------------------------------------
//  Software Data Type
//-------------------------------------------------------------------------------------------------

#if 0
#if 1
typedef unsigned char               MS_BOOL;
#else
typedef enum
{
    FALSE = 0,
    TRUE  = 1,
} BOOL, MS_BOOL, bool;
#endif
#endif

/// definition for VOID
#ifdef WIN32
#else
#ifndef VOID
typedef void                        VOID;
#endif
#endif
/// definition for FILEID
//typedef MS_S32                         FILEID;

//[TODO] use MS_U8, ... instead
// data type for 8051 code
//typedef MS_U16                      WORD;
//typedef MS_U8                       BYTE;

#ifndef MSOS_TYPE_LINUX_KERNEL
#ifndef true
/// definition for true
#define true                        1
/// definition for false
#define false                       0
#endif
#endif //End undef MSOS_TYPE_LINUX_KERNEL

#if !defined(TRUE) && !defined(FALSE)
/// definition for TRUE
#define TRUE                        1
/// definition for FALSE
#define FALSE                       0
#endif


#if defined(ENABLE) && (ENABLE!=1)
#warning ENALBE is not 1
#else
#define ENABLE                      1
#endif

#if defined(DISABLE) && (DISABLE!=0)
#warning DISABLE is not 0
#else
#define DISABLE                     0
#endif

//typedef struct _MS_SW_VERSION_INFO
//{
//  char  UtopiaBspVersion[8];  //Utopia BSP Version
//    char    MajorVersion[4];        //Major Version Number
//    char    MinorVersion[4];        //Minor Version Number
//    char    ChangeList_API[16];     //Sync Perforce Change List Number in API Folder
//    char    ChangeList_DRV[16];     //Sync Perforce Change List Number in DRV Folder
//    char    ChangeList_HAL[16];     //Sync Perforce Change List Number in HAL Folder
//} MS_SW_VERSION_INFO;

#define PTR2U32(x) (u32)(intptr_t)(x)
#define PTR2U64(x) (u64)(intptr_t)(x)

#define LIMIT(x, low, high) ((x)>(high)?(high):((x)<(low))?(low):(x))

#define min(a,b)        (((a) >= (b)) ? (b) : ( a))
#define max(a,b)        (((a) >= (b)) ? (a) : ( b))
#define sign(a)         (((a) >  (0)) ? (1) : (-1))
#define minmax(v,a,b)   (((v) <  (a)) ? (a) : ((v) > (b)) ? (b) : (v))

#if defined(__cplusplus) && defined(__GNUC__) && (__GNUC__>=4) && (__GNUC_MINOR__>=6)
#define opaque_enum(e) enum e : int
#else
#define opaque_enum(e) enum e
#endif
#define typedef_opaque_enum(e1, e2) \
    opaque_enum(e1); \
    typedef enum e1 e2



//#define MSG(...) fprintf(stdout, __VA_ARGS__)

#define F_IN()  fprintf(stdout,"%s +\n",__func__);
#define F_OUT()   fprintf(stdout,"%s -\n",__func__);

#ifdef WIN32
#define DES_INIT(a, ...) __VA_ARGS__
#else
#define DES_INIT(a, ...) a = __VA_ARGS__
#endif

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

///Define MS FB Format, to share with GE,GOP
/// FIXME THE NAME NEED TO BE REFINED, AND MUST REMOVE UNNESSARY FMT
typedef enum
{
    /// color format I1
    E_MS_FMT_I1                     = 0x0,
    /// color format I2
    E_MS_FMT_I2                     = 0x1,
    /// color format I4
    E_MS_FMT_I4                     = 0x2,
    /// color format palette 256(I8)
    E_MS_FMT_I8                     = 0x4,
    /// color format blinking display
    E_MS_FMT_FaBaFgBg2266  = 0x6,
    /// color format for blinking display format
    E_MS_FMT_1ABFgBg12355           = 0x7,
    /// color format RGB565
    E_MS_FMT_RGB565                 = 0x8,
    /// color format ARGB1555
    /// @note <b>[URANUS] <em>ARGB1555 is only RGB555</em></b>
    E_MS_FMT_ARGB1555               = 0x9,
    /// color format ARGB4444
    E_MS_FMT_ARGB4444               = 0xa,
    /// color format ARGB1555 DST
    E_MS_FMT_ARGB1555_DST           = 0xc,
    /// color format YUV422
    E_MS_FMT_YUV422                 = 0xe,
    /// color format ARGB8888
    E_MS_FMT_ARGB8888               = 0xf,
    /// color format RGBA5551
    E_MS_FMT_RGBA5551               = 0x10,
    /// color format RGBA4444
    E_MS_FMT_RGBA4444               = 0x11,
    /// Start of New color define
    /// color format BGRA5551
    E_MS_FMT_BGRA5551               = 0x12,
    /// color format ABGR1555
    E_MS_FMT_ABGR1555               = 0x13,
    /// color format ABGR4444
    E_MS_FMT_ABGR4444               = 0x14,
    /// color format BGRA4444
    E_MS_FMT_BGRA4444               = 0x15,
    /// color format BGR565
    E_MS_FMT_BGR565                 = 0x16,
    /// color format RGBA8888
    E_MS_FMT_RGBA8888               = 0x1d,
    /// color format BGRA8888
    E_MS_FMT_BGRA8888               = 0x1e,
    /// color format ABGR8888
    E_MS_FMT_ABGR8888               = 0x1f,
    /// color format AYUV8888
    E_MS_FMT_AYUV8888               = 0x20,

    E_MS_FMT_GENERIC                = 0xFFFF,

} MS_ColorFormat;

typedef union _MSIF_Version
{
    struct _DDI
    {
        MS_U8                       tag[4];
        MS_U8                       type[2];
        MS_U16                      customer;
        MS_U16                      model;
        MS_U16                      chip;
        MS_U8                       cpu;
        MS_U8                       name[4];
        MS_U8                       version[2];
        MS_U8                       build[2];
        MS_U8                       change[8];
        MS_U8                       os;
    } DDI;
    struct _MW
    {
        MS_U8                                     tag[4];
        MS_U8                                     type[2];
        MS_U16                                    customer;
        MS_U16                                    mod;
        MS_U16                                    chip;
        MS_U8                                     cpu;
        MS_U8                                     name[4];
        MS_U8                                     version[2];
        MS_U8                                     build[2];
        MS_U8                                     changelist[8];
        MS_U8                                     os;
    } MW;
    struct _APP
    {
        MS_U8                                     tag[4];
        MS_U8                                     type[2];
        MS_U8                                     id[4];
        MS_U8                                     quality;
        MS_U8                                     version[4];
        MS_U8                                     time[6];
        MS_U8                                     changelist[8];
        MS_U8                                     reserve[3];
    } APP;
} MSIF_Version;

typedef struct _MS_SW_VERSION_INFO
{
	char	UtopiaBspVersion[8];	//Utopia BSP Version
    char    MajorVersion[4];        //Major Version Number
    char    MinorVersion[4];        //Minor Version Number
    char    ChangeList_API[16];     //Sync Perforce Change List Number in API Folder
    char    ChangeList_DRV[16];     //Sync Perforce Change List Number in DRV Folder
    char    ChangeList_HAL[16];     //Sync Perforce Change List Number in HAL Folder

} MS_SW_VERSION_INFO;

typedef struct _MS_SW_VERSION_NUM
{
    char    UtopiaBspVersion[32];
    MS_U32  UtopiaVerNum;
} MS_SW_VERSION_NUM;


#define DLL_PACKED
#endif // __MS_TYPES_H__
