/**
* @file    mmi_wdg_screensaver_effect.h
* @brief   This file defines the interface of screensaver-effect widget
* @version $Id: mmi_wdg_screensaver_effect.h$
*/

#ifndef __MMI_WDG_SCREENSAVER_EFFECT_H__
#define __MMI_WDG_SCREENSAVER_EFFECT_H__

#if defined(__FEATURE_MGL__)

#include "mae_window.h"
#include "mmi_mae_live_effect.h"

/*************************************************************************/
/*   For IBase Interface                                                 */
/*************************************************************************/

/*************************************************************************/
/*   For IWidget Common Interface                                        */
/*************************************************************************/

/** WdgScreensaverEffectCreateForWnd
* @brief        Screensaver-effect widget create function for Window.
*
* @param[in]    hWin            The window handle
* @param[in]    pPos            A pointer of widget position; can't be NULL.
* @param[in]    pSize           A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID       The widget unique ID of window.
* @param[in]    pData           Widget Common Data.
*
* @retval       The pointer of screensaver-effect pointer        Success.
* @retval       NULL                                             Failed.
*
*/
IWidget* WdgScreensaverEffectCreateForWnd
(
 HWIN                hWin,
 Pos_t               *pPos,
 WidgetSize_t        *pSize,
 u16                 nWidgetID
 );

/*=============================================================*/
/** WdgScreensaverEffectCreate
* @brief        Create screensaver-effect widget.
*
* @retval       The pointer of screensaver-effect       Success.
* @retval       NULL                                    Failed.
*
*/
IWidget* WdgScreensaverEffectCreate(void);

/** WdgScreensaverEffectSetStyle
* @brief        Set screensaver-effect style.
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[in]    eStyle              The effect style
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed, Not Support or Error parameter(NULL).
*
*/
MAE_Ret WdgScreensaverEffectSetStyle
(
 IWidget                 *pWDGObject,
 ScreensaverStytle_e     eStyle
 );

/** WdgScreensaverEffectStartAnimation
* @brief        Set to start screensaver-effect or stop.
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[in ]   bRun                The animation control
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed, Not Support or Error parameter(NULL).
*
*/
MAE_Ret WdgScreensaverEffectStartAnimation
(
 IWidget                 *pWDGObject,
 boolean                 bRun
 );

#endif /* __FEATURE_MGL__ */
#endif /* __MMI_WDG_SCREENSAVER_EFFECT_H__ */

