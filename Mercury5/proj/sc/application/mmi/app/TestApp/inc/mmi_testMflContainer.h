/**
* @file mmi_testMflContainer.h
*/
#ifndef __MMI_TESTMflContainer_H__
#define __MMI_TESTMflContainer_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* MflContainer Widget
*/
MAE_Ret UTMflContainer_Create(IWidget **ppContainer, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nContainerID);
MAE_Ret UTMflContainer_View1(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTMflContainer_View2(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTMflContainer_View3(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTMflContainer_View4(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTMflContainer_View5(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTMflContainer_Close(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTMflContainer_Ftbl[MAX_TESTVIEW_NUM] = {
    UTMflContainer_Create,
    UTMflContainer_View1,
    UTMflContainer_View2,
    UTMflContainer_View3,
    UTMflContainer_View4,
    UTMflContainer_View5,
    UTMflContainer_Close
};

/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTMflContainer_H__ */
