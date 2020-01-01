/**
* @file mmi_testProfile.h
*/
#ifndef __MMI_TESTProfile_H__
#define __MMI_TESTProfile_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

#ifdef __GADGETS_MMI__
/*-------------------------------------------------------------------------*/
/**
* Profile Widget
*/
MAE_Ret UTProfile_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTProfile_View1(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTProfile_View2(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTProfile_View3(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTProfile_View4(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTProfile_View5(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTProfile_Close(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTProfile_Ftbl[MAX_TESTVIEW_NUM] = {
    UTProfile_Create,
    UTProfile_View1,
    UTProfile_View2,
    UTProfile_View3,
    UTProfile_View4,
    UTProfile_View5,
    UTProfile_Close
};
#endif

/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTProfile_H__ */
