/**
* @file    mmi_srv_cfg_priv.h
* @brief
*
*/

#ifndef __MMI_SrvCfgPRIV_H__
#define __MMI_SrvCfgPRIV_H__

#include "mmi_srv_client_commondefine.h"

/** SrvCfgCreate
 *@brief  The interface is use to create Service Body, Only used for Srv_Client.c;

 *@param[in]        pClient         Pointer to the Srv CFG client.
 *@param[in]        pData           init used data // non use in MAE

 *@return MAE_RET_SUCCESS           If successful.
 *@return MAE_RET_FAILED            If an error happen.
*/
__SLDPM_FREE__ MAE_Ret SrvCfgCreate(SrvClient_t *pClient, s32 *pData);

/** SrvCfgDestroy
 *@brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;

 *@param[in]        pClient         Pointer to the Srv CFG client.
 *@param[in]        pData           close used data // non use in MAE

 *@return MAE_RET_SUCCESS           If successful.
 *@return MAE_RET_FAILED            If an error happen.
*/
MAE_Ret SrvCfgDestroy(SrvClient_t *pClient, s32 *pData);


#endif //__MMI_SrvCfgPRIV_H__

