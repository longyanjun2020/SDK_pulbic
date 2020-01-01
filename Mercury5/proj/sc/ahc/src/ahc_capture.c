/**
 @file AHC_Capture.c
 @brief AHC capture control Function
 @author
 @version 1.0
*/

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "AHC_Config_SDK.h"
#include "ahc_capture.h"
#include "ahc_display.h"
#include "ahc_uf.h"
#include "ahc_dcf.h"
#include "ahc_gui.h"
#include "ahc_utility.h"
#include "ahc_sensor.h"
#include "ahc_parameter.h"
#include "ahc_isp.h"
#include "ahc_version.h"
#include "ahc_usb.h"
#include "ahc_usbhost.h"
#include "ahc_menu.h"
#include "ahc_message.h"
#include "mmp_dsc_inc.h"
#include "mmp_err.h"
#include "mmps_dsc.h"
#include "mmps_sensor.h"
#include "mmpf_jpeg_enc.h"
#include "mmpf_jpeg_enc_rc.h"
#include "ptz_cfg.h"
#include "snr_cfg.h"
#include "ait_utility.h"
#include "MenuSetting.h"
#if (GPS_CONNECT_ENABLE)
#include "gps_ctl.h"
#endif
#ifdef UUID_XML_FEATURE
    #if (UUID_XML_FEATURE == 1)
    #include "UUID_XML_FUNC.h"
    #endif
#endif

#include "component_jpe.h"

/** @addtogroup AHC_CAPTURE
@{
*/

/*===========================================================================
 * Global varible
 *===========================================================================*/

// JPEG Spec. suggestion
static const UINT8 AHC_JPEG_QTABLE_LUMA[64] =
{
    16,  11,  12,  14,  12,  10,  16,  14,
    13,  14,  18,  17,  16,  19,  24,  40,
    26,  24,  22,  22,  24,  49,  35,  37,
    29,  40,  58,  51,  61,  60,  57,  51,
    56,  55,  64,  72,  92,  78,  64,  68,
    87,  69,  55,  56,  80, 109,  81,  87,
    95,  98, 103, 104, 103,  62,  77, 113,
   121, 112, 100, 120,  92, 101, 103,  99
};

static const UINT8 AHC_JPEG_QTABLE_CHROMA[64] =
{
    17,  18,  18,  24,  21,  24,  47,  26,
    26,  47,  99,  66,  56,  66,  99,  99,
    99,  99,  99,  99,  99,  99,  99,  99,
    99,  99,  99,  99,  99,  99,  99,  99,
    99,  99,  99,  99,  99,  99,  99,  99,
    99,  99,  99,  99,  99,  99,  99,  99,
    99,  99,  99,  99,  99,  99,  99,  99,
    99,  99,  99,  99,  99,  99,  99,  99
};

static UINT16   m_u16ReviewTime     = 0;    // Unit:ms
static UINT16   m_u16WindowsTime    = 0;    // Unit:ms
static UINT32   m_u32StillImageW[2] = {1600, 1600};
static UINT32   m_u32StillImageH[2] = {1200, 1200};
static UINT32   m_u32ImageTgtSizeInKB[2] = {0, 0}; // Unit:KByte
static UINT16   m_u16ThumbCustomW   = 160;
static UINT16   m_u16ThumbCustomH   = 120;
static UINT32   m_u32TimeStampCfg   = ( AHC_ACC_TIMESTAMP_ENABLE     |
                                        AHC_ACC_TIMESTAMP_DATE_ONLY  |
                                        AHC_CAPTURE_STICKER_POS      |
                                        AHC_ACC_TIMESTAMP_FORMAT_1);

#if (AHC_CAPTURE_SYNC_STAMP_FILENAME)
static UINT8    m_u8PrmCaptureFileName[32] = {0};
static UINT8    m_u8ScdCaptureFileName[32] = {0};
#endif

static UINT16   m_u16ContiShotMaxNum    = 5;
static UINT16   m_u16ContiShotInterval  = 200; // Unit:ms

#if (ENABLE_DEBUG_AFTER_JPG)
static UINT8    m_ubDebugMessageBuffer[MAX_DBG_ARRAY_SIZE]={0};
#endif

static AHC_BOOL m_bAhcCaptureInitISP = AHC_FALSE;

/*===========================================================================
 * Extern variable
 *===========================================================================*/

extern AHC_BOOL gbAhcDbgBrk;
/*===========================================================================
 * Main body
 *===========================================================================*/

#if 0
void _____Local_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : CaptureAnaDecSnrSrcTypeHandler
//  Description : This Callback function will be called once TV source is changed or removed.
//  InParam     : byTvSrcType - TV type: 0 - None, 1 - PAL, 2 - NTSC
//                byFlag - Reserved
//------------------------------------------------------------------------------
static void CaptureAnaDecSnrSrcTypeHandler(MMP_UBYTE ubSrcType, MMP_UBYTE ubFlag)
{
    if (!CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
        return;
    }

    if ((ubSrcType == MMP_SNR_ANADEC_SRC_NO_READY) ||
        (ubSrcType == MMP_SNR_ANADEC_SRC_DISCNT)) {
        MMPS_Display_EnableScdAnaDecSnrPreviewWindow(MMPS_PREVIEW_UI_MODE_DSC, MMP_FALSE);

        MMPS_DSC_EnablePreviewDisplay(gsAhcScdSensor, MMP_FALSE, MMP_FALSE);

        MMPS_Display_EnableScdAnaDecSnrPreview(MMPS_PREVIEW_UI_MODE_DSC, MMP_FALSE);
    }
    else {
        AHC_Capture_SetScdCamCaptSetting();

        MMPS_DSC_AdjustScdCapturePipe(gsAhcScdSensor);
        MMPS_DSC_AdjustScdPreviewPipe(gsAhcScdSensor);

        MMPS_Display_EnableScdAnaDecSnrPreview(MMPS_PREVIEW_UI_MODE_DSC, MMP_TRUE);

        MMPS_DSC_EnablePreviewDisplay(gsAhcScdSensor, MMP_TRUE, MMP_FALSE);
    }

    AHC_SetCurKeyEventID(BUTTON_TV_DECODER_SRC_TYPE);
    AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_TV_DECODER_SRC_TYPE, 0);
}

#if 0
void _____EXIF_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_SetImageEXIF
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set image EXIF

 This function sets the fields in EXIF. The contents of the field are read from
 the AHC_SET_EXIF_MEM_LOCATION memory location, default : width/height/s8Date.
 Parameters:
 @param[in] pData       The update data buffer.
 @param[in] u32DataSize update data size.
 @param[in] u16IfdIdx   The IFD index of tag field.
 @param[in] u16TagID    The ID of tag field.
 @param[in] u16Type     The type of tag.
 @param[in] u16Count    Set the amount of entries of uwType.

 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_Capture_SetImageEXIF(UINT8 *pData, UINT32 u32DataSize, UINT16 u16IfdIdx, UINT16 u16TagID, UINT16 u16Type, UINT16 u16Count)
{
    return MMPS_DSC_SetImageEXIF((MMP_UBYTE *)pData, (MMP_ULONG)u32DataSize, (MMP_USHORT)u16IfdIdx, (MMP_USHORT)u16TagID, (MMP_USHORT)u16Type, (MMP_USHORT)u16Count);
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_GetImageEXIF
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get EXIF Setting

 This API gets EXIF Setting
 Parameters:
 @param[in]  Index EXIF Index
 @param[out] pExif EXIF setting
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_Capture_GetImageEXIF(UINT32 u32Index, AHC_EXIF_CONFIG *pstExif)
{
    return MMPS_DSC_GetImageEXIF(u32Index, (MMPS_DSC_EXIF_CONFIG *)pstExif);
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_OpenEXIFFileByName
//  Description : Open EXIF file by the file name
//------------------------------------------------------------------------------
AHC_BOOL AHC_Capture_OpenEXIFFileByName(UINT8 *pu8FileName)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    eRetErr = MMPS_DSC_OpenEXIFFile(pu8FileName, EXIF_NODE_ID_PRIMARY);

    return (eRetErr == MMP_ERR_NONE) ? AHC_TRUE : AHC_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_CloseEXIFFile
//  Description : Close EXIF file
//------------------------------------------------------------------------------
AHC_BOOL AHC_Capture_CloseEXIFFile(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    eRetErr = MMPS_DSC_CloseEXIFFile(EXIF_NODE_ID_PRIMARY);

    return (eRetErr == MMP_ERR_NONE) ? AHC_TRUE : AHC_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_ConfigRtcEXIF
//  Description : Config EXIF Related to time
//------------------------------------------------------------------------------
AHC_BOOL AHC_Capture_ConfigRtcEXIF(void)
{
    #define EXIF_DATE_LENGTH    20

    UINT16      u16Year, u16Month, u16Day, u16DayInWeek, u16Hour, u16Minute, u16Second;
    UINT8       u8AmOrPm, u8_12FormatEn;

    INT8        StrYear[8], StrMonth[8], StrDay[8], StrHour[8], StrMinute[8], StrSecond[8], s8Date[EXIF_DATE_LENGTH] = {0};
    AHC_BOOL    bSuccess = AHC_FALSE;

    AHC_SetParam(PARAM_ID_USE_RTC, 1);

    bSuccess = AHC_GetClock(&u16Year, &u16Month, &u16Day, &u16DayInWeek, &u16Hour, &u16Minute, &u16Second, &u8AmOrPm, &u8_12FormatEn);

    AHC_Utility_Int2Str(u16Year  , StrYear);
    AHC_Utility_Int2Str(u16Month , StrMonth);
    AHC_Utility_Int2Str(u16Day   , StrDay);
    AHC_Utility_Int2Str(u16Hour  , StrHour);
    AHC_Utility_Int2Str(u16Minute, StrMinute);
    AHC_Utility_Int2Str(u16Second, StrSecond);

    MEMSET(s8Date, 0, sizeof(s8Date));

    STRCPY(s8Date, StrYear);
    STRCAT(s8Date, ":");

    if (u16Month < 10)
        STRCAT(s8Date, "0");

    STRCAT(s8Date, StrMonth);
    STRCAT(s8Date, ":");

    if (u16Day < 10)
        STRCAT(s8Date, "0");

    STRCAT(s8Date, StrDay);

    STRCAT(s8Date, " ");

    if (u16Hour < 10)
        STRCAT(s8Date, "0");

    STRCAT(s8Date, StrHour);
    STRCAT(s8Date, ":");

    if (u16Minute < 10)
        STRCAT(s8Date, "0");

    STRCAT(s8Date, StrMinute);
    STRCAT(s8Date, ":");

    if (u16Second < 10)
        STRCAT(s8Date, "0");

    STRCAT(s8Date, StrSecond);

    AHC_Capture_SetImageEXIF((UINT8*)s8Date, EXIF_DATE_LENGTH, IFD_IDX_IFD0,      IFD0_DATE_TIME,             EXIF_TYPE_ASCII, EXIF_DATE_LENGTH);
    AHC_Capture_SetImageEXIF((UINT8*)s8Date, EXIF_DATE_LENGTH, IFD_IDX_EXIFIFD,   EXIFIFD_DATETIMEORIGINAL,   EXIF_TYPE_ASCII, EXIF_DATE_LENGTH);
    AHC_Capture_SetImageEXIF((UINT8*)s8Date, EXIF_DATE_LENGTH, IFD_IDX_EXIFIFD,   EXIFIFD_DATETIMECREATE,     EXIF_TYPE_ASCII, EXIF_DATE_LENGTH);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_ConfigSysInfoEXIF
//  Description : Config EXIF Related to System Info
//------------------------------------------------------------------------------
AHC_BOOL AHC_Capture_ConfigSysInfoEXIF(void)
{
    MMP_BYTE   exif_ver[] = {'V', '2', '.', '3'};       // Customer request format.
    //MMP_BYTE   exif_ver[] = {0x30, 0x32, 0x33, 0x30}; // Default format 0230 means version 2.3
    MMP_ULONG  ulExifIfdOffset = 0;
    MMP_USHORT exif_orientation = 1;
    MMP_ULONG  exif_res[2] = {300, 1};
    MMP_USHORT exif_res_unit = 2;
    MMP_USHORT ycc_pos = 1 ;
    MMP_UBYTE  exif_sensingmethod = 2;
    MMP_UBYTE  exif_scenetype = 1;
    MMP_USHORT flash = 0x00;
    MMP_USHORT colorspace = 0x01;
    MMP_USHORT scene_capture_type = 0x00;
    MMP_USHORT gain_control = 0x00;
    MMP_USHORT contrast = 0x00;
    MMP_USHORT saturation = 0x00;
    MMP_USHORT sharpness = 0x00;
    MMP_USHORT exposureprogram = 0x02 ;
    MMP_UBYTE  components[4] = {1, 2, 3, 0};
    MMP_ULONG  focallength[2] = {68, 10};
    MMP_ULONG  aperture[2] = {37, 10};
    MMP_ULONG  maxaperture[2] = {38, 10};

    AHC_Capture_SetImageEXIF((UINT8*)&ulExifIfdOffset          , 4                                    , IFD_IDX_IFD0, IFD0_EXIF_OFFSET  , EXIF_TYPE_LONG , 1);

    #if (EXIF_ENABLE_MAKER_INFO == 1)
    AHC_Capture_SetImageEXIF((UINT8*)AHC_EXIF_DEFAULT_MAKER    , STRLEN(AHC_EXIF_DEFAULT_MAKER)       , IFD_IDX_IFD0, IFD0_MAKE         , EXIF_TYPE_ASCII, STRLEN(AHC_EXIF_DEFAULT_MAKER));
    AHC_Capture_SetImageEXIF((UINT8*)AHC_EXIF_DEFAULT_MODEL    , STRLEN(AHC_EXIF_DEFAULT_MODEL)       , IFD_IDX_IFD0, IFD0_MODEL        , EXIF_TYPE_ASCII, STRLEN(AHC_EXIF_DEFAULT_MODEL));
    AHC_Capture_SetImageEXIF((UINT8*)AHC_EXIF_DEFAULT_SOFTWARE , STRLEN(AHC_EXIF_DEFAULT_SOFTWARE)    , IFD_IDX_IFD0, IFD0_SOFTWARE     , EXIF_TYPE_ASCII, STRLEN(AHC_EXIF_DEFAULT_SOFTWARE));
    AHC_Capture_SetImageEXIF((UINT8*)AHC_EXIF_DEFAULT_ARTIST   , STRLEN(AHC_EXIF_DEFAULT_ARTIST)      , IFD_IDX_IFD0, IFD0_ARTIST       , EXIF_TYPE_ASCII, STRLEN(AHC_EXIF_DEFAULT_ARTIST));
    AHC_Capture_SetImageEXIF((UINT8*)AHC_EXIF_DEFAULT_COPYRIGHT, STRLEN(AHC_EXIF_DEFAULT_COPYRIGHT)   , IFD_IDX_IFD0, IFD0_COPYRIGHT    , EXIF_TYPE_ASCII, STRLEN(AHC_EXIF_DEFAULT_COPYRIGHT));
    #endif

    AHC_Capture_SetImageEXIF((UINT8*)&exif_ver              , 4,  IFD_IDX_EXIFIFD,  EXIFIFD_VERSION         , EXIF_TYPE_ASCII   , 4);
    AHC_Capture_SetImageEXIF((UINT8*)&exif_orientation      , 2,  IFD_IDX_IFD0,     IFD0_ORIENTATION        , EXIF_TYPE_SHORT   , 1);
    AHC_Capture_SetImageEXIF((UINT8*)&exif_res              , 8,  IFD_IDX_IFD0,     IFD0_X_RESOLUTION       , EXIF_TYPE_RATIONAL, 1);
    AHC_Capture_SetImageEXIF((UINT8*)&exif_res              , 8,  IFD_IDX_IFD0,     IFD0_Y_RESOLUTION       , EXIF_TYPE_RATIONAL, 1);
    AHC_Capture_SetImageEXIF((UINT8*)&exif_res_unit         , 2,  IFD_IDX_IFD0,     IFD0_RESOLUTION_UNIT    , EXIF_TYPE_SHORT   , 1);
    AHC_Capture_SetImageEXIF((UINT8*)&ycc_pos               , 2,  IFD_IDX_IFD0,     IFD0_YCBCR_POSITION     , EXIF_TYPE_SHORT   , 1);
    AHC_Capture_SetImageEXIF((UINT8*)&exif_sensingmethod    , 1,  IFD_IDX_IFD0,     IFD0_SENSINGMETHOD      , EXIF_TYPE_BYTE    , 1);
    AHC_Capture_SetImageEXIF((UINT8*)&exif_scenetype        , 1,  IFD_IDX_EXIFIFD,  EXIFIFD_SCENETYPE       , EXIF_TYPE_BYTE    , 1);
    AHC_Capture_SetImageEXIF((UINT8*)&flash                 , 2,  IFD_IDX_EXIFIFD,  EXIFIFD_FLASH           , EXIF_TYPE_SHORT   , 1);
    AHC_Capture_SetImageEXIF((UINT8*)&colorspace            , 2,  IFD_IDX_EXIFIFD,  EXIFIFD_COLORSPACE      , EXIF_TYPE_SHORT   , 1);
    AHC_Capture_SetImageEXIF((UINT8*)&scene_capture_type    , 2,  IFD_IDX_EXIFIFD,  EXIFIFD_SCENE_CAP_TYPE  , EXIF_TYPE_SHORT   , 1);
    AHC_Capture_SetImageEXIF((UINT8*)&gain_control          , 2,  IFD_IDX_EXIFIFD,  EXIFIFD_GAINCONTROL     , EXIF_TYPE_SHORT   , 1);
    AHC_Capture_SetImageEXIF((UINT8*)&contrast              , 2,  IFD_IDX_EXIFIFD,  EXIFIFD_CONTRAST        , EXIF_TYPE_SHORT   , 1);
    AHC_Capture_SetImageEXIF((UINT8*)&saturation            , 2,  IFD_IDX_EXIFIFD,  EXIFIFD_SATURATION      , EXIF_TYPE_SHORT   , 1);
    AHC_Capture_SetImageEXIF((UINT8*)&sharpness             , 2,  IFD_IDX_EXIFIFD,  EXIFIFD_SHARPNESS       , EXIF_TYPE_SHORT   , 1);
    AHC_Capture_SetImageEXIF((UINT8*)&components            , 4,  IFD_IDX_EXIFIFD,  EXIFIFD_COMPONENTS      , EXIF_TYPE_BYTE    , 4);
    AHC_Capture_SetImageEXIF((UINT8*)&focallength           , 8,  IFD_IDX_EXIFIFD,  EXIFIFD_FOCAL_LENGTH    , EXIF_TYPE_RATIONAL, 1);
    AHC_Capture_SetImageEXIF((UINT8*)&aperture              , 8,  IFD_IDX_EXIFIFD,  EXIFIFD_APERTURE        , EXIF_TYPE_RATIONAL, 1);
    AHC_Capture_SetImageEXIF((UINT8*)&maxaperture           , 8,  IFD_IDX_EXIFIFD,  EXIFIFD_MAX_APERTURE    , EXIF_TYPE_RATIONAL, 1);
    AHC_Capture_SetImageEXIF((UINT8*)&exposureprogram       , 2,  IFD_IDX_EXIFIFD,  EXIFIFD_EXPO_PROGRAM    , EXIF_TYPE_SHORT   , 1);

    #if (GPS_CONNECT_ENABLE)
    if (AHC_GPS_Module_Attached())
    {
        MMP_ULONG  ulVersion = 2;
        MMP_ULONG  ulGPSoffset = 0;
        MMP_ULONG  ulGpsLatitude[6] = {50, 1, 40, 1,30, 1};
        MMP_ULONG  ulGpsLongitude[6] = {30, 1, 20, 1,10, 1};
        MMP_ULONG  ulGpsTimeStamp[6] = {24, 2, 60, 2, 25, 3};
        MMP_UBYTE  ubNS[2];
        MMP_UBYTE  ubWE[2];
        MMP_UBYTE  ubSpeedRef[2];
        MMP_ULONG  ulSpeed[2] = {123, 2};
        MMP_UBYTE  ubAltitudeRef;
        MMP_ULONG  ulSeeAltitude[2] = {111, 2};
        MMP_USHORT usDegree,usMin;
        double     usSec;

        #if (GPS_MODULE == GPS_MODULE_NMEA0183)
        NMEAINFO   *pInfo;
        pInfo =(NMEAINFO *)GPS_Information();
        #elif (GPS_MODULE == GPS_MODULE_GMC1030)
        GPSRADARINFO   *pInfo;
        pInfo =(GPSRADARINFO *)GPSRadar_Information();
        #endif

        ubNS[0] = 'N';
        ubNS[1] = 0;
        ubWE[0] = 'E';
        ubWE[1] = 0;

        ubSpeedRef[0] = 'K';
        ubSpeedRef[1] = 0;

        AHC_Capture_SetImageEXIF((UINT8*)&ulGPSoffset   , 4, IFD_IDX_IFD0,      EXIFIFD_GPSINFO , EXIF_TYPE_LONG, 1);
        AHC_Capture_SetImageEXIF((UINT8*)&ulVersion     , 4, IFD_IDX_GPSIFD,    GPS_VERSION     , EXIF_TYPE_BYTE, 4);

        if (GPSCtrl_GPS_IsValidValue())
        {
            ubNS[0]         = GPSCtrl_CheckRefForExif(0);
            ubWE[0]         = GPSCtrl_CheckRefForExif(1);
            ubAltitudeRef   = GPSCtrl_CheckRefForExif(2);
            ubSpeedRef[0]   = GPSCtrl_CheckRefForExif(3);

            GPSCtrl_GPSFormatTrans(pInfo->dwLat,&usDegree,&usMin,&usSec);
            ulGpsLatitude[0] = (MMP_ULONG)usDegree; ulGpsLatitude[2] = (MMP_ULONG)usMin; ulGpsLatitude[4] = (MMP_ULONG)(usSec*10000);
            ulGpsLatitude[1] = 1                  ; ulGpsLatitude[3] = 1               ; ulGpsLatitude[5] = 10000;

            GPSCtrl_GPSFormatTrans(pInfo->dwLon,&usDegree,&usMin,&usSec);
            ulGpsLongitude[0] = (MMP_ULONG)usDegree; ulGpsLongitude[2] = (MMP_ULONG)usMin; ulGpsLongitude[4] = (MMP_ULONG)(usSec*10000);
            ulGpsLongitude[1] = 1                  ; ulGpsLongitude[3] = 1               ; ulGpsLongitude[5] = 10000;

            ulSeeAltitude[0] = GPS_ABS(pInfo->dwElv);
            ulSeeAltitude[1] = 1;

            ulSpeed[0] = pInfo->dwSpeed;
            ulSpeed[1] = 1;

            ulGpsTimeStamp[0] = (MMP_ULONG)pInfo->sUTC.iHour; ulGpsTimeStamp[2] = (MMP_ULONG)pInfo->sUTC.iMin;ulGpsTimeStamp[4] = (MMP_ULONG)pInfo->sUTC.iSec;
            ulGpsTimeStamp[1] = 1;                            ulGpsTimeStamp[3] = 1;                          ulGpsTimeStamp[5] = 1;

            AHC_Capture_SetImageEXIF((UINT8*)&ubNS              , 2     , IFD_IDX_GPSIFD, GPS_LATITUDE_REF  , EXIF_TYPE_ASCII   , 2);
            AHC_Capture_SetImageEXIF((UINT8*)&(ulGpsLatitude)   , 24    , IFD_IDX_GPSIFD, GPS_LATITUDE      , EXIF_TYPE_RATIONAL, 3);
            AHC_Capture_SetImageEXIF((UINT8*)&ubWE              , 2     , IFD_IDX_GPSIFD, GPS_LONGITUDE_REF , EXIF_TYPE_ASCII   , 2);
            AHC_Capture_SetImageEXIF((UINT8*)&(ulGpsLongitude)  , 24    , IFD_IDX_GPSIFD, GPS_LONGITUDE     , EXIF_TYPE_RATIONAL, 3);
            AHC_Capture_SetImageEXIF((UINT8*)&ubAltitudeRef     , 1     , IFD_IDX_GPSIFD, GPS_ALTITUDE_REF  , EXIF_TYPE_BYTE    , 1);
            AHC_Capture_SetImageEXIF((UINT8*)&ulSeeAltitude     , 8     , IFD_IDX_GPSIFD, GPS_ALTITUDE      , EXIF_TYPE_RATIONAL, 1);
            AHC_Capture_SetImageEXIF((UINT8*)&(ulGpsTimeStamp)  , 24    , IFD_IDX_GPSIFD, GPS_TIME_STAMP    , EXIF_TYPE_RATIONAL, 3);
            AHC_Capture_SetImageEXIF((UINT8*)&ubSpeedRef        , 2     , IFD_IDX_GPSIFD, GPS_SPEED_REF     , EXIF_TYPE_ASCII   , 2);
            AHC_Capture_SetImageEXIF((UINT8*)&ulSpeed           , 8     , IFD_IDX_GPSIFD, GPS_SPEED         , EXIF_TYPE_RATIONAL, 1);
        }
    }
    else {
        return AHC_TRUE;
    }
    #endif

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_ConfigMenuEXIF
//  Description : Config EXIF Related to MENU settings
//------------------------------------------------------------------------------
AHC_BOOL AHC_Capture_ConfigMenuEXIF(void)
{
    MMP_USHORT  usWhiteBalance = 0x00;
    MMP_USHORT  usLightSource = 0x00;
    MMP_USHORT  usMetering = 0x00;
    UINT8       u8MeterMode = 0;
    UINT8       u8WB = 0;

    if ((AHC_Menu_SettingGetCB((char*)COMMON_KEY_METER, &u8MeterMode) == AHC_FALSE))
    {
        u8MeterMode = COMMON_METERING_DEFAULT;
    }

    switch(u8MeterMode)
    {
    #if (MENU_MANUAL_METERING_MULTI_EN)
        case COMMON_METERING_MULTI:         usMetering = 0x05;
        break;
    #endif
    #if (MENU_MANUAL_METERING_WEIGHTED_EN)
        case COMMON_METERING_WEIGHTED:      usMetering = 0x01;
        break;
    #endif
    #if (MENU_MANUAL_METERING_CENTER_SPOT_EN)
        case COMMON_METERING_CENTER_SPOT:   usMetering = 0x02;
        break;
    #endif
    default:
        break;
    }

    AHC_Capture_SetImageEXIF((UINT8*)&usMetering, 2 , IFD_IDX_EXIFIFD, EXIFIFD_METERINGMODE, EXIF_TYPE_SHORT, 1);

    if ((AHC_Menu_SettingGetCB((char*)COMMON_KEY_WB, &u8WB) == AHC_FALSE))
    {
        u8WB = COMMON_WB_DEFAULT;
    }

    switch(u8WB)
    {
    #if (MENU_MANUAL_WB_AUTO_EN)
        case COMMON_WB_AUTO:            usWhiteBalance = 0x00;
        break;
    #endif
    #if (MENU_MANUAL_WB_DAYLIGHT_EN)
        case COMMON_WB_DAYLIGHT:        usWhiteBalance = 0x01; usLightSource = 1;
            break;
    #endif
    #if (MENU_MANUAL_WB_CLOUDY_EN)
        case COMMON_WB_CLOUDY:          usWhiteBalance = 0x01; usLightSource = 10;
        break;
    #endif
    #if (MENU_MANUAL_WB_FLUORESCENT1_EN)
        case COMMON_WB_FLUORESCENT1:    usWhiteBalance = 0x01; usLightSource = 2;
        break;
    #endif
    #if (MENU_MANUAL_WB_FLUORESCENT2_EN)
        case COMMON_WB_FLUORESCENT2:    usWhiteBalance = 0x01; usLightSource = 2;
        break;
    #endif
    #if (MENU_MANUAL_WB_FLUORESCENT3_EN)
        case COMMON_WB_FLUORESCENT3:    usWhiteBalance = 0x01; usLightSource = 2;
        break;
    #endif
    #if (MENU_MANUAL_WB_INCANDESCENT_EN)
        case COMMON_WB_INCANDESCENT:    usWhiteBalance = 0x01; usLightSource = 21;
        break;
    #endif
    #if (MENU_MANUAL_WB_FLASH_EN)
        case COMMON_WB_FLASH:           usWhiteBalance = 0x01; usLightSource = 4;
        break;
    #endif
    #if (MENU_MANUAL_WB_ONEPUSH_EN)
        case COMMON_WB_ONEPUSH:         usWhiteBalance = 0x01; usLightSource = 0xFF;
    break;
    #endif
    #if (MENU_MANUAL_WB_ONE_PUSH_SET_EN)
        case COMMON_WB_ONE_PUSH_SET:    usWhiteBalance = 0x01; usLightSource = 0xFF;
        break;
    #endif
        default:
        break;
    }

    AHC_Capture_SetImageEXIF((UINT8*)&usWhiteBalance, 2, IFD_IDX_EXIFIFD, EXIFIFD_WHITEBLANCE, EXIF_TYPE_SHORT, 1);
    AHC_Capture_SetImageEXIF((UINT8*)&usLightSource,  2, IFD_IDX_EXIFIFD, EXIFIFD_LIGHTSOURCE, EXIF_TYPE_SHORT, 1);

    return AHC_TRUE;
}


#if 0
void _____Capture_Config_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_SetConfig
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Config capture mode

 This API controls several parameters which are relevant to still or video capture.
 Parameters:
 @param[in] byConfig Flags for configuration.
 @param[in] wOp Operand
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_Capture_SetConfig(AHC_CAPTURE_CONFIG byConfig, UINT16 u16Op)
{
    switch (byConfig) {
    case ACC_CUS_THUMB_W:
        if (u16Op % 16) {
            return AHC_FALSE;
        }
        m_u16ThumbCustomW = u16Op;
        break;
    case ACC_CUS_THUMB_H:
        if (u16Op % 8) {
            return AHC_FALSE;
        }
        m_u16ThumbCustomH = u16Op;
        break;
    case ACC_DATE_STAMP:
        m_u32TimeStampCfg = u16Op;
        break;
    default:
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_GetConfig
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get the capture config

 This API gets the capture configuration
 Parameters:
 @param[in] byConfig Flags for configuration.
 @param[in] wOp Operand
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_Capture_GetConfig(AHC_CAPTURE_CONFIG byConfig, UINT32 *pu32Op)
{
    switch (byConfig) {
    case ACC_CUS_THUMB_W:
        *pu32Op = m_u16ThumbCustomW;
        break;
    case ACC_CUS_THUMB_H:
        *pu32Op = m_u16ThumbCustomH;
        break;
    case ACC_DATE_STAMP:
        *pu32Op = m_u32TimeStampCfg;
        break;
    default:
        return AHC_FALSE;
    }
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_SetCompressRatio
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set compression ratio

 Set the compression ratio of still capture.
 Parameters:
 @param[in] wRatio 1~1000, means 1/1000~ 1000/1000
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_Capture_SetCompressRatio(UINT8 u8CamSel, UINT16 u16Ratio)
{
    m_u32ImageTgtSizeInKB[u8CamSel] = (m_u32StillImageW[u8CamSel] * m_u32StillImageH[u8CamSel] / 1024) * u16Ratio / 1000;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_GetImageTargetSizeInKB
//  Description :
//------------------------------------------------------------------------------
UINT32 AHC_Capture_GetImageTargetSizeInKB(UINT8 u8CamSel)
{
    return m_u32ImageTgtSizeInKB[u8CamSel];
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_SetCompressionQuality
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set compression quality

 Set the compression quality of still capture.
 Parameters:
 @param[in] Quality 10~100, means 10/100~ 100/100
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_Capture_SetCompressionQuality(UINT32 u32Quality)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;
    INT32   s32Temp = 0, i = 0;
    UINT8   QTable[2][64];

    if ((u32Quality < 10) || (u32Quality > 100)) {
        return AHC_FALSE;
    }

    if (u32Quality < 50)
        u32Quality = 5000 / u32Quality;
    else
        u32Quality = 200 - u32Quality*2;

    // LUMA
    for (i = 0; i < 64; i++) {
        s32Temp = ((long) AHC_JPEG_QTABLE_LUMA[i] * u32Quality + 50) / 100;

        /* limit the values to the valid range */
        if (s32Temp <= 0)
            s32Temp = 1;

         /* max quantizer needed for 12 bits */
        if (s32Temp > 32767)
            s32Temp = 32767;

        /* limit to baseline range if requested */
        if (s32Temp > 255)
            s32Temp = 255;

        QTable[0][i] = (UINT16) s32Temp;
    }

    // CHROMA
    for (i = 0; i < 64; i++) {
        s32Temp = ((long) AHC_JPEG_QTABLE_CHROMA[i] * u32Quality + 50) / 100;

        /* limit the values to the valid range */
        if (s32Temp <= 0)
            s32Temp = 1;

         /* max quantizer needed for 12 bits */
        if (s32Temp > 32767)
            s32Temp = 32767;

        /* limit to baseline range if requested */
        if (s32Temp > 255)
            s32Temp = 255;

        QTable[1][i] = (UINT16) s32Temp;
    }

    eRetErr = MMPS_DSC_SetCustomQTable(MMPS_DSC_CUSTOM_QTABLE_ALL, QTable[0], QTable[1], QTable[1]); // zigzag order

    return (eRetErr == MMP_ERR_NONE) ? AHC_TRUE : AHC_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_SetReviewTime
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_Capture_SetReviewTime(UINT16 u16ReviewTime, UINT16 u16WindowsTime)
{
    m_u16ReviewTime   = u16ReviewTime;
    m_u16WindowsTime  = u16WindowsTime;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_SetContiShotParam
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_Capture_SetContiShotParam(UINT16 u16MaxNum, UINT16 u16Interval)
{
    m_u16ContiShotMaxNum    = u16MaxNum;
    m_u16ContiShotInterval  = u16Interval;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_SetImageSize
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set capture resolution

 This API configures the captured resolution in selected mode.
 Parameters:
 @param[in] wSizeX Width.
 @param[in] wSizeY Height
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_Capture_SetImageSize(UINT8 ubCamSel, UINT16 u16SizeX, UINT16 u16SizeY)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    if ((u16SizeX == 0) || (u16SizeY == 0)) {
        AHC_DBG_ERR(1, "--E-- Wrong capture size\r\n");
        return AHC_FALSE;
    }

    m_u32StillImageW[ubCamSel] = u16SizeX;
    m_u32StillImageH[ubCamSel] = u16SizeY;

    eRetErr = MMPS_DSC_CustomedEncResol(ubCamSel, MMP_SCAL_FITMODE_OPTIMAL, u16SizeX, u16SizeY);

    return (eRetErr == MMP_ERR_NONE) ? AHC_TRUE : AHC_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_GetImageSize
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get capture resolution

 This API gets the captured resolution in selected mode.
 Parameters:
 @param[out] wSizeX Width.
 @param[out] wSizeY Height
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_Capture_GetImageSize(UINT8 u8CamSel, UINT32 *pu32SizeX, UINT32 *pu32SizeY)
{
    if (pu32SizeX)
        *pu32SizeX = m_u32StillImageW[u8CamSel];
    if (pu32SizeY)
        *pu32SizeY = m_u32StillImageH[u8CamSel];

    return AHC_TRUE;
}

#if 0
void _____Capture_PTZ_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_GetCurZoomStep
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_Capture_GetCurZoomStep(UINT16 *pu16ZoomStepNum)
{
    if (!MMPS_DSC_GetCurZoomStep(pu16ZoomStepNum))
        return AHC_FALSE;
    else
        return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_GetMaxZoomStep
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_Capture_GetMaxZoomStep(UINT16 *pu16ZoomStepNum)
{
     *pu16ZoomStepNum = gsDscPtzCfg.usMaxZoomSteps;

     return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_GetMaxZoomRatio
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_Capture_GetMaxZoomRatio(UINT16 *pu16MaxZoomRatio)
{
     *pu16MaxZoomRatio = gsDscPtzCfg.usMaxZoomRatio;

     return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_GetCurZoomStatus
//  Description :
//------------------------------------------------------------------------------
UINT8 AHC_Capture_GetCurZoomStatus(void)
{
    return (UINT8)MMPS_DSC_GetCurZoomStatus();
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_GetDigitalZoomRatio
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_Capture_GetDigitalZoomRatio(UINT32 *pu32ZoomRatio)
{
    UINT16 u16MaxZoomRatio, u16CurrentStep, u16MaxZoomStep;

    AHC_Capture_GetMaxZoomRatio(&u16MaxZoomRatio);

    AHC_Capture_GetCurZoomStep(&u16CurrentStep);
    AHC_Capture_GetMaxZoomStep(&u16MaxZoomStep);

    *pu32ZoomRatio = ((u16MaxZoomRatio > 1) && (u16MaxZoomStep > 0)) ? (100 + (u16CurrentStep * (u16MaxZoomRatio - 1) * 100) / u16MaxZoomStep) : 100;

    return AHC_TRUE;
}

#if 0
void _____Capture_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_StoreCardStartCB
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR AHC_Capture_StoreCardStartCB(void* pvArgu)
{
#if (AHC_CAPTURE_SYNC_STAMP_FILENAME)
    AHC_BOOL                ahc_ret = AHC_TRUE;
    MMPS_DSC_CAPTURE_INFO   *pCaptInfo = (MMPS_DSC_CAPTURE_INFO*) pvArgu;
    MMP_BYTE                bJpgFileName[MAX_FULL_FILENAME_SIZE] = {0};
    UINT16                  u16CaptureDirKey = 0;
    UINT8                   u8CaptureFileName[32] = {0};
    UINT8                   u8CreateNewDir = 0;

    if (pCaptInfo->ubCamSel == gsAhcPrmSensor) {

        AHC_UF_SetRearCamPathFlag(AHC_FALSE);

        ahc_ret = AHC_UF_GetName2(&pCaptInfo->stDateTime, (INT8*)bJpgFileName, (INT8*)u8CaptureFileName, AHC_Capture_GetCamStatusForDCF());
        if (ahc_ret != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahc_ret);}

        STRCAT(bJpgFileName, EXT_DOT);
        STRCAT(bJpgFileName, PHOTO_JPG_EXT);
        STRCAT((INT8*)u8CaptureFileName, EXT_DOT);
        STRCAT((INT8*)u8CaptureFileName, PHOTO_JPG_EXT);

        pCaptInfo->bFileName      = bJpgFileName;
        pCaptInfo->ulFileNameLen  = STRLEN(bJpgFileName);

        #if (FS_FORMAT_FREE_ENABLE)
        AHC_FF_SetFileNameSlot(pCaptInfo->bFileName);
        #endif

        AHC_DBG_MSG(1, "VR PrmJpeg [%s]\r\n", u8CaptureFileName);

        memcpy(&m_u8PrmCaptureFileName[0], &u8CaptureFileName[0], 32);

        ahc_ret = AHC_UF_PreAddFile(u16CaptureDirKey, (INT8*)m_u8PrmCaptureFileName);
    }
    else if (pCaptInfo->ubCamSel == gsAhcScdSensor) {

        AHC_UF_SetRearCamPathFlag(AHC_TRUE);

        ahc_ret = AHC_UF_GetName2(&pCaptInfo->stDateTime, (INT8*)bJpgFileName, (INT8*)u8CaptureFileName, AHC_Capture_GetCamStatusForDCF());
        if (ahc_ret != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahc_ret);}

        STRCAT(bJpgFileName, EXT_DOT);
        STRCAT(bJpgFileName, PHOTO_JPG_EXT);
        STRCAT((INT8*)u8CaptureFileName, EXT_DOT);
        STRCAT((INT8*)u8CaptureFileName, PHOTO_JPG_EXT);

        pCaptInfo->bFileName      = bJpgFileName;
        pCaptInfo->ulFileNameLen  = STRLEN(bJpgFileName);

        AHC_DBG_MSG(1, "VR ScdJpeg [%s]\r\n", u8CaptureFileName);

        memcpy(&m_u8ScdCaptureFileName[0], &u8CaptureFileName[0], 32);

        ahc_ret = AHC_UF_PreAddFile(u16CaptureDirKey, (INT8*)m_u8ScdCaptureFileName);
    }
#endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_StoreCardDoneCB
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR AHC_Capture_StoreCardDoneCB(void* pvArgu)
{
#if (AHC_CAPTURE_SYNC_STAMP_FILENAME)
    AHC_BOOL                ahc_ret = AHC_TRUE;
    MMPS_DSC_CAPTURE_INFO   *pCaptInfo = (MMPS_DSC_CAPTURE_INFO*) pvArgu;
    UINT16                  u16CaptureDirKey = 0;

    if (pCaptInfo->ubCamSel == gsAhcPrmSensor) {
        ahc_ret = AHC_UF_PostAddFile(u16CaptureDirKey, (INT8*)m_u8PrmCaptureFileName);
    }
    else if (pCaptInfo->ubCamSel == gsAhcScdSensor) {
        ahc_ret = AHC_UF_PostAddFile(u16CaptureDirKey, (INT8*)m_u8ScdCaptureFileName);
    }
#endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_SetCallBackFunc
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_Capture_SetCallBackFunc(MMP_UBYTE ubCBType)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    switch(ubCBType) {
    case AHC_CAPTURE_CALLBACK_CAPTURE_START:
        break;
    case AHC_CAPTURE_CALLBACK_STORECARD_START:
        eRetErr = MMPS_DSC_SetCallbackFunc(MMP_JPEG_ENC_CALLBACK_STORECARD_START, AHC_Capture_StoreCardStartCB);
        break;
    case AHC_CAPTURE_CALLBACK_STORECARD_END:
        eRetErr = MMPS_DSC_SetCallbackFunc(MMP_JPEG_ENC_CALLBACK_STORECARD_END, AHC_Capture_StoreCardDoneCB);
        break;
    case AHC_CAPTURE_CALLBACK_STORECARD_ERROR:
        break;
    default:
        break;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_SetDBGDataAfterJPEG
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_Capture_SetDBGDataAfterJPEG(UINT8 *u8Address, UINT32 *ulLength)
{
    UINT16 u16MajorVer = 0, u16MediumVer = 0, u16MinorVer = 0;

    //AHC_SetSensorDBGData(ubAddress, ulLength);

    MEMCPY((u8Address + *ulLength), "MENU", sizeof("MENU"));
    *ulLength += sizeof("MENU");
    MEMCPY((u8Address + *ulLength), MenuSettingConfig(), sizeof(MenuInfo));
    *ulLength += sizeof(MenuInfo);

    MEMCPY((u8Address + *ulLength), "FwVer", sizeof("FwVer"));
    *ulLength += sizeof("FwVer");

    AHC_GetFwVersion(&u16MajorVer, &u16MediumVer, &u16MinorVer, NULL, NULL, NULL);

    MEMCPY((u8Address + *ulLength), &u16MajorVer, sizeof(UINT16));
    *ulLength += sizeof(UINT16);
    MEMCPY((u8Address + *ulLength), &u16MediumVer, sizeof(UINT16));
    *ulLength += sizeof(UINT16);
    MEMCPY((u8Address + *ulLength), &u16MinorVer, sizeof(UINT16));
    *ulLength += sizeof(UINT16);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_IsScdCamConnect
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_Capture_IsScdCamConnect(void)
{
    AHC_BOOL bScdCamExist = AHC_FALSE;

    if (MMP_IsUSBCamExist()) {

        USB_DETECT_PHASE eUSBCurStates = 0;

        AHC_USBGetStates(&eUSBCurStates, AHC_USB_GET_PHASE_CURRENT);

        if ((eUSBCurStates == USB_DETECT_PHASE_REAR_CAM) &&
            (AHC_TRUE == AHC_HostUVC_IsDevEnabled())) {
            bScdCamExist = AHC_TRUE;
        }
    }
    else if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
        if (AHC_TRUE == AHC_SNR_GetAnaDecSnrCnntStatus()) {
            bScdCamExist = AHC_TRUE;
        }
    }
    else if (CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR)) {
        if (AHC_TRUE == AHC_SNR_GetYuvSnrCnntStatus()) {
            bScdCamExist = AHC_TRUE;
        }
    }
    else if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
        bScdCamExist = AHC_TRUE; //TODO: Add Check AHC_SNR_GetBayerSnrCnntStatus
    }

    return bScdCamExist;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_SetScdCamCaptSetting
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_Capture_SetScdCamCaptSetting(void)
{
    MMP_SNR_ANADEC_SRC_TYPE eAnaDecSrcType = MMP_SNR_ANADEC_SRC_NO_READY;
    MMP_SNR_YUV_SRC_TYPE    eYuvSrcType = MMP_SNR_YUV_SRC_DISCNT;
    UINT16                  u16CaptureW = 0, u16CaptureH = 0;

    if (CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR)) {

        MMPS_Sensor_GetYUVSnrSrcType(&eYuvSrcType);

        if (eYuvSrcType == MMP_SNR_YUV_SRC_HD) {
            u16CaptureW = 1280;
            u16CaptureH = 720;
        }
        else {
            u16CaptureW = 1920;
            u16CaptureH = 1080;
        }
    }
    else if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {

        MMPS_Sensor_GetAnaDecSrcType(&eAnaDecSrcType);

        if (eAnaDecSrcType == MMP_SNR_ANADEC_SRC_FHD) {
            u16CaptureW = 1920;
            u16CaptureH = 1080;
        }
        else if (eAnaDecSrcType == MMP_SNR_ANADEC_SRC_HD) {
            u16CaptureW = 1280;
            u16CaptureH = 720;
        }
        else if (eAnaDecSrcType == MMP_SNR_ANADEC_SRC_NTSC) {
            u16CaptureW = 720;
            u16CaptureH = 576;
        }
        else {
            u16CaptureW = 720;
            u16CaptureH = 480;
        }
    }
    else if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
        /* Same Resolution With PRM Cam */
        AHC_Capture_GetImageSize(gsAhcPrmSensor, &u16CaptureW, &u16CaptureH);
    }
    else {
        return AHC_FALSE;
    }

    if (MMP_GetANACamType() == ANA_CAM_2I1O) {
        u16CaptureW *= 2;
        if ( u16CaptureW > 2304 ) { // 2304 is max encode width
            u16CaptureW = 2304;
            u16CaptureH = 720;
        }
        UartSendTrace(FG_YELLOW("RearCam_2In1: Modified Capture resolution as %d x %d\r\n"), u16CaptureW, u16CaptureH);
    }

    AHC_Capture_SetImageSize(gsAhcScdSensor, u16CaptureW, u16CaptureH);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_SetPreviewMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_Capture_SetPreviewMode(AHC_BOOL bRawPreview, AHC_BOOL bCaptureReturn)
{
    AHC_DISPLAY_OUTPUTPANEL eOutputDevice;
    AHC_BOOL                bSnrFlipEn      = AHC_FALSE;
    UINT16                  u16ZoomIndex    = 0;
    MMP_USHORT              usDscDispMode   = DSC_NORMAL_PREVIEW_MODE;
    UINT32                  u32FlickerMode  = COMMON_FLICKER_50HZ;
    UINT8                   ubEv            = COMMON_EVVALUE_00;
    MMP_UBYTE               ubPrmHdrType    = 0;
    MMP_UBYTE               ubScdHdrType    = 0;
    MMP_ERR                 eRetErr         = MMP_ERR_NONE;

    if (bCaptureReturn == AHC_FALSE)
    {
        #if (AHC_ENABLE_STILL_STICKER == 0)
        AHC_Capture_SetConfig(ACC_DATE_STAMP, AHC_ACC_TIMESTAMP_DISABLE);
        #endif

        /* Stop Preview First */
        #if (UVC_HOST_VIDEO_ENABLE)
        if (MMP_IsUSBCamExist()) {
            AHC_HostUVC_PreviewStop(AHC_HUVC_UI_MODE_DSC);
            AHC_HostUVC_ResetFBMemory();
        }
        #endif

        if (MMP_IsScdCamExist()) {

            if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
                MMPS_Sensor_EnableAnaDecSrcTypeDetect(MMP_FALSE);
                eRetErr |= MMPS_DSC_EnablePreviewDisplay(gsAhcScdSensor, MMP_FALSE, MMP_FALSE);
            }
            else if (CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR)) {
                eRetErr |= MMPS_DSC_EnablePreviewDisplay(gsAhcScdSensor, MMP_FALSE, MMP_FALSE);
            }
            else if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
                eRetErr |= MMPS_DSC_EnablePreviewDisplay(gsAhcScdSensor, MMP_FALSE, MMP_FALSE);
            }
        }

        /* Initial ISP and Channel Setting */
        if (m_bAhcCaptureInitISP == AHC_FALSE) {

            eRetErr = MMPF_ISP_GlobalInit();

            ubPrmHdrType = (MMP_UBYTE)MMP_GetDscHDRType(CAM_TYPE_PRM);
            ubScdHdrType = (MMP_UBYTE)MMP_GetVidHDRType(CAM_TYPE_SCD);

            if (MMP_IsPrmCamExist()) { // Only primary sensor can support HDR function.
                if (CAM_CHECK_PRM(PRM_CAM_BAYER_SENSOR)) {
                    eRetErr = MMPF_ISP_AllocatePrmSensorChannel(ubPrmHdrType);
                    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
                }
                else if ((CAM_CHECK_PRM(PRM_CAM_ANA_DECODER)) ||
                         (CAM_CHECK_PRM(PRM_CAM_YUV_SENSOR))) {
                    eRetErr = MMPF_ISP_AllocatePrmRAWStoreSensorChannel();
                    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
                }
            }
            if (MMP_IsScdCamExist()) {
                if ((CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) ||
                    (CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR)) ||
                    (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))) {
                    eRetErr = MMPF_ISP_AllocateScdRAWStoreSensorChannel(ubScdHdrType);
                    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
                }
            }

            m_bAhcCaptureInitISP = AHC_TRUE;
        }

        /* Check if Prm cam and SCD cam I2C Addr are equal or not? */
        if (MMP_IsPrmCamExist() && MMP_IsScdCamExist()) {
            MMP_UBYTE ubPrmI2CAddr, ubScdI2CAddr;
            eRetErr = MMPF_Sensor_GetSensorI2CAddr(gsAhcPrmSensor, &ubPrmI2CAddr);
            if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
            eRetErr = MMPF_Sensor_GetSensorI2CAddr(gsAhcScdSensor, &ubScdI2CAddr);
            if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
            if (ubPrmI2CAddr == ubScdI2CAddr) {
                AHC_DBG_ERR(1, FG_RED("[Warning!]Prm Sensor I2C Addr = Scd Sensor I2C Addr 0x%x\r\n"), ubPrmI2CAddr);
            }
        }

        /* Set Display Device */
        AHC_GetDisplayOutputDev(&eOutputDevice);
        eRetErr = MMPS_Display_SetOutputPanel(MMP_DISPLAY_PRM_CTL, eOutputDevice);

        switch(eOutputDevice){
        case MMP_DISPLAY_SEL_MAIN_LCD:
        case MMP_DISPLAY_SEL_SUB_LCD:
            usDscDispMode = DSC_NORMAL_PREVIEW_MODE;
            break;
        case MMP_DISPLAY_SEL_NTSC_TV:
            usDscDispMode = DSC_TV_NTSC_PREVIEW_MODE;
            break;
        case MMP_DISPLAY_SEL_PAL_TV:
            usDscDispMode = DSC_TV_PAL_PREVIEW_MODE;
            break;
        case MMP_DISPLAY_SEL_HDMI:
            usDscDispMode = DSC_HDMI_PREVIEW_MODE;
            break;
        case MMP_DISPLAY_SEL_CCIR:
            usDscDispMode = DSC_CCIR_PREVIEW_MODE;
            break;
        case MMP_DISPLAY_SEL_NONE:
        default:
            usDscDispMode = DSC_NORMAL_PREVIEW_MODE;
            break;
        }

        /* Initial DSC Preview Parameter */
        if (bRawPreview) {
            if (MMP_IsPrmCamExist())
                eRetErr = MMPS_DSC_SetPreviewPath(gsAhcPrmSensor, MMP_DSC_RAW_PREVIEW);
            if (MMP_IsScdCamExist())
                eRetErr = MMPS_DSC_SetPreviewPath(gsAhcScdSensor, MMP_DSC_RAW_PREVIEW);
        }
        else {
            if (MMP_IsPrmCamExist())
                eRetErr = MMPS_DSC_SetPreviewPath(gsAhcPrmSensor, MMP_DSC_STD_PREVIEW);
            if (MMP_IsScdCamExist())
                eRetErr = MMPS_DSC_SetPreviewPath(gsAhcScdSensor, MMP_DSC_STD_PREVIEW);
        }

        /* Open Prm Script and Port */
        eRetErr = MMPS_DSC_SetPreviewMode(usDscDispMode);

        /* Initial Sensor */
        if (MMP_IsScdCamExist()) {
            MMP_ULONG ulIqCfgIdx = 0;

            eRetErr = MMPS_Sensor_Initialize(gsAhcScdSensor, 0, MMP_SNR_DSC_PRW_MODE, 0/*Second sensor does not support HDR*/, ulIqCfgIdx);
            if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

            if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
                eRetErr = MMPS_Sensor_RegisterCallback(MMP_SNR_EVENT_ANADEC_SRC_TYPE, (void*)CaptureAnaDecSnrSrcTypeHandler);
                eRetErr = MMPS_Sensor_EnableAnaDecSrcTypeDetectTimer(gsAhcScdSensor, NULL, SNR_R_CHECK_SIG_TYPE_PERIODIC, MMP_TRUE);
                if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }
            }
        }

        if (MMP_IsPrmCamExist()) {
            MMP_ULONG ulIqCfgIdx = 0;

            ulIqCfgIdx = (ubPrmHdrType == 0) ? 0 : 1; // For iqcfg file
            eRetErr = MMPS_Sensor_SetPreviewMode(gsAhcPrmSensor, AHC_SNR_GetPresetPrmSnrMode());
            eRetErr = MMPS_Sensor_Initialize(gsAhcPrmSensor, AHC_SNR_GetPresetPrmSnrMode(), MMP_SNR_DSC_PRW_MODE, ubPrmHdrType, ulIqCfgIdx);
            if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }
        }

        /* Set Sensor Flip Direction */
        bSnrFlipEn = AHC_CheckSNRFlipEn(CTRL_BY_ALL) && AHC_SNR_GetSnrDirStatus();
        AHC_SetKitDirection(AHC_LCD_NOFLIP, AHC_TRUE, AHC_SNR_GetSnrDirStatus(), bSnrFlipEn);

        /* Set Flicker Mode */
        if (AHC_Menu_SettingGetCB((char *)COMMON_KEY_FLICKER, &u32FlickerMode) == AHC_TRUE) {
            if (COMMON_FLICKER_60HZ == u32FlickerMode) {
                AHC_SNR_SetLightFreq(gsAhcPrmSensor, AHC_SENSOR_VIDEO_DEBAND_60HZ);
                if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                    AHC_SNR_SetLightFreq(gsAhcScdSensor, AHC_SENSOR_VIDEO_DEBAND_60HZ);
            }
            else {
                AHC_SNR_SetLightFreq(gsAhcPrmSensor, AHC_SENSOR_VIDEO_DEBAND_50HZ);
                if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                    AHC_SNR_SetLightFreq(gsAhcScdSensor, AHC_SENSOR_VIDEO_DEBAND_50HZ);
            }
        }
        else {
            AHC_SNR_SetLightFreq(gsAhcPrmSensor, AHC_SENSOR_VIDEO_DEBAND_60HZ);
            if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                AHC_SNR_SetLightFreq(gsAhcScdSensor, AHC_SENSOR_VIDEO_DEBAND_60HZ);
        }

        /* Set EV value */
        if (AHC_Menu_SettingGetCB((char *)COMMON_KEY_EV, &ubEv) == AHC_TRUE) {
            AHC_SetAeEvBiasMode(gsAhcPrmSensor, Menu_EV_To_AE_EV_BIAS(ubEv));
            if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                AHC_SetAeEvBiasMode(gsAhcScdSensor, Menu_EV_To_AE_EV_BIAS(ubEv));
        }

        /* Check Prm Analog Decoder / YUV sensor source type */
        if (MMP_IsPrmCamExist()) {
            if (CAM_CHECK_PRM(PRM_CAM_ANA_DECODER)) {
                AHC_SNR_CheckAnaDecSrcType(MMPS_PREVIEW_UI_MODE_DSC, gsAhcPrmSensor);
            }
            else if (CAM_CHECK_PRM(PRM_CAM_YUV_SENSOR)) {
                AHC_SNR_CheckYUVSnrSrcType(MMPS_PREVIEW_UI_MODE_DSC, gsAhcPrmSensor);
            }
        }

        /* Initial Zoom Parameter */
        //MMPS_DSC_GetCurZoomStep(&u16ZoomIndex);
        //MMPS_DSC_SetPreviewZoom(MMP_PTZ_ZOOMIN, u16ZoomIndex);

        if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
            MMPF_Sensor_SetDualBayerSensor(MMP_TRUE);
        }
        else {
            MMPF_Sensor_SetDualBayerSensor(MMP_FALSE);
        }

        /* Start Prm Preview Flow (Open VIF) */
        if (MMP_IsPrmCamExist()) {
            eRetErr = MMPS_DSC_EnablePreviewDisplay(gsAhcPrmSensor, MMP_TRUE, MMP_FALSE);
        }

        /* Check Scd Preview / Capture Pipe Attribute */
        if (MMP_IsScdCamExist()) {
            if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
                AHC_SNR_CheckAnaDecSrcType(MMPS_PREVIEW_UI_MODE_DSC, gsAhcScdSensor);

                if (AHC_TRUE == AHC_SNR_GetAnaDecSnrCnntStatus()) {
                    AHC_Capture_SetScdCamCaptSetting();

                    MMPS_DSC_AdjustScdCapturePipe(gsAhcScdSensor);
                    MMPS_DSC_AdjustScdPreviewPipe(gsAhcScdSensor);
                }
            }
            else if (CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR)) {
                AHC_SNR_CheckYUVSnrSrcType(MMPS_PREVIEW_UI_MODE_DSC, gsAhcScdSensor);

                if (AHC_TRUE == AHC_SNR_GetYuvSnrCnntStatus()) {
                    AHC_Capture_SetScdCamCaptSetting();

                    MMPS_DSC_AdjustScdCapturePipe(gsAhcScdSensor);
                    MMPS_DSC_AdjustScdPreviewPipe(gsAhcScdSensor);
                }
            }
            else if(CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)){
                AHC_Capture_SetScdCamCaptSetting();

                eRetErr = MMPS_DSC_AdjustScdCapturePipe(gsAhcScdSensor);
                eRetErr = MMPS_DSC_AdjustScdPreviewPipe(gsAhcScdSensor);
            }
        }

        /* Open Scd Script and Port */
        if (MMP_IsScdCamExist()) {
            if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
                if (AHC_FALSE == AHC_SNR_GetAnaDecSnrCnntStatus())
                    MMPS_Display_EnableScdAnaDecSnrPreview(MMPS_PREVIEW_UI_MODE_DSC, MMP_FALSE);
                else
                    MMPS_Display_EnableScdAnaDecSnrPreview(MMPS_PREVIEW_UI_MODE_DSC, MMP_TRUE);
            }
            else if (CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR)) {
                if (AHC_FALSE == AHC_SNR_GetYuvSnrCnntStatus())
                    MMPS_Display_EnableScdAnaDecSnrPreview(MMPS_PREVIEW_UI_MODE_DSC, MMP_FALSE);
                else
                    MMPS_Display_EnableScdAnaDecSnrPreview(MMPS_PREVIEW_UI_MODE_DSC, MMP_TRUE);
            }
            else if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
                MMPS_Display_EnableScdBayerSnrPreview(MMPS_PREVIEW_UI_MODE_DSC, MMP_TRUE);
            }
        }

        /* Start Scd Preview Flow (Open VIF) */
        if (MMP_IsScdCamExist()) {
            if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
                if (AHC_TRUE == AHC_SNR_GetAnaDecSnrCnntStatus()) {
                    eRetErr = MMPS_DSC_EnablePreviewDisplay(gsAhcScdSensor, MMP_TRUE, MMP_FALSE);
                }
            }
            else if (CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR)) {
                if (AHC_TRUE == AHC_SNR_GetYuvSnrCnntStatus()) {
                    eRetErr = MMPS_DSC_EnablePreviewDisplay(gsAhcScdSensor, MMP_TRUE, MMP_FALSE);
                }
            }
            else if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
                eRetErr = MMPS_DSC_EnablePreviewDisplay(gsAhcScdSensor, MMP_TRUE, MMP_FALSE);
            }
        }

        #if (UVC_HOST_VIDEO_ENABLE)
        if (MMP_IsUSBCamExist()) {
            AHC_HostUVC_PreviewStart(AHC_HUVC_UI_MODE_DSC, u32FlickerMode);
        }
        #endif

        #if (AHC_ENABLE_VIDEO_STICKER)
        UpdateVideoCurrentTimeStamp(AHC_TRUE);
        #endif
    }
    else {
        // TBD
        //eRetErr = MMPS_DSC_RestorePreview(gsAhcPrmSensor, m_u16WindowsTime);
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_StopPreview
//  Description : Stop capture preview
//------------------------------------------------------------------------------
AHC_BOOL AHC_Capture_StopPreview(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    /* Disable PRM Sticker Before PRM Cam Preview Stop */
    if (MMP_TRUE == MMPS_3GPRECD_IsStickerEnable(MMP_STICKER_ID_0)) {
        MMPS_3GPRECD_EnableSticker(MMP_STICKER_ID_0, MMP_FALSE);
    }

    #if (UVC_HOST_VIDEO_ENABLE)
    if (MMP_IsUSBCamExist()) {

        USB_DETECT_PHASE eUSBCurStates = 0;

        AHC_USBGetStates(&eUSBCurStates, AHC_USB_GET_PHASE_CURRENT);

        if (eUSBCurStates == USB_DETECT_PHASE_REAR_CAM) {
            AHC_HostUVC_PreviewStop(AHC_HUVC_UI_MODE_DSC);
        }

        AHC_HostUVC_ResetFBMemory();
    }
    #endif

    if (MMP_IsPrmCamExist()) {
        MMPS_DSC_EnablePreviewDisplay(gsAhcPrmSensor, MMP_FALSE, MMP_FALSE);
    }

    if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {

        //ubPortScriptIdx_PrevwSrc_Raw1_Fcam      = PORT_SCRIPT_VR_PREV_PRM_ANADEC_SRC_RAW1;              //RAWS_CH1 open port0=DIP_S0
        //ubCompScriptIdx_Scr_2In2_Raw1           = COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_SRC_2IN2_RAW1;      //RAWS_CH1->DIP_S0+DIP_S14+DIP_S8     (prev+Frec+wifi)
        //close these components in MMPS_Display_EnableScdAnaDecSnrPreview()
        if(MMP_GetANACamType() != ANA_CAM_2I2O){
            MMPS_Display_EnableScdAnaDecSnrPreviewWindow(MMPS_PREVIEW_UI_MODE_DSC, MMP_FALSE);
        }

        MMPS_Sensor_EnableAnaDecSrcTypeDetectTimer(gsAhcScdSensor, NULL, SNR_R_CHECK_SIG_TYPE_PERIODIC, MMP_FALSE);
        eRetErr = MMPS_DSC_EnablePreviewDisplay(gsAhcScdSensor, MMP_FALSE, MMP_FALSE);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }
    }
    else if (CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR)) {
        eRetErr = MMPS_DSC_EnablePreviewDisplay(gsAhcScdSensor, MMP_FALSE, MMP_FALSE);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }
    }
    else if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
        eRetErr = MMPS_DSC_EnablePreviewDisplay(gsAhcScdSensor, MMP_FALSE, MMP_FALSE);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }
    }

    /* Power Down Sensor/ISP */
    if (MMP_IsPrmCamExist()) {
        MMPS_Sensor_PowerDown(gsAhcPrmSensor);
    }
    if (MMP_IsScdCamExist()) {
        MMPS_Sensor_PowerDown(gsAhcScdSensor);
    }

    if (MMP_GetANACamType() != ANA_CAM_2I1O && MMP_GetANACamType() != ANA_CAM_2I2O){
        if (m_bAhcCaptureInitISP) {
            MMPF_ISP_GlobalUnInit();
            m_bAhcCaptureInitISP = AHC_FALSE;
        }
        //Need to review
        UartSendTrace(BG_BLUE("TODO:%s,%d\n"),__FUNCTION__, __LINE__);
    }

    /* Close Script */
    if (MMP_IsScdCamExist()) {
        if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
            MMPS_Display_EnableScdBayerSnrPreview(MMPS_PREVIEW_UI_MODE_DSC, MMP_FALSE);
        }
        else {
            MMPS_Display_EnableScdAnaDecSnrPreview(MMPS_PREVIEW_UI_MODE_DSC, MMP_FALSE);
        }
    }

    //workaround, do GlobalUnInit after cameraPreviewSetChannel((u32)RAWS_COMP_IDX2,MMP_FALSE);
    if (MMP_GetANACamType() == ANA_CAM_2I1O || MMP_GetANACamType() == ANA_CAM_2I2O){
        if (m_bAhcCaptureInitISP) {
            MMPF_ISP_GlobalUnInit();
            m_bAhcCaptureInitISP = AHC_FALSE;
        }
    }

    if (MMP_IsPrmCamExist()) {
        MMPS_DSC_SetPreviewMode((MMP_USHORT)-1);
    }

    /* Disable SCD Sticker After SCD Cam Preview Stop */
    if (MMP_TRUE == MMPS_3GPRECD_IsStickerEnable(MMP_STICKER_ID_1)) {
        MMPS_3GPRECD_EnableSticker(MMP_STICKER_ID_1, MMP_FALSE);
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_StartTakeJpeg
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_Capture_StartTakeJpeg(UINT8 u8Mode)
{
    MMP_ERR                 sRet = MMP_ERR_NONE;
    MMP_BYTE                bPrmJpgFileName[MAX_FULL_FILENAME_SIZE];
    MMP_BYTE                bScdJpgFileName[MAX_FULL_FILENAME_SIZE];
    MMP_BYTE                bDirName[16];
    UINT16                  u16CaptureDirKey = 0;
    UINT8                   u8PrmCaptureFileName[32];
    UINT8                   u8ScdCaptureFileName[32];
    UINT8                   bCreateNewDir = 0;
    MMP_BOOL                bPrmCamExist = MMP_FALSE;
    MMP_BOOL                bScdCamExist = MMP_FALSE;
    MMP_BOOL                bPrmWriteDone = MMP_FALSE;
    MMP_BOOL                bScdWriteDone = MMP_FALSE;
    MMPS_DSC_CAPTURE_INFO   stDscCaptInfo[DSC_CAPTURE_MAX_CAM_NUM];
    UINT32                  u32CaptureW = 0, u32CaptureH = 0;
    UINT32                  u32ThumbW = 0, u32ThumbH = 0;
    UINT32                  i = 0;
    AHC_EXIF_CONFIG         Exif;
    UINT32                  u32JpgQuality = 0;
    AHC_BOOL                ahc_ret = AHC_TRUE;
    MMP_ULONG               ulContiShotTimeOut = 800;
    #if (ENABLE_DEBUG_AFTER_JPG)
    UINT32                  u32DbgBufSize = 0;
    #endif
    #if (JPEG_INTO_AVI_WHILE_TURN_ON || PIR_JPEG_INTO_AVI_WHILE_TURN_ON)
    MMP_ULONG               ulTestFileID;
    MMP_ULONG               ulTestAviFileSize;
    MMP_ULONG               ulTestAviFrameNum;
    #endif

    for (i = 0; i < DSC_CAPTURE_MAX_CAM_NUM; i++) {
        stDscCaptInfo[i].bCaptureEn = MMP_FALSE;
    }

    /* Check Sensor Exist */
    if (MMP_IsPrmCamExist()) {
        bPrmCamExist = MMP_TRUE;
    }

    if (MMP_IsScdCamExist() || MMP_IsUSBCamExist()) {
        bScdCamExist = AHC_Capture_IsScdCamConnect();
    }

    /* Get Capture FileName */
    if (u8Mode != AHC_MODE_CONTINUOUS_CAPTURE)
    {
        #if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
        MEMSET(bDirName, 0, sizeof(bDirName));

        ahc_ret = AHC_UF_GetName(&u16CaptureDirKey, (INT8*)bDirName, (INT8*)u8PrmCaptureFileName, &bCreateNewDir);

        if (ahc_ret == AHC_TRUE) {

            STRCPY(bJpgFileName, (INT8*)AHC_UF_GetRootDirName());
            STRCAT(bJpgFileName, "\\");
            STRCAT(bJpgFileName, bDirName);

            if (bCreateNewDir) {
                MMPS_FS_DirCreate((INT8*)bJpgFileName, STRLEN(bJpgFileName));
                AHC_UF_AddDir(bDirName);
            }

            STRCAT(bJpgFileName, "\\");
            STRCAT(bJpgFileName, (INT8*)u8PrmCaptureFileName);
        }
        #elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
        {
            #if (AHC_CAPTURE_SYNC_STAMP_FILENAME == 0)
            AHC_RTC_TIME RtcTime;

            AHC_RTC_GetTime(&RtcTime);

            if (bPrmCamExist) {

                MEMSET(bPrmJpgFileName,      0, sizeof(bPrmJpgFileName));
                MEMSET(u8PrmCaptureFileName, 0, sizeof(u8PrmCaptureFileName));

                AHC_UF_SetRearCamPathFlag(AHC_FALSE);

                ahc_ret = AHC_UF_GetName2(&RtcTime, (INT8*)bPrmJpgFileName, (INT8*)u8PrmCaptureFileName, AHC_Capture_GetCamStatusForDCF());
                if (ahc_ret != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahc_ret); }

                STRCAT(bPrmJpgFileName, EXT_DOT);
                STRCAT((INT8*)u8PrmCaptureFileName, EXT_DOT);

                #if (JPEG_INTO_AVI_WHILE_TURN_ON)

                if (u8Mode == AHC_MODE_LONGTIME_FIRST_CAPTURE) {
                    STRCAT(bJpgFileName, MOVIE_AVI_EXT);
                    STRCAT((INT8*)u8PrmCaptureFileName, MOVIE_AVI_EXT);
                }
                else if (u8Mode == AHC_MODE_LONGTIME_NEXT_CAPTURE) {
                    STRCPY(bJpgFileName, AHC_InfoLog()->DCFCurStillFileName); // TBD
                }
                else {
                    STRCAT(bJpgFileName, PHOTO_JPG_EXT);
                    STRCAT((INT8*)u8PrmCaptureFileName, PHOTO_JPG_EXT);
                }

                if (u8Mode != AHC_MODE_LONGTIME_NEXT_CAPTURE) {
                    STRCPY(AHC_InfoLog()->DCFCurStillFileName, bJpgFileName);
                }

                #else // JPEG_INTO_AVI_WHILE_TURN_ON

                STRCAT(bPrmJpgFileName, PHOTO_JPG_EXT);
                STRCAT((INT8*)u8PrmCaptureFileName, PHOTO_JPG_EXT);

                #endif

                stDscCaptInfo[0].bFileName      = bPrmJpgFileName;
                stDscCaptInfo[0].ulFileNameLen  = STRLEN(bPrmJpgFileName);
            }

            if (bScdCamExist) {

                MEMSET(bScdJpgFileName,      0, sizeof(bScdJpgFileName));
                MEMSET(u8ScdCaptureFileName, 0, sizeof(u8PrmCaptureFileName));

                AHC_UF_SetRearCamPathFlag(AHC_TRUE);

                ahc_ret = AHC_UF_GetName2(&RtcTime, (INT8*)bScdJpgFileName, (INT8*)u8ScdCaptureFileName, AHC_Capture_GetCamStatusForDCF());
                if (ahc_ret != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahc_ret);}

                STRCAT(bScdJpgFileName, EXT_DOT);
                STRCAT((INT8*)u8ScdCaptureFileName, EXT_DOT);

                #if (JPEG_INTO_AVI_WHILE_TURN_ON)

                if (u8Mode == AHC_MODE_LONGTIME_FIRST_CAPTURE) {
                    STRCAT(bScdJpgFileName, MOVIE_AVI_EXT);
                    STRCAT((INT8*)u8ScdCaptureFileName, MOVIE_AVI_EXT);
                }
                else if (u8Mode == AHC_MODE_LONGTIME_NEXT_CAPTURE) {
                    STRCPY(bScdJpgFileName, AHC_InfoLog()->DCFCurStillFileName);
                }
                else {
                    STRCAT(bScdJpgFileName, PHOTO_JPG_EXT);
                    STRCAT((INT8*)u8ScdCaptureFileName, PHOTO_JPG_EXT);
                }

                if (u8Mode != AHC_MODE_LONGTIME_NEXT_CAPTURE) {
                    STRCPY(AHC_InfoLog()->DCFCurStillFileName, bScdJpgFileName);
                }

                #else // JPEG_INTO_AVI_WHILE_TURN_ON

                STRCAT(bScdJpgFileName, PHOTO_JPG_EXT);
                STRCAT((INT8*)u8ScdCaptureFileName, PHOTO_JPG_EXT);

                #endif

                stDscCaptInfo[1].bFileName      = bScdJpgFileName;
                stDscCaptInfo[1].ulFileNameLen  = STRLEN(bScdJpgFileName);
            }
            #endif
        }
        #endif
    }
    else {
        ahc_ret = AHC_TRUE;
    }

    if (ahc_ret == AHC_TRUE)
    {
        #if (SUPPORT_HDMI_OUT_FOCUS) // TBD
        /* Set TimeStamp */
        if (AHC_CheckHdmiOutFocus()) {
            MenuSettingConfig()->uiDateTimeFormat = DATETIME_SETUP_NONE;
            MenuItemDateTimeFormatToAhcTimeStampSetting();
        }
        #endif

        /* Get Preset Capture Parameter */
        AHC_Capture_GetConfig(ACC_CUS_THUMB_W, &u32ThumbW);
        AHC_Capture_GetConfig(ACC_CUS_THUMB_H, &u32ThumbH);

        AHC_Menu_SettingGetCB(COMMON_KEY_STILL_QUALITY, &u32JpgQuality);

        /* Allocate buffer */
        MMPS_DSC_AllocFileNameBuf();
        MMPS_DSC_AllocExifEncBuf();

        /* Update EXIF Node */
        for (i = 0; ; i++) {
            if (AHC_TRUE == AHC_Capture_GetImageEXIF(i, &Exif)) {
                MMPS_DSC_UpdateExifNode(EXIF_NODE_ID_PRIMARY,
                                        Exif.IfdID, Exif.TagID,
                                        Exif.TagType, Exif.TagDataSize,
                                        (MMP_UBYTE*)Exif.Data, Exif.DataSize, MMP_FALSE);
            }
            else {
                break;
            }
        }

        /* Take JPEG */
        if (u8Mode == AHC_MODE_STILL_CAPTURE ||
            u8Mode == AHC_MODE_CONTINUOUS_CAPTURE) {

            #if (DSC_SUPPORT_BASELINE_MP_FILE)
            if (u8Mode == AHC_MODE_STILL_CAPTURE)
                MMPS_DSC_EnableMultiPicFormat(MMP_TRUE, MMP_TRUE);
            else
                MMPS_DSC_EnableMultiPicFormat(MMP_FALSE, MMP_FALSE);
            #endif

            #if (AHC_CAPTURE_SYNC_STAMP_FILENAME)
            AHC_Capture_SetCallBackFunc(AHC_CAPTURE_CALLBACK_STORECARD_START);
            AHC_Capture_SetCallBackFunc(AHC_CAPTURE_CALLBACK_STORECARD_END);
            #endif

            if (bPrmCamExist) {

                AHC_Capture_GetImageSize(gsAhcPrmSensor, &u32CaptureW, &u32CaptureH);

                stDscCaptInfo[0].usPrimaryW     = u32CaptureW;
                stDscCaptInfo[0].usPrimaryH     = u32CaptureH;
                stDscCaptInfo[0].usThumbWidth   = u32ThumbW;
                stDscCaptInfo[0].usThumbHeight  = u32ThumbH;

                stDscCaptInfo[0].stQualityCtl.bTargetCtl      = MMP_TRUE;
                stDscCaptInfo[0].stQualityCtl.bLimitCtl       = MMP_FALSE;
                stDscCaptInfo[0].stQualityCtl.ulTargetSize    = AHC_Capture_GetImageTargetSizeInKB(gsAhcPrmSensor);
                stDscCaptInfo[0].stQualityCtl.ulLimitSize     = 0;
                stDscCaptInfo[0].stQualityCtl.usMaxTrialCnt   = 1;
                stDscCaptInfo[0].stQualityCtl.ubQualitySel    = u32JpgQuality;

                stDscCaptInfo[0].bCaptureEn     = MMP_TRUE;
                stDscCaptInfo[0].bExifEn        = MMP_TRUE;
            #if (DSC_ENC_THUMBNAIL_OK)
                stDscCaptInfo[0].bThumbnailEn   = (u8Mode == AHC_MODE_STILL_CAPTURE) ? (MMP_TRUE) : (MMP_FALSE);
            #else
                stDscCaptInfo[0].bThumbnailEn   = MMP_FALSE;
            #endif
                stDscCaptInfo[0].bFirstShot     = MMP_TRUE;
                stDscCaptInfo[0].ubShotMode     = (u8Mode == AHC_MODE_STILL_CAPTURE) ? (JPE_COMP_SINGLE_SHOT) : (JPE_COMP_CONTINUOUS_SHOT);
                stDscCaptInfo[0].usMaxShotNum   = (u8Mode == AHC_MODE_STILL_CAPTURE) ? (1) : (m_u16ContiShotMaxNum);
                stDscCaptInfo[0].ubUiMode       = JPE_COMP_UI_MODE_DSC;
                stDscCaptInfo[0].ubCamSel       = gsAhcPrmSensor;
                stDscCaptInfo[0].ubRawFmt       = JPE_COMP_FMT_NV12;
                stDscCaptInfo[0].usReviewTime   = m_u16ReviewTime;
                stDscCaptInfo[0].usWindowsTime  = m_u16WindowsTime;

                sRet = MMPS_DSC_CaptureJPEG(JPE_COMP_PRM_PRIMARY, &stDscCaptInfo[0]);
                if (sRet != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(0, sRet); goto CAPTURE_FAIL;}

            #if (ENABLE_DEBUG_AFTER_JPG)
                AHC_Capture_SetDBGDataAfterJPEG(m_ubDebugMessageBuffer, &u32DbgBufSize);

                stDscCaptInfo[0].ulExtraBufAddr  = (UINT32)m_ubDebugMessageBuffer;
                stDscCaptInfo[0].ulExtraBufSize  = u32DbgBufSize;
            #else
                stDscCaptInfo[0].ulExtraBufAddr  = 0;
                stDscCaptInfo[0].ulExtraBufSize  = 0;
            #endif

                if (u8Mode == AHC_MODE_STILL_CAPTURE) {

                    AHC_DBG_MSG(1, "PRM [%s] [%d]Bytes\r\n", stDscCaptInfo[0].bFileName, stDscCaptInfo[0].ulJpegFileSize);

                    sRet = MMPS_DSC_JpegDram2Card(&stDscCaptInfo[0]);
                    if (sRet != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, sRet); goto CAPTURE_FAIL;}

                    #if (AHC_CAPTURE_SYNC_STAMP_FILENAME == 0)
                    AHC_UF_PreAddFile(u16CaptureDirKey, (INT8*)u8PrmCaptureFileName);
                    AHC_UF_PostAddFile(u16CaptureDirKey, (INT8*)u8PrmCaptureFileName);
                    #endif

                    #if (ENABLE_AUTO_LOCKFILE_JPG)
                    AHC_FS_FileDirSetAttribute((INT8*)bJpgFileName, STRLEN(bJpgFileName), AHC_FS_ATTR_READ_ONLY);
                    #endif

                    bPrmWriteDone = MMP_TRUE;
                }
                else if (u8Mode == AHC_MODE_CONTINUOUS_CAPTURE) {

                    do {
                        bPrmWriteDone = MMPS_DSC_CheckContiShotWriteFileDone(gsAhcPrmSensor);

                        if (bPrmWriteDone) {
                            break;
                        }
                        else {
                            AHC_OS_SleepMs(10);
                            if (ulContiShotTimeOut) {
                                ulContiShotTimeOut--;
                            }
                        }
                    } while ((!bPrmWriteDone) && (ulContiShotTimeOut > 0));
                }
            }
            else {
                bPrmWriteDone = MMP_TRUE;
            }

            /* Close Prm Scripts */
            if (bPrmWriteDone) {
                if (bPrmCamExist) {
                    MMPS_DSC_CaptureJPEGFinish(JPE_COMP_PRM_PRIMARY, &stDscCaptInfo[0]);
                }
            }

            if (bScdCamExist) {

                AHC_Capture_GetImageSize(gsAhcScdSensor, &u32CaptureW, &u32CaptureH);

                stDscCaptInfo[1].usPrimaryW     = u32CaptureW;
                stDscCaptInfo[1].usPrimaryH     = u32CaptureH;
                stDscCaptInfo[1].usThumbWidth   = u32ThumbW;
                stDscCaptInfo[1].usThumbHeight  = u32ThumbH;

                stDscCaptInfo[1].stQualityCtl.bTargetCtl      = MMP_TRUE;
                stDscCaptInfo[1].stQualityCtl.bLimitCtl       = MMP_FALSE;
                stDscCaptInfo[1].stQualityCtl.ulTargetSize    = 400;
                stDscCaptInfo[1].stQualityCtl.ulLimitSize     = 400;
                stDscCaptInfo[1].stQualityCtl.usMaxTrialCnt   = 1;
                stDscCaptInfo[1].stQualityCtl.ubQualitySel    = u32JpgQuality;

                stDscCaptInfo[1].bCaptureEn     = MMP_TRUE;
                stDscCaptInfo[1].bExifEn        = MMP_TRUE;
            #if (DSC_ENC_THUMBNAIL_OK)
                if (MMP_IsUSBCamExist()) {
                    stDscCaptInfo[1].bThumbnailEn = MMP_FALSE;
                }
                else {
                    stDscCaptInfo[1].bThumbnailEn = (u8Mode == AHC_MODE_STILL_CAPTURE) ? (MMP_TRUE) : (MMP_FALSE);
                }
            #else
                stDscCaptInfo[1].bThumbnailEn   = MMP_FALSE;
            #endif
                stDscCaptInfo[1].bFirstShot     = MMP_TRUE;
                stDscCaptInfo[1].ubShotMode     = (u8Mode == AHC_MODE_STILL_CAPTURE) ? (JPE_COMP_SINGLE_SHOT) : (JPE_COMP_CONTINUOUS_SHOT);
                stDscCaptInfo[1].usMaxShotNum   = (u8Mode == AHC_MODE_STILL_CAPTURE) ? (1) : (m_u16ContiShotMaxNum);
                stDscCaptInfo[1].ubUiMode       = JPE_COMP_UI_MODE_DSC;
                stDscCaptInfo[1].ubCamSel       = gsAhcScdSensor;
                stDscCaptInfo[1].ubRawFmt       = JPE_COMP_FMT_NV12;
                stDscCaptInfo[1].usReviewTime   = m_u16ReviewTime;
                stDscCaptInfo[1].usWindowsTime  = m_u16WindowsTime;

                sRet = MMPS_DSC_CaptureJPEG(JPE_COMP_SCD_PRIMARY, &stDscCaptInfo[1]);
                if (sRet != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(0, sRet); goto CAPTURE_FAIL;}

            #if (ENABLE_DEBUG_AFTER_JPG)
                AHC_Capture_SetDBGDataAfterJPEG(m_ubDebugMessageBuffer, &u32DbgBufSize);

                stDscCaptInfo[1].ulExtraBufAddr  = (UINT32)m_ubDebugMessageBuffer;
                stDscCaptInfo[1].ulExtraBufSize  = u32DbgBufSize;
            #else
                stDscCaptInfo[1].ulExtraBufAddr  = 0;
                stDscCaptInfo[1].ulExtraBufSize  = 0;
            #endif

                if (u8Mode == AHC_MODE_STILL_CAPTURE) {

                    AHC_DBG_MSG(1, "SCD [%s] [%d]Bytes\r\n", stDscCaptInfo[1].bFileName, stDscCaptInfo[1].ulJpegFileSize);

                    sRet = MMPS_DSC_JpegDram2Card(&stDscCaptInfo[1]);
                    if (sRet != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, sRet); goto CAPTURE_FAIL;}

                    #if (AHC_CAPTURE_SYNC_STAMP_FILENAME == 0)
                    AHC_UF_PreAddFile(u16CaptureDirKey, (INT8*)u8ScdCaptureFileName);
                    AHC_UF_PostAddFile(u16CaptureDirKey, (INT8*)u8ScdCaptureFileName);
                    #endif

                    #if (ENABLE_AUTO_LOCKFILE_JPG)
                    AHC_FS_FileDirSetAttribute((INT8*)bScdJpgFileName, STRLEN(bScdJpgFileName), AHC_FS_ATTR_READ_ONLY);
                    #endif

                    bScdWriteDone = MMP_TRUE;
                }
                else if (u8Mode == AHC_MODE_CONTINUOUS_CAPTURE) {

                    ulContiShotTimeOut = 800;

                    do {
                        bScdWriteDone = MMPS_DSC_CheckContiShotWriteFileDone(gsAhcScdSensor);

                        if (bScdWriteDone) {
                            break;
                        }
                        else {
                            AHC_OS_SleepMs(10);
                            if (ulContiShotTimeOut) {
                                ulContiShotTimeOut--;
                            }
                        }
                    } while ((!bScdWriteDone) && (ulContiShotTimeOut > 0));
                }
            }
            else {
                bScdWriteDone = MMP_TRUE;
            }

            /* Close Scd Scripts */
            if (bScdWriteDone) {
                if (bScdCamExist) {
                    MMPS_DSC_CaptureJPEGFinish(JPE_COMP_SCD_PRIMARY, &stDscCaptInfo[1]);
                }
            }
        }
        else if (u8Mode == AHC_MODE_LONGTIME_FIRST_CAPTURE) { // TBD

            #if (PIR_JPEG_INTO_AVI_WHILE_TURN_ON)

            MMPS_3GPRECD_InitAVIFile((MMP_BYTE*)bJpgFileName, STRLEN(bJpgFileName), u32CaptureW, u32CaptureH,
                                     0, 1*1000, (stDscCaptInfo[0].ulJpegFileSize * 1 * 8), MMP_TRUE, &ulTestFileID);

            sRet = MMPS_3GPRECD_AVIAppendFrame(ulTestFileID, (MMP_UBYTE *)stDscCaptInfo.ulJpegFileAddr, stDscCaptInfo.ulJpegFileSize, &ulTestAviFileSize, &ulTestAviFrameNum);
            if (sRet != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); goto CAPTURE_FAIL;}

            MMPS_FS_FileClose(ulTestFileID);

            AHC_UF_PreAddFile(u16CaptureDirKey, (INT8*)u8PrmCaptureFileName);
            AHC_UF_PostAddFile(u16CaptureDirKey, (INT8*)u8PrmCaptureFileName);

            #else

            #endif
        }
        else if (u8Mode == AHC_MODE_LONGTIME_NEXT_CAPTURE) { // TBD

            #if (PIR_JPEG_INTO_AVI_WHILE_TURN_ON)

            MMPS_3GPRECD_InitAVIFile((MMP_BYTE *)bJpgFileName, STRLEN(bJpgFileName), u32CaptureW, u32CaptureH,
                                     0, 5*1000, (stDscCaptInfo.ulJpegFileSize * 5 * 8), MMP_FALSE, &ulTestFileID);

            sRet = MMPS_3GPRECD_AVIAppendFrame(ulTestFileID, (MMP_UBYTE *)stDscCaptInfo.ulJpegFileAddr, stDscCaptInfo.ulJpegFileSize, &ulTestAviFileSize, &ulTestAviFrameNum);
            if (sRet != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); goto CAPTURE_FAIL;}

            MMPS_FS_FileClose(ulTestFileID);

            #else

            #endif
        }
        else {
            goto CAPTURE_FAIL;
        }
    }
    else {
        goto CAPTURE_FAIL;
    }

    if (MMP_ERR_NONE != sRet) {
        goto CAPTURE_FAIL;
    }

    /* Release buffer */
    if (bPrmWriteDone && bScdWriteDone) {

        MMPS_DSC_DeInitJpegEncModule();

        MMPS_DSC_FreeFileNameBuf();
        MMPS_DSC_FreeExifEncBuf();
    }
    else {
        AHC_DBG_MSG(1, "StartTakeJpeg Fail, PrmWriteDone[%d] ScdWriteDone[%d] TOut[%d]\r\n",
                    bPrmWriteDone, bScdWriteDone, ulContiShotTimeOut);
        goto CAPTURE_FAIL;
    }

    return AHC_TRUE;

CAPTURE_FAIL:
    /* Release buffer */
    if (bPrmCamExist) {
        MMPS_DSC_CaptureJPEGFinish(JPE_COMP_PRM_PRIMARY, &stDscCaptInfo[0]);
    }
    if (bScdCamExist) {
        MMPS_DSC_CaptureJPEGFinish(JPE_COMP_SCD_PRIMARY, &stDscCaptInfo[1]);
    }

    MMPS_DSC_DeInitJpegEncModule();

    MMPS_DSC_FreeFileNameBuf();
    MMPS_DSC_FreeExifEncBuf();

    return AHC_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_GetFileName
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_Capture_GetFileName(UINT16 *pu16CaptureDirKey, INT8 *ps8JpgFileName, UINT8 *pu8CaptureFileName, UINT8 u8CamSel)
{
    MMP_BYTE    bJpgFileName[MAX_FULL_FILENAME_SIZE];
    MMP_BYTE    bDirName[16];
    UINT8       bCreateNewDir = 0;
    AHC_BOOL    ahc_ret = AHC_FALSE;

    MEMSET(bJpgFileName      , 0, sizeof(bJpgFileName));
    MEMSET(bDirName          , 0, sizeof(bDirName));
    MEMSET(pu8CaptureFileName, 0, 32);

    AHC_UF_SetFreeChar(0, DCF_SET_FREECHAR, (UINT8*)DSC_DEFAULT_FLIE_FREECHAR);

#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    ahc_ret = AHC_UF_GetName(pu16CaptureDirKey, (INT8*)bDirName, (INT8*)u8PrmCaptureFileName, &bCreateNewDir);

    if (ahc_ret == AHC_TRUE) {

        STRCPY(bJpgFileName, (INT8*)AHC_UF_GetRootDirName());
        STRCAT(bJpgFileName, "\\");
        STRCAT(bJpgFileName, bDirName);

        if (bCreateNewDir) {
            MMPS_FS_DirCreate((INT8*)bJpgFileName, STRLEN(bJpgFileName));
            AHC_UF_AddDir(bDirName);
        }

        STRCAT(bJpgFileName,"\\");
        STRCAT(bJpgFileName,(INT8*)u8PrmCaptureFileName);
    }
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    {
        AHC_RTC_TIME stAhcRtcTime;

        AHC_RTC_GetTime(&stAhcRtcTime);

        if (u8CamSel == gsAhcPrmSensor)
            AHC_UF_SetRearCamPathFlag(AHC_FALSE);
        else
            AHC_UF_SetRearCamPathFlag(AHC_TRUE);

        ahc_ret = AHC_UF_GetName2(&stAhcRtcTime, (INT8*)bJpgFileName, (INT8*)pu8CaptureFileName, AHC_Capture_GetCamStatusForDCF());
        if (ahc_ret != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahc_ret); return AHC_FALSE;}

        STRCAT(bJpgFileName, EXT_DOT);
        STRCAT(bJpgFileName, PHOTO_JPG_EXT);
        STRCAT((INT8*)pu8CaptureFileName, EXT_DOT);
        STRCAT((INT8*)pu8CaptureFileName, PHOTO_JPG_EXT);

        memcpy((void *)ps8JpgFileName, (void *)bJpgFileName, MAX_FULL_FILENAME_SIZE);
        *pu16CaptureDirKey = 0;
    }
#endif
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_PreAddFile
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_Capture_PreAddFile(UINT16 u16CaptureDirKey, UINT8 *pu8CaptureFileName)
{
    return AHC_UF_PreAddFile(u16CaptureDirKey, (INT8*)pu8CaptureFileName);
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_PostAddFile
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_Capture_PostAddFile(UINT16 u16CaptureDirKey, UINT8 *pu8CaptureFileName)
{
    return AHC_UF_PostAddFile(u16CaptureDirKey, (INT8*)pu8CaptureFileName);
}

//------------------------------------------------------------------------------
//  Function    : AHC_Capture_GetCamStatusForDCF
//  Description :
//------------------------------------------------------------------------------
UINT8 AHC_Capture_GetCamStatusForDCF(void)
{
    UINT8 u8CamStatus = 0;

    if (MMP_IsPrmCamExist()) {
        u8CamStatus |= DCF_CAM_FRONT_EXIST;
    }

    if (MMP_IsScdCamExist()) {
        if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
            if (AHC_TRUE == AHC_SNR_GetAnaDecSnrCnntStatus())
                u8CamStatus |= DCF_CAM_REAR_EXIST;
        }
        else if (CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR)) {
            if (AHC_TRUE == AHC_SNR_GetYuvSnrCnntStatus())
                u8CamStatus |= DCF_CAM_REAR_EXIST;
        }
        else if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
            u8CamStatus |= DCF_CAM_REAR_EXIST;
        }
    }
    else if (MMP_IsUSBCamExist()) {

        USB_DETECT_PHASE eUSBCurStates = 0;

        AHC_USBGetStates(&eUSBCurStates, AHC_USB_GET_PHASE_CURRENT);
        if ((eUSBCurStates == USB_DETECT_PHASE_REAR_CAM) &&
            (AHC_TRUE == AHC_HostUVC_IsDevEnabled())) {
            u8CamStatus |= DCF_CAM_REAR_EXIST;
        }
    }

    return u8CamStatus;
}
