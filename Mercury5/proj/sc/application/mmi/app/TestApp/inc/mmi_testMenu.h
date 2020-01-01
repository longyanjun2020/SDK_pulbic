/**
* @file mmi_testMenu.h
*/
#ifndef __MMI_TESTMenu_H__
#define __MMI_TESTMenu_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Menu Widget
*/
MAE_Ret UTMenu_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTMenu_View1(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTMenu_View2(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTMenu_View3(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTMenu_View4(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTMenu_View5(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTMenu_Close(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTMenu_Ftbl[MAX_TESTVIEW_NUM] = {
    UTMenu_Create,
    UTMenu_View1,
    UTMenu_View2,
    UTMenu_View3,
    UTMenu_View4,
    UTMenu_View5,
    UTMenu_Close
};

/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTMenu_H__ */
