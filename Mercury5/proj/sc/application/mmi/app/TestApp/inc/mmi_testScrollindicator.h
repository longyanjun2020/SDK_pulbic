/**
* @file mmi_testScrollindicator.h
*/
#ifndef __MMI_TESTSCROLLINDICATOR_H__
#define __MMI_TESTSCROLLINDICATOR_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Scroll indicator Widget
*/
MAE_Ret UTScrollindicator_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTScrollindicator_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTScrollindicator_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTScrollindicator_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTScrollindicator_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTScrollindicator_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTScrollindicator_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTScrollindicator_Ftbl[MAX_TESTVIEW_NUM] = {
    UTScrollindicator_Create,
    UTScrollindicator_View1,
    UTScrollindicator_View2,
    UTScrollindicator_View3,
    UTScrollindicator_View4,
    UTScrollindicator_View5,
    UTScrollindicator_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTSCROLLINDICATOR_H__ */
