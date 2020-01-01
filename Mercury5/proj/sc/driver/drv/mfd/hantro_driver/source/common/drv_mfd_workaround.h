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
--  Abstract : Header file for stream decoding utilities
--
--------------------------------------------------------------------------------
--
--  Version control information, please leave untouched.
--
--  $RCSfile: workaround.h,v $
--  $Date: 2009/09/16 13:45:52 $
--  $Revision: 1.1 $
--
------------------------------------------------------------------------------*/

#ifndef WORKAROUND_H_DEFINED
#define WORKAROUND_H_DEFINED

#include "drv_mfd_basetype.h"

typedef struct workaround_s 
{
    u32 stuffing;
} workaround_t;

#ifndef HANTRO_TRUE
    #define HANTRO_TRUE     (1)
#endif /* HANTRO_TRUE */

#ifndef HANTRO_FALSE
    #define HANTRO_FALSE    (0)
#endif /* HANTRO_FALSE*/

void InitWorkarounds(u32 decMode, workaround_t *pWorkarounds );
void PrepareStuffingWorkaround( u8 *pDecOut, u32 vopWidth, u32 vopHeight );
u32  ProcessStuffingWorkaround( u8 * pDecOut, u8 * pRefPic, u32 vopWidth, 
                                u32 vopHeight );

#endif /* WORKAROUND_H_DEFINED */
