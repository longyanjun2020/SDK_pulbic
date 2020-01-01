
#ifndef _GPS_NMEA0183_H_
#define _GPS_NMEA0183_H_

/*===========================================================================
 * Include file
 *===========================================================================*/

#include "Customer_config.h"
#include "mmpf_typedef.h"

#if (GPS_MODULE == GPS_MODULE_NMEA0183)

/*===========================================================================
 * Macro define
 *===========================================================================*/

#define NMEA_SIG_BAD        (0)
#define NMEA_SIG_LOW        (1)
#define NMEA_SIG_MID        (2)
#define NMEA_SIG_HIGH       (3)

#define NMEA_FIX_BAD        (1)
#define NMEA_FIX_2D         (2)
#define NMEA_FIX_3D         (3)

#define NMEA_MAXSAT         (12)
#define NMEA_SATINPACK      (4)
#define NMEA_NSATPACKS      (NMEA_MAXSAT / NMEA_SATINPACK)

/*
 * Distance units
 */

#define NMEA_TUD_YARDS      (1.0936)        /**< Yards, meter * NMEA_TUD_YARDS = yard */
#define NMEA_TUD_KNOTS      (1.852)         /**< Knots, kilometer / NMEA_TUD_KNOTS = knot */
#define NMEA_TUD_MILES      (1.609)         /**< Miles, kilometer / NMEA_TUD_MILES = mile */

/*
 * UART related settings
 */
#define GPS_UART_PIN 		(MMP_UART_PADSET_0)
#define GPS_UART_NUM 		(MMP_UART_ID_1)
#define GPS_MASTER_CLK 		(264000 >> 1) // (clock G0 / 2)
#define GPS_BAUD_RATE 		(9600)
#define RX_GPS_SIGNAL  		'$'
#define RX_SENSITIVE  		(100)
#define GPS_RX_QUEUE_SIZE	(4096)

/*===========================================================================
 * Enum define
 *===========================================================================*/

enum NMEAPACKTYPE
{
    //For GPS
    GPNON   = 0x0000,   /**< Unknown packet type. */
    GPGGA   = 0x0001,   /**< GGA - Essential fix data which provide 3D location and accuracy data. */
    GPGSA   = 0x0002,   /**< GSA - GPS receiver operating mode, SVs used for navigation, and DOP values. */
    GPGSV   = 0x0004,   /**< GSV - Number of SVs in view, PRN numbers, elevation, azimuth & SNR values. */
    GPRMC   = 0x0008,   /**< RMC - Recommended Minimum Specific GPS/TRANSIT Data. */
    GPVTG   = 0x0010,   /**< VTG - Actual track made good and speed over ground. */
    GPGLL   = 0x0020,   /**< GLL - Latitude and longitude, with time of position fix and status */
    //For Glonass
    GNGSA	= 0x0040,
    GNRMC	= 0x0080,
    GLGSV	= 0x0100
};

enum NMEARECEIVEPATH
{
	NMEA_RECEIVE_UART  = 0,
    NMEA_RECEIVE_USB   = 1,
    NMEA_RECEIVE_DDC   = 2, 
    NMEA_RECEIVE_TXT   = 3 //For Test(Read data from txt file)
};

typedef enum _NMEACOMMAND_TYPE // Only support UBX protocol now
{
	NMEACMD_CFG_SET_EXPERT   	= 0,
	NMEACMD_CFG_SL_CFG			= 1,
	NMEACMD_RST_HOT_START		= 2,
	NMEACMD_RST_WARM_START_1	= 3, 	// Clear EPH (ephemeris, for satellite orbit), Keep ANA(AssistNow Aiding) 
	NMEACMD_RST_WARM_START_2	= 4, 	// Clear EPH (ephemeris, for satellite orbit), Clear ANA(AssistNow Aiding)
	NMEACMD_RST_COLD_START		= 5, 	// Clear ALL
	NMEACMD_CFG_BAUDRATE_57600	= 6,
	// new added commands for u-blox 7
	NMEACMD_CFG_ANA_3DFIX 		= 7, 	// Enable ANA function (AssistNow Autonomous), 3D fix
	NMEACMD_CFG_AUTOMOTIVE_MODE = 8, 	// Automotive mode, PDOP Mask = 35, Ele = 3, Static hold 1.0m/s
	NMEACMD_CFG_NMEA_CFG 		= 9, 	// NMEA configuration: Filters (12346) & 1-Extended (3-digit), Max SVs (16), Compatibility mode (V), GP
	NMEACMD_CFG_PRN128 			= 10, 	// Enable PRN128
	NMEACMD_CFG_GLL_DEL 		= 11, 	// Delete GLL
	NMEACMD_CFG_VTG_DEL 		= 12, 	// Delete VTG
	NMEACMD_CFG_SETTING_SAVE 	= 13, 	// Save current setting
	NMEACMD_CFG_GLONASS_SWITCH 	= 14, 	// Switch to GLONASS
	NMEACMD_CFG_GPS_SWITCH 		= 15 	// Switch to GPS
	// End of new added commands for u-blox 7
} NMEACOMMAND_TYPE;

/*===========================================================================
 * Structure define
 *===========================================================================*/

typedef struct _NMEATIME
{
    MMP_LONG     iYear;       /**< Years since 1900 */
    MMP_LONG     iMon;        /**< Months since January - [0,11] */
    MMP_LONG     iDay;        /**< Day of the month - [1,31] */
    MMP_LONG     iHour;       /**< Hours since midnight - [0,23] */
    MMP_LONG     iMin;        /**< Minutes after the hour - [0,59] */
    MMP_LONG     iSec;        /**< Seconds after the minute - [0,59] */
    MMP_LONG     iHsec;       /**< Hundredth part of second - [0,99] */

} NMEATIME, *pNmeaTime;

typedef struct _NMEASATELLITE
{
    MMP_LONG     iId;         /**< Satellite PRN number */
    MMP_LONG     iIn_use;     /**< Used in position fix */
    MMP_LONG     iElv;        /**< Elevation in degrees, 90 maximum */
    MMP_LONG     iAzimuth;    /**< Azimuth, degrees from true north, 000 to 359 */
    MMP_LONG     iSig;        /**< Signal, 00-99 dB */

} NMEASATELLITE;

/**
 * GGA packet information structure (Global Positioning System Fix Data)
 */
typedef struct _NMEAGGA
{
    NMEATIME 	sUTC;         /**< UTC of position (just time) */
	double  	dwLat;        /**< Latitude in NDEG - [degree][min].[sec/60] */
    MMP_BYTE    chNS;         /**< [N]orth or [S]outh */
	double  	dwLon;        /**< Longitude in NDEG - [degree][min].[sec/60] */
    MMP_BYTE    chEW;         /**< [E]ast or [W]est */
    MMP_LONG    iSig;         /**< GPS quality indicator (0 = Invalid; 1 = Fix; 2 = Differential, 3 = Sensitive) */
	MMP_LONG    iSatinuse;    /**< Number of satellites in use (not those in view) */
    double  	dwHDOP;       /**< Horizontal dilution of precision */
    double  	dwElv;        /**< Antenna altitude above/below mean sea level (geoid) */
    MMP_BYTE    chElv_Units;  /**< [M]eters (Antenna height unit) */
    double  	dwDiff;       /**< Geoidal separation (Diff. between WGS-84 earth ellipsoid and mean sea level. '-' = geoid is below WGS-84 ellipsoid) */
    MMP_BYTE    chDiff_Units; /**< [M]eters (Units of geoidal separation) */
    double  	dwDgps_Age;   /**< Time in seconds since last DGPS update */
    MMP_LONG    iDgps_sid;    /**< DGPS station ID number */
} NMEAGGA;

/**
 * GSA packet information structure (Satellite status)
 */
typedef struct _NMEAGSA
{
    MMP_BYTE    chFix_Mode;   /**< Mode (M = Manual, forced to operate in 2D or 3D; A = Automatic, 3D/2D) */
    MMP_LONG    iFix_Type;    /**< Type, used for navigation (1 = Fix not available; 2 = 2D; 3 = 3D) */
    MMP_LONG    iSat_Prn[NMEA_MAXSAT]; /**< PRNs of satellites used in position fix (null for unused fields) */
    double  	dwPDOP;       /**< Dilution of precision */
    double  	dwHDOP;       /**< Horizontal dilution of precision */
    double  	dwVDOP;       /**< Vertical dilution of precision */
} NMEAGSA;

/**
 * GSV packet information structure (Satellites in view)
 */
typedef struct _NMEAGSV
{
    MMP_LONG     iPack_count; /**< Total number of messages of this type in this cycle */
    MMP_LONG     iPack_index; /**< Message number */
    MMP_LONG     iSat_count;  /**< Total number of satellites in view */
    NMEASATELLITE sSat_data[NMEA_SATINPACK];
} NMEAGSV;

/**
 * RMC packet information structure (Recommended Minimum sentence C)
 */
typedef struct _NMEARMC
{
    NMEATIME 	sUTC;         /**< UTC of position */
    MMP_BYTE    chStatus;     /**< Status (A = active or V = void) */
	double  	dwLat;        /**< Latitude in NDEG - [degree][min].[sec/60] */
    MMP_BYTE    chNS;         /**< [N]orth or [S]outh */
	double  	dwLon;        /**< Longitude in NDEG - [degree][min].[sec/60] */
    MMP_BYTE    chEW;         /**< [E]ast or [W]est */
    double  	dwSpeed;      /**< Speed over the ground in knots */
    double  	dwDirection;  /**< Track angle in degrees True */
    double  	dwDeclination;/**< Magnetic variation degrees (Easterly var. subtracts from true course) */
    MMP_BYTE    chDeclin_ew;  /**< [E]ast or [W]est */
    MMP_BYTE    chMode;       /**< Mode indicator of fix type (A = autonomous, D = differential, E = estimated, N = not valid, S = simulator) */
} NMEARMC;

/**
 * VTG packet information structure (Track made good and ground speed)
 */
typedef struct _NMEAVTG
{
    double  	dwDir;        /**< True track made good (degrees) */
    MMP_BYTE    chDir_t;      /**< Fixed text 'T' indicates that track made good is relative to true north */
    double  	dwDec;        /**< Magnetic track made good */
    MMP_BYTE    chDec_m;      /**< Fixed text 'M' */
    double  	dwSpn;        /**< Ground speed, knots */
    MMP_BYTE    chSpn_n;      /**< Fixed text 'N' indicates that speed over ground is in knots */
    double  	dwSpk;        /**< Ground speed, kilometers per hour */
    MMP_BYTE    chSpk_k;      /**< Fixed text 'K' indicates that speed over ground is in kilometers/hour */
} NMEAVTG;

/**
 * VTG packet information structure (Track made good and ground speed)
 */
typedef struct _NMEAGLL
{
	double  	dwLat;        /**< Latitude in NDEG - [degree][min].[sec/60] */
    MMP_BYTE    chNS;         /**< [N]orth or [S]outh */
	double  	dwLon;        /**< Longitude in NDEG - [degree][min].[sec/60] */
    MMP_BYTE    chEW;         /**< [E]ast or [W]est */
    NMEATIME 	sUTC;         /**< UTC of position */
    MMP_BYTE    chStatus;     /**< Status (A = active or V = void) */
} NMEAGLL;

typedef struct _NMEASATINFO
{
    MMP_LONG     iInuse;      /**< Number of satellites in use (not those in view) */
    MMP_LONG     iInview;     /**< Total number of satellites in view */
    NMEASATELLITE sSat[NMEA_MAXSAT]; /**< Satellites information */
} NMEASATINFO;
typedef void* GPS_HANDLE;
typedef struct _NMEAINFO
{
    GPS_HANDLE  *h_dec;
    double 		 dwLat;        /**< Latitude in NDEG - +/-[degree][min].[sec/60] */
    double  	 dwLon;        /**< Longitude in NDEG - +/-[degree][min].[sec/60] */
    double 		 dwSpeed;      /**< Speed over the ground in kilometers/hour */
    double 		 dwDirection;  /**< Track angle in degrees True */
    double 	 	 dwElv;        /**< Antenna altitude above/below mean sea level (geoid) in meters */
    MMP_LONG     iSmask;       /**< Mask specifying types of packages from which data have been obtained */

    NMEATIME 	 sUTC;         /**< UTC of position */

    //MMP_LONG     iSmask;       /**< Mask specifying types of packages from which data have been obtained */

    //NMEATIME 	 sUTC;         /**< UTC of position */

    MMP_LONG     iSig;         /**< GPS quality indicator (0 = Invalid; 1 = Fix; 2 = Differential, 3 = Sensitive) */
    MMP_LONG     iFix;         /**< Operating mode, used for navigation (1 = Fix not available; 2 = 2D; 3 = 3D) */

    double  	 dwPDOP;       /**< Position Dilution Of Precision */
    double  	 dwHDOP;       /**< Horizontal Dilution Of Precision */
    double  	 dwVDOP;       /**< Vertical Dilution Of Precision */

    //double 	 dwLat;        /**< Latitude in NDEG - +/-[degree][min].[sec/60] */
    //double  	 dwLon;        /**< Longitude in NDEG - +/-[degree][min].[sec/60] */
    //double 	 dwElv;        /**< Antenna altitude above/below mean sea level (geoid) in meters */
    //double 	 dwSpeed;      /**< Speed over the ground in kilometers/hour */
    //double 	 dwDirection;  /**< Track angle in degrees True */
    double 		 dwDeclination;/**< Magnetic variation degrees (Easterly var. subtracts from true course) */

    NMEASATINFO  sSatinfo_GPS;     /**< Satellites information for GPS*/
    NMEASATINFO  sSatinfo_GLONASS; /**< Satellites information for GLONASS*/

    MMP_UBYTE	 ubTotalSatInUse;  //Total Sat Number for GNSS.
} NMEAINFO, *pNmeaInfo, ST_GPS_INFO;

typedef struct _3RD_PARTY_GPS 
{
    //00
    MMP_ERR (*GPS_SetCommand)(struct _3RD_PARTY_GPS *pthis, void *pCommAry, MMP_ULONG ulCmdSize);
    MMP_ERR (*GPS_Initiate_ANA)(struct _3RD_PARTY_GPS *pthis);
    MMP_ERR (*GPS_SetHotStart)(struct _3RD_PARTY_GPS *pthis);
    MMP_ERR (*GPS_SetWarmStart_1)(struct _3RD_PARTY_GPS *pthis);    
    MMP_ERR (*GPS_SetWarmStart_2)(struct _3RD_PARTY_GPS *pthis);
	//05
    MMP_ERR (*GPS_SetColdStart)(struct _3RD_PARTY_GPS *pthis);
    MMP_ERR (*GPS_SetBR57600)(struct _3RD_PARTY_GPS *pthis); 
	MMP_ERR (*GPS_DisableNMEASentence)(struct _3RD_PARTY_GPS *pthis);
	MMP_ERR (*GPS_EnableNMEASentence)(struct _3RD_PARTY_GPS *pthis);
} THIRD_PARTY_GPS;

/*===========================================================================
 * Function Prototype
 *===========================================================================*/

MMP_LONG	GPS_Atoi_NMEA0183(MMP_BYTE *pStr, MMP_LONG iStr_sz, MMP_LONG iRadix);
double 		GPS_Atof_NMEA0183(MMP_BYTE *pStr, MMP_LONG iStr_sz);
MMP_LONG 	GPS_Scanf_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, MMP_BYTE *pFormat, ...);
void 		GPS_InitReceivePath_NMEA0183(MMP_BYTE path, MMP_ULONG ulBaudRate);
void 		GPS_UnInitPathUART_NMEA0183(MMP_ULONG ulBaudRate);
void 		GPS_ControlPathUART_NMEA0183(MMP_BOOL bEnable);
void 		GPS_ControlReceivePath_NMEA0183(MMP_BYTE path, MMP_BOOL bEnable);
void 		GPS_GetGPSPack_NMEA0183(MMP_BYTE path, MMP_BYTE *bDebugString, MMP_ULONG *ulDebugStringLength);
void 		GPS_ParserInitialize_NMEA0183(void);
void 		GPS_ResetContainer_NMEA0183(void);
void 		GPS_GMT2LocalTime(NMEATIME *sGMTBackup, NMEATIME *sRes, signed char sbGMTOffset);
MMP_LONG 	GPS_ParseTime_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEATIME *sRes);
MMP_LONG 	GPS_PackType_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz);
MMP_LONG 	GPS_FindTail_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, MMP_LONG *pRes_crc);
MMP_LONG 	GPS_ParseGPGGA_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEAGGA *psPack);
MMP_LONG 	GPS_ParseGPGSA_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEAGSA *psPack);
MMP_LONG 	GPS_ParseGNGSA_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEAGSA *psPack);
MMP_LONG 	GPS_ParseGPGSV_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEAGSV *psPack);
MMP_LONG 	GPS_ParseGLGSV_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEAGSV *psPack);
MMP_LONG 	GPS_ParseGPRMC_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEARMC *psPack);
MMP_LONG 	GPS_ParseGNRMC_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEARMC *psPack);
MMP_LONG 	GPS_ParseGPVTG_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEAVTG *psPack);
void 		GPS_GGA2info_NMEA0183(NMEAGGA *psPack, NMEAINFO *psInfo);
void 		GPS_GSA2info_NMEA0183(NMEAGSA *psPack, NMEAINFO *psInfo);
void 		GPS_GPGSV2info_NMEA0183(NMEAGSV *psPack, NMEAINFO *psInfo);
void 		GPS_GLGSV2info_NMEA0183(NMEAGSV *psPack, NMEAINFO *psInfo);
void 		GPS_RMC2info_NMEA0183(NMEARMC *psPack, NMEAINFO *psInfo);
void 		GPS_VTG2info_NMEA0183(NMEAVTG *psPack, NMEAINFO *psInfo);
void 		GPS_DubugMessageInfo_NMEA0183(NMEAINFO *psInfo);
void 		GPS_PaeserMain_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEAINFO *pInfo);

pNmeaInfo 	GPS_Information(void);
MMP_BOOL 	GPS_IsValidValue_NMEA0183(void);
//void 		GPS_EnableANA_NMEA0183(void);

//#if (GPS_CONFIG_NMEA_FILE)
MMP_BOOL 	GPS_GetGPSStringFromFile(MMP_BYTE *bDebugString, MMP_ULONG *ulDebugStringLength);
MMP_BOOL 	GPS_IsEOF(void);
void 		GPS_ResetEOF(void);
//#endif

pNmeaTime 	GPS_GetGMTBackupTime(void);
void 		GPS_InitPathUART_E_DOG(void);

void 		GPS_SetCommand_NMEA0183(NMEACOMMAND_TYPE type);
void 		GPS_ParserMain_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEAINFO *pInfo);

MMP_ERR GPS_SetCommand(void *CommAry, MMP_ULONG ulCmdSize);

void MMPF_3RDParty_GPS_Register(struct _3RD_PARTY_GPS *pdev_obj);
MMP_ERR MMPF_3RDParty_GPS_Initiate(void);
MMP_ERR MMPF_3RDParty_GPS_SetHotStart(void);
MMP_ERR MMPF_3RDParty_GPS_SetWarmStart_1(void);
MMP_ERR MMPF_3RDParty_GPS_SetWarmStart_2(void);
MMP_ERR MMPF_3RDParty_GPS_SetColdStart(void);
MMP_ERR MMPF_3RDParty_GPS_SetBR57600(void);
MMP_ERR MMPF_3RDParty_GPS_DisableNMEASentence(void);
MMP_ERR MMPF_3RDParty_GPS_EnableNMEASentence(void);

#endif // (GPS_MODULE == GPS_MODULE_NMEA0183)

#endif // _GPS_NMEA0183_H_
