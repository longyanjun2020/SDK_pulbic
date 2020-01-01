/* ut_cbs_req.h */
#ifndef __UT_CBS_REQ_H__
#define __UT_CBS_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getCBS_UT(void);
int   noCBS_UT(void);
void  releaseCBS_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CBS_REQ_H__ */
