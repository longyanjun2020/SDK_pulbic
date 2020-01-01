/*===========================================================================
 * Include file
 *===========================================================================*/

#include "ahc_utility.h"
#include "ahc_macro.h"
#include "ahc_menu.h"
#include "ahc_message.h"
#include "ahc_gui.h"
#include "ahc_general.h"
#include "ahc_parameter.h"
#include "ahc_display.h"
#include "ahc_browser.h"
#include "ahc_warningmsg.h"
#include "ahc_general_cardv.h"
#include "MenuCommon.h"
#include "MenuTouchButton.h"
#include "MenuStateMenu.h"
#include "MenuDrawingFunc.h"
#include "MenuDrawCommon.h"
#include "MenuStateMenu.h"
#include "MenuSetting.h"
#include "IconPosition.h"
#include "ColorDefine.h"
#include "OSDStrings.h"
#include "IconDefine.h"
#include "statebrowserfunc.h"
#ifdef _OEM_MENU_
#include "Oem_Menu.h"
#endif
#include "statetvfunc.h"
/*===========================================================================
 * Global variable
 *===========================================================================*/

PSMENUSTRUCT MenuPageList[] =
{
#if (MENU_MOVIE_PAGE_EN)
    &sMainMenuVideo,
#endif
#if (MENU_STILL_PAGE_EN)
    &sMainMenuStill,
#endif
#if (MENU_PLAYBACK_PAGE_EN)
    &sMainMenuPlayback,
#endif
#if (MENU_MEDIA_PAGE_EN)
    &sMainMenuMedia,
#endif
#if (MENU_GENERAL_PAGE_EN)
    &sMainMenuGeneral,
#endif
#if (MENU_WIFI_PAGE_EN)
    &sMainMenuWifi,
#endif
#if (EXIT_MENU_PAGE_EN)
    &sMainMenuExit,
#endif
};

AHC_BOOL    m_ubAtMenuTab = AHC_FALSE;

/*===========================================================================
 * Extern variable
 *===========================================================================*/
extern AHC_BOOL     Delete_File_Confirm;
extern AHC_BOOL     Protect_File_Confirm;
extern AHC_BOOL     UnProtect_File_Confirm;
extern AHC_BOOL     Deleting_InBrowser;
extern AHC_BOOL     Protecting_InBrowser;
extern AHC_BOOL     bShowHdmiWMSG;
extern AHC_BOOL     bShowTvWMSG;
//extern AHC_BOOL   bForceSwitchBrowser;

#if (VIRTUAL_KEY_BOARD)
extern UINT32   SubMenuEventHandler_Keyboard(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam );
#endif

/*===========================================================================
 * Main body
 *===========================================================================*/

#if 0
void ________Touch_Function_______(){ruturn;} //dummy
#endif

#if 0
void ________MainSubMenu_Function_______(){ruturn;} //dummy
#endif

#define MENU_PAGE_NUM   sizeof(MenuPageList)/sizeof(PSMENUSTRUCT)

PSMENUSTRUCT GetPrevCatagoryMenu(PSMENUSTRUCT pMenu)
{
    int i, Prev;

    for(i=0; i<MENU_PAGE_NUM; i++)
    {
        if(pMenu->iMenuId==MenuPageList[i]->iMenuId)
        {
            Prev = (i==0)?(MENU_PAGE_NUM-1):(i-1);
            return (MenuPageList[Prev]);
        }
    }

    return &sMainMenuVideo;
}

PSMENUSTRUCT GetNextCatagoryMenu(PSMENUSTRUCT pMenu)
{
    int i, Next;

    for(i=0; i<MENU_PAGE_NUM; i++)
    {
        if(pMenu->iMenuId==MenuPageList[i]->iMenuId)
        {
            Next = ((i+1)==MENU_PAGE_NUM)?(0):(i+1);
            return (MenuPageList[Next]);
        }
    }

    return &sMainMenuVideo;
}

int GetCatagoryMenuID(PSMENUSTRUCT pMenu)
{
    if     ( pMenu == &sMainMenuManual   ) { return 0;  }
    else if( pMenu == &sMainMenuVideo    ) { return 1;  }
    else if( pMenu == &sMainMenuStill    ) { return 2;  }
    else if( pMenu == &sMainMenuPlayback ) { return 3;  }
    else if( pMenu == &sMainMenuEdit     ) { return 4;  }
    else if( pMenu == &sMainMenuMedia    ) { return 5;  }
    else if( pMenu == &sMainMenuGeneral  ) { return 6;  }
    else if( pMenu == &sMainMenuExit     ) { return 7;  }
#if (MENU_WIFI_PAGE_EN)
    else if( pMenu == &sMainMenuWifi     ) { return 8;  }
#endif
    else                                   { return 0;  }
}

AHC_BOOL CommonMenuOK(PSMENUSTRUCT pMenu, AHC_BOOL bHover)
{
    INT32           i;
    PSMENUITEM      pCurItem;
    PSMENUSTRUCT    pSubMenu;

    if( pMenu == NULL )
    {
        return AHC_FALSE;
    }

    if( bHover == AHC_FALSE )
        i = pMenu->iSelected;
    else
        i = pMenu->iCurrentPos;

    pCurItem = pMenu->pItemsList[i];
    pSubMenu = pCurItem->pSubMenu;

    if( pSubMenu != NULL )
    {
        pSubMenu->pParentMenu = pMenu;
        SetCurrentMenu(pSubMenu);

        pSubMenu->pfEventHandler( pSubMenu, MENU_INIT, 0 );
        Deleting_InBrowser = 0;
        Protecting_InBrowser = 0;
        Delete_File_Confirm = 0;

        return AHC_FALSE;
    }
    else if( pCurItem->pfItemSelect != NULL )
    {
        pCurItem->pfItemSelect( pCurItem, bHover );

        return AHC_TRUE;
    }
    else
    {
        return AHC_FALSE;
    }
}

UINT32 MenuGetDefault(PSMENUSTRUCT pMenu)
{
    return 0;
}

AHC_BOOL MenuModePreCheck(UINT32 ulEvent)
{
#if (TVOUT_PREVIEW_EN==0 && HDMI_PREVIEW_EN==0)

    if(BUTTON_HDMI_DETECTED == ulEvent)
    {
        if(AHC_IsHdmiConnect() && bShowHdmiWMSG)
        {
            bShowHdmiWMSG = AHC_FALSE;
            AHC_WMSG_Draw(AHC_TRUE, WMSG_HDMI_TV, 3);
        }
    }

    if( BUTTON_TV_DETECTED == ulEvent)
    {
        if(AHC_IsTVConnectEx() && bShowTvWMSG)
        {
            bShowTvWMSG = AHC_FALSE;
            AHC_WMSG_Draw(AHC_TRUE, WMSG_HDMI_TV, 3);
        }
    }

    if(BUTTON_HDMI_REMOVED == ulEvent)
    {
        bShowHdmiWMSG = AHC_TRUE;
    }

    if(BUTTON_TV_REMOVED == ulEvent)
    {
        bShowTvWMSG = AHC_TRUE;
    }
#endif

    if(BUTTON_CLEAR_WMSG == ulEvent)
    {
        AHC_WMSG_Draw(AHC_FALSE, WMSG_NONE, 0);
    }

    return AHC_TRUE;
}

UINT32 MenuEditConfirmEventHandler(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
{
    INT32   iPrevPos;

#if(SUPPORT_TOUCH_PANEL)
    POINT   TouchPoint;

    if( MENU_TOUCH == ulEvent || MENU_TOUCH_MOVE == ulEvent ){
        TouchPoint.PointX = ulParam & 0xFFFF;
        TouchPoint.PointY = (ulParam >> 16) & 0xFFFF;
    }
#endif

    switch(ulEvent)
    {
        case MENU_EXIT:
            return MENU_ERR_EXIT;
            break;

        case MENU_INIT:
            pMenu->uiStatus = MENU_STATUS_NONE;
            pMenu->bSetOne  = 0;
            pMenu->iCurrentPos = pMenu->iSelected;

#if (SUPPORT_TOUCH_PANEL)
            KeyParser_TouchItemRegister(&MainMenu_TouchButton[0], ITEMNUM(MainMenu_TouchButton));
#endif

#if (EXIT_MENU_PAGE_EN)
            if(pMenu == (&sMainMenuExit))
                MenuDrawExitMainPage( pMenu );
            else
#endif
                MenuDrawMainPage( pMenu );
            break;

        case MENU_UP            :
            iPrevPos = pMenu->iCurrentPos;
            pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, -1, AHC_TRUE );

#if (EXIT_MENU_PAGE_EN)
            if(pMenu == (&sMainMenuExit))
                MenuDrawChangeExitItem( pMenu, pMenu->iCurrentPos, iPrevPos);
            else
#endif
                MenuDrawChangeItem( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
            break;

        case MENU_DOWN          :
            iPrevPos = pMenu->iCurrentPos;
            pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, 1, AHC_TRUE);

#if (EXIT_MENU_PAGE_EN)
            if(pMenu == (&sMainMenuExit))
                MenuDrawChangeExitItem( pMenu, pMenu->iCurrentPos, iPrevPos);
            else
#endif
                MenuDrawChangeItem( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
            break;

        case MENU_LEFT          :
            {
#ifdef CFG_MENU_TOP_PAGE_SD //may be defined in config_xxx.h
                break;
#else
                PSMENUSTRUCT pNewMenu;

                pNewMenu = GetPrevCatagoryMenu( pMenu );
                SetCurrentMenu( pNewMenu );
                pNewMenu->pfEventHandler ( pNewMenu, MENU_INIT, 0 );
#endif
            }
            break;

        case MENU_RIGHT         :
            {
#ifdef CFG_MENU_TOP_PAGE_SD //may be defined in config_xxx.h
                    break;
#else
                PSMENUSTRUCT pNewMenu;

                pNewMenu = GetNextCatagoryMenu( pMenu );


                SetCurrentMenu( pNewMenu );
                pNewMenu->pfEventHandler ( pNewMenu, MENU_INIT, 0 );
#endif
            }
            break;

        case MENU_OK            :
        case MENU_SET_ONE       :

            if(ulEvent==MENU_SET_ONE){
                pMenu->iCurrentPos = ulParam;
                pMenu->iSelected   = ulParam;
                pMenu->bSetOne   = 1;
                pMenu->uiStatus |= MENU_STATUS_PRESSED;
                pMenu->uiStatus |= MENU_STATUS_ITEM_TOUCHED;
            }
            else{
                pMenu->bSetOne   = 1;
                pMenu->iSelected = pMenu->iCurrentPos;
                pMenu->uiStatus |= MENU_STATUS_PRESSED;
            }

            if( CommonMenuOK( pMenu, AHC_TRUE ) == AHC_TRUE ){

                #if (TOP_MENU_PAGE_EN)
                PSMENUSTRUCT pCurrMenu = NULL;

                SetCurrentMenu(&sTopMenu);
                pCurrMenu = GetCurrentMenu();
                if( pCurrMenu == NULL ){
                    return MENU_ERR_EXIT;
                }

                pCurrMenu->pfEventHandler(pCurrMenu, MENU_INIT, 0);
                #endif

                return MENU_ERR_EXIT;
            }
            break;

        case MENU_MENU          :
            {
                PSMENUSTRUCT pParentMenu;

                pMenu->bSetOne     = 0;
                pParentMenu        = pMenu->pParentMenu;
                pMenu->pParentMenu = NULL;

                BrowserFunc_ThumbnailEditFilelComplete();
                if( pParentMenu == NULL ){
                    return MENU_ERR_EXIT;
                }

                SetCurrentMenu(pParentMenu);
                pParentMenu->pfEventHandler(pParentMenu, MENU_INIT, 0);
            }
            break;

        default:
            return MENU_ERR_OK;//MENU_ERR_NOT_MENU_EVENT;
            break;
    }

    return MENU_ERR_OK;
}

UINT32 MainMenuEventHandler(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
{
    INT32   iPrevPos;

#if(SUPPORT_TOUCH_PANEL)
    POINT   TouchPoint;

    if( MENU_TOUCH == ulEvent || MENU_TOUCH_MOVE == ulEvent ){
        TouchPoint.PointX = ulParam & 0xFFFF;
        TouchPoint.PointY = (ulParam >> 16) & 0xFFFF;
    }
#endif

    switch(ulEvent)
    {
        case MENU_EXIT:
            return MENU_ERR_EXIT;
            break;
        case EVENT_USB_DETECT:
            return MENU_EXIT_DO_PARENT_EVENT;
            break;

        case MENU_INIT:
            pMenu->uiStatus = MENU_STATUS_NONE;
            pMenu->bSetOne  = 0;
            pMenu->iCurrentPos = pMenu->iSelected;

#if (SUPPORT_TOUCH_PANEL)
            KeyParser_TouchItemRegister(&MainMenu_TouchButton[0], ITEMNUM(MainMenu_TouchButton));
#endif

#if (EXIT_MENU_PAGE_EN)
            if(pMenu == (&sMainMenuExit))
                MenuDrawExitMainPage( pMenu );
            else
#endif
                MenuDrawMainPage( pMenu );
            break;

        case MENU_UP            :
            iPrevPos = pMenu->iCurrentPos;
            pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, -1, AHC_TRUE );

#if (EXIT_MENU_PAGE_EN)
            if(pMenu == (&sMainMenuExit))
                MenuDrawChangeExitItem( pMenu, pMenu->iCurrentPos, iPrevPos);
            else
#endif
                MenuDrawChangeItem( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
            break;

        case MENU_DOWN          :
            iPrevPos = pMenu->iCurrentPos;
            pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, 1, AHC_TRUE);

#if (EXIT_MENU_PAGE_EN)
            if(pMenu == (&sMainMenuExit))
                MenuDrawChangeExitItem( pMenu, pMenu->iCurrentPos, iPrevPos);
            else
#endif
                MenuDrawChangeItem( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
            break;

        case MENU_LEFT          :
            {
#ifdef CFG_MENU_TOP_PAGE_SD //may be defined in config_xxx.h
                break;
#else
                PSMENUSTRUCT pNewMenu;

                pNewMenu = GetPrevCatagoryMenu( pMenu );
                SetCurrentMenu( pNewMenu );
                pNewMenu->pfEventHandler ( pNewMenu, MENU_INIT, 0 );
#endif
            }
            break;

        case MENU_RIGHT         :
            {
#ifdef CFG_MENU_TOP_PAGE_SD //may be defined in config_xxx.h
                break;
#else
                PSMENUSTRUCT pNewMenu;

                pNewMenu = GetNextCatagoryMenu( pMenu );


                SetCurrentMenu( pNewMenu );
                pNewMenu->pfEventHandler ( pNewMenu, MENU_INIT, 0 );
#endif
            }
            break;

        case MENU_OK            :
        case MENU_SET_ONE       :

            if(ulEvent==MENU_SET_ONE){
                pMenu->iCurrentPos = ulParam;
                pMenu->iSelected   = ulParam;
                pMenu->bSetOne   = 1;
                pMenu->uiStatus |= MENU_STATUS_PRESSED;
                pMenu->uiStatus |= MENU_STATUS_ITEM_TOUCHED;
            }
            else{
                pMenu->bSetOne   = 1;
                pMenu->iSelected = pMenu->iCurrentPos;
                pMenu->uiStatus |= MENU_STATUS_PRESSED;
            }

            if( CommonMenuOK( pMenu, AHC_TRUE ) == AHC_TRUE ){
#if (TOP_MENU_PAGE_EN)
                PSMENUSTRUCT pCurrMenu = NULL;

                SetCurrentMenu(&sTopMenu);
                pCurrMenu = GetCurrentMenu();
                if( pCurrMenu == NULL ){
                    return MENU_ERR_EXIT;
                }

                pCurrMenu->pfEventHandler(pCurrMenu, MENU_INIT, 0);
#endif
                return MENU_ERR_OK;
            }
            break;

        case MENU_MENU          :

            if(Deleting_InBrowser || Protecting_InBrowser){
                printc("Delete/Protect/UnProtect Change to Browser Mode2\r\n");
                // To check is there file in card, it no any file
                // to reset Delete/(Un)Protect file in broswer flags.
                // Otherwise those flag will make key/device events to
                // be NULL!! UI will be stuck
                BrowserFunc_ThumbnailEditCheckFileObj();
                return MENU_ERR_FORCE_BROWSER_EXIT;
            }
            else
            {
                PSMENUSTRUCT pParentMenu;

                pMenu->bSetOne     = 0;
                pParentMenu        = pMenu->pParentMenu;
                pMenu->pParentMenu = NULL;

                if( pParentMenu == NULL ){
                    return MENU_ERR_EXIT;
                }

                SetCurrentMenu(pParentMenu);
                pParentMenu->pfEventHandler(pParentMenu, MENU_INIT, 0);
            }
            break;

        default:
            return MENU_ERR_OK;//MENU_ERR_NOT_MENU_EVENT;
            break;
    }

    return MENU_ERR_OK;
}

#if (SUPPORT_TOUCH_PANEL)
UINT32 MainMenuItem_Touch(UINT16 pt_x,UINT16 pt_y)
{
    UINT32  uiNextEvent = MENU_NONE;
    UINT32  TouchEvent;
    UINT16  i = 0;
    PSMENUSTRUCT pMenu;
    int iPrevPos;

    pMenu=GetCurrentMenu();

    i = (pt_y - OSD_MENU_ITEM_Y )/( OSD_MENU_ITEM_H + OSD_MENU_ITEM_INTERVAL );
    i = (pMenu->iCurrentPos/MAIN_MENU_PAGE_ITEM)*MAIN_MENU_PAGE_ITEM + i;
    printc("MainMenuItem_Touch %d,ofItem %d\r\n",i,pMenu->iNumOfItems);
    if(i < pMenu->iNumOfItems)
    {
        if(i ==  pMenu->iCurrentPos)
            MainMenuEventHandler(pMenu,MENU_SET_ONE,i);
        else
        {
            iPrevPos = pMenu->iCurrentPos;
            pMenu->iCurrentPos = i;
            MenuDrawChangeItem( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
        }
    }
    return MENU_ERR_OK;
}
#endif

//Common SubMenuEventHandler.
UINT32 SubMenuEventHandler(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
{
    INT32   iPrevPos;
#if(SUPPORT_TOUCH_PANEL)
    POINT   TouchPoint;
#endif

#if(SUPPORT_TOUCH_PANEL)
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

            if( pMenu->pfMenuGetDefaultVal ){
                pMenu->iSelected = pMenu->pfMenuGetDefaultVal(pMenu);
            }
            else{
                pMenu->iSelected = 0 ;
            }
            pMenu->iCurrentPos = pMenu->iSelected;
            pMenu->bSetOne     = 0;

        #if (SUPPORT_TOUCH_PANEL)
            if( pMenu->iNumOfItems <= 2 )
                KeyParser_TouchItemRegister(&SubMenu2_TouchButton[0], ITEMNUM(SubMenu2_TouchButton));
            else if( pMenu->iNumOfItems <= 4 )
                KeyParser_TouchItemRegister(&SubMenu4_TouchButton[0], ITEMNUM(SubMenu4_TouchButton));
            else
                KeyParser_TouchItemRegister(&SubMenu6_TouchButton[0], ITEMNUM(SubMenu6_TouchButton));
        #endif

            MenuDrawSubPage(pMenu);
            break;

        case MENU_UP            :

        #ifdef SLIDE_MENU
            if(IsSlidingMenu())
                break;
        #endif

            iPrevPos = pMenu->iCurrentPos;

        #if (DIR_KEY_TYPE==KEY_TYPE_2KEY)
            pMenu->iCurrentPos = OffsetItemNumber(pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, -1, AHC_TRUE);
        #elif defined(FONT_LARGE)
            pMenu->iCurrentPos = OffsetItemNumber(pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, -1, AHC_FALSE);
        #else
            pMenu->iCurrentPos = OffsetItemNumber(pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, -2, AHC_FALSE);
        #endif
            MenuDrawChangeSubItem(pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected);
            break;

        case MENU_DOWN          :

        #ifdef SLIDE_MENU
            if(IsSlidingMenu())
                break;
        #endif

            iPrevPos = pMenu->iCurrentPos;

        #if (DIR_KEY_TYPE==KEY_TYPE_2KEY)
            pMenu->iCurrentPos = OffsetItemNumber(pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, 1, AHC_TRUE);
        #elif defined(FONT_LARGE)
            pMenu->iCurrentPos = OffsetItemNumber(pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, 1, AHC_FALSE);
        #else
            pMenu->iCurrentPos = OffsetItemNumber(pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, 2, AHC_FALSE);
        #endif
            MenuDrawChangeSubItem(pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected);
            break;

    #if (DIR_KEY_TYPE==KEY_TYPE_4KEY)
        case MENU_LEFT          :

        #ifdef SLIDE_MENU
            if(IsSlidingMenu())
                break;
        #endif

            iPrevPos = pMenu->iCurrentPos;
            pMenu->iCurrentPos = OffsetItemNumber(pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, -1, AHC_FALSE);

            MenuDrawChangeSubItem(pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected);
            break;

        case MENU_RIGHT          :

        #ifdef SLIDE_MENU
            if(IsSlidingMenu())
                break;
        #endif

            iPrevPos = pMenu->iCurrentPos;
            pMenu->iCurrentPos = OffsetItemNumber(pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, 1, AHC_FALSE);

            MenuDrawChangeSubItem(pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected);
            break;
    #endif

        case MENU_OK            :
        case MENU_SET_ONE       :

            pMenu->bSetOne   = 1;
            iPrevPos         = pMenu->iCurrentPos;

            if(ulEvent==MENU_SET_ONE){
                pMenu->iCurrentPos = ulParam;
                pMenu->iSelected   = ulParam;
                pMenu->uiStatus |= MENU_STATUS_PRESSED;
                pMenu->uiStatus |= MENU_STATUS_ITEM_TOUCHED;
            }
            else{
                pMenu->iSelected = pMenu->iCurrentPos;
                pMenu->uiStatus |= MENU_STATUS_PRESSED;
            }

            if( CommonMenuOK( pMenu, AHC_TRUE ) == AHC_TRUE )
            {
                if(Deleting_InBrowser || Protecting_InBrowser){
                    printc("Delete/Protect/UnProtect Change to Browser Mode2\r\n");
                    // To check is there file in card, it no any file
                    // to reset Delete/(Un)Protect file in broswer flags.
                    // Otherwise those flag will make key/device events to
                    // be NULL!! UI will be stuck
                    BrowserFunc_ThumbnailEditCheckFileObj();
                    if(AHC_CheckCurSysMode(AHC_MODE_PLAYBACK))
                    {
                        Deleting_InBrowser = 0;
                        Protecting_InBrowser = 0;
                    }
                    return MENU_ERR_FORCE_BROWSER_EXIT;
                }
                else
                {

                    PSMENUSTRUCT pParentMenu;

                    pParentMenu        = pMenu->pParentMenu;
                    pMenu->pParentMenu = NULL;

                    if( pParentMenu == NULL ){
                        return MENU_ERR_EXIT;
                    }
                    SetCurrentMenu(pParentMenu);
                    pParentMenu->pfEventHandler(pParentMenu, MENU_INIT, 0);
                }

                return MENU_ERR_OK;
            }
            break;

        case MENU_MENU          :
            {
                {
                    PSMENUSTRUCT pParentMenu;

                    pMenu->bSetOne     = 0;
                    pParentMenu        = pMenu->pParentMenu;
                    pMenu->pParentMenu = NULL;

                    if(Delete_File_Confirm){
                        BrowserFunc_ThumbnailResetVarible(EDIT_OP_DELETE);
                    }
                    if(Protect_File_Confirm){
                        BrowserFunc_ThumbnailResetVarible(EDIT_OP_PROTECT);
                    }
                    if(UnProtect_File_Confirm){
                        BrowserFunc_ThumbnailResetVarible(EDIT_OP_UNPROTECT);
                    }

                    if( pParentMenu == NULL ){
                        return MENU_ERR_EXIT;
                    }

                    SetCurrentMenu(pParentMenu);
                    pParentMenu->pfEventHandler(pParentMenu, MENU_INIT, 0);
                }
            }
        break;
    #if 0
        case MENU_POWER_OFF     :
            AHC_PowerOff_NormalPath();
            break;
    #endif

        default:
            return MENU_ERR_OK;//MENU_ERR_NOT_MENU_EVENT;
            break;
    }

    return MENU_ERR_OK;
}

#if (SUPPORT_TOUCH_PANEL)
UINT32 SubMenuItem_Touch(UINT16 pt_x,UINT16 pt_y)
{
    UINT16  i = 0;
    PSMENUSTRUCT pMenu;
    int iPrevPos;
    UINT32 ret = MENU_ERR_OK;

    pMenu=GetCurrentMenu();

    if( pMenu->iNumOfItems <= 2 )
    {
        i =  ( pt_x- OSD_SUBMENU20_X )/( OSD_SUBMENU20_W + OSD_MENU_SUBITEM2X_INTERVAL );
    }
    else if( pMenu->iNumOfItems <= 4 )
    {
        i =  (( pt_x- OSD_SUBMENU40_X )/( OSD_SUBMENU40_W + OSD_MENU_SUBITEM4X_INTERVAL )
            +(( pt_y - OSD_SUBMENU40_Y )/( OSD_SUBMENU40_H+ OSD_MENU_SUBITEM4Y_INTERVAL ))*2 );
    }
    else
    {
        i =  (( pt_x- OSD_SUBMENU60_X )/( OSD_SUBMENU60_W + OSD_MENU_SUBITEM6X_INTERVAL )
            +(( pt_y - OSD_SUBMENU60_Y )/( OSD_SUBMENU60_H + OSD_MENU_ITEM_INTERVAL ))*2 );

        i = (pMenu->iCurrentPos/SUB_MENU_PAGE_ITEM)*SUB_MENU_PAGE_ITEM + i;
    }
    printc("SubMenuItem_Touch %d,ofItem %d\r\n",i,pMenu->iNumOfItems);

    if(i < pMenu->iNumOfItems)
    {
        if(i ==  pMenu->iCurrentPos)
            ret = SubMenuEventHandler(pMenu,MENU_SET_ONE,i);
        else
        {
            iPrevPos = pMenu->iCurrentPos;
            pMenu->iCurrentPos = i;
            MenuDrawChangeSubItem( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
        }
    }
    printc(FG_RED("SubMenuItem_Touch ret %d\r\n"),ret);
    if(ret == MENU_ERR_EXIT)
    {
        #ifdef SLIDE_MENU
        if(IsSlidingMenu())
            StopSlideMenu();
        #endif

        ResetCurrentMenu();

        Menu_ImportSetting();

        if(Deleting_InBrowser || Protecting_InBrowser)
        {
            //bForceSwitchBrowser = AHC_TRUE;
            StateSwitchMode(UI_BROWSER_STATE);
        }

    }
    return MENU_ERR_OK;
}

UINT32  SubMenuComfirm_Touch(UINT16 pt_x,UINT16 pt_y)
{
    UINT16  i = 0;
    UINT32 uParam;
    UINT32 ret = MENU_ERR_OK;
    PSMENUSTRUCT pMenu;
    RECT rc = RECT_TOUCH_BUTTON_MENU_YES;
    #define STR_GAP     (30)

    pMenu = GetCurrentMenu();
    i = (pt_x -rc.uiLeft)/(rc.uiWidth+ STR_GAP);
    if(i==0)
        uParam = 0;
    else
        uParam = 1;
    ret = pMenu->pfEventHandler(pMenu,MENU_SET_ONE,uParam);

    return MENU_ERR_OK;
}

#endif
