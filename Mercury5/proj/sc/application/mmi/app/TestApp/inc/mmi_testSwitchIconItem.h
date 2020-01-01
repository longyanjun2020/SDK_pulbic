/**
* @file mmi_testSwitchIconItem.h
*/
#ifndef __MMI_TESTSWITCHICONITEM_H__
#define __MMI_TESTSWITCHICONITEM_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* SwitchIconItem Widget
*/
MAE_Ret UTSwitchIconItem_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTSwitchIconItem_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSwitchIconItem_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSwitchIconItem_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSwitchIconItem_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSwitchIconItem_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSwitchIconItem_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTSwitchIconItem_Ftbl[MAX_TESTVIEW_NUM] = {
    UTSwitchIconItem_Create,
    UTSwitchIconItem_View1,
    UTSwitchIconItem_View2,
    UTSwitchIconItem_View3,
    UTSwitchIconItem_View4,
    UTSwitchIconItem_View5,
    UTSwitchIconItem_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTSwitchIconItem_H__ */
