/**
* @file mmi_testStatusBar.h
*/
#ifndef __MMI_TESTSTATUSBAR_H__
#define __MMI_TESTSTATUSBAR_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* StatusBar Widget
*/
MAE_Ret UTStatusBar_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTStatusBar_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTStatusBar_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTStatusBar_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTStatusBar_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTStatusBar_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTStatusBar_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTStatusBar_Ftbl[MAX_TESTVIEW_NUM] = {
    UTStatusBar_Create,
    UTStatusBar_View1,
    UTStatusBar_View2,
    UTStatusBar_View3,
    UTStatusBar_View4,
    UTStatusBar_View5,
    UTStatusBar_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTSTATUSBAR_H__ */
