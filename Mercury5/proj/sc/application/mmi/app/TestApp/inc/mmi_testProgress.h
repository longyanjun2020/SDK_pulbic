/**
* @file mmi_testProgress.h
*/
#ifndef __MMI_TESTPROGRESS_H__
#define __MMI_TESTPROGRESS_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Progress Widget
*/
MAE_Ret UTProgress_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTProgress_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTProgress_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTProgress_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTProgress_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTProgress_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTProgress_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTProgress_Ftbl[MAX_TESTVIEW_NUM] = {
    UTProgress_Create,
    UTProgress_View1,
    UTProgress_View2,
    UTProgress_View3,
    UTProgress_View4,
    UTProgress_View5,
    UTProgress_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTPROGRESS_H__ */
