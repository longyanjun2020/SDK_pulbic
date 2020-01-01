/**
* @file mmi_testSearchDesktop.h
*/
#ifndef __MMI_TESTSearchDesktop_H__
#define __MMI_TESTSearchDesktop_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

#ifdef __GADGETS_MMI__
/*-------------------------------------------------------------------------*/
/**
* SearchDesktop Widget
*/
MAE_Ret UTSearchDesktop_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTSearchDesktop_View1(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSearchDesktop_View2(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSearchDesktop_View3(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSearchDesktop_View4(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSearchDesktop_View5(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSearchDesktop_Close(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTSearchDesktop_Ftbl[MAX_TESTVIEW_NUM] = {
    UTSearchDesktop_Create,
    UTSearchDesktop_View1,
    UTSearchDesktop_View2,
    UTSearchDesktop_View3,
    UTSearchDesktop_View4,
    UTSearchDesktop_View5,
    UTSearchDesktop_Close
};
#endif //__GADGETS_MMI__

/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTSearchDesktop_H__ */
