////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2010 MStar Semiconductor, Inc.
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


#ifndef MSVC_STDINT_H
#define MSVC_STDINT_H

typedef unsigned __int8   uint8_t;
typedef   signed __int8    int8_t;
typedef unsigned __int16 uint16_t;
typedef   signed __int16  int16_t;
typedef unsigned __int32 uint32_t;
typedef   signed __int32  int32_t;
typedef unsigned __int64 uint64_t;
typedef   signed __int64  int64_t;

#if defined(_WIN64)
typedef          __int64  intptr_t;
typedef unsigned __int64 uintptr_t;
#else
typedef            int    intptr_t;
typedef unsigned   int   uintptr_t;
#endif

#if !defined(__cplusplus) || defined(__STDC_CONSTANT_MACROS)
#define INT64_C(val) (val##I64)
#endif

#endif /* MSVC_STDINT_H */
