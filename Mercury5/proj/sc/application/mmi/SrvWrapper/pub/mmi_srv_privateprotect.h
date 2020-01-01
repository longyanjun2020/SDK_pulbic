/**
* @file    mmi_srv_privateprotect.h
* @brief   Privateprotect service wrapper header file
*          
*/

#ifndef __MMI_SRV_PRIVATEPROTECT_H__
#define __MMI_SRV_PRIVATEPROTECT_H__
#ifdef __APP_MMI_PRIVATEPROTECT__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_srv_client_commondefine.h"
#include "mmi_privateprotectsrv.h"

/*=============================================================*/
// Type definition of CallBack function
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

typedef void (*SrvPrivateProtectStatusCB)(void *pIApplet, PrivateProtectAuthResult_e eAuthResult);

/** SrvPrivateProtectSetStatusCB
@brief  The interface is used to set private protect status callback

@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_NOT_READY              PrivateProtectSrv is already terminated.
@retval  MAE_RET_FAILED                 If an error occurs.
@retval  MAE_RET_OUT_OF_MEMORY          Memory is not enough to complete the operation.
@retval  MAE_RET_NOT_SUPPORTED          PrivateProtectSrv is not supported.
*/
MAE_Ret SrvPrivateProtectSetStatusCB(SrvPrivateProtectStatusCB pfnStatusCB);
/*-----------------------------------------------------*/

/** SrvPrivateProtectGetItemProtectStatus
@brief  The interface is used to get  private protect status 

@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_NOT_READY              PrivateProtectSrv is already terminated.
@retval  MAE_RET_FAILED                 If an error occurs.
@retval  MAE_RET_OUT_OF_MEMORY          Memory is not enough to complete the operation.
@retval  MAE_RET_NOT_SUPPORTED          PrivateProtectSrv is not supported.
*/
MAE_Ret SrvPrivateProtectGetItemProtectStatus( MAE_ClsId id, boolean *bNeedVerifyPwProcedure);

#endif
#endif //__MMI_SRV_PRIVATEPROTECT_H__

