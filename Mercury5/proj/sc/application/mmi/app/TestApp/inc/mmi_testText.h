/**
* @file mmi_testText.h
*/
#ifndef __MMI_TESTTEXT_H__
#define __MMI_TESTTEXT_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Text Widget
*/
MAE_Ret UTText_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTText_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTText_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTText_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTText_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTText_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTText_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTText_Ftbl[MAX_TESTVIEW_NUM] = {
    UTText_Create,
    UTText_View1,
    UTText_View2,
    UTText_View3,
    UTText_View4,
    UTText_View5,
    UTText_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTTEXT_H__ */
