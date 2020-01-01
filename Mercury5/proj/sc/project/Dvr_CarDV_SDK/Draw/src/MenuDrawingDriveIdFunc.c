/*===========================================================================
 * Include file 
 *===========================================================================*/ 
#include "config_fw.h"

#include "lib_retina.h"
#include "ahc_common.h"
#include "ahc_general.h"
#include "ahc_gui.h"
#include "ahc_macro.h"
#include "ahc_menu.h"
#include "ahc_parameter.h"
#include "MenuDrawCommon.h"
#include "MenuCommon.h"
#include "MenuDrawingFunc.h"
#include "MenuStateGeneralSettingsMenu.h"
#include "MenuStateMenu.h"
#include "ShowOSDFunc.h"
#include "IconPosition.h"
#include "ColorDefine.h"
#include "OSDStrings.h"
#include "IconDefine.h"

#if (MENU_GENERAL_DRIVER_ID_SETTING_EN)

/*===========================================================================
 * Local function
 *===========================================================================*/ 

AHC_BOOL MenuItemDriverIdSettings(PSMENUITEM pItem, AHC_BOOL bIsHover);

/*===========================================================================
 * Global variable
 *===========================================================================*/

char Driverid[10] 		= DRIVER_ID_DEFAULT; // Driverid[0~8], 		initialize default value, DRVIER_ID_DEFAULT is defined in Oem_Menu.h
char tmpDriverId[10] 	= DRIVER_ID_DEFAULT; // tmpDriverId[0~8], 	initialize default value, DRVIER_ID_DEFAULT is defined in Oem_Menu.h

AHC_BOOL initDriverId = AHC_TRUE;

/*===========================================================================
 * Global variable : Item Structure
 *===========================================================================*/

 // Driver Id Settings
SMENUITEM sItemDriverIdSettings 		= { ITEMID_DRIVER_ID_SETTINGS, 	&BMICON_MENU_DRIVER_ID, IDS_DS_DRIVER_ID_SETTINGS, 	&sSubDriverIdSettings, 	0, 							0, AHC_TRUE, NULL };
SMENUITEM sItemDriverIdSettings_D0 		= { ITEMID_DRIVER_ID_D0,		NULL, 					IDS_DS_DRIVER_ID_SETTINGS, 	NULL, 					MenuItemDriverIdSettings, 	0, AHC_TRUE, NULL };
SMENUITEM sItemDriverIdSettings_D1 		= { ITEMID_DRIVER_ID_D1, 		NULL, 					IDS_DS_DRIVER_ID_SETTINGS, 	NULL, 					MenuItemDriverIdSettings, 	0, AHC_TRUE, NULL };
SMENUITEM sItemDriverIdSettings_D2 		= { ITEMID_DRIVER_ID_D2, 		NULL, 					IDS_DS_DRIVER_ID_SETTINGS, 	NULL, 					MenuItemDriverIdSettings, 	0, AHC_TRUE, NULL };
SMENUITEM sItemDriverIdSettings_D3 		= { ITEMID_DRIVER_ID_D3, 		NULL, 					IDS_DS_DRIVER_ID_SETTINGS, 	NULL, 					MenuItemDriverIdSettings, 	0, AHC_TRUE, NULL };
SMENUITEM sItemDriverIdSettings_D4 		= { ITEMID_DRIVER_ID_D4, 		NULL, 					IDS_DS_DRIVER_ID_SETTINGS, 	NULL, 					MenuItemDriverIdSettings, 	0, AHC_TRUE, NULL };
SMENUITEM sItemDriverIdSettings_D5 		= { ITEMID_DRIVER_ID_D5, 		NULL, 					IDS_DS_DRIVER_ID_SETTINGS, 	NULL, 					MenuItemDriverIdSettings, 	0, AHC_TRUE, NULL };
SMENUITEM sItemDriverIdSettings_D6 		= { ITEMID_DRIVER_ID_D6, 		NULL, 					IDS_DS_DRIVER_ID_SETTINGS, 	NULL, 					MenuItemDriverIdSettings, 	0, AHC_TRUE, NULL };
SMENUITEM sItemDriverIdSettings_D7 		= { ITEMID_DRIVER_ID_D7, 		NULL, 					IDS_DS_DRIVER_ID_SETTINGS, 	NULL, 					MenuItemDriverIdSettings, 	0, AHC_TRUE, NULL };
SMENUITEM sItemDriverIdSettings_D8 		= { ITEMID_DRIVER_ID_D8, 		NULL, 					IDS_DS_DRIVER_ID_SETTINGS, 	NULL, 					MenuItemDriverIdSettings, 	0, AHC_TRUE, NULL };
SMENUITEM sItemDriverIdSettings_OK 		= { ITEMID_DRIVER_ID_OK, 		NULL, 					IDS_DS_OK, 					NULL, 					MenuItemDriverIdSettings, 	0, AHC_TRUE, NULL };

/*===========================================================================
 * Global variable : Item List
 *===========================================================================*/

PSMENUITEM sMenuListDriverIdSettings[] = 
{
	&sItemDriverIdSettings_D0,
	&sItemDriverIdSettings_D1,
	&sItemDriverIdSettings_D2,
	&sItemDriverIdSettings_D3,
	&sItemDriverIdSettings_D4,
	&sItemDriverIdSettings_D5,
	&sItemDriverIdSettings_D6,
	&sItemDriverIdSettings_D7,
	&sItemDriverIdSettings_D8,

	&sItemDriverIdSettings_OK
};

/*===========================================================================
 * Global variable : Menu Structure
 *===========================================================================*/

SMENUSTRUCT sSubDriverIdSettings = 
{
	MENUID_SUB_MENU_DRIVER_ID_SETTINGS,
	NULL,
	IDS_DS_DRIVER_ID_SETTINGS,
	NULL,
	sizeof(sMenuListDriverIdSettings)/sizeof(PSMENUITEM),
	sMenuListDriverIdSettings,
#if VIRTUAL_KEY_BOARD_FOR_CAR_ID
    SubMenuEventHandler_Keyboard,//SubMenuEventHandler,
#else
    SubMenuEventHandler_DriverIdSetting,
#endif		
	MenuGetDefault,
	0,
	NULL,
	AHC_TRUE,
	0
};

/*===========================================================================
 * Main body 
 *===========================================================================*/ 

#if 0
void ____Driver_Id_Function____(){ruturn;} // dummy
#endif

void GetSubItemRect_DriverIdSetting(int i,  RECT* pRc)
{
	switch (i)
	{
		case 0: 	{RECT rc = { 30, 110,  16, 14}; *pRc = rc; break;}  // DriverID[0]
		case 1: 	{RECT rc = { 60, 110,  16, 14}; *pRc = rc; break;}  // DriverID[1]
		case 2: 	{RECT rc = { 90, 110,  16, 14}; *pRc = rc; break;}  // DriverID[2]
		case 3: 	{RECT rc = {120, 110,  16, 14}; *pRc = rc; break;}  // DriverID[3]
		case 4: 	{RECT rc = {150, 110,  16, 14}; *pRc = rc; break;}  // DriverID[4]
		case 5: 	{RECT rc = {180, 110,  16, 14}; *pRc = rc; break;}  // DriverID[5]
		case 6: 	{RECT rc = {210, 110,  16, 14}; *pRc = rc; break;}  // DriverID[6]
		case 7: 	{RECT rc = {240, 110,  16, 14}; *pRc = rc; break;}  // DriverID[7]
		case 8: 	{RECT rc = {270, 110,  16, 14}; *pRc = rc; break;}  // DriverID[8]
		case 9: 	{RECT rc = {105, 206, 102, 30}; *pRc = rc; break;}  // OK
		default: 	{RECT rc = { 30, 110,  16, 14}; *pRc = rc; break;}  // DriverID[0]
	}	
}

int GetSubItemDriverIdSetting_Driverid(int iItems)
{
	int	DriverId;

	switch (iItems)
	{
		case 0: {DriverId = tmpDriverId[0]; break;}
		case 1: {DriverId = tmpDriverId[1]; break;}
		case 2: {DriverId = tmpDriverId[2]; break;}
		case 3: {DriverId = tmpDriverId[3]; break;}
		case 4: {DriverId = tmpDriverId[4]; break;}
		case 5: {DriverId = tmpDriverId[5]; break;}
		case 6: {DriverId = tmpDriverId[6]; break;}
		case 7: {DriverId = tmpDriverId[7]; break;}
		//case 8: {DriverId = tmpDriverId[8]; break;}
		default:{DriverId = tmpDriverId[8]; break;}
	}

	return DriverId;
}

void DrawSubItem_DriverIdSetting(UINT16 uwDispID, int iItem, UINT32 iStrID, GUI_COLOR clrFont, GUI_BITMAP barID, GUI_COLOR clrBack, GUI_COLOR clrSelect)
{
	RECT 		rc, tmpRECT;
	int 		DriverId;
	GUI_RECT 	Rect;
	char 		tmpStr[2] = "0";

	GetSubItemRect_DriverIdSetting(iItem, &rc);

	DriverId = GetSubItemDriverIdSetting_Driverid(iItem);

	switch (iItem)
	{
		case 0: // Driverid[0]
		case 1: // Driverid[1]
		case 2: // Driverid[2]
		case 3: // Driverid[3]
		case 4: // Driverid[4]
		case 5: // Driverid[5]
		case 6: // Driverid[6]
		case 7: // Driverid[7]
		case 8: // Driverid[8]
		#if 0 // Draw string below the rectangle
			tmpRECT.uiLeft 		= rc.uiLeft;
			tmpRECT.uiTop 		= rc.uiTop 		+ 24;
			tmpRECT.uiWidth 	= rc.uiWidth 	+ 4;
			tmpRECT.uiHeight 	= rc.uiHeight;
			OSD_ShowStringPool(uwDispID, iStrID, tmpRECT, clrFont, OSD_COLOR_BLACK, GUI_TA_HCENTER | GUI_TA_VCENTER);
		#endif
			break;

		case 9: // OK
			OSD_Draw_Icon(barID, rc, uwDispID);

			tmpRECT.uiLeft 		= rc.uiLeft 	+ STR_RECT_OFFSET_X;
			tmpRECT.uiTop 		= rc.uiTop 		+ STR_RECT_OFFSET_Y;
			tmpRECT.uiWidth 	= rc.uiWidth 	+ STR_RECT_OFFSET_W;
			tmpRECT.uiHeight 	= rc.uiHeight 	+ STR_RECT_OFFSET_H;
			OSD_ShowStringPool(uwDispID, iStrID, tmpRECT, clrFont, clrBack, GUI_TA_HCENTER | GUI_TA_VCENTER);
			break;
	}

	// Draw Driver ID in the rectangle
	if (iItem < 9)
	{
		AHC_OSDSetFont(uwDispID, &GUI_Font24B_1);
		AHC_OSDSetBkColor(uwDispID, clrBack);

		Rect.x0 = rc.uiLeft - 2;
		Rect.y0 = rc.uiTop;
		Rect.x1 = Rect.x0 + rc.uiWidth 	+ 8;
		Rect.y1 = Rect.y0 + rc.uiHeight + 8;

		AHC_OSDSetColor(uwDispID, clrBack);
		AHC_OSDDrawFillRect(uwDispID, Rect.x0, Rect.y0, Rect.x1, Rect.y1);

		tmpStr[0] = tmpDriverId[iItem];

		AHC_OSDSetColor(uwDispID, clrFont);
		AHC_OSDDrawTextInRect(uwDispID, (UINT8*)tmpStr, &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
	}

}

void DrawSubItem_DriverIdSettingUD(UINT16 uwDispID, int iItem, int iOffset, GUI_COLOR clrFont, GUI_COLOR clrBack)
{
	RECT 		rc;
	GUI_RECT 	Rect;
	char 		tmpStr[2] = "0";

	GetSubItemRect_DriverIdSetting(iItem, &rc);

	AHC_OSDSetFont(uwDispID, &GUI_Font24B_1);
	AHC_OSDSetBkColor(uwDispID, clrBack);

	Rect.x0 = rc.uiLeft - 2;
	Rect.y0 = rc.uiTop;
	Rect.x1 = Rect.x0 + rc.uiWidth 	+ 8;
	Rect.y1 = Rect.y0 + rc.uiHeight + 8;

	AHC_OSDSetColor(uwDispID, clrBack);
	AHC_OSDDrawFillRect(uwDispID, Rect.x0, Rect.y0, Rect.x1, Rect.y1);

	tmpDriverId[iItem] += iOffset;
	switch (iItem)
	{
		case 0:
			AHC_Validate_DriverIdSetting(tmpDriverId, CHECK_DRIVER_ID_D0, AHC_TRUE, iOffset);
			tmpStr[0] = tmpDriverId[0];
			break;

		case 1:
			AHC_Validate_DriverIdSetting(tmpDriverId, CHECK_DRIVER_ID_D1, AHC_TRUE, iOffset);
			tmpStr[0] = tmpDriverId[1];
			break;

		case 2:
			AHC_Validate_DriverIdSetting(tmpDriverId, CHECK_DRIVER_ID_D2, AHC_TRUE, iOffset);
			tmpStr[0] = tmpDriverId[2];
			break;

		case 3:
			AHC_Validate_DriverIdSetting(tmpDriverId, CHECK_DRIVER_ID_D3, AHC_TRUE, iOffset);
			tmpStr[0] = tmpDriverId[3];
			break;

		case 4:
			AHC_Validate_DriverIdSetting(tmpDriverId, CHECK_DRIVER_ID_D4, AHC_TRUE, iOffset);
			tmpStr[0] = tmpDriverId[4];
			break;

		case 5:
			AHC_Validate_DriverIdSetting(tmpDriverId, CHECK_DRIVER_ID_D5, AHC_TRUE, iOffset);
			tmpStr[0] = tmpDriverId[5];
			break;

		case 6:
			AHC_Validate_DriverIdSetting(tmpDriverId, CHECK_DRIVER_ID_D6, AHC_TRUE, iOffset);
			tmpStr[0] = tmpDriverId[6];
			break;

		case 7:
			AHC_Validate_DriverIdSetting(tmpDriverId, CHECK_DRIVER_ID_D7, AHC_TRUE, iOffset);
			tmpStr[0] = tmpDriverId[7];
			break;

		case 8:
			AHC_Validate_DriverIdSetting(tmpDriverId, CHECK_DRIVER_ID_D8, AHC_TRUE, iOffset);
			tmpStr[0] = tmpDriverId[8];
			break;

		default:
			break;
	}

	AHC_OSDSetColor(uwDispID, clrFont);
	AHC_OSDDrawTextInRect(uwDispID, (UINT8*)tmpStr, &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
}

void MenuDrawSubPage_DriverIdSetting(PSMENUSTRUCT pMenu)
{
	UINT8 	bID0 = 0, bID1 = 0;
	UINT32 	i;
	UINT32 	iBegin, iEnd;

#ifdef SLIDE_STRING  // TBC
	StopSlideString();
#endif

    OSDDraw_EnterMenuDrawing(&bID0, &bID1);
    
	OSDDraw_ClearOvlDrawBuffer(bID0);
	MenuDrawSubBackCurtain(bID0, OSD_COLOR_BLACK);

	iBegin = ALIGN_DOWN(pMenu->iCurrentPos, 10);
	iEnd = MIN(iBegin + 10, pMenu->iNumOfItems);

	if (pMenu->uiStringId != -1)
	{
		MenuDrawSubTitle(bID0, pMenu->uiStringId);
	}

	for (i = iBegin; i < iEnd; i++)
	{
		GUI_COLOR 	clrBk = OSD_COLOR_DARKGRAY;
		GUI_BITMAP 	barID = BMICON_SMALLBAR_WHITE;

		if (i > 8)
		{
			clrBk = OSD_COLOR_TRANSPARENT;
		}

		if ((i == pMenu->iCurrentPos) && (pMenu->iCurrentPos <= 8))
		{
			clrBk = OSD_COLOR_DARKYELLOW;
		}
		DrawSubItem_DriverIdSetting(bID0, i, pMenu->pItemsList[i]->uiStringId, MENU_TEXT_COLOR, barID, clrBk, 0x0);
	}

	if (pMenu->uiStringDescription != NULL)
	{
		MenuDrawSubMenuDescription(bID0, pMenu->uiStringDescription);
	}


	#if (SUPPORT_TOUCH_PANEL) && !defined CFG_VIRTUAL_TOUCH
		{
			RECT RECTUp 	= RECT_TOUCH_BUTTON_DRIVER_ID_UP;
			RECT RECTDown 	= RECT_TOUCH_BUTTON_DRIVER_ID_DOWN;

			OSD_Draw_Icon(bmIcon_D_Up, RECTUp, bID0);
			OSD_Draw_Icon(bmIcon_D_Down, RECTDown, bID0);
		}
	#endif

	MenuDraw_BatteryStatus(bID0);

	OSDDraw_ExitMenuDrawing(&bID0, &bID1);
}

void MenuDrawChangeSubItem_DriverIdSetting(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected)
{
	UINT8 		bID0 = 0, bID1 = 0;
	GUI_COLOR 	colorFill = OSD_COLOR_DARKGRAY;
	GUI_COLOR 	colorSelected = OSD_COLOR_TRANSPARENT;
	GUI_BITMAP 	barID = BMICON_SUBBAR_WHITE;

	OSDDraw_EnterMenuDrawing(&bID0, &bID1);

	if (pMenu->iSelected == uiPrevItem)
	{
		colorSelected = OSD_COLOR_SELECTED;
	}
	else
	{
		colorSelected = OSD_COLOR_TRANSPARENT;
	}

	if (uiPrevItem > 8)
	{
		barID = BMICON_SUBBAR_WHITE;
		colorFill = OSD_COLOR_TRANSPARENT;
	}

	// Draw Previous
	DrawSubItem_DriverIdSetting(bID0, uiPrevItem, pMenu->pItemsList[uiPrevItem]->uiStringId, MENU_TEXT_COLOR, barID, colorFill, colorSelected);

	if (pMenu->iSelected == uiCurrItem)
	{
		colorSelected = OSD_COLOR_SELECTED;
	}
	else
	{
		colorSelected = OSD_COLOR_TRANSPARENT;
	}

	if (uiCurrItem > 8)
	{
		barID = BMICON_SMALLBAR_YELLOW;
		colorFill = OSD_COLOR_TRANSPARENT;
	}
	else if (uiCurrItem <= 8)
	{
		colorFill = OSD_COLOR_DARKYELLOW;
	}

	// Draw current
	DrawSubItem_DriverIdSetting(bID0, uiCurrItem, pMenu->pItemsList[uiCurrItem]->uiStringId, MENU_TEXT_COLOR, barID, colorFill, colorSelected);

	OSDDraw_ExitMenuDrawing(&bID0, &bID1);
}

void MenuDrawChangeSubItem_DriverIdSettingUD(PSMENUSTRUCT pMenu, int iOffset)
{
	UINT8 bID0 = 0, bID1 = 0;

	OSDDraw_EnterMenuDrawing(&bID0, &bID1);

	DrawSubItem_DriverIdSettingUD(bID0, pMenu->iCurrentPos, iOffset, MENU_TEXT_COLOR, OSD_COLOR_DARKYELLOW);

	OSDDraw_ExitMenuDrawing(&bID0, &bID1);
}

UINT16 AHC_Validate_DriverIdSetting(char *pDriverId, UINT16 ubCheckType, AHC_BOOL bAutoRestore, int iOffset)
{
	UINT8 	i;
	UINT16 	ubTempCheckType = ubCheckType;

	if (ubTempCheckType == CHECK_DRIVER_ID_ALL)
	{
		// TBD
	}
	else
	{
		for (i = 0; i < 9; i++)
		{
			if ((ubTempCheckType & 0x0001) == 0x0001)
			{
				break;
			}
			ubTempCheckType >>= 1;
		}

		if (pDriverId[i] > 'Z')
		{
			pDriverId[i] = ' ';
		}
		else if (pDriverId[i] < '0')
		{
			if (pDriverId[i] == '!')
			{
				pDriverId[i] = '.';
			}
			else if (pDriverId[i] == '/')
			{
				if (iOffset > 0)
				{
					pDriverId[i] = '0';
				}
				else if (iOffset < 0)
				{
					pDriverId[i] = '.';
				}
			}
			else if (pDriverId[i] == '-')
			{
				pDriverId[i] = ' ';
			}
			else
			{
				pDriverId[i] = 'Z';
			}
		}
		if ((pDriverId[i] > '9') && (pDriverId[i] < 'A'))
		{
			if (iOffset > 0)
			{
				pDriverId[i] += 7;
			}
			else if (iOffset < 0)
			{
				pDriverId[i] -= 7;
			}
		}
	}

	return CHECK_DRIVER_ID_PASS;
}

AHC_BOOL AHC_RestoreDefaultDriverId(char *pDriverId0, char *pDriverId1, char *pDriverId2,
                                    char *pDriverId3, char *pDriverId4, char *pDriverId5,
                                    char *pDriverId6, char *pDriverId7, char *pDriverId8)  // TBD
{
	AHC_SetParam(PARAM_ID_USE_DRIVER_ID, 1);
	
	*pDriverId0 = DRIVER_ID_DEFAULT_D0;
	*pDriverId1 = DRIVER_ID_DEFAULT_D1;
	*pDriverId2 = DRIVER_ID_DEFAULT_D2;
	*pDriverId3 = DRIVER_ID_DEFAULT_D3;
	*pDriverId4 = DRIVER_ID_DEFAULT_D4;
	*pDriverId5 = DRIVER_ID_DEFAULT_D5;
	*pDriverId6 = DRIVER_ID_DEFAULT_D6;
	*pDriverId7 = DRIVER_ID_DEFAULT_D7;
	*pDriverId7 = DRIVER_ID_DEFAULT_D8;
	
	return AHC_TRUE;
}

#if 0
void ____from_HCarDV_MenuStateGeneralSettingsMenu_c____(){ruturn;}  // dummy
#endif

AHC_BOOL MenuItemDriverIdSettings(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
	return AHC_TRUE;
}

AHC_BOOL MenuInitDriverId(void)
{
	AHC_SetParam(PARAM_ID_USE_DRIVER_ID, 1);

	// tmpDriverId
	*(((char *)Driverid) + 9) = '\0'; // TBC
	memcpy(tmpDriverId, Driverid, 9/*sizeof(Driverid)*/);
	*(((char *)tmpDriverId) + 9) = '\0'; // TBC

	initDriverId = AHC_FALSE;

	return AHC_TRUE;
}

UINT32 SubMenuEventHandler_DriverIdSetting(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam) // TBC
{
    INT32 	iPrevPos;
#if(SUPPORT_TOUCH_PANEL)       
    POINT	TouchPoint;
	
    if( MENU_TOUCH == ulEvent || MENU_TOUCH_MOVE == ulEvent )
    {
        TouchPoint.PointX = ulParam & 0xFFFF;
        TouchPoint.PointY = (ulParam >> 16) & 0xFFFF;
    }
#endif

	if (initDriverId == AHC_TRUE)
		MenuInitDriverId();

	switch (ulEvent)
	{
		case MENU_EXIT:
			return MENU_ERR_EXIT;
			//break;

		case MENU_INIT:
			pMenu->uiStatus = MENU_STATUS_NONE;
			pMenu->bSetOne = 0;

			if (pMenu->pfMenuGetDefaultVal)
			{
				pMenu->iSelected = pMenu->pfMenuGetDefaultVal(pMenu);
			}
			else
			{
				pMenu->iSelected = 0;
			}
			pMenu->iCurrentPos = pMenu->iSelected;

		#if (SUPPORT_TOUCH_PANEL)
			KeyParser_TouchItemRegister(&MenuDriverIdSetting_TouchButton[0], ITEMNUM(MenuDriverIdSetting_TouchButton));
		#endif

			MenuDrawSubPage_DriverIdSetting(pMenu);
			break;

		case MENU_UP:
		MenuDrawChangeSubItem_DriverIdSettingUD(pMenu, 1);
		break;

		case MENU_DOWN:
		MenuDrawChangeSubItem_DriverIdSettingUD(pMenu, -1);
		break;
		
	#if (DIR_KEY_TYPE == KEY_TYPE_2KEY)
		//case MENU_LEFT:
		//	break;

		case MENU_RIGHT:
			iPrevPos = pMenu->iCurrentPos;
			pMenu->iCurrentPos = OffsetItemNumber(pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, -1, AHC_FALSE);
			MenuDrawChangeSubItem_DriverIdSetting(pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected);
			break;
	#else
		case MENU_LEFT:
			iPrevPos = pMenu->iCurrentPos;
			pMenu->iCurrentPos = OffsetItemNumber(pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, -1, AHC_FALSE);
			MenuDrawChangeSubItem_DriverIdSetting(pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected);
			break;

		case MENU_RIGHT:
			iPrevPos = pMenu->iCurrentPos;
			pMenu->iCurrentPos = OffsetItemNumber(pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, 1, AHC_FALSE);
			MenuDrawChangeSubItem_DriverIdSetting(pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected);
			break;
	#endif

		case MENU_OK:
		case MENU_SET_ONE:
			pMenu->bSetOne = 1;
			pMenu->iSelected = pMenu->iCurrentPos;
			pMenu->uiStatus |= MENU_STATUS_PRESSED;

			iPrevPos = pMenu->iCurrentPos;
			pMenu->iCurrentPos = OffsetItemNumber(pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, 1, AHC_FALSE);
			#ifdef CFG_VIRTUAL_TOUCH
			if(1)
			#else
			if ((pMenu->pItemsList[iPrevPos]->uiStringId == IDS_DS_OK) &&
				(pMenu->pItemsList[pMenu->iCurrentPos]->uiStringId == IDS_DS_OK))
			#endif
			{
				PSMENUSTRUCT	pParentMenu;

				// OK -> Exit menu
				pParentMenu = pMenu->pParentMenu;
				pMenu->pParentMenu = NULL;
				initDriverId = AHC_TRUE; // TBC

				// Validate Driver Id Setting
				if (AHC_Validate_DriverIdSetting(tmpDriverId, CHECK_DRIVER_ID_ALL, AHC_TRUE, 0) != CHECK_DRIVER_ID_PASS)
				{
					//AHC_WMSG_Draw(AHC_TRUE, WMSG_INVALID_OPERATION, 3);
				}

				// Set value to DriverID in menu_atoms
				AHC_SetParam(PARAM_ID_USE_DRIVER_ID, AHC_TRUE);

				pf_SetDriverID();

				if (pParentMenu == NULL)
				{
					return MENU_ERR_EXIT;
				}

				SetCurrentMenu(pParentMenu);
				pParentMenu->pfEventHandler(pParentMenu, MENU_INIT, 0);
			}
			else
			{
				MenuDrawChangeSubItem_DriverIdSetting(pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected);
			}
			break;

		case MENU_MENU:
			{
				PSMENUSTRUCT	pParentMenu;

				pParentMenu = pMenu->pParentMenu;
				pMenu->pParentMenu = NULL;
				pMenu->bSetOne = 0;
				initDriverId = AHC_TRUE;  // TBC

				if (pParentMenu == NULL)
				{
					return MENU_ERR_EXIT;
				}

				SetCurrentMenu(pParentMenu);
				pParentMenu->pfEventHandler(pParentMenu, MENU_INIT, 0);
			}
			break;

	#if 0//(SUPPORT_TOUCH_PANEL)
		case MENU_TOUCH:
			{
				UINT32	TouchEvent;
				UINT32	uiNextEvent = MENU_NONE;
				UINT16  i = 0;

				i = (TouchPoint.PointX-POS_SUBMENU_DRIVEID_X0)/(OSD_SUBMENU_DRIVEID_W+OSD_SUBMENU_DRIVEID_X_INTERVAL);
				TouchEvent = AhcCheckTouchButton(&TouchPoint, 0);

			    switch (TouchEvent)
				{
					case MENU_RETURN_PRESS:
						uiNextEvent = MENU_MENU;
						break;
					case MENU_UP_PRESS:
						uiNextEvent = MENU_UP;
						break;
					case MENU_DOWN_PRESS:
						uiNextEvent = MENU_DOWN;
						break;
					case MENU_LEFT_PRESS:
						uiNextEvent = MENU_LEFT;
						break;
					case MENU_RIGHT_PRESS:
						uiNextEvent = MENU_RIGHT;
						break;
					case MENU_OK_PRESS:
						ulParam = 6;
						uiNextEvent = MENU_SET_ONE;
						break;
					case MENU_SUB_DRIVEID_00_PRESS	:
					case MENU_SUB_DRIVEID_10_PRESS	:
					case MENU_SUB_DRIVEID_20_PRESS	:
					case MENU_SUB_DRIVEID_30_PRESS	:
					case MENU_SUB_DRIVEID_40_PRESS	:
					case MENU_SUB_DRIVEID_50_PRESS	:
					case MENU_SUB_DRIVEID_60_PRESS	:
					case MENU_SUB_DRIVEID_70_PRESS	:
						iPrevPos = pMenu->iCurrentPos;
						pMenu->iCurrentPos= i;
						if(iPrevPos!= pMenu->iCurrentPos)
						{
							pMenu->iSelected = pMenu->iCurrentPos;
							MenuDrawChangeSubItem_DriverIdSetting(pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected);
						}
						uiNextEvent = MENU_UP;
						break;
					case MENU_SUB_DRIVEID_01_PRESS	:
					case MENU_SUB_DRIVEID_11_PRESS	:
					case MENU_SUB_DRIVEID_21_PRESS	:
					case MENU_SUB_DRIVEID_31_PRESS	:
					case MENU_SUB_DRIVEID_41_PRESS	:
					case MENU_SUB_DRIVEID_51_PRESS	:
					case MENU_SUB_DRIVEID_61_PRESS	:
					case MENU_SUB_DRIVEID_71_PRESS	:
						iPrevPos = pMenu->iCurrentPos;
						pMenu->iCurrentPos = i;
						if(iPrevPos!= pMenu->iCurrentPos)
						{
							pMenu->iSelected = pMenu->iCurrentPos;
							MenuDrawChangeSubItem_DriverIdSetting(pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected);
						}
						uiNextEvent = MENU_DOWN;
						break;
					default:
						uiNextEvent = MENU_NONE;
						break;
				}

				#ifdef CFG_VIRTUAL_TOUCH
				return SubMenuEventHandler_DriverIdSetting(pMenu, uiNextEvent, ulParam);
				#else
				return SubMenuEventHandler_DriverNumberSetting(pMenu, uiNextEvent, ulParam);
				#endif
				
			}
			break;
			
		case MENU_TOUCH_RELEASE:
			if (pMenu->uiStatus & MENU_STATUS_ITEM_TOUCHED)
			{
				iPrevPos = pMenu->iSelected;
				pMenu->uiStatus = 0;
				MenuDrawChangeSubItem_DriverIdSetting(pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected);
			}
			break;
	#endif

#if 0
		case MENU_POWER_OFF     :
			AHC_NormalPowerOffPath();
			break; 
#endif

		default:
			break;
	}

	return MENU_ERR_OK;
}

#if 0
void ____from_HCarDV_MenuStateMovieMenu_c____(){ruturn;}  // dummy
#endif

void MenuStateDriverIdSettingsMode(UINT32 ulEvent, UINT32 ulPosition)  // TBC
{
	UINT32			ulOperation;
	UINT32			ulResult;
	PSMENUSTRUCT	pCurrMenu = NULL;

	if (BUTTON_VIRTUAL_RESET == ulEvent)
	{
		SetCurrentMenu(&sSubDriverIdSettings);
	}

	MenuModePreCheck(ulEvent);

	ulOperation = MenuButtonToMenuOp(ulEvent ,ulPosition);

	if (ulOperation == MENU_NONE)
	{
		return;
	}

	pCurrMenu = GetCurrentMenu();

	if (pCurrMenu == NULL)
	{
		return;
	}

	ulResult = pCurrMenu->pfEventHandler(pCurrMenu, ulOperation, ulPosition);

	if (ulResult == MENU_ERR_EXIT)
	{
		ResetCurrentMenu();

		StateSwitchMode(UI_VIDEO_STATE);
	}
}

#endif

