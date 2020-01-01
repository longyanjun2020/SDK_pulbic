
#ifndef _MENU_DRAWING_DRIVE_ID_FUNC_H_
#define _MENU_DRAWING_DRIVE_ID_FUNC_H_

#include "Customer_config.h"

#if MENU_GENERAL_DRIVER_ID_SETTING_EN

/*===========================================================================
 * Include file 
 *===========================================================================*/ 

/*===========================================================================
 * Global varible
 *===========================================================================*/ 

extern char Driverid[10];
extern char tmpDriverId[10];

extern AHC_BOOL initDriverId;

/*===========================================================================
 * Global varible : Item Structure
 *===========================================================================*/

extern SMENUITEM sItemDriverIdSettings;
//extern SMENUITEM sItemDriverIdSettings_D0;
//extern SMENUITEM sItemDriverIdSettings_D1;
//extern SMENUITEM sItemDriverIdSettings_D2;
//extern SMENUITEM sItemDriverIdSettings_D3;
//extern SMENUITEM sItemDriverIdSettings_D4;
//extern SMENUITEM sItemDriverIdSettings_D5;
//extern SMENUITEM sItemDriverIdSettings_D6;
//extern SMENUITEM sItemDriverIdSettings_D7;
//extern SMENUITEM sItemDriverIdSettings_D8;
//extern SMENUITEM sItemDriverIdSettings_OK;
//extern SMENUITEM sItemDriverIdSettings_Cancel;

/*===========================================================================
 * Global varible : Item List
 *===========================================================================*/

//extern PSMENUITEM sMenuListDriverIdSettings[];

/*===========================================================================
 * Global varible : Menu Structure
 *===========================================================================*/

extern SMENUSTRUCT sSubDriverIdSettings;

/*===========================================================================
 * Macro definition
 *===========================================================================*/ 

/* Drvier Id Default Value */ // TBC
#define DRIVER_ID_DEFAULT_D0			' '
#define DRIVER_ID_DEFAULT_D1			' '
#define DRIVER_ID_DEFAULT_D2			' '
#define DRIVER_ID_DEFAULT_D3			' '
#define DRIVER_ID_DEFAULT_D4			' '
#define DRIVER_ID_DEFAULT_D5			' '
#define DRIVER_ID_DEFAULT_D6			' '
#define DRIVER_ID_DEFAULT_D7			' '
#define DRIVER_ID_DEFAULT_D8			' '

#define DRIVER_ID_MAX					(35)
#define DRIVER_ID_MIN					(0)

/* Driver Id Validation: D0 D1 D2 D3 D4 D5 D6 D7 D8 */ // TBC
/*                   EX: 1  6  8  A  I  T  8  8  8  */
#define IDX_DRIVER_ID_D0				(0)
#define IDX_DRIVER_ID_D1				(1)
#define IDX_DRIVER_ID_D2				(2)
#define IDX_DRIVER_ID_D3				(3)
#define IDX_DRIVER_ID_D4				(4)
#define IDX_DRIVER_ID_D5				(5)
#define IDX_DRIVER_ID_D6				(6)
#define IDX_DRIVER_ID_D7				(7)
#define IDX_DRIVER_ID_D8				(8)

#define DRIVER_ID_DEFAULT 				"         "

#define CHECK_DRIVER_ID_PASS			(0xFFFF)

#define CHECK_DRIVER_ID_D0				(0x0001)
#define CHECK_DRIVER_ID_D1				(0x0002)
#define CHECK_DRIVER_ID_D2				(0x0004)
#define CHECK_DRIVER_ID_D3				(0x0008)
#define CHECK_DRIVER_ID_D4				(0x0010)
#define CHECK_DRIVER_ID_D5				(0x0020)
#define CHECK_DRIVER_ID_D6				(0x0040)
#define CHECK_DRIVER_ID_D7				(0x0080)
#define CHECK_DRIVER_ID_D8				(0x0100)
#define CHECK_DRIVER_ID_ALL				(CHECK_DRIVER_ID_D0 | CHECK_DRIVER_ID_D1 | CHECK_DRIVER_ID_D2 | CHECK_DRIVER_ID_D3 | CHECK_DRIVER_ID_D4 | CHECK_DRIVER_ID_D5 | CHECK_DRIVER_ID_D6 | CHECK_DRIVER_ID_D7 | CHECK_DRIVER_ID_D8)

/* Touch Button Icon Position for Driver ID Settings */ // TBD
#define RECT_TOUCH_BUTTON_DRIVER_ID_UP		{140, 55,  44,  36}
#define RECT_TOUCH_BUTTON_DRIVER_ID_DOWN	{140, 150, 44,  36}
#define RECT_TOUCH_BUTTON_DRIVER_ID_RIGHT	{150, 206, 44,  36}
#define RECT_TOUCH_BUTTON_DRIVER_ID_OK		{105, 206, 102, 30}

/*===========================================================================
 * Structure definition
 *===========================================================================*/ 



/*===========================================================================
 * Enum definition
 *===========================================================================*/ 



/*===========================================================================
 * Function prototype
 *===========================================================================*/ 

extern int pf_SetDriverID(void);

extern void GetSubItemRect_DriverIdSetting(int i, RECT* pRc);
extern int 	GetSubItemDriverIdSetting_Driverid(int iItems);
extern void DrawSubItem_DriverIdSetting(UINT16 uwDisplayID, int iItem, UINT32 iStrID, GUI_COLOR colorFont, GUI_BITMAP barID, GUI_COLOR ColorBack, GUI_COLOR colorSelect);
extern void DrawSubItem_DriverIdSettingUD(UINT16 uwDisplayID, int iItem, int iOffset, GUI_COLOR colorFont, GUI_COLOR ColorBack);
extern void MenuDrawSubPage_DriverIdSetting(PSMENUSTRUCT pMenu);
extern void MenuDrawChangeSubItem_DriverIdSetting(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected);
extern void MenuDrawChangeSubItem_DriverIdSettingUD(PSMENUSTRUCT pMenu, int iOffset);

extern UINT16 	AHC_Validate_DriverIdSetting(char *pDriverId, UINT16 ubCheckType, AHC_BOOL bAutoRestore, int iOffset);
extern AHC_BOOL AHC_RestoreDefaultDriverId(char *pDriverId0, char *pDriverId1, char *pDriverId2,
                                           char *pDriverId3, char *pDriverId4, char *pDriverId5,
                                           char *pDriverId6, char *pDriverId7, char *pDriverId8);  // TBD

extern AHC_BOOL MenuInitDriverId(void);
extern UINT32 	SubMenuEventHandler_DriverIdSetting(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam);

extern void MenuStateDriverIdSettingsMode(UINT32 ulEvent, UINT32 ulPosition);  // TBC

#endif	// MENU_GENERAL_DRIVER_ID_SETTING_EN) && !defined(_OEM_MENU_)

#endif	// _MENU_DRAWING_DRIVE_ID_FUNC_H_
