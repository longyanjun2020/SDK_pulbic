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
--  Abstract : Decoded Picture Buffer (DPB) handling
--
--------------------------------------------------------------------------------
--
--  Version control information, please leave untouched.
--
--  $RCSfile: h264hwd_dpb.h,v $
--  $Date: 2007/10/08 09:52:41 $
--  $Revision: 1.2 $
--
------------------------------------------------------------------------------*/

#ifndef H264HWD_DPB_H
#define H264HWD_DPB_H

/*------------------------------------------------------------------------------
    1. Include headers
------------------------------------------------------------------------------*/

#include "drv_mfd_basetype.h"

#include "drv_mfd_h264hwd_slice_header.h"
#include "drv_mfd_h264hwd_image.h"

#include "drv_mfd_dwl.h"

#ifdef _M4VD_GBUF_
#include "drv_mfd_mvc_decoder.h"
#endif

/*------------------------------------------------------------------------------
    2. Module defines
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    3. Data types
------------------------------------------------------------------------------*/

/* enumeration to represent status of buffered image */
typedef enum
{
    UNUSED = 0,
    NON_EXISTING,
    SHORT_TERM,
    LONG_TERM
} dpbPictureStatus_e;

/* structure to represent a buffered picture */
typedef struct dpbPicture
{
    MEMMAP_t *data;
    u32 asicListID;
    i32 picNum;
    u32 frameNum;
    i32 picOrderCnt;
    dpbPictureStatus_e status;
    u32 toBeDisplayed;
    u32 picId;
    u32 numErrMbs;
    u32 isIdr;
#ifdef _M4VD_GBUF_
    VID_PICTURE decPic;
#endif
} dpbPicture_t;

/* structure to represent display image output from the buffer */
typedef struct
{
    MEMMAP_t *data;
    u32 picId;
    u32 numErrMbs;
    u32 isIdr;
#ifdef _M4VD_GBUF_
    VID_PICTURE decPic;
#endif
} dpbOutPicture_t;

typedef struct
{
    dpbOutPicture_t *outBuf;
    u32 outBufListSize;
    u32 numOut;
    u32 outIndex;
} dpbPrevOutBuf_t;

/* structure to represent DPB */
typedef struct dpbStorage
{
    /*dpbPrevOutBuf_t prevOutBuf; */
#ifdef _M4VD_GBUF_
    VID_PICTURE* cur_pic;
    u32 offsetFlag_Y;
#ifdef _KMV_    
    VID_PICTURE* cur_decPic_p;
#endif
#endif
    dpbPicture_t buffer[16 + 1];
    dpbPicture_t *list[16 + 1];
    dpbPicture_t *currentOut;
    dpbOutPicture_t *outBuf;
    u32 numOut;
    u32 outIndex;
    u32 maxRefFrames;
    u32 dpbSize;
    u32 maxFrameNum;
    u32 maxLongTermFrameIdx;
    u32 numRefFrames;
    u32 fullness;
    u32 prevRefFrameNum;
    u32 lastContainsMmco5;
    u32 noReordering;
    u32 flushed;
    u32 picSizeInMbs;
} dpbStorage_t;

/*------------------------------------------------------------------------------
    4. Function prototypes
------------------------------------------------------------------------------*/

u32 h264bsdInitDpb(const void *dwl,
                   dpbStorage_t * dpb,
                   u32 picSizeInMbs,
                   u32 dpbSize,
                   u32 numRefFrames, u32 maxFrameNum, u32 noReordering);

u32 h264bsdResetDpb(const void *dwl,
                    dpbStorage_t * dpb,
                    u32 picSizeInMbs,
                    u32 dpbSize,
                    u32 numRefFrames, u32 maxFrameNum, u32 noReordering);

void h264bsdInitRefPicList(dpbStorage_t * dpb);

void *h264bsdAllocateDpbImage(dpbStorage_t * dpb);

i32 h264bsdGetRefPicData(const dpbStorage_t * dpb, u32 index);
u8 *h264bsdGetRefPicDataVlcMode(const dpbStorage_t * dpb, u32 index);

u32 h264bsdReorderRefPicList(dpbStorage_t * dpb,
                             refPicListReordering_t * order,
                             u32 currFrameNum, u32 numRefIdxActive);

u32 h264bsdMarkDecRefPic(dpbStorage_t * dpb,
                         /*@null@ */ const decRefPicMarking_t * mark,
                         const image_t * image,
                         u32 frameNum,
                         i32 picOrderCnt, u32 isIdr, u32 picId, u32 numErrMbs);

u32 h264bsdCheckGapsInFrameNum(dpbStorage_t * dpb, u32 frameNum, u32 isRefPic,
                               u32 gapsAllowed);

/*@null@*/ dpbOutPicture_t *h264bsdDpbOutputPicture(dpbStorage_t * dpb);

void h264bsdFlushDpb(dpbStorage_t * dpb);

void h264bsdFreeDpb(const void *dwl, dpbStorage_t * dpb);

#endif /* #ifdef H264HWD_DPB_H */
