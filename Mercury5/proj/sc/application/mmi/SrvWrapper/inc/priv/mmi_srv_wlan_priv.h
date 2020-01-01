/**
* @file    mmi_srv_wlan_priv.h
* @brief   
*          
*
*/

#ifndef __MMI_WLANPRIV_H__
#define __MMI_WLANPRIV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"

/**
SrvWLanCreate
@brief  The interface is use to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient             Pointer to the Srv WLan client.
@param[in]      pData               init used data // non use in MAE

@return MAE_RET_SUCCESS             If successful.
@return MAE_RET_FAILED              If an error happen.
*/
MAE_Ret SrvWLanCreate(SrvClient_t *pClient, s32 *pData);

/**
SrvWLanDestroy
@brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient             Pointer to the Srv WLan client.
@param[in]      pData               close used data // non use in MAE

@return MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvWLanDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif //__MMI_WLANPRIV_H__
