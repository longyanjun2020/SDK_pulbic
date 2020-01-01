/**
* @file mmi_wdg_overlayimage_priv.h
*/
#ifndef __MMI_WDG_OVERLAYIMAGE_PRIV_H__
#define __MMI_WDG_OVERLAYIMAGE_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mae_decoratorbase.h"
#include "mmi_mae_image.h"
#include "mmi_mae_bitmap.h"

#include "mmi_wdg_overlayimage.h"
#include "mmi_wdg_image_priv.h"
#include "mae_widget_common.h"

/*=============================================================*/
// type and define
/*=============================================================*/

typedef struct 
{
	ImageWidget_t DecBase;
    WdgOverlayIcon_t aOverlayIcon[OVERLAY_ICON_NUM];
} OverlayImageWidget_t;

/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret OverlayImageWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean OverlayImageWidget_DefHandleEvent(IDecorator *pIDecorator, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/

#endif //__MMI_WDG_OVERLAYIMAGE_PRIV_H__
/*=============================================================*/
// end of file
