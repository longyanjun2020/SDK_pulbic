/**
* @file mmi_testimage_double.h
*/
#ifndef __MMI_TESTIMAGE_DOUBLE_H__
#define __MMI_TESTIMAGE_DOUBLE_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* ImageDouble Widget
*/
MAE_Ret UTImageDouble_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTImageDouble_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTImageDouble_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTImageDouble_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTImageDouble_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTImageDouble_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTImageDouble_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTImageDouble_Ftbl[MAX_TESTVIEW_NUM] = {
    UTImageDouble_Create,
    UTImageDouble_View1,
    UTImageDouble_View2,
    UTImageDouble_View3,
    UTImageDouble_View4,
    UTImageDouble_View5,
    UTImageDouble_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTImageDouble_H__ */
