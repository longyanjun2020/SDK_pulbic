////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
/**
* @file mmi_gpssrv.h
*
* Class Id: CLSID_GPSSRV
*
*
*/
/*=============================================================*/
// Include Files
/*=============================================================*/
//#ifdef __GPS_MMI__

#ifndef __MMI_GPSSRV_H__
#define __MMI_GPSSRV_H__

#include "mmi_mae_applet.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_mae_notifier.h"
#include "mmi_log.h"
#include "mmi_mediasrv_common.h"
#include "ABL_Gps.h"
/**
 * IGPSSRV Interfaces
 */
#define INHERIT_IGPSSRV(IName) \
    INHERIT_IHandler(IName)

DEFINE_INTERFACE(IGPSSRV);

#define IGPSSRV_QueryInterface(pICntlr, id, pp, po)GET_FUNCTBL((pICntlr), IGPSSRV)->QueryInterface(pICntlr, id, pp, po)
#define IGPSSRV_HandleEvent(pICntlr, e, p1, p2)GET_FUNCTBL((pICntlr), IGPSSRV)->HandleEvent(pICntlr, e, p1, p2)

#define GPS_SRV_PARSER_MAX_SAT_NUM      32      /* maximun satellite number, sync to ESL_GPS_PARSER_MAX_SAT_NUM */

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum
{
    GPSSRV_FREQ_DEFAULT,       /**< Use default value for GPS TCXO */
    GPSSRV_FREQ_16367600,      /**< GPS TCXO set to 16367600 */
    GPSSRV_FREQ_16369000,      /**< GPS TCXO set to 16369000 */
    GPSSRV_FREQ_NUM,           /**< Number of GPS TCXO frequency type */
} GPSSrvFreq_e;

typedef enum {
    GPSSRV_NMEA_TYPE_GPRMC,    /**< GPRMC */
    GPSSRV_NMEA_TYPE_GPGGA,    /**< GPGGA */
    GPSSRV_NMEA_TYPE_GPGSA,    /**< GPGSA */
    GPSSRV_NMEA_TYPE_GPGSV,    /**< GPGSV */
    GPSSRV_NMEA_TYPE_EM_RESP,  /**< EM response data */
    GPSSRV_NMEA_TYPE_RAW,      /**< RAW NMEA data */
    GPSSRV_NMEA_TYPE_NUM,       /**< Number of NMEA type */
} GPSSrvNmeaType_e;

typedef enum {
     GPS_SRV_INFO_TYPE__NONE = 0x00,
     GPS_SRV_INFO_TYPE__GPRMC = 0x01,
     GPS_SRV_INFO_TYPE__GPGGA = 0x02,
     GPS_SRV_INFO_TYPE__GPGSA = 0x04,
     GPS_SRV_INFO_TYPE__GPGSV = 0x08,
     GPS_SRV_INFO_TYPE__EM_RSP = 0x10,
     GPS_SRV_INFO_TYPE__RAW = 0x20,
     GPS_SRV_INFO_TYPE__ALL = 0x3F,
} GpsSrvNotifyInfoType_e;

typedef enum {
    GPSSRV_IOCTL_ENABLE_GPS_AND_LOG_VBI        = 51,   /**< Enable GPS & log VBI */
    GPSSRV_IOCTL_DISABLE_GPS_AND_STOP_LOG_VBI  = 52,   /**< Disable GPS & stop log VBI */
    GPSSRV_IOCTL_SUSPEND_GPS                   = 53,   /**< Suspend GPS */
    GPSSRV_IOCTL_RESUME_GPS                    = 54,   /**< Resume GPS */
    GPSSRV_IOCTL_ENABLE_VBI_OUTPUT_AND_LOG_VBI_TO_SD = 55,       /**< Enable VBI output and log VBI to SD */
    GPSSRV_IOCTL_DISABLE_VBI_OUTPUT_AND_STOP_LOG_VBI_TO_SD = 56, /**< Disable VBI output and stop log VBI to SD */
    GPSSRV_IOCTL_STOP_LOGGING_VBI_LOG_INTO_SD_CARD = 57,         /**< Stop logging VBI into SD card */
    GPSSRV_IOCTL_ENABLE_ASSERT_LOG             = 41,   /**< Enable assert log */
    GPSSRV_IOCTL_DISABLE_ASSERT_LOG            = 42,   /**< Disable assert log */
    GPSSRV_IOCTL_POWER_SAVING_MODE             = 43,   /**< Power saving mode */
    GPSSRV_IOCTL_CHANGE_TO_6_GPS_CHANNELS      = 31,   /**< Change to 6 GPS channels */
    GPSSRV_IOCTL_CHANGE_TO_9_GPS_CHANNELS      = 32,   /**< Change to 9 GPS channels */
    GPSSRV_IOCTL_CHANGE_TO_12_GPS_CHANNELS     = 33,   /**< Change to 12 GPS channels */
    GPSSRV_IOCTL_CHANGE_TO_16_GPS_CHANNELS     = 34,   /**< Change to 16 GPS channels */
    GPSSRV_IOCTL_COLD_START                    = 1,    /**< Cold start */
    GPSSRV_IOCTL_COLD_START_10_TIMES           = 2,    /**< Cold start 10 times */
    GPSSRV_IOCTL_COLD_START_50_TIMES           = 3,    /**< Cold start 50 times */
    GPSSRV_IOCTL_WARM_START                    = 4,    /**< Warm start */
    GPSSRV_IOCTL_WARM_START_50_TIMES           = 5,    /**< Warm start 50 times */
    GPSSRV_IOCTL_HOT_START                     = 6,    /**< Hot start */
    GPSSRV_IOCTL_HOT_START_100_TIMES           = 7,    /**< Hot start 100 times */
    GPSSRV_IOCTL_GET_BB_VERSION                = 14,   /**< Get BB version */
    GPSSRV_IOCTL_EXTERNAL_CMD_1                = 61,   /**< External cmd 1 */
    GPSSRV_IOCTL_EXTERNAL_CMD_2                = 62,   /**< External cmd 2 */
    GPSSRV_IOCTL_EXTERNAL_CMD_3                = 63,   /**< External cmd 3 */
    GPSSRV_IOCTL_EXTERNAL_CMD_4                = 64,   /**< External cmd 4 */
    GPSSRV_IOCTL_ENABLE_NMEA_TO_SD             = 65,   /**< Enable nmea to SD*/
    GPSSRV_IOCTL_DISABLE_NMEA_TO_SD            = 66,   /**< Disable nmea to SD*/
    GPSSRV_IOCTL_ENABLE_VBI_TO_SD              = 67,   /**< Enable nmea to SD*/
    GPSSRV_IOCTL_DISABLE_VBI_TO_SD             = 68,   /**< Disable nmea to SD*/
    GPSSRV_IOCTL_ENABLE_VBI_OUTPUT             = 69,   /**< Enable nmea to SD*/
    GPSSRV_IOCTL_DISABLE_VBI_OUTPUT            = 70,   /**< Disable nmea to SD*/
} GPSSrvIoctlCmdType_e;

typedef struct {
    u32 nP2;
    u32 nP3;
    u32 nP4;
} GPSSrvChangePSMode_t;

typedef struct {
    bool bEnableVirtualGps;     /**< Decide if run in Virtual GPS mode or not. */
    bool bEnableRecord;         /**< Valid if run in non-Virtual GPS, record data to SD card. */
    bool bEnableLoop;           /**< Valid if run in Virtual GPS, play recorded data looply. */
    bool bEnableLogPort;        /**< Open M3 UART to send GPS log to terminal for online-debug. */
    bool bEnableStoreLog;       /**< Enable to store GPS log to SD card for offline-debug. */
} GPSSrvDbgSetting_t;

typedef enum
{
    GPSSRV_ERR__OK,       /**< Use default value for GPS TCXO */
    GPSSRV_ERR__FAIL,
    GPSSRV_ERR__PARAM_ERROR,        //ESL_GPS_PARAM_ERROR
    GPSSRV_ERR__MEM_ALLOC_ERROR,    //ESL_GPS_MEM_ALLOC_ERROR
    GPSSRV_ERR__REJECT,             //ESL_GPS_REJECT
    GPSSRV_ERR__EOF,
    GPSSRV_ERR__TIMEOUT,
    GPSSRV_ERR__NOT_SUPPORT,
    GPSSRV_ERR__DENY,
    GPSSRV_ERR__NUM,           /**< Number of GPS TCXO frequency type */
} GPSSrvErrCode_e;

/**
* @brief The sturcture defines the satellite information.
*/
typedef struct {
    s32 sSatID;          /**< satellite ID */
    s32 sElevation;      /**< elevation value */
    s32 sAzimuth;        /**< azimuth value */
    s32 sSNR;            /**< signal value */
} GPSSrvNmeaSatviewData_t;

/**
* @brief The sturcture defines the nmea parser data structure for GPRMC.
*/
typedef struct {
    s32 sCount;          /**< GPRMC data count */
    s32 sTime;           /**< time: HHMMSS */
    s8 sStatus;         /**< status: 'A'=valid, 'V'=invalid */
    s32 sLatitude;       /**< latitude position */
    s8 sNorthInd;       /**< Nouth or South, 'N'=north, 'S'=south */
    s32 sLongitude;      /**< longitude position */
    s8 sEastInd;        /**< West or East, 'W'=west, 'E'=east */
    float fSog;            /**< speed over ground, m/sec */
    float fCog;            /**< course over ground, degrees True */
    s32 sDate;           /**< date: YYYYMMDD */
} GPSSrvNmeaGPRMC_t;

/**
* @brief The sturcture defines the nmea parser data structure for GPGGA.
*/
typedef struct {
    s32 sCount;          /**< GPGGS data count */
    float fAltitude;       /**< altidue value */
} GPSSrvNmeaGPGGA_t;

/**
* @brief The sturcture defines the nmea parser data structure for GPGSA.
*/
typedef struct {
    s32 sCount;          /**< GPGSA data count */
    s8 sOpMode;         /**< op mode: 'M'=manual, 'A'=automatic */
    s32 sFixMode;        /**< fix mode: 1=No, 2=2D, 3=3D */
    s32 sSatNum;         /**< satellite number */
    s32 sSatID[GPS_SRV_PARSER_MAX_SAT_NUM]; /**< satellite ID array */
    float fPdop;           /**< positional dilution of precision */
    float fhdop;           /**< horizontal dilution of precision */
    float fVdop;           /**< vertical dilution of precision */
} GPSSrvNmeaGPGSA_t;

/**
* @brief The sturcture defines the nmea parser data structure for GPGSV.
*/
typedef struct {
    s32 sCount;          /**< GPGSV data count */
    s32 sRecordNum;      /**< record number */
    s32 sRecordIndex;    /**< record index */
    s32 sSatNum;         /**< satellte number */
    GPSSrvNmeaSatviewData_t aSatView[GPS_SRV_PARSER_MAX_SAT_NUM]; /**< satellite information */
} GPSSrvNmeaGPGSV_t;

/**
* @brief The sturcture defines the nmea parser data structure for EM RESP.
*/
typedef struct {
    bool bValid;          /**< EM RESP data valid */
    s32 sTime;           /**< avarage time in msecs */
} GPSSrvNmeaEMRESP_t;

/**
* @brief The sturcture defines the data structure for RAW.
*/
typedef struct {
    u8 *pData;           /**< RAW data buffer */
    s32 sDataLength;     /**< data length */
} GPSSrvNmeaRAW_t;

/**
*  @brief The sturcture defines the gps data.
*/
typedef struct {
    GPSSrvNmeaType_e   eType;
    union {
        GPSSrvNmeaGPRMC_t   tGprmc;  /**< GPS GPRMC information response */
        GPSSrvNmeaGPGGA_t   tGpgga;  /**< GPS GPGGA information response */
        GPSSrvNmeaGPGSA_t   tGpgsa;  /**< GPS GPGSA information response */
        GPSSrvNmeaGPGSV_t   tGpgsv;  /**< GPS GPGSV information response */
        GPSSrvNmeaEMRESP_t  tEmresp; /**< GPS EM information response */
        GPSSrvNmeaRAW_t     tRaw;    /**< GPS RAW information response */
    } uData;
} GPSSrvData_t;

/**
*  @brief The sturcture defines the GPS version.
*/
typedef struct {
    u16 nMajor;  /**< GPS BB major version number */
    u16 nMinor;  /**< GPS BB minor version number */
} GPSSrvVersion_t;

/**
 *  @brief The sturcture defines the TTFF test result
 */
typedef struct {
  float fTTFF;                  /**< TTFF time (s) */
  GPSSrvNmeaGPRMC_t   tGprmc;   /**< GPS GPRMC information response */
} GPSSrvTTFFResult_t;


/**
*  @brief The sturcture defines the return information of GPS IOCTL commands.
*/
typedef struct {
    GPSSrvIoctlCmdType_e eIoctlCmd;   /**< GPS IOCTL command */
    union {
        GPSSrvVersion_t     tGPSVersion; /**< GPS BB version */
        GPSSrvTTFFResult_t  tTTFFResult; /**< TTFF test result */
    } uData;
} GPSSrvIoctl_t;

typedef void (*GPSSrvCnfCb)(void *pThis, GPSSrvErrCode_e eErrorCode);
typedef void (*GPSSrvDataCb)(void *pThis, GPSSrvErrCode_e eErrorCode, GPSSrvData_t *pData);
typedef void (*GPSSrvIoctlCb)(void *pThis, GPSSrvErrCode_e eErrorCode, GPSSrvIoctl_t *pData);
typedef void (*GPSSrvDataNotifyCb)(void *pThis, u32 nCusData, GPSSrvNmeaType_e eDataType, GPSSrvData_t *pData);


typedef struct
{
    u32 nSrvInstId;
    u32 nSrvClientInsId;
    u32 nCusData;
    u32 pfnCb;
} GPSSrvCusInfo_t;
/*=============================================================*/
// Variable Declarations
/*=============================================================*/
/*=============================================================*/
// Function Declarations
/*=============================================================*/
MAE_Ret GPSSrvNew(MAE_ClsId nId, void **ppObj);
void GPSSrvOpenSession(IGPSSRV *pIGPSSrv, u32 nSrvClientInstId);
void GPSSrvCloseSession(IGPSSRV *pIGPSSrv, u32 nSrvClientInstId);
MediaSrvErrCode_e GPSSrvOpen(IGPSSRV *pIGPSSrv, u32 nSrvClientInstId, GPSSrvFreq_e eFreq, GPSSrvDbgSetting_t *pDgbSetting, GPSSrvCnfCb pFnCb);
void GPSSrvStart(IGPSSRV *pIGPSSrv, u32 nSrvClientInstId, GPSSrvCnfCb pFnCb);
void GPSSrvStop(IGPSSRV *pIGPSSrv, u32 nSrvClientInstId, GPSSrvCnfCb pFnCb);
MediaSrvErrCode_e GPSSrvClose(IGPSSRV *pIGPSSrv, u32 nSrvClientInstId, GPSSrvCnfCb pFnCb);
MediaSrvErrCode_e GPSSrvReadData(IGPSSRV *pIGPSSrv, u32 nSrvClientInstId, GPSSrvNmeaType_e eType, GPSSrvDataCb pFnCb);
MediaSrvErrCode_e GPSSrvIoctl(IGPSSRV *pIGPSSrv, u32 nSrvClientInstId, GPSSrvIoctlCmdType_e eCmdType, GPSSrvIoctlCb pFnCb);
void GPSSrvChangePSMode(IGPSSRV *pIGPSSrv, u32 nSrvClientInstId, GPSSrvChangePSMode_t *ptMode, GPSSrvCnfCb pFnCb);
void GPSSrvSetInterruptNotifyCb(IGPSSRV *pIGPSSrv, u32 nSrvClientInstId, MediaSrvInterruptNotifyCb pfnGPSSrvCb, u32 nCusData);
MediaSrvErrCode_e GPSSrvSetDataNotifyCb(IGPSSRV *pIGPSSrv, u32 nSrvClientInstId, GPSSrvDataNotifyCb pfnGPSSrvCb, u32 nCusData);
/*=============================================================*/
// Private Function Implementations
/*=============================================================*/
#endif
//#endif

