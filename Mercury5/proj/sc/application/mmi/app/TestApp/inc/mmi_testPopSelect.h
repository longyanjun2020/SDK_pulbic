/**
* @file mmi_testPopSelect.h
*/
#ifndef __MMI_TESTPopSelect_H__
#define __MMI_TESTPopSelect_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* PopSelect Widget
*/
MAE_Ret UTPopSelect_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTPopSelect_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTPopSelect_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTPopSelect_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTPopSelect_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTPopSelect_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTPopSelect_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTPopSelect_Ftbl[MAX_TESTVIEW_NUM] = {
    UTPopSelect_Create,
    UTPopSelect_View1,
    UTPopSelect_View2,
    UTPopSelect_View3,
    UTPopSelect_View4,
    UTPopSelect_View5,
    UTPopSelect_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTPopSelect_H__ */
