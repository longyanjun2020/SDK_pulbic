#ifndef _MC_H_
#define _MC_H_

#include "swvenc_deftypes.h"
#include "swvenc_venc_debug.h"

void CopyBlockFrom(uint8* src,int16* dest,int jsize);

void CopyBlockBack      (int16* src, uint8* dest,           int jsize);
void CopyBlockBackWithDC(int16* src, uint8* dest, int16 dc, int jsize);

//void CopyBlockToBlock(uint8* src,uint8* dest,int jsize);

void CopyDiffBlockBack(int16* diff, uint8* dest, int jsize);
void CopyDiffBlockBack_DcOnly(int16 dc, uint8* dest, int jsize);

void HalfPointYMb_H(uint8 *pDst, uint8 *pSrc, int nStrideDst, int nStrideSrc, int nXStart, int nXEnd);
void HalfPointYMb_V(uint8 *pDst, uint8 *pSrc, int nStrideDst, int nStrideSrc, int nYStart, int nYEnd);
void HalfPointYMb_HV(uint8 *pDst, uint8 *pSrc, int nStrideDst, int nStrideSrc, int nYStart, int nYEnd, int nXStart, int nXEnd);

extern void (*const CopyDiffBlockFromHpel[4])(uint8*,uint8*,uint8*,int16*,int,int,int);    // Y only uses [0]

// Extern
extern int g_nOneMinusRounding, g_nTwoMinusRounding;

#endif
