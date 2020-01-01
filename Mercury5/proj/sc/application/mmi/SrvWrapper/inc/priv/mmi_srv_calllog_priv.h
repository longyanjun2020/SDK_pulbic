/**
* @file    mmi_srv_calllog_priv.h
* @brief   Call log service wrapper private header file
*
*
* @author
* @version $Id:
*/

#ifndef __MMI_SrvCallLogPRIV_H__
#define __MMI_SrvCallLogPRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_srv_client_commondefine.h"
#include "mmi_srv_client_priv.h"

/*=============================================================*/
// Global function definition
/*=============================================================*/

/** SrvCallLogCreate
@brief  The interface is used to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv Calllog client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvCallLogCreate(SrvClient_t *pClient, s32 *pData);

/** SrvCallLogDestroy
@brief  The interface is used to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv Calllog client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvCallLogDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif //__MMI_SrvCallLogPRIV_H__
