/**
* @file    mmi_srv_eventdb.h
* @brief  The document describes the service wrapper interface of IEventDB  
*          
*/

#ifndef __MMI_SRV_EVENTDB_H__
#define __MMI_SRV_EVENTDB_H__
/*-------------------------------------------------------------------------*/

#include "mmi_srv_client_commondefine.h"
#include "mmi_mae_eventdb_forward.h"
#include "mmi_base_util.h"

/*-------------------------------------------------------------------------*/

typedef void (* SrvEventDbEvent_Status_Change_CB)(void *pUserData, u32 nEventID);


/*-------------------------------------------------------------------------*/
/** SrvEventDbSetEventInsertedCB
 * @brief  Set CB to listen the insert calendar event notify from database. 
 *
 * @param[in]   pfnCallBack             Pointer to the callback function which listen to the event MAE_EVT_EventDB_INSERTED
 */
void SrvEventDbSetEventInsertedCB(SrvEventDbEvent_Status_Change_CB pfnCallBack);

/** SrvEventDbSetEventUpdatedCB
 * @brief  Set CB to listen the update calendar event notify from database. 
 *
 * @param[in]   pfnCallBack             Pointer to the callback function which listen to the event MAE_EVT_EventDB_UPDATED
 */
void SrvEventDbSetEventUpdatedCB(SrvEventDbEvent_Status_Change_CB pfnCallBack);

/** SrvEventDbSetEventDeletedCB
 * @brief  Set CB to listen the delete calendar event notify from database. 
 *
 * @param[in]   pfnCallBack             Pointer to the callback function which listen to the event MAE_EVT_EventDB_DELETED
 */
void SrvEventDbSetEventDeletedCB(SrvEventDbEvent_Status_Change_CB pfnCallBack);

/** SrvEventDbCreateEvent 
 * @brief       Create a new event record into database.
 *
 * @param[in]   pCalendarEvent          Pointer to instance of CalendarEvent_t to be added
 *
 * @retval MAE_RET_SUCCESS              Insert event into database successfully
 * @retval MAE_RET_FAILED               Fail to insert the event into database 
 * @retval MAE_RET_FLASH_FULL			Flash is full and not enough to use the EventDB Service
 */
MAE_Ret SrvEventDbCreateEvent(CalendarEvent_t *pCalendarEvent);

/** SrvEventDbUpdateEvent 
 * @brief       Update an event in database.
 *
 * @param[in]   pCalendarEvent          Pointer to instance of CalendarEvent_t to be updated
 *
 * @retval MAE_RET_SUCCESS              Update event into database successfully
 * @retval MAE_RET_FAILED               Fail to update the event into database
 * @retval MAE_RET_FLASH_FULL			Flash is full and not enough to use the EventDB Service
 */
MAE_Ret SrvEventDbUpdateEvent(CalendarEvent_t *pCalendarEvent);

/** SrvEventDbDeleteEvent 
 * @brief       Remove an event from database.
 *
 * @param[in]   nEventID                Pointer to id of the event to be deleted
 *
 * @retval MAE_RET_SUCCESS              Delete event from database successfully
 * @retval MAE_RET_FAILED               Fail to delete the event from database
 * @retval MAE_RET_FLASH_FULL			Flash is full and not enough to use the EventDB Service
 */
MAE_Ret SrvEventDbDeleteEvent(u32 nEventID);

/** SrvEventDbDeleteAllEvent 
 * @brief       Remove all events from database.
 *
 * @retval MAE_RET_SUCCESS              Delete event from database successfully
 * @retval MAE_RET_FAILED               Fail to delete the event from database
 * @retval MAE_RET_FLASH_FULL			Flash is full and not enough to use the EventDB Service
 */
MAE_Ret SrvEventDbDeleteAllEvent(void);

/** SrvEventDbGetEvent 
 * @brief       Get an event from database by ID.
 *              [Note]The data will alloc and copy to ppCalendarEvent; Remember to Free ppCalendarEvent by AP self
 *
 * @param[in]   nEventID                The event id for query
 * @param[out]  ppCalendarEvent         Pointer to pointer of CalendarEvent_t for getting the result
 *
 * @retval MAE_RET_SUCCESS              The event was found in database and returned
 * @retval MAE_RET_NOT_FOUND            The event id was not found in database
 * @retval MAE_RET_FLASH_FULL			Flash is full and not enough to use the EventDB Service
  */
MAE_Ret SrvEventDbGetEvent(u32 nEventID, CalendarEvent_t **ppCalendarEvent);

/** SrvEventDbGetEventIdList 
 * @brief   Search for events from database where the u32StartDateTime, u32EndDateTime of event are both 
 *          located between u32StartDateTime and u32EndDateTime.
 * 
 *          If there do not exist any event matching the query rule, a array model with no elements 
 *          was returned and MAE_RET_SUCCESS is returned.
 *          You need to release the array model if you are not going to use it anymore.
 * 
 *          If fail to execute the query, ppArray will fill with NULL.
 *          [Note]The ppArray will create in service; Remember to call ArrayRelease to release ppArray by AP self
 * 
 * @param[in]   pClient             Pointer to client owner 
 * @param[in]   nStartDateTime      Set the date range for query event, specify the start date time
 * @param[in]   nEndDateTime        Set the date range for query event, specify the end date time
 * @param[in]   eSortMode           Set the order of query result
 * @param[out]  ppArray             Pointer to pointer of the query result 
 *
 * @retval MAE_RET_SUCCESS          Query are executed successfully, note that the result may contain no event.
 * @retval MAE_RET_FLASH_FULL			Flash is full and not enough to use the EventDB Service
 */
MAE_Ret SrvEventDbGetEventIdList(u32 nStartDateTime,
                                 u32 nEndDateTime,
                                 SortMode_e eSortMode,
                                 ArrayClass_t **ppArray);

/** SrvEventDbSearchEvent 
 * @brief       Search for events from database by keyword.
 *              [Note]The ppArray will create in service; Remember to call ArrayRelease to release ppArray by AP self
 * 
 *          This interface will get event id from database where SUMMARY, LOCATION, DESCRIPTION
 *          contains the keyword. The result id(s) will be put into an array model and returns.
 *
 *          If there do not exist any event matching the query rule, an array model with no elements 
 *          was returned and MAE_RET_SUCCESS is returned.
 *          You need to release the array model if you are not going to use it anymore.
 *          If fail to execute the query, ppArray will fill with NULL.
 *          [Note]The ppArray will create in service; Remember to call ArrayRelease to release ppArray by AP self
 * 
 * @param[in]   pKeyword            Describe the keyword to be searched
 * @param[out]  ppArray             Pointer to pointer of the query result 
 *
 * @retval MAE_RET_SUCCESS          Query are executed successfully, note that the result may contain no event.
 * @retval MAE_RET_FAILED           Fail to execute the query 
 * @retval MAE_RET_FLASH_FULL		Flash is full and not enough to use the EventDB Service
 */
MAE_Ret SrvEventDbSearchEvent(MAE_WChar *pKeyword, ArrayClass_t **ppArray);

/** SrvEventDbGetEventCount
 * @brief       Query the number of events from database where the u32StartDateTime, u32EndDateTime of event are both 
 *          located between u32StartDateTime and u32EndDateTime
 * 
 * @param[in]   nStartDateTime  Set the date range for query event count, specify the start date time
 * @param[in]   nEndDateTime        Set the date range for query event count, specify the end date time
 *
 * @retval number of events match the query ; if count = ILLEGAL_EVENTCOUNT; it means it can not get count course of EventDB can not init with enough Resource
 */
u32 SrvEventDbGetEventCount(u32 nStartDateTime, u32 nEndDateTime);

/** SrvEventDbAddRepeatException
 * @brief       Add an exception range into database a for a repeat event. 
 * 
 * @param[in]   nEventID                The event id of the repeat event
 * @param[in]   nStartDateTime          Set the date range for repeat exception, specify the start date time
 * @param[in]   nEndDateTime            Set the date range for repeat exception, specify the end date time
 *
 * @retval MAE_RET_SUCCESS              Add repeat exception into database successfully.
 * @retval MAE_RET_FAILED               Fail to add repeat exception into database
 * @retval MAE_RET_FLASH_FULL			Flash is full and not enough to use the EventDB Service
 */
MAE_Ret SrvEventDbAddRepeatException(u32 nEventID, u32 nStartDateTime, u32 nEndDateTime);

/** SrvEventDbGetRepeatException
 * @brief       Get all repeat exception ranges for a repeat event. 
 *              [Note]The ppArray will create in service; Remember to call ArrayRelease to release ppArray by AP self
 * 
 *          The elements stored into the output array model is VCALDateRange_t.
 *          If there do not exist any exception range for the event, an array model with no elements 
 *          was returned and MAE_RET_SUCCESS is returned.
 *          You need to release the array model if you are not going to use it anymore.
 * 
 *          If fail to execute the query, ppArray will fill with NULL.
 *          [Note]The ppArray will create in service; Remember to call ArrayRelease to release ppArray by AP self
 * 
 * @param[in]   nEventID                The event id of the repeat event
 * @param[out]  ppArray                 Pointer to pointer of the query result 
 *
 * @retval MAE_RET_SUCCESS              Get repeat exception from database successfully.
 * @retval MAE_RET_FAILED               Fail to get repeat exception from database.
 * @retval MAE_RET_FLASH_FULL			Flash is full and not enough to use the EventDB Service
 */
MAE_Ret SrvEventDbGetRepeatException(u32 nEventID, ArrayClass_t **ppArray);

/*-------------------------------------------------------------------------*/
#endif /* __MMI_SRV_EVENTDB_H__ */


