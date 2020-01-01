/**
* @file     mmi_wdg_animimage_priv.h
* @version $Id: mmi_wdg_animimage_priv.h $
* @brief   
*
*/
#ifndef __MMI_WDG_ANIMIMAGE_PRIV_H__
#define __MMI_WDG_ANIMIMAGE_PRIV_H__


/*=============================================================*/
// include
/*=============================================================*/
#include "mae_widgetbase.h"
#include "mae_widget_common.h"

/*=============================================================*/
// type and define
/*=============================================================*/
#define DEFAULT_ANIMIMAGE_TIME 100

typedef struct {
    WidgetBaseEx_t        WdgBase;
    u32                        nFrameIndex;
    u32                        nTotalFrame;
    IBitmap                    *pBmp;        ///< a image widget
    ImageSize_t     tImgSize;
    WidgetSize_t    tBlockSize;
    Pos_t               tRCInfo;   //Row: x Col: y
    Pos_t               *pItemPos;
    s32                 nAnimTime;
    IWidget         *pImgWdg;
	boolean        bDisplayVisible;
} AnimImageWidget_t;


/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret AnimImageWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean AnimImageWidget_DefHandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret _WdgAnimImageConstructor(AnimImageWidget_t *pThis);
void _WdgAnimImageDestructor(AnimImageWidget_t *pThis);
//get size
static void AnimImageWidget_GetSize(IWidget *pIWidget, WidgetSize_t *pSize);
//set size
static void AnimImageWidget_SetSize(IWidget *pIWidget, WidgetSize_t *pSize);
//Draw function
static void AnimImageWidget_Draw(IWidget *pIWidget, IDispCanvas *pIDispCanvas, s32 x, s32 y);

#endif //__MMI_WDG_ANIMIMAGE_PRIV_H__
/*=============================================================*/

