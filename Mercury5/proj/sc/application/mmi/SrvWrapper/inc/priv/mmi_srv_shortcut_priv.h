/**
* @file    mmi_srv_shortcut_priv.h
*/

#ifndef __MMI_SrvShortcutPRIV_H__
#define __MMI_SrvShortcutPRIV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"


/** SrvShortcutCreate
* @brief  The interface is use to create Service Body, Only used for Srv_Client.c;
*
* @param[in]        pClient             Pointer to the Shortcut service client.
* @param[in]        pData               init used data // non use in MAE
*
* @return MAE_RET_SUCCESS               If successful.
* @return MAE_RET_FAILED                If an error happen.
*/
MAE_Ret SrvShortcutCreate(SrvClient_t *pClient, s32 *pData);

/** SrvShortcutDestroy
@brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Shortcut service client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvShortcutDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif //__MMI_SrvShortcutPRIV_H__
