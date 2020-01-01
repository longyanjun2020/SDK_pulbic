/*****************************************************************************************
* @todolistapp_view.h
*
* Comment:
*
* @author Jack.Kuo@mstarsemi.com
* @       Ryan.Fang@mstarsemi.com
* @version:0.0.2  @ 2009.12.01
*****************************************************************************************/
#ifndef __MMI_TODOLISTAPP_VIEW_H_
#define __MMI_TODOLISTAPP_VIEW_H_



// TODOLIST_WND_TODOLIST 
typedef struct
{
    IWidget *pMenuWdg;
}ToDoListAppToDoListViewWdgList_t;

MAE_Ret ToDoListAppCreateToDoListView(HWIN hWin, ToDoListAppToDoListViewWdgList_t *pWdgList);
void _ToDoListToDoListViewAdaptGet(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);
void _ToDoListToDoListViewItemDataFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
MAE_Ret _CreateToDoListItemInfo(ToDoListAppData_t *pThis, u16 nIndex, ImageTextImageInfo *pImgTextImgInfo,IWidget *pMenu);


/**************************************************************************************************/


typedef struct
{
    IWidget *pOptionMenuWdg;
}ToDoListAppOptionViewWdgList_t;

//    TODOLIST_WND_TODOLISTOPTION, TODOLIST_WND_EDITCONTENTOPTION , TODOLIST_WND_VIEWTASKOPTION ,, 
MAE_Ret ToDoListAppCreateToDoListOptionView(HWIN hWin, ToDoListAppOptionViewWdgList_t *pWdgList);
MAE_Ret ToDoListAppCreateEditContentOptionView(HWIN hWin, ToDoListAppOptionViewWdgList_t *pWdgList);
MAE_Ret ToDoListAppCreateViewTaskOptionView(HWIN hWin, ToDoListAppOptionViewWdgList_t *pWdgList);


typedef struct
{
    IWidget *pTextWdg;
}ToDoListAppViewTaskViewWdgList_t;

//TODOLIST_WND_VIEWTASK
MAE_Ret ToDoListAppCreateViewTaskView(HWIN hWin, ToDoListAppViewTaskViewWdgList_t *pWdgList); // pass a string


/**************************************************************************************************/




typedef struct
{
    IWidget *pMenuWdg;
    IWidget *pTextWdg;
}ToDoListAppPickPriorityWdgList_t;
//TODOLIST_WND_PICKPRIORITY
MAE_Ret ToDoListAppCreatePickPriorityView(HWIN hWin,ToDoListAppPickPriorityWdgList_t  *pWdgList);

/**************************************************************************************************/

typedef struct
{
    IWidget *pMenuWdg;
    IWidget *pTextWdg;
}ToDoListAppSortByWdgList_t;
//TODOLIST_WND_SORTBY
MAE_Ret ToDoListAppCreateSortByView(HWIN hWin, ToDoListAppSortByWdgList_t *pWdgList);


/**************************************************************************************************/


typedef struct
{
    IWidget *pMenuWdg;
}ToDoListAppSendViewWdgList_t;
//TODOLIST_WND_SEND
MAE_Ret ToDoListAppCreateSendView(HWIN hWin, ToDoListAppSendViewWdgList_t *pWdgList);


typedef struct
{
    IWidget *pIInputWdg;
}ToDoListAppEditContentViewWdgList_t;
//TODOLIST_WND_EDITCONTENT
MAE_Ret ToDoListAppCreateEditContentView(HWIN hWin, ToDoListAppEditContentViewWdgList_t *pWdgList);

/**************************************************************************************************/


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
#ifdef __APP_MMI_TODOLIST_VTODO__
    IWidget *pLocationDoubleTextWidget;
    IWidget *pDescriptionDoubleTextWidget;
#endif 
} ToDoListAppAddTaskViewWdgList_t;

//TODOLIST_WND_ADDTASK  TODOLIST_WND_EDITTASK
MAE_Ret ToDoListAppCreateAddTaskView(HWIN hWin, ToDoListAppAddTaskViewWdgList_t *pWdgList);

/**************************************************************************************************/



typedef struct
{
    IWidget *pDateTextDateWidget;
    IWidget *pTimeTextTimeWidget;
}ToDoListAppAddUpdateAddTaskWdgList_t ;

MAE_Ret ToDoListAppUpdateAddTaskView(HWIN hWin,ToDoListAppAddUpdateAddTaskWdgList_t *pWdgList,ToDoListReminder_e eRemind);

#endif //__todolistapp_view__H
