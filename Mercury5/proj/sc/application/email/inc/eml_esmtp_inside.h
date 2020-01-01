/**
* @file eml_esmtp_inside.h
* NCC email esmtp internal Layer
*
* Internal API unexposed by the NCC email esmtp module
*/
#ifndef __EML_ESMTP_INSIDE_H__
#define __EML_ESMTP_INSIDE_H__
#include <nccemail_common.h>
#include <nccemail_prot.h>

/** define address type */
#define ESMTP_ADDRESS_FROM  0
#define ESMTP_ADDRESS_TO    1
#define ESMTP_ADDRESS_CC    2
#define ESMTP_ADDRESS_BCC   3

/** email system macros */
#define EMAIL_MAXATTACHMENTNO			5	//the maximum of attachment
#define EMAIL_MAXSUBJECTLENGTH		1000//the maximum length of the subject
#define EMAIL_DATETIMELENGTH			31	//the length of the time string
#define EMAIL_MAXSENDERLENGTH			50	//the maximum of address
#define EMAIL_MAXADDRESSEELENGTH		500	//the maximum length of all address
#define EMAIL_MAXRECEIVEDMAILSIZE		(30*1024)//the maximum of received email size
//#define EMAIL_ESMTP_HEADER_LENGTH 360

/** esmtp header */
#define EMAIL_ESMTP_HEADER_EHLO "EHLO mobilephone\r\n\0"
#define EMAIL_ESMTP_HEADER_AUTH "AUTH LOGIN\r\n\0"
#define EMAIL_ESMTP_HEADER_STARTTLS "STARTTLS\r\n\0"

#define EMAIL_ESMTP_HEADER_MAILFROM_FORMAT_STR  "MAIL FROM: <%s>\r\n"
#define EMAIL_ESMTP_HEADER_RCPTTO_FORMAT_STR  "RCPT TO: <%s>\r\n"

#define EMAIL_ESMTP_HEADER_DATA "DATA\r\n\0"
#define EMAIL_ESMTP_HEADER_QUIT "QUIT\r\n\0"

#define EMAIL_ESMTP_HEADER_DATE "Date: "
#define EMAIL_ESMTP_HEADER_FROM "From: "
#define EMAIL_ESMTP_HEADER_TO "To: "
#define EMAIL_ESMTP_HEADER_CC "Cc: "
#define EMAIL_ESMTP_HEADER_BCC "Bcc: "
#define EMAIL_ESMTP_HEADER_REPLY "Reply-To: "
#define EMAIL_ESMTP_HEADER_SUBJECT "Subject: "
#define EMAIL_ESMTP_HEADER_MIME "MIME-Version: 1.0\r\n\0"
//#define EMAIL_ESMTP_HEADER_BOUNDARAY "\tboundary=\"----=_mstarsemi.com.cn----\"\r\n\0"
#define EMAIL_ESMTP_HEADER_BOUNDARAY "\tboundary=\""
#define EMAIL_ESMTP_HEADER_CORPORATION "------=_mstarsemi.com----\r\n\0"
#define EMAIL_ESMTP_HEADER_BOUNDARAY_END "\""
#define EMAIL_ESMTP_HEADER_CHARSET "\tcharset=\"gb2312\"\r\n\0"
#define EMAIL_ESMTP_HEADER_ENCODE "Content-Transfer-Encoding: base64\r\n\0"
#define EMAIL_ESMTP_HEADER_ATTACH "Content-Disposition: attachment;\r\n\0"
#define EMAIL_ESMTP_HEADER_CONTENTTYPE "Content-Type: "
#define EMAIL_ESMTP_HEADER_CONTENT_TEXT "Content-Type: text/plain;\r\n\0"
#define EMAIL_ESMTP_HEADER_CONTENT_MIXED "Content-Type: multipart/mixed;\r\n\0"
#define EMAIL_ESMTP_HEADER_CONTENTTYPE_TEXT "text/plain;"
#define EMAIL_ESMTP_HEADER_CONTENTTYPE_MIXED "multipart/mixed;"

#define EMAIL_ESMTP_HEADER_NAME "\tname=\""
#define EMAIL_ESMTP_HEADER_NAME_END "\"\r\n\0"
#define EMAIL_ESMTP_HEADER_FILENAME "filename=\""
#define EMAIL_ESMTP_HEADER_FILENAME_END "\"\r\n\r\n\0"
#define EMAIL_ESMTP_HEADER_PRIORITY "X-Priority: "
#define EMAIL_ESMTP_HEADER_MAIL_PRIORITY "X-Mail-Priority: "
#define EMAIL_ESMTP_HEADER_MAIL_PRIORITY_HIGH "High"
#define EMAIL_ESMTP_HEADER_MAIL_PRIORITY_NORMAL "Normal"
#define EMAIL_ESMTP_HEADER_MAIL_PRIORITY_LOW "Low"
#define EMAIL_ESMTP_HEADER_MAILER "X-Mailer: mstar mailer\r\n\0"
#define EMAIL_ESMTP_HEADER_MIMEOLE "X-MimeOLE: Produced By MimeOLE V5.50.4522.1200\r\n\0"

#define EMAIL_ESMTP_HEADER_ENDLINE "\r\n\0"
#define EMAIL_ESMTP_HEADER_ENDMAIL "\r\n.\r\n\0"

#define EMAIL_ESMTP_RESPONSE_BUFFERLEN  1024
#define EMAIL_ESMTP_REQUEST_BUFFERLEN   128
#define EMAIL_ESMTP_DATA_BUFFERLEN_EXTN 360
#define EMAIL_ESMTP_MAX_TIMEOUT 400

typedef struct T_EMAIL_ESMTP_HANDLE {
    T_EMAIL_Account_Config * esmtpConfig;

    T_EMAIL_MailBox_List From;
    T_EMAIL_MailBox_List To;
    T_EMAIL_MailBox_List Cc;
    T_EMAIL_MailBox_List Bcc;
    T_EMAIL_MailBox_Node *pCurMailbox;

    int32_t status;
    int32_t retryTime;
    int32_t retryLen;
    int32_t timeStamp;
    int32_t fdSocket;
    uint32_t fpipaddr;
    int32_t pSendLen;
    int32_t pRecvLen;
    int32_t respBufLen;
    int32_t sendBufLen;
    int32_t dataBufLen;
    int8_t pending;
    int8_t needAuthLogin;
    int8_t * pSend;
    int8_t * pRecv;
    int8_t * respBuf;
    int8_t * sendBuf;
    int8_t * dataBuf;

    FUNC_EMAIL_Notifier EMAILNotifier;
}T_EMAIL_ESMTP_HANDLE;

#ifdef __cplusplus
extern "C" {
#endif

int32_t checkEmail4Send(ESMTP_HANDLE TRANS_Handle);

int32_t fnEsmtp_getHostByName(ESMTP_HANDLE TRANS_Handle);

int32_t fnEsmtp_connectServer(ESMTP_HANDLE TRANS_Handle);

int32_t fnEsmtp_sendReqBuffer(ESMTP_HANDLE TRANS_Handle);

int32_t fnEsmtp_recvRespBuffer(ESMTP_HANDLE TRANS_Handle);

int32_t fnEsmtp_getSendData(ESMTP_HANDLE TRANS_Handle);

int32_t fnEsmtp_mailboxListCpy(T_EMAIL_MailBox_List *pDestList, T_EMAIL_MailBox_List *pSrcList);

int32_t fnEsmtp_initMailboxList(ESMTP_HANDLE esmtpHandle, int8_t *pEmailBuf, int32_t emailBufLen);

#ifdef __cplusplus
}
#endif

#endif /* __EML_ESMTP_INSIDE_H__ */
