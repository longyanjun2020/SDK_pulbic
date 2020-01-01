/**
* @file mmi_testViewport.h
*/
#ifndef __MMI_TESTVIEWPORT_H__
#define __MMI_TESTVIEWPORT_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Viewport Widget
*/
MAE_Ret UTViewport_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTViewport_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTViewport_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTViewport_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTViewport_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTViewport_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTViewport_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTViewport_Ftbl[MAX_TESTVIEW_NUM] = {
    UTViewport_Create,
    UTViewport_View1,
    UTViewport_View2,
    UTViewport_View3,
    UTViewport_View4,
    UTViewport_View5,
    UTViewport_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTVIEWPORT_H__ */
