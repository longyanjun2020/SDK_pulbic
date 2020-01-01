/**
 * @file    mmi_wdg_commonpickitem.h
 * @version $Id: mmi_wdg_commonpickitem.h 32671 2009-06-05 07:20:21Z otto.wu $
 * @brief   This file defines the interface of ICOMMONPICKITEMWIDGET
 *
 * Support class id:1.CLSID_TEXTPICK_TEXTWIDGET,
 *					2.CLSID_TEXTPICK_IMAGETEXTWIDGET,
 *					3.CLSID_IMAGETEXTPICK_IMAGETEXTWIDGET,
 *					4.CLSID_LINE2INFOPICK_TEXTWIDGET,
 * @layout
 *  ------------------------------------------
 *  | -------------------------------------- |
 *  | | Text                               | |
 *  | -------------------------------------- |
 *  | | <- | Pick    Item             | -> | |
 *  | -------------------------------------- |
 *  ------------------------------------------
 *  ------------------------------------------
 *  | -------------------------------------- |
 *  | | Image | Text                       | |
 *  | -------------------------------------- |
 *  | | <- | Pick    Item             | -> | |
 *  | -------------------------------------- |
 *  ------------------------------------------
 *  CLSID_LINE2INFOPICK_TEXTWIDGET
 *  ------------------------------------------
 *  | -------------------------------------- |
 *  | | Text                               | |
 *  | -------------------------------------- |
 *  | |Space| Pick  (ThmTextWdg)        |  | |
 *  | -------------------------------------- |
 *  ------------------------------------------
 *  This style will not show left and right pick to switch item, but
 *  if user enable PROP_PICKWDG_DIRECT_TOGGLE property of its pickwidget.
 *  User will be able to toggle value by using action key.
 **/
#ifndef __MMI_WDG_COMMONPICKITEM_H__
#define __MMI_WDG_COMMONPICKITEM_H__
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_window.h"
#include "mmi_mae_view_wrapper.h"
#include "mmi_wdg_common_interface.h"
#include "mmi_wdg_image_text_image.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/** CommonPickItemInfo
*
* @brief    pTopItemWidget_Ptr      ImageText at Top
*           nFocusIndex             Focused Index of pick widget
*           nTotalSize              Total number of Item Widget
*           pItemWidget_Ptr         Array of Void Pointers to Item Widget Info Pointer
*
*/
typedef struct {
   void	*pTopItemWidget_Ptr;
   u32	nFocusIndex;
   u32	nTotalSize;
   void	*pItemWidget_Ptr;
} CommonPickItemInfo;
typedef CommonPickItemInfo CommonPickItemInfo_st;

/** SingleTextInfo
*
* @brief    pText_Ptr        pointer to a text pointer
*
*/
typedef struct {
   MAE_WChar *pText_Ptr[1];      // Due to target compiler compatibility issue, we cannot define this as *pText_Ptr[]
} SingleTextInfo;                // If we change the definition to MAE_WChar **pText_Ptr, most of the existing code does not work anymore
                                 // Therefore, we first define a 1 element array of pointer and then if we need to
                                 // create this model item with source code, one will need to allocate extra memory at the
                                 // back of this structure with extra (n-1) MAE_WChar* . Please refer to mmi_settingapp_util.c
                                 // _SETTINGAPP_AllocateTextPickItemInfo for an example.

/** PickPaddingSize
*
* @brief    nLeft
*           nRight
*           nTop
*           nBottom
*
*/
typedef struct {
    u32 nLeft;
    u32 nRight;
    u32 nTop;
    u32 nBottom;
} PickPaddingSize;
typedef PickPaddingSize PickPaddingSize_st;

typedef enum
{
    COMMONPICK_STYLE_TEXTPICK_TEXTWIDGET,
    COMMONPICK_STYLE_TEXTPICK_IMAGETEXTWIDGET,
    COMMONPICK_STYLE_IMAGETEXTPICK_IMAGETEXTWIDGET,
    COMMONPICK_STYLE_LINE2INFOPICK_TEXTWIDGET
} CommonPickStyle_e;

/** WdgCommonPickInfo_t
*
* @brief    nImageID        Prev-Image ID.
*           nStrID          Post-Text ID.
*
*/
typedef struct {
   u32  nImageID;           // pre image
   u32  nStrID;             // text
}WdgCommonPickInfo_t;

/** PfnWdgCommonPickFocusChange
* @brief      CB register by "WdgCommonPickRegisterFocusChangeCb"
*             and will be trigger when the Focus of widget is changed; Ex,click arrows or press "Action Key"
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pFocusChangeData  The info of focus change, refer to FocusChangeData_t
* @param[in]  pReserve          The widget instance reserved for future (Please do NOT use now)
*
*/
typedef void (*PfnWdgCommonPickFocusChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusChangeData_t *pFocusChangeData, IWidget *pReserve);

/** PfnWdgCommonPickFocusSelect
* @brief      CB register by "WdgCommonPickRegisterFocusSelectCb"
*             and will be trigger when the Focus of widget is changed; Ex,click arrows or press "Action Key"
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nFocusIndex       The nth focus Index
* @param[in]  pReserve          The widget instance reserved for future (Please do NOT use now)
*
*/
typedef void (*PfnWdgCommonPickFocusSelect) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nFocusIndex, IWidget *pReserve);
/*=============================================================*/
// Interface functions
/*=============================================================*/
/** WdgCommonPickCreateForWnd
* @brief        CommonPick widget create function for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
* @param[in]    ePick_style         Pick widget style
*
* @retval       The pointer of CommonPick           Success.
* @retval       NULL                                Failed.
*
*/
IWidget* WdgCommonPickCreateForWnd
(
    HWIN         hWin,
    Pos_t               *pPos,
    WidgetSize_t        *pSize,
    u16                 nWidgetID,
    CommonPickStyle_e   ePick_style
);

/*=============================================================*/
/**  WdgCommonPickCreate
* @brief        Create CommonPick widget
*
* @param[in]    ePick_style                 Pick widget style
*
* @retval       The pointer of CommonPick   Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgCommonPickCreate
(
    CommonPickStyle_e       ePick_style
);

/** WdgCommonPickSetData
* @brief        Set display data.
*               Specific data for CommonPick widget.
*
* @param[in]    pWDGCommonPick    The CommonPick widget which want to be set
* @param[in]    nFocusIndex       Default Focused Index of pick widget
* @param[in]    nTotalSize        Total number of Item Widget
* @param[in]    pTitleData    Title Display data of CommonPick Widget, refer to ImageTextInfo_st.
* @param[in]    pPickData     Pick Display data of CommonPick Widget, refer to ImageTextInfo_st.
* @param[in]    pfFree            Free CB function for free data allocate by User while widget destroy.

* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgCommonPickSetData
(
    IWidget                   *pWDGCommonPick,
    u32                       nFocusIndex,
    u32                       nTotalSize,
    ImageTextInfo_st          *pTitleData,
    ImageTextInfo_st          *pPickData,
    PfnDataFree               pfFree
);


/** WdgCommonPickSetDataByID
* @brief        Set display data by resource ID.
*               Specific data for CommonPick widget.
*
* @param[in]    pWDGCommonPick    The CommonPick widget which want to be set
* @param[in]    nFocusIndex       Default Focused Index of pick widget
* @param[in]    nTotalSize        Total number of Item Widget
* @param[in]    pTitleDispData    Title Display data of CommonPick Widget, refer to WdgCommonPickInfo_t.
* @param[in]    pPickDispData     Pick Display data of CommonPick Widget, refer to WdgCommonPickInfo_t.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgCommonPickSetDataByID
(
    IWidget                 *pWDGCommonPick,
    u32                        nFocusIndex,
    u32                        nTotalSize,
    WdgCommonPickInfo_t     *pTitleDispData,
    WdgCommonPickInfo_t     *pPickDispData
);

/** WdgCommonPickSetFocusIndex
* @brief        Set CommonPick widget focus index
*
* @param[in]    pWDGCommonPick    The CommonPick widget which want to be set
* @param[in]    nIndex            The Focus index of CommonPick widget
*
* @retval       none
*
*/
__INLINE void WdgCommonPickSetFocusIndex
(
    IWidget                 *pWDGCommonPick,
    u32                     nIndex
)
{
    WdgCommonSetProperty(pWDGCommonPick, PROP_FOCUS_INDEX, (u32)nIndex);
}

/** WdgCommonPickSetHighLighted
* @brief        Set enable/disable highlight of CommonPick widget
*
* @param[in]    pWDGCommonPick      The CommonPick widget which want to be set
* @param[in]    bEnable             Enable/Disable highlight of CommonPick widget
*
* @retval       none
*
*/
__INLINE void WdgCommonPickSetHighLighted
(
    IWidget                 *pWDGCommonPick,
    boolean                 bEnable
)
{
    WdgCommonSetProperty(pWDGCommonPick, PROP_WDG_HIGHLIGHTED, (u32)bEnable);
}

/** WdgCommonPickSetTextOutlineColor
* @brief        Set text color of outline in CommonPick widget
*
* @param[in]    pWDGCommonPick      The CommonPick widget which want to be set
* @param[in]    nColor              the color of CommonPick widget
*
* @retval       none
*
*/
__INLINE void WdgCommonPickSetTextOutlineColor
(
    IWidget                 *pWDGCommonPick,
    RGBColor_t              nColor
)
{
    WdgCommonSetProperty(pWDGCommonPick, PROP_WDG_TEXT_OUTLINE_COLOR, (u32)nColor);
}

/** WdgCommonPickSetHighLightTextOutlineColor
* @brief        Set highlight text color of outline in CommonPick widget
*
* @param[in]    pWDGCommonPick      The CommonPick widget which want to be set
* @param[in]    nColor              Highlight text outline color
*
* @retval       none
*
*/
__INLINE void WdgCommonPickSetHighLightTextOutlineColor
(
    IWidget                 *pWDGCommonPick,
    RGBColor_t              nColor
)
{
    WdgCommonSetProperty(pWDGCommonPick, PROP_WDG_HIGHLIGHT_TEXT_OUTLINE_COLOR, (u32)nColor);
}

/** WdgCommonPickSetDirectToogle
* @brief        Set CommonPick Widget DirectToogle status
*
* @param[in]    pWDGCommonPick      The CommonPick widget which want to be set
* @param[in]    bDirectToogle       TRUE: When receive Action key it will toggle pick item directly,
*                                   FALSE: Do Not direct toggle pick item.
*
* @retval       none
*
*/
__INLINE void WdgCommonPickSetDirectToogle
(
    IWidget             *pWDGCommonPick,
    boolean             bDirectToogle

)
{
    WdgCommonSetProperty(pWDGCommonPick, PROP_PICKWDG_DIRECT_TOGGLE, (u32)bDirectToogle);
}

/** WdgCommonPickSetTextColor
* @brief        Set text color of widget.
*
* @param[in]    pWDGCommonPick        The CommonPick widget which want to be set
* @param[in]    TextColor            RGBColor_t value. User can make the value via MAKE_RGB(), MAKE_RGBA().
*
* @retval       none
*
*/
__INLINE void WdgCommonPickSetTextColor
(
    IWidget             *pWDGCommonPick,
    RGBColor_t          TextColor
)
{
    WdgCommonSetProperty(pWDGCommonPick, PROP_WDG_HIGHLIGHT_TEXT_COLOR, (u32)(TextColor));
}

/** WdgCommonPickSetArrowInside
* @brief        Set arrow inside or outside of the item widget.
*
*
* @param[in]    pWDGCommonPick    The CommonPick widget which want to be set
* @param[in]    bInside           TRUE: Arrow is inside of item widget.
*                                 FALSE: Arrow is outside of item widget.
*
* @retval       none
*
*/
__INLINE void WdgCommonPickSetArrowInside
(
    IWidget                 *pWDGCommonPick,
    boolean                 bInside
)
{
    WdgCommonSetProperty(pWDGCommonPick, PROP_SCLIND_WDG_ARROW_POSITION, (u32)bInside);
}

/** WdgCommonPickSetInvisibleIfDisable
* @brief        Set arrow to be invisible if it is disable
*
* @param[in]    pWDGCommonPick    The CommonPick widget which want to be set
* @param[in]    bInvisible        The invisible status
*                                 TRUE  : Arrow is invisible if it is disable.
*                                 FALSE : Arrow is "Bitmap"(ARROW_IMG_TYPE_DISABLE) if it is disable.
*
* @retval       none
*
*/
__INLINE void WdgCommonPickSetInvisibleIfDisable
(
    IWidget                 *pWDGCommonPick,
    boolean                 bInvisible
)
{
    WdgCommonSetProperty(pWDGCommonPick, PROP_SCLIND_WDG_INVISIBLE_IF_DISABLE, (u32)bInvisible);
}

/** WdgCommonPickSetArrowWidth
* @brief        Set widget's arrow width in pixel
*
* @param[in]    pWDGCommonPick    The CommonPick widget which want to be set
* @param[in]    nWidth            The arrow width in pixel
* @param[in]    eDirection        The arrow type we want to set, refer to Direction_e.
*
* @retval       none
*
*/
__INLINE void WdgCommonPickSetArrowWidth
(
    IWidget                 *pWDGCommonPick,
    u16                     nWidth,
    Direction_e             eDirection
)
{
    WdgCommonSetArrowWidth(pWDGCommonPick, nWidth, eDirection);
}


/** WdgCommonPickSetArrowHeight
* @brief        Set widget's arrow height in pixel
*
* @param[in]    pWDGCommonPick    The CommonPick widget which want to be set
* @param[in]    nHeight           The arrow height in pixel
* @param[in]    eDirection        The arrow type we want to set, refer to Direction_e.
*
* @retval       none
*
*/
__INLINE void WdgCommonPickSetArrowHeight
(
    IWidget                 *pWDGCommonPick,
    u16                     nHeight,
    Direction_e             eDirection
)
{
    WdgCommonSetArrowHeight(pWDGCommonPick, nHeight, eDirection);
}


/** WdgCommonPickSetArrowActiveImg
* @brief        Set arrow active image
*
* @param[in]    pWDGCommonPick    The CommonPick widget which want to be set
* @param[in]    pActiveImage      The arrow active image
* @param[in]    eDirection        The arrow type we want to set, refer to Direction_e.
*
* @retval       none
*
*/
__INLINE void WdgCommonPickSetArrowActiveImg
(
    IWidget                 *pWDGCommonPick,
    IBitmap                 *pActiveImage,
    Direction_e             eDirection
)
{
    WdgCommonSetArrowActiveImg(pWDGCommonPick, pActiveImage, eDirection);
}

/** WdgCommonPickSetArrowInActiveImg
* @brief        Set arrow inactive image
*
* @param[in]    pWDGCommonPick    The CommonPick widget which want to be set
* @param[in]    pInActiveImage    The arrow inactive image
* @param[in]    eDirection        The arrow type we want to set, refer to Direction_e.
*
* @retval       none
*
*/
__INLINE void WdgCommonPickSetArrowInActiveImg
(
    IWidget                 *pWDGCommonPick,
    IBitmap                 *pInActiveImage,
    Direction_e             eDirection
)
{
    WdgCommonSetArrowInActiveImg(pWDGCommonPick, pInActiveImage, eDirection);
}

#ifdef __TOUCH_SCREEN_MMI__
/** WdgCommonPickSetLeftArrowPressedImg
* @brief        Set image when arrow be pressed
*
* @param[in]    pWDGCommonPick    The CommonPick widget which want to be set
* @param[in]    pPressedImage     The arrow pressed image
* @param[in]    eDirection        The arrow type we want to set, refer to Direction_e.
*
* @retval       none
*/
__INLINE void WdgCommonPickSetArrowPressedImg
(
    IWidget                 *pWDGCommonPick,
    IBitmap                 *pPressedImage,
    Direction_e             eDirection
)
{
    WdgCommonSetArrowPressedImg(pWDGCommonPick, pPressedImage, eDirection);
}

#endif //__TOUCH_SCREEN_MMI__

/** WdgCommonPickSetLayoutStyle
* @brief        Set widget's layout style
*
* @param[in]    pWDGCommonPick    The CommonPick widget which want to be set
* @param[in]    eWdgLayoutStyle   The widget layout style
*
* @retval       none
*
*/
__INLINE void WdgCommonPickSetLayoutStyle
(
    IWidget                 *pWDGCommonPick,
    WdgLayoutStyle_e        eWdgLayoutStyle
)
{
    WdgCommonSetProperty(pWDGCommonPick, PROP_LAYOUT_STYLE, (u32)eWdgLayoutStyle);
}

/** WdgCommonPickSetEnableAnimate
* @brief        Turn on/off animation to widget
*
* @param[in]    pWDGCommonPick    Pointer to the CommonPick widget
* @param[in]    bEnableAnimate    TRUE, turn on,
*                                 FALSE, turn off.
*
* @retval       none
*
*/
__INLINE void WdgCommonPickSetEnableAnimate
(
    IWidget                 *pWDGCommonPick,
    boolean                 bEnableAnimate
)
{
    WdgCommonSetProperty(pWDGCommonPick, PROP_WDG_ENABLE_ANIMATE, (u32)bEnableAnimate);
}

/** WdgCommonPickGetFocusIndex
* @brief        Get CommonPick widget focused index
*
* @param[in]    pWDGCommonPick    The pointer of IWidget interface object
*
* @retval       u32                 The Focus index of CommonPick widget
*
*/
u32 WdgCommonPickGetFocusIndex
(
    IWidget                 *pWDGCommonPick
);

/** WdgCommonPickGetTopItemWdg
* @brief        Get top item of widget
*
* @param[in]    pWDGCommonPick      The CommonPick widget which want to be gotten
*
* @retval       Top item of widget
*
*/
IWidget* WdgCommonPickGetTopItemWdg
(
    IWidget                 *pWDGCommonPick
);

/** WdgCommonPickGetItemWdg
* @brief        Get ItemWdg of Pick widget in CommonPick widget
*
* @param[in]    pWDGCommonPick      The CommonPick widget which want to be gotten
*
* @retval       ItemWdg of Pick widget.
*
*/
IWidget* WdgCommonPickGetItemWdg
(
    IWidget                 *pWDGCommonPick
);

/** WdgCommonPickGetPickWdg
* @brief        Get pick widget of CommonPick widget
*
* @param[in]    pWDGCommonPick      The CommonPick widget which want to be gotten
*
* @retval       Pick widget of CommonPick widget.
*
*/
IWidget* WdgCommonPickGetPickWdg
(
    IWidget                 *pWDGCommonPick
);

/** WdgCommonPickGetDirectToogle
* @brief        Get CommonPick Widget DirectToogle status
*
* @param[in]    pWDGCommonPick      The widget which want to be gotten
*
* @retval       boolean         TRUE: When receive Action key it will toggle pick item directly,
*                               FALSE: Do Not direct toggle pick item.
*
*/
boolean WdgCommonPickGetDirectToogle
(
    IWidget                 *pWDGCommonPick
);

/** WdgCommonPickGetArrowPosition
* @brief        Get position info of arrow, inside or outside of the item widget.
*
* @param[in]    pWDGCommonPick    The widget which want to be gotten
*
* @retval       boolean             TRUE: Arrow is inside of item widget.
*                                 FALSE: Arrow is outside of item widget.
*
*/
boolean WdgCommonPickGetArrowInside
(
    IWidget                 *pWDGCommonPick
);

/** WdgCommonPickGetInvisibleIfDisable
* @brief        Get arrow invisible status when it is disable
*
* @param[in]    pWDGCommonPick    The widget which want to be gotten
*
* @retval       boolean       The invisible status if it's disabled
                            TRUE  : Arrow is invisible if it is disable.
*                           FALSE : Arrow is "Bitmap"(ARROW_IMG_TYPE_DISABLE) if it is disable.
*
*/
boolean WdgCommonPickGetInvisibleIfDisable
(
    IWidget                 *pWDGCommonPick
);

/** WdgCommonPickGetArrowWidth
* @brief        Get arrow width of widget
*
* @param[in]    pWDGCommonPick    The widget which want to be gotten
* @param[out]   pWidth            The arrow width
* @param[in]    eDirection        The arrow type
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgCommonPickGetArrowWidth
(
    IWidget                 *pWDGCommonPick,
    u16                     *pWidth,
    Direction_e             eDirection
)
{
    return WdgCommonGetArrowWidth(pWDGCommonPick, pWidth, eDirection);
}

/** WdgCommonPickGetArrowHeight
* @brief         Get arrow height of widget
*
* @param[in]     pWDGCommonPick    The widget which want to be gotten
* @param[out]    pHeight           The arrow height
* @param[in]     eDirection        The arrow type
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgCommonPickGetArrowHeight
(
    IWidget                 *pWDGCommonPick,
    u16                     *pHeight,
    Direction_e             eDirection
)
{
    return WdgCommonGetArrowHeight(pWDGCommonPick, pHeight, eDirection);
}

/** WdgCommonPickGetLayoutStyle
* @brief        Get widget's layout style
*
* @param[in]    pWDGCommonPick    The widget which want to be gotten
*
* @retval       WdgLayoutStyle_e  The widget layout style
*
*/
WdgLayoutStyle_e WdgCommonPickGetLayoutStyle
(
    IWidget                 *pWDGCommonPick
);

/*=============================================================*/
/** WdgCommonPickRegisterFocusChangeCb
* @brief        Register callback for changing focus item; CB will be triggered if focus item changed
*
* @param[in]    pWDGCommonPick    The CommonPick widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotton when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgCommonPickRegisterFocusChangeCb
(
    IWidget                 *pWDGCommonPick,
    PfnWdgCommonPickFocusChange pfn,
    void                    *pUserData
);

/** WdgCommonPickRegisterFocusSelectCb
* @brief        Register callback for selecting item; CB will be triggered if item selected
*
* @param[in]    pWDGCommonPick    The CommonPick widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotton when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgCommonPickRegisterFocusSelectCb
(
    IWidget                 *pWDGCommonPick,
    PfnWdgCommonPickFocusSelect pfn,
    void                    *pUserData
);

/** WdgCommonPickDeregisterFocusChangeCb
* @brief        Deregister callback for changing focus item
*
* @param[in]    pWDGCommonPick    The CommonPick widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotton when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgCommonPickDeregisterFocusChangeCb
(
    IWidget                 *pWDGCommonPick,
    PfnWdgCommonPickFocusChange pfn,
    void                    *pUserData
);

/** WdgCommonPickDeregisterFocusSelectCb
* @brief        Deregister callback for selecting item
*
* @param[in]    pWDGCommonPick          The CommonPick widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotton when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgCommonPickDeregisterFocusSelectCb
(
    IWidget                 *pWDGCommonPick,
    PfnWdgCommonPickFocusSelect pfn,
    void                    *pUserData
);

#endif	//__MMI_WDG_COMMONPICKITEM_H__
/*=============================================================*/
// end of file
