/* ut_client_req.h */
#ifndef __UT_CLIENT_REQ_H__
#define __UT_CLIENT_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getClient_UT(void);
int   noClient_UT(void);
void  releaseClient_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CLIENT_REQ_H__ */
