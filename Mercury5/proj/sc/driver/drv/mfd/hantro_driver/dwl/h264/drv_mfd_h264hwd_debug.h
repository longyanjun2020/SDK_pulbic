/*------------------------------------------------------------------------------
--                                                                            --
--       This software is confidential and proprietary and may be used        --
--        only as expressly authorized by a licensing agreement from          --
--                                                                            --
--                            Hantro Products Oy.                             --
--                                                                            --
--                   (C) COPYRIGHT 2006 HANTRO PRODUCTS OY                    --
--                            ALL RIGHTS RESERVED                             --
--                                                                            --
--                 The entire notice above must be reproduced                 --
--                  on all copies and should not be removed.                  --
--                                                                            --
--------------------------------------------------------------------------------
--
--  Abstract : Utility macros for debugging and tracing
--
--------------------------------------------------------------------------------
--
--  Version control information, please leave untouched.
--
--  $RCSfile: h264hwd_debug.h,v $
--  $Date: 2007/07/06 14:01:37 $
--  $Revision: 1.1 $
--
------------------------------------------------------------------------------*/

#ifndef __H264DEBUG_H__
#define __H264DEBUG_H__

/* macro for assertion, used only when _ASSERT_USED is defined */
#ifdef _ASSERT_USED
#ifndef ASSERT
#include <assert.h>
#define ASSERT(expr) assert(expr)
#endif
#else
//move to mstar_fpga.h
//#define ASSERT(expr)
#endif

/* macros for range checking used only when _RANGE_CHECK is defined */
#ifdef _RANGE_CHECK

/* macro for range checking an single value */
#define RANGE_CHECK(value, minBound, maxBound) \
{ \
    if ((value) < (minBound) || (value) > (maxBound)) \
        fprintf(stderr, "Warning: Value exceeds given limit(s)!\n"); \
}

/* macro for range checking an array of values */
#define RANGE_CHECK_ARRAY(array, minBound, maxBound, length) \
{ \
    i32 i; \
    for (i = 0; i < (length); i++) \
        if ((array)[i] < (minBound) || (array)[i] > (maxBound)) \
            fprintf(stderr,"Warning: Value [%d] exceeds given limit(s)!\n",i); \
}

#else /* _RANGE_CHECK */

#define RANGE_CHECK_ARRAY(array, minBound, maxBound, length)
#define RANGE_CHECK(value, minBound, maxBound)

#endif /* _RANGE_CHECK */

#include "drv_mfd_mstar_fpga.h"
//move _DEBUG_PRINT and _ERROR_PRINT to mstar_fpga.h
#if 0
/* macro for debug printing, used only when _DEBUG_PRINT is defined */
#ifdef _DEBUG_PRINT
#define DEBUG_PRINT(args) printf args
#else
#define DEBUG_PRINT(args)
#endif

/* macro for error printing, used only when _ERROR_PRINT is defined */
#ifdef _ERROR_PRINT
#include <stdio.h>
#define ERROR_PRINT(msg) fprintf(stderr,"ERROR: %s\n",msg)
#else
#define ERROR_PRINT(msg)
#endif
#endif //if 0

#endif /* __H264DEBUG_H__ */
