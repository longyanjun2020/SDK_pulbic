/**
* @file    mmi_srv_vtcc_priv.h
* @brief
*
*
* @author
* @version $Id:
*/

#ifndef __MMI_SrvVtCcPRIV_H__
#define __MMI_SrvVtCcPRIV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"

#ifdef __VT_3G324M__

/** SrvVtCcCreate
@brief  The interface is use to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient             Pointer to the Srv VTCC client.
@param[in]      pData               init used data // non use in MAE

@return MAE_RET_SUCCESS             If successful.
@return MAE_RET_FAILED              If an error happen.
*/
MAE_Ret SrvVtCcCreate(SrvClient_t *pClient, s32 *pData);

/** SrvVtCcDestroy
@brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient             Pointer to the Srv VTCC client.
@param[in]      pData               close used data // non use in MAE

@return MAE_RET_SUCCESS             If successful.
@return MAE_RET_FAILED              If an error happen.
*/
MAE_Ret SrvVtCcDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif //__VT_3G324M__
#endif //__MMI_SrvVtCcPRIV_H__

