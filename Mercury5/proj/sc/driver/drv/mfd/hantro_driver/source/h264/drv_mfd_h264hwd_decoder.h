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
--  Abstract : Top level control of the decoder
--
--------------------------------------------------------------------------------
--
--  Version control information, please leave untouched.
--
--  $RCSfile: h264hwd_decoder.h,v $
--  $Date: 2007/07/06 13:58:47 $
--  $Revision: 1.1 $
--
------------------------------------------------------------------------------*/
#ifndef H264HWD_DECODER_H
#define H264HWD_DECODER_H

/*------------------------------------------------------------------------------
    1. Include headers
------------------------------------------------------------------------------*/

#include "drv_mfd_basetype.h"
#include "drv_mfd_h264hwd_storage.h"
#include "drv_mfd_h264hwd_container.h"

/*------------------------------------------------------------------------------
    2. Module defines
------------------------------------------------------------------------------*/

/* enumerated return values of the functions */
enum
{
    H264BSD_RDY,
    H264BSD_PIC_RDY,
    H264BSD_HDRS_RDY,
    H264BSD_ERROR,
    H264BSD_PARAM_SET_ERROR,
    H264BSD_NEW_ACCESS_UNIT,
    H264BSD_FMO,
    H264BSD_ERROR_CONCEAL
};

/*------------------------------------------------------------------------------
    3. Data types
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    4. Function prototypes
------------------------------------------------------------------------------*/

void h264bsdInit(storage_t * pStorage, u32 noOutputReordering);
u32 h264bsdDecode(decContainer_t * pDecCont, const u8 * byteStrm, u32 len,
                  u32 picId, u32 * readBytes);
void h264bsdShutdown(storage_t * pStorage);

/*@null@*/ void *h264bsdNextOutputPicture(storage_t * pStorage, u32 * picId,
                                          u32 * isIdrPic, u32 * numErrMbs);

u32 h264bsdPicWidth(storage_t * pStorage);
u32 h264bsdPicHeight(storage_t * pStorage);
u32 h264bsdVideoRange(storage_t * pStorage);
u32 h264bsdMatrixCoefficients(storage_t * pStorage);
void h264bsdCroppingParams(storage_t * pStorage, u32 * croppingFlag,
                           u32 * left, u32 * width, u32 * top, u32 * height);

u32 h264bsdCheckValidParamSets(storage_t * pStorage);

void h264bsdFlushBuffer(storage_t * pStorage);

u32 h264bsdAspectRatioIdc(const storage_t * pStorage);
void h264bsdSarSize(const storage_t * pStorage, u32 * sar_width,
                    u32 * sar_height);

#endif /* #ifdef H264HWD_DECODER_H */
