/**
* @file mmi_testThmText.h
*/
#ifndef __MMI_TESTThmText_H__
#define __MMI_TESTThmText_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* ThmText Widget
*/
MAE_Ret UTThmText_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTThmText_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTThmText_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTThmText_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTThmText_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTThmText_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTThmText_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTThmText_Ftbl[MAX_TESTVIEW_NUM] = {
    UTThmText_Create,
    UTThmText_View1,
    UTThmText_View2,
    UTThmText_View3,
    UTThmText_View4,
    UTThmText_View5,
    UTThmText_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTThmText_H__ */
