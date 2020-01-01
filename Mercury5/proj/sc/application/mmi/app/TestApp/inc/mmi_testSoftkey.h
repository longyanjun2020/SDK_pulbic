/**
* @file mmi_testSoftkey.h
*/
#ifndef __MMI_TESTSoftkey_H__
#define __MMI_TESTSoftkey_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Softkey Widget
*/
MAE_Ret UTSoftkey_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTSoftkey_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSoftkey_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSoftkey_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSoftkey_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSoftkey_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSoftkey_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTSoftkey_Ftbl[MAX_TESTVIEW_NUM] = {
    UTSoftkey_Create,
    UTSoftkey_View1,
    UTSoftkey_View2,
    UTSoftkey_View3,
    UTSoftkey_View4,
    UTSoftkey_View5,
    UTSoftkey_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTSoftkey_H__ */
