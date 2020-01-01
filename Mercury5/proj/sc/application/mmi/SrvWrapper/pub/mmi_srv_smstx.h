/**
* @file    mmi_srv_smstx.h
* @brief   
*          
*
* @author  
* @version $Id:
*/

#ifndef __MMI_SRV_SMSTX_H__
#define __MMI_SRV_SMSTX_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_smstransactionsrv.h"
//#include "mmi_srv_client_platformdefines.h"


typedef void (* SrvSmsTxSetSmsScaCB)(void *pThis, MMI_SMS_SetSCACnf_t *pSetScaCnf);
/**
 SrvSmsTxSetSmsScaReq
@brief  The interface of Service Client is use to set the short message center address.

@param[in]      pSetScaReq              Pointer to the short message center address.
@param[in]      pfnCallBack             TXI_EVT_SmsSetScaCnf CB func point

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If SmsTx has been released. 
*/
MAE_Ret SrvSmsTxSetSmsScaReq(MMI_SMS_SetSCAReq_t *pSetScaReq, SrvSmsTxSetSmsScaCB          pfnCallBack);

typedef void (* SrvSmsTxQuerySmsScaCB)(void *pThis, MMI_SMS_QuerySCACnf_t *pQryScaCnf);
/**
 SrvSmsTxQuerySmsScaReq
@brief  The interface of Service Client is use to query the short message center address.

@param[in]      nSimModule              The sim module id of the request.
@param[in]      pfnCallBack             TXI_EVT_SmsQryScaCnf CB func point

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If SmsTx has been released. 
*/
MAE_Ret SrvSmsTxQuerySmsScaReq(u8 nSimModule, SrvSmsTxQuerySmsScaCB pfnCallBack);

typedef void (* SrvSmsTxQuerySmsStorageCB)(void *pThis, MMI_SMS_QueryStorageCnf_t *pQryStrgCnf);
/**
 SrvSmsTxQuerySmsStorageReq
@brief  The interface of Service Client is use to query the SMS received storage.

@param[in]      nSimModule              The sim module id of the request.
@param[in]      pfnCallBack             TXI_EVT_SmsQryStorageCnf CB func point

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If SmsTx has been released. 
*/
MAE_Ret SrvSmsTxQuerySmsStorageReq(u8 nSimModule, SrvSmsTxQuerySmsStorageCB pfnCallBack);

typedef void (* SrvSmsTxSetSmsRecvStorageCB)(void *pThis, MMI_SMS_SetRecvStorageCnf_t *pSetRecvStrgCnf);
/**
 SrvSmsTxSetSmsRecvStorageReq
@brief  The interface of Service Client is use to set the SMS received storage.

@param[in]      pSetRecvStrgReq         The sim module id of the request.
@param[in]      pfnCallBack             TXI_EVT_SmsQryStorageCnf CB func point

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If SmsTx has been released. 
*/
MAE_Ret SrvSmsTxSetSmsRecvStorageReq(MMI_SMS_SetRecvStorageReq_t *pSetRecvStrgReq,
                                        SrvSmsTxSetSmsRecvStorageCB     pfnCallBack);


typedef void (* SrvSmsTxSetSmsStatusReportCB)(void *pThis, MMI_SMS_SetStatusReportCnf_t *pSetStatusReportCnf);
/**
 SrvSmsTxSetSmsStatusReportReq
@brief  The interface of Service Client is use to set if receive the status report.

@param[in]      pSetStatusReportReq     Pointer to set the information of the status report.
@param[in]      pfnCallBack             TXI_EVT_SmsSetStatusReportCnf CB func point

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If SmsTx has been released. 
*/
MAE_Ret SrvSmsTxSetSmsStatusReportReq(MMI_SMS_SetStatusReportReq_t *pSetStatusReportReq,
                                         SrvSmsTxSetSmsStatusReportCB  pfnCallBack);

typedef void (* SrvSmsTxSetCbmiCB)(void *pThis, MMI_SMS_SetCBMICnf_t *pSetCbmiCnf);
/**
 SrvSmsTxSetCbmiReq
@brief  The interface of Service Client is use to set CBMI.

@param[in]      pSetCbmiReq             Pointer to set the information of the status report.
@param[in]      pfnCallBack             TXI_EVT_SetCbmiCnf CB func point

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If SmsTx has been released. 
*/
MAE_Ret SrvSmsTxSetCbmiReq(MMI_CB_SetCBMIReq_t *pSetCbmiReq, SrvSmsTxSetCbmiCB             pfnCallBack);

typedef void (* SrvSmsTxQueryCbmiCB)(void *pThis, MMI_SMS_QueryCBMICnf_t *pQryCbmiCnf);
/**
 SrvSmsTxQueryCbmiReq
@brief  The interface of Service Client is use to set CBMI.

@param[in]      pfnCallBack             TXI_EVT_QryCbmiCnf CB func point

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If SmsTx has been released. 
*/
MAE_Ret SrvSmsTxQueryCbmiReq(SrvSmsTxQueryCbmiCB           pfnCallBack);

typedef void (* SrvSmsTxActivateCbmiCB)(void *pThis, MMI_CB_ActiveCBMICnf_t *pActiveCbmiCnf);
/**
 SrvSmsTxActivateCbmiReq
@brief  The interface of Service Client is use to set CBMI.

@param[in]      pActiveCbmiReq          Pointer to the CBMI of the request.
@param[in]      pfnCallBack             TXI_EVT_ActiveCbmiCnf CB func point

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If SmsTx has been released. 
*/
MAE_Ret SrvSmsTxActivateCbmiReq(MMI_CB_ActiveCBMIReq_t *pActiveCbmiReq, SrvSmsTxActivateCbmiCB     pfnCallBack);

typedef void (* SrvSmsTxActivateRngCbmiCB)(void *pThis, MMI_CB_ActiveRngCBMICnf_t *pActiveRngCbmiCnf);
/**
 SrvSmsTxActivateRngCbmiReq
@brief  The interface of Service Client is use to set CBMI.

@param[in]      pActiveRngCbmiReq       Pointer to the range CBMI of the request.
@param[in]      pfnCallBack             TXI_EVT_ActiveRngCbmiCnf CB func point

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If SmsTx has been released. 
*/
MAE_Ret SrvSmsTxActivateRngCbmiReq(MMI_CB_ActiveRngCBMIReq_t *pActiveRngCbmiReq,
                                   SrvSmsTxActivateRngCbmiCB     pfnCallBack);

/*-----------------------------------------------------*/

#endif /* __MMI_SRV_SMSTX_H__ */
