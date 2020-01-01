/**
* @file mmi_testDouble.h
*/
#ifndef __MMI_TESTDouble_H__
#define __MMI_TESTDouble_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Double Widget
*/
MAE_Ret UTDouble_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTDouble_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDouble_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDouble_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDouble_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDouble_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDouble_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTDouble_Ftbl[MAX_TESTVIEW_NUM] = {
    UTDouble_Create,
    UTDouble_View1,
    UTDouble_View2,
    UTDouble_View3,
    UTDouble_View4,
    UTDouble_View5,
    UTDouble_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTDouble_H__ */
