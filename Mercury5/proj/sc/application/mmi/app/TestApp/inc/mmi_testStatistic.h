/**
* @file mmi_testStatistic.h
*/
#ifndef __MMI_TESTSTATISTIC_H__
#define __MMI_TESTSTATISTIC_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Statistic Widget
*/
MAE_Ret UTStatistic_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTStatistic_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTStatistic_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTStatistic_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTStatistic_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTStatistic_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTStatistic_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTStatistic_Ftbl[MAX_TESTVIEW_NUM] = {
    UTStatistic_Create,
    UTStatistic_View1,
    UTStatistic_View2,
    UTStatistic_View3,
    UTStatistic_View4,
    UTStatistic_View5,
    UTStatistic_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTSTATISTIC_H__ */
