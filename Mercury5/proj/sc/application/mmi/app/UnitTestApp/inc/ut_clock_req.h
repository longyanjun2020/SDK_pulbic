/* ut_clock_req.h */
#ifndef __UT_CLOCK_REQ_H__
#define __UT_CLOCK_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getCLOCK_UT(void);
int   noCLOCK_UT(void);
void  releaseCLOCK_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CLOCK_REQ_H__ */
