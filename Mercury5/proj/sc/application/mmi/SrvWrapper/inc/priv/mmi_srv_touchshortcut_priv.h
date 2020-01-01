/**
* @file    mmi_srv_touchshortcut_priv.h
* @brief
*
*/

#ifndef __MMI_SRV_TOUCHSHORTCUT_PRIV_H__
#define __MMI_SRV_TOUCHSHORTCUT_PRIV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"

/** SrvTouchShortcutCreate
@brief  The interface is use to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv TouchShortcut client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvTouchShortcutCreate(SrvClient_t *pClient, s32 *pData);

/** SrvTouchShortcutDestroy
@brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv TouchShortcut client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvTouchShortcutDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif //__MMI_SRV_TOUCHSHORTCUT_PRIV_H__
