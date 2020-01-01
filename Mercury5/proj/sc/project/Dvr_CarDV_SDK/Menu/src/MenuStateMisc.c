/*===========================================================================
 * Include file
 *===========================================================================*/

#include "ahc_macro.h"
#include "ahc_menu.h"
#include "ahc_gui.h"
#include "ahc_isp.h"
#include "ahc_video.h"
#include "ahc_audio.h"
#include "ahc_warningmsg.h"
#include "ahc_os.h"
#include "ahc_sensor.h"
#include "ahc_parameter.h"
#include "ahc_utility.h"
#include "ahc_general.h"
#include "ahc_general_cardv.h"
#include "MenuCommon.h"
#include "MenuStateMenu.h"
#include "MenuDrawingFunc.h"
#include "MenuDrawCommon.h"
#include "MenuSetting.h"
#include "MenuStateMisc.h"
#include "ShowOSDFunc.h"
#include "ledcontrol.h"
#include "IconPosition.h"
#include "IconDefine.h"
#include "ColorDefine.h"
#include "OSDStrings.h"
#include "statetvfunc.h"
#include "statehdmifunc.h"
#ifdef _OEM_MENU_
#include "Oem_Menu.h"
#endif
#include "keyparser.h"
#include "MenuCommon.h"
#include "MenuTouchButton.h"
/*===========================================================================
 * Extern varible
 *===========================================================================*/

#if (POWER_ON_MENU_SET_EN)
extern SMENUSTRUCT  sSubLanguage;
extern SMENUSTRUCT  sSubClockSettings;
extern SMENUSTRUCT  sSubMovieSoundRecord;
extern SMENUSTRUCT  sSubMoviePowerOffTime;
extern SMENUSTRUCT  sSubMovieClipTime;
extern SMENUSTRUCT  sSubMovieMode;
extern SMENUSTRUCT  sSubFormatSDCard;
extern SMENUSTRUCT  sSubExitPowerOnSetting;
#endif

#if (TOP_MENU_PAGE_EN)
extern SMENUSTRUCT  sMainMenuAll;
extern SMENUSTRUCT  sSubLanguage;

extern SMENUITEM    sItemBootUpMode;
extern SMENUITEM    sItemMovieClipTime;
extern SMENUITEM    sItemMovieMode;
extern SMENUITEM    sItemStillImageSize;
extern SMENUITEM    sItemTimeLapseTime;
extern SMENUITEM    sItemLCDRotate;
extern SMENUITEM    sItemDeleteFile;
extern SMENUITEM    sItemTVSystem;
extern SMENUITEM    sItemVolume;
extern SMENUITEM    sItemAutoPowerOff;
extern SMENUITEM    sItemClockSettings;
extern SMENUITEM    sItemFWVersionInfo;
#endif

/*===========================================================================
 * Local function
 *===========================================================================*/

AHC_BOOL MenuItemExitMenu(PSMENUITEM pItem, AHC_BOOL bIsHover);
#if (POWER_ON_MENU_SET_EN)
AHC_BOOL MenuItemExitPowerOnSetting(PSMENUITEM pItem, AHC_BOOL bIsHover);
#endif
#if (TOP_MENU_PAGE_EN)
UINT32   TopMenuEventHandler(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam);
#endif

/*===========================================================================
 * Global varible : Item Structure
 *===========================================================================*/

SMENUITEM sItemExitMenu        = { ITEMID_EXIT_SELECT,  &BMICON_MENU_EXIT, IDS_DS_EXITMENU, NULL, MenuItemExitMenu, 0, AHC_TRUE, NULL };
SMENUITEM sItemExitMenu_OK     = { ITEMID_EXIT_OK,      NULL, IDS_DS_YES,       NULL, MenuItemExitMenu, 0, AHC_TRUE, NULL };
SMENUITEM sItemExitMenu_Cancel = { ITEMID_EXIT_CANCEL,  NULL, IDS_DS_NO,        NULL, MenuItemExitMenu, 0, AHC_TRUE, NULL };

#if (POWER_ON_MENU_SET_EN)
SMENUITEM sItemExitPowerOnSetting_Yes    = { ITEMID_EXIT_SETTING_YES, NULL, IDS_DS_YES, NULL, MenuItemExitPowerOnSetting, 0, AHC_TRUE, NULL };
SMENUITEM sItemExitPowerOnSetting_No     = { ITEMID_EXIT_SETTING_NO,  NULL, IDS_DS_NO,  NULL, MenuItemExitPowerOnSetting, 0, AHC_TRUE, NULL };
#endif

#if (TOP_MENU_PAGE_EN)
SMENUITEM sItemTopMenu_Video    = { ITEMID_TOP_VIDEO,       &BMICON_MENU_MOVIE,         IDS_DS_MOVIE_MODE,          &sMainMenuVideo,    NULL, 0, AHC_TRUE, NULL };
SMENUITEM sItemTopMenu_Camera   = { ITEMID_TOP_CAMERA,      &BMICON_MENU_CAMERA,        IDS_DS_STILL_CAPTURE,       &sMainMenuStill,    NULL, 0, AHC_TRUE, NULL };
SMENUITEM sItemTopMenu_Playback = { ITEMID_TOP_PLAYBACK,    &BMICON_MENU_PLAYBACK,      IDS_DS_PLAYBACK,            &sMainMenuPlayback, NULL, 0, AHC_TRUE, NULL };
SMENUITEM sItemTopMenu_Media    = { ITEMID_TOP_MEDIA,       &BMICON_MENU_MEDIATOOL,     IDS_DS_MEDIA_TOOL,          &sMainMenuMedia,    NULL, 0, AHC_TRUE, NULL };
SMENUITEM sItemTopMenu_General  = { ITEMID_TOP_GENERAL,     &BMICON_MENU_GEN_SETTING,   IDS_DS_GENERAL_SETTINGS,    &sMainMenuGeneral,  NULL, 0, AHC_TRUE, NULL };
#if (MENU_GENERAL_LANGUAGE_EN)
SMENUITEM sItemTopMenu_Language = { ITEMID_TOP_LANGUAGE,    &BMICON_MENU_LANG,          IDS_DS_LANGUAGE,            &sMainLanguage,     NULL, 0, AHC_TRUE, NULL };
#endif
SMENUITEM sItemTopMenu_All      = { ITEMID_TOP_ALLSETTING,  NULL,                       IDS_DS_GENERAL_SETTINGS,    &sMainMenuAll,      NULL, 0, AHC_TRUE, NULL };
#endif
/*===========================================================================
 * Global varible : Item List
 *===========================================================================*/

PSMENUITEM sMenuListExitMenu[]=
{
    &sItemExitMenu_OK,
    &sItemExitMenu_Cancel,
};

#if (POWER_ON_MENU_SET_EN)
PSMENUITEM   sMenuListExitPowerOnSetting[] =
{
    &sItemExitPowerOnSetting_Yes,
    &sItemExitPowerOnSetting_No
};

PSMENUSTRUCT sMenuListPowerOnSetting[] =
{
    &sSubLanguage,
    &sSubClockSettings,
#if (MENU_GENERAL_DRIVER_ID_SETTING_EN)
    &sSubDriverIdSettings,
#endif
    &sSubExitPowerOnSetting,
    &sSubMovieSoundRecord,
    &sSubMoviePowerOffTime,
    &sSubMovieClipTime,
    &sSubMovieMode,
    &sSubFormatSDCard
};
#endif

#if (TOP_MENU_PAGE_EN)

PSMENUITEM   sMenuListMainAll[] =
{
#if (MENU_GENERAL_BOOT_UP_MODE_EN)
    &sItemBootUpMode,
#endif
#if (MENU_MOVIE_CLIP_TIME_EN)
    &sItemMovieClipTime,
#endif
#if (MENU_MOVIE_NIGHT_MODE_EN)
    &sItemMovieNightMode,
#endif
#if (MENU_MOVIE_SIZE_EN)
    &sItemMovieMode,
#endif
#if (MENU_STILL_SIZE_EN)
    &sItemStillImageSize,
#endif
#if (MENU_STILL_TIMELAPSE_TIME_EN)
    &sItemTimeLapseTime,
#endif
#if (MENU_GENERAL_LCD_ROTATE_EN)
    &sItemLCDRotate,
#endif
#if (MENU_EDIT_DELETE_EN)
    &sItemDeleteFile,
#endif
#if (MENU_GENERAL_TV_SYSTEM_EN)
    &sItemTVSystem,
#endif
#if (MENU_PLAYBACK_VOLUME_EN)
    &sItemVolume,
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_EN)
    &sItemAutoPowerOff,
#endif
#if (MENU_GENERAL_CLOCK_SETTING_EN)
    &sItemClockSettings,
#endif
#if (MENU_GENERAL_FW_VERSION_EN)
    &sItemFWVersionInfo,
#endif
#if (MENU_GENERAL_DRIVER_ID_SETTING_EN)
    &sItemDriverIdSettings,
#endif
    &sItemExitMenu
};

#ifndef _OEM_TOUCH_
PSMENUITEM   sTopMenuList[] =
{
    &sItemTopMenu_Video,
    &sItemTopMenu_Camera,
    &sItemTopMenu_Playback,
    &sItemTopMenu_Media,
    &sItemTopMenu_General
};
UINT32 m_ulTopMenuPageItem = sizeof(sTopMenuList)/sizeof(PSMENUITEM);
#endif  // _OEM_TOUCH_
#endif

/*===========================================================================
 * Global varible : Menu Structure
 *===========================================================================*/

SMENUSTRUCT sMainMenuExit =
{
    MENUID_MAIN_MENU_EXIT,
    NULL,
    IDS_DS_EXITMENU,
    NULL,
    sizeof(sMenuListExitMenu)/sizeof(PSMENUITEM),
    sMenuListExitMenu,
    MainMenuEventHandler,
    MenuGetDefault,
    0,
    0,
    0,
    0
};

#if (POWER_ON_MENU_SET_EN)
SMENUSTRUCT sSubExitPowerOnSetting =
{
    MENUID_MAIN_MENU_EXIT,
    NULL,
    IDS_DS_EXITMENU,
    NULL,
    sizeof(sMenuListExitPowerOnSetting)/sizeof(PSMENUITEM),
    sMenuListExitPowerOnSetting,
    SubMenuEventHandler_ExitPowerOnSet,
    NULL,
    0,
    0,
    0,
    0
};

SMENUSTRUCT sPowerOnMenu =
{
    MENUID_POWER_ON_SET,
    NULL,
    IDS_DS_NONE,
    NULL,
    sizeof(sMenuListPowerOnSetting)/sizeof(PSMENUSTRUCT),
    NULL,
    SubMenuEventHandler,
    NULL,
    0,
    0,
    0,
    0
};
#endif

#if (TOP_MENU_PAGE_EN)

SMENUSTRUCT   sMainMenuAll =
{
    MENUID_MAIN_MENU_VIDEO,
    NULL,
    IDS_DS_MOVIE_MODE,
    NULL,
    sizeof(sMenuListMainAll)/sizeof(PSMENUITEM),
    sMenuListMainAll,
    MainMenuEventHandler,
    MenuGetDefault,
    0,
    0,
    0,
    0
};
#ifndef _OEM_TOUCH_
SMENUSTRUCT   sTopMenu =
{
    MENUID_TOP_MENU,
    NULL,
    -1,
    NULL,
    sizeof(sTopMenuList)/sizeof(PSMENUITEM),
    sTopMenuList,
    TopMenuEventHandler,
    MenuGetDefault,
    0,
    0,
    0,
    0
};
#endif
#endif

/*===========================================================================
 * Global varible
 *===========================================================================*/

#if (POWER_ON_MENU_SET_EN)
static UINT32 uiPowerOnState = 0;
#endif

/*===========================================================================
 * Main body
 *===========================================================================*/

#if 0
void ________ExitMenu_Function________(){ruturn;} //dummy
#endif

AHC_BOOL MenuItemExitMenu(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    UINT8 State = uiGetLastState();

    printc("Change to State=%d\r\n",State);


    if(pItem->uiStringId==IDS_DS_YES && State!=UI_STATE_UNSUPPORTED)
    {
        ResetCurrentMenu();
        Menu_ImportSetting();
        StateSwitchMode(State);
    }
    else if(pItem->uiStringId==IDS_DS_NO)
    {
        extern SMENUSTRUCT   sMainMenuVideo;
        PSMENUSTRUCT pNewMenu = &sMainMenuVideo;

        SetCurrentMenu( pNewMenu );
        pNewMenu->pfEventHandler ( &sMainMenuVideo, MENU_INIT, 0 );
    }
    else
    {
        ResetCurrentMenu();
        Menu_ImportSetting();
        StateSwitchMode(State);
    }
    return AHC_TRUE;
}

#if 0
void ________PowerOn_Function________(){ruturn;} //dummy
#endif

#if (POWER_ON_MENU_SET_EN)

void MenuStatePowerOnSettingMode(UINT32 ulEvent, UINT32 ulPosition)
{
    UINT32       ulOperation;
    UINT32       ulResult;
    PSMENUSTRUCT pCurrMenu = NULL;

    if( BUTTON_VIRTUAL_RESET == ulEvent )
    {
        if(uiPowerOnState < sPowerOnMenu.iNumOfItems)
            SetCurrentMenu(sMenuListPowerOnSetting[uiPowerOnState]);
    }

    MenuModePreCheck(ulEvent);

    ulOperation = MenuButtonToMenuOp(ulEvent,ulPosition);

    if(ulOperation == MENU_NONE)
        return;

    pCurrMenu = GetCurrentMenu();

    if( pCurrMenu == NULL )
        return;

    ulResult = pCurrMenu->pfEventHandler(pCurrMenu, ulOperation, ulPosition);

    if( ulResult == MENU_ERR_EXIT )
    {
        if(ulOperation==MENU_MENU)
        {
            ResetCurrentMenu();
            Menu_ImportSetting();
            AHC_SetRecordByChargerIn(15);
            StateSwitchMode(UI_VIDEO_STATE);
        }
        else if(uiPowerOnState < sPowerOnMenu.iNumOfItems)
        {
            uiPowerOnState++;

            if(uiPowerOnState < sPowerOnMenu.iNumOfItems)
            {
                StateSwitchMode(UI_POWERON_SET);
            }
            else
            {
                ResetCurrentMenu();
                Menu_ImportSetting();
                AHC_SetRecordByChargerIn(15);
                StateSwitchMode(UI_VIDEO_STATE);
            }
        }
        else
        {
            ResetCurrentMenu();
            Menu_ImportSetting();
            AHC_SetRecordByChargerIn(15);
            StateSwitchMode(UI_VIDEO_STATE);
        }
    }
}

AHC_BOOL MenuItemExitPowerOnSetting(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    if(pItem->uiStringId==IDS_DS_YES)
    {
        uiPowerOnState = sPowerOnMenu.iNumOfItems;
    }

    return AHC_TRUE;
}

UINT32 SubMenuEventHandler_ExitPowerOnSet(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
{
    INT32 iPrevPos;

    switch(ulEvent)
    {
    case MENU_INIT          :
        pMenu->uiStatus = MENU_STATUS_NONE;
        pMenu->bSetOne  = 0;
        pMenu->iCurrentPos = pMenu->iSelected;

        MenuDrawExitMainPage( pMenu );
    break;

#if (DIR_KEY_TYPE==KEY_TYPE_2KEY)
    case MENU_UP            :
#else
    case MENU_LEFT          :
#endif
        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, -1, AHC_TRUE );
        MenuDrawChangeExitItem( pMenu, pMenu->iCurrentPos, iPrevPos);
    break;

#if (DIR_KEY_TYPE==KEY_TYPE_2KEY)
    case MENU_DOWN          :
#else
    case MENU_RIGHT         :
#endif
        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, 1, AHC_TRUE);
        MenuDrawChangeExitItem( pMenu, pMenu->iCurrentPos, iPrevPos);
    break;

    case MENU_OK            :

        pMenu->bSetOne   = 1;
        pMenu->iSelected = pMenu->iCurrentPos;
        pMenu->uiStatus |= MENU_STATUS_PRESSED;

        if( CommonMenuOK( pMenu, AHC_TRUE ) == AHC_TRUE )
        {
            return MENU_ERR_EXIT;
        }
    break;

    case MENU_MENU          :
    {
        PSMENUSTRUCT pParentMenu;

        pMenu->bSetOne     = 0;
        pParentMenu        = pMenu->pParentMenu;
        pMenu->pParentMenu = NULL;

        if( pParentMenu == NULL )
        {
            return MENU_ERR_EXIT;
        }

        SetCurrentMenu(pParentMenu);
        pParentMenu->pfEventHandler(pParentMenu, MENU_INIT, 0);
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

UINT32 KeyParser_MenuStatePowerOnSetting(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{

    return 0;
}

AHC_BOOL MenuStatePowerOnSettingModeInit(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    StateLCDCheckStatus(UI_POWERON_SET);

    MenuStatePowerOnSettingMode(BUTTON_VIRTUAL_RESET, 0);
    LedCtrl_LcdBackLight(AHC_TRUE);

    return ahcRet;
}

AHC_BOOL MenuStatePowerOnSettingModeShutDown(void* pData)
{
    return AHC_TRUE;
}

#endif

#if 0
void ________TopMenu_Function________(){ruturn;} //dummy
#endif

#if (TOP_MENU_PAGE_EN)
UINT32 TopMenuEventHandler(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
{
    INT32 iPrevPos;

    switch(ulEvent)
    {
    case MENU_INIT          :
        pMenu->uiStatus = MENU_STATUS_NONE;
        pMenu->bSetOne  = 0;
        pMenu->iCurrentPos = pMenu->iSelected = 0;

        MenuDrawTopMenuPage(pMenu);
    break;

#if (DIR_KEY_TYPE==KEY_TYPE_4KEY)
    case MENU_LEFT            :
#else
    case MENU_UP              :
#endif
        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, -1, AHC_TRUE );


        MenuDrawChangeTopMenuItem( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
    break;

#if (DIR_KEY_TYPE==KEY_TYPE_4KEY)
    case MENU_RIGHT          :
#else
    case MENU_DOWN           :
#endif
        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, 1, AHC_TRUE);


        MenuDrawChangeTopMenuItem( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
    break;

    case MENU_OK            :

        pMenu->bSetOne   = 1;
        pMenu->iSelected = pMenu->iCurrentPos;
        pMenu->uiStatus |= MENU_STATUS_PRESSED;

        if( CommonMenuOK( pMenu, AHC_TRUE ) == AHC_TRUE )
        {
            return MENU_ERR_OK;
        }
    break;

    case MENU_MENU          :
    {
        PSMENUSTRUCT pParentMenu;

        pMenu->bSetOne     = 0;
        pParentMenu        = pMenu->pParentMenu;
        pMenu->pParentMenu = NULL;

        if( pParentMenu == NULL )
        {
            return MENU_ERR_EXIT;
        }

        SetCurrentMenu(pParentMenu);
        pParentMenu->pfEventHandler(pParentMenu, MENU_INIT, 0);
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
