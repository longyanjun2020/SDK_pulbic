/**
* @file mmi_testTime.h
*/
#ifndef __MMI_TESTTIME_H__
#define __MMI_TESTTIME_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Time Widget
*/
MAE_Ret UTTime_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTTime_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTime_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTime_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTime_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTime_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTime_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTTime_Ftbl[MAX_TESTVIEW_NUM] = {
    UTTime_Create,
    UTTime_View1,
    UTTime_View2,
    UTTime_View3,
    UTTime_View4,
    UTTime_View5,
    UTTime_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTTIME_H__ */
