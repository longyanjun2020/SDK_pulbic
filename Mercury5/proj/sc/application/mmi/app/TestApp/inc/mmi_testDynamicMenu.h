/**
* @file mmi_testDynamicMenu.h
*/
#ifndef __MMI_TESTDynamicMenu_H__
#define __MMI_TESTDynamicMenu_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* DynamicMenu Widget
*/
#define MAX_WDG_TEST_DYNAMIC_MENU_NUM	  11

MAE_Ret UTDynamicMenu_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTDynamicMenu_View1(IWidget **ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDynamicMenu_View2(IWidget **ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDynamicMenu_View3(IWidget **ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDynamicMenu_View4(IWidget **ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDynamicMenu_View5(IWidget **ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDynamicMenu_View6(IWidget **ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDynamicMenu_View7(IWidget **ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDynamicMenu_View8(IWidget **ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDynamicMenu_View9(IWidget **ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDynamicMenu_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTDynamicMenu_Ftbl[MAX_WDG_TEST_DYNAMIC_MENU_NUM] = {
    UTDynamicMenu_Create,
    UTDynamicMenu_View1,
    UTDynamicMenu_View2,
    UTDynamicMenu_View3,
    UTDynamicMenu_View4,
    UTDynamicMenu_View5,
	UTDynamicMenu_View6,
	UTDynamicMenu_View7,
	UTDynamicMenu_View8,
	UTDynamicMenu_View9,
    UTDynamicMenu_Close
};

/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTDynamicMenu_H__ */
