/**
* @file mmi_wdg_image_priv.h
*
* @version $Id: mmi_wdg_image_priv.h 34664 2009-06-29 14:37:52Z bill.pan $
*/
#ifndef __MMI_WDG_IMAGE_PRIV_H__
#define __MMI_WDG_IMAGE_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mae_decoratorbase.h"
#include "mmi_mae_image.h"
#include "mmi_mae_bitmap.h"

#include "mmi_wdg_image.h"
#include "mae_widget_common.h"

/*=============================================================*/
// type and define
/*=============================================================*/
#define _IMGWDG_SUPPORT_PARTIAL_DECODE_

#define IMGWDG_DEF_IMG_ID  COMMON_IMG_PHOTO_ALL; // should move this default value to cus for customization

typedef u8 ImgWdgBool_t;

typedef struct{
	u32 Width;
	u32 Interval;
}SingleFrameAnimInfo_t;

/*
(a)Partial decode:

                 SrcW
        |-----------------------|
        |                       |           DecW
        |          SRegW        |        |------------|
        |        |------|       |        |     DRegW  |
   srcH |        |      |       |        |    |--|    |DecH
        |        |      |SRegH  |   ==>  |    |--|DRegH
        |        |------|       |        |            |
        |                       |        |------------|
        |                       |
        |-----------------------|


(b)Full decode:

                 SrcW=SRegW
        |-----------------------|
        |                       |           DecW=DRegW
        |                       |        |------------|
        |                       |        |            |
  SrcH  |                       |        |            |DecH=DRegH
  =SRegH|                       |   ==>  |            |
        |                       |        |            |
        |                       |        |------------|
        |                       |
        |-----------------------|
*/

typedef struct {
	DecoratorEx_t      DecBase;    ///< Use DecoratorEx_t as base structure and support border/padding/background
	ModelListener_t    MdlLsn;     ///< the interface-model listener
	IImage            *pImage;     ///< The source image
	IBitmap           *pBitmap;    ///< The source bitmap

	IImage            *pDefImage;  ///< The default image

	u32                nCurrentFrame;
	ImgWdgAutoFit_t    AutoFit;

	SingleFrameAnimInfo_t  SglFrmAnimInfo;

	u32                nDefImageID;
	MAE_WChar *pwLinkAddr;

#ifdef __TOUCH_SCREEN_MMI__
	ITouchSrv *pITouchSrv;  //< Touch service
#endif //__TOUCH_SCREEN_MMI__

#if defined(__G3D_MMI__)	
    u32		nRawDataID;			///< raw data (texture) ID for image
#endif

#ifdef _IMGWDG_SUPPORT_PARTIAL_DECODE_
	u32                nDecWidth;
	u32                nDecHeight;
	u32       bPartialDec : 1;
#endif
	u32       bSingleFrameAnim : 1;
	u32       bAnimating : 1;
	u32       bUpScale : 1;

	u32       bUseDefImage : 1;
	u32       bLinked : 1;
	u32       bTouched : 1;
	u32       bNeedAnimate : 1;
    u32       bIsInActive : 1;
    u32       bAnimateOnce : 1;
    u32       bKeepBuffer : 1;  
    		u32       bCanUsePalette : 1;  
    u32       ImgAlign : 8;   ///< Image alignment
} ImageWidget_t;

/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret ImageWidget_New(MAE_ClsId ClsID, void **ppObj);

MAE_Ret ImageWidgetStrucCtor(ImageWidget_t *pThis);
void ImageWidgetStrucDtor(ImageWidget_t *pThis);
void ImageWidget_DefDraw(IDecorator*, IDispCanvas*, s32, s32);
boolean ImageWidget_DefHandleEvent(IDecorator *pIDecorator, MAE_EventId evt, u32 P1, u32 P2);

IWidget *ImageWidget_CreateForWnd(HWIN hWin, Pos_t *pPos, WidgetSize_t *pSize, u16 nWidgetID, ImageStyle_e eStyle, WdgImageConfigData_t *pData, WdgCreateFnParam pFnCreate);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/

#endif //__MMI_WDG_IMAGE_PRIV_H__
/*=============================================================*/
// end of file
