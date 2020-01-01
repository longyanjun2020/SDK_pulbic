/**
* @file mmi_testSlideSwitch.h
*/
#ifndef __MMI_TESTSLIDESWITCH_H__
#define __MMI_TESTSLIDESWITCH_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* SlideSwitch Widget
*/
MAE_Ret UTSlideSwitch_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTSlideSwitch_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSlideSwitch_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSlideSwitch_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSlideSwitch_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSlideSwitch_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSlideSwitch_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTSlideSwitch_Ftbl[MAX_TESTVIEW_NUM] = {
    UTSlideSwitch_Create,
    UTSlideSwitch_View1,
    UTSlideSwitch_View2,
    UTSlideSwitch_View3,
    UTSlideSwitch_View4,
    UTSlideSwitch_View5,
    UTSlideSwitch_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTSlideSwitch_H__ */
