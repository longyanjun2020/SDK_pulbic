/*
 * RawUtils.h
 *
 *  Created on: Nov 17, 2015
 *      Author: edward00.yang
 */
#ifndef __RawUtils__
#define __RawUtils__

#include "MsTypes.h"

void RawAlignToLSBorMSB(MS_BOOL bAlignLSB, unsigned int uShiftBits,
    unsigned int u4DataSize, unsigned short* pData);
int IntpU8(MS_U8 *p1, MS_U8 *p2, MS_U8 *pOut, MS_U32 u4Width, MS_U32 u4Heigh, MS_U32 u4W1, MS_U32 u4W2, MS_BOOL bRowLimited);
int IntpU16(MS_U16 *p1, MS_U16 *p2, MS_U16 *pOut, MS_U32 u4Width, MS_U32 u4Heigh, MS_U32 u4W1, MS_U32 u4W2, MS_BOOL bRowLimited);
int IntpU32(MS_U32 *p1, MS_U32 *p2, MS_U32 *pOut, MS_U32 u4Width, MS_U32 u4Heigh, MS_U32 u4W1, MS_U32 u4W2, MS_BOOL bRowLimited);
int RawGetBayerID(MS_U32 u4HWID, char *sID);

#endif /* __RawUtils__ */
