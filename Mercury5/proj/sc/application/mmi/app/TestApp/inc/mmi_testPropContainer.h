/**
* @file mmi_testPropContainer.h
*/
#ifndef __MMI_TESTPropContainer_H__
#define __MMI_TESTPropContainer_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* PropContainer Widget
*/
MAE_Ret UTPropContainer_Create(IWidget **ppContainer, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nContainerID);
MAE_Ret UTPropContainer_View1(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTPropContainer_View2(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTPropContainer_View3(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTPropContainer_View4(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTPropContainer_View5(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTPropContainer_Close(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTPropContainer_Ftbl[MAX_TESTVIEW_NUM] = {
    UTPropContainer_Create,
    UTPropContainer_View1,
    UTPropContainer_View2,
    UTPropContainer_View3,
    UTPropContainer_View4,
    UTPropContainer_View5,
    UTPropContainer_Close
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
#endif /* __MMI_TESTPropContainer_H__ */
