#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION

//*****************************************************************************
//        Copyright (C) 2007.  MSTAR SEMICONDUCTOR INC. CONFIDENTIAL
//      All rights reserved.  No part of this program may be reproduced.
//
//    FILE	    : ms_AudioManager.h
//    VERSION   :
//    AUTHOR    : Henry Chang
//    USAGE     : Used for Audio Device(Application) Layer
//    DATE      : 2007.03.19
//    NOTE      :
//-----------------------------------------------------------------------------
//  Historical :
//-----------------------------------------------------------------------------
//    Date    | Author   | Err     | Modification
//------------+----------+---------+-------------------------------------------
//   19.03.07 | Henry    |         | Create
//------------+----------+---------+-------------------------------------------
//*****************************************************************************
#ifndef _IMGCODEC_COMMON_H_
#define _IMGCODEC_COMMON_H_

#include "mdl_imgcodec_main.h"
#include "imgcodec_surfmgr.h"
#include "imgcodec_util.h"

//******************************************************************************
//	D E F I N E S
//******************************************************************************
#undef  IMGCODEC_CLOSE_FILE_AFTER_FRAME_DONE
#undef  IMGCODEC_MALLOC_FAIL_TEST
#undef  IMGCODEC_MEM_OVERRUN_TEST
#define IMGCODEC_MEM_ALIGN_SIZE       (16)
#define IMGCODEC_MEM_GUARD_SIZE       (16)
#define IMGCODEC_MAX_SCALING_BUF_SIZE (600 * 1024)
#define MAX_OPENED_HANDLE 	          (20)
#define PQTUNING_MAGIC_NUM            (0x12345678)

#include "imgcodec_memmgr.h"
#define img_malloc(size)  imageCodec_allocateMem(size, IMAGE_MEMTYPE_SYS_DRAM_VIRTUAL)
#define img_free(ptr)     imageCodec_releaseMem(ptr)
#define img_imalloc(size) imageCodec_allocateMem(size, IMAGE_MEMTYPE_SYS_IRAM_PHYSICAL)
#define img_ifree(ptr)    imageCodec_releaseMem(ptr)
#define img_pmalloc(size) imageCodec_allocateMem(size, IMAGE_MEMTYPE_SYS_DRAM_PHYSICAL)
#define img_pfree(ptr)    imageCodec_releaseMem(ptr)

#include <string.h>
#define img_strcpy strcpy
#define img_strlen strlen
#define img_memcmp memcmp
#define img_memcpy memcpy
#define img_memset memset

#include "sys_traces.ho"
#include "cus_os.hc"
#define IMGCODEC_LV1 (_CUS1 | LEVEL_23)
#define IMGCODEC_LV2 (_CUS1 | LEVEL_24)
#define IMG_LEVEL    (_CUS2 | LEVEL_8 )
#ifdef __SDK_SIMULATION__
#define img_trace1(_format_, ...) vm_dbgTrace(IMGCODEC_LV1, (char *)(_format_), ##__VA_ARGS__)
#define img_trace2(_format_, ...) vm_dbgTrace(IMGCODEC_LV2, (char *)(_format_), ##__VA_ARGS__)
#define img_error1(_format_, ...) vm_dbgError(IMGCODEC_LV1, (char *)(_format_), ##__VA_ARGS__)
#define img_error2(_format_, ...) vm_dbgError(IMGCODEC_LV2, (char *)(_format_), ##__VA_ARGS__)
#define IMG_TRACE(_format_, ...)  vm_dbgTrace(IMG_LEVEL,    (char *)(_format_), ##__VA_ARGS__)
#define IMG_ERROR(_format_, ...)  vm_dbgError(IMG_LEVEL,    (char *)(_format_), ##__VA_ARGS__)
#define img_assert(expr)          //assert(expr)
#else
#define img_trace1(_format_, ...) imageCodec_dbgTrace(IMGCODEC_LV1, (char *)(_format_), ##__VA_ARGS__)
#define img_trace2(_format_, ...) imageCodec_dbgTrace(IMGCODEC_LV2, (char *)(_format_), ##__VA_ARGS__)
#define img_error1(_format_, ...) imageCodec_dbgError(IMGCODEC_LV1, (char *)(_format_), ##__VA_ARGS__)
#define img_error2(_format_, ...) imageCodec_dbgError(IMGCODEC_LV2, (char *)(_format_), ##__VA_ARGS__)
#define IMG_TRACE(_format_, ...)  imageCodec_dbgTrace(IMG_LEVEL,    (char *)(_format_), ##__VA_ARGS__)
#define IMG_ERROR(_format_, ...)  imageCodec_dbgError(IMG_LEVEL,    (char *)(_format_), ##__VA_ARGS__)
#define img_assert(expr)          //CUS_ASSERT(expr)
#endif

#define IMGCODEC_CHECK_ABORT(pDecoder) ((pDecoder) != 0 && \
                                       ((PIMGCODEC_CONTEXT)(pDecoder))->CheckAbort != 0 && \
                                       ((PIMGCODEC_CONTEXT)(pDecoder))->CheckAbort((u32)pDecoder))

//******************************************************************************
//	F U N C T I O N S
//******************************************************************************
typedef s32  (*fnDecode)(void *);
typedef s32  (*fnDecodeNext)(void *);
typedef s32  (*fnGetFrameInfo)(void *, u32 *, u32 *, u8 *);
typedef s32  (*fnFreeResource)(void**);

//******************************************************************************
//	S T R U C T S
//******************************************************************************
typedef struct _st_imgcodec_general_context_
{
    Image_Info_t        info;

    u8                  bIsFile;
    u16                *fileName;
    u32                 fileNameLen;
    u32                 filePos;

    Image_DispatchMode  dispatch;
    ImgRegion_t         ROI;
    Image_RotationAngle angle;
    u8                  bMirrorX;
    u8                  bMirrorY;
    u8                  bForceSW;
    u8                  bBootUp;
    Image_StereoMode    stereoMode;
    
    u8                  bLocked;
    u8                  bNeedCheckAbort;
    u8                  bNeedAbort;
    u32                 tickAbort;
    u32                 tickBegin;

    u32                 nextFrameDelay;
    u32                 nextFrameIndex;
    u8                  nextFrameValid;
    u8                  firstFrameValid;

#ifdef IMGCODEC_MEM_OVERRUN_TEST
    u8                 *tempOutRGB;
    u8                 *tempOutAlp;
    u8                 *backOutRGB;
    u8                 *backOutAlp;
#endif

    PMSSURFACE          pDstSurf;
    MSSURFACE           mmlDstSurf;
    void               *pPrivate;
    u32                 streamCacheSize;
    int                 cpuSpeedLevel;

    fnDecode            Decode;
    fnDecodeNext        DecodeNext;
    fnGetFrameInfo      GetFrameInfo;
    fnFreeResource      FreeResource;

    u32                 (*CheckAbort)(u32 nHandle);
    ImgFSFunc_st        funcFS;
    u32                 uPQTuningMagicNo;
}IMGCODEC_CONTEXT, *PIMGCODEC_CONTEXT;

extern u8 g_InternalDecodeAbort;
extern u8 g_EnterDecoding;

#endif//#ifndef _IMGCODEC_COMMON_H_
#endif

