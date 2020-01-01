/**
* @file    mmi_wdg_mflcontainer.h
* @version $Id: mmi_wdg_mflcontainer.h 14096 2008-09-16 02:25:50Z paul.ouyang $
*
*     Multi-Fields List (MFL) Container is a kind of container, which application can add one
*     or more widgets into MFL-container. MFL-container will show the child widgets as a
*     list, graphs as below.The default highlight item is the first item(with index zero).
*     MFL-container will handle up/down key events to move the highlight item. Every item's
*     width is the same with MFL-container's width. The height of highlight/unhighlight item
*     depend on the property value PROP_SEL_ITEMSIZE/PROP_ITEM_HEIGHT. The
*     default value of item height is default one line height(MAIN_LCD_ONELINE_HEIGHT).
*     Application can change the height value via IWIDGET_SetProperty() with property id
*     PROP_ITEM_HEIGHT/PROP_SEL_ITEMSIZE. If Application does not set the highlight
*     item height or set it to zero, the height of highlight item will equal to the height of unhighlight
*     item.
*
*       ex: Multi-Fields List (MFL) Container
*        +------------------+
*        |    Widget 1      |
*        |------------------|
*        |    Widget 2      |
*        |------------------|
*        |    Widget 3      |
*        |------------------|
*        |    Widget 4      |
*        +------------------+
*
*/
#ifndef __MMI_WDG_MFLCONTAINER_H__
#define __MMI_WDG_MFLCONTAINER_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_window.h"
#include "mmi_mae_container.h"
#include "mmi_wdg_common_interface.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/** WMflDesc_t
*
* @brief    This structure is used when a widget add into MFL-container.
*           isVisible:               
*           id:
*
*/
typedef struct {
	boolean isVisible;
	u16     id;
} WMflDesc_t;

/** PfnWdgMflContainerMFLFocusChange
* @brief      CB register by "WdgMflContainerRegisterMFLFocusChangeCb"
*             and will be trigger when the focus of widget is changed
*
* @param[in]  pApplet         The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData        User data ap developer setting when register CB.
* @param[in]  nEvtCode        Widget Event Code, only useful for softkey event
* @param[in]  pMFLFocusData   The info can get when focus changed, refer to MFLFocusData_t
* @param[in]  pIWidget        The widget instance
*
*/
typedef void (*PfnWdgMflContainerMFLFocusChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, MFLFocusData_t *pMFLFocusData, IWidget *pWidget);

/** PfnWdgMflContainerMFLFocusSelect
* @brief      CB register by "WdgMflContainerRegisterMFLFocusSelectCb"
*             and will be trigger when MFL item selected
*
* @param[in]  pApplet         The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData        User data ap developer setting when register CB.
* @param[in]  nEvtCode        Widget Event Code, only useful for softkey event
* @param[in]  pMFLFocusData   The info can get when focus selected, refer to MFLFocusData_t
* @param[in]  pIWidget        The widget instance
*
*/
typedef void (*PfnWdgMflContainerMFLFocusSelect) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, MFLFocusData_t *pMFLFocusData, IWidget *pWidget);

/** PfnWdgMflContainerScrollChange
* @brief      CB register by "WdgMflContainerRegisterScrollChangeCb"
*             and will be trigger when scroll visible range changed
*
* @param[in]  pApplet         The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData        User data ap developer setting when register CB.
* @param[in]  nEvtCode        Widget Event Code, only useful for softkey event
* @param[in]  pScrollData     The info can get when scroll changed, refer to ScrollData_t
* @param[in]  pIWidget        The widget instancez
*
*/
typedef void (*PfnWdgMflContainerScrollChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, ScrollData_t *pScrollData, IWidget *pWidget);

/** PfnWdgMflContainerScrollStepChange
* @brief      CB register by "WdgMflContainerRegisterScrollStepChangeCb"
*             and will be trigger when scroll step changed
*
* @param[in]  pApplet        The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData       User data ap developer setting when register CB.
* @param[in]  nEvtCode       Widget Event Code, only useful for softkey event
* @param[in]  pScrollStep    The info can get when scroll step changed, refer to ScrollStep_t
* @param[in]  pIWidget       The widget instance
*
*/
typedef void (*PfnWdgMflContainerScrollStepChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, ScrollStep_t *pScrollStep, IWidget *pWidget);

/*=============================================================*/
// Interface functions
/*=============================================================*/
/** WdgMflContainerCreateForWnd
* @brief        MflContainer widget Common create function
*
* @param[in]    hWin        The window handle
* @param[in]    pPos           A pointer of widget position; can't be NULL.
* @param[in]    pSize          A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID      The widget unique ID of window
* @param[in]    nItemHeight    Each height (in pixel) of items in container
*
* @retval       The pointer of Image         Success.
* @retval       NULL                         Failed.
*
*/
IWidget* WdgMflContainerCreateForWnd
(
    HWIN     hWin,
    Pos_t           *pPos,
    WidgetSize_t    *pSize,
    u16             nWidgetID,
    u16             nItemHeight
);
/*=============================================================*/
/** WdgMflContainerCreate
* @brief        Create MflContainer widget
*
* @retval       The pointer of MflContainer     Success.
* @retval       NULL                            Failed.
*
*/
IWidget* WdgMflContainerCreate
(
    void
);
/*=============================================================*/
/** WdgMflContainerAdd
* @brief        The function add a widget in the MflContainer
*
* @param[in]    pWDGMflContainer    The pointer of MflContainer
* @param[in]    pWidget             A pointer of IWidget interface object to add
* @param[in]    pRefWidget          The reference widget. A pointer of IWidget interface object to be reference
* @param[in]    isUpper             TRUE: add the widget to the above of the reference widget,
*                                   FALSE: add the widget to the below of the reference widget
* @param[in]    pWPos               The position of widget
*
* @retval       MAE_RET_SUCCESS         Success.
* @retval       MAE_RET_BAD_PARAM       Failed. pIWidget is NULL or pRefWidget not found.
* @retval       MAE_RET_OUT_OF_MEMORY   Failed. Memory is not enough.
*
*/
MAE_Ret WdgMflContainerAdd
(
    IWidget             *pWDGMflContainer,
    IWidget             *pWidget,
    IWidget             *pRefWidget,
    boolean             isUpper,
    WMflDesc_t          *pWPos
);

/** WdgMflContainerDelete
* @brief        The function delete a widget from the MflContainer
*
* @param[in]    pWDGMflContainer    The pointer of MflContainer
* @param[in]    pWidget             A pointer of IWidget interface object to delete
*
* @retval          MAE_RET_SUCCESS  Success. Successfully to remove.
* @retval          MAE_RET_FAILED   Failed. pIWidget is NULL or not found.
*
*/
MAE_Ret WdgMflContainerDelete
(
                IWidget                *pWDGMflContainer,
                IWidget                *pWidget
);

/** WdgMflContainerMove
* @brief        The function move the widget in container's widget stack
*
* @param[in]    pWDGMflContainer    The pointer of MflContainer
* @param[in]    pWidget             A pointer of IWidget interface object to be moved
* @param[in]    pRefWidget          A pointer of IWidget interface object to be referred to
* @param[in]    isUpper             A boolean, TRUE is moving the widget to the above of referred widget,
*                                   FALSE is moving the widget to the below of referred widget
*
* @retval        MAE_RET_SUCCESS    Success.
* @retval        MAE_RET_BAD_PARAM  Failed. pIWidget is NULL, or pIWidget not found in widget stack, or pRefWidget not found in widget stack.
*
*/
MAE_Ret WdgMflContainerMove
(
                IWidget                *pWDGMflContainer,
                IWidget                *pWidget,
                IWidget                *pRefWidget,
                boolean                isUpper
);

/** WdgMflContainerAddToTopMost
* @brief        The function add a widget to top of the MflContainer
*
* @param[in]    pWDGMflContainer    The pointer of MflContainer
* @param[in]    pWidget             A pointer of IWidget interface object to add
* @param[in]    pWPos               The position of widget
*
* @retval        MAE_RET_SUCCESS      Success.
* @retval        others               Failed.
*
*/
MAE_Ret WdgMflContainerAddToTopMost
(
    IWidget             *pWDGMflContainer,
    IWidget             *pWidget,
    WMflDesc_t          *pWPos
);

/** WdgMflContainerAddToBottomMost
* @brief    The function add a widget to bottom of the MflContainer
*
* @param[in]    pWDGMflContainer    The pointer of MflContainer
* @param[in]    pWidget             A pointer of IWidget interface object to add
* @param[in]    pWPos               The position of widget
*
* @retval        MAE_RET_SUCCESS      Success.
* @retval        others               Failed.
*
*/
MAE_Ret WdgMflContainerAddToBottomMost
(
    IWidget             *pWDGMflContainer,
    IWidget             *pWidget,
    WMflDesc_t          *pWPos
);

/** WdgMflContainerMoveFocusToWidget
* @brief    This function can move the focus to a specific widget in MflContainer.
*         If the specific widget(pChildWdg) is not in MflContainer, it will return MAE_RET_FAILED.
*
* @param[in]    pWDGMflContainer    The pointer of MflContainer.
* @param[in]    pChildWdg           A new focused widget we want of MflContainer.
*
* @retval      void
*/
void  WdgMflContainerMoveFocusToWidget
(
    IWidget                 *pWDGMflContainer,
    IWidget                 *pChildWdg
);

/** WdgMflContainerMoveFocusToWidget
* @brief    This function can move the focus to the top widget in MflContainer's stack.
*
* @param[in]    pWDGMflContainer    The pointer of MflContainer.
*
* @return      void
*/
void WdgMflContainerMoveFocusToTopWidget
(
    IWidget                 *pWDGMflContainer
);

/** WdgMflContainerMoveFocusToBottomWidget
* @brief    This function can move the focus to the bottom widget in MflContainer's stack.
*
* @param[in]    pWDGMflContainer    The pointer of MflContainer.
*
* @retval      void
*/
void WdgMflContainerMoveFocusToBottomWidget
(
    IWidget                 *pWDGMflContainer
);

/** WdgMflContainerMoveFocusToNextWidget
* @brief    This function can move the focus to the next widget of the focused widget.
*
* @param[in]    pWDGMflContainer    The pointer of MflContainer.
*
* @retval       void
*/
void WdgMflContainerMoveFocusToNextWidget
(
    IWidget                 *pWDGMflContainer
);

/** WdgMflContainerMoveFocusToPrevWidget
* @brief    This function can move the focus to the previous widget of the focused widget.
*
* @param[in]    pWDGMflContainer    The pointer of MflContainer.
*
* @retval       void
*/
void WdgMflContainerMoveFocusToPrevWidget
(
    IWidget                 *pWDGMflContainer
);
/*=============================================================*/
#ifdef __TOUCH_SCREEN_MMI__
/** WdgMflContainerSetEnableTouchSliding
* @brief        Set MflContainer be enable touch sliding
*
* @param[in]    pWDGMflContainer  The MflContainer widget which want to be set
* @param[in]    bEnable       TRUE/FALSE
*
* @retval       void
*
*/
__INLINE void WdgMflContainerSetEnableTouchSliding
(
    IWidget              *pWDGMflContainer,
    boolean                  bEnable
)
{
    WdgCommonSetProperty(pWDGMflContainer, PROP_MFL_ENABLE_TOUCH_SLIDE, (u32)bEnable);
}
#endif

/** WdgMflContainerSetFocusIndex
* @brief        Set MflContainer Highlighted item by index
*
* @param[in]    pWDGMflContainer  The MflContainer widget which want to be set
* @param[in]    nFocusIndex       The Focus Index
*
* @retval       void
*
*/
__INLINE void WdgMflContainerSetFocusIndex
(
    IWidget              *pWDGMflContainer,
    s32                  nFocusIndex
)
{
    WdgCommonSetProperty(pWDGMflContainer, PROP_FOCUS_INDEX, (u32)nFocusIndex);
}

/** WdgMflContainerSetItemHeight
* @brief        Set MflContainer height of each item
*
* @param[in]    pWDGMflContainer  The MflContainer widget which want to be set
* @param[in]    nItemHeight       Each height (in pixel) of items in container
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgMflContainerSetItemHeight
(
    IWidget              *pWDGMflContainer,
    u16                  nItemHeight
)
{
    return WdgCommonSetProperty(pWDGMflContainer, PROP_ITEM_HEIGHT, (u32)nItemHeight);
}

/** WdgMflContainerSetFocusItemHeight
* @brief        If you want the height of highlight item differs with other items;
*               you can set attribute value.
*
* @param[in]    pWDGMflContainer  The MflContainer widget which want to be set
* @param[in]    nItemHeight    The height of highlighted item
*
* @return       void
*
*/
__INLINE void WdgMflContainerSetFocusItemHeight
(
    IWidget               *pWDGMflContainer,
    u16                   nItemHeight
)
{
    WdgCommonSetProperty(pWDGMflContainer, PROP_SEL_ITEMSIZE, (u32)nItemHeight);
}

/** WdgMflContainerSetFCSItemBGColor
* @brief        Set MflContainer the background color of highlighted item
*
* @param[in]    pWDGMflContainer  The MflContainer widget which want to be set
* @param[in]    tFCSItemBGColor   The background color of highlighted item
*
* @retval       void
*
*/
__INLINE void WdgMflContainerSetFCSItemBGColor
(
    IWidget             *pWDGMflContainer,
    RGBColor_t          tFCSItemBGColor
)
{
    WdgCommonSetProperty(pWDGMflContainer, PROP_FCS_ITEM_BG_COLOR, (u32)tFCSItemBGColor);
}

/** WdgMflContainerSetFCSItemBGImage
* @brief        Set MflContainer the background picture of highlighted item
*
* @param[in]    pWDGMflContainer  The MflContainer widget which want to be set
* @param[in]    pFCSItemBGImage   The background picture of highlighted item
*
* @retval      void
*
*/
__INLINE void WdgMflContainerSetFCSItemBGImage
(
    IWidget                 *pWDGMflContainer,
    IImage                  *pFCSItemBGImage
)
{
    WdgCommonSetProperty(pWDGMflContainer, PROP_FCS_ITEM_BG_IMAGE, (u32)pFCSItemBGImage);
}

/** WdgMflContainerSetChildWDGRowGap
* @brief        Set the gap (in pixel) is between items.
*
* @param[in]    pWDGMflContainer  The MflContainer widget which want to be set
* @param[in]    nRowGap           The widget row gap
*
* @retval       void
*
*/
__INLINE void WdgMflContainerSetChildWDGRowGap
(
    IWidget                 *pWDGMflContainer,
    u16                     nRowGap
)
{
    WdgCommonSetProperty(pWDGMflContainer, PROP_WDG_ROW_GAP, (u32)nRowGap);
}

/** WdgMflContainerSetScrollData
* @brief        Set MflContainer widget scroll data; it works only enable scrollbar
*
* @param[in]    pWDGMflContainer  The MflContainer widget which want to be set
* @param[in]    pScrollData       The widget scroll data; refer to ScrollData_t
*
* @retval       void
*
*/
__INLINE void WdgMflContainerSetScrollData
(
    IWidget                *pWDGMflContainer,
    ScrollData_t           *pScrollData
)
{
    WdgCommonSetProperty(pWDGMflContainer, PROP_WDG_SCROLL_DATA, (u32)pScrollData);
}
/*=============================================================*/

/** WdgMflContainerGetObjWidget
* @brief        The function get the widget based on pRefWidget in container's widget stack
*
* @param[in]    pWDGMflContainer    The pointer of MflContainer
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
IWidget* WdgMflContainerGetObjWidget
(
                IWidget                *pWDGMflContainer,
                IWidget                *pRefWidget,
                boolean                isUpper,
                boolean                isWrap
);

/** WdgMflContainerGetObjWidgetByIndex
* @brief        Get Widget By Index from MflContainer
*
* @param[in]    pWDGMflContainer    The pointer of MflContainer
* @param[in]    nIndex              A zero-base index as reference to get a specific widget from this container
*
* @retval    Return an IWidget object pointer(IWidget*) if successfully. Otherwise, return NULL.
*
*/
IWidget* WdgMflContainerGetObjWidgetByIndex
(
                IWidget          *pWDGMflContainer,
                u32              nIndex
);

/** WdgMflContainerGetObjWidgetIdByIndex
* @brief        Get Widget ID By Index from MflContainer
*
* @param[in]    pWDGMflContainer    The pointer of MflContainer
* @param[in]    nIndex              A zero-base index as reference to get a specific widget from this container
* @param[out]   pId                 A pointer to a u32 variable to get the widget id
*
* @retval    Return MAE_RET_SUCCESS if successfully. Otherwise, return MAE_RET_FAILED.
*
*/
MAE_Ret WdgMflContainerGetObjWidgetIdByIndex
(
 IWidget          *pWDGMflContainer,
 u32              nIndex,
 u32              *pId
 );

/** WdgMflContainerGetFocusIndex
* @brief        Get MflContainer Focus(Highlighted) item index
*
* @param[in]    pWDGMflContainer  The MflContainer widget which want to be get

* @retval       u16               Index of Focus(Highlighted) item
*
*/
u32 WdgMflContainerGetFocusIndex
(
    IWidget                 *pWDGMflContainer
);

/** WdgMflContainerGetItemHeight
* @brief        Get MflContainer height of item
*
* @param[in]    pWDGMflContainer  The MflContainer widget which want to be get
*
* @retval      u16                Each height (in pixel) of items in container
*
*/
u16 WdgMflContainerGetItemHeight
(
    IWidget                 *pWDGMflContainer
);

/** WdgMflContainerGetFocusItemHeight
* @brief        Get MflContainer the height of highlighted item
*
* @param[in]    pWDGMflContainer  The MflContainer widget which want to be get
*
* @retval       u16               The height of highlighted item
*
*/
u16 WdgMflContainerGetFocusItemHeight
(
    IWidget                 *pWDGMflContainer
);

/** WdgMflContainerGetScrollData
* @brief        Get MflContainer widget scroll data; it works only enable scrollbar
*
* @param[in]    pWDGMflContainer  The MflContainer widget which want to be get
* @param[out]   pScrollData       The widget scroll data
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgMflContainerGetScrollData
(
    IWidget                 *pWDGMflContainer,
    ScrollData_t            *pScrollData
)
{
    return WdgCommonGetProperty(pWDGMflContainer, PROP_WDG_SCROLL_DATA, (u32*)pScrollData);
}

/**
* WdgMflContainerGetObjFocusedWidget
* @brief    This function can get the focused widget object instance in MflContainer.
*
* @param    pWDGMflContainer      The pointer of MflContainer.
*
* @retval   The widget which is the focused widget in MflContainer.
*/
IWidget* WdgMflContainerGetObjFocusedWidget
(
    IWidget               *pWDGMflContainer
);
/*=============================================================*/
/** WdgMflContainerRegisterMFLFocusChangeCb
* @brief        Register callback for MFL change the focus item; CB will be triggered if focus changed
*
* @param[in]    pWDGMflContainer The MflContainer widget which want to set callback
* @param[in]    pfn              callback function
* @param[in]    pUserData         User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMflContainerRegisterMFLFocusChangeCb
(
    IWidget                             *pWDGMflContainer,
    PfnWdgMflContainerMFLFocusChange    pfn,
    void                                *pUserData
);

/** WdgMflContainerRegisterMFLFocusSelectCb
* @brief        Register callback for MFL select item; CB will be triggered if MFL item selected
*
* @param[in]    pWDGMflContainer  The MflContainer widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMflContainerRegisterMFLFocusSelectCb
(
    IWidget                             *pWDGMflContainer,
    PfnWdgMflContainerMFLFocusSelect    pfn,
    void                                *pUserData
);

/** WdgMflContainerRegisterScrollChangeCb
* @brief        Register callback for handling scroll visible range change;
*               CB will be triggered if scroll visible range changed
*
* @param[in]    pWDGMflContainer  The MflContainer widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMflContainerRegisterScrollChangeCb
(
    IWidget                         *pWDGMflContainer,
    PfnWdgMflContainerScrollChange  pfn,
    void                            *pUserData
);

/** WdgMflContainerRegisterScrollStepChangeCb
* @brief        Register callback for handling the scroll step change;
*               CB will be triggered if scroll step changed
*
* @param[in]    pWDGMflContainer  The MflContainer widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMflContainerRegisterScrollStepChangeCb
(
    IWidget                             *pWDGMflContainer,
    PfnWdgMflContainerScrollStepChange  pfn,
    void                                *pUserData
);

/** WdgMflContainerDeregisterMFLFocusChangeCb
* @brief        Deregister callback for MFL change the focus item
*
* @param[in]    pWDGMflContainer  The MflContainer widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMflContainerDeregisterMFLFocusChangeCb
(
    IWidget                             *pWDGMflContainer,
    PfnWdgMflContainerMFLFocusChange    pfn,
    void                                *pUserData
);

/** WdgMflContainerDeregisterMFLFocusSelectCb
* @brief        Deregister callback for MFL select item
*
* @param[in]    pWDGMflContainer  The MflContainer widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMflContainerDeregisterMFLFocusSelectCb
(
    IWidget                             *pWDGMflContainer,
    PfnWdgMflContainerMFLFocusSelect    pfn,
    void                                *pUserData
);

/** WdgMflContainerDeregisterScrollChangeCb
* @brief        Deregister callback for handling scroll visible range change
*
* @param[in]    pWDGMflContainer  The MflContainer widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMflContainerDeregisterScrollChangeCb
(
    IWidget                         *pWDGMflContainer,
    PfnWdgMflContainerScrollChange  pfn,
    void                            *pUserData
);

/** WdgMflContainerDeregisterScrollStepChangeCb
* @brief        Deregister callback for handling the scroll step change
*
* @param[in]    pWDGMflContainer  The MflContainer widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMflContainerDeregisterScrollStepChangeCb
(
    IWidget                             *pWDGMflContainer,
    PfnWdgMflContainerScrollStepChange  pfn,
    void                                *pUserData
);

#endif /* __MMI_WDG_MFLCONTAINER_H__ */
/*=============================================================*/
// end of file
