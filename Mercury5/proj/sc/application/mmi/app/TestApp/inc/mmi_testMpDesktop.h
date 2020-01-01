/**
* @file mmi_testMpDesktop.h
*/
#ifndef __MMI_TESTMpDesktop_H__
#define __MMI_TESTMpDesktop_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

#ifdef __GADGETS_MMI__
/*-------------------------------------------------------------------------*/
/**
* MpDesktop Widget
*/
MAE_Ret UTMpDesktop_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTMpDesktop_View1(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTMpDesktop_View2(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTMpDesktop_View3(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTMpDesktop_View4(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTMpDesktop_View5(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTMpDesktop_Close(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTMpDesktop_Ftbl[MAX_TESTVIEW_NUM] = {
    UTMpDesktop_Create,
    UTMpDesktop_View1,
    UTMpDesktop_View2,
    UTMpDesktop_View3,
    UTMpDesktop_View4,
    UTMpDesktop_View5,
    UTMpDesktop_Close
};
#endif

/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTMpDesktop_H__ */
