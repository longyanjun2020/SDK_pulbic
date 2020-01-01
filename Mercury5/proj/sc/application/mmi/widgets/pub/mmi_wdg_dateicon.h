#ifndef __MMI_WDG_DATEICON_H__
#define __MMI_WDG_DATEICON_H__
/* ===========================================================*/
// Description
/* ===========================================================*/
/**
*   The purpose of DateIcon widget is to display a calendar, digital clock, or analog
*   clock by setting DateIconStyle_e element. There are three styles totally  and the
*   sketches are as followings. The detailed type of three styles, like fonts color or
*   text height, can also be adjusted to user's definition. The difference from Date widget
*   is DateIcon is an icon present, not string format instead.
*
*    DATEICON_STYLE_DATE style
*   +--------------+
*   |    month     |
*   |              |    <= for calendar
*   |     day      |
*   +--------------+
*
*    DATEICON_STYLE_TIME style
*   +-------------+
*   |  hour: min  |   <= for digital clock
*   +-------------+
*
*   DATEICON_STYLE_CLOCK style
*   +------------+
*   |    |       |
*   |    |       |
*   |    .------ |   <= for analog clock
*   |            |
*   +------------+
*/


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
#include "mmi_mae_clock.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef enum
{
    DATEICON_STYLE_DATE = 1,
    DATEICON_STYLE_TIME,
    DATEICON_STYLE_CLOCK
} DateIconStyle_e;

/** WdgDateIconTimeStyle_t
*
* @brief    nTextColor              Used in date icon style, text color
*           nOutlineColor           Used in date icon style, text outline color
*           nFontType               Used in date icon style, text font type
*           nFontType               Used in date icon style, text font category
*
*/
typedef struct
{
     RGBColor_t              nTextColor;
     RGBColor_t              nOutlineColor;
     FontType_t              nFontType;
     FontCategory_t          nFontCategory;
} WdgDateIconTimeStyle_t;

/*=============================================================*/
// functions
/*=============================================================*/
/** WdgDateIconCreateForWnd
* @brief        DateIcon widget create function for Window
*
* @param[in]    hWnd     The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
* @param[in]    nDateIconStyle      The date icon style
*
* @retval       The pointer of DateIcon pointer         Success.
* @retval       NULL                                    Failed.
*
*/
IWidget* WdgDateIconCreateForWnd
(
    HWIN                    hWin,
    Pos_t                          *pPos,
    WidgetSize_t                   *pSize,
    u16                            nWidgetID,
    DateIconStyle_e                nDateIconStyle
);

/** WdgDateIconCommon_SetTimeStyle
* @brief        Only available when style is set DATEICON_STYLE_TIME, indicate the the color, font type, and font category of month text
*
* @param[out]   pWDGDateIcon   The pointer to date icon widget
* @param[in]    pTimeStyle     Indicate the color, font type, and font category of time text
*
* @retval       none
*
*/
void WdgDateIconCommon_SetTimeStyle
(
    IWidget                *pWDGDateIcon,
    WdgDateIconTimeStyle_t *pTimeStyle
);

/** WdgDateIconSetData
* @brief        Set display data for DateIcon widget.
*               Specific data for DateIcon widget.
*
* @param[in]    pWDGDateIcon   Pointer to the DateIcon widget
* @param[in]    pSpecData      Display data of DateIcon Widget.
* @param[in]    pfFree         Free CB function for free data allocate by User while widget destroy.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
MAE_Ret WdgDateIconSetData
(
    IWidget         *pWDGDateIcon,
    MAE_DateTime_t  *pSpecData,
    PfnDataFree     pfFree
);

/** WdgDateIconCreate
* @brief        Create DateIcon widget
*
* @param[in]    nDateIconStyle              Indicate to create date icon or time icon or clock icon style
*
* @retval       The pointer of DateIcon     Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgDateIconCreate
(
    DateIconStyle_e nDateIconStyle
);

/** WdgDateIconSetTimeTextColor
* @brief        Only available when style is set DATEICON_STYLE_TIME. Set DateIcon widget text color
*
* @param[in]    pWDGDateIcon The pointer of IWidget interface object
* @param[in]    nTextColor   DateIcon widget month text color
*
* @retval       none
*
*/
void WdgDateIconSetTimeTextColor
(
    IWidget                 *pWDGDateIcon,
    RGBColor_t              nTextColor
);

/** WdgDateIconSetTimeOutlineColor
* @brief        Only available when style is set DATEICON_STYLE_TIME. Set DateIcon widget outline color
*
* @param[in]    pWDGDateIcon The pointer of IWidget interface object
* @param[in]    nTextColor   DateIcon widget month outline color
*
* @retval       none
*
*/
void WdgDateIconSetTimeOutlineColor
(
    IWidget                 *pWDGDateIcon,
    RGBColor_t              nTextColor
);

/** WdgDateIconSetTimeFontType
* @brief        Only available when style is set DATEICON_STYLE_TIME. Set DateIcon widget font type
*
* @param[in]    pWDGDateIcon The pointer of IWidget interface object
* @param[in]    nFontType    DateIcon widget month font type
*
* @retval       none
*
*/
void WdgDateIconSetTimeFontType
(
    IWidget                 *pWDGDateIcon,
    FontType_t              nFontType
);

/** WdgDateIconSetTimeFontCategory
* @brief        Only available when style is set DATEICON_STYLE_TIME. Set DateIcon widget font category
*
* @param[in]    pWDGDateIcon      The pointer of IWidget interface object
* @param[in]    nFontCategory     DateIcon widget month font category
*
* @retval       none
*
*/
void WdgDateIconSetTimeFontCategory
(
    IWidget                 *pWDGDateIcon,
    FontCategory_t          nFontCategory
);

/** WdgDateIconSetAutoUpdate
* @brief        Set DateIcon widget auto update on / off.
*               Time/Clock will automatically update to display according to the system timer.
*
* @param[in]    pWDGDateIcon  The pointer of IWidget interface object
* @param[in]    bAutoUpdate   Indicate DateIcon widget auto update on / off
*
* @retval       none
*
*/
void WdgDateIconSetAutoUpdate
(
    IWidget                 *pWDGDateIcon,
    boolean                 bAutoUpdate
);

/** WdgDateIconSetDisplayDateTime
* @brief        Display the Date icon or Not.
*
* @param[in]    pWDGDateIcon   The pointer of IWidget interface object
* @param[in]    bDisplay       True : display, False : disappear.
*
* @retval       none
*
*/
void WdgDateIconSetDisplayDateTime
(
    IWidget                 *pWDGDateIcon,
    boolean                 bDisplay
);

/** WdgDateIconSetTimeFormat
* @brief        Only available in time icon style, indicate DateIcon widget display date time format.
*
* @param[in]    pWDGDateIcon  The pointer of IWidget interface object
* @param[in]    nTimeFormat   Indicate DateIcon widget display date time format
*
* @retval       none
*
*/
void WdgDateIconSetTimeFormat
(
    IWidget                 *pWDGDateIcon,
    MAE_TimeFormat_e        nTimeFormat
);

#endif //__MMI_WDG_DATEICON_H__
/*=============================================================*/
// end of file
