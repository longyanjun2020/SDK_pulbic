/**
 * @file mmi_wdg_indicator_priv.h
 * @brief This file defines the data structure of a indicator widget and function prototype for implementation.
 *
 * @version $Id: mmi_wdg_indicatorpriv.h 25372 2009-03-11 08:10:22Z mark.yang $
 */
#ifndef __MMI_WDG_INDICATOR_PRIV_H__
#define __MMI_WDG_INDICATOR_PRIV_H__
/*=============================================================*/
// include
/*=============================================================*/
#include "mae_widgetbase.h"

/*=============================================================*/
// type and define
/*=============================================================*/
enum {
	INDICATOR_WDG_FG_OFFSET_LEFT = 0,
	INDICATOR_WDG_FG_OFFSET_RIGHT,
	INDICATOR_WDG_FG_OFFSET_TOP,
	INDICATOR_WDG_FG_OFFSET_BOTTOM,
	INDICATOR_WDG_FG_OFFSET_NUM
};

#ifdef __DOWNLOAD_PROGRESS__
enum {
	INDICATOR_WDG_DWN_OFFSET_LEFT = 0,
	INDICATOR_WDG_DWN_OFFSET_RIGHT,
	INDICATOR_WDG_DWN_OFFSET_TOP,
	INDICATOR_WDG_DWN_OFFSET_BOTTOM,
	INDICATOR_WDG_DWN_OFFSET_NUM
};
#endif	//__DOWNLOAD_PROGRESS__

enum {
	INDICATOR_WDG_IMG_BG = 0,
#ifdef __DOWNLOAD_PROGRESS__
	INDICATOR_WDG_IMG_DWN,
	INDICATOR_WDG_IMG_DWN_END,
#endif	//__DOWNLOAD_PROGRESS__
	INDICATOR_WDG_IMG_FG,
	INDICATOR_WDG_IMG_IND,
	INDICATOR_WDG_IMG_NUM
};
typedef u8 _IndWdgImgId_et;

/**
* Main structure for indicator widget
*/
typedef struct {
	WidgetBaseEx_t    WdgBase;
	WdgLayoutStyle_t  nLayoutStyle;
	IImage*           apImg[INDICATOR_WDG_IMG_NUM]; ///< background, foreground and indicator image bitmap
	ModelListener_t   DataMdlLsn;        ///< Data Model listener.
	s32               IndCenterPos;      ///< x or y position in this widget
	u8                aFGOffset[INDICATOR_WDG_FG_OFFSET_NUM];
	u8                IndOffset;

#ifdef __DOWNLOAD_PROGRESS__
	s32               DwnProgressStartPos;
	s32               DwnProgressEndPos;
	boolean           isDwnProgressEnd;
	boolean           isDisableIndMoveBoundaryChk;
	u8                aDWNOffset[INDICATOR_WDG_DWN_OFFSET_NUM];
	u8                DwnEndOffset;
#endif	//__DOWNLOAD_PROGRESS__

#ifdef __TOUCH_SCREEN_MMI__
	ITouchSrv         *pITouchSrv;
#endif

} _IndicatorWidget_st;


//Flags
enum
{
	INDICATOR_WDG_FLAG_START = WDG_BASE_FLAG_END,
#ifdef __TOUCH_SCREEN_MMI__
	INDICATOR_WDG_FLAG_DISABLE_TOUCH,    ///< To enable or disable handle touch event
	INDICATOR_WDG_FLAG_TOUCH_PRESSED,    ///< To indicate if touch pressed now.
#endif //__TOUCH_SCREEN_MMI__
	INDICATOR_WDG_FLAG_END
};

//Mask
#ifdef __TOUCH_SCREEN_MMI__
#define INDICATOR_WDG_MASK_DISABLE_TOUCH          (1<<INDICATOR_WDG_FLAG_DISABLE_TOUCH)
#define INDICATOR_WDG_MASK_TOUCH_PRESSED          (1<<INDICATOR_WDG_FLAG_TOUCH_PRESSED)
#endif //__TOUCH_SCREEN_MMI__

//Get flag value
#ifdef __TOUCH_SCREEN_MMI__
#define INDICATOR_WDG_IS_DISABLE_TOUCH(_pIndicatorWdg) \
	(boolean)(((_pIndicatorWdg)->WdgBase.Flags&INDICATOR_WDG_MASK_DISABLE_TOUCH)>>INDICATOR_WDG_FLAG_DISABLE_TOUCH)
#define INDICATOR_WDG_IS_TOUCH_PRESSED(_pIndicatorWdg) \
	(boolean)(((_pIndicatorWdg)->WdgBase.Flags&INDICATOR_WDG_MASK_TOUCH_PRESSED)>>INDICATOR_WDG_FLAG_TOUCH_PRESSED)
#endif //__TOUCH_SCREEN_MMI__

//Set flag value
#ifdef __TOUCH_SCREEN_MMI__
#define INDICATOR_WDG_DISALBE_TOUCH(_pWdg, _b) \
	(_pWdg)->WdgBase.Flags = ((_pWdg)->WdgBase.Flags&(~INDICATOR_WDG_MASK_DISABLE_TOUCH))|(((u32)_b)<<INDICATOR_WDG_FLAG_DISABLE_TOUCH)
#define INDICATOR_WDG_SET_TOUCH_PRESSED(_pWdg, _b) \
	(_pWdg)->WdgBase.Flags = ((_pWdg)->WdgBase.Flags&(~INDICATOR_WDG_MASK_TOUCH_PRESSED))|(((u32)_b)<<INDICATOR_WDG_FLAG_TOUCH_PRESSED)
#endif //__TOUCH_SCREEN_MMI__

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAERet_t IndicatorWidget_New(MAEClsId_t ClsID, void **ppObj);
boolean IndicatorWidget_DefHandleEvent(IWidget *pIWidget, MAEEvent_t evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAERet_t _WdgIndicatorConstructor(_IndicatorWidget_st *pThis);
void _WdgIndicatorDestructor(_IndicatorWidget_st *pThis);
void IndicatorWidget_SetSize(IWidget *pIWidget, WidgetSize_t *pSize);
void IndicatorWidget_GetPreferredSize(IWidget *pIWidget, WidgetSize_t *pSize);
void IndicatorWidget_Draw(IWidget *pIWidget, IDispCanvas *pIDispCanvas, s32 x, s32 y);
MAERet_t IndicatorWidget_SetModel(IWidget *pIWidget, IModel *pIModel, IBase *pOwner);

#endif //__MMI_WDG_INDICATOR_PRIV_H__
/*=============================================================*/
// end of file
