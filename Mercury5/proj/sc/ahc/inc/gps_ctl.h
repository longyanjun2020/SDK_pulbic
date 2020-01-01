//------------------------------------------------------------------------------
//
//  File        : gps_ctl.h
//  Description :
//  Author      :
//  Revision    : 0.0
//
//------------------------------------------------------------------------------
#ifndef _GPS_ctl_H_
#define _GPS_ctl_H_

/*===========================================================================
 * Include file
 *===========================================================================*/

///#include "data_type.h"
#include "config_fw.h"
#include "Customer_config.h"

#if(GPS_MODULE == GPS_MODULE_NMEA0183)
#include "gps_nmea0183.h"
#elif(GPS_MODULE == GPS_MODULE_GMC1030)
#include "GPSRadar_GMC1030.h"
#endif
#include "os_wrap.h"

//#include "ahc_general.h"
#include "ahc_rtc.h"
#include "Daylight_Saving_Time.h"
/*===========================================================================
 * Macro define
 *===========================================================================*/

 //File
#define GPS_TEMP_INFOFILE_DIR           "DATA"
#define GPS_TEMP_INFOFILE_NAME          "GPS_Info.txt"

//Error Check
#define GPS_NOSIGNAL_MARK_DOUBLE        0xFFFFFFFF
#define GPS_NOSIGNAL_MARK_LONG          0xFFFFFFFF
#define GPS_NOSIGNAL_MARK_SHORT         0xFFFF
#define GPS_NOSIGNAL_MARK_BYTE          0xFF

//Config
#define GPS_CONFIG_DBG_ENABLE           0
#define GPS_CONFIG_GRAPHIC_ENABLE       0
#define GPS_CONFIG_BUFFER_SIZE          2048
#define GPS_CONFIG_MAXGPSINFONUM        512
#define GPS_CONFIG_INFOSTRUC_VER        0x01
#define GPS_CONFIG_NMEA_FILE            0
    #if (GPS_CONFIG_NMEA_FILE  == 1)
    #define GPS_CONFIG_NMEA_FILE_NAME   "SD:\\GPS_Info.txt"
    #endif

#define GPS_RAW_BUFFER_SIZE             (1024*16)
#define GPS_OFFSET_ENABLE               0
    #if (GPS_OFFSET_ENABLE == 1)
    #define GPS_OFFSET_LAT              7.110545
    #define GPS_OFFSET_LON             -0.733213
    #endif
/*============= Offset data ======================
 *          31.938391, 120.276875
 *          24.967322, 121.541071
 *          24.827846, 121.010088
 *=================================================*/

//Task
#define GPS_FLAG_INITIAL                0x00000001
#define GPS_FLAG_GETGPSPACK             0x00000002
#define GPS_FLAG_PARSE                  0x00000004
#define GPS_FLAG_GETINFO                0x00000008
#define GPS_FLAG_GPSINFO2CHUCK          0x00000010
#define GPS_FLAG_JOB                    0x00000020
#define GPS_FLAG_SWITCHBUFFER           0x00000040
#define GPS_FLAG_SWITCHBUFFER_CLOSE     0x00000080

#ifdef TPMS_FUNC_EN
#define TPMS_FLAG_GETTPMSPACK           0x00000100
#endif

#define UART_CTL_FLAG_MAX               0x80000000


//Info for AVI chuck
#define GPS_MAKE_FCC(c0, c1, c2, c3) \
                ((MMP_ULONG)c0        | ((MMP_ULONG)c1 << 8) | \
                ((MMP_ULONG)c2 << 16) | ((MMP_ULONG)c3 << 24))

#define GPS_ABS(a) (((a) < 0) ? (-(a)) : (a))

//Measurement
#define TIMERPERIOD                     1000 // 1s

//For UART COMMAND
#define D_RMC                           (1<<0)
#define D_GGA                           (1<<1)
#define D_GSA                           (1<<2)
#define D_GSV                           (1<<3)
#define D_VTG                           (1<<4)

//KML header, position, tail
#define KML_HEADER "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n\
  <Document>\n\
    <name>Paths</name>\n\
    <description>The path of GVP Car DV</description>\n\
    <Style id=\"blueLine\">\n\
      <LineStyle>\n\
        <color>ffff0000</color>\n\
        <width>4</width>\n\
      </LineStyle>\n\
    </Style>\n\
    <Placemark>\n\
      <name>CAR PATH</name>\n\
      <description>GPS Path of Car DV %s</description>\n\
      <styleUrl>#blueLine</styleUrl>\n\
      <LineString>\n\
        <altitudeMode>relative</altitudeMode>\n\
        <coordinates>\n"

#define KML_POSITION "%f,%f,%d\n"

#define KML_TAILER  "\n\
        </coordinates>\n\
      </LineString>\n\
    </Placemark>\n\
  </Document>\n\
</kml>\n\
"

#define GPS_RAW_FILE_EXTENTION "NMEA"
#define GPS_KML_FILE_EXTENTION "GPSK"

// Maximum size of time zone table.
#define MAX_TIMEZONE_TABLE_SIZE     (100)

#define GPS_DEFAULT_PRERECORD_TIME  0xFFFFFFFF

/*===========================================================================
 * Enum define
 *===========================================================================*/

enum CURRENTSYSTEM
{
    GPS         = 0,
    GLONASS     = 1,
    SYSTEM_MAX  = 2
};

enum SCANFTOKEN
{
    SCAN_TOKS_COMPARE   = 1,
    SCAN_TOKS_PERCENT   = 2,
    SCAN_TOKS_WIDTH     = 3,
    SCAN_TOKS_TYPE      = 4
};

/*===========================================================================
 * Structure define
 *===========================================================================*/

typedef struct  _GPS_ATTRIBUTE
{
    MMP_UBYTE   ubStoreFreq;
    signed char byGMTOffset;
    MMP_UBYTE   ubDummy[2];

}GPS_ATTRIBUTE, *pGPS_Attribute;

typedef struct _GPSINFOCHUCKTIME
{
    MMP_UBYTE     byYear;       /**< Years since 1900 */
    MMP_UBYTE     byMon;        /**< Months since January - [0,11] */
    MMP_UBYTE     byDay;        /**< Day of the month - [1,31] */
    MMP_UBYTE     byHour;       /**< Hours since midnight - [0,23] */
    MMP_UBYTE     byMin;        /**< Minutes after the hour - [0,59] */
    MMP_UBYTE     bySec;        /**< Seconds after the minute - [0,59] */

}GPSINFOCHUCKTIME;

typedef struct _GPSINFOCHUCK
{
    double                  dwLat;      /**< Latitude in NDEG - +/-[degree][min].[sec/60] */
    double                  dwLon;      /**< Longitude in NDEG - +/-[degree][min].[sec/60] */
    MMP_LONG                lAlt;       /**< Altitude in meter +-:under/below sea level*/
    MMP_USHORT              usSpeed;    /**< Speed unit: km/h */
    GPSINFOCHUCKTIME        sUTC;       /**< UTC of position */
    MMP_UBYTE               ubDirection;/**< Clockwise degree from the North.*/
    MMP_UBYTE               ubFlag;     /**< Check if the GPS data is valid;*/
    MMP_UBYTE               ubVersion;  /**< Stuture Version*/
    MMP_UBYTE               ubReserved;

}GPSINFOCHUCK, *pGPSInfoChuck;

#if (VR_VIDEO_TYPE == COMMON_VR_VIDEO_TYPE_3GP)
// ulSize shound convert to big endian
typedef struct _GPSCHUCKHEADER
{
    MMP_ULONG ulSize;               ///< chunk size, not including the initial 8 bytes
    MMP_ULONG ulFourCC;             ///< chunk ID

}GPSCHUCKHEADER, *pGPSChuckHeader;
#else
// ulSize is little endian
typedef struct _GPSCHUCKHEADER
{
    MMP_ULONG ulFourCC;             ///< chunk ID
    MMP_ULONG ulSize;               ///< chunk size, not including the initial 8 bytes

}GPSCHUCKHEADER, *pGPSChuckHeader;
#endif

typedef struct  _GPS_LOG
{
    MMP_ULONG ulLogID;
    AHC_RTC_TIME psDateTime;

}GPS_LOG;

/*===========================================================================
 * Extern varible
 *===========================================================================*/

extern MMPF_OS_FLAGID       UartCtrlFlag;
extern unsigned int         dump_nmeaflag;

/*===========================================================================
 * Function prototype
 *===========================================================================*/
MMP_LONG    GPSCtrl_Atoi(MMP_BYTE *pStr, MMP_LONG iStr_sz, MMP_LONG iRadix);
double      GPSCtrl_Atof(MMP_BYTE *pStr, MMP_LONG iStr_sz);
MMP_LONG    GPSCtrl_Scanf(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, MMP_BYTE *pFormat, ...);
void        GPSCtrl_Enable(MMP_BOOL bEnable);
void        GPSCtrl_Initial(void);
void        GPSCtrl_UnInitial(void);
void        GPSCtrl_ResetContainer(void);
void        GPSCtrl_GetGPSPack(MMP_BYTE *bGPSString, MMP_ULONG *ulGPSStringLength);
void        GPSCtrl_ControlGPSPath(MMP_BOOL bEnable);
#if(GPS_MODULE == GPS_MODULE_NMEA0183)
void        GPSCtrl_ParseGPSMain(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEAINFO *pInfo);
void        GPSCtrl_DubugMessageInfo(NMEAINFO *pInfo);
void        GPSCtrl_GMT2LocalTime(NMEATIME *sGMTBackup, NMEATIME *sRes, signed char sbGMTOffset);
MMP_BOOL    GPSCtrl_LinkGPSTime2RTC(NMEATIME *sGPS);
#elif(GPS_MODULE == GPS_MODULE_GMC1030)
void        GPSCtrl_ParseGPSRadarMain(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, GPSRADARINFO *pInfo);
void        GPSCtrl_DubugMessageInfo(GPSRADARINFO *pInfo);
void        GPSCtrl_GMT2LocalTime(GPSRADARTIME *sGMTBackup, GPSRADARTIME *sRes, signed char sbGMTOffset);
MMP_BOOL    GPSCtrl_LinkGPSTime2RTC(GPSRADARTIME *sGPS);
#endif

MMP_BOOL    GPSCtrl_GPS_IsValidValue(void);
MMP_BOOL    GPSCtrl_ModuleConnected(void);
void        GPSCtrl_GPSFormatTrans(double dwInputValue, MMP_USHORT *sDegree, MMP_USHORT *sMin, double *sSec);
MMP_UBYTE   GPSCtrl_CheckRefForExif(MMP_UBYTE ubType);
void        GPSCtrl_Verification(void);
MMP_ULONG   GPSCtrl_GetSpeed(MMP_ULONG uiUnit);
MMP_UBYTE   GPSCtrl_GetSignalStrength(void);
void        GPSCtrl_BackupGPSInfo(MMP_ULONG ulCounter);
void        GPSCtrl_SetGPSRawFileName(MMP_BYTE bFilename[], MMP_USHORT usLength);
MMP_BOOL    GPSCtrl_GPSRawWrite(MMP_BYTE *pBuff, MMP_USHORT usLength);
MMP_BOOL    GPSCtrl_GPSRawClose(void);

void        GPSCtrl_SetGPSRawFileName_Emer(MMP_BYTE bFilename[], MMP_USHORT usLength);
MMP_BOOL    GPSCtrl_GPSRawWriteFirst_Emer(void);
MMP_BOOL    GPSCtrl_GPSRawClose_Emer(void);

void        GPSCtrl_SetCurrentSystem(MMP_UBYTE ubSystem);
MMP_UBYTE   GPSCtrl_GetCurrentSystem(void);

void        GPSCtrl_ResetBufferControlVariable(void);
void        GPSCtrl_OpenInfoFile(MMP_BYTE *ubFileName);
void        GPSCtrl_CloseInfoFile(void);
void        GPSCtrl_StartRecord(void);
void        GPSCtrl_EndRecord(void);
void        GPSCtrl_EndRecord_Backup(void);
pGPSInfoChuck GPSCtrl_InfoAddressForAviChuck(void);
MMP_ULONG   GPSCtrl_InfoSizeForAviChuck(void);
pGPSChuckHeader GPSCtrl_HeaderAddressForAviChuck(MMP_UBYTE ubSelection);
void        GPSCtrl_SetHeaderForAviChuck(void);
void        GPSCtrl_SetHeaderForAviChuck_GPSConfig(void);
pGPS_Attribute GPSCtrl_AttributeAddressForAviChuck(void);
void        GPSCtrl_RestoreAviChuck(void);
pGPSInfoChuck GPSCtrl_GetLastDataAddr(void);
pGPSInfoChuck GPSCtrl_GetBackupDataAddr(void);
void        GPS_EnableNMEA0183(void);
MMP_BOOL    GPSCtrl_IsCounting(void);
void        GPSCtrl_Timer_ISR(void *tmr, void *arg);
MMP_BOOL    GPSCtrl_Timer_Start(MMP_ULONG ulTime);
MMP_BOOL    GPSCtrl_Timer_Stop(void);

void        UARTCtrlTask(void);

void        GPSCtrl_SetKMLFileName(MMP_BYTE bFilename[], MMP_USHORT usLength);
MMP_BOOL    GPSCtrl_KMLGen_Write_Header(void);
MMP_BOOL    GPSCtrl_KMLGen_Write_Position(double lat, double lon, int att);
MMP_BOOL    GPSCtrl_KMLGen_Write_TailAndClose(void);

void        GPSCtrl_SetGPSRawStart_Emer(MMP_BOOL bStart);
MMP_BOOL    GPSCtrl_GetGPSRawStart_Emer(void);

void        GPSCtrl_SwitchRawFilePingPongBuffer(void);
void        GPSCtrl_GPSRawResetBuf_Emer(void);
void        GPSCtrl_GPSRawResetBuffer(void);

MMP_BOOL    GPSCtrl_GetGPSRawIndex_Emer(void);
void        GPSCtrl_IncGPSRawIndex_Emer(void);

void        GPSCtrl_SetGPSRawBufTime_Emer(MMP_ULONG ulTime);
MMP_BOOL    GPSCtrl_GPSRawWriteFirst_Normal(void);
void GPSCtrl_SetGPSRawWriteFirst(MMP_BOOL bStart);
MMP_BOOL GPSCtrl_GPSRawWriteFlushBuf_Emer(void);
MMP_BOOL GPSCtrl_GPSRawWrite_Close(void);
#if (EMERGENTRECD_SUPPORT)
void GPSCtrl_SetGPSRawBufTime_Normal(MMP_ULONG ulTime);
#endif
void GPSCtrl_GetFirstLocationTime(GPS_LOG* psGPSLog);
void GPSCtrl_SetFirstLocationTime(GPS_LOG *pGPSlog);
MMP_BOOL GPSCtrl_EnableStatus(void);
void GPSCtrl_SetCommand(MMP_UBYTE ubType, MMP_UBYTE ubValue);
void GPSCtrl_StartCountTTFF(void);
UINT64 GPSCtrl_GetTTFFTime(void);
void GPSCtrl_StopCountTTFF(void);
MMP_BOOL GPSCtrl_GPSRawFlushBuf(void);
MMP_BOOL GPSCtrl_GetGPSRawWriteFirst(void);
void GPSCtrl_IncGPSRawIndex_Normal(void);
AHC_BOOL GPSCtrl_GPSParsing(void);
MMP_ULONG GPSCtrl_GetGPSRawFileId_Emer(void);
MMP_ULONG GPSCtrl_GetGPSRawFileId(void);
MMP_BOOL GPSCtrl_GPSRawWriteBuffer(MMP_BYTE *pBuff, MMP_USHORT usLength);
MMP_BOOL GPSCtrl_GPSRawWriteBuffer_Emer(MMP_BYTE *pBuff, MMP_USHORT usLength);
MMP_BOOL GPSCtrl_GPSRawWriteBuffer_Normal(MMP_BYTE *pBuff, MMP_USHORT usLength);
MMP_BOOL GPSCtrl_GPSRawWrite_Emer(MMP_BYTE *pBuff, MMP_USHORT usLength);
MMP_BOOL SetTimeZoneTable(signed char* pTable, MMP_ULONG TableSize);
const signed char* GetTimeZoneTable(void);

void    GPSCtrl_EnableTimeSync(MMP_BOOL bEnable);
void    GPSCtrl_SwitchRawFileClose(void);
void    AHC_GPS_RestorePreRecordInfo( UINT32 ulPreRecordTime, MMP_BOOL bUseLastData );
void    AHC_GPS_TriggerRestorePreRecordInfo( MMP_BOOL bTrigger, UINT32 ulPreRecordTime, MMP_BOOL bUseLastData );
MMP_BOOL AHC_GPS_NeedToRestorePreRecordInfo( UINT32* ulPreRecordTime );
void    AHC_GPS_FlushBackupBuffer(MMP_UBYTE ubID, MMP_BOOL bEnable);
MMP_BOOL AHC_GPS_NeedToFlushBackupBuffer(MMP_UBYTE ubID);

AHC_BOOL    AHC_GPS_SetCurInfo(void);
AHC_BOOL    AHC_GPS_Module_Attached(void);

MMP_HANDLE MMPF_GPS_Open(void);

#endif
