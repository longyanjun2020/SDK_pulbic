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


#ifndef MSVC_INTTYPES_H
#define MSVC_INTTYPES_H

#include <stdint.h>

#if !defined(__cplusplus) || defined(__STDC_FORMAT_MACROS)

#if _MSC_VER < 1300
#define _INTTYPES_HH  // not supported
#define _INTTYPES_I32 // not supported
#else
#define _INTTYPES_HH  "hh"
#define _INTTYPES_I32 "I32"
#endif

/* fprintf macros for signed integers */
#define PRId8  _INTTYPES_HH"d"
#define PRId16 "hd"
#define PRId32 _INTTYPES_I32"d"
#define PRId64 "I64d"

#define PRIi8  _INTTYPES_HH"i"
#define PRIi16 "hi"
#define PRIi32 _INTTYPES_I32"i"
#define PRIi64 "I64i"

/* fprintf macros for unsigned integers */
#define PRIo8  _INTTYPES_HH"o"
#define PRIo16 "ho"
#define PRIo32 _INTTYPES_I32"o"
#define PRIo64 "I64o"

#define PRIu8  _INTTYPES_HH"u"
#define PRIu16 "hu"
#define PRIu32 _INTTYPES_I32"u"
#define PRIu64 "I64u"

#define PRIx8  _INTTYPES_HH"x"
#define PRIx16 "hx"
#define PRIx32 _INTTYPES_I32"x"
#define PRIx64 "I64x"

#define PRIX8  _INTTYPES_HH"X"
#define PRIX16 "hX"
#define PRIX32 _INTTYPES_I32"X"
#define PRIX64 "I64X"

/* fscanf macros for signed integers */
#define SCNd8  _INTTYPES_HH"d"
#define SCNd16 "hd"
#define SCNd32 _INTTYPES_I32"d"
#define SCNd64 "I64d"

#define SCNi8  _INTTYPES_HH"i"
#define SCNi16 "hi"
#define SCNi32 _INTTYPES_I32"i"
#define SCNi64 "I64i"

/* fscanf macros for unsigned integers */
#define SCNo8  _INTTYPES_HH"o"
#define SCNo16 "ho"
#define SCNo32 _INTTYPES_I32"o"
#define SCNo64 "I64o"

#define SCNu8  _INTTYPES_HH"u"
#define SCNu16 "hu"
#define SCNu32 _INTTYPES_I32"u"
#define SCNu64 "I64u"

#define SCNx8  _INTTYPES_HH"x"
#define SCNx16 "hx"
#define SCNx32 _INTTYPES_I32"x"
#define SCNx64 "I64x"

#define SCNX8  _INTTYPES_HH"X"
#define SCNX16 "hX"
#define SCNX32 _INTTYPES_I32"X"
#define SCNX64 "I64X"
#endif

#endif /* MSVC_INTTYPES_H */
