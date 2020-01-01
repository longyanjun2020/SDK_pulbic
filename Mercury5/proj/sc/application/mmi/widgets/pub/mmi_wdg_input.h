/**
 * @file    mmi_wdg_input.h
 * @brief   This file defines the interface of input widget.
 *
 *     Input Widget provides not only Date/Time/IP those fixed format of input methods,
 *     but also provides other input methods. For example, when entering PIN, or editing
 *     SMS, phone numbers, names of persons, etc., you can use Input Widget. Input
 *     Widget also provides a multiplicity of input methods, including the keyboard,
 *     soft keyboard and handwriting input. There are many options can be set in Input
 *     widget, such as display layout, insert symbol, and so on.
 *
 */

#ifndef __MMI_WDG_INPUT_H__
#define __MMI_WDG_INPUT_H__
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_retcode.h"
#include "mmi_mae_window.h"
#include "mmi_mae_langcode.h"

#include "mmi_mae_inputcontroller.h"
#include "mmi_wdg_common_interface.h"
/*=============================================================*/
// type and define
/*=============================================================*/

typedef struct{
	u32 nWordPos;
	u16 *pOutY;
}WordInfo_t;

/** sCurPosByTSXY
*
* @brief    nNewCursorPos:     new cursor position
*           nPosX_TS:
*           nPosY_TS:
*
*/
typedef struct
{
	u32 nNewCursorPos;
	u32 nPosX_TS;
	u32 nPosY_TS;
} sCurPosByTSXY;

typedef struct 
{
	u32 nLen;
	u32 *pColorAry;
} ColorAry_t;

/** SinglelineDisplayInfo
*
* @brief    nFirstDispCharinDispStr_Offset:     new cursor position
*           nFirstDispCharisDispStr_LeftPos:
*
*/
typedef struct{
    u32 nFirstDispCharinDispStr_Offset;
	u32 nFirstDispCharisDispStr_LeftPos;
}SinglelineDisplayInfo;

#define INPUT_BORDER_SIZE MAKE_BORDER_SIZE(1,1,1,1)
enum
{
	SKBOARD_DISABLE = 0,	/* The softkeyboard will be disabled. */
	SKBOARD_ENABLE,			/* The softkeyboard will be enableed. */
	SKBOARD_DEFAULT			/* The softkeyboard enable/disable will depend on configure service. */
};
typedef u8 SkBoard_e;

/** WdgInputConfigData_t
*
* @brief    bNeedIME            If you need to change input method from Title, plz set TRUE or set FALSE.
*           eSkBoard            Input need Softkey Board or Not or Default
*
*/
typedef struct
{
    boolean                 bNeedIME;
    SkBoard_e               eSkBoard;
}WdgInputConfigData_t;

/** PfnWdgInputWidgetSelectChange
* @brief      CB register by "WdgInputRegisterSelectChangeCb"
*             and will be triggered when text selection range changed.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pTextInfo         The info can get when text selection range changed., refer to TextInfo
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgInputWidgetSelectChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);

/** PfnWdgInputWidgetTextChange
* @brief      CB register by "WdgInputRegisterTextChangeCb"
*             and will be triggered when text text changed..
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pTextInfo         The info can get when text text changed.., refer to TextInfo
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgInputWidgetTextChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);

/** PfnWdgInputWidgetUnderlineChange
* @brief      CB register by "WdgInputRegisterUnderlineChangeCb"
*             and will be triggered when text underline range changed.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pTextInfo         The info can get when text underline range changed., refer to TextInfo
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgInputWidgetUnderlineChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);

/** PfnWdgInputWidgetCursorChange
* @brief      CB register by "WdgInputRegisterCursorChangeCb"
*             and will be triggered when text current cursor position changed.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pTextInfo         The info can get when current cursor position changed, refer to TextInfo
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgInputWidgetCursorChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);

/** PfnWdgInputScrollChange
* @brief      CB register by "WdgInputRegisterScrollChangeCb"
*             and will be triggered if scroll visible range changed
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pScrollData       The info can get when Scroll changed, refer to ScrollData_t
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgInputScrollChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, ScrollData_t *pScrollData, IWidget *pWidget);

/** PfnWdgInputMultilineDisplayChange
* @brief      CB register by "WdgInputRegisterMultilineDisplayChangeCb"
*             and will be triggered when multi-line display redraws.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pMultiLineData    The info can get when multi-line display changed, refer to MultiLineViewData_t
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgInputMultilineDisplayChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, MultiLineViewData_t *pMultiLineData, IWidget *pWidget);

/** PfnWdgInputFocusChange
* @brief      CB register by "WdgInputRegisterFocusChangeCb"
*             and will be trigger when the focus of widget is changed
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  bFocus            Indicate focus or not
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgInputFocusChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bFocus, IWidget *pWidget);

/** PfnWdgInputScrollChangeByTouch
* @brief      CB register by "WdgInputRegisterScrollChangeByTouchCb"
*             and will be triggered when user press scroll bar and changed the position of scroll indicator.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nReserve          Reserved parameter
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgInputScrollChangeByTouch) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);

/** PfnWdgInputTitleVisibleChange
* @brief      CB register by "WdgInputRegisterTitleVisibleChangeCb"
*             and for handling change the title.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  TitleElmntVisibleChangeData_t          The info can get when visible title changed, refer to TitleElmntVisibleChangeData_t
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgInputTitleVisibleChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TitleElmntVisibleChangeData_t *TitleElmntVisibleChangeData_t, IWidget *pWidget);

/** PfnWdgInputSKBVisibleChange
* @brief      CB register by "WdgInputRegisterSKBVisibleChangeCb"
*             and for handling change the SKB.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  boolean           The bVisible indicate SKB is visible or not
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgInputSKBVisibleChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bVisible, IWidget *pWidget);

/** PfnWdgInputSMSLengthEncoding
* @brief      CB register by "WdgInputRegisterSMSLengthEncodingCb"
*             and will be triggered when SMS Length Encoding changes.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pSMSData          The info can get when SMS Length Encoding changes, refer to SMSData_t
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgInputSMSLengthEncoding) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, SMSData_t *pSMSData, IWidget *pWidget);

/** PfnWdgInputDTMFKeyIn
* @brief      CB register by "WdgInputRegisterDTMFKeyInCb"
*             and will be triggered when DTMF mode changes.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pDTMFData         The info can get when DTMF mode changed, refer to pDTMFData
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgInputDTMFKeyIn) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, DTMFData_t *pDTMFData, IWidget *pWidget);

/** PfnWdgInputTouchPosition
* @brief      CB register by "WdgInputRegisterTouchPositionCb"
*             and will be triggered when getting the touched cursor position.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nTouchedPos       The touched position.
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgInputTouchPosition) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nTouchedPos, IWidget *pWidget);

/** PfnWdgInputExceedLimitedLen
* @brief      CB register by "WdgInputRegisterExceedLimitedLenCb"
*             and will be triggered when input limited length is exceeded.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nReserve          Reserved parameter
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgInputExceedLimitedLen) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);

/*=============================================================*/
// functions
/*=============================================================*/
/** WdgInputCreateForWnd
* @brief        Create Input widget and set size for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
* @param[in]    pData               Config Data for input
*                                   a, bNeedIME     Input need IME or Not
*                                   b, bSkBoard     Input need Softkey Board or Not
*
* @retval       The pointer of Input    Success.
* @retval       NULL                    Failed.
*
*/
__SLDPM_FREE__ IWidget* WdgInputCreateForWnd
(
    HWIN             hWin,
    Pos_t                   *pPos,
    WidgetSize_t            *pSize,
    u16                     nWidgetID,
    WdgInputConfigData_t    *pData
);

/** WdgInputCreate
* @brief        Create Input widget
*
* @retval       The pointer of Input   Success.
* @retval       NULL                    Failed.
*
*/
__SLDPM_FREE__ IWidget* WdgInputCreate
(
    void
);

/** WdgInputSetText
* @brief        Set MAE_WChar string to the widget.
*
* @param[in]    pWDGInput         Pointer to the Input widget
* @param[in]    pWChar            Pointer to MAE_WChar string.
* @param[in]    bCursorAtEnd      Input blink cursor will be set at begin/end of string.
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetText
(
    IWidget                 *pWDGInput,
    MAE_WChar               *pWChar,
	boolean                 bCursorAtEnd
);

/** WdgInputSetTextById
* @brief        Set MAE_WChar string to the widget By Text Id.
*
* @param[in]    pWDGInput         Pointer to the Input widget
* @param[in]    nTextID           Id of the text label
*
* @retval       void
*/
__SLDPM_FREE__ void WdgInputSetTextById
(
    IWidget                 *pWDGInput,
    u32                     nTextID
);

/** WdgInputSetMultiline
* @brief        Enable/Disable multi-line
*
* @param[in]    pWDGInput         Pointer to the Input widget
* @param[in]    bMultiline        boolean of multi-line
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetMultiline
(
    IWidget                 *pWDGInput,
    boolean                 bMultiline
);
/** WdgInputSetPasswordStyle
* @brief        Enable/Disable password style
*
* @param[in]    pWDGInput         Pointer to the Input widget
* @param[in]    bPasswordStyle    password style
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetPasswordStyle
(
    IWidget                 *pWDGInput,
    boolean                 bPasswordStyle
);

/** WdgInputSetFontCategory
* @brief        Set font category
*
* @param[in]    pWDGInput        Pointer to the Input widget
* @param[in]    nFontCategory        font category, reference to mae_font_base.h
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetFontCategory
(
    IWidget                 *pWDGInput,
    FontCategory_t          nFontCategory
);

/** WdgInputSetVectorFontSize
* @brief        Set Vector font size
*
* @param[in]    pWDGInput        Pointer to the Input widget
* @param[in]    nFontCategory        font size, reference to mae_font_base.h
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetVectorFontSize
(
    IWidget                 *pWDGInput,
    u32						nSize
);


/** WdgInputSetFontType
* @brief        Set font type
*
* @param[in]    pWDGInput         Pointer to the Input widget
* @param[in]    nFontType         font type, reference to mae_font_base.h
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetFontType
(
    IWidget                 *pWDGInput,
    FontType_t              nFontType
);

/** WdgInputSetTextColor
* @brief        Set text color
*
* @param[in]    pWDGInput         Pointer to the Input widget
* @param[in]    nTextColor        Text color, reference to mmi_mae_graphic.h
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetTextColor
(
    IWidget                 *pWDGInput,
    RGBColor_t              nTextColor
);

/** WdgInputSetInactiveTextColor
* @brief        Set displayed text color when the input widget is unfocused
*
* @param[in]    pWDGInput         Pointer to the Input widget
* @param[in]    nTextColor        Text color, reference to mmi_mae_graphic.h
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetInactiveTextColor
(
    IWidget                 *pWDGInput,
    RGBColor_t              nTextColor
);

/** WdgInputSetHighlightTextColor
* @brief        Set highlight text color
*
* @param[in]    pWDGInput              Pointer to the Input widget
* @param[in]    nHighlightTextColor    The Color of Text when highlight mode is set, reference to mmi_mae_graphic.h
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetHighlightTextColor
(
    IWidget                 *pWDGInput,
    RGBColor_t              nHighlightTextColor
);

/** WdgInputSetHighlightBGColor
* @brief        Set highlight BG color
*
* @param[in]    pWDGInput             Pointer to the Input widget
* @param[in]    nHighlightBGColor     The Background color when highlight mode is set, reference to mmi_mae_graphic.h
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetHighlightBGColor
(
    IWidget                 *pWDGInput,
    RGBColor_t              nHighlightBGColor
);

/** WdgInputSetCursorColor
* @brief        Set cursor color
*
* @param[in]    pWDGInput         Pointer to the Input widget
* @param[in]    nCursorColor      The Cursor Color, reference to mmi_mae_graphic.h
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetCursorColor
(
    IWidget                 *pWDGInput,
    RGBColor_t              nCursorColor
);

/** WdgInputSetRandomColorText
* @brief        Use random color to draw text or not
*
* @param[in]    pWDGInput             Pointer to the Input widget
* @param[in]    bIsRandomColorText    Use random color for text if bIsRandomColorText is TRUE.
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetRandomColorText
(
    IWidget                 *pWDGInput,
    boolean                 bIsRandomColorText
);

/** WdgInputSetRandomColorArray
* @brief        Set random color array for random color text
*
* @param[in]    pWDGInput         Pointer to the Input widget
* @param[in]    pColorAry         Pointer of random color array
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetRandomColorArray
(
    IWidget                 *pWDGInput,
    ColorAry_t              *pColorAry
);

/** WdgInputSetLineGap
* @brief        set line gap
*
* @param[in]    pWDGInput         Pointer to the Input widget
* @param[in]    nLineGap          the line gap value in pixel
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetLineGap
(
    IWidget                 *pWDGInput,
    u32                     nLineGap
);

/** WdgInputSetHideCursor
* @brief        Hide the cursor on the input widget or not
*
* @param[in]    pWDGInput         Pointer to the Input widget
* @param[in]    bIsHideCursor     Hide Cursor if bIsHideCursor is TRUE.
*
* @retval       void
*
*/

__SLDPM_FREE__ void WdgInputSetHideCursor
(
    IWidget                 *pWDGInput,
    boolean                 bIsHideCursor
);

/** WdgInputSetShowBorderWhenLoseFocus
* @brief        Enable/Disable show border when lose focus
*
* @param[in]    pWDGInput         Pointer to the Input widget
* @param[in]    bShowBorderWhenLoseFocus    the boolean of ShowBorderWhenLoseFocus
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgInputSetShowBorderWhenLoseFocus
(
    IWidget                 *pWDGInput,
    boolean                 bShowBorderWhenLoseFocus
);

/** WdgInputSetDrawUnderline
* @brief        Enable/Disable draw underline
*
* @param[in]    pWDGInput         Pointer to the Input widget
* @param[in]    bDrawUnderline    The pointer of DrawUnderline
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetDrawUnderline
(
    IWidget                 *pWDGInput,
    boolean                 bDrawUnderline
);

/** WdgInputSetHandWritingEnable
* @brief        Set hand writing enable/disable
*
* @param[in]    pWDGInput                        The input widget which want to be set
* @param[in]    bHandWritingEnabled              input hand writing  enable/disable
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetHandWritingEnable
(
    IWidget                 *pWDGInput,
    boolean                 bHandWritingEnabled
);

/** WdgInputSetSoftKeyBoardEnable
* @brief       Set the ability to input by soft keyboard
*
* @param[in]    pWDGInput                        The input widget which want to be set
* @param[in]    bSoftKeyBoardEnable              bSoftKeyBoardEnable TRUE/FALSE (Enable/Disable soft keyboard)
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetSoftKeyBoardEnable
(
    IWidget                 *pWDGInput,
    boolean                 bSoftKeyBoardEnable
);

/** WdgInputSetSoftKeyBoardAlwaysOn
* @brief       Set soft keyboard always on
*
* @param[in]    pWDGInput                      The input widget which want to be set
* @param[in]    bSoftKeyBoardAlwaysOn          TRUE/FALSE (Soft keyboard is always on or not)
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetSoftKeyBoardAlwaysOn
(
    IWidget                 *pWDGInput,
    boolean                 bSoftKeyBoardAlwaysOn
);

/** WdgInputSetSoftKeyBoardVisiableWhileInactive
* @brief       Set softkey-board was visible while Input widget is NOT focus
*
* @param[in]    pWDGInput                      The input widget which want to be set
* @param[in]    bSoftKeyBoardAlwaysOn          TRUE/FALSE (Soft keyboard visible while input widget inactive)
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetSoftKeyBoardVisiableWhileInactive
(
    IWidget                 *pWDGInput,
    boolean                 bSoftKeyBoardVisibleWhileInactive
);

/** WdgInputSetCursorPos
* @brief       Set cursor's position
*
* @param[in]    pWDGInput    The input widget which want to be set
* @param[in]    nPos         cursor's position which will be set to the editor
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetCursorPos
(
    IWidget                 *pWDGInput,
    u32                     nPos
);

/** WdgInputSetSelection
* @brief       Set the selected text on the input widget
*
* @param[in]    pWDGInput            The input widget which want to be set
* @param[in]    pInputSelection      The Selected text (nStart, nEnd)
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetSelection
(
    IWidget                 *pWDGInput,
    InputSelection_t        *pInputSelection
);

/** WdgInputSetIgnoreSelectWhenRecalculateDisplines
* @brief       Set to ignore select when recalculate display lines
*
* @param[in]    pWDGInput            The input widget which want to be set
* @param[in]    bIgnore				  TRUE/FALSE
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetIgnoreSelectWhenRecalculateDisplines
(
    IWidget                 *pWDGInput,
    boolean                 bIgnore
);

/** WdgInputSetDisableSymbolTable
* @brief       Set symbol table disable
*
* @param[in]    pWDGInput                        The input widget which want to be set
* @param[in]    bSymbolTableDisable              (TRUE/FALSE ) [disable/enable] symbol tabel which will be set to the editor
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetDisableSymbolTable
(
    IWidget                 *pWDGInput,
    boolean                 bSymbolTableDisable
);

/** WdgInputSetEnableMarkFuctions
* @brief       Set mark functions enable
*
* @param[in]    pWDGInput            The input widget which want to be set
* @param[in]    bMarkModeEnable      (TRUE/FALSE ) [enable/disable] mark functions which will be set to input widget
*
*/
__SLDPM_FREE__ void WdgInputSetEnableMarkFuctions
(
    IWidget                 *pWDGInput,
    boolean                 bMarkModeEnable
);

/** WdgInputSetDisableSwitchInputMode
* @brief       Can not switch input mode
*
* @param[in]    pWDGInput                              The input widget which want to be set
* @param[in]    bDisableSwitchInputMethod              (TRUE/FALSE ) [disable/enable] switch input mode which will be set to input widget
*
* @retval       void
*/
__SLDPM_FREE__ void WdgInputSetDisableSwitchInputMode
(
    IWidget                 *pWDGInput,
    boolean                 bDisableSwitchInputMethod
);

/** WdgInputSetEnableFileNameFilterOnSkBoard
* @brief       Set the file name filer Enable/Disable on the softkeyboard.
*			If bIsFileName is TRUE, the invalidate characters on file name won't be displayed on the softkeyboard.
*
* @param[in]    pWDGInput    The input widget which want to be set
* @param[in]    bIsFileName  File name or not for SKB restriction which will be set to input widget
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetEnableFileNameFilterOnSkBoard
(
    IWidget                 *pWDGInput,
    boolean                 bIsFileName
);

/** WdgInputSetChineseInputOff
* @brief       Off Chinese input
*
* @param[in]    pWDGInput                     The input widget which want to be set
* @param[in]    bChinsesInputOff              TRUE : turn off  Chinese input which will be set to input widget
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetChineseInputOff
(
    IWidget                 *pWDGInput,
    boolean                 bChinsesInputOff
);

/** WdgInputSetSmartInputOff
* @brief       disable smart input
*
* @param[in]    pWDGInput                       The input widget which want to be set
* @param[in]    bSmartInputDisable              (TRUE/FALSE ) [disable/enable] smart input which will be set to input widget
*
* @retval       void
*/
__SLDPM_FREE__ void WdgInputSetSmartInputOff
(
    IWidget                 *pWDGInput,
    boolean                 bSmartInputDisable
);

/** WdgInputSetLineFeedDisable
* @brief       set line feed disable
*			If bLineFeedDisable is TRUE, the line feed character on the softkeyboard won't be displayed.
*
* @param[in]    pWDGInput                       The input widget which want to be set
* @param[in]    bLineFeedDisable               (TRUE/FALSE ) [disable/enable] line feed which will be set to input widget
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetLineFeedDisable
(
    IWidget                 *pWDGInput,
    boolean                 bLineFeedDisable
);

/** WdgInputSetPauseSymbolDisableOnSkBoard
* @brief       set pause symbol Disable/Enable
*			If bPauseDisable is TRUE, the pause symbol won't be displayed on softkeyboard.
*
* @param[in]    pWDGInput                   The input widget which want to be set
* @param[in]    bPauseDisable               (TRUE/FALSE ) [disable/enable] pause which will be set to input widget
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetPauseSymbolDisableOnSkBoard
(
    IWidget                 *pWDGInput,
    boolean                 bPauseDisable
);

/** WdgInputSetMaxByteLength
* @brief       set the max byte length
*
* @param[in]    pWDGInput                   The input widget which want to be set
* @param[in]    nMaxInputBytes              The max byte  which will be set to input widget
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetMaxByteLength
(
    IWidget                 *pWDGInput,
    u32                      nMaxInputBytes
);

/** WdgInputSetSMSEncodeMaxWordCount
* @brief       set the max word count in Encode_SMS
*
* @param[in]    pWDGInput                   The input widget which want to be set
* @param[in]    nSMS7BitMaxWordCount        The max word count in 7bit SMS encoding which will be set to input widget
* @param[in]    nSMSUCS2MaxWordCount        The max word count in UCS2 SMS encoding which will be set to input widget
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetSMSEncodeMaxWordCount
(
    IWidget                 *pWDGInput,
    u32                      nSMS7BitMaxWordCount,
	u32                      nSMSUCS2MaxWordCount
);

/** WdgInputSetEncoding
* @brief       set input encode
*
* @param[in]    pWDGInput                    The input widget which want to be set
* @param[in]    eCurrentEncoding             Input encoding  which will be set to input widget
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetEncoding
(
    IWidget                 *pWDGInput,
    InputEnncode_e          eCurrentEncoding
);

/** WdgInputSetDTMFNotifyEnable
* @brief       enable DTMF notify
*
* @param[in]    pWDGInput                     The input widget which want to be set
* @param[in]    bSendDTMFNotify               (TRUE) [enable] DTMF notify which will be set to input widget
*
* @retval       void
*/
__SLDPM_FREE__ void WdgInputSetDTMFNotifyEnable
(
    IWidget                 *pWDGInput,
    boolean                 bSendDTMFNotify
);

/** WdgInputSetEntryOptionMenu
* @brief       entry option menu
*
* @param[in]    pWDGInput                 The input widget which want to be set
* @param[in]    pWDGOptMenu               option menu which will be set to input widget
*
* @retval       void
*/
void WdgInputSetEntryOptionMenu
(
    IWidget                 *pWDGInput,
    IWidget                 *pWDGOptMenu
);

/** WdgInputSetLaunchInputMenu
* @brief       Launch input menu
*
* @param[in]    pWDGInput                 The input widget which want to be set
* @param[in]    pWDGOptMenu               option menu which will be set to lauch input menu
*
* @retval       void
*
*/
MAE_Ret WdgInputSetLaunchInputMenu
(
    IWidget                 *pWDGInput,
    IWidget                 *pWDGOptMenu
);

/** WdgInputSetExitOptionMenu
* @brief      Exit option menu
*
* @param[in]    pWDGInput                    The input widget which want to be set
*
* @retval       void
*/
__SLDPM_FREE__ void WdgInputSetExitOptionMenu
(
    IWidget                 *pWDGInput
);

/** WdgInputSetCurrentInputLanguage
* @brief      Set current input language
*
* @param[in]    pWDGInput                The input widget which want to be set
* @param[in]    eCurrentInputLanguage    Current input language which will be set to input widget
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetCurrentInputLanguage
(
    IWidget                 *pWDGInput,
    MAE_LANG_e              eCurrentInputLanguage
);

/** WdgInputSetCurrentInputMode
* @brief      Set current input mode
*
* @param[in]    pWDGInput                  The input widget which want to be set
* @param[in]    eCurrentInputMode          Current input mode which will be set to input widget
*
* @retval       void
*/
__SLDPM_FREE__ void WdgInputSetCurrentInputMode
(
    IWidget                 *pWDGInput,
    u32                     nCurrentInputMode
);

/** WdgInputSetFirstKeyPress
* @brief        Set input first key press in dialing input mode
*
* @param[in]    pWDGInput         The input widget which want to be set
* @param[in]    nFirstKeyCode     The first key press(MAE_KEY ID) which will be set to the input controller
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetFirstKeyPress
(
    IWidget                 *pWDGInput,
    u32                     nFirstKeyCode
);

/** WdgInputSetInsertText
* @brief        Insert text to input widget
*
* @param[in]    pWDGInput         The input widget which want to be set
* @param[in]    pWStr             The  unicode of text which will be set to  input widget
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetInsertText
(
    IWidget                 *pWDGInput,
    MAE_WChar               *pWStr
);

/** WdgInputSetDecimalPointEnable
* @brief        Set input decimal point enable/disable in rate input mode
*			If bEnable is TRUE, the decimal point will be displayed on the softkeyboard.
*
* @param[in]    pWDGInput         The input widget which want to be set
* @param[in]    bEnable           input decimal point enable/disable
*
* @retval       void
*/
__SLDPM_FREE__ void WdgInputSetDecimalPointEnable
(
    IWidget                 *pWDGInput,
    boolean                 bEnable
);

/** WdgInputSetMaxlenAfterExponent
* @brief        Set max length after exponent in rate input mode
*
* @param[in]    pWDGInput                          The input widget which want to be set
* @param[in]    nMaxLenAfterExponent               The max length after exponent
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetMaxlenAfterExponent
(
    IWidget                 *pWDGInput,
    u8                      nMaxLenAfterExponent
);

/** WdgInputSetMaxlenAfterDecimalPoint
* @brief        Set max length after decimal point in rate input mode
*
* @param[in]    pWDGInput                            The input widget which want to be set
* @param[in]    nMaxLenAfterDecimalPoint             The max length after decimal point
*
* @retval       void
*/
__SLDPM_FREE__ void WdgInputSetMaxlenAfterDecimalPoint
(
    IWidget                 *pWDGInput,
    u8                       nMaxLenAfterDecimalPoint
);

/** WdgInputSetScrollUp
* @brief        Set scroll to up in VIEW ONLY input mode ( MAE_INPUTMODE_VIEWONLY)
*			If this function is called, the scroll bar will be move up.
*
* @param[in]    pWDGInput                                 The input widget which want to be set
*
* @retval       void
*/
__SLDPM_FREE__ void WdgInputSetScrollUp
(
    IWidget                 *pWDGInput
);

/** WdgInputSetScrollDown
* @brief        Set scroll to down in VIEW ONLY input mode ( MAE_INPUTMODE_VIEWONLY)
*			If this function is called, the scroll bar will be move down.
*
* @param[in]    pWDGInput                                 The input widget which want to be set
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetScrollDown
(
    IWidget                 *pWDGInput
);

/** WdgInputSetDialingShiftOldestChar
* @brief        Set input shift the oldest character enable/disable when overflow in dialing input mode
*			If bShiftOldest is TRUE, the oldest character will be shift out. (whne exceed the maxima length)
*
* @param[in]    pWDGInput         The input widget which want to be set
* @param[in]    bShiftOldest      Shift oldest character enable/disable
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetDialingShiftOldestChar
(
    IWidget                 *pWDGInput,
    boolean                 bShiftOldest
);

#ifdef __TOUCH_SCREEN_MMI__
/** WdgInputSetAddCustomToolBox
* @brief        add item into tool box
*
* @param[in]    pWDGInput             The input widget which want to be set
* @param[in]    ptCusToolBoxItem      The custom box item which will be set to the input widget.
*
* @retval        void
*
*/
__SLDPM_FREE__ void WdgInputSetAddCustomToolBox
(
    IWidget                 *pWDGInput,
    CusToolBoxItem_t        *ptCusToolBoxItem
);

/** WdgInputSeEnableTouchSliding
* @brief      set enable touch sliding or not
*
* @param[in]    pWDGInput             The input widget which want to be set
* @param[in]    bEnable				enable or not
*
* @retval        void
*
*/
__SLDPM_FREE__ void WdgInputSeEnableTouchSliding
(
    IWidget                 *pWDGInput,
    boolean				    bEnable
);
#endif

/** WdgInputSetModeMask
* @brief        Set input mode mask to input widget.
*			If the mask is set, the available input mode will be show.
*
* @param[in]    pWDGInput             The input widget which want to be set
* @param[in]    nAvailableInputModeMask      Available input mode mask which will be set to the input widget.
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetModeMask
(
    IWidget                 *pWDGInput,
    u32                     nAvailableInputModeMask
);

/** WdgInputSetFilter
* @brief        Set input filter to input widget.
*			If the filter is set, the filter mode will be disabled.
*
* @param[in]    pWDGInput             The input widget which want to be set
* @param[in]    nInputModeFilter      Input mode filter which will be set to the input widget.
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetFilter
(
    IWidget                 *pWDGInput,
    u32                     nInputModeFilter
);


/** WdgInputSetSelectionMode
* @brief        Set selection mode  to input widget
*			If bSelectionMode is TRUE, the selection ability will be enabled.
*
* @param[in]    pWDGInput            The input widget which want to be set
* @param[in]    bSelectionMode       selection mode   which will be set or not to the input widget.
*
* @retval       void
*
*/
void WdgInputSetSelectionMode
(
    IWidget                 *pWDGInput,
    boolean                  bSelectionMode
);

/** WdgInputSetFormatString
* @brief        Set Format String.
*
* @param[in]    pWDGInput       The input widget which want to be set
* @param[in]    pFormatStr      The format string pointer. This string must have null terminator.
*
* @retval       void
*
*/
__SLDPM_FREE__ void WdgInputSetFormatString
(
    IWidget                 *pWDGInput,
    MAE_WChar               *pFormatStr
);

/** WdgInputSetSwitchNegPos
* @brief        Set property if current value is negative, convert it to positive value.
*               For Rate input mode only.
*
* @param[in]    pWDGInput       The input widget which want to be set
* @param[in]    bEnable         Enable or Not
*
* @retval        void
*
*/
__SLDPM_FREE__ void WdgInputSetSwitchNegPos
(
    IWidget                 *pWDGInput,
    boolean                 bEnable
);

/** WdgInputSetUnderline
* @brief        This function sets the current underline start and end position for the underline range of text.
*
* @param[in]    pWDGInput       The input widget which want to be set.
* @param[in]    nStart          The start position of the underline text.
* @param[in]    nEnd            The end position of the underline text.
*
* @retval       MAE_RET_SUCCESS Success
* @retval       others          Failed
*
*/
MAE_Ret WdgInputSetUnderline
(
    IWidget                 *pWDGInput,
    u32                     nStart,
    u32                     nEnd
);

#ifdef __TOUCH_SCREEN_MMI__
#ifdef __IME_MMI_SOFTKEYBOARD__
#ifdef __IME_MMI_SOFTKEYBOARD_7COL_UI__
/** WdgInputSet7ColSoftKeyBoardNoSoftKey
* @brief       When use 7Col soft-keyboard, that the UI style don't have "SoftKey",  set this property, the 7Col soft-keyboard high-light widget can show correct.
*                  EX: When PhoneBook AP use  "__UI_STYLE_MMI_IFONE__", that UI don't have SoftKey, the 7Col soft-keyboard high-light widget can show correct.
* @param[in]    pWDGInput                      The input widget which want to be set
* @param[in]    bInputSet7ColSoftKeyBoardNoSoftKey  TRUE/FALSE ( 7Col Soft-keyboard have "SoftKey" or not)
*
* @retval       void
*
*/
__INLINE void WdgInputSet7ColSoftKeyBoardNoSoftKey
(
    IWidget                 *pWDGInput,
    boolean                 bInputSet7ColSoftKeyBoardNoSoftKey
)
{
    WdgCommonSetProperty(pWDGInput, PROP_INPUT_WDG_7COL_SOFTKEYBOARD_NO_SOFTKEY, (u32)bInputSet7ColSoftKeyBoardNoSoftKey);
}
#endif //__IME_MMI_SOFTKEYBOARD_7COL_UI__
#endif //__IME_MMI_SOFTKEYBOARD__
#endif //__TOUCH_SCREEN_MMI__

/** WdgInputReplaceSelectText
* @brief        This function replaces the current selection text with a new block of text.
*
* @param[in]    pWDGInput       The input widget which want to be set.
* @param[in]    pwText          The pointer to an MAE_WChar buffer for replacing the selection text.
* @param[in]    nLen            The string length of pwText, (in MAE_WChar *). (not include the zero teriminator)
*
* @retval       MAE_RET_SUCCESS Success
* @retval       others          Failed
*
*/
MAE_Ret WdgInputReplaceSelectText
(
    IWidget                 *pWDGInput,
    MAE_WChar               *pwText,
    u32                     nLen
);

__SLDPM_FREE__ MAE_Ret WdgInputGetCurrentInputMode
(
    IWidget                 *pWDGInput,
    u32                     *pCurrentInputMode
);

/** WdgInputGetScrollStep
* @brief        Get scroll step
*
* @param[in]     pWDGInput        Pointer to the Input widget
* @param[out]    pScrollStep      The pointer of Scroll Step
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgInputGetScrollStep
(
    IWidget                 *pWDGInput,
    ScrollStep_t            *pScrollStep
);

/** WdgInputGetCursorPosModifiedByTS
* @brief        Get the position of cursor  that is changed by touch screen.
*
* @param[in]     pWDGInput        Pointer to the Input widget
* @param[out]    pCurPosByTSXY    The pointer to the structure sCurPosByTSXY
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgInputGetCursorPosModifiedByTS
(
    IWidget                 *pWDGInput,
    sCurPosByTSXY           *pCurPosByTSXY
);

/** WdgInputGetTextInfo
* @brief        Get information about the text stored in the Widget, ex, length of text, string of text...
*
* @param[in]    pWDGInput         Pointer to the Input widget
* @param[out]   pTextInfo         Pointer to a TextInfo data structure, which contains length of text, string of text...
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputGetTextInfo
(
    IWidget                 *pWDGInput,
    TextInfo                *pTextInfo
);

/** WdgInputGetCursorPosAfterMoveUp
* @brief        Get the position of cursor after cursor is moved up
*
* @param[in]     pWDGInput       Pointer to the Input widget
* @param[out]    pNewPos         The pointer of cursor position
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgInputGetCursorPosAfterMoveUp
(
    IWidget             *pWDGInput,
    u32                 *pNewPos
);

/** WdgInputGetCursorPosAfterMoveDown
* @brief        Get the position of cursor after cursor is moved down
*
* @param[in]     pWDGInput         Pointer to the Input widget
* @param[out]    pNewPos           The pointer of cursor position
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgInputGetCursorPosAfterMoveDown
(
    IWidget             *pWDGInput,
    u32                 *pNewPos
);

/** WdgInputGetCaretXYPos
* @brief
*
* @param[in]     pWDGInput     Pointer to the Input widget
* @param[out]    pWPos         The pointer of structure WPos_t
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/

__SLDPM_FREE__ MAE_Ret WdgInputGetCaretXYPos
(
    IWidget                 *pWDGInput,
    WPos_t                  *pWPos
);

/** WdgInputGetFontCategory
* @brief        Get the category of font
*
* @param[in]     pWDGInput         Pointer to the Input widget
* @param[out]    pFontCategory         The pointer of Font Category
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgInputGetFontCategory
(
    IWidget                 *pWDGInput,
    FontCategory_t          *pFontCategory
);

/** WdgInputGetFontType
* @brief        Get the type of font
*
* @param[in]     pWDGInput         Pointer to the Input widget
* @param[out]    pFontType         The pointer of FontType
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgInputGetFontType
(
    IWidget                 *pWDGInput,
    FontType_t              *pFontType
);

/** WdgInputGetTextColor
* @brief        Get the color of text
*
* @param[in]     pWDGInput         Pointer to the Input widget
* @param[out]    pTextColor        The pointer of TextColor
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgInputGetTextColor
(
    IWidget                 *pWDGInput,
    RGBColor_t              *pTextColor
);

/** WdgInputGetInactiveTextColor
* @brief        Get the color of text when the input widget is unfocused
*
* @param[in]     pWDGInput         Pointer to the Input widget
* @param[out]    pTextColor        The pointer of TextColor
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgInputGetInactiveTextColor
(
    IWidget                 *pWDGInput,
    RGBColor_t              *pTextColor
);

/** WdgInputGetHighlightBGColor
* @brief        Get the color of highlight background
*
* @param[in]     pWDGInput         Pointer to the Input widget
* @param[out]    pHighlightBGColor The pointer of HighlightBGColor
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgInputGetHighlightBGColor
(
    IWidget                 *pWDGInput,
    RGBColor_t              *pHighlightBGColor
);

/** WdgInputGetHighlightTextColor
* @brief        Get the color of highlight text
*
* @param[in]     pWDGInput         Pointer to the Input widget
* @param[out]    pHighlightTextColor  The pointer of HighlightTextColor
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgInputGetHighlightTextColor
(
    IWidget                 *pWDGInput,
    RGBColor_t              *pHighlightTextColor
);

/** WdgInputGetMinInputCharLen
* @brief        Get Min Input Char Length; for what?? need to enhance comment
*
* @param[in]    pWDGInput               Pointer to the Input widget
* @param[out]   pMinInputCharLen        The less input length according to format string.
*
* @retval       MAE_RET_SUCCESS         Success
* @retval       others                  Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgInputGetMinInputCharLen
(
    IWidget                 *pWDGInput,
    u32                     *pMinInputCharLen
);

/** WdgInputGetSelection
* @brief        This function gets the current selection text.
*
* @param[in]    pWDGInput       The input widget which want to be set.
* @param[in]    pwText          The pointer to an MAE_WChar buffer will copy the selection text.
* @param[in]    nLen            The pwText buffer length, (in MAE_WChar *).
*
* @retval       MAE_RET_SUCCESS Success
* @retval       others          Failed
*
*/
MAE_Ret WdgInputGetSelection
(
    IWidget                 *pWDGInput,
    MAE_WChar               *pwText,
    u32                     nLen
);

/** WdgInputGetUnderlineText
* @brief        This function gets the current Underline text.
*
* @param[in]    pWDGInput       The input widget which want to be set.
* @param[in]    pwText          The pointer to an MAE_WChar buffer will copy the underline text.
* @param[in]    nLen            The pwText buffer length, (in MAE_WChar *).
*
* @retval       MAE_RET_SUCCESS Success
* @retval       others          Failed
*
*/
MAE_Ret WdgInputGetUnderlineText
(
    IWidget                 *pWDGInput,
    MAE_WChar               *pwText,
    u32                     nLen
);

/** WdgInputGetCursorPos
* @brief        This function gets current position in n-th word by x, y info.
*
* @param[in]    pWDGInput      The input widget which want to be set.
* @param[in]    nPosX          The x position info.
* @param[in]    nPosY          The y position info.
*
* @retval       u32            n-th word
*
*/
u32 WdgInputGetCursorPos
(
    IWidget                 *pWDGInput,
	u32                     nPosX,
	u32                     nPosY
);


/** WdgInputGetDisableSwitchInputMode
* @brief       Can not switch input mode
*
* @param[in]    pWDGInput                              The input widget which want to be set
* @param[in]    pDisableSwitchInputMethod              (TRUE/FALSE ) [disable/enable] switch input mode which will be set to input widget
*
* @retval       void
*/
MAE_Ret WdgInputGetDisableSwitchInputMode
(
    IWidget                 *pWDGInput,
    boolean                 *pDisableSwitchInputMethod
);


/** WdgInputRegisterSMSLengthEncodingCb
* @brief        Register SMS Length Encoding change callback.
*
* @param[in]    pWDGInput       The Input widget which want to set callback
* @param[in]    pfn             callback function
* @param[in]    pUserData        User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS Success
* @retval       others          Failed
*
*/
MAE_Ret WdgInputRegisterSMSLengthEncodingCb
(
    IWidget                         *pWDGInput,
    PfnWdgInputSMSLengthEncoding    pfn,
    void                            *pUserData
);

/** WdgInputRegisterSelectChangeCb
* @brief        Register selection range change callback; CB will be triggered if text selection range changed.
*
* @param[in]    pWDGInput       The Input widget which want to set callback
* @param[in]    pfn             callback function
* @param[in]    pUserData        User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS Success
* @retval       others          Failed
*
*/
MAE_Ret WdgInputRegisterSelectChangeCb
(
    IWidget                         *pWDGInput,
    PfnWdgInputWidgetSelectChange   pfn,
    void                            *pUserData
);

/** WdgInputRegisterTextChangeCb
* @brief        Register text change callback; CB will be triggered if text text changed.
*
* @param[in]    pWDGInput       The Input widget which want to set callback
* @param[in]    pfn             callback function
* @param[in]    pUserData        User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgInputRegisterTextChangeCb
(
    IWidget                     *pWDGInput,
    PfnWdgInputWidgetTextChange pfn,
    void                        *pUserData
);

/** WdgInputRegisterUnderlineChangeCb
* @brief        Register underline range change callback; CB will be triggered if text underline range changed.
*
* @param[in]    pWDGInput       The Input widget which want to set callback
* @param[in]    pfn             callback function
* @param[in]    pUserData        User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputRegisterUnderlineChangeCb
(
    IWidget                             *pWDGInput,
    PfnWdgInputWidgetUnderlineChange    pfn,
    void                                *pUserData
);

/** WdgInputRegisterCursorChangeCb
* @brief        Register current cursor position change callback; CB will be triggered if text current currsor position changed.
*
* @param[in]    pWDGInput       The Input widget which want to set callback
* @param[in]    pfn             callback function
* @param[in]    pUserData        User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputRegisterCursorChangeCb
(
    IWidget                         *pWDGInput,
    PfnWdgInputWidgetCursorChange   pfn,
    void                            *pUserData
);

/** WdgInputRegisterScrollChangeCb
* @brief        Register callback for handling scroll visible range change; CB will be triggered if scroll visible range changed
*
* @param[in]    pWDGInput         The text widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputRegisterScrollChangeCb
(
    IWidget                 *pWDGInput,
    PfnWdgInputScrollChange pfn,
    void                    *pUserData
);

/** WdgInputRegisterMultilineDisplayChangeCb
* @brief        Register callback : For formatinputwidget, CB will be triggered when Multi-line display redraw.
*
* @param[in]    pWDGInput         The text widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputRegisterMultilineDisplayChangeCb
(
    IWidget                             *pWDGInput,
    PfnWdgInputMultilineDisplayChange   pfn,
    void                                *pUserData
);

/** WdgInputRegisterFocusChangeCb
* @brief        Register callback for changing focus item; CB will be triggered if focus item changed
*
* @param[in]    pWDGInput         The text widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputRegisterFocusChangeCb
(
    IWidget                 *pWDGInput,
    PfnWdgInputFocusChange  pfn,
    void                    *pUserData
);

/** WdgInputRegisterScrollChangeByTouchCb
* @brief        Register callback : CB will be triggered when user press scroll bar and changed the position of scroll indicator.
*
* @param[in]    pWDGInput         The text widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputRegisterScrollChangeByTouchCb
(
    IWidget                         *pWDGInput,
    PfnWdgInputScrollChangeByTouch  pfn,
    void                            *pUserData
);

/** WdgInputRegisterTitleVisibleChangeCb
* @brief        Register callback : For handling change the title, dwParam : TitleElmntVisibleChangeData_t*???
*
* @param[in]    pWDGInput         The text widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputRegisterTitleVisibleChangeCb
(
    IWidget                         *pWDGInput,
    PfnWdgInputTitleVisibleChange   pfn,
    void                            *pUserData
);

/** WdgInputRegisterSKBVisibleChangeCb
* @brief        Register callback : For handling change the SKB, dwParam : boolean bVisible
*
* @param[in]    pWDGInput         The text widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputRegisterSKBVisibleChangeCb
(
    IWidget                         *pWDGInput,
	PfnWdgInputSKBVisibleChange     pfn,
    void                            *pUserData
);

/** WdgInputRegisterDTMFKeyInCb
* @brief        Register DTMF mode KeyIn callback.
*
* @param[in]    pWDGInput         The Input widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputRegisterDTMFKeyInCb
(
    IWidget                 *pWDGInput,
    PfnWdgInputDTMFKeyIn    pfn,
    void                    *pUserData
);

/** WdgInputRegisterTouchPositionCb
* @brief        Register callback for getting the touched cursor position.
*
* @param[in]    pWDGInput         The Input widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputRegisterTouchPositionCb
(
    IWidget                     *pWDGInput,
    PfnWdgInputTouchPosition    pfn,
    void                        *pUserData
);

/** WdgInputRegisterExceedLimitedLenCb
* @brief        Register callback for handling input limited length is exceeded.
*
* @param[in]    pWDGInput         The Input widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputRegisterExceedLimitedLenCb
(
    IWidget                         *pWDGInput,
    PfnWdgInputExceedLimitedLen     pfn,
    void                            *pUserData
);

/** WdgInputDeregisterSMSLengthEncodingCb
* @brief        Deregister SMS length encoding change callback
*
* @param[in]    pWDGInput       The Input widget which want to set callback
* @param[in]    pfn             callback function
* @param[in]    pUserData        User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgInputDeregisterSMSLengthEncodingCb
(
    IWidget                         *pWDGInput,
    PfnWdgInputSMSLengthEncoding    pfn,
    void                            *pUserData
);

/** WdgInputDeregisterSelectChangeCb
* @brief        Deregister selection range change callback; CB will be triggered if text selection range changed.
*
* @param[in]    pWDGInput       The Input widget which want to set callback
* @param[in]    pfn             callback function
* @param[in]    pUserData        User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputDeregisterSelectChangeCb
(
    IWidget                         *pWDGInput,
    PfnWdgInputWidgetSelectChange   pfn,
    void                            *pUserData
);

/** WdgInputDeregisterTextChangeCb
* @brief        Deregister text change callback; CB will be triggered if text text changed.
*
* @param[in]    pWDGInput       The Input widget which want to set callback
* @param[in]    pfn             callback function
* @param[in]    pUserData        User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgInputDeregisterTextChangeCb
(
    IWidget                     *pWDGInput,
    PfnWdgInputWidgetTextChange pfn,
    void                        *pUserData
);

/** WdgInputDeregisterUnderlineChangeCb
* @brief        Deregister underline range change callback; CB will be triggered if text underline range changed.
*
* @param[in]    pWDGInput       The Input widget which want to set callback
* @param[in]    pfn             callback function
* @param[in]    pUserData        User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputDeregisterUnderlineChangeCb
(
    IWidget                             *pWDGInput,
    PfnWdgInputWidgetUnderlineChange    pfn,
    void                                *pUserData
);

/** WdgInputDeregisterCursorChangeCb
* @brief        Deregister current cursor position change callback; CB will be triggered if text current currsor position changed.
*
* @param[in]    pWDGInput       The Input widget which want to set callback
* @param[in]    pfn             callback function
* @param[in]    pUserData        User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputDeregisterCursorChangeCb
(
    IWidget                         *pWDGInput,
    PfnWdgInputWidgetCursorChange   pfn,
    void                            *pUserData
);

/** WdgInputDeregisterScrollChangeCb
* @brief        Deregister callback for handling scroll visible range change; CB will be triggered if scroll visible range changed
*
* @param[in]    pWDGInput         The text widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputDeregisterScrollChangeCb
(
    IWidget                 *pWDGInput,
    PfnWdgInputScrollChange pfn,
    void                    *pUserData
);

/** WdgInputDeregisterMultilineDisplayChangeCb
* @brief        Deregister callback : For formatinputwidget, CB will be triggered when Multi-line display redraw.
*
* @param[in]    pWDGInput         The text widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputDeregisterMultilineDisplayChangeCb
(
    IWidget                             *pWDGInput,
    PfnWdgInputMultilineDisplayChange   pfn,
    void                                *pUserData
);

/** WdgInputDeregisterFocusChangeCb
* @brief        Deregister callback for changing focus item; CB will be triggered if focus item changed
*
* @param[in]    pWDGInput         The text widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputDeregisterFocusChangeCb
(
    IWidget                 *pWDGInput,
    PfnWdgInputFocusChange  pfn,
    void                    *pUserData
);

/** WdgInputDeregisterScrollChangeByTouchCb
* @brief        Deregister callback : CB will be triggered when user press scroll bar and changed the position of scroll indicator.
*
* @param[in]    pWDGInput         The text widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgInputDeregisterScrollChangeByTouchCb
(
    IWidget                         *pWDGInput,
    PfnWdgInputScrollChangeByTouch  pfn,
    void                            *pUserData
);

/** WdgInputDeregisterTitleVisibleChangeCb
* @brief        Deregister callback : For handling change the title, dwParam : TitleElmntVisibleChangeData_t*???
*
* @param[in]    pWDGInput         The text widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputDeregisterTitleVisibleChangeCb
(
    IWidget                         *pWDGInput,
    PfnWdgInputTitleVisibleChange   pfn,
    void                            *pUserData
);

/** WdgInputDeregisterSKBVisibleChangeCb
* @brief        Deregister callback : For handling change the SKB, dwParam : boolean bVisible
*
* @param[in]    pWDGInput         The text widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputDeregisterSKBVisibleChangeCb
(
    IWidget                         *pWDGInput,
    PfnWdgInputSKBVisibleChange     pfn,
    void                            *pUserData
);

/** WdgInputDeregisterDTMFKeyInCb
* @brief        Deregister DTMF mode KeyIn callback.
*
* @param[in]    pWDGInput         The Input widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputDeregisterDTMFKeyInCb
(
    IWidget                 *pWDGInput,
    PfnWdgInputDTMFKeyIn    pfn,
    void                    *pUserData
);

/** WdgInputDeregisterTouchPositionCb
* @brief        Deregister callback for getting the touched cursor position.
*
* @param[in]    pWDGInput         The Input widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputDeregisterTouchPositionCb
(
    IWidget                     *pWDGInput,
    PfnWdgInputTouchPosition    pfn,
    void                        *pUserData
);

/** WdgInputDeregisterExceedLimitedLenCb
* @brief        Deregister callback for handling input limited length is exceeded.
*
* @param[in]    pWDGInput         The Input widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgInputDeregisterExceedLimitedLenCb
(
    IWidget                         *pWDGInput,
    PfnWdgInputExceedLimitedLen     pfn,
    void                            *pUserData
);

/** InputWidgetGetPreferredSizeByCharPos
* @brief        Get the preferred size by specify length, It could be a substring
*
* @param[in]    pIWidget         The Input widget which want to get preferred size
* @param[in]    nCharPos         The position of the specify character, the length of substring
* @param[out]   pSize            The preferred size
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret InputWidgetGetPreferredSizeByCharPos(IWidget *pIWidget, u32 nCharPos, WidgetSize_t *pSize);

/** InputWidgetIsToggleInputModeHotKey
* @brief        query the mae_key is switch input method hot key or not
*
* @param[in]    pIWidget         The Input widget which want to get preferred size
* @param[in]    u32              The MAE KEY
*
* @retval       TRUE             The mae key is switch input method hot key
* @retval       others           The mae key is not switch input method hot key
*
*/
boolean InputWidgetIsToggleInputModeHotKey(IWidget *pIWidget, u32 nMaeKey);

MAE_Ret _InputWidget_GetWordDispY( IWidget *pWdg, WordInfo_t *WordInfo);

/** WdgInputGetLineGap
* @brief        Get the line gap of input widget
*
* @param[in]     pWDGInput         Pointer to the Input widget
* @param[out]   pLineGap            The pointer of LineGap
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgInputGetLineGap
(
    IWidget                 *pWDGInput,
    u32                     *pLineGap
);

/** WdgInputGetFontHeight
* @brief        Get the font height of input widget
*
* @param[in]     pWDGInput         Pointer to the Input widget
* @param[out]   pFontHeight        The pointer of FontHeight
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgInputGetFontHeight
(
    IWidget                 *pWDGInput,
    u32                     *pFontHeight
);

/** WdgInputGetWordDispY
* @brief        Get the word's pos Y of input widget
*
* @param[in]     pWDGInput         Pointer to the Input widget
* @param[in]     nWordPos           The word offset(begin index) in original full text
* @param[out]   pOutY                The pointer of word's pos Y
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgInputGetWordDispY
(
    IWidget                 *pWDGInput,
    u32                     nWordPos,
    u16                     *pOutY
);


/** WdgInputGetCurrentInputLanguage
* @brief      Get current input language
*
* @param[in]    pWDGInput                The input widget which want to be set
* @param[in]    pCurrentInputLanguage    Current input language which will be set to input widget
*
* @retval       void
*
*/
__SLDPM_FREE__ MAE_Ret WdgInputGetCurrentInputLanguage
(
    IWidget                 *pWDGInput,
    u32                     *pCurrentInputLanguage
);

#endif //__MMI_WDG_INPUT_H__
/*=============================================================*/
// end of file
