/**
* @file mmi_testShortCutBar.h
*/
#ifndef __MMI_TESTShortCutBar_H__
#define __MMI_TESTShortCutBar_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* ShortCutBar Widget
*/
MAE_Ret UTShortCutBar_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTShortCutBar_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTShortCutBar_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTShortCutBar_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTShortCutBar_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTShortCutBar_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTShortCutBar_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTShortCutBar_Ftbl[MAX_TESTVIEW_NUM] = {
    UTShortCutBar_Create,
    UTShortCutBar_View1,
    UTShortCutBar_View2,
    UTShortCutBar_View3,
    UTShortCutBar_View4,
    UTShortCutBar_View5,
    UTShortCutBar_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTShortCutBar_H__ */
