////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __MMI_TODOLISTAPP_UTIL_H__
#define __MMI_TODOLISTAPP_UTIL_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_mae_taskdbmgr.h"
#include "mmi_common_util.h"

/*==============================================================================
STRUCTURE DECLARATIONS
==============================================================================*/

typedef enum
{
    DUETIME_EXPIRED=0,
    DUETIME_CLOSECURRENTTIME,
    DUETIME_OK,
}ToDoListDueTimeType_e;

enum _ToDoList_APMode{
    TODOLIST_MODE_NONE,
    TODOLIST_MODE_TASKLIST,
    TODOLIST_MODE_TASKINFO,
    TODOLIST_MODE_MAX
};
typedef u8 ToDoList_APMode_e;

typedef struct _ToDoList_LaunchArg
{
    TASKATTRTYPE_ID     nFocusTaskID;
    ToDoList_APMode_e   nType;
    boolean             bByTimerExpired;
}ToDoList_LaunchArg_t;

typedef struct _ToDoList_TaskListElmt
{
    TASKATTRTYPE_ID nTaskID;
    MAE_WChar       *pDescStr;
}ToDoList_TaskListElmt_t;

enum _ToDoList_Util_ChangeTaskStateType{
    TODOLIST_UTIL_TASKSTATE_NONE,
    TODOLIST_UTIL_TASKSTATE_SNOOZE,
    TODOLIST_UTIL_TASKSTATE_CHECK,
    TODOLIST_UTIL_TASKSTATE_VIEWDETAIL,
    TODOLIST_UTIL_TASKSTATE_EXPIRED,        // task expired with users' response
    TODOLIST_UTIL_TASKSTATE_DLGAUTOTIMEOUT, // task expired without users' response
    TODOLIST_UTIL_TASKSTATE_MAX
};
typedef u8 ToDoList_Util_ChangeTaskStateType_e;

// define the data that a task should have
typedef struct _ToDoList_TaskData
{
    TASKATTRTYPE_ID             nID;          // rand
    MAE_WChar                   *pContent;    // the content(subject) of the task
    TASKATTRTYPE_CHECKSTATUS    nCheckStatus;   // init: MAE_TASKDB_CHECKSTATUS_UNCHECKED
    TASKATTRTYPE_REMINDERFLG    nReminderFlag;  // init: MAE_TASKDB_REMINDERFLAG_OFF
    TASKATTRTYPE_PRIORITY       nPriority;      // init: MAE_TASKDB_PRIORITYLEVEL_NORMAL
    TASKATTRTYPE_TIME           nDueTime;       // initial: TASKDBTIME_UNSET
    MAE_DateTime_t              tDueDateTime;
    TASKATTRTYPE_TIME           nModifiedTime;  // initial: TASKDBTIME_UNSET
#ifdef __APP_MMI_TODOLIST_VTODO__
	MAE_WChar                   *pDescription;    // the description of the task
	MAE_WChar                   *pLocation;    // the location of the task
#endif
}ToDoList_TaskData_t;

/*==============================================================================
FUNCTION DECLARATIONS
==============================================================================*/
MAE_Ret ToDoList_Util_GetTaskAlertData(u32 nEventUID, AlertDisplayType_e eDisplayType, MAE_WChar** ppAlertStr, TASKATTRTYPE_SNOOZETIMES* pAvailableSnoozeTimes, IBase* pOwner);
/*-------------------------------------------------------------------------*/
MAE_Ret ToDoList_Util_ChangeTaskState( u32 nTaskID, ToDoList_Util_ChangeTaskStateType_e nChangeType, boolean bCauseByTimerExpired, IBase *pOwner);
/*-------------------------------------------------------------------------*/
MAE_Ret ToDoList_Util_SnoozeTask(u32 nTaskID, IBase *pOwner);
/*-------------------------------------------------------------------------*/
MAE_Ret ToDoList_Util_CheckTask(u32 nTaskID, IBase *pOwner);
/*-------------------------------------------------------------------------*/
MAE_Ret ToDoList_Util_ExpireTask(u32 nTaskID, IBase *pOwner);
/*-------------------------------------------------------------------------*/
MAE_Ret ToDoList_Util_TaskAlertDlgTimesOut(u32 nTaskID,  IBase *pOwner);
/*-------------------------------------------------------------------------*/
MAE_Ret ToDoList_Util_ViewExpiredTask(u32 nTaskID, IBase *pOwner);
/*-------------------------------------------------------------------------*/
void ToDoList_Util_LaunchTaskInfoParamFree(IBase *pIssuer, u32 Param);
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
MAE_Ret ToDoList_Util_DeleteByTaskID(TASKATTRTYPE_ID nTaskID, IBase *pOwner);
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
MAE_Ret ToDoList_Util_AddTask(ToDoList_TaskData_t *pTaskInfo, u32 u32ModifyTime, IBase *pOwner);

/*-------------------------------------------------------------------------*/
MAE_Ret _ToDoList_Util_CancelAlarm(u32 nTaskId,IBase *pOwner);
MAE_Ret _ToDoList_Uteil_SetAlarm(u32 nTaskId,MAE_DateTime_t *pDueDate,IBase *pOwner);



#endif /* __MMI_TODOLISTAPP_UTIL_H__ */
