/**
* @file mmi_testDate.h
*/
#ifndef __MMI_TESTDATE_H__
#define __MMI_TESTDATE_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Date Widget
*/
MAE_Ret UTDate_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTDate_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDate_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDate_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDate_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDate_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDate_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTDate_Ftbl[MAX_TESTVIEW_NUM] = {
    UTDate_Create,
    UTDate_View1,
    UTDate_View2,
    UTDate_View3,
    UTDate_View4,
    UTDate_View5,
    UTDate_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTDATE_H__ */
