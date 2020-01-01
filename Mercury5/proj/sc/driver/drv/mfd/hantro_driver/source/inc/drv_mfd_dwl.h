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
--  Description : Sytem Wrapper Layer
--
------------------------------------------------------------------------------
--
--  Version control information, please leave untouched.
--
--  $RCSfile: dwl.h,v $
--  $Revision: 1.6 $
--  $Date: 2007/11/22 10:34:37 $
--
------------------------------------------------------------------------------*/
#ifndef __DWL_H__
#define __DWL_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "drv_mfd_basetype.h"
#include "drv_mfd_decapicommon.h"

#define DWL_OK                      0
#define DWL_ERROR                  -1

#define DWL_HW_WAIT_OK              DWL_OK
#define DWL_HW_WAIT_ERROR           DWL_ERROR
#define DWL_HW_WAIT_TIMEOUT         1

#define DWL_CLIENT_TYPE_H264_DEC         1U
#define DWL_CLIENT_TYPE_MPEG4_DEC        2U
#define DWL_CLIENT_TYPE_JPEG_DEC         3U
#define DWL_CLIENT_TYPE_PP               4U
#define DWL_CLIENT_TYPE_VC1_DEC          5U
#define DWL_CLIENT_TYPE_MPEG2_DEC        6U

#include "drv_mfd_udma_share.h"
#if 0
    //move this structure to udma_share.h
    /* Linear memory area descriptor */
    typedef struct MEMMAP
    {
        u8  *miuPointer;
        u32 miuAddress;
        u32 size;
    } MEMMAP_t;
#endif

#if 0
    /* Linear memory area descriptor */
    typedef struct DWLLinearMem
    {
        u32 *virtualAddress;
        u32 busAddress;
        u32 size;
    } MEMMAP_t;
#endif

    /* DWLInitParam is used to pass parameters when initializing the DWL */
    typedef struct DWLInitParam
    {
        u32 clientType;
    } DWLInitParam_t;

    /* Hardware configuration description */
    typedef struct DWLHwConfig
    {
        u32 maxDecPicWidth;  /* Maximum video decoding width supported  */
        u32 maxPpOutPicWidth;   /* Maximum output width of Post-Processor */
        u32 h264Support;     /* HW supports h.264 */
        u32 jpegSupport;     /* HW supports JPEG */
        u32 mpeg4Support;    /* HW supports MPEG-4 */
        u32 vc1Support;      /* HW supports VC-1 Simple */
        u32 mpeg2Support;    /* HW supports MPEG-2 */
        u32 ppSupport;       /* HW supports post-processor */
        u32 ppConfig;        /* HW post-processor functions bitmask */
        u32 sorensonSparkSupport;   /* HW supports Sorenson Spark */
    } DWLHwConfig_t;

/* HW ID retriving, static implementation */
    u32 DWLReadAsicID(void);

/* HW configuration retrieving, static implementation */
    void DWLReadAsicConfig(DWLHwConfig_t * pHwCfg);

/* DWL initilaization and release */
    const void *DWLInit(DWLInitParam_t * param);
    i32 DWLRelease(const void *instance);

/* HW sharing */
    i32 DWLReserveHw(const void *instance);
    void DWLReleaseHw(const void *instance);

/* Frame buffers memory */
    i32 DWLMallocRefFrm(const void *instance, u32 size, MEMMAP_t * info);
    void DWLFreeRefFrm(const void *instance, MEMMAP_t * info);

/* SW/HW shared memory */
    //move this prototype to udma_share.h
    //i32 M4VD_MMAPMalloc(u32 size, MEMMAP_t * info);
    i32 DWLMallocLinear(const void *instance, u32 size, MEMMAP_t * info);
    void DWLFreeLinear(const void *instance, MEMMAP_t * info);

/* D-Cache coherence */
    void DWLDCacheRangeFlush(const void *instance, MEMMAP_t * info);  /* NOT in use */
    void DWLDCacheRangeRefresh(const void *instance, MEMMAP_t * info);    /* NOT in use */

/* Register access */
    void DWLWriteRegBatch(const void *instance, const u32 * table, u32 start, u32 end); /* NOT in use */

    void DWLWriteReg(const void *instance, u32 offset, u32 value);
    u32 DWLReadReg(const void *instance, u32 offset);

    void DWLWriteRegAll(const void *instance, const u32 * table, u32 size); /* NOT in use */
    void DWLReadRegAll(const void *instance, u32 * table, u32 size);    /* NOT in use */

/* HW starting/stopping */
    void DWLEnableHW(const void *instance, u32 offset, u32 value);
    void DWLDisableHW(const void *instance, u32 offset, u32 value);

/* HW synchronization */
    i32 DWLWaitHwReady(const void *instance, u32 timeout);

/* SW/SW shared memory */
    //void *DWLmalloc(u32 n);
    void DWLfree(void *p);
    void *DWLcalloc(u32 n, u32 s);
    void *DWLmemcpy(void *d, const void *s, u32 n);
    void *DWLmemset(void *d, i32 c, u32 n);

#ifdef __cplusplus
}
#endif

#endif                       /* __DWL_H__ */
