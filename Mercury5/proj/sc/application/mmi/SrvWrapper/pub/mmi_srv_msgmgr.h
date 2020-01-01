/**
* @file    mmi_srv_msgmgr.h
* @brief
*
*
* @author
* @version $Id:
*/

#ifndef __MMI_SRV_MSGMGR_H__
#define __MMI_SRV_MSGMGR_H__


/*-----------------------------------------------------*/
#include "mmi_messagemanagersrv.h"
#include "mmi_srv_client_commondefine.h"
//#include "mmi_srv_client_platformdefines.h"

/**
SRV_MSGMGR EV and Callback Function descript
@brief  The interface of Service Client is use to set the indicator-callback to CB module

SMI_NOTIFY_MASK_ADD
Group1:
SMI_EVT_AddMsgNotify
SMI_EVT_AddMsgSortByTimeNotify

SMI_NOTIFY_MASK_DEL
Group2:
SMI_EVT_DelMsgNotify

SMI_NOTIFY_MASK_DEL_LOCATION
Group3:
SMI_EVT_DelLocationNotify

SMI_NOTIFY_MASK_UPDATE_HEADER
Group4:
SMI_EVT_UpdateMsgHeaderNotify

SMI_NOTIFY_MASK_NOBUSY
Group5:
SMI_EVT_OperationNotBusyNotify

*/


typedef void (* SrvMsgMgrCommandNotifyCB)(void *pThis, SMI_LIST_PARAM nListParam, IArrayModel *pArrayModel);
/**
SrvMsgMgrSetCommandNotifyCB
@brief  The interface of Service Client is use to set CB to listen the status

@param[in]      pfnCallBack             "SMI_NOTIFY_MASK_ADD" "SMI_NOTIFY_MASK_DEL" "SMI_NOTIFY_MASK_DEL_LOCATION" "SMI_NOTIFY_MASK_MOVE" CB func point
*/
void SrvMsgMgrSetCommandNotifyCB(SrvMsgMgrCommandNotifyCB pfnCallBack);

typedef void (* SrvMsgMgrAddMsgNotifyCB)(void *pThis, SMI_LIST_PARAM nListParam, IArrayModel *pArrayModel);
/**
SrvMsgMgrSetAddMsgNotifyCB
@brief  The interface of Service Client is use to set CB to listen the status

@param[in]      pfnCallBack             SMI_EVT_AddMsgNotify CB func point
*/
void SrvMsgMgrSetAddMsgNotifyCB(SrvMsgMgrAddMsgNotifyCB pfnCallBack);

typedef void (* SrvMsgMgrAddMsgSortByTimeNotifyCB)(void *pThis,
                                                         SMI_LIST_PARAM nListParam,
                                                         IArrayModel *pArrayModel);
/**
SrvMsgMgrSetAddMsgSortByTimeNotifyCB
@brief  The interface of Service Client is use to set CB to listen the status

@param[in]      pfnCallBack             SMI_EVT_AddMsgSortByTimeNotify CB func point
*/
void SrvMsgMgrSetAddMsgSortByTimeNotifyCB(SrvMsgMgrAddMsgSortByTimeNotifyCB pfnCallBack);


typedef void (* SrvMsgMgrDelMsgNotifyCB)(void *pThis, SMI_LIST_PARAM nListParam, IArrayModel *pArrayModel);
/**
 SrvMsgMgrSetDelMsgNotifyCB
@brief  The interface of Service Client is use to set CB to listen the ready

@param[in]      pfnCallBack             SMI_EVT_DelMsgNotify Call back function point
*/
void SrvMsgMgrSetDelMsgNotifyCB(SrvMsgMgrDelMsgNotifyCB           pfnCallBack);

typedef void (* SrvMsgMgrDelLocationNotifyCB)(void *pThis, SMI_LIST_PARAM nListParam, IArrayModel *pArrayModel);
/**
 SrvMsgMgrSetDelLocationNotifyCB
@brief  The interface of Service Client is use to set CB to listen the ready

@param[in]      pfnCallBack             SMI_EVT_DelLocationNotify Call back function point
*/
void SrvMsgMgrSetDelLocationNotifyCB(SrvMsgMgrDelLocationNotifyCB pfnCallBack);

typedef void (* SrvMsgMgrMsgStatusNotifyCB)(void *pThis, SMI_LIST_PARAM nListParam, IArrayModel *pArrayModel);
/**
 SrvMsgMgrSetMsgStatusNotifyCB
@brief  The interface of Service Client is use to set CB to listen the ready

@param[in]      pfnCallBack             "SMI_NOTIFY_MASK_READ_STATUS" "SMI_NOTIFY_MASK_SENT_STATUS" "SMI_NOTIFY_MASK_COMPLETE_STATUS"
                                        "SMI_NOTIFY_MASK_UPDATE_HEADER" Call back function point
*/
void SrvMsgMgrSetMsgStatusNotifyCB(SrvMsgMgrMsgStatusNotifyCB pfnCallBack);

typedef void (* SrvMsgMgrUpdateHeaderNotifyCB)(void *pThis, SMI_LIST_PARAM nListParam, IArrayModel *pArrayModel);
/**
 SrvMsgMgrSetUpdateHeaderNotifyCB
@brief  The interface of Service Client is use to set CB to listen the ready

@param[in]      pfnCallBack             SMI_EVT_UpdateMsgHeaderNotify Call back function point
*/
void SrvMsgMgrSetUpdateHeaderNotifyCB(SrvMsgMgrUpdateHeaderNotifyCB pfnCallBack);

typedef void (* SrvMsgMgrNoBusyNotifyCB)(void *pThis);
/**
 SrvMsgMgrSetNoBusyNotifyCB
@brief  The interface of Service Client is use to set CB to listen the ready

@param[in]      pfnCallBack             SMI_EVT_OperationNotBusyNotify Call back function point
*/
void SrvMsgMgrSetNoBusyNotifyCB(SrvMsgMgrNoBusyNotifyCB pfnCallBack);

typedef void (* SrvMsgMgrModifyMsgCB)(void *pThis, SMI_MsgMgrStatus_e eResult); //refer to post "SMI_EVT_ModifyMsgParamCnf"
/**
 SrvMsgMgrModifyMessageParamsAsync
@brief  The interface of Service Client is used to modify the parameter of the message's status.

@param[in]      nMsgId                  The id of the message.
@param[in]      eMsgLocation                The original location of the message.
@param[in]      pMsgHdr                 The modified data of the message header.
@param[in]      pfnCallBack             SMI_EVT_ModifyMsgParamCnf CB func point

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_BUSY                    If operation is busy.
@return MAE_RET_NOT_SUPPORTED           If input parameter error.
 */
MAE_Ret SrvMsgMgrModifyMessageParamsAsync(SMI_MsgID_t nMsgId,
                                          SMI_MsgLocation_e eMsgLocation,
                                          SMI_MsgHdr_t *pMsgHdr,
                                          SrvMsgMgrModifyMsgCB pfnCallBack);

typedef void (* SrvMsgMgrDelMsgByIdCB)(void *pThis, SMI_MsgMgrStatus_e Result); //refer to post "SMI_EVT_DelMsgByIdCnf"
/**
 SrvMsgMgrDeleteMessageByIdAsync
@brief  The interface of Service Client is used to delete the message of the location.

@param[in]      nMsgId                  The message id for this request.
@param[in]      MsgId                   The id of the message.
@param[in]      msgLocation             The location of the message.
@param[in]      pfnCallBack             SMI_EVT_DelMsgByIdCnf CB func point

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_BUSY                    If operation is busy.
 */
MAE_Ret SrvMsgMgrDeleteMessageByIdAsync(SMI_MsgID_t nMsgId,
                                           SMI_MsgLocation_e eMsgLocation,
                                           SrvMsgMgrDelMsgByIdCB pfnCallBack);

/**
 SrvMsgMgrRetrieveMessageHeader
@brief  The interface of Service Client is used to get the message header information.
        [Note]The data will alloc and copy to pMsgHder; Remember to Free pMsgHder by AP self

@param[in]      nMsgId                  The id of the message.
@param[in]      eMsgLocation            The location of the message.
@param[out]     pMsgHder                The pointer address of the retrieved message header.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_NOT_FOUND               If get msg info NULL.
*/
MAE_Ret SrvMsgMgrRetrieveMessageHeader(SMI_MsgID_t nMsgId,
                                       SMI_MsgLocation_e eMsgLocation,
                                       SMI_MsgHdr_t **pMsgHder);

/**
 SrvMsgMgrListMessageByParam
@brief  The interface of Service Client is used to get the message list information for the params filter.

@param[out]     pMsgHdrLstModel         The vector model of the retrieved message list information.
@param[in]      bVectorModel            Add the retrieved data into vector model or not.
@param[in]      nParams                 The filter parameter of the retrieved message list information.
@param[in]      pTransFunc              The structure pointer of the handled data
@param[in]      pUserData               The pUserData param of the pTransFunc

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_ILLEGAL_OPERATION       If terminated.
 */
MAE_Ret SrvMsgMgrListMessageByParam(IModel *pMsgHdrLstModel,
                                    boolean bVectorModel,
                                    SMI_LIST_PARAM nParams,
                                    SMI_MSGHEADER_TRANSFER_FUNC_PTR pTransFunc,
                                    void *pUserData);

/**
 SrvMsgMgrListMessageByParam
@brief  The interface of Service Client is used to get the message list information for the params filter.

@param[out]     pMsgHdrLstModel         The vector model of the retrieved message list information.
@param[in]      bVectorModel            Add the retrieved data into vector model or not.
@param[in]      nParams                 The filter parameter of the retrieved message list information.
@param[in]      pTransFunc              The structure pointer of the handled data
@param[in]      pUserData               The pUserData param of the pTransFunc

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_ILLEGAL_OPERATION       If terminated.
 */
MAE_Ret SrvMsgMgrListMessageByParamInMCA(IModel *pMsgHdrLstModel,
                                       boolean bVectorModel,
                                       SMI_LIST_PARAM nParams,
                                       SMI_MSGHEADER_TRANSFER_FUNC_PTR pTransFunc,
                                       void *pUserData,
                                       SMI_SmsSimMsgBox_e SmsSimMsgBox);
/**
 SrvMsgMgrCloseListMessage
@brief  The interface of Service Client is used to free the structure "SMI_MsgHdrLst_t".

@param[in]      pMsgHdrLst              The pointer address of the message header list.
*/
void SrvMsgMgrCloseListMessage(SMI_MsgHdrLst_t *pMsgHdrLst);

/**
 SrvMsgMgrUtilBeginUpdateHeader
@brief  The interface of Service Client is used to begin the messages list session by box param.

@param[in]      nBoxParam               The list parameter for this request.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_BUSY                    If operation is busy.
@return MAE_RET_ILLEGAL_OPERATION       If terminated.
 */
MAE_Ret SrvMsgMgrUtilBeginUpdateHeader(SMI_LIST_PARAM nBoxParam);

typedef void (* SrvMsgMgrCmtUptMsgHdrCB)(void *pThis, SMI_MsgMgrStatus_e Result); //refer to post "SMI_EVT_CmtUptMsgHdrCnf"
/**
 SrvMsgMgrUtilCommitUpdateHeaderAsync
@brief  The interface of Service Client is used to commit the session which modifies header's specific information for the message.

@param[in]      pfnCallBack             SMI_EVT_CmtUptMsgHdrCnf CB func point

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_ILLEGAL_OPERATION       If an error happen.
*/
MAE_Ret SrvMsgMgrUtilCommitUpdateHeaderAsync(SrvMsgMgrCmtUptMsgHdrCB pfnCallBack);

/**
 SrvMsgMgrUtilCancelCommitUpdateHeader
@brief  The interface of Service Client is used to cancel the begin update header, or cancel the commit update header async.

@param[in]      pfnCallBack             SMI_EVT_CmtUptMsgHdrCnf CB func point

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_ILLEGAL_OPERATION       If an error happen.
*/
MAE_Ret SrvMsgMgrUtilCancelCommitUpdateHeader(SrvMsgMgrCmtUptMsgHdrCB pfnCallBack);

/**
 SrvMsgMgrIsOperationBusy
@brief  The interface of Service Client is used to check if the MSGMGR is busy for the begin - commit operation session.

@return TRUE							If it's operation busy, return TRUE;
@return FALSE							If it's not operation busy, return FALSE;
 */
boolean SrvMsgMgrIsOperationBusy(void);

/**
 SrvMsgMgrUtilDeleteMessageById
@brief  The interface of Service Client is used after begin the update session, delete the specific message with unique message ID.

@param[in]      nMsgId                  The message id for this request.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_ILLEGAL_OPERATION       If an error happen.
*/
MAE_Ret SrvMsgMgrUtilDeleteMessageById(SMI_MsgID_t nMsgId);

/**
 SrvMsgMgrUtilGetFolder
@brief  The interface of Service Client is used to get the folder information of the message.

@param[in]      nMsgId                  The message id for this request.
@param[in]      msgLoc                  The location of the message.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_ILLEGAL_OPERATION       If an error happen.
 */
MAE_Ret SrvMsgMgrUtilGetFolder(SMI_MsgID_t nMsgId, SMI_MsgLocation_e *msgLoc);

/**
 SrvMsgMgrCloseRetrieveMessageHeader
@brief  The interface of Service Client is used to close the session for retrieving the message's header information	.

@param[in]      pMsgHdr                 Pointer to the message header.
*/
void SrvMsgMgrCloseRetrieveMessageHeader(SMI_MsgHdr_t *pMsgHdr);

/**
 SrvMsgMgrGetMsgNumByMsgBoxParam
@brief  The interface of Service Client is used to get msg total, read, and sending number by valid msg box param   .

@param[in]      nMsgBoxparam            The list parameter for this request.
@param[out]     pMsgTotalNum            Return pointer of total message number.
@param[out]     pMsgReadNum             Return pointer of read message number.
@param[out]     pMsgSendingNum          Return pointer of sending message number.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_ILLEGAL_OPERATION       If terminated.
@return MAE_RET_FAILED                  If an error happen.
 */
MAE_Ret SrvMsgMgrGetMsgNumByMsgBoxParam(SMI_LIST_PARAM nMsgBoxparam,
                                        u32 *pMsgTotalNum,
                                        u32 *pMsgReadNum,
                                        u32 *pMsgSendingNum);

/**
 SrvMsgMgrCancelCnf
@brief  The interface of Service Client is used to cancel the confirm of the request    .

@param[in]      nEventID                The event id for this request. value like SMI_EVT_xxxCnf (defined in mmi_messagemanagersrv.h)
*/
void SrvMsgMgrCancelCnf(u32 nEventID);

/**
 SrvMsgMgrIsPhoneFull
@brief  The interface of Service Client is used to check if the phone message number is reached the max phone message num limitation according to message type [sms/mms/sim/push msg/CB....].

@param[in]      eMsgType                The message type for this request.

@return TRUE
@return FALSE
*/
boolean SrvMsgMgrIsPhoneFull(SMI_MsgID_Type_e eMsgType);

/**
 SrvMsgMgrResetMasterFile
@brief  The interface of Service Client is used to reset the master file and Available IDs.

@param[in]      bPowerOnReset           poweron reset or not.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_ILLEGAL_OPERATION       If terminated.
*/
MAE_Ret SrvMsgMgrResetMasterFile(boolean bPowerOnReset);

/**
 SrvMsgMgrUpdateMsgFlag
@brief  The interface of Service Client is used to Update the message Flag in the master file but don't update the reading status to TXI.

@param[in]      pMsgHdr                 The modified data of the message header.
@param[in]      eMsgLocation                The location of the message.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_ILLEGAL_OPERATION       If terminated.
 */
MAE_Ret SrvMsgMgrUpdateMsgFlag(SMI_MsgHdr_t *pMsgHdr, SMI_MsgLocation_e eMsgLocation);

typedef void (* SrvMsgMgrCopySimMsgToPhoneCB)(void *pThis, SMI_MsgMgrStatus_e eResult, SMI_SIMData_t *pSIMData); //refer to post "SMI_EVT_CopySimMsgToPhoneCnf"
/**
 SrvMsgMgrCopySimMsgToPhoneAsync
@brief  The interface of Service Client is used to copy the SIM message to phone.

@param[in]      MsgId                   The message id for the request.
@param[in]      msgLocation             The destination message location for the request.
@param[in]      pfnCallBack             SMI_EVT_CopySimMsgToPhoneCnf CB func point

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FS_FULL                 If phone full.
*/
MAE_Ret SrvMsgMgrCopySimMsgToPhoneAsync(SMI_MsgID_t nMsgId,
                                        SMI_MsgLocation_e eMsgLocation,
                                        SrvMsgMgrCopySimMsgToPhoneCB pfnCallBack);

typedef void (* SrvMsgMgrCopyPhoneMsgToSimCB)(void *pThis, SMI_MsgMgrStatus_e eOpResult, SMI_MsgID_t nMsgID); //refer to post "SMI_EVT_CopyPhoneMsgToSimCnf"
/**
 SrvMsgMgrCopyPhoneMsgToSimAsync
@brief  The interface of Service Client is used to copy the phone SMS to SIM.

@param[in]      nMsgID                  The message id for the request.
@param[in]      eOrgLoc                 The original message location for the request.
@param[in]      eDualMode               The SIM module id for the request.
@param[in]      pfnCallBack             SMI_EVT_CopyPhoneMsgToSimCnf CB func point

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_ILLEGAL_OPERATION       If terminated.
@return MAE_RET_BUSY                    If operation is busy.
@return MAE_RET_NOT_SUPPORTED
 */
MAE_Ret SrvMsgMgrCopyPhoneMsgToSimAsync(SMI_MsgID_t nMsgID,
                                        SMI_MsgLocation_e eOrgLoc,
                                        MAE_DualMode_t eDualMode,
                                        SrvMsgMgrCopyPhoneMsgToSimCB pfnCallBack);

/**
 SrvMsgMgrGetSimMsgLstInfo
@brief  The interface of Service Client is used to get the recipients' addresses and content memo for the SIM message.
        [Note]The data will alloc and copy to ppMemo; Remember to Free ppMemo by AP self

@param[in]      nMsgId                  The message id for the request.
@param[in]      eDualMode               The SIM module id for the request.
@param[out]     pRecipAddr              The pointer of SIM Message information.
@param[out]     ppMemo                  The pointer of the content memo for the request.
@param[out]     pbMoreMemo              Pointer to check if content memo exist.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_ILLEGAL_OPERATION       If terminated.
@return MAE_RET_NOT_FOUND               If msg info list not found.
 */
MAE_Ret SrvMsgMgrGetSimMsgLstInfo(u16 nMsgId,
                                  MAE_DualMode_t eDualMode,
                                  SMS_MsgRecipAddr *pRecipAddr,
                                  MAE_WChar **ppMemo,
                                  boolean *pbMoreMemo);

typedef void (* SrvMsgMgrRetrvMsgDataFromSimCB)(void *pThis, SMI_MsgMgrStatus_e eResult, SMI_SIMData_t *pSIMData); //refer to post "SMI_EVT_RetrvMsgDataFromSimCnf"
/**
 SrvMsgMgrRetrvMsgDataFromSimAsync
@brief  The interface of Service Client is used to retrieve message data from SIM; and after listen "SMI_EVT_RetrvMsgDataFromSimCnf", handle the action.

@param[in]      nMsgId              The message id for the request.
@param[in]      eMsgLocation                The location of the message for the request.
@param[in]      pfnCallBack             SMI_EVT_RetrvMsgDataFromSimCnf CB func point

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_ILLEGAL_OPERATION       If terminated.
@return MAE_RET_BUSY                    If operation is busy.
@return MAE_RET_NOT_FOUND               If msg info list not found.
 */
MAE_Ret SrvMsgMgrRetrvMsgDataFromSimAsync(u16 nMsgId,
                                          SMI_MsgLocation_e eMsgLocation,
                                          SrvMsgMgrRetrvMsgDataFromSimCB pfnCallBack);

typedef void (* SrvMsgMgrStoreMessageAsyncCB)(void *pThis, SMI_MsgMgrStatus_e eResult, SMI_MsgID_t nMsgId); //refer to post "SMI_EVT_StoreMsgCfn"
/**
 SrvMsgMgrStoreMessageAsync
@brief  The interface of Service Client is used to store phone message to SIM; and after listen "SMI_EVT_StoreMsgCfn", handle the action.

@param[in]      pStoredData             The data of the stored message for the request.
@param[in]      pfnCallBack             SMI_EVT_RetrvMsgDataFromSimCnf CB func point

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_ILLEGAL_OPERATION       If terminated.
@return MAE_RET_BUSY                    If operation is busy.
@return MAE_RET_NOT_FOUND               If msg info list not found.
 */
MAE_Ret SrvMsgMgrStoreMessageAsync(SMS_StoreData_t *pStoredData,
                                          SrvMsgMgrStoreMessageAsyncCB pfnCallBack);

typedef void (* SrvMsgMgrSendSMSAsyncCB)(void *pThis, SMI_MsgMgrStatus_e eResult, SMI_MsgID_t nMsgId); //refer to post "SMI_EVT_SendSMSCnf"
/**
 SrvMsgMgrStoreMessageAsync
@brief  The interface of Service Client is used to send via Master or Slave SIM. DUAL_MASTER or DUAL_SLAVE; and after listen "SMI_EVT_SendSMSCnf", handle the action.

@param[in]		simModule:				send via Master or Slave SIM. DUAL_MASTER or DUAL_SLAVE
@param[in]		recipient:				The recipient number address in ASCII
@param[in]		pData:					The message content data in UCS2
@param[in]		dataStrLen:				string length of the pData
@param[in]		encoding:				the SMS preferred encoding
@param[in]      pfnCallBack             SMI_EVT_SendSMSCnf CB func point

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_ILLEGAL_OPERATION       If terminated.
@return MAE_RET_BUSY                    If operation is busy.
@return MAE_RET_NOT_FOUND               If msg info list not found.
 */
MAE_Ret SrvMsgMgrSendSMSAsync(u8 simModule,
							  SMS_MsgRecipAddr *pRecipient,
							  MAE_WChar *pData,
							  u16 dataStrLen,
							  SMI_SmEncoding_t encoding,
							  SrvMsgMgrSendSMSAsyncCB pfnCallBack);

/**
 SrvMsgMgrGetMmsHdrInfo
@brief  The interface of Service Client is used to get the header information of the MMS.
        [Note]The data will alloc and copy to ppMMSHdr; Remember to Free ppMMSHdr by AP self

@param[in]      nMsgId                  The message id for the request.
@param[in]      eMsgLocation                The location of the message for the request.
@param[out]     ppMMSHdr                The pointer address of the MMS header.

@return MAE_RET_SUCCESS                 If successful.
*/
MAE_Ret SrvMsgMgrGetMmsHdrInfo(SMI_MsgID_t nMsgId,
                               SMI_MsgLocation_e eMsgLocation,
                               SMI_MmsHdr_t **ppMMSHdr);

/**
 SrvMsgMgrUpdateMmsHdrInfo
@brief  The interface of Service Client is used to update the header information of the MMS.

@param[in]      nMsgId                  The message id for the request.
@param[in]      eMsgLocation                The location of the message for the request.
@param[in]      pMsgHdr                 The pointer of the modified MMS header.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_FAILED                  If Open raw data fail / write MMS raw data fail.
*/
MAE_Ret SrvMsgMgrUpdateMmsHdrInfo(SMI_MsgID_t nMsgId,
                                  SMI_MsgLocation_e eMsgLocation,
                                  SMI_MmsHdr_t *pMsgHdr);

/**
 SrvMsgMgrDeleteInactiveSIMMsg
@brief  The interface of Service Client is used to delete the Msg in the inactive SIM.

@param[in]      eDualMode               The SIM module id for the request.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_ILLEGAL_OPERATION       If an error happen.
*/
MAE_Ret SrvMsgMgrDeleteInactiveSIMMsg(MAE_DualMode_t eDualMode);

/**
 SrvMsgMgrGetSimPduCountInfo
@brief  The interface of Service Client is used to get the SIM total and used number of PDU.

@param[in]      eDualMode               The SIM module id for the request.
@param[out]     pTotal                  Pointer to return the total number of the SIM PDU.
@param[out]     pUsed                   Pointer to return the used number of the SIM PDU.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_ILLEGAL_OPERATION       If terminated.
*/
MAE_Ret SrvMsgMgrGetSimPduCountInfo(MAE_DualMode_t eDualMode, u16 *pTotal, u16 *pUsed);

/**
 SrvMsgMgrQueryMessageFullStatus
@brief  The interface of Service Client is used to check sms/mms phone/sim full status.

@return SMI_FULL_STATUS_e
 */
SMI_FULL_STATUS_e SrvMsgMgrQueryMessageFullStatus(void);

/**
 SrvMsgMgrGetMsgNumberByType
@brief  The interface of Service Client is used to get the message number for the specific message type.

@param[in]      eMsgType                The message type for the request.
@param[in]      pMsgNumber              Pointer to return the number of the message.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_BAD_PARAM               If wrong eMsgType.
*/
MAE_Ret SrvMsgMgrGetMsgNumberByType(SMI_MsgID_Type_e eMsgType, u32 *pMsgNumber);

/**
 SrvMsgMgrGetMsgNumberByStatus
@brief  The interface of Service Client is used to get the message number for the specific message status.

@param[in]      msgLocation			The message location for the request.
									Only support : MlInbox, MlDraft, MlOutbox, MlSent, MlSim1InBox, MlSim2InBox, MlSim1Sent, MlSim2Sent now.
@param[in]      params				The message status for the request.
									Only support :  SMI_LIST_SENT, SMI_LIST_NOT_SENT, SMI_LIST_RESENT, SMI_LIST_SENT_FAIL, SMI_LIST_READ, SMI_LIST_UNREAD, 
													SMI_LIST_COMPLETE, SMI_LIST_INCOMPLETE, SMI_LIST_REMOTE_DELIVERED, SMI_LIST_REMOTE_NOT_DELIVERED,
													SMI_LIST_DELIVERED_READ, SMI_LIST_DELIVERED_NOT_READ, SMI_LIST_DELETING, SMI_LIST_NON_DELETING now.
@param[in]      pMsgNumber           Pointer to return the number of the message.

@return MAE_RET_SUCCESS                 If successful.
@return MAE_RET_BAD_PARAM               If wrong eMsgType.
*/
MAE_Ret SrvMsgMgrGetMsgNumberByStatus(SMI_MsgLocation_e msgLocation, SMI_LIST_PARAM params, u32 *pMsgNumber);
/*-----------------------------------------------------*/

#endif /* __MMI_SRV_MSGMGR_H__ */
