/**
* @file BitStreamItf.h
*
* This header file defines the interfaces of double link list.
*
*/

#ifndef __BITSTREAMITF_H__
#define __BITSTREAMITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void BitStream_SetBit(u16 uPos, u8 *pData, u16 uDataSize);
bool BitStream_GetBit(u16 uPos, u8 *pData, u16 uDataSize);
void BitStream_ClearBit(u16 uPos, u8 *pData, u16 uDataSize);
void BitStream_AndBitStream(u8 *pSrc1, u8 *pSrc2, u8 *pDest, u16 uDataSize);
void BitStream_OrBitStream(u8 *pSrc1, u8 *pSrc2, u8 *pDest, u16 uDataSize);
void BitStream_ComplBitStream(u8 *pSrc1, u8 *pSrc2, u8 *pDest, u16 uDataSize);
u32 BitStream_GetSetBitsNum(u8 *pData, u16 uDataSize);

#endif //__BITSTREAMITF_H__
