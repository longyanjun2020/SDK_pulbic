#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION

#ifndef _IMGCODEC_SURFMGR_H_
#define _IMGCODEC_SURFMGR_H_

#include "imgcodec_common.h"

u8 imageCodec_isSurfVirtual(PMSSURFACE pSurf, u8 checkAlpha);
s32 imageCodec_checkSurf(PMSSURFACE pSurf);
PMSSURFACE imageCodec_createSurf(u32 width, u32 height, u32 format, u32 hasAlpha);
s32 imageCodec_destroySurf(PMSSURFACE pSurf);
s32 imageCodec_clearSurf(PMSSURFACE dstSurf, u32 x, u32 y, u32 w, u32 h);
s32 imageCodec_copySurf(PMSSURFACE dstSurf, PMSSURFACE srcSurf, s32 x, s32 y);
s32 imageCodec_blendSurf(PMSSURFACE dstSurf, PMSSURFACE srcSurf, s32 x, s32 y);
#endif
#endif

