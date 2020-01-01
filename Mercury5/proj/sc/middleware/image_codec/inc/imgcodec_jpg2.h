#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION

#ifndef _IMGCODEC_JPG2_H_
#define _IMGCODEC_JPG2_H_

IMGCODEC_FORMAT CodecJPG2_CheckJPG(u8 *pBuff);
void CodecJPG2_Loader(PIMGCODEC_CONTEXT context_op_p);
s32  CodecJPG2_GetInfoEx(ImgFSFunc_st *pFfuncFS, Image_Info_t *pInfo);

#endif
#endif
