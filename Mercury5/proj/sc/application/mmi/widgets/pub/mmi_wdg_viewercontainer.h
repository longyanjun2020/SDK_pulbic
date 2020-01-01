/**
* @file    mmi_wdg_viewercontainer.h
* @version $Id: mmi_wdg_viewercontainer.h 37261 2009-08-05 12:20:57Z steve.lee $
*
* @brief   This file defines IViewerContainer interface and 
*          CLSID_VIEWERCONTAINER class which implements IViewerContainer interface.
* <Interface Description>
*
* <Class Description>
*     Viewer Container is a kind of container,which implements IViewerContainer interface.
*     Application can add one or more widgets into viewer-container with description structure WViewerDesc_t.
*     Application can decide the child widget can be focused or not via the variable CanFocus in WViewerDesc_t
*     data structure.
*
*     The focus order will depend on the order of child widget stack in this viewer-container. AP can change the
*     order via IVIEWERCONTAINER_Move() interface function if the child widget is already added into this container.
*
*     The default keys to move focus next/previous are MAE_KEY_SIDE_DN and MAE_KEY_SIDE_UP. AP can change them by
*     properties PROP_VIEWERCNTR_MOVE_NEXT_FOCUS_KEY/ PROP_VIEWERCNTR_MOVE_PREV_FOCUS_KEY.
*
*     User can press navigation keys MAE_KEY_DOWN/MAE_KEY_UP to move the view of whole container. User also can use
*     touch panel to move the view of whole container.
*
*     This container supports to decorate a scrollbar widget for display scroll if the view range is larger than screen.
*
*/
#ifndef __MMI_WDG_VIEWERCONTAINER_H__
#define __MMI_WDG_VIEWERCONTAINER_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_container.h"
#include "mmi_mae_window.h"
#include "mmi_wdg_common_interface.h"


/*=============================================================*/
// type and define
/*=============================================================*/

/** WViewerDesc_t
*
* @brief    isVisible:    
*           x:   
*           y:         
*           CanFocus:   
*           bDrawFocusBorder:   
*
*/
typedef struct {
	boolean isVisible;
	s32 x;
	s32 y;
	boolean CanFocus;
	boolean bDrawFocusBorder;
} WViewerDesc_t;

/** WDGViewerDesc_t
*
* @brief    x:   
*           y:         
*           CanFocus:   
*           bDrawFocusBorder:   
*
*/
typedef struct {
    s32 x;
    s32 y;
    boolean CanFocus;
    boolean bDrawFocusBorder;
} WDGViewerDesc_t;

/** WDGViewerDesc_t
*
* @brief    nNextFocusKey:   the key id to move focus to next widget, Ex, MAE_KEY_1, MAE_KEY_LEFT...
*           nPrevFocusKey:   the key id to move focus to previous widget Ex, MAE_KEY_1, MAE_KEY_LEFT...   
*
*/
typedef struct
{
    MAE_Key_t           nNextFocusKey;    //the key id to move focus to next widget, Ex, MAE_KEY_1, MAE_KEY_LEFT...
    MAE_Key_t           nPrevFocusKey;    //the key id to move focus to previous widget Ex, MAE_KEY_1, MAE_KEY_LEFT...

}WdgViewerContainerMoveFocusKey_t;

/** WdgViewerContainerScrollKey_t
*
* @brief    nScrollUpKey:       the Key id to scroll up
*           nScrollDownKey:     the Key id to scroll down
*           nScrollLeftKey:     the Key id to scroll left
*           nScrollRightKey:    the Key id to scroll right 
*
*/
typedef struct
{
    MAE_Key_t           nScrollUpKey;       //the Key id to scroll up
    MAE_Key_t           nScrollDownKey;     //the Key id to scroll down
    MAE_Key_t           nScrollLeftKey;     //the Key id to scroll left
    MAE_Key_t           nScrollRightKey;    //the Key id to scroll right

}WdgViewerContainerScrollKey_t;

/** PfnWdgViewerContainerScrollChange
* @brief      CB register by "PfnWdgViewerContainerScrollChange"
*             and will be trigger when WdgViewerContainerSetScrollData.
*
* @param[in]  pApplet         The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData        User data ap developer setting when register CB.
* @param[in]  nEvtCode        Widget Event Code, only useful for softkey event
* @param[in]  pScrollData     Info of scroll
* @param[in]  pIWidget        The widget instance
*
*/
typedef void (*PfnWdgViewerContainerScrollChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, ScrollData_t *pScrollData, IWidget *pWidget);

/** PfnWdgViewerContainerBoundTop
* @brief      CB register by "PfnWdgViewerContainerBoundTop"
*             and will be trigger when the focus move to the top item and can't wrap.
*
* @param[in]  pApplet         The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData        User data ap developer setting when register CB.
* @param[in]  nEvtCode        Widget Event Code, only useful for softkey event
* @param[in]  nReserve        Reserve for enhancement in the future
* @param[in]  pIWidget        The widget instance
*
*/
typedef void (*PfnWdgViewerContainerBoundTop) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);

/** PfnWdgViewerContainerBoundBottom
* @brief      CB register by "PfnWdgViewerContainerBoundBottom"
*             and will be trigger when the focus move to the end item and can't wrap.
*
* @param[in]  pApplet         The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData        User data ap developer setting when register CB.
* @param[in]  nEvtCode        Widget Event Code, only useful for softkey event
* @param[in]  nReserve        Reserve for enhancement in the future
* @param[in]  pIWidget        The widget instance
*
*/
typedef void (*PfnWdgViewerContainerBoundBottom) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);

/*=============================================================*/
// functions
/*=============================================================*/
/** WdgViewerContainerCreateForWnd
* @brief        Create ViewerContainer widget and set size for Window
*
* @param[in]    hWin        The window handle
* @param[in]    pPos           A pointer of widget position; can't be NULL.
* @param[in]    pSize          A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID      The widget unique ID of window
*
* @retval       The pointer of ViewerContainer     Success.
* @retval       NULL                               Failed.
*
*/
IWidget* WdgViewerContainerCreateForWnd
(
    HWIN            hWin,
    Pos_t                  *pPos,
    WidgetSize_t           *pSize,
    u16                    nWidgetID
);
/*=============================================================*/
/** WdgViewerContainerCreate
* @brief        Create ViewerContainer widget
*
* @retval       The pointer of ViewerContainer   Success.
* @retval       NULL                             Failed.
*
*/
IWidget* WdgViewerContainerCreate
(
    void
);

/** WdgViewerContainerAdd
* @brief        The function add a widget in the ViewerContainer
*
* @param[in]    pWDGViewerContainer     The pointer of ViewerContainer
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
MAE_Ret WdgViewerContainerAdd
(
                IWidget                *pWDGViewerContainer,
                IWidget                *pWidget,
                IWidget                *pRefWidget,
                boolean                isUpper,
                WDGViewerDesc_t        *pWPos
);

/** WdgViewerContainerDelete
* @brief        The function delete a widget from the ViewerContainer
*
* @param[in]    pWDGViewerContainer    The pointer of ViewerContainer
* @param[in]    pWidget                A pointer of IWidget interface object to delete
*
* @retval       MAE_RET_SUCCESS        Success. Successfully to remove.
* @retval       MAE_RET_FAILED         Failed. pIWidget is NULL or not found.
*
*/
MAE_Ret WdgViewerContainerDelete
(
                IWidget                *pWDGViewerContainer,
                IWidget                *pWidget
);

/** WdgViewerContainerMove
* @brief        The function move the widget in container's widget stack
*
* @param[in]    pWDGViewerContainer    The pointer of ViewerContainer
* @param[in]    pWidget                A pointer of IWidget interface object to be moved
* @param[in]    pRefWidget             A pointer of IWidget interface object to be referred to
* @param[in]    isUpper                A boolean, TRUE is moving the widget to the above of referred widget,
*                                      FALSE is moving the widget to the below of referred widget
*
* @retval       MAE_RET_SUCCESS        Success.
* @retval       MAE_RET_BAD_PARAM      Failed. pIWidget is NULL, or pIWidget not found in widget stack, or
*                                      pRefWidget not found in widget stack.
*
*/
MAE_Ret WdgViewerContainerMove
(
                IWidget                *pWDGViewerContainer,
                IWidget                *pWidget,
                IWidget                *pRefWidget,
                boolean                isUpper
);

/** WdgViewerContainerAddToTopMost
* @brief        The function add a widget to top in the ViewerContainer
*
* @param[in]    pWDGViewerContainer    The pointer of ViewerContainer
* @param[in]    pWidget                A pointer of IWidget interface object to add
* @param[in]    pWPos                  The position of widget
*
* @retval       MAE_RET_SUCCESS        Success.
* @retval       others                 Failed.
*
*/
MAE_Ret WdgViewerContainerAddToTopMost
(
    IWidget                *pWDGViewerContainer,
    IWidget                *pWidget,
    WDGViewerDesc_t        *pWPos
);

/** WdgViewerContainerAddToBottomMost
* @brief    The function add a widget to bottom in the ViewerContainer
*
* @param[in]    pWDGViewerContainer    The pointer of ViewerContainer
* @param[in]    pWidget                A pointer of IWidget interface object to add
* @param[in]    pWPos                  The position of widget
*
* @retval       MAE_RET_SUCCESS        Success.
* @retval       others                 Failed.
*
*/
MAE_Ret WdgViewerContainerAddToBottomMost
(
    IWidget                *pWDGViewerContainer,
    IWidget                *pWidget,
    WDGViewerDesc_t        *pWPos
);

/** WdgViewerContainerMoveFocusToWidget
* @brief    This function can move the focus to a specific widget in ViewerContainer.
*         If the specific widget(pChildWdg) is not in ViewerContainer, it will return MAE_RET_FAILED.
*
* @param[in]    pWDGViewerContainer  The pointer of ViewerContainer.
* @param[in]    pChildWdg            A new focused widget we want of ViewerContainer.
*
* @retval       MAE_RET_SUCCESS      Success. The widget can handle this request.
* @retval       MAE_RET_FAILED       Failed. The widget can not handle this request.
*/
MAE_Ret WdgViewerContainerMoveFocusToWidget
(
    IWidget                 *pWDGViewerContainer,
    IWidget                 *pChildWdg
);

/** WdgViewerContainerMoveFocusToWidget
* @brief    This function can move the focus to a specific widget in ViewerContainer.
*         If the specific widget(pChildWdg) is not in ViewerContainer, it will return MAE_RET_FAILED.
*
* @param[in]    pWDGViewerContainer  The pointer of ViewerContainer.
*
* @retval       MAE_RET_SUCCESS      Success. The widget can handle this request.
* @retval       MAE_RET_FAILED       Failed. The widget can not handle this request.
*/
MAE_Ret WdgViewerContainerMoveFocusToTopWidget
(
    IWidget                 *pWDGViewerContainer
);

/** WdgViewerContainerMoveFocusToBottomWidget
* @brief    This function can move the focus to the bottom widget in ViewerContainer's stack.
*
* @param[in]    pWDGViewerContainer  The pointer of ViewerContainer.
*
* @retval       MAE_RET_SUCCESS      Success. The widget can handle this request.
* @retval       MAE_RET_FAILED       Failed. The widget can not handle this request.
*/
MAE_Ret WdgViewerContainerMoveFocusToBottomWidget
(
    IWidget                 *pWDGViewerContainer
);

/** WdgViewerContainerMoveFocusToNextWidget
* @brief    This function can move the focus to the next widget of the focused widget.
*
* @param[in]    pWDGViewerContainer  The pointer of ViewerContainer.
*
* @retval       MAE_RET_SUCCESS      Success. The widget can handle this request.
* @retval       MAE_RET_FAILED       Failed. The widget can not handle this request.
*/
MAE_Ret WdgViewerContainerMoveFocusToNextWidget
(
    IWidget                 *pWDGViewerContainer
);

/** WdgViewerContainerMoveFocusToPrevWidget
* @brief    This function can move the focus to the previous widget of the focused widget.
*
* @param[in]    pWDGViewerContainer  The pointer of ViewerContainer.
*
* @retval       MAE_RET_SUCCESS      Success. The widget can handle this request.
* @retval       MAE_RET_FAILED       Failed. The widget can not handle this request.
*/
MAE_Ret WdgViewerContainerMoveFocusToPrevWidget
(
    IWidget                 *pWDGViewerContainer
);
/*=============================================================*/
/** WdgViewerContainerSetPosAndFocus
* @brief        To change the position and focus ability of the specific widget.
*
* @param[in]    pWDGViewerContainer    The pointer of ViewerContainer
* @param[in]    pWidget                A specific widget inside this viewer-container.
* @param[in]    pViewerDesc            A pointer of WViewerDesc_t data structure which stores position
*                                      and focus information.
*
* @retval        MAE_RET_SUCCESS       Success.
* @retval        others                Failed.
*
*/
MAE_Ret WdgViewerContainerSetPosAndFocus
(
                IWidget                   *pWDGViewerContainer,
                IWidget                   *pWidget,
                WDGViewerDesc_t           *pViewerDesc
);

/** WdgViewerContainerSetMovingStep
* @brief        Set ViewerContainer moving step in pixels by touch on scroll
*
* @param[in]    pWDGViewerContainer  The ViewerContainer widget which want to be set
* @param[in]    nMovingStep          every moving step in pixels by touch on scroll
*
* @retval       None
*
*/
__INLINE void WdgViewerContainerSetMovingStep
(
    IWidget         *pWDGViewerContainer,
    u16             nMovingStep
)
{
    WdgCommonSetProperty(pWDGViewerContainer, PROP_VIEWERCNTR_MOVINGSTEP, (u32)nMovingStep);
}

/** WdgViewerContainerSetMoveNextFocusKey
* @brief        Set ViewerContainer the key id to move focus to next widget
*
* @param[in]    pWDGViewerContainer  The ViewerContainer widget which want to be set
* @param[in]    nNextFocusKey        The key id to move focus to next widget; Ex, MAE_KEY_1, MAE_KEY_LEFT...
*
* @retval       None
*
*/
__INLINE void WdgViewerContainerSetMoveNextFocusKey
(
    IWidget                 *pWDGViewerContainer,
    MAE_Key_t               nNextFocusKey
)
{
    WdgCommonSetProperty(pWDGViewerContainer, PROP_VIEWERCNTR_MOVE_NEXT_FOCUS_KEY, (u32)nNextFocusKey);
}

/** WdgViewerContainerSetMovePrevFocusKey
* @brief        Set ViewerContainer the key id to move focus to previous widget
*
* @param[in]    pWDGViewerContainer  The ViewerContainer widget which want to be set
* @param[in]    nPrevFocusKey        The key id to move focus to previous widget; Ex, MAE_KEY_1, MAE_KEY_LEFT...
*
* @retval       None
*
*/
__INLINE void WdgViewerContainerSetMovePrevFocusKey
(
    IWidget                 *pWDGViewerContainer,
    MAE_Key_t               nPrevFocusKey
)
{
    WdgCommonSetProperty(pWDGViewerContainer, PROP_VIEWERCNTR_MOVE_PREV_FOCUS_KEY, (u32)nPrevFocusKey);
}

/** WdgViewerContainerSetScrollUpKey
* @brief        Set ViewerContainer the Key id to scroll up
*
* @param[in]    pWDGViewerContainer  The ViewerContainer widget which want to be set
* @param[in]    nScrollUpKey         The Key id to scroll up; Ex, MAE_KEY_1, MAE_KEY_LEFT...
*
* @retval       None
*
*/
__INLINE void WdgViewerContainerSetScrollUpKey
(
    IWidget                 *pWDGViewerContainer,
    MAE_Key_t               nScrollUpKey
)
{
    WdgCommonSetProperty(pWDGViewerContainer, PROP_VIEWERCNTR_SCROLL_UP_KEY, (u32)nScrollUpKey);
}

/** WdgViewerContainerSetScrollDownKey
* @brief        Set ViewerContainer the Key id to scroll down
*
* @param[in]    pWDGViewerContainer  The ViewerContainer widget which want to be set
* @param[in]    nScrollDownKey       The Key id to scroll down; Ex, MAE_KEY_1, MAE_KEY_LEFT...
*
* @retval       None
*
*/
__INLINE void WdgViewerContainerSetScrollDownKey
(
    IWidget                 *pWDGViewerContainer,
    MAE_Key_t               nScrollDownKey
)
{
    WdgCommonSetProperty(pWDGViewerContainer, PROP_VIEWERCNTR_SCROLL_DOWN_KEY, (u32)nScrollDownKey);
}

/** WdgViewerContainerSetScrollLeftKey
* @brief        Set ViewerContainer the Key id to scroll left
*
* @param[in]    pWDGViewerContainer  The ViewerContainer widget which want to be set
* @param[in]    nScrollLeftKey       The Key id to scroll left; Ex, MAE_KEY_1, MAE_KEY_LEFT...
*
* @retval       None
*
*/
__INLINE void WdgViewerContainerSetScrollLeftKey
(
    IWidget                 *pWDGViewerContainer,
    MAE_Key_t               nScrollLeftKey
)
{
    WdgCommonSetProperty(pWDGViewerContainer, PROP_VIEWERCNTR_SCROLL_LEFT_KEY, (u32)nScrollLeftKey);
}

/** WdgViewerContainerSetScrollRightKey
* @brief        Set ViewerContainer the Key id to scroll right
*
* @param[in]    pWDGViewerContainer  The ViewerContainer widget which want to be set
* @param[in]    nScrollRightKey      The Key id to scroll right; Ex, MAE_KEY_1, MAE_KEY_LEFT...
*
* @retval       None
*
*/
__INLINE void WdgViewerContainerSetScrollRightKey
(
    IWidget                 *pWDGViewerContainer,
    MAE_Key_t               nScrollRightKey
)
{
    WdgCommonSetProperty(pWDGViewerContainer, PROP_VIEWERCNTR_SCROLL_RIGHT_KEY, (u32)nScrollRightKey);
}

/** WdgViewerContainerSetFocusWDGBorderColor
* @brief        Set ViewerContainer border color for focused widget
*
* @param[in]    pWDGViewerContainer     The ViewerContainer widget which want to be set
* @param[in]    nFocusWDGBorderColor    Border color for focused widget
*
* @retval       None
*
*/
__INLINE void WdgViewerContainerSetFocusWDGBorderColor
(
    IWidget                 *pWDGViewerContainer,
    RGBColor_t              nFocusWDGBorderColor
)
{
    WdgCommonSetProperty(pWDGViewerContainer, PROP_VIEWERCNTR_FOCUS_WDG_BORDER_COLOR, (u32)nFocusWDGBorderColor);
}

/** WdgViewerContainerSetScrollData
* @brief        Set ViewerContainer widget scroll data; it works only enable scrollbar
*
* @param[in]    pWDGViewerContainer  The ViewerContainer widget which want to be set
* @param[in]    pScrollData          The widget scroll data which will be set to the ViewerContainer widget
*
* @retval       MAE_RET_SUCCESS      Success
* @retval       others               Failed
*
*/
__INLINE MAE_Ret WdgViewerContainerSetScrollData
(
    IWidget                 *pWDGViewerContainer,
    ScrollData_t            *pScrollData
)
{
    return WdgCommonSetProperty(pWDGViewerContainer, PROP_WDG_SCROLL_DATA, (u32)pScrollData);
}
/*=============================================================*/

/** WdgViewerContainerGetObjWidget
* @brief        The function get the widget based on pRefWidget in container's widget stack
*
* @param[in]    pWDGViewerContainer    The pointer of ViewerContainer
* @param[in]    pRefWidget          A pointer of IWidget interface object to be reference
* @param[in]    isUpper             A boolean flag, TRUE to search the top of "pRefWidget";
*                                   FALSE to search to bottom of "pRefWidget".
* @param[in]    isWrap              A boolean flag;
*                                   TRUE : if "pRefWidget" is most top widget you can get most bottom when "isUpper" is TRUE.
*                                   if "pRefWidget" is most bottom widget you can get most top when "isUpper" is FALSE.
*
*                                   FALSE: if "pRefWidget" is most top widget you can't any widget when "isUpper" is TRUE.
*                                   if "pRefWidget" is most bottom widget you can't any widget when "isUpper" is FALSE.
*
* @retval       NULL.               If reference widget not found or stack empty.
* @retval       IWidget*            Get a widget according to the parameters condition.
*
*/
IWidget* WdgViewerContainerGetObjWidget
(
                IWidget                *pWDGViewerContainer,
                IWidget                *pRefWidget,
                boolean                isUpper,
                boolean                isWrap
);

/** WdgViewerContainerGetPosAndFocus
* @brief    To get the position and focus ability of the specific widget.
*
* @param[in]    pWDGViewerContainer   A pointer of ViewerContainer
* @param[in]    pWidget               A specific widget inside this viewer-container.
* @param[out]   pViewerDesc           A pointer of WViewerDesc_t data structure to retrieve the position
*                                     and focus ability information.
*
* @retval       MAE_RET_SUCCESS       Success.
* @retval       others                Failed.
*
*/
MAE_Ret WdgViewerContainerGetPosAndFocus
(
                IWidget           *pWDGViewerContainer,
                IWidget           *pWidget,
                WDGViewerDesc_t   *pViewerDesc
);
/*=============================================================*/
/** WdgViewerContainerGetMovingStep
* @brief        Get ViewerContainer moving step in pixels by touch on scroll
*
* @param[in]    pWDGViewerContainer  The ViewerContainer widget which want to be get
*
* @retval       MovingStep           every moving step in pixels by touch on scroll
*
*
*/
u16 WdgViewerContainerGetMovingStep
(
    IWidget                 *pWDGViewerContainer
);

/** WdgViewerContainerGetMoveNextFocusKey
* @brief        Get ViewerContainer the key id to move focus to next widget
*
* @param[in]    pWDGViewerContainer     The ViewerContainer widget which want to be got
* @param[out]   pNextFocusKey           The key id to move focus to next widget; Ex, MAE_KEY_1, MAE_KEY_LEFT...
*
* @retval       MAE_RET_SUCCESS         Success
* @retval       others                  Failed
*
*/
__INLINE MAE_Ret WdgViewerContainerGetMoveNextFocusKey
(
    IWidget                 *pWDGViewerContainer,
    MAE_Key_t               *pNextFocusKey
)
{
    return WdgCommonGetProperty(pWDGViewerContainer, PROP_VIEWERCNTR_MOVE_NEXT_FOCUS_KEY, (u32*)pNextFocusKey);
}

/** WdgViewerContainerGetMovePrevFocusKey
* @brief        Get ViewerContainer the key id to move focus to previous widget
*
* @param[in]     pWDGViewerContainer    The ViewerContainer widget which want to be get
* @param[out]    pPrevFocusKey          The key id to move focus to previous widget; Ex, MAE_KEY_1, MAE_KEY_LEFT...
*
* @retval       MAE_RET_SUCCESS         Success
* @retval       others                  Failed
*
*/
__INLINE MAE_Ret WdgViewerContainerGetMovePrevFocusKey
(
    IWidget            *pWDGViewerContainer,
    MAE_Key_t          *pPrevFocusKey
)
{
    return WdgCommonGetProperty(pWDGViewerContainer, PROP_VIEWERCNTR_MOVE_PREV_FOCUS_KEY, (u32*)pPrevFocusKey);
}

/** WdgViewerContainerGetScrollUpKey
* @brief        Get ViewerContainer the Key id to scroll up
*
* @param[in]     pWDGViewerContainer  The ViewerContainer widget which want to be get
* @param[out]    pScrollUpKey         The Key id to scroll up; Ex, MAE_KEY_1, MAE_KEY_LEFT...
*
* @retval       MAE_RET_SUCCESS       Success
* @retval       others                Failed
*
*/
__INLINE MAE_Ret WdgViewerContainerGetScrollUpKey
(
    IWidget            *pWDGViewerContainer,
    MAE_Key_t          *pScrollUpKey
)
{
    return WdgCommonGetProperty(pWDGViewerContainer, PROP_VIEWERCNTR_SCROLL_UP_KEY, (u32*)pScrollUpKey);
}

/** WdgViewerContainerGetScrollDownKey
* @brief        Get ViewerContainer the Key id to scroll down
*
* @param[in]    pWDGViewerContainer   The ViewerContainer widget which want to be get
* @param[out]   pScrollDownKey        The Key id to scroll down; Ex, MAE_KEY_1, MAE_KEY_LEFT...
*
* @retval       MAE_RET_SUCCESS       Success
* @retval       others                Failed
*
*/
__INLINE MAE_Ret WdgViewerContainerGetScrollDownKey
(
    IWidget                 *pWDGViewerContainer,
    MAE_Key_t               *pScrollDownKey
)
{
    return WdgCommonGetProperty(pWDGViewerContainer, PROP_VIEWERCNTR_SCROLL_DOWN_KEY, (u32*)pScrollDownKey);
}

/** WdgViewerContainerGetScrollLeftKey
* @brief        Get ViewerContainer the Key id to scroll left
*
* @param[in]    pWDGViewerContainer     The ViewerContainer widget which want to be get
* @param[out]   pScrollLeftKey          The Key id to scroll left; Ex, MAE_KEY_1, MAE_KEY_LEFT...
*
* @retval       MAE_RET_SUCCESS         Success
* @retval       others                  Failed
*
*/
__INLINE MAE_Ret WdgViewerContainerGetScrollLeftKey
(
    IWidget             *pWDGViewerContainer,
    MAE_Key_t           *pScrollLeftKey
)
{
    return WdgCommonGetProperty(pWDGViewerContainer, PROP_VIEWERCNTR_SCROLL_LEFT_KEY, (u32*)pScrollLeftKey);
}

/** WdgViewerContainerGetScrollRightKey
* @brief        Get ViewerContainer the Key id to scroll right
*
* @param[in]    pWDGViewerContainer     The ViewerContainer widget which want to be get
* @param[in]    pScrollRightKey         The Key id to scroll right; Ex, MAE_KEY_1, MAE_KEY_LEFT...
*
* @retval       MAE_RET_SUCCESS         Success
* @retval       others                  Failed
*
*/
__INLINE MAE_Ret WdgViewerContainerGetScrollRightKey
(
    IWidget             *pWDGViewerContainer,
    MAE_Key_t           *pScrollRightKey
)
{
    return WdgCommonGetProperty(pWDGViewerContainer, PROP_VIEWERCNTR_SCROLL_RIGHT_KEY, (u32*)pScrollRightKey);
}

/** WdgViewerContainerGetFocusWDGBorderColor
* @brief        Get ViewerContainer border color for focused widget
*
* @param[in]    pWDGViewerContainer     The ViewerContainer widget which want to be get
* @param[out]   pFocusWDGBorderColor    Border color for focused widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgViewerContainerGetFocusWDGBorderColor
(
    IWidget             *pWDGViewerContainer,
    RGBColor_t          *pFocusWDGBorderColor
)
{
    return WdgCommonGetProperty(pWDGViewerContainer, PROP_VIEWERCNTR_FOCUS_WDG_BORDER_COLOR, (u32*)pFocusWDGBorderColor);
}

/** WdgViewerContainerGetScrollData
* @brief        Get ViewerContainer widget scroll data; it works only enable scrollbar
*
* @param[in]    pWDGViewerContainer     The ViewerContainer widget which want to be get
* @param[out]   pScrollData             The widget scroll data which will be gotten to the ViewerContainer widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgViewerContainerGetScrollData
(
    IWidget                 *pWDGViewerContainer,
    ScrollData_t            *pScrollData
)
{
    return WdgCommonGetProperty(pWDGViewerContainer, PROP_WDG_SCROLL_DATA, (u32*)pScrollData);
}

/** WdgViewerContainerGetScrollStep
* @brief        Get ViewerContainer widget scroll step
*
* @param[in]    pWDGViewerContainer     The ViewerContainer widget which want to be get
* @param[out]   pScrollStep             The widget scroll step which will be get from the ViewerContainer widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgViewerContainerGetScrollStep
(
    IWidget                 *pWDGViewerContainer,
    ScrollStep_t            *pScrollStep
)
{
    return WdgCommonGetProperty(pWDGViewerContainer, PROP_WDG_SCROLL_STEP, (u32*)pScrollStep);
}

/**
* WdgViewerContainerGetObjFocusedWidget
* @brief    This function can get the focused widget object instance in ViewerContainer.
*
* @param    pWDGViewerContainer     The pointer of ViewerContainer.
*
* @retval   The Widget which is the focused widget in ViewerContainer.
*/
IWidget* WdgViewerContainerGetObjFocusedWidget
(
    IWidget                 *pWDGViewerContainer
);

/*=============================================================*/
/** WdgViewerContainerRegisterScrollChangeCb
* @brief        Register callback for handling scroll visible range change; CB will be triggered if scroll visible range changed
*
* @param[in]    pWDGViewerContainer    The ViewerContainer widget which want to set callback
* @param[in]    pfn                    callback function
* @param[in]    pUserData               User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS        Success
* @retval       others                 Failed
*
*/
MAE_Ret WdgViewerContainerRegisterScrollChangeCb
(
    IWidget                             *pWDGViewerContainer,
    PfnWdgViewerContainerScrollChange   pfn,
    void                                *pUserData
);

#ifndef _SMART_SCROLL_
/** WdgViewerContainerRegisterBoundTopNotifyCb
* @brief        Register callback : For list widget CB will be triggered when the focus move to the top item and can't wrap.
*
* @param[in]    pWDGViewerContainer The ViewerContainer widget which want to set callback
* @param[in]    pfn                 callback function
* @param[in]    pUserData            User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
MAE_Ret WdgViewerContainerRegisterBoundTopNotifyCb
(
    IWidget                         *pWDGViewerContainer,
    PfnWdgViewerContainerBoundTop   pfn,
    void                            *pUserData
);

/** WdgViewerContainerRegisterBoundBottomNotifyCb
* @brief        Register callback : For list widget, CB will be triggered when the focus move to the end item and can't wrap.
*
* @param[in]    pWDGViewerContainer  The ViewerContainer widget which want to set callback
* @param[in]    pfn                  callback function
* @param[in]    pUserData             User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS      Success
* @retval       others               Failed
*
*/
MAE_Ret WdgViewerContainerRegisterBoundBottomNotifyCb
(
    IWidget                             *pWDGViewerContainer,
    PfnWdgViewerContainerBoundBottom    pfn,
    void                                *pUserData
);
#endif

/** WdgViewerContainerDeregisterScrollChangeCb
* @brief        Deregister callback for handling scroll visible range change
*
* @param[in]    pWDGViewerContainer  The ViewerContainer widget which want to cancel callback
* @param[in]    pfn                  callback function
* @param[in]    pUserData             User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS      Success
* @retval       others               Failed
*
*/
MAE_Ret WdgViewerContainerDeregisterScrollChangeCb
(
    IWidget                             *pWDGViewerContainer,
    PfnWdgViewerContainerScrollChange   pfn,
    void                                *pUserData
);

#ifndef _SMART_SCROLL_
/** WdgViewerContainerDeregisterBoundTopNotifyCb
* @brief        Deregister PfnWdgViewerContainerBoundTop callback
*
* @param[in]    pWDGViewerContainer    The ViewerContainer widget which want to cancel callback
* @param[in]    pfn                    callback function
* @param[in]    pUserData               User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS        Success
* @retval       others                 Failed
*
*/
MAE_Ret WdgViewerContainerDeregisterBoundTopNotifyCb
(
    IWidget                         *pWDGViewerContainer,
    PfnWdgViewerContainerBoundTop   pfn,
    void                            *pUserData
);

/** WdgViewerContainerDeregisterBoundBottomNotifyCb
* @brief        Deregister PfnWdgViewerContainerBoundBottom callback
*
* @param[in]    pWDGViewerContainer    The ViewerContainer widget which want to cancel callback
* @param[in]    pfn                    callback function
* @param[in]    pUserData               User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS        Success
* @retval       others                 Failed
*
*/
MAE_Ret WdgViewerContainerDeregisterBoundBottomNotifyCb
(
    IWidget                             *pWDGViewerContainer,
    PfnWdgViewerContainerBoundBottom    pfn,
    void                                *pUserData
);
#endif

#endif /* __MMI_WDG_VIEWERCONTAINER_H__ */
/*=============================================================*/
// end of file
