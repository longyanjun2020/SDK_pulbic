/**
* @file    mmi_wdg_formatinput.h
* @brief   This file defines the interface of format input widget.
*          Format input widget supports 3 kinds of data format:
*          Date Widget: 
*              CLSID: CLSID_DATEWIDGET
*              Format: YYYY/MM/DD
*              Content: pointer to MAE_DateTime_t
*          Time Widget:
*              CLSID: CLSID_TIMEWIDGET
*              Format: HH:MM  (24 hour format) or  HH:MM AM/PM    (12 Hour format)
*              Content: pointer to MAE_DateTime_t
*          IP Widget:
*              CLSID: CLSID_IPWIDGET
*              Format: XXX.XXX.XXX.XXX
*              Content: pointer to u32
* @version $Id: mmi_wdg_formatinput.h 11565 2008-06-12 04:01:07Z steve.lee $
*/

#ifndef __MMI_WDG_FORMATINPUT_H__
#define __MMI_WDG_FORMATINPUT_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef enum 
{
    AM = 0,
    PM
}TimePeriod_e;

enum{
	DATEWDG_DISPLAY_FORMAT_YYYYMMDD = 0,
	DATEWDG_DISPLAY_FORMAT_MMDDYYYY,
	DATEWDG_DISPLAY_FORMAT_DDMMYYYY,
};
typedef u8 DateWdgDisplayFormat_e;

#define DEFAULT_SEGMENT_SIZE_DATE 3         ///< Date format: YYYY/MM/DD
#define DEFAULT_DATE_SEPERATER 0x002F           ///< '/'

#define DEFAULT_MIN_YEAR  1900      ///< default min year
#define DEFAULT_MAX_YEAR  2100      ///< default max year

#define FORMATINPUT_BORDER_SIZE	MAKE_BORDER_SIZE(1,1,1,1)

/*=============================================================*/
// interface functions
/*=============================================================*/
/* All interface function are declared in the following files :
    mmi_wdg_date.h 
	mmi_wdg_ip.h
	mmi_wdg_time.h
	*/

/** FormatInputSetDisableCheckLunarFebruary
* @brief        Set enable/disable the lunar February validation check, default is enable
*				     If disable the check, 2/30 is always valid
*
* @param[in]    pWdgDate         The Date widget
* @param[in]    bDisable         TRUE:Disable   FALSE:Enable
* @retval       none
*
*/
void FormatInputSetDisableCheckLunarFebruary(IWidget *pWdgDate, boolean bDisable);

#ifdef __TOUCH_SCREEN_MMI__
#ifdef __IME_MMI_SOFTKEYBOARD__
#ifdef __MMI_IME_CSTAR_FORMAT__
void FormatInputWidgetGetKMXConfig(IWidget *pWdg, IWidget **ppWdgSKB, void **ppconfig); 
#endif
#endif
#endif

#endif //__MMI_WDG_FORMATINPUT_H__
/*=============================================================*/
// end of file
