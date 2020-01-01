/**
* @file	mmi_wdg_button_priv.h
* @version	$Id: mmi_wdg_button_priv.h 25372 2009-03-11 08:10:22Z mark.yang $
*
* @brief	This is a private header file for Button-widget implementation.
*/
#ifndef __MMI_WDG_BUTTON_PRIV_H__
#define __MMI_WDG_BUTTON_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_button.h"
#include "mae_widgetbase.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct {

/**
* The structure for implementation of Button-widget.
*/
	WidgetBaseEx_t      WdgBase;            ///< Using WidgetBaseEx_t as base structure.
	IWidget            *pImageWdg;          ///< Use a image-widget to draw unpressed/pressed image.
	ModelListener_t     MdlLsn;             ///< Model listener for the data-model change.
	_TxtColor_t         stUnPrsdTxtColor;   ///< Text color and outline color while unpressed.
	_TxtColor_t         stPrsdTxtColor;     ///< Text color and outline color while pressed.
	FontCategory_t      FontCat;            ///< Font category
	u32      			FontSize;            ///< Font size
	FontType_t          FontType;           ///< Font type, normal, outline...
	u8                      textAlign;
	WdgPaddingData_t        pTextPaddingData;
#ifdef __TOUCH_SCREEN_MMI__
	ITouchSrv          *pITouchSrv;			///< Touch service
#endif //__TOUCH_SCREEN_MMI__

	/// the following are status flags
#ifdef __TOUCH_SCREEN_MMI__
	u32                 bIsLpEvtSent : 1;      ///< a flag to indicate if long press event is already sent
	u32                 bIsLpTimerRunning : 1; ///< a flag to indicate if long press timer running
	u32                 bIsRptTimerRunning : 1;///< a flog to indicate if repeat timer running
#endif //__TOUCH_SCREEN_MMI__

#if defined(__G3D_MMI__)	
    u32                 bTxtClrDiff : 1;///< a flog to indicate if press and unpress text color are different
    u32		        nTxtRawDataID;			///< RawData ID for text
#endif
	u32					nReloadRCFlag;		///< the flag record which rc property has been modified outside, those are not reload
    boolean             bEnableTouchHook;
} _ButtonWidget_t;

//Flags
enum
{
	BTN_WDG_FLAG_START = WDG_BASE_FLAG_END,
	BTN_WDG_FLAG_BE_ITEM_WDG = BTN_WDG_FLAG_START,///< A status flag to inidcate this button-widget is a item widget or not.
	BTN_WDG_FLAG_HIGHLIGHTED,///< is highlighted or unhighlighted.
	BTN_WDG_FLAG_DISABLE_DISPLAY_TEXT,///< Enable/Disable to display text
    BTN_WDG_FLAG_DISPLAY_DISABLE_BIDI,
#ifdef __TOUCH_SCREEN_MMI__
	BTN_WDG_FLAG_DISABLE_TOUCH,///< A status flag, to indicate if this button is disable to handle touch event
	BTN_WDG_FLAG_TOUCH_PRESSED,///< A status flag, to indicate if this button is pressed by touch
	BTN_WDG_FLAG_TOUCH_VALIDATION,///< A status flag, to indicate if touch press is in valid rectangle or invalid.
	BTN_WDG_FLAG_ITEM_PRESSED,///< is item pressed or not
#endif //__TOUCH_SCREEN_MMI__
	BTN_WDG_FLAG_END
};

//Mask 
#define BTN_WDG_MASK_BE_ITEM_WDG          (1<<BTN_WDG_FLAG_BE_ITEM_WDG)  ///<
#define BTN_WDG_MASK_HIGHLIGHTED          (1<<BTN_WDG_FLAG_HIGHLIGHTED)  ///<
#define BTN_WDG_MASK_DISABLE_DISPLAY_TEXT (1<<BTN_WDG_FLAG_DISABLE_DISPLAY_TEXT)      ///<
#define BTN_WDG_MASK_DISPALY_DISABLE_BIDI (1<<BTN_WDG_FLAG_DISPLAY_DISABLE_BIDI)
#ifdef __TOUCH_SCREEN_MMI__
#define BTN_WDG_MASK_DISABLE_TOUCH        (1<<BTN_WDG_FLAG_DISABLE_TOUCH)      ///<
#define BTN_WDG_MASK_TOUCH_PRESSED        (1<<BTN_WDG_FLAG_TOUCH_PRESSED)      ///<
#define BTN_WDG_MASK_TOUCH_VALIDATION     (1<<BTN_WDG_FLAG_TOUCH_VALIDATION)      ///<
#define BTN_WDG_MASK_ITEM_PRESSED         (1<<BTN_WDG_FLAG_ITEM_PRESSED)      ///<
#endif //__TOUCH_SCREEN_MMI__

//Get flag
#define BTN_WDG_IS_ITEM_WIDGET(_pBtnWdg) \
	(boolean)(((_pBtnWdg)->WdgBase.Flags&BTN_WDG_MASK_BE_ITEM_WDG)>>BTN_WDG_FLAG_BE_ITEM_WDG)
#define BTN_WDG_IS_HIGHLIGHTED(_pBtnWdg) \
	(boolean)(((_pBtnWdg)->WdgBase.Flags&BTN_WDG_MASK_HIGHLIGHTED)>>BTN_WDG_FLAG_HIGHLIGHTED)
#define BTN_WDG_IS_DISABLED_DISPLAY_TEXT(_pBtnWdg) \
	(boolean)(((_pBtnWdg)->WdgBase.Flags&BTN_WDG_MASK_DISABLE_DISPLAY_TEXT)>>BTN_WDG_FLAG_DISABLE_DISPLAY_TEXT)
#define BTN_WDG_IS_DISPLAY_DISABLE_BIDI(_pBtnWdg) \
    (boolean)(((_pBtnWdg)->WdgBase.Flags&BTN_WDG_MASK_DISPALY_DISABLE_BIDI)>>BTN_WDG_FLAG_DISPLAY_DISABLE_BIDI)
#ifdef __TOUCH_SCREEN_MMI__
#define BTN_WDG_IS_DISABLE_TOUCH(_pBtnWdg) \
	(boolean)(((_pBtnWdg)->WdgBase.Flags&BTN_WDG_MASK_DISABLE_TOUCH)>>BTN_WDG_FLAG_DISABLE_TOUCH)
#define BTN_WDG_IS_TOUCH_PRESSED(_pBtnWdg) \
	(boolean)(((_pBtnWdg)->WdgBase.Flags&BTN_WDG_MASK_TOUCH_PRESSED)>>BTN_WDG_FLAG_TOUCH_PRESSED)
#define BTN_WDG_IS_TOUCH_VALID(_pBtnWdg) \
	(boolean)(((_pBtnWdg)->WdgBase.Flags&BTN_WDG_MASK_TOUCH_VALIDATION)>>BTN_WDG_FLAG_TOUCH_VALIDATION)
#define BTN_WDG_IS_ITEM_PRESSED(_pBtnWdg) \
	(boolean)(((_pBtnWdg)->WdgBase.Flags&BTN_WDG_MASK_ITEM_PRESSED)>>BTN_WDG_FLAG_ITEM_PRESSED)
#endif //__TOUCH_SCREEN_MMI__

//Set flag
#define BTN_WDG_SET_ITEM_WIDGET(_pBtnWdg, _b) \
	(_pBtnWdg)->WdgBase.Flags = ((_pBtnWdg)->WdgBase.Flags&(~BTN_WDG_MASK_BE_ITEM_WDG))|(((u32)_b)<<BTN_WDG_FLAG_BE_ITEM_WDG)
#define BTN_WDG_SET_HIGHLIGHTED(_pBtnWdg, _b) \
	(_pBtnWdg)->WdgBase.Flags = ((_pBtnWdg)->WdgBase.Flags&(~BTN_WDG_MASK_HIGHLIGHTED))|(((u32)_b)<<BTN_WDG_FLAG_HIGHLIGHTED)
#define BTN_WDG_SET_DISABLE_DISPLAY_TEXT(_pBtnWdg, _b) \
	(_pBtnWdg)->WdgBase.Flags = ((_pBtnWdg)->WdgBase.Flags&(~BTN_WDG_MASK_DISABLE_DISPLAY_TEXT))|(((u32)_b)<<BTN_WDG_FLAG_DISABLE_DISPLAY_TEXT)
#define BTN_WDG_SET_DISPLAY_DISABLE_BIDI(_pBtnWdg, _b) \
    (_pBtnWdg)->WdgBase.Flags = ((_pBtnWdg)->WdgBase.Flags&(~BTN_WDG_MASK_DISPALY_DISABLE_BIDI))|(((u32)_b)<<BTN_WDG_FLAG_DISPLAY_DISABLE_BIDI)
#ifdef __TOUCH_SCREEN_MMI__
#define BTN_WDG_SET_DISABLE_TOUCH(_pBtnWdg, _b) \
	(_pBtnWdg)->WdgBase.Flags = ((_pBtnWdg)->WdgBase.Flags&(~BTN_WDG_MASK_DISABLE_TOUCH))|(((u32)_b)<<BTN_WDG_FLAG_DISABLE_TOUCH)
#define BTN_WDG_SET_TOUCH_PRESSED(_pBtnWdg, _b) \
	(_pBtnWdg)->WdgBase.Flags = ((_pBtnWdg)->WdgBase.Flags&(~BTN_WDG_MASK_TOUCH_PRESSED))|(((u32)_b)<<BTN_WDG_FLAG_TOUCH_PRESSED)
#define BTN_WDG_SET_TOUCH_VALID(_pBtnWdg, _b) \
	(_pBtnWdg)->WdgBase.Flags = ((_pBtnWdg)->WdgBase.Flags&(~BTN_WDG_MASK_TOUCH_VALIDATION))|(((u32)_b)<<BTN_WDG_FLAG_TOUCH_VALIDATION)
#define BTN_WDG_SET_ITEM_PRESSED(_pBtnWdg, _b) \
	(_pBtnWdg)->WdgBase.Flags = ((_pBtnWdg)->WdgBase.Flags&(~BTN_WDG_MASK_ITEM_PRESSED))|(((u32)_b)<<BTN_WDG_FLAG_ITEM_PRESSED)
#endif //__TOUCH_SCREEN_MMI__

// RELOAD flag
enum
{
	BTN_WDG_RELOAD_FLAG_START = 0,
	BTN_WDG_RELOAD_FLAG_UNPRESSED_TXTCOLOR = BTN_WDG_RELOAD_FLAG_START,   ///< stUnPrsdTxtColor
	BTN_WDG_RELOAD_FLAG_PRESSED_TXTCOLOR,	///< stPrsdTxtColor
	BTN_WDG_RELOAD_FLAG_FONTCATE,	///< FontCat
	BTN_WDG_RELOAD_FLAG_FONTTYPE,	///< FontType
	BTN_WDG_RELOAD_TEXT_ALIGN,	///<
	BTN_WDG_RELOAD_FLAG_END
};

/**
* Flag Mask
*/
#define BTN_WDG_RELOAD_MASK_UNPRESSED_TXTCOLOR         (1<<BTN_WDG_RELOAD_FLAG_UNPRESSED_TXTCOLOR)
#define BTN_WDG_RELOAD_MASK_PRESSED_TXTCOLOR        (1<<BTN_WDG_RELOAD_FLAG_PRESSED_TXTCOLOR)
#define BTN_WDG_RELOAD_MASK_FONTCATE         (1<<BTN_WDG_RELOAD_FLAG_FONTCATE)
#define BTN_WDG_RELOAD_MASK_FONTTYPE         (1<<BTN_WDG_RELOAD_FLAG_FONTTYPE)
#define BTN_WDG_RELOAD_MASK_TEXTALIGN         (1<<BTN_WDG_RELOAD_TEXT_ALIGN)
/**
* Macro to get flag value
*/
#define BTN_WDG_UNPRESSED_TXTCOLOR_IS_MODIFIED(_pWdg) \
    (boolean)(((_pWdg)->nReloadRCFlag&BTN_WDG_RELOAD_MASK_UNPRESSED_TXTCOLOR)>>BTN_WDG_RELOAD_FLAG_UNPRESSED_TXTCOLOR)
#define BTN_WDG_PRESSED_TXTCOLOR_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&BTN_WDG_RELOAD_MASK_PRESSED_TXTCOLOR)>>BTN_WDG_RELOAD_FLAG_PRESSED_TXTCOLOR)
#define BTN_WDG_FONTCATE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&BTN_WDG_RELOAD_MASK_FONTCATE)>>BTN_WDG_RELOAD_FLAG_FONTCATE)
#define BTN_WDG_FONTTYPE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&BTN_WDG_RELOAD_MASK_FONTTYPE)>>BTN_WDG_RELOAD_FLAG_FONTTYPE)
#define BTN_WDG_TEXTALIGN_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&BTN_WDG_RELOAD_MASK_TEXTALIGN)>>BTN_WDG_RELOAD_TEXT_ALIGN)
/**
* Macro to Set flag value
*/
#define BTN_WDG_UNPRESSED_TXTCOLOR_SET_MODIFIED(_pWdg, _b) \
    (_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~BTN_WDG_RELOAD_MASK_UNPRESSED_TXTCOLOR))|(((u32)_b)<<BTN_WDG_RELOAD_FLAG_UNPRESSED_TXTCOLOR)
#define BTN_WDG_PRESSED_TXTCOLOR_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~BTN_WDG_RELOAD_MASK_PRESSED_TXTCOLOR))|(((u32)_b)<<BTN_WDG_RELOAD_FLAG_PRESSED_TXTCOLOR)
#define BTN_WDG_FONTCATE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~BTN_WDG_RELOAD_MASK_FONTCATE))|(((u32)_b)<<BTN_WDG_RELOAD_FLAG_FONTCATE)
#define BTN_WDG_FONTTYPE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~BTN_WDG_RELOAD_MASK_FONTTYPE))|(((u32)_b)<<BTN_WDG_RELOAD_FLAG_FONTTYPE)
#define BTN_WDG_TEXTALIGN_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~BTN_WDG_RELOAD_MASK_TEXTALIGN))|(((u32)_b)<<BTN_WDG_RELOAD_TEXT_ALIGN)

/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret ButtonWidget_New(MAE_ClsId ClsID,void **ppObj);
__SLDPM_FREE__ boolean _ButtonWdg_DefHandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret ButtonWidgetStructCtor(_ButtonWidget_t *pThis);
__SLDPM_FREE__ void ButtonWidgetStructDtor(_ButtonWidget_t *pThis);

__SLDPM_FREE__ void ButtonWidget_SetSize(IWidget *pIWidget,
						  WidgetSize_t *pSize);
void ButtonWidget_GetPreferredSize(IWidget *pIWidget,
								   WidgetSize_t *pSize);
__SLDPM_FREE__ boolean ButtonWidget_IntersectOpaque(IWidget *pIWidget,
									 const Rect_t *pInRect,
									 Rect_t *pOutRect);
void ButtonWidget_Draw(IWidget *pIWidget,
					   IDispCanvas *pIDispCanvas,
					   s32 x,
					   s32 y);
__SLDPM_FREE__ MAE_Ret ButtonWidget_SetModel(IWidget *pIWidget,
							  IModel *pIModel,
							  IBase* pOwner);

static void _ButtonWidget_ReloadRC(_ButtonWidget_t *pThis, DisplayMode_e nDispMode);

#endif //__MMI_WDG_BUTTON_PRIV_H__
/*=============================================================*/
// end of file
