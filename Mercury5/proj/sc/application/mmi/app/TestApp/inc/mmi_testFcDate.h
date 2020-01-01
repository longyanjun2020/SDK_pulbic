/**
* @file mmi_testFcDate.h
*/
#ifndef __MMI_TESTFCDATE_H__
#define __MMI_TESTFCDATE_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* FcDate Widget
*/
MAE_Ret UTFcDate_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTFcDate_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTFcDate_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTFcDate_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTFcDate_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTFcDate_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTFcDate_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTFcDate_Ftbl[MAX_TESTVIEW_NUM] = {
    UTFcDate_Create,
    UTFcDate_View1,
    UTFcDate_View2,
    UTFcDate_View3,
    UTFcDate_View4,
    UTFcDate_View5,
    UTFcDate_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTFCDATE_H__ */
