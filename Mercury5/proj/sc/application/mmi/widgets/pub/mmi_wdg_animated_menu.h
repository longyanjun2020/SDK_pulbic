#ifndef __MMI_WDG_ANIMATED_MENU_H__
#define __MMI_WDG_ANIMATED_MENU_H__
/* ===========================================================*/
// Description
/* ===========================================================*/
/**
*     If AP wants to show current volume level or lets users adjust the volume, Volume
*     widget can achieve this goal. Volume widget can display volume level stairs and
*     indicates current level. Users can use up/down navigation keys to tune volume
*     up/down. Volume widget also provides silence mode to force AP mute.
*
*
*          ex: Volume widget
*           +---------------------------------+
*            |    +----------+       ------   |
*            |    |          |       ------   |
*            |    |   IMG    |       ------   |  <- volume level stairs
*            |    |          |       ------   |
*            |    |          |       ------   |
*            |    |          |       ======   |  <- current level
*            |    +----------+       ======   |
*           +---------------------------------+
*
*
*/

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_class.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_window.h"
#include "mmi_mae_animated_menu_effect.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/** WdgAnimatedMenuCfgData_t
*
* @brief    pDecoratorWdg             The widget which is decorated by pWDGAnimatedMenu widget.
*           eAnimationStyle           Animation Style (check SetDisplayMenuAnimationStyle_e definition)
*
*/
typedef struct
{
    IWidget     *pDecoratorWdg;
    u8          eAnimationStyle; // check SetDisplayMenuAnimationStyle_e definition
}WdgAnimatedMenuCfgData_t;


#define     OFFSETVALUE     2

// Liquid
#define BOTTOM_UP_MIN       9
#define ONE_ROW_ELEMENTS    3
#define ALL_ELEMENTS        12

// Split
#define     SPLIT_GAP       3

/*=============================================================*/
// functions
/*=============================================================*/
/*=============================================================*/
//Common Function

/** WdgAnimatedMenuCreateForWnd
* @brief        AnimatedMenu widget create function for Window
*
* @param[in]    pWndHdl         The window handle
* @param[in]    pPos            A pointer of widget position; can't be NULL.
* @param[in]    pSize           A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID       The widget unique ID of window
* @param[in]    pData           Widget Common Data, refer to WdgAnimatedMenuCfgData_t.
*
* @retval       The pointer of ScrollBar pointer        Success.
* @retval       NULL                                    Failed.
*
*/
IWidget* WdgAnimatedMenuCreateForWnd
(
    HWIN                     		hWin,
    Pos_t                           *pPos,
    WidgetSize_t                    *pSize,
    u16                             nWidgetID,
    WdgAnimatedMenuCfgData_t        *pData
);

/*=============================================================*/
/** WdgAnimatedMenuCreate
* @brief        Create AnimatedMenu widget
*
* @retval       The pointer of AbsContainer  Success.
* @retval       NULL                         Failed.
*
*/
IWidget* WdgAnimatedMenuCreate
(
    void
);

/** WdgAnimatedMenuSetDecoratorWdg

* @brief         Set the widget which is decorated by AnimatedMenu widget
*
* @param[in]     pWDGAnimatedMenu    The AnimatedMenu widget which want to be set
* @param[in]     pChild              The widget which is decorated by pWDGAnimatedMenu widget.
*
* @retval        None.
*
*/
void WdgAnimatedMenuSetDecoratorWdg
(
    IWidget                 *pWDGAnimatedMenu,
    IWidget                 *pChild
);

/** WdgAnimatedMenuSetAnimationStyle
* @brief         Set the AnimatedMenu widget's Animation Style
*
* @param[in]     pWDGAnimatedMenu       The pointer of AnimatedMenu widget
* @param[in]     eStyle                 A pointer of SetDisplayMenuAnimationStyle_e for the widget's Animation Style
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgAnimatedMenuSetAnimationStyle
(
    IWidget     *pWDGAnimatedMenu,
    u8          eStyle              // check SetDisplayMenuAnimationStyle_e definition
);

/** WdgAnimatedMenuSetAnimatedEffectStyle
* @brief         Set the AnimatedMenu widget's Animated effect Style
*
* @param[in]     pWDGAnimatedMenu       The pointer of AnimatedMenu widget
* @param[in]     eStyle								The effect style, refer AnimatedMenuEffectStyle_e
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgAnimatedMenuSetAnimatedEffectStyle
(
    IWidget     *pWDGAnimatedMenu,
    u8          eStyle		// check AnimatedMenuEffectStyle_e definition
);

/** MainMenuAnimatedWdg_SetThmImgIDList
* @brief         Set the theme image id info
*
* @param[in]     pThis             The pointer of AnimatedMenu widget
* @param[in]     nThemeID          The index of grid item
* @param[in]     nImgID            The image ID
*
* @retval        None
*
*/
void MainMenuAnimatedWdg_SetThmImgIDList
(
    IWidget *pThis,
    u32 nThemeID, 
    u32 *nImgID
);

/*=============================================================*/
// end of file

#endif /* __MAE_MAINMENUAPP_ANIMATEDWDG_H__ */
