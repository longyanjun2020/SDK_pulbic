/***********************************************************************
Filename   : rvgnu.h
Description: config file gnu compiler tools
************************************************************************
        Copyright (c) 2001 RADVISION Inc. and RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Inc. and RADVISION Ltd.. No part of this document may be
reproduced in any form whatsoever without written prior approval by
RADVISION Inc. or RADVISION Ltd..

RADVISION Inc. and RADVISION Ltd. reserve the right to revise this
publication and make changes without obligation to notify any person of
such revisions or changes.
***********************************************************************/
#ifndef RV_AEON_H
#define RV_AEON_H

#include <limits.h>

/* Possible type definitions. Used only for mapping into rvtypes */
/* definitions, not for use outside of this file. */
#define RV_SIZET_TYPE             size_t
#define RV_PTRDIFFT_TYPE          ptrdiff_t
#define RV_CHARACTER_TYPE         char
#define RV_SIGNED_CHAR_TYPE       signed char
#define RV_UNSIGNED_CHAR_TYPE     unsigned char
#define RV_SIGNED_SHORT_TYPE      signed short
#define RV_UNSIGNED_SHORT_TYPE    unsigned short
#define RV_SIGNED_INT_TYPE        signed int
#define RV_UNSIGNED_INT_TYPE      unsigned int
#define RV_SIGNED_LONG_TYPE       signed long
#define RV_UNSIGNED_LONG_TYPE     unsigned long
#define RV_SIGNED_LONGLONG_TYPE   signed long long
#define RV_UNSIGNED_LONGLONG_TYPE unsigned long long

/* Corresponding macros for attaching proper type suffixes to */
/* constants Used only for mapping into rvtypes definitions, not */
/* Outside of this file. */
#define RV_SIGNED_CHAR_SUFFIX(_n)       _n
#define RV_UNSIGNED_CHAR_SUFFIX(_n)     _n
#define RV_SIGNED_SHORT_SUFFIX(_n)      _n
#define RV_UNSIGNED_SHORT_SUFFIX(_n)    _n ## U
#define RV_SIGNED_INT_SUFFIX(_n)        _n
#define RV_UNSIGNED_INT_SUFFIX(_n)      _n ## U
#define RV_SIGNED_LONG_SUFFIX(_n)       _n ## L
#define RV_UNSIGNED_LONG_SUFFIX(_n)     _n ## UL
#define RV_SIGNED_LONGLONG_SUFFIX(_n)   _n ## LL
#define RV_UNSIGNED_LONGLONG_SUFFIX(_n) _n ## ULL

/* Provide type and suffix mappings for specific bit models. */
/* See rvtypes.h for requred definitions. These definitionions */
/* are only for use by the rvtypes.h file. */
#define RV_CHAR_TYPE           RV_CHARACTER_TYPE
#define RV_VAR_INT_TYPE        RV_SIGNED_INT_TYPE
#define RV_VAR_UINT_TYPE       RV_UNSIGNED_INT_TYPE
#define RV_VAR_LONG_TYPE       RV_SIGNED_LONG_TYPE
#define RV_VAR_ULONG_TYPE      RV_UNSIGNED_LONG_TYPE
#define RV_SIGNED_INT8_TYPE    RV_SIGNED_CHAR_TYPE
#define RV_UNSIGNED_INT8_TYPE  RV_UNSIGNED_CHAR_TYPE
#define RV_SIGNED_INT16_TYPE   RV_SIGNED_SHORT_TYPE
#define RV_UNSIGNED_INT16_TYPE RV_UNSIGNED_SHORT_TYPE
#define RV_SIGNED_INT32_TYPE   RV_SIGNED_INT_TYPE
#define RV_UNSIGNED_INT32_TYPE RV_UNSIGNED_INT_TYPE
#define RV_SIGNED_INT64_TYPE   RV_SIGNED_LONGLONG_TYPE
#define RV_UNSIGNED_INT64_TYPE RV_UNSIGNED_LONGLONG_TYPE

#define RV_VAR_INT_SUFFIX        RV_SIGNED_INT_SUFFIX
#define RV_VAR_UINT_SUFFIX       RV_UNSIGNED_INT_SUFFIX
#define RV_SIGNED_INT8_SUFFIX    RV_SIGNED_CHAR_SUFFIX
#define RV_UNSIGNED_INT8_SUFFIX  RV_UNSIGNED_CHAR_SUFFIX
#define RV_SIGNED_INT16_SUFFIX   RV_SIGNED_SHORT_SUFFIX
#define RV_UNSIGNED_INT16_SUFFIX RV_UNSIGNED_SHORT_SUFFIX
#define RV_SIGNED_INT32_SUFFIX   RV_SIGNED_INT_SUFFIX
#define RV_UNSIGNED_INT32_SUFFIX RV_UNSIGNED_INT_SUFFIX
#define RV_SIGNED_INT64_SUFFIX   RV_SIGNED_LONGLONG_SUFFIX
#define RV_UNSIGNED_INT64_SUFFIX RV_UNSIGNED_LONGLONG_SUFFIX

/* Since RvInt and RvUint are variable size types, min and */
/* max must be determined for them. */
#define RV_VAR_INT_MAX  INT_MAX
#define RV_VAR_INT_MIN  INT_MIN
#define RV_VAR_UINT_MAX UINT_MAX

#define RVINLINE       extern inline
#define RVSTATICINLINE static inline

#define TMT_TRACE 1
#define TRM_TRACE 0

#define RV_GET_LOWBYTE(a)   (RvUint32)(((RvUint64)a)&0xFFFFFFFF)
#define RV_GET_HIGHBYTE(a)  (RvUint32)(((RvUint64)(a)>>32)&0xFFFFFFFF)

#if TMT_TRACE
#define RVLEVEL_18 ((unsigned long) (0x12 << 8))
#define RV_CUS1 0x18
#define rv_log(level, format, args...) (level==2)?(vm_dbgError(RV_CUS1|RVLEVEL_18, "[VT_STACK]"format, ##args);):(vm_dbgTrace(RV_CUS1|RVLEVEL_18, "[VT_STACK]"format, ##args);)
#define  printf(format, args...)
#elif  TRM_TRACE
#define  rv_log(level, format, args...) UartSendTrace(format, ##args);
#define  printf(format, args...)
#else
#define  rv_log(level, format, args...)
#define  printf(format, args...)
#endif

#endif /* RV_GNU_H */
