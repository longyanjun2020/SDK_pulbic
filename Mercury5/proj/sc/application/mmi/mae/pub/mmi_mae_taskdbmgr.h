/**
* @file mae_taskdbmgrh
* @brief   The document describes the interface of ITaskDBMgr
* ITaskDBMgr is the manager of ITask, it management the add/del/update/query of task(to-do list) records
* in database.
*
* @author  nick.chou@mstarsemi.com
* @version $Id: mmi_mae_taskdbmgr.h 1684 2009-08-29 16:28:08Z zinc.chen $
*/
#ifndef __MMI_MAE_TASKDBMGR_H__
#define __MMI_MAE_TASKDBMGR_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_taskdb_typedef.h"
#include "mmi_mae_taskdb.h"

typedef enum
{
    MAE_TASKDBMGR_MASK_INSERTED = 0x01,		///< Indicate that a new task was added
    MAE_TASKDBMGR_MASK_UPDATED = 0x02,		///< Indicate that a task was updated
    MAE_TASKDBMGR_MASK_DELETED = 0x04,		///< Indicate that a task was removed
    MAE_TASKDBMGR_MASK_ALL = (s32)0xFFFFFFFF
} MAE_TaskDBMgr_Notify_e;

/**
* ITaskDBMgr interface definition
*/
#define INHERIT_ITaskDBMgr(IName) \
	INHERIT_IBase(IName); \
	u32 (*AddTask)		( IName *pITaskDBMgr, ITaskDB * pITaskDB);\
	u32 (*DeleteTask)	( IName *pITaskDBMgr, ITaskDB * pITaskDB);\
	u32 (*Save)			( IName *pITaskDBMgr, ITaskDB * pITaskDB);\
    u32 (*ListAllSorted)( IName* pITaskDBMgr,ITaskDB **pRetTaskDB,  TASKDB_FIELDS_e FieldID[], u8 FieldCount,  IBase* Owner);\
	u32 (*FindTaskByID) ( IName* pITaskDBMgr, u32 TaskID, ITaskDB **ret,  IBase* Owner );\
    u32 (*RegisterNotify)	(IName *pITaskDBMgr, void *listener, u32 mask);\
    u32 (*DeRegisterNotify)	(IName *pITaskDBMgr, void *listener, u32 mask)

DEFINE_INTERFACE(ITaskDBMgr);

#define ITaskDBMgr_AddRef(p)				GET_FUNCTBL(p, ITaskDBMgr)->AddRef(p)
#define ITaskDBMgr_Release(p)				GET_FUNCTBL(p, ITaskDBMgr)->Release(p)
#define ITaskDBMgr_QueryInterface(p,s,t)	GET_FUNCTBL(p, ITaskDBMgr)->QueryInterface(p,s,t)

/**
 * Add a new task into database
 *
 * @param p pointer to instance of ITaskDBMgr
 * @param s pointer to instance of ITaskDB to be added
 * @return MAE_Ret
 */
#define ITaskDBMgr_AddTask(p,s)				GET_FUNCTBL(p, ITaskDBMgr)->AddTask(p, s)

/**
 * Remove a task from database
 *
 * @param p pointer to instance of ITaskDBMgr
 * @param s pointer to instance of ITaskDB to be removed
 * @return MAE_Ret
 */
#define ITaskDBMgr_DeleteTask(p,s)			GET_FUNCTBL(p, ITaskDBMgr)->DeleteTask(p, s)

/**
 * Update a existing task in database
 *
 * @param p pointer to instance of ITaskDBMgr
 * @param s pointer to instance of ITaskDB to be removed
 * @return MAE_Ret
 */
#define ITaskDBMgr_Save(p,s)				GET_FUNCTBL(p, ITaskDBMgr)->Save(p,s)

/**
 * Query all task from database
 *
 * @param p pointer to instance of ITaskDBMgr
 * @param s [out] pointer to pointer of ITask for getting the output ITask address
 * @param t task db fields for sorting
 * @param u number of task db fiedls for sorting
 * @param v instance of caller for ADDREF for returning the ITask object
 * @return MAE_Ret
 */
#define ITaskDBMgr_ListAllSorted(p,s,t,u,v)	GET_FUNCTBL(p, ITaskDBMgr)->ListAllSorted(p,s,t,u,v)

/**
 * Get the specific task by ID from database
 *
 * @param p pointer to instance of ITaskDBMgr
 * @param s task id
 * @param t [out] pointer to pointer of ITask for getting the output ITask address
 * @param u instance of caller for ADDREF for returning the ITask object
 * @return MAE_Ret
 */
#define ITaskDBMgr_FindTaskByID(p,s,t,u)	GET_FUNCTBL(p, ITaskDBMgr)->FindTaskByID(p,s,t,u)

/**
 * @brief Register task db related event, such as add/del/update
 *
 * The listener should implement IHandler interface to handle related events.
 * Refer to MAE_TaskDBMgr_Notify_e for mask parameter
 *
 * @see ITaskDBMgr_DeRegisterNotify
 * @param  pNotifier        Pointer to the notifier structure
 * @param  listener         The instance of the one which want to register this notifier.
 * @param  mask             An 32 bits mask, providing 32 types of thing which user want to register.
 *                          Ref to MAE_TaskDBMgr_Notify_e
 * @retval MAE_RET_SUCCESS  SUCCESS
 * @retval MAE_RET_BAD_PARAM Bad parameter
 */
#define ITaskDBMgr_RegisterNotify(pITaskDBMgr,listener,mask)	GET_FUNCTBL(pITaskDBMgr, ITaskDBMgr)->RegisterNotify(pITaskDBMgr,listener,mask)

/**
 * @brief Deregister task db related event
 *
 * Refer to MAE_TaskDBMgr_Notify_e for mask parameter
 *
 * @see ITaskDBMgr_RegisterNotify
 * @param  pNotifier        Pointer to the notifier structure
 * @param  listener         The instance of the one which want to deregister this notifier.
 * @param  mask             An 32 bits mask, providing 32 types of thing which user want to deregister.
 *                          If mask is 0xfffffff, it would clear all mask for this listener.
 *                          Ref to MAE_TaskDBMgr_Notify_e
 * @retval MAE_RET_SUCCESS  SUCCESS, It is legal to deregister a 0 mask and it wouldn't have any effect.
 * @retval MAE_RET_BAD_PARAM Bad parameter, ot DeReregister an instance without registered before.
 */
#define ITaskDBMgr_DeRegisterNotify(pITaskDBMgr,listener,mask)	GET_FUNCTBL(pITaskDBMgr, ITaskDBMgr)->DeRegisterNotify(pITaskDBMgr,listener,mask)

MAE_Ret MAETaskDBMgr_New(u32 nClsID, void **ppObj);


/*-------------------------------------------------------------------------*/
#endif /* __MAE_TASKDBMGR_H__ */

