
#ifndef _MENU_DRAW_EDIT_TOOL_FUNC_H_
#define _MENU_DRAW_EDIT_TOOL_FUNC_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "ahc_common.h"
#include "ahc_gui.h"

/*===========================================================================
 * Function prototype 
 *===========================================================================*/ 

void DrawSubItem_DeleteAll( UINT16 uwDisplayID, int iItem, int iTotalItems, UINT32 iStrID, const GUI_BITMAP* IconID, GUI_COLOR colorFont, GUI_BITMAP barID, GUI_COLOR ColorBack, GUI_COLOR colorSelect );
void MenuDrawSubPage_DeleteAll(PSMENUSTRUCT pMenu );
void MenuDrawChangeSubItem_DeleteAll(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected );
void DrawSubItem_ProtectAll( UINT16 uwDisplayID, int iItem, int iTotalItems, UINT32 iStrID, const GUI_BITMAP* IconID, GUI_COLOR colorFont, GUI_BITMAP barID,GUI_COLOR ColorBack, GUI_COLOR colorSelect );
void MenuDrawSubPage_ProtectAll(PSMENUSTRUCT pMenu );
void MenuDrawChangeSubItem_ProtectAll(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected );
void DrawProgressBar(UINT32 CurrentIdx, UINT32 MaxIdx, AHC_BOOL bClear);

#endif //_MENU_DRAW_EDIT_TOOL_FUNC_H_

