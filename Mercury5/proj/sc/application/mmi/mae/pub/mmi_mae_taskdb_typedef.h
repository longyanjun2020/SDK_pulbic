#ifndef __MMI_MAE_TASKDB_TYPEDEF_H__
#define __MMI_MAE_TASKDB_TYPEDEF_H__
#include "mmi_mae_common_def.h"

//------------------------------------
#define TASKDBATTR_BASE 0x0600
#define TASKDBTIME_UNSET    0

#define TASKDB_NOMORE			0x20
#define TASKDB_ID_NOSUCHITEM    0
#define TASKDB_ID_TASKEMPTY     0x0FFFFFFF
/*==============================================================================*/
/* PART I: type definition */
// check status types
enum _MAE_TaskDB_CheckStatus
{
    MAE_TASKDB_CHECKSTATUS_NONE,
    MAE_TASKDB_CHECKSTATUS_CHECKED,
    MAE_TASKDB_CHECKSTATUS_UNCHECKED,
    MAE_TASKDB_CHECKSTATUS_MAX
};
typedef u8  MAE_TaskDB_CheckStatus_e;

// reminder types
enum _MAE_TaskDB_ReminderFlag
{
    MAE_TASKDB_REMINDERFLAG_NONE,
    MAE_TASKDB_REMINDERFLAG_ON,
    MAE_TASKDB_REMINDERFLAG_OFF,
    MAE_TASKDB_REMINDERFLAG_EXPIRED,
    MAE_TASKDB_REMINDERFLAG_MAX
};
typedef u8  MAE_TaskDB_ReminderFlag_e;

// priority
enum _MAE_TaskDB_PriorityLevel
{
    MAE_TASKDB_PRIORITYLEVEL_NONE,
    MAE_TASKDB_PRIORITYLEVEL_LOW,
    MAE_TASKDB_PRIORITYLEVEL_NORMAL,
    MAE_TASKDB_PRIORITYLEVEL_HIGH,
    MAE_TASKDB_PRIORITYLEVEL_MAX
};
typedef u8  MAE_TaskDB_PriorityLevel_e;

/*==============================================================================*/
/* PART II: TaskDB fields */
enum _TASKDB_FIELDS
{
    TASKDBATTR_ID = (TASKDBATTR_BASE + 0), 
    TASKDBATTR_CONTENT,
    TASKDBATTR_CHECKSTATUS,
    TASKDBATTR_PRIORITY,
    TASKDBATTR_REMINDERFLG,
    TASKDBATTR_DUE_TIME,
    TASKDBATTR_MODIFIED_TIME,
    TASKDBATTR_SNOOZETIMES,
 #ifdef __APP_MMI_TODOLIST_VTODO__
    TASKDBATTR_DESCRIPTION,
    TASKDBATTR_LOCATION,
 #endif
    TASKDBATTR_MAX
};
typedef u32 TASKDB_FIELDS_e;
/*==============================================================================*/
/* PART III: field type define */
#define TASKATTRTYPE_ID          u32
#define TASKATTRTYPE_CONTENT     MAE_WChar*
#define TASKATTRTYPE_CHECKSTATUS MAE_TaskDB_CheckStatus_e
#define TASKATTRTYPE_PRIORITY    MAE_TaskDB_PriorityLevel_e
#define TASKATTRTYPE_REMINDERFLG MAE_TaskDB_ReminderFlag_e
#define TASKATTRTYPE_TIME        u32
#define TASKATTRTYPE_SNOOZETIMES u32
#ifdef __APP_MMI_TODOLIST_VTODO__
#define TASKATTRTYPE_DESCRIPTION MAE_WChar*
#define TASKATTRTYPE_LOCATION    MAE_WChar*
#endif

/*==============================================================================*/

#endif /* __MAE_TASKDB_TYPEDEF_H__ */
