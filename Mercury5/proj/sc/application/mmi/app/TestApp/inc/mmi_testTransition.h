/**
* @file mmi_testTransition.h
*/
#ifndef __MMI_TESTTRANSITION_H__
#define __MMI_TESTTRANSITION_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Transition Widget
*/
MAE_Ret UTTransition_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTTransition_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTransition_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTransition_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTransition_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTransition_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTransition_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTTransition_Ftbl[MAX_TESTVIEW_NUM] = {
    UTTransition_Create,
    UTTransition_View1,
    UTTransition_View2,
    UTTransition_View3,
    UTTransition_View4,
    UTTransition_View5,
    UTTransition_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTTRANSITION_H__ */
