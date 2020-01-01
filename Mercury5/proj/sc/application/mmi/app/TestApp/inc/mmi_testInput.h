/**
* @file mmi_testInput.h
*/
#ifndef __MMI_TESTINPUT_H__
#define __MMI_TESTINPUT_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Input Widget
*/
MAE_Ret UTInput_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTInput_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTInput_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTInput_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTInput_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTInput_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTInput_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTInput_Ftbl[MAX_TESTVIEW_NUM] = {
    UTInput_Create,
    UTInput_View1,
    UTInput_View2,
    UTInput_View3,
    UTInput_View4,
    UTInput_View5,
    UTInput_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTINPUT_H__ */
