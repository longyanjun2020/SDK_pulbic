/**
 * @file    mmi_wdg_calendardesktop_priv.h
 * @brief   The internal structure of the calendar desktopwidget

 */

#ifndef __MMI_WDG_CALENDARDESKTOP_PRIV_H__
#define __MMI_WDG_CALENDARDESKTOP_PRIV_H__

#include "mmi_mae_common_def.h"
#include "mmi_wdg_desktop.h"
#include "mmi_mae_clock_types.h"
#include "mmi_mae_arraymodel.h"
#include "mmi_common_util.h"
#include "mmi_wdg_list.h"
#include "rs_layout_id.h"

#if defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_IDLE_SIMPLE__) || defined(__UI_STYLE_MMI_ANDROID_4_0_GADGET__)
#include "mmi_vcalstoresrv.h"
#define __CALENDAR_DESKTOPWDG_3D_UI_STYLE__
#define __CALENDAR_DESKTOPWDG_3D_DISABLE_TOUCH_EVENTMENU__
#ifndef __3D_UI_IDLE_SIMPLE__
#define __CALENDAR_DESKTOPWDG_3D_GETEVENT_FROM_CURRENTTIME__
#endif
///#define __CALENDAR_DESKTOPWDG_3D_HIGHLIGHT_WEEKDAY__
#if defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_IDLE_SIMPLE__)
#define __CALENDAR_DESKTOPWDG_3D_UI_FLIP_EFFECT__
#endif // 3D Flip Effect
#endif

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__) || defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_IDLE_SIMPLE__)


#define CALENDARWGT_WEEKDAY 7
#define CALENDARWGT_YEARMONTH 12
#define CALENDARWGT_GRIDITEMSIZE CALENDARWGT_WEEKDAY*6

#define CALENDARWGT_THIS_WEEKDAY_TEXTCOLOR 	(COLOR_BLACK)
#define CALENDARWGT_OTHER_WEEKDAY_TEXTCOLOR (COLOR_WHITE)

#define CALENDARWGT_WEEKDAY_TEXTCOLOR 	0x458511
#define CALENDARWGT_WEEKEND_TEXTCOLOR 	0x003E87
#define CALENDARWGT_OUTOFDAY_TEXTCOLOR 	0x5990CE

enum
{
	CALENDARDESKTOPWIDGET_TOUCH_SUBITEM_NONE = 0,
	CALENDARDESKTOPWIDGET_TOUCH_SUBITEM_FOCUSGRID,
	CALENDARDESKTOPWIDGET_TOUCH_SUBITEM_BIG_EVENTMENU,
	CALENDARDESKTOPWIDGET_TOUCH_SUBITEM_SMALL_EVENTMENU,
	CALENDARDESKTOPWIDGET_TOUCH_SUBITEM_DAYVIEW,
	CALENDARDESKTOPWIDGET_TOUCH_SUBITEM_FAKE_BITMAP_TSUP,
	CALENDARDESKTOPWIDGET_TOUCH_SUBITEM_FAKE_BITMAP_TSDOWN,
	CALENDARDESKTOPWIDGET_TOUCH_SUBITEM_SMALL_BITMAP_TSUP,
	CALENDARDESKTOPWIDGET_TOUCH_SUBITEM_SMALL_BITMAP_TSDOWN,
};

typedef u8 CalendarDesktop_Touch_Subitem_e;

typedef struct
{
	DECLARE_BASECLASS_DESKTOPWIDGET

	// Subwidget codes
	IWidget			*pIContainer;
	IWidget			*pITextNumWidget;
	IWidget			*pITextStrWidget;
	IWidget			*pIGridWidget;
	IWidget			*pIDayNumWidget;
	IWidget			*pIImgIconMonthWidget;
	IWidget			*pIImgIconDayWidget[2];
#ifdef __CALENDAR_DESKTOPWDG_3D_UI_STYLE__
	IWidget			*pIFocusGridWidget;
	IWidget			*pIWeekDayTextWidget[7];
	IWidget			*pIEventMenuWidget;
#ifdef __CALENDAR_DESKTOPWDG_3D_UI_FLIP_EFFECT__
    IWidget			*pSetFlipWdg;
#endif // __CALENDAR_DESKTOPWDG_3D_UI_FLIP_EFFECT__
    MAE_DateTime_t   tFocusDate;
    u32 nLastMonthNumDays;
    u32 nCurrrentMonthNumDays;
    MAE_WChar *pText;
    CalendarDesktop_Touch_Subitem_e eTouchSubwidget;
    IVCALSTORESRV *pIVCalStoreSrv;
    void *pUsrData;
	u8 previousDay;
#ifdef __CALENDAR_DESKTOPWDG_3D_GETEVENT_FROM_CURRENTTIME__
    MAE_DateTime_t   tCurrentEventDate;    
#endif    
#endif // End of __CALENDAR_DESKTOPWDG_3D_UI_STYLE__
	IArrayModel		*pIGridModel;
	ClockListener_t IClockListener;
	IClock			*pIClock;

	s32		startDayIdx;
    s32		endDayIdx;
    u8      previousYear;
    u8      previousMon;
	u8	    bLargeBg;
#ifdef __UI_STYLE_MMI_ANDROID_4_0_GADGET__
    boolean bInDragMode; // Avoid fliping to next day when moving up/down
#endif // __UI_STYLE_MMI_ANDROID_4_0_GADGET__
	CalendarDesktopWidget_Style_e  eCalendarStyle;
    IWidget	*pIFakeBitmapWidget;
} CalendarDesktopWdg_t;

/*************************************************************************/
/*   For IWidget interface                                               */
/*************************************************************************/

/*************************************************************************/
/*   Other Local Functions                                               */
/*************************************************************************/

#endif //__GADGETS_MMI__ || __3D_UI_IDLE_GADGETBAR__ || __3D_UI_IDLE_MULTIPAGE__ || __3D_UI_IDLE_SIMPLE__

#endif //__MMI_WDG_CALENDARDESKTOP_PRIV_H__
/*=============================================================*/
// end of file
