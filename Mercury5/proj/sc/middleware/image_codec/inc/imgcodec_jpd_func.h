#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION

//#pragma once

//For --------Montage Image Decoder-------------//
#ifndef _MW_IMAGEDECODER_H
#define _MW_IMAGEDECODER_H

#include "imgcodec_common.h"


// 1. FS handle
// 2. Decode Mode
// 3. Source Information (ROI Information)
// 4. Output Information
// 5. Return Information Buffer....

image_Errmsg MImage_DecodeImage(u8 Src, void *pDecode,void *pointer,u32 FileSize);
s32 CodecJPG_GetInfoHW(ImgFSFunc_st *pFfuncFS, Image_Info_t *pInfo);
void CodecJPG_LoaderHW(PIMGCODEC_CONTEXT pCodecCxt);
#endif //endif _MW_IMAGEDECODER_H
#endif

