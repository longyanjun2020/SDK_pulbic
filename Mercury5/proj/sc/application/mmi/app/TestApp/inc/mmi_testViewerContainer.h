/**
* @file mmi_testViewerContainer.h
*/
#ifndef __MMI_TESTViewerContainer_H__
#define __MMI_TESTViewerContainer_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* ViewerContainer Widget
*/
MAE_Ret UTViewerContainer_Create(IWidget **ppContainer, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nContainerID);
MAE_Ret UTViewerContainer_View1(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTViewerContainer_View2(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTViewerContainer_View3(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTViewerContainer_View4(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTViewerContainer_View5(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTViewerContainer_Close(IWidget *ppContainer, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTViewerContainer_Ftbl[MAX_TESTVIEW_NUM] = {
    UTViewerContainer_Create,
    UTViewerContainer_View1,
    UTViewerContainer_View2,
    UTViewerContainer_View3,
    UTViewerContainer_View4,
    UTViewerContainer_View5,
    UTViewerContainer_Close
};

/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTViewerContainer_H__ */
