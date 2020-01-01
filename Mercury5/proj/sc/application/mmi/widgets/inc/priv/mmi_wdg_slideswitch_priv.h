/**
 * @file    mmi_wdg_slideswitch_priv.h
 * @brief   The document describes internal declartion of SlideSwitch Widget
 * @author  christoph.kuo@mstarsemi.com
 *
 * @version $Id: mmi_wdg_slideswitch_priv.h 25372 2009-03-11 08:10:22Z mark.yang $
 */

#ifndef __MMI_WDG_SLIDESWITCH_PRIV_H__
#define __MMI_WDG_SLIDESWITCH_PRIV_H__

#ifdef __TOUCH_SCREEN_MMI__

#include "mae_abscontainerbase.h"
#include "mae_animation.h"
/*  Declarations */

typedef struct
{
    AbsContainerBase_t AbsCntrBase;
    IWidget *pISliderBGWdg;
	IWidget *pISliderTextWdg;
    IWidget *pISwitchWdg;
    ITouchSrv *pITouchSrv;					///< Touch service
    u32     nCurrentSwitchPosX;
    u32     nMaxSwitchPosX;
    u32     nMinSwitchPosX;
    u32     nCurrentCursorPosX;
    boolean bStartSlide;
    IAnimation *pAnimation;
#if defined (__UI_STYLE_MMI_IFONE__) || defined (__UI_STYLE_MMI_STYLE_SWITCH__)
    IWidget *pLeftImageWdg;
    IWidget *pFocusImageWdg;
    IWidget *pRightImageWdg;
#endif

	u32					nReloadRCFlag;		///< the flag record which rc property has been modified outside, those are not reload
}_MAE_SlideSwitchWidget;

// RELOAD flag
enum
{
	SLIDESWITCH_WDG_RELOAD_FLAG_START = 0,
	SLIDESWITCH_WDG_RELOAD_FLAG_SLIDERBGIMG = SLIDESWITCH_WDG_RELOAD_FLAG_START,
	SLIDESWITCH_WDG_RELOAD_FLAG_SLIDERBGSIZE,
	SLIDESWITCH_WDG_RELOAD_FLAG_SLIDERBGPOS,
	SLIDESWITCH_WDG_RELOAD_FLAG_SWITCHIMG,
	SLIDESWITCH_WDG_RELOAD_FLAG_SWITCHSIZE,
	SLIDESWITCH_WDG_RELOAD_FLAG_SWITCHPOS,
	SLIDESWITCH_WDG_RELOAD_FLAG_CURRPOSX,
	SLIDESWITCH_WDG_RELOAD_FLAG_MAXPOSX,
	SLIDESWITCH_WDG_RELOAD_FLAG_MINPOSX,
	SLIDESWITCH_WDG_RELOAD_FLAG_END
};

/**
* Flag Mask
*/
#define SLIDESWITCH_WDG_RELOAD_MASK_SLIDERBGIMG       (1<<SLIDESWITCH_WDG_RELOAD_FLAG_SLIDERBGIMG)
#define SLIDESWITCH_WDG_RELOAD_MASK_SLIDERBGSIZE      (1<<SLIDESWITCH_WDG_RELOAD_FLAG_SLIDERBGSIZE)
#define SLIDESWITCH_WDG_RELOAD_MASK_SLIDERBGPOS       (1<<SLIDESWITCH_WDG_RELOAD_FLAG_SLIDERBGPOS)
#define SLIDESWITCH_WDG_RELOAD_MASK_SWITCHIMG         (1<<SLIDESWITCH_WDG_RELOAD_FLAG_SWITCHIMG)
#define SLIDESWITCH_WDG_RELOAD_MASK_SWITCHSIZE        (1<<SLIDESWITCH_WDG_RELOAD_FLAG_SWITCHSIZE)
#define SLIDESWITCH_WDG_RELOAD_MASK_SWITCHPOS         (1<<SLIDESWITCH_WDG_RELOAD_FLAG_SWITCHPOS)
#define SLIDESWITCH_WDG_RELOAD_MASK_CURRPOSX           (1<<SLIDESWITCH_WDG_RELOAD_FLAG_CURRPOSX)
#define SLIDESWITCH_WDG_RELOAD_MASK_MAXPOSX           (1<<SLIDESWITCH_WDG_RELOAD_FLAG_MAXPOSX)
#define SLIDESWITCH_WDG_RELOAD_MASK_MINPOSX           (1<<SLIDESWITCH_WDG_RELOAD_FLAG_MINPOSX)
/**
* Macro to get flag value
*/
#define SLIDESWITCH_WDG_SLIDERBGIMG_IS_MODIFIED(_pWdg) \
    (boolean)(((_pWdg)->nReloadRCFlag&SLIDESWITCH_WDG_RELOAD_MASK_SLIDERBGIMG)>>SLIDESWITCH_WDG_RELOAD_FLAG_SLIDERBGIMG)
#define SLIDESWITCH_WDG_SLIDERBGSIZE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&SLIDESWITCH_WDG_RELOAD_MASK_SLIDERBGSIZE)>>SLIDESWITCH_WDG_RELOAD_FLAG_SLIDERBGSIZE)
#define SLIDESWITCH_WDG_SLIDERBGPOS_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&SLIDESWITCH_WDG_RELOAD_MASK_SLIDERBGPOS)>>SLIDESWITCH_WDG_RELOAD_FLAG_SLIDERBGPOS)
#define SLIDESWITCH_WDG_SWITCHIMG_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&SLIDESWITCH_WDG_RELOAD_MASK_SWITCHIMG)>>SLIDESWITCH_WDG_RELOAD_FLAG_SWITCHIMG)
#define SLIDESWITCH_WDG_SWITCHSIZE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&SLIDESWITCH_WDG_RELOAD_MASK_SWITCHSIZE)>>SLIDESWITCH_WDG_RELOAD_FLAG_SWITCHSIZE)
#define SLIDESWITCH_WDG_SWITCHPOS_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&SLIDESWITCH_WDG_RELOAD_MASK_SWITCHPOS)>>SLIDESWITCH_WDG_RELOAD_FLAG_SWITCHPOS)
#define SLIDESWITCH_WDG_CURRPOSX_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&SLIDESWITCH_WDG_RELOAD_MASK_CURRPOSX)>>SLIDESWITCH_WDG_RELOAD_FLAG_CURRPOSX)
#define SLIDESWITCH_WDG_MAXPOSX_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&SLIDESWITCH_WDG_RELOAD_MASK_MAXPOSX)>>SLIDESWITCH_WDG_RELOAD_FLAG_MAXPOSX)
#define SLIDESWITCH_WDG_MINPOSX_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&SLIDESWITCH_WDG_RELOAD_MASK_MINPOSX)>>SLIDESWITCH_WDG_RELOAD_FLAG_MINPOSX)
/**
* Macro to Set flag value
*/
#define SLIDESWITCH_WDG_SLIDERBGIMG_SET_MODIFIED(_pWdg, _b) \
    (_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SLIDESWITCH_WDG_RELOAD_MASK_SLIDERBGIMG))|(((u32)_b)<<SLIDESWITCH_WDG_RELOAD_FLAG_SLIDERBGIMG)
#define SLIDESWITCH_WDG_SLIDERBGSIZE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SLIDESWITCH_WDG_RELOAD_MASK_SLIDERBGSIZE))|(((u32)_b)<<SLIDESWITCH_WDG_RELOAD_FLAG_SLIDERBGSIZE)
#define SLIDESWITCH_WDG_SLIDERBGPOS_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SLIDESWITCH_WDG_RELOAD_MASK_SLIDERBGPOS))|(((u32)_b)<<SLIDESWITCH_WDG_RELOAD_FLAG_SLIDERBGPOS)
#define SLIDESWITCH_WDG_SWITCHIMG_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SLIDESWITCH_WDG_RELOAD_MASK_SWITCHIMG))|(((u32)_b)<<SLIDESWITCH_WDG_RELOAD_FLAG_SWITCHIMG)
#define SLIDESWITCH_WDG_SWITCHSIZE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SLIDESWITCH_WDG_RELOAD_MASK_SWITCHSIZE))|(((u32)_b)<<SLIDESWITCH_WDG_RELOAD_FLAG_SWITCHSIZE)
#define SLIDESWITCH_WDG_SWITCHPOS_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SLIDESWITCH_WDG_RELOAD_MASK_SWITCHPOS))|(((u32)_b)<<SLIDESWITCH_WDG_RELOAD_FLAG_SWITCHPOS)
#define SLIDESWITCH_WDG_CURRPOSX_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SLIDESWITCH_WDG_RELOAD_MASK_CURRPOSX))|(((u32)_b)<<SLIDESWITCH_WDG_RELOAD_FLAG_CURRPOSX)
#define SLIDESWITCH_WDG_MAXPOSX_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SLIDESWITCH_WDG_RELOAD_MASK_MAXPOSX))|(((u32)_b)<<SLIDESWITCH_WDG_RELOAD_FLAG_MAXPOSX)
#define SLIDESWITCH_WDG_MINPOSX_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SLIDESWITCH_WDG_RELOAD_MASK_MINPOSX))|(((u32)_b)<<SLIDESWITCH_WDG_RELOAD_FLAG_MINPOSX)

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret SlideSwitchWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean SlideSwitchWidget_HandleEvent(IAbsContainer *pIAbsContainer, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret _WdgSlideSwitchConstructor(_MAE_SlideSwitchWidget *pThis);
void _WdgSlideSwitchDestructor(_MAE_SlideSwitchWidget *pThis);
void SlideSwitchWidget_Notify(_MAE_SlideSwitchWidget *pThis, u32 MdlEvt, u32 dwParam);
void SlideAnimationEndCB(void * param1);
void SlideBackAnimationEndCB(void * param1);

static void _SlideSwitchWidget_ReloadRC(_MAE_SlideSwitchWidget *pThis, DisplayMode_e nDispMode);

#endif
#endif /* __MMI_WDG_SLIDESWITCH_PRIV_H__ */
