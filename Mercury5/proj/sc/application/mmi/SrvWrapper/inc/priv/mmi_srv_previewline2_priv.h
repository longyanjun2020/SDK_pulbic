/**
* @file    mmi_srv_previewline2_priv.h
* @brief
*
*/

#ifndef __MMI_SRV_PREVIEWLINE2_PRIV_H__
#define __MMI_SRV_PREVIEWLINE2_PRIV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"

/** SrvPreviewLine2Create
@brief  The interface is use to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv Previewline2 client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvPreviewLine2Create(SrvClient_t *pClient, s32 *pData);

/** SrvPreviewLine2Destroy
@brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv Previewline2 client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvPreviewLine2Destroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif //__MMI_SrvPreviewLine2PRIV_H__
