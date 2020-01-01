/**
* @file    mmi_wdg_glowtext.h
* 
*/
#ifndef __MMI_WDG_GLOWTEXT_H__
#define __MMI_WDG_GLOWTEXT_H__

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

/** WdgGlowTextCreateForWnd
* @brief        Create GlowText widget and set size for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
*
* @retval       The pointer of GlowText  Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgGlowTextCreateForWnd
(
 HWIN      hWin,
 Pos_t            *pPos,
 WidgetSize_t     *pSize,
 u16              nWidgetID
 );

/** WdgGlowTextCreate
* @brief        Create GlowText widget
*
* @retval       The pointer of GlowText  Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgGlowTextCreate
(
 void
 );

/** WdgGlowTextSetTextByID
* @brief        Set widget text by ID
*
* @param[in]    pWDGGlowText      The pointer of IWidget interface object
* @param[in]    nTextID           Id of the text label
*
* @retval       None
*
*/
__INLINE void WdgGlowTextSetTextByID
(
    IWidget                 *pWDGGlowText,
    u32                     nTextID
)
{
	WdgCommonSetProperty(pWDGGlowText, PROP_GLOWTEXT_WDG_TEXT_ID, nTextID);
}

/** WdgGlowTextSetTextPos
* @brief        Set GlowText widget background image position
*
* @param[in]    pWDGGlowText   The pointer of IWidget interface object
* @param[in]    pWPos          The position of GlowText widget background image position
*
* @retval       None
*
*/
__INLINE void WdgGlowTextSetTextPos
(
 IWidget                *pWDGGlowText,
 WPos_t                 *pWPos
 )
{
	WdgCommonSetProperty(pWDGGlowText, PROP_GLOWTEXT_WDG_TEXT_POS, (u32)pWPos);
}

/** WdgGlowTextSetSliderBGSize
* @brief        Set GlowText widget background size
*
* @param[in]    pWDGGlowText   The pointer of IWidget interface object
* @param[in]    pWidgetSize    The GlowText widget background size
*
* @retval       None
*
*/
__INLINE void WdgGlowTextSetTextSize
(
 IWidget              *pWDGGlowText,
 WidgetSize_t         *pWidgetSize
 )
{
	WdgCommonSetProperty(pWDGGlowText, PROP_GLOWTEXT_WDG_TEXT_SIZE, (u32)pWidgetSize);
}

/** WdgGlowTextGetSwitchPos
* @brief        Get GlowText widget position
*
* @param[in]    pWDGGlowText      The pointer of IWidget interface object
* @param[out]   pWPos             GlowText widget position
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgGlowTextGetTextPos
(
 IWidget                *pWDGGlowText,
 WPos_t                 *pWPos
 )
{
	return WdgCommonGetProperty(pWDGGlowText, PROP_GLOWTEXT_WDG_TEXT_POS, (u32*)pWPos);
}

/** WdgGlowTextGetSwitchSize
* @brief        Get GlowText widget switch size
*
* @param[in]    pWDGGlowText      The pointer of IWidget interface object
* @param[out]   pWidgetSize       The GlowText widget switch size
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgGlowTextGetTextSize
(
 IWidget              *pWDGGlowText,
 WidgetSize_t         *pWidgetSize
 )
{
	return WdgCommonGetProperty(pWDGGlowText, PROP_GLOWTEXT_WDG_TEXT_SIZE, (u32*)pWidgetSize);
}


#endif /*__MMI_WDG_GLOWTEXT_H__ */


