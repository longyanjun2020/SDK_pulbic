/**
* @file 	mmi_wdg_tab_priv.h
* @version $Id: mmi_wdg_tab_priv.h 10115 2008-05-06 05:32:36Z paul.ouyang $
* @brief   
*
*/
#ifndef __MMI_WDG_TAB_PRIV_H__
#define __MMI_WDG_TAB_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_decoratorbase.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct {
	DecoratorEx_t			DecBase;			///< A decorator base structure

	/// These items response for drawing tab region ///
	IWidget             *pTabCntrWdg;       ///<Prop container which contains list and button>
	IWidget             *pLeftBtnWdg;       ///<Left button widget>
    IWidget             *pRightBtnWdg;      ///<Right button widget>
	IWidget			*pListWdgDec;		///< A horizontal list widget or ring-list widget
	IWidget				*pItemWdg;			///< Item widget to draw tabs.
	ModelListener_t		ItemDataMdlLsn;		///< model listener for item widget's data model
	WidgetHandler_t		ItemWdgHdler;
	IWidget				*pImageWdg;			///< An image widget...
	IWidget				*pTextWdg;			///< A text widget.....

	/// ///
	IWidget			*pChildCntr;        ///< Default is a Sheet-container.

	s32					nFocusIdx;			///< A zero-base index of focus item
	u32					nFlage;				///< wrap, and...?
	u32					nStatusFlags;
	u32					nReloadRCFlag;		///< the flag record which rc property has been modified outside, those are not reload

	u16					nActiveWidth;		///< Active(Focused, highlighted) item width
	u16					nInactiveWidth;		///< Inactive(unfocused, unhighlighted) item width
	u16					nTabRegionHeight;	///< The height of Tab region
	u16					nTabOffset;			///< Height offset in pixels between active tab and inactive tab
	u8					nMode;				///< 
} TabWidget_t;

/**
* Status Flags in TabWidget_t
*/
enum
{
	TABWDG_FLAG_START = 0,
	TABWDG_FLAG_DISABLE_KEY_EVENT = TABWDG_FLAG_START,
	TABWDG_FLAG_MOVE_DIR_TO_RIGHT,
	TABWDG_FLAG_TOUCH_TRIGGER_FOCUS_CHANGE,
	TABWDG_FLAG_END
};

/**
* Status Flags Mask
*/
#define TABWDG_MASK_DISABLE_KEY_EVENT         (1<<TABWDG_FLAG_DISABLE_KEY_EVENT)
#define TABWDG_MASK_MOVE_DIR_TO_RIGHT         (1<<TABWDG_FLAG_MOVE_DIR_TO_RIGHT)
#define TABWDG_MASK_TOUCH_TRIGGER_FOCUS_CHANGE (1<<TABWDG_FLAG_TOUCH_TRIGGER_FOCUS_CHANGE)

/**
* Macro to Get Status Flags value
*/
#define TABWDG_IS_DISABLE_KEY_EVENT(_pTabWdg) \
	(boolean)(((_pTabWdg)->nStatusFlags&TABWDG_MASK_DISABLE_KEY_EVENT)>>TABWDG_FLAG_DISABLE_KEY_EVENT)
#define TABWDG_IS_MOVE_DIR_TO_RIGHT(_pTabWdg) \
	(boolean)(((_pTabWdg)->nStatusFlags&TABWDG_MASK_MOVE_DIR_TO_RIGHT)>>TABWDG_FLAG_MOVE_DIR_TO_RIGHT)
#define TABWDG_IS_TOUCH_TRIGGER_FOCUS_CHANGE(_pTabWdg) \
	(boolean)(((_pTabWdg)->nStatusFlags&TABWDG_MASK_TOUCH_TRIGGER_FOCUS_CHANGE)>>TABWDG_FLAG_TOUCH_TRIGGER_FOCUS_CHANGE)

/**
* Macro to Set Status flags value
*/
#define TABWDG_DISABLE_KEY_EVENT(_pTabWdg, _b) \
	(_pTabWdg)->nStatusFlags = ((_pTabWdg)->nStatusFlags&(~TABWDG_MASK_DISABLE_KEY_EVENT))|(((u32)_b)<<TABWDG_FLAG_DISABLE_KEY_EVENT)
#define TABWDG_SET_MOVE_DIR_TO_RIGHT(_pTabWdg, _b) \
	(_pTabWdg)->nStatusFlags = ((_pTabWdg)->nStatusFlags&(~TABWDG_MASK_MOVE_DIR_TO_RIGHT))|(((u32)_b)<<TABWDG_FLAG_MOVE_DIR_TO_RIGHT)
#define TABWDG_SET_TOUCH_TRIGGER_FOCUS_CHANGE(_pTabWdg, _b) \
	(_pTabWdg)->nStatusFlags = ((_pTabWdg)->nStatusFlags&(~TABWDG_MASK_TOUCH_TRIGGER_FOCUS_CHANGE))|(((u32)_b)<<TABWDG_FLAG_TOUCH_TRIGGER_FOCUS_CHANGE)
// RELOAD flag
enum
{
	TAB_WDG_RELOAD_FLAG_START = 0,
	TAB_WDG_RELOAD_FLAG_TABREGIONHEIGHT = TAB_WDG_RELOAD_FLAG_START,   ///< nTabRegionHeight
	TAB_WDG_RELOAD_FLAG_ACTIVEWIDTH,	///< nActiveWidth
	TAB_WDG_RELOAD_FLAG_INACTIVEWIDTH,	///< nInactiveWidth
	TAB_WDG_RELOAD_FLAG_TABOFFSET,	///< nTabOffset
	TAB_WDG_RELOAD_FLAG_MODE,	///< nMode
	TAB_WDG_RELOAD_FLAG_LISTPADDINGLEFT,	///< nListPaddingLeft
	TAB_WDG_RELOAD_FLAG_LISTPADDINGRIGHT,	///< nListPaddingRight
	TAB_WDG_RELOAD_FLAG_END
};

/**
* Flag Mask
*/
#define TAB_WDG_RELOAD_MASK_TABREGIONHEIGHT         (1<<TAB_WDG_RELOAD_FLAG_TABREGIONHEIGHT)
#define TAB_WDG_RELOAD_MASK_ACTIVEWIDTH        (1<<TAB_WDG_RELOAD_FLAG_ACTIVEWIDTH)
#define TAB_WDG_RELOAD_MASK_INACTIVEWIDTH         (1<<TAB_WDG_RELOAD_FLAG_INACTIVEWIDTH)
#define TAB_WDG_RELOAD_MASK_TABOFFSET         (1<<TAB_WDG_RELOAD_FLAG_TABOFFSET)
#define TAB_WDG_RELOAD_MASK_MODE         (1<<TAB_WDG_RELOAD_FLAG_MODE)
#define TAB_WDG_RELOAD_MASK_LISTPADDINGLEFT         (1<<TAB_WDG_RELOAD_FLAG_LISTPADDINGLEFT)
#define TAB_WDG_RELOAD_MASK_LISTPADDINGRIGHT         (1<<TAB_WDG_RELOAD_FLAG_LISTPADDINGRIGHT)
/**
* Macro to get flag value
*/
#define TAB_WDG_TABREGIONHEIGHT_IS_MODIFIED(_pWdg) \
    (boolean)(((_pWdg)->nReloadRCFlag&TAB_WDG_RELOAD_MASK_TABREGIONHEIGHT)>>TAB_WDG_RELOAD_FLAG_TABREGIONHEIGHT)
#define TAB_WDG_ACTIVEWIDTH_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TAB_WDG_RELOAD_MASK_ACTIVEWIDTH)>>TAB_WDG_RELOAD_FLAG_ACTIVEWIDTH)
#define TAB_WDG_INACTIVEWIDTH_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TAB_WDG_RELOAD_MASK_INACTIVEWIDTH)>>TAB_WDG_RELOAD_FLAG_INACTIVEWIDTH)
#define TAB_WDG_TABOFFSET_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TAB_WDG_RELOAD_MASK_TABOFFSET)>>TAB_WDG_RELOAD_FLAG_TABOFFSET)
#define TAB_WDG_MODE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TAB_WDG_RELOAD_MASK_MODE)>>TAB_WDG_RELOAD_FLAG_MODE)
#define TAB_WDG_LISTPADDINGLEFT_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TAB_WDG_RELOAD_MASK_LISTPADDINGLEFT)>>TAB_WDG_RELOAD_FLAG_LISTPADDINGLEFT)
#define TAB_WDG_LISTPADDINGRIGHT_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TAB_WDG_RELOAD_MASK_LISTPADDINGRIGHT)>>TAB_WDG_RELOAD_FLAG_LISTPADDINGRIGHT)
/**
* Macro to Set flag value
*/
#define TAB_WDG_TABREGIONHEIGHT_SET_MODIFIED(_pWdg, _b) \
    (_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TAB_WDG_RELOAD_MASK_TABREGIONHEIGHT))|(((u32)_b)<<TAB_WDG_RELOAD_FLAG_TABREGIONHEIGHT)
#define TAB_WDG_ACTIVEWIDTH_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TAB_WDG_RELOAD_MASK_ACTIVEWIDTH))|(((u32)_b)<<TAB_WDG_RELOAD_FLAG_ACTIVEWIDTH)
#define TAB_WDG_INACTIVEWIDTH_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TAB_WDG_RELOAD_MASK_INACTIVEWIDTH))|(((u32)_b)<<TAB_WDG_RELOAD_FLAG_INACTIVEWIDTH)
#define TAB_WDG_TABOFFSET_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TAB_WDG_RELOAD_MASK_TABOFFSET))|(((u32)_b)<<TAB_WDG_RELOAD_FLAG_TABOFFSET)
#define TAB_WDG_MODE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TAB_WDG_RELOAD_MASK_MODE))|(((u32)_b)<<TAB_WDG_RELOAD_FLAG_MODE)
#define TAB_WDG_LISTPADDINGLEFT_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TAB_WDG_RELOAD_MASK_LISTPADDINGLEFT))|(((u32)_b)<<TAB_WDG_RELOAD_FLAG_LISTPADDINGLEFT)
#define TAB_WDG_LISTPADDINGRIGHT_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TAB_WDG_RELOAD_MASK_LISTPADDINGRIGHT))|(((u32)_b)<<TAB_WDG_RELOAD_FLAG_LISTPADDINGRIGHT)

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret TabWidget_New(MAE_ClsId ClsID, void **ppObj);
__SLDPM_FREE__ boolean TabWidget_DefHandleEvent(IDecorator *pIDecorator, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret _WdgTabConstructor(TabWidget_t *pThis);
void _WdgTabDestructor(TabWidget_t *pThis);
static void TabWidget_SetSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
static void TabWidget_GetPreferredSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
boolean TabWidget_IntersectOpaque(IDecorator *pIDecorator, const Rect_t *pInRect, Rect_t *pOutRect);
__SLDPM_FREE__ void TabWidget_Draw(IDecorator *pIDecorator, IDispCanvas *pIDispCanvas, s32 x, s32 y);
static MAE_Ret TabWidget_SetModel(IDecorator *pIDecorator, IModel *pIModel, IBase* pOwner);
__SLDPM_FREE__ static void TabWidget_Invalidate(IDecorator *pIDecorator, IWidget *WidgetPtr, const Rect_t *WRectPtr, InvFlag_t Flags);
__SLDPM_FREE__ static MAE_Ret TabWidget_Locate(IDecorator *pIDecorator, WdgContainer_WdgLocate_t *pQuery);
__SLDPM_FREE__ static void TabWidget_SetDecWidget(IDecorator *pIDecorator, IWidget *pChild);

/*------------------------------------------------------------------------------------------
* For other functions
------------------------------------------------------------------------------------------*/
#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
static void _TabWidget_ReloadRC(TabWidget_t *pThis, DisplayMode_e nDispMode);
#endif // __AUTO_ROTATE_DISPLAY__

#endif //__MMI_WDG_TAB_PRIV_H__
/*=============================================================*/
// end of file
