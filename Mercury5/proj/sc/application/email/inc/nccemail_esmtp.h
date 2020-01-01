/**
* @file nccemail_esmtp.h
* NCC email ESMTP Service Layer
*
* Service API exposed by the NCC email ESMTP module
*
* <!-- #interface list begin -->
* \section nccemail_esmtp Interface
* - NCCEmail_esmtp_init()
* - NCCEmail_esmtp_send_run()
* - NCCEmail_esmtp_quit()
* <!-- #interface list end -->
*/

#ifndef __NCCEMAIL_ESMTP_H__
#define __NCCEMAIL_ESMTP_H__

#include <nccemail_common.h>

/**
* ======= CONSTANTS AND MACROS =======
*/

/*@{*/

/**
*    \name Return Values for NCCEmail_esmtp_*** functions.
*/

/** ESMTP result */
//Please reference the nccemail_common.h

/** define the email ESMTP status */
#define EMAIL_ESMTP_STATUS_IDLE             10
#define EMAIL_ESMTP_STATUS_START            11
#define EMAIL_ESMTP_STATUS_CONNECT          12
#define EMAIL_ESMTP_STATUS_CONNECT_RESP     13
#define EMAIL_ESMTP_STATUS_HELLOTLS         14
#define EMAIL_ESMTP_STATUS_HELLOTLS_RESP    15

#define EMAIL_ESMTP_STATUS_STARTTLS         16
#define EMAIL_ESMTP_STATUS_STARTTLS_RESP    17
#define EMAIL_ESMTP_STATUS_STARTTLS_SOCKET  18
#define EMAIL_ESMTP_STATUS_CONNECTSSL       19
#define EMAIL_ESMTP_STATUS_CONNECTSSL_RESP  20

#define EMAIL_ESMTP_STATUS_HELLO            21
#define EMAIL_ESMTP_STATUS_HELLO_RESP       22
#define EMAIL_ESMTP_STATUS_AUTH             23
#define EMAIL_ESMTP_STATUS_AUTH_RESP        24
#define EMAIL_ESMTP_STATUS_USER             25
#define EMAIL_ESMTP_STATUS_USER_RESP        26
#define EMAIL_ESMTP_STATUS_PWD              27
#define EMAIL_ESMTP_STATUS_PWD_RESP         28
#define EMAIL_ESMTP_STATUS_FROM             29
#define EMAIL_ESMTP_STATUS_FROM_RESP        30
#define EMAIL_ESMTP_STATUS_TO               31
#define EMAIL_ESMTP_STATUS_TO_RESP          32
#define EMAIL_ESMTP_STATUS_CC               33
#define EMAIL_ESMTP_STATUS_CC_RESP          34
#define EMAIL_ESMTP_STATUS_BCC              35
#define EMAIL_ESMTP_STATUS_BCC_RESP         36
#define EMAIL_ESMTP_STATUS_DATAREQ          37
#define EMAIL_ESMTP_STATUS_DATAREQ_RESP     38
#define EMAIL_ESMTP_STATUS_DATA             39
#define EMAIL_ESMTP_STATUS_DATA_RESP        40
#define EMAIL_ESMTP_STATUS_DATA_END         41
#define EMAIL_ESMTP_STATUS_QUIT             42
#define EMAIL_ESMTP_STATUS_QUIT_RESP        43
#define EMAIL_ESMTP_STATUS_OVER             44

/*@}*/

/**EMAIL ESMTP information structure*/
typedef struct T_EMAIL_ESMTP_HANDLE * ESMTP_HANDLE;

#ifdef __cplusplus
extern "C" {
#endif

/**
* Create and initialize the ESMTP handle.
*
* \param pConfig
*      The email account config pointer, keep it during the pop3 running and free it after quit the pop3 module.
*
* \param pEmailBuf
*      The email buffer need to be send.
*
* \param emailBufLen
*      The length of the email buffer need to be send.
*
* \param pFnNotifyCb
*      The callback function.
*
* \return    <ul>
*                <li>when successful,return#EMAIL_NET_SUCCESS
*                <li>when fail,return
*                    <ul>
*                        <li>#EMAIL_NET_PARAMETE_ERROR
*                        <li>#EMAIL_NET_ALLOC_FAIL
*                    </ul>
*            </ul>
*/
int32_t NCCEmail_esmtp_init(T_EMAIL_Account_Config *pConfig, int8_t *pEmailBuf, int32_t emailBufLen,
    ESMTP_HANDLE *pTRANS_Handle, FUNC_EMAIL_Notifier pFnNotifyCb);

/**
* Run the ESMTP handle.
* \param TRANS_Handle   The email ESMTP handle.
* \return    <ul>
*                <li>when successful,return#EMAIL_NET_SUCCESS
*                <li>when fail,return
*                    <ul>
*                        <li>#EMAIL_NET_PARAMETE_ERROR
*                        <li>#EMAIL_NET_ALLOC_FAIL
*                        <li>#EMAIL_NET_ERROR_STATUS or other status error value.
*                    </ul>
*            </ul>
*/
int32_t NCCEmail_esmtp_send_run(ESMTP_HANDLE TRANS_Handle);

/**
 * Quit and free the ESMTP handle.
 * \param pTRANS_Handle   The email ESMTP handle.
 * \return    <ul>
 *                <li>when successful,return#EMAIL_NET_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#EMAIL_NET_PARAMETE_ERROR
 *                    </ul>
 *            </ul>
 */
int32_t NCCEmail_esmtp_quit(ESMTP_HANDLE *pTRANS_Handle);

#ifdef __cplusplus
}
#endif

#endif /* __NCCEMAIL_ESMTP_H__ */
