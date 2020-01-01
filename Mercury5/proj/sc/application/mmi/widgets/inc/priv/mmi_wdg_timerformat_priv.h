/**
* @file    mmi_wdg_timerformat_priv.h
* @version $Id: mmi_wdg_timerformat_priv.h 14596 2008-10-01 09:04:35Z paul.ouyang $
* @brief
* <Description>
* TimerFormat Widget is a widget providing different kinds of timeformat display.
* APP set timetick to TimerFormatWidget datamodel, TimerFormatWidget will display time on specific layout
* Currently, the widget provide 4 layout:
*	(1) HH:MM:SS			( 09:08:59 )
*  (2) HH:MM				( 09:08 )
*  (3) MM:SS				( 08:59 )
*  (4) HH:MM:SS.MS	( 09:08:59.1)
* APP can set property to change the following parameter:
*	 - Format Lyaout		( 4 kinds of Timer Layout)
*   - Width for digit and separater	( Pixels for each digital and separater )
*   - Delimiter for separater
*/

#ifndef __MMI_WDG_TIMERFORMAT_PRIV_H__
#define __MMI_WDG_TIMERFORMAT_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_widgetbase.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_config.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct {
	WidgetBaseEx_t		WdgBase;				///< Using WidgetBase_t as base structure.  //WidgetBase_t-->WidgetBaseEx_t
	//u32 FormatLayout;								///< the CLSID of widget
	ModelListener_t 	MdlLsn;					///< Model listener for listening the data model change within this SwitchIcon widget.
	TimerTextFont_t fontInfo;					///< font information
	TimerFormatInfo_t	formatInfo;			///< format information
	u8                 		AlignFlag;  			 ///< TimerFormatWidget alignment
	s32             xOffset;
	s32             yOffset;
	u32				nReloadRCFlag;		///< the flag record which rc property has been modified outside, those are not reload
} WdgTimerFormat_t;

// RELOAD flag
enum
{
	TIMERFORMAT_WDG_RELOAD_FLAG_START = 0,
	TIMERFORMAT_WDG_RELOAD_FLAG_ALIGN = TIMERFORMAT_WDG_RELOAD_FLAG_START,
	TIMERFORMAT_WDG_RELOAD_FLAG_FONTSIZE,
	TIMERFORMAT_WDG_RELOAD_FLAG_FONTTYPE,
	TIMERFORMAT_WDG_RELOAD_FLAG_TEXTCOLOR,
	TIMERFORMAT_WDG_RELOAD_FLAG_OUTLINECOLOR,
	TIMERFORMAT_WDG_RELOAD_FLAG_LAYOUT,
	TIMERFORMAT_WDG_RELOAD_FLAG_SEPARATORWIDTH,
	TIMERFORMAT_WDG_RELOAD_FLAG_WSEPARATOR,
	TIMERFORMAT_WDG_RELOAD_FLAG_WSEPARATOREXT,
	TIMERFORMAT_WDG_RELOAD_FLAG_END
};

/**
* Flag Mask
*/
#define TIMERFORMAT_WDG_RELOAD_MASK_ALIGN      (1<<TIMERFORMAT_WDG_RELOAD_FLAG_ALIGN)
#define TIMERFORMAT_WDG_RELOAD_MASK_FONTSIZE      (1<<TIMERFORMAT_WDG_RELOAD_FLAG_FONTSIZE)
#define TIMERFORMAT_WDG_RELOAD_MASK_FONTTYPE     (1<<TIMERFORMAT_WDG_RELOAD_FLAG_FONTTYPE)
#define TIMERFORMAT_WDG_RELOAD_MASK_TEXTCOLOR     (1<<TIMERFORMAT_WDG_RELOAD_FLAG_TEXTCOLOR)
#define TIMERFORMAT_WDG_RELOAD_MASK_OUTLINECOLOR        (1<<TIMERFORMAT_WDG_RELOAD_FLAG_OUTLINECOLOR)
#define TIMERFORMAT_WDG_RELOAD_MASK_LAYOUT        (1<<TIMERFORMAT_WDG_RELOAD_FLAG_LAYOUT)
#define TIMERFORMAT_WDG_RELOAD_MASK_SEPARATORWIDTH      (1<<TIMERFORMAT_WDG_RELOAD_FLAG_SEPARATORWIDTH)
#define TIMERFORMAT_WDG_RELOAD_MASK_WSEPARATOR      (1<<TIMERFORMAT_WDG_RELOAD_FLAG_WSEPARATOR)
#define TIMERFORMAT_WDG_RELOAD_MASK_WSEPARATOREXT      (1<<TIMERFORMAT_WDG_RELOAD_FLAG_WSEPARATOREXT)
/**
* Macro to get flag value
*/
#define TIMERFORMAT_WDG_ALIGN_IS_MODIFIED(_pWdg) \
    (boolean)(((_pWdg)->nReloadRCFlag&TIMERFORMAT_WDG_RELOAD_MASK_ALIGN)>>TIMERFORMAT_WDG_RELOAD_FLAG_ALIGN)
#define TIMERFORMAT_WDG_FONTSIZE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TIMERFORMAT_WDG_RELOAD_MASK_FONTSIZE)>>TIMERFORMAT_WDG_RELOAD_FLAG_FONTSIZE)
#define TIMERFORMAT_WDG_FONTTYPE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TIMERFORMAT_WDG_RELOAD_MASK_FONTTYPE)>>TIMERFORMAT_WDG_RELOAD_FLAG_FONTTYPE)
#define TIMERFORMAT_WDG_TEXTCOLOR_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TIMERFORMAT_WDG_RELOAD_MASK_TEXTCOLOR)>>TIMERFORMAT_WDG_RELOAD_FLAG_TEXTCOLOR)
#define TIMERFORMAT_WDG_OUTLINECOLOR_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TIMERFORMAT_WDG_RELOAD_MASK_OUTLINECOLOR)>>TIMERFORMAT_WDG_RELOAD_FLAG_OUTLINECOLOR)
#define TIMERFORMAT_WDG_LAYOUT_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TIMERFORMAT_WDG_RELOAD_MASK_LAYOUT)>>TIMERFORMAT_WDG_RELOAD_FLAG_LAYOUT)
#define TIMERFORMAT_WDG_SEPARATORWIDTH_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TIMERFORMAT_WDG_RELOAD_MASK_SEPARATORWIDTH)>>TIMERFORMAT_WDG_RELOAD_FLAG_SEPARATORWIDTH)
#define TIMERFORMAT_WDG_WSEPARATOR_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TIMERFORMAT_WDG_RELOAD_MASK_WSEPARATOR)>>TIMERFORMAT_WDG_RELOAD_FLAG_WSEPARATOR)
#define TIMERFORMAT_WDG_WSEPARATOREXT_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TIMERFORMAT_WDG_RELOAD_MASK_WSEPARATOREXT)>>TIMERFORMAT_WDG_RELOAD_FLAG_WSEPARATOREXT)
/**
* Macro to Set flag value
*/
#define TIMERFORMAT_WDG_ALIGN_SET_MODIFIED(_pWdg, _b) \
    (_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TIMERFORMAT_WDG_RELOAD_MASK_ALIGN))|(((u32)_b)<<TIMERFORMAT_WDG_RELOAD_FLAG_ALIGN)
#define TIMERFORMAT_WDG_FONTSIZE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TIMERFORMAT_WDG_RELOAD_MASK_FONTSIZE))|(((u32)_b)<<TIMERFORMAT_WDG_RELOAD_FLAG_FONTSIZE)
#define TIMERFORMAT_WDG_FONTTYPE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TIMERFORMAT_WDG_RELOAD_MASK_FONTTYPE))|(((u32)_b)<<TIMERFORMAT_WDG_RELOAD_FLAG_FONTTYPE)
#define TIMERFORMAT_WDG_TEXTCOLOR_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TIMERFORMAT_WDG_RELOAD_MASK_TEXTCOLOR))|(((u32)_b)<<TIMERFORMAT_WDG_RELOAD_FLAG_TEXTCOLOR)
#define TIMERFORMAT_WDG_OUTLINECOLOR_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TIMERFORMAT_WDG_RELOAD_MASK_OUTLINECOLOR))|(((u32)_b)<<TIMERFORMAT_WDG_RELOAD_FLAG_OUTLINECOLOR)
#define TIMERFORMAT_WDG_LAYOUT_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TIMERFORMAT_WDG_RELOAD_MASK_LAYOUT))|(((u32)_b)<<TIMERFORMAT_WDG_RELOAD_FLAG_LAYOUT)
#define TIMERFORMAT_WDG_SEPARATORWIDTH_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TIMERFORMAT_WDG_RELOAD_MASK_SEPARATORWIDTH))|(((u32)_b)<<TIMERFORMAT_WDG_RELOAD_FLAG_SEPARATORWIDTH)
#define TIMERFORMAT_WDG_WSEPARATOR_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TIMERFORMAT_WDG_RELOAD_MASK_WSEPARATOR))|(((u32)_b)<<TIMERFORMAT_WDG_RELOAD_FLAG_WSEPARATOR)
#define TIMERFORMAT_WDG_WSEPARATOREXT_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TIMERFORMAT_WDG_RELOAD_MASK_WSEPARATOREXT))|(((u32)_b)<<TIMERFORMAT_WDG_RELOAD_FLAG_WSEPARATOREXT)
/*=============================================================*/
// functions
/*=============================================================*/
/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret TimerFormatWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean WdgTimerFormatDefHandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);


/*=============================================================*/
// Non-interface functions
/*=============================================================*/
	static MAE_Ret _WdgTimerFormatConstructor(WdgTimerFormat_t*);

	void _WdgTimerFormatDestructor(WdgTimerFormat_t *pThis);

	static void _WdgTimerFormatModelListener(void *pUsrData, ModelEvent_t *pMdlEvent);

	MAE_Ret _WdgTimerFormatSetModel(IWidget *pIWidget, IModel *pIModel, IBase* pOwner);

	void _WdgTimerFormatSetSize(IWidget *pIWidget, WidgetSize_t *pSize);

	void _WdgTimerFormatGetPreferredSize(IWidget *pIWidget, WidgetSize_t *pSize);

	void _WdgTimerFormatDraw(IWidget *pIWidget, IDispCanvas *pIDispCanvas, s32 x, s32 y);

	static boolean _WdgTimerFormatSetProperty(WdgTimerFormat_t *pThis, u32 P1, u32 P2);

	static void _WdgTimerFormatSecondtoHHMMSS(u32 TimerTick, MAE_WChar sep ,  MAE_WChar* pWStr);

	static void _WdgTimerFormatSecondtoMMSS(u32 TimerTick, MAE_WChar sep, MAE_WChar* pWStr);

	static void _WdgTimerFormatSecondtoHHMMSS_EXT(u32 IntTick, u32 FloatTick,  MAE_WChar sep , MAE_WChar sepExt,   MAE_WChar* pWStr);

	static void _WdgTimerFormatSecondtoHHMMSS_EXT2(u32 IntTick, u32 FloatTick,  MAE_WChar sep , MAE_WChar sepExt,   MAE_WChar* pWStr);

	void  _WdgTimerFormatCalculateOffset(WdgTimerFormat_t* pThis);

	void  _WdgTimerFormatCalculateSeparatorWidth(WdgTimerFormat_t* pThis);

	void _WdgTimerFormatDrawFitText(WdgTimerFormat_t* pThis, IDisplay *pDisp, s32 FontCat, u32 FontSize, const u16 *pText, s32 Chars, s32 x, s32 y, const Rect_t *pRect,u32 Types, boolean b3D);

	static void _WdgTimerFormat_ReloadRC(WdgTimerFormat_t *pThis, DisplayMode_e nDispMode);
#endif //__MMI_WDG_TIMERFORMAT_PRIV_H__
/*=============================================================*/
// end of file
