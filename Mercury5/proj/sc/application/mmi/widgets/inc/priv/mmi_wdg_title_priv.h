#ifndef __MMI_WDG_TITLE_PRIV_H__
#define __MMI_WDG_TITLE_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mae_decoratorbase.h"
#include "mmi_wdg_title.h"
#include "mae_wdgbackground.h"

#include "mmi_mae_image.h"
/*=============================================================*/
// type and define
/*=============================================================*/
enum
{
	TITLE_WDG_RELOAD_FLAG_START = 0,
	TITLE_WDG_RELOAD_FLAG_ELMNTVISABLE = TITLE_WDG_RELOAD_FLAG_START,
	TITLE_WDG_RELOAD_FLAG_ELMNTALIGN,
	TITLE_WDG_RELOAD_FLAG_SMSALIGN,
	TITLE_WDG_RELOAD_FLAG_SMSFONECATE,
	TITLE_WDG_RELOAD_FLAG_TEXTFONECATE,
	TITLE_WDG_RELOAD_FLAG_TEXTFONETYPE,
	TITLE_WDG_RELOAD_FLAG_LANGDIR,	///< nLangDir
	TITLE_WDG_RELOAD_FLAG_BGIMG,
	TITLE_WDG_RELOAD_FLAG_BGCOLOR,
	TITLE_WDG_RELOAD_FLAG_OUTLINECOLOR,
	TITLE_WDG_RELOAD_FLAG_TEXTCOLOR,
	TITLE_WDG_RELOAD_FLAG_SMSCOLOR,
	TITLE_WDG_RELOAD_FLAG_ELMNTWIDTH,
	TITLE_WDG_RELOAD_FLAG_SIZE,
	TITLE_WDG_RELOAD_FLAG_ELEMTPADDING,
	TITLE_WDG_RELOAD_FLAG_LPADDING,
	TITLE_WDG_RELOAD_FLAG_RPADDING,
	TITLE_WDG_RELOAD_FLAG_END
};
typedef struct ViewMdlListener_tag ViewMdlListener_t;

enum
{
	PROP_TITLE_WDG_SMSTXT_TEXT = PROP_WIDGET_IDV_END,
	PROP_TITLE_WDG_SMSTXT_ID
};

struct ViewMdlListener_tag
{
	ModelListener_t    MdlListener;
	ViewMdlListener_t *pNext;
};

enum
{
	TITLEWDG_VISIBLE_FLAG = TITLEWDG_ELMNT_ID_TOTAL,
	TITLEWDG_FIXSIZE_FLAG
};

#ifdef __TOUCH_SCREEN_MMI__
enum
{
	TITLEWDG_TS_TITLEICON_PRESSED_FLAG = 0,
	TITLEWDG_TS_TITLETEXT_PRESSED_FLAG,
	TITLEWDG_TS_SMSTEXT_PRESSED_FLAG,
#ifdef __QWERTY_KEYPAD_INPUTMETHOD__
	TITLEWDG_TS_ALTICON_PRESSED_FLAG,
#endif	
	TITLEWDG_TS_SOFTKBICON_PRESSED_FLAG,
	TITLEWDG_TS_INPUTICON_PRESSED_FLAG
};

#define TITLEWDG_TS_ELMNT_PRESSED_MSK(_id)  (1<<_id)

#endif /* __TOUCH_SCREEN_MMI__ */
/*
#define TITLEWDG_VISIBLE_MSK        0x00000001
#define TITLEWDG_FIXSIZE_MSK        0x00000002
#define TITLEWDG_TITLEICON_VIS_MSK  0x00000004
#define TITLEWDG_TITLETEXT_VIS_MSK  0x00000008
#define TITLEWDG_SMSTEXT_VIS_MSK    0x00000010
#define TITLEWDG_INPUTICON_VIS_MSK  0x00000020
*/
#ifdef __TOUCH_SCREEN_MMI__

//#define TITLEWDG_SOFTKBICON_VIS_MSK 0x00000040

/*
#define TITLEWDG_TS_FLAG_TITLEICON_PRESSED 0x00000001
#define TITLEWDG_TS_FLAG_TITLETEXT_PRESSED 0x00000002
#define TITLEWDG_TS_FLAG_SMSTEXT_PRESSED   0x00000004
#define TITLEWDG_TS_FLAG_INPUTICON_PRESSED 0x00000008
#define TITLEWDG_TS_FLAG_SOFTKBICON_PRESSED 0x00000010
*/

#endif /* __TOUCH_SCREEN_MMI__ */

/* Title element data !!from left to right!! */
typedef union {
	IImage     *pImage;
	MAE_WChar  *pText;
} TitleElmntData;

typedef struct {
	TitleElmntData ElmntData[TITLEWDG_ELMNT_ID_TOTAL];
} TitleElmntInfo;

typedef struct {
	DecoratorEx_t      DecBase;
	IWidget           *pElmntWdg[TITLEWDG_ELMNT_ID_TOTAL];
	TitleElmntData     ElmntData[TITLEWDG_ELMNT_ID_TOTAL];
/*
	IWidget *pTitleIconWdg;   ///< Image/Bitmap Widget
	IWidget *pTitleTextWdg;   ///< Text Widget
	IWidget *pSMSTextWdg;     ///< Text Widget
	IWidget *pInputIconWdg;   ///< Image/Bitmap Widget
#ifdef __TOUCH_SCREEN_MMI__
	IWidget *pSoftKBIconWdg;  ///< Image/Bitmap Widget
#endif
*/
	u32      VisFlags;

	ModelListener_t    DataMdlListener;
	ViewMdlListener_t *pViewMdlListener;
	WdgItemBG_t  TitleBg;   ///< Background color/image for title area
    u8 nChildLangDir;//add for store the lang direction

	u32 nReloadRCFlag;		///< the flag record which rc property has been modified outside, those will not to reload

#ifdef __TOUCH_SCREEN_MMI__
	u32      TSFlag;
#endif /* __TOUCH_SCREEN_MMI__ */
	WidgetSize_t   tTitleSize;
	u16 nTitleElmntWidth[TITLEWDG_ELMNT_ID_TOTAL];
	u16 nElemtPadding;
	u16 nLeftPadding;
	u16 nRightPadding;

    boolean bAutoFitSmsText;
    u16 nTitleSmsTextMaxWidth;
} _TitleWidget_t;

#define IS_TITLE_ELMNT_VIS(_p,_id)     ((_p->VisFlags&TITLEWDG_ELMNT_MSK(_id))>>_id)

#define IS_TITLE_VISIBLE(_p)           IS_TITLE_ELMNT_VIS(_p,TITLEWDG_VISIBLE_FLAG)
#define IS_TITLE_FIXSIZE(_p)           IS_TITLE_ELMNT_VIS(_p,TITLEWDG_FIXSIZE_FLAG)
/*
#define IS_TITLE_TITLEICON_VIS(_p)     ((_p->VisFlags&TITLEWDG_TITLEICON_VIS_MSK)>>2)
#define IS_TITLE_TITLETEXT_VIS(_p)     ((_p->VisFlags&TITLEWDG_TITLETEXT_VIS_MSK)>>3)
#define IS_TITLE_SMSTEXT_VIS(_p)       ((_p->VisFlags&TITLEWDG_SMSTEXT_VIS_MSK)>>4)
#define IS_TITLE_INPUTICON_VIS(_p)     ((_p->VisFlags&TITLEWDG_INPUTICON_VIS_MSK)>>5)

#ifdef __TOUCH_SCREEN_MMI__
#define IS_TITLE_SOFTKBICON_VIS(_p)    ((_p->VisFlags&TITLEWDG_SOFTKBICON_VIS_MSK)>>6)
#endif
*/

#define SET_TITLE_ELMNT_VIS(_p,_id,_val)     _p->VisFlags=(_p->VisFlags&(~TITLEWDG_ELMNT_MSK(_id)))|((_val)<<_id)
#define SET_TITLE_VISIBLE(_p,_val)           SET_TITLE_ELMNT_VIS(_p,TITLEWDG_VISIBLE_FLAG,_val)
#define SET_TITLE_FIXSIZE(_p,_val)           SET_TITLE_ELMNT_VIS(_p,TITLEWDG_FIXSIZE_FLAG,_val)

/*
#define SET_TITLE_VISIBLE(_p,_val)           _p->VisFlags=(_p->VisFlags&(~TITLEWDG_VISIBLE_MSK))|(_val)
#define SET_TITLE_FIXSIZE(_p,_val)           _p->VisFlags=(_p->VisFlags&(~TITLEWDG_FIXSIZE_MSK))|((_val)<<1)
#define SET_TITLE_TITLEICON_VIS(_p,_val)     _p->VisFlags=(_p->VisFlags&(~TITLEWDG_TITLEICON_VIS_MSK))|((_val)<<2)
#define SET_TITLE_TITLETEXT_VIS(_p,_val)     _p->VisFlags=(_p->VisFlags&(~TITLEWDG_TITLETEXT_VIS_MSK))|((_val)<<3)
#define SET_TITLE_SMSTEXT_VIS(_p,_val)       _p->VisFlags=(_p->VisFlags&(~TITLEWDG_SMSTEXT_VIS_MSK))|((_val)<<4)
#define SET_TITLE_INPUTICON_VIS(_p,_val)     _p->VisFlags=(_p->VisFlags&(~TITLEWDG_INPUTICON_VIS_MSK))|((_val)<<5)

#ifdef __TOUCH_SCREEN_MMI__
#define SET_TITLE_SOFTKBICON_VIS(_p,_val)     _p->VisFlags=(_p->VisFlags&(~TITLEWDG_SOFTKBICON_VIS_MSK))|((_val)<<6)
#endif
*/

/**
* Flag Mask
*/
#define	TITLE_WDG_RELOAD_MASK_ELMNTVISABLE 	(1<<TITLE_WDG_RELOAD_FLAG_ELMNTVISABLE)
#define	TITLE_WDG_RELOAD_MASK_ELMNTALIGN   	(1<<TITLE_WDG_RELOAD_FLAG_ELMNTALIGN)  
#define	TITLE_WDG_RELOAD_MASK_SMSALIGN     	(1<<TITLE_WDG_RELOAD_FLAG_SMSALIGN)    
#define	TITLE_WDG_RELOAD_MASK_SMSFONECATE  	(1<<TITLE_WDG_RELOAD_FLAG_SMSFONECATE) 
#define	TITLE_WDG_RELOAD_MASK_TEXTFONECATE 	(1<<TITLE_WDG_RELOAD_FLAG_TEXTFONECATE)
#define	TITLE_WDG_RELOAD_MASK_TEXTFONETYPE 	(1<<TITLE_WDG_RELOAD_FLAG_TEXTFONETYPE)
#define	TITLE_WDG_RELOAD_MASK_LANGDIR     	(1<<TITLE_WDG_RELOAD_FLAG_LANGDIR)     
#define	TITLE_WDG_RELOAD_MASK_BGIMG       	(1<<TITLE_WDG_RELOAD_FLAG_BGIMG)       
#define	TITLE_WDG_RELOAD_MASK_BGCOLOR     	(1<<TITLE_WDG_RELOAD_FLAG_BGCOLOR)     
#define	TITLE_WDG_RELOAD_MASK_OUTLINECOLOR	(1<<TITLE_WDG_RELOAD_FLAG_OUTLINECOLOR)
#define	TITLE_WDG_RELOAD_MASK_TEXTCOLOR   	(1<<TITLE_WDG_RELOAD_FLAG_TEXTCOLOR)   
#define	TITLE_WDG_RELOAD_MASK_SMSCOLOR    	(1<<TITLE_WDG_RELOAD_FLAG_SMSCOLOR)    
#define	TITLE_WDG_RELOAD_MASK_ELMNTWIDTH  	(1<<TITLE_WDG_RELOAD_FLAG_ELMNTWIDTH)  
#define	TITLE_WDG_RELOAD_MASK_SIZE        	(1<<TITLE_WDG_RELOAD_FLAG_SIZE)        
#define	TITLE_WDG_RELOAD_MASK_ELEMTPADDING	(1<<TITLE_WDG_RELOAD_FLAG_ELEMTPADDING)
#define	TITLE_WDG_RELOAD_MASK_LPADDING    	(1<<TITLE_WDG_RELOAD_FLAG_LPADDING)    
#define	TITLE_WDG_RELOAD_MASK_RPADDING    	(1<<TITLE_WDG_RELOAD_FLAG_RPADDING)    
/**
* Macro to get flag value
*/
#define TITLE_WDG_ELMNTVISABLE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TITLE_WDG_RELOAD_MASK_ELMNTVISABLE)>>TITLE_WDG_RELOAD_FLAG_ELMNTVISABLE)
#define TITLE_WDG_ELMNTALIGN_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TITLE_WDG_RELOAD_MASK_ELMNTALIGN)>>TITLE_WDG_RELOAD_FLAG_ELMNTALIGN)
#define TITLE_WDG_SMSALIGN_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TITLE_WDG_RELOAD_MASK_SMSALIGN)>>TITLE_WDG_RELOAD_FLAG_SMSALIGN)
#define TITLE_WDG_SMSFONECATE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TITLE_WDG_RELOAD_MASK_SMSFONECATE)>>TITLE_WDG_RELOAD_FLAG_SMSFONECATE)
#define TITLE_WDG_TEXTFONECATE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TITLE_WDG_RELOAD_MASK_TEXTFONECATE)>>TITLE_WDG_RELOAD_FLAG_TEXTFONECATE)
#define TITLE_WDG_TEXTFONETYPE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TITLE_WDG_RELOAD_MASK_TEXTFONETYPE)>>TITLE_WDG_RELOAD_FLAG_TEXTFONETYPE)
#define TITLE_WDG_LANGDIR_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TITLE_WDG_RELOAD_MASK_LANGDIR)>>TITLE_WDG_RELOAD_FLAG_LANGDIR)
#define TITLE_WDG_BGIMG_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TITLE_WDG_RELOAD_MASK_BGIMG)>>TITLE_WDG_RELOAD_FLAG_BGIMG)
#define TITLE_WDG_BGCOLOR_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TITLE_WDG_RELOAD_MASK_BGCOLOR)>>TITLE_WDG_RELOAD_FLAG_BGCOLOR)
#define TITLE_WDG_OUTLINECOLOR_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TITLE_WDG_RELOAD_MASK_OUTLINECOLOR)>>TITLE_WDG_RELOAD_FLAG_OUTLINECOLOR)
#define TITLE_WDG_TEXTCOLOR_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TITLE_WDG_RELOAD_MASK_TEXTCOLOR)>>TITLE_WDG_RELOAD_FLAG_TEXTCOLOR)
#define TITLE_WDG_SMSCOLOR_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TITLE_WDG_RELOAD_MASK_SMSCOLOR)>>TITLE_WDG_RELOAD_FLAG_SMSCOLOR)
#define TITLE_WDG_ELMNTWIDTH_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TITLE_WDG_RELOAD_MASK_ELMNTWIDTH)>>TITLE_WDG_RELOAD_FLAG_ELMNTWIDTH)
#define TITLE_WDG_SIZE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TITLE_WDG_RELOAD_MASK_SIZE)>>TITLE_WDG_RELOAD_FLAG_SIZE)
#define TITLE_WDG_ELEMTPADDING_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TITLE_WDG_RELOAD_MASK_ELEMTPADDING)>>TITLE_WDG_RELOAD_FLAG_ELEMTPADDING)
#define TITLE_WDG_LPADDING_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TITLE_WDG_RELOAD_MASK_LPADDING)>>TITLE_WDG_RELOAD_FLAG_LPADDING)
#define TITLE_WDG_RPADDING_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TITLE_WDG_RELOAD_MASK_RPADDING)>>TITLE_WDG_RELOAD_FLAG_RPADDING)

/**
* Macro to Set flag value
*/
#define TITLE_WDG_ELMNTVISABLE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TITLE_WDG_RELOAD_MASK_ELMNTVISABLE))|(((u32)_b)<<TITLE_WDG_RELOAD_FLAG_ELMNTVISABLE)
#define TITLE_WDG_ELMNTALIGN_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TITLE_WDG_RELOAD_MASK_ELMNTALIGN))|(((u32)_b)<<TITLE_WDG_RELOAD_FLAG_ELMNTALIGN)
#define TITLE_WDG_SMSALIGN_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TITLE_WDG_RELOAD_MASK_SMSALIGN))|(((u32)_b)<<TITLE_WDG_RELOAD_FLAG_SMSALIGN)
#define TITLE_WDG_SMSFONECATE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TITLE_WDG_RELOAD_MASK_SMSFONECATE))|(((u32)_b)<<TITLE_WDG_RELOAD_FLAG_SMSFONECATE)
#define TITLE_WDG_TEXTFONECATE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TITLE_WDG_RELOAD_MASK_TEXTFONECATE))|(((u32)_b)<<TITLE_WDG_RELOAD_FLAG_TEXTFONECATE)
#define TITLE_WDG_TEXTFONETYPE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TITLE_WDG_RELOAD_MASK_TEXTFONETYPE))|(((u32)_b)<<TITLE_WDG_RELOAD_FLAG_TEXTFONETYPE)
#define TITLE_WDG_LANGDIR_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TITLE_WDG_RELOAD_MASK_LANGDIR))|(((u32)_b)<<TITLE_WDG_RELOAD_FLAG_LANGDIR)
#define TITLE_WDG_BGIMG_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TITLE_WDG_RELOAD_MASK_BGIMG))|(((u32)_b)<<TITLE_WDG_RELOAD_FLAG_BGIMG)
#define TITLE_WDG_BGCOLOR_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TITLE_WDG_RELOAD_MASK_BGCOLOR))|(((u32)_b)<<TITLE_WDG_RELOAD_FLAG_BGCOLOR)
#define TITLE_WDG_OUTLINECOLOR_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TITLE_WDG_RELOAD_MASK_OUTLINECOLOR))|(((u32)_b)<<TITLE_WDG_RELOAD_FLAG_OUTLINECOLOR)
#define TITLE_WDG_TEXTCOLOR_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TITLE_WDG_RELOAD_MASK_TEXTCOLOR))|(((u32)_b)<<TITLE_WDG_RELOAD_FLAG_TEXTCOLOR)
#define TITLE_WDG_SMSCOLOR_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TITLE_WDG_RELOAD_MASK_SMSCOLOR))|(((u32)_b)<<TITLE_WDG_RELOAD_FLAG_SMSCOLOR)
#define TITLE_WDG_ELMNTWIDTH_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TITLE_WDG_RELOAD_MASK_ELMNTWIDTH))|(((u32)_b)<<TITLE_WDG_RELOAD_FLAG_ELMNTWIDTH)
#define TITLE_WDG_SIZE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TITLE_WDG_RELOAD_MASK_SIZE))|(((u32)_b)<<TITLE_WDG_RELOAD_FLAG_SIZE)
#define TITLE_WDG_ELEMTPADDING_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TITLE_WDG_RELOAD_MASK_ELEMTPADDING))|(((u32)_b)<<TITLE_WDG_RELOAD_FLAG_ELEMTPADDING)
#define TITLE_WDG_LPADDING_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TITLE_WDG_RELOAD_MASK_LPADDING))|(((u32)_b)<<TITLE_WDG_RELOAD_FLAG_LPADDING)
#define TITLE_WDG_RPADDING_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TITLE_WDG_RELOAD_MASK_RPADDING))|(((u32)_b)<<TITLE_WDG_RELOAD_FLAG_RPADDING)
/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret TitleWidget_New(MAE_ClsId ClsID, void **ppObj);
__SLDPM_FREE__ static boolean TitleWidget_HandleEvent(IDecorator *pIDecorator, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
__SLDPM_FREE__ static MAE_Ret _TitleWidget_Ctor(_TitleWidget_t *pThis);
__SLDPM_FREE__ static void _TitleWidget_Dtor(_TitleWidget_t *pThis);

__SLDPM_FREE__ static void TitleWidget_SetSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
static void TitleWidget_GetPreferredSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
__SLDPM_FREE__ static boolean TitleWidget_IntersectOpaque(IDecorator *pIDecorator, const Rect_t *pInRect, Rect_t *pOutRect);
__SLDPM_FREE__ static void TitleWidget_Draw(IDecorator *pIDecorator, IDispCanvas *pIDispCanvas, s32 x, s32 y);
__SLDPM_FREE__ static MAE_Ret TitleWidget_SetModel(IDecorator *pIDecorator, IModel *pIModel, IBase* pOwner);

__SLDPM_FREE__ static void TitleWidget_SetWidget(IDecorator *pIDecorator, IWidget *pChild);

__SLDPM_FREE__ static void TitleWidget_Invalidate(IDecorator *pIDecorator, IWidget *WidgetPtr, const Rect_t *WRectPtr, InvFlag_t Flags);
static MAE_Ret TitleWidget_Locate(IDecorator *pIDecorator, IWidget *WidgetPtr, IContainer **ppRoot, Rect_t *RelativeRectPtr, IBase *pOwner);

__SLDPM_FREE__ static MAE_Ret TitleWdgHpr_SetElementData(IWidget *pTitleWdg, u32 id, u32 type, u32 data, IBase *pOwner);

__SLDPM_FREE__ static MAE_Ret  _TitleWidget_SetElementData(_TitleWidget_t *pThis, u32 id, u32 type, u32 data);
__SLDPM_FREE__ static MAE_Ret  _TitleWidget_DataChanged(_TitleWidget_t *pThis, u32 flag);
__SLDPM_FREE__ static void     _TitleWidget_DataModelChanged(_TitleWidget_t *pThis, ModelEvent_t *pEvent);
__SLDPM_FREE__ static void     _TitleWidget_ViewModelChanged(_TitleWidget_t *pThis, ModelEvent_t *pEvent);
__SLDPM_FREE__ static boolean  _TitleWidget_SetProperty(_TitleWidget_t *pThis, u32 P1, u32 P2);
__SLDPM_FREE__ static u16      _TitleWidget_CalculateTitleTxtWidth(_TitleWidget_t *pThis, u16 WdgWidth);
__SLDPM_FREE__ static void     _TitleWidget_InvalidateTitleArea(_TitleWidget_t *pThis);
__SLDPM_FREE__ static MAERet_t _TitleWidget_LoadThemeFromRC(_TitleWidget_t *pThis);
__SLDPM_FREE__ static void     _TitleWidget_DataModelFree(void *pData, IBase *pOwner);

static void		_TitleWidget_ReloadRC(_TitleWidget_t *pThis, DisplayMode_e nDispMode);

#ifdef __TOUCH_SCREEN_MMI__
static MAERet_t _TitleWidget_HandleTouchEvent(_TitleWidget_t *pThis, MAE_EventId evt, u32 P1, u32 P2);
static boolean      _TitleWdgHpr_IsInsideTitleArea(_TitleWidget_t *pThis, s32 x, s32 y);
#endif //__TOUCH_SCREEN_MMI__

__SLDPM_FREE__ static MAE_WChar*   _TitleWdgHpr_WstrDup(const MAE_WChar *pWstrSrc);
__SLDPM_FREE__ static void         _TitleWdgHpr_NewIImage(IImage **ppImage, u16 *pFileName, IBase *pOwner);
#ifdef __UI_STYLE_MMI_IFONE__
static void _TitleWidgetSoftKeyClickCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
#endif
#endif //__MMI_WDG_TITLE_PRIV_H__
/*=============================================================*/
// end of file
