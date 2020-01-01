/**
* @file mae_scrollcommon.h
* @brief 
*
* @version $Id: mae_scrollcommon.h 25372 2009-03-11 08:10:22Z mark.yang $
*/
#ifndef __MAE_SCROLLCOMMON_H__
#define __MAE_SCROLLCOMMON_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget_events.h"
#include "mmi_mae_widget_custom.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/// move to mae_widget_custom.h
//#ifdef __TOUCH_SCREEN_MMI__
//#define SCRL_TOUCH_LONG_PRESS_DURATION   700 //msec, scroll would try to repeat if this duration expired.
//#define SCRL_TOUCH_REPEAT_DURATION       300 //msec
//#endif //__TOUCH_SCREEN_MMI__

/**
* Scroll direction
*/
enum {
	SCROLL_DIR_HORZ = 0,
	SCROLL_DIR_VERT,
	SCROLL_DIR_NUM,
	SCROLL_DIR_END = SCROLL_DIR_NUM
};

/**
* Scroll data for someone dimension
*/
typedef struct{
	u32 nTotal;             ///< Number of total pixels(or items)
	u32 nPos;               /*!< Current position. If listening on view change, it means the top visible pixel(or item);
	                             If listening on item index, it means the highlight index(zero-base)*/
	u32 nVisible;           ///< Number of pixels(or items) in the visible range 
	u16 nStep;              ///< Number of pixels(or items) moved in each step
	ScrollDataType_t nType; /*!< Scroll type, 
	                             SCROLL_DATA_TYPE_VIEW_RANGE: listen on view change; 
	                             SCROLL_DATA_TYPE_ITEM_NUMBER: listen on item index change */
} _ScrollInfo_st;


#endif //__MAE_SCROLLCOMMON_H__
/*=============================================================*/
// end of file
