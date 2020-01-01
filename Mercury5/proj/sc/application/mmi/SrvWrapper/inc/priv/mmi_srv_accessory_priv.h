/**
* @file    mmi_srv_accessory_priv.h
* @brief   Accesscory service wrapper private header file
*          
*/

#ifndef __MMI_SRV_ACCESSORY_PRIV_H__
#define __MMI_SRV_ACCESSORY_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_srv_client_commondefine.h"

/*=============================================================*/
// Global function definition
/*=============================================================*/

/** SrvAccessoryCreate
@brief  The interface is used to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv Accessory client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
__SLDPM_FREE__ MAE_Ret SrvAccessoryCreate(SrvClient_t *pClient, s32 *pData);

/** SrvAccessoryDestroy
@brief  The interface is used to destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv Accessory client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvAccessoryDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif //__MMI_SRV_ACCESSORY_PRIV_H__

