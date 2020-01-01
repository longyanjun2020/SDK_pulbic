/**
 * @file    mmi_wdg_ballslide.h
 * @brief   This file defines the interface of ballslide widget
 * @author  peng.hu@mstarsemi.com
 * @version $Id: mmi_wdg_ballslide.h$
 */
#ifndef __MMI_WDG_BALLSLIDE_H__
#define __MMI_WDG_BALLSLIDE_H__
#ifdef __MMI_BALLSLIDE_WDG_SUPPORT__

//typedef u8 BallSlideWdgID_e;

typedef void (*PfnWdgBallSlideSlideComplete) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);

MAE_Ret WdgBallSlideSwitchRegisterSlideCompleteCb
(
	IWidget                         *pWDGSlideSwitch,
	PfnWdgBallSlideSlideComplete     pfn,
	void                            *pUserData
);

#endif //__MMI_BALLSLIDE_WDG_SUPPORT__
#endif //__MMI_WDG_BALLSLIDE_H__


