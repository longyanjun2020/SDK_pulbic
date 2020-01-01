/**
* @file    mmi_wdg_event.h
* @version $Id: mmi_wdg_event.h 13288 2008-08-14 11:48:55Z lena.lin $
* @brief   
* <Description>
*
* <Class ID>
*     CLSID_EVENTWIDGET.
*
*/
#ifndef __MMI_WDG_EVENT_H__
#define __MMI_WDG_EVENT_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_window.h"
#include "mmi_mae_view_wrapper.h"
#include "mmi_wdg_common_interface.h"
#include "mmi_wdg_image_text_image.h"
/*=============================================================*/
// type and define
/*=============================================================*/

/** EvtTime_t
*
* @brief    This data structure is used for storing hour and minute of start date time or end date time.
*           nHour:         
*           nMinute:
*
*/
typedef struct
{
	u8 nHour;
	u8 nMinute;
} EvtTime_t;

/** EvtWdgLayoutInfo_t
*
* @brief    
*           tBGColor:         
*           tBorderColor:   
*           nBorderPixelSize:
*
*/
typedef struct  
{
	RGBColor_t  tBGColor;
	RGBColor_t  tBorderColor;
	u8          nBorderPixelSize;
} EvtWdgLayoutInfo_t;

/** EvtWdgSelectInfo_t
*
* @brief    
*           nEventUID:         
*           bIsGroupEvent:
*           tStartTime:         
*           tEndTime:
*
*/
typedef struct  
{
	u32         nEventUID;
	boolean     bIsGroupEvent;
	EvtTime_t   tStartTime;
	EvtTime_t   tEndTime;
} EvtWdgSelectInfo_t;

/** PfnWdgEventFocusSelect
* @brief      CB register by "WdgEventRegisterFocusSelectCb"
*             and will be trigger when the Focus of widget is changed; Ex,click arrows or press "Action Key"
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pEventInfo        The info of focus select, refer to EvtWdgSelectInfo_t
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgEventFocusSelect) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode,EvtWdgSelectInfo_t *pEventInfo,IWidget *pWidget);

/*=============================================================*/
// functions
/*=============================================================*/
/** WdgEventCreateForWnd
* @brief        Event widget create function for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
*
* @retval       The pointer of Event          Success.
* @retval       NULL                          Failed.
*
*/
IWidget* WdgEventCreateForWnd
(
    HWIN         hWin,
    Pos_t              *pPos,
    WidgetSize_t        *pSize,
    u16                 nWidgetID
);
/*=============================================================*/
/** WdgEventCreate
* @brief        Create Event widget
*
* @retval       The pointer of Event          Success.
* @retval       NULL                          Failed.
*
*/
IWidget* WdgEventCreate
(
    void
);

/** WdgEventSetEventUid
* @brief        Set the Event UID
*
* @param[in]    pWDGEvent         The pointer of IWidget interface object
* @param[in]    nEventUID         Event UID
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE void WdgEventSetEventUid
(
    IWidget                 *pWDGEvent,
    u32                     nEventUID
)
{
    WdgCommonSetProperty(pWDGEvent, PROP_EVENT_WDG_EVENT_UID, (u32)nEventUID);
}

/** WdgEventSetSummaryInfo
* @brief        Set the event summary info
*
* @param[in]    pWDGEvent         The pointer of IWidget interface object
* @param[in]    pImageTextInfo    The pointer of ImageTextInfo with the event summary info
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgEventSetSummaryInfo
(
    IWidget                 *pWDGEvent,
    ImageTextInfo           *pImageTextInfo
)
{
    return WdgCommonSetProperty(pWDGEvent, PROP_EVENT_WDG_SUMMARY_INFO, (u32)pImageTextInfo);
}

/** WdgEventSetStartTime
* @brief        Set the start time
*
* @param[in]    pWDGEvent         The pointer of IWidget interface object
* @param[in]    pStartTime        A pointer of EvtTime_t with the start time
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgEventSetStartTime
(
    IWidget                 *pWDGEvent,
    EvtTime_t               *pStartTime
)
{
    return WdgCommonSetProperty(pWDGEvent, PROP_EVENT_WDG_START_TIME, (u32)pStartTime);
}

/** WdgEventSetEndTime
* @brief        Set the end time
*
* @param[in]    pWDGEvent         The pointer of IWidget interface object
* @param[in]    pEndTime          A pointer of EvtTime_t with the end time
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgEventSetEndTime
(
    IWidget                 *pWDGEvent,
    EvtTime_t               *pEndTime
)
{
    return WdgCommonSetProperty(pWDGEvent, PROP_EVENT_WDG_END_TIME, (u32)pEndTime);
}

/** WdgEventSetEventRangeColor
* @brief        Set the color of the event range
*
* @param[in]    pWDGEvent         The pointer of IWidget interface object
* @param[in]    nColor            the color of event range
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE void WdgEventSetEventRangeColor
(
    IWidget                 *pWDGEvent,
    RGBColor_t              nColor
)
{
    WdgCommonSetProperty(pWDGEvent, PROP_EVENT_WDG_EVENT_RANGE_COLOR, (u32)nColor);
}

/** WdgEventSetSummaryTextColor
* @brief        Set the text color of summary
*
* @param[in]    pWDGEvent         The pointer of IWidget interface object
* @param[in]    nTextColor        The text color of summary
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE void WdgEventSetSummaryTextColor
(
    IWidget                 *pWDGEvent,
    RGBColor_t              nTextColor
)
{
    WdgCommonSetProperty(pWDGEvent, PROP_EVENT_WDG_SUMMARY_TEXT_COLOR, (u32)nTextColor);
}

/** WdgEventSetSingleEventLayoutInfo
* @brief        Set the info of the single event layout
*
* @param[in]    pWDGEvent         The pointer of IWidget interface object
* @param[in]    pLayoutInfo       The pointer of EvtWdgLayoutInfo_t with the single event layout info
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgEventSetSingleEventLayoutInfo
(
    IWidget                 *pWDGEvent,
    EvtWdgLayoutInfo_t      *pLayoutInfo
)
{
    return WdgCommonSetProperty(pWDGEvent, PROP_EVENT_WDG_SINGLE_EVENT_LAYOUT_INFO, (u32)pLayoutInfo);
}

/** WdgEventSetGroupEventLayoutInfo
* @brief        Set the info of the group event layout
*
* @param[in]    pWDGEvent         The pointer of IWidget interface object
* @param[in]    pLayoutInfo       The pointer of EvtWdgLayoutInfo_t with the group event layout info
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgEventSetGroupEventLayoutInfo
(
    IWidget                 *pWDGEvent,
    EvtWdgLayoutInfo_t      *pLayoutInfo
)
{
    return WdgCommonSetProperty(pWDGEvent, PROP_EVENT_WDG_GROUP_EVENT_LAYOUT_INFO, (u32)pLayoutInfo);
}

/** WdgEventSetFocusEventLayoutInfo
* @brief        Set the info of the focus event layout
*
* @param[in]    pWDGEvent         The pointer of IWidget interface object
* @param[in]    pLayoutInfo       The pointer of EvtWdgLayoutInfo_t with the focus event layout info
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgEventSetFocusEventLayoutInfo
(
    IWidget                 *pWDGEvent,
    EvtWdgLayoutInfo_t      *pLayoutInfo
)
{
    return WdgCommonSetProperty(pWDGEvent, PROP_EVENT_WDG_FOCUS_EVENT_LAYOUT_INFO, (u32)pLayoutInfo);
}

/** WdgEventSetOverlapCount
* @brief        Set how many event is overlap on this time slot
*
* @param[in]    pWDGEvent         The pointer of IWidget interface object
* @param[in]    nOverlapCount     The number of events which are overlap on this time slot
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgEventSetOverlapCount
(
    IWidget                 *pWDGEvent,
    u32                     nOverlapCount
)
{
    return WdgCommonSetProperty(pWDGEvent, PROP_EVENT_WDG_OVERLAP_COUNT, (u32)nOverlapCount);
}

/** WdgEventSetAlarmExist
* @brief        Set this event has alarm or not
*
* @param[in]    pWDGEvent         The pointer of IWidget interface object
* @param[in]    bAlarmExist       This event has alarm or not
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgEventSetAlarmExist
(
    IWidget                 *pWDGEvent,
    boolean                 bAlarmExist
)
{
    return WdgCommonSetProperty(pWDGEvent, PROP_EVENT_WDG_ALARM_EXIST, (u32)bAlarmExist);
}

/** WdgEventGetTimeSlotPosY
* @brief        Get the Time Slot Y position
*
* @param[in]    pWDGEvent         The pointer of IWidget interface object
*
* @return       Y position of time slot
*
*/

u32 WdgEventGetTimeSlotPosY
(
    IWidget                 *pWDGEvent
);

/** WdgEventGetStartTime
* @brief        Get the start time
*
* @param[in]    pWDGEvent         The pointer of IWidget interface object
* @param[out]   pStartTime        A pointer of EvtTime_t with result of the start time
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgEventGetStartTime
(
    IWidget                 *pWDGEvent,
    EvtTime_t               *pStartTime
)
{
    return WdgCommonGetProperty(pWDGEvent, PROP_EVENT_WDG_START_TIME, (u32*)pStartTime);
}

/** WdgEventGetEndTime
* @brief        Get the end time
*
* @param[in]    pWDGEvent         The pointer of IWidget interface object
* @param[out]   pEndTime          A pointer of EvtTime_t with result of the end time
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgEventGetEndTime
(
    IWidget                 *pWDGEvent,
    EvtTime_t               *pEndTime
)
{
    return WdgCommonGetProperty(pWDGEvent, PROP_EVENT_WDG_END_TIME, (u32*)pEndTime);
}

/** WdgEventGetTimeSlotBlockSize
* @brief        Get the block size of time slot
*
* @param[in]    pWDGEvent             The pointer of IWidget interface object
*
* @return       Block size of time slot
*
*/
u8 WdgEventGetTimeSlotBlockSize
(
    IWidget                 *pWDGEvent
);

/** WdgEventRegisterFocusSelectCb
* @brief        Register callback : For event widget, CB will be triggered when user selects item.
*
* @param[in]    pWDGEvent         The Event widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotton when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgEventRegisterFocusSelectCb
(
    IWidget                 *pWDGEvent,
    PfnWdgEventFocusSelect  pfn,
    void                    *pUserData
);

/** WdgEventDeregisterFocusSelectCb
* @brief        Deregister callback : For event widget, CB will be triggered when user selects item.
*
* @param[in]    pWDGEvent         The Event widget which want to deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotton when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgEventDeregisterFocusSelectCb
(
    IWidget                 *pWDGEvent,
    PfnWdgEventFocusSelect  pfn,
    void                    *pUserData
);
#endif //__MMI_WDG_EVENT_H__
/*=============================================================*/
// end of file
