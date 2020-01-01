/**
* @file mmi_testIP.h
*/
#ifndef __MMI_TESTIP_H__
#define __MMI_TESTIP_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* IP Widget
*/
MAE_Ret UTIP_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTIP_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTIP_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTIP_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTIP_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTIP_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTIP_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTIP_Ftbl[MAX_TESTVIEW_NUM] = {
    UTIP_Create,
    UTIP_View1,
    UTIP_View2,
    UTIP_View3,
    UTIP_View4,
    UTIP_View5,
    UTIP_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTIP_H__ */
