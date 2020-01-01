/**
 * @file mmi_wdg_input_priv.h
 * @brief This file defines the data structure of InputWidget
 *
 * @version $Id: mmi_wdg_input_priv.h 39819 2009-09-09 13:16:22Z ryan.chou $
 */
#ifndef __MMI_WDG_INPUT_PRIV_H__
#define __MMI_WDG_INPUT_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_forward.h"
#include "mae_widgetbase.h"
#include "mmi_mae_inputcontroller.h"
#include "mmi_mae_input_common.h"
#include "mmi_mae_text.h"
#include "mmi_mae_text_util.h"
#include "mmi_wdg_input.h"
#include "mae_inputcontroller_priv.h"
#ifdef __MMI_SCRIPT_EASY_EDITOR__
#include "scripteasy.h"
#include "mmi_wdg_text_priv.h"
#endif/*__MMI_SCRIPT_EASY_EDITOR__*/
/*=============================================================*/
// type and define
/*=============================================================*/

//#define DEFAULT_SEGMENT_SIZE 4
#define DEFAULT_CARET_WIDTH          1

#define MAE_WCHAR_LINE_FEED			 0x000A
#define MAE_WCHAR_CARRIAGE_RETURN    0x000D
#define MAE_WCHAR_SPACE              0x0020


/* FONT_TYPE 0 ==> Normal type */
#define DEFAULT_FONT_TYPE 0
#define DEFAULT_FONT_CATE FONT_CAT_NORMAL
#define MAX_DISPLAY_WORDS_IN_SINGLE_LINE	128
#define MAX_PASSWORD_WORD_COUNT				128

#define MULTILINE_EXTEND_LINES              20
#define MULTILINE_DIFF_LINES_BETWEEN_TOTAL_LAST 4

#define DEFAULT_START_UPDATE_POSITION       -1
#define IME_DEFAULT_SCROLL_STEP				1
#define IME_VIRTUAL_SINGLELINE_DISPLAY_WIDTH 0xFFFF


typedef struct{
	MAE_WChar* pDisplayStr;
	MAE_WChar* pWholeStr;
	u32 nStrLen;
	//u32 nStrPixel;
	boolean isRTL;
	boolean withUnderline;
	boolean withHighlight;
	u32 highlight_StartPos;
	u32 highlight_EndPos;
	u32 underline_StartPos;
	u32 underline_EndPos;
	u32 *pu32ColorAry;
}DrawLineInfo;

typedef struct{
    u32 *startPosInLine;
    u16 totalLines;
}EachLineInfo;

typedef struct{
    s32 startUpdatePos;
	u32 prevUnderlineStart;
	u32 prevUnderlineEnd;
	u32 prevSelectStart;
	u32 prevSelectEnd;
    u32 firstDisplayWordPos;
    u32 firstDisplayLine;
    u32 visiableLines;
    u32 cursorLine;
    u16 lastLine;
    //EachLineInfo lineInfo;
}MultilineDisplayInfo;


typedef struct {
    WidgetBaseEx_t WdgBase;
	//boolean isfocused;
    boolean isPasswdStyle;
	boolean bShowLatestPasswd;
    boolean isMultiline;
    boolean isWithTitle;            //For recording with title or not.
    MAE_WChar pwdMask;
    WidgetSize_t preffredSize;
    u32 lineGap;
    u32 fontHeight;
    boolean bIgnoreSelWhenRecalculatingDisplayLines;
	boolean bKeepLTRDirection;
    ModelListener_t mdlLsn;			//the text model listener
    Rect_t    rectCaret;
    IInputController* pInputController;    //the pointer to text controller
    IWidget* pCaret;                //the pointer to CaretWidget
	MultilineDisplayInfo mtlDispInfo;
	SinglelineDisplayInfo slDispInfo;
	u32 nCursorXOffset;
    boolean bEnableInvalideByTextModelChange;
	boolean bShowBorderWhenLoseFocus;
	TextThemeProperty	sTextThemeProperty;
	boolean bSetColorForUnfocused;
    boolean bDrawUnderLine;
	ModelListener_t mdlLsnTheme;          ///< A model listener for theme manager.
	u32 wdgAlignment_e;
	ITextTable *pITextTable;
	u32					nReloadRCFlag;		///< the flag record which rc property has been modified outside, those are not reload
	boolean bColorfulText;
	ColorAry_t sColorAry;
	u32 *pTextColorAry;
	u16 u16TextColorArySize;
#ifdef __TOUCH_SCREEN_MMI__
	// for multi-line
	s16 nDrawOffsetY;
	s32 nTS_StartY;
	s32 nTS_StartLocationY;
	s32 nSlideOffsetY;
	// for single-line
	ITouchSrv *pITouchSrv;
	s32 nTS_StartLocationX;
	s32 nSlideOffsetX;
	u32 nFitLen;
#endif
#ifdef __MMI_SCRIPT_EASY_EDITOR__
	SeEditor *pSeEditor;
	boolean bRecreateEditor; //destroy editor and re-create it! 
	void* pDeviceBitmap;
	TextWidget_t pTextWdg;

	int x; //used when the editor position changed
	int y; //used when the editor position changed

	/*cursor function*/
	boolean pCaretDisplayStatus; //
	boolean pCaretBlinkStatus;
	IDisplay *pIDisplay;
	u32 nCursorPos;

	/*for scrollbar function*/
	ScrollData_t pScrolldata;

	/*for inputWidget*/
	u32 new_inputWidget_width; // store width 
	u32 new_inputWidget_height; // stroe height
	u32 new_inputWidget_left;  // store dx
	u32 new_inputWidget_top;   // store dy

	IBitmap* piCaretBitmap;
	boolean active;
	boolean is_caret_timer_active;
#endif/*__MMI_SCRIPT_EASY_EDITOR__*/

} InputWidget_t;


typedef enum {
    FORWARD,
    BACKWARD
}Direction;

//Flags
enum
{
	INPUT_FLAG_START = WDG_BASE_FLAG_END,
	INPUT_FLAG_SHOW_LATEST_PASSWORD = INPUT_FLAG_START,
	INPUT_FLAG_ENABLE_TOUCH_SLIDING,
	INPUT_FLAG_SLIDE_TIMER_RUNNING,
	INPUT_FLAG_NEED_SLIDE_CHECKING,
	INPUT_FLAG_END
};

//Mask for flags
#define INPUT_MASK_SHOW_LATEST_PASSWORD (1<<INPUT_FLAG_SHOW_LATEST_PASSWORD)  ///< enable / disable check lunar February
#define INPUT_MASK_ENABLE_TOUCH_SLIDING (1<<INPUT_FLAG_ENABLE_TOUCH_SLIDING)  ///< check if allow touch slide
#define INPUT_MASK_SLIDE_TIMER_RUNNING (1<<INPUT_FLAG_SLIDE_TIMER_RUNNING)  ///< check touch slide timer running
#define INPUT_MASK_NEED_SLIDE_CHECKING (1<<INPUT_FLAG_NEED_SLIDE_CHECKING)  ///< check if need slide

//Get flag macro
#define INPUT_IS_ENABLE_SHOW_LATEST_PASSWORD(_pInput) \
	(boolean)(((_pInput)->WdgBase.Flags&INPUT_MASK_SHOW_LATEST_PASSWORD)>>INPUT_FLAG_SHOW_LATEST_PASSWORD)
#define INPUT_IS_ENABLE_TOUCH_SLIDING(_pInput) \
	(boolean)(((_pInput)->WdgBase.Flags&INPUT_MASK_ENABLE_TOUCH_SLIDING)>>INPUT_FLAG_ENABLE_TOUCH_SLIDING)
#define INPUT_IS_SLIDE_TIMER_RUNNING(_pInput) \
	(boolean)(((_pInput)->WdgBase.Flags&INPUT_MASK_SLIDE_TIMER_RUNNING)>>INPUT_FLAG_SLIDE_TIMER_RUNNING)
#define INPUT_IS_NEED_SLIDE_CHECKING(_pInput) \
	(boolean)(((_pInput)->WdgBase.Flags&INPUT_MASK_NEED_SLIDE_CHECKING)>>INPUT_FLAG_NEED_SLIDE_CHECKING)

//Set flag macro
#define INPUT_SET_ENABLE_SHOW_LATEST_PASSWORD(_pInput, _b) \
	(_pInput)->WdgBase.Flags = ((_pInput)->WdgBase.Flags&(~INPUT_MASK_SHOW_LATEST_PASSWORD))|(((u32)_b)<<INPUT_FLAG_SHOW_LATEST_PASSWORD)
#define INPUT_SET_ENABLE_TOUCH_SLIDING(_pInput, _b) \
	(_pInput)->WdgBase.Flags = ((_pInput)->WdgBase.Flags&(~INPUT_MASK_ENABLE_TOUCH_SLIDING))|(((u32)_b)<<INPUT_FLAG_ENABLE_TOUCH_SLIDING)
#define INPUT_SET_SLIDE_TIMER_RUNNING(_pInput, _b) \
	(_pInput)->WdgBase.Flags = ((_pInput)->WdgBase.Flags&(~INPUT_MASK_SLIDE_TIMER_RUNNING))|(((u32)_b)<<INPUT_FLAG_SLIDE_TIMER_RUNNING)
#define INPUT_SET_NEED_SLIDE_CHECKING(_pInput, _b) \
	(_pInput)->WdgBase.Flags = ((_pInput)->WdgBase.Flags&(~INPUT_MASK_NEED_SLIDE_CHECKING))|(((u32)_b)<<INPUT_FLAG_NEED_SLIDE_CHECKING)

// RELOAD flag
enum
{
	INPUT_WDG_RELOAD_FLAG_START = 0,
	INPUT_WDG_RELOAD_FLAG_TEXTTHEMEPROPERTY = INPUT_WDG_RELOAD_FLAG_START,   ///< sTextThemeProperty
	INPUT_WDG_RELOAD_FLAG_DRAWUNDERLINE,	///< bDrawUnderLine
	INPUT_WDG_RELOAD_FLAG_PADDINGSIZE,	///< padding size
	INPUT_WDG_RELOAD_FLAG_ALIGNMENT,	///< alignment
	INPUT_WDG_RELOAD_FLAG_BORDERSIZE,	///< border size
	INPUT_WDG_RELOAD_FLAG_BGPOSITION,	///< bg position
	INPUT_WDG_RELOAD_FLAG_END
};

/**
* Flag Mask
*/
#define INPUT_WDG_RELOAD_MASK_TEXTTHEMEPROPERTY         (1<<INPUT_WDG_RELOAD_FLAG_TEXTTHEMEPROPERTY)
#define INPUT_WDG_RELOAD_MASK_DRAWUNDERLINE        (1<<INPUT_WDG_RELOAD_FLAG_DRAWUNDERLINE)
#define INPUT_WDG_RELOAD_MASK_PADDINGSIZE        (1<<INPUT_WDG_RELOAD_FLAG_PADDINGSIZE)
#define INPUT_WDG_RELOAD_MASK_ALIGNMENT        (1<<INPUT_WDG_RELOAD_FLAG_ALIGNMENT)
#define INPUT_WDG_RELOAD_MASK_BORDERSIZE        (1<<INPUT_WDG_RELOAD_FLAG_BORDERSIZE)
#define INPUT_WDG_RELOAD_MASK_BGPOSITION        (1<<INPUT_WDG_RELOAD_FLAG_BGPOSITION)
/**
* Macro to get flag value
*/
#define INPUT_WDG_TEXTTHEMEPROPERTY_IS_MODIFIED(_pWdg) \
    (boolean)(((_pWdg)->nReloadRCFlag&INPUT_WDG_RELOAD_MASK_TEXTTHEMEPROPERTY)>>INPUT_WDG_RELOAD_FLAG_TEXTTHEMEPROPERTY)
#define INPUT_WDG_DRAWUNDERLINE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&INPUT_WDG_RELOAD_MASK_DRAWUNDERLINE)>>INPUT_WDG_RELOAD_FLAG_DRAWUNDERLINE)
#define INPUT_WDG_PADDINGSIZE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&INPUT_WDG_RELOAD_MASK_PADDINGSIZE)>>INPUT_WDG_RELOAD_FLAG_PADDINGSIZE)
#define INPUT_WDG_ALIGNMENT_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&INPUT_WDG_RELOAD_MASK_ALIGNMENT)>>INPUT_WDG_RELOAD_FLAG_ALIGNMENT)
#define INPUT_WDG_BORDERSIZE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&INPUT_WDG_RELOAD_MASK_BORDERSIZE)>>INPUT_WDG_RELOAD_FLAG_BORDERSIZE)
#define INPUT_WDG_BGPOSITION_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&INPUT_WDG_RELOAD_MASK_BGPOSITION)>>INPUT_WDG_RELOAD_FLAG_BGPOSITION)
/**
* Macro to Set flag value
*/
#define INPUT_WDG_TEXTTHEMEPROPERTY_SET_MODIFIED(_pWdg, _b) \
    (_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~INPUT_WDG_RELOAD_MASK_TEXTTHEMEPROPERTY))|(((u32)_b)<<INPUT_WDG_RELOAD_FLAG_TEXTTHEMEPROPERTY)
#define INPUT_WDG_DRAWUNDERLINE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~INPUT_WDG_RELOAD_MASK_DRAWUNDERLINE))|(((u32)_b)<<INPUT_WDG_RELOAD_FLAG_DRAWUNDERLINE)
#define INPUT_WDG_PADDINGSIZE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~INPUT_WDG_RELOAD_MASK_PADDINGSIZE))|(((u32)_b)<<INPUT_WDG_RELOAD_FLAG_PADDINGSIZE)
#define INPUT_WDG_ALIGNMENT_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~INPUT_WDG_RELOAD_MASK_ALIGNMENT))|(((u32)_b)<<INPUT_WDG_RELOAD_FLAG_ALIGNMENT)
#define INPUT_WDG_BORDERSIZE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~INPUT_WDG_RELOAD_MASK_BORDERSIZE))|(((u32)_b)<<INPUT_WDG_RELOAD_FLAG_BORDERSIZE)
#define INPUT_WDG_BGPOSITION_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~INPUT_WDG_RELOAD_MASK_BGPOSITION))|(((u32)_b)<<INPUT_WDG_RELOAD_FLAG_BGPOSITION)

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret InputWidget_New(MAE_ClsId ClsID, void **ppObj);
__SLDPM_FREE__ boolean InputWidget_HandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret _WdgInputConstructor(InputWidget_t *pThis);
void _WdgInputDestructor(InputWidget_t *pThis);

//for IWidget interface
void InputWidget_GetPreferredSize(IWidget *pIWidget, WidgetSize_t *pSize);
void _WdgInputDraw(IWidget *pIWidget, Wdg_Draw_Req_t *pReq);
__SLDPM_FREE__ MAE_Ret InputWidget_SetModel(IWidget *pIWidget, IModel *pIModel, IBase* pOwner);
__SLDPM_FREE__ void _InputWidget_ModelListener(void *pUsrData, ModelEvent_t *pMdlEvent);


void _InputWidget_CaretBlinkCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pCaretWidget);

//not interface function
boolean _InputWidget_ConvertTexttoPasswordFormat(TextInfo *textinfo, MAE_WChar *resultAry, u16 nArraySize, MAE_WChar cPwdMask, boolean bShowLatestPasswd);
void _InputWidget_singleline_CalculateFirstDisplayWord(IWidget *pIWidget, IFONT *pIFont, u32 nSelEnd, u32 nCursorPos, MAE_WChar *pwText, u32 *nCursorXOffset);
void _InputWidget_singleline_ConvertTextInfotoDrawLineInfo(u32 nDisplayAreaWidth, ITextTable *pITextTable, TextInfo *pDrawingLineTextInfo, u32 nFirstDispCharOffsetinDispStr, u32 nFirstDispCharLeftPos, DrawLineInfo* pOutDrawLineInfo);
void _InputWidget_DrawSingleLineText(IWidget *pIWidget, IDisplay *pIDisplay, u32 nDrawAreaStartPosX, u32 nDrawAreaStartPosY, Rect_t* CArect, DrawLineInfo *pDrawLineInfo, s32 *nDrawTextPosX, boolean b3D);
__SLDPM_FREE__ void InputWidget_SetSize(IWidget *pIWidget, WidgetSize_t *pSize);
__SLDPM_FREE__ void _InputWidget_SetVisibleLines(IWidget *pIWidget);
void _InputWidget_multiline_Update_TextTable_LineInfo(InputWidget_t *pThis, s32 nStartUpdatePos, u32 nDisplayWidth, MAE_WChar *pText, u32 nTextLen, MultilineDisplayInfo *pMtlDispInfo, boolean bKeepPreTable);
void _InputWidget_multiline_GetLineStartPosbyCurPos(InputWidget_t *pThis, MAE_WChar *pText, u32 nPos, ITextTable *pITextTable, u32 *nLineStartPos, u32 *nLineIdx);
void _InputWidget_SetupDrawLineInfo(IWidget *pIWidget, TextInfo *textInfoSingleLine, MAE_WChar *pwtext, u32 nStartPos, u32 nEndPos);
__SLDPM_FREE__ boolean _InputWidget_GetCursorPosAfterMoveUpAndDown(IWidget *pIWidget, boolean bPressUp, u32 *nNewCurPos);
void _InputWidget_SkipPreviousChangeLineCharacter(MAE_WChar *pText, u32 nPos,  u32 nCurLine, u32 *nFitChar);
__SLDPM_FREE__ void _InputWidget_SetFontHeightAndCaretSize(IWidget *pIWidget);
void InputWidget_InfoUpdateAfterDrawing(IBase* pUser, u32 Param);
__SLDPM_FREE__ void _InputWidget_CalculateDrawInfo(IWidget *pIWidget, boolean bKeepPreTable);
__SLDPM_FREE__ void InputWidget_Notify(IWidget *pIWidget, boolean bSendScorllNotify, boolean bSendMultilineNotify);
boolean _InputWidget_CreateTextTable(InputWidget_t *pThis, u32 nDisplayWidth, MAE_WChar* pText, u32 nTextLen, boolean bKeepPreTable);
void _InputWidget_multiline_FillinDrawLineInfo(InputWidget_t *pIWidget, ITextTable *pITextTable, u32 nLineIndex, DrawLineInfo *pOutDrawLineInfo);
void _InputWidget_singleline_CalculateFirstDisplayWordAndGetCursorXPos(IWidget *pIWidget, IFONT * pIFont, u32 nCursorOffset, u32 *nCursorXPos);

__SLDPM_FREE__ void _InputWidget_Controller_CB(void* pUser, InputControllerCallbackData* pData);
void InputWidget_PasswordMaskRedrawCallBack(InputWidget_t *pThis, void * pData);

#endif //__MMI_WDG_INPUT_PRIV_H__
/*=============================================================*/
// end of file
