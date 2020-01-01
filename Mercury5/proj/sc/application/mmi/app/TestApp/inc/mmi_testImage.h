/**
* @file mmi_testimage.h
*/
#ifndef __MMI_TESTIMAGE_H__
#define __MMI_TESTIMAGE_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Image Widget
*/
MAE_Ret UTImage_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTImage_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTImage_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTImage_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTImage_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTImage_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTImage_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTImage_Ftbl[MAX_TESTVIEW_NUM] = {
    UTImage_Create,
    UTImage_View1,
    UTImage_View2,
    UTImage_View3,
    UTImage_View4,
    UTImage_View5,
    UTImage_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTIMAGE_H__ */
