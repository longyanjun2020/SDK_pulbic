#ifndef __SG_SOCKET_ADAPTOR__H_
#define __SG_SOCKET_ADAPTOR__H_

#include "http_client.h"


typedef void (*sg_connect_CB)(sg_soc_struct *pSoc, sg_soc_err eErrCode);
typedef void (*sg_write_CB)(sg_soc_struct *pSoc, sg_soc_err eErrCode);
typedef void (*sg_read_CB)(sg_soc_struct *pSoc, SG_UINT8 *pBuf, SG_INT32 sLen);
typedef void (*sg_close_CB)(sg_soc_struct *pSoc, sg_soc_err eErrCode);
typedef void (*sg_gethostbyname_CB)(sg_soc_struct *pSoc);
typedef void (*sg_recv_CB)(sg_soc_struct *pSoc, SG_INT32 sLen);


SG_SOCKET_HANDLE sg_create_socket(sg_soc_struct *pSoc, sg_soc_type type, sg_recv_CB pfnRecvCb);
sg_soc_err sg_connect_async(sg_soc_struct *pSoc, SG_UINT16 port, sg_connect_CB pfnConnectCb);
sg_soc_err sg_write_async(sg_soc_struct *pSoc, const SG_UINT8  *cpBuf, SG_INT32 sLen, sg_write_CB pfnWriteCb, SG_INT32 sFlags);
#if 0 //unused
sg_soc_err sg_close_async(sg_soc_struct *pSoc, sg_close_CB pfnCloseCb);
#endif
sg_soc_err sg_close_sync(sg_soc_struct *pSoc);
sg_soc_err sg_gethostbyname_async(sg_soc_struct *pSoc, SG_UINT8 *host_name, sg_gethostbyname_CB pfnGetHostByNameCb);
void sg_trace_log(const SG_UINT8  *cpBuf, SG_INT32 sLen);

#endif/* __SG_SOCKET_ADAPTOR__H_ */
