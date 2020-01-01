/**
* @file    mmi_srv_vcalstore.h
* @brief   vCalendar store service wrapper header file
*          
*/

#ifndef __MMI_SRV_VCALSTORE_H__
#define __MMI_SRV_VCALSTORE_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_srv_client_commondefine.h"
#include "mmi_vcalstoresrv.h"
#include "mmi_base_util.h"

/*=============================================================*/
// Type definition of callBack function
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

/** SrvVCalStoreCreateEvent
@brief  Create a new event in the event database.

@param[in]      pCalendarEvent  Pointer to calendar event
 
@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVCalStoreCreateEvent(CalendarEvent_t *pCalendarEvent);

/** SrvVCalStoreCreateEventEx
@brief  Create a new event in the event database with an I/O param.

@param[in]      pCalendarEvent  Pointer to calendar event
@param[in]      eCreateMethod.bForceCreateEvent  create event even exceeds the limit of alarm at the same time.
                eCreateMethod.eOutput  The sub-result of creating an event.
 
@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVCalStoreCreateEventEx(CalendarEvent_t *pCalendarEvent, EventCreateParam_t *pCreateParam);

/** SrvVCalStoreUpdateEvent
@brief  Update an existing event in the event database.
 
@param[in]      pCalendarEvent  Pointer to calendar event
@param[in]      bIsResetAlarm   If reset alarm
 
@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVCalStoreUpdateEvent(CalendarEvent_t *pCalendarEvent, boolean bIsResetAlarm);

/** SrvVCalStoreUpdateEventEx
@brief  Update an existing event in the event database with an I/O param.
 
@param[in]      pCalendarEvent  Pointer to calendar event
@param[in]      pUpdateParam.bIsResetAlarm  If reset alarm
                eUpdateMethod.eOutput  The sub-result of updating an event.
 
@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVCalStoreUpdateEventEx(CalendarEvent_t *pCalendarEvent, EventUpdateParam_t *pUpdateParam);

/** SrvVCalStoreDeleteEvent
@brief  Delete an event from the event database with the given event uid.
 
@param[in]      nUID            Uid of the event
 
@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVCalStoreDeleteEvent(u32 nUID);

/** SrvVCalStoreDeleteAllEvent
@brief  Delete all events from the event database.
 
@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVCalStoreDeleteAllEvent(void);

/** SrvVCalStoreGetEvent
@brief  Get an event from the event database with the given event uid.
        [Note]The data will alloc and copy to ppCalendarEvent; Remember to Free ppCalendarEvent by AP self
 
@param[in]      nUID            Uid of the event (Get form CalendarEvent_t.nUID)
@param[out]     ppCalendarEvent Pointer to pointer of event
 
@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVCalStoreGetEvent(u32 nUID, CalendarEvent_t **ppCalendarEvent);

/** SrvVCalStoreGetEnumEventCount
@brief  Return the number of enumerated events.
 
@retval  The number of enumerated events.
*/
u32 SrvVCalStoreGetEnumEventCount(void);

/** SrvVCalStoreEnumInitEvent
@brief  Initialize the enumeration of the events within a given date range.
 
@param[in]      pDateRange		  
@param[in]      bIsListAllOccurrence
 
@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVCalStoreEnumInitEvent(DateRange_t *pDateRange, boolean bIsListAllOccurrence);

/** SrvVCalStoreEnumNextEvent
@brief  Retrieve the next event in the enumeration. SrvVCalStoreEnumInitEvent() function must be called before this function call.
        [Note] This ppCalenEventInfo will control in Srv, User shall not free this pointer ppCalenEventInfo.
 
@param[in]      pDateRange
@param[in]      ppCalenEventInfo  Pointer to calendar event

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVCalStoreEnumNextEvent(DateRange_t *pDateRange, CalenEventInfo_t **ppCalenEventInfo);

/** SrvVCalStoreAddRepeatException
@brief  Add an exception date range for a repeat event.
 
@param[in]      pCalendarEvent		Pointer to calendar event
@param[in]      nStartDateTimeSecs	The seconds of start date time
@param[in]      nEndDateTimeSecs	The seconds of end date time
 
@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVCalStoreAddRepeatException(CalendarEvent_t *pCalendarEvent,
                                       u32             nStartDateTimeSecs,
                                       u32             nEndDateTimeSecs);

/** SrvVCalStoreSetNewAlarmTime
@brief  Set the next alarm time of an event.
 
@param[in]      pCalendarEvent  Pointer to calendar event
 
@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVCalStoreSetNewAlarmTime(CalendarEvent_t *pCalendarEvent);

/** SrvVCalStoreListEvent
@brief  Query events within a specified date range.
         [Note]The ppArray will create in service; Remember to call ArrayRelease to release ppArray by AP self
 
@param[in]      pDateRange
@param[out]     ppArray
@param[in]      bIsListAllDayEvent
 
@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVCalStoreListEvent(DateRange_t   *pDateRange,
                              ArrayClass_t   **ppArray,
                              boolean       bIsListAllDayEvent);

/** SrvVCalStoreClearEnumEvent
@brief  Clear the enumeration of the events.



*/
void SrvVCalStoreClearEnumEvent(void);

/** SrvVCalStoreGetTotalEventCount
@brief  Return the total event number in DB.
 
@retval    Total Event Count
*/
u32 SrvVCalStoreGetTotalEventCount(void);

/** SrvVCalStoreGetEventIDList
@brief  Get list of event id from DB.
        [Note]The ppArray will create in service; Remember to call ArrayRelease to release ppArray by AP self

@param[out]     ppArray

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVCalStoreGetEventIDList(ArrayClass_t **ppArray);

/** SrvVCalStoreIsSetNextAlarm
@brief  Check if need to set the next alarm time of a repeat calendar event.
 
@param[in]      pCalendarEvent      Pointer to calendar event

@retval  TRUE    
@retval  FALSE   
*/
boolean SrvVCalStoreIsSetNextAlarm(CalendarEvent_t *pCalendarEvent);

/** SrvVCalStoreEnumInitEventIndicator
@brief  Initialize the enumeration of the event indicators within a given date range.
 
@param[in]      pDateRange		  
@param[in]      bIsListAllOccurrence

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvVCalStoreEnumInitEventIndicator(DateRange_t *pDateRange, boolean bIsListAllOccurrence);

/*-----------------------------------------------------*/
#endif //__MMI_SrvVCalStoreH__

