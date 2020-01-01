/**
* @file    mmi_srv_eventdb_priv.h
* @brief   
*          
*/

#ifndef __MMI_SRV_EVENTDB_PRIV_H__
#define __MMI_SRV_EVENTDB_PRIV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"

/** SrvEventDbCreate
* @brief  The interface is use to create Service Body, Only used for Srv_Client.c;
*
* @param[in]        pClient             Pointer to the EventDB service client.
* @param[in]        pData               Init used data // non use in MAE
*
* @return MAE_RET_SUCCESS               If successful.
* @return MAE_RET_FAILED                If an error happen.
*/
MAE_Ret SrvEventDbCreate(SrvClient_t *pClient, s32 *pData);

/** SrvEventDbDestroy
* @brief  The interface is use to Destroy Service Body, Only used for Srv_Client.c;
*
* @param[in]        pClient             Pointer to the EventDB service client.
* @param[in]        pData               Release used data // non use in MAE
*
* @return MAE_RET_SUCCESS               If successful.
* @return MAE_RET_FAILED                If an error happen.
*/
MAE_Ret SrvEventDbDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif //__MMI_SRV_EVENTDB_PRIV_H__
