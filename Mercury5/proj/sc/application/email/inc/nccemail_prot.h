/**
* @file nccmail_prot.h
* NCC email protocol Service Layer
*
* Service API exposed by the NCC mms protocol module
*
* <!-- #interface list begin -->
* \section nccmail_prot Interface
* - NCCEmail_cps_createNew()
* - NCCEmail_cps_reedit()
* - NCCEmail_cps_quit()
* - NCCEmail_cps_addFrom()
* - NCCEmail_cps_addTo()
* - NCCEmail_cps_addCc()
* - NCCEmail_cps_addBcc()
* - NCCEmail_cps_addReplyto()
* - NCCEmail_cps_addSubject()
* - NCCEmail_cps_setPriority()
* - NCCEmail_cps_addTextContent()
* - NCCEmail_cps_addHtmlContent()
* - NCCEmail_cps_addAutoSign()
* - NCCEmail_cps_getAddressStr()
* - NCCEmail_cps_getFromStr()
* - NCCEmail_cps_getToStr()
* - NCCEmail_cps_getCcStr()
* - NCCEmail_cps_getBccStr()
* - NCCEmail_cps_getBccStr()
* - NCCEmail_cps_getSubject()
* - NCCEmail_cps_getDateTime()
* - NCCEmail_cps_getPriority()
* - NCCEmail_cps_getTextContent()
* - NCCEmail_cps_getHtmlContent()
* - NCCEmail_cps_getAutosign()
* - NCCEmail_cps_addAttachment()
* - NCCEmail_cps_getAttachmentTotal()
* - NCCEmail_cps_getAttachmentByIndex()
* - NCCEmail_cps_getAttachmentByName()
* - NCCEmail_cps_getEmailData()
* <!-- #interface list end -->
*/

#ifndef __NCCEMAIL_PROT_H__
#define __NCCEMAIL_PROT_H__

#include <nccemail_common.h>
#include <nccport_i18n.h>


/**
* ======= CONSTANTS AND MACROS =======
*/

/**
*    \name Return Values for NCCEmail_cps_*** functions.
*/

/*@{ */

/** composer result */
/**Return code that indicates successful completion of an operation*/
#define EMAIL_CPS_SUCCESS            0
/**Return code indicates that current operation is failed*/
#define EMAIL_CPS_FAILED             -1
/**Return code that indicates failure completion of allocating memory*/
#define EMAIL_CPS_ALLOC_FAIL         -2
/**Return code indicates that param error */
#define EMAIL_CPS_PARAMETER_ERROR    -3
/**Return code indicates that there is no this content*/
#define EMAIL_CPS_NO_THIS_CONTENT    -4
/**Return code indicates that the subject length is out of max length*/
#define EMAIL_CPS_OUTOFSUBJECTLENGTH		-5
/**Return code indicates that the date time format is invalid*/
#define EMAIL_CPS_INVALIDDATETIME			-6
/**Return code indicates that the address "To" length is out of max length*/
#define EMAIL_CPS_OUTOFADDRESSEELENGTH	    -7
/**Return code indicates that the address "Cc" length is out of max length*/
#define EMAIL_CPS_OUTOFCOPYADDRESSLENGTH	-8
/**Return code indicates that the address "Bcc" length is out of max length*/
#define EMAIL_CPS_OUTOFCONFIDENTIALLENGTH	-9
/**Return code indicates that the attachment number is out of max count*/
#define EMAIL_CPS_OUTOFATTACHNO			    -10
/**Return code indicates that the receiver is empty*/
#define EMAIL_CPS_NORECEIVER                -11
/**Return code indicates that the username is empty*/
#define EMAIL_CPS_USERNAMEEMPTY			    -12
/**Return code indicates that the password is empty*/
#define EMAIL_CPS_PASSWORDEMPTY			    -13
/**Return code indicates that the charset type is unsupported*/
#define EMAIL_CPS_UNSUPPORTED_CHARSET       -14
#define EMAIL_CPS_INVALID_DATA              -15
/**Return code indicates that the format of mailbox is invalid*/
#define EMAIL_CPS_INVALID_MAILBOX           -16
/*@}*/

/**
*    \name Char set type string value.
*/

/*@{ */

/**
* Define a enum type to refer to s_FieldNameArray, The order of the enum must consistent
* with the order of s_FieldNameArray
* \sa s_FieldNameArray
*/
typedef enum {
    EMAIL_FIELD_TYPE_UNKNOWN = 0,
    EMAIL_FIELD_TYPE_BCC,
    EMAIL_FIELD_TYPE_CC,
    EMAIL_FIELD_TYPE_COMMENTS,
    EMAIL_FIELD_TYPE_CONTENT_DESCRIPTION,
    EMAIL_FIELD_TYPE_CONTENT_DISPOSITION,
    EMAIL_FIELD_TYPE_CONTENT_ID,
    EMAIL_FIELD_TYPE_CONTENT_TRANSFER_ENCODING,
    EMAIL_FIELD_TYPE_CONTENT_TYPE,
    EMAIL_FIELD_TYPE_ORIG_DATE,
    EMAIL_FIELD_TYPE_FROM,
    EMAIL_FIELD_TYPE_IN_REPLY_TO,
    EMAIL_FIELD_TYPE_KEYWORDS,
    EMAIL_FIELD_TYPE_MESSAGE_ID,
    EMAIL_FIELD_TYPE_MIME_VERSION,
    EMAIL_FIELD_TYPE_REFERENCES,
    EMAIL_FIELD_TYPE_REPLY_TO,
    EMAIL_FIELD_TYPE_RESENT_BCC,
    EMAIL_FIELD_TYPE_RESENT_CC,
    EMAIL_FIELD_TYPE_RESENT_DATE,
    EMAIL_FIELD_TYPE_RESENT_FROM,
    EMAIL_FIELD_TYPE_RESENT_MSG_ID,
    EMAIL_FIELD_TYPE_RESENT_SENDER,
    EMAIL_FIELD_TYPE_RESENT_TO,
    EMAIL_FIELD_TYPE_RETURN,
    EMAIL_FIELD_TYPE_SENDER,
    EMAIL_FIELD_TYPE_SENT,
    EMAIL_FIELD_TYPE_SUBJECT,
    EMAIL_FIELD_TYPE_TO,
    EMAIL_FIELD_TYPE_TRACE,
    EMAIL_FIELD_TYPE_X_PRIORITY
} EMAIL_FIELD_TYPE;

/*@}*/

typedef enum {
    EMAIL_PRIORITY_HIGHEST = 1,
    EMAIL_PRIORITY_HIGH,
    EMAIL_PRIORITY_NORMAL,
    EMAIL_PRIORITY_LOW,
    EMAIL_PRIORITY_LOWEST
} EMAIL_PRIORITY;
/**
*=======Data Structures are used by Protocol Module=======
*/

/**
*    \name Structure Types that are used by Protocol Module
*/

/** email address struct */
/*@{*/

typedef struct _T_EMAIL_MailBox {
    int8_t *name;                  /**<the name with charset encoding*/
    int32_t nameLen;                /**<the name length with charset encoding*/

    int8_t *address;               /**<the address with charset encoding*/
    int32_t addressLen;             /**<the address length with charset encoding*/
} T_EMAIL_MailBox;

/**
*  Structured Type that defines Basic information for address content resource,it is used by Protocol Module
*/
typedef struct _T_EMAIL_MailBox_Node {
    T_EMAIL_MailBox content;

    struct _T_EMAIL_MailBox_Node * next;
} T_EMAIL_MailBox_Node;

/**
 *  Structured Type that defines Basic information for address list resource,it is used by Protocol Module
 */
typedef struct _EMAIL_Address_List {
    int32_t total;               /**<the total count of the address list*/

    T_EMAIL_MailBox_Node *next;  /**<the address list*/
} T_EMAIL_MailBox_List;

typedef struct _EMAIL_Attachment_Content {
    int8_t *pFilename;      /**< The filename for attachment file*/
    int8_t *pContentType;   /**< The Content-Type value for attachment file*/

    int8_t *pData;          /**< The file data for attachment. NOTE: the data must be UTF-8 charset*/
    int32_t dataLen;        /**< The length of attachment data*/
} T_EMAIL_Attachment_Content;

/**
 *  Structure to save attachment related information
 */
typedef struct _EMAIL_Attachment_Node {
    T_EMAIL_Attachment_Content content;

    struct _EMAIL_Attachment_Node *next;
}T_EMAIL_Attachment_Node;

/**
 * The sturcture list for attachments
 */
typedef struct _EMAIL_Attachment {
    int32_t total;                      /**< The total count of the attachment list*/

    T_EMAIL_Attachment_Node *next; /**< The first attachment node of attachment list*/
}T_EMAIL_Attachment_List;

/*@}*/

/**EMAIL information structure*/
typedef struct T_EMAIL_HANDLE * EMAIL_HANDLE;

/*=============================================================================
*     API Defines
*=============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This API will be deprecated
 */
int32_t NCCEmail_initialize(void);

/**
 * Create a new email handle,alloc memory space for the EMAIL Handle
 *
 * \param *CPSHandle [out]
 *          The handle of the email
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *          <li>#EMAIL_CPS_ALLOC_FAIL
 *      </ul>
 */
int32_t NCCEmail_cps_createNew(EMAIL_HANDLE *CPSHandle);

/**
 * Reedit a email which has existed,fill cur email's struct with current
 * email pdu.NOTE: must call NCCEmail_cps_createNew to malloc memory for
 * email handle before call this API
 *
 * \param    CPSHandle [in, out]
 *              Structure pointer which save reedit email
 *
 * \param    *pData [in]
 *              The pdu of reedit email
 *
 * \param    dataLen [in]
 *              The length of email PDU, TRUE or FALSE
 *
 * \param    justHeader [in]
 *              Whether just reedit the header
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS, if succeed
 *          <li>#EMAIL_CPS_PARAMETER_ERROR, if invalid parameter
 *          <li>#EMAIL_CPS_ALLOC_FAIL, if memory leak
 *          <li>#EMAIL_CPS_FAILED
 *      </ul>
 *
 * \sa NCCEmail_cps_createNew
 */
int32_t NCCEmail_cps_reedit(EMAIL_HANDLE CPSHandle, const int8_t *pData,
    const int32_t dataLen, const int32_t justHeader);

/**
* Reply a email to the sender which has existed,fill cur email's struct with current
* email pdu.NOTE: must call NCCEmail_cps_createNew and NCCEmail_cps_reedit to malloc memory for
* email handle before call this API
*
* \param    CPSHandle [in, out]
*              Structure pointer which save reedit email
*
* \return
*      <ul>
*          <li>#EMAIL_CPS_SUCCESS, if succeed
*          <li>#EMAIL_CPS_PARAMETER_ERROR, if invalid parameter
*          <li>#EMAIL_CPS_ALLOC_FAIL, if memory leak
*          <li>#EMAIL_CPS_FAILED
*      </ul>
*
* \sa NCCEmail_cps_createNew
* \sa NCCEmail_cps_reedit
*/
int32_t NCCEmail_cps_reply(EMAIL_HANDLE CPSHandle);

/**
* Reply a email to all the addresses which has existed,fill cur email's struct with current
* email pdu.NOTE: must call NCCEmail_cps_createNew and NCCEmail_cps_reedit to malloc memory for
* email handle before call this API
*
* \param    CPSHandle [in, out]
*              Structure pointer which save reedit email
*
* \return
*      <ul>
*          <li>#EMAIL_CPS_SUCCESS, if succeed
*          <li>#EMAIL_CPS_PARAMETER_ERROR, if invalid parameter
*          <li>#EMAIL_CPS_ALLOC_FAIL, if memory leak
*          <li>#EMAIL_CPS_FAILED
*      </ul>
*
* \sa NCCEmail_cps_createNew
* \sa NCCEmail_cps_reedit
*/
int32_t NCCEmail_cps_replyall(EMAIL_HANDLE CPSHandle);

/**
* Forward a email which has existed,fill cur email's struct with current
* email pdu.NOTE: must call NCCEmail_cps_createNew and NCCEmail_cps_reedit to malloc memory for
* email handle before call this API
*
* \param    CPSHandle [in, out]
*              Structure pointer which save reedit email
*
* \return
*      <ul>
*          <li>#EMAIL_CPS_SUCCESS, if succeed
*          <li>#EMAIL_CPS_PARAMETER_ERROR, if invalid parameter
*          <li>#EMAIL_CPS_ALLOC_FAIL, if memory leak
*          <li>#EMAIL_CPS_FAILED
*      </ul>
*
* \sa NCCEmail_cps_createNew
* \sa NCCEmail_cps_reedit
*/
int32_t NCCEmail_cps_forward(EMAIL_HANDLE CPSHandle);

/**
 * Destroy email handle
 *
 * \param *CPSHandle [in, out]
 *          The handle of the current email
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *      </ul>
 */
int32_t NCCEmail_cps_quit(EMAIL_HANDLE *CPSHandle);

/**
 * Add new address into FROM field. Note: has one and only one mailbox in From field. If there is one mailbox is existed
 * in From field when add another mailbox into From field. the new mailbox will replace old one.
 *
 * \param CPSHandle [in, out]
 *          Structure pointer to save email information
 *
 * \param *pAddrContent [in]
 *          T_EMAIL_MailBox structure pointer to save mailbox information
 *
 * \return
 *      <ul>
 *         <li>#EMAIL_CPS_SUCCESS
 *         <li>#EMAIL_CPS_PARAMETER_ERROR
 *         <li>#EMAIL_CPS_ALLOC_FAIL
 *      </ul>
 */
int32_t NCCEmail_cps_addFrom(EMAIL_HANDLE CPSHandle, const T_EMAIL_MailBox *pAddrContent);

/**
 * Add new address into TO field
 *
 * \param CPSHandle [in, out]
 *          Structure pointer to save email information
 *
 * \param *pAddrContent [in]
 *          T_EMAIL_MailBox structure pointer to save mailbox information
 *
 * \return
 *      <ul>
 *         <li>#EMAIL_CPS_SUCCESS
 *         <li>#EMAIL_CPS_PARAMETER_ERROR
 *         <li>#EMAIL_CPS_ALLOC_FAIL
 *      </ul>
 */
int32_t NCCEmail_cps_addTo(EMAIL_HANDLE CPSHandle, const T_EMAIL_MailBox *pAddrContent);

/**
 * Add new address into CC field
 *
 * \param CPSHandle [in, out]
 *          Structure pointer to save email information
 *
 * \param *pAddrContent [in]
 *          T_EMAIL_MailBox structure pointer to save mailbox information
 *
 * \return
 *      <ul>
 *         <li>#EMAIL_CPS_SUCCESS
 *         <li>#EMAIL_CPS_PARAMETER_ERROR
 *         <li>#EMAIL_CPS_ALLOC_FAIL
 *      </ul>
 */
int32_t NCCEmail_cps_addCc(EMAIL_HANDLE CPSHandle, const T_EMAIL_MailBox *pAddrContent);

/**
 * Add new address into BCC field
 *
 * \param CPSHandle [in, out]
 *          Structure pointer to save email information
 *
 * \param *pAddrContent [in]
 *          T_EMAIL_MailBox structure pointer to save mailbox information
 *
 * \return
 *      <ul>
 *         <li>#EMAIL_CPS_SUCCESS
 *         <li>#EMAIL_CPS_PARAMETER_ERROR
 *         <li>#EMAIL_CPS_ALLOC_FAIL
 *      </ul>
 */
int32_t NCCEmail_cps_addBcc(EMAIL_HANDLE CPSHandle, const T_EMAIL_MailBox *pAddrContent);

/**
 * Add new address into reply-to field
 *
 * \param CPSHandle [in, out]
 *          Structure pointer to save email information
 *
 * \param *pAddrContent [in]
 *          T_EMAIL_MailBox structure pointer to save mailbox information
 *
 * \return
 *      <ul>
 *         <li>#EMAIL_CPS_SUCCESS
 *         <li>#EMAIL_CPS_PARAMETER_ERROR
 *         <li>#EMAIL_CPS_ALLOC_FAIL
 *      </ul>
 */
int32_t NCCEmail_cps_addReplyto(EMAIL_HANDLE CPSHandle, const T_EMAIL_MailBox *pAddrContent);

/**
 * Add subject into email struct.
 *
 * \param CPSHandle [in]
 *          The handle of the email
 *
 * \param pSubject [in]
 *          The subject string. encoded in utf8 charset
 *
 * \param  subjectLen [in]
 *          The length of subject string
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *          <li>#EMAIL_CPS_ALLOC_FAIL
 *      </ul>
 */
int32_t NCCEmail_cps_addSubject(EMAIL_HANDLE CPSHandle, const int8_t *pSubject, const int32_t subjectLen);

/**
 * set the priority into email struct
 *
 * \param CPSHandle [in]
 *          the handle of the email
 *
 * \param priority [in]
 *          the priority of the email #EMAIL_PRIORITY
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *      </ul>
 */
int32_t NCCEmail_cps_setPriority(EMAIL_HANDLE CPSHandle, EMAIL_PRIORITY priority);

/**
 * Add text plain content into email struct
 *
 * \param CPSHandle [in]
 *          The handle of the email
 *
 * \param pTextContent [in]
 *          The data of text plain content. NOTE: encoded in utf-8
 *
 * \param textContentLen [in]
 *          The length of text plain content
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *          <li>#EMAIL_CPS_ALLOC_FAIL
 *      </ul>
 */
int32_t NCCEmail_cps_addTextContent(EMAIL_HANDLE CPSHandle, const int8_t *pTextContent, const int32_t textContentLen);

/**
 * Add html content into email struct
 *
 * \param CPSHandle [in]
 *          The handle of the email
 *
 * \param pHtmlContent [in]
 *          The data of html content
 *
 * \param htmlContentlen [in]
 *          The length of html content
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *          <li>#EMAIL_CPS_ALLOC_FAIL
 *      </ul>
 */
int32_t NCCEmail_cps_addHtmlContent(EMAIL_HANDLE CPSHandle,
    const int8_t *pHtmlContent, const int32_t htmlContentLen);

/**
 * Add auto sign into email struct
 *
 * \param  CPSHandle [in]
 *          The handle of the email
 *
 * \param  pAutoSign [in]
 *          The data of auto sign. NOTE: encoded in utf-8
 *
 * \param autoSignLen [in]
 *          The length of auto sign
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *          <li>#EMAIL_CPS_ALLOC_FAIL
 *      </ul>
 */
int32_t NCCEmail_cps_addAutoSign(EMAIL_HANDLE CPSHandle, const int8_t *pAutoSign, const int32_t autoSignLen);

/**
 * Add one attachment into attachment list of email
 *
 * \param CPSHandle [in]
 *          The handle of the email
 *
 * \param  pAttachment [in]
 *          the point of the attachment
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *          <li>#EMAIL_CPS_ALLOC_FAIL
 *      </ul>
 */
int32_t NCCEmail_cps_addAttachment(EMAIL_HANDLE CPSHandle, T_EMAIL_Attachment_Content *pAttachment);

/**
 * Get the address string for specified field
 *
 * \param CPSHandle [in, out]
 *          The structure pointer to save email information
 *
 * \param ppAddrStr [out]
 *          The string point for mailbox list. such as "\"display name\" <mstar@mstarsemi.com>, mstar@mstarsemi.com"
 *          NOTE: should free this memory
 *
 * \param pAddrStrLen [out]
 *          The string length of address list string
 *
 * \param type [in]
 *          The address type, such as From, To, Cc, Bcc or ReplyTo
 *
 * \return
 *          <ul>
 *                <li>#EMAIL_CPS_SUCCESS
 *                <li>#EMAIL_CPS_PARAMETER_ERROR
 *                <li>#EMAIL_CPS_ALLOC_FAIL
 *           </ul>
 */
int32_t NCCEmail_cps_getAddressStr(EMAIL_HANDLE CPSHandle, EMAIL_FIELD_TYPE type,
    int8_t **ppAddrStr, int32_t *pAddrStrLen);

/**
 * Get the address list as string for FROM field
 *
 * \param CPSHandle [in]
 *          The structure pointer to save email information
 *
 * \param ppAddrStr [out]
 *          The string pointer to save mailbox list.NOTE: should free this memory
 *
 * \param pAddrStrLen [out]
 *          The string length of mailbos list string
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *          <li>#EMAIL_CPS_ALLOC_FAIL
 *      </ul>
 */
int32_t NCCEmail_cps_getFromStr(EMAIL_HANDLE CPSHandle, int8_t **ppAddrStr, int32_t *pAddrStrLen);

/**
 * Get the mailbox list from FROM field. Can not free the memory of T_EMAIL_MailBox_list
 *
 * \param CPSHandle [in]
 *          The handle of the email
 *
 * \return the pointer of #T_EMAIL_MailBox_List if succeed. otherwise return NULL
 */
T_EMAIL_MailBox_List *NCCEmail_cps_getFromList(EMAIL_HANDLE CPSHandle);

/**
 * Get the address list as string for TO field
 *
 * \param CPSHandle [in]
 *          The structure pointer to save email information
 *
 * \param ppAddrStr [out]
 *          The string pointer to save mailbox list. NOTE: should free this memory
 *
 * \param pAddrStrLen [out]
 *          The string length of mailbos list string
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *          <li>#EMAIL_CPS_ALLOC_FAIL
 *      </ul>
 */
int32_t NCCEmail_cps_getToStr(EMAIL_HANDLE CPSHandle, int8_t **ppAddrStr, int32_t *pAddrStrLen);

/**
 * Get the mailbox list from TO field. Can not free the memory of T_EMAIL_MailBox_list
 *
 * \param CPSHandle [in]
 *          The handle of the email
 *
 * \return the pointer of #T_EMAIL_MailBox_List if succeed. otherwise return NULL
 */
T_EMAIL_MailBox_List *NCCEmail_cps_getToList(EMAIL_HANDLE CPSHandle);

/**
 * Get the address list as string for CC field
 *
 * \param CPSHandle [in]
 *          The structure pointer to save email information
 *
 * \param ppAddrStr [out]
 *          The string pointer to save mailbox list. NOTE:should free this memory
 *
 * \param pAddrStrLen [out]
 *          The string length of mailbos list string
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *          <li>#EMAIL_CPS_ALLOC_FAIL
 *      </ul>
 */
int32_t NCCEmail_cps_getCcStr(EMAIL_HANDLE CPSHandle, int8_t **ppAddrStr, int32_t *pAddrStrLen);

/**
 * Get the mailbox list from CC field. NOTE: can not free the memory of T_EMAIL_MailBox_list
 *
 * \param CPSHandle [in]
 *          The handle of the email
 *
 * \return the pointer of #T_EMAIL_MailBox_List if succeed. otherwise return NULL
 */
T_EMAIL_MailBox_List *NCCEmail_cps_getCcList(EMAIL_HANDLE CPSHandle);

/**
 * Get the address list as string for BCC field
 *
 * \param CPSHandle [in]
 *          The structure pointer to save email information
 *
 * \param ppAddrStr [out]
 *          The string pointer to save mailbox list. NOTE:should free this memory
 *
 * \param pAddrStrLen [out]
 *          The string length of mailbos list string
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *          <li>#EMAIL_CPS_ALLOC_FAIL
 *      </ul>
 */
int32_t NCCEmail_cps_getBccStr(EMAIL_HANDLE CPSHandle, int8_t **ppAddrStr, int32_t *pAddrStrLen);

/**
 * Get the mailbox list from BCC field. NOTE:can not free the memory of T_EMAIL_MailBox_list
 *
 * \param CPSHandle [in]
 *          The handle of the email
 *
 * \return the pointer of #T_EMAIL_MailBox_List if succeed. otherwise return NULL
 */
T_EMAIL_MailBox_List *NCCEmail_cps_getBccList(EMAIL_HANDLE CPSHandle);

/**
 * Get the address list as string for Replay-To field
 *
 * \param CPSHandle [in]
 *          The structure pointer to save email information
 *
 * \param ppAddrStr [out]
 *          The string pointer to save mailbox list. NOTE:should free this memory block
 *
 * \param pAddrStrLen [out]
 *          The string length of mailbos list string
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *          <li>#EMAIL_CPS_ALLOC_FAIL
 *      </ul>
 */
int32_t NCCEmail_cps_getReplyToStr(EMAIL_HANDLE CPSHandle, int8_t **ppAddrStr, int32_t *pAddrStrLen);

/**
 * Get the mailbox list from reply-to field. NOTE:can not free the memory of T_EMAIL_MailBox_list
 *
 * \param CPSHandle [in]
 *          The handle of the email
 *
 * \return the pointer of #T_EMAIL_MailBox_List if succeed. otherwise return NULL
 */
T_EMAIL_MailBox_List *NCCEmail_cps_getReplytoList(EMAIL_HANDLE CPSHandle);

/**
 * Get the subject from the email struct
 *
 * \param CPSHandle [in]
 *          The handle of the email
 *
 * \param ppSubject [out]
 *          The subject string of this email. NOTE: can not be free this memory block
 *
 * \param pSubjectLen [out]
 *          The length of subject string
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *      </ul>
 */
int32_t NCCEmail_cps_getSubject(EMAIL_HANDLE CPSHandle, int8_t **ppSubject, int32_t *pSubjectLen);

/**
 * Get the seconds (in UTC) from the email struct
 *
 * \param CPSHandle [in]
 *          The handle of the email
 *
 * \return Greater than zero if succeed. other wise less than zero
 */
int32_t NCCEmail_cps_getDateTime(EMAIL_HANDLE CPSHandle);

/**
 * Get the priority of email
 *
 * \param CPSHandle [in]
 *      The handle of the email
 *
 * \return #EMAIL_PRIORITY if success. otherwise return#EMAIL_CPS_PARAMETER_ERROR
 */
int32_t NCCEmail_cps_getPriority(EMAIL_HANDLE CPSHandle);

/**
 * Get the text plain content from the email struct
 *
 * \param CPSHandle [in]
 *          The handle of the email
 *
 * \param ppTextContent [out]
 *          The text plain content of this email. NOTE: can not be freed
 *
 * \param pTextContentLen [out]
 *          The length of text plain content of this email
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *      </ul>
 */
int32_t NCCEmail_cps_getTextContent(EMAIL_HANDLE CPSHandle, int8_t **ppTextContent, int32_t *pTextContentLen);

/**
 * Get the html content from the email struct
 *
 * \param CPSHandle [in]
 *          The handle of the email
 *
 * \param ppHtmlContent [out]
 *          The point of the html content. NOTE: can not be freed
 *
 * \param pHtmlContentLen [out]
 *          The length of the html content
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *      </ul>
 */
int32_t NCCEmail_cps_getHtmlContent(EMAIL_HANDLE CPSHandle, int8_t **ppHtmlContent, int32_t *pHtmlContentLen);

/**
 * Get the auto sign information from the email struct
 *
 * \param CPSHandle [in]
 *          The handle of the email
 *
 * \param ppSignData [out]
 *          The point of the auto sign. NOTE: can not be freed
 *
 * \param pDataLen [out]
 *          The length of sign data
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *      </ul>
 */
int32_t NCCEmail_cps_getAutosign(EMAIL_HANDLE CPSHandle, int8_t **ppSignData, int32_t *pDataLen);

/**
 * Get the total number of attachment in this email
 *
 * \param CPSHandle [in]
 *          Structure pointer of T_EMAIL_HANDLE
 *
 * \return greater  than or equal to zero if success. otherwise less than zero
 */
int32_t NCCEmail_cps_getAttachmentTotal(EMAIL_HANDLE CPSHandle);

/**
 * Get the attachment content by index from the email struct. NOTE: the return structure pointer can not be freed
 *
 * \param CPSHandle [in]
 *          The structure pointer of T_EMAIL_HANDLE
 *
 * \param index [in]
 *          The location of attachment which located in attachment list. NOTE: index is begin from 1......
 *
 * \return The structure pointer of #T_EMAIL_Attachment_Content if succeed. otherwise return NULL
 */

T_EMAIL_Attachment_Content *NCCEmail_cps_getAttachmentByIndex(EMAIL_HANDLE CPSHandle, const int32_t index);

/**
 * Get the attachment content by name from the email struct. NOTE: the return pointer can not be freed
 *
 * \param CPSHandle [in]
 *          The structure pointer of T_EMAIL_HANDLE
 *
 * \param pAttachmentName [in]
 *          The name of attachment
 *
 * \return The structure pointer of #T_EMAIL_Attachment_Content if succeed. otherwise return NULL
 */
T_EMAIL_Attachment_Content *NCCEmail_cps_getAttachmentByName(EMAIL_HANDLE CPSHandle,
    const int8_t *pAttachmentName);

/**
 * Get the email binary PDU by the email struct
 *
 * \param CPSHandle [in]
 *          The structure pointer of EMAIL_HANDLE
 *
 * \param ppEmailData [out]
 *          The pointer to save email binary data. NOTE: should free this memory block after used
 *
 * \param pEmailDataLen [out]
 *          The length of email binary data.
 *
 * \return
 *      <ul>
 *          <li>#EMAIL_CPS_SUCCESS
 *          <li>#EMAIL_CPS_FAILED
 *          <li>#EMAIL_CPS_PARAMETER_ERROR
 *      </ul>
 */
int32_t NCCEmail_cps_getEmailData(EMAIL_HANDLE CPSHandle, int8_t **ppEmailData, int32_t *pEmailDataLen);

/**
 * Destroy one mailbox structure
 *
 * \param pNode
 *      point to the #T_EMAIL_MailBox_Node structure
 *
 */
void NCCEmail_cps_freeMailBoxNode(T_EMAIL_MailBox_Node *pNode);

/**
 * Destroy mailbox list structure. NOTE: don't free memory for header node
 *
 * \param pAddrList
 *      point to the #T_EMAIL_MailBox_list header
 *
 */
void NCCEmail_cps_freeMailBoxList(T_EMAIL_MailBox_List *pAddrList);

#ifdef __cplusplus
}
#endif

#endif /* __NCCEMAIL_PROT_H__ */
