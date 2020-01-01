/**
*      TimerFormat Widget is a widget providing different kinds of time format display.
*      AP sets time-tick to TimerFormatWidget, TimerFormat Widget will
*      display time on specific layout Currently, the widget provide 4 layout:
*
*           (1) HH:MM:SS                ( 09:08:59 )
*          (2) HH:MM                ( 09:08 )
*          (3) MM:SS                ( 08:59 )
*          (4) HH:MM:SS.MS            ( 09:08:59.1)
*
*      APP can set property to change the following parameter:
*           - Format Lyaout        (4 kinds of Timer Layout)
*          - Width for digit and separater    ( Pixels for each digital and separater )
*          - Delimiter for separater
*/

#ifndef __MMI_WDG_TIMERFORMAT_H__
#define __MMI_WDG_TIMERFORMAT_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_window.h"
#include "mmi_wdg_common_interface.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_retcode.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/** TimerFomatData_t
*
* @brief    intNum:    
*           floatNum:   
*
*/
typedef struct{
	u32 intNum;
	u8 floatNum;
} TimerFomatData_t;

/** TimerTextFont_t
*
* @brief    fontSize:           font size
*           fontType:           font type
*           rgbTextColor:       common text color
*           rgbOutlineColor:    common text color
*
*/
typedef struct{
	u32 fontCat;       ///< font category
	u32 fontSize;       ///< font size
	u32 fontType;       ///< font type
	RGBColor_t rgbTextColor;      ///< common text color
	RGBColor_t rgbOutlineColor;      ///< common text color
}TimerTextFont_t;

/** TimerFormatInfo_t
*
* @brief    layout:           
*           digitWidth:       width for each digital
*           ThinWidth:        width for "1" digital
*           separatorWidth:   width for each separator
*           WSeparator:       delimiter to separate from such field and next field
*           WSeparatorExt:    last separator
*
*/
typedef struct{
	TimerFormatType_t layout;
	u32 digitWidth;							///< width for each digital
	u32 ThinWidth;							///< width for "1" digital
	u32 separatorWidth;						///< width for each separator
	MAE_WChar WSeparator;			///< delimiter to separate from such field and next field
	MAE_WChar WSeparatorExt;		///< last separator
}TimerFormatInfo_t;

#define DEFAULT_TIME_SEPARATER		0x003A           ///< ':'
#define DOT_TIME_SEPARATER				0x002E           ///< '.'

#define DEFAULT_WIDTH_DIGIT				10
#define DEFAULT_WIDTH_SEPARATOR	5

/** WdgTimerFormatSeparator_t
*
* @brief    nSeparatorWidth:    TimerFormat widget separator width in pixel       
*           wSeparator:         delimiter to separate from such field and next field
*           wSeparatorExt:      Last separator
*
*/
typedef struct
{
    u32            nSeparatorWidth;//TimerFormat widget separator width in pixel
    MAE_WChar      wSeparator;     //delimiter to separate from such field and next field
    MAE_WChar      wSeparatorExt;  //Last separator
}WdgTimerFormatSeparator_t;

/** PfnWdgTimerFormatWidgetDataChange
* @brief      CB register by "WdgTimerFormatRegisterDataChangeCb"
*             and will be trigger when the data of widget is changed
*
* @param[in]  pApplet         The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData        User data ap developer setting when register CB.
* @param[in]  nEvtCode        Widget Event Code, only useful for softkey event
* @param[in]  dwParam       The data word param (NOT use now)
* @param[in]  pIWidget        The widget instance
*
*/
typedef void (*PfnWdgTimerFormatWidgetDataChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);


/*=============================================================*/
// functions
/*=============================================================*/
/*=============================================================*/
/** WdgTimerFormatCreateForWnd
* @brief        Create TimerFormat widget and set size for Window
*
* @param[in]    pWndHdl         The window handle
* @param[in]    pPos            A pointer of widget position; can't be NULL.
* @param[in]    pSize           A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID       The widget unique ID of window
* @param[in]    eLayout         TimerFormat widget layout
*
* @retval       The pointer of TimerFormat          Success.
* @retval       NULL                                Failed.
*
*/
IWidget* WdgTimerFormatCreateForWnd
(
	HWIN hWin,
    Pos_t                  *pPos,
    WidgetSize_t           *pSize,
    u16                    nWidgetID,
    TimerFormatType_e      eLayout
);

/** WdgTimerFormatCommon_SetSeparator
* @brief        Set TimerFormat widget separator width, separator, and last separator
*
* @param[in]    pWDGTimerFormat     The TimerFormat widget which want to be set
* @param[in]    pSeparator          The pointer of WdgTimerFormatSeparator_t
*
* @retval       MAE_RET_SUCCESS     Success.
* @retval       MAE_RET_BAD_PARAM   Failed. pSeparator is NULL
* @retval       MAE_RET_FAILED      Failed.
*
*/
MAE_Ret WdgTimerFormatCommon_SetSeparator
(
    IWidget                          *pWDGTimerFormat,
    WdgTimerFormatSeparator_t        *pSeparator
);

/** WdgTimerFormatSetData
* @brief        Set display data for TimerFormat widget.
*               Specific data for TimerFormat widget.
*
* @param[in]    pWDGTimerFormat  Pointer to the TimerFormat widget
* @param[in]    pSpecData        Display data of TimerFormat Widget.
* @param[in]    pfFree           Free CB function for free data allocate by User while widget destroy.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
MAE_Ret WdgTimerFormatSetData
(
    IWidget                    *pWDGTimerFormat,
    TimerFomatData_t           *pSpecData,
    PfnDataFree                pfFree
);

/*=============================================================*/
/** WdgTimerFormatCreate
* @brief        Create TimerFormat widget
*
* @retval       The pointer of TimerFormat  Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgTimerFormatCreate
(
    void
);

/** WdgTimerFormatSetFormatLayout
* @brief        Set TimerFormat widget layout
*
* @param[in]    pWDGTimerFormat   The pointer of IWidget interface object
* @param[in]    eLayout           TimerFormat widget layout
*
* @retval       None
*
*/
void WdgTimerFormatSetFormatLayout
(
    IWidget                 *pWDGTimerFormat,
    TimerFormatType_e       eLayout
);

/** WdgTimerFormatSetSeparatorWidth
* @brief        Set width of digit and separator.
*
* @param[in]    pWDGTimerFormat    The pointer of IWidget interface object
* @param[in]    nSeparatorWidth    Separator width in pixel
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTimerFormatSetSeparatorWidth
(
    IWidget                 *pWDGTimerFormat,
    u32                     nSeparatorWidth
);

/** WdgTimerFormatSetSeparator
* @brief        Set the delimiter Width of separator
*
* @param[in]    pWDGTimerFormat   The pointer of IWidget interface object
* @param[in]    nSeparatorWidth        Delimiter width fields ":".
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTimerFormatSetSeparator
(
    IWidget                 *pWDGTimerFormat,
    u32                     nSeparatorWidth
);

/** WdgTimerFormatSetSeparatorExt
* @brief        Set last separator
*
* @param[in]    pWDGTimerFormat   The pointer of IWidget interface object
* @param[in]    nSeparatorWidth     Last separator ".".
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTimerFormatSetSeparatorExt
(
    IWidget                 *pWDGTimerFormat,
    u32                     nSeparatorWidth
);

/** WdgTimerFormatSetTextOutlineColor
* @brief        Set TimerFormat widget text outline color
*
* @param[in]    pWDGTimerFormat   The pointer of IWidget interface object
* @param[in]    nTextOutlineColor TimerFormat widget text outline color
*
* @retval       None
*
*/
void WdgTimerFormatSetTextOutlineColor
(
    IWidget                 *pWDGTimerFormat,
    RGBColor_t              nTextOutlineColor
);

/** WdgTimerFormatSetTextColor
* @brief    Set text color of widget.
*
* @param[in]    pWDGTimerFormat   The pointer of IWidget interface object
* @param[in]    TextColor        RGBColor_t value. User can make the value via MAKE_RGB(), MAKE_RGBA().
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTimerFormatSetTextColor
(
    IWidget                 *pWDGTimerFormat,
    RGBColor_t              TextColor
)
{
    return WdgCommonSetProperty(pWDGTimerFormat, PROP_WDG_TEXT_COLOR, (u32)TextColor);
}

/** WdgTimerFormatSetFontCategory
* @brief    Set font category of widget.
*
* @param[in]    pWDGTimerFormat   The pointer of IWidget interface object
* @param[in]    FC                    A kind of font category enum value, refer to mae_font.h
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*/
__INLINE MAE_Ret WdgTimerFormatSetFontCategory
(
    IWidget                 *pWDGTimerFormat,
    FontCategory_t          FC
)
{
    return WdgCommonSetProperty(pWDGTimerFormat, PROP_WDG_FONT_CATE, (u32)FC);
}

/** WdgTimerFormatSetAlignment
* @brief        Set TimerFormat widget alignment
*
* @param[in]    pWDGTimerFormat   The pointer of IWidget interface object
* @param[in]    eWdgAlignment     The alignment flag
*
* @retval       None
*
*/
void WdgTimerFormatSetAlignment
(
    IWidget                 *pWDGTimerFormat,
    WdgAlignment_e          eWdgAlignment
);

/** WdgTimerFormatRegisterDataChangeCb
* @brief        Register data change callback; CB will be triggered while data changed.
*
* @param[in]    pWDGTimerFormat   The TimerFormat widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTimerFormatRegisterDataChangeCb
(
    IWidget                                 *pWDGTimerFormat,
    PfnWdgTimerFormatWidgetDataChange    pfn,
    void                                    *pUserData
);

/** WdgTimerFormatDeregisterDataChangeCb
* @brief        Deregister data change callback
*
* @param[in]    pWDGTimerFormat   The TimerFormat widget which want to unregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTimerFormatDeregisterDataChangeCb
(
    IWidget                                 *pWDGTimerFormat,
    PfnWdgTimerFormatWidgetDataChange    pfn,
    void                                    *pUserData
);

#endif //__MMI_WDG_TIMERFORMAT_H__
/*=============================================================*/
// end of file
