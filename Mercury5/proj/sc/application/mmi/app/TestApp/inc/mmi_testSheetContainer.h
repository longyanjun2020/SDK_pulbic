/**
* @file mmi_testSheetContainer.h
*/
#ifndef __MMI_TESTSheetContainer_H__
#define __MMI_TESTSheetContainer_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* SheetContainer Widget
*/
MAE_Ret UTSheetContainer_Create(IWidget **ppContainer, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nContainerID);
MAE_Ret UTSheetContainer_View1(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSheetContainer_View2(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSheetContainer_View3(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSheetContainer_View4(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSheetContainer_View5(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTSheetContainer_Close(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTSheetContainer_Ftbl[MAX_TESTVIEW_NUM] = {
    UTSheetContainer_Create,
    UTSheetContainer_View1,
    UTSheetContainer_View2,
    UTSheetContainer_View3,
    UTSheetContainer_View4,
    UTSheetContainer_View5,
    UTSheetContainer_Close
};

IWidget *WDG_A;
IWidget *WDG_B;
IWidget *WDG_C;

Pos_t wPos_A;
Pos_t wPos_B;
Pos_t wPos_C;

WidgetSize_t wSize_A;
WidgetSize_t wSize_B;
WidgetSize_t wSize_C;

/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTSheetContainer_H__ */
