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
--  Abstract : algorithm header file
--
--------------------------------------------------------------------------------
--
--  Version control information, please leave untouched.
--
--  $RCSfile: mpeg2hwd_strmdesc.h,v $
--  $Date: 2007/09/19 10:48:00 $
--  $Revision: 1.5 $
--
------------------------------------------------------------------------------*/

/*****************************************************************************/
#ifdef _HANTRO_M2V_EN_
#ifndef MPEG2DECSTRMDESC_H_DEFINED
#define MPEG2DECSTRMDESC_H_DEFINED

#include "drv_mfd_basetype.h"

typedef struct
{
    const u8 *pStrmBuffStart; /* pointer to start of stream buffer */
    const u8 *pStrmCurrPos;   /* current read addres in stream buffer */
    u32 bitPosInWord;   /* bit position in stream buffer */
    u32 strmBuffSize;   /* size of stream buffer (bytes) */
    u32 strmBuffReadBits;   /* number of bits read from stream buffer */

} DecStrmDesc;

#endif /* #ifndef MPEG2DECSTRMDESC_H_DEFINED */
#endif // _HANTRO_M2V_EN_