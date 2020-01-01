/**
* @file mmi_testPullDown.h
*/
#ifndef __MMI_TESTPULLDOWN_H__
#define __MMI_TESTPULLDOWN_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* PullDown Widget
*/
MAE_Ret UTPullDown_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTPullDown_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTPullDown_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTPullDown_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTPullDown_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTPullDown_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTPullDown_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTPullDown_Ftbl[MAX_TESTVIEW_NUM] = {
    UTPullDown_Create,
    UTPullDown_View1,
    UTPullDown_View2,
    UTPullDown_View3,
    UTPullDown_View4,
    UTPullDown_View5,
    UTPullDown_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTPULLDOWN_H__ */
