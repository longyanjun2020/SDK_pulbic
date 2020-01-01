#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION

//For --------Montage Image Decoder-------------//
#ifndef _MW_JPGDECODER_H
#define _MW_JPGDECODER_H

#include "imgcodec_jpdBaiscFun.h"
#include "imgcodec_jpdHeader.h"
#include "imgcodec_jpd_func.h"

typedef enum
{
    JPGSrc_FullRead = 0,
    JPGSrc_PartialRead,
} JPGSrcMode_e;

typedef enum
{
    NO_TIME_OUT = 0,
    LOW_BUF_TIME_OUT,
    HIGH_BUF_TIME_OUT,
    DECODE_DONE_TIME_OUT,
    SCL_DONE_TIME_OUT,
} JPGIsrTimeOut_e;

typedef enum
{
    JPGOut_FrameMode = 0,
    JPGOut_HWRowMode,
    JPGOut_SWRowMode,
} JPGOutMode_e;

#define JPGMdlPing      0
#define JPGMdlPong      1

typedef struct
{
    u8 *pPingPtr;
    u8 *pPongPtr;
    u32 PingPongSize;
    u8 PingPongFlag;
} JPGMdlPingPong_t;

image_Errmsg MwJpgDecode(ImageFSFunc_t *pImgFSFun, u16 Mode, ImageROIRegion_t *ROIRegion, ImageOutCfg_t *OutCfg, void *RetPtr);
image_Errmsg MwJpdMain(u32 nhandle, JPD_Header *pJPDHeader, ImageFSFunc_t *pImgFSFun, JpgMemory_t *pJpgMem, ImageROIRegion_t *ROIRegion, ImageOutCfg_t *OutCfg);
s32 CodecJPG_DecodeHW(void *ptr);
image_Errmsg MwJpdDataStrcTrans(PIMGCODEC_CONTEXT pDecoder, ImageROIRegion_t *ROIRegion, ImageOutCfg_t *OutCfg);
void JPD_HW_Reset(void);
u32 MdlJpdGetJPDOutputSize(JPD_Header *pJPDHeader, ImageROIRegion_t *ROIRegion, ImageOutCfg_t *OutCfg);
#endif //endif _MW_JPGDECODER_H
#endif

