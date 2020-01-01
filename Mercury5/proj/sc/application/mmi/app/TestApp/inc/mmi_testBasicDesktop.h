/**
* @file mmi_testBasicDesktop.h
*/
#ifndef __MMI_TESTBasicDesktop_H__
#define __MMI_TESTBasicDesktop_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

#ifdef __GADGETS_MMI__
/*-------------------------------------------------------------------------*/
/**
* BasicDesktop Widget
*/
MAE_Ret UTBasicDesktop_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTBasicDesktop_View1(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTBasicDesktop_View2(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTBasicDesktop_View3(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTBasicDesktop_View4(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTBasicDesktop_View5(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTBasicDesktop_Close(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTBasicDesktop_Ftbl[MAX_TESTVIEW_NUM] = {
    UTBasicDesktop_Create,
    UTBasicDesktop_View1,
    UTBasicDesktop_View2,
    UTBasicDesktop_View3,
    UTBasicDesktop_View4,
    UTBasicDesktop_View5,
    UTBasicDesktop_Close
};
#endif //__GADGETS_MMI__

/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTBasicDesktop_H__ */
