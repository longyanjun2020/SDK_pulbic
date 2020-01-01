/**
* @file mmi_wdg_text_priv.h
* @brief This file defines the data structure of a text widget and function prototype for implementation.
*
* @version $Id: mmi_wdg_text_priv.h 38441 2009-08-24 09:23:19Z bill.pan $
*/
#ifndef __MMI_WDG_TEXT_PRIV_H__
#define __MMI_WDG_TEXT_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_widgetbase.h"
#include "mmi_wdg_text.h"
#include "mmi_mae_text.h"

#define TEXTWDG_UPDATE_SHORT_TIME  3    ///< A short time timer for updating the sliding text

/*=============================================================*/
// type and define
/*=============================================================*/
enum
{
    TXT_WDG_RELOAD_FLAG_START = 0,
    TXT_WDG_RELOAD_FLAG_TXTALIGN = TXT_WDG_RELOAD_FLAG_START,   ///< textAlign
	TXT_WDG_RELOAD_FLAG_TXTLAYOUT,	///< textLayout
	TXT_WDG_RELOAD_FLAG_ALIGNPRIORITY,	///< AlignPriority
	TXT_WDG_RELOAD_FLAG_LANGDIR,	///< nLangDir
	TXT_WDG_RELOAD_FLAG_COLOR,	///< color
	TXT_WDG_RELOAD_FLAG_FONTINFO,	///< fontInfo
	TXT_WDG_RELOAD_FLAG_SLIDEINFO,	///< slideInfo
    TXT_WDG_RELOAD_FLAG_END
};

enum{
    TXT_WDG_IS_SLIDING  =0x01,
    TXT_WDG_FORCE_SLIDE =0x02,
    TXT_WDG_AUTO_ANIMATE=0x04,
    TXT_WDG_SLIDE_SUSPEND       =0x10,
    TXT_WDG_SLIDE_END_SUSPEND   =0x20,
}; //For SlideFlag in TextSlideInfo.

#define TXT_WDG_IS_SLIDING(SlideFlag)           (0!=(SlideFlag & TXT_WDG_IS_SLIDING))
#define TXT_WDG_IS_AUTO_ANIMATE(SlideFlag)      (0!=(SlideFlag & TXT_WDG_AUTO_ANIMATE))
#define TXT_WDG_IS_FORCE_SLIDE(SlideFlag)       (0!=(SlideFlag & TXT_WDG_FORCE_SLIDE))

#define TXT_WDG_IS_ALIGN_FIRST(AlignPriority)   (TEXTWDG_ALIGN_FIRST==(AlignPriority))

typedef struct {
	WidgetBaseEx_t  WdgBase;        ///< Use WidgetBaseEx_t as base structure, and support border/padding
	WidgetSize_t    PreferredContentSize;
	TextFontInfo fontInfo;
	TextSlideInfo slideInfo;
	u8 textAlign;
	u8 textLayout;
	u8 AlignPriority;   //< if the align priority > break line priority: default is break > align
	u8 nLangDir;

	u16 IsInGridItem : 1;		///< To indicate if this text is an item widget in grid widget
	u16 bLinked : 1;            ///< Link state.
	u16 bTouched : 1;           ///< Touch state
	u16 bLinkAutoUnderline : 1; ///< Auto use underline text when link addr set
	u16 bWithoutBidi : 1;
	u16 nReloadRCFlag;		///< the flag record which rc property has been modified outside, those are not reload

	MAE_WChar *pwLinkAddr;
	u32 nHighLightWidth;
    s32 nFocusPos;
    RGBColor_t color;
    u32 nTextOffset;
    ITextTable *pITextTable;
    u32 nTextLineNum;
#ifdef __TOUCH_SCREEN_MMI__
	ITouchSrv *pITouchSrv;  //< Touch service
#endif //__TOUCH_SCREEN_MMI__
} TextWidget_t;

/**
* Flag Mask
*/
#define TXT_WDG_RELOAD_MASK_TXTALIGN         (1<<TXT_WDG_RELOAD_FLAG_TXTALIGN)
#define TXT_WDG_RELOAD_MASK_TXTLAYOUT        (1<<TXT_WDG_RELOAD_FLAG_TXTLAYOUT)
#define TXT_WDG_RELOAD_MASK_ALIGNPRIORITY         (1<<TXT_WDG_RELOAD_FLAG_ALIGNPRIORITY)
#define TXT_WDG_RELOAD_MASK_LANGDIR         (1<<TXT_WDG_RELOAD_FLAG_LANGDIR)
#define TXT_WDG_RELOAD_MASK_COLOR         (1<<TXT_WDG_RELOAD_FLAG_COLOR)
#define TXT_WDG_RELOAD_MASK_FONTINFO         (1<<TXT_WDG_RELOAD_FLAG_FONTINFO)
#define TXT_WDG_RELOAD_MASK_SLIDEINFO         (1<<TXT_WDG_RELOAD_FLAG_SLIDEINFO)
/**
* Macro to get flag value
*/
#define TXT_WDG_TXTALIGN_IS_MODIFIED(_pWdg) \
    (boolean)(((_pWdg)->nReloadRCFlag&TXT_WDG_RELOAD_MASK_TXTALIGN)>>TXT_WDG_RELOAD_FLAG_TXTALIGN)
#define TXT_WDG_TXTLAYOUT_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TXT_WDG_RELOAD_MASK_TXTLAYOUT)>>TXT_WDG_RELOAD_FLAG_TXTLAYOUT)
#define TXT_WDG_ALIGNPRIORITY_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TXT_WDG_RELOAD_MASK_ALIGNPRIORITY)>>TXT_WDG_RELOAD_FLAG_ALIGNPRIORITY)
#define TXT_WDG_LANGDIR_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TXT_WDG_RELOAD_MASK_LANGDIR)>>TXT_WDG_RELOAD_FLAG_LANGDIR)
#define TXT_WDG_COLOR_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TXT_WDG_RELOAD_MASK_COLOR)>>TXT_WDG_RELOAD_FLAG_COLOR)
#define TXT_WDG_FONTINFO_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TXT_WDG_RELOAD_MASK_FONTINFO)>>TXT_WDG_RELOAD_FLAG_FONTINFO)
#define TXT_WDG_SLIDEINFO_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TXT_WDG_RELOAD_MASK_SLIDEINFO)>>TXT_WDG_RELOAD_FLAG_SLIDEINFO)
/**
* Macro to Set flag value
*/
#define TXT_WDG_TXTALIGN_SET_MODIFIED(_pWdg, _b) \
    (_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TXT_WDG_RELOAD_MASK_TXTALIGN))|(((u32)_b)<<TXT_WDG_RELOAD_FLAG_TXTALIGN)
#define TXT_WDG_TXTLAYOUT_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TXT_WDG_RELOAD_MASK_TXTLAYOUT))|(((u32)_b)<<TXT_WDG_RELOAD_FLAG_TXTLAYOUT)
#define TXT_WDG_ALIGNPRIORITY_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TXT_WDG_RELOAD_MASK_ALIGNPRIORITY))|(((u32)_b)<<TXT_WDG_RELOAD_FLAG_ALIGNPRIORITY)
#define TXT_WDG_LANGDIR_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TXT_WDG_RELOAD_MASK_LANGDIR))|(((u32)_b)<<TXT_WDG_RELOAD_FLAG_LANGDIR)
#define TXT_WDG_COLOR_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TXT_WDG_RELOAD_MASK_COLOR))|(((u32)_b)<<TXT_WDG_RELOAD_FLAG_COLOR)
#define TXT_WDG_FONTINFO_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TXT_WDG_RELOAD_MASK_FONTINFO))|(((u32)_b)<<TXT_WDG_RELOAD_FLAG_FONTINFO)
#define TXT_WDG_SLIDEINFO_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TXT_WDG_RELOAD_MASK_SLIDEINFO))|(((u32)_b)<<TXT_WDG_RELOAD_FLAG_SLIDEINFO)

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret TextWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean TextWidget_DefHandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret _WdgTextConstructor(TextWidget_t *pThis, MAEClsId_t clsId);
void _WdgTextDestructor(TextWidget_t *pThis);

void TextWidget_SetSize(IWidget *pIWidget, WidgetSize_t *pSize);
void TextWidget_GetPreferredSize(IWidget *pIWidget, WidgetSize_t *pSize);
void TextWidget_DefDraw(IWidget *pIWidget, IDispCanvas *pIDispCanvas, s32 x, s32 y);
boolean TextWidget_IntersectOpaque(IWidget *pIWidget, const Rect_t *pInRect, Rect_t *pOutRect);
MAE_Ret TextWidget_SetModel(IWidget *pIWidget, IModel *pIModel, IBase* pOwner);

void TextWidget_GetPreferredContentSize(TextWidget_t *pThis, WidgetSize_t *pSize);
void TextWidget_GetPreferredSizeWithMultiLineFlag(TextWidget_t *pThis, WidgetSize_t *pSize,
                                        boolean bMultiLine, /*if the layout is multi-line*/
                                        boolean bAllLine,   /*when bMultiLine is TRUE => if the size consider the line that can't fit in the widget height */
                                        boolean bFitWidth); /*when bMultiLine is TRUE => The width consider the fit width or the widget width*/

void TextWidget_ModelListener(void *pUsrData, ModelEvent_t *pMdlEvent);
void TextWidget_ResetSlideEndOffset(TextWidget_t *pThis);
void TextWidget_ResetCurrentOffset(TextWidget_t *pThis, u32 SlideStatus, boolean bResetSlideEnd, boolean bResetStepRemainTime);
MAE_Ret TextWidget_GetDrawLineX(TextWidget_t *pThis,
								IDisplay *pIDisplay,
								MAE_WChar* pwText,
								u32 nTextLen,
								u32 nWidth,
								u32 *pFits,
								u32 *pPixcel,
								u32 *pEllPix,
								boolean bLastLine,
								s32 *pDrawX);

MAE_Ret TextWidget_GetDrawLineY(TextWidget_t *pThis,
								IDisplay *pIDisplay,
								MAE_WChar* pwText,
								u32 nTextLen,
								u32 nWidth,
								u32 nHeight,
								u16 *pRows,
								u16 *pRowHeight,
								s32 *pDrawY);
MAE_Ret TextWidget_AlignmentCenterGetLeftSpace(TextWidget_t *pThis, s32 *pSize);
MAE_Ret TextWidget_AlignmentMiddleGetTopSpace(TextWidget_t *pThis, s32 *pSize);

s32 TextWidget_GetSlideEndOffset(TextWidget_t *pThis, u32 nSlideSize);

boolean TextWidget_TextSlideOnOff(TextWidget_t *pThis, boolean bSlideOn, boolean bResetOffset, boolean bResetInvalid);
void TextWidget_TextSlideCallBack(TextWidget_t *pThis, void * pData);
void TextWidget_TextSlideEndCallBack(TextWidget_t *pThis, void * pData);
void TextWidget_AutoAnimateCheck(TextWidget_t *pThis, boolean bConsiderForceSlide, boolean bKeepStatusReset, boolean bChangeStatusReset, boolean bResetInvalid);
boolean TextWidget_CheckNeedAnimate(TextWidget_t *pThis);
void TextWidget_SendSlideNotify(TextWidget_t *pThis,
								u32 SlideStatus);
MAE_Ret TextWidget_StopSlideText(TextWidget_t *pThis, u32 StopSlideStatus, u8 NewSlideFlag);

#endif //__MMI_WDG_TEXT_PRIV_H__
/*=============================================================*/
// end of file
