
/*===========================================================================
 * Include file
 *===========================================================================*/

#include "driving_safety.h"
#include "AHC_Config_SDK.h"
#include "ahc_gsensor.h"
#include "GSensor_ctrl.h"
#include "gps_ctl.h"

#if (DRIVING_SAFETY_ECODRIVE)
#include "EcoDrivingCal.h"
#endif
#include "MenuSetting.h"
#include "ahc_message.h"
#if (DRIVING_SAFETY_REMIND_HEADLIGHT)
#include "isp_if.h"
#endif
#include "ait_utility.h"
/*===========================================================================
 * Global variable
 *===========================================================================*/

#if 0//DRIVING_SAFETY_FATIGUE_ALERT
static MMP_ULONG    m_lCounterForFatigueAlert = 0;
static MMP_BOOL     m_bEnableFatigueAlertFunc = MMP_FALSE;
static MMP_BOOL     m_bEnableFatigueAlertNotify = MMP_FALSE;
#endif

#if (DRIVING_SAFETY_REMIND_HEADLIGHT)
static MMP_BOOL     m_bEnableRemindHeadlightFunc = MMP_FALSE;
static MMP_BOOL     m_bEnableRemindHeadlightNotify = MMP_FALSE;
#if (ENABLE_SHOWING_EXPOSURE_VALUE)
static MMP_ULONG    RecAvgLux;
MMP_ULONG    CurrentAvgLux;
#endif
#endif

#define RemindHeadlight_Thr1                (50)
#define RemindHeadlight_Thr2                (2800)

/*===========================================================================
 * Extern function
 *===========================================================================*/


/*===========================================================================
 * Main body
 *===========================================================================*/
#if ENABLE_RECORD_DEBUG_MSG
void Driving_Safety_WriteSDDEBugInfoFile(void)
{
    #define SIZE_STR_RECAVGLUX  (16)
    #define SIZE_WFILENAME      (64)

    AHC_ERR err;
    UINT32 ulFileId;
    UINT32 ulWriteCount;
    static UINT8 GenerateFileName = 0x00;
    static char wFileName[SIZE_WFILENAME], str_RecAvgLux[SIZE_STR_RECAVGLUX];

    if (!AHC_SDMMC_GetState())
        return;

    if (GenerateFileName == 0x00)
    {
        UINT32      CurObjIdx;
        AHC_RTC_TIME RtcTime;

        AHC_UF_GetCurrentIndex(&CurObjIdx);
        AHC_UF_GetFileTimebyIndex(CurObjIdx, &RtcTime);

        memset(wFileName, 0x00, SIZE_WFILENAME);
        sprintf( wFileName, "SD:\\%d-%d-%d-%d-%d_HeadLight.ait", RtcTime.uwYear, RtcTime.uwMonth, RtcTime.uwDay, RtcTime.uwHour, RtcTime.uwMinute );

        GenerateFileName = 0x01;

        err = AHC_FS_FileOpen(wFileName,
                        AHC_StrLen(wFileName),
                        "w",
                        AHC_StrLen("w"),
                        &ulFileId);
    }
    else
    {
        err = AHC_FS_FileOpen(wFileName,
                        AHC_StrLen(wFileName),
                        "a",
                        AHC_StrLen("a"),
                        &ulFileId);
    }

    #if (ENABLE_RECORD_DEBUG_MSG_TYPE == ENABLE_RECORD_DEBUG_MSG_VIA_TXT)
    if(err == AHC_ERR_NONE){
        memset(str_RecAvgLux, 0x00, SIZE_STR_RECAVGLUX);
        sprintf( str_RecAvgLux, "%u\t%u\t%d\r\n", CurrentAvgLux, RecAvgLux, ((m_bEnableRemindHeadlightNotify&0x03)==0x03));
        AHC_FS_FileWrite(ulFileId, str_RecAvgLux, SIZE_STR_RECAVGLUX, &ulWriteCount);
        AHC_FS_FileClose(ulFileId);
    }
    #elif (ENABLE_RECORD_DEBUG_MSG_TYPE == ENABLE_RECORD_DEBUG_MSG_VIA_BIN)
    if(err == AHC_ERR_NONE){
        memset(str_RecAvgLux, 0x00, SIZE_STR_RECAVGLUX);
        sprintf( str_RecAvgLux, "%u\t%u\t%d\r\n", CurrentAvgLux, RecAvgLux, ((m_bEnableRemindHeadlightNotify&0x03)==0x03));
        AHC_FS_FileWrite(ulFileId, str_RecAvgLux, SIZE_STR_RECAVGLUX, &ulWriteCount);
        AHC_FS_FileClose(ulFileId);
    }
    #endif
}
#endif

MMP_ULONG Driving_Safety_GetAvgLux(void)
{
    #if (ENABLE_SHOWING_EXPOSURE_VALUE)
    return RecAvgLux;
    #endif

    return 0xFFFFFFFF;
}

MMP_BOOL Driving_Safety_IsRemindHeadlightNotify(void)
{
    #if (DRIVING_SAFETY_REMIND_HEADLIGHT)
        if (m_bEnableRemindHeadlightNotify&0x02)
            return m_bEnableRemindHeadlightNotify&0x01;
        else
            return 0x00;
    #endif
        return MMP_FALSE;
    }


void Driving_Safety_IsRemindHeadlightProcDoneNotify(MMP_BOOL bEnable)
{
    #if (DRIVING_SAFETY_REMIND_HEADLIGHT)
    if (bEnable)
        m_bEnableRemindHeadlightNotify &= (~0x02);
    else
        m_bEnableRemindHeadlightNotify |= 0x02;
    #endif
}

void Driving_Safety_RemindHeadlightEnable(MMP_BOOL bEnable)
{
    #if (DRIVING_SAFETY_REMIND_HEADLIGHT)
    m_bEnableRemindHeadlightFunc = bEnable;
    #endif
}

MMP_BOOL Driving_Safety_GetState_RemindHeadlightEnable(void)
{
    #if (DRIVING_SAFETY_REMIND_HEADLIGHT)
    return m_bEnableRemindHeadlightFunc;
    #endif

    return MMP_FALSE;
}

MMP_BOOL Driving_Safety_Calculate_RemindHeadlight(MMP_BYTE Oprt, MMP_ULONG *GetAvgLux)
{
    #if (DRIVING_SAFETY_REMIND_HEADLIGHT)
    #define EN_CLIP_VAR             (0)
    static UINT32 Lux_Sum = 0;
    static UINT8 Lux_Cnt = 0;
    UINT8 OprtAccur = 3;
    /* Lux_Clp must be larger than ThrLux2 */
    UINT32 Lux_Clp = 0xFFFFFFFF;
    UINT32 Lux_Cur = ISP_IF_AE_GetLightCond();
    #if (ENABLE_SHOWING_EXPOSURE_VALUE)
    CurrentAvgLux = Lux_Cur;
    #endif

    #if 0
    *GetAvgLux = Lux_Cur;
    return MMP_TRUE;

    #else
    if (!Oprt) {
        Lux_Cnt = 0;
        Lux_Sum = 0;
    }
    if (Lux_Cnt>>OprtAccur)
        Lux_Sum -= (Lux_Sum>>OprtAccur);
    else
        Lux_Cnt++;

    #if (EN_CLIP_VAR)
    if (Lux_Cur > Lux_Clp)
        Lux_Sum += Lux_Clp;
    else
    #endif
        Lux_Sum += Lux_Cur;

    if (!(Lux_Cnt>>OprtAccur))
        return MMP_FALSE;

    if (Oprt)
        *GetAvgLux = (Lux_Sum>>OprtAccur);

    return MMP_TRUE;
    #endif
    #endif
    return MMP_FALSE;
}

MMP_BOOL Driving_Safety_RemindHeadlightCheck(void)
{
    #if (DRIVING_SAFETY_REMIND_HEADLIGHT)
    static MMP_ULONG GetAvgLux;


    if (!Driving_Safety_Calculate_RemindHeadlight(0x01, &GetAvgLux))
        return MMP_FALSE;


    #if (ENABLE_SHOWING_EXPOSURE_VALUE)
    RecAvgLux = GetAvgLux;
    #endif

    #if (ENABLE_RECORD_DEBUG_MSG)
    Driving_Safety_WriteSDDEBugInfoFile();
    #endif

    if ((!m_bEnableRemindHeadlightFunc)||(MenuSettingConfig()->uiRemindLight == REMIND_LIGHT_OFF))
        return MMP_FALSE;

    if (GetAvgLux <= RemindHeadlight_Thr1)
        m_bEnableRemindHeadlightNotify |= 0x01;
    else
        m_bEnableRemindHeadlightNotify &= (~0x01);
    if (GetAvgLux >= RemindHeadlight_Thr2)
        m_bEnableRemindHeadlightNotify |= 0x02;

    return MMP_TRUE;
    #endif

    return MMP_FALSE;
}

MMP_BOOL Driving_Safety_EcoDrive(void)
{
    #if DRIVING_SAFETY_ECODRIVE
    #endif
    return 0;
}

MMP_LONG Driving_Safety_CheckEcoDriveLevel(void)
{
    #if DRIVING_SAFETY_ECODRIVE
    #define STATUS_CHECK_COUNT 5
    AHC_GSENSOR_DATA    sdata = {0, 0, 0};
    MMP_ERR             err;
    MMP_LONG            lReturn = 0;
    static MMP_LONG     lLastStatus = 0;
    static MMP_UBYTE    ubCount = STATUS_CHECK_COUNT;

    AHC_Gsensor_Read_XYZ(&sdata);

    lReturn = EcoDrivingCal(sdata.acc_val[0]/1000.0, sdata.acc_val[1]/1000.0, sdata.acc_val[2]/1000.0, MMP_FALSE, 0);
    //printc("EcoDriveLevel : %d\r\n",lReturn);

    if(lReturn == -1)
    {
        if(ubCount)
        {
            ubCount--;
            lLastStatus = 0;
            return lLastStatus; //0: means Green
        }else
        {
            ubCount = STATUS_CHECK_COUNT;
            return lLastStatus;
        }

    }else
    {
        lLastStatus = lReturn;
        ubCount = STATUS_CHECK_COUNT;
        return lReturn;
    }

    #else
    return 0;
    #endif
}

#if (ENABLE_ADAS_LDWS)

static ldws_params_t m_LDWS_Param = {0};
static UINT32 m_LDWSSpeed = 80; // Km.
static MMP_BOOL m_bLDWSStart = MMP_FALSE;

#if 0
static UINT32 LDWS_GetSpeed(void)
{
    // Return the speed at the time LDWS was trigged.
    return m_LDWSSpeed;
}
#endif
MMP_BOOL LDWS_IsStart(void)
{
    return m_bLDWSStart;
}

void LDWS_Lock(void)
{
    m_bLDWSStart = MMP_TRUE;
}

void LDWS_Unlock(void)
{
    m_bLDWSStart = MMP_FALSE;
}

void LDWS_GetResult(ldws_params_t* pLDWS_Param)
{
    if (pLDWS_Param != NULL)
        memcpy(pLDWS_Param, &m_LDWS_Param, sizeof(ldws_params_t));
}

#if 1 //TBD
#define LDWS_TEST_FORCE_SPEED   (70)

void LDWS_Callback(const void * pADAS_Param,ADAS_CALL_BK_TYPE type)
{
//#if (SUPPORT_ADAS_LDWS)
#if (ENABLE_ADAS_LDWS)
    if(type == ADAS_CALL_BK_LDWS)
#else
    if(0)
#endif
    {
        printc("[ADAS_CALL_BK_LDWS]");
        if (LDWS_IsStart() == MMP_TRUE)
        {
            printc("[2]");
            return;
        }

        #if 0//(SUPPORT_GPS)
        if (MenuSettingConfig()->uiDistanceUnit == DISTANCE_UNIT_METRIC)
        {
            m_LDWSSpeed = GPSCtrl_GetSpeed(0);
        }
        else if (MenuSettingConfig()->uiDistanceUnit == DISTANCE_UNIT_IMPERIAL)
        {
            int speed;

            speed = (GPSCtrl_GetSpeed(1)*161-80)/100; // miles converted to km
            if (speed < 0)
                m_LDWSSpeed = 0;
            else
                m_LDWSSpeed = speed;
        }
        #endif

        #ifdef LDWS_TEST_FORCE_SPEED
        #if (!GPS_CONFIG_NMEA_FILE)
        m_LDWSSpeed = LDWS_TEST_FORCE_SPEED;
        #endif
        #endif
        {
            UINT32 bLDWS_En;
             AHC_Menu_SettingGetCB( (char *)COMMON_KEY_LDWS_EN, &bLDWS_En );

            if ((m_LDWSSpeed < LDWS_WARN_SPEED) || (bLDWS_En == REMIND_LDWS_OFF))
            {
                LDWS_Unlock();
                return;
            }
        }
        LDWS_Lock();
        memcpy(&m_LDWS_Param, pADAS_Param, sizeof(ldws_params_t));
        AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_LDWS_START, 0);
    }
#if(SUPPORT_ADAS_FCWS)
    else if(type == ADAS_CALL_BK_FCWS)
    {
        printc("[ADAS_CALL_BK_FCWS]");
        //AHC_PlaySoundEffect(AHC_SOUNDEFFECT_SPCAMWARN);
        AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_FCWS_START, 0);
    }
#endif
#if(SUPPORT_ADAS_SAG)
    else if(type == ADAS_CALL_BK_SAG)
    {
        AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_SAG_START, 0);
    }
#endif
    else if(type == ADAS_CALL_BK_WRITE_LOG)
    {
        printc("ADAS_CALL_BK_WRITE_LOG\n");
        AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_ADAS_WRITE_LOG, 0);
    }
}
#else
void LDWS_Callback(const ldws_params_t* pLDWS_Param)
{
    if (LDWS_IsStart() == MMP_TRUE)
        return;

    #if (SUPPORT_GPS)
    if (MenuSettingConfig()->uiDistanceUnit == DISTANCE_UNIT_METRIC)
    {
        m_LDWSSpeed = GPSCtrl_GetSpeed(0);
    }
    else if (MenuSettingConfig()->uiDistanceUnit == DISTANCE_UNIT_IMPERIAL)
    {
        int speed;

        speed = (GPSCtrl_GetSpeed(1)*161-80)/100;
        if (speed < 0)
            m_LDWSSpeed = 0;
        else
            m_LDWSSpeed = speed;
    }
    #endif

    if (m_LDWSSpeed < LDWS_WARN_SPEED /*|| MenuSettingConfig()->uiLDWSAlertType == LDWS_ALERT_METHOD_OFF*/)
    {
        LDWS_Unlock();
        return;
    }
    LDWS_Lock();

    memcpy(&m_LDWS_Param, pLDWS_Param, sizeof(ldws_params_t));
    AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_LDWS_START, 0);
}
#endif
#endif // #if (ENABLE_ADAS_LDWS)
