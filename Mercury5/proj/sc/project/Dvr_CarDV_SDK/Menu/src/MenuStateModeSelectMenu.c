/*===========================================================================
 * Include file
 *===========================================================================*/

#include "ahc_display.h"
#include "ahc_macro.h"
#include "ahc_menu.h"
#include "ahc_common.h"
#include "ahc_gui.h"
#include "ahc_utility.h"
#include "ahc_video.h"
#include "ahc_warningmsg.h"
#include "ahc_parameter.h"
#include "ahc_dcf.h"
#include "ahc_uf.h"
#include "ahc_os.h"
#include "ahc_message.h"
#include "ahc_general_cardv.h"
#include "MenuCommon.h"
#include "MenuStateModeSelectMenu.h"
#include "MenuStateGeneralSettingsMenu.h"
#include "MenuSetting.h"
#include "MenuStateMenu.h"
#include "MenuDrawCommon.h"
#include "MenuDrawingFunc.h"
#include "IconPosition.h"
#include "ColorDefine.h"
#include "OSDStrings.h"
#include "IconDefine.h"
#include "ledcontrol.h"
#include "dsc_charger.h"
#if WIFI_PORT == 1
#include "netapp.h"
#endif

/*===========================================================================
 * Extern function
 *===========================================================================*/
void InitOSD(void);
/*===========================================================================
 * Local function
 *===========================================================================*/

#if (USB_MODE_SELECT_EN)
AHC_BOOL USBSelectModeMSDC(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL USBSelectModePCam(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL USBSelectModeDSC(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL USBSelectModeDV(PSMENUITEM pItem, AHC_BOOL bIsHover);
#endif

UINT32 ModeMenuEventHandler(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam);
UINT32 KeyParser_USBModeSelectEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam);

/*===========================================================================
 * Global variable : Item Structure
 *===========================================================================*/

#if (USB_MODE_SELECT_EN)
SMENUITEM sItemUSB_MSDC_Mode     = { ITEMID_USB_MSDC_MODE,  &bmIcon_MSDC,         IDS_MSDC_MODE,    NULL, USBSelectModeMSDC,    0, AHC_TRUE, NULL };
SMENUITEM sItemUSB_PCam_Mode     = { ITEMID_USB_PCAM_MODE,  &bmIcon_PCCAM,        IDS_PCAM_MODE,    NULL, USBSelectModePCam,    0, AHC_TRUE, NULL };
SMENUITEM sItemUSB_DSC_Mode      = { ITEMID_USB_DSC_MODE,   &bmIcon_Button_Still, IDS_DSC_MODE,     NULL, USBSelectModeDSC,     0, AHC_TRUE, NULL };
SMENUITEM sItemUSB_DV_Mode       = { ITEMID_USB_DV_MODE,    &bmIcon_Button_Movie, IDS_DV_MODE,      NULL, USBSelectModeDV,      0, AHC_TRUE, NULL };
#endif

/*===========================================================================
 * Global variable : Item List
 *===========================================================================*/

#if (USB_MODE_SELECT_EN)
PSMENUITEM   sMenuListUSBModeSelect[] =
{
    &sItemUSB_MSDC_Mode,
    &sItemUSB_PCam_Mode,
    //&sItemUSB_DSC_Mode,
    &sItemUSB_DV_Mode
};
#endif

/*===========================================================================
 * Global varible : Menu Structure
 *===========================================================================*/

#if (USB_MODE_SELECT_EN)
SMENUSTRUCT   sUSBModeSelectMenu =
{
    MENUID_USB_MODE_SELECT,
    NULL,
    IDS_USB_FUNCTION,
    NULL,
    sizeof( sMenuListUSBModeSelect )/sizeof(PSMENUITEM),
    sMenuListUSBModeSelect,
    ModeMenuEventHandler,
    NULL,
    0,
    IDS_USB_FUNCTION,
#if (USB_MODE_SELECT_STYLE==MENU_2ND_STYLE)
    AHC_FALSE,
#else
    2, /* display on center of screen */
#endif
    0
};
#endif

/*===========================================================================
 * Global varible
 *===========================================================================*/

#if (USB_MODE_SELECT_EN)
USBMODE  ubUSBSelectedMode  = AHC_USB_MAX_MODE;
#endif

UINT8    ubModeDrawStyle    = 0;

extern AHC_BOOL     gbAhcDbgBrk;

/*===========================================================================
 * Main body
 *===========================================================================*/

#if 0
void ____USB_Function_____(){ruturn;} //dummy
#endif

#if (USB_MODE_SELECT_EN)
AHC_BOOL USBSelectModeMSDC(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiUSBFunction = MENU_SETTING_USB_MSDC;
    ubUSBSelectedMode = AHC_USB_MSDC_MODE;
    return AHC_TRUE;
}

AHC_BOOL USBSelectModePCam(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiUSBFunction = MENU_SETTING_USB_PCAM;
    ubUSBSelectedMode = AHC_USB_PCAM_MODE;
    return AHC_TRUE;
}

AHC_BOOL USBSelectModeDSC(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    ubUSBSelectedMode = AHC_USB_DSC_MODE;
    return AHC_TRUE;
}

AHC_BOOL USBSelectModeDV(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    ubUSBSelectedMode = AHC_USB_DV_MODE;
    return AHC_TRUE;
}

AHC_BOOL USBFunctionHandler(USBMODE selection)
{
    switch (selection)
    {
        case AHC_USB_MSDC_MODE:
            StateSwitchMode(UI_MSDC_STATE);
            break;
        case AHC_USB_PCAM_MODE:
            StateSwitchMode(UI_PCCAM_STATE);
            break;
        case AHC_USB_DSC_MODE:
            StateSwitchMode(UI_CAMERA_STATE);
            break;
        case AHC_USB_DV_MODE:
            StateSwitchMode(UI_VIDEO_STATE);
            break;
        default:
            StateSwitchMode(UI_MSDC_STATE);
            break;
    }
    return AHC_TRUE;
    }
#endif

#if 0
void ____Event_Function_____(){ruturn;} //dummy
#endif

#if (USB_MODE_SELECT_EN)
UINT32 ModeMenuEventHandler(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
{
    INT32 iPrevPos;

    switch(ulEvent)
    {
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
        pMenu->bSetOne     = 0;

        MenuDrawMainPage_ModeSelect( pMenu );
    break;

    case MENU_UP            :
        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, -1, AHC_TRUE );

        MenuDrawChangeItem_ModeSelect( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
    break;

    case MENU_DOWN          :
        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, 1, AHC_TRUE);

        MenuDrawChangeItem_ModeSelect( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
    break;

#if(DIR_KEY_TYPE==KEY_TYPE_4KEY)
    case MENU_LEFT          :

        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, -1, AHC_TRUE );
        MenuDrawChangeItem_ModeSelect( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
    break;

    case MENU_RIGHT          :

        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, 1, AHC_TRUE);
        MenuDrawChangeItem_ModeSelect( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
    break;
#endif

    case MENU_OK            :
    {
        UINT32 uiPrevSelected = pMenu->iSelected;

        pMenu->bSetOne   = 1;
        iPrevPos         = pMenu->iCurrentPos;
        pMenu->iSelected = pMenu->iCurrentPos;
        pMenu->uiStatus |= MENU_STATUS_PRESSED;

        MenuDrawChangeItem_ModeSelect( pMenu, pMenu->iCurrentPos, iPrevPos, uiPrevSelected );

        if( CommonMenuOK( pMenu, AHC_TRUE ) == AHC_TRUE )
        {
            return MENU_ERR_EXIT;
        }
    }
    break;

    case MENU_MENU          :
    case MENU_MODE_PRESS    :
    {
        PSMENUSTRUCT pParentMenu;

        pMenu->bSetOne     = 0;
        pParentMenu        = pMenu->pParentMenu;
        pMenu->pParentMenu = NULL;

        if( pParentMenu == NULL )
        {
            USBSelectModeDV(NULL,TRUE);//return to video preview.
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

#if (USB_MODE_SELECT_EN)
#if 0
void MenuStateUSBModeSelectMode( UINT32 ulEvent, UINT32 ulPosition )
{
    UINT32       ulOperation;
    UINT32       ulResult;
    PSMENUSTRUCT pCurrMenu = NULL;

    if( BUTTON_VIRTUAL_RESET == ulEvent )
    {
        ubUSBSelectedMode = AHC_USB_MAX_MODE;
        ubModeDrawStyle   = 0;
        SetCurrentMenu(&sUSBModeSelectMenu);
    }

    MenuModePreCheck(ulEvent);

    if(BUTTON_USB_REMOVED == ulEvent)
    {
        AHC_SetMode(AHC_MODE_IDLE);
        AHC_PowerOff_NormalPath();
    }

    ulOperation = MenuButtonToMenuOp( ulEvent,ulPosition );

    if(ulOperation == MENU_NONE)
        return;

#ifdef NET_SYNC_PLAYBACK_MODE
    if(EVENT_NET_ENTER_PLAYBACK == ulOperation)
    {
        ResetCurrentMenu();
        Menu_ImportSetting();
        StateSwitchMode(UI_NET_PLAYBACK_STATE);
        CGI_SET_STATUS(ulOperation, 0 /* SUCCESSFULLY */)
        return;
    }
#endif

    pCurrMenu = GetCurrentMenu();

    if( pCurrMenu == NULL )
        return;

    ulResult = pCurrMenu->pfEventHandler( pCurrMenu, ulOperation, ulPosition );

    if( ulResult == MENU_ERR_EXIT )
    {
        ResetCurrentMenu();

        Menu_ImportSetting();

        USBFunctionHandler(ubUSBSelectedMode);
    }
}
#endif

#if defined(WIFI_PORT) && (WIFI_PORT == 1)
DECL_AHC_EV_HANDLER(STATE_USB_MODE_SELECT_EVENT_ENTER_NET_PLAYBACK)
{
    //TBD //StateSwitchMode(UI_NET_PLAYBACK_STATE);
    CGI_SET_STATUS(ulEvent, CGI_ERR_NONE /* SUCCESSFULLY */);
}
#endif

DECL_AHC_EV_HANDLER(STATE_USB_MODE_SELECT_EVENT_USB_DETECT_LCD)
{
#if 0 //TBD
    if(IsAdapter_Connect())
    {
        if (VideoFunc_GetRecordStatus()) {
            // Video Recording to ignore USB Charger
            return;//break;
        }
        else {
            //Power Off
        }
    }
    else
    {
        if (MMPS_USB_NORMAL == MMPS_USB_GetStatus()) {
            StateSwitchMode(UI_USBSELECT_MENU_STATE);
        }
        else
        {
            StateSwitchMode(UI_VIDEO_STATE);
        }
    }
#endif
}

DECL_AHC_EV_HANDLER(STATE_USB_MODE_SELECT_EVENT_USB_REMOVED_LCD)
{
   /* In Video state, the event should always be USB adapter out,
     * the real USB plug-out event should be received in MSDC state.
     *
     * The function AHC_USB_GetLastStatus() may return wrong status,
     * when USB plug-in/out then adapter plug-in.
     *
     */
#if 0  //TBD
    if (AHC_IsDcCableConnect() == AHC_TRUE)
        return;//break;

    //AHC_Charger_SetEnable(AHC_FALSE);
#endif

    AHC_PowerOff_NormalPath();
}

#if (UVC_HOST_VIDEO_ENABLE)
DECL_AHC_EV_HANDLER(STATE_USB_MODE_SELECT_EVENT_USB_B_DEVICE_DETECT)
{
    //TBD
}
#endif

#if (TVOUT_ENABLE)
DECL_AHC_EV_HANDLER(STATE_USB_MODE_SELECT_EVENT_TV_DETECT)
{
    StateSwitchMode(UI_USBSELECT_MENU_STATE);
}
#endif

#if (HDMI_ENABLE)
DECL_AHC_EV_HANDLER(STATE_USB_MODE_SELECT_EVENT_HDMI_DETECT)
{
    StateSwitchMode(UI_USBSELECT_MENU_STATE);
}
#endif

UINT32 MenuStateUSBModeSelectModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{
    UINT32 ulResult = 0;
    UINT32 ulUSBModeSelectEvent = 0;

    ulUSBModeSelectEvent = KeyParser_USBModeSelectEvent(ulMsgId, ulEvent, ulParam);

    if (ulUSBModeSelectEvent != EVENT_NONE) {
        StateModeDoHandlerEvent(ulMsgId, ulUSBModeSelectEvent, ulParam);
    }
    else {
        ulResult = MenuStateHandlerCommon(ulMsgId, ulEvent, ulParam);
        if (MENU_ERR_EXIT == ulResult) {
            USBFunctionHandler(ubUSBSelectedMode);
        }
    }

    return 0;
}

AHC_BOOL MenuStateUSBModeSelectModeInitCommon(void)
{
    AHC_BOOL ahcRet = AHC_TRUE;
    UINT32 ulEvent = 0, ulResult = 0;

    MenuSettingConfig()->uiUSBFunction = 0xFF;

    ulEvent = MenuButtonToMenuOp(BUTTON_VIRTUAL_RESET , 0);

    ubUSBSelectedMode = AHC_USB_MAX_MODE;
    ubModeDrawStyle   = 0;
    SetCurrentMenu(&sUSBModeSelectMenu);

    ulResult = MenuStateExecutionCommon(ulEvent, 0);

    //MenuStateUSBModeSelectMode(BUTTON_VIRTUAL_RESET, 0);
    //LedCtrl_LcdBackLight(AHC_TRUE);

    return ahcRet;
}

AHC_BOOL MenuStateUSBModeSelectModeInitLCD(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    StateLCDCheckStatus(UI_USBSELECT_MENU_STATE); //TBD.

    ahcRet = AHC_SwitchDisplayOutputDevLCD();
    if (ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return AHC_FALSE;}

    RTNA_LCD_Backlight(MMP_TRUE);

    ahcRet = MenuStateUSBModeSelectModeInitCommon();
    if (ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return AHC_FALSE;}

    return ahcRet;
}

#if (TVOUT_ENABLE)
AHC_BOOL MenuStateUSBModeSelectModeInitTV(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    StateLCDCheckStatus(UI_USBSELECT_MENU_STATE); //TBD.

    ahcRet = AHC_SwitchDisplayOutputDevTVout();
    if (ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return AHC_FALSE;}

    ahcRet = MenuStateUSBModeSelectModeInitCommon();
    if (ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return AHC_FALSE;}

    return ahcRet;
}
#endif

#if (HDMI_ENABLE)
AHC_BOOL MenuStateUSBModeSelectModeInitHDMI(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    ahcRet = AHC_SwitchDisplayOutputDevHDMI();
    if (ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return AHC_FALSE;}

    ahcRet = MenuStateUSBModeSelectModeInitCommon();
    if (ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return AHC_FALSE;}

    return ahcRet;
}
#endif

AHC_BOOL MenuStateUSBModeSelectModeShutDown(void* pData)
{
    AHC_SetMode(AHC_MODE_IDLE);

    return AHC_TRUE;
}
#endif

#if (USB_MODE_SELECT_EN)
AHC_BOOL StateSelectFuncUSBSelectMenuMode(void)
{
    AHC_BOOL    ahcRet = AHC_TRUE;

#if defined(WIFI_PORT) && (WIFI_PORT == 1)
    RegisterEventCb(EVENT_NET_ENTER_PLAYBACK,           STATE_USB_MODE_SELECT_EVENT_ENTER_NET_PLAYBACK);
#endif

    RegisterEventCb(EVENT_USB_DETECT,                   STATE_USB_MODE_SELECT_EVENT_USB_DETECT_LCD);
    RegisterEventCb(EVENT_USB_REMOVED,                  STATE_USB_MODE_SELECT_EVENT_USB_REMOVED_LCD);

#if (UVC_HOST_VIDEO_ENABLE)
    RegisterEventCb(EVENT_USB_B_DEVICE_DETECT,          STATE_USB_MODE_SELECT_EVENT_USB_B_DEVICE_DETECT);
    RegisterEventCb(EVENT_USB_B_DEVICE_REMOVED,         STATE_USB_MODE_SELECT_EVENT_USB_B_DEVICE_DETECT);
#endif

#if (TVOUT_ENABLE)
    RegisterEventCb(EVENT_TV_DETECT,                    STATE_USB_MODE_SELECT_EVENT_TV_DETECT);
    RegisterEventCb(EVENT_TV_REMOVED,                   STATE_USB_MODE_SELECT_EVENT_TV_DETECT);
#endif
#if (HDMI_ENABLE)
    RegisterEventCb(EVENT_HDMI_DETECT,                  STATE_USB_MODE_SELECT_EVENT_HDMI_DETECT);
    RegisterEventCb(EVENT_HDMI_REMOVED,                 STATE_USB_MODE_SELECT_EVENT_HDMI_DETECT);
#endif

#if (HDMI_ENABLE)
    if (AHC_IsHdmiConnect()){
        ahcRet = StateModeSetOperation(UI_USBSELECT_MENU_STATE, MenuStateUSBModeSelectModeInitHDMI, MenuStateUSBModeSelectModeShutDown, MenuStateUSBModeSelectModeHandler);
    }else
#endif
#if (TVOUT_ENABLE)
    if (AHC_IsTVConnectEx()){
        ahcRet = StateModeSetOperation(UI_USBSELECT_MENU_STATE, MenuStateUSBModeSelectModeInitTV, MenuStateUSBModeSelectModeShutDown, MenuStateUSBModeSelectModeHandler);
    }else
#endif
    {
        ahcRet = StateModeSetOperation(UI_USBSELECT_MENU_STATE, MenuStateUSBModeSelectModeInitLCD, MenuStateUSBModeSelectModeShutDown, MenuStateUSBModeSelectModeHandler);
    }

    return ahcRet;
}
#endif
