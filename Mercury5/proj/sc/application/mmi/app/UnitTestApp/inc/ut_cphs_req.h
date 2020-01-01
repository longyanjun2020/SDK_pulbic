/* ut_cphs_req.h */
#ifndef __UT_CPHS_REQ_H__
#define __UT_CPHS_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getCPHS_UT(void);
int   noCPHS_UT(void);
void  releaseCPHS_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CPHS_REQ_H__ */
