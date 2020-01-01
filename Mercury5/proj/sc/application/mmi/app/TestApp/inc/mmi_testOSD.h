/**
* @file mmi_testOSD.h
*/
#ifndef __MMI_TESTOSD_H__
#define __MMI_TESTOSD_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* OSD Widget
*/
MAE_Ret UtOsdCreate(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UtOsdView1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UtOsdView2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UtOsdView3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UtOsdView4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UtOsdView5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UtOsdClose(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTOSD_Ftbl[MAX_TESTVIEW_NUM] = {
    UtOsdCreate,
    UtOsdView1,
    UtOsdView2,
    UtOsdView3,
    UtOsdView4,
    UtOsdView5,
    UtOsdClose
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTOSD_H__ */
