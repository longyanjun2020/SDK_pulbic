/**
* @file    mmi_srv_cc_priv.h
* @brief   Call control service wrapper private header file
*
*
* @author
* @version $Id:
*/

#ifndef __MMI_SrvCcPRIV_H__
#define __MMI_SrvCcPRIV_H__


/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_srv_client_commondefine.h"

/*=============================================================*/
// Global function definition
/*=============================================================*/

/** SrvCcCreate
@brief  The interface is used to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient             Pointer to the Srv CC client.
@param[in]      pData               init used data // non use in MAE

@return MAE_RET_SUCCESS             If successful.
@return MAE_RET_FAILED              If an error happen.
*/
MAE_Ret SrvCcCreate(SrvClient_t *pClient, s32 *pData);

/** SrvCcDestroy
@brief  The interface is used to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient             Pointer to the Srv CC client.
@param[in]      pData               close used data // non use in MAE

@return MAE_RET_SUCCESS             If successful.
@return MAE_RET_FAILED              If an error happen.
*/
MAE_Ret SrvCcDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif //__MMI_SrvCcPRIV_H__
