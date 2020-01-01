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
--  Abstract : Definition of decContainer_t data structure
--
--------------------------------------------------------------------------------
--
--  Version control information, please leave untouched.
--
--  $RCSfile: h264hwd_container.h,v $
--  $Date: 2007/11/22 12:21:50 $
--  $Revision: 1.5 $
--
------------------------------------------------------------------------------*/

#ifndef H264HWD_CONTAINER_H
#define H264HWD_CONTAINER_H

/*------------------------------------------------------------------------------
    1. Include headers
------------------------------------------------------------------------------*/

#include "drv_mfd_basetype.h"
#include "drv_mfd_h264hwd_storage.h"
#include "drv_mfd_deccfg.h"
#include "drv_mfd_decppif.h"

/*------------------------------------------------------------------------------
    2. Module defines
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    3. Data types
------------------------------------------------------------------------------*/

#define H264DEC_UNINITIALIZED   0U
#define H264DEC_INITIALIZED     1U
#define H264DEC_BUFFER_EMPTY    2U
#define H264DEC_NEW_HEADERS     3U

/* asic interface */
typedef struct DecAsicBuffers
{
    u32 buff_status;
    MEMMAP_t mbCtrl;
    MEMMAP_t mv;
    MEMMAP_t intraPred;
    MEMMAP_t residual;
    MEMMAP_t *outBuffer;
    u32 refPicList[16];
    u32 maxRefFrm;
    u32 filterDisable;
    i32 chromaQpIndexOffset;
    u32 currentMB;
    u32 notCodedMask;
    u32 rlcWords;
    u32 picSizeInMbs;
    u32 wholePicConcealed;
    u32 disableOutWriting;
} DecAsicBuffers_t;

typedef struct decContainer
{
    const void *checksum;
    u32 decStat;
    u32 picNumber;
    u32 asicRunning;
    u32 rlcMode;
    u32 tryVlc;
    u32 reallocate;
    const u8 *pHwStreamStart;
    u32 hwStreamStartBus;
#ifdef _SIM_
    u32 hwStreamConsumed;
#endif
    u32 hwBitPos;
    u32 hwLength;
    u32 streamPosUpdated;
    u32 nalStartCode;
    u32 modeChange;
    u32 gapsCheckedForThis;
    u32 packetDecoded;
    u32 forceRlcMode;        /* by default stays 0, testing can set it to 1 for RLC mode */

    u32 h264Regs[DEC_X170_REGISTERS + 10];
    storage_t storage;       /* h264bsd storage */
    DecAsicBuffers_t asicBuff[1];
    const void *dwl;         /* DWL instance */
#ifdef _KMV_
    u32 m_KMV_type;
#endif
    struct
    {
        const void *ppInstance;
        void (*PPDecStart) (const void *, const DecPpInterface *);
        void (*PPDecWaitEnd) (const void *);
        void (*PPConfigQuery) (const void *, DecPpQuery *);
        DecPpInterface decPpIf;
        DecPpQuery ppInfo;
    } pp;

} decContainer_t;

/*------------------------------------------------------------------------------
    4. Function prototypes
------------------------------------------------------------------------------*/

#endif /* #ifdef H264HWD_CONTAINER_H */
