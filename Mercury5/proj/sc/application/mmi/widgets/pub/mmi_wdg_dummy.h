/**
 * @file    mmi_wdg_dummy.h
 * @author  alison.chen@mstarsemi.com
 * 
 * @version $Id: mmi_wdg_dummy.h 4291 2007-11-19 03:56:54Z alison.chen $
 *
 *
 * @brief   
 *
 */
 
#ifndef __MMI_WDG_DUMMY_H__
#define __MMI_WDG_DUMMY_H__
/* ===========================================================*/
// Description
/* ===========================================================*/

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_window.h"
#include "mmi_mae_view_wrapper.h"
#include "mmi_wdg_common_interface.h"
#include "mmi_wdg_headers.h"


/*=============================================================*/
// type and define
/*=============================================================*/

/*=============================================================*/
// functions
/*=============================================================*/
/*=============================================================*/
/** WdgDummyCreateForWnd
* @brief        Create Dummy widget and set size  for Window
*
* @param[in]    hWin       The window handle
* @param[in]    pPos          A pointer of widget position; can't be NULL.
* @param[in]    pSize         A pointer of widget size; NULL means default value.
* @param[in]    nWdgId        The widget unique ID of window
*
* @retval       The pointer of Dummy   Success.
* @retval       NULL                 Failed.
*
*/
IWidget* WdgDummyCreateForWnd
(
    HWIN          hWin,
    Pos_t                *pPos,
    WidgetSize_t         *pSize,
    u16                  nWdgId
);

/** WdgDummyCreate
* @brief        Create Dummy widget
*
* @retval       The pointer of Dummy    Success.
* @retval       NULL                  Failed.
*
*/
IWidget* WdgDummyCreate
(
    void
);


#endif //__MMI_WDG_DUMMY_H__
/*=============================================================*/
// end of file
