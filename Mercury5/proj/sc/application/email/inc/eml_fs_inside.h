/**
* @file eml_fs_inside.h
* NCC email FS internal Layer
*
* Internal API unexposed by the NCC email FS module
*/
#ifndef __EML_FS_INSIDE_H__
#define __EML_FS_INSIDE_H__
#include <nccemail_common.h>

/** Email index flag string */
#define EMAIL_FS_FLAG_TOTAL         "Total:"
#define EMAIL_FS_FLAG_TOTAL_LEN     6
#define EMAIL_FS_FLAG_NEWCOUNT      "New:"
#define EMAIL_FS_FLAG_NEWCOUNT_LEN  4

//#define EMAIL_FS_FLAG_FILENAME      "Filename:"
#define EMAIL_FS_FLAG_FILEID        "FileId:"
#define EMAIL_FS_FLAG_FILEID_LEN    7
#define EMAIL_FS_FLAG_DATETIME      "DateTime:"
#define EMAIL_FS_FLAG_DATETIME_LEN  9
#define EMAIL_FS_FLAG_SUBJECT       "Subject:"
#define EMAIL_FS_FLAG_SUBJECT_LEN       8
#define EMAIL_FS_FLAG_FROM          "From:"
#define EMAIL_FS_FLAG_FROM_LEN      5
#define EMAIL_FS_FLAG_TO            "To:"
#define EMAIL_FS_FLAG_TO_LEN        3
#define EMAIL_FS_FLAG_SIZE          "Size:"
#define EMAIL_FS_FLAG_SIZE_LEN      5
#define EMAIL_FS_FLAG_STATUS        "Status:"
#define EMAIL_FS_FLAG_STATUS_LEN    7
#define EMAIL_FS_FLAG_UID           "Uid:"
#define EMAIL_FS_FLAG_UID_LEN       4

#define EMAIL_FS_FLAG_ENDLINE       "\r\n"
#define EMAIL_FS_FLAG_ENDLINE_LEN   2
#define EMAIL_FS_FLAG_TWOENDLINE       "\r\n\r\n"
#define EMAIL_FS_FLAG_TWOENDLINE_LEN   4

/** Macro for file system */
#define EMAIL_FS_EMAIL_DUMMY_LEN    50*1024

#define EMAIL_FS_MAX_ACCOUNT_NUM    20
#define EMAIL_FS_MAX_PATH_LEN       230
#define EMAIL_FS_MAX_FILEPATH_LEN   262 //not bigger than MAX_FILENAME_LEN
#define EMAIL_FS_EMAIL_COUNT_LEN    4
#define EMAIL_FS_DEFAULT_SYSTEM_DIR "/My Email"

#define EMAIL_FS_INBOX_DIR          "/inbox"
#define EMAIL_FS_OUTBOX_DIR         "/outbox"
#define EMAIL_FS_SENTBOX_DIR        "/sentbox"
#define EMAIL_FS_DRAFT_DIR          "/draftbox"

#define EMAIL_FS_DUMMY              "/dummy"
#define EMAIL_FS_UIDL_INDEX         "uidl.index"
#define EMAIL_FS_ACCOUNTS_LIST      "/accounts.index"
#define EMAIL_FS_ACCOUNTS_SETTING   "/settings.index"
#define EMAIL_FS_ACCOUNT_CFG        "accountcfg.index"
#define EMAIL_FS_INBOX_INDEX        "inbox.index"
#define EMAIL_FS_OUTBOX_INDEX       "outbox.index"
#define EMAIL_FS_SENTBOX_INDEX      "sent.index"
#define EMAIL_FS_DRAFT_INDEX        "draft.index"

#define EMAIL_FS_ACCOUNTS_PROTECT_LIST      "/temp_accounts.index"
#define EMAIL_FS_ACCOUNTS_PROTECT_SETTING   "/temp_settings.index"
#define EMAIL_FS_ACCOUNT_PROTECT_CFG        "temp_accountcfg.index"
#define EMAIL_FS_INBOX_PROTECT_INDEX        "temp_inbox.index"
#define EMAIL_FS_OUTBOX_PROTECT_INDEX       "temp_outbox.index"
#define EMAIL_FS_SENTBOX_PROTECT_INDEX      "temp_sent.index"
#define EMAIL_FS_DRAFT_PROTECT_INDEX        "temp_draft.index"


//static int8_t fs_email_dir[EMAIL_FS_MAX_FILEPATH_LEN] = {0};

#ifdef __cplusplus
extern "C" {
#endif
int32_t CreateFileInEmailBox(int32_t accountId, int32_t BoxId);

void par_freeHeadlist(T_EMAIL_FS_HEADER **parEmailList, T_EMAIL_FS_HEADER *newEmailHeader);

int32_t par_addEmailList(T_EMAIL_FS_HEADER ** boxEmailList,T_EMAIL_FS_HEADER * addEmailheader, int32_t sortby);

int32_t par_delEmailList(T_EMAIL_FS_HEADER ** boxEmailList,T_EMAIL_FS_HEADER ** delEmailheader, int32_t fileId);

int32_t par_getEmailListBuffer(T_EMAIL_FS_HEADER * boxEmailList, int8_t ** headerBuf, int32_t * headerBufLen);

int32_t par_loadEmailList(T_EMAIL_FS_HEADER ** boxEmailList, int32_t * totalCount, int32_t * newCount,
                          int8_t * emailbuf, int32_t emailbufLen, int32_t startIndex, int32_t count);
/**
  * Generate the email file name.
  * \param boxId                  the box ID of the store mailbox
  * \param *outFileId          the generated filename
  * \param *boxEmailHeaderList    the current mail list in this mailbox
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PARAMETER_ERROR
  *                        <li>#EMAIL_FS_ALLOC_FAIL
  *                    </ul>
  *            </ul>
  */
int32_t Email_fs_getNewFilename(int32_t boxId, int32_t * outFileId, T_EMAIL_FS_HEADER * boxEmailHeaderList);

/**
  * Generate the full file name.
  * \param  accountId   the account ID of the store mailbox
  * \param boxId          the box ID of the store mailbox
  * \param *ppoutFilename  the generated filename, it should be a string array.
  * \param *pinFilename    the filename with no path
  * \return    <ul>
  *                <li>when successful,return#EMAIL_FS_SUCCESS
  *                <li>when fail,return
  *                    <ul>
  *                        <li>#EMAIL_FS_PARAMETER_ERROR
  *                        <li>#EMAIL_FS_ALLOC_FAIL
  *                    </ul>
  *            </ul>
  */
int32_t Email_fs_getFullFilename(int32_t accounId,int32_t boxId, int8_t * poutFilename, int8_t * pinFilename);

#ifdef __cplusplus
}
#endif

#endif /* __EML_FS_INSIDE_H__ */
