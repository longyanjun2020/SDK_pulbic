/* ut_calllog_req.h */
#ifndef __UT_CALLLOG_REQ_H__
#define __UT_CALLLOG_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getCalllog_UT(void);
int   noCalllog_UT(void);
void  releaseCalllog_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CALLLOG_REQ_H__ */
