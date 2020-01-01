/**
* @file mmi_testTab.h
*/
#ifndef __MMI_TESTTAB_H__
#define __MMI_TESTTAB_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Tab Widget
*/
MAE_Ret UTTab_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTTab_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTab_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTab_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTab_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTab_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTab_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTTab_Ftbl[MAX_TESTVIEW_NUM] = {
    UTTab_Create,
    UTTab_View1,
    UTTab_View2,
    UTTab_View3,
    UTTab_View4,
    UTTab_View5,
    UTTab_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTTAB_H__ */
