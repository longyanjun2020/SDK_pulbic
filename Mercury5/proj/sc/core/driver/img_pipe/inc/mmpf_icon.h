//==============================================================================
//
//  File        : mmpf_icon.h
//  Description : INCLUDE File for the Firmware ICON/ICO engine control  
//  Author      : Jerry Lai
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_ICON_H_
#define _MMPF_ICON_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_icon_inc.h"

/** @addtogroup MMPF_Icon
 *  @{
 */

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPF_Icon_SetAttributes(MMP_STICKER_ATTR *pBufAttr);
MMP_ERR MMPF_Icon_SetSemiTP(MMP_STICKER_ID StickerID, MMP_BOOL bSemiTPEn, MMP_ULONG ulWeight);
MMP_ERR MMPF_Icon_SetTransparent(MMP_STICKER_ID StickerID, MMP_BOOL bTranspActive, MMP_ULONG ulTranspColor);
MMP_ERR MMPF_Icon_SetEnable(MMP_STICKER_ID StickerID, MMP_BOOL bEnable);
MMP_ERR MMPF_Icon_UpdateAddress(MMP_STICKER_ID StickerID, MMP_ULONG ulBaseAddr);
MMP_ERR MMPF_Icon_LoadIndexColorTable(MMP_STICKER_ID StickerID, MMP_ICON_COLOR ubColor, MMP_USHORT* pLUT, MMP_USHORT usColorNum);
MMP_ERR MMPF_Icon_GetEnable(MMP_STICKER_ID StickerID, MMP_BOOL *bEnable);

/// @}

#endif //_MMPF_ICON_H_
