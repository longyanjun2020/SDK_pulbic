
#ifndef _MENU_DRAW_GENERAL_SETTING_MENU_H_
#define _MENU_DRAW_GENERAL_SETTING_MENU_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "ahc_common.h"
#include "ahc_gui.h"

/*===========================================================================
 * Function prototype 
 *===========================================================================*/ 

void MenuDrawSubButtons_ClockSetting(UINT16  uwDisplayID);
void GetSubItemRect_ClockSetting(int i,  RECT* pRc );
int  GetSubItemClockSetting_DateTime(int iItems);
void DrawSubItem_ClockSetting( UINT16 uwDisplayID, int iItem, UINT32 iStrID, GUI_COLOR colorFont, GUI_BITMAP barID, GUI_COLOR ColorBack, GUI_COLOR colorSelect );
void MenuDrawSubPage_ClockSetting(PSMENUSTRUCT pMenu);
void MenuDrawChangeSubItem_ClockSetting(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected);
void DrawSubItem_ClockSettingUP( UINT16 uwDisplayID, int iItem, int iOffset, GUI_COLOR colorFont, GUI_COLOR ColorBack);
void MenuDrawChangeSubItem_ClockSettingUD(PSMENUSTRUCT pMenu, int iOffset );
void DrawSubItem_ResetSetup( UINT16 uwDisplayID, int iItem, int iTotalItems, UINT32 iStrID, const GUI_BITMAP* IconID, GUI_COLOR colorFont, GUI_BITMAP barID,GUI_COLOR ColorBack, GUI_COLOR colorSelect );
void MenuDrawSubPage_ResetSetup(PSMENUSTRUCT pMenu );
void MenuDrawChangeSubItem_ResetSetup(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected);
void DrawSubItem_FwVersionInfo(int iMenuId, UINT16 uwDisplayID, GUI_COLOR colorFont, GUI_COLOR ColorBack );
void MenuDrawSubPage_FwVersionInfo(PSMENUSTRUCT pMenu );
void MenuDrawSubPage_GPSInfo(PSMENUSTRUCT pMenu );
void MenuDrawSubPage_PQAdjust(PSMENUSTRUCT pMenu );
void MenuDrawChangeSubItem_PQAdjust(PSMENUSTRUCT pMenu);

#endif //_MENU_DRAW_GENERAL_SETTING_MENU_H_

