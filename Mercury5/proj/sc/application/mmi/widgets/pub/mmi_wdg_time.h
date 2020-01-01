/**
*          Time Widget provides the time format information from the
*          inputting data, including a 24-hour and 12-hour system clock.
*           Clock format is HH:MM (24 hour) or HH:MM AM/PM (12 hour)
*
*          ex: Time Widget
*           +---------------+          +------------+
*           |     09:08     |     or   |  09:08 PM  |
*           +---------------+          +------------+
*                12 hour                  24 hour
*/

#ifndef __MMI_WDG_TIME_H__
#define __MMI_WDG_TIME_H__

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
#include "mmi_mae_datamodel.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/** WdgTimeTimeSetting_t
*
* @brief    bHourFormat:    Hour format is 12-hour or not
*           bSecondField:   Enable second field or not
*           bAdjustValue:   Can use UP/Down navigation key to adjust the input values or not
*
*/
typedef struct
{
    boolean                 bHourFormat;
    boolean                 bSecondField;
    boolean                 bAdjustValue;

}WdgTimeTimeSetting_t;

/*=============================================================*/
// functions
/*=============================================================*/
/** PfnWdgTimeFieldAutoCorrect
* @brief      CB register by "WdgTimeRegisterFieldAutoCorrectCB"
*             and will be trigger when the Input value is illegal(Ex, minute > 60).
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nReserve           Unuseful parameter
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgTimeFieldAutoCorrect) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);


/** PfnWdgTimeFocusChange
* @brief      CB register by "WdgTimeRegisterFocusChangeCB"
*             and will be trigger when focused item is changed, Ex, Focus change from Hour to Minute.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nReserve           Unuseful parameter
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgTimeFocusChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);


/** PfnWdgTimeTimeAMPMChange
* @brief      CB register by "WdgTimeRegisterTimeAMPMChangeCB"
*             and will be trigger when the time's AM/PM is changed
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  eTimePeriod       AM or PM of the time
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgTimeTimeAMPMChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TimePeriod_e eTimePeriod, IWidget *pWidget);

/** PfnWdgTimeWidgetDataChange
* @brief      CB register by "WdgTimeRegisterDataChangeCB"
*             and will be trigger when the widget's data is changed
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  dwParam          The data word param (NOT use now)
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgTimeWidgetDataChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

/** PfnWdgTimeWidgetFormatinputDataChange
* @brief      CB register by "WdgTimeRegisterFormatinputDataChangeCb"
*             and will be triggered while data is changed by the format input widget.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nReserve          Reserve for enhancement in the future
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgTimeWidgetFormatinputDataChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);

/** WdgTimeCreateForWnd
* @brief        Create Time widget and set size for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
*
* @retval       The pointer of Time         Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgTimeCreateForWnd
(
    HWIN             hWin,
    Pos_t                   *pPos,
    WidgetSize_t            *pSize,
    u16                     nWidgetID
);

/** WdgTimeCommonSetTimeSetting
* @brief        Set Hour format 12-hour or not, second field or not, and use UP/Down navigation key to adjust the input values or not
*
* @param[in]    pWDGTime            The Time widget which want to be set
* @param[in]    pTimeSetting        The pointer of WdgTimeTimeSetting_t
*
* @retval        MAE_RET_SUCCESS        Success.
* @retval        MAE_RET_BAD_PARAM      Failed. pTimeSetting is NULL
* @retval        MAE_RET_FAILED         Failed
*
*/
MAE_Ret WdgTimeCommonSetTimeSetting
(
    IWidget                 *pWDGTime,
    WdgTimeTimeSetting_t    *pTimeSetting
);
/*=============================================================*/
/** WdgTimeCreate
* @brief        Create Time widget
*
* @param[in]    hWin             The window handle
*
* @retval       The pointer of Time         Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgTimeCreate
(
    HWIN            hWin
);
/*=============================================================*/
/** WdgTimeSetTimeValue
* @brief        Set Time value, Specific data for Time widget.
*
* @param[in]    pWDGTime          The Time widget which want to be set
* @param[in]    pTimeValue        Time value. (A pointer of MAE_DateTime_t structure.)
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTimeSetTimeValue
(
    IWidget                 *pWDGTime,
    MAE_DateTime_t          *pTimeValue
)
{
    return WdgCommonSetProperty(pWDGTime, PROP_FORMATINPUT_WDG_TIME_VALUE, (u32)pTimeValue);
}

/** WdgTimeSetSoftKeyBoardEnable
* @brief        Set the ability to input by soft keyboard
*
* @param[in]    pWDGTime            The Time widget which want to be set
* @param[in]    bSoftKeyBoardEnable TRUE/FALSE (Enable/Disable soft keyboard)
*
* @retval       None
*
*/
__INLINE void WdgTimeSetSoftKeyBoardEnable
(
    IWidget                 *pWDGTime,
    boolean                 bSoftKeyBoardEnable
)
{
    WdgCommonSetProperty(pWDGTime, PROP_INPUT_WDG_SOFTKEYBOARD_ENABLE, (u32)bSoftKeyBoardEnable);
}

/** WdgTimeSetSoftKeyBoardAlwaysOn
* @brief        Set soft keyboard always on
*
* @param[in]    pWDGTime                The Time widget which want to be set
* @param[in]    bSoftKeyBoardAlwaysOn   TRUE/FALSE (Soft keyboard is always on or not)
*
* @retval       None
*
*/
__INLINE void WdgTimeSetSoftKeyBoardAlwaysOn
(
    IWidget                 *pWDGTime,
    boolean                 bSoftKeyBoardAlwaysOn
)
{
    WdgCommonSetProperty(pWDGTime, PROP_INPUT_WDG_SOFTKEYBOARD_ALWAYS_ON, (u32)bSoftKeyBoardAlwaysOn);
}

/** WdgTimeSetEnableAdjustValueByNaviUpDown
* @brief        Set enable if you can use UP/Down navigation key to adjust the input values.
*
* @param[in]    pWDGTime          The Time widget which want to be set
* @param[in]    bAdjustValue      TRUE/FALSE (Can use UP/Down navigation key to adjust the input values or not)
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTimeSetEnableAdjustValueByNaviUpDown
(
    IWidget                 *pWDGTime,
    boolean                 bAdjustValue
)
{
    return WdgCommonSetProperty(pWDGTime, PROP_FORMATINPUT_WDG_ENABLE_ADJUST_VALUE_BY_NAVI_UP_DOWN, (u32)bAdjustValue);
}

/** WdgTimeSetEnableSecondField
* @brief        Allow to show second field.
*
* @param[in]    pWDGTime          The Time widget which want to be set
* @param[in]    bSecondField      TRUE/FALSE (Enable second field or not)
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTimeSetEnableSecondField
(
    IWidget                 *pWDGTime,
    boolean                 bSecondField
)
{
    return WdgCommonSetProperty(pWDGTime, PROP_FORMATINPUT_WDG_ENABLE_SECOND_FIELD, (u32)bSecondField);
}

/** WdgTimeSetTimeperiodAmPm
* @brief        Set the time period (AM/PM).It's useful only when HourFormat(12-hour) is set to TRUE
*
* @param[in]    pWDGTime          The Time widget which want to be set
* @param[in]    eTimeperiodAmPm   The time period (AM/PM)
*
* @retval       None
*
*/
__INLINE void WdgTimeSetTimeperiodAmPm
(
    IWidget                 *pWDGTime,
    TimePeriod_e            eTimeperiodAmPm
)
{
    WdgCommonSetProperty(pWDGTime, PROP_FORMATINPUT_WDG_TIMEPERIOD_AM_PM, (u32)eTimeperiodAmPm);
}

/** WdgTimeSetHourFormat
* @brief        Use 12-hour(TRUE) time format. The default format is 24-hour(FALSE).
*
* @param[in]    pWDGTime          The Time widget which want to be set
* @param[in]    bHourFormat       TRUE/FALSE (Hour format is 12-hour or not)
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTimeSetHourFormat
(
    IWidget                 *pWDGTime,
    boolean                 bHourFormat
)
{
    return WdgCommonSetProperty(pWDGTime, PROP_FORMATINPUT_WDG_12HOURFORMAT, (u32)bHourFormat);
}

/** WdgTimeSetFGColor
* @brief        Set the text color(not highlight text)
*
* @param[in]    pWDGTime          The Time widget which want to be set
* @param[in]    nFGColor          The widget foreground color which will be set to the Time widget
*
* @retval       None
*
*/
__INLINE void WdgTimeSetFGColor
(
    IWidget                 *pWDGTime,
    RGBColor_t              nFGColor
)
{
    WdgCommonSetProperty(pWDGTime, PROP_WDG_FG_COLOR, (u32)nFGColor);
}

/** WdgTimeSetHighlightTextColor
* @brief        Set the text color of editing field
*
* @param[in]    pWDGTime        The Time widget which want to be set
* @param[in]    nTextColor      The text color of editing field
*
* @retval       None
*
*/
__INLINE void WdgTimeSetHighlightTextColor
(
    IWidget                 *pWDGTime,
    RGBColor_t              nTextColor
)
{
    WdgCommonSetProperty(pWDGTime, PROP_FORMATINPUT_WDG_HIGHLIGHT_TEXT_COLOR, (u32)nTextColor);
}

/** WdgTimeSetHighlightBGColor
* @brief        Set the background color of editing field
*
* @param[in]    pWDGTime          The Time widget which want to be set
* @param[in]    nBGColor          The background color of editing field
*
* @retval       None
*
*/
__INLINE void WdgTimeSetHighlightBGColor
(
    IWidget                 *pWDGTime,
    RGBColor_t              nBGColor
)
{
    WdgCommonSetProperty(pWDGTime, PROP_FORMATINPUT_WDG_HIGHLIGHT_BG_COLOR, (u32)nBGColor);
}

/** WdgTimeSetAlignment
* @brief        Set Time widget alignment flag
*
* @param[in]    pWDGTime          The Time widget which want to be set
* @param[in]    eWdgAlignment     The widget alignment flag which will be set to the Time widget
*
* @retval       None
*
*/
__INLINE void WdgTimeSetAlignment
(
    IWidget                 *pWDGTime,
    WdgAlignment_e          eWdgAlignment
)
{
    WdgCommonSetProperty(pWDGTime, PROP_WDG_ALIGNMENT, (u32)eWdgAlignment);
}
/*=============================================================*/
/** WdgTimeGetTimeperiodAmPm
* @brief        Get the time period (AM/PM)
*
* @param[in]    pWDGTime          The Time widget which want to be get
*
* @return       The time period (AM/PM)
*
*/
TimePeriod_e WdgTimeGetTimeperiodAmPm
(
    IWidget                 *pWDGTime
);

/** WdgTimeGetTimeValue
* @brief        Get Time value
*
* @param[in]    pWDGTime          The Time widget which want to be get
* @param[out]   pTimeValue        Time value.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTimeGetTimeValue
(
    IWidget                 *pWDGTime,
    MAE_DateTime_t          *pTimeValue
)
{
    return WdgCommonGetProperty(pWDGTime, PROP_FORMATINPUT_WDG_TIME_VALUE, (u32*)pTimeValue);
}

/** WdgTimeGetFormateinputTextColor
* @brief        Get the text color
*
* @param[in]     pWDGTime        The Time widget which want to be get
* @param[out]    pTextColor      Font color of text that is not in the current edit field
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgTimeGetFormateinputTextColor
(
    IWidget                 *pWDGTime,
    RGBColor_t              *pTextColor
);

/** WdgTimeGetHighlightBGColor
* @brief        Get the background color of editing field
*
* @param[in]    pWDGTime          The Time widget which want to be get
* @param[out]   pBGColor          The background color of editing field
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTimeGetHighlightBGColor
(
    IWidget                 *pWDGTime,
    RGBColor_t              *pBGColor
)
{
    return WdgCommonGetProperty(pWDGTime, PROP_FORMATINPUT_WDG_HIGHLIGHT_BG_COLOR, (u32*)pBGColor);
}

/** WdgTimeGetHighlightTextColor
* @brief        Get the text color of editing field
*
* @param[in]     pWDGTime        The Time widget which want to be get
* @param[out]    pTextColor      The text color of editing field
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgTimeGetHighlightTextColor
(
    IWidget                 *pWDGTime,
    RGBColor_t              *pTextColor
)
{
    return WdgCommonGetProperty(pWDGTime, PROP_FORMATINPUT_WDG_HIGHLIGHT_TEXT_COLOR, (u32*)pTextColor);
}
/*=============================================================*/
/** WdgTimeRegisterFieldAutoCorrectCb
* @brief        Register callback : For the format input widget, CB will be triggered, it keeps focused at original field after correcting the data???
*
* @param[in]    pWDGTime          The Time widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTimeRegisterFieldAutoCorrectCb
(
    IWidget                     *pWDGTime,
    PfnWdgTimeFieldAutoCorrect  pfn,
    void                        *pUserData
);

/** WdgTimeRegisterFocusChangeCb
* @brief        Register callback for changing focused item; CB will be triggered if focused item is changed
*
* @param[in]    pWDGTime          The Time widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTimeRegisterFocusChangeCb
(
    IWidget                 *pWDGTime,
    PfnWdgTimeFocusChange   pfn,
    void                    *pUserData
);

/** WdgTimeRegisterTimeAMPMChangeCb
* @brief        Register callback : For the format input widget, CB will be triggered when the AM/PM is changed.
*
* @param[in]    pWDGTime          The Time widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTimeRegisterTimeAMPMChangeCb
(
    IWidget                     *pWDGTime,
    PfnWdgTimeTimeAMPMChange    pfn,
    void                        *pUserData
);

/** WdgTimeRegisterFormatinputDataChangeCb
* @brief        Register data change callback; CB will be triggered while data is changed by the format input widget.
*
* @param[in]    pWDGTime          The Time widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTimeRegisterFormatinputDataChangeCb
(
    IWidget                                 *pWDGTime,
    PfnWdgTimeWidgetFormatinputDataChange   pfn,
    void                                    *pUserData
);

/** WdgTimeDeregisterFieldAutoCorrectCb
* @brief        Deregister PfnWdgTimeFieldAutoCorrect callback
*
* @param[in]    pWDGTime          The Time widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTimeDeregisterFieldAutoCorrectCb
(
    IWidget                     *pWDGTime,
    PfnWdgTimeFieldAutoCorrect  pfn,
    void                        *pUserData
);

/** WdgTimeDeregisterFocusChangeCb
* @brief        Deregister callback for changing focused item
*
* @param[in]    pWDGTime          The Time widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTimeDeregisterFocusChangeCb
(
    IWidget                 *pWDGTime,
    PfnWdgTimeFocusChange   pfn,
    void                    *pUserData
);

/** WdgTimeDeregisterTimeAMPMChangeCb
* @brief        Deregister PfnWdgTimeTimeAMPMChange callback
*
* @param[in]    pWDGTime          The Time widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTimeDeregisterTimeAMPMChangeCb
(
    IWidget                     *pWDGTime,
    PfnWdgTimeTimeAMPMChange    pfn,
    void                        *pUserData
);

/** WdgTimeDeregisterFormatinputDataChangeCb
* @brief        Deregister data change callback
*
* @param[in]    pWDGTime          The Time widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTimeDeregisterFormatinputDataChangeCb
(
    IWidget                                 *pWDGTime,
    PfnWdgTimeWidgetFormatinputDataChange   pfn,
    void                                    *pUserData
);


/** WdgTimeSetDisableCheckHour
* @brief        Set disable the hour check, default is enable
*				     If disable the check, hour can larger than 24
*
* @param[in]    pWdgTime         The Time widget
* @param[in]    bDisable         TRUE:Disable   FALSE:Enable
* @retval       none
*
*/
void WdgTimeSetDisableCheckHour(IWidget *pWdgTime, boolean bDisable);

#endif //__MMI_WDG_TIME_H__
