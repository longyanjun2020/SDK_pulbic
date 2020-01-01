#ifndef MMI_CALENDARAPP_INDIAN_H
#define MMI_CALENDARAPP_INDIAN_H

#ifdef __INDIAN_CALENDAR__

#include "mmi_calendarapp_priv.h"
#include "mmi_calendarapp_util.h"

#define CALENDAR_INDIAN_SUPPORT_YEAR_BEGIN 2012
#define CALENDAR_INDIAN_SUPPORT_YEAR_END 2021

MAE_Ret CalendarWndTithiDetailsHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CalendarWndFestivalListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CalendarWndYearlyTithiHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CalendarWndIndianFestivalPopupHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CalendarWndIndianYearlyPopupHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

MAE_Ret _CalendarWndCreateIndianEntry(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CalendarWndShowIndianEntry(void *pCusHandle, void *pWndData);
MAE_Ret _CalendarWndHideIndianEntry(void *pCusHandle, void *pWndData);
MAE_Ret _CalendarWndDestroyIndianEntry(void *pCusHandle, void *pWndData);

MAE_Ret _CalendarWndCreateTithiDetails(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CalendarWndShowTithiDetails(void *pCusHandle, void *pWndData);
MAE_Ret _CalendarWndHideTithiDetails(void *pCusHandle, void *pWndData);
MAE_Ret _CalendarWndDestroyTithiDetails(void *pCusHandle, void *pWndData);

MAE_Ret _CalendarWndCreateFestivalList(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CalendarWndShowFestivalList(void *pCusHandle, void *pWndData);
MAE_Ret _CalendarWndHideFestivalList(void *pCusHandle, void *pWndData);
MAE_Ret _CalendarWndDestroyFestivalList(void *pCusHandle, void *pWndData);

MAE_Ret _CalendarWndCreateYearlyTithi(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CalendarWndShowYearlyTithi(void *pCusHandle, void *pWndData);
MAE_Ret _CalendarWndHideYearlyTithi(void *pCusHandle, void *pWndData);
MAE_Ret _CalendarWndDestroyYearlyTithi(void *pCusHandle, void *pWndData);

MAE_Ret _CalendarWndCreateIndianFestivalPopup(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CalendarWndDestroyIndianFestivalPopup(void *pCusHandle, void *pWndData);

MAE_Ret _CalendarWndCreateIndianYearlyPopup(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _CalendarWndDestroyIndianYearlyPopup(void *pCusHandle, void *pWndData);

void _CalendarIndianYearlyTithiPopupKeyPress(MMI_CALENDARAPP* pThis, u32 param);
void _CalendarIndianFestivalPopupKeyPress(MMI_CALENDARAPP* pThis, u32 param);
void _CalendarIndianTithiDetailsKeyPress(MMI_CALENDARAPP* pThis, u32 param);

static void _CalendarIndianFestivalListAdaptGet(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
static void _CalendarIndianFestivalListAdaptGetFree(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType);
static void _CalendarIndianYearlyTithiAdaptGet(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
static void  _CalendarIndianYearlyTithiAdaptGetFree(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType);

void _CalendarIndianFestivalListSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _CalendarIndianFestivalListCancelCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _CalendarIndianYearlyTithiSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _CalendarIndianYearlyTithiCancelCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
MAE_Ret _CalendarIndianGetTithiDetailStr(u16 nIndYear, u16 nIndMonth,u16 nIndDay, u16 nDayofWeek,IndianCalendar_LeapType eLeapType, MAE_WChar** ppIndianDateStr);

MAE_Ret _CalendarIndianGetDateString(MAE_DateTime_t* pSolarDate, MAE_WChar** ppIndianDateStr);
MAE_Ret _CalendarIndianSetPrviewLine(void *pApplet, IWidget *pTextWdg);
MAE_Ret _CalendarIndian_GetFestival(u32 nOffest, MAE_WChar** ppFestivalStr);

void _Indian_GetTithiStr(u32 nIndex, MAE_WChar* pTithiStr);
void _Indian_GetMonthStr(u32 nIndex, IndianCalendar_LeapType eIsInLeapMonth ,MAE_WChar* pMasaStr);
void _Indian_GetFestivalStr(Festival_Enum nIndex, MAE_WChar* pFestivalStr);
void _Indian_GetWeekDayStr(u32 nIndex, MAE_WChar* pWeekdayStr);
void _Indian_GetPakshaStr(u32 nIndex, MAE_WChar* pPakshaStr);

s32 _CalendarApp_WesternToIndian(MAE_DateTime_t *pDate, u16 *pYear, u16 *pMonth,u16 *pDay, IndianCalendar_LeapType *pIsInLeapMonth);
s32 _CalendarApp_GetSunriseTime(MAE_DateTime_t *pDate);
s32 _CalendarApp_GetYearlyTithi(int year, u32 Tithi, MAE_WChar ** ppOutPutStr);
s32 _CalendarApp_IndianToWestern(int year,int month,int day, IndianCalendar_LeapType eLeapType, int *num, MAE_DateTime_t* WesternDate1, MAE_DateTime_t* WesternDate2);
boolean _CalendarApp_IndianIsSupportCurrLang(MMI_CALENDARAPP *pThis);
boolean _CalendarApp_IndianInSupportRange(u32 nYear);
s32 _CalendarApp_NextTithi(MAE_DateTime_t *pInputDate, u16 InputIndianYear, u16 InputIndianMonth,u16 InputIndianDay, IndianCalendar_LeapType eLeapType,
MAE_DateTime_t *pOutputDate ,u16 *pOutputIndianYear, u16 *pOutputIndianMonth,u16 *pOutputIndianDay, IndianCalendar_LeapType *pOutputLeapType);
void _CalenarApp_GetNextTithiDate(MAE_DateTime_t *pInputDate, u16 InputIndianYear, u16 InputIndianMonth,u16 InputIndianDay, IndianCalendar_LeapType eLeapType,
MAE_DateTime_t *pOutputDate ,u16 *pOutputIndianYear, u16 *pOutputIndianMonth,u16 *pOutputIndianDay, IndianCalendar_LeapType *pOutputLeapType);
void _CalendarAppLoadDLM(void);
void _CalendarUnloadDLM(void);

#endif /* __INDIAN_CALENDAR__ */
#endif /* MMI_CALENDARAPP_INDIAN_UTIL_H */
