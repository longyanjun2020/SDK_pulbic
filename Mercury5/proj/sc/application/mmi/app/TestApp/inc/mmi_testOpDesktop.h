/**
* @file mmi_testOpDesktop.h
*/
#ifndef __MMI_TESTOpDesktop_H__
#define __MMI_TESTOpDesktop_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

#ifdef __GADGETS_MMI__
/*-------------------------------------------------------------------------*/
/**
* OpDesktop Widget
*/
MAE_Ret UTOpDesktop_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTOpDesktop_View1(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTOpDesktop_View2(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTOpDesktop_View3(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTOpDesktop_View4(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTOpDesktop_View5(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTOpDesktop_Close(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTOpDesktop_Ftbl[MAX_TESTVIEW_NUM] = {
    UTOpDesktop_Create,
    UTOpDesktop_View1,
    UTOpDesktop_View2,
    UTOpDesktop_View3,
    UTOpDesktop_View4,
    UTOpDesktop_View5,
    UTOpDesktop_Close
};
#endif //__GADGETS_MMI__

/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTOpDesktop_H__ */
