/**
 * @file mmi_mae_dib_types.h
 *
 * TODO: Add desctiptions here
 *
 * @version $Id: mmi_mae_dib_types.h $
 */
#ifndef __MMI_MAE_DIB_TYPES_H__
#define __MMI_MAE_DIB_TYPES_H__
#include "mmi_mae_common_def.h"

// Structure of Device Independent Bitmap structure
// This structure should sync with dirver's MSSURFACE
struct DIB_t_
{
	u32         nCaps;   //< no use here
	u16         nWidth;  //< Bitmap width
	u16         nHeight; //< Bitmap height
	u32         nBpp;    //< Bits per pixel
	u32         nStride; //< Bytes per row in bytes
	u32         nSize;   //< Data size in bytes
	u32         nFormat; //< Do NOT modify manually
	u32         nAddr;   //< Pointer to raw data, need type casting before using
	u8*         pAlphaMask;
    u8*         pExtraData;
	u32         nPreAlphaFormat; // the raw data is premultiplied alpha format or not
    u8          rbFieldInverse; // 0 : rgb, 1 : bgr
    u8          alphaBitsUsed;//0 : 8bits, 1 : 4bits
    u8			nGlobalAlhpa;//0~255,for dib format without alpha channel, use global alpha value instead.
    u8          reserve;
};

#endif /* __MMI_MAE_DIB_TYPES_H__ */
