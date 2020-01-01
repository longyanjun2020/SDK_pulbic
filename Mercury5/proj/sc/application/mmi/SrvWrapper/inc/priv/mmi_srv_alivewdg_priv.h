/**
* @file    mmi_srv_ALIVEWD_Priv.h
* @brief   
*          
*/

#ifndef __MMI_SRV_ALIVEWDG_PRIV_H__
#define __MMI_SRV_ALIVEWDG_PRIV_H__

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__)

/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"

/**
SrvAlivewdgCreate
@brief  The interface is use to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv ALIVEWDG client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvAlivewdgCreate(SrvClient_t *pClient, s32 *pData);

/**
SrvAlivewdgDestroy
@brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv ALIVEWDG client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvAlivewdgDestroy(SrvClient_t *pClient, s32 *pData);

#endif //__GADGETS_MMI__ || __3D_UI_IDLE_GADGETBAR__

#endif //__MMI_SRV_ALIVEWDG_PRIV_H__
/*-----------------------------------------------------*/
