/**
* @file    mmi_wdg_propcontainer.h
* @version $Id: mmi_wdg_propcontainer.h 38890 2009-08-29 16:22:38Z zinc.chen $
* @brief   This file defines the interface of IPropContainer
*/
#ifndef __MMI_WDG_PROPCONTAINER_H__
#define __MMI_WDG_PROPCONTAINER_H__


/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_window.h"
#include "mmi_mae_propcontainer.h"
#include "mmi_wdg_common_interface.h"

/*=============================================================*/
// interface
/*=============================================================*/
/** WdgProContainerCreateForWnd
* @brief        Create PropContainer Widget and set the PropContainer value for Window
*
* @param[in]    hWin        The window handle
* @param[in]    pPos           A pointer of widget position; can't be NULL.
* @param[in]    pSize          A pointer of widget size; NULL means default value.
* @param[in]    nWdgId         The widget unique ID of window
* @param[in]    nLayoutStyle   Layout Style

*
* @retval       The pointer of PropContainer     Success.
* @retval       NULL                             Failed.
*
*/
__SLDPM_FREE__ IWidget* WdgProContainerCreateForWnd
(
    HWIN               hWin,
    Pos_t                     *pPos,
    WidgetSize_t              *pSize,
    u16                        nWdgId,
    WdgLayoutStyle_t           nLayoutStyle
);

/*=============================================================*/
/** WdgProContainerCreate
* @brief        Create PropContainer widget
*
* @retval       The pointer of PropContainer  Success.
* @retval       NULL                          Failed.
*
*/
__SLDPM_FREE__ IWidget* WdgProContainerCreate
(
    void
);

/** WdgPropContainerAdd
* @brief        The function add a widget in the PropContainer
*
* @param[in]    pProCntr     The pointer of PropContainer
* @param[in]    pWidget      A pointer of IWidget interface object to add
* @param[in]    pRefWdg      The reference widget. A pointer of IWidget interface object to be reference
* @param[in]    isUpper      TRUE: add the widget to the above of the reference widget,
*                            FALSE: add the widget to the below of the reference widget
* @param[in]    pProp        Proportion Setting to a PropContainer
*
* @retval       MAE_RET_SUCCESS           Success.
* @retval       MAE_RET_BAD_PARAM         Failed. pIWidget is NULL or pRefWdg not found.
* @retval       MAE_RET_OUT_OF_MEMORY     Failed. Memory is not enough.
*
*/
MAE_Ret WdgPropContainerAdd
(
    IWidget                *pProCntr,
    IWidget                *pWidget,
    IWidget                *pRefWdg,
    boolean                isUpper,
    WProp_t                *pProp
);


/** WdgPropContainerDel
* @brief        The function delete a widget from the PropContainer
*
* @param[in]    pProCntr    The pointer of PropContainer
* @param[in]    pWidget     A pointer of IWidget interface object to delete
*
* @retval       MAE_RET_SUCCESS   Success. Successfully to remove.
* @retval       MAE_RET_FAILED    Failed. pIWidget is NULL or not found.
*
*/
MAE_Ret WdgPropContainerDel
(
                IWidget                *pProCntr,
                IWidget                *pWidget
);


/** WdgPropContainerMove
* @brief        The function move the widget in container's widget stack
*
* @param[in]    pProCntr    The pointer of PropContainer
* @param[in]    pWidget     A pointer of IWidget interface object to be moved
* @param[in]    pRefWdg     A pointer of IWidget interface object to be referred to
* @param[in]    isUpper     A boolean, TRUE is moving the widget to the above of referred widget,
*                           FALSE is moving the widget to the below of referred widget
*
* @retval       MAE_RET_SUCCESS    Success.
* @retval       MAE_RET_BAD_PARAM  Failed. pIWidget is NULL, or pIWidget not found in widget stack,
*                                                                or pRefWdg not found in widget stack.
*
*/
MAE_Ret WdgPropContainerMove
(
                IWidget                *pProCntr,
                IWidget                *pWidget,
                IWidget                *pRefWdg,
                boolean                isUpper
);


/** WdgPropContainerAddToTopMost
* @brief        The function add a widget to top in the PropContainer
*
* @param[in]    pProCntr    The pointer of PropContainer
* @param[in]    pWidget     A pointer of IWidget interface object to add
* @param[in]    pProp       Proportion Setting to a PropContainer
*
* @retval       MAE_RET_SUCCESS       Success.
* @retval       others                Failed.
*
*/
MAE_Ret WdgPropContainerAddToTopMost
(
    IWidget             *pProCntr,
    IWidget             *pWidget,
    WProp_t             *pProp
);

/** WdgPropContainerAddToBottomMost
* @brief    The function add a widget to bottom in the PropContainer
*
* @param[in]    pProCntr    The pointer of PropContainer
* @param[in]    pWidget     A pointer of IWidget interface object to add
* @param[in]    pProp       Proportion Setting to a PropContainer
*
* @retval       MAE_RET_SUCCESS        Success.
* @retval       others                 Failed.
*
*/
MAE_Ret WdgPropContainerAddToBottomMost
(
    IWidget             *pProCntr,
    IWidget             *pWidget,
    WProp_t             *pProp
);

/** WdgPropContainerMoveToTop
* @brief        The function move the widget to the top of container's widget stack
*
* @param[in]    pProCntr    The pointer of PropContainer
* @param[in]    pWidget     A pointer of IWidget interface object to be moved
*
* @retval       MAE_RET_SUCCESS        Success. Moving is successful.
* @retval       MAE_RET_BAD_PARAM      Failed. pIWidget is NULL, or pIWidget not found in widget stack.
* @retval       MAE_RET_NOT_SUPPORTED  Failed. Some kind of container does not support.
*
*/
MAE_Ret WdgPropContainerMoveToTop
(
    IWidget             *pProCntr,
    IWidget             *pWidget
);


/** WdgPropContainerMoveToBottom
* @brief        The function move the widget to the bottom of container's widget stack
*
* @param[in]    pProCntr    The pointer of PropContainer
* @param[in]    pWidget     A pointer of IWidget interface object to be moved
*
* @retval       MAE_RET_SUCCESS         Success. Moving is successful.
* @retval       MAE_RET_BAD_PARAM       Failed. pIWidget is NULL, or pIWidget not found in widget stack.
* @retval       MAE_RET_NOT_SUPPORTED   Failed. Some kind of container does not support.
*
*/
MAE_Ret WdgPropContainerMoveToBottom
(
    IWidget             *pProCntr,
    IWidget             *pWidget
);
/*=============================================================*/
/** WdgPropContainerMoveFocusToWdg
* @brief    This function can move the focus to a specific widget in PropContainer.
*         If the specific widget(pChildWdg) is not in PropContainer, it will return MAE_RET_FAILED.
*
* @param[in]    pProCntr    The pointer of PropContainer.
* @param[in]    pChildWdg   A new focused widget we want of PropContainer.
*
* @retval       MAE_RET_SUCCESS   Success. The widget can handle this request.
* @retval       MAE_RET_FAILED    Failed. The widget can not handle this request.
*/
MAE_Ret WdgPropContainerMoveFocusToWdg
(
    IWidget                 *pProCntr,
    IWidget                 *pChildWdg
);

/** WdgPropContainerMoveFocusToWdg
* @brief    This function can move the focus to a specific widget in PropContainer.
*         If the specific widget(pChildWdg) is not in PropContainer, it will return MAE_RET_FAILED.
*
* @param[in]    pProCntr    The pointer of PropContainer.
*
* @retval       MAE_RET_SUCCESS  Success. The widget can handle this request.
* @retval       MAE_RET_FAILED   Failed. The widget can not handle this request.
*/
MAE_Ret WdgPropContainerMoveFocusToTopWdg
(
    IWidget                 *pProCntr
);

/** WdgPropContainerMoveFocusToBottomWdg
* @brief    This function can move the focus to the bottom widget in PropContainer's stack.
*
* @param[in]    pProCntr  The pointer of PropContainer.
*
* @retval       MAE_RET_SUCCESS   Success. The widget can handle this request.
* @retval       MAE_RET_FAILED    Failed. The widget can not handle this request.
*/
MAE_Ret WdgPropContainerMoveFocusToBottomWdg
(
    IWidget                 *pProCntr
);

/** WdgPropContainerMoveFocusToNextWdg
* @brief    This function can move the focus to the next widget of the focused widget.
*
* @param[in]    pProCntr  The pointer of PropContainer.
*
* @retval       MAE_RET_SUCCESS   Success. The widget can handle this request.
* @retval       MAE_RET_FAILED    Failed. The widget can not handle this request.
*/
MAE_Ret WdgPropContainerMoveFocusToNextWdg
(
    IWidget                 *pProCntr
);

/** WdgPropContainerMoveFocusTopPrevWdg
* @brief    This function can move the focus to the previous widget of the focused widget.
*
* @param[in]    pProCntr  The pointer of PropContainer.
*
* @retval       MAE_RET_SUCCESS   Success. The widget can handle this request.
* @retval       MAE_RET_FAILED    Failed. The widget can not handle this request.
*/
MAE_Ret WdgPropContainerMoveFocusTopPrevWdg
(
    IWidget                 *pProCntr
);


/*=============================================================*/
/** WdgPropContainerSetProp
* @brief        Set the proportion of specific widget to container
*
* @param[in]    pProCntr    The pointer of PropContainer
* @param[in]    pWidget     A pointer of IWidget interface object to set proportion
* @param[in]    pProp       A pointer of Proportion structure
*
* @retval       MAE_RET_SUCCESS  Success.
* @retval       others           Failed.
*
*/
MAE_Ret WdgPropContainerSetProp
(
    IWidget                *pProCntr,
    IWidget                *pWidget,
    const     WProp_t      *pProp
);

/** WdgPropContainerSetWdgPadding
* @brief        Set the padding of specific widget to container
*
* @param[in]    pProCntr          The pointer of PropContainer
* @param[in]    pWidget           A pointer of IWidget interface object to set padding
* @param[in]    nBeforePixels     padding pixels before this widget
* @param[in]    nAfterPixels      padding pixels after this widget
*
* @retval       MAE_RET_SUCCESS     Success.
* @retval       others              Failed.
*
*/
MAE_Ret WdgPropContainerSetWdgPadding
(
    IWidget            *pProCntr,
    IWidget            *pWidget,
    u16                 nBeforePixels,
    u16                 nAfterPixels
);

/** WdgPropContainerSetLayoutStyle
* @brief        Set the widget layout vertical or horizontal
*
* @param[in]    pProCntr        The pointer of PropContainer
* @param[in]    nLayoutStyle    Layout Style
*
* @retval       MAE_RET_SUCCESS    Success.
* @retval       others             Failed.
*
*/
__INLINE MAE_Ret WdgPropContainerSetLayoutStyle
(
                IWidget             *pProCntr,
                WdgLayoutStyle_t     nLayoutStyle
)
{
    return WdgCommonSetProperty(pProCntr, PROP_LAYOUT_STYLE, (u32)nLayoutStyle);
}


/** WdgPropContainerSetLayoutInverseByLang
* @brief        Set the widget layout in container is right-to-left or left-to-right
*               that dependent on the direction of current display language or Not.
*
* @param[in]    pProCntr   The pointer of PropContainer
* @param[in]    bLayoutInverse     Layout inverse depends by language (TRUE or FALSE)
*
* @retval       MAE_RET_SUCCESS   Success.
* @retval       others            Failed.
*
*/
__INLINE MAE_Ret WdgPropContainerSetLayoutInverseByLang
(
                IWidget             *pProCntr,
                boolean             bLayoutInverse
)
{
    return WdgCommonSetProperty(pProCntr, PROP_LAYOUT_INVERSE_BY_LANGUAGE, (u32)bLayoutInverse);
}

/*=============================================================*/

/** WdgPropContainerGetWdg
* @brief        The function get the widget based on pRefWdg in container's widget stack
*
* @param[in]    pProCntr            he pointer of PropContainer
* @param[in]    pRefWdg             A pointer of IWidget interface object to be reference
* @param[in]    isUpper             A boolean flag, TRUE to search the top of "pRefWdg";
*                                   FALSE to search to bottom of "pRefWdg".
* @param[in]    isWrap              A boolean flag;
*                                   TRUE : if "pRefWdg" is most top widget you can get most bottom when "isUpper" is TRUE.
*                                          if "pRefWdg" is most bottom widget you can get most top when "isUpper" is FALSE.
*                                   FALSE: if "pRefWdg" is most top widget you can't any widget when "isUpper" is TRUE.
*                                          if "pRefWdg" is most bottom widget you can't any widget when "isUpper" is FALSE.
*
* @retval       NULL.               If reference widget not found or stack empty.
* @retval       IWidget*            Get a widget according to the parameters condition.
*
*/
IWidget* WdgPropContainerGetWdg
(
                IWidget            *pProCntr,
                IWidget            *pRefWdg,
                boolean            isUpper,
                boolean            isWrap
);

/** WdgPropContainerGetProp
* @brief        Get the proportion of specific widget from container
*
* @param[in]    pProCntr   The pointer of PropContainer
* @param[in]    pWidget    A pointer of IWidget interface object to get proportion
* @param[out]   pProp      A point of Proportion structure
*
* @retval       MAE_RET_SUCCESS    Success.
* @retval       others             Failed.
*
*/
MAE_Ret WdgPropContainerGetProp
(
                IWidget              *pProCntr,
                IWidget              *pWidget,
                WProp_t              *pProp
);

/** PropContainer_GetWidgetPadding
* @brief        Set the padding of specific widget to container
*
* @param[in]    pProCntr        The pointer of PropContainer
* @param[in]    pWidget         A pointer of IWidget interface object to set padding
* @param[out]   pBeforePixels   A pointer of padding pixels before this widget
* @param[out]   pAfterPixels    A pointer of padding pixels after this widget
*
* @retval       MAE_RET_SUCCESS  Success.
* @retval       others           Failed.
*
*/
MAE_Ret WdgPropContainerGetWdgPadding
(
                IWidget           *pProCntr,
                IWidget           *pWidget,
                u16               *pBeforePixels,
                u16               *pAfterPixels
);


/** WdgPropContainerGetTopMostWdg
* @brief        The function get top most widget in the PropContainer
*
* @param[in]    pProCntr    The pointer of PropContainer
*
* @retval       IWidget*          A pointer of IWidget object
* @retval       NULL              Failed.
*
*/
IWidget* WdgPropContainerGetTopMostWdg
(
                IWidget            *pProCntr
);


/** WdgPropContainerGetBottomMostWdg
* @brief        The function get bottom most widget in the PropContainer
*
* @param[in]    pProCntr    The pointer of PropContainer
*
* @retval       IWidget*          A pointer of IWidget object
* @retval       NULL              Failed.
*
*/
IWidget* WdgPropContainerGetBottomMostWdg
(
                IWidget             *pProCntr
);

/** WdgPropContainerGetLayoutStyle
* @brief        Get the widget layout vertical or horizontal
*
* @param[in]    pProCntr    The pointer of PropContainer
*
* @retval       WdgLayoutStyle_t   Layout Style
*
*/
WdgLayoutStyle_t WdgPropContainerGetLayoutStyle
(
                IWidget              *pProCntr
);

/** WdgPropContainerGetLayoutInverseByLang
* @brief        Get the widget layout in container right-to-left or left-to-right.
*
* @param[in]    pProCntr    The pointer of PropContainer
*
* @retval       boolean    Layout inverse by language (TRUE or FALSE)
*
*/
boolean WdgPropContainerGetLayoutInverseByLang
(
                IWidget                 *pProCntr
);

/**
* WdgPropContainerGetFocusedWdg
* @brief    This function can get the focused widget object instance in PropContainer.
*
* @param    pProCntr  The pointer of PropContainer.
*
* @retval   MAE_RET_SUCCESS     Success. The widget can handle this request.
* @retval   MAE_RET_FAILED      Failed. The widget can not handle this request.
* @retval   MAE_RET_BAD_PARAM   Failed. Invalid parameters.
*/
IWidget* WdgPropContainerGetFocusedWdg
(
    IWidget                *pProCntr
);


#endif	//__MMI_WDG_PROPCONTAINER_H__
/*=============================================================*/
// end of file
