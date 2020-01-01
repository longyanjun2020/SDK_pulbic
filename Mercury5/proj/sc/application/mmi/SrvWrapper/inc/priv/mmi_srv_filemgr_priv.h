/**
* @file    mmi_srv_filemgr_priv.h
* @brief
*
*/

#ifndef __MMI_SRV_FILEMGR_PRIV_H__
#define __MMI_SRV_FILEMGR_PRIV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"

/** SRV_FileMgr_Create
@brief  The interface is use to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the FileMgr Core client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SRV_FileMgr_Create(SrvClient_t *pClient, s32 *pData);

/** SRV_FileMgr_Destroy
@brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv FileMgr client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SRV_FileMgr_Destroy(SrvClient_t *pClient, s32 *pData);


/** SrvFileMgrCreate
@brief  The interface is use to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the FileMgr Core client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvFileMgrCreate(SrvClient_t *pClient, s32 *pData);

/** SrvFileMgrDestroy
@brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv FileMgr client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvFileMgrDestroy(SrvClient_t *pClient, s32 *pData);
/*-----------------------------------------------------*/
#endif //__MMI_SRV_FILEMGR_PRIV_H__
