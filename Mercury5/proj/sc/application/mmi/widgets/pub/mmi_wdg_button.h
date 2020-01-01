/**
* @file    mmi_wdg_button.h
* @version $Id: mmi_wdg_button.h 8917 2008-04-11 03:24:13Z steve.lee $
*
* @brief   This file defines CLSID_BUTTONWIDGET class which is a kind of widget object.
*
* <Class Description>
*     Button-Widget is a widget. The functionality of Button-widget
*     is to display an image and a string upon the image. The layout graphs as below:
*<pre>
*          +----------------+
*          |              <-+--Display an image
*          |                |
*          |  "text.test"<--+--Displaying a string
*          |                |
*          +----------------+
*</pre>
*
*     There are two states in Button-widget, one is "pressed" and another is "unpressed". The
*     "pressed" state means that the user pressed this Button-widget via touch-screen. The remainder
*     is "unpressed" state. In the different state, the Button-widget would display different image 
*     and different text color.
*
*     Default unpressed text color is RGBCOLOR_BLACK and default pressed text color is RGBCOLOR_WHITE.
*     Application can change text color by setting property.
*
*     There is no default image to display, two kinds of image are kept in data-model. And the displaying
*     string is also kept in data-model.
*
*     The alignments of image and text are (ALIGN_H_CENTER | ALIGN_V_MIDDLE).
*
* <Class ID>
*     CLSID_BUTTONWIDGET.
*
*/
#ifndef __MMI_WDG_BUTTON_H__
#define __MMI_WDG_BUTTON_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_window.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_widget_properties.h"
#include "mmi_wdg_common_interface.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/** ButtonData_t
*
* @brief    pWStr             A string displaying on button
*           pUnPressedImg     An image to display when unpressed.
*           pPressedImg       An image to display when pressed.
*
*/
typedef struct {
	MAE_WChar *pWStr;           
	IImage   *pUnPressedImg; 
	IImage   *pPressedImg;  
} ButtonData_t;

/** _TxtColor_t
*
* @brief    TextColor        text string color
*           OutlineColor     text string Outline color
*
*/
typedef struct {
	RGBColor_t TextColor;
	RGBColor_t OutlineColor;
} _TxtColor_t;

/** WdgButtonDataID_t
*
* @brief    nStrID              A string ID displaying on button
*           nUnPressedID        An image ID to display when unpressed.
*           nPressedID          An image ID to display when pressed.
*
*/
typedef struct {
    u32                     nStrID;
    u32                     nUnPressedID;
    u32                     nPressedID;
}WdgButtonDataID_t;


/*=============================================================*/
// functions
/*=============================================================*/

//for button widget
/** PfnWdgButtonWidgetButtonClick
* @brief      CB register by "PfnWdgButtonWidgetButtonClick"
*             and will be trigger when the button is clicked by user.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode         Widget Event Code, only useful for softkey event
* @param[in]  dwParam       The data word param (NOT use now)
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgButtonWidgetButtonClick) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);

/** PfnWdgButtonWidgetButtonValid
* @brief        CB register by "PfnWdgButtonWidgetButtonValid"
*                 and will be triggered when Button widget is touched, and keep on touching button.
*
* @param[in]    pWDGButton        The Button widget which want to set callback
* @param[in]    pfn               callback function
*
* @param[in]  pApplet          The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData         User data ap developer setting when register CB.
* @param[in]  nEvtCode         Widget Event Code, only useful for softkey event
* @param[in]  bValid           valid value is TRUE(1) and invalid value is FALSE(0)
* @param[in]  pIWidget         The widget instance
*
*/
typedef void (*PfnWdgButtonWidgetButtonValid) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bValid,IWidget *pWidget);

/** PfnWdgButtonWidgetButtonInvalid
* @brief        CB register by "PfnWdgButtonWidgetButtonInvalid"
*                 and will be triggered when Button widget is released, or the touching is moved outside of Button.
*
* @param[in]  pApplet          The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData         User data ap developer setting when register CB.
* @param[in]  nEvtCode         Widget Event Code, only useful for softkey event
* @param[in]  bValid           valid value is TRUE(1) and invalid value is FALSE(0)
* @param[in]  pIWidget         The widget instance
*
*/
typedef void (*PfnWdgButtonWidgetButtonInvalid) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bValid,IWidget *pWidget);

/** PfnWdgButtonWidgetButtonLongPress
* @brief      CB register by "PfnWdgButtonWidgetButtonLongPress"
*             and will be trigger when the button is pressed for a long time.
*
* @param[in]  pApplet          The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData         User data ap developer setting when register CB.
* @param[in]  nEvtCode         Widget Event Code, only useful for softkey event
* @param[in]  dwParam       The data word param (NOT use now)
* @param[in]  pIWidget         The widget instance
*
*/
typedef void (*PfnWdgButtonWidgetButtonLongPress) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);

/** PfnWdgButtonWidgetButtonTouchRepeat
* @brief      CB register by "PfnWdgButtonWidgetButtonTouchRepeat"
*             and CB will be triggered while button is pressed for a long time.
*
* @param[in]  pApplet          The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData         User data ap developer setting when register CB.
* @param[in]  nEvtCode         Widget Event Code, only useful for softkey event
* @param[in]  dwParam       The data word param (NOT use now)
* @param[in]  pIWidget         The widget instance
*
*/
typedef void (*PfnWdgButtonWidgetButtonTouchRepeat) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);

/** PfnWdgButtonWidgetDataChange
* @brief      CB register by "PfnWdgButtonWidgetDataChange"
*             and will be trigger when the data of widget is changed
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  dwParam       The data word param (NOT use now)
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgButtonWidgetDataChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
/*=============================================================*/
// functions
/*=============================================================*/
/** WdgButtonCreateForWnd
* @brief        Button widget create function for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
*
* @retval       The pointer of Button             Success.
* @retval       NULL                              Failed.
*
*/
__SLDPM_FREE__ IWidget* WdgButtonCreateForWnd
(
    HWIN         hWin,
    Pos_t               *pPos,
    WidgetSize_t        *pSize,
    u16                 nWidgetID
);
/*=============================================================*/
/** WdgButtonCreate
* @brief        Create Button widget
*
* @retval       The pointer of Button   Success.
* @retval       NULL                    Failed.
*
*/
__SLDPM_FREE__ IWidget* WdgButtonCreate
(
    void
);

/** WdgButtonSetDataByID
* @brief        Set display data for button widget.
*               Specific data for button widget.
*
* @param[in]    pWDGButton         Pointer to the Button widget
* @param[in]    pDispData         Display data of Button Widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgButtonSetDataByID
(
    IWidget                 *pWDGButton,
    WdgButtonDataID_t       *pDispData
);

/** WdgButtonSetData
* @brief        Set display data for button widget.
*               Specific data for button widget.
*
* @param[in]    pWDGButton         Pointer to the Button widget
* @param[in]    pDispData         Display data of Button Widget.
* @param[in]    pfFree            Free CB function for free data allocate by User while widget destroy.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgButtonSetData
(
    IWidget                 *pWDGButton,
    ButtonData_t            *pDispData,
    PfnDataFree             pfFree
);

/** WdgButtonGetData
* @brief        Get display data from button widget.
*
* @param[in]    pWDGTitle         Pointer to the Button widget
* @param[in]    ppDispData        Display data of Button Widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgButtonGetData
(
    IWidget                 *pWDGButton,
    ButtonData_t            **ppDispData
);

/** WdgButtonDataChanged
* @brief        The content in display data for the the Button widget is changed.
*
* @param[in]    pWDGTitle         Pointer to the Button widget
*
*
*/
void WdgButtonDataChanged
(
    IWidget                 *pWDGButton
);

/** WdgButtonSetDisDisplayText
* @brief        Disable Display Text
*
* @param[in]    pWDGButton        The button widget which want to set
* @param[in]    bTextOnOff        Display text on/off
*
*
*/
__INLINE void WdgButtonSetDisDisplayText
(
    IWidget                 *pWDGButton,
    boolean                 bTextOnOff
)
{
    WdgCommonSetProperty(pWDGButton, PROP_BTN_WDG_DISABLE_DISPLAY_TEXT, (u32)bTextOnOff);
}

__INLINE void WdgButtonSetDisplayDisableBidi
(
    IWidget                 *pWDGButton,
    boolean                 bBidiOnOff
)
{
    WdgCommonSetProperty(pWDGButton, PROP_BTN_WDG_DISPLAY_DISABLE_BIDI, (u32)bBidiOnOff);
}

/** WdgButtonSetTextAlignment
* @brief        Set text alignment
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    nTextAlignment    Text Alignment
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgButtonSetTextAlignment
(
    IWidget                 *pWDGButton,
    WdgAlignment_e          nTextAlignment
)
{
    return WdgCommonSetProperty(pWDGButton, PROP_WDG_ALIGNMENT, (u32)nTextAlignment);
}

/** WdgButtonSetFontCategory
* @brief    Set font category of widget.
*
* @param[in]    pIWidget(IWidget*)    The pointer of IWidget interface object
* @param[in]    FC                    A kind of font category enum value, refer to mae_font.h
*
*
*/
__INLINE void WdgButtonSetFontCategory
(
    IWidget                 *pWDGObject,
    FontCategory_t          FC
)
{
    WdgCommonSetProperty(pWDGObject, PROP_WDG_FONT_CATE, (u32)FC);
}

/** WdgButtonSetUnpressedTextColor
* @brief        Set unpressed text color
*
* @param[in]    pWDGButton        The button widget which want to set
* @param[in]    nTextColor        Unpressed text color
*
*
*/
__INLINE void WdgButtonSetUnpressedTextColor
(
    IWidget                 *pWDGButton,
    RGBColor_t              nTextColor
)
{
    WdgCommonSetProperty(pWDGButton, PROP_BTN_WDG_UNPRESSED_TEXT_COLOR, (u32)nTextColor);
}

/** WdgButtonSetUnpressedTextOutlineColor
* @brief        Set unpressed outline text color
*
* @param[in]    pWDGButton        The button widget which want to set
* @param[in]    nOutlineColor     Unpressed outline text color
*
*
*/
__INLINE void WdgButtonSetUnpressedTextOutlineColor
(
    IWidget                 *pWDGButton,
    RGBColor_t              nOutlineColor
)
{
    WdgCommonSetProperty(pWDGButton, PROP_BTN_WDG_UNPRESSED_TEXT_OUTLINE_COLOR, (u32)nOutlineColor);
}

/** WdgButtonSetPressedTextColor
* @brief        Set pressed text color
*
* @param[in]    pWDGButton        The button widget which want to set
* @param[in]    nTextColor        Pressed text color
*
*
*/
__INLINE void WdgButtonSetPressedTextColor
(
    IWidget                 *pWDGButton,
    RGBColor_t              nTextColor
)
{
    WdgCommonSetProperty(pWDGButton, PROP_BTN_WDG_PRESSED_TEXT_COLOR, (u32)nTextColor);
}

/** WdgButtonSetPressedTextOutlineColor
* @brief        Set pressed outline text color
*
* @param[in]    pWDGButton        The button widget which want to set
* @param[in]    nOutlineColor     Pressed outline text color
*
*
*/
__INLINE void WdgButtonSetPressedTextOutlineColor
(
    IWidget                 *pWDGButton,
    RGBColor_t              nOutlineColor
)
{
    WdgCommonSetProperty(pWDGButton, PROP_BTN_WDG_PRESSED_TEXT_OUTLINE_COLOR, (u32)nOutlineColor);
}

/** WdgButtonSetPressed
* @brief        Set button pressed
*
* @param[in]    pWDGButton        The button widget which want to set
* @param[in]    nTextColor        text color
*
*
*/
__INLINE void WdgButtonSetPressed
(
    IWidget                 *pWDGButton,
    RGBColor_t              nTextColor
)
{
    WdgCommonSetProperty(pWDGButton, PROP_BTN_WDG_PRESSED_TEXT_COLOR, (u32)nTextColor);
}

#ifdef __TOUCH_SCREEN_MMI__
/** WdgButtonSetDisableTouchEvent
* @brief        Disable handle touch callback
*
* @param[in]    pWDGButton        The button widget which want to set
* @param[in]    bDisable          TouchEevent Enable/Disable flag
*
*
*/
__INLINE void WdgButtonSetDisableTouchEvent
(
    IWidget                 *pWDGButton,
    boolean                 bDisableTouchEevent
)
{
    WdgCommonSetProperty(pWDGButton, PROP_DISABLE_HANDLE_TOUCH_EVT, (u32)bDisableTouchEevent);
}
#endif

/** WdgButtonGetDisDisplayText
* @brief        Get Disable Display Text status
*
* @param[in]    pWDGButton  The button widget which want to get
*
* @retval       boolean        Get display text on/off
*
*/
boolean WdgButtonGetDisDisplayText
(
    IWidget                 *pWDGButton
);

/** WdgButtonGetUnpressedTextColor
* @brief        Get unpressed text color
*
* @param[in]     pWDGButton        The button widget which want to get
* @param[out]    pTextColor        Unpressed test color
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgButtonGetUnpressedTextColor
(
    IWidget                 *pWDGButton,
    RGBColor_t              *pTextColor
)
{
    return WdgCommonGetProperty(pWDGButton, PROP_BTN_WDG_UNPRESSED_TEXT_COLOR, (u32*)pTextColor);
}

/** WdgButtonGetUnpressedOutlineColor
* @brief        Get unpressed outline text color
*
* @param[in]     pWDGButton        The button widget which want to get
* @param[out]    pOutlineColor     outline test color
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgButtonGetUnpressedOutlineColor
(
    IWidget                 *pWDGButton,
    RGBColor_t              *pOutlineColor
)
{
    return WdgCommonGetProperty(pWDGButton, PROP_BTN_WDG_UNPRESSED_TEXT_OUTLINE_COLOR, (u32*)pOutlineColor);
}

/** WdgButtonGetPressedTextColor
* @brief        Get pressed text color
*
* @param[in]     pWDGButton        The button widget which want to get
* @param[out]    pTextColor        Pressed test color
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgButtonGetPressedTextColor
(
    IWidget                 *pWDGButton,
    RGBColor_t              *pTextColor
)
{
    return WdgCommonGetProperty(pWDGButton, PROP_BTN_WDG_PRESSED_TEXT_COLOR, (u32*)pTextColor);
}

/** WdgButtonGetPressedOutlineColor
* @brief        Get pressed outline text color
*
* @param[in]     pWDGButton        The button widget which want to get
* @param[out]    pOutlineColor     outline test color
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgButtonGetPressedOutlineColor
(
    IWidget                 *pWDGButton,
    RGBColor_t              *pOutlineColor
)
{
    return WdgCommonGetProperty(pWDGButton, PROP_BTN_WDG_PRESSED_TEXT_OUTLINE_COLOR, (u32*)pOutlineColor);
}

/** WdgButtonRegisterButtonClickCb
* @brief        Register button click callback; CB will be triggered while button be clicked.
*
* @param[in]    pWDGButton        The Button widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgButtonRegisterButtonClickCb
(
    IWidget                 *pWDGButton,
    PfnWdgButtonWidgetButtonClick   pfn,
    void                    *pUserData
);

/** WdgButtonRegisterButtonValidCb
* @brief        Register button valid callback;
                CB will be triggered when Button widget is touched, and keep on touching button.
*
* @param[in]    pWDGButton        The Button widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgButtonRegisterButtonValidCb
(
    IWidget                 *pWDGButton,
    PfnWdgButtonWidgetButtonValid   pfn,
    void                    *pUserData
);

/** WdgButtonRegisterButtonInvalidCb
* @brief        Register button invalid callback;
                CB will be triggered when Button widget is released, or the touching is moved outside of Button.
*
* @param[in]    pWDGButton        The Button widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgButtonRegisterButtonInvalidCb
(
    IWidget                 *pWDGButton,
    PfnWdgButtonWidgetButtonInvalid pfn,
    void                    *pUserData
);

/** WdgButtonRegisterButtonLongPressCb
* @brief        Register button long press callback; CB will be triggered while button is pressed for a long time.
*
* @param[in]    pWDGButton        The Button widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgButtonRegisterButtonLongPressCb
(
    IWidget                 *pWDGButton,
    PfnWdgButtonWidgetButtonLongPress   pfn,
    void                    *pUserData
);

/** WdgButtonRegisterButtonTouchRepeatCb
* @brief        Register button touch repeat callback; CB will be triggered while button is pressed for a long time.
*
* @param[in]    pWDGButton        The Button widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgButtonRegisterButtonTouchRepeatCb
(
    IWidget                 *pWDGButton,
    PfnWdgButtonWidgetButtonTouchRepeat pfn,
    void                    *pUserData
);

/** WdgButtonRegisterDataChangeCb
* @brief        Register data change callback; CB will be triggered while widget data be changed,
                Ex, text of button be changed by WdgButtonSetDataByID or WdgButtonSetData.
*
* @param[in]    pWDGButton        The Button widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgButtonRegisterDataChangeCb
(
    IWidget                 *pWDGButton,
    PfnWdgButtonWidgetDataChange pfn,
    void                    *pUserData
);

/** WdgButtonDeregisterButtonClickCb
* @brief        Deregister button click callback
*
* @param[in]    pWDGButton        The Button widget which want to Deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgButtonDeregisterButtonClickCb
(
    IWidget                 *pWDGButton,
    PfnWdgButtonWidgetButtonClick   pfn,
    void                    *pUserData
);

/** WdgButtonDeregisterButtonValidCb
* @brief        Deregister button valid callback
*
* @param[in]    pWDGButton        The Button widget which want to Deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgButtonDeregisterButtonValidCb
(
    IWidget                 *pWDGButton,
    PfnWdgButtonWidgetButtonValid   pfn,
    void                    *pUserData
);

/** WdgButtonDeregisterButtonInvalidCb
* @brief        Deregister button invalid callback
*
* @param[in]    pWDGButton        The Button widget which want to Deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgButtonDeregisterButtonInvalidCb
(
    IWidget                 *pWDGButton,
    PfnWdgButtonWidgetButtonInvalid pfn,
    void                    *pUserData
);

/** WdgButtonDeregisterButtonLongPressCb
* @brief        Deregister button long press callback
*
* @param[in]    pWDGButton        The Button widget which want to Deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgButtonDeregisterButtonLongPressCb
(
    IWidget                 *pWDGButton,
    PfnWdgButtonWidgetButtonLongPress   pfn,
    void                    *pUserData
);

/** WdgButtonDeregisterButtonTouchRepeatCb
* @brief        Deregister button touch repeat callback
*
* @param[in]    pWDGButton        The Button widget which want to Deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgButtonDeregisterButtonTouchRepeatCb
(
    IWidget                 *pWDGButton,
    PfnWdgButtonWidgetButtonTouchRepeat pfn,
    void                    *pUserData
);

/** WdgButtonDeregisterDataChangeCb
* @brief        Deregister data change callback
*
* @param[in]    pWDGButton        The Button widget which want to Deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgButtonDeregisterDataChangeCb
(
    IWidget                 *pWDGButton,
    PfnWdgButtonWidgetDataChange pfn,
    void                    *pUserData
);

MAE_Ret WdgButtonEnableTouchHook(IWidget *pWDGButton, boolean bEnable);

#endif //__MMI_WDG_BUTTON_H__
/*=============================================================*/
// end of file
