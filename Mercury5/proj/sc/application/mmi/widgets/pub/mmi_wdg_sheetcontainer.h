/**
* @file    mmi_wdg_sheetcontainer.h
* @version $Id: mmi_wdg_sheetcontainer.h 14096 2008-09-16 02:25:50Z paul.ouyang $
* @brief   
*<Description>
*
*<Class ID>
*    CLSID_SHEETCONTAINER
*
*    If AP wants to add many widgets in the screen, but only show ONE widget
*    in a time, Sheet Container can achieve this goal. Widgets in Sheet Container likes
*    cards which are all stacked together, users simply see the top of the card. If you want
*    to replace the top of the card, it would take through the interface of Sheet Container
*    to change. The example is sketched below. Moreover, default display is the first of
*    the widget by adding the widget, its index is 0. Users can specify index or widget instance
*    to decide which one widget on the top. Each of the widget¡¦s size in Sheet Container will
*    be the same with Sheet Container.
*
*                   ex: Sheet Container widget
*                    +----------------------------------------+
*                    | +----------------------------------+    |
*                    | |                                  |-+  |
*                    | |       Widget    A                |  | |            Widget A is the top widget.
*                    | |                                  |  | |             Other widgets are covered by Widget A
*                    | |                                  |  | |
*                    | +----------------------------------+  | |
*                    |    |      Widget   B                  | |
*                    |    +----------------------------------+ |
*                    |                  Sheet Container        |
*                    +-----------------------------------------+
*
*/

#ifndef __MMI_WDG_SHEETCONTAINER_H__
#define __MMI_WDG_SHEETCONTAINER_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_container.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_window.h"
#include "mmi_mae_view_wrapper.h"
#include "mmi_wdg_sheetcontainer.h"
#include "mmi_wdg_common_interface.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/** WVisDesc_t
*
* @brief    isVisible:
*
*/
typedef struct {
	boolean isVisible;
} WVisDesc_t;

/** PfnWdgSheetContainerTabChange
* @brief      CB register by "WdgSheetContainerRegisterTabChangeCb"
*             and will be trigger when  tab changes.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pTabChangeData    The info of tab change, refer to TabChangeData_t
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgSheetContainerTabChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TabChangeData_t *pTabChangeData, IWidget *pWidget);

/*=============================================================*/
// Interface Functions
/*=============================================================*/
/** WdgSheetContainerCreateForWnd
* @brief        SheetContainer widget create function for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
*
* @retval       The pointer of SheetContainer pointer    Success.
* @retval       NULL                                     Failed.
*
*/
__SLDPM_FREE__ IWidget* WdgSheetContainerCreateForWnd
(
    HWIN         hWin,
    Pos_t               *pPos,
    WidgetSize_t        *pSize,
    u16                 nWidgetID
);
/*=============================================================*/
/** WdgSheetContainerCreate
* @brief        Create SheetContainer widget
*
* @retval       The pointer of SheetContainer pointer    Success.
* @retval       NULL                                     Failed.
*
*/
IWidget* WdgSheetContainerCreate
(
    void
);

/** WdgSheetContainerAdd
* @brief        The function add a widget in the SheetContainer
*
* @param[in]    pWDGSheetContainer      The pointer of SheetContainer
* @param[in]    pWidget                 A pointer of IWidget interface object to add
* @param[in]    pRefWidget              The reference widget. A pointer of IWidget interface object to be reference
* @param[in]    isUpper                 TRUE: add the widget to the above of the reference widget, FALSE: add the widget to the below of the reference widget
* @param[in]    pWPos                   The position of widget
*
* @retval       MAE_RET_SUCCESS         Success.
* @retval       MAE_RET_BAD_PARAM       Failed. pIWidget is NULL or pRefWidget not found.
* @retval       MAE_RET_OUT_OF_MEMORY   Failed. Memory is not enough.
*
*/
MAE_Ret WdgSheetContainerAdd
(
    IWidget                *pWDGSheetContainer,
    IWidget                *pWidget,
    IWidget                *pRefWidget,
    boolean                isUpper,
    WVisDesc_t             *pWPos
);

/** WdgSheetContainerAddToTopMost
* @brief        The function add a widget to top in the SheetContainer
*
* @param[in]    pWDGSheetContainer      The pointer of SheetContainer
* @param[in]    pWidget                 A pointer of IWidget interface object to add
* @param[in]    pWPos                   The position of widget
*
* @retval        MAE_RET_SUCCESS        Success.
* @retval        others                 Failed.
*
*/
MAE_Ret WdgSheetContainerAddToTopMost
(
    IWidget                *pWDGSheetContainer,
    IWidget                *pWidget,
    WVisDesc_t             *pWPos
);

/** WdgSheetContainerAddToBottomMost
* @brief    The function add a widget to bottom in the SheetContainer
*
* @param[in]    pWDGSheetContainer      The pointer of SheetContainer
* @param[in]    pWidget                 A pointer of IWidget interface object to add
* @param[in]    pWPos                   The position of widget
*
* @retval       MAE_RET_SUCCESS         Success.
* @retval       others                  Failed.
*
*/
MAE_Ret WdgSheetContainerAddToBottomMost
(
    IWidget                *pWDGSheetContainer,
    IWidget                *pWidget,
    WVisDesc_t             *pWPos
);

/** WdgSheetContainerDelete
* @brief        The function delete a widget from the SheetContainer
*
* @param[in]    pWDGSheetContainer      The pointer of SheetContainer
* @param[in]    pWidget                 A pointer of IWidget interface object to delete
*
* @retval       MAE_RET_SUCCESS         Success. Successfully to remove.
* @retval       MAE_RET_FAILED          Failed. pIWidget is NULL or not found.
*
*/
MAE_Ret WdgSheetContainerDelete
(
                IWidget                 *pWDGSheetContainer,
                IWidget                 *pWidget
);

/** WdgSheetContainerMove
* @brief        The function move the widget in container's widget stack
*
* @param[in]    pWDGSheetContainer      The pointer of SheetContainer
* @param[in]    pWidget                 A pointer of IWidget interface object to be moved
* @param[in]    pRefWidget              A pointer of IWidget interface object to be referred to
* @param[in]    isUpper                 A boolean, TRUE is moving the widget to the above of referred widget,
*                                                  FALSE is moving the widget to the below of referred widget
*
* @retval       MAE_RET_SUCCESS         Success.
* @retval       MAE_RET_BAD_PARAM       Failed. pIWidget is NULL, or pIWidget not found in widget stack,
*                                       or pRefWidget not found in widget stack.
*
*/
MAE_Ret WdgSheetContainerMove
(
                IWidget                 *pWDGSheetContainer,
                IWidget                 *pWidget,
                IWidget                 *pRefWidget,
                boolean                 isUpper
);

/**
* WdgSheetContainerActivatedByIndex
* @brief        To activate a specific widget via index.
*
* @param[in]    pWDGSheetContainer      The pointer of SheetContainer
* @param[in]    nIndex                  A zero-based index, which refers to a widget to activate
*
* @retval       MAE_RET_SUCCESS         Success. Activating is successful.
* @retval       MAE_RET_BAD_PARAM       Failed. nIndex is not correct.
* @retval       MAE_RET_FAILED          Failed. Other reason.
*/
MAE_Ret WdgSheetContainerActivatedByIndex
(
                IWidget                *pWDGSheetContainer,
                u32                    nIndex
);

/**
* WdgSheetContainerActivatedByWidget
* @brief    To activate a specific widget via widget pointer
*
* @param[in]    pWDGSheetContainer  The pointer of SheetContainer
* @param[in]    pWidget             A Iwidget object pointer be activated.
*
* @retval        MAE_RET_SUCCESS       Success. Activating is successful.
* @retval        MAE_RET_BAD_PARAM     Failed. pIWidget is NULL, or pIWidget not found in widget stack.
* @retval        MAE_RET_FAILED        Failed. Other reason.
*/
MAE_Ret WdgSheetContainerActivatedByWidget
(
                IWidget                *pWDGSheetContainer,
                IWidget                *pWidget
);
/*=============================================================*/
/** WdgSheetContainerSetEnableSlide
* @brief        To enable or disable sliding effect.
*
* @param[in]    pWDGSheetContainer    The pointer of SheetContainer
* @param[in]    bEnableSlide          Enable or Disable sliding effect
*
* @retval       None
*
*/
__INLINE void WdgSheetContainerSetEnableSlide
(
                IWidget             *pWDGSheetContainer,
                boolean             bEnableSlide
)
{
    WdgCommonSetProperty(pWDGSheetContainer, PROP_SHEETCNTR_ENABLE_SLIDE, bEnableSlide);
}

/** WdgSheetContainerSetSlideStep
* @brief        Set total steps of the sliding effect.
*
* @param[in]    pWDGSheetContainer    The pointer of SheetContainer
* @param[in]    nSlideStep            Total steps of the sliding effect.
*
* @retval       None
*
*/
__INLINE void WdgSheetContainerSetSlideStep
(
                IWidget             *pWDGSheetContainer,
                u32                 nSlideStep
)
{
    WdgCommonSetProperty(pWDGSheetContainer, PROP_SHEETCNTR_SLIDE_STEP, nSlideStep);
}
/*=============================================================*/

/** WdgSheetContainerGetObjWidget
* @brief        The function get the widget based on pRefWidget in container's widget stack
*
* @param[in]    pWDGSheetContainer    The pointer of SheetContainer
* @param[in]    pRefWidget          A pointer of IWidget interface object to be reference
* @param[in]    isUpper             A boolean flag, TRUE to search the top of "pRefWidget";
*                                                   FALSE to search to bottom of "pRefWidget".
* @param[in]    isWrap              A boolean flag;
*                                   TRUE : if "pRefWidget" is most top widget you can get most bottom when "isUpper" is TRUE.
*                                          if "pRefWidget" is most bottom widget you can get most top when "isUpper" is FALSE.
*
*                                   FALSE: if "pRefWidget" is most top widget you can't any widget when "isUpper" is TRUE.
*                                          if "pRefWidget" is most bottom widget you can't any widget when "isUpper" is FALSE.
*
* @retval       NULL.               If reference widget not found or stack empty.
* @retval       IWidget*            Get a widget according to the parameters condition.
*
*/

IWidget* WdgSheetContainerGetObjWidget
(
                IWidget                *pWDGSheetContainer,
                IWidget                *pRefWidget,
                boolean                isUpper,
                boolean                isWrap
);

/**
* WdgSheetContainerGetObjActiveWidget
* @brief        Get the active widget of the sheetcontainer.
*
* @param[in]    pWDGSheetContainer   The pointer of SheetContainer
*
* @retval        IWidget*, A pointer of IWidget object if successful
* @retval        NULL.
*/
IWidget* WdgSheetContainerGetObjActiveWidget
(
                IWidget                *pWDGSheetContainer
);


/*=============================================================*/
/** WdgSheetContainerRegisterTabChangeCb
* @brief        Register callback : For Tab widget, CB will be triggered when tab changes.
*
* @param[in]    pWDGSheetContainer  The SheetContainer widget which want to set callback
* @param[in]    pfn                 callback function
* @param[in]    pUserData            User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgSheetContainerRegisterTabChangeCb
(
    IWidget                         *pWDGSheetContainer,
    PfnWdgSheetContainerTabChange   pfn,
    void                            *pUserData
);

/** WdgSheetContainerDeregisterTabChangeCb
* @brief        Deregister PfnWdgSheetContainerTabChange callback
*
* @param[in]    pWDGSheetContainer  The SheetContainer widget which want to cancel callback
* @param[in]    pfn                 callback function
* @param[in]    pUserData            User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgSheetContainerDeregisterTabChangeCb
(
    IWidget                         *pWDGSheetContainer,
    PfnWdgSheetContainerTabChange   pfn,
    void                            *pUserData
);
#endif /* __MMI_WDG_SHEETCONTAINER_H__ */
/*=============================================================*/
// end of file
