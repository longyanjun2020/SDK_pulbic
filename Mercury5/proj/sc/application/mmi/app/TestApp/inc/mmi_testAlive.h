/**
* @file mmi_testAlive.h
*/
#ifndef __MMI_TESTAlive_H__
#define __MMI_TESTAlive_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Alive Widget
*/
MAE_Ret UTAlive_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTAlive_View1(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTAlive_View2(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTAlive_View3(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTAlive_View4(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTAlive_View5(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTAlive_Close(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTAlive_Ftbl[MAX_TESTVIEW_NUM] = {
    UTAlive_Create,
    UTAlive_View1,
    UTAlive_View2,
    UTAlive_View3,
    UTAlive_View4,
    UTAlive_View5,
    UTAlive_Close
};

/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTAlive_H__ */
