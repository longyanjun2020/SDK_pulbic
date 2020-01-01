#ifndef __M_UTILITY_IMGPORTING_H__
#define __M_UTILITY_IMGPORTING_H__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mgl_utility_common.h"

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
typedef struct MGL_PORTING_DIB_t_tag
{
	mgl_u16         nWidth;  	//< Bitmap width
	mgl_u16         nHeight; 	//< Bitmap height
	mgl_u32         nBpp;    		//< Bits per pixel
	mgl_u32         nStride; 	//< Bytes per row in bytes
	mgl_u32         nFormat; 	//< Do NOT modify manually
	mgl_u32         nAddr;   	//< Pointer to raw data, need type casting before using
	mgl_u8*         pAlphaMask;
}MGL_PORTING_DIB_t_;

typedef enum MGL_COLOR_FORMAT_Tag
{
	MGL_PORTING_COLORFORMAT_RGB16_565,
	MGL_PORTING_COLORFORMAT_RGB32_8888,
	MGL_PORTING_COLORFORMAT_UNKNOWN,
}MGL_COLOR_FORMAT;

typedef enum MGL_DISPMODE_Tag
{
	MGL_PORTING_DISPMODE_LANDSCAPE_90,
	MGL_PORTING_DISPMODE_LANDSCAPE_270,
	MGL_PORTIMG_DISPMODE_UNKNOWN,
}MGL_DISPMODE;

/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
MGL_COLOR_FORMAT MGL_PORTING_ReMappingColorFormat(mgl_u32 format);
MGL_DISPMODE MGL_PORTING_ReMappingDispMode(mgl_u8 dispMode);
mgl_boolean MGL_PORTING_GetDibFromImageID(mgl_u32 imageID, mgl_void **ppBitmap, mgl_void *pDibDst);
mgl_boolean  MGL_PORTING_GetDibFromRawData(mgl_void *pRawData, mgl_void *pDibDst);
mgl_void MGL_PORTING_RELEASEIF(mgl_void *pObj);
mgl_void MGL_PORTING_LOG(mgl_s8 *x, ...);

#endif    /* __M_UTILITY_IMGPORTING_H__ */
