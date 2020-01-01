/**
* @file    mmi_srv_btobex.h
* @brief   
*          
*/

#ifndef __MMI_SRV_BTOBEX_H__
#define __MMI_SRV_BTOBEX_H__

#include "mmi_srv_client_commondefine.h"
#include "mmi_btobexsrv.h"

#ifdef __BLUETOOTH_MMI__
//Specific Service ListenerCallBack API

// BTOBEXSRV_MASK_TRANS_PROGRESS
typedef void (*SrvBtObexTransProgressCB)(void *pThis, u32 nTransFileSize, u32 nTotalFileSize); //BTOBEXSRV_EVT_TRANS_PROGRESS_IND

// BTOBEXSRV_MASK_TRANS_STATUS
typedef void (*SrvBtObexSendStatusCB)(void *pThis, BTSRV_TRANS_RESULT_e eResult); //BTOBEXSRV_EVT_SEND_STATUS_IND
typedef void (*SrvBtObexRecvReqCB)(void *pThis, u16 *pDevName); //BTOBEXSRV_EVT_RECV_REQ_IND
typedef void (*SrvBtObexRecvStatusCB)(void *pThis, BTSRV_TRANS_RESULT_e eResult, MAE_WChar *pFileName); //BTOBEXSRV_EVT_RECV_STATUS_IND
typedef void (*SrvBtObexImportStatusCB)(void *pThis, BTSRV_TRANS_RESULT_e eResult); //BTOBEXSRV_EVT_IMPORT_STATUS_IND

// BTOBEXSRV_MASK_TRANS_INTERACTIVE
typedef void (*SrvBtObexTransInteractiveCB)(void *pThis); //BTOBEXSRV_EVT_TRANS_INTERACTIVE_IND

/** SrvBtObexSetxxxCB
@brief  Add a CB to BT obex.

@param[in]      pfnCallBack             the function which will be called to notify the detection of specific event.

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_NOT_SUPPORTED           BTObex Srv is already terminated.
*/
MAE_Ret SrvBtObexSetTransProgressCB(SrvBtObexTransProgressCB pfnCallBack);

MAE_Ret SrvBtObexSetSendStatusCB(SrvBtObexSendStatusCB pfnCallBack);

MAE_Ret SrvBtObexSetRecvReqCB(SrvBtObexRecvReqCB pfnCallBack);

MAE_Ret SrvBtObexSetRecvStatusCB(SrvBtObexRecvStatusCB pfnCallBack);

MAE_Ret SrvBtObexSetImportStatusCB(SrvBtObexImportStatusCB pfnCallBack);

MAE_Ret SrvBtObexSetTransInteractiveCB(SrvBtObexTransInteractiveCB pfnCallBack);

/** SrvBtObexSendFileReq
@brief  BTObex send file request.

@param[in]      pAddr                   address
@param[in]      pwFileName              file name

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_BUSY                    BTObex Srv is already terminated.
*/
MAE_Ret SrvBtObexSendFileReq(u8 *pAddr, MAE_WChar *pwFileName);


/** SrvBtObexAbortTransFile
@brief  BTObex abort trans file.
*/
void SrvBtObexAbortTransFile(void);

/** SrvBtObexAcceptRsp
@brief  Set BTObex accept response or not.

@param[in]      bIsAccept               TRUE/FALSE
*/
void SrvBtObexAcceptRsp(boolean bIsAccept);

/** SrvBtObexIsReceiving
@brief  Get BTObex is receiving or not.

@retval TRUE                If is receiving.
@retval FALSE               If is not receiving. 
*/
boolean SrvBtObexIsReceiving(void);

/** SrvBtObexDisconObexLink
@brief  If this file  is last one in the sending list, calling this function to disconnect with ObexLink. (Correct PR#0150551)
*/
void SrvBtObexDisconObexLink(void);

#endif /*__BLUETOOTH_MMI__*/
#endif /*__MMI_SRV_BTOBEX_H__*/
