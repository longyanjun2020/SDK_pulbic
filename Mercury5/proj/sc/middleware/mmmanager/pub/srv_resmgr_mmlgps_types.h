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
* @file    srv_resmgr_mmlgps_types.h
* @version
* @brief
*
*/

#ifndef __SRV_RESMGR_MMLGPS_TYPES_H__
#define __SRV_RESMGR_MMLGPS_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup MMLayerGps GPS
    Global Position System (GPS)
    @{
*/

/** @} */

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

/*=============================================================*/
// Include files
/*=============================================================*/
#include "srv_resmgr_mml_forward.h"
#include "vm_types.ht"
#include "esl_gps_itf.h"
#include "srv_resmgr_mmlcommon_types.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/** @ingroup    MMLayerGps
    @brief      Use case IDs
*/
opaque_enum(MmlUseCaseGpsId_e_)
{
    /* Gps Init */
    MML_UCID_GPS_INIT_BASE = MML_GET_UCID_INIT_BASE(MML_UCGID_GPS),
    MML_UCID_GPS_REG_NOTIFY_CALLBACK = MML_UCID_GPS_INIT_BASE,             ///< 000A0000 = Reg notify callback
    MML_UCID_GPS_UNREG_NOTIFY_CALLBACK,                                    ///< 000A0001 = Unreg notify callback
    MML_UCID_GPS_INIT_CATEGORY,

    /* Gps Get */
    MML_UCID_GPS_GET_BASE = MML_GET_UCID_GET_BASE(MML_UCGID_GPS),
    MML_UCID_GPS_READ_GPS_DATA = MML_UCID_GPS_GET_BASE,                    ///< 000A0100 = Read GPS data
    MML_UCID_GPS_GET_CATEGORY,

    /* Gps Set */
    MML_UCID_GPS_SET_BASE = MML_GET_UCID_SET_BASE(MML_UCGID_GPS),
    MML_UCID_GPS_SET_CATEGORY,

    /* Gps Execute */
    MML_UCID_GPS_EXECUTE_BASE = MML_GET_UCID_EXE_BASE(MML_UCGID_GPS),
    MML_UCID_GPS_OPEN_GPS = MML_UCID_GPS_EXECUTE_BASE,                     ///< 000A0300 = Open GPS
    MML_UCID_GPS_CLOSE_GPS,                                                ///< 000A0301 = Close GPS
    MML_UCID_GPS_START_GPS,                                                ///< 000A0302 = Start GPS
    MML_UCID_GPS_STOP_GPS,                                                 ///< 000A0303 = Close GPS
    MML_UCID_GPS_IO_CONTROL_GPS,                                           ///< 000A0304 = IO control
    MML_UCID_GPS_EXECUTE_CATEGORY,

    /* Force ID to be at least 32-bits */
    MML_UCID_GPS_FORCE_U32 = 0x7FFFFFFF
};

/** @ingroup    MMLayerGps
    @brief      Response results
*/
typedef enum
{
    /* Common */
    GPS_ERROR_SUCCESS = 0,
    GPS_ERROR_FAIL,
    GPS_ERROR_PARAMETER_INVALID,
    GPS_ERROR_STATE_CHANGE,
    GPS_ERROR_ACCEPT,
    GPS_ERROR_IGNORE,
    GPS_ERROR_REJECT,
    GPS_ERROR_MEMORY_FAILURE,
    /* */
    GPS_ERROR_NUM
} MmlGpsResult_e;

/** @ingroup    MMLayerGps
    @brief      States
*/
typedef enum
{
    /* GPS */
    GPS_STATE_CLOSED = 0,
    GPS_STATE_OPENED,
    GPS_STATE_RUNNING,
    /* */
    GPS_STATE_DONTCARE,
    GPS_STATE_NUM
} MmlGpsState_e;

/** @ingroup    MMLayerGps
    @brief      Events
*/
typedef enum
{
    /* Common */
    GPS_EVENT_STATE_CHANGE = MML_GET_UCGEVENT_BASE(MML_UCGID_GPS),
    GPS_EVENT_RUNTIME_ERROR,
    /* GPS */
    GPS_EVENT_GPS_DATA_UPDATE,
    /* */
    GPS_EVENT_DONTCARE,
    GPS_EVENT_ALL,
    GPS_EVENT_NUM
} MmlGpsEvent_e;

/** @ingroup    MMLayerGps
    @brief      GPS frequencies (ESL legacy)
*/
typedef         esl_GpsFreq_e         MmlGpsFrequency_e;

/** @ingroup    MMLayerGps
    @brief      NMEA data types (ESL legacy)
*/
typedef         esl_GpsNmeaType_e     MmlGpsNmeaDataType_e;

/** @ingroup    MMLayerGps
    @brief      NMEA data (ESL legacy)
*/
typedef         esl_GpsData_t         MmlGpsNmeaData_t;

/** @ingroup    MMLayerGps
    @brief      GPS IOCTL command types (ESL legacy)
*/
typedef         esl_GpsIoctlCmdType_e MmlGpsIoControlType_e;

/** @ingroup    MMLayerGps
    @brief      Response data of GPS IOCTL commands (ESL legacy)
*/
typedef         esl_GpsIoctl_t        MmlGpsIoControlResult_t;

/** @ingroup    MMLayerGps
    @brief      State change info
*/
typedef	struct
{
    MmlGpsState_e    eState;    ///< The new state after the transition
    MmlGpsEvent_e    eCause;    ///< The cause of state change, if any
} MmlGpsStateChange_t;

/** @ingroup    MMLayerGps
    @brief      Notification payload
*/
typedef struct
{
    MmlGpsEvent_e            eEvent;    ///< Specify the event you want to notify

    /// union of MmlGpsNotify_t parameters
    union
    {
        MmlGpsNmeaData_t                 tNmeaData;       ///< Used with GPS_EVENT_GPS_DATA_UPDATE event
        MmlGpsStateChange_t              tStateChange;    ///< Used with GPS_EVENT_STATE_CHANGE event
        MmlGpsResult_e                   eErrCode;        ///< Used with GPS_EVENT_RUNTIME_ERROR event
	} uParam;
} MmlGpsNotify_t;

/** @ingroup    MMLayerGps
    @brief      Notification callback prototype
    @param      nSenderID        Sender's mailbox ID
    @param      nUserValue       Interface self-reference
    @param      pGpsNotify       Pointer to the accompanying notification payload
*/
typedef void (*PfnMmlGpsNotifyCallback)(u16 nSenderID, u32 nUserValue, MmlGpsNotify_t *pGpsNotify);

/** @ingroup    MMLayerGps
    @brief      Notification callback registration structure
*/
typedef struct
{
    u16                            nSenderID;            ///< Sender's mailbox ID
    u32                            nUserValue;           ///< Interface self-reference
    PfnMmlGpsNotifyCallback        pfnNotifyCallback;    ///< Callback function your want to register
} MmlGpsNotifyCallback_t;

/** @ingroup    MMLayerGps
    @brief      Response callback prototype
    @param      nSenderID        Sender's mailbox ID
    @param      nUserValue       Interface self-reference
    @param      eErrCode         Returned result (error code)
    @param      pGpsResponse     Pointer to the returned response payload
*/
struct MmlGpsResponse_t_;
typedef void (*PfnMmlGpsResponseCallback)(u16 nSenderID, u32 nUserValue, MmlGpsResult_e eErrCode, struct MmlGpsResponse_t_ *pGpsResponse);

/** @ingroup    MMLayerGps
    @brief      Response callback registration structure
*/
typedef struct
{
    u16                            nSenderID;              ///< Sender's mailbox ID
    u32                            nUserValue;             ///< Interface self-reference
    PfnMmlGpsResponseCallback      pfnResponseCallback;    ///< Callback function your want to register
} MmlGpsResponseCallback_t;

/** @ingroup    MMLayerGps
    @brief      Register notification callback
*/
typedef struct
{
    MmlGpsEvent_e                 eEvent;            ///< Specify which event you want to handle
    MmlGpsNotifyCallback_t        tNotifyCallback;   ///< Callback function you want to register
} MmlGpsRegNotifyCallback_t;



/** @ingroup    MMLayerGps
    @brief      Open GPS
*/
typedef struct
{
    MmlGpsFrequency_e    eFrequency;    ///< GPS frequency
    u16                  bToLogVBI;      ///< Log VBI at start
    u16                  bToOutVBI;      ///< Output VBI through UART for debugging
} MmlGpsOpenGps_t;

/** @ingroup    MMLayerGps
    @brief      IO Control
*/
typedef struct
{
    MmlGpsIoControlType_e   eIoControlType;
}
MmlGpsIoControl_t;

/** @ingroup    MMLayerGps
    @brief      Read GPS data
*/
typedef struct
{
    MmlGpsNmeaDataType_e     eNmeaDataType;
} MmlGpsReadGpsData_t;

/** @ingroup    MMLayerGps
    @brief      Response payload
*/
typedef struct MmlGpsResponse_t_
{
    MmlGpsState_e        eState;        ///< Current state

    union
    {
        MmlGpsNmeaData_t       tNmeaData;       ///< Used with 'Read GPS data'
        MmlGpsStateChange_t    tStateChange;    ///< Used with 'GPS_ERROR_STATE_CHANGE' result
        MmlGpsIoControlResult_t     tIoCtrolResult;  ///< Used with MML_UCID_GPS_IO_CONTROL_GPS result
    } uParam;
} MmlGpsResponse_t;

/** @ingroup    MMLayerGps
    @brief      Gps use case parameters
*/
typedef struct
{
    u32                             nUseCaseID;
    MmlGpsResponseCallback_t       *pResponseCallback;
    MmlGpsResponse_t               *pResponse;

    union
    {
   	    /* No parameter: 'Close GPS, Start GPS, Stop GPS' */

        MmlGpsOpenGps_t        tOpenGps;        /* Open GPS */
        MmlGpsReadGpsData_t    tReadGpsData;    /* Read GPS data */
        MmlGpsIoControl_t      tIoControl;      /* Io control for internal use */
    } uParam;
} MmlGpsUCParam_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#ifdef __cplusplus
}
#endif

#endif //__SRV_RESMGR_MMLGPS_TYPES_H__
