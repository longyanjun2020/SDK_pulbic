/**
* @file    mmi_mae_widget_custom.h
* @brief   This file defines all definitions for widget customization
* 
* @version $Id: mmi_mae_widget_custom.h 35190 2009-07-06 09:02:13Z elvis.chen $
*/

#ifndef __MMI_MAE_WIDGET_CUSTOM_H__
#define __MMI_MAE_WIDGET_CUSTOM_H__


//GRID WIDGET
#ifdef __TOUCH_SCREEN_MMI__
#define GRID_WDG_SLIDE_STEP_INTERVAL    100 //msec.
#define GRID_WDG_SLIDE_TOTAL_STEPS      4
#define GRID_WDG_SLIDE_THRESHOLD       					30	///< in pixels
#define GRID_WDG_SLIDE_TIME_LIMIT						300	///< in msec.

#define GRID_WDG_AUTOSCROLL_MIN_DIST	8 // pixel
#define GRID_WDG_AUTOSCROLL_THRESHOLD_DEFAULT_BLOCKS	3	//decide the threshold by dividing the CntSize into how many blocks
#define GRID_WDG_AS_TIMER_INIT_INTERVAL    	800 //msec.
#define GRID_WDG_AS_TIMER_MIN    	100 //msec.
#define GRID_WDG_AS_SPEEDUP_DIST_BLOCKS	3	//speed-up level
#define GRID_WDG_AS_SPEEDUP_TIME_INT	3	//cb times interval
#endif // __TOUCH_SCREEN_MMI__

//MFL Container
#ifdef __TOUCH_SCREEN_MMI__
#define MFL_SLIDE_STEP_INTERVAL    100 //msec.
#define MFL_SLIDE_TOTAL_STEPS      4
#define MFL_SLIDE_THRESHOLD       					30	///< in pixels
#define MFL_SLIDE_TIME_LIMIT						300	///< in msec.
#endif // __TOUCH_SCREEN_MMI__

//Input widget
#ifdef __TOUCH_SCREEN_MMI__
#define INPUT_SLIDE_STEP_INTERVAL    100 //msec.
#define INPUT_SLIDE_TOTAL_STEPS      4
#define INPUT_SLIDE_THRESHOLD       					30	///< in pixels
#define INPUT_SLIDE_TIME_LIMIT						300	///< in msec.
#endif // __TOUCH_SCREEN_MMI__

//PROGRESS WIDGET
#define PROGRESSWDG_AUTO_STEP_TIME   300

//TEXT WIDGET
#define TEXTWDG_FIRST_STEP_START_TIME 1500  ///< in msec.
#define TEXTWDG_MIN_STEP_TIME 300           ///< in msec.
#define TEXTWDG_DEF_STEP_TIME 300           ///< in msec.
#define TEXTWDG_DEF_STEP_OFFSET 5           ///< in pixels

//INPUT WIDGET
#define INPUTWDG_SHOW_LATEST_INSERT_PASSWORD_TIME 1000  ///< in msec.


//CARET WIDGET
#define CARET_WDG_DEFAULT_BLINK_ON_INTERVAL   1000    ///< The duration(in msec) to show the cursor
#define CARET_WDG_DEFAULT_BLINK_OFF_INTERVAL	1000    ///< The duration(in msec) to hide the cursor
#define CARET_WDG_MIN_BLINK_INTERVAL			1000     ///< The mininum duration(in msec)to show/hide the cursor

#ifdef __TOUCH_SCREEN_MMI__
#define SCRL_TOUCH_LONG_PRESS_DURATION   700 //msec, scroll would try to repeat if this duration expired.
#define SCRL_TOUCH_REPEAT_DURATION       300 //msec

/**
* The duration for touch long press
*/
#define SK_WDG_TOUCH_LONGPRESS_DURATION    1500 ///msec.

/**
* duration for button widget long touch press
*/
#define BTN_WDG_TOUCH_LONG_DURATION		1000 //msec.
#define BTN_WDG_TOUCH_REPEAT_DURATION	800 //msec.
#endif //__TOUCH_SCREEN_MMI__



#endif //__MAE_WIDGET_CUSTOM_H__
/*=============================================================*/
// end of file

