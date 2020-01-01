/**
 * @file ven_gps.h
 *
 * This file defines the GPS API
 *
 * @version $Id: ven_gps.h 45468 2009-11-13 05:13:00Z Mobile_CM $
 *
 */

#ifndef __VEN_GPS_H_
#define __VEN_GPS_H_


#include "ven_sdk.h"

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/

#define VEN_GPS_MAX_SAT_NUM     12  ///< maximun satellite number

/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/
enum
{
    VEN_GPS_RET_SUCCESS,        ///< Function complete successfully
    VEN_GPS_RET_FAIL,           ///< Function common fail
    VEN_GPS_RET_BAD_PARAM,      ///< The input parameter is wrong
    VEN_GPS_RET_REJECT,         ///< Request rejected because of other function's confliction
    VEN_GPS_RET_EOF,            ///< NMEA string streaming is closed by host side or Hydra side
    VEN_GPS_RET_TIMEOUT,        ///< Request no response timeout
    VEN_GPS_RET_NOT_SUPPORT,    ///< Function is not support
};
typedef u8 ven_gps_ret_t;

enum
{
    VEN_GPS_NMEA_TYPE_GPRMC,    ///< GPRMC
    VEN_GPS_NMEA_TYPE_GPGGA,    ///< GPGGA
    VEN_GPS_NMEA_TYPE_GPGSA,    ///< GPGSA
    VEN_GPS_NMEA_TYPE_GPGSV,    ///< GPGSV
    VEN_GPS_NMEA_TYPE_RAW,      ///< NMEA string raw data

    VEN_GPS_NMEA_TYPE_MAX,      ///< Number of NMEA type
};
typedef u8 ven_gpsNmeaType_t;

enum
{
    VEN_GPS_NMEA_BIT_NONE  = 0x00,  ///< None
    VEN_GPS_NMEA_BIT_GPRMC = 0x01,  ///< GPRMC
    VEN_GPS_NMEA_BIT_GPGGA = 0x02,  ///< GPGGA
    VEN_GPS_NMEA_BIT_GPGSA = 0x04,  ///< GPGSA
    VEN_GPS_NMEA_BIT_GPGSV = 0x08,  ///< GPGSV
    VEN_GPS_NMEA_BIT_RAW   = 0x20,  ///< NMEA string raw data
    VEN_GPS_NMEA_BIT_ALL   = 0x3F,  ///< All
};
typedef u8 ven_gpsNmeaBitmap_t;

typedef struct
{
    bool bStoreLog;             ///< TRUE for storing GPS log to SD card for offline-debug
} ven_gps_setting_t;

///< The sturcture defines the satellite information.
typedef struct
{
    s32           satID;          ///< satellite ID
    s32           elevation;      ///< elevation value
    s32           azimuth;        ///< azimuth value
    s32           SNR;            ///< signal value
} ven_gpsNmeaSatviewData_t;

///< The sturcture defines the nmea parser data structure for GPRMC.
typedef struct
{
    s32           count;          ///< GPRMC data count
    s32           time;           ///< time: HHMMSS
    s8            status;         ///< status: 'A'=valid, 'V'=invalid
    s32           latitude;       ///< latitude position
    s8            northInd;       ///< Nouth or South, 'N'=north, 'S'=south
    s32           longitude;      ///< longitude position
    s8            eastInd;        ///< West or East, 'W'=west, 'E'=east
    float         sog;            ///< speed over ground, m/sec
    float         cog;            ///< course over ground, degrees
    s32           date;           ///< date: YYYYMMDD
} ven_gpsNmeaGPRMC_t;

///< The sturcture defines the nmea parser data structure for GPGGA.
typedef struct
{
    s32           count;          ///< GPGGS data count
    float         altitude;       ///< altidue value
} ven_gpsNmeaGPGGA_t;

///< The sturcture defines the nmea parser data structure for GPGSA.
typedef struct
{
    s32           count;                       ///< GPGSA data count
    s8            opMode;                      ///< op mode: 'M'=manual, 'A'=automatic
    s32           fixMode;                     ///< fix mode: 1=No, 2=2D, 3=3D
    s32           satNum;                      ///< satellite number
    s32           satID[VEN_GPS_MAX_SAT_NUM];  ///< satellite ID array
    float         pdop;                        ///< positional dilution of precision
    float         hdop;                        ///< horizontal dilution of precision
    float         vdop;                        ///< vertical dilution of precision
} ven_gpsNmeaGPGSA_t;

///< The sturcture defines the nmea parser data structure for GPGSV.
typedef struct
{
    s32           count;                                      ///< GPGSV data count
    s32           recordNum;                                  ///< record number
    s32           recordIndex;                                ///< record index
    s32           satNum;                                     ///< satellte number
    ven_gpsNmeaSatviewData_t satView[VEN_GPS_MAX_SAT_NUM];    ///< satellite information
} ven_gpsNmeaGPGSV_t;

///< The sturcture defines the nmea parser data structure for NMEA string raw data.
typedef struct
{
    u8 *pNMEAStr;   ///< NMEA string without NULL terminate
    u8   strLen;    ///< Character length of NMEA string
} ven_gpsNmeaRaw_t;

typedef struct
{
    ven_gpsNmeaType_t   type;
    union
    {
        ven_gpsNmeaGPRMC_t   gprmc;  ///< GPS GPRMC information response
        ven_gpsNmeaGPGGA_t   gpgga;  ///< GPS GPGGA information response
        ven_gpsNmeaGPGSA_t   gpgsa;  ///< GPS GPGSA information response
        ven_gpsNmeaGPGSV_t   gpgsv;  ///< GPS GPGSV information response
        ven_gpsNmeaRaw_t     raw;    ///< GPS NMEA raw data
    } data;
} ven_gpsData_t;

///< Callback function definition
typedef void (*ven_gpsDataCbFuncPtr_t)(ven_gpsData_t *pGpsData);

/*--------------------------------------------------------------------------*/
/* Public Function Definition                                               */
/*--------------------------------------------------------------------------*/

/**
 * ven_gpsOpen
 * @brief  Open GPS device and get a handle
 *
 * @param  pGpsHandle   [out]Pointer to store GPS handle
 *
 * @param  pGpsSetting  [in]Pointer to GPS setting
 *
 * @param  ptVenReq     [in]The pointer of vendor request data.
 *                          This api will not keep the pointer and will not free the memory.
 *                          It is up to the user to free the memory allocated for the vendor request data.
 *
 * @retval VEN_GPS_RET_SUCCESS if success
 *         VEN_GPS_RET_FAIL if failed
 *         VEN_GPS_RET_BAD_PARAM if the input handle or parameter is wrong
 */
ven_gps_ret_t ven_gpsOpen(u32 *pGpsHandle, ven_gps_setting_t *pGpsSetting, ven_req_data_t *ptVenReq);

/**
 * ven_gpsClose
 * @brief  Close GPS device with the given GPS handle
 *
 * @param  gpsHandle    [in]GPS handle
 *
 * @param  ptVenReq     [in]The pointer of vendor request data.
 *                          This api will not keep the pointer and will not free the memory.
 *                          It is up to the user to free the memory allocated for the vendor request data.
 *
 * @retval VEN_GPS_RET_SUCCESS if success
 *         VEN_GPS_RET_FAIL if failed
 *         VEN_GPS_RET_BAD_PARAM if the input handle or parameter is wrong
 */
ven_gps_ret_t ven_gpsClose(u32 gpsHandle, ven_req_data_t *ptVenReq);

/**
 * ven_gpsGetData
 * @brief Get latest data for specific NMEA type
 *
 * @param  gpsHandle    [in]GPS handle
 *
 * @param  nmeaType     [in]NMEA type to request (VEN_GPS_NMEA_TYPE_RAW is not supported now)
 *
 * @param  nmeaType     [out]Output GPS data

 * @param  ptVenReq     [in]The pointer of vendor request data.
 *                          This api will not keep the pointer and will not free the memory.
 *                          It is up to the user to free the memory allocated for the vendor request data.
 *
 * @retval VEN_GPS_RET_SUCCESS if success
 *         VEN_GPS_RET_FAIL if failed
 *         VEN_GPS_RET_BAD_PARAM if the input handle or parameter is wrong
 *
 */
ven_gps_ret_t ven_gpsGetData(u32 gpsHandle, ven_gpsNmeaType_t nmeaType, ven_gpsData_t *pData, ven_req_data_t *ptVenReq);

/**
 * ven_gpsRegDataCb
 * @brief Register gps notification
 *
 * @param  gpsHandle    [in]GPS handle
 *
 * @param  nmeaBitmap   [in]The bitmap of types that client wants to receive
 *
 * @param  pFnCb        [in]The pointer of notification callback structure
 *
 * @param  ptVenReq     [in]The pointer of vendor request data.
 *                          This api will not keep the pointer and will not free the memory.
 *                          It is up to the user to free the memory allocated for the vendor request data.
 *
 * @retval VEN_GPS_RET_SUCCESS if success
 *         VEN_GPS_RET_FAIL if failed
 *         VEN_GPS_RET_BAD_PARAM if the input handle or parameter is wrong
 *
 */
ven_gps_ret_t ven_gpsRegDataCb(u32 gpsHandle, ven_gpsNmeaBitmap_t nmeaBitmap, ven_gpsDataCbFuncPtr_t pFnCb, ven_req_data_t *ptVenReq);

#endif // __VEN_GPS_H_
