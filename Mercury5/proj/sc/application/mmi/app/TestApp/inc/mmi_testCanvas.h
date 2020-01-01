/**
* @file mmi_testCanvas.h
*/
#ifndef __MMI_TESTCANVAS_H__
#define __MMI_TESTCANVAS_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Canvas Widget
*/
MAE_Ret UTCanvas_Create(IWidget **pWdg, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nContainerID);
MAE_Ret UTCanvas_View1(IWidget *pWdg, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTCanvas_View2(IWidget *pWdg, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTCanvas_View3(IWidget *pWdg, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTCanvas_View4(IWidget *pWdg, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTCanvas_View5(IWidget *pWdg, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTCanvas_Close(IWidget *pWdg, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTCanvas_Ftbl[MAX_TESTVIEW_NUM] = {
    UTCanvas_Create,
    UTCanvas_View1,
    UTCanvas_View2,
    UTCanvas_View3,
    UTCanvas_View4,
    UTCanvas_View5,
    UTCanvas_Close
};

/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTCANVAS_H__ */
