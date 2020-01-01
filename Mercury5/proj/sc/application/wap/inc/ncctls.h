
/**
 * @file
 * Transport Layer Security Service Layer
 *
 * Service API exposed by the Transport Layer Security.
 *
 * <!-- #interface list begin -->
 * \section svc_tls_interface Interface
 * - NCCtls_check()
 * - NCCtls_init()
 * - NCCtls_newSession()
 * - NCCtls_connect()
 * - NCCtls_newConnection()
 * - NCCtls_upgradeConnection()
 * - NCCtls_read()
 * - NCCtls_write()
 * - NCCtls_close()
 * - NCCtls_getSupportedCipherSuitesLen()
 * - NCCtls_getSupportedCipherSuites()
 * - NCCtls_getConnCipherSuiteLen()
 * - NCCtls_getConnCipherSuite()
 * - NCCtls_getIpSess()
 * - NCCtls_getConnSess()
 * - NCCtls_exit()
 * - NCCtls_setVersion()
 * - NCCtls_getVersion()
 * - NCCtls_setIsResumable()
 * - NCCtls_getIsResumable()
 * - NCCtls_setTimeOut()
 * - NCCtls_getTimeOut()
 * - NCCtls_setLiveTime()
 * - NCCtls_getLiveTime()
 * - NCCtls_setBlockMode()
 * - NCCtls_getBlockMode()
 * - NCCtls_setAutoAddCert()
 * - NCCtls_getAutoAddCert()
 * - NCCtls_setCertVerifyCallback()
 * - NCCtls_getCertVerifyCallback()
 * - NCCtls_setCertDisplayCallback()
 * - NCCtls_getCertDisplayCallback()
 * - NCCgetConnectionSocketId()
 * - NCCtls_getServerCertObj()
 * - NCCtls_userAcceptVerifyNotPass()
 * - NCCtls_getVerifyServerFailedReason()
 * - NCCtls_setSessServerName()
 * - NCCtls_checkIfServerNameMatch()
 * - NCCtls_checkIfOtherConnWaitForUserRes()
 * <!-- #interface list end -->
 */

#ifndef __NCCTLS_INTERFACE_H__
#define __NCCTLS_INTERFACE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <tls_err.h>
#include <ncccert.h>

/** the verision SSL supports */
#define SSL3_VERSION    0x0300  /**< SSL 3.0 */
#define TLS1_VERSION    0x0301  /**< TLS 1.0 */

#define SSL_SESSION_REUSABLE TRUE           /** session is resumable */
#define SSL_SESSION_ISNOT_RESUMABLE FALSE   /** session is not resumable */

/** the block mode of lower network */
#define SSL_NBIO    0   /**< non-block */
#define SSL_BIO     1   /**< block */

#define SSL_DEFAULT_TIMEOUT     (180  * 1000)    /**< the default timeout of session (ms) */
#define SSL_DEFAULT_LIVETIME    (600 * 1000)    /**< the default livetime of session (ms) */

//the status in handshake
enum
{
    SSL_CONNECT_START       = 0, /**< start to connect */
    SSL_WAIT_CONNECT        = 1, /**< waitting for connect over */
    SSL_CONNECT_ESTABLSHED  = 2  /**< the connect is over  */
} ;

/** the address definition same to windows */
typedef struct
{
    int16_t  sin_family;  /**< address family, AF_xxx   */
    uint16_t sin_port;    /**< the port that ssl operation */
    uint32_t saddr;       /**< the ip other peer's address */
}T_SSL_sockaddr_in;

/**< whether need display the debug information*/
#ifdef NCC_DEBUG_ON
#define SSL_DEBUG
#endif

/**< define the printf SSL uses */
#ifdef SSL_DEBUG
    #define SSL_PRINTF  CRTL_printf
#else
    #define SSL_PRINTF
#endif

/** ssl configure infor */
typedef struct
{
    uint32_t ssl_version;
    int32_t is_resumale;
    uint32_t time_out;
    uint32_t live_time;
    int32_t block_mode;
    int32_t is_auto_add;
    CERT_VERIFY_CALLBACK_FUNC verify_callback;
    CERT_DISPLAY_CALLBACK_FUNC display_callback;
}T_SSL_Config_Info;

extern T_SSL_Config_Info gssl_config_info;
extern T_SSL_List gssl_verify_record;

/* only for memor leak check */
#ifdef SSL_CHECK_MEMORY_LEAK
#define SSL_MALLOC_TAB 10000
extern int32_t CPL_wapmem_mallocAddr[SSL_MALLOC_TAB][2];
extern int32_t ssl_mem_count;
#endif

/**
 * The entrance of SSL module, do handshake and receive/send data with server
 * \param  none
 * \return
 *  SSL_OK  succeed
 *   error code
 *     SSL_UNKNOW_PKT
 *     SSL_NOT_CONN
 *     SSL_UNSUPPORT_VER
 *     SSL_RCV_ERR
 *     SSL_CONN_NOT_EXIST
 *     SSL_CONNECT_FAILED
 *     SSL_CONN_STATE_ERR
 *     SSL_SESS_REJECT_RESUME
 *     SSL_SERVER_CERTS_EXLIMIT
 *     SSL_MALLOC_FAILED
 *     SSL_ADD_SERVER_CA_FAILED
 *     SSL_NO_BUFFER
 *     SSL_CONN_SENT_ERR
 */
int32_t NCCtls_check(int32_t connection);

/**
 * Init SSL
 * \param  none
 * \return
 *   SSL_OK      succeed
 *   error code
 *     SSL_INIT_NET_FAILED
 *     SSL_INIT_ALG_ERR
 *     SSL_LOAD_SERVER_AUTH_FAIL
 *     SSL_LOAD_CODE_SIGN_FAIL
 *     SSL_LOAD_CRL_CERT_FAIL
 */
 int32_t NCCtls_init(int32_t appId, int8_t *sysPath);

/**
 * Create the context of a session
 * \param  none
 * \return
 *   the session created   succeed
 *   error code
 *     SSL_MAX_SESSION
 *     SSL_MALLOC_FAILED
 */
int32_t NCCtls_newSession(void);

/**
 * Create a connection context in a session
 * \param  ssl_session(input)  the ssl session in which new connection belongs
 * \return
 *  the connection created   succeed
 *   error code
 *     SSL_CONN_NUM_EXLIMT
 *     SSL_MALLOC_FAILED
 */
int32_t NCCtls_newConnection(int32_t ssl_session);

/**
 * Upgrade a unsecure connection connected before to secure connection
 * \param  connection(input)  the connetion created by NCCtls_newConnection
 * \param  socket_id(input)   the socket descriptor
 *   SSL_OK      succeed
 *   error code
 *     SSL_CONN_NOT_EXIST
 */
int32_t NCCtls_upgradeConnection(int32_t connection,int32_t socket_id);

/**
 * Establish a secure connection,
             Note: if the connection has been connected before, params ip_addr and port are ignored
 * \param  ip_addr(input)     the ssl server's ip address
 * \param  port(input)        the port through which connect ssl server
 * \param  connection(input)  the connection created by NCCtls_newConnection
 * \return
 *   SSL_OK      succeed
 *   SSL_WAIT_CONNECT  in connecting
 *   error code
 *     SSL_CONN_NOT_EXIST
 *     SSL_CLOSED
 *     SSL_SESS_REJECT_RESUME
 *     SSL_CREATE_SOCK_ERR
 *     SSL_CONNECT_FAILED
 *     SSL_NOT_CONN
 *     SSL_INPROGRESS
 *     SSL_BAD_CERT
 */
int32_t NCCtls_connect(uint32_t ip_addr,uint16_t port,int32_t connection,int32_t appId);

/**
 * Receive app data on a secure connection
 * \param connection(input)  the connection on which to receive data
 * \param len(input)         the expected length of data want to receive
 * \param rbuf(output)       Where to store the app data received
 * \return
 *   >0          the length of data recved
 *   SSL_RECV_NO_DATA  no data recved
 *   error code
 *     SSL_CONN_NOT_EXIST
 *     SSL_WOULD_BLOCK
 *     SSL_RCV_ERR
 */
int32_t NCCtls_read(int32_t connection, uint8_t *rbuf, int32_t len);

/**
 * Send app data on a secure connection
 * \param connection(input)  the connection on which to send app data
 * \param wbuf(input)        Where to store the app data to be sent
 * \param len(input)         the expected length of app data to be sent
 * \return
 *  > 0         the length of data sent actually
 *   error code
 *     SSL_CONN_NOT_EXIST
 *     SSL_NET_DOWN
 *     SSL_WOULD_BLOCK
 *     SSL_CONN_SENT_ERR
 */
 int32_t NCCtls_write(int32_t connection,uint8_t *wbuf, int32_t len);

/**
 * Close a secure connection
 * \param connection(input) the secure connection to be closed
 * \return
 *   SSL_OK      succeed
 *   error code
 *     SSL_CONN_NOT_EXIST
 */
int32_t NCCtls_close(int32_t connection);

/**
 * Exit SSL, this function should be called when exit SSL
 * \param none
 * \return
 *   SSL_OK      succeed
 *   error code
 *     SSL_UNLOAD_TRUST_CERT_FAIL
 *     SSL_UNLOAD_CRL_CERT_FAIL
 */
int32_t NCCtls_exit(int32_t appId);

/**
 * Get the ssl session by ip addr
 * \param  ip_addr(input)  the ip address of SSL server
 * \return
 *  the session   succeed
 *   error code
 *     SSL_NO_RELATED_SESSION
 */
int32_t NCCtls_getIpSess(uint32_t ip_addr);

/**
 * Get the SSL session by connection
 * \param  connection(input)  the secure connection established before
 *  the session   succeed
 *   error code
 *     SSL_CONN_NOT_EXIST
 */
 int32_t NCCtls_getConnSess(int32_t connection);

/**
 * Set the version of SSL
 * \param session(input)     ssl session
 * \param ssl_version(input) ssl version, now only SSL3_VERSION and TLS1_VERSION are valid
 * \return
 *  SSL_OK     succeed
 *   error code
 *  SSL_UNSUPPORT_VER
 *  SSL_SESSION_NOT_EXIST
 */
int32_t NCCtls_setVersion(int32_t session,uint32_t ssl_version);

/**
 * Get the version of SSL
 * \param session(input)  ssl session
 * \return
 *  the version of SSL
 *   error code
 *  SSL_SESSION_NOT_EXIST
 */
int32_t NCCtls_getVersion(int32_t session);

/**
 * Set the version of SSL
 * \param ssl_version(input) ssl version, now only SSL3_VERSION and TLS1_VERSION are valid
 * \return
 *  SSL_OK     succeed
 *   error code
 *     SSL_UNSUPPORT_VER
 */
int32_t NCCtls_userSetVersion(uint32_t ssl_version);

/**
 * Get the version of SSL
 * \param  none
 * \return  the version of SSL
 */
uint32_t NCCtls_userGetVersion(void);

/**
 * Set if is resumable
 * \param is_resumale(input) the flag of resume, TRUE or FALSE
 * \return none
 */
void NCCtls_setIsResumable(int32_t is_resumale);

/**
 * Get if is resumable
 * \param  none
 * \return
 *   TRUE   session is resumable
 *   FALSE  session is not resumable
 */
int32_t NCCtls_getIsResumable(void);

/**
 * Set timeout
 * \param time_out(input)  the timeout
 * \return none
 */
void NCCtls_setTimeOut(uint32_t time_out);

/**
 * Get timeout
 * \param none
 * \return  the timeout
 */
uint32_t NCCtls_getTimeOut(void);

/**
 * Set live time
 * \param live_time(input)  the live time
 * \return none
 */
void NCCtls_setLiveTime(uint32_t live_time);

/**
 * Get live time
 * \param none
 * \return  the live time of session
 */
uint32_t NCCtls_getLiveTime(void);

/**
 * Set block mode
 * \param block_mode(input) the block_mode, SSL_NBIO or SSL_BIO
 * \return none
 */
void NCCtls_setBlockMode(int32_t block_mode);

/**
 * Get block mode
 * \param  none
 * \return  the block_mode, SSL_NBIO or SSL_BIO
 */
int32_t NCCtls_getBlockMode(void);

/**
 * Set if is auto add server's root CA certificate
 *           when server's certificates cann't pass verification in handshake
 * \param is_auto_add(input) the flag of auto add server certificate to trust store, TRUE or FALSE
 * \return  none
 */
void NCCtls_setAutoAddCert(int32_t is_auto_add);

/**
 * Get if auto add server's root CA certificate when it not in trust store
 * \param  none
 * \return
 *   TRUE   session is auto add server's root CA certificate
 *   FALSE  session is not auto add server's root CA certificate
 */
int32_t NCCtls_getAutoAddCert(void);

/**
 * Set uesr's cert verify callback
 * \param verify_callback(input)  user's cert verify callback to verify server's certificates in handshake
 * \return  none
 */
void NCCtls_setCertVerifyCallback(CERT_VERIFY_CALLBACK_FUNC verify_callback);

/**
 * Get user's cert verify callback
 * \param  none
 * \return  user's cert verify callback
 */
CERT_VERIFY_CALLBACK_FUNC NCCtls_getCertVerifyCallback(void);

/**
 * Set uesr's cert display callback when server's certificates cann't pass verification in handshake
 * \param display_callback(input)  user's cert display callback to display server's certificate to user
 * \return
 *  SSL_OK   none
 */
void NCCtls_setCertDisplayCallback(CERT_DISPLAY_CALLBACK_FUNC display_callback);

/**
 * Get uesr's cert display callback when server's certificates cann't pass verification in handshake
 * \param  none
 * \return    user's cert display callback
 */
CERT_DISPLAY_CALLBACK_FUNC NCCtls_getCertDisplayCallback(void);

/**
 * Get the length of supported cipher suites by SSL/TLS
 * \return  the length of supported cipher suite by SSL/TLS
 */
int32_t NCCtls_getSupportedCipherSuitesLen(void);

/**
 * Get the cipher suites of supported cipher suites by SSL/TLS
 * \param  len(input) the length of supported cipher suites by SSL/TLS
 * \param valueBuf(output) where to store the cipher suites got
 * \return
 *  SSL_OK      succeed
 *   error code
 *     SSL_NULL_POINTER
 */
int32_t NCCtls_getSupportedCipherSuites(uint8_t *valueBuf,int32_t len);

/**
 * Get the length of connection cipher suite
 * \return
 *  the length of connection cipher suite
 *  error code
 *     SSL_CONN_NOT_EXIST
 */
int32_t NCCtls_getConnCipherSuiteLen(int32_t connection);

/**
 * Get the cipher suite of one connection
 * \param connection(input)   the connection on which cipher suite need to be got
 * \param len(input) the length of connection cipher suite
 * \param valueBuf(output)    where to store the cipher suite got
 * \return
 *   SSL_OK      succeed
 *   error code
 *     SSL_CONN_NOT_EXIST
 */
int32_t NCCtls_getConnCipherSuite(int32_t connection, uint8_t *valueBuf,int32_t len);

/**
 * Get the length of server certificate
 * \param session(input)  the session which the certificate belongs
 * \return
 *  > 0   the length of server certificate
 *   error code
 *     SSL_SESSION_NOT_EXIST
 */
 int32_t NCCtls_getServerCertLen(int32_t session);

/**
 * Get the certificate of server
 * \param session(input)  the session which the certificate belongs
 * \param buffer Buffer where the certificate is to be copied.
 * \param len Size of buffer in bytes.
 * \return
 *   SSL_OK      succeed
 *   error code
 *     SSL_SESSION_NOT_EXIST
 */
int32_t NCCtls_getServerCert(int32_t session,uint8_t* buffer, int32_t len);

/**
 * Get the socket of an connection.
 * \param connection connection descriptor.
 * \return
 *   socket     success
 *   error code
 *     SSL_CONN_NOT_EXIST
 */
 int32_t NCCtls_getConnectionSocketId(int32_t connection);

/**
 * Get server certificate
 * \param session(input)  the session which the certificate belongs
 * \return
 *  the server certificate obj  succeed
 *  NULL                        session not exist
 */
const T_CERT_Obj* NCCtls_getServerCertObj(int32_t session);

/**
 * Handle user accept verify server not pass
 * \param server_name the name of ssl server
 * \param connection connection descriptor.
 * \return
 *   SSL_OK     success
 *   error code
 *     SSL_CONN_NOT_EXIST
 */
int32_t NCCtls_userAcceptVerifyNotPass(uint8_t *server_name,int32_t connection);

/**
 * Get the reason of verify server failed
 * \param connection connection descriptor.
 * \return
 *   error code
 *      if bit 0 is 1, means server cert is not trusted
 *      if bit 1 is 1, means server cert expired
 *      if bit 2 is 1, means server cert site name not match
 *   error code
 *     SSL_CONN_NOT_EXIST
 */
int8_t NCCtls_getVerifyServerFailedReason(int32_t connection)  ;

/**
 * Set the server name of session
 * \param connection(input)  the connection descriptor.
 * \param server_name(input)  the server name
 * \return
 *   SSL_OK     success
 *   error code
 *     SSL_SESSION_NOT_EXIST
 */
int32_t NCCtls_setSessServerName(int32_t connection,uint8_t *server_name);

/**
 * Check if server name is match
 * \param session(input)  the session which the certificate belongs
 * \return
 *   TRUE   match
 *   FALSE  not match
 *   error code
 *     SSL_SESSION_NOT_EXIST
 */
int32_t NCCtls_checkIfServerNameMatch(int32_t session);

/**
 * check to see if waiting for user response when auth server failed.
 * \param connection connection descriptor.
 * \return   the flag to indicate if waiting for user response
 */
int32_t NCCtls_getWaitForUserRes(int32_t connection);

/**
 * Set if waiting for user response when auth server failed.
 * \param connection connection descriptor.
 * \param is_waiting_for  the flag to indicate if waiting for user response
 * \return  none
 */
void NCCtls_setWaitForUserRes(int32_t connection,int32_t is_waiting_for);

/**
 * Check whether there are other connections in the same session waiting for user response
 * \param connection(input)  the connection descriptor
 * \return
 *   TRUE   yes
 *   FALSE  no
 */
int32_t NCCtls_checkIfOtherConnWaitForUserRes(int32_t connection);


#ifdef __cplusplus
}
#endif

#endif  /* __NCCTLS_INTERFACE_H__ */
