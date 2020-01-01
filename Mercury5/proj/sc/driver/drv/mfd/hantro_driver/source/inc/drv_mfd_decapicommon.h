/*------------------------------------------------------------------------------
--                                                                            --
--       This software is confidential and proprietary and may be used        --
--        only as expressly authorized by a licensing agreement from          --
--                                                                            --
--                            Hantro Products Oy.                             --
--                                                                            --
--                   (C) COPYRIGHT 2007 HANTRO PRODUCTS OY                    --
--                            ALL RIGHTS RESERVED                             --
--                                                                            --
--                 The entire notice above must be reproduced                 --
--                  on all copies and should not be removed.                  --
--                                                                            --
--------------------------------------------------------------------------------
--
--  Description : Common Decoder API definitions
--
--------------------------------------------------------------------------------
--
--  Version control information, please leave untouched.
--
--  $RCSfile: decapicommon.h,v $
--  $Date: 2007/11/06 13:38:50 $
--  $Revision: 1.3 $
--
------------------------------------------------------------------------------*/
#ifndef __DECAPICOMMON_H__
#define __DECAPICOMMON_H__

#include "drv_mfd_basetype.h"

#define MPEG4_NOT_SUPPORTED             (u32)(0x00)
#define MPEG4_SIMPLE_PROFILE            (u32)(0x01)
#define MPEG4_ADVANCED_SIMPLE_PROFILE   (u32)(0x02)
#define H264_NOT_SUPPORTED              (u32)(0x00)
#define H264_BASELINE_PROFILE           (u32)(0x01)
#define H264_HIGH_PROFILE               (u32)(0x02)
#define VC1_NOT_SUPPORTED               (u32)(0x00)
#define VC1_SIMPLE_PROFILE              (u32)(0x01)
#define VC1_MAIN_PROFILE                (u32)(0x02)
#define VC1_ADVANCED_PROFILE            (u32)(0x03)
#define MPEG2_NOT_SUPPORTED             (u32)(0x00)
#define MPEG2_MAIN_PROFILE              (u32)(0x01)
#define JPEG_NOT_SUPPORTED              (u32)(0x00)
#define JPEG_BASELINE                   (u32)(0x01)
#define PP_NOT_SUPPORTED                (u32)(0x00)
#define PP_SUPPORTED                    (u32)(0x01)
#define PP_DITHERING                    (u32)(0x10000000)
#define PP_SCALING                      (u32)(0x0C000000)
#define PP_DEINTERLACING                (u32)(0x02000000)
#define PP_ALPHA_BLENDING               (u32)(0x01000000)
#define SORENSON_SPARK_NOT_SUPPORTED    (u32)(0x00)
#define SORENSON_SPARK_SUPPORTED        (u32)(0x01)

typedef struct DecHwConfig_
{
    u32 mpeg4Support;        /* one of the MPEG4 values defined above */
    u32 h264Support;         /* one of the H264 values defined above */
    u32 vc1Support;          /* one of the VC1 values defined above */
    u32 mpeg2Support;        /* one of the MPEG2 values defined above */
    u32 jpegSupport;         /* one of the JPEG values defined above */
    u32 maxDecPicWidth;      /* maximum picture width in decoder */
    u32 ppSupport;           /* PP_SUPPORTED or PP_NOT_SUPPORTED */
    u32 ppConfig;            /* Bitwise list of PP function */
    u32 maxPpOutPicWidth;    /* maximum post-processor output picture width */
    u32 sorensonSparkSupport;/* one of the SORENSON_SPARK values defined above */
} DecHwConfig;

#endif /* __DECAPICOMMON_H__ */
