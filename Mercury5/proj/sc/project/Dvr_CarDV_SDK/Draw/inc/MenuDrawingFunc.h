
#ifndef _MENU_DRAWING_MENU_H_
#define _MENU_DRAWING_MENU_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "Customer_config.h"
#include "ahc_common.h"
#include "ahc_gui.h"
#include "ColorDefine.h"
#include "MenuCommon.h"
#include "MenuDrawingDriveIdFunc.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

#define QUICK_MENU_TOTAL_ITEM		(8)

#define CONFIRM_MENU_PAGE_ITEM		(2)
#define TV_MENU_BK_COLOR			(OSD_COLOR_DARKGRAY2)
#define TOP_MENU_BK_COLOR			(OSD_COLOR_DARKGRAY2)

#if defined(DOT_MATRIX_PANEL)

#define MAIN_MENU_PAGE_ITEM			(2)
#define SUB_MENU_PAGE_ITEM			(2)
#define TV_MAIN_MENU_PAGE_ITEM		(3)
#define TV_SUB_MENU_PAGE_ITEM		(6)
#define MENU_BACKGROUND_COLOR		(OSD_COLOR_BACKGROUND)
#define MENU_R1BK_COLOR				(OSD_COLOR_BACKGROUND)
#define MENU_R2BK_COLOR				(OSD_COLOR_BACKGROUND)
#define MENU_R3BK_COLOR				(OSD_COLOR_BACKGROUND)
#define MENU_TEXT_COLOR				(OSD_COLOR_WHITE)
#define MENU_LINE_COLOR				(OSD_COLOR_WHITE)
#define MENU_FOCUS_COLOR			(OSD_COLOR_DARKYELLOW)
#define RECT_ROUND_RADIUS			(3)
#define DMP_OSD_TEXT_COLOR			(OSD_COLOR_DARKBLUE)
#define DMP_OSD_BK_COLOR			(OSD_COLOR_WHITE)	

#elif defined(FONT_LARGE)

#define MAIN_MENU_PAGE_ITEM			(3)
#define SUB_MENU_PAGE_ITEM			(3)
#define MENU_BACKGROUND_COLOR		(OSD_COLOR_BACKGROUND)
#define MENU_R1BK_COLOR				(OSD_COLOR_BACKGROUND)
#define MENU_R2BK_COLOR				(OSD_COLOR_BACKGROUND)
#define MENU_R3BK_COLOR				(OSD_COLOR_BACKGROUND)
#define MENU_TEXT_COLOR				(OSD_COLOR_WHITE)
#define MENU_LINE_COLOR				(OSD_COLOR_WHITE)
#define MENU_FOCUS_COLOR			(OSD_COLOR_DARKYELLOW)
#define RECT_ROUND_RADIUS			(3)

#else	// FONT_LARGE

#define MAIN_MENU_PAGE_ITEM			(3)
#define SUB_MENU_PAGE_ITEM			(6)
#define MENU_BACKGROUND_COLOR		(OSD_COLOR_BACKGROUND)
#define MENU_R1BK_COLOR				(OSD_COLOR_BACKGROUND)
#define MENU_R2BK_COLOR				(OSD_COLOR_BACKGROUND)
#define MENU_R3BK_COLOR				(OSD_COLOR_BACKGROUND)
#define MENU_TEXT_COLOR				(OSD_COLOR_WHITE)
#define MENU_LINE_COLOR				(OSD_COLOR_WHITE)
#define MENU_FOCUS_COLOR			(OSD_COLOR_DARKYELLOW)
#define RECT_ROUND_RADIUS			(3)

#endif	// FONT_LARGE

#define TVNTSC_OffsetX 				(12)
#define TVNTSC_OffsetY 				(3)
#define TVPAL_OffsetX 				(20)  //(360-320)>>1
#define TVPAL_OffsetY 				(10)

/*===========================================================================
 * Extern varible
 *===========================================================================*/ 

extern  const GUI_FONT GUI_FontEnglish12;

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 

void MenuDrawItem(UINT16 uwDispID, PSMENUITEM pCurItem, int iItem, UINT32 iStrID, GUI_BITMAP barID, GUI_COLOR clrFont, GUI_COLOR clrBack, AHC_BOOL bCustom);
void MenuMainDrawIcon(UINT16 uwDisplayID,  int iItem, const GUI_BITMAP* IconID);
void MenuDrawSubTitle(UINT16 uwDisplay, UINT32 iStrID);
void GetQuickMenuItemRect( int i, RECT* pRc );
void MenuDrawPageInfo(UINT16 uwDisplayID, int uiCurrentPage, int uiTotalPage);
void DrawQuickMenuItem(UINT16 uwDisplayID, int iItem, UINT32 iStrID, GUI_COLOR colorFont, GUI_BITMAP barID, GUI_COLOR ColorBack);
void MenuDrawNaviOK(UINT16 uwDisplayID);
void MenuDrawNaviBack(UINT16 uwDisplayID);
void MenuMainDrawBackCurtain(UINT16 uwDisplayID, GUI_COLOR colorBackground);
void MenuDrawTitle(UINT16 uwDisplayID, UINT32 uiStringID);
void MenuMainDrawButtons(UINT16  uwDisplayID );
#if (MENU_WIFI_PAGE_EN)
void DrawCatagoryMenuIcon(UINT16 uwDispID, AHC_BOOL ManualHL, AHC_BOOL MovieHL, AHC_BOOL StillHL, AHC_BOOL PlaybackHL, AHC_BOOL EditHL, AHC_BOOL MediaHL, AHC_BOOL GeneralHL, AHC_BOOL WifiHL);
#else
void DrawCatagoryMenuIcon(UINT16 uwDispID, AHC_BOOL ManualHL, AHC_BOOL MovieHL, AHC_BOOL StillHL, AHC_BOOL PlaybackHL, AHC_BOOL EditHL, AHC_BOOL MediaHL, AHC_BOOL GeneralHL);
#endif
void MenuMainDrawCatagory(UINT16 uwDisplayID, int  iCata);
void MenuDrawMainPage(PSMENUSTRUCT pMenu);
void MenuDrawChangeItem(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected);
void MenuSubDrawBackCurtain(UINT16 uwDisplayID, GUI_COLOR colorBackground);
void MenuDrawSubMenuDescription(UINT16  uwDisplayID, UINT32 iStrID);
void GetSubItemRect(UINT16 uwDispID, int i, int iItems, RECT* pRc );
void MenuDrawSubButtons(UINT16  uwDisplayID);
void DrawSubItem(UINT16 uwDisplayID, int iItem, int iTotalItems, UINT8 uLang, UINT32 iStrID, const GUI_BITMAP* IconID, UINT32 barState, GUI_COLOR colorFont,GUI_COLOR ColorBack, GUI_COLOR colorSelect);
void MenuDrawSubPage(PSMENUSTRUCT pMenu);
void MenuDrawChangeSubItem(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected);
void MenuQuickMenuDrawBackCurtain(UINT16 uwDisplayID, GUI_COLOR colorBackground);
void MenuQuickMenuDrawExit(UINT16 uwDisplayID);
void MenuQuickMenuDrawTitle(UINT16 uwDisplayID, UINT32 uiStringID, GUI_COLOR colorBackground);
void MenuQuickMenuDrawPage(PSMENUSTRUCT pMenu);
void MenuQuickMenuDrawChangeItem(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected);
void MenuQuickMenuDrawPage_Playback(PSMENUSTRUCT pMenu);
void MenuQuickMenuDrawChangeItem_Playback(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected);
void QuickMenuSubDrawBackCurtain(UINT16 uwDisplayID, GUI_COLOR colorBackground);
void QuickMenuDrawSubItem(UINT16 uwDisplayID, int iItem, int iTotalItems, UINT32 iStrID, const GUI_BITMAP* IconID, GUI_COLOR colorFont, GUI_BITMAP barID,GUI_COLOR ColorBack, GUI_COLOR colorSelect);
void QuickMenuDrawSubPage(PSMENUSTRUCT pMenu);
void QuickMenuDrawChangeSubItem(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected);
void QuickMenuDrawSubButtons(UINT16  uwDisplayID,const GUI_BITMAP Bmp1, const GUI_BITMAP Bmp2);

void MenuDrawSubPage_GPSInfo(PSMENUSTRUCT pMenu);
void MenuDraw_SD_Status(void);

void MenuDrawSetMenuAttribute( UINT32	 MenuType,  UINT32    PageItemNum, 	
							   GUI_COLOR R1BkClr,   GUI_COLOR R2BkClr, 
							   GUI_COLOR R3BkClr, 	GUI_COLOR TextClr,  	GUI_COLOR LineClr, 
							   GUI_COLOR FocusClr, 	UINT32    PenSize, 		UINT32    R2SepX);

void MenuDrawSetIconTextSubAttribute( 	UINT32	  MenuType,    UINT32 	 PageType, UINT32    PageItemNum, 
										GUI_COLOR L1BkClr,     GUI_COLOR L2BkClr,  GUI_COLOR TextClr,     
										GUI_COLOR LineClr, 	   GUI_COLOR FocusClr, UINT32    PenSize);
										
void MenuDrawResetRegionSize(void);
void MenuDraw2ndSubPageInit(UINT16 uwDispID, PSMENUSTRUCT pMenu, UINT32 CurtainType);
UINT8 MenuDraw_GetDefaultLanguage(PSMENUSTRUCT pMenu);
void MenuDraw_BatteryStatus(UINT16 ubID);
void MenuDrawSubPage_FlashLevel(PSMENUSTRUCT pMenu);
void MenuDrawSubPage_ClockSetting(PSMENUSTRUCT pMenu);
void MenuDrawSubPage_FwVersionInfo(PSMENUSTRUCT pMenu);
void MenuDrawSubPage_EV(PSMENUSTRUCT pMenu);
void MenuDrawSubPage_StorageInfo(PSMENUSTRUCT pMenu);
void MenuDrawSubPage_Volume(PSMENUSTRUCT pMenu);

/* Edit File Page */
void MenuDrawSubPage_EditOneFile(PSMENUSTRUCT pMenu);
void MenuDrawChangeSubItem_EditOneFile(void);

/* Power Off Page */
void MenuDrawSubPage_PowerOffCancel_TV(void);
void MenuDrawSubPage_PowerOff_TV_Browser(UINT16 uwDispID);
void MenuDrawSubPage_PowerOff_TV_Play(UINT16 uwDispID);
void MenuDrawSubPage_PowerOff_TV(void);
void MenuDrawChangeSubItem_PowerOff_TV(void);
void MenuDrawSubPage_PowerOffCancel_HDMI(void);
void MenuDrawSubPage_PowerOff_HDMI_Browser(UINT16 uwDispID);
void MenuDrawSubPage_PowerOff_HDMI_Play(UINT16 uwDispID);
void MenuDrawSubPage_PowerOff_HDMI(void);
void MenuDrawChangeSubItem_PowerOff_HDMI(void);
void MenuDrawSubPage_PowerOff(PSMENUSTRUCT pMenu);
void MenuDrawChangeSubItem_PowerOff(void);

/* Exit Menu Page */
void MenuDrawExitMainPage(PSMENUSTRUCT pMenu);
void MenuDrawChangeExitItem(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem);

/* Confirmed Page */
void MenuDrawSubPage_ConfirmPage(PSMENUSTRUCT pMenu);
void MenuDrawChangeSubItem_ConfirmPage(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected);

/* Mode Selection Page */
void MenuDrawMainPage_ModeSelect(PSMENUSTRUCT pMenu);
void MenuDrawChangeItem_ModeSelect(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected);

/* A General Menu Page drawing function */
void MenuDrawMenuPage(PSMENUSTRUCT pMenu);
/* Top Menu Page */
void MenuDrawTopMenuPage(PSMENUSTRUCT pMenu);
void MenuDrawChangeTopMenuItem(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected);

/* Slide Menu */
void 	StartSlideMenu(UINT32 ulXpos, INT32 ulXoff, UINT8 ubShow, UINT8 ubEn);
void  	StopSlideMenu(void);
UINT8 	IsSlidingMenu(void);
void	SetSlidingMenuEn(UINT8 bEn);
UINT32 	GetSlideXPostion(void);
void 	SlideSubMenu(void);

/* Slide String */
int  	IsSlideSting(UINT32 idStr);
int  	StartSlideString(UINT16 uwDisplayID,UINT32 idStr, RECT strrc, GUI_BITMAP bar, RECT barrc,GUI_COLOR clrfnt, GUI_COLOR clrbak,int slide);
void 	SlideString(void);
void 	StopSlideString(void);
void 	StopSlideStringIdx(UINT8 idx);
int  	GetSlideStringIdx(UINT32 idStr);

/* Oem Drawing Function */
void Oem_MenuDrawSetMainMenuAttribute(void);
void Oem_MenuDrawSetSubPageMenuAttribute(void);
void Oem_MenuDrawSetSubTextMenuAttribute(void);
void Oem_MenuDrawSetSubIconMenuAttribute(void);

AHC_BOOL AHC_DrawMenuRotateEvent(UINT32 Event, PSMENUSTRUCT pMenu);

#endif //_MENU_DRAWING_MENU_H_

