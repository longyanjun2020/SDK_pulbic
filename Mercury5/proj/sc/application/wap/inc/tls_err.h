
#ifndef __TLS_ERR_H__
#define __TLS_ERR_H__

#ifdef __cplusplus
extern "C" {
#endif

/** the ssl protocol's error code  */
#define SSL_OK                      0       /**< ssl operation ok */
#define SSL_FAILED                  -1      /**< ssl operation error */
#define SSL_NOT_INITIALISED         -2      /**< didn't init ssl */
#define SSL_NET_DOWN                -3      /**< the lower connection has disconnected */
#define SSL_INPROGRESS              -4      /**< in connecting  */
#define SSL_UNSUPPORT_VER           -5      /**< unsupport ssl versiion */
#define SSL_INVALID_ARG             -6      /**< invalid arguments */
#define SSL_SESS_REJECT_RESUME      -7      /**< server reject to resume a session */
#define SSL_HANDSHAKE_FAILED        -8      /**< handshake failed */
#define SSL_CONNECT_FAILED          -9      /**< connect to server failed */
#define SSL_BAD_CERT                -10     /**< verify certificate failed */
#define SSL_INIT_FAIL               -11     /**< init ssl fail */
#define SSL_MAX_SESSION             -12     /**< the number of session has reach maximun */
#define SSL_NO_BUFFER               -13     /**< memory error */
#define SSL_CREATE_SOCK_ERR         -14     /**< create socket error */
#define SSL_NOT_CONN                -15     /**< the secure connect hasn't been established, or has down */
#define SSL_WOULD_BLOCK             -16     /**< the session is in block */
#define SSL_MALLOC_FAILED           -17     /**< maloc memory failed */
#define SSL_UNKNOWN_ERROR           -18     /**< unknwn error */
#define SSL_CONN_NOT_EXIST          -19     /**< connection is not exist */
#define SSL_CONN_STATE_ERR          -20     /**< connection state error */
#define SSL_SESS_CORRUPTED          -21     /**< session has been corrupted */
#define SSL_SESS_ID_TOO_LONG        -22     /**< session id too long */
#define SSL_CONN_SENT_ERR           -23     /**< connection sent data error */
#define SSL_SET_CIPHER_ERR          -24     /**< set ciphter suite error */
#define SSL_SERVER_CERTS_EXLIMIT    -26     /**< server sent too many certificates */
#define SSL_ERR_MT_DISMATCH         -27     /**< message type dismatch */
#define SSL_ERR_PKT_INCOMPLETE      -29     /**< pkt has not received over */
#define SSL_ERR_BUFFER_EMPTY        -30     /**< buffer empty */
#define SSL_ERR_MD_VERIFY_FAIL      -31     /**< mac verify failed */
#define SSL_ERR_SEQ_EXLIMIT         -32     /**< sequence number exceed limit */
#define SSL_DISPLAY_WAIT            -33     /**< when need to display the cert, there may be a status that waiting for the user's option*/
#define SSL_ADD_SERVER_CA_FAILED    -34     /**< add server ca to trust cert store failed */
#define SSL_RAND_ERR                -35     /**< ssl rand error */
#define SSL_CHANGE_CIPHER_ERR       -36     /**< ssl change cipher error */
#define SSL_DIGIST_ERROR            -37     /**< ssl digisth error */
#define SSL_CONN_NUM_EXLIMT         -38     /**< too many connection */
#define SSL_INIT_ALG_ERR            -39     /**< ssl init algorithm error */
#define SSL_UNSUPPORT_CIPHER        -40     /**< unsupport cipher suite */
#define SSL_CIPHER_TXT_EXLIMIT      -41     /**< cipher text too long */
#define SSL_RCV_BUF_OVERFLOW        -42     /**< ssl recv buffer is overflow */
#define SSL_RCV_ERR                 -43     /**< ssl receive error */
#define SSL_UNKNOW_PKT              -44     /**< unknown pkt */
#define SSL_HAS_INITED              -45     /**< ssl has been inited */
#define SSL_INIT_NET_FAILED         -46     /**< init network failed */
#define SSL_LOAD_SERVER_AUTH_FAIL   -47     /**< load server auth store file failed */
#define SSL_LOAD_CRL_CERT_FAIL      -48     /**< load crl cert store file failed */
#define SSL_SESSION_NOT_EXIST       -50     /**< session not exist */
#define SSL_NULL_POINTER            -51     /**< null pointer */
#define SSL_UNKNOW_HASH_ALG         -52     /**< unknown hash algorithm */
#define SSL_NO_RELATED_SESSION      -53     /**< no related session for a ip addr */
#define SSL_GET_IP_ADDR_FAILED      -54     /**< get ip address failed */
#define SSL_UNLOAD_SERVER_AUTH_FAIL -55     /**< un-load server authentication store file failed */
#define SSL_UNLOAD_CRL_CERT_FAIL    -56     /**< un-load crl cert store file failed */
#define SSL_UNLOAD_CODE_SIGN_FAIL   -57     /**< un-load code sign store file failed */
#define SSL_LOAD_CODE_SIGN_FAIL     -58     /**< load code sign store file failed */
#define SSL_TRUST_SERVER_BADCERT	-59		/**< verify server certificate failed, but client trust it,added by will.wang */

#ifdef __cplusplus
}
#endif

#endif /* __TLS_ERR_H__ */

