/**
 *
 * @file    ema_gps_msg.h
 *
 * @brief   This module defines the EMA GPS message struct type for GPS interface using.
 *
 * @author  Kevin Chang
 * @version $Id: ema_gps_msg.h 14361 2008-09-24 10:56:18Z kevin.chang $
 *
 */
#ifndef __EMA_GPS_MSG_H__
#define __EMA_GPS_MSG_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "esl_gps_itf.h"
#include "isl_gps_itf.h"


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __EMA_PARSE__
#define	DefExtern
#else
#define	DefExtern	extern
#endif


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/
typedef struct
{
  esl_GpsFreq_e           freq;
  esl_GpsDbgSetting_t     dbgSetting;
} ema_GpsOpen_t;

typedef struct
{
  esl_GpsNotifyBitmap_e   notifyBitmap;
  esl_GpsNotifyCb_t       notifyCb;
} ema_GpsRegNotify_t;

typedef struct
{
  esl_GpsNmeaType_e       nmeaType;
} ema_GpsReadData_t;

typedef struct
{
  esl_GpsIoctlCmdType_e   ioctlCmdType;
} ema_GpsIoctl_t;

typedef struct
{
  u32                     p2;
  u32                     p3;
  u32                     p4;
} ema_GpsPowerSaving_t;

typedef struct
{
  u8                     *nmeaBuffer;
  u16                     nmeaLength;
  isl_GpsErrCode_e        errCode;
} ema_GpsNmeaCnf_t;

typedef struct
{
  ema_TransType_t         TransType;
  esl_GpsCb_t            *pGpsDoneCB;
  union
  {
    ema_GpsOpen_t         gpsOpenCmd;
    ema_GpsRegNotify_t    gpsRegNotifyCmd;
    ema_GpsReadData_t     gpsReadDataCmd;
    ema_GpsIoctl_t        gpsIoctlCmd;
    ema_GpsPowerSaving_t  gpsPowerSavingCmd;
    ema_GpsNmeaCnf_t      gpsNmeaCnf;
  } cmdType;
} ema_GpsCmd_t;


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/


#endif /* __EMA_GPS_MSG_H__ */



