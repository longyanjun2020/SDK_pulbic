/**
* @file	   mmi_wdg_pulldown_priv.h
* @version $Id: mmi_wdg_pulldown_priv.h 28701 2009-04-16 15:12:45Z steve.lee $
*
* @brief	This is a private header file for Pull-Down widget implementation.
*
*/
#ifndef __MMI_WDG_PULLDOWN_PRIV_H__
#define __MMI_WDG_PULLDOWN_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_pulldown.h"
#include "mae_widgetbase.h"

/*=============================================================*/
// type and define
/*=============================================================*/
//typedef struct {
//	IWidget        *pImageTextWdg;     ///< An image-text widget to display seleted item.
//	u32            nIndex;             ///< The index of displayed item
//	RGBColor_t     FcsBgColor;         ///< The background color when widget focused.
//} _SeletedItemInfo_t;

//typedef struct {
//	IWidget        *pBitmapWdg;         ///< A bitmap widget to display down arrow
//	IBitmap        *pBmp;               ///< An Ibitmap object for down arrow icon
//	u16             nWidth;             ///< The width of arrow
//} _ArrowInfo_t;

typedef struct {
	IWidget         *pItemWdg;          ///< A image-text widget as item widget in list
	IWidget         *pListWdg;          ///< A list widget pointer
	IWidget         *pScrlWdg;          ///< A scrollbar widget pointer
	WidgetHandler_t ScrollWdgHdlData;   ///< to hook scroll bar widget's event
	RGBColor_t      BorderColor;        ///< The border color of the scrollbar widget???
	u16             nMaxItemNum;        ///< the max item number in the list
	u16             nSingleItemHeight;  ///< the height of single item
} _DropListInfo_t;
/**
* The main structure for implementation of Pull-down widget.
*/
typedef struct {
	WidgetBaseEx_t      WdgBase;			///< Using WidgetBaseEx_t as base structure.
	PullDownWdgMode_et  nMode;
	ModelListener_t     MdlLsn;				///< Model listener for listening the list model changed
	//_SeletedItemInfo_t  stSelItem;          ///< All information for display the seleted item
	//_ArrowInfo_t        stArrow;            ///< All information for displaying the arrow
	IWidget             *pSelItemWdg;
	u32                 nIndex;
	RGBColor_t          FcsBgColor;         ///< The background color when widget focused. It also be the highlighted background color for drop list
	RGBColor_t          UnFcsBgColor;       ///< The background color when widget unfocused.
	RGBColor_t          TextColor;          ///< text color
	RGBColor_t          HlTextColor;        ///< highlight text color
	IWidget             *pArrowWdg;
	IImage             *pDownImg;
#ifdef __TOUCH_SCREEN_MMI__
	IImage             *pDownImgPressed;
	ITouchSrv           *pITouchSrv;            ///< Touch Service
#endif //__TOUCH_SCREEN_MMI__
	_DropListInfo_t     stDropList;         ///< All information for displaying the list
	FontCategory_t      nFontCat;
	u32      			nFontSize;			///< Valid in vector font
	u16                 nArrowWidth;        ///< the width of arrow
	MAE_Key_t           nUpKeyCode;
	MAE_Key_t           nDownKeyCode;
	MAE_Key_t           nToggleDropListKeyCode;

	/// below are all status flags
	u32                 bDisableKeyEvt : 1; ///< 1: disable to handle key event, 0: enable to handle key event
	u32                 bIsListUplifted : 1;    ///< a flag to indicate if the dropping list is uplifted to root-container.
	u32                 bIsForceRemoved : 1;    ///< a flag to indicate if the dropping list forces to remove by container.
#ifdef __TOUCH_SCREEN_MMI__
	u32                 bTouchPressed : 1;  ///< indicate if this widget is pressed by touch
#endif //__TOUCH_SCREEN_MMI__
} _PullDownWidget_t;

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAERet_t PullDownWidget_New(MAEClsId_t ClsID, void **ppObj);
boolean _PullDownWdg_DefHandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAERet_t _WdgPullDownConstructor(_PullDownWidget_t *pThis);
void _WdgPullDownDestructor(_PullDownWidget_t *pThis);
void PullDownWidget_SetSize(IWidget *pIWidget,   ///< An IWidget object instance
							  WidgetSize_t *pSize  ///< A pointer of widget size to keep new size
							  );
void PullDownWidget_GetPreferredSize(IWidget *pIWidget,   ///< An IWidget object instance
                                     WidgetSize_t *pSize  ///< A pointer of widget size to return preferred size
                                     );
boolean PullDownWidget_IntersectOpaque(IWidget *pIWidget,
										 const Rect_t *pInRect,
										 Rect_t *pOutRect);
MAERet_t PullDownWidget_SetModel(IWidget *pIWidget,
                                  IModel *pIModel,
                                  IBase* pOwner
                                  );
void _PullDownWdg_DefDraw(IWidget *pIWidget,
						  IDispCanvas *pIDispCanvas,
						  s32 x,
						  s32 y
						  );
#endif //__MMI_WDG_PULLDOWN_PRIV_H__
/*=============================================================*/
// end of file
