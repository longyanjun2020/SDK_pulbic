/**
 * @file mmi_mae_gps_types.h
 *
 * @version $Id: mmi_mae_gps_types.h $
 */
#ifndef __MMI_MAE_GPS_TYPES_H__
#define __MMI_MAE_GPS_TYPES_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_clstbl.h"

#define GPS_PARSER_MAX_SAT_NUM      32      /* maximun satellite number */

opaque_enum(MAEGpsCallBackEvent_e_)
{
    MAE_GPS_NONE = -1,
    MAE_GPS_OPEN_CNF = (CLSID_GPS << 16 | 0),
    MAE_GPS_CLOSE_CNF,
    MAE_GPS_GETDATA_CNF,
};

opaque_enum(MAEGpsRetCode_e_)
{
    MAE_GPS_RET_SUCCESS = 0,
    MAE_GPS_RET_FAILURE
};

opaque_enum(MAEGpsAppId_e_)
{
    MAE_GPS_APP_UNKNOWN = -1,
    MAE_GPS_APP_CAMERA = 0,
    MAE_GPS_APP_LBS,
};

opaque_enum(MAEGpsState_e_)
{
    MAE_GPS_UNKNOWN = -1,
    MAE_GPS_SEARCHING = 2, /* = MAE_CAMERA_LOCATION_SEARCH */
    MAE_GPS_FIXED, /* MAE_CAMERA_LOCATION_FIXED */
    MAE_GPS_NO_FIXED,
};

opaque_enum(MAEGpsCmd_e_)
{
    MAE_GPS_NMEA_TYPE_UNKNOWN = -1,        /* unknown data type */
    MAE_GPS_NMEA_TYPE_GPRMC = 0,        /* GPRMC */
    MAE_GPS_NMEA_TYPE_GPGGA,        /* GPGGA */
    MAE_GPS_NMEA_TYPE_GPGSA,        /* GPGSA */
    MAE_GPS_NMEA_TYPE_GPGSV,         /* GPGSV */
    MAE_GPS_NMEA_TYPE_MAX           /* Number of NMEA type */
};

/* defines the satellite information */
struct MAE_NmeaSatviewData_t_
{
  s32            nSatID;        /* satellite ID */
  s32            nElevation;    /* elevation value */
  s32            nAzimuth;      /* azimuth value */
  s32            nSNR;          /* signal value */
};

/* defines the nmea parser data structure */
/* ------ GPRMC ------ */
struct MAE_NmeaGPRMC_t_
{
	s32 nGPRMC_Count;       /* GPRMC data count */
	s32 nGPRMC_Longitude;   /* longitude position */
	s8 nGPRMC_NorS;       /* Nouth or South */
	s32 nGPRMC_Latitude;    /* latitude position */
	s8 nGPRMC_WorE;       /* West or East */
	s32 nGPRMC_Azimuth;     /* azimuth */
	s32 nGPRMC_Date;        /* date: YYYYMMDD */
	s32 nGPRMC_Time;        /* time: HHMMSS */
	float fGPRMC_Speed;       /* speed. m/sec */
    float fGPRMC_Course;     /* course over ground, degrees True */
	s8 nGPRMC_Status;     /* status: A/V */
};

/* ------ GPGGA ------ */
struct MAE_NmeaGPGGA_t_
{
  s32            nGPGGA_Count;       /* GPGGS data count */
  float          fGPGGA_Altitude;    /* altidue value */
};

/* ------ GPGSA ------ */
struct MAE_NmeaGPGSA_t_
{
  s32            nGPGSA_Count;       /* GPGSA data count */
  s32            nGPGSA_FixMode;     /* fix mode */
  float          fGPGSA_Hdop;
  s32            nGPGSA_SatNum;      /* satellite number */
  s32            nGPGSA_SatID[GPS_PARSER_MAX_SAT_NUM];  /* satellite ID array */
};

/* ------ GPGSV ------ */
struct MAE_NmeaGPGSV_t_
{
  s32            nGPGSV_Count;       /* GPGSV data count */
  s32            nGPGSV_RecordNum;   /* record number */
  s32            nGPGSV_RecordIndex; /* record index */
  s32            nGPGSV_SatNum;      /* satellte number */
  MAE_NmeaSatviewData_t tGPSGSV_SatView[GPS_PARSER_MAX_SAT_NUM];   /* satellite information */
};

/**
 *  @brief The sturcture defines the return information of gps information
 */
struct MAEGpsData_t_
{
	union
  	{
  		MAE_NmeaGPRMC_t tNmeaGPRMC; /**< GPS GPRMC information response */
    		MAE_NmeaGPGGA_t tNmeaGPGGA; /**< GPS GPGGA information response */
    		MAE_NmeaGPGSA_t tNmeaGPGSA; /**< GPS GPGSA information response */
    		MAE_NmeaGPGSV_t tNmeaGPGSV; /**< GPS GPGSV information response */
	} param_u;
};

// Callback data definition
struct MAEGpsCallbackData_t_
{
	MAEGpsCallBackEvent_e	eEvtCode;
	MAEGpsRetCode_e			eRetCode;
	MAEGpsData_t			*pGpsData;
};

#endif /* __MMI_MAE_GPS_TYPES_H__ */
