/**
* @file    mmi_srv_tts_priv.h
* @brief   
*          
*/

#ifndef __MMI_SRV_TTS_PRIV_H__
#define __MMI_SRV_TTS_PRIV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"

/** SrvTtsCreate
@brief  The interface is use to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv Accessory client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvTtsCreate(SrvClient_t *pClient, s32 *pData);

/** SrvTtsDestroy
@brief  The interface is use to destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv Accessory client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvTtsDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif //__MMI_SRV_TTS_PRIV_H__

