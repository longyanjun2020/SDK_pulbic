//==============================================================================
//
//  File        : AHC_RTC.c
//  Description : AHC RTC control function
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "Customer_config.h"
#include "ahc_rtc.h"
//#include "mmp_lib.h"
//#include "mmp_err.h"
#include "lib_retina.h"
#include "ait_utility.h"
#include "mmps_rtc.h"
#include "ahc_parameter.h"
#include "AHC_Config_SDK.h"
#include "ahc_datetime.h"
#include "ahc_utility.h"
#include "ahc_usbhost.h"
#include "ahc_fs.h"
#include "gps_ctl.h"

/*===========================================================================
 * Global varible
 *===========================================================================*/ 
extern AHC_BOOL gbBlockRealIDUIKeyTask;

#if (RTC_FORCE_DEFAULT_TIME == 1) // It's used when external RTC without driver, but we still want to test video record with DateTime file name.
static AHC_RTC_TIME m_sRTCTime = {2011, 1, 1, 0, 0, 0, 0, 0, 0};
#else
static AHC_RTC_TIME m_sRTCTime = {0};
#endif

static AHC_BOOL     m_bUpdateRelativeTime = AHC_FALSE;

#if (RTC_CHECK_SF_BASETIME)
static ULONG        m_ulBaseTimeInSeconds_SF;
#endif

#if (RTC_CHECK_INTERVAL)
static UINT32  m_ulRtcOsTimeInterval = 0;
#endif

DSTDuration DST_GMT_P00[7] ={
                                {{13, 3, 31, 1}, {13, 10, 27, 1}},
                                {{14, 3, 30, 1}, {14, 10, 26, 1}},
                                {{15, 3, 29, 1}, {15, 10, 25, 1}},
                                {{16, 3, 27, 1}, {16, 10, 30, 1}},
                                {{17, 3, 26, 1}, {17, 10, 29, 1}},
                                {{18, 3, 25, 1}, {18, 10, 28, 1}},
                                {{19, 3, 31, 1}, {19, 10, 27, 1}}
                            };

DSTDuration DST_GMT_P10[7] ={
                                {{13, 10, 6, 2}, {14, 4, 6, 2}},
                                {{14, 10, 5, 2}, {15, 4, 5, 2}},
                                {{15, 10, 4, 2}, {16, 4, 3, 2}},
                                {{16, 10, 2, 2}, {17, 4, 2, 2}},
                                {{17, 10, 1, 2}, {18, 4, 1, 2}},
                                {{18, 10, 7, 2}, {19, 4, 7, 2}},
                                {{19, 10, 6, 2}, {20, 4, 1, 2}}
                            };

DSTDuration DST_GMT_P02[7] ={
                                {{13, 3, 29, 2}, {13, 10, 27, 1}},
                                {{14, 3, 28, 2}, {14, 10, 26, 1}},
                                {{15, 3, 27, 2}, {15, 10, 25, 1}},
                                {{16, 3, 25, 2}, {16, 10, 30, 1}},
                                {{17, 3, 24, 2}, {17, 10, 29, 1}},
                                {{18, 3, 23, 2}, {18, 10, 28, 1}},
                                {{19, 3, 29, 2}, {19, 10, 27, 1}}
                            };

/*===========================================================================
 * Main body
 *===========================================================================*/

#if 0
void _____RTC_Function_________(){ruturn;} //dummy
#endif

#if (RTC_CHECK_INTERVAL)
//------------------------------------------------------------------------------
//  Function    : AHC_RTC_SetOSTimeInterval
//  Description : 
//------------------------------------------------------------------------------
void AHC_RTC_SetOSTimeInterval(ULONG32 ulSec) 
{
    m_ulRtcOsTimeInterval = ulSec;
}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_RTC_CheckBaseTime
//  Description : 
//------------------------------------------------------------------------------
AHC_BOOL AHC_RTC_CheckBaseTime(void)
{
#if (RTC_CHECK_SF_BASETIME)
    AHC_ERR err;
    UINT32 ulFileId;
    UINT32 ulReadCount;
    MMP_ULONG ulRTCBaseTime;

    if(m_ulBaseTimeInSeconds_SF == 0) {
        err = AHC_FS_FileOpen(RTC_BASETIME_FILE_NAME, STRLEN(RTC_BASETIME_FILE_NAME), "r", sizeof("r"), &ulFileId);
        if (err == AHC_ERR_NONE)
        {
            AHC_FS_FileSeek(ulFileId, 0, AHC_FS_SEEK_SET);
            AHC_FS_FileRead(ulFileId, (UINT8 *)&m_ulBaseTimeInSeconds_SF, sizeof(m_ulBaseTimeInSeconds_SF), &ulReadCount);
            AHC_FS_FileClose(ulFileId);
        }
        else {
            AHC_DBG_ERR(0, "RTC Error: RTCBaseTime.txt open fail!\r\n");
            AHC_FS_FileClose(ulFileId);
            return AHC_FALSE;
        }
    }

    if(m_ulBaseTimeInSeconds_SF) {
        MMPF_RTC_CTL_Read_BaseTime(&ulRTCBaseTime);
        if(m_ulBaseTimeInSeconds_SF != ulRTCBaseTime) {
            AHC_DBG_ERR(1, "RTC Error: Check BaseTime Fail! SF:0x%X  RTC:0x%X\n", m_ulBaseTimeInSeconds_SF, ulRTCBaseTime);
            return AHC_FALSE;
        }
    }
#endif

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_RTC_UpdateTime
//  Description : 
//------------------------------------------------------------------------------
AHC_BOOL AHC_RTC_UpdateTime(void)
{
    MMP_ERR status;
    AUTL_DATETIME scur_rtc_time;
    #if (RTC_CHECK_INTERVAL)
    UINT32      ulRTCSecondsOffset;
    UINT32      ulOSSecondsOffset;
    UINT32      ulSecondsOffsetInterval;
    MMP_ULONG   ulOSTickCount;
    AHC_RTC_TIME RtcTime;
    #endif 

    if(gbBlockRealIDUIKeyTask)
        return AHC_FALSE;

    status = MMPS_RTC_GetTime(&scur_rtc_time);

    #if (RTC_CHECK_INTERVAL)
    if(m_ulRtcOsTimeInterval) {
        ulRTCSecondsOffset = AHC_DT_GetSecondsOffset(scur_rtc_time.usYear, scur_rtc_time.usMonth, scur_rtc_time.usDay, scur_rtc_time.usHour, scur_rtc_time.usMinute, scur_rtc_time.usSecond);
        MMPF_OS_GetTime(&ulOSTickCount);
        ulOSSecondsOffset = (ulOSTickCount/1000) + m_ulRtcOsTimeInterval;
        if(ulRTCSecondsOffset > ulOSSecondsOffset) {
            ulSecondsOffsetInterval = ulRTCSecondsOffset - ulOSSecondsOffset;
            if(ulSecondsOffsetInterval > RTC_MAX_INTERVAL) {
                AHC_DT_SecondsToDateTime(ulOSSecondsOffset, &RtcTime);
                AHC_DBG_ERR(1, "RTC Error: %2d %2d %2d - %2d:%2d:%2d  ulSecondsOffsetInterval=%d\r\n", RtcTime.uwYear, RtcTime.uwMonth, RtcTime.uwDay, RtcTime.uwHour, RtcTime.uwMinute, RtcTime.uwSecond, ulSecondsOffsetInterval);
                scur_rtc_time.usYear = RtcTime.uwYear;
                scur_rtc_time.usMonth = RtcTime.uwMonth;
                scur_rtc_time.usDay = RtcTime.uwDay;
                scur_rtc_time.usHour = RtcTime.uwHour;
                scur_rtc_time.usMinute = RtcTime.uwMinute;
                scur_rtc_time.usSecond = RtcTime.uwSecond;
                MMPS_RTC_SetTime(&scur_rtc_time);
            }
        }
        else {
            ulSecondsOffsetInterval = ulOSSecondsOffset - ulRTCSecondsOffset;
            if(ulSecondsOffsetInterval > RTC_MAX_INTERVAL) {
                AHC_DT_SecondsToDateTime(ulOSSecondsOffset, &RtcTime);
                AHC_DBG_ERR(1, "RTC Error: %2d %2d %2d - %2d:%2d:%2d  ulSecondsOffsetInterval=%d\r\n", RtcTime.uwYear, RtcTime.uwMonth, RtcTime.uwDay, RtcTime.uwHour, RtcTime.uwMinute, RtcTime.uwSecond, ulSecondsOffsetInterval);
                scur_rtc_time.usYear = RtcTime.uwYear;
                scur_rtc_time.usMonth = RtcTime.uwMonth;
                scur_rtc_time.usDay = RtcTime.uwDay;
                scur_rtc_time.usHour = RtcTime.uwHour;
                scur_rtc_time.usMinute = RtcTime.uwMinute;
                scur_rtc_time.usSecond = RtcTime.uwSecond;
                MMPS_RTC_SetTime(&scur_rtc_time);
            }
        }
    }
    #endif

    if (status != MMP_ERR_NONE) {
        return AHC_FALSE;
    }

    MEMCPY((void *)&m_sRTCTime, (void *)&scur_rtc_time, sizeof(AHC_RTC_TIME));
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_RTC_DSTCheck_GMT
//  Description : 
//------------------------------------------------------------------------------
AHC_BOOL AHC_RTC_DSTCheck_GMT(const UINT32 uiYear, const UINT32 uiMon, const UINT32 uiDay, const UINT32 uiHour)
{
    UINT8   ubSize = 0;
    UINT8   i = 0;
    UINT32  uiCurTime = 0;
    UINT32  uiStartTime = 0;
    UINT32  uiEndTime = 0;
    pDSTDuration DSTZone = NULL;

    if (uiYear >= 2000)
    {
        uiCurTime = ((uiYear - 2000 & 0xFF) << 24   )   | \
                    ((uiMon         & 0xFF) << 16   )   | \
                    ((uiDay         & 0xFF) << 8    )   | \
                    ((uiHour        & 0xFF) << 0    );
    }
    else
    {
        uiCurTime = ((uiYear        & 0xFF) << 24   )   | \
                    ((uiMon         & 0xFF) << 16   )   | \
                    ((uiDay         & 0xFF) << 8    )   | \
                    ((uiHour        & 0xFF) << 0    );
    }

    switch(DST_TIMEZONE)
    {
        case 0:
            DSTZone = DST_GMT_P00;
        break;
        case 8:
            DSTZone = DST_GMT_P02;
        break;
        case 40:
            DSTZone = DST_GMT_P10;
        break;
    }

    if (DSTZone == NULL) //No need DST
        return 0;

    ubSize = sizeof(DST_GMT_P00)/sizeof(DSTDuration);

    for (i = 0; i < ubSize; i++)
    {
        uiStartTime =   ((DSTZone[i].sStart.uiYear  & 0xFF) << 24   )   | \
                        ((DSTZone[i].sStart.uiMon   & 0xFF) << 16   )   | \
                        ((DSTZone[i].sStart.uiDay   & 0xFF) << 8    )   | \
                        ((DSTZone[i].sStart.uiHour  & 0xFF) << 0    );

        uiEndTime =     ((DSTZone[i].sEnd.uiYear    & 0xFF) << 24   )   | \
                        ((DSTZone[i].sEnd.uiMon     & 0xFF) << 16   )   | \
                        ((DSTZone[i].sEnd.uiDay     & 0xFF) << 8    )   | \
                        ((DSTZone[i].sEnd.uiHour    & 0xFF) << 0    );

        if (uiCurTime < uiEndTime && uiCurTime >= uiStartTime)
        {
            return 1;
        }
    }

    return 0;
}

//------------------------------------------------------------------------------
//  Function    : AHC_RTC_DSTCheck_UserSet
//  Description : 
//------------------------------------------------------------------------------
AHC_BOOL AHC_RTC_DSTCheck_UserSet(const UINT32 uiYear, const UINT32 uiMon, const UINT32 uiDay, const UINT32 uiHour)
{
    UINT8   ubSize = 0;
    UINT8   i = 0;
    UINT32  uiCurTime = 0;
    UINT32  uiStartTime = 0;
    UINT32  uiEndTime = 0;
    pDSTDuration DSTZone = NULL;

    if (uiYear >= 2000)
    {
        uiCurTime = ((uiYear - 2000 & 0xFF) << 24   )   | \
                    ((uiMon         & 0xFF) << 16   )   | \
                    ((uiDay         & 0xFF) << 8    )   | \
                    ((uiHour        & 0xFF) << 0    );
    }
    else
    {
        uiCurTime = ((uiYear        & 0xFF) << 24   )   | \
                    ((uiMon         & 0xFF) << 16   )   | \
                    ((uiDay         & 0xFF) << 8    )   | \
                    ((uiHour        & 0xFF) << 0    );
    }

    switch(DST_TIMEZONE)
    {
        case 0:
            DSTZone = DST_GMT_P00;
        break;
        case 8:
            DSTZone = DST_GMT_P02;
        break;
        case 40:
            DSTZone = DST_GMT_P10;
        break;
    }

    if (DSTZone == NULL)//No need DST
        return 0;

    ubSize = sizeof(DST_GMT_P00)/sizeof(DSTDuration);

    for (i = 0; i < ubSize; i++)
    {
        uiStartTime =   ((DSTZone[i].sStart.uiYear  & 0xFF) << 24   )   | \
                        ((DSTZone[i].sStart.uiMon   & 0xFF) << 16   )   | \
                        ((DSTZone[i].sStart.uiDay   & 0xFF) << 8    )   | \
                        ((DSTZone[i].sStart.uiHour  & 0xFF) << 0    );

        uiEndTime =     ((DSTZone[i].sEnd.uiYear    & 0xFF) << 24   )   | \
                        ((DSTZone[i].sEnd.uiMon     & 0xFF) << 16   )   | \
                        ((DSTZone[i].sEnd.uiDay     & 0xFF) << 8    )   | \
                        ((DSTZone[i].sEnd.uiHour    & 0xFF) << 0    );

        if (uiCurTime <= uiEndTime && uiCurTime > uiStartTime)
        {
            return 1;
        }
    }

    return 0;
}

//------------------------------------------------------------------------------
//  Function    : AHC_RTC_DSTTimeOffset
//  Description : 
//------------------------------------------------------------------------------
void AHC_RTC_DSTTimeOffset(DSTFullTime *sBackup, DSTFullTime *sRes, signed char sbOffset)
{
    INT lBackupYear,lBackupDay,lBackupHour,lBackupMin;
    signed char byHour = sbOffset/4;
    signed char byMinute = (sbOffset%4)*15;

    if (sBackup->iYear == 0 ||  sBackup->iMon == 0 ||  sBackup->iDay == 0) {
        return;
    }
    
    if (byHour < -12)
        byHour = -12;
    else if (byHour > 13)
        byHour = 13;

    lBackupYear = sBackup->iYear;
    lBackupDay  = sBackup->iDay;
    lBackupHour = sBackup->iHour;
    lBackupMin  = sBackup->iMin;

    if (byMinute != 0)
    {
        sBackup->iMin = ((sBackup->iMin + byMinute)%60);

        if ((lBackupMin + byMinute) > 60)
        {
            if (sBackup->iHour != 23)
            {
                sBackup->iHour +=1;
            }
            else
            {
                sBackup->iHour = 0;
                
                if (sBackup->iMon != 2)
                {
                    switch(sBackup->iDay)
                    {
                        case 30:
                            switch(sBackup->iMon)
                            {
                                case 4:
                                case 6:
                                case 9:
                                case 11:
                                    sBackup->iDay = 1;
                                    sBackup->iMon += 1;
                                break;
                                default:
                                    sBackup->iDay += 1;
                                break;
                            }
                        break;
                        case 31:
                            switch(sBackup->iMon)
                            {
                                case 12:
                                    sBackup->iDay = 1;
                                    sBackup->iMon = 1;
                                    sBackup->iYear += 1;
                                break;
                                default:
                                    sBackup->iDay = 1;
                                    sBackup->iMon += 1;
                                break;
                            }
                        break;
                        default:
                            sBackup->iDay += 1;
                        break;
                    }
                }
                else
                {
                    switch(sBackup->iDay)
                    {
                        case 29:
                            sBackup->iDay = 1;
                            sBackup->iMon += 1;
                        break;
                        case 28:
                            if((sBackup->iYear%400==0))
                            {
                                sBackup->iDay += 1;
                            }
                            else if((sBackup->iYear%4 == 0)&&(sBackup->iYear%100 != 0))
                            {
                                sBackup->iDay += 1;
                            }
                            else
                            {
                                sBackup->iDay = 1;
                                sBackup->iMon += 1;
                            }
                        break;
                        default:
                            sBackup->iDay += 1;
                        break;
                    }
                }
            }
        }
        else if ((lBackupMin + byMinute)<0)
        {
            if (sBackup->iHour > 0)
            {
                sBackup->iHour -=1;
            }
            else if (sBackup->iHour == 0)
            {
                sBackup->iHour = 23;

                if (sBackup->iDay != 1)
                {
                    sBackup->iDay -= 1;
                }
                else if (sBackup->iDay == 1)
                {
                    if (sBackup->iMon == 3)
                    {
                        if ((sBackup->iYear%400==0))
                        {
                            sBackup->iMon = 2;
                            sBackup->iDay = 29;
                        }
                        else if ((sBackup->iYear%4 == 0) && (sBackup->iYear%100 != 0))
                        {
                            sBackup->iMon = 2;
                            sBackup->iDay = 29;
                        }
                        else
                        {
                            sBackup->iMon = 2;
                            sBackup->iDay = 28;
                        }
                    }
                    else
                    {
                        switch(sBackup->iMon)
                        {
                            case 1:
                                sBackup->iYear -= 1;
                                sBackup->iMon = 12;
                                sBackup->iDay = 31;
                            break;
                            case 3:
                            case 5:
                            case 7:
                            case 8:
                            case 10:
                            case 12:
                                sBackup->iMon -= 1;
                                sBackup->iDay = 30;
                            break;
                            case 2:
                            case 4:
                            case 6:
                            case 9:
                            case 11:
                                sBackup->iMon -= 1;
                                sBackup->iDay = 31;
                            break;

                        }
                    }
                }
            }
        }
    }

    if ((sBackup->iHour + byHour) >= 24)
    {
        sBackup->iHour = ((sBackup->iHour + byHour)%24);

        if (sBackup->iMon != 2)
        {
            switch(sBackup->iDay)
            {
                case 30:
                    switch(sBackup->iMon)
                    {
                        case 4:
                        case 6:
                        case 9:
                        case 11:
                            sBackup->iDay = 1;
                            sBackup->iMon += 1;
                        break;
                        default:
                            sBackup->iDay += 1;
                        break;
                    }
                break;
                case 31:
                    switch(sBackup->iMon)
                    {
                        case 12:
                            sBackup->iDay = 1;
                            sBackup->iMon = 1;
                            sBackup->iYear += 1;
                        break;
                        default:
                            sBackup->iDay = 1;
                            sBackup->iMon += 1;
                        break;
                    }
                break;
                default:
                    sBackup->iDay += 1;
                break;
            }
        }
        else
        {
            switch(sBackup->iDay)
            {
                case 29:
                    sBackup->iDay = 1;
                    sBackup->iMon += 1;
                break;
                case 28:
                    if ((sBackup->iYear%400==0))
                    {
                        sBackup->iDay += 1;
                    }
                    else if ((sBackup->iYear%4 == 0)&&(sBackup->iYear%100 != 0))
                    {
                        sBackup->iDay += 1;
                    }
                    else
                    {
                        sBackup->iDay = 1;
                        sBackup->iMon += 1;
                    }
                break;
                default:
                    sBackup->iDay += 1;
                break;
            }
        }
    }
    else if ((sBackup->iHour + byHour) < 0)
    {
        sBackup->iHour = ((sBackup->iHour + 24 + byHour));

        if (sBackup->iDay != 1)
        {
            sBackup->iDay -= 1;
        }
        else if(sBackup->iDay == 1)
        {
            if (sBackup->iMon == 3)
            {
                if ((sBackup->iYear%400==0))
                {
                    sBackup->iMon = 2;
                    sBackup->iDay = 29;
                }
                else if ((sBackup->iYear%4 == 0)&&(sBackup->iYear%100 != 0))
                {
                    sBackup->iMon = 2;
                    sBackup->iDay = 29;
                }
                else
                {
                    sBackup->iMon = 2;
                    sBackup->iDay = 28;
                }
            }
            else
            {
                switch(sBackup->iMon)
                {
                    case 1:
                        sBackup->iYear -= 1;
                        sBackup->iMon = 12;
                        sBackup->iDay = 31;
                    break;
                    case 3:
                    case 5:
                    case 7:
                    case 10:
                    case 12:
                        sBackup->iMon -= 1;
                        sBackup->iDay = 30;
                    break;
                    case 2:
                    case 4:
                    case 6:
                    case 8:
                    case 9:
                    case 11:
                        sBackup->iMon -= 1;
                        sBackup->iDay = 31;
                    break;
                }
            }
        }
    }
    else
    {
        sBackup->iHour += byHour;
    }

    sRes->iYear = sBackup->iYear;
    sRes->iMon  = sBackup->iMon ;
    sRes->iDay  = sBackup->iDay;
    sRes->iHour = sBackup->iHour;
    sRes->iMin  = sBackup->iMin ;
    sRes->iSec  = sBackup->iSec ;

    sBackup->iYear  = lBackupYear;
    sBackup->iDay   = lBackupDay;
    sBackup->iHour  = lBackupHour;
    sBackup->iMin   = lBackupMin;
}

//------------------------------------------------------------------------------
//  Function    : AHC_RTC_DayLightSavingEnable
//  Description : 
//------------------------------------------------------------------------------
void AHC_RTC_DayLightSavingEnable(AHC_BOOL bEnable)
{
    if (bEnable) {
        m_bUpdateRelativeTime = AHC_TRUE;
    }
    else {
        m_bUpdateRelativeTime = AHC_FALSE;
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_RTC_GetTimeEx
//  Description : 
//------------------------------------------------------------------------------
void AHC_RTC_GetTimeEx(AHC_RTC_TIME *psAHC_RTC_Time, AHC_BOOL bUpdateRelativeTime)
{
    AHC_RTC_TIME sAHC_RTC_TempTime = {0};
    
    if (!bUpdateRelativeTime)
    {
        *psAHC_RTC_Time = m_sRTCTime;
    }

    if (AHC_RTC_DSTCheck_GMT(m_sRTCTime.uwYear, m_sRTCTime.uwMonth, m_sRTCTime.uwDay, m_sRTCTime.uwHour))
    {
        DSTFullTime sTime = {0};
        DSTFullTime sOffsetTime = {0};

        sTime.iYear = m_sRTCTime.uwYear;
        sTime.iMon  = m_sRTCTime.uwMonth;
        sTime.iDay  = m_sRTCTime.uwDay;
        sTime.iHour = m_sRTCTime.uwHour;
        sTime.iMin  = m_sRTCTime.uwMinute;
        sTime.iSec  = m_sRTCTime.uwSecond;

        AHC_RTC_DSTTimeOffset(&sTime, &sOffsetTime, 4); //Add one hour

        sAHC_RTC_TempTime.uwYear   = sOffsetTime.iYear;
        sAHC_RTC_TempTime.uwMonth  = sOffsetTime.iMon;
        sAHC_RTC_TempTime.uwDay    = sOffsetTime.iDay;
        sAHC_RTC_TempTime.uwHour   = sOffsetTime.iHour;
        sAHC_RTC_TempTime.uwMinute = sOffsetTime.iMin;
        sAHC_RTC_TempTime.uwSecond = sOffsetTime.iSec;
    }
    else
    {
        sAHC_RTC_TempTime = m_sRTCTime;
    }

    *psAHC_RTC_Time = sAHC_RTC_TempTime;
}

//------------------------------------------------------------------------------
//  Function    : AHC_RTC_GetTime
//  Description : 
//------------------------------------------------------------------------------
void AHC_RTC_GetTime(AHC_RTC_TIME *psAHC_RTC_Time)
{
    AHC_RTC_TIME sAHC_RTC_TempTime = {0};
    
    if (!m_bUpdateRelativeTime) {
        *psAHC_RTC_Time = m_sRTCTime;
    }
    else
    {
        AHC_DBG_ERR(1, " for daytime saveing please use AHC_RTC_GetTimeEx() !!\n");
    }
    
    #ifdef CUSTOMER_RESET_YEAR
    if (m_sRTCTime.uwYear > RTC_MAX_YEAR){
        m_sRTCTime.uwYear = RTC_DEFAULT_YEAR;
        AHC_DBG_ERR(1, "#@#@RESET m_sRTCTime.uwYear = %d \r\n",m_sRTCTime.uwYear);
        AHC_SetClock(m_sRTCTime.uwYear, m_sRTCTime.uwMonth, m_sRTCTime.uwDay, m_sRTCTime.uwDayInWeek, m_sRTCTime.uwHour, m_sRTCTime.uwMinute, m_sRTCTime.uwSecond, m_sRTCTime.ubAmOrPm, m_sRTCTime.b_12FormatEn);
    }
    #endif

    // TBD:: Need to remove here.
    if (AHC_RTC_DSTCheck_GMT(m_sRTCTime.uwYear, m_sRTCTime.uwMonth, m_sRTCTime.uwDay, m_sRTCTime.uwHour))
    {
        DSTFullTime sTime = {0};
        DSTFullTime sOffsetTime = {0};

        sTime.iYear = m_sRTCTime.uwYear;
        sTime.iMon  = m_sRTCTime.uwMonth;
        sTime.iDay  = m_sRTCTime.uwDay;
        sTime.iHour = m_sRTCTime.uwHour;
        sTime.iMin  = m_sRTCTime.uwMinute;
        sTime.iSec  = m_sRTCTime.uwSecond;

        AHC_RTC_DSTTimeOffset(&sTime, &sOffsetTime, 4); //Add one hour

        sAHC_RTC_TempTime.uwYear   = sOffsetTime.iYear;
        sAHC_RTC_TempTime.uwMonth  = sOffsetTime.iMon;
        sAHC_RTC_TempTime.uwDay    = sOffsetTime.iDay;
        sAHC_RTC_TempTime.uwHour   = sOffsetTime.iHour;
        sAHC_RTC_TempTime.uwMinute = sOffsetTime.iMin;
        sAHC_RTC_TempTime.uwSecond = sOffsetTime.iSec;
    }
    else
    {
        sAHC_RTC_TempTime = m_sRTCTime;
    }

    *psAHC_RTC_Time = sAHC_RTC_TempTime;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetClock
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set RTC

 Set RTC value.
 Parameters:
 @param[in] uiYear Set year
 @param[in] uiMonth Set Month
 @param[in] uiDay Set Day
 @param[in] uiHour Set Hour
 @param[in] uiMinute Set Minute
 @param[in] uiSecond Set Second
 @retval TRUE or FALSE. // TRUE: Success, FALSE: Fail
*/
AHC_BOOL AHC_SetClock(UINT16 uiYear, UINT16 uiMonth, UINT16 uiDay, UINT16 uiDayInWeek, UINT16 uiHour, UINT16 uiMinute, UINT16 uiSecond,  UINT8 ubAmOrPm, UINT8 b_12FormatEn)
{
    MMP_ERR status;
    AUTL_DATETIME sTime;

#if (RTC_CHECK_INTERVAL)
    MMP_UBYTE i;
    AUTL_DATETIME scur_rtc_time;
    UINT32      ulRTCSecondsOffset, ulRTCSecondsOffset_temp;
    MMP_ULONG   ulOSTickCount;
#endif

#if (RTC_CHECK_SF_BASETIME)
    AHC_ERR err;
    UINT32 ulFileId;
    UINT32 ulWriteCount;

    AUTL_DATETIME pBaseTime = {
    2010,   ///< Year
    1,      ///< Month: 1 ~ 12
    1,      ///< Day of month: 1 ~ 28/29/30/31
    0,      ///< Sunday ~ Saturday
    0,      ///< 0 ~ 11 for 12-hour, 0 ~ 23 for 24-hour
    0,      ///< 0 ~ 59
    0,      ///< 0 ~ 59
    0,      ///< AM: 0; PM: 1 (for 12-hour only)
    0       ///< 24-hour: 0; 12-hour: 1
    };
#endif

    sTime.usYear         = uiYear;
    sTime.usMonth        = uiMonth;
    sTime.usDay          = uiDay;
    sTime.usDayInWeek    = uiDayInWeek;
    sTime.usHour         = uiHour;
    sTime.usMinute       = uiMinute;
    sTime.usSecond       = uiSecond;
    sTime.ubAmOrPm       = ubAmOrPm;
    sTime.b_12FormatEn   = b_12FormatEn;

    status = MMPS_RTC_SetTime(&sTime);

    if (status != MMP_ERR_NONE) {
        AHC_DBG_ERR(1, "RTC Error: %s,%d error!\r\n", __FUNCTION__, __LINE__);
        return AHC_FALSE;
    }
    else{
        MEMCPY((void *)&m_sRTCTime, (void *)&sTime, sizeof(AHC_RTC_TIME));
    }

    #if (RTC_CHECK_SF_BASETIME)
    //Save RTC BaseTime to SF　　
    m_ulBaseTimeInSeconds_SF = AUTL_Calendar_DateToSeconds(&sTime, &pBaseTime);
    err = AHC_FS_FileOpen(RTC_BASETIME_FILE_NAME, STRLEN(RTC_BASETIME_FILE_NAME),"wb+", sizeof("wb+"), &ulFileId);
    if (err == MMP_ERR_NONE){
        AHC_FS_FileSeek(ulFileId, 0, AHC_FS_SEEK_SET);
        AHC_FS_FileWrite(ulFileId, (UINT8 *)&m_ulBaseTimeInSeconds_SF, sizeof(m_ulBaseTimeInSeconds_SF), &ulWriteCount);
        AHC_FS_FileClose(ulFileId);
    }
    else {
        AHC_FS_FileClose(ulFileId);
        AHC_DBG_ERR(1, "RTC Error: RTCBaseTime.txt open fail #2!\r\n");
    }
    #endif

    #if (RTC_CHECK_INTERVAL)
    ulRTCSecondsOffset_temp = AHC_DT_GetSecondsOffset(uiYear, uiMonth, uiDay, uiHour, uiMinute, uiSecond);
    for(i=0; i<5; i++) {
        MMPS_RTC_GetTime(&scur_rtc_time);
        #if 0  //Test
        {
            static MMP_ULONG t = 0;
            t++;
            if(t < 3) {
                scur_rtc_time.usYear = 2060;
            }
            AHC_DBG_ERR(1, "AHC_SetClock Test: %2d %2d %2d - %2d:%2d:%2d\r\n", scur_rtc_time.usYear, scur_rtc_time.usMonth, scur_rtc_time.usDay, scur_rtc_time.usHour, scur_rtc_time.usMinute, scur_rtc_time.usSecond);
        }
        #endif
        ulRTCSecondsOffset = AHC_DT_GetSecondsOffset(scur_rtc_time.usYear, scur_rtc_time.usMonth, scur_rtc_time.usDay, scur_rtc_time.usHour, scur_rtc_time.usMinute, scur_rtc_time.usSecond);
        if((ulRTCSecondsOffset_temp > ulRTCSecondsOffset)) {
            if((ulRTCSecondsOffset_temp - ulRTCSecondsOffset) < RTC_MAX_INTERVAL) {
                break;
            }
            else {
                if(i == 4) {
                    AHC_DBG_ERR(1, "RTC Error: %s,%d error 2 !\r\n", __FUNCTION__, __LINE__);
                    return AHC_FALSE;
                }
                else {
                    MMPS_RTC_SetTime(&sTime);
                }
            }
        }
        else {
            if((ulRTCSecondsOffset - ulRTCSecondsOffset_temp) < RTC_MAX_INTERVAL) {
                break;
            }
            else {
                if(i == 4) {
                    AHC_DBG_ERR(1, "RTC Error: %s,%d error 3 !\r\n", __FUNCTION__, __LINE__);
                    return AHC_FALSE;
                }
                else {
                    MMPS_RTC_SetTime(&sTime);
                }
            }
        }
    }
    MMPF_OS_GetTime(&ulOSTickCount);
    AHC_DBG_ERR(1, "R:%d T:%d O:%d\r\n", ulRTCSecondsOffset,ulOSTickCount, ulOSTickCount/1000);
    AHC_RTC_SetOSTimeInterval(ulRTCSecondsOffset - ulOSTickCount/1000);
    #endif

    #if (UVC_HOST_VIDEO_ENABLE)
    AHC_HostUVC_ResetDevTime();
    #endif

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetClock
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get RTC

 Get RTC value.
 Parameters:
 @param[out] puwYear Get year
 @param[out] puwMonth Get Month
 @param[out] puwDay Get Day
 @param[out] puwHour Get Hour
 @param[out] puwMinute Get Minute
 @param[out] puwSecond Get Second
 @retval TRUE or FALSE.
*/
AHC_BOOL AHC_GetClock(UINT16* puwYear, UINT16* puwMonth, UINT16* puwDay, UINT16* puwDayInWeek, UINT16* puwHour, UINT16* puwMinute, UINT16* puwSecond, UINT8* ubAmOrPm, UINT8* b_12FormatEn)
{
    *puwYear        = m_sRTCTime.uwYear;
    *puwMonth       = m_sRTCTime.uwMonth;
    *puwDay         = m_sRTCTime.uwDay;
    *puwDayInWeek   = m_sRTCTime.uwDayInWeek;
    *puwHour        = m_sRTCTime.uwHour;
    *puwMinute      = m_sRTCTime.uwMinute;
    *puwSecond      = m_sRTCTime.uwSecond;
    *ubAmOrPm       = m_sRTCTime.ubAmOrPm;
    *b_12FormatEn   = m_sRTCTime.b_12FormatEn;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_RtcSetWakeUpEn
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set wake up counter of RTC unit

 Set wake up counter of RTC unit.
 Parameters:
 @param[in] bEnable Enable/Disable RTC wake up.
 @param[in] uiYear Set year
 @param[in] uiMonth Set Month
 @param[in] uiDay Set Day
 @param[in] uiHour Set Hour
 @param[in] uiMinute Set Minute
 @param[in] uiSecond Set Second
 @param[in] phHandleFunc Handler function
 @retval TRUE or FALSE.
*/
AHC_BOOL AHC_RtcSetWakeUpEn(AHC_BOOL bEnable, UINT16 uiYear, UINT16 uiMonth, UINT16 uiDay, UINT16 uiHour, UINT16 uiMinute, UINT16 uiSecond, void *phHandleFunc)
{
    AUTL_DATETIME sTime;

    sTime.usYear         = uiYear;
    sTime.usMonth        = uiMonth;
    sTime.usDay          = uiDay;
    sTime.usDayInWeek    = 0;
    sTime.usHour         = uiHour;
    sTime.usMinute       = uiMinute;
    sTime.usSecond       = uiSecond;
    sTime.ubAmOrPm       = 0;
    sTime.b_12FormatEn   = 1;

    if (MMPS_RTC_SetWakeUpEn(bEnable, &sTime, (RtcAlarmCallBackFunc *)phHandleFunc) != MMP_ERR_NONE) {
        AHC_DBG_ERR(1, "RTC Error: %s,%d error!\r\n", __FUNCTION__, __LINE__);
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

#if 0
void ____RTC_TimeStamp_Function_____(){ruturn;} //dummy
#endif

#define AHC_SYSTEM_TIMER    MMPF_TIMER_4

UINT8 sm[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void AIHC_AdvanceTime(AHC_RTC_TIME *pt)
{
    pt->uwSecond++;
    if (pt->uwSecond < 60)
        return;

    pt->uwSecond = 0;
    pt->uwMinute++;
    if (pt->uwMinute < 60)
        return;

    pt->uwMinute = 0;
    pt->uwHour++;
    if (pt->uwHour < 24)
        return;

    pt->uwHour = 0;
    pt->uwDay++;
    if (pt->uwDay <= sm[pt->uwMonth-1])
        return;

    if (pt->uwMonth == 2) {
        if (pt->uwDay == 29) {
            if (pt->uwYear % 4 == 0) {
                if (pt->uwYear % 100 == 0) {
                    if (pt->uwYear % 400 == 0) {
                        // leap year
                        return;
                    }
                } else {
                    // leap year
                    return;
                }
            }
        }
    }

    pt->uwDay = 1;
    pt->uwMonth++;
    if (pt->uwMonth < 13)
        return;

    pt->uwMonth = 1;
    pt->uwYear++;
}

AHC_BOOL AHC_Validate_Year(UINT16 year)
{
    return (year >= RTC_DEFAULT_YEAR);
}

UINT8 AHC_Validate_ClockSetting(INT32 *pDatetime, UINT8 ubCheckType, AHC_BOOL bAutoRestore)
{
    INT32 Year,Month,Day,Hour,Min,Sec;

    Year  = *(pDatetime+IDX_YEAR);
    Month = *(pDatetime+IDX_MONTH);
    Day   = *(pDatetime+IDX_DAY);
    Hour  = *(pDatetime+IDX_HOUR);
    Min   = *(pDatetime+IDX_MIN);
    Sec   = *(pDatetime+IDX_SEC);

    //Check Year
    if(ubCheckType & CHECK_YEAR)
    {
        if(Year > RTC_MAX_YEAR)
        {
            if(bAutoRestore)
                *(pDatetime+IDX_YEAR) = RTC_MIN_YEAR;
            else
                return IDX_YEAR;
        }
        else if(Year < RTC_MIN_YEAR)
        {
            if(bAutoRestore)
                *(pDatetime+IDX_YEAR) = RTC_MAX_YEAR;
            else
                return IDX_YEAR;
        }

        if( ((Year %4 == 0) && (Year %100 != 0)) || ( Year %400 == 0))//Leap Year
        {
            if( Month == 2 && Day == 28 )
            {
                if(bAutoRestore)
                    *(pDatetime+IDX_DAY) = RTC_MAX_DAY_FEB_LEAP_YEAR;
                else
                    return IDX_DAY;
            }
        }
        else
        {
            if( Month == 2 && Day == 29 )
            {
                if(bAutoRestore)
                    *(pDatetime+IDX_DAY) = RTC_MAX_DAY_FEB_NONLEAP_YEAR;
                else
                    return IDX_DAY;
            }
        }
    }

    //Check Month
    if(ubCheckType & CHECK_MONTH)
    {
        if(Month > RTC_MAX_MONTH)
        {
            if(bAutoRestore)
                *(pDatetime+IDX_MONTH) = RTC_MIN_MONTH;
            else
                return IDX_MONTH;
        }
        else if(Month < RTC_MIN_MONTH)
        {
            if(bAutoRestore)
                *(pDatetime+IDX_MONTH) = RTC_MAX_MONTH;
            else
                return IDX_MONTH;
        }

        if(Month == 2)
        {
            if( ((Year %4 == 0) && (Year %100 != 0)) || ( Year %400 == 0))//Leap Year
            {
                if(Day == 30 || Day == 31)
                {
                    if(bAutoRestore)
                        *(pDatetime+IDX_DAY) = RTC_MAX_DAY_FEB_LEAP_YEAR;
                    else
                        return IDX_DAY;
                }
            }
            else
            {
                if(Day == 29 || Day == 30 || Day == 31)
                {
                    if(bAutoRestore)
                        *(pDatetime+IDX_DAY) = RTC_MAX_DAY_FEB_NONLEAP_YEAR;
                    else
                        return IDX_DAY;
                }
            }
        }
        else if(Month == 4 || Month == 6 || Month == 9 || Month == 11)
        {
            if(Day == 31)
            {
                if(bAutoRestore)
                    *(pDatetime+IDX_DAY) = RTC_MAX_DAY_30;
                else
                    return IDX_DAY;
            }
        }
    }

    //Check Day
    if(ubCheckType & CHECK_DAY)
    {
        if(Month==1  || Month==3 || Month==5 || Month==7 || Month==8 || Month==10 || Month==12)
        {
            if(Day >RTC_MAX_DAY_31)
            {
                if(bAutoRestore)
                    *(pDatetime+IDX_DAY) = RTC_MIN_DAY;
                else
                    return IDX_DAY;

            }
            else if(Day < RTC_MIN_DAY)
            {
                if(bAutoRestore)
                    *(pDatetime+IDX_DAY) = RTC_MAX_DAY_31;
                else
                    return IDX_DAY;
            }
        }

        if(Month==4 || Month==6 || Month==9 || Month==11)
        {
            if(Day >RTC_MAX_DAY_30)
            {
                if(bAutoRestore)
                    *(pDatetime+IDX_DAY) = RTC_MIN_DAY;
                else
                    return IDX_DAY;
            }
            else if(Day < RTC_MIN_DAY)
            {
                if(bAutoRestore)
                    *(pDatetime+IDX_DAY) = RTC_MAX_DAY_30;
                else
                    return IDX_DAY;
            }
        }

        if(Month==2)
        {
            if( ((Year %4 == 0) && (Year %100 != 0)) || ( Year %400 == 0))//Leap Year
            {
                if(Day >RTC_MAX_DAY_FEB_LEAP_YEAR)
                {
                    if(bAutoRestore)
                        *(pDatetime+IDX_DAY) = RTC_MIN_DAY;
                    else
                        return IDX_DAY;
                }
                else if(Day < RTC_MIN_DAY)
                {
                    if(bAutoRestore)
                        *(pDatetime+IDX_DAY) = RTC_MAX_DAY_FEB_LEAP_YEAR;
                    else
                        return IDX_DAY;
                }
            }
            else
            {
                if(Day >RTC_MAX_DAY_FEB_NONLEAP_YEAR)
                {
                    if(bAutoRestore)
                        *(pDatetime+IDX_DAY) = RTC_MIN_DAY;
                    else
                        return IDX_DAY;
                }
                else if(Day < RTC_MIN_DAY)
                {
                    if(bAutoRestore)
                        *(pDatetime+IDX_DAY) = RTC_MAX_DAY_FEB_NONLEAP_YEAR;
                    else
                        return IDX_DAY;
                }
            }
        }
    }

    //Check Hour
    if(ubCheckType & CHECK_HOUR)
    {
        if(Hour > RTC_MAX_HOUR)
        {
            if(bAutoRestore)
                *(pDatetime+IDX_HOUR) = RTC_MIN_HOUR;
            else
                return IDX_HOUR;

        }
        else if(Hour < RTC_MIN_HOUR)
        {
            if(bAutoRestore)
                *(pDatetime+IDX_HOUR) = RTC_MAX_HOUR;
            else
                return IDX_HOUR;
        }
    }

    //Check Minute
    if(ubCheckType & CHECK_MIN)
    {
        if(Min > RTC_MAX_MIN)
        {
            if(bAutoRestore)
                *(pDatetime+IDX_MIN) = RTC_MIN_MIN;
            else
                return IDX_MIN;
        }
        else if(Min < RTC_MIN_MIN)
        {
            if(bAutoRestore)
                *(pDatetime+IDX_MIN) = RTC_MAX_MIN;
            else
                return IDX_MIN;
        }
    }

    //Check Second
    if(ubCheckType & CHECK_SEC)
    {
        if(Sec > RTC_MAX_SEC)
        {
            if(bAutoRestore)
                *(pDatetime+IDX_SEC) = RTC_MIN_SEC;
            else
                return IDX_SEC;
        }
        else if(Sec < RTC_MIN_SEC)
        {
            if(bAutoRestore)
                *(pDatetime+IDX_SEC) = RTC_MAX_SEC;
            else
                return IDX_SEC;
        }
    }

    return CHECK_PASS;
}

AHC_BOOL AHC_RestoreDefaultTime(UINT16 *py, UINT16 *pm, UINT16 *pd, UINT16 *pd_in_week,UINT16 *ph, UINT16 *pmm, UINT16 *ps, UINT8 *pam_pm, UINT8 *p12format_en)
{
    AHC_SetParam(PARAM_ID_USE_RTC,1);

    *py     = RTC_DEFAULT_YEAR;
    *pm     = RTC_DEFAULT_MONTH;
    *pd     = RTC_DEFAULT_DAY;
    *ph     = RTC_DEFAULT_HOUR;
    *pmm    = RTC_DEFAULT_MIN;
    *ps     = RTC_DEFAULT_SEC;

    *pd_in_week = 0;
    *pam_pm = 0;
    *p12format_en = 0;

    return AHC_TRUE;
}
