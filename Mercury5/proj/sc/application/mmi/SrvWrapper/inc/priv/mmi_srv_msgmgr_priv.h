/**
* @file    mmi_srv_msgmgr_priv.h
* @brief   
*          
*
*/

#ifndef __MMI_SrvMsgMgrPRIV_H__
#define __MMI_SrvMsgMgrPRIV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"

/** SrvMsgMgrCreate
@brief  The interface is use to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv MSGMGR client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvMsgMgrCreate(SrvClient_t *pClient, s32 *pData);

/** SrvMsgMgrDestroy
@brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv MSGMGR client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvMsgMgrDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif //__MMI_SrvMsgMgrPRIV_H__
