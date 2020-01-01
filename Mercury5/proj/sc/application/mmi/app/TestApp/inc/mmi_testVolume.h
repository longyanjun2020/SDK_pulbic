/**
* @file mmi_testVolume.h
*/
#ifndef __MMI_TESTVOLUME_H__
#define __MMI_TESTVOLUME_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

/*-------------------------------------------------------------------------*/
/**
* Volume Widget
*/
MAE_Ret UTVolume_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTVolume_View1(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTVolume_View2(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTVolume_View3(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTVolume_View4(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTVolume_View5(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTVolume_Close(IWidget *pWidget, u32 nParam1, u32 nParam2, IBase *pOwner);




static void* UTVolume_Ftbl[MAX_TESTVIEW_NUM] = {
    UTVolume_Create,
    UTVolume_View1,
    UTVolume_View2,
    UTVolume_View3,
    UTVolume_View4,
    UTVolume_View5,
    UTVolume_Close
};
/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTVOLUME_H__ */
