#ifndef __MMI_WDG_FADEOUT_H__
#define __MMI_WDG_FADEOUT_H__
/* ===========================================================*/
// Description
/* ===========================================================*/
/**
*  Fadeout widget is a widget provided the fade out effect. AP sometimes
*  needs to highlight information of particular area to the User, this time on
*  the need to fad out the other areas. For example: When a Dialog is running
*  up, fat out the area beyond the Dialog. The same effect is need when Option
*  menu is running up.
*
*          ex:
*           +--------------+
*           |##############|  <- #: fade out area
*           |##############|
*           |==============|
*           | @ option 1   |   <- option menu
*           |--------------|
*           | @ option 2   |
*          +---------------+
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
enum
{
	DISABLE_FADEOUT = 0,
	ENABLE_FADEOUT
};

#define DEFAULT_FADE_LEVEL  FADEOUT_LEVEL_4


/*=============================================================*/
// functions
/*=============================================================*/
/** WdgFadeoutCreateForWnd
* @brief        Fadeout widget create function for Window
*
* @param[in]    hWin        The window handle
* @param[in]    pPos           A pointer of widget position; can't be NULL.
* @param[in]    pSize          A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID      The widget unique ID of window
* @param[in]    nFoLevel       The fadeout's level
*
* @retval       The pointer of Fadeout   Success.
* @retval       NULL                     Failed.
*
*/
__SLDPM_FREE__ IWidget* WdgFadeoutCreateForWnd
(
    HWIN      hWin,
    Pos_t            *pPos,
    WidgetSize_t     *pSize,
    u16              nWidgetID,
    FadeoutLevel_t   nFoLevel
);

/*=============================================================*/
/** WdgFadeoutCreate
* @brief        Create Fadeout widget
*
* @retval       The pointer of Fadeout     Success.
* @retval       NULL                       Failed.
*
*/
__SLDPM_FREE__ IWidget* WdgFadeoutCreate
(
    void
);

/** WdgFadeoutSetFoLevel
* @brief        Set the fadeout's level
*
* @param[in]    pWDGFadeout       The pointer of IWidget interface object
* @param[in]    nFoLevel          The fadeout's level
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgFadeoutSetFoLevel
(
    IWidget              *pWDGFadeout,
    FadeoutLevel_t       nFoLevel
);

/** WdgFadeoutGetFoLevel
* @brief        Get the fadeout's level
*
* @param[in]    pWDGFadeout       The pointer of IWidget interface object
* @param[out]   pFoLevel          A pointer of FadeoutLevel_t with result of the fadeout's level
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgFadeoutGetFoLevel
(
    IWidget             *pWDGFadeout,
    FadeoutLevel_t      *pFoLevel
);

#endif //__MMI_WDG_FADEOUT_H__
/*=============================================================*/
// end of file
