#ifndef __MMI_WDG_DATE_H__
#define __MMI_WDG_DATE_H__

/* ===========================================================*/
// Description
/* ===========================================================*/
/**
*
*  The purpose of Date widget is provide the date format information from
*  the inputting data. Format is "YYYY/MM/DD". The detailed type, like fonts
*  color or text height, can also be adjusted to user's definition.
*
*          ex:
*           +--------------+
*           |              |
*           |  2009/1/23   |
*           +--------------+
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

/** WdgDateDateSetting_t
*
* @brief    nMaxYear:        The maximum allowable Year
*           nMinYear:        The minimum allowable Year
*           bAdjustValue:    Can use UP/Down navigation key to adjust the input values or not
*
*/
typedef struct
{
    u16                     nMaxYear;
    u16                     nMinYear;
    boolean                 bAdjustValue;

}WdgDateDateSetting_t;
/*=============================================================*/
// functions
/*=============================================================*/
/** PfnWdgDateFieldAutoCorrect
* @brief      CB register by "WdgDateRegisterFieldAutoCorrectCb"
*                  and will be trigger when the Input value is illegal(Ex, Month > 12).
*
* @param[in]  pApplet        The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData       User data ap developer setting when register CB.
* @param[in]  nEvtCode       Widget Event Code, only useful for softkey event
* @param[in]  nReserve       Unuseful parameter
* @param[in]  pIWidget       The widget instance
*
*/
typedef void (*PfnWdgDateFieldAutoCorrect) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);

/** PfnWdgDateFocusChange
* @brief      CB register by "WdgDateRegisterFocusChangeCb"
*             and will be trigger when focused item is changed, Ex, Focus change from Year to Month.
*
* @param[in]  pApplet         The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData        User data ap developer setting when register CB.
* @param[in]  nEvtCode        Widget Event Code, only useful for softkey event
* @param[in]  nReserve        Unuseful parameter
* @param[in]  pIWidget        The widget instance
*
*/
typedef void (*PfnWdgDateFocusChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);

/** PfnWdgDateWidgetFormatinputDataChange
* @brief      CB register by "WdgDateRegisterFormatinputDataChangeCb"
*             and will be triggered while data is changed by the format input widget.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nReserve          Reserve for enhancement in the future
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgDateWidgetFormatinputDataChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);

/*=============================================================*/
/** WdgDateCreateForWnd
* @brief        Date widget create function for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
* @param[in]    pDateValue          Date value. (A pointer of MAE_DateTime_t structure.)
*                                   NULL; means you need system date.
*
* @retval       The pointer of Date        Success.
* @retval       NULL                       Failed.
*
*/
IWidget* WdgDateCreateForWnd
(
    HWIN         hWin,
    Pos_t               *pPos,
    WidgetSize_t        *pSize,
    u16                 nWidgetID,
    MAE_DateTime_t      *pDateValue
);

/** WdgDateCommon_SetDateSetting
* @brief        Set maximum allowable Year, minimum allowable Year, and use UP/Down navigation key to adjust the input values or not
*
* @param[in]    pWDGDate           The Date widget which want to be set
* @param[in]    pDateSetting       The pointer of WdgDateDateSetting_t
*
* @retval       MAE_RET_SUCCESS    Success.
* @retval       MAE_RET_BAD_PARAM  Failed. pDateSetting is NULL
* @retval       MAE_RET_FAILED     Failed.
*
*/
MAE_Ret WdgDateCommon_SetDateSetting
(
    IWidget                    *pWDGDate,
    WdgDateDateSetting_t       *pDateSetting
);
/*=============================================================*/
/** WdgDateCreate
* @brief        Create Date widget
*
* @param[in]    hWin                         The window handle
*
* @retval       The pointer of Date             Success.
* @retval       NULL                            Failed.
*
*/
IWidget* WdgDateCreate
(
    HWIN         hWin
);
/*=============================================================*/
/** WdgDateSetDateValue
* @brief        Set Date value, Specific data for Date widget.
*
* @param[in]    pWDGDate       The Date widget which want to be set
* @param[in]    pDateValue        Date value. (A pointer of MAE_DateTime_t structure.)
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgDateSetDateValue
(
    IWidget                 *pWDGDate,
    MAE_DateTime_t          *pDateValue
)
{
    return WdgCommonSetProperty(pWDGDate, PROP_FORMATINPUT_WDG_DATE_VALUE, (u32)pDateValue);
}

/** WdgDateSetSoftKeyBoardEnable
* @brief        Set the ability to input by soft keyboard
*
* @param[in]    pWDGDate              The Date widget which want to be set
* @param[in]    bSoftKeyBoardEnable   TRUE/FALSE (Enable/Disable soft keyboard)
*
* @retval       none
*
*/
__INLINE void WdgDateSetSoftKeyBoardEnable
(
    IWidget                 *pWDGDate,
    boolean                 bSoftKeyBoardEnable
)
{
    WdgCommonSetProperty(pWDGDate, PROP_INPUT_WDG_SOFTKEYBOARD_ENABLE, (u32)bSoftKeyBoardEnable);
}

/** WdgDateSetSoftKeyBoardAlwaysOn
* @brief        Set soft keyboard always on
*
* @param[in]    pWDGDate                The Date widget which want to be set
* @param[in]    bSoftKeyBoardAlwaysOn   TRUE/FALSE (Soft keyboard is always on or not)
*
* @retval       none
*
*/
__INLINE void WdgDateSetSoftKeyBoardAlwaysOn
(
    IWidget                 *pWDGDate,
    boolean                 bSoftKeyBoardAlwaysOn
)
{
    WdgCommonSetProperty(pWDGDate, PROP_INPUT_WDG_SOFTKEYBOARD_ALWAYS_ON, (u32)bSoftKeyBoardAlwaysOn);
}

/** WdgDateSetEnableAdjustValueByNaviUpDown
* @brief        Set enable if you can use UP/Down navigation key to adjust the input values.
*
* @param[in]    pWDGDate        The Date widget which want to be set
* @param[in]    bAdjustValue    TRUE/FALSE (Can use UP/Down navigation key to adjust the input values or not)
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgDateSetEnableAdjustValueByNaviUpDown
(
    IWidget                 *pWDGDate,
    boolean                 bAdjustValue
)
{
    return WdgCommonSetProperty(pWDGDate, PROP_FORMATINPUT_WDG_ENABLE_ADJUST_VALUE_BY_NAVI_UP_DOWN, (u32)bAdjustValue);
}

/** WdgDateSetMaxYear
* @brief        Set the maximum allowable Year
*
* @param[in]    pWDGDate          The Date widget which want to be set
* @param[in]    nMaxYear          The maximum allowable Year
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgDateSetMaxYear
(
    IWidget                 *pWDGDate,
    u16                     nMaxYear
)
{
    return WdgCommonSetProperty(pWDGDate, PROP_FORMATINPUT_WDG_SET_MAX_YEAR, (u32)nMaxYear);
}

/** WdgDateSetMinYear
* @brief        Set the minimum allowable Year
*
* @param[in]    pWDGDate          The Date widget which want to be set
* @param[in]    nMinYear          The minimum allowable Year
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgDateSetMinYear
(
    IWidget                 *pWDGDate,
    u16                     nMinYear
)
{
    return WdgCommonSetProperty(pWDGDate, PROP_FORMATINPUT_WDG_SET_MIN_YEAR, (u32)nMinYear);
}

/** WdgDateSetFGColor
* @brief        Set the text color(not highlight text)
*
* @param[in]    pWDGDate          The Date widget which want to be set
* @param[in]    nFGColor          The widget foreground color which will be set to the Date widget
*
* @retval       none
*
*/
__INLINE void WdgDateSetFGColor
(
    IWidget                 *pWDGDate,
    RGBColor_t              nFGColor
)
{
    WdgCommonSetProperty(pWDGDate, PROP_WDG_FG_COLOR, (u32)nFGColor);
}

/** WdgDateSetHighlightTextColor
* @brief        Set the text color of editing field
*
* @param[in]    pWDGDate        The Date widget which want to be set
* @param[in]    nTextColor      The text color of editing field
*
* @retval       none
*
*/
__INLINE void WdgDateSetHighlightTextColor
(
    IWidget                 *pWDGDate,
    RGBColor_t              nTextColor
)
{
    WdgCommonSetProperty(pWDGDate, PROP_FORMATINPUT_WDG_HIGHLIGHT_TEXT_COLOR, (u32)nTextColor);
}

/** WdgDateSetHighlightBGColor
* @brief        Set the background color of editing field
*
* @param[in]    pWDGDate          The Date widget which want to be set
* @param[in]    nBGColor          The background color of editing field
*
* @retval       none
*
*/
__INLINE void WdgDateSetHighlightBGColor
(
    IWidget                 *pWDGDate,
    RGBColor_t              nBGColor
)
{
    WdgCommonSetProperty(pWDGDate, PROP_FORMATINPUT_WDG_HIGHLIGHT_BG_COLOR, (u32)nBGColor);
}

/** WdgDateSetAlignment
* @brief        Set Date widget alignment flag ( refer: WdgAlignment_e)
*
* @param[in]    pWDGDate         The Date widget which want to be set
* @param[in]    eWdgAlignment    The widget alignment flag which will be set to the Date widget
*
* @retval       none
*
*/
__INLINE void WdgDateSetAlignment
(
    IWidget                 *pWDGDate,
    WdgAlignment_e          eWdgAlignment
)
{
    WdgCommonSetProperty(pWDGDate, PROP_WDG_ALIGNMENT, (u32)eWdgAlignment);
}

/** WdgDateGetDateValue
* @brief        Get Date value
*
* @param[in]     pWDGDate         The Date widget which want to be get
* @param[out]    pDateValue       Date value.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgDateGetDateValue
(
    IWidget                 *pWDGDate,
    MAE_DateTime_t          *pDateValue
)
{
    return WdgCommonGetProperty(pWDGDate, PROP_FORMATINPUT_WDG_DATE_VALUE, (u32*)pDateValue);
}

/** WdgDateGetHighlightBGColor
* @brief        Get the background color of editing field
*
* @param[in]    pWDGDate          The Date widget which want to be get
* @param[out]   pBGColor          The background color of editing field
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgDateGetHighlightBGColor
(
    IWidget                 *pWDGDate,
    RGBColor_t              *pBGColor
)
{
    return WdgCommonGetProperty(pWDGDate, PROP_FORMATINPUT_WDG_HIGHLIGHT_BG_COLOR, (u32*)pBGColor);
}

/** WdgDateGetHighlightTextColor
* @brief        Get the text color of editing field
*
* @param[in]    pWDGDate         The Date widget which want to be get
* @param[out]   pTextColor      The text color of editing field
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgDateGetHighlightTextColor
(
    IWidget                 *pWDGDate,
    RGBColor_t              *pTextColor
)
{
    return WdgCommonGetProperty(pWDGDate, PROP_FORMATINPUT_WDG_HIGHLIGHT_TEXT_COLOR, (u32*)pTextColor);
}

/** WdgDateEnableCheckLunarFebruary
* @brief        Enable the lunar February validation check, default is enable
*				     If disable the check, 2/30 is always valid
*
* @param[in]    pWDGDate         The Date widget
*
* @retval       none
*
*/
__INLINE void WdgDateEnableCheckLunarFebruary
(
    IWidget                 *pWDGDate
)
{
	FormatInputSetDisableCheckLunarFebruary(pWDGDate, FALSE);
}

/** WdgDateDisableCheckLunarFebruary
* @brief        Disable the lunar February validation check, default is enable
*				     If disable the check, 2/30 is always valid
*
* @param[in]    pWDGDate         The Date widget
*
* @retval       none
*
*/
__INLINE void WdgDateDisableCheckLunarFebruary
(
    IWidget                 *pWDGDate
)
{
	FormatInputSetDisableCheckLunarFebruary(pWDGDate, TRUE);
}

/** WdgDateSetDisplayFormat
* @brief        Set the display format (YYYYMMDD / MMDDYYYY / DDMMYYYY)
*
* @param[in]    pWDGDate         The Date widget
* @param[in]	eFormat				The Display format, refer to DateWdgDisplayFormat_e
*
* @retval       none
*
*/
__INLINE void WdgDateSetDisplayFormat
(
    IWidget                 *pWDGDate,
	DateWdgDisplayFormat_e  eFormat
)
{
	WdgCommonSetProperty(pWDGDate, PROP_FORMATINPUT_WDG_DATE_DISPLAY_FORMAT, (u32)eFormat);
}

/*=============================================================*/
/** WdgDateRegisterFieldAutoCorrectCb
* @brief        Register callback : For the format input widget, CB will be triggered, it keeps focused at original field after correcting the data???
*
* @param[in]    pWDGDate          The Date widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgDateRegisterFieldAutoCorrectCb
(
    IWidget                     *pWDGDate,
    PfnWdgDateFieldAutoCorrect  pfn,
    void                        *pUserData
);

/** WdgDateRegisterFocusChangeCB
* @brief        Register callback for changing focused item; CB will be triggered if focused item is changed
*
* @param[in]    pWDGDate          The Date widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgDateRegisterFocusChangeCb
(
    IWidget                 *pWDGDate,
    PfnWdgDateFocusChange   pfn,
    void                    *pUserData
);

/** WdgDateRegisterFormatinputDataChangeCb
* @brief        Register data change callback; CB will be triggered while data is changed by the format input widget.
*
* @param[in]    pWDGDate          The Date widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotton when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgDateRegisterFormatinputDataChangeCb
(
    IWidget                                 *pWDGDate,
    PfnWdgDateWidgetFormatinputDataChange   pfn,
    void                                    *pUserData
);

/** WdgDateDereregisterFieldAutoCorrectCb
* @brief        Deregister PfnWdgDateFieldAutoCorrect callback
*
* @param[in]    pWDGDate          The Date widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgDateDeregisterFieldAutoCorrectCb
(
    IWidget                     *pWDGDate,
    PfnWdgDateFieldAutoCorrect  pfn,
    void                        *pUserData
);

/** WdgDateDeregisterFocusChangeCb
* @brief        Deregister callback for changing focus item
*
* @param[in]    pWDGDate          The Date widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgDateDeregisterFocusChangeCb
(
    IWidget                 *pWDGDate,
    PfnWdgDateFocusChange   pfn,
    void                    *pUserData
);

/** WdgDateDeregisterFormatinputDataChangeCb
* @brief        Deregister data change callback
*
* @param[in]    pWDGDate          The Date widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotton when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgDateDeregisterFormatinputDataChangeCb
(
    IWidget                                 *pWDGDate,
    PfnWdgDateWidgetFormatinputDataChange   pfn,
    void                                    *pUserData
);

#endif //__MMI_WDG_DATE_H__
