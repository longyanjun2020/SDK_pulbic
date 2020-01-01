/**
* @file    mmi_srv_config_priv.h
* @brief   
*          
*/

#ifndef __MMI_SRV_CONFIG_PRIV_H__
#define __MMI_SRV_CONFIG_PRIV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"


/** SrvConfigCreate
* @brief  The interface is use to create Service body, Only used for Srv_Client.c;
*
* @param[in]        pClient             Pointer to the Config service client.
* @param[in]        pData               Init used data // non use in MAE
*
* @return MAE_RET_SUCCESS               If successful.
* @return MAE_RET_FAILED                If an error happen.
*/
MAE_Ret SrvConfigCreate(SrvClient_t *pClient, s32 *pData);

/** SrvConfigDestroy
* @brief  The interface is use to destroy Service body, Only used for Srv_Client.c;
*
* @param[in]        pClient             Pointer to the Config service client.
* @param[in]        pData               Release used data // non use in MAE
*
* @return MAE_RET_SUCCESS               If successful.
* @return MAE_RET_FAILED                If an error happen.
*/
MAE_Ret SrvConfigDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif //__MMI_SRV_CONFIG_PRIV_H__
