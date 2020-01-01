/**
* @file    mmi_srv_taskdb.h
* @brief
*
*/

#ifndef __MMI_SRV_TASKDB_H__
#define __MMI_SRV_TASKDB_H__


/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_mae_taskdb.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef void *hTaskDB;

/*=============================================================*/
// functions
/*=============================================================*/


/** SrvTaskDbCreateObject
* @brief  The interface is used to create TaskDB object
* 
* @param[in]      pTaskDB             Pointer to the TaskDB Object.
* @param[in]      pOwner              The owner instance
* 
* @retval MAE_RET_SUCCESS       If successful.
* @retval MAE_RET_FAILED        If an error happen.
* @retval MAE_RET_BAD_PARAM		Bad parameter.
*/
MAE_Ret SrvTaskDbCreateObject(hTaskDB* ppTaskDB, void *pOwner);

/** SrvTaskDbDestroyObject
* @brief  The interface is used to destroy TaskDB object
* 
* @param[in]      pTaskDB             Pointer to the TaskDB Object.
* @param[in]      pOwner              The owner instance
* 
* @retval MAE_RET_SUCCESS       If successful.
*/
MAE_Ret SrvTaskDbDestroyObject(hTaskDB pTaskDB, void *pOwner);


/** SrvTaskDbMoveNext
* @brief  Switch the task object to next one
* Change to next task in the list. If the current is the latest one,
* it should return TASKDB_NOMORE and nothing happens.
*
* There may be more than one task inside the object because there may exist
* many records when you are using SrvTaskDbMgrListAllSorted to get all tasks
* The client can use SrvTaskDbMoveNext to get all the task information from
* the returning pTaskDB object of SrvTaskDbMoveNext.
*
* This interface will affect the result of the following interfaces:
* (Because current data inside the object is switched)
* ITaskDB_SetAttr (and related setter interface)
* ITaskDB_GetAttr (and related getter interface)
*
* @param[in]       pTaskDB                     Pointer to the TaskDB handle.
*
* @retval MAE_RET_SUCCESS                      Success
* @retval TASKDB_NOMORE                        no more
*/
MAE_Ret SrvTaskDbMoveNext(hTaskDB pTaskDB);

/** SrvTaskDbSetID
* @brief  Set the Unique ID for this task
*
* @param[in]       pTaskDB                      Pointer to the TaskDB Object.
* @param[in]       pTID                         Pointer to the TaskDB ID
*/
MAE_Ret SrvTaskDbSetID(hTaskDB pTaskDB, u32 *pTID);

/** SrvTaskDbSetContent
* @brief  Set the new task description to TaskDB
*
* @param[in]           pTaskDB                      Pointer to the TaskDB handle.
* @param[in]           pContent                     Pointer to a string with the new task description
*/
MAE_Ret SrvTaskDbSetContent(hTaskDB pTaskDB, MAE_WChar *pContent);

/** SrvTaskDbSetDescription
* @brief  Set the new task description to TaskDB
*
* @param[in]           pTaskDB                      Pointer to the TaskDB handle.
* @param[in]           pDescription                     Pointer to a string with the new task description
*/
#ifdef __APP_MMI_TODOLIST_VTODO__
MAE_Ret SrvTaskDbSetDescription(hTaskDB pTaskDB, MAE_WChar *pDescription);

/** SrvTaskDbSetLocation
* @brief  Set the new task description to TaskDB
*
* @param[in]           pTaskDB                      Pointer to the TaskDB handle.
* @param[in]           pLocation                     Pointer to a string with the new task Location
*/
MAE_Ret SrvTaskDbSetLocation(hTaskDB pTaskDB, MAE_WChar *pLocation);
#endif

/** SrvTaskDbSetCheckFlag
* @brief  Set the flag with checked/unchecked
*
* @param[in]       pTaskDB                      Pointer to the TaskDB handle.
* @param[in]       pCheckStatus                 Pointer to the Flag with Checked/Unchecked
*/
MAE_Ret SrvTaskDbSetCheckFlag(hTaskDB pTaskDB, MAE_TaskDB_CheckStatus_e *pCheckStatus);

/** SrvTaskDbSetPriority
* @brief  Set the task's priority
*
* @param[in]           pTaskDB                      Pointer to the TaskDB handle.
* @param[in]           pPriority                    Pointer to the priority with Low/Normal/High,
*/
MAE_Ret SrvTaskDbSetPriority(hTaskDB pTaskDB, MAE_TaskDB_PriorityLevel_e *pPriority);

/** SrvTaskDbSetReminder
* @brief  Set the reminder on or off
*
* @param[in]       pTaskDB                      Pointer to the TaskDB handle.
* @param[in]       pReminderFlg                 Pointer to the Flag with On/Off
*/
MAE_Ret SrvTaskDbSetReminder(hTaskDB pTaskDB, MAE_TaskDB_ReminderFlag_e *pReminderFlg);

/** SrvTaskDbSetDueTime
* @brief  Set the due time for this to-do item
*
* @param[in]           pTaskDB                      Pointer to the TaskDB handle.
* @param[in]           pDueTime                     Pointer to the due time for this to-do item
*/
MAE_Ret SrvTaskDbSetDueTime(hTaskDB pTaskDB, u32 *pDueTime);

/** SrvTaskDbSetModifyTime
* @brief  Set the task's last modify time
*
* @param[in]       pTaskDB                      Pointer to the TaskDB handle.
* @param[in]       pModifiedTime                Pointer to the task's last modify time
*/
MAE_Ret SrvTaskDbSetModifyTime(hTaskDB pTaskDB, u32 *pModifiedTime);

/** SrvTaskDbSetSnoozeTimes
* @brief  Set the task's snooze times
*
* @param[in]           pTaskDB                      Pointer to the TaskDB handle.
* @param[in]           pSnoozeTimes                 Pointer to the task's snooze times
*/
MAE_Ret SrvTaskDbSetSnoozeTimes(hTaskDB pTaskDB, u32 *pSnoozeTimes);

/** SrvTaskDbGetID
* @brief  Get the Unique ID for this task
*
* @param[in]       pTaskDB                      Pointer to the TaskDB handle.
* @param[in]       ppTID                        Reference to the result of  the TaskDB ID
*/
MAE_Ret SrvTaskDbGetID(hTaskDB pTaskDB, u32 **ppTID);

/** SrvTaskDbGetContent
* @brief  Get the task title to TaskDB
*		  [Note] This content string will free in Srv, User shall not free this pointer ppContent.
*
* @param[in]           pTaskDB                      Pointer to the TaskDB handle.
* @param[in]           ppContent                    Reference to the result of  a string with the task description
*/
MAE_Ret SrvTaskDbGetContent(hTaskDB pTaskDB, MAE_WChar **ppContent);

/** SrvTaskDbGetDescription
* @brief  Get the task description to TaskDB
*		  [Note] This description string will free in Srv, User shall not free this pointer ppContent.
*
* @param[in]           pTaskDB                      Pointer to the TaskDB handle.
* @param[in]           ppDescription                    Reference to the result of  a string with the task description
*/
MAE_Ret SrvTaskDbGetDescription(hTaskDB pTaskDB, MAE_WChar **ppDescription);

/** SrvTaskDbGetLocation
* @brief  Get the task Location to TaskDB
*		  [Note] This Location string will free in Srv, User shall not free this pointer ppLocation.
*
* @param[in]           pTaskDB                      Pointer to the TaskDB handle.
* @param[in]           ppLocation                    Reference to the result of  a string with the task location
*/
MAE_Ret SrvTaskDbGetLocation(hTaskDB pTaskDB, MAE_WChar **ppLocation);

/** SrvTaskDbGetCheckFlag
* @brief  Get the task's check status
*
* @param[in]           pTaskDB                      Pointer to the TaskDB handle.
* @param[in]           ppCheckStatus                Reference to the result of  the check status
*/
MAE_Ret SrvTaskDbGetCheckFlag(hTaskDB pTaskDB, MAE_TaskDB_CheckStatus_e **ppCheckStatus);

/** SrvTaskDbGetPriority
* @brief  Get the task's priority
*
* @param[in]           pTaskDB                      Pointer to the TaskDB handle.
* @param[in]           ppPriority                   Reference to the result of  the task's priority
*/
MAE_Ret SrvTaskDbGetPriority(hTaskDB pTaskDB, MAE_TaskDB_PriorityLevel_e **ppPriority);

/** SrvTaskDbGetReminder
* @brief  Get the reminder status
* 
* @param[in]           pTaskDB                      Pointer to the TaskDB handle.
* @param[in]           ppReminderFlg                Reference to the result of  the reminder's flag
*/
MAE_Ret SrvTaskDbGetReminder(hTaskDB pTaskDB, MAE_TaskDB_ReminderFlag_e **ppReminderFlg);

/** SrvTaskDbGetDueTime
* @brief  Get the due time for this to-do item
*
* @param[in]           pTaskDB                      Pointer to the TaskDB handle.
* @param[in]           ppDueTime                    Reference to the result of  the due time for this to-do item
*/
MAE_Ret SrvTaskDbGetDueTime(hTaskDB pTaskDB, u32 **ppDueTime);

/** SrvTaskDbGetModifyTime
* @brief  Get the task's last modify time
*
* @param[in]           pTaskDB                      Pointer to the TaskDB handle.
* @param[in]           ppModifiedTime               Reference to the result of  the task's last modify time
*/
MAE_Ret SrvTaskDbGetModifyTime(hTaskDB pTaskDB, u32 **ppModifiedTime);

/** SrvTaskDbGetSnoozeTimes
* @brief  Get the task's snooze times
*
* @param[in]           pTaskDB                      Pointer to the TaskDB handle.
* @param[in]           ppSnoozeTimes                Reference to the result of  the task's snooze times
*/
MAE_Ret SrvTaskDbGetSnoozeTimes(hTaskDB pTaskDB, u32 **ppSnoozeTimes);


#endif // __MMI_SRV_TASKDB_H__

