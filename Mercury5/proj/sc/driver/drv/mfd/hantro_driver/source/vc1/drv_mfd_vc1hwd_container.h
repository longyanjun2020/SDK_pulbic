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
--  Description : Decoder container
--
--------------------------------------------------------------------------------
--
--  Version control information, please leave untouched.
--
--  $RCSfile: vc1hwd_container.h,v $
--  $Revision: 1.4 $
--  $Date: 2007/12/13 13:27:44 $
--
------------------------------------------------------------------------------*/

#ifndef VC1HWD_CONTAINER_H
#define VC1HWD_CONTAINER_H

/*------------------------------------------------------------------------------
    Include headers
------------------------------------------------------------------------------*/

#include "drv_mfd_vc1hwd_storage.h"
#include "drv_mfd_deccfg.h"
#include "drv_mfd_decppif.h"

/*------------------------------------------------------------------------------
    Module defines
------------------------------------------------------------------------------*/

/* String length for tracing */
#define VC1DEC_TRACE_STR_LEN 100

/*------------------------------------------------------------------------------
    Data types
------------------------------------------------------------------------------*/

typedef struct
{
    enum {
        VC1DEC_UNINITIALIZED,
        VC1DEC_INITIALIZED,
        VC1DEC_RESOURCES_ALLOCATED
    } decStat;

    swStrmStorage_t storage;
#ifdef VC1DEC_TRACE
    char str[VC1DEC_TRACE_STR_LEN];
#endif
    u32 picNumber;
    u32 asicRunning;
    u32 vc1Regs[DEC_X170_REGISTERS];

    u32 maxWidthHw;

    DecPpInterface ppControl;
    DecPpQuery ppConfigQuery; /* Decoder asks pp info about setup, 
                                 info stored here */
    u32 ppStatus;

    MEMMAP_t bitPlaneCtrl;
    MEMMAP_t directMvs;
    const void *dwl;    /* DWL instance */
    const void *ppInstance;
    void (*PPRun)(const void *, DecPpInterface *);
    void (*PPEndCallback) (const void *);
    void  (*PPConfigQuery)(const void *, DecPpQuery *);
} decContainer_t;

/*------------------------------------------------------------------------------
    Function prototypes
------------------------------------------------------------------------------*/

#endif /* #ifndef VC1HWD_CONTAINER_H */

