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
--  $RCSfile: mp4dechwd_storage.h,v $
--  $Date: 2008/01/08 15:05:51 $
--  $Revision: 1.2 $
--
------------------------------------------------------------------------------*/
#ifndef DECSTRMSTORAGE_H_DEFINED
#define DECSTRMSTORAGE_H_DEFINED

#include "drv_mfd_basetype.h"
#include "drv_mfd_mp4deccfg.h"

#ifdef _M4VD_GBUF_
#include "drv_mfd_mvc_decoder.h"
#endif

typedef struct
{
    u32 dataIndex;
    u32 picType;
    u32 picId;
    u32 isInter;
    MP4DecRet retVal;
    u32 nbrErrMbs;
    u32 sendToPp;
    MP4DecTime timeCode;
} picture_t;

typedef struct
{
    u8  quantMat[64*2];
    u32 status; /* status of syncronization */
    u32 strmDecReady;

    u32 resyncMarkerLength;
    u32 vpMbNumber;
    u32 vpNumMbs;
    u32 vpFirstCodedMb;
    u32 qP;
    u32 prevQP;
    u32 vpQP;
    u32 skipB;

    u32 shortVideo;
    u32 mpeg4Video; /* Sequence contains mpeg-4 headers: either mpeg-4 or
                       mpeg-4 short video */
    u32 gobResyncFlag;

    const u8 *pLastSync;
    /* pointer to stream buffer right after motion vectors of an intra macro
     * block. Needed to avoid decoding motion vectors twice in case decoder
     * runs out of rlc buffer (decoding twice means using results of previous
     * decoding in motion vector differential decoding) */
    u8 *pStrmAfterMv;
    u32 bitPosAfterMv;
    u32 readBitsAfterMv;

    u32 startCodeLoss;
    u32 validVopHeader;

    /* to be added to TicsFromPrev (to accommodate modulo time base changes
     * caused by GOV time codes) */
    u32 govTimeIncrement;

    u32 numErrMbs;

    /* 6 lsbs represent status for each block, msb high if mb not coded */
    u8 codedBits[MP4API_DEC_MBS];

    MEMMAP_t quantMatLinear;
    MEMMAP_t directMvs;

#ifdef _M4VD_GBUF_
    VID_PICTURE *cur_pic;
    VID_PICTURE decPic[4];
    u32 offsetFlag_Y;
#endif
    picture_t pPicBuf[4];
    MEMMAP_t data[4];
    u32 outBuf[2];
    u32 outIndex;
    u32 outCount;
    u32 workOut;
    u32 work0;
    u32 work1;
    u32 latestId; /* current pic id, used for debug */
    u32 previousNotCoded;

    u32 sorensonSpark;
    u32 sorensonVer;
    u32 disposable; /* sorenson */
    u32 unsupportedFeaturesPresent;

    /* these are used to check if re-initialization is needed */
    u32 lowDelay;
    u32 videoObjectLayerWidth;
    u32 videoObjectLayerHeight;

    u8  lastPacketByte; /* last byte of last decoded packet. used to check
                         * against clumsily stuffed short video end markers */

} DecStrmStorage;

#endif
