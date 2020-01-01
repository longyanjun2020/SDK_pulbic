/**
* @file    mmi_srv_mmstx.h
* @brief   
*          
*
* @author  
* @version $Id:
*/

#ifndef __MMI_SRV_MMSTX_H__
#define __MMI_SRV_MMSTX_H__


/*-----------------------------------------------------*/
#include "mmi_mmstransactionsrv.h"
#include "mmi_srv_client_commondefine.h"

typedef void (* SrvMmsTxSaveMmsCB)(void *pThis, MMI_SaveMmsCnf_t *pSaveMmsCnf);
/**
 SrvMmsTxSaveMmsReq
@brief  The interface of Service Client is used to save the editing MMI_MMS_Composer_Cntx data to a draft MMS.

@param[in]      pMmsCnt                 The pointer to data structure MMI_MMS_Composer_Cntx.
@param[in]      nMsgId                  The message id for this request.
@param[in]      eMsgLoc                 The mailbox of specified message.
@param[in]      pfnCallBack             MMSTRANSSRV_EVT_SAVE_MMS_CNF CB func point.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If MMSTRANSSRV has been released. 
@return MAE_RET_FOLDER_NOT_FOUND        If Can't not create My_MMS folder. 
@return MAE_RET_FS_FULL                 
 */
MAE_Ret SrvMmsTxSaveMmsReq(MMI_MMS_Composer_Cntx *pMmsCnt,
                           SMI_MsgID_t nMsgId,
                           SMI_MsgLocation_e eMsgLoc,
                           SrvMmsTxSaveMmsCB pfnCallBack);

typedef void (* SrvMmsTxGetMmsReceiverListCB)(void *pThis, MMI_GetMmsReceiverListCnf_t *pMmsGetRecvLstCnf);
/**
 SrvMmsTxGetMmsReceiverListReq
@brief  The interface of Service Client is used to get the receiver list of the specified MMS by id.

@param[in]      nMsgId                  The message id for this request.
@param[in]      eMsgBox                 The mailbox of specified message.
@param[in]      pfnCallBack             MMSTRANSSRV_EVT_GET_RECVLIST_CNF CB func point.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If MMSTRANSSRV has been released. 
*/
MAE_Ret SrvMmsTxGetMmsReceiverListReq(u16 nMsgId,
                                      MMI_MMS_FS_MAILBOX_e eMsgBox,
                                      SrvMmsTxGetMmsReceiverListCB pfnCallBack);

typedef void (* SrvMmsTxGetMmsSenderAddrCB)(void *pThis, MMI_GetMmsSenderAddrCnf_t *pMmsGetSenderAddrCnf);
/**
 SrvMmsTxGetMmsSenderAddrReq
@brief  The interface of Service Client is used to get the sender address of the specified MMS by id.

@param[in]      nMsgId                  The message id for this request.
@param[in]      eMsgBox                 The mailbox of specified message.
@param[in]      pfnCallBack             MMSTRANSSRV_EVT_GET_SENDER_CNF CB func point.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If MMSTRANSSRV has been released. 
 */
MAE_Ret SrvMmsTxGetMmsSenderAddrReq(u16 nMsgId,
                                    MMI_MMS_FS_MAILBOX_e eMsgBox,
                                    SrvMmsTxGetMmsSenderAddrCB pfnCallBack);

typedef void (* SrvMmsTxGetMmsItemInfoCB)(void *pThis, MMI_GetMmsItemInfoCnf_t *pMmsGetItemInfoCnf);
/**
 SrvMmsTxGetMmsItemInfoReq
@brief  The interface of Service Client is used to get the item info of the specified MMS by id.

@param[in]      nMsgId                  The message id for this request.
@param[in]      eMsgBox                 The mailbox of specified message.
@param[in]      pfnCallBack             MMSTRANSSRV_EVT_GET_ITEMINFO_CNF CB func point.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If MMSTRANSSRV has been released.  
*/
MAE_Ret SrvMmsTxGetMmsItemInfoReq(u16 nMsgId,
                                  MMI_MMS_FS_MAILBOX_e eMsgBox,
                                  SrvMmsTxGetMmsItemInfoCB pfnCallBack);

typedef void (* SrvMmsTxGetMmsSubjectInfoCB)(void *pThis, MMI_GetMmsSubjectInfoCnf_t *pMmsGetSubjectInfoCnf);
/**
 SrvMmsTxGetMmsSubjectInfoReq
@brief  The interface of Service Client is used to get the subject info of the specified MMS by id.

@param[in]      nMsgId                  The message id for this request.
@param[in]      eMsgBox                 The mailbox of specified message.
@param[in]      pfnCallBack             MMSTRANSSRV_EVT_GET_SUBJECT_CNF CB func point.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If MMSTRANSSRV has been released.  
*/
MAE_Ret SrvMmsTxGetMmsSubjectInfoReq(u16 nMsgId,
                                     MMI_MMS_FS_MAILBOX_e eMsgBox,
                                     SrvMmsTxGetMmsSubjectInfoCB pfnCallBack);

typedef void (* SrvMmsTxGetMmsStatusInfoCB)(void *pThis, MMI_GetMmsStatusInfoCnf_t *pMmsStatusInfoCnf);
/**
 SrvMmsTxGetMmsStatusInfoReq
@brief  The interface of Service Client is used to get the status(read/unread) info of the specified MMS by id.

@param[in]      nMsgId                  The message id for this request.
@param[in]      eMsgBox                 The mailbox of specified message.
@param[in]      pfnCallBack             MMSTRANSSRV_EVT_GET_STATUS_CNF CB func point.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If MMSTRANSSRV has been released.  
 */
MAE_Ret SrvMmsTxGetMmsStatusInfoReq(u16 nMsgId,
                                    MMI_MMS_FS_MAILBOX_e eMsgBox,
                                    SrvMmsTxGetMmsStatusInfoCB pfnCallBack);

typedef void (* SrvMmsTxGetMmsAllSlidesCB)(void *pThis, MMI_GetMmsAllSlidesCnf_t *pGetMmsAllSlidesCnf);
/**
 SrvMmsTxGetMmsAllSlidesReq
@brief  The interface of Service Client is used to get the content of all slides by a specified id.

@param[in]      nMsgId                  The message id for this request.
@param[in]      eMsgLoc                 The location of specified message.
@param[in]      pfnCallBack             MMSTRANSSRV_EVT_GET_ALL_SLIDES_CNF CB func point.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If MMSTRANSSRV has been released.
 */
MAE_Ret SrvMmsTxGetMmsAllSlidesReq(u16 nMsgId,
                                   SMI_MsgLocation_e eMsgLoc,
                                   SrvMmsTxGetMmsAllSlidesCB pfnCallBack);

typedef void (* SrvMmsTxSendMmsByBoxCB)(void *pThis, SMI_MsgID_t msgId, MMI_MmsStatus_e status);
/**
 SrvMmsTxSendMmsByBoxReq
@brief  The interface of Service Client is used to send a MMS by a specified id.

@param[in]      nMsgId                  The message id for this request.
@param[in]      eMsgBox                 The mailbox of specified message.
@param[in]      nSimModule              The SIM module id.
@param[in]      pfnCallBack             MMSTRANSSRV_EVT_SEND_BYBOX_CNF CB func point.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If MMSTRANSSRV has been released.
 */
MAE_Ret SrvMmsTxSendMmsByBoxReq(u16 nMsgId,
                                MMI_MMS_FS_MAILBOX_e eMsgBox,
                                u8 nSimModule,
                                SrvMmsTxSendMmsByBoxCB pfnCallBack);

typedef void (* SrvMmsTxMmsTransCancelCB)(void *pThis, MMI_TransCancelCnf_t *pMmsTransCancelCnf);
/**
 SrvMmsTxMmsTransCancelReq
@brief  The interface of Service Client is used to cancel the current transaction.

@param[in]      pfnCallBack             MMSTRANSSRV_EVT_TRANS_CANCEL_CNF CB func point.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If MMSTRANSSRV has been released.
*/
MAE_Ret SrvMmsTxMmsTransCancelReq(SrvMmsTxMmsTransCancelCB pfnCallBack);

typedef void (* SrvMmsTxRecvMmsBodyCB)(void *pThis, SMI_MsgID_t msgId, MMI_MmsStatus_e status);
/**
 SrvMmsTxRecvMmsBodyReq
@brief  The interface of Service Client is used to receive the MMS body by a specified id.

@param[in]      nMsgId                  The message id for this request.
@param[in]      eMsgBox                 The mailbox of specified message.
@param[in]      nSimModule              The SIM module id.
@param[in]      pfnCallBack             MMSTRANSSRV_EVT_RECV_MAIL_CNF CB func point.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If MMSTRANSSRV has been released.
@return MAE_RET_FS_FULL                 
*/
MAE_Ret SrvMmsTxRecvMmsBodyReq(u16 nMsgId,
                               MMI_MMS_FS_MAILBOX_e eMsgBox,
                               u8 nSimModule,
                               SrvMmsTxRecvMmsBodyCB pfnCallBack);

typedef void (* SrvMmsTxDelMmsByIdCB)(void *pThis, MMI_DelMmsByIdCnf_t *pMmsDelByIdCnf, SMI_MsgID_t msgId);
/**
 SrvMmsTxDelMmsByIdReq
@brief  The interface of Service Client is used to delete a MMS by a specified id.

@param[in]      nMsgId                  The message id for this request.
@param[in]      eMsgLoc                 The location of specified message.
@param[in]      pfnCallBack             MMSTRANSSRV_EVT_DEL_ITEM_CNF CB func point.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If MMSTRANSSRV has been released.
 */
MAE_Ret SrvMmsTxDelMmsByIdReq(u16 nMsgId,
                              SMI_MsgLocation_e eMsgLoc,
                              SrvMmsTxDelMmsByIdCB pfnCallBack);

typedef void (* SrvMmsTxDelMmsByLocCB)(void *pThis, MMI_DelMmsByBoxCnf_t *pMmsDelByBoxCnf);
/**
 SrvMmsTxDelMmsByLocReq
@brief  The interface of Service Client is used to delete messages for a specified location.

@param[in]      eMsgLoc                 The location of specified message.
@param[in]      pfnCallBack             MMSTRANSSRV_EVT_DEL_ALL_ITEMS_CNF CB func point.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If MMSTRANSSRV has been released.
 */
MAE_Ret SrvMmsTxDelMmsByLocReq(SMI_MsgLocation_e eMsgLoc,
                               SrvMmsTxDelMmsByLocCB pfnCallBack);

typedef void (* SrvMmsTxMmsBootUpCB)(void *pThis, MMI_BootupMmsCnf_t *pMmsBootupCnf);
/**
 SrvMmsTxMmsBootUpReq
@brief  The interface of Service Client is used to initialize and activate the CDMMS kernel.

@param[in]      pfnCallBack             MMSTRANSSRV_EVT_BOOTUP_CNF CB func point.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If MMSTRANSSRV has been released.
 */
MAE_Ret SrvMmsTxMmsBootUpReq(SrvMmsTxMmsBootUpCB pfnCallBack);

typedef void (* SrvMmsTxGetMmsAllAttachCB)(void *pThis, MMI_GetMmsAllAttachesCnf_t *pGetMmsAllAttachesCnf);
/**
 SrvMmsTxGetMmsAllAttachReq
@brief  The interface of Service Client is used to get the content of all attachments by a specified id.

@param[in]      nMsgId                  The message id for this request.
@param[in]      eMsgLoc                 The location of specified message.
@param[in]      pfnCallBack             MMSTRANSSRV_EVT_GET_ALL_ATTACHES_CNF CB func point.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If MMSTRANSSRV has been released.
*/
MAE_Ret SrvMmsTxGetMmsAllAttachReq(u16 nMsgId,
                                   SMI_MsgLocation_e eMsgLoc,
                                   SrvMmsTxGetMmsAllAttachCB pfnCallBack);

typedef void (* SrvMmsTxMoveMmsCB)(void *pThis, MMI_MoveMmsCnf_t *pMmsMoveMmsCnf, SMI_MsgID_t msgId);
/**
 SrvMmsTxMoveMmsReq
@brief  The interface of Service Client is used to move mms message from eSourceLoc to eDesLoc.

@param[in]      nMsgId                  The message id for this request.
@param[in]      eSourceLoc              The source location of specified message.
@param[in]      eDesLoc                 The destination location of specified message.
@param[in]      pfnCallBack             MMSTRANSSRV_EVT_MOVE_MMS_CNF CB func point.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_SUPPORTED           If MMSTRANSSRV has been released.
 */
MAE_Ret SrvMmsTxMoveMmsReq(u16 nMsgId,
                           SMI_MsgLocation_e eSourceLoc,
                           SMI_MsgLocation_e eDesLoc,
                           SrvMmsTxMoveMmsCB pfnCallBack);
/*-----------------------------------------------------*/

#endif /* __MMI_SRV_MMSTX_H__ */
