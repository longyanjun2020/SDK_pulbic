/**
 * \file    mmi_mae_input_common.h
 * \brief
 *
 * @version $Id: mmi_mae_input_common.h 40810 2009-09-18 10:28:00Z alison.chen $
 */
#ifndef __MMI_MAE_INPUT_COMMON_H__
#define __MMI_MAE_INPUT_COMMON_H__

#include "mmi_mae_common_def.h"


#include "mmi_mae_interface_def.h"
#include "mmi_mae_class.h"
#include "mmi_mae_shell.h"
#ifdef __TOUCH_SCREEN_MMI__
#include "mmi_wdg_softkeyboard.h"
#endif
#include "mmi_wdg_title.h"


#include "mmi_mae_imeassistmodel.h"
#include "mmi_mae_softkeyboard_ime_mappingtable.h"


#define DEFAULT_TEXT_COLOR			 RGBCOLOR_GRAY
#define DEFAULT_HIGHLIGHT_TEXT_COLOR RGBCOLOR_WHITE
#define DEFAULT_HIGHLIGHT_BG_COLOR	 RGBCOLOR_BLUE
#define DEFAULT_UNDERLINE_COLOR		 0xFFAEAEAE
#define DAFAULT_BGCOLOR				 RGBCOLOR_WHITE
#define DEFAULT_CURSOR_COLOR RGBCOLOR_GRAY
#define DEFAULT_BORDER_COLOR RGBCOLOR_BLACK

#define DEFAULT_MASK_CHAR			 0x002A      // Star symbol

/* used for checking every character in filename is valid or not. */
#define INPUT_COMMON_IS_VALID_FILE_NAME_CHAR(ch)   ((ch != L'\\') && (ch != L'/') && \
                            (ch != L':') && (ch != L'*') && (ch != L'?') && \
                            (ch != L'"') && (ch != L'<') && (ch != L'>') && \
                            (ch != L'|') && (ch != L'\n')&& (ch != MAE_IME_SYMBOL_LINEFEED))

#ifdef __TOUCH_SCREEN_MMI__
typedef enum
{
	SOFTKEYBOARD_STATUS_OFF = 0,
	SOFTKEYBOARD_STATUS_ON
}SoftKeyboardStatus_e;

//void InputCommon_EnableSKBSwitcher(IModel *pViewMdl, boolean bVisible);		// Removed by Leo.Tang 2009.11.06
void InputCommon_EnableSKBSwitcher(IWidget *pThis, boolean bVisible);		// Add by Leo.Tang 2009.11.06

#ifdef __IME_MMI_SOFTKEYBOARD__
//void InputCommon_UpdateSoftKeyboardIcon(IModel *pViewMdl, SoftKeyboardStatus_e eSoftKeyboardStatus);		// Removed by Leo.Tang 2009.11.07
void InputCommon_UpdateSoftKeyboardIcon(IWidget *pThis, SoftKeyboardStatus_e eSoftKeyboardStatus);	// Add by Leo.Tang 2009.11.07
__SLDPM_FREE__ SoftKeyboardStatus_e InputCommon_GetDefaultSoftKeyboardStatus(IBase *pOwner);
#endif //__IME_MMI_SOFTKEYBOARD__

#endif

typedef boolean (*pfInputFilter)(MAE_WChar);

typedef struct{
	u32             nFilter;
	pfInputFilter   fFilterFunction;
}FilterTable;

boolean InputCommon_IsInvalidFilter_DisableShiftMode(MAE_WChar nCode);
boolean InputCommon_IsInvalidFilter_DisableFileNameChar(MAE_WChar nCode);
boolean InputCommon_IsInvalidFilter_DisableSymbol(MAE_WChar nCode);
boolean InputCommon_IsInvalidFilter_DisableLineFeed(MAE_WChar nCode);
boolean InputCommon_IsInvalidFilter_DisableNumeric(MAE_WChar nCode);
boolean InputCommon_IsInvalidFilter_EnableStandardAsciiOnly(MAE_WChar nCode);
boolean InputCommon_IsInvalidFilter_EnableAsciiOnly(MAE_WChar nCode);
boolean InputCommon_IsInvalidFilter_DisablePause(MAE_WChar nCode);
boolean InputCommon_IsInvalidFilter_DisableDecimalpoints(MAE_WChar nCode);
boolean InputCommon_IsInvalidFilter_All(MAE_WChar nCode);
boolean InputCommon_IsInvalidFilter_DisableWildCard(MAE_WChar nCode);
boolean InputCommon_IsInvalidFilter_DisableForDTMF(MAE_WChar nCode);

void InputCommon_SetAssistWidgetVisible(IIMEAssistModel *pIIMEAssistModel, u32 nAsstWidetID, boolean bVisible, boolean bFixedPosition, u32 nPosX, u32 nPosY);
__SLDPM_FREE__ boolean InputCommon_IsAssistWidgetVisible(IIMEAssistModel *pIIMEAssistModel, u32 nAsstWidetID);
boolean InputCommon_IsHandledKey_ForInputRelatedWDG(u32 key);
u8 InputCommon_GetCurrentDisplayLanguageFromSetting(IBase *pOwner);
boolean InputCommon_IsValidFilter(u32 nFilterSet);

typedef enum
{
	FONT_SIZE = 0x0001,
	FONT_TYPE = 0x0002,
	TEXT_COLOR = 0x0004,
	BG_COLOR	= 0x0008,
	HIGHLIGHT_TEXT_COLOR = 0x0010,
	HIGHLIGHT_BG_COLOR= 0x0020,
	UNDERLINE_COLOR= 0x0040,
	BORDER_COLOR = 0x0080,
	CURSOR_COLOR = 0x0100,
	INACTIVE_TEXT_COLOR = 0x0200
}e_TextColorSetting;

typedef struct{
	u32 FontCat;          ///< Font category
	u32 FontSize;         ///< Font Size
	u32 FontType;         ///< Font type
	RGBColor_t nText;	  ///< text color when widget is activated.
	RGBColor_t nBG;		  // BG color
	RGBColor_t nHighlightText;  ///< highlighted text color
	RGBColor_t nHighlightBG;    ///< highlighted BG color
	RGBColor_t nUnderline;      ///< Underline color
	RGBColor_t nCursor;			///< cursor color
	RGBColor_t nBorder;			///< border color
	RGBColor_t nInactiveText;	///< text color when widget is inactivated
	u16 nTextColorUpdatedInfo;
}TextThemeProperty;

__SLDPM_FREE__ boolean InputCommon_IsThemeResReassigned(u16 nTextColorUpdatedInfo, e_TextColorSetting eTextColorID);
void InputCommon_ThemeResReassigned(u16 *nTextColorUpdatedInfo, e_TextColorSetting eTextColorID);


/*
How to add a filter?
In mmi_mae_input_common.h
Step1. Plus 1 to MAE_INPUT_FILTER_SIZE.
Step2. Define your FILTER.
In mae_input_common.c
Step3. Add the new filter in to the array au32Filter in function InputCommon_IsValidForSKBKey.
Step4. Add code to validate the SKB key in function InputCommon_IsInvalidSKBKeyAccordingToFilter.
*/

/*
How to add a filter?
Step1. Plus 1 to MAE_INPUT_FILTER_SIZE.
*/
#define MAE_INPUT_FILTER_SIZE 11

#define MAE_INPUT_FILTER_NONE	0												//disalbe all filters
#define MAE_INPUT_FILTER_DISABLE_SHIFT_MODE		(1<<0)							//disable shift mode
#define MAE_INPUT_FILTER_DISABLE_FILE_NAME_INVALID_CHAR	 (1<<1)					//disable file name invalide charact
#define MAE_INPUT_FILTER_DISABLE_SYMBOL		(1<<2)								//disable symbol
#define MAE_INPUT_FILTER_DISABLE_LINE_FEED	(1<<3)								//disable line feed
#define MAE_INPUT_FILTER_DISABLE_NUMERIC	(1<<4)								//disable all digits
#define MAE_INPUT_FILTER_DISABLE_PAUSE	    (1<<5)								//disable pause symbol
#define MAE_INPUT_FILTER_DISABLE_DECIMALPOINTS   (1<<6)							//disable decimal point
#define MAE_INPUT_FILTER_DISABLE_WILDCARD	    (1<<7)							//disable wildcard symbol
#define MAE_INPUT_FILTER_DISABLE_FOR_DTMF	    (1<<8)							//disable for DTMF

/*
How to add a filter?
Step2. Define your FILTER.
*/
#define MAE_INPUT_FILTER_ENABLE_STANDARD_ASCII_ONLY	(1<<9)		//enable ascii only
#define MAE_INPUT_FILTER_ENABLE_ASCII_ONLY	(1<<(MAE_INPUT_FILTER_SIZE-1))		//enable ascii only
#define MAE_INPUT_FILTER_ALL  0xFFFFFFFF										//enable all filters

typedef u32 MAE_INPUT_FILTER_e;

u32 InputCommon_SetFilter(u32 eFilterMask, MAE_INPUT_FILTER_e eInputFilter);
boolean InputCommon_GetFilter(u32 eFilterMask, MAE_INPUT_FILTER_e eInputFilter);
u32 InputCommon_ClearFilter(u32 eFilterMask, MAE_INPUT_FILTER_e eInputFilter);
boolean InputCommon_IsPreDefinedSymbol(MAE_WChar nCode);

#ifdef __TOUCH_SCREEN_MMI__
#ifdef __IME_MMI_SOFTKEYBOARD__
boolean InputCommon_IsValidForSKBKey(u32 nFilterMask, u32 nFilterSet, MAE_WChar nSKBKeyCode);
#endif //__IME_MMI_SOFTKEYBOARD__

#endif
#endif /* __MAE_INPUT_COMMON_H__ */

