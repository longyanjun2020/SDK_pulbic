/**
* @file    mmi_srv_vcalstore_priv.h
* @brief   vCalendar store service wrapper private header file
*          
*
* @author  
* @version $Id: 
*/

#ifndef __MMI_SrvVCalStorePRIV_H__
#define __MMI_SrvVCalStorePRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_srv_client_commondefine.h"

/*=============================================================*/
// Global function definition
/*=============================================================*/

/**
SrvVCalStoreCreate
@brief  The interface is used to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv Vcalstore client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvVCalStoreCreate(SrvClient_t *pClient, s32 *pData);

/**
SrvVCalStoreDestroy
@brief  The interface is used to Destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv Vcalstore client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvVCalStoreDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif //__MMI_SrvVCalStorePRIV_H__

