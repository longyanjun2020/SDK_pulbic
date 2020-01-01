
#ifndef __WHTTP_SOCKET_H__
#define __WHTTP_SOCKET_H__

#include <nccport_browser_net.h>
#include <nccport_whttp_tls.h>

#ifdef __cplusplus
extern "C"{
#endif

#define NET_SOCKET_INVALID  -1

/************************ Function Declaration ****************************/
void htNet_Init( void );
void htNet_shut( void );
void htNet_CreateSocket(HTTPCTXT *ctxt);
void htNet_CloseSocket(HTTPCTXT *ctxt);
int32_t htNet_Connect(HTTPCTXT *ctxt);
int32_t htNet_SetNoBlock(HTTPCTXT *ctxt);
int32_t htNet_GetHostByName(HTTPCTXT *ctxt,
                            int8_t * httpproxy,
                            int32_t httpproxyport);
int32_t htNet_Send( HTTPCTXT *ctxt);
int32_t htNet_Recv(HTTPCTXT *ctxt);

#ifdef __cplusplus
}
#endif

#endif /* __WHTTP_SOCKET_H__ */
