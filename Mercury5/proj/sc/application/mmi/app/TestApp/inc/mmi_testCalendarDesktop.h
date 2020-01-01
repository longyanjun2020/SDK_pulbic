/**
* @file mmi_testCalendarDesktop.h
*/
#ifndef __MMI_TESTCalendarDesktop_H__
#define __MMI_TESTCalendarDesktop_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

#ifdef __GADGETS_MMI__
/*-------------------------------------------------------------------------*/
/**
* CalendarDesktop Widget
*/
MAE_Ret UTCalendarDesktop_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTCalendarDesktop_View1(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTCalendarDesktop_View2(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTCalendarDesktop_View3(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTCalendarDesktop_View4(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTCalendarDesktop_View5(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTCalendarDesktop_Close(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTCalendarDesktop_Ftbl[MAX_TESTVIEW_NUM] = {
    UTCalendarDesktop_Create,
    UTCalendarDesktop_View1,
    UTCalendarDesktop_View2,
    UTCalendarDesktop_View3,
    UTCalendarDesktop_View4,
    UTCalendarDesktop_View5,
    UTCalendarDesktop_Close
};
#endif //__GADGETS_MMI__

/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTCalendarDesktop_H__ */
