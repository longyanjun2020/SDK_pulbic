/**
* @file    mmi_srv_OBJPROCESSING.h
* @brief   
*          
*/

#ifndef __MMI_SRV_OBJPROCESSING_PRIV_H__
#define __MMI_SRV_OBJPROCESSING_PRIV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"

/** SrvObjProcessingCreate
@brief  The interface is use to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv OBJPROCESSING client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvObjProcessingCreate(SrvClient_t *pClient, s32 *pData);

/** SrvObjProcessingDestroy
@brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv OBJPROCESSING client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvObjProcessingDestroy(SrvClient_t *pClient, s32 *pData);

#endif //__MMI_SRV_OBJPROCESSING_PRIV_H__
/*-----------------------------------------------------*/
