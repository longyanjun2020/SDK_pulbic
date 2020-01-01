/**
* @file    mmi_wdg_text.h
* @version $Id: mmi_wdg_text.h 36292 2009-07-22 12:33:57Z bill.pan $
*
*   This file defines the interface of text-widget.
*   Text widget as the name implies, is a string of text display widget. Text widget
*   should be used with a Text Model. AP only needs to add string to Text model
*   to display, and Text widget is responsible for this string to be displayed.
*   The following figure, we set up a string "Hello world!" to the Text Model in Text
*   Widget. Text widget supports alignment (ex: ALIGN_H_LEFT) and layout
*   (ex: LAYOUT_MULTILINE). Of course, Text Widget can set the background
*   color, background image, Border, Padding, characters, character types (normal,
*   underline, out-line), color and outline color.
*
*     ex: Text widget
*     +-----------------------+
*     |  Hello world!         |   30      <-- A text widget with 80 pixels width and 30 pixels height.
*     |                       |  pixels        And the default alignment is Top / Left
*     +-----------------------+
*     |<--------------------->|
*              80 pixels
*
*/

#ifndef __MMI_WDG_TEXT_H__
#define __MMI_WDG_TEXT_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_mae_widget_custom.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_window.h"
#include "mmi_wdg_common_interface.h"
#include "mmi_mae_datamodel.h"

/*=============================================================*/
// type and define
/*=============================================================*/

//Text Layout
typedef enum e_Text_Layout
{
	LAYOUT_NONE        = 0x00,
	LAYOUT_MULTILINE   = 0x01,
	LAYOUT_BREAKONWORD = 0x02,   ///< only in effect while multiline turn on
	LAYOUT_ELLIPSIS    = 0x04,
	LAYOUT_E_TOTAL     = 0x08,
} TextLayout_e;
typedef u8 TextLayout_t;

//Text Alignment priority
typedef enum e_Text_AlignAndBreak	    //<==The Align priority only effect if the text layout is single line, if the layout is multi-line, the priority will always be TEXTWDG_BREAK_THEN_ALIGN
{
	TEXTWDG_BREAK_THEN_ALIGN   = 0x00,  //Break the line if the string it too long, and then align the text
	TEXTWDG_ALIGN_FIRST,	            //Align the text without consider if the string is too long. But still consider the return character.
   	                                    //<==If set Align First, text widget won't show the ellipsis

	TEXTWDG_ALIGN_PRIORITY_TOTAL,
} TextAlignAndBreak_e;

/// slide animation only active while multiline turn off and ellipsis turn off, right?
typedef enum e_Slide_Direction
{
    SLIDE_HORIZONTAL_START,
	SLIDE_TO_LEFT=SLIDE_HORIZONTAL_START,
	SLIDE_TO_RIGHT,
    SLIDE_TO_START,
    SLIDE_TO_END,
    SLIDE_HORIZONTAL_END=SLIDE_TO_END,
    SLIDE_VERTICAL_START,
	SLIDE_TO_UP=SLIDE_VERTICAL_START,
	SLIDE_TO_DOWN,
    SLIDE_VERTICAL_END=SLIDE_TO_DOWN,
	SLIDE_DIRECTION_E_TOTAL,
} SlideDirection_e;
typedef u8 SlideDirection_t;

typedef enum e_Slide_Style
{
    SLIDE_STYLE_IN_MASK=0x0F,
    SLIDE_STYLE_NO_SLIDE_IN=0x00,
    SLIDE_STYLE_SLIDE_IN=0x01,
    SLIDE_STYLE_OUT_MASK=0xF0,
    SLIDE_STYLE_NO_SLIDE_OUT=0x00,
    SLIDE_STYLE_SLIDE_OUT=0x10
} SlideStyle_e;
typedef u8 SlideStyle_t;

//The dwParam for EVT_VIEWMDL_SLIDE_CHANGE event
enum e_Slide_Status
{
	SLIDE_STATUS_E_NONE,
	SLIDE_STATUS_E_FINAL = 0x01, ///< if the PROP_TEXT_WDG_SLIDE_AUTO_REPEAT set as FALSE, the text widget view model will notify the final slide step
	SLIDE_STATUS_E_ON = 0x02,   ///< if the sliding was started by user set PROP_TEXT_WDG_SLIDE_ON_OFF as TRUE
	SLIDE_STATUS_E_OFF = 0x04,   ///< if the sliding was stoped, and slide final wasn't the stop cause.
	SLIDE_STATUS_E_DIRECTION_CHANGE = 0x08,///< when the PROP_TEXT_WDG_SLIDE_DIRECTION changed
	SLIDE_STATUS_E_RESET_OFFSET = 0x10	///< The slide offset has been reset to the default position (the position it start to slide)
                                        /// <The default position was determined by the alignment and the PROP_TEXT_WDG_SLIDE_STYLE (Slide_In) property
};

#define TEXTWDG_MIN_PREFERRED_WIDTH 30 ///< in pixels

/** TextFontInfo
*
* @brief    FontSize:               Font category
*           FontType:               Font type
*           bHighlight:           
*           TextColor:              text color
*           OutlineColor:           outline color
*           HighlightTextColor:     text color for highlight
*           HighlightOutlineColor:  outline color for highlight
*           HighlightBgColor:       background color for highlight
*           MinFontHeight:          minimum font height in pixels        
*
*/
typedef struct{
	u32 FontCat;         ///< Font category
	u32 FontSize;         ///< Font size
	u32 FontType;         ///< Font type
	boolean bHighlight;
	RGBColor_t TextColor;   ///< text color
	RGBColor_t OutlineColor;///< outline color
	RGBColor_t HighlightTextColor;    ///< text color for highlight
	RGBColor_t HighlightOutlineColor; ///< outline color for highlight
	RGBColor_t HighlightBgColor; ///< background color for highlight
	u32 MinFontHeight;    ///< minimum font height in pixels
} TextFontInfo;

/** TextSlideInfo
*
* @brief    nStepTime:          in msec.
*           nStepOffset:
*           nCurrentOffset:
*           nSlideEndOffset:
*           bAutoRepeat:
*           nLastStepTick:      The os tick of last step
*           nStepRemainTime:    The current step remain time
*           nSlideFlag:
*           nSlideStyle:
*           nDirection:   
*
*/
typedef struct {
	s32 nStepTime;            ///< in msec.
	s32 nStepOffset;
	s32 nCurrentOffset;
	s32 nSlideEndOffset;
	boolean bAutoRepeat;

    u32 nLastStepTick;      //The os tick of last step
    u32 nStepRemainTime;    //The current step remain time

	u8  nSlideFlag;
	u8  nSlideStyle;
	u8  nDirection;
} TextSlideInfo;

typedef u8 TextStyle_t;
enum {
    TEXT_STYLE_COMMON,
    TEXT_STYLE_LABEL,
    TEXT_STYLE_HIGHLIGHT
};

/** PfnWdgTextSlideChange
* @brief      CB register by "WdgTextRegisterSlideChangeCb"
*             and will be trigger when text slide changed.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nReserve          Reserve for enhancement in the future
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgTextSlideChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);

/** PfnWdgTextLinkTextClick
* @brief      CB register by "WdgTextRegisterLinkTextClickCb"
*             and will be trigger when link text(text on website) click.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nReserve          Reserve for enhancement in the future
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgTextLinkTextClick) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);

/** PfnWdgTextWidgetDataChange
* @brief      CB register by "WdgTextRegisterDataChangeCb"
*             and will be trigger when the data of widget is changed
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  dwParam       The data word param (NOT use now)
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgTextWidgetDataChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

/*=============================================================*/
// Interface functions
/*=============================================================*/
/** WdgTextCreateForWnd
* @brief        Text widget create function for Window
*
* @param[in]    hWin           The window handle
* @param[in]    pPos              A pointer of widget position; can't be NULL.
* @param[in]    pSize             A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID         The widget unique ID of window
* @param[in]    nTextStyle        The text style
*
* @retval       The pointer of Text             Success.
* @retval       NULL                            Failed.
*
*/
IWidget* WdgTextCreateForWnd
(
    HWIN             hWin,
    Pos_t                   *pPos,
    WidgetSize_t            *pSize,
    u16                     nWidgetID,
    TextStyle_t             nTextStyle
);

/** WdgTextCreate
* @brief        Create Text widget
*
* @param[in]    nTextStyle          The Text widget style
*
* @retval       The pointer of Text Success.
* @retval       NULL                Failed.
*
*/
IWidget* WdgTextCreate
(
    TextStyle_t nTextStyle
);
/*=============================================================*/
/** WdgTextSetData
* @brief        Set MAE_WChar string to the widget.
*               Specific data for TEXT_STYLE_COMMON, TEXT_STYLE_LABEL and TEXT_STYLE_HIGHLIGHTbitmap widget.
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    pWChar            Pointer to MAE_WChar string.
*                                 NULL means you want to clean the text.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTextSetData
(
    IWidget                 *pWDGText,
    MAE_WChar               *pWChar
);

/** WdgTextSetDataByID
* @brief        Set MAE_WChar string to the widget By Text Id. Only available when the specified string ID is in the resource file.
*               Specific data for TEXT_STYLE_COMMON, TEXT_STYLE_LABEL and TEXT_STYLE_HIGHLIGHTbitmap widget.
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    nTextID           Id of the text label
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTextSetDataByID
(
    IWidget                 *pWDGText,
    u32                     nTextID
);

/** WdgTextSetFontHeight
* @brief        Set the line height of the text widget.
*               The line height of the text widget will be the maximum value of the property or font height.
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    nMinLineHeight    The line height in pixel
*
* @retval       None
*
*/
__INLINE void WdgTextSetFontHeight
(
    IWidget                 *pWDGText,
    u32                     nMinLineHeight
)
{
    WdgCommonSetProperty(pWDGText, PROP_TEXT_WDG_MIN_LINE_HEIGHT, (u32)nMinLineHeight);
}

/** WdgTextSetFontType
* @brief    Set font type on widget.
*
* @param[in]    pWDGText      Pointer to the Text widget
* @param[in]    FT              A kind of font type value, refer to mae_font.h
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*/
__INLINE MAE_Ret WdgTextSetFontType
(
    IWidget                 *pWDGText,
    FontType_t              FT
)
{
    return WdgCommonSetProperty(pWDGText, PROP_WDG_FONT_TYPE, (u32)FT);
}

/** WdgTextSetFontCategory
* @brief    Set font category of widget.
*
* @param[in]    pWDGText      Pointer to the Text widget
* @param[in]    FC                    A kind of font category enum value, refer to mae_font.h
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*/
__INLINE MAE_Ret WdgTextSetFontCategory
(
    IWidget                 *pWDGText,
    FontCategory_t          FC
)
{
    return WdgCommonSetProperty(pWDGText, PROP_WDG_FONT_CATE, (u32)FC);
}

/** WdgTextSetTextColor
* @brief    Set text color of widget.
*
* @param[in]    pWDGObject       The pointer of IWidget interface object
* @param[in]    TextColor        RGBColor_t value. User can make the value via MAKE_RGB(), MAKE_RGBA().
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTextSetTextColor
(
    IWidget                 *pWDGObject,
    RGBColor_t              TextColor
)
{
    return WdgCommonSetProperty(pWDGObject, PROP_WDG_TEXT_COLOR, (u32)TextColor);
}

/** WdgTextSetTextOutlineColor
* @brief        Set text outline color
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    nTextOutlineColor The color of outline text
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTextSetTextOutlineColor
(
    IWidget                 *pWDGText,
    RGBColor_t              nTextOutlineColor
)
{
    return WdgCommonSetProperty(pWDGText, PROP_WDG_TEXT_OUTLINE_COLOR, (u32)nTextOutlineColor);
}

/** WdgTextSetTextOffset
* @brief        set the offset of the text
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    nOffest					The offset
*
* @retval       None
*
*/
__INLINE void WdgTextSetTextOffset
(
    IWidget                 *pWDGText,
    u32                 nOffest
)
{
    WdgCommonSetProperty(pWDGText, PROP_TEXT_WDG_TEXT_OFFSET, nOffest);
}

/** WdgTextSetHighlighted
* @brief        Highlight the text widget
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    bIsHighlighted    highlight the item widget
*
* @retval       None
*
*/
__INLINE void WdgTextSetHighlighted
(
    IWidget                 *pWDGText,
    boolean                 bIsHighlighted
)
{
    WdgCommonSetProperty(pWDGText, PROP_WDG_HIGHLIGHTED, (u32)bIsHighlighted);
}

/** WdgTextSetHighlightedWidth
* @brief        set the highlight width of the text widget
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    nWidth					The highlight width
*
* @retval       None
*
*/
__INLINE void WdgTextSetHighlightedWidth
(
    IWidget                 *pWDGText,
    u32                 nWidth
)
{
    WdgCommonSetProperty(pWDGText, PROP_TEXT_WDG_HIGHLIGHT_WIDTH, nWidth);
}

/** WdgTextSetHighlightedPosition
* @brief        set the highlight position of the text widget
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    nPos					The highlight position
*
* @retval       None
*
*/
__INLINE void WdgTextSetHighlightedPosition
(
    IWidget                 *pWDGText,
    s32                 nPos
)
{
    WdgCommonSetProperty(pWDGText, PROP_TEXT_WDG_HIGHLIGHT_POS, (u32)nPos);
}

/** WdgTextSetHighlightTextColor
* @brief    Set text color of widget.
*
* @param[in]    pWDGText      Pointer to the Text widget
* @param[in]    TextColor        RGBColor_t value. User can make the value via MAKE_RGB(), MAKE_RGBA().
*
*
*/
__INLINE void WdgTextSetHighlightTextColor
(
    IWidget                 *pWDGText,
    RGBColor_t              TextColor
)
{
    WdgCommonSetProperty(pWDGText, PROP_WDG_HIGHLIGHT_TEXT_COLOR, (u32)TextColor);
}

/** WdgTextSetHighlightTextOutlineColor
* @brief        Set text color when highlight mode is set.
*
* @param[in]    pWDGText                          Pointer to the Text widget
* @param[in]    nHighLightTextOutlineColor        The color of highlight text's outline
*
* @retval       None
*
*/
__INLINE void WdgTextSetHighlightTextOutlineColor
(
    IWidget                 *pWDGText,
    RGBColor_t              nHighLightTextOutlineColor
)
{
    WdgCommonSetProperty(pWDGText, PROP_WDG_HIGHLIGHT_TEXT_OUTLINE_COLOR, (u32)nHighLightTextOutlineColor);
}

/** WdgTextSetHighlightBGColor
* @brief        Set background color when highlight mode is set.
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    nHighLightBGColor The color of high BG
*
* @retval       None
*
*/
__INLINE void WdgTextSetHighlightBGColor
(
    IWidget                 *pWDGText,
    RGBColor_t              nHighLightBGColor
)
{
    WdgCommonSetProperty(pWDGText, PROP_WDG_HIGHLIGHT_BG_COLOR, (u32)nHighLightBGColor);
}

/** WdgTextSetSlideDirection
* @brief        Set slide direction
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    nSlideDirection   The sliding directions. ( up, down, left and right )
*
* @retval       None
*
*/
__INLINE void WdgTextSetSlideDirection
(
    IWidget                 *pWDGText,
    SlideDirection_e        nSlideDirection
)
{
    WdgCommonSetProperty(pWDGText, PROP_TEXT_WDG_SLIDE_DIRECTION, (u32)nSlideDirection);
}

/** WdgTextSetSlideStepOffset
* @brief        Set slide step offset. The shifting positions that text slide every time
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    nSlideStepOffset  The shifting positions that text slide every time.
*
* @retval       None
*
*/
__INLINE void WdgTextSetSlideStepOffset
(
    IWidget                 *pWDGText,
    s32                     nSlideStepOffset
)
{
    WdgCommonSetProperty(pWDGText, PROP_TEXT_WDG_SLIDE_STEP_OFFSET, (u32)nSlideStepOffset);
}

/** WdgTextSetSlideStepTime
* @brief        Set slide step time. Each duration time of sliding. The unit is msec, if a negative sign to stop sliding
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    nSlideStepTime    Each duration time of sliding. The unit is msec, if a negative sign to stop sliding.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTextSetSlideStepTime
(
    IWidget                 *pWDGText,
    s32                     nSlideStepTime
)
{
    return WdgCommonSetProperty(pWDGText, PROP_TEXT_WDG_SLIDE_STEP_TIME, (u32)nSlideStepTime);
}

/** WdgTextSetEnableAnimate
* @brief        Turn on/off animation to widget
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    bEnableAnimate    TRUE, turn on,
*                                 FALSE, turn off.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTextSetEnableAnimate
(
    IWidget                 *pWDGText,
    boolean                 bEnableAnimate
)
{
    return WdgCommonSetProperty(pWDGText, PROP_WDG_ENABLE_ANIMATE, (u32)bEnableAnimate);
}

/** WdgTextSetSlideOnOff
* @brief        Set slide on off
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    bSlideOnOff       Start/Stop the sliding.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTextSetSlideOnOff
(
    IWidget                 *pWDGText,
    boolean                 bSlideOnOff
)
{
    return WdgCommonSetProperty(pWDGText, PROP_TEXT_WDG_SLIDE_ON_OFF, (u32)bSlideOnOff);
}

/** WdgTextSetSlideAutoRepeat
* @brief        Set slide auto repeat
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    bSlideAutoRepeat  Automatically repeat the sliding.
*
* @retval       None
*
*/
__INLINE void WdgTextSetSlideAutoRepeat
(
    IWidget                 *pWDGText,
    boolean                 bSlideAutoRepeat
)
{
    WdgCommonSetProperty(pWDGText, PROP_TEXT_WDG_SLIDE_AUTO_REPEAT, (u32)bSlideAutoRepeat);
}

/** WdgTextSetSlideStyle
* @brief        Set slide style
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    nSlideStyle       the sliding mode, it can be set to slide-in or slide-out.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTextSetSlideStyle
(
    IWidget                 *pWDGText,
    SlideStyle_e            nSlideStyle
)
{
    return WdgCommonSetProperty(pWDGText, PROP_TEXT_WDG_SLIDE_STYLE, (u32)nSlideStyle);
}

/** WdgTextSetAlignment
* @brief        Set text alignment
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    nTextAlignment    Text Alignment
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTextSetAlignment
(
    IWidget                 *pWDGText,
    WdgAlignment_e          nTextAlignment
)
{
    return WdgCommonSetProperty(pWDGText, PROP_WDG_ALIGNMENT, (u32)nTextAlignment);
}

/** WdgTextSetPadding
* @brief   Set the paddings for a specific widget
*
* @param[in]   pWDGText          Pointer to the Text widget
* @param[in]   PaddingSize(u32)       u32 value. use MAKE_PADDING_SIZE to compose an u32 as this parameter.
*
* @retval	MAE_RET_SUCCESS		Success. The widget can handle this request.
* @retval	MAE_RET_FAILED		Failed. The widget can not handle this request.
*/
__INLINE MAE_Ret WdgTextSetPadding
(
 IWidget                 *pWDGText,
 u32          nPaddingSize
 )
{
	return WdgCommonSetProperty(pWDGText, PROP_PADDING_SIZE, nPaddingSize);
}

/** WdgTextSetLayoutFlag
* @brief        Set layout flag
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    nLayoutType       The layout type.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTextSetLayoutFlag
(
    IWidget                 *pWDGText,
    TextLayout_e            nLayoutType
)
{
    return WdgCommonSetProperty(pWDGText, PROP_TEXT_WDG_LAYOUT_FLAG, (u32)nLayoutType);
}

/** WdgTextSetAlignPriority
* @brief        Set align priority
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    nAlignPriority    the Align Priority
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTextSetAlignPriority
(
    IWidget                 *pWDGText,
    TextAlignAndBreak_e     nAlignPriority
)
{
    return WdgCommonSetProperty(pWDGText, PROP_TEXT_WDG_ALIGN_PRIORITY, (u32)nAlignPriority);
}


/** WDG_Text_SetAutoAnimate
* @brief        Set widget to be auto animate for text slide if text length is large than widget width
*               If auto is TRUE: Text slide effect enable if text length is large than widget width
*               If auto is FALSE: Text slide effect disable.
*
* @param[in]    pWDGText           The Text widget which want to be set
* @param[in]    bIsAutoAnimate      The widget auto animate status
*
* @retval       None
*
*/
__INLINE void WdgTextSetBeAutoAnimate
(
    IWidget                 *pWDGText,
    boolean                 bIsAutoAnimate
)
{
    WdgCommonSetProperty(pWDGText, PROP_WDG_BE_AUTO_ANIMATE, (u32)bIsAutoAnimate);
}


/** WdgTextSetLinkAddr
* @brief        Set the pointer of string to store the linking address
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    pLinkAddr         A pointer of string to store the linking address
*
* @retval       None
*
*/
__INLINE void WdgTextSetLinkAddr
(
    IWidget                 *pWDGText,
    MAE_WChar               *pLinkAddr
)
{
    WdgCommonSetProperty(pWDGText, PROP_TEXT_WDG_LINK_ADDR, (u32)pLinkAddr);
}

/** WdgTextSetLinkedState
* @brief        Set the state of linking address that is visited or is not visited yet
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    bLinkedState      A state of linking address that is visited or is not visited yet.
*
* @retval       None
*
*/
__INLINE void WdgTextSetLinkedState
(
    IWidget                 *pWDGText,
    boolean                 bLinkedState
)
{
    WdgCommonSetProperty(pWDGText, PROP_TEXT_WDG_LINKED_STATE, (u32)bLinkedState);
}

/** WdgTextSetLinkAutoUnderline
* @brief        Set link auto underline. If the value is TRUE, a text with linking information will be draw underline on text.
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    bLinkAutoUnderline        linking information will be draw underline on text.
*
* @retval       None
*
*/
__INLINE void WdgTextSetLinkAutoUnderline
(
    IWidget                 *pWDGText,
    boolean                 bLinkAutoUnderline
)
{
    WdgCommonSetProperty(pWDGText, PROP_TEXT_WDG_LINK_AUTO_UNDERLINE, (u32)bLinkAutoUnderline);
}

/** WdgTextSetFcsItemBGColor
* @brief        Set focus item background color
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    nFCSItemBGColor   the background color of selected/focused item widget.
*
* @retval       None
*
*/
__INLINE void WdgTextSetFcsItemBGColor
(
    IWidget                 *pWDGText,
    RGBColor_t              nFCSItemBGColor
)
{
    WdgCommonSetProperty(pWDGText, PROP_FCS_ITEM_BG_COLOR, (u32)nFCSItemBGColor);
}

/** WdgTextSetBIDI
* @brief        Enable/Disable bidi function
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[in]    bEnableBIDI       Set true to enable bidi function
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTextSetBIDI
(
    IWidget                 *pWDGText,
    boolean                 bEnableBIDI
)
{
    return WdgCommonSetProperty(pWDGText, PROP_TEXT_WDG_BIDI, (u32)bEnableBIDI);
}

/** WdgTextSetSelection
* @brief       Set the selected text on the text widget
*
* @param[in]    pWDGText            The text widget which want to be set
* @param[in]       nStartPos          The Selected text (nStart, nEnd)
* @param[in]       nEndPos
*
* @retval       MAE_Ret
*
*/
MAE_Ret WdgTextSetSelection
(
    IWidget                 *pWDGText,
    u32                        nStartPos,
    u32                        nEndPos
);

/** WdgTextReplaceSelectText
* @brief        This function replaces the current selection text with a new block of text.
*
* @param[in]    pWDGText       The text widget which want to be set.
* @param[in]    pwText          The pointer to an MAE_WChar buffer for replacing the selection text.
* @param[in]    nLen            The string length of pwText, (in MAE_WChar *). (not include the zero teriminator)
*
* @retval       MAE_RET_SUCCESS Success
* @retval       others          Failed
*
*/
MAE_Ret WdgTextReplaceSelectText
(
    IWidget                 *pWDGText,
    MAE_WChar               *pwText,
    u32                     nLen
);

/** WdgTextGetTextInfo
* @brief        Get information about the text stored in the Widget, ex, length of text, string of text...
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[out]   pTextInfo         Pointer to a TextInfo data structure, which contains length of text, string of text...
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTextGetTextInfo
(
    IWidget                 *pWDGText,
    TextInfo                *pTextInfo
);

/** WdgTextGetFontHeight
* @brief        Get the line height of the text widget
*
* @param[in]    pWDGText          Pointer to the Text widget
*
* @retval       MinLineHeight     The line height of the text widget
*
*/
u32 WdgTextGetFontHeight
(
    IWidget                 *pWDGText
);

/** WdgTextGetTextOutlineColor
* @brief        Get outline text color
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[out]   pTextOutlineColor the color of outline text
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTextGetTextOutlineColor
(
    IWidget                 *pWDGText,
    RGBColor_t              *pTextOutlineColor
)
{
    return WdgCommonGetProperty(pWDGText, PROP_WDG_TEXT_OUTLINE_COLOR, (u32*)pTextOutlineColor);
}

/** WdgTextGetHighlightTextOutlineColor
* @brief        Get highlight text outline color
*
* @param[in]     pWDGText                      Pointer to the Text widget
* @param[out]    pHighLightTextOutlineColor    The color of highlight text's outline
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgTextGetHighlightTextOutlineColor
(
    IWidget                 *pWDGText,
    RGBColor_t              *pHighLightTextOutlineColor
)
{
    return WdgCommonGetProperty(pWDGText, PROP_WDG_HIGHLIGHT_TEXT_OUTLINE_COLOR, (u32*)pHighLightTextOutlineColor);
}

/** WdgTextGetHighlightBGColor
* @brief        Get highlight background color
*
* @param[in]     pWDGText          Pointer to the Text widget
* @param[out]    pHighLightBGColor The color of high BG
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgTextGetHighlightBGColor
(
    IWidget                 *pWDGText,
    RGBColor_t              *pHighLightBGColor
)
{
    return WdgCommonGetProperty(pWDGText, PROP_WDG_HIGHLIGHT_BG_COLOR, (u32*)pHighLightBGColor);
}

/** WdgTextGetSlideDirection
* @brief        Get slide direction
*
* @param[in]     pWDGText          Pointer to the Text widget
*
* @return        The sliding directions. ( up, down, left and right )
*
*/
SlideDirection_e WdgTextGetSlideDirection
(
    IWidget                 *pWDGText
);

/** WdgTextGetSlideStepOffSet
* @brief        Get slide step offset. The shifting positions that text slide every time
*
* @param[in]    pWDGText         Pointer to the Text widget
*
* @retval       SlideStepOffSet  The shifting positions that text slide every time.
*
*/
s32 WdgTextGetSlideStepOffSet
(
    IWidget                 *pWDGText
);

/** WdgTextGetSlideStepTime
* @brief        Get slide step time. Each duration time of sliding. The unit is msec, if a negative sign to stop sliding
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[out]   pSlideStepTime    Each duration time of sliding. The unit is msec, if a negative sign to stop sliding.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTextGetSlideStepTime
(
    IWidget                 *pWDGText,
    s32                     *pSlideStepTime
)
{
    return WdgCommonGetProperty(pWDGText, PROP_TEXT_WDG_SLIDE_STEP_TIME, (u32*)pSlideStepTime);
}

/** WdgTextGetSlideOnOff
* @brief        Get slide on off
*
* @param[in]    pWDGText         Pointer to the Text widget
*
* @retval       SlideOnOff       Start/Stop the sliding.
*
*
*/
boolean WdgTextGetSlideOnOff
(
    IWidget                 *pWDGText
);

/** WdgTextGetSlideAutoRepeat
* @brief        Get slide auto repeat
*
* @param[in]    pWDGText         Pointer to the Text widget
*
* @retval       SlideAutoRepeat  Automatically repeat the sliding.
*
*/
boolean WdgTextGetSlideAutoRepeat
(
    IWidget                 *pWDGText
);

/** WdgTextGetSlideStyle
* @brief        Get slide style
*
* @param[in]    pWDGText          Pointer to the Text widget
*
* @return       Slide style.
*
*/
SlideStyle_e WdgTextGetSlideStyle
(
    IWidget                 *pWDGText
);

/** WdgTextGetAlignment
* @brief        Get text alignment
*
* @param[in]    pWDGText          Pointer to the Text widget
* @param[out]   pTextAlignment    Text Alignment
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTextGetAlignment
(
    IWidget                 *pWDGText,
    WdgAlignment_e          *pTextAlignment
)
{
    return WdgCommonGetProperty(pWDGText, PROP_WDG_ALIGNMENT, (u32*)pTextAlignment);
}

/** WdgTextGetLayoutFlag
* @brief        Get layout flag
*
* @param[in]     pWDGText          Pointer to the Text widget
*
* @return        The layout type.
*
*/
u32 WdgTextGetLayoutFlag
(
    IWidget                 *pWDGText
);

/** WdgTextGetAlignPriority
* @brief        Get align priority
*
* @param[in]     pWDGText          Pointer to the Text widget
*
* @return        The Align Priority
*
*/
TextAlignAndBreak_e WdgTextGetAlignPriority
(
    IWidget                 *pWDGText
);

/** WdgTextGetLinkAddr
* @brief        Get the pointer of string to store the linking address
*
* @param[in]    pWDGText          Pointer to the Text widget
*
* @retval       pLinkAddr         A pointer of string to store the linking address
*
*/
MAE_WChar* WdgTextGetLinkAddr
(
    IWidget                 *pWDGText
);

/** WdgTextGetLinkedState
* @brief        Set the state of linking address that is visited or is not visited yet
*
* @param[in]    pWDGText          Pointer to the Text widget
*
* @retval       LinkedState       A state of linking address that is visited or is not visited yet.
*
*/
boolean WdgTextGetLinkedState
(
    IWidget                 *pWDGText
);

/** WdgTextGetLinkAutoUnderline
* @brief        Get link auto underline. If the value is TRUE, a text with linking information will be draw underline on text.
*
* @param[in]    pWDGText            Pointer to the Text widget
*
* @return 
* @retval       Link auto underline setting.
*
*/
boolean WdgTextGetLinkAutoUnderline
(
    IWidget                 *pWDGText
);

/** WdgTextGetFcsItemBGColor
* @brief        Get focus item background color
*
* @param[in]     pWDGText          Pointer to the Text widget
* @param[out]    pFCSItemBGColor   the background color of selected/focused item widget.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgTextGetFcsItemBGColor
(
    IWidget                 *pWDGText,
    RGBColor_t              *pFCSItemBGColor
)
{
    return WdgCommonGetProperty(pWDGText, PROP_FCS_ITEM_BG_COLOR, (u32*)pFCSItemBGColor);
}

/** WdgTextGetBIDI
* @brief        Enable/Disable bidi function
*
* @param[in]     pWDGText         Pointer to the Text widget
*
* @retval        EnableBIDI       the pointer of boolean value EnableBIDI
*
*/
boolean WdgTextGetBIDI
(
    IWidget                 *pWDGText
);

/** WdgTextGetSelection
* @brief        This function gets the current selection text.
*
* @param[in]    pWDGText       The text widget which want to be set.
* @param[in]    pwText          The pointer to an MAE_WChar buffer will copy the selection text.
* @param[in]    nLen            The pwText buffer length, (in MAE_WChar *).
*
* @retval       MAE_RET_SUCCESS Success
* @retval       others          Failed
*
*/
MAE_Ret WdgTextGetSelection
(
    IWidget                 *pWDGText,
    MAE_WChar               *pwText,
    u32                     nLen
);

/** WdgTextRegisterSlideChangeCb
* @brief        Register text slide change callback; CB will be triggered if text slide changed.
*
* @param[in]    pWDGText          The text widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTextRegisterSlideChangeCb
(
    IWidget                 *pWDGText,
    PfnWdgTextSlideChange   pfn,
    void                    *pUserData
);

/** WdgTextRegisterLinkTextClickCb
* @brief        Register link text click callback; CB will be triggered if link text(text on website) click. (#ifdef __TOUCH_SCREEN_MMI__)
*
* @param[in]    pWDGText          The text widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTextRegisterLinkTextClickCb
(
    IWidget                 *pWDGText,
    PfnWdgTextLinkTextClick pfn,
    void                    *pUserData
);

/** WdgTextRegisterDataChangeCb
* @brief        Register data change callback; CB will be triggered while data changed.
*
* @param[in]    pWDGText          The Text widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTextRegisterDataChangeCb
(
    IWidget                         *pWDGText,
    PfnWdgTextWidgetDataChange   pfn,
    void                            *pUserData
);

/** WdgTextDeregisterSlideChangeCb
* @brief        Deregister text slide change callback; CB will be triggered if text slide changed.
*
* @param[in]    pWDGText          The text widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTextDeregisterSlideChangeCb
(
    IWidget                 *pWDGText,
    PfnWdgTextSlideChange   pfn,
    void                    *pUserData
);

/** WdgTextDeregisterLinkTextClickCb
* @brief        Deregister link text click callback; CB will be triggered if link text(text on website) click. (#ifdef __TOUCH_SCREEN_MMI__)
*
* @param[in]    pWDGText          The text widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTextDeregisterLinkTextClickCb
(
    IWidget                 *pWDGText,
    PfnWdgTextLinkTextClick pfn,
    void                    *pUserData
);

/** WdgTextDeregisterDataChangeCb
* @brief        Deregister data change callback; CB will be triggered while data changed.
*
* @param[in]    pWDGText       The Text widget which want to set callback
* @param[in]    pfn            callback function
* @param[in]    pUserData       User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval      others            Failed
*
*/
MAE_Ret WdgTextDeregisterDataChangeCb
(
    IWidget                         *pWDGText,
    PfnWdgTextWidgetDataChange   pfn,
    void                            *pUserData
);

#endif //__MMI_WDG_TEXT_H__
/*=============================================================*/
// end of file
