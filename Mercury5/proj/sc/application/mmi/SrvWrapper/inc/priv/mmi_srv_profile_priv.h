/**
* @file    mmi_srv_profile_priv.h
*/

#ifndef __MMI_SrvProfilePRIV_H__
#define __MMI_SrvProfilePRIV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"

/** SrvProfileCreate
* @brief  The interface is use to create Service Body, Only used for Srv_Client.c;
*
* @param[in]        pClient             Pointer to the Profile service client.
* @param[in]        pData               init used data // non use in MAE
*
* @return MAE_RET_SUCCESS               If successful.
* @return MAE_RET_FAILED                If an error happen.
*/
MAE_Ret SrvProfileCreate(SrvClient_t *pClient, s32 *pData);

/** SrvProfileDestroy
@brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Profile service client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvProfileDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif //__MMI_SrvProfilePRIV_H__
