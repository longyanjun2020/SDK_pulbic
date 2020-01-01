/**
* @file mmi_testCommonPick.h
*/
#ifndef __MMI_TESTCOMMONPICK_H__
#define __MMI_TESTCOMMONPICK_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* CommonPick Widget
*/
MAE_Ret UTCommonPick_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTCommonPick_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTCommonPick_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTCommonPick_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTCommonPick_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTCommonPick_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTCommonPick_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTCommonPick_Ftbl[MAX_TESTVIEW_NUM] = {
    UTCommonPick_Create,
    UTCommonPick_View1,
    UTCommonPick_View2,
    UTCommonPick_View3,
    UTCommonPick_View4,
    UTCommonPick_View5,
    UTCommonPick_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTCommonPick_H__ */
