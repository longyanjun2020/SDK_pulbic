
#ifndef _GPSRADAR_GMC1030_H_
#define _GPSRADAR_GMC1030_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/

#include "Customer_config.h"
#include "mmpf_typedef.h"

#if (GPS_MODULE == GPS_MODULE_GMC1030)

/*===========================================================================
 * Macro define
 *===========================================================================*/
 /*
 * UART related settings
 */

#define GPSRADAR_UART_PIN 		(MMPF_UART_PADSET_3)
#define GPSRADAR_UART_NUM 		(MMP_UART_ID_1)
#define GPSRADAR_MASTER_CLK		(120000) // clock G0/2
#define GPSRADAR_BAUD_RATE 		(115200)
#define RX_GPSRADAR_SIGNAL 		'$'
#define RX_SENSITIVE  			100
#define RX_QUEUE_SIZE			256
#define MAXSATELLITE        	(12)

#define RADARCMD_HEADER			'$2,'
#define RADARCMD_TAIL			'\r\n'

/*===========================================================================
 * Enum define
 *===========================================================================*/
enum GPSRADARRECEIVEPATH
{
	GPSRADAR_RECEIVE_UART  = 0,
    GPSRADAR_RECEIVE_USB   = 1,
    GPSRADAR_RECEIVE_DDC   = 2,
    GPSRADAR_RECEIVE_TXT   = 3
};

typedef enum _RADARSET_TYPE
{
	RADARSET_MUTE   		  	= 1,
    RADARSET_SPEED_REFINEMENT 	= 2,
    RADARSET_ALARM  			= 3,
    RADARSET_ENABLE 			= 4,
    RADARSET_BRIGHTNESS 		= 5,
    RADARSET_VOLUME  			= 6
}RADARSET_TYPE;

typedef enum _RADARSET_MUTE_SPEED
{
	RADARSET_MUTE_OFF  		  	= 1,
	RADARSET_MUTE_30  		  	= 2,
	RADARSET_MUTE_40  		  	= 3,
	RADARSET_MUTE_50  		  	= 4
}RADARSET_MUTE_SPEED;

typedef enum _RADARSET_SPEED_REFIN
{
	RADARSET_SPEED_REFIN_MINUS_10 = 1,
	RADARSET_SPEED_REFIN_MINUS_08 = 2,
	RADARSET_SPEED_REFIN_MINUS_06 = 3,
	RADARSET_SPEED_REFIN_MINUS_04 = 4,
	RADARSET_SPEED_REFIN_MINUS_02 = 5,
	RADARSET_SPEED_REFIN_PLUS_00 = 6,
	RADARSET_SPEED_REFIN_PLUS_02 = 7,
	RADARSET_SPEED_REFIN_PLUS_04 = 8,
	RADARSET_SPEED_REFIN_PLUS_06 = 9,
	RADARSET_SPEED_REFIN_PLUS_08 = 10,
	RADARSET_SPEED_REFIN_PLUS_10 = 11
}RADARSET_SPEED_REFIN;

typedef enum _RADARSET_ALARM_MODE
{
	RADARSET_ALARM_PICTURE	= 1,
	RADARSET_ALARM_SAFE		= 2
}RADARSET_ALARM_MODE;

typedef enum _RADARSET_ENABLE_SWITCH
{
	RADARSET_ENABLE_ON		= 1,
	RADARSET_ENABLE_OFF		= 2
}RADARSET_ENABLE_SWITCH;

typedef enum _RADARSET_BRIGHTNESS_LEVEL
{
	RADARSET_BRIGHTNESS_DARK = 1,
	RADARSET_BRIGHTNESS_BRIGHTER = 2,
	RADARSET_BRIGHTNESS_BRIGHTEST = 3,
	RADARSET_BRIGHTNESS_AUTO = 4
}RADARSET_BRIGHTNESS_LEVEL;

typedef enum _RADARSET_VOLUME_LEVEL
{
	RADARSET_VOLUME_LEVEL_01 = 1, //Min
	RADARSET_VOLUME_LEVEL_02 = 2,
	RADARSET_VOLUME_LEVEL_03 = 3, 
	RADARSET_VOLUME_LEVEL_04 = 4, 
	RADARSET_VOLUME_LEVEL_05 = 5  //Max 
}RADARSET_VOLUME_LEVEL;


/*===========================================================================
 * Structure define
 *===========================================================================*/

typedef struct _GPSRADARTIME
{
    MMP_UBYTE    iYear;       /**< Years 20xx */
    MMP_UBYTE    iMon;        /**< Months  */
    MMP_UBYTE    iDay;        /**< Day of the month - [1,31] */
    MMP_UBYTE    iHour;       /**< Hours */
    MMP_UBYTE    iMin;        /**< Minutes after the hour - [0,59] */
    MMP_UBYTE    iSec;        /**< Seconds after the minute - [0,59] */
} GPSRADARTIME, *pGPSRadarTime;

typedef struct _GPARADARPACK
{
    GPSRADARTIME sUTC;     			/**< UTC of position */
    MMP_BYTE     chLocated;    		/**< Located or not*/
    double  	 dwLon;        		/**< Longitude in NDEG - +/-[degree][min].[sec/60] */
    MMP_BYTE     chEW;		   		/**< East or West */
    double 		 dwLat;        		/**< Latitude in NDEG - +/-[degree][min].[sec/60] */
    MMP_BYTE     chNS;		   		/**< South ot North */
    double	     dwSpeed;      		/**< Speed over the ground in kilometers/hour */
    double 	     dwDirection;  		/**< Track angle in degrees True 0~359 */
	MMP_UBYTE    ubFixedPointSig;	/**< Fixed point signature*/
	MMP_UBYTE	 ubFixedPointType;	/**< Fixed point Type*/
	MMP_UBYTE	 ubFixedPointSpeedLimit;		/**< Speed Limit of Fixed point*/
	MMP_USHORT   usFixedPointDistance;	/**< Distance to the Fixed point*/
	MMP_USHORT   usMobileRadarSig;	/**< Mobile Radar Signal*/

} GPSRADARPACK;

typedef struct _GMCSATELLITE
{
    MMP_LONG     iId;         /**< Satellite PRN number */
    MMP_LONG     iIn_use;     /**< Used in position fix */
    MMP_LONG     iElv;        /**< Elevation in degrees, 90 maximum */
    MMP_LONG     iAzimuth;    /**< Azimuth, degrees from true north, 000 to 359 */
    MMP_LONG     iSig;        /**< Signal, 00-99 dB */

} GMCSATELLITE;

typedef struct _GMCSATINFO
{
    MMP_LONG     iInuse;      /**< Number of satellites in use (not those in view) */
    MMP_LONG     iInview;     /**< Total number of satellites in view */
    GMCSATELLITE sSat[MAXSATELLITE]; /**< Satellites information */

} GMCSATINFO;

typedef struct _GPSRADARINFO
{	
    GPS_HANDLE  *h_dec;
    double  	 dwLon;        		/**< Longitude in NDEG - +/-[degree][min].[sec/60] */
    double 		 dwLat;        		/**< Latitude in NDEG - +/-[degree][min].[sec/60] */
    double	     dwSpeed;      		/**< Speed over the ground in kilometers/hour */
    double 	     dwDirection;  		/**< Track angle in degrees True 0~359 */
	double  	 dwElv;
    MMP_LONG     iSmask;            
    GPSRADARTIME sUTC;     			/**< UTC of position */
    
    MMP_BYTE     chLocated;    		/**< Located or not*/
    //double  	 dwLon;        		/**< Longitude in NDEG - +/-[degree][min].[sec/60] */
    MMP_BYTE     chEW;		   		/**< East or West */
    //double 	 dwLat;        		/**< Latitude in NDEG - +/-[degree][min].[sec/60] */
    MMP_BYTE     chNS;		   		/**< South ot North */
    //double     dwSpeed;      		/**< Speed over the ground in kilometers/hour */
    //double     dwDirection;  		/**< Track angle in degrees True 0~359 */
	MMP_UBYTE    ubFixedPointSig;	/**< Fixed point signature*/
	MMP_UBYTE	 ubFixedPointType;	/**< Fixed point Type*/
	MMP_UBYTE	 ubFixedPointSpeedLimit;		/**< Speed Limit of Fixed point*/
	MMP_USHORT   usFixedPointDistance;	/**< Distance to the Fixed point*/
	MMP_USHORT   usMobileRadarSig;	/**< Mobile Radar Signal*/
	//double  	 dwElv;
	GMCSATINFO   sSatinfo;     		/**< Satellites information */

} GPSRADARINFO, *pGPSRadarInfo, ST_GPS_INFO;

/*===========================================================================
 * Function Prototype
 *===========================================================================*/
 
MMP_LONG	GPSRadar_Atoi_GMC1030(MMP_BYTE *pStr, MMP_LONG iStr_sz, MMP_LONG iRadix);
double 		GPSRadar_Atof_GMC1030(MMP_BYTE *pStr, MMP_LONG iStr_sz);
MMP_LONG 	GPSRadar_Scanf_GMC1030(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, MMP_BYTE *pFormat, ...);
void 		GPSRadar_InitReceivePath_GMC1030(MMP_BYTE path);
void 		GPSRadar_UnInitPathUART_GMC1030(void);
void 		GPSRadar_ControlPathUART_GMC1030(MMP_BOOL bEnable);
void 		GPSRadar_ControlReceivePath_GMC1030(MMP_BYTE path, MMP_BOOL bEnable);
void 		GPSRadar_GetPack_GMC1030(MMP_BYTE path, MMP_BYTE *bDebugString, MMP_ULONG *ulDebugStringLength);
void 		GPSRadar_ParserInitialize_GMC1030(void);
void 		GPSRadar_ResetContainer_GMC1030(void);
void 		GPSRadar_GMT2LocalTime(GPSRADARTIME *sGMTBackup, GPSRADARTIME *sRes, signed char sbGMTOffset);
MMP_LONG 	GPSRadar_ParseTime_GMC1030(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, GPSRADARTIME *sRes);

MMP_LONG 	GPSRadar_FindTail_GMC1030(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, MMP_LONG *pRes_crc);

void 		GPSRadar_2info_GMC1030(GPSRADARPACK *psPack, GPSRADARINFO *psInfo);
void 		GPSRadar_DubugMessageInfo_GMC1030(GPSRADARINFO *pInfo);
void 		GPSRadar_PaeserMain_GMC1030(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, GPSRADARINFO *pInfo);
void 		GPS_GetGPSStringFromFile(MMP_BYTE *bGPSRadarString, MMP_ULONG *ulGPSRadarStringLength);
MMP_BOOL 	GPSRadar_ValidValue_GMC1030(void);
pGPSRadarInfo GPSRadar_Information(void);
pGPSRadarTime GPSRadar_GetGMTBackupTime(void);


void 		GPSRadar_SetCommand_GMC1030(RADARSET_TYPE ubType, MMP_UBYTE ubValue);
/***********************
	Control Radar API
************************/
void 		GPSRadar_Set_MuteSpeed(MMP_UBYTE ubValue);
void 		GPSRadar_Set_SpeedRefinement(MMP_UBYTE ubValue);
void 		GPSRadar_Set_AlarmMode(MMP_UBYTE ubValue);
void 		GPSRadar_Set_EnableRadar(MMP_UBYTE ubValue);
void 		GPSRadar_Set_Brightness(MMP_UBYTE ubValue);
void 		GPSRadar_Set_Volume(MMP_UBYTE ubValue);

#endif

#endif // _GPSRADAR_GMC1030_H_
