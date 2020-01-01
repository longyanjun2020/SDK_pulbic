/**
* @file mmi_testImageTextImage.h
*/
#ifndef __MMI_TESTImageTextImage_H__
#define __MMI_TESTImageTextImage_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* ImageTextImage Widget
*/
MAE_Ret UTImageTextImage_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTImageTextImage_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTImageTextImage_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTImageTextImage_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTImageTextImage_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTImageTextImage_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTImageTextImage_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTImageTextImage_Ftbl[MAX_TESTVIEW_NUM] = {
    UTImageTextImage_Create,
    UTImageTextImage_View1,
    UTImageTextImage_View2,
    UTImageTextImage_View3,
    UTImageTextImage_View4,
    UTImageTextImage_View5,
    UTImageTextImage_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTImageTextImage_H__ */
