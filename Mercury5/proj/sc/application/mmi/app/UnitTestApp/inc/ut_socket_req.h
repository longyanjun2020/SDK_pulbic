/**
* @file ut_socket_req.h
* @brief Unit Test for SrvWrapper of Socket.
*/
#ifndef __UT_SOCKET_REQ_H__
#define __UT_SOCKET_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getSocket_UT(void);
int   noSocket_UT(void);
void  releaseSocket_UT(FILE *pFn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_SOCKET_REQ_H__ */