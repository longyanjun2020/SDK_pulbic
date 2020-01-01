/**
* @file	mmi_wdg_switchicon.h
* @version	$Id: mmi_wdg_switchicon.h 25372 2009-03-11 08:10:22Z mark.yang $
*
* @brief	This is a private header file for SwitchIcon widget implementation.
*/
#ifndef __MMI_WDG_SWITCHICON_PRIV_H__
#define __MMI_WDG_SWITCHICON_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_wdg_switchicon.h"
#include "mmi_mae_image.h"
#include "mmi_mae_bitmap.h"
#include "mae_widgetbase.h"

/*=============================================================*/
// type and define
/*=============================================================*/
enum
{
    SWITCHICON_WDG_RELOAD_FLAG_START = 0,
    SWITCHICON_WDG_RELOAD_FLAG_ACTIVEICON = SWITCHICON_WDG_RELOAD_FLAG_START,   ///< ACTIVE ICON
	SWITCHICON_WDG_RELOAD_FLAG_INACTIVEICON,
    SWITCHICON_WDG_RELOAD_FLAG_END
};


/**
* The structure for implementation of SwitchIcon widget.
*/
typedef struct {
	WidgetBaseEx_t		WdgBase;			///< Using WidgetBaseEx_t as base structure.
	ModelListener_t 	MdlLsn;				///< Model listener for listening the data model change.
	IWidget				*pIImageWdg;		///< Using a Bitmap widget to display icon.
	IImage				*pActiveImage;		///< A IBitmap object for active icon to display.
	IImage				*pInactiveImage;	///< A IBitmap object for inactive icon to display.
#ifdef __TOUCH_SCREEN_MMI__
	ITouchSrv *pITouchSrv;
	boolean    bTouchPressed;
#endif //__TOUCH_SCREEN_MMI__
	u32					nIconStyle;
	u16 nReloadRCFlag;		///< the flag record which rc property has been modified outside, those are not reload
} SwitchIconWidget_t;

/**
* Flag Mask
*/
#define SWITCHICON_WDG_RELOAD_MASK_ACTIVEICON           (1<<SWITCHICON_WDG_RELOAD_FLAG_ACTIVEICON)
#define SWITCHICON_WDG_RELOAD_MASK_INACTIVEICON         (1<<SWITCHICON_WDG_RELOAD_FLAG_INACTIVEICON)

/**
* Macro to get flag value
*/
#define SWITCHICON_WDG_ACTIVEICON_IS_MODIFIED(_pWdg) \
    (boolean)(((_pWdg)->nReloadRCFlag&SWITCHICON_WDG_RELOAD_MASK_ACTIVEICON)>>SWITCHICON_WDG_RELOAD_FLAG_ACTIVEICON)
#define SWITCHICON_WDG_INACTIVEICON_IS_MODIFIED(_pWdg) \
    (boolean)(((_pWdg)->nReloadRCFlag&SWITCHICON_WDG_RELOAD_MASK_INACTIVEICON)>>SWITCHICON_WDG_RELOAD_FLAG_INACTIVEICON)
/**
* Macro to Set flag value
*/
#define SWITCHICON_WDG_ACTIVEICON_SET_MODIFIED(_pWdg, _b) \
    (_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SWITCHICON_WDG_RELOAD_MASK_ACTIVEICON))|(((u32)_b)<<SWITCHICON_WDG_RELOAD_FLAG_ACTIVEICON)
#define SWITCHICON_WDG_INACTIVEICON_SET_MODIFIED(_pWdg, _b) \
    (_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SWITCHICON_WDG_RELOAD_MASK_INACTIVEICON))|(((u32)_b)<<SWITCHICON_WDG_RELOAD_FLAG_INACTIVEICON)

/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret SwitchIconWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean SwitchIconWidget_DefHandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret SwitchIconWidgetStructCtor(SwitchIconWidget_t *pThis);
void SwitchIconWidgetStructDtor(SwitchIconWidget_t *pThis);
void SwitchIconWidget_SetSize(IWidget *pIWidget, WidgetSize_t *pSize);
void SwitchIconWidget_GetPreferredSize(IWidget *pIWidget, WidgetSize_t *pSize);
boolean SwitchIconWidget_IntersectOpaque(IWidget *pIWidget, const Rect_t *pInRect, Rect_t *pOutRect);
void SwitchIconWidget_Draw(IWidget *pIWidget, IDispCanvas *pIDispCanvas, s32 x, s32 y);
MAE_Ret SwitchIconWidget_SetModel(IWidget *pIWidget, IModel *pIModel, IBase* pOwner);
static void SwitchIconWidget_ReloadRC(SwitchIconWidget_t *pThis, DisplayMode_e nDispMode);

#endif //__MMI_WDG_SWITCHICON_PRIV_H__
/*=============================================================*/
// end of file
