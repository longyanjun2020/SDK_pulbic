/**
* @file mmi_testPick.h
*/
#ifndef __MMI_TESTPICK_H__
#define __MMI_TESTPICK_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Pick Widget
*/
MAE_Ret UTPick_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTPick_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTPick_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTPick_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTPick_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTPick_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTPick_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTPick_Ftbl[MAX_TESTVIEW_NUM] = {
    UTPick_Create,
    UTPick_View1,
    UTPick_View2,
    UTPick_View3,
    UTPick_View4,
    UTPick_View5,
    UTPick_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTPick_H__ */
