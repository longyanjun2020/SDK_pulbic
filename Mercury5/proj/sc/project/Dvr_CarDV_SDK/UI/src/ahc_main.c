/*===========================================================================
 * Include file
 *===========================================================================*/

#include "Customer_config.h"
#include "ahc_common.h"
#include "ahc_message.h"
#include "ahc_sensor.h"
#include "ahc_utility.h"
#include "ahc_gui.h"
#include "ahc_os.h"
#include "ahc_menu.h"
#include "ahc_version.h"
#include "ahc_fs.h"
#include "ahc_media.h"
#include "ahc_parameter.h"
#include "ahc_warningmsg.h"
#include "ahc_display.h"
#include "ahc_general_cardv.h"
#include "ahc_video.h"
#include "ahc_usb.h"
#include "ledcontrol.h"
#include "zoomcontrol.h"
#include "statecamerafunc.h"
#include "dsc_charger.h"
#if (SUPPORT_GSENSOR)
#include "GSensor_ctrl.h"
#endif
#if (SUPPORT_IR_CONVERTER)
#include "ir_ctrl.h"
#endif
#if (SUPPORT_GPS)
#include "gps_ctl.h"
#endif
#if (TOUCH_UART_FUNC_EN)
#include "Touch_Uart_ctrl.h"
#endif
#if defined(SPEECH_RECOGNIZE_EN) && (SPEECH_RECOGNIZE_EN)
#include "3rd_speech.h"
#include "mmpd_audio.h"
#endif
#include "disp_drv.h"
#include "AIT_Init.h"
#include "ahc_task.h"

#include "hdr_cfg.h"
#include "snr_cfg.h"
#include "mmpf_system.h" //For task monitor //CarDV...
#include "pmuctrl.h"
#include "IconPosition.h"
#include "ColorDefine.h"
#include "MenuDrawCommon.h"
#include "ahc_callback.h"
#include "ahc_uf.h"
#if defined(__RTK_OS__)
#include "cam_os_wrapper.h"
#include "halex_timer.h"
#include "sys_MsWrapper_cus_os_type.h"
#include "sys_MsWrapper_cus_os_timer.h"
#endif

/*===========================================================================
 * Global variable
 *===========================================================================*/

AHC_OS_SEMID    ahc_System_Ready;
AHC_BOOL        gAHC_InitialDone = AHC_FALSE;
AHC_BOOL        gAHC_UpdateMenuDone = AHC_FALSE;

/*===========================================================================
 * Extern variable
 *===========================================================================*/

extern UARTCOMMAND  sAhcUartCommand[];

/*===========================================================================
 * Extern function
 *===========================================================================*/

extern void     AIHC_SetTempDCFMemStartAddr(UINT32 addr);

/*===========================================================================
 * Main body
 *===========================================================================*/

#if (TVOUT_PREVIEW_EN)
void InitOSDCustom_Tv(U32 colorFormat, AHC_OSD_ROTATE_DRAW_MODE ahcOSDRotateDraw)
{
    UINT16      uwTVWidth, uwTVHeight;
    UINT16      uwTVOffX, uwTVOffY;
    UINT32      pos[2];
    UINT32      uwDispScale = 0;
    UINT16      uwTVTempWidth, uwTVTempHeight;
    UINT8       ubTVSystem = MenuSettingConfig()->uiTVSystem;
    UINT16 uwDisplayID = 0;

    AHC_Display_GetWidthHdight(&uwTVWidth, &uwTVHeight);

    if(ubTVSystem == TV_SYSTEM_PAL)
    {
        if ((uiGetCurrentState() == UI_CAMERA_STATE)||
            (uiGetCurrentState() == UI_VIDEO_STATE)||
            (uiGetCurrentState() == UI_CLOCK_SETTING_STATE)||
            (uiGetCurrentState() == UI_USBSELECT_MENU_STATE))
        {
            uwDispScale = 1;
            uwTVTempWidth = uwTVWidth / uwDispScale;
            uwTVTempHeight = uwTVHeight / uwDispScale;
            uwTVOffX = 0;
            uwTVOffY = 0;
        }else
        if (uiGetCurrentState() == UI_BROWSER_STATE)
        {
            uwDispScale = 1;
            uwTVTempWidth = POS_TV_PAL_BROWSER_OSD_W;
            uwTVTempHeight = POS_TV_PAL_BROWSER_OSD_H;
            uwTVOffX = 0;
            uwTVOffY = 0;//68;
        }else
        //if (uiGetCurrentState() == UI_PLAYBACK_STATE)  //By default,All of other state use this setting, include UI_PLAYBACK_STATE
        {
            uwDispScale = 1;
            uwTVTempWidth = POS_TV_PLAY_OSD_W;
            uwTVTempHeight = POS_TV_PLAY_OSD_H;
            uwTVOffX = uwTVWidth- uwTVTempWidth - 40;
            uwTVOffY = 68;
        }
    }
    else if(ubTVSystem == TV_SYSTEM_NTSC)
    {
        if ((uiGetCurrentState() == UI_CAMERA_STATE)||
            (uiGetCurrentState() == UI_VIDEO_STATE)||
            (uiGetCurrentState() == UI_CLOCK_SETTING_STATE)||
            (uiGetCurrentState() == UI_USBSELECT_MENU_STATE))
        {
            uwDispScale = 1;
            uwTVTempWidth = uwTVWidth / uwDispScale;
            uwTVTempHeight = uwTVHeight / uwDispScale;
            uwTVOffX = 0;
            uwTVOffY = 0;
        }else
        if (uiGetCurrentState() == UI_BROWSER_STATE)
        {
            uwDispScale = 1;
            uwTVTempWidth = POS_TV_NTSC_BROWSER_OSD_W;
            uwTVTempHeight = POS_TV_NTSC_BROWSER_OSD_H;
            uwTVOffX = 0;
            uwTVOffY = 0;//20;
        }else
        //if (uiGetCurrentState() == UI_PLAYBACK_STATE)  //All of other state use this setting, include UI_PLAYBACK_STATE
        {
            uwDispScale = 1;
            uwTVTempWidth = POS_TV_PLAY_OSD_W;
            uwTVTempHeight = POS_TV_PLAY_OSD_H;
            uwTVOffX = uwTVWidth- uwTVTempWidth - 20;
            uwTVOffY = 20;
        }
    }

    {
        //** Set TV OSD#1 by uwDisplayID = 17
        uwDisplayID = TVFunc_GetUImodeOsdID();
        AHC_OSDCreateBuffer(uwDisplayID ,uwTVTempWidth, uwTVTempHeight, OSD_COLOR_RGB565);
        pos[0] = uwTVOffX;
        pos[1] = uwTVOffY;
        AHC_OSDSetDisplayAttr(uwDisplayID, AHC_OSD_ATTR_DISPLAY_OFFSET, pos);
        pos[0] = uwDispScale - 1;
        pos[1] = uwDispScale - 1;
        AHC_OSDSetDisplayAttr(uwDisplayID, AHC_OSD_ATTR_DISPLAY_SCALE, pos);
        pos[0] = 1;
        pos[1] = OSD_COLOR_TRANSPARENT;
        AHC_OSDSetDisplayAttr(uwDisplayID, AHC_OSD_ATTR_TRANSPARENT_ENABLE, pos);

        pos[0] = OSD_ROTATE_DRAW_NONE;
        AHC_OSDSetDisplayAttr(uwDisplayID, AHC_OSD_ATTR_ROTATE_BY_GUI, pos);

        pos[0] = OSD_FLIP_DRAW_NONE_ENABLE;
        AHC_OSDSetDisplayAttr(uwDisplayID, AHC_OSD_ATTR_FLIP_BY_GUI, pos);

        //** Set TV OSD by uwDisplayID = 17
        //      AHC_OSDCreateBuffer(TV_UI_OSD2_ID ,uwTVTempWidth, uwTVTempHeight, OSD_COLOR_RGB565);
        //      pos[0] = uwTVOffX;
        //      pos[1] = uwTVOffY;
        //      AHC_OSDSetDisplayAttr(TV_UI_OSD2_ID, AHC_OSD_ATTR_DISPLAY_OFFSET, pos);
        //      pos[0] = uwDispScale - 1;
        //      pos[1] = uwDispScale - 1;
        //      AHC_OSDSetDisplayAttr(TV_UI_OSD2_ID, AHC_OSD_ATTR_DISPLAY_SCALE, pos);
        //      pos[0] = 1;
        //      pos[1] = OSD_COLOR_TRANSPARENT;
        //      AHC_OSDSetDisplayAttr(TV_UI_OSD2_ID, AHC_OSD_ATTR_TRANSPARENT_ENABLE, pos);

        //      pos[0] = OSD_ROTATE_DRAW_NONE;
        //      AHC_OSDSetDisplayAttr(TV_UI_OSD2_ID, AHC_OSD_ATTR_ROTATE_BY_GUI, pos);

        //      pos[0] = OSD_FLIP_DRAW_NONE_ENABLE;
        //    AHC_OSDSetDisplayAttr(TV_UI_OSD2_ID, AHC_OSD_ATTR_FLIP_BY_GUI, pos);
        //--------------------------------------------------------
    }

#if (TV_MENU_EN)
    {
        UINT32      uwDispScale = 0;
        UINT16      uwTVTempWidth, uwTVTempHeight;
        UINT16 uwDisplayID = 0, uwDisplayID2 = 0;

        uwDispScale = OSD_DISPLAY_SCALE_TV;

        uwTVTempWidth = uwTVWidth / OSD_DISPLAY_SCALE_TV;
        uwTVTempHeight = uwTVHeight / OSD_DISPLAY_SCALE_TV;

        uwDisplayID = TVFunc_GetMenuOsdID();
        uwDisplayID2 = TVFunc_GetMenuOsd2ID();
        //** Set TV MENU#1 by uwDisplayID = 18,19
        AHC_OSDCreateBuffer(uwDisplayID, uwTVTempWidth, uwTVTempHeight, OSD_COLOR_RGB565);
        AHC_OSDCreateBuffer(uwDisplayID2, uwTVTempWidth, uwTVTempHeight, OSD_COLOR_RGB565);
        pos[0] = 0;//uwTVOffX;
        pos[1] = 0;//uwTVOffY;
        AHC_OSDSetDisplayAttr(uwDisplayID, AHC_OSD_ATTR_DISPLAY_OFFSET, pos);
        AHC_OSDSetDisplayAttr(uwDisplayID2, AHC_OSD_ATTR_DISPLAY_OFFSET, pos);
        pos[0] = uwDispScale - 1;
        pos[1] = uwDispScale - 1;
        AHC_OSDSetDisplayAttr(uwDisplayID, AHC_OSD_ATTR_DISPLAY_SCALE, pos);
        AHC_OSDSetDisplayAttr(uwDisplayID2, AHC_OSD_ATTR_DISPLAY_SCALE, pos);
        pos[0] = OSD_FLIP_DRAW_NONE_ENABLE;
        AHC_OSDSetDisplayAttr(uwDisplayID,  AHC_OSD_ATTR_FLIP_BY_GUI, pos);
        AHC_OSDSetDisplayAttr(uwDisplayID2,  AHC_OSD_ATTR_FLIP_BY_GUI, pos);
        pos[0] = OSD_ROTATE_DRAW_NONE;
        AHC_OSDSetDisplayAttr(uwDisplayID,  AHC_OSD_ATTR_ROTATE_BY_GUI, pos);
        AHC_OSDSetDisplayAttr(uwDisplayID2,  AHC_OSD_ATTR_ROTATE_BY_GUI, pos);
        AHC_OSDClearBuffer(uwDisplayID);
        AHC_OSDClearBuffer(uwDisplayID2);
    }
#endif
}
#endif

#if (HDMI_ENABLE)
void InitOSDCustom_Hdmi(U32 colorFormat, AHC_OSD_ROTATE_DRAW_MODE ahcOSDRotateDraw)
{
    UINT16      uwHDMIWidth, uwHDMIHeight;
    UINT16      uwHDMIOffX, uwHDMIOffY;
    UINT32      pos[2];
    UINT32      uwDispScale = 0;
    UINT16      uwHDMITempWidth, uwHDMITempHeight;

    AHC_GetHdmiDisplayWidthHeight(&uwHDMIWidth, &uwHDMIHeight);


    if((MenuSettingConfig()->uiHDMIOutput == HDMI_OUTPUT_1080I)||(MenuSettingConfig()->uiHDMIOutput == HDMI_OUTPUT_1080P))
    {
        if ((uiGetCurrentState() == UI_CAMERA_STATE)||
            (uiGetCurrentState() == UI_VIDEO_STATE)||
            (uiGetCurrentState() == UI_CLOCK_SETTING_STATE)||
            (uiGetCurrentState() == UI_USBSELECT_MENU_STATE))
        {
            uwDispScale = OSD_DISPLAY_SCALE_HDMI_FHD;
            uwHDMITempWidth = uwHDMIWidth / uwDispScale;
            uwHDMITempHeight = uwHDMIHeight / uwDispScale;
            uwHDMIOffX = 0;
            uwHDMIOffY = 0;
        }else
        if (uiGetCurrentState() == UI_BROWSER_STATE)
        {
            uwDispScale = OSD_PREVIEW_SCALE_HDMI;
            uwHDMITempWidth = POS_HDMI_1080P_BROWSER_OSD_W;
            uwHDMITempHeight = POS_HDMI_1080P_BROWSER_OSD_H;
            uwHDMIOffX = 0;
            uwHDMIOffY = 15;
        }else
        //if (uiGetCurrentState() == UI_PLAYBACK_STATE)     //By default,All of other state use this setting, include UI_PLAYBACK_STATE
        {
            uwDispScale = OSD_PREVIEW_SCALE_HDMI;
            uwHDMITempWidth = POS_HDMI_PLAY_OSD_W;
            uwHDMITempHeight = POS_HDMI_PLAY_OSD_H;
            uwHDMIOffX = uwHDMIWidth- uwHDMITempWidth - 50;
            uwHDMIOffY = 25;
        }
    }
    else if(MenuSettingConfig()->uiHDMIOutput == HDMI_OUTPUT_720P)
    {
        if ((uiGetCurrentState() == UI_CAMERA_STATE)||
            (uiGetCurrentState() == UI_VIDEO_STATE)||
            (uiGetCurrentState() == UI_CLOCK_SETTING_STATE)||
            (uiGetCurrentState() == UI_USBSELECT_MENU_STATE))
        {
            uwDispScale = OSD_DISPLAY_SCALE_HDMI_HD;
            uwHDMITempWidth = uwHDMIWidth / uwDispScale;
            uwHDMITempHeight = uwHDMIHeight / uwDispScale;
            uwHDMIOffX = 0;
            uwHDMIOffY = 0;
        }else
        if (uiGetCurrentState() == UI_BROWSER_STATE)
        {
            uwDispScale = OSD_PREVIEW_SCALE_HDMI;
            uwHDMITempWidth = POS_HDMI_720P_BROWSER_OSD_W;
            uwHDMITempHeight = POS_HDMI_720P_BROWSER_OSD_H;
            uwHDMIOffX = 0;
            uwHDMIOffY = 20;
        }else
        //if (uiGetCurrentState() == UI_PLAYBACK_STATE)     //All of other state use this setting
        {
            uwDispScale = OSD_PREVIEW_SCALE_HDMI;
            uwHDMITempWidth = POS_HDMI_PLAY_OSD_W;
            uwHDMITempHeight = POS_HDMI_PLAY_OSD_H;
            uwHDMIOffX = uwHDMIWidth- uwHDMITempWidth - 40;
            uwHDMIOffY = 25;
        }
    }
    else if(MenuSettingConfig()->uiHDMIOutput == HDMI_OUTPUT_480P)
    {
        if ((uiGetCurrentState() == UI_CAMERA_STATE)||
            (uiGetCurrentState() == UI_VIDEO_STATE)||
            (uiGetCurrentState() == UI_CLOCK_SETTING_STATE)||
            (uiGetCurrentState() == UI_USBSELECT_MENU_STATE))
        {
            uwDispScale = OSD_DISPLAY_SCALE_TV;
            uwHDMITempWidth = uwHDMIWidth / uwDispScale;
            uwHDMITempHeight = uwHDMIHeight / uwDispScale;
            uwHDMIOffX = 0;
            uwHDMIOffY = 0;
        }else
        if (uiGetCurrentState() == UI_BROWSER_STATE)
        {
            uwDispScale = OSD_PREVIEW_SCALE_HDMI;
            uwHDMITempWidth = POS_HDMI_480P_BROWSER_OSD_W;
            uwHDMITempHeight = POS_HDMI_480P_BROWSER_OSD_H;
            uwHDMIOffX = 0;
            uwHDMIOffY = 20;
        }else
        //if (uiGetCurrentState() == UI_PLAYBACK_STATE)     //CAUTION:: All of other state use this setting
        {
            uwDispScale = OSD_PREVIEW_SCALE_HDMI;
            uwHDMITempWidth = POS_HDMI_PLAY_OSD_W;
            uwHDMITempHeight = POS_HDMI_PLAY_OSD_H;
            uwHDMIOffX = uwHDMIWidth- uwHDMITempWidth - 40;
            uwHDMIOffY = 25;
        }
    }
#if OSD_PREVIEW_SCALE_HDMI
    {
        UINT16 uwDisplayID = 0, uwDisplayID2 = 0;

        uwDisplayID = HDMIFunc_GetUImodeOsdID();
        uwDisplayID2 = HDMIFunc_GetUImodeOsd2ID();
        //** Set HDMI OSD#1 by uwDisplayID = 16
        AHC_OSDCreateBuffer(uwDisplayID ,uwHDMITempWidth, uwHDMITempHeight, OSD_COLOR_RGB565);
        pos[0] = uwHDMIOffX;
        pos[1] = uwHDMIOffY;
        AHC_OSDSetDisplayAttr(uwDisplayID, AHC_OSD_ATTR_DISPLAY_OFFSET, pos);
        pos[0] = uwDispScale - 1;
        pos[1] = uwDispScale - 1;
        AHC_OSDSetDisplayAttr(uwDisplayID, AHC_OSD_ATTR_DISPLAY_SCALE, pos);
        pos[0] = 1;
        pos[1] = OSD_COLOR_TRANSPARENT;
        AHC_OSDSetDisplayAttr(uwDisplayID, AHC_OSD_ATTR_TRANSPARENT_ENABLE, pos);

        pos[0] = OSD_ROTATE_DRAW_NONE;
        AHC_OSDSetDisplayAttr(uwDisplayID, AHC_OSD_ATTR_ROTATE_BY_GUI, pos);

        pos[0] = OSD_FLIP_DRAW_NONE_ENABLE;
        AHC_OSDSetDisplayAttr(uwDisplayID, AHC_OSD_ATTR_FLIP_BY_GUI, pos);

        //** Set HDMI OSD by uwDisplayID = 17
        AHC_OSDCreateBuffer(uwDisplayID2 ,uwHDMITempWidth, uwHDMITempHeight, OSD_COLOR_RGB565);
        pos[0] = uwHDMIOffX;
        pos[1] = uwHDMIOffY;
        AHC_OSDSetDisplayAttr(uwDisplayID2, AHC_OSD_ATTR_DISPLAY_OFFSET, pos);
        pos[0] = uwDispScale - 1;
        pos[1] = uwDispScale - 1;
        AHC_OSDSetDisplayAttr(uwDisplayID2, AHC_OSD_ATTR_DISPLAY_SCALE, pos);
        pos[0] = 1;
        pos[1] = OSD_COLOR_TRANSPARENT;
        AHC_OSDSetDisplayAttr(uwDisplayID2, AHC_OSD_ATTR_TRANSPARENT_ENABLE, pos);

        pos[0] = OSD_ROTATE_DRAW_NONE;
        AHC_OSDSetDisplayAttr(uwDisplayID2, AHC_OSD_ATTR_ROTATE_BY_GUI, pos);

        pos[0] = OSD_FLIP_DRAW_NONE_ENABLE;
        AHC_OSDSetDisplayAttr(uwDisplayID2, AHC_OSD_ATTR_FLIP_BY_GUI, pos);
        //--------------------------------------------------------
    }
#endif

#if (HDMI_MENU_EN)
    {
        UINT16 uwMenuID = 0, uwMenuID2 = 0;

        uwMenuID = HDMIFunc_GetMenuOsdID();
        uwMenuID2 = HDMIFunc_GetMenuOsd2ID();
        if((MenuSettingConfig()->uiHDMIOutput == HDMI_OUTPUT_1080I)||(MenuSettingConfig()->uiHDMIOutput == HDMI_OUTPUT_1080P))
        {
            if (uiGetCurrentState() == UI_BROWSER_STATE)
            {
                uwDispScale = OSD_DISPLAY_SCALE_HDMI_FHD;
                uwHDMITempWidth = uwHDMIWidth / uwDispScale;
                uwHDMITempHeight = uwHDMIHeight / uwDispScale;
                uwHDMIOffX = 0;
                uwHDMIOffY = 0;
            }
        }
        else if((MenuSettingConfig()->uiHDMIOutput == HDMI_OUTPUT_720P))
        {
            if (uiGetCurrentState() == UI_BROWSER_STATE)
            {
                uwDispScale = OSD_DISPLAY_SCALE_HDMI_HD;
                uwHDMITempWidth = uwHDMIWidth / uwDispScale;
                uwHDMITempHeight = uwHDMIHeight / uwDispScale;
                uwHDMIOffX = 0;
                uwHDMIOffY = 0;
            }
        }
        //** Set HDMI OSD#1 by uwDisplayID = 18,19
        AHC_OSDCreateBuffer(uwMenuID, uwHDMITempWidth, uwHDMITempHeight, OSD_COLOR_RGB565);

        pos[0] = uwHDMIOffX;
        pos[1] = uwHDMIOffY;
        AHC_OSDSetDisplayAttr(uwMenuID, AHC_OSD_ATTR_DISPLAY_OFFSET, pos);
        pos[0] = uwDispScale - 1;
        pos[1] = uwDispScale - 1;
        AHC_OSDSetDisplayAttr(uwMenuID, AHC_OSD_ATTR_DISPLAY_SCALE, pos);
        pos[0] = OSD_ROTATE_DRAW_NONE;
        AHC_OSDSetDisplayAttr(uwMenuID,  AHC_OSD_ATTR_ROTATE_BY_GUI, pos);
        AHC_OSDClearBuffer(uwMenuID);

        AHC_OSDCreateBuffer(uwMenuID2, uwHDMITempWidth, uwHDMITempHeight, OSD_COLOR_RGB565);
        pos[0] = uwHDMIOffX;
        pos[1] = uwHDMIOffY;
        AHC_OSDSetDisplayAttr(uwMenuID2, AHC_OSD_ATTR_DISPLAY_OFFSET, pos);
        pos[0] = uwDispScale - 1;
        pos[1] = uwDispScale - 1;
        AHC_OSDSetDisplayAttr(uwMenuID2, AHC_OSD_ATTR_DISPLAY_SCALE, pos);
        pos[0] = OSD_ROTATE_DRAW_NONE;
        AHC_OSDSetDisplayAttr(uwMenuID2,  AHC_OSD_ATTR_ROTATE_BY_GUI, pos);
        AHC_OSDClearBuffer(uwMenuID2);
    }
#endif
}
#endif

void InitOSDCustom_Lcd(U32 colorFormat, AHC_OSD_ROTATE_DRAW_MODE ahcOSDRotateDraw)
{
    UINT32 i;
    UINT32 iVal[10];
    INT32  bAlphaBlendingEn = 1;

    // LAYER 0 - ID 0 ~ 15
    // LAYER 1 - ID 16 ~ 31
    // Default layer is display id 0 & 16

    if(OSD_COLOR_RGB565 == colorFormat){
        colorFormat = OSD_COLOR_RGB565_CCW; //use RGB565 CCW internally.
    }
    else if(OSD_COLOR_ARGB32 == colorFormat){
        colorFormat = OSD_COLOR_ARGB32_CCW; //use ARGB CCW internally.
    }

    for(i= MENU_OSD_FIRST_ID; i <= MENU_OSD_END_ID; i++)
    {
        AHC_OSDCreateBuffer(i,
                RTNA_LCD_GetAttr()->usPanelW / OSD_DISPLAY_SCALE_LCD, RTNA_LCD_GetAttr()->usPanelH / OSD_DISPLAY_SCALE_LCD,
                colorFormat);

        iVal[0] = ahcOSDRotateDraw;
        AHC_OSDSetDisplayAttr(i,  AHC_OSD_ATTR_ROTATE_BY_GUI, iVal);
        iVal[0] = OSD_FLIP_DRAW_NONE_ENABLE;
        AHC_OSDSetDisplayAttr(i,  AHC_OSD_ATTR_FLIP_BY_GUI, iVal);

        if (OSD_DISPLAY_SCALE_LCD) {
            iVal[0] = OSD_DISPLAY_SCALE_LCD - 1;    // remapping to enum MMP_DISPLAY_DUPLICATE
            iVal[1] = OSD_DISPLAY_SCALE_LCD - 1;
        }
        else {
            iVal[0] = MMP_DISPLAY_DUPLICATE_1X;
            iVal[1] = MMP_DISPLAY_DUPLICATE_1X;
        }
        AHC_OSDSetDisplayAttr(i, AHC_OSD_ATTR_DISPLAY_SCALE, iVal);
        AHC_OSDClearBuffer(i);
        AHC_OSDSetCurrentDisplay(i);

        // Set transparent color
        iVal[0] = 1;            // Enable
        iVal[1] = 0x00000000;   // Black color
        AHC_OSDSetDisplayAttr(i, AHC_OSD_ATTR_TRANSPARENT_ENABLE, iVal);

        if(bAlphaBlendingEn){
            iVal[0] = 1;        // Enable
            iVal[1] = AHC_OSD_ALPHA_GLOBAL; //AHC_OSD_ALPHA_ARGB;
            iVal[2] = 0xFF; // constant alpha ( 0 ~ 0xFF)

            AHC_OSDSetDisplayAttr(i, AHC_OSD_ATTR_ALPHA_BLENDING_ENABLE, iVal);
        }
    }

    // Set transparent color
    iVal[0] = 1;            // Enable
    iVal[1] = 0x00000000;   // Black color
    AHC_OSDSetDisplayAttr(0, AHC_OSD_ATTR_TRANSPARENT_ENABLE, iVal);

    if(bAlphaBlendingEn){
        iVal[0] = 1;        // Enable
        iVal[1] = AHC_OSD_ALPHA_GLOBAL; //AHC_OSD_ALPHA_ARGB;
        iVal[2] = 0xFF; // constant alpha ( 0 ~ 0xFF)

        AHC_OSDSetDisplayAttr(0, AHC_OSD_ATTR_ALPHA_BLENDING_ENABLE, iVal);
    }

    AHC_OSDSetCurrentDisplay(0);
    AHC_OSDSetCurrentDisplay(MENU_OSD_FIRST_ID);

    // Set MAIN Inactive & OVERLAY WINDOW Active
    AHC_OSDSetActive(0, 0);
    AHC_OSDSetActive(MENU_OSD_FIRST_ID, 1);
}

#if (TVOUT_ENABLE)//(TVOUT_PREVIEW_EN)
void InitOSD_TVout(void)
{
    U32 colorFormat;
    AHC_OSD_ROTATE_DRAW_MODE ahcOSDRotateDraw;
    U32 ulOSDWidth, ulOSDHeight, ulThumbWidth, ulThumbHeight;
    AHC_BOOL bMainBuffFull;
    UINT16      uwTVWidth, uwTVHeight;

    GUI_RegisterExternalFillRectCB((void *)AHC_OSD_ExternalFillRectCB);

#if 0//TBD
    if(MenuSettingConfig()->uiTVSystem==TV_SYSTEM_PAL)
    AHC_SetDisplayOutputDev(DISP_OUT_TV_PAL, AHC_DISPLAY_DUPLICATE_1X);
    else
    AHC_SetDisplayOutputDev(DISP_OUT_TV_NTSC, AHC_DISPLAY_DUPLICATE_1X);
#endif
#if (TVOUT_PREVIEW_EN)
    ulOSDWidth = 320; //TBD
    ulOSDHeight = 240;
#else
    ulOSDWidth = 0; //TBD
    ulOSDHeight = 0
#endif
    if (uiGetCurrentState() == UI_BROWSER_STATE){
        AHC_DISPLAY_OUTPUTPANEL pCurDevice;

        AHC_GetDisplayOutputDev(&pCurDevice);
        //TBD
        if(((MenuSettingConfig()->uiTVSystem == TV_SYSTEM_PAL) && (pCurDevice != AHC_DISPLAY_PAL_TV)) ||
        ((MenuSettingConfig()->uiTVSystem == TV_SYSTEM_NTSC) && (pCurDevice != AHC_DISPLAY_NTSC_TV))){
            switch(MenuSettingConfig()->uiTVSystem)
            {
                case TV_SYSTEM_PAL:
                    AHC_SetDisplayOutputDev(DISP_OUT_TV_PAL, AHC_DISPLAY_DUPLICATE_1X);
                    AHC_SetCurrentDisplayEx(MMP_DISPLAY_SEL_PAL_TV);
                    break;

                case TV_SYSTEM_NTSC:
                default:
                    AHC_SetDisplayOutputDev(DISP_OUT_TV_NTSC, AHC_DISPLAY_DUPLICATE_1X);
                    AHC_SetCurrentDisplayEx(MMP_DISPLAY_SEL_NTSC_TV);
                    break;
            }
        }
        AHC_Display_GetWidthHdight(&uwTVWidth, &uwTVHeight);
        switch(MenuSettingConfig()->uiTVSystem) {
            case TV_SYSTEM_NTSC:
                ulThumbWidth    = uwTVWidth;
                ulThumbHeight   = uwTVHeight - POS_TV_NTSC_BROWSER_OSD_H;
                break;

            case TV_SYSTEM_PAL:
                ulThumbWidth    = uwTVWidth;
                ulThumbHeight   = uwTVHeight - POS_TV_PAL_BROWSER_OSD_H;
                break;

            default:
                printc("TVFunc_ChangeOSDStatus Error!\r\n");
                break;
        }

    }else{
        ulThumbWidth = 0;
        ulThumbHeight = 0;
    }

    bMainBuffFull = AHC_FALSE;

    colorFormat = WMSG_LAYER_WIN_COLOR_FMT;
    ahcOSDRotateDraw = OSD_ROTATE_DRAW_NONE;
    AHC_OSD_RegisterInitOSDCustomCB((void *)InitOSDCustom_Tv);

    AHC_OSDInit(ulOSDWidth, ulOSDHeight,
                ulThumbWidth, ulThumbHeight,
                PRIMARY_DATESTAMP_WIDTH, PRIMARY_DATESTAMP_HEIGHT,
                THUMB_DATESTAMP_WIDTH, THUMB_DATESTAMP_HEIGHT,
                colorFormat, bMainBuffFull, ahcOSDRotateDraw);

}
#endif

#if (HDMI_ENABLE)
void InitOSD_HDMI(void)
{
    U32 colorFormat;
    AHC_OSD_ROTATE_DRAW_MODE ahcOSDRotateDraw;

    U32 ulOSDWidth, ulOSDHeight, ulThumbWidth, ulThumbHeight;
    AHC_BOOL bMainBuffFull;

    UINT16      uwHDMIWidth, uwHDMIHeight;
    //UINT16        uwHDMIOffX,  uwHDMIOffY;
    AHC_DISPLAY_HDMIOUTPUTMODE  HdmiMode;

    GUI_RegisterExternalFillRectCB((void *)AHC_OSD_ExternalFillRectCB);
    //bHaveInitOsdHdmi = AHC_TRUE;

#if (HDMI_PREVIEW_EN)
    ulOSDWidth = 320;
    ulOSDHeight = 240;
#else
    ulOSDWidth = 0;
    ulOSDHeight = 0;
#endif
    if (uiGetCurrentState() == UI_BROWSER_STATE)
    {
        AHC_GetHdmiDisplayWidthHeight(&uwHDMIWidth, &uwHDMIHeight);
        AHC_GetHDMIOutputMode(&HdmiMode);

        switch(HdmiMode)
        {
            case AHC_DISPLAY_HDMIOUTPUT_1920X1080P:
                ulThumbWidth    = uwHDMIWidth;
                ulThumbHeight   = uwHDMIHeight - POS_HDMI_1080I_BROWSER_OSD_H;// - POS_HDMI_1080I_BROWSER_OSD_H;
                break;

            case AHC_DISPLAY_HDMIOUTPUT_1920X1080I:
                ulThumbWidth    = uwHDMIWidth;
                ulThumbHeight   = (uwHDMIHeight<<1) - POS_HDMI_1080I_BROWSER_OSD_H;
                break;

            case AHC_DISPLAY_HDMIOUTPUT_1280X720P:
                ulThumbWidth    = uwHDMIWidth;
                ulThumbHeight   = uwHDMIHeight - POS_HDMI_720P_BROWSER_OSD_H;
                break;

            case AHC_DISPLAY_HDMIOUTPUT_640X480P:
            case AHC_DISPLAY_HDMIOUTPUT_720X480P:
            case AHC_DISPLAY_HDMIOUTPUT_720X576P:
            case AHC_DISPLAY_HDMIOUTPUT_1280X720P_50FPS:
            case AHC_DISPLAY_HDMIOUTPUT_1920X1080P_30FPS:
            default:
                printc("HDMIFunc_ChangeOSDStatus Error!\r\n");
                break;
        }
    }else{
        ulThumbWidth = 0;
        ulThumbHeight = 0;
    }

    bMainBuffFull = AHC_FALSE;

    //AHC_SetDisplayOutputDev(DISP_OUT_HDMI, AHC_DISPLAY_DUPLICATE_1X);
    colorFormat = WMSG_LAYER_WIN_COLOR_FMT;
    ahcOSDRotateDraw = OSD_ROTATE_DRAW_NONE;
    AHC_OSD_RegisterInitOSDCustomCB((void *)InitOSDCustom_Hdmi);

    AHC_OSDInit(ulOSDWidth, ulOSDHeight,
                ulThumbWidth, ulThumbHeight,
                PRIMARY_DATESTAMP_WIDTH, PRIMARY_DATESTAMP_HEIGHT,
                THUMB_DATESTAMP_WIDTH, THUMB_DATESTAMP_HEIGHT,
                colorFormat, bMainBuffFull, ahcOSDRotateDraw);
}
#endif

void InitOSD_LCD(void)
{
    U32 colorFormat;
    AHC_OSD_ROTATE_DRAW_MODE ahcOSDRotateDraw;
    U32 ulOSDWidth, ulOSDHeight, ulThumbWidth, ulThumbHeight;
    AHC_BOOL bMainBuffFull;
    MMP_ERR     err = MMP_ERR_NONE;

    ulOSDWidth = RTNA_LCD_GetAttr()->usPanelW / OSD_DISPLAY_SCALE_LCD;
    ulOSDHeight = RTNA_LCD_GetAttr()->usPanelH / OSD_DISPLAY_SCALE_LCD;

    GUI_RegisterExternalFillRectCB((void *)AHC_OSD_ExternalFillRectCB);

    ulThumbWidth = RTNA_LCD_GetAttr()->usPanelW;// / OSD_DISPLAY_SCALE_LCD;
    ulThumbHeight = RTNA_LCD_GetAttr()->usPanelH;// / OSD_DISPLAY_SCALE_LCD;
    bMainBuffFull = AHC_TRUE;

    //Force OSD format as RGB565 for saving memory and drawing time.
    colorFormat = OSD_COLOR_RGB565;
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
    ahcOSDRotateDraw = OSD_ROTATE_DRAW_NONE;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90)
    ahcOSDRotateDraw = OSD_ROTATE_DRAW_RIGHT_90;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
    ahcOSDRotateDraw = OSD_ROTATE_DRAW_RIGHT_270;
#endif
    AHC_OSD_RegisterInitOSDCustomCB((void *)InitOSDCustom_Lcd);

    if (OSD_DISPLAY_SCALE_LCD == 0) {
        AHC_PRINT_RET_ERROR(0,0);
        return;
    }

    AHC_OSDInit(ulOSDWidth,
                ulOSDHeight,
                ulThumbWidth,
                ulThumbHeight,
                PRIMARY_DATESTAMP_WIDTH,
                PRIMARY_DATESTAMP_HEIGHT,
                THUMB_DATESTAMP_WIDTH,
                THUMB_DATESTAMP_HEIGHT,
                colorFormat,
                bMainBuffFull,
                ahcOSDRotateDraw);
}

void InitOSD_None(void)
{
    GUI_RegisterExternalFillRectCB((void *)AHC_OSD_ExternalFillRectCB);
}

void InitOSD(void)
{
#if (TVOUT_ENABLE)//(TVOUT_PREVIEW_EN)
    if(AHC_IsTVConnectEx()){
        InitOSD_TVout();
    }
    else
#endif
#if (HDMI_ENABLE)//(HDMI_PREVIEW_EN)
    if(AHC_IsHdmiConnect()){
        InitOSD_HDMI();
    }
    else
#endif
    {
        InitOSD_LCD();
    }
}

#if (defined(SPEECH_RECOGNIZE_EN)&&(SPEECH_RECOGNIZE_EN))
void SpeechRecogRunCB(MMP_ULONG ID)
{
    printc("SpeechRecogCB=%X.\r\n",ID);
}
#endif

UINT8 AHC_WaitForSystemReady(void)
{
    UINT16 SemCount = 0;

    AHC_OS_QuerySem(ahc_System_Ready, &SemCount);

    return (0 == SemCount)?(0):(1);
}

MMP_UBYTE bDCFInitDone = 0; //Andy Liu. Remove it later...
void AHC_DCF_Init(void)
{
    AHC_AUDIO_I2S_CFG   ConfigAudioI2S;
    AHC_BOOL            bSD_inserted = AHC_FALSE;
    UINT32              nInVirAddr;
    UINT32              nMIMFInVirAddr;
    //dcfdt mem
    nInVirAddr = (UINT32)MsPA2VA(MsAllocateMem(0x80000));
    AIHC_SetTempDCFMemStartAddr(nInVirAddr);
    #if (MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_MULTI_DB_DECREASE)
    //MIMF mem
    nMIMFInVirAddr = (UINT32)MsPA2VA(MsAllocateMem(0x80000));
    AHC_MIMF_SetMIMFMemStartAddr(nMIMFInVirAddr);
    #endif
    #if (AHC_SHAREENC_SUPPORT)
    AHC_UF_RegisterCallback(AHC_UFCB_CREATE_FORMAT_FREE_FILE, (void *)AHC_UF_CreateShareFileCB);
    #endif

    if(MEDIA_SETTING_SD_CARD == MenuSettingConfig()->uiMediaSelect)
    {
        bSD_inserted = AHC_IsSDInserted();

        if(bSD_inserted){
            Enable_SD_Power(1 /* Power On */);
            AHC_SDMMC_SetState(SDMMC_IN);

            #if (FS_FORMAT_FREE_ENABLE)
            if( AHC_CheckMedia_FormatFree( AHC_MEDIA_MMC ) == AHC_FALSE )
            {
                SystemSettingConfig()->byNeedToFormatMediaAsFormatFree = 1;
            }
            else
            #endif
                AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect);
        }
        else{
            Enable_SD_Power(0 /* Power Off */);
            AHC_SDMMC_SetState(SDMMC_OUT);
        }
    }
    else
    {
        AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect);
    }

    ConfigAudioI2S.workingMode      = AHC_AUDIO_I2S_MASTER_MODE;
    ConfigAudioI2S.mclkMode         = AHC_AUDIO_I2S_256FS_MODE;
    ConfigAudioI2S.outputBitSize    = AHC_AUDIO_I2S_OUT_16BIT;
    ConfigAudioI2S.lrckPolarity     = AHC_AUDIO_I2S_LRCK_L_LOW;

    AHC_ConfigAudioExtDevice(&ConfigAudioI2S, 44100);

    //MIMF_CUSTOMIZED_SORT_TYPE use for customized sorting type, implement by AHC_MIMF.c
#if(MIMF_CUSTOMIZED_SORT_TYPE)
    AHC_MIMF_RegisterCusCallback();
#endif

    bDCFInitDone = 1;
}

#define SETREG16(addr, a)       ( (*(volatile u16 *)(addr)) |= a )
#define CLRREG16(addr, a)       ( (*(volatile u16 *)(addr)) &= ~a )
#define INREG16(addr)           (*(volatile u16 *)(addr))
#define mdelay(x)               MsOS_DelayTask(x)
#define BASE_REG_RIU_PA         0x1F000000
#define BK_REG(reg)             ((reg) << 2)
#define GET_BASE_ADDR_BY_BANK(x, y)         ((x) + ((y) << 1))
#define BASE_REG_PMSAR_PA       GET_BASE_ADDR_BY_BANK(BASE_REG_RIU_PA, 0x1400)
#define BASE_REG_PMSLEEP_PA     GET_BASE_ADDR_BY_BANK(BASE_REG_RIU_PA, 0x0E00)
#define REG_ID_00               BK_REG(0x00)
#define REG_ID_10               BK_REG(0x10)
#define REG_ID_19               BK_REG(0x19)
#define REG_ID_2F               BK_REG(0x2F)
#define REG_ID_46               BK_REG(0x46)
#define REG_ID_64               BK_REG(0x64)
unsigned char m_bChangeVol = 0;
extern MMPF_OS_MQID            MidTaskWork_QId;
void AHC_DVFS_Change(void)
{
    int temp = 0;
    CLRREG16(BASE_REG_PMSAR_PA + REG_ID_19, (1<<7)); //ch7 reference voltage select to 2.0V bit6 for I3
    CLRREG16(BASE_REG_PMSAR_PA + REG_ID_10, (1<<0)); //reg_pm_dmy
    SETREG16(BASE_REG_PMSLEEP_PA + REG_ID_64, (1<<10));
    SETREG16(BASE_REG_PMSLEEP_PA + REG_ID_2F, (1<<2));
    CLRREG16(BASE_REG_PMSAR_PA + REG_ID_00, (1<<4));
    SETREG16(BASE_REG_PMSAR_PA + REG_ID_00, (1<<5));
    SETREG16(BASE_REG_PMSAR_PA + REG_ID_00, (1<<9));
    CLRREG16(BASE_REG_PMSAR_PA + REG_ID_00, (1<<8));
    mdelay(1);
    CLRREG16(BASE_REG_PMSAR_PA + REG_ID_00, (1<<6));
    mdelay(1);
    SETREG16(BASE_REG_PMSAR_PA + REG_ID_00, (1<<14));
    temp = INREG16(BASE_REG_PMSAR_PA + REG_ID_46);
    temp = (1250 * (400 - temp) + 26000)/1000;
    AHC_DBG_MSG(0, "CPU Temp [%d]\r\n", temp);
    if (temp < 40) {
        if (m_bChangeVol) {
            m_bChangeVol = 0;
            *(volatile unsigned short *)(0x1F000000 + (0xF *0x200) + (0x8*4)) |= 2;
            *(volatile unsigned short *)(0x1F000000 + (0xF *0x200) + (0x8*4)) &= ~1;
        }
    }
    else if (temp >= 50) {
        if (m_bChangeVol == 0) {
            m_bChangeVol = 1;
            *(volatile unsigned short *)(0x1F000000 + (0xF *0x200) + (0x8*4)) &= ~2;
            *(volatile unsigned short *)(0x1F000000 + (0xF *0x200) + (0x8*4)) &= ~1;
        }
    }
    else {
    }
}
void AHC_DVFS_Timer_CB(void)
{
    MMPF_OS_PutMessage(MidTaskWork_QId, (void *)(AHC_DVFS_Change));
}
MMP_ERR AHC_DVFS_StartTimer(void)
{
    MsOsErr_e   ret = RTK_OK;
    MsTimerId_e eTimerID;
    ret = MsStartCbTimerMs(&eTimerID,
                                 AHC_DVFS_Timer_CB,
                                 0,
                                 300/*ms*/,
                                 300/*ms*/);
    if (ret != RTK_OK) {
        UartSendTrace("DVFS timer start fail\n");
        return MMP_SYSTEM_ERR_TIMER;
    }
    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : AhcTask
//  Description :
//------------------------------------------------------------------------------
void AhcTask(void *p_arg)
{
    extern  void AHC_Main_Task(void *p_arg);
    AHC_Main_Task(p_arg);
}

UINT32 m_u32CurMsgId = 0;
UINT32 m_u32CurMsgParam1 = 0;
UINT32 m_u32CurMsgParam2 = 0;

void AHC_Main_Task(void *p_arg)
{
    ahc_System_Ready = AHC_OS_CreateSem(1);

    SystemSettingInit();
    //Get gsensor interrupt status  must be run ahead of VBUS checking.
    //AHC_Main_Task has a higher boot priority than JobdispatchTask_init
    InitGsensorAhead();
    AHC_StartUSBDetect();

    //Note : MAC addres burn in must follow AHC_DCF_Init()
    #if(WIFI_PORT && SD_MAC_POWERON_BURNIN)
    if (SDUpdateBackupMAC(SD_MAC_FILENAME))
        SDUpdateBurnInMAC();
    #endif

    #if (SUPPORT_IR_CONVERTER)
    IRConverter_Initialize();
    // To Clear IR status of PowerOn Key avoid power off
    IRConverter_WriteCommand(IR_CONVERTER_CLEAR_POWERON, 0x01);
    #endif

    AHC_Initialize();
    AHC_WaitForBootComplete();

    #ifdef USB_LABLE_STRING
    AHC_SetUSBLable(USB_LABLE_STRING);
    #endif

    /* Update Menu Setting */
    uiCheckDefaultMenuExist();
    gAHC_UpdateMenuDone = AHC_TRUE;
    MenuSettingConfig()->uiMediaSelect = MEDIA_SETTING_SD_CARD;

    #if (AHC_DRAM_SIZE == COMMON_DRAM_SIZE_32MB)
    pf_FCWS_EnSet(FCWS_EN_OFF);
    pf_SAG_EnSet(SAG_EN_OFF);
    pf_HDR_EnSet(HDR_EN_OFF);
    MMP_SetVidHDRType(CAM_TYPE_PRM, CUS_SNR_HDR_DISABLE);
    #endif

    #if defined(SUPPORT_ONCHIP_IRDA)&&(SUPPORT_ONCHIP_IRDA)
    MMPS_IrDA_Initialize();
    MMPS_IrDA_SetIrEn(MMP_TRUE);
    #endif

    #if SNR_CLK_POWER_SAVING_SETTING
    pf_HDR_EnSet(COMMON_HDR_EN_OFF);
    #endif

    Menu_SetVolume(MenuSettingConfig()->uiVolume);
    AHC_SetMenuFlashLEDStatus(MenuSettingConfig()->uiLEDFlash);

    #if (TOUCH_UART_FUNC_EN)
    AHC_OS_SetFlags(UartCtrlFlag, Touch_Uart_FLAG_INITIAL, AHC_OS_FLAG_SET);
    #endif

    #ifdef CFG_TURN_OFF_POWER_LED_WHEN_BOOT_FINISH
    LedCtrl_PowerLed(AHC_FALSE);
    #else
    LedCtrl_PowerLed(AHC_TRUE);
    #endif

    #ifdef CFG_BOOT_FLASH_MODE //may be defined in config_xxx.h, could be FLASH_OFF or FLASH_ON
    // Always set Flash ON or OFF when system start up.
    #if CFG_BOOT_FLASH_MODE
        MenuSettingConfig()->uiFlashMode = FLASH_ON;
    #else
        MenuSettingConfig()->uiFlashMode = FLASH_OFF;
    #endif
    #endif

    #ifdef CFG_BOOT_MOV_CLIP_TIME //may be defined in config_xxx.h, could be MOVIE_CLIP_TIME_OFF or MOVIE_CLIP_TIME_xMIN
    MenuSettingConfig()->uiMOVClipTime   = CFG_BOOT_MOV_CLIP_TIME;
    #endif
    #ifdef CFG_BOOT_SLIDESHOW_FILE //may be defined in config_xxx.h, could be SLIDESHOW_FILE_STILL
    // Force slideshow photo only
    MenuSettingConfig()->uiSlideShowFile = SLIDESHOW_FILE_STILL;
    #endif
    #ifdef CFG_BOOT_CHECK_USB_KEY_FILE //may be defined in config_xxx.h, a file name such as "SD:\\aituvc.txt"
    // Check USB Key file to run PCCAM
    AHC_CheckUSB_KeyFile(CFG_BOOT_CHECK_USB_KEY_FILE, 1 /* 1 for PCCAM */);
    #endif
    #ifdef CFG_BOOT_LCD_ROTATE //may be defined in config_xxx.h, could be LCD_ROTATE_OFF
    // Init LCD direction, always is normal
    MenuSettingConfig()->uiLCDRotate = CFG_BOOT_LCD_ROTATE;
    #endif

    #if defined(WIFI_PORT) && (WIFI_PORT == 1)
    #if defined(CFG_BOOT_FORCE_TURN_OFF_WIFI)&&(CFG_BOOT_FORCE_TURN_OFF_WIFI) //    defined in config_xxx.h, for project of key control Wi-Fi On/Off
    Setpf_WiFi(WIFI_MODE_OFF);
    #endif
    #if defined(CFG_BOOT_FORCE_TURN_ON_WIFI)&&(CFG_BOOT_FORCE_TURN_ON_WIFI) //  defined in config_xxx.h, for project of key control Wi-Fi On/Off
    Setpf_WiFi(WIFI_MODE_ON);
    #endif
    #endif

    #ifdef CFG_VIDEO_FORMAT_SELECT_BY_SWITCH
    CFG_VIDEO_FORMAT_SELECT_BY_SWITCH();
    #endif
    #if(MENU_REARCAM_TYPE_EN)
    if(SCD_CAM_NONE != MMP_GetScdCamType()){
        pf_RearCamType_EnSet(USB_CAM_SONIX_MJPEG2H264 + MMP_GetScdCamType());
    }
    else {
        pf_RearCamType_EnSet(MMP_GetUSBCamType());
    }
    #endif

    uiStateSystemStart();

    #if (VR_VIDEO_TYPE == COMMON_VR_VIDEO_TYPE_3GP)
    AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_CLIP_CONTAINER_TYPE, AHC_MOVIE_CONTAINER_3GP);
    #elif (VR_VIDEO_TYPE == COMMON_VR_VIDEO_TYPE_AVI)
    AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_CLIP_CONTAINER_TYPE, AHC_MOVIE_CONTAINER_AVI);
    #elif (VR_VIDEO_TYPE == COMMON_VR_VIDEO_TYPE_TS)
    AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_CLIP_CONTAINER_TYPE, AHC_MOVIE_CONTAINER_TS);
    #endif

    #if defined(AIT_HW_WATCHDOG_ENABLE) && (AIT_HW_WATCHDOG_ENABLE)
    AHC_WD_Enable(AHC_TRUE);
    #endif

    AHC_DVFS_StartTimer();
    //RtkSetTaskMonitorMaxTimeout(RtkCurrentTask(),2*RTK_MAX_TASK_TIMEOUT_COUNT);
    RtkSetTaskMonitorMaxTimeout(RtkCurrentTask(),2*0xF000); //TL 2018_0627:For pause/resume -> Stress Test

    while(1) {

        UINT32 u32MsgId = 0, u32Param1 = 0, u32Param2 = 0;
        UINT16 u16Count = 0, u16HpCount = 0;

        while(1) {

            AHC_GetAHLMessageCount_HP(&u16HpCount);

            if (u16HpCount < AHC_HP_MSG_QUEUE_SIZE) {

                if (AHC_GetAHLMessage_HP(&u32MsgId, &u32Param1, &u32Param2) == AHC_FALSE) {

                    AHC_GetAHLMessageCount(&u16Count);

                    if (u16Count < AHC_MSG_QUEUE_SIZE) {
                        if (AHC_GetAHLMessage(&u32MsgId, &u32Param1, &u32Param2) == AHC_FALSE) {
                            AHC_OS_Sleep(AHC_AHL_MSGQ_TIMEOUT);
                            continue;
                        }
                        break;
                    }
                    else {
                        AHC_OS_Sleep(AHC_AHL_MSGQ_TIMEOUT);
                        continue;
                    }
                }
                break;
            }
            else {
                AHC_GetAHLMessageCount(&u16Count);

                if (u16Count < AHC_MSG_QUEUE_SIZE) {
                    if (AHC_GetAHLMessage(&u32MsgId, &u32Param1, &u32Param2) == AHC_FALSE) {
                        AHC_OS_Sleep(AHC_AHL_MSGQ_TIMEOUT);
                        continue;
                    }
                    break;
                }
                else {
                    AHC_OS_Sleep(AHC_AHL_MSGQ_TIMEOUT);
                    continue;
                }
            }
        }

        AHC_OS_AcquireSem(ahc_System_Ready, 0);

        m_u32CurMsgId       = u32MsgId;
        m_u32CurMsgParam1   = u32Param1;
        m_u32CurMsgParam2   = u32Param2;

        uiStateMachine(u32MsgId, u32Param1, u32Param2);

        AHC_OS_ReleaseSem(ahc_System_Ready);
    }
}

void AHC_RtcUpdate_Task_init(void *p_arg)
{
}

static u32 _GetTime(void)
{
    CamOsTimespec_t tTime;

    CamOsGetMonotonicTime(&tTime);

    return ((tTime.nSec*1000000+ tTime.nNanoSec/1000)/1000);
}

void AHC_RtcUpdate_Task(void *p_arg)
{
    #define WORK_STACK_WAIT_UINT       30   // ms
    #define MAX_MS                     DrvTimerGlobalTimerTick2Ms(HAL_OSTICK2_GET_TIMEOUTLENGTH())

    int u32OSTmrA = 0;
    int u32OSTmrB = 0;
    int u32OSTmrC = 0;
    int u32OSTmrDuration;
    AHC_BOOL bFirstSec = AHC_TRUE;

    AHC_RTC_TIME RTCTime1, RTCTime2;

    AHC_SetParam(PARAM_ID_USE_RTC, 1);
    AHC_RTC_UpdateTime();
    AHC_RTC_GetTime(&RTCTime1);
    u32OSTmrA = _GetTime();
    //printc("@\r\n");
    //printc("RTC_0: %d\r\n",RTCTime1.uwSecond);
    while (1)
    {
        if(bFirstSec == AHC_TRUE) {
            AHC_SetParam(PARAM_ID_USE_RTC, 1);
            AHC_RTC_UpdateTime();
            AHC_RTC_GetTime(&RTCTime2);
            u32OSTmrC = _GetTime();
            //printc("@\r\n");
            if(RTCTime2.uwSecond == RTCTime1.uwSecond) {
                u32OSTmrA = u32OSTmrC;
            }
            else {
                RTCTime1.uwSecond = RTCTime2.uwSecond;
                u32OSTmrB = u32OSTmrC;
                bFirstSec = AHC_FALSE;
                //printc("RTC_1: %d\r\n",RTCTime1.uwSecond);
            }
        }
        else {
            u32OSTmrC = _GetTime();

            if(u32OSTmrC > u32OSTmrB) {
                u32OSTmrDuration = u32OSTmrC - u32OSTmrB;
            }
            else {
                u32OSTmrDuration = MAX_MS - u32OSTmrB + u32OSTmrC;
            }

            if((u32OSTmrDuration) < (1000 - 2*WORK_STACK_WAIT_UINT)) {
                u32OSTmrA = u32OSTmrC;
            }
            else {
                AHC_RTC_UpdateTime();
                AHC_RTC_GetTime(&RTCTime2);
                u32OSTmrC = _GetTime();
                //printc("@\r\n");
                if(RTCTime2.uwSecond == RTCTime1.uwSecond) {
                    u32OSTmrA = u32OSTmrC;
                }
                else {
                    RTCTime1.uwSecond = RTCTime2.uwSecond;
                    u32OSTmrB = u32OSTmrC;
                    //printc("RTC_2: %d\r\n",RTCTime1.uwSecond);
                }
            }
        }

        AHC_OS_SleepMs(WORK_STACK_WAIT_UINT);
    }
}

void AHC_WorkJob_Task_init(void *p_arg)
{
    UartSendTrace("AHC_WorkJob_Task_init\n\r");
}

void AHC_WorkJob_Task(void *p_arg)
{
    static MMP_ULONG Count = 0;
#if (GPS_CONNECT_ENABLE)
    static MMP_ULONG ulGPSInfoRefreshCnt;
#endif

    while(1)
    {
        if (AHC_GetWaitIconState())
        {
            AHC_DrawWaitIcon();
        }

        if (AHC_WMSG_States())
        {
            Count++;
            if(AHC_WMSG_IsTimeOut(Count*100)) {
                Count = 0;
            }
        }

#if (GPS_CONNECT_ENABLE)
        if( uiGetCurrentState() >= UI_CAMERA_MENU_STATE    &&
            uiGetCurrentState() <= UI_CLOCK_SETTING_STATE)
        {
            ulGPSInfoRefreshCnt++;
            if(ulGPSInfoRefreshCnt == 10)
            {
                ulGPSInfoRefreshCnt = 0;
                AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_UPDATE_MESSAGE, 0);
            }
        }
#endif

#if defined(AIT_HW_WATCHDOG_ENABLE) && (AIT_HW_WATCHDOG_ENABLE)
        AHC_WD_Kick();
#endif

    #if (defined(CUS_ADAS_OUTPUT_LOG) && ADAS_OUTPUT_LOG == 1)
    {
            extern MMP_BOOL FlagSetWrAdasLog;
            extern void ADAS_write_log(void);
            if (FlagSetWrAdasLog)
            {
                FlagSetWrAdasLog = MMP_FALSE;
                ADAS_write_log();
            }
    }
    #endif
        AHC_OS_SleepMs(100);
    }
}

void AHC_UARTLogTxTask_Task_init(void *p_arg)
{
    UartSendTrace("AHC_UARTLogTxTask_Task_init\n\r");
}

void AHC_UARTLogTx_Task(void *p_arg)
{
#if defined(__RTK_OS__)
    u32 nSize = 4096 * 2;
    void* ppUserPtr = 0;
    u64 MiuAddr = 0;
    u64 lpPhysAddr = 0;
    CamOsRet_e camret = CAM_OS_OK;

    camret = CamOsDirectMemAlloc("UART",nSize, &ppUserPtr, &MiuAddr, &lpPhysAddr);
    if(camret != CAM_OS_OK) { UartSendTrace("[%s,%d] failed.\n",__FUNCTION__, __LINE__); return;}

    send_msg_set_buffer_mode((unsigned int)lpPhysAddr, nSize);
    send_msg_buffer_mode_en(1);

    while(1){
        while((send_msg_get_data_size() > 0) /*&& (iuart_cnt++ < 10)*/){
            send_msg_trigger();
        }

        AHC_OS_SleepMs(1);
    }

    camret = CamOsDirectMemRelease(ppUserPtr, nSize);
    if(camret != CAM_OS_OK) { UartSendTrace("[%s,%d] failed.\n",__FUNCTION__, __LINE__); return;}
#endif
}

#if 0
void ________Uart_Function_________(){ruturn;} //dummy
#endif

void UartCmdSetMode( char* szParam )
{
    int iMode;

    sscanfl( szParam, "%x",&iMode);

    if( iMode == 0xFF )
    {
        printc("AHC_MODE_IDLE = 0x00,              \n");
        printc("AHC_MODE_CAPTURE_PREVIEW = 0x10,   \n");
        printc("AHC_MODE_STILL_CAPTURE = 0x20,     \n");
        printc("AHC_MODE_USB_MASS_STORAGE = 0x30,  \n");
        printc("AHC_MODE_USB_WEBCAM = 0x31,        \n");
        printc("AHC_MODE_PLAYBACK  = 0x40,         \n");
        printc("AHC_MODE_THUMB_BROWSER = 0x50,     \n");
        printc("AHC_MODE_VIDEO_RECORD = 0x60,      \n");
        printc("AHC_MODE_RECORD_PREVIEW = 0x62,    \n");
        printc("AHC_MODE_CALIBRATION = 0xF0,       \n");
        printc("AHC_MODE_MAX = 0xFF                \n");
    }
    else
    {
        AHC_SetMode( iMode );
    }
}

void UartCmdSetUiMode( char* szParam )
{
    int uiMode;

    sscanfl( szParam, "%x",&uiMode);

    if( uiMode == 0xFF )
    {
        printc("UI_CAMERA_STATE         = 0x00, \n");
        printc("UI_VIDEO_STATE          = 0x01, \n");
        printc("UI_BROWSER_STATE        = 0x02, \n");
        printc("UI_PLAYBACK_STATE       = 0x03, \n");
        printc("UI_SLIDESHOW_STATE      = 0x04, \n");
        printc("UI_MSDC_STATE           = 0x05, \n");
        printc("UI_CAMERA_MENU_STATE    = 0x08, \n");
        printc("UI_VIDEO_MENU_STATE     = 0x09, \n");
        printc("UI_PLAYBACK_MENU_STATE  = 0x0A, \n");
    }
    else
    {
        StateSwitchMode( uiMode );
    }
}

UARTCOMMAND sAhcUartCommand[] =
{
    { "mode",          " Mode ",           "AHC_SetMode",               UartCmdSetMode },
    { "uimode",        " uiMode ",         "UI_SetMode",                UartCmdSetUiMode },
    {0,0,0,0}
};

AHC_BOOL MenuFunc_CheckAvailableSpace( UINT8 uiCameraState )
{
    AHC_BOOL bIsAvailableSpace = AHC_TRUE;

    switch( uiCameraState )
    {
    case UI_VIDEO_STATE:
        {
            UBYTE bHour = 0, bMin = 0, bSec = 0;

            AHC_VIDEO_AvailableRecTimeEx(0, &bHour, &bMin, &bSec);

            if ((bHour + bMin + bSec) == 0)
            {
                bIsAvailableSpace = AHC_FALSE;
            }
        }
        break;

    case UI_CAMERA_BURST_STATE:
        /*
        // TBD
        if( CameraSettingConfig()->uiRemainingShots < CaptureBurstFunc_GetShotNumber( MenuSettingConfig()->uiBurstShot ) )
        {
            bIsAvailableSpace = AHC_FALSE;
        }
        */
        break;

    default:
        {
            UINT64 freeBytes = 0;
            UINT32 remainCaptureNum = 0;

            CaptureFunc_CheckMemSizeAvailable(&freeBytes, &remainCaptureNum);

            if (remainCaptureNum)
            {
                bIsAvailableSpace = AHC_FALSE;
            }
        }
        break;
    }

    return bIsAvailableSpace;
}
