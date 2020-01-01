/**
* @file    mmi_srv_gps.h
* @brief
*
*/

#ifndef __MMI_SRV_GPS_H__
#define __MMI_SRV_GPS_H__


#include "mmi_srv_client_commondefine.h"
#include "mmi_gpssrv.h"

/*
    Open a session of GPS activity. Resource Manager will inform App of interrupt happenend/ ended
    via this command
*/

void SrvGpsOpenSessionReq(void);

/*
    Close a session of GPS activity.
*/

void SrvGpsCloseSessionReq(void);

/** SrvGpsOpenReq
@brief   The interface is use to open GPS.

@param[in]      pUserData               Pointer to the user specified data
@param[in]      eAppId                  Application Id which want to use GPS service
@param[in]      pfnCallBack             Pointer to the callback funtion of MAE_GPS_OPEN_CNF
*/
MediaSrvErrCode_e SrvGpsOpenReq(GPSSrvFreq_e eFreq, GPSSrvDbgSetting_t *pDgbSetting, GPSSrvCnfCb pfnCallBack);

/** SrvGpsCloseReq
@brief  The interface is use to close GPS.

@param[in]      pUserData               Pointer to the user specified data
@param[in]      eAppId                  Application Id which want to use GPS service
@param[in]      pfnCallBack             Pointer to the callback funtion of MAE_GPS_CLOSE_CNF
*/
MediaSrvErrCode_e  SrvGpsCloseReq(GPSSrvCnfCb pfnCallBack);

/** SrvGpsGetDataReq
@brief  The interface is use to get data.

@param[in]      eAppId                  Application Id which want to use GPS service
@param[in]      eCmdId                  GPS data type
@param[in]      pfnCallBack             Pointer to the callback funtion of MAE_GPS_GETDATA_CNF
*/
MediaSrvErrCode_e SrvGpsReadDataReq(GPSSrvNmeaType_e eType, GPSSrvDataCb pFnCb);

MediaSrvErrCode_e SrvGpsIoctlReq(GPSSrvIoctlCmdType_e eCmdType, GPSSrvIoctlCb pFnCb);

void SrvGpsChangePSMode(GPSSrvChangePSMode_t *ptMode, GPSSrvCnfCb pFnCb);

void SrvGpsSetInterruptNotifyCb(MediaSrvInterruptNotifyCb pfnGPSSrvCb, u32 nCusData);

MediaSrvErrCode_e  SrvGpsSetDataNotifyCb(GpsSrvNotifyInfoType_e eInfoType, GPSSrvDataNotifyCb pfnGPSSrvCb, u32 nCusData);

#endif /*__MMI_SRV_GPS_H__*/
