/**
* @file mmi_testRinglist.h
*/
#ifndef __MMI_TESTRinglist_H__
#define __MMI_TESTRinglist_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Ringlist Widget
*/
MAE_Ret UTRinglist_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTRinglist_View1(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTRinglist_View2(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTRinglist_View3(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTRinglist_View4(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTRinglist_View5(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTRinglist_Close(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTRinglist_Ftbl[MAX_TESTVIEW_NUM] = {
    UTRinglist_Create,
    UTRinglist_View1,
    UTRinglist_View2,
    UTRinglist_View3,
    UTRinglist_View4,
    UTRinglist_View5,
    UTRinglist_Close
};

/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTRinglist_H__ */
