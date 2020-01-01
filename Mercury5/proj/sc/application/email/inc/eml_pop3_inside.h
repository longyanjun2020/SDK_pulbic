/**
* @file eml_pop3_inside.h
* NCC email pop3 internal Layer
*
* Internal API unexposed by the NCC email po3 module
*/
#ifndef __EML_POP3_INSIDE_H__
#define __EML_POP3_INSIDE_H__
#include <nccemail_common.h>

/** email POP3 COMMAND String */
#define EMAIL_POP3_USER "USER "
#define EMAIL_POP3_PASS "PASS "
#define EMAIL_POP3_STAT "STAT"
#define EMAIL_POP3_UIDL "UIDL"
#define EMAIL_POP3_LIST "LIST"
#define EMAIL_POP3_RETR "RETR "

#define EMAIL_POP3_TOP  "TOP "
#define EMAIL_POP3_NOOP "NOOP"
#define EMAIL_POP3_DELE "DELE "
#define EMAIL_POP3_RSET "RSET"
#define EMAIL_POP3_QUIT "QUIT"

#define EMAIL_POP3_XAUTHLIST  "XAUTHLIST "
#define EMAIL_POP3_XSENDER  "XSENDER "

#define EMAIL_POP3_SPACE  " "
#define EMAIL_POP3_OK   "+OK"
#define EMAIL_POP3_ERR  "-ERR"
#define EMAIL_POP3_HEADER_ENDLINE "\r\n\0"
#define EMAIL_POP3_HEADER_ENDMAIL "\r\n.\r\n\0"
#define EMAIL_POP3_HEADER_ENDLINE_LEN 2
#define EMAIL_POP3_HEADER_ENDMAIL_LEN 5

#define EMAIL_POP3_REQUEST_BUFFERLEN   256
#define EMAIL_POP3_RESPONSE_BUFFERLEN  1024
#define EMAIL_POP3_DEBUG_BUFFERLEN     300
#define EMAIL_POP3_MAX_HEADER_LEN      20480 // malloc 20KB for the email header
#define EMAIL_POP3_MAX_MORE_LEN        20480 // malloc 20KB more space for the retrieve email
#define EMAIL_POP3_MAX_TIMEOUT 400

#define EMAIL_POP3_UID_OPT_DEL    1
#define EMAIL_POP3_UID_OPT_ADD    2
#define EMAIL_POP3_UID_OPT_DELALL 3

#define NCCPort_EMAIL_POP3_RETRY_TIME 10

typedef struct _EMAIL_Retr_List {
    int32_t index;
    int8_t * uidStr;
    int32_t emailSize;
    struct _EMAIL_Retr_List * next;
}T_EMAIL_Retr_List;

typedef struct T_EMAIL_Pop3_Handle {
    T_EMAIL_Account_Config * pop3Config;
    int32_t status;
    int32_t retryTime;
    int32_t retryLen;
    int32_t timeStamp;
    int32_t fdSocket;
    uint32_t fpipaddr;
    int32_t requestType;//define the request type, very useful
    int32_t requestIndex;
    int32_t pSendLen;
    int32_t pRecvLen;
    int32_t sendBufLen;
    int32_t respBufLen;
    int32_t uidlClientBufLen;
    int32_t totalMsgTask;
    int32_t totalMsgFinished;
    int32_t totalSize;
    int32_t pending;
    int32_t sizeLimit;
    int8_t * pSend;
    int8_t * pRecv;
    int8_t * respBuf;
    int8_t * sendBuf;
    int8_t * curUidStr;
    int8_t * statusInfor;
    int8_t * uidlFileName;
    int8_t * uidlClientBuf;
    T_EMAIL_Retr_List * uidListClient;
    T_EMAIL_Retr_List * uidListServer;
    T_EMAIL_Retr_List * retrEmailList;
    T_EMAIL_Retr_List * curRetrEmailItem;
    FUNC_EMAIL_Notifier EMAILNotifier;
}T_EMAIL_Pop3_Handle;

//typedef T_EMAIL_Pop3_Handle * POP3_HANDLE;

#ifdef __cplusplus
extern "C" {
#endif

    int32_t fnPop3_getHostByName(POP3_HANDLE TRANS_Handle);

    int32_t fnPop3_sendReqBuffer(POP3_HANDLE TRANS_Handle);

    int32_t fnPop3_recvRespBuffer(POP3_HANDLE TRANS_Handle);

    int32_t fnPop3_statusPre(POP3_HANDLE TRANS_Handle);

    int32_t fnPop3_statusNext(POP3_HANDLE TRANS_Handle);

    int32_t fnPop3_statusError(POP3_HANDLE TRANS_Handle);

#ifdef __cplusplus
}
#endif

#endif /* __EML_POP3_INSIDE_H__ */
