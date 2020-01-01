#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION

/****************************************************************************/
/*  File    : imgcodec_png.h                                                */
/*--------------------------------------------------------------------------*/
/*  Scope   : png extern header file                                        */
/****************************************************************************/
#ifndef _IMGCODEC_PNG_H_
#define _IMGCODEC_PNG_H_

#include "imgcodec_common.h"
//===================================================================
// CONSTANTS
// These describe the color_type field in png_info.
// color type masks
#define PNG_COLOR_MASK_PALETTE      1
#define PNG_COLOR_MASK_COLOR        2
#define PNG_COLOR_MASK_ALPHA        4

// color types.  Note that not all combinations are legal
#define PNG_COLOR_TYPE_GRAY         0
#define PNG_COLOR_TYPE_PALETTE      (PNG_COLOR_MASK_COLOR | PNG_COLOR_MASK_PALETTE)
#define PNG_COLOR_TYPE_RGB          (PNG_COLOR_MASK_COLOR)
#define PNG_COLOR_TYPE_RGB_ALPHA    (PNG_COLOR_MASK_COLOR | PNG_COLOR_MASK_ALPHA)
#define PNG_COLOR_TYPE_GRAY_ALPHA   (PNG_COLOR_MASK_ALPHA)
// aliases
#define PNG_COLOR_TYPE_RGBA         PNG_COLOR_TYPE_RGB_ALPHA
#define PNG_COLOR_TYPE_GA           PNG_COLOR_TYPE_GRAY_ALPHA


//===================================================================
// API
IMGCODEC_FORMAT CodecPNG_CheckPNG(u8*   pBuff);
void CodecPNG_Loader(PIMGCODEC_CONTEXT context_op_p);
s32 CodecPNG_GetInfoEx(ImgFSFunc_st *pFfuncFS, Image_Info_t *pInfo);
s32 CodecPNG_DecodeFirstFrame(PIMGCODEC_CONTEXT pDecoder);
s32 CodecAPNG_DecodeFirstFrame(PIMGCODEC_CONTEXT pDecoder);

s32 CodecPNG_DecodeDispatch(PIMGCODEC_CONTEXT pDecoder);
u8 CodecPNG_SupportAPNG(void);

#endif //_IMGCODEC_PNG_H_
#endif

