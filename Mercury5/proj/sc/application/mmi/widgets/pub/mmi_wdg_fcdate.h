/**
*
*  FCDate is a widget that composed of several Ring-List widgets. Each Ring-List
*  displays one of date value, and one of those Ring-List widgets is a focus widget
*  that can change its first display index of item when user press up/down navigation
*  keys. User presses left/right navigation keys or touch other inside widget will change
*  the current focus widget (Ring-List widget). AP can set default, maximum, and minimum
*  date of each Ring List widget.
*
*         ex: FCDate widget
*
*      +---------------------------------+
*       |  +=====+  +---+  +---+  +---+  |
*       |  || 1 ||  | 4 |  | 7 |  | 0 |  |
*       |  || 2 ||  | 5 |  | 8 |  | 1 |  |  <= 4 Ring List Widgets, the first one is focused.
*       |  || 3 ||  | 6 |  | 9 |  | 2 |  |
*       |  +=====+  +---+  +---+  +---+  |
*       |  +-----+  +---+  +---+         |
*       |  | May |  | 1 |  | 4 |         |
*       |  | June|  | 2 |  | 5 |         |  <= 3 Ring List Widgets
*       |  | July|  | 3 |  | 6 |         |
*       |  +-----+  +---+  +---+         |
*      +---------------------------------+
*
*/

#ifndef __MMI_WDG_FC_DATE_H__
#define __MMI_WDG_FC_DATE_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_window.h"
#include "mmi_wdg_common_interface.h"

/*=============================================================*/
// type and define
/*=============================================================*/

typedef enum {
	FCD_IND_FIRST = 0,
	FCD_IND_YEAR4 = 0,		///>
	FCD_IND_YEAR3,		///>
	FCD_IND_YEAR2,		///>
	FCD_IND_YEAR1,
	FCD_IND_MONTH,
	FCD_IND_DAY2,
	FCD_IND_DAY1,
	FCD_IND_LAST = FCD_IND_DAY1,
	FCD_IND_SUM,
} _FCDIndType_e;
typedef u8 _FCDIndType_t;

#define DEFAULT_FCD_MIN_YEAR  1900      ///< default min year
#define DEFAULT_FCD_MAX_YEAR  2100      ///< default max year

/** PfnWdgFcDateWidgetDataChange
* @brief      CB register by "WdgFcDateRegisterDataChangeCb"
*             and will be trigger when the data of widget is changed; Ex,WdgFcDateSetData
*
* @param[in]  pApplet         The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData        User data ap developer setting when register CB.
* @param[in]  nEvtCode        Widget Event Code, only useful for softkey event
* @param[in]  dwParam       The data word param (NOT use now)
* @param[in]  pIWidget        The widget instance
*
*/
typedef void (*PfnWdgFcDateWidgetDataChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
/*------------------------------------------------------------------------------------------
* Interface functions
------------------------------------------------------------------------------------------*/
/** WdgFcDateCreateForWnd
* @brief        FCDate widget create function for Window
*
* @param[in]    hWin        The window handle
* @param[in]    pPos           A pointer of widget position; can't be NULL.
* @param[in]    pSize          A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID      The widget unique ID of window
* @param[in]    pDateTime      Indicate initial date time.
*
* @retval       The pointer of FCDate            Success.
* @retval       NULL                             Failed.
*
*/
IWidget* WdgFcDateCreateForWnd
(
    HWIN         hWin,
    Pos_t                 *pPos,
    WidgetSize_t          *pSize,
    u16                         nWidgetID,
    MAE_DateTime_t   *pDateTime
);
/*=============================================================*/
/** WdgFcDateCreate
* @brief        Create FCDate widget
*
* @retval       The pointer of FCDate           Success.
* @retval       NULL                            Failed.
*
*/
IWidget* WdgFcDateCreate
(
    void
);

/** WdgFcDateSetData
* @brief        Set FCDate widget date value
*
* @param[in]    pWDGFCDate        The pointer of IWidget interface object
* @param[in]    pDateTime         date time
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgFcDateSetData
(
    IWidget                 *pWDGFCDate,
    MAE_DateTime_t          *pDateTime
);

/** WdgFcDateSetMaxYear
* @brief        Set FCDate widget max year
*
* @param[in]    pWDGFCDate        The pointer of IWidget interface object
* @param[in]    nMaxYear          Indicate the FCDate widget max year
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgFcDateSetMaxYear
(
    IWidget              *pWDGFCDate,
    u32                  nMaxYear
)
{
    return WdgCommonSetProperty(pWDGFCDate, PROP_FC_DATE_WDG_SET_MAX_YEAR, (u32)nMaxYear);
}

/** WdgFcDateSetMinYear
* @brief        Set FCDate widget min year
*
* @param[in]    pWDGFCDate  The pointer of IWidget interface object
* @param[in]    nMinYear    Indicate the FCDate widget min year
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgFcDateSetMinYear
(
    IWidget              *pWDGFCDate,
    u32                  nMinYear
)
{
    return WdgCommonSetProperty(pWDGFCDate, PROP_FC_DATE_WDG_SET_MIN_YEAR, (u32)nMinYear);
}

/** WdgFcDateSetFocusInd
* @brief        Set Current FCDate focus Index
*
* @param[in]    pWDGFCDate      The pointer of IWidget interface object
* @param[in]    nFCDIndType     Focused index type; refer to _FCDIndType_e.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE void WdgFcDateSetFocusInd
(
    IWidget          *pWDGFCDate,
    _FCDIndType_e    nFCDIndType
)
{
    WdgCommonSetProperty(pWDGFCDate, PROP_FC_DATE_WDG_FOCUS_IND, (u32)nFCDIndType);
}

/** WdgFcDateGetDateValue
* @brief        Get FCDate widget date value
*
* @param[in]    pWDGFCDate        The pointer of IWidget interface object
* @param[out]   pDateTime         date time
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgFcDateGetDateValue
(
    IWidget         *pWDGFCDate,
    MAE_DateTime_t  *pDateTime
)
{
    return WdgCommonGetProperty(pWDGFCDate, PROP_FC_DATE_WDG_DATE_VALUE, (u32*)pDateTime);
}

/** WdgFcDateGetFocusInd
* @brief        Get Current FCDate focus index
*
* @param[in]    pWDGFCDate        The pointer of IWidget interface object
*
* @return    Current FCDate focus index
*
*/
_FCDIndType_e WdgFcDateGetFocusInd
(
    IWidget                 *pWDGFCDate
);

/** WdgFcDateRegisterDataChangeCb
* @brief        Register data change callback; CB will be triggered while data changed.
*
* @param[in]    pWDGFCDate        The FCDate widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgFcDateRegisterDataChangeCb
(
    IWidget                         *pWDGFCDate,
    PfnWdgFcDateWidgetDataChange pfn,
    void                            *pUserData
);

/** WdgFcDateDeregisterDataChangeCb
* @brief        Deregister data change callback
*
* @param[in]    pWDGFCDate        The FCDate widget which want to Deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgFcDateDeregisterDataChangeCb
(
    IWidget                         *pWDGFCDate,
    PfnWdgFcDateWidgetDataChange pfn,
    void                            *pUserData
);
#endif //__MMI_WDG_FC_DATE_H__
/*=============================================================*/
// end of file
