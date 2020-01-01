
#ifndef _MENU_DRAW_CAMERA_FUNC_H_
#define _MENU_DRAW_CAMERA_FUNC_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/ 
 
#include "ahc_common.h"
#include "ahc_gui.h"

/*===========================================================================
 * Function prototype 
 *===========================================================================*/ 

void DrawSubItem_FlashLevel( UINT16 uwDisplayID, int iItem, int iTotalItems, UINT32 iStrID, GUI_BITMAP barID, GUI_COLOR colorFont, GUI_COLOR ColorBack, GUI_COLOR colorSelect );
void MenuDrawSubPage_FlashLevel(PSMENUSTRUCT pMenu );
void MenuDrawChangeSubItem_FlashLevel(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected );

#endif //_MENU_DRAW_CAMERA_FUNC_H_

