/**
mae * @file mmi_mae_taskdb.h
* @brief   The document describes the interface of ITaskDB
* ITaskDB represent record(s) of to-do list in database.
*
* @author  nick.chou@mstarsemi.com
* @version $Id: mmi_mae_taskdb.h 639 2009-04-15 13:33:34Z mark.yang $
*/
#ifndef __MMI_MAE_TASKDB_H__
#define __MMI_MAE_TASKDB_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_taskdb_typedef.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TASKDB_NTASKID_SIZE							(sizeof(u32))
#define TASKDB_NSNOOZETIMES_SIZE					(sizeof(u32))
#define TASKDB_PCONTENT_SIZE						((sizeof(MAE_WChar))*26)
#define TASKDB_NCHECKSTATUS_SIZE					(sizeof(u8))
#define TASKDB_NPRIORITY_SIZE						(sizeof(u8))
#define TASKDB_NREMINDERFLG_SIZE					(sizeof(u8))
#define TASKDB_NDUETIME_SIZE						(sizeof(u32))
#define TASKDB_NMODIFIEDTIME_SIZE					(sizeof(u32))
#ifdef __APP_MMI_TODOLIST_VTODO__
#define TASKDB_PDESCRIPTION_SIZE					((sizeof(MAE_WChar))*26)
#define TASKDB_PLOCATION_SIZE					    ((sizeof(MAE_WChar))*26)

#define TASKDB_RECORD_SIZE	\
	(TASKDB_NTASKID_SIZE+TASKDB_NSNOOZETIMES_SIZE+TASKDB_PCONTENT_SIZE+TASKDB_NCHECKSTATUS_SIZE+TASKDB_NPRIORITY_SIZE+\
	TASKDB_NREMINDERFLG_SIZE+TASKDB_NDUETIME_SIZE+TASKDB_NMODIFIEDTIME_SIZE+TASKDB_PDESCRIPTION_SIZE+TASKDB_PLOCATION_SIZE)

#define TASKDB_COLUMN_NUM							10
#else
#define TASKDB_RECORD_SIZE	\
	(TASKDB_NTASKID_SIZE+TASKDB_NSNOOZETIMES_SIZE+TASKDB_PCONTENT_SIZE+TASKDB_NCHECKSTATUS_SIZE+TASKDB_NPRIORITY_SIZE+\
	TASKDB_NREMINDERFLG_SIZE+TASKDB_NDUETIME_SIZE+TASKDB_NMODIFIEDTIME_SIZE)

#define TASKDB_COLUMN_NUM							8
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct MAETaskDB_t_
{
	u32 nTaskID;				/**< Unique ID for this task */
	MAE_WChar *pContent;		/**< Task description */
	u8 nCheckStatus;			/**< Checked/Unchecked, value ref to enum _MAE_TaskDB_CheckStatus */
	u8 nPriority;			/**< Low/Normal/High, value ref to enum _MAE_TaskDB_PriorityLevel */
	u8 nReminderFlg;			/**< On/Off, value ref to enum _MAE_TaskDB_ReminderFlag */
	u32 nDueTime;			/**< Due time for this to-do item */
	u32 nModifiedTime ;		/**< Last modify time */
	u32 nSnoozeTimes;		/**< Snooze time */
#ifdef __APP_MMI_TODOLIST_VTODO__
    MAE_WChar *pDescription; /** Description for the Todo (optional) */
    MAE_WChar *pLocation;  /** Location for the Todo (optional) */
#endif
	struct MAETaskDB_t_ *pNext;	/**< (internal usage) Pointer to next task db instance */
} MAETaskDB_t;

typedef enum
{
    ASC,
    DESC
}ListOrder_e;

/**
* ITaskDB Interfaces
*/
#define INHERIT_ITaskDB(IName) \
	INHERIT_IBase(IName); \
	u32 (*SetAttr)		(IName *pITaskDB, TASKDB_FIELDS_e FieldID, void * NewValue );\
	u32 (*GetAttr)		(IName *pITaskDB, TASKDB_FIELDS_e FieldID, void **RetValue);\
	u32 (*Init)			(IName *pITaskDB, MAETaskDB_t *TaskDB);\
	u32 (*MoveNext)		(IName *pITaskDB)

DEFINE_INTERFACE(ITaskDB);

/**
 * Add object reference
 */
#define ITaskDB_AddRef(p)				GET_FUNCTBL(p, ITaskDB)->AddRef(p)

/**
 * Release object
 */
#define ITaskDB_Release(p)				GET_FUNCTBL(p, ITaskDB)->Release(p)

/**
 * Query if this object supports a the specific interface
 */
#define ITaskDB_QueryInterface(p,s,t)	GET_FUNCTBL(p, ITaskDB)->QueryInterface(p,s,t)

/**
 * Set attributes for current task
 *
 * You can use the following helper macro to set the attributes instead of ITaskDB_SetAttr:
 *  ITASKDB_SetID
 *  ITASKDB_SetContent
 *  ITASKDB_SetCheckFlag
 *  ITASKDB_SetPriority
 *  ITASKDB_SetReminder
 *  ITASKDB_SetDueTime
 *  ITASKDB_SetModifyTime
 *  ITASKDB_SetSnoozeTimes
 *  ITASKDB_Description
 *  ITASKDB_Location
 *
 * @param p pointer to instance of ITask
 * @param s attribute Id, begins from TASKDBATTR_BASE end to TASKDBATTR_MAX
 * @param t pointer to the new value for this attribute
 * @return MAE_RET_SUCCESS Get attribute ok
 *         MAE_RET_FAILED Fail to connect to database to get related information
 *         MAE_RET_NOT_SUPPORTED Attribute is not support
 */
#define ITaskDB_SetAttr(p,s,t)			GET_FUNCTBL(p, ITaskDB)->SetAttr(p,s,t)

/**
 * Get attributes for current task
 *
 * You can use the following helper macro to get the attributes instead of ITaskDB_GetAttr:
 *  ITASKDB_GetID
 *  ITASKDB_GetContent
 *  ITASKDB_GetCheckFlag
 *  ITASKDB_GetPriority
 *  ITASKDB_GetReminder
 *  ITASKDB_GetDueTime
 *  ITASKDB_GetModifyTime
 *  ITASKDB_GetSnoozeTimes
 *  ITASKDB_GetDescription
 *  ITASKDB_GetLocation
 *
 * @param p pointer to instance of ITask
 * @param s attribute Id, begins from TASKDBATTR_BASE end to TASKDBATTR_MAX
 * @param t pointer to the new value for this attribute
 * @return MAE_RET_SUCCESS Get attribute ok
 *         MAE_RET_FAILED Fail to connect to database to get related information
 *         MAE_RET_NOT_SUPPORTED Attribute is not support
 */
#define ITaskDB_GetAttr(p,s,t)			GET_FUNCTBL(p, ITaskDB)->GetAttr(p,s,t)

/**
 * (internal function, to be moved to private area)
 */
#define ITaskDB_Init(p,s)				GET_FUNCTBL(p, ITaskDB)->Init(p,s)

/**
 * Switch the task object to next one.
 *
 * Change to next contain in the list. If the current is the latest one,
 * it should return TASKDB_NOMORE and nothing happens.
 *
 * There may more than one task inside the object because there may exist
 * many records when you are using ITaskDBMgr_ListAllSorted to get all tasks
 * The client can use ITaskDB_MoveNext to get all the task information from
 * the returning ITask object of ITaskDB_MoveNext.
 *
 * This interface will affect the result of the following interfaces:
 * (Because current data inside the object is switched)
 *   ITaskDB_SetAttr (and related setter interface)
 *   ITaskDB_GetAttr (and related getter interface)
 *
 * @param p pointer to instance of ITask
 */
#define ITaskDB_MoveNext(p)				GET_FUNCTBL(p, ITaskDB)->MoveNext(p)

/* Attribute getter functions */
#define ITASKDB_GetID(itaskdb, ppRet)   ITaskDB_GetAttr(itaskdb, TASKDBATTR_ID, ppRet)
#define ITASKDB_GetContent(itaskdb, ppRet)   ITaskDB_GetAttr(itaskdb, TASKDBATTR_CONTENT, ppRet)
#define ITASKDB_GetCheckFlag(itaskdb, ppRet)   ITaskDB_GetAttr(itaskdb, TASKDBATTR_CHECKSTATUS, ppRet)
#define ITASKDB_GetPriority(itaskdb, ppRet)   ITaskDB_GetAttr(itaskdb, TASKDBATTR_PRIORITY, ppRet)
#define ITASKDB_GetReminder(itaskdb, ppRet)   ITaskDB_GetAttr(itaskdb, TASKDBATTR_REMINDERFLG, ppRet)
#define ITASKDB_GetDueTime(itaskdb, ppRet)   ITaskDB_GetAttr(itaskdb, TASKDBATTR_DUE_TIME, ppRet)
#define ITASKDB_GetModifyTime(itaskdb, ppRet)   ITaskDB_GetAttr(itaskdb, TASKDBATTR_MODIFIED_TIME, ppRet)
#define ITASKDB_GetSnoozeTimes(itaskdb, ppRet)   ITaskDB_GetAttr(itaskdb, TASKDBATTR_SNOOZETIMES, ppRet)
#ifdef __APP_MMI_TODOLIST_VTODO__
#define ITASKDB_GetDescription(itaskdb, ppRet)   ITaskDB_GetAttr(itaskdb, TASKDBATTR_DESCRIPTION, ppRet)
#define ITASKDB_GetLocation(itaskdb, ppRet)   ITaskDB_GetAttr(itaskdb, TASKDBATTR_LOCATION, ppRet)
#endif

/* Attribute setter functions */
#define ITASKDB_SetID(itaskdb, pVal)   ITaskDB_SetAttr(itaskdb, TASKDBATTR_ID, pVal)
#define ITASKDB_SetContent(itaskdb, pVal)   ITaskDB_SetAttr(itaskdb, TASKDBATTR_CONTENT, pVal)
#define ITASKDB_SetCheckFlag(itaskdb, pVal)   ITaskDB_SetAttr(itaskdb, TASKDBATTR_CHECKSTATUS, pVal)
#define ITASKDB_SetPriority(itaskdb, pVal)   ITaskDB_SetAttr(itaskdb, TASKDBATTR_PRIORITY, pVal)
#define ITASKDB_SetReminder(itaskdb, pVal)   ITaskDB_SetAttr(itaskdb, TASKDBATTR_REMINDERFLG, pVal)
#define ITASKDB_SetDueTime(itaskdb, pVal)   ITaskDB_SetAttr(itaskdb, TASKDBATTR_DUE_TIME, pVal)
#define ITASKDB_SetModifyTime(itaskdb, pVal)   ITaskDB_SetAttr(itaskdb, TASKDBATTR_MODIFIED_TIME, pVal)
#define ITASKDB_SetSnoozeTimes(itaskdb, pVal)   ITaskDB_SetAttr(itaskdb, TASKDBATTR_SNOOZETIMES, pVal)
#ifdef __APP_MMI_TODOLIST_VTODO__
#define ITASKDB_SetDescription(itaskdb, pVal)   ITaskDB_SetAttr(itaskdb, TASKDBATTR_DESCRIPTION, pVal)
#define ITASKDB_SetLocation(itaskdb, pVal)   ITaskDB_SetAttr(itaskdb, TASKDBATTR_LOCATION, pVal)
#endif

MAE_Ret MAETaskDB_New(u32 nId, void **ppObj);

/*-------------------------------------------------------------------------*/
#endif /* __MAE_TASKDB_H__ */

