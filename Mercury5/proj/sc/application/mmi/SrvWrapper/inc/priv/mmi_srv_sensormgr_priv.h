/**
* @file    mmi_srv_sensormgr_priv.h
* @brief
*
*/

#ifndef __MMI_SRV_SENSORMGR_PRIV_H__
#define __MMI_SRV_SENSORMGR_PRIV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"

/** SrvSensorMgrCreate
@brief  The interface is use to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv SensorMgr client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvSensorMgrCreate(SrvClient_t *pClient, s32 *pData);

/** SrvSensorMgrDestroy
@brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv SensorMgr client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvSensorMgrDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif // __MMI_SRV_SENSORMGR_PRIV_H__
