//==============================================================================
//
//  File        : AHC_poweroff.c
//  Description : AHC power off function
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_poweroff.h"
#include "Customer_config.h"
#include "ahc_media.h"
#include "ahc_warningmsg.h"
#include "mmpd_system.h"
#include "ahc_display.h"

/*===========================================================================
 * Extern varible
 *===========================================================================*/

extern AHC_BOOL gbBlockRealIDUIKeyTask;

/*===========================================================================
 * Main body
 *===========================================================================*/

#if 0
void ____PowerOff_Function_____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_PowerOff_Preprocess
//  Description : Store FW/User settings before power off
//------------------------------------------------------------------------------
void AHC_PowerOff_Preprocess(void)
{
    Menu_WriteSetting();
    AHC_OS_SleepMs(10);

#if (POWER_OFF_PREPROCESS_EN)
    AHC_SetMode(AHC_MODE_IDLE);
    AHC_OS_SleepMs(10);

    AHC_VIDEO_WaitVideoWriteFileFinish();

    AHC_UnloadSystemFile();

    #if (!DEBUG_UART_TO_FILE) && (!DEBUG_UART_TO_SD)
    AHC_UnmountVolume(AHC_MEDIA_MMC);
    #endif

    AHC_OS_SleepMs(10);
#endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_PowerOff_VirtualPath
//  Description :
//------------------------------------------------------------------------------
void AHC_PowerOff_VirtualPath(void)
{
#if (SUPPORT_VIRTUAL_POWER_OFF)

    #if (SUPPORT_IR_CONVERTER)
    AHC_IR_WriteRegister(IR_CONVERTER_CLEAR_POWERON, 0x01);
    #endif

    if (uiGetCurrentState() == UI_VIRTUAL_POWER_SAVE_STATE) {
        printc("VPS -> Power Off\r\n");
    }
    else {
        if (AHC_IsUsbConnect()) {
            printc("Go -> VPS\r\n");
            #if (ENABLE_POWER_OFF_PICTURE)
            uiPowerOffPicture();
            #endif
            StateSwitchMode(UI_VIRTUAL_POWER_SAVE_STATE);
            return;
        }
    }

    AHC_PowerOff_Preprocess();

    if (uiGetCurrentState() == UI_VIRTUAL_POWER_SAVE_STATE) {
        // NOP
    }
    else {
        #if (ENABLE_POWER_OFF_PICTURE)
        uiPowerOffPicture();
        #endif
    }

    LedCtrl_LcdBackLight(AHC_FALSE);
    AHC_PMU_PowerOff();
#endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_PowerOff_NormalPath
//  Description :
//------------------------------------------------------------------------------
void AHC_PowerOff_NormalPath(void)
{
    #if (defined(DEVICE_GPIO_2NDSD_PLUG))
    #if (TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_MASTER_SLAVE)
    MenuSettingConfig()->uiMediaSelect = MEDIA_SETTING_SD_CARD;
    #endif
    #endif

    #if (SUPPORT_IR_CONVERTER)
    //AHC_IR_WriteRegister(IR_CONVERTER_CLEAR_POWERON, 0x01);//TBD
    #endif

    gbBlockRealIDUIKeyTask = AHC_TRUE;

    AHC_PowerOff_Preprocess();

    #ifndef CFG_POWEROFF_WITHOUT_CLEAR_WMSG
    AHC_WMSG_Draw(AHC_FALSE, WMSG_NONE, 0); // Clear WMSG
    #endif

    #if(ENABLE_POWER_OFF_PICTURE)
    uiPowerOffPicture();
    #endif

    AHC_PMU_PowerOff();

    gbBlockRealIDUIKeyTask = AHC_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_PowerOff_NormalPathEx
//  Description :
//------------------------------------------------------------------------------
void AHC_PowerOff_NormalPathEx(AHC_BOOL bForce, AHC_BOOL bByebye, AHC_BOOL bSound)
{
    extern void AHC_PMU_PowerOffEx(AHC_BOOL bSound);

    if (bForce == AHC_TRUE)
    {
        AHC_PowerOff_Preprocess();

        if (bByebye == AHC_TRUE) {
            uiPowerOffPicture();
        }
        AHC_PMU_PowerOffEx(bSound);
    }
    else {
        #if (POWER_OFF_CONFIRM_PAGE_EN)
        PowerOff_InProcess  = AHC_TRUE;
        PowerOff_Option     = CONFIRM_NOT_YET;

        if (PowerOff_Option == CONFIRM_NOT_YET) {
            MenuDrawSubPage_PowerOff(NULL);
        }
        #endif
    }
}

#if (POWER_OFF_CONFIRM_PAGE_EN)
//------------------------------------------------------------------------------
//  Function    : AHC_PowerOff_ResetVarible
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_PowerOff_ResetVarible(void)
{
    PowerOff_InProcess  = AHC_FALSE;
    PowerOff_Option     = CONFIRM_NOT_YET;
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_PowerOff_Confirmed
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_PowerOff_Confirmed(void)
{
    /*
     * Turn off backlight, to avoid user see preview before goodbye screen.
     */
    LedCtrl_LcdBackLight(AHC_FALSE);

    AHC_PowerOff_ResetVarible();

    AHC_OSDSetColor(0 /*OSD_COLOR_TRANSPARENT*/);
    AHC_OSDDrawFillRect(0 /*MAIN_DISPLAY_BUFFER*/, 0, 0 , 320, 240);

    AHC_PowerOff_Preprocess();

    uiPowerOffPicture();
    AHC_PMU_PowerOff();

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_PowerOff_Cancel
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_PowerOff_Cancel(void)
{
    AHC_PowerOff_ResetVarible();

    if (uiGetCurrentState() == UI_TVOUT_STATE)
    {
        #if (TVOUT_ENABLE)
        MenuDrawSubPage_PowerOffCancel_TV();
        #endif
        return AHC_TRUE;
    }
    else if (uiGetCurrentState() == UI_HDMI_STATE)
    {
        #if (HDMI_ENABLE)
        MenuDrawSubPage_PowerOffCancel_HDMI();
        #endif
        return AHC_TRUE;
    }
    else if (uiGetCurrentState() == UI_PLAYBACK_STATE)
    {
        extern AHC_BOOL gbEnterPowerOffPagePause;

        if (GetMovConfig()->iState == MOV_STATE_PAUSE && gbEnterPowerOffPagePause == AHC_TRUE)
        {
            MovPlayback_Resume();
            gbEnterPowerOffPagePause = AHC_FALSE;
        }
    }

    AHC_OSDSetColor(0 /*OSD_COLOR_TRANSPARENT*/);
    AHC_OSDDrawFillRect(0 /*MAIN_DISPLAY_BUFFER*/, 0, 0 , m_OSD[0]->width, m_OSD[0]->height);

    #ifdef FLM_GPIO_NUM
    AHC_OSDRefresh_PLCD();
    #endif

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_PowerOff_Option
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_PowerOff_Option(AHC_BOOL op)
{
    if (op == CONFIRM_OPT_YES)
        AHC_PowerOff_Confirmed();
    else if(op == CONFIRM_OPT_NO)
        AHC_PowerOff_Cancel();

    return AHC_TRUE;
}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_PowerOff_ShowPicture
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_PowerOff_ShowPicture(INT8 *charStr)
{
    MMP_DSC_JPEG_INFO           stJpegInfo;
    MMP_DISPLAY_OUTPUT_SEL      displaypanel;
    MMP_ERR                     err;
    UINT16                      ImgW;
    UINT16                      ImgH;
    UINT16                      OSDWidth, OSDHeight, OSDColor,usTmpW,usTmpH;
    UINT32                      OSDAddr;

    #if (FS_INPUT_ENCODE == UCS2)
    uniStrcpy(stJpegInfo.bJpegFileName, charStr);
    stJpegInfo.usJpegFileNameLength = uniStrlen((short *)charStr);
    #elif (FS_INPUT_ENCODE == UTF8)
    STRCPY(stJpegInfo.bJpegFileName, charStr);
    stJpegInfo.usJpegFileNameLength = STRLEN(charStr);
    #endif

    stJpegInfo.ulJpegBufAddr        = 0;
    stJpegInfo.ulJpegBufSize        = 0;
    stJpegInfo.bDecodeThumbnail     = MMP_FALSE;
    #if (DSC_SUPPORT_BASELINE_MP_FILE)
    stJpegInfo.bDecodeLargeThumb    = MMP_FALSE;
    #endif
    stJpegInfo.bValid               = MMP_FALSE;
    stJpegInfo.bPowerOffLogo        = MMP_TRUE;
    stJpegInfo.bReEncodeThumb       = MMP_FALSE;

    MMPS_Display_SetOutputPanel(MMP_DISPLAY_PRM_CTL, MMP_DISPLAY_SEL_MAIN_LCD);
    MMPS_Display_SetWinActive(OSD_LAYER_WINDOW_ID, MMP_FALSE);
    MMPS_Display_GetOutputPanel(MMP_DISPLAY_PRM_CTL, &displaypanel);

    if (displaypanel == MMP_DISPLAY_SEL_MAIN_LCD)
    {
        AHC_Display_GetWidthHdight(&ImgW, &ImgH);

        AIHC_DrawReservedOSD(MMP_TRUE);

        AHC_OSDGetBufferAttr(32, &OSDWidth, &OSDHeight, &OSDColor, &OSDAddr);

        #if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
        AHC_SetDisplayWindow(DISPLAY_SYSMODE_STILLPLAYBACK, AHC_TRUE, AHC_FALSE, 0, 0, ImgW, ImgH);
        #elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
        AHC_SetDisplayWindow(DISPLAY_SYSMODE_STILLPLAYBACK, AHC_TRUE, AHC_FALSE, 0, 0, ImgH, ImgW);
        #endif

        err = MMPS_DSC_PlaybackJpeg(&stJpegInfo, 0, 0);

        //MMPS_DSC_ExitJpegPlayback(); // Move to PMUCtrl_Power_Off

        AIHC_DrawReservedOSD(MMP_FALSE);
    }
    else {
        printc("TODO:AHC_PowerOff_ShowPicture...\r\n");
    }

    return AHC_TRUE;
}
