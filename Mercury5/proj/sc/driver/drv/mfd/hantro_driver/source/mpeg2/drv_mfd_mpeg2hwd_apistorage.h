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
--  Abstract : API's internal static data storage definition
--
--------------------------------------------------------------------------------
--
--  Version control information, please leave untouched.
--
--  $RCSfile: mpeg2hwd_apistorage.h,v $
--  $Date: 2007/09/19 10:48:00 $
--  $Revision: 1.6 $
--
------------------------------------------------------------------------------*/
#ifdef _HANTRO_M2V_EN_
#ifndef MPEG2DECAPISTORAGE_H
#define MPEG2DECAPISTORAGE_H

#include "drv_mfd_dwl.h"

typedef struct
{
    enum
    {
        UNINIT,
        INITIALIZED,
        HEADERSDECODED,
        STREAMDECODING,
        HW_PIC_STARTED,
        HW_STRM_ERROR
    } DecStat;

    enum
    {
        NO_BUFFER = 0,
        BUFFER_0,
        BUFFER_1,
        BUFFER_2
    } bufferForPp;

    MEMMAP_t InternalFrameIn;
    MEMMAP_t InternalFrameOut;
    MEMMAP_t pQTableBase;

    u32 firstHeaders;
    u32 disableFilter;
    u32 externalBuffers;    /* application gives frame buffers */
    u32 firstField;
    u32 outputOtherField;
    u32 parity;
    u32 ignoreField;

} DecApiStorage;

#endif /* #ifndef MPEG2DECAPISTORAGE_H */
#endif // _HANTRO_M2V_EN_

