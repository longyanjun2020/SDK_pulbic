
#ifndef _MENU_DRAW_MEDIA_TOOL_MENU_H_
#define _MENU_DRAW_MEDIA_TOOL_MENU_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "ahc_common.h"
#include "ahc_gui.h"

/*===========================================================================
 * Function prototype 
 *===========================================================================*/ 

void DrawSubItem_FormatSDCard( UINT16 uwDisplayID, int iItem, int iTotalItems, UINT32 iStrID, const GUI_BITMAP* IconID, GUI_COLOR colorFont, GUI_BITMAP barID,GUI_COLOR ColorBack, GUI_COLOR colorSelect );
void MenuDrawSubPage_FormatSDCard(PSMENUSTRUCT pMenu );
void MenuDrawChangeSubItem_FormatSDCard(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected );
void DrawSubItem_FormatINTMemory( UINT16 uwDisplayID, int iItem, int iTotalItems, UINT32 iStrID, const GUI_BITMAP* IconID, GUI_COLOR colorFont, GUI_BITMAP barID,GUI_COLOR ColorBack, GUI_COLOR colorSelect );
void MenuDrawSubPage_FormatINTMemory(PSMENUSTRUCT pMenu );
void MenuDrawChangeSubItem_FormatINTMemory(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected );
void DrawSubItem_StorageInfo( UINT16 uwDisplayID, int iItem, UINT32 iStrID, GUI_COLOR colorFont, GUI_COLOR ColorBack );
void MenuDrawSubPage_StorageInfo(PSMENUSTRUCT pMenu );

#endif //_MENU_DRAW_MEDIA_TOOL_MENU_H_

