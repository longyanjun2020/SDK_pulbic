/**
* @file mmi_srv_qq_priv.h
* QQ service wrapper module inner header files
*/

#ifndef __MMI_SRV_QQ_PRIV_H__
#define __MMI_SRV_QQ_PRIV_H__

#include "mmi_srv_qq.h"

#ifdef __cplusplus
extern "C" {
#endif

/** SrvQQCreate
@brief  The interface is use to create Service Body, Only used for Srv_Client.c

@param[in]      pClient                 Pointer to the Srv QQ client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvQQCreate(SrvClient_t *pClient, s32 *pData);


/** SrvQQDestroy
@brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv QQ client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvQQDestroy(SrvClient_t *pClient, s32 *pData);

#ifdef __cplusplus
}
#endif

#endif //__MMI_SRV_QQ_PRIV_H__

