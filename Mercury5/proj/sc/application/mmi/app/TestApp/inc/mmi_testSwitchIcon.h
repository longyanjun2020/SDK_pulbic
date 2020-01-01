/**
* @file mmi_testSwitchIcon.h
*/
#ifndef __MMI_TESTSWITCHICON_H__
#define __MMI_TESTSWITCHICON_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* SwitchIcon Widget
*/
MAE_Ret UTSwitchIcon_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTSwitchIcon_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSwitchIcon_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSwitchIcon_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSwitchIcon_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSwitchIcon_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSwitchIcon_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTSwitchIcon_Ftbl[MAX_TESTVIEW_NUM] = {
    UTSwitchIcon_Create,
    UTSwitchIcon_View1,
    UTSwitchIcon_View2,
    UTSwitchIcon_View3,
    UTSwitchIcon_View4,
    UTSwitchIcon_View5,
    UTSwitchIcon_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTSwitchIcon_H__ */
