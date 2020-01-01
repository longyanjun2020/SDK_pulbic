/**
* @file mmi_testNoteDesktop.h
*/
#ifndef __MMI_TESTNoteDesktop_H__
#define __MMI_TESTNoteDesktop_H__

/*-------------------------------------------------------------------------*/

#include "mmi_testCommonDef.h"

#ifdef __GADGETS_MMI__
/*-------------------------------------------------------------------------*/
/**
* NoteDesktop Widget
*/
MAE_Ret UTNoteDesktop_Create(IWidget **ppWidget, u32 nStyle, WidgetSize_t *pSize, Pos_t *pWPos, HWIN hWin, u16 nWidgetID);
MAE_Ret UTNoteDesktop_View1(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTNoteDesktop_View2(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTNoteDesktop_View3(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTNoteDesktop_View4(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTNoteDesktop_View5(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);
MAE_Ret UTNoteDesktop_Close(IWidget *ppWidget, u32 nParam1, u32 nParam2, IBase *pOwner);

static void* UTNoteDesktop_Ftbl[MAX_TESTVIEW_NUM] = {
    UTNoteDesktop_Create,
    UTNoteDesktop_View1,
    UTNoteDesktop_View2,
    UTNoteDesktop_View3,
    UTNoteDesktop_View4,
    UTNoteDesktop_View5,
    UTNoteDesktop_Close
};
#endif //__GADGETS_MMI__

/*-------------------------------------------------------------------------*/
#endif /* __MMI_TESTNoteDesktop_H__ */
