
#ifndef __TLS_INT_H__
#define __TLS_INT_H__

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------    Variable Declaration    ------------------------*/
extern T_SSL_List gSSL_SessionList;
extern int32_t gSSL_Connection[SSL_MAX_CONNECT_NUM];
extern int32_t SSL_Display_Time;
extern const uint8_t gSSL_Padding1[];
extern const uint8_t gSSL_Padding2[];

/*----------------------    Function Declaration    ------------------------*/
int32_t sslHandshake(T_SSL_Conn *ssl_connect);
int32_t sslSendFinished( T_SSL_Conn *ssl_connect);
int32_t sslChangeCipherState(T_SSL_Conn *ssl_connect, int32_t which);
int32_t sslChangeCipher(T_SSL_Conn *ssl_connect);
void sslDestroySession(T_SSL_Sess * dssl_session);
int32_t sslGenerateMasterSecret(T_SSL_Conn *ssl_connect, uint8_t *out, uint8_t *p,int32_t len);
int32_t sslSetCipher(T_SSL_Conn *ssl_connect);
int32_t sslSendPkt(T_SSL_Conn *ssl_connect);
int32_t sslSetKeyBlock(T_SSL_Conn *ssl_connect);
int32_t tlsGenerateMasterSecret(T_SSL_Conn *ssl_connect, uint8_t *p,int32_t len);
void  tlsPRF(uint32_t md5_id, uint32_t sha1_id, uint8_t *label, int32_t label_len,
             const uint8_t *sec, int32_t slen, uint8_t *out1,uint8_t *out2, int32_t olen);
void sslDestroyRecord(T_SSL_Conn* pst_ssl_socket);
int32_t sslIsConnectExist(int32_t connection);
int32_t sslInitConnection(T_SSL_Conn* pst_ssl_socket);
int32_t sslIsSessionExist(int32_t session);
int32_t sslResumeSocket(int32_t socket_id,int32_t session,int32_t *connection);
void sslSysTaskLoop(void);
void sslDestroyConnection(T_SSL_Conn* pst_ssl_socket);
void sslUnInit(void);
int32_t sslInit (void );
int32_t sslOpen(void);
int32_t sslDefaultCertCallBack(int32_t session,T_CERT_Buf *cert_list, int32_t cert_count);
int32_t sslConnect(uint32_t ip_addr,uint16_t port,int32_t connection,int32_t appId);
void sslClose(int32_t connection);
int32_t sslGetState(int32_t connection);
int32_t sslRecvPkt( T_SSL_Conn *ssl_connect);
int32_t sslRecordOutput(T_SSL_Conn *ssl_connect, int32_t ct,uint32_t  len,int8_t pending);
void  sslSendAlert( T_SSL_Conn *ssl_connect, uint8_t level, uint8_t desc);
int32_t sslGetPlainAppFromRecvBufToUserBuf( T_SSL_Conn *ssl_connect, uint8_t * read_buf, uint32_t data_len);
int32_t sslGetPlainHsOrAlertFromHsQueToReadRecordBuf(T_SSL_Conn *ssl_connect, int8_t ct, int8_t mt);
T_SSL_HsPkt* sslGetHsPkt( T_SSL_Que * pkt_queue);
int32_t sslFreeHsPkt( T_SSL_HsPkt * pkt);
int32_t sslDefaultDisplayCert(T_CERT_Obj *cert_obj, int8_t err_code);


#ifdef __cplusplus
}
#endif

#endif /* __TLS_INT_H__ */

