/**
* @file    mmi_srv_privateprotect_priv.h
* @brief   Privateprotect service wrapper private header file
*          
*/

#ifndef __MMI_SRV_PRIVATEPROTECT_PRIV_H__
#define __MMI_SRV_PRIVATEPROTECT_PRIV_H__
#ifdef __APP_MMI_PRIVATEPROTECT__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_srv_client_commondefine.h"

/*=============================================================*/
// Global function definition
/*=============================================================*/

/** SrvPrivateProtectCreate
@brief  The interface is used to create Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv NoteBook client.
@param[in]      pData                   init used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvPrivateProtectCreate(SrvClient_t *pClient, s32 *pData);

/** SrvPrivateProtectDestroy
@brief  The interface is used to destroy Service Body, Only used for Srv_Client.c;

@param[in]      pClient                 Pointer to the Srv NoteBook client.
@param[in]      pData                   close used data // non use in MAE

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If an error happen.
*/
MAE_Ret SrvPrivateProtectDestroy(SrvClient_t *pClient, s32 *pData);

/*-----------------------------------------------------*/
#endif //__MMI_SRV_PRIVATEPROTECT_PRIV_H__
#endif

