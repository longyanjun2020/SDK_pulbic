/**
 @file AHC_Genera_CarDV.c
 @brief AHC general control Function for CarDV project
 @author
 @version 1.0
*/

/*===========================================================================
 * Include file
 *===========================================================================*/

#include "Customer_config.h"
#include "AHC_Config_SDK.h"
#include "ahc_display.h"

#include "mmp_lib.h"
#include "mmp_err.h"
#include "ait_utility.h"
#include "ahc_message.h"
#include "ahc_video.h"
#include "ahc_sensor.h"
#include "ahc_general_cardv.h"
#include "ahc_uf.h"
#include "ahc_modectl.h"
#include "ledcontrol.h"
#include "MenuSetting.h"
#include "mediaplaybackctrl.h"
#include "ShowOSDFunc.h"
#include "OSDStrings.h"
#include "snr_cfg.h"

#ifdef _OEM_MENU_
#include "Oem_Menu.h"
#endif

#if defined(WIFI_PORT) && (WIFI_PORT==1)
#include "netapp.h"
#endif

/*===========================================================================
 * Global variable
 *===========================================================================*/

static UINT32       m_ulVRPowerOffTime          = 0;    //Unit:seconds
static UINT8        m_ubBootwithCharger         = 0;
static AHC_BOOL     m_ubShutdownByChargerOut    = AHC_FALSE;
static UINT8        m_ubDialogState             = MSG_DISMISS;
static UINT8        m_ubDialogEvent             = WMSG_NONE;
static UINT8        m_ubMenuFlashLed            = 0;
AHC_BOOL            m_ubInTVMode                = AHC_FALSE;
AHC_BOOL            bUpdateFlashLedIcon         = AHC_FALSE;
TMHOOK              gTmKeypadHook               = NULL;
AHC_BOOL            bInLCDPowerSave             = AHC_FALSE;

#if (POWER_ON_BUTTON_ACTION)
static UINT32       m_ulQuickKey                = 0;
static UINT16       m_usOption                  = 1;
static AHC_BOOL     PowerOnAction               = AHC_FALSE;
#endif

#if (SWITCH_TVOUT_BY_KEY)
AHC_BOOL            m_ubGoToTVmode              = AHC_TRUE;
#endif
#if (defined(SWITCH_TVOUT_BY_MENU) && SWITCH_TVOUT_BY_MENU)
AHC_BOOL            m_ubGoToTVmode              = AHC_FALSE;
#endif

static OSD_LANGSET gLangSet[] =
{
#if (MENU_GENERAL_LANGUAGE_ENGLISH_EN)
    {(const unsigned char **)gEnglishOSDStringPool,     &LANGUAGE_FONT_ENGLISH},
#endif
#if (MENU_GENERAL_LANGUAGE_SPANISH_EN)
    {(const unsigned char **)gSpanishOSDStringPool,     &LANGUAGE_FONT_SPANISH},
#endif
#if (MENU_GENERAL_LANGUAGE_PORTUGUESE_EN)
    {(const unsigned char **)gPortugueseOSDStringPool,  &LANGUAGE_FONT_PORTUGUESE},
#endif
#if (MENU_GENERAL_LANGUAGE_RUSSIAN_EN)
    {(const unsigned char **)gRussianOSDStringPool,     &LANGUAGE_FONT_RUSSIAN},
#endif
#if (MENU_GENERAL_LANGUAGE_SCHINESE_EN)
    {(const unsigned char **)gSChineseOSDStringPool,    &LANGUAGE_FONT_SCHINESE},
    #endif  
#if (MENU_GENERAL_LANGUAGE_TCHINESE_EN)
    {(const unsigned char **)gTChineseOSDStringPool,    &LANGUAGE_FONT_TCHINESE},
#endif
#if (MENU_GENERAL_LANGUAGE_GERMAN_EN)
    {(const unsigned char **)gGermanOSDStringPool,      &LANGUAGE_FONT_GERMAN},
#endif
#if (MENU_GENERAL_LANGUAGE_ITALIAN_EN)
    {(const unsigned char **)gItalianOSDStringPool,     &LANGUAGE_FONT_ITALIAN},
#endif
#if (MENU_GENERAL_LANGUAGE_LATVIAN_EN)
    {(const unsigned char **)gLatvianOSDStringPool,     &LANGUAGE_FONT_LATVIAN},
#endif
#if (MENU_GENERAL_LANGUAGE_POLISH_EN)
    {(const unsigned char **)gPolishOSDStringPool,      &LANGUAGE_FONT_POLISH},
#endif
#if (MENU_GENERAL_LANGUAGE_ROMANIAN_EN)
    {(const unsigned char **)gRomanianOSDStringPool,    &LANGUAGE_FONT_ROMANIAN},
#endif
#if (MENU_GENERAL_LANGUAGE_SLOVAK_EN)
    {(const unsigned char **)gSlovakOSDStringPool,      &LANGUAGE_FONT_SLOVAK},
#endif
#if (MENU_GENERAL_LANGUAGE_UKRANINIAN_EN)
    {(const unsigned char **)gUkraninianOSDStringPool,  &LANGUAGE_FONT_UKRANINIAN},
#endif
#if (MENU_GENERAL_LANGUAGE_FRENCH_EN)
    {(const unsigned char **)gFrenchOSDStringPool,      &LANGUAGE_FONT_FRENCH},
#endif
#if (MENU_GENERAL_LANGUAGE_JAPANESE_EN)
    {(const unsigned char **)gJapaneseOSDStringPool,    &LANGUAGE_FONT_JAPANESE},
#endif
#if (MENU_GENERAL_LANGUAGE_KOREAN_EN)
    {(const unsigned char **)gKoreanOSDStringPool,      &LANGUAGE_FONT_KOREAN},
#endif
#if (MENU_GENERAL_LANGUAGE_CZECH_EN)
    {(const unsigned char **)gCzechOSDStringPool,       &LANGUAGE_FONT_CZECH},
#endif
#if (MENU_GENERAL_LANGUAGE_TURKISH_EN)
    {(const unsigned char **)gTurkishOSDStringPool,     &LANGUAGE_FONT_TURKISH},
#endif
#if (MENU_GENERAL_LANGUAGE_DUTCH_EN)
    {(const unsigned char **)gDutchOSDStringPool,       &LANGUAGE_FONT_DUTCH},
#endif
#if (MENU_GENERAL_LANGUAGE_DANISH_EN)
    {(const unsigned char **)gDanishOSDStringPool,      &LANGUAGE_FONT_DANISH},
#endif
#if (MENU_GENERAL_LANGUAGE_GREEK_EN)
    {(const unsigned char **)gGreekOSDStringPool,       &LANGUAGE_FONT_GREEK},
#endif
#if (MENU_GENERAL_LANGUAGE_ARABIC_EN)
    {(const unsigned char **)gArabicOSDStringPool,      &LANGUAGE_FONT_ARABIC},
#endif
#if (MENU_GENERAL_LANGUAGE_THAI_EN)
    {(const unsigned char **)gThaiOSDStringPool,        &LANGUAGE_FONT_THAI},
#endif
};

/*===========================================================================
 * Extern variable
 *===========================================================================*/

extern UINT32       ObjSelect;
extern AHC_BOOL     m_ubPlaybackRearCam;

/*===========================================================================
 * Extern function
 *===========================================================================*/

extern AHC_BOOL AHC_VIDEO_SetRecVolumeByMenuSetting(AHC_BOOL bEnable);

/*===========================================================================
 * Main body
 *===========================================================================*/

#if 0
void ____Language_Function____(){ruturn;} //dummy
#endif

#define NUM_LANGUAGE    (sizeof(gLangSet) / sizeof(OSD_LANGSET))

extern const unsigned char **pShowOSDStringPool;

UINT8 ShowOSD_GetLanguageEx()
{
    return MenuSettingConfig()->uiLanguage;
}

void ShowOSD_SetLanguageEx(UINT8 id, UINT8 nlang)
{
    if (nlang >= NUM_LANGUAGE)
        nlang = SHOWOSD_LANG_ENG;

    pShowOSDStringPool = gLangSet[nlang].strpool;
    if (id != 0xff) {
        AHC_OSDSetFont(id, gLangSet[nlang].fontmap);
    }
}

#if 0
void ____Timer_Hook_Function_____(){ruturn;} //dummy
#endif

void AHC_TmKeypadHook(void *cb)
{
    gTmKeypadHook = (TMHOOK)cb;
}

#if 0
void ____Video_Record_Function_____(){ruturn;} //dummy
#endif

UINT32 AHC_GetVideoPowerOffTime(void)
{
    switch(MenuSettingConfig()->uiMOVPowerOffTime)
    {
    #if (MENU_MOVIE_POWER_OFF_DELAY_0SEC_EN)
        case MOVIE_POWEROFF_TIME_0MIN:
            m_ulVRPowerOffTime = 0;
            break;
    #endif
    #if (MENU_MOVIE_POWER_OFF_DELAY_5SEC_EN)
        case MOVIE_POWEROFF_TIME_5SEC:
            m_ulVRPowerOffTime = 5;
            break;
    #endif
    #if (MENU_MOVIE_POWER_OFF_DELAY_10SEC_EN)
        case MOVIE_POWEROFF_TIME_10SEC:
            m_ulVRPowerOffTime = 10;
            break;
    #endif
    #if (MENU_MOVIE_POWER_OFF_DELAY_15SEC_EN)
        case MOVIE_POWEROFF_TIME_15SEC:
            m_ulVRPowerOffTime = 15;
            break;
    #endif
    #if (MENU_MOVIE_POWER_OFF_DELAY_30SEC_EN)
        case MOVIE_POWEROFF_TIME_30SEC:
            m_ulVRPowerOffTime = 30;
            break;
    #endif
    #if (MENU_MOVIE_POWER_OFF_DELAY_1MIN_EN)
        case MOVIE_POWEROFF_TIME_1MIN:
            m_ulVRPowerOffTime = 60;
            break;
    #endif
    #if (MENU_MOVIE_POWER_OFF_DELAY_2MIN_EN)
        case MOVIE_POWEROFF_TIME_2MIN:
            m_ulVRPowerOffTime = 120;
            break;
    #endif
    #if (MENU_MOVIE_POWER_OFF_DELAY_3MIN_EN)
        case MOVIE_POWEROFF_TIME_3MIN:
            m_ulVRPowerOffTime = 180;
            break;
    #endif
    #if (MENU_MOVIE_POWER_OFF_DELAY_5MIN_EN)
        case MOVIE_POWEROFF_TIME_5MIN:
            m_ulVRPowerOffTime = 300;
            break;
    #endif
    #if (MENU_MOVIE_POWER_OFF_DELAY_10MIN_EN)
        case MOVIE_POWEROFF_TIME_10MIN:
            m_ulVRPowerOffTime = 600;
            break;
    #endif
    #if (MENU_MOVIE_POWER_OFF_DELAY_15MIN_EN)
        case MOVIE_POWEROFF_TIME_15MIN:
            m_ulVRPowerOffTime = 900;
            break;
    #endif
    #if (MENU_MOVIE_POWER_OFF_DELAY_30MIN_EN)
        case MOVIE_POWEROFF_TIME_30MIN:
            m_ulVRPowerOffTime = 1800;
            break;
    #endif
    #if (MENU_MOVIE_POWER_OFF_DELAY_60MIN_EN)
        case MOVIE_POWEROFF_TIME_60MIN:
            m_ulVRPowerOffTime = 3600;
            break;
    #endif
        default:
            m_ulVRPowerOffTime = 0;
            break;
    }

    return m_ulVRPowerOffTime;
}

UINT32 AHC_GetVideoMaxLockFileTime(void)
{
    return MAX_LOCK_FILE_TIME;
}

INT8* AHC_GetLockedFileName(UINT8 bSelect)
{
    INT8        FileName[DCF_MAX_FILE_NAME_SIZE] = {0};
    UINT32      MaxDcfObj;

    MaxDcfObj = AHC_GetMappingFileNum(FILE_MOVIE);

    if(MaxDcfObj == 0)
        return (INT8*)DEFAULT_LOCKED_FILENAME;

    switch(bSelect)
    {
        case 0://Previous
            if(MaxDcfObj<=1)
                return (INT8*)DEFAULT_LOCKED_FILENAME;
            else
                AHC_UF_GetFileNamebyIndex(MaxDcfObj-2,FileName) ;
        break;
        case 1://Current
            AHC_UF_GetFileNamebyIndex(MaxDcfObj-2,FileName) ;
        break;
        default:
            return (INT8*)DEFAULT_LOCKED_FILENAME;
        break;
    }
    return FileName;
}

void AHC_SetShutdownByChargerOut(AHC_BOOL bEnable)
{
    VideoPowerOffCounterReset();
    m_ubShutdownByChargerOut = bEnable;
}

AHC_BOOL AHC_GetShutdownByChargerOut(void)
{
    return m_ubShutdownByChargerOut;
}

void AHC_SetRecordByChargerIn(UINT8 ubDelay)
{
    #if (SUPPORT_GSENSOR && POWER_ON_BY_GSENSOR_EN)
    if ((AHC_GetBootingSrc() & PWR_ON_BY_GSENSOR) == PWR_ON_BY_GSENSOR)
    {
        if (GSNR_PWRON_ACT == GSNR_PWRON_REC_AUTO) {
            m_ubBootwithCharger = ubDelay;
            return;
        }
    }
    #endif

    if (AHC_GetAutoRec()) {
        m_ubBootwithCharger = ubDelay;
    }
    else {
        printc(FG_RED("!!! MenuSettingConfig()->uiAutoRec is OFF\r\n"));
        m_ubBootwithCharger = 0;
    }
}

UINT8 AHC_GetRecordByChargerIn(void)
{
    return m_ubBootwithCharger;
}

AHC_BOOL AHC_GetAutoRec(void)
{
    return (MenuSettingConfig()->uiAutoRec == AUTO_REC_ON)? (AHC_TRUE) : (AHC_FALSE);
}
AHC_BOOL AHC_RollBackMinKeyProtectFile(void)
{
    extern UINT32       m_ulLockFileNum;
    AHC_BOOL            ahc_ret         = AHC_FALSE;
    UINT32              MaxObjIdx;
    UINT32              ObjIdx;
    AHC_BOOL            bReadOnly;
    AHC_BOOL            bCharLock;
    
    MaxObjIdx = AHC_GetMappingFileNum(FILE_MOVIE);

    if(MaxObjIdx == 0) {
        printc("No More DCF File for Delete!\r\n");
        return AHC_FALSE;
    }

    for(ObjIdx = 0; ObjIdx < MaxObjIdx; ObjIdx++) {
        if (m_ulLockFileNum <= MAX_LOCK_FILE_NUM) {
            return AHC_TRUE;
        }

        AHC_UF_SetCurrentIndex(ObjIdx);

        if(AHC_FALSE == AHC_UF_IsReadOnlybyIndex(ObjIdx,&bReadOnly)) {
            printc(FG_RED("AHC_UF_IsReadOnlybyIndex Error\r\n"));
            return AHC_FALSE;
        }

        if (AHC_FALSE == AHC_UF_IsCharLockbyIndex(ObjIdx, &bCharLock)) {
            printc(FG_RED("AHC_UF_IsCharLockbyIndex Error\r\n"));
            return AHC_FALSE;
        }

        if (bReadOnly) {
            // Read Only File
            ahc_ret = AHC_UF_FileOperation_ByIdx(ObjIdx, DCF_FILE_NON_READ_ONLY_ALL_CAM, NULL, NULL);
            if(ahc_ret == AHC_FALSE) {
                printc(FG_RED("AHC_UF_FileOperation_ByIdx DCF_FILE_NON_READ_ONLY_ALL_CAM Error\r\n"));
                return AHC_FALSE;
            }
        }

        if (bCharLock) {
            // Char Lock
            ahc_ret = AHC_UF_FileOperation_ByIdx(ObjIdx, DCF_FILE_CHAR_UNLOCK_ALL_CAM, NULL, NULL);
            if(ahc_ret==AHC_FALSE) {
                printc(FG_RED("AHC_UF_FileOperation_ByIdx DCF_FILE_CHAR_UNLOCK_ALL_CAM Error\r\n"));
            }
        }

        if (bReadOnly && bCharLock) {
            m_ulLockFileNum++;
        }
    }
    
    return ahc_ret;
}

#if 0
void ____TV_Function_____(){ruturn;} //dummy
#endif

void AHC_SwitchLCDandTVOUT(void)
{
#if (SWITCH_TVOUT_BY_KEY)

    #ifdef TV_ONLY

    if(AHC_IsTVConnectEx())
    {
        if(m_ubInTVMode)
        {
            m_ubInTVMode = AHC_FALSE;
        }
        else
        {
            m_ubInTVMode = AHC_TRUE;
        }
    }

    #else//TV_ONLY

    if(AHC_IsTVConnectEx())
    {
        m_ubGoToTVmode = AHC_FALSE;
        StateTVMode(EVENT_TV_KEY_LCD_OUTPUT);
    }
    else
    {
        m_ubGoToTVmode = AHC_TRUE;
        AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_TV_DETECTED, 0);
    }
    #endif
#endif
}

#if 0
void ____LCD_Function_____(){ruturn;} //dummy
#endif

AHC_BOOL AHC_SwitchLCDBackLight(void)
{
    if(!LedCtrl_GetBacklightStatus())
    {
        LedCtrl_LcdBackLight(AHC_TRUE);
    }
    else
    {
        bInLCDPowerSave = AHC_TRUE;
        LedCtrl_LcdBackLight(AHC_FALSE);
    }

    return AHC_TRUE;
}


AHC_BOOL AHC_ChangeEV(AHC_BOOL bCycle, UINT8 bDir)
{
    extern void DrawStateCaptureUpdate(UINT32 ubEvent);
    UINT8 cev = 0;
    if((AHC_Menu_SettingGetCB((char*)COMMON_KEY_EV, &cev) == AHC_FALSE))
    {
        cev = COMMON_EVVALUE_DEFAULT; // default;
    }
    if(bCycle)
    {
        if(cev < (COMMON_EVVALUE_NUM - 1))
        {
            cev++;
        }
        else if(cev == (COMMON_EVVALUE_NUM - 1))
        {
            cev = 0;
        }
    }
    else
    {
        if(bDir && cev < (COMMON_EVVALUE_NUM - 1))
        {
            cev++;
        }
        else if(!bDir && cev > 0)
        {
            cev--;
        }
    }
    AHC_SetAeEvBiasMode(gsAhcPrmSensor, Menu_EV_To_AE_EV_BIAS(cev));
    if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
        AHC_SetAeEvBiasMode(gsAhcScdSensor, Menu_EV_To_AE_EV_BIAS(cev));
    DrawStateCaptureUpdate(EVENT_DSC_SET_EV);

    return AHC_TRUE;
}

AHC_BOOL AHC_ChangeVolume(AHC_BOOL bCycle,UINT8 bDir)
{
    #define MAX_VOLUME (10)

    if(bCycle)
    {
        if(MenuSettingConfig()->uiVolume < MAX_VOLUME)
        {
            MenuSettingConfig()->uiVolume++;
        }
        else if(MenuSettingConfig()->uiVolume == MAX_VOLUME)
        {
            MenuSettingConfig()->uiVolume = 0;
        }
    }
    else
    {
        if(bDir && MenuSettingConfig()->uiVolume < MAX_VOLUME)
        {
            MenuSettingConfig()->uiVolume++;
        }
        else if(!bDir && MenuSettingConfig()->uiVolume > 0)
        {
            MenuSettingConfig()->uiVolume--;
        }
    }

    Menu_SetVolume(MenuSettingConfig()->uiVolume);

    return AHC_TRUE;
}

AHC_BOOL AHC_ToggleMute(void)
{
    extern AHC_BOOL bMuteRecord;

    if (MenuSettingConfig()->uiMOVSoundRecord==MOVIE_SOUND_RECORD_ON) {
        bMuteRecord = AHC_TRUE;
        Menu_SetMICSensitivity(MenuSettingConfig()->uiMicSensitivity);//backup AGAIN&DGAIN
        Menu_SetSoundRecord(MOVIE_SOUND_RECORD_OFF);
    }
    else {
        bMuteRecord = AHC_FALSE;
        Menu_SetSoundRecord(MOVIE_SOUND_RECORD_ON);
    }

    if (VideoFunc_GetRecordStatus()) {
        if (bMuteRecord) {
            AHC_VIDEO_SetRecVolumeByMenuSetting(AHC_FALSE);
            MMPD_AUDIO_SetRecordSilence(MMP_TRUE); 
        }
        else {
            AHC_VIDEO_SetRecVolumeByMenuSetting(AHC_TRUE);
            MMPD_AUDIO_SetRecordSilence(MMP_FALSE);
        }
    }
    else
    {
        if (bMuteRecord) {
            AHC_PlaySoundEffect(AHC_SOUNDEFFECT_MICOFF);
        }
        else {
            AHC_PlaySoundEffect(AHC_SOUNDEFFECT_MICON);
        }
    }

    return AHC_TRUE;
}

AHC_BOOL AHC_ToggleTwilightMode(void)
{
#if (DAY_NIGHT_MODE_SWITCH_EN)

    extern AHC_BOOL bNightMode;
    UINT8 csc = 0;

    if((AHC_Menu_SettingGetCB((char*)COMMON_KEY_SCENE, &csc) == AHC_FALSE)){
        csc = COMMON_SCENE_AUTO;//default value
    }

    switch(csc)
    {
    case COMMON_SCENE_TWILIGHT:
        Menu_SetSceneMode(SCENE_TWILIGHT);
        bNightMode = AHC_TRUE;
        printc("TWILIGHT MODE!!\r\n");
        break;
    case COMMON_SCENE_AUTO:
        Menu_SetSceneMode(SCENE_AUTO);
        bNightMode = AHC_FALSE;
        printc("AUTO MODE!\r\n");
        break;
    }
#endif
    return AHC_TRUE;
}

#if 0
void ____LED_Function_____(){ruturn;} //dummy
#endif

void AHC_SetMenuFlashLEDStatus(UINT8 ubLed)
{
    bUpdateFlashLedIcon = AHC_TRUE;
    m_ubMenuFlashLed = ubLed;
}

UINT8 AHC_GetMenuFlashLEDStatus(void)
{
    return m_ubMenuFlashLed;
}

AHC_BOOL AHC_ToggleFlashLED(UINT8 ubMode)
{
    UINT8 ubCtrl = LED_FLASH_CTRL;
    UINT8 LEDState;

    if(ubMode==LED_MODE_AUTO_ON_OFF)
    {
        MenuSettingConfig()->uiFlashMode = (MenuSettingConfig()->uiFlashMode + 1) % FLASH_NUM;
        Menu_SetFlashLEDMode( MenuSettingConfig()->uiFlashMode );
    }
    else if(ubMode==LED_MODE_ON_OFF)
    {
        switch(ubCtrl)
        {
            case LED_BY_KEY:
                if(MenuSettingConfig()->uiFlashMode==FLASH_ON)
                    MenuSettingConfig()->uiFlashMode = FLASH_OFF;
                else if(MenuSettingConfig()->uiFlashMode==FLASH_OFF)
                    MenuSettingConfig()->uiFlashMode = FLASH_ON;

                Menu_SetFlashLEDMode( MenuSettingConfig()->uiFlashMode );
            break;

            case LED_BY_KEY_WITH_MENU_CONFIRMED:

                if(MenuSettingConfig()->uiLEDFlash==LED_FALSH_ON)
                {
                    if(MenuSettingConfig()->uiFlashMode==FLASH_ON)
                        MenuSettingConfig()->uiFlashMode = FLASH_OFF;
                    else if(MenuSettingConfig()->uiFlashMode==FLASH_OFF)
                        MenuSettingConfig()->uiFlashMode = FLASH_ON;
                }

                Menu_SetFlashLEDMode( MenuSettingConfig()->uiFlashMode );
            break;

            case LED_BY_MENU:
                //TBD
            break;

            case LED_BY_MENU_AND_KEY_LINK:

                if(MenuSettingConfig()->uiLEDFlash==LED_FALSH_ON)
                    MenuSettingConfig()->uiLEDFlash = LED_FALSH_OFF;
                else if(MenuSettingConfig()->uiLEDFlash==LED_FALSH_OFF)
                    MenuSettingConfig()->uiLEDFlash = LED_FALSH_ON;

                AHC_SetMenuFlashLEDStatus (MenuSettingConfig()->uiLEDFlash);
                Menu_SetFlashLEDMode( MenuSettingConfig()->uiLEDFlash );
            break;

            case LED_BY_MENU_AND_KEY_NOT_LINK:

                LEDState = AHC_GetMenuFlashLEDStatus();
                LEDState = (LEDState == LED_FALSH_ON)?(LED_FALSH_OFF):(LED_FALSH_ON);

                AHC_SetMenuFlashLEDStatus(LEDState);
                LedCtrl_FlashLed(!LEDState);
            break;

            default:
                printc("Not Support LED Control Mode\r\n");
            break;
        }
    }
    bUpdateFlashLedIcon = AHC_TRUE;

    return AHC_TRUE;
}

void AHC_PreSetFlashLED(void)
{
#if (LED_FLASH_CTRL==LED_BY_MENU                || \
     LED_FLASH_CTRL==LED_BY_MENU_AND_KEY_LINK   || \
     LED_FLASH_CTRL==LED_BY_MENU_AND_KEY_NOT_LINK)

    Menu_SetFlashLEDMode(AHC_GetMenuFlashLEDStatus());

#elif ( LED_FLASH_CTRL==LED_BY_KEY || \
        LED_FLASH_CTRL==LED_BY_KEY_WITH_MENU_CONFIRMED)

    Menu_SetFlashLEDMode(MenuSettingConfig()->uiFlashMode);
#endif
}

#if 0
void ____Misc_Function_____(){ruturn;} //dummy
#endif

AHC_BOOL AHC_PowerOn_Welcome(void)
{
//  MMPS_AUDIO_PLAY_STATUS  status;
//    MMP_ERR               ret_val;
    AHC_BOOL                ahc_ret;

#ifdef CFG_CUS_POWERON_SOUNDEFFECT
    CFG_CUS_POWERON_SOUNDEFFECT();
#else
    ahc_ret = AHC_PlaySoundEffect(AHC_SOUNDEFFECT_POWERON);
#endif

    /* Delay more time for task init priority */
    if(AHC_TRUE != ahc_ret)
        return AHC_TRUE;
//CZ patch...20160204       
#if 0 // For power on speed. Don't wait power on sound here. If need we can call stop play later.
    do{
        ret_val = MMPS_AUI_GetPlayStatus(&status);
        AHC_OS_Sleep(100);
    } while((MMP_ERR_NONE == ret_val) && (MMPS_AUDIO_PLAY_STOP != status));
#endif
    return AHC_TRUE;
}

AHC_BOOL AHC_ShowErrorDialog(WMSG_INFO iInfo)
{
    if (iInfo != WMSG_NONE)
    {
        m_ubDialogState = MSG_PRESENT;
        AHC_WMSG_Draw(AHC_TRUE, iInfo, 0);
        m_ubDialogEvent = iInfo;
    }
    else
    {
        m_ubDialogState = MSG_DISMISS;
        AHC_WMSG_Draw(AHC_FALSE, WMSG_NONE, 0);
        m_ubDialogEvent = WMSG_NONE;
    }
    return AHC_TRUE;
}

AHC_BOOL AHC_CheckErrorDialog(UINT32 ulEvent)
{
    if (ERROR_DIALOG_PRESENT(m_ubDialogState))
    {
        if (AHC_WMSG_GetInfo() == WMSG_NONE) {
            AHC_WMSG_Draw(AHC_TRUE, m_ubDialogEvent, 0);
        }

        if(m_ubDialogEvent == WMSG_INSERT_SD_AGAIN && ulEvent == EVENT_SD_DETECT)
        {
            AHC_ShowErrorDialog(WMSG_NONE); // Dismiss Error Dialog
            AHC_WMSG_Draw(AHC_TRUE, WMSG_WAIT_INITIAL_DONE, 3);
            return AHC_TRUE;
        }
        
        // Critical Error Presetns and waiting any keys to release
        if ((ulEvent == EVENT_POWER_OFF)        ||
            ((ulEvent >= EVENT_KEY_START) && (ulEvent < EVENT_KEY_END)))
        {
            AHC_ShowErrorDialog(WMSG_NONE); // Dismiss Error Dialog
        }
        return AHC_FALSE;
    }
    return AHC_TRUE;
}

AHC_BOOL AHC_IsDialogPresent(void)
{
    return ERROR_DIALOG_PRESENT(m_ubDialogState);
}

AHC_BOOL AHC_ShowSoundWarning(void)
{
    if (ERROR_DIALOG_PRESENT(m_ubDialogState))
    {
        if (MenuSettingConfig()->uiBeep == BEEP_ON && MenuSettingConfig()->uiVolume != 0)
        {
            if(!VideoFunc_GetRecordStatus() && !VideoFunc_PreRecordStatus())
                AHC_PlaySoundEffect(AHC_SOUNDEFFECT_BATWARNING);
        }
    }
    return AHC_TRUE;
}

AHC_BOOL AHC_CheckCurSysMode(UINT16 CheckMode)
{
    UINT32   CurSysMode;

    AHC_GetSystemStatus(&CurSysMode);

    CurSysMode >>= 16;

    return (CurSysMode==CheckMode)?(AHC_TRUE):(AHC_FALSE);
}

AHC_BOOL AHC_CheckCurFileLockStatus(void)
{
    UINT32 CurObjIdx;

    AHC_UF_GetCurrentIndex(&CurObjIdx);

    return (AHC_IsFileProtect(CurObjIdx))?(AHC_TRUE):(AHC_FALSE);
}

AHC_BOOL AHC_IsCurFileCharLock(void)
{
    UINT32 CurObjIdx;

    AHC_UF_GetCurrentIndex(&CurObjIdx);

    return (AHC_Thumb_IsFileLocked(CurObjIdx))?(AHC_TRUE):(AHC_FALSE);
}

AHC_BOOL AHC_SetPlayFileOrder(UINT8 ubOrder)
{
    UINT32 MaxDcfObj;

    if(GetCurrentOpMode()==MOVPB_MODE || GetCurrentOpMode()==VIDEOREC_MODE)
        MaxDcfObj = AHC_GetMappingFileNum(FILE_MOVIE);
    else if(GetCurrentOpMode()==JPGPB_MODE || GetCurrentOpMode()==CAPTURE_MODE)
        MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO);
    else if(GetCurrentOpMode()==JPGPB_MOVPB_MODE)
        MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO_MOVIE);
    
    if(MaxDcfObj==0)
        return AHC_FALSE;

    switch(ubOrder)
    {
        case PLAY_FIRST_FILE:
            ObjSelect = 0;
        break;
        case PLAY_CUR_FILE:
            //TBD
        break;
        case PLAY_LAST_FILE:
            ObjSelect = MaxDcfObj-1;
        break;
        default:
        break;
    }
    return AHC_TRUE;
}

UINT32 AHC_GetMappingFileNum(UINT8 ubFileType)
{
    UINT32  MaxDcfObj = 0;

    switch(ubFileType)
    {
        case FILE_PHOTO:
            AHC_UF_SetFreeChar(0, DCF_SET_ALLOWED, (UINT8 *) SEARCH_PHOTO);
        break;

        case FILE_MOVIE:
            AHC_UF_SetFreeChar(0, DCF_SET_ALLOWED, (UINT8 *) SEARCH_MOVIE);
        break;

        case FILE_PHOTO_MOVIE:
            AHC_UF_SetFreeChar(0, DCF_SET_ALLOWED, (UINT8 *) SEARCH_PHOTO_MOVIE);
        break;

        default:
            return 0;
    }
    if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){ 
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
    }
    AHC_UF_GetTotalFileCount(&MaxDcfObj);
    if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){ 
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
    }
    return MaxDcfObj;
}

AHC_BOOL AHC_SetBootUpUIMode(void)
{
#ifdef CFG_CUS_BOOT_UP_UI_MODE
    CFG_CUS_BOOT_UP_UI_MODE();
#else
    #if (MENU_GENERAL_BOOT_UP_MODE_EN)

    extern UINT8 m_ubDSCMode;

    switch(MenuSettingConfig()->uiBootUpMode)
    {
    #if (MENU_GENERAL_BOOT_UP_VR_MODE_EN)
        case BOOT_UP_MODE_DVR:
            StateSwitchMode(UI_VIDEO_STATE);
        break;
    #endif
    #if (MENU_GENERAL_BOOT_UP_DSC_MODE_EN)
        case BOOT_UP_MODE_DSC:
            m_ubDSCMode = DSC_ONE_SHOT;
            StateSwitchMode(UI_CAMERA_STATE);
        break;
    #endif
    #if (MENU_GENERAL_BOOT_UP_BURST_MODE_EN)
        case BOOT_UP_MODE_BURST:
            m_ubDSCMode = DSC_BURST_SHOT;
            StateSwitchMode(UI_CAMERA_STATE);
        break;
    #endif
    #if (MENU_GENERAL_BOOT_UP_TIMELAPSE_MODE_EN)
        case BOOT_UP_MODE_TIMELAPSE:
            m_ubDSCMode = DSC_TIME_LAPSE;
            StateSwitchMode(UI_CAMERA_STATE);
        break;
    #endif
    #if (MENU_GENERAL_BOOT_UP_WIFI_SWITCH_MODE_EN)
        case BOOT_UP_MODE_WIFI_SWITCH:
            StateSwitchMode(UI_VIDEO_STATE);
        break;
    #endif
    #if (MENU_GENERAL_BOOT_UP_6S_REC_MODE_EN)
        case BOOT_UP_MODE_6S_REC:
            StateSwitchMode(UI_VIDEO_STATE);
        break;
    #endif
        default:
            StateSwitchMode(UI_VIDEO_STATE);
        break;
    }
    #endif
#endif

    return AHC_TRUE;
}

static  int m_ulKeyWorking = 0;

int AHC_PauseKeyUI(void)
{
    m_ulKeyWorking++;
    return m_ulKeyWorking;
}

int AHC_ResumeKeyUI(void)
{
    if (m_ulKeyWorking == 0) {
        printc("!!!!! Pause/Resume isn't match!!!!!\r\n");
        return -1;
    }

    m_ulKeyWorking--;
    return m_ulKeyWorking;
}

int AHC_KeyUIWorking(void)
{
    return (m_ulKeyWorking == 0);
}

#if 0
void ____FileIO_Function_____(){ruturn;} //dummy
#endif

#define IS_LINE_ENDING(c)   ((c) == 0x0a || (c) == 0x0d)

int AHC_ReadlLine(UINT32 fd, char* buf, int size)
{
    AHC_BOOL    err;
    UINT32      out;
    int         i;

    i = 0;

    do {
        out = 0;

        err = AHC_FS_FileRead(fd, (unsigned char*)buf + i, 1, &out);

        if (err == 0 && out == 1)
        {
            if (IS_LINE_ENDING(*(buf + i)))
            {
                /* got line ending */
                if (i == 0)
                    continue;

                *(buf + i) = 0;
                break;
            }

            i++;

            if (i == size - 1)
            {
                /* line is too long, read and drop it */
                do {
                    out = 0;
                    err = AHC_FS_FileRead(fd, (unsigned char*)buf + i, 1, &out);

                    if (err == 0 && out == 1) {
                        if (IS_LINE_ENDING(*(buf + i)))
                            break;
                    } else {
                        break;
                    }
                } while (1);

                *(buf + i) = 0;
                break;
            }
        }
        else
        {
            *(buf + i) = 0;
            break;
        }

    } while (1);

    return i;
}

/*
 * fbuf: source buffer
 * fp  : source current index
 * fs  : soufce buffer size
 * outl: output buffer
 * size: output buffer size
 */
int AHC_ReadLineMem(char *fbuf, int* fp, int fs, char* outl, int size)
{
    int     i;

    i = 0;

    do {
        *(outl + i) = *(fbuf + *fp);

        (*fp)++;

        if (*fp < fs)
        {
            if (IS_LINE_ENDING(*(outl + i)))
            {
                /* got line ending */
                if (i == 0)
                    continue;

                *(outl + i) = 0;
                break;
            }

            i++;

            if (i == size - 1)
            {
                /* line is too long, read and drop it */
                do {
                    *(outl + i) = *(fbuf + *fp);

                    (*fp)++;
                    if (*fp < fs) {
                        if (IS_LINE_ENDING(*(outl + i)))
                            break;
                    } else {
                        break;
                    }
                } while (1);

                *(outl + i) = 0;
                break;
            }
        }
        else
        {
            *(outl + i) = 0;
            break;
        }

    } while (1);

    return i;
}

#if 0
void ____SDMMC_Function_____(){ruturn;} //dummy
#endif

UINT32 AHC_SDMMC_GetLockFileNum(void)
{
    AHC_BOOL        ahc_ret = AHC_TRUE;
    UINT32          MaxDcfObj, i;
    UINT32          CurrentObjIdx;
    UINT32          ulFileNum = 0;
    AHC_BOOL        bReadOnly;
    #if (PROTECT_FILE_TYPE == PROTECT_FILE_RENAME)
    AHC_BOOL        bDeleteFile;
    #endif
    INT8            byFileName[DCF_MAX_FILE_NAME_SIZE];

    if(!AHC_IsSDInserted()) {
        RTNA_DBG_Str(0, "SDMMC is not inseart\r\n");
        return 0;
    }

    MaxDcfObj = AHC_GetMappingFileNum(FILE_MOVIE);

    if(MaxDcfObj == 0) {
        RTNA_DBG_Str(0, "MaxDcfObj is 0\r\n");
        return 0;
    }

    AHC_UF_SetCurrentIndex(0);
    AHC_UF_InitLockFileTable();

    for(i=0;i<MaxDcfObj;i++)
    {
        AHC_UF_GetCurrentIndex(&CurrentObjIdx);
        ahc_ret = AHC_UF_IsReadOnlybyIndex(CurrentObjIdx, &bReadOnly);

        if(ahc_ret == AHC_FALSE) {
            printc(FG_RED("AHC_UF_IsReadOnlybyIndex error - %d\r\n"), ulFileNum);
            return ulFileNum;
        }

        if (bReadOnly)
        {
            ulFileNum++;
        }
        else {
            AHC_UF_GetFileNamebyIndex(CurrentObjIdx, byFileName);
        
            #if (PROTECT_FILE_TYPE == PROTECT_FILE_RENAME)
            if(memcmp(byFileName, FILE_RENAME_STRING, strlen(FILE_RENAME_STRING))==0)
            {
                ulFileNum++;
                AHC_UF_UpdateLockFileTable(CurrentObjIdx,&bDeleteFile);
                if(bDeleteFile == AHC_TRUE)
                {
                    CurrentObjIdx--;           //if delete lockfile Index would shift up 1 offset
                    MaxDcfObj--;
                    bDeleteFile = AHC_FALSE;
                }
            }
            #endif
        }
        
        CurrentObjIdx++;
        AHC_UF_SetCurrentIndex(CurrentObjIdx);
    }

    return ulFileNum;
}

#if 0
void ____PowerOn_Option_Function_____(){ruturn;} //dummy
#endif

void AHC_CancelQuickKey(int qk)
{
#if (POWER_ON_BUTTON_ACTION)
    m_ulQuickKey &= ~qk;
#endif
}

INT32 AHC_GetQuickKey(int qk)
{
#if (POWER_ON_BUTTON_ACTION)
    return m_ulQuickKey & qk;
#else
    return 0;
#endif
}

int AHC_SetQuickKey(int qk)
{
#if (POWER_ON_BUTTON_ACTION)
    if (m_usOption) {
        m_ulQuickKey |= qk;
    }
    return m_ulQuickKey;
#else
    return 0;
#endif
}

AHC_BOOL AHC_SetButtonStatus(UINT32 keyId)
{
#if (POWER_ON_BUTTON_ACTION)
    switch(keyId)
    {
    #ifdef CFG_KEY_POWER_ON_KEYSET_2 //may be defined in config_xxx.h
        case KEY_PRESS_FUNC2:
        case KEY_LPRESS_FUNC2:
    #else
        case KEY_LPRESS_REC:    //REC
        case KEY_PRESS_REC:
    #endif

            #ifdef CFG_BOOT_CUS_QUICK_KEY //may be defined in config_xxx.h, could be QUICK_REC
            AHC_SetQuickKey(CFG_BOOT_CUS_QUICK_KEY);
            #else
            AHC_SetQuickKey(QUICK_PCCAM);
            #endif
        break;


        case KEY_LPRESS_MENU:   //Menu
        case KEY_PRESS_MENU:
            AHC_SetQuickKey(QUICK_MENU);
        break;

        case KEY_LPRESS_MODE:   //Mode
        case KEY_PRESS_MODE:
            AHC_SetQuickKey(QUICK_MODE);
        break;


        case KEY_LPRESS_PLAY:   //Play
        case KEY_PRESS_PLAY:
            AHC_SetQuickKey(QUICK_PLAY);
        break;

        case KEY_LPRESS_UP:     //Up
        case KEY_PRESS_UP:
            AHC_SetQuickKey(QUICK_UP);
        break;

        case KEY_LPRESS_DOWN:   //Down
        case KEY_PRESS_DOWN:
            AHC_SetQuickKey(QUICK_DOWN);
        break;
    }
#endif
    return AHC_TRUE;
}

AHC_BOOL AHC_PowerOnOption(void)
{
#if (POWER_ON_BUTTON_ACTION)

    int     quick;

    quick = AHC_GetQuickKey(QUICK_ALL);


    if ((quick & QUICK_REC) ||
        (quick & QUICK_MENU))  //Show FW version or PCAM
    {
        if (quick & QUICK_MENU)
            printc("@@@ POWER_ON QUCIK MENU!!\r\n");

        if (quick & QUICK_REC)
            printc("@@@ POWER_ON QUCIK REC!!\r\n");

        #ifdef CFG_BOOT_QUICK_POWER_ON_MENU //may be defined in config_xxx.h
            AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_POWER_ON_MENU, 0);
        #endif
    }

    if (quick & QUICK_PLAY) //TBD
    {
        printc("POWER_ON QUCIK PLAY!!!\r\n");
    #ifdef CFG_BOOT_QUICK_POWER_ON_PLAY //may be defined in config_xxx.h
        AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_POWER_ON_PLAY, 0);
    #endif
    }

    if (quick & QUICK_MODE) //Format and Restore menu setting.
    {
        printc(">>> POWER_ON QUCIK MODE!!!\r\n");
    #ifdef CFG_BOOT_QUICK_POWER_ON_FORMAT //may be defined in config_xxx.h
        QuickMediaOperation(MEDIA_CMD_FORMAT);
        RestoreFromDefaultSetting();
    #endif
    }

    if (quick & QUICK_UP)   //Update FW
    {
        #if defined CFG_BOOT_QUICK_UPDATE_FW || defined CFG_BOOT_QUICK_UPDATE_FW_PER_USB //may be defined in config_xxx.h
        extern AHC_BOOL ubUpdateFWbySD;
        #endif

        printc(">>> POWER_ON QUCIK UP!!!\r\n");
        #ifdef CFG_BOOT_QUICK_UPDATE_FW //may be defined in config_xxx.h
            ubUpdateFWbySD = AHC_TRUE;
        #elif defined (CFG_BOOT_QUICK_UPDATE_FW_PER_USB)
            {
                if (AHC_FALSE == AHC_IsUsbConnect())
                    ubUpdateFWbySD = AHC_TRUE;
                else
                    AHC_SetQuickKey(QUICK_PCCAM);
            }
        #endif
    }

    if (quick & QUICK_DOWN)     //Format and Restore menu setting.
    {
        printc(">>> POWER_ON QUCIK DOWN!!!\r\n");
        #ifdef CFG_BOOT_QUICK_FORMAT_AND_OFF //may be defined in config_xxx.h
            LedCtrl_LcdBackLightLock(AHC_FALSE);
            #if (TVOUT_PREVIEW_EN)
            if(!AHC_IsTVConnectEx())
            #endif
                LedCtrl_LcdBackLight(AHC_TRUE);
            QuickMediaOperation(MEDIA_CMD_FORMAT);
            RestoreFromDefaultSetting();
            AHC_PowerOff_NormalPath();
        #endif
    }

    if (quick)
        PowerOnAction = AHC_TRUE;
    else
        PowerOnAction = AHC_FALSE;

    m_usOption = 0; // make AHC_SetQuickKey dummy
                    // avoid USB handler to refer qucik key to do PCCAM
    return PowerOnAction;

#else

    return AHC_FALSE;

#endif
}

#if 0
void ____USB_Function____(){ruturn;} //dummy
#endif

/*
 app == 1 for PCCAM
 app == 0 for MSDC
 */
void AHC_CheckUSB_KeyFile(char *kf, int app)
{
#if (USB_MODE_SELECT_EN == 0)
    MMP_ULONG   fd;
    MMP_ERR     err;

    err = MMPC_FS_FileOpen(kf, "r", (void **)&fd);
    printc("Open %s %d\r\n", kf, err);

    if (err == MMP_ERR_NONE) {
        MenuSettingConfig()->uiUSBFunction = (app == 1)? MENU_SETTING_USB_PCAM : MENU_SETTING_USB_MSDC;
        MMPC_FS_FileClose((void *)fd);
    } else {
        MenuSettingConfig()->uiUSBFunction = MENU_SETTING_USB_MSDC;
    }
    printc("Open %s %d USB is %s\r\n", kf, err, (MenuSettingConfig()->uiUSBFunction == MENU_SETTING_USB_PCAM)? "PCCAM" : "MSDC");

#endif
}

AHC_BOOL AHC_SetUSBLable(char *pszLable)
{
    if (pszLable) {
        FS_SetVolumeLabel("SD:0:\\", pszLable);
    }
    return AHC_TRUE;
}

// TY Miao - TBD
const char* AHC_GetVideoExt(void)
{
    UINT32  ct;

    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_CLIP_CONTAINER_TYPE, &ct);
    return (ct == VIDMGR_CONTAINER_3GP)? VR_3GP_EXT_FILENAME : "AVI";
}
