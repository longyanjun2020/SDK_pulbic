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
--  $RCSfile: mpeg2hwd_container.h,v $
--  $Date: 2007/11/20 08:45:36 $
--  $Revision: 1.7 $
--
------------------------------------------------------------------------------*/
#ifdef _HANTRO_M2V_EN_
#ifndef _MPEG2DECCONTAINER_H_
#define _MPEG2DECCONTAINER_H_

#include "drv_mfd_basetype.h"
#include "drv_mfd_mpeg2hwd_framedesc.h"
#include "drv_mfd_mpeg2hwd_mbsetdesc.h"
#include "drv_mfd_mpeg2hwd_strmdesc.h"
#include "drv_mfd_mpeg2hwd_hdrs.h"
#include "drv_mfd_mpeg2hwd_storage.h"
#include "drv_mfd_mpeg2hwd_apistorage.h"
#include "drv_mfd_mpeg2hwd_cfg.h"
#include "drv_mfd_deccfg.h"
#include "drv_mfd_decppif.h"

typedef struct
{
    u32 mpeg2Regs[DEC_X170_REGISTERS];
    DecFrameDesc FrameDesc; /* Frame description */
    DecMbSetDesc MbSetDesc; /* Mb set descriptor */
    DecStrmDesc StrmDesc;
    DecStrmStorage StrmStorage; /* StrmDec storage */
    DecHdrs Hdrs;
    DecHdrs tmpHdrs;    /* for decoding of repeated headers */
    DecApiStorage ApiStorage;   /* Api's internal data storage */
    DecPpInterface ppControl;
    DecPpQuery ppConfigQuery;   /* Decoder asks pp info about setup, info stored here */
    u32 ppStatus;
    u32 asicRunning;
    u32 mbErrorConceal;
    const void *dwl;
    u32 drop_broken_b;

    const void *ppInstance;
    void (*PPRun) (const void *, DecPpInterface *);
    void (*PPEndCallback) (const void *);
    void (*PPConfigQuery) (const void *, DecPpQuery *);

    u32 resChgID;
    u32 pID;
} DecContainer;

#endif /* #ifndef _MPEG2DECCONTAINER_H_ */
#endif // _HANTRO_M2V_EN_