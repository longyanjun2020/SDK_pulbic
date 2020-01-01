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
--  Abstract : MPEG2 decoder and PP pipeline support
--
--------------------------------------------------------------------------------
--
--  Version control information, please leave untouched.
--
--  $RCSfile: mpeg2hwd_pp_pipeline.h,v $
--  $Date: 2007/09/19 10:48:00 $
--  $Revision: 1.3 $
--
------------------------------------------------------------------------------*/
#ifdef _HANTRO_M2V_EN_
#ifndef MPEG2_PP_PIPELINE_H
#define MPEG2_PP_PIPELINE_H

#include "drv_mfd_decppif.h"

i32 mpeg2RegisterPP(const void *decInst, const void *ppInst,
                    void (*PPDecSetup) (const void *, const DecPpInterface *),
                    void (*PPDecPipelineEndCallback) (const void *),
                    void (*PPConfigQuery) (const void *, DecPpQuery *));

i32 mpeg2UnregisterPP(const void *decInst, const void *ppInst);

#endif /* #ifdef MPEG2_PP_PIPELINE_H */
#endif // _HANTRO_M2V_EN_