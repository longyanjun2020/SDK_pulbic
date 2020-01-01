/**
* @file    mmi_wdg_AnimImage.h
* @version $Id: mmi_wdg_AnimImage.h $
* @brief   AnimImage Widget
*<Description>
*
*
*
*/

#ifndef __MMI_WDG_ANIMIMAGE_H__
#define __MMI_WDG_ANIMIMAGE_H__

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

/*=============================================================*/
// functions
/*=============================================================*/
/** WdgAnimImageCreateForWnd
* @brief        Create AnimImage Widget and set the AnimImage value for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
* @param[in]    bDirectToogle       TRUE: When receive Action key it will toggle AnimImage item directly,
*                                   FALSE: Do Not direct toggle AnimImage item.
*
* @retval       The pointer of AnimImage         Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgAnimImageCreateForWnd
(
    HWIN             hWin,
    Pos_t                   *pPos,
    WidgetSize_t            *pSize,
    u16                     nWidgetID
);

/*=============================================================*/
/** WdgAnimImageCreate
* @brief        Create AnimImage widget
*
* @retval       The pointer of AnimImage         Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgAnimImageCreate
(
    void
);

/** WdgAnimImageSetImgAndRCInfo
* @brief        Set display data for AnimImage widget By Image ID.
*               Specific data for AnimImage widget.
*
* @param[in]    pIWidget         Pointer to the AnimImage widget
* @param[in]    nImageID      Image ID.
* @param[in]    nRowNum      Block in row
* @param[in]    nColNum      Block in col
*
* @retval       MAE_RET_SUCCESS  Success
* @retval       others           Failed
*
*/
MAE_Ret WdgAnimImageSetImgAndRCInfo
(
    IWidget                 *pIWidget,
    u32                     nImageID,
    u32 nRowNum,
    u32 nColNum
);

/** WdgAnimImageSetImgAnimSpeed
* @brief        Set Animation timer interval of tigger and start animation immediately .
* 
*
* @param[in]    pIWidget         Pointer to the AnimImage widget
* @param[in]    nMsec      timer interval.
*
* @retval       MAE_RET_SUCCESS  Success
* @retval       others           Failed
*
*/
MAE_Ret WdgAnimImageSetImgAnimSpeed
(
    IWidget                 *pIWidget,
    s32                     nMsec
);


/** WdgAnimImageStopAnimate
* @brief        Stop the animation
* 
*
* @param[in]    pIWidget         Pointer to the AnimImage widget
*
* @retval       MAE_RET_SUCCESS  Success
* @retval       others           Failed
*
*/
MAE_Ret WdgAnimImageStopAnimate
(
    IWidget                 *pIWidget
);


/** WdgAnimImageSetImgRegion
* @brief        display the specific region id to display. the order is sorted by Row major.
* 
*
* @param[in]    pIWidget         Pointer to the AnimImage widget
* @param[in]    nRegionIndex         the image index start by 0.
*
* @retval       MAE_RET_SUCCESS  Success
* @retval       others           Failed
*
*/
MAE_Ret WdgAnimImageSetImgRegion
(
    IWidget                 *pIWidget,
    u32                     nRegionIndex
);

#endif /* __MMI_WDG_AnimImage_H__ */
/*=============================================================*/
// end of file
