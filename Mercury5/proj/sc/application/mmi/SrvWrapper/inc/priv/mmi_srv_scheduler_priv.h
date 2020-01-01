/**
* @file    mmi_srv_scheduler_priv.h
* @brief
*
*/

#ifndef __MMI_SRV_SCHEDULER_PRIV_H__
#define __MMI_SRV_SCHEDULER_PRIV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"

/** SrvSchCreate
@brief  The interface is use to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv scheduler client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvSchCreate(SrvClient_t *pClient, s32 *pData);

/** SrvSchDestroy
@brief  The interface is use to destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv scheduler client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvSchDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif //__MMI_SRV_SCHEDULER_PRIV_H__

