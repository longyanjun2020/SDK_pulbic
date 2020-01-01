/**
* @file mmi_testIndicator.h
*/
#ifndef __MMI_TESTINDICATOR_H__
#define __MMI_TESTINDICATOR_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Indicator Widget
*/
MAE_Ret UTIndicator_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTIndicator_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTIndicator_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTIndicator_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTIndicator_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTIndicator_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTIndicator_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTIndicator_Ftbl[MAX_TESTVIEW_NUM] = {
    UTIndicator_Create,
    UTIndicator_View1,
    UTIndicator_View2,
    UTIndicator_View3,
    UTIndicator_View4,
    UTIndicator_View5,
    UTIndicator_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTINDICATOR_H__ */
