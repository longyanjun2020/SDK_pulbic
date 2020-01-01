/**
* @file mmi_testEvent.h
*/
#ifndef __MMI_TESTEvent_H__
#define __MMI_TESTEvent_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Event Widget
*/
MAE_Ret UTEvent_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTEvent_View1(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTEvent_View2(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTEvent_View3(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTEvent_View4(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTEvent_View5(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTEvent_Close(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTEvent_Ftbl[MAX_TESTVIEW_NUM] = {
    UTEvent_Create,
    UTEvent_View1,
    UTEvent_View2,
    UTEvent_View3,
    UTEvent_View4,
    UTEvent_View5,
    UTEvent_Close
};

/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTEvent_H__ */
