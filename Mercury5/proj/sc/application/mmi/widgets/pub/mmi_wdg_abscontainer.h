#ifndef __MMI_WDG_ABSCONTAINER_H__
#define __MMI_WDG_ABSCONTAINER_H__
/* ===========================================================*/
// Description
/* ===========================================================*/
/**
*  AbsContainer, which is a rectangular widget, provides a container for putting widgets in
*  it by specify a relatively two-dimensional X-Y coordinates. In other words, widgets will
*  be placed in AbsContainer in accordance with the coordinates of the location. The (x,y)
*  coordinate is relative to the left and top position of AbsContainer object, that is to say,
*  the left-top coordinate of the container is (0,0) and the right-bottom coordinate is
*  (MAX_HEIGH, MAX_WIDTH). Moreover, it also can be set the background color,
*  background image, Padding, and Border.
*
*
*               ex: the AbsContainer
*        (0,0) +-----------------+
*              |   @             |   <- @ is a widget in (20, 30).
*              |                 |
*              +-----------------+ (100, 100)
*/

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_abscontainer.h"
#include "mmi_mae_window.h"

/*=============================================================*/
// functions
/*=============================================================*/

/** WdgAbsContainerCreateForWnd
* @brief        AbsContainer widget create function for Window
*
* @param[in]    hWin         The window handle
* @param[in]    pPos            A pointer of widget position; can't be NULL.
* @param[in]    pSize           A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID       The widget unique ID of window
*
* @retval       The pointer of AbsContainer  Success.
* @retval       NULL                         Failed.
*
*/
IWidget* WdgAbsContainerCreateForWnd
(
    HWIN     hWin,
    Pos_t           *pPos,
    WidgetSize_t    *pSize,
    u16             nWidgetID
);
/*=============================================================*/
/** WdgAbsContainerCreate
* @brief        Create AbsContainer widget
*
* @retval       The pointer of AbsContainer  Success.
* @retval       NULL                         Failed.
*
*/
IWidget* WdgAbsContainerCreate
(
    void
);

/** WdgAbsContainerAdd
* @brief        Add a widget in the AbsContainer
*
* @param[in]    pWDGAbsContainer        The pointer of AbsContainer
* @param[in]    pWidget                 A pointer of IWidget interface object to add
* @param[in]    pRefWidget              The reference widget. A pointer of IWidget interface object to be reference
* @param[in]    isUpper                 TRUE: add the widget to the above of the reference widget,
*                                       FALSE: add the widget to the below of the reference widget
* @param[in]    pWPos                   The position of widget
*
* @retval       MAE_RET_SUCCESS         Success.
* @retval       MAE_RET_BAD_PARAM       Failed. pIWidget is NULL or pRefWidget not found.
* @retval       MAE_RET_OUT_OF_MEMORY   Failed. Memory is not enough.
*
*/
MAE_Ret WdgAbsContainerAdd
(
    IWidget    *pWDGAbsContainer,
    IWidget    *pWidget,
    IWidget    *pRefWidget,
    boolean    isUpper,
    Pos_t      *pWPos
);

/** WdgAbsContainerDelete
* @brief        Delete a widget from the AbsContainer
*
* @param[in]    pWDGAbsContainer        The pointer of AbsContainer
* @param[in]    pWidget                 A pointer of IWidget interface object to delete
*
* @retval       MAE_RET_SUCCESS         Success. Successfully remove.
* @retval       MAE_RET_FAILED          Failed. pIWidget is NULL or not found.
*
*/
MAE_Ret WdgAbsContainerDelete
(
    IWidget    *pWDGAbsContainer,
    IWidget    *pWidget
);

/** WdgAbsContainerMove
* @brief        Move the widget in container's stack
*
* @param[in]    pWDGAbsContainer      The pointer of AbsContainer
* @param[in]    pWidget               A pointer of IWidget interface object to be moved
* @param[in]    pRefWidget            A pointer of IWidget interface object to be referred to
* @param[in]    isUpper               A boolean, TRUE is moving the widget to the above of referred widget,
*                                     FALSE is moving the widget to the below of referred widget
*
* @retval       MAE_RET_SUCCESS       Success.
* @retval       MAE_RET_BAD_PARAM     Failed. pIWidget is NULL, or pIWidget not found in widget stack,
*                                     or pRefWidget not found in widget stack.
*
*/
MAE_Ret WdgAbsContainerMove
(
    IWidget    *pWDGAbsContainer,
    IWidget    *pWidget,
    IWidget    *pRefWidget,
    boolean    isUpper
);

/** WdgAbsContainerAddToTopMost
* @brief        Add a widget to top in the AbsContainer
*
* @param[in]    pWDGAbsContainer     The pointer of AbsContainer
* @param[in]    pWidget              A pointer of IWidget interface object to add
* @param[in]    pPos                The position of widget
*
* @retval       MAE_RET_SUCCESS      Success.
* @retval       others               Failed.
*
*/
MAE_Ret WdgAbsContainerAddToTopMost
(
    IWidget    *pWDGAbsContainer,
    IWidget    *pWidget,
    Pos_t      *pPos
);

/** WdgAbsContainerAddToBottomMost
* @brief        Add a widget to bottom in the AbsContainer
*
* @param[in]    pWDGAbsContainer     The pointer of AbsContainer
* @param[in]    pWidget              A pointer of IWidget interface object to add
* @param[in]    pPos                The position of widget
*
* @retval       MAE_RET_SUCCESS      Success.
* @retval       others               Failed.
*
*/
MAE_Ret WdgAbsContainerAddToBottomMost
(
    IWidget    *pWDGAbsContainer,
    IWidget    *pWidget,
    Pos_t      *pPos
);

/** WdgAbsContainerMoveToTop
* @brief        Move the widget to the top of container's widget stack
*
* @param[in]    pWDGAbsContainer        The pointer of AbsContainer
* @param[in]    pWidget                 A pointer of IWidget interface object to be moved
*
* @retval       MAE_RET_SUCCESS         Success. Moving is successful.
* @retval       MAE_RET_BAD_PARAM       Failed. pIWidget is NULL, or pIWidget not found in widget stack.
* @retval       MAE_RET_NOT_SUPPORTED   Failed. Some kind of container does not support.
*
*/
MAE_Ret WdgAbsContainerMoveToTop
(
    IWidget    *pWDGAbsContainer,
    IWidget    *pWidget
);

/** WdgAbsContainerMoveToBottom
* @brief        Move the widget to the bottom of container's widget stack
*
* @param[in]    pWDGAbsContainer        The pointer of AbsContainer
* @param[in]    pWidget                 A pointer of IWidget interface object to be moved
*
* @retval       MAE_RET_SUCCESS         Success. Moving is successful.
* @retval       MAE_RET_BAD_PARAM       Failed. pIWidget is NULL, or pIWidget not found in widget stack.
* @retval       MAE_RET_NOT_SUPPORTED   Failed. Some kind of container does not support.
*
*/
MAE_Ret WdgAbsContainerMoveToBottom
(
    IWidget    *pWDGAbsContainer,
    IWidget    *pWidget
);
/*=============================================================*/

/** WdgAbsContainerMoveFocusToWidget
* @brief        This function can move the focus to a specific widget in Abs container.
*
* @param[in]    pWDGAbsContainer        The pointer of Abs Container.
* @param[in]    pChildWdg               A new focused widget we want of Abs Container.
*
*/
void WdgAbsContainerMoveFocusToWidget
(
    IWidget    *pWDGAbsContainer,
    IWidget    *pChildWdg
);

/** WdgAbsContainerMoveFocusToTopWidget
* @brief        This function can move the focus to the top widget in Abs container.
*
* @param[in]    pWDGAbsContainer   The pointer of Abs Container.
*
*/
void WdgAbsContainerMoveFocusToTopWidget
(
    IWidget    *pWDGAbsContainer
);

/** WdgAbsContainerMoveFocusToBottomWidget
* @brief    This function can move the focus to the bottom widget in Abs container's stack.
*
* @param[in]    pWDGAbsContainer    The pointer of Abs Container.
*
*/
void WdgAbsContainerMoveFocusToBottomWidget
(
    IWidget    *pWDGAbsContainer
);

/** WdgAbsContainerMoveFocusToNextWidget
* @brief    This function can move the focus to the next widget of the focused widget.
*
* @param[in]    pWDGAbsContainer    The pointer of Abs Container.
*
*/
void WdgAbsContainerMoveFocusToNextWidget
(
    IWidget    *pWDGAbsContainer
);

/** WdgAbsContainerMoveFocusToPrevWidget
* @brief    This function can move the focus to the previous widget of the focused widget.
*
* @param[in]    pWDGAbsContainer    The pointer of Abs Container.
*
*/
void WdgAbsContainerMoveFocusToPrevWidget
(
    IWidget    *pWDGAbsContainer
);

/** WdgAbsContainerSetPos
* @brief        Set position of the widget in the AbsContainer(Please use WdgAbsContainerSetPosition!!)
*
* @param[in]    pWDGAbsContainer    The pointer of AbsContainer
* @param[in]    pWidget             A pointer of IWidget interface object to set position
* @param[in]    pPos                A pointer of Position structure
*
* @retval       MAE_RET_SUCCESS     Success.
* @retval       others              Failed.
*
*/
MAE_Ret WdgAbsContainerSetPos
(
    IWidget         *pWDGAbsContainer,
    IWidget         *pWidget,
    const WPos_t    *pPos
);

/** WdgAbsContainerSetPosition
* @brief        Set position of the widget in the AbsContainer
*
* @param[in]    pWDGAbsContainer    The pointer of AbsContainer
* @param[in]    pWidget             A pointer of IWidget interface object to set position
* @param[in]    pPos                A pointer of Position structure
*
* @retval       MAE_RET_SUCCESS     Success.
* @retval       others              Failed.
*
*/
MAE_Ret WdgAbsContainerSetPosition
(
    IWidget         *pWDGAbsContainer,
    IWidget         *pWidget,
    const Pos_t     *pPos
);

/** WdgAbsContainerSetLayoutInverseByLanguage
* @brief        Set the widget layout in container is right-to-left or left-to-right
*               that dependent on the direction of current display language or Not.
*
* @param[in]    pWDGAbsContainer      The pointer of AbsContainer
* @param[in]    bLayoutInverse        Layout inverse depends by language (TRUE or FALSE)
*
*
*/
void WdgAbsContainerSetLayoutInverseByLanguage
(
    IWidget     *pWDGAbsContainer,
    boolean     bLayoutInverse
);

/** WdgAbsContainerGetPos
* @brief        Get position of the widget in the AbsContainer (Please use WdgAbsContainerGetPosion!!)
*
* @param[in]    pWDGAbsContainer    The pointer of AbsContainer
* @param[in]    pWidget             A pointer of IWidget interface object to get position
* @param[out]   pPos                A pointer of Position structure
*
* @retval       MAE_RET_SUCCESS     Success.
* @retval       others              Failed.
*
*/
MAE_Ret WdgAbsContainerGetPos
(
    IWidget    *pWDGAbsContainer,
    IWidget    *pWidget,
    WPos_t     *pPos
);

/** WdgAbsContainerGetPosition
* @brief        Get position of the widget in the AbsContainer
*
* @param[in]    pWDGAbsContainer    The pointer of AbsContainer
* @param[in]    pWidget             A pointer of IWidget interface object to get position
* @param[out]   pPos                A pointer of Position structure
*
* @retval       MAE_RET_SUCCESS     Success.
* @retval       others              Failed.
*
*/
MAE_Ret WdgAbsContainerGetPosition
(
    IWidget    *pWDGAbsContainer,
    IWidget    *pWidget,
    Pos_t      *pPos
);

/** WdgAbsContainerGetObjWidget
* @brief        Get the widget based on pRefWidget in container's widget stack
*
* @param[in]    pWDGAbsContainer    The pointer of AbsContainer
* @param[in]    pRefWidget          A pointer of IWidget interface object to be reference
* @param[in]    isUpper             A boolean flag, TRUE to search the top of "pRefWidget";
*                                   FALSE to search to bottom of "pRefWidget".
* @param[in]    isWrap              A boolean flag;
*                                   TRUE : if "pRefWidget" is most top widget you can get most bottom when "isUpper" is TRUE.
*                                   if "pRefWidget" is most bottom widget you can get most top when "isUpper" is FALSE.
*                                   FALSE: if "pRefWidget" is most top widget you can't any widget when "isUpper" is TRUE.
*                                   if "pRefWidget" is most bottom widget you can't any widget when "isUpper" is FALSE.
*
* @retval       NULL.               If reference widget not found or stack empty.
* @retval       IWidget*            Get a widget according to the parameters condition.
*
*/
IWidget* WdgAbsContainerGetObjWidget
(
    IWidget    *pWDGAbsContainer,
    IWidget    *pRefWidget,
    boolean    isUpper,
    boolean    isWrap
);

/** WdgAbsContainerGetObjTopMostWidget
* @brief        The function get top most widget in the AbsContainer
*
* @param[in]    pWDGAbsContainer    The pointer of AbsContainer
*
* @retval       IWidget*            A pointer of IWidget object
* @retval       NULL                Failed.
*
*/
IWidget* WdgAbsContainerGetObjTopMostWidget
(
    IWidget    *pWDGAbsContainer
);

/** WdgAbsContainerGetObjBottomMostWidget
* @brief        The function get bottom most widget in the AbsContainer
*
* @param[in]    pWDGAbsContainer    The pointer of AbsContainer
*
* @retval       IWidget*            A pointer of IWidget object
* @retval       NULL                Failed.
*
*/
IWidget* WdgAbsContainerGetObjBottomMostWidget
(
    IWidget    *pWDGAbsContainer
);
/*=============================================================*/

/** WdgAbsContainerGetLayoutInverseByLanguage
* @brief        Get the widget layout in container right-to-left or left-to-right
*                  that dependent on the direction of current display language or Not.
*
* @param[in]    pWDGAbsContainer    The pointer of AbsContainer
*
* @retval       boolean                Layout inverse by language (TRUE or FALSE)
*
*/
boolean WdgAbsContainerGetLayoutInverseByLanguage
(
    IWidget    *pWDGAbsContainer
);


/**
* WdgAbsContainerGetObjFocusedWidget
* @brief    This function can get the focused widget object instance in Abs container.
*
* @param    pWDGAbsContainer    The pointer of Abs container.
*
* @retval   The widget which is the focused widget in Abs container.
*/
IWidget* WdgAbsContainerGetObjFocusedWidget
(
    IWidget    *pWDGAbsContainer
);

#endif	//__MMI_WDG_ABSCONTAINER_H__
/*=============================================================*/
// end of file
