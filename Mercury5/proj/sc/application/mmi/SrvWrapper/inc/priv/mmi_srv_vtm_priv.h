/**
* @file    mmi_srv_vtm_priv.h
* @brief   
*          
*/
#ifdef __VT_3G324M__

#ifndef __MMI_SRVVTMPRIV_H__
#define __MMI_SRVVTMPRIV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"

/** SrvVtmCreate
@brief  The interface is use to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv VTM client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvVtmCreate(SrvClient_t *pClient, s32 *pData);

/** SrvVtmDestroy
@brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv VTM client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvVtmDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif //__MMI_SRVVTMPRIV_H__

#endif //#ifdef __VT_3G324M__
