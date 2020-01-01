/**
* @file mmi_testFcTime.h
*/
#ifndef __MMI_TESTFCTIME_H__
#define __MMI_TESTFCTIME_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* FcTime Widget
*/
MAE_Ret UTFCTime_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTFCTime_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTFCTime_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTFCTime_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTFCTime_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTFCTime_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTFCTime_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTFcTime_Ftbl[MAX_TESTVIEW_NUM] = {
    UTFCTime_Create,
    UTFCTime_View1,
    UTFCTime_View2,
    UTFCTime_View3,
    UTFCTime_View4,
    UTFCTime_View5,
    UTFCTime_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTFCTIME_H__ */
