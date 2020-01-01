/**
* @file mmi_testDummy.h
*/
#ifndef __MMI_TESTDummy_H__
#define __MMI_TESTDummy_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Dummy Widget
*/
MAE_Ret UTDummy_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTDummy_View1(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDummy_View2(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDummy_View3(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDummy_View4(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDummy_View5(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDummy_Close(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTDummy_Ftbl[MAX_TESTVIEW_NUM] = {
    UTDummy_Create,
    UTDummy_View1,
    UTDummy_View2,
    UTDummy_View3,
    UTDummy_View4,
    UTDummy_View5,
    UTDummy_Close
};

/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTDummy_H__ */
