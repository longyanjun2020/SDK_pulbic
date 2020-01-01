/**
 * @file:  mmi_wdg_textbubble_priv.h
 * @brief: This file defines the data structure of text bubble widget and function prototypes.
 *
 * @version: mmi_wdg_textbubble_priv.h  2011-06-27 evan.chang
 */

#ifndef __MMI_WDG_TEXTBUBBLE_PRIV_H__
#define __MMI_WDG_TEXTBUBBLE_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_widgetbase.h"

/*=============================================================*/
// type and define
/*=============================================================*/
enum {
    TEXTBUBBLE_WDG_IMG_TOP_LEFT = 0,
    TEXTBUBBLE_WDG_IMG_TOP_MID,
    TEXTBUBBLE_WDG_IMG_TOP_RIGHT,
    TEXTBUBBLE_WDG_IMG_CENTER_LEFT,
    TEXTBUBBLE_WDG_IMG_CENTER_MID,
    TEXTBUBBLE_WDG_IMG_CENTER_RIGHT,
    TEXTBUBBLE_WDG_IMG_BOTTOM_LEFT,
    TEXTBUBBLE_WDG_IMG_BOTTOM_MID,
    TEXTBUBBLE_WDG_IMG_BOTTOM_RIGHT,
	TEXTBUBBLE_WDG_IMG_TOTAL_NUM
};
typedef u8 _TextBubbleWdgImgIndex_et;

// Main structure for text bubble widget
typedef struct {
	WidgetBaseEx_t    WdgBase;
	IWidget			  *pITextWidget;
	IImage*           apImg[TEXTBUBBLE_WDG_IMG_TOTAL_NUM];
    Rect_t            aImgDrawRect[TEXTBUBBLE_WDG_IMG_TOTAL_NUM];
    Pos_t             WdgBasePosition;
    Pos_t             TextWidgetPosOffset;
    WidgetSize_t      TextWidgetSize;
    u32               TextWidgetLineHeight;

#ifdef __TOUCH_SCREEN_MMI__
	ITouchSrv         *pITouchSrv;
#endif

} _TextBubbleWidget_st;


#ifdef __TOUCH_SCREEN_MMI__

//Flags
enum
{
	TEXTBUBBLE_WDG_FLAG_START = WDG_BASE_FLAG_END,
	TEXTBUBBLE_WDG_FLAG_DISABLE_TOUCH,    ///< To enable or disable handle touch event
	TEXTBUBBLE_WDG_FLAG_TOUCH_PRESSED,    ///< To indicate if touch pressed now.
	TEXTBUBBLE_WDG_FLAG_END
};

//Mask
#define TEXTBUBBLE_WDG_MASK_DISABLE_TOUCH          (1<<TEXTBUBBLE_WDG_FLAG_DISABLE_TOUCH)
#define TEXTBUBBLE_WDG_MASK_TOUCH_PRESSED          (1<<TEXTBUBBLE_WDG_FLAG_TOUCH_PRESSED)

//Get flag value
#define TEXTBUBBLE_WDG_IS_DISABLE_TOUCH(_pTextBubbleWdg) \
	(boolean)(((_pTextBubbleWdg)->WdgBase.Flags&TEXTBUBBLE_WDG_MASK_DISABLE_TOUCH)>>TEXTBUBBLE_WDG_FLAG_DISABLE_TOUCH)
#define TEXTBUBBLE_WDG_IS_TOUCH_PRESSED(_pTextBubbleWdg) \
	(boolean)(((_pTextBubbleWdg)->WdgBase.Flags&TEXTBUBBLE_WDG_MASK_TOUCH_PRESSED)>>TEXTBUBBLE_WDG_FLAG_TOUCH_PRESSED)

//Set flag value
#define TEXTBUBBLE_WDG_DISALBE_TOUCH(_pWdg, _b) \
	(_pWdg)->WdgBase.Flags = ((_pWdg)->WdgBase.Flags&(~TEXTBUBBLE_WDG_MASK_DISABLE_TOUCH))|(((u32)_b)<<TEXTBUBBLE_WDG_FLAG_DISABLE_TOUCH)
#define TEXTBUBBLE_WDG_SET_TOUCH_PRESSED(_pWdg, _b) \
	(_pWdg)->WdgBase.Flags = ((_pWdg)->WdgBase.Flags&(~TEXTBUBBLE_WDG_MASK_TOUCH_PRESSED))|(((u32)_b)<<TEXTBUBBLE_WDG_FLAG_TOUCH_PRESSED)

#endif //__TOUCH_SCREEN_MMI__

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAERet_t TextBubbleWidget_New(MAEClsId_t ClsID, void **ppObj);
boolean TextBubbleWidget_DefHandleEvent(IWidget *pIWidget, MAEEvent_t evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAERet_t TextBubbleWidget_Ctor(_TextBubbleWidget_st *pThis);
void TextBubbleWidget_Dtor(_TextBubbleWidget_st *pThis);
void TextBubbleWidget_SetWdgBaseSize(IWidget *pIWidget, WidgetSize_t *pSize);
void TextBubbleWidget_Draw(IWidget *pIWidget, IDispCanvas *pIDispCanvas, s32 x, s32 y);

#endif //__MMI_WDG_TEXTBUBBLE_PRIV_H__
/*=============================================================*/
// end of file
