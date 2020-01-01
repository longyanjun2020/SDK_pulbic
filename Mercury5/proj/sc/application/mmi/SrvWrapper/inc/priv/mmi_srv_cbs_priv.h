/**
* @file    mmi_srv_cbs_priv.h
* @brief   
*          
*
*/

#ifndef __MMI_SrvCbsPRIV_H__
#define __MMI_SrvCbsPRIV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_srv_client_priv.h"

/** SrvCbsCreate
@brief  The interface is use to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient         Pointer to the Srv CBS client.
@param[in]      pData           init used data // non use in MAE

@return MAE_RET_SUCCESS         If successful.
@return MAE_RET_FAILED          If an error happen.
*/
MAE_Ret SrvCbsCreate(SrvClient_t *pClient, s32 *pData);

/** SrvCbsDestroy
@brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient         Pointer to the Srv CBS client.
@param[in]      pData           close used data // non use in MAE

@return MAE_RET_SUCCESS         If successful.
@return MAE_RET_FAILED          If an error happen.
*/
MAE_Ret SrvCbsDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif //__MMI_SrvCbsPRIV_H__
