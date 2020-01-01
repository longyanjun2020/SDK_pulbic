
#ifndef _MENU_DRAW_PLAYBACK_MENU_H_
#define _MENU_DRAW_PLAYBACK_MENU_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "ahc_common.h"
#include "ahc_gui.h"

/*===========================================================================
 * Function prototype 
 *===========================================================================*/ 

void MenuDrawSubButtons_Volume( UINT16  uwDisplayID );
void DrawSubItem_Volume( UINT16 uwDisplayID, int iItem, int iTotalItems, GUI_COLOR colorFont, GUI_COLOR ColorBack, GUI_COLOR colorSelect );
void MenuDrawSubPage_Volume(PSMENUSTRUCT pMenu );
void MenuDrawChangeSubItem_Volume(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected );
void QuickMenuDrawSubItem_Rotate( UINT16 uwDisplayID, int iItem, int iTotalItems, UINT32 iStrID, const GUI_BITMAP* IconID, GUI_COLOR colorFont, GUI_BITMAP barID,GUI_COLOR ColorBack, GUI_COLOR colorSelect );
void QuickMenuDrawSubPage_Rotate(PSMENUSTRUCT pMenu );
void QuickMenuDrawChangeSubItem_Rotate(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected );
void QuickMenuDrawSubItem_Trimming( UINT16 uwDisplayID, int iItem, int iTotalItems, UINT32 iStrID, const GUI_BITMAP* IconID, GUI_COLOR colorFont, GUI_BITMAP barID,GUI_COLOR ColorBack, GUI_COLOR colorSelect );
void QuickMenuDrawSubPage_Trimming(PSMENUSTRUCT pMenu );
void QuickMenuDrawChangeSubItem_Trimming(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected );

#endif //_MENU_DRAW_PLAYBACK_MENU_H_

