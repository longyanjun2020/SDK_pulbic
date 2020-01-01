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
--  Abstract : Stream decoding storage definition
--
--------------------------------------------------------------------------------
--
--  Version control information, please leave untouched.
--
--  $RCSfile: mpeg2hwd_storage.h,v $
--  $Date: 2008/02/19 10:51:10 $
--  $Revision: 1.10 $
--
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------

    Table of context 

     1. xxx...
   
 
------------------------------------------------------------------------------*/
#ifdef _HANTRO_M2V_EN_
#ifndef MPEG2DECSTRMSTORAGE_H_DEFINED
#define MPEG2DECSTRMSTORAGE_H_DEFINED

#include "drv_mfd_basetype.h"
#include "drv_mfd_mpeg2hwd_cfg.h"

#ifdef _M4VD_GBUF_
#include "drv_mfd_mvc_decoder.h"
#endif

typedef struct
{
    MEMMAP_t data;
    u32 picType;
    u32 picId;
    u32 tf;
    u32 ff[2];
    u32 rff;
    u32 rfc;
    u32 isInter;
    u32 nbrErrMbs;
    Mpeg2DecRet retVal;
    u32 sendToPp;
    Mpeg2DecTime timeCode;
} picture_t;

typedef struct
{
    u32 status;
    u32 strmDecReady;

    u32 validPicHeader;
    u32 validPicExtHeader;
    u32 validSequence;
    u32 vpQP;

#ifdef _M4VD_GBUF_
    VID_PICTURE *cur_pic;
    VID_PICTURE decPic[4];
    u32 offsetFlag_Y;
#endif

    picture_t pPicBuf[4];
    u32 outBuf[2];
    u32 outIndex;
    u32 outCount;
    u32 workOut;
    u32 work0;
    u32 work1;
    u32 latestId;   /* current pic id, used for debug */
    u32 skipB;
    u32 prevPicCodingType;
    u32 prevPicStructure;
    u32 fieldToReturn;  /* 0 = First, 1 second */

} DecStrmStorage;

#endif /* #ifndef MPEG2DECSTRMSTORAGE_H_DEFINED */
#endif // _HANTRO_M2V_EN_
