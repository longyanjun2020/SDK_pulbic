/**
* @file mmi_mae_imagemaker_types.h
*
* IIMAGEMAKER Data Types
*
* @version $Id: mmi_mae_imagemaker_types.h $
*/
#ifndef __MMI_MAE_IMAGEMAKER_TYPES_H__
#define __MMI_MAE_IMAGEMAKER_TYPES_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_graphic_forward.h"

enum ImageEncType_e_
{
	IMG_ENC_TYPE_START = 0,
	IMG_ENC_TYPE_BMP = IMG_ENC_TYPE_START,
	IMG_ENC_TYPE_PALETTE_BMP,
	IMG_ENC_TYPE_JPG,
	IMG_ENC_TYPE_END
};

enum ImageMakerStatus_e_
{
	IMGMKR_STAT_ERROR,
	IMGMKR_STAT_DONE
};

enum ImgMkrRotate_e_
{
	IMGMKR_ANGLE_0 = 0,
	IMGMKR_ANGLE_90,
	IMGMKR_ANGLE_180,
	IMGMKR_ANGLE_270,
	IMGMKR_ANGLE_TOTAL
	//	IMGMKR_MIRROR
};

struct ImageMakerCBData_t_
{
	MAE_Ret     nRetCode;
	IBase      *pCaller;
	u32         nCallerInstID;
	IBase      *pObj;
	u32         nEncodeSize;   ///< for IIMAGEMAKER_Encode, the encoded size of output buffer
    MAE_WChar  *pFileName; // file URL
};

struct BmpPaletteData_t_
{
	RGBColor_t  *pPalette;
	u16         nCntPalette;
};

typedef union
{
	BmpPaletteData_t    tBmpPaletteData;
}ExtraImageData_u;

struct ImgMkrEncData_t_
{
	ImageEncType_e      nEncType;
	ExtraImageData_u    uImgData;
	RGBColor_t          nBGColor;     ///< background for tranparent color
};

#endif /* __MMI_MAE_IMAGEMAKER_TYPES_H__ */
