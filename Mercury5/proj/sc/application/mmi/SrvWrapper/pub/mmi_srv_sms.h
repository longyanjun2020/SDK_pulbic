/**
* @file mmi_srv_sms.h
*
*/
#ifndef __MMI_SRV_SMS_H__
#define __MMI_SRV_SMS_H__

#include "mmi_srv_client_commondefine.h"
#include "mmi_smssrv.h"

typedef void (* SrvSmsSetScaCnfCB)(void *pThis, SMS_ScaSetting_Conf_e eResult); //SMS_EVT_SMS_SetScaCnf, SMS_Notify_Mask_ScaSetting
typedef void (* SrvSmsSendingStartCB)(void *pThis); //SMS_EVT_Message_Sending_Start, SMS_Notify_Mask_Sending_Start
typedef void (* SrvSmsSendingFinishCB)(void *pThis, u32 nSuccessSend, u32 nFailSend); //SMS_EVT_Message_Sending_Finish,SMS_Notify_Mask_Sending_Finish
typedef void (* SrvSmsSrvReadyCB)(void *pThis, COMMON_SIM_CARD_STATUS_e eSIMCardStatus); //SMS_EVT_SmsSrv_Ready,SMS_Notify_Mask_Ready
typedef void (* SrvSmsSIMChangeReadyCB)(void *pThis, COMMON_SIM_CARD_STATUS_e eSIMCardStatus); //SMS_EVT_SIMChange_Ready, SMS_Notify_Mask_SIMChange
typedef void (* SrvSmsSIMRetrieveMsgOKCB)(void *pThis);               //SMS_EVT_SIM_RetrieveMsg_OK,SMS_Notify_Mask_SIMChange
typedef void (* SrvSmsSIMDeactiveOKCB)(void *pThis, MAE_DualMode_t eDualMode);    //SMS_EVT_SIM_Deactive_OK,SMS_Notify_Mask_SIMChange
#ifdef __SMS_SEND_FROM_BUFFER__
typedef void (* SrvSmsBuffMessageAddedCB)(void *pApplet, SMI_MsgID_t nMsgId);    //SMS_EVT_BuffMessageAddedInd,SMS_Notify_Mask_BUFF_MESSAGE_IND
typedef void (* SrvSmsBuffMessageDeletedCB)(void *pApplet, SMI_MsgID_t nMsgId);    //SMS_EVT_BuffMessageDeletedInd,SMS_Notify_Mask_BUFF_MESSAGE_IND
typedef void (* SrvSmsBuffMessageMsgFlagUpdatedCB)(void *pApplet, SMI_MsgID_t nMsgId, SMI_MsgFlag eMsgFlag);    //SMS_EVT_BuffMessageMsgFlagUpdatedInd,SMS_Notify_Mask_BUFF_MESSAGE_IND
#endif /* __SMS_SEND_FROM_BUFFER__ */

/**
 SrvSmsSetSendingStartCB
@brief  The interface of Service Client is use to set CB to listen the sending start Ind

@param[in]      pfnCallBack         SrvSmsSendingStartCB Call back function point
*/
void SrvSmsSetSendingStartCB(SrvSmsSendingStartCB pfnCallBack);

/**
 SrvSmsSetSendingFinishCB
@brief  The interface of Service Client is use to set CB to listen the sending finish Ind

@param[in]      pfnCallBack         SrvSmsSendingFinishCB Call back function point
*/
void SrvSmsSetSendingFinishCB(SrvSmsSendingFinishCB pfnCallBack);

/**
 SrvSmsSetSMSSrvReadyCB
@brief  The interface of Service Client is use to set CB to listen the sms ready ind

@param[in]      pfnCallBack         SrvSmsSrvReadyCB Call back function point
*/
void SrvSmsSetSMSSrvReadyCB(SrvSmsSrvReadyCB pfnCallBack);

/**
 SrvSmsSetSetScaCnfCB
@brief  The interface of Service Client is use to set CB to listen the set service center address cnf Ind

@param[in]      pfnCallBack         SrvSmsSetScaCnfCB Call back function point
*/
void SrvSmsSetSetScaCnfCB(SrvSmsSetScaCnfCB pfnCallBack);

/**
 SrvSmsSetSIMChangeReadyCB
@brief  The interface of Service Client is use to set CB to listen the sim change Ind

@param[in]      pfnCallBack         SrvSmsSIMChangeReadyCB Call back function point
*/
void SrvSmsSetSIMChangeReadyCB(SrvSmsSIMChangeReadyCB pfnCallBack); //@@

/**
 SrvSmsSetSIMRetrieveMsgCB
@brief  The interface of Service Client is use to set CB to retrieve msg OK Ind

@param[in]      pfnCallBack         SrvSmsSIMRetrieveMsgOKCB Call back function point
*/
void SrvSmsSetSIMRetrieveMsgCB(SrvSmsSIMRetrieveMsgOKCB pfnCallBack); //@@

/**
 SrvSmsSetSIMDeactiveCB
@brief  The interface of Service Client is use to set CB to listen the Deactive Ind

@param[in]      pfnCallBack         SrvSmsSIMDeactiveOKCB Call back function point
*/
void SrvSmsSetSIMDeactiveCB(SrvSmsSIMDeactiveOKCB pfnCallBack); //@@

/**
 * SrvSmsSendMessage
 * @brief send messaeg by msgID
 * @param[in] pSentItem         pointer of msg info, MsgID/SIMModule/status
 *
 * @return MAE_RET_SUCCESS      If successful.
 */
MAE_Ret SrvSmsSendMessage(SMS_Msg_ItemData_t *pSentItem);

/**
 * SrvSmsservice_isReady
 * @brief get the sms service status,
       if not ready, register SMS_Notify_Mask_Ready[SMS_EVT_SmsSrv_Ready]
 *
 * @param[out] pbReady              return sms service ready status, bReady =1, it means sms service ready
 * @param[out] peSimCardStatus      return current SIM  status.
*/
void SrvSmsservice_isReady(boolean *pbReady, COMMON_SIM_CARD_STATUS_e *peSimCardStatus);

/**
 * SrvSmsQueryMessagesAtSendingQueue
 *
 * @brief check current sms sending status
 *
 * @param[out]  pUnSent     return unsent message number
 * @param[out]  pSending    return sending message number
*/
void SrvSmsQueryMessagesAtSendingQueue(u32 *pUnSent, u32 *pSending);

/**
 * SrvSmsQueryMessageServiceCenter
 * @brief get service center address

 * @param[out]  pSCA            return service center related info
 * @param[in]   eDualMode       query for which sim, DUAL_MASTER/DUAL_SLAVE
 *
 * @return MAE_RET_SUCCESS      If successful.
 * @return MAE_RET_BAD_PARAM    If eDualMode is not DUAL_MASTER or DUAL_SLAVE.
*/
MAE_Ret SrvSmsQueryMessageServiceCenter(Msg_SMS_Service_Center_t *pSCA, MAE_DualMode_t eDualMode);

/**
 * SrvSmsSetMessgageServiceCenter
 * @brief set service center address for certain SIM

 * @param[in] pSCA          pointer of service center related info
 * @param[in] eDualMode    set for which sim, DUAL_MASTER/DUAL_SLAVE
 *
 * @return MAE_RET_SUCCESS      If successful.
 * @return MAE_RET_BAD_PARAM    If eDualMode is not DUAL_MASTER or DUAL_SLAVE.
*/
MAE_Ret SrvSmsSetMessgageServiceCenter(Msg_SMS_Service_Center_t *pSCA, MAE_DualMode_t eDualMode);

/**
 * SrvSmsSIMSrvRetrieveIND
 * @brief Simsrv notify SMS to retrieve SIM message for sim change / power on/stkrefresh

 * @param[in] eSimCardStatus    current sim status
 * @param[in] eDualMode        retrieve which sim, DUAL_MASTER/DUAL_SLAVE
 * @param[in] bSTKRefresh       bSTKRefresh = 1, it means strkrefresh.
*/
void SrvSmsSIMSrvRetrieveIND(COMMON_SIM_CARD_STATUS_e eSimCardStatus, MAE_DualMode_t eDualMode, boolean bSTKRefresh);

/**
 * SrvSmsSIMSrvDeactiveIND
 * @brief SIM srv notify sms to deactive certain SIM

 * @param[in] eDualMode        retrieve which sim, DUAL_MASTER/DUAL_SLAVE
*/
void SrvSmsSIMSrvDeactiveIND(MAE_DualMode_t eDualMode);

/**
 * SrvSmsSIMSrvRetrieveAbort
 * @brief Simsrv notify SMS to stop retrieving

 * @param[in] eDualMode        indicate stop which sim, DUAL_MASTER/DUAL_SLAVE

 * @return MAE_RET_SUCCESS              Success
 * @return MAE_RET_ILLEGAL_OPERATION    Fail, SMI is busy
*/
MAE_Ret SrvSmsSIMSrvRetrieveAbort(MAE_DualMode_t eDualMode);

/**
 * SrvSmsSendMessagebyData
 * @brief send sms by data, sms will save and send this sms and result sent by callback function.

 * @param[in] pSendData   pointer of SMS data including content /recipient/simmodule
 * @param[in] fnSendCB    pointer of sending result callback, caller will know sending result though this callback function
                          fnSendCB = NULL, do not pass sending result. If caller close and sms waits for sending, caller has to cancel callback
 * @param[in] userData    the caller data will pass by callback "fnSendCB"
 * +pObj: for fnSendCB parameter
 *
 * @return SRVCLIENT_RET_SUCCESS        If successful.
 * @return SRVCLIENT_RET_OUT_OF_MEMORY  Failed, no memory
*/
/* for vendor service use only
MAE_Ret SrvSmsSendMessagebyData(SMS_MSG_SentData_t *pSendData,
                                   pfn_sms_send_CB pfnSendCB,
                                   u32 userData);
*/
/**
 * SrvSmsCancelCallBack
 * @brief cancel the sending result callback if caller close or do not need to care sending result.

 * @param[in] fnSendCB   pointer of sending result callback, caller will know sending result though this callback function
*/
void SrvSmsCancelCallBack(pfn_sms_send_CB pfnSendCB, u32 userData);

/**
 * SrvSmsSendSMSWithoutNotify
 * @brief send sms by data, 1.background sending without status report
                            2.the sending result does not display on Idle but pass by fnSendCB
                            3.no sms stored at sentbox(draft)


 * @param[in] SendData   pointer of SMS data including content /recipient/simmodule
 * @param[in] fnSendCB   pointer of sending result callback, caller will know sending result though this callback function
                             fnSendCB = NULL, do not pass sending result. If caller close and sms waits for sending, caller has to cancel callback
 * @param[in] userData   the caller data will pass by callback "fnSendCB"
 * +pObj: for fnSendCB parameter

 * @return SRVCLIENT_RET_SUCCESS        If successful.
 * @return SRVCLIENT_RET_OUT_OF_MEMORY  Failed, no memory

*/
MAE_Ret SrvSmsSendSMSWithoutNotify(SMS_MSG_SentData_t *pSendData,
                                      pfn_sms_send_CB  pfnSendCB,
                                      u32 userData);

/**
 * SrvSmsRegisterPort
 *  @brief register certain port to receive this port SMS by receive callback


 *  @param[in] nPort        port range 1 byte or 2 byte
 *  @param[in] eDualMode   indicate receive which SIM port SMS
 *  @param[in] pReceiveCB   receive callback funtion to receive port SMS
 *  @param[in] userData     the caller data will pass by callback "pReceiveCB", it would be NULL.
 *  @param[in] nCallerID    indicate whilch caler and caller will pass by callback "pReceiveCB", it would be instance address


 * @return SRVCLIENT_RET_SUCCESS        If successful.
 * @return SRVCLIENT_RET_FAILED         If an error happen.
 * @return SRVCLIENT_RET_BAD_PARAM      If input parameter error.
 * @return SRVCLIENT_RET_OUT_OF_MEMORY  Failed, no memory
*/
/* for vendor service use only
MAE_Ret SrvSmsRegisterPort(u32 nPort,
                           MAE_DualMode_t eDualMode,
                           pfn_sms_receive_CB pReceiveCB,
                           u32 userData,
                           u32 nCallerID);
*/
/**
 * SrvSmsDeRegisterPort
 * @brief deregister certain port not to receive this port SMS

 * @param[in] nPort         the registered one
 * @param[in] eDualMode    indicate deregister which SIM port SMS
 * @param[in] nCallerID     indicate whilch caler

 * @return SRVCLIENT_RET_SUCCESS        If successful.
 * @return SRVCLIENT_RET_FAILED         If an error happen.do not find the registered one
 * @return SRVCLIENT_RET_BAD_PARAM      If input parameter error.
*/
/* for vendor service use only
MAE_Ret SrvSmsDeRegisterPort(u32 nPort, MAE_DualMode_t eDualMode, u32 nCallerID);
*/
/**
 * SrvSmsDeRegisterAllPort
 * @brief deregister all port registered by certain caller

 * @param[in] CallerID   indicate whilch caller

 * @return SRVCLIENT_RET_SUCCESS        If successful.
 * @return SRVCLIENT_RET_FAILED         If an error happen.do not find the registered one
 * @return SRVCLIENT_RET_BAD_PARAM      If input parameter error.
*/
/* for vendor service use only
MAE_Ret SrvSmsDeRegisterAllPort(u32 nCallerID);
*/
/**
 * SrvSmsSendPushMessage
 *  @ brief send sms by data with certain port,
            1.sms send this sms and result sent by callback function.
            2. this sms donot display at message box

 * @param[in] pSendData     pointer of SMS data including content /recipient/simmodule
 * @param[in] nport         port number of message.
 * @param[in] fnSendCB      pointer of sending result callback, caller will know sending result though this callback function
                                 fnSendCB = NULL, do not pass sending result. If caller close and sms waits for sending, caller has to cancel callback
 * @param[in] userData      the caller data will pass by callback "fnSendCB"

 * @return SRVCLIENT_RET_SUCCESS        If successful.
 * @return SRVCLIENT_RET_FAILED         If an error happen.
 * @return SRVCLIENT_RET_BAD_PARAM      If input parameter error.
 * @return SRVCLIENT_RET_OUT_OF_MEMORY  Failed, no memory
*/
/* for vendor service use only
MAE_Ret SrvSmsSendPushMessage(SMS_MSG_SentData_t *pSendData,
                                 u32 nPort,
                                 pfn_sms_send_CB pfnSendCB,
                                 u32 userData);
*/

/**
 * SrvSmsGetData_byMsgID
 * @brief get message content and recipients[sender] by message ID

 * @param[in] nMsgID                message Id
 * @param[out]pData                 return SMS data [content,recipient,encoding, simModule], this pData alloc by caller

 * @return MAE_RET_SUCCESS          If successful.
*/
MAE_Ret SrvSmsGetData_byMsgID(SMI_MsgID_t  nMsgID, SMS_3rd_ReceiveData_t *pData);

/**
 * SrvSmsGetDataSize_ByMsgID
 * @brief get message content / recipient word count

 * @param[in] nMsgID        message Id
 * @param[out]pDataSize     return  word count of SMS content
 * @param[out]pTelSize      return word count of SMS recipient/sender telphone number

 * @return MAE_RET_SUCCESS          Success
 * @return MAE_RET_BAD_PARAM        Fail, error msgID
 * @return MAE_RET_NOT_SUPPORTED    Fail, pud len exceed limitation
 * @return MAE_RET_FAILED           Fail, over 9 page
 * @return MAE_RET_NOT_SUPPORTED    Fail, pud len exceed limitation
*/
MAE_Ret SrvSmsGetDataSize_ByMsgID(SMI_MsgID_t  nMsgID, u32 *pDataSize, u32 *pTelSize);

/**
 * SrvSmsRegisterTelNo
 * @brief register certain telphone number  to receive specific SMS by receive callback

 * @param[in] pTelNo        u16 string pointer of telphone number
 * @param[in] nTelNoLen     the word count of telphone number
 * @param[in] eDualMode    indicate receive which sim card
 * @param[in] pReceiveCB    receive callback function. If there is one MT sms and from the registered tel, notify through this function
 * @param[in] nUserData     It will pass by callback "pReceiveCB", apply caller to differentiate
 * @param[in] nCallerID     indicate whilch caller . It could be instance address and caller will pass by callback "pReceiveCB"

 * @return SRVCLIENT_RET_SUCCESS        Success
 * @return SRVCLIENT_RET_OUT_OF_MEMORY  Fail
 * @return SRVCLIENT_RET_FAILED Fail    there is existed one.
*/
/* for vendor service use only
MAE_Ret SrvSmsRegisterTelNo(u16 *pTelNo,
                            u8 nTelNoLen,
                            MAE_DualMode_t eDualMode,
                            pfn_sms_receive_CB pfnReceiveCB,
                            u32 userData,
                            u32 nCallerID);
*/

/**
 * SrvSmsDeRegisterTelNo
 * @brief deregister certain telphone number  not to receive specific SMS by receive callback
 
 * @param[in] pTelNo        u16 string pointer of telphone number
 * @param[in] nTelNoLen     the word count of telphone number
 * @param[in] eDualMode    indicate receive which sim card
 * @param[in] nCallerID     indicate whilch caller.

 * @return SRVCLIENT_RET_SUCCESS Success
 * @return SRVCLIENT_RET_FAILED Fail, there is no existed one.
*/
/* for vendor service use only
MAE_Ret SrvSmsDeRegisterTelNo(u16 *pTelNo,
                                 u8 nTelNoLen,
                                 MAE_DualMode_t eDualMode,
                                 u32 nCallerID);
*/
/**
  * SrvSmsDeRegisterAllTelNo
 * @brief deregister all telno. certain caller do not receive any sms.

 * @param[in] pClient       Pointer to the SMS client.
 * @param[in] nCallerID     indicate whilch caller

 * @return SRVCLIENT_RET_SUCCESS    Success
 * @return SRVCLIENT_RET_FAILED     Fail, there is no existed one.
*/
/* for vendor service use only
MAE_Ret SrvSmsDeRegisterAllTelNo(u32 nCallerID);
*/

/**
* SrvSmsIsTelNoMessage
 * @brief check if sender of the MT SMS is the registered one.
 *
 * @param[in] pTelNo        pointer of telphone number by u16 string
 * @param[in] nTelNoLen     word count of telphone number
 * @param[in] eDualMode    indicate from which SIM card
 *
 * @return TRUE         It is one SMS from  registed telNo
 * @return FALSE        not registed telNo SMS
*/
boolean SrvSmsIsTelNoMessage(u16 *pTelNo, u8 nTelNoLen, MAE_DualMode_t eDualMode);

/**
 * SrvSmsKeepTelNoMsgByID
 * @ brief delete certain Msg or move certain msg to inbox
 *
 * @param[in] nMsgId        MsgID
 * @param[in] bKeepMsg      FALSE: delete this Msg, TRUE:move this msg to Inbox
 * @param[in] nCallerID     the register caller
 *
 * @return MAE_RET_SUCCESS  success
 * @return MAE_RET_FAILED   Fail, no such Msg.
*/
MAE_Ret SrvSmsKeepTelNoMsgByID(u16 nMsgId, boolean bKeepMsg, u32 nCallerID);

/**
 * SrvSmsSendAntiStealSMS
 *  @ brief send anti steal sms by data, 1.background sending without status report
                                         2.the sending result does not display on Idle but pass by fnSendCB
                                         3.no sms stored at sentbox(draft)
 *  @ param pSendData, pointer of SMS data including content /recipient/simmodule
 *  @ param fnSendCB, pointer of sending result callback, caller will know sending result though this callback function
                                        fnSendCB = NULL, do not pass sending result. If caller close and sms waits for sending, caller has to cancel callback
 *  @ param userData, the caller data will pass by callback "fnSendCB"
*/
MAE_Ret SrvSmsSendAntiStealSMS(SMS_MSG_SentData_t *pSendData, pfn_sms_send_CB fnSendCB, IBase *pObj, u32 userData);

/**
 * SrvSmsSetAutoRejectMTMessage
 *  @ brief Set the value of the flag IsMTMessageAllowed
 *  @ param bRejectMTMessage, the flag to enable/disable receiving SMS process
*/
void SrvSmsSetAutoRejectMTMessage(boolean bRejectMTMessage);
#ifdef __SMS_SEND_FROM_BUFFER__
/**
 * sms_CancelBuffMessage
 *  @ brief cancel a waiting message
 *  @ param nMsgID, message Id

 *  @retval MAE_RET_SUCCESS Success
 *  @return MAE_RET_NOT_FOUND Failed, not found
 *  @return MAE_RET_REJECT Failed , this message is sending now
 */
MAE_Ret SrvSmsCancelBuffMessage(SMI_MsgID_t nMsgId);

/**
 * SrvSmsGetAllBuffMessageMsgIds
 *  @ brief get all the MsgIds of buff-messages
 *  @ param ppMsgIds, return a list of buff-message MsgIds
 *  @ param pMsgNum, return num of buff-messages 

 *  @retval MAE_RET_SUCCESS Success
 *  @retval MAE_RET_BAD_PARAM Failed, bad parameter
 *  @retval MAE_RET_OUT_OF_MEMORY Failed, out of memory
*/
MAE_Ret SrvSmsGetAllBuffMessageMsgIds(SMI_MsgID_t **ppMsgIds, u8 *pMsgNum);

/**
 * sms_GetBuffMessageBriefInfo
 *  @ brief get the brief info of the buff-message
 *  @ param nMsgID, message Id
 *  @ param pRecipAddr, the address of the first recipient of the buff-message
 *  @ param pIsMultiRecip, FALSE: single recipient, TRUE: multi recipients 
 *  @ param ppMemo, the front part of the buff-message content. Text truncated to SMI_MEMO_BYTE_LEN chars
 *  @ param pIsMoreMemo, FALSE: no more than SMI_MEMO_BYTE_LEN chars, TRUE: more than SMI_MEMO_BYTE_LEN chars 

 *  @retval MAE_RET_SUCCESS Success
 *  @return MAE_RET_NOT_FOUND Failed, not found
 *  @retval MAE_RET_OUT_OF_MEMORY Failed, out of memory
 */
MAE_Ret SrvSmsGetBuffMessageBriefInfo(SMI_MsgID_t nMsgId, SMS_MsgRecipAddr *pRecipAddr, boolean *pIsMultiRecip, MAE_WChar **ppMemo, boolean *pIsMoreMemo);

/**
 * SrvSmsGetBuffMessageHeader
 *  @ brief get the MsgHdr info of the specified buff-message by MsgId
 *  @ param nMsgID, message Id
 *  @ param pMsgHdr, pointer to a SMI_MsgHdr_t structure

 *  @return MAE_RET_SUCCESS Success
 *  @return MAE_RET_BAD_PARAM Failed, bad parameter
 *  @return MAE_RET_NOT_FOUND Failed, not found
*/
MAE_Ret SrvSmsGetBuffMessageHeader(SMI_MsgID_t nMsgId, SMI_MsgHdr_t *pMsgHdr);

/**
 * SrvSmsGetBuffMessageNum
 *  @ brief get the number of the buff-messages
 *  @ param bSIMSelect, need to select by SIM module
 *  @ param nSIMModule, SIM module Id

 *  @return 0 ~ MAX_BUFF_MSG_NUM
*/
u8 SrvSmsGetBuffMessageNum(boolean bSIMSelect, u8 nSIMModule);

/**
 * sms_ResendBuffMessage
 *  @ brief resend a sent-fail or sent-retry message
 *  @ param nMsgID, message Id

 *  @retval MAE_RET_SUCCESS Success
 *  @return MAE_RET_NOT_FOUND Failed, not found
 */
MAE_Ret SrvSmsResendBuffMessage(SMI_MsgID_t nMsgId);

/**
 * SrvSmsSendMessageFromBuffer
 *  @ brief send messaeg without saving
 *  @ param pSentItemEx, pointer to a SMS_Msg_ItemDataEx_t structure

 *  @return MAE_RET_SUCCESS Success
 *  @return MAE_RET_BAD_PARAM Failed, bad parameter
 *  @return MAE_RET_NOT_READY Failed, queue full
 *  @return MAE_RET_OUT_OF_MEMORY Failed, out of memory
*/
MAE_Ret SrvSmsSendMessageFromBuffer(SMS_Msg_ItemDataEx_t *pSentItemEx);

void SrvSmsSetBuffMessageAddedCB(SrvSmsBuffMessageAddedCB pfnCallBack);
void SrvSmsSetBuffMessageDeletedCB(SrvSmsBuffMessageDeletedCB pfnCallBack);
void SrvSmsSetBuffMessageMsgFlagUpdatedCB(SrvSmsBuffMessageMsgFlagUpdatedCB pfnCallBack);
#endif /* __SMS_SEND_FROM_BUFFER__ */
#endif /* __MMI_SRV_SMS_H__ */
