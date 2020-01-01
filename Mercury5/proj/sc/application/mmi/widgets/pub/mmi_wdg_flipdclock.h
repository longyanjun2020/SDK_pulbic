#ifdef __UI_STYLE_FLIPDCLOCK__
/**
* @file    mmi_wdg_flipdclock.h
* @author  Ryan.Chou
* @version $Id: mmi_wdg_flipdclock.h   2010-12-3 Lin.wang $
* @brief
* @layout
*  -----------------------------------------------
*  | ------------------------------------------- ||
*  | | Left-Top Image        | |  Right-Top Image            |
*  | ------------------------------------------- ||
*  | | Left-Bottom Image   | |  Right-Bottom Image      ||
*  | --------------------------------------------  |
*  -----------------------------------------------
*/

#ifndef __MMI_WDG_FLIPDCLOCK_H__
#define __MMI_WDG_FLIPDCLOCK_H__
/**
* Flip digital clock widget
*/
#ifndef FLIPDCLOCK_DIGIT_WIDTH
#define FLIPDCLOCK_DIGIT_WIDTH      44
#endif
#ifndef FLIPDCLOCK_DIGIT_HEIGHT
#define FLIPDCLOCK_DIGIT_HEIGHT     80
#endif
#ifndef FLIPDCLOCK_MARGIN
#define FLIPDCLOCK_MARGIN           8
#endif

#define FLIPDCLOCK_AMPMWIDGET_WIDTH 40
#define FLIPDCLOCK_AMPMWIDGET_HEIGHT 24//MAIN_LCD_ONELINE_HEIGHT
#define FLIPDCLOCK_AMPMWIDGET_POS_X ((FLIPDCLOCK_DIGIT_WIDTH + FLIPDCLOCK_MARGIN) *4 - 6)
#define FLIPDCLOCK_AMPMWIDGET_POS_Y (FLIPDCLOCK_DIGIT_HEIGHT-FLIPDCLOCK_AMPMWIDGET_HEIGHT)

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_propcontainer.h"
#include "mmi_mae_common_def.h"//for data & time widget
#include "mmi_mae_window.h"

/*=============================================================*/
// type and define
/*=============================================================*/


/*=============================================================*/
// functions
/*=============================================================*/
/** WdgFlipdClockCreateForWnd
* @brief        Create FlipClock Widget and set value for Window
*
* @param[in]    hWin                The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
*
* @retval       The pointer of Statusbar    Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgFlipdClockCreateForWnd
(
 HWIN                    hWin,
 Pos_t                   *pPos,
 WidgetSize_t            *pSize,
 u16                     nWidgetID
 );
/*=============================================================*/
/** WdgFlipdClockCreate
* @brief        Create Flipclock widget
*
* @retval       The pointer of flip widget      Success.
* @retval       NULL                            Failed.
*
*/
IWidget* WdgFlipdClockCreate
(
 void
 );

#endif //__MMI_WDG_FLIPDCLOCK_H__
#endif  //__UI_STYLE_FLIPDCLOCK__
/*=============================================================*/
// end of file
