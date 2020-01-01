/**
* @file 	mae_wdgbackground.h
* @brief   This file is the header file for implementation of background color/image for widget
*
* @version $Id: mae_wdgbackground.h 13590 2008-08-26 06:06:43Z paul.ouyang $
*/
#ifndef __MAE_WDGBACKGROUND_H__
#define __MAE_WDGBACKGROUND_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_image.h"
#include "mmi_mae_bitmap.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct WdgItemBG_TAG {
	RGBColor_t	color;         ///< Item BG color.
	IBase      *pImgObj;       /*!< An IImage object or an IBitmap object.
							   Please Don't assign it directly, should set it via WdgItemBG_SetImage() function.
							   */
	u8          nImgType;      ///< Background image type. An IImage or IBitmap or None.
	//u8          nAlignment;    ///< Background image alignment.
#if defined(__G3D_MMI__)
    u32	nBgRawDataId;
#endif
} WdgItemBG_t;

enum WdgItemBGType_TAG
{
	WDGITEMBG_TYPE_NONE = 0,
	WDGITEMBG_TYPE_IMAGE,
	WDGITEMBG_TYPE_BITMAP,
	WDGITEMBG_TYPE_END
};

/*=============================================================*/
// functions
/*=============================================================*/
/**
* To draw the color and image in WdgItemBG_t structure on a specific rectangle.
*
*/
void WdgItemBG_Draw(WidgetBase_t *pThis, WdgItemBG_t *pItemBG, IDisplay *pIDisplay, const Rect_t *pRectToDraw, boolean b3D);

/**
* To change the image objec in WdgItemBG_t structure.
*/
MAERet_t WdgItemBG_SetImage(WidgetBase_t *pThis, WdgItemBG_t *pItemBG, IBase *pImageObj, IBase *pOwner);


/**
* Release macro function
*/
#define RELEASE_ITEMBG(_pWdgItemBg, _pOwner) \
	do {\
		if ((_pWdgItemBg) && ((_pWdgItemBg)->pImgObj))\
		{\
			RELEASE((_pWdgItemBg)->pImgObj, _pOwner);\
		}\
	}while(0)


#endif //__MAE_WDGBACKGROUND_H__
/*=============================================================*/
// end of file
