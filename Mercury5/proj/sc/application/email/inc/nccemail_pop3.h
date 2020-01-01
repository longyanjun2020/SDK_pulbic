/**
* @file nccmail_pop3.h
* NCC email pop3 Service Layer
*
* Service API exposed by the NCC email pop3 module
*
* <!-- #interface list begin -->
* \section nccmail_pop3 Interface
* - NCCEmail_pop3_init()
* - NCCEmail_pop3_recv_run()
* - NCCEmail_pop3_quit()
* <!-- #interface list end -->
*/

#ifndef __NCCEMAIL_POP3_H__
#define __NCCEMAIL_POP3_H__
#include <nccemail_common.h>

/**
* ======= CONSTANTS AND MACROS =======
*/

/*@{*/

/**
*    \name Return Values for NCCEmail_pop3_*** functions.
*/

/** POP3 result */
//Please reference the nccemail_common.h

/** define the email POP3 status */
#define EMAIL_POP3_STATUS_IDLE              50
#define EMAIL_POP3_STATUS_START             51
#define EMAIL_POP3_STATUS_CONNECT           52
#define EMAIL_POP3_STATUS_CONNECT_RESP      53
#define EMAIL_POP3_STATUS_USER              54
#define EMAIL_POP3_STATUS_USER_RESP         55
#define EMAIL_POP3_STATUS_PASS              56
#define EMAIL_POP3_STATUS_PASS_RESP         57
#define EMAIL_POP3_STATUS_STAT              58
#define EMAIL_POP3_STATUS_STAT_RESP         59
#define EMAIL_POP3_STATUS_UIDL              60
#define EMAIL_POP3_STATUS_UIDL_RESP         61
#define EMAIL_POP3_STATUS_LIST              62
#define EMAIL_POP3_STATUS_LIST_RESP         63
#define EMAIL_POP3_STATUS_RETR              64
#define EMAIL_POP3_STATUS_RETR_RESP         65
#define EMAIL_POP3_STATUS_QUIT              66
#define EMAIL_POP3_STATUS_QUIT_RESP         67

#define EMAIL_POP3_STATUS_LISTA             68
#define EMAIL_POP3_STATUS_LISTA_RESP        69
#define EMAIL_POP3_STATUS_DELE              70
#define EMAIL_POP3_STATUS_DELE_RESP         71
#define EMAIL_POP3_STATUS_NOOP              72
#define EMAIL_POP3_STATUS_NOOP_RESP         73
#define EMAIL_POP3_STATUS_RSET              74
#define EMAIL_POP3_STATUS_RSET_RESP         75
#define EMAIL_POP3_STATUS_XSENDER           76
#define EMAIL_POP3_STATUS_XSENDER_RESP      77
#define EMAIL_POP3_STATUS_TOP               78
#define EMAIL_POP3_STATUS_TOP_RESP          79
#define EMAIL_POP3_STATUS_XAUTHLIST         80
#define EMAIL_POP3_STATUS_XAUTHLIST_RESP    81
#define EMAIL_POP3_STATUS_XAUTHLISTA        82
#define EMAIL_POP3_STATUS_XAUTHLISTA_RESP   83
#define EMAIL_POP3_STATUS_SENDCOMMAND       84
#define EMAIL_POP3_STATUS_SENDCOMMAND_RESP  85
#define EMAIL_POP3_STATUS_SENDCOMMANDA      86
#define EMAIL_POP3_STATUS_SENDCOMMANDA_RESP 87
#define EMAIL_POP3_STATUS_CONPROXY          88
#define EMAIL_POP3_STATUS_CONPROXY_RESP     89
#define EMAIL_POP3_STATUS_OVER              90



/** define the request type */
/** Retrieve all email which had not been download*/
#define EMAIL_POP3_REQ_RETR_ALL             0
/** Retrieve all email header which had not been download*/
#define EMAIL_POP3_REQ_RETR_ALL_HEADER      1
/** Retrieve one email which had not been download*/
#define EMAIL_POP3_REQ_RETR_ONE             2
/** Delete all email which had been backup on the server*/
#define EMAIL_POP3_REQ_DELE_ALL             3
/** Delete one email which had been backup on the server*/
#define EMAIL_POP3_REQ_DELE_ONE             4
/** Get the email list information on the server*/
#define EMAIL_POP3_REQ_CHECK_INFO           5
/** Check the user and password*/
#define EMAIL_POP3_REQ_CHECK_ACCOUNT        6

/*@}*/

/**EMAIL POP3 information structure*/
typedef struct T_EMAIL_Pop3_Handle * POP3_HANDLE;

#ifdef __cplusplus
extern "C" {
#endif

    /**
    * Create and initialize the pop3 handle.
    * \param *pConfig           The email account config pointer, keep it during the pop3 running and free it after quit the pop3 module.
    * \param *pTRANS_Handle     The pop3 handle.
    * \param *reqType           The request type.
    * \param *uidlFilename      The uid list file name.
    * \param *reqUidStr         The request uid string, it is in the email header.
    * \param *sizeLimit         The limit size value. if it is 0, there is no size limit.
    * \param *callback          The callback function.
    * \return    <ul>
    *                <li>when successful,return#EMAIL_NET_SUCCESS
    *                <li>when fail,return
    *                    <ul>
    *                        <li>#EMAIL_NET_PARAMETE_ERROR
    *                        <li>#EMAIL_NET_ALLOC_FAIL
    *                    </ul>
    *            </ul>
    */
int32_t NCCEmail_pop3_init(const T_EMAIL_Account_Config * pConfig, POP3_HANDLE * pTRANS_Handle,
    const int32_t reqType, const int8_t * uidlFilename, const int8_t * reqUidStr,
    const int32_t sizeLimit, FUNC_EMAIL_Notifier callback);
    /**
    * Run the pop3 handle.
    * \param TRANS_Handle   The email pop3 handle.
    * \return    <ul>
    *                <li>when successful,return#EMAIL_NET_SUCCESS
    *                <li>when fail,return
    *                    <ul>
    *                        <li>#EMAIL_NET_PARAMETE_ERROR
    *                        <li>#EMAIL_NET_ALLOC_FAIL
    *                        <li>#EMAIL_NET_STATUS_ERROR or other status error value.
    *                    </ul>
    *            </ul>
    */
    int32_t NCCEmail_pop3_recv_run(POP3_HANDLE TRANS_Handle);

    /**
    * Quit and free the pop3 handle.
    * \param TRANS_Handle   The email pop3 handle.
    * \return    <ul>
    *                <li>when successful,return#EMAIL_NET_SUCCESS
    *                <li>when fail,return
    *                    <ul>
    *                        <li>#EMAIL_NET_PARAMETE_ERROR
    *                    </ul>
    *            </ul>
    */
    int32_t NCCEmail_pop3_quit(POP3_HANDLE TRANS_Handle);

#ifdef __cplusplus
}
#endif

#endif /* __NCCEMAIL_POP3_H__ */
