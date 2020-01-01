//==============================================================================
//
//  File        : ahc_modectl.c
//  Description : AHC message queue function
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_modectl.h"
#include "AHC_Config_SDK.h"
#include "snr_cfg.h"
#include "ahc_video.h"
#include "ahc_usb.h"
#include "ahc_sensor.h"
#include "ahc_stream.h"
#include "ahc_gui.h"
#include "ahc_parameter.h"
#include "ahc_msgqueue.h"
#include "ahc_utility.h"
#include "ahc_version.h"
#include "mmps_system.h"
#include "mmps_audio.h"
#include "mmp_vidplay_inc.h"
#include "component_cfg.h"
#include "ahc_video.h"

/*===========================================================================
 * Macro Define
 *===========================================================================*/

#define AHC_MODE_NUM (20)

/*===========================================================================
 * Global varible
 *===========================================================================*/

static AHC_MODE_DESCP m_stAhcModeDescp[AHC_MODE_NUM] =
{
    {AHC_MODE_IDLE,                     "IDLE"},
    {AHC_MODE_CAPTURE_PREVIEW,          "DSC_PREVW"},
    {AHC_MODE_STILL_CAPTURE,            "SINGLE_SHOT"},
    {AHC_MODE_CONTINUOUS_CAPTURE,       "CONTI_SHOT"},
    {AHC_MODE_LONGTIME_FIRST_CAPTURE,   "LT_1ST_SHOT"},
    {AHC_MODE_LONGTIME_NEXT_CAPTURE,    "LT_2ND_SHOT"},
    {AHC_MODE_LONGTIME_LAST_CAPTURE,    "LT_FINAL_SHOT"},
    {AHC_MODE_USB_MASS_STORAGE,         "MSDC"},
    {AHC_MODE_USB_WEBCAM,               "PCAM"},
    {AHC_MODE_PLAYBACK,                 "PLAY"},
    {AHC_MODE_THUMB_BROWSER,            "BROWSER"},
    {AHC_MODE_VIDEO_RECORD,             "VID_REC"},
    {AHC_MODE_RECORD_PREVIEW,           "VID_PREVIEW"},
    {AHC_MODE_RECORD_PRERECD,           "VID_PRE_ENC"},
    {AHC_MODE_RAW_PREVIEW,              "RAW_PREVW"},
    {AHC_MODE_RAW_CAPTURE,              "RAW_SHOT"},
    {AHC_MODE_NET_PLAYBACK,             "NET_PLAY"},
    {AHC_MODE_CALIBRATION,              "CALIBRATE"},
    {AHC_MODE__NO_CHANGE,               "NO_CHANGE"},
};

static UINT8                    m_bAHCGeneralInit       = 0;
MMP_ULONG                       glAhcBootComplete       = AHC_FALSE;
static AHC_MODE_ID              m_AhcSystemMode         = AHC_MODE_IDLE;
AHC_OS_SEMID                    m_AhcModeSemID = 0xFF;
BOOT_UP_SRC                     gbBootUpStatus = PWR_ON_BY_KEY|PWR_ON_BY_VBUS|PWR_ON_BY_DC;

/*===========================================================================
 * Extern variable
 *===========================================================================*/

extern AHC_BOOL                 gbAhcDbgBrk;

/*===========================================================================
 * Main body
 *===========================================================================*/

#if 0
void _____UI_Mode_Function_________(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_SetBootingSrc
//  Description :
//------------------------------------------------------------------------------
UINT8 AHC_SetBootingSrc(BOOT_UP_SRC bBootupFlag)
{
    gbBootUpStatus |= bBootupFlag;

    return gbBootUpStatus;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetBootingSrc
//  Description :
//------------------------------------------------------------------------------
BOOT_UP_SRC AHC_GetBootingSrc(void)
{
//  PWR_ON_BY_KEY       0x01
//  PWR_ON_BY_VBUS      0x02
//  PWR_ON_BY_GSENSOR   0x04
//  PWR_ON_BY_IR        0x08
//  PWR_ON_BY_DC        0x10
    return gbBootUpStatus;
}

//------------------------------------------------------------------------------
//  Function    : AHC_WaitForBootComplete
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_WaitForBootComplete(void)
{
    while ((glAhcBootComplete != AHC_TRUE) && (MMPS_System_GetBootStatus() != AHC_TRUE)) {
        AHC_OS_Sleep(100);
    }

    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_Initialize
//  Description :
//------------------------------------------------------------------------------
/**
@brief The intialize code that should be called once after system power-up

 The intialize code that should be called once after system power-up
 Parameters:
 @retval TRUE or FALSE. // TRUE: Success, FALSE: Fail
*/
AHC_BOOL AHC_Initialize(void)
{
    if (!m_bAHCGeneralInit)
    {
        AHC_PrintBuildTime();
        AHC_PrintFwVersion();

        AIHC_PARAM_Initialize();

        AIHC_InitMsgQueue();
        AIHC_InitAHLMessage();
        AIHC_InitAHLMessage_HP();

        AHC_WMSG_Config();

        MMPS_VIDPLAY_InitConfig(MMPS_VIDPLAY_GetConfig());

        m_bAHCGeneralInit = AHC_TRUE;
    }

    // Note: Please keep below function call to make sure functions in AHC_Callback.c can work
    AHC_CheckCallbackExisted();

    #if (FS_FORMAT_FREE_ENABLE)
    MMPS_FORMATFREE_Enable(1);
    #endif

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetMode_IDLE
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetMode_IDLE(AHC_MODE_ID uiMode)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    LOCK_AHC_MODE();

    if (uiMode == AHC_MODE_CAPTURE_PREVIEW) {
        AHC_Capture_SetPreviewMode(AHC_FALSE, AHC_FALSE);
        AHC_SetAhcSysMode(AHC_MODE_CAPTURE_PREVIEW);
    }
    else if (uiMode == AHC_MODE_USB_MASS_STORAGE) {
        ahcRet = AHC_SetUsbMode(AHC_USB_MODE_MASS_STORAGE);
        if(ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, 0); UNLOCK_AHC_MODE(); return ahcRet;}

        AHC_SetAhcSysMode(uiMode);
    }
    #if(SUPPORT_UVC_FUNC)
    else if (uiMode == AHC_MODE_USB_WEBCAM) {
        //AHC_SNR_PresetPrmSnrMode(AHC_SENSOR_MODE_FULL_HD_30P_RESOLUTION); //Temporary pass this value to prevent infinite loop.
        //pcam_usb_CustomedPreviewAttr(MMP_TRUE, AHC_SNR_GetPresetPrmSnrMode());

        ahcRet = AHC_SetUsbMode(AHC_USB_MODE_WEBCAM);
        if(ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, 0); UNLOCK_AHC_MODE(); return ahcRet;}

        AHC_SetAhcSysMode(uiMode);
    }
    #endif
    else if (uiMode == AHC_MODE_PLAYBACK) {
        ahcRet = AIHC_SetPlaybackMode();
        if(ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, 0); UNLOCK_AHC_MODE(); return ahcRet;}

        AHC_SetAhcSysMode(uiMode);
    }
    else if (uiMode == AHC_MODE_THUMB_BROWSER) {
        MMPS_Display_SetWinActive(LOWER_IMAGE_WINDOW_ID, MMP_FALSE);
        AHC_Thumb_DrawPage(AHC_TRUE);
        AHC_SetAhcSysMode(uiMode);
    }
    else if (uiMode == AHC_MODE_RECORD_PREVIEW) {

        ahcRet = AHC_VIDEO_SetRecordMode(AHC_VIDRECD_INIT);
        if (ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, 0); UNLOCK_AHC_MODE(); return ahcRet;}

        AHC_SetAhcSysMode(uiMode);
    }
    else if (uiMode == AHC_MODE_RAW_PREVIEW) {
        AHC_Capture_SetPreviewMode(AHC_TRUE, AHC_FALSE);
        AHC_SetAhcSysMode(uiMode);
    }
    else if (uiMode == AHC_MODE_NET_PLAYBACK) {
        AHC_SetAhcSysMode(uiMode);
    }
    else {
        AHC_DBG_ERR(1, "[%s] NewMode [%d]\r\n", __FUNCTION__, uiMode);
        UNLOCK_AHC_MODE();
        return AHC_FALSE;
    }

    UNLOCK_AHC_MODE();

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetMode_CAPTURE_PREVIEW
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetMode_CAPTURE_PREVIEW(AHC_MODE_ID uiMode)
{
    AHC_BOOL    ahcRet = AHC_TRUE;
    MMP_ERR     err = MMP_ERR_NONE;

    LOCK_AHC_MODE();

    if (uiMode == AHC_MODE_IDLE) {

        #if (defined(WIFI_PORT) && WIFI_PORT == 1)
        if (AHC_GetStreamingMode() != AHC_STREAM_OFF) {
            UNLOCK_AHC_MODE();//Must be unlock here,Because of the Semp is to be used in AHC_SetStreamingMode.
            AHC_SetStreamingMode(AHC_STREAM_OFF);
            LOCK_AHC_MODE();
        }
        #endif

        AHC_Capture_StopPreview();
        AHC_SetAhcSysMode(AHC_MODE_IDLE);
    }
    else if (uiMode == AHC_MODE_STILL_CAPTURE) {

        if (AHC_Capture_StartTakeJpeg(uiMode) == AHC_TRUE) {

            AHC_SetAhcSysMode(uiMode);

            #if defined(CCIR656_OUTPUT_ENABLE) && (CCIR656_OUTPUT_ENABLE)
            MMPS_DSC_EnablePreviewDisplay(gsAhcPrmSensor, MMP_FALSE, MMP_TRUE);
            #endif

            UNLOCK_AHC_MODE();

            err = AHC_SetMode(AHC_MODE_CAPTURE_PREVIEW);

            LOCK_AHC_MODE();

            if (err == AHC_FALSE) {
                UNLOCK_AHC_MODE();
                return AHC_FALSE;
            }
        }
        else {
            DBG_AutoTestPrint(ATEST_ACT_CAPTURE_0x0005, ATEST_STS_END_0x0003, 0, AHC_TRUE, gbAhcDbgBrk);
        }
    }
    else if (uiMode == AHC_MODE_LONGTIME_FIRST_CAPTURE) {
        if (AHC_Capture_StartTakeJpeg(uiMode) == AHC_TRUE) {
            AHC_SetAhcSysMode(uiMode);
        }
        else {
            DBG_AutoTestPrint(ATEST_ACT_CAPTURE_0x0005, ATEST_STS_END_0x0003, 0, AHC_TRUE, gbAhcDbgBrk);
        }
    }
    else if (uiMode == AHC_MODE_CONTINUOUS_CAPTURE) {
        if (AHC_Capture_StartTakeJpeg(uiMode) == AHC_TRUE) {
            AHC_SetAhcSysMode(uiMode);
        }
        else {
            DBG_AutoTestPrint(ATEST_ACT_CAPTURE_0x0005, ATEST_STS_END_0x0003, 0, AHC_TRUE, gbAhcDbgBrk);
        }
    }
    else {
        AHC_DBG_ERR(1, "[%s] NewMode [%d]\r\n", __FUNCTION__, uiMode);
        UNLOCK_AHC_MODE();
        return AHC_FALSE;
    }

    UNLOCK_AHC_MODE();
    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetMode_STILL_CAPTURE
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetMode_STILL_CAPTURE(AHC_MODE_ID uiMode)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    LOCK_AHC_MODE();

    if (uiMode == AHC_MODE_CAPTURE_PREVIEW) {
        AHC_Capture_SetPreviewMode(AHC_FALSE, AHC_TRUE);
        AHC_SetAhcSysMode(AHC_MODE_CAPTURE_PREVIEW);
    }
    else {
        AHC_DBG_ERR(1, "[%s] NewMode [%d]\r\n", __FUNCTION__, uiMode);
        UNLOCK_AHC_MODE();
        return AHC_FALSE;
    }

    UNLOCK_AHC_MODE();
    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetMode_C2C_CAPTURE
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetMode_C2C_CAPTURE(AHC_MODE_ID uiMode)
{
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetMode_LONG_TIME_CONTINUOUS_FIRST_CAPTURE
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetMode_LONG_TIME_CONTINUOUS_FIRST_CAPTURE(AHC_MODE_ID uiMode)
{
    AHC_BOOL    ahcRet = AHC_TRUE;
    MMP_ERR     err;

    LOCK_AHC_MODE();

    if (uiMode == AHC_MODE_LONGTIME_NEXT_CAPTURE) {
        if (AHC_Capture_StartTakeJpeg(uiMode) == AHC_TRUE) {
            AHC_SetAhcSysMode(AHC_MODE_LONGTIME_FIRST_CAPTURE);
        }
        else {
            DBG_AutoTestPrint(ATEST_ACT_CAPTURE_0x0005, ATEST_STS_END_0x0003, 0, AHC_TRUE, gbAhcDbgBrk);
        }
    }
    else if (uiMode == AHC_MODE_LONGTIME_LAST_CAPTURE) {
        if (AHC_Capture_StartTakeJpeg(AHC_MODE_LONGTIME_NEXT_CAPTURE) == AHC_TRUE ) {

            AHC_SetAhcSysMode(AHC_MODE_LONGTIME_LAST_CAPTURE);

            UNLOCK_AHC_MODE();
            err = AHC_SetMode(AHC_MODE_CAPTURE_PREVIEW);
            LOCK_AHC_MODE();

            if (err == AHC_FALSE) {
                UNLOCK_AHC_MODE();
                return AHC_FALSE;
            }
        }
    }
    else {
        AHC_DBG_ERR(1, "[%s] NewMode [%d]\r\n", __FUNCTION__, uiMode);
    }

    UNLOCK_AHC_MODE();
    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetMode_LONG_TIME_CONTINUOUS_NEXT_CAPTURE
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetMode_LONG_TIME_CONTINUOUS_NEXT_CAPTURE(AHC_MODE_ID uiMode)
{
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetMode_LONG_TIME_CONTINUOUS_LAST_CAPTURE
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetMode_LONG_TIME_CONTINUOUS_LAST_CAPTURE(AHC_MODE_ID uiMode)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    LOCK_AHC_MODE();

    if (uiMode == AHC_MODE_CAPTURE_PREVIEW) {
        AHC_Capture_SetPreviewMode(AHC_FALSE, AHC_TRUE);
        AHC_SetAhcSysMode(AHC_MODE_CAPTURE_PREVIEW);
    }
    else {
        AHC_DBG_ERR(1, "[%s] NewMode [%d]\r\n", __FUNCTION__, uiMode);
        UNLOCK_AHC_MODE();
        return AHC_FALSE;
    }

    UNLOCK_AHC_MODE();
    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetMode_CONTINUOUS_CAPTURE
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetMode_CONTINUOUS_CAPTURE(AHC_MODE_ID uiMode)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    LOCK_AHC_MODE();

    if (uiMode == AHC_MODE_CAPTURE_PREVIEW) {
        AHC_Capture_SetPreviewMode(AHC_FALSE, AHC_TRUE);
        AHC_SetAhcSysMode(uiMode);
    }
    else {
        AHC_DBG_ERR(1, "[%s] NewMode [%d]\r\n", __FUNCTION__, uiMode);
        UNLOCK_AHC_MODE();
        return AHC_FALSE;
    }

    UNLOCK_AHC_MODE();
    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetMode_USB_MASS_STORAGE
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetMode_USB_MASS_STORAGE(AHC_MODE_ID uiMode)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    LOCK_AHC_MODE();

    if (uiMode == AHC_MODE_IDLE) {
        AHC_USB_DisConnectDevice();
        AHC_SetAhcSysMode(AHC_MODE_IDLE);
    }
    else {
        AHC_DBG_ERR(1, "[%s] NewMode [%d]\r\n", __FUNCTION__, uiMode);
        UNLOCK_AHC_MODE();
        return AHC_FALSE;
    }

    UNLOCK_AHC_MODE();
    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetMode_USB_WEBCAM
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetMode_USB_WEBCAM(AHC_MODE_ID uiMode)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    LOCK_AHC_MODE();

    if (uiMode == AHC_MODE_IDLE) {
        AHC_USB_DisConnectDevice();
        AHC_UVC_CloseStreaming(PRM_SENSOR);
        AHC_SetAhcSysMode(AHC_MODE_IDLE);
    }
    else {
        AHC_DBG_ERR(1, "[%s] NewMode [%d]\r\n", __FUNCTION__, uiMode);
        UNLOCK_AHC_MODE();
        return AHC_FALSE;
    }

    UNLOCK_AHC_MODE();
    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetMode_PLAYBACK
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetMode_PLAYBACK(AHC_MODE_ID uiMode)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    LOCK_AHC_MODE();

    if (uiMode == AHC_MODE_IDLE) {
        AIHC_StopPlaybackMode();
        AHC_SetAhcSysMode(AHC_MODE_IDLE);
    }
    else if (uiMode == AHC_MODE_PLAYBACK) { // CHECK : The mode is the same.
        AIHC_StopPlaybackMode();

        if (AIHC_SetPlaybackMode() == AHC_FALSE) {
            UNLOCK_AHC_MODE();
            return AHC_FALSE;
        }
    }
    else {
        AHC_DBG_ERR(1, "[%s] NewMode [%d]\r\n", __FUNCTION__, uiMode);
        UNLOCK_AHC_MODE();
        return AHC_FALSE;
    }

    UNLOCK_AHC_MODE();
    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetMode_THUMB_BROWSER
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetMode_THUMB_BROWSER(AHC_MODE_ID uiMode)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    LOCK_AHC_MODE();

    if (uiMode == AHC_MODE_PLAYBACK) {
        if (AIHC_SetPlaybackMode() == AHC_TRUE) {
            AHC_SetAhcSysMode(AHC_MODE_PLAYBACK);
        }
        else {
            // Turn off PIP window, to prevent customers redraw GUI without setting PIP properly
            MMPS_Display_SetWinActive(LOWER_IMAGE_WINDOW_ID, MMP_FALSE);
        }
    }
    else if (uiMode == AHC_MODE_IDLE) {

        AIHC_DrawReservedOSD(AHC_TRUE);
        AHC_OSDSetActive(THUMBNAIL_OSD_FRONT_ID, AHC_FALSE);
        AIHC_DrawReservedOSD(AHC_FALSE);
        AHC_SetAhcSysMode(AHC_MODE_IDLE);
    }
    else if (uiMode == AHC_MODE_THUMB_BROWSER) { // The mode is the same.
        AHC_Thumb_DrawPage(AHC_TRUE);
    }
    else {
        AHC_DBG_ERR(1, "[%s] NewMode [%d]\r\n", __FUNCTION__, uiMode);
    }

    UNLOCK_AHC_MODE();
    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetMode_VIDEO_RECORD
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetMode_VIDEO_RECORD(AHC_MODE_ID uiMode)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    LOCK_AHC_MODE();

    if (uiMode == AHC_MODE_IDLE) {

        #if (defined(WIFI_PORT) && WIFI_PORT == 1)
        if (AHC_STREAM_H264 == AHC_GetStreamingMode()) {
            UNLOCK_AHC_MODE();
            return AHC_FALSE;
        }
        #endif

        //#if (defined(WIFI_PORT) && WIFI_PORT == 1)
        //ahcRet = AHC_VIDEO_SetRecordMode(AHC_VIDRECD_STOP);
        //#else
        ahcRet = AHC_VIDEO_SetRecordMode(AHC_VIDRECD_STOP);
        ahcRet = AHC_VIDEO_SetRecordMode(AHC_VIDRECD_IDLE);
        //#endif

        AHC_SetAhcSysMode(uiMode);
    }
    else if (uiMode == AHC_MODE_RECORD_PREVIEW) {

        #if (defined(WIFI_PORT) && WIFI_PORT == 1)
        ahcRet = AHC_IsRecorderControllable(uiMode);
        if(ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, 0); UNLOCK_AHC_MODE(); return ahcRet;}
        #endif

        ahcRet = AHC_VIDEO_SetRecordMode(AHC_VIDRECD_STOP);
        if(ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, 0); UNLOCK_AHC_MODE(); return ahcRet;}

        AHC_SetAhcSysMode(uiMode);
    }
    else {
        AHC_DBG_ERR(1, "[%s] NewMode [%d]\r\n", __FUNCTION__, uiMode);
        UNLOCK_AHC_MODE();
        return AHC_FALSE;
    }

    UNLOCK_AHC_MODE();
    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetMode_RECORD_PREVIEW
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetMode_RECORD_PREVIEW(AHC_MODE_ID uiMode)
{
    VIDENC_FW_STATUS    eEncSts = VIDENC_FW_STATUS_NONE;
    AHC_BOOL            ahcRet = AHC_TRUE;

    LOCK_AHC_MODE();

    if (uiMode == AHC_MODE_IDLE) {

        #if (defined(WIFI_PORT) && WIFI_PORT == 1)
        if (AHC_STREAM_H264 == (AHC_GetStreamingMode() & AHC_STREAM_V_MASK)) {
            UNLOCK_AHC_MODE();
            return AHC_FALSE;
        }
        else if (AHC_GetStreamingMode() != AHC_STREAM_OFF) {
            UNLOCK_AHC_MODE();
            AHC_SetStreamingMode(AHC_STREAM_OFF);
            LOCK_AHC_MODE();
        }
        #endif

        // Turn off the preview, == AHC_VIDEO_StopRecordModeEx(AHC_FALSE, AHC_TRUE, AHC_TRUE);
        AHC_VIDEO_SetRecordMode(AHC_VIDRECD_IDLE);

        AHC_SetAhcSysMode(AHC_MODE_IDLE);
    }
    else if (uiMode == AHC_MODE_USB_WEBCAM) {
        ahcRet = AHC_SetUsbMode(AHC_USB_MODE_WEBCAM);
        if (ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, 0); UNLOCK_AHC_MODE(); return ahcRet;}

        AHC_SetAhcSysMode(AHC_MODE_USB_WEBCAM);
    }
    else if (uiMode == AHC_MODE_RECORD_PRERECD) {
        ahcRet = AHC_VIDEO_SetRecordMode(AHC_VIDRECD_PRERECD);
        if (ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, 0); UNLOCK_AHC_MODE(); return ahcRet;}

        MMPS_3GPRECD_GetPrmEncoderStatus(&eEncSts);
        if (eEncSts == VIDENC_FW_STATUS_NONE) {
            AHC_DBG_ERR(1, "SetPreRecordMode Sts None\r\n");
            ahcRet = AHC_FALSE;
        }

        AHC_SetAhcSysMode(uiMode);
    }
    else if (uiMode == AHC_MODE_VIDEO_RECORD) {
        #if (defined(WIFI_PORT) && WIFI_PORT == 1)
        ahcRet = AHC_IsRecorderControllable(uiMode);
        if(ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, 0); UNLOCK_AHC_MODE(); return ahcRet;}
        #endif

        ahcRet = AHC_VIDEO_SetRecordMode(AHC_VIDRECD_START);

        MMPS_3GPRECD_GetPrmEncoderStatus(&eEncSts);
        if (eEncSts == VIDENC_FW_STATUS_NONE) {
            AHC_DBG_ERR(1, "SetRecordMode Sts None\r\n");
            ahcRet = AHC_FALSE;
        }

        if (ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, 0); UNLOCK_AHC_MODE(); return ahcRet;}

        AHC_SetAhcSysMode(uiMode);
    }
    else {
        AHC_DBG_ERR(1, "[%s] NewMode [%d]\r\n", __FUNCTION__, uiMode);
        UNLOCK_AHC_MODE();
        return AHC_FALSE;
    }

    UNLOCK_AHC_MODE();
    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetMode_RECORD_PRERECD
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetMode_RECORD_PRERECD(AHC_MODE_ID uiMode)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    if (uiMode == AHC_MODE_VIDEO_RECORD) {
        ahcRet = AHC_SetMode_RECORD_PREVIEW(uiMode);
        if(ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, 0); return ahcRet;}
    }
    else if ((uiMode == AHC_MODE_IDLE) || (uiMode == AHC_MODE_RECORD_PREVIEW)) {
        ahcRet = AHC_SetMode_VIDEO_RECORD(uiMode);
        if(ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, 0); return ahcRet;}
    }
    else {
        AHC_DBG_ERR(1, "[%s] NewMode [%d]\r\n", __FUNCTION__, uiMode);
        return AHC_FALSE;
    }

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetMode_RECORD_PREVIEW
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetMode_RAW_PREVIEW(AHC_MODE_ID uiMode)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    LOCK_AHC_MODE();

    if (uiMode == AHC_MODE_RAW_CAPTURE) {
        if (AHC_Capture_StartTakeJpeg(uiMode)) {
            // NOP
        }
        else {
            DBG_AutoTestPrint(ATEST_ACT_CAPTURE_0x0005, ATEST_STS_END_0x0003, 0, AHC_TRUE, gbAhcDbgBrk);
        }

        AHC_SetAhcSysMode(AHC_MODE_RAW_CAPTURE);
        UNLOCK_AHC_MODE();
        AHC_SetMode(AHC_MODE_RAW_PREVIEW);
        LOCK_AHC_MODE();
    }
    else if (uiMode == AHC_MODE_IDLE) {
        AHC_Capture_StopPreview();
        AHC_SetAhcSysMode(AHC_MODE_IDLE);
    }
    else {
        AHC_DBG_ERR(1, "[%s] NewMode [%d]\r\n", __FUNCTION__, uiMode);
        UNLOCK_AHC_MODE();
        return AHC_FALSE;
    }

    UNLOCK_AHC_MODE();
    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetMode_RAW_CAPTURE
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetMode_RAW_CAPTURE(AHC_MODE_ID uiMode)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    LOCK_AHC_MODE();

    if (uiMode == AHC_MODE_RAW_PREVIEW) {
        AHC_Capture_SetPreviewMode(AHC_TRUE, AHC_FALSE);
        AHC_SetAhcSysMode(AHC_MODE_RAW_PREVIEW);
    }
    else if (uiMode == AHC_MODE_IDLE) {
        AHC_SetAhcSysMode(AHC_MODE_IDLE);
    }
    else {
        AHC_DBG_ERR(1, "[%s] NewMode [%d]\r\n", __FUNCTION__, uiMode);
        UNLOCK_AHC_MODE();
        return AHC_FALSE;
    }

    UNLOCK_AHC_MODE();
    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetMode_NET_PLAYBACK
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetMode_NET_PLAYBACK(AHC_MODE_ID uiMode)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    LOCK_AHC_MODE();

    if (uiMode == AHC_MODE_IDLE) {
        #if (defined(WIFI_PORT) && WIFI_PORT == 1)
        ncam_stop_transcoding();
        #endif
        AHC_SetAhcSysMode(AHC_MODE_IDLE);
    }
    else {
        AHC_DBG_ERR(1, "[%s] NewMode [%d]\r\n", __FUNCTION__, uiMode);
        UNLOCK_AHC_MODE();
        return AHC_FALSE;
    }

    UNLOCK_AHC_MODE();
    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetMode_CALIBRATION
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SetMode_CALIBRATION(AHC_MODE_ID uiMode)
{
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetMode
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set system mode

 Set system to assigned mode.
 Parameters:
 @param[in] uiMode AHC_MODE_IDLE, AHC_MODE_CAPTURE_PREVIEW...etc
 @retval TRUE or FALSE.
*/
AHC_BOOL AHC_SetMode(AHC_MODE_ID uiNewMode)
{
    AHC_BOOL    ahcRet = AHC_TRUE;
    AHC_MODE_ID uiOldMode = AHC_GetAhcSysMode();
    UINT8       u8OldIdx = 0, u8NewIdx = 0;

#if 1
    for (u8OldIdx = 0; u8OldIdx < AHC_MODE_NUM; u8OldIdx++) {
        if (m_stAhcModeDescp[u8OldIdx].eModeId == uiOldMode) {
            break;
        }
    }
    for (u8NewIdx = 0; u8NewIdx < AHC_MODE_NUM; u8NewIdx++) {
        if (m_stAhcModeDescp[u8NewIdx].eModeId == uiNewMode) {
            break;
        }
    }

    AHC_DBG_MSG(1, FG_RED("== SetMode [%s] To [%s]\r\n"),
                m_stAhcModeDescp[u8OldIdx].u8Name,
                m_stAhcModeDescp[u8NewIdx].u8Name);
#else
    AHC_DBG_MSG(1, FG_RED("== SetMode [0x%X] To [0x%X]\r\n"), uiOldMode, uiMode);
#endif

    if (m_AhcModeSemID == 0xFF) {
        m_AhcModeSemID = AHC_OS_CreateSem(1);
    }

    switch(uiOldMode) {

    case AHC_MODE_IDLE:
        ahcRet = AHC_SetMode_IDLE(uiNewMode);
        break;
    case AHC_MODE_CAPTURE_PREVIEW:
        ahcRet = AHC_SetMode_CAPTURE_PREVIEW(uiNewMode);
        break;
    case AHC_MODE_STILL_CAPTURE:
        ahcRet = AHC_SetMode_STILL_CAPTURE(uiNewMode);
        break;
    case AHC_MODE_LONGTIME_FIRST_CAPTURE:
        ahcRet = AHC_SetMode_LONG_TIME_CONTINUOUS_FIRST_CAPTURE(uiNewMode);
        break;
    case AHC_MODE_LONGTIME_NEXT_CAPTURE:
        ahcRet = AHC_SetMode_LONG_TIME_CONTINUOUS_NEXT_CAPTURE(uiNewMode);
        break;
    case AHC_MODE_LONGTIME_LAST_CAPTURE:
        ahcRet = AHC_SetMode_LONG_TIME_CONTINUOUS_LAST_CAPTURE(uiNewMode);
        break;
    case AHC_MODE_CONTINUOUS_CAPTURE:
        ahcRet = AHC_SetMode_CONTINUOUS_CAPTURE(uiNewMode);
        break;
    case AHC_MODE_USB_MASS_STORAGE:
        ahcRet = AHC_SetMode_USB_MASS_STORAGE(uiNewMode);
        break;
    case AHC_MODE_USB_WEBCAM:
        ahcRet = AHC_SetMode_USB_WEBCAM(uiNewMode);
        break;
    case AHC_MODE_PLAYBACK:
        ahcRet = AHC_SetMode_PLAYBACK(uiNewMode);
        break;
    case AHC_MODE_THUMB_BROWSER:
        ahcRet = AHC_SetMode_THUMB_BROWSER(uiNewMode);
        break;
    case AHC_MODE_VIDEO_RECORD:
        ahcRet = AHC_SetMode_VIDEO_RECORD(uiNewMode);
        break;
    case AHC_MODE_RECORD_PREVIEW:
        ahcRet = AHC_SetMode_RECORD_PREVIEW(uiNewMode);
        break;
    case AHC_MODE_RECORD_PRERECD:
        ahcRet = AHC_SetMode_RECORD_PRERECD(uiNewMode);
        break;
    case AHC_MODE_RAW_PREVIEW:
        ahcRet = AHC_SetMode_RAW_PREVIEW(uiNewMode);
        break;
    case AHC_MODE_RAW_CAPTURE:
        ahcRet = AHC_SetMode_RAW_CAPTURE(uiNewMode);
        break;
    case AHC_MODE_NET_PLAYBACK:
        ahcRet = AHC_SetMode_NET_PLAYBACK(uiNewMode);
        break;
    case AHC_MODE_CALIBRATION:
        ahcRet = AHC_SetMode_CALIBRATION(uiNewMode);
        break;
    default:
        AHC_DBG_ERR(1, "This AHC Mode(%d) is not ready yet!\r\n", AHC_GetAhcSysMode());
        break;
    }

    if (ahcRet != AHC_TRUE) {
        AHC_DBG_ERR(0, FG_RED("AHC_SetMode ERROR!\r\n"));
        return AHC_FALSE;
    }

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetAhcSysMode
//  Description :
//------------------------------------------------------------------------------
AHC_MODE_ID AHC_GetAhcSysMode(void)
{
    #if (EN_AUTO_TEST_LOG == 1)
    if (gbAhcDbgBrk) {
        MMPD_System_IsAutoTestCmdLFull(m_AhcSystemMode);
    }
    #endif

    return m_AhcSystemMode;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetAhcSysMode
//  Description :
//------------------------------------------------------------------------------
void AHC_SetAhcSysMode(AHC_MODE_ID uiMode)
{
    if (uiMode == AHC_MODE_IDLE) {
        #if (EN_AUTO_TEST_LOG == 1)
        if (gbAhcDbgBrk) {
            MMPD_System_IsAutoTestCmdLFull(m_AhcSystemMode);
        }
        #endif
    }

    m_AhcSystemMode = uiMode;
}

//------------------------------------------------------------------------------
//  Function    : AHC_IsInVideoMode
//  Description :
//------------------------------------------------------------------------------
int AHC_IsInVideoMode(void)
{
    return m_AhcSystemMode == AHC_MODE_VIDEO_RECORD ||
           m_AhcSystemMode == AHC_MODE_RECORD_PRERECD ||
           m_AhcSystemMode == AHC_MODE_RECORD_PREVIEW;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetSystemStatus
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get system status

 Get current system status from the information keeper.
 Parameters:
 @param[out] *pwValue Get status result.
 @retval TRUE or FALSE.
*/
AHC_BOOL AHC_GetSystemStatus(UINT32 *pwValue)
{
    MMP_ULONG fw_status = 0;
    UINT32    ulCurrentPBtype = 0;

    *pwValue = (m_AhcSystemMode << 16) & 0xFFFF0000;

    switch(m_AhcSystemMode) {
        case AHC_MODE_IDLE:
            *pwValue |= (AHC_SYS_IDLE & 0xFFFF);
            break;
        case AHC_MODE_CAPTURE_PREVIEW:
            *pwValue |= (AHC_SYS_IDLE & 0xFFFF);
            break;
        case AHC_MODE_STILL_CAPTURE:
            *pwValue |= (AHC_SYS_IDLE & 0xFFFF);
            break;
        case AHC_MODE_USB_MASS_STORAGE:
            fw_status = MMPS_USB_GetStatus();
            *pwValue |= (AHC_SYS_USB_STATUS + fw_status) & 0xFFFF;
            break;
        case AHC_MODE_USB_WEBCAM:
            *pwValue |= (AHC_SYS_IDLE & 0xFFFF);
            break;
        case AHC_MODE_PLAYBACK:
            AIHC_GetCurrentPBFileType(&ulCurrentPBtype);
            if (ulCurrentPBtype == DCF_OBG_JPG)
            {
                *pwValue |= (AHC_SYS_IDLE & 0xFFFF);
            }
            else if ((ulCurrentPBtype == DCF_OBG_MP3) ||
                     (ulCurrentPBtype == DCF_OBG_WAV) ||
                     (ulCurrentPBtype == DCF_OBG_OGG) ||
                     (ulCurrentPBtype == DCF_OBG_WMA))
            {
                MMPS_AUDIO_GetPlayStatus((MMPS_AUDIO_PLAY_STATUS*)&fw_status);
                *pwValue |= (AHC_SYS_AUDPLAY_STATUS + (fw_status>>8)) & 0xFFFF;
            }
            else
            {
                MMPS_VIDPLAY_GetState((MMP_M_STATE*)&fw_status);
                *pwValue |= (AHC_SYS_VIDPLAY_INVALID + fw_status) & 0xFFFF;
            }
            break;
        case AHC_MODE_THUMB_BROWSER:
            *pwValue |= (AHC_SYS_IDLE & 0xFFFF);
            break;
        case AHC_MODE_VIDEO_RECORD:
            MMPS_3GPRECD_GetPrmEncoderStatus((VIDENC_FW_STATUS *)&fw_status);
            *pwValue |= (AHC_SYS_VIDRECD_STATUS + fw_status) & 0xFFFF;
            break;
        case AHC_MODE_RECORD_PREVIEW:
            MMPS_3GPRECD_GetPreviewPipeStatus(gsAhcPrmSensor, (MMP_BOOL*)&fw_status);
            if (fw_status == MMP_TRUE) {
                *pwValue |= AHC_SYS_VIDRECD_PREVIEW_NORMAL & 0xFFFF;
            }
            else {
                *pwValue |= AHC_SYS_VIDRECD_PREVIEW_ABNORMAL & 0xFFFF;
            }
            break;
        case AHC_MODE_CALIBRATION:
            *pwValue |= (AHC_SYS_IDLE & 0xFFFF);
            break;
    }

    return AHC_TRUE;
}
