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
* @file ABL_Gps.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of operations of GPS.
*
*/

#ifndef __SRV_RESMGR_GPS_H__
#define __SRV_RESMGR_GPS_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Common.h"
#include "esl_gps_itf.h"
//#include "MML_Manager.h"
#include "srv_resmgr_mmlgps_types.h"


/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
/**
 *  @brief The enumeration defines the return code of the GPS interface.
 */
typedef enum {
    ABL_GPS_OK,                 //ESL_GPS_OK
    ABL_GPS_FAIL,               //ESL_GPS_FAIL
    ABL_GPS_PARAM_ERROR,        //ESL_GPS_PARAM_ERROR
    ABL_GPS_MEM_ALLOC_ERROR,    //ESL_GPS_MEM_ALLOC_ERROR
    ABL_GPS_REJECT,             //ESL_GPS_REJECT
    ABL_GPS_EOF,                //ESL_GPS_EOF
    ABL_GPS_TIMEOUT,            //ESL_GPS_TIMEOUT
    ABL_GPS_NOT_SUPPORT,        //ESL_GPS_NOT_SUPPORT
    ABL_GPS_DENY,
} ABL_GpsErrCode_e;

/**
 * @brief The enumeration defines the GPS Ioctl command code.
 */
 /*
typedef enum {
    ABL_GPS_IOCTL_ENABLE_GPS_AND_LOG_VBI,    //ESL_GPS_IOCTL_ENABLE_GPS_AND_LOG_VBI
    ABL_GPS_IOCTL_DISABLE_GPS_AND_STOP_LOG_VBI,    //ESL_GPS_IOCTL_DISABLE_GPS_AND_STOP_LOG_VBI
    ABL_GPS_IOCTL_SUSPEND_GPS,    //ESL_GPS_IOCTL_SUSPEND_GPS
    ABL_GPS_IOCTL_RESUME_GPS,    //ESL_GPS_IOCTL_RESUME_GPS
    ABL_GPS_IOCTL_ENABLE_VBI_OUTPUT_AND_LOG_VBI_TO_SD,    //ESL_GPS_IOCTL_ENABLE_VBI_OUTPUT_AND_LOG_VBI_TO_SD
    ABL_GPS_IOCTL_DISABLE_VBI_OUTPUT_AND_STOP_LOG_VBI_TO_SD,    //ESL_GPS_IOCTL_DISABLE_VBI_OUTPUT_AND_STOP_LOG_VBI_TO_SD
    ABL_GPS_IOCTL_STOP_LOGGING_VBI_LOG_INTO_SD_CARD,    //ESL_GPS_IOCTL_STOP_LOGGING_VBI_LOG_INTO_SD_CARD
    ABL_GPS_IOCTL_ENABLE_ASSERT_LOG,    //ESL_GPS_IOCTL_ENABLE_ASSERT_LOG
    ABL_GPS_IOCTL_DISABLE_ASSERT_LOG,    //ESL_GPS_IOCTL_DISABLE_ASSERT_LOG
    ABL_GPS_IOCTL_POWER_SAVING_MODE,    //ESL_GPS_IOCTL_POWER_SAVING_MODE
    ABL_GPS_IOCTL_CHANGE_TO_6_GPS_CHANNELS,    //ESL_GPS_IOCTL_CHANGE_TO_6_GPS_CHANNELS
    ABL_GPS_IOCTL_CHANGE_TO_9_GPS_CHANNELS,    //ESL_GPS_IOCTL_CHANGE_TO_9_GPS_CHANNELS
    ABL_GPS_IOCTL_CHANGE_TO_12_GPS_CHANNELS,    //ESL_GPS_IOCTL_CHANGE_TO_12_GPS_CHANNELS
    ABL_GPS_IOCTL_CHANGE_TO_16_GPS_CHANNELS,    //ESL_GPS_IOCTL_CHANGE_TO_16_GPS_CHANNELS
    ABL_GPS_IOCTL_COLD_START,    //ESL_GPS_IOCTL_COLD_START
    ABL_GPS_IOCTL_COLD_START_10_TIMES,    //ESL_GPS_IOCTL_COLD_START_10_TIMES
    ABL_GPS_IOCTL_COLD_START_50_TIMES,    //ESL_GPS_IOCTL_COLD_START_50_TIMES
    ABL_GPS_IOCTL_WARM_START,    //ESL_GPS_IOCTL_WARM_START
    ABL_GPS_IOCTL_WARM_START_50_TIMES,    //ESL_GPS_IOCTL_WARM_START_50_TIMES
    ABL_GPS_IOCTL_HOT_START,    //ESL_GPS_IOCTL_HOT_START
    ABL_GPS_IOCTL_HOT_START_100_TIMES,    //ESL_GPS_IOCTL_HOT_START_100_TIMES
    ABL_GPS_IOCTL_GET_BB_VERSION,    //ESL_GPS_IOCTL_GET_BB_VERSION
    ABL_GPS_IOCTL_EXTERNAL_CMD_1,    //ESL_GPS_IOCTL_EXTERNAL_CMD_1
    ABL_GPS_IOCTL_EXTERNAL_CMD_2,    //ESL_GPS_IOCTL_EXTERNAL_CMD_2
    ABL_GPS_IOCTL_EXTERNAL_CMD_3,    //ESL_GPS_IOCTL_EXTERNAL_CMD_3
    ABL_GPS_IOCTL_EXTERNAL_CMD_4,    //ESL_GPS_IOCTL_EXTERNAL_CMD_4
} ABL_GpsIoctlCmdType_e;
*/
/**
 *  @brief The sturcture defines the return information of GPS.
 */
typedef esl_GpsInfo_t ABL_GpsInfo_t;

typedef esl_GpsFreq_e ABL_GpsFreq_e;
typedef esl_GpsDbgSetting_t ABL_GpsDbgSetting_t;
typedef esl_GpsNmeaType_e ABL_GpsNmeaType_e;
typedef esl_GpsIoctlCmdType_e ABL_GpsIoctlCmdType_e;

typedef struct ABL_GpsRspInfo_t_
{
    ABL_GpsErrCode_e eErrCode;
    ABL_GpsInfo_t tGpsInfo;
} ABL_GpsRspInfo_t;

/**
 * @brief Call back function, Application needs to provide the function entry
 *
 * @param senderID      : Sender task ID
 * @param userValue     : Reference value for indicating different sender in same task or check msg response.
 * @param pGpsInfo      : Callback information return by GPS multi-media driver
 *
 * @return None
 */
typedef void (*ABL_GpsCb)(u16 senderID, u32 userValue, ABL_GpsErrCode_e eErrCode, ABL_GpsInfo_t *pGpsInfo);
typedef struct
{
    u16 uSenderId;
    u32 uUserValue;
    ABL_GpsCb pfnCb;
} ABL_GpsCb_t;

typedef struct {
    esl_GpsFreq_e eFreq;
    esl_GpsDbgSetting_t tDbgSetting;
} ABL_GpsOpen_t;

typedef struct {
    esl_GpsNmeaType_e eType;
} ABL_GpsReadData_t;

typedef struct {
    esl_GpsIoctlCmdType_e eType;
} ABL_GpsIoctlCmd_t;

typedef struct {
    u32 nP2;
    u32 nP3;
    u32 nP4;
} ABL_GpsChangePSMode_t;

typedef MmlGpsOpenGps_t ABL_GpsOpenGps_t;
typedef MmlGpsReadGpsData_t ABL_GpsReadGpsData_t;

typedef struct {
    ABL_GpsCb_t *pCbParams;
    union
    {
        ABL_GpsOpenGps_t tGpsOpenGps;
        ABL_GpsReadGpsData_t tGpsReadGpsData;
        ABL_GpsOpen_t tGpsOpen;
        ABL_GpsReadData_t tGpsReadData;
        ABL_GpsIoctlCmd_t tGpsIoctl;
        ABL_GpsChangePSMode_t tGpsChangePSMode;
    } tParams;
} GpsCmd_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void ABL_GpsOpenSession(ResMgr_AppId_e eAppId, ABL_GpsCb_t *pGpsCb);
void ABL_GpsCloseSession(ResMgr_AppId_e eAppId, ABL_GpsCb_t *pGpsCb);
void ABL_GpsOpenReq(ResMgr_AppId_e eAppId, ABL_GpsFreq_e eFreq, ABL_GpsDbgSetting_t *pDgbSetting, ABL_GpsCb_t *pGpsCb);
void ABL_GpsStartReq(ResMgr_AppId_e eAppId, ABL_GpsCb_t *pGpsCb);
void ABL_GpsStopReq(ResMgr_AppId_e eAppId, ABL_GpsCb_t *pGpsCb);
void ABL_GpsCloseReq(ResMgr_AppId_e eAppId, ABL_GpsCb_t *pGpsCb);
void ABL_GpsReadDataReq(ResMgr_AppId_e eAppId, ABL_GpsNmeaType_e eType, ABL_GpsCb_t *pGpsCb);
void ABL_GpsIoctlReq(ResMgr_AppId_e eAppId, ABL_GpsIoctlCmdType_e eCmdType, ABL_GpsCb_t *pGpsCb);
void ABL_GpsChangePSModeReq(ResMgr_AppId_e eAppId, ABL_GpsChangePSMode_t *ptMode, ABL_GpsCb_t *pGpsCb);

void ABL_GpsOpenSyncReq(ResMgr_AppId_e eAppId, ABL_GpsFreq_e eFreq, ABL_GpsDbgSetting_t *pDgbSetting, ABL_GpsCb_t *pGpsCb);
void ABL_GpsStartSyncReq(ResMgr_AppId_e eAppId, ABL_GpsCb_t *pGpsCb);
void ABL_GpsStopSyncReq(ResMgr_AppId_e eAppId, ABL_GpsCb_t *pGpsCb);
void ABL_GpsCloseSyncReq(ResMgr_AppId_e eAppId, ABL_GpsCb_t *pGpsCb);
void ABL_GpsReadDataSyncReq(ResMgr_AppId_e eAppId, ABL_GpsNmeaType_e eType, ABL_GpsCb_t *pGpsCb);
void ABL_GpsIoctlSyncReq(ResMgr_AppId_e eAppId, ABL_GpsIoctlCmdType_e eCmdType, ABL_GpsCb_t *pGpsCb);
void ABL_GpsChangePSModeSyncReq(ResMgr_AppId_e eAppId, ABL_GpsChangePSMode_t *ptMode, ABL_GpsCb_t *pGpsCb);

ResMgr_ExecRes_e ABL_MmlGpsParseExecRes(s16 sResult);

#endif //__ABL_GPS_H__
