/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "ahc_macro.h"
#include "ahc_menu.h"
#include "ahc_gui.h"
#include "ahc_utility.h"
#include "ahc_general.h"
#include "ahc_media.h"
#include "ahc_parameter.h"
#include "ahc_display.h"
#include "ahc_browser.h"
#include "ahc_warningmsg.h"
#include "ahc_general_cardv.h"
#include "MenuCommon.h"
#include "MenuTouchButton.h"
#include "MenuStateMediaToolMenu.h"
#include "MenuSetting.h"
#include "MenuDrawingMediaToolFunc.h"
#include "MenuDrawingFunc.h"
#include "MenuDrawCommon.h"
#include "MenuStateMenu.h"
#include "IconPosition.h"
#include "ColorDefine.h"
#include "OSDStrings.h"
#include "IconDefine.h"
#include "statebrowserfunc.h"
#include "mediaplaybackctrl.h"

/*===========================================================================
 * Local function
 *===========================================================================*/

UINT32 	SubMenuEventHandler_FormatSDCard(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam);
UINT32 	SubMenuEventHandler_FormatINTMemory(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam);
UINT32 	SubMenuEventHandler_StorageInfo(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam);
UINT32  MenuGetDefault_MediaTool(PSMENUSTRUCT pMenu);

AHC_BOOL MenuItemMediaSelect(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemFormatSDCard(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemFormatINTMemory(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemSDCardINFO(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemINTMemoryINFO(PSMENUITEM pItem, AHC_BOOL bIsHover);

/*===========================================================================
 * Global varible : Menu
 *===========================================================================*/ 

SMENUSTRUCT sMainMenuMedia;

SMENUSTRUCT sSubMediaSelect;
SMENUSTRUCT sSubFormatSDCard;
SMENUSTRUCT sSubFormatINTMemory;
SMENUSTRUCT sSubSDCardINFO;
SMENUSTRUCT sSubINTMemoryINFO;

/*===========================================================================
 * Global variable : Item Structure
 *===========================================================================*/ 

// Media Select
#if (MENU_MEDIA_SELECT_MDEIA_EN)
SMENUITEM sItemMediaSelect       = { ITEMID_MEDIA_SELECT, NULL, IDS_DS_MEDIA_SELECT,	&sSubMediaSelect, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemMedia_SDCard      = { ITEMID_MEDIA_SD_CARD,  &BMICON_MEDIA_SD, 	 IDS_DS_MEDIA_SD_CARD,	NULL, MenuItemMediaSelect, 0, AHC_TRUE, NULL };
SMENUITEM sItemMedia_Internal    = { ITEMID_MEDIA_INTERNAL, &BMICON_INTERNALMEM_ERROR, IDS_DS_MEDIA_INTERNAL, NULL, MenuItemMediaSelect, 0, AHC_TRUE, NULL };
#endif

// Format SD-Card
#if (MENU_MEDIA_FORMAT_SD_EN)
SMENUITEM sItemFormatCard        = { ITEMID_FORMAT_SD_CARD,  &BMICON_MENU_SD_FORMAT,IDS_DS_FORMAT_SD_CARD,	&sSubFormatSDCard, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemFormatCard_Yes    = { ITEMID_FORMAT_CARD_YES, &BMICON_FORMAT_YES, 	IDS_DS_YES, NULL, MenuItemFormatSDCard, 0, AHC_TRUE, NULL };
SMENUITEM sItemFormatCard_No     = { ITEMID_FORMAT_CARD_NO,  &BMICON_FORMAT_NO,  	IDS_DS_NO,  NULL, MenuItemFormatSDCard, 0, AHC_TRUE, NULL };
#endif

//Format INT.Memory
#if (MENU_MEDIA_FORMAT_INT_MEM_EN)
SMENUITEM sItemFormatINTMem      = { ITEMID_FORMAT_INTMEM, NULL, IDS_DS_FORMAT_INTMEM,	&sSubFormatINTMemory, 0, AHC_TRUE, NULL };
SMENUITEM sItemFormatINTMem_Yes  = { ITEMID_FORMAT_INTMEM_YES, NULL, IDS_DS_YES,	NULL, MenuItemFormatINTMemory, 0, AHC_TRUE, NULL };
SMENUITEM sItemFormatINTMem_No   = { ITEMID_FORMAT_INTMEM_NO,  NULL, IDS_DS_NO,     NULL, MenuItemFormatINTMemory, 0, AHC_TRUE, NULL };
#endif

// SD-Card INFO
#if (MENU_MEDIA_SHOW_SD_INFO)
SMENUITEM sItemSDCardINFO        = { ITEMID_SD_CARD_INFO, &BMICON_MENU_SD_INFO, IDS_DS_SD_CARD_INFO, &sSubSDCardINFO, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemCardTimeLeft      = { ITEMID_CARD_TIME_LEFT,  NULL, IDS_DS_TIME_LEFT,  NULL, MenuItemSDCardINFO, 0, AHC_TRUE, NULL };
SMENUITEM sItemCardPhotoLeft     = { ITEMID_CARD_PHOTO_LEFT, NULL, IDS_DS_PHOTO_LEFT, NULL, MenuItemSDCardINFO, 0, AHC_TRUE, NULL };
#endif

// INT.Memory INFO
#if (MENU_MEDIA_SHOW_INT_MEM_INFO)
SMENUITEM sItemINTMemINFO        = { ITEMID_INTMEM_INFO, NULL, IDS_DS_INTMEM_INFO, &sSubINTMemoryINFO, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemINTTimeLeft       = { ITEMID_INT_TIME_LEFT,  NULL, IDS_DS_TIME_LEFT,  NULL, MenuItemINTMemoryINFO, 0, AHC_TRUE, NULL };
SMENUITEM sItemINTPhotoLeft      = { ITEMID_INT_PHOTO_LEFT, NULL, IDS_DS_PHOTO_LEFT, NULL, MenuItemINTMemoryINFO, 0, AHC_TRUE, NULL };
#endif

/*===========================================================================
 * Global varible : Item List
 *===========================================================================*/ 

#if (MENU_MEDIA_SELECT_MDEIA_EN)
PSMENUITEM   sMenuListMediaSelect[] =
{
    &sItemMedia_SDCard,
    &sItemMedia_Internal
};
#endif

#if (MENU_MEDIA_FORMAT_SD_EN)
PSMENUITEM   sMenuListFormatSDCard[] =
{
    &sItemFormatCard_Yes,
    &sItemFormatCard_No
};
#endif

#if (MENU_MEDIA_FORMAT_INT_MEM_EN)
PSMENUITEM   sMenuListFormatINTMemory[] =
{
    &sItemFormatINTMem_Yes,
    &sItemFormatINTMem_No
};
#endif

#if (MENU_MEDIA_SHOW_SD_INFO)
PSMENUITEM   sMenuListSDCardInfo[] =
{
    &sItemCardTimeLeft,
    &sItemCardPhotoLeft
};
#endif

#if (MENU_MEDIA_SHOW_INT_MEM_INFO)
PSMENUITEM   sMenuListINTMemoryInfo[] =
{
    &sItemINTTimeLeft,
    &sItemINTPhotoLeft
};
#endif

PSMENUITEM   sMenuListMainMedia[] =
{
#if (MENU_MEDIA_FORMAT_SD_EN)
    &sItemFormatCard,    
#endif
#if (MENU_MEDIA_SHOW_SD_INFO)    
    &sItemSDCardINFO
#endif    
};

/*===========================================================================
 * Global variable : Menu Structure
 *===========================================================================*/

SMENUSTRUCT   sMainMenuMedia =
{
    MENUID_MAIN_MENU_MEDIA,                            
    NULL,                                              
    IDS_DS_MEDIA_TOOL,                                 
    NULL,                                              
    sizeof(sMenuListMainMedia)/sizeof(PSMENUITEM),   
    sMenuListMainMedia,                                
    MainMenuEventHandler,                             
    MenuGetDefault,                                    
    0,                                                 
    0,                                                
    0,                                               
    0                                                  
};

//--------------SUB MENU-------------------

#if (MENU_MEDIA_SELECT_MDEIA_EN)
SMENUSTRUCT sSubMediaSelect =
{
    MENUID_SUB_MENU_MEDIA_SELECT,
    NULL,
    IDS_DS_MEDIA_SELECT,
    NULL,
    sizeof(sMenuListMediaSelect)/sizeof(PSMENUITEM),
    sMenuListMediaSelect,
    SubMenuEventHandler,
    MenuGetDefault_MediaTool,
    0,
    IDS_DS_MEDIA_SELECT_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_MEDIA_FORMAT_SD_EN)
SMENUSTRUCT sSubFormatSDCard =
{
    MENUID_SUB_MENU_FORMAT_SD_CARD,
    NULL,
    IDS_DS_FORMAT_SD_CARD,
    NULL,
    sizeof(sMenuListFormatSDCard)/sizeof(PSMENUITEM),
    sMenuListFormatSDCard,
    SubMenuEventHandler_FormatSDCard,//SubMenuEventHandler,
    MenuGetDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};
#endif

#if (MENU_MEDIA_FORMAT_INT_MEM_EN)
SMENUSTRUCT sSubFormatINTMemory =
{
    MENUID_SUB_MENU_FORMAT_INTMEM,
    NULL,
    IDS_DS_FORMAT_INTMEM,
    NULL,
    sizeof(sMenuListFormatINTMemory)/sizeof(PSMENUITEM),
    sMenuListFormatINTMemory,
    SubMenuEventHandler_FormatINTMemory,
    MenuGetDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};
#endif

#if (MENU_MEDIA_SHOW_SD_INFO)
SMENUSTRUCT sSubSDCardINFO =
{
    MENUID_SUB_MENU_SD_CARD_INFO,
    NULL,
    IDS_DS_CARD_INFO,
    NULL,
    sizeof(sMenuListSDCardInfo)/sizeof(PSMENUITEM),
    sMenuListSDCardInfo,
    SubMenuEventHandler_StorageInfo,//SubMenuEventHandler,
    MenuGetDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};
#endif

#if (MENU_MEDIA_SHOW_INT_MEM_INFO)
SMENUSTRUCT sSubINTMemoryINFO =
{
    MENUID_SUB_MENU_INTMEM_INFO,
    NULL,
    IDS_DS_INTMEM_INFORMATION,
    NULL,
    sizeof(sMenuListINTMemoryInfo)/sizeof(PSMENUITEM),
    sMenuListINTMemoryInfo,
    SubMenuEventHandler_StorageInfo,
    MenuGetDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};
#endif

/*===========================================================================
 * Global varible
 *===========================================================================*/

AHC_BOOL m_ubFormatSDing = AHC_FALSE;


/*===========================================================================
 * Main body
 *===========================================================================*/

#if (MENU_MEDIA_SELECT_MDEIA_EN)
AHC_BOOL MenuItemMediaSelect(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    UINT8 	Media = MEDIA_SETTING_SD_CARD_ERR;
    
    MenuSettingConfig()->uiMediaSelect= pItem->iItemId - ITEMID_MEDIA_SELECT-1; 
    
    if((AHC_GetMediaPath() == AHC_MEDIA_MMC) && (MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD) ||
       (AHC_GetMediaPath() == AHC_MEDIA_SMC) && (MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_INTERNAL))
    {
    	return AHC_TRUE;
    }
    
    if(Media != MenuSettingConfig()->uiMediaSelect)
    {
    	Media = MenuSettingConfig()->uiMediaSelect;
        AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect);

        if( AHC_CheckCurSysMode(AHC_MODE_THUMB_BROWSER) ) 
        {
            AHC_Thumb_DrawPage(AHC_TRUE); 
        }
    }
   
    return AHC_TRUE;
}
#endif

#if (MENU_MEDIA_FORMAT_SD_EN)
AHC_BOOL MenuItemFormatSDCard(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
	if(pItem->iItemId == ITEMID_FORMAT_CARD_YES) 
	{
		if(m_ubFormatSDing)
			return AHC_TRUE;
		
		m_ubFormatSDing = AHC_TRUE;	 
	
		QuickMediaOperation(MEDIA_CMD_FORMAT);
		
		m_ubFormatSDing = AHC_FALSE;
    }

    return AHC_TRUE;
}
#endif

#if (MENU_MEDIA_FORMAT_INT_MEM_EN)
AHC_BOOL MenuItemFormatINTMemory(PSMENUITEM pItem, AHC_BOOL bIsHover)
{    
    if(pItem->iItemId == ITEMID_FORMAT_INTMEM_YES) 
    {    
        AHC_FormatStorageMedia(AHC_MEDIA_SMC);
        AHC_MountStorageMedia(AHC_MEDIA_SMC);
        AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect);
      
        if( AHC_CheckCurSysMode(AHC_MODE_THUMB_BROWSER) ) 
        {
            AHC_Thumb_DrawPage(AHC_TRUE); 
        }
    }

    return AHC_TRUE;
}
#endif

#if (MENU_MEDIA_SHOW_SD_INFO)
AHC_BOOL MenuItemSDCardINFO(PSMENUITEM pItem, AHC_BOOL bIsHover )
{
    return AHC_TRUE;
}
#endif

#if (MENU_MEDIA_SHOW_INT_MEM_INFO)
AHC_BOOL MenuItemINTMemoryINFO(PSMENUITEM pItem, AHC_BOOL bIsHover )
{
    return AHC_TRUE;
}
#endif

UINT32 MenuGetDefault_MediaTool(PSMENUSTRUCT pMenu)
{
    UINT32       DefaultValue;

    switch( pMenu->iMenuId )
    {
    #if (MENU_MEDIA_SELECT_MDEIA_EN)
        case MENUID_SUB_MENU_MEDIA_SELECT:
            DefaultValue = MenuSettingConfig()->uiMediaSelect;
            break;
    #endif
    	default:
    		break;        
    }

	return DefaultValue;
}

#if (MENU_MEDIA_FORMAT_SD_EN)
UINT32 SubMenuEventHandler_FormatSDCard(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
{
    INT32  	iPrevPos;
#if(SUPPORT_TOUCH_PANEL)   
    POINT  	TouchPoint;

    if( MENU_TOUCH == ulEvent || MENU_TOUCH_MOVE == ulEvent )
    {
        TouchPoint.PointX = ulParam & 0xFFFF;
        TouchPoint.PointY = (ulParam >> 16) & 0xFFFF;
    }
#endif

	switch(ulEvent)
	{
	case MENU_EXIT:
		return MENU_ERR_EXIT;
	break;
	
	case MENU_INIT          :
        pMenu->uiStatus = MENU_STATUS_NONE;
	    pMenu->bSetOne  = 0;
	    
	    if( pMenu->pfMenuGetDefaultVal )
	    {
		    pMenu->iSelected = pMenu->pfMenuGetDefaultVal( pMenu );
	    }
	    else
	    {
			pMenu->iSelected = 0;
	    }
  		pMenu->iCurrentPos = pMenu->iSelected;

		
		#if (SUPPORT_TOUCH_PANEL)
		KeyParser_TouchItemRegister(&MenuConfirm_TouchButton[0], ITEMNUM(MenuConfirm_TouchButton));
		#endif

	    MenuDrawSubPage_ConfirmPage( pMenu );
	break;

	#if (DIR_KEY_TYPE==KEY_TYPE_2KEY)
	case MENU_UP:
	#else
	case MENU_LEFT:	
	#endif
		#ifdef SLIDE_MENU
		if(IsSlidingMenu())
			break;
		#endif

        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, -1, AHC_FALSE );

        MenuDrawChangeSubItem_ConfirmPage( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
	break;
		
	#if (DIR_KEY_TYPE==KEY_TYPE_2KEY)
	case MENU_DOWN:
	#else
	case MENU_RIGHT:
	#endif
		#ifdef SLIDE_MENU
		if(IsSlidingMenu())
			break;
		#endif
		
        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, 1, AHC_FALSE );

        MenuDrawChangeSubItem_ConfirmPage( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
	break;
				
	case MENU_OK            :
	case MENU_SET_ONE		:

		if(m_ubFormatSDing)
			break;

		#ifdef SLIDE_MENU
		if(IsSlidingMenu())
			break;
		#endif
	 
        if(ulEvent==MENU_SET_ONE)
        {
       		pMenu->iCurrentPos = ulParam;
        	pMenu->iSelected   = ulParam;
			pMenu->bSetOne   = 1;
        	pMenu->uiStatus |= MENU_STATUS_PRESSED;
        	pMenu->uiStatus |= MENU_STATUS_ITEM_TOUCHED;
		}
		else
		{	
			pMenu->bSetOne   = 1;
	        pMenu->iSelected = pMenu->iCurrentPos;
	        pMenu->uiStatus |= MENU_STATUS_PRESSED;		
		}
		
        if( CommonMenuOK( pMenu, AHC_TRUE ) == AHC_TRUE )
        {
			         
			PSMENUSTRUCT pParentMenu;
			
			pParentMenu        = pMenu->pParentMenu;
			pMenu->pParentMenu = NULL;

 			if( pParentMenu == NULL )
			{
				return MENU_ERR_EXIT;
			}
			SetCurrentMenu(pParentMenu);
			pParentMenu->pfEventHandler( pParentMenu, MENU_INIT, 0 );	        	
        	
        	
            return MENU_ERR_OK;
        }
	break;

	case MENU_MENU          :
    {
		if(m_ubFormatSDing)
			break;

        {
        	PSMENUSTRUCT pParentMenu;

        	pParentMenu        = pMenu->pParentMenu;
        	pMenu->pParentMenu = NULL;
			pMenu->bSetOne     = 0;
		
        	if( pParentMenu == NULL )
        	{
	        	return MENU_ERR_EXIT;
        	}

        	SetCurrentMenu(pParentMenu);
        	pParentMenu->pfEventHandler( pParentMenu, MENU_INIT, 0 );
        }
    }
	break;

#if 0
	case MENU_POWER_OFF     :
        AHC_PowerOff_NormalPath();
	break; 		
#endif

	default:
	break;
	}

    return MENU_ERR_OK;
}
#endif

#if (MENU_MEDIA_FORMAT_INT_MEM_EN)
UINT32 SubMenuEventHandler_FormatINTMemory(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam )
{
    INT32  	iPrevPos;

	switch(ulEvent)
	{
	case MENU_INIT          :

        pMenu->uiStatus = MENU_STATUS_NONE;
		pMenu->bSetOne  = 0;
		
	    if( pMenu->pfMenuGetDefaultVal )
	    {
		    pMenu->iSelected = pMenu->pfMenuGetDefaultVal( pMenu );
	    }
	    else
	    {
      	    pMenu->iSelected = 0 ;
	    }
        pMenu->iCurrentPos = pMenu->iSelected;

	    MenuDrawSubPage_ConfirmPage( pMenu );
		break;
		
#if (DIR_KEY_TYPE==KEY_TYPE_2KEY)
	case MENU_UP            :	
#else
	case MENU_LEFT:	
#endif		
        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, -1, AHC_FALSE );

        MenuDrawChangeSubItem_ConfirmPage( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
		break;
		
#if (DIR_KEY_TYPE==KEY_TYPE_2KEY)
	case MENU_DOWN          :	
#else
	case MENU_RIGHT:		
#endif	
        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, 1, AHC_FALSE );

        MenuDrawChangeSubItem_ConfirmPage( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
		break;
			
	case MENU_OK            :

		pMenu->bSetOne   = 1;
		pMenu->iSelected = pMenu->iCurrentPos;
        pMenu->uiStatus |= MENU_STATUS_PRESSED;

        if( CommonMenuOK( pMenu, AHC_TRUE ) == AHC_TRUE )
        {
			PSMENUSTRUCT pParentMenu;
			
			pParentMenu        = pMenu->pParentMenu;
			pMenu->pParentMenu = NULL;

 			if( pParentMenu == NULL )
			{
				return MENU_ERR_EXIT;
			}
			SetCurrentMenu(pParentMenu);
			pParentMenu->pfEventHandler( pParentMenu, MENU_INIT, 0 );	        	

            return MENU_ERR_OK;
        }
		break;

	case MENU_MENU          :
    {
        PSMENUSTRUCT pParentMenu;

        pParentMenu        = pMenu->pParentMenu;
        pMenu->pParentMenu = NULL;
		pMenu->bSetOne     = 0;
		
        if( pParentMenu == NULL )
        {
	        return MENU_ERR_EXIT;
        }

        SetCurrentMenu(pParentMenu);
        pParentMenu->pfEventHandler( pParentMenu, MENU_INIT, 0 );
    }
		break;

#if 0
	case MENU_POWER_OFF     :
        AHC_PowerOff_NormalPath();
	    break; 	
#endif

	default:
		break;
	}

    return MENU_ERR_OK;
}
#endif

#if (MENU_MEDIA_SHOW_SD_INFO)
UINT32 SubMenuEventHandler_StorageInfo(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
{
#if(SUPPORT_TOUCH_PANEL)   
    POINT  TouchPoint;

    if( MENU_TOUCH == ulEvent || MENU_TOUCH_MOVE == ulEvent )
    {
        TouchPoint.PointX = ulParam & 0xFFFF;
        TouchPoint.PointY = (ulParam >> 16) & 0xFFFF;
    }
#endif

	switch(ulEvent)
	{
	case MENU_EXIT:
		return MENU_ERR_EXIT;
	break;	
	
	case MENU_INIT          :

        pMenu->uiStatus = MENU_STATUS_NONE;

	    if( pMenu->pfMenuGetDefaultVal )
	    {
		    pMenu->iSelected = pMenu->pfMenuGetDefaultVal( pMenu );
	    }
	    else
	    {
      	    pMenu->iSelected = 0 ;
	    }
        pMenu->iCurrentPos = pMenu->iSelected;


		#if (SUPPORT_TOUCH_PANEL)
		KeyParser_TouchItemRegister(&MenuInfo_TouchButton[0], ITEMNUM(MenuInfo_TouchButton));		
		#endif
	
	    MenuDrawSubPage_StorageInfo( pMenu );
	break;

		
	case MENU_OK            :

        if( CommonMenuOK( pMenu, AHC_TRUE ) == AHC_TRUE )
        {
			PSMENUSTRUCT pParentMenu;
			
			pParentMenu        = pMenu->pParentMenu;
			pMenu->pParentMenu = NULL;

 			if( pParentMenu == NULL )
			{
				return MENU_ERR_EXIT;
			}
			SetCurrentMenu(pParentMenu);
			pParentMenu->pfEventHandler( pParentMenu, MENU_INIT, 0 );	        	
        
            return MENU_ERR_OK;
        }
	break;

	case MENU_MENU          :
    {
        PSMENUSTRUCT pParentMenu;

        pParentMenu        = pMenu->pParentMenu;
        pMenu->pParentMenu = NULL;

        if( pParentMenu == NULL )
        {
	        return MENU_ERR_EXIT;
        }

        SetCurrentMenu(pParentMenu);
        pParentMenu->pfEventHandler( pParentMenu, MENU_INIT, 0 );
    }
	break;

#if (SUPPORT_TOUCH_PANEL)
	case MENU_TOUCH         :
	{
		UINT32 	TouchEvent;
		UINT32  uiNextEvent = MENU_NONE;

		TouchEvent = AhcCheckTouchButton(&TouchPoint, 0);

		switch( TouchEvent )
		{
			case MENU_RETURN_PRESS :
				uiNextEvent = MENU_MENU;
			break;
			default:
				uiNextEvent = MENU_NONE;
			break;
		}
		return SubMenuEventHandler_StorageInfo(pMenu, uiNextEvent, ulParam);
	}
	break;
#endif

#if 0
	case MENU_POWER_OFF     :
        AHC_PowerOff_NormalPath();
	break; 	
#endif

	default:
	break;
	}

    return MENU_ERR_OK;
}
#endif
