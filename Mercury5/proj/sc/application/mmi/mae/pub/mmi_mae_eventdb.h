/**
 * @file mmi_mae_eventdb.h
 * @brief   The document describes the interface of IEventDB
 * IEventDB represent event record(s) in calendar application.
 *
 * @author  nick.chou@mstarsemi.com
 * @version $Id: mmi_mae_eventdb.h 1684 2009-08-29 16:28:08Z zinc.chen $
 */
#ifndef __MMI_MAE_EVENTDB_H__
#define __MMI_MAE_EVENTDB_H__
/*-------------------------------------------------------------------------*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_eventdb_forward.h"
///COMMON Module Header
#include "mmi_base_util.h"
/*-------------------------------------------------------------------------*/

#define INHERIT_IEventDB(IName) \
	INHERIT_IBase(IName); \
    u32 (*CreateEvent)				(IName* pIEventDB, CalendarEvent_t* pCalendarEvent); \
    u32 (*UpdateEvent)				(IName* pIEventDB, CalendarEvent_t* pCalendarEvent); \
    u32 (*DeleteEvent)				(IName* pIEventDB, u32 nEventUID); \
    u32 (*DeleteAllEvent)			(IName* pIEventDB); \
    u32 (*GetEvent)					(IName* pIEventDB, u32 nEventUID, CalendarEvent_t **ppCalendarEvent); \
    u32 (*GetEventIdList)			(IName* pIEventDB, u32 nStartDateTime, u32 nEndDateTime, SortMode_e nSortMode, ArrayClass_t** ppArray, IBase *pOwner ); \
    u32 (*SearchEvent)				(IName* pIEventDB, MAE_WChar* pKeyword, ArrayClass_t** ppArray, IBase *pOwner );\
    u32 (*GetEventCount)			(IName* pIEventDB, u32 nStartDateTime, u32 nEndDateTime); \
    u32 (*AddRepeatException)		(IName* pIEventDB, u32 nEventUID, u32 nStartDateTime, u32 nEndDateTime); \
    u32 (*GetRepeatException)		(IName* pIEventDB, u32 nEventUID, ArrayClass_t** pArray , IBase *pOwner); \
    u32 (*RegisterNotify)			(IName *pIEventDB, void *listener, u32 mask);\
    u32 (*DeRegisterNotify)			(IName *pIEventDB, void *listener, u32 mask);\
    u32 (*DeleteException)		        (IName* pIEventDB, u32 nEventUID)

DEFINE_INTERFACE(IEventDB);

#define IEventDB_AddRef(p)					GET_FUNCTBL(p, IEventDB)->AddRef(p)
#define IEventDB_Release(p)					GET_FUNCTBL(p, IEventDB)->Release(p)
#define IEventDB_QueryInterface(p,s,t)		GET_FUNCTBL(p, IEventDB)->QueryInterface(p,s,t)

/**
 * Create a new event record into database
 *
 * @param p pointer to instance of IEventDB
 * @param s pointer to instance of CalendarEvent_t to be added
 * @return MAE_RET_SUCCESS Insert event into database successfully
 *         MAE_RET_OUT_OF_MEMORY out of memory
 *         MAE_RET_FAILED fail to insert the event into database
 */
#define IEventDB_CreateEvent(p,s)			GET_FUNCTBL(p, IEventDB)->CreateEvent(p,s)

/**
 * Update a existing event in database
 *
 * @param p pointer to instance of IEventDB
 * @param s pointer to instance of CalendarEvent_t to be updated
 * @return MAE_RET_SUCCESS Update event in database successfully
 *         MAE_RET_OUT_OF_MEMORY out of memory
 *         MAE_RET_FAILED fail to update the event in database
 */
#define IEventDB_UpdateEvent(p,s)			GET_FUNCTBL(p, IEventDB)->UpdateEvent(p,s)

/**
 * Remove a existing event from database
 *
 * @param p pointer to instance of IEventDB
 * @param s id of the event to be removed
 * @return MAE_RET_SUCCESS Delete event from database successfully
 *         MAE_RET_OUT_OF_MEMORY out of memory
 *         MAE_RET_FAILED fail to delete the event in database
 */
#define IEventDB_DeleteEvent(p,s)			GET_FUNCTBL(p, IEventDB)->DeleteEvent(p,s)

/**
 * Remove a existing event execption from database
 *
 * @param p pointer to instance of IEventDB
 * @param s id of the event to be removed
 * @return MAE_RET_SUCCESS Delete event from database successfully
 *         MAE_RET_OUT_OF_MEMORY out of memory
 *         MAE_RET_FAILED fail to delete the event in database
 */
#define IEventDB_DeleteException(p,s)			GET_FUNCTBL(p, IEventDB)->DeleteException(p,s)

/**
 * Remove all events from database
 *
 * @param p pointer to instance of IEventDB
 * @return MAE_RET_SUCCESS Delete events from database successfully
 *         MAE_RET_OUT_OF_MEMORY out of memory
 *         MAE_RET_FAILED fail to delete events in database
 */
#define IEventDB_DeleteAllEvent(p)			GET_FUNCTBL(p, IEventDB)->DeleteAllEvent(p)

/**
 * Get event from database by ID
 *
 * @param p pointer to instance of IEventDB
 * @param event id for query
 * @param [out] pointer of pointer of CalendarEvent_t for getting the result
 * @return MAE_RET_SUCCESS The event was found in database and returned
 *         MAE_RET_NOT_FOUND The event id was not found in database
 *         MAE_RET_FAILED fail to get the event from database
 */
#define IEventDB_GetEvent(p,s,t)			GET_FUNCTBL(p, IEventDB)->GetEvent(p,s,t)

/**
 * Search for events from database where the nStartDateTime, nEndDateTime of event are both
 * located between nStartDateTime and nEndDateTime
 *
 * If there do not exist any event matching the query rule, a array model with no elements
 * was returned and MAE_RET_SUCCESS is returned.
 * You need to release the array model if you are not going to use it anymore.
 *
 * If fail to execute the query, ppArray will fill with NULL
 *
 * @param p pointer to instance of IEventDB
 * @param nStartDateTime
 * @param nEndDateTime
 * @param nSortMode
 * @param [out] ppArray
 * @param pOwner owner instance for ADDREF to the query result
 * @return MAE_RET_SUCCESS Query are executed successfully, note that the result may contain no event.
 *         MAE_RET_FAILED fail to execute the query
 */
#define IEventDB_GetEventIdList(p,s,t,u,v,w)	GET_FUNCTBL(p, IEventDB)->GetEventIdList(p,s,t,u,v,w)

/**
 * Search for events by pKeyword from database.
 *
 * This interface will get event id from database where SUMMARY, LOCATION, DESCRIPTION
 * contains the keyword. The result id(s) will be put into a array model and returns.
 *
 * If there do not exist any event matching the query rule, a array model with no elements
 * was returned and MAE_RET_SUCCESS is returned.
 * You need to release the array model if you are not going to use it anymore.
 *
 * If fail to execute the query, ppArray will fill with NULL
 *
 * @param p pointer to instance of IEventDB
 * @param pKeyword
 * @param [out] ppArray
 * @param pOwner owner instance for ADDREF to the query result
 * @return MAE_RET_SUCCESS Query are executed successfully, note that the result may contain no event.
 *         MAE_RET_FAILED fail to execute the query
 */
#define IEventDB_SearchEvent(p,s,t,w)			GET_FUNCTBL(p, IEventDB)->SearchEvent(p,s,t,w)

/**
 * Get the number of events from database where the nStartDateTime, nEndDateTime of event are both
 * located between nStartDateTime and nEndDateTime
 *
 * @see IEventDB_GetEvent
 * @param p pointer to instance of IEventDB
 * @param nStartDateTime
 * @param nEndDateTime
 * @return number of events match the query; if count = ILLEGAL_EVENTCOUNT; it's illegal count
 */
#define IEventDB_GetEventCount(p,s,t)			GET_FUNCTBL(p, IEventDB)->GetEventCount(p,s,t)

/**
 * Add a exception rule into database a for a repeated event.
 *
 * @see IEventDB_GetRepeatException
 * @param p pointer to instance of IEventDB
 * @param nEventUID
 * @param nStartDateTime
 * @param nEndDateTime
 * @return MAE_RET_SUCCESS add the record into database successfully
 *         MAE_RET_OUT_OF_MEMORY out of memory during the operation
 *         MAE_RET_FAILED fail to add the record into database
 */
#define IEventDB_AddRepeatException(p,s,t,u) GET_FUNCTBL(p, IEventDB)->AddRepeatException(p,s,t,u)

/**
 * Get all exception rules for a specific event
 *
 * The elements stored into the output array model is VCALDateRange_t.
 * If there do not exist any exception rules for the event, a array model with no elements
 * was returned and MAE_RET_SUCCESS is returned.
 * You need to release the array model if you are not going to use it anymore.
 *
 * If fail to execute the query, ppArray will fill with NULL
 *
 * @see IEventDB_AddRepeatException
 * @param p pointer to instance of IEventDB
 * @param nEventUID
 * @param ppArray
 * @param pOwner
 * @return MAE_RET_SUCCESS
 */
#define IEventDB_GetRepeatException(p,s,t,u)	 GET_FUNCTBL(p, IEventDB)->GetRepeatException(p,s,t,u)

/**
 * Register for event db related events such as add/remove/update
 *
 * The listener should implement IHandler interface to handle related events.
 * Refer to MAE_EventDB_Notify_e for mask parameter
 *
 * @see IEventDB_DeRegisterNotify
 * @param  pNotifier        Pointer to the notifier structure
 * @param  listener         The instance of the one which want to register this notifier.
 * @param  mask             An 32 bits mask, providing 32 types of thing which user want to register.
 *                          Ref to MAE_EventDB_Notify_e
 * @retval MAE_RET_SUCCESS  SUCCESS
 * @retval MAE_RET_BAD_PARAM Bad parameter
 */
#define IEventDB_RegisterNotify(pIEventDB,listener,mask)	GET_FUNCTBL(pIEventDB, IEventDB)->RegisterNotify(pIEventDB,listener,mask)

/**
 * Deregister event db related events.
 *
 * Refer to MAE_EventDB_Notify_e for mask parameter
 *
 * @see IEventDB_RegisterNotify
 * @param  pNotifier        Pointer to the notifier structure
 * @param  listener         The instance of the one which want to deregister this notifier.
 * @param  mask             An 32 bits mask, providing 32 types of thing which user want to deregister.
 *                          If mask is 0xfffffff, it would clear all mask for this listener.
 *                          Ref to MAE_EventDB_Notify_e
 * @retval MAE_RET_SUCCESS  SUCCESS, It is legal to deregister a 0 mask and it wouldn't have any effect.
 * @retval MAE_RET_BAD_PARAM Bad parameter, or DeReregister an instance without registered before.
 */
#define IEventDB_DeRegisterNotify(pIEventDB,listener,mask)	GET_FUNCTBL(pIEventDB, IEventDB)->DeRegisterNotify(pIEventDB,listener,mask)
/*-------------------------------------------------------------------------*/

void MAE_EventDB_Init(void);

MAE_Ret MAEEventDB_New(MAE_ClsId nClsID, void **ppObj);

#endif /* __MMI_MAE_EVENTDB_H__ */


