/**
* @file mmi_testBasicBitmap.h
*/
#ifndef __MMI_TESTBasicBitmap_H__
#define __MMI_TESTBasicBitmap_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* BasicBitmap Widget
*/
MAE_Ret UTBasicBitmap_Create(IWidget **ppWigdet, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTBasicBitmap_View1(IWidget *pWigdet, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTBasicBitmap_View2(IWidget *pWigdet, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTBasicBitmap_View3(IWidget *pWigdet, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTBasicBitmap_View4(IWidget *pWigdet, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTBasicBitmap_View5(IWidget *pWigdet, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTBasicBitmap_Close(IWidget *pWigdet, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTBasicBitmap_Ftbl[MAX_TESTVIEW_NUM] = {
    UTBasicBitmap_Create,
    UTBasicBitmap_View1,
    UTBasicBitmap_View2,
    UTBasicBitmap_View3,
    UTBasicBitmap_View4,
    UTBasicBitmap_View5,
    UTBasicBitmap_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTBasicBitmap_H__ */
