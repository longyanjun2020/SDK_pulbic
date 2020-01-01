/**
* @file mmi_testFadeOut.h
*/
#ifndef __MMI_TESTFadeOut_H__
#define __MMI_TESTFadeOut_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* FadeOut Widget
*/
MAE_Ret UTFadeOut_Create(IWidget **ppWigdet, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTFadeOut_View1(IWidget *pWigdet, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTFadeOut_View2(IWidget *pWigdet, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTFadeOut_View3(IWidget *pWigdet, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTFadeOut_View4(IWidget *pWigdet, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTFadeOut_View5(IWidget *pWigdet, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTFadeOut_Close(IWidget *pWigdet, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTFadeOut_Ftbl[MAX_TESTVIEW_NUM] = {
    UTFadeOut_Create,
    UTFadeOut_View1,
    UTFadeOut_View2,
    UTFadeOut_View3,
    UTFadeOut_View4,
    UTFadeOut_View5,
    UTFadeOut_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTFadeOut_H__ */
