#ifndef __UT_DBUTILITY_REQ_H__
#define __UT_DBUTILITY_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getDBUtility_UT(void);
int   noDBUtility_UT(void);
void  releaseDBUtility_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_DBUTILITY_REQ_H__ */
