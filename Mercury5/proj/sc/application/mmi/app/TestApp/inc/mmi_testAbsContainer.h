/**
* @file mmi_testAbsContainer.h
*/
#ifndef __MMI_TESTAbsContainer_H__
#define __MMI_TESTAbsContainer_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* AbsContainer Widget
*/
MAE_Ret UTAbsContainer_Create(IWidget **ppContainer, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nContainerID);
MAE_Ret UTAbsContainer_View1(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTAbsContainer_View2(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTAbsContainer_View3(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTAbsContainer_View4(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTAbsContainer_View5(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTAbsContainer_Close(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTAbsContainer_Ftbl[MAX_TESTVIEW_NUM] = {
    UTAbsContainer_Create,
    UTAbsContainer_View1,
    UTAbsContainer_View2,
    UTAbsContainer_View3,
    UTAbsContainer_View4,
    UTAbsContainer_View5,
    UTAbsContainer_Close
};

/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTAbsContainer_H__ */
