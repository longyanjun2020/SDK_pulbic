/**
* @file    mmi_wdg_fliptext.h
*
*/
#ifndef __MMI_WDG_FLIPTEXT_H__
#define __MMI_WDG_FLIPTEXT_H__

/*=============================================================*/
// include
/*=============================================================*/

#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_window.h"
#include "mmi_mae_view_wrapper.h"
#include "mmi_wdg_common_interface.h"

/*=============================================================*/
// type and define
/*=============================================================*/

typedef enum
{
    FLIPTEXT_TEXTSTYLE_LARGE = 0,

    FLIPTEXT_TEXTSTYLE_COUNT
}eFLIPTEXT_TEXTSTYLE;

typedef enum
{
    FLIPTEXT_FLIP_DIRECTION_UP = 0,
    FLIPTEXT_FLIP_DIRECTION_DOWN
} eFLIPTEXT_FLIP_DIRECTION;

/** WdgFlipTextCreateForWnd
* @brief        Create FlipText widget and set size for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
*
* @retval       The pointer of FlipText  Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgFlipTextCreateForWnd
(
 HWIN      hWin,
 Pos_t            *pPos,
 WidgetSize_t     *pSize,
 u16              nWidgetID
);

/** WdgFlipTextCreate
* @brief        Create FlipText widget
*
* @retval       The pointer of FlipText  Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgFlipTextCreate
(
 void
);

#endif /*__MMI_WDG_FLIPTEXT_H__ */

