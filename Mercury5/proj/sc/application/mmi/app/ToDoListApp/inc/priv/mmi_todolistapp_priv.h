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

/**
* @file    mmi_todolistapp_priv.h
* @version
* @brief   ToDoList applet private header file
*
*/

#ifndef __MMI_TODOLISTAPP_PRIV_H__
#define __MMI_TODOLISTAPP_PRIV_H__
/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_common_dialog.h"
#include "mmi_srv_header.h"
#include "mmi_common_rai_id.h"
#include "mmi_common_vtm.h"
#include "mmi_common_custom.h"
#include "mmi_todolistapp.h"
#include "mmi_todolistapp_id.h"
#include "todolistapp_resource.h"
#include "mmi_todolistapp_util.h"
#include "mmi_setting_cfg.h"


// bad?
/*=============================================================*/
// Extern definition
/*=============================================================*/


/*=============================================================*/
// Macro definition
/*=============================================================*/
#define MMI_TODOLIST_MAX_TITLE_LEN       20
// if the size of content, description and location are not identical, the bellow define must change
#define MMI_TODOLIST_MAX_CONTENT_LEN     TODOLIST_CONTENTSTR_MAX_CHARS  //(TASKDB_PCONTENT_SIZE-sizeof(MAE_WChar))edit content len reference mmi_mae_taskdb.h ((sizeof(MAE_WChar))*26)
#define MMI_TODOLIST_MAX_VIEW_LEN        250 //for view task
#define MMI_TODOLIST_DELETEALL_TIMER     2
#define MMI_TODOLIST_FIRST_LIST_BE_SELECTED 0
#define MMI_TODOLIST_SECONDS_PER_DAY     (24*60*60)
#define MMI_TODOLIST_MAX_RADIOCHECK_NUMBER 1
#define MMI_TODOLIST_MIN_RADIOCHECK_NUMBER 1
#define MMI_TODOLIST_NO_LIST               0
#define MMI_TODOLIST_AUTOCLOSE_TIMER       1000

//menu number of option menu wdg stytle: radio
#define MMI_TODOLIST_PICKPRIORITY_MENU_NUMBER 3
#define MMI_TODOLIST_SORTBY_MENU_NUMBER 3
#define MMI_TODOLIST_SENDBY_MENU_NUMBER 2

// count mode TASKDBATTR_CHECKSTATUS, TASKDBATTR_PRIORITY, TASKDBATTR_MODIFIED_TIME, TASKDBATTR_DUE_TIME
#define MMI_TODOLIST_TASKDBSORTATTR_COUNT   4


#define MMI_TODOLIST_SEND_TASK_WITHOUT_DUE_FORMAT_STRL L"%s: %s\n%s: %s\n%s: %s\n%s: %s\n"
#define MMI_TODOLIST_SEND_TASK_WITH_DUE_FORMAT_STRL L"%s: %s\n%s: %s\n%s: %s\n%s: %s\n%s: %s\n%s: %s\n"
#ifdef __APP_MMI_TODOLIST_VTODO__
#define MMI_TODOLIST_SEND_TASK_WITH_DUE_ONE_OPTION_FORMAT_STRL L"%s: %s\n%s: %s\n%s: %s\n%s: %s\n%s: %s\n%s: %s\n%s: %s\n" // one option =>one of location or description
#define MMI_TODOLIST_SEND_TASK_WITH_DUE_TWO_OPTION_FORMAT_STRL L"%s: %s\n%s: %s\n%s: %s\n%s: %s\n%s: %s\n%s: %s\n%s: %s\n%s: %s\n" // both location and description
#endif

#define MMI_TODOLIST_ARRAY_SIZE_INIT 15
#define MMI_TODOLIST_ARRAY_SIZE_GROW 10

#define MMI_TODOLIST_BREAK_IF_NULL_RET(p, nRetVar, RetVal, str) \
    { \
    if(NULL == (p)) \
        { \
        nRetVar = RetVal; \
        LOG_ERROR(MMI_LEVEL_TODOLIST, str); \
        ASSERT(0); \
        break; \
        } \
    }
#define MMI_TODOLIST_BREAK_IF_NULL(p, str) \
    { \
    if(NULL == (p)) \
        { \
        LOG_ERROR(MMI_LEVEL_TODOLIST, str); \
        ASSERT(0); \
        break; \
        } \
    }
#define MMI_TODOLIST_BREAK_IF_FAIL(a, str) \
    { \
    if(MAE_RET_SUCCESS != (a)) \
            { \
            LOG_ERROR(MMI_LEVEL_TODOLIST, str, (a)); \
            break; \
        } \
    }
/*=============================================================*/
// definition for  use RAI                                     //
/*=============================================================*/
// if file crash , write the 255 value to rai file...
#define MMI_TODOLIST_IDX_NO_DATA     255
#define MMI_TODOLIST_LEAST_MEMORY    (6*1024)
#define MMI_TODOLIST_NOTEFILE_MEMORY 1024

/*=============================================================*/
// Data type definition
/*=============================================================*/



/*=============================================================*/
/*Window data */
/*=============================================================*/

/* Application structure*/
//do not change the order of enum
typedef enum
{
    PRIORITY_HIGH=0,
    PRIORITY_NORMAL,
    PRIORITY_LOW,
    PRIORITY_ENUM_END
} ToDoListPriority_e;
//do not change the order of enum
typedef enum
{
    STATUS_UNCHENK=0,
    STATUS_CHECK,
    STATUS_ENUM_END
}ToDoListStatus_e;
//do not change the order of enum
typedef enum
{
    REMINDER_OFF=0,
    REMINDER_ON,
    REMINDER_ENUM_END
}ToDoListReminder_e;

typedef enum
{
    DAYEVENT_OFF=0,
    DAYEVENT_ON,
    DAYEVENT_ENUM_END
}ToDoListDayEvent_e;

typedef enum
{
    SORTBY_STATUS=0,
    SORTBY_PRIORITY,
    SORTBY_DUEDATE,
    SORTBY_EDITDATE,
    SORTBY_ENUM_END,
}ToDoListWndSortBy_e;

typedef enum
{
    EDIT_CONTENT=0,
#ifdef __APP_MMI_TODOLIST_VTODO__
    EDIT_DESCRIPTION,
    EDIT_LOCATION,
#endif
    EDIT_ENUM_END,
}ToDoListEditTextCategory_e;
typedef struct
{
    IWidget     *pMenuWdg;
}ToDoListListView_t;

typedef struct
{
    IWidget *pOptionMenuWidget;
    ToDoListWndToDoListOptMnuId_e  eOptionMenuIndex;
} ToDoListToDoListOptionView_t;

typedef struct
{
    IWidget *pOptionMenuWidget;
    ToDoListWndViewTaskOptMnuId_e  eOptionMenuIndex;
}ToDoListWndViewTaskOptionView_t;

typedef struct
{
    IWidget *pInputWidget;
    MAE_DateTime_t tEditDate;
    ToDoListEditTextCategory_e eEditTextCategory;
} ToDoListAppEditContentView_t;

typedef struct
{
    IWidget *pOptionMenuWidget;
} ToDoListEditContentOptionMenuView_t;

typedef struct
{
    IWidget *pOptionMenuWidget;
} ToDoListPickPriorityOptionMenuView_t;

typedef struct
{
    IWidget *pOptionMenuWidget;
} ToDoListSortByOptionMenuView_t;

typedef struct
{
    IWidget *pTextWidget;
    MAE_WChar *pText;
} ToDoListAppViewTaskView_t;
typedef struct
{
    IWidget *pScrollBarWidget;
    IWidget *pMflContainer;
    IWidget *pContentDoubleTextWidget;
    IWidget *pPriorityTextPickWidget;
    IWidget *pStatusTextPickWidget;
    IWidget *pReminderTextPickWidget;
    IWidget *pDateTextDateWidget;
    IWidget *pTimeTextTimeWidget;
    MAE_WChar *pContent;
    u16      nContentStrSize;
#ifdef __APP_MMI_TODOLIST_VTODO__
    IWidget *pDescriptionDoubleTextWidget;
    IWidget *pLocationDoubleTextWidget;
    MAE_WChar *pDescription;
    MAE_WChar *pLocation;
    u16      nDescriptionStrSize;
    u16      nLocationStrSize;
#endif
} ToDoListAppAddTaskView_t;





typedef struct
{
    TASKATTRTYPE_ID          nID;            // rand
    MAE_WChar                *pContent;      // the content(subject) of the task
    TASKATTRTYPE_CHECKSTATUS nCheckStatus;   // init: MAE_TASKDB_CHECKSTATUS_UNCHECKED
    TASKATTRTYPE_REMINDERFLG nReminderFlag;  // init: MAE_TASKDB_REMINDERFLAG_OFF
    TASKATTRTYPE_PRIORITY    nPriority;  // init: MAE_TASKDB_PRIORITYLEVEL_NORMAL
    TASKATTRTYPE_TIME        nDueDateTime;   // initial: TASKDBTIME_UNSET
    MAE_DateTime_t           tDueDateTime;
    TASKATTRTYPE_TIME        nModifiedTime;  // initial: TASKDBTIME_UNSET
    u32                      nTaskNumber;
    ToDoListDueTimeType_e    eDueTimeType;
#ifdef  __APP_MMI_TODOLIST_VTODO__
    TASKATTRTYPE_DESCRIPTION pDescription;
    TASKATTRTYPE_LOCATION    pLocation;
#endif
}mmi_ToDoListTaskData_t;


typedef struct
{
    TASKATTRTYPE_ID nTaskID;
    u32             nListID;
    TASKATTRTYPE_CHECKSTATUS eCheckStatus;
    TASKATTRTYPE_REMINDERFLG eReminderFlag;
    TASKATTRTYPE_PRIORITY ePriority;
    MAE_WChar       aTitleStr[MMI_TODOLIST_MAX_TITLE_LEN];
}mmi_ToDoListTaskInfo_t;

/*=============================================================*/
// AppData //
/*=============================================================*/
typedef struct
{
    APPLET_BASE_ELEMENTS;
    mmi_ToDoListTaskData_t  *pTaskData;
    IArrayModel             *pListItemModel;
    boolean                 bIsEditTask;
    boolean                 bIsEditContent;
    boolean                 bIsExit;
    boolean                 bIsDeleteALL;
    boolean                 bIsSaving;
    boolean                 bIsDeleting;
    boolean                 bIsResumeStop;
    u8                      u8SelectedListIdx;
    u32                     nMflFocusWgdId;
    TASKDB_FIELDS_e         eMainSortMode;
    ToDoList_APMode_e       nAPLaunchFor;
    SetPhoneTimeFormat_e    nTimeFormat;
} ToDoListAppData_t;

/*=============================================================*/
// Local function definition
/*=============================================================*/


/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret ToDoListConstruct(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret ToDoListDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

boolean ToDoListStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ToDoListStopCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ToDoListKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ToDoListResumeCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ToDoListSuspendCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ToDoListPreHookCB(IApplet *pApplet, u32 evt, u32 nParam1, u32 nParam2);

//void  _ToDoListCommonCreatetDialog(void *pThis,ToDoListDlgId_e nDlgId);
MAE_Ret _ToDoListCommonCancelAlarm(u32 nTaskId);
MAE_Ret _ToDoListCommonSetAlarm(u32 nTaskId,MAE_DateTime_t *pDueDate);


//void ToDoListAccessoryPlugStatusCB(void *pUserData, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);
//void ToDoListExpiredToDoListCloseCB(void *pUserData, u32 nExpiredToDoListUserCode, u32 nToDoListAlertReply);




/*=============================================================*/
// Private function definition
/*=============================================================*/
static MAE_Ret _ToDoListInitFile(ToDoListAppData_t *pThis);

//before write of read file allocate a buffer the following function..


static MAE_Ret _ToDoListInitDefListValue(void * pCusHandle, ToDoListAppAddTaskView_t *tWdgList); //elvis .shih
static MAE_Ret _ToDoListInitAppData(ToDoListAppData_t *pAppData);
//#ifndef __APP_MMI_TODOLIST_VTODO__
static MAE_Ret _ToDoListRemindDateInit(void *pCusHandle);
//#endif
static MAE_Ret _ToDoListSetEditContent(void *pCusHandle);


static MAE_Ret _ToDoListEditTaskSetValue(void *pApplet, void *pWndData);// For TaskDB using
static MAE_Ret _ToDoListViewTaskGetText(void *pCusHandle, MAE_WChar **ppText); //for TaskDB using

static MAE_Ret _ToDoListCheckIfFullOfList(void *pCusHandle);

// launch APP for send msg
static MAE_Ret _ToDoListLaunchAppSendSMS(void *pApplet);
//now is not support
//static MAE_Ret _ToDoListLaunchAppSendMMS(void * pApplet);

static void _ToDoListBackToDoListWnd(IApplet *pApplet);
static void _ToDoListCommonCreatetDialog(void *pThis,ToDoListDlgId_e nDlgId);
#ifdef  __APP_MMI_TODOLIST_VTODO__
static void _ToDoListStrCopy(MAE_WChar **ppDes, MAE_WChar *pSrc);
#endif
static void _ToDoListViewTaskScroll(IApplet *pApplet,u32 MAE_KEY_ID);
/*=============================================================*/
// TaskDB Releated Funtion
/*=============================================================*/

// save task entry function
static void ToDoListSave(void *pThis);
static MAE_Ret ToDoListSaveTask(void *pThis);
static MAE_Ret _ToDoListSaveTask(void *pThis);

// save the task check flag,
static MAE_Ret _ToDoListSaveTaskCheckStatus(void *pThis,MAE_TaskDB_CheckStatus_e eChackStatus);


static MAE_Ret _ToDoListGetTaskData(void  *pThis, u32 nTaskID);
static MAE_Ret _ToDoListListAllTasks(void *pThis);

// delete Sel task entry function ,
static MAE_Ret ToDoListDeleteTask(ToDoListAppData_t *pAppData);
static MAE_Ret _ToDoListDeleteTask(void *pThis,u32 nTaskID);

// delete ALL task entry function
static void _ToDoListDeleteALLTaskStart(void *pThis);

/*====================================*/
// map function: MenuID to TaskDB Format
/*====================================*/
// map selected Task MnuID to TaskDB TaskID
static MAE_TaskDB_PriorityLevel_e _ToDoListMenuIDMapToTaskDBPriorityLevel(const u32 npSelectID);

// map function MenuID to TaskDB Format
static MAE_TaskDB_CheckStatus_e _ToDoListMenuIDMapToTaskDBCheckStatus(const u32 nSelectID);
static MAE_TaskDB_ReminderFlag_e _ToDoListMenuIDMapToTaskDBReminderFlag(const u32 nSelectID);
static TASKDB_FIELDS_e _ToDoListMenuIDMapToTaskDBFields(const u32 nSelectID);
static MAE_Ret _ToDoListListSelectIDMapToTaskID(void* pThis,const u32 nSelectId,u32 *pnTaskID);


/*====================================*/
// map function: TaskDB Format to MenuID
/*====================================*/
static u32 _ToDoListTaskDBReminderFlagMapToMenuID(const MAE_TaskDB_ReminderFlag_e nReminderFlag);
static u32 _ToDoListTaskDBCheckStatusMapToMenuID(const MAE_TaskDB_CheckStatus_e eCheckStatus );
static u32 _ToDoListTaskDBPriorityLevelMapToMenuID(const MAE_TaskDB_PriorityLevel_e ePriority);
static u32 _ToDoListTaskDBFieldsMapToMenuID(TASKDB_FIELDS_e  eField);

static MAE_Ret _ToDoListCommonSetEmptyList(IArrayModel  *pListItemModel);

static MAE_Ret _ToDoListIsAlarmExpired(void *pThis,MAE_DateTime_t *pDateTime);



/*=================================================*/
//Window manager related function
/*=================================================*/

MAE_Ret ToDoListToDoListWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ToDoListToDoListWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ToDoListToDoListWndShow(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ToDoListToDoListWndDestory(void *pCusHandle, void *pWndData, u32 nWndInitParam);

//    TODOLIST_WND_EDITCONTENT,
MAE_Ret ToDoListEditContentWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ToDoListEditContentWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);


//     TODOLIST_WND_EDITCONTENTOPTION,
MAE_Ret ToDoListEditContentOptionWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ToDoListEditContentOptionWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ToDoListEditContentOptionWndDestory(void *pCusHandle, void *pWndData, u32 nWndInitParam);

//    TODOLIST_WND_PICKPRIORITY,
MAE_Ret ToDoListPickPriorityWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ToDoListPickPriorityWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ToDoListPickPriorityWndDestory(void *pCusHandle, void *pWndData, u32 nWndInitParam);

//    TODOLIST_WND_VIEWTASKOPTION,
MAE_Ret ToDoListViewTaskOptionWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ToDoListViewTaskOptionWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ToDoListViewTaskOptionWndDestory(void *pCusHandle, void *pWndData, u32 nWndInitParam);

//    TODOLIST_WND_VIEWTASK,
MAE_Ret ToDoListViewTaskWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ToDoListViewTaskWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ToDoListViewTaskWndDestory(void *pCusHandle, void *pWndData, u32 nWndInitParam);

//    TODOLIST_WND_SORTBY
MAE_Ret ToDoListSortByWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ToDoListSortByWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ToDoListSortByWndDestory(void *pCusHandle, void *pWndData, u32 nWndInitParam);

//    TODOLIST_WND_ADDTASK, TODOLIST_WND_VIEWTASK,
MAE_Ret ToDoListAddTaskWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ToDoListAddTaskWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ToDoListAddTaskWndShow(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ToDoListAddTaskWndDestory(void *pCusHandle, void *pWndData, u32 nWndInitParam);

//    TODOLIST_WND_TODOLISTOPTION,
MAE_Ret ToDoListToDoListOptionWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _ToDoListToDoListOptionWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _ToDoListToDoListOptionWndDestory(void *pCusHandle, void *pWndData, u32 nWndInitParam);



/*=================================================*/
//Window CB function //
/*=================================================*/
void _ToDoListMflContainerMFLFocusChangeCB(void * pApplet, void* pUsrData, WidgetEvtCode_t nEvt,MFLFocusData_t * pMFLFocusData,IWidget *pwidget);
void _ToDoListMflContainerMFLFocusSelectCB(void * pApplet, void* pUsrData, WidgetEvtCode_t nEvt,MFLFocusData_t * pMFLFocusData,IWidget *pwidget);

void _ToDoListCommonPickFocusChangeCB (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusChangeData_t * nFocusIndex, IWidget *pReserve);


void _ToDoListPickPrioityMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);

void _ToDoListSortByMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);

void _ToDoListToDoListOptionMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);

void _ToDoListViewTaskOptionMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);

void _ToDoListToDoListMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);

void _ToDoListEditContentOptionMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);

void _ToDoListEditContentOptionLayer2MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);

void _ToDoListDateInputDataChangeCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);


/*=================================================*/
//dialog CB function //
/*=================================================*/

MAE_Ret ToDoListDeleteConfirmDialogCb(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
static MAE_Ret _ToDoListExitFieldListConfirmDialogKeyPress(void *pApplet, u32 evt, u32 param1, u32 param2);
/*=================================================*/
// dialogtimeout CB
/*=================================================*/
MAE_Ret ToDoListDialogTimeOutCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
MAE_Ret ToDoListSaveAlarmExpiredConfirmDialogCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);

//
static void _TodoListTimeAmPmChangeCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TimePeriod_e eTimePeriod, IWidget *pWidget);

#endif /* __MMI_TODOLISTAPP_PRIV_H__ */
