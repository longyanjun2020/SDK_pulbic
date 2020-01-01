/*===========================================================================
 * Include file
 *===========================================================================*/
#include "os_wrap.h"
#include "ahc_parameter.h"
#include "ahc_os.h"
#include "MenuSetting.h"
#include "ahc_fs.h"
#include "ahc_video.h"
#include "ahc_utility.h"
#include "ahc_datetime.h"
#include "ahc_media.h"
#include "stdarg.h"
#include "stdio.h"
#include "mmpf_pio.h"
#include "mmpf_fs_api.h"
#include "math.h"
#include "gps_ctl.h"
#include "mmpf_system.h" //For task monitor //CarDV...
#include "ait_utility.h"
#include "edog_ctl.h"
#include "ahc_menu_inc.h"
#if TPMS_FUNC_EN
#include "TPMS_driver.h"
#endif
#if (TOUCH_UART_FUNC_EN)
#include "Touch_Uart_ctrl.h"
#endif
#if(GPS_MODULE == GPS_MODULE_NMEA0183)
#include "gps_nmea0183.h"
#elif(GPS_MODULE == GPS_MODULE_GMC1030)
#include "GPSRadar_GMC1030.h"
#endif

/*===========================================================================
 * Macro define
 *===========================================================================*/
#define SHOW_GPS_MESSAGE_ON_PANEL_ALWAYS    1
#define GPS_RAW_EMER_BUF_1SEC               10240 //bytes
#define GPS_RAW_EMER_BUF_TIME               10   //sec

#define GPS_RAW_NORM_BUF_TIME               2   //sec
#define GPS_RAW_NORM_BUF_1SEC               10240 //

#define IS_A_DIGIT(x)                    ((x >='0') && (x <='9'))
#if (VR_VIDEO_TYPE == COMMON_VR_VIDEO_TYPE_3GP)
    #define GPSCTL_BIGENDIAN(d)     GPSCtrl_Convert_Endian(d + 8) // 8 is FOURCC + sizeof(unsigned int) for 3GP container
#else
    #define GPSCTL_BIGENDIAN(d)     (d)
#endif

/*===========================================================================
 * Global varible
 *===========================================================================*/

#if (GPS_KML_FILE_ENABLE == 1)
UINT32              ulKMLFileId = NULL;
static MMP_BYTE     ubGPSKmlFileName[256];
#endif
#if (GPS_RAW_FILE_ENABLE == 1)
UINT32              ulGPSRawFileId = NULL;
static MMP_BYTE     ubGPSRawFileName[256];
MMP_UBYTE           ubGPSRAWBufferIndex = 0;
MMP_BYTE            ubGPSRawBuffer_0[GPS_RAW_BUFFER_SIZE];
MMP_ULONG           ulGPSRawBufferLen_0 = 0;
MMP_BYTE            ubGPSRawBuffer_1[GPS_RAW_BUFFER_SIZE];
MMP_ULONG           ulGPSRawBufferLen_1 = 0;
MMP_BYTE            ubGPSRawEmerBuf[GPS_RAW_EMER_BUF_TIME][GPS_RAW_EMER_BUF_1SEC];
MMP_ULONG           ulGPSRawEmerBufLen[GPS_RAW_EMER_BUF_TIME];
MMP_ULONG           ulGPSRawEmerStartAddr  = 0xFFFFFFFF;
MMP_ULONG           ulGPSRawEmerStartTemp  = {0xFFFFFFFF};
MMP_ULONG           ulGPSRawEmerCountTemp  = 0;
#endif

#if (GPS_RAW_FILE_EMER_EN == 1)
UINT32              ulGPSRawFileId_Emer = NULL;
static MMP_BYTE     ubGPSRawFileName_Emer[256];
MMP_BOOL            bStartEmergencyRecordRaw = MMP_FALSE;
MMP_UBYTE           ubGPSRawEmerBufIndex = 0;
MMP_BOOL            bDumpEmerDone        = MMP_FALSE;
static MMP_ULONG    ulGPSRawEmerBufTime     = 0;
#endif

#if (GPS_RAW_FILE_ENABLE == 1)
MMP_UBYTE           ubGPSRawNormBufIndex = 0;
MMP_ULONG           ulGPSRawNormStartAddr  = 0xFFFFFFFF;
MMP_BYTE            ubGPSRawNormBuf[GPS_RAW_NORM_BUF_TIME][GPS_RAW_NORM_BUF_1SEC];
MMP_ULONG           ulGPSRawNormBufLen[GPS_RAW_NORM_BUF_TIME];
static MMP_ULONG    ulGPSRawNormBufTime     = 0;
#endif

extern  AHC_BOOL    m_EnterNoFitStorageAllocateQuery;

MMPF_OS_FLAGID      UartCtrlFlag = MMPF_OS_CREATE_FLAG_INT_ERR;
MMP_HANDLE          *hGps;


#if (GPS_CONNECT_ENABLE)
static MMP_BOOL     m_bGPS_TriggerRestorePreRecordInfo = MMP_FALSE;
static MMP_ULONG    m_ulGpsPreRecordTime = 0;
static MMP_BOOL     m_bGPS_FlushBackupBuffer[2] = {MMP_FALSE, MMP_FALSE};

#if (TOUCH_UART_FUNC_EN)
static MMP_ULONG    uiDTVPackLength;
static MMP_BYTE     szDTVPack[512];
#endif

static MMP_BYTE     szGPSPack[1024];
GPS_ATTRIBUTE       gGPS_Attribute          = {1, 32, NULL, NULL};
UINT32              ulGPSInfoFileId         = NULL;

UINT32              ulGPSInfoFileByte       = 0;
UINT32              ulGPSInfoLastByte       = 0;

static MMP_UBYTE    ubDrawCounter           = 20;
static MMP_ULONG    uiGPSPackLength;
static MMP_UBYTE    ubStartRecordWithGPSInfo = MMP_FALSE;
static MMP_ULONG    ulGPSCount_0            = 0;
static MMP_ULONG    ulGPSCount_1            = 0;
static MMP_ULONG    ulGPSCount_Last = 0;
static MMP_ULONG    ulGPSInfo2ChuckCount_0  = 0;
static MMP_ULONG    ulGPSInfo2ChuckCount_1  = 0;
static MMP_BOOL     bGPSinitialized = MMP_FALSE;
static GPSINFOCHUCK sGPSInfo2Chuck_0[GPS_CONFIG_MAXGPSINFONUM] = {0};
static GPSINFOCHUCK sGPSInfo2Chuck_1[GPS_CONFIG_MAXGPSINFONUM] = {0};
static MMP_UBYTE    ubGPSBufferIndex        = 0;
static MMP_UBYTE    ubGPSBufferIndex_Store  = 0;
static MMP_UBYTE    ubGPSBufferIndex_Last   = 0;
static MMP_UBYTE    ubGPSBufferIndex_Backup = 0;
static MMP_BOOL     bGPSPingPongBufferStart = MMP_FALSE;
static MMP_UBYTE    ubGPSBufferCounter      = 0;
static GPSCHUCKHEADER sGPSChuckHeader[1],sGPSInfoChuckHeader[1];
static MMP_BOOL     bLinkGPStime2RTC        = MMP_TRUE;
static MMP_BOOL     bGPSPWRStatus           = MMP_FALSE;
static MMP_BOOL     bGPSUseLastData         = MMP_FALSE;

#if (AHC_SHAREENC_SUPPORT)
MMP_BOOL        m_bStartGPS_SHARE           = MMP_FALSE;
MMP_ULONG       ulGPSTCount_Pre_SHARE       = 0xFFFF;     // PreRec count bound
MMP_ULONG       ulGPSCount_Pre_SHARE        = 0xFFFF;      // PreRec count
MMP_ULONG       ulGPSCount_SHARE            = 0xFFFF;          // Normal count
GPSINFOCHUCK    sGPSInfo2Chuck_Pre_SHARE[DUAL_RECORD_WRITE_PRETIME+DUAL_RECORD_WRITE_PRETIME_LIMIT] = {0};
GPSINFOCHUCK    sGPSInfo2Chuck_SHARE[DUAL_RECORD_WRITE_PRETIME+DUAL_RECORD_WRITE_INTERVAL] = {0};
#endif

static MMP_ULONG64  ullTotalTime = 0;
static MMP_BOOL     bStartCountTTFF = MMP_FALSE;
MMP_UBYTE  GPSTimerID           = 0xFF;
// ulGPS_AliveCnt RESET by GPS_FLAG_PARSE arrived and descrease by GPSCtrl_GPS_IsValidValue
// When ulGPS_AliveCnt <= 0 means GPS module removed, clean GPS info.
#define AVALIABLE_CNT       (20)
static MMP_LONG     ulGPS_AliveCnt          = -1;

static MMP_BOOL     bWaitForLogFirstTime = MMP_FALSE; //MMP_TRUE;

//Time zone table is established according to (time difference)*4. EX The value of GMT+8:00(Taiwan) will be 32.
//It should match with ITEMID_TIME_ZONE in MenuStateGeneralSettingsMenu.h
static signed char m_TimeZoneTable[MAX_TIMEZONE_TABLE_SIZE] =
{
    -48, -44, -40, -36, -32, -28, -24, -20, -16, -14, -12, -8, -4,
    0, 4, 8, 12, 14, 16, 18, 20, 22, 23, 24, 26, 28, 32, 36, 38, 40, 44, 48, 52
};
//extern MMPF_GPS_FUNCTION   *gsGpsFunction;

/*===========================================================================
 * Main body
 *===========================================================================*/
#if 0
void _____GPS_String_Tool_________(){ruturn;} //dummy
#endif


MMP_HANDLE MMPF_GPS_Open(void)
{
#if (GPS_MODULE == GPS_MODULE_NMEA0183)
    extern MMP_HANDLE GPS_NMEA0183_Open(void);
    return (MMP_HANDLE *)GPS_NMEA0183_Open();
#elif (GPS_MODULE == GPS_MODULE_GMC1030)
    extern MMP_HANDLE GPS_GMC1030_Open();
    return (MMP_HANDLE *)GPS_GMC1030_Open();
#endif
}

static UINT32 GPSCtrl_Convert_Endian(UINT32 d)
{
    UINT32 t = d;
    *((char*)&d + 3) = *((char*)&t + 0);
    *((char*)&d + 2) = *((char*)&t + 1);
    *((char*)&d + 1) = *((char*)&t + 2);
    *((char*)&d + 0) = *((char*)&t + 3);
    return d;
}

/**
 @brief Convert string to number
 */

MMP_LONG GPSCtrl_Atoi(MMP_BYTE *pStr, MMP_LONG iStr_sz, MMP_LONG iRadix)
{
    MMP_BYTE *pTmp_ptr;
    MMP_BYTE szBuff[256];
    MMP_LONG iRes = 0;

    if(iStr_sz < 256)
    {
        memcpy(&szBuff[0], pStr, iStr_sz);
        szBuff[iStr_sz] = '\0';
        iRes = strtol(&szBuff[0], &pTmp_ptr, iRadix);
    }

    return iRes;
}

/**
 @brief Convert string to fractional number
 */

double GPSCtrl_Atof(MMP_BYTE *pStr, MMP_LONG iStr_sz)
{
    MMP_BYTE    *pTmp_ptr;
    MMP_BYTE    szBuff[256];
    double      dwRes = 0;

    if(iStr_sz < 256)
    {
        memcpy(&szBuff[0], pStr, iStr_sz);
        szBuff[iStr_sz] = '\0';
        dwRes = strtod(&szBuff[0], &pTmp_ptr);
    }

    return dwRes;
}

/**
 @brief Analyse string (specificate for NMEA sentences)
 */

MMP_LONG GPSCtrl_Scanf(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, MMP_BYTE *pFormat, ...)
{
    MMP_BYTE    *pBeg_tok;
    MMP_BYTE    *pEnd_buf   = pBuff + iBuff_sz;
    MMP_LONG    iTok_type   = SCAN_TOKS_COMPARE;
    MMP_LONG    iWidth      = 0;
    MMP_BYTE    *pBeg_fmt   = 0;
    MMP_LONG    iSnum = 0, iUnum = 0;
    MMP_LONG    iTok_count  = 0;
    void        *parg_target;
    va_list     arg_ptr;

    va_start(arg_ptr, pFormat);

    for(; *pFormat && pBuff < pEnd_buf; ++pFormat)
    {
        switch(iTok_type)
        {
            case SCAN_TOKS_COMPARE:
                if('%' == *pFormat)
                    iTok_type = SCAN_TOKS_PERCENT;
                else if(*pBuff++ != *pFormat)
                    goto fail;
            break;

            case SCAN_TOKS_PERCENT:
                iWidth = 0;
                pBeg_fmt = pFormat;
                iTok_type = SCAN_TOKS_WIDTH;

            case SCAN_TOKS_WIDTH:
                if(IS_A_DIGIT(*pFormat))
                    break;
                {
                    iTok_type = SCAN_TOKS_TYPE;
                    if(pFormat > pBeg_fmt)
                        iWidth = GPSCtrl_Atoi(pBeg_fmt, (MMP_LONG)(pFormat - pBeg_fmt), 10);
                }

            case SCAN_TOKS_TYPE:
                pBeg_tok = pBuff;

                if(!iWidth && ('c' == *pFormat || 'C' == *pFormat) && *pBuff != pFormat[1])
                    iWidth = 1;

                if(iWidth)
                {
                    if(pBuff + iWidth <= pEnd_buf)
                        pBuff += iWidth;
                    else
                        goto fail;
                }
                else
                {
                    if(!pFormat[1] || (0 == (pBuff = (MMP_BYTE *)memchr(pBuff, pFormat[1], pEnd_buf - pBuff))))
                        pBuff = pEnd_buf;
                }

                if(pBuff > pEnd_buf)
                    goto fail;

                iTok_type = SCAN_TOKS_COMPARE;
                iTok_count++;

                parg_target = 0; iWidth = (MMP_LONG)(pBuff - pBeg_tok);

                switch(*pFormat)
                {
                    case 'c':
                    case 'C':
                        parg_target = (void *)va_arg(arg_ptr, MMP_BYTE *);
                        if(iWidth && 0 != (parg_target))
                            *((MMP_BYTE *)parg_target) = *pBeg_tok;
                        break;
                    case 's':
                    case 'S':
                        parg_target = (void *)va_arg(arg_ptr, MMP_BYTE *);
                        if(iWidth && 0 != (parg_target))
                        {
                            memcpy(parg_target, pBeg_tok, iWidth);
                            ((MMP_BYTE *)parg_target)[iWidth] = '\0';
                        }
                        break;
                    case 'f':
                    case 'e':
                    case 'E':
                        parg_target = (void *)va_arg(arg_ptr, double *);
                        if(iWidth && 0 != (parg_target))
                            *((double *)parg_target) = GPSCtrl_Atof(pBeg_tok, iWidth);
                        break;
                };

                if(parg_target)
                    break;
                if(0 == (parg_target = (void *)va_arg(arg_ptr, int *)))
                    break;
                if(!iWidth)
                    break;

                switch(*pFormat)
                {
                    case 'd':
                    case 'i':
                        iSnum = GPSCtrl_Atoi(pBeg_tok, iWidth, 10);
                        memcpy(parg_target, &iSnum, sizeof(MMP_LONG));
                        break;
                    case 'u':
                        iUnum = GPSCtrl_Atoi(pBeg_tok, iWidth, 10);
                        memcpy(parg_target, &iUnum, sizeof(MMP_ULONG));
                        break;
                    case 'x':
                    case 'X':
                        iUnum = GPSCtrl_Atoi(pBeg_tok, iWidth, 16);
                        memcpy(parg_target, &iUnum, sizeof(MMP_ULONG));
                        break;
                    case 'o':
                        iUnum = GPSCtrl_Atoi(pBeg_tok, iWidth, 8);
                        memcpy(parg_target, &iUnum, sizeof(MMP_ULONG));
                        break;
                    default:
                        goto fail;
                };

                break;
        };
    }

fail:

    va_end(arg_ptr);

    return iTok_count;
}

#if 0
void _____GPS_Measure_Tool_________(){ruturn;} //dummy
#endif

double GpsDmmToDegree_double(double dblLatLonDmm )
{
    double dblLat;
    INT32 uiLat;
    dblLat = dblLatLonDmm/100;
    uiLat  = dblLat;
    dblLat = uiLat + ( (dblLat - uiLat ) /60 * 100 );
    return dblLat;
}

double DegreeToGpsDmm_double(double dblLatLonDmm )
{

    double dblLat;
    INT32 uiLat;
    dblLat = dblLatLonDmm;

    uiLat  = dblLat;

    dblLat = (uiLat * 100 ) + ( (dblLat - uiLat ) * 60 );
    return dblLat;
}

float GpsDmmToDegree_float(float dblLatLonDmm )
{
    float dblLat;
    INT32 uiLat;
    dblLat = dblLatLonDmm/100;
    uiLat  = dblLat;
    dblLat = uiLat + ( (dblLat - (float)uiLat ) /60 * 100 );
    return dblLat;
}
float DegreeToGpsDmm_float(float dblLatLonDmm )
{

    float dblLat;
    INT32 uiLat;
    dblLat = dblLatLonDmm;

    uiLat  = dblLat;

    dblLat = (uiLat * 100 ) + ( (dblLat - uiLat ) * 60 );
    return dblLat;
}


void GPSCtrl_ResetTTFFTime()
{
    ullTotalTime = 0;
}

UINT64 GPSCtrl_GetTTFFTime()
{
    return ullTotalTime;
}
void GPSCtrl_StartCountTTFF()
{
    GPSCtrl_ResetContainer();
    GPSCtrl_ResetTTFFTime();
    GPSCtrl_Timer_Start(TIMERPERIOD);
    ullTotalTime = 0;
    bStartCountTTFF = MMP_TRUE;
}

void GPSCtrl_StopCountTTFF()
{
    GPSCtrl_Timer_Stop();
    bStartCountTTFF = MMP_FALSE;
}

void GPSCtrl_UpdateCountTTFF()
{
    if(GPSCtrl_IsCounting())
    {
        ullTotalTime += (TIMERPERIOD/1000);
    }
}

MMP_BOOL GPSCtrl_IsCounting()
{
    return bStartCountTTFF;
}

void GPSCtrl_Timer_ISR(void *tmr, void *arg)
{
    GPSCtrl_UpdateCountTTFF();
}

MMP_BOOL GPSCtrl_Timer_Start(UINT32 ulTime)
{

    GPSTimerID = AHC_OS_StartTimer( ulTime, AHC_OS_TMR_OPT_PERIODIC, GPSCtrl_Timer_ISR, (void*)NULL );

    if(0xFE <= GPSTimerID)
        return AHC_FALSE;
    else
        return AHC_TRUE;
}

MMP_BOOL GPSCtrl_Timer_Stop(void)
{
    UINT8 ret = 0;

    if(GPSTimerID < 0xFE){

        ret = AHC_OS_StopTimer( GPSTimerID, AHC_OS_TMR_OPT_PERIODIC );

        GPSTimerID = 0xFF;

        if(0xFF == ret)
            return AHC_FALSE;
        else
            return AHC_TRUE;
    }else{

        return AHC_FALSE;
    }

}

#if 0
void _____GPS_Parse_Method_________(){ruturn;} //dummy
#endif

void GPSCtrl_Enable(AHC_BOOL bEnable)
{
#if defined(GPS_MODULE_EN_GPIO)
    if (GPS_MODULE_EN_GPIO != MMP_GPIO_MAX)
    {
        AHC_GPIO_ConfigPad(GPS_MODULE_EN_GPIO, PAD_OUT_DRIVING(0));
        AHC_GPIO_SetOutputMode(GPS_MODULE_EN_GPIO, AHC_TRUE);
        AHC_GPIO_SetData(GPS_MODULE_EN_GPIO, bEnable);
    }
    bGPSPWRStatus = bEnable;
#endif
}

void GPS_EnableNMEA0183(void)
{
    #if (GPS_MODULE == GPS_MODULE_NMEA0183)
#if 1 // new for u-blox 7
    MMPF_3RDParty_GPS_Initiate();
    //gsGpsFunction->MMPF_Gps_InitCustFunc(); //MMPF_GpsDrv_InitCustFunc
#else
    //GPS_EnableANA_NMEA0183();
    // moved to driver layer due to need to wait the first NMEA string.
#endif
    #endif
}

void GPSCtrl_ChangeBaudRate(void)
{
    #if(GPS_MODULE == GPS_MODULE_NMEA0183)
    GPS_SetCommand_NMEA0183(NMEACMD_CFG_BAUDRATE_57600);
    #endif
}

void GPSCtrl_Initial(void)
{
    if(bGPSinitialized == MMP_FALSE)
    {
        hGps = (MMP_HANDLE *)MMPF_GPS_Open();
    #if(GPS_MODULE == GPS_MODULE_NMEA0183)
        GPS_ParserInitialize_NMEA0183();
    #if(GPS_CONFIG_NMEA_FILE == 0)
        GPSCtrl_Enable(AHC_TRUE);
        GPS_InitReceivePath_NMEA0183(NMEA_RECEIVE_UART, 9600);
        //GPS_EnableNMEA0183(); // new for u-blox 7
    #endif
    #elif(GPS_MODULE == GPS_MODULE_GMC1030)
        GPSRadar_ParserInitialize_GMC1030();
        GPSRadar_InitReceivePath_GMC1030(GPSRADAR_RECEIVE_UART);
    #endif
        bGPSinitialized = MMP_TRUE;
    }
}

void GPSCtrl_UnInitial(void)
{
    if(bGPSinitialized == MMP_TRUE)
    {
        #if(GPS_MODULE == GPS_MODULE_NMEA0183)
        GPS_ParserInitialize_NMEA0183();
        GPSCtrl_Enable(AHC_FALSE);
        GPS_UnInitPathUART_NMEA0183(9600);
        #elif(GPS_MODULE == GPS_MODULE_GMC1030)
        GPSRadar_ParserInitialize_GMC1030();
        GPSRadar_UnInitPathUART_GMC1030();
        #endif
        bGPSinitialized = MMP_FALSE;
    }
}

void GPSCtrl_ResetContainer(void)
{
    #if(GPS_MODULE == GPS_MODULE_NMEA0183)
    GPS_ResetContainer_NMEA0183();
    #elif(GPS_MODULE == GPS_MODULE_GMC1030)
    GPSRadar_ResetContainer_GMC1030();
    #endif
}

void GPSCtrl_GetGPSPack(MMP_BYTE *bGPSString, MMP_ULONG *ulGPSStringLength)
{
    #if(GPS_MODULE == GPS_MODULE_NMEA0183)
        #if (GPS_CONFIG_NMEA_FILE == 0)
        GPS_GetGPSPack_NMEA0183(NMEA_RECEIVE_UART,bGPSString,ulGPSStringLength);
        #else
        GPS_GetGPSPack_NMEA0183(NMEA_RECEIVE_TXT,bGPSString,ulGPSStringLength);
        #endif
    #elif(GPS_MODULE == GPS_MODULE_GMC1030)
    GPSRadar_GetPack_GMC1030(GPSRADAR_RECEIVE_UART,bGPSString,ulGPSStringLength);
    #endif
}

void GPSCtrl_ControlGPSPath(MMP_BOOL bEnable)
{
    #if(GPS_MODULE == GPS_MODULE_NMEA0183)
    GPS_ControlReceivePath_NMEA0183(NMEA_RECEIVE_UART,bEnable);
    #elif(GPS_MODULE == GPS_MODULE_GMC1030)
    GPSRadar_ControlReceivePath_GMC1030(GPSRADAR_RECEIVE_UART,bEnable);
    #endif
}

#if(GPS_MODULE == GPS_MODULE_NMEA0183)
void GPSCtrl_ParseGPSMain(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEAINFO *pInfo)
{
    GPS_ParserMain_NMEA0183(pBuff,iBuff_sz,pInfo);
}

void GPSCtrl_DubugMessageInfo(NMEAINFO *pInfo)
{
    GPS_DubugMessageInfo_NMEA0183(pInfo);
}

void GPSCtrl_GMT2LocalTime(NMEATIME *sGMTBackup, NMEATIME *sRes, signed char sbGMTOffset)
{
    GPS_GMT2LocalTime(sGMTBackup, sRes, sbGMTOffset);
}

#elif(GPS_MODULE == GPS_MODULE_GMC1030)

void GPSCtrl_ParseGPSMain(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, GPSRADARINFO *pInfo)
{
    GPSRadar_ParserMain_GMC1030(pBuff,iBuff_sz,pInfo);
}

void GPSCtrl_DubugMessageInfo(GPSRADARINFO *pInfo)
{
    GPSRadar_DubugMessageInfo_GMC1030(pInfo);
}

void GPSCtrl_GMT2LocalTime(GPSRADARTIME *sGMTBackup, GPSRADARTIME *sRes, signed char sbGMTOffset)
{
    GPSRadar_GMT2LocalTime(sGMTBackup, sRes, sbGMTOffset);
}
#endif

MMP_BOOL GPSCtrl_ModuleConnected(void)
{
    if (ulGPS_AliveCnt <= 0)
        return MMP_FALSE;
    else
        return MMP_TRUE;
}

MMP_BOOL GPSCtrl_GPS_IsValidValue(void)
{
    if (ulGPS_AliveCnt <= 0)
    {
        if (ulGPS_AliveCnt == 0)
        {
            #if(GPS_MODULE == GPS_MODULE_NMEA0183)
            GPS_ParserInitialize_NMEA0183();
            #elif(GPS_MODULE == GPS_MODULE_GMC1030)
            GPSRadar_ParserInitialize_GMC1030();
            #endif
            ulGPS_AliveCnt--;
        }
        return MMP_FALSE;
    }
    else
    {
        ulGPS_AliveCnt--;
    }
    #if(GPS_MODULE == GPS_MODULE_NMEA0183)
    return GPS_IsValidValue_NMEA0183();
    #elif(GPS_MODULE == GPS_MODULE_GMC1030)
    return GPSRadar_ValidValue_GMC1030();
    #endif
}

void GPSCtrl_GPSFormatTrans(double dwInputValue, MMP_USHORT *sDegree, MMP_USHORT *sMin, double *sSec)
{
    MMP_SHORT sTempValue;

    dwInputValue = GPS_ABS(dwInputValue);

    sTempValue = (MMP_USHORT)dwInputValue;

    *sDegree = (MMP_USHORT)dwInputValue/100;

    *sMin =(MMP_USHORT)(sTempValue - (*sDegree * 100));

    *sSec =(double)((dwInputValue - sTempValue)*60);

    #if (GPS_CONFIG_DBG_ENABLE)
    AHC_DBG_MSG(1, "sDegree : %d\r\n",*sDegree);
    AHC_DBG_MSG(1, "sMin : %d\r\n",*sMin);
    AHC_DBG_MSG(1, "sSec : %d\r\n",*sSec);
    #endif
}

MMP_UBYTE GPSCtrl_CheckRefForExif(MMP_UBYTE ubType)
{
#if(GPS_MODULE == GPS_MODULE_NMEA0183)
    NMEAINFO  *pInfo;

    pInfo =(NMEAINFO *)GPS_Information();

    switch(ubType)
    {
        case 0: //NS
            if((pInfo->dwLat)>=0)
                return 'N';
            else
                return 'S';
        break;
        case 1: //WE
            if((pInfo->dwLon)>=0)
                return 'E';
            else
                return 'W';
        break;
        case 2: //Under/below
            if((pInfo->dwElv)>=0)
                return 0;
            else
                return 1;
        break;
        case 3: //Speed
            return 'k';
        break;
        default:
            return 0;
        break;
    }
#elif(GPS_MODULE == GPS_MODULE_GMC1030)
    GPSRADARINFO   *pInfo;

    pInfo =(GPSRADARINFO *)GPSRadar_Information();

    switch(ubType)
    {
        case 0: //NS
            if((pInfo->chNS) == 'N')
                return 'N';
            else
                return 'S';
        break;
        case 1: //WE
            if((pInfo->chEW) == 'E')
                return 'E';
            else
                return 'W';
        break;
        case 2: //Under/below
            if((pInfo->dwElv)>=0)
                return 0;
            else
                return 1;
        break;
        case 3: //Speed
            return 'k';
        break;
        default:
            return 0;
        break;
    }
#endif

}

#if (GPS_CONFIG_NMEA_FILE)
void GPSCtrl_Verification(void)
{
    MMP_BOOL bSkipString;
    #if(GPS_MODULE == GPS_MODULE_NMEA0183)
    NMEAINFO            *pInfo;
    NMEATIME            *pGMTtime;
    #elif(GPS_MODULE == GPS_MODULE_GMC1030)
    GPSRADARINFO        *pInfo;
    GPSRADARTIME        *pGMTtime;
    #endif

    #if(GPS_MODULE == GPS_MODULE_NMEA0183)
    GPS_GetGPSPack_NMEA0183(NMEA_RECEIVE_TXT,szGPSPack,&uiGPSPackLength);
    #endif
    #if(GPS_MODULE == GPS_MODULE_GMC1030)
    GPSRadar_GetPack_GMC1030(GPSRADAR_RECEIVE_TXT,szGPSPack,&uiGPSPackLength);
    #endif

    //MMPF_OS_SetFlags(GPSCtrlFlag, GPS_FLAG_PARSE, MMPF_OS_FLAG_SET);

    #if(GPS_MODULE == GPS_MODULE_NMEA0183)
    pInfo    = (NMEAINFO *)GPS_Information();
    pGMTtime = (NMEATIME *)GPS_GetGMTBackupTime();
    #elif(GPS_MODULE == GPS_MODULE_GMC1030)
    pInfo    = (GPSRADARINFO *)GPSRadar_Information();
    pGMTtime = (GPSRADARTIME *)GPSRadar_GetGMTBackupTime();
    #endif

    // Reset available counter
    ulGPS_AliveCnt  = AVALIABLE_CNT;

    #if(GPS_MODULE == GPS_MODULE_NMEA0183)
        GPSCtrl_ParseGPSMain(szGPSPack,uiGPSPackLength,pInfo);
        if((pInfo->iSmask == GPRMC) || (pInfo->iSmask == GNRMC))
    #elif(GPS_MODULE == GPS_MODULE_GMC1030)
        GPSCtrl_ParseGPSMain(szGPSPack,uiGPSPackLength,pInfo);
    #endif
    {
        //GPSCtrl_DubugMessageInfo(pInfo);
    }
}
#endif

#if(GPS_MODULE == GPS_MODULE_NMEA0183)
MMP_BOOL GPSCtrl_LinkGPSTime2RTC(NMEATIME *sGPS)
{
    UINT16 uwYear,uwMonth,uwDay,uwDayInWeek,uwHour,uwMinute,uwSecond;

    AHC_BOOL bReturn;

    uwYear      = (UINT16)sGPS->iYear+2000;
    uwMonth     = (UINT16)sGPS->iMon;
    uwDay       = (UINT16)sGPS->iDay;
    uwHour      = (UINT16)sGPS->iHour;
    uwMinute    = (UINT16)sGPS->iMin;
    uwSecond    = (UINT16)sGPS->iSec;

    if( sGPS->iYear == 0 ||  sGPS->iMon == 0 ||  sGPS->iDay == 0)
    return MMP_FALSE;

    #if defined(GPS_TO_RTC_TIME_OFFSET) &&  (GPS_TO_RTC_TIME_OFFSET != 0 )
    {
        DATE_TIME DateTime;
        AHC_RTC_TIME sRtcTime;
        DateTime = AHC_DT_GetSecondsOffset(uwYear,uwMonth,uwDay,uwHour,uwMinute,uwSecond);
        DateTime += GPS_TO_RTC_TIME_OFFSET;

        AHC_DT_SecondsToDateTime( DateTime, &sRtcTime);
        uwYear   = sRtcTime.uwYear;
        uwMonth  = sRtcTime.uwMonth;
        uwDay    = sRtcTime.uwDay;
        uwHour   = sRtcTime.uwHour;
        uwMinute = sRtcTime.uwMinute;
        uwSecond = sRtcTime.uwSecond;
    }
    #endif

    AHC_SetParam(PARAM_ID_USE_RTC, AHC_TRUE);
    bReturn = AHC_SetClock(uwYear, uwMonth, uwDay, uwDayInWeek, uwHour, uwMinute, uwSecond, 0, 0);

    #if (GPS_CONFIG_DBG_ENABLE)
    if(bReturn)
        AHC_DBG_MSG(1, FG_YELLOW("Set RTC time yy/mm/dd h:min:sec: %d/%d/%d/ %d:%d:%d\r\n"),uwYear,uwMonth,uwDay,uwHour,uwMinute,uwSecond);
    else
        AHC_DBG_MSG(1, FG_RED("RTC Setting Fail!\r\n"));
    #endif
    return MMP_TRUE;
}
#elif (GPS_MODULE == GPS_MODULE_GMC1030)
MMP_BOOL GPSCtrl_LinkGPSTime2RTC(GPSRADARTIME *sGPS)
{
    UINT16 uwYear,uwMonth,uwDay,uwDayInWeek,uwHour,uwMinute,uwSecond;

    AHC_BOOL bReturn;

    uwYear      = (UINT16)sGPS->iYear+2000;
    uwMonth     = (UINT16)sGPS->iMon;
    uwDay       = (UINT16)sGPS->iDay;
    uwHour      = (UINT16)sGPS->iHour;
    uwMinute    = (UINT16)sGPS->iMin;
    uwSecond    = (UINT16)sGPS->iSec;

    uwDayInWeek = 0;
    ubAmOrPm = 0;
    b_12FormatEn = 0;

    if((uwYear==0)||(uwMonth==0)||(uwDay==0))
    return MMP_FALSE;

    AHC_SetParam(PARAM_ID_USE_RTC, AHC_TRUE);
    bReturn = AHC_SetClock(uwYear,uwMonth,uwDay, uwDayInWeek, uwHour,uwMinute,uwSecond, 0, 0);

    #if (GPS_CONFIG_DBG_ENABLE)
    if(bReturn)
        AHC_DBG_MSG(1, "Set RTC time yy/mm/dd h:min:sec: %d/%d/%d/ %d:%d:%d\r\n",uwYear,uwMonth,uwDay,uwHour,uwMinute,uwSecond);
    else
        AHC_DBG_MSG(1, "RTC Setting Fail!\r\n");
    #endif

    return MMP_TRUE;
}
#endif

MMP_ULONG GPSCtrl_GetSpeed(MMP_ULONG uiUnit)
{
    #if(GPS_MODULE == GPS_MODULE_NMEA0183)
    NMEAINFO  *pInfo = (NMEAINFO *)GPS_Information();
    #elif(GPS_MODULE == GPS_MODULE_GMC1030)
    GPSRADARINFO    *pInfo = (GPSRADARINFO *)GPSRadar_Information();
    #endif

    if(GPSCtrl_GPS_IsValidValue())
    {
        if(uiUnit == 0)
            return (MMP_ULONG)pInfo->dwSpeed;//km/hr
        else if(uiUnit == 1)
            return (((MMP_ULONG)(pInfo->dwSpeed*100+80))/161);//mile/hr
    }
    return 0;

}

MMP_UBYTE GPSCtrl_GetSignalStrength(void)
{
    #if(GPS_MODULE == GPS_MODULE_NMEA0183)
    NMEAINFO  *pInfo = (NMEAINFO *)GPS_Information();
    #elif(GPS_MODULE == GPS_MODULE_GMC1030)
    GPSRADARINFO    *pInfo = (GPSRADARINFO *)GPSRadar_Information();
    #endif

    if(GPSCtrl_GPS_IsValidValue())
    {
        if(pInfo->iSig == 0)
        return 0;
        else
        {
            float fGPSSignalStrength;
            fGPSSignalStrength = (float)(100 - 30*(log10(pInfo->dwHDOP)));
            if(fGPSSignalStrength >= 50 && fGPSSignalStrength < 88)
            return 1;
            else if(fGPSSignalStrength >= 88 && fGPSSignalStrength < 91)
            return 2;
            else if(fGPSSignalStrength >= 91)
            return 3;
            else
            return 0;
        }
    }else
    {
         return 0;
    }

}

#if (AHC_SHAREENC_SUPPORT)
void GPSCtrl_BackupGPSInfoEx(MMP_ULONG ulCounter)
{
    #if(GPS_MODULE == GPS_MODULE_NMEA0183)
    NMEAINFO  *pInfo = (NMEAINFO *)GPS_Information();
    #elif(GPS_MODULE == GPS_MODULE_GMC1030)
    GPSRADARINFO    *pInfo = (GPSRADARINFO *)GPSRadar_Information();
    #endif

    if(!GPSCtrl_GPS_IsValidValue())
    {
        if (m_bStartGPS_SHARE == MMP_FALSE) //PreRec
        {
            ulCounter = ulCounter % ulGPSTCount_Pre_SHARE;

            sGPSInfo2Chuck_Pre_SHARE[ulCounter].dwLat       = GPS_NOSIGNAL_MARK_DOUBLE;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].dwLon       = GPS_NOSIGNAL_MARK_DOUBLE;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].ubDirection = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].lAlt        = GPS_NOSIGNAL_MARK_LONG;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].usSpeed     = GPS_NOSIGNAL_MARK_SHORT;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].sUTC.byYear = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].sUTC.byMon  = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].sUTC.byDay  = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].sUTC.byHour = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].sUTC.byMin  = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].sUTC.bySec  = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].ubFlag      = MMP_FALSE;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].ubVersion   = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].ubReserved  = GPS_NOSIGNAL_MARK_BYTE;

            ulGPSCount_Pre_SHARE = ulCounter + 1;
            return;
        }

        if(ulCounter < DUAL_RECORD_WRITE_INTERVAL)
        {
            sGPSInfo2Chuck_SHARE[ulCounter].dwLat       = GPS_NOSIGNAL_MARK_DOUBLE;
            sGPSInfo2Chuck_SHARE[ulCounter].dwLon       = GPS_NOSIGNAL_MARK_DOUBLE;
            sGPSInfo2Chuck_SHARE[ulCounter].ubDirection = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_SHARE[ulCounter].lAlt        = GPS_NOSIGNAL_MARK_LONG;
            sGPSInfo2Chuck_SHARE[ulCounter].usSpeed     = GPS_NOSIGNAL_MARK_SHORT;
            sGPSInfo2Chuck_SHARE[ulCounter].sUTC.byYear = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_SHARE[ulCounter].sUTC.byMon  = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_SHARE[ulCounter].sUTC.byDay  = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_SHARE[ulCounter].sUTC.byHour = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_SHARE[ulCounter].sUTC.byMin  = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_SHARE[ulCounter].sUTC.bySec  = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_SHARE[ulCounter].ubFlag      = MMP_FALSE;
            sGPSInfo2Chuck_SHARE[ulCounter].ubVersion   = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_SHARE[ulCounter].ubReserved  = GPS_NOSIGNAL_MARK_BYTE;
            //sGPSInfo2Chuck_SHARE[ulCounter].sUTC.byHsec = GPS_NOSIGNAL_MARK_BYTE;
        }
    }
    else
    {
        if (m_bStartGPS_SHARE == MMP_FALSE) //PreRec
        {
            ulCounter = ulCounter % ulGPSTCount_Pre_SHARE;

            sGPSInfo2Chuck_Pre_SHARE[ulCounter].dwLat       = pInfo->dwLat;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].dwLon       = pInfo->dwLon;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].ubDirection = (MMP_UBYTE)(pInfo->dwDirection/2);
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].lAlt        = (MMP_LONG)pInfo->dwElv;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].usSpeed     = (MMP_USHORT)pInfo->dwSpeed;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].sUTC.byYear = (MMP_UBYTE)pInfo->sUTC.iYear;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].sUTC.byMon  = (MMP_UBYTE)pInfo->sUTC.iMon;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].sUTC.byDay  = (MMP_UBYTE)pInfo->sUTC.iDay;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].sUTC.byHour = (MMP_UBYTE)pInfo->sUTC.iHour;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].sUTC.byMin  = (MMP_UBYTE)pInfo->sUTC.iMin;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].sUTC.bySec  = (MMP_UBYTE)pInfo->sUTC.iSec;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].ubFlag      = MMP_TRUE;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].ubVersion   = GPS_CONFIG_INFOSTRUC_VER;
            sGPSInfo2Chuck_Pre_SHARE[ulCounter].ubReserved  = 0;
            //sGPSInfo2Chuck_Pre_SHARE[ulCounter].sUTC.byHsec = (MMP_UBYTE)pInfo->sUTC.iHsec;

            ulGPSCount_Pre_SHARE = ulCounter++;
            return;
        }

        if(ulCounter < DUAL_RECORD_WRITE_INTERVAL)
        {
            sGPSInfo2Chuck_SHARE[ulCounter].dwLat       = pInfo->dwLat;
            sGPSInfo2Chuck_SHARE[ulCounter].dwLon       = pInfo->dwLon;
            sGPSInfo2Chuck_SHARE[ulCounter].ubDirection = (MMP_UBYTE)(pInfo->dwDirection/2);
            sGPSInfo2Chuck_SHARE[ulCounter].lAlt        = (MMP_LONG)pInfo->dwElv;
            sGPSInfo2Chuck_SHARE[ulCounter].usSpeed     = (MMP_USHORT)pInfo->dwSpeed;
            sGPSInfo2Chuck_SHARE[ulCounter].sUTC.byYear = (MMP_UBYTE)pInfo->sUTC.iYear;
            sGPSInfo2Chuck_SHARE[ulCounter].sUTC.byMon  = (MMP_UBYTE)pInfo->sUTC.iMon;
            sGPSInfo2Chuck_SHARE[ulCounter].sUTC.byDay  = (MMP_UBYTE)pInfo->sUTC.iDay;
            sGPSInfo2Chuck_SHARE[ulCounter].sUTC.byHour = (MMP_UBYTE)pInfo->sUTC.iHour;
            sGPSInfo2Chuck_SHARE[ulCounter].sUTC.byMin  = (MMP_UBYTE)pInfo->sUTC.iMin;
            sGPSInfo2Chuck_SHARE[ulCounter].sUTC.bySec  = (MMP_UBYTE)pInfo->sUTC.iSec;
            sGPSInfo2Chuck_SHARE[ulCounter].ubFlag      = MMP_TRUE;
            sGPSInfo2Chuck_SHARE[ulCounter].ubVersion   = GPS_CONFIG_INFOSTRUC_VER;
            sGPSInfo2Chuck_SHARE[ulCounter].ubReserved  = 0;
            //sGPSInfo2Chuck_SHARE[ulCounter].sUTC.byHsec = (MMP_UBYTE)pInfo->sUTC.iHsec;
        }
    }
}
#endif

void GPSCtrl_BackupGPSInfo(MMP_ULONG ulCounter)
{
    #if(GPS_MODULE == GPS_MODULE_NMEA0183)
    NMEAINFO  *pInfo = (NMEAINFO *)GPS_Information();
    #elif(GPS_MODULE == GPS_MODULE_GMC1030)
    GPSRADARINFO    *pInfo = (GPSRADARINFO *)GPSRadar_Information();
    #endif

    if(!GPSCtrl_GPS_IsValidValue())
    {
        if(ubGPSBufferIndex)
        {
            sGPSInfo2Chuck_1[ulCounter].dwLat       = GPS_NOSIGNAL_MARK_DOUBLE;
            sGPSInfo2Chuck_1[ulCounter].dwLon       = GPS_NOSIGNAL_MARK_DOUBLE;
            sGPSInfo2Chuck_1[ulCounter].ubDirection = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_1[ulCounter].lAlt        = GPS_NOSIGNAL_MARK_LONG;
            sGPSInfo2Chuck_1[ulCounter].usSpeed     = GPS_NOSIGNAL_MARK_SHORT;
            sGPSInfo2Chuck_1[ulCounter].sUTC.byYear = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_1[ulCounter].sUTC.byMon  = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_1[ulCounter].sUTC.byDay  = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_1[ulCounter].sUTC.byHour = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_1[ulCounter].sUTC.byMin  = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_1[ulCounter].sUTC.bySec  = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_1[ulCounter].ubFlag      = MMP_FALSE;
            sGPSInfo2Chuck_1[ulCounter].ubVersion   = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_1[ulCounter].ubReserved  = GPS_NOSIGNAL_MARK_BYTE;
            //sGPSInfo2Chuck_1[ulCounter].sUTC.byHsec = GPS_NOSIGNAL_MARK_BYTE;
        }
        else
        {
            sGPSInfo2Chuck_0[ulCounter].dwLat       = GPS_NOSIGNAL_MARK_DOUBLE;
            sGPSInfo2Chuck_0[ulCounter].dwLon       = GPS_NOSIGNAL_MARK_DOUBLE;
            sGPSInfo2Chuck_0[ulCounter].ubDirection = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_0[ulCounter].lAlt        = GPS_NOSIGNAL_MARK_LONG;
            sGPSInfo2Chuck_0[ulCounter].usSpeed     = GPS_NOSIGNAL_MARK_SHORT;
            sGPSInfo2Chuck_0[ulCounter].sUTC.byYear = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_0[ulCounter].sUTC.byMon  = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_0[ulCounter].sUTC.byDay  = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_0[ulCounter].sUTC.byHour = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_0[ulCounter].sUTC.byMin  = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_0[ulCounter].sUTC.bySec  = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_0[ulCounter].ubFlag      = MMP_FALSE;
            sGPSInfo2Chuck_0[ulCounter].ubVersion   = GPS_NOSIGNAL_MARK_BYTE;
            sGPSInfo2Chuck_0[ulCounter].ubReserved  = GPS_NOSIGNAL_MARK_BYTE;
            //sGPSInfo2Chuck_0[ulCounter].sUTC.byHsec = GPS_NOSIGNAL_MARK_BYTE;
        }
    }
    else
    {
        if(ubGPSBufferIndex)
        {
            sGPSInfo2Chuck_1[ulCounter].dwLat       = pInfo->dwLat;
            sGPSInfo2Chuck_1[ulCounter].dwLon       = pInfo->dwLon;
            sGPSInfo2Chuck_1[ulCounter].ubDirection = (MMP_UBYTE)(pInfo->dwDirection/2);
            sGPSInfo2Chuck_1[ulCounter].lAlt        = (MMP_LONG)pInfo->dwElv;
            sGPSInfo2Chuck_1[ulCounter].usSpeed     = (MMP_USHORT)pInfo->dwSpeed;
            sGPSInfo2Chuck_1[ulCounter].sUTC.byYear = (MMP_UBYTE)pInfo->sUTC.iYear;
            sGPSInfo2Chuck_1[ulCounter].sUTC.byMon  = (MMP_UBYTE)pInfo->sUTC.iMon;
            sGPSInfo2Chuck_1[ulCounter].sUTC.byDay  = (MMP_UBYTE)pInfo->sUTC.iDay;
            sGPSInfo2Chuck_1[ulCounter].sUTC.byHour = (MMP_UBYTE)pInfo->sUTC.iHour;
            sGPSInfo2Chuck_1[ulCounter].sUTC.byMin  = (MMP_UBYTE)pInfo->sUTC.iMin;
            sGPSInfo2Chuck_1[ulCounter].sUTC.bySec  = (MMP_UBYTE)pInfo->sUTC.iSec;
            sGPSInfo2Chuck_1[ulCounter].ubFlag      = MMP_TRUE;
            sGPSInfo2Chuck_1[ulCounter].ubVersion   = GPS_CONFIG_INFOSTRUC_VER;
            sGPSInfo2Chuck_1[ulCounter].ubReserved  = 0;
            //sGPSInfo2Chuck_1[ulCounter].sUTC.byHsec = (MMP_UBYTE)pInfo->sUTC.iHsec;
        }
        else
        {
            sGPSInfo2Chuck_0[ulCounter].dwLat       = pInfo->dwLat;
            sGPSInfo2Chuck_0[ulCounter].dwLon       = pInfo->dwLon;
            sGPSInfo2Chuck_0[ulCounter].ubDirection = (MMP_UBYTE)(pInfo->dwDirection/2);
            sGPSInfo2Chuck_0[ulCounter].lAlt        = (MMP_LONG)pInfo->dwElv;
            sGPSInfo2Chuck_0[ulCounter].usSpeed     = (MMP_USHORT)pInfo->dwSpeed;
            sGPSInfo2Chuck_0[ulCounter].sUTC.byYear = (MMP_UBYTE)pInfo->sUTC.iYear;
            sGPSInfo2Chuck_0[ulCounter].sUTC.byMon  = (MMP_UBYTE)pInfo->sUTC.iMon;
            sGPSInfo2Chuck_0[ulCounter].sUTC.byDay  = (MMP_UBYTE)pInfo->sUTC.iDay;
            sGPSInfo2Chuck_0[ulCounter].sUTC.byHour = (MMP_UBYTE)pInfo->sUTC.iHour;
            sGPSInfo2Chuck_0[ulCounter].sUTC.byMin  = (MMP_UBYTE)pInfo->sUTC.iMin;
            sGPSInfo2Chuck_0[ulCounter].sUTC.bySec  = (MMP_UBYTE)pInfo->sUTC.iSec;
            sGPSInfo2Chuck_0[ulCounter].ubFlag      = MMP_TRUE;
            sGPSInfo2Chuck_0[ulCounter].ubVersion   = GPS_CONFIG_INFOSTRUC_VER;
            sGPSInfo2Chuck_0[ulCounter].ubReserved  = 0;
            //sGPSInfo2Chuck_0[ulCounter].sUTC.byHsec = (MMP_UBYTE)pInfo->sUTC.iHsec;
        }
    }
}

#if 0
void _____AVI_Chunk_Function_________(){ruturn;} //dummy
#endif

void GPSCtrl_ResetBufferControlVariable(void)
{
    ulGPSCount_0            = 0;
    ulGPSCount_1            = 0;
    ubGPSBufferIndex        = 0;
    bGPSPingPongBufferStart = MMP_FALSE;
    ubGPSBufferCounter      = 0;
    ulGPSInfo2ChuckCount_0  = 0;
    ulGPSInfo2ChuckCount_1  = 0;
#if (GPS_USE_FILE_AS_DATABUF)
    ulGPSInfoFileByte       = 0;
    ulGPSInfoLastByte       = 0;
#endif
}

void GPSCtrl_OpenInfoFile(INT8 *ubFileName)
{
#if (GPS_USE_FILE_AS_DATABUF)
    if (ubFileName == NULL) {
        AHC_DBG_MSG(1, "--E-- %s: File name is NULL\r\n", __FUNCTION__);
        return;
    }

    if(ulGPSInfoFileId == NULL) {
        //AHC_FS_FileOpen(ubFileName, AHC_StrLen(ubFileName), "w+b", AHC_StrLen("w+b"), &ulGPSInfoFileId);
        // Change "w+b" to "a+b" Means to append the same file position.
        if( AHC_FS_FileOpen(ubFileName, AHC_StrLen(ubFileName),"a+b",AHC_StrLen("a+b"), &ulGPSInfoFileId) != MMP_ERR_NONE )
        {
            ulGPSInfoFileId = NULL;
            return;
        }
    }

    AHC_FS_FileSeek(ulGPSInfoFileId, 0, AHC_FS_SEEK_SET);
//  MMPF_FS_FSeek(ulGPSInfoFileId, 0, AHC_FS_SEEK_SET);    //MMP_FS_FILE_BEGIN

    GPSCtrl_ResetBufferControlVariable();
#endif
}

void GPSCtrl_CloseInfoFile(void)
{
#if (GPS_USE_FILE_AS_DATABUF)
    if(ulGPSInfoFileId != NULL) {
        AHC_FS_FileClose(ulGPSInfoFileId);
    }

    ulGPSInfoFileId = NULL;
#endif
}

void GPSCtrl_StartRecord(void)
{
    ubStartRecordWithGPSInfo = (bGPSinitialized)?(MMP_TRUE):(MMP_FALSE);

#if (GPS_USE_FILE_AS_DATABUF)

    bGPSPingPongBufferStart = MMP_TRUE;

#else

    if(ubGPSBufferCounter)
    {
        bGPSPingPongBufferStart = MMP_TRUE;
    }
    else
    {
        ubGPSBufferCounter++;
    }
#endif

#if (AHC_SHAREENC_SUPPORT)
    MEMSET(sGPSInfo2Chuck_Pre_SHARE, 0, sizeof(sGPSInfo2Chuck_Pre_SHARE));
    ulGPSCount_Pre_SHARE = 0;
#endif

}

#if (AHC_SHAREENC_SUPPORT)
void GPSCtrl_EndRecordEx(void)
{
    AHC_DBG_MSG(1, " %s, %d\r\n", __FUNCTION__, __LINE__);
}
#endif

void GPSCtrl_EndRecord(void)
{
#if (GPS_USE_FILE_AS_DATABUF)

    if(ulGPSCount_0 != 0 && ulGPSCount_0 < GPS_CONFIG_MAXGPSINFONUM)
    {
        ulGPSInfoLastByte = ulGPSCount_0*sizeof(GPSINFOCHUCK);
        ubGPSBufferIndex_Store = 0;
        ubGPSBufferIndex = 1;
    }
    else if(ulGPSCount_1 != 0 && ulGPSCount_1 < GPS_CONFIG_MAXGPSINFONUM)
    {
        ulGPSInfoLastByte = ulGPSCount_1*sizeof(GPSINFOCHUCK);
        ubGPSBufferIndex_Store = 1;
        ubGPSBufferIndex = 0;
    }

#else

    if(ubGPSBufferIndex)
    {
        ubGPSBufferIndex = 0;
        ulGPSInfo2ChuckCount_1 = ulGPSCount_1;
    }
    else
    {
        ubGPSBufferIndex = 1;
        ulGPSInfo2ChuckCount_0 = ulGPSCount_0;
    }

    if(bGPSPingPongBufferStart)
    {
        if(ubGPSBufferIndex)
            ulGPSCount_1 = 0;
        else
            ulGPSCount_0 = 0;
    }
#endif
    ubStartRecordWithGPSInfo = MMP_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : GPSCtrl_EndRecord_Backup
//  Description : It will record GPS data index for current video,
//                and keep recording GPS data. (Reset nothing.)
//------------------------------------------------------------------------------
void GPSCtrl_EndRecord_Backup(void)
{
    if(ulGPSCount_0 != 0 && ulGPSCount_0 < GPS_CONFIG_MAXGPSINFONUM)
    {
        ulGPSInfoLastByte = ulGPSCount_0*sizeof(GPSINFOCHUCK);
    }
    else if(ulGPSCount_1 != 0 && ulGPSCount_1 < GPS_CONFIG_MAXGPSINFONUM)
    {
        ulGPSInfoLastByte = ulGPSCount_1*sizeof(GPSINFOCHUCK);
    }

    ubGPSBufferIndex_Backup = ubGPSBufferIndex;
}

#if (AHC_SHAREENC_SUPPORT)
pGPSInfoChuck GPSCtrl_InfoAddressForAviChuckEx(void)
{
    if (m_bStartGPS_SHARE)
        return sGPSInfo2Chuck_SHARE;

    return NULL;
}

MMP_ULONG GPSCtrl_InfoSizeForAviChuckEx(void)
{
    MMP_ULONG ulReturnValue = 0;

    if (m_bStartGPS_SHARE)
    {
        ulReturnValue = ulGPSCount_SHARE * sizeof(GPSINFOCHUCK);
        return ulReturnValue;
    }

    return 0;
}
#endif

pGPSInfoChuck GPSCtrl_InfoAddressForAviChuck(void)
{
    if(ubGPSBufferIndex)
        return sGPSInfo2Chuck_0;
    else
        return sGPSInfo2Chuck_1;
}

MMP_ULONG GPSCtrl_InfoSizeForAviChuck(void)
{
    MMP_ULONG ulReturnValue;

#if (GPS_USE_FILE_AS_DATABUF)
    ulReturnValue = ulGPSInfoFileByte + ulGPSInfoLastByte;
#else

    if(bGPSPingPongBufferStart)
    {
        if(ubGPSBufferIndex)
        {
            ulReturnValue = ulGPSInfo2ChuckCount_0;
        }
        else
        {
            ulReturnValue = ulGPSInfo2ChuckCount_1;
        }
    }
    else
    {
        if(ubGPSBufferIndex)
        {
            ulReturnValue = ulGPSInfo2ChuckCount_0;
        }
        else
        {
            ulReturnValue = ulGPSInfo2ChuckCount_1;
        }
    }
    ulReturnValue *= sizeof(GPSINFOCHUCK);

#endif
    AHC_DBG_MSG(0, "GPSINFO_SIZE:%d\r\n",ulReturnValue);
    return ulReturnValue;
}

pGPSChuckHeader GPSCtrl_HeaderAddressForAviChuck(MMP_UBYTE ubSelsection)
{
    if(ubSelsection == 0)
        return sGPSInfoChuckHeader;
    else
        return sGPSChuckHeader;
}

#if (AHC_SHAREENC_SUPPORT)
void GPSCtrl_SetHeaderForAviChuckEx(void)
{
    sGPSChuckHeader[0].ulFourCC = GPS_MAKE_FCC('g','p','s','0');
    sGPSChuckHeader[0].ulSize   = GPSCTL_BIGENDIAN(GPSCtrl_InfoSizeForAviChuckEx());
}

pGPSInfoChuck GPSCtrl_GetLastDataAddrEx(void)
{
    if (m_bStartGPS_SHARE)
        return sGPSInfo2Chuck_SHARE;

    return NULL;
}
#endif

void GPSCtrl_SetHeaderForAviChuck(void)
{
    sGPSChuckHeader[0].ulFourCC = GPS_MAKE_FCC('g','p','s','0');
    sGPSChuckHeader[0].ulSize   = GPSCTL_BIGENDIAN(GPSCtrl_InfoSizeForAviChuck());
}

void GPSCtrl_SetHeaderForAviChuck_GPSConfig(void)
{
    sGPSInfoChuckHeader[0].ulFourCC = GPS_MAKE_FCC('g','p','s','a');
    sGPSInfoChuckHeader[0].ulSize   = GPSCTL_BIGENDIAN(sizeof(GPS_ATTRIBUTE));
}

pGPS_Attribute GPSCtrl_AttributeAddressForAviChuck(void)
{
    return &gGPS_Attribute;
}

void GPSCtrl_RestoreAviChuck(void)
{
    UINT32 ulTimelimit;
    MMP_UBYTE dummy;

    if(ubStartRecordWithGPSInfo)
    {
        AHC_VIDEO_GetCurRecordingTime(&ulTimelimit);

        if( AHC_GPS_NeedToRestorePreRecordInfo( &ulTimelimit ) == MMP_TRUE )
        {
            m_bGPS_TriggerRestorePreRecordInfo = MMP_FALSE;

            AHC_GPS_RestorePreRecordInfo( ulTimelimit, bGPSUseLastData );
            bGPSUseLastData = MMP_FALSE;
        }

        if(ubGPSBufferIndex)
        {
            if((ulGPSCount_1 + ulGPSInfoFileByte/(sizeof(GPSINFOCHUCK))) < ulTimelimit/1000 * gGPS_Attribute.ubStoreFreq)
            {
                dummy = ulTimelimit/1000 * (gGPS_Attribute.ubStoreFreq) - (ulGPSCount_1 + ulGPSInfoFileByte/(sizeof(GPSINFOCHUCK)));
                do{
                    GPSCtrl_BackupGPSInfo(ulGPSCount_1);
                    #if (AHC_SHAREENC_SUPPORT)
                    if (m_bStartGPS_SHARE)
                        GPSCtrl_BackupGPSInfoEx(ulGPSCount_SHARE++);
                    else
                        GPSCtrl_BackupGPSInfoEx(ulGPSCount_Pre_SHARE);
                    #endif
                    ulGPSCount_1++;
                    dummy--;
                }while((dummy > 0) && (ulGPSCount_1 < GPS_CONFIG_MAXGPSINFONUM));
            }
            else
            {
                GPSCtrl_BackupGPSInfo(ulGPSCount_1);
                #if (AHC_SHAREENC_SUPPORT)
                if (m_bStartGPS_SHARE)
                    GPSCtrl_BackupGPSInfoEx(ulGPSCount_SHARE++);
                else
                    GPSCtrl_BackupGPSInfoEx(ulGPSCount_Pre_SHARE);
                #endif
                ulGPSCount_1++;
            }
            #if (GPS_USE_FILE_AS_DATABUF)
            if(ulGPSCount_1 == GPS_CONFIG_MAXGPSINFONUM)
            {
                UINT32 ulWriteCount;

                AHC_FS_FileWrite(ulGPSInfoFileId, (UINT8*)sGPSInfo2Chuck_1, GPS_CONFIG_MAXGPSINFONUM*sizeof(GPSINFOCHUCK), &ulWriteCount);
                ulGPSInfoFileByte += ulWriteCount;

                ulGPSCount_1        = 0;//Reset
                ubGPSBufferIndex    = 0;//Toggle

            }
            #endif
            #if (GPS_KML_FILE_ENABLE == 1)
            GPSCtrl_KMLGen_Write_Position(sGPSInfo2Chuck_1->dwLat,sGPSInfo2Chuck_1->dwLon, sGPSInfo2Chuck_1->lAlt);
            #endif
        }
        else
        {
            if((ulGPSCount_0 + ulGPSInfoFileByte/(sizeof(GPSINFOCHUCK))) < ulTimelimit/1000 * gGPS_Attribute.ubStoreFreq)
            {
                dummy = ulTimelimit/1000 * (gGPS_Attribute.ubStoreFreq) - (ulGPSCount_0 + ulGPSInfoFileByte/(sizeof(GPSINFOCHUCK)));
                do{
                    GPSCtrl_BackupGPSInfo(ulGPSCount_0);
                    #if (AHC_SHAREENC_SUPPORT)
                    if (m_bStartGPS_SHARE)
                        GPSCtrl_BackupGPSInfoEx(ulGPSCount_SHARE++);
                    else
                        GPSCtrl_BackupGPSInfoEx(ulGPSCount_Pre_SHARE);
                    #endif
                    ulGPSCount_0++;
                    dummy--;
                }while((dummy > 0) && (ulGPSCount_0 < GPS_CONFIG_MAXGPSINFONUM));
            }
            else
            {
                GPSCtrl_BackupGPSInfo(ulGPSCount_0);
                #if (AHC_SHAREENC_SUPPORT)
                if (m_bStartGPS_SHARE)
                    GPSCtrl_BackupGPSInfoEx(ulGPSCount_SHARE++);
                else
                    GPSCtrl_BackupGPSInfoEx(ulGPSCount_Pre_SHARE);
                #endif
                ulGPSCount_0++;
            }
            #if (GPS_USE_FILE_AS_DATABUF)
            if(ulGPSCount_0 == GPS_CONFIG_MAXGPSINFONUM)
            {
                UINT32 ulWriteCount;

                AHC_FS_FileWrite(ulGPSInfoFileId, (UINT8*)sGPSInfo2Chuck_0, GPS_CONFIG_MAXGPSINFONUM*sizeof(GPSINFOCHUCK), &ulWriteCount);
                ulGPSInfoFileByte += ulWriteCount;

                ulGPSCount_0     = 0;//Reset
                ubGPSBufferIndex = 1;//Toggle
                AHC_DBG_MSG(1, "Buf0-ulGPSInfoFileByte %d\r\n",ulGPSInfoFileByte);
            }
            #endif
            #if (GPS_KML_FILE_ENABLE == 1)
            GPSCtrl_KMLGen_Write_Position(sGPSInfo2Chuck_0->dwLat,sGPSInfo2Chuck_0->dwLon, sGPSInfo2Chuck_0->lAlt);
            #endif
        }
    }
}

pGPSInfoChuck GPSCtrl_GetLastDataAddr(void)
{
    if( ubGPSBufferIndex_Store == 0 )
    {
        ulGPSCount_Last       = ulGPSCount_0;
        ubGPSBufferIndex_Last = 0;
        AHC_DBG_MSG(0, "GPS Flush Buffer[0] Cnt [%d]\r\n", ulGPSCount_0);
        ulGPSCount_0 = 0;
        return sGPSInfo2Chuck_0;
    }
    else if( ubGPSBufferIndex_Store == 1 )
    {
        ulGPSCount_Last       = ulGPSCount_1;
        ubGPSBufferIndex_Last = 1;
        AHC_DBG_MSG(0, "GPS Flush Buffer[1] Cnt [%d]\r\n", ulGPSCount_1);
        ulGPSCount_1 = 0;
        return sGPSInfo2Chuck_1;
    }
    return NULL;
}

pGPSInfoChuck GPSCtrl_GetBackupDataAddr(void)
{
    if( ubGPSBufferIndex_Backup == 0 )
    {
        AHC_DBG_MSG(0, "GPS Flush Backup[%d] Cnt[%d]\r\n", ubGPSBufferIndex_Backup, ulGPSCount_0);
        return sGPSInfo2Chuck_0;
    }
    else
    {
        AHC_DBG_MSG(0, "GPS Flush Backup[%d] Cnt[%d]\r\n", ubGPSBufferIndex_Backup, ulGPSCount_1);
        return sGPSInfo2Chuck_1;
    }
}

#if 0
void _____KML_Generate_Function_________(){ruturn;} //dummy
#endif

#if (GPS_KML_FILE_ENABLE == 1)
extern int      sprintf(char * /*s*/, const char * /*format*/, ...);
void GPSCtrl_SetKMLFileName(MMP_BYTE bFilename[], MMP_USHORT usLength)
{
    MMP_BYTE *ptr;
    MMP_USHORT i;

    ptr = (MMP_BYTE *)bFilename;

    for (i = 0; i < usLength; i++) {
        ubGPSKmlFileName[i] = *ptr++;
    }

    if(ulKMLFileId != NULL)
    {
        GPSCtrl_KMLGen_Write_TailAndClose();
    }

    AHC_FS_FileOpen(ubGPSKmlFileName, AHC_StrLen(ubGPSKmlFileName), "w+b", AHC_StrLen("w+b"), &ulKMLFileId);
//  MMPF_FS_FOpen(ubGPSKmlFileName, "w+b", &ulKMLFileId);
    GPSCtrl_KMLGen_Write_Header();
}

MMP_BOOL GPSCtrl_KMLGen_Write_Header(void)
{
    UINT32 ulWriteSize = 0;

    if(ulKMLFileId != NULL)
    {
        AHC_FS_FileWrite(ulKMLFileId, (UINT8 *)KML_HEADER,sizeof(KML_HEADER),&ulWriteSize);
        return MMP_TRUE;
    }
    else
    {
        return MMP_FALSE;
    }
}

MMP_BOOL GPSCtrl_KMLGen_Write_Position(double lat, double lon, int att)
{
    UINT32 ulWriteSize = 0;
    char   buffer[30];

    sprintf( buffer, "%.10f", lon);
    buffer[10] = 0x2c; //","
    AHC_FS_FileWrite(ulKMLFileId, (UINT8 *)buffer,11,&ulWriteSize);
    sprintf( buffer, "%.10f", lat);
    buffer[10] = 0x2c; //","
    AHC_FS_FileWrite(ulKMLFileId, (UINT8 *)buffer,11,&ulWriteSize);
    sprintf( buffer, "%d\n", att);
    AHC_FS_FileWrite(ulKMLFileId, (UINT8 *)buffer,6,&ulWriteSize);

    return MMP_TRUE;
}

MMP_BOOL GPSCtrl_KMLGen_Write_TailAndClose(void)
{
    UINT32 ulWriteSize = 0;

    if(ulKMLFileId != NULL)
    {
        AHC_FS_FileWrite(ulKMLFileId, (UINT8 *)KML_TAILER,sizeof(KML_TAILER),&ulWriteSize);
        AHC_FS_FileClose(ulKMLFileId);
        ulKMLFileId = NULL;
        return MMP_TRUE;
    }
    else
    {
        return MMP_FALSE;
    }
}
#endif

#if 0
void _____Send_Command_Function_________(){ruturn;} //dummy
#endif


void GPSCtrl_SetCommand(MMP_UBYTE ubType, MMP_UBYTE ubValue)
{
    #if(GPS_MODULE == GPS_MODULE_GMC1030)
    GPSRadar_SetCommand_GMC1030((RADARSET_TYPE)ubType, ubValue);
    #endif
    #if(GPS_MODULE == GPS_MODULE_NMEA0183)
    GPS_SetCommand_NMEA0183((NMEACOMMAND_TYPE)ubType);
    #endif
}

#if 0
void _____GPS_Position_Log_Function_________(){ruturn;} //dummy
#endif

//#define GPS_LOG_SECTOR_BEGIN        (48)
#define GPS_LOG_SECTORS             (8)
#define SF_SECTOR_SIZE              (0x200)
#define UNUSEDYEAR                  (1900)
#define UNUSEDTIME                  (01)
#define GPS_LOG_RECORD_ID           0x55AA55AA

#ifndef GPS_LOG_SECTOR_BEGIN_OFFSET
// CarDV should be define to 1 in Config_SDK.h
#define GPS_LOG_SECTOR_BEGIN_OFFSET (0)
#endif

#include "mmpf_sf.h"
#include "cdvmem.h"

void GPSCtrl_GetFirstLocationTime(GPS_LOG* psGPSLog)
{
    MMP_ULONG ulSFData = AHC_DCF_TEMP_BASE_ADDR - SF_SECTOR_SIZE*2;
    MMP_ERR err;
    MMP_ULONG ulSectorBegin;
    MMPF_SIF_INFO *info;

    info = MMPF_SF_GetSFInfo();

    ulSectorBegin = (info->ulSFTotalSize - (GPS_LOG_SECTORS + GPS_LOG_SECTOR_BEGIN_OFFSET) * SF_SECTOR_SIZE)/SF_SECTOR_SIZE;

    psGPSLog->ulLogID  = 0xFFFFFFFF;
    psGPSLog->psDateTime.uwYear   = 2013;
    psGPSLog->psDateTime.uwMonth  = 1;
    psGPSLog->psDateTime.uwDay    = 1;
    psGPSLog->psDateTime.uwHour   = 0;
    psGPSLog->psDateTime.uwMinute = 0;
    psGPSLog->psDateTime.uwSecond = 0;

    AHC_DBG_MSG(1, "Get SF from %d\r\n",(ulSectorBegin)*SF_SECTOR_SIZE);
    err = MMPF_SF_FastReadData((MMP_ULONG)(ulSectorBegin)*SF_SECTOR_SIZE, (MMP_ULONG)ulSFData, (MMP_ULONG)sizeof(GPS_LOG));

    if(err == MMP_ERR_NONE)
    {
        AHC_DBG_MSG(1, "No error\r\n");
        MEMCPY(psGPSLog, (GPS_LOG *)ulSFData, sizeof(GPS_LOG));
        if(psGPSLog->ulLogID == GPS_LOG_RECORD_ID)
        {
            bWaitForLogFirstTime = AHC_FALSE;
        }
    }else
    {
        AHC_DBG_MSG(1, "error\r\n");
        psGPSLog->ulLogID   = 0xFFFFFFFF;
        psGPSLog->psDateTime.uwYear     = UNUSEDYEAR;
        psGPSLog->psDateTime.uwMonth = UNUSEDTIME;
        psGPSLog->psDateTime.uwDay  = UNUSEDTIME;
        psGPSLog->psDateTime.uwHour     = UNUSEDTIME;
        psGPSLog->psDateTime.uwMinute = UNUSEDTIME;
        psGPSLog->psDateTime.uwSecond = UNUSEDTIME;
    }

    AHC_DBG_MSG(1, "ulLogID : 0x%x\r\n",psGPSLog->ulLogID);
    AHC_DBG_MSG(1, "uwYear : %d\r\n",psGPSLog->psDateTime.uwYear);
    AHC_DBG_MSG(1, "uwMonth : %d\r\n",psGPSLog->psDateTime.uwMonth);
    AHC_DBG_MSG(1, "uwDay : %d\r\n",psGPSLog->psDateTime.uwDay);
    AHC_DBG_MSG(1, "uwHour : %d\r\n",psGPSLog->psDateTime.uwHour);
    AHC_DBG_MSG(1, "uwMinute : %d\r\n",psGPSLog->psDateTime.uwMinute);
    AHC_DBG_MSG(1, "uwSecond : %d\r\n",psGPSLog->psDateTime.uwSecond);

}

void GPSCtrl_SetFirstLocationTime(GPS_LOG *pGPSlog)
{
    MMP_ERR err;
    MMP_ULONG ulSectorBegin;

    MMPF_SIF_INFO *info;
    info = MMPF_SF_GetSFInfo();

    ulSectorBegin = (info->ulSFTotalSize - (GPS_LOG_SECTORS + GPS_LOG_SECTOR_BEGIN_OFFSET) * SF_SECTOR_SIZE) / SF_SECTOR_SIZE;

    MMPF_SF_EraseSector((MMP_ULONG)(ulSectorBegin)*SF_SECTOR_SIZE);
    err = MMPF_SF_WriteData((MMP_ULONG)(ulSectorBegin)*SF_SECTOR_SIZE, (MMP_ULONG)pGPSlog, (MMP_ULONG)sizeof(GPS_LOG));
}

MMP_BOOL GPSCtrl_NeedToLogFirstTime(void)
{
    return bWaitForLogFirstTime;
}

AHC_BOOL GPSCtrl_GPSParsing(void)
{
    if(ulGPS_AliveCnt > 0)
    return AHC_TRUE;
    else
    return AHC_FALSE;
}

#endif //#if GPS_CONNECT_ENABLE

AHC_BOOL AHC_RTC_NeedToUpdate(void) //Only for GPS.  Don't put it into common code.
{
    UINT16 uwYear,uwMonth,uwDay,uwDayInWeek,uwHour,uwMinute,uwSecond;
    UINT8 ubAmOrPm, b_12FormatEn;
    AHC_BOOL success;

    //AHC_SetParam(PARAM_ID_USE_RTC,1);
    success = AHC_GetClock( &uwYear, &uwMonth, &uwDay, &uwDayInWeek, &uwHour, &uwMinute, &uwSecond, &ubAmOrPm, &b_12FormatEn);
    //AHC_DBG_MSG(1, "uwYear : %d\r\n",uwYear);

    if(MenuSettingConfig()->uiTimeZone == TIMEZONE_GMT_OFF)
        return AHC_FALSE;

    return AHC_TRUE;
}


#if 0
void _____UART_Task_Function_________(){ruturn;} //dummy
#endif

void UARTCtrlTask_init(void)
{
    //Nop
    UartSendTrace("UARTCtrlTask_init\n\r");
}

void UARTCtrlTask(void)
{
    MMPF_OS_FLAGS       flags;
    MMPF_OS_FLAGS       waitFlags;
#if GPS_CONNECT_ENABLE
    #if(GPS_MODULE == GPS_MODULE_NMEA0183)
    NMEAINFO            *pInfo;
    NMEATIME            *pGMTtime;
    #elif(GPS_MODULE == GPS_MODULE_GMC1030)
    GPSRADARINFO        *pInfo;
    GPSRADARTIME        *pGMTtime;
    #endif
    GPS_LOG             sGPSlog={0};
#endif

    #if TPMS_FUNC_EN
    TPMSINFO            *pTPMS   = (TPMSINFO *)TPMS_Information();
    #endif
    #if GPS_CONNECT_ENABLE
    waitFlags = GPS_FLAG_INITIAL | GPS_FLAG_GETGPSPACK | GPS_FLAG_PARSE | GPS_FLAG_GETINFO | GPS_FLAG_GPSINFO2CHUCK  \
                | GPS_FLAG_SWITCHBUFFER | GPS_FLAG_SWITCHBUFFER_CLOSE ;
    #endif
    #if TPMS_FUNC_EN
    waitFlags |= TPMS_FLAG_GETTPMSPACK;
    #endif

    #if (TOUCH_UART_FUNC_EN)
    waitFlags |= Touch_Uart_FLAG_INITIAL | Touch_Uart_FLAG_GETPACK | Touch_Uart_FLAG_PARSERPACK;
    #endif

    // waitFlags can not be 0.
    waitFlags |= UART_CTL_FLAG_MAX;

    #if (GPS_CONNECT_ENABLE)
    GPSCtrl_Initial();
    #endif

    while(1)
    {
        MMPF_OS_WaitFlags( UartCtrlFlag, waitFlags, MMPF_OS_FLAG_WAIT_SET_ANY | MMPF_OS_FLAG_CONSUME, 0, &flags);

        #if GPS_CONNECT_ENABLE
        if ( flags & GPS_FLAG_INITIAL )
        {
            GPSCtrl_Initial();
        }

        if ( flags & GPS_FLAG_GETGPSPACK )
        {
            if(bGPSinitialized)
            {
                #if(GPS_MODULE == GPS_MODULE_NMEA0183)
                pInfo    = (NMEAINFO *)GPS_Information();
                pGMTtime = (NMEATIME *)GPS_GetGMTBackupTime();
                #elif(GPS_MODULE == GPS_MODULE_GMC1030)
                pInfo    = (GPSRADARINFO *)GPSRadar_Information();
                pGMTtime = (GPSRADARTIME *)GPSRadar_GetGMTBackupTime();
                #endif

                MEMSET(szGPSPack, 0, 1024);
                GPSCtrl_GetGPSPack(szGPSPack,&uiGPSPackLength);

                // Reset available counter
                #if defined(SHOW_GPS_MESSAGE_ON_PANEL_ALWAYS)&&(SHOW_GPS_MESSAGE_ON_PANEL_ALWAYS)
                ulGPS_AliveCnt  = AVALIABLE_CNT; //
                #endif

                #if(GPS_MODULE == GPS_MODULE_NMEA0183)
                GPSCtrl_ParseGPSMain(szGPSPack,uiGPSPackLength,pInfo);
                if((pInfo->iSmask == GPRMC) || (pInfo->iSmask == GNRMC))
                #elif(GPS_MODULE == GPS_MODULE_GMC1030)
                GPSCtrl_ParseGPSMain(szGPSPack,uiGPSPackLength,pInfo);
                #endif
                {
                    // Reset available counter
                    #if defined(SHOW_GPS_MESSAGE_ON_PANEL_ALWAYS)&&(0 == SHOW_GPS_MESSAGE_ON_PANEL_ALWAYS)
                    ulGPS_AliveCnt  = AVALIABLE_CNT; //show message while data is available
                    #endif
                    MEMSET(szGPSPack, 0, 1024);
                }

                {
                    #if 1//(MENU_GENERAL_TIME_ZONE_EN)
                    if(bLinkGPStime2RTC)
                    {
                        if(GPSCtrl_GPS_IsValidValue())
                        {
                            #if (MENU_STYLE == 1)
                            if (MenuSettingConfig()->uiGPSTimeSync)
                            #endif
                            {

                                if(AHC_RTC_NeedToUpdate())
                                {
                                    GPSCtrl_GMT2LocalTime(pGMTtime,&(pInfo->sUTC),m_TimeZoneTable[MenuSettingConfig()->uiTimeZone]);

                                    // Set 12 or 24 format before set GPS time to RTC.
                                    if(GPSCtrl_LinkGPSTime2RTC(&(pInfo->sUTC)) == MMP_FALSE) {
                                        GPSCtrl_EnableTimeSync( MMP_TRUE );
                                    }
                                    else {
                                        GPSCtrl_EnableTimeSync( MMP_FALSE );
                                    }
                                }
                                else {
                                    GPSCtrl_EnableTimeSync( MMP_FALSE );
                                }

                                if(GPSCtrl_NeedToLogFirstTime())
                                {
                                    GPSCtrl_GetFirstLocationTime(&sGPSlog);
                                    GPSCtrl_GMT2LocalTime(pGMTtime,&(pInfo->sUTC),m_TimeZoneTable[MenuSettingConfig()->uiTimeZone]);
                                    //GPSCtrl_LinkGPSTime2RTC(&(pInfo->sUTC));
                                    sGPSlog.ulLogID = GPS_LOG_RECORD_ID;
                                    sGPSlog.psDateTime.uwYear = pInfo->sUTC.iYear;
                                    sGPSlog.psDateTime.uwMonth = pInfo->sUTC.iMon;
                                    sGPSlog.psDateTime.uwDay = pInfo->sUTC.iDay;
                                    sGPSlog.psDateTime.uwHour = pInfo->sUTC.iHour;
                                    sGPSlog.psDateTime.uwMinute = pInfo->sUTC.iMin;
                                    sGPSlog.psDateTime.uwSecond = pInfo->sUTC.iSec;

                                    GPSCtrl_SetFirstLocationTime(&sGPSlog);
                                }
                            }
                        }
                    }
                    #endif
                }
            }
        }
        if ( flags & GPS_FLAG_SWITCHBUFFER )
        {
            AHC_DBG_MSG(0, "GPS_FLAG_SWITCHBUFFER\r\n");
            #if (GPS_RAW_FILE_ENABLE == 1)
            GPSCtrl_SwitchRawFilePingPongBuffer();
            #endif
        }
        if ( flags & GPS_FLAG_SWITCHBUFFER_CLOSE )
        {
            AHC_DBG_MSG(1, "GPS_FLAG_SWITCHBUFFER_CLOSE\r\n");
            #if (GPS_RAW_FILE_ENABLE == 1)
            GPSCtrl_SwitchRawFileClose();
            #endif
        }
        if ( flags & GPS_FLAG_GETINFO )
        {
            ubDrawCounter++;

            //if(ubDrawCounter > 5)
            {
                #if(GPS_MODULE == GPS_MODULE_NMEA0183)
                pInfo =(NMEAINFO *)GPS_Information();
                #elif(GPS_MODULE == GPS_MODULE_GMC1030)
                pInfo =(GPSRADARINFO *)GPSRadar_Information();
                #endif

                #if (GPS_CONFIG_DBG_ENABLE)
                GPSCtrl_DubugMessageInfo(pInfo);
                #endif
                #if (GPS_CONFIG_GRAPHIC_ENABLE)
                GPS_DrawInformationPage();
                #endif
                ubDrawCounter = 0;

                #if 0
                if(ubStartRecordWithGPSInfo)
                {
                    GPSCtrl_BackupGPSInfo(ulGPSInfo2ChuckCount[ubGPSBufferIndex]);
                    ulGPSInfo2ChuckCount[ubGPSBufferIndex]++;
                }
                #endif
            }
        }

        if ( flags & GPS_FLAG_GPSINFO2CHUCK )
        {
            if(AHC_GPS_Module_Attached())
            {
                UINT8 bgps_en = 0;
                if ((AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bgps_en) == AHC_TRUE) &&
                    (bgps_en != COMMON_GPS_REC_INFO_OFF)) {
                    GPSCtrl_RestoreAviChuck();
                }
            }
        }
        #endif
        #if TPMS_FUNC_EN
        if(flags & TPMS_FLAG_GETTPMSPACK)
        {
            if (TPMSCtrl_GetInitStatus())
                TPMS_UpdateData();

        }
        #endif
        #if (TOUCH_UART_FUNC_EN)
        if(flags & Touch_Uart_FLAG_INITIAL)
        {
            Touch_Uart_Ctrl_Init();
        }

        if(flags & Touch_Uart_FLAG_GETPACK)
        {
        //  AHC_DBG_MSG(1, "+++ DTV_FLAG_GETDTVPACK  \r\n");
            MEMSET(szDTVPack, 0, 512);
            Touch_Uart_Ctrl_GetString(szDTVPack,&uiDTVPackLength);
        }

        if(flags & Touch_Uart_FLAG_PARSERPACK)
        {
        //  AHC_DBG_MSG(1, "+++ DTV_FLAG_PARSEDTVPACK  \r\n");
        //  Touch_Uart_Ctrl_PARSERPACK(szDTVPack,uiDTVPackLength);
        }
        #endif

        AHC_OS_Sleep(50);
    }
}

void UARTCtrl_TaskHandler_init(void *p_arg)
{
    UartCtrlFlag = MMPF_OS_CreateEventFlagGrp(0);
    if (UartCtrlFlag >= MMPF_OS_ERR_FLAG_ID_EXCEED_MAX) {
        AHC_DBG_MSG(1, "Error:UartCtrlFlag Failed\r\n");
    }
    UARTCtrlTask_init();
}

void UARTCtrl_TaskHandler(void *p_arg)
{
    UARTCtrlTask();
}

#if 0
void _____GPS_RawFile_Emergency_Function_________(){ruturn;} //dummy
#endif

#if (GPS_RAW_FILE_EMER_EN == 1)

MMP_UBYTE GPSCtrl_GetGPSRawIndex_Emer(void)
{
    return ubGPSRawEmerBufIndex;
}

void GPSCtrl_GPSRawClearBuffer_Emer()
{
    MMP_UBYTE ubIndex = GPSCtrl_GetGPSRawIndex_Emer();
    MEMSET(&ubGPSRawEmerBuf[ubIndex],0,GPS_RAW_EMER_BUF_1SEC);
    ulGPSRawEmerBufLen[ubIndex] = 0;
}

void GPSCtrl_IncGPSRawIndex_Emer(void)
{
    ubGPSRawEmerBufIndex += 1;
    ubGPSRawEmerBufIndex = ubGPSRawEmerBufIndex % EMER_RECORD_DUAL_WRITE_PRETIME;
    GPSCtrl_GPSRawClearBuffer_Emer();
    //AHC_DBG_MSG(1, "CurrentIndex %d\r\n",ubGPSRawEmerBufIndex);
}

void GPSCtrl_SetGPSRawFileName_Emer(MMP_BYTE bFilename[], MMP_USHORT usLength)
{
    MMP_BYTE *ptr;
    MMP_USHORT i;

    ptr = (MMP_BYTE *)bFilename;

    MEMSET(ubGPSRawFileName_Emer, 0, 256);

    for (i = 0; i < usLength; i++) {
        ubGPSRawFileName_Emer[i] = *ptr++;
    }

    AHC_DBG_MSG(1, "ubGPSRawFileName_Emer : %s\r\n",ubGPSRawFileName_Emer);

    if(ulGPSRawFileId_Emer != NULL)
    {
        AHC_DBG_MSG(1, "GPS file is being written, Close first\r\n");
        AHC_FS_FileClose(ulGPSRawFileId_Emer);
//        MMPF_FS_FClose(ulGPSRawFileId_Emer);

        ulGPSRawFileId_Emer = NULL;
    }
    AHC_FS_FileOpen(ubGPSRawFileName_Emer, AHC_StrLen(ubGPSRawFileName_Emer), "w+", AHC_StrLen("w+"), &ulGPSRawFileId_Emer);
    //MMPF_FS_FOpen(ubGPSRawFileName_Emer, "w+", &ulGPSRawFileId_Emer);
}

MMP_BOOL GPSCtrl_GPSRawWriteFirst_Emer(void)
{
    UINT32 ulWriteSize = 0;
    MMP_UBYTE ubCurrentIndex = GPSCtrl_GetGPSRawIndex_Emer();
    MMP_UBYTE ubBufTime = ulGPSRawEmerBufTime;
    MMP_UBYTE i;
    #if((GSENSOR_RAW_FILE_ENABLE == 1) && (GPS_RAW_FILE_EMER_EN == 1))
    {
        if(ulGPSRawFileId_Emer != NULL)
        {
            if(ubCurrentIndex >= ubBufTime)
            {
                AHC_DBG_MSG(1, "GPSCtrl_GPSRawWriteFirst_Emer Case 1\r\n");
                for(i = (ubCurrentIndex - ubBufTime + 1); i<= ubCurrentIndex; i++)
                {
                    if(ubCurrentIndex != GPS_RAW_EMER_BUF_TIME)
                    {
                        AHC_FS_FileWrite(ulGPSRawFileId_Emer,(UINT8 *)(ubGPSRawEmerBuf+i), ulGPSRawEmerBufLen[i], &ulWriteSize);
                        MEMSET((ubGPSRawEmerBuf+i), 0, GPS_RAW_EMER_BUF_1SEC);
                        ulGPSRawEmerBufLen[i] = 0;
                    }
                }
            }else
            {
                AHC_DBG_MSG(1, "GPSCtrl_GPSRawWriteFirst_Emer Case 2\r\n");
                for(i = GPS_RAW_EMER_BUF_TIME - (ubBufTime - ubCurrentIndex); i< GPS_RAW_EMER_BUF_TIME; i++)
                {
                    AHC_FS_FileWrite(ulGPSRawFileId_Emer,(UINT8 *)(ubGPSRawEmerBuf+i), ulGPSRawEmerBufLen[i], &ulWriteSize);
                    MEMSET((ubGPSRawEmerBuf+i), 0, GPS_RAW_EMER_BUF_1SEC);
                    ulGPSRawEmerBufLen[i] = 0;
                }
                for(i = 0; i<=ubCurrentIndex;i++)
                {
                    if(ubCurrentIndex != GPS_RAW_EMER_BUF_TIME)
                    {
                        AHC_FS_FileWrite(ulGPSRawFileId_Emer,(UINT8 *)(ubGPSRawEmerBuf+i), ulGPSRawEmerBufLen[i], &ulWriteSize);
                        MEMSET((ubGPSRawEmerBuf+i), 0, GPS_RAW_EMER_BUF_1SEC);
                        ulGPSRawEmerBufLen[i] = 0;
                    }
                }
            }
            return MMP_TRUE;
        }
        else
        {
            return MMP_FALSE;
        }
    }
    #endif
}

MMP_BOOL GPSCtrl_GPSRawWrite_Emer(MMP_BYTE *pBuff, MMP_USHORT usLength)
{
    UINT32 ulWriteSize = 0;
    #if((GSENSOR_RAW_FILE_ENABLE == 1) && (GPS_RAW_FILE_ENABLE == 1))
    {
        if(ulGPSRawFileId_Emer != NULL)
        {
            AHC_FS_FileWrite(ulGPSRawFileId_Emer,(UINT8 *)pBuff, usLength, &ulWriteSize);
            //MMPF_FS_FWrite(ulGPSRawFileId_Emer,(UINT8 *)pBuff, usLength, &ulWriteSize);
            AHC_DBG_MSG(1, "GPSCtrl_GPSRawWrite_Emer %d bytes\r\n",ulWriteSize);
            return MMP_TRUE;
        }
        else
        {
            return MMP_FALSE;
        }
    }
    #endif
}

MMP_BOOL GPSCtrl_GPSRawWriteBuffer_Emer(MMP_BYTE *pBuff, MMP_USHORT usLength)
{
    MMP_UBYTE ubIndex = GPSCtrl_GetGPSRawIndex_Emer();

    #if(defined(DEVICE_GPIO_2NDSD_PLUG))

    #if(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_MASTER_SLAVE)
    if(uiGetCurrentState() == UI_VIDEO_STATE && AHC_IsSDInserted() && AHC_GetMountStorageMediaStatus() && AHC_SDMMC_IsSD1MountDCF() /*or AHC_SDMMC_IsSD2MountDCF()???*/ )
    #elif(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_COMPLEMENTARY)
    if(uiGetCurrentState() == UI_VIDEO_STATE && (AHC_IsSDInserted() || AHC_Is2ndSDInserted()) && AHC_GetMountStorageMediaStatus() && AHC_SDMMC_IsSD1MountDCF() /*or AHC_SDMMC_IsSD2MountDCF()???*/ )
    #endif

    #else//DEVICE_GPIO_2NDSD_PLUG
    if(uiGetCurrentState() == UI_VIDEO_STATE && AHC_IsSDInserted() && AHC_GetMountStorageMediaStatus() && AHC_SDMMC_IsSD1MountDCF() /*or AHC_SDMMC_IsSD2MountDCF()???*/ )
    #endif//DEVICE_GPIO_2NDSD_PLUG
    {
        if((ulGPSRawEmerBufLen[ubIndex] + usLength) < GPS_RAW_EMER_BUF_1SEC)
        {
            memcpy(&ubGPSRawEmerBuf[ubIndex][ulGPSRawEmerBufLen[ubIndex]],pBuff,usLength);
            ulGPSRawEmerBufLen[ubIndex] += usLength;
        }else
        {
            AHC_DBG_MSG(1, "GPSRawEmerBuf full\r\n");
        }
    }
    return MMP_TRUE;
}

MMP_BOOL GPSCtrl_GPSRawWriteFlushBuf_Emer(void)
{
    MMP_BOOL bCheck = MMP_TRUE;
    UINT32 ulWriteSize = 0;
    AHC_DBG_MSG(1, "GPSCtrl_GPSRawWriteFlushBuf_Emer\r\n");
    AHC_DBG_MSG(1, "ubGPSRAWBufferIndex %d\r\n",ubGPSRAWBufferIndex);
    AHC_DBG_MSG(1, "ulGPSRawEmerStartAddr %d\r\n",ulGPSRawEmerStartAddr);
    AHC_DBG_MSG(1, "ulGPSRawBufferLen_0 %d\r\n",ulGPSRawBufferLen_0);
    AHC_DBG_MSG(1, "ulGPSRawBufferLen_1 %d\r\n",ulGPSRawBufferLen_1);
    AHC_DBG_MSG(1, "ulGPSRawEmerStartAddr %d\r\n",ulGPSRawEmerStartAddr);

    if(ulGPSRawFileId_Emer != NULL)
    {
        if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)
        {
            if (ulGPSRawEmerStartAddr != 0xFFFFFFFF)
                bCheck = MMP_TRUE;
            else
                bCheck = MMP_FALSE;
        }

        if (bCheck)
        {
            if(ubGPSRAWBufferIndex == 0)
            {
                if(ulGPSRawBufferLen_0 >= ulGPSRawEmerStartAddr) {
                    //MMPF_FS_FWrite(ulGPSRawFileId_Emer,(UINT8 *)(ubGPSRawBuffer_0+ulGPSRawEmerStartAddr), ulGPSRawBufferLen_0 - ulGPSRawEmerStartAddr, &ulWriteSize);
                    AHC_FS_FileWrite(ulGPSRawFileId_Emer,(UINT8 *)(ubGPSRawBuffer_0+ulGPSRawEmerStartAddr), ulGPSRawBufferLen_0 - ulGPSRawEmerStartAddr, &ulWriteSize);
                }
                else
                {
                    ulGPSRawEmerStartAddr = 0xFFFFFFFF;
                    ulGPSRawBufferLen_0 = 0;
                }
            }
            else
            {
                if(ulGPSRawBufferLen_1 >= ulGPSRawEmerStartAddr) {
                    AHC_FS_FileWrite(ulGPSRawFileId_Emer,(UINT8 *)(ubGPSRawBuffer_1+ulGPSRawEmerStartAddr), ulGPSRawBufferLen_1 - ulGPSRawEmerStartAddr, &ulWriteSize);
                    //MMPF_FS_FWrite(ulGPSRawFileId_Emer,(UINT8 *)(ubGPSRawBuffer_1+ulGPSRawEmerStartAddr), ulGPSRawBufferLen_1 - ulGPSRawEmerStartAddr, &ulWriteSize);
                }
                else
                {
                    ulGPSRawEmerStartAddr = 0xFFFFFFFF;
                    ulGPSRawBufferLen_1 = 0;
                }
            }

        }

        if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)
        {
            ulGPSRawEmerStartAddr = 0xFFFFFFFF;
        }

        AHC_DBG_MSG(1, "ulWriteSize %d\r\n",ulWriteSize);
        return MMP_TRUE;
    }
    else
    {
        return MMP_FALSE;
    }
}

MMP_BOOL GPSCtrl_GPSRawClose_Emer(void)
{
    AHC_DBG_MSG(1, "GPSCtrl_GPSRawClose_Emer\r\n");
    if(ulGPSRawFileId_Emer != NULL)
    {
        AHC_FS_FileClose(ulGPSRawFileId_Emer);
        //MMPF_FS_FClose(ulGPSRawFileId_Emer);
        ulGPSRawFileId_Emer = NULL;
        return MMP_TRUE;
    }
    else
    {
        return MMP_FALSE;
    }
}

MMP_ULONG GPSCtrl_GetGPSRawFileId_Emer(void)
{
    if(ulGPSRawFileId_Emer != NULL)
    return ulGPSRawFileId_Emer;
    else
    return NULL;
}
void GPSCtrl_SetGPSRawStart_Emer(MMP_BOOL bStart)
{
    bStartEmergencyRecordRaw = bStart;
}
MMP_BOOL GPSCtrl_GetGPSRawStart_Emer(void)
{
    return bStartEmergencyRecordRaw;
}

void GPSCtrl_SetGPSRawBufTime_Emer(MMP_ULONG ulTime)
{
    ulGPSRawEmerBufTime = ulTime;
}

void GPSCtrl_SetGPSRawWriteFirst(MMP_BOOL bStart)
{
    bDumpEmerDone = bStart;
}

MMP_BOOL GPSCtrl_GetGPSRawWriteFirst(void)
{
    return bDumpEmerDone;
}

#endif
#if 0
void _____GPS_RawFile_Function_________(){ruturn;} //dummy
#endif

#if (GPS_RAW_FILE_ENABLE == 1)
void GPSCtrl_SetGPSRawFileName(MMP_BYTE bFilename[], MMP_USHORT usLength)
{
    MMP_BYTE *ptr;
    MMP_USHORT i;

    ptr = (MMP_BYTE *)bFilename;

    MEMSET(ubGPSRawFileName, 0, 256);

    for (i = 0; i < usLength; i++) {
        ubGPSRawFileName[i] = *ptr++;
    }

    AHC_DBG_MSG(1, "ubGPSRawFileName : %s\r\n",ubGPSRawFileName);

    if(ulGPSRawFileId != NULL)
    {
        AHC_DBG_MSG(1, "GPS file is being written, Close first\r\n");
        AHC_FS_FileClose(ulGPSRawFileId);
        //MMPF_FS_FClose(ulGPSRawFileId);
        ulGPSRawFileId = NULL;
    }

    AHC_FS_FileOpen(ubGPSRawFileName, AHC_StrLen(ubGPSRawFileName), "w+", AHC_StrLen("w+"), &ulGPSRawFileId);
    //MMPF_FS_FOpen(ubGPSRawFileName,  "w+", &ulGPSRawFileId);
}

MMP_BOOL GPSCtrl_GPSRawWrite(MMP_BYTE *pBuff, MMP_USHORT usLength)
{
    UINT32 ulWriteSize = 0;
    #if((GSENSOR_RAW_FILE_ENABLE == 1) || (GPS_RAW_FILE_ENABLE == 1))
    {
        if(ulGPSRawFileId != NULL)
        {
            AHC_DBG_MSG(1, "GPSCtrl_GPSRawWrite %d Bytes\r\n",usLength);
            AHC_FS_FileWrite(ulGPSRawFileId,(UINT8 *)pBuff, usLength, &ulWriteSize);
            //MMPF_FS_FWrite(ulGPSRawFileId,(UINT8 *)pBuff, usLength, &ulWriteSize);
            return MMP_TRUE;
        }
        else
        {
            //AHC_DBG_MSG(1, "GPS WR error\r\n");

            return MMP_FALSE;
        }
    }
    #endif
}

MMP_BOOL GPSCtrl_GPSRawWrite_Close(void)
{

    if(ubGPSRAWBufferIndex == 0)
    {
        if(ulGPSRawBufferLen_0 > 0)
        {
            GPSCtrl_GPSRawWrite(ubGPSRawBuffer_0,ulGPSRawBufferLen_0);
            MEMSET(ubGPSRawBuffer_0, 0, GPS_RAW_BUFFER_SIZE);
            ulGPSRawBufferLen_0 = 0;
        }
        ubGPSRAWBufferIndex = 1;
    }
    else
    {
        if(ulGPSRawBufferLen_1 > 0)
        {
            GPSCtrl_GPSRawWrite(ubGPSRawBuffer_1,ulGPSRawBufferLen_1);
            MEMSET(ubGPSRawBuffer_1, 0, GPS_RAW_BUFFER_SIZE);
            ulGPSRawBufferLen_1 = 0;
        }
        ubGPSRAWBufferIndex = 0;
    }
    return MMP_TRUE;
}

MMP_BOOL GPSCtrl_GPSRawFlushBuf(void)
{
    if(ubGPSRAWBufferIndex == 0)
    {
        if(ulGPSRawBufferLen_0 > 0)
        {
            GPSCtrl_GPSRawWrite(ubGPSRawBuffer_0,ulGPSRawBufferLen_0);
            MEMSET(ubGPSRawBuffer_0, 0, GPS_RAW_BUFFER_SIZE);
            ulGPSRawBufferLen_0 = 0;
        }
    }
    else
    {
        if(ulGPSRawBufferLen_1 > 0)
        {
            GPSCtrl_GPSRawWrite(ubGPSRawBuffer_1,ulGPSRawBufferLen_1);
            MEMSET(ubGPSRawBuffer_1, 0, GPS_RAW_BUFFER_SIZE);
            ulGPSRawBufferLen_1 = 0;
        }
    }
    return MMP_TRUE;
}


MMP_BOOL GPSCtrl_GPSRawWriteBuffer(MMP_BYTE *pBuff, MMP_USHORT usLength)
{
//  MMP_ULONG uiTime;
//  MMP_ULONG ulTemp;
//  MMP_UBYTE i;
//  static MMP_UBYTE ubIndex;
//  static MMP_BOOL  bEmergeFull;
    #if((GSENSOR_RAW_FILE_ENABLE == 1) || (GPS_RAW_FILE_ENABLE == 1))


    #if(defined(DEVICE_GPIO_2NDSD_PLUG))

    #if(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_MASTER_SLAVE)
    if(uiGetCurrentState() == UI_VIDEO_STATE && AHC_IsSDInserted() && AHC_GetMountStorageMediaStatus() && AHC_SDMMC_IsSD1MountDCF() /*or AHC_SDMMC_IsSD2MountDCF()???*/)
    #elif(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_COMPLEMENTARY)
    if(uiGetCurrentState() == UI_VIDEO_STATE && (AHC_IsSDInserted() || AHC_Is2ndSDInserted()) && AHC_GetMountStorageMediaStatus() && AHC_SDMMC_IsSD1MountDCF() /*or AHC_SDMMC_IsSD2MountDCF()???*/)
    #endif

    #else//DEVICE_GPIO_2NDSD_PLUG
    if(uiGetCurrentState() == UI_VIDEO_STATE && AHC_IsSDInserted() && AHC_GetMountStorageMediaStatus() && AHC_SDMMC_IsSD1MountDCF() /*or AHC_SDMMC_IsSD2MountDCF()???*/)
    #endif//DEVICE_GPIO_2NDSD_PLUG
    {
        if(ubGPSRAWBufferIndex == 0)
        {
            //AHC_DBG_MSG(1, "wr buf_0\r\n");
            if((ulGPSRawBufferLen_0 + usLength) < GPS_RAW_BUFFER_SIZE)
            {
                memcpy(&ubGPSRawBuffer_0[ulGPSRawBufferLen_0],pBuff,usLength);
                ulGPSRawBufferLen_0 += usLength;

            }else
            {
                AHC_DBG_MSG(1, "GPS Raw Buffer 0 full\r\n");
            }

        }else
        {
            //AHC_DBG_MSG(1, "wr buf_1\r\n");
            if((ulGPSRawBufferLen_1 + usLength) < GPS_RAW_BUFFER_SIZE)
            {
                memcpy(&ubGPSRawBuffer_1[ulGPSRawBufferLen_1],pBuff,usLength);
                ulGPSRawBufferLen_1 += usLength;

            }else
            {
                AHC_DBG_MSG(1, "GPS Raw Buffer 1 full\r\n");
            }
        }

    }//else
    //{
    //  GPSCtrl_GPSRawResetBuffer();
    //}
    #endif
    return MMP_TRUE;
}


MMP_BOOL GPSCtrl_GPSRawClose(void)
{
    AHC_ERR err;
    AHC_DBG_MSG(1, "GPSCtrl_GPSRawClose\r\n");
    if(ulGPSRawFileId != NULL)
    {

        err = AHC_FS_FileClose(ulGPSRawFileId);
        //err = MMPF_FS_FClose(ulGPSRawFileId);
        if(err)
        AHC_DBG_MSG(1, "GPS_ file close error 0x%x\r\n",err);
        //MMPF_FS_FClose(ulGPSRawFileId);
        ulGPSRawFileId = NULL;
        return MMP_TRUE;
    }
    else
    {
        return MMP_FALSE;
    }
}

MMP_ULONG GPSCtrl_GetGPSRawFileId(void)
{
    if(ulGPSRawFileId != NULL)
    return ulGPSRawFileId;
    else
    return NULL;
}


void GPSCtrl_SwitchRawFilePingPongBuffer(void)
{
    AHC_DBG_MSG(1, "GPSCtrl_SwitchRawFilePingPongBuffer\r\n");
    #if(GPS_RAW_FILE_EMER_EN == 1)
    if(GPSCtrl_GetGPSRawStart_Emer())
    {
        if(ulGPSRawEmerStartAddr != 0)
        {
            GPSCtrl_GPSRawWriteFlushBuf_Emer();
            ulGPSRawEmerStartAddr = 0;
        }
        else
        {
            if(ubGPSRAWBufferIndex == 0)
            GPSCtrl_GPSRawWrite_Emer(ubGPSRawBuffer_0,ulGPSRawBufferLen_0);
            else
            GPSCtrl_GPSRawWrite_Emer(ubGPSRawBuffer_1,ulGPSRawBufferLen_1);
        }
    }
    #endif

    if(ubGPSRAWBufferIndex == 0)
    {
        if(ulGPSRawBufferLen_0 > 0)
        {
            AHC_DBG_MSG(1, "Flush Buf0 %d Byte \r\n",ulGPSRawBufferLen_0);
            GPSCtrl_GPSRawWrite(ubGPSRawBuffer_0,ulGPSRawBufferLen_0);
            MEMSET(ubGPSRawBuffer_0, 0, GPS_RAW_BUFFER_SIZE);
            ulGPSRawBufferLen_0 = 0;
        }
        ubGPSRAWBufferIndex = 1;
    }
    else
    {
        if(ulGPSRawBufferLen_1 > 0)
        {
            AHC_DBG_MSG(1, "Flush Buf1 %d Byte \r\n",ulGPSRawBufferLen_1);
            GPSCtrl_GPSRawWrite(ubGPSRawBuffer_1,ulGPSRawBufferLen_1);
            MEMSET(ubGPSRawBuffer_1, 0, GPS_RAW_BUFFER_SIZE);
            ulGPSRawBufferLen_1 = 0;
        }
        ubGPSRAWBufferIndex = 0;
    }
}

void GPSCtrl_SwitchRawFileClose(void)
{
    #if (GPS_RAW_FILE_ENABLE == 1)
    {
        UINT8 bgps_en;

        if (AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bgps_en) == AHC_TRUE) {
            switch (bgps_en) {
            case RECODE_GPS_OFF:
            case RECODE_GPS_IN_VIDEO:
                // NOP
                break;

            default:
                GPSCtrl_GPSRawClose();
                break;
            }
        }
    }
    #endif
    #if (GPS_KML_FILE_ENABLE == 1)
    GPSCtrl_KMLGen_Write_TailAndClose();
    #endif
}

#if (EMERGENTRECD_SUPPORT)
void GPSCtrl_SetGPSRawBufTime_Normal(MMP_ULONG ulTime)
{
    ulGPSRawNormBufTime = ulTime;
}

MMP_UBYTE GPSCtrl_GetGPSRawIndex_Normal(void)
{
    return ubGPSRawNormBufIndex;
}
void GPSCtrl_GPSRawClearBuffer_Normal()
{
    MMP_UBYTE ubIndex = GPSCtrl_GetGPSRawIndex_Normal();
    MEMSET(&ubGPSRawNormBuf[ubIndex],0,GPS_RAW_NORM_BUF_1SEC);
    ulGPSRawNormBufLen[ubIndex] = 0;
}

MMP_BOOL GPSCtrl_GPSRawWriteBuffer_Normal(MMP_BYTE *pBuff, MMP_USHORT usLength)
{
    MMP_UBYTE ubIndex = GPSCtrl_GetGPSRawIndex_Normal();
    if(AHC_VIDEO_IsEmergRecStarted() && AHC_IsSDInserted())
    {
        if((ulGPSRawNormBufLen[ubIndex] + usLength) < GPS_RAW_NORM_BUF_1SEC)
        {
            memcpy(&ubGPSRawNormBuf[ubIndex][ulGPSRawNormBufLen[ubIndex]],pBuff,usLength);
            ulGPSRawNormBufLen[ubIndex] += usLength;
        }else
        {
            AHC_DBG_MSG(1, "GPSRawNormBuf full\r\n");
        }
    }
    return MMP_TRUE;
}

void GPSCtrl_IncGPSRawIndex_Normal(void)
{
    ubGPSRawNormBufIndex += 1;
    ubGPSRawNormBufIndex = (ubGPSRawNormBufIndex)%(2);
    GPSCtrl_GPSRawClearBuffer_Normal();
}

MMP_BOOL GPSCtrl_GPSRawWriteFirst_Normal(void)
{
    UINT32 ulWriteSize = 0;
    MMP_UBYTE ubCurrentIndex = GPSCtrl_GetGPSRawIndex_Normal();
    MMP_UBYTE ubBufTime = ulGPSRawNormBufTime;
    MMP_UBYTE i;
    AHC_DBG_MSG(1, "ubCurrentIndex : %d\r\n",ubCurrentIndex);
    AHC_DBG_MSG(1, "ulGPSRawNormBufTime : %d\r\n",ulGPSRawNormBufTime);

    #if((GPS_RAW_FILE_ENABLE == 1) || (GSENSOR_RAW_FILE_ENABLE == 1))
    {
        if((ulGPSRawFileId != NULL))
        {
            if(ubCurrentIndex >= ubBufTime)
            {
                AHC_DBG_MSG(1, "GPSCtrl_GPSRawWriteFirst_Normal Case 1\r\n");
                for(i = (ubCurrentIndex - ubBufTime + 1); i<= ubCurrentIndex; i++)
                {
                    if(ubCurrentIndex != GPS_RAW_NORM_BUF_TIME)
                    {
                        AHC_FS_FileWrite(ulGPSRawFileId,(UINT8 *)(ubGPSRawNormBuf+i), ulGPSRawNormBufLen[i], &ulWriteSize);
                        //MMPF_FS_FWrite(ulGPSRawFileId,(UINT8 *)(ubGPSRawNormBuf+i), ulGPSRawNormBufLen[i], &ulWriteSize);
                        AHC_DBG_MSG(1, "wr ubGPSRawNormBuf[%d] : %d Bytes\r\n",i, ulWriteSize);
                        MEMSET((ubGPSRawNormBuf+i), 0, GPS_RAW_NORM_BUF_1SEC);
                        ulGPSRawNormBufLen[i] = 0;
                    }
                }
            }
            else
            {
                AHC_DBG_MSG(1, "GPSCtrl_GPSRawWriteFirst_Norm Case 2\r\n");
                for(i = GPS_RAW_NORM_BUF_TIME - (ubBufTime - ubCurrentIndex); i< GPS_RAW_NORM_BUF_TIME; i++)
                {
                    //MMPF_FS_FWrite(ulGPSRawFileId,(UINT8 *)(ubGPSRawNormBuf+i), ulGPSRawNormBufLen[i], &ulWriteSize);
                    AHC_FS_FileWrite(ulGPSRawFileId,(UINT8 *)(ubGPSRawNormBuf+i), ulGPSRawNormBufLen[i], &ulWriteSize);
                    AHC_DBG_MSG(1, "wr ubGPSRawNormBuf[%d] : %d Bytes\r\n",i, ulWriteSize);
                    MEMSET((ubGPSRawNormBuf+i), 0, GPS_RAW_NORM_BUF_1SEC);
                    ulGPSRawNormBufLen[i] = 0;
                }
                for(i = 0; i<=ubCurrentIndex;i++)
                {
                    if(ubCurrentIndex != GPS_RAW_NORM_BUF_TIME)
                    {
                        //MMPF_FS_FWrite(ulGPSRawFileId,(UINT8 *)(ubGPSRawNormBuf+i), ulGPSRawNormBufLen[i], &ulWriteSize);
                        AHC_FS_FileWrite(ulGPSRawFileId,(UINT8 *)(ubGPSRawNormBuf+i), ulGPSRawNormBufLen[i], &ulWriteSize);
                        AHC_DBG_MSG(1, "wr ubGPSRawNormBuf[%d] : %d Bytes\r\n",i, ulWriteSize);
                        MEMSET((ubGPSRawNormBuf+i), 0, GPS_RAW_NORM_BUF_1SEC);
                        ulGPSRawNormBufLen[i] = 0;
                    }
                }
            }
            return MMP_TRUE;
        }
        else if ((MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE) && (ulGPSRawNormBufTime == 0))
        {
            return MMP_TRUE;
        }
        else
        {
            return MMP_FALSE;
        }

    }
    #endif
}
#endif

void GPSCtrl_GPSRawResetBuffer(void)
{
    MEMSET(ubGPSRawBuffer_0, 0, GPS_RAW_BUFFER_SIZE);
    MEMSET(ubGPSRawBuffer_1, 0, GPS_RAW_BUFFER_SIZE);
    ulGPSRawBufferLen_0 = 0;
    ulGPSRawBufferLen_1 = 0;
    ubGPSRAWBufferIndex = 0;
}

#else

MMP_BOOL GPSCtrl_GPSRawClose(void)
{
    // Null Function
    return MMP_TRUE;
}
#endif

MMP_BOOL GPSCtrl_EnableStatus(void)
{
    #if (GPS_CONNECT_ENABLE)
    return bGPSPWRStatus;
    #else
    return MMP_FALSE;
    #endif
}

#if (GPS_CONNECT_ENABLE)
MMP_BOOL SetTimeZoneTable(signed char* pTable, MMP_ULONG TableSize)
{

    if (TableSize > MAX_TIMEZONE_TABLE_SIZE)
        return MMP_FALSE;

    memcpy(m_TimeZoneTable, pTable, TableSize);
    return MMP_TRUE;
}

const signed char* GetTimeZoneTable(void)
{
    return (const signed char*)m_TimeZoneTable;
}

void GPSCtrl_EnableTimeSync(MMP_BOOL bEnable)
{
    bLinkGPStime2RTC = bEnable;
}

#if (AHC_SHAREENC_SUPPORT)
AHC_BOOL AHC_GPS_StartSHAREPreRec(MMP_ULONG PreRecTime)
{
    MEMSET(sGPSInfo2Chuck_Pre_SHARE, 0, sizeof(sGPSInfo2Chuck_Pre_SHARE));
    if (PreRecTime > 0)
    {
        ulGPSTCount_Pre_SHARE = PreRecTime / 1000;
        ulGPSCount_Pre_SHARE = 0;
    }

    return AHC_TRUE;
}

AHC_BOOL AHC_GPS_SetSHAREIndex(void)
{
    MMP_ULONG idx_nor, idx_pre;
    //m_bStartGPS_SHARE = (m_bStartGPS_SHARE)?(MMP_FALSE):(MMP_TRUE);

    if (m_bStartGPS_SHARE)  // normal -> prerec
    {
        MEMSET(sGPSInfo2Chuck_Pre_SHARE, 0, sizeof(sGPSInfo2Chuck_Pre_SHARE));
        ulGPSCount_Pre_SHARE = 0;
        //MEMSET(sGPSInfo2Chuck_SHARE, 0, sizeof(sGPSInfo2Chuck_SHARE));
        ulGPSCount_SHARE = 0;
        m_bStartGPS_SHARE = MMP_FALSE;
    }
    else if (m_bStartGPS_SHARE == MMP_FALSE)                    // prerec -> normal
    {
        MEMSET(sGPSInfo2Chuck_SHARE, 0, sizeof(sGPSInfo2Chuck_SHARE));
        m_bStartGPS_SHARE = MMP_TRUE;
    }

    if (m_bStartGPS_SHARE)
    {
        if (ulGPSCount_Pre_SHARE > 0)
        {
            ulGPSCount_SHARE = ulGPSTCount_Pre_SHARE;

            idx_pre = ulGPSCount_Pre_SHARE - 1;
            idx_nor = ulGPSCount_SHARE - 1;

            do {
                sGPSInfo2Chuck_SHARE[idx_nor] = sGPSInfo2Chuck_Pre_SHARE[idx_pre];
                if (idx_pre > 0)
                    idx_pre--;
                else
                    idx_pre = ulGPSTCount_Pre_SHARE - 1;

                if (idx_nor > 0)
                    idx_nor--;
                else
                    break;
            } while (idx_pre != (ulGPSCount_Pre_SHARE - 1));
        }
        else
        {
            ulGPSCount_SHARE = 0;
        }
    }

    return AHC_TRUE;
}
#endif

//-------------------------------------------------------------------------------------------
//  Function    : AHC_GPS_RestorePreRecordInfo
//  Description : Copy GPS data from start of Pre-record to beginning of GPS buffer
//-------------------------------------------------------------------------------------------
void AHC_GPS_RestorePreRecordInfo( UINT32 ulPreRecordTime, MMP_BOOL bUseLastData )
{
    UINT32 ulPreRecordNumber = ( ulPreRecordTime * gGPS_Attribute.ubStoreFreq ) / 1000;

    if( ulPreRecordNumber > GPS_CONFIG_MAXGPSINFONUM )
    {
        AHC_DBG_MSG(1, FG_RED("ERROR: Too many Pre-record data for GPS buffer [%d]\r\n"), ulPreRecordNumber);
        return;
    }

    AHC_DBG_MSG(1, FG_BLUE("GPS Restore PreRecord Cnt [%d]\r\n"), ulPreRecordNumber);

    ulGPSInfoFileByte = 0; // Reset ulGPSInfoFileByte since it's not used

    if( ubGPSBufferIndex == 0 )
    {
        if( ulGPSCount_0 < ulPreRecordNumber ) // Need to copy data from ping-pong buffer
        {
            UINT32 ulCopyNumber = ulPreRecordNumber - ulGPSCount_0;

            if( bUseLastData == MMP_TRUE )
            {
                if( ubGPSBufferIndex_Last == 0)
                {
                    memcpy( &sGPSInfo2Chuck_1[0], &sGPSInfo2Chuck_0[ulGPSCount_Last - ulCopyNumber], ulCopyNumber*sizeof(GPSINFOCHUCK) );
                }
                else
                {
                    memcpy( &sGPSInfo2Chuck_1[0], &sGPSInfo2Chuck_1[ulGPSCount_Last - ulCopyNumber], ulCopyNumber*sizeof(GPSINFOCHUCK) );
                }
            }
            else
            {
                memcpy( &sGPSInfo2Chuck_1[0], &sGPSInfo2Chuck_1[GPS_CONFIG_MAXGPSINFONUM - ulCopyNumber], ulCopyNumber*sizeof(GPSINFOCHUCK) );
            }
            memcpy( &sGPSInfo2Chuck_1[ulCopyNumber], &sGPSInfo2Chuck_0[0], ulGPSCount_0*sizeof(GPSINFOCHUCK) );
        }
        else
        {
            memcpy( &sGPSInfo2Chuck_1[0], &sGPSInfo2Chuck_0[ulGPSCount_0 - ulPreRecordNumber], ulPreRecordNumber*sizeof(GPSINFOCHUCK) );
        }

        ubGPSBufferIndex = 1;
        ulGPSCount_1 = ulPreRecordNumber;
        ulGPSCount_0 = 0;
    }
    else //ubGPSBufferIndex == 1
    {
        if( ulGPSCount_1 < ulPreRecordNumber ) // Need to copy data from ping-pong buffer
        {
            UINT32 ulCopyNumber = ulPreRecordNumber - ulGPSCount_1;
            if( bUseLastData == MMP_TRUE )
            {
                if( ubGPSBufferIndex_Last == 0)
                {
                    memcpy( &sGPSInfo2Chuck_0[0], &sGPSInfo2Chuck_0[ulGPSCount_Last - ulCopyNumber], ulCopyNumber*sizeof(GPSINFOCHUCK) );
                }
                else
                {
                    memcpy( &sGPSInfo2Chuck_0[0], &sGPSInfo2Chuck_1[ulGPSCount_Last - ulCopyNumber], ulCopyNumber*sizeof(GPSINFOCHUCK) );
                }
            }
            else
            {
                memcpy( &sGPSInfo2Chuck_0[0], &sGPSInfo2Chuck_0[GPS_CONFIG_MAXGPSINFONUM - ulCopyNumber], ulCopyNumber*sizeof(GPSINFOCHUCK) );
            }
            memcpy( &sGPSInfo2Chuck_0[ulCopyNumber], &sGPSInfo2Chuck_1[0], ulGPSCount_1*sizeof(GPSINFOCHUCK) );
        }
        else
        {
            memcpy( &sGPSInfo2Chuck_0[0], &sGPSInfo2Chuck_1[ulGPSCount_1 - ulPreRecordNumber], ulPreRecordNumber*sizeof(GPSINFOCHUCK) );
        }

        ubGPSBufferIndex = 0;
        ulGPSCount_0 = ulPreRecordNumber;
        ulGPSCount_1 = 0;
    }
}

void AHC_GPS_TriggerRestorePreRecordInfo( MMP_BOOL bTrigger, UINT32 ulPreRecordTime, MMP_BOOL bUseLastData )
{
    m_bGPS_TriggerRestorePreRecordInfo = bTrigger;
    m_ulGpsPreRecordTime = ulPreRecordTime;
    bGPSUseLastData = bUseLastData;
}

MMP_BOOL AHC_GPS_NeedToRestorePreRecordInfo( UINT32* ulPreRecordTime )
{
    if( m_ulGpsPreRecordTime != GPS_DEFAULT_PRERECORD_TIME )
    {
        *ulPreRecordTime = m_ulGpsPreRecordTime;
    }

    return m_bGPS_TriggerRestorePreRecordInfo;
}

void AHC_GPS_FlushBackupBuffer(MMP_UBYTE ubID, MMP_BOOL bEnable)
{
    m_bGPS_FlushBackupBuffer[ubID] = bEnable;
}

MMP_BOOL AHC_GPS_NeedToFlushBackupBuffer(MMP_UBYTE ubID)
{
    return m_bGPS_FlushBackupBuffer[ubID];
}

AHC_BOOL AHC_GPS_SetCurInfo(void)
{
#if (GPS_CONNECT_ENABLE)
    MMPF_OS_SetFlags(UartCtrlFlag, GPS_FLAG_GPSINFO2CHUCK, MMPF_OS_FLAG_SET);
#endif
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GPS_Module_Attached
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_GPS_Module_Attached(void)
{
#if (GPS_MODULE_ATT_COMPILER)
    #if (GPS_CONNECT_ENABLE)
    return AHC_TRUE;
    #else
    return AHC_FALSE;
    #endif
#elif (GPS_MODULE_ATT_GPIO)
    UINT8 ubValue = AHC_FALSE;

    if (GPS_MODULE_GPIO != MMP_GPIO_MAX)
    {
        AHC_GPIO_GetData(GPS_MODULE_GPIO, &ubValue);
        return ubValue;
    }
    else
    {
        return AHC_FALSE;
    }
#endif
    return AHC_FALSE;
}

#endif
