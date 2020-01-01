/**
* @file mmi_testButton.h
*/
#ifndef __MMI_TESTBUTTON_H__
#define __MMI_TESTBUTTON_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Button Widget
*/
MAE_Ret UTButton_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTButton_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTButton_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTButton_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTButton_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTButton_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTButton_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTButton_Ftbl[MAX_TESTVIEW_NUM] = {
    UTButton_Create,
    UTButton_View1,
    UTButton_View2,
    UTButton_View3,
    UTButton_View4,
    UTButton_View5,
    UTButton_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTBUTTON_H__ */
