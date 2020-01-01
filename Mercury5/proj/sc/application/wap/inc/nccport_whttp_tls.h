
/**
 * @file
 * TLS Porting Layer
 *
 * Basic support functions that are needed by TLS.
 *
 * <!-- #interface list begin -->
 * \section nccport_whttp_tls Interface
 * - NCCPort_whttptls_create()
 * - NCCPort_whttptls_connect()
 * - NCCPort_whttptls_tlsUpdate()
 * - NCCPort_whttptls_sendData()
 * - NCCPort_whttptls_recvData()
 * - NCCPort_whttptls_getServerCertLen()
 * - NCCPort_whttptls_getVersion()
 * - NCCPort_whttptls_getServerCert()
 * - NCCPort_whttptls_getConnCipherSuite()
 * - NCCPort_whttptls_close()
 * <!-- #interface list end -->
 */

#ifndef __NCCPORT_WHTTP_TLS_H__
#define __NCCPORT_WHTTP_TLS_H__

#define TLS_OK	0
#define TLS_CONN_NOT_EXIST  -1

/**
 * Create a SSL connection.
 * \param ip_addr Fast host address
 * \return FNDB_NCCPort_NET_ERROR:failed;    >0:success
 */
int32_t NCCPort_whttptls_create(int8_t *host_name,uint32_t ip_addr);

/**
 * SSL connection.
 * \param ip_addr Fast host ip address
 * \param port Fast host port
 * \param conn ssl Connect NO.
 * \return
 *      success:FNDB_NCCPort_NET_OK;
 *      failed:FNDB_NCCPort_NET_ERROR
 *      pending:FNDB_NCCPort_NET_PENDING
 */
int32_t NCCPort_whttptls_connect( uint8_t *server_name, uint32_t ip_addr,
	int32_t port, int32_t *conn, int32_t *tlsAuthServerErrCode,int32_t appId);

/**
 * Update to TLS through channeling.
 * \param s Socket NO.
 * \return
 *    >0: success and return connect NO.
 *   other: failed.
 */
int32_t NCCPort_whttptls_tlsUpdate(int32_t s);

/**
 * Send data stored in the buffer.
 * \param conn Connect NO.
 * \param sendbuf Point to send data.
 * \param len Length of send data.
 * \return
 *   FNDB_NCCPort_NET_NOBUFF: No send data.
 *   FNDB_NCCPort_NET_ERROR: Send failed.
 *   *   >0: Send success and return the length of send data.
 */
int32_t NCCPort_whttptls_sendData(int32_t conn, uint8_t *sendbuf, int32_t len);
/**
 * Receive data and store in buffer.
 * \param conn Connect NO.
 * \param recvbuf Receive buffer.
 * \param len Buffer length.
 * \return
 *   FNDB_NCCPort_NET_NOBUFF: No received storage.
 *   FNDB_NCCPort_NET_PENDING:Waiting.
 *   FNDB_NCCPort_NET_ERROR:Receive failed.
 *   >0:Received success and return the length of send data.
 */
int32_t NCCPort_whttptls_recvData(int32_t conn, uint8_t *recvbuf, int32_t len);

/**
 * Get the length of the server certificate
 * \param conn Connect NO.
 * \return
 *   >=0:length of server certificate.
 *   TLS_CONN_NOT_EXIST: connection does not exist
 */
int32_t NCCPort_whttptls_getServerCertLen(int32_t conn);

/**
 * Get the secure protocol
 * \param conn Connect NO.
 * \return
 *   the version of TLS
 *   TLS_CONN_NOT_EXIST: connection does not exist
 */
int32_t NCCPort_whttptls_getVersion(int32_t conn);

/**
 * Get the certificate of server
 * \param conn Connect NO.
 * \param buf  Buffer where the certificate is to be copied.
 * \param len  Size of buffer in bytes.
 * \return
 *   TLS_OK: succeed
 *   TLS_CONN_NOT_EXIST: connection does not exist
 */
int32_t NCCPort_whttptls_getServerCert(int32_t conn,uint8_t *buf,int32_t len);

/**
 * Get the length of cipher suite
 * \param conn Connect NO.
 * \return
 *   >0: length of the cipher suite
 *   TLS_CONN_NOT_EXIST: connection does not exist
 */
int32_t NCCPort_whttptls_getConnCipherSuiteLen(int32_t conn);

/**
 * Get the cipher suite of the connection
 * \param conn Connect NO.
 * \param buf  Buffer where the suite is to be copied.
 * \param len  Size of buffer in bytes.
 * \return
 *   TLS_OK: succeed
 *   TLS_CONN_NOT_EXIST: connection does not exist
 */
int32_t NCCPort_whttptls_getConnCipherSuite(int32_t conn,uint8_t* buf,int32_t len);

/**
 * Close connection.
 * \param conn Connection NO.
 */
void NCCPort_whttptls_close(int32_t conn);

#endif /* __NCCPORT_WHTTP_TLS_H__ */

