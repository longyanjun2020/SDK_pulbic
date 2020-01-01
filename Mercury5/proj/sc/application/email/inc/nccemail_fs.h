/**
* @file nccmail_fs.h
* NCC email FS Service Layer
*
* Service API exposed by the NCC email FS module
*
* <!-- #interface list begin -->
* \section nccmail_fs Interface
* - NCCEmail_fs_init()
* - NCCEmail_fs_getNewFilename()
* - NCCEmail_fs_getFilename()
* - NCCEmail_fs_saveNew()
* - NCCEmail_fs_saveUpdate()
* - NCCEmail_fs_loadEmail()
* - NCCEmail_fs_loadList()
* - NCCEmail_fs_deleteEmail()
* - NCCEmail_fs_deleteEmailAll()
* <!-- #interface list end -->
*/

#ifndef __NCCEMAIL_FS_H__
#define __NCCEMAIL_FS_H__
#include <nccemail_common.h>

/**
* ======= CONSTANTS AND MACROS =======
*/


/**
*    \name Return Values for NCCEmail_fs_*** functions.
*/

/*@{ */

/** composer result */
/** Email status */
/**email status in the mailbox: it is just a header and no email body.*/
#define EMAIL_FS_STATUS_HEADER          0x08
/**email status in the mailbox: it is a new email which had not been read.*/
#define EMAIL_FS_STATUS_NEW             0X01
/**email status in the mailbox: it is a new email which had been read.*/
#define EMAIL_FS_STATUS_READ            0X02
/**email status in the mailbox: it is a email which is in the sending list.*/
#define EMAIL_FS_STATUS_SENDING         0X03
/**email status in the mailbox: it is a email which is failed to sent out.*/
#define EMAIL_FS_STATUS_SENDFAILD       0X04
/**email status in the mailbox: it is a email which had been sent out.*/
#define EMAIL_FS_STATUS_SENT            0X05
/**email status in the mailbox: it is a draft email.*/
#define EMAIL_FS_STATUS_DRAFT           0X06

/** Email boxId */
/**email box ID in the mailbox: inbox*/
#define EMAIL_FS_BOXID_INBOX            0X10
/**email box ID in the mailbox: outbox*/
#define EMAIL_FS_BOXID_OUTBOX           0X20
/**email box ID in the mailbox: sentbox*/
#define EMAIL_FS_BOXID_SENTBOX          0X30
/**email box ID in the mailbox: draftbox*/
#define EMAIL_FS_BOXID_DRAFT            0X40

/** Sort support */
/**email list sorted by: datetime*/
#define EMAIL_FS_SORTBY_DATETIME    0
/**email list sorted by: subject*/
#define EMAIL_FS_SORTBY_SUBJECT     1
/**email list sorted by: sender*/
#define EMAIL_FS_SORTBY_SENDER      2
/**email list sorted by: size*/
#define EMAIL_FS_SUPPORT_SORTBY_SIZE        3

/** index list operation type */
#define EMAIL_FS_OPT_ADD_ONE        1
#define EMAIL_FS_OPT_DEL_ONE        2
#define EMAIL_FS_OPT_DEL_ALL        3
#define EMAIL_FS_OPT_UPDATE         4

#define EMAIL_ACCOUNT_MAXACCOUNTNUM         10          ///max account number
#define EMAIL_ACCOUNT_ADDR_MAXLEN           65
#define EMAIL_MAX_EMAIL_AMOUNT_IN_BOX 100
#define EMAIL_ATTACHMENT_MAXACCOUNTNUM      20          ///max ATTACHMENT number


#define  EMAIL_SETTING_SIZE_LIMIT_DEFAULT           300

#define  EMAIL_SETTING_RETRIEVAL_AMOUNT_DEFAULT     100

#define  EMAIL_SETTING_AUTOMATIC_RETRIEVAL_DEFAULT  5

/*@}*/

/**
*    \name Structure Types that are used by FS Module
*/

/** email header struct */
/*@{*/

typedef struct _EMAIL_FS_HEADER {
    int8_t * subject;      /**<the subject of the email*/
    int8_t * From;         /**<the From address of the email*/
    int8_t * To;           /**<the To address of the email*/
    int8_t * Uid;           /**<the Uid string of the email*/
    int32_t datetime;      /**<the datetime of the email*/
    int32_t size;          /**<the file size of the email data*/
    int32_t status;        /**<the status of the email*/
    int32_t boxId;         /**<the box ID of the email*/
    int32_t fileId;        /**<the filename ID of the email data file*/
    int8_t fileIdName[16];
    struct _EMAIL_FS_HEADER * next;
}T_EMAIL_FS_HEADER;
typedef struct
{
    int8_t                     EmailAddr[EMAIL_ACCOUNT_ADDR_MAXLEN];  ///  account address   
    int32_t                    AccountID;        ///account ID;
}T_EMAIL_FS_ACCOUNT_HEAD;

typedef struct
{
    int32_t                      AvailableAccNum;
    T_EMAIL_FS_ACCOUNT_HEAD      HeadList[EMAIL_ACCOUNT_MAXACCOUNTNUM];
}T_EMAIL_FS_ACCOUNT_HEAD_LIST;


/*@}*/

/*=============================================================================
 *     API Defines
 *=============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
/**
  * Initialize the FS module. This function need to be called when email system start up.
  * \param *sysPath       the system path for email, suggest it should be "/My_email"
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PATH_TOOLONG
  *                        <li>#EMAIL_FS_ALLOC_FAIL
  *                    </ul>
  *            </ul>
  */
int32_t NCCEmail_fs_init(int8_t *sysPath);

int32_t NCCEmail_ssl_init(int8_t *sslPath1, int8_t *sslPath2);

int8_t * NCCEmail_ssl_path(int32_t index);

int8_t * NCCEmail_ssl_path_auto(void);

int32_t NCCEMAIL_SSL_isSupport(void);

/**
  * Initialize the account. This function need to be called when the user create a new account
  * \param  accountId   the account ID of the store mailbox
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PATH_TOOLONG
  *                        <li>#EMAIL_FS_ALLOC_FAIL
  *                    </ul>
  *            </ul>
  */
int32_t NCCEmail_fs_CreateAccount(int32_t  accountId);

/**
  * Remove account folder. This function need to be called when the user delete a exist account
  * \param  accountId   the account ID of the store mailbox
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PATH_TOOLONG
  *                        <li>#EMAIL_FS_ALLOC_FAIL
  *                    </ul>
  *            </ul>
  */
int32_t NCCEmail_fs_DeleteAccount(int32_t accountId); 

/**
  * Load the account list header buffer from email root folder.
  * \param ppAccoutList        the  account list header  buffer,should be T_EMAIL_FS_ACCOUNT_HEAD_LIST
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PARAMETER_ERROR
  *                        <li>#EMAIL_FS_ALLOC_FAIL
  *                    </ul>
  *            </ul>
  */
int32_t NCCEmail_fs_LoadAccountList(T_EMAIL_FS_ACCOUNT_HEAD_LIST **ppAccoutList);

/**
  * save the  account list header buffer in email root folder
  * \param  pAccoutList         the AccountList data buffer ,should be struct  T_EMAIL_FS_ACCOUNT_HEAD_LIST
  * \param  buflen     the AccountList data buffer length,should be sizeof(T_EMAIL_FS_ACCOUNT_HEAD_LIST)
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PARAMETER_ERROR
  *                        <li>#EMAIL_FS_ALLOC_FAIL
  *                    </ul>
  *            </ul>
  */
int32_t NCCEmail_fs_SaveAccountList(T_EMAIL_FS_ACCOUNT_HEAD_LIST *pAccoutList ,uint32_t buflen);

/**
  * read the account setting data buffer from email root folder.
  * \param  ppAccountSetting        the Account setting data buffer,should be T_EMAIL_Account_Setting
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PARAMETER_ERROR
  *                        <li>#EMAIL_FS_ALLOC_FAIL
  *                    </ul>
  *            </ul>
  */
int32_t NCCEmail_fs_ReadAccountSetting(T_EMAIL_Account_Setting **ppAccountSetting);

/**
  * write the  account setting data buffer to  email root folder
  * \param  pAccountSetting        the  Account setting data buffer
  * \param  buflen     the  Account setting data buffer length
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PARAMETER_ERROR
  *                        <li>#EMAIL_FS_ALLOC_FAIL
  *                    </ul>
  *            </ul>
  */
    
int32_t NCCEmail_fs_WriteAccountSetting(T_EMAIL_Account_Setting  *pAccountSetting  ,uint32_t buflen);

/**
  *Load the account configuration  from account folder.
  * \param  accountId   the account ID of the store mailbox
  * \param **ppbuf          the AccountList data buffer ,should be struct T_EMAIL_Account_Config.
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PARAMETER_ERROR
  *                        <li>#EMAIL_FS_ALLOC_FAIL
  *                    </ul>
  *            </ul>
  */
int32_t NCCEmail_fs_ReadAccountCFG(int32_t accountId, T_EMAIL_Account_Config **ppCfg);

/**
  *Write the account configuration to account folder.
  * \param  accountId   the account ID of the store mailbox
  * \param *pbuf          the AccountCFG data buffer ,should be struct T_EMAIL_Account_Config.
  * \param  buflen     the AccountCFG data buffer length ,should be sizeof(T_EMAIL_Account_Config)
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PARAMETER_ERROR
  *                        <li>#EMAIL_FS_ALLOC_FAIL
  *                    </ul>
  *            </ul>
  */
int32_t NCCEmail_fs_WriteAccountCFG(int32_t accountId, T_EMAIL_Account_Config *pCfg, uint32_t buflen);

/**
  * Save new email to the mailbox.
  * \param  accountId   the account ID of the store mailbox
  * \param  boxFlag    the box ID of the store mailbox
  * \param  statusValue      the email status 
  * \param *emailbuf          the email PDU data buffer
  * \param emailbufLen        the email PDU data buffer length
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PARAMETER_ERROR
  *                        <li>#EMAIL_FS_ALLOC_FAIL
  *                    </ul>
  *            </ul>
  */
int32_t NCCEmail_fs_saveNew(int32_t accountId, int8_t *emailbuf, int32_t emailbufLen,
                                   int32_t boxFlag, int32_t statusValue, int8_t *uidStr);

int32_t NCCEmail_fs_saveNew_list(int32_t accountId,
                                T_EMAIL_FS_HEADER ** ppEmailList,
                                int8_t *emailbuf,
                                int32_t emailbufLen,
                                int32_t boxFlag,
                                int32_t statusValue);
/**
  * Save new email information to the mailbox, there was this email in the mailbox. This function used to
  * change the mail status from "NEW" to "READ", or from "SENDING" to "SENDFAILD", save new email body to
  * the current email header PDU data buffer.
  * \param  accountId   the account ID of the store mailbox
  * \param *newEmailHeader    the email header information, the information is new
  * \param *emailbuf          the email PDU data buffer, if it is empty, just update the header information.
  * \param emailbufLen        the email PDU data buffer length
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PARAMETER_ERROR
  *                        <li>#EMAIL_FS_ALLOC_FAIL
  *                    </ul>
  *            </ul>
  */
int32_t NCCEmail_fs_saveUpdate(int32_t accountId, T_EMAIL_FS_HEADER *newEmailHeader, int8_t *emailbuf, int32_t emailbufLen);

/**
  * Save new email information to the mailbox, there was this email in the mailbox. This function used to
  * change the mail status from "NEW" to "READ", or from "SENDING" to "SENDFAILD", save new email body to
  * the current email header PDU data buffer. There is the mail list as parameter.
  * \param  accountId   the account ID of the store mailbox
  * \param **ppEmailList    the email index list
  * \param *newEmailHeader    the email header information, the information is new
  * \param *emailbuf          the email PDU data buffer, if it is empty, just update the header information.
  * \param emailbufLen        the email PDU data buffer length
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PARAMETER_ERROR
  *                        <li>#EMAIL_FS_ALLOC_FAIL
  *                    </ul>
  *            </ul>
  */
int32_t NCCEmail_fs_saveUpdate_list(int32_t accountId,
                                   T_EMAIL_FS_HEADER ** ppEmailList,
                                   T_EMAIL_FS_HEADER *newEmailHeader,
                                   int8_t *emailbuf,
                                   int32_t emailbufLen);
/**
  * Load the email data buffer with special filename.
  * \param  accountId   the account ID of the store mailbox
  * \param boxId              the mailbox ID
  * \param fileId                 the file ID of the email PDU data file
  * \param *emailbuf          the email PDU data buffer
  * \param emailbufLen        the email PDU data buffer length
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PARAMETER_ERROR
  *                        <li>#EMAIL_FS_ALLOC_FAIL
  *                    </ul>
  *            </ul>
  */
int32_t NCCEmail_fs_loadEmail(int32_t accountId, int32_t boxId, int32_t fileId, int8_t **emailbuf, int32_t *emailbufLen);

/**
  * Load the mail list in special mailbox.
  * \param  accountId               the account ID of the store mailbox
  * \param  boxId                      the mailbox ID
  * \param  *total                      the email count in the mail list
  * \param  *newCount              the new email count in the mail list
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PARAMETER_ERROR
  *                        <li>#EMAIL_FS_ALLOC_FAIL
  *                    </ul>
  *            </ul>
  */
int32_t NCCEmail_fs_loadMailCount(int32_t accountId, int32_t boxId, int32_t *totalCount, int32_t *newCount);

/**
  * Load the mail list in special mailbox.
  * \param  accountId   the account ID of the store mailbox
  * \param boxId              the mailbox ID
  * \param **boxEmailList     the email list information
  * \param sortby             the sort method
  * \param startIndex       the start email id 
  * \param count                the email count to be loaded
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PARAMETER_ERROR
  *                        <li>#EMAIL_FS_ALLOC_FAIL
  *                    </ul>
  *            </ul>
  */
int32_t NCCEmail_fs_loadList(int32_t accountId, int32_t boxId, T_EMAIL_FS_HEADER ** ppEmailList, int32_t startIndex, int32_t count);

/**
  *Save the mail list in special mailbox.
  * \param  accountId   the account ID of the store mailbox
  * \param boxId              the mailbox ID
  * \param pEmailList     the email list information
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PARAMETER_ERROR
  *                        <li>#EMAIL_FS_ALLOC_FAIL
  *                    </ul>
  *            </ul>
  */

int32_t NCCEmail_fs_saveList(int32_t accountId, int32_t boxId, T_EMAIL_FS_HEADER *pEmailList);

/**
  * Update the mail list in special mailbox with special index.
  * \param accountId        account ID
  * \param boxId            mailbox ID
  * \param optType          operate type
  * EMAIL_FS_OPT_ADD_ONE: add a new email index
  * EMAIL_FS_OPT_DEL_ONE: delete one email index
  * EMAIL_FS_OPT_DEL_ALL: delete all email
  * EMAIL_FS_OPT_UPDATE: update a exist email index
  * \param **ppEmailList    email index list
  * \param *pEmailIndex     email index header
  */
int32_t NCCEmail_fs_updateList_all(int32_t accountId,
                                   int32_t boxId,
                                   int32_t optType,
                                   T_EMAIL_FS_HEADER ** ppEmailList,
                                   T_EMAIL_FS_HEADER * pEmailIndex
                                   );
/**
  * Free the mail list generate by NCCEmail_fs_loadList.
  * \param **boxEmailList     the email list information
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PARAMETER_ERROR
  *                    </ul>
  *            </ul>
  */
int32_t NCCEmail_fs_freeLoadList(T_EMAIL_FS_HEADER **ppEmailHeaderList);

/**
  * API to free one email header node
  *
  * \param ppHeaderNode [in, out]
  *	the pointer for email header
  *
  */
void NCCEmail_fs_freeEmailHeaderNode(T_EMAIL_FS_HEADER **ppHeaderNode);

/**
  * Delete the email in special mailbox with account ID.
  * \param  accountId   the account ID of the store mailbox
  * \param boxId        the mailbox ID
  * \param fileId    the file ID of the email PDU data file
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PARAMETER_ERROR
  *                        <li>#EMAIL_FS_ALLOC_FAIL
  *                    </ul>
  *            </ul>
  */
int32_t NCCEmail_fs_deleteEmail(int32_t accountId, int32_t boxId, int32_t fileId);

/**
  * Delete the email in special mailbox with account ID.
  * \param  accountId   the account ID of the store mailbox
  * \param boxId        the mailbox ID
  * \param emailIDArray    the file ID list of the email PDU data file
  * \param arrayLen    how many emails will be deleted
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PARAMETER_ERROR
  *                        <li>#EMAIL_FS_ALLOC_FAIL
  *                    </ul>
  *            </ul>
  */

int32_t NCCEmail_fs_deleteEmailList(int32_t accountId, int32_t boxId, int32_t emailIDArray[], int32_t arrayLen);


/**
  * Delete all the email in the mailbox with special box ID.
  * \param  accountId   the account ID of the store mailbox
  * \param boxId        the mailbox ID
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PARAMETER_ERROR
  *                        <li>#EMAIL_FS_ALLOC_FAIL
  *                    </ul>
  *            </ul>
  */
int32_t NCCEmail_fs_deleteEmailAll(int32_t accountId,int32_t boxId);

/**
  * Move  email from src box to  dst box.
  * \param  accountId   the account ID of the store mailbox
  * \param  DstboxId    the box ID of the destination mailbox
  * \param  SrcBoxId    the box ID of the source mailbox
  * \param  fileId          the file ID of the email PDU data file
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PARAMETER_ERROR
  *                        <li>#EMAIL_FS_ALLOC_FAIL
  *                    </ul>
  *            </ul>
  */
int32_t NCCEmail_MoveEmail(int32_t accountId, int32_t DstboxId, int32_t SrcBoxId, int32_t fileId);

#ifdef __cplusplus
}
#endif

#endif /* __NCCEMAIL_FS_H__ */
