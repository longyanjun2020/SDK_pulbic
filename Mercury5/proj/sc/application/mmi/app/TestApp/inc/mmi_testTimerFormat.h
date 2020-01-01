/**
* @file mmi_testTimerFormat.h
*/
#ifndef __MMI_TESTTIMERFORMAT_H__
#define __MMI_TESTTIMERFORMAT_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* TimerFormat Widget
*/
MAE_Ret UTTimerFormat_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTTimerFormat_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTimerFormat_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTimerFormat_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTimerFormat_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTimerFormat_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTTimerFormat_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTTimerFormat_Ftbl[MAX_TESTVIEW_NUM] = {
    UTTimerFormat_Create,
    UTTimerFormat_View1,
    UTTimerFormat_View2,
    UTTimerFormat_View3,
    UTTimerFormat_View4,
    UTTimerFormat_View5,
    UTTimerFormat_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTTIMERFORMAT_H__ */
