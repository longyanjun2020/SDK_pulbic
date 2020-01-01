/**
* @file mmi_testDClockDesktop.h
*/
#ifndef __MMI_TESTDClockDesktop_H__
#define __MMI_TESTDClockDesktop_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

#ifdef __GADGETS_MMI__
/*-------------------------------------------------------------------------*/
/**
* DClockDesktop Widget
*/
MAE_Ret UTDClockDesktop_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTDClockDesktop_View1(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDClockDesktop_View2(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDClockDesktop_View3(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDClockDesktop_View4(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDClockDesktop_View5(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDClockDesktop_Close(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTDClockDesktop_Ftbl[MAX_TESTVIEW_NUM] = {
    UTDClockDesktop_Create,
    UTDClockDesktop_View1,
    UTDClockDesktop_View2,
    UTDClockDesktop_View3,
    UTDClockDesktop_View4,
    UTDClockDesktop_View5,
    UTDClockDesktop_Close
};
#endif //__GADGETS_MMI__

/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTDClockDesktop_H__ */
