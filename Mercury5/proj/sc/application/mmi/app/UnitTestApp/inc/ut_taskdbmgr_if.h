#ifndef __UT_TASKDBMGR_IF_H__
#define __UT_TASKDBMGR_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getTaskDbMgr_if_UT(void);
int   noTaskDbMgr_if_UT(void);
void  releaseTaskDbMgr_if_UT(FILE *pFile);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_TASKDBMGR_IF_H__ */
