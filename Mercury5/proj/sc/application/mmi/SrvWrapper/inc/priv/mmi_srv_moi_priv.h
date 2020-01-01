/**
* @file    mmi_srv_moi_priv.h
* @brief   
*          
*/

#ifndef __MMI_SrvMoiPRIV_H__
#define __MMI_SrvMoiPRIV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"

/** SrvMoiCreate
@brief  The interface is use to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient             Pointer to the MOI Core client.
@param[in]      pData               init used data // non use in MAE

@return MAE_RET_SUCCESS             If successful.
@return MAE_RET_FAILED              If an error happen.
*/
MAE_Ret SrvMoiCreate(SrvClient_t *pClient, s32 *pData);

/** SrvMoiDestroy
@brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient             Pointer to the Srv MOI client.
@param[in]      pData               close used data // non use in MAE

@return MAE_RET_SUCCESS             If successful.
@return MAE_RET_FAILED              If an error happen.
*/
MAE_Ret SrvMoiDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif //__MMI_SrvMoiPRIV_H__
