/*****************************************************************************************
* @alarmapp_view.h
*
* Comment:
*
* @author Jack.Kuo@mstarsemi.com
* @       Ryan.Fang@mstarsemi.com
* @version:0.0.2  @ 2009.12.01
*****************************************************************************************/
#ifndef __alarmapp_view__H
#define __alarmapp_view__H

typedef struct
{
    IWidget *pIMenuWdg;
}AlarmAppAlarmListViewWdgList_t;

MAE_Ret AlarmAppCreateAlarmListView(HWIN hWin, AlarmAppAlarmListViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pScrollBarWidget;
    IWidget *pMflContainer;
    IWidget *pTitleDoubleTextWidget;
    IWidget *pTimeTextTimeWidget;
    IWidget *pStatusTextPickWidget;
    IWidget *pFrequencyDoubleTextWidget;
    IWidget *pRingToneDoubleTextWidget;
}AlarmAppSetAlarmViewWdgList_t;

MAE_Ret AlarmAppCreateSetAlarmView(HWIN hWin, AlarmAppSetAlarmViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pIInputWdg;
}AlarmAppSetTitleViewWdgList_t;

MAE_Ret AlarmAppCreateSetTitleView(HWIN hWin, AlarmAppSetTitleViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pIOptionMenuWdg;
}AlarmAppSetTitleLoadOptionMenuViewWdgList_t;

MAE_Ret AlarmAppCreateSetTitleLoadOptionMenuView(HWIN hWin, AlarmAppSetTitleLoadOptionMenuViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
}AlarmAppSetFrequencyViewWdgList_t;

MAE_Ret AlarmAppCreateSetFrequencyView(HWIN hWin, AlarmAppSetFrequencyViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pIInputWdg;
}AlarmAppViewAlarmViewWdgList_t;

MAE_Ret AlarmAppCreateViewAlarmView(HWIN hWin, AlarmAppViewAlarmViewWdgList_t *pWdgList);

//*******************************************************************//


typedef struct
{
    IWidget *pIMenuWdg;
}AlarmAppFileMgrViewWdgList_t;

MAE_Ret AlarmAppCreateFileMgrView(HWIN hWin, AlarmAppFileMgrViewWdgList_t *pWdgList);

//*******************************************************************//
void _AlarmListViewAdaptGet(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);
void _AlarmListViewItemDataFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
MAE_Ret _CreateAlarmListItemInfo(AlarmAppData_t *pThis, u16 nIndex, ITSTextInfo *pITSTextInfo);

#endif //__alarmapp_view__H
