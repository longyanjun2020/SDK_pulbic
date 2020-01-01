/**
* @file mmi_testScrollBar.h
*/
#ifndef __MMI_TESTSCROLLBAR_H__
#define __MMI_TESTSCROLLBAR_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* ScrollBar Widget
*/
MAE_Ret UTScrollBar_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTScrollBar_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTScrollBar_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTScrollBar_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTScrollBar_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTScrollBar_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTScrollBar_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTScrollBar_Ftbl[MAX_TESTVIEW_NUM] = {
    UTScrollBar_Create,
    UTScrollBar_View1,
    UTScrollBar_View2,
    UTScrollBar_View3,
    UTScrollBar_View4,
    UTScrollBar_View5,
    UTScrollBar_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTSCROLLBAR_H__ */
