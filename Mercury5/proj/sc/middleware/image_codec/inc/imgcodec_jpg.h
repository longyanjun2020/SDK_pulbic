#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION

#ifndef _IMGCODEC_JPG_H_
#define _IMGCODEC_JPG_H_

IMGCODEC_FORMAT CodecJPG_CheckJPG(u8 *pBuff);
void CodecJPG_Loader(PIMGCODEC_CONTEXT context_op_p);
s32  CodecJPG_GetInfoEx(ImgFSFunc_st *pFfuncFS, Image_Info_t *pInfo);

#endif
#endif
