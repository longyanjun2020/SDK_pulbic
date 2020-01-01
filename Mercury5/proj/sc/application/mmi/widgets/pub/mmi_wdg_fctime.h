/**
* @file    mmi_wdg_fctime.h
*
*  FCTime is a widget that composed of several Ring-List widgets. Each Ring-List
*  displays one of time value, and one of those Ring-List widgets is a focus widget
*  that can change its first display index of item when user presses up/down navigation
*  keys. User presses left/right navigation keys or touch other inside widget will
*  change the current focus widget (Ring-List widget). Two types of FCTime
*  widget can be used: CLSID_FCTIME_WIDGET and
*  CLSID_COUNTDOWNTIME_WIDGET.
*
*         ex: FCDate widget, CLSID_FCTIME_WIDGET type
*      +-------------------------- +
*       |  +======+  +---+  +---+  |
*       |  || 14 ||  | 4 |  | 7 |  |
*       |  || 15 ||  | 5 |  | 8 |  |  <= 3 Ring List Widgets,
*       |  || 16 ||  | 6 |  | 9 |  |       current time is 15:58
*       |  +======+  +---+  +---+  |
*       +--------------------------+
*           hour        minute
*
*
*         ex: FCDate widget, CLSID_COUNTDOWNTIME_WIDGET type
*      +----------------------------------------------+
*       |  +=====+ +---+   +---+ +---+   +---+ +---+  |
*       |  || 9 || | 9 |   | 5 | | 9 |   | 5 | | 9 |  |
*       |  || 0 || | 0 |   | 0 | | 0 |   | 0 | | 0 |  |  <= 6 Ring List Widgets
*       |  || 1 || | 1 |   | 1 | | 1 |   | 1 | | 1 |  |
*       |  +=====+ +---+   +---+ +---+   +---+ +---+  |
*      +----------------------------------------------+
*                hour         minute       second
*
*/

#ifndef __MMI_WDG_FCTIME_H__
#define __MMI_WDG_FCTIME_H__

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
#include "mmi_wdg_common_interface.h"
/*=============================================================*/
// type and define
/*=============================================================*/

typedef enum
{
    FCTIME_STYLE_FCTIME,
    FCTIME_STYLE_COUNTDOWNTIME
} FCTimeStyle_e;
typedef u8 FCTimeStyle_t;

enum {
	FCT_TIME_WDG_HOUR,
	FCT_TIME_WDG_MINUTE2,
	FCT_TIME_WDG_MINUTE1,
	FCT_TIME_WDG_AMPM,
	FCT_TIME_WDG_SUM,
};

enum {
	FCT_COUNT_TIMER_WDG_HOUR2,
	FCT_COUNT_TIMER_WDG_HOUR1,
	FCT_COUNT_TIMER_WDG_MINUTE2,
	FCT_COUNT_TIMER_WDG_MINUTE1,
	FCT_COUNT_TIMER_WDG_SECOND2,
	FCT_COUNT_TIMER_WDG_SECOND1,
	FCT_COUNT_TIMER_WDG_SUM,
};


typedef enum {
	FCT_RING_LIST_HOUR_DATA,
	FCT_RING_LIST_HOUR2_DATA,
	FCT_RING_LIST_HOUR1_DATA,
	FCT_RING_LIST_MINUTE2_DATA,
	FCT_RING_LIST_MINUTE1_DATA,
	FCT_RING_LIST_SECOND2_DATA,
	FCT_RING_LIST_SECOND1_DATA,
	FCT_RING_LIST_AMPM_DATA
} _FCTRingListData_e;
typedef u8 _FCTRingListData_t;

//H:M2M1:AM/PM
typedef enum {
	FCT_IND_FIRST = 0,
	FCT_IND_HOUR = 0,		///>
	FCT_IND_MINUTE2,		///>
	FCT_IND_MINUTE1,		///>
	FCT_IND_AMPM,
	FCT_IND_COUNT_TIMER_HOUR2,
	FCT_IND_COUNT_TIMER_HOUR1,
	FCT_IND_COUNT_TIMER_MINUTE2,
	FCT_IND_COUNT_TIMER_MINUTE1,
	FCT_IND_COUNT_TIMER_SECOND2,
	FCT_IND_COUNT_TIMER_SECOND1,
    FCT_IND_12TIME_FORMAT_LAST = FCT_IND_AMPM,
    FCT_IND_24TIME_FORMAT_LAST = FCT_IND_MINUTE1,

} _FCTIndType_e;
typedef u8 _FCTIndType_t;

/** FCT_TimeDispInfo_t
*
* @brief    
*           u16Xpos:         
*           u16Ypos:   
*           u16Width:
*           u16Height:         
*           u16IndXpos:   
*           u16IndYpos:
*           u16IndWidth:         
*           u16IndHeight:   
*           eRingListData:
*           eFCTIndType:         
*           eImageID:   
*
*/
typedef struct{
	u16 u16Xpos;
	u16 u16Ypos;
	u16 u16Width;
	u16 u16Height;
	u16 u16IndXpos;
	u16 u16IndYpos;
	u16 u16IndWidth;
	u16 u16IndHeight;
	_FCTRingListData_t eRingListData;
	_FCTIndType_t eFCTIndType;
	u32 eImageID;
}FCT_TimeDispInfo_t;

/** PfnWdgFcTimeWidgetDataChange
* @brief      CB register by "WdgFcTimeRegisterDataChangeCB"
*             and will be trigger when the data of widget is changed; Ex,WdgFcTimeSetData
*
* @param[in]  pApplet         The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData        User data ap developer setting when register CB.
* @param[in]  nEvtCode        Widget Event Code, only useful for softkey event
* @param[in]  dwParam       The data word param (NOT use now)
* @param[in]  pIWidget        The widget instance
*
*/
typedef void (*PfnWdgFcTimeWidgetDataChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

/*=============================================================*/
// functions
/*=============================================================*/

/** WdgFcTimeCreateForWnd
* @brief        FCTime widget create function for Window
*
* @param[in]    hWin        The window handle
* @param[in]    pPos           A pointer of widget position; can't be NULL.
* @param[in]    pSize          A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID      The widget unique ID of window
* @param[in]    nFCTimeStyle   Indicate to create FCTime or CountDownTime widget.
* @param[in]    pDateTime      Indicate initial date time.
*
* @retval       The pointer of FCTime           Success.
* @retval       NULL                            Failed.
*
*/

IWidget* WdgFcTimeCreateForWnd
(
    HWIN      hWin,
    Pos_t            *pPos,
    WidgetSize_t     *pSize,
    u16              nWidgetID,
    FCTimeStyle_e    nFCTimeStyle,
    MAE_DateTime_t   *pDateTime
);
/*=============================================================*/
/** WdgFcTimeCreate
* @brief        Create FCTime widget
*
* @param[in]    nFCTimeStyle        Indicate to create FCTime or CountDownTime widget.
*
* @retval       The pointer of FCTime           Success.
* @retval       NULL                            Failed.
*
*/
IWidget* WdgFcTimeCreate
(
    FCTimeStyle_e   nFCTimeStyle
);

/** WdgFcTimeSetData
* @brief        Set time value
*
* @param[in]    pWDGFCTime  The pointer of IWidget interface object
* @param[in]    pDateTime   Date time
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgFcTimeSetData
(
    IWidget                 *pWDGFCTime,
    MAE_DateTime_t          *pDateTime
);

/** WdgFcTimeGetTimeValue
* @brief        Get time value
*
* @param[in]    pWDGFCTime   The pointer of IWidget interface object
* @param[out]   pDateTime    Date time
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgFcTimeGetTimeValue
(
    IWidget                 *pWDGFCTime,
    MAE_DateTime_t          *pDateTime
)
{
    return WdgCommonGetProperty(pWDGFCTime, PROP_FC_TIME_WDG_TIME_VALUE, (u32*)pDateTime);
}

/** WdgFcTimeRegisterDataChangeCb
* @brief        Register data change callback; CB will be triggered while data changed.
*
* @param[in]    pWDGFCTime     The FCTime widget which want to set callback
* @param[in]    pfn            callback function
* @param[in]    pUserData       User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgFcTimeRegisterDataChangeCb
(
    IWidget                         *pWDGFCTime,
    PfnWdgFcTimeWidgetDataChange pfn,
    void                            *pUserData
);

/** WdgFcTimeDeregisterDataChangeCb
* @brief        Deregister data change callback
*
* @param[in]    pWDGFCTime     The FCTime widget which want to Deregister callback
* @param[in]    pfn            callback function
* @param[in]    pUserData       User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgFcTimeDeregisterDataChangeCb
(
    IWidget                         *pWDGFCTime,
    PfnWdgFcTimeWidgetDataChange pfn,
    void                            *pUserData
);

#endif //__MMI_WDG_FCTIME_H__
/*=============================================================*/
// end of file
