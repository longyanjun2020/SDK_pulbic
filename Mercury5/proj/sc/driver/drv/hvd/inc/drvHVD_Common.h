//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all 
// or part of MStar Software is expressly prohibited, unless prior written 
// permission has been granted by MStar. 
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.  
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software. 
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s 
//    confidential information in strictest confidence and not disclose to any
//    third party.  
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.  
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or 
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.  
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
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
/// @file   drvHVD_Common.h
/// @brief  MStar General Data Types
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVHVD_COMMON_H_
#define _DRVHVD_COMMON_H_
#if !(defined(REDLION_LINUX_KERNEL_ENVI))
#include "MsCommon.h"
#include "MsVersion.h"
#else //defined(REDLION_LINUX_KERNEL_ENVI)
//-------------------------------------------------------------------------------------------------
//  System Data Type
//-------------------------------------------------------------------------------------------------

#if !(defined( __MDRV_TYPES_H__ ))
/// data type unsigned char, data length 1 byte
typedef unsigned char               MS_U8;                              // 1 byte
/// data type unsigned short, data length 2 byte
typedef unsigned short              MS_U16;                             // 2 bytes
/// data type unsigned int, data length 4 byte
typedef unsigned long               MS_U32;                             // 4 bytes
/// data type unsigned int, data length 8 byte
typedef unsigned long long          MS_U64;                             // 8 bytes
/// data type signed char, data length 1 byte
typedef signed char                 MS_S8;                              // 1 byte
/// data type signed short, data length 2 byte
typedef signed short                MS_S16;                             // 2 bytes
/// data type signed int, data length 4 byte
typedef signed long                 MS_S32;                             // 4 bytes
/// data type signed int, data length 8 byte
typedef signed long long            MS_S64;                             // 8 bytes

/// data type float, data length 4 byte
typedef float                       MS_FLOAT;                           // 4 bytes

/// definition for MS_BOOL
typedef unsigned char               MS_BOOL;
/// definition for VOID
typedef void                        VOID;
/// definition for FILEID
typedef MS_S32                      FILEID;

#endif

typedef unsigned long               MS_PHYADDR;                         // 32bit physical address


/// data type null pointer
#ifdef NULL
#undef NULL
#endif
#define NULL                        0

/// data type hardware physical address


//-------------------------------------------------------------------------------------------------
//  Software Data Type
//-------------------------------------------------------------------------------------------------


//[TODO] use MS_U8, ... instead
// data type for 8051 code
//typedef MS_U16                      WORD;
//typedef MS_U8                       BYTE;


#ifndef true
/// definition for true
#define true                        1
/// definition for false
#define false                       0
#endif


#if !defined(TRUE) && !defined(FALSE)
/// definition for TRUE
#define TRUE                        1
/// definition for FALSE
#define FALSE                       0
#endif

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

    E_MS_FMT_GENERIC                = 0xFFFF,

} MS_ColorFormat;


typedef union _MSIF_Version
{
    struct _DDI
    {
        MS_U8                       tag[4];
        MS_U8                       class[2];
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
    } MW;

    struct _APP
    {
    } APP;

} MSIF_Version;

#ifndef BIT
#define BIT(_bit_)                  (1 << (_bit_))
#endif

#ifndef BITS
    #ifdef _BIT
        #define BITS(bits,value)            ((_BIT(((1)?bits)+1)-_BIT(((0)?bits))) & (value<<((0)?bits)))
    #elif defined(BIT)
        #define BITS(_bits_, _val_)         ((BIT(((1)?_bits_)+1)-BIT(((0)?_bits_))) & (_val_<<((0)?_bits_)))
    #endif
#endif

#ifndef BMASK
    #ifdef _BIT
        #define BMASK(bits)                 (_BIT(((1)?bits)+1)-_BIT(((0)?bits)))
    #elif defined(BIT)
        #define BMASK(_bits_)               (BIT(((1)?_bits_)+1)-BIT(((0)?_bits_)))
    #endif
#endif

#define READ_BYTE(_reg)             (*(volatile MS_U8*)(_reg))
#define READ_WORD(_reg)             (*(volatile MS_U16*)(_reg))
#define READ_LONG(_reg)             (*(volatile MS_U32*)(_reg))
#define WRITE_BYTE(_reg, _val)      { (*((volatile MS_U8*)(_reg))) = (MS_U8)(_val); }
#define WRITE_WORD(_reg, _val)      { (*((volatile MS_U16*)(_reg))) = (MS_U16)(_val); }
#define WRITE_LONG(_reg, _val)      { (*((volatile MS_U32*)(_reg))) = (MS_U32)(_val); }

#define MSIF_TAG                    {'M','S','I','F'}                   // MSIF
#define MSIF_CLASS                  {'0','0'}                           // DRV/API (DDI)
#define MSIF_CUS                    0x0000                              // MStar Common library
#define MSIF_MOD                    0x0000                              // MStar Common library
#define MSIF_CHIP                   0x000B
#define MSIF_CPU                    '0'
#define MSIF_OS                     '2'

#define DISABLE                     0
#define ENABLE                      1



#endif //defined(REDLION_LINUX_KERNEL_ENVI)

#endif // _DRVHVD_COMMON_H_
