/**
* @file    mmi_srv_clipboard_priv.h
* @brief
*
*
* @author
* @version $Id:
*/

#ifndef __MMI_SRV_CLIPBOARD_PRIV_H__
#define __MMI_SRV_CLIPBOARD_PRIV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"

/** SrvClipBoardCreate
@brief  The interface is use to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv ClipBoard client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvClipBoardCreate(SrvClient_t *pClient, s32 *pData);

/** SrvClipBoardDestroy
@brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv ClipBoard client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvClipBoardDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif // __MMI_SRV_CLIPBOARD_PRIV_H__
