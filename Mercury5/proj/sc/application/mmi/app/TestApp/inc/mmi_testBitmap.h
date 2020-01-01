/**
* @file mmi_testBitmap.h
*/
#ifndef __MMI_TESTBitmap_H__
#define __MMI_TESTBitmap_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Bitmap Widget
*/
MAE_Ret UTBitmap_Create(IWidget **ppWigdet, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTBitmap_View1(IWidget *pWigdet, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTBitmap_View2(IWidget *pWigdet, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTBitmap_View3(IWidget *pWigdet, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTBitmap_View4(IWidget *pWigdet, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTBitmap_View5(IWidget *pWigdet, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTBitmap_Close(IWidget *pWigdet, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTBitmap_Ftbl[MAX_TESTVIEW_NUM] = {
    UTBitmap_Create,
    UTBitmap_View1,
    UTBitmap_View2,
    UTBitmap_View3,
    UTBitmap_View4,
    UTBitmap_View5,
    UTBitmap_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTBitmap_H__ */
