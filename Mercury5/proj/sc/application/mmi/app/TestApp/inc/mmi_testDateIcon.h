/**
* @file mmi_testDateIcon.h
*/
#ifndef __MMI_TESTDATEICON_H__
#define __MMI_TESTDATEICON_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* DateIcon Widget
*/
MAE_Ret UTDateIcon_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTDateIcon_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDateIcon_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDateIcon_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDateIcon_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDateIcon_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTDateIcon_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTDateIcon_Ftbl[MAX_TESTVIEW_NUM] = {
    UTDateIcon_Create,
    UTDateIcon_View1,
    UTDateIcon_View2,
    UTDateIcon_View3,
    UTDateIcon_View4,
    UTDateIcon_View5,
    UTDateIcon_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTDateIcon_H__ */
