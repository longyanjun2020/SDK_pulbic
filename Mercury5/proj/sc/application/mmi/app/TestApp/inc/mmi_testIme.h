/**
* @file mmi_testIme.h
*/
#ifndef __MMI_TESTIme_H__
#define __MMI_TESTIme_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Ime Widget
*/
MAE_Ret UTIme_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTIme_View1(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTIme_View2(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTIme_View3(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTIme_View4(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTIme_View5(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTIme_Close(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTIme_Ftbl[MAX_TESTVIEW_NUM] = {
    UTIme_Create,
    UTIme_View1,
    UTIme_View2,
    UTIme_View3,
    UTIme_View4,
    UTIme_View5,
    UTIme_Close
};

/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTIme_H__ */
