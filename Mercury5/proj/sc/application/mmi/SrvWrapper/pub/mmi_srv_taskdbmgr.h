/**
* @file    mmi_srv_taskdbmgr.h
* @brief
*
*/

#ifndef __MMI_SRV_TASKDBMGR_H__
#define __MMI_SRV_TASKDBMGR_H__


/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_mae_taskdbmgr.h"
#include "mmi_srv_taskdb.h"

/*=============================================================*/
// type and define
/*=============================================================*/

typedef void (*SrvTaskDbMgrInsertedCB)(void *pUserdata, u32 nTID);
typedef void (*SrvTaskDbMgrUpdatedCB)(void *pUserdata, u32 nTID);
typedef void (*SrvTaskDbMgrDeletedCB)(void *pUserdata, u32 nTID);


/*=============================================================*/
// functions
/*=============================================================*/
/** SrvTaskDbMgrAddTask
* @brief  Add a new task into database
* 
* @param[in]       pTaskDB                 Pointer to TaskDB Object
* 
* @retval MAE_RET_SUCCESS                  If successful
* @retval MAE_RET_FAILED                   If Fail to prepare insert statement / insert fail.
*/
MAE_Ret SrvTaskDbMgrAddTask(hTaskDB pTaskDB);

/** SrvTaskDbMgrDeleteTask
* @brief  Remove a task from database
*
* @param[in]       pTaskDB                 Pointer to TaskDB Object to be removed
*
* @retval MAE_RET_SUCCESS                  If successful
* @retval MAE_RET_FAILED                   If an error happen.
*/
MAE_Ret SrvTaskDbMgrDeleteTask(hTaskDB pTaskDB);

/** SrvTaskDbMgrSave
* @brief  Update a existing task in database
*
* @param[in]       pTaskDB                     Pointer to TaskDB Object
*
* @retval MAE_RET_SUCCESS                  Success
* @retval MAE_RET_FAILED                   If an error happen.
*/
MAE_Ret SrvTaskDbMgrSave(hTaskDB pTaskDB);

/** SrvTaskDbMgrListAllSorted
* @brief  Query all task from database
*
* @param[out]          ppRetTaskDB             pointer to ITaskDB  for getting the output ITask address
* @param[in]           eFieldID[]              sorted by which property(task db field)
* @param[in]           nFieldCount             number of task db fields for sorting
*/
MAE_Ret SrvTaskDbMgrListAllSorted(hTaskDB *ppRetTaskDB, TASKDB_FIELDS_e eFieldID[], u8 nFieldCount);

/** SrvTaskDbMgrFindTaskByID
* @brief  Set the task's priority
*
* @param[out]          ppRetTaskDB             pointer to ITaskDB  for getting the output ITask address
* @param[in]           nTaskID                 The unique ID for the task which want to find
*/
MAE_Ret SrvTaskDbMgrFindTaskByID(u32 nTaskID, hTaskDB *ppRetTaskDB);

/** SrvTaskDbMgrSetInsertedCB
* @brief  The interface is used to Set CB which will trigger after adding a new task into database
*
* @param[in]      pfnCallBack                     a call back function which trigger after added a new task into database
*/
void SrvTaskDbMgrSetInsertedCB(SrvTaskDbMgrInsertedCB pfnCallBack);

/** SrvTaskDbMgrSetUpdatedCB
* @brief  The interface is used to Set CB which will trigger after updating a existing task in database
*
* @param[in]      pfnCallBack                     a call back function which trigger after updated a existing task in database
*/
void SrvTaskDbMgrSetUpdatedCB(SrvTaskDbMgrUpdatedCB pfnCallBack);

/** SrvTaskDbMgrSetDeletedCB
* @brief  The interface is used to Set CB which will trigger after removing a task from database
*
* @param[in]      pfnCallBack                     a call back function which trigger after removed a task from database
*/
void SrvTaskDbMgrSetDeletedCB(SrvTaskDbMgrDeletedCB pfnCallBack);

#endif // __MMI_SRV_TASKDBMGR_H__

