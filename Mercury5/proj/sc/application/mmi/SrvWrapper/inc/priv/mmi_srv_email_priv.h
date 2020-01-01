/**
* @file mmi_srv_email_priv.h
* 	email service wrapper module inner header files
*/

#ifndef __MMI_SRV_EMAIL_PRIV_H__
#define __MMI_SRV_EMAIL_PRIV_H__

#include "mmi_srv_email.h"

#ifdef __cplusplus
extern "C" {
#endif

/** SrvEmailCreate
@brief  The interface is use to create Service Body, Only used for Srv_Client.c

@param[in]      pClient                 Pointer to the Srv Email client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvEmailCreate(SrvClient_t *pClient, s32 *pData);


/** SrvEmailDestroy
@brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv Email client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvEmailDestroy(SrvClient_t *pClient, s32 *pData);

#ifdef __cplusplus
}
#endif

#endif //__MMI_SRV_EMAIL_PRIV_H__

