
#ifndef __notepadapp_view__H
#define __notepadapp_view__H

#ifdef __APP_MMI_NOTEPAD__

typedef struct
{
    IWidget *pIMenuWdg;
}NotepadAppNoteListViewWdgList_t;

MAE_Ret NotepadAppCreateNoteListView(HWIN hWin, NotepadAppNoteListViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pIInputWdg;
}NotepadAppEditNoteViewWdgList_t;

MAE_Ret NotepadAppCreateEditNoteView(HWIN hWin, NotepadAppEditNoteViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pIInputWdg;
}NotepadAppViewNoteViewWdgList_t;

MAE_Ret NotepadAppCreateViewNoteView(HWIN hWin, NotepadAppViewNoteViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pIOptionMenuWdg;
}NotepadAppLoadOptionMenuViewWdgList_t;

MAE_Ret NotepadAppCreateLoadOptionMenuView(HWIN hWin, NotepadAppLoadOptionMenuViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pIOptionMenuWdg;
}NotepadAppEditNoteLoadOptionMenuViewWdgList_t;

MAE_Ret NotepadAppCreateEditNoteLoadOptionMenuView(HWIN hWin, NotepadAppEditNoteLoadOptionMenuViewWdgList_t *pWdgList);

//*******************************************************************//
void _NotepadListViewAdaptGet(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);
void _NotepadListViewItemDataFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
MAE_Ret _CreateNoteListItemInfo(NotepadAppData_t *pThis, u16 nIndex, ITSITInfo *ptITSITInfo);

#endif // __APP_MMI_NOTEPAD__

#endif //__notepadapp_view__H

