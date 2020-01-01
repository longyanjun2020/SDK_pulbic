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
--  $RCSfile: mpeg2hwd_framedesc.h,v $
--  $Date: 2007/09/19 10:48:00 $
--  $Revision: 1.4 $
--
------------------------------------------------------------------------------*/

/*****************************************************************************/
#ifdef _HANTRO_M2V_EN_
#ifndef MPEG2DECFRAMEDESC_H_DEFINED
#define MPEG2DECFRAMEDESC_H_DEFINED

#include "drv_mfd_basetype.h"

typedef struct
{
    u32 frameNumber;
    u32 frameTimePictures;
    u32 picCodingType;
    u32 totalMbInFrame;
    u32 frameWidth; /* in macro blocks */
    u32 frameHeight;    /* in macro blocks */
    u32 timeCodeHours;
    u32 timeCodeMinutes;
    u32 timeCodeSeconds;

    //stanley mpeg-2 "resolution change"
    u32 resolutionChange;
    u32 preFrameWidth; /* in macro blocks */
    u32 preFrameHeight;    /* in macro blocks */
    
} DecFrameDesc;

#endif /* #ifndef MPEG2DECFRAMEDESC_H_DEFINED */
#endif // _HANTRO_M2V_EN_