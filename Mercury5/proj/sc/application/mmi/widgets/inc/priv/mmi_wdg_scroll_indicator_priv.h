/**
* @file mmi_wdg_scroll_indicator_priv.h
* @brief This file defines the data structure of scroll indicator widget
*
* @version $Id: mmi_wdg_scroll_indicator_priv.h 25372 2009-03-11 08:10:22Z mark.yang $
*/
#ifndef __MMI_WDG_SCROLL_INDICATOR_PRIV_H__
#define __MMI_WDG_SCROLL_INDICATOR_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_scroll_indicator.h"
#include "mmi_mae_common_def.h"
#include "mae_decoratorbase.h"
#include "mae_scrollcommon.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/**
*/
enum {
	ARROW_IMG_TYPE_NONE = 0,
	ARROW_IMG_TYPE_ENABLE,
	ARROW_IMG_TYPE_DISABLE,
#ifdef __TOUCH_SCREEN_MMI__
	ARROW_IMG_TYPE_PRESSED,
#endif //__TOUCH_SCREEN_MMI__
	ARROW_IMG_TYPE_END
};
typedef u8 _ArrowImgType_t;


/**
*/
typedef struct {
	IImage   *pArrowEnable;    ///< An IBitmap object to display enabled arrow.
	IImage   *pArrowDisable;   ///< An IBitmap object to display disabled arrow.
#ifdef __TOUCH_SCREEN_MMI__
	IImage   *pArrowPressed;   ///< An IBitmap object to display pressed arrow.
#endif //__TOUCH_SCREEN_MMI__
} _ArrowImages_t;

/**
* This is the main structure for a scroll-indicator widget
*/
typedef struct {
	DecoratorEx_t     DecBase;                   ///< Use DecoratorEx_t structure as a base structure.
	IWidget*          apArrowWdg[ARROW_NUM];      ///< Use four Image-widget to display left/right/up/down arrow.
	_ArrowImages_t    astArrowImages[ARROW_NUM]; /*!< Keep arrow images for all directions(left/right/up/down) 
	                                                  and types(enable/disable/pressed) */
	_ArrowImgType_t   aArrowImgType[ARROW_NUM];  ///< Indicate which image displaying now.
	ModelListener_t   ChildWdgViewMdlLsn;        ///< Model listener, use child widget's viewmodel as our model.
	WdgLayoutStyle_t  nLayoutMode;               ///< Layout mode, default is LAYOUT_STYLE_HORIZONTAL.
	Rect_t            astArrowRect[ARROW_NUM];   ///< Rectangles for left/right/up/down arrow
	Rect_t            ChildWdgRect;              ///< Rectangle for child widget
	_ScrollInfo_st    astScrollInfo[SCROLL_DIR_NUM]; ///< Scroll information in two dimension(horizontal and vertical)
#ifdef __TOUCH_SCREEN_MMI__
	ITouchSrv        *pITouchSrv;            ///< Touch Service
	WidgetHandler_t   aArrowWdgHdlData[ARROW_NUM]; ///< to hook widget's eventhandler
	_ArrowDir_t       nPressedArrow; ///< indicate which arrow is pressed.
#endif            

	u32					nReloadRCFlag;		///< the flag record which rc property has been modified outside, those are not reload
} _ScrollIndicatorWdg_t;

// RELOAD flag
enum
{
	SCROLLIND_WDG_RELOAD_FLAG_START = 0,
	SCROLLIND_WDG_RELOAD_FLAG_ARR_LEFT_W = SCROLLIND_WDG_RELOAD_FLAG_START,
	SCROLLIND_WDG_RELOAD_FLAG_ARR_LEFT_H,
	SCROLLIND_WDG_RELOAD_FLAG_ARR_RIGHT_W,
	SCROLLIND_WDG_RELOAD_FLAG_ARR_RIGHT_H,
	SCROLLIND_WDG_RELOAD_FLAG_ARR_UP_W,
	SCROLLIND_WDG_RELOAD_FLAG_ARR_UP_H,
	SCROLLIND_WDG_RELOAD_FLAG_ARR_DOWN_W,
	SCROLLIND_WDG_RELOAD_FLAG_ARR_DOWN_H,
	SCROLLIND_WDG_RELOAD_FLAG_END
};

/**
* Flag Mask
*/
#define SCROLLIND_WDG_RELOAD_MASK_ARR_LEFT_W      (1<<SCROLLIND_WDG_RELOAD_FLAG_ARR_LEFT_W)
#define SCROLLIND_WDG_RELOAD_MASK_ARR_LEFT_H      (1<<SCROLLIND_WDG_RELOAD_FLAG_ARR_LEFT_H)
#define SCROLLIND_WDG_RELOAD_MASK_ARR_RIGHT_W     (1<<SCROLLIND_WDG_RELOAD_FLAG_ARR_RIGHT_W)
#define SCROLLIND_WDG_RELOAD_MASK_ARR_RIGHT_H     (1<<SCROLLIND_WDG_RELOAD_FLAG_ARR_RIGHT_H)
#define SCROLLIND_WDG_RELOAD_MASK_ARR_UP_W        (1<<SCROLLIND_WDG_RELOAD_FLAG_ARR_UP_W)
#define SCROLLIND_WDG_RELOAD_MASK_ARR_UP_H        (1<<SCROLLIND_WDG_RELOAD_FLAG_ARR_UP_H)
#define SCROLLIND_WDG_RELOAD_MASK_ARR_DOWN_W      (1<<SCROLLIND_WDG_RELOAD_FLAG_ARR_DOWN_W)
#define SCROLLIND_WDG_RELOAD_MASK_ARR_DOWN_H      (1<<SCROLLIND_WDG_RELOAD_FLAG_ARR_DOWN_H)
/**
* Macro to get flag value
*/
#define SCROLLIND_WDG_ARR_LEFT_W_IS_MODIFIED(_pWdg) \
    (boolean)(((_pWdg)->nReloadRCFlag&SCROLLIND_WDG_RELOAD_MASK_ARR_LEFT_W)>>SCROLLIND_WDG_RELOAD_FLAG_ARR_LEFT_W)
#define SCROLLIND_WDG_ARR_LEFT_H_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&SCROLLIND_WDG_RELOAD_MASK_ARR_LEFT_H)>>SCROLLIND_WDG_RELOAD_FLAG_ARR_LEFT_H)
#define SCROLLIND_WDG_ARR_RIGHT_W_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&SCROLLIND_WDG_RELOAD_MASK_ARR_RIGHT_W)>>SCROLLIND_WDG_RELOAD_FLAG_ARR_RIGHT_W)
#define SCROLLIND_WDG_ARR_RIGHT_H_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&SCROLLIND_WDG_RELOAD_MASK_ARR_RIGHT_H)>>SCROLLIND_WDG_RELOAD_FLAG_ARR_RIGHT_H)
#define SCROLLIND_WDG_ARR_UP_W_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&SCROLLIND_WDG_RELOAD_MASK_ARR_UP_W)>>SCROLLIND_WDG_RELOAD_FLAG_ARR_UP_W)
#define SCROLLIND_WDG_ARR_UP_H_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&SCROLLIND_WDG_RELOAD_MASK_ARR_UP_H)>>SCROLLIND_WDG_RELOAD_FLAG_ARR_UP_H)
#define SCROLLIND_WDG_ARR_DOWN_W_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&SCROLLIND_WDG_RELOAD_MASK_ARR_DOWN_W)>>SCROLLIND_WDG_RELOAD_FLAG_ARR_DOWN_W)
#define SCROLLIND_WDG_ARR_DOWN_H_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&SCROLLIND_WDG_RELOAD_MASK_ARR_DOWN_H)>>SCROLLIND_WDG_RELOAD_FLAG_ARR_DOWN_H)
/**
* Macro to Set flag value
*/
#define SCROLLIND_WDG_ARR_LEFT_W_SET_MODIFIED(_pWdg, _b) \
    (_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SCROLLIND_WDG_RELOAD_MASK_ARR_LEFT_W))|(((u32)_b)<<SCROLLIND_WDG_RELOAD_FLAG_ARR_LEFT_W)
#define SCROLLIND_WDG_ARR_LEFT_H_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SCROLLIND_WDG_RELOAD_MASK_ARR_LEFT_H))|(((u32)_b)<<SCROLLIND_WDG_RELOAD_FLAG_ARR_LEFT_H)
#define SCROLLIND_WDG_ARR_RIGHT_W_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SCROLLIND_WDG_RELOAD_MASK_ARR_RIGHT_W))|(((u32)_b)<<SCROLLIND_WDG_RELOAD_FLAG_ARR_RIGHT_W)
#define SCROLLIND_WDG_ARR_RIGHT_H_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SCROLLIND_WDG_RELOAD_MASK_ARR_RIGHT_H))|(((u32)_b)<<SCROLLIND_WDG_RELOAD_FLAG_ARR_RIGHT_H)
#define SCROLLIND_WDG_ARR_UP_W_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SCROLLIND_WDG_RELOAD_MASK_ARR_UP_W))|(((u32)_b)<<SCROLLIND_WDG_RELOAD_FLAG_ARR_UP_W)
#define SCROLLIND_WDG_ARR_UP_H_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SCROLLIND_WDG_RELOAD_MASK_ARR_UP_H))|(((u32)_b)<<SCROLLIND_WDG_RELOAD_FLAG_ARR_UP_H)
#define SCROLLIND_WDG_ARR_DOWN_W_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SCROLLIND_WDG_RELOAD_MASK_ARR_DOWN_W))|(((u32)_b)<<SCROLLIND_WDG_RELOAD_FLAG_ARR_DOWN_W)
#define SCROLLIND_WDG_ARR_DOWN_H_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SCROLLIND_WDG_RELOAD_MASK_ARR_DOWN_H))|(((u32)_b)<<SCROLLIND_WDG_RELOAD_FLAG_ARR_DOWN_H)

/// Status flags
enum {
	SCLIND_WDG_FLAG_STAR = DEC_BASE_FLAG_END,
	SCLIND_WDG_FLAG_ARROW_INSIDE = SCLIND_WDG_FLAG_STAR,
	SCLIND_WDG_FLAG_INVSISBLE_IF_DISABLE,
	SCLIND_WDG_FLAG_CHILD_WRAP,
#ifdef __TOUCH_SCREEN_MMI__
	SCLIND_WDG_FLAG_TS_LONG_PRESSED,
	SCLIND_WDG_FLAG_TOUCH_VALID,
	SCLIND_WDG_FLAG_LONG_TS_TIMER_RUNNING,
	SCLIND_WDG_FLAG_REPEAT_TIMER_RUNNING,
#endif // __TOUCH_SCREEN_MMI__
	SCLIND_WDG_FLAG_END
};

/// Masks
#define SCLIND_WDG_MASK_ARROW_INSIDE            (1<<SCLIND_WDG_FLAG_ARROW_INSIDE)
#define SCLIND_WDG_MASK_INVISIBLE_IF_DISABLE    (1<<SCLIND_WDG_FLAG_INVSISBLE_IF_DISABLE)
#define SCLIND_WDG_MASK_CHILD_WRAP              (1<<SCLIND_WDG_FLAG_CHILD_WRAP)
#ifdef __TOUCH_SCREEN_MMI__
#define SCLIND_WDG_MASK_TS_LONG_PRESSED         (1<<SCLIND_WDG_FLAG_TS_LONG_PRESSED)
#define SCLIND_WDG_MASK_TOUCH_VALID             (1<<SCLIND_WDG_FLAG_TOUCH_VALID)
#define SCLIND_WDG_MASK_LONG_TS_TIMER_RUNNING   (1<<SCLIND_WDG_FLAG_LONG_TS_TIMER_RUNNING)
#define SCLIND_WDG_MASK_REPEAT_TIMER_RUNNING    (1<<SCLIND_WDG_FLAG_REPEAT_TIMER_RUNNING)
#endif // __TOUCH_SCREEN_MMI__

/// macro to Get flag
#define SCLIND_WDG_IS_ARROW_INSIDE(_pSclIndWdg_) \
	(boolean)(((_pSclIndWdg_)->DecBase.WdgBase.Flags&SCLIND_WDG_MASK_ARROW_INSIDE)>>SCLIND_WDG_FLAG_ARROW_INSIDE)
#define SCLIND_WDG_IS_INVISIBLE_IF_DISABLE(_pSclIndWdg_) \
	(boolean)(((_pSclIndWdg_)->DecBase.WdgBase.Flags&SCLIND_WDG_MASK_INVISIBLE_IF_DISABLE)>>SCLIND_WDG_FLAG_INVSISBLE_IF_DISABLE)
#define SCLIND_WDG_IS_CHILD_WRAP(_pSclIndWdg_) \
	(boolean)(((_pSclIndWdg_)->DecBase.WdgBase.Flags&SCLIND_WDG_MASK_CHILD_WRAP)>>SCLIND_WDG_FLAG_CHILD_WRAP)
#ifdef __TOUCH_SCREEN_MMI__
#define SCLIND_WDG_IS_TS_LONG_PRESSED(_pSclIndWdg_) \
	(boolean)(((_pSclIndWdg_)->DecBase.WdgBase.Flags&SCLIND_WDG_MASK_TS_LONG_PRESSED)>>SCLIND_WDG_FLAG_TS_LONG_PRESSED)
#define SCLIND_WDG_IS_TOUCH_VALID(_pSclIndWdg_) \
	(boolean)(((_pSclIndWdg_)->DecBase.WdgBase.Flags&SCLIND_WDG_MASK_TOUCH_VALID)>>SCLIND_WDG_FLAG_TOUCH_VALID)
#define SCLIND_WDG_IS_LONG_TS_TIMER_RUNNING(_pSclIndWdg_) \
	(boolean)(((_pSclIndWdg_)->DecBase.WdgBase.Flags&SCLIND_WDG_MASK_LONG_TS_TIMER_RUNNING)>>SCLIND_WDG_FLAG_LONG_TS_TIMER_RUNNING)
#define SCLIND_WDG_IS_REPEAT_TIMER_RUNNING(_pSclIndWdg_) \
	(boolean)(((_pSclIndWdg_)->DecBase.WdgBase.Flags&SCLIND_WDG_MASK_REPEAT_TIMER_RUNNING)>>SCLIND_WDG_FLAG_REPEAT_TIMER_RUNNING)
#endif // __TOUCH_SCREEN_MMI__


/// macro to set flag
#define SCLIND_WDG_SET_ARROW_INSIDE(_pSclIndWdg_, _b) \
	(_pSclIndWdg_)->DecBase.WdgBase.Flags = ((_pSclIndWdg_)->DecBase.WdgBase.Flags&(~SCLIND_WDG_MASK_ARROW_INSIDE))|(((u32)_b)<<SCLIND_WDG_FLAG_ARROW_INSIDE)
#define SCLIND_WDG_SET_INVISIBLE_IF_DISABLE(_pSclIndWdg_, _b) \
	(_pSclIndWdg_)->DecBase.WdgBase.Flags = ((_pSclIndWdg_)->DecBase.WdgBase.Flags&(~SCLIND_WDG_MASK_INVISIBLE_IF_DISABLE))|(((u32)_b)<<SCLIND_WDG_FLAG_INVSISBLE_IF_DISABLE)
#define SCLIND_WDG_SET_CHILD_WRAP(_pSclIndWdg_, _b) \
	(_pSclIndWdg_)->DecBase.WdgBase.Flags = ((_pSclIndWdg_)->DecBase.WdgBase.Flags&(~SCLIND_WDG_MASK_CHILD_WRAP))|(((u32)_b)<<SCLIND_WDG_FLAG_CHILD_WRAP)
#ifdef __TOUCH_SCREEN_MMI__
#define SCLIND_WDG_SET_TS_LONG_PRESSED(_pSclIndWdg_, _b) \
	(_pSclIndWdg_)->DecBase.WdgBase.Flags = ((_pSclIndWdg_)->DecBase.WdgBase.Flags&(~SCLIND_WDG_MASK_TS_LONG_PRESSED))|(((u32)_b)<<SCLIND_WDG_FLAG_TS_LONG_PRESSED)
#define SCLIND_WDG_SET_TOUCH_VALID(_pSclIndWdg_, _b) \
	(_pSclIndWdg_)->DecBase.WdgBase.Flags = ((_pSclIndWdg_)->DecBase.WdgBase.Flags&(~SCLIND_WDG_MASK_TOUCH_VALID))|(((u32)_b)<<SCLIND_WDG_FLAG_TOUCH_VALID)
#define SCLIND_WDG_SET_LONG_TS_TIMER_RUN(_pSclIndWdg_, _b) \
	(_pSclIndWdg_)->DecBase.WdgBase.Flags = ((_pSclIndWdg_)->DecBase.WdgBase.Flags&(~SCLIND_WDG_MASK_LONG_TS_TIMER_RUNNING))|(((u32)_b)<<SCLIND_WDG_FLAG_LONG_TS_TIMER_RUNNING)
#define SCLIND_WDG_SET_REPEAT_TIMER_RUN(_pSclIndWdg_, _b) \
	(_pSclIndWdg_)->DecBase.WdgBase.Flags = ((_pSclIndWdg_)->DecBase.WdgBase.Flags&(~SCLIND_WDG_MASK_REPEAT_TIMER_RUNNING))|(((u32)_b)<<SCLIND_WDG_FLAG_REPEAT_TIMER_RUNNING)
#endif // __TOUCH_SCREEN_MMI__

/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAERet_t ScrollIndicatorWidget_New(MAEClsId_t ClsID, void **ppObj);
boolean _ScrlIndWdg_DefHandleEvent(IDecorator *pIDecorator, MAEEvent_t evt, u32 P1, u32 P2);


/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAERet_t SrlIndWdgCtor(_ScrollIndicatorWdg_t *pThis);
void SrlIndWdgDtor(_ScrollIndicatorWdg_t *pThis);

void ScrollIndicatorWidget_SetSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
void ScrollIndicatorWidget_GetPreferredSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
boolean ScrollIndicatorWidget_IntersectOpaque(IDecorator *pIDecorator, const Rect_t *pInRect, Rect_t *pOutRect);
void ScrollIndicatorWidget_Invalidate(IDecorator *pIDecorator, IWidget *WidgetPtr, const Rect_t *WRectPtr, InvFlag_t Flags);
MAERet_t ScrollIndicatorWidget_Locate(IDecorator *pIDecorator, IWidget *WidgetPtr, IContainer **ppRoot, Rect_t *RelativeRectPtr, IBase *pOwner);
void ScrollIndicatorWidget_SetDecWidget(IDecorator *pIDecorator, IWidget *pChild);

#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
static void _ScrollIndicatorWidget_ReloadRC(_ScrollIndicatorWdg_t *pThis, DisplayMode_e nDispMode);
#endif // __AUTO_ROTATE_DISPLAY__
boolean ScrollIndWidget_NotifyScrollFinish(_ScrollIndicatorWdg_t *pThis, MAE_EventId evt, u32 P1, u32 P2);

#endif //__MMI_WDG_SCROLL_INDICATOR_PRIV_H__
/*=============================================================*/
// end of file
