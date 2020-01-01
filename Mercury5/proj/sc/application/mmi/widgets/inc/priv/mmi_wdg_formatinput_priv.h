/**
* @file mmi_wdg_formatinput_priv.h
* @brief This file defines the data structure of FormatInputWidget
*
* @version $Id: mmi_wdg_formatinput_priv.h 34798 2009-07-01 08:29:45Z william.lien $
*/
#ifndef __MMI_WDG_FORMATINPUT_PRIV_H__
#define __MMI_WDG_FORMATINPUT_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_widgetbase.h"
#include "mmi_mae_input_common.h"
#include "mmi_mae_softkeyboard_resource_id.h"

#ifdef __MMI_IME_CSTAR_FORMAT__
#include "kmx_ime_config.h"
#endif
/*=============================================================*/
// type and define
/*=============================================================*/
#define DEFAULT_SEGMENT_SIZE_IP 4           ///< IP format :  XXX.XXX.XXX.XXX
#define DEFAULT_SEGMENT_SIZE_TIME 2         ///< Time format: HH:MM (AM/PM)

#define SEGMENT_SIZE_TIME_UPDOWN_ADJUST_ENABLE	  3	///< Time format: HH:MM AM/PM
#define SEGMENT_SIZE_TIME_HHMMSS  3			///<Time format: HH:MM:SS

#define DEFAULT_SEGMENT_SIZE DEFAULT_SEGMENT_SIZE_IP        ///< the max segment size of supporting type.

#define DEFAULT_IP_SEPERATER 0x002E             ///< '.'
#define DEFAULT_TIME_SEPERATER 0x003A           ///< ':'
#define MAE_WCHAR_SPACE 0x0020
#define MAE_WCHAR_NULL 0x0000
#define MAE_WCHAR_8 0x0038
#define MAE_WCHAR_DASH  0x002D                  ///< '-'

#define DEFAULT_FIELD_GAP_PIXEL 0            ///< the gap between each Field.
#define DEFAULT_FIELD_MAX_LEN 4         ///< default string length of each field

//#define DEFAULT_FONT_TYPE FONT_TYPE_NORMAL      ///<  FONT_TYPE 0 ==> Normal type
//#define DEFAULT_FONT_CATE FONT_CAT_NORMAL      ///<  default font size


///< For Date Widget
#define AVAILABLE_MIN_MONTH  1      ///< the min value of month
#define AVAILABLE_MAX_MONTH  12     ///< the max value of month
#define AVAILABLE_MAX_DAY 31        ///< the max value of day
#define AUTOMOVENEXT_MIN_MONTH 2    ///< if user inputs value in month field which is equal or more than such value, the focus will move to next field automatically.
#define AUTOMOVENEXT_MIN_DAY  4         ///< if user inputs value in day field which is equal or more than such value, the focus will move to next field automatically.
#define AVAILABLE_MAX_LEN_YEAR  4   ///< the max length of year field
#define AVAILABLE_MAX_LEN_MONTH 2   ///< the max length of month field
#define AVAILABLE_MAX_LEN_DAY   2   ///< the max length of day field

///< For IP Widget
#define IP_MAX_VALUE            255 ///< the max value for each IP element
#define IP_MIN_VALUE            0   ///< the  min value for each IP element
#define AUTOMOVENEXT_MIN_IP     26  ///< if user inputs value in an IP element field which is equal or more than such value, the focus will move to next field automatically.
#define AVAILABLE_MAX_LEN_IP_ELEMENT    3   ///< the max length of IP element  field

///< For Time Widget
#define AVAILABLE_MIN_MIMUTE_SECOND    0    ///< the min value of MINUTE/SECOND field
#define AVAILABLE_MAX_MIMUTE_SECOND    59   ///< the max value of MINUTE/SECOND field
#define AUTOMOVENEXT_MIN_MINUTE_SECOND 6    ///< if user inputs value in MINUTE/SECOND field which is equal or more than such value, the focus will move to next field automatically.

#define AVAILABLE_MAX_LEN_HOUR  2   ///< the max length of hour field
#define AVAILABLE_MAX_LEN_MIN_SEC   2   ///< the max length of minute/seocnd field

#define TIMEFORMAT_12HR_MAX_HOUR    12 ///< the max value of HOUR field of 12 Hour time format
#define TIMEFORMAT_12HR_MIN_HOUR    1   ///< the min value of HOUR field of 12 Hour time format
#define TIMEFORMAT_12HR_MIN_AUTOMOVENEXT_HOUR    2  ///< when time format is 12 hour time format, if user inputs value in HOUR field which is equal or more than such value, the focus will move to next field automatically.

#define TIMEFORMAT_24HR_MAX_HOUR    23  ///< the max value of HOUR field of 24 Hour time format
#define TIMEFORMAT_24HR_MIN_HOUR    0   ///< the min value of HOUR field of 24 Hour time format
#define TIMEFORMAT_24HR_MIN_AUTOMOVENEX_HOUR    3 ///< when time format is 24 hour time format, if user inputs value in HOUR field which is equal or more than such value, the focus will move to next field automatically.

//Just a define value to distinguish between SKB key press event or real MAE key press event
#define SOFTKEYBOARD_KEY_PRESS 0x10

enum
{
	FORMATINPUT_WDG_RELOAD_FLAG_START = 0,
	FORMATINPUT_WDG_RELOAD_FLAG_TXTFONTSIZE = FORMATINPUT_WDG_RELOAD_FLAG_START,   ///< textAlign
	FORMATINPUT_WDG_RELOAD_FLAG_TXTFONTTYPE,
	FORMATINPUT_WDG_RELOAD_FLAG_AMPM,
	FORMATINPUT_WDG_RELOAD_FLAG_AVAIMAXYEAR,
	FORMATINPUT_WDG_RELOAD_FLAG_AVAIMINYEAR,
	FORMATINPUT_WDG_RELOAD_FLAG_ALIGNMENT,
	FORMATINPUT_WDG_RELOAD_FLAG_END
};
/**
* Flag Mask
*/
#define FORMATINPUT_WDG_RELOAD_MASK_TXTFONTSIZE         (1<<FORMATINPUT_WDG_RELOAD_FLAG_TXTFONTSIZE)
#define FORMATINPUT_WDG_RELOAD_MASK_TXTFONTTYPE         (1<<FORMATINPUT_WDG_RELOAD_FLAG_TXTFONTTYPE)
#define FORMATINPUT_WDG_RELOAD_MASK_AMPM				(1<<FORMATINPUT_WDG_RELOAD_FLAG_AMPM)
#define FORMATINPUT_WDG_RELOAD_MASK_AVAIMAXYEAR			(1<<FORMATINPUT_WDG_RELOAD_FLAG_AVAIMAXYEAR)
#define FORMATINPUT_WDG_RELOAD_MASK_AVAIMINYEAR			(1<<FORMATINPUT_WDG_RELOAD_FLAG_AVAIMINYEAR)
#define FORMATINPUT_WDG_RELOAD_MASK_ALIGNMENT			(1<<FORMATINPUT_WDG_RELOAD_FLAG_ALIGNMENT)
/**
* Macro to get flag value
*/
#define FORMATINPUT_WDG_TXTFONTSIZE_IS_MODIFIED(_pWdg) \
    (boolean)(((_pWdg)->nReloadRCFlag&FORMATINPUT_WDG_RELOAD_MASK_TXTFONTSIZE)>>FORMATINPUT_WDG_RELOAD_FLAG_TXTFONTSIZE)
#define FORMATINPUT_WDG_TXTFONTTYPE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&FORMATINPUT_WDG_RELOAD_MASK_TXTFONTTYPE)>>FORMATINPUT_WDG_RELOAD_FLAG_TXTFONTTYPE)
#define FORMATINPUT_WDG_AMPM_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&FORMATINPUT_WDG_RELOAD_MASK_AMPM)>>FORMATINPUT_WDG_RELOAD_FLAG_AMPM)
#define FORMATINPUT_WDG_AVAIMAXYEAR_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&FORMATINPUT_WDG_RELOAD_MASK_AVAIMAXYEAR)>>FORMATINPUT_WDG_RELOAD_FLAG_AVAIMAXYEAR)
#define FORMATINPUT_WDG_AVAIMINYEAR_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&FORMATINPUT_WDG_RELOAD_MASK_AVAIMINYEAR)>>FORMATINPUT_WDG_RELOAD_FLAG_AVAIMINYEAR)
#define FORMATINPUT_WDG_ALIGNMENT_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&FORMATINPUT_WDG_RELOAD_MASK_ALIGNMENT)>>FORMATINPUT_WDG_RELOAD_FLAG_ALIGNMENT)

/**
* Macro to Set flag value
*/
#define FORMATINPUT_WDG_TXTFONTSIZE_SET_MODIFIED(_pWdg, _b) \
    (_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~FORMATINPUT_WDG_RELOAD_MASK_TXTFONTSIZE))|(((u32)_b)<<FORMATINPUT_WDG_RELOAD_FLAG_TXTFONTSIZE)
#define FORMATINPUT_WDG_TXTFONTTYPE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~FORMATINPUT_WDG_RELOAD_MASK_TXTFONTTYPE))|(((u32)_b)<<FORMATINPUT_WDG_RELOAD_FLAG_TXTFONTTYPE)
#define FORMATINPUT_WDG_AMPM_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~FORMATINPUT_WDG_RELOAD_MASK_AMPM))|(((u32)_b)<<FORMATINPUT_WDG_RELOAD_FLAG_AMPM)
#define FORMATINPUT_WDG_AVAIMAXYEAR_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~FORMATINPUT_WDG_RELOAD_MASK_AVAIMAXYEAR))|(((u32)_b)<<FORMATINPUT_WDG_RELOAD_FLAG_AVAIMAXYEAR)
#define FORMATINPUT_WDG_AVAIMINYEAR_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~FORMATINPUT_WDG_RELOAD_MASK_AVAIMINYEAR))|(((u32)_b)<<FORMATINPUT_WDG_RELOAD_FLAG_AVAIMINYEAR)
#define FORMATINPUT_WDG_ALIGNMENT_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~FORMATINPUT_WDG_RELOAD_MASK_ALIGNMENT))|(((u32)_b)<<FORMATINPUT_WDG_RELOAD_FLAG_ALIGNMENT)

typedef struct{
    u8  nMaxLen;            ///< max length of a field ex. YEAR field takes 4 characters
    u16 nValue;             ///< value
    MAE_WChar wDelimiter;   ///< the delimiter to separate from such field and next field
	#ifdef __TOUCH_SCREEN_MMI__
	u32 nStartPosX;
	u32 nWidth;
	#endif
}FormatSegment_t;

#ifdef __TOUCH_SCREEN_MMI__
typedef struct{
	u32 nFontHeight;
	u32 nSegmentStartPosY;	///< the start Y position of
	u32 nAMPMStartPosX;		///< the Start pos
	u32 nAMPMWidth;
}DrawInfo_t;
#endif

typedef struct {
    WidgetBaseEx_t WdgBase;
    ModelListener_t mdlLsn;		///< the data model listener
    boolean bValidModelData;        ///< Check if the data in data model is valid
    WidgetSize_t preffredSize;
	u32 nDigitCommonWidth;
    //Soft Keyboard related
    IIMEAssistModel *pIIMEAssistModel;
#ifdef __TOUCH_SCREEN_MMI__
#ifdef __IME_MMI_SOFTKEYBOARD__
    IWidget *pSoftKeyboardWidget;			///< the pointer to soft-keyboard widget
    boolean bSKBSwitcher;
    SoftKeyboardStatus_e eSoftKeyboardStatus;
#endif //__IME_MMI_SOFTKEYBOARD__
#endif
    s8  nCurEditingField;   ///< current editing field
    u8  nCurInputLen;       ///< current input length
    u8  nSegmentNum;        ///< total segment numbers of this widget
    FormatSegment_t segments[DEFAULT_SEGMENT_SIZE];   ///< segments
    boolean bShowAMPM;           ///< should the widget show AM/PM
	boolean bShowSecond;		 ///< should the widget show SEOCND field
    boolean bAM;                 ///< current time period
	boolean bEnableUpDownKey;	//< Enable navi- up/down key to adjust value.
	boolean bSetColorForUnfocused;
	boolean bSKBAlwaysOn;
    u16 nAvailableMaxYear;  ///< valid max year
    u16 nAvailableMinYear;  ///< valid min year
    u8 nMaxDay;             ///< valid max day value
    u8 nAutoMoveMinDay;     ///< the min day value to trigger an action to move focus from Hour field to next field
    u8 nMaxHour;            ///< max hour value for current time format
    u8 nMinHour;	        ///< min hour value for current time format
    u8 nAutoMoveMinHour;    ///< the min hour value to trigger an action to move focus from Hour field to next field
	u8 aDateSegmentIndex[3];	///< given YEAR/MONTH/DAY to query real index of segments, depends on eDateDisplayFormat
	u8 aDateSegmentType[3];	///< given filed index to query to the corresponding type of segment (YEAR/MONTH/DAY), depends on eDateDisplayFormat
	DateWdgDisplayFormat_e eDateDisplayFormat;	///< The display style of date widget, default is YYYYMMDD
	#ifdef __TOUCH_SCREEN_MMI__
	DrawInfo_t drawInfo;
	#endif
	TextThemeProperty	sTextThemeProperty;
	ModelListener_t mdlLsnTheme;          ///< A model listener for theme manager.
	u32 nXOffset;
	u32 nYOffset;
	u16 wdgAlignment_e;

	u32 nReloadRCFlag;		///< the flag record which rc property has been modified outside, those are not reload
#ifdef __IME_MMI_SOFTKEYBOARD_7COL_UI__
	IWidget *pSKBHighlightWidget;
	ModelListener_t SoftKeyboardMdlLsn;			///< the view model listener for soft-keyboard widget
#endif //__IME_MMI_SOFTKEYBOARD_7COL_UI__
#ifdef __MMI_IME_CSTAR_FORMAT__
	KMX_PT_IM_CONFIG    kmx_im_config;
	ModelListener_t     kmx_SoftKeyboardMdlLsn;
#endif /*__MMI_IME_CSTAR_FORMAT__*/

} FormatInputWidget_t;


enum TimeFields_e
{
    HOUR = 0,
    MINUTE,
	SECOND
};


enum DateFields_e
{
    YEAR = 0,
    MONTH,
    DAY,
	YYYYMMDD_YEAR = 0,
	YYYYMMDD_MONTH,
	YYYYMMDD_DAY,
	MMDDYYYY_MONTH = 0,
	MMDDYYYY_DAY,
	MMDDYYYY_YEAR,
	DDMMYYYY_DAY = 0,
	DDMMYYYY_MONTH,
	DDMMYYYY_YEAR
};


typedef enum
{
    NOT_VALID = 0,       ///< the field value is NOT a valid value, which has to be corrected.
    VALID_CANNOT_MOVETO_NEXTFIELD,  ///< the field value is an unfinished input value, but it is valid for current status. if user moves focus, the field value will be corrected.
    VALID_CAN_MOVETO_NEXTFIELD,     ///< the field value is a valid and user can move focus from such field to another one.
    VALID_AUTO_MOVETO_NEXTFIELD     ///< the field value is a valid value, and format input widget should move focus to next field automatically.
}ContentValidationResult_t;

//Flags
enum
{
	FORMATINPUT_FLAG_START = WDG_BASE_FLAG_END,
	FORMATINPUT_FLAG_DISABLE_CHECK_LUNAR_FEBRUARY = FORMATINPUT_FLAG_START,
	FORMATINPUT_FLAG_DISABLE_CHECK_HOUR,
	FORMATINPUT_FLAG_END
};

//Mask for flags
#define FORMATINPUT_MASK_DISABLE_CHECK_LUNAR_FEBRUARY (1<<FORMATINPUT_FLAG_DISABLE_CHECK_LUNAR_FEBRUARY)  ///< enable / disable check lunar February
#define FORMATINPUT_MASK_DISABLE_CHECK_HOUR (1<<FORMATINPUT_FLAG_DISABLE_CHECK_HOUR)  ///< enable / disable check hour

//Get flag macro
#define FORMATINPUT_IS_DISABLE_CHECK_LUNAR_FEBRUARY(_pFormatInput) \
	(boolean)(((_pFormatInput)->WdgBase.Flags&FORMATINPUT_MASK_DISABLE_CHECK_LUNAR_FEBRUARY)>>FORMATINPUT_FLAG_DISABLE_CHECK_LUNAR_FEBRUARY)
#define FORMATINPUT_IS_DISABLE_CHECK_HOUR(_pFormatInput) \
	(boolean)(((_pFormatInput)->WdgBase.Flags&FORMATINPUT_MASK_DISABLE_CHECK_HOUR)>>FORMATINPUT_FLAG_DISABLE_CHECK_HOUR)

//Set flag macro
#define FORMATINPUT_SET_DISABLE_CHECK_LUNAR_FEBRUARY(_pFormatInput, _b) \
	(_pFormatInput)->WdgBase.Flags = ((_pFormatInput)->WdgBase.Flags&(~FORMATINPUT_MASK_DISABLE_CHECK_LUNAR_FEBRUARY))|(((u32)_b)<<FORMATINPUT_FLAG_DISABLE_CHECK_LUNAR_FEBRUARY)
#define FORMATINPUT_SET_DISABLE_CHECK_HOUR(_pFormatInput, _b) \
	(_pFormatInput)->WdgBase.Flags = ((_pFormatInput)->WdgBase.Flags&(~FORMATINPUT_MASK_DISABLE_CHECK_HOUR))|(((u32)_b)<<FORMATINPUT_FLAG_DISABLE_CHECK_HOUR)

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
/**
*  FormatInputWidget_New
*  @brief   Create Format Input Widget.
*
*  @param  ppObj       	Pointer to the IWidget object.
*  @param  ClsID    	CLSID_DATEWIDGET/CLSID_TIMEWIDGET/CLSID_IPWIDGET
*  @retval              MAE_RET_SUCCESS/MAE_RET_OUT_OF_MEMORY/MAE_RET_FAILED 	    Success/No More memory/Create Failed.
*/
MAE_Ret FormatInputWidget_New(MAE_ClsId ClsID, void **ppObj);

/**
*  FormatInputWidget_DefHandleEvent
*  @brief   the handle event function of FormatInputWidget.
*
*  @param  pIWidget      Pointer to the FormatInputWidget object.
*  @param  evt           Event ID.
*  @param  param1        The first parameter for the inputted event.
*  @param  param2        The second parameter for the inputted event.
*  @retval               TRUE/FALSE   the inputted event is handled/the event is not handled.
*/
boolean FormatInputWidget_DefHandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 param1, u32 param2);
/*------------------------------------------------------------------------------------------
* Non-interface functions
------------------------------------------------------------------------------------------*/
/**
*  FormatInputWidgetBaseStrucCtor
*  @brief   Set initial data and default handler for FormatInputWidget.
*
*  @param  pThis        Pointer to the FormatInputWidget object.
*  @retval              MAE_RET_BAD_PARAM/MAE_RET_SUCCESS/MAE_RET_FAILED      Wrong parameter/Success/Widgtbase Construct failed.
*/
MAE_Ret _WdgFormatInputConstructor(FormatInputWidget_t *pThis);
void _WdgFormatInputDestructor(FormatInputWidget_t *pThis);

/**
*  FormatInputWidget_Draw
*  @brief   the draw function of caret widget.
*
*  @param  pIWidget      Pointer to the FormatInputWidget object.
*  @param  pIDispCanvas  Pointer to the DispCanvas object, it contains the valid client area to draw in.
*  @param  x             Draw position X.
*  @param  y             Draw position Y.
*  @retval               void
*/
void FormatInputWidget_Draw(IWidget *pIWidget, IDispCanvas *pIDispCanvas, s32 x, s32 y);

/**
*  FormatInputWidget_GetPreferredSize
*  @brief   To get the preferred size of FormatInputWidget widget.
*
*  @param  pIWidget      Pointer to the FormatInputWidget object.
*  @param  pSize         Preferred widget size.
*  @retval               void
*/
void FormatInputWidget_GetPreferredSize(IWidget *pIWidget, WidgetSize_t *pSize);
/**
*  FormatInputWidget_FreeModel
*  @brief   the call back function to free the data model.
*
*  @param  pData         Pointer to the data in data model.
*  @param  pOwner        Pointer to the owner of the data model.
*  @retval               void
*/
void FormatInputWidget_FreeModel(void *pData, IBase *pOwner);
/**
*  FormatInputWidget_ModelListener
*  @brief   the call back function when model change.
*
*  @param  pUsrData      Pointer to the FormatInputWidget object.
*  @param  ModelEvent_t  The type of happened event to data model.
*  @retval               void
*/
void FormatInputWidget_ModelListener(void *pUsrData, ModelEvent_t *pMdlEvent);

/**
*  FormatInputWidget_SetModel
*  @brief   the model setting function of FormatInputWidget.
*
*  @param  pIWidget      Pointer to the FormatInputWidget object.
*  @param  pIModel       The data model.
*  @param  pOwner        Pointer to the owner of the data model.
*  @retval               void
*/
MAE_Ret FormatInputWidget_SetModel(IWidget *pIWidget, IModel *pIModel, IBase* pOwner);

// internal function
/**
*  FormatInputWidget_GetNullString
*  @brief   Return a NULL string with specific length.
*
*  @param  wChString   The returned NULL string.
*  @param  nStrlen     the string length of NULL string.
*  @param  wch         The symbol displayed in NULL string.
*  @retval             void
*/
static void FormatInputWidget_GetNullString(MAE_WChar * wChString, u32 nStrlen, MAE_WChar wch);

/**
*  FormatInputWidget_ConvertIntegertoWChar
*  @brief   Convert integer data to wChar string.
*
*  @param  nInput      Inputted integer.
*  @param  wStr        The converted string.
*  @param  strLen      Max string length of such converted string.
*  @param  bLeadingZero Should add 0 before the converted string to fill the string length?
*  @retval             void
*/
static void FormatInputWidget_ConvertIntegertoWChar(u32 nInput, MAE_WChar * wStr, u8 strLen , boolean bLeadingZero);
/**
*  FormatInputWidget_ContentValidation
*  @brief   Validate the value of current editing field.
*
*  @param  pThis      Pointer to the FormatInputWidget object.
*  @retval NOTVALID        the field value is NOT a valid value, which has to be corrected.
           VALID_CANNOT_MOVETO_NEXTFIELD  the field value is an unfinished input value, but it is valid for current status. if user moves focus, the field value will be corrected.
           VALID_CAN_MOVETO_NEXTFIELD     the field value is a valid and user can move focus from such field to another one.
           VALID_AUTO_MOVETO_NEXTFIELD    the field value is a valid value, and format input widget should move focus to next field automatically.
*/
static ContentValidationResult_t FormatInputWidget_ContentValidation(FormatInputWidget_t *pThis);
/**
*  FormatInputWidget_MoveToNextField
*  @brief   Move focus to next field and initialize the input status(set nCurInputLen to be zero.)
*
*  @param  pThis      Pointer to the FormatInputWidget object.
*  @retval            void
*/
static void FormatInputWidget_MoveToNextField(FormatInputWidget_t *pThis);
/**
*  FormatInputWidget_MoveToPreviousField
*  @brief   Move focus to previous field and initialize the input status(set nCurInputLen to be zero.)
*
*  @param  pThis      Pointer to the FormatInputWidget object.
*  @retval            void
*/
static void FormatInputWidget_MoveToPreviousField(FormatInputWidget_t *pThis);
/**
*  FormatInputWidget_CheckLeapYearAndSetValidDateValue
*  @brief   set parameters nMaxDay and nAutoMoveMinDay according to user's input Date value
*
*  @param  nYear      YEAR value.
*  @param  nMonth     Month value.
*  @param  nDay       Day value.
*  @param  nMaxDay    the max day of such YEAR/Month.
*  @param  nAutoMoveMinDay the min day value to move focus from day field to next period of such YEAR/Month.
*  @retval            void
*/
static void FormatInputWidget_CheckLeapYearAndSetValidDateValue(u16 nYear, u16 nMonth, u16 nDay, u8 *nMaxDay, u8 *nAutoMoveMinDay);
/**
*  FormatInputWidget_UpdateDayValueifNecessary
*  @brief   if the inputted day value is larger than valid max day value of such YEAR/MONTH, update the day value to the max day value of such YEAR/MONTH.
*
*  @param  pThis      Pointer to the FormatInputWidget object
*  @retval            void
*/
static void FormatInputWidget_UpdateDayValueifNecessary(FormatInputWidget_t *pThis);
/**
*  FormatInputWidget_CorrectContent
*  @brief   Correct the value of pEditingData according to the rule of each field.
*
*  @param  pThis                Pointer to the FormatInputWidget object
*  @param  nField               The field name, for checking rule.
*  @param  pEditingData         The pointer to the editing data.
*  @param  bUpdateCurInputLen   After correct content value, reset pthis->nCurInputLen.
*  @retval            void
*/
static void FormatInputWidget_CorrectContent(FormatInputWidget_t *pThis, u8 nField, u16 *pEditingData, boolean bUpdateCurInputLen);
/**
*  FormatInputWidget_SetModelValue
*  @brief   Set model value from segments
*
*  @param  pThis                Pointer to the FormatInputWidget object
*  @retval            void
*/
static void FormatInputWidget_SetModelValue(FormatInputWidget_t *pThis);
/**
*  FormatInputWidget_SetDateModelValue
*  @brief   Set model value from segments
*
*  @param  pThis        Pointer to the FormatInputWidget object
*  @param  segments     the pointer to segments
*  @param  pDateModel   the pointer to the data in data model which will be updated
*  @retval void
*/
static void FormatInputWidget_SetDateModelValue(FormatInputWidget_t *pThis, u16* segments, MAE_DateTime_t* pDateModel);
/**
*  FormatInputWidget_SetTimeModelValue
*  @brief   Set model value from segments
*
*  @param  pThis        Pointer to the FormatInputWidget object
*  @param  segments     the pointer to segments
*  @param  pTimeModel   the pointer to the data in data model which will be updated

*  @retval void
*/
static void FormatInputWidget_SetTimeModelValue(FormatInputWidget_t *pThis, u16* segments, MAE_DateTime_t* pTimeModel);
/**
*  FormatInputWidget_SetIPModelValue
*  @brief   Set model value from segments
*
*  @param  segments     the pointer to segments
*  @param  pTimeModel   the pointer to the data in data model which will be updated

*  @retval void
*/
static void FormatInputWidget_SetIPModelValue(u16* segments, u32* pIPModel);
/**
*  FormatInputWidget_SetSegmentValueFromModel
*  @brief   Set the content value in pThis->segments according to data model
*
*  @param  pThis      Pointer to the FormatInputWidget object

*  @retval void
*/
static void FormatInputWidget_SetSegmentValueFromModel(FormatInputWidget_t *pThis);
/**
*  FormatInputWidget_SetIPSegments
*  @brief   Set the content value in  pThis->segment according to nIP
*
*  @param  pThis      Pointer to the FormatInputWidget object
*  @param  nIP        The pointer to the IP data.
*  @retval void
*/
static void FormatInputWidget_SetIPSegments(FormatInputWidget_t *pThis,  u32 *nIP);
/**
*  FormatInputWidget_SetIPSegments
*  @brief   Set the content value in pThis->segment according to the time value of pDateTime
*
*  @param  pThis      Pointer to the FormatInputWidget object
*  @param  pDateTime  The pointer to the MAE_DateTime.
*  @retval void
*/
static void FormatInputWidget_SetTimeSegments(FormatInputWidget_t *pThis, MAE_DateTime_t *pDateTime);
/**
*  FormatInputWidget_SetIPSegments
*  @brief   Set the content value in pThis->segment according to the date value of pDateTime
*
*  @param  pThis      Pointer to the FormatInputWidget object
*  @param  pDateTime  The pointer to the MAE_DateTime.
*  @retval void
*/
static void FormatInputWidget_SetDateSegments(FormatInputWidget_t *pThis, MAE_DateTime_t *pDateTime);
/**
*  FormatInputWidget_GetNextAvailableContent
*  @brief   Get next available content according to the rule of each field. This function will be called when pEditingData data is invalided.
*			And this function will return minimum available value if the pEditingData value is more then the maximum available value.
*			And this function will return maximum available value if the pEditingData value is more then the minimum available value.
*
*  @param  pThis                Pointer to the FormatInputWidget object
*  @param  nField               The field name, for checking rule.
*  @param  pEditingData         The pointer to the editing data.
*  @retval            void
*/
static void FormatInputWidget_GetNextAvailableContent(FormatInputWidget_t *pThis, u8 nField, u16 *pEditingData);

/**
*  FormatInputWidget_ViewModelNotify
*  @brief   Notify owner AP events by view model.
*
*  @param  pThis                Pointer to the FormatInputWidget object
*  @param  evtCode				event code
*  @retval            void
*/
static void FormatInputWidget_ViewModelNotify(FormatInputWidget_t *pThis, ModelEvtCode_t evtCode);

/**
*  FormatInputWidget_CalculateContentArea
*  @brief   Calculate the width and the height of drawing area.
*
*  @param  pThis                Pointer to the FormatInputWidget object
*  @param  nWidth               the width of drawing area
*  @param  nHeight              the height of drawing area
*  @retval            void
*/
static void FormatInputWidget_CalculateContentArea(FormatInputWidget_t *pThis, u32* nWidth, u32* nHeight);

/**
*  FormatInputWidget_CalculateWdgOffsetForAlignment
*  @brief Calculate and set the X, Y drawing offset for the alignment.
*
*  @param  pThis                Pointer to the FormatInputWidget object
*  @retval            void
*/
static void FormatInputWidget_CalculateWdgOffsetForAlignment(FormatInputWidget_t *pThis);

#ifdef __TOUCH_SCREEN_MMI__
/**
*  FormatInputWidget_GetTouchedSegment
*  @brief   Notify owner AP that the focused segment is changed.
*
*  @param  pThis                Pointer to the FormatInputWidget object
*  @u32    xPos                 The x-coordinates of touched point.
*  @u32    yPos                 The y-coordinates of touched point.
*  @retval u32					The touched segment index of FormatInputWidget.
*/
static u32 FormatInputWidget_GetTouchedSegment(FormatInputWidget_t *pThis, u32 xPos, u32 yPos);

/**
*  FormatInputWidget_TouchAmPmSegment
*  @brief   Notify owner AP that the focused segment is changed.
*
*  @param  pThis                Pointer to the FormatInputWidget object
*  @u32    xPos                 The x-coordinates of touched point.
*  @u32    yPos                 The y-coordinates of touched point.
*  @retval boolean				TRUE: if the touch point in AmPm segment area. FALSE: otherwise.
*/
static boolean FormatInputWidget_TouchAmPmSegment(FormatInputWidget_t *pThis, u32 xPos, u32 yPos);

#ifdef __IME_MMI_SOFTKEYBOARD__
void FormatInputWidget_SoftKeyboardWidget_ButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, SoftKeyBoardWidget_NotifyData_t *SoftKeyboardData, IWidget *pWDGSoftkeyBoard);
#endif //__IME_MMI_SOFTKEYBOARD__

#endif

static void FormatInputWidget_ChangeDateFormat(FormatInputWidget_t *pThis, DateWdgDisplayFormat_e eNewFormat);

/**
* Load resource from theme, and set them to myself.
*/
static void _FormatInputWidget_LoadResource(FormatInputWidget_t *pThis);

#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
static void _FormatInputWidget_ReloadRC(FormatInputWidget_t *pThis, DisplayMode_e nDispMode);
#endif //__AUTO_ROTATE_DISPLAY__

#ifdef __IME_MMI_SOFTKEYBOARD_7COL_UI__
void FormatInput_SoftKeyboardWidget_ViewModelListener(void *pUsrData, ModelEvent_t *pMdlEvent);
#endif //__IME_MMI_SOFTKEYBOARD_7COL_UI__

/** FormatInputSetDisableCheckHour
* @brief        Set enable/disable the hour check, default is enable
*				     If disable the check, hour can larger than 24
*
* @param[in]    pWdgTime         The Time widget
* @param[in]    bDisable         TRUE:Disable   FALSE:Enable
* @retval       none
*
*/
void FormatInputSetDisableCheckHour(IWidget *pWdgTime, boolean bDisable);

/** _FormatInputWidget_GetDigitCommonWidth
* @brief        Get Digit Common Width
*
* @param  pThis                Pointer to the FormatInputWidget object
* @retval       none
*
*/
static void _FormatInputWidget_GetDigitCommonWidth(FormatInputWidget_t *pThis);

#ifdef __MMI_IME_CSTAR_FORMAT__
void FormatInputWidget_KMX_SoftKeyboardWidget_ViewModelListener(void *pUsrData, ModelEvent_t *pMdlEvent);
#endif /*__MMI_IME_CSTAR_FORMAT__*/
#endif //__MMI_WDG_FORMATINPUT_PRIV_H__
/*=============================================================*/
// end of file
