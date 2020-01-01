/**
* @file mmi_srv_email.h
* 	email service wrapper module header files
*/

#ifndef __MMI_SRV_EMAIL_H__
#define __MMI_SRV_EMAIL_H__

#include "mmi_mae_vectormodel.h"

#include "mmi_srv_client_commondefine.h"
#include "mmi_emailsrv.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The APIs is used to query actively the status of some email account.
 *
 * \param accountID [in]
 *	The ID of email account
 *
 * \param pStatusInfo [out]
 *	The status of email account #EMAILSRV_AccountStatusInfo_t
 *
 * \return
 *      #MAE_RET_SUCCESS if successful, otherwise return error code.
 */
MAE_Ret SrvEmailGetAccountStatus(u32 accountID, EMAILSRV_AccountStatusInfo_t *pStatusInfo);

/**
 * Function pointer to trigger the progress change of email service
 *
 * \param pThis [in]
 *
 * \param pProgressInfo [in]
 *	the progress info of email service
 *
 */
typedef void (*EmailSrvSendReceiveCB)(void *pThis, EMAILSRV_AccountStatusInfo_t *pProgressInfo);

/**
 * The APIs is used to set call back function pointer which will be triggered when the progress changed for email service
 *
 * \param pFnProgressChangeCB [in]
 *	the function point to notify owner the email service progress has changed
 *
 * \return #MAE_RET_SUCCESS if successful, otherwise #MAE_RET_FAILED
 */
MAE_Ret SrvEmailSetSendReceiveCB(EmailSrvSendReceiveCB pFnProgressChangeCB);

/**
 * Email UI or other email AP can call this API to add sending task into email service
 *
 * \param emailAccountID [in]
 *	which email account should be operated
 *
 * \return #MAE_RET_SUCCESS, if success. otherwise return error code
 *
 */
MAE_Ret SrvEmailSendAll(u32 emailAccountID);

/**
 * Email UI or other email ap can call this API to send one email which located in outbox
 *
 * \param emailAccountID [in]
 *      Sending email belong to which email account
 *
 * \param emailID [in]
 *      The email message ID will be sent.
 */
MAE_Ret SrvEmailSendOne(u32 emailAccountID, u32 emailID);

/**
 * Email UI or other email AP can call this API to send receiving request to Email service to retrieve all email messages
 *
 * \param emailAccountID [in]
 *	which email acccount should be retrieved
 *
 * \return #MAE_RET_SUCCESS, if success. otherwise return error code
 *
 */
MAE_Ret SrvEmailReceiveAll(u32 emailAccountID);

/**
 * Send one cancel request to Email service to cancel send/receive task for specified email account.
 *
 * \param emailAccountID [in]
 *  which email account should be cancelled
 *
 * \return #MAE_RET_SUCCESS and wait to callback for cancelling request, if succeed, otherwise return error code
 */
MAE_Ret SrvEmailCancelSendReceive(u32 emailAccountID);

/**
 * Function pointer for reading email account list callback.
 *
 * \param pThis [in]
 *
 * \param pEmailAccountList [in]
 *      The structure pointer to point to the header of  email account list.
 *
 * \param status [in]
 *      Specify the result of reading email account list operation. #MAE_RET_SUCCESS if success, otherwise #MAE_RET_FAILED
 */
typedef void (*EmailSrvReadEmailAccountListCB)(void *pThis, T_EMAIL_FS_ACCOUNT_HEAD_LIST *pEmailAccountList, u32 status);

/**
 * Regist callback function into email service to trigger reading email account list operation.
 *
 * \param pFnReadEmailAccountListCB [in]
 *      the function point to notify email UI the result of reading email account list.
 *
 * \return
 *      #MAE_RET_SUCCESS, if success,otherwise #MAE_RET_FAILED.
 */
MAE_Ret SrvEmailSetReadEmailAccountListCB(EmailSrvReadEmailAccountListCB pFnReadEmailAccountListCB);

/**
 * Read the account list header buffer from email root folder.
 *
 *\return #MAE_RET_SUCCESS, if success. otherwise return error code
 */
MAE_Ret SrvEmailReadEmailAccountList(void);

/**
 * Function pointer to read configuration for specified email account.
 *
 * \param pThis [in]
 *
 * \param pEmailAccountCfg [in]
 *      The structure pointer(#T_EMAIL_Account_Config) for email account configuration.
 * NOTE: This memory should be freed by UI.
 *
 * \param status [in]
 *      The result of reading email account configuration. #MAE_RET_SUCCESS, if success, otherwise #MAE_RET_FAILED.
 */
typedef void (*EmailSrvReadEmailAccountCfgCB)(void *pThis, T_EMAIL_Account_Config *pEmailAccountCfg, u32 status);

/**
 * Set callback function to trigger the result of reading email account configuration.
 *
 * \param pFnReadEmailAccountCfgCB [in]
 *  The function point to notify email UI the result of reading email account configuration.
 *
 * \return
 *      #MAE_RET_SUCCESS if succeed, otherwise return #MAE_RET_FAILED
 */
MAE_Ret SrvEmailSetReadEmailAccountCfgCB(EmailSrvReadEmailAccountCfgCB pFnReadEmailAccountCfgCB);

/**
 * Read the account configuration  from account folder.
 *
 * \param  emailAccountID   the account ID of the store mailbox
 *
 * \return #MAE_RET_SUCCESS, if success. otherwise return error code
 */
MAE_Ret SrvEmailReadEmailAccountCfg(u32 emailAccountID);

/**
 * Define function pointer to trigger the result of saving email account configuration.
 *
 * \param pThis [in]
 *
 * \param status [in]
 *      The result of saving email account configuration, #MAE_RET_SUCCESS if succeed,otherwise #MAE_RET_FAILED.
 */
typedef void (*EmailSrvWriteEmailAccountCfgCB)(void *pThis,  u32 status);

/**
 * Set callback to trigger result of saving email account configuration.
 *
 * \param  pFnWriteEmailAccountCfgCB [in]
 *      The function point to notify email UI the result of saving email account configuration.
 *
 * \return #MAE_RET_SUCCESS, if success. otherwise return error code
 */
MAE_Ret SrvEmailSetWriteEmailAccountCfgCB(EmailSrvWriteEmailAccountCfgCB pFnWriteEmailAccountCfgCB);

/**
 *Write the account configuration to account folder.
 * \param  emailAccountID   the account ID of the store mailbox
 * \param *pEmailAccountCfg         the AccountCFG data buffer ,should be struct T_EMAIL_Account_Config.
 *
 * \return #MAE_RET_SUCCESS, if success. otherwise return error code
 */
MAE_Ret SrvEmailWriteEmailAccountCfg(u32 emailAccountID, T_EMAIL_Account_Config *pEmailAccountCfg);

/**
 * Define the function pointer to trigger the result of saving email account information.
 *
 * \param pThis [in]
 *
 * \param status [in]
 *      The result of saving email account information. #MAE_RET_SUCCESS, if succeed. otherwise #MAE_RET_FAILED.
 */
typedef void (*EmailSrvWriteEmailAccountInfoCB)(void *pThis,  u32 status);

/**
 * Set callback to trigger the result of saving email account information.
 *
 * \param pFnWriteEmailAccountInfoCB [in]
 *      The function pointer for callback of saving email account information.
 *
 * \return
 *      #MAE_RET_SUCCESS, if succeed. otherwise #MAE_RET_FAILED.
 */
MAE_Ret SrvEmailSetWriteEmailAccountInfoCB(EmailSrvWriteEmailAccountInfoCB pFnWriteEmailAccountInfoCB);

/**
 * Send one request to email service to save email account information for specified email account.
 *
 * \param NewAccount [in]
 *      The flag to identify if the email account is new created.
 *
 * \param emailAccountID [in]
 *      Specify which email account should be updated. If the email account is new, it won't be used.
 *
 * \param pEmailAccountList [in]
 *      The structure pointer to point to the header of T_EMAIL_FS_ACCOUNT_HEAD_LIST list.
 *
 * \param pEmailAccountCfg [in]
 *      The structure pinter to point to the new email account information structure.
 *
 * \return
 *      #MAE_RET_SUCCESS, if succeed. otherwise return#MAE_RET_FAILED.
 */
MAE_Ret SrvEmailWriteEmailAccountInfo(boolean NewAccount, u32 emailAccountID, T_EMAIL_FS_ACCOUNT_HEAD_LIST *pEmailAccountList, T_EMAIL_Account_Config *pEmailAccountCfg);

/**
 * Define function pointer to trigger the result of reading email settings.
 *
 * \param pThis [in]
 *
 * \param pEmailSetting [in]
 *      The structure pointer for T_EMAIL_Account_Setting structure. NOTE: the memory should be freed.
 *
 *  \param status [in]
 *      The result of reading email settings operation. #MAE_RET_SUCCESS if succeed. otherwise #MAE_RET_FAILED.
 */
typedef void (*EmailSrvReadEmailSettingCB)(void *pThis, T_EMAIL_Account_Setting *pEmailSetting, u32 status);

/**
 * Set callback to trigger the result of reading email setting.
 *
 * \param pFnReadEmailSettingCB [in]
 *      The function pointer to trigger the result of reading email setting.
 *
 * \return
 *      #MAE_RET_SUCCESS, if succeed. otherwise #MAE_RET_FAILED
 */
MAE_Ret SrvEmailSetReadEmailSettingCB(EmailSrvReadEmailSettingCB pFnReadEmailSettingCB);

/**
 * Send one request to Email service to read email settings.
 *
 * \return #MAE_RET_SUCCESS if succeed. otherwise #MAE_RET_FAILED.
 */
MAE_Ret SrvEmailReadEmailSetting(void);

/**
 * Define function pinter to trigger the result of saving email setting operation.
 *
 * \param pThis [in]
 *
 * \param status [in]
 *      The result of savingn email setting operation. #MAE_RET_SUCCESS if succeed. otherwise #MAE_RET_FAILED.
 */
typedef void (*EmailSrvWriteEmailSettingCB)(void *pThis,  u32 status);

/**
 * Regist callback function to trigger saving email settings operation.
 *
 * \param pFnWriteEmailSettingCB [in]
 *      The function pointer to trigger saving email settings.
 *
 * \return #MAE_RET_SUCCES, if succeed. otherwise #MAE_RET_FAILED.
 */
MAE_Ret SrvEmailSetWriteEmailSettingCB(EmailSrvWriteEmailSettingCB pFnWriteEmailSettingCB);

/**
* write the  account list header buffer to email root folder
* \param  *pEmailAccountList[in]
*the AccountList data buffer ,should be struct  T_EMAIL_FS_ACCOUNT_HEAD_LIST
*
* \return   #MAE_RET_SUCCESS, if success. otherwise return error code
*/
MAE_Ret SrvEmailWriteEmailSetting(T_EMAIL_Account_Setting *pEmailSetting);

/**
 * Define function pointer to trigger delete email account operation.
 *
 * \param pThis [in]
 *
 * \param status [in]
 *      The result of deleting email account operation.
 */
typedef void (*EmailSrvDeleteEmailAccountCB)(void *pThis,  u32 status);

/**
 * Regist callback function to trigger deleting email account operation.
 *
 * \param pFnDeleteEmailAccount [in]
 *      The function pointer to trigger deleting email account.
 *
 * \return #MAE_RET_SUCCES, if succeed. otherwise #MAE_RET_FAILED.
 */
MAE_Ret SrvEmailSetDeleteEmailAccountCB(EmailSrvDeleteEmailAccountCB pFnDeleteEmailAccount);

/**
* Request email service to delete email account
*
*\param   emailAccountID[in]
*which email account should be deleted.
*
* \param  *pEmailAccountList[in]
*the AccountList data buffer ,should be struct  T_EMAIL_FS_ACCOUNT_HEAD_LIST
*
* \return   #MAE_RET_SUCCESS, if success. otherwise return error code
*/
MAE_Ret SrvEmailDeleteEmailAccount(u32 emailAccountID, T_EMAIL_FS_ACCOUNT_HEAD_LIST *pEmailAccountList);

/**
 * Define function pointer to trigger sorting email operation.
 *
 * \param pThis [in]
 *
 * \param status [in]
 *      The result of deleting email account operation.
 */
typedef void (*EmailSrvSortEmailHeaderListCB)(void *pThis,  u32 status);

/**
 * Regist callback function to trigger sorting email operation.
 *
 * \param pFnSortEmailHeaderList [in]
 *      The function pointer to trigger sorting email
 *
 * \return #MAE_RET_SUCCES, if succeed. otherwise #MAE_RET_FAILED.
 */
MAE_Ret SrvEmailSetSortEmailHeaderListCB(EmailSrvSortEmailHeaderListCB pFnSortEmailHeaderList);

/**
* Request email service to sort email in box.
*
*\param   boxId[in]
*     which email box should be sorted.
*
* \param  sortBy[in]
*    email list sorted by
*
* \return   #MAE_RET_SUCCESS, if success. otherwise return error code
*/
MAE_Ret SrvEmailSortEmailHeaderList(u32 boxId, u32 sortBy);

/**
 * Define function pointer to trigger deleting  email operation.
 *
 * \param pThis [in]
 *
 * \param status [in]
 *      The result of deleting email account operation.
 */
typedef void (*EmailSrvDeleteEmailCB)(void *pThis,  u32 status);

/**
 * Regist callback function to trigger deleting email operation.
 *
 * \param pFnDeleteEmail [in]
 *      The function pointer to trigger deleting email
 *
 * \return #MAE_RET_SUCCES, if succeed. otherwise #MAE_RET_FAILED.
 */
MAE_Ret SrvEmailSetDeleteEmailCB(EmailSrvDeleteEmailCB pFnDeleteEmail);

/**
* Request email service to delete email
*
*\param   emailList[in]
*   the emai list which will be deleted
*
*\param   emailNum[in]
*the amount of emailList
*
*\param   boxId[in]
*which email box should be sorted.
*
* \return   #MAE_RET_SUCCESS, if success. otherwise return error code
*/
MAE_Ret SrvEmailDeleteEmail(u32 *emailList, u32 emailNum, u32 boxId);

/**
 * Define function pointer to trigger updating  email  status operation.
 *
 * \param pThis [in]
 *
 * \param status [in]
 *      The result of deleting email account operation.
 */
typedef void (*EmailSrvMarkEmailAsReadCB)(void *pThis,  u32 status);

/**
 * Regist callback function to trigger updating email  status operation.
 *
 * \param pFnUpdateEmailList [in]
 *      The function pointer to trigger updating email  status
 *
 * \return #MAE_RET_SUCCES, if succeed. otherwise #MAE_RET_FAILED.
 */
MAE_Ret SrvEmailSetMarkEmailAsReadCB(EmailSrvMarkEmailAsReadCB pFnUpdateEmailList);

/**
* Request email service to update email  status
*
* \param boxID [in]
*   mailbox ID
*
* \param emailID [in]
*   email message ID.
*
* \param isRead [in]
*       read flag
*
* \return   #MAE_RET_SUCCESS, if success. otherwise return error code
*/
MAE_Ret SrvEmailMarkEmailAsRead(u32 boxID, u32 emailID, u8 isRead);


/**
 * Function pointer to trigger the result for opening email account ID
 *
 * \param pThis [in]
 *
 * \param emailAccountID [in]
 *	The ID of email account which has been opened
 *
 * \param status [in]
 *	The result for opening the email account
 */
typedef void (*EmailSrvOpenEmailAccountCB)(void *pThis, u32 emailAccountID, u32 status);

/**
 * The APIs is used to set call back function pointer which will be triggered when the specified email account has been opened
 *
 * \param pFnOpenEmailAccountCB [in]
 *	The function pointer to notify email AP that the specified email account has been opened or not
 *
 * \return #MAE_RET_SUCCESS if successful, otherwise #MAE_RET_FAILED
 */
MAE_Ret SrvEmailSetOpenEmailAccountCB(EmailSrvOpenEmailAccountCB pFnOpenEmailAccountCB);

/**
 * Email AP can call this API to open the specified email account
 *
 * \param emailAccountID [in]
 *	the ID for specified email account
 *
 *
 * \return #MAE_RET_SUCCESS, if success, otherwise return MAE_RET_FAILED
 */
MAE_Ret SrvEmailOpenEmailAccount(u32 emailAccountID);

/**
 * Email Ap can call this API to close opened email account
 *
 * \param emailAccountID
 *	current opened email account
 */
MAE_Ret SrvEmailCloseEmailAccount(u32 emailAccountID);

/**
* Request email service to get email account
*
*\param   pUnreadItems[out]
*   the count of unread email in inbox
*
*\param   *pSendingItems[out]
*   the count of sending  email in inbox
*
*\param  *pTotalItems[out]
*   the count of  email in inbox
*
* \return   #MAE_RET_SUCCESS, if success. otherwise return error code
*/
MAE_Ret SrvEmailGetInboxItemsCount(u32 *pUnreadItems, u32 *pSendingItems, u32 *pTotalItems);

/**
* Request email service to get email account
*
*\param   pUnreadItems[out]
*   the count of unread email in Draftbox
*
*\param   *pSendingItems[out]
*   the count of sending  email in Draftbox
*
*\param  *pTotalItems[out]
*   the count of  email in Draftbox
*
* \return   #MAE_RET_SUCCESS, if success. otherwise return error code
*/
MAE_Ret SrvEmailGetDraftboxItemsCount(u32 *pUnreadItems, u32 *pSendingItems, u32 *pTotalItems);

/**
* Request email service to get email account
*
*\param   pUnreadItems[out]
*   the count of unread email in Outbox
*
*\param   *pSendingItems[out]
*   the count of sending  email in Outbox
*
*\param  *pTotalItems[out]
*   the count of  email in Outbox
*
* \return   #MAE_RET_SUCCESS, if success. otherwise return error code
*/
MAE_Ret SrvEmailGetOutboxItemsCount(u32 *pUnreadItems, u32 *pSendingItems, u32 *pTotalItems);

/**
* Request email service to get email account
*
*\param   pUnreadItems[out]
*   the count of unread email in Sentbox
*
*\param   *pSendingItems[out]
*   the count of sending  email in Sentbox
*
*\param  *pTotalItems[out]
*   the count of  email in Sentbox
*
* \return   #MAE_RET_SUCCESS, if success. otherwise return error code
*/
MAE_Ret SrvEmailGetSentboxItemsCount(u32 *pUnreadItems, u32 *pSendingItems, u32 *pTotalItems);

/**
* Request email service to get email header list in inbox
*
*\param   **ppVector[out]
*   the list of email header list in inbox.
*
* \return   #MAE_RET_SUCCESS, if success. otherwise return error code
*/
MAE_Ret SrvEmailGetInBoxHeaderList(VectorClass_t **ppVector);

/**
* Request email service to get email header list in DraftBox
*
*\param   **ppVector[out]
*   the list of email header list in DraftBox.
*
* \return   #MAE_RET_SUCCESS, if success. otherwise return error code
*/
MAE_Ret SrvEmailGetDraftBoxHeaderList(VectorClass_t **ppVector);

/**
* Request email service to get email header list in OutBox
*
*\param   **ppVector[out]
*   the list of email header list in OutBox.
*
* \return   #MAE_RET_SUCCESS, if success. otherwise return error code
*/
MAE_Ret SrvEmailGetOutBoxHeaderList(VectorClass_t **ppVector);

/**
* Request email service to get email header list in SentBox
*
*\param   **ppVector[out]
*   the list of email header list in SentBox.
*
* \return   #MAE_RET_SUCCESS, if success. otherwise return error code
*/
MAE_Ret SrvEmailGetSentBoxHeaderList(VectorClass_t **ppVector);

/**
 * Function pointer to trigger the result for opening email
 *
 * \param pThis [in]
 *
 * \param emailAccountID [in]
 *	The ID of email account which has been opened
 *
 * \param status [in]
 *	The result for opening the email account
 */
typedef void (*EmailSrvOpenEmailCB) (void *pThis, u32 status, u32 emailAccountID, u32 boxID, u32 msgID, void *emailHandle);

/**
 * Regist the callback function to trigger the result of opening email.
 *
 * \param pFnOpenEmailCB [in]
 *      The function pointer of the API to trigger the result of opening email operation.
 *
 * \return #MAE_RET_SUCCESS if succeed. otherwise #MAE_RET_FAILED.
 */
MAE_Ret SrvEmailSetOpenEmailCB(EmailSrvOpenEmailCB pFnOpenEmailCB);

/**
 * Send one request to email service to open the specified email.
 *
 * \param boxID [in]
 *      The ID of email box (EMAIL_FS_BOXID_INBOX, EMAIL_FS_BOXID_OUTBOX, EMAIL_FS_BOXID_SENTBOX, EMAIL_FS_BOXID_DRAFT).
 *
 * \param msgID [in]
 *     The ID of email msg.
 *
 * \return #MAE_RET_SUCCESS, if succeed. otherwise #MAE_RET_FAILED.
 */
MAE_Ret SrvEmailOpenEmail(u32 boxID, u32 msgID, u32 isOnlyHeader);

/**
 * Function pointer to trigger the result of saving email data
 *
 */
typedef void (*EmailSrvSaveEmailDataCB) (void *pThis, u32 status);

/**
 * Regist callback function to trigger the saving email data operation.
 *
 * \param pFnSaveEmailDataCB [in]
 *      The function pointer of EmailSrvSaveEmailDataCB.
 *
 * \return #MAE_RET_SUCCESS, if succeed. otherwise #MAE_RET_FAILED.
 */
MAE_Ret SrvEmailSetSaveEmailDataCB(EmailSrvSaveEmailDataCB pFnSaveEmailDataCB);

/**
 * Send one request to email service to save email data
 *
 * \param accountID [in]
 *      The ID of email account.
 *
 *  \param boxID [in]
 *      Specify the email folder to save email data.
 *
 * \param msgID [in]
 *      The ID of email msg. if the email is new, it won't be used.
 *
 *  \param isNew [in]
 *      Specify if the email is new or old.
 *
 * \param pBuf [in]
 *      Point to the email buffer.
 *
 * \param bufLen [in]
 *      Specify the length of email buffer
 *
 * \return #MAE_RET_SUCCESS if succeed. otherwise #MAE_RET_FAILED.
 */
MAE_Ret SrvEmailSaveEmailData(u32 accountID, u32 boxID, u32 msgID, boolean isNew, u8 *pBuf, u32 bufLen);

#ifdef __cplusplus
}
#endif

#endif //__MMI_SRV_EMAIL_H__

