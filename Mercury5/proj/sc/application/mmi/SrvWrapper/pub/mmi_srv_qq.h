/**
* @file mmi_srv_qq.h
* QQ service wrapper module header files
*/

#ifndef __MMI_SRV_QQ_H__
#define __MMI_SRV_QQ_H__

#include "mmi_mae_vectormodel.h"

#include "mmi_srv_client_commondefine.h"

#include "mmi_qqsrv.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Define function pointer to trigger initializing qq client.
 *
 * \param pThis [in]
 *
 * \param status [in]
 *      The result of initializing qq client. #QQSrvErrCode_e
 */
typedef void (*SrvQQInitQQClientCB)(void *pThis, u32 status);

/**
 * Regist callback function to trigger initializing qq client operation.
 *
 * \param pFnInitQQClientCB [in]
 *      The function pointer to trigger initializing qq client
 *
 * \return #MAE_RET_SUCCES, if succeed. otherwise #MAE_RET_FAILED.
 */
MAE_Ret SrvQQSetInitQQClientReqCB(SrvQQInitQQClientCB pFnInitQQClientCB);

/**
* Request qq service to init qq client.
*
* \param nActiveSimId [in]
*       The selected SIM card's ID
*
* \return   #MAE_RET_SUCCESS, if succeed. otherwise return error code
*/
MAE_Ret SrvQQInitQQClient(u8 nActiveSimId);

/**
 * Define function pointer to trigger destroy QQ client.
 *
 * \param pThis [in]
 *
 * \param status [in]
 *      The result of destroy QQ client.#QQSrvErrCode_e
 */
typedef void (*SrvQQDestroyQQClientCB)(void *pThis, u32 status);

/**
 * Regist callback function to trigger destroy QQ client operation.
 *
 * \param pFnDestroyQQClientCB [in]
 *      The function pointer to trigger destroy qq client
 *
 * \return #MAE_RET_SUCCES, if succeed. otherwise #MAE_RET_FAILED.
 */
MAE_Ret SrvQQSetDestroyQQClientReqCB(SrvQQDestroyQQClientCB pFnDestroyQQClientCB);

/**
* Request qq service to destroy QQ client. .
*
* \return   #MAE_RET_SUCCESS, if success. otherwise return error code
*/
MAE_Ret SrvQQDestroyQQClient(void);

/**
* Request QQ service to Update qq config .
*
* \return   #MAE_RET_SUCCESS, if success. otherwise return error code
*/
MAE_Ret SrvQQUpdateQQConfig(void);

/**
 * Used to Active Query the status of QQ service.
 *
 * \param pStatus [out]
 *      Used to save the return value for QQ service status.
 *
 * \return MAE_RET_SUCCESS if succeed. otherwise return error code.
 */
MAE_Ret SrvQQGetQQSrvStatus(QQSrvStatus_e *pStatus);

/**
 * Define function pointer to trigger Logining qq.
 *
 * \param pThis [in]
 *      The instance of caller for SrvQQLogin API.
 *
 * \param status [in]
 *      The result of logining. Please see #QQSrvErrCode_e. If status is QQSRV_OK, that means
 *  successfully login on QQ server. If #QQSRV_ERR_VERIFY_REQUIRED, that means QQ server need to verify
 *  QQ client and the pResponse represents the verify data, if #QQSRV_ERR_DENIED, that means
 *  QQ server require user go to web(http://jihuo.qq.com) to active QQ account.
 *  if #QQSRV_ERR_WRONG_PASSWORD, that means password is not mismatch with QQ account.
 *  NOTE: param2 is not meanless when status is not #QQSRV_ERR_VERIFY_REQUIRED
 *
 * \param pResponse [in]
 *      The responding data to respond the logining status. if status is #QQSRV_ERR_VERIFY_REQUIRED,
 *  pResponse data represents the verify data.
 */
typedef void (*SrvQQLoginCB)(void *pThis, QQSrvErrCode_e status, u32 param2);

/**
 * Regist callback function to trigger Logining operation.
 *
 * \param pFnQQLogin [in]
 *      The function pointer to trigger qq Logining
 *
 * \return #MAE_RET_SUCCES, if succeed. otherwise #MAE_RET_FAILED.
 */
MAE_Ret SrvQQSetLoginReqCB(SrvQQLoginCB pFnQQLogin);

/**
* Request qq service to login.
*
* \param accountID [in]
*       The QQ ID number
*
* \param pPswStr [in]
*       The password string.
*
* \param bRemPsw [in]
*       Whether or not remember QQ password
*
* \param bRecvGroupMsg [in]
*       Whether or not receive QQ group message
*
* \param bHideLogin [in]
*       TRUE that means invisibility login, otherwise visibility login.
*
* \return
*   #MAE_RET_SUCCESS, if success. otherwise return error code (#MAE_RET_BUSY means
*       this QQ account has been signed on localhost)
*/
MAE_Ret SrvQQLogin(u32 accountID, u8 *pPswStr, boolean bRemPsw, boolean bRecvGroupMsg,
    boolean bHideLogin);

/**
 * Define function pointer to trigger Verifing qq .
 *
 * \param pThis [in]
 *
 * \param accountID [in]
 *      The QQ account number
 *
 * \param status [in]
 *      The result of Verifing qq.
 */
typedef void (*SrvQQVerifyCB)(void *pThis, u32 accountID, u32 status);

/**
 * Regist callback function to trigger Verifing qq operation.
 *
 * \param pFnQQVerify [in]
 *      The function pointer to trigger Verifing qq
 *
 * \return #MAE_RET_SUCCES, if succeed. otherwise #MAE_RET_FAILED.
 */
MAE_Ret SrvQQSetVerifyReqCB(SrvQQVerifyCB pFnQQVerify);

/**
* Request qq service to Verifing .
*
* \param pVerifyStr [in]
*       Verify code string
*
* \param type [in]
*       #QQSRV_VERIFY_IDENTITY or #QQSRV_VERIFY_ANSWER
*
* \return
*       #MAE_RET_SUCCESS, if success. otherwise return error code
*/
MAE_Ret SrvQQVerify(u8 *pVerifyStr, QQSrvVerifyType_e type);

/**
 * Define function pointer to trigger Logout qq
 *
 * \param pThis [in]
 *
 * \param status [in]
 *      The result of Logout qq
 */
typedef void (*SrvQQLogoutCB)(void *pThis, u32 accountID, u32 status);

/**
 * Regist callback function to trigger Logout.
 *
 * \param pFnReadQQconfig [in]
 *      The function pointer to trigger Logout
 *
 * \return #MAE_RET_SUCCES, if succeed. otherwise #MAE_RET_FAILED.
 */
MAE_Ret SrvQQSetLogoutReqCB(SrvQQLogoutCB pFnQQLogout);

/**
* Request qq service to Logout .
*
* \param accountID [in]
*       The QQ account ID of QQ client which will be logined out.
*
* \return
*       #MAE_RET_SUCCESS, if success. otherwise return error code
*/
MAE_Ret SrvQQLogout(u32 accountID);

/**
* Request qq service to get qq config .
*
* \return   #MAE_RET_SUCCESS, if success. otherwise return error code
*/
MAE_Ret SrvQQGetQQConfig(QQSrvQQConfig_t **ppConfig);

/**
* Request qq service to get qq client .
*
* \param ppClient [in, out]
*       The structure pointer to record the QQ client infomation.
*
* \return   #MAE_RET_SUCCESS, if success. otherwise return error code
*/
MAE_Ret SrvQQGetActiveQQClient(QQSrvQQClient_t **ppClient);

/**
* Request qq service to get qq client vector.
*
* \param ppClientVector [in, out]
*       The vector pointer to record the QQ client infomation.
*
* \return   #MAE_RET_SUCCESS, if success. otherwise return error code
*/
MAE_Ret SrvQQGetQQClientVector(VectorClass_t **ppClientVector);


/**
 * Define function pointer to trigger QQ client's event .
 *
 * \param pThis [in]
 *
 * \param pEvtUpdateData [in]
 *      #QQSrvEvtUpdateItem_t
 *
 */
typedef void (*SrvQQEventListener) (void *pThis, QQSrvEvtUpdateItem_t *pEvtUpdateData);

/**
 * Regist event listener after QQ successfully login on server and listener the event of QQ client
 *
 * \return   #MAE_RET_SUCCESS, if success. otherwise return error code
 */
MAE_Ret SrvQQRegEventListener(SrvQQEventListener pFnEvtListener);

/**
 * Send QQ mesage.
 *
 * \param type [in]
 *      The type of message, (#QQSRV_MSG_TYPE_BUDDY or #QQSRV_MSG_TYPE_QUN)
 *
 * \param receiverID [in]
 *      The ID of receiver
 *
 * \param pMsg [in]
 *      The string pointer of message
 *
 * \return
 *      #MAE_RET_SUCCESS if succeed. otherwise return error code
 */
MAE_Ret SrvQQSendMsg(u32 type, u32 receiverID, u8 *pMsg);

/**
 * Change QQ status.
 *
 * \param newStatus [in]
 *      The new status of QQ account
 *
 * \return
 *      MAE_RET_SUCCESS if successfully send request to QQ task. MAE_RET_FAILED if failed to send request
 */
MAE_Ret SrvQQChangeStatus(QQSrvQQStatus_e newStatus);

/**
 * Change Group Message Settings. NOTE: just for active QQ account
 *
 * \param bBlockGroupMsg
 *      TRUE means block all group messages. FALSE means receive all group messages
 */
MAE_Ret SrvQQSetGroupMsgSettings(boolean bBlockGroupMsg);

/**
 * Define function pointer to trigger the result of deleting qq buddy by id.
 *
 * \param pThis [in]
 *
 * \param id [in]
 *      The number of QQ buddy
 *
 * \param result [in]
 *      TRUE if succeed, otherwise FALSE
 */
typedef void (*SrvQQDelBuddyByIdCB) (void *pThis, u32 id, u32 result);

/**
 * Regist callback function to trigger deleting qq buddy.
 *
 * \param FnQQDelBuddyById [in]
 *      The function pointer to trigger deleting qq buddy
 *
 * \return #MAE_RET_SUCCES, if succeed. otherwise #MAE_RET_FAILED.
 */
MAE_Ret SrvQQSetDelBuddyByIdReqCB(SrvQQDelBuddyByIdCB FnQQDelBuddyById);

/**
 * Define function pointer to trigger the result of get buddy info.
 *
 * \param pThis [in]
 *
 * \param id [in]
 *      The number of QQ buddy
 *
 * \param result [in]
 *      TRUE if succeed, otherwise FALSE
 */
typedef void (*SrvQQGetBuddyInfoCB) (void *pThis, u32 id, u32 result);

/**
 * Regist callback function to trigger getting qq buddy info.
 *
 * \param FnQQDelBuddyById [in]
 *      The function pointer to trigger deleting qq buddy
 *
 * \return #MAE_RET_SUCCES, if succeed. otherwise #MAE_RET_FAILED.
 */
MAE_Ret SrvQQSetGetBuddyInfoReqCB(SrvQQGetBuddyInfoCB FnQQGetBuddyInfo);

/**
 * Send request to QQ TASK to delete specified qq buddy
 *
 * \param id [in]
 *      The number of buddy which will be deleted from buddy list
 *
 * \param isBlock [in]
 *      If block permanently
 *
 * \return
 *      #MAE_RET_SUCCESS,if successfully send request to QQ task. otherwise return error code
 */
MAE_Ret SrvQQDelBuddyById(u32 id, u8 isBlock);

typedef void (*SrvQQAddBuddyByIdCB)(void *pThis, QQSrvErrCode_e status, u32 param);

MAE_Ret SrvQQSetAddBuddyByIdReqCB(SrvQQAddBuddyByIdCB FnQQAddBuddyById);

/**
 * Add QQ buddy by QQ number
 *
 * \param id [in]
 *      The QQ number which will be added.
 *
 * \param pReqStr [in]
 *      request string.
 *
 * \return
 *      #MAE_RET_SUCCESS if successful, otherwise return error code.
 */
MAE_Ret SrvQQAddBuddyById(u32 id, u8 *pReqStr);

MAE_Ret SrvQQAddBuddyReply(u32 id, boolean isAccept);
/**
 * Send request to QQ TASK to get the detail info of qq buddy
 *
 * \param type [in]
 *      #QQSRV_MSG_TYPE_BUDDY
 *
 * \param id [in]
 *      The number of buddy which will be deleted from buddy list
 *
 * \return
 *      #MAE_RET_SUCCESS,if successfully send request to QQ task. otherwise return error code
 */
MAE_Ret SrvQQGetBuddyInfo(u32 type, u32 id);

/**
 * Define function pointer to trigger the result of loading chat history
 *
 * \param pThis [in]
 *
 * \param result [in]
 *
 *\param pVector[in]
 *      vector for saving history message string.
 *
 *      TRUE if succeed, otherwise FALSE
 */
typedef void (*SrvQQLoadChatHistoryCB) (void *pThis, u32 result, QQSrvHistoryBufferItem_t *pHistoryBufferStruct);

/**
 * Regist callback function to trigger loading qq chat history.
 *
 * \param SrvQQLoadChatHistoryCB [in]
 *      The function pointer to trigger  loading chat history
 *
 * \return #MAE_RET_SUCCES, if succeed. otherwise #MAE_RET_FAILED.
 */
MAE_Ret SrvQQSetLoadChatHistoryReqCB(SrvQQLoadChatHistoryCB FnQQLoadChatHistory);

/**
 *  Load specified qq chat history
 *
 *\param msgType [in]
 *       QQSRV_STATUS_RECV_IM_MSG or QQSRV_STATUS_RECV_QUN_MSG
 *
 * \param id [in]
 *      The number of buddy or qun
 *
 * \return
 *      #MAE_RET_SUCCESS,if successfully . otherwise return error code
 */
MAE_Ret SrvQQLoadChatHistory(u32 msgType, u32 id);

/**
 *  Delete chat history file for specified qq or qun
 *
 *\param msgType[in]
 *       QQSRV_STATUS_RECV_IM_MSG or QQSRV_STATUS_RECV_QUN_MSG
 *
 * \param id [in]
 *      The number of buddy or qun
 *
 * \return
 *      #MAE_RET_SUCCESS,if successfully  otherwise return error code
 */
MAE_Ret SrvQQCleanChatHistory(u32 msgType, u32 id);

/**
 * Expand all buddy members of specified group.
 *
 * \param groupID [in]
 *      The ID number of group.
 *
 * \return
 *      #MAE_RET_SUCCESS if successful, otherwise return error code.
 */
MAE_Ret SrvQQExpandGroupById(u32 groupID);

/**
 * Close all buddy members of specified group,So that QQ Client don't display these buddys
 *
 * \param groupID [in]
 *      The ID number of group.
 *
 * \return
 *      #MAE_RET_SUCCESS if successful. otherwise return error code.
 */
MAE_Ret SrvQQCloseGroupById(u32 groupID);

/**
 * Get All contacts list which contains qq friends and qq group
 *
 * \param ppContactsList [in, out]
 *      The VectorClass_t structure pointer to record all contacts information which contains
 *      QQ buddy and QQ group information. NOTE: can not release this vector.
 *
 * \return
 *      #MAE_RET_SUCCESS if successful, otherwise return error code.
 */
MAE_Ret SrvQQGetContactsList(VectorClass_t **ppContactsList);

/**
 * Get specified QQ buddy information structure.
 *
 * \param buddyID [in]
 *      The ID of specified QQ buddy
 *
 * \param ppBuddy [in, out]
 *      The structure pointer to record the QQ buddy's information
 *
 * \return
 *      MAE_RET_SUCCESS if successful, otherwise return error code.
 */
MAE_Ret SrvQQGetBuddyItemByNumber(u32 buddyID, QQSrvQQBuddy_t **ppBuddy);

/**
 * Get Group Item structure by specified group id.
 *
 * \param groupID [in]
 *      The number of specified group.
 *
 * \param ppGroup [in, out]
 *      The structure pointer to record specified QQ group information.
 *
 * \return
 *      #MAE_RET_SUCCESS if successful, otherwise return error code.
 */
MAE_Ret SrvQQGetGroupItemById(u32 groupID, QQSrvQQGroup_t **ppGroup);

/**
  * Get all qun list information.
  *
  * \param ppQunList [in, out]
  *     VectorClass_t pointer to record all QQ qun information. item data is #QQSrvQQQun_t
  *     NOTE: can not memory for this vector list.
  *
  * \return
  *     #MAE_RET_SUCCESS if successful, otherwise return error code.
  */
MAE_Ret SrvQQGetQunList(VectorClass_t **ppQunList);

/**
 * Get the specified QQ qun's information
 *
 * \param qunID [in]
 *      The number of QQ qun
 *
 * \param ppQun [in, out]
 *      The structure pointer of QQ qun infomation. NOTE: can not free the memory for this pointer.
 *
 * \return
 *      MAE_RET_SUCCESS if successful, otherwise return error code.
 */
MAE_Ret SrvQQGetQunItemById(u32 qunID, QQSrvQQQun_t **ppQun);

/**
 * Disalbe or enable QQ client to only show online buddy.
 *
 * \param bShowOnlineBuddyOnly [in]
 *      TRUE means just only show online buddy in contacts list and FALSE means show all
 *      buddies in contacts list
 *
 * \return
 *      #MAE_RET_SUCCESS if success, otherwise return error code(MAE_RET_XXX)
 */
MAE_Ret SrvQQSetShowOnlineBuddyOnly(u8 bShowOnlineBuddyOnly);

/**
 *  Set some QQ account to be active. If only one QQ account is logined, then it is default to be active.
 *  Only one account is active at some time.
 *
 * \param accountID [in]
 *      The QQ account ID of QQ account which will be set as active.
 *
 * \return
 *      #MAE_RET_SUCCESS if successful, otherwise error code.
 */
MAE_Ret SrvQQSetActiveQQAccount(u32 accountID);

#ifdef __cplusplus
}
#endif

#endif //__MMI_SRV_QQ_H__

