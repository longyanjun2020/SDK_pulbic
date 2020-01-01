#ifndef __MMI_WDG_IP_H__
#define __MMI_WDG_IP_H__
/* ===========================================================*/
// Description
/* ===========================================================*/
/**
*    Provide the IP format information from the inputting data. Format is
*    ¡§NNN.NNN.NNN.NNN¡¨, and each field maximum value is 255.
*
*       ex:  IP Widget
*       +-----------------------------+
*       |       120. 109. 3 .20       |    Format: XXX.XXX.XXX.XXX
*       +-----------------------------+
*
*/

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_window.h"
#include "mmi_mae_view_wrapper.h"
#include "mmi_wdg_formatinput.h"
#include "mmi_mae_imeassistmodel.h"
#include "mmi_wdg_common_interface.h"

/*=============================================================*/
// type and define
/*=============================================================*/
/** PfnWdgIPFocusChange
* @brief      CB register by "WdgIPRegisterFocusChangeCb"
*             and will be trigger when the Focus of widget is changed; Ex,click arrows or press "Action Key"
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pFocusChangeData  The info of focus change, refer to FocusChangeData_t
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgIPFocusChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusChangeData_t *pFocusChangeData, IWidget *pWidget);

/** PfnWdgIPWidgetFormatinputDataChange
* @brief      CB register by "WdgIPRegisterFormatinputDataChangeCb"
*             and will be triggered while data is changed by the format input widget.
*
* @param[in]  pApplet         The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData        User data ap developer setting when register CB.
* @param[in]  nEvtCode        Widget Event Code, only useful for softkey event
* @param[in]  nReserve        Reserve for enhancement in the future
* @param[in]  pIWidget        The widget instance
*
*/
typedef void (*PfnWdgIPWidgetFormatinputDataChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);

typedef struct
{
    FontCategory_t        nFontCategory;    //The widget font size which will be set to the IP widget
    FontType_t            nFontType;        //The widget font type which will be set to the IP widget

}WdgIPFont_t;

typedef struct
{
    RGBColor_t              nBGColor;        //The background color of editing field
    RGBColor_t              nTextColor;      //The text color of editing field

}WdgIPHighlightColor_t;
/*=============================================================*/
// functions
/*=============================================================*/
/** WdgIPCreateForWnd
* @brief        Create IP Widget and set the IP value for Window
*
* @param[in]    hWin         The window handle
* @param[in]    pPos            A pointer of widget position; can't be NULL.
* @param[in]    pSize           A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID       The widget unique ID of window
* @param[in]    pIPValue        The IP value
*
* @retval       The pointer of IP      Success.
* @retval       NULL                   Failed.
*
*/
IWidget* WdgIPCreateForWnd
(
    HWIN       hWin,
    Pos_t             *pPos,
    WidgetSize_t      *pSize,
    u16               nWidgetID,
    u32               *pIPValue
);

/** WdgIPCommonSetFont
* @brief        Set the font size and the font type
*
* @param[in]    pWDGIP           The IP widget which want to be set
* @param[in]    pFont            The pointer of WdgIPFont_t
*
* @retval       void
*
*/
void WdgIPCommonSetFont
(
                IWidget            *pWDGIP,
                WdgIPFont_t        *pFont
);

/** WdgIPCommonSetHighlightColor
* @brief        Set the font size and the font type
*
* @param[in]    pWDGIP                The IP widget which want to be set
* @param[in]    pHighlightColor       The pointer of WdgIPHighlightColor_t
*
* @retval       void
*
*/
void WdgIPCommonSetHighlightColor
(
                IWidget               *pWDGIP,
                WdgIPHighlightColor_t *pHighlightColor
);
/*=============================================================*/
/** WdgIPCreate
* @brief        Create IP widget
*
* @param[in]    hWin                 The window handle
*
* @retval       The pointer of IP       Success.
* @retval       NULL                    Failed.
*
*/
IWidget* WdgIPCreate
(
    HWIN         hWin
);
/*=============================================================*/

/** WdgIPSetSoftKeyBoardEnable
* @brief        Set the ability to input by soft keyboard
*
* @param[in]    pWDGIP              The IP widget which want to be set
* @param[in]    bSoftKeyBoardEnable TRUE/FALSE (Enable/Disable soft keyboard)
*
* @retval       void
*
*/
__INLINE void WdgIPSetSoftKeyBoardEnable
(
    IWidget                 *pWDGIP,
    boolean                 bSoftKeyBoardEnable
)
{
    WdgCommonSetProperty(pWDGIP, PROP_INPUT_WDG_SOFTKEYBOARD_ENABLE, (u32)bSoftKeyBoardEnable);
}

/** WdgIPSetSoftKeyBoardAlwaysOn
* @brief        Set soft keyboard always on
*
* @param[in]    pWDGIP                  The IP widget which want to be set
* @param[in]    bSoftKeyBoardAlwaysOn   TRUE/FALSE (Soft keyboard is always on or not)
*
* @retval       void
*
*/
__INLINE void WdgIPSetSoftKeyBoardAlwaysOn
(
    IWidget                 *pWDGIP,
    boolean                 bSoftKeyBoardAlwaysOn
)
{
    WdgCommonSetProperty(pWDGIP, PROP_INPUT_WDG_SOFTKEYBOARD_ALWAYS_ON, (u32)bSoftKeyBoardAlwaysOn);
}

/** WdgIPSetEnableAdjustValueByNaviUpDown
* @brief        Set enable if you can use UP/Down navigation key to adjust the input values.
*
* @param[in]    pWDGIP            The IP widget which want to be set
* @param[in]    bAdjustValue      TRUE/FALSE (Can use UP/Down navigation key to adjust the input values or not)
*
* @retval       void
*
*/
__INLINE void WdgIPSetEnableAdjustValueByNaviUpDown
(
    IWidget                 *pWDGIP,
    boolean                 bAdjustValue
)
{
    WdgCommonSetProperty(pWDGIP, PROP_FORMATINPUT_WDG_ENABLE_ADJUST_VALUE_BY_NAVI_UP_DOWN, (u32)bAdjustValue);
}

/** WdgIPSetIPValue
* @brief        Set the IP value, Specific data for IP widget.
*
* @param[in]    pWDGIP            The IP widget which want to be set
* @param[in]    pIPValue          The IP value, IP value.  ex. 0xFFFFFFFF --> 255.255.255.255   0x04030201 --> 4.3.2.1
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgIPSetIPValue
(
    IWidget               *pWDGIP,
    u32                   *pIPValue
)
{
    return WdgCommonSetProperty(pWDGIP, PROP_FORMATINPUT_WDG_IP_VALUE, (u32)pIPValue);
}

/** WdgIPSetFontCategory
* @brief        Set the font category
*
* @param[in]    pWDGIP            The IP widget which want to be set
* @param[in]    nFontCat          The font size
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgIPSetFontCategory
(
    IWidget               *pWDGIP,
    FontCategory_t   nFontCat
)
{
    return WdgCommonSetProperty(pWDGIP, PROP_WDG_FONT_CATE, (u32)nFontCat);
}

/** WdgIPSetFontType
* @brief        Set the Font Type
*
* @param[in]    pWDGIP            The IP widget which want to be set
* @param[in]    nFontType         The Font Type
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgIPSetFontType
(
    IWidget               *pWDGIP,
    FontType_t          nFontType
)
{
    return WdgCommonSetProperty(pWDGIP, PROP_WDG_FONT_TYPE, (u32)nFontType);
}

/** WdgIPSetFGColor
* @brief        Set the foreground color
*
* @param[in]    pWDGIP            The IP widget which want to be set
* @param[in]    nFGColor          The widget foreground color which will be set to the IP widget
*
* @retval       void
*
*/
__INLINE void WdgIPSetFGColor
(
    IWidget              *pWDGIP,
    RGBColor_t           nFGColor
)
{
    WdgCommonSetProperty(pWDGIP, PROP_WDG_FG_COLOR, (u32)nFGColor);
}

/** WdgIPSetHighlightTextColor
* @brief        Set the text color of editing field
*
* @param[in]    pWDGIP          The IP widget which want to be set
* @param[in]    nTextColor      The text color of editing field
*
* @retval       void
*
*/
__INLINE void WdgIPSetHighlightTextColor
(
    IWidget             *pWDGIP,
    RGBColor_t          nTextColor
)
{
    WdgCommonSetProperty(pWDGIP, PROP_FORMATINPUT_WDG_HIGHLIGHT_TEXT_COLOR, (u32)nTextColor);
}

/** WdgIPSetHighlightBGColor
* @brief        Set the background color of editing field
*
* @param[in]    pWDGIP           The IP widget which want to be set
* @param[in]    nBGColor         The background color of editing field
*
* @retval       void
*
*/
__INLINE void WdgIPSetHighlightBGColor
(
    IWidget              *pWDGIP,
    RGBColor_t           nBGColor
)
{
    WdgCommonSetProperty(pWDGIP, PROP_FORMATINPUT_WDG_HIGHLIGHT_BG_COLOR, (u32)nBGColor);
}

/** WdgIPSetAlignment
* @brief        Set IP widget alignment flag
*
* @param[in]    pWDGIP            The IP widget which want to be set
* @param[in]    eWdgAlignment     The widget alignment flag which will be set to the IP widget
*
* @retval       void
*
*/
__INLINE void WdgIPSetAlignment
(
    IWidget           *pWDGIP,
    WdgAlignment_e    eWdgAlignment
)
{
    WdgCommonSetProperty(pWDGIP, PROP_WDG_ALIGNMENT, (u32)eWdgAlignment);
}
/*=============================================================*/

/** WdgIPGetIPValue
* @brief        Get the IP value, Specific data for IP widget.
*
* @param[in]   pWDGIP         The IP widget which want to be gotten
* @param[out]  pIPValue       The IP value, IP value.  ex. 0xFFFFFFFF --> 255.255.255.255   0x04030201 --> 4.3.2.1
*
* @retval      MAE_RET_SUCCESS   Success
* @retval      others            Failed
*
*/
__INLINE MAE_Ret WdgIPGetIPValue
(
    IWidget              *pWDGIP,
    u32                  *pIPValue
)
{
    return WdgCommonGetProperty(pWDGIP, PROP_FORMATINPUT_WDG_IP_VALUE, (u32*)pIPValue);
}

/** WdgIPGetHighlightBGColor
* @brief        Get the background color of editing field
*
* @param[in]    pWDGIP           The IP widget which want to be gotten
* @param[out]   pBGColor         The background color of editing field
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgIPGetHighlightBGColor
(
    IWidget             *pWDGIP,
    RGBColor_t          *pBGColor
)
{
    return WdgCommonGetProperty(pWDGIP, PROP_FORMATINPUT_WDG_HIGHLIGHT_BG_COLOR, (u32*)pBGColor);
}

/** WdgIPGetHighlightTextColor
* @brief        Get the text color of editing field
*
* @param[in]    pWDGIP          The IP widget which want to be gotten
* @param[out]   pTextColor      The text color of editing field
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgIPGetHighlightTextColor
(
    IWidget             *pWDGIP,
    RGBColor_t          *pTextColor
)
{
    return WdgCommonGetProperty(pWDGIP, PROP_FORMATINPUT_WDG_HIGHLIGHT_TEXT_COLOR, (u32*)pTextColor);
}
/*=============================================================*/
/** WdgIPRegisterFocusChangeCb
* @brief        Register callback for changing focused item; CB will be triggered if focused item is changed
*
* @param[in]    pWDGIP      The IP widget which want to set callback
* @param[in]    pfn         callback function
* @param[in]    pUserData    User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgIPRegisterFocusChangeCb
(
    IWidget                 *pWDGIP,
    PfnWdgIPFocusChange     pfn,
    void                    *pUserData
);

/** WdgIPRegisterFormatinputDataChangeCb
* @brief        Register data change callback; CB will be triggered while data is changed by the format input widget.
*
* @param[in]    pWDGIP          The IP widget which want to set callback
* @param[in]    pfn             callback function
* @param[in]    pUserData        User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgIPRegisterFormatinputDataChangeCb
(
    IWidget                             *pWDGIP,
    PfnWdgIPWidgetFormatinputDataChange pfn,
    void                                *pUserData
);

/** WdgIPDeregisterFocusChangeCb
* @brief        Deregister callback for changing focused item
*
* @param[in]    pWDGIP      The IP widget which want to cancel callback
* @param[in]    pfn         callback function
* @param[in]    pUserData    User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgIPDeregisterFocusChangeCb
(
    IWidget                 *pWDGIP,
    PfnWdgIPFocusChange     pfn,
    void                    *pUserData
);

/** WdgIPDeregisterFormatinputDataChangeCb
* @brief        Deregister data change callback
*
* @param[in]    pWDGIP     The IP widget which want to cancel callback
* @param[in]    pfn        callback function
* @param[in]    pUserData   User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgIPDeregisterFormatinputDataChangeCb
(
    IWidget                             *pWDGIP,
    PfnWdgIPWidgetFormatinputDataChange pfn,
    void                                *pUserData
);
#endif //__MMI_WDG_IP_H__
