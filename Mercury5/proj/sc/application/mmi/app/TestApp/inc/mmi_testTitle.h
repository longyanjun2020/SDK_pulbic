/**
* @file mmi_testTitle.h
*/
#ifndef __MMI_TESTTITLE_H__
#define __MMI_TESTTITLE_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Title Widget
*/
MAE_Ret UTTitle_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTTitle_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTitle_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTitle_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTitle_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTitle_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTitle_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTTitle_Ftbl[MAX_TESTVIEW_NUM] = {
    UTTitle_Create,
    UTTitle_View1,
    UTTitle_View2,
    UTTitle_View3,
    UTTitle_View4,
    UTTitle_View5,
    UTTitle_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTTITLE_H__ */
