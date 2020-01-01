/**
* @file mmi_testList.h
*/
#ifndef __MMI_TESTList_H__
#define __MMI_TESTList_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* List Widget
*/
MAE_Ret UTList_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTList_View1(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTList_View2(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTList_View3(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTList_View4(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTList_View5(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTList_Close(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTList_Ftbl[MAX_TESTVIEW_NUM] = {
    UTList_Create,
    UTList_View1,
    UTList_View2,
    UTList_View3,
    UTList_View4,
    UTList_View5,
    UTList_Close
};

/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTList_H__ */
