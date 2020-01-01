/**
* @file    mmi_srv_touchshortcut_priv.h
* @brief
*
*/

#ifndef __MMI_SrvTouchPRIV_H__
#define __MMI_SrvTouchPRIV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"

/** SrvTouchCreate
@brief  The interface is use to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv TouchShortcut client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvTouchCreate(SrvClient_t *pClient, s32 *pData);

/** SrvTouchDestroy
@brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv TouchShortcut client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvTouchDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif //__MMI_SrvTouchPRIV_H__
