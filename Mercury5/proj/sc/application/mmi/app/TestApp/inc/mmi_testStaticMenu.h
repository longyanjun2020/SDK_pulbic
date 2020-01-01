/**
* @file mmi_testStaticMenu.h
*/
#ifndef __MMI_TESTStaticMenu_H__
#define __MMI_TESTStaticMenu_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* StaticMenu Widget
*/
#define MAX_WDG_TEST_STATICMENU_NUM	  11

MAE_Ret UTStaticMenu_Create(IWidget **ppWidget, u32 nParameter, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTStaticMenu_View1(IWidget **ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTStaticMenu_View2(IWidget **ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTStaticMenu_View3(IWidget **ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTStaticMenu_View4(IWidget **ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTStaticMenu_View5(IWidget **ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTStaticMenu_View6(IWidget **ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTStaticMenu_View7(IWidget **ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTStaticMenu_View8(IWidget **ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTStaticMenu_View9(IWidget **ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTStaticMenu_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTStaticMenu_Ftbl[MAX_WDG_TEST_STATICMENU_NUM] = {
    UTStaticMenu_Create,
    UTStaticMenu_View1,
    UTStaticMenu_View2,
    UTStaticMenu_View3,
    UTStaticMenu_View4,
    UTStaticMenu_View5,
	UTStaticMenu_View6,
	UTStaticMenu_View7,
	UTStaticMenu_View8,
	UTStaticMenu_View9,
    UTStaticMenu_Close
};

/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTStaticMenu_H__ */
