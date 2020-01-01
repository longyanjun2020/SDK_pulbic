#ifndef __UT_DATAMGR_REQ_H__
#define __UT_DATAMGR_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getDataMgr_UT(void);
int   noDataMgr_UT(void);
void  releaseDataMgr_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_DATAMGR_REQ_H__ */
