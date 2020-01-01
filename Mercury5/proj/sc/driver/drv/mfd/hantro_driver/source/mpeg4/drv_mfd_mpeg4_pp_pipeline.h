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
--  Abstract : MPEG4 decoder and PP pipeline support
--
--------------------------------------------------------------------------------
--
--  Version control information, please leave untouched.
--
--  $RCSfile: mpeg4_pp_pipeline.h,v $
--  $Date: 2007/06/28 11:41:27 $
--  $Revision: 1.2 $
--
------------------------------------------------------------------------------*/

#ifndef MPEG4_PP_PIPELINE_H
#define MPEG4_PP_PIPELINE_H

#include "drv_mfd_decppif.h"

i32 mpeg4RegisterPP(const void *decInst, const void *ppInst,
                    void (*PPDecSetup) (const void *, const DecPpInterface *),
                    void (*PPDecPipelineEndCallback) (const void *),
                    void (*PPConfigQuery)(const void *, DecPpQuery *));

i32 mpeg4UnregisterPP(const void *decInst, const void *ppInst);

#endif /* #ifdef MPEG4_PP_PIPELINE_H */
