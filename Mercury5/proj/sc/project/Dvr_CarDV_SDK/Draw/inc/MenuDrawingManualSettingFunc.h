
#ifndef _MENU_DRAW_MANUAL_SETTING_MENU_H_
#define _MENU_DRAW_MANUAL_SETTING_MENU_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "ahc_common.h"
#include "ahc_gui.h"

/*===========================================================================
 * Function prototype 
 *===========================================================================*/ 

void MenuDrawSubButtons_EV( UINT16  uwDisplayID );
GUI_COLOR GetSubItemColor_EV(  int iItems  );
void DrawSubItem_EV( UINT16 uwDisplayID, int iItem, int iTotalItems, GUI_COLOR colorFont, GUI_COLOR ColorBack, GUI_COLOR colorSelect );
void MenuDrawSubPage_EV(PSMENUSTRUCT pMenu );
void MenuDrawChangeSubItem_EV(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected );

void MenuDrawSubButtons_Contrast( UINT16  uwDisplayID );
GUI_COLOR GetSubItemColor_Contrast(  int iItems  );
void DrawSubItem_Contrast( UINT16 uwDisplayID, int iItem, int iTotalItems, GUI_COLOR colorFont, GUI_COLOR ColorBack, GUI_COLOR colorSelect );
void MenuDrawSubPage_Contrast(PSMENUSTRUCT pMenu );
void MenuDrawChangeSubItem_Contrast(void);

void MenuDrawSubButtons_Saturation( UINT16  uwDisplayID );
GUI_COLOR GetSubItemColor_Saturation(  int iItems  );
void DrawSubItem_Saturation( UINT16 uwDisplayID, int iItem, int iTotalItems, GUI_COLOR colorFont, GUI_COLOR ColorBack, GUI_COLOR colorSelect );
void MenuDrawSubPage_Saturation(PSMENUSTRUCT pMenu );
void MenuDrawChangeSubItem_Saturation(void);

void MenuDrawSubButtons_Sharpness( UINT16  uwDisplayID );
GUI_COLOR GetSubItemColor_Sharpness(  int iItems  );
void DrawSubItem_Sharpness( UINT16 uwDisplayID, int iItem, int iTotalItems, GUI_COLOR colorFont, GUI_COLOR ColorBack, GUI_COLOR colorSelect );
void MenuDrawSubPage_Sharpness(PSMENUSTRUCT pMenu );
void MenuDrawChangeSubItem_Sharpness(void);

void MenuDrawSubButtons_Gamma( UINT16  uwDisplayID );
GUI_COLOR GetSubItemColor_Gamma(  int iItems  );
void DrawSubItem_Gamma( UINT16 uwDisplayID, int iItem, int iTotalItems, GUI_COLOR colorFont, GUI_COLOR ColorBack, GUI_COLOR colorSelect );
void MenuDrawSubPage_Gamma(PSMENUSTRUCT pMenu );
void MenuDrawChangeSubItem_Gamma(void);

#endif //_MENU_DRAW_MANUAL_SETTING_MENU_H_

