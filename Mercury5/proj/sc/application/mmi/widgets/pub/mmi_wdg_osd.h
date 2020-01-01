#ifndef __MMI_WDG_OSD_H__
#define __MMI_WDG_OSD_H__
/* ===========================================================*/
// Description
/* ===========================================================*/
/**
*    Osd widget is a special application of widget, to paint in RGBCOLOR_OSD_TRANS
*    color on display buffer. The purpose of this is informed MMP that deals with camera and
*    video can to send image stream on the region. Other regions are not affected by MMP.
*
*          ex:  Osd widget
*           +--------------+
*           |  +--------+  |  
*           |  | @@@@@  |  |  <-  @: Osd region
*           |  | @@@@@  |  |
*           |  +--------+  |
*           +--------------+
*/



/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_window.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_retcode.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/*=============================================================*/
// functions
/*=============================================================*/
/*=============================================================*/
/** WdgOsdCreateForWnd
* @brief        Create OSD widget and set size for Window
*
* @param[in]    hWin       The window handle
* @param[in]    pPos          A pointer of widget position; can't be NULL.
* @param[in]    pSize         A pointer of widget size; NULL means default value.
* @param[in]    nWdgId        The widget unique ID of window
*
* @retval       The pointer of OSD   Success.
* @retval       NULL                 Failed.
*
*/
IWidget* WdgOsdCreateForWnd
(
    HWIN          hWin,
    Pos_t                *pPos,
    WidgetSize_t         *pSize,
    u16                  nWdgId
);

/** WdgOsdCreate
* @brief        Create OSD widget
*
* @retval       The pointer of OSD    Success.
* @retval       NULL                  Failed.
*
*/
IWidget* WdgOsdCreate
(
    void
);


#endif //__MMI_WDG_OSD_H__
/*=============================================================*/
// end of file
