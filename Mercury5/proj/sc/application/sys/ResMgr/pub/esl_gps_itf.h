/**
 *
 * @file    esl_gps_itf.h
 *
 * @brief   This module defines the Enhanced Service Layer interface of GPS serivce
 *
 * @author  Arthur Cheng
 * @version $Id: $
 *
 */
#ifndef __ESL_GPS_ITF_H__
#define __ESL_GPS_ITF_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "vm_types.ht"


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __ESL_GPS_ITF__
#define DefExtern
#else
#define DefExtern extern
#endif

#define ESL_GPS_PARSER_MAX_SAT_NUM      32      /* maximun satellite number */
//#define ESL_GPS_HYDRA_EM_RESP                   /* support Hydra $PMST119 EM response string */


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/
/**
 *  @brief The enumeration defines the return code of the GPS interface.
 */
typedef enum {
  ESL_GPS_OK,                 /**< Function complete successfully */
  ESL_GPS_FAIL,               /**< Function common fail */
  ESL_GPS_PARAM_ERROR,        /**< The input parameter is wrong */
  ESL_GPS_MEM_ALLOC_ERROR,    /**< Can not allocate memory from OS */
  ESL_GPS_REJECT,             /**< Request rejected because of other function's confliction */
  ESL_GPS_EOF,                /**< NMEA string streaming is closed by host side or Hydra side */
  ESL_GPS_TIMEOUT,            /**< Request no response timeout, this error is returned by call back function */
  ESL_GPS_NOT_SUPPORT,        /**< Function is not support */
} esl_GpsErrCode_e;

/**
 * @brief The enumeration defines the nmea data type.
 */
typedef enum {
  ESL_GPS_NMEA_TYPE_GPRMC,    /**< GPRMC */
  ESL_GPS_NMEA_TYPE_GPGGA,    /**< GPGGA */
  ESL_GPS_NMEA_TYPE_GPGSA,    /**< GPGSA */
  ESL_GPS_NMEA_TYPE_GPGSV,    /**< GPGSV */
  ESL_GPS_NMEA_TYPE_EM_RESP,  /**< EM response data */
  ESL_GPS_NMEA_TYPE_RAW,      /**< RAW NMEA data */
  ESL_GPS_NMEA_TYPE_MAX       /**< Number of NMEA type */
} esl_GpsNmeaType_e;

#if 0
/**
 * @brief The enumeration defines the notification bitmap.
 */
typedef enum {
  ESL_GPS_NOTIFY_BIT_NONE     = 0x00,     /**< None */
  ESL_GPS_NOTIFY_BIT_GPRMC    = 0x01,     /**< GPRMC */
  ESL_GPS_NOTIFY_BIT_GPGGA    = 0x02,     /**< GPGGA */
  ESL_GPS_NOTIFY_BIT_GPGSA    = 0x04,     /**< GPGSA */
  ESL_GPS_NOTIFY_BIT_GPGSV    = 0x08,     /**< GPGSV */
  ESL_GPS_NOTIFY_BIT_EM_RESP  = 0x10,     /**< EM response data */
  ESL_GPS_NOTIFY_BIT_RAW      = 0x20,     /**< RAW NMEA data */
  ESL_GPS_NOTIFY_BIT_ALL      = 0x3F,     /**< All */
} esl_GpsNotifyBitmap_e;
#endif

/**
 * @brief The enumeration defines the GPS Ioctl command code.
 */
typedef enum {
  ESL_GPS_IOCTL_ENABLE_GPS_AND_LOG_VBI        = 51,   /**< Enable GPS & log VBI */
  ESL_GPS_IOCTL_DISABLE_GPS_AND_STOP_LOG_VBI  = 52,   /**< Disable GPS & stop log VBI */
  ESL_GPS_IOCTL_SUSPEND_GPS                   = 53,   /**< Suspend GPS */
  ESL_GPS_IOCTL_RESUME_GPS                    = 54,   /**< Resume GPS */
  ESL_GPS_IOCTL_ENABLE_VBI_OUTPUT_AND_LOG_VBI_TO_SD = 55,       /**< Enable VBI output and log VBI to SD */
  ESL_GPS_IOCTL_DISABLE_VBI_OUTPUT_AND_STOP_LOG_VBI_TO_SD = 56, /**< Disable VBI output and stop log VBI to SD */
  ESL_GPS_IOCTL_STOP_LOGGING_VBI_LOG_INTO_SD_CARD = 57,         /**< Stop logging VBI into SD card */
  ESL_GPS_IOCTL_ENABLE_ASSERT_LOG             = 41,   /**< Enable assert log */
  ESL_GPS_IOCTL_DISABLE_ASSERT_LOG            = 42,   /**< Disable assert log */
  ESL_GPS_IOCTL_POWER_SAVING_MODE             = 43,   /**< Power saving mode */
  ESL_GPS_IOCTL_CHANGE_TO_6_GPS_CHANNELS      = 31,   /**< Change to 6 GPS channels */
  ESL_GPS_IOCTL_CHANGE_TO_9_GPS_CHANNELS      = 32,   /**< Change to 9 GPS channels */
  ESL_GPS_IOCTL_CHANGE_TO_12_GPS_CHANNELS     = 33,   /**< Change to 12 GPS channels */
  ESL_GPS_IOCTL_CHANGE_TO_16_GPS_CHANNELS     = 34,   /**< Change to 16 GPS channels */
  ESL_GPS_IOCTL_COLD_START                    = 1,    /**< Cold start */
  ESL_GPS_IOCTL_COLD_START_10_TIMES           = 2,    /**< Cold start 10 times */
  ESL_GPS_IOCTL_COLD_START_50_TIMES           = 3,    /**< Cold start 50 times */
  ESL_GPS_IOCTL_WARM_START                    = 4,    /**< Warm start */
  ESL_GPS_IOCTL_WARM_START_50_TIMES           = 5,    /**< Warm start 50 times */
  ESL_GPS_IOCTL_HOT_START                     = 6,    /**< Hot start */
  ESL_GPS_IOCTL_HOT_START_100_TIMES           = 7,    /**< Hot start 100 times */
  ESL_GPS_IOCTL_GET_BB_VERSION                = 14,   /**< Get BB version */
  ESL_GPS_IOCTL_EXTERNAL_CMD_1                = 61,   /**< External cmd 1 */
  ESL_GPS_IOCTL_EXTERNAL_CMD_2                = 62,   /**< External cmd 2 */
  ESL_GPS_IOCTL_EXTERNAL_CMD_3                = 63,   /**< External cmd 3 */
  ESL_GPS_IOCTL_EXTERNAL_CMD_4                = 64,   /**< External cmd 4 */
  ESL_GPS_IOCTL_ENABLE_NMEA_TO_SD             = 65,   /**< Enable nmea to SD*/
  ESL_GPS_IOCTL_DISABLE_NMEA_TO_SD            = 66,   /**< Disable nmea to SD*/
  ESL_GPS_IOCTL_ENABLE_VBI_TO_SD              = 67,   /**< Enable nmea to SD*/
  ESL_GPS_IOCTL_DISABLE_VBI_TO_SD             = 68,   /**< Disable nmea to SD*/
  ESL_GPS_IOCTL_ENABLE_VBI_OUTPUT             = 69,   /**< Enable nmea to SD*/
  ESL_GPS_IOCTL_DISABLE_VBI_OUTPUT            = 70,   /**< Disable nmea to SD*/
} esl_GpsIoctlCmdType_e;

/**
 * @brief The sturcture defines the satellite information.
 */
typedef struct {
  s32           satID;          /**< satellite ID */
  s32           elevation;      /**< elevation value */
  s32           azimuth;        /**< azimuth value */
  s32           SNR;            /**< signal value */
} esl_NmeaSatviewData_t;

/**
 * @brief The sturcture defines the nmea parser data structure for GPRMC.
 */
typedef struct {
  s32           count;          /**< GPRMC data count */
  s32           time;           /**< time: HHMMSS */
  s8            status;         /**< status: 'A'=valid, 'V'=invalid */
  s32           latitude;       /**< latitude position */
  s8            northInd;       /**< Nouth or South, 'N'=north, 'S'=south */
  s32           longitude;      /**< longitude position */
  s8            eastInd;        /**< West or East, 'W'=west, 'E'=east */
  float         sog;            /**< speed over ground, m/sec */
  float         cog;            /**< course over ground, degrees True */
  s32           date;           /**< date: YYYYMMDD */
} esl_NmeaGPRMC_t;

/**
 * @brief The sturcture defines the nmea parser data structure for GPGGA.
 */
typedef struct {
  s32           count;          /**< GPGGS data count */
  float         altitude;       /**< altidue value */
} esl_NmeaGPGGA_t;

/**
 * @brief The sturcture defines the nmea parser data structure for GPGSA.
 */
typedef struct {
  s32           count;          /**< GPGSA data count */
  s8            opMode;         /**< op mode: 'M'=manual, 'A'=automatic */
  s32           fixMode;        /**< fix mode: 1=No, 2=2D, 3=3D */
  s32           satNum;         /**< satellite number */
  s32           satID[ESL_GPS_PARSER_MAX_SAT_NUM]; /**< satellite ID array */
  float         pdop;           /**< positional dilution of precision */
  float         hdop;           /**< horizontal dilution of precision */
  float         vdop;           /**< vertical dilution of precision */
} esl_NmeaGPGSA_t;

/**
 * @brief The sturcture defines the nmea parser data structure for GPGSV.
 */
typedef struct {
  s32           count;          /**< GPGSV data count */
  s32           recordNum;      /**< record number */
  s32           recordIndex;    /**< record index */
  s32           satNum;         /**< satellte number */
  esl_NmeaSatviewData_t satView[ESL_GPS_PARSER_MAX_SAT_NUM]; /**< satellite information */
} esl_NmeaGPGSV_t;

/**
 * @brief The sturcture defines the nmea parser data structure for EM RESP.
 */
typedef struct {
  bool          valid;          /**< EM RESP data valid */
  s32           time;           /**< avarage time in msecs */
} esl_NmeaEMRESP_t;

/**
 * @brief The sturcture defines the data structure for RAW.
 */
typedef struct {
  u8           *data;           /**< RAW data buffer */
  s32           dataLength;     /**< data length */
} esl_NmeaRAW_t;

/**
 *  @brief The sturcture defines the gps data.
 */
typedef struct {
  esl_GpsNmeaType_e   type;
  union {
    esl_NmeaGPRMC_t   gprmc;  /**< GPS GPRMC information response */
    esl_NmeaGPGGA_t   gpgga;  /**< GPS GPGGA information response */
    esl_NmeaGPGSA_t   gpgsa;  /**< GPS GPGSA information response */
    esl_NmeaGPGSV_t   gpgsv;  /**< GPS GPGSV information response */
    esl_NmeaEMRESP_t  emresp; /**< GPS EM information response */
    esl_NmeaRAW_t     raw;    /**< GPS RAW information response */
  } data;
} esl_GpsData_t;

/**
 *  @brief The sturcture defines the GPS version.
 */
typedef struct {
  u16 major;  /**< GPS BB major version number */
  u16 minor;  /**< GPS BB minor version number */
} esl_GpsVersion_t;


/**
 *  @brief The sturcture defines the TTFF test result
 */
typedef struct {
  float             fTTFF;   /**< TTFF time (s) */
  esl_NmeaGPRMC_t   gprmc;   /**< GPS GPRMC information response */
} esl_TTFFResult_t;


/**
 *  @brief The sturcture defines the return information of GPS IOCTL commands.
 */
typedef struct {
  esl_GpsIoctlCmdType_e ioctlCmd;   /**< GPS IOCTL command */
  union {
    esl_GpsVersion_t    gpsVersion; /**< GPS BB version */
    esl_TTFFResult_t    tTTFFResult;/**< use for cold/warm/hot start*/
  } data;
} esl_GpsIoctl_t;

/**
 *  @brief The sturcture defines the return information of GPS.
 */
typedef struct {
  esl_GpsErrCode_e  errCode;    /**< Callback result */
  union {
    esl_GpsData_t   gpsData;    /**< GPS data */
    esl_GpsIoctl_t  gpsIoctl;   /**< GPS Ioctl result */
  } data;
} esl_GpsInfo_t;

#if 0
/**
 * @brief Call back function, Application needs to provide the function entry
 *
 * @param senderID      : Sender task ID
 * @param userValue     : Reference value for indicating different sender in same task or check msg response.
 * @param pGpsInfo      : Callback information return by GPS multi-media driver
 *
 * @return None
 */
typedef void (*esl_GpsCb)(u16 senderID, u32 userValue, esl_GpsInfo_t *pGpsInfo);
#endif

/**
 * @brief Notification call back function, Application needs to provide the function entry
 *
 * @param senderID      : Sender task ID
 * @param userValue     : Reference value for indicating different sender in same task or check msg response.
 * @param pGpsInfo      : Callback information return by GPS multi-media driver
 *
 * @return None
 */
typedef void (*esl_GpsNotifyCb)(u16 senderID, u32 userValue, esl_GpsInfo_t *pGpsInfo);

#if 0
/**
 * @brief The GPS service call back function structure definition
 */
typedef struct {
  u16       senderID;         /**< Sender task ID */
  u32       userValue;        /**< Reference value for indicating different sender in same task or check msg response. */
  esl_GpsCb pfnCb;            /**< Call back function that called by Media task after process finished. */
} esl_GpsCb_t;
#endif

/**
 * @brief The GPS service notification call back function structure definition
 */
typedef struct {
  u16             senderID;     /**< Sender task ID */
  u32             userValue;    /**< Reference value for indicating different sender in same task or check msg response. */
  esl_GpsNotifyCb pfnNotifyCb;  /**< Notification call back function that called by Media task. */
} esl_GpsNotifyCb_t;

/**
 * @brief The GPS frequency setting for open request.
 */
typedef enum {
  ESL_GPS_FREQ_DEFAULT,       /**< Use default value for GPS TCXO */
  ESL_GPS_FREQ_16367600,      /**< GPS TCXO set to 16367600 */
  ESL_GPS_FREQ_16369000,      /**< GPS TCXO set to 16369000 */
  ESL_GPS_FREQ_MAX,           /**< Number of GPS TCXO frequency type */
} esl_GpsFreq_e;

/**
 * @brief The GPS debug setting for open request.
 */
typedef struct {
  bool  enableVirtualGps;     /**< Decide if run in Virtual GPS mode or not. */
  bool  enableRecord;         /**< Valid if run in non-Virtual GPS, record data to SD card. */
  bool  enableLoop;           /**< Valid if run in Virtual GPS, play recorded data looply. */
  bool  enableLogPort;        /**< Open M3 UART to send GPS log to terminal for online-debug. */
  bool  enableStoreLog;       /**< Enable to store GPS log to SD card for offline-debug. */
} esl_GpsDbgSetting_t;

/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/

#if 0
/**
 * @brief Open the designate GPS device
 *
 * @param freq                          : Frequency of GPS chip
 * @param enableRecord                  : Enable GPS record data to SD card for future using
 * @param enableLogPort                 : Enable GPS debug message from M3 UART port (Debugging)
 * @param enableStoreLog                : Enable GPS debug message stored to SD card directly (Debugging)
 * @param pGpsCb                        : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @return ESL_GPS_OK                   : initial request success
 * @return ESL_GPS_FAIL                 : initial request fail
 * @return ESL_GPS_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_GPS_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_GPS_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_GPS_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_GPS_TIMEOUT              : Request no response timeout, this error is returned by call back function
 * @retval ESL_GPS_NOT_SUPPORT          : This function is not supported in current configuration
 */
esl_GpsErrCode_e esl_GpsOpenReq(esl_GpsFreq_e freq, esl_GpsDbgSetting_t *pDbgSetting, esl_GpsCb_t *pGpsCb);


/**
 * @brief Start receiving data from GPS device
 *
 * @param pGpsCb                        : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @return ESL_GPS_OK                   : Function start request success
 * @return ESL_GPS_FAIL                 : Function start request fail
 * @return ESL_GPS_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_GPS_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_GPS_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_GPS_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_GPS_TIMEOUT              : Request no response timeout, this error is returned by call back function
 * @retval ESL_GPS_NOT_SUPPORT          : This function is not supported in current configuration
 */
esl_GpsErrCode_e esl_GpsStartReq(esl_GpsCb_t *pGpsCb);


/**
 * @brief Stop receiving data from GPS device
 *
 * @param pGpsCb                        : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @return ESL_GPS_OK                   : Function stop request success
 * @return ESL_GPS_FAIL                 : Function stop request fail
 * @return ESL_GPS_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_GPS_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_GPS_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_GPS_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_GPS_TIMEOUT              : Request no response timeout, this error is returned by call back function
 * @retval ESL_GPS_NOT_SUPPORT          : This function is not supported in current configuration
 */
esl_GpsErrCode_e esl_GpsStopReq(esl_GpsCb_t *pGpsCb);


/**
 * @brief Close the designate GPS device
 *
 * @param pGpsCb                        : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @return ESL_GPS_OK                   : Function close request success
 * @return ESL_GPS_FAIL                 : Function close request fail
 * @return ESL_GPS_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_GPS_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_GPS_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_GPS_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_GPS_TIMEOUT              : Request no response timeout, this error is returned by call back function
 * @retval ESL_GPS_NOT_SUPPORT          : This function is not supported in current configuration
 */
esl_GpsErrCode_e esl_GpsCloseReq(esl_GpsCb_t *pGpsCb);


/**
 * @brief Register gps notification
 *
 * @param gpsNotifyBitmap               : The bitmap of types that client wants to receive
 * @param pGpsNotifyCb                  : The notification callback structure pointer
 * @param pGpsCb                        : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @return ESL_GPS_OK                   : Function register request success
 * @return ESL_GPS_FAIL                 : Function register request fail
 * @return ESL_GPS_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_GPS_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_GPS_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_GPS_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_GPS_TIMEOUT              : Request no response timeout, this error is returned by call back function
 * @retval ESL_GPS_NOT_SUPPORT          : This function is not supported in current configuration
 */
esl_GpsErrCode_e esl_GpsRegNotify(esl_GpsNotifyBitmap_e gpsNotifyBitmap, esl_GpsNotifyCb_t *pGpsNotifyCb, esl_GpsCb_t *pGpsCb);


/**
 * @brief Read latest data for specific NMEA type
 *
 * @param nmeaType                      : NMEA type to request
 * @param pGpsCb                        : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @retval ESL_GPS_OK                   : Function read request success
 * @retval ESL_GPS_FAIL                 : Function read request fail
 * @retval ESL_GPS_PARAM_ERROR          : Incorrect parameter setting
 * @retval ESL_GPS_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @retval ESL_GPS_REJECT               : Request rejected becuase of other function's confliction
 * @retval ESL_GPS_ABORT                : Request aborted becuase of incorrect sequence
 * @retval ESL_GPS_TIMEOUT              : Request no response timeout, this error is returned by call back function
 * @retval ESL_GPS_NOT_SUPPORT          : This function is not supported in current configuration
 */
esl_GpsErrCode_e esl_GpsReadDataReq(esl_GpsNmeaType_e nmeaType, esl_GpsCb_t *pGpsCb);


/**
 * @brief Send IOCTL command request
 *
 * @param ioctlCmdType                  : IOCTL command Id
 * @param pGpsCb                        : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @retval ESL_GPS_OK                   : Ioctl request success
 * @retval ESL_GPS_FAIL                 : Ioctl request fail
 * @retval ESL_GPS_PARAM_ERROR          : Incorrect parameter setting
 * @retval ESL_GPS_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @retval ESL_GPS_REJECT               : Request rejected becuase of other function's confliction
 * @retval ESL_GPS_ABORT                : Request aborted becuase of incorrect sequence
 * @retval ESL_GPS_TIMEOUT              : Request no response timeout, this error is returned by call back function
 * @retval ESL_GPS_NOT_SUPPORT          : This function is not supported in current configuration
 */
esl_GpsErrCode_e esl_GpsIoctlReq(esl_GpsIoctlCmdType_e ioctlCmdType, esl_GpsCb_t *pGpsCb);


/**
 * @brief Change power saving mode request
 *
 * @param p2                            :
 * @param p3                            :
 * @param p4                            :
 * @param pGpsCb                        : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @retval ESL_GPS_OK                   : Change power saving mode request success
 * @retval ESL_GPS_FAIL                 : Change power saving mode request fail
 * @retval ESL_GPS_PARAM_ERROR          : Incorrect parameter setting
 * @retval ESL_GPS_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @retval ESL_GPS_REJECT               : Request rejected becuase of other function's confliction
 * @retval ESL_GPS_ABORT                : Request aborted becuase of incorrect sequence
 * @retval ESL_GPS_TIMEOUT              : Request no response timeout, this error is returned by call back function
 * @retval ESL_GPS_NOT_SUPPORT          : This function is not supported in current configuration
 */
esl_GpsErrCode_e esl_GpsChangePSModeReq(u32 p2, u32 p3, u32 p4, esl_GpsCb_t *pGpsCb);
#endif

#endif /* __ESL_GPS_ITF_H__ */

