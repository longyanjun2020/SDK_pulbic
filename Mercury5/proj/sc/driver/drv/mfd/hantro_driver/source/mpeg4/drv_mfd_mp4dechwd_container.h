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
--  $RCSfile: mp4dechwd_container.h,v $
--  $Date: 2007/11/26 10:06:47 $
--  $Revision: 1.6 $
--
------------------------------------------------------------------------------*/

#ifndef _DECCONTAINER_H_
#define _DECCONTAINER_H_

#include "drv_mfd_basetype.h"
#include "drv_mfd_mp4dechwd_vopdesc.h"
#include "drv_mfd_mp4dechwd_mbsetdesc.h"
#include "drv_mfd_mp4dechwd_strmdesc.h"
#include "drv_mfd_mp4dechwd_mbdesc.h"
#include "drv_mfd_mp4dechwd_hdrs.h"
#include "drv_mfd_mp4dechwd_svdesc.h"
#include "drv_mfd_mp4dechwd_storage.h"
#include "drv_mfd_mp4dechwd_mvstorage.h"
#include "drv_mfd_mp4decapihwd_storage.h"
#include "drv_mfd_mp4deccfg.h"
#include "drv_mfd_deccfg.h"
#include "drv_mfd_decppif.h"

typedef struct DecContainer_t
{
    u32 mp4Regs[DEC_X170_REGISTERS];
    DecVopDesc VopDesc;         /* VOP description */
    DecMbSetDesc MbSetDesc;     /* Mb set descriptor */
    DecMBDesc MBDesc[MP4API_DEC_MBS];
    DecStrmDesc StrmDesc;
    DecStrmStorage StrmStorage; /* StrmDec storage */
    DecHdrs Hdrs;
    DecHdrs tmpHdrs;
    DecSvDesc SvDesc;   /* Short video descriptor */
    DecApiStorage ApiStorage;  /* Api's internal data storage */
    DecPpInterface ppControl;
    DecPpQuery ppConfigQuery; /* Decoder asks pp info about setup, info stored here */
    u32 ppStatus;
    u32 asicRunning;
    u32 rlcMode;
    u32 mbErrorConceal;
    const void *dwl;
    u32 packedMode;
    u32 drop_broken_b;

    const void *ppInstance;
    void (*PPRun) (const void *, DecPpInterface *);
    void (*PPEndCallback) (const void *);
    void  (*PPConfigQuery)(const void *, DecPpQuery *);

} DecContainer;

#endif /* _DECCONTAINER_H_ */
