#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION

/****************************************************************************/
/*  File    : imgcodec_wapbmp.h                                             */
/*--------------------------------------------------------------------------*/
/*  Scope   : png extern header file                                        */
/****************************************************************************/
#ifndef _IMGCODEC_WAPBMP_H_
#define _IMGCODEC_WAPBMP_H_

#include "imgcodec_common.h"

IMGCODEC_FORMAT CodecWAPBMP_CheckWAPBMP(u8* pBuff);
void CodecWAPBMP_Loader(PIMGCODEC_CONTEXT context_op);
s32  CodecWAPBMP_GetInfoEx(ImgFSFunc_st *pFfuncFS, Image_Info_t *pInfo);

#endif//_IMGCODEC_WAVECOM_H_
#endif

