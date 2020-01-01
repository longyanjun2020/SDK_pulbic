#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION

/****************************************************************************/
/*  File    : imgcodec_bmp.h                                                */
/*--------------------------------------------------------------------------*/
/*  Scope   : standard bitmap extern header file                            */
/****************************************************************************/
#ifndef _IMGCODEC_BMP_H_
#define _IMGCODEC_BMP_H_

#include "imgcodec_common.h"

#define STANDARD_BMP_SIGNATURE  0x4D42
#define BMP_FILE_HEADER_SIZE    14

typedef struct _st_img_bmp_header_
{
    u16     Signature;
    u32     Size;
    u16     Reversed1;
    u16     Reversed2;
    u32     BitmapOffset;
}STDBMPFILEHEADER,*PSTDBMPFILEHEADER;

typedef struct _st_win2x_bmp_header_
{
    u32     HeaderSize;
    u16     Width;
    u16     Height;
    u16     Planes;
    u16     BitsPerPixel;
}WIN2XBMPHEADER, *PWIN2XBMPHEADER;

typedef struct _st_win3x_bmp_header_
{
    u32     HeaderSize;
    u32     Width;
    u32     Height;
    u16     Planes;
    u16     BitsPerPixel;
    u32     Compression;
    u32     SizeOfBmp;
    u32     HResolution;
    u32     VResolution;
    u32     ColorsUsed;
    u32     ColorsImportant;
}WIN3XBMPHEADER, *PWIN3XBMPHEADER;

typedef struct _st_win4x_bmp_header_
{
    u32     HeaderSize;
    u32     Width;
    u32     Height;
    u16     Planes;
    u16     BitsPerPixel;
    u32     Compression;
    u32     SizeOfBmp;
    u32     HResolution;
    u32     VResolution;
    u32     ColorsUsed;
    u32     ColorsImportant;
    u32     RedMask;
    u32     GreenMask;
    u32     BlueMask;
    u32     AlphaMask;
    u32     CSType;
    u32     RedX;
    u32     RedY;
    u32     RedZ;
    u32     GreenX;
    u32     GreenY;
    u32     GreenZ;
    u32     BlueX;
    u32     BlueY;
    u32     BlueZ;
    u32     GammaRed;
    u32     GammaGreen;
    u32     GammaBlue;
}WIN4XBMPHEADER, *PWIN4XBMPHEADER;


IMGCODEC_FORMAT CodecBMP_CheckBMP(u8* pBuff);
void CodecBMP_Loader(PIMGCODEC_CONTEXT context_op_p);
s32  CodecBMP_GetInfoEx(ImgFSFunc_st *pFfuncFS, Image_Info_t *pInfo);

#endif//_IMGCODEC_BMP_H_
#endif

